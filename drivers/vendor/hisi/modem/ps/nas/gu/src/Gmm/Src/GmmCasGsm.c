

/*****************************************************************************
   1 头文件包含
*****************************************************************************/
#include "GmmInc.h"
#include "GmmCasGlobal.h"
#include "GmmCasComm.h"
#include "GmmCasMain.h"
#include "GmmCasSuspend.h"
#include "GmmCasSend.h"
#include "GmmCasGsm.h"
#include "GmmMmInterface.h"
#include "GmmExt.h"
#include "NasGmmSndOm.h"
#include "NasUtranCtrlInterface.h"
#include "NasUsimmApi.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人:luojian 107747;检视人:sunshaohua65952;原因:LOG方案设计需要*/
#define    THIS_FILE_ID        PS_FILE_ID_GMM_CASGSM_C
/*lint +e767 修改人:luojian 107747;检视人:sunshaohua*/

extern VOS_VOID Gmm_RcvRoutingAreaUpdateRejectMsg_AttachFlg_Handling(VOS_VOID);


/*lint -save -e958 */

/*****************************************************************************
 Prototype      : GMM_CasCellS0E45
 Description    :
                  接收ID_LL_GMM_STATUS_IND消息处理
                  HSS 4100 V200R001 新增
                  接收到LLC上报状态信息ID_LL_GMM_STATUS_IND的处理

 Input          : VOS_VOID*     pRcvMsg     入口消息指针
 Output         :
 Return Value   :
 Calls          :
 Called By      :
 History        :
  1.Date        : 2005-08-25
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_VOID GMM_CasCellS0E45(VOS_VOID *pRcvMsg)
{
    LL_GMM_STATUS_IND_MSG   *pStatusInd;

    if ((GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
        || (GMM_DEREGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
        || (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
        || (GMM_TC_ACTIVE == g_GmmGlobalCtrl.ucState)
        || (0x20 == (g_GmmGlobalCtrl.ucState & 0xF0)))
    {
        /* GSM模式处理过程 */
        pStatusInd = (LL_GMM_STATUS_IND_MSG*)pRcvMsg;

        /* 检查TLLI值 */
        if (gstGmmCasGlobalCtrl.ulTLLI != pStatusInd->stLlGmmStatusInd.ulTlli)
        {
            #ifdef __PS_WIN32_RECUR__
            if ((pStatusInd->stLlGmmStatusInd.ulTlli & 0xf0000000) != 0x70000000)
            {
                GMM_AssignSysTlli();                                                /* 同步更新LLC的new TLLI */
            }
            #else
                GMM_AssignSysTlli();                                                /* 同步更新LLC的new TLLI */
            #endif

        }

        if (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
        {
            /*如果层二还没有挂起，需要挂起*/
            if (GMM_NOT_SUSPEND_LLC == gstGmmCasGlobalCtrl.ucSuspendLlcCause)
            {
                GMM_SndLlcSuspendReq();
            }

            /*在GMM_ROUTING_AREA_UPDATING_INITIATED状态，没有置GMM_SUSPEND_LLC_FOR_RAU*/
            if (GMM_SUSPEND_LLC_FOR_RAU != (GMM_SUSPEND_LLC_FOR_RAU & gstGmmCasGlobalCtrl.ucSuspendLlcCause))
            {
                gstGmmCasGlobalCtrl.ucSuspendLlcCause |= GMM_SUSPEND_LLC_FOR_RAU;
            }
        }
        /* 分析ucCause原因值 */
        GMM_ExecLlgmmStatusIndCause(pStatusInd->stLlGmmStatusInd.usCause);
    }

    return;
}

VOS_VOID NAS_GMM_RcvGmmRabmRoutingAreaUpdateRsp(VOS_VOID *pRcvMsg)
{
    VOS_UINT8                                ucNum = 0;
    GMMRABM_ROUTING_AREA_UPDATE_RSP_MSG     *pRabmRauRspMsg;

    Gmm_TimerStop(GMM_TIMER_RAU_RSP);

    gstGmmCasGlobalCtrl.ucRabmRauRspRcvdFlg = VOS_TRUE;

    if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        return;
    }
    pRabmRauRspMsg = (GMMRABM_ROUTING_AREA_UPDATE_RSP_MSG*)pRcvMsg;

    /* 保存消息中NPDU的内容 */
    if (GMM_RABM_NPDU_VALID == pRabmRauRspMsg->ucNpduValidFlg)
    {
        g_GmmRauCtrl.ucNpduCnt = pRabmRauRspMsg->aucRecvNPDUNumListIE[1];
        g_GmmDownLinkNpduBake.ucNpduCnt = pRabmRauRspMsg->aucRecvNPDUNumListIE[1];
        for (ucNum=0; ucNum<g_GmmRauCtrl.ucNpduCnt; ucNum++)
        {
            g_GmmRauCtrl.aucNpduNum[ucNum] =
                pRabmRauRspMsg->aucRecvNPDUNumListIE[ucNum+2];
            g_GmmDownLinkNpduBake.aucNpduNum[ucNum] =
                pRabmRauRspMsg->aucRecvNPDUNumListIE[ucNum+2];
        }
    }
    else
    {
        g_GmmRauCtrl.ucNpduCnt = 0;     /* UE侧NPDU无有效数据 */
        g_GmmDownLinkNpduBake.ucNpduCnt = 0;
    }

    /* 不需要等待WRR的回复消息，或者已经收到WRR的回复消息，进行RAU流程结束的相应处理 */
    if (   (VOS_FALSE == g_GmmInterRatInfoCtrl.ucRauCmpWaitInterRatCnfMsg)
        || (VOS_TRUE == g_GmmInterRatInfoCtrl.ucInterRatCnfMsgRcvdFlg))
    {
        NAS_GMM_RauCompleteHandling();
    }

    return;
}
/*****************************************************************************
 Prototype      : GMM_RcvGasPagingInd
 Description    :
                  接收GRRMM_PAGING_IND消息入口处理
                  HSS 4100 V200R001 新增

 Input          : VOS_VOID*     pMsg     入口消息指针
 Output         :
 Return Value   :
 Calls          :
 Called By      :
 History        :
  1.Date        : 2005-08-25
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_VOID GMM_RcvGasPagingInd(VOS_VOID *pMsg)
{
    GRRMM_PAGING_IND_ST     *pIndMsg;

    if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        GMM_LOG_WARN("GMM_RcvGasPagingInd():Warning: message only use for GSM");
        return;
    }

    pIndMsg = (GRRMM_PAGING_IND_ST*)pMsg;
    /* 判断寻呼发起的域 */
    if (GAS_PAGING_CS == pIndMsg->ucPagingType)
    {/* CS寻呼 */
        return;                                                                 /* 不处理，直接结束 */
    }

    switch (g_GmmGlobalCtrl.ucState)
    {
    case GMM_DEREGISTERED_INITIATED:
    case GMM_REGISTERED_IMSI_DETACH_INITIATED:
       GMM_RcvGsmPagingAtDeregInit(pIndMsg);
       break;

    case GMM_ROUTING_AREA_UPDATING_INITIATED:
       GMM_RcvGsmPagingAtRauInit(pIndMsg);
       break;

    case GMM_REGISTERED_NORMAL_SERVICE:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
       GMM_RcvGsmPagingAtRegNmlServ(pIndMsg);
       break;
    case GMM_REGISTERED_PLMN_SEARCH:
        GMM_RcvGsmPaging_RegPlmnSrch(pIndMsg);
        break;
    default:
       break;
    }

    return;
}


VOS_UINT32 NAS_GMM_GsmAccessBarredProcess(VOS_VOID)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8    enRatType;


    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;
    enRatType   = NAS_MML_GetCurrNetRatType();

    if ( (VOS_TRUE == NAS_MML_GetGsmForbidFlg())
      && (NAS_MML_NET_RAT_TYPE_GSM == enRatType))
    {
        Gmm_ComStaChg(GMM_DEREGISTERED_ATTACH_NEEDED);
        return VOS_ERR;
    }
    if ((GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
        || ((0x10 == (g_GmmGlobalCtrl.ucState & 0xF0))
        && (GMM_NULL != g_GmmGlobalCtrl.ucState)
        && (GMM_DEREGISTERED_NO_IMSI != g_GmmGlobalCtrl.ucState)))
    {                                                                       /* PS域没有注册                             */
        Gmm_ComStaChg(GMM_DEREGISTERED_ATTACH_NEEDED);
        return VOS_ERR;
    }
    else if (GMM_REGISTERED_IMSI_DETACH_INITIATED == g_GmmGlobalCtrl.ucState)
    {
        Gmm_TimerStop(GMM_TIMER_T3321);                                     /* 停T3321                                  */
        Gmm_ComStaChg(GMM_REGISTERED_UPDATE_NEEDED);

        /* 判断等待标志是否存在，如果存在则向MMC,MM发送DETACH信息 */
        if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
        {
            NAS_GMM_SndMmcMmDetachInfo();
        }
        return VOS_ERR;
    }
    else if (GMM_DEREGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
    {
        Gmm_TimerStop(GMM_TIMER_T3321);                                     /* 停T3321                                  */
        NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);
        Gmm_ComStaChg(GMM_DEREGISTERED_ATTACH_NEEDED);

        Gmm_ClearLlcData(LL_GMM_CLEAR_DATA_TYPE_ALL);                       /* 去指配TLLI，释放LLC层数据 */
        Gmm_TimerStop(GMM_TIMER_T3314);
        gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_IDLE;
        gstGmmCasGlobalCtrl.ulReadyTimerValue = 44000;


#if (FEATURE_LTE == FEATURE_ON)
        if (GMM_TIMER_T3312_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
        {
            NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
        }
#endif
        Gmm_TimerStop(GMM_TIMER_T3312);
        NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
        if (GMM_UEID_P_TMSI_SIGNATURE
            == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask & GMM_UEID_P_TMSI_SIGNATURE))
        {                                                                           /* DETACH成功且使用了P_TMSI_SIGNATURE       */
            g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI_SIGNATURE;   /* 清除P_TMSI_SIGNATURE                     */

            NAS_MML_InitUeIdPtmsiSignatureInvalid();
            if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* 更新SIM卡信息                            */
            }
            else
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
            }
        }

        /* 判断等待标志是否存在，如果存在则向MMC,MM发送DETACH信息 */
        if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
        {
            if (GMM_WAIT_PS_DETACH == (g_GmmGlobalCtrl.stDetachInfo.enDetachType & GMM_WAIT_PS_DETACH))
            {
                NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);
            }
            NAS_GMM_SndMmcMmDetachInfo();
        }
        else
        {
            /* 收到网侧的去注册成功后需要通知MM，否则MM不启动T3212定时器 */
            NAS_GMM_SndMmGprsDetachComplete();
        }

        return VOS_ERR;
    }
    else if ((GMM_NULL != g_GmmGlobalCtrl.ucState)
        && (GMM_DEREGISTERED_NO_IMSI != g_GmmGlobalCtrl.ucState))
    {
        Gmm_ComStaChg(GMM_REGISTERED_UPDATE_NEEDED);
        return VOS_ERR;
    }
    else
    {
    }

    return VOS_OK;
}


VOS_UINT32 NAS_GMM_GasSysInfoPreCheck(VOS_VOID *pMsg)
{
    MMCGMM_GSM_SYS_INFO_IND_ST  *pSysInfoMsg;
    VOS_UINT32                  ulResult;
    VOS_UINT8                           ucSimPsRegStatus;

    pSysInfoMsg = (MMCGMM_GSM_SYS_INFO_IND_ST *)pMsg;

    Gmm_SndSmSysInfoInd(pSysInfoMsg->ucSgsnRelease);

    gstGmmCasGlobalCtrl.ucCellReselFlg = VOS_FALSE;

    ucSimPsRegStatus = NAS_MML_GetSimPsRegStatus();

    if ( (VOS_TRUE == ucSimPsRegStatus)
      && (MMC_GMM_NO_FORBIDDEN == pSysInfoMsg->ulForbiddenFlg) )
    {
        if ((RRC_NAS_ACCESS_RESTRICTION_NORMAL_SERVICE  == pSysInfoMsg->unAcInfo.ucRestrictType)
         || (RRC_NAS_ACCESS_RESTRICTION_ALL_SERVICE     == pSysInfoMsg->unAcInfo.ucRestrictType))
        {
            GMM_BufferMsgDump();

            ulResult = NAS_GMM_GsmAccessBarredProcess();
            if (VOS_ERR == ulResult)
            {

                NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED);

                return VOS_ERR;
            }
        }
    }

    /* 分析接收消息，修改参数标志 */
    if (GMM_FAILURE == GMM_SaveGsmSysInfoIndMsgPara(pSysInfoMsg))
    {
        GMM_LOG_NORM("GMM_RcvGasSysInfoInd():Normal: Sys info handle finish in GMM_SaveGsmSysInfoIndMsgPara.");
        return VOS_ERR;
    }

    if ((GMM_REGISTERED_PLMN_SEARCH == g_GmmGlobalCtrl.ucState)
        || (GMM_DEREGISTERED_PLMN_SEARCH == g_GmmGlobalCtrl.ucState))
    {
        NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_PTMSI_RAI);
    }

    if ((GMM_REGISTERED_PLMN_SEARCH == g_GmmGlobalCtrl.ucState)
        && (GMM_TRUE == g_GmmGlobalCtrl.ucCvrgAreaLostFlg))
    {
        if(GMM_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
        {
            g_GmmGlobalCtrl.ucNeedChgServiceStatus = VOS_FALSE;
        }
        Gmm_ComStaChg(GMM_REGISTERED_NO_CELL_AVAILABLE);
        g_GmmGlobalCtrl.ucNeedChgServiceStatus = VOS_TRUE;
    }

    return VOS_OK;
}


VOS_VOID NAS_GMM_GasSysInfoDistribute(VOS_VOID *pMsg)
{
    switch (g_GmmGlobalCtrl.ucState)
    {
    case GMM_DEREGISTERED_NORMAL_SERVICE:
    case GMM_DEREGISTERED_LIMITED_SERVICE:
    case GMM_DEREGISTERED_ATTACH_NEEDED:
    case GMM_DEREGISTERED_NO_CELL_AVAILABLE:
    case GMM_DEREGISTERED_PLMN_SEARCH:
       GMM_CasCellS1E49(pMsg);
       break;

    case GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH:
       GMM_CasCellS4E49(pMsg);
       break;

    case GMM_REGISTERED_INITIATED:
       GMM_CasCellS8E49(pMsg);
       break;

    case GMM_REGISTERED_NORMAL_SERVICE:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
       GMM_CasCellS9E49(pMsg);
       break;

    case GMM_REGISTERED_LIMITED_SERVICE:
    case GMM_REGISTERED_PLMN_SEARCH:
       GMM_CasCellS10E49(pMsg);
       break;

    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
       GMM_CasCellS11E49(pMsg);
       break;

    case GMM_REGISTERED_UPDATE_NEEDED:
    case GMM_REGISTERED_NO_CELL_AVAILABLE:
       NAS_GMM_EnterCovery(pMsg);
       break;

    case GMM_REGISTERED_IMSI_DETACH_INITIATED:
    case GMM_DEREGISTERED_INITIATED:
       GMM_CasCellS18E49(pMsg);
       break;

    case GMM_ROUTING_AREA_UPDATING_INITIATED:
       GMM_CasCellS19E49(pMsg);
       break;
    case GMM_SUSPENDED_WAIT_FOR_SYSINFO:
       GMM_RcvGasSysInfoInd_SuspWaitSys(pMsg);
       break;
    default:
       break;
    }

    return;
}


VOS_VOID GMM_RcvGasSysInfoInd(VOS_VOID *pMsg)
{
    VOS_UINT32                          ulRestul;
    VOS_UINT8                           ucSimPsRegStatus;

    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus;

    VOS_UINT8                           ucPsAttachAllowFlg;

    MMCGMM_GSM_SYS_INFO_IND_ST         *pSysInfo;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulT3423StatuChgNeedRegFlg;
    VOS_UINT32                          ulIsNeedDeactiveIsrFlg;
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrNetType;

    pstRplmnCfgInfo           = NAS_MML_GetRplmnCfg();
    enCurrNetType             = NAS_MML_GetCurrNetRatType();
    ulT3423StatuChgNeedRegFlg = NAS_GMM_IsT3423StatusChangeNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                                 NAS_MML_GetTinType(), NAS_MML_GetT3423Status());
#endif

    pstConnStatus       = NAS_MML_GetConnStatus();

    NAS_GMM_LogGmmCtxInfo();

    /* 停HO等待系统消息定时器 */
    Gmm_TimerStop(GMM_TIMER_HO_WAIT_SYSINFO);

    /* 如果CS正在建立连接或者连接已经建立成功 */
    pSysInfo           = (MMCGMM_GSM_SYS_INFO_IND_ST *)pMsg;
    ucPsAttachAllowFlg = NAS_MML_GetPsAttachAllowFlg();

    /* PS可以发起注册时才需要缓存系统信息 */
    if ((VOS_FALSE == NAS_MML_GetPsRestrictRegisterFlg())
     && (0 != pSysInfo->ucGprsSupportInd)
     && (MMCGMM_GSM_NO_FORBIDDEN == pSysInfo->ulForbiddenFlg)
     && (VOS_TRUE  == ucPsAttachAllowFlg))
    {
        if (VOS_TRUE == pstConnStatus->ucCsSigConnStatusFlg)
        {
            /* RR连接不存在表示CS正在建立连接,此时缓存系统消息 */
            if (VOS_FALSE == pstConnStatus->ucRrcStatusFlg)
            {
                NAS_GMM_SaveGsmSysInfo((MMCGMM_GSM_SYS_INFO_IND_ST*)pMsg);
            }
            return;
        }
    }

#if (FEATURE_ON == FEATURE_LTE)
    if (GMM_REGISTERED_PLMN_SEARCH == g_GmmGlobalCtrl.ucState)
    {
        /* L下丢网，搜网到GU后，需要判断如果有ISR激活后激活的pdp上下文，需要去激活ISR*/
        ulIsNeedDeactiveIsrFlg = NAS_GMM_IsNeedDeactiveIsr_InterSys(gstGmmSuspendCtrl.ucPreRat, enCurrNetType, MMC_SUSPEND_CAUSE_BUTT);

        if (VOS_TRUE == ulIsNeedDeactiveIsrFlg)
        {
            NAS_GMM_WriteTinInfoNvim(NAS_MML_TIN_TYPE_GUTI, pstRplmnCfgInfo->aucLastImsi);

            /* ISR去激活，需要更新pdp激活是在ISR激活前激活的 */
            NAS_MML_UpdateAllPsBearIsrFlg(NAS_MML_PS_BEARER_EXIST_BEFORE_ISR_ACT);
        }
    }
#endif

    ulRestul = NAS_GMM_GasSysInfoPreCheck(pMsg);

    if (VOS_ERR == ulRestul)
    {
        /* 系统消息处理后，释放缓存的系统消息 */
        NAS_GMM_FreeGsmSysInfo();

        gstGmmSuspendCtrl.ucPreRat = NAS_MML_NET_RAT_TYPE_GSM;
        return;
    }

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {
        /*  suspend过程中收到T3312超时，若GPRS NOT SUPPORT,不会再进入suspend的处理，转换为expiredFlag */
        if (GMM_T3312_TIMEOUT == gstGmmSuspendCtrl.ucT3312State)
        {
            g_GmmRauCtrl.ucT3312ExpiredFlg = GMM_TRUE;
            gstGmmSuspendCtrl.ucT3312State = GMM_T3312_NOT_TIMEOUT;
        }
    }

    /* 重选到PS被BARRED的小区,在网络模式I,并且T3312超时 */
    if (VOS_TRUE == NAS_MML_GetPsRestrictRegisterFlg())
    {
        /*  suspend过程中收到T3312超时，若PS barred,不会再进入suspend的处理，转换为expiredFlag */
        if (GMM_T3312_TIMEOUT == gstGmmSuspendCtrl.ucT3312State)
        {
            g_GmmRauCtrl.ucT3312ExpiredFlg = GMM_TRUE;
            gstGmmSuspendCtrl.ucT3312State = GMM_T3312_NOT_TIMEOUT;
        }

        if ((VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
          && (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg))
        {
            NAS_GMM_SndMmLuInitiation(GMMMM_T3312_EXPIRED);
        }
#if (FEATURE_ON == FEATURE_LTE)
        else if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
              && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod)
              && (VOS_TRUE == ulT3423StatuChgNeedRegFlg))
        {
            NAS_GMM_SndMmLuInitiation(GMMMM_T3412OrT3423_EXPIRED);
        }
        else
        {
        }
#endif
    }

    NAS_GMM_GasSysInfoDistribute(pMsg);

    /* 系统消息处理后，释放缓存的系统消息 */
    NAS_GMM_FreeGsmSysInfo();

    gstGmmSuspendCtrl.ucPreRat = NAS_MML_NET_RAT_TYPE_GSM;

    if ((GMM_AGB_GPRS_READY == gstGmmCasGlobalCtrl.GmmSrvState)
        && (GMM_ROUTING_AREA_UPDATING_INITIATED != g_GmmGlobalCtrl.ucState))
    {
        if (GMM_TRUE == gstGmmCasGlobalCtrl.ucCellUpdateFlg)
        {
            NAS_GMM_InitCellUpdate_RcvSysInfo(GMM_FALSE);                                               /* 小区更新 */
            gstGmmCasGlobalCtrl.ucCellUpdateFlg = GMM_FALSE;
        }
    }

    /*  获取SIM卡PS是否有效标志 */
    ucSimPsRegStatus = NAS_MML_GetSimPsRegStatus();

    if (VOS_TRUE != ucSimPsRegStatus)
    {
        g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;
        /* 向MMC发送PS注册结果 */
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                     GMM_MMC_ACTION_RESULT_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_SIM_INVALID);

        g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;
        return;
    }

    /*收到系统消息，可能是小区重选结束，也可能是out of service之后，重新搜到网
      或者是3G重选到2G，或者是CS业务在3G被释放，只有RAI不改变，并且是前面挂起过层2才向层二指示resume*/
    if (GMM_NOT_SUSPEND_LLC != gstGmmCasGlobalCtrl.ucSuspendLlcCause)
    {
        if (GMM_SUSPEND_LLC_FOR_RAU != (GMM_SUSPEND_LLC_FOR_RAU & gstGmmCasGlobalCtrl.ucSuspendLlcCause))
        {
            GMM_SndLlcResumeReq(LL_GMM_RESUME_TYPE_ALL);
            gstGmmCasGlobalCtrl.ucSuspendLlcCause = GMM_NOT_SUSPEND_LLC;
        }
        else
        {
            gstGmmCasGlobalCtrl.ucSuspendLlcCause = GMM_SUSPEND_LLC_FOR_RAU;
        }
    }

    /* 收到G模系统消息, 指示RABM当前系统模式, 根据是否支持GPRS, 挂起或恢复RABM */
    if ((VOS_TRUE == NAS_MML_GetPsRestrictNormalServiceFlg())
     || (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
     || (GMM_FALSE == gstGmmCasGlobalCtrl.ucTlliAssignFlg))
    {
        /* 不支持GPRS、PS bar或者没有指派层2, 挂起RABM, bRatChangeFlg为FALSE
           没有指派层2时如果不挂起RABM，RABM会向SN发送数据，SN会发送到LLC，
           而LLC在未指派情况下接收到数据会释放内存导致解除流控,后续数传小包会将消息队列灌满 */
        NAS_GMM_SndRabmSysSrvChgInd(NAS_MML_NET_RAT_TYPE_GSM,
                                    VOS_FALSE,
                                    VOS_TRUE,
                                    VOS_TRUE);
    }
    else
    {
        /* 支持GPRS, 恢复RABM, bRatChangeFlg为FALSE */
        NAS_GMM_SndRabmSysSrvChgInd(NAS_MML_NET_RAT_TYPE_GSM,
                                    VOS_FALSE,
                                    VOS_FALSE,
                                    VOS_TRUE);
    }

    return;
}

VOS_VOID GMM_CasCellS1E49(VOS_VOID *pRcvMsg)
{
    MMCGMM_GSM_SYS_INFO_IND_ST         *pSysInfo;
    VOS_UINT8                           ucLaiChgFlg;
    VOS_UINT8                           ucRaiChgFlg;

    pSysInfo    = (MMCGMM_GSM_SYS_INFO_IND_ST*)pRcvMsg;
    ucLaiChgFlg = gstGmmCasGlobalCtrl.TempMsgPara.ucLaiChgFlg;
    ucRaiChgFlg = gstGmmCasGlobalCtrl.TempMsgPara.ucRaiChgFlg;

    if (VOS_TRUE != NAS_MML_GetSimPsRegStatus())
    {                                                                           /* 原来SIM无效                              */
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* 清除出覆盖区标志                         */

        GMM_CasFsmStateChangeTo(GMM_DEREGISTERED_NO_IMSI);

        g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;

        /* 向MMC发送PS注册结果 */
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                     GMM_MMC_ACTION_RESULT_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_SIM_INVALID);
        g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;

        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvMmcSysInfoInd_DeregNmlServ:NORMAL: STATUS IS GMM_DEREGISTERED_NO_IMSI");
        return;
    }

    if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
    {
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* 清除出覆盖区标志                         */
        if(MMC_GMM_NO_FORBIDDEN != pSysInfo->ulForbiddenFlg)
        {
            Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                    /* 调用状态的公共处理                       */
        }
        else
        {
            Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);                     /* 调用状态的公共处理                       */
        }
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcSysInfoInd_DeregNmlServ:WARNING: Not allow Attach");

        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);


        /* 此时可能有缓冲的SM注册请求消息 */
        GMM_BufferMsgResume();

        return;
    }

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* 不支持GPRS                               */
        if ((GMM_DEREGISTERED_NO_CELL_AVAILABLE == g_GmmGlobalCtrl.ucState)
            && (GMM_FALSE == g_GmmGlobalCtrl.ucCvrgAreaLostFlg))
        {                                                                       /* 前一个小区也不支持GPRS                   */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcSysInfoInd_DeregNmlServ:WARNING: Not support GPRS and No cell available");
            NAS_GMM_CnfSmNotAttach(GMM_SM_CAUSE_GPRS_NOT_SUPPORT);
            NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);
            return;
        }
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* 清除出覆盖区标志                         */
        Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                        /* 调用状态的公共处理                       */


        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
        {                                                                       /* A+I                                      */

            if (GMM_FALSE == ucLaiChgFlg)
            {                                                                   /* LA没变                                   */
                NAS_GMM_SndMmLuInitiation(GMMMM_NO_TIMER_EXPIRED);          /* 通知MM进行LU                             */
            }
        }

        NAS_GMM_CnfSmNotAttach(GMM_SM_CAUSE_GPRS_NOT_SUPPORT);


        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);


    }
    else if (MMCGMM_GSM_NO_FORBIDDEN != pSysInfo->ulForbiddenFlg)
    {                                                                           /* 在forbidden列表中                        */
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* 清除出覆盖区标志                         */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */
        Gmm_ComForbiddenList(pSysInfo->ulForbiddenFlg);                         /* 调用对禁止列表的操作                     */

        NAS_GMM_CnfSmNotAttach(GMM_SM_CAUSE_FORBID_LA);

        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenFlg);

    }
    else if (GMM_TRUE == ucRaiChgFlg)
    {                                                                           /* RA改变                                   */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */
        g_GmmAttachCtrl.ucAttachAttmptCnt = 0;                                  /* Attach attempt counter清0                */
        Gmm_AttachInitiate(GMM_NULL_PROCEDURE);                                                   /* 进行Attach                               */
    }
    else
    {                                                                           /* 小区改变                                 */
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* 清除出覆盖区标志                         */
        NAS_GMM_HandleModeANOIWhenDeregister();
    }

    return;
}

VOS_VOID GMM_CasCellS4E49(VOS_VOID *pRcvMsg)
{
    MMCGMM_GSM_SYS_INFO_IND_ST *pSysInfo;
    VOS_UINT8                   ucRaiChgFlg;
    VOS_UINT8                   ucDrxLengthChgFlg;
    VOS_UINT8                   ucLaiChgFlg;

    pSysInfo          = (MMCGMM_GSM_SYS_INFO_IND_ST*)pRcvMsg;
    ucRaiChgFlg       = gstGmmCasGlobalCtrl.TempMsgPara.ucRaiChgFlg;
    ucDrxLengthChgFlg = gstGmmCasGlobalCtrl.TempMsgPara.ucDrxLengthChgFlg;
    ucLaiChgFlg       = gstGmmCasGlobalCtrl.TempMsgPara.ucLaiChgFlg;

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* 不支持GPRS                               */
        if (GMM_TRUE == ucRaiChgFlg)
        {
            if (MMCGMM_GSM_NO_FORBIDDEN == pSysInfo->ulForbiddenFlg)
            {
                g_GmmAttachCtrl.ucAttachAttmptCnt = 0;                              /* attach attempt counter清0                */
            }
        }
        Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                        /* 调用状态的公共处理                       */
        Gmm_TimerStop(GMM_TIMER_ALL);                                           /* 停所有Timer                              */


        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
        {                                                                       /* A+I                                      */

            if (GMM_FALSE == ucLaiChgFlg)
            {                                                                   /* LA没变                                   */
                NAS_GMM_SndMmLuInitiation(GMMMM_NO_TIMER_EXPIRED);          /* 通知MM进行LU                             */
            }
        }

        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);

    }
    else if (MMCGMM_GSM_NO_FORBIDDEN != pSysInfo->ulForbiddenFlg)
    {                                                                           /* 在forbidden列表中                        */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */

        Gmm_ComForbiddenList(pSysInfo->ulForbiddenFlg);                        /* 调用对禁止列表的操作                     */

        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenFlg);


    }
    else if (GMM_TRUE == ucRaiChgFlg)
    {                                                                           /* RA改变                                   */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */
        g_GmmAttachCtrl.ucAttachAttmptCnt = 0;                                  /* Attach attempt counter清0                */
        Gmm_AttachInitiate(GMM_NULL_PROCEDURE);                                                   /* 进行Attach                               */
    }
    else if (GMM_TRUE == ucDrxLengthChgFlg)
    {                                                                           /* DRX改变                                  */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */
        Gmm_AttachInitiate(GMM_NULL_PROCEDURE);                                                   /* 进行Attach                               */
    }
    else
    {
        if ((GMM_TRUE == g_GmmAttachCtrl.ucRetryFlg)
            && (GMM_TRUE == gstGmmCasGlobalCtrl.TempMsgPara.ucGsmCellChgFlg))
        {                                                                       /* 换小区需要进行attach                     */
            Gmm_TimerStop(GMM_TIMER_T3311);                                     /* 停T3311                                  */
            Gmm_TimerStop(GMM_TIMER_T3302);                                     /* 停T3302                                  */
            Gmm_AttachInitiate(GMM_NULL_PROCEDURE);                                               /* 进行Attach                               */
        }
        else
        {
            /* 网络带下来的T3302定时器时长为0时，不启T3302定时器，如果不加最后一个判断，UE会一直发起ATTACH */
            if ((GMM_TIMER_T3302_FLG
                != (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3302_FLG))
            && ((GMM_TIMER_T3311_FLG
                != (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3311_FLG)))
            && (0 != g_GmmTimerMng.aTimerInf[GMM_TIMER_T3302].ulTimerVal))
            {
                Gmm_AttachInitiate(GMM_NULL_PROCEDURE);
            }

            else
            {
                NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);

                if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
                 && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
                {
                    g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;

                    NAS_GMM_SndMmCombinedAttachInitiation();

                    NAS_GMM_SndMmCombinedAttachRejected(NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE_REG_MAX_TIMES);

                    g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;
                }

            }
        }
    }

    return;
}

VOS_VOID GMM_CasCellS8E49(VOS_VOID *pRcvMsg)
{
    MMCGMM_GSM_SYS_INFO_IND_ST *pSysInfo;
    VOS_UINT8                   ucRaiChgFlg;
    VOS_UINT8                   ucDrxLengthChgFlg;
    VOS_UINT8                   ucLaiChgFlg;

    pSysInfo          = (MMCGMM_GSM_SYS_INFO_IND_ST*)pRcvMsg;
    ucRaiChgFlg       = gstGmmCasGlobalCtrl.TempMsgPara.ucRaiChgFlg;
    ucDrxLengthChgFlg = gstGmmCasGlobalCtrl.TempMsgPara.ucDrxLengthChgFlg;
    ucLaiChgFlg       = gstGmmCasGlobalCtrl.TempMsgPara.ucLaiChgFlg;

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* 不支持GPRS                               */
        g_GmmReqCnfMng.ucCnfMask = 0;                                           /* 清除原语等待标志                         */
        Gmm_TimerStop(GMM_TIMER_ALL);                                           /* 停所有Timer                              */
        Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                        /* 调用状态的公共处理                       */
        if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
        {
            Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_GPRS_NOT_SUPPORT);    /* 通知SM GMM注册失败                       */

            g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;                             /* 清ucSmCnfFlg标志                         */
        }
        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                        /* 清当前流程                               */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd_RegInit:INFO: specific procedure ended");

        if (((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
          && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
          && (GMM_FALSE == ucLaiChgFlg))
        {                                                                       /* LA没变,并且是A+I                         */
            NAS_GMM_SndMmLuInitiation(GMMMM_NO_TIMER_EXPIRED);          /* 通知MM进行LU                             */
        }


        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);

    }
    else if (MMCGMM_GSM_NO_FORBIDDEN != pSysInfo->ulForbiddenFlg)
    {                                                                           /* 在forbidden列表中                        */
        Gmm_TimerStop(GMM_TIMER_T3310);                                         /* 停T3310                                  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */

        if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
        {                                                                       /* ATTACH过程是由SM触发的                   */
            Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_FORBID_LA);  /* 通知SM GMM注册失败                       */

            g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;                             /* 清ucSmCnfFlg标志                         */
        }
        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG ==
            (g_GmmReqCnfMng.ucCnfMask
                    & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* 等待鉴权响应                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* 停保护定时器                             */
            g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG; /* 清除原语等待标志                         */
        }
        Gmm_ComForbiddenList(pSysInfo->ulForbiddenFlg);                        /* 调用对禁止列表的操作                     */


        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenFlg);


    }
    else if (GMM_TRUE == ucRaiChgFlg)
    {                                                                           /* RA改变                                   */
        Gmm_TimerStop(GMM_TIMER_T3310);                                         /* 停T3310                                  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */

        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG ==
            (g_GmmReqCnfMng.ucCnfMask
                    & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* 等待鉴权响应                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* 停保护定时器                             */
            g_GmmReqCnfMng.ucCnfMask
                &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;                      /* 清除原语等待标志                         */
        }
        /* 当前是小区重选挂起层二的场景，需要通知层二清除缓存*/
        if (GMM_SUSPEND_LLC_FOR_CELL_RESEL == gstGmmCasGlobalCtrl.ucSuspendLlcCause)
        {
            NAS_NORMAL_LOG(WUEPS_PID_GMM,
                "GMM_CasCellS8E49: Snd ABORT REQ with CLEAR ALL to LL when LL is suspended caused by Cell Reselection");
            Gmm_SndLlcAbortReq(LL_GMM_CLEAR_DATA_TYPE_ALL);
        }

        Gmm_AttachInitiate(GMM_NULL_PROCEDURE);                                                   /* 进行Attach                               */
    }
    else if ((GMM_TRUE == ucDrxLengthChgFlg)
        || (GMM_TRUE == gstGmmCasGlobalCtrl.ucCellUpdateFlg))
    {                                                                           /* DRX改变                                  */
        if (GMM_TRUE == ucDrxLengthChgFlg)
        {
            g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg = GMM_TRUE;                      /* 流程结束之后进行RAU                      */
            g_GmmGlobalCtrl.MsgHold.ucInitiateLuFlg = GMM_FALSE;                    /* 标记GMM不能进行RAU时不需要触发MM的LU过程 */
        }
        if (GMM_TRUE == gstGmmCasGlobalCtrl.ucCellUpdateFlg)
        {
            GMM_SndLlcTriggerReq(LL_GMM_TRIG_CAUSE_CELUPD_CELL_NOTIFY);
            gstGmmCasGlobalCtrl.ucCellUpdateFlg = GMM_FALSE;
        }
    }
    else
    {
    }

    return;
}

VOS_VOID GMM_CasCellS9E49(VOS_VOID *pRcvMsg)
{
    MMCGMM_GSM_SYS_INFO_IND_ST *pSysInfo;
    VOS_UINT8                   ucRaiChgFlg;
    VOS_UINT8                   ucDrxLengthChgFlg;
    VOS_UINT8                   ucSimCsRegStatus;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulT3423StatusChgNeedRegFlg;
#endif
    NAS_MML_LAI_STRU                   *pstCsSuccLai = VOS_NULL_PTR;

    GMM_RAI_STRU                        stRai;
    VOS_UINT8                           ucCmpWithLastSucRaiChgFlg;
    VOS_UINT8                           ucCsRestrictFlg;

    pstCsSuccLai     = NAS_MML_GetCsLastSuccLai( );
    stRai.ucRac = pstCsSuccLai->ucRac;
    /* 填写LAC */
    stRai.Lai.aucLac[0] = pstCsSuccLai->aucLac[0];
    stRai.Lai.aucLac[1] = pstCsSuccLai->aucLac[1];                       /* LAC */
    /* 填写PLMN */
    stRai.Lai.PlmnId.aucMccDigit[0] =
        (VOS_UINT8)(pstCsSuccLai->stPlmnId.ulMcc & 0x0F);                           /* MCC Digit 1                              */
    stRai.Lai.PlmnId.aucMccDigit[1] =
        (VOS_UINT8)((pstCsSuccLai->stPlmnId.ulMcc >> 8) & 0x0F);                    /* MCC Digit 2                              */
    stRai.Lai.PlmnId.aucMccDigit[2] =
        (VOS_UINT8)((pstCsSuccLai->stPlmnId.ulMcc >> 16) & 0x0F);                   /* MCC Digit 3                              */
    stRai.Lai.PlmnId.aucMncDigit[0] =
        (VOS_UINT8)(pstCsSuccLai->stPlmnId.ulMnc & 0x0F);                           /* MNC Digit 1                              */
    stRai.Lai.PlmnId.aucMncDigit[1] =
        (VOS_UINT8)((pstCsSuccLai->stPlmnId.ulMnc >> 8) & 0x0F);                    /* MNC Digit 2                              */
    stRai.Lai.PlmnId.aucMncDigit[2] =
        (VOS_UINT8)((pstCsSuccLai->stPlmnId.ulMnc >> 16) & 0x0F);                   /* MNC Digit 3                              */
    stRai.Lai.PlmnId.ucMncCnt = 3;                                          /* MNC Degit count                          */
    if (GMM_PLMNID_MNC3_INVALID == stRai.Lai.PlmnId.aucMncDigit[2])
    {
        stRai.Lai.PlmnId.ucMncCnt = 2;                                      /* MNC Degit count                          */
    }
    ucCmpWithLastSucRaiChgFlg = Gmm_Compare_Rai(&stRai, &(g_GmmGlobalCtrl.SysInfo.Rai));
    ucCsRestrictFlg = NAS_MML_GetCsRestrictRegisterFlg();


    pSysInfo          = (MMCGMM_GSM_SYS_INFO_IND_ST*)pRcvMsg;
    ucRaiChgFlg       = gstGmmCasGlobalCtrl.TempMsgPara.ucRaiChgFlg;
    ucDrxLengthChgFlg = gstGmmCasGlobalCtrl.TempMsgPara.ucDrxLengthChgFlg;

#if (FEATURE_ON == FEATURE_LTE)
    ulT3423StatusChgNeedRegFlg = NAS_GMM_IsT3423StatusChangeNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                                 NAS_MML_GetTinType(), NAS_MML_GetT3423Status());
#endif

    ucSimCsRegStatus = NAS_MML_GetSimCsRegStatus();

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* 不支持GPRS                               */
        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                          /* 调用状态的公共处理                       */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */

        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);


    }
    else if (MMCGMM_GSM_NO_FORBIDDEN != pSysInfo->ulForbiddenFlg)
    {                                                                           /* 在forbidden列表中                        */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_ComForbiddenList(pSysInfo->ulForbiddenFlg);                         /* 调用对禁止列表的操作                     */

        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenFlg);


    }
    else if (GMM_TRUE == ucDrxLengthChgFlg)
    {                                                                           /* DRX改变                                  */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);               /* 进行RAU                                  */
    }
#if (FEATURE_ON == FEATURE_LTE)
    else if (VOS_TRUE == ulT3423StatusChgNeedRegFlg)
    {
        NAS_GMM_RcvLmmTimerInfoNotify_RegNmlServ();
    }
#endif
    else if ((GMM_TRUE == ucRaiChgFlg)
        || (GMM_TRUE == g_GmmGlobalCtrl.ucGprsResumeFlg))
    {                                                                           /* RA改变                                   */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);
        /*4.2.5.1.7 Substate, ATTEMPTING-TO-UPDATE-MM
        - perform routing area update indicating "combined RA/LA updating with
        IMSI attach" when the routing area of the serving cell has changed and
        the location area this cell is belonging to is not in the list of forbidden LAs.*/

        if ( (VOS_TRUE == NAS_GMM_IsAllowedCombinedAttach_GmmRegisteredAttemptingToUpdateMm())
          && (GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM == g_GmmGlobalCtrl.ucState) )
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);
        }
        else
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        }
    }
    else if (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
    {
        /*此分枝预期是G下小区重选过程中T3312超时时才会进入*/
        /* T3311不在运行时才发起RAU */
        if (VOS_FALSE == NAS_GMM_QryTimerStatus(GMM_TIMER_T3311))
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
        }
    }
    else if (VOS_TRUE == NAS_GMM_IsUeInfoChangeTriggerRau())
    {
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
    }
    else if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
          && (GMM_TRUE == g_GmmRauCtrl.ucCsSpringRauFlg)
          && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod)
          && (VOS_TRUE == ucSimCsRegStatus))
    {
        Gmm_TimerStop(GMM_TIMER_T3311);                                             /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                             /* 停T3302                                  */
        Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);         /* 执行RAU                                  */
        g_GmmRauCtrl.ucCsSpringRauFlg = GMM_FALSE;                                  /* 清除CS触发RAU的标志                      */
    }
    /* NMO1下如果LAU成功时携带的RAC与当前驻留的RAC不一样,也认为RAI改变,需要触发RAU */
    else if  ((VOS_TRUE                             == NAS_MML_GetCsAttachAllowFlg())
           && (VOS_FALSE                            == ucCmpWithLastSucRaiChgFlg)
           && (GMM_NET_MODE_I                       == g_GmmGlobalCtrl.ucNetMod)
           && (VOS_TRUE                             == ucSimCsRegStatus)
           && (VOS_FALSE                            == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
           && (VOS_FALSE                            == ucCsRestrictFlg))
    {
        Gmm_TimerStop(GMM_TIMER_T3311);                                             /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                             /* 停T3302                                  */

        Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);
    }
    else
    {
        g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;

        /* 向MMC发送PS注册结果 */
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                     GMM_MMC_ACTION_RESULT_SUCCESS,
                                     NAS_MML_REG_FAIL_CAUSE_NULL);


        if ( (VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
          && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
        {
            NAS_GMM_NotifyMmUnrealCombinedRauResult();
        }


        g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;

        /* 如果存在缓存的PDP激活请求,那么处理缓存 */
        Gmm_DealWithBuffAfterProc();
    }

    NAS_GMM_ProcSavedMmT3211ExpiredNotify();

    return;
}

VOS_VOID GMM_CasCellS10E49(VOS_VOID *pRcvMsg)
{
    MMCGMM_GSM_SYS_INFO_IND_ST         *pSysInfo;
    VOS_UINT8                           ucLaiChgFlg;
    VOS_UINT8                           ucRauFlg = GMM_TRUE;
    VOS_UINT8                           ucOldSpecProc;
    VOS_UINT8                           ucCsAttachAllow;
    VOS_UINT8                           ucCsRestrictionFlg;
     VOS_UINT8                          ucRaiChgFlg;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulT3423StatusChgNeedRegFlg;
    ulT3423StatusChgNeedRegFlg = NAS_GMM_IsT3423StatusChangeNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                                          NAS_MML_GetTinType(), NAS_MML_GetT3423Status());

#endif

    pSysInfo    = (MMCGMM_GSM_SYS_INFO_IND_ST*)pRcvMsg;
    ucLaiChgFlg = gstGmmCasGlobalCtrl.TempMsgPara.ucLaiChgFlg;

    ucRaiChgFlg = gstGmmCasGlobalCtrl.TempMsgPara.ucRaiChgFlg;

    if ( (GMM_TRUE                   == ucRaiChgFlg)
      && (GMM_REGISTERED_PLMN_SEARCH == g_GmmGlobalCtrl.ucState))
    {
        if ( (GMM_REGISTERED_NO_CELL_AVAILABLE    == g_GmmGlobalCtrl.ucPlmnSrchPreSta)
          || (GMM_REGISTERED_ATTEMPTING_TO_UPDATE == g_GmmGlobalCtrl.ucPlmnSrchPreSta))
        {
            /* 在由ATTEMPT TO UPDATE或者REGISTERED_NO_CELL_AVAILABLE状态经过
               搜网后收到系统消息，需要清除ATTEMPT COUNTER */
            if (MMCGMM_GSM_NO_FORBIDDEN == pSysInfo->ulForbiddenFlg)
            {
                g_GmmRauCtrl.ucRauAttmptCnt = 0;
            }
        }
    }

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* 不支持GPRS                               */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */
        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                          /* 调用状态的公共处理                       */

        if (VOS_TRUE == NAS_GMM_IsAModeAndNetworkI())
        {                                                                       /* A+I                                      */
            if ((GMM_FALSE == ucLaiChgFlg)
             && (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
             && (VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg))
            {                                                                   /* LA没变                                   */
                NAS_GMM_SndMmLuInitiation(GMMMM_T3312_EXPIRED);          /* 通知MM进行LU                             */
            }
        }


        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);

    }
    /* 周期RAU被用户指定搜打断，后续搜到同一个RAI网络需要停T3311定时器并发起注册 */
    else if ((VOS_TRUE == NAS_GMM_QryTimerStatus(GMM_TIMER_T3311))
          && (GMM_FALSE == ucRaiChgFlg)
          && (VOS_TRUE == pSysInfo->ulUserSrchFlg)
          && (GMM_REGISTERED_PLMN_SEARCH == g_GmmGlobalCtrl.ucState))
    {
        NAS_NORMAL_LOG(WUEPS_PID_GMM, "GMM_CasCellS10E49: User NW Srch, need to stop T3311 and send RAU Req");
        /* 用户发起的指定搜网，强制发起注册 */
        Gmm_TimerStop(GMM_TIMER_T3311);
        Gmm_TimerStop(GMM_TIMER_T3302);

        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
    }
    else if (MMCGMM_GSM_NO_FORBIDDEN != pSysInfo->ulForbiddenFlg)
    {                                                                           /* 在forbidden列表中                        */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */
        Gmm_ComForbiddenList(pSysInfo->ulForbiddenFlg);                         /* 调用对禁止列表的操作                     */

        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenFlg);

    }
#if (FEATURE_ON == FEATURE_LTE)
    else if (VOS_TRUE == ulT3423StatusChgNeedRegFlg)
    {
        if (GMM_REGISTERED_LIMITED_SERVICE == g_GmmGlobalCtrl.ucState)
        {
            NAS_GMM_RcvLmmTimerInfoNotify_RegLimitServ();
            return;
        }

        if (GMM_REGISTERED_PLMN_SEARCH == g_GmmGlobalCtrl.ucState)
        {
            NAS_GMM_RcvLmmTimerInfoNotify_RegNmlServ();
        }
    }
#endif
    else
    {                                                                           /* 小区改变                                 */
        /* g下attach成功lau #17 9088nv开启触发搜网搜hplmn失败，anycell成功回原lau被拒小区，
        gmm在gprs suspend状态搜到mmc搜网指示将g_GmmGlobalCtrl.ucPlmnSrchPreSta设置为6
        gprs suspend，后续在搜网状态收到gprs resume和系统消息多发了rau*/
        if (((GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucPlmnSrchPreSta)
          || (GMM_GPRS_SUSPENSION == g_GmmGlobalCtrl.ucPlmnSrchPreSta)
          || (GMM_REGISTERED_ATTEMPTING_TO_UPDATE == g_GmmGlobalCtrl.ucPlmnSrchPreSta)
          || (GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM == g_GmmGlobalCtrl.ucPlmnSrchPreSta)
          || ((GMM_REGISTERED_NO_CELL_AVAILABLE == g_GmmGlobalCtrl.ucPlmnSrchPreSta)
             && (NAS_MML_NET_RAT_TYPE_LTE == gstGmmSuspendCtrl.ucPreRat)))
            && (GMM_REGISTERED_PLMN_SEARCH == g_GmmGlobalCtrl.ucState))
        {
            if ((GMM_FALSE == gstGmmCasGlobalCtrl.TempMsgPara.ucRaiChgFlg)
                && (GMM_FALSE == gstGmmCasGlobalCtrl.TempMsgPara.ucDrxLengthChgFlg)
                && (GMM_FALSE == g_GmmGlobalCtrl.ucGprsResumeFlg))
            {
                ucRauFlg = GMM_FALSE;
            }
        }

        ucCsAttachAllow    = NAS_MML_GetCsAttachAllowFlg();
        ucCsRestrictionFlg = NAS_MML_GetCsRestrictRegisterFlg();

        if (GMM_TRUE == ucRauFlg)
        {
            Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
            Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */
            if ((GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
                &&(GMM_FALSE == gstGmmCasGlobalCtrl.ucSysRauFlg))
            {
                if ((VOS_TRUE == NAS_MML_GetSimCsRegStatus())
                 && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod)
                 && (VOS_FALSE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
                 && (VOS_TRUE == ucCsAttachAllow)
                 && (VOS_FALSE == ucCsRestrictionFlg))
                {
                    Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
                }
                else
                {
                    Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
                    g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
                }
            }
            else
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);               /* 进行RAU                                  */
            }
        }
        else
        {
#if (FEATURE_ON == FEATURE_LTE)
            if ((NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == NAS_MML_GetTinType())
             && (GMM_REGISTERED_PLMN_SEARCH == g_GmmGlobalCtrl.ucState)
             && (NAS_MML_NET_RAT_TYPE_LTE == gstGmmSuspendCtrl.ucPreRat))
            {
                NAS_GMM_IsrActiveRaiNoChg_InterSys();
            }
            else if ((NAS_MML_ROUTING_UPDATE_STATUS_UPDATED != NAS_MML_GetPsUpdateStatus())
                  && (GMM_REGISTERED_PLMN_SEARCH == g_GmmGlobalCtrl.ucState))
#else
            if ((NAS_MML_ROUTING_UPDATE_STATUS_UPDATED != NAS_MML_GetPsUpdateStatus())
                  && (GMM_REGISTERED_PLMN_SEARCH == g_GmmGlobalCtrl.ucState))
#endif
            {
                /* 网络带下来的T3302定时器时长为0时，不启T3302定时器，如果不加最后一个判断，UE会一直发起ATTACH */
                if ((GMM_TIMER_T3302_FLG
                    != (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3302_FLG))
                && ((GMM_TIMER_T3311_FLG
                    != (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3311_FLG)))
                && (0 != g_GmmTimerMng.aTimerInf[GMM_TIMER_T3302].ulTimerVal))
                {                                                                       /* Timer3302在运行中                        */
                    Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);               /* 进行RAU                                  */
                }
                else
                {
                    Gmm_ComStaChg(GMM_REGISTERED_ATTEMPTING_TO_UPDATE);
                    NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);
                }

            }
            else if (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
                g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
            }

            /*3G重选或者搜网到2G网络，两者RAI完全相同，而且UE之前在3G发
              送过信令或用户数据，此时在2G做PS业务时没有进行RAU，导致业
              务失败，修改方案是立即进行RAU(与协议不完全一致，经CCB裁决)*/
            else if (gstGmmCasGlobalCtrl.ucLastDataSender !=
                        NAS_MML_GetCurrNetRatType())
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
            }
            /* attahc或rau中携带的ms radio capability是否支持L能力与接入层上报的ms radio capabitlity是否支持L能力不一致需要触发Rau*/
            else if (VOS_TRUE == NAS_GMM_IsUeInfoChangeTriggerRau())
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
            }

            else
            {
                if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
                 && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod)
                 && (VOS_TRUE == ucCsAttachAllow))
                {
                    NAS_GMM_HandleModeANOIWhenRAInotChange();
                }
                else
                {
                    Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);
                    g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;
                    ucOldSpecProc = g_GmmGlobalCtrl.ucSpecProc;
                    g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;


                    /* 向MMC发送PS注册结果 */
                    NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                                 GMM_MMC_ACTION_RESULT_SUCCESS,
                                                 NAS_MML_REG_FAIL_CAUSE_NULL);

                    g_GmmGlobalCtrl.ucSpecProc = ucOldSpecProc;
                    g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;
                }
            }



            if (GMM_ROUTING_AREA_UPDATING_INITIATED != g_GmmGlobalCtrl.ucState)
            {
                if (GMM_SERVICE_REQ_PAGING == g_GmmGlobalCtrl.enServReq)
                {
                    if (GMM_FALSE == gstGmmCasGlobalCtrl.ucTlliAssignFlg)
                    {
                        GMM_UpdateSysTlli(GMM_LOCAL_TLLI);
                        GMM_AssignSysTlli();
                    }

                    Gmm_TimerStop(GMM_TIMER_T3314);

#if (FEATURE_LTE == FEATURE_ON)
                    if (GMM_TIMER_T3312_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
                    {
                        NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
                    }
#endif

                    Gmm_TimerStop(GMM_TIMER_T3312);

                    if ( 0xffffffff == gstGmmCasGlobalCtrl.ulReadyTimerValue )
                    {
                        gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_READY;
#if (FEATURE_LTE == FEATURE_ON)
                    if (NAS_GMM_TIMER_T3323_FLG == (NAS_GMM_TIMER_T3323_FLG & g_GmmTimerMng.ulTimerRunMask))
                    {
                        Gmm_TimerStop(GMM_TIMER_T3323);
                    }
#endif
                    }
                    else if ( 0 == gstGmmCasGlobalCtrl.ulReadyTimerValue )
                    {
                        gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_STANDBY;
                        Gmm_TimerStart(GMM_TIMER_T3312);
                    }
                    else
                    {
                        gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_READY;
#if (FEATURE_LTE == FEATURE_ON)
                        if (NAS_GMM_TIMER_T3323_FLG == (NAS_GMM_TIMER_T3323_FLG & g_GmmTimerMng.ulTimerRunMask))
                        {
                            Gmm_TimerStop(GMM_TIMER_T3323);
                        }
#endif
                        g_GmmTimerMng.aTimerInf[GMM_TIMER_T3314].ulTimerVal
                            = gstGmmCasGlobalCtrl.ulReadyTimerValue;
                        g_GmmTimerMng.ulTimerValMask |= GMM_TIMER_T3314_FLG;
                        Gmm_TimerStart(GMM_TIMER_T3314);
                    }
                    NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);

                    GMM_SndLlcTriggerReq(LL_GMM_TRIG_CAUSE_PAG_RSP);
                }
                else if (GMM_SERVICE_REQ_PDPACT == g_GmmGlobalCtrl.enServReq)
                {
                    if (GMM_FALSE == gstGmmCasGlobalCtrl.ucTlliAssignFlg)
                    {
                        GMM_UpdateSysTlli(GMM_LOCAL_TLLI);
                        GMM_AssignSysTlli();
                    }

                    Gmm_DealWithBuffAfterProc();
                }
                else
                {
                    if (GMM_FALSE == gstGmmCasGlobalCtrl.ucTlliAssignFlg)
                    {
                        GMM_UpdateSysTlli(GMM_LOCAL_TLLI);
                        GMM_AssignSysTlli();
                    }
                }
            }
        }
    }


    g_GmmGlobalCtrl.enServReq = GMM_SERVICE_REQ_NONE;

    return;
}

VOS_VOID GMM_CasCellS11E49(VOS_VOID *pRcvMsg)
{
    MMCGMM_GSM_SYS_INFO_IND_ST         *pSysInfo;
    VOS_UINT8                           ucRaiChgFlg;
    VOS_UINT8                           ucDrxLengthChgFlg;
    VOS_UINT8                           ucLaiChgFlg;

    pSysInfo          = (MMCGMM_GSM_SYS_INFO_IND_ST*)pRcvMsg;
    ucRaiChgFlg       = gstGmmCasGlobalCtrl.TempMsgPara.ucRaiChgFlg;
    ucDrxLengthChgFlg = gstGmmCasGlobalCtrl.TempMsgPara.ucDrxLengthChgFlg;
    ucLaiChgFlg       = gstGmmCasGlobalCtrl.TempMsgPara.ucLaiChgFlg;

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* 不支持GPRS                               */
        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                          /* 调用状态的公共处理                       */
        Gmm_TimerStop(GMM_TIMER_ALL);                                           /* 停所有Timer                              */
        if (GMM_TRUE == ucRaiChgFlg)
        {
            if (MMCGMM_GSM_NO_FORBIDDEN == pSysInfo->ulForbiddenFlg)
            {
                g_GmmRauCtrl.ucRauAttmptCnt = 0;                                    /* RAU attempt counter清0                   */
            }
        }

        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
        {                                                                       /* A+I                                      */
            if (GMM_FALSE == ucLaiChgFlg)
            {                                                                   /* LA没变                                   */
                NAS_GMM_SndMmLuInitiation(GMMMM_NO_TIMER_EXPIRED);          /* 通知MM进行LU                             */
            }
        }

        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);



    }

    else if (MMCGMM_GSM_NO_FORBIDDEN != pSysInfo->ulForbiddenFlg)
    {                                                                           /* 在forbidden列表中                        */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */

        Gmm_ComForbiddenList(pSysInfo->ulForbiddenFlg);                         /* 调用对禁止列表的操作                     */

        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenFlg);


    }
    else if (GMM_TRUE == ucRaiChgFlg)
    {                                                                           /* RA改变                                   */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */
        g_GmmRauCtrl.ucRauAttmptCnt = 0;                                        /* RAU attempt counter清0                   */
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);               /* 进行RAU                                  */
    }
    else if (GMM_TRUE == ucDrxLengthChgFlg)
    {                                                                           /* DRX改变                                  */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);               /* 进行RAU                                  */
    }
    else
    {
        if ((GMM_TRUE == g_GmmRauCtrl.ucRetryFlg)
         && (GMM_TRUE == gstGmmCasGlobalCtrl.TempMsgPara.ucGsmCellChgFlg))
        {                                                                       /* 换小区需要进行RAU                        */
            Gmm_TimerStop(GMM_TIMER_T3311);                                     /* 停T3311                                  */
            Gmm_TimerStop(GMM_TIMER_T3302);                                     /* 停T3302                                  */
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);           /* 进行RAU                                  */
        }

        else
        {
            NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);

            if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
             && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
            {
                g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;

                NAS_GMM_SndMmCombinedRauInitiation();
                NAS_GMM_SndMmCombinedRauRejected(NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE_REG_MAX_TIMES);
                g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;
            }

        }
    }

    return;
}


VOS_VOID NAS_GMM_ProcessSmMsgInBuff()
{
    if(GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
    {
        if(GMM_SERVICE_REQ_PDPACT == g_GmmGlobalCtrl.enServReq)
        {
            Gmm_DealWithBuffAfterProc();
            g_GmmGlobalCtrl.enServReq = GMM_SERVICE_REQ_NONE;
        }
    }
}


VOS_VOID NAS_GMM_EnterCoveryRaiNoChg_BeforeT3312Exp(VOS_VOID)
{
    VOS_UINT8                           ucCsRestrictionFlg;
    VOS_UINT8                           ucCsAttachAllow;
    VOS_UINT8                           ucSimCsRegStatus;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;

    enRatType        = NAS_MML_GetCurrNetRatType();
    ucCsAttachAllow  = NAS_MML_GetCsAttachAllowFlg();
    ucSimCsRegStatus = NAS_MML_GetSimCsRegStatus();
    ucCsRestrictionFlg  =   NAS_MML_GetCsRestrictRegisterFlg();

    if ( (NAS_MML_ROUTING_UPDATE_STATUS_UPDATED == NAS_MML_GetPsUpdateStatus())
       && ( gstGmmCasGlobalCtrl.ucLastDataSender == enRatType ))
    {
        g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;            /* 设置假流程标志                           */

        if ((VOS_TRUE != NAS_MML_GetCsAttachAllowFlg())
         || (GMM_NET_MODE_I != g_GmmGlobalCtrl.ucNetMod)
         || (VOS_TRUE == ucCsRestrictionFlg))
        {                                                               /* 非A+I                                    */
            Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);               /* 调用状态的公共处理                       */
#if (FEATURE_LTE == FEATURE_ON)
            if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
            {
                NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
            }

            /* 如果之前出服务区，T3312超时，启动了T3323,后重进服务区，需要停止T3323*/
            Gmm_TimerStop(GMM_TIMER_T3323);
#endif

            Gmm_TimerStart(GMM_TIMER_T3312);                            /* 启动T3312                                */
            g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd_RegNoCell:INFO: normal RAU procedure started");


            /* 向MMC发送PS注册结果 */
            NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                         GMM_MMC_ACTION_RESULT_SUCCESS,
                                         NAS_MML_REG_FAIL_CAUSE_NULL);

            g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;
        }
        else
        {                                                               /* A+I                                      */
            if (  (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == NAS_MML_GetCsUpdateStatus())
                &&(VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg))
            {                                                           /* 更新状态是U1                             */
                Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);           /* 调用状态的公共处理                       */
#if (FEATURE_LTE == FEATURE_ON)
                if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
                {
                    NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
                }

                /* 如果之前出服务区，T3312超时，启动了T3323,后重进服务区，需要停止T3323*/
                Gmm_TimerStop(GMM_TIMER_T3323);
#endif

                Gmm_TimerStart(GMM_TIMER_T3312);                        /* 启动T3312                                */
                if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
                {                                                       /* 需要给SM回EST_CNF                        */
                    g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;

                    Gmm_SndSmEstablishCnf(GMM_SM_EST_SUCCESS, GMM_SM_CAUSE_SUCCESS);    /* 向SM回建立成功的响应                     */
                }
                if (VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
                {                                                       /* CS域允许注册                             */
                    NAS_GMM_SndMmCombinedRauInitiation();
                    NAS_GMM_SndMmCombinedRauAccept(GMMMM_RAU_RESULT_COMBINED,
                                                   NAS_MML_REG_FAIL_CAUSE_NULL,
                                                   VOS_NULL_PTR,
                                                   VOS_NULL_PTR);            /* 发送 MMCGMM_COMBINED_RAU_ACCEPTED        */
                }


                /* 向MMC发送PS注册结果 */
                NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                             GMM_MMC_ACTION_RESULT_SUCCESS,
                                             NAS_MML_REG_FAIL_CAUSE_NULL);

            }
            else
            {                                                           /* 更新状态不是U1                           */
                if ((VOS_FALSE == ucCsAttachAllow)
                 || (VOS_TRUE != ucSimCsRegStatus))
                {                                                       /* sim无效或者CS域不允许注册                */
                    Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);       /* 调用状态的公共处理                       */
#if (FEATURE_LTE == FEATURE_ON)
                    if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
                    {
                        NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
                    }

                    /* 如果之前出服务区，T3312超时，启动了T3323,后重进服务区，需要停止T3323*/
                    Gmm_TimerStop(GMM_TIMER_T3323);
#endif

                    Gmm_TimerStart(GMM_TIMER_T3312);                    /* 启动T3312                                */
                    if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
                    {                                                   /* 需要给SM回EST_CNF                        */
                        g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;
                        Gmm_SndSmEstablishCnf(GMM_SM_EST_SUCCESS, GMM_SM_CAUSE_SUCCESS);    /* 向SM回建立成功的响应                     */
                    }
                    g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;
                    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd_RegNoCell:INFO: normal RAU procedure started");


                    /* 向MMC发送PS注册结果 */
                    NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                                 GMM_MMC_ACTION_RESULT_SUCCESS,
                                                 NAS_MML_REG_FAIL_CAUSE_NULL);

                    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;
                }
                else
                {
                    Gmm_RoutingAreaUpdateInitiate(
                                        GMM_UPDATING_TYPE_INVALID);     /* 调用RAU                                  */
                }
            }
        }
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd_RegNoCell:INFO: specific procedure ended");
        g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;              /* 设置真流程标志                           */
    }
    else
    {                                                                   /* 更新状态不是GU1                          */
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);       /* 调用RAU                                  */
    }

    NAS_GMM_ProcessSmMsgInBuff();
}


VOS_VOID NAS_GMM_EnterCoveryRaiNoChg_AfterT3312Exp(VOS_VOID)
{
    g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                      /* 清除出覆盖区标志                         */

    if ((VOS_TRUE != NAS_MML_GetCsAttachAllowFlg())
     || (GMM_NET_MODE_I != g_GmmGlobalCtrl.ucNetMod))
    {                                                                   /* 非A+I                                    */
        Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
    }
    else
    {                                                                   /* A+I                                      */
        Gmm_RoutingAreaUpdateInitiate(
                            GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);       /* 调用RAU过程combined RAU with IMSI attach */
    }
}


VOS_VOID NAS_GMM_EnterCovery(VOS_VOID *pRcvMsg)
{
    MMCGMM_GSM_SYS_INFO_IND_ST         *pSysInfo;
    VOS_UINT8                           ucRaiChgFlg;
    VOS_UINT8                           ucDrxLengthChgFlg;
    VOS_UINT8                           ucLaiChgFlg;
     NAS_MML_RAI_STRU                       *pstLastSuccRai;
     GMM_RAI_STRU                            stGmmRai;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulT3423StatusChgNeedRegFlg;

    ulT3423StatusChgNeedRegFlg = NAS_GMM_IsT3423StatusChangeNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                                                 NAS_MML_GetTinType(), NAS_MML_GetT3423Status());
#endif



    pstLastSuccRai    = NAS_MML_GetPsLastSuccRai();
    NAS_GMM_ConvertPlmnIdToGmmFormat(&(pstLastSuccRai->stLai.stPlmnId), &stGmmRai.Lai.PlmnId);

    stGmmRai.ucRac          = pstLastSuccRai->ucRac;
    stGmmRai.Lai.aucLac[0]  = pstLastSuccRai->stLai.aucLac[0];
    stGmmRai.Lai.aucLac[1]  = pstLastSuccRai->stLai.aucLac[1];

    pSysInfo          = (MMCGMM_GSM_SYS_INFO_IND_ST*)pRcvMsg;
    ucRaiChgFlg       = gstGmmCasGlobalCtrl.TempMsgPara.ucRaiChgFlg;
    ucDrxLengthChgFlg = gstGmmCasGlobalCtrl.TempMsgPara.ucDrxLengthChgFlg;
    ucLaiChgFlg       = gstGmmCasGlobalCtrl.TempMsgPara.ucLaiChgFlg;

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* 不支持GPRS                               */
        if (GMM_TRUE == g_GmmGlobalCtrl.ucCvrgAreaLostFlg)
        {
            g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;

            if (GMM_FALSE == ucLaiChgFlg)
            {
                if (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
                {
                    NAS_GMM_SndMmLuInitiation(GMMMM_T3312_EXPIRED);             /* 通知MM进行LU                             */
                }
            }
        }

        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);


        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);
    }
    else if (MMCGMM_GSM_NO_FORBIDDEN != pSysInfo->ulForbiddenFlg)
    {                                                                           /* 在forbidden列表中                        */
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* 清除出覆盖区标志                         */
        Gmm_ComForbiddenList(pSysInfo->ulForbiddenFlg);                        /* 调用对禁止列表的操作                     */

        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenFlg);


    }
#if (FEATURE_ON == FEATURE_LTE)
    else if (VOS_TRUE == ulT3423StatusChgNeedRegFlg)
    {
        NAS_GMM_RcvLmmTimerInfoNotify_RegNmlServ();
    }

    else if (VOS_TRUE == NAS_GMM_IsUeInfoChangeTriggerRau())
    {
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
    }

#endif
    else if ((GMM_TRUE == Gmm_Compare_Rai(&g_GmmGlobalCtrl.SysInfo.Rai, &stGmmRai))
          && (GMM_FALSE == ucRaiChgFlg) && (GMM_FALSE == ucDrxLengthChgFlg)
          && (GMM_FALSE == g_GmmGlobalCtrl.ucGprsResumeFlg))
    {                                                                           /* 回到原来的RA并且DRX参数没有改变          */
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* 清除出覆盖区标志                         */

#if (FEATURE_ON == FEATURE_LTE)
        if ((NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == NAS_MML_GetTinType())
         && (GMM_REGISTERED_NO_CELL_AVAILABLE == g_GmmGlobalCtrl.ucState)
         && (NAS_MML_NET_RAT_TYPE_LTE == gstGmmSuspendCtrl.ucPreRat))
        {
            NAS_GMM_IsrActiveRaiNoChg_InterSys();
            return;
        }
#endif

        if (GMM_FALSE == g_GmmRauCtrl.ucT3312ExpiredFlg)
        {                                                                       /* 出覆盖区时T3312未溢出                    */
            NAS_GMM_EnterCoveryRaiNoChg_BeforeT3312Exp();
        }
        else
        {                                                                       /* 出覆盖区时T3312溢出                      */
            NAS_GMM_EnterCoveryRaiNoChg_AfterT3312Exp();
        }
    }
    else
    {                                                                           /* RA改变或者DRX参数变化                    */
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* 清除出覆盖区标志                         */
        g_GmmRauCtrl.ucT3312ExpiredFlg    = GMM_FALSE;                          /* 清除T3312溢出标记                        */

        if (VOS_FALSE == NAS_GMM_IsAModeAndNetworkI())
        {                                                                       /* 非A+I                                    */
            Gmm_RoutingAreaUpdateInitiate(GMM_RA_UPDATING);
        }
        else
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        }
    }

    return;
}

VOS_VOID GMM_CasCellS18E49(VOS_VOID *pRcvMsg)
{
    MMCGMM_GSM_SYS_INFO_IND_ST *pSysInfo;
    VOS_UINT8                   ucRaiChgFlg;
    VOS_UINT8                   ucDrxLengthChgFlg;

    pSysInfo          = (MMCGMM_GSM_SYS_INFO_IND_ST*)pRcvMsg;
    ucRaiChgFlg       = gstGmmCasGlobalCtrl.TempMsgPara.ucRaiChgFlg;
    ucDrxLengthChgFlg = gstGmmCasGlobalCtrl.TempMsgPara.ucDrxLengthChgFlg;

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* 不支持GPRS                               */
        Gmm_TimerStop(GMM_TIMER_T3321);                                         /* 停T3321                                  */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* 停保护定时器                             */

        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */

        g_GmmReqCnfMng.ucCnfMask = 0;                                           /* 清除原语等待标志                         */
        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                          /* 调用状态的公共处理                       */
        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                        /* 清当前流程                               */

        /* 判断等待标志是否存在，如果存在则向MMC,MM发送DETACH信息 */
        if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
        {
            /* 本地detach后,需要迁移到对应的状态 */
            if (GMM_WAIT_PS_DETACH == (g_GmmGlobalCtrl.stDetachInfo.enDetachType & GMM_WAIT_PS_DETACH))
            {
                NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);

                Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);
            }
            NAS_GMM_SndMmcMmDetachInfo();
        }

        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd_DeregInit:INFO: specific procedure ended");

        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);


    }
    else if (MMCGMM_GSM_NO_FORBIDDEN != pSysInfo->ulForbiddenFlg)
    {                                                                           /* 在forbidden列表中                        */
        Gmm_TimerStop(GMM_TIMER_T3321);                                         /* 停T3321                                  */

        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */

        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG ==
            (g_GmmReqCnfMng.ucCnfMask
                        & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* 等待鉴权响应                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* 停保护定时器                             */
            g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG; /* 清除原语等待标志                         */
        }
        Gmm_ComForbiddenList(pSysInfo->ulForbiddenFlg);                         /* 调用对禁止列表的操作                     */

        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenFlg);


    }
    else if ((GMM_TRUE == ucRaiChgFlg) || (GMM_TRUE == ucDrxLengthChgFlg))
    {                                                                           /* RA改变或者DRX改变                        */
        Gmm_TimerStop(GMM_TIMER_T3321);                                         /* 停T3321                                  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */

        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask
            & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* 等待鉴权响应                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* 停保护定时器                             */
            g_GmmReqCnfMng.ucCnfMask
                &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;                      /* 清除原语等待标志                         */
        }
        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

        g_GmmGlobalCtrl.ucSpecProcHold = g_GmmGlobalCtrl.ucSpecProc;
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);               /* 进行RAU                                  */
    }
    else if (GMM_TRUE == gstGmmCasGlobalCtrl.ucCellUpdateFlg)
    {
        GMM_SndLlcTriggerReq(LL_GMM_TRIG_CAUSE_CELUPD_CELL_NOTIFY);
        gstGmmCasGlobalCtrl.ucCellUpdateFlg = GMM_FALSE;
    }
    else
    {
    }
    return;
}

VOS_VOID GMM_CasCellS19E49(VOS_VOID *pRcvMsg)
{
    MMCGMM_GSM_SYS_INFO_IND_ST *pSysInfo;
    VOS_UINT8                   ucRaiChgFlg;
    VOS_UINT8                   ucDrxLengthChgFlg;
    VOS_UINT8                   ucLaiChgFlg;

    pSysInfo          = (MMCGMM_GSM_SYS_INFO_IND_ST*)pRcvMsg;
    ucRaiChgFlg       = gstGmmCasGlobalCtrl.TempMsgPara.ucRaiChgFlg;
    ucDrxLengthChgFlg = gstGmmCasGlobalCtrl.TempMsgPara.ucDrxLengthChgFlg;
    ucLaiChgFlg       = gstGmmCasGlobalCtrl.TempMsgPara.ucLaiChgFlg;

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* 不支持GPRS                               */
        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                          /* 调用状态的公共处理                       */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* 停保护定时器                             */
        g_GmmReqCnfMng.ucCnfMask = 0;                                           /* 清除原语等待标志                         */
        Gmm_TimerStop(GMM_TIMER_T3330);                                         /* 停T3330                                  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */

        if (GMM_FALSE == ucLaiChgFlg)
        {
            /* 当前驻留的位置区与之前驻留的位置区LAI没改变,并且在网络模式I,并且T3312超时 */
            if ((VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
             && (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg))
            {
                NAS_GMM_SndMmLuInitiation(GMMMM_T3312_EXPIRED);                    /* 通知MM进行LU                             */
            }
            else if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
                  && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
            {                                                                   /* LA没变,并且是A+I                         */
                NAS_GMM_SndMmLuInitiation(GMMMM_NO_TIMER_EXPIRED);              /* 通知MM进行LU                             */
            }
            else
            {
            }
        }


        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);


    }
    else if (MMCGMM_GSM_NO_FORBIDDEN != pSysInfo->ulForbiddenFlg)
    {                                                                           /* 在forbidden列表中                        */
        Gmm_TimerStop(GMM_TIMER_T3330);                                         /* 停T3330                                  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */

        if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
        {                                                                       /* RAU过程是由SM触发的                      */
            Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_FORBID_LA);  /* 通知SM GMM注册失败                       */

            g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;                             /* 清ucSmCnfFlg标志                         */
        }
        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG ==
            (g_GmmReqCnfMng.ucCnfMask
                        & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* 等待鉴权响应                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* 停保护定时器                             */
            g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG; /* 清除原语等待标志                         */
        }
        Gmm_ComForbiddenList(pSysInfo->ulForbiddenFlg);                        /* 调用对禁止列表的操作                     */

        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenFlg);


    }
    else if (GMM_TRUE == ucRaiChgFlg)
    {                                                                           /* RA改变                                   */
        NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_NOT_UPDATED);                                    /* 更新状态设为GU2                          */
        if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* 更新SIM卡信息                            */
        }
        else
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
        }

        if (GMM_TRUE == g_GmmGlobalCtrl.ucGprsResumeFlg)
        {
            g_GmmRauCtrl.ucT3312ExpiredFlg = GMM_FALSE;
            g_GmmRauCtrl.ucPeriodicRauFlg = GMM_FALSE;

            GMM_LOG_WARN("GMM_CasCellS19E49 warning:Not Start RAU in GMM_RAU_NORMAL_GPRS_RESUME.");
        }
        Gmm_TimerStop(GMM_TIMER_T3330);                                         /* 停T3330                                  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */

        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG ==
            (g_GmmReqCnfMng.ucCnfMask
                        & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* 等待鉴权响应                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* 停保护定时器                             */
            g_GmmReqCnfMng.ucCnfMask
                &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;                      /* 清除原语等待标志                         */
        }
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);               /* 进行RAU                                  */
    }
    else if (GMM_TRUE == ucDrxLengthChgFlg)
    {                                                                           /* DRX改变                                  */
        g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg = GMM_TRUE;                      /* 流程结束之后进行RAU                      */
        g_GmmGlobalCtrl.MsgHold.ucInitiateLuFlg = GMM_TRUE;                     /* 标记GMM不能进行RAU时要触发MM的LU过程     */
    }
    else
    {
    }

    return;
}

VOS_VOID NAS_GMM_CheckBufferDetach(VOS_VOID)
{
	VOS_VOID                           *pMsg;
	MMCGMM_DETACH_REQ_STRU             *pstDetach;

	if (GMM_MSG_HOLD_FOR_DETACH
		== (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_DETACH))
	{                                                                           /* 如果有保留的SR原语                       */
		g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_DETACH;      /* 清除缓存标志                             */

		pMsg = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach;

		/*构造分发消息*/
		pstDetach = (MMCGMM_DETACH_REQ_STRU *)Gmm_MemMalloc(sizeof(MMCGMM_DETACH_REQ_STRU));

		if (VOS_NULL_PTR == pstDetach)
		{
			Gmm_MemFree(pMsg);
			PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR,
				"Gmm_DealWithBuffAfterProc:ERROR: Gmm_MemMalloc fail !! ");
			return;
		}

		Gmm_MemCpy(pstDetach, pMsg, sizeof(MMCGMM_DETACH_REQ_STRU));

		/*释放保存的detach消息*/
		Gmm_MemFree(pMsg);

		/*分发缓存的detach消息*/
		Gmm_MsgDistribute((VOS_VOID *)(pstDetach));

		/*释放新申请的内存*/
		Gmm_MemFree(pstDetach);
	}
}

VOS_VOID GMM_RcvGasSysInfoInd_SuspWaitSys(VOS_VOID *pRcvMsg)
{
    MMCGMM_GSM_SYS_INFO_IND_ST         *pSysInfo;
    VOS_UINT8                           ucRaiChgFlg;
    VOS_UINT8                           ucLaiChgFlg;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulT3423StatuChgNeedRegFlg;
    ulT3423StatuChgNeedRegFlg = NAS_GMM_IsT3423StatusChangeNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                                    NAS_MML_GetTinType(), NAS_MML_GetT3423Status());
#endif

    pSysInfo    = (MMCGMM_GSM_SYS_INFO_IND_ST*)pRcvMsg;
    ucRaiChgFlg = gstGmmCasGlobalCtrl.TempMsgPara.ucRaiChgFlg;
    ucLaiChgFlg = gstGmmCasGlobalCtrl.TempMsgPara.ucLaiChgFlg;

    Gmm_TimerStop(GMM_TIMER_SUSPENDED);

    GMM_ResumeTimer(GMM_TIMER_RESUME);

    if (VOS_TRUE != NAS_MML_GetSimPsRegStatus())
    {                                                                           /* 原来SIM无效                              */
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* 清除出覆盖区标志                         */

        GMM_CasFsmStateChangeTo(GMM_DEREGISTERED_NO_IMSI);

        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SIM_INVALID);

        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "GMM_RcvGasSysInfoInd_SuspWaitSys:NORMAL: STATUS IS GMM_DEREGISTERED_NO_IMSI");
        return;
    }
    if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
    {
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* 清除出覆盖区标志                         */
        Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);                         /* 调用状态的公共处理                       */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "GMM_RcvGasSysInfoInd_SuspWaitSys:WARNING: Not allow Attach");

        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);


        return;
    }
    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* 不支持GPRS                               */
        GMM_LOG_INFO("GMM_RcvGasSysInfoInd_SuspWaitSys:the cell not support GPRS.");
        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                          /* 调用状态的公共处理                       */
        Gmm_TimerStop(GMM_REGSTER_AND_SHUTDOWN_TIMER);                                           /* 停所有Timer                              */

        if (GMM_TRUE == ucRaiChgFlg)
        {
            if (MMCGMM_GSM_NO_FORBIDDEN == pSysInfo->ulForbiddenFlg)
            {
                g_GmmRauCtrl.ucRauAttmptCnt = 0;                                    /* RAU attempt counter清0                   */
            }
        }

        if (VOS_TRUE == NAS_GMM_IsAModeAndNetworkI())
        {                                                                       /* A+I                                      */
            if ((GMM_FALSE == ucLaiChgFlg)
             && (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
             && (VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg))
            {                                                                   /* LA没变                                   */
                NAS_GMM_SndMmLuInitiation(GMMMM_T3312_EXPIRED);                 /* 通知MM进行LU                             */
            }
        }

        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);

    }
    else if (MMCGMM_GSM_NO_FORBIDDEN != pSysInfo->ulForbiddenFlg)
    {                                                                           /* 在forbidden列表中                        */
        g_GmmRauCtrl.ucNpduCnt = 0x0;
        GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_HANDOVER, GMM_RABM_RAU_FAILURE);

        Gmm_ComForbiddenList(pSysInfo->ulForbiddenFlg);                        /* 调用对禁止列表的操作                     */

        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenFlg);


    }
    else if (GMM_TRUE == ucRaiChgFlg)
    {                                                                           /* RA改变                                   */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */

        Gmm_TimerStop(GMM_TIMER_T3330);
        Gmm_TimerStop(GMM_TIMER_T3318);
        Gmm_TimerStop(GMM_TIMER_T3320);
        g_GmmRauCtrl.ucRauAttmptCnt = 0;                                        /* RAU attempt counter清0                   */
        gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_INTERSYSTEM;


        if (GMM_NETMODE_CHG_NULL == gstGmmSuspendCtrl.ucNetModeChange)
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);           /* 进行RAU                                  */
        }
        else
        {
            GMM_ProcedureByNetMode(gstGmmSuspendCtrl.ucNetModeChange);
        }
    }
    else if (RR_REL_CAUSE_DIRECTED_SINGNALING_CONNECTION_RE_ESTABLISHMENT
        == g_GmmGlobalCtrl.ucRelCause)
    {
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_RoutingAreaUpdateInitiateWithReEstRR();
    }
    else
    {
        if ((GMM_IU_PMM_CONNECTED == gstGmmSuspendCtrl.ucPreSrvState)
         && (NAS_MML_NET_RAT_TYPE_LTE != gstGmmSuspendCtrl.ucPreRat))
        {
            GMM_LOG_INFO("GMM_RcvGasSysInfoInd_SuspWaitSys:Need immediately RAU.");
#if 0
            GMM_SndRabmGprsInfoInd(GMM_RABM_GPRS_SUPPORTED, GMM_RABM_PROC_HANDOVER,
                                   GMM_RABM_IMMEDIATELY_RAU);
#endif
            Gmm_TimerStop(GMM_TIMER_T3311);                                     /* 停T3311                                  */
            Gmm_TimerStop(GMM_TIMER_T3302);                                     /* 停T3302                                  */
            Gmm_TimerStop(GMM_TIMER_T3330);
            Gmm_TimerStop(GMM_TIMER_T3318);
            Gmm_TimerStop(GMM_TIMER_T3320);
            g_GmmRauCtrl.ucRauAttmptCnt = 0;                                    /* RAU attempt counter清0                   */
            gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_INTERSYSTEM;
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);           /* 进行RAU                                  */

        }
        else if ( (gstGmmCasGlobalCtrl.ucLastDataSender !=
                            NAS_MML_GetCurrNetRatType())
#if (FEATURE_ON == FEATURE_LTE)
                      && (gstGmmCasGlobalCtrl.ucLastDataSender != NAS_MML_NET_RAT_TYPE_LTE)
#endif
                )
        {
            GMM_LOG_INFO("GMM_RcvGasSysInfoInd_SuspWaitSys:Need selective RAU.");

            Gmm_TimerStop(GMM_TIMER_T3311);                                     /* 停T3311                                  */
            Gmm_TimerStop(GMM_TIMER_T3302);                                     /* 停T3302                                  */
            Gmm_TimerStop(GMM_TIMER_T3330);
            Gmm_TimerStop(GMM_TIMER_T3318);
            Gmm_TimerStop(GMM_TIMER_T3320);

            gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_INTERSYSTEM;
            if (GMM_T3312_TIMEOUT == gstGmmSuspendCtrl.ucT3312State)
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
                gstGmmSuspendCtrl.ucT3312State = GMM_T3312_NOT_TIMEOUT;
            }
            else
            {
                /* 无条件进行一次RAU */
                Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
            }
        }
#if (FEATURE_ON == FEATURE_LTE)
        else if (VOS_TRUE == ulT3423StatuChgNeedRegFlg)
        {
            NAS_GMM_RcvLmmTimerInfoNotify_RegNmlServ();
        }
        else if (VOS_TRUE == NAS_GMM_IsUeInfoChangeTriggerRau())
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        }
#endif
        else
        {
            GMM_LOG_INFO("GMM_RcvGasSysInfoInd_SuspWaitSys:Need not RAU.");
            g_GmmRauCtrl.ucNpduCnt = 0x0;
            GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_HANDOVER, GMM_RABM_RAU_SUCCESS);

            /* W->G, W下接入禁止或者不支持GPRS，到G下后，如果RAC不改变，
               重新调用下GMM_REGISTERED_UPDATE_NEEDED状态下的系统消息处理函数 */
            if ((GMM_REGISTERED_UPDATE_NEEDED == gstGmmSuspendCtrl.ucPreState)
             || (GMM_REGISTERED_LIMITED_SERVICE== gstGmmSuspendCtrl.ucPreState))
            {
                NAS_GMM_EnterCovery(pRcvMsg);
            }
            else
            {
                Gmm_ComStaChg(gstGmmSuspendCtrl.ucPreState);
                GMM_ResumeSuccess();
                if (GMM_TRUE == g_GmmGlobalCtrl.ucFollowOnFlg)
                {
                    g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;
                    NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

                    Gmm_RoutingAreaUpdateHandleFollowOn();
                }
                else
                {
                    if (GMM_FALSE == gstGmmCasGlobalCtrl.ucTlliAssignFlg)
                    {
                        GMM_UpdateSysTlli(GMM_LOCAL_TLLI);
                        GMM_AssignSysTlli();
                    }
                }

#if   (FEATURE_ON == FEATURE_LTE)
                /* L重选到G,路由区未改变，ISR激活，无需做RAU时需要更新状态，
                  否则为register no cell available，后续无法做业务 */
                if ((NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == NAS_MML_GetTinType())
                 && (NAS_MML_NET_RAT_TYPE_LTE == gstGmmSuspendCtrl.ucPreRat))

                {
                    NAS_GMM_IsrActiveRaiNoChg_InterSys();
                }
#endif
            }
        }
    }

    if ( GMM_ROUTING_AREA_UPDATING_INITIATED != g_GmmGlobalCtrl.ucState)
	{
		NAS_GMM_CheckBufferDetach();
	}

    return;
}

VOS_VOID GMM_RcvLlcDataInd(VOS_VOID *pRcvMsg)
{
    LL_NAS_UNITDATA_IND_MSG *pDataInd;
    RRMM_DATA_IND_STRU      *pRrmmDataInd;
    VOS_UINT8                aucBuffer[300];
    VOS_UINT8                ucGprsCipher;

    pDataInd = (LL_NAS_UNITDATA_IND_MSG*)pRcvMsg;

    pRrmmDataInd = (RRMM_DATA_IND_STRU*)aucBuffer;
    /*该域在Gmm_RcvRrmmDataInd函数中检查，这里填充好*/
    pRrmmDataInd->ulCnDomainId       = RRC_NAS_PS_DOMAIN;
    /*该域在Gmm_RcvRrmmDataInd函数中检查，这里填充好*/
    /*
    pRrmmDataInd->ulIntegCheckResult = RRC_NAS_MSG_INTEGRITY_CHECK_SUCCESS;
    */
    /*NAS消息包长度*/
    pRrmmDataInd->RcvNasMsg.ulNasMsgSize = pDataInd->stUnitDataInd.usPduLen;
    /*把LLC包中内容拷贝到RRMM_DATA_IND数据结构中的内容部分*/

    if (pDataInd->stUnitDataInd.usPduLen > 252)
    {
        GMM_LOG_WARN("The length of Msg from LLC is too large!");
        return;
    }

    Gmm_MemCpy(pRrmmDataInd->RcvNasMsg.aucNasMsg,
               pDataInd->stUnitDataInd.aucPdu,
               pDataInd->stUnitDataInd.usPduLen);

    /* 2G消息默认消息完整性通过 */
    if (GMM_FALSE == g_GmmGlobalCtrl.ucIntegrityProtStart)
    {
        g_GmmGlobalCtrl.ucIntegrityProtStart = GMM_TRUE;
    }

    if ((GMM_PD_GMM == (pRrmmDataInd->RcvNasMsg.aucNasMsg[0] & 0x0F))
     && (GMM_MSG_RAU_ACCEPT == pRrmmDataInd->RcvNasMsg.aucNasMsg[1]))
    {
        /* ucCiphInd LL使用的宏定义是LL_NONZERO_VALUE = 1,GMM需要保持同步 */
        if (1 == pDataInd->stUnitDataInd.ucCiphInd)
        {
            ucGprsCipher = VOS_TRUE;
        }
        else
        {
            ucGprsCipher = VOS_FALSE;
        }
        if (ucGprsCipher != gstGmmCasGlobalCtrl.ucGprsCipher)
        {
            gstGmmCasGlobalCtrl.ucGprsCipher = ucGprsCipher;

            NAS_GMM_SndMmcCipherInfoInd();

            /* 指定Kc和加密算法 */
            GMM_AssignGsmKc();
        }
    }

    /*走原来3G的分支 */
    Gmm_RcvRrmmDataInd(pRrmmDataInd);

    return;
}


VOS_VOID NAS_GMM_RcvLlcDataCnf(
    VOS_VOID                           *pRcvMsg
)
{
    LL_NAS_UNITDATA_CNF_MSG            *pstLlNasUintdataCnf = VOS_NULL_PTR;

    pstLlNasUintdataCnf                 = (LL_NAS_UNITDATA_CNF_MSG*)pRcvMsg;

    /* 判断是否为关机流程 */
    if ( (GMM_DETACH_COMBINED_POWER_OFF == g_GmmGlobalCtrl.ucSpecProc)
      || (GMM_DETACH_NORMAL_POWER_OFF   == g_GmmGlobalCtrl.ucSpecProc) )
    {
        if ( pstLlNasUintdataCnf->usMui  != NAS_GMM_GetPowerOffDetachPsMui() )
        {
            NAS_WARNING_LOG(WUEPS_PID_GMM, "GMM_RcvLlcDataCnf:The Result Of ID_LL_UNITDATA_CNF Is Wrong!");

            return;
        }

        /* 关机DETACH消息发送给网侧后的处理 */
        NAS_GMM_RcvLlcDataCnf_PowerOff();

        return;
    }

    return;
}


VOS_VOID NAS_GMM_RcvLlcDataCnf_PowerOff(VOS_VOID)
{
    /* 向OM上报NAS事件 */
    NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_DETACH_FINISH,
                    VOS_NULL_PTR,
                    NAS_OM_EVENT_NO_PARA);

    /* 判断当前接入模式是否GSM网络 */
    if (GMM_TRUE != GMM_IsCasGsmMode())
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_RcvLlcDataCnf_PowerOff:Power Off Failure Due To GMM Is CasGsmMode!");
        return;
    }

    /* 停止定时器 */
    Gmm_TimerStop(GMM_TIMER_1S);
    Gmm_TimerStop(GMM_TIMER_DETACH_FOR_POWER_OFF);

    /* 清除P_TMSI_SIGNATURE */
    if (GMM_UEID_P_TMSI_SIGNATURE
            == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask & GMM_UEID_P_TMSI_SIGNATURE))
    {
        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI_SIGNATURE;

        NAS_MML_InitUeIdPtmsiSignatureInvalid();

        Gmm_SndAgentUsimUpdateFileReq(GMM_USIM_FILE_PS_LOC_INFO);
    }

    /* 给MMC及缓存的应用模块回复消息 */
    Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);

    if (GMM_DETACH_COMBINED_POWER_OFF == g_GmmGlobalCtrl.ucSpecProc)
    {
        NAS_GMM_SndMmGprsDetachComplete();
    }

    Gmm_SndMmcPowerOffCnf();
    Gmm_ComCnfHandle();
    NAS_GMM_FreeTlliForPowerOff();

    /* 清除全局变量 */
    if (GMM_MSG_HOLD_FOR_POWEROFF == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_POWEROFF))
    {
        Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPowerOff);
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_POWEROFF;
    }
    Gmm_HoldBufferFree();

    GMM_BufferMsgDump();

    Gmm_ComVariantInit();

    return;
}


VOS_VOID GMM_RcvGasSuspensionInd(VOS_VOID *pRcvMsg)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    GMM_LOG_INFO("GMM_RcvGasSuspensionInd:Receive RRMM_GPRS_SUSPENSION_IND");

    enCurRat = NAS_MML_GetCurrNetRatType();

    /* 此时CS域连接肯定存在，但MMCGMM_SERVICE_IND可能不会收到 */
    g_GmmGlobalCtrl.CsInfo.ucCsTransFlg       = GMM_TRUE;

#if (FEATURE_LTE == FEATURE_ON)

    /* 通知L,ps域状态为挂起 */
    NAS_GMM_SndLmmInfoChangeNotifyReq(NAS_MML_GetCurrNetRatType(),
                                      VOS_FALSE,
                                      VOS_TRUE,
                                      gstGmmCasGlobalCtrl.GmmSrvState,
                                      VOS_TRUE);
#endif

    switch (g_GmmGlobalCtrl.ucState)
    {
        case GMM_SUSPENDED_WAIT_FOR_SYSINFO:
            g_GmmGlobalCtrl.ucInterRatFlg = VOS_TRUE;
            Gmm_TimerStop(GMM_TIMER_SUSPENDED);
            Gmm_ComStaChg(GMM_SUSPENDED_GPRS_SUSPENSION);
            return;
        case GMM_GPRS_SUSPENSION:
        case GMM_SUSPENDED_GPRS_SUSPENSION:
        case GMM_SUSPENDED_NORMAL_SERVICE:
            GMM_LOG_INFO("GMM_RcvGasSuspensionInd:Receive RRMM_GPRS_SUSPENSION_IND in abnormal state.");
            return;
        default:
            break;
    }

    GMM_SuspendTimer();

    /* <==A32D09766 如果之前LLC没有被挂起，此时需要挂起LLC */
    if (GMM_TRUE == gstGmmCasGlobalCtrl.ucTlliAssignFlg)
    {
        if(GMM_NOT_SUSPEND_LLC == gstGmmCasGlobalCtrl.ucSuspendLlcCause)
        {
            GMM_SndLlcSuspendReq();
        }
        gstGmmCasGlobalCtrl.ucSuspendLlcCause |= GMM_SUSPEND_LLC_FOR_CS;
    }

    gstGmmSuspendCtrl.ucPreSrvState = gstGmmCasGlobalCtrl.GmmSrvState;
    gstGmmSuspendCtrl.ucPreState = g_GmmGlobalCtrl.ucState;

    Gmm_ComStaChg(GMM_GPRS_SUSPENSION);

    /* 指示RABM当前系统模式, 并挂起RABM, bRatChangeFlg为FALSE */
    NAS_GMM_SndRabmSysSrvChgInd(enCurRat,
                                VOS_FALSE,
                                VOS_TRUE,
                                VOS_TRUE);

    return;
}

/*****************************************************************************
 Prototype      : GMM_PowerOffHandle
 Description    : 在GPRS_SUSPENSION状态下,
                  接收POWER OFF消息的延迟处理
 Input          : VOS_VOID
 Output         :
 Return Value   :
 Calls          :
 Called By      :
 History        :
  1.Date        : 2007-03-30
    Author      : s46746
    Modification: Created function
*****************************************************************************/
VOS_VOID GMM_PowerOffHandle()
{
    MMCGMM_POWER_OFF_REQ_STRU stPowerOffReq;

    stPowerOffReq.MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    stPowerOffReq.MsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    stPowerOffReq.MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    stPowerOffReq.MsgHeader.ulReceiverPid   = WUEPS_PID_GMM;
    stPowerOffReq.MsgHeader.ulLength        = sizeof(MMCGMM_POWER_OFF_REQ_STRU)
                                                    - VOS_MSG_HEAD_LENGTH;
    stPowerOffReq.MsgHeader.ulMsgName       = MMCGMM_POWER_OFF_REQ;

    Gmm_RcvMmcPowerOffReq(&stPowerOffReq);
}


VOS_VOID NAS_GMM_HandleGrpsResumeFail()
{
    if (GMM_GPRS_SUSPENSION == g_GmmGlobalCtrl.ucState)
    {
        gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_NORMAL;
        GMM_ResumeTimer(GMM_TIMER_RESUME);
        if (GMM_T3312_TIMEOUT == gstGmmSuspendCtrl.ucT3312State)
        {
            gstGmmSuspendCtrl.ucT3312State = GMM_T3312_NOT_TIMEOUT;
        }

        /*存在PDP激活时，进行路由区更新以回复PS域业务A32D10990==>*/
        /*处于正常服务状态，进行路由区更新以回复PS域业务AT2D18123==>*/
        Gmm_ComStaChg(gstGmmSuspendCtrl.ucPreState);
        if ((GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
         || (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
         || (GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM == g_GmmGlobalCtrl.ucState)
         || (GMM_REGISTERED_NO_CELL_AVAILABLE == g_GmmGlobalCtrl.ucState)
         || (GMM_REGISTERED_PLMN_SEARCH == g_GmmGlobalCtrl.ucState)
         || (GMM_TRUE == g_GmmGlobalCtrl.ucSuspendProc))
        {
            g_GmmGlobalCtrl.ucGprsResumeFlg = GMM_TRUE;
            g_GmmGlobalCtrl.ucSuspendProc   = GMM_FALSE;
        }
        /*<==A32D10990*/
    }
    else
    {
        /*异系统改变之前GMM处于注册状态*/
        if ((0x20 == (gstGmmSuspendCtrl.ucPreState & 0xF0))
         || (GMM_ROUTING_AREA_UPDATING_INITIATED == gstGmmSuspendCtrl.ucPreState))
        {

            Gmm_ComStaChg(GMM_SUSPENDED_WAIT_FOR_SYSINFO);
            Gmm_TimerStart(GMM_TIMER_SUSPENDED);
        }
        else
        {
            if (GMM_TC_ACTIVE == gstGmmSuspendCtrl.ucPreState)
            {
                if ((gstGmmCasGlobalCtrl.ucLastDataSender != NAS_MML_GetCurrNetRatType())
                 && (GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta))
                {
                    Gmm_ComStaChg(GMM_SUSPENDED_WAIT_FOR_SYSINFO);
                }
                else
                {
                    Gmm_ComStaChg(g_GmmGlobalCtrl.ucTcPreSta);
                }
            }
            else
            {
                Gmm_ComStaChg(gstGmmSuspendCtrl.ucPreState);
            }

            GMM_ResumeTimer(GMM_TIMER_RESUME);
            GMM_BufferMsgDump();
            Gmm_HoldBufferFree();                                           /* 清除保留消息                             */
            Gmm_ComCnfHandle();
        }
    }
}


VOS_VOID GMM_RcvGasGprsResumeInd( VOS_VOID *pRcvMsg )
{
    RRMM_GPRS_RESUME_IND_ST *pstGprsResumeMsg;

    pstGprsResumeMsg = (RRMM_GPRS_RESUME_IND_ST*)pRcvMsg;

    GMM_LOG_INFO("GMM_RcvGasGprsResumeInd:Receive RRMM_GPRS_RESUME_IND");

    if ((GMM_GPRS_SUSPENSION != g_GmmGlobalCtrl.ucState)
      && (GMM_SUSPENDED_GPRS_SUSPENSION != g_GmmGlobalCtrl.ucState))
    {
        GMM_LOG_WARN("GMM_RcvGasResumeInd:Receive RRMM_GPRS_RESUME_IND in abnormal state.");
        return;
    }

    if (GMM_POWER_OFF_RCV == gstGmmSuspendCtrl.ucPowerOff)
    {
        if (GMM_TRUE == gstGmmCasGlobalCtrl.ucTlliAssignFlg)
        {
            GMM_SndLlcResumeReq(LL_GMM_RESUME_TYPE_SIGNAL);
        }
        Gmm_TimerStop(GMM_TIMER_1S);
        Gmm_ComStaChg(gstGmmSuspendCtrl.ucPreState);
        GMM_PowerOffHandle();
        gstGmmSuspendCtrl.ucPowerOff = GMM_POWER_OFF_NOT_RCV;
        return;
    }

    /* 此时CS域连接肯定不存在，因此将MMCGMM_SERVICE_IND消息中的处理提前放到此处 */
    g_GmmGlobalCtrl.CsInfo.ucCsTransFlg = GMM_FALSE;
    /* GSM下该标志仅使用GMM_RAU_NORMAL_CS_UPDATED，清除以免对后续流程影响 */
    if (GMM_RAU_NORMAL_CS_UPDATED != g_GmmGlobalCtrl.ucSpecProcInCsTrans)
    {
        g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
    }

    if ((GRR_GMM_GPRS_RESUME_SUCCESS == pstGprsResumeMsg->ucResult)
        && (VOS_FALSE == g_GmmGlobalCtrl.ucInterRatFlg))
    {

        /* 在W下电话切换到GSM后，还回结束后，GMM状态迁移到GMM_TC_ACTIVE状态，导致没有处理系统消息 */
        if (GMM_TC_ACTIVE ==  gstGmmSuspendCtrl.ucPreState)
        {
            if (GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta)
            {
                Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);
            }
            else
            {
                Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);
            }
        }
        else
        {
            /*只存在于非异系统改变过程中*/
            Gmm_ComStaChg(gstGmmSuspendCtrl.ucPreState);
        }

        GMM_ResumeTimer(GMM_TIMER_RESUME);

        GMM_BufferMsgResume();

        if (GMM_T3312_TIMEOUT == gstGmmSuspendCtrl.ucT3312State)
        {
            g_GmmRauCtrl.ucT3312ExpiredFlg = GMM_TRUE;
            gstGmmSuspendCtrl.ucT3312State = GMM_T3312_NOT_TIMEOUT;
        }
    }
    else
    {
        NAS_GMM_HandleGrpsResumeFail();

        GMM_BufferMsgResume();
    }

    g_GmmGlobalCtrl.ucInterRatFlg = VOS_FALSE;

    NAS_GMM_ProcSavedGsmSysInfo();

    return;
}


VOS_VOID GMM_RcvCellReselectInd( VOS_VOID *pRcvMsg )
{
    RRMM_CELL_RESELECT_IND_ST *pstCellReselMsg;

    pstCellReselMsg = (RRMM_CELL_RESELECT_IND_ST *)pRcvMsg;

    GMM_LOG_INFO("GMM_RcvCellReselectInd:Receive RRMM_CELL_RESELECT_IND");

    if(GMM_FALSE == GMM_IsCasGsmMode())
    {
        return;
    }

    if(RRMM_CELL_RESEL_START == pstCellReselMsg->ucCellReselProc)
    {
        gstGmmCasGlobalCtrl.ucCellReselFlg = VOS_TRUE;
    }
    else
    {
        gstGmmCasGlobalCtrl.ucCellReselFlg = VOS_FALSE;
    }

    if(VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
    {
        return;
    }
    if ( VOS_FALSE == NAS_MML_GetSimPsRegStatus()  )
    {
        return;
    }

    /*
    当开始重选时，GMM需要通知LLC挂起用户面数据，并清除LLC的信令面数据
    */
    if(RRMM_CELL_RESEL_START == pstCellReselMsg->ucCellReselProc)
    {
        if (GMM_TRUE == gstGmmCasGlobalCtrl.ucTlliAssignFlg)
        {
            if (GMM_NOT_SUSPEND_LLC == gstGmmCasGlobalCtrl.ucSuspendLlcCause)
            {
                GMM_SndLlcSuspendReq();
            }
            NAS_NORMAL_LOG(WUEPS_PID_GMM,
                "GMM_RcvCellReselectInd: Suspend LLC for Cell Reselection");
            gstGmmCasGlobalCtrl.ucSuspendLlcCause |= GMM_SUSPEND_LLC_FOR_CELL_RESEL;
        }
    }
    else
    {
        if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
        {
            Gmm_SndLlcAbortReq(LL_GMM_CLEAR_DATA_TYPE_NO_SM_SIGNALLING);
        }
        else
        {
            Gmm_SndLlcAbortReq(LL_GMM_CLEAR_DATA_TYPE_TRIG);
        }
    }


    return;
}


VOS_UINT8 GMM_IsGasCellReselect(VOS_VOID)
{
    return gstGmmCasGlobalCtrl.ucCellReselFlg;
}

VOS_VOID GMM_RcvGasTbfRleInd( VOS_VOID *pRcvMsg )
{
    Gmm_SndMmcTBFRelInd();

    if ((GMM_DEREGISTERED_PLMN_SEARCH == g_GmmGlobalCtrl.ucState)
     || (GMM_REGISTERED_PLMN_SEARCH == g_GmmGlobalCtrl.ucState))
    {
        Gmm_TimerStop(GMM_TIMER_WAIT_CONNECT_REL);
    }
    else
    {
        if(GMM_TRUE == g_GmmGlobalCtrl.ulGmmAttachFlg)
        {
            if((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
            && (GMM_DEREGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState))
            {
                Gmm_RcvRoutingAreaUpdateRejectMsg_AttachFlg_Handling();
            }
            g_GmmGlobalCtrl.ulGmmAttachFlg = GMM_FALSE;
        }
    }
}

#if (FEATURE_ON == FEATURE_LTE)

VOS_VOID NAS_GMM_RcvMsRadioCapaInfo_TimerWaitAsMsRadioCapaRunning(VOS_VOID)
{

    if (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
    {
        NAS_GMM_SndRoutingAreaUpdateReq(NAS_GMM_GetRauUpdateType());
        return;
    }

    if (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
    {
        NAS_GMM_SndAttachReq();
    }

    return;
}

#endif

VOS_VOID GMM_RcvGasRadioAccessCapa( VOS_VOID *pRcvMsg )
{
    VOS_UINT8                                               ucLen;
    GRRMM_MS_RADIO_ACCESS_CAPABILITIES_IND_STRU            *pstRacMsg;


#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                                              ulIsWaitMsRadioCapaTimerRunning;

    ulIsWaitMsRadioCapaTimerRunning = NAS_GMM_QryTimerStatus(GMM_TIMER_WAIT_AS_MS_RADIO_CAPA_INFO);
#endif

    if (VOS_NULL_PTR == pRcvMsg)
    {
        return;
    }

    pstRacMsg = (GRRMM_MS_RADIO_ACCESS_CAPABILITIES_IND_STRU *)pRcvMsg;

    ucLen = pstRacMsg->aucData[0] + 1;

    if ((ucLen > MS_RADIO_ACCESS_CAPABILITY_MAX_SIZE) || (ucLen < MS_RADIO_ACCESS_CAPABILITY_MIN_SIZE))
    {
        NAS_ERROR_LOG1(WUEPS_PID_GMM, "GMM_RcvGasRadioAccessCapa: Wrong RAC Len: ", ucLen);
    }
    else
    {
        if (0 != VOS_MemCmp(g_GmmGlobalCtrl.UeInfo.aucRadioCpb,
                    pstRacMsg->aucData, MS_RADIO_ACCESS_CAPABILITY_MAX_SIZE))
        {
            PS_MEM_CPY(g_GmmGlobalCtrl.UeInfo.aucRadioCpb, pstRacMsg->aucData,
                       MS_RADIO_ACCESS_CAPABILITY_MAX_SIZE);

#if (FEATURE_ON == FEATURE_LTE)
            if (NAS_UTRANCTRL_UTRAN_MODE_TDD == NAS_UTRANCTRL_GetCurrUtranMode())
            {
                return;
            }

            /* 根据syscfg设置是否支持L和L是否enable状态更新ucMsRadioCapSupportLteFromAs*/
            g_GmmGlobalCtrl.UeInfo.ucMsRadioCapSupportLteFromAs = (VOS_UINT8)NAS_MML_IsSupportLteCapability();

            if (VOS_TRUE == ulIsWaitMsRadioCapaTimerRunning)
            {
                Gmm_TimerStop(GMM_TIMER_WAIT_AS_MS_RADIO_CAPA_INFO);

                if ((GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
                 || (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState))
                {
                    NAS_GMM_RcvMsRadioCapaInfo_TimerWaitAsMsRadioCapaRunning();

                    return;
                }
            }

            /* 当前已经运行时，重新启动 */
            if (VOS_TRUE == NAS_GMM_QryTimerStatus(GMM_TIMER_DELAY_RADIO_CAPA_TRIGED_RAU))
            {
                Gmm_TimerStop(GMM_TIMER_DELAY_RADIO_CAPA_TRIGED_RAU);
                Gmm_TimerStart(GMM_TIMER_DELAY_RADIO_CAPA_TRIGED_RAU);
                return;
            }

            if (g_GmmGlobalCtrl.UeInfo.ucMsRadioCapSupportLteFromAs != g_GmmGlobalCtrl.UeInfo.ucMsRadioCapSupportLteFromRegReq)
            {
                NAS_GMM_HandleMsRadioCapLteSupportChanged();
            }
#endif
        }

    }

    return;
}


VOS_VOID GMM_RcvGasTdsRadioAccessCapa(
    VOS_VOID                           *pstRcvMsg
)
{
    VOS_UINT8                                               ucLen;
    GRRMM_MS_RADIO_ACCESS_CAPABILITIES_IND_STRU            *pstRacMsg = VOS_NULL_PTR;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                                              ulIsWaitMsRadioCapaTimerRunning;

    ulIsWaitMsRadioCapaTimerRunning = NAS_GMM_QryTimerStatus(GMM_TIMER_WAIT_AS_MS_RADIO_CAPA_INFO);
#endif

    if (VOS_NULL_PTR == pstRcvMsg)
    {
        return;
    }

    pstRacMsg = (GRRMM_MS_RADIO_ACCESS_CAPABILITIES_IND_STRU *)pstRcvMsg;

    ucLen     = pstRacMsg->aucData[0] + 1;

    if ((ucLen > MS_RADIO_ACCESS_CAPABILITY_MAX_SIZE) || (ucLen < MS_RADIO_ACCESS_CAPABILITY_MIN_SIZE))
    {
        NAS_ERROR_LOG1(WUEPS_PID_GMM, "GMM_RcvGasTdsRadioAccessCapa: Wrong RAC Len: ", ucLen);
    }
    else
    {
        if (0 != VOS_MemCmp(g_GmmGlobalCtrl.UeInfo.aucTdsRadioCpb,
                    pstRacMsg->aucData, MS_RADIO_ACCESS_CAPABILITY_MAX_SIZE))
        {
            PS_MEM_CPY(g_GmmGlobalCtrl.UeInfo.aucTdsRadioCpb, pstRacMsg->aucData,
                       MS_RADIO_ACCESS_CAPABILITY_MAX_SIZE);

#if (FEATURE_ON == FEATURE_LTE)
            /* 根据syscfg设置是否支持L和L是否enable状态更新ucMsRadioCapSupportLteFromAs*/
            if (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
            {
                return;
            }

            g_GmmGlobalCtrl.UeInfo.ucMsRadioCapSupportLteFromAs = (VOS_UINT8)NAS_MML_IsSupportLteCapability();

            if (VOS_TRUE == ulIsWaitMsRadioCapaTimerRunning)
            {
                Gmm_TimerStop(GMM_TIMER_WAIT_AS_MS_RADIO_CAPA_INFO);

                if ((GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
                 || (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState))
                {
                    NAS_GMM_RcvMsRadioCapaInfo_TimerWaitAsMsRadioCapaRunning();

                    return;
                }
            }


            /* 当前已经运行时，重新启动 */
            if (VOS_TRUE == NAS_GMM_QryTimerStatus(GMM_TIMER_DELAY_RADIO_CAPA_TRIGED_RAU))
            {
                Gmm_TimerStop(GMM_TIMER_DELAY_RADIO_CAPA_TRIGED_RAU);
                Gmm_TimerStart(GMM_TIMER_DELAY_RADIO_CAPA_TRIGED_RAU);
                return;
            }

            if (g_GmmGlobalCtrl.UeInfo.ucMsRadioCapSupportLteFromAs != g_GmmGlobalCtrl.UeInfo.ucMsRadioCapSupportLteFromRegReq)
            {
                NAS_GMM_HandleMsRadioCapLteSupportChanged();
            }
#endif
        }

    }

    return;
}

VOS_VOID GMM_InitCellUpdate(VOS_UINT8 ucReadychangFLG)
{
    if (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask)
    {
        Gmm_TimerStop(GMM_TIMER_T3312);

#if (FEATURE_LTE == FEATURE_ON)
        NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
#endif
    }

    /* force to standby状态，不发起 */
    if (GMM_TRUE == gstGmmCasGlobalCtrl.ucFtsFlg)
    {
        Gmm_TimerStop(GMM_TIMER_T3314);

        gstGmmCasGlobalCtrl.ucFtsFlg = GMM_FALSE;

        if ( 0xffffffff == gstGmmCasGlobalCtrl.ulReadyTimerValue )
        {
             gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_READY;
#if (FEATURE_LTE == FEATURE_ON)
             if (NAS_GMM_TIMER_T3323_FLG == (NAS_GMM_TIMER_T3323_FLG & g_GmmTimerMng.ulTimerRunMask))
             {
                 Gmm_TimerStop(GMM_TIMER_T3323);
             }
#endif
        }
        else
        {
            gstGmmCasGlobalCtrl.ulReadyTimerValue = 0x0;
            gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_STANDBY;
#if (FEATURE_LTE == FEATURE_ON)
            if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
            {
                NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
            }
#endif
            Gmm_TimerStart(GMM_TIMER_T3312);
        }
        NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
        gstGmmCasGlobalCtrl.ucCellUpdateFlg = GMM_FALSE;
        return;
    }

    /* READY TIMER值为0，不发起 */
    if (0 == gstGmmCasGlobalCtrl.ulReadyTimerValue)
    {
        Gmm_TimerStop(GMM_TIMER_T3314);

        gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_STANDBY;
        NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
        Gmm_TimerStart(GMM_TIMER_T3312);

        gstGmmCasGlobalCtrl.ucCellUpdateFlg = GMM_FALSE;
        return;
    }

    /* 重启READY TIMER */
    if ( 0xffffffff != gstGmmCasGlobalCtrl.ulReadyTimerValue )
    {
        g_GmmTimerMng.aTimerInf[GMM_TIMER_T3314].ulTimerVal
            = gstGmmCasGlobalCtrl.ulReadyTimerValue;

        g_GmmTimerMng.ulTimerValMask |= GMM_TIMER_T3314_FLG;
        if ((GMM_TRUE == ucReadychangFLG))
        {
            Gmm_TimerStop(GMM_TIMER_T3314);
        }
        Gmm_TimerStart(GMM_TIMER_T3314);
    }
    else
    {
        Gmm_TimerStop(GMM_TIMER_T3314);
    }


    gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_READY;   /* GSM READY态标志 */

#if (FEATURE_LTE == FEATURE_ON)
    if (NAS_GMM_TIMER_T3323_FLG == (NAS_GMM_TIMER_T3323_FLG & g_GmmTimerMng.ulTimerRunMask))
    {
        Gmm_TimerStop(GMM_TIMER_T3323);
    }
#endif


    NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);


    if (GMM_FALSE == gstGmmCasGlobalCtrl.ucCellUpdateFlg)
    {/* 小区更新标志无效，不用通知LLC进行小区更新 */
        return;
    }

    if ( VOS_FALSE == gstGmmCasGlobalCtrl.ucReadyTimerChgFlg )
    {
        gstGmmCasGlobalCtrl.ucCellUpdateFlg     = GMM_FALSE;
        return;
    }

    /* 通知LLC */
    if ((GMM_TRUE == gstGmmCasGlobalCtrl.ucCellNotifyFlg)
        && (GMM_FALSE == ucReadychangFLG))
    {
        GMM_SndLlcTriggerReq(LL_GMM_TRIG_CAUSE_CELUPD_CELL_NOTIFY);
    }
    else
    {
        GMM_SndLlcTriggerReq(LL_GMM_TRIG_CAUSE_CELUPD_NO_CELL_NOTIFY);
    }

    gstGmmCasGlobalCtrl.ucCellUpdateFlg     = GMM_FALSE;
    gstGmmCasGlobalCtrl.ucReadyTimerChgFlg   = VOS_FALSE;
    return;
}


VOS_VOID GMM_RcvGasClassMarkChangeInd( VOS_VOID *pRcvMsg )
{
    RRMM_CLASSMARK_CHANGE_IND_STRU     *pstClassMarkMsg = VOS_NULL_PTR;
    NAS_MML_MS_CAPACILITY_INFO_STRU    *pstMsCapability = VOS_NULL_PTR;

    pstClassMarkMsg = (RRMM_CLASSMARK_CHANGE_IND_STRU *)pRcvMsg;
    pstMsCapability = NAS_MML_GetMsCapability();

    /* 更新classmark1 */
    NAS_GMM_UpdateClassmark1(pstMsCapability, pstClassMarkMsg);

    /* 更新classmark2 */
    NAS_GMM_UpdateClassmark2(pstMsCapability, pstClassMarkMsg);

    /* 更新classmark3 */
    NAS_GMM_UpdateClassmark3(pstMsCapability, pstClassMarkMsg);

    return;
}



VOS_VOID GMM_SaveReadyTimerValue(
                        VOS_UINT8 ucMsgByte                 /* 消息中时长位置的字节 */
                        )
{
    VOS_UINT8   ucUnit       = 0;       /* 定义临时变量存储时长单位 */
    VOS_UINT8   ucTimerValue = 0;       /* 定义临时变量存储时长 */
    VOS_UINT32  ulLocalReadyTimer;

    #if 0
    if (GMM_FALSE == gstGmmCasGlobalCtrl.ucReadyTimerNgtFlg)
    {/* 不允许协商READY TIMER */
        return;
    }

    ucUnit       = (VOS_UINT8)(ucMsgByte >> 5);             /* 得到时长单位 */
    ucTimerValue = (VOS_UINT8)(ucMsgByte & 0x1F);           /* 得到Timer Value */

    switch (ucUnit)
    {/* 判断时长单位 */
    case 0:                             /* 2 seconds */
        g_GmmTimerMng.aTimerInf[GMM_TIMER_T3314].ulTimerVal
            = GMM_TIMER_T3314_VALUE;    /* 作为READY TIMER超时基本单位，不改变 */
        gstGmmCasGlobalCtrl.ulReadyTimerValue = ucTimerValue * 2 * 1000;
        break;
    case 1:                             /* 1 minute */
        g_GmmTimerMng.aTimerInf[GMM_TIMER_T3314].ulTimerVal
            = GMM_TIMER_T3314_VALUE;    /* 作为READY TIMER超时基本单位，不改变 */
        gstGmmCasGlobalCtrl.ulReadyTimerValue = ucTimerValue * 60 * 1000;
        break;
    case 2:                             /* decihours */
        g_GmmTimerMng.aTimerInf[GMM_TIMER_T3314].ulTimerVal
            = GMM_TIMER_T3314_VALUE;    /* 作为READY TIMER超时基本单位，不改变 */
        gstGmmCasGlobalCtrl.ulReadyTimerValue = ucTimerValue * 360 * 1000;
        break;
    case 7:                             /* timer is deactivated */
        g_GmmTimerMng.aTimerInf[GMM_TIMER_T3314].ulTimerVal = 0;
        gstGmmCasGlobalCtrl.ulReadyTimerValue = 0;
        break;
    default:
        g_GmmTimerMng.aTimerInf[GMM_TIMER_T3314].ulTimerVal
            = GMM_TIMER_T3314_VALUE;    /* 作为READY TIMER超时基本单位，不改变 */
        gstGmmCasGlobalCtrl.ulReadyTimerValue = ucTimerValue * 60 * 1000;
        break;
    }

    /* READY TIMER超时最大次数更新 */
    gstGmmCasGlobalCtrl.ulReadyTimerCntMax
            = gstGmmCasGlobalCtrl.ulReadyTimerValue / GMM_TIMER_T3314_VALUE;
    #endif

    ucUnit       = (VOS_UINT8)(ucMsgByte >> 5);             /* 得到时长单位 */
    ucTimerValue = (VOS_UINT8)(ucMsgByte & 0x1F);           /* 得到Timer Value */
    gstGmmCasGlobalCtrl.ucReadyTimerChgFlg = VOS_FALSE;
    ulLocalReadyTimer                   = gstGmmCasGlobalCtrl.ulReadyTimerValue;
    switch (ucUnit)
    {
        case 0 :/* 2 seconds */
            gstGmmCasGlobalCtrl.ulReadyTimerValue = ucTimerValue * 2 * 1000;
            break;

        case 1 :/* 1 minute */
            gstGmmCasGlobalCtrl.ulReadyTimerValue = ucTimerValue * 60 * 1000;
            break;

        case 2 :/* decihours */
            gstGmmCasGlobalCtrl.ulReadyTimerValue = ucTimerValue * 360 * 1000;
            break;

        case 7 : /* timer is deactivated */
            gstGmmCasGlobalCtrl.ulReadyTimerValue = 0xffffffff;
            break;

        default:break;

    }
    if ( gstGmmCasGlobalCtrl.ucReadyTimerChgFlg != ulLocalReadyTimer )
    {
        gstGmmCasGlobalCtrl.ucReadyTimerChgFlg = VOS_TRUE;
    }
    return;
}

/*****************************************************************************
 Prototype      : GMM_CasGetMsGprsMode
 Description    : 获取GMM当前MS GPRS模式
                  HSS 4100 V200R001 新增
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2006-03-29
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_UINT8 GMM_CasGetMsGprsMode(VOS_VOID)
{
    VOS_UINT8   ucMsMode = NAS_GSM_GPRS_MODE_A;
    NAS_MML_MS_MODE_ENUM_UINT8      enMsMode;

    enMsMode    = NAS_MML_GetMsMode();

    switch (enMsMode)
    {
        case NAS_MML_MS_MODE_PS_CS:
            ucMsMode = NAS_GSM_GPRS_MODE_A;
            break;
        case NAS_MML_MS_MODE_PS_ONLY:
            ucMsMode = NAS_GSM_GPRS_MODE_C_GPRS;
            break;
        case NAS_MML_MS_MODE_CS_ONLY:
            ucMsMode = NAS_GSM_GPRS_MODE_C_GSM;
            break;
        default:
            ucMsMode = NAS_GSM_GPRS_MODE_B;
            break;
    }

    return ucMsMode;
}

/*****************************************************************************
 Prototype      : GMM_CasGetGmmState
 Description    : 获取GMM当前服务状态，是否处于READY状态
                  HSS 4100 V200R001 新增
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2006-03-29
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_UINT8 GMM_CasGetGmmState(VOS_VOID)
{
    VOS_UINT8   ucGmmState = NAS_GMM_STATE_IDLE;

    switch (gstGmmCasGlobalCtrl.GmmSrvState)
    {
        case GMM_AGB_GPRS_IDLE:
            ucGmmState = NAS_GMM_STATE_IDLE;
            break;
        case GMM_AGB_GPRS_STANDBY:
            ucGmmState = NAS_GMM_STATE_STANDYBY;
            break;
        case GMM_AGB_GPRS_READY:
            ucGmmState = NAS_GMM_STATE_READY;
            break;
        default:
            ucGmmState = NAS_GMM_STATE_IDLE;
            break;
    }

    return ucGmmState;
}


VOS_VOID GMM_CasFsmStateChangeTo(VOS_UINT8 ucFsmSta)
{

    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    enCurRat = NAS_MML_GetCurrNetRatType();
    if ( (NAS_MML_NET_RAT_TYPE_GSM == enCurRat)
      || (NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat) )
    {
        NAS_GMM_NotifyRrmmChgNonDrxMode(g_GmmGlobalCtrl.ucState, ucFsmSta);
    }

#if(FEATURE_ON == FEATURE_DSDS)
    NAS_GMM_NotifySessionAccordingStateChg(g_GmmGlobalCtrl.ucState, ucFsmSta);
#endif

    g_GmmGlobalCtrl.ucState = ucFsmSta;

    NAS_GMM_LogGmmStateInfo(g_GmmGlobalCtrl.ucState);


    NAS_GMM_StopReadyTimer_DeregStat();

    NAS_GMM_SetIdleSrvState_DeregStat();


    GMM_PrintState();

    Gmm_Com_ServiceStatus_Handle();                                               /* 通知MMC服务状态                          */


    return;
}


VOS_VOID NAS_GMM_RcvGprsAccessResultInd(
    VOS_VOID                           *pstMsg
)
{
    GRRGMM_GPRS_ACCESS_RESULT_IND_STRU *pstRcvMsg;

    pstRcvMsg = (GRRGMM_GPRS_ACCESS_RESULT_IND_STRU*)pstMsg;

    /* 根据GAS上报的内容，通知MMC当前的信令连接状态 */
    if (NAS_GPRS_ACCESS_SUCCESS == pstRcvMsg->enResult )
    {
        /* 设置GSM模式下PS域存在业务或者在进行注册 */
        NAS_MML_SetPsTbfStatusFlg(VOS_TRUE);

        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_PRESENT);


#if (FEATURE_LTE == FEATURE_ON)
        if (NAS_GMM_TIMER_T3323_FLG == (NAS_GMM_TIMER_T3323_FLG & g_GmmTimerMng.ulTimerRunMask))
        {
            Gmm_TimerStop(GMM_TIMER_T3323);
        }
#endif
    }
    else
    {
        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);
    }
}


VOS_VOID NAS_GMM_SaveGsmSysInfo(
    MMCGMM_GSM_SYS_INFO_IND_ST         *pstGsmSysInfo
)
{
    MMCGMM_GSM_SYS_INFO_IND_ST         *pstHoldGsmSysInfo = VOS_NULL_PTR;



    /* 只保存一条GSM的系统消息，先释放原来存储的消息，避免内存泄露 */
    NAS_GMM_FreeGsmSysInfo();

    pstHoldGsmSysInfo = (MMCGMM_GSM_SYS_INFO_IND_ST *)Gmm_MemMalloc(sizeof(MMCGMM_GSM_SYS_INFO_IND_ST));
    if (VOS_NULL_PTR == pstHoldGsmSysInfo)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_GMM_SaveGsmSysInfo:WARNING: Mem alloc fail.");
        return;
    }

    /* 置缓存标志 */
    g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_GSM_SYSINFO;

    /* 保存系统消息 */
    Gmm_MemCpy(pstHoldGsmSysInfo, pstGsmSysInfo, sizeof(MMCGMM_GSM_SYS_INFO_IND_ST));
    g_GmmGlobalCtrl.MsgHold.ulMsgAddrForGsmSysinfo = (VOS_UINT32)pstHoldGsmSysInfo;

    return;
}



VOS_VOID NAS_GMM_SetMmT3211ExpiredDelayRauFlag(
    VOS_UINT8                           ucMmT3211ExpiredDelayRauFlag
)
{
    g_GmmGlobalCtrl.MsgHold.ucMmT3211ExpiredDelayRauFlag = ucMmT3211ExpiredDelayRauFlag;
}


VOS_UINT8 NAS_GMM_GetMmT3211ExpiredDelayRauFlag(VOS_VOID)
{
    return g_GmmGlobalCtrl.MsgHold.ucMmT3211ExpiredDelayRauFlag;
}


VOS_VOID NAS_GMM_ProcSavedMmT3211ExpiredNotify(VOS_VOID)
{
    if (VOS_FALSE == NAS_MML_IsPlmnSupportDam(NAS_MML_GetCurrCampPlmnId()))
    {
        return;
    }

    if (VOS_FALSE == NAS_GMM_GetMmT3211ExpiredDelayRauFlag())
    {
        return;
    }

    if (GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
    {
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
    }

    return;
}


VOS_VOID NAS_GMM_ProcSavedGsmSysInfo()
{
    if (NAS_MML_NET_RAT_TYPE_GSM != NAS_MML_GetCurrNetRatType())
    {
        return;
    }


    if (GMM_MSG_HOLD_FOR_GSM_SYSINFO
        != (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_GSM_SYSINFO))
    {
        return;
    }

    if ((GMM_GPRS_SUSPENSION == g_GmmGlobalCtrl.ucState)
     || (GMM_SUSPENDED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
     || (GMM_SUSPENDED_GPRS_SUSPENSION == g_GmmGlobalCtrl.ucState))
    {
        return;
    }



    if (VOS_NULL_PTR != g_GmmGlobalCtrl.MsgHold.ulMsgAddrForGsmSysinfo)
    {
        Gmm_MsgDistribute((VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForGsmSysinfo);
    }


    return;
}



VOS_VOID NAS_GMM_FreeGsmSysInfo()
{
    VOS_VOID                           *pAddr = VOS_NULL_PTR;

    if (GMM_MSG_HOLD_FOR_GSM_SYSINFO
        != (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_GSM_SYSINFO))
    {
        return;
    }

    /* 清除保留标志 */
    g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_GSM_SYSINFO;

    /* 将保留buffer中所有的消息释放 */
    if (VOS_NULL_PTR != g_GmmGlobalCtrl.MsgHold.ulMsgAddrForGsmSysinfo)
    {
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForGsmSysinfo;
        Gmm_MemFree(pAddr);
        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForGsmSysinfo = VOS_NULL_PTR;
    }

    return;
}


VOS_VOID NAS_GMM_InitCellUpdate_RcvSysInfo(VOS_UINT8 ucReadychangFLG)
{
    if (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask)
    {
        Gmm_TimerStop(GMM_TIMER_T3312);

#if (FEATURE_LTE == FEATURE_ON)
        NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
#endif
    }

    /* force to standby状态，不发起 */
    if (GMM_TRUE == gstGmmCasGlobalCtrl.ucFtsFlg)
    {
        Gmm_TimerStop(GMM_TIMER_T3314);

        gstGmmCasGlobalCtrl.ucFtsFlg = GMM_FALSE;

        if ( 0xffffffff == gstGmmCasGlobalCtrl.ulReadyTimerValue )
        {
             gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_READY;
#if (FEATURE_LTE == FEATURE_ON)
             if (NAS_GMM_TIMER_T3323_FLG == (NAS_GMM_TIMER_T3323_FLG & g_GmmTimerMng.ulTimerRunMask))
             {
                 Gmm_TimerStop(GMM_TIMER_T3323);
             }
#endif
        }
        else
        {
            gstGmmCasGlobalCtrl.ulReadyTimerValue = 0x0;
            gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_STANDBY;
#if (FEATURE_LTE == FEATURE_ON)
            if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
            {
                NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
            }
#endif
            Gmm_TimerStart(GMM_TIMER_T3312);
        }
        NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
        gstGmmCasGlobalCtrl.ucCellUpdateFlg = GMM_FALSE;
        return;
    }

    /* READY TIMER值为0，不发起 */
    if (0 == gstGmmCasGlobalCtrl.ulReadyTimerValue)
    {
        Gmm_TimerStop(GMM_TIMER_T3314);

        gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_STANDBY;
        NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
        Gmm_TimerStart(GMM_TIMER_T3312);

        gstGmmCasGlobalCtrl.ucCellUpdateFlg = GMM_FALSE;
        return;
    }

    /* 重启READY TIMER */
    if ( 0xffffffff != gstGmmCasGlobalCtrl.ulReadyTimerValue )
    {
        g_GmmTimerMng.aTimerInf[GMM_TIMER_T3314].ulTimerVal
            = gstGmmCasGlobalCtrl.ulReadyTimerValue;

        g_GmmTimerMng.ulTimerValMask |= GMM_TIMER_T3314_FLG;
        if ((GMM_TRUE == ucReadychangFLG))
        {
            Gmm_TimerStop(GMM_TIMER_T3314);
        }
        Gmm_TimerStart(GMM_TIMER_T3314);
    }
    else
    {
        Gmm_TimerStop(GMM_TIMER_T3314);
    }


    gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_READY;   /* GSM READY态标志 */

#if (FEATURE_LTE == FEATURE_ON)
    if (NAS_GMM_TIMER_T3323_FLG == (NAS_GMM_TIMER_T3323_FLG & g_GmmTimerMng.ulTimerRunMask))
    {
        Gmm_TimerStop(GMM_TIMER_T3323);
    }
#endif


    NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);


    if (GMM_FALSE == gstGmmCasGlobalCtrl.ucCellUpdateFlg)
    {/* 小区更新标志无效，不用通知LLC进行小区更新 */
        return;
    }

    /* 通知LLC */
    if ((GMM_TRUE == gstGmmCasGlobalCtrl.ucCellNotifyFlg)
      && (GMM_FALSE == ucReadychangFLG))
    {
        GMM_SndLlcTriggerReq(LL_GMM_TRIG_CAUSE_CELUPD_CELL_NOTIFY);
    }
    else
    {
        GMM_SndLlcTriggerReq(LL_GMM_TRIG_CAUSE_CELUPD_NO_CELL_NOTIFY);
    }

    gstGmmCasGlobalCtrl.ucCellUpdateFlg     = GMM_FALSE;
    gstGmmCasGlobalCtrl.ucReadyTimerChgFlg   = VOS_FALSE;
    return;
}


VOS_VOID NAS_GMM_NotifyRrmmChgNonDrxMode(
    VOS_UINT8                           ucCurState,
    VOS_UINT8                           ucTargetState
)
{

    /* 44060协议5.5.1.5中描述:
    When initiating the MM procedures for GPRS attach and routeing area update defined in 3GPP TS 24.008,
    the mobile station shall enter the MM non-DRX mode period. This period ends when either of the messages GPRS ATTACH ACCEPT,
    GPRS ATTACH REJECT, ROUTING AREA UPDATE ACCEPT or ROUTING AREA UPDATE REJECT is received by the mobile station.
    This period also ends after timeout when waiting for any of these messages
    在ATTACH和RAU开始到结束应该保持在MM non-DRX状态,本函数根据GMM
        状态的改变判断是否应该给GAS发送通知消息，并发送
    */
    RRMM_GMM_PROC_TYPE_ENUM_UINT16      enGprsProcType;
    RRMM_GMM_PROC_FLAG_ENUM_UINT16      enGprsProcFlg;

    NAS_MML_GMM_PROC_TYPE_ENUM_UINT16   enMmlGmmProcType;
    NAS_MML_GMM_PROC_FLAG_ENUM_UINT16   enMmlGmmProcFlag;

    enGprsProcType = RRMM_GMM_PROC_TYPE_INVALID;
    enGprsProcFlg  = RRMM_GMM_PROC_FLAG_INVALID;

    if ( GMM_REGISTERED_INITIATED == ucCurState )
    {
        enGprsProcType = RRMM_GMM_PROC_TYPE_ATTACH;

        if ( GMM_REGISTERED_INITIATED != ucTargetState )
        {
            enGprsProcFlg = RRMM_GMM_PROC_FLAG_FINISH;
        }
        else
        {
            enGprsProcFlg = RRMM_GMM_PROC_FLAG_START;
        }
    }
    else if ( GMM_ROUTING_AREA_UPDATING_INITIATED == ucCurState )
    {
        if ( GMM_TRUE == g_GmmRauCtrl.ucPeriodicRauFlg )
        {
            enGprsProcType = RRMM_GMM_PROC_TYPE_PERIOD_RAU;
        }
        else
        {
            enGprsProcType = RRMM_GMM_PROC_TYPE_NORMAL_RAU;
        }

        if ( GMM_ROUTING_AREA_UPDATING_INITIATED != ucTargetState )
        {
            enGprsProcFlg = RRMM_GMM_PROC_FLAG_FINISH;
        }
        else
        {
            enGprsProcFlg = RRMM_GMM_PROC_FLAG_START;
        }
    }
    else if ( GMM_REGISTERED_INITIATED == ucTargetState )
    {
        enGprsProcType = RRMM_GMM_PROC_TYPE_ATTACH;
        enGprsProcFlg = RRMM_GMM_PROC_FLAG_START;
    }
    else if ( GMM_ROUTING_AREA_UPDATING_INITIATED == ucTargetState )
    {
        if ( GMM_TRUE == g_GmmRauCtrl.ucPeriodicRauFlg )
        {
            enGprsProcType = RRMM_GMM_PROC_TYPE_PERIOD_RAU;
        }
        else
        {
            enGprsProcType = RRMM_GMM_PROC_TYPE_NORMAL_RAU;
        }

        enGprsProcFlg = RRMM_GMM_PROC_FLAG_START;
    }
    else
    {
    }

    if ( RRMM_GMM_PROC_TYPE_INVALID != enGprsProcType )
    {
        NAS_GMM_SndRrmmGmmProcNotify(enGprsProcType, enGprsProcFlg);

        NAS_GMM_ConverRrcGmmProcTypeToMml(enGprsProcType, &enMmlGmmProcType);
        NAS_GMM_ConverRrcGmmProcFlagToMml(enGprsProcFlg, &enMmlGmmProcFlag);
        NAS_MML_SetGmmProcType(enMmlGmmProcType);
        NAS_MML_SetGmmProcFlag(enMmlGmmProcFlag);
    }
}

VOS_VOID NAS_GMM_UpdateClassmark1(
    NAS_MML_MS_CAPACILITY_INFO_STRU    *pstMsCapability,
    RRMM_CLASSMARK_CHANGE_IND_STRU     *pstClassMarkMsg
)
{
    VOS_UINT8                           ucClassmark2Len;


    ucClassmark2Len = pstClassMarkMsg->ucClassmark2Len;

    /* 长度非法或为0则不使用 */
    if ((MS_CLASSMARK2_MAX_LEN < ucClassmark2Len)
     || (0                    == ucClassmark2Len))
    {
        NAS_ERROR_LOG1(WUEPS_PID_GMM, "NAS_GMM_UpdateClassmark2: Wrong classmark2 Len: ", ucClassmark2Len);
    }
    else
    {
        /* pstClassMarkMsg->aucClassmark2[0]是classmark2的实际长度，从aucClassmark2[1]开始才是实际的值 */
        pstMsCapability->ucClassmark1 = pstClassMarkMsg->aucClassmark2[1];
    }

    return;
}



VOS_VOID NAS_GMM_UpdateClassmark2(
    NAS_MML_MS_CAPACILITY_INFO_STRU    *pstMsCapability,
    RRMM_CLASSMARK_CHANGE_IND_STRU     *pstClassMarkMsg
)
{
    VOS_UINT8                           ucClassmark2Len;


    ucClassmark2Len = pstClassMarkMsg->ucClassmark2Len;

    /* 长度非法或为0则不使用 */
    if ((MS_CLASSMARK2_MAX_LEN < ucClassmark2Len)
     || (0                    == ucClassmark2Len))
    {
        NAS_ERROR_LOG1(WUEPS_PID_GMM, "NAS_GMM_UpdateClassmark2: Wrong classmark2 Len: ", ucClassmark2Len);
    }
    else
    {
        if (0 != PS_MEM_CMP(pstMsCapability->aucClassmark2,
                            pstClassMarkMsg->aucClassmark2, MS_CLASSMARK2_MAX_LEN))
        {
            /* pstClassMarkMsg->aucClassmark2[0]是classmark2的实际长度，从aucClassmark2[1]开始才是实际的值 */
            pstMsCapability->aucClassmark2[0]   = pstClassMarkMsg->aucClassmark2[0];

            PS_MEM_CPY(&(pstMsCapability->aucClassmark2[1]), &(pstClassMarkMsg->aucClassmark2[1]), pstClassMarkMsg->aucClassmark2[0]);
        }
    }

    return;

}


VOS_VOID NAS_GMM_UpdateClassmark3(
    NAS_MML_MS_CAPACILITY_INFO_STRU    *pstMsCapability,
    RRMM_CLASSMARK_CHANGE_IND_STRU     *pstClassMarkMsg
)
{
    VOS_UINT8                           ucFddLen;
    VOS_UINT8                           ucTddLen;


    ucFddLen = pstClassMarkMsg->ucClassmark3FddLen;

    /* 长度非法或为0则不使用 */
    if ((MS_CLASSMARK3_MAX_LEN < ucFddLen)
     || (0                    == ucFddLen))
    {
        NAS_ERROR_LOG1(WUEPS_PID_GMM, "GMM_RcvGasClassMarkChangeInd: Wrong fdd classmark3 Len: ", ucFddLen);
    }
    else
    {
        if (0 != PS_MEM_CMP(&(pstMsCapability->aucFddClassmark3[1]),
                            pstClassMarkMsg->aucClassmark3Fdd, MS_CLASSMARK3_MAX_LEN))
        {
            pstMsCapability->aucFddClassmark3[0] = ucFddLen;
            PS_MEM_CPY(&(pstMsCapability->aucFddClassmark3[1]), pstClassMarkMsg->aucClassmark3Fdd, ucFddLen);
        }
    }

    ucTddLen = pstClassMarkMsg->ucClassmark3TddLen;

    if ((MS_CLASSMARK3_MAX_LEN < ucTddLen)
     || (0                     == ucTddLen))
    {
        NAS_ERROR_LOG1(WUEPS_PID_GMM, "GMM_RcvGasClassMarkChangeInd: Wrong tdd classmark3 Len: ", ucTddLen);
    }
    else
    {
        if (0 != VOS_MemCmp(&(pstMsCapability->aucTddClassmark3[1]),
                            pstClassMarkMsg->aucClassmark3Tdd, MS_CLASSMARK3_MAX_LEN))
        {
            pstMsCapability->aucTddClassmark3[0] = ucTddLen;
            PS_MEM_CPY(&(pstMsCapability->aucTddClassmark3[1]), pstClassMarkMsg->aucClassmark3Tdd, ucTddLen);
        }
    }

    return;

}


/*lint -restore */


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
