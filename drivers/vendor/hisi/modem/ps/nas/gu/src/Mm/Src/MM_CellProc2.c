

#include        "MM_Inc.h"
#include        "GmmMmInterface.h"
#include        "NasMmcProcNvim.h"
#include        "MM_Ext.h"
#include        "NasMmEcall.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人:luojian 107747;检视人:sunshaohua65952;原因:LOG方案设计需要*/
#define    THIS_FILE_ID        PS_FILE_ID_MM_CELLPROC2_C
/*lint +e767 修改人:luojian 107747;检视人:sunshaohua*/

/*lint -save -e958 */



VOS_VOID Mm_Cell_S3_E13(VOS_VOID *pMsg)
{
    GMMMM_NETWORK_DETACH_IND_STRU      *pstNetWkDetachInd;


    if (MM_FALSE == NAS_MM_RcvGmmNetworkDetechInd(pMsg))
    {
        return;

    }

    if (NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode())
    {
    }

    pstNetWkDetachInd = (GMMMM_NETWORK_DETACH_IND_STRU*)pMsg;

    if (VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNtMod))
    {                                                                           /* 如果为A+I,且不是类似B或A+II处理的场合    */
        if (GMMMM_NET_DETACH_REATTACH == pstNetWkDetachInd->enDetachType)
        {
            NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
        }
        else if (GMMMM_NET_DETACH_IMSI == pstNetWkDetachInd->enDetachType)
        {
            Mm_ComSaveProcAndCauseVal(MM_NET_DETACH_PROC,
                                      NAS_MML_REG_FAIL_CAUSE_NTDTH_IMSI);       /* 记录流程和原因值                         */

            g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;          /* 设置服务状态                             */
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* 记录前状态                               */
            Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S3_E13:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");

            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                                    ~MM_MS_ID_TMSI_PRESENT;     /* 清除标志位                               */
            NAS_MML_InitUeIdTmsiInvalid();
            Mm_ComDelLai();                                                     /* 删除LAI                                  */
            Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                             MM_CKSN_INVALID);
            if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
            {
                Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
                Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKC_ID);               /* 更新SIM卡更新状态                        */
            }
            else
            {
                Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
                Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYS_ID);            /* 更新SIM卡更新状态                        */
            }



            Mm_ComProcCauseClear();
        }
        else
        {
            Mm_ComNetDetachCauseHandle(
                (VOS_UINT8)pstNetWkDetachInd->ulDetachCause);                     /* 调用DETACH原因值的公共处理               */
        }
    }
    else
    {                                                                           /* 如果为非A+I模式                          */
        if (GMMMM_NET_DETACH_REATTACH == pstNetWkDetachInd->enDetachType)
        {
            NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
        }
        else if (GMMMM_NET_DETACH_IMSI == pstNetWkDetachInd->enDetachType)
        {
            Mm_ComSaveProcAndCauseVal(MM_NET_DETACH_PROC,
                                      NAS_MML_REG_FAIL_CAUSE_NTDTH_IMSI);                 /* 记录流程和原因值                         */

            g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;          /* 设置服务状态                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S3_E13:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");

            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* 记录前状态                               */
            Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                                    ~MM_MS_ID_TMSI_PRESENT;     /* 清除标志位                               */
            NAS_MML_InitUeIdTmsiInvalid();
            Mm_ComDelLai();                                                     /* 删除LAI                                  */
            Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                             MM_CKSN_INVALID);

            if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
            {
                Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
                Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKC_ID);               /* 更新SIM卡更新状态                        */
            }
            else
            {
                Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
                Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYS_ID);            /* 更新SIM卡更新状态                        */
            }



            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E13:NORMAL: STATUS is MM_IDLE_ATTEMPTING_TO_UPDATE");
            Mm_ComProcCauseClear();
        }
        else
        {
            Mm_ComNetDetachCauseHandle(
                (VOS_UINT8)pstNetWkDetachInd->ulDetachCause);                     /* 调用DETACH原因值的公共处理               */
        }
    }
}


VOS_VOID Mm_Cell_S3_E15(VOS_VOID *pMsg)
{
    GMMMM_LU_INITIATION_STRU    *pstMmcLuIni;

    if (MM_FALSE == Mm_RcvGmmLuIni(pMsg))
    {
        return;
    }

    pstMmcLuIni = (GMMMM_LU_INITIATION_STRU*)pMsg;

    if(  (GMMMM_NO_TIMER_EXPIRED == pstMmcLuIni->enTimerExpiredFlg)
       &&(VOS_FALSE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg))
    {
        return;                                                              /*非定时器超时引起的LU请求都是当LAI没改变时为了去除Gs关联。 */
    }

    if ((VOS_FALSE == NAS_MML_GetPsRestrictRegisterFlg())
     && ((GMMMM_T3312_EXPIRED == pstMmcLuIni->enTimerExpiredFlg)
      || (GMMMM_T3412OrT3423_EXPIRED == pstMmcLuIni->enTimerExpiredFlg)))
    {
        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_PERIODIC_UPDATING;        /* 设置LU类型为周期                         */
    }
    else
    {
        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;                /* 设置LU类型为NORMAL                       */
    }

    Mm_ComLuOnly();                                                          /* 进行LU过程                               */

    return;
}

/*******************************************************************************
  Module:   Mm_Cell_S3_E16
  Function: 在MM IDLE NORMAL SERVICE状态下收到
            GMMMM_AUTHENTICATON_FAILURE_IND的处理
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2003.12.09  新版做成
*******************************************************************************/
VOS_VOID Mm_Cell_S3_E16(VOS_VOID *pMsg)
{
    VOS_UINT8 ucCause;

    if (MM_FALSE == Mm_RcvGmmAuthFailInd(pMsg))
    {
        return;
    }

    if (LOCATION_UPDATING_INITIATED == g_MmGlobalInfo.ucState)
    {
        ucCause = NAS_OM_MM_CAUSE_AUT_NETWORK_REJECT;
        NAS_EventReport(WUEPS_PID_MM, NAS_OM_EVENT_LOCATION_UPDATE_FAILURE,
                        &ucCause, NAS_OM_EVENT_LAU_FAIL_LEN);
    }
    Mm_ComAuthenRcvAuthenRej();                                                 /* 调用鉴权失败的公共处理                   */

    NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_AUTH_REJ);

    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                MM_MMC_LU_RESULT_FAILURE,
                                NAS_MML_REG_FAIL_CAUSE_AUTH_REJ);
}


VOS_VOID Mm_Cell_S3_E17(VOS_VOID *pMsg)
{
    if (MM_FALSE == Mm_RcvGmmCombinedRauInitiation(pMsg))
    {
        return;
    }
    NAS_MML_SetDelayedCsfbLauFlg(VOS_FALSE);

    if (VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
    {
        return;
    }

    /* 因为MM_WAIT_FOR_ATTACH为暂态,如果此时保存,当联合注册失败时,
       会恢复到注册前的状态,此时恢复到MM_WAIT_FOR_ATTACH会影响业务 */
    if (MM_WAIT_FOR_ATTACH != g_MmGlobalInfo.ucState)
    {
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                         /* 记录前状态                               */
    }
    Mm_ComSetMmState(LOCATION_UPDATING_PENDING);

    g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_FALSE;


    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E17:NORMAL: STATUS is  LOCATION_UPDATING_PENDING");
}

/*******************************************************************************
  Module:   Mm_Cell_S17_E17
  Function: 在LOCATION UPDATING PENDING状态下收到GMMMM_COMBINED_RAU_INITIATION的处理
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  欧阳飞      2009.03.11   新版做成
*******************************************************************************/
VOS_VOID Mm_Cell_S17_E17(VOS_VOID *pMsg)
{
    /* 在GSM下，如果原来收到COMBINED_RAU_ACCEPTED with PS ONLY ACCEPTED, 5次失败后MM会启定时器MM_TIMER_DELAY_LU_GSM
       延迟1秒发起LU, 如果此时又收到GMM的联合注册开始消息，需先停掉该定时器，避免同时发起RAU和LU */
    Mm_TimerStop(MM_TIMER_DELAY_LU_GSM);
}




VOS_VOID Mm_Cell_S4_E5(VOS_VOID *pMsg)
{
    VOS_UINT8                           ucLaChgFlg = VOS_FALSE;
    VOS_UINT8                           ucUserSpecificSearchFLg;
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulCsfbExistFlag;

    /* 取得CSFB是否存在的标志 */
    ulCsfbExistFlag         = NAS_MML_IsCsfbServiceStatusExist();
#endif

    if (VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
    {
        NAS_MM_ProcMmcMmSysInfoInd_CsAttachNotAllow();

        return;
    }

    if (VOS_TRUE == NAS_MM_IsCsForbidden())
    {
        NAS_MM_ProcCsForbidenFlg_RcvSysInfoInd(g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg);

        return;
    }

    if (VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg())
    {
        NAS_MM_ProcMmcMmSysInfoInd_CsRegisterRestrict();

        return;
    }

    ucUserSpecificSearchFLg = Mm_Get_UserSpecificSearchFlg_From_SysInfo(pMsg);

    ucLaChgFlg = NAS_MML_IsCsLaiChanged();


    if ((VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNewNtMod))
#if  (FEATURE_ON == FEATURE_LTE)
     && (VOS_FALSE == ulCsfbExistFlag)
#endif
     )
    {                                                                           /* 如果为A+I,且不是类似B或A+II处理的场合    */
        g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;

        /* RAC为0的场合 */
        if ((MM_UNSUPPORT_GPRS == g_MmGlobalInfo.usRac)
         || (MMCMM_FORBIDDEN_PLMN_FOR_GPRS == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
        {
            NAS_MM_SetLikeBFlg();
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S4_E5:INFO: MmLikeB is MM_TRUE");

            if ((VOS_TRUE == NAS_MML_IsCampLaiInfoChanged())
             || (VOS_TRUE == ucUserSpecificSearchFLg))
            {
                /* LAI改变,或者用户发起的指定搜网时,发起LU过程 */
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;       /* 设置LU类型                               */
                Mm_ComLuOnly();                                             /* LU REQ                                   */
            }
        }
    }
    else
    {                                                                           /* 非A+I模式                                */
#if (FEATURE_ON == FEATURE_LTE)
        if (VOS_TRUE == NAS_MM_RcvSysInfoSurpportLte_PreProc())
        {
            return;
        }
#endif

        if (g_MmGlobalInfo.ucNtMod == g_MmGlobalInfo.ucNewNtMod)
        {
            if ((NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == NAS_MML_GetCsUpdateStatus())
                && (MM_TRUE == g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg)
                && (VOS_FALSE == ucLaChgFlg))
            {
                g_MmGlobalInfo.LuInfo.ucLuType =
                                MM_IE_LUT_PERIODIC_UPDATING;            /* 设置LU类型                               */
                Mm_ComLuOnly();                                         /* 发送LU REQ                               */
            }
            else if ( (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == NAS_MML_GetCsUpdateStatus())
                   && (VOS_FALSE == ucLaChgFlg))
            {
                if ((MM_TRUE == g_MmGlobalInfo.ucPowerOnFlg)
                 && (MM_ATT_NEED == g_MmGlobalInfo.ucAttFlg))
                {
                    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_IMSI_ATTACH;
                    Mm_ComLuOnly();
                }
                else if (VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
                {
                    g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;
                    Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL,
                           "Mm_Cell_S4_E5:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");


                    Mm_SndRrNasInfoChgReq(MM_NAS_INFO_SYNC_AS_FLG);


                    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                MM_MMC_LU_RESULT_SUCCESS,
                                                NAS_MML_REG_FAIL_CAUSE_NULL);
                }
                else
                {
                }
            }
            else if ((VOS_FALSE        == NAS_MML_IsCampLaiInfoChanged())
                  && (MM_TIMER_RUNNING == gstMmTimer[MM_TIMER_T3212].ucTimerStatus)
                  && (VOS_FALSE        == ucUserSpecificSearchFLg))
            {
                /* 当前驻留小区与上次驻留小区相同，并且T3212正在运行，此时不需要发起LAU，等T3212超时后发起 */
                Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);


                Mm_SndRrNasInfoChgReq(MM_NAS_INFO_SYNC_AS_FLG);


                /* 上报注册失败,保证服务状态的正确性 */
                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                            MM_MMC_LU_RESULT_FAILURE,
                                            NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);

                NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                         NAS_MML_REG_FAIL_CAUSE_NULL);
            }
            else
            {
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;   /* 设置LU类型                               */
                Mm_ComLuOnly();                                         /* 发送LU REQ                               */
            }
        }
        else
        {
            Mm_ComNetModeChange();
        }
    }

}


VOS_VOID Mm_Cell_S4_E15(VOS_VOID *pMsg)
{
    GMMMM_LU_INITIATION_STRU            *pstLuIniMsg;

    pstLuIniMsg  = (GMMMM_LU_INITIATION_STRU *)pMsg;

    if (MM_FALSE == Mm_RcvGmmLuIni(pMsg))
    {
        return;

    }

    if (GMMMM_T3412OrT3423_EXPIRED == pstLuIniMsg->enTimerExpiredFlg)
    {
        /* 设置LU类型为周期 */
        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_PERIODIC_UPDATING;
    }
    else
    {
        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;                       /* 设置LU类型为NORMAL                       */
    }

    Mm_ComLuOnly();                                                             /* 进行LU过程                               */
}


VOS_VOID Mm_Cell_S6_E15(VOS_VOID *pMsg)
{
    GMMMM_LU_INITIATION_STRU    *pstMmcLuIni;

    if (MM_FALSE == Mm_RcvGmmLuIni(pMsg))
    {
        return;

    }

    pstMmcLuIni = (GMMMM_LU_INITIATION_STRU*)pMsg;

    if ((VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg())
        && (GMMMM_T3312_EXPIRED == pstMmcLuIni->enTimerExpiredFlg) )
    {
        g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_TRUE;
    }

    return;
}


VOS_VOID Mm_Cell_S5_E5(VOS_VOID *pMsg)
{
    VOS_UINT32                          ucLaChgFlg;

    VOS_UINT8                           ucUserSpecificSearchFlg;
    VOS_UINT32                          ul3211Status;

    VOS_UINT32                          ulT3213Status;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                                              ulCsfbExistFlag;
    VOS_UINT32                          ulIsTestCard;

    ulIsTestCard    = NAS_USIMMAPI_IsTestCard();

    /* 取得CSFB是否存在的标志 */
    ulCsfbExistFlag     = NAS_MML_IsCsfbServiceStatusExist();

#endif

    if (VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
    {
        NAS_MM_ProcMmcMmSysInfoInd_CsAttachNotAllow();

        return;
    }

    if (VOS_TRUE == NAS_MM_IsCsForbidden())
    {
        NAS_MM_ProcCsForbidenFlg_RcvSysInfoInd(g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg);

        return;
    }

    if (VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg())
    {
        NAS_MM_ProcMmcMmSysInfoInd_CsRegisterRestrict();

        return;
    }



    ul3211Status = NAS_MM_QryTimerStatus(MM_TIMER_T3211);


    ulT3213Status = NAS_MM_QryTimerStatus(MM_TIMER_T3213);

    ucUserSpecificSearchFlg = Mm_Get_UserSpecificSearchFlg_From_SysInfo(pMsg);

    ucLaChgFlg   = NAS_MML_IsCsLaiChanged();

    if (VOS_TRUE == NAS_MML_IsCampLaiInfoChanged())
    {
        g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;
        g_MmGlobalInfo.LuInfo.ucImmAccRejLuAttmptCnt = 0;
        g_MmGlobalInfo.LuInfo.ucT3213AttmptCnt = 0;
    }

    if ( (MM_TIMER_RUNNING == NAS_MM_QryTimerStatus(MM_TIMER_T3213))
      && (MM_TRUE == g_MmGlobalInfo.MsCsInfo.ucCellChgFlg) )
    {
        /* 如果小区信息改变，则清除建链失败原因值，在T3213定时器超时时，发起LAU */
        NAS_MM_SetEstCnfResult(RRC_NAS_EST_RESULT_BUTT);
    }

    if ((VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNewNtMod))
     && (MM_FALSE == g_MmGlobalInfo.ucLikeNetmode2)
#if  (FEATURE_ON == FEATURE_LTE)
     && (VOS_FALSE == ulCsfbExistFlag)
#endif
       )
    {                                                                           /* 如果为A+I,且不是类似B或A+II处理的场合    */
        g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;

        if ( (VOS_TRUE == NAS_MML_GetPsRestrictRegisterFlg())
          || (MM_UNSUPPORT_GPRS == g_MmGlobalInfo.usRac)
          || (MMCMM_FORBIDDEN_PLMN_FOR_GPRS == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
        {                                                                       /* RAC为0的场合                             */
            NAS_MM_SetLikeBFlg();

            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S5_E5:INFO: MmLikeB is MM_TRUE");

            if ((VOS_TRUE       == NAS_MML_IsCampLaiInfoChanged())
             || ((VOS_TRUE      == ucUserSpecificSearchFlg)
              && (MM_TIMER_STOP == ul3211Status)))
            {
                /* LAI发生改变,或者用户指定搜网时,强制执行LU过程 */
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;       /* 设置LU类型                               */
                Mm_ComLuOnly();                                             /* LU REQ                                   */
            }
            else if ((MM_TRUE == g_MmGlobalInfo.LuInfo.ucRetryFlg)
                   &&(MM_TRUE == g_MmGlobalInfo.MsCsInfo.ucCellChgFlg))
            {
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;       /* 设置LU类型                               */
                Mm_ComLuOnly();                                             /* 发送LU REQ                               */
                g_MmGlobalInfo.MsCsInfo.ucCellChgFlg = MM_FALSE;
            }
            else if (VOS_TRUE == NAS_MML_GetDelayedCsfbLauFlg())
            {
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;       /* 设置LU类型                               */
                Mm_ComLuOnly();                                             /* LU REQ                                   */
            }
            else
            {
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;       /* 设置LU类型                               */
                if (VOS_FALSE == g_MmGlobalInfo.ucRetryLauFlg)
                {
                    /* 向MMC发送CS注册结果,当PS注册失败，假流程需要给MMC上报原因值为OTHER CAUSE */
                    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                MM_MMC_LU_RESULT_FAILURE,
                                                NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);          /* 向MMC发送MMCMM_LU_RESULT_IND,使MMC迁移状态 */
                    NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                             NAS_MML_REG_FAIL_CAUSE_NULL);                    /* 向MMC发送MMCMM_LU_RESULT_IND,使MMC迁移状态 */
                }

            }
        }
        else
        {                                                                       /* RAC不等于零                              */
            /*stop T3211*/
            Mm_TimerStop(MM_TIMER_T3211);
            g_MmGlobalInfo.LuInfo.ucImmAccRejLuAttmptCnt = 0;
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt          = 0;
        }
    }
    else
    {                                                                           /* 非A+I                                    */
#if (FEATURE_ON == FEATURE_LTE)
        if (VOS_TRUE == NAS_MM_RcvSysInfoSurpportLte_PreProc())
        {
            return;
        }
#endif

        if (g_MmGlobalInfo.ucNtMod != g_MmGlobalInfo.ucNewNtMod)
        {
            Mm_TimerStop(MM_TIMER_T3211);
            Mm_ComNetModeChange();
        }
        else if((NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == NAS_MML_GetCsUpdateStatus())
             && (VOS_FALSE                              == ucLaChgFlg))
        {
            Mm_ComSysInfoHandleWithLaiNoChange(0);
            if (VOS_TRUE == ulIsTestCard)
            {
                Mm_TimerStop(MM_TIMER_T3213);
            }
        }
        else if ((VOS_TRUE == NAS_MML_IsCampLaiInfoChanged())
              || ((VOS_TRUE      == ucUserSpecificSearchFlg)
               && (MM_TIMER_STOP == ul3211Status)))
        {
            /* LAI发生改变,或者用户指定搜网时,强制执行LU过程 */
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;
            Mm_ComLuOnly();
        }
        else if ((MM_TRUE == g_MmGlobalInfo.LuInfo.ucRetryFlg)
            && (MM_TRUE == g_MmGlobalInfo.MsCsInfo.ucCellChgFlg))
        {
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;           /* 设置LU类型                               */
            Mm_ComLuOnly();                                                 /* 发送LU REQ                               */
            g_MmGlobalInfo.MsCsInfo.ucCellChgFlg = MM_FALSE;
        }
        else
        {
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;

            if (VOS_FALSE == g_MmGlobalInfo.ucRetryLauFlg)
            {
                /* 向MMC发送CS注册结果,当PS注册失败，假流程需要给MMC上报原因值为OTHER CAUSE */
                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                            MM_MMC_LU_RESULT_FAILURE,
                                            NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);                 /* 向MMC发送MMCMM_LU_RESULT_IND,使MMC迁移状态 */
                NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                         NAS_MML_REG_FAIL_CAUSE_NULL);                    /* 向MMC发送MMCMM_LU_RESULT_IND,使MMC迁移状态 */
            }

        }

        /* 链路释放后需重新发起LAU,并且在收到sysinfo后没有发起LAU */
        if ((VOS_TRUE == g_MmGlobalInfo.ucRetryLauFlg)
            && (WAIT_FOR_RR_CONNECTION_LOCATION_UPDATING != g_MmGlobalInfo.ucState))
        {
            Mm_ComLuOnly();
        }

    }

    NAS_MM_ProcT3213AttemptCounter(ulT3213Status);

    /* 标志复位 */
    g_MmGlobalInfo.ucRetryLauFlg = VOS_FALSE;

    Mm_DealWithBuffMsg();

}


VOS_VOID Mm_Cell_S6_E5(VOS_VOID *pMsg)
{
    VOS_UINT32                          ulLaiChangeFlag;
    VOS_UINT8                           ucUserSpecificSearchFlg = 0;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulCsfbExistFlag;

    /* 取得CSFB是否存在的标志 */
    ulCsfbExistFlag     = NAS_MML_IsCsfbServiceStatusExist();
#endif



    /* ==>AT2D01490 */
    ulLaiChangeFlag =  NAS_MML_IsCsLaiChanged();
    if ((VOS_TRUE == ulLaiChangeFlag)
        || (g_MmGlobalInfo.MsCsInfo.ucCellChgFlg == MM_TRUE))
    {
        Mm_TimerStop(MM_TIMER_T3211);
    }
    /* <==AT2D01490 */

    if (VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
    {
        NAS_MM_ProcMmcMmSysInfoInd_CsAttachNotAllow();

        return;
    }

    if (VOS_TRUE == NAS_MM_IsCsForbidden())
    {
        NAS_MM_ProcCsForbidenFlg_RcvSysInfoInd(g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg);

        return;
    }

    if (VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg())
    {
        NAS_MM_ProcMmcMmSysInfoInd_CsRegisterRestrict();

        return;
    }

    if ((VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNewNtMod))
#if  (FEATURE_ON == FEATURE_LTE)
     && (VOS_FALSE == ulCsfbExistFlag)
#endif
       )
    {                                                                           /* 如果为A+I,且不是类似B或A+II处理的场合    */
        g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;

        /* RAC为0的场合 */
        if ((MM_UNSUPPORT_GPRS             == g_MmGlobalInfo.usRac)
         || (MMCMM_FORBIDDEN_PLMN_FOR_GPRS == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
        {
            NAS_MM_SetLikeBFlg();

            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S6_E5:INFO: MmLikeB is MM_TRUE");

            if (VOS_FALSE == ulLaiChangeFlag)
            {                                                               /* 如果LAI不变,更新状态为U1                 */
                if (MM_TRUE == g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg)
                {
                    g_MmGlobalInfo.LuInfo.ucLuType =
                                    MM_IE_LUT_PERIODIC_UPDATING;            /* 设置LU类型                               */
                    Mm_ComLuOnly();                                         /* 发送LU REQ                               */
                }
                else if (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED !=
                    NAS_MML_GetCsUpdateStatus())
                {
                    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;   /* 设置LU类型                               */
                    Mm_ComLuOnly();                                         /* 发送LU REQ                               */
                }
                else
                {
                    Mm_ComNasInfoSav(
                             MM_STATUS_ATTACHED,
                             NAS_MML_GetSimCsSecurityCksn()
                             );
                    g_MmGlobalInfo.ucMmServiceState =
                        MM_NORMAL_SERVICE;                          /* 设置服务状态                             */
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S6_E5:INFO: MmServiceState is MM_NORMAL_SERVICE");
                    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                MM_MMC_LU_RESULT_SUCCESS,
                                                NAS_MML_REG_FAIL_CAUSE_NULL);        /* 向MMC发送MMCMM_LU_RESULT_IND             */
                    NAS_MM_SndGmmLuResultInd(MMGMM_LU_SUCCESS,
                                             NAS_MML_REG_FAIL_CAUSE_NULL);        /* 向MMC发送MMCMM_LU_RESULT_IND             */


                    Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S6_E5:NORMAL: STATUS is  MM_IDLE_NORMAL_SERVICE");
                    NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                }
            }
            else
            {
                Mm_TimerStop(MM_TIMER_T3213);
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;       /* 设置LU类型                               */
                Mm_ComLuOnly();                                             /* 发送LU REQ                               */
            }
        }
        else if (VOS_TRUE == NAS_MML_GetPsRestrictRegisterFlg())
        {
            if (VOS_FALSE == ulLaiChangeFlag)
            {                                                                   /* 如果LAI不变,更新状态为U1                 */
                if (MM_TRUE == g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg)
                {
                    g_MmGlobalInfo.LuInfo.ucLuType =
                                    MM_IE_LUT_PERIODIC_UPDATING;                /* 设置LU类型                               */
                    Mm_ComLuOnly();                                             /* 发送LU REQ                               */
                }
                else if (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED !=
                    NAS_MML_GetCsUpdateStatus())
                {
                    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;       /* 设置LU类型                               */
                    Mm_ComLuOnly();                                             /* 发送LU REQ                               */
                }
                else
                {
                    NAS_MM_RcvSysInfoPsRestrictRegLaiNoChangeU1();
                }
            }
            else
            {
                Mm_TimerStop(MM_TIMER_T3213);
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;           /* 设置LU类型                               */
                Mm_ComLuOnly();                                                 /* 发送LU REQ                               */
            }
        }
        else
        {                                                                       /* RAC不等于零                              */
            ;
        }
    }
    else
    {
        ucUserSpecificSearchFlg = Mm_Get_UserSpecificSearchFlg_From_SysInfo(pMsg);
        Mm_ComRcvSysHandle(ucUserSpecificSearchFlg);                       /* 调用在系统信息的公共处理                 */
    }


    Mm_DealWithBuffMsg();
}


VOS_VOID Mm_Cell_S9_E13(VOS_VOID *pMsg)
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

    if (GMMMM_NET_DETACH_REATTACH == pstNetWkDetachInd->enDetachType)
    {
        g_MmGlobalInfo.ucLikeB = MM_TRUE;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S9_E13:INFO: MmLikeB is MM_TRUE");
    }
    else if (GMMMM_NET_DETACH_IMSI == pstNetWkDetachInd->enDetachType)
    {
        Mm_ComSaveProcAndCauseVal(MM_NET_DETACH_PROC,
                                  NAS_MML_REG_FAIL_CAUSE_NTDTH_IMSI);                     /* 记录流程和原因值                         */
    }
    else
    {
        switch (pstNetWkDetachInd->ulDetachCause)
        {
        case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
            Mm_TimerStop(MM_TIMER_PROTECT_AGENT);
            g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
            Mm_TimerStop(MM_TIMER_T3230);                                       /* 停止T3230                                */
            if (NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode())
            {
                /* 释放除紧急呼外所有存在和正在建立的MM连接 */
                Mm_ComRelAllMmConnExcEmergencyCall(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SIM_INVALID);
            }
            Mm_ComSaveProcAndCauseVal(MM_NET_DETACH_PROC,
                                      (VOS_UINT8)pstNetWkDetachInd->ulDetachCause);   /* 记录流程和原因值                         */
            g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                       /* 设置服务状态                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S9_E13:INFO: MmServiceState is MM_NO_IMSI");
            Mm_ComToNoImsiHandle();                                             /* 调用删除IMSI的公共处理                   */
            if ((MM_FALSE ==
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                ucEstingCallTypeFlg)
                && (MMCC_EMERGENCY_CALL !=
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                RcvXXEstReq.ulCallType))
            {
                Mm_TimerStart(MM_TIMER_T3240);                                  /* 启动T3240                                */
                g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;             /* 记录前状态                               */
                Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E14:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
            }
            break;
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
            g_MmGlobalInfo.ucLikeB = MM_TRUE;                                   /* 类似于B模式的全局量                      */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S9_E13:INFO: MmLikeB is MM_TRUE");
            break;
        case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
            Mm_ComSaveProcAndCauseVal(MM_NET_DETACH_PROC,
                                      (VOS_UINT8)pstNetWkDetachInd->ulDetachCause);   /* 记录流程和原因值                         */
            break;
        case NAS_MML_REG_FAIL_CAUSE_NULL:
            NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
            g_MmGlobalInfo.ucLikeB = MM_TRUE;
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S9_E13:INFO: MmLikeB is MM_TRUE");
            break;
        default:
            break;
        }
    }
}


VOS_VOID Mm_Cell_S9_E14(VOS_VOID* pMsg)
{
    VOS_UINT8                               ucActionType;
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
    {                                                                           /* 结果为失败的场合                         */
        switch (pstGmmActionRstInd->enGmmActionType)
        {
        case GMMMM_ACTION_RAU:                                                 /* 类型为RAU的场合                          */
            ucActionType = MM_GMM_RAU_PROC;
            break;
        case GMMMM_ACTION_ATTACH:                                              /* 类型为ATTACH的场合                       */
            ucActionType = MM_GMM_ATTACH_PROC;
            break;
        case GMMMM_ACTION_SR:                                                  /* 类型为SR的场合                           */
            ucActionType = MM_GMM_SR_PROC;
            break;
        default:
            ucActionType = MM_NULL_PROC;
            break;
        }
        if (MM_NULL_PROC != ucActionType)
        {                                                                       /* 如果类型不为空的场合                     */
            switch (pstGmmActionRstInd->enCause)
            {
            case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
            case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
                Mm_TimerStop(MM_TIMER_T3230);                                   /* 停止T3230                                */
                Mm_TimerStop(MM_TIMER_PROTECT_AGENT);
                g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
                Mm_TimerStop(MM_TIMER_T3210);                               /* 停止T3210                                */
                Mm_ComSaveProcAndCauseVal(ucActionType,
                                       (VOS_UINT8)pstGmmActionRstInd->enCause);   /* 记录流程和原因值                         */
                g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;               /* 设置服务状态                             */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S9_E14:INFO: MmServiceState is MM_NO_IMSI");

                if (NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode())
                {
                    /* 释放除紧急呼外所有存在和正在建立的MM连接 */
                    Mm_ComRelAllMmConnExcEmergencyCall(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SIM_INVALID);
                }
                Mm_ComToNoImsiHandle();                                     /* 调用删除IMSI的公共处理                   */
                if ((MM_FALSE ==
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                    ucEstingCallTypeFlg)
                    && (MMCC_EMERGENCY_CALL !=
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                    RcvXXEstReq.ulCallType))
                {
                    Mm_TimerStart(MM_TIMER_T3240);                          /* 启动T3240                                */
                    Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E14:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
                }
                break;
            case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
                if ( MM_GMM_ATTACH_PROC == ucActionType )
                {
                    Mm_TimerStop(MM_TIMER_PROTECT_AGENT);
                    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
                    Mm_TimerStop(MM_TIMER_T3210);                               /* 停止T3210                                */
                    Mm_ComSaveProcAndCauseVal(ucActionType,
                                           (VOS_UINT8)pstGmmActionRstInd->enCause);   /* 记录流程和原因值                         */
                    g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;               /* 设置服务状态                             */
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S9_E14:INFO: MmServiceState is MM_NO_IMSI");

                    if (NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode())
                    {
                        /* 释放除紧急呼外所有存在和正在建立的MM连接 */
                        Mm_ComRelAllMmConnExcEmergencyCall(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SIM_INVALID);
                    }
                    Mm_ComToNoImsiHandle();                                     /* 调用删除IMSI的公共处理                   */

                    if ((MM_FALSE ==
                        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                        ucEstingCallTypeFlg)
                        && (MMCC_EMERGENCY_CALL !=
                        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                        RcvXXEstReq.ulCallType))
                    {
                        Mm_TimerStart(MM_TIMER_T3240);                          /* 启动T3240                                */
                        Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E14:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
                    }
                }
                break;
            case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
            case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
                g_MmGlobalInfo.ucLikeB = MM_TRUE;                               /* 类似于B模式的全局量                      */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S9_E14:INFO: MmLikeB is MM_TRUE");
                break;
            case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
            case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
            case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
            case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
                Mm_ComSaveProcAndCauseVal(ucActionType,
                                           (VOS_UINT8)pstGmmActionRstInd->enCause);   /* 记录流程和原因值                         */
                break;
            case NAS_MML_REG_FAIL_CAUSE_NO_PDP_CONTEXT_ACT:
            case NAS_MML_REG_FAIL_CAUSE_MS_ID_NOT_DERIVED:
            case NAS_MML_REG_FAIL_CAUSE_IMPLICIT_DETACHED:
                break;
            default:

                /* A+I下,PS注册失败达到最大次数,MM正在进行紧急呼叫,此时需要通知MMC当前CS继续尝试注册
                   等待RRC重新驻留后发起LAU或联合attach */
                if ((VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNewNtMod))
                 && (pstGmmActionRstInd->ucAttCounter >= 5)
                 && (NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE_REG_MAX_TIMES != pstGmmActionRstInd->enCause))
                {
                    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                MM_MMC_LU_RESULT_FAILURE,
                                                NAS_MML_REG_FAIL_CAUSE_DELAY_CS_IN_TRANS_LAU);

                    g_MmGlobalInfo.ucLikeB = MM_TRUE;
                }

                break;
            }
        }
    }
}

/*******************************************************************************
  Module:   Mm_Cell_S9_E44
  Function: 在WAIT FOR OUTGOING MM CONNECTION状态下
            收到RRMM_DATA_IND(MM STATUS)的处理
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
        1.  张志勇     2003.12.09  新版做成
*******************************************************************************/

VOS_VOID Mm_Cell_S9_E44(VOS_VOID *pMsg)
{
    if (MM_LIMITED_SERVICE != g_MmGlobalInfo.ucMmServiceState)
    {
        Mm_TimerStop( MM_TIMER_T3212 );                                         /* 停T3212                                  */
    }
}


VOS_VOID Mm_Cell_S11_E9(VOS_VOID *pMsg)
{

    if ( MM_FALSE == Mm_RcvGmmImsiDetechIni(pMsg) )
    {
        return;

    }

    Mm_TimerStop(MM_TIMER_T3240);                                               /* 停T3240                                  */

    Mm_SndRrRelReq(RRC_CELL_UNBARRED);

    g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                         /* 记录前状态                               */
    Mm_ComSetMmState(IMSI_DETACH_PENDING);
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S11_E9:NORMAL: STATUS is IMSI_DETACH_PENDING");
}


VOS_VOID Mm_Cell_S11_E11(VOS_VOID *pMsg)
{
    if (MM_FALSE == NAS_MM_RcvGmmGprsDetechIni(pMsg))
    {
        return;
    }

    Mm_TimerStop(MM_TIMER_T3240);                                               /* 停T3240                                  */
    Mm_SndRrRelReq(RRC_CELL_UNBARRED);

    g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                         /* 记录前状态                               */
    Mm_ComSetMmState(IMSI_DETACH_PENDING);
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S11_E11:NORMAL: STATUS is IMSI_DETACH_PENDING");
}



VOS_VOID Mm_Cell_S11_E13(VOS_VOID *pMsg)
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

    if ( GMMMM_NET_DETACH_REATTACH == pstNetWkDetachInd->enDetachType )
    {
        NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);

        g_MmGlobalInfo.ucLikeB = MM_TRUE;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S11_E13:INFO: MmLikeB is MM_TRUE");
    }
    else if ( GMMMM_NET_DETACH_IMSI == pstNetWkDetachInd->enDetachType )
    {
        Mm_TimerStop(MM_TIMER_PROTECT_AGENT);
        g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
        Mm_ComSaveProcAndCauseVal(MM_NET_DETACH_PROC,
                                                    NAS_MML_REG_FAIL_CAUSE_NTDTH_IMSI);   /* 记录流程和原因值                         */
    }
    else
    {
        switch ( pstNetWkDetachInd->ulDetachCause )
        {
        case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
            Mm_TimerStop(MM_TIMER_PROTECT_AGENT);
            g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
            Mm_ComSaveProcAndCauseVal(MM_NET_DETACH_PROC,
                                      (VOS_UINT8)pstNetWkDetachInd->ulDetachCause);   /* 记录流程和原因值                         */
            g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                       /* 设置服务状态                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S11_E13:INFO: MmServiceState is MM_NO_IMSI");
            Mm_ComToNoImsiHandle();                                             /* 调用删除IMSI的公共处理                   */
            break;
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
            g_MmGlobalInfo.ucLikeB = MM_TRUE;                                   /* 类似于B模式的全局量                      */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S11_E13:INFO: MmLikeB is MM_TRUE");
            break;
        case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
            Mm_ComSaveProcAndCauseVal(MM_NET_DETACH_PROC,
                                      (VOS_UINT8)pstNetWkDetachInd->ulDetachCause);   /* 记录流程和原因值                         */
            break;
        case NAS_MML_REG_FAIL_CAUSE_NULL:
            NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
            g_MmGlobalInfo.ucLikeB = MM_TRUE;
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S11_E13:INFO: MmLikeB is MM_TRUE");
            break;
        default:
            break;
        }
    }
}


VOS_VOID Mm_Cell_S11_E14(VOS_VOID* pMsg)
{
    VOS_UINT8                                   ucActionType = MM_NULL_PROC;
    GMMMM_GMM_ACTION_RESULT_IND_STRU        *pstGmmActionRstInd;


    if ( MM_FALSE == Mm_RcvGmmGmmActionResultInd(pMsg) )
    {
        return;

    }

    if (NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode())
    {
    }

    pstGmmActionRstInd = (GMMMM_GMM_ACTION_RESULT_IND_STRU*)pMsg;

    if (GMMMM_ACTION_FAILURE == pstGmmActionRstInd->enActionResult )
    {                                                                           /* 结果为失败的场合                         */
        switch ( pstGmmActionRstInd->enGmmActionType )
        {
        case GMMMM_ACTION_RAU:                                                 /* 类型为RAU的场合                          */
            ucActionType = MM_GMM_RAU_PROC;
            break;
        case GMMMM_ACTION_ATTACH:                                              /* 类型为ATTACH的场合                       */
            ucActionType = MM_GMM_ATTACH_PROC;
            break;
        case GMMMM_ACTION_SR:                                                  /* 类型为SR的场合                           */
            ucActionType = MM_GMM_SR_PROC;
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S11_E14:WARNING: ulGmmActionType Abnormal");
            break;
        }
        if ( MM_NULL_PROC != ucActionType )
        {                                                                       /* 如果类型为空的场合                       */
            switch ( pstGmmActionRstInd->enCause )
            {
            case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
            case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
                Mm_TimerStop(MM_TIMER_PROTECT_AGENT);
                g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
                Mm_ComSaveProcAndCauseVal(ucActionType,
                                  (VOS_UINT8)pstGmmActionRstInd->enCause);        /* 记录流程和原因值                         */
                g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;               /* 设置服务状态                             */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S11_E14:INFO: MmServiceState is MM_NO_IMSI");
                Mm_ComToNoImsiHandle();                                     /* 调用删除IMSI的公共处理                   */
                Mm_SndRrRelReq(RRC_CELL_UNBARRED);
                break;
            case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
                if ( MM_GMM_ATTACH_PROC == ucActionType )
                {
                    Mm_TimerStop(MM_TIMER_PROTECT_AGENT);
                    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
                    Mm_ComSaveProcAndCauseVal(ucActionType,
                                      (VOS_UINT8)pstGmmActionRstInd->enCause);        /* 记录流程和原因值                         */
                    g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;               /* 设置服务状态                             */
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S11_E14:INFO: MmServiceState is MM_NO_IMSI");
                    Mm_ComToNoImsiHandle();                                     /* 调用删除IMSI的公共处理                   */
                }
                break;
            case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
            case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
                g_MmGlobalInfo.ucLikeB = MM_TRUE;                               /* 类似于B模式的全局量                      */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S11_E14:INFO: MmLikeB is MM_TRUE");
                break;
            case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
            case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
            case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
            case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
                    Mm_ComSaveProcAndCauseVal(ucActionType,
                                      (VOS_UINT8)pstGmmActionRstInd->enCause);        /* 记录流程和原因值                         */
                break;
            case NAS_MML_REG_FAIL_CAUSE_NO_PDP_CONTEXT_ACT:
            case NAS_MML_REG_FAIL_CAUSE_MS_ID_NOT_DERIVED:
            case NAS_MML_REG_FAIL_CAUSE_IMPLICIT_DETACHED:
                break;
            default:
                /* A+I下,PS注册失败达到最大次数,MM正在进行紧急呼叫,此时需要通知MMC当前CS继续尝试注册
                   等待RRC重新驻留后发起LAU或联合attach */
                if ((VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNewNtMod))
                 && (pstGmmActionRstInd->ucAttCounter >= 5)
                 && (NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE_REG_MAX_TIMES != pstGmmActionRstInd->enCause))
                {
                    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                MM_MMC_LU_RESULT_FAILURE,
                                                NAS_MML_REG_FAIL_CAUSE_DELAY_CS_IN_TRANS_LAU);

                    g_MmGlobalInfo.ucLikeB = MM_TRUE;
                }
                break;
            }
        }
    }
}

/*******************************************************************************
  Module:   Mm_Cell_S11_E16
  Function: 在WAIT_FOR_NETWORK_COMMAND状态下
            收到GMMMM_AUTHENTICATON_FAILURE_IND的处理
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2003.12.09  新版做成
*******************************************************************************/
VOS_VOID Mm_Cell_S11_E16(VOS_VOID *pMsg)
{
    if ( MM_FALSE == Mm_RcvGmmAuthFailInd(pMsg) )
    {
        return;

    }
    Mm_ComSaveProcAndCauseVal(MM_AUTH_FAIL_PROC, NAS_MML_REG_FAIL_CAUSE_NULL);            /* 记录流程和原因值                         */
    g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                               /* 设置服务状态                             */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S11_E16:INFO: MmServiceState is MM_NO_IMSI");
    Mm_ComToNoImsiHandle();                                                     /* 调用删除IMSI的公共处理                   */
}


VOS_VOID Mm_Cell_S12_E13(VOS_VOID *pMsg)
{
    GMMMM_NETWORK_DETACH_IND_STRU      *pstNetWkDetachInd;


    if ( MM_FALSE == NAS_MM_RcvGmmNetworkDetechInd(pMsg) )
    {
        return;
    }

    if (NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode())
    {
    }

    pstNetWkDetachInd = (GMMMM_NETWORK_DETACH_IND_STRU*)pMsg;

    g_MmGlobalInfo.ucProc = MM_NET_DETACH_PROC;                                 /* 记录当前的流程                           */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S12_E13:INFO: MmServiceState is MM_NET_DETACH_PROC");
    if ( GMMMM_NET_DETACH_REATTACH == pstNetWkDetachInd->enDetachType )
    {
        NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
        g_MmGlobalInfo.ucLikeB = MM_TRUE;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S12_E13:INFO: MmLikeB is MM_TRUE");
    }
    else if ( GMMMM_NET_DETACH_IMSI == pstNetWkDetachInd->enDetachType )
    {
        Mm_TimerStop(MM_TIMER_T3230);                                           /* 停止T3230                                */
        Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

        NAS_NORMAL_LOG(WUEPS_PID_MM, "Mm_Cell_S12_E13: Network IMSI detach, Could not make CS call");
        Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

        Mm_ComSaveProcAndCauseVal(MM_NET_DETACH_PROC,
                                                    NAS_MML_REG_FAIL_CAUSE_NTDTH_IMSI);   /* 记录流程和原因值                         */
        g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;              /* 设置服务状态                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S12_E13:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");
        Mm_ComToU2Handle();                                                     /* 调用MM进U2的处理                         */
        Mm_SndRrRelReq(RRC_CELL_UNBARRED);
        /* Mm_SndMmcCmSvcInd在Mm_ComRelAllMmConn中上报 */
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        Mm_TimerStop(MM_TIMER_T3218);                                           /* 停T3218                                  */
        Mm_ComDelRandRes();                                                     /* 删除RAND和RES                            */
    }
    else
    {
        switch ( pstNetWkDetachInd->ulDetachCause )
        {
        case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
            Mm_TimerStop(MM_TIMER_T3230);                                       /* 停止T3230                                */
            Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

            Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SIM_INVALID);

            Mm_ComNetDetachCauseHandle((VOS_UINT8)pstNetWkDetachInd->ulDetachCause);
            Mm_SndRrRelReq(RRC_CELL_UNBARRED);

            Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);                            /* 通知MMC，CS域的业务已经停止              */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
            break;
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
            g_MmGlobalInfo.ucLikeB = MM_TRUE;                                   /* 类似于B模式的全局量                      */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S12_E13:INFO: MmLikeB is MM_TRUE");
            break;
        case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
            Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

            /* 网络发起 DETACH后MS不再ATTACH:这个地方回复cs detach更合适，不应该回复forb other */
            Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

            Mm_ComNetDetachCauseHandle((VOS_UINT8)pstNetWkDetachInd->ulDetachCause);
            Mm_SndRrRelReq(RRC_CELL_UNBARRED);
            Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);                            /* 通知MMC，CS域的业务已经停止              */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
            break;
        case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
            if ( MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState )
            {
                Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

                /* 网络发起 DETACH后MS不再ATTACH:这个地方回复cs detach更合适，不应该回复forb other */
                Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

                Mm_ComNetDetachCauseHandle(
                                    (VOS_UINT8)pstNetWkDetachInd->ulDetachCause );
                Mm_SndRrRelReq(RRC_CELL_UNBARRED);

                Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);                        /* 通知MMC，CS域的业务已经停止              */
                NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);

            }
            break;
        case NAS_MML_REG_FAIL_CAUSE_NULL:
            NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
            g_MmGlobalInfo.ucLikeB = MM_TRUE;
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S12_E13:INFO: MmLikeB is MM_TRUE");
            break;
        default:
            break;
        }
    }
}


VOS_VOID Mm_Cell_S12_E14(VOS_VOID* pMsg)
{

    VOS_UINT8                                ucActionType = MM_NULL_PROC;
    GMMMM_GMM_ACTION_RESULT_IND_STRU        *pstGmmActionRstInd;
    VOS_UINT32                               ulCsServExist;

    if (MM_FALSE == Mm_RcvGmmGmmActionResultInd(pMsg))
    {
        return;

    }

    ulCsServExist  = Mm_ComJudgeCsServExist();
    if (MM_CS_SERV_EMERGENCY_CALL_EXIST == ulCsServExist)
    {
        return;
    }

    pstGmmActionRstInd = (GMMMM_GMM_ACTION_RESULT_IND_STRU*)pMsg;

    if (GMMMM_ACTION_FAILURE == pstGmmActionRstInd->enActionResult)
    {                                                                           /* 结果为失败的场合                         */
        switch (pstGmmActionRstInd->enGmmActionType)
        {
        case GMMMM_ACTION_RAU:                                                 /* 类型为RAU的场合                          */
            ucActionType = MM_GMM_RAU_PROC;
            break;
        case GMMMM_ACTION_ATTACH:                                              /* 类型为ATTACH的场合                       */
            ucActionType = MM_GMM_ATTACH_PROC;
            break;
        case GMMMM_ACTION_SR:                                                  /* 类型为SR的场合                           */
            ucActionType = MM_GMM_SR_PROC;
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S12_E14:WARNING: ulGmmActionType Abnormal");
            break;
        }

        if (MM_NULL_PROC != ucActionType)
        {
            switch (pstGmmActionRstInd->enCause)
            {
            case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
            case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
                Mm_TimerStop(MM_TIMER_T3230);                                   /* 停止T3230                                */
                if ( ( MM_GMM_SR_PROC == ucActionType ) ||
                    ( ( MM_GMM_ATTACH_PROC == ucActionType ) &&
                    ( MM_STATUS_ATTACHED ==
                            g_MmSubLyrShare.MmShare.ucCsAttachState ) ) ||
                    ( ( MM_GMM_RAU_PROC == ucActionType ) &&
                    ( MM_STATUS_ATTACHED ==
                                g_MmSubLyrShare.MmShare.ucCsAttachState ) ) )
                {
                    Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

                    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SIM_INVALID);

                    Mm_ComCauseHandleAllProc(
                                            ucActionType,
                                            pstGmmActionRstInd->enCause);
                    Mm_SndRrRelReq(RRC_CELL_UNBARRED);
                    /* Mm_SndMmcCmSvcInd在Mm_ComRelAllMmConn中上报 */
                    NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);

                }
                break;
            case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
                if ( MM_GMM_ATTACH_PROC == ucActionType )
                {
                    Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

                    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SIM_INVALID);

                    Mm_ComCauseHandleAllProc(
                                            ucActionType,
                                            pstGmmActionRstInd->enCause);
                    Mm_SndRrRelReq(RRC_CELL_UNBARRED);
                    Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);
                    Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);                    /* 通知MMC，CS域的业务已经停止              */
                    NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
                }
                break;
            case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
            case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
                g_MmGlobalInfo.ucLikeB = MM_TRUE;                               /* 类似于B模式的全局量                      */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S12_E14:INFO: MmLikeB is MM_TRUE");
                break;
            case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
                if ( ( MM_GMM_SR_PROC == ucActionType ) ||
                    ( ( MM_GMM_ATTACH_PROC == ucActionType ) &&
                    ( MM_STATUS_ATTACHED ==
                                g_MmSubLyrShare.MmShare.ucCsAttachState ) ) ||
                    ( ( MM_GMM_RAU_PROC == ucActionType ) &&
                    ( MM_STATUS_ATTACHED ==
                                g_MmSubLyrShare.MmShare.ucCsAttachState ) ) )
                {
                    Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

                    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_FORB_OTHER);

                    Mm_ComCauseHandleAllProc(
                                            ucActionType,
                                            pstGmmActionRstInd->enCause);
                    Mm_SndRrRelReq(RRC_CELL_UNBARRED);
                    Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);                    /* 通知MMC，CS域的业务已经停止              */
                    NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);

                }
                break;
            case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
            case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
            case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
                if (MM_STATUS_ATTACHED ==
                                    g_MmSubLyrShare.MmShare.ucCsAttachState)
                {
                    Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

                        /* 原因值12被拒不触发搜网待着不动不再尝试重播，服务状态是MM_COM_SRVST_LIMITED_SERVICE_REGION,*/
                        if (NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW == pstGmmActionRstInd->enCause)
                        {
                            Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_FORB_LA);
                        }
                        else
                        {
                            Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_FORB_OTHER);
                        }

                    Mm_ComCauseHandleAllProc(
                                            ucActionType,
                                            pstGmmActionRstInd->enCause);
                    Mm_SndRrRelReq(RRC_CELL_UNBARRED);
                    Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);                    /* 通知MMC，CS域的业务已经停止              */
                    NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);

                }
                break;

            default:
                /* A+I下,PS注册失败达到最大次数,MM正在进行紧急呼叫,此时需要通知MMC当前CS继续尝试注册
                   等待RRC重新驻留后发起LAU或联合attach */
                if ((VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNewNtMod))
                 && (pstGmmActionRstInd->ucAttCounter >= 5)
                 && (NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE_REG_MAX_TIMES != pstGmmActionRstInd->enCause))
                {
                    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                MM_MMC_LU_RESULT_FAILURE,
                                                NAS_MML_REG_FAIL_CAUSE_DELAY_CS_IN_TRANS_LAU);

                    g_MmGlobalInfo.ucLikeB = MM_TRUE;
                }
                break;
            }
        }
    }
}



VOS_VOID Mm_Cell_S12_E16(VOS_VOID *pMsg)
{
    if (MM_FALSE == Mm_RcvGmmAuthFailInd(pMsg))
    {
        return;
    }

    Mm_TimerStop(MM_TIMER_STOP_ALL);                                            /* 停保护定时器                             */

    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SIM_INVALID);

    Mm_ComAuthenRcvAuthenRej();                                                 /* 调用鉴权失败的公共处理                   */
    Mm_SndRrRelReq(RRC_CELL_UNBARRED);
    /* Mm_SndMmcCmSvcInd在Mm_ComRelAllMmConn中上报 */
    NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
    Mm_TimerStop(MM_TIMER_T3218);                                               /* 停T3218                                  */
    Mm_ComDelRandRes();                                                         /* 删除RAND和RES                            */

}
/*******************************************************************************
  Module:   Mm_Cell_S14_E13
  Function: 在WAIT FOR REESTABLISH（WAIT FOR EST_CNF）状态下,
                收到GMMMM_NETWORK_DETACH_IND的处理
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2004.03.11  根据二期接口改造,新版做成
*******************************************************************************/

VOS_VOID Mm_Cell_S14_E13(VOS_VOID *pMsg)
{
    if (MM_CS_SIG_CONN_PRESENT == g_MmGlobalInfo.ucCsSigConnFlg)
    {
        Mm_Cell_S9_E13(pMsg);
        Mm_TimerStop(MM_TIMER_T3230);                                           /* 停止T3230                                */
    }
    else
    {
        Mm_Cell_S12_E13(pMsg);
    }
}

/*******************************************************************************
  Module:   Mm_Cell_S14_E14
  Function: 在WAIT FOR REESTABLISH（WAIT FOR EST_CNF）状态下,
                收到GMMMM_GMM_ACTION_RESULT_IND的处理
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2004.03.11  根据二期接口改造,新版做成
*******************************************************************************/

VOS_VOID Mm_Cell_S14_E14(VOS_VOID *pMsg)
{
    if ( MM_CS_SIG_CONN_PRESENT == g_MmGlobalInfo.ucCsSigConnFlg )
    {
        Mm_Cell_S9_E14(pMsg);
    }
    else
    {
        Mm_Cell_S12_E14(pMsg);
    }
}


/*******************************************************************************
  Module:   Mm_Cell_S14_E16
  Function: 在WAIT FOR REESTABLISH（WAIT FOR EST_CNF）状态下,
                收到GMMMM_AUTHENTICATON_FAILURE_IND的处理
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2004.03.11  根据二期接口改造,新版做成
*******************************************************************************/
VOS_VOID Mm_Cell_S14_E16(VOS_VOID *pMsg)
{
    Mm_ComAuthenRcvAuthenRej();
}


VOS_VOID Mm_Cell_S17_E5(VOS_VOID *pMsg)
{
    VOS_UINT8                           ucUserSpecificSearchFlg = 0;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulCsfbExistFlag;

    /* 取得CSFB是否存在的标志 */
    ulCsfbExistFlag     = NAS_MML_IsCsfbServiceStatusExist();
#endif

    if (VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
    {
        NAS_MM_ProcMmcMmSysInfoInd_CsAttachNotAllow();

        return;
    }

    if (VOS_TRUE == NAS_MM_IsCsForbidden())
    {
        NAS_MM_ProcCsForbidenFlg_RcvSysInfoInd(g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg);

        return;
    }

    if (VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg())
    {
        NAS_MM_ProcMmcMmSysInfoInd_CsRegisterRestrict();

        return;
    }

    /* CS ONLY或PS ONLY，nmo1下GMM进行联合注册 */
    if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
     && (MM_NET_MODE_I == g_MmGlobalInfo.ucNewNtMod)
     /* pending状态不需要判断like B标记 */
#if  (FEATURE_ON == FEATURE_LTE)
     && (VOS_FALSE == ulCsfbExistFlag)
#endif
    )
    {                                                                           /* 如果为A+I,且不是类似B或A+II处理的场合    */
        g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;

        /* RAC为0的场合 */
        if ((MM_UNSUPPORT_GPRS == g_MmGlobalInfo.usRac)
         || (MMCMM_FORBIDDEN_PLMN_FOR_GPRS == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
        {
            NAS_MM_SetLikeBFlg();

            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E5:INFO: MmLikeB is MM_TRUE");

            if (VOS_TRUE == NAS_MML_IsCampLaiInfoChanged())
            {                                                               /* LAI变化的场合                            */
                Mm_ComSetMmState(g_MmGlobalInfo.ucPreState);
                PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E5:NORMAL: ucState = ", g_MmGlobalInfo.ucState);
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;       /* 设置LU类型                               */
                Mm_ComLuOnly();                                             /* LU REQ                                   */
            }
        }
    }
    else
    {                                                                           /* 非A+I模式                                */
        if ( g_MmGlobalInfo.ucNtMod != g_MmGlobalInfo.ucNewNtMod )
        {
            Mm_ComSetMmState(g_MmGlobalInfo.ucPreState);
            PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E5:NORMAL: ucState = ", g_MmGlobalInfo.ucState);
            Mm_ComNetModeChange();
        }
        else
        {   /* A+II或者B模式                            */
            ucUserSpecificSearchFlg = Mm_Get_UserSpecificSearchFlg_From_SysInfo(pMsg);
            Mm_ComRcvSysHandle(ucUserSpecificSearchFlg);                                               /* 调用在系统信息的公共处理                 */
        }
    }

    Mm_DealWithBuffMsg();
}




VOS_VOID Mm_Cell_S17_E7(VOS_VOID *pMsg)
{

    GMMMM_COMBINED_ATTACH_ACCEPTED_STRU     *pCombinedAttatchAccpt;
    NAS_MML_LAI_STRU                   *pstCsSuccLai = VOS_NULL_PTR;
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8   enCsUpdateStatus;
    NAS_MML_IGNORE_AUTH_REJ_INFO_STRU      *pstAuthRejInfo;

    pstCsSuccLai    = NAS_MML_GetCsLastSuccLai(  );


    if ( MM_FALSE == Mm_RcvGmmCombinedAttachAccept(pMsg) )
    {
        return;
    }

    g_MmGlobalInfo.LuInfo.ucPsRandomAccessFailCnt = 0;

    pCombinedAttatchAccpt = (GMMMM_COMBINED_ATTACH_ACCEPTED_STRU*)pMsg;
    if ( GMMMM_ATTACH_RESLUT_COMBINED ==
                        pCombinedAttatchAccpt->enAttachResult )
    {
        g_MmGlobalInfo.ucLikeNetmode2 = MM_FALSE;
        g_MmGlobalInfo.ucLikeB = MM_FALSE;                                      /* 设置类似于B模式的全局量                  */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E7:INFO: MmLikeB is MM_FALSE");
        Mm_TimerStop( MM_TIMER_T3212 );                                         /* 停T3212                                  */
        Mm_TimerStop( MM_TIMER_T3211 );                                         /* 停T3211                                  */
        Mm_ComSaveProcAndCauseVal(MM_COMB_ATTACH_PROC, NAS_MML_REG_FAIL_CAUSE_NULL);      /* 记录流程和原因值                         */
        g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;                    /* 设置服务状态                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E7:INFO: MmServiceState is MM_NORMAL_SERVICE");


        /* 记录注册成功的RAC，用于网络模式改变,比较RAI是否发生改变 */
        g_MmGlobalInfo.MsCsInfo.ucOldRac = NAS_MML_GetCurrCampRac();

        /* 由于网络模式改变,RAI不改变时,MM没有更新网络模式,而GMM模块可能会
           进行联合过程，为保证后续流程与GMM一致，此处需要更新网络模式 */
        g_MmGlobalInfo.ucNtMod           = g_MmGlobalInfo.ucNewNtMod;

        pstCsSuccLai->stPlmnId.ulMcc = NAS_MML_GetCurrCampPlmnId()->ulMcc;
        pstCsSuccLai->stPlmnId.ulMnc = NAS_MML_GetCurrCampPlmnId()->ulMnc;
        pstCsSuccLai->aucLac[0] = NAS_MML_GetCurrCampLai()->aucLac[0];
        pstCsSuccLai->aucLac[1] = NAS_MML_GetCurrCampLai()->aucLac[1];

        pstCsSuccLai->ucRac = g_MmGlobalInfo.MsCsInfo.ucOldRac;

        NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_UPDATED);

        g_MmSubLyrShare.MmShare.ucSpecProFlg =  MM_NOT_UPDATED_SPECIFIC_PROCEDURE;

        if ( GMMMM_MS_ID_TYPE_IMSI ==
                                pCombinedAttatchAccpt->stMsIdentity.enMsIdType )
        {
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                                    ~MM_MS_ID_TMSI_PRESENT;     /* 设置TMSI无效                             */
            NAS_MML_InitUeIdTmsiInvalid();
        }
        else if ( GMMMM_MS_ID_TYPE_TMSI ==
                            pCombinedAttatchAccpt->stMsIdentity.enMsIdType )
        {
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg |=
                                                    MM_MS_ID_TMSI_PRESENT;      /* 设置TMSI无效                             */
            PS_MEM_CPY(NAS_MML_GetUeIdTmsi(),
                       pCombinedAttatchAccpt->stMsIdentity.aucTmsi,
                       NAS_MML_MAX_TMSI_LEN);
            g_MmGlobalInfo.MsCsInfo.stPlmnId.ulMcc = NAS_MML_GetCsLastSuccMcc();
            g_MmGlobalInfo.MsCsInfo.stPlmnId.ulMnc = NAS_MML_GetCsLastSuccMnc();
        }
        else
        {

        }
        Mm_ComNasInfoSav(
                        MM_STATUS_ATTACHED,
                        NAS_MML_GetSimCsSecurityCksn()
                        );

        if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
        {/* 3G USIM */
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
        }
        else
        {/* 2G SIM */
            Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
        }



        if (MM_TRUE == g_MmGlobalInfo.ucPowerOnFlg)
        {
            g_MmGlobalInfo.ucPowerOnFlg = MM_FALSE;
        }

        g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_0;                   /* LAU 记数器清零 */

        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* 记录前状态                               */
        Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);

        pstAuthRejInfo = NAS_MML_GetAuthRejInfo();
        pstAuthRejInfo->ucHplmnCsAuthRejCounter = 0;


        /* 标示MM正在进行联合注册 */
        g_MmGlobalInfo.ucIsComBined = VOS_TRUE;

        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                    MM_MMC_LU_RESULT_SUCCESS,
                                    NAS_MML_REG_FAIL_CAUSE_NULL);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E7:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
    }
    else
    {
        switch(pCombinedAttatchAccpt->enCause)
        {
        case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR:
            g_MmGlobalInfo.ucLikeNetmode2 = MM_FALSE;
            Mm_TimerStop( MM_TIMER_T3212 );                                         /* 停T3212                                  */
            Mm_TimerStop( MM_TIMER_T3211 );                                         /* 停T3211                                  */
            Mm_ComSaveProcAndCauseVal(
                                      MM_COMB_ATTACH_PROC,
                                      (VOS_UINT8)pCombinedAttatchAccpt->enCause);   /* 记录流程和原因值                         */
            g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                       /* 设置服务状态                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E7:INFO: MmServiceState is MM_NO_IMSI");
            Mm_ComToNoImsiHandle();                                             /* 调用进NO IMSI的公共处理                  */
            Mm_ComSetMmState(MM_IDLE_NO_IMSI);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E7:NORMAL: STATUS is MM_IDLE_NO_IMSI");
            break;
        case NAS_MML_REG_FAIL_CAUSE_MSC_UNREACHABLE:
        case NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE:
        case NAS_MML_REG_FAIL_CAUSE_PROCEDURE_CONGESTION:
            if ( pCombinedAttatchAccpt->ulAttachAttCounter < MM_RAU_ATTACH_COUNTER_MAX)
            {
                enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
                if ( (VOS_FALSE == NAS_MML_IsCsLaiChanged() )
                  && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus) )
                {

                    Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                }
                else
                {
                    Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);
                }

                if( MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
                {
                }
            }
            else
            {
                /**************************************************************
                The MM sublayer shall act as in network operation mode II or III
                (depending whether a PCCCH is present) as long as the combined
                GMM procedures are not successful and no new RA is entered. The
                new MM state is MM IDLE. 3gpp 24.008 4.7.3.2.3.2
                ***************************************************************/
                g_MmGlobalInfo.ucLikeNetmode2 = MM_TRUE;
                g_MmGlobalInfo.ucLikeB        = MM_TRUE;

                /*if CS is already attached,don't LAU any more*/
                if(MM_STATUS_ATTACHED != g_MmSubLyrShare.MmShare.ucCsAttachState)
                {
                    if(( MM_ATT_NEED == g_MmGlobalInfo.ucAttFlg ) && ( MM_TRUE == g_MmGlobalInfo.ucPowerOnFlg ))
                    {
                        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_IMSI_ATTACH;             /* 设置LU类型                               */
                    }
                    else
                    {
                        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;              /* 设置LU类型                               */
                    }
                    Mm_ComLuOnly();                                                                     /* 发送LU REQ                               */
                }
                else
                {
                    Mm_ComSetMmState(g_MmGlobalInfo.ucPreState);

                    NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                }
            }
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S17_E7:WARNING: Cause Abnormal");
            /* WUEPS_ASSERT(0); */                                                    /* 异常错误处理                             */
            break;
        }

        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    pCombinedAttatchAccpt->enCause);
    }
    Mm_ComProcCauseClear();
    Mm_ComCheckDelayMmConn( MM_TRUE );
}



VOS_VOID Mm_Cell_S17_E8(VOS_VOID *pMsg)
{
    GMMMM_COMBINED_ATTACH_REJECTED_STRU        *pCombinedAttachRjct;
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8   enCsUpdateStatus;
    VOS_UINT8                                   ucState;                           /* MM状态                                   */

    if ( MM_FALSE == NAS_MM_RcvGmmCombinedAttachRej(pMsg) )
    {
        return;
    }

    pCombinedAttachRjct = (GMMMM_COMBINED_ATTACH_REJECTED_STRU*)pMsg;

    /* 标示MM正在进行联合注册 */
    g_MmGlobalInfo.ucIsComBined = VOS_TRUE;

    NAS_MM_ComProcPsRandomAccessFailCnt(pCombinedAttachRjct->enCause,pCombinedAttachRjct->ulAttachAttCounter);

    switch(pCombinedAttachRjct->enCause)
    {
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
        Mm_ComSaveProcAndCauseVal(
                                  MM_COMB_ATTACH_PROC,
                                  (VOS_UINT8)pCombinedAttachRjct->enCause);     /* 记录流程和原因值                         */
        g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                           /* 设置服务状态                             */

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E8:INFO: MmServiceState is MM_NO_IMSI");

        Mm_ComToNoImsiHandle();                                                 /* 调用进NO IMSI的公共处理                  */

        Mm_ComSetMmState(MM_IDLE_NO_IMSI);

        NAS_MML_SetSimCsRegStatus(VOS_FALSE);

        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    pCombinedAttachRjct->enCause);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E8:NORMAL: STATUS is MM_IDLE_NO_IMSI");

        break;
    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
        g_MmGlobalInfo.ucLikeB = MM_TRUE;                                       /* 设置类似于B模式的全局量                  */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E8:INFO: MmLikeB is MM_TRUE");
        if ( MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState )
        {
            if ( VOS_FALSE == NAS_MML_IsCsLaiChanged() )
            {
                Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E8:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");

                NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);


                Mm_SndRrNasInfoChgReq(MM_NAS_INFO_SYNC_AS_FLG);


                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                            MM_MMC_LU_RESULT_SUCCESS,
                                            NAS_MML_REG_FAIL_CAUSE_NULL);

            }
            else
            {
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;           /* 设置LU类型                               */
                Mm_ComLuOnly();                                                 /* LU REQ                                   */
            }
        }
        else
        {
            enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
            if ( (VOS_FALSE == NAS_MML_IsCsLaiChanged() ) &&
                (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus) )
            {                                                                   /* 如果LAI不变,更新状态为U1的场合           */
                if ( MM_ATT_NEED == g_MmGlobalInfo.ucAttFlg )
                {
                    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_IMSI_ATTACH;     /* 设置LU类型                               */
                    Mm_ComLuOnly();                                             /* LU REQ                                   */
                }
                else
                {
                    Mm_ComNasInfoSav(
                                     MM_STATUS_ATTACHED,
                                     NAS_MML_GetSimCsSecurityCksn()
                                     );
                    g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;        /* 设置服务状态                             */
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E8:INFO: MmServiceState is MM_NORMAL_SERVICE");


                    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                MM_MMC_LU_RESULT_SUCCESS,
                                                NAS_MML_REG_FAIL_CAUSE_NULL);                    /* 向MMC发送MMCMM_LU_RESULT_IND             */

                    Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E8:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
                    NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                }
            }
            else
            {
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;           /* 设置LU类型                               */
                Mm_ComLuOnly();                                                 /* LU REQ                                   */
            }
        }
        break;
    case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        Mm_ComSaveProcAndCauseVal(
                                  MM_COMB_ATTACH_PROC,
                                  (VOS_UINT8)pCombinedAttachRjct->enCause);         /* 记录流程和原因值                         */
        Mm_ComRejectCause11(MM_ATTACH);                                         /* 调用原因值为#11的处理                    */
        g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_0;


        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    pCombinedAttachRjct->enCause);


        break;
    case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
        Mm_ComSaveProcAndCauseVal(
                                  MM_COMB_ATTACH_PROC,
                                  (VOS_UINT8)pCombinedAttachRjct->enCause);         /* 记录流程和原因值                         */
        Mm_ComRejectCause13(MM_ATTACH);                                         /* 调用原因值为#13的处理                    */
        g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_0;


        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    pCombinedAttachRjct->enCause);


        break;
    case NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED:
        Mm_ComSetMmState(MM_IDLE_LOCATION_UPDATE_NEEDED);

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E8:NORMAL: STATUS is MM_IDLE_LOCATION_UPDATE_NEEDED");
        Mm_ComSaveProcAndCauseVal(
                                  MM_COMB_RAU_PROC,
                                  (VOS_UINT8)pCombinedAttachRjct->enCause);         /* 记录流程和原因值                         */


        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    pCombinedAttachRjct->enCause);


        break;
    default:

        if (pCombinedAttachRjct->ulAttachAttCounter == 0x0)
        {
            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                            MM_MMC_LU_RESULT_FAILURE,
                            pCombinedAttachRjct->enCause);
        }

        else if ( pCombinedAttachRjct->ulAttachAttCounter < 5)
        {
            enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
            if ( (VOS_FALSE == NAS_MML_IsCsLaiChanged() )
              && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus) )
            {                                                                   /* 如果LAI不变,更新状态为U1的场合           */
                Mm_ComSaveProcAndCauseVal(
                                        MM_COMB_ATTACH_PROC,
                                        (VOS_UINT8)pCombinedAttachRjct->enCause);   /* 记录流程和原因值                         */
                g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;            /* 设置服务状态                             */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E8:INFO: MmServiceState is MM_NORMAL_SERVICE");
                Mm_ComNasInfoSav(
                                 MM_STATUS_ATTACHED,
                                 NAS_MML_GetSimCsSecurityCksn()
                                 );
                g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;             /* 记录前状态                               */
                Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);

                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E8:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");

                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                            MM_MMC_LU_RESULT_SUCCESS,
                                            NAS_MML_REG_FAIL_CAUSE_NULL);

            }
            else
            {
                Mm_ComSaveProcAndCauseVal(
                                        MM_COMB_ATTACH_PROC,
                                        (VOS_UINT8)pCombinedAttachRjct->enCause);   /* 记录流程和原因值                         */
                g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;      /* 设置服务状态                             */


                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                            MM_MMC_LU_RESULT_FAILURE,
                                            pCombinedAttachRjct->enCause);


                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E8:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");
                g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;             /* 记录前状态                               */
                Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);
                NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);

                NAS_MM_UpdateEquPlmnInfo(pCombinedAttachRjct->enCause);

                Mm_ComNasInfoSav(
                                MM_STATUS_DETACHED,
                                MM_CKSN_INVALID
                                );                                              /* 设置MM信息                               */
                Mm_ComDelLai();                                                 /* 删除LAI                                  */
                g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                    ~MM_MS_ID_TMSI_PRESENT;
                NAS_MML_InitUeIdTmsiInvalid();
                if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
                {
                    Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
                    Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKC_ID);               /* 更新SIM卡更新状态                        */
                }
                else
                {
                    Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
                    Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYS_ID);            /* 更新SIM卡更新状态                        */
                }

                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E8:NORMAL: STATUS is MM_IDLE_ATTEMPTING_TO_UPDATE");
            }
        }
        else if (NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE_REG_MAX_TIMES != pCombinedAttachRjct->enCause)
        {
            Mm_ComSaveProcAndCauseVal(
                                        MM_COMB_ATTACH_PROC,
                                        (VOS_UINT8)pCombinedAttachRjct->enCause);   /* 记录流程和原因值                         */
            g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;          /* 设置服务状态                             */


            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E8:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");

            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* 记录前状态                               */
            Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);

            Mm_ComNasInfoSav(
                            MM_STATUS_DETACHED,
                            MM_CKSN_INVALID
                            );                                                  /* 设置MM信息                               */
            Mm_ComDelLai();                                                     /* 删除LAI                                  */
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                ~MM_MS_ID_TMSI_PRESENT;
            NAS_MML_InitUeIdTmsiInvalid();

            if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
            {
                Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
                Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKC_ID);               /* 更新SIM卡更新状态                        */
            }
            else
            {
                Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
                Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYS_ID);            /* 更新SIM卡更新状态                        */
            }


            /**************************************************************
            The MM sublayer shall act as in network operation mode II or III
            (depending whether a PCCCH is present) as long as the combined
            GMM procedures are not successful and no new RA is entered. The
            new MM state is MM IDLE. 3gpp 24.008 4.7.3.2.3.2
            ***************************************************************/
            g_MmGlobalInfo.ucLikeNetmode2 = MM_TRUE;
            g_MmGlobalInfo.ucLikeB        = MM_TRUE;

            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E8:NORMAL: STATUS is MM_IDLE_ATTEMPTING_TO_UPDATE");

            /*PS尝试失败后，CS尝试单独进行一次位置更新A32D10820==>*/
            Mm_ComProcCauseClear();
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;
            if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
            {
                Mm_ComLuOnly();
            }
            else
            {
                /* G下，GAS同时处理CELL UPDATE和LU有问题，GCF 44.2.1.2.8 FAIL, 此处特殊处理
                   延迟1秒再发起 LU 过程。 */
                /* 此时状态不变，仍为: LOCATION UPDATING PENDING */
                Mm_TimerStart(MM_TIMER_DELAY_LU_GSM);
            }
            return;
        }
        else
        {
            ucState = g_MmGlobalInfo.ucState;
            Mm_ComSetMmState(g_MmGlobalInfo.ucPreState);
            g_MmGlobalInfo.ucPreState = ucState;                 /* 记录前状态                               */
        }
        break;
    }

    g_MmGlobalInfo.ucProc     = MM_NULL_PROC;
    Mm_ComCheckDelayMmConn( MM_TRUE );
    g_MmGlobalInfo.usCauseVal = NAS_MML_REG_FAIL_CAUSE_NULL;
}




VOS_VOID Mm_Cell_S17_E11(VOS_VOID *pMsg)
{
    if ( MM_FALSE == NAS_MM_RcvGmmGprsDetechIni(pMsg) )
    {
        return;
    }

    g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                         /* 记录前状态                               */
    Mm_ComSetMmState(IMSI_DETACH_PENDING);
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E11:NORMAL: STATUS is IMSI_DETACH_PENDING");
}



VOS_VOID Mm_Cell_S17_E13(VOS_VOID *pMsg)
{
    GMMMM_NETWORK_DETACH_IND_STRU       *pstNetWkDetachInd;

    if ( MM_FALSE == NAS_MM_RcvGmmNetworkDetechInd(pMsg) )
    {
        return;
    }

    pstNetWkDetachInd = (GMMMM_NETWORK_DETACH_IND_STRU*)pMsg;

    if ( GMMMM_NET_DETACH_REATTACH == pstNetWkDetachInd->enDetachType )
    {
        NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
    }
    else if ( GMMMM_NET_DETACH_NOATTACH == pstNetWkDetachInd->enDetachType )
    {
        switch ( pstNetWkDetachInd->ulDetachCause )
        {
        case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
            Mm_ComNetDetachCauseHandle(
                            (VOS_UINT8)pstNetWkDetachInd->ulDetachCause );        /* 调用Net Detach的处理                     */
            NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR);

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR);
            break;
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
            g_MmGlobalInfo.ucLikeB = MM_TRUE;                                   /* 设置类似于B模式的全局量                  */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E13:INFO: MmLikeB is MM_TRUE");
            switch(g_MmGlobalInfo.ucMmServiceState)
            {
            case MM_NORMAL_SERVICE:
                Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E13:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
                NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                break;
            case MM_LIMITED_SERVICE:
                Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E13:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
                break;
            case MM_ATTEMPTING_TO_UPDATE:
                Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E13:NORMAL: STATUS is MM_IDLE_ATTEMPTING_TO_UPDATE");
                NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                break;
            case MM_NO_IMSI:
                Mm_ComSetMmState(MM_IDLE_NO_IMSI);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E13:NORMAL: STATUS is MM_IDLE_NO_IMSI");
                break;

            case MM_NO_SERVICE:
                Mm_ComSetMmState(MM_IDLE_NO_CELL_AVAILABLE);

                if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
                {
                    /* gsm下tbf释放后不会再上系统消息，需要启动MM_TIMER_DELAY_LU_GSM定时器做lau */
                    Mm_TimerStart(MM_TIMER_DELAY_LU_GSM);
                }
                break;

            default:
                break;
            }
            break;
        case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
            Mm_ComNetDetachCauseHandle(
                            (VOS_UINT8)pstNetWkDetachInd->ulDetachCause );        /* 调用Net Detach的处理                     */
            NAS_MM_UpdateEquPlmnInfo(pstNetWkDetachInd->ulDetachCause);

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        pstNetWkDetachInd->ulDetachCause);
            break;
        case NAS_MML_REG_FAIL_CAUSE_NULL:
            switch(g_MmGlobalInfo.ucMmServiceState)
            {
            case MM_NORMAL_SERVICE:
                Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E13:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
                NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                break;
            case MM_LIMITED_SERVICE:
                Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E13:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
                break;
            case MM_ATTEMPTING_TO_UPDATE:
                Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E13:NORMAL: STATUS is MM_IDLE_ATTEMPTING_TO_UPDATE");
                NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                break;
            case MM_NO_IMSI:
                Mm_ComSetMmState(MM_IDLE_NO_IMSI);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E13:NORMAL: STATUS is MM_IDLE_NO_IMSI");
                break;

            case MM_NO_SERVICE:
                Mm_ComSetMmState(MM_IDLE_NO_CELL_AVAILABLE);

                if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
                {
                    /* gsm下tbf释放后不会再上系统消息，需要启动MM_TIMER_DELAY_LU_GSM定时器做lau */
                    Mm_TimerStart(MM_TIMER_DELAY_LU_GSM);
                }
                break;

            default:
                break;
            }

            g_MmGlobalInfo.ucLikeB = MM_TRUE;
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E13:INFO: MmLikeB is MM_TRUE");
            break;
        default:
            break;
        }
    }
    else
    {

    }
}


VOS_VOID Mm_Cell_S17_E15(VOS_VOID *pMsg)
{
    GMMMM_LU_INITIATION_STRU    *pstMmcLuIni;
    VOS_UINT8                    ucPsRestrictionFlg;

    ucPsRestrictionFlg      = NAS_MML_GetPsRestrictRegisterFlg();

    if ( MM_FALSE == Mm_RcvGmmLuIni(pMsg) )
    {
        return;
    }

    pstMmcLuIni = ( GMMMM_LU_INITIATION_STRU* )pMsg;

    if ( GMMMM_NO_TIMER_EXPIRED == pstMmcLuIni->enTimerExpiredFlg )
    {
        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;                   /* 设置LU类型为NORMAL                       */
    }
    else
    {
        if (((NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == NAS_MML_GetCsUpdateStatus() )
           && (VOS_FALSE == ucPsRestrictionFlg)
           && (GMMMM_T3312_EXPIRED == pstMmcLuIni->enTimerExpiredFlg))
          || (GMMMM_T3412OrT3423_EXPIRED == pstMmcLuIni->enTimerExpiredFlg))
        {                                                                       /* 如果更新状态为U1的场合                   */
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_PERIODIC_UPDATING;       /* 设置LU类型为周期                         */
        }
        else
        {
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;               /* 设置LU类型为NORMAL                       */
        }
    }
    Mm_ComLuOnly();                                                             /* 进行LU过程                               */
}




VOS_VOID Mm_Cell_S17_E18(VOS_VOID *pMsg)
{

    VOS_UINT32                              ulCsServExist;
    NAS_MML_LAI_STRU                       *pstCsSuccLai        = VOS_NULL_PTR;
    GMMMM_COMBINED_RAU_ACCEPTED_STRU       *pstCombinedRauAccpt = VOS_NULL_PTR;
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8   enCsUpdateStatus;

    pstCsSuccLai    = NAS_MML_GetCsLastSuccLai(  );

    if ( MM_FALSE == Mm_RcvGmmCombinedRauAccepted(pMsg) )
    {
        return;
    }

    g_MmGlobalInfo.LuInfo.ucPsRandomAccessFailCnt = 0;

    pstCombinedRauAccpt = (GMMMM_COMBINED_RAU_ACCEPTED_STRU*)pMsg;

    if ( GMMMM_RAU_RESULT_COMBINED == pstCombinedRauAccpt->enRauResult )
    {
        g_MmGlobalInfo.ucLikeB = MM_FALSE;                                      /* 设置类似于B模式的全局量                  */
        g_MmGlobalInfo.ucLikeNetmode2 = MM_FALSE;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E18:INFO: MmLikeB is MM_FALSE");
        Mm_TimerStop( MM_TIMER_T3212 );                                         /* 停T3212                                  */
        Mm_TimerStop( MM_TIMER_T3211 );                                         /* 停T3211                                  */
        Mm_ComSaveProcAndCauseVal(
                                  MM_COMB_RAU_PROC,
                                  NAS_MML_REG_FAIL_CAUSE_NULL);                           /* 记录流程和原因值                         */
        g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;                    /* 设置服务状态                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E18:INFO: MmServiceState is MM_NORMAL_SERVICE");

        /* 记录注册成功的RAC，用于网络模式改变,比较RAI是否发生改变 */
        g_MmGlobalInfo.MsCsInfo.ucOldRac = NAS_MML_GetCurrCampRac();

        /* 由于网络模式改变,RAI不改变时,MM没有更新网络模式,而GMM模块可能会
           进行联合过程，为保证后续流程与GMM一致，此处需要更新网络模式 */
        g_MmGlobalInfo.ucNtMod           = g_MmGlobalInfo.ucNewNtMod;

        pstCsSuccLai->stPlmnId.ulMcc = NAS_MML_GetCurrCampPlmnId()->ulMcc;
        pstCsSuccLai->stPlmnId.ulMnc = NAS_MML_GetCurrCampPlmnId()->ulMnc;
        pstCsSuccLai->aucLac[0] = NAS_MML_GetCurrCampLai()->aucLac[0];
        pstCsSuccLai->aucLac[1] = NAS_MML_GetCurrCampLai()->aucLac[1];

        pstCsSuccLai->ucRac = g_MmGlobalInfo.MsCsInfo.ucOldRac;

        NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_UPDATED);              /* 设置更新状态                             */
        g_MmSubLyrShare.MmShare.ucSpecProFlg =  MM_NOT_UPDATED_SPECIFIC_PROCEDURE;

        /* ==>AT2D01703 */
        if (GMMMM_REAL_PROCEDURE == pstCombinedRauAccpt->enRealProFlg)
        {
            if ( GMMMM_MS_ID_TYPE_IMSI == pstCombinedRauAccpt->stMsIdentity.enMsIdType )
            {
                g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                                        ~MM_MS_ID_TMSI_PRESENT; /* 设置TMSI无效                             */
                NAS_MML_InitUeIdTmsiInvalid();
            }
            else if ( GMMMM_MS_ID_TYPE_TMSI ==
                                pstCombinedRauAccpt->stMsIdentity.enMsIdType )
            {
                g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg |=
                                                        MM_MS_ID_TMSI_PRESENT;
                PS_MEM_CPY(NAS_MML_GetUeIdTmsi(),
                           pstCombinedRauAccpt->stMsIdentity.aucTmsi,
                           NAS_MML_MAX_TMSI_LEN);

                g_MmGlobalInfo.MsCsInfo.stPlmnId.ulMcc = NAS_MML_GetCsLastSuccMcc();
                g_MmGlobalInfo.MsCsInfo.stPlmnId.ulMnc = NAS_MML_GetCsLastSuccMnc();
            }
            else
            {

            }
        }
        /* <==AT2D01703 */
        Mm_ComNasInfoSav(
                        MM_STATUS_ATTACHED,
                        NAS_MML_GetSimCsSecurityCksn()
                        );

        if (GMMMM_REAL_PROCEDURE == pstCombinedRauAccpt->enRealProFlg)
        {
            if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
            {/* 3G USIM */
                Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
            }
            else
            {/* 2G SIM */
                Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
            }
        }
        else
        {
            NAS_MM_NotifyAsInfoChgReq();
        }


        g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_0;                   /*LAU 记数器清零 */
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* 记录前状态                               */
        Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);

        /* 标示MM正在进行联合注册 */
        g_MmGlobalInfo.ucIsComBined = VOS_TRUE;

        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                    MM_MMC_LU_RESULT_SUCCESS,
                                    NAS_MML_REG_FAIL_CAUSE_NULL);

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E18:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
    }
    else
    {
        switch(pstCombinedRauAccpt->enCause)
        {
        case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR:
            Mm_ComSaveProcAndCauseVal(
                                      MM_COMB_RAU_PROC,
                                      (VOS_UINT8)pstCombinedRauAccpt->enCause);   /* 记录流程和原因值                         */
            g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                       /* 设置服务状态                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E18:INFO: MmServiceState is MM_NO_IMSI");

            Mm_ComToNoImsiHandle();                                             /* 调用进NO IMSI的公共处理                  */
            Mm_ComSetMmState(MM_IDLE_NO_IMSI);

            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E18:NORMAL: STATUS is MM_IDLE_NO_IMSI");
            break;
        case NAS_MML_REG_FAIL_CAUSE_MSC_UNREACHABLE:
        case NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE:
        case NAS_MML_REG_FAIL_CAUSE_PROCEDURE_CONGESTION:


            /* 此处协议未明确给出具体的描述，进行如下处理，
               注册失败次数小于5，则若LAI不变且当前MM的状态为UPDATED,则更新为
               NORMAL SERVICE,否则当前状态为MM_IDLE_ATTEMPTING_TO_UPDATE，
               参考协议24008:4.7.5.2.6 */
            if ( (pstCombinedRauAccpt->ulRauAttCounter < MM_RAU_ATTACH_COUNTER_MAX)
              || (GMMMM_REAL_PROCEDURE != pstCombinedRauAccpt->enRealProFlg))
            {
                enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
                if ( (VOS_FALSE == NAS_MML_IsCsLaiChanged())
                  && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus))
                {                                                               /* 如果LAI不变,更新状态为U1的场合 */
                    g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;
                    g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;         /* 记录前状态 */

                    Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                }
                else
                {
                    g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;  /* 设置服务状态 */

                    g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;         /* 记录前状态 */

                    Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);

                }
            }

            else if ((NAS_MML_NET_RAT_TYPE_GSM != NAS_MML_GetCurrNetRatType())
                  || (MM_FALSE == g_MmGlobalInfo.ucLikeB))
            {
                /**************************************************************
                The MM sublayer shall act as in network operation mode II or III
                (depending whether a PCCCH is present) as long as the combined
                GMM procedures are not successful and no new RA is entered. The
                new MM state is MM IDLE. 3gpp 24.008 4.7.3.2.3.2
                ***************************************************************/
                g_MmGlobalInfo.ucLikeNetmode2 = MM_TRUE;
                g_MmGlobalInfo.ucLikeB        = MM_TRUE;

                /*if CS is already attached,don't LAU any more*/
                if(MM_STATUS_ATTACHED != g_MmSubLyrShare.MmShare.ucCsAttachState)
                {
                    enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
                    if ((VOS_FALSE == NAS_MML_IsCsLaiChanged())
                     && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus)
                     && (MM_ATT_NEED == g_MmGlobalInfo.ucAttFlg)
                     && (MM_TRUE == g_MmGlobalInfo.ucPowerOnFlg))
                    {
                        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_IMSI_ATTACH; /* 设置LU类型                               */
                    }
                    else
                    {
                        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;   /* 设置LU类型                               */
                    }
                }
                else
                {

                    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;
                }
                if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
                {
                    Mm_ComLuOnly();
                }
                else
                {
                    /* G下，GAS同时处理CELL UPDATE和LU有问题，GCF 44.2.3.2.3-2 FAIL, 此处特殊处理
                       延迟1秒再发起 LU 过程。 */
                    /* 此时状态不变，仍为: LOCATION UPDATING PENDING */
                    Mm_TimerStart(MM_TIMER_DELAY_LU_GSM);
                }
            }
            else
            {
                NAS_MM_ResumeMmStateToPreState_LocationUpdatingPending();

                g_MmGlobalInfo.ucPreState = LOCATION_UPDATING_PENDING;
            }
            break;


        /* GMM收到系统消息时候通知MM的假流程原因值，不会触发MMC发起搜网 */
        case NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE:
            NAS_MM_ResumeMmStateToPreState_LocationUpdatingPending();

            g_MmGlobalInfo.ucPreState = LOCATION_UPDATING_PENDING;
            break;

        default:
            NAS_MM_ResumeMmStateToPreState_LocationUpdatingPending();

            g_MmGlobalInfo.ucPreState = LOCATION_UPDATING_PENDING;
            break;
        }

        NAS_MM_SndMmcCsRegResultInd(pstCombinedRauAccpt->enRealProFlg,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    pstCombinedRauAccpt->enCause);
    }
    Mm_ComProcCauseClear();

    if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        Mm_ComCheckDelayMmConn( MM_TRUE );
        Mm_ComCheckDelayDetach();
    }
    else
    {
        /* G下，当收到GMM 联合RAU成功消息后，不能马上发起缓存的CS业务，因为此时GMM的RAU流程还未完全结束,
           可能还有RAU COMPLETE消息需要回复，还有TLLI 指派等等，如果此时马上发起MM的建链请求，GAS可能挂起
           GMM，导致RAU流程不能正常结束
           目前的解决方案是启个1秒定时器，延迟发起CS业务 */
        ulCsServExist = Mm_ComJudgeCsServExist();

        if ((MM_IDLE_NORMAL_SERVICE == g_MmGlobalInfo.ucState) && (MM_CS_SERV_NONE_EXIST != ulCsServExist))
        {
            Mm_TimerStart(MM_TIMER_DELAY_CS_SERVICE_GSM);
        }
        else
        {
            Mm_ComCheckDelayMmConn( MM_TRUE );
            Mm_ComCheckDelayDetach();
        }
    }
}



VOS_VOID Mm_Cell_S17_E19(VOS_VOID *pMsg)
{
    GMMMM_COMBINED_RAU_REJECTED_STRU           *pstCombinedRauRjct;
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8   enCsUpdateStatus;


    if ( MM_FALSE == Mm_RcvGmmCombinedRauRejected(pMsg) )
    {
        return;
    }

    pstCombinedRauRjct = (GMMMM_COMBINED_RAU_REJECTED_STRU*)pMsg;

    /* 标示MM正在进行联合注册 */
    g_MmGlobalInfo.ucIsComBined = VOS_TRUE;

    NAS_MM_ComProcPsRandomAccessFailCnt(pstCombinedRauRjct->enCause,pstCombinedRauRjct->ulRauAttCounter);

    switch(pstCombinedRauRjct->enCause)
    {
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
        Mm_ComSaveProcAndCauseVal(
                                  MM_COMB_RAU_PROC,
                                  (VOS_UINT8)pstCombinedRauRjct->enCause);            /* 记录流程和原因值                         */
        g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                           /* 设置服务状态                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E19:INFO: MmServiceState is MM_NO_IMSI");


        Mm_ComToNoImsiHandle();                                                 /* 调用进NO IMSI的公共处理                  */

        Mm_ComSetMmState(MM_IDLE_NO_IMSI);

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E19:NORMAL: STATUS is MM_IDLE_NO_IMSI");
        break;
    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
        g_MmGlobalInfo.ucLikeB = MM_TRUE;                                       /* 设置类似于B模式的全局量                  */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E19:INFO: MmLikeB is MM_TRUE");
        if ( MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState )
        {
            if ( VOS_FALSE == NAS_MML_IsCsLaiChanged() )
            {
                Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E19:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
                NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
            }
            else
            {
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;           /* 设置LU类型                               */
                Mm_ComLuOnly();                                                 /* LU REQ                                   */
            }
        }
        else
        {
            enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
            if ((VOS_FALSE == NAS_MML_IsCsLaiChanged())
                && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus))
            {                                                                   /* 如果LAI不变,更新状态为U1的场合           */
                if (MM_ATT_NEED == g_MmGlobalInfo.ucAttFlg)
                {
                    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_IMSI_ATTACH;     /* 设置LU类型                               */
                    Mm_ComLuOnly();                                             /* LU REQ                                   */
                }
                else
                {
                    Mm_ComNasInfoSav(
                                     MM_STATUS_ATTACHED,
                                     NAS_MML_GetSimCsSecurityCksn()
                                     );
                    g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;        /* 设置服务状态                             */
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E19:INFO: MmServiceState is MM_NORMAL_SERVICE");


                    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                MM_MMC_LU_RESULT_SUCCESS,
                                                NAS_MML_REG_FAIL_CAUSE_NULL);                    /* 向MMC发送MMCMM_LU_RESULT_IND             */
                    NAS_MM_SndGmmLuResultInd(MMGMM_LU_SUCCESS,
                                             NAS_MML_REG_FAIL_CAUSE_NULL);                    /* 向MMC发送MMCMM_LU_RESULT_IND             */
                    Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E19:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
                    NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                }
            }
            else
            {
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;           /* 设置LU类型                               */
                Mm_ComLuOnly();                                                 /* LU REQ                                   */
            }
        }
        break;
    case NAS_MML_REG_FAIL_CAUSE_MS_ID_NOT_DERIVED:
        Mm_ComSaveProcAndCauseVal(
                                  MM_COMB_RAU_PROC,
                                  (VOS_UINT8)pstCombinedRauRjct->enCause);        /* 记录流程和原因值                         */
        g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;                    /* 设置服务状态                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E19:INFO: MmServiceState is MM_NORMAL_SERVICE");
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* 记录前状态                               */
        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E19:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
        Mm_ComNasInfoSav(
                        MM_STATUS_ATTACHED,
                        NAS_MML_GetSimCsSecurityCksn()
                        );                                                      /* 设置MM信息                               */
        break;
    case NAS_MML_REG_FAIL_CAUSE_IMPLICIT_DETACHED:
        Mm_ComSaveProcAndCauseVal(
                                  MM_COMB_RAU_PROC,
                                  (VOS_UINT8)pstCombinedRauRjct->enCause);        /* 记录流程和原因值                         */
        g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;                   /* 设置服务状态                             */


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E19:INFO: MmServiceState is MM_LIMITED_SERVICE");
        Mm_ComNasInfoSav(
                        MM_STATUS_DETACHED,
                        NAS_MML_GetSimCsSecurityCksn()
                        );                                                      /* 设置MM信息                               */
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* 记录前状态                               */
        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E19:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
        break;
    case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        Mm_ComSaveProcAndCauseVal(
                                  MM_COMB_RAU_PROC,
                                  (VOS_UINT8)pstCombinedRauRjct->enCause);        /* 记录流程和原因值                         */
        Mm_ComRejectCause11(MM_RAU);                                            /* 调用原因值为#11的处理                    */
        g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_0;
        break;
    case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
        Mm_ComSaveProcAndCauseVal(
                                  MM_COMB_RAU_PROC,
                                  (VOS_UINT8)pstCombinedRauRjct->enCause);        /* 记录流程和原因值                         */
        Mm_ComRejectCause13(MM_RAU);                                            /* 调用原因值为#13的处理                    */
        g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_0;
        break;
    case NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED:
        Mm_ComSetMmState(MM_IDLE_LOCATION_UPDATE_NEEDED);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E19:NORMAL: STATUS is MM_IDLE_LOCATION_UPDATE_NEEDED");
        Mm_ComSaveProcAndCauseVal(
                                  MM_COMB_RAU_PROC,
                                  (VOS_UINT8)pstCombinedRauRjct->enCause);        /* 记录流程和原因值                         */
        break;
    default:
        if (pstCombinedRauRjct->ulRauAttCounter == 0x0)
        {
            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                            MM_MMC_LU_RESULT_FAILURE,
                            pstCombinedRauRjct->enCause);
        }
        if ( pstCombinedRauRjct->ulRauAttCounter < 5)
        {
            enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
            if ( (VOS_FALSE == NAS_MML_IsCsLaiChanged())
              && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus))
            {                                                                   /* 如果LAI不变,更新状态为U1的场合           */
                Mm_ComSaveProcAndCauseVal(
                                          MM_COMB_RAU_PROC,
                                          (VOS_UINT8)pstCombinedRauRjct->enCause);/* 记录流程和原因值                         */
                g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;            /* 设置服务状态                             */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E19:INFO: MmServiceState is MM_NORMAL_SERVICE");
                Mm_ComNasInfoSav(
                                MM_STATUS_ATTACHED,
                                NAS_MML_GetSimCsSecurityCksn()
                                );                                              /* 设置MM信息                               */
                g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;             /* 记录前状态                               */
                Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E19:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
            }
            else
            {
                Mm_ComSaveProcAndCauseVal(
                                          MM_COMB_RAU_PROC,
                                          (VOS_UINT8)pstCombinedRauRjct->enCause);    /* 记录流程和原因值                         */
                g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;      /* 设置服务状态                             */


                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E19:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");

                NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);
                g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;             /* 记录前状态                               */
                Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);

                Mm_ComNasInfoSav(
                                MM_STATUS_DETACHED,
                                MM_CKSN_INVALID
                                );                                              /* 设置MM信息                               */

                Mm_ComDelLai();                                                 /* 删除LAI                                  */

                g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                    ~MM_MS_ID_TMSI_PRESENT;
                NAS_MML_InitUeIdTmsiInvalid();
                if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
                {
                    Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
                    Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKC_ID);               /* 更新SIM卡更新状态                        */
                }
                else
                {
                    Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
                    Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYS_ID);            /* 更新SIM卡更新状态                        */
                }


                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E19:NORMAL: STATUS is MM_IDLE_ATTEMPTING_TO_UPDATE");
            }
        }
        else if(NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE_REG_MAX_TIMES != pstCombinedRauRjct->enCause)
        {
            Mm_ComSaveProcAndCauseVal(
                                      MM_COMB_RAU_PROC,
                                      (VOS_UINT8)pstCombinedRauRjct->enCause);    /* 记录流程和原因值                         */
            g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;          /* 设置服务状态                             */


            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E19:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");

            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* 记录前状态                               */
            Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);

            Mm_ComNasInfoSav(
                            MM_STATUS_DETACHED,
                            MM_CKSN_INVALID
                            );                                                  /* 设置MM信息                               */
            Mm_ComDelLai();                                                     /* 删除LAI                                  */
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                ~MM_MS_ID_TMSI_PRESENT;
            NAS_MML_InitUeIdTmsiInvalid();

            if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
            {
                Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
                Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKC_ID);               /* 更新SIM卡更新状态                        */
            }
            else
            {
                Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
                Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYS_ID);            /* 更新SIM卡更新状态                        */
            }


            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E19:NORMAL: STATUS is  MM_IDLE_ATTEMPTING_TO_UPDATE");

            /**************************************************************
            The MM sublayer shall act as in network operation mode II or III
            (depending whether a PCCCH is present) as long as the combined
            GMM procedures are not successful and no new RA is entered. The
            new MM state is MM IDLE. 3gpp 24.008 4.7.3.2.3.2
            ***************************************************************/
            g_MmGlobalInfo.ucLikeNetmode2 = MM_TRUE;
            g_MmGlobalInfo.ucLikeB        = MM_TRUE;

            /*PS尝试失败后，CS尝试单独进行一次位置更新A32D10820==>*/
            Mm_ComProcCauseClear();
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;
            Mm_ComLuOnly();
            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        pstCombinedRauRjct->enCause);
            return;
        }
        else
        {
            NAS_MM_ResumeMmStateToPreState_LocationUpdatingPending();

            g_MmGlobalInfo.ucPreState = LOCATION_UPDATING_PENDING;
        }
        break;
    }


    /* 通知MM的状态为401， */
    if ( NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE_REG_MAX_TIMES == pstCombinedRauRjct->enCause )
    {
        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);
    }
    else
    {
        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    pstCombinedRauRjct->enCause);
    }

    NAS_MM_UpdateEquPlmnInfo(pstCombinedRauRjct->enCause);

    g_MmGlobalInfo.ucProc    = MM_NULL_PROC;
    Mm_ComCheckDelayMmConn( MM_TRUE );

    g_MmGlobalInfo.usCauseVal = NAS_MML_REG_FAIL_CAUSE_NULL;

    Mm_ComCheckDelayDetach();
}




VOS_VOID Mm_Cell_S18_E5(VOS_VOID *pMsg)
{


    if (g_MmGlobalInfo.ucNtMod != g_MmGlobalInfo.ucNewNtMod)
    {
        /* 该状态下网络模式变化后不做Lu，直接向上层回复Detach成功 */
        g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;                     /* 更新网络模式                             */
        g_MmGlobalInfo.ucMmServiceState = MM_DETACHED;                          /* 设置服务状态                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S18_E5:INFO: MmServiceState is MM_DETACHED");

        Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                         NAS_MML_GetSimCsSecurityCksn());                 /* 设置MM信息                               */

        /* 判断等待标志是否存在，如果存在则发送MMCGMM_DETACH CNF */
        if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                     & MM_WAIT_CS_DETACH))
        {
            NAS_MM_SndMmcDetachCnf(MMC_MM_NO_IMSI);
            /* 清除等待标志 */
            g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
        }

        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S18_E5:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
    }


    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                MM_MMC_LU_RESULT_FAILURE,
                                NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);

    NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                             NAS_MML_REG_FAIL_CAUSE_NULL);
    /* 回复MMCMM_ATTACH_CNF的操作,清除等待ATTACH结果标志位 */
    if (MM_WAIT_CS_ATTACH == (g_MmGlobalInfo.stAttachInfo.enAttachType
                            & MM_WAIT_CS_ATTACH))
    {
        NAS_MM_SndMmcAttachCnf();
    }
    g_MmGlobalInfo.stAttachInfo.enAttachType = MM_WAIT_NULL_ATTACH;

    return;
}



VOS_VOID Mm_Cell_S18_E10(VOS_VOID *pMsg)
{
    if (MM_FALSE == Mm_RcvGmmImsiDetechComplete(pMsg))
    {
        return;
    }

    Mm_TimerStop(MM_TIMER_T3218);                                               /* 停T3218                                  */
    Mm_ComDelRandRes();                                                         /* 删除RAND和RES                            */

    NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);

    Mm_ComNasInfoSav(
                    MM_STATUS_DETACHED,
                    NAS_MML_GetSimCsSecurityCksn());

    /* 判断等待标志是否存在，如果存在则发送MMCGMM_DETACH CNF */
    if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                 & MM_WAIT_CS_DETACH))
    {
        NAS_MM_SndMmcDetachCnf(MMC_MM_LIMITED_SERVICE);
        /* 清除等待标志 */
        g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
    }

    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                MM_MMC_LU_RESULT_FAILURE,
                                NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

    g_MmGlobalInfo.ucPowerOnFlg = MM_TRUE;

    if (MM_IDLE_LOCATION_UPDATE_NEEDED != g_MmGlobalInfo.ucState)
    {
        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
    }


    NAS_EventReport(WUEPS_PID_MM, NAS_OM_EVENT_IMSI_DETACH_IND,
                    VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S18_E10:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
}


VOS_VOID Mm_Cell_S18_E12(VOS_VOID *pMsg)
{

    if (MM_FALSE == Mm_RcvGmmGprsDetechCmpl(pMsg))
    {
        return;
    }

    NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);

    Mm_TimerStop(MM_TIMER_T3218);                                               /* 停T3218                                  */
    Mm_ComDelRandRes();                                                         /* 删除RAND和RES                            */
    Mm_ComNasInfoSav(
                    MM_STATUS_DETACHED,
                    NAS_MML_GetSimCsSecurityCksn());
    if (MM_DETACH_CS_POWEROFF == g_MmGlobalInfo.ucDetachType)
    {                                                                           /* 关机的场合                               */
        Mm_SndMmcPowerOffCnf();
        Mm_ComSetMmState(MM_STATE_NULL);

        g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S18_E12:NORMAL: STATUS is MM_STATE_NULL");
    }
    else
    {
        /* 判断等待标志是否存在，如果存在则发送MMCGMM_DETACH CNF */
        if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                     & MM_WAIT_CS_DETACH))
        {
            NAS_MM_SndMmcDetachCnf(MMC_MM_LIMITED_SERVICE);
            /* 清除等待标志 */
            g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
        }

        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

        if (MM_IDLE_LOCATION_UPDATE_NEEDED != g_MmGlobalInfo.ucState)
        {
            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
        }
        g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S18_E12:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
    }

    NAS_EventReport(WUEPS_PID_MM, NAS_OM_EVENT_IMSI_DETACH_IND,
                    VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    g_MmGlobalInfo.ucPowerOnFlg = MM_TRUE;

}


VOS_VOID Mm_Cell_S9_E48(
                    VOS_VOID     *pMsg                                          /* 当前处理的消息                           */
                    )
{
    USIMM_AUTHENTICATION_CNF_STRU     *pstUsimAuthCnf = VOS_NULL_PTR;

    pstUsimAuthCnf = (USIMM_AUTHENTICATION_CNF_STRU *)pMsg;

    /* 当前不在等待此消息,丢弃 */
    NAS_MM_LogAuthInfo((VOS_UINT8)(pstUsimAuthCnf->stCmdResult.ulSendPara), g_MmGlobalInfo.AuthenCtrlInfo.ucOpId);

    if ((VOS_UINT8)(pstUsimAuthCnf->stCmdResult.ulSendPara) != g_MmGlobalInfo.AuthenCtrlInfo.ucOpId)
    {
        return;
    }

    if ((USIMM_3G_AUTH != pstUsimAuthCnf->enAuthType )
     && (USIMM_2G_AUTH != pstUsimAuthCnf->enAuthType ))
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_Cell_S9_E48:ERROR: authentication type is not expected!");

        return;
    }

    /* SIM 卡 || USIM 卡但鉴权请求中不包含 AUTN */
    if ((NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
        || (MM_IE_AUTN_PRESENT != g_MmMsgAuthReq.ucAutnFlg))
    {
        MM_RcvSimAuthCnf(pMsg);
        return;

    }

    if (MM_TRUE == Mm_RcvAgntUsimAuthenticationCnf(pMsg))
    {                                                                           /* 接收成功                                 */
        Mm_ComAuthenRcvUsimCnf();                                               /* 调用鉴权结束公共处理 */
    }
    else
    {                                                                           /* 接收失败                                 */
    }
    return;                                                                     /* 返回                                     */
}

/*******************************************************************************
  MODULE   : Mm_Cell_S9_E55
  FUNCTION : 在WAIT FOR OUTGOING MM CONNECTION状态下
             收到T3214_EXPIRED的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      03-12-22  新版作成
     2.
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E55(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{

    Mm_ComT3214orT3216Expired();                                                /* 调用T3214或者T3216溢出的处理             */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S9_E55:INFO: RECEIVE MM T3214 EXPIRED");
    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S9_E56
  FUNCTION : 在WAIT FOR OUTGOING MM CONNECTION状态下
             收到T3216_EXPIRED的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      03-12-22  新版作成
     2.
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E56(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{

    Mm_ComT3214orT3216Expired();                                                /* 调用T3214或者T3216溢出的处理             */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S9_E56:INFO: RECEIVE MM T3216 EXPIRED");
    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S9_E57
  FUNCTION : 在WAIT FOR OUTGOING MM CONNECTION状态下
             收到T3218_EXPIRED的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      03-12-22  新版作成
     2.
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E57(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{

    Mm_ComT3218Expired();                                                       /* T3218溢出的处理                          */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S9_E57:INFO: RECEIVE MM T3218 EXPIRED");
    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S9_E59
  FUNCTION : 在WAIT FOR OUTGOING MM CONNECTION状态下
             收到T3230_EXPIRED的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      03-12-22  新版作成
     2.
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E59(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{

    Mm_T3230Expire();                                                           /* T3230溢出的处理                          */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S9_E59:INFO: RECEIVE MM T3230 EXPIRED");
    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S11_E60
  FUNCTION : 在WAIT FOR NETWORK COMMAND状态下
             收到T3240_EXPIRED的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      03-12-22  新版作成
     2.
*******************************************************************************/
VOS_VOID Mm_Cell_S11_E60(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{

    Mm_T3240Expire();                                                           /* T3230溢出的处理                          */
    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S0_E61
  FUNCTION : 在MM_NULL状态下收到TIMER_PROTECT_EXPIRED的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      03-12-22  新版作成
     2.  张志勇       2004.05.20  MM_IT_BUG_027对应
     3.  张志勇        2005.01.27  007037 for MM
*******************************************************************************/
VOS_VOID Mm_Cell_S0_E61(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{

}
/*******************************************************************************
  MODULE   : Mm_Cell_S1_E61
  FUNCTION : 在MM IDLE NO CELL AVAILABLE状态下收到TIMER_PROTECT_EXPIRED的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      03-12-22  新版作成
     2.
     3.  张志勇        2005.01.27  007037 for MM
*******************************************************************************/
VOS_VOID Mm_Cell_S1_E61(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
}
/*******************************************************************************
  MODULE   : Mm_Cell_S12_E61
  FUNCTION : 在WAIT FOR RR CONNECTION (MM CONNECTION)状态下
             收到TIMER_PROTECT_EXPIRED的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      03-12-22  新版作成
     2.
     3.  张志勇        2005.01.27  007037 for MM
*******************************************************************************/
VOS_VOID Mm_Cell_S12_E61(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
}
/*******************************************************************************
  MODULE   : Mm_Cell_S13_E61
  FUNCTION : 在WAIT FOR REESTABLISH(WAIT FOR REEST REQ)状态下
             收到TIMER_PROTECT_EXPIRED的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      03-12-22  新版作成
     2.
     3.  张志勇        2005.01.27  007037 for MM
*******************************************************************************/
VOS_VOID Mm_Cell_S13_E61(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
}

/*******************************************************************************
  MODULE   : NAS_MM_ProcConnCtrlInfo_WaitForNetworkCommand
  FUNCTION : 在WAIT FOR NETWORK COMMAND状态下收到setup消息处理呼叫缓存
  INPUT    : VOS_UINT8 *pucCMMsg
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
  1.卞尹      15-6-15    新版作成

*******************************************************************************/
VOS_VOID NAS_MM_ProcConnCtrlInfo_WaitForNetworkCommand(VOS_UINT8 *pucCMMsg)
{
    if (MM_CC_MSG_SETUP == (pucCMMsg[MM_CC_MSG_TYPE_POS] & 0x3f))
    {
        if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
        {
            Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                                NAS_MMCM_REL_CAUSE_CM_SRV_REJ_CONGESTION);

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;
        }
    }
}


VOS_VOID Mm_Cell_S11_E50(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    VOS_UINT8            ucTI = 0;                                              /* CC消息中的TI                             */
    RRMM_DATA_IND_STRU  *pRrDataInd = (RRMM_DATA_IND_STRU *)pRcvMsg;            /* 消息RRMM_DATA_IND的结构体指针            */
    VOS_UINT8           *pucCMMsg = VOS_NULL_PTR;                               /* 指针类型转换                             */
    VOS_UINT8           *pucBakCMMsg = VOS_NULL_PTR;

    pucCMMsg = (VOS_UINT8 *)MM_MEM_ALLOC(
                           VOS_MEMPOOL_INDEX_MM,
                           pRrDataInd->RcvNasMsg.ulNasMsgSize,
                           WUEPS_MEM_NO_WAIT);                                  /* 申请内存                                 */
    if(VOS_NULL_PTR == pucCMMsg)
    {                                                                           /* 内存申请失败                             */

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_Cell_S11_E50:ERROR: MALLOC ERROR!");
        return;                                                                 /* 返回                                     */
    }
    pucBakCMMsg = pucCMMsg;
    Mm_TimerStop( MM_TIMER_T3240 );                                             /* 停TIMER3240                              */

    PS_MEM_SET(pucCMMsg, 0,
        sizeof(VOS_UINT8) * pRrDataInd->RcvNasMsg.ulNasMsgSize);                /* 初始化内存                               */

    PS_MEM_CPY (pucCMMsg, &(pRrDataInd->RcvNasMsg.aucNasMsg[0]),
        pRrDataInd->RcvNasMsg.ulNasMsgSize);                                    /* 得到消息内容                             */

    ucTI = (VOS_UINT8)(((pucCMMsg[0] & 0xf0) >> 4));                           /* 得到CC消息中的TI                         */

    if (((MM_CONST_NUM_7 == ucTI) || (MM_CONST_NUM_15 == ucTI)))
    {                                                                           /* TIO = 111                                */
        NAS_MM_ProcConnCtrlInfo_WaitForNetworkCommand(pucCMMsg);
        Mm_SndCcEstInd (ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize, pucCMMsg);    /* 向CC发送MMCC_EST_IND                     */
        Mm_ComCheckDelayMmConn(MM_FALSE);
    }

    /*lint -e701*/
    if ((MM_CONST_NUM_7 > ucTI))
    {                                                                           /* 网侧建立的MM连接                         */
        NAS_MM_ProcConnCtrlInfo_WaitForNetworkCommand(pucCMMsg);
        Mm_SndCcEstInd(ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize, pucCMMsg );    /* 向CC发送MMCC_EST_IND                     */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0] =
            (VOS_UINT8)(0x01 << ucTI);                                          /* 设置已经存在的MM连接的标志位             */
        Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);                                    /* 通知MMC，CS域的业务已经启动              */
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_EXIST);
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* 记录迁移之前的状态                       */
        Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S11_E50:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
        Mm_ComCheckDelayMmConn(MM_FALSE);

    }
    else if (((MM_CONST_NUM_7 < ucTI) && (MM_CONST_NUM_15 > ucTI))
        && (MMC_MM_NORMAL_SERVICE == g_MmGlobalInfo.ucMmServiceState))
    {                                                                           /* CC建立的MM连接                           */
        NAS_MM_ProcConnCtrlInfo_WaitForNetworkCommand(pucCMMsg);
        Mm_SndCcEstInd(ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize, pucCMMsg);     /* 向CC发送MMCC_EST_IND                     */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] =
            (VOS_UINT8)(0x01 << (ucTI - 8));                                    /* 设置已经存在的MM连接的标志位             */
        Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);                                    /* 通知MMC，CS域的业务已经启动              */
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_EXIST);
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* 记录迁移之前的状态                       */
        Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S11_E50:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
        Mm_ComCheckDelayMmConn(MM_FALSE);
    }
    else
    {

    }

    /*lint +e701*/
    MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucBakCMMsg);                            /* 释放申请的消息                           */

    NAS_MM_UpdateCsServiceConnStatusFlg();

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S14_E40
  FUNCTION : 在WAIT FOR REESTABLISH(WAIT FOR EST_CNF)状态下
             收到RRMM_DATA_IND(CM SERVICE ACCEPT)的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      04-01-06  新版作成
*******************************************************************************/
VOS_VOID Mm_Cell_S14_E40(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    VOS_UINT8   i = 0;                                                          /* 循环计数变量                             */
    /*lint -e701*/
    Mm_TimerStop(MM_TIMER_T3230);                                               /* 停TIMER3230                              */
    for (i = 0; i < MM_CONST_NUM_7; i++)
    {                                                                           /* 重建的MM连接                             */
        if (MM_CONST_NUM_0 !=
        (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
            & (0x01 << i)))
        {                                                                       /* 该TI的MM连接正在等待重建                 */
            Mm_SndCcReestCnf( i, MMCC_REEST_SUCCESS);                           /* 通知CC,MM连接正在建                      */
        }
        if (MM_CONST_NUM_0 !=
            (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
            & (0x01 << i)))
        {                                                                       /* 该TI的MM连接正在等待重建                 */
            Mm_SndCcReestCnf((i + 8), MMCC_REEST_SUCCESS);                      /* 通知CC,MM连接正在建                      */
        }
    }
    /*lint +e701*/
    g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                         /* 记录迁移之前的状态                       */
    Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S14_E40:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
    Mm_ComCheckDelayMmConn( MM_FALSE );                                         /* 检查是否有保留的需要建立的MM连接         */

#if (FEATURE_ON == FEATURE_ECALL)
    /* 处理eCall定时器启动标识 */
    NAS_MM_RecordEcallTimerStartNeededFlag();
#endif

    return;
}


VOS_VOID Mm_Cell_S0_E3(
                    VOS_VOID     *pMsg                                          /* 当前处理的消息                           */
                    )
{
    if (MM_TRUE == Mm_RcvMmcPlmnSrchIni(pMsg))
    {
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* 设置ucPreState                           */
        Mm_ComSetMmState(MM_IDLE_PLMN_SEARCH);

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S0_E3:NORMAL: STATUS is MM_IDLE_PLMN_SEARCH");
    }
    else
    {
    }
    return;                                                                     /* 返回                                     */
}


VOS_VOID Mm_Cell_S3_E65(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    MM_MSG_CM_SVC_REQ_STRU      CmSvcReq;                                       /* 要发送的CM SERVICE REQ消息               */
    VOS_UINT16                  usMsgSize = 0;                                  /* 消息长度,以字节为单位                    */
    VOS_UINT8                  *pucCmSvcReq = 0;                                /* 要发送的CM SERVICE REQ消息指针           */

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList = VOS_NULL_PTR;
#endif

    if (MM_FALSE == Mm_RcvSsEstReq(pRcvMsg))
    {                                                                           /* 消息检查结果失败                         */
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
        /* 如果当前为L单模则直接回复ss失败 */
        pstPrioRatList = NAS_MML_GetMsPrioRatList();
        if (VOS_TRUE == NAS_MML_IsLteOnlyMode(pstPrioRatList))
        {
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_NOT_SUPPORT_CS_CALL_S1_MODE_ONLY);
            return;
        }

        if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
        {
            NAS_MM_RcvSsEstReq_CSFB();

            return;
        }
#endif

        g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;             /* 记录收到建立请求时的状态                 */

        if ((MM_CONST_NUM_8 > g_MmSsEstReq.ulTi)
            || (MM_CONST_NUM_14 < g_MmSsEstReq.ulTi))
        {
            /* TI不合法 */

            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);
        }
        else
        {                                                                       /* TI合法                                   */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg
                = MM_TRUE;
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                                RcvXXEstReq.ulTransactionId
                = g_MmSsEstReq.ulTi;
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulCallType
                = 0;
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulCallPri
                = 0;
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucRat = NAS_MML_GetCurrNetRatType();

            Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_SS_ACT, MM_FALSE, &CmSvcReq);/* 填充CM SERVICE REQUEST结构体             */
            pucCmSvcReq = Mm_ComMsgCmSvcReqOfRrEstReq( &CmSvcReq, &usMsgSize ); /* 填充CM SERVICE REQUEST 消息              */
            if (VOS_NULL_PTR == pucCmSvcReq)
            {                                                                   /* 消息制作失败                             */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S3_E65:WARNING: MAKE MSG CM SERVICE REQUEST ERROR!");
                return;                                                         /* 返回                                     */
            }
            else
            {                                                                   /* 消息制作成功                             */
                Mm_SndRrEstReq(RRC_EST_CAUSE_ORIGIN_HIGH_PRIORITY_SIGNAL,
                   MM_FALSE, usMsgSize, pucCmSvcReq);                           /* 发送消息                                 */
                MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucCmSvcReq);                /* 释放CM SERVICE REQUEST 消息结构体        */
            }
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI =
                (VOS_UINT8)g_MmSsEstReq.ulTi;                                   /* 记录正在建立的MM连接的TI                 */
            g_MmGlobalInfo.ucMMConnEstingPD = MM_IE_PD_NON_CALL_RLT_SS_MSG;     /* 记录正在建立的MM连接的PD                 */
            Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);
            Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);                                /* 通知MMC，CS域的业务已经启动              */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* 记录迁移之前的状态                       */
            Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_MM_CONNECTION);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E65:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_MM_CONNECTION");
        }

        NAS_MM_UpdateCsServiceConnStatusFlg();

        NAS_MM_UpdateCsServiceBufferStatusFlg();
    }

    return;
}


VOS_VOID Mm_Cell_S4_E65(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{
    NAS_MML_MISCELLANEOUS_CFG_INFO_STRU   *pstMiscellaneousCfgInfo = VOS_NULL_PTR;
    NAS_MMCM_REL_CAUSE_ENUM_UINT32         enRelCause;

    pstMiscellaneousCfgInfo               = NAS_MML_GetMiscellaneousCfgInfo();
    enRelCause                            = NAS_MM_GetMmCmRelCause();

    if ( MM_FALSE == Mm_RcvSsEstReq(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
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

            /* CS域卡无效，则不处理补充业务 */
            if (VOS_FALSE  == NAS_MML_GetSimCsRegStatus())
            {
                Mm_SndSsRelInd(g_MmSsEstReq.ulTi,
                               NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SIM_INVALID);

                return;
            }
            
            /* 如果当前PS ONLY时支持CS业务NV未激活，则SS失败 */
            if ( (NAS_MML_MS_MODE_PS_ONLY == NAS_MML_GetMsMode())
              && (NAS_MMC_NV_ITEM_DEACTIVE == pstMiscellaneousCfgInfo->ucPsOnlyCsServiceSupportFlg) )
            {
                NAS_NORMAL_LOG(WUEPS_PID_MM, "Mm_Cell_S4_E65: PS ONLY mode and NV 9056 not active under L mode, Could not make SS call");
                Mm_SndSsRelInd(g_MmSsEstReq.ulTi,
                              NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);
                
                return;
            }
            
            /* 在LIMIT SRVICE状态放开SS业务的CSFB处理 */
            if (MM_IDLE_LIMITED_SERVICE == Mm_GetState())
            {
                NAS_MM_RcvSsEstReq_CSFB();

                return;
            }            

            
            /* LTE下UE在null、no imsi、wait for attach状态无法处理ss业务 */
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_NOT_SUPPORT_CS_CALL_S1_MODE_ONLY);

            return;
        }


        
#endif
        if ((NAS_MML_MS_MODE_PS_ONLY  == NAS_MML_GetMsMode())
         && (NAS_MMC_NV_ITEM_DEACTIVE == pstMiscellaneousCfgInfo->ucPsOnlyCsServiceSupportFlg))
        {
            NAS_NORMAL_LOG(WUEPS_PID_MM, "Mm_Cell_S4_E65: PS ONLY mode and NV 9056 not active, Could not make SS call");
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);
        }
        else
        {
            /*状态不为limited service或者服务域不为PS ONLY*/
            if ((NAS_MML_MS_MODE_PS_ONLY != NAS_MML_GetMsMode())
             || (MM_IDLE_LIMITED_SERVICE != g_MmGlobalInfo.ucState))
            {
                NAS_NORMAL_LOG1(WUEPS_PID_MM, "Mm_Cell_S4_E65: MM Substate ", g_MmGlobalInfo.ucState);
                /* UE在null、no imsi状态无法处理ss业务 */
                Mm_SndSsRelInd(g_MmSsEstReq.ulTi, enRelCause);
            }
            else
            {
                NAS_MML_SetCsAttachAllowFlg(VOS_TRUE);
                /*缓存该服务请求并进行CS注册*/
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg
                    = MM_TRUE;
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                                    RcvXXEstReq.ulTransactionId
                    = g_MmSsEstReq.ulTi;
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulCallType
                    = 0;
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulCallPri
                    = 0;
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucRat = NAS_MML_GetCurrNetRatType();
                if ((MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod)
                 && (MM_FALSE == g_MmGlobalInfo.ucLikeB))
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

        }
    }

    NAS_MM_UpdateCsServiceConnStatusFlg();

    NAS_MM_UpdateCsServiceBufferStatusFlg();

    return;
}


VOS_VOID Mm_Cell_S10_E65(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    MM_MSG_CM_SVC_REQ_STRU          CmSvcReq;                                   /* CM service request结构体                 */
    VOS_UINT8                       ucRst;

    if ( MM_FALSE == Mm_RcvSsEstReq(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        /* 当前小区主叫业务受限则不处理 */
        if (VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
        {
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);

            return;
        }
        /*lint -e701*/
        ucRst = Mm_ComJudgeLimitSvc();
        if ( ( MM_CONST_NUM_8 > g_MmSsEstReq.ulTi )
            || ( MM_CONST_NUM_14 < g_MmSsEstReq.ulTi )
            || ( MM_TRUE == ucRst ) )
        {                                                                       /* TI不合法或者在受限服务状态               */
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);
        }
        else if ( MM_CONST_NUM_0 !=
            ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1] &
            ( 0x01 << ( g_MmSsEstReq.ulTi - 8 ) ) ) )
        {                                                                       /* 要求建立的MM连接已经存在                 */
            Mm_SndSsEstCnf( g_MmSsEstReq.ulTi, MMSS_EST_SUCCESS );              /* 通知SS，MM连接建立成功                   */
        }
        else
        {                                                                       /* TI合法                                   */
            Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_SS_ACT, MM_FALSE, &CmSvcReq);/* 填充CM SERVICE REQUEST结构体             */
            Mm_ComMsgCmSvcReqSnd( &CmSvcReq );                                  /* 向网侧发送建立MM连接的请求               */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                                    RcvXXEstReq.ulTransactionId
                = g_MmSsEstReq.ulTi;                                           /* 记录重建MM连接的TI */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI =
                (VOS_UINT8)g_MmSsEstReq.ulTi;                                       /* 记录正在建立的MM连接的TI                 */
            g_MmGlobalInfo.ucMMConnEstingPD = MM_IE_PD_NON_CALL_RLT_SS_MSG;     /* 记录正在建立的MM连接的PD                 */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucRat = NAS_MML_GetCurrNetRatType();

            Mm_TimerStart(MM_TIMER_T3230);                                      /* 启动TIMER3230                            */
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* 记录迁移之前的状态                       */
            Mm_ComSetMmState(WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S10_E65:NORMAL: STATUS is WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION");
        }
        /*lint +e701*/
    }

    return;
}


VOS_VOID Mm_Cell_S11_E65(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList = VOS_NULL_PTR;
#endif

    if ( MM_FALSE == Mm_RcvSsEstReq(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S11_E65:WARNING: MMSS_EST_REQ check fail.");
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
        /* 如果当前为L单模则直接回复ss失败 */
        pstPrioRatList = NAS_MML_GetMsPrioRatList();
        if ( VOS_TRUE == NAS_MML_IsLteOnlyMode(pstPrioRatList) )
        {
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_NOT_SUPPORT_CS_CALL_S1_MODE_ONLY);
            return;
        }

        /* 如果当前驻留LTE,则直接回复SS失败 */
        /* L下在LOCATION_UPDATING_PENDING状态收到ss请求，mm需缓存 */
        if ((NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
         && (MM_IDLE_PLMN_SEARCH != g_MmGlobalInfo.ucState)
         && (LOCATION_UPDATING_PENDING != g_MmGlobalInfo.ucState))
        {
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_UE_INVALID_STATE);

            return;
        }
#endif

        if (MM_TRUE ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg)
        {                                                                       /* 已经存在一个保留的MM连接建立请求         */
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);
        }

        /* 检查多业务冲突是否允许 */
        if (VOS_FALSE == Mm_IsMultiSrvCollisionAllow(MM_CONN_CTRL_SS))
        {
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SERVICE_CONGESTION);

            return;
        }

        if (MM_IDLE_PLMN_SEARCH == g_MmGlobalInfo.ucState)
        {
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_SEARCHING_NETWORK);
            return;
        }

        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg
            = MM_TRUE;

        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId
            = g_MmSsEstReq.ulTi;

        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulCallType
            = 0;
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulCallPri
            = 0;
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucRat = NAS_MML_GetCurrNetRatType();


    }

    return;
}


VOS_VOID Mm_Cell_S3_E62(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    MM_MSG_CM_SVC_REQ_STRU      CmSvcReq;                                       /* 要发送的CM SERVICE REQ消息               */
    VOS_UINT16                  usMsgSize = 0;                                  /* 消息长度,以字节为单位                    */
    VOS_UINT8                  *pucCmSvcReq = 0;                                /* 要发送的CM SERVICE REQ消息指针           */


    if ( MM_FALSE == Mm_RcvSmsEstReq(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        /* 当前小区主叫业务受限则不处理 */
        if (VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
        {
            /* 通知SMS建立失败 */
            Mm_SndSmsRelInd(g_MmSmsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);
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

        g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;             /* 记录收到建立请求时的状态                 */
        if ( ( MM_CONST_NUM_8 > g_MmSmsEstReq.ulTi )
            || ( MM_CONST_NUM_14 < g_MmSmsEstReq.ulTi ) )
        {                                                                       /* TI不合法                                 */
            Mm_SndSmsRelInd( g_MmSmsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);/* 通知SMS建立失败                          */
        }
        else
        {                                                                       /* TI合法                                   */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg
                = MM_TRUE;

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                                    RcvXXEstReq.ulTransactionId
                = g_MmSmsEstReq.ulTi;
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulCallType
                = 0;
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulCallPri
                = 0;
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucRat = NAS_MML_GetCurrNetRatType();


            Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_SMS, MM_FALSE, &CmSvcReq);   /* 填充CM SERVICE REQUEST结构体             */
            pucCmSvcReq = Mm_ComMsgCmSvcReqOfRrEstReq( &CmSvcReq, &usMsgSize ); /* 填充CM SERVICE REQUEST 消息              */
            if ( VOS_NULL_PTR == pucCmSvcReq )
            {                                                                   /* 消息制作失败                             */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S3_E62:WARNING: MAKE MSG CM SERVICE REQUEST ERROR!");
                return;                                                         /* 返回                                     */
            }
            else
            {                                                                   /* 消息制作成功                             */
                Mm_SndRrEstReq( RRC_EST_CAUSE_ORIGIN_LOW_PRIORITY_SIGNAL,
                   MM_FALSE,
                   usMsgSize, pucCmSvcReq );                                    /* 发送消息                                 */
                MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucCmSvcReq );               /* 释放CM SERVICE REQUEST 消息结构体        */
            }
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI =
                (VOS_UINT8)g_MmSmsEstReq.ulTi;                                  /* 记录正在建立的MM连接的TI                 */
            g_MmGlobalInfo.ucMMConnEstingPD = MM_IE_PD_SMS_MSG;                 /* 记录正在建立的MM连接的PD                 */
            Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);
            Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);                                /* 通知MMC，CS域的业务已经启动              */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* 记录迁移之前的状态                       */
            Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_MM_CONNECTION);
            /*A32D11456==>*/
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E62:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_MM_CONNECTION");
            /*<==A32D11456*/
        }
    }

    NAS_MM_UpdateCsServiceBufferStatusFlg();

    NAS_MM_UpdateCsServiceConnStatusFlg();

    return;
}


VOS_VOID NAS_MM_ProcSmsEstReq_WaitForOutgoingMmConnection(VOS_VOID)
{
    MM_MSG_CM_SVC_REQ_STRU                     CmSvcReq;                            /* 要发送的CM SERVICE REQ消息               */
    VOS_UINT16                                 usMsgSize = 0;                        /* 消息长度,以字节为单位                    */
    VOS_UINT8                                 *pucCmSvcReq = 0;
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8  enCsUpdateStatus;

    enCsUpdateStatus                      = NAS_MML_GetCsUpdateStatus();

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

    if ((VOS_FALSE                               == NAS_MML_IsCsLaiChanged())
     || (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED  != enCsUpdateStatus))
    {
        NAS_MML_SetCsAttachAllowFlg(VOS_TRUE);

        if ((MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod)
            && (MM_FALSE == g_MmGlobalInfo.ucLikeB))
        {
            NAS_MM_SndGmmRegisterInit();                                /* 通知GMM进行注册                          */
        }
        else
        {
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;   /* 设置LU类型                               */
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;
            Mm_ComLuOnly();                                         /* LU REQ                                   */
        }
    }
    else
    {
        Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_SMS, MM_FALSE, &CmSvcReq); /* 填充CM SERVICE REQUEST结构体             */

        pucCmSvcReq = Mm_ComMsgCmSvcReqOfRrEstReq(&CmSvcReq, &usMsgSize); /* 填充CM SERVICE REQUEST 消息              */

        if (VOS_NULL_PTR == pucCmSvcReq)
        {                                                           /* 消息制作失败                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S4_E62:WARNING: MAKE MSG CM SERVICE REQUEST ERROR!");
            return;                                                 /* 返回                                     */
        }
        else
        {                                                           /* 消息制作成功                             */
            Mm_SndRrEstReq( RRC_EST_CAUSE_ORIGIN_LOW_PRIORITY_SIGNAL,
                            MM_FALSE,
                            usMsgSize, pucCmSvcReq );                                /* 发送消息                                 */
            MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucCmSvcReq);        /* 释放CM SERVICE REQUEST 消息结构体        */
        }

        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI
            = (VOS_UINT8)g_MmSmsEstReq.ulTi;                        /* 记录正在建立的MM连接的TI                 */
        g_MmGlobalInfo.ucMMConnEstingPD = MM_IE_PD_SMS_MSG;         /* 记录正在建立的MM连接的PD                 */
        Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);
        Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);                        /* 通知MMC，CS域的业务已经启动              */
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;         /* 记录迁移之前的状态                       */
        Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_MM_CONNECTION);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S4_E62:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_MM_CONNECTION");
    }
}


VOS_VOID Mm_Cell_S4_E62(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    NAS_MML_MISCELLANEOUS_CFG_INFO_STRU       *pstMiscellaneousCfgInfo = VOS_NULL_PTR;

    VOS_UINT8                                  ucSimCsRegStatus;
    NAS_MMCM_REL_CAUSE_ENUM_UINT32             enRelCause;

    pstMiscellaneousCfgInfo               = NAS_MML_GetMiscellaneousCfgInfo();
    enRelCause                            = NAS_MM_GetMmCmRelCause();

    if ( MM_FALSE == Mm_RcvSmsEstReq(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        /* 当前小区主叫业务受限则不处理 */
        if (VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
        {
            /* 通知SMS建立失败 */
            Mm_SndSmsRelInd(g_MmSmsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);

            return;
        }

        /* 在MM_IDLE_NO_IMSI状态时收到短信业务请求直接回复CS_SIM_INVALID,
           其他状态一般是收到系统消息后还未注册时处理缓存,暂时无法提供CS服务，需要重拨 */
        if (MM_IDLE_NO_IMSI == g_MmGlobalInfo.ucState)
        {
            Mm_SndSmsRelInd(g_MmSmsEstReq.ulTi,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SIM_INVALID);    /* 通知CC建立失败                           */

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
        /* 如果no rf，先缓存业务请求，通知mmc触发搜网 */
        ucSimCsRegStatus = NAS_MML_GetSimCsRegStatus();

        if ((VOS_FALSE == NAS_MML_GetRfAvailFlg())
         && (MM_IDLE_NO_CELL_AVAILABLE == g_MmGlobalInfo.ucState)
         && (VOS_TRUE == ucSimCsRegStatus))
        {
            NAS_MM_UpdateConnCtrlInfo(MM_CONN_CTRL_SMS);
            Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);
            return;
        }

        if ((NAS_MML_MS_MODE_PS_ONLY == NAS_MML_GetMsMode())
         && (NAS_MMC_NV_ITEM_DEACTIVE == pstMiscellaneousCfgInfo->ucPsOnlyCsServiceSupportFlg))
        {
            NAS_NORMAL_LOG(WUEPS_PID_MM, "Mm_Cell_S4_E62: PS ONLY mode and NV 9056 not active, Could not start SMS service");
            Mm_SndSmsRelInd(g_MmSmsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);
        }
        else
        {
            /*状态不为limited service或者服务域不为PS ONLY*/
            if ((NAS_MML_MS_MODE_PS_ONLY != NAS_MML_GetMsMode())
             || (MM_IDLE_LIMITED_SERVICE != g_MmGlobalInfo.ucState))
            {
                NAS_NORMAL_LOG1(WUEPS_PID_MM, "Mm_Cell_S4_E62: MM Substate ", g_MmGlobalInfo.ucState);
                /* UE在null、no imsi、WAIT FOR RR CONNECTION (IMSI DETACH)、IMSI DETACH INITIATED
                   状态无法处理sms业务 */
                Mm_SndSmsRelInd(g_MmSmsEstReq.ulTi, enRelCause);
            }
            else
            {
                g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;         /* 记录收到建立请求时的状态                 */

                if ((MM_CONST_NUM_8 > g_MmSmsEstReq.ulTi)
                    || (MM_CONST_NUM_14 < g_MmSmsEstReq.ulTi))
                {                                                                   /* TI不合法                                 */
                    Mm_SndSmsRelInd(g_MmSmsEstReq.ulTi,
                                    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);                /* 通知SMS建立失败                          */
                }
                else
                {
                    NAS_MM_ProcSmsEstReq_WaitForOutgoingMmConnection();
                }
            }

        }
    }


    NAS_MM_UpdateCsServiceConnStatusFlg();

    NAS_MM_UpdateCsServiceBufferStatusFlg();

    return;
}


VOS_VOID Mm_Cell_S10_E62(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    MM_MSG_CM_SVC_REQ_STRU              CmSvcReq;                               /* CM service request结构体                 */
    VOS_UINT8                           ucRst = MM_FALSE;
    if ( MM_FALSE == Mm_RcvSmsEstReq(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        /* ucRst = Mm_ComJudgeLimitSvc(); */
        if (MM_NO_IMSI == g_MmGlobalInfo.ucMmServiceState)
        {                                                                       /* 是受限服务                               */
            ucRst = MM_TRUE;                                                    /* 设置是受限服务                           */
        }

        if ((NAS_MML_MS_MODE_PS_ONLY != NAS_MML_GetMsMode())
         && ((MM_LIMITED_SERVICE == g_MmGlobalInfo.ucMmServiceState)
          || ( MM_ATTEMPTING_TO_UPDATE == g_MmGlobalInfo.ucMmServiceState )))
        {
            ucRst = MM_TRUE;                                                 /* 设置是受限服务                           */
        }
        /*lint -e701*/
        if ( ( MM_CONST_NUM_8 > g_MmSmsEstReq.ulTi )
            || ( MM_CONST_NUM_14 < g_MmSmsEstReq.ulTi )
            || ( MM_TRUE == ucRst ) )
        {                                                                       /* TI不合法或者在受限服务状态               */
            Mm_SndSmsRelInd( g_MmSmsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);/* 通知SMS建立失败                          */
        }
        else if (MM_CONST_NUM_0 !=
            (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1] &
            (0x01 << (g_MmSmsEstReq.ulTi - 8))))
        {                                                                       /* 要求建立的MM连接已经存在                 */
            Mm_SndSmsEstCnf( g_MmSmsEstReq.ulTi );                              /* 通知SMS，MM连接建立成功                  */
        }
        else
        {                                                                       /* TI合法                                   */
            Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_SMS, MM_FALSE, &CmSvcReq);   /* 填充CM SERVICE REQUEST结构体             */
            Mm_ComMsgCmSvcReqSnd( &CmSvcReq );                                  /* 向网侧发送建立MM连接的请求               */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                                    RcvXXEstReq.ulTransactionId
                = g_MmSmsEstReq.ulTi;                                           /* 记录重建MM连接的TI */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI =
                (VOS_UINT8)g_MmSmsEstReq.ulTi;                                  /* 记录正在建立的MM连接的TI                 */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucRat = NAS_MML_GetCurrNetRatType();
            g_MmGlobalInfo.ucMMConnEstingPD = MM_IE_PD_SMS_MSG;                 /* 记录正在建立的MM连接的PD                 */
            Mm_TimerStart(MM_TIMER_T3230);                                      /* 启动TIMER3230                            */
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* 记录迁移之前的状态                       */
            Mm_ComSetMmState(WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S10_E62:NORMAL: STATUS is WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION");
        }
        /*lint +e701*/
    }

    return;
}


VOS_VOID Mm_Cell_S11_E62(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{

    if ( MM_FALSE == Mm_RcvSmsEstReq(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S11_E62:WARNING: MMSMS_EST_REQ check fail.");
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        /* 当前小区主叫业务受限则不处理 */
        if (VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
        {
            /* 通知SMS建立失败 */
            Mm_SndSmsRelInd(g_MmSmsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);

            return;
        }

#if   (FEATURE_ON == FEATURE_LTE)
        if ( NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
        {
            if (MM_TRUE ==
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg)
            {                                                                       /* 已经存在一个保留的MM连接建立请求         */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg = MM_FALSE;
                Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                    RcvXXEstReq.ulTransactionId, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);
            }

            Mm_SndSmsRelInd(g_MmSmsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_UE_INVALID_STATE);

            return;
        }
#endif

        if (MM_TRUE ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg)
        {                                                                       /* 已经存在一个保留的MM连接建立请求         */
            Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                RcvXXEstReq.ulTransactionId, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);
        }

        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg
            = MM_TRUE;

        NAS_MML_SetCsServiceBufferStatusFlg(VOS_TRUE);

        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId
            = g_MmSmsEstReq.ulTi;
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulCallType
            = 0;
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulCallPri
            = 0;
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucRat = NAS_MML_GetCurrNetRatType();

        if (MM_IDLE_PLMN_SEARCH == g_MmGlobalInfo.ucState)
        {
            Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);
        }

    }


    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S27_E68
  FUNCTION : 在PROCESS CM SERVICE PROMPT状态下收到MMCC_PROMPT_REJ的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      04-03-08    新版作成
     3.  张志勇        2005.01.27  007037 for MM
*******************************************************************************/
VOS_VOID Mm_Cell_S27_E68(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    MM_MSG_MM_STATUS_STRU          MsgMmStatus;                                 /* MM STATUS 消息结构体                     */

    if ( MM_FALSE == Mm_RcvCcPromptRej( pRcvMsg ) )
    {                                                                           /* 消息检查结果失败                         */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        Mm_TimerStop(MM_TIMER_PROTECT_CCBS);
        Mm_TimerStop(MM_TIMER_T3240);
        MsgMmStatus.MmIeRjctCause.ucRejCause = (VOS_UINT8)(g_MmCcPromptRej.ulRefuseCause);
        Mm_ComMsgMmStatusSnd( &MsgMmStatus );

        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* 记录迁移之前的状态                       */
        if ( MM_FALSE == Mm_ComMmConnExist( ) )
        {                                                                       /* 没有存在的MM连接 */
            g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = g_MmGlobalInfo.
                ucStaOfRcvXXEstReq;                                             /* 进入空闲的状态                           */
            Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );    /* MM连接流程                               */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* 记录迁移之前的状态                       */
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S27_E68:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
            Mm_TimerStart(MM_TIMER_T3240);                                      /* 启动TIMER3240                            */
        }
        else
        {                                                                       /* 有存在的MM连接 */
            Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
            Mm_ComCheckDelayMmConn(VOS_FALSE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S27_E68:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
        }
    }

    return;

}

/*******************************************************************************
  MODULE   : Mm_Cell_S9_E47
  FUNCTION : 在WAIT FOR OUTGOING MM CONNECTION状态下收到
                RRMM_DATA_IND(CM SERVICE PROMPT)的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      04-03-08    新版作成
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E47(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    MM_MSG_MM_STATUS_STRU          MsgMmStatus;                                 /* MM STATUS 消息结构体                     */

    if (MM_LIMITED_SERVICE != g_MmGlobalInfo.ucMmServiceState)
    {
        Mm_TimerStop(MM_TIMER_T3212);                                           /* 停T3212                                  */
    }
    MsgMmStatus.MmIeRjctCause.ucRejCause =
        NAS_MML_REG_FAIL_CAUSE_MSG_TYPE_NOT_COMPATIBLE;                                   /* Service option not supported             */
    Mm_ComMsgMmStatusSnd( &MsgMmStatus );                                       /* 填充并发送 MM STATUS 消息                */

    return;
}


VOS_VOID Mm_Cell_S10_E47(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    MM_MSG_MM_STATUS_STRU          MsgMmStatus;                                 /* MM STATUS 消息结构体                     */
    VOS_UINT8                      aucClassmark2[4];


    PS_MEM_SET(aucClassmark2, 0x00, sizeof(aucClassmark2));

    MM_Fill_IE_ClassMark2(aucClassmark2);

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
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S10_E47:NORMAL: STATUS is PROCESS_CM_SERVICE_PROMPT");
        Mm_TimerStart(MM_TIMER_PROTECT_CCBS);
    }

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S27_E27
  FUNCTION : 在PROCESS CM SERVICE PROMPT状态下收到MMCC_DATA_REQ的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      04-03-08    新版作成
     6.  张志勇        2005.01.27  007037 for MM
*******************************************************************************/
VOS_VOID Mm_Cell_S27_E27(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    MMCC_DATA_REQ_STRU      *pMmCcDataReq;
    pMmCcDataReq = (MMCC_DATA_REQ_STRU*)pRcvMsg;

    if ( MM_FALSE == Mm_RcvCcDataReq(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        /*lint -e701*/
        if ( ( MM_CONST_NUM_7 > pMmCcDataReq->ulTransactionId)
           && ( MM_CONST_NUM_0 ==
           ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
           & ( 0x01 << pMmCcDataReq->ulTransactionId ) ) ) )
        {                                                                       /* 该消息中的TI小于7不存在并且TIO !=111     */
        }
        else if(((MM_CONST_NUM_7  < pMmCcDataReq->ulTransactionId)
            &&(MM_CONST_NUM_15 > pMmCcDataReq->ulTransactionId))
            && (MM_CONST_NUM_0 ==
            (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
            & (0x01 << (pMmCcDataReq->ulTransactionId - 8)))))
        {                                                                       /* 该消息中的TI大于7不存在并且TIO !=111     */
            Mm_TimerStop(MM_TIMER_PROTECT_CCBS);
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] |=
                (VOS_UINT8)( 0x01 << ( pMmCcDataReq->ulTransactionId - 8 ) );   /* 设置该TI存在                             */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* 记录迁移之前的状态                       */
            Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S27_E27:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
        }
        else
        {

        }
        Mm_SndRrDataReq(pMmCcDataReq->SendCcMsg.ulCcMsgSize,
                        &pMmCcDataReq->SendCcMsg.aucCcMsg[0],
                        RRC_NAS_MSG_PRIORTY_HIGH);                              /* 将CC的消息传送下去                       */

        /*lint +e701*/
    }

    return;

}

/*******************************************************************************
  MODULE   : Mm_Cell_S9_E69
  FUNCTION : 在WAIT FOR OUTGOING MM CONNECTION状态下
             收到RRMM_DATA_IND( SS Message)的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      04-03-11    新版作成
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E69(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    VOS_UINT8                ucTI = 0;                                          /* CC消息中的TI                             */
    RRMM_DATA_IND_STRU      *pRrDataInd = (RRMM_DATA_IND_STRU *)pRcvMsg;        /* 消息RRMM_DATA_IND的结构体指针            */
    VOS_UINT8               *pucCMMsg = VOS_NULL_PTR;                                                   /* 指针类型转换                             */
    VOS_UINT8               *pucBakCMMsg = VOS_NULL_PTR;

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

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_Cell_S9_E69:ERROR: MALLOC ERROR!");
        return;                                                                 /* 返回                                     */
    }
    pucBakCMMsg = pucCMMsg;
    PS_MEM_SET(pucCMMsg, 0, pRrDataInd->RcvNasMsg.ulNasMsgSize );              /* 初始化内存                               */
    PS_MEM_CPY (pucCMMsg, & ( pRrDataInd->RcvNasMsg.aucNasMsg[0] ),
        pRrDataInd->RcvNasMsg.ulNasMsgSize );                                   /* 得到消息内容                             */
    ucTI = ( VOS_UINT8 )( ( ( pucCMMsg[0] & 0xf0 ) >> 4 ) );                        /* 得到SS消息中的TI                         */
    if ( MM_CONST_NUM_7 > ucTI )
    {                                                                           /* 网侧建立的MM连接                         */
        /*lint -e701*/
        if ( MM_CONST_NUM_0 != (
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0]
            & ( 0x01 << ucTI ) ) )
        {                                                                       /* 该连接存在                               */
            Mm_SndSsDataInd (
                (VOS_UINT32 )ucTI,
                pRrDataInd->RcvNasMsg.ulNasMsgSize,
                pucCMMsg );                                                     /* 向SS发送MMSS_DATA_IND                    */
        }
        else
        {                                                                       /* 该连接不存在                             */
            Mm_SndSsEstInd ( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize,
            pucCMMsg );                                                         /* 向SS发送MMSS_EST_IND                     */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0] |=
                ( VOS_UINT8 )( 0x01 << ucTI );                                      /* 设置已经存在的MM连接的标志位             */

            /* 目前有三种状态会调用该函数
                WAIT_FOR_OUTGOING_MM_CONNECTION
                WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION
                MM_CONNECTION_ACTIVE
                其它两种状态保持不变。*/
            if ( g_MmGlobalInfo.ucState == WAIT_FOR_OUTGOING_MM_CONNECTION )
            {
                g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                          /* 记录迁移之前的状态                       */
                Mm_ComSetMmState(WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E69:NORMAL: STATUS is WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION");
            }


        }
        /*lint +e701*/
    }
    else if ( ( MM_CONST_NUM_7 < ucTI ) && ( MM_CONST_NUM_15 > ucTI ) )
    {                                                                           /* SS建立的MM连接                           */
        /*lint -e701*/
        if ( MM_CONST_NUM_0 != (
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1]
            & ( 0x01 << ( ucTI - 8 ) ) ) )
        {                                                                       /* 该连接存在                               */
            Mm_SndSsDataInd ( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize,
                pucCMMsg );                                                     /* 向SS发送MMSS_DATA_IND                    */
        }
        else
        {                                                                       /* 该连接不存在                             */
            Mm_SndSsEstInd ( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize,
            pucCMMsg );                                                         /* 向SS发送MMSS_EST_IND                     */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1] |=
                ( VOS_UINT8 )( 0x01 << ( ucTI - 8 ) );                              /* 设置已经存在的MM连接的标志位             */
            Mm_TimerStop( MM_TIMER_T3230 );                                     /* 停T3230                                  */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* 记录迁移之前的状态                       */
            Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E69:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
            Mm_ComCheckDelayMmConn( MM_FALSE );
        }
        /*lint +e701*/
    }
    else
    {

    }
    MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucBakCMMsg );                                /* 释放申请的消息                           */

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S9_E70
  FUNCTION : 在WAIT FOR OUTGOING MM CONNECTION状态下
             收到RRMM_DATA_IND( SMS Message)的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      04-03-11    新版作成
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E70(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    VOS_UINT8                ucTI = 0;                                          /* SMS消息中的TI                            */
    RRMM_DATA_IND_STRU      *pRrDataInd = (RRMM_DATA_IND_STRU *)pRcvMsg;        /* 消息RRMM_DATA_IND的结构体指针            */
    VOS_UINT8               *pucCMMsg = VOS_NULL_PTR;                           /* 指针类型转换                             */
    VOS_UINT8               *pucBakCMMsg = VOS_NULL_PTR;

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

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_Cell_S9_E70:ERROR: MALLOC ERROR!");
        return;                                                                 /* 返回                                     */
    }
    pucBakCMMsg = pucCMMsg;
    PS_MEM_SET(pucCMMsg, 0, pRrDataInd->RcvNasMsg.ulNasMsgSize );              /* 初始化内存                               */
    PS_MEM_CPY (pucCMMsg, & ( pRrDataInd->RcvNasMsg.aucNasMsg[0] ),
        pRrDataInd->RcvNasMsg.ulNasMsgSize );                                   /* 得到消息内容                             */
    ucTI = ( VOS_UINT8 )( ( ( pucCMMsg[0] & 0xf0 ) >> 4 ) );                        /* 得到SMS消息中的TI                        */
    if ( MM_CONST_NUM_7 > ucTI )
    {                                                                           /* 网侧建立的MM连接                         */
        /*lint -e701*/
        if ( MM_CONST_NUM_0 != (
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0]
            & ( 0x01 << ucTI ) ) )
        {                                                                       /* 该连接存在                               */
            Mm_SndSmsDataInd(
                (VOS_UINT32 )ucTI,
                pRrDataInd->RcvNasMsg.ulNasMsgSize,
                pucCMMsg );                                                     /* 向SMS发送MMSMS_DATA_IND                  */
        }
        else
        {                                                                       /* 该连接不存在                             */
            Mm_SndSmsEstInd( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize,
            pucCMMsg );                                                         /* 向SMS发送MMSMS_EST_IND                   */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0] |=
                ( VOS_UINT8 )( 0x01 << ucTI );                                      /* 设置已经存在的MM连接的标志位             */

            /* 目前有三种状态会调用该函数
                WAIT_FOR_OUTGOING_MM_CONNECTION
                WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION
                MM_CONNECTION_ACTIVE
                其它两种状态保持不变。*/
            if ( g_MmGlobalInfo.ucState == WAIT_FOR_OUTGOING_MM_CONNECTION )
            {
                g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                          /* 记录迁移之前的状态                       */
                Mm_ComSetMmState(WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E70:NORMAL: STATUS is WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION");
            }


        }
        /*lint +e701*/
    }
    else if ( ( MM_CONST_NUM_7 < ucTI ) && ( MM_CONST_NUM_15 > ucTI ) )
    {                                                                           /* SMS建立的MM连接                          */
        /*lint -e701*/
        if ( MM_CONST_NUM_0 != (
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]
            & ( 0x01 << ( ucTI - 8 ) ) ) )
        {                                                                       /* 该连接存在                               */
            Mm_SndSmsDataInd( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize,
                pucCMMsg );                                                     /* 向SMS发送MMSMS_DATA_IND                  */
        }
        else
        {                                                                       /* 该连接不存在                             */
            Mm_SndSmsEstInd( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize,
            pucCMMsg );                                                         /* 向SMS发送MMSMS_EST_IND                   */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1] |=
                ( VOS_UINT8 )( 0x01 << ( ucTI - 8 ) );                              /* 设置已经存在的MM连接的标志位             */
            Mm_TimerStop( MM_TIMER_T3230 );                                     /* 停T3230                                  */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* 记录迁移之前的状态                       */
            Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E70:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
            Mm_ComCheckDelayMmConn( MM_FALSE );
        }
        /*lint +e701*/
    }
    else
    {

    }
    MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucBakCMMsg);                            /* 释放申请的消息                           */

    return;
}


VOS_VOID Mm_Cell_S11_E69(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{

    VOS_UINT8   ucTI = 0;                                                           /* SS消息中的TI                             */
    RRMM_DATA_IND_STRU *pRrDataInd = ( RRMM_DATA_IND_STRU *) pRcvMsg;           /* 消息RRMM_DATA_IND的结构体指针            */
    VOS_UINT8   *pucCMMsg = VOS_NULL_PTR;                                                   /* 指针类型转换                             */
    VOS_UINT8   *pucBakCMMsg = VOS_NULL_PTR;

    Mm_TimerStop( MM_TIMER_T3240 );                                             /* 停TIMER3240                              */
    pucCMMsg = (VOS_UINT8 *)MM_MEM_ALLOC(
                           VOS_MEMPOOL_INDEX_MM,
                           pRrDataInd->RcvNasMsg.ulNasMsgSize,
                           WUEPS_MEM_NO_WAIT);                                  /* 申请内存                                 */
    if( VOS_NULL_PTR == pucCMMsg )
    {                                                                           /* 内存申请失败                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S11_E69:WARNING: MALLOC ERROR!");
        return;                                                                 /* 返回                                     */
    }
    pucBakCMMsg = pucCMMsg;
    PS_MEM_SET(pucCMMsg, 0, pRrDataInd->RcvNasMsg.ulNasMsgSize );              /* 初始化内存                               */
    PS_MEM_CPY (pucCMMsg, & ( pRrDataInd->RcvNasMsg.aucNasMsg[0] ),
        pRrDataInd->RcvNasMsg.ulNasMsgSize );                                   /* 得到消息内容                             */
    /*lint -e701*/
    ucTI = ( VOS_UINT8 )( ( ( pucCMMsg[0] & 0xf0 ) >> 4 ) );                        /* 得到SS消息中的TI                         */
    if ( MM_CONST_NUM_7 > ucTI )
    {                                                                           /* 网侧建立的MM连接                         */
        Mm_SndSsEstInd ( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize, pucCMMsg );  /* 向SS发送MMSS_EST_IND                     */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0] |=
        ( VOS_UINT8 )( 0x01 << ucTI );                                              /* 设置已经存在的MM连接的标志位             */
        g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                   /* 记录迁移之前的状态                       */
        Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S11_E69:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
        Mm_ComCheckDelayMmConn( MM_FALSE );

    }
    else if ( ( MM_CONST_NUM_7 < ucTI ) && ( MM_CONST_NUM_15 > ucTI ) )
    {                                                                           /* SS建立的MM连接                           */
        Mm_SndSsEstInd ( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize, pucCMMsg );  /* 向SS发送MMSS_EST_IND                     */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1] |=
            ( VOS_UINT8 )( 0x01 << ( ucTI - 8 ) );                                  /* 设置已经存在的MM连接的标志位             */
        g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                   /* 记录迁移之前的状态                       */
        Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S11_E69:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
        Mm_ComCheckDelayMmConn( MM_FALSE );
    }
    else
    {
    }
    /*lint +e701*/
    MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucBakCMMsg);                                /* 释放申请的消息                           */

    NAS_MM_UpdateCsServiceConnStatusFlg();

    return;
}


VOS_VOID Mm_Cell_S11_E70(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{

    VOS_UINT8   ucTI = 0;                                                           /* SMS消息中的TI                            */
    RRMM_DATA_IND_STRU *pRrDataInd = ( RRMM_DATA_IND_STRU *) pRcvMsg;           /* 消息RRMM_DATA_IND的结构体指针            */
    VOS_UINT8   *pucCMMsg = VOS_NULL_PTR;                                       /* 指针类型转换                             */
    VOS_UINT8   *pucBakCMMsg = VOS_NULL_PTR;

    Mm_TimerStop( MM_TIMER_T3240 );                                             /* 停TIMER3240                              */
    pucCMMsg = (VOS_UINT8 *)MM_MEM_ALLOC(
                           VOS_MEMPOOL_INDEX_MM,
                           pRrDataInd->RcvNasMsg.ulNasMsgSize,
                           WUEPS_MEM_NO_WAIT);                                  /* 申请内存                                 */
    if( VOS_NULL_PTR == pucCMMsg )
    {                                                                           /* 内存申请失败                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S11_E70:WARNING: MALLOC ERROR!");
        return;                                                                 /* 返回                                     */
    }
    pucBakCMMsg = pucCMMsg;
    PS_MEM_SET(pucCMMsg, 0, pRrDataInd->RcvNasMsg.ulNasMsgSize );              /* 初始化内存                               */
    PS_MEM_CPY (pucCMMsg, & ( pRrDataInd->RcvNasMsg.aucNasMsg[0] ),
        pRrDataInd->RcvNasMsg.ulNasMsgSize );                                   /* 得到消息内容                             */
    ucTI = ( VOS_UINT8 )( ( ( pucCMMsg[0] & 0xf0 ) >> 4 ) );                        /* 得到SMS消息中的TI                        */
    if ( MM_CONST_NUM_7 > ucTI )
    {                                                                           /* 网侧建立的MM连接                         */
        Mm_SndSmsEstInd( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize,
        pucCMMsg );                                                             /* 向SMS发送MMSMS_EST_IND                   */

        /*lint -e701*/
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0] |=
            ( VOS_UINT8 )( 0x01 << ucTI );                                          /* 设置已经存在的MM连接的标志位             */
        /*lint +e701*/
        g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                   /* 记录迁移之前的状态                       */
        Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S11_E70:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
        Mm_ComCheckDelayMmConn( MM_FALSE );
    }
    else if ( ( MM_CONST_NUM_7 < ucTI ) && ( MM_CONST_NUM_15 > ucTI ) )
    {                                                                           /* SMS建立的MM连接                          */
        Mm_SndSmsEstInd( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize,
        pucCMMsg );                                                             /* 向SMS发送MMSMS_EST_IND                   */

        /*lint -e701*/
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1] |=
            ( VOS_UINT8 )( 0x01 << ( ucTI - 8 ) );                                  /* 设置已经存在的MM连接的标志位             */
        /*lint +e701*/

        g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                   /* 记录迁移之前的状态                       */
        Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S11_E70:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
        Mm_ComCheckDelayMmConn( MM_FALSE );
    }
    else
    {
    }
    MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucBakCMMsg);                            /* 释放申请的消息                           */

    NAS_MM_UpdateCsServiceConnStatusFlg();


    return;
}

VOS_VOID Mm_Cell_S10_E67(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{
    MMSS_DATA_REQ_STRU      *pMmSsDataReq;
    pMmSsDataReq = ( MMSS_DATA_REQ_STRU* )pRcvMsg;

    if ( MM_FALSE == Mm_RcvSsDataReq(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        /*lint -e701*/
        if ( ( ( MM_CONST_NUM_7 > pMmSsDataReq->ulTi )
            && ( MM_CONST_NUM_0 !=
            ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0]
            & ( 0x01 << pMmSsDataReq->ulTi ) ) ) )
            || ( ( MM_CONST_NUM_7 < pMmSsDataReq->ulTi )
            && ( MM_CONST_NUM_0 !=
            ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1]
            & ( 0x01 << ( pMmSsDataReq->ulTi - 8 ) ) ) ) ) )
        {                                                                       /* 该TI的MM连接存在                         */
            Mm_SndRrDataReq( pMmSsDataReq->SsMsg.ulSsMsgSize,
                &pMmSsDataReq->SsMsg.aucSsMsg[0],
                RRC_NAS_MSG_PRIORTY_HIGH);                                      /* 将SS的消息传送下去                       */
        }
        else
        {                                                                       /* 该TI的MM连接不存在                       */
            Mm_SndSsRelInd( pMmSsDataReq->ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);                               /* 通知SS建立失败                           */
        }

        /*lint +e701*/
    }

    return;
}


VOS_VOID Mm_Cell_S10_E64(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{
    MMSMS_DATA_REQ_STRU      *pMmSmsDataReq;
    pMmSmsDataReq = ( MMSMS_DATA_REQ_STRU* )pRcvMsg;

    if ( MM_FALSE == Mm_RcvSmsDataReq(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        /*lint -e701*/
        if ( ( ( MM_CONST_NUM_7 > pMmSmsDataReq->ulTi )
            && ( MM_CONST_NUM_0 !=
            ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0]
            & ( 0x01 << pMmSmsDataReq->ulTi ) ) ) )
            || ( ( MM_CONST_NUM_7 < pMmSmsDataReq->ulTi )
            && ( MM_CONST_NUM_0 !=
            ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]
            & ( 0x01 << ( pMmSmsDataReq->ulTi - 8 ) ) ) ) ) )
        {                                                                       /* 该TI的MM连接存在                         */
            Mm_SndRrDataReq( pMmSmsDataReq->SmsMsg.ulNasMsgSize,
                &pMmSmsDataReq->SmsMsg.aucNasMsg[0],
                RRC_NAS_MSG_PRIORTY_LOW);                                       /* 将SMS的消息传送下去                      */
        }
        else
        {                                                                       /* 该TI的MM连接不存在                       */
            Mm_SndSmsRelInd(pMmSmsDataReq->ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);/* 通知SMS建立失败                          */
        }

        /*lint +e701*/
    }

    return;
}

VOS_VOID Mm_Cell_S9_E25(
    VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
)
{
    if ( MM_FALSE == Mm_RcvCcRelReq( pRcvMsg ) )
    {                                                                           /* 消息检查结果失败                         */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        if ( ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
          && ( ( ( MMCC_RELEASE_SPECIFIC == g_MmCcRelReq.ulReleaseType )
              && ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                                RcvXXEstReq.ulTransactionId
            == g_MmCcRelReq.ulTransactionId ) )
            || ( MMCC_RELEASE_ALL == g_MmCcRelReq.ulReleaseType ) ) )
        {                                                                       /* 要求释放的MM连接是被缓存的       */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;                                                     /* 设置不存在缓存的MM连接 */
        }
        else
        {
            /* 这个值不会报上去，因为CC在发MMCC_REL_REQ时，主叫时CC会给CALL发MNCC_REL_IND,MNCC_REL_CNF,MNCC_REJ_IND
               如果是被叫，setup检查失败，ring还没报上去，不会有CEND上报 */
            Mm_SndCcRelInd( g_MmCcRelReq.ulTransactionId, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_REL_REQ);/* 通知CC指定释放的MM连接不存在             */
        }

        NAS_MM_UpdateCsServiceBufferStatusFlg();

     }

    return;
}


VOS_VOID Mm_Cell_S12_E25(VOS_VOID  *pRcvMsg)
{
    if ( MM_FALSE == Mm_RcvCcRelReq( pRcvMsg ) )
    {                                                                           /* 消息检查结果失败                         */
    }
    else
    {
        if ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI ==
                g_MmCcRelReq.ulTransactionId )
        {
            /* 终止的MM连接建立是正在建立的,如果接入技术相同则发送rel req */
            if (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucRat == NAS_MML_GetCurrNetRatType())
            {
                Mm_SndRrRelReq(RRC_CELL_UNBARRED);
                g_MmGlobalInfo.bWaitingEstCnf = VOS_FALSE;
                g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = g_MmGlobalInfo.ucStaOfRcvXXEstReq;
                Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
                Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL);
                NAS_NORMAL_LOG(WUEPS_PID_MM, "Mm_Cell_S12_E26:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
                Mm_TimerStart(MM_TIMER_T3240);
            }
            else
            {
                Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
            }

            Mm_TimerStop( MM_TIMER_PROTECT_SIGNALLING );

            /* 清除MM相关全局变量 */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI  = NO_MM_CONN_ESTING;
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;

        }
        else
        {
            if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
             && (g_MmCcRelReq.ulTransactionId ==
                     g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId))
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;
                Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);
                NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
            }
        }

#if (FEATURE_ON == FEATURE_LTE)
        if (VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist())
        {
            NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

            NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
        }
#endif

        NAS_MM_UpdateCsServiceBufferStatusFlg();
    }

    return;
}




VOS_VOID Mm_Cell_S1_E63(VOS_VOID    *pRcvMsg)
{
    if (MM_FALSE == Mm_RcvSmsRelReq(pRcvMsg))
    {
    }
    else
    {
        /*如果存在SMS或者SS的缓存，需要清除*/
        if ( (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg)
          && (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId == g_MmSmsRelReq.ulTi) )
        {
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg = MM_FALSE;
        }

        NAS_MM_UpdateCsServiceBufferStatusFlg();
    }
}


VOS_VOID Mm_Cell_S32_E63(
    VOS_VOID                           *pRcvMsg
)
{
    if (WAIT_FOR_OUTGOING_MM_CONNECTION == g_MmGlobalInfo.ucSuspendPreState)
    {
        Mm_Cell_S32_DataTransfer(pRcvMsg);
        return;
    }

    if (MM_FALSE == Mm_RcvSmsRelReq(pRcvMsg))
    {
    }
    else
    {
        /*如果存在SMS或者SS的缓存，需要清除*/
        if ( (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg)
          && (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId == g_MmSmsRelReq.ulTi) )
        {
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg = MM_FALSE;
        }

        NAS_MM_SndRrMmServiceAbortNotify(WUEPS_PID_WRR);
        NAS_MM_SndRrMmServiceAbortNotify(UEPS_PID_GAS);

        NAS_MM_UpdateCsServiceBufferStatusFlg();
    }
}






VOS_VOID Mm_Cell_S10_E63(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{
    if ( MM_FALSE == Mm_RcvSmsRelReq(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        /*lint -e701*/
        if ( ( MM_CONST_NUM_7 > g_MmSmsRelReq.ulTi ) &&
            ( MM_CONST_NUM_0 !=
            ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0]
            & ( 0x01 << g_MmSmsRelReq.ulTi ) ) ) )
        {                                                                       /* TI小于7并且该MM连接存在                  */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0] &=
                ~(VOS_UINT8)( 0x01 << g_MmSmsRelReq.ulTi );                         /* 清除该标志位                             */
        }
        if ( ( MM_CONST_NUM_7 < g_MmSmsRelReq.ulTi ) &&
            ( MM_CONST_NUM_15 > g_MmSmsRelReq.ulTi ) &&
            ( MM_CONST_NUM_0 !=
            ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]
            & ( 0x01 << ( g_MmSmsRelReq.ulTi - 8 ) ) ) ) )
        {                                                                       /* TI小于7并且该MM连接存在                  */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1] &=
                ~(VOS_UINT8)( 0x01 << ( g_MmSmsRelReq.ulTi - 8 ) );                 /* 清除该标志位                             */
        }
        /*lint +e701*/
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
            g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                g_MmGlobalInfo.ucStaOfRcvXXEstReq;                              /* 进入空闲的状态                           */
            Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );    /* MM连接流程                               */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* 记录迁移之前的状态                       */
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S10_E63:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
            Mm_TimerStart(MM_TIMER_T3240);                                      /* 启动TIMER3240                            */
        }
    }

    NAS_MM_UpdateCsServiceConnStatusFlg();

    return;
}

VOS_VOID Mm_Cell_S12_E63(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    if ( MM_FALSE == Mm_RcvSmsRelReq(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S12_E63:WARNING:  CHECK PRIMITIVE ERROR!");
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        if ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI ==
            g_MmSmsRelReq.ulTi )
        {
            if (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucRat == NAS_MML_GetCurrNetRatType())
            {
                /* 终止的MM连接建立是正在建立的             */
                Mm_SndRrRelReq(RRC_CELL_UNBARRED);

                g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                    g_MmGlobalInfo.ucStaOfRcvXXEstReq;                              /* 返回到接收到建立MM连接请求时的状态       */
                Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
                Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );    /* MM连接流程                               */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E63:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
                Mm_TimerStart(MM_TIMER_T3240);                                      /* 启动TIMER3240                            */
            }
            else
            {
                Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
            }

            Mm_TimerStop( MM_TIMER_PROTECT_SIGNALLING );
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI =
                NO_MM_CONN_ESTING;                                              /* 清除正在建立的MM连接的标志               */

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg = MM_FALSE;
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* 记录迁移之前的状态                       */
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
        }

        NAS_MM_UpdateCsServiceBufferStatusFlg();
    }

    return;
}

VOS_VOID Mm_Cell_S16_E63(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    if ( MM_FALSE == Mm_RcvSmsRelReq(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        /*lint -e701*/
        if ( ( MM_CONST_NUM_7 > g_MmSmsRelReq.ulTi ) &&
            ( MM_CONST_NUM_0 !=
            ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0]
            & ( 0x01 << g_MmSmsRelReq.ulTi ) ) ) )
        {                                                                       /* TI小于7并且该MM连接存在                  */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0] &=
                ~(VOS_UINT8)( 0x01 << g_MmSmsRelReq.ulTi );                     /* 清除该标志位                             */
        }
        if ( ( MM_CONST_NUM_7 < g_MmSmsRelReq.ulTi ) &&
            ( MM_CONST_NUM_15 > g_MmSmsRelReq.ulTi ) &&
            ( MM_CONST_NUM_0 !=
            ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]
            & ( 0x01 << ( g_MmSmsRelReq.ulTi - 8 ) ) ) ) )
        {                                                                       /* TI小于7并且该MM连接存在                  */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1] &=
                ~(VOS_UINT8)( 0x01 << ( g_MmSmsRelReq.ulTi - 8 ) );             /* 清除该标志位                             */
        }
        /*lint +e701*/
        if ( ( MM_TRUE ==
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                                    RcvXXEstReq.ucFlg )
                && ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                RcvXXEstReq.ulTransactionId == g_MmSmsRelReq.ulTi ) )
        {
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg
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
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S16_E63:NORMAL: STATUS is WAIT_FOR_OUTGOING_MM_CONNECTION");
        }
    }

    NAS_MM_UpdateCsServiceConnStatusFlg();

    NAS_MM_UpdateCsServiceBufferStatusFlg();

    return;
}


VOS_VOID Mm_Cell_S3_E49(
    VOS_VOID                           *pRcvMsg
)
{
    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;

    Mm_ComSetMmState(MM_IDLE_PLMN_SEARCH);

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E49:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");

    return;
}


VOS_VOID Mm_Cell_S11_E49(
    VOS_VOID                           *pRcvMsg
)
{

    Mm_SndRrRelReq(RRC_CELL_UNBARRED);                                      /* 向RRC发送RRMM_REL_REQ(CS域)              */

    Mm_TimerStop(MM_TIMER_T3240);
    Mm_TimerStop(MM_TIMER_T3218);
    Mm_ComDelRandRes();

    if ( (MM_LU_PROC == g_MmGlobalInfo.ucProc)
      && (NAS_MML_REG_FAIL_CAUSE_NULL == g_MmGlobalInfo.usCauseVal) )
    {
        NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);

        if (MM_DETACH_NEED_DELAY == g_MmGlobalInfo.ucDetachType)
        {
            Mm_TimerStop(MM_TIMER_PROTECT_DETACH);
            g_MmGlobalInfo.ucDetachType = MM_DETACH_TYPE_BUTT;
            Mm_Cell_S3_E23(VOS_NULL_PTR);
        }

        Mm_ComProcCauseClear();
    }
    else if ( (MM_MM_CONN_PROC == g_MmGlobalInfo.ucProc)
           && (NAS_MML_REG_FAIL_CAUSE_NULL == g_MmGlobalInfo.usCauseVal) )
    {
        Mm_ComProcCauseClear();
    }
    else
    {
        Mm_ComProcCauseProcess();
    }

    Mm_TimerStart(MM_TIMER_WAIT_CONNECT_REL);

    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;

    Mm_ComSetMmState(MM_IDLE_PLMN_SEARCH);

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S11_E49:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");

    return;
}


VOS_VOID Mm_Cell_S9_E49(
    VOS_VOID                           *pRcvMsg
)
{

    Mm_SndRrRelReq(RRC_CELL_UNBARRED);                                      /* 向RRC发送RRMM_REL_REQ(CS域)              */

    Mm_TimerStop(MM_TIMER_T3230);

    Mm_ComDelRandRes();

    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;

    Mm_ComSetMmState(MM_IDLE_PLMN_SEARCH);

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E49:NORMAL: STATUS is WAIT FOR OUTGOING MM CONNECTION");

    return;
}


VOS_VOID Mm_Cell_S10_E49(
    VOS_VOID                           *pRcvMsg
)
{

    Mm_SndRrRelReq(RRC_CELL_UNBARRED);                                      /* 向RRC发送RRMM_REL_REQ(CS域)              */

    Mm_ComDelRandRes();

    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;

    Mm_ComSetMmState(MM_IDLE_PLMN_SEARCH);

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S10_E49:NORMAL: STATUS is MM CONNECTION ACTIVE");

    return;
}



VOS_VOID Mm_Cell_S12_E49(
    VOS_VOID                           *pRcvMsg
)
{

    Mm_SndRrRelReq(RRC_CELL_UNBARRED);                                      /* 向RRC发送RRMM_REL_REQ(CS域)              */

    Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

    Mm_ComDelRandRes();

    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;

    Mm_ComSetMmState(MM_IDLE_PLMN_SEARCH);

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E49:NORMAL: STATUS is WAIT FOR RR CONNECTION");

    return;
}



VOS_VOID Mm_Cell_S22_E49(
    VOS_VOID                           *pRcvMsg
)
{
    /* 向RRC发送RRMM_REL_REQ(CS域) */
    Mm_SndRrRelReq(RRC_CELL_UNBARRED);

    Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

    Mm_TimerStart(MM_TIMER_WAIT_CONNECT_REL);

    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;

    Mm_ComSetMmState(MM_IDLE_PLMN_SEARCH);

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S22_E49:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_LOCATION_UPDATING");

    return;
}


VOS_VOID Mm_Cell_S23_E49(
    VOS_VOID                           *pRcvMsg
)
{
    /* 向RRC发送RRMM_REL_REQ(CS域) */
    Mm_SndRrRelReq(RRC_CELL_UNBARRED);

    Mm_TimerStop(MM_TIMER_T3211);

    Mm_TimerStart(MM_TIMER_WAIT_CONNECT_REL);


    /* 回复MMCMM_ATTACH_CNF的操作,清除等待ATTACH结果标志位 */
    if (MM_WAIT_CS_ATTACH == (g_MmGlobalInfo.stAttachInfo.enAttachType
                            & MM_WAIT_CS_ATTACH))
    {
        NAS_MM_SndMmcAttachCnf();
    }
    g_MmGlobalInfo.stAttachInfo.enAttachType = MM_WAIT_NULL_ATTACH;

    NAS_MM_ClearAuthInfo();

    g_MmSubLyrShare.MmShare.ucCsIntegrityProtect  = NAS_MML_RRC_INTEGRITY_PROTECT_DEACTIVE;

    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;

    /* 认为本次LAU失败 */
    NAS_MM_LocationUpdateAttemptCounter(NAS_MML_REG_FAIL_CAUSE_RR_CONN_ABORT);         /* 调用RAU attempt counter的处理            */

    g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_FALSE;


    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;

    Mm_ComSetMmState(MM_IDLE_PLMN_SEARCH);

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S23_E49:NORMAL: STATUS is LOCATION_UPDATING_INITIATED");

    return;
}


VOS_VOID Mm_Cell_S24_E49(
    VOS_VOID                           *pRcvMsg
)
{
    /* 向RRC发送RRMM_REL_REQ(CS域) */
    Mm_SndRrRelReq(RRC_CELL_UNBARRED);

    Mm_TimerStop(MM_TIMER_T3240);
    Mm_TimerStop(MM_TIMER_T3218);

    Mm_ComDelRandRes();
    Mm_ComProcCauseProcess();

    Mm_TimerStart(MM_TIMER_WAIT_CONNECT_REL);

    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;

    Mm_ComSetMmState(MM_IDLE_PLMN_SEARCH);

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S24_E49:NORMAL: STATUS is LOCATION_UPDATE_REJECTED");

    return;
}


VOS_VOID Mm_Cell_S25_E49(
    VOS_VOID                           *pRcvMsg
)
{
    if (MM_DETACH_CS_POWEROFF == g_MmGlobalInfo.ucDetachType)
    {
        return;
    }

    /* 向RRC发送RRMM_REL_REQ(CS域) */
    Mm_SndRrRelReq(RRC_CELL_UNBARRED);

    Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

    Mm_TimerStop(MM_TIMER_PROTECT_DETACH);

    /* 判断等待标志是否存在，如果存在则发送MMCMM_DETACH CNF */
    if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                 & MM_WAIT_CS_DETACH))
    {
        NAS_MM_SndMmcDetachCnf(MM_DETACHED);

        /* 清除等待标志 */
        g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
    }

    Mm_TimerStart(MM_TIMER_WAIT_CONNECT_REL);

    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;

    Mm_ComSetMmState(MM_IDLE_PLMN_SEARCH);

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S25_E49:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_IMSI_DETACH");

    return;
}


VOS_VOID Mm_Cell_S26_E49(
    VOS_VOID                           *pRcvMsg
)
{
    if (MM_DETACH_CS_POWEROFF == g_MmGlobalInfo.ucDetachType)
    {
        return;
    }

    /* 向RRC发送RRMM_REL_REQ(CS域) */
    Mm_SndRrRelReq(RRC_CELL_UNBARRED);

    Mm_TimerStop(MM_TIMER_T3220);

    Mm_TimerStop(MM_TIMER_PROTECT_DETACH);

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

    g_MmGlobalInfo.ucPowerOnFlg = MM_TRUE;

    NAS_EventReport(WUEPS_PID_MM, NAS_OM_EVENT_IMSI_DETACH_IND,
                    VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    Mm_TimerStart(MM_TIMER_WAIT_CONNECT_REL);

    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;

    Mm_ComSetMmState(MM_IDLE_PLMN_SEARCH);

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S26_E49:NORMAL: STATUS is IMSI_DETACH_INITIATED");

    return;
}


VOS_VOID Mm_Cell_S27_E87(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    MMCC_DATA_REQ_STRU *pstMsg;
    VOS_UINT8                           ucTi;

    pstMsg = (MMCC_DATA_REQ_STRU *)pRcvMsg;

    ucTi = (VOS_UINT8)pstMsg->ulTransactionId;
    /*lint -e701*/
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]  =
    (VOS_UINT8)( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
               | (0x01 << (ucTi - 0x08)) );
    /*lint +e701*/
    Mm_TimerStop(MM_TIMER_PROTECT_CCBS);
    Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
    Mm_SndRrDataReq(pstMsg->SendCcMsg.ulCcMsgSize,
                            &pstMsg->SendCcMsg.aucCcMsg[0],
                            RRC_NAS_MSG_PRIORTY_HIGH);

    Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);
    NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);

    Mm_ComCheckDelayMmConn(VOS_FALSE);

    NAS_MM_UpdateCsServiceConnStatusFlg();
}


VOS_VOID Mm_Cell_S3_E88(
    VOS_VOID                           *pRcvMsg
)
{
    MMCMM_W_AC_INFO_CHANGE_IND_STRU  *pstAcInfoChangeInd = VOS_NULL_PTR;

    pstAcInfoChangeInd = (MMCMM_W_AC_INFO_CHANGE_IND_STRU*)pRcvMsg;

    /* 当前小区变为注册受限，需要迁移MM状态 */
    if (NAS_MML_RESTRICTION_UNBAR_TO_BAR == pstAcInfoChangeInd->enCsRestrictRegisterChange)
    {
        g_MmGlobalInfo.ucMmServiceState = NAS_MM_GetLauUptNeededCsSrvStatus();
        Mm_ComSetMmState(MM_IDLE_LOCATION_UPDATE_NEEDED);

    }
}


VOS_VOID Mm_Cell_S6_E88(
    VOS_VOID                           *pRcvMsg
)
{
    MMCMM_W_AC_INFO_CHANGE_IND_STRU    *pstAcInfoChangeInd = VOS_NULL_PTR;

    pstAcInfoChangeInd  = (MMCMM_W_AC_INFO_CHANGE_IND_STRU*)pRcvMsg;

    /* 当前小区从CS注册受限变为不受限 */
    if (NAS_MML_RESTRICTION_BAR_TO_UNBAR == pstAcInfoChangeInd->enCsRestrictRegisterChange)
    {
        /* 用户设置不支持CS */
        if (VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
        {
            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
            return;
        }

        /* 当前网络在禁止列表中 */
        if ((MMCMM_NO_FORBIDDEN != g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)
         && (MMCMM_FORBIDDEN_PLMN_FOR_GPRS != g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
        {
            g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;               /* 设置服务状态                             */
            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
            return;
        }

        if (VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNtMod))
        {
            /* 网络PS注册受限 */
            if (VOS_TRUE == NAS_MML_GetPsRestrictRegisterFlg())
            {                                                                   /* RAC为0的场合                             */
                NAS_MM_ProcCsAcChgRegisterNetModeII();
            }
            /* 网络GPRS不支持或GPRS禁止 */
            else if ((MM_UNSUPPORT_GPRS == g_MmGlobalInfo.usRac)
             || (MMCMM_FORBIDDEN_PLMN_FOR_GPRS == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
            {
                NAS_MM_SetLikeBFlg();
                NAS_MM_ProcCsAcChgRegisterNetModeII();
            }
            else
            {
            }
        }
        else
        {
            NAS_MM_ProcCsAcChgRegisterNetModeII();
        }
    }
}


VOS_VOID Mm_Cell_S9_E88(
    VOS_VOID                           *pRcvMsg
)
{
    MMCMM_W_AC_INFO_CHANGE_IND_STRU            *pstAcInfoChangeInd = VOS_NULL_PTR;

    pstAcInfoChangeInd  = (MMCMM_W_AC_INFO_CHANGE_IND_STRU*)pRcvMsg;

    /* 如果当前CS注册变为受限，需要重新设置建链前状态 */
    if (NAS_MML_RESTRICTION_UNBAR_TO_BAR == pstAcInfoChangeInd->enCsRestrictRegisterChange)
    {
        if (MM_IDLE_NO_IMSI != g_MmGlobalInfo.ucStaOfRcvXXEstReq)
        {
            g_MmGlobalInfo.ucStaOfRcvXXEstReq       = MM_IDLE_LOCATION_UPDATE_NEEDED;
            g_MmGlobalInfo.ucStaAfterWaitForNwkCmd  = MM_IDLE_LOCATION_UPDATE_NEEDED;
        }
    }

    /* 如果当前CS注册变为不受限，需要重新设置建链前状态 */
    if (NAS_MML_RESTRICTION_BAR_TO_UNBAR == pstAcInfoChangeInd->enCsRestrictRegisterChange)
    {
        NAS_MM_UpdateMmStateCsRegRestrictBarToUnbar();
    }

    if (VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNtMod))
    {
        /* 网络模式I，手机模式A，PS注册从受限变为不受限 */
        if ((NAS_MML_RESTRICTION_BAR_TO_UNBAR == pstAcInfoChangeInd->enPsRestrictRegisterChange)
         && (MM_TRUE == g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg ))
        {
            g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_FALSE;
        }
    }

}

#if (FEATURE_ON == FEATURE_LTE)

VOS_VOID Mm_Cell_S3_E89(
    VOS_VOID                           *pRcvMsg
)
{
    VOS_UINT8                           ucPsRestrictionFlg;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrNetRatType;
    VOS_UINT32                          ulT3412ExpNeedRegFlg;

    enCurrNetRatType     = NAS_MML_GetCurrNetRatType();
    ulT3412ExpNeedRegFlg = NAS_MM_IsT3412ExpiredNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                           NAS_MML_GetTinType(), NAS_MML_GetT3412Status());
    ucPsRestrictionFlg   = NAS_MML_GetPsRestrictRegisterFlg();

    /* 3GPP 24.008中4.4.1  Location updating procedure章节描述如下：
        The normal location updating procedure shall also be started if the MS is
        configured to use CS fallback and SMS over SGs, or SMS over SGs only,
        and the TIN indicates "RAT-related TMSI",
        - when the periodic tracking area update timer T3412 expires and the
        network operates in network operation mode II or III
    */
    if ((VOS_FALSE == ulT3412ExpNeedRegFlg)
     || (NAS_MML_NET_RAT_TYPE_LTE == enCurrNetRatType))
    {
        return;
    }

    /* 网络模式I下，如果GMM已经注册或者正在进行注册，无需处理 */
    if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
     && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod))
    {
        if (VOS_TRUE == NAS_GMM_IsRegisteredOrRegistering())
        {
            return;
        }
    }

    /* 3GPP 24.008中4.4.1  Location updating procedure章节描述如下：
       The normal location updating procedure shall also be started if the MS is
       configured to use CS fallback and SMS over SGs, or SMS over SGs only,
       and the TIN indicates "RAT-related TMSI",
       - when the periodic tracking area update timer T3412 expires and the
       network operates in network operation mode II or III
    */
    if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
     && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod)
     && (VOS_FALSE == ucPsRestrictionFlg))
    {
        return;
    }

    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_PERIODIC_UPDATING;
    Mm_ComLuOnly();

    return;

}


VOS_VOID Mm_Cell_S5_E89(
    VOS_VOID                           *pRcvMsg
)
{
    VOS_UINT8                           ucPsRestrictionFlg;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrNetRatType;
    VOS_UINT32                          ulT3412ExpNeedRegFlg;

    enCurrNetRatType     = NAS_MML_GetCurrNetRatType();
    ulT3412ExpNeedRegFlg = NAS_MM_IsT3412ExpiredNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                           NAS_MML_GetTinType(), NAS_MML_GetT3412Status());
    ucPsRestrictionFlg   = NAS_MML_GetPsRestrictRegisterFlg();

    /* 3GPP 24.008中4.4.1  Location updating procedure章节描述如下：
        The normal location updating procedure shall also be started if the MS is
        configured to use CS fallback and SMS over SGs, or SMS over SGs only,
        and the TIN indicates "RAT-related TMSI",
        - when the periodic tracking area update timer T3412 expires and the
        network operates in network operation mode II or III
    */
    if ((VOS_FALSE == ulT3412ExpNeedRegFlg)
     || (NAS_MML_NET_RAT_TYPE_LTE == enCurrNetRatType))
    {
        return;
    }

    if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
     && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod)
     && (VOS_FALSE == ucPsRestrictionFlg))
    {
        return;
    }

    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_PERIODIC_UPDATING;
    Mm_ComLuOnly();
    return;
}

#endif


VOS_VOID Mm_Cell_S1_E65(VOS_VOID *pRcvMsg)
{
    VOS_UINT8                           ucSimCsRegStatus;

    if ( MM_FALSE == Mm_RcvSsEstReq(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
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
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_NOT_SUPPORT_CS_CALL_S1_MODE_ONLY);

            return;
        }
#endif
        /* 如果当前no rf，需要缓存业务请求，通知mmc触发搜网 */
        ucSimCsRegStatus = NAS_MML_GetSimCsRegStatus();

        if ((VOS_FALSE == NAS_MML_GetRfAvailFlg())
         && (VOS_TRUE == ucSimCsRegStatus))
        {
            NAS_MM_UpdateConnCtrlInfo(MM_CONN_CTRL_SS);
            Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);
            return;
        }

        Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_OUT_OF_COVERAGE);
    }

    return;
}


VOS_VOID Mm_Cell_S25_E65(VOS_VOID  *pRcvMsg)
{

    if ( MM_FALSE == Mm_RcvSsEstReq(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
    }
    else
    {
        Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);
    }

    return;
}


/*lint -restore */

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
