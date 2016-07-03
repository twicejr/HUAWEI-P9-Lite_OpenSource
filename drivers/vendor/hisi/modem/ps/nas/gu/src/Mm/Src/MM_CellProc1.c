
#include        "MM_Inc.h"
#include        "NasCommDef.h"
#include        "GmmMmInterface.h"
#include        "NasMmcProcNvim.h"
#include        "MM_Ext.h"

#include        "NasMmSndOm.h"
#include        "NasMmEcall.h"
#include        "NasUtranCtrlInterface.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人:luojian 107747;检视人:sunshaohua65952;原因:LOG方案设计需要*/
#define    THIS_FILE_ID        PS_FILE_ID_MM_CELLPROC1_C
/*lint +e767 修改人:luojian 107747;检视人:sunshaohua*/

/*lint -save -e958 */


VOS_VOID NAS_MM_StoreCsUnavailableInfo(
    VOS_UINT16                          usCause,
    NAS_MNTN_CS_UNAVAILABLE_INFO_STRU  *pstCsUnavailableInfo
)
{
    VOS_UINT32                          ulPos;

    /* 事件记录标志设置一: 尝试次数达上限 */
    if (NAS_MNTN_CS_ATTEMPT_MAX == pstCsUnavailableInfo->ucTimes)
    {
        pstCsUnavailableInfo->bRecordRequired = VOS_TRUE;
    }

    /* 事件记录标志设置二: 注册失败原因值指示当前驻留位无法提供服务，重选后再尝试注册 */
    NAS_MNTN_ServiceUnavailableType(usCause, &pstCsUnavailableInfo->bRecordRequired);

    /* 异常数据直接退出一: 注册失败原因值没有指示当前驻留位无法提供服务，
       且注册失败计数器值为0 */
    if ((VOS_TRUE != pstCsUnavailableInfo->bRecordRequired)
     && (0 == g_MmGlobalInfo.LuInfo.ucLuAttmptCnt))
    {
        NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_StoreCsUnavailableInfo: Error Counter.");
        return;
    }

    /* 异常数据直接退出二: 注册失败计数器值超过最大值 */
    if (g_MmGlobalInfo.LuInfo.ucLuAttmptCnt > NAS_MNTN_CS_ATTEMPT_MAX)
    {
        return;
    }

    /* 记录注册失败原因值到全局变量 */
    if (0 != g_MmGlobalInfo.LuInfo.ucLuAttmptCnt)
    {
        ulPos = g_MmGlobalInfo.LuInfo.ucLuAttmptCnt - 1;

    }
    else
    {
        ulPos = 0;
    }

    pstCsUnavailableInfo->aulCause[ulPos]= usCause;
    pstCsUnavailableInfo->ucTimes = g_MmGlobalInfo.LuInfo.ucLuAttmptCnt;

    return;
}

#if (FEATURE_ON == FEATURE_LTE)

VOS_VOID NAS_MM_RcvCcEstReq_CSFB(VOS_VOID)
{
    VOS_UINT32                          ulCsfbExistFlg;
    ulCsfbExistFlg = NAS_MML_IsCsfbServiceStatusExist();

    if ((MM_CONST_NUM_8  > g_MmCcEstReq.ulTransactionId)
     || (MM_CONST_NUM_14 < g_MmCcEstReq.ulTransactionId)
     || (VOS_TRUE == ulCsfbExistFlg))
    {
        if (VOS_TRUE == ulCsfbExistFlg)
        {
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CSFB_ALREADY_EXISTS);
        }
        else
        {
            /* ti非法，回复NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID */
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);
        }

        /* Mm_RcvCcEstReq函数判断如果是紧急呼设置了ucEstingCallTypeFlg，需要清除 */
        if (VOS_TRUE == NAS_MML_GetCsEmergencyServiceFlg())
        {
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucEstingCallTypeFlg = MM_FALSE;
            NAS_MML_SetCsEmergencyServiceFlg( VOS_FALSE );
        }

        return;
    }

    /* 缓存建立请求 */
    NAS_MM_UpdateConnCtrlInfo(MM_CONN_CTRL_CC);

    /* 更新CSFB状态 */
    if (VOS_TRUE == NAS_MML_GetCsEmergencyServiceFlg())
    {
        NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_MO_EMERGENCY_EXIST);

        NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_MO_EMERGENCY_EXIST);

        /* 记录CSFB业务建立开始 */
        NAS_MML_SetMoCallStatus(NAS_MML_CSFB_MO_EMC_CALL_SETUP_START);
    }
    else
    {
        NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_CC_EXIST);

        NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_CC_EXIST);

        /* 记录CSFB业务建立开始 */
        NAS_MML_SetMoCallStatus(NAS_MML_CSFB_MO_NORMAL_CALL_SETUP_START);
    }

    /* 向L发送CSFB流程开始请求,CSFB是否可以发起的判断由LMM负责，如果不允许发起,
       L会回复LMM_MM_CSFB_SERVICE_END_IND */
    NAS_MM_SndLmmCsfbServiceStartNotify();

    return;

}


VOS_VOID NAS_MM_RcvSsEstReq_CSFB(VOS_VOID)
{
    /* 已经在CSFB流程，如已在主被叫CSFB，无需响应，回复SS建立失败 */
    if (VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist())
    {
        Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CSFB_ALREADY_EXISTS);

        return;
    }

    if ((MM_CONST_NUM_8 > g_MmSsEstReq.ulTi)
     || (MM_CONST_NUM_14 < g_MmSsEstReq.ulTi))
    {                                                                       /* TI不合法 */
        Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);

        return;
    }

    /* 缓存建立请求 */
    NAS_MM_UpdateConnCtrlInfo(MM_CONN_CTRL_SS);

    NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST);

    /* 更新CSFB状态 */
    NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST);

    /* 向L发送CSFB流程开始请求,CSFB是否可以发起的判断由LMM负责，如果不允许发起,
       L会回复LMM_MM_CSFB_SERVICE_END_IND */
    NAS_MM_SndLmmCsfbServiceStartNotify();

    NAS_MML_SetMoSsStatus(NAS_MML_CSFB_MO_SS_SETUP_START);

    return;

}
#endif

VOS_VOID Mm_Cell_S3_E24(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList = VOS_NULL_PTR;

#endif


    if (MM_FALSE == Mm_RcvCcEstReq(pRcvMsg))
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

        /* 如果当前驻留LTE,则直接回复CC失败 */
        if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
        {
            NAS_MM_RcvCcEstReq_CSFB();
            return;
        }
#endif

        /* 非紧急呼，当前小区主叫业务受限则不处理 */
        if ((VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
         && (MMCC_EMERGENCY_CALL != g_MmCcEstReq.ulCallType))
        {
            /* 通知CC建立失败                           */
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);

            return;
        }

        g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;             /* 记录收到建立请求时的状态                 */

        if ((MM_CONST_NUM_8 > g_MmCcEstReq.ulTransactionId)
            ||(MM_CONST_NUM_14 < g_MmCcEstReq.ulTransactionId))
        {
            /* TI不合法                                 */
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);      /* 通知CC建立失败                           */
        }
        else
        {                                                                       /* TI合法                                   */
            NAS_MM_EstMmConnection(MM_CONN_CTRL_CC);
        }
    }

    NAS_MM_UpdateCsServiceBufferStatusFlg();

    NAS_MM_UpdateCsServiceConnStatusFlg();

    return;
}


VOS_VOID NAS_MM_ProcCcEstReq_IdleLimitedService(VOS_VOID)
{
    NAS_MML_MISCELLANEOUS_CFG_INFO_STRU   *pstMiscellaneousCfgInfo = VOS_NULL_PTR;
    NAS_MMCM_REL_CAUSE_ENUM_UINT32         enRelCause;

    pstMiscellaneousCfgInfo = NAS_MML_GetMiscellaneousCfgInfo();
    enRelCause              = NAS_MM_GetMmCmRelCause();

    if (MMCC_EMERGENCY_CALL == g_MmCcEstReq.ulCallType)
    {                                                                   /* 是紧急呼叫                               */
        NAS_MM_EstMmConnection(MM_CONN_CTRL_CC);
    }
    else
    {                                                                   /* 不是紧急呼叫                             */
        if ((NAS_MML_MS_MODE_PS_ONLY == NAS_MML_GetMsMode())
         && (NAS_MMC_NV_ITEM_DEACTIVE == pstMiscellaneousCfgInfo->ucPsOnlyCsServiceSupportFlg))
        {
            NAS_NORMAL_LOG(WUEPS_PID_MM, "NAS_MM_ProcCcEstReq_IdleLimitedService: PS ONLY mode and NV 9056 not active, Could not make CS call");
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);      /* 通知CC建立失败                           */
        }
        else
        {
            /*状态为NO IMSI或者服务域不为PS ONLY*/
            if ((NAS_MML_MS_MODE_PS_ONLY != NAS_MML_GetMsMode())
             || (MM_IDLE_LIMITED_SERVICE != g_MmGlobalInfo.ucState))
            {
                /* no imsi时，普通呼叫回cs detach更合适 */
                NAS_NORMAL_LOG1(WUEPS_PID_MM, "NAS_MM_ProcCcEstReq_IdleLimitedService: MM Substate ", g_MmGlobalInfo.ucState);
                Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId, enRelCause);                      /* 通知CC建立失败                           */
            }
            else
            {
                NAS_MML_SetCsAttachAllowFlg(VOS_TRUE);
                if ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
                {
                    Mm_SndCcRelInd(
                        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                        NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);
                }

                /*缓存该服务请求并进行CS注册*/
                NAS_MM_UpdateConnCtrlInfo(MM_CONN_CTRL_CC);

                if ((MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod)
                 && (MM_FALSE == g_MmGlobalInfo.ucLikeB))
                {
                    NAS_MM_SndGmmRegisterInit();
                }
                else
                {
                    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;
                    g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;
                    Mm_ComLuOnly();
                }
            }

        }

    }
}


VOS_VOID Mm_Cell_S4_E24(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList = VOS_NULL_PTR;


    NAS_MML_MISCELLANEOUS_CFG_INFO_STRU                    *pstMiscellaneousCfgInfo = VOS_NULL_PTR;

    pstMiscellaneousCfgInfo = NAS_MML_GetMiscellaneousCfgInfo();
#endif


    if (MM_FALSE == Mm_RcvCcEstReq(pRcvMsg))
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        /* 非紧急呼，当前小区主叫业务受限则不处理 */
        if ((VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
         && (MMCC_EMERGENCY_CALL != g_MmCcEstReq.ulCallType))
        {
           /* 通知CC建立失败                           */
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);

            return;
        }

        /* 在MM_IDLE_NO_IMSI状态时收到普通呼叫请求直接回复CS_SIM_INVALID,
           其他状态一般是收到系统消息后还未注册时处理缓存,暂时无法提供CS服务，需要重拨 */
        if ( (VOS_FALSE           == NAS_MML_GetSimCsRegStatus())
          && (MMCC_MO_NORMAL_CALL == g_MmCcEstReq.ulCallType) )
        {
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SIM_INVALID);    /* 通知CC建立失败                           */

            return;
        }

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

            /* 如果当前PS ONLY时支持CS业务NV未激活，则主叫失败 */
            if ( (NAS_MML_MS_MODE_PS_ONLY  == NAS_MML_GetMsMode())
              && (NAS_MMC_NV_ITEM_DEACTIVE == pstMiscellaneousCfgInfo->ucPsOnlyCsServiceSupportFlg)
              && (MMCC_MO_NORMAL_CALL      == g_MmCcEstReq.ulCallType) )
            {
                NAS_NORMAL_LOG(WUEPS_PID_MM, "Mm_Cell_S4_E24: PS ONLY mode and NV 9056 not active, Could not make CS call");
                Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                              NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);       /* 通知CC建立失败                           */

                return;
            }

            NAS_MM_RcvCcEstReq_CSFB();

            return;
        }
#endif

        g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;             /* 记录收到建立请求时的状态                 */

        if (VOS_FALSE == NAS_MM_IsCcTiValid())
        {
            /* TI不合法                                 */
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);            /* 通知CC建立失败                           */
        }
        else
        {
            NAS_MM_ProcCcEstReq_IdleLimitedService();
        }
    }

    NAS_MM_UpdateCsServiceBufferStatusFlg();

    NAS_MM_UpdateCsServiceConnStatusFlg();

    return;
}


VOS_VOID Mm_Cell_S9_E24(
                        VOS_VOID            *pRcvMsg                           /* 接收消息的头地址                         */
                    )
{
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList = VOS_NULL_PTR;

#endif

    if (MM_FALSE == Mm_RcvCcEstReq(pRcvMsg))
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        /* 非紧急呼，且不再搜网状态，当前小区主叫业务受限则不处理 */
        if ((VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
         && (MMCC_EMERGENCY_CALL != g_MmCcEstReq.ulCallType)
         && (MM_IDLE_PLMN_SEARCH != g_MmGlobalInfo.ucState))
        {
            /* 通知CC建立失败                           */
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);

            return;
        }

#if (FEATURE_ON == FEATURE_LTE)

        /* 如果当前为L单模则直接回复CC失败 */
        pstPrioRatList = NAS_MML_GetMsPrioRatList();
        if ( VOS_TRUE == NAS_MML_IsLteOnlyMode(pstPrioRatList) )
        {
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_NOT_SUPPORT_CS_CALL_S1_MODE_ONLY);                              /* 通知CC建立失败                           */
            return;
        }

        /* 如果当前驻留LTE,则直接回复CC失败 */
        if ((NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
         && (MM_IDLE_PLMN_SEARCH != g_MmGlobalInfo.ucState))
        {
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_LTE_LIMITED_SERVICE);                              /* 通知CC建立失败                           */

            return;
        }
#endif


        if(VOS_FALSE == NAS_MML_GetSimCsRegStatus())
        {
            if(MMCC_EMERGENCY_CALL != g_MmCcEstReq.ulCallType)
            {
                Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SIM_INVALID);                          /* 通知CC建立失败                           */

                return;
            }
        }

        if ((MM_IDLE_PLMN_SEARCH == g_MmGlobalInfo.ucState)
         && (MMCC_EMERGENCY_CALL != g_MmCcEstReq.ulCallType))
        {
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_SEARCHING_NETWORK);                          /* 通知CC建立失败                           */
            return;
        }

        /* 检查多业务冲突是否允许 */
        if (VOS_FALSE == Mm_IsMultiSrvCollisionAllow(MM_CONN_CTRL_CC))
        {
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SERVICE_CONGESTION);
            return;
        }

        /*缓存该服务请求 */
        NAS_MM_UpdateConnCtrlInfo(MM_CONN_CTRL_CC);

        if (MM_IDLE_PLMN_SEARCH == g_MmGlobalInfo.ucState)
        {
            Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);
        }
    }
    return;
}


VOS_VOID Mm_Cell_S10_E24(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    MM_MSG_CM_SVC_REQ_STRU              CmSvcReq;                               /* CM service request结构体                 */
    VOS_UINT8                           ucRst;

    PS_MEM_SET(&CmSvcReq,0x00,sizeof(CmSvcReq));

    if (MM_FALSE == Mm_RcvCcEstReq(pRcvMsg))
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        /*lint -e701*/
        /* 非紧急呼，当前小区主叫业务受限则不处理 */
        if ((VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
         && (MMCC_EMERGENCY_CALL != g_MmCcEstReq.ulCallType))
        {
            /* 通知CC建立失败                           */
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);

            return;
        }

        ucRst = Mm_ComJudgeLimitSvc();
        if ((MM_CONST_NUM_8 > g_MmCcEstReq.ulTransactionId)
            || (MM_CONST_NUM_14 < g_MmCcEstReq.ulTransactionId)
            || (MM_TRUE == ucRst))
        {                                                                       /* TI不合法或者在受限服务状态               */
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);                   /* 通知CC建立失败                           */
        }
        /*lint -e701*/
        else if (MM_CONST_NUM_0 !=
            (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] &
            (0x01 << (g_MmCcEstReq.ulTransactionId - 8))))
        /*lint +e701*/
        {                                                                       /* 要求建立的MM连接已经存在                 */
        }
        else
        {                                                                       /* TI合法                                   */
            if (MMCC_MO_NORMAL_CALL == g_MmCcEstReq.ulCallType)
            {                                                                   /* 主叫正常呼叫                             */
                Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_MO_CALL_EST,
                    MM_FALSE, &CmSvcReq);                                       /* 填充CM SERVICE REQUEST结构体             */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucEstingCallTypeFlg
                    = MM_FALSE;                                                 /* 不是紧急呼叫                             */
                NAS_MML_SetCsEmergencyServiceFlg( VOS_FALSE );
            }
            else if (MMCC_EMERGENCY_CALL == g_MmCcEstReq.ulCallType)
            {                                                                   /* 主叫紧急呼叫                             */
                Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_EMG_CALL_EST,
                    MM_FALSE, &CmSvcReq);                                       /* 填充CM SERVICE REQUEST结构体             */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucEstingCallTypeFlg
                    = MM_TRUE;                                                  /* 是紧急呼叫                               */
                NAS_MML_SetCsEmergencyServiceFlg( VOS_TRUE );
            }
            else
            {
            }
            Mm_ComMsgCmSvcReqSnd(&CmSvcReq);                                    /* 向网侧发送建立MM连接的请求               */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                                    RcvXXEstReq.ulTransactionId
                = g_MmCcEstReq.ulTransactionId;                                           /* 记录重建MM连接的TI */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI =
                (VOS_UINT8)g_MmCcEstReq.ulTransactionId;                        /* 记录正在建立的MM连接                     */
            g_MmGlobalInfo.ucMMConnEstingPD = MM_IE_PD_CALL_CONTROL;            /* 记录正在建立的MM连接的PD                 */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucRat = NAS_MML_GetCurrNetRatType();
            Mm_TimerStart(MM_TIMER_T3230);                                      /* 启动TIMER3230                            */
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* 记录迁移之前的状态                       */
            Mm_ComSetMmState(WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S10_E24:NORMAL: STATUS is  WAIT_FOR_RR_CONNECTION_MM_CONNECTION");
        }

        /*lint +e701*/
    }

    return;
}

VOS_VOID Mm_Cell_S11_E24(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    if (MM_FALSE == Mm_RcvCcEstReq(pRcvMsg))
    {                                                                           /* 消息检查结果失败                         */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S10_E24:WARNING: MMCC_EST_REQ check fail.");;
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        /* 非紧急呼，当前小区主叫业务受限则不处理 */
        if ((VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
         && (MMCC_EMERGENCY_CALL != g_MmCcEstReq.ulCallType))
        {
            /* 通知CC建立失败                           */
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);

            return;
        }

        if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
        {
            /* 已经存在一个保留的MM连接建立请求         */
            Mm_SndCcRelInd(
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);                             /* 通知CC建立失败                           */
        }

        /* 检查多业务冲突是否允许 */
        if (VOS_FALSE == Mm_IsMultiSrvCollisionAllow(MM_CONN_CTRL_CC))
        {
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SERVICE_CONGESTION);
            return;
        }

        /* 缓存消息 */
        NAS_MM_UpdateConnCtrlInfo(MM_CONN_CTRL_CC);
      }

    return;
}


VOS_VOID Mm_Cell_S19_E24(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    if (MM_FALSE == Mm_RcvCcEstReq(pRcvMsg))
    {                                                                           /* 消息检查结果失败                         */
        MM_WARN_LOG(" \nMM:Recieve CC EST REQUEST ERROR!\r " );
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        /* 非紧急呼，当前小区主叫业务受限则不处理 */
        if ((VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
         && (MMCC_EMERGENCY_CALL != g_MmCcEstReq.ulCallType))
        {
            /* 通知CC建立失败                           */
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);

            return;
        }

        if ((MM_CONST_NUM_8 > g_MmCcEstReq.ulTransactionId)
            ||(MM_CONST_NUM_14 < g_MmCcEstReq.ulTransactionId))
        {
            /* TI不合法,通知CC建立失败 */
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);
        }
        else
        {                                                                       /* TI合法                                   */
            if (MMCC_EMERGENCY_CALL == g_MmCcEstReq.ulCallType)
            {                                                                   /* 是紧急呼叫                               */
                g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;     /* 记录收到建立请求时的状态                 */

                NAS_MM_EstMmConnection(MM_CONN_CTRL_CC);
            }
            else
            {
                if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
                {
                    /* 已经存在一个保留的MM连接建立请求,通知CC建立失败 */
                    Mm_SndCcRelInd(
                        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                        NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);
                }

                /* 缓存消息 */
                NAS_MM_UpdateConnCtrlInfo(MM_CONN_CTRL_CC);
            }
        }
    }
    return;
}

VOS_VOID Mm_Cell_S10_E25(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{

    if (MM_FALSE == Mm_RcvCcRelReq(pRcvMsg))
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        if (MMCC_RELEASE_SPECIFIC == g_MmCcRelReq.ulReleaseType)
        {                                                                       /* 释放类型为释放指定的MM连接               */
            /*lint -e701*/
            if ((MM_CONST_NUM_7 > g_MmCcRelReq.ulTransactionId)
                && (MM_CONST_NUM_0 !=
               (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
                    & (0x01 << g_MmCcRelReq.ulTransactionId))))
            {                                                                   /* 释放网侧建立的MM连接并且存在             */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
                    = (VOS_UINT8)(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                    aucMMConnExtFlg[0]
                    & (~(VOS_UINT8)(0x01 << g_MmCcRelReq.ulTransactionId)));    /* 清除MM连接存在标志                       */
            }
            else if ((MM_CONST_NUM_7 < g_MmCcRelReq.ulTransactionId)
                    && (MM_CONST_NUM_15 > g_MmCcRelReq.ulTransactionId)
                    && (MM_CONST_NUM_0 != (g_MmGlobalInfo.
                    ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
                    & (0x01 << (g_MmCcRelReq.ulTransactionId - 8)))))
            {                                                                   /* 释放CC建立的MM连接并且存在               */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
                    = (VOS_UINT8)(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                    aucMMConnExtFlg[1]
                    & (~(VOS_UINT8)(0x01 <<
                    (g_MmCcRelReq.ulTransactionId - 8))));                      /* 清除MM连接存在标志                       */
            }
            else
            {
                /* 指定释放的MM连接不存在, 通知CC指定释放的MM连接不存在 */
                Mm_SndCcRelInd(g_MmCcRelReq.ulTransactionId,
                    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);
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
              g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]))
            {                                                                   /* 没有MM连接存在                           */
                g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = g_MmGlobalInfo.
                    ucStaOfRcvXXEstReq;                                         /* 进入空闲的状态                           */
                Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );/* MM连接流程                               */
                g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;           /* 记录迁移之前的状态                       */
                Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S10_E25:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
                Mm_TimerStart(MM_TIMER_T3240);                                  /* 启动TIMER3240                            */

                NAS_MML_SetCsServiceConnStatusFlg(VOS_FALSE);
            }
        }
        else
        {                                                                       /* 释放类型为释放所有的MM连接               */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0] = 0;/* 本地释放网侧建立的MM连接                 */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] = 0;/* 本地释放CC建立的MM连接                   */
            if ( ( MM_CONST_NUM_0 ==
              g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0] )
              && ( MM_CONST_NUM_0 ==
              g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1] )
              && ( MM_CONST_NUM_0 ==
              g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0] )
              && ( MM_CONST_NUM_0 ==
              g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]))
            {                                                                   /* 没有MM连接存在                           */
                g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                    g_MmGlobalInfo.ucStaOfRcvXXEstReq;                          /* 进入空闲的状态                           */
                Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );/* MM连接流程                               */
                g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;           /* 记录迁移之前的状态                       */
                Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S10_E25:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
                Mm_TimerStart(MM_TIMER_T3240);                                  /* 启动TIMER3240                            */

                NAS_MML_SetCsServiceConnStatusFlg(VOS_FALSE);
            }
        }
    }

    return;
}

VOS_VOID Mm_Cell_S13_E25(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    MM_MSG_RE_EST_REQ_STRU      MsgReEstReq;
    PS_MEM_SET(&MsgReEstReq,0,sizeof(MM_MSG_RE_EST_REQ_STRU));

    if ( MM_FALSE == Mm_RcvCcRelReq(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        /*lint -e701*/
        if ( MMCC_RELEASE_SPECIFIC == g_MmCcRelReq.ulReleaseType )
        {                                                                       /* 释放类型为释放指定的MM连接               */
            if (   ( MM_CONST_NUM_7 > g_MmCcRelReq.ulTransactionId )
                && ( MM_CONST_NUM_0 != ( g_MmGlobalInfo.
                ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[0]
                & ( 0x01 << g_MmCcRelReq.ulTransactionId ) ) ) )
            {                                                                   /* 释放网侧重建的MM连接并且存在             */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                    aucMMConnReestFlg[0] = ( VOS_UINT8 )( g_MmGlobalInfo.
                    ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[0]
                    & ( ~(VOS_UINT8)( 0x01 << g_MmCcRelReq.ulTransactionId ) ) );   /* 清除MM连接重建标志                       */
            }
            else if ( ( MM_CONST_NUM_7 < g_MmCcRelReq.ulTransactionId )
                    && ( MM_CONST_NUM_15 > g_MmCcRelReq.ulTransactionId )
                    && ( MM_CONST_NUM_0 !=
                ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                aucMMConnReestFlg[1] & ( 0x01 <<
                ( g_MmCcRelReq.ulTransactionId - 8 ) ) ) ) )
            {                                                                   /* 释放CC重建的MM连接并且存在               */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                    aucMMConnReestFlg[1] = ( VOS_UINT8 )( g_MmGlobalInfo.
                    ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[1]
                    & ( ~(VOS_UINT8)( 0x01 <<
                    ( g_MmCcRelReq.ulTransactionId - 8 ) ) ) );                 /* 清除MM连接重建标志                       */
            }
            else
            {
                /* 指定释放的MM连接不存在                   */
                Mm_SndCcRelInd( g_MmCcRelReq.ulTransactionId,
                    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);                              /* 通知CC指定释放的MM连接不存在             */
            }
            if ( ( MM_CONST_NUM_0 == g_MmGlobalInfo.
                ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[0])
                && (MM_CONST_NUM_0 == g_MmGlobalInfo.
                ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[1]) )
            {                                                                   /* 没有等待重建的MM连接存在                 */
                Mm_TimerStop(MM_TIMER_PROTECT_CC);                              /* 启动保护TIMER                            */
                if ( ( MM_CONST_NUM_0 == g_MmGlobalInfo.
                    ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0] )
                    && ( MM_CONST_NUM_0 == g_MmGlobalInfo.
                    ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] ) )
                {                                                               /* 全部释放，没有要求重建的MM连接           */
                    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;       /* 记录迁移之前的状态                       */
                    Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
                    PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S13_E25:NORMAL: ucState = ", g_MmGlobalInfo.ucState);

                    if (VOS_TRUE == NAS_MM_IsDisableGprsCombineAttach())
                    {
                        if ((MM_IDLE_NORMAL_SERVICE == g_MmGlobalInfo.ucState)
                         || ((MM_IDLE_ATTEMPTING_TO_UPDATE == g_MmGlobalInfo.ucState)
                          && (MM_TIMER_STOP == gstMmTimer[MM_TIMER_T3211].ucTimerStatus)))
                        {
                            NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                        }


                    }
                }
                else
                {
                    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;       /* 记录迁移之前的状态                       */
                    Mm_ComSetMmState(WAIT_FOR_REESTABLISH_WAIT_FOR_EST_CNF);
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S13_E25:NORMAL: ucState is WAIT_FOR_REESTABLISH_WAIT_FOR_EST_CNF");
                    Mm_TimerStart(MM_TIMER_T3230);                              /* 启动保护TIMER                            */

                    MsgReEstReq.MmIeCKSN.ucCksn = NAS_MML_GetSimCsSecurityCksn();

                    MsgReEstReq.MmIeLai.IeLai.PlmnId.ulMcc
                        = NAS_MML_GetCsLastSuccMcc();
                    MsgReEstReq.MmIeLai.IeLai.PlmnId.ulMnc
                        = NAS_MML_GetCsLastSuccMnc();
                    MsgReEstReq.MmIeLai.IeLai.ulLac
                        = NAS_MML_GetCsLastSuccLac();

                    NAS_MM_FillMobileID(&(MsgReEstReq.MmIeMobileId.MobileID));

                    Mm_ComMsgCmReEstReqSnd(&MsgReEstReq);
                }
            }
        }
        else
        {                                                                       /* 释放类型为释放所有的MM连接               */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[0]
                = 0;                                                            /* 本地释放网侧建立的MM连接                 */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[1]
                = 0;                                                            /* 本地释放CC建立的MM连接                   */
            g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                g_MmGlobalInfo.ucStaOfRcvXXEstReq;                              /* 进入空闲的状态                           */
            Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );    /* MM连接流程                               */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* 记录迁移之前的状态                       */
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S13_E25:NORMAL: STATUS is  WAIT_FOR_NETWORK_COMMAND");
            Mm_TimerStart(MM_TIMER_T3240);                                      /* 启动TIMER3240                            */
        }

        /*lint +e701*/
    }

    NAS_MM_UpdateCsServiceConnStatusFlg();

    return;
}

VOS_VOID Mm_Cell_S16_E25(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{

    if ( MM_FALSE == Mm_RcvCcRelReq(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        /*lint -e701*/

        if ( MMCC_RELEASE_SPECIFIC == g_MmCcRelReq.ulReleaseType )
        {                                                                       /* 释放类型为释放指定的MM连接               */
            if (   ( MM_CONST_NUM_7 > g_MmCcRelReq.ulTransactionId )
                && ( MM_CONST_NUM_0 != ( g_MmGlobalInfo.
                ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
                    & ( 0x01 << g_MmCcRelReq.ulTransactionId ) ) ) )
            {                                                                   /* 释放网侧建立的MM连接并且存在             */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]=
                    ( VOS_UINT8 )( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                    aucMMConnExtFlg[0]
                    & ( ~(VOS_UINT8)( 0x01 << g_MmCcRelReq.ulTransactionId ) ) );   /* 清除MM连接存在标志                       */
            }
            else if ( ( MM_CONST_NUM_7 < g_MmCcRelReq.ulTransactionId )
                    && ( MM_CONST_NUM_15 > g_MmCcRelReq.ulTransactionId )
                    && ( MM_CONST_NUM_0 !=
               ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
                    & ( 0x01 << ( g_MmCcRelReq.ulTransactionId - 8 ) ) ) ) )
            {                                                                   /* 释放CC建立的MM连接并且存在               */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] =
                    ( VOS_UINT8 )( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                    aucMMConnExtFlg[1]
                    & ( ~(VOS_UINT8)( 0x01 <<
                    ( g_MmCcRelReq.ulTransactionId - 8 ) ) ) );                 /* 清除MM连接存在标志                       */
            }
            else if ( ( MM_TRUE ==
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
                && ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                RcvXXEstReq.ulTransactionId == g_MmCcRelReq.ulTransactionId ) )
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg
                    = MM_FALSE;                                                 /* 设置不存在缓存的MM连接 */

            }
            else
            {
                /* 指定释放的MM连接不存在                   */
                Mm_SndCcRelInd( g_MmCcRelReq.ulTransactionId,
                    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);                              /* 通知CC指定释放的MM连接不存在             */
            }
        }
        else
        {                                                                       /* 释放类型为释放所有的MM连接               */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0] = 0;/* 本地释放网侧建立的MM连接                 */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] = 0;/* 本地释放CC建立的MM连接                   */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg
                = MM_FALSE;                                                     /* 设置不存在缓存的MM连接                   */
        }

        NAS_MM_UpdateCsServiceConnStatusFlg();

        NAS_MM_UpdateCsServiceBufferStatusFlg();


        /*lint +e701*/
    }

    return;
}


VOS_VOID Mm_Cell_S32_E26(
    VOS_VOID                            *pRcvMsg
)
{
    if (WAIT_FOR_OUTGOING_MM_CONNECTION == g_MmGlobalInfo.ucSuspendPreState)
    {
        Mm_Cell_S32_DataTransfer(pRcvMsg);
        return;
    }

    if ( MM_FALSE == Mm_RcvCcAbortReq( pRcvMsg ) )
    {
        /* 消息检查结果失败 */
        ;
    }
    else
    {
        /* 消息检查结果成功*/
        if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                                                      .RcvXXEstReq.ucFlg)
         && (g_MmCcAbortReq.ulTransactionId == g_MmGlobalInfo
                .ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId))
        {
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                                             .RcvXXEstReq.ucFlg = MM_FALSE;
            Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);

            /* 处理MMCC_ABORT_REQ，应该需要将MM正在建立的链接标记清除。
               如果MM正在建立的链接标记没有清除，当回退到LTE时，发现有业务标记存在，就会触发释放业务的流程
            */
            if (g_MmCcAbortReq.ulTransactionId == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI)
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI = NO_MM_CONN_ESTING;
            }

            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);

            NAS_MM_SndRrMmServiceAbortNotify(WUEPS_PID_WRR);
            NAS_MM_SndRrMmServiceAbortNotify(UEPS_PID_GAS);


#if (FEATURE_ON == FEATURE_LTE)
            if (VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist())
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
    }

    NAS_MM_UpdateCsServiceBufferStatusFlg();

    return;
}


VOS_VOID Mm_Cell_S2_E26(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    VOS_UINT8                           ucCsSigConnStatusFlg;

    ucCsSigConnStatusFlg = NAS_MML_GetCsSigConnStatusFlg();

    if ( MM_FALSE == Mm_RcvCcAbortReq( pRcvMsg ) )
    {                                                                           /* 消息检查结果失败                         */
        ;
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                                                      .RcvXXEstReq.ucFlg)
         && (g_MmCcAbortReq.ulTransactionId == g_MmGlobalInfo
                .ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId))
        {
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                                             .RcvXXEstReq.ucFlg = MM_FALSE;
            Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);

            if (g_MmCcAbortReq.ulTransactionId == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI)
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI = NO_MM_CONN_ESTING;
            }


            if ( VOS_FALSE == ucCsSigConnStatusFlg )
            {
                NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
            }

#if (FEATURE_ON == FEATURE_LTE)
            if (VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist())
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
    }

    NAS_MM_UpdateCsServiceBufferStatusFlg();

    return;
}

VOS_VOID Mm_Cell_S9_E26(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{

    if ( MM_FALSE == Mm_RcvCcAbortReq( pRcvMsg ) )
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        if ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI ==
            g_MmCcAbortReq.ulTransactionId )
        {                                                                       /* 终止的MM连接建立是正在建立的             */
            Mm_TimerStop( MM_TIMER_T3230 );                                     /* 停T3230                                  */
            Mm_ComMsgCmSvcAbortSnd();
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI =
                NO_MM_CONN_ESTING;                                              /* 清除正在建立的MM连接的标志               */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;

            g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                g_MmGlobalInfo.ucStaOfRcvXXEstReq;                              /* 返回到接收到建立MM连接请求时的状态       */
            Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );    /* MM连接流程                               */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* 记录迁移之前的状态                       */
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E26:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
            Mm_TimerStart(MM_TIMER_T3240);                                      /* 启动TIMER3240                            */
        }
        else
        {
            if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                                                          .RcvXXEstReq.ucFlg)
             && (g_MmCcAbortReq.ulTransactionId == g_MmGlobalInfo
                    .ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId))
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                                                 .RcvXXEstReq.ucFlg = MM_FALSE;
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

        NAS_MM_UpdateCsServiceConnStatusFlg();
    }
    return;
}

VOS_VOID Mm_Cell_S10_E26(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{
    /*lint -e701*/
    if ( MM_FALSE == Mm_RcvCcAbortReq( pRcvMsg ) )
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        if ( 0 != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
        .aucMMConnExtFlg[1]
            & (0x01 << ( g_MmCcAbortReq.ulTransactionId - 8 ))))
        {                                                                       /* 终止的MM连接建立是正在建立的             */
            if (((0x01 << ( g_MmCcAbortReq.ulTransactionId - 8 ))
                == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                .aucMMConnExtFlg[1])
                &&(0 == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                .aucMMConnExtFlg[0]))
            {
                Mm_ComMsgCmSvcAbortSnd();
                g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                               g_MmGlobalInfo.ucStaOfRcvXXEstReq;               /* 返回到接收到建立MM连接请求时的状态       */

                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;
                Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );/* MM连接流程                               */
                g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;           /* 记录迁移之前的状态                       */
                Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S10_E26:NORMAL: STATUS is  WAIT_FOR_NETWORK_COMMAND");
                Mm_TimerStart(MM_TIMER_T3240);                                  /* 启动TIMER3240                            */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                .aucMMConnExtFlg[1] = 0;
            }
            else
            {
                Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );/* MM连接流程                               */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
                    &= ~(VOS_UINT8)(0x01 << ( g_MmCcAbortReq.ulTransactionId - 8 ));
            }
        }
        else
        {
            if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                                                          .RcvXXEstReq.ucFlg)
             && (g_MmCcAbortReq.ulTransactionId == g_MmGlobalInfo
                    .ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId))
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                                                 .RcvXXEstReq.ucFlg = MM_FALSE;
            }
        }

#if (FEATURE_ON == FEATURE_LTE)
        if (VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist())
        {
            NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

            NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
        }
#endif

        NAS_MM_UpdateCsServiceConnStatusFlg();

        NAS_MM_UpdateCsServiceBufferStatusFlg();
    }
    /*lint +e701*/
    return;
}

VOS_VOID Mm_Cell_S12_E26(
    VOS_VOID                            *pRcvMsg
)
{
    if ( MM_FALSE == Mm_RcvCcAbortReq( pRcvMsg ) )
    {
        return;
    }
    else
    {
        if ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI ==
                g_MmCcAbortReq.ulTransactionId )
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

                Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);
                NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
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
             && (g_MmCcAbortReq.ulTransactionId ==
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

VOS_VOID Mm_Cell_S16_E26(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{

    if ( MM_FALSE == Mm_RcvCcAbortReq(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        if ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI ==
            g_MmCcAbortReq.ulTransactionId )
        {                                                                       /* 终止的MM连接建立是正在建立的             */
            Mm_TimerStop( MM_TIMER_T3230 );                                     /* 停T3230                                  */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI =
                NO_MM_CONN_ESTING;                                              /* 清除正在建立的MM连接的标志               */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* 记录迁移之前的状态                       */
            Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S16_E26:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
            Mm_ComCheckDelayMmConn( MM_FALSE );                                 /* 检查是否有保留的需要建立的MM连接         */
        }
        else
        {
            if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                                                          .RcvXXEstReq.ucFlg)
             && (g_MmCcAbortReq.ulTransactionId == g_MmGlobalInfo
                    .ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId))
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                                                 .RcvXXEstReq.ucFlg = MM_FALSE;
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

VOS_VOID Mm_Cell_S10_E27(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    MMCC_DATA_REQ_STRU      *pMmCcDataReq;
    pMmCcDataReq = (MMCC_DATA_REQ_STRU*)pRcvMsg;

    if ( MM_FALSE == Mm_RcvCcDataReq(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        if ( ( MM_CONST_NUM_7 == pMmCcDataReq->ulTransactionId )
            || ( MM_CONST_NUM_15 == pMmCcDataReq->ulTransactionId ) )
        {                                                                       /* TIO 等于111                              */
            Mm_SndRrDataReq(
                pMmCcDataReq->SendCcMsg.ulCcMsgSize,
                &pMmCcDataReq->SendCcMsg.aucCcMsg[0],
                RRC_NAS_MSG_PRIORTY_HIGH);                                      /* 将CC的消息传送下去                       */
        }
        else
        {                                                                       /* TIO 不等于111                            */
            /*lint -e701*/
            if ( ( ( MM_CONST_NUM_7 > pMmCcDataReq->ulTransactionId)
                && ( MM_CONST_NUM_0 !=
                ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                aucMMConnExtFlg[0]
                & ( 0x01 << pMmCcDataReq->ulTransactionId ) ) ) )
                || ( ( MM_CONST_NUM_7 < pMmCcDataReq->ulTransactionId)
                && ( MM_CONST_NUM_0 !=
                ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                aucMMConnExtFlg[1]
                & ( 0x01 << ( pMmCcDataReq->ulTransactionId - 8 ) ) ) ) ) )
            {                                                                   /* 该TI的MM连接存在                         */
                Mm_SndRrDataReq(
                pMmCcDataReq->SendCcMsg.ulCcMsgSize,
                &pMmCcDataReq->SendCcMsg.aucCcMsg[0],
                RRC_NAS_MSG_PRIORTY_HIGH);                                      /* 将CC的消息传送下去                       */
            }
            else
            {
                /* 该TI的MM连接不存在                       */
                Mm_SndCcRelInd(pMmCcDataReq->ulTransactionId,
                    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);                              /* 通知CC建立失败                           */
            }

            /*lint +e701*/
        }
    }

    return;
}

VOS_VOID Mm_Cell_S13_E28(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    MM_MSG_RE_EST_REQ_STRU      MsgReEstReq;
    PS_MEM_SET(&MsgReEstReq,0,sizeof(MM_MSG_RE_EST_REQ_STRU));

    if ( MM_FALSE == Mm_RcvCcReestReq(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        /*lint -e701*/
        if ( MM_CONST_NUM_7 > g_MmCcReestReq.ulTransactionId )
        {                                                                       /* 是网侧建立的MM连接重建                   */
            if ( MM_CONST_NUM_0 !=
            ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[0]
            & ( 0x01 << g_MmCcReestReq.ulTransactionId ) ) )
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0] =
                    ( VOS_UINT8 )( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                    aucMMConnExtFlg[0] |
                    ( 0x01 << g_MmCcReestReq.ulTransactionId ) );               /* 设置正在重建的MM连接的标志               */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                .aucMMConnReestFlg[0] =
                    ( VOS_UINT8 )( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                    aucMMConnReestFlg[0] &
                    (~(VOS_UINT8)( 0x01 << g_MmCcReestReq.ulTransactionId ) ) );    /* 清除正在重建的MM连接的标志               */
            }
            else
            {
                Mm_SndCcRelInd(g_MmCcReestReq.ulTransactionId,
                    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);                        /* 通知CC重建立失败                         */
            }

        }
        else if ( MM_CONST_NUM_0 !=
            ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[1]
            & ( 0x01 << ( g_MmCcReestReq.ulTransactionId - 8 ) ) ) )
        {                                                                       /* 是CC建立的MM连接重建                     */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] =
                ( VOS_UINT8 )( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                aucMMConnExtFlg[1] |
                ( 0x01 << ( g_MmCcReestReq.ulTransactionId - 8 ) ) );           /* 设置正在重建的MM连接的标志               */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[1] =
                ( VOS_UINT8 )( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                aucMMConnReestFlg[1] &
                (~(VOS_UINT8)( 0x01 << ( g_MmCcReestReq.ulTransactionId - 8 ) ) ) );/* 清除正在重建的MM连接的标志               */
        }
        else
        {
            /* 要求重建的MM连接不存在                   */
            Mm_SndCcRelInd(g_MmCcReestReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);                                  /* 通知CC重建立失败                         */
        }
        /*lint +e701*/
        if ( ( MM_CONST_NUM_0 ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[0])
            && (MM_CONST_NUM_0 ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[1]) )
        {                                                                       /* 没有等待重建的MM连接存在                 */
            Mm_TimerStop(MM_TIMER_PROTECT_CC);
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* 记录迁移之前的状态                       */
            Mm_ComSetMmState(WAIT_FOR_REESTABLISH_WAIT_FOR_EST_CNF);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S13_E28:NORMAL: STATUS is WAIT_FOR_REESTABLISH_WAIT_FOR_EST_CNF");
            MsgReEstReq.MmIeCKSN.ucCksn = NAS_MML_GetSimCsSecurityCksn();

            MsgReEstReq.MmIeLai.IeLai.PlmnId.ulMcc
                = NAS_MML_GetCsLastSuccMcc();
            MsgReEstReq.MmIeLai.IeLai.PlmnId.ulMnc
                = NAS_MML_GetCsLastSuccMnc();
            MsgReEstReq.MmIeLai.IeLai.ulLac
                = NAS_MML_GetCsLastSuccLac();

            NAS_MM_FillMobileID(&(MsgReEstReq.MmIeMobileId.MobileID));

            Mm_ComMsgCmReEstReqSnd(&MsgReEstReq);
            Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);
        }
    }

    return;
}

VOS_VOID Mm_Cell_S2_E31(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{

    if (MM_FALSE == Mm_RcvRrcPagingInd(pRcvMsg))
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING,
               "Mm_Cell_S2_E31:WARNING: Msg is invalid.");
        return;
    }

    /* 当前小区PAGING受限则不处理 */
    if (VOS_TRUE == NAS_MML_GetCsRestrictPagingFlg())
    {
#if (FEATURE_ON == FEATURE_PTM)
        NAS_MM_CsPagingFailRecord(NAS_ERR_LOG_CS_PAGING_CAUSE_MM_PAGING_BAR);
#endif
        return;
    }

    g_MmSubLyrShare.MmShare.ucPagingPlmnSrch = MM_PAGING_PLMNSRCH_TRUE;

    /* 通知MMC CS服务要发起，需要停止搜网 */
    Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO,
           "Mm_Cell_S2_E31:INFO: Rcv Paging in Plmn Search, Wait camping.");

    return;
}

VOS_VOID Mm_Cell_S3_E31(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    MM_MSG_PAGING_RSP_STRU      CmRspRsp;                                       /* 要发送的PAGING RSP消息                   */

    if ( MM_FALSE == Mm_RcvRrcPagingInd(pRcvMsg) )
    {
        /* WUEPS_ASSERT(0); */
        return;
    }

    /* 当前小区PAGING受限则不处理 */
    if (VOS_TRUE == NAS_MML_GetCsRestrictPagingFlg())
    {
#if (FEATURE_ON == FEATURE_PTM)
        NAS_MM_CsPagingFailRecord(NAS_ERR_LOG_CS_PAGING_CAUSE_MM_PAGING_BAR);
#endif
        return;
    }

    Mm_TimerStop(MM_TIMER_T3211);

    if (VOS_TRUE == NAS_MML_IsNeedClearCsCksn_UsimDoneGsmCsAuth())
    {
        NAS_MML_SetSimCsSecurityCksn(MM_CKSN_INVALID);
        NAS_MML_SetUsimDoneGsmCsAuthFlg(VOS_FALSE);
    }

    CmRspRsp.MmIeCksn.ucCksn = NAS_MML_GetSimCsSecurityCksn();            /* 存储CKSN                                 */
    g_MmGlobalInfo.ucStaOfRcvXXEstReq
        = g_MmGlobalInfo.ucState;

    NAS_MM_FillMobileID(&(CmRspRsp.MmIeMobileId.MobileID));

    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType()) /* 当前处于 GSM 网中 */
    {
        /* 向 GAS 发送建立 RR 请求 */
        Mm_SndRrEstReq(RRC_EST_CAUSE_TERMINAT_CONVERSAT_CALL, MM_TRUE,
                       MM_CONST_NUM_0, VOS_NULL_PTR);
    }
    else /* UMTS 网中 */
    {
        Mm_ComMsgPagingRspSnd( &CmRspRsp );                                     /* 填充并发送 PAGING RESPONSE 消息          */
    }

    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                       /* 记录迁移之前的状态                       */
    Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_MM_CONNECTION);
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E31:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_MM_CONNECTION");
    Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);                                        /* 通知MMC，CS域的业务已经启动              */
    NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);
    Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);                                 /* 启动保护TIMER                            */

    NAS_MML_SetCsServiceConnStatusFlg(VOS_TRUE);

    return;
}

VOS_VOID Mm_Cell_S4_E31(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                        )
{
    MM_MSG_PAGING_RSP_STRU              CmRspRsp;                                       /* 要发送的PAGING RSP消息                   */
    VOS_UINT8                           ucCsAttachAllow;
    NAS_MML_MS_MODE_ENUM_UINT8          enMsMode;
    NAS_MML_MISCELLANEOUS_CFG_INFO_STRU   *pstMiscellaneousCfgInfo = VOS_NULL_PTR;

    pstMiscellaneousCfgInfo = NAS_MML_GetMiscellaneousCfgInfo();



    enMsMode        = NAS_MML_GetMsMode();

    ucCsAttachAllow = NAS_MML_GetCsAttachAllowFlg();

    if ( MM_FALSE == Mm_RcvRrcPagingInd(pRcvMsg) )
    {
        return;
    }

    /* 当前小区PAGING受限则不处理 */
    if (VOS_TRUE == NAS_MML_GetCsRestrictPagingFlg())
    {
#if (FEATURE_ON == FEATURE_PTM)
        NAS_MM_CsPagingFailRecord(NAS_ERR_LOG_CS_PAGING_CAUSE_MM_PAGING_BAR);
#endif
        return;
    }

    Mm_TimerStop(MM_TIMER_T3211);

    /* 24.008：4.2.2.3：it may respond to paging (with IMSI).*/
    if (( (MM_IMSI_PAGING == g_MmGlobalInfo.ucPagingRecordTypeId)
       && (VOS_TRUE == ucCsAttachAllow))
       || ( (NAS_MML_MS_MODE_PS_ONLY == enMsMode)
          &&(NAS_MMC_NV_ITEM_ACTIVE == pstMiscellaneousCfgInfo->ucPsOnlyCsServiceSupportFlg)))
    {
        if (VOS_TRUE == NAS_MML_IsNeedClearCsCksn_UsimDoneGsmCsAuth())
        {
            NAS_MML_SetSimCsSecurityCksn(MM_CKSN_INVALID);
            NAS_MML_SetUsimDoneGsmCsAuthFlg(VOS_FALSE);
        }
    
        CmRspRsp.MmIeCksn.ucCksn = NAS_MML_GetSimCsSecurityCksn();        /* 存储CKSN                                 */

        g_MmGlobalInfo.ucStaOfRcvXXEstReq
            = g_MmGlobalInfo.ucState;

        NAS_MM_FillMobileID(&CmRspRsp.MmIeMobileId.MobileID);

        if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())              /* 当前处于 GSM 网中 */
        {
            /* 向 GAS 发送建立 RR 请求 */
            Mm_SndRrEstReq(RRC_EST_CAUSE_TERMINAT_CONVERSAT_CALL, MM_TRUE,
                           MM_CONST_NUM_0, VOS_NULL_PTR);
        }
        else /* UMTS 网中 */
        {
            Mm_ComMsgPagingRspSnd( &CmRspRsp );                                 /* 填充并发送 PAGING RESPONSE 消息          */
        }

        g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                   /* 记录迁移之前的状态                       */
        Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_MM_CONNECTION);

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S4_E31:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_MM_CONNECTION");
        Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);                                    /* 通知MMC，CS域的业务已经启动              */
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);
        Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);                             /* 启动保护TIMER                            */

        NAS_MML_SetCsServiceConnStatusFlg(VOS_TRUE);
    }

    return;
}

VOS_VOID Mm_Cell_S5_E31(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    MM_MSG_PAGING_RSP_STRU      CmRspRsp;                                       /* 要发送的PAGING RSP消息                   */

    if ( MM_FALSE == Mm_RcvRrcPagingInd(pRcvMsg) )
    {
        /* WUEPS_ASSERT(0); */
        return;
    }

    /* 当前小区PAGING受限则不处理 */
    if (VOS_TRUE == NAS_MML_GetCsRestrictPagingFlg())
    {
#if (FEATURE_ON == FEATURE_PTM)
        NAS_MM_CsPagingFailRecord(NAS_ERR_LOG_CS_PAGING_CAUSE_MM_PAGING_BAR);
#endif
        return;
    }

    Mm_TimerStop(MM_TIMER_T3211);

    /* 用 IMEI 寻呼的处理 */
    if (MM_IMSI_PAGING == g_MmGlobalInfo.ucPagingRecordTypeId)
    {
        if (VOS_TRUE == NAS_MML_IsNeedClearCsCksn_UsimDoneGsmCsAuth())
        {
            NAS_MML_SetSimCsSecurityCksn(MM_CKSN_INVALID);
            NAS_MML_SetUsimDoneGsmCsAuthFlg(VOS_FALSE);
        }

        CmRspRsp.MmIeCksn.ucCksn = NAS_MML_GetSimCsSecurityCksn();        /* 存储CKSN                                 */

        g_MmGlobalInfo.ucStaOfRcvXXEstReq
            = g_MmGlobalInfo.ucState;

        NAS_MM_FillMobileID(&(CmRspRsp.MmIeMobileId.MobileID));

        if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType()) /* 当前处于 GSM 网中 */
        {
            /* 向 GAS 发送建立 RR 请求 */
            Mm_SndRrEstReq(RRC_EST_CAUSE_TERMINAT_CONVERSAT_CALL, MM_TRUE,
                           MM_CONST_NUM_0, VOS_NULL_PTR);
        }
        else /* UMTS 网中 */
        {
            Mm_ComMsgPagingRspSnd( &CmRspRsp );                                     /* 填充并发送 PAGING RESPONSE 消息          */
        }

        g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                   /* 记录迁移之前的状态                       */
        Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_MM_CONNECTION);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S5_E31:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_MM_CONNECTION");
        Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);                                    /* 通知MMC，CS域的业务已经启动              */
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);
        Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);                             /* 启动保护TIMER                            */

        NAS_MML_SetCsServiceConnStatusFlg(VOS_TRUE);

    }

    return;
}

VOS_VOID Mm_Cell_S6_E31(
    VOS_VOID                           *pstRcvMsg
)
{
    MM_MSG_PAGING_RSP_STRU              stCmRspRsp;                                       /* 要发送的PAGING RSP消息                   */
    VOS_UINT8                           ucCsAttachAllow;
    NAS_MML_MS_MODE_ENUM_UINT8          enMsMode;
    NAS_MML_MISCELLANEOUS_CFG_INFO_STRU *pstMiscellaneousCfgInfo = VOS_NULL_PTR;

    pstMiscellaneousCfgInfo = NAS_MML_GetMiscellaneousCfgInfo();

    enMsMode                = NAS_MML_GetMsMode();

    ucCsAttachAllow         = NAS_MML_GetCsAttachAllowFlg();

    if (MM_FALSE == Mm_RcvRrcPagingInd(pstRcvMsg))
    {
        return;
    }

    /* 当前小区PAGING受限则不处理 */
    if (VOS_TRUE == NAS_MML_GetCsRestrictPagingFlg())
    {
#if (FEATURE_ON == FEATURE_PTM)
        NAS_MM_CsPagingFailRecord(NAS_ERR_LOG_CS_PAGING_CAUSE_MM_PAGING_BAR);
#endif
        return;
    }

    Mm_TimerStop(MM_TIMER_T3211);

    /* MM_IDLE_LOCATION_UPDATE_NEEDED状态如果当前CS 注册状态响应普通寻呼，
       否则只能响应 IMSI 寻呼 */
    if ((MM_COM_SRVST_NORMAL_SERVICE == NAS_MM_GetLauUptNeededCsSrvStatus())
     || (( (MM_IMSI_PAGING == g_MmGlobalInfo.ucPagingRecordTypeId)
        && (VOS_TRUE == ucCsAttachAllow))
      || ( (NAS_MML_MS_MODE_PS_ONLY == enMsMode)
        && (NAS_MMC_NV_ITEM_ACTIVE == pstMiscellaneousCfgInfo->ucPsOnlyCsServiceSupportFlg))))
    {
        if (VOS_TRUE == NAS_MML_IsNeedClearCsCksn_UsimDoneGsmCsAuth())
        {
            NAS_MML_SetSimCsSecurityCksn(MM_CKSN_INVALID);
            NAS_MML_SetUsimDoneGsmCsAuthFlg(VOS_FALSE);
        }

        stCmRspRsp.MmIeCksn.ucCksn            = NAS_MML_GetSimCsSecurityCksn(); /* 存储CKSN                                 */
        g_MmGlobalInfo.ucStaOfRcvXXEstReq     = g_MmGlobalInfo.ucState;
        NAS_MM_FillMobileID(&(stCmRspRsp.MmIeMobileId.MobileID));

        if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())            /* 当前处于 GSM 网中 */
        {
            /* 向 GAS 发送建立 RR 请求 */
            Mm_SndRrEstReq(RRC_EST_CAUSE_TERMINAT_CONVERSAT_CALL, MM_TRUE,
                           MM_CONST_NUM_0,
                           VOS_NULL_PTR);
        }
        else /* UMTS 网中 */
        {
            Mm_ComMsgPagingRspSnd(&stCmRspRsp);                                 /* 填充并发送 PAGING RESPONSE 消息          */
        }

        g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                   /* 记录迁移之前的状态                       */
        Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_MM_CONNECTION);

        Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);                                    /* 通知MMC，CS域的业务已经启动              */
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);
        Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);                             /* 启动保护TIMER                            */

        NAS_MML_SetCsServiceConnStatusFlg(VOS_TRUE);
    }

    return;

}


VOS_VOID Mm_Cell_S12_E32(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{

    RRMM_EST_CNF_STRU       *pRrMmEstCnf;

    if ( MM_FALSE == Mm_RcvRrcEstCnf(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        pRrMmEstCnf = (RRMM_EST_CNF_STRU*)pRcvMsg;
        Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);                              /* 启动保护TIMER                            */

        NAS_MM_SetEstCnfResult(pRrMmEstCnf->ulResult);


        /* 处理当前缓存的CS域去注册 */
        if ( MM_WAIT_CS_DETACH == (g_MmGlobalInfo.stDetachInfo.enDetachType & MM_WAIT_CS_DETACH) )
        {
            NAS_MM_RcvRrMmEstCnf_ExistCsDetachBuffer(pRrMmEstCnf);

            return;
        }

        /* 在进行CS呼叫建链过程中，如果接入层回复建链失败，原因值为: Conn_Fail，
             对比标杆，发现标杆会重新发起建链请求，直到CC T303超时后中断为止,
            这样可以提高电话接通率 */
        if (  (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
           && ((RRC_EST_EST_CONN_FAIL == pRrMmEstCnf->ulResult)
            || (RRC_EST_RJ_NOT_ALLOW == pRrMmEstCnf->ulResult)
            || (RRC_EST_RJ_TIME_OUT == pRrMmEstCnf->ulResult)
            || (RRC_EST_RJ_RA_RESOURCE_FAIL == pRrMmEstCnf->ulResult)
            || (RRC_EST_RJ_IMMEDIATE_ASSIGN_INVALID == pRrMmEstCnf->ulResult)
            || (RRC_EST_RJ_ACTIVE_PHISICAL_CHANNEL_FAIL == pRrMmEstCnf->ulResult))
           && (MM_IE_PD_CALL_CONTROL == g_MmGlobalInfo.ucMMConnEstingPD))
        {
            g_MmGlobalInfo.ucCallRetryCount++;

            /* 为了防止MM/GAS反复进行乒乓操作，导致系统消息队列溢出，限制尝试次数 */
            if (g_MmGlobalInfo.ucCallRetryCount < MM_CALL_RETRY_MAX_TIMES)
            {
                NAS_MM_EstMmConnection(MM_CONN_CTRL_CC);

                return;
            }
        }

#if (FEATURE_ON == FEATURE_PTM)
        NAS_MM_RecordCsPagingFail_WaitForRrConnection(pRrMmEstCnf->ulResult);
#endif

        /* 清除消息缓存标志               */
        NAS_MM_ClearConnCtrlInfo(g_MmGlobalInfo.ucMMConnEstingPD);

        /* 只有建链结果是RRC_EST_SUCCESS或者RRC_EST_PRESENT，才需要设置业务存在标志 */

        NAS_MM_ProcEstCnfCauseAtState12(pRrMmEstCnf->ulResult);
    }

    return;
}

VOS_VOID Mm_Cell_S14_E32(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    VOS_UINT8                i = 0;                                             /* 循环计数变量                             */
    RRMM_EST_CNF_STRU       *pRrMmEstCnf;
    VOS_UINT8                ucTiValidFlg = MM_TRUE;

    if ( MM_FALSE == Mm_RcvRrcEstCnf(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        pRrMmEstCnf = (RRMM_EST_CNF_STRU*)pRcvMsg;


        NAS_MM_SetEstCnfResult(pRrMmEstCnf->ulResult);

        /* 处理当前缓存的CS域去注册 */
        if ( MM_WAIT_CS_DETACH == (g_MmGlobalInfo.stDetachInfo.enDetachType & MM_WAIT_CS_DETACH) )
        {
            NAS_MM_RcvRrMmEstCnf_ExistCsDetachBuffer(pRrMmEstCnf);

            return;
        }

        Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);                              /* 启动保护TIMER                            */
        switch ( pRrMmEstCnf->ulResult)
        {
        case RRC_EST_SUCCESS:                                                   /* 信令连接建立成功                         */
        case RRC_EST_PRESENT:                                                   /* 该信令连接已经存在                       */
            if ( RRC_EST_PRESENT == pRrMmEstCnf->ulResult )
            {
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S14_E32:WARNING: RR CONNECTION PRESENT !");
            }
            Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ESTED );

            Mm_TimerStart(MM_TIMER_T3230);                                      /* 启动TIMER3230                            */
            g_MmGlobalInfo.ucCsSigConnFlg = MM_CS_SIG_CONN_PRESENT;
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S14_E32:INFO: MmCsSigConnFlg is MM_CS_SIG_CONN_PRESENT");
            break;
        /* case RRC_EST_DELING:  */                                                  /* 该信令连接正在释放                       */
        case RRC_EST_RJ_CONGEST:                                                /* RRC Connection Reject: Congestion        */
        case RRC_EST_RJ_UNSPEC:                                                 /* RRC Connection Reject: Unspecified       */
        case RRC_EST_EST_CONN_FAIL:                                             /* RR connection establish failure          */
        case RRC_EST_RJ_NOT_ALLOW:
        case RRC_EST_RJ_TIME_OUT:
        case RRC_EST_RJ_RA_RESOURCE_FAIL:
        case RRC_EST_RJ_IMMEDIATE_ASSIGN_INVALID:
        case RRC_EST_RJ_ACTIVE_PHISICAL_CHANNEL_FAIL:
        case RRC_EST_RJ_AIRMSG_DECODE_ERR:
        case RRC_EST_RJ_FASTRETURN_LTE:
        case RRC_EST_RJ_RA_FAIL_NO_VALID_INFO:
        case RRC_EST_RJ_CURR_PROTOCOL_NOT_SUPPORT:

        case RRC_EST_RJ_SNW:

        case RRC_EST_RJ_NO_RF:

        case RRC_EST_RJ_T3122_RUNNING:

        case RRC_EST_OTHER_ACCESS_BARRED:
        case RRC_EST_ACCESS_BARRED:
        case RRC_EST_RJ_INTER_RAT:
        case RRC_EST_IMMEDIATE_ASSIGN_REJECT:
        case RRC_EST_RANDOM_ACCESS_REJECT:
        /* RRC_EST_RJ_RA_FAIL是从原来的RRC_EST_RANDOM_ACCESS_REJECT可拆出来的，与RRC_EST_RANDOM_ACCESS_REJECT的处理保持一致
           RRC_EST_RJ_CELL_BAR 是从原来的RRC_EST_ACCESS_BARRED中拆出来的，与RRC_EST_ACCESS_BARRED的处理保持一致 */
        case RRC_EST_RJ_RA_FAIL:
        case RRC_EST_RJ_CELL_BAR:

        case RRC_EST_RANDOM_ACCESS_REJECT_NO_VALID_INFO:
            /*lint -e701*/
            for ( i = 0; i < MM_CONST_NUM_7; i++ )
            {                                                                   /* 重建的MM连接                             */
                if ( MM_CONST_NUM_0 !=
                (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
                    & ( 0x01 << i ) ) )
                {
                    /* 该TI的MM连接正在等待重建 */
                    Mm_SndCcRelInd(i, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_REEST_FAIL);
                }
                if ( MM_CONST_NUM_0 !=
                (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
                    & ( 0x01 << i ) ) )
                {
                    /* 该TI的MM连接正在等待重建 */
                    Mm_SndCcRelInd( ( i + 8 ), NAS_MMCM_REL_CAUSE_MM_INTER_ERR_REEST_FAIL);/* 通知CC,MM连接重建失败                    */
                }
            }

            /*lint +e701*/

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
                = MM_CONST_NUM_0;                                               /* 清除存在的MM连接标志                     */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
                = MM_CONST_NUM_0;                                               /* 清除存在的MM连接标志                     */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* 记录迁移之前的状态                       */
            Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
            PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S14_E32:NORMAL: ucState = ", g_MmGlobalInfo.ucState);
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

                Mm_ComCheckDelayDetach();
            }
            else
            {
                if ( MM_TRUE ==
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
                {                                                               /* 有等待的CC触发的需要建立的MM连接         */
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                    RcvXXEstReq.ucFlg = MM_FALSE;

                    Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                                  NAS_MMCM_REL_CAUSE_MM_INTER_ERR_REEST_FAIL);   /* 通知CC建立失败                           */
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
                        NAS_MMCM_REL_CAUSE_MM_INTER_ERR_REEST_FAIL);
                }
                if ( MM_TRUE ==
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                            RcvXXEstReq.ucFlg )
                {                                                               /* 有等待的CC触发的需要建立的MM连接         */
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                            RcvXXEstReq.ucFlg = MM_FALSE;

                    Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                                   NAS_MMCM_REL_CAUSE_MM_INTER_ERR_REEST_FAIL);
                }
            }

            break;
        case RRC_EST_ESTING:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S14_E32:WARNING: RR CONNECTION ESTING !");
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S14_E32:WARNING: ulResult Abnormal");
            break;
        }

        NAS_MM_UpdateCsServiceConnStatusFlg();

        NAS_MM_UpdateCsServiceBufferStatusFlg();

    }

    return;
}


VOS_VOID Mm_Cell_S9_E33(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{

    RRMM_REL_IND_STRU                   *pRrmmRelInd;
    VOS_UINT8                           ucTiValidFlg = MM_TRUE;
    VOS_UINT8                           ucRrConnRelFlg = MM_TRUE;
    VOS_UINT8                           ucRst;

    VOS_UINT32                          ucEmergencyLauFlg;

    NAS_MM_ClearAuthInfo();

    /* 处理当前缓存的CS域去注册 */
    if ( (VOS_FALSE         == NAS_MM_IsNeedGmmProcUserDetach())
      && (MM_WAIT_CS_DETACH == (g_MmGlobalInfo.stDetachInfo.enDetachType & MM_WAIT_CS_DETACH)) )
    {
        /* 建链不成功，直接本地DETACH */
        NAS_MM_LocalDetach();

        return;
    }

    if ( MM_FALSE == Mm_RcvRrcRelInd(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        NAS_NORMAL_LOG(WUEPS_PID_MM, "Mm_Cell_S9_E33: Rcv RR REL IND, Set CellNotSupportCsmoFlg to TRUE");
        NAS_MML_SetCellNotSupportCsmoFlg(VOS_TRUE);

        ucEmergencyLauFlg = NAS_MM_IsEmergencyCallEndTrigLau();

        ucRrConnRelFlg = Mm_ComRrConnRelChk();
        if ( MM_TRUE == ucRrConnRelFlg )
        {
            Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );                     /* RR连接不存在                             */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }
        g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
        Mm_TimerStop(MM_TIMER_PROTECT_AGENT);
        pRrmmRelInd = (RRMM_REL_IND_STRU*)pRcvMsg;

        ucRst = NAS_MM_RetryCurrentProcedureCheck(pRrmmRelInd->ulRelCause,
                    pRrmmRelInd->ulRrcConnStatus);

        if (VOS_TRUE == ucRst)
        {
            Mm_TimerStop( MM_TIMER_T3230 );                                     /* 停TIMER3230                              */

            Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);

            PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E33:NORMAL: ucState = ", g_MmGlobalInfo.ucState);

            /* 重新发起当前MM CONNECTION建链流程 */
            NAS_MM_RetryMmConnectionProc(g_MmGlobalInfo.ucMMConnEstingPD);
            return;
        }

        switch ( pRrmmRelInd->ulRelCause )
        {                                                                       /* 原因值                                   */
        case RRC_REL_CAUSE_RL_FAILURE:                                          /* Radio Link Failure                       */
        case RRC_REL_CAUSE_CONN_FAIL:                                           /* RR Connection Failure                    */
        case RRC_REL_CAUSE_RR_NORM_EVENT:                                       /* Normal event                             */
        case RRC_REL_CAUSE_RR_UNSPEC:                                           /* Unspecified                              */
        case RRC_REL_CAUSE_RR_PRE_EMPT_REL:                                     /* Pre-emptive release                      */
        case RRC_REL_CAUSE_RR_CONGEST:                                          /* Congedtion                               */
        case RRC_REL_CAUSE_RR_RE_EST_REJ:                                       /* Re-establishment reject                  */
        case RRC_REL_CAUSE_RR_DRIECT_SIGN_CONN_EST:                             /* Directed signal conn re-establish        */
        case RRC_REL_CAUSE_RR_USER_INACT:                                       /* User inactive                            */
        case RRC_REL_CAUSE_UTRAN_RELEASE:                                       /* Signaling Connection Release             */
        case RRC_REL_CAUSE_NAS_REL_SUCCESS:                                     /* NAS Release Connection：Successful       */
        case RRC_REL_CAUSE_NAS_REL_ABSENT:                                      /* NAS Release Connection: Absent           */
        case RRC_REL_CAUSE_NAS_ABORT:                                           /* NAS : Abort                              */
        case RRC_REL_CAUSE_NAS_STOP_SETUP:                                      /* NAS Stop connection setup                */
        case RRC_REL_CAUSE_NAS_DATA_ABSENT:                                     /* NAS Data Request: Connection Absent      */
        case RRC_REL_CAUSE_RRC_ERROR:                                           /* RRC处理异常: RRC ERROR                   */
        case RRC_REL_CAUSE_GAS_TIMEOUT:                                         /* GAS 超时引起 RR 释放 */
        case RRC_REL_CAUSE_OTHER_REASON:                                        /* 其它原因                                 */
        case RRC_REL_CAUSE_NO_RF:                                               /* 没有射频资源 */
        case RRC_REL_CAUSE_RLC_ERROR:
        case RRC_REL_CAUSE_CELL_UPDATE_FAIL:
        case RRC_REL_CAUSE_T314_EXPIRED:
        case RRC_REL_CAUSE_W_RL_FAIL:

        case RRC_REL_CAUSE_G_RL_FAIL:

            Mm_TimerStop( MM_TIMER_T3230 );                                     /* 停TIMER3230                              */

            /* 释放当前正在建立的MM连接的TI */
            NAS_MM_RelEstingMmConn(pRrmmRelInd->ulRelCause);

            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* 记录迁移之前的状态                       */
            Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
            PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E33:NORMAL: ucState = ", g_MmGlobalInfo.ucState);
            Mm_ComProcCauseProcess();

            /* CS未注册下，紧急呼过程中收到attach cs请求先回复attach结果，紧急呼结束链接释放后，
                   判断如果当前有PS业务，需要发起LAU */
            if ( VOS_TRUE == ucEmergencyLauFlg )
            {
                /* 发起LAU */
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;    /* 设置LU类型                               */
                Mm_ComLuOnly();

                return ;
            }

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
                Mm_ComCheckDelayMmConn( MM_FALSE );

                Mm_ComCheckDelayDetach();
            }
            else
            {
                if ( MM_TRUE ==
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
                {                                                               /* 有等待的CC触发的需要建立的MM连接         */
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                                RcvXXEstReq.ucFlg = MM_FALSE;

                    Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                       NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);                          /* 通知CC建立失败                           */
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
                        NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);
                }
                if ( MM_TRUE ==
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                            RcvXXEstReq.ucFlg )
                {                                                               /* 有等待的CC触发的需要建立的MM连接         */
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                            RcvXXEstReq.ucFlg = MM_FALSE;

                    Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                                   NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);
                }
            }
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S9_E33:WARNING: ulRelCause Abnormal");
            break;
        }

        NAS_MM_UpdateCsServiceBufferStatusFlg();
    }

    return;
}


VOS_VOID NAS_MM_NotifyCcErrInd(
    NAS_MMCM_REL_CAUSE_ENUM_UINT32      enCause
)
{
    VOS_UINT8   i;

    i = 0;

    for (i = 0; i < MM_CONST_NUM_7; i++)
    {                                                                           /* 重建的MM连接                             */
        /*lint -e701*/
        if (MM_CONST_NUM_0
            != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
                & (0x01 << i)))
        {                                                                       /* 该TI的MM连接失效                         */
            Mm_SndCcErrInd(i, enCause);                                         /* 通知CC,MM连接失效                        */
        }
        if (MM_CONST_NUM_0
            != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
                & (0x01 << i)))
        {                                                                       /* 该TI的MM连接失效                         */
            Mm_SndCcErrInd(i + 8, enCause);                                              /* 通知CC,MM连接失效                        */
        }


        if (MM_CONST_NUM_0
            != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0]
                & (0x01 << i)))
        {                                                                       /* 该TI的MM连接失效                         */
            Mm_SndSsRelInd(i, enCause);                                                  /* 通知SS,MM连接失效                        */
        }
        if (MM_CONST_NUM_0
            != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1]
                & (0x01 << i)))
        {                                                                       /* 该TI的MM连接失效                         */
            Mm_SndSsRelInd(i + 8, enCause);                                              /* 通知SS,MM连接失效                        */
        }

        if (MM_CONST_NUM_0
            != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0]
                & (0x01 << i)))
        {                                                                       /* 该TI的MM连接失效                         */
            Mm_SndSmsRelInd(i, enCause);                 /* 通知SS,MM连接失效                        */
        }
        if (MM_CONST_NUM_0
            != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]
                & (0x01 << i)))
        {                                                                       /* 该TI的MM连接失效                         */
            Mm_SndSmsRelInd((i + 8), enCause);          /* 通知SS,MM连接失效                        */
        }
        /*lint +e701*/

    }
}


VOS_VOID NAS_MM_HandleRelIndCause15AtS10(VOS_UINT8    ucRrConnRelFlg)
{
    VOS_UINT8    ucTiValidFlg;

    ucTiValidFlg = MM_TRUE;

    NAS_MM_NotifyCcErrInd(NAS_MMCM_REL_CAUSE_RR_REL_RL_FAILURE);

    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[0]
        = g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0];      /* 记录需要重建的标志                       */

    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[1]
        = g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1];      /* 记录需要重建的标志                       */

    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
        = MM_CONST_NUM_0;                                               /* 清除存在的MM连接标志                     */

    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
        = MM_CONST_NUM_0;                                               /* 清除存在的MM连接标志                     */

    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0]
        = MM_CONST_NUM_0;                                               /* 清除存在的MM连接标志                     */

    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1]
        = MM_CONST_NUM_0;                                               /* 清除存在的MM连接标志                     */

    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0]
        = MM_CONST_NUM_0;                                               /* 清除存在的MM连接标志                     */

    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]
        = MM_CONST_NUM_0;                                               /* 清除存在的MM连接标志                     */

    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* 记录迁移之前的状态                       */

    if ((MM_CONST_NUM_0 !=
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[0])
        || (MM_CONST_NUM_0 !=
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[1]))
    {
        Mm_ComSetMmState(WAIT_FOR_REESTABLISH_WAIT_FOR_REEST_REQ);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "NAS_MM_HandleRelIndCause15AtS10:NORMAL: STATUS is WAIT_FOR_REESTABLISH_WAIT_FOR_REEST_REQ");
        Mm_TimerStart(MM_TIMER_PROTECT_CC);                             /* 启动保护TIMER                            */
    }
    else
    {
        if (MM_TRUE == ucRrConnRelFlg)
        {
            Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );                     /* RR连接不存在                             */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }

        Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
        PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "NAS_MM_HandleRelIndCause15AtS10:NORMAL: ucState = ", g_MmGlobalInfo.ucState);

        Mm_ComProcCauseProcess();

        if ( MM_FALSE == Mm_ComChkLu() )
        {
            if ((MM_TRUE
                    == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
                ||(MM_TRUE
                    == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg)
                ||(MM_TRUE
                    == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg))
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

            Mm_ComCheckDelayDetach();
        }
        else
        {
            if (MM_TRUE
                == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
            {                                                           /* 有等待的CC触发的需要建立的MM连接         */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg
                    = MM_FALSE;

                Mm_SndCcRelInd(
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);                      /* 通知CC建立失败                           */
            }
            if (MM_TRUE
                == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg)
            {                                                           /* 有等待的CC触发的需要建立的MM连接         */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg
                    = MM_FALSE;

                Mm_SndSmsRelInd(
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId,
                    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);
            }
            if (MM_TRUE
                == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg)
            {                                                           /* 有等待的CC触发的需要建立的MM连接         */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg
                    = MM_FALSE;

                Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                               NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST );
            }
        }
    }

    NAS_MM_UpdateCsServiceConnStatusFlg();

    NAS_MM_UpdateCsServiceBufferStatusFlg();
}

VOS_VOID Mm_Cell_S10_E33(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    RRMM_REL_IND_STRU                  *pRrmmRelInd;
    VOS_UINT8                           ucRrConnRelFlg;
    VOS_UINT32                          ucEmergencyLauFlg;
    NAS_MMCM_REL_CAUSE_ENUM_UINT32      enMmCcRelCause;

    NAS_MM_ClearAuthInfo();

    /* 处理当前缓存的CS域去注册 */
    if ( (VOS_FALSE         == NAS_MM_IsNeedGmmProcUserDetach())
      && (MM_WAIT_CS_DETACH == (g_MmGlobalInfo.stDetachInfo.enDetachType & MM_WAIT_CS_DETACH)) )
    {
        /* 建链不成功，直接本地DETACH */
        NAS_MM_LocalDetach();

        return;
    }

    ucRrConnRelFlg = MM_TRUE;

    if ( MM_FALSE == Mm_RcvRrcRelInd(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        ucEmergencyLauFlg = NAS_MM_IsEmergencyCallEndTrigLau();

        ucRrConnRelFlg = Mm_ComRrConnRelChk();
        pRrmmRelInd = (RRMM_REL_IND_STRU*)pRcvMsg;

        /* RRC_REL_CAUSE转换为MMCC_REL_CAUSE */
        enMmCcRelCause  = NAS_MM_ConvertRrcRelCauseToMmCcRelCause(pRrmmRelInd->ulRelCause);

        if ((MM_TRUE == ucRrConnRelFlg)
         && (RRC_REL_CAUSE_RL_FAILURE != pRrmmRelInd->ulRelCause))
        {
            Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );                     /* RR连接不存在                             */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }

        switch ( pRrmmRelInd->ulRelCause )
        {                                                                       /* 原因值                                   */
            case RRC_REL_CAUSE_RL_FAILURE:                                          /* Radio Link Failure                       */
                NAS_MM_HandleRelIndCause15AtS10(ucRrConnRelFlg);
                break;

            case RRC_REL_CAUSE_CONN_FAIL:                                           /* RR Connection Failure                    */
            case RRC_REL_CAUSE_RR_NORM_EVENT:                                       /* Normal event                             */
            case RRC_REL_CAUSE_RR_UNSPEC:                                           /* Unspecified                              */
            case RRC_REL_CAUSE_RR_PRE_EMPT_REL:                                     /* Pre-emptive release                      */
            case RRC_REL_CAUSE_RR_CONGEST:                                          /* Congedtion                               */
            case RRC_REL_CAUSE_RR_RE_EST_REJ:                                       /* Re-establishment reject                  */
            case RRC_REL_CAUSE_RR_DRIECT_SIGN_CONN_EST:                             /* Directed signal conn re-establish        */
            case RRC_REL_CAUSE_RR_USER_INACT:                                       /* User inactive                            */
            case RRC_REL_CAUSE_UTRAN_RELEASE:                                       /* Signaling Connection Release             */
            case RRC_REL_CAUSE_NAS_REL_SUCCESS:                                     /* NAS Release Connection：Successful       */
            case RRC_REL_CAUSE_NAS_REL_ABSENT:                                      /* NAS Release Connection: Absent           */
            case RRC_REL_CAUSE_NAS_ABORT:                                           /* NAS : Abort                              */
            case RRC_REL_CAUSE_NAS_STOP_SETUP:                                      /* NAS Stop connection setup                */
            case RRC_REL_CAUSE_NAS_DATA_ABSENT:                                     /* NAS Data Request: Connection Absent      */
            case RRC_REL_CAUSE_RRC_ERROR:                                           /* RRC处理异常: RRC ERROR                   */
            case RRC_REL_CAUSE_GAS_TIMEOUT:                                         /* GAS 超时引起 RR 释放 */
            case RRC_REL_CAUSE_OTHER_REASON:                                        /* 其它原因                                 */
            case RRC_REL_CAUSE_NO_RF:                                               /* 没有射频资源 */
            case RRC_REL_CAUSE_RLC_ERROR:
            case RRC_REL_CAUSE_CELL_UPDATE_FAIL:
            case RRC_REL_CAUSE_T314_EXPIRED:
            case RRC_REL_CAUSE_W_RL_FAIL:

            case RRC_REL_CAUSE_G_RL_FAIL:



                Mm_ComRelAllMmConn(enMmCcRelCause);

                                                              /* 释放所有mm连接                           */
                g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;               /* 记录迁移之前的状态                       */
                Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
                PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S10_E33:NORMAL: ucState = ", g_MmGlobalInfo.ucState);
                Mm_ComProcCauseProcess();

                Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);         /* RR连接不存在                             */
                NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);


                /* CS未注册下，紧急呼过程中收到attach cs请求先回复attach结果，紧急呼结束链接释放后，
                   判断如果当前有PS业务，需要发起LAU */
                if ( VOS_TRUE == ucEmergencyLauFlg )
                {
                    /* 发起LAU */
                    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;    /* 设置LU类型                               */
                    Mm_ComLuOnly();

                    return ;
                }

                if ( MM_FALSE == Mm_ComChkLu() )
                {
                    (VOS_VOID)NAS_MM_NotifyBufferedServiceRRConnNotExist();

                    Mm_ComCheckDelayMmConn( MM_FALSE );

                    Mm_ComCheckDelayDetach();
                }
                break;

            default:
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S10_E33:WARNING: ulRelCause Abnormal");
                break;
        }
    }

    return;
}


VOS_VOID Mm_Cell_S11_E33(
    VOS_VOID                           *pRcvMsg                                /* 接收消息的头地址                         */
)
{
    RRMM_REL_IND_STRU                  *pRrmmRelInd;
    VOS_UINT8                           ucRrConnRelFlg;
    VOS_UINT32                          ucEmergencyLauFlg;
#if (FEATURE_ON == FEATURE_PTM)
    VOS_UINT8                           ucCsServiceConnStatusFlg;
#endif

    NAS_MM_ClearAuthInfo();

    /* 处理当前缓存的CS域去注册 */
    if ( (VOS_FALSE         == NAS_MM_IsNeedGmmProcUserDetach())
      && (MM_WAIT_CS_DETACH == (g_MmGlobalInfo.stDetachInfo.enDetachType & MM_WAIT_CS_DETACH)) )
    {
        /* 建链不成功，直接本地DETACH */
        NAS_MM_LocalDetach();

        return;
    }

    ucRrConnRelFlg = MM_TRUE;

    if ( MM_FALSE == Mm_RcvRrcRelInd(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        ucEmergencyLauFlg = NAS_MM_IsEmergencyCallEndTrigLau();

        ucRrConnRelFlg = Mm_ComRrConnRelChk();
        if ( MM_TRUE == ucRrConnRelFlg )
        {
            Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );                     /* RR连接不存在                             */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);

            NAS_MML_SetCsEmergencyServiceFlg(VOS_FALSE);

            Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);

        }

#if (FEATURE_ON == FEATURE_PTM)
        ucCsServiceConnStatusFlg = NAS_MML_GetCsServiceConnStatusFlg();
        /* MT的场景且非CSFB MT则记录异常 */
        if ((NAS_ERR_LOG_CSFB_MT_STATE_NULL == NAS_MML_GetCsfbMtCurrState())
         && (VOS_TRUE == ucCsServiceConnStatusFlg))
        {
            /* 收到CS PAGING后连接建立成功，但还未收到业务消息，收到底层释放指示的异常记录 */
            NAS_MM_CsPagingFailRecord(NAS_ERR_LOG_CS_PAGING_CAUSE_CONN_RELEASED);
        }

        /* 在CSFB MT保护定时器超时状态下收到REL IND，清除CSFB的状态信息 */
        if (NAS_ERR_LOG_BASE_STATE_CSFB_MT_TI_TIME_OUT_RCV_REL_IND == NAS_MML_GetCsfbMtCurrState())
        {
            NAS_MM_ClearErrorLogInfo();
        }
#endif

        pRrmmRelInd = (RRMM_REL_IND_STRU*)pRcvMsg;
        switch ( pRrmmRelInd->ulRelCause )
        {                                                                       /* 原因值                                   */
            case RRC_REL_CAUSE_NAS_REL_SUCCESS:                                     /* NAS Release Connection：Successful       */
            case RRC_REL_CAUSE_NAS_REL_ABSENT:                                      /* NAS Release Connection: Absent           */
            case RRC_REL_CAUSE_NAS_ABORT:                                           /* NAS : Abort                              */
            case RRC_REL_CAUSE_RL_FAILURE:                                          /* Radio Link Failure                       */
            case RRC_REL_CAUSE_CONN_FAIL:                                           /* RR Connection Failure                    */
            case RRC_REL_CAUSE_RR_NORM_EVENT:                                       /* Normal event                             */
            case RRC_REL_CAUSE_RR_UNSPEC:                                           /* Unspecified                              */
            case RRC_REL_CAUSE_RR_PRE_EMPT_REL:                                     /* Pre-emptive release                      */
            case RRC_REL_CAUSE_RR_CONGEST:                                          /* Congedtion                               */
            case RRC_REL_CAUSE_RR_RE_EST_REJ:                                       /* Re-establishment reject                  */
            case RRC_REL_CAUSE_RR_DRIECT_SIGN_CONN_EST:                             /* Directed signal conn re-establish        */
            case RRC_REL_CAUSE_RR_USER_INACT:                                       /* User inactive                            */
            case RRC_REL_CAUSE_UTRAN_RELEASE:                                       /* Signaling Connection Release             */
            case RRC_REL_CAUSE_NAS_STOP_SETUP:                                      /* NAS Stop connection setup                */
            case RRC_REL_CAUSE_NAS_DATA_ABSENT:                                     /* NAS Data Request: Connection Absent      */
            case RRC_REL_CAUSE_RRC_ERROR:                                           /* RRC处理异常: RRC ERROR                   */
            case RRC_REL_CAUSE_GAS_TIMEOUT:                                         /* GAS 超时引起 RR 释放 */
            case RRC_REL_CAUSE_OTHER_REASON:                                        /* 其它原因                                 */
            case RRC_REL_CAUSE_NO_RF:                                               /* 没有射频资源 */
            case RRC_REL_CAUSE_RLC_ERROR:
            case RRC_REL_CAUSE_CELL_UPDATE_FAIL:
            case RRC_REL_CAUSE_T314_EXPIRED:
            case RRC_REL_CAUSE_W_RL_FAIL:

            case RRC_REL_CAUSE_G_RL_FAIL:



                Mm_TimerStop( MM_TIMER_T3240 );
                g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;

                /*根据协议4.7.5.1.4，ATTACH或者RAU拒绝原因值为15不发起LAU*/
                if (( (NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL == g_MmGlobalInfo.usCauseVal)
                    || (NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == g_MmGlobalInfo.usCauseVal)
                    || (NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW == g_MmGlobalInfo.usCauseVal)
                    || (NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW == g_MmGlobalInfo.usCauseVal))
                 && (  (MM_GMM_RAU_PROC                       == g_MmGlobalInfo.ucProc)
                    || (MM_GMM_ATTACH_PROC                    == g_MmGlobalInfo.ucProc) )
                 && (MM_NORMAL_SERVICE                        == g_MmGlobalInfo.ucMmServiceState) )
                {
                    /* 对比标杆:在PS注册失败#15时,不影响CS的注册过程.
                       当PS先注册失败,CS注册成功时,MMC先删除禁止LAI,然后PS域再发起一次注册,最终结果是当前的LAI加入禁止LAI列表中 */
                    /*Mm_ComProcCauseProcess中将全局变量g_MmGlobalInfo.ucProc和
                      g_MmGlobalInfo.ucCauseVal清除*/
                    /* Mm_ComProcCauseProcess(); */
                    g_MmGlobalInfo.usCauseVal = NAS_MML_REG_FAIL_CAUSE_NULL;
                    g_MmGlobalInfo.ucProc     = MM_NULL_PROC;
                    Mm_ComProcCauseProcess_Handling_LU_PROC();
                }
                else
                {
                    Mm_ComProcCauseProcess();

                    /* CS未注册下，紧急呼过程中收到attach cs请求先回复attach结果，紧急呼结束链接释放后，
                       判断如果当前有PS业务，需要发起LAU */
                    if ( VOS_TRUE == ucEmergencyLauFlg )
                    {
                        /* 发起LAU */
                        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;   /* 设置LU类型                               */
                        Mm_ComLuOnly();

                        NAS_MM_UpdateCsServiceConnStatusFlg();

                        return ;
                    }

                    if ((MM_TRUE == Mm_ComChkLu())
                      || (WAIT_FOR_RR_CONNECTION_LOCATION_UPDATING ==
                                                g_MmGlobalInfo.ucState))
                    {
                        NAS_MM_UpdateCsServiceConnStatusFlg();

                        return;
                    }
                }

                /*不做LAU或者已发起LAU进行如下处理:*/

                (VOS_VOID)NAS_MM_NotifyBufferedServiceRRConnNotExist();

                Mm_ComCheckDelayMmConn(MM_FALSE);

                NAS_MM_UpdateCsServiceConnStatusFlg();

                /*没有缓存业务存在时,如果服务域设置为PS ONLY需要Detach CS*/
                Mm_ComCheckDelayDetach();

                break;
            default:
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S11_E33:WARNING: ulRelCause Abnormal");
                break;
        }
    }

    return;
}

VOS_VOID    Mm_Cell_S12_E33(VOS_VOID *pRcvMsg )
{
    VOS_UINT8                           ucValidFlg;

    RRMM_REL_IND_STRU                  *pstRelMsg  = VOS_NULL_PTR;

    VOS_UINT32                          ucEmergencyLauFlg;

    NAS_MMCM_REL_CAUSE_ENUM_UINT32      enMmCcRelCause;

#if (FEATURE_ON == FEATURE_PTM)
    VOS_UINT8                           ucCsServiceConnStatusFlg;
#endif

    pstRelMsg = (RRMM_REL_IND_STRU *)pRcvMsg;

    ucValidFlg = Mm_RcvRrcRelInd(pRcvMsg);

    ucEmergencyLauFlg = NAS_MM_IsEmergencyCallEndTrigLau();

    NAS_MM_ClearAuthInfo();

    enMmCcRelCause  = NAS_MM_ConvertRrcRelCauseToMmCcRelCause(pstRelMsg->ulRelCause);


    /* 处理当前缓存的CS域去注册 */
    if ( (VOS_FALSE         == NAS_MM_IsNeedGmmProcUserDetach())
      && (MM_WAIT_CS_DETACH == (g_MmGlobalInfo.stDetachInfo.enDetachType & MM_WAIT_CS_DETACH)) )
    {
        /* 建链不成功，直接本地DETACH */
        NAS_MM_LocalDetach();

        return;
    }

    if (MM_TRUE == ucValidFlg)
    {
        /* 停止保护定时器 */
        Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);
        /* 通知MMC连接不存在 */
        Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);

        /* 记录迁移之前的状态  */
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
        /* 状态迁移   */
        Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
        PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E33:NORMAL: ucState = ", g_MmGlobalInfo.ucState);

        /* 如果是在MM连接建立过程中发生LAI改变，不需要释放所有MM连接,正在建的MM连接 */
        if(VOS_FALSE == g_MmGlobalInfo.ucPendingLu)
        {
            Mm_ComRelAllMmConn(enMmCcRelCause);
        }

        /* 处理缓存的LU流程 */


        /* CS未注册下，紧急呼过程中收到attach cs请求先回复attach结果，紧急呼结束链接释放后，
                   判断如果当前有PS业务，需要发起LAU */
        if ( VOS_TRUE == ucEmergencyLauFlg )
        {
            /* 发起LAU */
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;    /* 设置LU类型                               */
            Mm_ComLuOnly();

            return ;
        }

        if (MM_FALSE == Mm_ComChkLu())
        {
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S12_E33:WARNING: Mm_ComChkLu return MM_FALSE\n");
        }

        g_MmGlobalInfo.ucPendingLu = VOS_FALSE;

#if (FEATURE_ON == FEATURE_PTM)
        ucCsServiceConnStatusFlg = NAS_MML_GetCsServiceConnStatusFlg();
        /* 收到CS PAGING后连接建立时收到底层释放指示的异常记录 */
        if ((NAS_ERR_LOG_CSFB_MT_STATE_NULL == NAS_MML_GetCsfbMtCurrState())
         && (VOS_TRUE == ucCsServiceConnStatusFlg))
        {
            NAS_MM_CsPagingFailRecord(NAS_ERR_LOG_CS_PAGING_CAUSE_EST_RELEASED);
        }

        /* 在CSFB MT保护定时器超时状态下收到REL IND，清除CSFB的状态信息 */
        if (NAS_ERR_LOG_BASE_STATE_CSFB_MT_TI_TIME_OUT_RCV_REL_IND == NAS_MML_GetCsfbMtCurrState())
        {
            NAS_MM_ClearErrorLogInfo();
        }
#endif

        Mm_ComCheckDelayDetach();

        /* 需要清除MM保存的GMM的cause值 */
        Mm_ComProcCauseClear();

    }
    else
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S12_E33:WARNING: ulRelCause Abnormal");
    }
}

VOS_VOID Mm_Cell_S14_E33(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    VOS_UINT8                i = 0;                                             /* 循环计数变量                             */
    RRMM_REL_IND_STRU       *pRrmmRelInd    = VOS_NULL_PTR;
    VOS_UINT8                ucTiValidFlg   = MM_TRUE;
    VOS_UINT8                ucRrConnRelFlg = MM_TRUE;

    VOS_UINT32                          ucEmergencyLauFlg;

    NAS_MM_ClearAuthInfo();

    /* 处理当前缓存的CS域去注册 */
    if ( (VOS_FALSE         == NAS_MM_IsNeedGmmProcUserDetach())
      && (MM_WAIT_CS_DETACH == (g_MmGlobalInfo.stDetachInfo.enDetachType & MM_WAIT_CS_DETACH)) )
    {
        /* 建链不成功，直接本地DETACH */
        NAS_MM_LocalDetach();

        return;
    }

    if ( MM_FALSE == Mm_RcvRrcRelInd(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        ucEmergencyLauFlg = NAS_MM_IsEmergencyCallEndTrigLau();

        ucRrConnRelFlg = Mm_ComRrConnRelChk();
        if ( MM_TRUE == ucRrConnRelFlg )
        {
            Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );                     /* RR连接不存在                             */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }
        pRrmmRelInd = (RRMM_REL_IND_STRU*)pRcvMsg;

        Mm_TimerStop( MM_TIMER_T3230 );                                         /* 停TIMER3230                              */
        switch ( pRrmmRelInd->ulRelCause )
        {                                                                       /* 原因值                                   */
        case RRC_REL_CAUSE_RL_FAILURE:                                          /* Radio Link Failure                       */
        case RRC_REL_CAUSE_CONN_FAIL:                                           /* RR Connection Failure                    */
        case RRC_REL_CAUSE_NAS_REL_SUCCESS:                                     /* NAS Release Connection：Successful       */
        case RRC_REL_CAUSE_NAS_REL_ABSENT:                                      /* NAS Release Connection: Absent           */
        case RRC_REL_CAUSE_NAS_ABORT:                                           /* NAS : Abort                              */
        case RRC_REL_CAUSE_RR_NORM_EVENT:                                       /* Normal event                             */
        case RRC_REL_CAUSE_RR_UNSPEC:                                           /* Unspecified                              */
        case RRC_REL_CAUSE_RR_PRE_EMPT_REL:                                     /* Pre-emptive release                      */
        case RRC_REL_CAUSE_RR_CONGEST:                                          /* Congedtion                               */
        case RRC_REL_CAUSE_RR_RE_EST_REJ:                                       /* Re-establishment reject                  */
        case RRC_REL_CAUSE_RR_DRIECT_SIGN_CONN_EST:                             /* Directed signal conn re-establish        */
        case RRC_REL_CAUSE_RR_USER_INACT:                                       /* User inactive                            */
        case RRC_REL_CAUSE_UTRAN_RELEASE:                                       /* Signaling Connection Release             */
        case RRC_REL_CAUSE_NAS_STOP_SETUP:                                      /* NAS Stop connection setup                */
        case RRC_REL_CAUSE_NAS_DATA_ABSENT:                                     /* NAS Data Request: Connection Absent      */
        case RRC_REL_CAUSE_RRC_ERROR:                                           /* RRC处理异常: RRC ERROR                   */
        case RRC_REL_CAUSE_GAS_TIMEOUT:                                         /* GAS 超时引起 RR 释放 */
        case RRC_REL_CAUSE_OTHER_REASON:                                        /* 其它原因                                 */
        case RRC_REL_CAUSE_NO_RF:                                               /* 没有射频资源 */
        case RRC_REL_CAUSE_RLC_ERROR:
        case RRC_REL_CAUSE_CELL_UPDATE_FAIL:
        case RRC_REL_CAUSE_T314_EXPIRED:
        case RRC_REL_CAUSE_W_RL_FAIL:

        case RRC_REL_CAUSE_G_RL_FAIL:

            for ( i = 0; i < MM_CONST_NUM_7; i++ )
            {                                                                   /* 重建的MM连接                             */
                /*lint -e701*/
                if ( MM_CONST_NUM_0 !=
                        ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                    aucMMConnExtFlg[0] & ( 0x01 << i ) ) )
                {
                    /* 该TI的MM连接失效                         */
                    Mm_SndCcRelInd( i, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_REEST_FAIL);       /* 通知CC,MM连接建立失败                    */
                }
                if ( MM_CONST_NUM_0 !=
                ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                    aucMMConnExtFlg[1] & ( 0x01 << i ) ) )
                {
                    /* 该TI的MM连接失效                         */
                    Mm_SndCcRelInd( ( i + 8 ), NAS_MMCM_REL_CAUSE_MM_INTER_ERR_REEST_FAIL);
                }
                /*lint +e701*/
            }
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
                = MM_CONST_NUM_0;                                               /* 清除存在的MM连接标志                     */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
                = MM_CONST_NUM_0;                                               /* 清除存在的MM连接标志                     */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* 记录迁移之前的状态                       */
            Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
            PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S14_E33:NORMAL: ucState = ", g_MmGlobalInfo.ucState);
            Mm_ComProcCauseProcess();


            /* CS未注册下，紧急呼过程中收到attach cs请求先回复attach结果，紧急呼结束链接释放后，
                   判断如果当前有PS业务，需要发起LAU */
            if ( VOS_TRUE == ucEmergencyLauFlg )
            {
                /* 发起LAU */
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;           /* 设置LU类型                               */
                Mm_ComLuOnly();

                return ;
            }

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
                    Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );
                    NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
                }
                Mm_ComCheckDelayMmConn( MM_FALSE );

                Mm_ComCheckDelayDetach();
            }
            else
            {
                /* WAIT FOR REESTABLISH(WAIT FOR EST_CNF)收到rel ind不再重拨 */
                NAS_MM_RelBufferedServiceEstReq(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_REEST_FAIL);
            }
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S14_E33:WARNING: ulRelCause Abnormal");
            break;
        }

        NAS_MM_UpdateCsServiceConnStatusFlg();

        NAS_MM_UpdateCsServiceBufferStatusFlg();
    }

    return;
}

VOS_VOID Mm_Cell_S16_E33(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    VOS_UINT8                i = 0;                                             /* 循环计数变量                             */
    RRMM_REL_IND_STRU       *pRrmmRelInd;
    VOS_UINT8                ucTiValidFlg = MM_TRUE;
    VOS_UINT8                ucRrConnRelFlg = MM_TRUE;
    NAS_MMCM_REL_CAUSE_ENUM_UINT32      enMmCcRelCause;


    NAS_MM_ClearAuthInfo();

    /* 处理当前缓存的CS域去注册 */
    if ( (VOS_FALSE         == NAS_MM_IsNeedGmmProcUserDetach())
      && (MM_WAIT_CS_DETACH == (g_MmGlobalInfo.stDetachInfo.enDetachType & MM_WAIT_CS_DETACH)) )
    {
        /* 建链不成功，直接本地DETACH */
        NAS_MM_LocalDetach();

        return;
    }

    if ( MM_FALSE == Mm_RcvRrcRelInd(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        ucRrConnRelFlg = Mm_ComRrConnRelChk();
        if ( MM_TRUE == ucRrConnRelFlg )
        {
            Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );                     /* RR连接不存在                             */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }
        pRrmmRelInd = (RRMM_REL_IND_STRU*)pRcvMsg;
        Mm_TimerStop( MM_TIMER_T3230 );                                         /* 停TIMER3230                              */

        enMmCcRelCause  = NAS_MM_ConvertRrcRelCauseToMmCcRelCause(pRrmmRelInd->ulRelCause);


        switch ( pRrmmRelInd->ulRelCause )
        {                                                                       /* 原因值                                   */
        case RRC_REL_CAUSE_RL_FAILURE:                                          /* Radio Link Failure                       */
            NAS_MM_RelEstingMmConn(pRrmmRelInd->ulRelCause);

            for ( i = 0; i < MM_CONST_NUM_7; i++ )
            {                                                                   /* 重建的MM连接                             */
                /*lint -e701*/
                if ( MM_CONST_NUM_0 !=
                ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                aucMMConnExtFlg[0] & ( 0x01 << i ) ) )
                {                                                               /* 该TI的MM连接失效                         */
                    Mm_SndCcErrInd( i, NAS_MMCM_REL_CAUSE_RR_REL_RL_FAILURE );                                        /* 通知CC,MM连接失效                        */
                }
                if ( MM_CONST_NUM_0 !=
                ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                aucMMConnExtFlg[1] & ( 0x01 << i ) ) )
                {                                                               /* 该TI的MM连接失效                         */
                    Mm_SndCcErrInd( i + 8, NAS_MMCM_REL_CAUSE_RR_REL_RL_FAILURE );                                    /* 通知CC,MM连接失效                        */
                }
                if ( MM_CONST_NUM_0 !=
                    ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                    aucMMConnExtFlg[0] & ( 0x01 << i ) ) )
                {                                                               /* 该TI的MM连接失效                         */
                    Mm_SndSsRelInd(i, NAS_MMCM_REL_CAUSE_RR_REL_RL_FAILURE);                                        /* 通知SS,MM连接失效                        */
                }
                if ( MM_CONST_NUM_0 !=
                    ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                    aucMMConnExtFlg[1] & ( 0x01 << i ) ) )
                {                                                               /* 该TI的MM连接失效                         */
                    Mm_SndSsRelInd( i + 8, NAS_MMCM_REL_CAUSE_RR_REL_RL_FAILURE);                                    /* 通知SS,MM连接失效                        */

                }
                if ( MM_CONST_NUM_0 !=
                    (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                    aucMMConnExtFlg[0] & ( 0x01 << i ) ) )
                {                                                               /* 该TI的MM连接失效                         */
                    Mm_SndSmsRelInd( i, NAS_MMCM_REL_CAUSE_RR_REL_RL_FAILURE );        /* 通知SS,MM连接失效                        */
                }
                if ( MM_CONST_NUM_0 !=
                    ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                    aucMMConnExtFlg[1]  & ( 0x01 << i ) ) )
                {                                                               /* 该TI的MM连接失效                         */
                    Mm_SndSmsRelInd( (i + 8), NAS_MMCM_REL_CAUSE_RR_REL_RL_FAILURE ); /* 通知SS,MM连接失效                        */
                }
                /*lint +e701*/
            }
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[0] =
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0];/* 记录需要重建的标志                       */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[1] =
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1];/* 记录需要重建的标志                       */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
                = MM_CONST_NUM_0;                                               /* 清除存在的MM连接标志                     */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
                = MM_CONST_NUM_0;                                               /* 清除存在的MM连接标志                     */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0]
                = MM_CONST_NUM_0;                                               /* 清除存在的MM连接标志                     */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1]
                = MM_CONST_NUM_0;                                               /* 清除存在的MM连接标志                     */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0]
                = MM_CONST_NUM_0;                                               /* 清除存在的MM连接标志                     */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]
                = MM_CONST_NUM_0;                                               /* 清除存在的MM连接标志                     */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* 记录迁移之前的状态                       */
            if ( ( MM_CONST_NUM_0 !=
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                                        aucMMConnReestFlg[0] )
                || ( MM_CONST_NUM_0 !=
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                                        aucMMConnReestFlg[1] )
                )
            {
                Mm_ComSetMmState(WAIT_FOR_REESTABLISH_WAIT_FOR_REEST_REQ);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S16_E33:NORMAL: STATUS is  WAIT_FOR_REESTABLISH_WAIT_FOR_REEST_REQ");
                Mm_TimerStart(MM_TIMER_PROTECT_CC);                             /* 启动保护TIMER                            */
            }
            else
            {
                Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
                PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S16_E33:NORMAL: ucState = ", g_MmGlobalInfo.ucState);
                Mm_ComProcCauseProcess();
                if ( MM_FALSE == Mm_ComChkLu() )
                {
                    if ( ( MM_TRUE ==
                        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                                        RcvXXEstReq.ucFlg)
                        ||( MM_TRUE ==
                        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                                        RcvXXEstReq.ucFlg)
                        ||( MM_TRUE ==
                        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                                        RcvXXEstReq.ucFlg ) )
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

                    Mm_ComCheckDelayDetach();
                }
                else
                {
                    if ( MM_TRUE ==
                        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                                RcvXXEstReq.ucFlg )
                    {                                                           /* 有等待的CC触发的需要建立的MM连接         */
                        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                                RcvXXEstReq.ucFlg = MM_FALSE;

                        Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                                 NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);                      /* 通知CC建立失败                           */

                    }
                    if ( MM_TRUE ==
                        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                                RcvXXEstReq.ucFlg )
                    {                                                           /* 有等待的CC触发的需要建立的MM连接         */
                        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                                RcvXXEstReq.ucFlg = MM_FALSE;

                        Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId,
                                        NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);
                    }
                    if ( MM_TRUE ==
                        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                                RcvXXEstReq.ucFlg )
                    {                                                           /* 有等待的CC触发的需要建立的MM连接         */
                        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                                RcvXXEstReq.ucFlg = MM_FALSE;

                        Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                                       NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST );
                    }
                }
            }
            break;
        case RRC_REL_CAUSE_CONN_FAIL:                                           /* RR Connection Failure                    */
        case RRC_REL_CAUSE_NAS_REL_SUCCESS:                                     /* NAS Release Connection：Successful       */
        case RRC_REL_CAUSE_NAS_REL_ABSENT:                                      /* NAS Release Connection: Absent           */
        case RRC_REL_CAUSE_NAS_ABORT:                                           /* NAS : Abort                              */
        case RRC_REL_CAUSE_RR_NORM_EVENT:                                       /* Normal event                             */
        case RRC_REL_CAUSE_RR_UNSPEC:                                           /* Unspecified                              */
        case RRC_REL_CAUSE_RR_PRE_EMPT_REL:                                     /* Pre-emptive release                      */
        case RRC_REL_CAUSE_RR_CONGEST:                                          /* Congedtion                               */
        case RRC_REL_CAUSE_RR_RE_EST_REJ:                                       /* Re-establishment reject                  */
        case RRC_REL_CAUSE_RR_DRIECT_SIGN_CONN_EST:                             /* Directed signal conn re-establish        */
        case RRC_REL_CAUSE_RR_USER_INACT:                                       /* User inactive                            */
        case RRC_REL_CAUSE_UTRAN_RELEASE:                                       /* Signaling Connection Release             */
        case RRC_REL_CAUSE_NAS_STOP_SETUP:                                      /* NAS Stop connection setup                */
        case RRC_REL_CAUSE_NAS_DATA_ABSENT:                                     /* NAS Data Request: Connection Absent      */
        case RRC_REL_CAUSE_RRC_ERROR:                                           /* RRC处理异常: RRC ERROR                   */
        case RRC_REL_CAUSE_GAS_TIMEOUT:                                         /* GAS 超时引起 RR 释放 */
        case RRC_REL_CAUSE_OTHER_REASON:                                        /* 其它原因                                 */
        case RRC_REL_CAUSE_NO_RF:                                               /* 没有射频资源 */
        case RRC_REL_CAUSE_RLC_ERROR:
        case RRC_REL_CAUSE_CELL_UPDATE_FAIL:
        case RRC_REL_CAUSE_T314_EXPIRED:
        case RRC_REL_CAUSE_W_RL_FAIL:

        case RRC_REL_CAUSE_G_RL_FAIL:

            Mm_ComRelAllMmConn(enMmCcRelCause);
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* 记录迁移之前的状态                       */
            Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
            PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S16_E33:NORMAL: ucState = ", g_MmGlobalInfo.ucState);
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
                        Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );         /* RR连接不存在                             */
                        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
                    }
                    else
                    {
                        Mm_ComSigRelForDelayMmConnRej();
                    }
                }
                Mm_ComCheckDelayMmConn( MM_FALSE );

                Mm_ComCheckDelayDetach();
            }
            else
            {
                if ( MM_TRUE ==
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                            RcvXXEstReq.ucFlg )
                {                                                               /* 有等待的CC触发的需要建立的MM连接         */
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                            RcvXXEstReq.ucFlg = MM_FALSE;

                    Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                             NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);                          /* 通知CC建立失败                           */
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
                        NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);
                }
                if ( MM_TRUE ==
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                            RcvXXEstReq.ucFlg )
                {                                                               /* 有等待的CC触发的需要建立的MM连接         */
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                            RcvXXEstReq.ucFlg = MM_FALSE;

                    Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                                   NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST );
                }
            }
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S16_E33:WARNING: ulRelCause Abnormal");
            break;
        }
    }

    NAS_MM_UpdateCsServiceConnStatusFlg();

    NAS_MM_UpdateCsServiceBufferStatusFlg();

    return;
}

VOS_VOID Mm_Cell_S9_E34(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    if ( MM_FALSE == Mm_RcvRrcSecurityInd(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        if (( RRC_SECURITY_CS_SMC_CMPL == g_MmGlobalInfo.CsSecutityInfo.ucSecurityType)
            && ( MM_LIMITED_SERVICE != g_MmGlobalInfo.ucMmServiceState))
        {
            Mm_TimerStop( MM_TIMER_T3212 );                                     /* 停T3212                                  */
        }
        if ( RRC_SECURITY_CS_SMC_CMPL == g_MmGlobalInfo.CsSecutityInfo.ucSecurityType)
        {                                                                       /* 完整性保护和安全模式启动                 */
            Mm_TimerStop( MM_TIMER_T3230 );                                     /* 停TIMER3230                              */
            switch ( g_MmGlobalInfo.ucMMConnEstingPD )
            {                                                                   /* 确定是哪个PD建立的MM连接                 */
            case MM_IE_PD_CALL_CONTROL:                                         /* CC要求建立的MM连接                       */
                Mm_SndCcEstCnf(
                    (VOS_UINT32)( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                        ucMMConnEstingTI), MMCC_EST_SUCCESS );  /* 该MM连接建立成功                         */
                /*lint -e701*/
                if ( MM_CONST_NUM_7 >
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI )
                {                                                               /*TI小于7                                   */
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                    aucMMConnExtFlg[0] =
                        (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                        aucMMConnExtFlg[0] |
                        (VOS_UINT8)( 0x01 << g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                        ucMMConnEstingTI ) );                                   /* 设置MM连接存在标志                       */
                }
                else
                {                                                               /*TI大于7                                   */
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                    aucMMConnExtFlg[1] =
                        (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                        aucMMConnExtFlg[1] |
                        (VOS_UINT8)( 0x01 <<
                        ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                        ucMMConnEstingTI - 8 )) );                              /* 设置MM连接存在标志                       */
                }
                /*lint +e701*/
#if (FEATURE_ON == FEATURE_ECALL)
                /* 处理eCall定时器启动标识 */
                NAS_MM_RecordEcallTimerStartNeededFlag();
#endif

                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI
                    = NO_MM_CONN_ESTING;                                        /* 清除正在建立的MM连接的标志               */
                break;
            case MM_IE_PD_SMS_MSG:                                              /* SMS要求建立的MM连接                      */
                if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())      /* 在GSM网络中短消息主叫需要建立SAPI3       */
                {
                    if (MM_MO_PAGING == g_MmGlobalInfo.ucPagingType)            /* 主叫 */
                    {
                        if (MM_FALSE == MM_SndSapi3EstReq())
                        {
                            Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI,
                                        NAS_MMCM_REL_CAUSE_MM_INTER_ERR_SND_SAPI3_FAIL);

                            Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
                            NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_ERROR,
                                        "Mm_Cell_S9_E34: ERROR: snd SAPI3 est fail.");

                            g_MmGlobalInfo.ucMMConnEstingPD = NO_MM_CONN_ESTING;       /* 设置没有正在建立的连接           */

                            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI
                                        = NO_MM_CONN_ESTING;

                            g_MmGlobalInfo.ucPagingType     = MM_NO_PAGING;

                            return;
                        }

                        Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);

                        g_MmGlobalInfo.ucPagingType = MM_NO_PAGING;

                        return;
                    }
                }

                Mm_SndSmsEstCnf( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                    ucMMConnEstingTI );                                         /* 该MM连接建立成功                         */
                /*lint -e701*/
                if ( MM_CONST_NUM_7 >
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI )
                {                                                               /*TI小于7                                   */
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                        aucMMConnExtFlg[0] |=
                        (VOS_UINT8)( 0x01 << g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                        ucMMConnEstingTI );                                     /* 设置MM连接存在标志                       */
                }
                else
                {                                                               /*TI大于7                                   */
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                        aucMMConnExtFlg[1] |= (VOS_UINT8)( 0x01 <<
                        ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                        ucMMConnEstingTI - 8 ) );                               /* 设置MM连接存在标志                       */
                }
                /*lint +e701*/
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI
                    = NO_MM_CONN_ESTING;                                        /* 清除正在建立的MM连接的标志               */
                break;
            case MM_IE_PD_NON_CALL_RLT_SS_MSG:                                  /* SS要求建立的MM连接                       */
                Mm_SndSsEstCnf( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                    ucMMConnEstingTI, MMSS_EST_SUCCESS );                       /* 该MM连接建立成功                         */
                /*lint -e701*/
                if ( MM_CONST_NUM_7 >
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI )
                {                                                               /*TI小于7                                   */
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                        aucMMConnExtFlg[0]
                     |= (VOS_UINT8)( 0x01 << g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                        ucMMConnEstingTI );                                     /* 设置MM连接存在标志                       */
                }
                else
                {                                                               /*TI大于7                                   */
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                        aucMMConnExtFlg[1] |= (VOS_UINT8)( 0x01 <<
                        ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                        ucMMConnEstingTI - 8 ) );                               /* 设置MM连接存在标志                       */
                }
                /*lint +e701*/
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI
                    = NO_MM_CONN_ESTING;                                        /* 清除正在建立的MM连接的标志               */
                break;
            default:
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S9_E34:WARNING: g_MmGlobalInfo.ucMMConnEstingPD Abnormal");
                break;
            }
            g_MmGlobalInfo.ucMMConnEstingPD = NO_MM_CONN_ESTING;                /* 设置没有正在建立的连接                   */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* 记录迁移之前的状态                       */
            Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E34:NORMAL: STATUS is  MM_CONNECTION_ACTIVE");
            Mm_ComCheckDelayMmConn( MM_FALSE );                                 /* 检查是否有保留的需要建立的MM连接         */
        }
        else if ((NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
            && ((RR_SYN_TCH == g_MmGlobalInfo.CsSecutityInfo.ucSecurityType)
                 ||(RR_SYN_TCH_MODIFY == g_MmGlobalInfo.CsSecutityInfo.ucSecurityType)))
        {
            if (g_RrMmSyncInd.ulRabCnt > 0)
            {
                Mm_SndCcSyncInd();                                                      /* 向CC指示专有信道已经分配或改变           */
            }
        }
        else
        {
        }
    }

    NAS_MM_UpdateCsServiceConnStatusFlg();

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S10_E34
  FUNCTION : 在MM CONNECTION ACTIVE状态下
             收到RRMM_SECURITY_IND的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      03-12-11  新版作成
*******************************************************************************/
VOS_VOID Mm_Cell_S10_E34(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    if ( MM_FALSE == Mm_RcvRrcSecurityInd(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
        NAS_LOG(WUEPS_PID_MM, MM_ORIGIN, PS_LOG_LEVEL_WARNING,
                "Mm_Cell_S10_E34: WARNING: Receive RR Security false.");

        return;
    }

    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {
        if ((MM_CONNECTION_ACTIVE == g_MmGlobalInfo.ucState) || (WAIT_FOR_NETWORK_COMMAND == g_MmGlobalInfo.ucState))
        {
            if (g_RrMmSyncInd.ulRabCnt > 0)
            {
                Mm_SndCcSyncInd();                                                      /* 向CC指示专有信道已经分配或改变           */
            }
        }
    }
    return;
}

VOS_VOID Mm_Cell_S14_E34(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    VOS_UINT8   i = 0;                                                          /* 循环计数变量                             */

    if ( MM_FALSE == Mm_RcvRrcSecurityInd(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        if (RRC_SECURITY_CS_SMC_CMPL ==
                    g_MmGlobalInfo.CsSecutityInfo.ucSecurityType)
        {                                                                       /* 完整性保护和安全模式启动                 */
            Mm_TimerStop( MM_TIMER_T3230 );                                     /* 停TIMER3230                              */
            for ( i = 0; i < MM_CONST_NUM_7; i++ )
            {                                                                   /* 重建的MM连接                             */
                /*lint -e701*/
                if ( MM_CONST_NUM_0 !=
                ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                aucMMConnExtFlg[0] & ( 0x01 << i ) ) )
                {                                                               /* 该TI的MM连接重建成功                     */
                    Mm_SndCcReestCnf( i, MMCC_REEST_SUCCESS );                  /* 通知CC,MM连接重建成功                    */
                }
                if ( MM_CONST_NUM_0 !=
                ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                aucMMConnExtFlg[1] & ( 0x01 << i ) ) )
                {                                                               /* 该TI的MM连接重建成功                     */
                    Mm_SndCcReestCnf( ( i + 8 ), MMCC_REEST_SUCCESS );          /* 通知CC,MM连接重建成功                    */
                }
                /*lint +e701*/
            }
            g_MmGlobalInfo.ucPreState  = g_MmGlobalInfo.ucState;                /* 记录迁移之前的状态                       */
            Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S14_E34:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
            Mm_ComCheckDelayMmConn( MM_FALSE );                                 /* 检查是否有保留的需要建立的MM连接         */

#if (FEATURE_ON == FEATURE_ECALL)
            /* 处理eCall定时器启动标识 */
            NAS_MM_RecordEcallTimerStartNeededFlag();
#endif
        }
    }

    return;
}


VOS_VOID Mm_Cell_S9_E35(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{
    if ( MM_FALSE == Mm_RcvRrcSyncInd(pRcvMsg) )
    {
        return;
    }

    Mm_SndCcSyncInd();                                                      /* 向CC指示专有信道已经分配或改变           */
    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S9_E36
  FUNCTION : 在WAIT FOR OUTGOING MM CONNECTION状态下
             收到RRMM_DATA_IND(AUTHENTICATION REQUEST)的处理
  INPUT    : VOS_VOID
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      03-12-11  新版作成
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E36(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    NAS_EventReport(WUEPS_PID_MM, NAS_OM_EVENT_AUTH_REQ,
                    VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    if ( MM_LIMITED_SERVICE != g_MmGlobalInfo.ucMmServiceState )
    {
        Mm_TimerStop( MM_TIMER_T3212 );                                         /* 停T3212                                  */
    }
    Mm_ComAuthenRcvAuthenReq();                                                 /* 收到AUTHEN REQ的处理                     */

    return;
}

VOS_VOID Mm_Cell_S9_E37(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    VOS_UINT8       ucCause;

    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;

    Mm_TimerStop( MM_TIMER_T3212 );                                         /* 停T3212                                  */

    /* 24008_CR1942R3_(Rel-11)_C1-114725 24008 4.3.2.5章节描述如下:
    If the AUTHENTICATION REJECT message is received in any other state the mobile station shall
    abort any MM specific, MM connection establishment or call re-establishment procedure,
    stop any of the timers T3210, or T3230, T3214 or T3216 (if they were running),
    release all MM connections (if any), start timer T3240 and enter the state WAIT FOR NETWORK COMMAND,
    expecting the release of the RR connection. */
    Mm_TimerStop(MM_TIMER_T3214);
    Mm_TimerStop(MM_TIMER_T3216);

    NAS_EventReport(WUEPS_PID_MM, NAS_OM_EVENT_AUTH_REJECT,
                    VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    if (LOCATION_UPDATING_INITIATED == g_MmGlobalInfo.ucState)
    {
        ucCause = NAS_OM_MM_CAUSE_AUT_NETWORK_REJECT;
        NAS_EventReport(WUEPS_PID_MM, NAS_OM_EVENT_LOCATION_UPDATE_FAILURE,
                        &ucCause, NAS_OM_EVENT_LAU_FAIL_LEN);    }

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

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S9_E38
  FUNCTION : 在WAIT FOR OUTGOING MM CONNECTION状态下
             收到RRMM_DATA_IND(IDENTITY REQUEST)的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      03-12-11  新版作成
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E38(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    if ( MM_LIMITED_SERVICE != g_MmGlobalInfo.ucMmServiceState )
    {
        Mm_TimerStop( MM_TIMER_T3212 );                                         /* 停T3212                                  */
    }

    Mm_ComIdentity();                                                           /* IDENTITY过程的处理                       */

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S9_E39
  FUNCTION : 在WAIT FOR OUTGOING MM CONNECTION状态下
             收到RRMM_DATA_IND(TMSI REALLOCATION COMMAND)的处理
  INPUT    : VOS_VOID
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      03-12-11  新版作成
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E39(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    if ( MM_LIMITED_SERVICE != g_MmGlobalInfo.ucMmServiceState )
    {
        Mm_TimerStop( MM_TIMER_T3212 );                                         /* 停T3212                                  */
    }

    Mm_ComTmsiReloc();                                                          /* TMSI RELOC过程                           */

    return;
}

VOS_VOID Mm_Cell_S9_E40(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    if ( MM_LIMITED_SERVICE != g_MmGlobalInfo.ucMmServiceState )
    {
        Mm_TimerStop( MM_TIMER_T3212 );                                         /* 停T3212                                  */
    }

    Mm_TimerStop( MM_TIMER_T3230 );                                             /* 停TIMER3230                              */
    switch ( g_MmGlobalInfo.ucMMConnEstingPD )
    {                                                                           /* 确定是哪个PD建立的MM连接                 */
    case MM_IE_PD_CALL_CONTROL:                                                 /* CC要求建立的MM连接                       */
        /*lint -e701*/
        if ( MM_CONST_NUM_7 > g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            ucMMConnEstingTI )
        {                                                                       /*TI小于7                                   */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0] =
                        (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                        aucMMConnExtFlg[0] |
                (VOS_UINT8)( 0x01 << g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                ucMMConnEstingTI ) );                                           /* 设置MM连接存在标志                       */
        }
        else
        {                                                                       /*TI大于7                                   */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] =
                (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
                 | (VOS_UINT8)( 0x01 << ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                ucMMConnEstingTI - 8 ) ) );                                     /* 设置MM连接存在标志                       */
        }
        /*lint +e701*/
        Mm_SndCcEstCnf( (VOS_UINT32)(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            ucMMConnEstingTI), MMCC_EST_SUCCESS );                               /* 该MM连接建立成功                         */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI
            = NO_MM_CONN_ESTING;                                                /* 清除正在建立的MM连接的标志               */

#if (FEATURE_ON == FEATURE_ECALL)
        /* 处理eCall定时器启动标识 */
        NAS_MM_RecordEcallTimerStartNeededFlag();
#endif
        break;
    case MM_IE_PD_SMS_MSG:                                                      /* SMS要求建立的MM连接                      */
        if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())              /* 在GSM网络中短消息主叫需要建立SAPI3       */
        {
            if (MM_MO_PAGING == g_MmGlobalInfo.ucPagingType)                    /* 主叫 */
            {
                if (MM_FALSE == MM_SndSapi3EstReq())
                {
                    Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI,
                                        NAS_MMCM_REL_CAUSE_MM_INTER_ERR_SND_SAPI3_FAIL);

                    Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
                    NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_ERROR,
                                        "Mm_Cell_S9_E40: ERROR: snd SAPI3 est fail.");

                    g_MmGlobalInfo.ucMMConnEstingPD         = NO_MM_CONN_ESTING; /* 设置没有正在建立的连接           */

                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI
                                        = NO_MM_CONN_ESTING;

                    g_MmGlobalInfo.ucPagingType             = MM_NO_PAGING;

                    return;
                }

                Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);

                g_MmGlobalInfo.ucPagingType = MM_NO_PAGING;

                return;
            }
        }
        /*lint -e701*/
        if ( MM_CONST_NUM_7 > g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
            ucMMConnEstingTI )
        {                                                                       /*TI小于7                                   */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0] |=
                (VOS_UINT8)( 0x01 << g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                ucMMConnEstingTI ) ;                                            /* 设置MM连接存在标志                       */
        }
        else
        {                                                                       /*TI大于7                                   */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1] |=
                (VOS_UINT8)( 0x01 << ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                ucMMConnEstingTI - 8 ) );                                       /* 设置MM连接存在标志                       */
        }
        /*lint +e701*/
        Mm_SndSmsEstCnf( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
            ucMMConnEstingTI);                                                  /* 该MM连接建立成功                         */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI
            = NO_MM_CONN_ESTING;                                                /* 清除正在建立的MM连接的标志               */
        break;
    case MM_IE_PD_NON_CALL_RLT_SS_MSG:                                          /* SS要求建立的MM连接                       */
        /*lint -e701*/
        if ( MM_CONST_NUM_7 > g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
            ucMMConnEstingTI )
        {                                                                       /*TI小于7                                   */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0] |=
                (VOS_UINT8)( 0x01 << g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                ucMMConnEstingTI );                                             /* 设置MM连接存在标志                       */
        }
        else
        {                                                                       /*TI大于7                                   */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1] |=
                (VOS_UINT8)( 0x01 << ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                ucMMConnEstingTI - 8 ) );                                       /* 设置MM连接存在标志                       */
        }
        /*lint +e701*/
        Mm_SndSsEstCnf( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
            ucMMConnEstingTI, MMSS_EST_SUCCESS );                               /* 该MM连接建立成功                         */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI
            = NO_MM_CONN_ESTING;                                                /* 清除正在建立的MM连接的标志               */
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S9_E40:WARNING: g_MmGlobalInfo.ucMMConnEstingPD Abnormal");
        break;
    }
    g_MmGlobalInfo.ucMMConnEstingPD = NO_MM_CONN_ESTING;                        /* 设置没有正在建立的连接                   */
    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                       /* 记录迁移之前的状态                       */
    Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E40:NORMAL: STATUS is  MM_CONNECTION_ACTIVE");
    Mm_ComCheckDelayMmConn( MM_FALSE );                                         /* 检查是否有保留的需要建立的MM连接         */

    NAS_MM_UpdateCsServiceConnStatusFlg();

    return;
}


VOS_VOID NAS_MM_ProcCmServiceRej_CcExist( VOS_VOID )
{
    switch(g_MmMsgCmSvcRjct.MmIeRejCause.ucRejCause)
    {
        /* 原因值4时，缓存CM层业务，等待Lu完成后重新发起CM业务 */
        case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_VLR:

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg
                = MM_TRUE;

            break;

        /* 原因值22时，通知CC业务失败，区分是否携带T3246，携带T3246时不需要重拨 */
        case NAS_MML_REG_FAIL_CAUSE_PROCEDURE_CONGESTION:

            if (VOS_TRUE == g_MmMsgCmSvcRjct.ucIsCmSrvRejCongestionWithT3246)
            {
                Mm_SndCcRelInd( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI,
                    NAS_MMCM_REL_CAUSE_CM_SRV_REJ_CONGESTION_WITH_T3246);           /* 通知CC,MM连接建立失败:NAS_MMCM_REL_CAUSE_CM_SRV_REJ_CONGESTION_WITH_T3246 */

            }
            else
            {
                Mm_SndCcRelInd( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI,
                    NAS_MMCM_REL_CAUSE_CM_SRV_REJ_CONGESTION);                      /* 通知CC,MM连接建立失败:NAS_MMCM_REL_CAUSE_CM_SRV_REJ_CONGESTION */
            }


            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI
                = NO_MM_CONN_ESTING;                                                /* 清除正在建立MM连接的标志 */

            break;

        /* 其他原因值 */
        default:

            Mm_SndCcRelInd( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI,
                (g_MmMsgCmSvcRjct.MmIeRejCause.ucRejCause + NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN));                /* 通知CC,MM连接建立失败                    */

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI
                = NO_MM_CONN_ESTING;                                                /* 清除正在建立MM连接的标志 */

            break;
    }

    return;
}


VOS_VOID NAS_MM_ProcCmServiceRej_SsExist( VOS_VOID )
{
    switch(g_MmMsgCmSvcRjct.MmIeRejCause.ucRejCause)
    {
        /* 原因值4时，缓存CM层业务，等待Lu完成后重新发起CM业务 */
        case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_VLR:

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg
                = MM_TRUE;

            break;

        /* 原因值22时，通知CC业务失败，区分是否携带T3246，携带T3246时不需要重拨 */
        case NAS_MML_REG_FAIL_CAUSE_PROCEDURE_CONGESTION:

            if (VOS_TRUE == g_MmMsgCmSvcRjct.ucIsCmSrvRejCongestionWithT3246)
            {
                Mm_SndSsRelInd( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                    ucMMConnEstingTI,
                    NAS_MMCM_REL_CAUSE_CM_SRV_REJ_CONGESTION_WITH_T3246);           /* 通知CC,MM连接建立失败:NAS_MMCM_REL_CAUSE_CM_SRV_REJ_CONGESTION_WITH_T3246 */

            }
            else
            {
                Mm_SndSsRelInd( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                    ucMMConnEstingTI,
                    NAS_MMCM_REL_CAUSE_CM_SRV_REJ_CONGESTION);                      /* 通知CC,MM连接建立失败:NAS_MMCM_REL_CAUSE_CM_SRV_REJ_CONGESTION */
            }


            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI
                = NO_MM_CONN_ESTING;                                                /* 清除正在建立MM连接的标志 */

            break;

         /* 其他原因值 */
         default:

            Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI,
                           (g_MmMsgCmSvcRjct.MmIeRejCause.ucRejCause + NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN));

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI           /* 清除正在建立MM连接的标志 */
                = NO_MM_CONN_ESTING;

            break;
    }

    return;
}


VOS_VOID NAS_MM_ProcCmServiceRej_SmsExist( VOS_VOID )


{
    switch(g_MmMsgCmSvcRjct.MmIeRejCause.ucRejCause)
    {
        /* 原因值4时，缓存CM层业务，等待Lu完成后重新发起CM业务 */
        case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_VLR:

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg
                = MM_TRUE;

            break;

        /* 原因值22时，通知CC业务失败，区分是否携带T3246，携带T3246时不需要重拨 */
         case NAS_MML_REG_FAIL_CAUSE_PROCEDURE_CONGESTION:

             if (VOS_TRUE == g_MmMsgCmSvcRjct.ucIsCmSrvRejCongestionWithT3246)
             {
                 Mm_SndSmsRelInd( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI,
                     NAS_MMCM_REL_CAUSE_CM_SRV_REJ_CONGESTION_WITH_T3246);           /* 通知CC,MM连接建立失败:NAS_MMCM_REL_CAUSE_CM_SRV_REJ_CONGESTION_WITH_T3246 */

             }
             else
             {
                 Mm_SndSmsRelInd( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI,
                     NAS_MMCM_REL_CAUSE_CM_SRV_REJ_CONGESTION);                      /* 通知CC,MM连接建立失败:NAS_MMCM_REL_CAUSE_CM_SRV_REJ_CONGESTION */
             }


             g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI
                 = NO_MM_CONN_ESTING;                                                /* 清除正在建立MM连接的标志 */

             break;

        /* 其他原因值 */
         default:

             Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI,
                (g_MmMsgCmSvcRjct.MmIeRejCause.ucRejCause + NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN));

             g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI
                = NO_MM_CONN_ESTING;                                                /* 清除正在建立MM连接的标志 */

             break;
    }

    return;
}



VOS_VOID Mm_Cell_S9_E41(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampPlmnInfo;

    pstCampPlmnInfo = NAS_MML_GetCurrCampPlmnInfo();

    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
    if ( MM_LIMITED_SERVICE != g_MmGlobalInfo.ucMmServiceState )
    {
        Mm_TimerStop( MM_TIMER_T3212 );                                        /* 停T3212                                  */
    }
    Mm_TimerStop( MM_TIMER_T3230 );                                             /* 停MM_TIMER_T3230                         */

    switch ( g_MmGlobalInfo.ucMMConnEstingPD )
    {                                                                           /* 确定是哪个PD建立的MM连接                 */
    case MM_IE_PD_CALL_CONTROL:                                                 /* CC要求建立的MM连接                       */

        NAS_MM_ProcCmServiceRej_CcExist();

        break;

    case MM_IE_PD_NON_CALL_RLT_SS_MSG:                                          /* SS要求建立的MM连接                       */

        NAS_MM_ProcCmServiceRej_SsExist();

        break;

    case MM_IE_PD_SMS_MSG:                                                      /* SMS要求建立的MM连接                      */

        NAS_MM_ProcCmServiceRej_SmsExist();

        break;

    default:
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S9_E41:WARNING: g_MmGlobalInfo.ucMMConnEstingPD Abnormal");
        break;
    }

    Mm_SndMmcCmSvcRejInd( g_MmMsgCmSvcRjct.MmIeRejCause.ucRejCause );

    switch (g_MmMsgCmSvcRjct.MmIeRejCause.ucRejCause)
    {                                                                           /* 拒绝原因值                               */
    case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_VLR:                                      /* 拒绝原因值#4                             */
        Mm_ComRejectCause4();                                                   /* 拒绝原因值#4的公共处理                   */


        if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
         && (NAS_MML_NET_MODE_I == pstCampPlmnInfo->enNetworkMode))
        {
            NAS_MM_SndGmmCmSvcRejInd(NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_VLR );
        }
        break;
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:                                               /* 拒绝原因值#6                             */
        Mm_ComRejectCause6();                                                   /* 拒绝原因值#6的公共处理                   */


        if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
         && (NAS_MML_NET_MODE_I == pstCampPlmnInfo->enNetworkMode))
        {
            NAS_MM_SndGmmCmSvcRejInd(NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_VLR );
        }
        break;
    case NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE:
    case NAS_MML_REG_FAIL_CAUSE_PROCEDURE_CONGESTION:
    case NAS_MML_REG_FAIL_CAUSE_SERV_OPT_NOT_SUPPORT:
    case NAS_MML_REG_FAIL_CAUSE_REQ_SERV_OPT_NOT_SUBSCRIBE:
    case NAS_MML_REG_FAIL_CAUSE_SERV_OPT_OUT_OF_ORDER:
    case NAS_MML_REG_FAIL_CAUSE_SEMANTICALLY_INCORRECT_MSG:
    case NAS_MML_REG_FAIL_CAUSE_INVALID_MANDATORY_INF:
    case NAS_MML_REG_FAIL_CAUSE_MSG_NONEXIST_NOTIMPLEMENTE:
    case NAS_MML_REG_FAIL_CAUSE_IE_NONEXIST_NOTIMPLEMENTED:
    case NAS_MML_REG_FAIL_CAUSE_CONDITIONAL_IE_ERROR:
    case NAS_MML_REG_FAIL_CAUSE_PROTOCOL_ERROR:
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
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1] ) )
        {                                                                       /* 没有MM连接存在                           */
            g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                g_MmGlobalInfo.ucStaOfRcvXXEstReq;                              /* 记录要进入的状态                         */
            Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );    /* MM连接流程                               */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* 记录迁移之前的状态                       */
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E41:NORMAL: STATUS is  WAIT_FOR_NETWORK_COMMAND");
            Mm_TimerStart( MM_TIMER_T3240 );                                    /* 启动TIMER3240                            */
        }
        else
        {
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* 记录迁移之前的状态                       */
            Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E41:NORMAL: STATUS is  MM_CONNECTION_ACTIVE");
            Mm_ComCheckDelayMmConn( MM_FALSE );                                 /* 检查是否有保留的需要建立的MM连接         */
        }

        break;
    default:
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
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1] ) )
        {                                                                       /* 没有MM连接存在                           */
            g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                g_MmGlobalInfo.ucStaOfRcvXXEstReq;                              /* 记录要进入的状态                         */
            Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );    /* MM连接流程                               */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* 记录迁移之前的状态                       */
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E41:NORMAL: STATUS is  WAIT_FOR_NETWORK_COMMAND");
            Mm_TimerStart( MM_TIMER_T3240 );                                    /* 启动TIMER3240                            */
        }
        else
        {
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* 记录迁移之前的状态                       */
            Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E41:NORMAL: STATUS is  MM_CONNECTION_ACTIVE");
            Mm_ComCheckDelayMmConn( MM_FALSE );                                 /* 检查是否有保留的需要建立的MM连接         */
        }

        break;
    }
    g_MmGlobalInfo.ucMMConnEstingPD = NO_MM_CONN_ESTING;                        /* 设置没有正在建立的连接                   */

    NAS_MM_UpdateCsServiceConnStatusFlg();

    NAS_MM_UpdateCsServiceBufferStatusFlg();

    return;
}


VOS_VOID Mm_Cell_S14_E41(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    VOS_UINT8   i = 0;                                                          /* 循环计数变量                             */
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampPlmnInfo;

    pstCampPlmnInfo = NAS_MML_GetCurrCampPlmnInfo();

    Mm_TimerStop( MM_TIMER_T3230 );                                             /* 停MM_TIMER_T3230                         */

    for ( i = 0; i < MM_CONST_NUM_7; i++ )
    {                                                                           /* 重建的MM连接                             */
        /*lint -e701*/
        if ( MM_CONST_NUM_0 !=
        ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
            & ( 0x01 << i ) ) )
        {
            Mm_SndCcRelInd( i, (g_MmMsgCmSvcRjct.MmIeRejCause.ucRejCause + NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN));             /* 通知CC,MM连接建立失败                    */
        }
        if ( MM_CONST_NUM_0 !=
        ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
            & ( 0x01 << i ) ) )
        {
            Mm_SndCcRelInd( ( i + 8 ), (g_MmMsgCmSvcRjct.MmIeRejCause.ucRejCause + NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN));                            /* 通知CC,MM连接建立失败                    */
        }
        /*lint +e701*/
    }

    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
        = MM_CONST_NUM_0;                                                       /* 清除存在的MM连接标志                     */
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
        = MM_CONST_NUM_0;                                                       /* 清除存在的MM连接标志                     */

    Mm_SndMmcCmSvcRejInd(g_MmMsgCmSvcRjct.MmIeRejCause.ucRejCause);

    switch (g_MmMsgCmSvcRjct.MmIeRejCause.ucRejCause)
    {                                                                           /* 拒绝原因值                               */
    case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_VLR:                                      /* 拒绝原因值#4                             */
        Mm_ComRejectCause4();                                                   /* 拒绝原因值#4的公共处理                   */


        if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
         && (NAS_MML_NET_MODE_I == pstCampPlmnInfo->enNetworkMode))
        {
            NAS_MM_SndGmmCmSvcRejInd(NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_VLR );
        }
        break;
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:                                               /* 拒绝原因值#6                             */
        Mm_ComRejectCause6();                                                   /* 拒绝原因值#6的公共处理                   */


        if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
         && (NAS_MML_NET_MODE_I == pstCampPlmnInfo->enNetworkMode))
        {
            NAS_MM_SndGmmCmSvcRejInd(NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_VLR );
        }
        break;
    case NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE:
    case NAS_MML_REG_FAIL_CAUSE_PROCEDURE_CONGESTION:
    case NAS_MML_REG_FAIL_CAUSE_SERV_OPT_NOT_SUPPORT:
    case NAS_MML_REG_FAIL_CAUSE_REQ_SERV_OPT_NOT_SUBSCRIBE:
    case NAS_MML_REG_FAIL_CAUSE_SERV_OPT_OUT_OF_ORDER:
    case NAS_MML_REG_FAIL_CAUSE_SEMANTICALLY_INCORRECT_MSG:
    case NAS_MML_REG_FAIL_CAUSE_INVALID_MANDATORY_INF:
    case NAS_MML_REG_FAIL_CAUSE_MSG_NONEXIST_NOTIMPLEMENTE:
    case NAS_MML_REG_FAIL_CAUSE_IE_NONEXIST_NOTIMPLEMENTED:
    case NAS_MML_REG_FAIL_CAUSE_CONDITIONAL_IE_ERROR:
    case NAS_MML_REG_FAIL_CAUSE_PROTOCOL_ERROR:
        g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
            g_MmGlobalInfo.ucStaOfRcvXXEstReq;                                  /* 记录要进入的状态                         */
        Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );        /* MM连接流程                               */
        g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                   /* 记录迁移之前的状态                       */
        Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S14_E41:NORMAL: STATUS is  WAIT_FOR_NETWORK_COMMAND");
        Mm_TimerStart( MM_TIMER_T3240 );                                        /* 启动TIMER3240                            */
        break;
    default:
        break;
    }

    NAS_MM_UpdateCsServiceConnStatusFlg();

    return;
}

VOS_VOID Mm_Cell_S9_E42(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;

    if ( MM_LIMITED_SERVICE != g_MmGlobalInfo.ucMmServiceState )
    {
        Mm_TimerStop( MM_TIMER_T3212 );                                         /* 停T3212                                  */
    }
    Mm_TimerStop( MM_TIMER_T3230 );                                             /* 停T3212                                  */

    switch (g_MmMsgAbort.MmIeRejCause.ucRejCause )
    {                                                                           /* 拒绝原因值                               */
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:                                               /* 拒绝原因值#6                             */
        Mm_ComAbortCause6();                                                    /* 拒绝原因值#6的公共处理                   */
        /* 通知MMC */
        NAS_MM_SndMmcAbortInd(NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME);
        break;
    case NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE:                                          /* 拒绝原因值#17                            */

#if (FEATURE_ON == FEATURE_PTM)
        /* MT的场景， 该标记为TRUE时为MT */
        if (VOS_TRUE == NAS_MML_GetCsServiceConnStatusFlg())
        {
            /* 收到CS PAGING后连接建立成功，但还未收到业务消息，收到网络ABORT的异常记录 */
            NAS_MM_CsPagingFailRecord(NAS_ERR_LOG_CS_PAGING_CAUSE_CONN_ABORT);
        }
#endif

        Mm_ComAbortCause17();                                                   /* 拒绝原因值#17的公共处理                  */
        /* 通知MMC */
        NAS_MM_SndMmcAbortInd(NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE);
        break;
    default:
        break;
    }

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S9_E43
  FUNCTION : 在WAIT FOR OUTGOING MM CONNECTION状态下
             收到RRMM_DATA_IND(MM INFORMATION)的处理
  INPUT    : VOS_VOID
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      03-12-11    新版作成
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E43(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    if ( MM_LIMITED_SERVICE != g_MmGlobalInfo.ucMmServiceState )
    {
        Mm_TimerStop( MM_TIMER_T3212 );                                         /* 停T3212                                  */
    }

    Mm_ComInfo();                                                               /* MM INFO过程的处理                        */

    return;
}


VOS_VOID Mm_Cell_S9_E50(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    VOS_UINT8           ucTI = 0;                                               /* CC消息中的TI                             */
    RRMM_DATA_IND_STRU *pRrDataInd = ( RRMM_DATA_IND_STRU *) pRcvMsg;           /* 消息RRMM_DATA_IND的结构体指针            */
    VOS_UINT8          *pucCMMsg = VOS_NULL_PTR;                                /* 指针类型转换                             */
    VOS_UINT8          *pucBakCMMsg = VOS_NULL_PTR;

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

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_Cell_S9_E50:ERROR: MALLOC ERROR!");
        return;                                                                 /* 返回                                     */
    }
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
        /*lint -e701*/
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

            /* 目前有两种状态会调用该函数
                WAIT_FOR_OUTGOING_MM_CONNECTION
                WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION
                统一状态变迁到 WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION */
            if ( g_MmGlobalInfo.ucState == WAIT_FOR_OUTGOING_MM_CONNECTION )
            {
                g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                          /* 记录迁移之前的状态                       */
                Mm_ComSetMmState(WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E50:NORMAL: STATUS is  WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION");
            }


        }
        /*lint +e701*/
    }
    else if ( ( MM_CONST_NUM_7 < ucTI ) && ( MM_CONST_NUM_15 > ucTI ) )
    {                                                                           /* CC建立的MM连接                           */
        /*lint -e701*/
        if ( MM_CONST_NUM_0 != (
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
            & ( 0x01 << ( ucTI - 8 ) ) ) )
        {                                                                       /* 该连接存在                               */
            Mm_SndCcDataInd ( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize,
                pucCMMsg );                                                     /* 向CC发送MMCC_DATA_IND                    */
        }
        /*lint +e701*/

    }
    else
    {

    }
    MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucBakCMMsg );                                /* 释放申请的消息                           */

    NAS_MM_UpdateCsServiceConnStatusFlg();

    return;
}
/*******************************************************************************
  Module:   Mm_Cell_S0_E1
  Function: MM_NULL 状态,收到 MMCMM_START_REQ 原语的处理
  Input:    VOS_VOID     *pMsg,  当前处理的消息
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇   2003.12.09   新版作成
*******************************************************************************/
VOS_VOID Mm_Cell_S0_E1(
                    VOS_VOID     *pMsg                                          /* 当前处理的消息                           */
                    )
{
    if (MM_TRUE == Mm_RcvMmcStartReq(pMsg))
    {
        Mm_ComStart();                                                          /* 调用收到MMCMM_START_REQ的公共处理        */
    }
    else
    {
        /* WUEPS_ASSERT(0); */
    }
    return;                                                                     /* 返回                                     */
}

VOS_VOID Mm_Cell_S1_E1(
                    VOS_VOID     *pMsg                                          /* 当前处理的消息                           */
                    )
{
    if (MM_TRUE == Mm_RcvMmcStartReq(pMsg))
    {
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* 设置ucPreState                           */
        Mm_ComSetMmState(MM_STATE_NULL);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S1_E1:NORMAL: STATUS is MM_STATE_NULL");

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

VOS_VOID Mm_Cell_S1_E3(
                    VOS_VOID     *pMsg                                          /* 当前处理的消息                           */
                    )
{
    NAS_MML_SetCsSigConnStatusFlg(VOS_FALSE);

    if (MM_TRUE == Mm_RcvMmcPlmnSrchIni(pMsg))
    {
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* 设置ucPreState                           */

        /* 保存出服务区前的状态,在搜网成功后用于判断LAI是否改变 */
        if ((MM_IDLE_NO_CELL_AVAILABLE != g_MmGlobalInfo.ucState)
         && (MM_IDLE_PLMN_SEARCH       != g_MmGlobalInfo.ucState))
        {
            g_MmGlobalInfo.ucNotCampONPreState = g_MmGlobalInfo.ucState;
        }

        Mm_ComSetMmState(MM_IDLE_PLMN_SEARCH);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S1_E3:NORMAL: STATUS is MM_IDLE_PLMN_SEARCH");
    }
    else
    {
        /* WUEPS_ASSERT(0); */
    }
    return;                                                                     /* 返回                                     */
}


VOS_VOID Mm_Cell_S3_E6(
                    VOS_VOID     *pMsg                                              /* 当前处理的消息                           */
                    )
{
    if (MM_TRUE == Mm_RcvGmmCombinedAttachIni(pMsg))
    {

        NAS_MML_SetDelayedCsfbLauFlg(VOS_FALSE);



        if (VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
        {
            return;
        }

        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* 设置ucPreState                           */
        Mm_ComSetMmState(LOCATION_UPDATING_PENDING);

        g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_FALSE;


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E6:NORMAL: STATUS is LOCATION_UPDATING_PENDING");
    }
    else
    {
        /* WUEPS_ASSERT(0); */
    }
    return;                                                                     /* 返回                                     */
}


VOS_VOID Mm_Cell_S9_E1(
                    VOS_VOID     *pMsg                                              /* 当前处理的消息                           */
                    )
{
    if (MM_TRUE == Mm_RcvMmcStartReq(pMsg))
    {
        Mm_TimerStop(MM_TIMER_T3230);                                           /* 停timer 3230                             */

        Mm_SndRrRelReq(RRC_CELL_UNBARRED);

        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* 设置ucPreState                           */
        Mm_ComSetMmState(MM_STATE_NULL);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E1:NORMAL: STATUS is MM_STATE_NULL");

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

/* MMCMM_PLMN_USER_SEL_REQ不再使用，删除Mm_Cell_S9_E4 */



VOS_VOID Mm_Cell_S10_E1(
                    VOS_VOID     *pMsg                                              /* 当前处理的消息                           */
                    )
{
    if (MM_TRUE == Mm_RcvMmcStartReq(pMsg))
    {
        Mm_SndRrRelReq(RRC_CELL_UNBARRED);

        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* 设置ucPreState                           */
        Mm_ComSetMmState(MM_STATE_NULL);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S10_E1:NORMAL: STATUS is MM_STATE_NULL");

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

/* MMCMM_PLMN_USER_SEL_REQ不再使用，删除Mm_Cell_S10_E4 */


VOS_VOID Mm_Cell_S11_E1(
                    VOS_VOID     *pMsg                                          /* 当前处理的消息                           */
                    )
{
    if (MM_TRUE == Mm_RcvMmcStartReq(pMsg))
    {
        if (MM_TIMER_RUNNING == gstMmTimer[MM_TIMER_T3240].ucTimerStatus)
        {                                                                       /* 如果timer 3240正在运行,则停止            */
            Mm_TimerStop(MM_TIMER_T3240);                                       /* 停timer 3240                             */
        }
        Mm_SndRrRelReq(RRC_CELL_UNBARRED);

        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* 设置ucPreState                           */
        Mm_ComSetMmState(MM_STATE_NULL);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S11_E1:NORMAL: STATUS is MM_STATE_NULL");

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

/* MMCMM_PLMN_USER_SEL_REQ不再使用，删除Mm_Cell_S11_E4 */



VOS_VOID Mm_Cell_S12_E1(
                    VOS_VOID     *pMsg                                          /* 当前处理的消息                           */
                    )
{
    if (MM_TRUE == Mm_RcvMmcStartReq(pMsg))
    {
        Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);                              /* 启动保护TIMER                            */

        Mm_SndRrRelReq(RRC_CELL_UNBARRED);

        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* 设置ucPreState                           */
        Mm_ComSetMmState(MM_STATE_NULL);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E1:NORMAL: STATUS is  MM_STATE_NULL");

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

/* MMCMM_PLMN_USER_SEL_REQ不再使用，删除Mm_Cell_S12_E4 */


VOS_VOID Mm_Cell_S13_E1(
                    VOS_VOID     *pMsg                                          /* 当前处理的消息                           */
                    )
{
    if (MM_TRUE == Mm_RcvMmcStartReq(pMsg))
    {
        Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);                              /* 启动保护TIMER                            */
        Mm_SndRrRelReq(RRC_CELL_UNBARRED);

        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* 设置ucPreState                           */
        Mm_ComSetMmState(MM_STATE_NULL);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S13_E1:NORMAL: STATUS is MM_STATE_NULL");

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
/* MMCMM_PLMN_USER_SEL_REQ不再使用，删除Mm_Cell_S13_E4 */


VOS_VOID Mm_Cell_S14_E1(
                    VOS_VOID     *pMsg                                          /* 当前处理的消息                           */
                    )
{
    if (MM_TRUE == Mm_RcvMmcStartReq(pMsg))
    {
        Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);                              /* 启动保护TIMER                            */
        Mm_SndRrRelReq(RRC_CELL_UNBARRED);

        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* 设置ucPreState                           */
        Mm_ComSetMmState(MM_STATE_NULL);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S14_E1:NORMAL: STATUS is MM_STATE_NULL");

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

/* MMCMM_PLMN_USER_SEL_REQ不再使用，删除Mm_Cell_S14_E4 */


VOS_VOID Mm_Cell_S16_E1(
                    VOS_VOID     *pMsg                                          /* 当前处理的消息                           */
                    )
{
    if (MM_TRUE == Mm_RcvMmcStartReq(pMsg))
    {
        Mm_TimerStop(MM_TIMER_T3230);                                           /* 停timer 3230                             */

        Mm_SndRrRelReq(RRC_CELL_UNBARRED);



        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* 设置ucPreState                           */
        Mm_ComSetMmState(MM_STATE_NULL);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S16_E1:NORMAL: STATUS is MM_STATE_NULL");

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

/* MMCMM_PLMN_USER_SEL_REQ不再使用，删除Mm_Cell_S16_E4 */

/* MMCMM_PLMN_USER_SEL_REQ不再使用，删除Mm_Cell_S19_E4 */



VOS_UINT8 Mm_Get_UserSpecificSearchFlg_From_SysInfo(
                   VOS_VOID *pRcvMsg
                   )
{
    VOS_UINT8                           ucUserSpecificSearchFlg = 0;
    MMCMM_SYS_INFO_IND_STRU            *pSysInfoInd             = VOS_NULL_PTR;
    MMCMM_GSM_SYS_INFO_IND_ST          *pGsmSysInfoInd          = VOS_NULL_PTR;

    pSysInfoInd      = (MMCMM_SYS_INFO_IND_STRU *)pRcvMsg;
    pGsmSysInfoInd   = (MMCMM_GSM_SYS_INFO_IND_ST *)pRcvMsg;

    if (MM_IDLE_PLMN_SEARCH != g_MmGlobalInfo.ucState)
    {
        return VOS_FALSE;
    }

    if (MMCMM_SYS_INFO_IND == pSysInfoInd->MsgHeader.ulMsgName )
    {
        ucUserSpecificSearchFlg = pSysInfoInd->ucUserSpecificSearchFlg;
    }
    else
    {
        ucUserSpecificSearchFlg = pGsmSysInfoInd->ucUserSpecificSearchFlg;
    }

    return ucUserSpecificSearchFlg;
}



VOS_VOID Mm_Cell_S1_E5(
                   VOS_VOID *pRcvMsg
                   )
{
    VOS_UINT32                                  ulLaiChangeFlag;
    VOS_UINT8                                   ucUserSpecificSearchFlg = 0;
    VOS_UINT8                                   ucPsRestrictionFlg;
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8   enCsUpdateStatus;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                                              ulCsfbExistFlag;

    /* 取得CSFB是否存在的标志 */
    ulCsfbExistFlag         = NAS_MML_IsCsfbServiceStatusExist();
#endif

    ucPsRestrictionFlg      = NAS_MML_GetPsRestrictRegisterFlg();


    ulLaiChangeFlag =  NAS_MML_IsCsLaiChanged();

    if ((VOS_TRUE == ulLaiChangeFlag)
     || (MM_TRUE  == g_MmGlobalInfo.MsCsInfo.ucCellChgFlg))
    {
        Mm_TimerStop(MM_TIMER_T3211);
    }

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

    /* CS ONLY或PS ONLY,在NMO1下需要进行联合注册 */
    if ((VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNewNtMod))
     && (VOS_FALSE == ucPsRestrictionFlg)
#if  (FEATURE_ON == FEATURE_LTE)
     && (VOS_FALSE == ulCsfbExistFlag)
#endif
       )
    {
        g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;

        /* RAC为0的场合 */
        if ((MM_UNSUPPORT_GPRS == g_MmGlobalInfo.usRac)
         || (MMCMM_FORBIDDEN_PLMN_FOR_GPRS == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
        {
            NAS_MM_SetLikeBFlg();

            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S1_E5:INFO: mmLikeB is MM_TRUE");

            if (MMCMM_FORBIDDEN_PLMN_FOR_GPRS == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)
            {
                enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
                if ( ( VOS_FALSE == ulLaiChangeFlag ) &&
                     ( NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus ) )
                {
                    if ( MM_TRUE
                     == g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg )
                    {
                        g_MmGlobalInfo.LuInfo.ucLuType =
                            MM_IE_LUT_PERIODIC_UPDATING;                /* 设置LU类型                               */
                        Mm_ComLuOnly();                                 /* 发送LU REQ                               */
                    }
                    else
                    {
                        Mm_ComNasInfoSav(MM_STATUS_ATTACHED,
                                         NAS_MML_GetSimCsSecurityCksn());

                        g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;    /* 设置服务状态                             */

                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S1_E5:INFO: MmServiceState is MM_NORMAL_SERVICE");

                        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                    MM_MMC_LU_RESULT_SUCCESS,
                                                    NAS_MML_REG_FAIL_CAUSE_NULL);        /* 向MMC发送MMCMM_LU_RESULT_IND             */
                        NAS_MM_SndGmmLuResultInd(MMGMM_LU_SUCCESS,
                                                 NAS_MML_REG_FAIL_CAUSE_NULL);        /* 向MMC发送MMCMM_LU_RESULT_IND             */

                        Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);

                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S1_E5:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
                        NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                    }
                }
                else
                {
                    g_MmGlobalInfo.LuInfo.ucLuType =
                                    MM_IE_LUT_NORMAL_LU;                /* 设置LU类型                               */
                    Mm_ComLuOnly();                                     /* LU REQ                                   */
                }
            }
            else
            {
                if (VOS_TRUE == NAS_MML_IsCampLaiInfoChanged())
                {
                    g_MmGlobalInfo.LuInfo.ucLuType =
                                    MM_IE_LUT_NORMAL_LU;                /* 设置LU类型                               */
                    Mm_ComLuOnly();                                     /* LU REQ                                   */
                }
                else
                {
                    switch ( NAS_MML_GetCsUpdateStatus() )
                    {
                    case NAS_MML_LOCATION_UPDATE_STATUS_UPDATED:
                         NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                        g_MmGlobalInfo.ucMmServiceState =
                                            MM_NORMAL_SERVICE;
                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S1_E5:INFO: MmServiceState is MM_NORMAL_SERVICE");


                        Mm_SndRrNasInfoChgReq(MM_NAS_INFO_SYNC_AS_FLG);


                        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                    MM_MMC_LU_RESULT_SUCCESS,
                                                    NAS_MML_REG_FAIL_CAUSE_NULL);    /* 向MMC发送MMCMM_LU_RESULT_IND             */
                        NAS_MM_SndGmmLuResultInd(MMGMM_LU_SUCCESS,
                                                 NAS_MML_REG_FAIL_CAUSE_NULL);    /* 向MMC发送MMCMM_LU_RESULT_IND             */

                        g_MmGlobalInfo.ucPreState =
                                        g_MmGlobalInfo.ucState;         /* 记录前状态                               */

                        Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);

                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S1_E5:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
                        break;
                    case NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED:
                         NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                        g_MmGlobalInfo.ucMmServiceState =
                                        MM_ATTEMPTING_TO_UPDATE;
                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S1_E5:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");

                        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                    MM_MMC_LU_RESULT_FAILURE,
                                                    NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);    /* 向MMC发送MMCMM_LU_RESULT_IND             */
                        NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                                 NAS_MML_REG_FAIL_CAUSE_NULL);    /* 向MMC发送MMCMM_LU_RESULT_IND             */

                        g_MmGlobalInfo.ucPreState =
                                        g_MmGlobalInfo.ucState;         /* 记录前状态                               */
                        Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);

                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S1_E5:NORMAL: STATUS is MM_IDLE_ATTEMPTING_TO_UPDATE");
                        break;
                    default:
                        break;
                    }
                }
            }
        }
        else
        {
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;             /* 记录前状态                               */
            Mm_ComSetMmState(MM_WAIT_FOR_ATTACH);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S1_E5:NORMAL: STATUS is MM_WAIT_FOR_ATTACH");
        }
    }
    else
    {   /* A+II或者B模式                            */
        ucUserSpecificSearchFlg = Mm_Get_UserSpecificSearchFlg_From_SysInfo(pRcvMsg);
        Mm_ComRcvSysHandle(ucUserSpecificSearchFlg);                       /* 调用在系统信息的公共处理                 */
    }
}


VOS_VOID Mm_MakeCcEstReq(MMCC_EST_REQ_STRU *pMsg)
{
    pMsg->ulCallPri =
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulCallPri;
    pMsg->ulCallType =
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulCallType;
    pMsg->ulTransactionId =
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId;
    pMsg->ulCallMode =
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulCallMode;

}

VOS_VOID Mm_MakeSmsEstReq(MMSMS_EST_REQ_STRU *pMsg)
{
    pMsg->ulTi=
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId;
    pMsg->ulEstCause = g_MmSmsEstReq.ulEstCause;
}

VOS_VOID Mm_MakeSsEstReq(MMSS_EST_REQ_STRU *pMsg)
{
    pMsg->ulTi=
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId;
}


VOS_VOID Mm_MakeGPagingInd(GRRMM_PAGING_IND_ST *pMsg)
{
    pMsg->MsgHeader.ulMsgName           = GRRMM_PAGING_IND;
    pMsg->MsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pMsg->MsgHeader.ulSenderPid         = UEPS_PID_GAS;
    pMsg->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pMsg->MsgHeader.ulReceiverPid       = WUEPS_PID_MM;
    pMsg->MsgHeader.ulLength            = sizeof(GRRMM_PAGING_IND_ST) - VOS_MSG_HEAD_LENGTH;
    if (MM_TMSI_PAGING == g_MmGlobalInfo.ucPagingRecordTypeId)
    {
        pMsg->ucMSIDType                = GAS_TMSI;
    }
    else
    {
        pMsg->ucMSIDType                = GAS_IMSI;
    }
    pMsg->ucPagingType                  = 0;

    return;
}


VOS_VOID Mm_MakeWPagingInd(RRMM_PAGING_IND_STRU *pMsg)
{
    pMsg->MsgHeader.ulMsgName           = RRMM_PAGING_IND;
    pMsg->MsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pMsg->MsgHeader.ulSenderPid         = WUEPS_PID_WRR;
    pMsg->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pMsg->MsgHeader.ulReceiverPid       = WUEPS_PID_MM;
    pMsg->MsgHeader.ulLength            = sizeof(RRMM_PAGING_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pMsg->ulPagingCause                 = g_MmGlobalInfo.ucPagingCause;
    pMsg->ulCnDomainId                  = RRC_NAS_CS_DOMAIN;

    if (MM_TMSI_PAGING == g_MmGlobalInfo.ucPagingRecordTypeId)
    {
        pMsg->ulPagingUeId              = RRC_TMSI_GSM_MAP_P_TMSI;
    }
    else
    {
        pMsg->ulPagingUeId              = RRC_IMSI_GSM_MAP;
    }

    pMsg->ulPagingType                  = 0;
}


VOS_VOID Mm_DealWithBuffMsg(VOS_VOID)
{
    MMCC_EST_REQ_STRU                   CcEstReqMsg;
    MMSMS_EST_REQ_STRU                  SmsMsg;                                 /* 定义接收到的消息类型指针                 */
    MMSS_EST_REQ_STRU                   SsMsg;                                  /* 定义接收到的消息类型指针                 */
    RRMM_PAGING_IND_STRU                stWPagingMsg;
    GRRMM_PAGING_IND_ST                 stGPagingMsg;

    VOS_UINT32                          ulLaiChangeFlag;
    LAU_TYPE_ENUM_UINT8                 enLauType;
    VOS_UINT32                          ulEmergencyCallFlg;

    ulEmergencyCallFlg             = Mm_ComJudgeCsServExist();

    ulLaiChangeFlag = NAS_MML_IsCsLaiChanged();
    enLauType       = MM_IE_LUT_TYPE_BUTT;
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_DealWithBuffMsg: deal with buffer message! ");
    if ((MM_IDLE_NORMAL_SERVICE == g_MmGlobalInfo.ucState)
     || (MM_IDLE_ATTEMPTING_TO_UPDATE == g_MmGlobalInfo.ucState))
    {
        if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
        {
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_DealWithBuffMsg: start CC message preceed! ");
            Mm_MakeCcEstReq(&CcEstReqMsg);
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;
            /*lint -e961*/
            gaMmStateTable[23][g_MmGlobalInfo.ucState](&CcEstReqMsg);
            /*lint +e961*/
        }
        else if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg)
        {
            Mm_MakeSmsEstReq(&SmsMsg);
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg = MM_FALSE;
            /*lint -e961*/
            gaMmStateTable[61][g_MmGlobalInfo.ucState](&SmsMsg);
            /*lint +e961*/
        }
        else if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg)
        {
            Mm_MakeSsEstReq(&SsMsg);
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg = MM_FALSE;
            /*lint -e961*/
            gaMmStateTable[64][g_MmGlobalInfo.ucState](&SsMsg);
            /*lint +e961*/
        }
        else if (MM_PAGING_PLMNSRCH_TRUE == g_MmSubLyrShare.MmShare.ucPagingPlmnSrch)
        {
            g_MmSubLyrShare.MmShare.ucPagingPlmnSrch = MM_PAGING_PLMNSRCH_FALSE;
            if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
            {
                Mm_MakeGPagingInd(&stGPagingMsg);
                /*lint -e961*/
                gaMmStateTable[30][g_MmGlobalInfo.ucState](&stGPagingMsg);
                /*lint +e961*/
            }
            else
            {
                Mm_MakeWPagingInd(&stWPagingMsg);
                /*lint -e961*/
                gaMmStateTable[30][g_MmGlobalInfo.ucState](&stWPagingMsg);
                /*lint +e961*/
            }
        }
        else
        {
        }
    }
    else if((WAIT_FOR_RR_CONNECTION_LOCATION_UPDATING != g_MmGlobalInfo.ucState )
        && (MM_WAIT_FOR_ATTACH != g_MmGlobalInfo.ucState )
        && (WAIT_FOR_RR_CONNECTION_MM_CONNECTION != g_MmGlobalInfo.ucState)
        && (LOCATION_UPDATING_PENDING != g_MmGlobalInfo.ucState ))
    {
        if(MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
        {
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_DealWithBuffMsg: start EMC! ");
            Mm_MakeCcEstReq(&CcEstReqMsg);
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;
            Mm_Cell_S4_E24(&CcEstReqMsg);

        }
        else if(MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg)
        {
            Mm_MakeSmsEstReq(&SmsMsg);
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg = MM_FALSE;
            Mm_Cell_S4_E62(&SmsMsg);
        }
        else if(MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg)
        {
            Mm_MakeSsEstReq(&SsMsg);
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg = MM_FALSE;
            Mm_Cell_S4_E65(&SsMsg);
        }
        else
        {
        }
    }
    else if (MM_WAIT_FOR_ATTACH == g_MmGlobalInfo.ucState)
    {
        if (MM_PAGING_PLMNSRCH_TRUE == g_MmSubLyrShare.MmShare.ucPagingPlmnSrch)
        {/* 此时小区肯定没有发生变化 */
            g_MmSubLyrShare.MmShare.ucPagingPlmnSrch = MM_PAGING_PLMNSRCH_FALSE;
            if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
            {
                Mm_MakeGPagingInd(&stGPagingMsg);
                Mm_Cell_S3_E31(&stGPagingMsg);
            }
            else
            {
                Mm_MakeWPagingInd(&stWPagingMsg);
                Mm_Cell_S3_E31(&stWPagingMsg);
            }
        }
        if (MM_CS_SERV_EMERGENCY_CALL_EXIST == ulEmergencyCallFlg)
        {
            /* 发起LAU流程 有紧急呼先进行紧急呼*/
            enLauType = NAS_MM_GetLuType();

            NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, enLauType);
        }

    }
    else
    {
    }

    g_MmSubLyrShare.MmShare.ucPagingPlmnSrch = MM_PAGING_PLMNSRCH_FALSE;

    NAS_MM_UpdateCsServiceBufferStatusFlg();
}



VOS_VOID Mm_Cell_S2_E5(VOS_VOID *pRcvMsg)
{
    VOS_UINT32                                  ulLaiChangeFlag;
    VOS_UINT8                                   ucUserSpecificSearchFlg = 0;
    VOS_UINT8                                   ucPsRestrictionFlg;
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8   enCsUpdateStatus;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8             enCurrentRatType;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulCsfbExistFlag;

    /* 取得CSFB是否存在的标志 */
    ulCsfbExistFlag     = NAS_MML_IsCsfbServiceStatusExist();
#endif
    ucPsRestrictionFlg      = NAS_MML_GetPsRestrictRegisterFlg();

    ulLaiChangeFlag =  NAS_MML_IsCsLaiChanged();

    NAS_MM_NotifyAsInfoChgReq();


    enCurrentRatType = NAS_MML_GetCurrNetRatType();

    if (( MM_CKSN_INVALID != NAS_MML_GetSimCsSecurityCksn() )
     && (NAS_MML_NET_RAT_TYPE_GSM == enCurrentRatType))
    {
        Mm_SndRrNasInfoChgReq(MM_NAS_INFO_SK_FLG);
    }

    /* 如果当前LAI与之前驻留的LAI相比发生变化,需要清除atttemp conter值 */
    if (VOS_TRUE == NAS_MM_IsNeedClearAttemptCounter())
    {
        g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;
    }

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

    /* CS ONLY,PS ONLY下NMO1下GMM需要进行联合注册 */
    if ((VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNewNtMod))
     && (VOS_FALSE == ucPsRestrictionFlg)
#if  (FEATURE_ON == FEATURE_LTE)
     && (VOS_FALSE == ulCsfbExistFlag)
#endif
        )
    {
        g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;

        /* RAC为0的场合 */
        if ((MM_UNSUPPORT_GPRS == g_MmGlobalInfo.usRac)
         || (MMCMM_FORBIDDEN_PLMN_FOR_GPRS == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
        {
            NAS_MM_SetLikeBFlg();

            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S2_E5:INFO: LikeB is MM_TRUE");

            enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();

            if ( ( VOS_FALSE == ulLaiChangeFlag )
              && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus ) )
            {
                if ( MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg )
                {
                    if ( MM_TRUE ==
                            g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg )
                    {
                        NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, MM_IE_LUT_PERIODIC_UPDATING);
                    }
                    else
                    {
                        Mm_ComNasInfoSav(
                                 MM_STATUS_ATTACHED,
                                 NAS_MML_GetSimCsSecurityCksn()
                                 );
                        g_MmGlobalInfo.ucMmServiceState =
                            MM_NORMAL_SERVICE;                          /* 设置服务状态                             */
                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S2_E5:INFO: MmServiceState is MM_NORMAL_SERVICE");

                        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                    MM_MMC_LU_RESULT_SUCCESS,
                                                    NAS_MML_REG_FAIL_CAUSE_NULL);        /* 向MMC发送MMCMM_LU_RESULT_IND             */
                        NAS_MM_SndGmmLuResultInd(MMGMM_LU_SUCCESS,
                                                 NAS_MML_REG_FAIL_CAUSE_NULL);        /* 向MMC发送MMCMM_LU_RESULT_IND             */

                        Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);

                        if ( MM_TRUE == g_MmGlobalInfo.ucPowerOnFlg )
                        {
                            g_MmGlobalInfo.ucPowerOnFlg = MM_FALSE;
                        }

                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S2_E5:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
                        NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                    }
                }
                else
                {
                    if ( MM_TRUE == g_MmGlobalInfo.ucPowerOnFlg )
                    {
                        NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, MM_IE_LUT_IMSI_ATTACH);

                    }
                    else if ( MM_TRUE ==
                            g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg )
                    {
                        NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, MM_IE_LUT_PERIODIC_UPDATING);
                    }
                    else
                    {
                        Mm_ComNasInfoSav(
                                 MM_STATUS_ATTACHED,
                                 NAS_MML_GetSimCsSecurityCksn()
                                 );

                        g_MmGlobalInfo.ucMmServiceState =
                            MM_NORMAL_SERVICE;                          /* 设置服务状态                             */
                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S2_E5:INFO: MmServiceState is MM_NORMAL_SERVICE");


                        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                    MM_MMC_LU_RESULT_SUCCESS,
                                                    NAS_MML_REG_FAIL_CAUSE_NULL);        /* 向MMC发送MMCMM_LU_RESULT_IND             */
                        NAS_MM_SndGmmLuResultInd(MMGMM_LU_SUCCESS,
                                                 NAS_MML_REG_FAIL_CAUSE_NULL);        /* 向MMC发送MMCMM_LU_RESULT_IND             */

                        Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S2_E5:NORMAL: STATUS is  MM_IDLE_NORMAL_SERVICE");
                        NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                    }
                }
            }
            else
            {
                NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, MM_IE_LUT_NORMAL_LU);
            }
        }
        else
        {
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;             /* 记录前状态                               */
            Mm_ComSetMmState(MM_WAIT_FOR_ATTACH);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S2_E5:NORMAL: STATUS is MM_WAIT_FOR_ATTACH");
        }
    }
    else
    {
        /* A+II或者B模式                            */
        ucUserSpecificSearchFlg = Mm_Get_UserSpecificSearchFlg_From_SysInfo(pRcvMsg);
        Mm_ComRcvSysHandle(ucUserSpecificSearchFlg);                                               /* 调用在系统信息的公共处理                 */
    }

    Mm_DealWithBuffMsg();
}



VOS_VOID Mm_Cell_S2_E21(VOS_VOID *pMsg)
{
    if ( MM_FALSE == Mm_RcvMmcCoverageLostInd(pMsg) )
    {
        return;
    }

    if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
    {
        /* 如果是EMC，继续等待上层的终止, 如果当前no rf直接给cc回复失败 */
        if ((VOS_FALSE == NAS_MML_GetRfAvailFlg())
         || (MMCC_EMERGENCY_CALL != g_MmCcEstReq.ulCallType))

        {
            Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_OUT_OF_COVERAGE);

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;
        }
    }

    if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg)
    {
        Mm_SndSmsRelInd( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_OUT_OF_COVERAGE);                        /* 通知SMS建立失败                          */
    }

    if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg)
    {
        Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                       NAS_MMCM_REL_CAUSE_MM_INTER_ERR_OUT_OF_COVERAGE);
    }

    if (TEST_CONTROL_ACTIVE == g_MmGlobalInfo.ucState)
    {
        Mm_TimerResume(MM_TIMER_STOP_ALL);

        /* TC状态收到COVERAGE LOST消息时，通知TC连接释放 */
        NAS_MM_SndTcRrRelInd();
    }

    g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                         /* 记录前状态                               */
    g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;

    /* 保存出服务区前的状态,在搜网成功后用于判断LAI是否改变 */
    g_MmGlobalInfo.ucNotCampONPreState = g_MmGlobalInfo.ucState;

    Mm_ComSetMmState(MM_IDLE_NO_CELL_AVAILABLE);

#if (FEATURE_ON == FEATURE_ECALL)
    NAS_MM_ProcEcallTimerStartNeededFlg();
#endif

    g_MmSubLyrShare.MmShare.ucPagingPlmnSrch = MM_PAGING_PLMNSRCH_FALSE;

    if (MM_WAIT_CS_DETACH == (g_MmGlobalInfo.stDetachInfo.enDetachType
                     & MM_WAIT_CS_DETACH))
    {
        NAS_MM_SndMmcDetachCnf(MMC_MM_NO_SERVICE);

        NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);

        Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                         NAS_MML_GetSimCsSecurityCksn());             /* 设置MM信息                               */

        /* 清除等待标志 */
        g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
    }


    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S2_E21:NORMAL: STATUS is MM_IDLE_NO_CELL_AVAILABLE");
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S2_E21:INFO: MmServiceState is MM_NO_SERVICE");
}


VOS_VOID Mm_Cell_S14_E21(VOS_VOID *pMsg)
{
    if ( MM_FALSE == Mm_RcvMmcCoverageLostInd(pMsg) )
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S14_E21:WARNING: MMCMM_COVERAGE_LOST_IND is not correct.");
        return;
    }

    Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);                                  /* 启动保护TIMER                            */

    g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                         /* 记录前状态                               */
    g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;

    /* 保存出服务区前的状态,在搜网成功后用于判断LAI是否改变 */
    g_MmGlobalInfo.ucNotCampONPreState = g_MmGlobalInfo.ucState;

    if (WAIT_FOR_RR_CONNECTION_LOCATION_UPDATING == g_MmGlobalInfo.ucState)
    {
        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);
        
        NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                 NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL); 
    }

    Mm_ComSetMmState(MM_IDLE_NO_CELL_AVAILABLE);

#if (FEATURE_ON == FEATURE_ECALL)
    NAS_MM_ProcEcallTimerStartNeededFlg();
#endif

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S14_E21:NORMAL: STATUS is MM_IDLE_NO_CELL_AVAILABLE");

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S14_E21:INFO: MmServiceState is MM_NO_SERVICE");




    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_OUT_OF_COVERAGE);


    NAS_MML_SetCsSigConnStatusFlg(VOS_FALSE);

    Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);

    return;
}


VOS_VOID Mm_RcvRrmmRelInd()
{
    RRMM_REL_IND_STRU                   RrRelInd;

    /* 填写EST CNF消息内容 */
    RrRelInd.MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    RrRelInd.MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    RrRelInd.MsgHeader.ulReceiverPid    = WUEPS_PID_MM;

    RrRelInd.MsgHeader.ulMsgName        = RRMM_REL_IND;

    RrRelInd.ulCnDomainId               = RRC_NAS_CS_DOMAIN;
    RrRelInd.ulRrcConnStatus            = RRC_RRC_CONN_STATUS_ABSENT;
    RrRelInd.ulRelCause                 = RRC_REL_CAUSE_RR_NORM_EVENT;

    if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        RrRelInd.MsgHeader.ulSenderPid = WUEPS_PID_WRR;
    }
    else
    {
        RrRelInd.MsgHeader.ulSenderPid = UEPS_PID_GAS;
    }
    /*直接调用GMM处理消息RRMM_REL_IND的函数*/
    /*lint -e961*/
    gaMmStateTable[33 - 1][g_MmGlobalInfo.ucState](&RrRelInd);
    /*lint +e961*/
    return;
}
/*******************************************************************************
  Module:   Mm_RcvRrmmEstCnf
  Function:
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:

*******************************************************************************/
VOS_VOID Mm_RcvRrmmEstCnf()
{
    RRMM_EST_CNF_STRU                   RrEstCnf;

    /* 填写EST CNF消息内容 */
    RrEstCnf.MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    RrEstCnf.MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    RrEstCnf.MsgHeader.ulReceiverPid    = WUEPS_PID_MM;

    RrEstCnf.MsgHeader.ulMsgName        = RRMM_EST_CNF;

    RrEstCnf.ulOpId                     = g_MmGlobalInfo.ucRrEstReqOpid;
    RrEstCnf.ulCnDomainId               = RRC_NAS_CS_DOMAIN;
    RrEstCnf.ulResult                   = RRC_EST_EST_CONN_FAIL;

    if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        RrEstCnf.MsgHeader.ulSenderPid = WUEPS_PID_WRR;
    }
    else
    {
        RrEstCnf.MsgHeader.ulSenderPid = UEPS_PID_GAS;
    }
    /*lint -e961*/
    gaMmStateTable[31][g_MmGlobalInfo.ucState](&RrEstCnf);
    /*lint +e961*/

    return;
}

VOS_VOID Mm_Cell_S9_E21(VOS_VOID *pMsg)
{
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8               enCsUpdateStatus;
    MM_LAI_STRU                                            *pstAttLaiInfo   = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                                       *pstCampLaiInfo  = VOS_NULL_PTR;

    if (MM_FALSE == Mm_RcvMmcCoverageLostInd(pMsg))
    {
        return;
    }

    switch (g_MmGlobalInfo.ucState)
    {
        case WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION:
        case WAIT_FOR_OUTGOING_MM_CONNECTION:

            Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_OUT_OF_COVERAGE);
            break;
        case LOCATION_UPDATING_INITIATED:

            Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_OUT_OF_COVERAGE);

            enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
            if ((VOS_TRUE == NAS_MML_IsCsLaiChanged())
             || (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED != enCsUpdateStatus))
            {
                g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;
                g_MmGlobalInfo.usCauseVal = NAS_MML_REG_FAIL_CAUSE_RR_CONN_FAIL;
                NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);

                /* 在U2状态，保存当前的LAI信息 */
                pstAttLaiInfo   = NAS_MM_GetAttemptUpdateLaiInfo();
                pstCampLaiInfo  = NAS_MML_GetCurrCampLai();

                pstAttLaiInfo->PlmnId.ulMcc = pstCampLaiInfo->stPlmnId.ulMcc;
                pstAttLaiInfo->PlmnId.ulMnc = pstCampLaiInfo->stPlmnId.ulMnc;
                pstAttLaiInfo->ulLac        = ((pstCampLaiInfo->aucLac[0] << 8)| (pstCampLaiInfo->aucLac[1]));

                Mm_ComNasInfoSav(
                                MM_STATUS_DETACHED,
                                MM_CKSN_INVALID
                                );
                Mm_ComDelLai();
                g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &= ~MM_MS_ID_TMSI_PRESENT;

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

                Mm_TimerStart(MM_TIMER_T3211);
            }
            break;
        case LOCATION_UPDATE_REJECTED:
            Mm_TimerStop(MM_TIMER_T3240);
            Mm_TimerStop(MM_TIMER_T3218);                                       /* 停T3218                                  */
            Mm_ComDelRandRes();
            Mm_ComLuCauseHandle(g_MmGlobalInfo.usCauseVal);
            break;
        case WAIT_FOR_NETWORK_COMMAND:
            Mm_TimerStop(MM_TIMER_T3240);
            Mm_TimerStop(MM_TIMER_T3218);                                       /* 停T3218                                  */
            Mm_ComDelRandRes();
            break;
        case WAIT_FOR_REESTABLISH_WAIT_FOR_REEST_REQ:
            Mm_TimerStop(MM_TIMER_PROTECT_CC);
            break;
        default:
            break;
    }

    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
    Mm_TimerStop(MM_TIMER_PROTECT_AGENT);

    if ((VOS_TRUE == NAS_MM_IsDisableGprsCombineAttach())
     && (MM_NORMAL_SERVICE == g_MmGlobalInfo.ucMmServiceState))
    {
        NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
    }

    g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                         /* 记录前状态                               */
    g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;

    /* 保存出服务区前的状态,在搜网成功后用于判断LAI是否改变 */
    g_MmGlobalInfo.ucNotCampONPreState = g_MmGlobalInfo.ucState;

    Mm_ComSetMmState(MM_IDLE_NO_CELL_AVAILABLE);

#if (FEATURE_ON == FEATURE_ECALL)
    NAS_MM_ProcEcallTimerStartNeededFlg();
#endif

    NAS_MML_SetCsSigConnStatusFlg(VOS_FALSE);

    Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);

    Mm_ComProcCauseClear();

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E21:NORMAL: STATUS is MM_IDLE_NO_CELL_AVAILABLE");
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S9_E21:INFO: MmServiceState is MM_NO_SERVICE");

    return;
}


VOS_UINT8 NAS_MM_GetStaOfRcvXXEstReq_CSFB(VOS_VOID)
{
    VOS_UINT8                           ucState;
    VOS_UINT32                          ulLaiChangeFlag;

    ulLaiChangeFlag = NAS_MML_IsCsLaiChanged();

    switch (g_MmGlobalInfo.ucState)
    {
        case MM_IDLE_NO_CELL_AVAILABLE:
        case MM_IDLE_PLMN_SEARCH:
        case LOCATION_UPDATING_PENDING:
        case MM_IDLE_LOCATION_UPDATE_NEEDED:
        case MM_WAIT_FOR_ATTACH:
            if (VOS_FALSE == NAS_MML_GetSimCsRegStatus())
            {
                ucState = MM_IDLE_NO_IMSI;
            }
            else if ( ( MMCMM_NO_FORBIDDEN != g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg )
                   && ( MMCMM_FORBIDDEN_PLMN_FOR_GPRS != g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg ) )
            {
                ucState = MM_IDLE_LIMITED_SERVICE;
            }
            else if (VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg())
            {
                ucState = MM_IDLE_LOCATION_UPDATE_NEEDED;
            }
            else if ((NAS_MML_LOCATION_UPDATE_STATUS_UPDATED != NAS_MML_GetCsUpdateStatus())
                  || (VOS_TRUE == ulLaiChangeFlag))
            {
                ucState = MM_IDLE_ATTEMPTING_TO_UPDATE;
            }
            else
            {
                ucState = MM_IDLE_NORMAL_SERVICE;
            }
            break;

        default:
            ucState = g_MmGlobalInfo.ucState;
            break;
    }

    return ucState;
}
#if (FEATURE_ON == FEATURE_LTE)


VOS_VOID NAS_MM_ResponseLmmPagingInd_CSFB(VOS_VOID)
{
    MM_MSG_PAGING_RSP_STRU              stCmRspRsp;

    Mm_TimerStop(MM_TIMER_T3211);

    if (VOS_TRUE == NAS_MML_IsNeedClearCsCksn_UsimDoneGsmCsAuth())
    {
        NAS_MML_SetSimCsSecurityCksn(MM_CKSN_INVALID);
        NAS_MML_SetUsimDoneGsmCsAuthFlg(VOS_FALSE);
    }
    
    stCmRspRsp.MmIeCksn.ucCksn = NAS_MML_GetSimCsSecurityCksn();                /* 存储CKSN                                 */


    NAS_MM_FillMobileID(&(stCmRspRsp.MmIeMobileId.MobileID));

    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())                /* 当前处于 GSM 网中 */
    {
        /* 向 GAS 发送建立 RR 请求 */
        Mm_SndRrEstReq(RRC_EST_CAUSE_TERMINAT_CONVERSAT_CALL, MM_TRUE,
                       MM_CONST_NUM_0, VOS_NULL_PTR);
    }
    else /* UMTS 网中 */
    {
        g_MmGlobalInfo.ucPagingCause = RRC_PAGE_CAUSE_TERMINAT_CONVERSAT_CALL;
        Mm_ComMsgPagingRspSnd( &stCmRspRsp );                                   /* 填充并发送 PAGING RESPONSE 消息          */
    }

    g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                         /* 记录迁移之前的状态                       */
    Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_MM_CONNECTION);
    Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);                                        /* 通知MMC，CS域的业务已经启动              */

    NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);

    Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);                                 /* 启动保护TIMER                            */

    NAS_MML_SetCsServiceConnStatusFlg(VOS_TRUE);

    return;
}



VOS_VOID NAS_MM_PerformBufferedSsService(VOS_VOID)
{
    MM_MSG_CM_SVC_REQ_STRU              stCmSvcReq;                               /* 要发送的CM SERVICE REQ消息               */
    VOS_UINT16                          usMsgSize = 0;                          /* 消息长度,以字节为单位                    */
    VOS_UINT8                          *pucCmSvcReq = 0;                        /* 要发送的CM SERVICE REQ消息指针           */


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

    Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_SS_ACT, MM_FALSE, &stCmSvcReq);      /* 填充CM SERVICE REQUEST结构体             */
    pucCmSvcReq = Mm_ComMsgCmSvcReqOfRrEstReq( &stCmSvcReq, &usMsgSize );       /* 填充CM SERVICE REQUEST 消息              */
    if (VOS_NULL_PTR == pucCmSvcReq)
    {                                                                           /* 消息制作失败                             */
        NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_PerformBufferedSsService: MAKE MSG CM SERVICE REQUEST ERROR!");
        return;                                                                 /* 返回                                     */
    }
    else
    {                                                                           /* 消息制作成功                             */
        Mm_SndRrEstReq(RRC_EST_CAUSE_ORIGIN_HIGH_PRIORITY_SIGNAL,
           MM_FALSE, usMsgSize, pucCmSvcReq);                                   /* 发送消息                                 */
        MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucCmSvcReq);                        /* 释放CM SERVICE REQUEST 消息结构体        */
    }
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI =
        (VOS_UINT8)g_MmSsEstReq.ulTi;                                           /* 记录正在建立的MM连接的TI                 */
    g_MmGlobalInfo.ucMMConnEstingPD = MM_IE_PD_NON_CALL_RLT_SS_MSG;             /* 记录正在建立的MM连接的PD                 */
    Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);
    Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);                                        /* 通知MMC，CS域的业务已经启动              */
    NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);
    g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                         /* 记录迁移之前的状态                       */
    Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_MM_CONNECTION);

    NAS_MM_UpdateCsServiceConnStatusFlg();

    NAS_MM_UpdateCsServiceBufferStatusFlg();

    return;
}

VOS_VOID NAS_MM_RcvSysInfo_CSFB(VOS_VOID)
{
    NAS_MML_CSFB_SERVICE_STATUS_ENUM_UINT8                  enCsfbServiceStatus;
    VOS_UINT32                                              ulLaiChangeFlag;

    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8               enCsUpdateStatus;

    enCsUpdateStatus  = NAS_MML_GetCsUpdateStatus();

    enCsfbServiceStatus = NAS_MML_GetCsfbServiceStatus();
    ulLaiChangeFlag     = NAS_MML_IsCsLaiChanged();

    /* CSFB 流程，如果LAI改变，做LAU, 如果LAI未变，可直接发起业务 */
    switch (enCsfbServiceStatus)
    {
        case NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_CC_EXIST:

            /* 3GPP 24008 4.4.1:
               indicating to the network that the MS, configured to use CS fallback
               and SMS over SGs, or SMS over SGs only, has entered a GERAN or UTRAN cell in
               NMO II or III, after intersystem change from S1 mode to Iu or A/Gb mode,
               the TIN indicates "GUTI" and the location area of the current cell is the
               same as the stored location area; NOTE1:The location updating procedure
               can be delayed when the intersystem change is due to CS fallback.
               In this case, the MS has to remember that it has to perform a
               location updating procedure after the RR connection is released,
               if the MS is still in GERAN/UTRAN.*/

            if ((VOS_FALSE == ulLaiChangeFlag)
             && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus))
            {

                /* 当前存在缓存的CC业务，发起CC业务 */
                if ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
                {
                    /* 记录delay lau标识，呼叫结束后收到系统消息需要做lau */
                    NAS_MML_SetDelayedCsfbLauFlg(VOS_TRUE);

                    g_MmGlobalInfo.ucStaOfRcvXXEstReq = NAS_MM_GetStaOfRcvXXEstReq_CSFB();/* 记录收到建立请求时的状态                 */

                    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                MM_MMC_LU_RESULT_SUCCESS,
                                                NAS_MML_REG_FAIL_CAUSE_NULL);   /* 向MMC发送MMCMM_LU_RESULT_IND */

                    Mm_ComSetMmState(NAS_MM_GetStaOfRcvXXEstReq_CSFB());

                    NAS_MM_EstMmConnection(MM_CONN_CTRL_CC);
                    return;
                }

                /* 无缓存的CC业务，进行异常处理 */
                NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_RcvSysInfo_CSFB:NORMAL CC BUFFER NOT EXIST ");

                NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
                return;
            }

            /* 发起LAU流程,LAU成功后进行CSFB的主叫 */
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;

            Mm_ComLuOnly();

            return ;

        case NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST:
            if ((VOS_FALSE == ulLaiChangeFlag)
             && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus))
            {
                /* 当前存在缓存的SS业务，发起缓存的SS业务 */
                if ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg )
                {
                    /* 记录delay lau标识，呼叫结束后收到系统消息需要做lau */
                    NAS_MML_SetDelayedCsfbLauFlg(VOS_TRUE);

                    g_MmGlobalInfo.ucStaOfRcvXXEstReq = NAS_MM_GetStaOfRcvXXEstReq_CSFB(); /* 记录收到建立请求时的状态                 */

                    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                MM_MMC_LU_RESULT_SUCCESS,
                                                NAS_MML_REG_FAIL_CAUSE_NULL);   /* 向MMC发送MMCMM_LU_RESULT_IND */

                    Mm_ComSetMmState(NAS_MM_GetStaOfRcvXXEstReq_CSFB());

                    NAS_MM_PerformBufferedSsService();
                    return;
                }

                /* 无缓存的CC业务，进行异常处理 */
                NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_RcvSysInfo_CSFB:SS BUFFER SERVICE NOT EXIST ");

                NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
                return;
            }

            /* 发起LAU流程,LAU成功后进行CSFB的SS业务 */
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;


            Mm_ComLuOnly();
            return;

        case NAS_MML_CSFB_SERVICE_STATUS_MT_EXIST:

            if (NAS_MML_MT_CSFB_PAGING_TIMER_RUNNING == NAS_MML_GetCsfbMtPagingTimerStatus())
            {
                /* 后续LAU携带CSMT标志 */
                NAS_MM_SetCsfbMtLauFlg(VOS_TRUE);
            }

            if ((VOS_FALSE == ulLaiChangeFlag)
             && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus))
            {
                g_MmGlobalInfo.ucStaOfRcvXXEstReq = NAS_MM_GetStaOfRcvXXEstReq_CSFB();

                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                            MM_MMC_LU_RESULT_SUCCESS,
                                            NAS_MML_REG_FAIL_CAUSE_NULL);       /* 向MMC发送MMCMM_LU_RESULT_IND */

                Mm_ComSetMmState(NAS_MM_GetStaOfRcvXXEstReq_CSFB());            /* CREG状态迁移 */

                /* 在GU下，回复paging response */
                NAS_MM_ResponseLmmPagingInd_CSFB();

                /* 记录状态为CSFB MT已发送paging response */
                NAS_MM_RecordErrorLogInfo(NAS_ERR_LOG_BASE_STATE_PAGING_RSP_SEND,
                                          NAS_MML_REG_FAIL_CAUSE_NULL);

                /* 记录delay lau标识，呼叫结束后收到系统消息需要做lau */
                NAS_MML_SetDelayedCsfbLauFlg(VOS_TRUE);

                return;
            }

            /* 修改为在收到CSFB寻呼时候启动定时器 */

            /* 发起LAU流程 */
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;

            /* 记录状态为CSFB MT触发LAU流程 */
            NAS_MM_RecordErrorLogInfo(NAS_ERR_LOG_BASE_STATE_TRAG_LAU,
                                      NAS_MML_REG_FAIL_CAUSE_NULL);


            Mm_ComLuOnly();
            return;

        case NAS_MML_CSFB_SERVICE_STATUS_MO_EMERGENCY_EXIST:
            /* 如果lai不同但注册受限无需lau直接发起紧急呼叫 */
            if (VOS_TRUE == NAS_MM_IsNeedLauFirst_CsfbMoEmcExist())
            {
                /* NV配置lai改变先做lau再进行紧急呼叫，发起LAU流程 */
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;

                Mm_ComLuOnly();
                return;
            }

            /* 当前存在缓存的CC业务，发起CC业务 */
            if ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
            {
                /* 记录delay lau标识，呼叫结束后收到系统消息需要做lau */
                NAS_MML_SetDelayedCsfbLauFlg(VOS_TRUE);

                g_MmGlobalInfo.ucStaOfRcvXXEstReq = NAS_MM_GetStaOfRcvXXEstReq_CSFB(); /* 记录收到建立请求时的状态                 */

                /* 紧急呼CSFB到GU,不需要做LAU时，上报CS域注册状态 */
                NAS_MM_SndMmcCsRegResultInd_CsfbMoEmcExist();

                Mm_ComSetMmState(NAS_MM_GetStaOfRcvXXEstReq_CSFB());

                NAS_MM_EstMmConnection(MM_CONN_CTRL_CC);

                return;
            }

            /* 无缓存的CC业务，进行异常处理 */
            NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_RcvSysInfo_CSFB:NORMAL CC BUFFER NOT EXIST ");

            NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

            NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
            return;

         default:
            break;
    }

    return;
}
#endif


VOS_VOID Mm_Cell_S3_E5(VOS_VOID *pRcvMsg)
{
    VOS_UINT32                          ulLaiChangeFlag;
    VOS_UINT8                           ucPsRestrictionFlg;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrentNetRatType;
    VOS_UINT8                           ucT3211RunFlg;
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulCsfbExistFlag;
    VOS_UINT32                          ulEmergencyCallFlg;

    ulEmergencyCallFlg  = Mm_ComJudgeCsServExist();

    /* 取得CSFB是否存在的标志 */
    ulCsfbExistFlag     = NAS_MML_IsCsfbServiceStatusExist();
#endif

    enCurrentNetRatType = NAS_MML_GetCurrNetRatType();
    ucPsRestrictionFlg  = NAS_MML_GetPsRestrictRegisterFlg();

    ucT3211RunFlg       = VOS_FALSE;



    /* ==>AT2D01490 */
    ulLaiChangeFlag =  NAS_MML_IsCsLaiChanged();
    if ( (VOS_TRUE == ulLaiChangeFlag) ||
        ((g_MmGlobalInfo.MsCsInfo.ucCellChgFlg == MM_TRUE) && (MM_TRUE == g_MmGlobalInfo.LuInfo.ucRetryFlg)))
    {
        if (MM_TIMER_RUNNING == gstMmTimer[MM_TIMER_T3211].ucTimerStatus)
        {
            ucT3211RunFlg = VOS_TRUE;
            Mm_TimerStop(MM_TIMER_T3211);
        }
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
     && (VOS_FALSE == ucPsRestrictionFlg)
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

            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S3_E5:INFO: MmLikeB is MM_TRUE");

            if (VOS_TRUE == NAS_MML_IsCampLaiInfoChanged())
            {
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;       /* 设置LU类型                               */
                Mm_ComLuOnly();                                             /* LU REQ                                   */
            }
            else
            {
                if ( MMCMM_FORBIDDEN_PLMN_FOR_GPRS !=
                            g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg )
                {
                    NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                }
                g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;         /* 记录前状态                               */
                Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);


                Mm_SndRrNasInfoChgReq(MM_NAS_INFO_SYNC_AS_FLG);


                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                            MM_MMC_LU_RESULT_SUCCESS,
                                            NAS_MML_REG_FAIL_CAUSE_NULL);

                NAS_MM_SndGmmLuResultInd(MMGMM_LU_SUCCESS,
                                         NAS_MML_REG_FAIL_CAUSE_NULL);

                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E5:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
            }
        }
        else
        {                                                                       /* RAC不等于0                               */
            if ( VOS_TRUE == ulLaiChangeFlag )
            {
                g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;             /* 记录前状态                               */
                Mm_ComSetMmState(MM_WAIT_FOR_ATTACH);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E5:NORMAL: STATUS is MM_WAIT_FOR_ATTACH");
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

        if ( g_MmGlobalInfo.ucNtMod != g_MmGlobalInfo.ucNewNtMod )
        {
            Mm_ComNetModeChange();
        }
        else
        {
            if ( VOS_TRUE == ulLaiChangeFlag )
            {                                                               /* 如果LAI变                                */
                NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, MM_IE_LUT_NORMAL_LU);
            }
            else
            {
                if (VOS_TRUE == ucT3211RunFlg)
                {
                    Mm_ComLuOnly();
                }
                else
                {
                    /* A+0模式,PS不支持时,LAI不改变时,3212超时发起LAU不响应再次收到系统消息不应该
                       再次发起LAU */
                    if ((MM_TRUE == g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg)
                     && (MM_TIMER_RUNNING != gstMmTimer[MM_TIMER_T3211].ucTimerStatus))
                    {
                        g_MmGlobalInfo.LuInfo.ucLuType =
                                        MM_IE_LUT_PERIODIC_UPDATING;            /* 设置LU类型                               */
                        Mm_ComLuOnly();                                         /* 发送LU REQ                               */
                        return;
                    }

                    if (VOS_TRUE == NAS_MM_IsDisableGprsCombineAttach())
                    {
                        NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                    }
                }

                if (enCurrentNetRatType != g_MmGlobalInfo.enPreRatType)
                {


                    /* 回复MMCMM_ATTACH_CNF的操作,清除等待ATTACH结果标志位 */
                    if (MM_WAIT_CS_ATTACH == (g_MmGlobalInfo.stAttachInfo.enAttachType
                                            & MM_WAIT_CS_ATTACH))
                    {
                        NAS_MM_SndMmcAttachCnf();
                    }
                    g_MmGlobalInfo.stAttachInfo.enAttachType = MM_WAIT_NULL_ATTACH;
                }


                Mm_SndRrNasInfoChgReq(MM_NAS_INFO_SYNC_AS_FLG);


                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                            MM_MMC_LU_RESULT_SUCCESS,
                                            NAS_MML_REG_FAIL_CAUSE_NULL);

                NAS_MM_SndGmmLuResultInd(MMGMM_LU_SUCCESS,
                                         NAS_MML_REG_FAIL_CAUSE_NULL);

            }
        }
    }

    if ((WAIT_FOR_RR_CONNECTION_LOCATION_UPDATING != g_MmGlobalInfo.ucState)
     && ((MM_WAIT_FOR_ATTACH != g_MmGlobalInfo.ucState)
      || (VOS_TRUE == ulEmergencyCallFlg)))
    {
        Mm_DealWithBuffMsg();
    }
}




VOS_VOID Mm_Cell_S3_E9(VOS_VOID *pMsg)
{

    if ( MM_FALSE == Mm_RcvGmmImsiDetechIni(pMsg) )
    {
        return;
    }

    g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                         /* 记录前状态                               */
    Mm_ComSetMmState(IMSI_DETACH_PENDING);
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E9:NORMAL: STATUS is IMSI_DETACH_PENDING");
}



VOS_VOID Mm_Cell_S3_E11(VOS_VOID *pMsg)
{
    GMMMM_GPRS_DETACH_INITIATION_STRU   *pGprsDetachInit;

    if ( MM_FALSE == NAS_MM_RcvGmmGprsDetechIni(pMsg) )
    {
        return;
    }

    pGprsDetachInit = (GMMMM_GPRS_DETACH_INITIATION_STRU*)pMsg;

    if ( GMMMM_GPRS_DETACH_NORMAL == pGprsDetachInit->enDetachType )
    {
        ;                                                                       /* 空处理                                   */
    }
    else
    {
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* 记录前状态                               */
        Mm_ComSetMmState(IMSI_DETACH_PENDING);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E11:NORMAL: STATUS is IMSI_DETACH_PENDING");
    }
}


VOS_VOID Mm_Cell_S32_E32(
    VOS_VOID                           *pRcvMsg
)
{
    if ( MM_FALSE == Mm_RcvRrcEstCnf(pRcvMsg) )
    {
        /* WUEPS_ASSERT(0); */
    }
    else
    {
        if (WAIT_FOR_RR_CONNECTION_MM_CONNECTION == g_MmGlobalInfo.ucSuspendPreState)
        {
            Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

            if (NO_MM_CONN_ESTING != g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI )
            {
                /* CC发起的RR连接的建立, 通知CC建立失败             */
                Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI,
                                   NAS_MMCM_REL_CAUSE_MM_INTER_ERR_INTER_RAT_SYSTEM_CHANGE);

                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI = NO_MM_CONN_ESTING;
            }
            else if ( NO_MM_CONN_ESTING !=
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI )
            {
                /* SS发起的RR连接的建立 ，通知SS,MM连接建立失败      */
                Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI,
                                   NAS_MMCM_REL_CAUSE_MM_INTER_ERR_INTER_RAT_SYSTEM_CHANGE);

                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI = NO_MM_CONN_ESTING;
            }
            else if ( NO_MM_CONN_ESTING !=
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI )
            {
                /* SMS发起的RR连接的建立 ,通知SMS,MM连接建立失败      */
                Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI,
                                   NAS_MMCM_REL_CAUSE_MM_INTER_ERR_INTER_RAT_SYSTEM_CHANGE);
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI = NO_MM_CONN_ESTING;
            }
            else
            {
                /* 没有正在建立的MM连接，即被叫 */
            }

            /* 业务触发的建链过程 */
            if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
             || (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg)
             || (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg))
            {

                Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );
                NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
            }

            /* 清除消息缓存标志 */
            NAS_MM_ClearConnCtrlInfo(g_MmGlobalInfo.ucMMConnEstingPD);

            g_MmGlobalInfo.ucSuspendPreState = g_MmGlobalInfo.ucStaOfRcvXXEstReq;
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

