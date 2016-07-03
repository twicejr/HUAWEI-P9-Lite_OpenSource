
#include "GmmInc.h"
#include "GmmCasGlobal.h"
#include "GmmCasComm.h"
#include "GmmCasGsm.h"
#include "GmmCasMain.h"

#include "NasUsimmApi.h"
#include "NasUtranCtrlInterface.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人:luojian 107747;检视人:sunshaohua65952;原因:LOG方案设计需要*/
#define    THIS_FILE_ID        PS_FILE_ID_GMM_SERVICE_C
/*lint +e767 修改人:luojian 107747;检视人:sunshaohua*/


VOS_VOID NAS_GMM_RcvRabmReestablishReq_AttemptToUpdate(
    GMMRABM_REESTABLISH_REQ_STRU       *pstMsg
)
{
    if (VOS_FALSE == NAS_MML_IsPlmnSupportDam(NAS_MML_GetCurrCampPlmnId()))
    {
        /*
        3gpp 24.008 4.7.5 : The routing area updating attempt counter shall be
        reset when the MS is in substate ATTEMPTING-TO-UPDATE and
            - a new routing area is entered;
            - expiry of timer T3302; or
            - at request from registration function.
        */

        /* 停止Timer3302 */
        Gmm_TimerStop(GMM_TIMER_T3302);

        /* 停止Timer3311*/
        Gmm_TimerStop(GMM_TIMER_T3311);

        /*发起RAU过程*/
        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

        g_GmmGlobalCtrl.ucSpecProcHold = GMM_SERVICE_REQUEST_DATA_IDLE;
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
    }
    else
    {
        Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);
    }

    return;
}


VOS_VOID NAS_GMM_RcvRabmRabSetupInd(
    GMMRABM_RAB_SETUP_IND_STRU         *pstRabSetupIndMsg
)
{
    VOS_UINT32                          ulT3340TimerStatus;

    ulT3340TimerStatus = NAS_GMM_QryTimerStatus(GMM_TIMER_T3340);

    /* 2G网络模式不处理 */
    if (GMM_TRUE == GMM_IsCasGsmMode())
    {
        return;
    }

    /* 如果t3340定时器在运行，则停止t3340 */
    if (VOS_TRUE == ulT3340TimerStatus)
    {
        Gmm_TimerStop(GMM_TIMER_T3340);

        if (0 != g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk)
        {
            Gmm_DealWithBuffAfterProc();
        }
    }

    return;
}



VOS_VOID Gmm_RcvRabmReestablishReq(VOS_VOID *pMsg)
{
    VOS_UINT32                      ulRrcEstCauseTemp;
    NAS_MSG_STRU                    *ptrNasMsg;
    GMMRABM_REESTABLISH_REQ_STRU    *pRabmMsg;
    GMMRABM_REESTABLISH_REQ_STRU    *ptr;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    enCurRat = NAS_MML_GetCurrNetRatType();

    if (GMM_TRUE == GMM_IsCasGsmMode())
    {/* 2G网络模式不处理 */
        return;
    }

    if (VOS_TRUE == NAS_MML_GetPsRestrictNormalServiceFlg())
    {
        Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);
        return;
    }

    pRabmMsg = (GMMRABM_REESTABLISH_REQ_STRU *)pMsg;

    #if(PS_UE_REL_VER >= PS_PTL_VER_R7)
    g_GmmGlobalCtrl.usUplinkDataStatus  = pRabmMsg->usUplinkDataStatus;
    #endif

    /* 如果当前用户发起列表搜网,已用户发起的列表搜网优先 */
    /*if ( VOS_TRUE == NAS_MMC_IsEnableRabmReset())
 */
    /*{
 */
    /*    Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);                  发送GMMRABM_REESTABLISH_CNF(fail)        */
    /*    return;
 */
    /*}
 */

    /* 将RabmReestablishReq原语中的原因值对应到RRMM_EST_REQ原语中的原因值 */
    switch (pRabmMsg->ulRrcEstCause)

    {
    case GMM_RABM_RRC_EST_CAUSE_ORG_CONV_CALL:
        ulRrcEstCauseTemp = RRC_EST_CAUSE_ORIGIN_CONVERSAT_CALL;
        break;
    case GMM_RABM_RRC_EST_CAUSE_ORG_STM_CALL:
        ulRrcEstCauseTemp = RRC_EST_CAUSE_ORIGIN_STREAM_CALL;
        break;
    case GMM_RABM_RRC_EST_CAUSE_ORG_INTER_CALL:
        ulRrcEstCauseTemp = RRC_EST_CAUSE_ORIGIN_INTERACT_CALL;
        break;
    case GMM_RABM_RRC_EST_CAUSE_ORG_BG_CALL:
        ulRrcEstCauseTemp = RRC_EST_CAUSE_ORIGIN_BACKGROUND_CALL;
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRabmReestablishReq:WARNING: RRC Connection Setup Cause is Abnormal");
        return;
    }

    switch (g_GmmGlobalCtrl.ucState)
    {                                                                           /* 根据GMM不同的状态，进行相应的处理        */
    case GMM_DEREGISTERED_INITIATED:
    case GMM_REGISTERED_NO_CELL_AVAILABLE:
    case GMM_REGISTERED_LIMITED_SERVICE:
    case GMM_DEREGISTERED_PLMN_SEARCH:
        Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);                 /* 发送GMMRABM_REESTABLISH_CNF(fail)        */
        break;
    case GMM_ROUTING_AREA_UPDATING_INITIATED:
    case GMM_SERVICE_REQUEST_INITIATED:
    case GMM_REGISTERED_IMSI_DETACH_INITIATED:
        /* 如果已经缓存有消息,则释放原来的缓存 */
        if (GMM_MSG_HOLD_FOR_SERVICE
            == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &
                                        GMM_MSG_HOLD_FOR_SERVICE))
        {                                                                       /* 如果有保留的ServiceRequest原语           */
            ptr = (GMMRABM_REESTABLISH_REQ_STRU *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForService;      /* 读取ServiceRequest原语地址               */
            Gmm_MemFree(ptr);                                                   /* 将保留buffer中所有的消息释放             */
        }
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_SERVICE;       /* 填写GMM_MSG_HOLD_STRU类型的变量          */

        ptr = (GMMRABM_REESTABLISH_REQ_STRU *)Gmm_MemMalloc(sizeof(GMMRABM_REESTABLISH_REQ_STRU));
        if (VOS_NULL_PTR == ptr)
        {
              PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Gmm_RcvRabmReestablishReq:ERROR: Memory is not allocated");
              return;
        }
        Gmm_MemCpy(ptr, pRabmMsg, sizeof(GMMRABM_REESTABLISH_REQ_STRU));
        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForService = (VOS_UINT32)ptr;               /* 保留该原语                               */
        break;

    case GMM_REGISTERED_PLMN_SEARCH:
        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

        g_GmmGlobalCtrl.ucSpecProcHold = GMM_SERVICE_REQUEST_DATA_IDLE;

        Gmm_SndMmcGprsServiceInd(NAS_MMC_GMM_GPRS_SERVICE_DATA);
        break;

    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
        NAS_GMM_RcvRabmReestablishReq_AttemptToUpdate(pRabmMsg);
        break;

    case GMM_REGISTERED_NORMAL_SERVICE:
    case GMM_REGISTERED_UPDATE_NEEDED:

        if ((MM_COM_SRVST_NORMAL_SERVICE != NAS_GMM_GetRegUptNeededPsSrvStatus())
         && (GMM_REGISTERED_UPDATE_NEEDED == g_GmmGlobalCtrl.ucState))
        {
            return;
        }

        g_GmmGlobalCtrl.ulEstCause = ulRrcEstCauseTemp;

        if (RR_REL_CAUSE_DIRECTED_SINGNALING_CONNECTION_RE_ESTABLISHMENT ==
                                                    g_GmmGlobalCtrl.ucRelCause)
        {
            g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

            g_GmmGlobalCtrl.ucSpecProcHold = GMM_SERVICE_REQUEST_DATA_IDLE;
            return;
        }
        if ((GMM_RAU_FOR_WAITSERVICE == gstGmmSuspendCtrl.ucRauCause)
            && (gstGmmCasGlobalCtrl.ucLastDataSender != enCurRat)
#if (FEATURE_ON == FEATURE_LTE)
          && (gstGmmCasGlobalCtrl.ucLastDataSender != NAS_MML_NET_RAT_TYPE_LTE)
#endif
            )
        {
            GMM_LOG_INFO("Gmm_RcvRabmReestablishReq:Inter System change, Exec select RAU.");

            g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

            g_GmmGlobalCtrl.ucSpecProcHold = GMM_SERVICE_REQUEST_DATA_IDLE;
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
            return;
        }
        /* 如果此前GMM在建连接的过程中由于RAI改变而主动要求释放正在建立的连接，
           那么对于在等待接入层的连接释放指示以及连接释放指示之后上报的系统消息
           过程中收到的上层请求需要缓存*/
        if (GMM_TRUE == g_GmmGlobalCtrl.ucRaiChgRelFlg)
        {
            if (GMM_FALSE == g_GmmGlobalCtrl.ucFollowOnFlg)
            {
                g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
                NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

                g_GmmGlobalCtrl.ucSpecProcHold = GMM_SERVICE_REQUEST_DATA_IDLE;
            }
            else
            {
                if (GMM_MSG_HOLD_FOR_SERVICE ==
                    (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &
                                        GMM_MSG_HOLD_FOR_SERVICE))
                {                                                               /* 如果有保留的ServiceRequest原语           */
                    ptr = (GMMRABM_REESTABLISH_REQ_STRU *)g_GmmGlobalCtrl.MsgHold.
                                                        ulMsgAddrForService;    /* 读取ServiceRequest原语地址               */
                    Gmm_MemFree(ptr);                                           /* 将保留buffer中所有的消息释放             */
                }
                g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |=
                                                    GMM_MSG_HOLD_FOR_SERVICE;   /* 填写GMM_MSG_HOLD_STRU类型的变量          */

                ptr = (GMMRABM_REESTABLISH_REQ_STRU *)Gmm_MemMalloc(sizeof(GMMRABM_REESTABLISH_REQ_STRU));
                if (VOS_NULL_PTR == ptr)
                {
                      PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Gmm_RcvRabmReestablishReq:ERROR: Memory is not allocated");
                      return;
                }
                Gmm_MemCpy(ptr, pRabmMsg, sizeof(GMMRABM_REESTABLISH_REQ_STRU));
                g_GmmGlobalCtrl.MsgHold.ulMsgAddrForService = (VOS_UINT32)ptr;  /* 保留该原语                               */
            }

            return;
        }

        if (  (GMM_TIMER_T3319_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3319_FLG))
            || (GMM_TIMER_T3340_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3340_FLG))
            || (VOS_TRUE == gstGmmCasGlobalCtrl.ucRauCmpFlg))
        {                                                                       /* T3319/T3340在运行                              */
            ptr = (GMMRABM_REESTABLISH_REQ_STRU *)Gmm_MemMalloc(sizeof(GMMRABM_REESTABLISH_REQ_STRU));

            if (VOS_NULL_PTR == ptr)
            {
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Gmm_RcvRabmReestablishReq:ERROR: Memory is not allocated");
                return;
            }

            Gmm_MemCpy(ptr, pRabmMsg, sizeof(GMMRABM_REESTABLISH_REQ_STRU));
            g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_SERVICE;   /* 置消息缓存标志                           */
            g_GmmGlobalCtrl.MsgHold.ulMsgAddrForService = (VOS_UINT32)ptr;      /* 保留该原语                               */
            return;
        }

        g_GmmGlobalCtrl.ucServPreSta = g_GmmGlobalCtrl.ucState;                 /* 保留GMM状态                              */

        GMM_CasFsmStateChangeTo(GMM_SERVICE_REQUEST_INITIATED);

        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvRabmReestablishReq:NORMAL: STATUS IS GMM_SERVICE_REQUEST_INITIATED");

        g_MmSubLyrShare.GmmShare.ucDeatchEnableFlg = GMM_DETACH_ABLE;

        if (GMM_FALSE == g_GmmGlobalCtrl.ucSigConFlg)
        {                                                                       /* 无信令                                   */
            g_GmmGlobalCtrl.ucSpecProc = GMM_SERVICE_REQUEST_DATA_IDLE;         /* 设置当前进行的specific流程               */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRabmReestablishReq:INFO: SR(data) procedure started");
            ptrNasMsg = Gmm_ServiceRequestMsgMake_ForData(pRabmMsg->usUplinkDataStatus, pRabmMsg->usPdpContextStatus);                            /* 调用make函数                             */

            Gmm_SndRrmmEstReq(ulRrcEstCauseTemp,
                              GMM_RRC_IDNNS_UNKNOWN,
                              ptrNasMsg);                                       /* 发RRMM_EST_REQ                           */

            Gmm_TimerStart(GMM_TIMER_PROTECT_FOR_SIGNALING);
            NAS_EventReport(WUEPS_PID_GMM,
                            NAS_OM_EVENT_DATA_SERVICE_REQ,
                            VOS_NULL_PTR,
                            NAS_OM_EVENT_NO_PARA);
        }
        else
        {                                                                       /* 有信令                                   */
            g_GmmGlobalCtrl.ucSpecProc = GMM_SERVICE_REQUEST_DATA_CONN;         /* 设置当前进行的specific流程               */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRabmReestablishReq:INFO: SR(data) procedure started");
            ptrNasMsg = Gmm_ServiceRequestMsgMake_ForData(pRabmMsg->usUplinkDataStatus, pRabmMsg->usPdpContextStatus);                            /* 调用make函数                             */

            Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, ptrNasMsg);            /* 调用发送RRMM_DATA_REQ函数                */
            Gmm_TimerStart(GMM_TIMER_T3317);                                    /* 启动T3317                                */
        }

        if (0 != (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3311_FLG))
        {                                                                       /* T3311在运行                              */
            Gmm_TimerPause(GMM_TIMER_T3311);                                    /* 挂起T3311                                */
        }
        break;

    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
        g_GmmGlobalCtrl.ulEstCause = ulRrcEstCauseTemp;
        if ( (GMM_RAU_FOR_WAITSERVICE == gstGmmSuspendCtrl.ucRauCause)
          && (gstGmmCasGlobalCtrl.ucLastDataSender != enCurRat)
#if (FEATURE_ON == FEATURE_LTE)
          && (gstGmmCasGlobalCtrl.ucLastDataSender != NAS_MML_NET_RAT_TYPE_LTE)
#endif
          )
        {
            GMM_LOG_INFO("Gmm_RcvRabmReestablishReq:Inter System change, Exec select RAU.");

            g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

            g_GmmGlobalCtrl.ucSpecProcHold = GMM_SERVICE_REQUEST_DATA_IDLE;
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
            return;
        }

        if (0 != (g_GmmTimerMng.ulTimerRunMask & (0x00000001 << GMM_TIMER_T3319)))
        {                                                                       /* T3319在运行                              */
            ptr = (GMMRABM_REESTABLISH_REQ_STRU *)Gmm_MemMalloc(sizeof(GMMRABM_REESTABLISH_REQ_STRU));

            if (VOS_NULL_PTR == ptr)
            {
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Gmm_RcvRabmReestablishReq:ERROR: Memory is not allocated");
                return;
            }

            Gmm_MemCpy(ptr, pRabmMsg, sizeof(GMMRABM_REESTABLISH_REQ_STRU));
            g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_SERVICE;   /* 置消息缓存标志                           */
            g_GmmGlobalCtrl.MsgHold.ulMsgAddrForService = (VOS_UINT32)ptr;      /* 保留该原语                               */
            return;
        }

        g_GmmGlobalCtrl.ucServPreSta = g_GmmGlobalCtrl.ucState;                 /* 保留GMM状态                              */
        GMM_CasFsmStateChangeTo(GMM_SERVICE_REQUEST_INITIATED);
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvRabmReestablishReq:NORMAL: STATUS IS GMM_SERVICE_REQUEST_INITIATED");

        g_MmSubLyrShare.GmmShare.ucDeatchEnableFlg = GMM_DETACH_ABLE;

        if (GMM_FALSE == g_GmmGlobalCtrl.ucSigConFlg)
        {                                                                       /* 无信令                                   */
            g_GmmGlobalCtrl.ucSpecProc = GMM_SERVICE_REQUEST_DATA_IDLE;         /* 设置当前进行的specific流程               */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRabmReestablishReq:INFO: SR(data) procedure started");
            ptrNasMsg = Gmm_ServiceRequestMsgMake_ForData(pRabmMsg->usUplinkDataStatus, pRabmMsg->usPdpContextStatus);                            /* 调用make函数                             */

            Gmm_SndRrmmEstReq(ulRrcEstCauseTemp,
                              GMM_RRC_IDNNS_UNKNOWN,
                              ptrNasMsg);                                       /* 发RRMM_EST_REQ                           */
            Gmm_TimerStart(GMM_TIMER_PROTECT_FOR_SIGNALING);
            NAS_EventReport(WUEPS_PID_GMM,
                            NAS_OM_EVENT_DATA_SERVICE_REQ,
                            VOS_NULL_PTR,
                            NAS_OM_EVENT_NO_PARA);
        }
        else
        {                                                                       /* 有信令                                   */
            g_GmmGlobalCtrl.ucSpecProc = GMM_SERVICE_REQUEST_DATA_CONN;         /* 设置当前进行的specific流程               */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRabmReestablishReq:INFO: SR(data) procedure started");
            ptrNasMsg = Gmm_ServiceRequestMsgMake_ForData(pRabmMsg->usUplinkDataStatus, pRabmMsg->usPdpContextStatus);                            /* 调用make函数                             */

            Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH,ptrNasMsg);             /* 调用发送RRMM_DATA_REQ函数                */
            Gmm_TimerStart(GMM_TIMER_T3317);                                    /* 启动T3317                                */
        }

        if (0 != (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3311_FLG))
        {                                                                       /* T3311在运行                              */
            Gmm_TimerPause(GMM_TIMER_T3311);                                    /* 挂起T3311                                */
        }
        if (0 != (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3302_FLG))
        {                                                                       /* T3302在运行                              */
            Gmm_TimerPause(GMM_TIMER_T3302_FLG);                                /* 挂起T3302                                */
        }
        break;
    case GMM_SUSPENDED_WAIT_FOR_SYSINFO:
        NAS_GMM_RcvRabmEstReq_SuspendWaitForSysinfo(pMsg);
        break;
    default:
        /* 其他状态回复失败消息 */
        Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);                 /* 发送GMMRABM_REESTABLISH_CNF(fail)        */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRabmReestablishReq:WARNING: g_GmmGlobalCtrl.ucState is Error");
        break;
    }

    return;
}


VOS_VOID NAS_GMM_RcvRabmEstReq_SuspendWaitForSysinfo(
    VOS_VOID                            *pMsg
)
{
    if (VOS_FALSE == NAS_MML_GetSimPsRegStatus())
    {
        Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);;
        return;
    }

    if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
    {
        Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);;
        return;
    }

    /* 在从G切换到W时,需要首先发起RAU恢复PS,然后处理缓冲的RABM消息 */
    if ((NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
     && (MMC_SUSPEND_CAUSE_HANDOVER == gstGmmSuspendCtrl.ucSuspendCause)
     && (NAS_MML_NET_RAT_TYPE_GSM   == gstGmmSuspendCtrl.ucPreRat))
    {
        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

        g_GmmGlobalCtrl.ucSpecProcHold = GMM_SERVICE_REQUEST_DATA_IDLE;

        /* 如果等系统消息定时器在运行，则不下发RAU */
        if (NAS_GMM_TIMER_HO_WAIT_SYSINFO_FLG == (NAS_GMM_TIMER_HO_WAIT_SYSINFO_FLG & g_GmmTimerMng.ulTimerRunMask))
        {
            return;
        }

        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);

    }

    return;
}


VOS_VOID Gmm_RcvRabRelInd(VOS_VOID)
{
    VOS_VOID                            *pMsg;
    GMMRABM_REESTABLISH_REQ_STRU        *pRabmReEst;
    Gmm_TimerStop(GMM_TIMER_T3319);

    if (GMM_MSG_HOLD_FOR_SERVICE ==
        (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SERVICE))
    {                                                                           /* 如果有保留的SR原语                       */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SERVICE;      /* 清除缓存标志                             */

        pMsg = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForService;

        /*构造分发消息*/
        pRabmReEst = (GMMRABM_REESTABLISH_REQ_STRU *)Gmm_MemMalloc(sizeof(GMMRABM_REESTABLISH_REQ_STRU));

        if (VOS_NULL_PTR == pRabmReEst)
        {
            Gmm_MemFree(pMsg);
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "Gmm_DealWithBuffAfterProc:ERROR: Gmm_MemMalloc fail !! ");
            return;
        }

        Gmm_MemCpy(pRabmReEst, pMsg, sizeof(GMMRABM_REESTABLISH_REQ_STRU));

        /*释放保存的RAMB消息*/
        Gmm_MemFree(pMsg);

        /*分发缓存的Service消息*/
        Gmm_MsgDistribute((VOS_VOID *)(pRabmReEst));

        /*释放新申请的内存*/
        Gmm_MemFree(pRabmReEst);
    }
}

VOS_VOID Gmm_RcvRrmmSecurityInd(VOS_VOID *pMsg)
{
    RRMM_SECURITY_IND_STRU             *pstSecurityInd = VOS_NULL_PTR;

    pstSecurityInd = (RRMM_SECURITY_IND_STRU *)pMsg;

    /* 收到了从网侧来的Security Mode Command 消息 */
    g_GmmGlobalCtrl.stGmmLinkCtrl.ucSmcOrFirstNasMsgRcvdFlg = VOS_TRUE;

    if (RRC_SECURITY_PS_SMC_CMPL == pstSecurityInd->ulRptMode)
    {
        /* 一个PS SMC流程结束认为进入PMM_CONNECTED状态，需要停止T3312 */
        Gmm_TimerStop(GMM_TIMER_T3312);
#if (defined(__PS_WIN32_RECUR__)) || ( VOS_WIN32 == VOS_OS_VER )
#else
#if (FEATURE_LTE == FEATURE_ON)
        NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
#endif
#endif

        /* 24008_CR1735R3_(Rel-10)_C1-111529 was 1470 was 1012 24008-a10 24008 4.7.5.1.5章节描述如下:
        If in addition the ROUTING AREA UPDATE REQUEST message indicated "periodic updating",
        -   in Iu mode, the timer T3311 may be stopped when the MS enters PMM-CONNECTED mode;
        -   in A/Gb mode, the timer T3311 may be stopped when the READY timer is started.*/
        NAS_GMM_StopT3311InIuPmmConnMode_T3312Exp();

    }

    switch (g_GmmGlobalCtrl.ucState)
    {                                                                           /* 根据GMM不同的状态，进行相应的处理        */
    case GMM_REGISTERED_INITIATED:
    case GMM_DEREGISTERED_INITIATED:
    case GMM_ROUTING_AREA_UPDATING_INITIATED:
    case GMM_DEREGISTERED_NORMAL_SERVICE:
    case GMM_DEREGISTERED_LIMITED_SERVICE:
    case GMM_DEREGISTERED_ATTACH_NEEDED:
    case GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH:
    case GMM_REGISTERED_NORMAL_SERVICE:
    case GMM_REGISTERED_LIMITED_SERVICE:
    case GMM_REGISTERED_UPDATE_NEEDED:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
    case GMM_REGISTERED_IMSI_DETACH_INITIATED:
        Gmm_RcvRrmmSecurityInd_RegInit((RRMM_SECURITY_IND_STRU *)pMsg);
        break;
    case GMM_SERVICE_REQUEST_INITIATED:
        Gmm_RcvRrmmSecurityInd_ServReqInit((RRMM_SECURITY_IND_STRU *)pMsg);
        break;

    case GMM_SUSPENDED_WAIT_FOR_SYSINFO:
        Gmm_RcvRrmmSecurityInd_SuspendWaitSysinfo((RRMM_SECURITY_IND_STRU *)pMsg);
        break;

    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRrmmSecurityInd:WARNING: g_GmmGlobalCtrl.ucState is Error");
        break;
    }
}

VOS_VOID Gmm_RcvRrmmSecurityInd_RegInit(
                                    RRMM_SECURITY_IND_STRU *ptr                 /* 原语首地址                               */
                                    )
{
    if (RRC_SECURITY_PS_SMC_RCV == ptr->ulRptMode)
    {                                                                           /* ulRptMode=收到有效的PS SMC消息           */
        g_GmmAuthenCtrl.ucResStoredFlg  = GMM_FALSE;                            /* 将"RES存在标志 "置为0                    */
        g_GmmAuthenCtrl.ucRandStoredFlg = GMM_FALSE;                            /* 将"RAND存在标志 "置为0                   */

        Gmm_TimerStop(GMM_TIMER_T3316);                                         /* 停止T3316                                */

        /*A32D12268==>完整性保护启动*/
        g_MmSubLyrShare.GmmShare.ucPsIntegrityProtect   = NAS_MML_RRC_INTEGRITY_PROTECT_ACTIVE;
        /*<==A32D12268*/
    }
    else if ((RRC_SECURITY_DEL_CS_PS_KEY == ptr->ulRptMode)
        || (RRC_SECURITY_DEL_PS_KEY == ptr->ulRptMode))
    {                                                                           /* ulRptMode=USIM中(CS+PS)/PS域CK、IK被删除 */

        NAS_MML_SetSimPsSecurityCksn(NAS_MML_CKSN_INVALID);            /* 删除CKSN                                 */
        NAS_MML_InitPsSecurityUmtsCkInvalid();
        NAS_MML_InitPsSecurityUmtsIkInvalid();
    }
    else
    {
    }
}

VOS_VOID Gmm_RcvRrmmSecurityInd_ServReqInit(
                                        RRMM_SECURITY_IND_STRU *ptr             /* 原语首地址                               */
                                        )
{
    GMMSM_DATA_REQ_STRU *pSmDataReqMsg;                                         /* 指向GMMSM_DATA_REQ_STRU结构的指针        */


    if (RRC_SECURITY_PS_SMC_CMPL == ptr->ulRptMode)
    {                                                                           /* ulRptMode=一个SMC流程结束                */
        if (GMM_SERVICE_REQUEST_DATA_CONN == g_GmmGlobalCtrl.ucSpecProc)
        {                                                                       /* service type = data_connected            */
            return;
        }

        Gmm_TimerStop(GMM_TIMER_T3317);                                         /* 停T3317                                  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */
        Gmm_ComStaChg(g_GmmGlobalCtrl.ucServPreSta);                            /* 调用状态的公共处理                       */
        if (GMM_SERVICE_REQUEST_DATA_IDLE == g_GmmGlobalCtrl.ucSpecProc)
        {
            Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_SUCCESS);             /* 发送GMMRABM_REESTABLISH_CNF（Success）   */
            /* RABM触发的 Service Request 流程成功后，如果踊剐缓存的RABM
               重建消息，那么不需要再次向网侧发送，清除掉即可。 */
            if (GMM_MSG_HOLD_FOR_SERVICE
                == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SERVICE))
            {                                                                           /* 如果有保留的SR原语                       */
                g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SERVICE;      /* 清除缓存标志                             */
                Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForService);
            }

            Gmm_TimerStart(GMM_TIMER_T3319);                                    /* 启动3319                                 */
        }
        if ((GMM_SERVICE_REQUEST_SIGNALLING == g_GmmGlobalCtrl.ucSpecProc)
            && (GMM_MSG_HOLD_FOR_SM
            == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SM)))
        {                                                                       /* 当前的流程是SERVICE_REQUEST_SIGNALLING   */
            NAS_NORMAL_LOG(WUEPS_PID_GMM, "Gmm_RcvRrmmSecurityInd_ServReqInit(): Process cached SM Data Req");

            pSmDataReqMsg =
                (GMMSM_DATA_REQ_STRU*)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSm;   /* 得到保留的消息                           */

            Gmm_SndRrmmDataReqForCm(RRC_NAS_MSG_PRIORTY_HIGH,
                                    &pSmDataReqMsg->SmMsg);                     /* 发送RRMM_DATA_REQ(CM子层的消息首地址)    */

            g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SM;       /* 清除保留标志                             */
            Gmm_MemFree(pSmDataReqMsg);                                         /* 释放保存的SM消息                         */

            NAS_GMM_SndSmSigConnInd();
        }

        if ( GMM_TRUE == g_GmmServiceCtrl.ucSmsFlg)
        {                                                                       /* SMS在等待响应                            */
            Gmm_SndSmsEstCnf();                                                 /* 发送PMMSMS_EST_CNF                       */
            g_GmmServiceCtrl.ucSmsFlg = GMM_FALSE;
        }

        NAS_GMM_SndMmGmmActionResultInd(GMMMM_ACTION_SUCCESS,
                                        NAS_MML_REG_FAIL_CAUSE_NULL);                                     /* 发送MMCGMM_GMM_ACTION_RESULT_IND()       */


        /* 向MMC发送service request结果 */
        NAS_GMM_SndMmcServiceRequestResultInd(GMM_MMC_ACTION_RESULT_SUCCESS,
                                              NAS_MML_REG_FAIL_CAUSE_NULL);
        /* 事件上报 */
        NAS_EventReport(WUEPS_PID_GMM,
                        NAS_OM_EVENT_DATA_SERVICE_ACC,
                        VOS_NULL_PTR,
                        NAS_OM_EVENT_NO_PARA);

        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                        /* 清当前进行的specific流程                 */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmSecurityInd_ServReqInit:INFO: specific procedure ended");
        if (GMM_TIMER_T3311_FLG
            == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3311_FLG))
        {                                                                       /* 存在被挂起的T3311                        */
            Gmm_TimerResume(GMM_TIMER_T3311);                                   /* 恢复T3311                                */
        }
        else if (GMM_TIMER_T3302_FLG
            == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3302_FLG))
        {                                                                       /* 存在被挂起的T3302                        */
            Gmm_TimerResume(GMM_TIMER_T3302);                                   /* 恢复T3302                                */
        }
        else
        {
        }

        if (0 != g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk)
        {                                                                       /* 有保留的消息                             */
            Gmm_DealWithBuffAfterProc();
        }

    }
    else if (RRC_SECURITY_PS_SMC_RCV == ptr->ulRptMode)
    {                                                                           /* ulRptMode=收到有效的PS SMC消息           */
        g_GmmAuthenCtrl.ucResStoredFlg  = GMM_FALSE;                            /* 将"RES存在标志 "置为0                    */
        g_GmmAuthenCtrl.ucRandStoredFlg = GMM_FALSE;                            /* 将"RAND存在标志 "置为0                   */

        Gmm_TimerStop(GMM_TIMER_T3316);                                         /* 停止T3316                                */

        /*A32D12268==>完整性保护启动*/
        g_MmSubLyrShare.GmmShare.ucPsIntegrityProtect =
                                        NAS_MML_RRC_INTEGRITY_PROTECT_ACTIVE;
        /*<==A32D12268*/
    }
    else if ((RRC_SECURITY_DEL_CS_PS_KEY == ptr->ulRptMode)
        || (RRC_SECURITY_DEL_PS_KEY == ptr->ulRptMode))
    {                                                                           /* ulRptMode=USIM中(CS+PS)/PS域CK、IK被删除 */
        NAS_MML_SetSimPsSecurityCksn(NAS_MML_CKSN_INVALID);            /* 删除CKSN                                 */
        NAS_MML_InitPsSecurityUmtsCkInvalid();
        NAS_MML_InitPsSecurityUmtsIkInvalid();
    }
    else
    {
    }

}


VOS_VOID Gmm_RcvRrmmSecurityInd_SuspendWaitSysinfo(
    RRMM_SECURITY_IND_STRU              *pStSecurityInd
)
{
    if (RRC_SECURITY_PS_SMC_CMPL == pStSecurityInd->ulRptMode)
    {
        Gmm_TimerStop(GMM_TIMER_T3317);
        Gmm_TimerStop(GMM_TIMER_T3318);
        Gmm_TimerStop(GMM_TIMER_T3320);

    }
    else if (RRC_SECURITY_PS_SMC_RCV == pStSecurityInd->ulRptMode)
    {
        g_GmmAuthenCtrl.ucResStoredFlg  = GMM_FALSE;
        g_GmmAuthenCtrl.ucRandStoredFlg = GMM_FALSE;

        Gmm_TimerStop(GMM_TIMER_T3316);

        g_MmSubLyrShare.GmmShare.ucPsIntegrityProtect =
                                        NAS_MML_RRC_INTEGRITY_PROTECT_ACTIVE;

    }
    else if ((RRC_SECURITY_DEL_CS_PS_KEY == pStSecurityInd->ulRptMode)
        || (RRC_SECURITY_DEL_PS_KEY == pStSecurityInd->ulRptMode))
    {
        NAS_MML_SetSimPsSecurityCksn(NAS_MML_CKSN_INVALID);
        NAS_MML_InitPsSecurityUmtsCkInvalid();
        NAS_MML_InitPsSecurityUmtsIkInvalid();
    }
    else
    {
    }

}


VOS_VOID Gmm_RcvServiceAcceptMsg(
                             NAS_MSG_FOR_PCLINT_STRU *pMsg
                             )
{

    NAS_MSG_STRU        *pGmmStatus;
    VOS_UINT32           ulPDPStatus;

    ulPDPStatus = 0;

    if (pMsg->ulNasMsgSize < GMM_MSG_LEN_SERVICE_ACCEPT)
    {                                                                           /* 空中接口长度非法                         */

        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvServiceAcceptMsg:WARNING: Length of SERVICE ACCEPT is invalid");
        pGmmStatus = Gmm_GmmStatusMsgMake(NAS_MML_REG_FAIL_CAUSE_INVALID_MANDATORY_INF);

        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH , pGmmStatus);

        return;
    }

    if ( (VOS_TRUE == NAS_UTRANCTRL_IsUtranPsSmcNeeded())
      && (GMM_SERVICE_REQUEST_DATA_CONN != g_GmmGlobalCtrl.ucSpecProc))
    {
        return;
    }

    /* 24008_CR1735R3_(Rel-10)_C1-111529 was 1470 was 1012 24008-a10 24008 4.7.5.1.5章节描述如下:
    If in addition the ROUTING AREA UPDATE REQUEST message indicated "periodic updating",
    -   in Iu mode, the timer T3311 may be stopped when the MS enters PMM-CONNECTED mode;
    -   in A/Gb mode, the timer T3311 may be stopped when the READY timer is started.
    TDS下没有SMC流程所以在service accept这再判断下是否需要停止T3311定时器 */
    NAS_GMM_StopT3311InIuPmmConnMode_T3312Exp();

    Gmm_TimerStop(GMM_TIMER_T3316);                                             /* 停止T3316                                */

    g_GmmAuthenCtrl.ucResStoredFlg  = GMM_FALSE;                                /* 将"RES存在标志 "置为0                    */
    g_GmmAuthenCtrl.ucRandStoredFlg = GMM_FALSE;                                /* 将"RAND存在标志 "置为0                   */

    switch (g_GmmGlobalCtrl.ucState)
    {                                                                           /* 根据GMM不同的状态，进行相应的处理        */
    case GMM_SERVICE_REQUEST_INITIATED:
        if (pMsg->ulNasMsgSize >= (GMM_MSG_LEN_SERVICE_ACCEPT + NAS_GMM_IE_LEN_PDP_STATUS))
        {
            if (GMM_IEI_PDP_CONTEXT_STATUS == pMsg->aucNasMsg[GMM_SR_ACCEPT_IE_PDP_CONTEXT_STATUS])
            {
                /* PDP status是TLV类型的IE,所以要跳过类型和长度获取PDP status */
                ulPDPStatus = (pMsg->aucNasMsg[GMM_SR_ACCEPT_IE_PDP_CONTEXT_STATUS + 3] << 8) | \
                            pMsg->aucNasMsg[GMM_SR_ACCEPT_IE_PDP_CONTEXT_STATUS + 2];

                Gmm_SndSmPdpStatusInd(ulPDPStatus, GMM_SM_CAUSE_SERVICE_ACCEPT);
            }
        }
        if ( (GMM_SERVICE_REQUEST_DATA_CONN == g_GmmGlobalCtrl.ucSpecProc)
          || (GMM_SERVICE_REQUEST_DATA_IDLE == g_GmmGlobalCtrl.ucSpecProc))
        {
          Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_SUCCESS);                 /* 发送GMMRABM_REESTABLISH_CNF(success)     */
        }

        /* RABM触发的 Service Request 流程成功后，如果还有缓存的RABM
           重建消息，那么不需要再次向网侧发送，清除掉即可。 */
        if (GMM_MSG_HOLD_FOR_SERVICE
            == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SERVICE))
        {                                                                           /* 如果有保留的SR原语                       */
            g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SERVICE;      /* 清除缓存标志                             */
            Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForService);
        }

        Gmm_TimerStop(GMM_TIMER_T3317);                                         /* 停T3317                                  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */
        Gmm_TimerStart(GMM_TIMER_T3319);                                        /* 启动3319                                 */

        Gmm_ComStaChg(g_GmmGlobalCtrl.ucServPreSta);                            /* 调用状态的公共处理                       */
        NAS_GMM_SndMmGmmActionResultInd(GMMMM_ACTION_SUCCESS,
                                        NAS_MML_REG_FAIL_CAUSE_NULL);                                     /* 发送MMCGMM_GMM_ACTION_RESULT_IND()       */


        /* 向MMC发送service request结果 */
        NAS_GMM_SndMmcServiceRequestResultInd(GMM_MMC_ACTION_RESULT_SUCCESS,
                                              NAS_MML_REG_FAIL_CAUSE_NULL);
        /* 事件上报 */
        NAS_EventReport(WUEPS_PID_GMM,
                        NAS_OM_EVENT_DATA_SERVICE_ACC,
                        VOS_NULL_PTR,
                        NAS_OM_EVENT_NO_PARA);

        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                        /* 清当前进行的specific流程                 */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvServiceAcceptMsg:INFO: specific procedure ended");
        if (GMM_TIMER_T3311_FLG
            == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3311_FLG))
        {                                                                       /* 存在被挂起的T3311                        */
            Gmm_TimerResume(GMM_TIMER_T3311);                                   /* 恢复T3311                                */
        }
        else if (GMM_TIMER_T3302_FLG
            == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3302_FLG))
        {                                                                       /* 存在被挂起的T3302                        */
            Gmm_TimerResume(GMM_TIMER_T3302);                                   /* 恢复T3302                                */
        }
        else
        {
        }

        if ( GMM_TRUE == g_GmmServiceCtrl.ucSmsFlg)
        {                                                                       /* SMS在等待响应                            */
            Gmm_SndSmsEstCnf();                                                 /* 发送PMMSMS_EST_CNF                       */
            g_GmmServiceCtrl.ucSmsFlg = GMM_FALSE;
        }

        if (0 != g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk)
        {                                                                       /* 有保留的消息                             */
            Gmm_DealWithBuffAfterProc();
        }
        g_GmmServiceCtrl.ucSmFlg = GMM_FALSE;
        break;

    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvServiceAcceptMsg:WARNING: SERVICE ACCEPT is unexpected");
        pGmmStatus = Gmm_GmmStatusMsgMake(NAS_MML_REG_FAIL_CAUSE_MSG_TYPE_NOT_COMPATIBLE);

        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH , pGmmStatus);
        break;
    }
}


VOS_VOID  Gmm_RcvServiceRejectMsg_Cause_Handling(VOS_UINT8 ucRejectCause)
{
    /*保存被拒绝的错误码*/
    NAS_GMM_SetAttach2DetachErrCode(NAS_GMM_TransGmmNwCause2GmmSmCause(ucRejectCause));

    switch (ucRejectCause)
    {
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        Gmm_ServiceReqRejectCasue3(ucRejectCause);
        break;

    
    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
        Gmm_ServiceReqRejectCasue3(ucRejectCause);
        break;

    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
        Gmm_ServiceReqRejectCasue7();
        break;
    case NAS_MML_REG_FAIL_CAUSE_MS_ID_NOT_DERIVED:
        Gmm_ServiceReqRejectCasue9();
        break;
    case NAS_MML_REG_FAIL_CAUSE_IMPLICIT_DETACHED:
        Gmm_ServiceReqRejectCasue10();
        break;
    case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
        Gmm_ServiceReqRejectCasue11();
        break;
    case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        Gmm_ServiceReqRejectCasue12();
        break;
    case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
        Gmm_ServiceReqRejectCasue13(ucRejectCause);
        break;
    case NAS_MML_REG_FAIL_CAUSE_NO_PDP_CONTEXT_ACT:
        Gmm_ServiceReqRejectCasue40();
        break;
    default:
        Gmm_ServiceReqRejectTheOtherCause(ucRejectCause);
        break;
    }
    return;

}


VOS_VOID Gmm_RcvServiceRejectMsg(
                             NAS_MSG_FOR_PCLINT_STRU *pMsg
                             )
{
    VOS_UINT8                           ucRejectCause;                                         /* 拒绝原因                                 */
    NAS_MSG_STRU                       *pGmmStatus;
    VOS_UINT8                           ucDellRejectEnableFlg;

    /* 获取拨号被拒定制是否使能 */
    ucDellRejectEnableFlg = NAS_MML_GetDailRejectCfg();

    if (pMsg->ulNasMsgSize < GMM_MSG_LEN_SERVICE_REJECT)
    {                                                                           /* 空中接口长度非法                         */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvServiceRejectMsg:WARNING: Length of SERVICE REJECT is invalid");
        pGmmStatus = Gmm_GmmStatusMsgMake(NAS_MML_REG_FAIL_CAUSE_INVALID_MANDATORY_INF);
        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH , pGmmStatus);
        return;
    }

    if (GMM_SERVICE_REQUEST_INITIATED != g_GmmGlobalCtrl.ucState)
    {                                                                           /* GMM状态= GMM-SERVICE-REQUEST-INITIATED   */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvServiceRejectMsg:WARNING: SERVICE REJECT is unexpected");
        pGmmStatus = Gmm_GmmStatusMsgMake(NAS_MML_REG_FAIL_CAUSE_MSG_NOT_COMPATIBLE);

        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH , pGmmStatus);
        return;
    }

    if ((GMM_SERVICE_REQUEST_DATA_CONN == g_GmmGlobalCtrl.ucSpecProc)
         ||(GMM_SERVICE_REQUEST_DATA_IDLE == g_GmmGlobalCtrl.ucSpecProc))
    {                                                                           /* service request type=data                */
        Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);                 /* 发送GMMRABM_REESTABLISH_CNF(failure)     */
    }
    Gmm_TimerStop(GMM_TIMER_T3317);                                             /* 停T3317                                  */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* 停止T3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* 停止T3320                                */
    Gmm_TimerStop(GMM_TIMER_T3316);                                             /* 停止T3316                                */

    g_GmmAuthenCtrl.ucResStoredFlg  = GMM_FALSE;                                /* 将"RES存在标志 "置为0                    */
    g_GmmAuthenCtrl.ucRandStoredFlg = GMM_FALSE;                                /* 将"RAND存在标志 "置为0                   */
    NAS_GMM_ChangePsSerRejCauseAvoidInvalidSim(&(pMsg->aucNasMsg[2]));

    ucRejectCause = *(pMsg->aucNasMsg + 2);

    /*服务拒绝原因为15时，不给SM回失败，也不清除SM消息缓冲，等搜网注册后再回结果。*/
    if ((VOS_FALSE == NAS_USIMMAPI_IsTestCard())
     && (NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL == ucRejectCause)
     && (VOS_FALSE == ucDellRejectEnableFlg))
    {
        g_GmmServiceCtrl.ucRejCauseVaildFlg = GMM_TRUE;  /* reject casue valid*/
        g_GmmServiceCtrl.ucRejCause         = ucRejectCause;

        Gmm_RcvServiceRejectMsg_Cause_Handling(ucRejectCause);
        NAS_GMM_CheckCauseToStartT3340(ucRejectCause);

        g_GmmServiceCtrl.ucRejCauseVaildFlg = GMM_FALSE;    /* 处理完成 */

        return;
    }
    NAS_NORMAL_LOG(WUEPS_PID_GMM, "Gmm_RcvServiceRejectMsg(): Service reject, clear msg cached buffer");

    Gmm_HoldBufferFree();                                                       /* 清除保留消息                             */

    if (GMM_TRUE == g_GmmServiceCtrl.ucSmsFlg)
    {                                                                           /* SMS在等待响应                            */
        g_GmmServiceCtrl.ucSmsFlg = GMM_FALSE;
        /* 如果已经缓存有SMS消息,则释放原来的缓存 */
        if (GMM_MSG_HOLD_FOR_SMS
            == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &GMM_MSG_HOLD_FOR_SMS))
        {                                                                       /* 如果有保留的EST_REQ原语           */
            g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SMS;      /* 清除缓存标志                             */
            Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSMS);               /* 将保留buffer中所有的消息释放             */
            g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSMS = (VOS_UINT32)NULL;
        }
        Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);                              /* 发送PMMSMS_ERROR_IND                     */
    }

    if ((GMM_SERVICE_REQUEST_SIGNALLING == g_GmmGlobalCtrl.ucSpecProc)
     && (GMM_TRUE == g_GmmServiceCtrl.ucSmFlg))
    {
        /* 服务拒绝原因为 9，10，不向SM发送拒绝消息，但要清除SM消息缓冲，等ATTACH完成后立即做PDP激活 */
        if ((NAS_MML_REG_FAIL_CAUSE_MS_ID_NOT_DERIVED != ucRejectCause)
         && (NAS_MML_REG_FAIL_CAUSE_IMPLICIT_DETACHED != ucRejectCause))
        {
            /* service reject 被拒原因值定制NV打开时，对于40不能回复失败 */
            if (((NAS_MML_REG_FAIL_CAUSE_NO_PDP_CONTEXT_ACT != ucRejectCause)
              && (VOS_TRUE == ucDellRejectEnableFlg))
             || (VOS_FALSE == ucDellRejectEnableFlg))
            {
                GMM_SndSmServiceRej(NAS_GMM_TransGmmNwCause2GmmSmCause(ucRejectCause));
            }
        }

        g_GmmServiceCtrl.ucSmFlg = GMM_FALSE;
    }

    if (ucRejectCause == NAS_MML_REG_FAIL_CAUSE_NO_PDP_CONTEXT_ACT)
    {
        Gmm_SndSmPdpStatusInd(0, GMM_SM_CAUSE_NO_PDP_CONTEXT_ACT);
    }

    g_GmmServiceCtrl.ucRejCauseVaildFlg = GMM_TRUE;  /* reject casue valid*/
    g_GmmServiceCtrl.ucRejCause         = ucRejectCause;

    Gmm_RcvServiceRejectMsg_Cause_Handling(ucRejectCause);
    NAS_GMM_CheckCauseToStartT3340(ucRejectCause);

    g_GmmServiceCtrl.ucRejCauseVaildFlg = GMM_FALSE;    /* 处理完成 */
    return;
}


VOS_VOID Gmm_ServiceReqRejectCasue3(
                                VOS_UINT8 ucCause                               /* 失败原因                                 */
                                )
{
    NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_PLMN_NOT_ALLOWED);      /* update status设为GU3                     */
    NAS_MML_SetSimPsRegStatus(VOS_FALSE);
    Gmm_DelPsLocInfoUpdateUsim();
    Gmm_ComStaChg(GMM_DEREGISTERED_NO_IMSI);                                    /* 调用状态的公共处理                       */

    /* 清除相关标志 */
    NAS_GMM_ClearIMSIOfUeID();

    NAS_GMM_SndMmGmmActionResultInd(GMMMM_ACTION_FAILURE, ucCause);/* 发送MMCGMM_GMM_ACTION_RESULT_IND()       */


    /* 向MMC发送service request结果 */
    NAS_GMM_SndMmcServiceRequestResultInd(GMM_MMC_ACTION_RESULT_FAILURE,
                                          ucCause);
    /* 事件上报 */
    NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_DATA_SERVICE_REJ,
                    (VOS_VOID*)(&ucCause),
                    NAS_OM_EVENT_SERVICE_REJ_LEN);

    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                            /* 清当前流程                               */
    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_ServiceReqRejectCasue3:INFO: SERVICE REJECT is unexpected");
    g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;                        /* 清保留流程                               */

    Gmm_TimerStop(GMM_TIMER_T3311);                                             /* 停T3311                                  */
    Gmm_TimerStop(GMM_TIMER_T3302);                                             /* 停T3302                                  */

}


VOS_VOID Gmm_ServiceReqRejectCasue7(VOS_VOID)
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause;

    enCause = NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW;

    NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_PLMN_NOT_ALLOWED);      /* update status设为GU3                     */
    NAS_MML_SetSimPsRegStatus(VOS_FALSE);
    Gmm_DelPsLocInfoUpdateUsim();
    Gmm_ComStaChg(GMM_DEREGISTERED_NO_IMSI);                                    /* 调用状态的公共处理                       */

    /* 清除相关标志 */
    NAS_GMM_ClearIMSIOfUeID();

    NAS_GMM_SndMmGmmActionResultInd(GMMMM_ACTION_FAILURE,
                                    enCause);                                 /* 发送MMCGMM_GMM_ACTION_RESULT_IND()       */


    /* 向MMC发送service request结果 */
    NAS_GMM_SndMmcServiceRequestResultInd(GMM_MMC_ACTION_RESULT_FAILURE,
                                          enCause);
    /* 事件上报 */
    NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_DATA_SERVICE_REJ,
                    (VOS_VOID*)&enCause,
                    NAS_OM_EVENT_SERVICE_REJ_LEN);

    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                            /* 清当前流程                               */
    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_ServiceReqRejectCasue7:INFO: specific procedure ended");
    g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;                        /* 清保留流程                               */

    Gmm_TimerStop(GMM_TIMER_T3311);                                             /* 停T3311                                  */
    Gmm_TimerStop(GMM_TIMER_T3302);                                             /* 停T3302                                  */

}

VOS_VOID Gmm_ServiceReqRejectCasue9(VOS_VOID)
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause;

    enCause = NAS_MML_REG_FAIL_CAUSE_MS_ID_NOT_DERIVED;

    NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_NOT_UPDATED);         /* update status设为GU2                     */

    Gmm_DelPsLocInfoUpdateUsim();
    Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);                             /* 调用状态的公共处理                       */
    /* 事件上报 */
    NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_DATA_SERVICE_REJ,
                    (VOS_VOID*)&enCause,
                    NAS_OM_EVENT_SERVICE_REJ_LEN);

    Gmm_TimerStop(GMM_TIMER_T3311);                                             /* 停T3311                                  */
    Gmm_TimerStop(GMM_TIMER_T3302);                                             /* 停T3302                                  */

#if (FEATURE_ON == FEATURE_LTE)

    NAS_GMM_SetLteGutiValid(VOS_FALSE);
#endif

    Gmm_Attach_Prepare();
    Gmm_AttachInitiate(GMM_NULL_PROCEDURE);                                     /* 进行attach                               */

#if (FEATURE_ON == FEATURE_LTE)
    NAS_GMM_SetLteGutiValid(VOS_TRUE);
#endif
}

VOS_VOID Gmm_ServiceReqRejectCasue10(VOS_VOID)
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause;
    enCause = NAS_MML_REG_FAIL_CAUSE_IMPLICIT_DETACHED;
    Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);                             /* 调用状态的公共处理                       */

    /* 事件上报 */
    NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_DATA_SERVICE_REJ,
                    (VOS_VOID*)&enCause,
                    NAS_OM_EVENT_SERVICE_REJ_LEN);

    Gmm_TimerStop(GMM_TIMER_T3311);                                             /* 停T3311                                  */
    Gmm_TimerStop(GMM_TIMER_T3302);                                             /* 停T3302                                  */

    Gmm_Attach_Prepare();
    Gmm_AttachInitiate(GMM_NULL_PROCEDURE);                                     /* 进行attach                               */
}

VOS_VOID Gmm_ServiceReqRejectCasue11(VOS_VOID)
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause;

    enCause = NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW;

    NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_ROUTING_AREA_NOT_ALLOWED);      /* update status设为GU3:PLMN not allowed    */

    g_GmmGlobalCtrl.SysInfo.ucForbMask |= GMM_FORBIDDEN_PLMN;                   /* 设置禁止注册列表标志                     */
    Gmm_DelPsLocInfoUpdateUsim();

    Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                            /* 调用状态的公共处理                       */
    NAS_GMM_SndMmGmmActionResultInd(GMMMM_ACTION_FAILURE,
                                    enCause);                                 /* 发送MMCGMM_GMM_ACTION_RESULT_IND()       */


    /* 向MMC发送service request结果 */
    NAS_GMM_SndMmcServiceRequestResultInd(GMM_MMC_ACTION_RESULT_FAILURE,
                                          enCause);
    /* 事件上报 */
    NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_DATA_SERVICE_REJ,
                    (VOS_VOID*)&enCause,
                    NAS_OM_EVENT_SERVICE_REJ_LEN);

    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                            /* 清当前流程                               */
    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_ServiceReqRejectCasue11:INFO: specific procedure ended");
    g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;                        /* 清保留流程                               */

    Gmm_TimerStop(GMM_TIMER_T3311);                                             /* 停T3311                                  */
    Gmm_TimerStop(GMM_TIMER_T3302);                                             /* 停T3302                                  */

}

VOS_VOID Gmm_ServiceReqRejectCasue12(VOS_VOID)
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16   enCause;

    enCause                             = NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW;
    NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_ROUTING_AREA_NOT_ALLOWED);      /* update status设为GU3                     */
    g_GmmGlobalCtrl.SysInfo.ucForbMask |= GMM_FORBIDDEN_LA_FOR_REG_PRVS_SVS;    /* 设置禁止注册列表标志                     */
    Gmm_DelPsLocInfoUpdateUsim();

    g_GmmGlobalCtrl.ucLaNotAllowFlg = GMM_TRUE;
    Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                            /* 调用状态的公共处理                       */
    NAS_GMM_SndMmGmmActionResultInd(GMMMM_ACTION_FAILURE,
                                    enCause);                                 /* 发送MMCGMM_GMM_ACTION_RESULT_IND         */


    /* 向MMC发送service request结果 */
    NAS_GMM_SndMmcServiceRequestResultInd(GMM_MMC_ACTION_RESULT_FAILURE,
                                          enCause);
    /* 事件上报 */
    NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_DATA_SERVICE_REJ,
                    (VOS_VOID*)&enCause,
                    NAS_OM_EVENT_SERVICE_REJ_LEN);

    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                            /* 清当前流程                               */
    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_ServiceReqRejectCasue12:INFO: specific procedure ended");
    g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;                        /* 清保留流程                               */

    Gmm_TimerStop(GMM_TIMER_T3311);                                             /* 停T3311                                  */
    Gmm_TimerStop(GMM_TIMER_T3302);                                             /* 停T3302                                  */

}

VOS_VOID Gmm_ServiceReqRejectCasue13(
                             VOS_UINT8 ucCause                                  /* 失败原因                                 */
                             )
{
    NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_ROUTING_AREA_NOT_ALLOWED);      /* update status设为GU3                     */
    g_GmmGlobalCtrl.SysInfo.ucForbMask |= GMM_FORBIDDEN_LA_FOR_ROAM;            /* 设置禁止注册列表标志                     */

    if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
    {
        Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* 更新SIM卡信息                            */
    }
    else
    {
        Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
    }

    Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                              /* 调用状态的公共处理                       */
    NAS_GMM_SndMmGmmActionResultInd(GMMMM_ACTION_FAILURE,
                                    ucCause);                                /* 发送MMCGMM_GMM_ACTION_RESULT_IND()       */


    /* 向MMC发送service request结果 */
    NAS_GMM_SndMmcServiceRequestResultInd(GMM_MMC_ACTION_RESULT_FAILURE,
                                          ucCause);
    /* 事件上报 */
    NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_DATA_SERVICE_REJ,
                    (VOS_VOID*)&ucCause,
                    NAS_OM_EVENT_SERVICE_REJ_LEN);

    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                            /* 清当前流程                               */
    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_ServiceReqRejectCasue13:INFO: specific procedure ended");
    g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;                        /* 清保留流程                               */

    Gmm_TimerStop(GMM_TIMER_T3311);                                             /* 停T3311                                  */
    Gmm_TimerStop(GMM_TIMER_T3302);                                             /* 停T3302                                  */

}


VOS_VOID Gmm_ServiceReqRejectCasue40(VOS_VOID)
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause;
    enCause = NAS_MML_REG_FAIL_CAUSE_NO_PDP_CONTEXT_ACT;
    Gmm_ComStaChg(g_GmmGlobalCtrl.ucServPreSta);                                /* 调用状态的公共处理                       */

    NAS_GMM_SndMmGmmActionResultInd(GMMMM_ACTION_FAILURE,
                                    enCause);                                 /* 发送MMCGMM_GMM_ACTION_RESULT_IND()       */


    /* 向MMC发送service request结果 */
    NAS_GMM_SndMmcServiceRequestResultInd(GMM_MMC_ACTION_RESULT_FAILURE,
                                          enCause);
    /* 事件上报 */
    NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_DATA_SERVICE_REJ,
                    (VOS_VOID*)&enCause,
                    NAS_OM_EVENT_SERVICE_REJ_LEN);

    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                            /* 清当前流程                               */
    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_ServiceReqRejectCasue40:INFO: specific procedure ended");

    if (GMM_TIMER_T3311_FLG
        == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3311_FLG))
    {                                                                           /* 存在被挂起的T3311                        */
        Gmm_TimerResume(GMM_TIMER_T3311);                                       /* 恢复T3311                                */
    }
    else if (GMM_TIMER_T3302_FLG
        == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3302_FLG))
    {                                                                           /* 存在被挂起的T3302                        */
        Gmm_TimerResume(GMM_TIMER_T3302);                                       /* 恢复T3302                                */
    }
    else
    {
    }
}

VOS_VOID Gmm_ServiceReqRejectTheOtherCause(
                                       VOS_UINT8 ucCause                        /* 拒绝原因值                               */
                                       )
{

    Gmm_ComStaChg(g_GmmGlobalCtrl.ucServPreSta);                                /* 调用状态的公共处理                       */
    NAS_GMM_SndMmGmmActionResultInd(GMMMM_ACTION_FAILURE,
                                    ucCause);                        /* 发送MMCGMM_GMM_ACTION_RESULT_IND()       */

    /* 向MMC发送service request结果 */
    NAS_GMM_SndMmcServiceRequestResultInd(GMM_MMC_ACTION_RESULT_FAILURE,
                                          ucCause);
    /* 事件上报 */
    NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_DATA_SERVICE_REJ,
                    (VOS_VOID*)&ucCause,
                    NAS_OM_EVENT_SERVICE_REJ_LEN);

    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                            /* 清当前流程                               */
    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_ServiceReqRejectTheOtherCause:INFO: specific procedure ended");
    if (GMM_TIMER_T3311_FLG
        == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3311_FLG))
    {                                                                           /* 存在被挂起的T3311                        */
        Gmm_TimerResume(GMM_TIMER_T3311);                                       /* 恢复T3311                                */
    }
    else if (GMM_TIMER_T3302_FLG
        == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3302_FLG))
    {                                                                           /* 存在被挂起的T3302                        */
        Gmm_TimerResume(GMM_TIMER_T3302);                                       /* 恢复T3302                                */
    }
    else
    {
    }
}

NAS_MSG_STRU *Gmm_ServiceRequestMsgMake()
{
    NAS_MSG_FOR_PCLINT_STRU            *ptrNasMsg;
    NAS_MSG_STRU                       *pNasMsg;
    VOS_UINT8                           ucTotalLen = GMM_MSG_LEN_SERVICE_REQUEST;       /* 空中接口消息的长度                       */
    VOS_UINT8                           ucServiceType;                                  /* 暂时变量                                 */
    VOS_UINT8                           i;                                              /* 循环控制变量                             */

    VOS_UINT32                          ulPdpCtxStatus;
    NAS_MML_PS_BEARER_CONTEXT_STRU     *pstPsBearerCtx;

    pstPsBearerCtx = NAS_MML_GetPsBearerCtx();

    /* 固定IE: PDP context status IE */
    ucTotalLen += 4;

    pNasMsg = (NAS_MSG_STRU *)Gmm_MemMalloc((sizeof(NAS_MSG_STRU)
                                              + ucTotalLen) - 4);               /* 申请内存空间                             */
    if (VOS_NULL_PTR == pNasMsg)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_ServiceRequestMsgMake:WARNING: Alloc memory fail.");
        return pNasMsg;
    }

    ptrNasMsg = (NAS_MSG_FOR_PCLINT_STRU *)pNasMsg;

    ptrNasMsg->ulNasMsgSize = ucTotalLen;
    ptrNasMsg->aucNasMsg[0] = GMM_PD_GMM;                                       /* GMM_PD_GMM为：0x0080                     */
    ptrNasMsg->aucNasMsg[1] = GMM_MSG_SERVICE_REQUEST;                          /* GMM_MSG_SERVICE_REQUEST为：12            */

    /* 得到service 的type */
    if (GMM_SERVICE_REQUEST_SIGNALLING == g_GmmGlobalCtrl.ucSpecProc)
    {                                                                           /* 当前进行的specific流程是GMM_SERVICE_REQU *
                                                                                 * EST_SIGNALLING/                          */
        ucServiceType = GMM_SERVICE_TYPE_SIGNALLING;
    }
    else if (GMM_SERVICE_REQUEST_PAGING_RSP == g_GmmGlobalCtrl.ucSpecProc)
    {                                                                           /* 当前进行的specific流程是GMM_SERVICE_REQU *
                                                                                 * EST_PAGING_RSP                           */
        ucServiceType = GMM_SERVICE_TYPE_PAGING_RSP;
    }
    else
    {                                                                           /* 当前进行的specific流程是service "data"   */
        ucServiceType = GMM_SERVICE_TYPE_DATA;
    }

    
    if (VOS_TRUE == NAS_MML_IsNeedClearPsCksn_UsimDoneGsmPsAuth())
    {
        NAS_MML_SetSimPsSecurityCksn(MM_CKSN_INVALID);

        NAS_MML_SetUsimDoneGsmPsAuthFlg(VOS_FALSE);
    }
    
    ptrNasMsg->aucNasMsg[2] =
        (VOS_UINT8)((NAS_MML_GetSimPsSecurityCksn() & 0x07) |
                                        ((ucServiceType & 0x07) << 4));         /* 对ptrNasMsg->aucNasMsg[2]赋值            */
    ptrNasMsg->aucNasMsg[3] = 5;                                                /* ptrNasMsg-> aucNasMsg[3]= P_TMSI的长度   */
    ptrNasMsg->aucNasMsg[4] = GMM_MOBILE_ID_TMSI_PTMSI | 0xF0;                  /* 对ptrNasMsg-> aucNasMsg[4]进行填充       */

    if (GMM_UEID_P_TMSI
        == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask & GMM_UEID_P_TMSI))
    {
        PS_MEM_CPY(&ptrNasMsg->aucNasMsg[5],
                   NAS_MML_GetUeIdPtmsi(),
                   NAS_MML_MAX_PTMSI_LEN);                                         /* P_TMSI赋值                               */
    }
    else
    {
        for (i=0; i<4; i++)
        {                                                                       /* 对P_TMSI进行填空                         */
            ptrNasMsg->aucNasMsg[5 + i] = GMM_PTMSI_INVALID;
        }
    }

    ptrNasMsg->aucNasMsg[9]   = GMM_IEI_PDP_CONTEXT_STATUS;
    ptrNasMsg->aucNasMsg[10]  = 2;

    NAS_GMM_ConvertPdpCtxStatusToNetworkPdpCtxStatus(pstPsBearerCtx, &ulPdpCtxStatus);
    ptrNasMsg->aucNasMsg[11] = (VOS_UINT8)(ulPdpCtxStatus & 0xE0);
    ptrNasMsg->aucNasMsg[12] = (VOS_UINT8)(ulPdpCtxStatus >> NAS_MML_OCTET_MOVE_EIGHT_BITS);

    /* 发起Service Request流程，更新GMM链路释放控制变量 */
    NAS_GMM_UpdateGmmLinkCtrlStru();
    g_GmmServiceCtrl.ucRetrySrForRelCtrlFlg = VOS_FALSE;
    g_GmmServiceCtrl.ucServiceRequestProc = g_GmmGlobalCtrl.ucSpecProc;

    return (NAS_MSG_STRU *)ptrNasMsg;
}


NAS_MSG_STRU *Gmm_ServiceRequestMsgMake_ForData(
    VOS_UINT16                          usUplinkDataStatus,
    VOS_UINT16                          usPdpContextStatus
)
{
    NAS_MSG_FOR_PCLINT_STRU            *ptrNasMsg;
    NAS_MSG_STRU                       *pNasMsg;
    VOS_UINT8                           ucTotalLen = GMM_MSG_LEN_SERVICE_REQUEST;       /* 空中接口消息的长度                       */
    VOS_UINT8                           ucServiceType;                                  /* 暂时变量                                 */
    VOS_UINT8                           i;                                              /* 循环控制变量                             */
    VOS_INT8                            cVersion;

    VOS_UINT32                          ulPdpCtxStatus;
    NAS_MML_PS_BEARER_CONTEXT_STRU     *pstPsBearerCtx;

    pstPsBearerCtx = NAS_MML_GetPsBearerCtx();

    cVersion = NAS_Common_Get_Supported_3GPP_Version(MM_COM_SRVDOMAIN_PS);

    /* 固定IE: PDP context status IE */
    ucTotalLen += 4;

    #if(PS_UE_REL_VER >= PS_PTL_VER_R7)
    if (cVersion >= PS_PTL_VER_R7)
    {
        /* 可选IE: Uplink data status IE */
        ucTotalLen += 4;
    }
    #endif
    pNasMsg = (NAS_MSG_STRU *)Gmm_MemMalloc((sizeof(NAS_MSG_STRU)
                                              + ucTotalLen) - 4);                 /* 申请内存空间                             */
    if (VOS_NULL_PTR == pNasMsg)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_ServiceRequestMsgMake_ForData:WARNING: Alloc memory fail.");
        return pNasMsg;
    }

    ptrNasMsg = (NAS_MSG_FOR_PCLINT_STRU *)pNasMsg;

    ptrNasMsg->ulNasMsgSize = ucTotalLen;
    ptrNasMsg->aucNasMsg[0] = GMM_PD_GMM;                                         /* GMM_PD_GMM为：0x0080                     */
    ptrNasMsg->aucNasMsg[1] = GMM_MSG_SERVICE_REQUEST;                            /* GMM_MSG_SERVICE_REQUEST为：12            */

    /* 得到service 的type */
    if (GMM_SERVICE_REQUEST_SIGNALLING == g_GmmGlobalCtrl.ucSpecProc)
    {                                                                             /* 当前进行的specific流程是GMM_SERVICE_REQU *
                                                                                 * EST_SIGNALLING                           */
        ucServiceType = GMM_SERVICE_TYPE_SIGNALLING;
    }
    else if (GMM_SERVICE_REQUEST_PAGING_RSP == g_GmmGlobalCtrl.ucSpecProc)
    {                                                                             /* 当前进行的specific流程是GMM_SERVICE_REQU *
                                                                                 * EST_PAGING_RSP                           */
        ucServiceType = GMM_SERVICE_TYPE_PAGING_RSP;
    }
    else
    {                                                                             /* 当前进行的specific流程是service "data"   */
        ucServiceType = GMM_SERVICE_TYPE_DATA;
    }

    
    if (VOS_TRUE == NAS_MML_IsNeedClearPsCksn_UsimDoneGsmPsAuth())
    {
        NAS_MML_SetSimPsSecurityCksn(MM_CKSN_INVALID);

        NAS_MML_SetUsimDoneGsmPsAuthFlg(VOS_FALSE);
    }
        
    ptrNasMsg->aucNasMsg[2] =
        (VOS_UINT8)((NAS_MML_GetSimPsSecurityCksn() & 0x07) |
                                        ((ucServiceType & 0x07) << 4));           /* 对ptrNasMsg->aucNasMsg[2]赋值            */
    ptrNasMsg->aucNasMsg[3] = 5;                                                  /* ptrNasMsg-> aucNasMsg[3]= P_TMSI的长度   */
    ptrNasMsg->aucNasMsg[4] = GMM_MOBILE_ID_TMSI_PTMSI | 0xF0;                    /* 对ptrNasMsg-> aucNasMsg[4]进行填充       */

    if (GMM_UEID_P_TMSI
        == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask & GMM_UEID_P_TMSI))
    {
        Gmm_MemCpy(&ptrNasMsg->aucNasMsg[5],
                   NAS_MML_GetUeIdPtmsi(),
                   NAS_MML_MAX_PTMSI_LEN);                                         /* P_TMSI赋值                               */
    }
    else
    {
        for (i=0; i<4; i++)
        {                                                                         /* 对P_TMSI进行填空                         */
            ptrNasMsg->aucNasMsg[5 + i] = GMM_PTMSI_INVALID;
        }
    }

    ptrNasMsg->aucNasMsg[9]   = GMM_IEI_PDP_CONTEXT_STATUS;
    ptrNasMsg->aucNasMsg[10]  = 2;

    /* TDD模式下,需要根据RABM通知的PDP STATUS上报网络 */
    if (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
    {
        NAS_GMM_ConvertPdpCtxStatusToNetworkPdpCtxStatus(pstPsBearerCtx, &ulPdpCtxStatus);
        ptrNasMsg->aucNasMsg[11] = (VOS_UINT8)(ulPdpCtxStatus & 0xE0);
        ptrNasMsg->aucNasMsg[12] = (VOS_UINT8)(ulPdpCtxStatus >> NAS_MML_OCTET_MOVE_EIGHT_BITS);
    }
    else
    {
        ptrNasMsg->aucNasMsg[11] = (VOS_UINT8)(usPdpContextStatus & 0xE0);                           /* b4~b0:00000                              */
        ptrNasMsg->aucNasMsg[12] = (VOS_UINT8)((usPdpContextStatus >> 8) & 0xFF);
    }

    #if(PS_UE_REL_VER >= PS_PTL_VER_R7)
    if (cVersion >= PS_PTL_VER_R7)
    {
        ptrNasMsg->aucNasMsg[13] = GMM_IEI_UPLINK_DATA_STATUS;
        ptrNasMsg->aucNasMsg[14] = 2;
        ptrNasMsg->aucNasMsg[15]
            = (VOS_UINT8)(usUplinkDataStatus & 0xE0);                           /* b4~b0:00000                              */
        ptrNasMsg->aucNasMsg[16] = (VOS_UINT8)((usUplinkDataStatus >> 8) & 0xFF);
    }
    #endif

    /* 发起Service Request流程，更新GMM链路释放控制变量 */
    NAS_GMM_UpdateGmmLinkCtrlStru();
    g_GmmServiceCtrl.ucRetrySrForRelCtrlFlg = VOS_FALSE;
    g_GmmServiceCtrl.ucServiceRequestProc = g_GmmGlobalCtrl.ucSpecProc;

    return (NAS_MSG_STRU *)ptrNasMsg;
}


VOS_VOID Gmm_RcvSmsUnitdataReq(
                           VOS_VOID    *pMsg                                    /* 消息指针                                 */
                           )
{
    PMMSMS_UNITDATA_REQ_STRU *pPmmSmsDataReq;                                   /* PMMSMS_UNITDATA_REQ_STRU类型指针         */

    pPmmSmsDataReq = (PMMSMS_UNITDATA_REQ_STRU *)pMsg;

    if (GMM_STATUS_DETACHED == g_MmSubLyrShare.GmmShare.ucAttachSta)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvSmsUnitdataReq:WARNING: PS signalling connection is invalid");
        Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);                              /* 通知SMS信令连接不存在                    */
        return;
    }

    if (GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg)
    {                                                                           /* 信令连接存在                             */
        if ((GMM_NULL_PROCEDURE != g_GmmGlobalCtrl.ucSpecProc)
            && (0x40 != (g_GmmGlobalCtrl.ucSpecProc & 0x40))
            && (0x20 != (g_GmmGlobalCtrl.ucSpecProc & 0x20)))
        {
            Gmm_SndSmsErrorInd(GMM_SMS_SPEC_PROC_ONGOING);                      /* 通知SMS GMM正在进行流程                  */
        }
        else
        {
            Gmm_SndRrmmDataReqForCm(RRC_NAS_MSG_PRIORTY_LOW,
                                    &pPmmSmsDataReq->SmsMsg);                   /* 发送 RRMM_DATA_REQ                       */
        }
    }
    else
    {
        Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);                              /* 通知SMS信令连接不存在                    */
    }
}

/*******************************************************************************
  Module   : NAS_GMM_BufferSmsEstReq
  Function : 缓存收到的原语PMMSMS_EST_REQ
  Input    : VOS_VOID       *pMsg   指向原语的指针
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 欧阳飞  2010.01.07  新规作成
*******************************************************************************/
VOS_VOID NAS_GMM_BufferSmsEstReq(
    VOS_VOID                            *pMsg
)
{
    PMMSMS_EST_REQ_STRU *ptr;                                           /* 缓存消息指针              */

    if (GMM_FALSE == g_GmmGlobalCtrl.ucFollowOnFlg)
    {
        g_GmmServiceCtrl.ucSmsFlg = GMM_TRUE;                           /* 记录有SMS请求标志  */
        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

        g_GmmGlobalCtrl.ucSpecProcHold = GMM_SERVICE_REQUEST_SIGNALLING;
        g_GmmGlobalCtrl.ulEstCause = ((PMMSMS_EST_REQ_STRU *)pMsg)->ulEstCause;
    }
    else
    {
        ptr = (PMMSMS_EST_REQ_STRU *)Gmm_MemMalloc(sizeof(PMMSMS_EST_REQ_STRU));
        if (VOS_NULL_PTR == ptr)
        {
              PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Gmm_RcvSmsEstReq:ERROR: Memory is not allocated");
              return;
        }

        Gmm_MemCpy(ptr, pMsg, sizeof(PMMSMS_EST_REQ_STRU));
        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSMS = (VOS_UINT32)ptr;      /* 保留该原语                               */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_SMS;   /* 填写GMM_MSG_HOLD_STRU类型的变量          */
    }

}


VOS_VOID NAS_GMM_RcvSmsEstReq_RegUptNeededNormalSrv(
    PMMSMS_EST_REQ_STRU                *pstGmmSmsEstReq
)
{
    NAS_MSG_STRU                       *pstNasMsg = VOS_NULL_PTR;

    g_GmmGlobalCtrl.ulEstCause = pstGmmSmsEstReq->ulEstCause;

    if ((gstGmmCasGlobalCtrl.ucLastDataSender != NAS_MML_GetCurrNetRatType())
     && (GMM_RAU_FOR_WAITSERVICE == gstGmmSuspendCtrl.ucRauCause))
    {
        return;
    }

    /* 如果此前GMM在建连接的过程中由于RAI改变而主动要求释放正在建立的连接，
       那么对于在等待接入层的连接释放指示以及连接释放指示之后上报的系统消息
       过程中收到的上层请求需要缓存
       或者T3340正在运行，当前流程正在拆线，缓存SMS请求 */
    if (GMM_TRUE == g_GmmGlobalCtrl.ucRaiChgRelFlg)
    {
        NAS_GMM_BufferSmsEstReq(pstGmmSmsEstReq);
        return;
    }

    g_GmmServiceCtrl.ucSmsFlg = GMM_TRUE;                                       /* 记录标志待信令连接建立成功后给SMS回响应  */

    if (GMM_TIMER_T3302_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3302_FLG))
    {                                                                           /* T3302正在运行                            */
        Gmm_TimerPause(GMM_TIMER_T3302);                                        /* 挂起T3302                                */
    }

    else if (GMM_TIMER_T3311_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3311_FLG))
    {                                                                           /* T3311正在运行                            */
        Gmm_TimerPause(GMM_TIMER_T3311);                                        /* 挂起T3311                                */
    }
    else
    {
    }

    /* 迁移GMM状态 */
    g_GmmGlobalCtrl.ucServPreSta = g_GmmGlobalCtrl.ucState;
    GMM_CasFsmStateChangeTo(GMM_SERVICE_REQUEST_INITIATED);

    g_MmSubLyrShare.GmmShare.ucDeatchEnableFlg = GMM_DETACH_ABLE;
    g_GmmGlobalCtrl.ucSpecProc = GMM_SERVICE_REQUEST_SIGNALLING;                /* 存储当前的流程                           */

    pstNasMsg = Gmm_ServiceRequestMsgMake();                                    /* 调用service request制作函数              */
    Gmm_SndRrmmEstReq(pstGmmSmsEstReq->ulEstCause,
                      GMM_RRC_IDNNS_UNKNOWN,
                      pstNasMsg);                                               /* 进行service request(signalling)          */

    Gmm_TimerStart(GMM_TIMER_PROTECT_FOR_SIGNALING);
    NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_DATA_SERVICE_REQ,
                    VOS_NULL_PTR,
                    NAS_OM_EVENT_NO_PARA);

}

VOS_VOID Gmm_RcvSmsEstReq(
                      VOS_VOID    *pMsg                                         /* 消息指针                                 */
                      )
{
    NAS_MSG_STRU        *pNasMsg = VOS_NULL_PTR;                                /* 定义指针                                 */
    PMMSMS_EST_REQ_STRU *pPmmSmsEstReq;                                         /* PMMSMS_EST_REQ_STRU类型指针              */
    PMMSMS_EST_REQ_STRU *ptr;                                                   /* 缓存消息指针              */
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    enCurRat      = NAS_MML_GetCurrNetRatType();

    pPmmSmsEstReq = (PMMSMS_EST_REQ_STRU *)pMsg;

    if (GMM_MSG_HOLD_FOR_SMS
          == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &GMM_MSG_HOLD_FOR_SMS))
    {
                                                                                /* 已经缓存有SMS消息请求,则释放原来的缓存 */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SMS;          /* 清除缓存标志                             */
        Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSMS);                   /* 将保留buffer中所有的消息释放             */
        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSMS = (VOS_UINT32)NULL;
    }

    if (VOS_TRUE == NAS_MML_GetPsRestrictNormalServiceFlg())
    {
        /* 通知SMS建链失败 */
        Gmm_SndSmsErrorInd(GMM_SMS_SPEC_PROC_ONGOING);
        return;
    }

    if ((GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg)
        && ((GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
          ||(GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM ==
                                                g_GmmGlobalCtrl.ucState)))
    {                                                                           /* 信令连接存在,且不在GMM过程中                             */
        if ((GMM_TIMER_T3340_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3340_FLG))
         || (VOS_TRUE == gstGmmCasGlobalCtrl.ucRauCmpFlg))
        {
            NAS_GMM_BufferSmsEstReq(pMsg);
            return;
        }

        g_GmmServiceCtrl.ucSmsFlg = GMM_FALSE;                                  /* SMS请求已处理，清除标志  */
        Gmm_SndSmsEstCnf();                                                     /* 发送 PMMSMS_EST_CNF                      */
    }
    else
    {
        switch (g_GmmGlobalCtrl.ucState)
        {                                                                       /* GMM状态                                  */
        case GMM_SERVICE_REQUEST_INITIATED:
            g_GmmServiceCtrl.ucSmsFlg = GMM_TRUE;                               /* 记录有SMS请求标志  */
            break;
        case GMM_ROUTING_AREA_UPDATING_INITIATED:
        case GMM_REGISTERED_IMSI_DETACH_INITIATED:
            /* 当前有GMM流程，置SMS标志位，缓存该原语。 */
            g_GmmServiceCtrl.ucSmsFlg = GMM_TRUE;                               /* 记录有SMS请求标志  */

            ptr = (PMMSMS_EST_REQ_STRU *)Gmm_MemMalloc(sizeof(PMMSMS_EST_REQ_STRU));
            if (VOS_NULL_PTR == ptr)
            {
                  PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Gmm_RcvSmsEstReq:ERROR: Memory is not allocated");
                  return;
            }
            Gmm_MemCpy(ptr, pMsg, sizeof(PMMSMS_EST_REQ_STRU));
            g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSMS = (VOS_UINT32)ptr;          /* 保留该原语                               */
            g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_SMS;       /* 填写GMM_MSG_HOLD_STRU类型的变量          */
            break;

        case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
            Gmm_RcvCmServReq_RegAtmpToUpdt(pMsg);
            break;
        case GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH:
            Gmm_RcvCmServReq_DeregAtmpToAtch(pMsg);
            break;
        case GMM_REGISTERED_NORMAL_SERVICE:
        case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
            g_GmmGlobalCtrl.ulEstCause = pPmmSmsEstReq->ulEstCause;

            if ((GMM_RAU_FOR_WAITSERVICE == gstGmmSuspendCtrl.ucRauCause)
             && (gstGmmCasGlobalCtrl.ucLastDataSender != enCurRat)
#if (FEATURE_ON == FEATURE_LTE)
          && (gstGmmCasGlobalCtrl.ucLastDataSender != NAS_MML_NET_RAT_TYPE_LTE)
#endif
             )
            {
                GMM_LOG_INFO("Gmm_RcvSmsEstReq:Inter System change, Exec select RAU.");

                /*GMM_BufferMsgReceive(pMsg);*/
                g_GmmServiceCtrl.ucSmsFlg = GMM_TRUE;                           /* 记录有SMS请求标志  */
                g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
                NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

                g_GmmGlobalCtrl.ucSpecProcHold = GMM_SERVICE_REQUEST_SIGNALLING;

                Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
                return;
            }
            /* 如果此前GMM在建连接的过程中由于RAI改变而主动要求释放正在建立的连接，
               那么对于在等待接入层的连接释放指示以及连接释放指示之后上报的系统消息
               过程中收到的上层请求需要缓存
               或者T3340正在运行，当前流程正在拆线，缓存SMS请求 */

            if (GMM_TRUE == g_GmmGlobalCtrl.ucRaiChgRelFlg)
            {
                NAS_GMM_BufferSmsEstReq(pMsg);
                return;
            }

            g_GmmServiceCtrl.ucSmsFlg = GMM_TRUE;                               /* 记录标志待信令连接建立成功后给SMS回响应  */
            if (GMM_TIMER_T3302_FLG
                == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3302_FLG))
            {                                                                   /* T3302正在运行                            */
                Gmm_TimerPause(GMM_TIMER_T3302);                                /* 挂起T3302                                */
            }

            else if (GMM_TIMER_T3311_FLG
                == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3311_FLG))

            {                                                                   /* T3311正在运行                            */
                Gmm_TimerPause(GMM_TIMER_T3311);                                /* 挂起T3311                                */
            }
            else
            {
            }
            g_GmmGlobalCtrl.ucServPreSta = g_GmmGlobalCtrl.ucState;

            GMM_CasFsmStateChangeTo(GMM_SERVICE_REQUEST_INITIATED);

            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvSmsEstReq:NORMAL: STATUS IS GMM_SERVICE_REQUEST_INITIATED");

            g_MmSubLyrShare.GmmShare.ucDeatchEnableFlg = GMM_DETACH_ABLE;

            g_GmmGlobalCtrl.ucSpecProc = GMM_SERVICE_REQUEST_SIGNALLING;        /* 存储当前的流程                           */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvSmsEstReq:INFO: SR(signaling) procedure started");

            pNasMsg = Gmm_ServiceRequestMsgMake();                              /* 调用service request制作函数              */

            Gmm_SndRrmmEstReq(pPmmSmsEstReq->ulEstCause,
                              GMM_RRC_IDNNS_UNKNOWN,
                              pNasMsg);                                         /* 进行service request(signalling)          */

            Gmm_TimerStart(GMM_TIMER_PROTECT_FOR_SIGNALING);
            NAS_EventReport(WUEPS_PID_GMM,
                            NAS_OM_EVENT_DATA_SERVICE_REQ,
                            VOS_NULL_PTR,
                            NAS_OM_EVENT_NO_PARA);
            break;
        case GMM_REGISTERED_UPDATE_NEEDED:
            if (MM_COM_SRVST_NORMAL_SERVICE == NAS_GMM_GetRegUptNeededPsSrvStatus())
            {
                /* 发起请求 */
                NAS_GMM_RcvSmsEstReq_RegUptNeededNormalSrv(pPmmSmsEstReq);
            }
            else
            {
                Gmm_SndSmsErrorInd(GMM_SMS_SPEC_PROC_ONGOING);
            }
            break;

        /* 背景搜网快速指定搜网过程中用户发送短信，GMM不缓存，回复error ind，不打断，后续靠短信重发机制再次触发短信*/
        case GMM_REGISTERED_PLMN_SEARCH:
            Gmm_SndSmsErrorInd(GMM_SMS_SPEC_PROC_ONGOING);
            break;

        case GMM_SUSPENDED_WAIT_FOR_SYSINFO:
            NAS_GMM_RcvSmsEstReq_SuspendWaitForSysinfo(pMsg);
            break;

        default:
            Gmm_SndSmsErrorInd(GMM_SMS_SPEC_PROC_ONGOING);
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvSmsEstReq:WARNING: Receive SMS Request in a not suitable state");
            break;
        }
    }
    return;
}

#if (FEATURE_ON == FEATURE_DSDS)

VOS_VOID NAS_GMM_ConvertSmsSessionTypeToRrc(
    GMMSMS_SESSION_TYPE_ENUM_UINT8      enGmmSmsSessionType,
    RRC_NAS_SESSION_TYPE_ENUM_UINT8    *pucRrcSessionType
)
{
    switch (enGmmSmsSessionType)
    {
        case GMMSMS_SESSION_TYPE_MO_SMS:
            *pucRrcSessionType = RRC_NAS_SESSION_TYPE_PS_MO_SMS;
            break;

        case GMMSMS_SESSION_TYPE_MT_SMS:
            *pucRrcSessionType = RRC_NAS_SESSION_TYPE_PS_MT_SMS;
            break;

        default:
            *pucRrcSessionType = RRC_NAS_SESSION_TYPE_BUTT;
            break;
    }
    return;
}
#endif 


VOS_VOID NAS_GMM_RcvSmsBeginSessionNotify_PreProc(
    GMMSMS_BEGIN_SESSION_NOTIFY_STRU   *pstBeginSessionMsg
)
{
#if (FEATURE_ON == FEATURE_DSDS)
    RRC_NAS_SESSION_TYPE_ENUM_UINT8     enRrcSessionType;
#endif

#if (FEATURE_ON == FEATURE_DSDS)
    if (GMMSMS_SESSION_TYPE_BUTT != pstBeginSessionMsg->enSessionType)
    {
        NAS_GMM_ConvertSmsSessionTypeToRrc(pstBeginSessionMsg->enSessionType, &enRrcSessionType);

        NAS_GMM_SndBeginSessionNotify(enRrcSessionType);
    }
#endif

    Gmm_TimerStop(GMM_TIMER_DELAY_PS_SMS_CONN_REL);                       

    return;
}


VOS_VOID NAS_GMM_RcvSmsEndSessionNotify_PreProc(
    GMMSMS_END_SESSION_NOTIFY_STRU     *pstEndSessionMsg
)
{
#if (FEATURE_ON == FEATURE_DSDS)
    RRC_NAS_SESSION_TYPE_ENUM_UINT8     enRrcSessionType;
#endif

#if (FEATURE_ON == FEATURE_DSDS)
    if (GMMSMS_SESSION_TYPE_BUTT != pstEndSessionMsg->enSessionType)
    {
        NAS_GMM_ConvertSmsSessionTypeToRrc(pstEndSessionMsg->enSessionType, &enRrcSessionType);

        NAS_GMM_SndEndSessionNotify(enRrcSessionType);
    }
#endif

    if (VOS_TRUE == NAS_GMM_IsNeedProcDelayPsSmsConnRelTimer())
    {
        Gmm_TimerStart(GMM_TIMER_DELAY_PS_SMS_CONN_REL);
    }

    return;
}


VOS_VOID NAS_GMM_RcvSmsEstReq_SuspendWaitForSysinfo(
    VOS_VOID                            *pMsg
)
{
    if (VOS_FALSE == NAS_MML_GetSimPsRegStatus())
    {
        Gmm_SndSmsErrorInd(GMM_SMS_SPEC_PROC_ONGOING);
        return;
    }

    if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
    {
        Gmm_SndSmsErrorInd(GMM_SMS_SPEC_PROC_ONGOING);
        return;
    }

    /* 在从G切换到W时,需要首先发起RAU恢复PS,然后处理缓冲的SM消息 */
    if ((NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
     && (MMC_SUSPEND_CAUSE_HANDOVER == gstGmmSuspendCtrl.ucSuspendCause)
     && (NAS_MML_NET_RAT_TYPE_GSM   == gstGmmSuspendCtrl.ucPreRat))
    {
        g_GmmServiceCtrl.ucSmsFlg = GMM_TRUE;                           /* 记录有SMS请求标志  */
        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

        g_GmmGlobalCtrl.ucSpecProcHold = GMM_SERVICE_REQUEST_SIGNALLING;


        /* 如果等系统消息定时器在运行，则不下发RAU */
        if (NAS_GMM_TIMER_HO_WAIT_SYSINFO_FLG == (NAS_GMM_TIMER_HO_WAIT_SYSINFO_FLG & g_GmmTimerMng.ulTimerRunMask))
        {
            return;
        }

        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
    }

    return;
}


VOS_VOID NAS_GMM_RcvRabmMmlProcStatusQryReq(
    struct MsgCB                       *pMsg
)
{
    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus;
    RABM_GMM_MML_PROC_STATUS_STRU       stMmlProcStatus;
    RABM_GMM_MML_PROC_STATUS_QRY_REQ_STRU   *pstQryMsg;

    PS_MEM_SET(&stMmlProcStatus, 0, sizeof(stMmlProcStatus));
    pstQryMsg = (RABM_GMM_MML_PROC_STATUS_QRY_REQ_STRU *)pMsg;

    stMmlProcStatus.enOptFlag = pstQryMsg->enOptFlag;

    /* 获取当前GMM是否有专有流程 */
    stMmlProcStatus.bitOpGmmSpecificProcedure = NAS_GMM_IsInRegisterProcedure();

    /* 取得当前的链接信息 */
    pstConnStatus = NAS_MML_GetConnStatus();
    stMmlProcStatus.bitOpCsSignal = pstConnStatus->ucCsSigConnStatusFlg;

    /* 获取是否当前存在PS域短信 */
    /* 当前GMM没有维护当前是否有PS短信流程的处理，如要能维护，需要增加
       消息流程，SMS修改点比较散，由于时间紧迫，这里暂时先用API调用*/
    if (VOS_TRUE == NAS_SMS_IsPsDomainIdle())
    {
        stMmlProcStatus.bitOpPsSmsService = VOS_FALSE;
    }

    /* 调用函数NAS_GMM_SndRabmMmlProcStatusQryCnf回复结果 */
    NAS_GMM_SndRabmMmlProcStatusQryCnf(&stMmlProcStatus);
}


VOS_VOID NAS_GMM_ChangePsSerRejCauseAvoidInvalidSim(VOS_UINT8 *pucRcvMsg)
{
    NAS_MML_PLMN_ID_STRU               *pstCurrCampPlmnId    = VOS_NULL_PTR;
    VOS_UINT32                          bIsRegisteredInHplmn = VOS_FALSE;

    /* 增加测试卡保护，测试卡时不修改，直接返回 */
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_GMM_ChangeDetachCauseAvoidInvalidSim: The sim is Test card");
        return;
    }

    NAS_MML_SetOriginalRejectCause(*pucRcvMsg);
    /* 取得当前驻留的PLMN ID */
    pstCurrCampPlmnId    = NAS_MML_GetCurrCampPlmnId();
    bIsRegisteredInHplmn = NAS_MML_ComparePlmnIdWithHplmn(pstCurrCampPlmnId);

    if (VOS_TRUE == bIsRegisteredInHplmn)
    {
        /* HPLMN */
        NAS_GMM_HandleHplmnRejCauseChange(NAS_MML_CHANGE_REJ_TYPE_PS_SER_REJ, pucRcvMsg);
    }
    else
    {
        /* VPLMN */
        NAS_GMM_HandleVplmnRejCauseChange(NAS_MML_CHANGE_REJ_TYPE_PS_SER_REJ, pucRcvMsg);
    }
}

/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

