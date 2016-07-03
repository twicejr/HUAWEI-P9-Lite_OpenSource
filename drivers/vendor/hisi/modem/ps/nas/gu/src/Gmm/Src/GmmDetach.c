

#include "GmmInc.h"
#include "GmmCasGlobal.h"
#include "GmmCasComm.h"
#include "GmmCasSend.h"
#include "GmmCasGsm.h"
#include "NasCommDef.h"
#include "GmmCasSuspend.h"

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
#define    THIS_FILE_ID        PS_FILE_ID_GMM_DETACH_C
/*lint +e767 修改人:luojian 107747;检视人:sunshaohua*/

/*lint -save -e958 */



VOS_VOID NAS_GMM_SaveDetachMsg(VOS_VOID *pMsg)
{
    MMCGMM_DETACH_REQ_STRU      *pDetachMsg = VOS_NULL_PTR;

    /* 已经有缓冲的detach消息时,以最后一个detach消息为准
       此处不考虑detach类型不同的情况 */
    if ((VOS_NULL_PTR != g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach)
     && (GMM_MSG_HOLD_FOR_DETACH == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_DETACH)))
    {
        Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach);
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_DETACH;
    }

    pDetachMsg = (MMCGMM_DETACH_REQ_STRU *)Gmm_MemMalloc(sizeof(MMCGMM_DETACH_REQ_STRU));
    if (VOS_NULL_PTR == pDetachMsg)
    {
          PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "NAS_GMM_SaveDetachMsg:ERROR: Allocate memory error in Gmm_RcvMmcDetachReq");
          return;
    }
    Gmm_MemCpy(pDetachMsg, pMsg, sizeof(MMCGMM_DETACH_REQ_STRU));
    g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach = (VOS_UINT32)pDetachMsg;
    g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_DETACH;
}


VOS_UINT32 NAS_GMM_DeleteSavedDetachMsg(
    NAS_GMM_DETACH_TYPE_ENUM_UINT32     ulDelDetachType
)
{
    MMCGMM_DETACH_REQ_STRU             *pstMsDetach = VOS_NULL_PTR;
    NAS_GMM_DETACH_TYPE_ENUM_UINT32     ulGmmDetach;

    if ( ( GMM_MSG_HOLD_FOR_DETACH == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_DETACH) )
      && ((VOS_NULL_PTR            != g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach)) )
    {
         pstMsDetach = (MMCGMM_DETACH_REQ_STRU *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach;

         /* 获取缓存的DETACH类型 */
         ulGmmDetach = pstMsDetach->enDetachType;

          /* 如果缓存的需要删除域的DETACH,则清除缓存的Detach消息 */
        if ( ulDelDetachType == (ulGmmDetach & ulDelDetachType) )
        {
            g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_DETACH;   /* 清除缓存标志                             */
            Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach);
            g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach = VOS_NULL_PTR;
        }

        return VOS_TRUE;
    }

    return VOS_FALSE;

}


VOS_VOID NAS_GMM_RcvMmcGmmDetachReqMsg_GmmRegisteredInitiated(
    VOS_VOID                           *pMsg
)
{
    VOS_UINT32                          ulDetachType;                                  /* 定义detach类型                           */
    MMCGMM_DETACH_REQ_STRU             *pMsDetach       = VOS_NULL_PTR;                                     /* 定义指针                                 */

    pMsDetach    = (MMCGMM_DETACH_REQ_STRU *)pMsg;                              /* 初始化指针                               */
    ulDetachType = pMsDetach->enDetachType;

    /* 正在建链过程中，则缓存去注册消息 */
    if ( (GMM_FALSE                 == g_GmmGlobalCtrl.ucSigConFlg)
      && (GMM_RRC_RRMM_EST_CNF_FLG  == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG)) )
    {                                                                       /* 无信令且正在建立信令连接                 */
        /* 缓存DETACH消息时候需要释放先前已缓存的DETACH消息，否则会导致内存泄露 */
        NAS_GMM_SaveDetachMsg(pMsg);

        return;                                                       /* 返回                                     */
    }

    /* 在联合注册过程中，则缓存消息,在联合注册过程结束后再处理 */
    if ( (GMM_ATTACH_COMBINED            == g_GmmGlobalCtrl.ucSpecProc)
      || (GMM_ATTACH_WHILE_IMSI_ATTACHED == g_GmmGlobalCtrl.ucSpecProc) )
    {
        if (MMC_GMM_PS_CS_DETACH != ulDetachType)
        {
            /* 在进行联合注册过程中,缓存消息,在联合注册过程结束后再处理 */
            NAS_GMM_SaveDetachMsg(pMsg);

            return;
        }
    }

    /* 网络模式I,如果当前CS域已处于DETACH状态，并且当前是CS与PS域的DETACH，则只进行PS ONLY DETACH */
    ulDetachType = NAS_GMM_ConvertDetachType(ulDetachType);

    Gmm_TimerStop(GMM_TIMER_T3310);                                             /* 停T3310                                  */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* 停止T3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* 停止T3320                                */
    g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;                                  /* 清除followon标志                         */
    NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

    if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
    {                                                                           /* ATTACH过程是由SM触发的                   */
        Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_PS_DETACH);      /* 通知SM GMM注册失败                       */
        g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;                                 /* 清ucSmCnfFlg标志                         */
    }

    if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
        == (g_GmmReqCnfMng.ucCnfMask
        & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
    {                                                                           /* 等待鉴权响应                             */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* 停保护定时器                             */
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;     /* 清除原语等待标志                         */
    }

    if (MMC_GMM_CS_DETACH != ulDetachType)
    {
        NAS_MML_SetPsAttachAllowFlg( VOS_FALSE );                               /* 设置禁止注册标志                         */
    }

    Gmm_MsInitNormalDetach(ulDetachType);

    return;

}



VOS_VOID NAS_GMM_RcvMmcGmmDetachReqMsg_GmmServiceReqInitiated(
    VOS_VOID                           *pMsg
)
{
    VOS_UINT32                          ulDetachType;                                  /* 定义detach类型                           */
    MMCGMM_DETACH_REQ_STRU             *pMsDetach       = VOS_NULL_PTR;                                     /* 定义指针                                 */

    pMsDetach    = (MMCGMM_DETACH_REQ_STRU *)pMsg;                              /* 初始化指针                               */
    ulDetachType = pMsDetach->enDetachType;

    /* 正在建链过程中，则缓存去注册消息 */
    if ( (GMM_FALSE                 == g_GmmGlobalCtrl.ucSigConFlg)
      && (GMM_RRC_RRMM_EST_CNF_FLG  == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG)) )
    {                                                                       /* 无信令且正在建立信令连接                 */
        /* 缓存DETACH消息时候需要释放先前已缓存的DETACH消息，否则会导致内存泄露 */
        NAS_GMM_SaveDetachMsg(pMsg);

        return;                                                       /* 返回                                     */
    }

    Gmm_TimerStop(GMM_TIMER_T3317);                                             /* 停T3317                                  */
    Gmm_TimerStop(GMM_TIMER_T3302);                                             /* 停止T3302                                */
    Gmm_TimerStop(GMM_TIMER_T3311);                                             /* 停止T3311                                */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* 停止T3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* 停止T3320                                */

    if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
        == (g_GmmReqCnfMng.ucCnfMask
        & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
    {                                                                           /* 等待鉴权响应                             */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* 停保护定时器                             */
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;     /* 清除原语等待标志                         */
    }

    if ((GMM_SERVICE_REQUEST_DATA_IDLE == g_GmmGlobalCtrl.ucSpecProc)
        ||(GMM_SERVICE_REQUEST_DATA_CONN == g_GmmGlobalCtrl.ucSpecProc))
    {                                                                           /* SR类型为data                             */
        Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);                 /* 向RABM发送结果                           */
    }
    if (GMM_TRUE == g_GmmServiceCtrl.ucSmsFlg)
    {
        Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);                              /* 发送PMMSMS_ERROR_IND                     */
        g_GmmServiceCtrl.ucSmsFlg = GMM_FALSE;
    }
    if (GMM_MSG_HOLD_FOR_SM
        ==(g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SM))
    {
        NAS_NORMAL_LOG(WUEPS_PID_GMM, "NAS_GMM_RcvMmcGmmDetachReqMsg_GmmServiceReqInitiated(): Clear cached SM Data Req");

        Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSm);
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SM;
    }

    /* 进行DETACH类型的转换 */
    ulDetachType = NAS_GMM_ConvertDetachType(ulDetachType);

    Gmm_MsInitNormalDetach(ulDetachType);                                       /* 调用MS启动的detach处理                   */

    return;

}


VOS_VOID NAS_GMM_LocalDetach_GmmDeregisteredNoImsi(VOS_VOID)
{
    NAS_MML_SetPsAttachAllowFlg( VOS_FALSE );     /* 设置禁止注册标志                         */

    /* 判断等待标志是否存在，如果存在则向MMC,MM发送DETACH信息 */
    if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
    {
        NAS_GMM_SndMmcMmDetachInfo();
    }

    /* 向MMC发送PS注册结果 */
    NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                 GMM_MMC_ACTION_RESULT_FAILURE,
                                 NAS_MML_REG_FAIL_CAUSE_SIM_INVALID);

    return;
}


VOS_VOID NAS_GMM_LocalDetach_GmmDeregisteredNormalService(VOS_VOID)
{
    NAS_MML_SetPsAttachAllowFlg( VOS_FALSE );     /* 设置禁止注册标志                         */

    /* 判断等待标志是否存在，如果存在则向MMC,MM发送DETACH信息 */
    if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
    {
        NAS_GMM_SndMmcMmDetachInfo();
    }
    else
    {
        /* 收到网侧的去注册成功后需要通知MM，否则MM不启动T3212定时器 */
        NAS_GMM_SndMmGprsDetachComplete();
    }

    /* 向MMC发送PS注册结果 */
    NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                 GMM_MMC_ACTION_RESULT_FAILURE,
                                 NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

    return;
}


VOS_VOID NAS_GMM_LocalDetach_GmmDeregisteredAttemptingToAttach(VOS_VOID)
{
    /* 通知MM模块 */
    if ((VOS_TRUE      == NAS_MML_GetCsAttachAllowFlg())
     && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod) )
    {
        NAS_GMM_SndMmLuInitiation(GMMMM_NO_TIMER_EXPIRED);
    }

    /* GMM进行本地DEACH */
    NAS_GMM_GprsLocalDetach();

    /* 迁移状态 */
    Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);                             /* 调用状态的公共处理                       */

    return;
}


VOS_VOID NAS_GMM_LocalDetach_GmmDeregisteredInitiated(VOS_VOID)
{
    /* 如果当前PS域已经去注册了，并且存在P-TMSI signature,则清除P-TMSI signature */
    if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
    {
        if (GMM_UEID_P_TMSI_SIGNATURE
            == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask & GMM_UEID_P_TMSI_SIGNATURE))
        {
            /* Upon completion of an MS initiated detach procedure, the used P-TMSI signature shall be deleted */
            g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI_SIGNATURE;

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
    }

    /* GMM本地去注册 */
    NAS_GMM_GprsLocalDetach();

    /* 迁移状态 */
    Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);

    return;
}


VOS_VOID NAS_GMM_LocalDetach_GmmRauInitiated(VOS_VOID)
{
    if (GMM_RAU_FOR_NORMAL != gstGmmSuspendCtrl.ucRauCause)
    {
        GMM_RauFailureInterSys();
    }
    else
    {
        GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_FAILURE);
    }

    Gmm_ComCnfHandle();

    /* GMM本地去注册 */
    NAS_GMM_GprsLocalDetach();

    /* 迁移状态 */
    Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);

    return;
}





VOS_VOID NAS_GMM_StartDetachProtectingTimer(
    MMCGMM_DETACH_REQ_STRU             *pstMsg
)
{
    /* Detach流程保护定时器时长 */
    VOS_UINT32                          ulDetachTimerVal;

    MMC_GMM_DETACH_TYPE_ENUM_UINT32     enDetachType;

    /* GMM的PS域Detach保护定时器运行状态 */
    VOS_UINT32                          ulPsDetachTimerStatus;

    if (MMC_GMM_DETACH_CAUSE_USER_DETACH == pstMsg->enDetachReason)
    {
        /* 用户触发的DETACH的时长: 90s */
        ulDetachTimerVal  = GMM_TIMER_PROTECT_DETACH_NOT_BY_SYSCFG_VALUE;
    }
    else
    {
        /* 如果当前是SYSCFG或服务域变化触发的DETACH,则设置保护定时器的时长为15s */
        ulDetachTimerVal  = GMM_TIMER_PROTECT_DETACH_BY_SYSCFG_VALUE;
    }


    /* 获取GMM的Detach保护定时器运行状态 */
    ulPsDetachTimerStatus = NAS_GMM_QryTimerStatus(GMM_TIMER_PROTECT_PS_DETACH);

    /* 默认当前启动的PS域DETACH */
    enDetachType         = MMC_GMM_PS_DETACH;

    enDetachType         = pstMsg->enDetachType;

    /* 如果当前不需要PS域的DETACH，则直接返回 */
    if ( MMC_GMM_PS_DETACH != (enDetachType & MMC_GMM_PS_DETACH) )
    {
        return;
    }

    /* 否则用户执行的是PS域DETACH,如果GMM的PS域Detach保护定时器未在运行，则启动PS域Detach保护定时器 */
    if ( VOS_FALSE         == ulPsDetachTimerStatus )
    {
        /* 设置GMM的CS域Detach保护定时器时长 */
        g_GmmTimerMng.aTimerInf[GMM_TIMER_PROTECT_PS_DETACH].ulTimerVal = ulDetachTimerVal;

        /* 启动GMM的PS域detach保护定时器 */
        Gmm_TimerStart(GMM_TIMER_PROTECT_PS_DETACH);
    }

    return;
}




VOS_VOID NAS_GMM_LocalDetach_GprsSuspension(VOS_VOID)
{
    /* 设置禁止注册标志                         */
    NAS_MML_SetPsAttachAllowFlg( VOS_FALSE );

    if (GMM_REGISTERED_NO_CELL_AVAILABLE == gstGmmSuspendCtrl.ucPreState)
    {
        gstGmmSuspendCtrl.ucPreState = GMM_DEREGISTERED_NO_CELL_AVAILABLE;
    }
    else if (GMM_DEREGISTERED_NO_IMSI != gstGmmSuspendCtrl.ucPreState)
    {
        gstGmmSuspendCtrl.ucPreState = GMM_DEREGISTERED_NORMAL_SERVICE;
    }
    else
    {

    }

    /* 判断等待标志是否存在，如果存在则向MMC,MM发送DETACH信息 */
    if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
    {
        NAS_GMM_SndMmcMmDetachInfo();
    }
    else
    {
        /* 收到网侧的去注册成功后需要通知MM，否则MM不启动T3212定时器 */
        NAS_GMM_SndMmGprsDetachComplete();
    }

    /* 向MMC发送PS注册结果 */
    NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                 GMM_MMC_ACTION_RESULT_FAILURE,
                                 NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

    NAS_GMM_SndSmStatusInd(GMM_SM_STATUS_DETACHED, GMM_SM_CAUSE_PS_DETACH);

    NAS_GMM_ClearMsgFromBuff(MMCGMM_ATTACH_REQ,WUEPS_PID_MMC,WUEPS_PID_GMM);
}


VOS_VOID NAS_GMM_GprsLocalDetachRelCsPsAllConn(VOS_VOID)
{
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enUtranMode;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurNetRatType;

    enUtranMode         = NAS_UTRANCTRL_GetCurrUtranMode();
    enCurNetRatType     = NAS_MML_GetCurrNetRatType();

    /* W下存在信令，则通知接入层进行链接释放 */
    if ((NAS_MML_NET_RAT_TYPE_WCDMA == enCurNetRatType )
     && ((GMM_TRUE                  == g_GmmGlobalCtrl.ucSigConFlg)
      || (GMM_RRC_RRMM_EST_CNF_FLG  == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG))))

    {
        /* SVLTE特性TDD模式使用新增原语通知tds连接释放 */
        if ((VOS_TRUE == NAS_MML_GetSvlteSupportFlag())
         && (NAS_UTRANCTRL_UTRAN_MODE_TDD == enUtranMode))
        {
            NAS_GMM_SndRrmmRelCsPsAllConnReq();
            return;
        }

        /* 非svlte场景使用rrmm_rel_req通知接入层连接释放 */
        Gmm_SndRrmmRelReq(RRC_CELL_UNBARRED);
    }

    return;
}



VOS_VOID NAS_GMM_GprsLocalDetach(VOS_VOID)
{

    NAS_GMM_GprsLocalDetachRelCsPsAllConn();

#if (FEATURE_LTE == FEATURE_ON)
    if (GMM_TIMER_T3312_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
    {
        NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
    }
#endif

    /* GMM停止保护定时器 */
    Gmm_TimerStop(GMM_TIMER_ALL);

    /* 设置禁止注册标志 */
    NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);

    /* 清除缓存的服务标志 */
    NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

    /* 清除followon标志 */
    g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;

    /* 清当前流程 */
    g_GmmGlobalCtrl.ucSpecProc    = GMM_NULL_PROCEDURE;

    /* G下清除层2相关数据 */
    if (GMM_TRUE == GMM_IsCasGsmMode())
    {
        Gmm_ClearLlcData(LL_GMM_CLEAR_DATA_TYPE_ALL);
    }

    /* 如果正在鉴权，则清除等待标志 */
    if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
        == (g_GmmReqCnfMng.ucCnfMask & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
    {
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;
    }

    /* 清除缓存的ATTACH标志 */
    NAS_GMM_ClearMsgFromBuff(MMCGMM_ATTACH_REQ, WUEPS_PID_MMC, WUEPS_PID_GMM);

    /* 判断等待标志是否存在，如果存在则向MMC,MM发送DETACH信息 */
    if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
    {
        NAS_GMM_SndMmcMmDetachInfo();
    }
    else
    {
        /* 收到网侧的去注册成功后需要通知MM，否则MM不启动T3212定时器 */
        NAS_GMM_SndMmGprsDetachComplete();
    }

    /* 向MMC发送PS注册结果 */
    NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                 GMM_MMC_ACTION_RESULT_FAILURE,
                                 NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);


    /* 挂起用户面，保证数据不再下发 */
    NAS_GMM_SndRabmSysSrvChgInd(NAS_MML_NET_RAT_TYPE_BUTT,
                                VOS_FALSE,
                                VOS_TRUE,
                                VOS_FALSE);

}


VOS_UINT32 NAS_GMM_IsNeedProcUserCsDetach(VOS_VOID)
{
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampInfo       = VOS_NULL_PTR;
    NAS_MML_NETWORK_INFO_STRU          *pstNetWorkInfo    = VOS_NULL_PTR;
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU   *pstForbidPlmnInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    pstForbidPlmnInfo = NAS_MML_GetForbidPlmnInfo();

    /* 获取当前网络模式 */
    pstCampInfo       = NAS_MML_GetCurrCampPlmnInfo();

    /* 获取当前的网络信息 */
    pstNetWorkInfo    =  NAS_MML_GetNetworkInfo();

    ulRet             = VOS_FALSE;


    /* 非网络模式I下，不用GMM处理用户发起的detach */
    if ( NAS_MML_NET_MODE_I != pstCampInfo->enNetworkMode )
    {
        return VOS_FALSE;
    }

    /* PS域不准许注册，不用GMM处理用户发起的detach */
    if ( VOS_FALSE == NAS_MML_GetPsAttachAllowFlg() )
    {
        return VOS_FALSE;
    }

    /* PS域注册首限，不用GMM处理用户发起的detach */
    if ( VOS_TRUE == NAS_MML_GetPsRestrictRegisterFlg() )
    {
        return VOS_FALSE;
    }

    /* PS 卡无效，不用GMM处理用户发起的detach */
    if ( VOS_FALSE == NAS_MML_GetSimPsRegStatus())
    {
        return VOS_FALSE;
    }

    /* 当前小区是否支持GPRS */
    if ( VOS_FALSE == pstNetWorkInfo->stPsDomainInfo.ucPsSupportFlg )
    {
        return VOS_FALSE;
    }

    /* 当前小区是否在FORB GPRS PLMN里面 */

    ulRet = NAS_MML_IsSimPlmnIdInDestBcchPlmnList( &(pstCampInfo->stLai.stPlmnId),
                                           pstForbidPlmnInfo->ucForbGprsPlmnNum,
                                           pstForbidPlmnInfo->astForbGprsPlmnList );
    if ( VOS_TRUE == ulRet )
    {
        return VOS_FALSE;
    }

    /* MM已处于ATTACHED状态，但当前GS接口不存在 */
    if ( (VOS_FALSE          == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
      && (MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState) )
    {
        return VOS_FALSE;
    }

    /* 否则用户发起的CS域的DETACH，可由GMM进行处理 */
    return VOS_TRUE;

}



NAS_GMM_DETACH_TYPE_ENUM_UINT32 NAS_GMM_ConvertDetachType(
    NAS_GMM_DETACH_TYPE_ENUM_UINT32     ulDetachType
)
{
    if (MMC_GMM_PS_CS_DETACH == ulDetachType)
    {                                                                           /* 是combined detach                        */
        if ( GMM_NET_MODE_I != g_GmmGlobalCtrl.ucNetMod )
        {                                                                       /* 当前是非A+I                              */
            return MMC_GMM_PS_DETACH;
        }

        if ( (MM_STATUS_DETACHED             == g_MmSubLyrShare.MmShare.ucCsAttachState)
          && (GMM_ATTACH_COMBINED            != g_GmmGlobalCtrl.ucSpecProc)
          && (GMM_ATTACH_WHILE_IMSI_ATTACHED != g_GmmGlobalCtrl.ucSpecProc) )
        {
            return MMC_GMM_PS_DETACH;                                           /* GMM只执行PS域的detach                    */
        }

        return MMC_GMM_PS_CS_DETACH;
    }

    /* 其它去注册类型保持不变 */
    return ulDetachType;

}




VOS_VOID NAS_Gmm_RcvMmCsLocalDetachInd_RegImsiDtchInit(VOS_VOID)
{
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* 停止T3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* 停止T3320                                */

    if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
        == (g_GmmReqCnfMng.ucCnfMask & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
    {                                                                           /* 等待鉴权响应                             */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* 停保护定时器                             */
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;     /* 清除原语等待标志                         */
    }

    Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);                               /* 调用状态的公共处理                       */
    g_GmmDetachCtrl.ucT3321OutCnt = 0;                                          /* T3321溢出次数清0                         */

    if (GMM_UEID_P_TMSI_SIGNATURE
        == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
        & GMM_UEID_P_TMSI_SIGNATURE))
    {                                                                           /* DETACH成功且使用了P_TMSI_SIGNATURE       */
        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
            &= ~GMM_UEID_P_TMSI_SIGNATURE;                                      /* 清除P_TMSI_SIGNATURE                     */

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
        g_GmmGlobalCtrl.stDetachInfo.enDetachType &= ~GMM_WAIT_CS_DETACH;
    }

    return;                                                                     /* 返回                                     */
}



VOS_VOID NAS_Gmm_RcvMmCsLocalDetachInd_RegInit(VOS_VOID)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;                           /* 当前的网络接入技术 */

    enCurRat = NAS_MML_GetCurrNetRatType();

    /* 当前处在联合RAU/attach过程中 */
    if ( (GMM_ATTACH_COMBINED            != g_GmmGlobalCtrl.ucSpecProc)
      && (GMM_ATTACH_WHILE_IMSI_ATTACHED != g_GmmGlobalCtrl.ucSpecProc) )
    {
        return ;
    }

    /* W下存在信令，则通知接入层进行链接释放 */
    if ( ( NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat )
      && ( (GMM_TRUE                  == g_GmmGlobalCtrl.ucSigConFlg)
        || (GMM_RRC_RRMM_EST_CNF_FLG  == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG)) ) )
    {
        Gmm_SndRrmmRelReq(RRC_CELL_UNBARRED);

    }

    return;                                                                     /* 返回                                     */
}




VOS_VOID NAS_Gmm_RcvMmCsLocalDetachInd_RauInit(VOS_VOID)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;                           /* 当前的网络接入技术 */

    enCurRat = NAS_MML_GetCurrNetRatType();

    /* 当前处在联合RAU/attach过程中 */
    if ( (GMM_RAU_COMBINED            != g_GmmGlobalCtrl.ucSpecProc)
      && (GMM_RAU_WITH_IMSI_ATTACH    != g_GmmGlobalCtrl.ucSpecProc) )
    {
        return ;
    }

    /* W下存在信令，则通知接入层进行链接释放 */
    if ( ( NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat )
      && ( (GMM_TRUE                  == g_GmmGlobalCtrl.ucSigConFlg)
        || (GMM_RRC_RRMM_EST_CNF_FLG  == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG)) )  )
    {
        Gmm_SndRrmmRelReq(RRC_CELL_UNBARRED);
    }

    return;                                                                     /* 返回                                     */
}


#if (FEATURE_MULTI_MODEM == FEATURE_ON)

VOS_VOID NAS_GMM_GprsLocalDetach_SvltePsTransfer(VOS_VOID)
{
    switch (g_GmmGlobalCtrl.ucState)
    {
        case GMM_REGISTERED_INITIATED:
        case GMM_ROUTING_AREA_UPDATING_INITIATED:
        case GMM_REGISTERED_IMSI_DETACH_INITIATED:
        case GMM_SERVICE_REQUEST_INITIATED:
            Gmm_ComStaChg(GMM_DEREGISTERED_NO_CELL_AVAILABLE);
            NAS_GMM_GprsLocalDetach();
            break;

        case GMM_REGISTERED_NORMAL_SERVICE:
        case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
            Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);
            NAS_GMM_GprsLocalDetach();
            break;

        case GMM_REGISTERED_PLMN_SEARCH:

            /* GMM进行本地DEACH */
            NAS_GMM_GprsLocalDetach();
            Gmm_ComStaChg(GMM_DEREGISTERED_PLMN_SEARCH);
            break;

        case GMM_REGISTERED_NO_CELL_AVAILABLE:

            /* GMM进行本地DEACH */
            NAS_GMM_GprsLocalDetach();
            Gmm_ComStaChg(GMM_DEREGISTERED_NO_CELL_AVAILABLE);
            break;

        case GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH:
        case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:

            NAS_GMM_LocalDetach_GmmDeregisteredAttemptingToAttach();
            break;

        case GMM_REGISTERED_UPDATE_NEEDED:

            /* GMM进行本地DEACH */
            NAS_GMM_GprsLocalDetach();

            /* 迁移状态 */
            Gmm_ComStaChg(GMM_DEREGISTERED_ATTACH_NEEDED);
            break;

        case GMM_REGISTERED_LIMITED_SERVICE:

            /* GMM进行本地DEACH */
            NAS_GMM_GprsLocalDetach();

            /* 迁移状态 */
            Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);
            break;

        case GMM_DEREGISTERED_NORMAL_SERVICE:
        case GMM_DEREGISTERED_LIMITED_SERVICE:
        case GMM_DEREGISTERED_ATTACH_NEEDED:
        case GMM_DEREGISTERED_NO_CELL_AVAILABLE:
        case GMM_DEREGISTERED_PLMN_SEARCH:

            /* GMM进行本地DEACH */
            NAS_GMM_LocalDetach_GmmDeregisteredNormalService();
            break;

        case GMM_DEREGISTERED_NO_IMSI:

            /* GMM进行本地DEACH */
            NAS_GMM_LocalDetach_GmmDeregisteredNoImsi();
            break;

        case GMM_SUSPENDED_NORMAL_SERVICE:
        case GMM_GPRS_SUSPENSION:
        case GMM_SUSPENDED_GPRS_SUSPENSION:

        /* 在GMM_SUSPENDED_WAIT_FOR_SYSINFO需增加进行本地Detach的处理 */
        case GMM_SUSPENDED_WAIT_FOR_SYSINFO:
            NAS_GMM_LocalDetach_GprsSuspension();
            break;

        /* 在Gmm_MsgDistribute_GMM_TC_ACTIVE状态已经处理 */
        case GMM_TC_ACTIVE:
            break;

        /* 在GMM_DEREGISTERED_INITIATED状态，收到PS域detach，则不处理 */
        case GMM_DEREGISTERED_INITIATED:

            return;

        default:
            NAS_GMM_GprsLocalDetach();

            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "WARNING: g_GmmGlobalCtrl.ucState is Abnormal");
            break;
    }


    /* 通知MM当前CS已本地去注册 */
    if ( (VOS_TRUE             == NAS_GMM_IsNeedProcUserCsDetach())
      && (GMM_WAIT_CS_DETACH   == (g_GmmGlobalCtrl.stDetachInfo.enDetachType & GMM_WAIT_CS_DETACH)) )
    {
        NAS_GMM_SndMmcMmDetachInfo();
        return;
    }

    return;
}
#endif




VOS_VOID Gmm_RcvMmcDetachReq(
                         VOS_VOID       *pMsg                                   /* 当前处理的消息                           */
                         )
{
    VOS_UINT32                   ulDetachType;                                  /* 定义detach类型                           */
    MMCGMM_DETACH_REQ_STRU      *pMsDetach;                                     /* 定义指针                                 */

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurNetRatType;
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enUtranMode;
    VOS_UINT8                           ucPsLocalDetachFlag;

    enUtranMode         = NAS_UTRANCTRL_GetCurrUtranMode();
    enCurNetRatType     = NAS_MML_GetCurrNetRatType();
    ucPsLocalDetachFlag = NAS_MML_GetPsLocalDetachFlag();
#endif

    pMsDetach    = (MMCGMM_DETACH_REQ_STRU *)pMsg;                              /* 初始化指针                               */
    ulDetachType = pMsDetach->enDetachType;                                     /* 初始化detach类型                         */


    ulDetachType = NAS_GMM_ConvertDetachType(ulDetachType);

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    /* svlte特性开启，且gmm收到mtc的rrc假丢网消息，modem0 ps要迁移到modem1时为了减少detach ps
       时间，直接进行本地ps detach不和网络交互 */
    if ((VOS_TRUE == NAS_MML_GetSvlteSupportFlag())
     && (NAS_UTRANCTRL_UTRAN_MODE_TDD == enUtranMode)
     && (NAS_MML_NET_RAT_TYPE_WCDMA == enCurNetRatType)
     && (VOS_TRUE == ucPsLocalDetachFlag)
     && (MMC_GMM_PS_DETACH == ulDetachType))
    {
        NAS_GMM_GprsLocalDetach_SvltePsTransfer();


        NAS_MML_SetPsLocalDetachFlag(VOS_FALSE);
        return;
    }
#endif

    switch (g_GmmGlobalCtrl.ucState)
    {                                                                           /* 判断当前状态进行不同处理                 */
    case GMM_REGISTERED_INITIATED:                                              /* GMM-REGISTERED-INITIATED状态             */

        /* GMM在GMM_REGISTERED_INITIATED状态收到DETACH REQ的处理 */
        NAS_GMM_RcvMmcGmmDetachReqMsg_GmmRegisteredInitiated(pMsg);
        return;

    case GMM_ROUTING_AREA_UPDATING_INITIATED:

        /* 在RAU过程中收到detach请求,缓冲此消息,在RAU完成后再进行DETACH操作 */
        NAS_GMM_SaveDetachMsg(pMsg);
        return;

    case GMM_REGISTERED_IMSI_DETACH_INITIATED:

        /* 在IMSI DETACH过程中收到detach请求,如果新的DETACH请求不是IMSI请求,
           缓冲此消息,在RAU完成后再进行DETACH操作 */
        if (MMC_GMM_CS_DETACH != ulDetachType)
        {
            NAS_GMM_SaveDetachMsg(pMsg);
        }
        return;

    case GMM_SERVICE_REQUEST_INITIATED:                                         /* GMM-SERVICE-REQUEST-INITIATED状态        */
        NAS_GMM_RcvMmcGmmDetachReqMsg_GmmServiceReqInitiated(pMsg);
        return;

    case GMM_REGISTERED_NORMAL_SERVICE:                                         /* GMM-REGISTERED.NORMAL-SERVIC状态         */
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:                                /* REGISTERED.ATTEMPTING-TO-UPDATE-MM状态   */
        NAS_GMM_ProcDetachReq_RegNmlServ(pMsDetach, ulDetachType);
        return;

    case GMM_REGISTERED_PLMN_SEARCH:                                            /* GMM-REGISTERED.PLMN-SEARCH状态           */
        if (MMC_GMM_CS_DETACH != ulDetachType)
        {
            /* GMM进行本地DEACH */
            NAS_GMM_GprsLocalDetach();

            Gmm_ComStaChg(GMM_DEREGISTERED_PLMN_SEARCH);
        }
        break;

    case GMM_REGISTERED_NO_CELL_AVAILABLE:                                      /* GMM-REGISTERED.NO-CELL-AVAILABLE状态     */
        if (MMC_GMM_CS_DETACH != ulDetachType)
        {
            /* GMM进行本地DEACH */
            NAS_GMM_GprsLocalDetach();

            Gmm_ComStaChg(GMM_DEREGISTERED_NO_CELL_AVAILABLE);
        }
        break;

    case GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:                                   /* GMM-REGISTERED.ATTEMPTING-TO-UPDATE状态  */
        if (MMC_GMM_CS_DETACH != ulDetachType)
        {
            NAS_GMM_LocalDetach_GmmDeregisteredAttemptingToAttach();
        }
        break;

    case GMM_REGISTERED_UPDATE_NEEDED:
        if (MMC_GMM_CS_DETACH != ulDetachType)
        {
            /* GMM进行本地DEACH */
            NAS_GMM_GprsLocalDetach();

            /* 迁移状态 */
            Gmm_ComStaChg(GMM_DEREGISTERED_ATTACH_NEEDED);
        }
        break;

    case GMM_REGISTERED_LIMITED_SERVICE:
        if (MMC_GMM_CS_DETACH != ulDetachType)
        {
            /* GMM进行本地DEACH */
            NAS_GMM_GprsLocalDetach();

            /* 迁移状态 */
            Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);
        }
        break;

    case GMM_DEREGISTERED_NORMAL_SERVICE:
    case GMM_DEREGISTERED_LIMITED_SERVICE:
    case GMM_DEREGISTERED_ATTACH_NEEDED:
    case GMM_DEREGISTERED_NO_CELL_AVAILABLE:
    case GMM_DEREGISTERED_PLMN_SEARCH:
        if (MMC_GMM_CS_DETACH != ulDetachType)
        {
            /* GMM进行本地DEACH */
            NAS_GMM_LocalDetach_GmmDeregisteredNormalService();
        }

        break;

    case GMM_DEREGISTERED_NO_IMSI:
        if (MMC_GMM_CS_DETACH != ulDetachType)
        {
            /* GMM进行本地DEACH */
            NAS_GMM_LocalDetach_GmmDeregisteredNoImsi();
        }

        break;

    case GMM_SUSPENDED_NORMAL_SERVICE:

    case GMM_GPRS_SUSPENSION:
    case GMM_SUSPENDED_GPRS_SUSPENSION:

    /* 在GMM_SUSPENDED_WAIT_FOR_SYSINFO需增加进行本地Detach的处理 */
    case GMM_SUSPENDED_WAIT_FOR_SYSINFO:

        if (MMC_GMM_CS_DETACH != ulDetachType)
        {
            NAS_GMM_LocalDetach_GprsSuspension();
        }

        break;

    /* 在Gmm_MsgDistribute_GMM_TC_ACTIVE状态已经处理 */
    case GMM_TC_ACTIVE:
        break;

    /* 在GMM_DEREGISTERED_INITIATED状态，收到PS域detach，则不处理 */
    case GMM_DEREGISTERED_INITIATED:
        if (MMC_GMM_CS_DETACH != ulDetachType)
        {
            return;
        }

        /* 统一处理CS域DETACH */
        break;

    default:
        if (MMC_GMM_CS_DETACH != ulDetachType)
        {
            NAS_GMM_GprsLocalDetach();
        }

        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcDetachReq:WARNING: g_GmmGlobalCtrl.ucState is Abnormal");
        break;
    }


    /* 通知MM当前CS已本地去注册 */
    if ( (VOS_TRUE             == NAS_GMM_IsNeedProcUserCsDetach())
      && (GMM_WAIT_CS_DETACH   == (g_GmmGlobalCtrl.stDetachInfo.enDetachType & GMM_WAIT_CS_DETACH)) )
    {
        NAS_GMM_SndMmcMmDetachInfo();
        return;
    }

    return;                                                                     /* 返回                                     */
}


VOS_VOID Gmm_RcvMmcDetachReq_RegNoCell(VOS_VOID)
{
    Gmm_ComStaChg(GMM_DEREGISTERED_NO_CELL_AVAILABLE);                          /* 调用状态的公共处理                       */
    NAS_MML_SetPsAttachAllowFlg( VOS_FALSE );              /* 设置PS域attach禁止标志                   */
    gstGmmCasGlobalCtrl.ucTlliAssignFlg = GMM_FALSE;

    /* 判断等待标志是否存在，如果存在则向MMC,MM发送DETACH信息 */
    if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
    {
        NAS_GMM_SndMmcMmDetachInfo();
    }


    /* 向MMC发送PS注册结果 */
    NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                 GMM_MMC_ACTION_RESULT_FAILURE,
                                 NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);
}


VOS_VOID Gmm_MsInitNormalDetach(
    VOS_UINT32                          ulDetachType                   /* detach类型                               */
)
{
    VOS_UINT8                           ucSimCsRegStatus;                       /* SIM卡CS域的注册结果导致的卡是否有效VOS_TRUE:CS域的卡有效,VOS_FALSE:CS域的卡无效*/

    ucSimCsRegStatus = NAS_MML_GetSimCsRegStatus();

    switch (ulDetachType)
    {                                                                           /* 判断detach类型进行不同处理               */
    case MMC_GMM_PS_CS_DETACH:                                                  /* combined detach                          */
        if((VOS_FALSE      == NAS_MML_GetCsRestrictRegisterFlg())
        && (VOS_TRUE       == ucSimCsRegStatus)
        && (GMM_NET_MODE_I == g_GmmGlobalCtrl.SysInfo.ucNetMod))
        {
            g_GmmGlobalCtrl.ucSpecProc = GMM_DETACH_COMBINED;                   /* 赋值当前spesific过程                     */
        }
        else
        {
            g_GmmGlobalCtrl.ucSpecProc = GMM_DETACH_NORMAL;
        }
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_MsInitNormalDetach:INFO: combined detach procedure started");

        GMM_CasFsmStateChangeTo(GMM_DEREGISTERED_INITIATED);                    /* 状态迁移到GMM DEREGISTERED INITIATED     */

        NAS_GMM_SndMmGprsDetachInitiation();                                       /* 向MMC发送MMCGMM_GPRS_DETACH_INITIATION   */
        Gmm_Com_MsInitNormalDetach();                                           /* 调用MS启动的detach的公共处理             */


        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_MsInitNormalDetach:NORMAL: STATUS IS GMM_DEREGISTERED_INITIATED");

        g_MmSubLyrShare.GmmShare.ucDeatchEnableFlg = GMM_DETACH_ABLE;
        break;
    case MMC_GMM_PS_DETACH:                                                     /* GPRS detach                              */
        g_GmmGlobalCtrl.ucSpecProc = GMM_DETACH_NORMAL;                         /* 赋值当前spesific过程                     */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_MsInitNormalDetach:INFO: normal detach procedure start");

        GMM_CasFsmStateChangeTo(GMM_DEREGISTERED_INITIATED);                    /* 状态迁移到GMM DEREGISTERED INITIATED     */

        Gmm_Com_MsInitNormalDetach();                                           /* 调用MS启动的detach的公共处理             */


        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_MsInitNormalDetach:NORMAL: STATUS IS GMM_DEREGISTERED_INITIATED");

        g_MmSubLyrShare.GmmShare.ucDeatchEnableFlg = GMM_DETACH_ABLE;
        break;
    case MMC_GMM_CS_DETACH:                                                     /* IMSI detach                              */
        if((VOS_FALSE == NAS_MML_GetCsRestrictRegisterFlg())
        && (GMM_NET_MODE_I == g_GmmGlobalCtrl.SysInfo.ucNetMod))
        {
            g_GmmGlobalCtrl.ucSpecProc = GMM_DETACH_WITH_IMSI;                      /* 赋值当前spesific过程                     */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_MsInitNormalDetach:INFO: IMSI detach procedure started");

            GMM_CasFsmStateChangeTo(GMM_REGISTERED_IMSI_DETACH_INITIATED);

            NAS_GMM_SndMmImsiDetachInitiation();                                       /* 向MMC发送MMCGMM_IMSI_DETACH_INITIATION   */
            Gmm_Com_MsInitNormalDetach();                                           /* 调用MS启动的detach的公共处理             */


            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_MsInitNormalDetach:NORMAL: STATUS IS GMM_REGISTERED_IMSI_DETACH_INITIATED");

            g_MmSubLyrShare.GmmShare.ucDeatchEnableFlg = GMM_DETACH_ABLE;
        }
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_MsInitNormalDetach:WARNING: Detach Type is Abnormal");
        break;
    }

    return;                                                                     /* 返回                                     */
}


VOS_VOID NAS_GMM_ProcDetachReq_RegNmlServ(
    MMCGMM_DETACH_REQ_STRU             *pstDetachReq,
    VOS_UINT32                          ulDetachType                   /* detach类型                               */
)
{
    MMCGMM_DETACH_REQ_STRU              *pstBufDetach = VOS_NULL_PTR;

    if ((GMM_TIMER_T3340_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3340_FLG))
     || (VOS_TRUE == gstGmmCasGlobalCtrl.ucRauCmpFlg))
    {
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_DETACH;    /* 置原语缓存标志                           */
        pstBufDetach = (MMCGMM_DETACH_REQ_STRU *)Gmm_MemMalloc(sizeof(MMCGMM_DETACH_REQ_STRU));
        if (VOS_NULL_PTR == pstBufDetach)
        {
              PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "NAS_GMM_ProcDetachReq_RegNmlServ:ERROR: Allocate memory error in Gmm_RcvMmcDetachReq");
              return;
        }

        Gmm_MemCpy(pstBufDetach, pstDetachReq, sizeof(MMCGMM_DETACH_REQ_STRU));
        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach = (VOS_UINT32)pstBufDetach;       /* 缓存原语                                 */
    }
    else if ((gstGmmCasGlobalCtrl.ucLastDataSender != NAS_MML_GetCurrNetRatType())
          && (GMM_RAU_FOR_WAITSERVICE == gstGmmSuspendCtrl.ucRauCause)
#if (FEATURE_ON == FEATURE_LTE)
          && (gstGmmCasGlobalCtrl.ucLastDataSender != NAS_MML_NET_RAT_TYPE_LTE)
#endif
          )
    {
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_DETACH;    /* 置原语缓存标志                           */
        pstBufDetach = (MMCGMM_DETACH_REQ_STRU *)Gmm_MemMalloc(sizeof(MMCGMM_DETACH_REQ_STRU));
        if (VOS_NULL_PTR == pstBufDetach)
        {
              PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "NAS_GMM_ProcDetachReq_RegNmlServ:ERROR: Allocate memory error in Gmm_RcvMmcDetachReq");
              return;
        }
        Gmm_MemCpy(pstBufDetach, pstDetachReq, sizeof(MMCGMM_DETACH_REQ_STRU));
        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach = (VOS_UINT32)pstBufDetach;       /* 缓存原语                                 */

        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
    }

    else
    {
        Gmm_MsInitNormalDetach(ulDetachType);                                   /* 调用MS启动的detach处理                   */
    }
}

/*******************************************************************************
  Module   : Gmm_Com_MsInitNormalDetach
  Function : MS启动的detach过程的公共处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2003.12.08  新规作成
*******************************************************************************/
VOS_VOID Gmm_Com_MsInitNormalDetach(VOS_VOID)
{
    NAS_MSG_STRU    *pDetachRequest;                                            /* 定义指针                                 */

    pDetachRequest = Gmm_DetachRequestMsgMake();                                /* 调用detach request消息制作函数           */

    if (GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg)
    {                                                                           /* 当前有信令连接                           */
        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pDetachRequest);           /* 发送detach request消息                   */
        Gmm_TimerStart(GMM_TIMER_T3321);                                        /* 启动T3321                                */
    }
    else
    {                                                                           /* 当前没有有信令连接                       */
        Gmm_SndRrmmEstReq(RRC_EST_CAUSE_DETACH,
                          GMM_RRC_IDNNS_UNKNOWN,
                          pDetachRequest);                                      /* 建立信令连接                             */
        Gmm_TimerStart(GMM_TIMER_PROTECT_FOR_SIGNALING);
    }

    return;                                                                     /* 返回                                     */
}


VOS_VOID Gmm_RcvMmcPowerOffReq(
                           VOS_VOID *pMsg                                       /* 原语指针                                 */
                           )
{
    MMCGMM_POWER_OFF_REQ_STRU      *ptr;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    NAS_GMM_SetAttach2DetachErrCode(GMM_SM_CAUSE_PS_DETACH);

    /* 启动关机保护定时器，*/
    Gmm_TimerStart(GMM_TIMER_1S);

    if ((GMM_FALSE == g_GmmGlobalCtrl.ucSigConFlg)
        && (GMM_RRC_RRMM_EST_CNF_FLG
        == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG))
        && ((GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
        || (GMM_DEREGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
        || (GMM_SERVICE_REQUEST_INITIATED == g_GmmGlobalCtrl.ucState)
        || (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
        || (GMM_REGISTERED_IMSI_DETACH_INITIATED == g_GmmGlobalCtrl.ucState)))
    {                                                                           /* 状态是GMM-流程-INITIATED                 *
                                                                                 * 且无信令且正在建立信令连接               */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_POWEROFF;      /* 置缓存标志                               */
        ptr = (MMCGMM_POWER_OFF_REQ_STRU *)Gmm_MemMalloc(sizeof(MMCGMM_POWER_OFF_REQ_STRU));
        if (VOS_NULL_PTR == ptr)
        {
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcPowerOffReq:WARNING: STATUS IS GMM_REGISTERED_IMSI_DETACH_INITIATED");
            return;
        }
        Gmm_MemCpy(ptr, pMsg, sizeof(MMCGMM_POWER_OFF_REQ_STRU));
        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPowerOff = (VOS_UINT32)ptr;         /* 缓存原语                                 */

        return;                                                                 /* 返回                                     */
    }

    /* GMM给上层应用回复失败 */
    Gmm_ComCnfHandle();
    Gmm_HoldBufferFree();
    /* 关机清除GMM缓存 */
    GMM_BufferMsgDump();

    NAS_GMM_FreeGsmSysInfo();

    NAS_GMM_FreeWasSysInfo();

    /* PS未attach上,直接给MMC回复关机结果 */
    if ((GMM_STATUS_ATTACHED                    != g_MmSubLyrShare.GmmShare.ucAttachSta)
     && (GMM_REGISTERED_INITIATED               != g_GmmGlobalCtrl.ucState)
     && (GMM_ROUTING_AREA_UPDATING_INITIATED    != g_GmmGlobalCtrl.ucState))
    {
        g_GmmReqCnfMng.ucCnfMask = 0;
        g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;
        g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;

        Gmm_ComStaChg(GMM_NULL);                                                /* 调用状态的公共处理                       */
        Gmm_SndMmcPowerOffCnf();                                                /* 向MMC发送MMCGMM_POWER_CNF               */
        Gmm_ComVariantInit();                                                   /* 清除全局变量                             */

        return;
    }

    enCurRat = NAS_MML_GetCurrNetRatType();

    /*G下，当前MM有业务正在进行，缓存关机请求 */
    if ((MMC_MM_SIGNALING_STATUS_PRESENT == MM_GetSignalingStatus())
     && (NAS_MML_NET_RAT_TYPE_GSM == enCurRat))
    {
        gstGmmSuspendCtrl.ucPowerOff = GMM_POWER_OFF_RCV;

        return;
    }

    /* 进行关机流程 */
    Gmm_TimerStop(GMM_TIMER_ALL);

    g_GmmReqCnfMng.ucCnfMask = 0;
    g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;
    g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;

    if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
     && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
    {                                                                           /* A+I                                      */
        if ((GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta)
            && (MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState))

        {                                                                       /* MM和GMM均注册                            */
            g_GmmGlobalCtrl.ucSpecProc = GMM_DETACH_COMBINED_POWER_OFF;         /* 置当前的specific过程                     */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcPowerOffReq:INFO: combined detach(power off) procedure started");

        }
        else if ((GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta)
            && (MM_STATUS_DETACHED
            == g_MmSubLyrShare.MmShare.ucCsAttachState))
        {                                                                       /* MM未注册,GMM注册                         */
            if((GMM_RAU_COMBINED == g_GmmGlobalCtrl.ucSpecProc)
                || (GMM_RAU_WITH_IMSI_ATTACH == g_GmmGlobalCtrl.ucSpecProc))
            {                                                                   /* 当前流程是combined                       */
                g_GmmGlobalCtrl.ucSpecProc = GMM_DETACH_COMBINED_POWER_OFF;     /* 置当前的specific过程                     */
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcPowerOffReq:INFO: combined detach(power off) procedure started");
            }
            else
            {                                                                   /* 当前流程不是combined                     */
                g_GmmGlobalCtrl.ucSpecProc = GMM_DETACH_NORMAL_POWER_OFF;       /* 置当前的specific过程                     */
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcPowerOffReq:INFO: normal detach(power off) procedure started");
            }
        }
        else
        {                                                                       /* GMM未注册                                */
            if (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
            {                                                                   /* 当前状态是REGISTERED_INITIATED           */

                if ((GMM_ATTACH_NORMAL == g_GmmGlobalCtrl.ucSpecProc)
                   ||(GMM_ATTACH_NORMAL_CS_TRANS == g_GmmGlobalCtrl.ucSpecProc))
                {                                                               /* 进行normal attach                        */
                    g_GmmGlobalCtrl.ucSpecProc = GMM_DETACH_NORMAL_POWER_OFF;   /* 置当前的specific过程                     */
                    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcPowerOffReq:INFO: normal detach(power off) procedure started");
                }
                else
                {                                                               /* 进行combine attach                       */
                    g_GmmGlobalCtrl.ucSpecProc = GMM_DETACH_COMBINED_POWER_OFF; /* 置当前的specific过程                     */
                    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcPowerOffReq:INFO: combined detach(power off) procedure started");
                }
            }
            else if (GMM_ROUTING_AREA_UPDATING_INITIATED
                                            == g_GmmGlobalCtrl.ucState)
            {                                                                   /* 当前状态是RAU_INITIATED                  */

                if ((GMM_RAU_NORMAL == g_GmmGlobalCtrl.ucSpecProc)
                    ||(GMM_RAU_NORMAL_CS_TRANS == g_GmmGlobalCtrl.ucSpecProc))
                {                                                               /* 进行normal rau                           */
                    g_GmmGlobalCtrl.ucSpecProc = GMM_DETACH_NORMAL_POWER_OFF;   /* 置当前的specific过程                     */
                    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcPowerOffReq:INFO: normal detach(power off) procedure started");
                }
                else
                {                                                               /* 进行combine rau                          */
                    g_GmmGlobalCtrl.ucSpecProc = GMM_DETACH_COMBINED_POWER_OFF; /* 置当前的specific过程                     */
                    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcPowerOffReq:INFO: combined detach(power off) procedure started");
                }
            }
            else
            {                                                                   /* 其他状态                                 */
                Gmm_ComStaChg(GMM_NULL);                 /* 调用状态的公共处理                       */
                Gmm_SndMmcPowerOffCnf();                                        /* 向MMC发送MMCGMM_DETACH_CNF               */
                Gmm_ComVariantInit();                                           /* 清除全局变量                             */
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcPowerOffReq:INFO: specific procedure ended");
                return;
            }
        }
    }
    else
    {                                                                           /* A+II或C                                  */
        if ((GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta)
            || (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
            || (GMM_ROUTING_AREA_UPDATING_INITIATED
                                             == g_GmmGlobalCtrl.ucState))
        {                                                                       /* GMM注册或者
                                                                                 * 当前状态是REGISTERED_INITIATE            */
            g_GmmGlobalCtrl.ucSpecProc = GMM_DETACH_NORMAL_POWER_OFF;           /* 置当前的specific过程                     */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcPowerOffReq:INFO: normal detach(power off) procedure started");
        }
        else
        {                                                                       /* GMM未注册                                */
            Gmm_ComStaChg(GMM_NULL);                     /* 调用状态的公共处理                       */
            Gmm_SndMmcPowerOffCnf();                                            /* 向MMC发送MMCGMM_DETACH_CNF               */
            Gmm_ComVariantInit();                                                   /* 清除全局变量                             */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcPowerOffReq:INFO: specific procedure ended");
            return;
        }
    }

    Gmm_PowerOffDetach();                                                       /* 调用Power Off时的detach处理              */

    return;                                                                     /* 返回                                     */
}


VOS_VOID Gmm_PowerOffDetach(VOS_VOID)
{
    NAS_MSG_STRU        *pDetachRequest;                                        /* 定义指针                                 */

    if ( (GMM_REGISTERED_NO_CELL_AVAILABLE == g_GmmGlobalCtrl.ucState)
      || (GMM_REGISTERED_LIMITED_SERVICE  == g_GmmGlobalCtrl.ucState)
      || (GMM_REGISTERED_UPDATE_NEEDED  == g_GmmGlobalCtrl.ucState)
      || (GMM_REGISTERED_ATTEMPTING_TO_UPDATE  == g_GmmGlobalCtrl.ucState)
      || (GMM_REGISTERED_PLMN_SEARCH  == g_GmmGlobalCtrl.ucState) )
    {
        if(GMM_TRUE == GMM_IsCasGsmMode())
        {
            Gmm_ClearLlcData(LL_GMM_CLEAR_DATA_TYPE_ALL);
        }
        if ((GMM_DETACH_COMBINED_POWER_OFF == g_GmmGlobalCtrl.ucSpecProc)
            || (GMM_DETACH_NORMAL_POWER_OFF == g_GmmGlobalCtrl.ucSpecProc))
        {                                                                       /* 当前流程是POWER OFF                      */
            if (GMM_UEID_P_TMSI_SIGNATURE
             == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
            & GMM_UEID_P_TMSI_SIGNATURE))
            {                                                                   /* DETACH成功且使用了P_TMSI_SIGNATURE       */
                g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
                    &= ~GMM_UEID_P_TMSI_SIGNATURE;                              /* 清除P_TMSI_SIGNATURE                     */
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

            if (GMM_DETACH_COMBINED_POWER_OFF == g_GmmGlobalCtrl.ucSpecProc)
            {                                                                       /* 是combined流程                           */
                NAS_GMM_SndMmGprsDetachInitiation();                                   /* 发送原语通知MMC                          */
            }

            Gmm_SndMmcPowerOffCnf();                                            /* 向MMC回POWER OFF的响应                   */

            Gmm_ComStaChg(GMM_NULL);                     /* 调用状态的公共处理                       */

            /*Gmm_TimerDistroy();*/                                                     /* 销毁所有TIMER                            */
            Gmm_ComVariantInit();                                               /* 清除全局变量                             */
            g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                    /* 清当前流程                               */
        }
        else if ((GMM_DETACH_COMBINED_SIM_REMOVE == g_GmmGlobalCtrl.ucSpecProc)
            || (GMM_DETACH_NORMAL_SIM_REMOVE == g_GmmGlobalCtrl.ucSpecProc))
        {                                                                       /* 当前流程是SIM REMOVE                     */
            /* 判断等待标志是否存在，如果存在则向MMC,MM发送DETACH信息 */
            if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
            {
                NAS_GMM_SndMmcMmDetachInfo();
            }


            /* 向MMC发送PS注册结果 */
            NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                         GMM_MMC_ACTION_RESULT_FAILURE,
                                         NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

            Gmm_ComStaChg(GMM_DEREGISTERED_NO_IMSI);                            /* 调用状态的公共处理                       */

            g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                    /* 清当前流程                               */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_Tim5sExpired:INFO: specific procedure ended");

            g_GmmReqCnfMng.ucCnfMask = 0;                                       /* 清等待cnf标志                            */
        }
        else
        {
        }
    }
    else
    {
        if (GMM_TRUE == GMM_IsCasGsmMode())
        {
            if(GMM_NOT_SUSPEND_LLC == gstGmmCasGlobalCtrl.ucSuspendLlcCause)
            {
                GMM_SndLlcSuspendReq();
                gstGmmCasGlobalCtrl.ucSuspendLlcCause = GMM_SUSPEND_LLC_FOR_DETACH;
            }
        }

        /* 在发起detach时，有可能原来曾经把LLC挂起，所以在发送detach前，需要恢复LLC */
        if (GMM_NOT_SUSPEND_LLC != gstGmmCasGlobalCtrl.ucSuspendLlcCause)
        {
            GMM_SndLlcResumeReq(LL_GMM_RESUME_TYPE_SIGNAL);
        }

        pDetachRequest = Gmm_DetachRequestMsgMake();                            /* 调用detach request消息制作函数           */

        if ((GMM_DETACH_COMBINED_POWER_OFF == g_GmmGlobalCtrl.ucSpecProc)
            || (GMM_DETACH_COMBINED_SIM_REMOVE == g_GmmGlobalCtrl.ucSpecProc))
        {                                                                       /* 是combined流程                           */
            NAS_GMM_SndMmGprsDetachInitiation();                                   /* 发送原语通知MMC                          */
        }
        if (GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg)
        {                                                                       /* 当前存在信令连接                         */
            Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pDetachRequest);       /* 发送detach request消息                   */
            GMM_CasFsmStateChangeTo(GMM_DEREGISTERED_NORMAL_SERVICE);
            Gmm_TimerStart(GMM_TIMER_1S);                                       /* 启动1S定时器                             */
        }
        else
        {                                                                       /* 当前不存在信令连接                       */
            Gmm_SndRrmmEstReq(RRC_EST_CAUSE_DETACH,
                              GMM_RRC_IDNNS_UNKNOWN,
                              pDetachRequest);                                  /* 建立信令连接                             */

            Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ESTING);      /* 通知MMC PS域信令连接正在建立             */
            GMM_CasFsmStateChangeTo(GMM_DEREGISTERED_NORMAL_SERVICE);
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_PowerOffDetach:NORMAL: STATUS IS GMM_DEREGISTERED_NORMAL_SERVICE");

            if ((GMM_DETACH_COMBINED_SIM_REMOVE == g_GmmGlobalCtrl.ucSpecProc)
                || (GMM_DETACH_COMBINED_POWER_OFF == g_GmmGlobalCtrl.ucSpecProc))
            {                                                                   /* 当前流程是combined sim remove或power off */
                g_MmSubLyrShare.GmmShare.ucDeatchEnableFlg = GMM_DETACH_ABLE;   /* 置标志位能作detach                       */
            }
            Gmm_TimerStart(GMM_TIMER_1S);                                       /* 启动5S定时器                             */
        }
        ++ (g_GmmGlobalCtrl.stPowerOffCtrl.ucSndDetachCnt);

        /* G下关机参考标杆做法:GMM启动5S定时器,这里detach发出后只需要尝试5次 */
        Gmm_TimerStart(GMM_TIMER_DETACH_FOR_POWER_OFF);
    }
    return;                                                                     /* 返回                                     */
}

/*lint -e438 -e830*/


NAS_MSG_STRU* Gmm_DetachRequestMsgMake(VOS_VOID)
{
    NAS_MSG_FOR_PCLINT_STRU    *pDetachRequest;                                 /* 定义指针                                 */
    NAS_MSG_STRU               *pNasMsg;
    VOS_UINT32                  ulMsgLen;                                       /* 定义变量存储消息长度                     */
    VOS_UINT8                   ucPtmsiFlg;                                     /* 定义变量标志是否存在P-TMSI               */
    VOS_UINT8                   ucPtmsiSigFlg;                                  /* 定义变量标志是否存在P-TMSI signature     */
    VOS_UINT8                   ucNumber;
    VOS_INT8                    cVersion;

    cVersion = NAS_Common_Get_Supported_3GPP_Version(MM_COM_SRVDOMAIN_PS);

    ulMsgLen        = GMM_MSG_LEN_DETACH_REQUEST;                               /* 初始化临时变量,消息中必选部分            */
    ucPtmsiFlg      = GMM_FALSE;                                                /* 初始化临时变量                           */
    ucPtmsiSigFlg   = GMM_FALSE;                                                /* 初始化临时变量                           */
    pDetachRequest  = VOS_NULL_PTR;                                             /* 初始化临时变量                           */

    /* R99以前版本无可选IE */
    if(PS_PTL_VER_PRE_R99 != cVersion)
    {
        if (GMM_UEID_P_TMSI == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask & GMM_UEID_P_TMSI))
        {                                                                           /* 存在P-TMSI                               */
            ulMsgLen  += 7;                                                         /* 消息长度增加                             */
            ucPtmsiFlg = GMM_TRUE;                                                  /* 标志存在P-TMSI                           */
        }

        if (  (GMM_TRUE == ucPtmsiFlg)
            &&(GMM_UEID_P_TMSI_SIGNATURE == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask & GMM_UEID_P_TMSI_SIGNATURE)))
        {                                                                           /* 存在P-TMSI signature                     */
            ulMsgLen     += 5;                                                      /* 消息长度增加                             */
            ucPtmsiSigFlg = GMM_TRUE;                                               /* 标志存在P-TMSI signature                 */
        }
    }

    if (ulMsgLen <= 4)
    {                                                                           /* 消息长度小于等于4                        */
        pNasMsg = (NAS_MSG_STRU *)Gmm_MemMalloc(sizeof(NAS_MSG_STRU));          /* 申请内存空间                             */
        if (VOS_NULL_PTR == pNasMsg)
        {
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "Gmm_DetachRequestMsgMake:error: Alloc mem fail.");
            return pNasMsg;
        }
        pDetachRequest = (NAS_MSG_FOR_PCLINT_STRU *)pNasMsg;
        Gmm_MemSet(pDetachRequest, 0, sizeof(NAS_MSG_STRU));                    /* 将申请的内存空间清0                      */
    }
    else
    {                                                                           /* 消息长度大于4                            */
        pNasMsg = (NAS_MSG_STRU *)Gmm_MemMalloc(
                                         (sizeof(NAS_MSG_STRU) + ulMsgLen) - 4);  /* 申请内存空间                             */
        if (VOS_NULL_PTR == pNasMsg)
        {
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "Gmm_DetachRequestMsgMake:error: Alloc mem fail.");
            return pNasMsg;
        }
        pDetachRequest = (NAS_MSG_FOR_PCLINT_STRU *)pNasMsg;
        Gmm_MemSet(pDetachRequest, 0, (sizeof(NAS_MSG_STRU) + ulMsgLen) - 4);   /* 将申请的内存空间清0                      */
    }

    pDetachRequest->ulNasMsgSize = ulMsgLen;                                    /* 赋值消息长度                             */
    pDetachRequest->aucNasMsg[0] = GMM_PD_GMM;                                  /* PD和Skip Indicator                       */
    pDetachRequest->aucNasMsg[1] = GMM_MSG_DETACH_REQUEST;                      /* message type                             */
    switch (g_GmmGlobalCtrl.ucSpecProc)
    {                                                                           /* 判断detach类型进行不同处理               */
    case GMM_DETACH_COMBINED:                                                   /* combined detach                          */
        pDetachRequest->aucNasMsg[2] = GMM_COMBINED_DETACH_NORMAL;              /* detach type                              */
        break;
    case GMM_DETACH_NORMAL:                                                     /* normal detach                            */
    case GMM_DETACH_NORMAL_NETMODE_CHANGE:
        pDetachRequest->aucNasMsg[2] = GMM_GPRS_DETACH_NORMAL;                  /* detach type                              */
        break;
    case GMM_DETACH_WITH_IMSI:                                                  /* IMSI detach                              */
        pDetachRequest->aucNasMsg[2] = GMM_IMSI_DETACH_MS_TO_NET;               /* detach type                              */
        break;
    case GMM_DETACH_COMBINED_POWER_OFF:                                         /* combined detach with power off           */
    case GMM_DETACH_COMBINED_SIM_REMOVE:                                        /* combined detach with sim removing        */
        pDetachRequest->aucNasMsg[2] = GMM_COMBINED_DETACH_POWEROFF;            /* detach type                              */
        break;
    case GMM_DETACH_NORMAL_POWER_OFF:                                           /* GPRS detach with power off               */
    case GMM_DETACH_NORMAL_SIM_REMOVE:                                          /* GPRS detach with sim removing            */
        pDetachRequest->aucNasMsg[2] = GMM_GPRS_DETACH_POWEROFF;                /* detach type                              */
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_DetachRequestMsgMake:WARNING: g_GmmGlobalCtrl.ucSpecProc is Abnormal");
        Gmm_MemFree(pDetachRequest);
        return VOS_NULL_PTR;
    }

    /* R99以前版本无可选IE */
    if(PS_PTL_VER_PRE_R99 != cVersion)
    {
        ucNumber = 3;
        if (GMM_TRUE == ucPtmsiFlg)
        {                                                                           /* 存在P-TMSI                               */
            /*lint -e961*/
            pDetachRequest->aucNasMsg[ucNumber++]
                                        = GMM_IEI_P_TMSI;                           /* IEI                                      */
            pDetachRequest->aucNasMsg[ucNumber++]
                                        = 0x05;                                     /* length                                   */
            pDetachRequest->aucNasMsg[ucNumber++]
                                        = GMM_MOBILE_ID_TMSI_PTMSI | 0xf0;          /* type of id and the 5-8 bit               */
            /*lint +e961*/
            Gmm_MemCpy(&pDetachRequest->aucNasMsg[ucNumber],
                       NAS_MML_GetUeIdPtmsi(),
                       NAS_MML_MAX_PTMSI_LEN);                                         /* P_TMSI赋值                               */
            ucNumber = ucNumber + NAS_MML_MAX_PTMSI_LEN;

        }
        if (GMM_TRUE == ucPtmsiSigFlg)
        {                                                                           /* 存在P-TMSI signature                     */
            /*lint -e961*/
            pDetachRequest->aucNasMsg[ucNumber++] = GMM_IEI_P_TMSI_SIGNATURE;       /* IEI                                      */
            pDetachRequest->aucNasMsg[ucNumber++] = 0x03;                           /* length                                   */
            /*lint +e961*/
            Gmm_MemCpy(&(pDetachRequest->aucNasMsg[ucNumber]),
                       NAS_MML_GetUeIdPtmsiSignature(),
                       NAS_MML_MAX_PTMSI_SIGNATURE_LEN);                            /* P_TMSI signature赋值 */
            ucNumber += NAS_MML_MAX_PTMSI_SIGNATURE_LEN;
        }
    }

    /* 发起Detach流程，更新GMM链路释放控制变量 */
    NAS_GMM_UpdateGmmLinkCtrlStru();
    g_GmmDetachCtrl.ucRetryDetachForRelCtrlFlg =  VOS_FALSE;
    g_GmmDetachCtrl.ucDetachProc = g_GmmGlobalCtrl.ucSpecProc;

    return (NAS_MSG_STRU *)pDetachRequest;                                                      /* 返回做成的消息                           */
}
/*lint +e438 +e830*/


VOS_VOID Gmm_RcvDetachRequestMsg(
                             NAS_MSG_FOR_PCLINT_STRU       *pMsg
                             )
{
    VOS_UINT8               ucDetachType;                                           /* 定义临时变量                             */
    VOS_UINT8               ucGmmCause;                                             /* 定义临时变量                             */
    NAS_MSG_STRU        *pGmmStatus;
    VOS_UINT8           ucForceToStandby;

    ucDetachType = 0;                                                           /* 初始化临时变量                           */
    ucGmmCause   = NAS_MML_REG_FAIL_CAUSE_NULL;                                 /* 初始化临时变量                           */

    if (pMsg->ulNasMsgSize < GMM_MSG_LEN_DETACH_REQUEST)
    {                                                                           /* 消息中必选项的长度不够                   */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvDetachRequestMsg:WARNING: Length of DETACH REQUEST is invalid");
        pGmmStatus = Gmm_GmmStatusMsgMake(NAS_MML_REG_FAIL_CAUSE_INVALID_MANDATORY_INF);

        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH , pGmmStatus);
        return;                                                                 /* 返回                                     */
    }

    ucForceToStandby = (VOS_UINT8)((pMsg->aucNasMsg[2]>>4) & 0x0F);
    if (1 == ucForceToStandby)
    {
        gstGmmCasGlobalCtrl.ucFtsFlg = GMM_TRUE;
    }
    else if (0 == ucForceToStandby)
    {
        gstGmmCasGlobalCtrl.ucFtsFlg = GMM_FALSE;
    }
    else
    {                                                                           /* Force to standby                         */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvDetachRequestMsg:WARNING: DETACH REQUEST is semantically incorrect");
        /*pGmmStatus = */
        /*    Gmm_GmmStatusMsgMake(NAS_MML_REG_FAIL_CAUSE_SEMANTICALLY_INCORRECT_MSG);*/

        /*Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH , pGmmStatus);*/
        /*return;*/
        gstGmmCasGlobalCtrl.ucFtsFlg = GMM_FALSE;
    }

    ucDetachType = (VOS_UINT8)(pMsg->aucNasMsg[2] & 0x0F);                          /* 从消息中取detach类型                     */
    if ((GMM_NET_DETACH_REATTACH_REQUIRED != ucDetachType)
        && (GMM_NET_DETACH_IMSI_DETACH    != ucDetachType))
    {                                                                           /* detach类型不是reattach required
                                                                                 * 并且也不是imsi detach                    */
        ucDetachType = GMM_NET_DETACH_REATTACH_NOT_REQUIRED;                    /* 将消息类型置为reattach not required      */
    }
    /* 如果是PS域DETACH，需要保存触发原因 */
    if (GMM_NET_DETACH_IMSI_DETACH != ucDetachType)
    {
        if (5 == pMsg->ulNasMsgSize)
        {                                                                           /* 消息长度等于5                            */
            if (GMM_IEI_GMM_CAUSE != pMsg->aucNasMsg[3])
            {
                /* 原因值的IEI不正确 */
                NAS_GMM_SetAttach2DetachErrCode(GMM_SM_CAUSE_PROTOCOL_ERROR);
            }
            else
            {
                /* 原因值的IEI正确 */
                NAS_GMM_ChangeDetachCauseAvoidInvalidSim(&(pMsg->aucNasMsg[4]));

                ucGmmCause = pMsg->aucNasMsg[4];                                    /* 从消息中取detach原因                     */
                NAS_GMM_SetAttach2DetachErrCode(NAS_GMM_TransGmmNwCause2GmmSmCause(ucGmmCause));
            }
        }
        else
        {
            NAS_GMM_SetAttach2DetachErrCode(GMM_SM_CAUSE_PROTOCOL_ERROR);
        }
    }

#if (FEATURE_ON == FEATURE_PTM)
    NAS_GMM_NwDetachIndRecord(ucDetachType, ucGmmCause, ucForceToStandby);
#endif

    switch (g_GmmGlobalCtrl.ucState)
    {                                                                           /* 判断当前状态进行不同的处理               */
    case GMM_REGISTERED_INITIATED:                                              /* GMM-REGISTERED-INITIATED                 */
        Gmm_RcvDetachRequestMsg_RegInit(ucDetachType, ucGmmCause);              /* 调用该状态下的detach处理                 */
        break;
    case GMM_DEREGISTERED_INITIATED:                                            /* GMM-DEREGISTERED-INITIATED               */
        Gmm_RcvDetachRequestMsg_DeregInit(ucDetachType, ucGmmCause);                                    /* 调用该状态下的detach处理                 */
        break;
    case GMM_ROUTING_AREA_UPDATING_INITIATED:                                   /* GMM-ROUTING-AREA-UPDATING-INITIATED      */
        Gmm_RcvDetachRequestMsg_RauInit(ucDetachType, ucGmmCause);              /* 调用该状态下的detach处理                 */
        break;
    case GMM_SERVICE_REQUEST_INITIATED:                                         /* GMM-SERVICE-REQUEST-INITIATED            */
        Gmm_RcvDetachRequestMsg_ServReqInit(ucDetachType, ucGmmCause);          /* 调用该状态下的detach处理                 */
        break;
    case GMM_REGISTERED_NORMAL_SERVICE:                                         /* GMM-REGISTERED.NORMAL-SERVICE            */
    case GMM_REGISTERED_LIMITED_SERVICE:                                        /* GMM-REGISTERED.LIMITED-SERVICE           */
        Gmm_RcvDetachRequestMsg_RegNmlServ(ucDetachType, ucGmmCause);           /* 调用该状态下的detach处理                 */
        break;
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:                                /* GMM-REGISTERED.ATTEMPTING-TO-UPDATE-MM   */
        Gmm_RcvDetachRequestMsg_RegAtmpToUpdtMm(ucDetachType, ucGmmCause);      /* 调用该状态下的detach处理                 */
        break;
    case GMM_REGISTERED_IMSI_DETACH_INITIATED:                                  /* GMM-REGISTERED.IMSI-DETACH-INITIATED     */
        Gmm_RcvDetachRequestMsg_RegImsiDtchInit(ucDetachType, ucGmmCause);                              /* 调用该状态下的detach处理                 */
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvDetachRequestMsg:WARNING: g_GmmGlobalCtrl.ucState is Abnormal");
        break;
    }

    if (GMM_TRUE == GMM_IsCasGsmMode())
    {
        if ( ucDetachType == GMM_NET_DETACH_IMSI_DETACH )
        {
            if ( GMM_TRUE == gstGmmCasGlobalCtrl.ucFtsFlg )
            {
                gstGmmCasGlobalCtrl.ucFtsFlg = GMM_FALSE;

                if ( 0xffffffff != gstGmmCasGlobalCtrl.ulReadyTimerValue )
                {
                    gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_STANDBY;
                    Gmm_TimerStop(GMM_TIMER_T3314);
#if (FEATURE_LTE == FEATURE_ON)
                    if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
                    {
                        NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
                    }
#endif
                    Gmm_TimerStart(GMM_TIMER_T3312);
                    NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
                }
            }
        }
        else/* detach PS */
        {
            Gmm_TimerStop(GMM_TIMER_T3314);
            gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_IDLE;
            gstGmmCasGlobalCtrl.ulReadyTimerValue = 44000;/* default 44s */
#if (FEATURE_LTE == FEATURE_ON)
            if (GMM_TIMER_T3312_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
            {
                NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
            }
#endif
            Gmm_TimerStop(GMM_TIMER_T3312);
            NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
        }

    }

    return;                                                                     /* 返回                                     */
}


VOS_VOID Gmm_RcvDetachRequestMsg_RegInit(
                                     VOS_UINT8      ucDetachType,                   /* detach类型                               */
                                     VOS_UINT8      ucGmmCause                      /* detach原因                               */
                                     )
{
    /* 24008_CR2300R1_(Rel-11)_C1-124892 24008 4.7.3.1.5描述如下:
    If the MS receives a DETACH REQUEST message from the network in state
    GMM-REGISTERED-INITIATED with detach type of detach '"re-attach not required"
    and no cause code, or "re-attach not required"' and the cause code is not #2
    "IMSI unknown in HLR", the GPRS detach procedure shall be progressed and the
    GPRS attach procedure shall be aborted. Otherwise the GPRS attach procedure
    shall be progressed and the DETACH REQUEST message shall be ignored.*/
    if ((GMM_NET_DETACH_REATTACH_NOT_REQUIRED == ucDetachType)
     && (NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR != ucGmmCause))
    {                                                                           /* detach类型是"re-attach not required"     */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* 停保护Timer                              */
        Gmm_TimerStop(GMM_TIMER_T3310);                                         /* 停T3310                                  */

        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */

        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;                              /* 清除followon标志                         */
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

        g_GmmReqCnfMng.ucCnfMask   = 0;                                         /* 清除等待CNF标志                          */
        if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
        {                                                                       /* ATTACH过程是由SM触发的                   */
            /* 该函数的入参ucGmmCause由函数Gmm_RcvDetachRequestMsg传入，其取值可
             能为NAS_MML_REG_FAIL_CAUSE_NULL，该值不在GMM/SM层的原因值内，故此处
             用g_GmmGlobalCtrl.enGmmCause保存的值 */

            Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, NAS_GMM_GetAttach2DetachErrCode());    /* 通知SM GMM注册失败                       */

            g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;                             /* 清ucSmCnfFlg标志                         */
        }
        Gmm_NetInitNotRequiredDetach(ucGmmCause);                               /* 调用detach的公共处理                     */
        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                        /* 清除当前进行的specific过程               */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvDetachRequestMsg_RegInit:INFO: specific procedure ended");
    }

    return;                                                                     /* 返回                                     */
}


VOS_VOID Gmm_RcvDetachRequestMsg_DeregInit(
    VOS_UINT8                           ucDetachType,           /* detach类型                               */
    VOS_UINT8                           ucGmmCause              /* detach原因                               */
)
{
    NAS_MSG_STRU    *pDetachAccept;                                             /* 定义指针                                 */

    /* 24008_CR2062R2_(Rel-11)_C1-121261 24008 4.7.4.1.4章节描述如下:
    GPRS detach containing other causes than "power off":
    If the DETACH REQUEST message received by the MS contains detach type "IMSI detach",
    and the MS initiated detach procedure is with detach type "GPRS detach" or
    "combined GPRS/IMSI detach", the MS shall progress both procedures.
    The MS in operation mode A or B in network operation mode I need not re-attach to non-GPRS services.*/
    if ((GMM_NET_DETACH_IMSI_DETACH == ucDetachType)
     && ((GMM_WAIT_PS_DETACH == g_GmmGlobalCtrl.stDetachInfo.enDetachType)
      || (GMM_WAIT_CS_PS_DETACH == g_GmmGlobalCtrl.stDetachInfo.enDetachType))
      && (MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState))
    {
        Gmm_SndMmcNetworkDetachInd(NAS_MMC_GMM_NT_DETACH_IMSI, NAS_MML_REG_FAIL_CAUSE_NULL);  /* 发送MMCGMM_NETWORK_DETACH_IND            */
        NAS_GMM_SndMmNetworkDetachInd(GMMMM_NET_DETACH_IMSI,
                                      NAS_MML_REG_FAIL_CAUSE_NULL);

        pDetachAccept = Gmm_DetachAcceptMsgMake();
        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pDetachAccept);
        return;
    }

    pDetachAccept = Gmm_DetachAcceptMsgMake();                                  /* 调用函数制作detach accept消息            */

    Gmm_TimerStop(GMM_TIMER_T3321);
    Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pDetachAccept);                /* 发送RRMM_DATA_REQ(detach accept消息)     */
    if (GMM_TRUE == GMM_IsCasGsmMode())
    {
        Gmm_ClearLlcData(LL_GMM_CLEAR_DATA_TYPE_USER);

        Gmm_TimerStop(GMM_TIMER_T3314);

        gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_IDLE;

        NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
        Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);
    }
    /* 判断等待标志是否存在，如果存在则向MMC,MM发送DETACH信息 */
    if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
    {
        NAS_GMM_SndMmcMmDetachInfo();
    }
    else
    {
        /* 收到网侧的去注册成功后需要通知MM，否则MM不启动T3212定时器 */
        NAS_GMM_SndMmGprsDetachComplete();
    }


    Gmm_SndMmcNetworkDetachInd(ucDetachType, ucGmmCause);  /* 发送MMCGMM_NETWORK_DETACH_IND            */

    NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);

    return;                                                                     /* 返回                                     */
}


VOS_VOID Gmm_RcvDetachRequestMsg_RauInit(
                                     VOS_UINT8      ucDetachType,               /* detach类型                               */
                                     VOS_UINT8      ucGmmCause                  /* detach原因                               */
                                     )
{
    /* 24008_CR1598R2_(Rel-9)_C1-103557 24008 4.7.4.2.4描述如下:
    If the network receives a ROUTING AREA UPDATE REQUEST message before the network initiated
    GPRS detach procedure has been completed, the detach procedure shall be progressed,
    i.e. the ROUTING AREA UPDATE REQUEST message shall be ignored. If the DETACH REQUEST
    message contains detach type "re-attach not required" and GMM cause  #2 "IMSI unknown in HLR",
    the network will follow the procedure as described below for the detach type "IMSI detach".
    GPRS detach containing detach type "IMSI detach":
     If the network receives a ROUTING AREA UPDATE REQUEST message before the network
     initiated GPRS detach procedure has been completed, the network shall abort the detach procedure,
     shall stop T3322 and shall progress the routing area update procedure.*/
    if (GMM_NET_DETACH_IMSI_DETACH == ucDetachType)
    {
        return;
    }

    if ((GMM_NET_DETACH_REATTACH_NOT_REQUIRED == ucDetachType)
     && (NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR == ucGmmCause))
    {
        return;
    }                                                                          /* detach类型为"re-attach not required"
                                                                             * 或"re-attach required                    */
    Gmm_TimerStop(GMM_TIMER_T3330);                                         /* 停T3330                                  */

    Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */

    Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* 停保护Timer                              */

    Gmm_ComCnfHandle();
    g_GmmReqCnfMng.ucCnfMask   = 0;                                         /* 清除等待CNF标志                          */
    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                        /* 清除当前进行的specific过程               */
    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvDetachRequestMsg_RauInit:INFO: specific procedure ended");

    if (GMM_NET_DETACH_REATTACH_NOT_REQUIRED == ucDetachType)
    {                                                                       /* detach类型为"re-attach not required"     */
        Gmm_NetInitNotRequiredDetach(ucGmmCause);                           /* 调用"re-attach not required"的公共处理   */
    }
    else
    {                                                                       /* detach类型为"re-attach required"         */
        Gmm_NetInitRequiredDetach();                                        /* 调用re-attach required的处理             */
    }


    return;                                                                     /* 返回                                     */
}


VOS_VOID Gmm_RcvDetachRequestMsg_ServReqInit(
                                         VOS_UINT8      ucDetachType,           /* detach类型                               */
                                         VOS_UINT8      ucGmmCause              /* detach原因                               */
                                         )
{
    /* 24008_CR1598R2_(Rel-9)_C1-103557 24008 4.7.4.2.4描述如下:
    If the GPRS Detach Request message contains detach type "re-attach not required"
    and GMM cause  #2 "IMSI unknown in HLR", the network will follow the procedure as
    described below for the detach type "IMSI detach".
    GPRS detach containing detach type "IMSI detach":
    If the network receives a SERVICE REQUEST message before the network initiated
    GPRS detach procedure has been completed, the network shall progress both
    procedures.*/
    if ((GMM_NET_DETACH_REATTACH_NOT_REQUIRED == ucDetachType)
     && (NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR == ucGmmCause))
    {
        ucDetachType = GMM_NET_DETACH_IMSI_DETACH;
    }

    Gmm_TimerStop(GMM_TIMER_T3317);                                             /* 停T3317                                  */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* 停止T3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* 停止T3320                                */
    Gmm_TimerStop(GMM_TIMER_PROTECT);                                           /* 停保护Timer                              */

    g_GmmReqCnfMng.ucCnfMask = 0;                                               /* 清除等待CNF标志                          */
    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                            /* 清除当前进行的specific过程               */
    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvDetachRequestMsg_ServReqInit:INFO: specific procedure ended");

    switch (ucDetachType)
    {                                                                           /* 判断detach类型进行不同处理               */
    case GMM_NET_DETACH_REATTACH_NOT_REQUIRED:                                  /* "re-attach not required"                 */
        Gmm_ComCnfHandle();

        Gmm_NetInitNotRequiredDetach(ucGmmCause);                               /* 调用"re-attach not required"的公共处理   */
        break;
    case GMM_NET_DETACH_REATTACH_REQUIRED:                                      /* "re-attach required"                     */
        Gmm_ComCnfHandle();

        Gmm_NetInitRequiredDetach();                                            /* 调用re-attach required的处理             */
        break;

    case GMM_NET_DETACH_IMSI_DETACH:                                            /* IMSI detach                              */
        /* Gmm_ComCnfHandle函数会清除sm缓存，imsi detach场景会立即发rau，不清sm
           缓存rau带follow on rau成功后可处理缓存发起sm业务请求 */
        Gmm_NetInitImsiDetach();                                                /* ??IMSI detach???                    */
        break;

    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvDetachRequestMsg_ServReqInit:WARNING: Detach Type is Abnormal");
        break;
    }

    return;                                                                     /* 返回                                     */
}

/*******************************************************************************
  Module   : Gmm_RcvDetachRequestMsg_RegNmlServ
  Function : 在GMM-REGISTERED.NORMAL-SERVICE状态下收到DETACH_REQUEST的处理
  Input    : VOS_UINT8     ucDetachType     detach类型
             VOS_UINT8     ucGmmCause       detach原因
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2003.12.08  新规作成
*******************************************************************************/
VOS_VOID Gmm_RcvDetachRequestMsg_RegNmlServ(
                                        VOS_UINT8      ucDetachType,                /* detach类型                               */
                                        VOS_UINT8      ucGmmCause                   /* detach原因                               */
                                        )
{
    switch (ucDetachType)
    {                                                                           /* 判断detach类型进行不同处理               */
    case GMM_NET_DETACH_REATTACH_NOT_REQUIRED:                                  /* "re-attach not required"                 */
        Gmm_NetInitNotRequiredDetach(ucGmmCause);                               /* 调用"re-attach not required"的公共处理   */
        break;
    case GMM_NET_DETACH_REATTACH_REQUIRED:                                      /* "re-attach required"                     */
        Gmm_NetInitRequiredDetach();                                            /* 调用re-attach required的处理             */
        break;
    case GMM_NET_DETACH_IMSI_DETACH:                                            /* IMSI detach                              */
        Gmm_NetInitImsiDetach();                                                /* 调用IMSI detach的处理                    */
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvDetachRequestMsg_RegNmlServ:WARNING: Detach Type is Abnormal");
        break;
    }

    return;                                                                     /* 返回                                     */
}

/*******************************************************************************
  Module   : Gmm_RcvDetachRequestMsg_RegAtmpToUpdtMm
  Function : 在REGISTERED.ATTEMPTING-TO-UPDATE-MM状态下收到DETACH_REQUEST的处理
  Input    : VOS_UINT8     ucDetachType     detach类型
             VOS_UINT8     ucGmmCause       detach原因
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2003.12.08  新规作成
*******************************************************************************/
VOS_VOID Gmm_RcvDetachRequestMsg_RegAtmpToUpdtMm(
                                             VOS_UINT8      ucDetachType,           /* detach类型                               */
                                             VOS_UINT8      ucGmmCause              /* detach原因                               */
                                             )
{
    Gmm_RcvDetachRequestMsg_RegNmlServ(ucDetachType, ucGmmCause);
}


VOS_VOID Gmm_RcvDetachRequestMsg_RegImsiDtchInit(
    VOS_UINT8                           ucDetachType,           /* detach类型                               */
    VOS_UINT8                           ucGmmCause              /* detach原因                               */
)
{



    NAS_MSG_STRU    *pDetachAccept;                                             /* 定义指针                                 */

    pDetachAccept = Gmm_DetachAcceptMsgMake();                                  /* 调用函数制作detach accept消息            */

    Gmm_TimerStop(GMM_TIMER_T3321);

    switch (ucDetachType)
    {                                                                           /* 判断detach类型进行不同处理               */
        case GMM_NET_DETACH_REATTACH_NOT_REQUIRED:                              /* "re-attach not required"                 */
            Gmm_NetInitNotRequiredDetach(ucGmmCause);                           /* 调用"re-attach not required"的公共处理   */
            break;

        case GMM_NET_DETACH_REATTACH_REQUIRED:                                  /* "re-attach required"                     */

            /* 设置CS不准许标志，这样不会发起联合ATTACH */
            if (GMM_WAIT_CS_DETACH == (g_GmmGlobalCtrl.stDetachInfo.enDetachType & GMM_WAIT_CS_DETACH))
            {
                NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
            }

            Gmm_NetInitRequiredDetach();                                        /* 调用re-attach required的处理             */
            break;

        case GMM_NET_DETACH_IMSI_DETACH:                                        /* IMSI detach                              */
            Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pDetachAccept);        /* 发送RRMM_DATA_REQ(detach accept消息)     */
            Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);
            Gmm_SndMmcNetworkDetachInd(ucDetachType, ucGmmCause);
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_GMM, "Gmm_RcvDetachRequestMsg_RegImsiDtchInit: INVALID DETACH TYPE!");
            break;
    }
    /* 判断等待标志是否存在，如果存在则向MMC,MM发送DETACH信息 */
    if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
    {
        NAS_GMM_SndMmcMmDetachInfo();
    }


    return;
}


VOS_VOID Gmm_NetInitNotRequiredDetach(
                                  VOS_UINT8         ucGmmCause                      /* detach的原因值                           */
                                  )
{
    switch (ucGmmCause)
    {                                                                           /* 根据原因值不同进行不同处理               */
    case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR:                                      /* 原因值2                                  */
        Gmm_Com_Cause2Detach();
        break;
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:                                               /* 原因值3                                  */
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:                                               /* 原因值6                                  */
    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:                    /* 原因值8                                  */
        Gmm_ComStaChg(GMM_DEREGISTERED_NO_IMSI);                                /* 调用状态的公共处理                       */
        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask  &= ~GMM_UEID_IMSI;              /* 清除IMSI存在MASK                         */
        NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_PLMN_NOT_ALLOWED);/* Update status更新为GU2                   */
        break;
    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:                                      /* 原因值7                                  */
        Gmm_ComStaChg(GMM_DEREGISTERED_NO_IMSI);                                /* 调用状态的公共处理                       */
        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask  &= ~GMM_UEID_IMSI;              /* 清除IMSI存在MASK                         */
        NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_PLMN_NOT_ALLOWED);  /* Update status更新为GU2                  */
        break;
    case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:                                           /* 原因值11                                 */
        Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                        /* 调用状态的公共处理                       */
        g_GmmGlobalCtrl.SysInfo.ucForbMask |= GMM_FORBIDDEN_PLMN;               /* 设置禁止注册列表标志                     */
        NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_ROUTING_AREA_NOT_ALLOWED);  /* Update status更新为GU3                   */

        
        g_GmmAttachCtrl.ucAttachAttmptCnt = 0;
        break;
    case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:                                             /* 原因值12                                 */
        g_GmmGlobalCtrl.ucLaNotAllowFlg = GMM_TRUE;
        Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                        /* 调用状态的公共处理                       */
        NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_ROUTING_AREA_NOT_ALLOWED);  /* Update status更新为GU3                   */
        g_GmmAttachCtrl.ucAttachAttmptCnt  = 0;                                 /* ATTACH ATTEMPT COUNTER RESET             */
        g_GmmGlobalCtrl.SysInfo.ucForbMask |=
                                        GMM_FORBIDDEN_LA_FOR_REG_PRVS_SVS;      /* 设置禁止注册列表标志                     */
        break;
    case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:                                           /* 原因值13                                 */
    case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:                                          /* 原因值15                                 */
        Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                        /* 调用状态的公共处理                       */
        NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_ROUTING_AREA_NOT_ALLOWED);  /* Update status更新为GU3                   */
        g_GmmAttachCtrl.ucAttachAttmptCnt  = 0;                                 /* ATTACH ATTEMPT COUNTER RESET             */
        g_GmmGlobalCtrl.SysInfo.ucForbMask |= GMM_FORBIDDEN_LA_FOR_ROAM;        /* 设置禁止注册列表标志                     */
        break;
    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:                              /* 原因值14                                 */
        Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                        /* 调用状态的公共处理                       */
        NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_ROUTING_AREA_NOT_ALLOWED);  /* Update status更新为GU3                   */
        g_GmmGlobalCtrl.SysInfo.ucForbMask |= GMM_FORBIDDEN_PLMN_FOR_GPRS;      /* 设置禁止注册列表标志                     */

        
        g_GmmAttachCtrl.ucAttachAttmptCnt = 0;
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_NetInitNotRequiredDetach:WARNING: GMM Cause is Abnormal");
        ucGmmCause = NAS_MML_REG_FAIL_CAUSE_NULL;                                         /* 将原因值置为空                           */
        Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);                         /* 调用状态的公共处理                       */
        g_GmmGlobalCtrl.ucRcvNetDetachFlg = VOS_TRUE;
        if (VOS_FALSE == NAS_MML_GetPsAutoAttachFlg())
        {
            NAS_MML_SetPsAttachAllowFlg( VOS_FALSE );
        }
        break;
    }

    if (NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR != ucGmmCause)
    {                                                                           /* 原因值不等于2                            */
        Gmm_Com_CauseDetach(ucGmmCause);                                        /* 调用原因值有效且不是2的公共处理          */
    }

    if ((NAS_MML_MS_MODE_CS_ONLY == NAS_MML_GetMsMode())
     && (VOS_FALSE == g_GmmGlobalCtrl.ucUserPsAttachFlag))
    {
        NAS_MML_SetPsAttachAllowFlg( VOS_FALSE );
    }

    return;                                                                     /* 返回                                     */
}



VOS_VOID Gmm_Com_Cause2Detach(VOS_VOID)
{
    NAS_MSG_STRU    *pDetachAccept;                                             /* 定义消息指针                             */

    pDetachAccept = Gmm_DetachAcceptMsgMake();                                  /* 调用函数制作detach accept消息            */

    Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pDetachAccept);                /* 发送RRMM_DATA_REQ(detach accept消息)     */
    Gmm_SndMmcNetworkDetachInd(NAS_MMC_GMM_NT_DETACH_NOATTACH,
                               NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR);               /* 发送MMCGMM_NETWORK_DETACH_IND            */
    NAS_GMM_SndMmNetworkDetachInd(GMMMM_NET_DETACH_NOATTACH,
                                  NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR);
    NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_DETACH_FINISH,
                    VOS_NULL_PTR,
                    NAS_OM_EVENT_NO_PARA);

    if (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
    {                                                                           /* 当前状态为REGISTERED_INITIATED           */
        Gmm_AttachInitiate(GMM_NULL_PROCEDURE);                                                   /* 重新进行ATTACH                           */                                                  /* 重新进行attach                           */
    }
    else if (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
    {                                                                           /* 当前状态为RAU_INITIATED                  */
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);               /* 重新进行RAU                              */
    }
    else if (GMM_SERVICE_REQUEST_INITIATED == g_GmmGlobalCtrl.ucState)
    {
        Gmm_ComStaChg(g_GmmGlobalCtrl.ucServPreSta);                            /* 调用状态的公共处理                       */
        if (GMM_TIMER_T3302_FLG
            == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3302_FLG))
        {                                                                       /* T3302正在运行                            */
            Gmm_TimerPause(GMM_TIMER_T3302);                                    /* 挂起T3302                                */
        }
        else if (GMM_TIMER_T3311_FLG
            == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3311_FLG))
        {                                                                       /* T3311正在运行                            */
            Gmm_TimerPause(GMM_TIMER_T3311);                                    /* 挂起T3311                                */
        }
        else
        {
        }
    }
    else
    {
    }

    return;                                                                     /* 返回                                     */
}


VOS_VOID Gmm_Com_CauseDetach(
                         VOS_UINT8  ucGmmCause                                      /* detach的原因值                           */
                         )
{
    NAS_MSG_STRU    *pDetachAccept;                                             /* 定义消息指针                             */

    pDetachAccept = VOS_NULL_PTR;                                                       /* 初始化消息指针                           */

    Gmm_TimerStop(GMM_TIMER_ALL);                                               /* 停止所有的GMM TIMER                      */

    pDetachAccept = Gmm_DetachAcceptMsgMake();                                  /* 调用函数制作detach accept消息            */

    Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pDetachAccept);                /* 发送RRMM_DATA_REQ(detach accept消息)     */
    Gmm_SndMmcNetworkDetachInd(NAS_MMC_GMM_NT_DETACH_NOATTACH, ucGmmCause);         /* 发送MMCGMM_NETWORK_DETACH_IND            */
    NAS_GMM_SndMmNetworkDetachInd(GMMMM_NET_DETACH_NOATTACH, ucGmmCause);
    NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_DETACH_FINISH,
                    VOS_NULL_PTR,
                    NAS_OM_EVENT_NO_PARA);

    if (NAS_MML_REG_FAIL_CAUSE_NULL != ucGmmCause)
    {                                                                           /* 原因值有效                               */
        Gmm_DelPsLocInfoUpdateUsim();
    }

    NAS_GMM_CheckCauseToStartT3340(ucGmmCause);

    if (GMM_TRUE == GMM_IsCasGsmMode())
    {
        Gmm_TimerStop(GMM_TIMER_T3314);

        gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_IDLE;

        NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
        if(GMM_TRUE == gstGmmCasGlobalCtrl.ucTlliAssignFlg)
        {
            Gmm_ClearLlcData(LL_GMM_CLEAR_DATA_TYPE_USER);
        }
    }
    return;                                                                     /* 返回                                     */
}


VOS_VOID Gmm_NetInitRequiredDetach(VOS_VOID)
{
    NAS_MSG_STRU    *pDetachAccept;                                             /* 定义消息指针                             */

    pDetachAccept = VOS_NULL_PTR;                                                       /* 初始化消息指针                           */

    Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);                             /* 调用状态的公共处理                       */
    Gmm_SndMmcNetworkDetachInd(NAS_MMC_GMM_NT_DETACH_REATTACH, NAS_MML_REG_FAIL_CAUSE_NULL);  /* 通知MMC GMM进行的detach                  */
    NAS_GMM_SndMmNetworkDetachInd(GMMMM_NET_DETACH_REATTACH,
                                  NAS_MML_REG_FAIL_CAUSE_NULL);
    pDetachAccept = Gmm_DetachAcceptMsgMake();                                  /* 调用函数制作detach accept消息            */

    Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pDetachAccept);                /* 发送RRMM_DATA_REQ(detach accept消息)     */
    NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_DETACH_FINISH,
                    VOS_NULL_PTR,
                    NAS_OM_EVENT_NO_PARA);
    Gmm_HoldBufferFree();                                                       /* 清除保留消息                             */
    if (GMM_TRUE == GMM_IsCasGsmMode())
    {
        Gmm_ClearLlcData(LL_GMM_CLEAR_DATA_TYPE_USER);

        Gmm_TimerStop(GMM_TIMER_T3314);

        gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_IDLE;

        NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
    }

    if ((NAS_MML_MS_MODE_CS_ONLY == NAS_MML_GetMsMode())
     && (VOS_FALSE == g_GmmGlobalCtrl.ucUserPsAttachFlag))
    {
        NAS_MML_SetPsAttachAllowFlg( VOS_FALSE );

        /* 向MMC发送PS注册结果 */
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                     GMM_MMC_ACTION_RESULT_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

    }
    else
    {
        if(GMM_TRUE == GMM_IsCasGsmMode())
        {
            g_GmmGlobalCtrl.ulGmmAttachFlg = GMM_TRUE;
        }
        else
        {
            Gmm_AttachInitiate(GMM_NULL_PROCEDURE);
        }
    }

    return;                                                                     /* 返回                                     */
}


VOS_VOID Gmm_NetInitImsiDetach(VOS_VOID)
{
    NAS_MSG_STRU    *pDetachAccept;                                             /* 定义消息指针                             */

    pDetachAccept = VOS_NULL_PTR;                                                       /* 初始化消息指针                           */

    if (MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
    {                                                                           /* CS域注册                                 */
        Gmm_SndMmcNetworkDetachInd(NAS_MMC_GMM_NT_DETACH_IMSI, NAS_MML_REG_FAIL_CAUSE_NULL);  /* 发送MMCGMM_NETWORK_DETACH_IND            */
        NAS_GMM_SndMmNetworkDetachInd(GMMMM_NET_DETACH_IMSI,
                                      NAS_MML_REG_FAIL_CAUSE_NULL);
        pDetachAccept = Gmm_DetachAcceptMsgMake();                              /* 调用函数制作detach accept消息            */

        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pDetachAccept);            /* 发送RRMM_DATA_REQ(detach accept消息)     */

        g_GmmGlobalCtrl.ucDetachAcceptedFlg = VOS_TRUE;

        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod)
         && (GMM_FALSE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg))
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH); /* 调用RAU过程combined RAU with IMSI attach */
        }
        else if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
              && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod)
              && (GMM_TRUE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg))
        {
            g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_ATTACH_NORMAL;
        }
        else
        {
        }

        g_GmmGlobalCtrl.ucDetachAcceptedFlg = VOS_FALSE;
    }

    return;                                                                     /* 返回                                     */
}

/*******************************************************************************
  Module   : Gmm_DetachAcceptMsgMake
  Function : Detach accept消息制作
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : NAS_MSG_STRU *
  History  :
    1. 张志勇  2003.12.09  新规作成
*******************************************************************************/
NAS_MSG_STRU* Gmm_DetachAcceptMsgMake(VOS_VOID)
{
    NAS_MSG_STRU    *pDetachAccept;                                             /* 定义消息指针                             */

    pDetachAccept = VOS_NULL_PTR;                                                       /* 初始化消息指针                           */

    pDetachAccept = (NAS_MSG_STRU *)Gmm_MemMalloc(sizeof(NAS_MSG_STRU));        /* 申请内存空间                             */
    if (VOS_NULL_PTR == pDetachAccept)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR,
            "Gmm_DetachAcceptMsgMake:error: Alloc mem fail.");
        return pDetachAccept;
    }
    Gmm_MemSet(pDetachAccept, 0, sizeof(NAS_MSG_STRU));                         /* 将申请的内存空间清0                      */

    pDetachAccept->ulNasMsgSize = GMM_MSG_LEN_DETACH_ACCEPT;                    /* 消息长度                                 */
    pDetachAccept->aucNasMsg[0] = GMM_PD_GMM;                                   /* PD                                       */
    pDetachAccept->aucNasMsg[1] = GMM_MSG_DETACH_ACCEPT;                        /* message type                             */

    return pDetachAccept;                                                       /* 返回                                     */
}


VOS_VOID Gmm_RcvDetachAcceptMsg(
                            NAS_MSG_FOR_PCLINT_STRU        *pMsg
                            )
{
    NAS_MSG_STRU                       *pGmmStatus;
    VOS_UINT8                           ucForceToStandby;
    VOS_UINT8                           ucDetachType=0x0;

#if (FEATURE_LTE == FEATURE_ON)
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo;

    pstRplmnCfgInfo = NAS_MML_GetRplmnCfg();
#endif

    if (GMM_MSG_LEN_DETACH_ACCEPT > pMsg->ulNasMsgSize)
    {                                                                           /* 消息中必选项的长度不够长                 */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvDetachAcceptMsg:WARNING: Length of DETACH ACCEPT is invalid");
        pGmmStatus = Gmm_GmmStatusMsgMake(NAS_MML_REG_FAIL_CAUSE_INVALID_MANDATORY_INF);

        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH , pGmmStatus);
        return;                                                                 /* 返回                                     */
    }

    ucForceToStandby = (VOS_UINT8)(pMsg->aucNasMsg[2] & 0x0F);
    if (1 == ucForceToStandby)
    {
        gstGmmCasGlobalCtrl.ucFtsFlg = GMM_TRUE;
    }
    else if (0 == ucForceToStandby)
    {
        gstGmmCasGlobalCtrl.ucFtsFlg = GMM_FALSE;
    }
    else
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvDetachAcceptMsg:WARNING: DETACH ACCEPT is semantically incorrect");
        /*pGmmStatus = Gmm_GmmStatusMsgMake(*/
        /*    NAS_MML_REG_FAIL_CAUSE_SEMANTICALLY_INCORRECT_MSG);*/

        /*Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH , pGmmStatus);*/
        /*return;*/
        gstGmmCasGlobalCtrl.ucFtsFlg = GMM_FALSE;
    }

    switch (g_GmmGlobalCtrl.ucState)
    {                                                                           /* 判断当前状态进行不同处理                 */
    case GMM_DEREGISTERED_INITIATED:                                            /* GMM-DEREGISTERED-INITIATED               */
        Gmm_RcvDetachAcceptMsg_DeregInit();                                     /* 调用该状态下的处理                       */
        ucDetachType = GMM_NET_DETACH_REATTACH_NOT_REQUIRED;
        break;
    case GMM_REGISTERED_IMSI_DETACH_INITIATED:                                  /* GMM-REGISTERED.IMSI-DETACH-INITIATED     */
        Gmm_RcvDetachAcceptMsg_RegImsiDtchInit();                               /* 调用该状态下的处理                       */
        ucDetachType = GMM_NET_DETACH_IMSI_DETACH;
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvDetachAcceptMsg:WARNING: DETACH ACCEPT is unexpected");
        pGmmStatus = Gmm_GmmStatusMsgMake(NAS_MML_REG_FAIL_CAUSE_MSG_NOT_COMPATIBLE);

        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH , pGmmStatus);
        break;
    }

    if (ucDetachType != GMM_NET_DETACH_IMSI_DETACH)
    {
        NAS_GMM_SetAttach2DetachErrCode(GMM_SM_CAUSE_PS_DETACH);
    }

    if (GMM_TRUE == GMM_IsCasGsmMode())
    {

        if ( ucDetachType == GMM_NET_DETACH_IMSI_DETACH )
        {
            if ( GMM_TRUE == gstGmmCasGlobalCtrl.ucFtsFlg )
            {
                gstGmmCasGlobalCtrl.ucFtsFlg = GMM_FALSE;

                if ( 0xffffffff != gstGmmCasGlobalCtrl.ulReadyTimerValue )
                {
                     gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_STANDBY;
                     Gmm_TimerStop(GMM_TIMER_T3314);
                     Gmm_TimerStart(GMM_TIMER_T3312);
                     NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
                }
            }
        }
        else/* detach PS */
        {
            Gmm_ClearLlcData(LL_GMM_CLEAR_DATA_TYPE_ALL);                                                 /* 去指配TLLI，释放LLC层数据 */
            Gmm_TimerStop(GMM_TIMER_T3314);
            gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_IDLE;
            gstGmmCasGlobalCtrl.ulReadyTimerValue = 44000;/* default 44s */

#if (FEATURE_LTE == FEATURE_ON)
            if (GMM_TIMER_T3312_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
            {
                NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
            }

            /* detach ps后如果ISR激活，需要去激活ISR */
            if (NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == NAS_MML_GetTinType())
            {
                NAS_GMM_WriteTinInfoNvim(NAS_MML_TIN_TYPE_PTMSI, pstRplmnCfgInfo->aucLastImsi);
                Gmm_TimerStop(GMM_TIMER_T3323);

                /* ISR去激活，需要更新pdp激活是在ISR激活前激活的 */
                NAS_MML_UpdateAllPsBearIsrFlg(NAS_MML_PS_BEARER_EXIST_BEFORE_ISR_ACT);
            }
#endif
            Gmm_TimerStop(GMM_TIMER_T3312);
            NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
        }

    }
    else
    {
        if (GMM_NET_DETACH_IMSI_DETACH != ucDetachType)
        {
            Gmm_ClearLlcData(LL_GMM_CLEAR_DATA_TYPE_ALL);
#if (FEATURE_LTE == FEATURE_ON)
            if (GMM_TIMER_T3312_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
            {
                NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
            }

            /* detach ps后如果ISR激活，需要去激活ISR */
            if (NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == NAS_MML_GetTinType())
            {
                NAS_GMM_WriteTinInfoNvim(NAS_MML_TIN_TYPE_PTMSI, pstRplmnCfgInfo->aucLastImsi);
                Gmm_TimerStop(GMM_TIMER_T3323);

                /* ISR去激活，需要更新pdp激活是在ISR激活前激活的 */
                NAS_MML_UpdateAllPsBearIsrFlg(NAS_MML_PS_BEARER_EXIST_BEFORE_ISR_ACT);
            }
#endif
            Gmm_TimerStop(GMM_TIMER_T3312);
        }
    }

    return;                                                                     /* 返回                                     */
}


VOS_VOID Gmm_RcvDetachAcceptMsg_DeregInit(VOS_VOID)
{
    Gmm_TimerStop(GMM_TIMER_T3321);                                             /* 停T3321                                  */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* 停止T3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* 停止T3320                                */

    if (GMM_DETACH_NORMAL_NETMODE_CHANGE != g_GmmGlobalCtrl.ucSpecProc)
    {
        NAS_MML_SetPsAttachAllowFlg( VOS_FALSE );             /* 置PS域的attach禁止标志                   */
    }
    /*Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);*/                             /* 调用状态的公共处理                       */
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

    if (GMM_TRUE == GMM_IsCasGsmMode())
    {
        Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);
        /* 判断等待标志是否存在，如果存在则向MMC,MM发送DETACH信息 */
        if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
        {
            NAS_GMM_SndMmcMmDetachInfo();
        }

        else
        {
            /* 收到网侧的去注册成功后需要通知MM，否则MM不启动T3212定时器 */
            NAS_GMM_SndMmGprsDetachComplete();
        }

        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;
    }
    else if (VOS_OK != Mm_StartRelTimer(&g_stGmmProtectRrRelTimer,
                                            WUEPS_PID_GMM,
                                            GMM_TIMER_PROTECT_FOR_RR_REL_VALUE,
                                            GMM_TIMER_PROTECT_FOR_RR_REL,
                                            0,
                                            VOS_RELTIMER_NOLOOP))
    {
        Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);
        /* 判断等待标志是否存在，如果存在则向MMC,MM发送DETACH信息 */
        if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
        {
            NAS_GMM_SndMmcMmDetachInfo();
        }
        else
        {
            /* 收到网侧的去注册成功后需要通知MM，否则MM不启动T3212定时器 */
            NAS_GMM_SndMmGprsDetachComplete();
        }

        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvDetachAcceptMsg_DeregInit:WARNING: Gmm Start Timer fail.");
    }
    else
    {
        g_GmmTimerMng.ulTimerRunMask |= (0x00000001 << GMM_TIMER_PROTECT_FOR_RR_REL);
    }

    /* 向MMC发送PS注册结果 */
    NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                 GMM_MMC_ACTION_RESULT_FAILURE,
                                 NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvDetachAcceptMsg_DeregInit:INFO: specific procedure ended");
    return;                                                                     /* 返回                                     */
}


VOS_VOID Gmm_RcvDetachAcceptMsg_RegImsiDtchInit(VOS_VOID)
{
    Gmm_TimerStop(GMM_TIMER_T3321);                                             /* 停T3321                                  */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* 停止T3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* 停止T3320                                */

    Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);                               /* 调用状态的公共处理                       */
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
        NAS_GMM_SndMmcMmDetachInfo();
    }
    g_GmmGlobalCtrl.ucSpecProc               = GMM_NULL_PROCEDURE;              /* 清除当前进行的specific过程               */
    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvDetachAcceptMsg_RegImsiDtchInit:INFO: specific procedure ended");
    return;                                                                     /* 返回                                     */
}


VOS_VOID NAS_GMM_SetAttach2DetachErrCode(GMM_SM_CAUSE_ENUM_UINT16 enCause)
{
    g_GmmGlobalCtrl.enAttach2DetachCause = enCause;

    return;
}


GMM_SM_CAUSE_ENUM_UINT16 NAS_GMM_GetAttach2DetachErrCode(VOS_VOID)
{
    return g_GmmGlobalCtrl.enAttach2DetachCause;
}




VOS_VOID NAS_GMM_ChangeDetachCauseAvoidInvalidSim(VOS_UINT8 *pucRcvMsg)
{
    NAS_MML_PLMN_ID_STRU               *pstCurrCampPlmnId    = VOS_NULL_PTR;
    VOS_UINT32                          bIsRegisteredInHplmn = VOS_FALSE;

    /* 增加测试卡保护，测试卡时不修改，直接返回 */
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_GMM_ChangeDetachCauseAvoidInvalidSim: The sim is Test card");
        return;
    }

    /* 取得当前驻留的PLMN ID */
    pstCurrCampPlmnId    = NAS_MML_GetCurrCampPlmnId();
    bIsRegisteredInHplmn = NAS_MML_ComparePlmnIdWithHplmn(pstCurrCampPlmnId);

    NAS_MML_SetOriginalRejectCause(*pucRcvMsg);
    if (VOS_TRUE == bIsRegisteredInHplmn)
    {
        /* HPLMN */
        NAS_GMM_HandleHplmnRejCauseChange(NAS_MML_CHANGE_REJ_TYPE_DETACH, pucRcvMsg);
    }
    else
    {
        /* VPLMN */
        NAS_GMM_HandleVplmnRejCauseChange(NAS_MML_CHANGE_REJ_TYPE_DETACH, pucRcvMsg);
    }
}

/*lint -restore */


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

