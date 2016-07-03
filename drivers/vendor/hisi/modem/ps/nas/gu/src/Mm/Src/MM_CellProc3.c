

#include        "MM_Inc.h"
#include        "GmmMmInterface.h"
#include        "NasMmlCtx.h"
#include        "NasMmSndOm.h"


#include "NasStkInterface.h"
#include "NasMmEcall.h"
#include "NasUtranCtrlInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人:luojian 107747;检视人:sunshaohua65952;原因:LOG方案设计需要*/
#define    THIS_FILE_ID        PS_FILE_ID_MM_CELLPROC3_C
/*lint +e767 修改人:luojian 107747;检视人:sunshaohua*/
extern VOS_UINT8 GMM_IsGasCellReselect(VOS_VOID);

/*lint -save -e958 */


VOS_VOID Mm_Cell_S10_E66(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    if (MM_FALSE == Mm_RcvSsRelReq(pRcvMsg))
    {                                                                           /* 消息检查结果失败                         */
    }
    else
    {                                                                           /* 消息检查结果成功                         */

        /*lint -e701*/
        if ((MM_CONST_NUM_7 > g_MmSsRelReq.ulTi)
            && (MM_CONST_NUM_0 !=
            (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0]
            & (0x01 << g_MmSsRelReq.ulTi))))
        {                                                                       /* TI小于7并且该MM连接存在                  */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0] &=
                ~(VOS_UINT32)(0x01 << g_MmSsRelReq.ulTi);                       /* 清除该标志位                             */
        }
        if ((MM_CONST_NUM_7 < g_MmSsRelReq.ulTi)
            && (MM_CONST_NUM_15 > g_MmSsRelReq.ulTi)
            && (MM_CONST_NUM_0 !=
            (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1]
            & (0x01 << (g_MmSsRelReq.ulTi - 8)))))
        {                                                                       /* TI小于7并且该MM连接存在                  */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1] &=
                ~(VOS_UINT32)(0x01 << (g_MmSsRelReq.ulTi - 8));                 /* 清除该标志位                             */
        }
        if ((MM_CONST_NUM_0 ==
          g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0])
          && (MM_CONST_NUM_0 ==
          g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1])
          && (MM_CONST_NUM_0 ==
          g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0])
          && (MM_CONST_NUM_0 ==
          g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1])
          && (MM_CONST_NUM_0 ==
          g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0])
          && (MM_CONST_NUM_0 ==
          g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]))
        {                                                                       /* 没有MM连接存在                           */
            g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                g_MmGlobalInfo.ucStaOfRcvXXEstReq;                              /* 进入空闲的状态                           */
            Mm_ComSaveProcAndCauseVal(MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL);      /* MM连接流程                               */
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* 记录迁移之前的状态                       */
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S10_E66:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
            Mm_TimerStart(MM_TIMER_T3240);                                      /* 启动TIMER3240                            */

            NAS_MML_SetCsServiceConnStatusFlg(VOS_FALSE);
        }


        /*lint +e701*/

    }

    return;
}

VOS_VOID Mm_Cell_S12_E66(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                       )
{
    if (MM_FALSE == Mm_RcvSsRelReq(pRcvMsg))
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S12_E66:WARNING: Rcv SS Rel Req error.");
    }
    else
    {
        if ( (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI == g_MmSsRelReq.ulTi )
          && (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg))
        {
            /* 终止的MM连接建立是正在建立的             */
            if (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucRat == NAS_MML_GetCurrNetRatType())
            {
                Mm_SndRrRelReq(RRC_CELL_UNBARRED);

                g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = g_MmGlobalInfo.ucStaOfRcvXXEstReq;                              /* 返回到接收到建立MM连接请求时的状态       */
                Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
                Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );    /* MM连接流程                               */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E80:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
                Mm_TimerStart(MM_TIMER_T3240);                                      /* 启动TIMER3240                            */
            }
            else
            {
                Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
            }

            Mm_TimerStop( MM_TIMER_PROTECT_SIGNALLING );
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI =
                NO_MM_CONN_ESTING;                                              /* 清除正在建立的MM连接的标志               */

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg = MM_FALSE;

            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* 记录迁移之前的状态                       */

#if (FEATURE_ON == FEATURE_LTE)

            /* 当前存在补充业务的CSFB流程，则清空CSFB存在标志 */
            if (NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST == NAS_MML_GetCsfbServiceStatus())
            {
                NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
            }
#endif
        }
        else
        {
            if (( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg )
             && ( g_MmSsRelReq.ulTi == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId ) )
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                                                 .RcvXXEstReq.ucFlg = MM_FALSE;

#if (FEATURE_ON == FEATURE_LTE)
                /* 当前存在补充业务的CSFB流程，则清空CSFB存在标志 */
                if (NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST == NAS_MML_GetCsfbServiceStatus())
                {
                    NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                    NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
                }
#endif
            }

            NAS_MM_UpdateCsServiceBufferStatusFlg();
        }

    }

    return;
}


VOS_VOID Mm_Cell_S24_E13(VOS_VOID *pMsg)
{
    GMMMM_NETWORK_DETACH_IND_STRU       *pstNetWkDetachInd;


    if (MM_FALSE == NAS_MM_RcvGmmNetworkDetechInd(pMsg))
    {
        return;
    }

    if (NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode())
    {
    }

    pstNetWkDetachInd = (GMMMM_NETWORK_DETACH_IND_STRU*)pMsg;

    g_MmGlobalInfo.ucProc = MM_NET_DETACH_PROC;                                 /* 记录当前的流程                           */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S24_E13:INFO: MmServiceState is MM_NET_DETACH_PROC");

    if (GMMMM_NET_DETACH_REATTACH == pstNetWkDetachInd->enDetachType)
    {
        ;                                                                       /* 空处理                                   */
    }
    else if (GMMMM_NET_DETACH_IMSI == pstNetWkDetachInd->enDetachType)
    {
        Mm_ComSaveProcAndCauseVal(MM_NET_DETACH_PROC,
                                  NAS_MML_REG_FAIL_CAUSE_NTDTH_IMSI);                     /* 记录流程和原因值                         */
        Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S24_E13:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
    }
    else
    {
        switch (pstNetWkDetachInd->ulDetachCause)
        {
        case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
            Mm_ComSaveProcAndCauseVal(MM_NET_DETACH_PROC,
                                     (VOS_UINT8)pstNetWkDetachInd->ulDetachCause);/* 记录流程和原因值                         */
            g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                       /* 设置服务状态                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S24_E13:INFO: MmServiceState is MM_NO_IMSI");
            Mm_ComToNoImsiHandle();                                             /* 调用删除IMSI的公共处理                   */
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* 记录前状态                               */
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S24_E13:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
            break;
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
            g_MmGlobalInfo.ucLikeB = MM_TRUE;                                   /* 设置类似于B模式的全局量                  */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S24_E13:INFO: MmLikeB is MM_TRUE");
            break;
        case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
            Mm_ComSaveProcAndCauseVal(MM_NET_DETACH_PROC,
                                     (VOS_UINT8)pstNetWkDetachInd->ulDetachCause);/* 记录流程和原因值                         */
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S24_E13:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
            break;
        default:
            break;
        }
    }

}


VOS_VOID Mm_Cell_S3_E14(VOS_VOID* pMsg)
{
    VOS_UINT8                                ucActionType = MM_NULL_PROC;
    GMMMM_GMM_ACTION_RESULT_IND_STRU        *pstGmmActionRstInd;
    VOS_UINT8                                ucState;

    ucState                             = g_MmGlobalInfo.ucState;

    if (MM_FALSE == Mm_RcvGmmGmmActionResultInd(pMsg))
    {
        return;
    }

    if (NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode())
    {
    }

    pstGmmActionRstInd = (GMMMM_GMM_ACTION_RESULT_IND_STRU*)pMsg;

    if (GMMMM_ACTION_FAILURE == pstGmmActionRstInd->enActionResult)
    {
        switch (pstGmmActionRstInd->enGmmActionType)
        {
        case GMMMM_ACTION_RAU:
            ucActionType = MM_GMM_RAU_PROC;
            break;
        case GMMMM_ACTION_ATTACH:
            ucActionType = MM_GMM_ATTACH_PROC;
            break;
        case GMMMM_ACTION_SR:
            ucActionType = MM_GMM_SR_PROC;
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S3_E14:WARNING: ulGmmActionType Abnormal");
            break;
        }

        if (VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNtMod))
        {                                                                       /* 如果为A+I,且不是类似B或A+II处理的场合    */
            if (MM_GMM_SR_PROC == ucActionType)
            {
                Mm_ComGmmSrCauseHandle(pstGmmActionRstInd->enCause);   /* 调用SR过程原因值的公共处理               */
            }
        }
        else
        {                                                                       /* 如果为非A+I模式的场合                    */
            if (MM_NULL_PROC != ucActionType)
            {
                Mm_ComCauseHandleAllProc(ucActionType,
                                         pstGmmActionRstInd->enCause); /* 调用原因值的处理                         */

                if ( (NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW == pstGmmActionRstInd->enCause)
                  && ( (MM_IDLE_NORMAL_SERVICE == ucState)
                    || (MM_IDLE_ATTEMPTING_TO_UPDATE == ucState) ) )
                {
                    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                            MM_MMC_LU_RESULT_FAILURE,
                            NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_REG_PRVS_SVS);
                }
            }
        }
    }
}


VOS_VOID Mm_Cell_S24_E14(VOS_VOID* pMsg)
{
    VOS_UINT8                               ucActionType = MM_NULL_PROC;
    GMMMM_GMM_ACTION_RESULT_IND_STRU       *pstGmmActionRstInd;


    if (MM_FALSE == Mm_RcvGmmGmmActionResultInd(pMsg))
    {
        return;
    }

    if (NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode())
    {
    }

    pstGmmActionRstInd = (GMMMM_GMM_ACTION_RESULT_IND_STRU*)pMsg;

    if (GMMMM_ACTION_FAILURE == pstGmmActionRstInd->enActionResult)
    {
        switch (pstGmmActionRstInd->enGmmActionType)
        {
        case GMMMM_ACTION_RAU:
            ucActionType = MM_GMM_RAU_PROC;
            break;
        case GMMMM_ACTION_ATTACH:
            ucActionType = MM_GMM_ATTACH_PROC;
            break;
        case GMMMM_ACTION_SR:
            ucActionType = MM_GMM_SR_PROC;
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S24_E14:WARNING: ulGmmActionType Abnormal");
            break;
        }
        if (MM_NULL_PROC != ucActionType)
        {
            switch (pstGmmActionRstInd->enCause)
            {
            case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
            case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
                Mm_TimerStop(MM_TIMER_PROTECT_AGENT);
                Mm_TimerStop(MM_TIMER_T3210);                               /* 停止T3210                                */
                Mm_ComSaveProcAndCauseVal(ucActionType,
                                          (VOS_UINT8)pstGmmActionRstInd->enCause); /* 记录流程和原因值                         */
                g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;               /* 设置服务状态                             */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S24_E14:INFO: MmServiceState is MM_NO_IMSI");
                Mm_ComToNoImsiHandle();                                     /* 调用删除IMSI的公共处理                   */
                Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S24_E14:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
                break;
            case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
                if (MM_GMM_ATTACH_PROC == ucActionType)
                {
                    Mm_TimerStop(MM_TIMER_PROTECT_AGENT);
                    Mm_TimerStop(MM_TIMER_T3210);                               /* 停止T3210                                */
                    Mm_ComSaveProcAndCauseVal(ucActionType,
                                       (VOS_UINT8)pstGmmActionRstInd->enCause);   /* 记录流程和原因值                         */
                    g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;               /* 设置服务状态                             */
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S24_E14:INFO: MmServiceState is MM_NO_IMSI");
                    Mm_ComToNoImsiHandle();                                     /* 调用删除IMSI的公共处理                   */
                    Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S24_E14:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
                }
                break;
            case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
            case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
                g_MmGlobalInfo.ucLikeB = MM_TRUE;                               /* 设置类似于B模式的全局量                  */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S24_E14:INFO: MmLikeB is MM_TRUE");
                break;
            case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
            case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
            case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
                Mm_ComSaveProcAndCauseVal(ucActionType,
                                       (VOS_UINT8)pstGmmActionRstInd->enCause);   /* 记录流程和原因值                         */
                Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S24_E14:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
                break;

            case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
                /* 在LOCATION UPDATE REJECTED状态下收到PS域拒绝原因值15时按照CS域被拒的原因值处理 */
                break;

            default:
                break;
            }
        }
    }
}
/*******************************************************************************
  Module:   Mm_Cell_S24_E16
  Function: 在LOCATION UPDATE REJECTED状态下,
                收到MMCMM_AUTHENTICATON_FAILURE_IND的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2004.03.12  新版做成
*******************************************************************************/

VOS_VOID Mm_Cell_S24_E16(VOS_VOID* pMsg)
{
    if (MM_FALSE == Mm_RcvGmmAuthFailInd(pMsg))
    {
        return;
    }

    Mm_ComSaveProcAndCauseVal(MM_AUTH_FAIL_PROC, NAS_MML_REG_FAIL_CAUSE_NULL);            /* 记录流程和原因值                         */
    g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                               /* 设置服务状态                             */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S24_E16:INFO: MmServiceState is MM_NO_IMSI");
    Mm_ComToNoImsiHandle();                                                     /* 调用删除IMSI的公共处理                   */
    Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S24_E16:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
}


VOS_VOID Mm_Cell_S25_E16(VOS_VOID* pMsg)
{
    if (MM_FALSE == Mm_RcvGmmAuthFailInd(pMsg))
    {
        return;
    }

    Mm_SndRrRelReq(RRC_CELL_UNBARRED);
    Mm_ComToNoImsiHandle();

    Mm_TimerStart(MM_TIMER_PROTECT_DETACH);
    Mm_ComSetMmState(IMSI_DETACH_INITIATED);


    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S25_E16:NORMAL: STATUS is MM_STATE_NULL");
}
/*******************************************************************************
  Module:   Mm_Cell_S26_E16
  Function: 在IMSI DETACH INITIATED状态下,
                            收到GMMMM_AUTHENTICATON_FAILURE_IND的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2004.03.12  新版做成
*******************************************************************************/
VOS_VOID Mm_Cell_S26_E16(VOS_VOID* pMsg)
{
    if (MM_FALSE == Mm_RcvGmmAuthFailInd(pMsg))
    {
        return;
    }

    Mm_ComToNoImsiHandle();
}

VOS_VOID Mm_Cell_S3_E22(VOS_VOID* pMsg)
{
    MMCMM_DETACH_REQ_STRU*          pMmcDetachReq;

    MM_MSG_IMSI_DETACH_IND_STRU     Msg;

    if (MM_FALSE == Mm_RcvMmcDetachReq(pMsg))
    {
        return;
    }

    pMmcDetachReq = (MMCMM_DETACH_REQ_STRU*)pMsg;



    /* 当前是否由GMM处理用户发起的detach */
    if ( VOS_TRUE == NAS_MM_IsNeedGmmProcUserDetach() )
    {
        g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_NORMAL;
        return;
    }

    if (MMC_MM_PS_DETACH != pMmcDetachReq->enDetachType)
    {
        Mm_TimerStop(MM_TIMER_T3212);                                           /* 停止T3212                                */
        if (MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
        {
            if (MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg)
            {
                NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);                         /* 设置禁止注册CS域的标识                   */

                g_MmGlobalInfo.ucMmServiceState = MM_DETACHED;              /* 设置服务状态                             */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S3_E22:INFO: MmServiceState is MM_DETACHED");
                Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                                 NAS_MML_GetSimCsSecurityCksn());     /* 设置MM信息                               */

                /* 判断等待标志是否存在，如果存在则发送MMCGMM_DETACH CNF */
                if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                             & MM_WAIT_CS_DETACH))
                {
                    NAS_MM_SndMmcDetachCnf(MM_DETACHED);
                    /* 清除等待标志 */
                    g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
                }

                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                            MM_MMC_LU_RESULT_FAILURE,
                                            NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

                Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E22:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");

            }
            else
            {
                g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_NORMAL;          /* 设置DETACH类型                           */

                NAS_MM_FillMobileID(&(Msg.MmIeMobileId.MobileID));

                g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;

                Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_IMSI_DETACH);

                Mm_ComMsgImsiDetachIniSndOfEstReq(&Msg);                        /* 填写消息,发送消息                        */

                Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);                     /* 启动保护TIMER                            */

                NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);


                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E22:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_IMSI_DETACH");
                g_MmGlobalInfo.ucMmServiceState = MM_DETACHED;                  /* 设置服务状态                             */
            }
        }
        else if (MM_STATUS_DETACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
        {
            NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);                             /* 设置禁止注册CS域的标识                   */
            g_MmGlobalInfo.ucMmServiceState = MM_DETACHED;                  /* 设置服务状态                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S3_E22:INFO: MmServiceState is MM_DETACHED");
            Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                             NAS_MML_GetSimCsSecurityCksn());         /* 设置MM信息                               */

            /* 判断等待标志是否存在，如果存在则发送MMCGMM_DETACH CNF */
            if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                         & MM_WAIT_CS_DETACH))
            {
                NAS_MM_SndMmcDetachCnf(MM_DETACHED);
                /* 清除等待标志 */
                g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
            }

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E22:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
        }
        else
        {

        }
    }

}

VOS_VOID Mm_Cell_S4_E22(VOS_VOID* pMsg)
{
    MMCMM_DETACH_REQ_STRU*   pMmcDetachReq;

    if (MM_FALSE == Mm_RcvMmcDetachReq(pMsg))
    {
        return;
    }

    pMmcDetachReq = (MMCMM_DETACH_REQ_STRU*)pMsg;

    if (MMC_MM_PS_DETACH != pMmcDetachReq->enDetachType)
    {
        Mm_TimerStop(MM_TIMER_T3212);                                           /* 停止T3212                                */
        NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
        g_MmGlobalInfo.ucMmServiceState = MM_DETACHED;                      /* 设置服务状态                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S4_E22:INFO: MmServiceState is MM_DETACHED");
        Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                         NAS_MML_GetSimCsSecurityCksn());             /* 设置MM信息                               */

        /* 判断等待标志是否存在，如果存在则发送MMCMM_DETACH CNF */
        if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                     & MM_WAIT_CS_DETACH))
        {
            NAS_MM_SndMmcDetachCnf(MM_DETACHED);
            /* 清除等待标志 */
            g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
        }

        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);


        if ( MM_IDLE_ATTEMPTING_TO_UPDATE == g_MmGlobalInfo.ucState )
        {
            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
        }


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S4_E22:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
    }
}

VOS_VOID Mm_Cell_S6_E22(VOS_VOID* pMsg)
{
    NAS_MM_COM_SERVICE_STATUS_ENUM_UINT8                    enServiceStatus;

    enServiceStatus = NAS_MM_GetLauUptNeededCsSrvStatus();

    if ((VOS_FALSE == NAS_MML_GetCsRestrictRegisterFlg())
     || (MM_COM_SRVST_NORMAL_SERVICE == enServiceStatus))
    {
        Mm_Cell_S3_E22(pMsg);
    }
    else
    {
        Mm_Cell_S4_E22(pMsg);
    }
}

VOS_VOID Mm_Cell_S8_E22(VOS_VOID* pMsg)
{
    MMCMM_DETACH_REQ_STRU*   pMmcDetachReq;

    if (MM_FALSE == Mm_RcvMmcDetachReq(pMsg))
    {
        return;
    }

    pMmcDetachReq = (MMCMM_DETACH_REQ_STRU*)pMsg;

    if (MMC_MM_PS_DETACH != pMmcDetachReq->enDetachType)
    {
        NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
        g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                           /* 设置服务状态                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S8_E22:INFO: MmServiceState is MM_NO_IMSI");

        /* 判断等待标志是否存在，如果存在则发送MMCMM_DETACH CNF */
        if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                     & MM_WAIT_CS_DETACH))
        {
            NAS_MM_SndMmcDetachCnf(MM_NO_IMSI);
            /* 清除等待标志 */
            g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
        }


        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    NAS_MML_REG_FAIL_CAUSE_SIM_INVALID);

    }
}

VOS_VOID Mm_Cell_S9_E22(VOS_VOID* pMsg)
{
    MMCMM_DETACH_REQ_STRU*          pMmcDetachReq;

    MM_MSG_IMSI_DETACH_IND_STRU     Msg;

    if (MM_FALSE == Mm_RcvMmcDetachReq(pMsg))
    {
        return;
    }

    pMmcDetachReq = (MMCMM_DETACH_REQ_STRU*)pMsg;



    /* 当前是否由GMM处理用户发起的detach */
    if ( VOS_TRUE == NAS_MM_IsNeedGmmProcUserDetach() )
    {
        /* 停等待保护定时器 */
        Mm_TimerStop(MM_TIMER_T3218);

        /* 在鉴权过程中，则清除鉴权标志信息 */
        if ( MM_RCV_AUTH_CNF_FLG == (g_MmGlobalInfo.ucRcvAgentFlg & MM_RCV_AUTH_CNF_FLG) )
        {
            g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;

            /* 停止保护定时器 */
            Mm_TimerStop(MM_TIMER_PROTECT_AGENT);
        }

        Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

                Mm_SndRrRelReq(RRC_CELL_UNBARRED);
                g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
                Mm_ComSetMmState(IMSI_DETACH_PENDING);

                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E22:NORMAL: STATUS is IMSI_DETACH_PENDING");
        /* Mm_SndMmcCmSvcInd在Mm_ComRelAllMmConn中上报 */

                if (MMC_MM_PS_DETACH != pMmcDetachReq->enDetachType)
                {
                    g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_NORMAL;
                }

        return;
    }

    if (MMC_MM_PS_DETACH != pMmcDetachReq->enDetachType)
    {
        Mm_TimerStop(MM_TIMER_T3212);                                           /* 停止T3212                                */
        g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_NORMAL;                  /* 设置DETACH类型                           */

        Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

        if ((MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg)
            || (MM_STATUS_ATTACHED !=
                        g_MmSubLyrShare.MmShare.ucCsAttachState))
        {
            Mm_SndRrRelReq(RRC_CELL_UNBARRED);
            NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
            Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                             NAS_MML_GetSimCsSecurityCksn());         /* 设置MM信息                               */

            /* 判断等待标志是否存在，如果存在则发送MMCMM_DETACH CNF */
            if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                         & MM_WAIT_CS_DETACH))
            {
                NAS_MM_SndMmcDetachCnf(MM_DETACHED);
                /* 清除等待标志 */
                g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
            }

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

            Mm_ComSaveProcAndCauseVal(MM_IMSI_DETACH, NAS_MML_REG_FAIL_CAUSE_NULL);       /* 记录流程和原因值                         */
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E22:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
            Mm_TimerStart(MM_TIMER_T3240);                                      /* 启动T3240                                */
        }
        else
        {
            NAS_MM_FillMobileID(&(Msg.MmIeMobileId.MobileID));                  /* 填写MobileID                             */

            Mm_ComSetMmState(IMSI_DETACH_INITIATED);

            Mm_ComMsgImsiDetachIniSndOfDataReq(&Msg);                           /* 填写消息,发送消息                        */
            Mm_TimerStart(MM_TIMER_T3220);                                      /* 启动T3220                                */


            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E22:NORMAL: STATUS is IMSI_DETACH_INITIATED");
        }

    }
}

VOS_VOID Mm_Cell_S12_E22(VOS_VOID* pMsg)
{
    MMCMM_DETACH_REQ_STRU*          pMmcDetachReq;

    MM_MSG_IMSI_DETACH_IND_STRU     Msg;

    if (MM_FALSE == Mm_RcvMmcDetachReq(pMsg))
    {
        return;
    }

    pMmcDetachReq = (MMCMM_DETACH_REQ_STRU*)pMsg;


    /* 当前是否由GMM处理用户发起的detach */
    if ( VOS_TRUE == NAS_MM_IsNeedGmmProcUserDetach() )
    {
        Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

        if ( VOS_TRUE == NAS_MML_GetCsSigConnStatusFlg() )
        {
            Mm_SndRrRelReq(RRC_CELL_UNBARRED);
        }

        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
        Mm_ComSetMmState(IMSI_DETACH_PENDING);

        /* Mm_SndMmcCmSvcInd在Mm_ComRelAllMmConn中上报 */
        if (MMC_MM_PS_DETACH != pMmcDetachReq->enDetachType)
        {
            g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_NORMAL;
        }

        return;
    }

    if (MMC_MM_PS_DETACH != pMmcDetachReq->enDetachType)
    {
        Mm_TimerStop(MM_TIMER_T3212);                                           /* 停止T3212                                */
        if ((MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg)
            || (MM_STATUS_ATTACHED !=
                                g_MmSubLyrShare.MmShare.ucCsAttachState))
        {
            NAS_MM_LocalDetach();


            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E22:NORMAL: STATUS is MM_IDLE_NO_IMSI");
        }
        else
        {
            g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_NORMAL;              /* 设置DETACH类型                           */

            Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

            if ( VOS_TRUE == NAS_MML_GetCsSigConnStatusFlg() )
            {
                /* 继续等待建链结果 */
                return;
            }

            /* 停止WAIT_FOR_REESTABLISH_WAIT_FOR_REEST_REQ状态的保护定时器 */
            Mm_TimerStop(MM_TIMER_PROTECT_CC);

            NAS_MM_FillMobileID(&(Msg.MmIeMobileId.MobileID));

            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;

            Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_IMSI_DETACH);

            Mm_ComMsgImsiDetachIniSndOfEstReq(&Msg);                            /* 填写消息,发送消息                        */

            Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);                         /* 启动保护TIMER                            */

            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);


            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E22:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_IMSI_DETACH");
        }
    }
}

VOS_VOID Mm_Cell_S14_E22(VOS_VOID* pMsg)
{
    MMCMM_DETACH_REQ_STRU*          pMmcDetachReq;

    if (MM_FALSE == Mm_RcvMmcDetachReq(pMsg))
    {
        return;
    }

    pMmcDetachReq = (MMCMM_DETACH_REQ_STRU*)pMsg;


    /* 当前是否由GMM处理用户发起的detach */
    if ( VOS_TRUE == NAS_MM_IsNeedGmmProcUserDetach() )
    {
        Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

        if ( VOS_TRUE == NAS_MML_GetCsSigConnStatusFlg() )
        {
            Mm_SndRrRelReq(RRC_CELL_UNBARRED);
        }

        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
        Mm_ComSetMmState(IMSI_DETACH_PENDING);

        /* Mm_SndMmcCmSvcInd在Mm_ComRelAllMmConn中上报 */

        if (MMC_MM_PS_DETACH != pMmcDetachReq->enDetachType)
        {
            g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_NORMAL;
        }

        return;
    }

    if (MMC_MM_PS_DETACH != pMmcDetachReq->enDetachType)
    {

        if ((MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg)
            || (MM_STATUS_ATTACHED !=
                         g_MmSubLyrShare.MmShare.ucCsAttachState))
        {
            NAS_MM_LocalDetach();

        }
        else
        {

            Mm_TimerStop(MM_TIMER_T3212);                                           /* 停止T3212                                */
            g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_NORMAL;                      /* 设置DETACH类型                           */

            Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);


            /* 等建链成功后再发起IMSI DETACH */
        }
    }
}

VOS_VOID Mm_Cell_S0_E23(VOS_VOID* pMsg)
{

    if (MM_FALSE == Mm_RcvMmcPowerOffReq(pMsg))
    {
        return;
    }

    Mm_TimerStop(MM_TIMER_T3212);                                               /* 停止T3212                                */

    Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                     NAS_MML_GetSimCsSecurityCksn());                     /* 设置MM信息                               */

    Mm_SndMmcPowerOffCnf();                                                     /* 向MMC发送MMCMM_POWER_OFF_CNF             */

    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {
        MM_SndMmcRrRelInd(RRC_REL_CAUSE_RR_NORM_EVENT);
    }

    Mm_ComSetMmState(MM_STATE_NULL);

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S0_E23:NORMAL: STATUS is MM_STATE_NULL");
}

VOS_VOID Mm_Cell_S3_E23(VOS_VOID* pMsg)
{

    MM_MSG_IMSI_DETACH_IND_STRU     Msg;

    if (MM_FALSE == Mm_RcvMmcPowerOffReq(pMsg))
    {
        return;

    }

#if (FEATURE_ON == FEATURE_LTE)

    /* 如果当前驻留LTE,则直接回复关机 */
    if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
        g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;                        /* 设置服务状态                             */
        Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                         NAS_MML_GetSimCsSecurityCksn());                 /* 设置MM信息                               */
        Mm_SndMmcPowerOffCnf();                                                 /* 向MMC发送MMCMM_POWER_OFF_CNF             */

        Mm_ComSetMmState(MM_STATE_NULL);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E23:NORMAL: STATUS is MM_STATE_NULL");

        return;
    }
#endif

    if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
     && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod))
    {                                                                           /* 如果为A+I模式                            */
        if ((VOS_FALSE == NAS_MML_GetPsRestrictRegisterFlg())
         && (MM_FALSE == g_MmGlobalInfo.ucLikeB)
         && (GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta))
        {


            Mm_TimerStart(MM_TIMER_MODE_I_CS_PS_POWER_OFF_PROTECT);

            g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_POWEROFF;                /* 设置DETACH类型                           */
            return;                                                             /* 不是类似B或者A+II模式的场合              */
        }
    }
    Mm_TimerStop(MM_TIMER_T3212);                                               /* 停止T3212                                */

    if (MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
    {

        if (MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg)
        {
            NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
            g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;                    /* 设置服务状态                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S3_E23:INFO: MmServiceState is MM_NO_IMSI");
            Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                             NAS_MML_GetSimCsSecurityCksn());             /* 设置MM信息                               */
            Mm_SndMmcPowerOffCnf();
            Mm_ComSetMmState(MM_STATE_NULL);

            MM_SndMmcRrRelInd(RRC_REL_CAUSE_RR_NORM_EVENT);

            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E23:NORMAL: STATUS is MM_STATE_NULL");
        }
        else
        {
            g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_POWEROFF;                /* 设置DETACH类型                           */

            NAS_MM_FillMobileID(&(Msg.MmIeMobileId.MobileID));

            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
            Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_IMSI_DETACH);

            Mm_ComMsgImsiDetachIniSndOfEstReq(&Msg);                            /* 填写消息,发送消息                        */
            Mm_TimerStart(MM_TIMER_PROTECT_DETACH);



            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E23:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_IMSI_DETACH");
        }

    }
    else if (MM_STATUS_DETACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
    {
        NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
        g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;                        /* 设置服务状态                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S3_E23:INFO: MmServiceState is MM_NO_SERVICE");
        Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                         NAS_MML_GetSimCsSecurityCksn());                 /* 设置MM信息                               */
        Mm_SndMmcPowerOffCnf();                                                 /* 向MMC发送MMCMM_POWER_OFF_CNF             */

        if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
        {
            MM_SndMmcRrRelInd(RRC_REL_CAUSE_RR_NORM_EVENT);
        }

        Mm_ComSetMmState(MM_STATE_NULL);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E23:NORMAL: STATUS is MM_STATE_NULL");

    }
    else
    {
    }
    return;
}

VOS_VOID Mm_Cell_S9_E23(VOS_VOID* pMsg)
{

    MM_MSG_IMSI_DETACH_IND_STRU     Msg;

    if (MM_FALSE == Mm_RcvMmcPowerOffReq(pMsg))
    {
        return;
    }
    Mm_TimerStop(MM_TIMER_STOP_ALL);

    g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_POWEROFF;                        /* 设置DETACH类型                           */

    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

    if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
     && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod))
    {                                                                           /* 如果为A+I模式                            */
        if ((VOS_FALSE == NAS_MML_GetPsRestrictRegisterFlg())
         && (MM_FALSE == g_MmGlobalInfo.ucLikeB)
         && (GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta))
        {

            Mm_TimerStart(MM_TIMER_MODE_I_CS_PS_POWER_OFF_PROTECT);

            Mm_SndRrRelReq(RRC_CELL_UNBARRED);
            g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = g_MmGlobalInfo.ucStaOfRcvXXEstReq;
            Mm_TimerStart(MM_TIMER_T3240);
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E23:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
            return;                                                             /* 不是类似B或者A+II模式的场合              */
        }
    }

    if (MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
    {
        if (MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg)
        {
            Mm_SndRrRelReq(RRC_CELL_UNBARRED);
            g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;                    /* 设置服务状态                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S9_E23:INFO: MmServiceState is MM_NO_SERVICE");
            Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                             NAS_MML_GetSimCsSecurityCksn());             /* 设置MM信息                               */

            Mm_TimerStart(MM_TIMER_PROTECT_DETACH);
            Mm_ComSetMmState(IMSI_DETACH_INITIATED);


            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E23:NORMAL: STATUS is MM_STATE_NULL");
        }
        else
        {
            NAS_MM_FillMobileID(&(Msg.MmIeMobileId.MobileID));

            Mm_ComSetMmState(IMSI_DETACH_INITIATED);
            Mm_ComMsgImsiDetachIniSndOfDataReq(&Msg);                           /* 填写消息,发送消息                        */
            Mm_TimerStart(MM_TIMER_T3220);                                      /* 启动T3220                                */
            Mm_TimerStart(MM_TIMER_PROTECT_DETACH);


            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E23:NORMAL: STATUS is IMSI_DETACH_INITIATED");
        }
    }
    else
    {
        Mm_SndRrRelReq(RRC_CELL_UNBARRED);
        g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;                        /* 设置服务状态                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S9_E23:INFO: MmServiceState is MM_NO_SERVICE");

        Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                         NAS_MML_GetSimCsSecurityCksn());                 /* 设置MM信息                               */

        Mm_TimerStart(MM_TIMER_PROTECT_DETACH);
        Mm_ComSetMmState(IMSI_DETACH_INITIATED);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E23:NORMAL: STATUS is MM_STATE_NULL");
    }
}

VOS_VOID Mm_Cell_S12_E23(VOS_VOID* pMsg)
{

    MM_MSG_IMSI_DETACH_IND_STRU     Msg;

    if (MM_FALSE == Mm_RcvMmcPowerOffReq(pMsg))
    {
        return;

    }

    if ( (VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
      && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod))
    {                                                                           /* 如果为A+I模式                            */
        if ((VOS_FALSE == NAS_MML_GetPsRestrictRegisterFlg())
         && (MM_FALSE == g_MmGlobalInfo.ucLikeB)
         && (GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta))
        {

            Mm_TimerStart(MM_TIMER_MODE_I_CS_PS_POWER_OFF_PROTECT);

            g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_POWEROFF;                /* 设置DETACH类型                           */
            return;                                                             /* 不是类似B或者A+II模式的场合              */
        }
    }

    Mm_TimerStop(MM_TIMER_STOP_ALL);
    g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_POWEROFF;                        /* 设置DETACH类型                           */

    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

    Mm_SndRrRelReq(RRC_CELL_UNBARRED);

    if (MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
    {
        if (MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg)
        {
            g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;                    /* 设置服务状态                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S12_E23:INFO: MmServiceState is MM_NO_SERVICE");
            Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                             NAS_MML_GetSimCsSecurityCksn());             /* 设置MM信息                               */

            Mm_TimerStart(MM_TIMER_PROTECT_DETACH);
            Mm_ComSetMmState(IMSI_DETACH_INITIATED);


            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E23:NORMAL: STATUS is MM_STATE_NULL");
        }
        else
        {
            NAS_MM_FillMobileID(&(Msg.MmIeMobileId.MobileID));

            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
            Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_IMSI_DETACH);
            Mm_ComMsgImsiDetachIniSndOfEstReq(&Msg);                            /* 填写消息,发送消息                        */

            Mm_TimerStart(MM_TIMER_PROTECT_DETACH);


            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E23:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_IMSI_DETACH");
        }
    }
    else
    {
        g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;                        /* 设置服务状态                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S12_E23:INFO: MmServiceState is MM_NO_SERVICE");
        Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                         NAS_MML_GetSimCsSecurityCksn());                 /* 设置MM信息                               */

        Mm_TimerStart(MM_TIMER_PROTECT_DETACH);
        Mm_ComSetMmState(IMSI_DETACH_INITIATED);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E23:NORMAL: STATUS is MM_STATE_NULL");
    }
}


VOS_VOID Mm_Cell_S14_E23(VOS_VOID* pMsg)
{

    MM_MSG_IMSI_DETACH_IND_STRU     Msg;

    if (MM_FALSE == Mm_RcvMmcPowerOffReq(pMsg))
    {
        return;
    }

    if ( (VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
      && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod))
    {                                                                           /* 如果为A+I模式                            */
        if ((VOS_FALSE == NAS_MML_GetPsRestrictRegisterFlg())
         && (MM_FALSE == g_MmGlobalInfo.ucLikeB)
         && (GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta))
        {


            Mm_TimerStart(MM_TIMER_MODE_I_CS_PS_POWER_OFF_PROTECT);

            g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_POWEROFF;                /* 设置DETACH类型                           */
            return;                                                             /* 不是类似B或者A+II模式的场合              */
        }
    }

    Mm_TimerStop(MM_TIMER_STOP_ALL);
    g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_POWEROFF;                        /* 设置DETACH类型                           */

    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

    if (MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
    {
        if (MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg)
        {
            Mm_SndRrRelReq(RRC_CELL_UNBARRED);
            g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;                    /* 设置服务状态                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S14_E23:INFO: MmServiceState is MM_NO_SERVICE");

            Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                             NAS_MML_GetSimCsSecurityCksn());             /* 设置MM信息                               */

            Mm_TimerStart(MM_TIMER_PROTECT_DETACH);
            Mm_ComSetMmState(IMSI_DETACH_INITIATED);


            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S14_E23:NORMAL: STATUS is MM_STATE_NULL");
        }
        else
        {
            if (MM_CS_SIG_CONN_PRESENT == g_MmGlobalInfo.ucCsSigConnFlg)
            {
                NAS_MM_FillMobileID(&(Msg.MmIeMobileId.MobileID));

                Mm_ComSetMmState(IMSI_DETACH_INITIATED);

                Mm_ComMsgImsiDetachIniSndOfDataReq(&Msg);                       /* 填写消息,发送消息                        */
                Mm_TimerStart(MM_TIMER_T3220);                                  /* 启动保护定时器                           */
                Mm_TimerStart(MM_TIMER_PROTECT_DETACH);


                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S14_E23:NORMAL: STATUS is IMSI_DETACH_INITIATED");
            }
            else
            {
                Mm_SndRrRelReq(RRC_CELL_UNBARRED);

                NAS_MM_FillMobileID(&(Msg.MmIeMobileId.MobileID));

                g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
                Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_IMSI_DETACH);
                Mm_ComMsgImsiDetachIniSndOfEstReq(&Msg);                        /* 填写消息,发送消息                        */

                Mm_TimerStart(MM_TIMER_PROTECT_DETACH);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S14_E23:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_IMSI_DETACH");
            }

        }
    }
    else
    {
        Mm_SndRrRelReq(RRC_CELL_UNBARRED);
        g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;                        /* 设置服务状态                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S14_E23:INFO: MmServiceState is MM_NO_SERVICE");

        Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                         NAS_MML_GetSimCsSecurityCksn());                 /* 设置MM信息                               */

        Mm_TimerStart(MM_TIMER_PROTECT_DETACH);
        Mm_ComSetMmState(IMSI_DETACH_INITIATED);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S14_E23:NORMAL: STATUS is MM_STATE_NULL");
    }
}

VOS_VOID Mm_Cell_S22_E23(VOS_VOID* pMsg)
{

    if (MM_FALSE == Mm_RcvMmcPowerOffReq(pMsg))
    {
        return;
    }

    g_MmGlobalInfo.ucDetachType = MM_DETACH_NEED_DELAY;                        /* 设置DETACH类型                           */
    Mm_TimerStart(MM_TIMER_PROTECT_DETACH);
}
/*******************************************************************************
  Module:   Mm_Cell_S25_E23
  Function: 在WAIT FOR RR CONNECTION (IMSI DETACH)状态下,收到MMCMM_POWER_OFF_REQ的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2004.03.15  新版做成
*******************************************************************************/
VOS_VOID Mm_Cell_S25_E23(VOS_VOID* pMsg)
{

    if (MM_FALSE == Mm_RcvMmcPowerOffReq(pMsg))
    {
        return;
    }

    g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_POWEROFF;                        /* 设置DETACH类型                           */
}


VOS_UINT32 NAS_MM_IsNeedStopT3213_EstCnf(
    RRC_NAS_EST_RESULT_ENUM_UINT32      ulResult
)
{
    if ((RRC_EST_RANDOM_ACCESS_REJECT != ulResult)
     && (RRC_EST_RANDOM_ACCESS_REJECT_NO_VALID_INFO != ulResult)
     && (RRC_EST_RJ_RA_FAIL != ulResult)
     && (RRC_EST_RJ_RA_FAIL_NO_VALID_INFO != ulResult))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}


VOS_VOID Mm_Cell_S22_E32(VOS_VOID* pMsg)
{
    RRMM_EST_CNF_STRU*                                      pRrcEstCnf;
    VOS_UINT8                                               ucTiValidFlg;
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8               enCsUpdateStatus;
    MM_LAI_STRU                                            *pstAttLaiInfo   = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                                       *pstCampLaiInfo  = VOS_NULL_PTR;
    VOS_UINT32                                              ulIsGsmOnlyEstCnfRslt;
    VOS_UINT32                                  ulIsTestCard;

    ulIsTestCard    = NAS_USIMMAPI_IsTestCard();
    ucTiValidFlg = MM_TRUE;

    if (MM_FALSE == Mm_RcvRrcEstCnf(pMsg))
    {
        return;
    }

    pRrcEstCnf = (RRMM_EST_CNF_STRU*)pMsg;



    NAS_MM_SetEstCnfResult(pRrcEstCnf->ulResult);


    /* 处理当前缓存的CS域去注册 */
    /* 24008_CR1201R1_(Rel-8)_C1-082683 24008 4.3.4章节描述:If a RR connection
       exists and the ATT flag indicates that no detach procedure is required,
       the MM sublayer will release locally any ongoing MM connections before
       releasing the RR connection. If a MM specific procedure is active,
       the release of the RR connection may be delayed until the MM specific
       procedure is complete. lau结束后连接释放时再做本地detach,如果lau建链失败则做本地detach */
    if (VOS_TRUE == NAS_MM_IsNeedProcBufferedCsDetach_RcvLauEstCnf(pRrcEstCnf->ulResult))
    {
        Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

        NAS_MM_RcvRrMmEstCnf_ExistCsDetachBuffer(pRrcEstCnf);

        return;
    }



    if (NAS_MM_IsNeedStopT3213_EstCnf(pRrcEstCnf->ulResult))
    {
        g_MmGlobalInfo.LuInfo.ucT3213AttmptCnt = 0;
        Mm_TimerStop(MM_TIMER_T3213);                                           /* 停止随机接入失败的过程 */
    }

    if ((RRC_EST_SUCCESS != pRrcEstCnf->ulResult)
        && (RRC_EST_PRESENT != pRrcEstCnf->ulResult))
    {
        /*如果PS ONLY，则直接进入limit service*/
        if (NAS_MML_MS_MODE_PS_ONLY == NAS_MML_GetMsMode())
        {
            Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

            Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S22_E32:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
            Mm_ComCheckDelayMmConn(MM_FALSE);

#if (FEATURE_ON == FEATURE_ECALL)
            /* PS ONLY在ECALL ONLY模式下不设置CS不允许attach标记*/
            if (NAS_MML_ECALL_ONLY == NAS_MML_GetCallMode())
            {
                return;
            }
#endif

            NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
            return;
        }
    }

    switch(pRrcEstCnf->ulResult)
    {
    case RRC_EST_SUCCESS:
    case RRC_EST_PRESENT:

        Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

        if (RRC_EST_PRESENT == pRrcEstCnf->ulResult)
        {
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S22_E32:WARNING: RR CONNECTION PRESENT!");
        }

        g_MmGlobalInfo.LuInfo.ucImmAccRejLuAttmptCnt = 0;
        Mm_TimerStart(MM_TIMER_T3210);                                          /* 启动保护定时器                           */
        g_MmGlobalInfo.ucCsSigConnFlg = MM_CS_SIG_CONN_PRESENT;                 /* 设置信令连接已存在                       */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S22_E32:INFO: MmCsSigConnFlg is MM_CS_SIG_CONN_PRESENT");
        Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ESTED);                            /* RR连接建立成功                           */
        Mm_ComSetMmState(LOCATION_UPDATING_INITIATED);

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S22_E32:NORMAL: STATUS is LOCATION_UPDATING_INITIATED");
        break;
    case RRC_EST_ESTING:
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S22_E32:WARNING: RR CONNECTION ESTING!");
        break;

    case RRC_EST_RJ_CONGEST:
    case RRC_EST_RJ_UNSPEC:
    case RRC_EST_EST_CONN_FAIL:
    case RRC_EST_RJ_NOT_ALLOW:
    case RRC_EST_RJ_TIME_OUT:
    case RRC_EST_RJ_RA_RESOURCE_FAIL:
    case RRC_EST_RJ_IMMEDIATE_ASSIGN_INVALID:
    case RRC_EST_RJ_ACTIVE_PHISICAL_CHANNEL_FAIL:
    case RRC_EST_RJ_AIRMSG_DECODE_ERR:
    case RRC_EST_RJ_FASTRETURN_LTE:
    case RRC_EST_RJ_CURR_PROTOCOL_NOT_SUPPORT:
    case RRC_EST_RJ_SNW:
    case RRC_EST_RANDOM_ACCESS_REJECT:
    case RRC_EST_RJ_RA_FAIL:
    case RRC_EST_RJ_RA_FAIL_NO_VALID_INFO:


    case RRC_EST_RANDOM_ACCESS_REJECT_NO_VALID_INFO:

        Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

        /* 仅在2G网络下处理结果原因RRC_EST_RANDOM_ACCESS_REJECT */
        ulIsGsmOnlyEstCnfRslt = NAS_MM_IsGsmOnlyEstCnfRslt(pRrcEstCnf->ulResult);

        if ((NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
         && (VOS_TRUE == ulIsGsmOnlyEstCnfRslt))
        {
            g_MmGlobalInfo.LuInfo.ucT3213AttmptCnt++;

            /* 最多允许两次连续的随机接入失败尝试 */
            if (g_MmGlobalInfo.LuInfo.ucT3213AttmptCnt < MM_CONST_NUM_2)
            {
                g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_FALSE;
                Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);
                Mm_TimerStop(MM_TIMER_T3213);
                Mm_TimerStart(MM_TIMER_T3213);                                  /* 启动T3213 */
                Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );
                NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
                break;
            }

            Mm_TimerStop(MM_TIMER_T3213);                                       /* 停止随机接入失败的过程 */
        }

        if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
        {
            g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_TRUE;

            if ( (VOS_TRUE == ulIsTestCard)
              && ((RRC_EST_RANDOM_ACCESS_REJECT == pRrcEstCnf->ulResult)
               || (RRC_EST_RJ_RA_FAIL == pRrcEstCnf->ulResult)) )
            {
                g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_FALSE;
            }
        }
        else
        {
            g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_FALSE;
        }

        NAS_MM_ProcLuAttemptCounter(pRrcEstCnf->ulResult);


        if (g_MmGlobalInfo.LuInfo.ucLuAttmptCnt < MM_CONST_NUM_4)
        {
            enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
            if ((VOS_FALSE == NAS_MML_IsCsLaiChanged())
                && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus))
            {                                                                   /* 如果LAI不变,且更新状态为U1的时候         */
                g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;             /* 记录前状态                               */
                g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;
                Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S22_E32:INFO: MmServiceState is MM_NORMAL_SERVICE");


                NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

                /* NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                              MM_MMC_LU_RESULT_FAILURE,
                                              NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL); */           /* 向MMC发送MMCMM_LU_RESULT_IND             */
                NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                         NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);            /* 向MMC发送MMCMM_LU_RESULT_IND             */


                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                            MM_MMC_LU_RESULT_FAILURE,
                                            NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

                Mm_ComNasInfoSav(MM_STATUS_ATTACHED,
                                 NAS_MML_GetSimCsSecurityCksn());
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S22_E32:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
                Mm_TimerStart(MM_TIMER_T3211);                                  /* 启动T3211                                */
                g_T3211Flag = 1;
            }
            else
            {
                g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S22_E32:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");


                /* GSM下建联失败，则按照RR_CONNECTION_FAILURE处理, W下建联失败，处理流程不改变 */

                /* 在U2状态，保存当前的LAI信息 */
                pstAttLaiInfo   = NAS_MM_GetAttemptUpdateLaiInfo();
                pstCampLaiInfo  = NAS_MML_GetCurrCampLai();

                pstAttLaiInfo->PlmnId.ulMcc = pstCampLaiInfo->stPlmnId.ulMcc;
                pstAttLaiInfo->PlmnId.ulMnc = pstCampLaiInfo->stPlmnId.ulMnc;
                pstAttLaiInfo->ulLac        = ((pstCampLaiInfo->aucLac[0] << 8)| (pstCampLaiInfo->aucLac[1]));

                NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                            MM_MMC_LU_RESULT_FAILURE,
                                            NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

                NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                         NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

                /* 进U2的公共处理 */
                Mm_ComToU2Handle();

                Mm_TimerStart(MM_TIMER_T3211);                                  /* 启动T3211                                */
            }
        }
        else
        {
            g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S22_E32:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");

            /* 在U2状态，保存当前的LAI信息 */
            pstAttLaiInfo   = NAS_MM_GetAttemptUpdateLaiInfo();
            pstCampLaiInfo  = NAS_MML_GetCurrCampLai();

            pstAttLaiInfo->PlmnId.ulMcc = pstCampLaiInfo->stPlmnId.ulMcc;
            pstAttLaiInfo->PlmnId.ulMnc = pstCampLaiInfo->stPlmnId.ulMnc;
            pstAttLaiInfo->ulLac        = ((pstCampLaiInfo->aucLac[0] << 8)| (pstCampLaiInfo->aucLac[1]));

            NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

            NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

            /* 进U2的公共处理 */
            Mm_ComToU2Handle();

            NAS_MM_StartT3212Timer(NAS_MM_ConvertLauEstCnfRsltToT3212StartScean(pRrcEstCnf->ulResult));
        }


        if ( VOS_FALSE == NAS_MM_NotifyBufferedServiceRRConnNotExist() )
        {
             Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                      /* RR连接不存在                             */

             NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }

        Mm_ComCheckDelayMmConn(MM_FALSE);
        break;
    case RRC_EST_REGISTER_ACCESS_BARRED:
    case RRC_EST_IMMEDIATE_ASSIGN_REJECT:
    case RRC_EST_ACCESS_BARRED:
        /* 仅在2G网络下处理结果原因RRC_EST_IMMEDIATE_ASSIGN_REJECT */
        if ( (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
          && (RRC_EST_IMMEDIATE_ASSIGN_REJECT == pRrcEstCnf->ulResult) )
        {
            break;
        }

        Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

        g_MmGlobalInfo.LuInfo.ucImmAccRejLuAttmptCnt++;

        if ((RRC_EST_REGISTER_ACCESS_BARRED == pRrcEstCnf->ulResult)
         || (RRC_EST_ACCESS_BARRED          == pRrcEstCnf->ulResult))
        {
            NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED);

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED);                       /* 向MMC发送MMCMM_LU_RESULT_IND             */
            NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED);                       /* 向MMC发送MMCMM_LU_RESULT_IND             */

            Mm_ComSetMmState(MM_IDLE_LOCATION_UPDATE_NEEDED);
        }
        else
        {


            /* 立即指派拒绝不删除EPLMN */

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);                       /* 向MMC发送MMCMM_LU_RESULT_IND             */
            NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);
            Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);
        }

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S22_E32:NORMAL: STATUS is MM_IDLE_LOCATION_UPDATE_NEEDED");

        if (MM_FALSE ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
        {                                                                       /* 没有等待的CC触发的需要建立的MM连接       */
            Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                       /* RR连接建立失败                           */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }
        if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                      .RcvXXEstReq.ucFlg)
            ||(MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                      .RcvXXEstReq.ucFlg)
            ||(MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                      .RcvXXEstReq.ucFlg))
        {
            ucTiValidFlg = Mm_ComTiChk();
            if (MM_FALSE == ucTiValidFlg)
            {
                Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                   /* RR连接不存在                             */
                NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
            }
            else
            {
                Mm_ComSigRelForDelayMmConnRej();
            }
        }
        else
        {
             Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                      /* RR连接不存在                             */
             NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }

        NAS_MM_EndBufferedCSServiceExceptEmergencyCall_ImmediateAssignReject();

        Mm_ComCheckDelayMmConn(MM_FALSE);
        break;

    case RRC_EST_RJ_T3122_RUNNING :

        Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

        NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                 NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);


        Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);

        if ( VOS_FALSE == NAS_MM_NotifyBufferedServiceRRConnNotExist() )
        {
             Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                      /* RR连接不存在                             */
             NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }

        NAS_MM_EndBufferedCSServiceExceptEmergencyCall_ImmediateAssignReject();

        Mm_ComCheckDelayMmConn(MM_FALSE);

        break;


    case RRC_EST_RJ_NO_RF:
        NAS_MM_ProcLauEstCnfNoRf();
        break;

    default:
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S22_E32:WARNING:  Result Abnormal");
        break;
    }

    g_MmGlobalInfo.LuInfo.ucPsRandomAccessFailCnt = 0;

}

VOS_VOID Mm_Cell_S25_E32(VOS_VOID* pMsg)
{
    RRMM_EST_CNF_STRU*      pRrcEstCnf;

    if (MM_FALSE == Mm_RcvRrcEstCnf(pMsg))
    {
        return;
    }

    pRrcEstCnf = (RRMM_EST_CNF_STRU*)pMsg;
    Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

    NAS_MM_SetEstCnfResult(pRrcEstCnf->ulResult);

    switch(pRrcEstCnf->ulResult)
    {
    case RRC_EST_SUCCESS:
    case RRC_EST_PRESENT:
        if (RRC_EST_PRESENT == pRrcEstCnf->ulResult)
        {
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S25_E32:WARNING: RR CONNECTION PRESENT!");
            return;
        }

        Mm_TimerStart(MM_TIMER_T3220);                                          /* 启动T3220                                */
        g_MmGlobalInfo.ucCsSigConnFlg = MM_CS_SIG_CONN_PRESENT;                 /* 设置信令连接已存在                       */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S25_E32:INFO: MmCsSigConnFlg is MM_CS_SIG_CONN_PRESENT");
        Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ESTED);                            /* RR连接建立成功                           */
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_EXIST);
        Mm_ComSetMmState(IMSI_DETACH_INITIATED);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S25_E32:NORMAL: STATUS is IMSI_DETACH_INITIATED");
        break;
    case RRC_EST_ESTING:
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S25_E32:WARNING: RR CONNECTION ESTING!");
        break;
    case RRC_EST_RJ_CONGEST:
    case RRC_EST_RJ_UNSPEC:
    case RRC_EST_REGISTER_ACCESS_BARRED:
    case RRC_EST_ACCESS_BARRED:

    case RRC_EST_OTHER_ACCESS_BARRED:

    case RRC_EST_EST_CONN_FAIL:
    case RRC_EST_RJ_NOT_ALLOW:
    case RRC_EST_RJ_TIME_OUT:
    case RRC_EST_RJ_RA_RESOURCE_FAIL:
    case RRC_EST_RJ_IMMEDIATE_ASSIGN_INVALID:
    case RRC_EST_RJ_ACTIVE_PHISICAL_CHANNEL_FAIL:
    case RRC_EST_RJ_AIRMSG_DECODE_ERR:
    case RRC_EST_RJ_CELL_BAR:
    case RRC_EST_RJ_FASTRETURN_LTE:
    case RRC_EST_RJ_CURR_PROTOCOL_NOT_SUPPORT:
    case RRC_EST_RJ_SNW:

    case RRC_EST_RJ_NO_RF:

    case RRC_EST_RJ_T3122_RUNNING:

    case RRC_EST_RJ_INTER_RAT:
    case RRC_EST_IMMEDIATE_ASSIGN_REJECT:
    case RRC_EST_RANDOM_ACCESS_REJECT:
    case RRC_EST_RJ_RA_FAIL:
    case RRC_EST_RJ_RA_FAIL_NO_VALID_INFO:

    case RRC_EST_RANDOM_ACCESS_REJECT_NO_VALID_INFO:

        Mm_TimerStop(MM_TIMER_PROTECT_DETACH);
        Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        MM_SndMmcRrRelInd(RRC_REL_CAUSE_RR_NORM_EVENT);

        /* 其他接入受限，设置标志位 */
        if (RRC_EST_REGISTER_ACCESS_BARRED  == pRrcEstCnf->ulResult)
        {
            NAS_MML_SetCsRestrictRegisterFlg(VOS_TRUE);
        }

        /* 非紧急呼叫才设置限制注册和寻呼标记 */
        if  (((RRC_EST_ACCESS_BARRED  == pRrcEstCnf->ulResult)
           || (RRC_EST_RJ_CELL_BAR == pRrcEstCnf->ulResult))
          && (MMCC_EMERGENCY_CALL   !=  g_MmCcEstReq.ulCallType))
        {
            NAS_MML_SetCsRestrictPagingFlg(VOS_TRUE);
            NAS_MML_SetCsRestrictRegisterFlg(VOS_TRUE);
        }


        if (MM_DETACH_CS_POWEROFF == g_MmGlobalInfo.ucDetachType)
        {
            Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                             NAS_MML_GetSimCsSecurityCksn());             /* 设置MM信息                               */
            Mm_SndMmcPowerOffCnf();                                             /* 向MMC发送MMCMM_POWER_OFF_CNF             */

            Mm_ComSetMmState(MM_STATE_NULL);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S25_E32:NORMAL: STATUS is MM_STATE_NULL");
            g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;
        }
        else
        {
            /* 判断等待标志是否存在，如果存在则发送MMCMM_DETACH CNF */
            if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                         & MM_WAIT_CS_DETACH))
            {
                NAS_MM_SndMmcDetachCnf(MMC_MM_LIMITED_SERVICE);
                /* 清除等待标志 */
                g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
            }

            Mm_ComSetMmState(g_MmGlobalInfo.ucPreState);
            PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S25_E32:NORMAL: STATUS is",g_MmGlobalInfo.ucState);
        }
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S25_E32:WARNING: Result Abnormal");
        break;
    }

}

VOS_VOID Mm_Cell_S22_E33(VOS_VOID *pRcvMsg)
{
    VOS_UINT8                           ucValidFlg;
    RRMM_REL_IND_STRU                   *pMsg = VOS_NULL_PTR;
    VOS_UINT8                           ucRst;
    MM_LAI_STRU                        *pstAttLaiInfo   = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                   *pstCampLaiInfo  = VOS_NULL_PTR;

    pMsg = (RRMM_REL_IND_STRU *)pRcvMsg;
    ucValidFlg = Mm_RcvRrcRelInd(pRcvMsg);

    if (MM_TRUE == ucValidFlg)
    {
        NAS_MM_ClearAuthInfo();

        Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);
        Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        ucRst = NAS_MM_RetryCurrentProcedureCheck(pMsg->ulRelCause,
                    pMsg->ulRrcConnStatus);
        if (VOS_TRUE == ucRst)
        {
            /* LAU在收到系统消息后再重新发起 */
            g_MmGlobalInfo.ucRetryLauFlg = VOS_TRUE;

            Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);
            return;
        }

        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
        Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
        PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S22_E33:NORMAL: ucState = ", g_MmGlobalInfo.ucState);

        /* 当CS域正在建立CS域连接时,如果PS域主动要求释放正在建立的PS域连接,
           这种情况接入层会释放所有正在建立的连接,从而会影响到CS域的业务.
           为避免这种情况,规定这种情况下接入层给NAS发送的连接释放指示中的
           原因值定为RRC_REL_CAUSE_NAS_REL_SUCCESS,MM在收到该原因值的释放
           指示之后不认为流程失败,继续等待接入层重新上报系统消息,重新发起流程.*/
        if (RRC_REL_CAUSE_NAS_REL_SUCCESS == pMsg->ulRelCause)
        {
            g_MmGlobalInfo.ucConnRcvSysFlg = MM_TRUE;

            /* 处理缓存的LU流程 */
            if (MM_FALSE == Mm_ComChkLu())
            {
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S22_E33:WARNING: Mm_ComChkLu return MM_FALSE\n");
            }
        }
        else
        {

            /*如果PS ONLY，则直接进入limit service*/
            if (NAS_MML_MS_MODE_PS_ONLY == NAS_MML_GetMsMode())
            {
                 Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);

                 NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);

                 Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
                 PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S22_E33:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
                 Mm_ComCheckDelayMmConn(MM_FALSE);

#if (FEATURE_ON == FEATURE_ECALL)
                /* PS ONLY在ECALL ONLY模式下不设置CS不允许attach标记*/
                if (NAS_MML_ECALL_ONLY == NAS_MML_GetCallMode())
                {
                    return;
                }
#endif
                NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
                return;
            }



            if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
            {
                g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_TRUE;
            }
            else
            {
                g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_FALSE;
            }


            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt++;

            if (g_MmGlobalInfo.LuInfo.ucLuAttmptCnt < MM_CONST_NUM_4)
            {
                NAS_MM_ProcConnFailLauAttmptCntLess4_RcvRelInd(pMsg->ulRelCause);
            }
            else
            {
                g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S22_E33:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");

                /* 在U2状态，保存当前的LAI信息 */
                pstAttLaiInfo   = NAS_MM_GetAttemptUpdateLaiInfo();
                pstCampLaiInfo  = NAS_MML_GetCurrCampLai();

                pstAttLaiInfo->PlmnId.ulMcc = pstCampLaiInfo->stPlmnId.ulMcc;
                pstAttLaiInfo->PlmnId.ulMnc = pstCampLaiInfo->stPlmnId.ulMnc;
                pstAttLaiInfo->ulLac        = ((pstCampLaiInfo->aucLac[0] << 8)| (pstCampLaiInfo->aucLac[1]));

                NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                            MM_MMC_LU_RESULT_FAILURE,
                                            NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

                NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                         NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

                /* 进U2的公共处理 */
                Mm_ComToU2Handle();


                /* T3212定时器启动处理 */
                NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_LAU_RRC_EST_REL_BY_AS);

            }

            NAS_MM_SndMmcRrConn_RcvRelInd();

            Mm_ComCheckDelayMmConn(MM_FALSE);
        }

        /* 需要清除MM保存的GMM的cause值 */
        Mm_ComProcCauseClear();
    }
    else
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S22_E33:WARNING: ulRelCause Abnormal");
    }
}


VOS_VOID Mm_Cell_S23_E33(VOS_VOID* pMsg)
{
    RRMM_REL_IND_STRU*                                      pRrcRelInd;
    VOS_UINT8                                               ucTiValidFlg = MM_TRUE;
    VOS_UINT8                                               ucRrConnRelFlg = MM_TRUE;
    VOS_UINT8                                               ucRst;
    if (MM_FALSE == Mm_RcvRrcRelInd(pMsg))
    {
        return;
    }

    pRrcRelInd = (RRMM_REL_IND_STRU*)pMsg;

    NAS_MM_ClearAuthInfo();

    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
    Mm_TimerStop(MM_TIMER_T3210);

    NAS_NORMAL_LOG(WUEPS_PID_MM, "Mm_Cell_S23_E33: Rcv RR REL IND, Set CellNotSupportCsmoFlg to TRUE");
    NAS_MML_SetCellNotSupportCsmoFlg(VOS_TRUE);

    if (NAS_MML_MS_MODE_PS_ONLY == NAS_MML_GetMsMode())
    {
        /*迁移状态到limit service*/
        /*设置标志Attach not allow*/
        /*指示上层业务失败*/
        Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S23_E33:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
        Mm_ComCheckDelayMmConn(MM_FALSE);

        return;
    }

    ucRst = NAS_MM_RetryCurrentProcedureCheck(pRrcRelInd->ulRelCause,
                pRrcRelInd->ulRrcConnStatus);
    if (VOS_TRUE == ucRst)
    {
        /* LAU在收到系统消息后再重新发起 */
        g_MmGlobalInfo.ucRetryLauFlg = VOS_TRUE;
        Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                           /* RR连接不存在                             */
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);
        return;
    }


    NAS_MM_LocationUpdateAttemptCounter(NAS_MML_REG_FAIL_CAUSE_RR_CONN_FAIL);

    NAS_MM_UpdateLauRetryFlg_RcvRelInd(pRrcRelInd);



    ucRrConnRelFlg = Mm_ComRrConnRelChk();
    if (MM_TRUE == ucRrConnRelFlg)
    {
        Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                           /* RR连接不存在                             */
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
    }
    else
    {
        ucTiValidFlg = Mm_ComTiChk();
        if (MM_FALSE == ucTiValidFlg)
        {
            Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                       /* RR连接不存在                             */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }
        else
        {
            Mm_ComSigRelForDelayMmConnRej();
        }
        Mm_ComCheckDelayMmConn(MM_FALSE);
    }

    /* 需要清除MM保存的GMM的cause值 */
    Mm_ComProcCauseClear();

    /* 处理当前缓存的CS域去注册 */
    if ((VOS_FALSE  == NAS_MM_IsNeedGmmProcUserDetach())
     && (MM_WAIT_CS_DETACH == (g_MmGlobalInfo.stDetachInfo.enDetachType & MM_WAIT_CS_DETACH)))
    {
        /* 建链不成功，直接本地DETACH */
        NAS_MM_LocalDetach();
    }
}

VOS_VOID Mm_Cell_S24_E33(VOS_VOID* pMsg)
{
    VOS_UINT8                   ucOldCsUpdateStatus;
    VOS_UINT8                   ucTempCsUpdateStatus;
    VOS_UINT8                   ucTiValidFlg = MM_TRUE;
    VOS_UINT8                   ucRrConnRelFlg = MM_TRUE;

    if (MM_FALSE == Mm_RcvRrcRelInd(pMsg))
    {
        return;
    }

    NAS_MM_ClearAuthInfo();

    Mm_TimerStop(MM_TIMER_T3240);                                               /* 停止T3240                                */


    ucOldCsUpdateStatus = NAS_MML_GetCsUpdateStatus();

    Mm_ComLuCauseHandle(g_MmGlobalInfo.usCauseVal);                             /* 调用原因值的公共处理                     */
    ucTempCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
    NAS_MML_SetCsUpdateStatus(ucOldCsUpdateStatus);

    NAS_MML_SetCsUpdateStatus(ucTempCsUpdateStatus);

    ucRrConnRelFlg = Mm_ComRrConnRelChk();

    if (MM_TRUE == ucRrConnRelFlg)
    {
        Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                           /* RR连接不存在                             */
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
    }
    else
    {
        ucTiValidFlg = Mm_ComTiChk();
        if (MM_FALSE == ucTiValidFlg)
        {
            Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                       /* RR连接不存在                             */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }
        else
        {
            Mm_ComSigRelForDelayMmConnRej();
        }
        Mm_ComCheckDelayMmConn(MM_FALSE);
    }

    Mm_ComCheckDelayDetach();
}

VOS_VOID  Mm_Cell_S25_E33( VOS_VOID* pMsg )
{
    VOS_UINT8                           ucValidFlg;

    ucValidFlg = Mm_RcvRrcRelInd(pMsg);

    if (MM_TRUE == ucValidFlg)
    {
        NAS_MM_ClearAuthInfo();

        Mm_TimerStop(MM_TIMER_PROTECT_DETACH);
        Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        MM_SndMmcRrRelInd(RRC_REL_CAUSE_RR_NORM_EVENT);

        if (MM_DETACH_CS_POWEROFF == g_MmGlobalInfo.ucDetachType)
        {
            Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                             NAS_MML_GetSimCsSecurityCksn());
            Mm_SndMmcPowerOffCnf();
            Mm_ComSetMmState(MM_STATE_NULL);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S25_E33:NORMAL: STATUS is MM_STATE_NULL");
            g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;
        }
        else
        {
            /* 判断等待标志是否存在，如果存在则发送MMCMM_DETACH CNF */
            if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                         & MM_WAIT_CS_DETACH))
            {
                NAS_MM_SndMmcDetachCnf(MMC_MM_LIMITED_SERVICE);

                /* 清除等待标志 */
                g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
            }

            Mm_ComSetMmState(g_MmGlobalInfo.ucPreState);
            PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S25_E33:NORMAL: STATUS is",g_MmGlobalInfo.ucState);
        }

        /* 需要清除MM保存的GMM的cause值 */
        Mm_ComProcCauseClear();
    }
    else
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S25_E33:WARNING: ulRelCause Abnormal");
    }
    return;
}

VOS_VOID Mm_Cell_S26_E33(VOS_VOID* pMsg)
{
    VOS_UINT8  ucTiValidFlg = MM_TRUE;
    VOS_UINT8  ucRrConnRelFlg = MM_TRUE;

    if (MM_FALSE == Mm_RcvRrcRelInd(pMsg))
    {
        return;
    }
    NAS_MM_ClearAuthInfo();

    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;

    Mm_TimerStop(MM_TIMER_T3220);                                               /* 停止T3220                                */
    Mm_TimerStop(MM_TIMER_PROTECT_DETACH);

    switch(g_MmGlobalInfo.ucDetachType)
    {
    case MM_DETACH_CS_POWEROFF:
        Mm_TimerStop(MM_TIMER_STOP_ALL);
        Mm_ComSetMmState(MM_STATE_NULL);
        g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S26_E33:NORMAL: STATUS is MM_STATE_NULL");
        Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                         NAS_MML_GetSimCsSecurityCksn());
        Mm_SndMmcPowerOffCnf();
        break;
    case MM_DETACH_CS_NORMAL:

        Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                          NAS_MML_GetSimCsSecurityCksn());

        /* 判断等待标志是否存在，如果存在则发送MMCMM_DETACH CNF */
        if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                     & MM_WAIT_CS_DETACH))
        {
            NAS_MM_SndMmcDetachCnf(MM_DETACHED);
            /* 清除等待标志 */
            g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
        }

        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
        g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S26_E33:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S26_E33:WARNING: Detach type Abnormal");
        break;
    }

    g_MmGlobalInfo.ucPowerOnFlg = MM_TRUE;

    NAS_EventReport(WUEPS_PID_MM, NAS_OM_EVENT_IMSI_DETACH_IND,
                    VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    ucRrConnRelFlg = Mm_ComRrConnRelChk();
    if (MM_TRUE == ucRrConnRelFlg)
    {
        Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                           /* RR连接不存在                             */
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
    }
    else
    {
        ucTiValidFlg = Mm_ComTiChk();
        if (MM_FALSE == ucTiValidFlg)
        {
            Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                       /* RR连接不存在                             */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }
        else
        {
            Mm_ComSigRelForDelayMmConnRej();
        }
        Mm_ComCheckDelayMmConn(MM_FALSE);
    }

    /* 需要清除MM保存的GMM的cause值 */
    Mm_ComProcCauseClear();
}

VOS_VOID Mm_Cell_S23_E51(VOS_VOID* pMsg)
{
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8   enCsUpdateStatus;

    Mm_TimerStop(MM_TIMER_T3210);                                               /* 停止T3210                                */

    Mm_TimerStop(MM_TIMER_T3212);                                               /* 停止T3212                                */
    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
    g_MmGlobalInfo.LuInfo.ucLuAttmptCnt++;

    Mm_ComSaveProcAndCauseVal(MM_LU_PROC, NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT);          /* 记录流程和原因值                         */
    Mm_SndRrRelReq(RRC_CELL_UNBARRED);
    Mm_TimerStart(MM_TIMER_T3240);                                              /* 启动T3240                                */
    Mm_ComSetMmState(LOCATION_UPDATE_REJECTED);
    if (g_MmGlobalInfo.LuInfo.ucLuAttmptCnt < MM_CONST_NUM_4)
    {                                                                           /* 判断LU Counter是否小于4                  */
        enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
        if ((VOS_FALSE == NAS_MML_IsCsLaiChanged()) &&
            (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus))
        {                                                                       /* 判断LAI是否未改变,且更新状态为U1         */
            g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;

            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S23_E46:INFO: MmServiceState is MM_NORMAL_SERVICE");

        }
        else
        {
            g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;

            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S23_E46:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");

        }
    }
    else
    {
        g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;              /* 设置服务状态                             */

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S23_E46:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");
    }

    NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT);

    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                MM_MMC_LU_RESULT_FAILURE,
                                NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT);
    NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                             NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT);
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S23_E51:NORMAL: STATUS is LOCATION_UPDATE_REJECTED");
}

VOS_VOID Mm_Cell_S3_E52(VOS_VOID* pMsg)
{
    /* AT&T 测试用例GSM-BTR-1-0644和GSM-BTR-1-0650和GSM-BTR-1-0652
       和GSM-BTR-1-0656要求网络模式II，CS lau被拒#17，PS attach成功后，
       MM T3211定时器超时CS做lau被拒#17，要求PS需要做rau,该场景MM需要通知GMM做RAU*/
    if ((VOS_TRUE == NAS_MML_IsPlmnSupportDam(NAS_MML_GetCurrCampPlmnId()))
      && (MM_NET_MODE_II == g_MmGlobalInfo.ucNewNtMod))
    {
        NAS_MM_SndGmmT3211ExpiredNotify(g_MmMsgLuRjct.MmIeRejCause.ucRejCause);
    }

    if (g_MmGlobalInfo.LuInfo.ucLuType >= MM_IE_LUT_TYPE_BUTT)
    {
        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;
    }

    Mm_ComLuOnly();                                                             /* 发送LU REQ                               */
}


VOS_VOID Mm_Cell_S9_E52(VOS_VOID* pMsg)
{
    Mm_TimerStart(MM_TIMER_T3211);
}


VOS_VOID Mm_Cell_S1_E53(VOS_VOID* pMsg)
{
    Mm_TimerStop(MM_TIMER_T3212);                                               /* 停止T3212                                */

    if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_TRUE;

        if (NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED == NAS_MML_GetCsUpdateStatus())
        {
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;
        }
        return;
    }

    if (VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNtMod))
    {
        if (MM_TRUE == g_MmGlobalInfo.ucLikeNetmode2)
        {
            g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_TRUE;
        }

        if (MMCMM_NO_FORBIDDEN != g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)
        {
            g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_TRUE;
        }
    }
    else
    {
        g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_TRUE;                      /* 设置T3212溢出的标识                      */
    }


    /* T3212定时器超时再ATTEMPT 2 UPDATE状态，需要清空COUNTER值 */
    if (NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED == NAS_MML_GetCsUpdateStatus())
    {
        g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;
    }
}

VOS_VOID Mm_Cell_S3_E53(VOS_VOID* pMsg)
{
    VOS_UINT8                    ucPsRestrictionFlg;

    ucPsRestrictionFlg      = NAS_MML_GetPsRestrictRegisterFlg();
    Mm_TimerStop(MM_TIMER_T3212);                                               /* 停止T3212                                */

    if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_TRUE;
        return;
    }

    /* 网络模式I下，如果GMM已经注册或者正在进行注册，T3212不处理。
    GCF44.2.1.2.8 */
    /* 此处加测试卡判断是为了在GCF测试时，不进行LAU；但现网中仍需要发起LAU */
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        if ( (VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
          && (MM_NET_MODE_I    == g_MmGlobalInfo.ucNtMod))
        {
            if (VOS_TRUE == NAS_GMM_IsRegisteredOrRegistering())
            {
                return;
            }
        }
    }

    if ((VOS_TRUE  == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNtMod))
     && (VOS_FALSE == ucPsRestrictionFlg))
    {
        if (MM_TRUE == g_MmGlobalInfo.ucLikeNetmode2)
        {
             g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_PERIODIC_UPDATING;
             g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_TRUE;
             Mm_ComLuOnly();
        }
    }
    else
    {
        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_PERIODIC_UPDATING;           /* 设置LU类型                               */
        g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_TRUE;
        Mm_ComLuOnly();                                                         /* 发送LU REQ                               */
    }
}


VOS_VOID Mm_Cell_S5_E53(VOS_VOID* pMsg)
{
    VOS_UINT8                    ucPsRestrictionFlg;

    ucPsRestrictionFlg      = NAS_MML_GetPsRestrictRegisterFlg();

    Mm_TimerStop(MM_TIMER_T3212);                                               /* 停止T3212                                */

    if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_TRUE;
        g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;
        return;
    }

    g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;

    if ((VOS_TRUE  == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNtMod))
     && (VOS_FALSE == ucPsRestrictionFlg))
    {
        if (MM_TRUE == g_MmGlobalInfo.ucLikeNetmode2)
        {
             g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;              /* 设置LU类型                               */
             Mm_ComLuOnly();
        }
    }
    else
    {
        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;                   /* 设置LU类型                               */
        Mm_ComLuOnly();                                                         /* 发送LU REQ                               */
    }

    g_MmGlobalInfo.LuInfo.ucImmAccRejLuAttmptCnt = 0;

}


VOS_VOID Mm_Cell_S6_E54(VOS_VOID* pMsg)
{
    RRC_NAS_EST_RESULT_ENUM_UINT32      enEstCnfResult;

    enEstCnfResult = NAS_MM_GetEstCnfResult();

    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {
        /* 24008 4.4.4.9中描述:
        c)  Random access failure (A/Gb mode only)
        Timer T3213 is started. When it expires the procedure is attempted again if still necessary.
        NOTE 1: As specified in 3GPP TS 45.008 [34], a cell reselection then takes place, with return to
        the cell inhibited for 5 seconds if there is at least one other suitable cell. Typically the
        selection process will take the mobile station back to the cell where the random access failed
        after 5 seconds.
        If at the expiry of timer T3213 a new cell has not been selected due to the lack of
        valid information (see 3GPP TS 45.008 [34]), the mobile station may as an option delay
        the repeated attempt for up to 8 seconds to allow cell re-selection to take place.
        In this case the procedure is attempted as soon as a new cell has been selected or
        the mobile station has concluded that no other cell can be selected.
        */
        if((VOS_TRUE == GMM_IsGasCellReselect())
        || (RRC_EST_RANDOM_ACCESS_REJECT_NO_VALID_INFO == enEstCnfResult)
        || (RRC_EST_RJ_RA_FAIL_NO_VALID_INFO           == enEstCnfResult))
        {
            if(g_MmGlobalInfo.LuInfo.ucT3213AttmptCnt < MM_CONST_NUM_2)
            {
                Mm_TimerStart(MM_TIMER_T3213);
            }
            else
            {
                Mm_TimerStart(MM_TIMER_T3211);
            }
        }
        else
        {
            Mm_ComLuOnly();
            g_MmGlobalInfo.LuInfo.ucT3213AttmptCnt++;
        }

        if ( (RRC_EST_RANDOM_ACCESS_REJECT_NO_VALID_INFO == enEstCnfResult)
          || (RRC_EST_RJ_RA_FAIL_NO_VALID_INFO           == enEstCnfResult) )
        {
            NAS_MM_SetEstCnfResult(RRC_NAS_EST_RESULT_BUTT);
        }
    }
}

VOS_VOID Mm_Cell_S26_E58(VOS_VOID* pMsg)
{
    VOS_UINT8  ucTiValidFlg = MM_TRUE;
    VOS_UINT8  ucRrConnRelFlg = MM_TRUE;

    Mm_TimerStop(MM_TIMER_T3220);                                               /* 停止T3220                                */
    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;

    switch(g_MmGlobalInfo.ucDetachType)
    {
    case MM_DETACH_CS_POWEROFF:
        Mm_TimerStop(MM_TIMER_STOP_ALL);
        Mm_ComSetMmState(MM_STATE_NULL);
        g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S26_E58:NORMAL: STATUS is MM_STATE_NULL");
        Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                         NAS_MML_GetSimCsSecurityCksn());
        Mm_SndMmcPowerOffCnf();
        break;
    case MM_DETACH_CS_NORMAL:
        Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                         NAS_MML_GetSimCsSecurityCksn());

        /* 判断等待标志是否存在，如果存在则发送MMCMM_DETACH CNF */
        if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                     & MM_WAIT_CS_DETACH))
        {
            NAS_MM_SndMmcDetachCnf(MM_DETACHED);
            /* 清除等待标志 */
            g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
        }

        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S26_E58:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S26_E58:WARNING: Detach type Abnormal");
        break;
    }

    g_MmGlobalInfo.ucPowerOnFlg = MM_TRUE;

    NAS_EventReport(WUEPS_PID_MM, NAS_OM_EVENT_IMSI_DETACH_IND,
                    VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    ucRrConnRelFlg = Mm_ComRrConnRelChk();
    if (MM_TRUE == ucRrConnRelFlg)
    {
        Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                           /* RR连接不存在                             */
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
    }
    else
    {
        ucTiValidFlg = Mm_ComTiChk();
        if (MM_FALSE == ucTiValidFlg)
        {
            Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                       /* RR连接不存在                             */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }
        else
        {
            Mm_ComSigRelForDelayMmConnRej();
        }
        Mm_ComCheckDelayMmConn(MM_FALSE);
    }

    Mm_SndRrRelReq(RRC_CELL_UNBARRED);
}

/*******************************************************************************
  Module:   Mm_Cell_S24_E60
  Function: 在LOCATION UPDATE REJECTED状态下,接收到T3240溢出的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2004.03.15  新版做成
*******************************************************************************/
VOS_VOID Mm_Cell_S24_E60(VOS_VOID* pMsg)
{
    Mm_T3240Expire();
}


VOS_VOID Mm_Cell_S23_E45(VOS_VOID* pMsg)
{
    MM_LAI_STRU                                             stCurLai;
    NAS_MML_LAI_STRU                                       *pstCurrCampLai = VOS_NULL_PTR;
    VOS_UINT32                                              i;
    VOS_UINT32                                              j;
    VOS_UINT8                                               ucLacChangeFlg;
    NAS_MML_LAI_STRU                                       *pstCsSuccLai = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                              *pstEplmnAddr = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stTempEplmnAddr;
    NAS_MML_IGNORE_AUTH_REJ_INFO_STRU      *pstAuthRejInfo;
    NAS_MML_EMERGENCY_NUM_LIST_STRU                        *pstEmergencyNumList;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                                              ulDeactiveIsrFlg;
    NAS_MML_RPLMN_CFG_INFO_STRU                            *pstRplmnCfgInfo;

    pstRplmnCfgInfo = NAS_MML_GetRplmnCfg();
#endif

    pstCsSuccLai    = NAS_MML_GetCsLastSuccLai();

    pstCurrCampLai = NAS_MML_GetCurrCampLai();

    PS_MEM_SET(&stCurLai, 0x0 ,sizeof(stCurLai));
    NAS_MM_ConvertMmlLaiFormatToMMFormat(pstCurrCampLai, &stCurLai);

    pstEmergencyNumList     = NAS_MML_GetEmergencyNumList();

    ucLacChangeFlg                              = VOS_FALSE;
    g_MmSubLyrShare.GmmShare.ucGsAssociationFlg = VOS_FALSE;


    PS_MEM_SET(&stTempEplmnAddr, 0x00, sizeof(stTempEplmnAddr));

    if (MM_TRUE == g_MmMsgLuAccpt.ucEmcFlg)
    {
        pstEmergencyNumList->ulMcc = NAS_MML_GetCurrCampPlmnId()->ulMcc;

        Mm_SndCcEmergencyNumberList(pstEmergencyNumList);
    }

    else if (0 != pstEmergencyNumList->ucEmergencyNumber)
    {
        /* 消息中包不含紧急呼列表但之前存储了紧急呼列表,如果不是同一个国家的mcc则，删除之前存储的紧急呼叫列表
        24008_CR2107R1_(Rel-11)_C1-121605 24008 4.4.4.6、4.7.3.1.3、4.7.5.1.3描述如下:
        The emergency number(s) received in the Emergency Number List IE are valid only
        in networks with in.the same MCCcountry as in  the cell on which this IE
        is received.*/
        if (VOS_FALSE == NAS_MML_ComparePlmnMcc(pstEmergencyNumList->ulMcc, pstCurrCampLai->stPlmnId.ulMcc))
        {
            pstEmergencyNumList->ulMcc = 0xFFFFFFFF;

            for (i = 0; i < pstEmergencyNumList->ucEmergencyNumber; i++)
            {
                pstEmergencyNumList->aucEmergencyList[i].ucCategory = 0xFF;

                for (j = 0; j < NAS_MML_EMERGENCY_NUM_MAX_LEN; j++)
                {
                    pstEmergencyNumList->aucEmergencyList[i].aucEmcNum[j] = 0xFF;
                }
            }

            pstEmergencyNumList->ucEmergencyNumber = 0;
        }

        Mm_SndCcEmergencyNumberList(pstEmergencyNumList);
    }
    else
    {
    }

    if (VOS_FALSE ==  MM_ComCmpLai(g_MmMsgLuAccpt.MmIeLAI.IeLai, stCurLai))
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S23_E45:WARNING: LU ACCEPTED LAI ERROR!");
        ucLacChangeFlg = VOS_TRUE;
    }

    g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_FALSE;


    g_MmGlobalInfo.ucRejectCause = NAS_MML_REG_FAIL_CAUSE_NULL;
    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;

    Mm_TimerStop(MM_TIMER_T3210);

    /* 停止T3212定时器，并回复为配置的默认时长 */
    Mm_TimerStop(MM_TIMER_T3212);

    NAS_MM_SetNetworkT3212RandLen(MM_CONST_NUM_0);


    pstAuthRejInfo = NAS_MML_GetAuthRejInfo();
    pstAuthRejInfo->ucHplmnCsAuthRejCounter = 0;
    g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;                        /* 设置服务状态                             */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S23_E45:INFO: MmServiceState is MM_NORMAL_SERVICE");
    g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_0;

    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_TYPE_BUTT;

    /* 记录注册成功的RAC，用于网络模式改变,比较RAI是否发生改变 */
    g_MmGlobalInfo.MsCsInfo.ucOldRac
        = NAS_MML_GetCurrCampRac();

    pstCsSuccLai->stPlmnId.ulMcc = pstCurrCampLai->stPlmnId.ulMcc;
    pstCsSuccLai->stPlmnId.ulMnc = pstCurrCampLai->stPlmnId.ulMnc;
    pstCsSuccLai->aucLac[0]      = pstCurrCampLai->aucLac[0];
    pstCsSuccLai->aucLac[1]      = pstCurrCampLai->aucLac[1];

    pstCsSuccLai->ucRac = g_MmGlobalInfo.MsCsInfo.ucOldRac;

    /* 网络下发的non broadcase lai与系统消息的不同且合法，需要更新last success lai，连接释放后需要触发lau */
    if ((VOS_TRUE == ucLacChangeFlg)
     && (MM_INVALID_LAI != g_MmMsgLuAccpt.MmIeLAI.IeLai.ulLac))
    {
        pstCsSuccLai->stPlmnId.ulMcc                  = g_MmMsgLuAccpt.MmIeLAI.IeLai.PlmnId.ulMcc;
        pstCsSuccLai->stPlmnId.ulMnc                  = g_MmMsgLuAccpt.MmIeLAI.IeLai.PlmnId.ulMnc;
        pstCsSuccLai->aucLac[0]                       = (g_MmMsgLuAccpt.MmIeLAI.IeLai.ulLac >> 8) & (0x00FF);
        pstCsSuccLai->aucLac[1]                       = (g_MmMsgLuAccpt.MmIeLAI.IeLai.ulLac) & (0x00FF);

        PS_MEM_CPY(pstCurrCampLai, pstCsSuccLai, sizeof(NAS_MML_LAI_STRU));
        g_MmGlobalInfo.ucLauAcceptContainDiffNbLaiFlg = VOS_TRUE;
    }

    if (MM_TRUE == g_MmMsgLuAccpt.ucMobileIDFlg)
    {
        if (MM_MS_ID_IMSI_PRESENT ==
            (g_MmMsgLuAccpt.MmIeMobileId.MobileID.ucMsIdFlg
                                         & MM_MS_ID_IMSI_PRESENT))
        {                                                                       /* 如果存在IMSI                             */
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                                    ~MM_MS_ID_TMSI_PRESENT;     /* 设置TMSI无效                             */
            NAS_MML_InitUeIdTmsiInvalid();
        }
        else if (MM_MS_ID_TMSI_PRESENT ==
            (g_MmMsgLuAccpt.MmIeMobileId.MobileID.ucMsIdFlg
                                            & MM_MS_ID_TMSI_PRESENT))
        {
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg |= MM_MS_ID_TMSI_PRESENT;/* 设置TMSI有效                             */

            PS_MEM_CPY(NAS_MML_GetUeIdTmsi(),
                       g_MmMsgLuAccpt.MmIeMobileId.MobileID.aucTmsi,
                       NAS_MML_MAX_TMSI_LEN);

            g_MmGlobalInfo.MsCsInfo.stPlmnId.ulMcc = NAS_MML_GetCsLastSuccMcc();
            g_MmGlobalInfo.MsCsInfo.stPlmnId.ulMnc = NAS_MML_GetCsLastSuccMnc();
            Mm_ComMsgTmsiRelocCpltSnd();                                        /* 向网侧发送TMSI REALLOCATION COMPLETE     */
        }
        else
        {
        }
    }

    NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_UPDATED);                  /* 设置更新状态                             */
    Mm_ComNasInfoSav(
                     MM_STATUS_ATTACHED,
                     NAS_MML_GetSimCsSecurityCksn()
                     );                                                         /* 通知RRC,MM的Attach状态                   */
    if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
    {
        Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
    }
    else
    {
        Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
    }




    /* 回复MMCMM_ATTACH_CNF的操作,清除等待ATTACH结果标志位 */
    if (MM_WAIT_CS_ATTACH == (g_MmGlobalInfo.stAttachInfo.enAttachType
                            & MM_WAIT_CS_ATTACH))
    {
        NAS_MM_SndMmcAttachCnf();
    }
    g_MmGlobalInfo.stAttachInfo.enAttachType = MM_WAIT_NULL_ATTACH;



    /* LAU成功，更新EPLMN/RPLMN */

    /* 从网侧下发的EPLMN列表中删除无效 、禁止和不允许漫游的网络 */
    if ( MM_TRUE == g_MmMsgLuAccpt.ucPlmnListFlg )
    {
        g_MmMsgLuAccpt.MmIePlmnList.ucPlmnNum = (VOS_UINT8)NAS_MML_DelInvalidPlmnFromList((VOS_UINT32)g_MmMsgLuAccpt.MmIePlmnList.ucPlmnNum,
                                           (NAS_MML_PLMN_ID_STRU *)g_MmMsgLuAccpt.MmIePlmnList.aPlmnId);

        g_MmMsgLuAccpt.MmIePlmnList.ucPlmnNum = (VOS_UINT8)NAS_MML_DelForbPlmnInList((VOS_UINT32)g_MmMsgLuAccpt.MmIePlmnList.ucPlmnNum,
                                           (NAS_MML_PLMN_ID_STRU *)g_MmMsgLuAccpt.MmIePlmnList.aPlmnId);

        /* 生成EPlmn信息列表  */
        NAS_MM_GenerateEPlmnInfo(g_MmMsgLuAccpt.MmIePlmnList.ucPlmnNum,
                                 g_MmMsgLuAccpt.MmIePlmnList.aPlmnId,
                                 &stTempEplmnAddr);
    }
    else
    {
        stTempEplmnAddr.ucEquPlmnNum = 0x1;
        stTempEplmnAddr.astEquPlmnAddr[0].ulMcc = NAS_MML_GetCurrCampPlmnId()->ulMcc;
        stTempEplmnAddr.astEquPlmnAddr[0].ulMnc = NAS_MML_GetCurrCampPlmnId()->ulMnc;
    }

    pstEplmnAddr = NAS_MML_GetEquPlmnList();


    /* 将EPLMN保存到MML全局变量 */
    PS_MEM_CPY(pstEplmnAddr, &stTempEplmnAddr, sizeof(NAS_MML_EQUPLMN_INFO_STRU));

    NAS_MML_SetEplmnValidFlg(VOS_TRUE);

    /* 将EPLMN更新到NV中 */
    NAS_MM_WriteEplmnNvim(pstEplmnAddr);


    if (VOS_TRUE == NAS_MM_IsGURplmnChanged(NAS_MML_GetCurrCampPlmnId(), NAS_MML_GetCurrNetRatType()))
    {
        /* 保存RPlmn信息到全局变量中 */
        NAS_MML_UpdateGURplmn(NAS_MML_GetCurrCampPlmnId(), NAS_MML_GetCurrNetRatType());

        NAS_MM_WriteRplmnWithRatNvim(NAS_MML_GetRplmnCfg());
    }

    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                MM_MMC_LU_RESULT_SUCCESS,
                                NAS_MML_REG_FAIL_CAUSE_NULL);
    NAS_MM_SndGmmLuResultInd(MMGMM_LU_SUCCESS,
                             NAS_MML_REG_FAIL_CAUSE_NULL);


    NAS_MM_RecordErrorLogInfo(NAS_ERR_LOG_BASE_STATE_LAU_ACCEPT,
                              NAS_MML_REG_FAIL_CAUSE_NULL);

    Mm_ComSaveProcAndCauseVal(MM_LU_PROC, NAS_MML_REG_FAIL_CAUSE_NULL);                   /* 记录流程和原因值                         */

    if (MM_TRUE == g_MmGlobalInfo.ucPowerOnFlg)
    {
        g_MmGlobalInfo.ucPowerOnFlg = MM_FALSE;
    }


    g_MmSubLyrShare.MmShare.ucSpecProFlg = MM_UPDATED_SPECIFIC_PROCEDURE;

    if (MM_TRUE == g_MmMsgLuAccpt.ucFollowOFlg)
    {                                                                           /* 如存在Follow On流程                      */
        Mm_ComFollowOnProc();                                                   /* 调用Follow On的公共处理                  */
    }
    else
    {
        Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S23_E45:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
        Mm_TimerStart(MM_TIMER_T3240);                                          /* 停止T3240                                */
    }

#if (FEATURE_ON == FEATURE_LTE)
    ulDeactiveIsrFlg = NAS_MM_IsNeedDeactiveIsrAfterLau();
    if (VOS_TRUE == ulDeactiveIsrFlg)
    {
        /* 去激活ISR,更新TIN值为P-TMSI */
        NAS_MM_WriteTinInfoNvim(NAS_MML_TIN_TYPE_PTMSI, pstRplmnCfgInfo->aucLastImsi);
        NAS_MML_SetT3423Status(NAS_MML_TIMER_STOP);
        NAS_MML_SetT3412Status(NAS_MML_TIMER_STOP);
    }
#endif


}



NAS_STK_UPDATE_TYPE_ENUM_UINT8 NAS_MM_ConvertMmLuTypeToStkLuType (LAU_TYPE_ENUM_UINT8 enMmLuType)
{
    switch (enMmLuType)
    {
        case MM_IE_LUT_NORMAL_LU:
             return NAS_STK_LUT_NORMAL_LU;

        case MM_IE_LUT_PERIODIC_UPDATING:
             return NAS_STK_LUT_PERIODIC_UPDATING;

        case MM_IE_LUT_IMSI_ATTACH:
             return NAS_STK_LUT_IMSI_ATTACH;

        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_MM_ConvertMmLuTypeToStkLuType:WARNING: The input in invalid");
            return NAS_STK_UPDATE_TYPE_ENUM_BUTT;
    }
}


TAF_MMA_RAT_TYPE_ENUM_UINT8 NAS_MM_ConvertMmRatTypeToStkRatType (NAS_MML_NET_RAT_TYPE_ENUM_UINT8 enMmRatType)
{
    switch (enMmRatType)
    {
        case NAS_MML_NET_RAT_TYPE_GSM:
             return TAF_MMA_RAT_GSM;

        case NAS_MML_NET_RAT_TYPE_WCDMA:
             return TAF_MMA_RAT_WCDMA;

        case NAS_MML_NET_RAT_TYPE_LTE:
             return TAF_MMA_RAT_LTE;

        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_MM_ConvertMmRatTypeToStkRatType:WARNING: The input in invalid");
            return TAF_MMA_RAT_BUTT;
    }
}


VOS_VOID NAS_MM_SndStkLauRej(VOS_UINT8 ucCause)
{
    NAS_STK_NETWORK_REJECTION_EVENT_STRU                   *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                                              ulLength;
    NAS_MML_LAI_STRU                                       *pstLai = VOS_NULL_PTR;

    /* 申请内存 */
    ulLength = sizeof(NAS_STK_NETWORK_REJECTION_EVENT_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg   = (NAS_STK_NETWORK_REJECTION_EVENT_STRU *)PS_ALLOC_MSG(WUEPS_PID_MM, ulLength);
    if (VOS_NULL_PTR == pstMsg)
    {
        MM_ERR_LOG("NAS_MM_ReportStkLauRej: Alloc Msg");
        return;
    }

    PS_MEM_SET(&(pstMsg->stNetworkRejectionEvent), 0, sizeof(NAS_STK_NETWORK_REJECTION_EVENT_INFO_STRU));

    /* 填写新消息内容 */
    pstMsg->ulReceiverPid   = NAS_GetOamReceivePid(MAPS_STK_PID);

    pstLai      =  NAS_MML_GetCurrCampLai();
    pstMsg->stNetworkRejectionEvent.uRejectInfo.stLacInfo.stCurPlmnID.Mcc = pstLai->stPlmnId.ulMcc;
    pstMsg->stNetworkRejectionEvent.uRejectInfo.stLacInfo.stCurPlmnID.Mnc = pstLai->stPlmnId.ulMnc;
    pstMsg->stNetworkRejectionEvent.uRejectInfo.stLacInfo.usLac           = (pstLai->aucLac[0] << 8) | (pstLai->aucLac[1]);

    pstMsg->stNetworkRejectionEvent.enRejType                             = NAS_STK_LAU_REJECT;

    pstMsg->stNetworkRejectionEvent.enRat                                 = NAS_MM_ConvertMmRatTypeToStkRatType(pstLai->enCampPlmnNetRat);

    pstMsg->stNetworkRejectionEvent.ucCauseCode                           = ucCause;

    pstMsg->stNetworkRejectionEvent.enUpdateAttachType                    = NAS_MM_ConvertMmLuTypeToStkLuType(NAS_MM_GetLuType());

    pstMsg->ulMsgName                                                     = ID_NAS_STK_NETWORK_REJECTION_EVENT;

    /* 发送消息 */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_MM, pstMsg))
    {
        MM_ERR_LOG("NAS_MM_SndStkLauRej: PS_SEND_MSG ERROR");
    }

    return;
}


VOS_VOID Mm_Cell_S23_E46(VOS_VOID* pMsg)
{
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8               enCsUpdateStatus;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                                              ulT3423StatusChgNeedRegFlg;
    VOS_UINT32                                              ulT3412StatusChgNeedRegFlg;
#endif

    g_MmGlobalInfo.ucRejectCause = g_MmMsgLuRjct.MmIeRejCause.ucRejCause;
    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;

    Mm_TimerStop(MM_TIMER_PROTECT_AGENT);
    Mm_TimerStop(MM_TIMER_T3210);                                               /* 停止T3210                                */
    Mm_TimerStop(MM_TIMER_T3212);                                               /* 停止T3212                                */
    Mm_ComSaveProcAndCauseVal(MM_LU_PROC,
                              g_MmMsgLuRjct.MmIeRejCause.ucRejCause);           /* 记录流程和原因值                         */

    NAS_MM_SndStkLauRej(g_MmMsgLuRjct.MmIeRejCause.ucRejCause);

    NAS_MM_RecordErrorLogInfo(NAS_ERR_LOG_BASE_STATE_LAU_REJECT,
                              g_MmMsgLuRjct.MmIeRejCause.ucRejCause);

    switch(g_MmMsgLuRjct.MmIeRejCause.ucRejCause)
    {
    case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR:
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;
        /* 设置CS域卡无效。一定要在收到拒绝原因值时处理，
           因为GMM处理GMM消息时会判断此标志 */
        NAS_MML_SetSimCsRegStatus(VOS_FALSE);
        break;
    case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
        g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;
        g_MmSubLyrShare.GmmShare.ucGsAssociationFlg = VOS_FALSE;
        break;
    default:
        if ((g_MmMsgLuRjct.MmIeRejCause.ucRejCause
            <= NAS_MML_REG_FAIL_CAUSE_RETRY_UPON_ENTRY_CELL_MAX)
         && (g_MmMsgLuRjct.MmIeRejCause.ucRejCause
            >= NAS_MML_REG_FAIL_CAUSE_RETRY_UPON_ENTRY_CELL_MIN))
        {
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;
            g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_TRUE;
        }
        else
        {
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt++;
        }
#if (PS_UE_REL_VER >= PS_PTL_VER_R6)
            /*
            Upon reception of the cause codes # 95, # 96, # 97, # 99 and # 111 the MS
            should set the attempt counter to 4.
            */
        if (   (NAS_MML_REG_FAIL_CAUSE_SEMANTICALLY_INCORRECT_MSG == g_MmMsgLuRjct.MmIeRejCause.ucRejCause)
            || (NAS_MML_REG_FAIL_CAUSE_INVALID_MANDATORY_INF == g_MmMsgLuRjct.MmIeRejCause.ucRejCause)
            || (NAS_MML_REG_FAIL_CAUSE_MSG_NONEXIST_NOTIMPLEMENTE == g_MmMsgLuRjct.MmIeRejCause.ucRejCause)
            || (NAS_MML_REG_FAIL_CAUSE_IE_NONEXIST_NOTIMPLEMENTED == g_MmMsgLuRjct.MmIeRejCause.ucRejCause)
            || ( (g_MmMsgLuRjct.MmIeRejCause.ucRejCause > NAS_MML_REG_FAIL_CAUSE_MSG_NOT_COMPATIBLE )
              && (g_MmMsgLuRjct.MmIeRejCause.ucRejCause <= NAS_MML_REG_FAIL_CAUSE_PROTOCOL_ERROR) )
            )
        {
            /* now only WAS and WTTF support REL-6 */
            /* WCDMA/GSM都修改为4次:
                3GPP 24008 4.4.4.9 Abnormal cases on the mobile station side:
                g)Location updating reject, other causes than those treated in subclause 4.4.4.7,
                and cases of MM cause values #22 and #25, if considered as abnormal cases according to subclause 4.4.4.7
                Upon reception of the cause codes #22, # 95, # 96, # 97, # 99 and # 111 the MS should set the attempt counter to 4.
            */
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_4;
        }
#endif

        /* 不需要继续尝试时，把次数修改为4次 */
        if (VOS_FALSE == NAS_MM_IsLauRejNeedRetry(g_MmMsgLuRjct.MmIeRejCause.ucRejCause))
        {
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_4;
        }


        if (g_MmGlobalInfo.LuInfo.ucLuAttmptCnt < MM_CONST_NUM_4)
        {                                                                       /* 判断LU Counter是否小于4                  */
            enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
            if ( (VOS_FALSE == NAS_MML_IsCsLaiChanged())
              && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus))
            {                                                                   /* 判断LAI是否未改变,且更新状态为U1         */
                g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;

                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S23_E46:INFO: MmServiceState is MM_NORMAL_SERVICE");

            }
            else
            {
                g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;

                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S23_E46:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");

            }
        }
        else
        {
            g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;          /* 设置服务状态                             */

            /* Steering of Roaming 特性 */
            /* SOR 特性: 4次搜网失败,重新搜网后，如果仍驻留在被拒绝的网络，终端需要再尝试一次注册 */



            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S23_E46:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");
        }
        break;
    }

#if (FEATURE_ON == FEATURE_LTE)
    /* 3GPP 23401 4.3.5.6 Idle mode signalling reduction function描述去激活ISR场景：
       After a LAU procedure if the UE has CS fallback and/or SMS over SGs activated.*/
    ulT3423StatusChgNeedRegFlg = NAS_MM_IsT3423StatusChangeNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                                         NAS_MML_GetTinType(), NAS_MML_GetT3423Status());

    if (VOS_TRUE == ulT3423StatusChgNeedRegFlg)
    {
        NAS_MML_SetT3423Status(NAS_MML_TIMER_STOP);
    }

    ulT3412StatusChgNeedRegFlg = NAS_MM_IsT3412ExpiredNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                                         NAS_MML_GetTinType(), NAS_MML_GetT3412Status());

    if (VOS_TRUE == ulT3412StatusChgNeedRegFlg)
    {
        NAS_MML_SetT3412Status(NAS_MML_TIMER_STOP);
    }
#endif
    NAS_MM_UpdateEquPlmnInfo(g_MmGlobalInfo.usCauseVal);

    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                MM_MMC_LU_RESULT_FAILURE,
                                g_MmGlobalInfo.usCauseVal);
    NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                             g_MmGlobalInfo.usCauseVal);
    Mm_ComSetMmState(LOCATION_UPDATE_REJECTED);
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S23_E46:NORMAL: STATUS is LOCATION_UPDATE_REJECTED");
    Mm_TimerStart(MM_TIMER_T3240);                                              /* 停止T3240                                */
}


VOS_VOID Mm_Cell_S0_E2(VOS_VOID* pMsg)
{
    VOS_UINT8   ucRet;

    ucRet = Mm_RcvMmcAttachReq(pMsg);
    if ( MM_FALSE == ucRet )
    {
    }
    else
    {
        g_MmGlobalInfo.ucLikeNetmode2 = MM_FALSE;
    }

    /* 回复MMCMM_ATTACH_CNF的操作,清除等待ATTACH结果标志位 */
    if (MM_WAIT_CS_ATTACH == (g_MmGlobalInfo.stAttachInfo.enAttachType
                            & MM_WAIT_CS_ATTACH))
    {
        NAS_MM_SndMmcAttachCnf();
    }
    g_MmGlobalInfo.stAttachInfo.enAttachType = MM_WAIT_NULL_ATTACH;
}

VOS_VOID Mm_Cell_S1_E2(VOS_VOID* pMsg)
{
    VOS_UINT8                           ucRet;

    ucRet = Mm_RcvMmcAttachReq( pMsg );
    if (MM_FALSE == ucRet)
    {
    }
    else
    {

        /*在以下状态需要直接回复结果*/
        if (( MM_IDLE_NO_CELL_AVAILABLE == g_MmGlobalInfo.ucState )
            || ( MM_IDLE_LOCATION_UPDATE_NEEDED == g_MmGlobalInfo.ucState )
            || ( MM_IDLE_NO_IMSI == g_MmGlobalInfo.ucState )
#if (!defined(__PS_WIN32_RECUR__)) && ( VOS_WIN32 != VOS_OS_VER )
            || ( MM_IDLE_PLMN_SEARCH == g_MmGlobalInfo.ucState )
#endif
            )
        {
            /* 回复MMCMM_ATTACH_CNF的操作,清除等待ATTACH结果标志位 */
            if (MM_WAIT_CS_ATTACH == (g_MmGlobalInfo.stAttachInfo.enAttachType
                                    & MM_WAIT_CS_ATTACH))
            {
                NAS_MM_SndMmcAttachCnf();
            }
            g_MmGlobalInfo.stAttachInfo.enAttachType = MM_WAIT_NULL_ATTACH;

            /* 删除原来此处服务状态上报*/
        }
        else
        {
        }
    }
}

VOS_VOID Mm_Cell_S4_E2(VOS_VOID* pMsg)
{
    VOS_UINT8   ucRet;

    MMCMM_ATTACH_REQ_STRU                      *pRcvMsg             = VOS_NULL_PTR;
    VOS_UINT8                                   ucPsAttachAllow;
    VOS_UINT8                                   ucSimPsRegStatus;
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8   enCsUpdateStatus;
    VOS_UINT8                                   ucPsRestrictRegisterFlg;

    ucPsAttachAllow  = NAS_MML_GetPsAttachAllowFlg();
    ucSimPsRegStatus = NAS_MML_GetSimPsRegStatus();

    ucPsRestrictRegisterFlg = NAS_MML_GetPsRestrictRegisterFlg();

    pRcvMsg = (MMCMM_ATTACH_REQ_STRU*)pMsg;

    ucRet = Mm_RcvMmcAttachReq(pMsg);
    if (MM_FALSE == ucRet)
    {
    }
    else
    {
        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod)
         && (MM_FALSE == g_MmGlobalInfo.ucLikeB)
         && (VOS_TRUE == ucSimPsRegStatus)
         && (VOS_FALSE == ucPsRestrictRegisterFlg)
         && ((VOS_TRUE == ucPsAttachAllow)
          || (MMC_MM_ATTACH_TYPE_GPRS_IMSI == pRcvMsg->enAttachType)))
        {                                                                       /* 网络模式I                                */
        }
        else
        {                                                                       /* 网络模式II                               */
            if (VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
            {
                if (VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg())
                {
                    /*当前小区被bar时，直接回复MMCMM_ATTACH_CNF,清除等待ATTACH结果标志位 */
                    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                MM_MMC_LU_RESULT_FAILURE,
                                                NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED);           /* 向MMC发送MMCMM_LU_RESULT_IND             */
                    NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                             NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED);           /* 向MMC发送MMCMM_LU_RESULT_IND             */

                    Mm_ComSetMmState(MM_IDLE_LOCATION_UPDATE_NEEDED);


                    return;
                }

                enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
                if ( (VOS_FALSE == NAS_MML_IsCsLaiChanged())
                  && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus))
                {                                                               /* 如果LAI不变,更新状态为U1                 */
                    if (MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg)
                    {
                        Mm_ComNasInfoSav(
                                         MM_STATUS_ATTACHED,
                                         NAS_MML_GetSimCsSecurityCksn()
                                         );
                        g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;    /* 设置服务状态                             */
                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S4_E2:INFO: MmServiceState is MM_NORMAL_SERVICE");

                        /* 当前如果update状态是U1状态，直接回复MMCMM_ATTACH_CNF,清除等待ATTACH结果标志位 */

                        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                    MM_MMC_LU_RESULT_SUCCESS,
                                                    NAS_MML_REG_FAIL_CAUSE_NULL);                /* 向MMC发送MMCMM_LU_RESULT_IND             */
                        NAS_MM_SndGmmLuResultInd(MMGMM_LU_SUCCESS,
                                                 NAS_MML_REG_FAIL_CAUSE_NULL);                /* 向MMC发送MMCMM_LU_RESULT_IND             */
                        Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);


                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S4_E2:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
                        NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                    }
                    else
                    {
                        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_IMSI_ATTACH; /* 设置LU类型                               */

                        Mm_ComLuOnly();                                         /* 发送LU REQ                               */
                    }
                }
                else
                {
                    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;   /* 设置LU类型                               */

                    Mm_ComLuOnly();                                         /* 发送LU REQ                               */
                }
            }
        }

    }
}


VOS_VOID Mm_Cell_S19_E2(VOS_VOID* pMsg)
{
    VOS_UINT8                                   ucRet;
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8   enCsUpdateStatus;

    ucRet = Mm_RcvMmcAttachReq(pMsg);

    if (MM_FALSE == ucRet)
    {
    }
    else
    {
        if (VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNtMod))
        {                                                                       /* 网络模式I                                */
            ;
        }
        else
        {                                                                       /* 网络模式II                               */
            if (VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
            {
                enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
                if ( (VOS_FALSE == NAS_MML_IsCsLaiChanged())
                  && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus))
                {                                                               /* 如果LAI不变,更新状态为U1                 */
                    if (MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg)
                    {
                        Mm_ComNasInfoSav(
                                         MM_STATUS_ATTACHED,
                                         NAS_MML_GetSimCsSecurityCksn()
                                         );
                        g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;    /* 设置服务状态                             */
                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S19_E2:INFO: MmServiceState is MM_NORMAL_SERVICE");
                        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                    MM_MMC_LU_RESULT_SUCCESS,
                                                    NAS_MML_REG_FAIL_CAUSE_NULL);                /* 向MMC发送MMCMM_LU_RESULT_IND             */
                        NAS_MM_SndGmmLuResultInd(MMGMM_LU_SUCCESS,
                                                 NAS_MML_REG_FAIL_CAUSE_NULL);                /* 向MMC发送MMCMM_LU_RESULT_IND             */
                        Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);


                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S19_E2:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
                        NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                    }
                    else
                    {
                        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_IMSI_ATTACH; /* 设置LU类型                               */
                        Mm_ComLuOnly();                                         /* 发送LU REQ                               */
                    }
                }
                else
                {
                    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;   /* 设置LU类型                               */
                    Mm_ComLuOnly();                                         /* 发送LU REQ                               */
                }
            }
        }
    }
}

VOS_VOID Mm_Cell_S1_E20(VOS_VOID* pMsg)
{
    VOS_UINT8                    ucRet;
    MMCMM_MODE_CHANGE_REQ_STRU  *pRcvMsg;

    ucRet = Mm_RcvMmcModeChngReq(pMsg);

    if ( MM_FALSE == ucRet )
    {
    }
    else
    {
        pRcvMsg = (MMCMM_MODE_CHANGE_REQ_STRU*)pMsg;
        switch (pRcvMsg->enMsMode)
        {
        case NAS_MML_MS_MODE_PS_CS:                                                     /* A模式的场合                              */
            NAS_MML_SetCsAttachAllowFlg(VOS_TRUE);
            break;
        case NAS_MML_MS_MODE_PS_ONLY:                                                    /* CG模式的场合                             */
#if (FEATURE_ON == FEATURE_ECALL)
            /* ecall only模式配置为PS ONLY不影响CS的attach标记 */
            if (NAS_MML_ECALL_ONLY == NAS_MML_GetCallMode())
            {
                return;
            }
#endif

            NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
            break;
        case NAS_MML_MS_MODE_CS_ONLY:                                                    /* CC模式的场合                             */
            NAS_MML_SetCsAttachAllowFlg(VOS_TRUE);
            break;
        case NAS_MML_MS_MODE_NULL:
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S1_E20:WARNING: MsMode Abnormal");
            break;
        }
    }
}




VOS_VOID Mm_Cell_S22_E1(VOS_VOID* pMsg)
{
    VOS_UINT8   ucRet;

    ucRet = Mm_RcvMmcStartReq(pMsg);
    if (MM_TRUE != ucRet)
    {
    }
    else
    {
        Mm_SndRrRelReq(RRC_CELL_UNBARRED);

        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* 设置ucPreState                           */
        Mm_ComSetMmState(MM_STATE_NULL);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S22_E1:NORMAL: STATUS is MM_STATE_NULL");

        Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

        Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                         NAS_MML_GetSimCsSecurityCksn());
        Mm_ComInit();                                                           /* 全局变量初始化                           */
        Mm_ComStart();                                                          /* 调用收到MMCMM_START_REQ的公共处理        */
    }
}

VOS_VOID Mm_Cell_S9_E2(VOS_VOID* pMsg)
{
    VOS_UINT8                                               ucRet;

    ucRet = Mm_RcvMmcAttachReq(pMsg);
    if (MM_TRUE != ucRet)
    {
    }
    else
    {
        /* 回复MMCMM_ATTACH_CNF的操作,清除等待ATTACH结果标志位 */
        if (MM_WAIT_CS_ATTACH == (g_MmGlobalInfo.stAttachInfo.enAttachType
                                & MM_WAIT_CS_ATTACH))
        {
            NAS_MM_SndMmcAttachCnf();
        }
        g_MmGlobalInfo.stAttachInfo.enAttachType = MM_WAIT_NULL_ATTACH;
    }
}

VOS_VOID Mm_Cell_S3_E12(VOS_VOID* pMsg)
{
    VOS_UINT8   ucRet;

    ucRet = Mm_RcvGmmGprsDetechCmpl(pMsg);
    if (MM_TRUE != ucRet)
    {
    }
    else
    {
        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod))
        {                                                                       /* 网络模式为I,且用户模式为A的场合          */
            if ((MM_TRUE == g_MmGlobalInfo.ucLikeB)
               || (GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta))
            {                                                                   /* 类似于B模式的场合                        */
                ;
            }
            else
            {
                g_MmGlobalInfo.ucLikeB = MM_TRUE;
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S3_E12:INFO: MmLikeB is MM_TRUE");

                if (MM_IDLE_ATTEMPTING_TO_UPDATE == g_MmGlobalInfo.ucState)
                {
                    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;
                    Mm_ComLuOnly();
                }
                else
                {
                    NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                }
            }
        }
    }
}

VOS_VOID Mm_Cell_S4_E12(VOS_VOID* pMsg)
{
    VOS_UINT8   ucRet;
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8  enUpdateStatus;

    VOS_UINT32                          ulCurrMMState;

    ulCurrMMState  = Mm_GetState();

    enUpdateStatus = NAS_MML_GetCsUpdateStatus();

    ucRet = Mm_RcvGmmGprsDetechCmpl(pMsg);
    if (MM_TRUE != ucRet)
    {
    }
    else
    {
        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod))
        {                                                                       /* 网络模式为I,且用户模式为A的场合          */
            if ((MM_TRUE == g_MmGlobalInfo.ucLikeB)
               || (GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta))
            {                                                                   /* 类似于B模式的场合                        */
                ;
            }
            else
            {
                g_MmGlobalInfo.ucLikeB = MM_TRUE;                               /* 设置为类似B模式                          */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S4_E12:INFO: MmLikeB is MM_TRUE");
            }


            if ( (VOS_TRUE               == NAS_MM_IsCsEnableLau())
              && (MM_IDLE_LIMITED_SERVICE == ulCurrMMState) )
            {

                /* 位置区没有改变,不需要进行 */
                if ( (VOS_TRUE == NAS_MML_IsCsLaiChanged())
                  || (NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED == enUpdateStatus))
                {
                    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;
                    Mm_ComLuOnly();
                }
                else
                {

                    g_MmGlobalInfo.ucLikeB = MM_TRUE;
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S4_E12:INFO: MmLikeB is MM_TRUE");
                    NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                    Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                }
            }

        }
    }
}



VOS_VOID Mm_Cell_S17_E12(
    VOS_VOID                           *pMsg
)
{
    VOS_UINT8   ucRet;
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8  enUpdateStatus;

    enUpdateStatus = NAS_MML_GetCsUpdateStatus();

    ucRet = Mm_RcvGmmGprsDetechCmpl(pMsg);
    if (MM_TRUE != ucRet)
    {
    }
    else
    {
        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod))
        {                                                                       /* 网络模式为I,且用户模式为A的场合          */
            if ((MM_TRUE == g_MmGlobalInfo.ucLikeB)
               || (GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta))
            {                                                                   /* 类似于B模式的场合                        */
                ;
            }
            else
            {
                g_MmGlobalInfo.ucLikeB = MM_TRUE;                               /* 设置为类似B模式                          */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S4_E12:INFO: MmLikeB is MM_TRUE");
            }


            if ( VOS_TRUE == NAS_MM_IsCsEnableLau() )
            {
                /* 位置区没有改变,不需要进行 */
                if ( (VOS_TRUE == NAS_MML_IsCsLaiChanged())
                  || (NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED == enUpdateStatus))
                {
                    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;
                    Mm_ComLuOnly();
                }
                else
                {

                    g_MmGlobalInfo.ucLikeB = MM_TRUE;
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S4_E12:INFO: MmLikeB is MM_TRUE");
                    NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                    Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                }
            }

        }
    }
}



VOS_VOID Mm_Cell_S0_E20(VOS_VOID* pMsg)
{
    VOS_UINT8                        ucRet;
    MMCMM_MODE_CHANGE_REQ_STRU      *pModChgReq = VOS_NULL_PTR;

    ucRet = Mm_RcvMmcModeChngReq(pMsg);

    if (MM_TRUE != ucRet)
    {
    }
    else
    {
         g_MmGlobalInfo.ucLikeNetmode2 = MM_FALSE;

        if (VOS_TRUE == NAS_MML_GetSimPresentStatus())
        {                                                                       /* SIM存在的场合                            */
            NAS_MML_SetSimCsRegStatus(VOS_TRUE);
        }
        else
        {                                                                       /* SIM不存在的场合                          */
            NAS_MML_SetSimCsRegStatus(VOS_FALSE);
        }

        pModChgReq = (MMCMM_MODE_CHANGE_REQ_STRU*)pMsg;
        switch (pModChgReq->enMsMode)
        {
        case NAS_MML_MS_MODE_PS_CS:                                                     /* A模式的场合                              */
            NAS_MML_SetCsAttachAllowFlg(VOS_TRUE);
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* 记录原状态                               */
            if (MM_TRUE == g_MmGlobalInfo.ucSysInfoFlg)
            {                                                                   /* 存在缓存系统信息的场合                   */
                if (VOS_TRUE != NAS_MML_GetSimCsRegStatus())
                {                                                               /* SIM无效的场合                            */
                    Mm_ComSetMmState(MM_IDLE_NO_IMSI);


                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S0_E20:NORMAL: STATUS is MM_IDLE_NO_IMSI");
                }
                else
                {
                    Mm_ComSetMmState(MM_WAIT_FOR_ATTACH);


                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S0_E20:NORMAL: STATUS is MM_WAIT_FOR_ATTACH");
                }
            }
            else
            {
                Mm_ComSetMmState(MM_IDLE_NO_CELL_AVAILABLE);


                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S0_E20:NORMAL: STATUS is MM_IDLE_NO_CELL_AVAILABLE");
            }
            break;
        case NAS_MML_MS_MODE_PS_ONLY:                                                    /* CG模式的场合                             */
#if (FEATURE_ON == FEATURE_ECALL)
            /* ecall only模式配置为PS ONLY不影响CS的attach标记 */
            if (NAS_MML_ECALL_ONLY == NAS_MML_GetCallMode())
            {
                return;
            }
#endif

            NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
            break;
        case NAS_MML_MS_MODE_CS_ONLY:                                                    /* CC模式的场合                             */
            NAS_MML_SetCsAttachAllowFlg(VOS_TRUE);
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* 记录原状态                               */
            if (MM_TRUE == g_MmGlobalInfo.ucSysInfoFlg)
            {
                if (VOS_TRUE != NAS_MML_GetSimCsRegStatus())
                {                                                               /* SIM无效的场合                            */
                    Mm_ComSetMmState(MM_IDLE_NO_IMSI);


                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S0_E20:NORMAL: STATUS is MM_IDLE_NO_IMSI");
                }
                else
                {
                    Mm_ComSetMmState(MM_WAIT_FOR_ATTACH);


                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S0_E20:NORMAL: STATUS is MM_WAIT_FOR_ATTACH");
                }
            }
            else
            {
                Mm_ComSetMmState(MM_IDLE_NO_CELL_AVAILABLE);


                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S0_E20:NORMAL: STATUS is MM_IDLE_NO_CELL_AVAILABLE");
            }
            break;
        default:
            break;
        }
    }
}

VOS_VOID Mm_Cell_S3_E20(VOS_VOID* pMsg)
{
    VOS_UINT8                        ucRet;
    MMCMM_MODE_CHANGE_REQ_STRU      *pModChgReq = VOS_NULL_PTR;

    ucRet = Mm_RcvMmcModeChngReq(pMsg);

    if (MM_TRUE != ucRet)
    {
    }
    else
    {
        pModChgReq = (MMCMM_MODE_CHANGE_REQ_STRU*)pMsg;
        switch (pModChgReq->enMsMode)
        {
        case NAS_MML_MS_MODE_PS_CS:                                                     /* A模式的场合                              */
            NAS_MML_SetCsAttachAllowFlg(VOS_TRUE);
            if (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod)
            {                                                                   /* 网络模式为I的场合                        */
                if (MM_TIMER_STOP != gstMmTimer[MM_TIMER_T3212].ucTimerStatus)
                {
                    Mm_TimerStop(MM_TIMER_T3212);                               /* 停T3212                                  */
                }
            }
            break;
        case NAS_MML_MS_MODE_PS_ONLY:                                                    /* CG模式的场合                             */
#if (FEATURE_ON == FEATURE_ECALL)
            /* ecall only模式配置为PS ONLY不影响CS的attach标记 */
            if (NAS_MML_ECALL_ONLY == NAS_MML_GetCallMode())
            {
                return;
            }
#endif

            NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S3_E20:WARNING: MsMode Abnormal");
            break;
        case NAS_MML_MS_MODE_CS_ONLY:                                                    /* CC模式的场合                             */
            NAS_MML_SetCsAttachAllowFlg(VOS_TRUE);
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S3_E20:WARNING: MsMode Abnormal");
            break;
        }
    }
}

VOS_VOID Mm_Cell_S9_E20(VOS_VOID* pMsg)
{
    VOS_UINT8                        ucRet;
    MMCMM_MODE_CHANGE_REQ_STRU      *pModChgReq = VOS_NULL_PTR;

    ucRet = Mm_RcvMmcModeChngReq(pMsg);

    if ( MM_TRUE != ucRet )
    {
    }
    else
    {
        pModChgReq = (MMCMM_MODE_CHANGE_REQ_STRU*)pMsg;
        switch (pModChgReq->enMsMode)
        {
        case NAS_MML_MS_MODE_PS_CS:                                                     /* A模式的场合                              */
            NAS_MML_SetCsAttachAllowFlg(VOS_TRUE);
            if (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod)
            {                                                                   /* 网络模式为I的场合                        */
                if (MM_TRUE == g_MmGlobalInfo.ucLikeB)
                {
                    g_MmGlobalInfo.ucLikeB = MM_FALSE;
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S9_E20:INFO: MmLikeB is MM_FALSE");
                }
            }
            break;
        case NAS_MML_MS_MODE_PS_ONLY:                                                    /* CG模式的场合                             */
#if (FEATURE_ON == FEATURE_ECALL)
            /* ecall only模式配置为PS ONLY不影响CS的attach标记 */
            if (NAS_MML_ECALL_ONLY == NAS_MML_GetCallMode())
            {
                return;
            }
#endif

            NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S9_E20:WARNING: MsMode Abnormal");
            break;
        case NAS_MML_MS_MODE_CS_ONLY:                                                    /* CC模式的场合                             */
            NAS_MML_SetCsAttachAllowFlg(VOS_TRUE);
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S9_E20:WARNING: MsMode Abnormal");
            break;
        }
    }
}
/*******************************************************************************
  MODULE   : Mm_Cell_S11_E27
  FUNCTION : 在wait for network command状态下收到MMCC_DATA_REQ的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      04-04-09    新版作成
     2.  s46746     05-11-24    修改
*******************************************************************************/
VOS_VOID Mm_Cell_S11_E27(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{
    MMCC_DATA_REQ_STRU      *pMmCcDataReq;

    pMmCcDataReq = (MMCC_DATA_REQ_STRU*)pRcvMsg;

    if (MM_FALSE == Mm_RcvCcDataReq(pRcvMsg))
    {                                                                           /* 消息检查结果失败                         */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        if ((pMmCcDataReq->ulTransactionId <= 15)
            && (MM_CS_SIG_CONN_PRESENT == g_MmGlobalInfo.ucCsSigConnFlg))
        {                                                                       /* TIO 等于111并且有CS域信令连接            */
            Mm_SndRrDataReq(pMmCcDataReq->SendCcMsg.ulCcMsgSize,
                            &pMmCcDataReq->SendCcMsg.aucCcMsg[0],
                            RRC_NAS_MSG_PRIORTY_HIGH);                          /* 将CC的消息传送下去                       */
        }
    }

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S14_E50
  FUNCTION : 在WAIT FOR REESTABLISH(WAIT FOR EST_CNF)状态下
             收到RRMM_DATA_IND( CM Message)的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      04-04-09    新版作成
*******************************************************************************/
VOS_VOID Mm_Cell_S14_E50(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    VOS_UINT8   ucTI = 0;                                                       /* CC消息中的TI                             */
    RRMM_DATA_IND_STRU *pRrDataInd = (RRMM_DATA_IND_STRU *) pRcvMsg;            /* 消息RRMM_DATA_IND的结构体指针            */
    VOS_UINT8   *pucCMMsg = VOS_NULL_PTR;                                       /* 指针类型转换                             */
    VOS_UINT8   *pucBakCMMsg = VOS_NULL_PTR;

    Mm_TimerStop(MM_TIMER_T3212);                                               /* 停T3212                                  */

    pucCMMsg = (VOS_UINT8 *)MM_MEM_ALLOC(VOS_MEMPOOL_INDEX_MM,
                            pRrDataInd->RcvNasMsg.ulNasMsgSize,
                            WUEPS_MEM_NO_WAIT);                                 /* 申请内存                                 */
    if (VOS_NULL_PTR == pucCMMsg)
    {                                                                           /* 内存申请失败                             */

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_Cell_S14_E50:ERROR: MALLOC ERROR!");
        return;                                                                 /* 返回                                     */
    }
    pucBakCMMsg = pucCMMsg;
    PS_MEM_SET(pucCMMsg, 0,
               sizeof(VOS_UINT8) * pRrDataInd->RcvNasMsg.ulNasMsgSize);         /* 初始化内存                               */

    PS_MEM_CPY (pucCMMsg,
                &(pRrDataInd->RcvNasMsg.aucNasMsg[0]),
                pRrDataInd->RcvNasMsg.ulNasMsgSize);                            /* 得到消息内容                             */
    ucTI = (VOS_UINT8)(((pucCMMsg[0] & 0xf0) >> 4));                            /* 得到CC消息中的TI                         */
    if (((MM_CONST_NUM_7 == ucTI) || (MM_CONST_NUM_15 == ucTI))
        && (MM_CS_SIG_CONN_PRESENT == g_MmGlobalInfo.ucCsSigConnFlg))
    {                                                                           /* TIO = 111                                */
        Mm_SndCcEstInd (ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize, pucCMMsg);    /* 向CC发送MMCC_EST_IND                     */
    }
    MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucBakCMMsg);                            /* 释放申请的消息                           */

    return;
}

VOS_VOID Mm_Cell_S22_E5(VOS_VOID* pMsg)
{

    VOS_UINT8  ucTiValidFlg = MM_TRUE;



    if ((MMCMM_NO_FORBIDDEN !=
         g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)
        && (MMCMM_FORBIDDEN_PLMN_FOR_GPRS !=
            g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
    {
        Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);
        Mm_SndRrRelReq(RRC_CELL_UNBARRED);

        NAS_MM_ProcCsForbidenFlg_RcvSysInfoInd(g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg);

        if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                      .RcvXXEstReq.ucFlg)
            ||(MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                      .RcvXXEstReq.ucFlg)
            ||(MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                      .RcvXXEstReq.ucFlg))
        {
            ucTiValidFlg = Mm_ComTiChk();
            if (MM_FALSE == ucTiValidFlg)
            {
                Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                   /* RR连接不存在                             */
                NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
            }
            else
            {
                Mm_ComSigRelForDelayMmConnRej();
            }
        }
        else
        {
             Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                      /* RR连接不存在                             */
             NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }
        Mm_ComCheckDelayMmConn(MM_FALSE);
    }
    else
    {
        g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;
    }
}

VOS_VOID Mm_Cell_S23_E5(VOS_VOID* pMsg)
{


    if ((MMCMM_NO_FORBIDDEN !=
         g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)
        && (MMCMM_FORBIDDEN_PLMN_FOR_GPRS !=
            g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
    {
        Mm_TimerStop(MM_TIMER_T3210);                                           /* 停T3210                                  */
        Mm_SndRrRelReq(RRC_CELL_UNBARRED);                                      /* 向RRC发送RRMM_REL_REQ(CS域)              */
        if (MMCMM_FORBIDDEN_PLMN ==
            (MMCMM_FORBIDDEN_PLMN &
                g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
        {
            Mm_ComSaveProcAndCauseVal(MM_LU_PROC, NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN); /* 记录流程和原因值                         */
        }
        else if (MMCMM_FORBIDDEN_LA_FOR_REG_PRVS_SVS
            == (MMCMM_FORBIDDEN_LA_FOR_REG_PRVS_SVS
                & g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)
            )
        {
            Mm_ComSaveProcAndCauseVal(MM_LU_PROC, NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_REG_PRVS_SVS);   /* 记录流程和原因值                         */
        }
        else
        {
            Mm_ComSaveProcAndCauseVal(MM_LU_PROC, NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_ROAM); /* 记录流程和原因值                         */
        }
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* 记录前状态                               */
        Mm_ComSetMmState(LOCATION_UPDATE_REJECTED);

        g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;

        NAS_MM_UpdateEquPlmnInfo(g_MmGlobalInfo.usCauseVal);

        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    g_MmGlobalInfo.usCauseVal);
        NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                 g_MmGlobalInfo.usCauseVal);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S23_E5:NORMAL: STATUS is LOCATION_UPDATE_REJECTED");
        Mm_TimerStart(MM_TIMER_T3240);                                          /* 启动TIMER3240                            */
    }
    else
    {
        g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;
    }
}




VOS_VOID Mm_Cell_S23_E22(VOS_VOID* pMsg)
{
    MM_MSG_IMSI_DETACH_IND_STRU         stMsg;

    if (MM_FALSE == Mm_RcvMmcDetachReq(pMsg))
    {
        return;
    }


    /* 在LAU时候，如果当前信令链接已建立好了，则直接发送DETACH REQ到网侧 */
    if (MM_CS_SIG_CONN_PRESENT == g_MmGlobalInfo.ucCsSigConnFlg)
    {
        /* 24008_CR1201R1_(Rel-8)_C1-082683 24008 4.3.4章节描述:If a RR connection
           exists and the ATT flag indicates that no detach procedure is required,
           the MM sublayer will release locally any ongoing MM connections before
           releasing the RR connection. If a MM specific procedure is active,
           the release of the RR connection may be delayed until the MM specific
           procedure is complete.*/
        if (MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg)
        {
            return;
        }

        /* 在鉴权过程中，则清除鉴权标志信息 */
        if ( MM_RCV_AUTH_CNF_FLG == (g_MmGlobalInfo.ucRcvAgentFlg & MM_RCV_AUTH_CNF_FLG) )
        {
            g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;

            /* 停止保护定时器 */
            Mm_TimerStop(MM_TIMER_PROTECT_AGENT);
        }


        /* 设置DETACH类型，否则在收到REL时候，不回复MMC的DETACH CNF */
        g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_NORMAL;

        /* 如果CS域信令连接存在                     */
        /* 停止LAU的保护定时器T3210 */
        Mm_TimerStop(MM_TIMER_T3210);
        NAS_MM_FillMobileID(&(stMsg.MmIeMobileId.MobileID));

        Mm_ComSetMmState(IMSI_DETACH_INITIATED);
        Mm_ComMsgImsiDetachIniSndOfDataReq(&stMsg);                             /* 填写消息,发送消息                        */
        Mm_TimerStart(MM_TIMER_T3220);                                          /* 启动T3220                                */
    }

    /* 如果当前信令尚未建立好，则等收到EST_CNF后进行DETACH的处理  */

    return;

}

VOS_VOID Mm_Cell_S24_E22(VOS_VOID* pMsg)
{
    MMCMM_DETACH_REQ_STRU*          pMmcDetachReq;
    MM_MSG_IMSI_DETACH_IND_STRU     Msg;

    if (MM_FALSE == Mm_RcvMmcDetachReq(pMsg))
    {
        return;
    }

    pMmcDetachReq = ( MMCMM_DETACH_REQ_STRU* )pMsg;



    if (MMC_MM_PS_DETACH != pMmcDetachReq->enDetachType)
    {
        Mm_TimerStop(MM_TIMER_T3212);                                           /* 停止T3212                                */

        /* 如果注册结果导致卡无效，则返回  */
        if ( VOS_FALSE == NAS_MML_GetSimCsRegStatus() )
        {
            NAS_MM_LocalDetach();
            return;
        }

        if ((MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg)
            || (MM_STATUS_ATTACHED !=
                            g_MmSubLyrShare.MmShare.ucCsAttachState))
        {
            Mm_SndRrRelReq(RRC_CELL_UNBARRED);
            NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
            Mm_ComSaveProcAndCauseVal(MM_IMSI_DETACH, NAS_MML_REG_FAIL_CAUSE_NULL);       /* 记录流程和原因值                         */
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S24_E22:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
            Mm_TimerStart(MM_TIMER_T3240);                                      /* 启动T3240                                */
        }
        else
        {
            NAS_MM_FillMobileID(&(Msg.MmIeMobileId.MobileID));


            /* 设置DETACH类型，否则在收到REL时候，不回复MMC的DETACH CNF */
            g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_NORMAL;

            Mm_ComSetMmState(IMSI_DETACH_INITIATED);
            Mm_ComMsgImsiDetachIniSndOfDataReq(&Msg);                           /* 填写消息,发送消息                        */
            Mm_TimerStart(MM_TIMER_T3220);                                      /* 启动T3220                                */

            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S24_E22:NORMAL: STATUS is IMSI_DETACH_INITIATED");
        }
    }
}


VOS_VOID Mm_Cell_S6_E53(VOS_VOID* pMsg)
{
    Mm_TimerStop(MM_TIMER_T3212);                                               /* 停止T3212                                */

    if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_TRUE;
        return;
    }

    if (MM_IDLE_LOCATION_UPDATE_NEEDED == g_MmGlobalInfo.ucState)
    {
        g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_TRUE;
    }
}
/*******************************************************************************
  Module:   Mm_Cell_S0_E14
  Function: 在MM NULL状态下,接收到GMMMM_GMM_ACTION_RESULT_IND的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2004.05.08  新版做成
*******************************************************************************/
VOS_VOID Mm_Cell_S0_E14(VOS_VOID* pMsg)
{
    if (NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode())
    {
    }
}
/*******************************************************************************
  Module:   Mm_Cell_S0_E13
  Function: 在MM NULL状态下,接收到GMMMM_NETWORK_DETACH_IND的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2004.05.08  新版做成
*******************************************************************************/
VOS_VOID Mm_Cell_S0_E13(VOS_VOID* pMsg)
{
    if (NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode())
    {
    }

}

VOS_VOID Mm_Cell_S4_E13(VOS_VOID *pMsg)
{
    GMMMM_NETWORK_DETACH_IND_STRU       *pstNetWkDetachInd = VOS_NULL_PTR;

    if (MM_FALSE == NAS_MM_RcvGmmNetworkDetechInd(pMsg))
    {
        return;
    }
    if (NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode())
    {
    }
    pstNetWkDetachInd = (GMMMM_NETWORK_DETACH_IND_STRU*)pMsg;

    if (GMMMM_NET_DETACH_REATTACH == pstNetWkDetachInd->enDetachType)
    {
        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod))
        {                                                                       /* 如果为A+I模式                            */
            if (MM_FALSE == g_MmGlobalInfo.ucLikeB)
            {
                g_MmGlobalInfo.ucLikeB = MM_TRUE;                               /* 设置类似于B模式                          */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S4_E13:INFO: MmLikeB is MM_TRUE");
            }
        }
    }
    else if (GMMMM_NET_DETACH_IMSI == pstNetWkDetachInd->enDetachType)
    {
    }
    else
    {
        switch(pstNetWkDetachInd->ulDetachCause)
        {
        case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
            Mm_ComNetDetachCauseHandle(
                (VOS_UINT8)pstNetWkDetachInd->ulDetachCause);
            break;
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
            if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
             && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod))
            {                                                                   /* 如果为A+I模式                            */
                if (MM_FALSE == g_MmGlobalInfo.ucLikeB)
                {
                    g_MmGlobalInfo.ucLikeB = MM_TRUE;                           /* 设置类似于B模式                          */
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S4_E13:INFO: MmLikeB is MM_TRUE");
                }
            }
            break;
        case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
            Mm_ComNasInfoSav(
                            MM_STATUS_DETACHED,
                            MM_CKSN_INVALID
                            );
            Mm_ComDelLai();
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                                ~MM_MS_ID_TMSI_PRESENT;
            NAS_MML_InitUeIdTmsiInvalid();
            break;
        case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
            break;
        default:
            break;
        }
    }
}

VOS_VOID Mm_Cell_S5_E13(VOS_VOID *pMsg)
{
    GMMMM_NETWORK_DETACH_IND_STRU      *pstNetWkDetachInd;
    VOS_UINT8                           ucOldUpdateSts;
    VOS_UINT8                           ucTempUpdateSts;

    if (MM_FALSE == NAS_MM_RcvGmmNetworkDetechInd(pMsg))
    {
        return;
    }

    pstNetWkDetachInd = (GMMMM_NETWORK_DETACH_IND_STRU*)pMsg;

    if (GMMMM_NET_DETACH_REATTACH == pstNetWkDetachInd->enDetachType)
    {
        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod))
        {                                                                       /* 如果为A+I模式                            */
            if (MM_FALSE == g_MmGlobalInfo.ucLikeB)
            {
                g_MmGlobalInfo.ucLikeB = MM_TRUE;                               /* 设置类似于B模式                          */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S5_E13:INFO: MmLikeB is MM_TRUE");
                NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
            }
        }
    }
    else if (GMMMM_NET_DETACH_IMSI == pstNetWkDetachInd->enDetachType)
    {
    }
    else
    {
        switch(pstNetWkDetachInd->ulDetachCause)
        {
        case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
            Mm_ComNetDetachCauseHandle(
                (VOS_UINT8)pstNetWkDetachInd->ulDetachCause);
            break;
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
            if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
             && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod))
            {                                                                   /* 如果为A+I模式                            */
                if (MM_FALSE == g_MmGlobalInfo.ucLikeB)
                {
                    g_MmGlobalInfo.ucLikeB = MM_TRUE;                           /* 设置类似于B模式                          */
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S5_E13:INFO: MmLikeB is MM_TRUE");
                    NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                }
            }
            break;
        case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
            g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;               /* 设置服务状态                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S5_E13:INFO: MmServiceState is MM_LIMITED_SERVICE");
            ucOldUpdateSts = NAS_MML_GetCsUpdateStatus();
            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED);          /* 设置更新状态                             */
            ucTempUpdateSts = NAS_MML_GetCsUpdateStatus();
            NAS_MML_SetCsUpdateStatus(ucOldUpdateSts);
            NAS_MML_SetCsUpdateStatus(ucTempUpdateSts);
            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);


            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S5_E13:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
            break;
        case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
            break;
        default:
            break;
        }
    }
}


VOS_VOID    Mm_Cell_S6_E24( VOS_VOID* pMsg)
{
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList = VOS_NULL_PTR;

#endif

    if ( MM_FALSE == Mm_RcvCcEstReq(pMsg) )
    {                                                                           /* 消息检查结果失败                         */
    }
    else
    {
#if (FEATURE_ON == FEATURE_LTE)

        /* 如果当前为L单模则直接回复CC失败 */
        pstPrioRatList = NAS_MML_GetMsPrioRatList();
        if ( VOS_TRUE == NAS_MML_IsLteOnlyMode(pstPrioRatList) )
        {
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_NOT_SUPPORT_CS_CALL_S1_MODE_ONLY);                        /* 通知CC建立失败                           */
            return;
        }

        if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
        {

            /* NAS修改不拦截电话 */


            NAS_MM_RcvCcEstReq_CSFB();
            return;
        }
#endif

        /* 非紧急呼，当前小区主叫业务受限则不处理 */
        if ((VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
         && (MMCC_EMERGENCY_CALL != g_MmCcEstReq.ulCallType))
        {
            /* 通知CC建立失败 */
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);
            return;
        }

        if ( (MM_CONST_NUM_8 > g_MmCcEstReq.ulTransactionId)
            ||(MM_CONST_NUM_14 < g_MmCcEstReq.ulTransactionId))
        {
            /* TI不合法                                 */
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);                              /* 通知CC建立失败                           */
        }
        else
        {                                                                       /* TI合法                                   */
            if ( MMCC_EMERGENCY_CALL == g_MmCcEstReq.ulCallType )
            {                                                                   /* 是紧急呼叫                               */
                g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;     /* 记录收到建立请求时的状态                 */

                NAS_MM_EstMmConnection(MM_CONN_CTRL_CC);
            }
            else
            {
                if (MM_COM_SRVST_NORMAL_SERVICE == NAS_MM_GetLauUptNeededCsSrvStatus())
                {
                    g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;

                    /* TI合法  */
                    NAS_MM_EstMmConnection(MM_CONN_CTRL_CC);
                }
                else
                {
                    if ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
                    {
                        Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                                       NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);                                  /* 通知CC建立失败                           */
                    }
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;

                    /* GU下location update needed状态收到cc的est_req,NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR */
                    /* MM在unbar to bar或者LMM报access bar的时候才会迁到location update needed状态 */
                    Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                                    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);
                }
            }
        }
    }
}

VOS_VOID    Mm_Cell_S6_E62( VOS_VOID* pMsg)
{
    MM_MSG_CM_SVC_REQ_STRU              stCmSvcReq;
    VOS_UINT16                          usMsgSize = 0;
    VOS_UINT8                          *pucCmSvcReq = 0;

    if ( MM_FALSE == Mm_RcvSmsEstReq(pMsg) )
    {                                                                           /* 消息检查结果失败                         */
    }
    else
    {
        /* 当前小区主叫业务受限则不处理 */
        if (VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
        {
            Mm_SndSmsRelInd(g_MmSmsEstReq.ulTi,
                            NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);            /* 通知SMS建立失败                           */
            return;
        }

        if (MM_COM_SRVST_NORMAL_SERVICE == NAS_MM_GetLauUptNeededCsSrvStatus())
        {
            g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;             /* 记录收到建立请求时的状态                 */

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg
                = MM_TRUE;

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId
                = g_MmSmsEstReq.ulTi;

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulCallType
                = 0;

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulCallPri
                = 0;

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucRat
                = NAS_MML_GetCurrNetRatType();

            /* 填充CM SERVICE REQUEST结构体 */
            Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_SMS, MM_FALSE, &stCmSvcReq);

            /* 填充CM SERVICE REQUEST 消息 */
            pucCmSvcReq = Mm_ComMsgCmSvcReqOfRrEstReq( &stCmSvcReq, &usMsgSize );
            if ( VOS_NULL_PTR == pucCmSvcReq )
            {
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S6_E62:WARNING: MAKE MSG CM SERVICE REQUEST ERROR!");
                return;
            }
            else
            {
                Mm_SndRrEstReq( RRC_EST_CAUSE_ORIGIN_LOW_PRIORITY_SIGNAL,
                   MM_FALSE,
                   usMsgSize, pucCmSvcReq );
                MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucCmSvcReq );
            }

            /* 记录正在建立的MM连接的TI和PD */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI
                = (VOS_UINT8)g_MmSmsEstReq.ulTi;
            g_MmGlobalInfo.ucMMConnEstingPD = MM_IE_PD_SMS_MSG;

            /* 启动保护定时器 */
            Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);

            /* 通知MMC/GMM，CS域的业务已经启动 */
            Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);

            /* 记录状态 */
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
            Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_MM_CONNECTION);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E62:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_MM_CONNECTION");

            /* 设置业务存在标志 */
            NAS_MM_UpdateCsServiceBufferStatusFlg();
            NAS_MM_UpdateCsServiceConnStatusFlg();
        }
        else
        {
            /* GU下location update needed状态收到sms的est_req,NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR */
            /* MM在access bar或者LMM报access bar的时候才会迁到location update needed状态 */
            Mm_SndSmsRelInd(g_MmSmsEstReq.ulTi,
                            NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);                                /* 通知SMS建立失败                           */
        }
    }
}


VOS_VOID    Mm_Cell_S6_E65( VOS_VOID* pMsg)
{
    MM_MSG_CM_SVC_REQ_STRU              stCmSvcReq;
    VOS_UINT16                          usMsgSize = 0;
    VOS_UINT8                          *pucCmSvcReq = 0;

    if ( MM_FALSE == Mm_RcvSsEstReq(pMsg) )
    {                                                                           /* 消息检查结果失败                         */
    }
    else
    {
        /* 当前小区主叫业务受限则不处理 */
        if (VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
        {
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);

            return;
        }

#if (FEATURE_ON == FEATURE_LTE)
        /* 如果当前驻留LTE,则直接发起 */
        if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
        {
            NAS_MM_RcvSsEstReq_CSFB();

            return;
        }
#endif

        if (MM_COM_SRVST_NORMAL_SERVICE == NAS_MM_GetLauUptNeededCsSrvStatus())
        {
            g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;             /* 记录收到建立请求时的状态                 */

           /* 正常服务发起建链 */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg
                = MM_TRUE;
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId
                = g_MmSsEstReq.ulTi;
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulCallType
                = 0;
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulCallPri
                = 0;
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucRat = NAS_MML_GetCurrNetRatType();

            /* 填充CM SERVICE REQUEST结构体 */
            Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_SS_ACT, MM_FALSE, &stCmSvcReq);

            /* 填充CM SERVICE REQUEST 消息 */
            pucCmSvcReq = Mm_ComMsgCmSvcReqOfRrEstReq( &stCmSvcReq, &usMsgSize );
            if (VOS_NULL_PTR == pucCmSvcReq)
            {
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S6_E65:WARNING: MAKE MSG CM SERVICE REQUEST ERROR!");
                return;
            }
            else
            {
                Mm_SndRrEstReq(RRC_EST_CAUSE_ORIGIN_HIGH_PRIORITY_SIGNAL,
                   MM_FALSE, usMsgSize, pucCmSvcReq);
                MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucCmSvcReq);
            }

            /* 记录正在建立的MM连接的TI和PD */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI = (VOS_UINT8)g_MmSsEstReq.ulTi;
            g_MmGlobalInfo.ucMMConnEstingPD = MM_IE_PD_NON_CALL_RLT_SS_MSG;

            /* 启动保护定时器 */
            Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);

            /* 通知MMC，CS域的业务已经启动              */
            Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);

            /* 记录状态 */
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
            Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_MM_CONNECTION);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E65:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_MM_CONNECTION");
        }
        else
        {
            /* ==>A32D12640 */
            /* GU下location update needed状态收到ss的est_req,NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR */
            /* MM在access bar或者LMM报access bar的时候才会迁到location update needed状态 */
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);
        }
    }
}

VOS_VOID    Mm_Cell_S5_E24( VOS_VOID* pMsg)
{
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList = VOS_NULL_PTR;

#endif

    if ( MM_FALSE == Mm_RcvCcEstReq(pMsg) )
    {                                                                           /* 消息检查结果失败                         */
    }
    else
    {
#if (FEATURE_ON == FEATURE_LTE)


        /* 如果当前为L单模则直接回复CC失败 */
        /* 如果当前为L单模则直接回复CC失败 */
        pstPrioRatList = NAS_MML_GetMsPrioRatList();
        if ( VOS_TRUE == NAS_MML_IsLteOnlyMode(pstPrioRatList) )
        {
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_NOT_SUPPORT_CS_CALL_S1_MODE_ONLY);                        /* 通知CC建立失败                           */
            return;
        }

        if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
        {
            /* 如果当前驻留LTE,则也尝试发起普通呼叫 */

            NAS_MM_RcvCcEstReq_CSFB();
            return;
        }
#endif

        /* 非紧急呼，当前小区主叫业务受限则不处理 */
        if ((VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
         && (MMCC_EMERGENCY_CALL != g_MmCcEstReq.ulCallType))
        {
            /* 通知CC建立失败 */
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);

            return;
        }

        g_MmGlobalInfo.ucStaOfRcvXXEstReq =
            g_MmGlobalInfo.ucState;                                             /* 记录收到建立请求时的状态                 */

        if (VOS_FALSE == NAS_MM_IsCcTiValid())
        {
            /* TI不合法                                 */
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);                              /* 通知CC建立失败                           */
        }
        else
        {                                                                       /* TI合法                                   */
            if ( MMCC_EMERGENCY_CALL == g_MmCcEstReq.ulCallType )
            {                                                                   /* 是紧急呼叫                               */
                NAS_MM_EstMmConnection(MM_CONN_CTRL_CC);
            }
            else
            {
                /* 不是紧急呼叫                             */
                if ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
                {
                    /* 已经存在一个保留的MM连接建立请求         */
                    Mm_SndCcRelInd(
                        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                        NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST );                     /* 通知CC建立失败                           */

                    return;
                }

                if (VOS_TRUE == NAS_MML_IsPlmnSupportDam(NAS_MML_GetCurrCampPlmnId()))
                {
                    /* 不触发重拨的原因值 */
                    Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                        NAS_MMCM_REL_CAUSE_MM_INTER_ERR_UE_INVALID_STATE);
                    return;
                }

                /* 缓存消息 */
                NAS_MM_UpdateConnCtrlInfo(MM_CONN_CTRL_CC);

                if (VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNtMod))
                {
                    NAS_MM_SndGmmRegisterInit();                                    /* 通知GMM进行注册                          */
                }
                else
                {
                    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;       /* 设置LU类型                               */
                    g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;
                    Mm_ComLuOnly();                                             /* LU REQ                                   */
                }
            }
        }
    }
}

VOS_VOID Mm_Cell_S0_E22(VOS_VOID* pMsg)
{
    MMCMM_DETACH_REQ_STRU*   pMmcDetachReq;

    if ( MM_FALSE == Mm_RcvMmcDetachReq(pMsg) )
    {
        return;
    }

    pMmcDetachReq = ( MMCMM_DETACH_REQ_STRU* )pMsg;

    if ( MMC_MM_PS_DETACH != pMmcDetachReq->enDetachType )
    {
        NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
        g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;                        /* 设置服务状态                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S0_E22:INFO: MmServiceState is MM_NO_SERVICE");
        Mm_ComNasInfoSav(
                         MM_STATUS_DETACHED,
                         NAS_MML_GetSimCsSecurityCksn());                 /* 设置MM信息                               */
        switch ( pMmcDetachReq->enDetachType )
        {
        case MMC_MM_CS_DETACH:
        case MMC_MM_PS_CS_DETACH:
            /* 判断等待标志是否存在，如果存在则发送MMCMM_DETACH CNF */
            if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                         & MM_WAIT_CS_DETACH))
            {
                NAS_MM_SndMmcDetachCnf(MM_DETACHED);

                g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
            }

            if ( MM_STATE_NULL != Mm_GetState() )
            {
                Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
            }

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S0_E22:WARNING: Detach Cause Abnormal");
            break;
        }
    }
}
/*******************************************************************************
  Module:   Mm_Cell_S0_E59
  Function: 在MM NULL状态下,收到T3230溢出的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2004.05.28  新版做成
*******************************************************************************/
VOS_VOID Mm_Cell_S0_E59(VOS_VOID* pMsg)
{
    Mm_TimerStop(MM_TIMER_T3230);                                               /* 停止TIMER3230                            */
}
/*******************************************************************************
  Module:   Mm_Cell_S0_E60
  Function: 在MM NULL状态下,收到T3240溢出的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2004.05.31  新版做成
*******************************************************************************/
VOS_VOID Mm_Cell_S0_E60(VOS_VOID* pMsg)
{
    Mm_TimerStop(MM_TIMER_T3240);                                               /* 停止TIMER3230                            */
}

VOS_VOID Mm_Cell_S11_E36(VOS_VOID* pMsg)
{
    NAS_EventReport(WUEPS_PID_MM, NAS_OM_EVENT_AUTH_REQ,
                    VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);
    Mm_TimerStop( MM_TIMER_T3212 );                                             /* 停T3212                                  */


    /* WaitForNetworkCommand状态重启T3240 */
    NAS_MM_RestartT3240_WaitForNetworkCommand();

    Mm_ComAuthenRcvAuthenReq();
}

VOS_VOID Mm_Cell_S11_E37(VOS_VOID* pMsg)
{
    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;

    Mm_TimerStop( MM_TIMER_T3212 );                                             /* 停T3212                                  */

    Mm_TimerStop( MM_TIMER_T3240 );                                             /* 停T3240                                  */

    Mm_TimerStart( MM_TIMER_T3240 );                                            /* 启动T3240                                */

    /* 24008_CR1942R3_(Rel-11)_C1-114725 24008 4.3.2.5章节描述如下:
    If the AUTHENTICATION REJECT message is received in any other state the mobile station shall
    abort any MM specific, MM connection establishment or call re-establishment procedure,
    stop any of the timers T3210, or T3230, T3214 or T3216 (if they were running),
    release all MM connections (if any), start timer T3240 and enter the state WAIT FOR NETWORK COMMAND,
    expecting the release of the RR connection. */
    Mm_TimerStop(MM_TIMER_T3214);
    Mm_TimerStop(MM_TIMER_T3216);


    Mm_ComAuthenRcvAuthenRej();                                                 /* 收到AUTHEN REJ的处理                     */

    NAS_MM_SndGmmAuthFailInd();
    NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_AUTH_REJ);

    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                MM_MMC_LU_RESULT_FAILURE,
                                NAS_MML_REG_FAIL_CAUSE_AUTH_REJ);

    /* 判断等待标志是否存在，如果存在则发送MMCGMM_DETACH CNF */
    if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                 & MM_WAIT_CS_DETACH))
    {
        NAS_MM_SndMmcDetachCnf(MMC_MM_NO_IMSI);
        /* 清除等待标志 */
        g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
    }

    NAS_EventReport(WUEPS_PID_MM, NAS_OM_EVENT_AUTH_REJECT,
                    VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);
}


VOS_VOID Mm_Cell_S11_E38(VOS_VOID* pMsg)
{
    Mm_TimerStop( MM_TIMER_T3212 );                                             /* 停T3212                                  */


    /* WaitForNetworkCommand状态重启T3240 */
    NAS_MM_RestartT3240_WaitForNetworkCommand();

    Mm_ComIdentity();                                                           /* IDENTITY过程的处理                       */

    return;
}

VOS_VOID Mm_Cell_S11_E39(VOS_VOID* pMsg)
{
    Mm_TimerStop( MM_TIMER_T3212 );                                             /* 停T3212                                  */


    /* WaitForNetworkCommand状态重启T3240 */
    NAS_MM_RestartT3240_WaitForNetworkCommand();

    Mm_ComTmsiReloc();
    return;
}


VOS_VOID Mm_Cell_S11_E43(VOS_VOID* pMsg)
{
    Mm_TimerStop( MM_TIMER_T3212 );                                             /* 停T3212                                  */


    /* WaitForNetworkCommand状态重启T3240 */
    NAS_MM_RestartT3240_WaitForNetworkCommand();

    Mm_ComInfo();                                                               /* MM INFO过程的处理                        */
    return;
}


VOS_VOID Mm_Cell_S11_E44(VOS_VOID* pMsg)
{
    Mm_TimerStop( MM_TIMER_T3212 );                                             /* 停T3212                                  */


    /* WaitForNetworkCommand状态重启T3240 */
    NAS_MM_RestartT3240_WaitForNetworkCommand();

    return;
}


VOS_VOID Mm_Cell_S11_E47(VOS_VOID* pMsg)
{
    MM_MSG_MM_STATUS_STRU          MsgMmStatus;                                 /* MM STATUS 消息结构体                     */
    VOS_UINT8                      aucClassmark2[4];


    PS_MEM_SET(aucClassmark2, 0x00, sizeof(aucClassmark2));


    MM_Fill_IE_ClassMark2(aucClassmark2);

    if (MM_STATUS_DETACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
    {
        return;
    }
    Mm_TimerStop( MM_TIMER_T3240 );                                             /* 停TIMER3240                              */

    if ( MM_CONST_NUM_0 == ( aucClassmark2[3] & 0x04 ) )
    {                                                                           /* 不支持CCBS                               */
        MsgMmStatus.MmIeRjctCause.ucRejCause =
            NAS_MML_REG_FAIL_CAUSE_MSG_NONEXIST_NOTIMPLEMENTE;                            /* Msg type non-existent or not implemented */
        Mm_ComMsgMmStatusSnd( &MsgMmStatus );                                   /* 填充并发送 MM STATUS 消息                */
    }
    else
    {                                                                           /* 支持CCBS                                 */
        Mm_SndCcPromptInd();                                                    /* 向CC发送MMCC_PROMPT_IND                  */
        g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                   /* 记录迁移之前的状态                       */
        Mm_ComSetMmState(PROCESS_CM_SERVICE_PROMPT);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S11_E47:NORMAL: STATUS is PROCESS_CM_SERVICE_PROMPT");
        Mm_TimerStart(MM_TIMER_PROTECT_CCBS);
    }

    return;
}


VOS_VOID    Mm_Cell_S5_E62( VOS_VOID*pMsg )
{


    if ( MM_FALSE == Mm_RcvSmsEstReq(pMsg) )
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        /* 当前小区主叫业务受限则不处理 */
        if (VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
        {
            Mm_SndSmsRelInd( g_MmSmsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);/* 通知SMS建立失败                          */
            return;
        }

#if (FEATURE_ON == FEATURE_LTE)

        /* 如果当前驻留LTE,则直接回复SMS失败 */
        if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
        {
            Mm_SndSmsRelInd(g_MmSmsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_UE_INVALID_STATE);/* 通知SMS建立失败                          */

            return;
        }
#endif
        if ( ( MM_CONST_NUM_8 > g_MmSmsEstReq.ulTi )
            || ( MM_CONST_NUM_14 < g_MmSmsEstReq.ulTi ) )
        {                                                                       /* TI不合法                                 */
            Mm_SndSmsRelInd( g_MmSmsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);/* 通知SMS建立失败                          */
            return;
        }
        if (VOS_TRUE == NAS_MML_IsPlmnSupportDam(NAS_MML_GetCurrCampPlmnId()))
        {
            /* 不触发重拨的原因值 */
            Mm_SndSmsRelInd( g_MmSmsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_UE_INVALID_STATE);
            return;
        }

        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg
            = MM_TRUE;
        NAS_MML_SetCsServiceBufferStatusFlg(VOS_TRUE);
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                                RcvXXEstReq.ulTransactionId
            = g_MmSmsEstReq.ulTi;
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulCallType
            = 0;
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulCallPri
            = 0;
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucRat = NAS_MML_GetCurrNetRatType();

        if (VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNtMod))
        {
            NAS_MM_SndGmmRegisterInit();                                        /* 通知GMM进行注册                          */
        }
        else
        {
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;           /* 设置LU类型                               */
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;
            Mm_ComLuOnly();                                                 /* LU REQ                                   */
        }
    }


    return;
}


VOS_VOID    Mm_Cell_S5_E65( VOS_VOID*pMsg )
{
    if ( MM_FALSE == Mm_RcvSsEstReq(pMsg) )
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        /* 当前小区主叫业务受限则不处理 */
        if (VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
        {
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);

            return;
        }

#if (FEATURE_ON == FEATURE_LTE)
        /* 如果当前驻留LTE,则直接回复SS失败 */
        if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
        {

            /* 在ATTEMPT TO UPDATE状态尝试发起补充业务 */
            NAS_MM_RcvSsEstReq_CSFB();

            return;
        }
#endif
        if ( ( MM_CONST_NUM_8 > g_MmSsEstReq.ulTi )
            || ( MM_CONST_NUM_14 < g_MmSsEstReq.ulTi ) )
        {                                                                       /* TI不合法                                 */
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);

            return;
        }
        if (VOS_TRUE == NAS_MML_IsPlmnSupportDam(NAS_MML_GetCurrCampPlmnId()))
        {
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_UE_INVALID_STATE);
            return;
        }

        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg
            = MM_TRUE;
        NAS_MML_SetCsServiceBufferStatusFlg(VOS_TRUE);
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                            RcvXXEstReq.ulTransactionId
            = g_MmSsEstReq.ulTi;
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulCallType
            = 0;
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulCallPri
            = 0;
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucRat = NAS_MML_GetCurrNetRatType();

        if (VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNtMod))
        {
            NAS_MM_SndGmmRegisterInit();                                        /* 通知GMM进行注册                          */
        }
        else
        {
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;           /* 设置LU类型                               */
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;
            Mm_ComLuOnly();                                                 /* LU REQ                                   */
        }
    }

    return;
}


VOS_VOID    Mm_Cell_S22_E24( VOS_VOID*pMsg )
{
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList = VOS_NULL_PTR;

#endif

    if ( MM_FALSE == Mm_RcvCcEstReq(pMsg) )
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
#if (FEATURE_ON == FEATURE_LTE)
        /* 如果当前为L单模则直接回复CC失败 */
        pstPrioRatList = NAS_MML_GetMsPrioRatList();
        if ( VOS_TRUE == NAS_MML_IsLteOnlyMode(pstPrioRatList) )
        {
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_NOT_SUPPORT_CS_CALL_S1_MODE_ONLY);                              /* 通知CC建立失败                           */
            return;
        }

        if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
        {
            if (LOCATION_UPDATING_PENDING != g_MmGlobalInfo.ucState)
            {
                /* 异常保护:LTE下不会迁移到这几个状态 */
                Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                               NAS_MMCM_REL_CAUSE_MM_INTER_ERR_UE_INVALID_STATE);                              /* 通知CC建立失败                           */

                return;
            }

            /* 如果当前驻留LTE,MM LOCATION_UPDATING_PENDING状态收到紧急呼叫或普通呼叫需要给LMM
               发起ID_MM_LMM_CSFB_SERVICE_START_NOTIFY，tau注册被拒#17 1次，mm会迁到location update pending */
            NAS_MM_RcvCcEstReq_CSFB();
            return;


            
        }
#endif
        /* 非紧急呼，当前小区主叫业务受限则不处理 */
        if ((VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
         && (MMCC_EMERGENCY_CALL != g_MmCcEstReq.ulCallType))
        {
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);                              /* 通知CC建立失败                           */

            return;
        }


        if ( (MM_CONST_NUM_8 > g_MmCcEstReq.ulTransactionId)
            ||(MM_CONST_NUM_14 < g_MmCcEstReq.ulTransactionId))
        {
            /* TI不合法                                 */
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);                              /* 通知CC建立失败                           */
        }
        else
        {                                                                       /* TI合法                                   */
            if ( ( MM_TRUE ==
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
                || ( MM_TRUE ==
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg )
                || ( MM_TRUE ==
               g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg )
                )
            {
                /* 已经存在一个保留的MM连接建立请求         */
                Mm_SndCcRelInd(
                    g_MmCcEstReq.ulTransactionId,
                    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);                        /* 通知CC建立失败                           */
            }
            else
            {
                /* 缓存消息 */
                NAS_MM_UpdateConnCtrlInfo(MM_CONN_CTRL_CC);
            }
        }
    }

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S11_E40
  FUNCTION : 在WAIT FOR NETWORK COMMAND 状态下收到
                RRMM_DATA_IND(CM SERVICE ACCEPT)的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      04-03-08    新版作成
*******************************************************************************/
VOS_VOID Mm_Cell_S11_E40(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{
    MM_MSG_MM_STATUS_STRU          MsgMmStatus;                                 /* MM STATUS 消息结构体                     */


    MsgMmStatus.MmIeRjctCause.ucRejCause =
        NAS_MML_REG_FAIL_CAUSE_MSG_TYPE_NOT_COMPATIBLE;                                   /* Service option not supported             */
    Mm_ComMsgMmStatusSnd( &MsgMmStatus );                                       /* 填充并发送 MM STATUS 消息                */

    return;
}


VOS_VOID Mm_Cell_S1_E24(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList = VOS_NULL_PTR;

#endif


    if ( MM_FALSE == Mm_RcvCcEstReq(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
#if (FEATURE_ON == FEATURE_LTE)

        /* 如果当前为L单模则直接回复CC失败 */
        pstPrioRatList = NAS_MML_GetMsPrioRatList();
        if ( VOS_TRUE == NAS_MML_IsLteOnlyMode(pstPrioRatList) )
        {
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_NOT_SUPPORT_CS_CALL_S1_MODE_ONLY);                              /* 通知CC建立失败                           */
            return;
        }

        if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
        {


            NAS_MM_RcvCcEstReq_CSFB();
            return;
        }
#endif

        /* 当前no rf时收到业务请求，mm需要通知mmc先触发搜网，普通呼叫需要卡有效，缓存业务请求 */
        if (VOS_TRUE == NAS_MM_IsCcServiceNeedTriggerPlmnSearch())
        {
            /*缓存该服务请求 */
            NAS_MM_UpdateConnCtrlInfo(MM_CONN_CTRL_CC);
            Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);
            return;
        }

        if ( MMCC_MO_NORMAL_CALL == g_MmCcEstReq.ulCallType )
        {
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                               NAS_MMCM_REL_CAUSE_MM_INTER_ERR_OUT_OF_COVERAGE);        /* 通知CC建立失败                           */
        }
        else
        {
            if ( MM_LIMITED_SERVICE == g_MmGlobalInfo.ucMmServiceState )
            {
                if ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
                {
                    /* 已经存在一个保留的MM连接建立请求         */
                    Mm_SndCcRelInd(
                        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                        NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST );                     /* 通知CC建立失败                           */

                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;
                }

                g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;                                     /* 记录收到建立请求时的状态                 */
                if ( (MM_CONST_NUM_8 > g_MmCcEstReq.ulTransactionId)
                    ||(MM_CONST_NUM_14 < g_MmCcEstReq.ulTransactionId))
                {
                    /* TI不合法                                 */
                    Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                                    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);                      /* 通知CC建立失败                           */
                }
                else
                {
                    NAS_MM_EstMmConnection(MM_CONN_CTRL_CC);
                }
            }
            else
            {
                Mm_SndCcRelInd(
                        g_MmCcEstReq.ulTransactionId,
                        NAS_MMCM_REL_CAUSE_MM_INTER_ERR_OUT_OF_COVERAGE);                     /* 通知CC建立失败                           */
            }
        }
    }

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S9_E71
  FUNCTION : 在WAIT FOR OUTGOING MM CONNECTION状态下收到TCMM_TEST_REQ的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇   2004.06.18 新规作成
*******************************************************************************/

VOS_VOID Mm_Cell_S9_E71(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{
    TCMM_TEST_REQ_STRU           *pTcmmTestReq;

    pTcmmTestReq = ( TCMM_TEST_REQ_STRU* )pRcvMsg;

    /*WUEPS_TRACE(MM_LOG_LEVEL_4, "ulMode = %d \r",pTcmmTestReq->ulMode);       */

    if ( TC_RB_TEST_ACTIVE == pTcmmTestReq->ulMode )
    {
        Mm_TimerPause(MM_TIMER_STOP_ALL);                                       /* 暂停所有Timer                            */
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* 原状态迁移                               */
        Mm_ComSetMmState(TEST_CONTROL_ACTIVE);
        /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                          */
        /*    " \nMM:STATUS is  TEST_CONTROL_ACTIVE\r " );                      */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E71:NORMAL: STATUS is TEST_CONTROL_ACTIVE");
    }

}

/*******************************************************************************
  MODULE   : Mm_Cell_S9_E72
  FUNCTION : 在TEST_CONTROL_ACTIVE状态下收到TCMM_DATA_REQ的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇   2004.06.18 新规作成
*******************************************************************************/

VOS_VOID Mm_Cell_S31_E72(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{
    TCMM_DATA_REQ_STRU          *pTcmmDataReq;

    pTcmmDataReq = ( TCMM_DATA_REQ_STRU* )pRcvMsg;

    /*WUEPS_TRACE(MM_LOG_LEVEL_4, "SendTcMsg = %d \r",pTcmmDataReq->SendTcMsg.ulTcMsgSize); */

    Mm_SndRrDataReq(
                pTcmmDataReq->SendTcMsg.ulTcMsgSize,
                &pTcmmDataReq->SendTcMsg.aucTcMsg[0],
                RRC_NAS_MSG_PRIORTY_HIGH);                                      /* 将TC的消息传送下去                       */
}



VOS_VOID Mm_Cell_S9_E73(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{
    RRMM_DATA_IND_STRU          *pRrmmDataInd;

    pRrmmDataInd = ( RRMM_DATA_IND_STRU* )pRcvMsg;


    Mm_TimerStop( MM_TIMER_T3240 );                                             /* 停TIMER3240                              */

    Mm_SndTcDataInd(
                pRrmmDataInd->RcvNasMsg.ulNasMsgSize,
                pRrmmDataInd->RcvNasMsg.aucNasMsg);
}



VOS_VOID Mm_Cell_S31_E71(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{
    TCMM_TEST_REQ_STRU          *pTcmmTestReq;

    pTcmmTestReq = ( TCMM_TEST_REQ_STRU* )pRcvMsg;

    /*WUEPS_TRACE(MM_LOG_LEVEL_4, "ulMode = %d \r",pTcmmTestReq->ulMode);       */

    if ( TC_RB_TEST_DEACTIVE == pTcmmTestReq->ulMode )
    {
        Mm_TimerResume(MM_TIMER_STOP_ALL);
        if ( MM_CS_SIG_CONN_PRESENT == g_MmGlobalInfo.ucCsSigConnFlg )
        {
            Mm_ComSetMmState(g_MmGlobalInfo.ucPreState);
        }
        else
        {
            switch ( g_MmGlobalInfo.ucMmServiceState )
            {
            case MM_NORMAL_SERVICE:
                Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                  */
                /*    " \nMM:STATUS is  MM_IDLE_NORMAL_SERVICE\r " );           */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S31_E71:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
                NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                break;
            case MM_LIMITED_SERVICE:
                Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
                /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                  */
                /*    " \nMM:STATUS is  MM_IDLE_LIMITED_SERVICE\r " );          */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S31_E71:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
                break;
            case MM_ATTEMPTING_TO_UPDATE:
                Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);

                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S31_E71:NORMAL: STATUS is MM_IDLE_ATTEMPTING_TO_UPDATE");


                if (MM_TIMER_STOP == gstMmTimer[MM_TIMER_T3211].ucTimerStatus)
                {
                    NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                }

                break;
            case MM_NO_IMSI:
                Mm_ComSetMmState(MM_IDLE_NO_IMSI);

                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S31_E71:NORMAL: STATUS is MM_IDLE_NO_IMSI");
                break;
            case MM_DETACHED:
                Mm_ComSetMmState(g_MmGlobalInfo.ucPreState);
                /*WUEPS_TRACE(MM_LOG_LEVEL_1,                                   */
                /*    "\nMM:ucState = %d\r", g_MmGlobalInfo.ucState);           */
                PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S31_E71:NORMAL: ucState = ", g_MmGlobalInfo.ucState);
                break;
            default:
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S31_E71:WARNING: g_MmGlobalInfo.ucMmServiceState Abnormal");
                break;
            }
        }
    }

}



VOS_VOID Mm_Cell_S31_E33(
    VOS_VOID                           *pRcvMsg                                 /* 接收消息的头地址                         */
)
{
    /*WUEPS_TRACE(MM_LOG_LEVEL_4, "RRMM_REL_IND = %d \r",RRMM_REL_IND);         */

    Mm_TimerStop( MM_TIMER_T3240 );

    g_MmGlobalInfo.ucCsSigConnFlg = MM_CS_SIG_CONN_ABSENT;
    Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );                             /* RR连接不存在                             */
    NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);

    /* TC状态下收到接入层连接释放消息时，向TC发送TCMM_RR_REL_IND */
    NAS_MM_SndTcRrRelInd();
}


/*******************************************************************************
  MODULE   : Mm_Cell_S0_E21
  FUNCTION : 在NULL状态下收到MMCMM_COVERAGE_LOST_IND的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇   2005.01.06 新规作成
*******************************************************************************/

VOS_VOID Mm_Cell_S0_E21(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{
    if ( MM_FALSE == Mm_RcvMmcCoverageLostInd(pRcvMsg) )
    {
        /* WUEPS_ASSERT(0); */                                                        /* 调用异常处理                             */
    }

}


/*******************************************************************************
  MODULE   : Mm_Cell_S3_E34
  FUNCTION : 在MM IDLE NORMAL SERVICE状态下收到RRMM_SECURITY_IND的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇   2005.01.06 新规作成
*******************************************************************************/

VOS_VOID Mm_Cell_S3_E34(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{
    if ( MM_FALSE == Mm_RcvRrcSecurityInd(pRcvMsg) )
    {
        /* WUEPS_ASSERT(0); */                                                      /* 调用异常处理                             */
    }

}




VOS_VOID Mm_Cell_S25_E24(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{
    if ( MM_FALSE == Mm_RcvCcEstReq(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */                                                        /* 调用异常处理                             */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        Mm_SndCcRelInd(
                        g_MmCcEstReq.ulTransactionId,
                        NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH );                 /* 通知CC建立失败                           */
    }
    return;
}


VOS_VOID Mm_Cell_S22_E13(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{
    GMMMM_NETWORK_DETACH_IND_STRU       *pstNetWkDetachInd;


    if ( MM_FALSE == NAS_MM_RcvGmmNetworkDetechInd(pRcvMsg) )
    {
        /* WUEPS_ASSERT( 0 ); */

        return;
    }



    pstNetWkDetachInd = (GMMMM_NETWORK_DETACH_IND_STRU*)pRcvMsg;

    g_MmGlobalInfo.ucProc = MM_NET_DETACH_PROC;                                 /* 记录当前的流程                           */
    /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                              */
    /*    " \nMM:MmServiceState is MM_NET_DETACH_PROC \r " );                   */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S22_E13:INFO: MmServiceState is MM_NET_DETACH_PROC");
    if ( GMMMM_NET_DETACH_IMSI == pstNetWkDetachInd->enDetachType )
    {
        Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);
        /* Mm_SndRrRelReq(); */                                                 /* 向RRC发送RRMM_REL_REQ(CS域)              */
        /* Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);  */                         /* 通知MMC，CS域的业务已经停止              */
        Mm_ComSaveProcAndCauseVal(MM_NET_DETACH_PROC,
                                                    NAS_MML_REG_FAIL_CAUSE_NTDTH_IMSI);   /* 记录流程和原因值                         */
        g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;              /* 设置服务状态                             */
        /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                          */
        /*    " \nMM:MmServiceState is MM_ATTEMPTING_TO_UPDATE \r " );          */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S22_E13:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");
        Mm_ComToU2Handle();                                                     /* 调用MM进U2的处理                         */
        Mm_SndRrRelReq(RRC_CELL_UNBARRED);
        Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);


    }
    else
    {
        switch ( pstNetWkDetachInd->ulDetachCause )
        {
        case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
            Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);
            Mm_ComNetDetachCauseHandle((VOS_UINT8)pstNetWkDetachInd->ulDetachCause);
            Mm_SndRrRelReq(RRC_CELL_UNBARRED);                                  /* 向RRC发送RRMM_REL_REQ(CS域)              */
            Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);                            /* 通知MMC，CS域的业务已经停止              */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
            /* Mm_ComNetDetachCauseHandle((VOS_UINT8)pstNetWkDetachInd->ulDetachCause); */ /* 调用DETACH过程的原因值处理               */
            NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR);
            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR);
            break;
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
            g_MmGlobalInfo.ucLikeB = MM_TRUE;                                   /* 类似于B模式的全局量                      */
            /*WUEPS_TRACE( MM_LOG_LEVEL_6, " \nMM:MmLikeB is MM_TRUE \r " );    */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S22_E13:INFO: MmLikeB is MM_TRUE");
            break;
        case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
            Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);
            Mm_ComNetDetachCauseHandle((VOS_UINT8)pstNetWkDetachInd->ulDetachCause);
            Mm_SndRrRelReq(RRC_CELL_UNBARRED);                                  /* 向RRC发送RRMM_REL_REQ(CS域)              */
            Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);                            /* 通知MMC，CS域的业务已经停止              */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);

            NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW);

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW);
            /* Mm_ComNetDetachCauseHandle((VOS_UINT8)pstNetWkDetachInd->ulDetachCause); */ /* 调用DETACH过程的原因值处理               */
            break;
        case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
            if ( MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState )
            {
                Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);
                Mm_ComNetDetachCauseHandle(
                    (VOS_UINT8)pstNetWkDetachInd->ulDetachCause);
                Mm_SndRrRelReq(RRC_CELL_UNBARRED);                              /* 向RRC发送RRMM_REL_REQ(CS域)              */
                Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);                        /* 通知MMC，CS域的业务已经停止              */
                NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
                NAS_MM_UpdateEquPlmnInfo(pstNetWkDetachInd->ulDetachCause);

                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                            MM_MMC_LU_RESULT_FAILURE,
                                            pstNetWkDetachInd->ulDetachCause);
                /* Mm_ComNetDetachCauseHandle((VOS_UINT8)pstNetWkDetachInd
                ->ulDetachCause); */                                            /* 调用DETACH过程的原因值处理               */
            }
            break;
        default:
            break;
        }
    }
}



VOS_VOID Mm_Cell_S23_E13(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{
    GMMMM_NETWORK_DETACH_IND_STRU       *pstNetWkDetachInd;


    if ( MM_FALSE == NAS_MM_RcvGmmNetworkDetechInd(pRcvMsg) )
    {
        /* WUEPS_ASSERT(0); */

        return;
    }



    pstNetWkDetachInd = (GMMMM_NETWORK_DETACH_IND_STRU*)pRcvMsg;

    if ( GMMMM_NET_DETACH_REATTACH == pstNetWkDetachInd->enDetachType )
    {
        NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
    }
    else if ( GMMMM_NET_DETACH_IMSI == pstNetWkDetachInd->enDetachType )
    {
        Mm_TimerStop(MM_TIMER_T3210);                                           /* 停止T3210                                */
        Mm_ComSaveProcAndCauseVal(MM_NET_DETACH_PROC,
                                                    NAS_MML_REG_FAIL_CAUSE_NTDTH_IMSI);   /* 记录流程和原因值                         */
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* 记录前状态                               */
        Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S23_E13:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
        Mm_TimerStart(MM_TIMER_T3240);                                          /* 启动TIMER3240                            */
    }
    else
    {
        switch ( pstNetWkDetachInd->ulDetachCause )
        {
        case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
            Mm_TimerStop(MM_TIMER_T3210);                                       /* 停止T3210                                */
            Mm_ComSaveProcAndCauseVal(MM_NET_DETACH_PROC,
                                      (VOS_UINT8)pstNetWkDetachInd->ulDetachCause);   /* 记录流程和原因值                         */
            g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                       /* 设置服务状态                             */
            /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                      */
            /*    " \nMM:MmServiceState is MM_NO_IMSI \r " );                   */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S23_E13:INFO: MmServiceState is MM_NO_IMSI");
            Mm_ComToNoImsiHandle();                                             /* 调用删除IMSI的公共处理                   */
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* 记录前状态                               */
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S23_E13:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
            Mm_TimerStart(MM_TIMER_T3240);                                      /* 启动TIMER3240                            */
            NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR);

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR);
            break;
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
            g_MmGlobalInfo.ucLikeB = MM_TRUE;                                   /* 类似于B模式的全局量                      */
            /*WUEPS_TRACE( MM_LOG_LEVEL_6, " \nMM:MmLikeB is MM_TRUE \r " );    */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S23_E13:INFO: MmLikeB is MM_TRUE");
            break;
        case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
            Mm_TimerStop(MM_TIMER_T3210);                                       /* 停止T3210                                */
            Mm_ComSaveProcAndCauseVal(MM_NET_DETACH_PROC,
                                      (VOS_UINT8)pstNetWkDetachInd->ulDetachCause);   /* 记录流程和原因值                         */
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* 记录前状态                               */
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S23_E13:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
            Mm_TimerStart(MM_TIMER_T3240);                                      /* 启动TIMER3240                            */
            NAS_MM_UpdateEquPlmnInfo(pstNetWkDetachInd->ulDetachCause);
            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        pstNetWkDetachInd->ulDetachCause);
            break;
        case NAS_MML_REG_FAIL_CAUSE_NULL:
            NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
            break;
        default:
            break;
        }
    }
}



VOS_VOID Mm_Cell_S0_E16(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )

{
    if ( MM_FALSE == Mm_RcvGmmAuthFailInd(pRcvMsg) )
    {
        /* WUEPS_ASSERT(0);  */                                                      /* 调用异常处理                             */
        return;
    }

    NAS_MML_SetSimCsRegStatus(VOS_FALSE);


    Mm_ComDelLai();                                                            /* 删除LAI     */
    NAS_MML_InitUeIdTmsiInvalid();
    NAS_MML_SetSimCsSecurityCksn(NAS_MML_CKSN_INVALID);


}

/*******************************************************************************
  MODULE   : Mm_Cell_S0_E33
  FUNCTION : 在NULL状态下收到RRMM_REL_IND的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇        2005.01.10  003020 for MM
*******************************************************************************/
VOS_VOID Mm_Cell_S0_E33(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{
    if ( MM_FALSE == Mm_RcvRrcRelInd(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
    }
    else
    {                                                                           /* 消息检查结果成功                         */

        Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
    }
    return;
}


VOS_VOID Mm_Cell_S2_E33(VOS_VOID *pRcvMsg )
{
    VOS_UINT8                           ucValidFlg;
    NAS_MMCM_REL_CAUSE_ENUM_UINT32      enRelCause;

    ucValidFlg                          = Mm_RcvRrcRelInd(pRcvMsg);
    enRelCause                          = NAS_MM_GetMmCmRelCause();

    if ( MM_TRUE == ucValidFlg )
    {
        Mm_TimerStop(MM_TIMER_WAIT_CONNECT_REL);

        /* 通知MMC连接不存在 */
        Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        /* 释放所有MM连接,正在建的MM连接 */
        /* imsi detach pending状态收到rel ind，
           底层有异常，CS域应该未注册成功，释放所有的MM连接，不重拨 */
        NAS_NORMAL_LOG1(WUEPS_PID_MM, "Mm_Cell_S2_E33: MM Substate ", g_MmGlobalInfo.ucState);
        Mm_ComRelAllMmConn(enRelCause);


        /* 需要清除MM保存的GMM的cause值 */
        Mm_ComProcCauseClear();
    }
    else
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S2_E33:WARNING: ulRelCause Abnormal");
    }
}




VOS_VOID Mm_Cell_S26_E37(VOS_VOID* pMsg)
{
    Mm_TimerStop(MM_TIMER_PROTECT_AGENT);
    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
    Mm_ComToNoImsiHandle();
    Mm_TimerStop(MM_TIMER_T3218);                                               /* 停T3218                                  */
    Mm_ComDelRandRes();                                                         /* 删除RAND和RES                            */

    /* 24008_CR1942R3_(Rel-11)_C1-114725 24008 4.3.2.5章节描述如下:
    If the AUTHENTICATION REJECT message is received in any other state the mobile station shall
    abort any MM specific, MM connection establishment or call re-establishment procedure,
    stop any of the timers T3210, or T3230, T3214 or T3216 (if they were running),
    release all MM connections (if any), start timer T3240 and enter the state WAIT FOR NETWORK COMMAND,
    expecting the release of the RR connection. */
    Mm_TimerStop(MM_TIMER_T3214);
    Mm_TimerStop(MM_TIMER_T3216);

    NAS_MM_SndGmmAuthFailInd();
    NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_AUTH_REJ);
    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                MM_MMC_LU_RESULT_FAILURE,
                                NAS_MML_REG_FAIL_CAUSE_AUTH_REJ);


    /* 判断DETACH等待标志是否存在，如果存在则发送MMCMM_DETACH CNF */
    if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                 & MM_WAIT_CS_DETACH))
    {
        NAS_MM_SndMmcDetachCnf(MMC_MM_NO_IMSI);
        /* 清除等待标志 */
        g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
    }

}



VOS_VOID Mm_Cell_S17_E22(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )

{
    MMCMM_DETACH_REQ_STRU*          pMmcDetachReq;

    if ( MM_FALSE == Mm_RcvMmcDetachReq(pRcvMsg) )
    {
        /* WUEPS_ASSERT(0);  */                                                      /* 调用异常处理                             */

        return;
    }

    pMmcDetachReq = ( MMCMM_DETACH_REQ_STRU* )pRcvMsg;

    if ( MMC_MM_PS_DETACH != pMmcDetachReq->enDetachType )
    {
        /* 在联合RAU过程中，收到DETACH_REQ 消息，GMM不会发起 DETACH过程，MM需要设置标志位 */
        g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_CS_DETACH;
    }
}



VOS_VOID Mm_Cell_S17_E23(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )

{
    if ( MM_FALSE == Mm_RcvMmcPowerOffReq(pRcvMsg) )
    {
        /* WUEPS_ASSERT(0); */                                                       /* 调用异常处理                             */

        return;
    }

#if (FEATURE_ON == FEATURE_LTE)

    /* 如果当前驻留LTE,则直接回复关机 */
    if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        Mm_SndMmcPowerOffCnf();                                                     /* 向MMC发送MMCMM_POWER_OFF_CNF             */
        Mm_ComSetMmState(MM_NULL);

        return;
    }
#endif

    if (MM_STATUS_DETACHED
            == g_MmSubLyrShare.MmShare.ucCsAttachState)
    {
        Mm_SndMmcPowerOffCnf();                                                     /* 向MMC发送MMCMM_POWER_OFF_CNF             */

        Mm_ComSetMmState(MM_NULL);
    }
    else
    {

        Mm_TimerStart(MM_TIMER_MODE_I_CS_PS_POWER_OFF_PROTECT);
    }


    g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_POWEROFF;                        /* 设置DETACH类型                           */
}


VOS_VOID Mm_Cell_S25_E76(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{
    /*A32D10964==>*/
    MM_MSG_IMSI_DETACH_IND_STRU     Msg;
    if ((MM_DETACH_NEED_DELAY == g_MmGlobalInfo.ucDetachType)
      && (MM_CS_SIG_CONN_PRESENT == g_MmGlobalInfo.ucCsSigConnFlg))
    {
        NAS_MM_FillMobileID(&(Msg.MmIeMobileId.MobileID));
        Mm_ComMsgImsiDetachIniSndOfDataReq(&Msg);
    }
    /*<==A32D10964*/
    switch(g_MmGlobalInfo.ucDetachType)
    {
        case MM_DETACH_CS_POWEROFF:
        /*A32D10964==>*/
        case MM_DETACH_NEED_DELAY:
        /*<==A32D10964*/
            Mm_ComNasInfoSav(
                             MM_STATUS_DETACHED,
                             NAS_MML_GetSimCsSecurityCksn());                     /* 设置MM信息                               */

            Mm_SndMmcPowerOffCnf();                                                     /* 向MMC发送MMCMM_POWER_OFF_CNF             */

            Mm_ComSetMmState(MM_STATE_NULL);
            g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S25_E76:NORMAL: STATUS is  MM_STATE_NULL");
            Mm_TimerStop(MM_TIMER_STOP_ALL);
            Mm_SndRrRelReq(RRC_CELL_UNBARRED);
            if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
            {
                MM_SndMmcRrRelInd(RRC_REL_CAUSE_RR_NORM_EVENT);
            }

            break;
        case MM_DETACH_CS_NORMAL:
            /* 判断等待标志是否存在，如果存在则发送MMCMM_DETACH CNF */
            if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                         & MM_WAIT_CS_DETACH))
            {
                NAS_MM_SndMmcDetachCnf(MMC_MM_LIMITED_SERVICE);

                /* 清除等待标志 */
                g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
            }
            Mm_ComSetMmState(g_MmGlobalInfo.ucPreState);
            PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S25_E76:NORMAL: STATUS is",g_MmGlobalInfo.ucState);
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S25_E76:WARNING: Detach type is unexpect.");
            break;

    }
    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S9_E75
  FUNCTION : 在WAIT FOR OUTGOING MM CONNECTION状态下MM_TIMER_PROTECT_AGENT溢出
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇        2005.01.27  007037 for MM
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E75(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{
    /* WUEPS_ASSERT(0); */
}

VOS_VOID Mm_Cell_S12_E77(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{
    /* WUEPS_ASSERT(0); */
    VOS_UINT8 ucCause;
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S12_E77:WARNING: Wait for RRMM_EST_CNF expired");

    if (WAIT_FOR_RR_CONNECTION_LOCATION_UPDATING == g_MmGlobalInfo.ucState)
    {
        ucCause = NAS_OM_MM_CAUSE_RR_CONN_EST_FAIL;
        NAS_EventReport(WUEPS_PID_MM, NAS_OM_EVENT_LOCATION_UPDATE_FAILURE,
                        &ucCause, NAS_OM_EVENT_LAU_FAIL_LEN);
    }

    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;              /* 记录迁移之前的状态                       */


    if (NO_MM_CONN_ESTING !=
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI)
    {
        /* CC发起的RR连接的建立                     */
        Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            ucMMConnEstingTI,
            NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_EST_CNF_TIME_OUT);                          /* 通知CC建立失败                           */

        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI =
            NO_MM_CONN_ESTING;

        PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E77:NORMAL: ucState = ", g_MmGlobalInfo.ucState);
    }
    else if (NO_MM_CONN_ESTING !=
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI)
    {                                                                   /* SS发起的RR连接的建立                     */
        Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI,
                       NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_EST_CNF_TIME_OUT);

        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI =
            NO_MM_CONN_ESTING;

        PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E77:NORMAL: ucState = ", g_MmGlobalInfo.ucState);
    }
    else if (NO_MM_CONN_ESTING !=
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI)
    {                                                                   /* SMS发起的RR连接的建立                    */
        Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
            ucMMConnEstingTI, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_EST_CNF_TIME_OUT);          /* 通知SMS,MM连接建立失败                   */

        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI =
            NO_MM_CONN_ESTING;

        PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E77:NORMAL: ucState = ", g_MmGlobalInfo.ucState);
    }
    else
    {                                                                   /* 没有正在建立的MM连接，即被叫             */

#if (FEATURE_ON == FEATURE_PTM)
        /* 收到CS PAGING后连接建立超时的异常记录 */
        NAS_MM_CsPagingFailRecord(NAS_ERR_LOG_CS_PAGING_CAUSE_EST_TIMEOUT);
#endif

        PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E77:NORMAL: ucState = ", g_MmGlobalInfo.ucState);
    }

    Mm_SndRrRelReq(RRC_CELL_UNBARRED);
    Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );/* MM连接流程                               */
    g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = g_MmGlobalInfo.ucStaOfRcvXXEstReq;
    Mm_TimerStart(MM_TIMER_T3240);
    Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E77:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");

    /* 需要进行LU，则释放缓存的业务 */
    if (MM_TRUE == Mm_ComChkLu())
    {
        if (MM_TRUE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
        {                                                               /* 有等待的CC触发的需要建立的MM连接         */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                        RcvXXEstReq.ucFlg = MM_FALSE;

            Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                .RcvXXEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_EST_CNF_TIME_OUT);                          /* 通知CC建立失败                           */
        }

        if (MM_TRUE ==
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                        RcvXXEstReq.ucFlg )
        {                                                               /* 有等待的CC触发的需要建立的MM连接         */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                    RcvXXEstReq.ucFlg = MM_FALSE;

            Mm_SndSmsRelInd(
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                .RcvXXEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_EST_CNF_TIME_OUT);
        }
        if (MM_TRUE ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                    RcvXXEstReq.ucFlg )
        {                                                               /* 有等待的CC触发的需要建立的MM连接         */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                    RcvXXEstReq.ucFlg = MM_FALSE;

            Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_EST_CNF_TIME_OUT);
        }

    }


}

/*******************************************************************************
  MODULE   : Mm_Cell_S22_E77
  FUNCTION : 在WAIT FOR RR CONNECTION (MM CONNECTION)状态下MM_TIMER_PROTECT_SIGNALLING溢出
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
*******************************************************************************/
VOS_VOID Mm_Cell_S22_E77(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{
    Mm_RcvRrmmEstCnf();
}

VOS_VOID Mm_Cell_S14_E77(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{
    VOS_UINT8 i;
    VOS_UINT8 ucTiValidFlg;

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S14_E77:WARNING: MM_TIMER_PROTECT_SIGNALLING expire at WAIT FOR REESTABLISH(WAIT FOR EST_CNF).");


    /*lint -e701*/
    for (i = 0; i < MM_CONST_NUM_7; i++)
    {                                                                   /* 重建的MM连接                             */
        if ( MM_CONST_NUM_0 !=
        (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
            & ( 0x01 << i ) ) )
        {
            /* 该TI的MM连接正在等待重建                 */
            Mm_SndCcRelInd( i, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_EST_CNF_TIME_OUT);       /* 通知CC,MM连接重建失败                    */
        }
        if ( MM_CONST_NUM_0 !=
        (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
            & ( 0x01 << i ) ) )
        {
            /* 该TI的MM连接正在等待重建                 */
            Mm_SndCcRelInd( ( i + 8 ),NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_EST_CNF_TIME_OUT);/* 通知CC,MM连接重建失败                    */

        }
    }

    /*lint +e701*/

    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
        = MM_CONST_NUM_0;                                               /* 清除存在的MM连接标志                     */
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
        = MM_CONST_NUM_0;                                               /* 清除存在的MM连接标志                     */
    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* 记录迁移之前的状态                       */
    Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
    PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S14_E77:NORMAL: ucState = ", g_MmGlobalInfo.ucState);

    if ( MM_FALSE == Mm_ComChkLu() )
    {

        if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                      .RcvXXEstReq.ucFlg)
            ||(MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                      .RcvXXEstReq.ucFlg)
            ||(MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                      .RcvXXEstReq.ucFlg))
        {
            ucTiValidFlg = Mm_ComTiChk();
            if ( MM_FALSE == ucTiValidFlg )
            {
                Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );         /* RR连接不存在                             */
                NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
            }
            else
            {
                Mm_ComSigRelForDelayMmConnRej();
            }
        }
        else
        {
            Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );             /* RR连接不存在                             */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }

        Mm_ComCheckDelayMmConn( MM_FALSE );
    }
    else
    {
        if ( MM_TRUE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
        {                                                               /* 有等待的CC触发的需要建立的MM连接         */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                            RcvXXEstReq.ucFlg = MM_FALSE;

            Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                .RcvXXEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_EST_CNF_TIME_OUT);                          /* 通知CC建立失败                           */
        }

        if ( MM_TRUE ==
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                        RcvXXEstReq.ucFlg )
        {                                                               /* 有等待的CC触发的需要建立的MM连接         */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                    RcvXXEstReq.ucFlg = MM_FALSE;
            Mm_SndSmsRelInd(
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                .RcvXXEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_EST_CNF_TIME_OUT);
        }
        if ( MM_TRUE ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                    RcvXXEstReq.ucFlg )
        {                                                               /* 有等待的CC触发的需要建立的MM连接         */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                    RcvXXEstReq.ucFlg = MM_FALSE;

            Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_EST_CNF_TIME_OUT);

        }

    }

    NAS_MM_UpdateCsServiceConnStatusFlg();


}



VOS_VOID Mm_Cell_S6_E74(VOS_VOID *pRcvMsg)
{
    RRMM_AC_INFO_CHANGE_IND_STRU               *pRrMmAcInfoChgInd;
    VOS_UINT8                                   ucPsRestrictionFlg;
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8   enCsUpdateStatus;

    ucPsRestrictionFlg      = NAS_MML_GetPsRestrictRegisterFlg();

    pRrMmAcInfoChgInd = (RRMM_AC_INFO_CHANGE_IND_STRU*)pRcvMsg;

    if ( MM_FALSE == Mm_RcvRrcAcInfoChgInd(pRcvMsg) )
    {
        return;
    }
    if (( RRC_NAS_AC_NOT_BAR == pRrMmAcInfoChgInd->ulAcChangeInd)
     || ( RRC_NAS_T3122_EXPIRE == pRrMmAcInfoChgInd->ulAcChangeInd) )
    {
        if (RRC_NAS_AC_NOT_BAR == pRrMmAcInfoChgInd->ulAcChangeInd)
        {
            NAS_MML_SetCsRestrictRegisterFlg(VOS_FALSE);
            NAS_MML_SetCsRestrictPagingFlg(VOS_FALSE);
            NAS_MML_SetCsRestrictNormalServiceFlg(VOS_FALSE);
        }

        if ((VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNtMod))
         && (VOS_FALSE == ucPsRestrictionFlg))
        {
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* 记录前状态                               */
            Mm_ComSetMmState(MM_WAIT_FOR_ATTACH);

            NAS_MM_SndGmmRegisterInit();
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S6_E74:NORMAL: STATUS is MM_WAIT_FOR_ATTACH");
        }
        else
        {
            enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
            if (( VOS_FALSE == NAS_MML_IsCsLaiChanged() )
             && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus) )
            {                                                                   /* 如果LAI不变,更新状态为U1                 */
                if ( MM_TRUE == g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg )
                {
                    g_MmGlobalInfo.LuInfo.ucLuType =
                                    MM_IE_LUT_PERIODIC_UPDATING;                /* 设置LU类型                               */
                }
                else
                {
                    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;       /* 设置LU类型                               */
                }
            }
            else
            {
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;           /* 设置LU类型                               */
            }

            if ((g_MmGlobalInfo.LuInfo.ucImmAccRejLuAttmptCnt < MM_CONST_NUM_4)
             || (RRC_NAS_AC_NOT_BAR == pRrMmAcInfoChgInd->ulAcChangeInd))
            {
                Mm_ComLuOnly();                                                 /* 发送LU REQ                               */
            }

            if (g_MmGlobalInfo.LuInfo.ucImmAccRejLuAttmptCnt >= MM_CONST_NUM_4)
            {
                NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
            }
        }
    }
}


VOS_VOID Mm_Cell_S0_E24(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    if ( MM_FALSE == Mm_RcvCcEstReq(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */                                                     /* 调用异常处理                             */
        return;
    }
    else
    {
        /* 消息检查结果成功                         */
        Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                       NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);                      /* 通知CC建立失败                           */
    }
    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S10_E40
  FUNCTION : 在MM CONNECTION ACTIVE状态下收到RRMM_REL_IND的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇        2005.01.11  Status for MM
*******************************************************************************/
VOS_VOID Mm_Cell_S10_E40(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{
    MM_MSG_MM_STATUS_STRU    Msg;

    Msg.MmIeRjctCause.ucRejCause = NAS_MML_REG_FAIL_CAUSE_MSG_TYPE_NOT_COMPATIBLE;

    Mm_ComMsgMmStatusSnd(&Msg);
}



VOS_VOID Mm_Cell_S31_E1(VOS_VOID* pMsg)
{
    if (MM_TRUE == Mm_RcvMmcStartReq(pMsg))
    {


        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* 设置ucPreState                           */

        Mm_ComSetMmState(MM_STATE_NULL);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S31_E1:NORMAL: STATUS is MM_STATE_NULL");

        Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

        Mm_ComNasInfoSav(
                MM_STATUS_DETACHED,
                NAS_MML_GetSimCsSecurityCksn()
                );
        Mm_ComInit();                                                           /* 全局变量初始化                           */
        Mm_ComStart();                                                          /* 调用收到MMCMM_START_REQ的公共处理        */
    }
    else
    {
        /* WUEPS_ASSERT(0); */
    }
    return;                                                                     /* 返回                                     */
}



VOS_VOID Mm_Cell_S0_E78(VOS_VOID* pMsg)
{
#if 0
    PS_OM_MSG_HEAD_STRU *pNewMsg;
    pNewMsg = (PS_OM_MSG_HEAD_STRU *)pMsg;

    switch (pNewMsg->ulMsgID)
    {
        case AGENT_MM_INQUIRE:
            Mm_RcvMmAgentInquire(pMsg);
            break;
        case MM_TRANS_STATUS_INFO_REQ:
            Mm_SndAgentTransInfo(pNewMsg);
            break;
        default:
            break;
    }
#endif
}


VOS_VOID Mm_Cell_S31_E23(VOS_VOID* pMsg)
{

    MM_MSG_IMSI_DETACH_IND_STRU     Msg;

    if ( MM_FALSE == Mm_RcvMmcPowerOffReq(pMsg) )
    {
        return;
    }


    /* TC状态下收到关机请求时，主动发起REL_REQ */
    if ( g_MmGlobalInfo.ucCsSigConnFlg == MM_CS_SIG_CONN_PRESENT )
    {
        NAS_MM_SndTcRrRelInd();

        Mm_SndRrRelReq(RRC_CELL_UNBARRED);
    }


    if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
     && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod))
    {                                                                           /* 如果为A+I模式                            */
        if ((VOS_FALSE == NAS_MML_GetPsRestrictRegisterFlg())
         && (MM_FALSE == g_MmGlobalInfo.ucLikeB)
         && (GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta))
        {

            Mm_TimerStart(MM_TIMER_MODE_I_CS_PS_POWER_OFF_PROTECT);
            g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_POWEROFF;                /* 设置DETACH类型                           */
            return;                                                             /* 不是类似B或者A+II模式的场合              */
        }
    }
    Mm_TimerStop(MM_TIMER_STOP_ALL);
    g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_POWEROFF;                        /* 设置DETACH类型                           */

    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

    if ( MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState )
    {
        if ( MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg )
        {
            if ( MM_CS_SIG_CONN_PRESENT == g_MmGlobalInfo.ucCsSigConnFlg )
            {
                Mm_SndRrRelReq(RRC_CELL_UNBARRED);
                /* ==>A32D12706 */
                Mm_TimerStart(MM_TIMER_PROTECT_DETACH);
                Mm_ComSetMmState(IMSI_DETACH_INITIATED);
                /* <==A32D12706 */
            }
            else
            {
                MM_SndMmcRrRelInd(RRC_REL_CAUSE_RR_NORM_EVENT);
                Mm_SndMmcPowerOffCnf();
                Mm_ComSetMmState(MM_STATE_NULL);

            }
            g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;                    /* 设置服务状态                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S31_E23:INFO: MmServiceState is MM_NO_SERVICE");
            Mm_ComNasInfoSav(
                             MM_STATUS_DETACHED,
                             NAS_MML_GetSimCsSecurityCksn());             /* 设置MM信息                               */


            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S31_E23:NORMAL: STATUS is MM_STATE_NULL");
        }
        else
        {
            if ( MM_CS_SIG_CONN_PRESENT == g_MmGlobalInfo.ucCsSigConnFlg )
            {
                NAS_MM_FillMobileID(&(Msg.MmIeMobileId.MobileID));

                Mm_ComSetMmState(IMSI_DETACH_INITIATED);

                Mm_ComMsgImsiDetachIniSndOfDataReq(&Msg);                       /* 填写消息,发送消息                        */
                Mm_TimerStart(MM_TIMER_T3220);                                  /* 启动保护定时器                           */
                Mm_TimerStart(MM_TIMER_PROTECT_DETACH);


                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S31_E23:NORMAL: STATUS is IMSI_DETACH_INITIATED");
            }
            else
            {
                NAS_MM_FillMobileID(&(Msg.MmIeMobileId.MobileID));

                g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
                Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_IMSI_DETACH);

                Mm_ComMsgImsiDetachIniSndOfEstReq(&Msg);                        /* 填写消息,发送消息                        */
                Mm_TimerStart(MM_TIMER_PROTECT_DETACH);


                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S31_E23:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_IMSI_DETACH");
            }

        }
    }
    else
    {
        if ( MM_CS_SIG_CONN_PRESENT == g_MmGlobalInfo.ucCsSigConnFlg )
        {
            Mm_SndRrRelReq(RRC_CELL_UNBARRED);
        }
        g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;                        /* 设置服务状态                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S31_E23:INFO: MmServiceState is MM_NO_SERVICE");
        Mm_ComNasInfoSav(
                         MM_STATUS_DETACHED,
                         NAS_MML_GetSimCsSecurityCksn());                 /* 设置MM信息                               */
        Mm_SndMmcPowerOffCnf();
        Mm_ComSetMmState(MM_STATE_NULL);
        if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
        {
            MM_SndMmcRrRelInd(RRC_REL_CAUSE_RR_NORM_EVENT);
        }

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S31_E23:NORMAL: STATUS is MM_STATE_NULL");
    }
}

/*******************************************************************************
  MODULE   : Mm_Cell_S12_E79
  FUNCTION : 在WAIT FOR RR CONNECTION (MM CONNECTION)状态下MM_TIMER_PROTECT_CC溢出
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇        2005.01.28  新规做成
*******************************************************************************/
VOS_VOID Mm_Cell_S12_E79(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{

}


VOS_VOID Mm_Cell_S13_E79(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{
    VOS_UINT8 ucTiValidFlg;

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S13_E79:WARNING: MM_TIMER_PROTECT_CC expire at WAIT FOR REESTABLISH(WAIT FOR REEST REQ).");

    Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
    PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S13_E79:NORMAL: ucState = ", g_MmGlobalInfo.ucState);

    Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );                     /* RR连接不存在                             */
    NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
    Mm_ComProcCauseProcess();

    if ( MM_FALSE == Mm_ComChkLu() )
    {
        if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                      .RcvXXEstReq.ucFlg)
            ||(MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                      .RcvXXEstReq.ucFlg)
            ||(MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                      .RcvXXEstReq.ucFlg))
        {
            ucTiValidFlg = Mm_ComTiChk();
            if ( MM_FALSE == ucTiValidFlg )
            {
                Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );     /* RR连接不存在                             */
                NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
            }
            else
            {
                Mm_ComSigRelForDelayMmConnRej();
            }
        }
        Mm_ComCheckDelayMmConn( MM_FALSE );
    }
    else
    {
        if ( MM_TRUE ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                    RcvXXEstReq.ucFlg )
        {                                                           /* 有等待的CC触发的需要建立的MM连接         */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                    RcvXXEstReq.ucFlg = MM_FALSE;

            Mm_SndCcRelInd(
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                .RcvXXEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_CC_REEST_TIME_OUT);                      /* 通知CC建立失败                           */
        }
        if ( MM_TRUE ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                    RcvXXEstReq.ucFlg )
        {                                                           /* 有等待的CC触发的需要建立的MM连接         */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                    RcvXXEstReq.ucFlg = MM_FALSE;
            Mm_SndSmsRelInd(
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                .RcvXXEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_CC_REEST_TIME_OUT);
        }
        if ( MM_TRUE ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                    RcvXXEstReq.ucFlg )
        {                                                           /* 有等待的CC触发的需要建立的MM连接         */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                    RcvXXEstReq.ucFlg = MM_FALSE;

            Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_CC_REEST_TIME_OUT);
        }
    }

    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_CC_REEST_TIME_OUT);
}


/*******************************************************************************
  MODULE   : Mm_Cell_S9_E15
  FUNCTION : 在WAIT_FOR_OUTGOING_MM_CONNECTION状态下GMMMM_LU_INITIATION溢出
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇        2005.01.28  新规做成
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E15(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{
    GMMMM_LU_INITIATION_STRU    *pstMmcLuIni;

    if ( MM_FALSE == Mm_RcvGmmLuIni(pRcvMsg) )
    {
        /* WUEPS_ASSERT(0); */                                                      /* 异常错误处理                             */
        return;
    }

    pstMmcLuIni = ( GMMMM_LU_INITIATION_STRU* )pRcvMsg;

    if ( GMMMM_T3312_EXPIRED == pstMmcLuIni->enTimerExpiredFlg )
    {
        g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_TRUE;
    }
}



VOS_VOID Mm_Cell_S9_E5(VOS_VOID* pMsg)
{
    MMCMM_SYS_INFO_IND_STRU            *pstSysInfoMsg;



    g_MmGlobalInfo.ucConnRcvSysFlg = MM_TRUE;

    /* G下在该状态收到系统消息在预处理丢弃，因此只会在W下收到该消息 */
    pstSysInfoMsg   = (MMCMM_SYS_INFO_IND_STRU*)pMsg;

    /* 如果当前CS注册变为受限，需要重新设置建链前状态 */
    if (VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg())
    {
        if (MM_IDLE_NO_IMSI != g_MmGlobalInfo.ucStaOfRcvXXEstReq)
        {
            g_MmGlobalInfo.ucStaOfRcvXXEstReq = MM_IDLE_LOCATION_UPDATE_NEEDED;
        }
    }

    /* 如果当前CS注册变为不受限，需要重新设置建链前状态 */
    if (VOS_TRUE == pstSysInfoMsg->ucCsChanged2UnBarFlg)
    {
        NAS_MM_UpdateMmStateCsRegRestrictBarToUnbar();
    }
    /* MM处于通话中，PS域bar，期间T3312超时，GMM会通知MM，此时MM会将T3212超时标志
       置位TRUE,此后如果PS又从bar转为不bar, MM需要将T3212超时标志清除掉。
       否则，当通话结束时，Mm_ComChkLu函数 检测到该标志位后，会发起不期望的LU过程。 */
    if (  (VOS_TRUE == pstSysInfoMsg->ucPsChanged2UnBarFlg)
        &&(MM_TRUE == g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg ))
    {
        if (VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNewNtMod))
        {
            g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_FALSE;
        }
    }

    if (VOS_TRUE == pstSysInfoMsg->ucCsChanged2UnBarFlg)
    {
        NAS_MM_UpdateMmStateCsRegRestrictBarToUnbar();
    }
}



VOS_VOID Mm_Cell_S12_E5(VOS_VOID* pMsg)
{
    VOS_UINT8                           ucLaiChange;
    VOS_UINT32                          ulCsServExist;

    VOS_UINT32                          ulCsfbEmgCallLaiChgLauFirstFlg;

    ucLaiChange    = NAS_MML_IsCsLaiChanged();
    ulCsServExist  = Mm_ComJudgeCsServExist();

    /* 如果当前CS注册变为受限，需要重新设置建链前状态 */
    if (VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg())
    {
        if (MM_IDLE_NO_IMSI != g_MmGlobalInfo.ucStaOfRcvXXEstReq)
        {
            g_MmGlobalInfo.ucStaOfRcvXXEstReq = MM_IDLE_LOCATION_UPDATE_NEEDED;
        }
    }

    /* 如果当前CS注册变为不受限，需要重新设置建链前状态 */
    if (NAS_MML_RESTRICTION_BAR_TO_UNBAR == NAS_MML_GetCsRegisterBarToUnBarFlg())
    {
        NAS_MM_UpdateMmStateCsRegRestrictBarToUnbar();
    }

    /* 驻留受限网络，且当前无紧急呼，返回 */
    if (MM_CS_SERV_EMERGENCY_CALL_EXIST == ulCsServExist)
    {

        g_MmGlobalInfo.ucConnRcvSysFlg = MM_TRUE;

        /* 正常驻留，出服务区，拨打紧急呼，在建链过程中紧急驻留到受限小区，状态未刷新，导致T3212被异常
           停止，并且紧急呼结束后错误上报正常服务状态 */
        if ( (MMCMM_NO_FORBIDDEN != g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)
          && (MMCMM_FORBIDDEN_PLMN_FOR_GPRS != g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg) )
        {
            if (MM_IDLE_NO_IMSI != g_MmGlobalInfo.ucStaOfRcvXXEstReq)
            {
                g_MmGlobalInfo.ucMmServiceState   = MM_LIMITED_SERVICE;
                g_MmGlobalInfo.ucStaOfRcvXXEstReq = MM_IDLE_LIMITED_SERVICE;
            }

            return;
        }

        ulCsfbEmgCallLaiChgLauFirstFlg = NAS_MML_GetCsfbEmgCallLaiChgLauFirstFlg();

        if ((VOS_FALSE == NAS_MML_GetCsRestrictRegisterFlg())
         && (VOS_TRUE == ucLaiChange)
         && (VOS_TRUE == ulCsfbEmgCallLaiChgLauFirstFlg))
        {
            g_MmGlobalInfo.ucPendingLu  = VOS_TRUE;
            g_MmGlobalInfo.ucConnRcvSysFlg = MM_TRUE;

            Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);
            Mm_SndRrRelReq(RRC_CELL_UNBARRED);
            Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);
        }

        return;
    }

    if (VOS_TRUE == NAS_MM_IsCsForbidden())
    {
        Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

        NAS_MM_ProcCsForbidenFlg_RcvSysInfoInd(g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg);

        Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_FORB_LA);

        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
    }
    else
    {
        /* 无异系统切换，正常业务建链过程中发生位置区改变 */
        if ((VOS_FALSE == NAS_MML_GetCsRestrictRegisterFlg())
         && (VOS_TRUE == ucLaiChange))
        {
            g_MmGlobalInfo.ucPendingLu  = VOS_TRUE;
            g_MmGlobalInfo.ucConnRcvSysFlg = MM_TRUE;

            g_MmSubLyrShare.MmShare.ucPagingPlmnSrch = MM_PAGING_PLMNSRCH_TRUE;

            /* 释放连接，在连接释放后，首先进行LU/RAU，然后继续处理呼叫消息 */
            Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);
            Mm_SndRrRelReq(RRC_CELL_UNBARRED);
            Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);
            return;
        }

        /* 如果cs update状态是U0,LAI未发生变化，上报注册结果
           对应场景: LAU过程中(LOCATION UPDATING INITIATED状态)收到业务请求，缓存
           未收到LAU accept，直接rel ind，MM迁到idle normal service状态，处理缓存的业务请求
           业务建链过程中(WAIT FOR RR CONNECTION (MM CONNECTION)状态)收到系统消息，补报注册成功
           否则在电话过程中，界面会显示无服务或限制服务 */
        if ((NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == NAS_MML_GetCsUpdateStatus())
         && (VOS_FALSE == ucLaiChange)
         && (MM_NORMAL_SERVICE == g_MmGlobalInfo.ucMmServiceState))
        {
            /* 向MMC发送MMCMM_LU_RESULT_IND */
            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                        MM_MMC_LU_RESULT_SUCCESS,
                                        NAS_MML_REG_FAIL_CAUSE_LOCAL_NULL);

            /* 向GMM发送MMGMM_LU_RESULT_IND */
            NAS_MM_SndGmmLuResultInd(MMGMM_LU_SUCCESS,
                                     NAS_MML_REG_FAIL_CAUSE_LOCAL_NULL);
        }
    }
    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S10_E50
  FUNCTION : 在MM_CONNECTION_ACTIVE状态下
             收到RRMM_DATA_IND( CM Message)的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      2005.02.02  新版作成
*******************************************************************************/
VOS_VOID Mm_Cell_S10_E50(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{
    VOS_UINT8   ucTI = 0;                                                           /* CC消息中的TI                             */
    RRMM_DATA_IND_STRU *pRrDataInd = ( RRMM_DATA_IND_STRU *) pRcvMsg;           /* 消息RRMM_DATA_IND的结构体指针            */
    VOS_UINT8   *pucCMMsg = VOS_NULL_PTR;                                                   /* 指针类型转换                             */
    VOS_UINT8   *pucBakCMMsg = VOS_NULL_PTR;

    if ( MM_LIMITED_SERVICE != g_MmGlobalInfo.ucMmServiceState )
    {
        Mm_TimerStop( MM_TIMER_T3212 );                                         /* 停T3212                                  */
    }

    pucCMMsg = (VOS_UINT8 *)MM_MEM_ALLOC(
                           VOS_MEMPOOL_INDEX_MM,
                           pRrDataInd->RcvNasMsg.ulNasMsgSize,
                           WUEPS_MEM_NO_WAIT);                                  /* 申请内存                                 */
    if( VOS_NULL_PTR == pucCMMsg )
    {                                                                           /* 内存申请失败                             */

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_Cell_S10_E50:ERROR: MALLOC ERROR!");
        return;                                                                 /* 返回                                     */
    }

    /*lint -e701*/
    pucBakCMMsg = pucCMMsg;
    PS_MEM_SET(pucCMMsg, 0,
        sizeof( VOS_UINT8 ) * pRrDataInd->RcvNasMsg.ulNasMsgSize );                 /* 初始化内存                               */
    PS_MEM_CPY (pucCMMsg, & ( pRrDataInd->RcvNasMsg.aucNasMsg[0] ),
        pRrDataInd->RcvNasMsg.ulNasMsgSize );                                   /* 得到消息内容                             */
    ucTI = ( VOS_UINT8 )( ( ( pucCMMsg[0] & 0xf0 ) >> 4 ) );                        /* 得到CC消息中的TI                         */
    if ( ( MM_CONST_NUM_7 == ucTI ) || ( MM_CONST_NUM_15 == ucTI ) )
    {                                                                           /* TIO = 111                                */
        Mm_SndCcEstInd ( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize, pucCMMsg );  /* 向CC发送MMCC_EST_IND                     */
    }
    if ( MM_CONST_NUM_7 > ucTI )
    {                                                                           /* 网侧建立的MM连接                         */
        if ( MM_CONST_NUM_0 != (
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
            & ( 0x01 << ucTI ) ) )
        {                                                                       /* 该连接存在                               */
            Mm_SndCcDataInd ( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize,
            pucCMMsg );                                                         /* 向CC发送MMCC_DATA_IND                    */
        }
        else
        {                                                                       /* 该连接不存在                             */
            Mm_SndCcEstInd ( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize,
            pucCMMsg );                                                         /* 向CC发送MMCC_EST_IND                     */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0] |=
                ( VOS_UINT8 )( 0x01 << ucTI );                                      /* 设置已经存在的MM连接的标志位             */
            Mm_ComCheckDelayMmConn( MM_FALSE );
        }
    }
    else if ( ( MM_CONST_NUM_7 < ucTI ) && ( MM_CONST_NUM_15 > ucTI ) )
    {                                                                           /* CC建立的MM连接                           */
        if ( MM_CONST_NUM_0 != (
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
            & ( 0x01 << ( ucTI - 8 ) ) ) )
        {                                                                       /* 该连接存在                               */
            Mm_SndCcDataInd ( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize,
                pucCMMsg );                                                     /* 向CC发送MMCC_DATA_IND                    */
        }
        else
        {                                                                       /* 该连接不存在                             */
            Mm_SndCcEstInd ( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize,
            pucCMMsg );                                                         /* 向CC发送MMCC_EST_IND                     */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] |=
                ( VOS_UINT8 )( 0x01 << ( ucTI - 8 ) );                              /* 设置已经存在的MM连接的标志位             */
            Mm_ComCheckDelayMmConn( MM_FALSE );
        }
    }
    else
    {

    }


    /*lint +e701*/

    MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucBakCMMsg );                                /* 释放申请的消息                           */

    return;
}

VOS_VOID Mm_Cell_S5_E80(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{

    if ( MM_FALSE == Mm_RcvSsAbortReq( pRcvMsg ) )
    {                                                                           /* 消息检查结果失败                         */
        ;
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                                                      .RcvXXEstReq.ucFlg)
         && (g_MmSsAbortReq.ulTransactionId == g_MmGlobalInfo
                .ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId))
        {
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                                             .RcvXXEstReq.ucFlg = MM_FALSE;

            if (g_MmSsAbortReq.ulTransactionId == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI)
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI = NO_MM_CONN_ESTING;
            }

#if (FEATURE_ON == FEATURE_LTE)

            /* 当前存在补充业务的CSFB流程，则清空CSFB存在标志 */
            if (NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST == NAS_MML_GetCsfbServiceStatus())
            {
                NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
                {
                    /* 通知L CSFB 流程终止 */
                    NAS_MM_SndLmmCsfbServiceAbortNotify();
                }

            }
#endif
        }

        NAS_MM_UpdateCsServiceBufferStatusFlg();
    }
    return;
}


VOS_VOID Mm_Cell_S32_E80(
    VOS_VOID                           *pRcvMsg
)
{
    if (WAIT_FOR_OUTGOING_MM_CONNECTION == g_MmGlobalInfo.ucSuspendPreState)
    {
        Mm_Cell_S32_DataTransfer(pRcvMsg);
        return;
    }

    if ( MM_FALSE == Mm_RcvSsAbortReq( pRcvMsg ) )
    {                                                                           /* 消息检查结果失败                         */
        ;
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                                                      .RcvXXEstReq.ucFlg)
         && (g_MmSsAbortReq.ulTransactionId == g_MmGlobalInfo
                .ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId))
        {
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                                             .RcvXXEstReq.ucFlg = MM_FALSE;

            NAS_MM_SndRrMmServiceAbortNotify(WUEPS_PID_WRR);
            NAS_MM_SndRrMmServiceAbortNotify(UEPS_PID_GAS);

#if (FEATURE_ON == FEATURE_LTE)

            /* 当前存在补充业务的CSFB流程，则清空CSFB存在标志 */
            if (NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST == NAS_MML_GetCsfbServiceStatus())
            {
                NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
                {
                    /* 通知L CSFB 流程终止 */
                    NAS_MM_SndLmmCsfbServiceAbortNotify();
                }
            }
#endif
        }

        NAS_MM_UpdateCsServiceBufferStatusFlg();
    }
    return;
}





VOS_VOID Mm_Cell_S9_E80(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{

    if ( MM_FALSE == Mm_RcvSsAbortReq( pRcvMsg ) )
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        if ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI ==
            g_MmSsAbortReq.ulTransactionId )
        {                                                                       /* 终止的MM连接建立是正在建立的             */
            Mm_TimerStop( MM_TIMER_T3230 );                                     /* 停T3230                                  */
            Mm_ComMsgCmSvcAbortSnd();
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI =
                NO_MM_CONN_ESTING;                                              /* 清除正在建立的MM连接的标志               */
            g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                g_MmGlobalInfo.ucStaOfRcvXXEstReq;                              /* 返回到接收到建立MM连接请求时的状态       */
            Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );    /* MM连接流程                               */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* 记录迁移之前的状态                       */
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                      */
            /*    " \nMM:STATUS is  WAIT_FOR_NETWORK_COMMAND\r " );             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E80:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
            Mm_TimerStart(MM_TIMER_T3240);                                      /* 启动TIMER3240                            */

#if (FEATURE_ON == FEATURE_LTE)

            /* 当前存在补充业务的CSFB流程，则清空CSFB存在标志 */
            if (NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST == NAS_MML_GetCsfbServiceStatus())
            {
                NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
            }
#endif
        }
        else
        {
            if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                                                          .RcvXXEstReq.ucFlg)
             && (g_MmSsAbortReq.ulTransactionId == g_MmGlobalInfo
                    .ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId))
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                                                 .RcvXXEstReq.ucFlg = MM_FALSE;

#if (FEATURE_ON == FEATURE_LTE)

                /* 当前存在补充业务的CSFB流程，则清空CSFB存在标志 */
                if (NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST == NAS_MML_GetCsfbServiceStatus())
                {
                    NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                    NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
                }
#endif

            }
        }

        NAS_MM_UpdateCsServiceBufferStatusFlg();
    }

    return;
}

VOS_VOID Mm_Cell_S5_E81(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{

    if ( MM_FALSE == Mm_RcvSmsAbortReq( pRcvMsg ) )
    {                                                                           /* 消息检查结果失败                         */
        ;
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        if ( (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg)
          && (g_MmSmsAbortReq.ulTransactionId == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId) )
        {
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg = MM_FALSE;
        }

        NAS_MM_UpdateCsServiceBufferStatusFlg();
    }
    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S9_E81
  FUNCTION : 在WAIT FOR OUTGOING MM CONNECTION状态下收到MMSMS_ABORT_REQ的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇   05-02-01  新版作成
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E81(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{

    if ( MM_FALSE == Mm_RcvSmsAbortReq( pRcvMsg ) )
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        if ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI ==
            g_MmSmsAbortReq.ulTransactionId )
        {                                                                       /* 终止的MM连接建立是正在建立的             */
            Mm_TimerStop( MM_TIMER_T3230 );                                     /* 停T3230                                  */
            Mm_ComMsgCmSvcAbortSnd();
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI =
                NO_MM_CONN_ESTING;                                              /* 清除正在建立的MM连接的标志               */
            g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                g_MmGlobalInfo.ucStaOfRcvXXEstReq;                              /* 返回到接收到建立MM连接请求时的状态       */
            Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );    /* MM连接流程                               */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* 记录迁移之前的状态                       */
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                      */
            /*    " \nMM:STATUS is  WAIT_FOR_NETWORK_COMMAND\r " );             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E81:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAN");
            Mm_TimerStart(MM_TIMER_T3240);                                      /* 启动TIMER3240                            */
        }
        else
        {
            if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                                                          .RcvXXEstReq.ucFlg)
             && (g_MmSsAbortReq.ulTransactionId == g_MmGlobalInfo
                    .ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId))
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                                                 .RcvXXEstReq.ucFlg = MM_FALSE;
            }

            NAS_MM_UpdateCsServiceBufferStatusFlg();
        }
    }

    return;
}


VOS_VOID Mm_Cell_S10_E80(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{

    if ( MM_FALSE == Mm_RcvSsAbortReq( pRcvMsg ) )
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* 消息检查结果成功                         */

        /*lint -e701*/

        if ( 0 != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1]
        /*    & (0x01 << ( g_MmCcAbortReq.ulTransactionId - 8 )))) */
            & (0x01 << ( g_MmSsAbortReq.ulTransactionId - 8 ))))
        {                                                                       /* 终止的MM连接建立是正在建立的             */
            if ( ( ( 0x01 << ( g_MmSsAbortReq.ulTransactionId - 8 ) ) ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1] )
                &&(0 ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0] ) )
            {
                Mm_ComMsgCmSvcAbortSnd();
                g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                               g_MmGlobalInfo.ucStaOfRcvXXEstReq;               /* 返回到接收到建立MM连接请求时的状态       */
                Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );/* MM连接流程                               */
                g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;           /* 记录迁移之前的状态                       */
                Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
                /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                  */
                /*    " \nMM:STATUS is  WAIT_FOR_NETWORK_COMMAND\r " );         */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S10_E80:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
                Mm_TimerStart(MM_TIMER_T3240);                                  /* 启动TIMER3240                            */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1] = 0;
            }
            else
            {
                Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );/* MM连接流程                               */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1]
                    &= ~(VOS_UINT32)(0x01 << ( g_MmSsAbortReq.ulTransactionId - 8 ));
            }

#if (FEATURE_ON == FEATURE_LTE)

            /* 当前存在补充业务的CSFB流程，则清空CSFB存在标志 */
            if (NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST == NAS_MML_GetCsfbServiceStatus())
            {
                NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
            }
#endif

        }
        else
        {
            if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                                                          .RcvXXEstReq.ucFlg)
             && (g_MmSsAbortReq.ulTransactionId == g_MmGlobalInfo
                    .ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId))
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                                                 .RcvXXEstReq.ucFlg = MM_FALSE;

#if (FEATURE_ON == FEATURE_LTE)

                /* 当前存在补充业务的CSFB流程，则清空CSFB存在标志 */
                if (NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST == NAS_MML_GetCsfbServiceStatus())
                {
                    NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                    NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
                }
#endif

            }
        }

        /*lint +e701*/

    }

    NAS_MM_UpdateCsServiceConnStatusFlg();

    NAS_MM_UpdateCsServiceBufferStatusFlg();

    return;
}


VOS_VOID Mm_Cell_S10_E81(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{

    if ( MM_FALSE == Mm_RcvSmsAbortReq( pRcvMsg ) )
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        /*lint -e701*/

        if ( 0 !=
            ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]
            & ( 0x01 << ( g_MmCcAbortReq.ulTransactionId - 8 ) ) ) )
        {                                                                       /* 终止的MM连接建立是正在建立的             */
            if ( ( ( 0x01 << ( g_MmSmsAbortReq.ulTransactionId - 8 ) ) ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1] )
                &&(0 ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0] ) )
            {
                Mm_ComMsgCmSvcAbortSnd();
                g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                               g_MmGlobalInfo.ucStaOfRcvXXEstReq;               /* 返回到接收到建立MM连接请求时的状态       */
                Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );/* MM连接流程                               */
                g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;           /* 记录迁移之前的状态                       */
                Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
                /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                  */
                /*    " \nMM:STATUS is  WAIT_FOR_NETWORK_COMMAND\r " );         */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S10_E81:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
                Mm_TimerStart(MM_TIMER_T3240);                                  /* 启动TIMER3240                            */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                                    aucMMConnExtFlg[1] = 0;
            }
            else
            {
                Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );/* MM连接流程                               */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]
                &= ~(VOS_UINT32)(0x01 << ( g_MmSmsAbortReq.ulTransactionId - 8 ));
            }
        }
        else
        {
            if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                                                          .RcvXXEstReq.ucFlg)
             && (g_MmSmsAbortReq.ulTransactionId ==
             g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.
                                                            ulTransactionId))
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                                                 .RcvXXEstReq.ucFlg = MM_FALSE;
            }
        }

        /*lint +e701*/

    }

    NAS_MM_UpdateCsServiceConnStatusFlg();

    NAS_MM_UpdateCsServiceBufferStatusFlg();

    return;
}


VOS_VOID Mm_Cell_S12_E80(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{

    if ( MM_FALSE == Mm_RcvSsAbortReq( pRcvMsg ) )
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        if ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI ==
            g_MmSsAbortReq.ulTransactionId )
        {
            /* 终止的MM连接建立是正在建立的             */
            if (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucRat == NAS_MML_GetCurrNetRatType())
            {
                Mm_SndRrRelReq(RRC_CELL_UNBARRED);

                g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                    g_MmGlobalInfo.ucStaOfRcvXXEstReq;                              /* 返回到接收到建立MM连接请求时的状态       */
                Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
                Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );    /* MM连接流程                               */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E80:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
                Mm_TimerStart(MM_TIMER_T3240);                                      /* 启动TIMER3240                            */
            }
            else
            {
                Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
            }

            Mm_TimerStop( MM_TIMER_PROTECT_SIGNALLING );
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI =
                NO_MM_CONN_ESTING;                                              /* 清除正在建立的MM连接的标志               */

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg = MM_FALSE;

            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* 记录迁移之前的状态                       */


#if (FEATURE_ON == FEATURE_LTE)

            /* 当前存在补充业务的CSFB流程，则清空CSFB存在标志 */
            if (NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST == NAS_MML_GetCsfbServiceStatus())
            {
                NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
            }
#endif
        }
        else
        {
            if ( ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                                                          .RcvXXEstReq.ucFlg )
             && ( g_MmSsAbortReq.ulTransactionId ==
             g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.
                                                        ulTransactionId ) )
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                                                 .RcvXXEstReq.ucFlg = MM_FALSE;

#if (FEATURE_ON == FEATURE_LTE)

                /* 当前存在补充业务的CSFB流程，则清空CSFB存在标志 */
                if (NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST == NAS_MML_GetCsfbServiceStatus())
                {
                    NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                    NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
                }
#endif

            }

            NAS_MM_UpdateCsServiceBufferStatusFlg();
        }
    }

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S12_E81
  FUNCTION : 在WAIT FOR RR CONNECTION (MM CONNECTION)状态下收到MMSMS_ABORT_REQ的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇   05-02-01  新版作成
*******************************************************************************/
VOS_VOID Mm_Cell_S12_E81(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{

    if ( MM_FALSE == Mm_RcvSmsAbortReq( pRcvMsg ) )
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        if ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI ==
            g_MmSmsAbortReq.ulTransactionId )
        {                                                                       /* 终止的MM连接建立是正在建立的             */
            Mm_SndRrRelReq(RRC_CELL_UNBARRED);
            Mm_TimerStop( MM_TIMER_PROTECT_SIGNALLING );
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI =
                NO_MM_CONN_ESTING;                                              /* 清除正在建立的MM连接的标志               */
            g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                g_MmGlobalInfo.ucStaOfRcvXXEstReq;                              /* 返回到接收到建立MM连接请求时的状态       */
            Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );    /* MM连接流程                               */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* 记录迁移之前的状态                       */
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                      */
            /*    " \nMM:STATUS is  WAIT_FOR_NETWORK_COMMAND\r " );             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E81:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
            Mm_TimerStart(MM_TIMER_T3240);                                      /* 启动TIMER3240                            */
        }
        else
        {
            if ( ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                                                          .RcvXXEstReq.ucFlg )
             && ( g_MmSsAbortReq.ulTransactionId ==
             g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.
                                                            ulTransactionId ) )
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                                                 .RcvXXEstReq.ucFlg = MM_FALSE;
            }

            NAS_MM_UpdateCsServiceBufferStatusFlg();
        }
    }

    return;
}


VOS_VOID Mm_Cell_S16_E80(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{

    if ( MM_FALSE == Mm_RcvSsAbortReq(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        if ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI ==
            g_MmSsAbortReq.ulTransactionId )
        {                                                                       /* 终止的MM连接建立是正在建立的             */
            Mm_TimerStop( MM_TIMER_T3230 );                                     /* 停T3230                                  */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI =
                NO_MM_CONN_ESTING;                                              /* 清除正在建立的MM连接的标志               */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* 记录迁移之前的状态                       */
            Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
            /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                      */
            /*    " \nMM:STATUS is  MM_CONNECTION_ACTIVE\r " );                 */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S16_E80:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
            Mm_ComCheckDelayMmConn( MM_FALSE );                                 /* 检查是否有保留的需要建立的MM连接         */

#if (FEATURE_ON == FEATURE_LTE)

            /* 当前存在补充业务的CSFB流程，则清空CSFB存在标志 */
            if (NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST == NAS_MML_GetCsfbServiceStatus())
            {
                NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
            }
#endif
        }
        else
        {
            if ( ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                                                          .RcvXXEstReq.ucFlg )
             && ( g_MmSsAbortReq.ulTransactionId ==
             g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.
                                                        ulTransactionId ) )
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                                                 .RcvXXEstReq.ucFlg = MM_FALSE;

#if (FEATURE_ON == FEATURE_LTE)

                /* 当前存在补充业务的CSFB流程，则清空CSFB存在标志 */
                if (NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST == NAS_MML_GetCsfbServiceStatus())
                {
                    NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                    NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
                }
#endif
            }

            NAS_MM_UpdateCsServiceBufferStatusFlg();
        }
    }

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S16_E81
  FUNCTION : 在WAIT FOR ADDITIONAL OUTGOING MM CONNECTION状态下
             收到MMSMS_ABORT_REQ的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇   05-02-01  新版作成
*******************************************************************************/
VOS_VOID Mm_Cell_S16_E81(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{

    if ( MM_FALSE == Mm_RcvSmsAbortReq(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        if ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI ==
            g_MmSmsAbortReq.ulTransactionId )
        {                                                                       /* 终止的MM连接建立是正在建立的             */
            Mm_TimerStop( MM_TIMER_T3230 );                                     /* 停T3230                                  */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI =
                NO_MM_CONN_ESTING;                                              /* 清除正在建立的MM连接的标志               */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* 记录迁移之前的状态                       */
            Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
            /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                      */
            /*    " \nMM:STATUS is  MM_CONNECTION_ACTIVE\r " );                 */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S16_E81:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
            Mm_ComCheckDelayMmConn( MM_FALSE );                                 /* 检查是否有保留的需要建立的MM连接         */
        }
        else
        {
            if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                                                          .RcvXXEstReq.ucFlg)
             && (g_MmSsAbortReq.ulTransactionId == g_MmGlobalInfo
                    .ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId))
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                                                 .RcvXXEstReq.ucFlg = MM_FALSE;
            }

            NAS_MM_UpdateCsServiceBufferStatusFlg();
        }
    }

    return;
}


/*******************************************************************************
  MODULE   : Mm_Cell_S16_E66
  FUNCTION : 在WAIT FOR ADDITIONAL OUTGOING MM CONNECTION状态下收到MMSS_REL_REQ的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇    2005.03.28  新版作成
*******************************************************************************/
VOS_VOID Mm_Cell_S16_E66(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{
    if ( MM_FALSE == Mm_RcvSsRelReq(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        /*lint -e701*/
        if ( ( MM_CONST_NUM_7 > g_MmSsRelReq.ulTi ) &&
            ( MM_CONST_NUM_0 !=
            ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0]
            & ( 0x01 << g_MmSsRelReq.ulTi ) ) ) )
        {                                                                       /* TI小于7并且该MM连接存在                  */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0] &=
                ~(VOS_UINT32)( 0x01 << g_MmSsRelReq.ulTi );                          /* 清除该标志位                             */
        }
        if ( ( MM_CONST_NUM_7 < g_MmSsRelReq.ulTi ) &&
            ( MM_CONST_NUM_15 > g_MmSsRelReq.ulTi ) &&
            ( MM_CONST_NUM_0 !=
            ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1]
            & ( 0x01 << ( g_MmSsRelReq.ulTi - 8 ) ) ) ) )
        {                                                                       /* TI小于7并且该MM连接存在                  */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1] &=
                ~(VOS_UINT32)( 0x01 << ( g_MmSsRelReq.ulTi - 8 ) );                  /* 清除该标志位                             */
        }
        if ( ( MM_TRUE ==
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg )
                && ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                RcvXXEstReq.ulTransactionId == g_MmSsRelReq.ulTi ) )
        {
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg
                = MM_FALSE;                                                     /* 设置不存在缓存的MM连接 */
        }
        if ( ( MM_CONST_NUM_0 ==
          g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0] )
          && ( MM_CONST_NUM_0 ==
          g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] )
          && ( MM_CONST_NUM_0 ==
          g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0] )
          && ( MM_CONST_NUM_0 ==
          g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1] )
          && ( MM_CONST_NUM_0 ==
          g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0] )
          && ( MM_CONST_NUM_0 ==
          g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]) )
        {                                                                       /* 没有MM连接存在                           */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* 记录迁移之前的状态                       */
            Mm_ComSetMmState(WAIT_FOR_OUTGOING_MM_CONNECTION);
            /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                      */
            /*    " \nMM:STATUS is  WAIT_FOR_OUTGOING_MM_CONNECTION\r " );      */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S16_E66:NORMAL: STATUS is WAIT_FOR_OUTGOING_MM_CONNECTION");
        }

        NAS_MM_UpdateCsServiceConnStatusFlg();

        NAS_MM_UpdateCsServiceBufferStatusFlg();

        /*lint +e701*/
    }

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S27_E82
  FUNCTION : 在PROCESS CM SERVICE PROMPT状态下
             收到MM_TIMER_PROTECT_CCBS EXPIRED的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇    2005.04.14  新版作成
     2.
*******************************************************************************/
VOS_VOID Mm_Cell_S27_E82(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{
    MM_MSG_MM_STATUS_STRU          MsgMmStatus;                                 /* MM STATUS 消息结构体                     */
    /*WUEPS_TRACE( MM_LOG_LEVEL_6, " \nMM:MM_TIMER_PROTECT_CCBS EXPIRED\r " );  */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S27_E82:INFO: MM_TIMER_PROTECT_CCBS EXPIRED");
    MsgMmStatus.MmIeRjctCause.ucRejCause = NAS_MML_REG_FAIL_CAUSE_SERV_OPT_OUT_OF_ORDER;  /* Service option temporarily out of order  */
    Mm_ComMsgMmStatusSnd( &MsgMmStatus );                                       /* 填充并发送 MM STATUS 消息                */

    if ( MM_FALSE == Mm_ComMmConnExist( ) )
    {                                                                           /* 没有存在的MM连接 */
        g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = g_MmGlobalInfo.
            ucStaOfRcvXXEstReq;                                                 /* 进入空闲的状态                           */
        Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );        /* MM连接流程                               */
        g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                   /* 记录迁移之前的状态                       */
        Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
        /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                          */
        /*    " \nMM:STATUS is  WAIT_FOR_NETWORK_COMMAND\r " );                 */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S27_E82:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
        Mm_TimerStart(MM_TIMER_T3240);                                          /* 启动TIMER3240                            */
    }
    else
    {                                                                           /* 有存在的MM连接 */
        Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
        /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                          */
        /*    " \nMM:STATUS is  MM_CONNECTION_ACTIVE\r " );                     */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S27_E82:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
    }
}



/* Mm_Cell_S27_E33_Handling_REL_CAUSE_NOT_RL_FAILURE不再使用，删除 */


/* 删除S27E33 */




VOS_VOID Mm_Cell_S9_E83(VOS_VOID *pRcvMsg)
{
    GRRMM_EST_SAPI3_CNF_ST             *pstEstSapi3Cnf;

    NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_NORMAL,
                    "Mm_Cell_S9_E83:STATE: WAIT_FOR_OUTGOING_MM_CONNECTION Receive GRRMM_EST_SAPI3_CNF.");

    /* 消息检查 */
    if (MM_IE_PD_SMS_MSG != g_MmGlobalInfo.ucMMConnEstingPD)
    {
        NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_WARNING,
                    "Mm_Cell_S9_E83: WARNING: Receive GRRMM_EST_SAPI3_CNF error.");

        return;
    }

    /* 消息检查结果成功 */
    pstEstSapi3Cnf = (GRRMM_EST_SAPI3_CNF_ST*)pRcvMsg;

    Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);  /* 停止保护TIMER */

    if (MM_EST_SAPI3_SUCCESS == pstEstSapi3Cnf->ucResult)
    {
        /* 该MM连接建立成功 */
        Mm_SndSmsEstCnf(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI);
        /*lint -e701*/
        /* TI 小于7 */
        if (MM_CONST_NUM_7 >
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI)
        {
            /* 设置MM连接存在标志 */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0]   |=
                (VOS_UINT8)(0x01 << g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI);
        }
        else /*TI大于7 */
        {
            /* 设置 MM 连接存在标志 */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]   |=
                (VOS_UINT8)(0x01 << (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI - 8 ) );
        }
        /*lint +e701*/
        g_MmGlobalInfo.ucPreState       = g_MmGlobalInfo.ucState;  /* 记录迁移之前的状态               */
        Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E83:NORMAL: STATUS is MM_CONNECTION_ACTIVE");

        g_MmGlobalInfo.ucMMConnEstingPD     = NO_MM_CONN_ESTING;       /* 设置没有正在建立的连接           */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI
                                            = NO_MM_CONN_ESTING;
        Mm_ComCheckDelayMmConn(MM_FALSE);                          /* 检查是否有保留的需要建立的MM连接 */

        NAS_MM_UpdateCsServiceConnStatusFlg();

        return;
    }
    else /* SAPI3 建立失败 */
    {
        /* 通知 SMS, MM 连接建立失败 */
        Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI,
                        NAS_MMCM_REL_CAUSE_MM_INTER_ERR_EST_SAPI3_FAIL);

        Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);

        NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_ERROR,
                    "Mm_Cell_S9_E83: ERROR: SAPI3 est fail.");
    }

    g_MmGlobalInfo.ucMMConnEstingPD     = NO_MM_CONN_ESTING;       /* 设置没有正在建立的连接           */

    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI
                                        = NO_MM_CONN_ESTING;

    NAS_MM_UpdateCsServiceConnStatusFlg();

    return;
}

VOS_VOID Mm_Cell_S6_E86(VOS_VOID *pRcvMsg)
{
    GAS_RR_CHAN_MOD_IND_ST   *pChanMod;
    MMCC_CHANNEL_MODE_ENUM_U32        enMmCcChanMode;

    pChanMod = (GAS_RR_CHAN_MOD_IND_ST *)pRcvMsg;

    /* 对于GSM，以下参数忽略，初始化为默认值 */
    g_RrMmSyncInd.ulRabCnt = 1;
    g_RrMmSyncInd.NasSyncInfo[0].ulRabId = 0;
    g_RrMmSyncInd.NasSyncInfo[0].ulCnDomainId = 0;
    g_RrMmSyncInd.ulReason = MMCC_GSM_RES_ASSIGNED;
    g_RrMmSyncInd.NasSyncInfo[0].ulRabSyncInfo = 0;

    enMmCcChanMode = MM_ComGetChanMode(pChanMod->enChanMod);
    if(MMCC_CHAN_MOD_SIG_ONLY == enMmCcChanMode)
    {
        NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_WARNING,
                        "Mm_Cell_S6_E86:  Receive GAS_RR_CHAN_MOD_IND, parameter is error.");
    }

    g_RrMmSyncInd.ulChannelMode = enMmCcChanMode;

    g_MmGlobalInfo.ucGasRrChanIndMsgValidFlg = VOS_TRUE;

    Mm_SndCcSyncInd();
}


VOS_VOID NAS_MM_ProcInterRatReselInLuProcedure(VOS_VOID)
{
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8               enCsUpdateStatus;
    MM_LAI_STRU                                            *pstAttLaiInfo   = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                                       *pstCampLaiInfo  = VOS_NULL_PTR;

    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
    Mm_TimerStop(MM_TIMER_T3210);

    if (NAS_MML_MS_MODE_PS_ONLY == NAS_MML_GetMsMode())
    {
        /*迁移状态到limit service*/
        /*设置标志Attach not allow*/
        /*指示上层业务失败*/
        Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S23_E33:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
        Mm_ComCheckDelayMmConn(MM_FALSE);

        return;
    }

    g_MmGlobalInfo.LuInfo.ucLuAttmptCnt++;

    if (g_MmGlobalInfo.LuInfo.ucLuAttmptCnt < MM_CONST_NUM_4)
    {
        enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
        if ( (VOS_FALSE == NAS_MML_IsCsLaiChanged())
         &&  (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus))
        {
            g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_MM_ProcInterRatReselInLuProcedure:INFO: MmServiceState is MM_NORMAL_SERVICE");

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_RR_CONN_FAIL);                    /* 向MMC发送MMCMM_LU_RESULT_IND             */
            NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_RR_CONN_FAIL);                    /* 向MMC发送MMCMM_LU_RESULT_IND             */
            Mm_ComNasInfoSav(MM_STATUS_ATTACHED,
                             NAS_MML_GetSimCsSecurityCksn());
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* 记录前状态                               */
            Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "NAS_MM_ProcInterRatReselInLuProcedure:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
            Mm_TimerStop(MM_TIMER_T3211);
            Mm_TimerStart(MM_TIMER_T3211);                                      /* 启动T3211                                */

            g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_FALSE;

        }
        else
        {
            g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_MM_ProcInterRatReselInLuProcedure:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_RR_CONN_FAIL);

            NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_RR_CONN_FAIL);

            /* 进U2的公共处理 */
            Mm_ComToU2Handle();

            Mm_TimerStop(MM_TIMER_T3211);
            Mm_TimerStart(MM_TIMER_T3211);                                      /* 启动T3211                                */
        }
    }
    else
    {
        g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_MM_ProcInterRatReselInLuProcedure:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");

        /* 在U2状态，保存当前的LAI信息 */
        pstAttLaiInfo   = NAS_MM_GetAttemptUpdateLaiInfo();
        pstCampLaiInfo  = NAS_MML_GetCurrCampLai();

        pstAttLaiInfo->PlmnId.ulMcc = pstCampLaiInfo->stPlmnId.ulMcc;
        pstAttLaiInfo->PlmnId.ulMnc = pstCampLaiInfo->stPlmnId.ulMnc;
        pstAttLaiInfo->ulLac        = ((pstCampLaiInfo->aucLac[0] << 8)| (pstCampLaiInfo->aucLac[1]));

        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    NAS_MML_REG_FAIL_CAUSE_RR_CONN_FAIL);

        NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                 NAS_MML_REG_FAIL_CAUSE_RR_CONN_FAIL);

        /* 进U2的公共处理 */
        Mm_ComToU2Handle();

        Mm_TimerStop(MM_TIMER_T3212);                                           /* T3212先进行停止                                */
        NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
    }

    NAS_MM_ProcDelayService();

    if ((VOS_FALSE  == NAS_MM_IsNeedGmmProcUserDetach())
     && (MM_WAIT_CS_DETACH == (g_MmGlobalInfo.stDetachInfo.enDetachType & MM_WAIT_CS_DETACH)))
    {
        NAS_MM_LocalDetach();
    }

    return;
}


VOS_VOID NAS_MM_ProcDelayService(VOS_VOID)
{
    VOS_UINT8                                   ucRrConnRelFlg;
    VOS_UINT8                                   ucTiValidFlg;

    ucRrConnRelFlg = Mm_ComRrConnRelChk();
    if (MM_TRUE == ucRrConnRelFlg)
    {
        Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                           /* RR连接不存在                             */
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
    }
    else
    {
        ucTiValidFlg = Mm_ComTiChk();
        if (MM_FALSE == ucTiValidFlg)
        {
            Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                       /* RR连接不存在                             */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }
        else
        {
            Mm_ComSigRelForDelayMmConnRej();
        }
        Mm_ComCheckDelayMmConn(MM_FALSE);
    }

    return;
}


VOS_VOID Mm_Cell_S2_E15(
    VOS_VOID                           *pRcvMsg
)
{
    GMMMM_LU_INITIATION_STRU           *pstMmcLuIni = VOS_NULL_PTR;

    if (MM_FALSE == Mm_RcvGmmLuIni(pRcvMsg))
    {
        return;
    }

    pstMmcLuIni = ( GMMMM_LU_INITIATION_STRU* )pRcvMsg;

    if ( GMMMM_T3312_EXPIRED == pstMmcLuIni->enTimerExpiredFlg )
    {
        g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_TRUE;
    }
}




VOS_VOID Mm_Cell_S3_E54(VOS_VOID* pMsg)
{
    VOS_UINT32                          ulIsTestCard;

    ulIsTestCard    = NAS_USIMMAPI_IsTestCard();
    if (VOS_TRUE == ulIsTestCard)
    {
        return;
    }

    /* LTE下不能发起LAU */
    if (NAS_MML_NET_RAT_TYPE_LTE != NAS_MML_GetCurrNetRatType())
    {
        /* 发起LAU */
        Mm_ComLuOnly();
    }

    return;
}

/*lint -restore */

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
