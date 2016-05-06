/*******************************************************************************
  Copyright     : 2005-2007, Huawei Tech. Co., Ltd.
  File name     : EmmTAU.c
  Description   : EMM TAU REQUEST功能相关处理用源文件
  Function List :
    01.   NAS_EMM_MsRegSsNormalMsgSysinfo
    02.   NAS_EMM_MsRegSsNormalMsgT3411Exp
    03.   NAS_EMM_MsRegSsNormalMsgT3412Exp
    04.   NAS_EMM_MsRegSsNormalMsgT3402Exp
    05.   NAS_EMM_MsRegSsNormalMsgMmIntraTAUReq
    06.   NAS_EMM_MsRegSsAtpUpdataMsgSysinfo
    07.   NAS_EMM_MsRegSsAtpUpdataMsgT3411Exp
    08.   NAS_EMM_MsRegSsAtpUpdataMsgT3402Exp
    09.   NAS_EMM_MsRegSsLimitSRMsgSysinfo
    10.   NAS_EMM_MsRegSsPLMNSearchMsgSysinfo
    11.   NAS_EMM_MsRegSsUpdataNeedMsgSysinfo
    12.   NAS_EMM_MsRegSsNocellMsgSysinfo
    13.   NAS_EMM_MsTAUInitSsWaitCNCnfMsgTAUAcp
    14.   NAS_EMM_MsTAUInitSsWaitCNCnfMsgTAURej
    15.   NAS_EMM_MsTAUInitSsWaitCNCnfMsgT3430Exp
    16.   NAS_EMM_MsTAUInitSsWaitCNCnfMsgSysinfo
    17.   NAS_EMM_MsTauInitSsWaitCNCnfMsgIntraConnectFailInd
    18.   NAS_EMM_MsTAUInitSsWaitCNCnfMsgRrcRelInd
    19.   NAS_EMM_MsTAUInitSsWaitMrrcRelMsgMrrcRelInd
    20.   NAS_EMM_MsSERInitSsWaitCNCnfMsgSysinfo
    21.   NAS_EMM_MsSERInitSsWaitCNCnfMsgT3411Exp
    22.   NAS_EMM_MsSERInitSsWaitCNCnfMsgT3412Exp
    23.   NAS_EMM_MsSERInitSsWaitCNCnfMsgT3402Exp
    24.   NAS_EMM_MsSERInitSsWaitCNCnfMsgMmIntraTAUReq

  History       :
    1.  Zhouyan     00125190    2008.09.17  新规作成
    2.  luojian     00107747    2009.01.13  协议更新到8.0.0
    3.  hanlufeng   41410       2009.04.25  BJ9D00494 被BAR后的处理，已向卢哲军
                                确认，接入被BAR后RRC不会重选到属于FORBIDDEN LIST
                                的小区
    4.  leili       00132387    2009.06.25   BJ9001269 收到系统消息后处理优化
*******************************************************************************/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include "NasEmmTauSerInclude.h"
#include "NasEmmAttDetInclude.h"
#include "NasEmmTauInterface.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASEMMTAUREQ_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASEMMTAUREQ_C
/*lint +e767*/


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/
VOS_UINT32    g_ulIntraHoIgnoreForbidTaFlag = PS_FALSE;



/*******************************************************************************
  Function : NAS_EMM_TAU_StartTAUREQ
  Input    :
  Output   :
  NOTE     :
  Return   :
  History  :
    1.Zhouyan 00125190  2008.09.17  新规作成
    2.z00148421  2009.03.06
    3.sunjitan 00193151    2012-07-10 Modify: Last attempt reg TA 维护,增加save Last TA操作
    4.leixiantiao 00258641 2015-07-23 Modify: 新增入参TAU发起原因,用于上报给HIDS
*******************************************************************************/
VOS_VOID    NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_ENUM_UINT32 enTauStartType)
{
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    TAF_CTRL_STRU                                           stCtrl;
    MTC_SESSION_TYPE_ENUM_UINT8                             enMtcSessionType = MTC_SESSION_TYPE_BUTT;
    PS_MEM_SET(&stCtrl, 0x00, sizeof(TAF_CTRL_STRU));
#endif

    /* 打印进入该函数， INFO_LEVEL */
    NAS_EMM_TAU_LOG_NORM( "NAS_EMM_TAU_StartTAUREQ is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_StartTAUREQ_ENUM,LNAS_ENTRY);

    /* 如果由于L无线能力变更发起的TAU，则不发起，转为本地DETACH重新ATTACH */
    if (NAS_LMM_UE_RADIO_CAP_LTE_CHG == NAS_LMM_GetEmmInfoUeRadioCapChgFlag())
        {
            /*需要清理TAU和SER资源, 在下面的函数处理中将清理所有相关资源*/
            NAS_EMM_TAU_LOG_NORM("NAS_EMM_TAU_StartTAUREQ:  LTE change, local detach and re-attach needed.");
             TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_StartTAUREQ_ENUM,LNAS_FUNCTION_LABEL1);
            NAS_EMM_SomeStateRcvMsgSysInfoLteRadioCapChgCommProc();
            return;
    }
    /* 勾出TAU发起条件 */
    NAS_LMM_SndOmTauStartTypeInfo(enTauStartType);

    /* 大数据:更新TAU发起次数 */
    NAS_LMM_AddTauCounter(NAS_LMM_OM_PCE_TIMES_TYPE_TOTAL);
    /*启动定时器T3430*/
    NAS_LMM_StartStateTimer(TI_NAS_EMM_STATE_TAU_T3430);

    NAS_LMM_Stop3402Timer();
    NAS_LMM_StopPtlTimer(TI_NAS_EMM_PTL_T3411);

    NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_SERVICE_T3442);

    /* 清除UPDATE_MM标识 */
    /*NAS_LMM_SetEmmInfoUpdateMmFlag(NAS_EMM_UPDATE_MM_FLAG_INVALID);*/

    /* DTS201202070220 增加是否有上行数据和信令pending的判断 */
    NAS_EMM_TAU_IsUplinkPending();

    /*转换EMM状态机MS_TAU_INIT+SS_TAU_WAIT_CN_TAU_CNF*/
    NAS_EMM_TAUSER_FSMTranState(EMM_MS_TAU_INIT, EMM_SS_TAU_WAIT_CN_TAU_CNF, TI_NAS_EMM_STATE_TAU_T3430);

    #if (FEATURE_ON == FEATURE_DSDS)
    /*发送begin notify消息给RRC，通知RRC申请资源*/
    NAS_EMM_TAU_SendRrcDsdsBeginNotify();
    #endif

    /*组合并发送MRRC_DATA_REQ(TAU_REQ)*/
    if(NAS_EMM_TRIGGER_TAU_RRC_REL_LOAD_BALANCE ==
                                        NAS_LMM_GetEmmInfoTriggerTauRrcRel())
    {
        NAS_EMM_TAU_SendMrrcDataReq_TAUReq(       NAS_EMM_MSG_LOAD_BALANCING_TAU);
    }
    else
    {
        NAS_EMM_TAU_SendMrrcDataReq_TAUReq(       NAS_EMM_MSG_NOT_LOAD_BALANCING_TAU);
    }

    /* 发起TAU，将当前网络信息同步到Last尝试发起注册的网络信息中 */
    NAS_EMM_SaveLastAttemptRegTa();


    /*清除TAU_REQ发送失败原因是LRRC释放标识*/
    NAS_LMM_SetTauReqSndFailFlag(PS_FALSE);

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    stCtrl.ulModuleId = PS_PID_MM;
    enMtcSessionType = NAS_EMM_GetTAUMtcSessionType();

    MTC_SetBeginSessionInfo(&stCtrl,enMtcSessionType);
#endif
    return;
}

/*******************************************************************************
  Module   :
  Function : Nas_Emm_TAU_RcvSysinfo
  Input    :
  Output   :
  NOTE     :
  Return   :
  History  :
    1.  Zhouyan 00125190  2008.09.17  新规作成
*******************************************************************************/
/*lint -e960*/
/*lint -e961*/
VOS_UINT32 NAS_EMM_TAU_IsCurrentTAInTaList(VOS_VOID)
{
    VOS_UINT32                          ulTARslt         = NAS_EMM_FAIL;
    NAS_MM_TA_STRU                      stPresentTa;
    NAS_MM_TA_LIST_STRU                 stLastTaiList;

    NAS_LMM_MEM_SET_S(  &stLastTaiList,
                        sizeof(NAS_MM_TA_LIST_STRU),
                        0,
                        sizeof(NAS_MM_TA_LIST_STRU));

    /*获取当前的TA*/
    NAS_LMM_MEM_CPY_S(      &(stPresentTa.stPlmnId),
                            sizeof(NAS_MM_PLMN_ID_STRU),
                            &(g_stEmmInfo.stNetInfo.stPresentNetId.stPlmnId),
                            sizeof(NAS_MM_PLMN_ID_STRU));

    NAS_LMM_MEM_CPY_S(      &(stPresentTa.stTac),
                            sizeof(NAS_MM_TAC_STRU),
                            &(g_stEmmInfo.stNetInfo.stPresentNetId.stTac),
                            sizeof(NAS_MM_TAC_STRU));

    /*获取上次注册的TA List*/
    NAS_LMM_MEM_CPY_S(      &(stLastTaiList),
                            sizeof(NAS_MM_TA_LIST_STRU),
                            &(g_stEmmInfo.stNetInfo.stTaiList),
                            sizeof(NAS_MM_TA_LIST_STRU));

    /*判断当前TA是否在TA List中*/
    ulTARslt = NAS_LMM_TaMatchTaList(&stPresentTa, &stLastTaiList);

    /*如果新的TA在TA List中*/
    if(NAS_LMM_MATCH_SUCCESS == ulTARslt)
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_TAU_IsCurrentTAInTaList:TA is in the TAI List.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_IsCurrentTAInTaList_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_SUCC;
    }
    /*TA不在TA List中，需要发起TAU流程*/
    else
    {
        NAS_EMM_TAU_LOG_INFO( "NAS_EMM_TAU_IsCurrentTAInTaList:TA is not in the TAI List,TAU Need.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_IsCurrentTAInTaList_ENUM,LNAS_EMM_TA_NOT_IN_TA_LIST);
        return NAS_EMM_FAIL;
    }
}
#if(FEATURE_ON == FEATURE_CSG)
/*******************************************************************************
  Function : NAS_EMM_TAU_IsCSGIdInAllowedOrOperaterCSGList
  Input    :
  Output   :
  NOTE     :
  Return   :
  History  :
    1.yanglei 00307272  2015-09-24  新规作成
*******************************************************************************/
VOS_UINT32 NAS_EMM_TAU_IsCsgIdInAllowedOrOperatorCsgList(VOS_VOID)
{
    VOS_UINT32                          ulCsgRslt         = NAS_EMM_FAIL;

    NAS_MML_PLMN_WITH_CSG_ID_LIST_STRU  *pstAllowedCsgList;
    NAS_MML_PLMN_WITH_CSG_ID_LIST_STRU  *pstOperatorCsgList;


    pstAllowedCsgList  = NAS_MML_GetAllowedCsgList();
    pstOperatorCsgList = NAS_MML_GetOperatorCsgList();


    /*判断当前CSG ID是否在CSG List中*/
    ulCsgRslt = NAS_LMM_CsgIdMatchAllowedOrOperatorCsgList(pstAllowedCsgList,pstOperatorCsgList);

    /*如果新的CSG在CSG List中*/
    if(NAS_LMM_MATCH_SUCCESS == ulCsgRslt)
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_TAU_IsCSGIdInAllowedOrOperatorCSGList:CSG ID is in the CSG List.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_IsCSGIdInAllowedOrOperatorCSGList_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_SUCC;
    }
    /*CSG不在CSG List中，需要发起TAU流程*/
    else
    {
        NAS_EMM_TAU_LOG_INFO( "NAS_EMM_TAU_IsCSGIdInAllowedOrOperatorCSGList:CSG ID is not in the CSG List,TAU Need.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_IsCSGIdInAllowedOrOperatorCSGList_ENUM,LNAS_FUNCTION_LABEL2);
        return NAS_EMM_FAIL;
    }
}
#endif

/*******************************************************************************
  Module   :
  Function : NAS_EMM_MsRegSsNormalMsgSysinfo
  Input    :
  Output   :
  NOTE     :
  Return   :
  History  :
    1.  Zhouyan 00125190  2008.09.10  新规作成
    2.  zhengjunyan 00148421 2011-02-15 DTS2011021401149
    3.  sunjitan 00193151     2011-09-13    DTS2011080801319
    4.  sunjitan 00193151     2012-02-02   Modify for UE radio capability
    5.  lihong 00150010       2012-12-18   Modify:Emergency
    6.  leixiantiao 00258641  2015-07-03   fix DTS2015062301014
*******************************************************************************/
VOS_UINT32 NAS_EMM_MsRegSsNormalMsgSysinfo(VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru)
{
    VOS_UINT32                          ulRslt          = NAS_EMM_FAIL;
    EMMC_EMM_SYS_INFO_IND_STRU         *pstsysinfo      = NAS_EMM_NULL_PTR;
    EMMC_EMM_FORBIDDEN_INFO_ENUM_UINT32  ulForbiddenInfo = EMMC_EMM_NO_FORBIDDEN;

    pstsysinfo                          = (EMMC_EMM_SYS_INFO_IND_STRU*)pMsgStru;

    (VOS_VOID)ulMsgId;

    /* 打印进入该函数， INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO("Nas_Emm_MsRegSsNormalMsgSysinfo is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsNormalMsgSysinfo_ENUM,LNAS_ENTRY);

    ulRslt = NAS_EMM_TAU_CHKFSMStateMsgp(EMM_MS_REG,EMM_SS_REG_NORMAL_SERVICE,pMsgStru);

    /* 函数输入指针参数检查, 状态匹配检查,若不匹配,退出*/
    if(NAS_EMM_SUCC != ulRslt)
    {
        /* 打印异常 */
        NAS_EMM_TAU_LOG_WARN("NAS_EMM_MsRegSsNormalMsgSysinfo:ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsNormalMsgSysinfo_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }
    /* 定制系统内切换到被禁小区,忽略被禁:当存在L小区A和B(属于俩TA)
        UE在小区B上驻留，由于MME某些异常,给UE下发原因值#15，但MME未将
        TA放入被禁列表中(未真被禁，只是临时被禁)，当UE收到#15原因值,
        主动释重新驻留在A小区，之后网侧让UE切换到B小区，而切换时LRRC
        不会判断小区是否被禁，LMM收到系统消息后，由B小区上收到过#15原
        因值,LMM主动释放进入限制服务态，LRRC释放后在小区A上驻留，从而导致乒乓切换 */
    ulForbiddenInfo = pstsysinfo->ulForbiddenInfo;
    if(NAS_EMM_YES == NAS_EMM_IsIntraHoIgnoreForbSysInfo())
    {
        /* 忽略FORBIDDEN TA FOR ROAMING,由于被#15原因值拒后,驻留的TA将放入FORBIDDEN TA LIST里,并从TAILIST里删除，所以后续发起TAU */
        if(EMMC_EMM_FORBIDDEN_TA_FOR_ROAMING == pstsysinfo->ulForbiddenInfo)
        {
            NAS_EMM_PUBU_LOG1_INFO("NAS_EMM_MsRegSsNormalMsgSysinfo Ignore ForbTaForRoaming:forbiddenInfo = ",
                               pstsysinfo->ulForbiddenInfo);
            TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsRegSsNormalMsgSysinfo_ENUM,LNAS_EMM_FORB_INFO,
                               pstsysinfo->ulForbiddenInfo );
            ulForbiddenInfo = EMMC_EMM_NO_FORBIDDEN;
            #if (FEATURE_ON == FEATURE_PTM)
            NAS_EMM_ImprovePerformceeErrReport(EMM_OM_ERRLOG_IMPROVEMENT_TYPE_HO_TO_FORBIDDEN_TA);
            #endif
        }
    }
    /*根据禁止信息判断是否处理当前的系统消息*/
    if ((NAS_LMM_REG_STATUS_NORM_REGED == NAS_LMM_GetEmmInfoRegStatus())
        && ((EMMC_EMM_NO_FORBIDDEN != ulForbiddenInfo)
            || (EMMC_EMM_CELL_STATUS_ANYCELL == pstsysinfo->ulCellStatus)))
    {
        NAS_EMM_SetTauTypeNoProcedure();

        /*转换EMM状态机*/
        NAS_EMM_TAUSER_FSMTranState(EMM_MS_REG,
                                    EMM_SS_REG_LIMITED_SERVICE,
                                    TI_NAS_EMM_STATE_NO_TIMER);

        /*向MMC发送LMM_MMC_TAU_RESULT_IND消息*/
        NAS_EMM_MmcSendTauActionResultIndForbType((VOS_VOID*)&pstsysinfo->ulForbiddenInfo);
        /* 如果当前CSFB延时定时器在运行，说明之前在释放过程中收到过CSFB，
           这种情况下直接报SERVICE失败触发MMC搜网去GU */
        if(NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_CSFB_DELAY))
        {
            /* 停止CSFB时延定时器 */
            NAS_LMM_StopPtlTimer(TI_NAS_EMM_PTL_CSFB_DELAY);

            /* 给MMC上报SERVICE失败触发搜网去GU */
            NAS_EMM_MmcSendSerResultIndOtherType(MMC_LMM_SERVICE_RSLT_FAILURE);
        }
        if (MMC_LMM_CONN_IDLE != NAS_EMM_GetConnState())
        {
            NAS_EMM_TAU_LOG_INFO("Nas_Emm_MsRegSsNormalMsgSysinfo: Connected");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsNormalMsgSysinfo_ENUM,LNAS_FUNCTION_LABEL1);

            /*发送NAS_EMM_REL_REQ*/
            NAS_EMM_RelReq(         NAS_LMM_NOT_BARRED);
        }
        return NAS_LMM_MSG_HANDLED;
    }

    /* 如果当前CSFB延时定时器在运行，说明之前在REG-NORMAL态释放过程中收到过CSFB，
       但是收到系统消息后又需要发起TAU，二者冲突的这种情况下优先发起TAU，之后再解决SERVICE的冲突 */
    if(NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_CSFB_DELAY))
    {
        /* 停止CSFB时延定时器 */
        NAS_LMM_StopPtlTimer(TI_NAS_EMM_PTL_CSFB_DELAY);

        /* 设置流程冲突标志位，后面发起TAU时会因存在冲突自然携带active flag，
           SERVICE发起原因不必记录，在启动CSFB延时定时器时已经设置上了 */
        NAS_EMM_TAU_SaveEmmCollisionCtrl(NAS_EMM_COLLISION_SERVICE);
        /* 增加入参,用于判断小区信息是否发生改变 */
        NAS_EMM_MsRegSsNormalCsfbDelayProc(pstsysinfo->ulChangeInfo);
    }
    else
    {
        /* 增加入参,用于判断小区信息是否发生改变 */
        NAS_EMM_RegNormalServiceOrUpdateMMMsgSysInfoCommProc(pstsysinfo->ulChangeInfo);
    }

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsRegSsRegAttemptUpdateMmMsgSysinfo
 Description     : 状态REG+REG_ATTEMPTING_TO_UPDATE_MM收到系统消息
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2011-7-12  Draft Enact
    2.sunjitan 00193151   2012-02-07 Modify  for UE Radio capability
    3.l00150010           2012-12-19 Modify:Emergency
*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegSsRegAttemptUpdateMmMsgSysinfo
(
    VOS_UINT32  ulMsgId,
    VOS_VOID   *pMsgStru
)
{
    VOS_UINT32                          ulRslt          = NAS_EMM_FAIL;
    EMMC_EMM_SYS_INFO_IND_STRU         *pstsysinfo      = NAS_EMM_NULL_PTR;
    EMMC_EMM_FORBIDDEN_INFO_ENUM_UINT32  ulForbiddenInfo = EMMC_EMM_NO_FORBIDDEN;

    pstsysinfo                          = (EMMC_EMM_SYS_INFO_IND_STRU*)pMsgStru;

    (VOS_VOID)ulMsgId;

    /* 打印进入该函数， INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO("NAS_EMM_MsRegSsRegAttemptUpdateMmMsgSysinfo is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgSysinfo_ENUM,LNAS_ENTRY);

    ulRslt = NAS_EMM_TAU_CHKFSMStateMsgp(   EMM_MS_REG,
                                            EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM,
                                            pMsgStru);

    /* 函数输入指针参数检查, 状态匹配检查,若不匹配,退出*/
    if(NAS_EMM_SUCC != ulRslt)
    {
        /* 打印异常 */
        NAS_EMM_TAU_LOG_WARN("NAS_EMM_MsRegSsRegAttemptUpdateMmMsgSysinfo:ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgSysinfo_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }
    /* 定制系统内切换到被禁小区,忽略被禁:当存在L小区A和B(属于俩TA)
        UE在小区B上驻留，由于MME某些异常,给UE下发原因值#15，但MME未将
        TA放入被禁列表中(未真被禁，只是临时被禁)，当UE收到#15原因值,
        主动释重新驻留在A小区，之后网侧让UE切换到B小区，而切换时LRRC
        不会判断小区是否被禁，LMM收到系统消息后，由B小区上收到过#15原
        因值,LMM主动释放进入限制服务态，LRRC释放后在小区A上驻留，从而导致乒乓切换 */
    ulForbiddenInfo = pstsysinfo->ulForbiddenInfo;
    if(NAS_EMM_YES == NAS_EMM_IsIntraHoIgnoreForbSysInfo())
    {
        /* 忽略FORBIDDEN TA FOR ROAMING,由于被#15原因值拒后,驻留的TA将放入FORBIDDEN TA LIST里,并从TAILIST里删除，所以后续发起TAU */
        if(EMMC_EMM_FORBIDDEN_TA_FOR_ROAMING == pstsysinfo->ulForbiddenInfo)
        {
            NAS_EMM_PUBU_LOG1_INFO("NAS_EMM_MsRegSsNormalMsgSysinfo Ignore ForbTaForRoaming:forbiddenInfo = ",
                               pstsysinfo->ulForbiddenInfo);
            TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgSysinfo_ENUM,LNAS_EMM_FORB_INFO,
                               pstsysinfo->ulForbiddenInfo);
            ulForbiddenInfo = EMMC_EMM_NO_FORBIDDEN;
            #if (FEATURE_ON == FEATURE_PTM)
            NAS_EMM_ImprovePerformceeErrReport(EMM_OM_ERRLOG_IMPROVEMENT_TYPE_HO_TO_FORBIDDEN_TA);
            #endif
        }
    }
    /*根据禁止信息判断是否处理当前的系统消息*/
    if ((NAS_LMM_REG_STATUS_NORM_REGED == NAS_LMM_GetEmmInfoRegStatus())
        && ((EMMC_EMM_NO_FORBIDDEN != ulForbiddenInfo)
            || (EMMC_EMM_CELL_STATUS_ANYCELL == pstsysinfo->ulCellStatus)))
    {
        /*NAS_LMM_SetEmmInfoUpdateMmFlag(NAS_EMM_UPDATE_MM_FLAG_VALID);*/

        NAS_EMM_SetTauTypeNoProcedure();

        /*转换EMM状态机*/
        NAS_EMM_TAUSER_FSMTranState(    EMM_MS_REG,
                                        EMM_SS_REG_LIMITED_SERVICE,
                                        TI_NAS_EMM_STATE_NO_TIMER);

        /*向MMC发送LMM_MMC_TAU_RESULT_IND消息*/
        NAS_EMM_MmcSendTauActionResultIndForbType((VOS_VOID*)&pstsysinfo->ulForbiddenInfo);

        if (MMC_LMM_CONN_IDLE != NAS_EMM_GetConnState())
        {
            NAS_EMM_TAU_LOG_INFO("NAS_EMM_MsRegSsRegAttemptUpdateMmMsgSysinfo: Limited Srv Connected");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgSysinfo_ENUM,LNAS_FUNCTION_LABEL1);

            /*发送NAS_EMM_REL_REQ*/
            NAS_EMM_RelReq(         NAS_LMM_NOT_BARRED);
        }
        return NAS_LMM_MSG_HANDLED;
    }
     /*判断TA发生变化，重置TAU ATTEMPT COUNTER,重新TAU*/
    if((EMMC_EMM_CHANGE_PLMN == pstsysinfo->ulChangeInfo)
      ||(EMMC_EMM_CHANGE_TA == pstsysinfo->ulChangeInfo))
    {
        NAS_EMM_TAU_SaveEmmTAUAttemptCnt(NAS_EMM_TAU_ATTEMPT_CNT_ZERO);
    }

    /* 增加入参,用于判断小区信息是否发生改变 */
    NAS_EMM_RegNormalServiceOrUpdateMMMsgSysInfoCommProc(pstsysinfo->ulChangeInfo);
    return NAS_LMM_MSG_HANDLED;
}


/*****************************************************************************
 Function Name   : NAS_EMM_MsRegSsNmlSrvProcMsgRrcRelInd
 Description     : 处理RRC_REL_IND消息
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.X00148705    2009-9-30  Draft Enact
    2.X00148705    2009-11-13 修改和重构
    3.Z00148421    2009-12-15 消息传输失败的处理
    4.Z00148421    2010-12-22 DTS2010111701490:CONN_FAIL和 LOAD_BALANCE_REQ原因值
                              不立即触发TAU，收到SYS_INFO_IND再触发。
*****************************************************************************/
VOS_VOID  NAS_EMM_MsRegSsNmlSrvProcMsgRrcRelInd( VOS_UINT32 ulCause )
{

    NAS_EMM_TAU_LOG_INFO(                         "NAS_EMM_MsRegSsNmlSrvProcMsgRrcRelInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsNmlSrvProcMsgRrcRelInd_ENUM,LNAS_ENTRY);

    /*发送内部消息 INTRA_CONN2IDLE_REQ,更新连接状态*/
    NAS_EMM_CommProcConn2Ilde();

    /* 停T3411定时器 */
    NAS_LMM_StopPtlTimer(TI_NAS_EMM_PTL_T3411);

    /* 根据RRC携带的释放原因值做不同处理*/
    switch(ulCause)
    {
        case LRRC_LNAS_REL_CAUSE_LOAD_BALANCE_REQ:
            /*NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_RRC_REL_LOAD_BALANCE);*/
            NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
            NAS_LMM_SetEmmInfoTriggerTauRrcRel(NAS_EMM_TRIGGER_TAU_RRC_REL_LOAD_BALANCE);
            /*
            NAS_EMM_TAUSER_FSMTranState(   EMM_MS_REG,
                                           EMM_SS_REG_PLMN_SEARCH,
                                           TI_NAS_EMM_STATE_NO_TIMER);
            */
             break;

        case LRRC_LNAS_REL_CAUSE_CONN_FAIL:
            /*NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_RRC_REL_CONN_FAILURE);*/
            NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
            NAS_LMM_SetEmmInfoTriggerTauRrcRel(NAS_EMM_TRIGGER_TAU_RRC_REL_CONN_FAILURE);
            /*
            NAS_EMM_TAUSER_FSMTranState(   EMM_MS_REG,
                                           EMM_SS_REG_PLMN_SEARCH,
                                           TI_NAS_EMM_STATE_NO_TIMER);
            */
            break;

        default:
            /* 其他原因不会导致TAU，不处理 */;
            NAS_EMM_TAU_LOG1_INFO("NAS_EMM_MsRegSsNmlSrvProcMsgRrcRelInd: ulCause = ", ulCause);
            TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsRegSsNmlSrvProcMsgRrcRelInd_ENUM,LNAS_CAUSE_NUMBER,ulCause);
            break;

    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsRegSsRegAttemptUpdateMmProcMsgRrcRelInd
 Description     : 处理RRC_REL_IND消息
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010    2014-09-03  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_EMM_MsRegSsRegAttemptUpdateMmProcMsgRrcRelInd
(
    VOS_UINT32                          ulCause
)
{
    /*发送内部消息 INTRA_CONN2IDLE_REQ,更新连接状态*/
    NAS_EMM_CommProcConn2Ilde();

    /* 根据RRC携带的释放原因值做不同处理*/
    switch(ulCause)
    {
        case LRRC_LNAS_REL_CAUSE_LOAD_BALANCE_REQ:

            /* 记录UPDATE_MM标识 */
            /*NAS_LMM_SetEmmInfoUpdateMmFlag(NAS_EMM_UPDATE_MM_FLAG_VALID);*/
            /*NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_RRC_REL_LOAD_BALANCE);*/
            NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
            NAS_LMM_SetEmmInfoTriggerTauRrcRel(NAS_EMM_TRIGGER_TAU_RRC_REL_LOAD_BALANCE);
            /*
            NAS_EMM_TAUSER_FSMTranState(    EMM_MS_REG,
                                            EMM_SS_REG_PLMN_SEARCH,
                                            TI_NAS_EMM_STATE_NO_TIMER);
            */
            break;

        case LRRC_LNAS_REL_CAUSE_CONN_FAIL:

            /* 记录UPDATE_MM标识 */
            /* NAS_LMM_SetEmmInfoUpdateMmFlag(NAS_EMM_UPDATE_MM_FLAG_VALID);*/
            /*NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_RRC_REL_CONN_FAILURE);*/
            NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
            NAS_LMM_SetEmmInfoTriggerTauRrcRel(NAS_EMM_TRIGGER_TAU_RRC_REL_CONN_FAILURE);
            /*
            NAS_EMM_TAUSER_FSMTranState(   EMM_MS_REG,
                                           EMM_SS_REG_PLMN_SEARCH,
                                           TI_NAS_EMM_STATE_NO_TIMER);
            */
            break;

        default:
            /* 其他原因不会导致TAU，不处理 */;
            NAS_EMM_TAU_LOG1_INFO("NAS_EMM_MsRegSsRegAttemptUpdateMmProcMsgRrcRelInd: ulCause = ", ulCause);
            TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsRegSsRegAttemptUpdateMmProcMsgRrcRelInd_ENUM,LNAS_CAUSE_NUMBER,ulCause);
            break;

    }

    return ;
}
/*****************************************************************************
 Function Name  : NAS_EMM_MsRegSsNmlSrvMsgRrcRelInd
 Discription    : sRegSsNmlSrv状态下，收到RRC_REL_IND消息
 Input          : None
 Output         : None
 Return         :
 History:
      1.  z00148421  2008-12.29  Draft Enact
      2.  X00148705  2009-09-30  重构
*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegSsNmlSrvMsgRrcRelInd(
                                                    VOS_UINT32 ulMsgId,
                                                    VOS_VOID *pMsgStru)
{
    LRRC_LMM_REL_IND_STRU        *pMsgRrcRelInd  =    (LRRC_LMM_REL_IND_STRU *)pMsgStru;
    VOS_UINT32                  ulCause;

    (VOS_VOID)ulMsgId;

    NAS_EMM_TAU_LOG_NORM("NAS_EMM_MsRegSsNmlSrvMsgRrcRelInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsNmlSrvMsgRrcRelInd_ENUM,LNAS_ENTRY);

    /*获得原因值*/
    ulCause                                    =    pMsgRrcRelInd->enRelCause;

    NAS_EMM_MsRegSsNmlSrvProcMsgRrcRelInd(          ulCause);

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsRegSsRegAttemptUpdateMmMsgRrcRelInd
 Description     : 状态REG+REG_ATTEMPTING_TO_UPDATE_MM收到RRC_MM_REL_IND消息
 Input           : ulMsgId-------------------------消息ID
                   pMsgStru------------------------消息指针
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2011-7-12     Draft Enact
    2.lihong 00150010     2011-11-17    Modify

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegSsRegAttemptUpdateMmMsgRrcRelInd
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    LRRC_LMM_REL_IND_STRU        *pMsgRrcRelInd  = (LRRC_LMM_REL_IND_STRU *)pMsgStru;

    (VOS_VOID)ulMsgId;

    NAS_EMM_TAU_LOG_NORM("NAS_EMM_MsRegSsRegAttemptUpdateMmMsgRrcRelInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgRrcRelInd_ENUM,LNAS_ENTRY);

    NAS_EMM_MsRegSsRegAttemptUpdateMmProcMsgRrcRelInd(pMsgRrcRelInd->enRelCause);

    return NAS_LMM_MSG_HANDLED;
}

/*******************************************************************************
  Module   :
  Function : NAS_EMM_MsRegSsNormalMsgT3411Exp
  Input    :
  Output   :
  NOTE     :
  Return   :
  History  :
    1.  Zhouyan 00125190  2008.09.10  新规作成
*******************************************************************************/
VOS_UINT32 NAS_EMM_MsRegSsNormalMsgT3411Exp(VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru )
{
    VOS_UINT32                          ulRslt  = NAS_EMM_FAIL;

    (VOS_VOID)ulMsgId;

    /* 打印进入该函数， INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO("NAS_EMM_MsRegSsNormalMsgT3411Exp is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsNormalMsgT3411Exp_ENUM,LNAS_ENTRY);

    ulRslt = NAS_EMM_TAU_CHKFSMStateMsgp(EMM_MS_REG,EMM_SS_REG_NORMAL_SERVICE,pMsgStru);

    /* 函数输入指针参数检查, 状态匹配检查,若不匹配,退出*/
    if(NAS_EMM_SUCC != ulRslt)
    {
        /* 打印异常 */
        NAS_EMM_TAU_LOG_WARN("NAS_EMM_MsRegSsNormalMsgT3411Exp ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsNormalMsgT3411Exp_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    /*调用消息处理函数*/
    /* 新增入参TAU发起原因 */
    NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_3411OR3402);

    return NAS_LMM_MSG_HANDLED;

}
/*******************************************************************************
  Module   : REG+ATTEMPT_TO_UPDATE_MM状态下收到T3411超时
  Function : NAS_EMM_MsRegSsRegAttemptUpdateMmMsgT3411Exp
  Input    :
  Output   :
  NOTE     :
  Return   :
  History  :
    1.  lihong00150010  2011.11.17  新规作成
*******************************************************************************/
VOS_UINT32 NAS_EMM_MsRegSsRegAttemptUpdateMmMsgT3411Exp
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    VOS_UINT32                          ulRslt  = NAS_EMM_FAIL;

    (VOS_VOID)ulMsgId;

    /* 打印进入该函数， INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO("NAS_EMM_MsRegSsRegAttemptUpdateMmMsgT3411Exp is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgT3411Exp_ENUM,LNAS_ENTRY);

    ulRslt = NAS_EMM_TAU_CHKFSMStateMsgp(EMM_MS_REG,EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM,pMsgStru);

    /* 函数输入指针参数检查, 状态匹配检查,若不匹配,退出*/
    if(NAS_EMM_SUCC != ulRslt)
    {
        /* 打印异常 */
        NAS_EMM_TAU_LOG_WARN("NAS_EMM_MsRegSsRegAttemptUpdateMmMsgT3411Exp ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgT3411Exp_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    /*NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_IMSI_ATTACH);*/
    NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);

    /*调用消息处理函数*/
    /* 新增入参TAU发起原因 */
    NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_3411OR3402);

    return NAS_LMM_MSG_HANDLED;

}

/*******************************************************************************
  Module   : REG+ATTEMPT_TO_UPDATE_MM状态下收到T3402时
  Function : NAS_EMM_MsRegSsRegAttemptUpdateMmMsgT3402Exp
  Input    :
  Output   :
  NOTE     :
  Return   :
  History  :
    1.  lihong00150010  2011.11.17  新规作成
*******************************************************************************/
VOS_UINT32 NAS_EMM_MsRegSsRegAttemptUpdateMmMsgT3402Exp
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    VOS_UINT32                                  ulRslt          = NAS_EMM_FAIL;

    (VOS_VOID)ulMsgId;

    /* 打印进入该函数， INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO( "NAS_EMM_MsRegSsRegAttemptUpdateMmMsgT3402Exp is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgT3402Exp_ENUM,LNAS_ENTRY);

    /* 函数输入指针参数检查, 状态匹配检查,若不匹配,退出*/
    ulRslt = NAS_EMM_TAU_CHKFSMStateMsgp(EMM_MS_REG,EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM,pMsgStru);
    if ( NAS_EMM_SUCC != ulRslt )
    {
        /* 打印异常 */
        NAS_EMM_TAU_LOG_WARN( "NAS_EMM_MsRegSsRegAttemptUpdateMmMsgT3402Exp ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgT3402Exp_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    /*NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_IMSI_ATTACH);*/
    NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);

    /*调用消息处理函数*/
    /* 新增入参TAU发起原因 */
    NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_3411OR3402);

    return NAS_LMM_MSG_HANDLED;

}
/*******************************************************************************
  Module   :
  Function : NAS_EMM_MsRegSsNormalMsgT3412Exp
  Input    :
  Output   :
  NOTE     :
  Return   :
  History  :
    1.  zhengjunyan 00148421  2008.12.29  新规作成
*******************************************************************************/
VOS_UINT32 NAS_EMM_MsRegSsNormalMsgT3412Exp(VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru )
{
    VOS_UINT32                          ulRslt  = NAS_EMM_FAIL;

    (VOS_VOID)ulMsgId;

    NAS_EMM_TAU_LOG_NORM("NAS_EMM_MsRegSsNormalMsgT3412Exp is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsNormalMsgT3412Exp_ENUM,LNAS_ENTRY);

    /* 函数输入指针参数检查, 状态匹配检查,若不匹配,退出*/
    ulRslt = NAS_EMM_TAU_CHKFSMStateMsgp(EMM_MS_REG,EMM_SS_REG_NORMAL_SERVICE,pMsgStru);
    if ( NAS_EMM_SUCC != ulRslt)
    {
        NAS_EMM_TAU_LOG_WARN("NAS_EMM_MsRegSsNormalMsgT3412Exp ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsNormalMsgT3412Exp_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    /* 触发周期性TAU
       注:Reg.Normal_Service状态下收到T3412Exp说明没有业务请求，不判断上行阻塞*/
    NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_T3412EXP);
    NAS_LMM_SetEmmInfoT3412ExpCtrl(NAS_EMM_T3412_EXP_YES_OTHER_STATE);

    /* 新增入参TAU发起原因 */
    NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_3412_EXP);
    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsRegSsRegAttemptUpdateMmMsgT3412Exp
 Description     : 状态REG+REG_ATTEMPTING_TO_UPDATE_MM收到3412超时消息
 Input           : ulMsgId-------------------------消息ID
                   pMsgStru------------------------消息指针
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong 00150010     2011-11-17     Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegSsRegAttemptUpdateMmMsgT3412Exp
(
    VOS_UINT32                              ulMsgId,
    VOS_VOID                               *pMsgStru
)
{
    VOS_UINT32                          ulRslt  = NAS_EMM_FAIL;

    (VOS_VOID)ulMsgId;

    NAS_EMM_TAU_LOG_NORM("NAS_EMM_MsRegSsRegAttemptUpdateMmMsgT3412Exp is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgT3412Exp_ENUM,LNAS_ENTRY);

    /* 函数输入指针参数检查, 状态匹配检查,若不匹配,退出*/
    ulRslt = NAS_EMM_TAU_CHKFSMStateMsgp(EMM_MS_REG,EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM,pMsgStru);
    if ( NAS_EMM_SUCC != ulRslt)
    {
        NAS_EMM_TAU_LOG_WARN("NAS_EMM_MsRegSsRegAttemptUpdateMmMsgT3412Exp ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgT3412Exp_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    /* 3412的时长一般情况下比3411和3402都长，因此此场景发生的概率很小，目前简化
       处理，不发起周期性TAU，而是直接发起联合TAU */
    /*NAS_EMM_TAU_SaveEmmTAUStartCause(     NAS_EMM_TAU_START_CAUSE_SYSINFO);*/
    NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
    NAS_LMM_SetEmmInfoT3412ExpCtrl(NAS_EMM_T3412_EXP_YES_OTHER_STATE);
    /* 新增入参TAU发起原因 */
    NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_3412_EXP);

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsSuspendSsAnyMsgT3412Exp
 Description     : 挂起过程中3412超时，只记录超时。
                   若系统变换回退，进入NO CELL后，收到系统消息时使用此标识；
                   若变换到GU去，清除此超时标识
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.HanLufeng 41410      2011-5-11  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsSuspendSsAnyMsgT3412Exp(
                                            VOS_UINT32  ulMsgId,
                                            VOS_VOID   *pMsgStru  )
{
    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;

    NAS_EMM_TAU_LOG_NORM("NAS_EMM_MsSuspendSsAnyMsgT3412Exp: entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsSuspendSsAnyMsgT3412Exp_ENUM,LNAS_ENTRY);


    /*  仿照如下设置赋值*/
    NAS_LMM_SetEmmInfoT3412ExpCtrl(NAS_EMM_T3412_EXP_YES_OTHER_STATE);
    return NAS_LMM_MSG_HANDLED;
}


/*******************************************************************************
  Module   :
  Function : NAS_EMM_MsRegSsAtpUpdataMsgSysinfo
  Input    :
  Output   :
  NOTE     :
  Return   :
  History  :
    1.  Zhouyan 00125190  2008.09.10  新规作成
    2.  zhengjunyan 00148421 2011-02-15 DTS2011021401149
    3.  liuhua      00212067 2012-05-29 当收到小区被禁消息后，不需要停止T3411, T3402
    4.  sunjitan 00193151    2012-07-10 modify: Last attempt reg TA 维护
    5.  lihong 00150010      2012-12-19 Modify:Emergency
*******************************************************************************/
VOS_UINT32 NAS_EMM_MsRegSsAtpUpdataMsgSysinfo(VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru )
{
    VOS_UINT32                          ulRslt            = NAS_EMM_FAIL;
    EMMC_EMM_SYS_INFO_IND_STRU         *pstsysinfo        = NAS_EMM_NULL_PTR;
    NAS_LMM_PTL_TI_ENUM_UINT16          enPtlTimerId    = NAS_LMM_PTL_TI_BUTT;
    MMC_LMM_TAU_RSLT_ENUM_UINT32        ulTauRslt;


    pstsysinfo                          = (EMMC_EMM_SYS_INFO_IND_STRU*)pMsgStru;

    (VOS_VOID)ulMsgId;

    /* 打印进入该函数， INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO("Nas_Emm_MsRegSsAtpUpdataMsgSysinfo is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsAtpUpdataMsgSysinfo_ENUM,LNAS_ENTRY);

    ulRslt = NAS_EMM_TAU_CHKFSMStateMsgp(EMM_MS_REG,EMM_SS_REG_ATTEMPTING_TO_UPDATE,pMsgStru);

    /* 函数输入指针参数检查, 状态匹配检查,若不匹配,退出*/
    if ( NAS_EMM_SUCC != ulRslt)
    {
        /* 打印异常 */
        NAS_EMM_TAU_LOG_WARN("NAS_EMM_MsRegSsAtpUpdataMsgSysinfo ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsAtpUpdataMsgSysinfo_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }
    /*根据禁止信息判断是否处理当前的系统消息*/
    if ((NAS_LMM_REG_STATUS_NORM_REGED == NAS_LMM_GetEmmInfoRegStatus())
        && ((EMMC_EMM_NO_FORBIDDEN != pstsysinfo->ulForbiddenInfo)
            || (EMMC_EMM_CELL_STATUS_ANYCELL == pstsysinfo->ulCellStatus)))
    {
        NAS_EMM_SetTauTypeNoProcedure();

        /*转换EMM状态机*/
        NAS_EMM_TAUSER_FSMTranState(    EMM_MS_REG,
                                        EMM_SS_REG_LIMITED_SERVICE,
                                        TI_NAS_EMM_STATE_NO_TIMER);

        /*向MMC发送LMM_MMC_TAU_RESULT_IND消息*/
        NAS_EMM_MmcSendTauActionResultIndForbType((VOS_VOID*)&pstsysinfo->ulForbiddenInfo);


        return NAS_LMM_MSG_HANDLED;
    }
#if(FEATURE_ON == FEATURE_CSG)
    if(NAS_EMM_YES == NAS_EMM_MsRegSsAtpUpdataIsCsgIdNotInListTauStart())
    {
        return NAS_LMM_MSG_HANDLED;
    }
#endif

    /* 如果当前TA在TAI LIST */
    if (NAS_EMM_SUCC == NAS_EMM_TAU_IsCurrentTAInTaList())
    {
        /* 如果有定时器(保护作用，正常一定有) */
        if (NAS_EMM_YES == NAS_EMM_IsT3411orT3402Running(&enPtlTimerId))
        {
            /* 当前TA与上次尝试发起注册或TAU的TA等效，等超时 */
            if (NAS_EMM_YES == NAS_LMM_IsLastAttemptRegTaInTaiList())
            {
                NAS_EMM_TAU_LOG_NORM("NAS_EMM_MsRegSsAtpUpdataMsgSysinfo: Equivalent TA, wait timer expired.");
                TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsAtpUpdataMsgSysinfo_ENUM,LNAS_FUNCTION_LABEL1);

                /* 若之前有过因RRC_REL导致的TAU_REQ发送失败的情况，那么此时应发起TAU */
                if(PS_TRUE == NAS_LMM_GetTauReqSndFailFlag())
                {
                     TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegSsAtpUpdataMsgSysinfo_ENUM,LNAS_FUNCTION_LABEL2);

                     /* 新增入参TAU发起原因 */
                     NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_SND_MSG_FAIL);

                     return NAS_LMM_MSG_HANDLED;
                }

                /* 网络信息更新,MMA不会立即更新网络信息,需要收到TAU IND才会更新,为规避该问题,
                   LMM构造一条不带任何参数TAU IND消息上报给MMC */
                /* 在UE收到MMC发来的系统消息之后，若要发起attach或tau流程，按照原有流程处理；若有T3411或T3402在run，那么给MMC上报TAU结果的假消息 */
                /* 有定时器是3402在运行, 需上报TAU结果 */
                if ( TI_NAS_EMM_PTL_T3402 == enPtlTimerId )
                {
                    NAS_EMM_SetTauTypeNoProcedure();

                    ulTauRslt = MMC_LMM_TAU_RSLT_T3402_RUNNING;
                    NAS_EMM_MmcSendTauActionResultIndOthertype((VOS_VOID*)&ulTauRslt);

                }
                /* 有定时器是3411在运行, 需上报TAU结果 */
                if ( TI_NAS_EMM_PTL_T3411 == enPtlTimerId )
                {
                    NAS_EMM_SetTauTypeNoProcedure();

                    ulTauRslt = MMC_LMM_TAU_RSLT_FAILURE;
                    NAS_EMM_MmcSendTauActionResultIndOthertype((VOS_VOID*)&ulTauRslt);
                }
                return NAS_LMM_MSG_HANDLED;
            }
        }

        /* 非等效TA，或者没定时器，都立即发起TAU */
        /* 重置TAU计数 */
        NAS_EMM_TAU_SaveEmmTAUAttemptCnt(NAS_EMM_TAU_ATTEMPT_CNT_ZERO);
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);

        /*启动TAU Procedure*/
        /* 新增入参TAU发起原因 */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_LAST_ATTEMPT_TA_NOT_IN_TAI_LIST);

    }
    else /* 当前TA不在TAI LIST */
    {
        NAS_EMM_MsRegSsAtpUpdataTaIsNotListProc();

    }

    return NAS_LMM_MSG_HANDLED;

}

/*******************************************************************************
  Module   :
  Function : NAS_EMM_MsRegSsAtpUpdataMsgT3411Exp
  Input    :
  Output   :
  NOTE     :
  Return   :
  History  :
    1.  Zhouyan 00125190  2008.09.10  新规作成
*******************************************************************************/
VOS_UINT32 NAS_EMM_MsRegSsAtpUpdataMsgT3411Exp(VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru
                               )
{
    VOS_UINT32                                  ulRslt          = NAS_EMM_FAIL;


    (VOS_VOID)ulMsgId;

    /* 打印进入该函数， INFO_LEVEL */
    NAS_EMM_TAU_LOG_NORM("Nas_Emm_MsRegSsAtpUpdataMsgT3411Exp is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsAtpUpdataMsgT3411Exp_ENUM,LNAS_ENTRY);

    /* 函数输入指针参数检查, 状态匹配检查,若不匹配,退出*/
    ulRslt = NAS_EMM_TAU_CHKFSMStateMsgp(EMM_MS_REG,EMM_SS_REG_ATTEMPTING_TO_UPDATE,pMsgStru);
    if ( NAS_EMM_SUCC != ulRslt )
    {
        /* 打印异常 */
        NAS_EMM_TAU_LOG_WARN( "NAS_EMM_TAUSER_CHKFSMStateMsgp ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsAtpUpdataMsgT3411Exp_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    /*重新发起TAU*/
    /* 新增入参TAU发起原因 */
    NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_3411OR3402);

    return NAS_LMM_MSG_HANDLED;

}

/*******************************************************************************
  Module   :
  Function : NAS_EMM_MsRegSsAtpUpdataMsgT3402Exp
  Input    :
  Output   :
  NOTE     :
  Return   :
  History  :
    1.  Zhouyan 00125190  2008.09.10  新规作成
*******************************************************************************/
VOS_UINT32 NAS_EMM_MsRegSsAtpUpdataMsgT3402Exp(VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru
                               )
{
    VOS_UINT32                                  ulRslt          = NAS_EMM_FAIL;

    (VOS_VOID)ulMsgId;

    /* 打印进入该函数， INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO( "Nas_Emm_MsRegSsAtpUpdataMsgT3402Exp is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsAtpUpdataMsgT3402Exp_ENUM,LNAS_ENTRY);

    /* 函数输入指针参数检查, 状态匹配检查,若不匹配,退出*/
    ulRslt = NAS_EMM_TAU_CHKFSMStateMsgp(EMM_MS_REG,EMM_SS_REG_ATTEMPTING_TO_UPDATE,pMsgStru);
    if ( NAS_EMM_SUCC != ulRslt )
    {
        /* 打印异常 */
        NAS_EMM_TAU_LOG_WARN( "NAS_EMM_TAUSER_CHKFSMStateMsgp ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsAtpUpdataMsgT3402Exp_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    /*调用消息处理函数*/
    /* 新增入参TAU发起原因 */
    NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_3411OR3402);

    return NAS_LMM_MSG_HANDLED;

}

/*******************************************************************************
  Module   :
  Function : NAS_EMM_MsRegSsAtpUpdataMsgT3346Exp
  Input    :
  Output   :
  NOTE     :
  Return   :
  History  :
    1.  wangchen 00209181   2015-02-10  新规作成
*******************************************************************************/
VOS_UINT32 NAS_EMM_MsRegSsAtpUpdataMsgT3346Exp
(
    VOS_UINT32  ulMsgId,
    VOS_VOID   *pMsgStru
)
{
    VOS_UINT32                                  ulRslt          = NAS_EMM_FAIL;

    (VOS_VOID)ulMsgId;

    /* 打印进入该函数， INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO( "NAS_EMM_MsRegSsAtpUpdataMsgT3346Exp is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsAtpUpdataMsgT3346Exp_ENUM,LNAS_ENTRY);

    /* 函数输入指针参数检查, 状态匹配检查,若不匹配,退出*/
    ulRslt = NAS_EMM_TAU_CHKFSMStateMsgp(EMM_MS_REG,EMM_SS_REG_ATTEMPTING_TO_UPDATE,pMsgStru);
    if ( NAS_EMM_SUCC != ulRslt )
    {
        /* 打印异常 */
        NAS_EMM_TAU_LOG_WARN( "NAS_EMM_TAUSER_CHKFSMStateMsgp ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsAtpUpdataMsgT3346Exp_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    /*调用消息处理函数*/
    /* 新增入参TAU发起原因 */
    NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_3346);

    return NAS_LMM_MSG_HANDLED;

}

/*******************************************************************************
  Module   :
  Function : NAS_EMM_MsRegSsSomeStateMsgEsmDataReq
  Input    : ulMsgId--------------------消息ID
             pMsgStru-------------------消息指针
  Output   : None
  NOTE     : REG+ATTEMPT_TO_UPDATE和REG+WAIT_ACCESS_GRANT_IND状态下收到ESM消息
  Return   : VOS_UINT32
  History  :
    1.  lihong 00150010  2012.12.13  新规作成
*******************************************************************************/
VOS_UINT32 NAS_EMM_MsRegSsSomeStateMsgEsmDataReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    VOS_UINT32                          ulRslt1          = NAS_EMM_FAIL;
    VOS_UINT32                          ulRslt2          = NAS_EMM_FAIL;

    EMM_ESM_DATA_REQ_STRU              *pstEsmDataReq   = (EMM_ESM_DATA_REQ_STRU*)pMsgStru;

    (VOS_VOID)ulMsgId;

    /* 打印进入该函数， INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO( "NAS_EMM_MsRegSsSomeStateMsgEsmDataReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsSomeStateMsgEsmDataReq_ENUM,LNAS_ENTRY);

/* 此处因多处调用不能只用一个检查状态 */
    /* 函数输入指针参数检查, 状态匹配检查,若不匹配,退出*/
    ulRslt1 = NAS_EMM_TAU_CHKFSMStateMsgp(EMM_MS_REG,EMM_SS_REG_ATTEMPTING_TO_UPDATE,pMsgStru);
    ulRslt2 = NAS_EMM_TAU_CHKFSMStateMsgp(EMM_MS_REG,EMM_SS_REG_WAIT_ACCESS_GRANT_IND,pMsgStru);

    if (( NAS_EMM_SUCC != ulRslt1 ) && ( NAS_EMM_SUCC != ulRslt2 ))
    {
        /* 打印异常 */
        NAS_EMM_TAU_LOG_WARN( "NAS_EMM_MsRegSsAtpUpdataMsgEsmDataReq ERROR !");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsSomeStateMsgEsmDataReq_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    /* 如果不是紧急类型，则丢弃 */
    if (VOS_TRUE != pstEsmDataReq->ulIsEmcType)
    {
        NAS_EMM_TAU_LOG_NORM( "NAS_EMM_MsRegSsSomeStateMsgEsmDataReq:NOT EMC!");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsSomeStateMsgEsmDataReq_ENUM,LNAS_FUNCTION_LABEL1);
        return  NAS_LMM_MSG_DISCARD;
    }

    NAS_LMM_SetEmmInfoIsEmerPndEsting(VOS_TRUE);

    /* 解决LRRC REL搜小区驻留上报系统消息前收到ESM紧急承载建立请求，由于空口发送失败，本地detach,发起紧急ATTACH问题
       方案:先高优先级缓存，等到收到LRRC系统消息后处理*/
    if((NAS_EMM_CONN_WAIT_SYS_INFO == NAS_EMM_GetConnState())
        ||(NAS_EMM_CONN_RELEASING == NAS_EMM_GetConnState()))
    {
        return NAS_LMM_STORE_HIGH_PRIO_MSG;
    }

    /* 缓存紧急类型的ESM消息 */
    NAS_EMM_SaveEmcEsmMsg(pMsgStru);

    NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_ESM_EMC_PDN_REQ);

    /*调用消息处理函数*/
    /* 新增入参TAU发起原因 */
    NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_EMC_PDN_EST_REQ);

    return NAS_LMM_MSG_HANDLED;
}

/*******************************************************************************
  Module   :
  Function : NAS_EMM_MsRegSsLimitSRMsgSysinfo
  Input    :
  Output   :
  NOTE     :
  Return   :
  History  :
    1.Zhouyan     00125190  2008.09.10  新规作成
    2.zhengjunyan 00148421  2009.08.13  BJ9D01691:不再判断TAI List
    3.X00148705             2009.11.17  依据TAU的启动原因值发起不同类型的TAU
    4.z00148421             2009.09.15  优化:通过判断TA是否在TAI List中,
                                        UeNeCapOrDrxChange标志和T3412超时标志，
                                        减少多余触发TAU，并保证TAU类型正确。
    5.z00148421             2010-12-23   DTS2010111701490:修改DrxNetCapChange的处理
                                        根据TauStartCause触发TAU
    6.z00148421             2011-01-11   DTS2010122201496
    7.l00150010             2012-12-19   Modify:Emergency
*******************************************************************************/
VOS_UINT32 NAS_EMM_MsRegSsLimitSRMsgSysinfo(VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru )
{
    VOS_UINT32                          ulRslt          = NAS_EMM_FAIL;
    EMMC_EMM_SYS_INFO_IND_STRU         *pstsysinfo      = VOS_NULL_PTR;

    (VOS_VOID)ulMsgId;
    NAS_EMM_TAU_LOG_INFO("NAS_EMM_MsRegSsLimitSRMsgSysinfo entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsLimitSRMsgSysinfo_ENUM,LNAS_ENTRY);

    /* 函数输入指针参数检查, 状态匹配检查,若不匹配,退出*/
    ulRslt = NAS_EMM_TAU_CHKFSMStateMsgp(EMM_MS_REG,EMM_SS_REG_LIMITED_SERVICE,pMsgStru);
    if (NAS_EMM_SUCC != ulRslt )
    {
        NAS_EMM_TAU_LOG_WARN("NAS_EMM_MsRegSsLimitSRMsgSysinfo:INPUT ERROR.");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsLimitSRMsgSysinfo_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    /* 获取系统消息*/
    pstsysinfo                          = (EMMC_EMM_SYS_INFO_IND_STRU*)pMsgStru;
    /* 如果系统消息被禁，状态不变，函数返回*/
    if ((NAS_LMM_REG_STATUS_NORM_REGED == NAS_LMM_GetEmmInfoRegStatus())
        && ((EMMC_EMM_NO_FORBIDDEN != pstsysinfo->ulForbiddenInfo)
            || (EMMC_EMM_CELL_STATUS_ANYCELL == pstsysinfo->ulCellStatus)))
    {
        NAS_EMM_TAU_LOG_WARN("NAS_EMM_MsRegSsLimitSRMsgSysinfo:Cell Forb.");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsLimitSRMsgSysinfo_ENUM,LNAS_EMM_FORBIDDEN);

        NAS_EMM_SetTauTypeNoProcedure();

        /*向MMC发送LMM_MMC_TAU_RESULT_IND消息*/
        NAS_EMM_MmcSendTauActionResultIndForbType((VOS_VOID*)&pstsysinfo->ulForbiddenInfo);

        return NAS_LMM_MSG_HANDLED;
    }

    /* 进入收到SYS_INFO的公共处理*/
    NAS_EMM_RegSomeStateMsgSysInfoCommProc();

    return NAS_LMM_MSG_HANDLED;
}

/*******************************************************************************
  Module   :
  Function : NAS_EMM_MsRegSsPLMNSearchMsgSysinfo
  Input    :
  Output   :
  NOTE     :
  Return   :
  History  :
    1.  Zhouyan 00125190  2008.09.10  新规作成
    2.  leili   00132387  2009.06.16  问题单BJ9D00875修改
    3.  X00148705         2009-11-13  修改TAU类型和DRXNetCap改变时发起TAU
    4.  z00148421         2010-07-30  用TauStartCause代替EU作为判断条件
    5.  z00148421         2010-09-15  1)将更新LVR TAI移到不触发TAU的位置
                                      2)调整TAUStartCause和DrxNetCapChange两个
                                        条件的判断顺序
    6.  z00148421         2010-12-23   DTS2010111701490:修改DrxNetCapChange的处理
                                       根据TauStartCause触发TAU
    7.  z00148421         2011-02-14   DTS2011021401149
    8.  sunjitan 00193151 2012-02-02 Modify for UE radio capability
    9.  l00150010         2012-12-19   Modify:Emergency
*******************************************************************************/
VOS_UINT32 NAS_EMM_MsRegSsPLMNSearchMsgSysinfo(VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru )
{
    VOS_UINT32                          ulRslt          = NAS_EMM_FAIL;
    EMMC_EMM_SYS_INFO_IND_STRU         *pstsysinfo      = NAS_EMM_NULL_PTR;

    (VOS_VOID)ulMsgId;
    NAS_EMM_TAU_LOG_INFO(               "Nas_Emm_MsRegSsPLMNSearchMsgSysinfo is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsPLMNSearchMsgSysinfo_ENUM,LNAS_ENTRY);

    /* 函数输入指针参数检查, 状态匹配检查,若不匹配,退出*/
    ulRslt = NAS_EMM_TAU_CHKFSMStateMsgp(EMM_MS_REG,EMM_SS_REG_PLMN_SEARCH,pMsgStru);
    if ( NAS_EMM_SUCC                   != ulRslt )
    {
        NAS_EMM_TAU_LOG_WARN(           "Nas_Emm_MsRegSsPLMNSearchMsgSysinfo ERROR.");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsPLMNSearchMsgSysinfo_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    /*获取系统消息和网络信息*/
    pstsysinfo                          = (EMMC_EMM_SYS_INFO_IND_STRU*)pMsgStru;
    /*如果收到的系统消息被禁，状态迁移到Reg.Limite_Service，函数返回*/
    if ((NAS_LMM_REG_STATUS_NORM_REGED == NAS_LMM_GetEmmInfoRegStatus())
        && ((EMMC_EMM_NO_FORBIDDEN != pstsysinfo->ulForbiddenInfo)
            || (EMMC_EMM_CELL_STATUS_ANYCELL == pstsysinfo->ulCellStatus)))
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_MsRegSsPLMNSearchMsgSysinfo:SysInfo Forb.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsPLMNSearchMsgSysinfo_ENUM,LNAS_EMM_FORBIDDEN);

        NAS_EMM_SetTauTypeNoProcedure();

        NAS_EMM_TAUSER_FSMTranState(    EMM_MS_REG,
                                        EMM_SS_REG_LIMITED_SERVICE,
                                        TI_NAS_EMM_STATE_NO_TIMER);

        /*向MMC发送LMM_MMC_TAU_RESULT_IND消息*/
        NAS_EMM_MmcSendTauActionResultIndForbType((VOS_VOID*)&pstsysinfo->ulForbiddenInfo);


        return NAS_LMM_MSG_HANDLED;
    }

    NAS_EMM_RegSomeStateMsgSysInfoCommProc();

    return NAS_LMM_MSG_HANDLED;
}

/*******************************************************************************
  Module   :
  Function : NAS_EMM_MsRegSsNocellMsgSysinfo
  Input    :
  Output   :
  NOTE     :
  Return   :
  History  :
    1.  Zhouyan 00125190  2008.09.10  新规作成
    2.  luojian 00107747  2009.01.13  协议更新到8.0.0
    3.  yangfan 00159566  2009.09.01  修改
    4.  X00148705         2009.11.13  修改TAU的消息类型
    5.  z00148421         2010-12-23  DTS2010111701490:修改DrxNetCapChange的处理
                                      根据TauStartCause触发TAU
    6.  z00148421         2011-12-22  添加异常保护分支:挂起态下不处理SYS_INFO
    7.  l00150010         2012-12-19   Modify:Emergency
*******************************************************************************/
VOS_UINT32 NAS_EMM_MsRegSsNocellMsgSysinfo(VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru )
{

    VOS_UINT32  ulRslt                            = NAS_EMM_FAIL;
    EMMC_EMM_SYS_INFO_IND_STRU   *pstsysinfo       = NAS_EMM_NULL_PTR;

    (VOS_VOID)ulMsgId;
    NAS_EMM_TAU_LOG_INFO(                         "Nas_Emm_MsRegSsNocellMsgSysinfo is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsNocellMsgSysinfo_ENUM,LNAS_ENTRY);

    /*check the input params*/
    ulRslt = NAS_EMM_TAU_CHKFSMStateMsgp(         EMM_MS_REG,EMM_SS_REG_NO_CELL_AVAILABLE,pMsgStru);
    if( NAS_EMM_SUCC                              != ulRslt )
    {
        NAS_EMM_TAU_LOG_WARN(                     "NAS_EMM_TAUSER_CHKFSMStateMsgp ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsNocellMsgSysinfo_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    /* 如果当前处于挂起态，则不处理SYS_INFO,直接丢弃*/
    if(NAS_LMM_CUR_LTE_SUSPEND == NAS_EMM_GetCurLteState())
    {
        NAS_EMM_TAU_LOG_ERR("Nas_Emm_MsRegSsNocellMsgSysinfo:LTE SUSPEND.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegSsNocellMsgSysinfo_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_LMM_MSG_HANDLED;
    }

    /* 获取系统消息和网络信息*/
    pstsysinfo                                    = (EMMC_EMM_SYS_INFO_IND_STRU*)pMsgStru;

    /*根据禁止信息判断是否处理当前的系统消息*/
    if ((NAS_LMM_REG_STATUS_NORM_REGED == NAS_LMM_GetEmmInfoRegStatus())
        && ((EMMC_EMM_NO_FORBIDDEN != pstsysinfo->ulForbiddenInfo)
            || (EMMC_EMM_CELL_STATUS_ANYCELL == pstsysinfo->ulCellStatus)))
    {
        NAS_EMM_TAU_LOG_WARN("NAS_EMM_MsRegSsNocellMsgSysinfo:Cell Forb.");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsNocellMsgSysinfo_ENUM,LNAS_EMM_FORBIDDEN);

        NAS_EMM_SetTauTypeNoProcedure();

        /*转换EMM状态机*/
        NAS_EMM_TAUSER_FSMTranState(    EMM_MS_REG,
                                        EMM_SS_REG_LIMITED_SERVICE,
                                        TI_NAS_EMM_STATE_NO_TIMER);

        /*向MMC发送LMM_MMC_TAU_RESULT_IND消息*/
        NAS_EMM_MmcSendTauActionResultIndForbType((VOS_VOID*)&pstsysinfo->ulForbiddenInfo);

        return NAS_LMM_MSG_HANDLED;
    }
    /*inform ESM that return to E-UTRAN*/
    NAS_EMM_TAU_SendEsmStatusInd(       EMM_ESM_ATTACH_STATUS_AREA_RE_ENTRY);

    /* 进入收到SYS_INFO的公共处理*/
    NAS_EMM_RegSomeStateMsgSysInfoCommProc();

    return NAS_LMM_MSG_HANDLED;
}


/*******************************************************************************
  Module   :
  Function : NAS_EMM_MsRegSsNormalCsfbDelayProc
  Input    : VOS_VOID
  Output   : VOS_VOID
  NOTE     :
  Return   : VOS_VOID
  History  :
    1.  sunjitan 00193151    2014-05-15  新规作成
    2.  leixiantiao 00258641 2015-07-02  新增入参
    3.  leixiantiao 00258641   2015-07-09  fix DTS2015062509266
*******************************************************************************/
VOS_VOID NAS_EMM_MsRegSsNormalCsfbDelayProc(EMMC_EMM_CHANGE_INFO_ENUM_UINT32    ulChangeInfo)
{

    /* 打印进入该函数， INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO("NAS_EMM_MsRegSsNormalCsfbDelayProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsNormalCsfbDelayProc_ENUM,LNAS_ENTRY);
    /* 增加入参,用于判断小区信息是否发生改变 */
    NAS_EMM_RegNormalServiceOrUpdateMMMsgSysInfoCommProc(ulChangeInfo);

    /* 保持NORMAL态不变的情况 */
    /* 如果当前CSFB延时定时器在运行，说明之前在释放过程中收到过CSFB，
       这种情况下直接发起EXTEND SERVICE */
    if((EMM_MS_REG == NAS_LMM_GetEmmCurFsmMS())
        &&(EMM_SS_REG_NORMAL_SERVICE ==NAS_LMM_GetEmmCurFsmSS()))
    {
        /* 设置UE接受CSFB */
        NAS_EMM_SER_SaveEmmSerCsfbRsp(NAS_EMM_CSFB_RSP_ACCEPTED_BY_UE);

        /*启动定时器3417*/
        NAS_LMM_StartStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417_EXT);

        /*转换EMM状态机MS_SER_INIT+SS_SER_WAIT_CN_CNF*/
        NAS_EMM_TAUSER_FSMTranState(EMM_MS_SER_INIT, EMM_SS_SER_WAIT_CN_SER_CNF, TI_NAS_EMM_STATE_SERVICE_T3417_EXT);

        /* ESR空口发送前,通知LRRC CSFB流程INIT,LRRC置一个全局变量,当ESR发送时发生重建,直接回LMM REL,搜网去GU */
        NAS_EMM_SndLrrcLmmCsfbNotify(LRRC_LNAS_CSFB_STATUS_INIT);

        /*组合并发送MRRC_DATA_REQ(SERVICE_REQ)*/
        NAS_EMM_SER_SendMrrcDataReq_ExtendedServiceReq();

        /* 清除之前记录的SERVICE冲突 */
        NAS_EMM_TAU_SaveEmmCollisionCtrl(NAS_EMM_COLLISION_NONE);
    }
    /* 如果状态不再是REG NORMAL，说明发起了TAU或其他流程，完成其它流程再解决冲突 */

    return;

}



VOS_VOID  NAS_EMM_ProcTauBar( VOS_VOID )
{
    /* 检查BarType，如果全部解除，则迁移到REG.NORMAL_SERVICE*/
    if(0 == (NAS_EMM_TAU_GetRegBarType()&NAS_LMM_LOW_HALF_BYTE_F))
    {
        /*清空BarProcedure*/
        NAS_EMM_TAU_SetRegBarProcedure(NAS_EMM_BAR_PROCEDURE_NULL);
        NAS_EMM_TranStatePsNormalServiceOrPsLimitService();

        /*转换EMM状态机Reg Normal态*/
        /*NAS_EMM_TAUSER_FSMTranState(EMM_MS_REG, EMM_SS_REG_NORMAL_SERVICE, TI_NAS_EMM_STATE_NO_TIMER);*/
    }

    /*如果MO Signal没有被bar，则发起TAU*/
    if( NAS_EMM_SUCC != NAS_EMM_JudgeBarType(NAS_EMM_BAR_TYPE_MO_SIGNAL))
    {
        /* 判断是否存在上行Pending*/
        NAS_EMM_TAU_IsUplinkPending();

        NAS_EMM_RegSomeStateMsgSysInfoCommProc();
    }
}


/*****************************************************************************
 Function Name   : NAS_EMM_SrvBarIsTauStarted
 Description     : Service流程被Bar,收到Grant_Ind消息，判断如果需要则触发携带
                   'ACTIVE'的TAU
                   触发了TAU,返回 NAS_EMM_YES
                   没有触发TAU,则返回 NAS_EMM_NO
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-12-14  Draft Enact
    2.zhengjunyan 00148421      2011-1-12   DTS2010122201496
    3.zhengjunyan 00148421      2011-2-15   DTS2011021501149
*****************************************************************************/
VOS_UINT32  NAS_EMM_SrvBarIsTauStarted( VOS_VOID)
{
    /*如果Mo_Signal允许接入，判断是否需要触发TAU*/
    if(NAS_EMM_SUCC != NAS_EMM_JudgeBarType(NAS_EMM_BAR_TYPE_MO_SIGNAL))
    {
        /* 判断是否存在上行Pending*/
        NAS_EMM_TAU_IsUplinkPending();

        if (NAS_EMM_SER_START_CAUSE_MO_CSFB_REQ == NAS_EMM_SER_GetEmmSERStartCause())
        {
            NAS_EMM_TAU_SaveEmmCollisionCtrl(NAS_EMM_COLLISION_SERVICE);
        }

        /*判断是否需要发起TAU或者本地Detach*/
        NAS_EMM_RegSomeStateMsgSysInfoCommProc();

        if (EMM_MS_REG == NAS_LMM_GetEmmCurFsmMS())
        {
            NAS_EMM_TAU_SaveEmmCollisionCtrl(NAS_EMM_COLLISION_NONE);
            return NAS_EMM_NO;
        }
        else
        {
            /* 如果需要发起TAU或者无线能力变更引起的本地Detach后重新Attach,则返回NAS_EMM_YES */
            return NAS_EMM_YES;
        }
    }
    return NAS_EMM_NO;

}

/*****************************************************************************
 Function Name   : NAS_EMM_ProcSrvBar
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.    leili  00132387      2010-8-24  Draft Enact
    2.    sunbing 49683        2010-11-16 Service流程解bar后，判断是否有TAU流程需要执行
    3.    zhengjunyan 00148421 2010-11-23 MOD:重新触发TAU时携带'ACTIVE'标志，且要
                                              区分TauStartCause
    4.    lihong00150010       2012-12-18 Modify:Emergency
    5.    leixiantiao 00258641 2015-07-09 fix DTS2015062509266
*****************************************************************************/
VOS_VOID  NAS_EMM_ProcSrvBar( VOS_VOID )
{
    VOS_UINT32                          ulRslt;
    /* 检查BarType，如果全部解除，则迁移到REG.NORMAL_SERVICE*/
    if(0 == (NAS_EMM_TAU_GetRegBarType()&NAS_LMM_LOW_HALF_BYTE_F))
    {
        /*清空BarProcedure*/
        NAS_EMM_TAU_SetRegBarProcedure(NAS_EMM_BAR_PROCEDURE_NULL);
        NAS_EMM_TranStatePsNormalServiceOrPsLimitService();

        /*转换EMM状态机Reg Normal态*/
        /*NAS_EMM_TAUSER_FSMTranState(EMM_MS_REG, EMM_SS_REG_NORMAL_SERVICE, TI_NAS_EMM_STATE_NO_TIMER);*/
    }

    /*判断如果需要则触发携带'active'的TAU流程，函数返回，否则继续*/
    ulRslt = NAS_EMM_SrvBarIsTauStarted();
    if(NAS_EMM_YES == ulRslt)
    {
        return;
    }
    /*如果MT call被bar，并且Service目的响应寻呼，则发起Service流程*/
    if( (NAS_EMM_SUCC != NAS_EMM_JudgeBarType(NAS_EMM_BAR_TYPE_MT))
       && (NAS_EMM_SER_START_CAUSE_RRC_PAGING == NAS_EMM_SER_GetEmmSERStartCause())
       && (VOS_TRUE != NAS_EMM_IsEnterRegLimitService()))
    {
        /*触发Service流程*/
        NAS_EMM_SER_RcvRrcStmsiPagingInd();
        return;
    }

    /*如果MT call不被bar，并且EXTENDED Service目的响应寻呼，则发起EXTENDED Service流程*/
    if( (NAS_EMM_SUCC != NAS_EMM_JudgeBarType(NAS_EMM_BAR_TYPE_MT))
       &&(NAS_EMM_SER_START_CAUSE_MT_CSFB_REQ == NAS_EMM_SER_GetEmmSERStartCause()))
    {
        /* 设置UE接受CSFB */
        NAS_EMM_SER_SaveEmmSerCsfbRsp(NAS_EMM_CSFB_RSP_ACCEPTED_BY_UE);

        /*启动定时器3417*/
        NAS_LMM_StartStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417_EXT);

        /*转换EMM状态机MS_SER_INIT+SS_SER_WAIT_CN_CNF*/
        NAS_EMM_TAUSER_FSMTranState(EMM_MS_SER_INIT, EMM_SS_SER_WAIT_CN_SER_CNF, TI_NAS_EMM_STATE_SERVICE_T3417_EXT);

        /* ESR空口发送前,通知LRRC CSFB流程INIT,LRRC置一个全局变量,当ESR发送时发生重建,直接回LMM REL,搜网去GU */

        NAS_EMM_SndLrrcLmmCsfbNotify(LRRC_LNAS_CSFB_STATUS_INIT);

        /*组合并发送MRRC_DATA_REQ(SERVICE_REQ)*/
        NAS_EMM_SER_SendMrrcDataReq_ExtendedServiceReq();
        return;
    }

     /*如果MO csfb不被bar，并且CSFB没有abort，则发起Service流程*/
    if ( (NAS_EMM_SUCC != NAS_EMM_JudgeBarType(NAS_EMM_BAR_TYPE_MO_CSFB))
       &&(NAS_EMM_SER_START_CAUSE_MO_CSFB_REQ == NAS_EMM_SER_GetEmmSERStartCause())
       && (NAS_EMM_CSFB_ABORT_FLAG_VALID != NAS_EMM_SER_GetEmmSerCsfbAbortFlag()))
    {
        /*启动定时器3417*/
        NAS_LMM_StartStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417_EXT);

        /*转换EMM状态机MS_SER_INIT+SS_SER_WAIT_CN_CNF*/
        NAS_EMM_TAUSER_FSMTranState(EMM_MS_SER_INIT, EMM_SS_SER_WAIT_CN_SER_CNF, TI_NAS_EMM_STATE_SERVICE_T3417_EXT);

        /* ESR空口发送前,通知LRRC CSFB流程INIT,LRRC置一个全局变量,当ESR发送时发生重建,直接回LMM REL,搜网去GU */

        NAS_EMM_SndLrrcLmmCsfbNotify(LRRC_LNAS_CSFB_STATUS_INIT);

        /*组合并发送MRRC_DATA_REQ(SERVICE_REQ)*/
        NAS_EMM_SER_SendMrrcDataReq_ExtendedServiceReq();
    }
    return;
}



VOS_UINT32 NAS_EMM_MsRegSsWaitAccessGrantIndMsgRrcGrantInd(VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru)
 {
    VOS_UINT32                              ulRslt;

    LRRC_LMM_ACCESS_GRANT_IND_STRU            *pRrcMmGrantInd = NAS_EMM_NULL_PTR;

    (VOS_VOID)ulMsgId;

    NAS_EMM_TAU_LOG_INFO("NAS_EMM_MsRegSsWaitAccessGrantIndMsgRrcGrantInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsWaitAccessGrantIndMsgRrcGrantInd_ENUM,LNAS_ENTRY);

    /*check the input params and states*/
    ulRslt = NAS_EMM_TAU_CHKFSMStateMsgp(EMM_MS_REG,EMM_SS_REG_WAIT_ACCESS_GRANT_IND,pMsgStru);
    if ( NAS_EMM_SUCC != ulRslt )
    {
        NAS_EMM_TAU_LOG_WARN( "NAS_EMM_TAUSER_CHKFSMStateMsgp ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsWaitAccessGrantIndMsgRrcGrantInd_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    /*get the msg info*/
    pRrcMmGrantInd = (LRRC_LMM_ACCESS_GRANT_IND_STRU *) pMsgStru;

    NAS_EMM_TAU_LOG1_INFO("NAS_EMM_MsRegSsWaitAccessGrantIndMsgRrcGrantInd: Granttype =.",pRrcMmGrantInd->enAccessGrantType);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsRegSsWaitAccessGrantIndMsgRrcGrantInd_ENUM,LNAS_FUNCTION_LABEL1,
                                        pRrcMmGrantInd->enAccessGrantType);

    /* 清除bar类型*/
    NAS_EMM_ClearBarType(pRrcMmGrantInd->enAccessGrantType);

    /* 调用REG态下解Bar的公共处理*/
    NAS_EMM_RegBarCommProc();

    return NAS_LMM_MSG_HANDLED;
 }

/*****************************************************************************
 Function Name   : NAS_EMM_RegBarCommProc
 Description     : REG态解bar的公共处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-12-1  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_RegBarCommProc( VOS_VOID )
{
    /* 根据BarProcedure进入不同的处理*/
    if (NAS_EMM_BAR_PROCEDURE_TAU == NAS_EMM_GetBarProcedure())
    {
        NAS_EMM_TAU_LOG_NORM("NAS_EMM_RegBarCommProc:TAU BAR");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegBarCommProc_ENUM,LNAS_FUNCTION_LABEL1);
        NAS_EMM_ProcTauBar();
    }
    else if (NAS_EMM_BAR_PROCEDURE_SERVICE == NAS_EMM_GetBarProcedure())
    {
        NAS_EMM_TAU_LOG_NORM("NAS_EMM_RegBarCommProc:SERVICE BAR");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegBarCommProc_ENUM,LNAS_FUNCTION_LABEL2);
        NAS_EMM_ProcSrvBar();
    }
    else
    {
        ;
    }

    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_MsRegSsWaitAccessGrantIndMsgSysinfoInd
 Description     : Reg.WtAccessGrantInd状态下收到SYS_INFO_IND处理禁止信息
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-12-14  Draft Enact
    2.lihong 00150010           2012-12-19  Modify:Emergency

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegSsWaitAccessGrantIndMsgSysinfoInd( VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru )
{
    VOS_UINT32                          ulRslt;
    EMMC_EMM_SYS_INFO_IND_STRU          *pstsysinfo = NAS_EMM_NULL_PTR;

    NAS_EMM_TAU_LOG_INFO("NAS_EMM_MsRegSsWaitAccessGrantIndMsgSysinfoInd entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsWaitAccessGrantIndMsgSysinfoInd_ENUM,LNAS_ENTRY);
    (VOS_VOID)ulMsgId;

    /* 入参检查*/
    ulRslt = NAS_EMM_TAU_CHKFSMStateMsgp(EMM_MS_REG,EMM_SS_REG_WAIT_ACCESS_GRANT_IND,pMsgStru);
    if ( NAS_EMM_SUCC != ulRslt )
    {
        NAS_EMM_TAU_LOG_WARN( "NAS_EMM_TAUSER_CHKFSMStateMsgp ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsWaitAccessGrantIndMsgSysinfoInd_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    /* 如果系统消息被禁，则清空Bar信息，迁移到 Reg.Limite_Service*/
    pstsysinfo                          = (EMMC_EMM_SYS_INFO_IND_STRU*)pMsgStru;
    if ((NAS_LMM_REG_STATUS_NORM_REGED == NAS_LMM_GetEmmInfoRegStatus())
        && ((EMMC_EMM_NO_FORBIDDEN != pstsysinfo->ulForbiddenInfo)
            || (EMMC_EMM_CELL_STATUS_ANYCELL == pstsysinfo->ulCellStatus)))
    {
        NAS_EMM_SetTauTypeNoProcedure();

        /* 清空Bar信息*/
        NAS_EMM_ClearBarResouce();

        /* 状态迁移: Reg.Limite_Service*/
        NAS_EMM_TAUSER_FSMTranState(    EMM_MS_REG,
                                        EMM_SS_REG_LIMITED_SERVICE,
                                        TI_NAS_EMM_STATE_NO_TIMER);

        /*向MMC发送LMM_MMC_TAU_RESULT_IND消息*/
        NAS_EMM_MmcSendTauActionResultIndForbType((VOS_VOID*)&pstsysinfo->ulForbiddenInfo);
    }

    return NAS_LMM_MSG_HANDLED;
}


VOS_UINT32  NAS_EMM_MsRegSsWaitAccessGrantIndMsgIntraTauReq( VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru )
{
    VOS_UINT32                               ulRslt;
    NAS_LMM_INTRA_TAU_REQ_STRU         *pIntraTauReq = NAS_EMM_NULL_PTR;

    (VOS_VOID)ulMsgId;
    pIntraTauReq    = (NAS_LMM_INTRA_TAU_REQ_STRU*)pMsgStru;

    NAS_EMM_TAU_LOG_NORM("NAS_EMM_MsRegSsWaitAccessGrantIndMsgIntraTauReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsWaitAccessGrantIndMsgIntraTauReq_ENUM,LNAS_ENTRY);

    /*check the input params and states*/
    ulRslt = NAS_EMM_TAU_CHKFSMStateMsgp(EMM_MS_REG,EMM_SS_REG_WAIT_ACCESS_GRANT_IND,pMsgStru);
    if ( NAS_EMM_SUCC != ulRslt )
    {
        NAS_EMM_TAU_LOG_WARN( "NAS_EMM_TAUSER_CHKFSMStateMsgp ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsWaitAccessGrantIndMsgIntraTauReq_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }
    if(NAS_LMM_INTRA_TAU_TYPE_PARA_CHANGE == pIntraTauReq->enIntraTauType)
    {
        /*设置DRX或NetCapability改变标志*/
        NAS_LMM_SetEmmInfoDrxNetCapChange( NAS_EMM_YES);
    }

    else if(NAS_LMM_INTRA_TAU_TYPE_IMSI_ATTACH == pIntraTauReq->enIntraTauType)
    {
        if (NAS_EMM_SUCC == NAS_EMM_JudgeBarType(NAS_EMM_BAR_TYPE_MO_SIGNAL))
        {
            NAS_EMM_TAU_LOG_WARN( "NAS_EMM_MsRegSsWaitAccessGrantIndMsgIntraTauReq TAU_IMSI_ATTACH MO SIGNAL!!");
            TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsWaitAccessGrantIndMsgIntraTauReq_ENUM,LNAS_FUNCTION_LABEL1);
            NAS_EMM_AppSendAttRstInTau(MMC_LMM_ATT_RSLT_FAILURE);
            return NAS_LMM_MSG_HANDLED;
        }
    }
    else
    {

    }

    if (NAS_EMM_SUCC != NAS_EMM_JudgeBarType(NAS_EMM_BAR_TYPE_MO_SIGNAL))
    {
        NAS_EMM_TAU_LOG_NORM("NAS_EMM_MsRegSsWaitAccessGrantIndMsgIntraTauReq:TAU is start");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsWaitAccessGrantIndMsgIntraTauReq_ENUM,LNAS_FUNCTION_LABEL2);

        /* 判断是否存在上行Pending*/
        NAS_EMM_TAU_IsUplinkPending();

        /* 新增入参TAU发起原因 */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_OTHERS);
    }

    return NAS_LMM_MSG_HANDLED;
}


VOS_UINT32  NAS_EMM_MsRegSsWaitAccessGrantIndMsgBearerStatusReq(
                                                    VOS_UINT32  ulMsgId,
                                                    VOS_VOID   *pMsgStru )
{
    VOS_UINT32                               ulRslt;

    (VOS_VOID)ulMsgId;
    NAS_EMM_TAU_LOG_NORM("NAS_EMM_MsRegSsWaitAccessGrantIndMsgBearerStatusReq entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsWaitAccessGrantIndMsgBearerStatusReq_ENUM,LNAS_ENTRY);

    /* 检查当前状态和入参*/
    ulRslt = NAS_EMM_TAU_CHKFSMStateMsgp(EMM_MS_REG,EMM_SS_REG_WAIT_ACCESS_GRANT_IND,pMsgStru);
    if ( NAS_EMM_SUCC != ulRslt )
    {
        NAS_EMM_TAU_LOG_WARN( "NAS_EMM_TAUSER_CHKFSMStateMsgp ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsWaitAccessGrantIndMsgBearerStatusReq_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    /* 设置承载上下文变化*/
    NAS_EMM_SetEpsContextStatusChange(NAS_EMM_EPS_BEARER_STATUS_CHANGEED);

    /* 判断如果MO_Signal允许接入，则立即触发TAU，携带'ACTIVE'*/
    if (NAS_EMM_SUCC != NAS_EMM_JudgeBarType(NAS_EMM_BAR_TYPE_MO_SIGNAL))
    {
        NAS_EMM_TAU_LOG_NORM("NAS_EMM_MsRegSsWaitAccessGrantIndMsgBearerStatusReq:Init TAU");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsWaitAccessGrantIndMsgBearerStatusReq_ENUM,LNAS_FUNCTION_LABEL1);

        /* 判断是否存在上行Pending*/
        NAS_EMM_TAU_IsUplinkPending();

        /* 如果存在未完成的LOAD_BALANCE TAU，则触发LOAD_BALANCE类型TAU
           否则，触发承载上下文改变触发的TAU*/

        /*NAS_EMM_TAU_SaveEmmTAUStartCause(     NAS_EMM_TAU_START_CAUSE_SYSINFO);*/
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
        /* 新增入参TAU发起原因 */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_BEARER_STATUS_CHANGEED);
    }

    return NAS_LMM_MSG_HANDLED;
}


VOS_UINT32  NAS_EMM_MsRegSsWaitAccessGrantIndMsgT3412Exp(  VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru)
{
    VOS_UINT32                               ulRslt;

    (VOS_VOID)ulMsgId;

    NAS_EMM_TAU_LOG_NORM("NAS_EMM_MsRegSsWaitAccessGrantIndMsgT3412Exp is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsWaitAccessGrantIndMsgT3412Exp_ENUM,LNAS_ENTRY);

     /*check the input params and states*/
    ulRslt = NAS_EMM_TAU_CHKFSMStateMsgp(EMM_MS_REG,EMM_SS_REG_WAIT_ACCESS_GRANT_IND,pMsgStru);
    if ( NAS_EMM_SUCC != ulRslt )
    {
        NAS_EMM_TAU_LOG_WARN( "NAS_EMM_TAUSER_CHKFSMStateMsgp ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsWaitAccessGrantIndMsgT3412Exp_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }


    /*设置周期TAU定制器超时标志*/
    NAS_LMM_SetEmmInfoT3412ExpCtrl(NAS_EMM_T3412_EXP_YES_OTHER_STATE);

    if (MMC_LMM_TIN_RAT_RELATED_TMSI == NAS_EMM_GetTinType())
    {
        /*启动定时器T3423*/
        NAS_LMM_StartPtlTimer(TI_NAS_EMM_PTL_T3423);

        /*通知GU模T3423启动*/
        NAS_EMM_SendTimerStateNotify(TI_NAS_EMM_PTL_T3423, LMM_MMC_TIMER_START);

    }

    if (NAS_EMM_SUCC != NAS_EMM_JudgeBarType(NAS_EMM_BAR_TYPE_MO_SIGNAL))
    {
        NAS_EMM_TAU_LOG_NORM("NAS_EMM_MsRegSsWaitAccessGrantIndMsgT3412Exp:TAU is start");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsWaitAccessGrantIndMsgT3412Exp_ENUM,LNAS_FUNCTION_LABEL1);

        /* 判断是否存在上行Pending*/
        NAS_EMM_TAU_IsUplinkPending();

        /*触发周期性TAU*/
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_T3412EXP);
        NAS_LMM_SetEmmInfoT3412ExpCtrl(NAS_EMM_T3412_EXP_YES_OTHER_STATE);
        /* 新增入参TAU发起原因 */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_3412_EXP);
    }

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsRegSsWaitAccessGrantIndMsgT3411Exp
 Description     : Reg.WtAccessGrantInd状态下收到t3411超时，判断如果需要则重
                   新触发TAU:可能的场景
                   1)承载状态变化触发TAU，底层出错进入Reg.Normal_Service状态，启动T3411
                   2)上行数传触发Service，接入被Bar，进入Reg.WtAccGrantInd
                   3)在Reg.WtAccGrantInd状态下收到T3411超时
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421    2010-11-23  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegSsWaitAccessGrantIndMsgT3411Exp( VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru )
{
    MMC_LMM_TAU_RSLT_ENUM_UINT32        ulTauRslt = MMC_LMM_TAU_RSLT_BUTT;
    VOS_UINT32                               ulRslt;

   (VOS_VOID)ulMsgId;
   NAS_EMM_TAU_LOG_NORM("NAS_EMM_MsRegSsWaitAccessGrantIndMsgT3411Exp entered.");
   TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsWaitAccessGrantIndMsgT3411Exp_ENUM,LNAS_ENTRY);


    /*状态和入参检查*/
    ulRslt = NAS_EMM_TAU_CHKFSMStateMsgp(EMM_MS_REG,EMM_SS_REG_WAIT_ACCESS_GRANT_IND,pMsgStru);
    if ( NAS_EMM_SUCC != ulRslt )
    {
        NAS_EMM_TAU_LOG_WARN( "NAS_EMM_TAUSER_CHKFSMStateMsgp ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsWaitAccessGrantIndMsgT3411Exp_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    /*如果MO_SIGNAL允许接入，则检查是否有未完成的TAU*/
    if (NAS_EMM_SUCC != NAS_EMM_JudgeBarType(NAS_EMM_BAR_TYPE_MO_SIGNAL))
    {
        /*如果有未完成的TAU则重新触发，且携带'ACTIVE'标志*/
        if(NAS_EMM_YES == NAS_EMM_SER_AbnormalNeedtoContinueTau())
        {
            NAS_EMM_TAU_SaveEmmCollisionCtrl(    NAS_EMM_COLLISION_SERVICE);
            /* 新增入参TAU发起原因 */
            NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_3411OR3402);
        }
    }
    else
    {
        if (NAS_EMM_YES == NAS_EMM_TAU_CanTriggerComTauWithIMSI())
        {
            NAS_EMM_TAU_SaveTAUtype(NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_WITH_IMSI);

            ulTauRslt = MMC_LMM_TAU_RSLT_ACCESS_BARED;
            NAS_EMM_MmcSendTauActionResultIndOthertype((VOS_VOID*)&ulTauRslt);
        }

    }
    return NAS_LMM_MSG_HANDLED;
}

/*******************************************************************************
  Module   :
  Function : NAS_EMM_MsDeRegInitSsWaitCNDetachCnfMsgSysinfo
  Input    :
  Output   :
  NOTE     :
  Return   :
  History  :
    1.Zhouyan 00125190  2008.09.10  新规作成
    2.zhengjunyan 00148421 2010-10-25 Mod:添加对Forb信息的判断处理
    3.zhengjunyan 00148421 2010-11-16 添加:TA在TAI LIST中更新 LVR TAI
    4.lihong 00150010      2012-12-17 Modify:Emergency
    5.lifuxin 00253982     2014-11-06 建链重构
*******************************************************************************/
VOS_UINT32 NAS_EMM_MsDeRegInitSsWaitCNDetachCnfMsgSysinfo(VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru )
{
    VOS_UINT32                          ulRslt      = NAS_EMM_FAIL;
    VOS_UINT32                          ulTaRslt    = NAS_EMM_FAIL;
    EMMC_EMM_SYS_INFO_IND_STRU          *pstsysinfo  = NAS_EMM_NULL_PTR;
    NAS_LMM_NETWORK_INFO_STRU           *pMmNetInfo  = NAS_EMM_NULL_PTR;
    EMMC_EMM_FORBIDDEN_INFO_ENUM_UINT32  ulForbiddenInfo = EMMC_EMM_NO_FORBIDDEN;
    (VOS_VOID)ulMsgId;
    NAS_EMM_TAU_LOG_NORM("Nas_Emm_MsDeRegInitSsWaitCNDetachCnfMsgSysinfo entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDeRegInitSsWaitCNDetachCnfMsgSysinfo_ENUM,LNAS_ENTRY);

    /* 函数输入指针参数检查, 状态匹配检查,若不匹配,退出*/
    ulRslt = NAS_EMM_TAU_CHKFSMStateMsgp(EMM_MS_DEREG_INIT,EMM_SS_DETACH_WAIT_CN_DETACH_CNF,pMsgStru);
    if ( NAS_EMM_SUCC != ulRslt)
    {
        NAS_EMM_TAU_LOG_WARN( "NAS_EMM_MsDeRegInitSsWaitCNDetachCnfMsgSysinfo ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDeRegInitSsWaitCNDetachCnfMsgSysinfo_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    pstsysinfo = (EMMC_EMM_SYS_INFO_IND_STRU *)pMsgStru;

    /*建链过程中收到系统消息，等待建链回复后，直接处理即可*/
    if(NAS_EMM_CONN_ESTING == NAS_EMM_GetConnState())
    {
        return  NAS_LMM_STORE_HIGH_PRIO_MSG;
    }

    /* 判断TA是否在TA List中*/
    ulTaRslt = NAS_EMM_TAU_IsCurrentTAInTaList();
    if (VOS_TRUE == NAS_EMM_GLO_AD_GetUsimPullOutFlag())
    {
         if (NAS_EMM_FAIL == ulTaRslt)
         {
             /*停止定时器T3421*/
             NAS_LMM_StopStateTimer(          TI_NAS_EMM_T3421);

            #if (FEATURE_ON == FEATURE_DSDS)
            /*发送end notify消息给RRC，通知RRC释放资源*/
            NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_PS_DETACH);
            #endif

             /*向ESM发送ID_EMM_ESM_STATUS_IND消息*/
             NAS_EMM_TAU_SendEsmStatusInd(EMM_ESM_ATTACH_STATUS_DETACHED);

             NAS_EMM_ProcLocalNoUsim();

             /* 通知APP_DETACH_IND(APP_MM_DETACH_ENTITY_ME)*/
             NAS_EMM_MmcSendDetIndLocal(MMC_LMM_L_LOCAL_DETACH_OTHERS);

            #if (FEATURE_PTM == FEATURE_ON)
            NAS_EMM_LocalDetachErrRecord(EMM_ERR_LOG_LOCAL_DETACH_TYPE_OTHER);
            #endif
             NAS_EMM_ClearAppMsgPara();

             NAS_EMM_RelReq(                 NAS_LMM_NOT_BARRED);
         }
         return NAS_LMM_MSG_HANDLED;
    }
    /* 定制系统内切换到被禁小区,忽略被禁:当存在L小区A和B(属于俩TA)
        UE在小区B上驻留，由于MME某些异常,给UE下发原因值#15，但MME未将
        TA放入被禁列表中(未真被禁，只是临时被禁)，当UE收到#15原因值,
        主动释重新驻留在A小区，之后网侧让UE切换到B小区，而切换时LRRC
        不会判断小区是否被禁，LMM收到系统消息后，由B小区上收到过#15原
        因值,LMM主动释放进入限制服务态，LRRC释放后在小区A上驻留，从而导致乒乓切换 */
    ulForbiddenInfo = pstsysinfo->ulForbiddenInfo;
    if(NAS_EMM_YES == NAS_EMM_IsIntraHoIgnoreForbSysInfo())
    {
        /* 忽略FORBIDDEN TA FOR ROAMING,由于被#15原因值拒后,驻留的TA将放入FORBIDDEN TA LIST里,并从TAILIST里删除，所以后续发起TAU */
        if(EMMC_EMM_FORBIDDEN_TA_FOR_ROAMING == pstsysinfo->ulForbiddenInfo)
        {
            NAS_EMM_PUBU_LOG1_INFO("NAS_EMM_MsRegSsNormalMsgSysinfo Ignore ForbTaForRoaming:forbiddenInfo = ",
                               pstsysinfo->ulForbiddenInfo);
            TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsDeRegInitSsWaitCNDetachCnfMsgSysinfo_ENUM,LNAS_EMM_FORB_INFO,
                               pstsysinfo->ulForbiddenInfo);
            ulForbiddenInfo = EMMC_EMM_NO_FORBIDDEN;
            #if (FEATURE_ON == FEATURE_PTM)
            NAS_EMM_ImprovePerformceeErrReport(EMM_OM_ERRLOG_IMPROVEMENT_TYPE_HO_TO_FORBIDDEN_TA);
            #endif
        }
    }
    /* 获取系统消息 + 当前网络信息*/
    pstsysinfo                          = (EMMC_EMM_SYS_INFO_IND_STRU*)pMsgStru;
    pMmNetInfo                          = NAS_LMM_GetEmmInfoNetInfoAddr();
    /* 如果系统消息被禁，则释放连接,本地完成DETACH,进入Dereg.Limite_Service*/
    if ((NAS_LMM_REG_STATUS_NORM_REGED == NAS_LMM_GetEmmInfoRegStatus())
        && ((EMMC_EMM_NO_FORBIDDEN != ulForbiddenInfo)
            || (EMMC_EMM_CELL_STATUS_ANYCELL == pstsysinfo->ulCellStatus)))
    {
        NAS_EMM_TAU_LOG_WARN("NAS_EMM_MsDeRegInitSsWaitCNDetachCnfMsgSysinfo: Cell Forb.");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDeRegInitSsWaitCNDetachCnfMsgSysinfo_ENUM,LNAS_EMM_FORBIDDEN);

        /* 终止DETACH流程,释放连接,注意:给RRC发送REL_REQ消息和状态转换的顺序不能颠倒*/
        NAS_EMM_DetProcEnterForbTA();

        return  NAS_LMM_MSG_HANDLED;
    }

#if(FEATURE_ON == FEATURE_CSG)
    if(NAS_EMM_YES == NAS_EMM_MsDeRegInitSsWaitCNDetachCnfIsCsgIdNotInListTauStart())
    {
        return NAS_LMM_MSG_HANDLED;
    }
#endif

    if (NAS_EMM_FAIL == ulTaRslt)
    {
         NAS_EMM_TAU_LOG_INFO("NAS_EMM_MsDeRegInitSsWaitCNDetachCnfMsgSysinfo:TA not in TAI List.");
         TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDeRegInitSsWaitCNDetachCnfMsgSysinfo_ENUM,LNAS_EMM_TA_NOT_IN_TA_LIST);

         /* 设置流程冲突标志位DETACH*/
         NAS_EMM_TAU_SaveEmmCollisionCtrl(NAS_EMM_COLLISION_DETACH);

         /*NAS_EMM_TAU_SaveEmmTAUStartCause(     NAS_EMM_TAU_START_CAUSE_SYSINFO);*/
         NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);

         /* 如果是DETACH类型为EPS/IMSI，则设置联合DETACH被TAU打断标识，这样
            发起的TAU类型为联合TAU */
         if (MMC_LMM_MO_DET_CS_PS == NAS_EMM_GetDetachType())
         {
            /* 设置联合DETACH被TAU打断标识，这样后续发起的TAU类型仍然为联合TAU */
            NAS_EMM_TAU_SetEmmCombinedDetachBlockFlag(NAS_EMM_COM_DET_BLO_YES);
         }

         /* 调用DETACH的函数，结束DETACH流程*/
         NAS_EMM_DetachToTAU();

         /* 启动TAU Procedure
            注:MO_DETACH流程中触发TAU，因为DETACH_COLLISION标志，必然携带ACTVIE,
           不判断上行阻塞*/
         /* 新增入参TAU发起原因 */
         NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_NOT_IN_TAI_LIST);
    }
    /* TA在TAI List中，更新 L.V.R TAI*/
    else
    {
        NAS_EMM_SetLVRTai(&pMmNetInfo->stPresentNetId);
        if (NAS_LMM_REG_STATUS_EMC_REGED != NAS_LMM_GetEmmInfoRegStatus())
        {
            /*保存PS LOC信息*/
            NAS_LMM_WritePsLoc(NAS_NV_ITEM_UPDATE);
        }

        /* 网络信息变更,MMA不会立即更新网络信息,需要收到TAU IND才会更新,为规避该问题,
            LMM构造一条不带任何参数TAU IND消息上报给MMC */
        NAS_EMM_SetTauTypeNoProcedure();

        /*向MMC发送LMM_MMC_TAU_RESULT_IND消息*/
        NAS_EMM_MmcSendTauActionResultIndSuccWithoutPara();
    }

    return NAS_LMM_MSG_HANDLED;
}

/*******************************************************************************
  Module   : 在REG+IMSI_DETACH_INIT状态下处理系统消息
  Function : NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgSysinfo
  Input    : ulMsgId----------------------消息ID
             pMsgStru---------------------系统消息指针
  Output   : NONE
  NOTE     :
  Return   : VOS_UINT32
  History  :
    1.lihong 00150010  2011.09.17  新规作成
    2.lihong 00150010  2012.12.18  Modify:Emergency
*******************************************************************************/
VOS_UINT32 NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgSysinfo
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    VOS_UINT32                          ulRslt      = NAS_EMM_FAIL;
    VOS_UINT32                          ulTaRslt    = NAS_EMM_FAIL;
    EMMC_EMM_SYS_INFO_IND_STRU          *pstsysinfo  = NAS_EMM_NULL_PTR;
    NAS_LMM_NETWORK_INFO_STRU           *pMmNetInfo  = NAS_EMM_NULL_PTR;
    EMMC_EMM_FORBIDDEN_INFO_ENUM_UINT32  ulForbiddenInfo = EMMC_EMM_NO_FORBIDDEN;

    (VOS_VOID)ulMsgId;
    NAS_EMM_TAU_LOG_NORM("NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgSysinfo entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgSysinfo_ENUM,LNAS_ENTRY);

    /* 函数输入指针参数检查, 状态匹配检查,若不匹配,退出*/
    ulRslt = NAS_EMM_TAU_CHKFSMStateMsgp(EMM_MS_REG,EMM_SS_REG_IMSI_DETACH_WATI_CN_DETACH_CNF,pMsgStru);
    if ( NAS_EMM_SUCC != ulRslt)
    {
        NAS_EMM_TAU_LOG_WARN( "NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgSysinfo ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgSysinfo_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    pstsysinfo = (EMMC_EMM_SYS_INFO_IND_STRU *)pMsgStru;

    /* 判断TA是否在TA List中*/
    ulTaRslt = NAS_EMM_TAU_IsCurrentTAInTaList();
    /* 定制系统内切换到被禁小区,忽略被禁:当存在L小区A和B(属于俩TA)
        UE在小区B上驻留，由于MME某些异常,给UE下发原因值#15，但MME未将
        TA放入被禁列表中(未真被禁，只是临时被禁)，当UE收到#15原因值,
        主动释重新驻留在A小区，之后网侧让UE切换到B小区，而切换时LRRC
        不会判断小区是否被禁，LMM收到系统消息后，由B小区上收到过#15原
        因值,LMM主动释放进入限制服务态，LRRC释放后在小区A上驻留，从而导致乒乓切换 */
    ulForbiddenInfo = pstsysinfo->ulForbiddenInfo;
    if(NAS_EMM_YES == NAS_EMM_IsIntraHoIgnoreForbSysInfo())
    {
        /* 忽略FORBIDDEN TA FOR ROAMING,由于被#15原因值拒后,驻留的TA将放入FORBIDDEN TA LIST里,并从TAILIST里删除，所以后续发起TAU */
        if(EMMC_EMM_FORBIDDEN_TA_FOR_ROAMING == pstsysinfo->ulForbiddenInfo)
        {
            NAS_EMM_PUBU_LOG1_INFO("NAS_EMM_MsRegSsNormalMsgSysinfo Ignore ForbTaForRoaming:forbiddenInfo = ",
                               pstsysinfo->ulForbiddenInfo);
            TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgSysinfo_ENUM,LNAS_EMM_FORB_INFO,
                               pstsysinfo->ulForbiddenInfo);
            ulForbiddenInfo = EMMC_EMM_NO_FORBIDDEN;
            #if (FEATURE_ON == FEATURE_PTM)
            NAS_EMM_ImprovePerformceeErrReport(EMM_OM_ERRLOG_IMPROVEMENT_TYPE_HO_TO_FORBIDDEN_TA);
            #endif
        }
    }

    /* 获取系统消息 + 当前网络信息*/
    pstsysinfo                          = (EMMC_EMM_SYS_INFO_IND_STRU*)pMsgStru;
    pMmNetInfo                          = NAS_LMM_GetEmmInfoNetInfoAddr();
    /* 如果系统消息被禁，则释放连接,本地完成DETACH,进入Dereg.Limite_Service*/
    if ((NAS_LMM_REG_STATUS_NORM_REGED == NAS_LMM_GetEmmInfoRegStatus())
        && ((EMMC_EMM_NO_FORBIDDEN != ulForbiddenInfo)
            || (EMMC_EMM_CELL_STATUS_ANYCELL == pstsysinfo->ulCellStatus)))
    {
        NAS_EMM_TAU_LOG_WARN("NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgSysinfo: Cell Forb.");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgSysinfo_ENUM,LNAS_EMM_FORBIDDEN);

        /* 终止DETACH流程，根据是否存在紧急呼承载，决定是否释放链路 */
        NAS_EMM_ImsiDetProcEnterForbTA();

        return  NAS_LMM_MSG_HANDLED;
    }
#if(FEATURE_ON == FEATURE_CSG)
    if((NAS_EMM_YES == NAS_LMM_IsCsgCampOn())
        &&(NAS_EMM_FAIL == NAS_EMM_TAU_IsCsgIdInAllowedOrOperatorCsgList()))
    {
         NAS_EMM_TAU_LOG_INFO("NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgSysinfo:CSG ID not in CSG List.");
         TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgSysinfo_ENUM,LNAS_FUNCTION_LABEL1);


       /* 设置流程冲突标志位DETACH*/
        NAS_EMM_TAU_SaveEmmCollisionCtrl(NAS_EMM_COLLISION_DETACH);

        /*NAS_EMM_TAU_SaveEmmTAUStartCause(     NAS_EMM_TAU_START_CAUSE_SYSINFO);*/
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);

        /* 设置联合DETACH被TAU打断标识，这样后续发起的TAU类型仍然为联合TAU */
        NAS_EMM_TAU_SetEmmCombinedDetachBlockFlag(NAS_EMM_COM_DET_BLO_YES);

        /* 调用DETACH的函数，结束DETACH流程*/
        NAS_EMM_DetachToTAU();

        /* 新增入参TAU发起原因 */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_NOT_IN_CSG_LIST);

        return NAS_LMM_MSG_HANDLED;
    }
#endif
    if (NAS_EMM_FAIL == ulTaRslt)
    {
         NAS_EMM_TAU_LOG_INFO("NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgSysinfo:TA not in TAI List.");
         TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgSysinfo_ENUM,LNAS_EMM_TA_NOT_IN_TA_LIST);

         /* 设置流程冲突标志位DETACH*/
         NAS_EMM_TAU_SaveEmmCollisionCtrl(NAS_EMM_COLLISION_DETACH);

         /*NAS_EMM_TAU_SaveEmmTAUStartCause(     NAS_EMM_TAU_START_CAUSE_SYSINFO);*/
         NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);

         /* 设置联合DETACH被TAU打断标识，这样后续发起的TAU类型仍然为联合TAU */
         NAS_EMM_TAU_SetEmmCombinedDetachBlockFlag(NAS_EMM_COM_DET_BLO_YES);

         /* 调用DETACH的函数，结束DETACH流程*/
         NAS_EMM_DetachToTAU();

         /* 启动TAU Procedure
            注:MO_DETACH流程中触发TAU，因为DETACH_COLLISION标志，必然携带ACTVIE,
               不判断上行阻塞*/
         /* 新增入参TAU发起原因 */
         NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_NOT_IN_TAI_LIST);
    }
    /* TA在TAI List中，更新 L.V.R TAI*/
    else
    {
        NAS_EMM_SetLVRTai(&pMmNetInfo->stPresentNetId);
        if (NAS_LMM_REG_STATUS_EMC_REGED != NAS_LMM_GetEmmInfoRegStatus())
        {
            /*保存PS LOC信息*/
            NAS_LMM_WritePsLoc(NAS_NV_ITEM_UPDATE);
        }
        /* 小区信息更新,MMA不会立即更新网络信息,需要收到TAU IND才会更新,为规避该问题,
            LMM构造一条不带任何参数TAU IND消息上报给MMC */
        NAS_EMM_SetTauTypeNoProcedure();

        /*向MMC发送LMM_MMC_TAU_RESULT_IND消息*/
        NAS_EMM_MmcSendTauActionResultIndSuccWithoutPara();
    }

    return NAS_LMM_MSG_HANDLED;
}

/*******************************************************************************
  Module   :
  Function : NAS_EMM_MsTAUInitSsWaitCNCnfMsgSysinfo
  Input    :
  Output   :
  NOTE     :
  Return   :
  History  :
    1.  Zhouyan 00125190  2008.09.10  新规作成
    2.  yangfan 00159566  2009.08.06  修改
    3.  zhengjunyan 00148421 2010.10.25 Mod:添加系统消息被禁的处理和New TA的处理
    4.  liuhua      00212067 2012.05.29 TA发生变化时，更新EU值为EU2
    5.  lihong  00150010  2012.12.14  Modify:Emergency
    6.  lifuxin 00253982  2014.11.06  建链重构
*******************************************************************************/
VOS_UINT32 NAS_EMM_MsTauInitSsWaitCNCnfMsgSysinfo(VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru )
{
    VOS_UINT32                          ulRslt      = NAS_EMM_FAIL;
    EMMC_EMM_SYS_INFO_IND_STRU          *pstsysinfo  = NAS_EMM_NULL_PTR;
    NAS_EMM_TAU_START_CAUSE_ENUM_UINT8  enTauStartCause;

    (VOS_VOID)ulMsgId;
    NAS_EMM_TAU_LOG_INFO("Nas_Emm_MsTauInitSsWaitCNCnfMsgSysinfo is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsTauInitSsWaitCNCnfMsgSysinfo_ENUM,LNAS_ENTRY);

    /* 函数输入指针参数检查, 状态匹配检查,若不匹配,退出*/
    ulRslt = NAS_EMM_TAU_CHKFSMStateMsgp(EMM_MS_TAU_INIT,EMM_SS_TAU_WAIT_CN_TAU_CNF,pMsgStru);
    if ( NAS_EMM_SUCC != ulRslt )
    {
        NAS_EMM_TAU_LOG_WARN("NAS_EMM_MsTauInitSsWaitCNCnfMsgSysinfo ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsTauInitSsWaitCNCnfMsgSysinfo_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    /* 获取系统消息*/
    pstsysinfo                          = (EMMC_EMM_SYS_INFO_IND_STRU*)pMsgStru;
    /*如果系统消息被禁，则缓存，进入各流程具体处理*/
    if(((EMMC_EMM_NO_FORBIDDEN != pstsysinfo->ulForbiddenInfo)
        || (EMMC_EMM_CELL_STATUS_ANYCELL == pstsysinfo->ulCellStatus))
        && (NAS_EMM_CONN_ESTING == NAS_EMM_GetConnState()))
    {
        return  NAS_LMM_STORE_HIGH_PRIO_MSG;
    }

    /* 如果系统消息被禁,终止TAU流程，释放连接*/
    if ((NAS_LMM_REG_STATUS_NORM_REGED == NAS_LMM_GetEmmInfoRegStatus())
        && ((EMMC_EMM_NO_FORBIDDEN != pstsysinfo->ulForbiddenInfo)
            || (EMMC_EMM_CELL_STATUS_ANYCELL == pstsysinfo->ulCellStatus)))
    {
        /* 终止TAU流程*/
        NAS_LMM_StopStateTimer(          TI_NAS_EMM_STATE_TAU_T3430);

        #if (FEATURE_ON == FEATURE_DSDS)
        /*发送end notify消息给RRC，通知RRC释放资源*/
        NAS_EMM_TAU_SendRrcDsdsEndNotify();
        #endif

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
        NAS_EMM_SendMtcTAUEndType();
#endif

        if (NAS_EMM_TAU_START_CAUSE_ESM_EMC_PDN_REQ == NAS_EMM_TAU_GetEmmTAUStartCause())
        {
            NAS_EMM_TAU_LOG_INFO("NAS_EMM_MsTauInitSsWaitCNCnfMsgSysinfo:CAUSE_ESM_EMC_PDN_REQ");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_MsTauInitSsWaitCNCnfMsgSysinfo_ENUM,LNAS_FUNCTION_LABEL1);

            NAS_EMM_EmcPndReqTauAbnormalCommProc(   NAS_EMM_MmcSendTauActionResultIndForbType,
                                                    (VOS_VOID*)&pstsysinfo->ulForbiddenInfo,
                                                    EMM_SS_DEREG_LIMITED_SERVICE);
        }
        else
        {
            /* 状态迁移*/
            NAS_EMM_TAUSER_FSMTranState(EMM_MS_REG,
                            EMM_SS_REG_LIMITED_SERVICE,
                            TI_NAS_EMM_STATE_NO_TIMER);

            /*向MMC发送LMM_MMC_TAU_RESULT_IND消息在冲突处理中执行*/
            NAS_EMM_TAU_ProcEnterForbTA(pstsysinfo->ulForbiddenInfo);
        }
        NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);

        return NAS_LMM_MSG_HANDLED;
    }

    /*在TAU_INIT+WAIT_CN_CNF中收到系统消息，当前的连接状态是NAS_EMM_CONN_ESTING
      ,如果收到的系统消息在被禁列表中，则释放链路，转到限制服务态，如果是周期性的TAU
      则高优先级缓存，否则，直接丢弃，等本次的建链回复
    */
    enTauStartCause = NAS_EMM_TAU_GetTauStartCause();
    if(NAS_EMM_CONN_ESTING == NAS_EMM_GetConnState())
    {
        if(NAS_EMM_TAU_START_CAUSE_T3412EXP == enTauStartCause)
        {
            return NAS_LMM_STORE_HIGH_PRIO_MSG;
        }
        else
        {
            return NAS_LMM_MSG_HANDLED;
        }
    }

#if(FEATURE_ON == FEATURE_CSG)
    if(NAS_EMM_YES == NAS_EMM_MsTauInitSsWaitCNCnfIsCsgIdChangeTauStart())
    {
        return NAS_LMM_MSG_HANDLED;
    }
#endif

    NAS_EMM_MsTauInitSsWaitCNCnfSysChangeOrNotProc(pstsysinfo->ulChangeInfo);
    return NAS_LMM_MSG_HANDLED;
}

VOS_VOID NAS_EMM_ProcHoWaitSysInfoBufferMsg( VOS_VOID )
{
    NAS_EMM_MRRC_MGMT_DATA_STRU         *pEmmMrrcMgmtData = NAS_EMM_NULL_PTR;
    NAS_EMM_MRRC_DATA_REQ_STRU          *pMrrcDataMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulRrcMmDataReqMsgLen;
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          ulCurSaveMsgNum = 0;
    VOS_UINT32                          ulMmRrcOpId;

    ulCurSaveMsgNum = g_ulSaveMsgNum;

    pEmmMrrcMgmtData                    = NAS_EMM_GET_MRRC_MGMT_DATA_ADDR();
    ulRrcMmDataReqMsgLen = (sizeof(NAS_EMM_MRRC_DATA_REQ_STRU)+
                                   pEmmMrrcMgmtData->ulNasMsgLength) -
                                   NAS_EMM_4BYTES_LEN;
    /* 申请消息内存*/
    pMrrcDataMsg = (NAS_EMM_MRRC_DATA_REQ_STRU *)(VOS_VOID*)NAS_LMM_MEM_ALLOC(ulRrcMmDataReqMsgLen);

    if(VOS_NULL_PTR == pMrrcDataMsg)
    {
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_ProcHoWaitSysInfoBufferMsg: Mem Alloc Fail");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_ProcHoWaitSysInfoBufferMsg_ENUM,LNAS_NULL_PTR);
        return;
    }

    /* 查找HO WAIT SYS INFO 缓存记录 */
    for (ulIndex = 0; ulIndex < ulCurSaveMsgNum; ++ulIndex)
    {
        if (VOS_TRUE == pEmmMrrcMgmtData->ulHoWaitSysInfoFlag)
        {
            /* 重发消息之后，当前指针指向的消息可能已经改变，所以需要将当前消息的OPID保存，
            用于后续清缓存使用*/
            ulMmRrcOpId = pEmmMrrcMgmtData->ulMmRrcOpId;

            if (NAS_EMM_MSG_SERVICE_REQ == pEmmMrrcMgmtData->enLastMsgId)
            {
                /* 重发SERVICE或者EXTENDED SERVICE REQ消息 */
                pMrrcDataMsg->enDataCnf = LRRC_LMM_DATA_CNF_NEED;

                pMrrcDataMsg->enEmmMsgType = NAS_EMM_MSG_SERVICE_REQ;
                pMrrcDataMsg->ulMsgId = ID_NAS_LMM_INTRA_MRRC_DATA_REQ;
                pMrrcDataMsg->ulEsmMmOpId = pEmmMrrcMgmtData->ulEsmMmOpId;

                pMrrcDataMsg->stNasMsg.ulNasMsgSize = pEmmMrrcMgmtData->ulNasMsgLength;

                /* 构造MRRC_DATA_REQ 中的 NAS_MSG_STRU,即CN消息(Compose the msg of): SER_REQ */
                NAS_EMM_SER_CompCnServiceReq(&(pMrrcDataMsg->stNasMsg));

                NAS_EMM_SndUplinkNasMsg(pMrrcDataMsg);

            }
            else if (NAS_EMM_MSG_EXTENDED_SERVICE_REQ == pEmmMrrcMgmtData->enLastMsgId)
            {
                /* 重发EXTENDED SERVICE REQ消息 */
                /* 函数重构 */
                NAS_EMM_ExtSerReqRetranProc(pEmmMrrcMgmtData->ulMmRrcOpId);
            }
            else if (NAS_EMM_MSG_TAU_CMP == pEmmMrrcMgmtData->enLastMsgId)
            {
                pMrrcDataMsg->enDataCnf = LRRC_LMM_DATA_CNF_NEED;

                pMrrcDataMsg->enEmmMsgType = NAS_EMM_MSG_TAU_CMP;
                pMrrcDataMsg->ulMsgId = ID_NAS_LMM_INTRA_MRRC_DATA_REQ;
                pMrrcDataMsg->ulEsmMmOpId = pEmmMrrcMgmtData->ulEsmMmOpId;

                pMrrcDataMsg->stNasMsg.ulNasMsgSize = pEmmMrrcMgmtData->ulNasMsgLength;

                NAS_LMM_MEM_CPY_S(  pMrrcDataMsg->stNasMsg.aucNasMsg,
                                    pEmmMrrcMgmtData->ulNasMsgLength,
                                    pEmmMrrcMgmtData->aucNasMsgContent,
                                    pEmmMrrcMgmtData->ulNasMsgLength);

                NAS_EMM_SndUplinkNasMsg(pMrrcDataMsg);

            }
            #if (FEATURE_LPP == FEATURE_ON)
            else if (NAS_EMM_NAS_UPLINK_GENERIC_NAS_TRANSPORT == pEmmMrrcMgmtData->enLastMsgId)
            {
                pMrrcDataMsg->enDataCnf             = LRRC_LMM_DATA_CNF_NEED;
                pMrrcDataMsg->enEmmMsgType          = NAS_EMM_NAS_UPLINK_GENERIC_NAS_TRANSPORT;
                pMrrcDataMsg->ulMsgId               = ID_NAS_LMM_INTRA_MRRC_DATA_REQ;
                pMrrcDataMsg->ulEmmLppOrSsOpId      = pEmmMrrcMgmtData->ulEmmLppOrSsOpId;
                pMrrcDataMsg->ulLppSsFlag           = pEmmMrrcMgmtData->ulLppSsFlag;

                pMrrcDataMsg->stNasMsg.ulNasMsgSize = pEmmMrrcMgmtData->ulNasMsgLength;
                NAS_LMM_MEM_CPY_S(  pMrrcDataMsg->stNasMsg.aucNasMsg,
                                    pEmmMrrcMgmtData->ulNasMsgLength,
                                    pEmmMrrcMgmtData->aucNasMsgContent,
                                    pEmmMrrcMgmtData->ulNasMsgLength);

                NAS_EMM_SndUplinkNasMsg(pMrrcDataMsg);
            }
            #endif
            else
            {

            }

            NAS_EMM_ClrDataReqBufferMsg(ulMmRrcOpId);
        }
        else
        {
            pEmmMrrcMgmtData++;
        }

    }
    /*释放所申请内存 */
    NAS_LMM_MEM_FREE(pMrrcDataMsg);
    return;
}
/* NO RF上行直传消息重传处理动作表 */
NAS_LMM_BUFFER_MSG_RETRAN_ACT_STRU  gstEmmBufferMsgActTbl[]=
{
    {NAS_EMM_MSG_EXTENDED_SERVICE_REQ,      NAS_EMM_ExtSerReqRetranProc},
};
VOS_UINT32        g_ulEmmBufferMsgActTblLen = sizeof(gstEmmBufferMsgActTbl)
                                                / sizeof(NAS_LMM_BUFFER_MSG_RETRAN_ACT_STRU);
/*******************************************************************************
  Function : NAS_EMM_ProcNoRfWaitSysInfoBufferMsg
  Input    : NONE
  Output   : NONE
  NOTE     : NO RF导致一些上行直传发送失败,在收到系统消息后一些需要重传
  Return   : NONE
  History  :
    1.leixiantiao 00258641     2015-02-04  NEW draf
*******************************************************************************/
VOS_VOID NAS_EMM_ProcNoRfWaitSysInfoBufferMsg( VOS_VOID )
{
    NAS_EMM_MRRC_MGMT_DATA_STRU         *pEmmMrrcMgmtData = NAS_EMM_NULL_PTR;
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          ulCurSaveMsgNum = 0;
    VOS_UINT32                          ulMmRrcOpId;
    NAS_LMM_BUFFER_MSG_RETRAN_ACT_FUN   pActFun;

    ulCurSaveMsgNum = g_ulSaveMsgNum;

    pEmmMrrcMgmtData                    = NAS_EMM_GET_MRRC_MGMT_DATA_ADDR();

    /* 查找HO WAIT SYS INFO 缓存记录 */
    for (ulIndex = 0; ulIndex < ulCurSaveMsgNum; ++ulIndex)
    {
        if (VOS_TRUE == pEmmMrrcMgmtData->ulNoRfWaitSysInfoFlag)
        {
            /* 重发消息之后，当前指针指向的消息可能已经改变，所以需要将当前消息的OPID保存，
            用于后续清缓存使用*/
            ulMmRrcOpId = pEmmMrrcMgmtData->ulMmRrcOpId;

            for(ulLoop = 0; ulLoop < g_ulEmmBufferMsgActTblLen; ulLoop++)
            {
                if(gstEmmBufferMsgActTbl[ulLoop].enMsgId == pEmmMrrcMgmtData->enLastMsgId)
                {
                    pActFun = gstEmmBufferMsgActTbl[ulLoop].pfMsgReTranFun;
                    if(VOS_NULL_PTR != pActFun)
                    {
                        (VOS_VOID)pActFun(pEmmMrrcMgmtData->ulMmRrcOpId);
                    }
                    break;
                }
            }
            NAS_EMM_ClrDataReqBufferMsg(ulMmRrcOpId);
        }
        else
        {
            pEmmMrrcMgmtData++;
        }
    }
    return;
}

NAS_LMM_BUFFER_MSG_RETRAN_ACT_STRU  gstEmmBufferMsgActConnRelTbl[]=
{
    {NAS_EMM_MSG_ESM,      NAS_EMM_EsmDataReqRetranProc},
};
VOS_UINT32        g_ulEmmBufferMsgActConnRelTblLen = sizeof(gstEmmBufferMsgActConnRelTbl)
                                                / sizeof(NAS_LMM_BUFFER_MSG_RETRAN_ACT_STRU);

/*******************************************************************************
  Function : NAS_EMM_ProcConnRelWaitSysInfoBufferMsg
  Input    : NONE
  Output   : NONE
  NOTE     : 处理由于流程对冲，RRC CONN REL导致上行直传发送失败,在收到系统消息后一些需要重传的情况
  Return   : NONE
  History  :
    1.chengmin 00285307     2015-02-04  draf enact
*******************************************************************************/
VOS_VOID NAS_EMM_ProcConnRelWaitSysInfoBufferMsg( VOS_VOID )
{
    NAS_EMM_MRRC_MGMT_DATA_STRU        *pEmmMrrcMgmtData = NAS_EMM_NULL_PTR;
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          ulCurSaveMsgNum = 0;
    VOS_UINT32                          ulMmRrcOpId;
    NAS_LMM_BUFFER_MSG_RETRAN_ACT_FUN   pActFun;

    ulCurSaveMsgNum                     = g_ulSaveMsgNum;

    pEmmMrrcMgmtData                    = NAS_EMM_GET_MRRC_MGMT_DATA_ADDR();

    /* 查找CONN REL WAIT SYS INFO 缓存记录 */
    for (ulIndex = 0; ulIndex < ulCurSaveMsgNum; ++ulIndex)
    {
        if (VOS_TRUE == pEmmMrrcMgmtData->ulConnRelWaitSysInfoFlag)
        {
            /* 重发消息之后，当前指针指向的消息可能已经改变，所以需要将当前消息的OPID保存，
            用于后续清缓存使用*/
            ulMmRrcOpId = pEmmMrrcMgmtData->ulMmRrcOpId;

            for(ulLoop = 0; ulLoop < g_ulEmmBufferMsgActConnRelTblLen; ulLoop++)
            {
                if(gstEmmBufferMsgActConnRelTbl[ulLoop].enMsgId == pEmmMrrcMgmtData->enLastMsgId)
                {
                    pActFun = gstEmmBufferMsgActConnRelTbl[ulLoop].pfMsgReTranFun;
                    if(VOS_NULL_PTR != pActFun)
                    {
                        pActFun(pEmmMrrcMgmtData->ulMmRrcOpId);
                    }
                    break;
                }
            }
            NAS_EMM_ClrDataReqBufferMsg(ulMmRrcOpId);
        }
        else
        {
            pEmmMrrcMgmtData++;
        }
    }
}




/*******************************************************************************
  Module   :
  Function : NAS_EMM_MsSerInitSsWaitCNCnfMsgSysInfoCommProc
  Input    :
  Output   :
  NOTE     : SERVICE_INIT+WAIT_CN_CNF状态下收到系统消息的公共处理
  Return   : VOS_UINT32
  History  :
    1.lihong 00150010       2012.12.20      新规作成
*******************************************************************************/
VOS_VOID NAS_EMM_MsSerInitSsWaitCNCnfMsgSysInfoCommProc( VOS_VOID )
{
    VOS_UINT32                          ulTaRslt    = NAS_EMM_FAIL;
    NAS_LMM_NETWORK_INFO_STRU           *pMmNetInfo = NAS_EMM_NULL_PTR;

    /* 获取EMM维护的网络信息*/
    pMmNetInfo                          = NAS_LMM_GetEmmInfoNetInfoAddr();


#if(FEATURE_ON == FEATURE_CSG)
    if((NAS_EMM_YES == NAS_LMM_IsCsgCampOn())
        &&(NAS_EMM_FAIL == NAS_EMM_TAU_IsCsgIdInAllowedOrOperatorCsgList()))
    {

        NAS_EMM_TAU_LOG_INFO("NAS_EMM_MsSerInitSsWaitCNCnfMsgSysInfoCommProc:CSGID not in CSG LIST.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsSerInitSsWaitCNCnfMsgSysInfoCommProc_ENUM,LNAS_FUNCTION_LABEL1);

        /*停止T3417定时器*/
        NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417);

        /*停止T3417ext定时器*/
        NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417_EXT);

        if (VOS_TRUE != NAS_EMM_SER_IsCsfbProcedure())
        {
            /*Inform RABM that SER fail*/
            NAS_EMM_SER_SendRabmReestInd(EMM_ERABM_REEST_STATE_FAIL);
        }

        /* 清除ulHoWaitSysInfoFlag标识存在的缓存记录 */
        (VOS_VOID)NAS_EMM_ClrWaitSysInfoBufferMsg();

        /*设置流程冲突标志位*/
        NAS_EMM_TAU_SaveEmmCollisionCtrl(NAS_EMM_COLLISION_SERVICE);

        if (NAS_EMM_SER_START_CAUSE_ESM_DATA_REQ_EMC == NAS_EMM_SER_GetEmmSERStartCause())
        {
            NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_ESM_EMC_PDN_REQ);
        }
        else
        {
            NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
        }

        /*启动TAU Procedure*/
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_NOT_IN_CSG_LIST);

        return;
    }
#endif

    /*判断TA不在TA List中，需要发起TAU Procedure,TA在上次注册的TA List中，忽略对当前系统消息的处理*/
    ulTaRslt = NAS_EMM_TAU_IsCurrentTAInTaList();
    if (NAS_EMM_FAIL == ulTaRslt)
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_MsSerInitSsWaitCNCnfMsgSysInfoCommProc:TA not in TAI LIST.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsSerInitSsWaitCNCnfMsgSysInfoCommProc_ENUM,LNAS_EMM_TA_NOT_IN_TA_LIST);

        /*停止T3417定时器*/
        NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417);

        /*停止T3417ext定时器*/
        NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417_EXT);

        if (VOS_TRUE != NAS_EMM_SER_IsCsfbProcedure())
        {
            /*Inform RABM that SER fail*/
            NAS_EMM_SER_SendRabmReestInd(EMM_ERABM_REEST_STATE_FAIL);
        }

        /* 清除ulHoWaitSysInfoFlag标识存在的缓存记录 */
        /* 修改函数名称 */
        (VOS_VOID)NAS_EMM_ClrWaitSysInfoBufferMsg();

        /*设置流程冲突标志位*/
        NAS_EMM_TAU_SaveEmmCollisionCtrl(NAS_EMM_COLLISION_SERVICE);

        if (NAS_EMM_SER_START_CAUSE_ESM_DATA_REQ_EMC == NAS_EMM_SER_GetEmmSERStartCause())
        {
            NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_ESM_EMC_PDN_REQ);
        }
        else
        {
            NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
        }

        /*启动TAU Procedure*/
        /* 新增入参TAU发起原因 */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_NOT_IN_TAI_LIST);
    }
    else
    {
        /*设置L.V.R TAI*/
        NAS_EMM_SetLVRTai(&pMmNetInfo->stPresentNetId);
        /* 针对网络侧缺陷优化:
           UE发送ESR消息,并且搜到网络发送成功消息的响应,此时发送X2接口的切换
           UE切换成功后,MME应该重新触发eNB发送CSFB流程,因为网络异常,CSFB流程没有发起来
           UE未收到重定向GU的异系统流程,导致T3417ext超时
           优化为:UE识别该场景,重新发送一次ESR,触发网络发起CSFB流程 */
        NAS_EMM_ProcHoRetransESRMsg();

        NAS_EMM_ProcHoWaitSysInfoBufferMsg();
        #if (FEATURE_ON == FEATURE_DSDS)
        /* 处理由于RF资源被抢导致上行直传没有发送成功需要重传的buffer */
        NAS_EMM_ProcNoRfWaitSysInfoBufferMsg();
        #endif

        if (NAS_LMM_REG_STATUS_EMC_REGED != NAS_LMM_GetEmmInfoRegStatus())
        {
            /*保存PS LOC信息*/
            NAS_LMM_WritePsLoc(NAS_NV_ITEM_UPDATE);
        }
        /* 网络信息更新,MMA不会立即更新网络信息,需要收到TAU IND才会更新,为规避该问题,
            LMM构造一条不带任何参数TAU IND消息上报给MMC */
        NAS_EMM_SetTauTypeNoProcedure();

        /*向MMC发送LMM_MMC_TAU_RESULT_IND消息*/
        NAS_EMM_MmcSendTauActionResultIndSuccWithoutPara();
    }
}

/*******************************************************************************
  Module   :
  Function : NAS_EMM_MsSerInitSsWaitCNCnfMsgForbiddenAnycellSysinfoProc
  Input    : None
  Output   : None
  NOTE     : SERVICE_INIT+WAIT_CN_CNF状态下收到被禁和ANYCELL系统消息处理
  Return   : VOS_UINT32
  History  :
    1.lihong 00150010       2012.12.20      新规作成
*******************************************************************************/
VOS_VOID NAS_EMM_MsSerInitSsWaitCNCnfMsgForbiddenAnycellSysinfoProc( VOS_VOID )
{
    if (NAS_LMM_REG_STATUS_NORM_REGED != NAS_LMM_GetEmmInfoRegStatus())
    {
        if ((NAS_EMM_SER_START_CAUSE_RRC_PAGING == NAS_EMM_SER_GetEmmSERStartCause())
            || (NAS_EMM_SER_START_CAUSE_RABM_REEST_EMC == NAS_EMM_SER_GetEmmSERStartCause()))
        {
            NAS_EMM_MsSerInitSsWaitCNCnfMsgSysInfoCommProc();
            return ;
        }

        if (VOS_TRUE == NAS_EMM_SER_IsCsfbProcedure())
        {
            /*向MMC发送LMM_MMC_SERVICE_RESULT_IND消息*/
            NAS_EMM_MmcSendSerResultIndOtherType( MMC_LMM_SERVICE_RSLT_FAILURE);
        }

        /* 终止SER流程*/
        NAS_EMM_SER_AbnormalOver();

        NAS_EMM_TAUSER_FSMTranState(    EMM_MS_REG,
                                        EMM_SS_REG_LIMITED_SERVICE,
                                        TI_NAS_EMM_STATE_NO_TIMER);

        /* 清空Service模块*/
        NAS_EMM_SER_ClearResource();

        NAS_EMM_RelReq(                 NAS_LMM_NOT_BARRED);

        return ;
    }

    if (VOS_TRUE == NAS_EMM_SER_IsCsfbProcedure())
    {
        /*向MMC发送LMM_MMC_SERVICE_RESULT_IND消息*/
        NAS_EMM_MmcSendSerResultIndOtherType( MMC_LMM_SERVICE_RSLT_FAILURE);
    }

    /* 终止SER流程*/
    NAS_EMM_SER_AbnormalOver();

    if (NAS_EMM_SER_START_CAUSE_ESM_DATA_REQ_EMC == NAS_EMM_SER_GetEmmSERStartCause())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_MsSerInitSsWaitCNCnfMsgForbiddenAnycellSysinfoProc: CAUSE_ESM_DATA_REQ_EMC.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsSerInitSsWaitCNCnfMsgForbiddenAnycellSysinfoProc_ENUM,LNAS_FUNCTION_LABEL1);

        NAS_EMM_EmcPndReqSerAbnormalCommProc(EMM_SS_DEREG_LIMITED_SERVICE);
    }
    else
    {
        /* 状态迁移:Reg.Limite_Service*/
        NAS_EMM_TAUSER_FSMTranState(    EMM_MS_REG,
                                        EMM_SS_REG_LIMITED_SERVICE,
                                        TI_NAS_EMM_STATE_NO_TIMER);
    }

    /* 清空Service模块*/
    NAS_EMM_SER_ClearResource();

    NAS_EMM_RelReq(                 NAS_LMM_NOT_BARRED);
}
/*******************************************************************************
  Module   :
  Function : NAS_EMM_MsSERInitSsWaitCNCnfMsgSysinfo
  Input    :
  Output   :
  NOTE     :
  Return   :
  History  :
    1.  Zhouyan 00125190    2008.09.10  新规作成
    2.zhengjunyan 00148421  2010-10-25  MOD:修改系统消息被禁的处理
    3.3.lihong 00150010     2012-02-27  Modify:CSFB
    4.wangchen 00209181     2012-08-21  Modify
    5.lihong 00150010       2012-12-13  Modify:Emergency
    6.lifuxin 00253982      2014-11-06  建链重构
*******************************************************************************/
VOS_UINT32 NAS_EMM_MsSerInitSsWaitCNCnfMsgSysinfo(VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru)
{

    VOS_UINT32                          ulRslt       = NAS_EMM_FAIL;
    EMMC_EMM_SYS_INFO_IND_STRU         *pstsysinfo   = NAS_EMM_NULL_PTR;
    EMMC_EMM_FORBIDDEN_INFO_ENUM_UINT32  ulForbiddenInfo = EMMC_EMM_NO_FORBIDDEN;
    (VOS_VOID)ulMsgId;
    NAS_EMM_TAU_LOG_INFO("NAS_EMM_MsSerInitSsWaitCNCnfMsgSysinfo entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsSerInitSsWaitCNCnfMsgSysinfo_ENUM,LNAS_ENTRY);

    /* 函数输入指针参数检查, 状态匹配检查,若不匹配,退出*/
    ulRslt = NAS_EMM_TAU_CHKFSMStateMsgp(EMM_MS_SER_INIT,EMM_SS_SER_WAIT_CN_SER_CNF,pMsgStru);
    if ( NAS_EMM_SUCC != ulRslt )
    {
        NAS_EMM_TAU_LOG_WARN("NAS_EMM_MsSerInitSsWaitCNCnfMsgSysinfo ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsSerInitSsWaitCNCnfMsgSysinfo_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    /* 获取系统消息*/
    pstsysinfo                          = (EMMC_EMM_SYS_INFO_IND_STRU*)pMsgStru;

    if(NAS_EMM_CONN_ESTING == NAS_EMM_GetConnState())
    {
        return  NAS_LMM_STORE_HIGH_PRIO_MSG;
    }
    /* 定制系统内切换到被禁小区,忽略被禁:当存在L小区A和B(属于俩TA)
        UE在小区B上驻留，由于MME某些异常,给UE下发原因值#15，但MME未将
        TA放入被禁列表中(未真被禁，只是临时被禁)，当UE收到#15原因值,
        主动释重新驻留在A小区，之后网侧让UE切换到B小区，而切换时LRRC
        不会判断小区是否被禁，LMM收到系统消息后，由B小区上收到过#15原
        因值,LMM主动释放进入限制服务态，LRRC释放后在小区A上驻留，从而导致乒乓切换 */
    ulForbiddenInfo = pstsysinfo->ulForbiddenInfo;
    if(NAS_EMM_YES == NAS_EMM_IsIntraHoIgnoreForbSysInfo())
    {
        /* 忽略FORBIDDEN TA FOR ROAMING,由于被#15原因值拒后,驻留的TA将放入FORBIDDEN TA LIST里,并从TAILIST里删除，所以后续发起TAU */
        if(EMMC_EMM_FORBIDDEN_TA_FOR_ROAMING == pstsysinfo->ulForbiddenInfo)
        {
            NAS_EMM_PUBU_LOG1_INFO("NAS_EMM_MsRegSsNormalMsgSysinfo Ignore ForbTaForRoaming:forbiddenInfo = ",
                               pstsysinfo->ulForbiddenInfo);
            TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsSerInitSsWaitCNCnfMsgSysinfo_ENUM,LNAS_EMM_FORB_INFO,
                               pstsysinfo->ulForbiddenInfo );
            ulForbiddenInfo = EMMC_EMM_NO_FORBIDDEN;
            #if (FEATURE_ON == FEATURE_PTM)
            NAS_EMM_ImprovePerformceeErrReport(EMM_OM_ERRLOG_IMPROVEMENT_TYPE_HO_TO_FORBIDDEN_TA);
            #endif
        }
    }
    /* 如果系统消息被禁，终止SER流程，释放连接*/
    if ((EMMC_EMM_NO_FORBIDDEN != ulForbiddenInfo)
            || (EMMC_EMM_CELL_STATUS_ANYCELL == pstsysinfo->ulCellStatus))
    {
        NAS_EMM_TAU_LOG_WARN("NAS_EMM_MsSerInitSsWaitCNCnfMsgSysinfo:CELL FORB.");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsSerInitSsWaitCNCnfMsgSysinfo_ENUM,LNAS_EMM_FORBIDDEN);

        NAS_EMM_MsSerInitSsWaitCNCnfMsgForbiddenAnycellSysinfoProc();

        return NAS_LMM_MSG_HANDLED;
    }

    NAS_EMM_MsSerInitSsWaitCNCnfMsgSysInfoCommProc();

    return NAS_LMM_MSG_HANDLED;
}
/*******************************************************************************
  Module   :
  Function : NAS_EMM_MsRegSsNormalServiceMsgIntraTauReq
  Input    :
  Output   :
  NOTE     :
  Return   :
  History  :
    1.  leili 00132387  2009.03.09  新规作成
    2.  X00148705                   NAS_EMM_TAU_UE_NET_CAP_BIT和NAS_EMM_TAU_DRX_BIT()在OM操作时已设置
    3.  X00148705       2009-11-17  修改依据不同的原因值发起TAU
    4.  sunbing 49683   2010.09.13  正常服务状态下收到参数变根的请求，如果之前有TAU没有成功，需要等定时器超时再发起TAU
*******************************************************************************/
VOS_UINT32 NAS_EMM_MsRegSsNormalServiceMsgIntraTauReq(VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru)
{

    NAS_LMM_INTRA_TAU_REQ_STRU         *pIntraTauReq = NAS_EMM_NULL_PTR;
    (VOS_VOID)ulMsgId;

    /* 打印进入该函数*/
    NAS_EMM_TAU_LOG_NORM(               "NAS_EMM_MsRegSsNormalServiceMsgIntraTauReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsNormalServiceMsgIntraTauReq_ENUM,LNAS_ENTRY);

    /* 函数输入指针参数检查*/
    if(NAS_EMM_NULL_PTR                 == pMsgStru)
    {
       NAS_EMM_TAU_LOG_ERR(             "NAS_EMM_MsRegSsNormalServiceMsgIntraTauReq TpCmdType Err!!");
       TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegSsNormalServiceMsgIntraTauReq_ENUM,LNAS_NULL_PTR);
       return NAS_LMM_MSG_DISCARD;
    }

    /* 判断是否存在上行Pending*/
    NAS_EMM_TAU_IsUplinkPending();
    /*如果内部TAU的类型为NAS_LMM_INTRA_TAU_TYPE_IMSI_ATTACH，无线能力变更类型为
    NAS_LMM_UE_RADIO_CAP_LTE_CHG，且存储的APP消息类型为ATTACH REQ，则回复ATTACH CNF，
    结果为MMC_LMM_ATT_RSLT_FAILURE*/
    pIntraTauReq = (NAS_LMM_INTRA_TAU_REQ_STRU*)pMsgStru;
    if((NAS_LMM_INTRA_TAU_TYPE_IMSI_ATTACH == pIntraTauReq->enIntraTauType)   &&
        (NAS_LMM_UE_RADIO_CAP_LTE_CHG == NAS_LMM_GetEmmInfoUeRadioCapChgFlag())&&
        (NAS_EMM_OK == NAS_EMM_CheckAppMsgPara(ID_MMC_LMM_ATTACH_REQ)))
      {
            NAS_EMM_MmcSendAttCnf(MMC_LMM_ATT_RSLT_FAILURE);
      }

    /* 如果上次TAU没有成功，则设置参数变更标识，等待T3411超时*/
    if ((NAS_EMM_YES == NAS_EMM_SER_AbnormalNeedtoContinueTau())
        &&(NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_T3411)))
    {
        NAS_LMM_SetEmmInfoDrxNetCapChange(NAS_EMM_YES);
        /*修改TAU发起原因*/
        /*NAS_EMM_TAU_SaveEmmTAUStartCause( NAS_EMM_TAU_START_CAUSE_INTRA_TAU_REQ);*/
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
    }
    else
    {
        NAS_LMM_SetEmmInfoDrxNetCapChange(NAS_EMM_YES);
        /*NAS_EMM_TAU_SaveEmmTAUStartCause( NAS_EMM_TAU_START_CAUSE_INTRA_TAU_REQ);*/
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);

        /* 新增入参TAU发起原因 */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_DRX_CHANGEED);
    }

    return NAS_LMM_MSG_HANDLED;

}

/*****************************************************************************
 Function Name   : NAS_EMM_MsRegSsNormalMsgBearerStatusReq
 Description     : Reg.Normal_Service状态下ESM本地修改承载上下文，触发TAU流程，
                   同步UE和MME两侧维护的承载上下文
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421     2011-1-11  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegSsNormalMsgBearerStatusReq( VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru )
{

    (VOS_VOID)ulMsgId;

    NAS_EMM_TAU_LOG_NORM("NAS_EMM_MsRegSsNormalMsgBearerStatusReq entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsNormalMsgBearerStatusReq_ENUM,LNAS_ENTRY);

    /* 函数输入指针参数检查*/
    if(NAS_EMM_NULL_PTR                 == pMsgStru)
    {
       NAS_EMM_TAU_LOG_ERR("NAS_EMM_MsRegSsNormalMsgBearerStatusReq:NULL PTR.");
       TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegSsNormalMsgBearerStatusReq_ENUM,LNAS_NULL_PTR);
       return NAS_LMM_MSG_DISCARD;
    }


    /* 如果上次TAU没有成功，则修改TAU触发原因，等待T3411超时*/
    if ((NAS_EMM_YES == NAS_EMM_SER_AbnormalNeedtoContinueTau())
        &&(NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_T3411)))
    {
        /*NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_BEARER_CNTXT_LOCAL_CHANGED);*/
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
        NAS_EMM_SetEpsContextStatusChange(NAS_EMM_EPS_BEARER_STATUS_CHANGEED);
    }
    else
    {
        /* 判断是否存在上行Pending*/
        NAS_EMM_TAU_IsUplinkPending();

        /* 触发TAU*/
        /*NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_BEARER_CNTXT_LOCAL_CHANGED);*/
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
        NAS_EMM_SetEpsContextStatusChange(NAS_EMM_EPS_BEARER_STATUS_CHANGEED);
        /* 新增入参TAU发起原因 */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_BEARER_STATUS_CHANGEED);
    }

    return NAS_LMM_MSG_HANDLED;

}

/*****************************************************************************
 Function Name   : NAS_EMM_MsRegSsRegAttemptUpdateMmMsgBearerStatusReq
 Description     : Reg.Attempting_to_update_mm状态下ESM本地修改承载上下文，
                    触发TAU流程，同步UE和MME两侧维护的承载上下文
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2011-7-12  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegSsRegAttemptUpdateMmMsgBearerStatusReq
(
    VOS_UINT32  ulMsgId,
    VOS_VOID   *pMsgStru
)
{
    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;
    NAS_EMM_TAU_LOG_NORM("NAS_EMM_MsRegSsRegAttemptUpdateMmMsgBearerStatusReq entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgBearerStatusReq_ENUM,LNAS_ENTRY);

    /* 函数输入指针参数检查*/
    if(NAS_EMM_NULL_PTR                 == pMsgStru)
    {
       NAS_EMM_TAU_LOG_ERR("NAS_EMM_MsRegSsRegAttemptUpdateMmMsgBearerStatusReq:NULL PTR.");
       TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgBearerStatusReq_ENUM,LNAS_NULL_PTR);
       return NAS_LMM_MSG_DISCARD;
    }

    /* 如果上次TAU没有成功，则修改TAU触发原因，等待T3411或者T3402超时*/
    if ((NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_T3402))
        ||(NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_T3411)))
    {
        /*NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_BEARER_CNTXT_LOCAL_CHANGED);*/
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
    }
    else
    {
        /* 判断是否存在上行Pending*/
        NAS_EMM_TAU_IsUplinkPending();

        /* 触发TAU*/
        /*NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_BEARER_CNTXT_LOCAL_CHANGED);*/
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
        /* 新增入参TAU发起原因 */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_BEARER_STATUS_CHANGEED);
    }

    return NAS_LMM_MSG_HANDLED;
}


/*****************************************************************************
 Function Name   : NAS_EMM_MsTauInitSsWaitCnCnfMsgBearerStatusReq
 Description     : TauInit.WtCnTauCnf状态下ESM本地修改了承载上下文，中止当前流程，
                   重新触发TAU.
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421  2011-1-12  Draft Enact
    2.lihong00150010        2012-12-14 Modify:Emergency

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsTauInitSsWaitCnCnfMsgBearerStatusReq(
                                                    VOS_UINT32  ulMsgId,
                                                    VOS_VOID   *pMsgStru )
{
    VOS_UINT32                          ulRslt = NAS_EMM_FAIL;

    (VOS_VOID)(ulMsgId);
    (VOS_VOID)(pMsgStru);
    NAS_EMM_TAU_LOG_NORM("NAS_EMM_MsTauInitSsWaitCnCnfMsgBearerStatusReq entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsTauInitSsWaitCnCnfMsgBearerStatusReq_ENUM,LNAS_ENTRY);

    /* 函数输入指针参数检查, 状态匹配检查,若不匹配,退出*/
    ulRslt = NAS_EMM_TAU_CHKFSMStateMsgp(EMM_MS_TAU_INIT,EMM_SS_TAU_WAIT_CN_TAU_CNF,pMsgStru);
    if ( NAS_EMM_SUCC != ulRslt )
    {
        NAS_EMM_TAU_LOG_WARN("NAS_EMM_TAUSER_CHKFSMStateMsgp ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsTauInitSsWaitCnCnfMsgBearerStatusReq_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

     /*终止当前TAU流程*/
    NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_TAU_T3430);

    #if (FEATURE_ON == FEATURE_DSDS)
    /*发送end notify消息给RRC，通知RRC释放资源*/
    NAS_EMM_TAU_SendRrcDsdsEndNotify();
    #endif

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    NAS_EMM_SendMtcTAUEndType();
#endif

    NAS_EMM_TAU_SaveEmmTAUAttemptCnt(NAS_EMM_TAU_ATTEMPT_CNT_ZERO);

    NAS_EMM_TAU_ProcAbnormal();
    if (NAS_EMM_TAU_START_CAUSE_ESM_EMC_PDN_REQ == NAS_EMM_TAU_GetEmmTAUStartCause())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_MsTauInitSsWaitCNCnfMsgSysinfo:CAUSE_ESM_EMC_PDN_REQ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsTauInitSsWaitCnCnfMsgBearerStatusReq_ENUM,LNAS_FUNCTION_LABEL1);

        NAS_EMM_EmcPndReqTauAbnormalCommProc(   NAS_EMM_MmcSendTauActionResultIndFailWithPara,
                                                (VOS_VOID*)NAS_EMM_NULL_PTR,
                                                EMM_SS_DEREG_NORMAL_SERVICE);
    }
    else
    {
        /* 上报TAU结果在冲突处理中执行 */
        NAS_EMM_TAU_RelIndCollisionProc(NAS_EMM_MmcSendTauActionResultIndFailWithPara,
                             (VOS_VOID*)NAS_EMM_NULL_PTR);
    }
    /*向MRRC发送NAS_EMM_MRRC_REL_REQ消息*/
    NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);

    return  NAS_LMM_MSG_HANDLED;
}
/*****************************************************************************
 Function Name   : NAS_EMM_MsRegSsNoVailableCellMsgT3412Exp
 Description     : REG+NO_VAILABLE_CELL状态下收到T3412定时器超时
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.    lihong  00150010      2011-08-26  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegSsNoVailableCellMsgT3412Exp
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                     *pMsgStru
)
{
    (VOS_VOID)ulMsgId;

    /* 打印进入该函数*/
    NAS_EMM_TAU_LOG_INFO( "NAS_EMM_MsRegSsNoVailableCellMsgT3412Exp is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsNoVailableCellMsgT3412Exp_ENUM,LNAS_ENTRY);

    /* 函数输入指针参数检查*/
    if(NAS_EMM_NULL_PTR == pMsgStru)
    {
        NAS_EMM_TAU_LOG_ERR("NAS_EMM_MsRegSsNoVailableCellMsgT3412Exp PARA NULL!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegSsNoVailableCellMsgT3412Exp_ENUM,LNAS_NULL_PTR);
        return NAS_LMM_MSG_DISCARD;
    }

    /* 协议24301 5.3.5章节描述，在REG+NO_AVAILABLE_CELL状态下，T3412超时，如果
       ISR激活，就启动T3423定时器;如果ISR没有激活，如果
       当前是联合注册成功，则回到REG+NORMAL_SERVICE态后，发起联合TAU，TAU类型为
       combined TA/LA updating with IMSI attach；如果不是联合注册成功，则发起周期性TAU */

    /*设置周期TAU定制器超时标志*/
    NAS_LMM_SetEmmInfoT3412ExpCtrl(NAS_EMM_T3412_EXP_YES_REG_NO_AVALABLE_CELL);

    if (MMC_LMM_TIN_RAT_RELATED_TMSI == NAS_EMM_GetTinType())
    {
        /*启动定时器T3423*/
        NAS_LMM_StartPtlTimer(TI_NAS_EMM_PTL_T3423);

        /*通知GU模T3423启动*/
        NAS_EMM_SendTimerStateNotify(TI_NAS_EMM_PTL_T3423, LMM_MMC_TIMER_START);

    }
    return NAS_LMM_MSG_HANDLED;

}

VOS_UINT32  NAS_EMM_MsRegSsAnyStatusMsgT3412Exp( VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru )
{
    (VOS_VOID)ulMsgId;

    /* 打印进入该函数*/
    NAS_EMM_TAU_LOG_INFO( "NAS_EMM_MsRegSsAnyStatusMsgT3412Exp is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsAnyStatusMsgT3412Exp_ENUM,LNAS_ENTRY);

    /* 函数输入指针参数检查*/
    if(NAS_EMM_NULL_PTR == pMsgStru)
    {
        NAS_EMM_TAU_LOG_ERR("NAS_EMM_MsRegSsAnyStatusMsgT3412Exp PARA NULL!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegSsAnyStatusMsgT3412Exp_ENUM,LNAS_NULL_PTR);
        return NAS_LMM_MSG_DISCARD;
    }

    /* 针对GCF9.2.3.1.5 用例临时方案 ,UE丢网,MMC发起搜网 ,搜网期间T3412超时,发起的TAU类型是combined TAU with IMSI类型，
       而仪器测试中,存在现网干扰下,UE在现网上受限驻留,导致无法转到no cell态。
       针对GCF测试，该场景TAU定时器超时标志置为REG_NO_AVALABLE_CELL */
    if((PS_SUCC == LPS_OM_IsTestMode())
        &&(EMM_MS_REG == NAS_LMM_GetEmmCurFsmMS())
        &&(EMM_SS_REG_LIMITED_SERVICE == NAS_LMM_GetEmmCurFsmSS()))
    {
        /*设置周期TAU定制器超时标志*/
        NAS_LMM_SetEmmInfoT3412ExpCtrl(NAS_EMM_T3412_EXP_YES_REG_NO_AVALABLE_CELL);
    }
    else
    {
        /*设置周期TAU定制器超时标志*/
        NAS_LMM_SetEmmInfoT3412ExpCtrl(NAS_EMM_T3412_EXP_YES_OTHER_STATE);
    }


    if (MMC_LMM_TIN_RAT_RELATED_TMSI == NAS_EMM_GetTinType())
    {
        /*启动定时器T3423*/
        NAS_LMM_StartPtlTimer(TI_NAS_EMM_PTL_T3423);

        /*通知GU模T3423启动*/
        NAS_EMM_SendTimerStateNotify(TI_NAS_EMM_PTL_T3423, LMM_MMC_TIMER_START);

    }
    return NAS_LMM_MSG_HANDLED;

}


VOS_UINT32  NAS_EMM_MsRegSsSomeStatusMsgIntraTauReq( VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru )
{
    NAS_LMM_INTRA_TAU_REQ_STRU         *pIntraTauReq = NAS_EMM_NULL_PTR;
    (VOS_VOID)ulMsgId;
    pIntraTauReq    = (NAS_LMM_INTRA_TAU_REQ_STRU*)pMsgStru;

    /* 打印进入该函数*/
    NAS_EMM_TAU_LOG_INFO(               "NAS_EMM_MsRegSsSomeStatusMsgIntraTauReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsSomeStatusMsgIntraTauReq_ENUM,LNAS_ENTRY);

    /* 函数输入指针参数检查*/
    if(NAS_EMM_NULL_PTR                 == pMsgStru)
    {
        NAS_EMM_TAU_LOG_ERR(            "NAS_EMM_MsRegSsSomeStatusMsgIntraTauReq PARA NULL!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegSsSomeStatusMsgIntraTauReq_ENUM,LNAS_NULL_PTR);
        return NAS_LMM_MSG_DISCARD;
    }

    /*设置DRX或NetCapability改变标志*/
    if(NAS_LMM_INTRA_TAU_TYPE_PARA_CHANGE == pIntraTauReq->enIntraTauType)
    {
        NAS_LMM_SetEmmInfoDrxNetCapChange( NAS_EMM_YES);
    }

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsRegSsSomeStateMsgBearerStatusReq
 Description     : Reg.Limite_Service
                   Reg.No_Cell_Available
                   Reg.Plmn_Search
                   这三个状态下，ESM本地修改承载上下文，记录标志
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421    2011-1-11  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegSsSomeStateMsgBearerStatusReq( VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru )
{
    NAS_EMM_TAU_LOG_INFO("NAS_EMM_MsRegSsSomeStateMsgBearerStatusReq entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsSomeStateMsgBearerStatusReq_ENUM,LNAS_ENTRY);
    (VOS_VOID)ulMsgId;

    /* 函数输入指针参数检查*/
    if(NAS_EMM_NULL_PTR == pMsgStru)
    {
        NAS_EMM_TAU_LOG_ERR("NAS_EMM_MsRegSsSomeStateMsgBearerStatusReq:NULL PTR.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegSsSomeStateMsgBearerStatusReq_ENUM,LNAS_NULL_PTR);
        return NAS_LMM_MSG_DISCARD;
    }

    /* 设置承载上下文变化*/
    NAS_EMM_SetEpsContextStatusChange(NAS_EMM_EPS_BEARER_STATUS_CHANGEED);

    return NAS_LMM_MSG_HANDLED;
}
/*****************************************************************************
 Function Name   : NAS_EMM_MsRegSsLimitedSrvMsgRrcRelInd
 Description     : 在Reg.LimitedService状态下收到LRRC_LMM_REL_IND消息的处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2011-9-24  Draft Enact
    2.lihong00150010      2012-12-19 Modify:Emergency

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegSsLimitedSrvMsgRrcRelInd
(
    VOS_UINT32                              ulMsgId,
    VOS_VOID                                *pMsgStru
)
{
    LRRC_LMM_REL_IND_STRU              *pMsgRrcRelInd  = (LRRC_LMM_REL_IND_STRU *)pMsgStru;
    VOS_UINT32                          ulCause;

    (VOS_VOID)ulMsgId;

    NAS_EMM_TAU_LOG_NORM("NAS_EMM_MsRegSsLimitedSrvMsgRrcRelInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsLimitedSrvMsgRrcRelInd_ENUM,LNAS_ENTRY);

    /*获得原因值*/
    ulCause = pMsgRrcRelInd->enRelCause;

    NAS_EMM_MsRegSsNmlSrvProcMsgRrcRelInd(ulCause);

    return NAS_LMM_MSG_HANDLED;
}
/*****************************************************************************
 Function Name   : NAS_LMM_PreProcIntraTauReq
 Description     : 处理NAS_LMM_INTRA_TAU_TYPE_UPDATE_MM类型的内部TAU，其他类型
                   的内部TAU进状态机处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2011-11-16  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LMM_PreProcIntraTauReq
(
    MsgBlock                           *pMsg
)
{
    NAS_LMM_INTRA_TAU_REQ_STRU         *pEmmIntraTauReq = VOS_NULL_PTR;
    VOS_UINT32                          ulCurEmmStat;

    NAS_EMM_TAU_LOG_INFO("NAS_LMM_PreProcIntraTauReq is enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcIntraTauReq_ENUM,LNAS_ENTRY);

    pEmmIntraTauReq                     = (VOS_VOID*)pMsg;
    ulCurEmmStat = NAS_LMM_PUB_COMP_EMMSTATE(NAS_EMM_CUR_MAIN_STAT,
                                            NAS_EMM_CUR_SUB_STAT);

    /*
    改动背景: 异系统TAU被bar，解bar之后发起TAU的时候存在连续发
    两次TAU的场景，第一次TAU发起原因: CSFB到G做过LAU，回到L然后
    设置为ps only，然后在reg-update_mm状态的时候发起内部TAU，
    在预处理的时候会发TAU. 第二次TAU发起原因:TAU被bar之后，收到
    解bar之后需要立即发起TAU。
    如何改动: 发起第二次TAU的时候发起建链的时候，高优先级缓存
    该内部TAU消息，等到稳态的时候再发。
    */
    if((NAS_EMM_CONN_RELEASING == NAS_EMM_GetConnState())
        || (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsStaTimerRunning(TI_NAS_EMM_STATE_T3440))
        || (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_REATTACH_DELAY))
        || (NAS_EMM_CONN_ESTING == NAS_EMM_GetConnState()))
    {
        NAS_EMM_TAU_LOG_INFO("NAS_LMM_PreProcIntraTauReq: REL_INIT or EST_INIT is high priority store");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcIntraTauReq_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_LMM_STORE_HIGH_PRIO_MSG;
    }

    if (EMM_MS_TAU_INIT == NAS_LMM_GetEmmCurFsmMS())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_LMM_PreProcIntraTauReq: EMM_MS_TAU_INIT is discard");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcIntraTauReq_ENUM,LNAS_FUNCTION_LABEL2);
        return NAS_LMM_MSG_HANDLED;
    }

    /* 预处理中只处理UPDATE_MM类型的内部TAU */
    /*只有在reg+normal_service以及reg+attempt_updata_mm的时候才发送TAU*/
    if ((NAS_LMM_INTRA_TAU_TYPE_UPDATE_MM == pEmmIntraTauReq->enIntraTauType) &&
         ((ulCurEmmStat == NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_NORMAL_SERVICE)) ||
          (ulCurEmmStat == NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM))))
    {
        /* 清除UPDATE_MM标识 */
        /*NAS_LMM_SetEmmInfoUpdateMmFlag(NAS_EMM_UPDATE_MM_FLAG_INVALID);*/

        if (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_T3411))
        {
            NAS_EMM_TAU_LOG_NORM("NAS_LMM_PreProcIntraTauReq:3411 is running");
            TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcIntraTauReq_ENUM,LNAS_EMM_T3411_RUNNING);

            /*修改状态：进入主状态REG子状态REG_ATTEMPTING_TO_UPDATE_MM*/
            NAS_EMM_AdStateConvert(         EMM_MS_REG,
                                            EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM,
                                            TI_NAS_EMM_STATE_NO_TIMER);
        }
        else if (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_T3402))
        {
            NAS_EMM_TAU_LOG_NORM("NAS_LMM_PreProcIntraTauReq:3402 is running");
            TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcIntraTauReq_ENUM,LNAS_EMM_T3402_RUNNING);

            /*修改状态：进入主状态REG子状态REG_ATTEMPTING_TO_UPDATE_MM*/
            NAS_EMM_AdStateConvert(         EMM_MS_REG,
                                            EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM,
                                            TI_NAS_EMM_STATE_NO_TIMER);
        }
        else
        {
            NAS_EMM_TAU_LOG_NORM("NAS_LMM_PreProcIntraTauReq:3411 and 3402 is not running");
            TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcIntraTauReq_ENUM,LNAS_FUNCTION_LABEL3);

            /* 判断是否存在上行Pending*/
            NAS_EMM_TAU_IsUplinkPending();

            /*启动TAU Procedure*/
            /*NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_IMSI_ATTACH);*/
            NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
            /* 新增入参TAU发起原因 */
            NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_OTHERS);
        }

        return NAS_LMM_MSG_HANDLED;
    }

    return NAS_LMM_MSG_DISCARD;
}
/*****************************************************************************
 Function Name   : NAS_LMM_SendMmcUtranModeCnf
 Description     : 向MMC发送ID_LMM_MMC_UTRAN_MODE_CNF消息
 Input           : VOS_VOID
 Output          : None
 Return          : NAS_EMM_SEND_RRC_OK   发送成功
                   NAS_EMM_SEND_RRC_ERR  发送失败
 History         :
    1.sunjitan 00193151      2012-07-21  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LMM_SendMmcUtranModeCnf(VOS_VOID)
{
    LMM_MMC_UTRAN_MODE_CNF_STRU  *pstLmmUtranModCnf = NAS_EMM_NULL_PTR;

    /*分配内存*/
    /* 申请MMC内部消息 */
    pstLmmUtranModCnf  = (VOS_VOID*)NAS_LMM_GetLmmMmcMsgBuf(sizeof(LMM_MMC_UTRAN_MODE_CNF_STRU));
    if(NAS_EMM_NULL_PTR == pstLmmUtranModCnf)
    {
        NAS_EMM_PUBU_LOG_WARN("NAS_LMM_SendMmcUtranModeCnf: MSG ALLOC ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_SendMmcUtranModeCnf_ENUM,LNAS_NULL_PTR);
        return NAS_EMM_SEND_MMC_ERR;
    }

    /*清空申请到的消息空间*/
    NAS_LMM_MEM_SET_S(  pstLmmUtranModCnf,
                        sizeof(LMM_MMC_UTRAN_MODE_CNF_STRU),
                        0,
                        sizeof(LMM_MMC_UTRAN_MODE_CNF_STRU));

    /* 填充给MMC的DOPRA头 */
    EMM_PUBU_COMP_MMC_MSG_HEADER(pstLmmUtranModCnf,
                                 sizeof(LMM_MMC_UTRAN_MODE_CNF_STRU) -
                                 EMM_LEN_VOS_MSG_HEADER);

    /* 填充消息ID */
    pstLmmUtranModCnf->ulMsgId       = ID_LMM_MMC_UTRAN_MODE_CNF;

    /* 发送LMM_MMC_UTRAN_MODE_CNF消息 */
    NAS_LMM_SendLmmMmcMsg(pstLmmUtranModCnf);

    return NAS_EMM_SEND_MMC_OK;
}

/*****************************************************************************
 Function Name   : NAS_LMM_SendRrcUtranModeNotifyReq
 Description     : 向RRC发送ID_LRRC_LMM_UTRAN_MODE_NTF消息
 Input           : RRC_NAS_UTRAN_MODE_ENUM_UINT8
 Output          : None
 Return          : NAS_EMM_SEND_RRC_OK   发送成功
                   NAS_EMM_SEND_RRC_ERR  发送失败
 History         :
    1.sunjitan 00193151      2012-07-21  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LMM_SendRrcUtranModeReq
(
    LRRC_LNAS_UTRAN_MODE_ENUM_UINT8       enUtranMode
)
{
    LRRC_LMM_UTRAN_MODE_REQ_STRU  *pstLmmUtranModReq = NAS_EMM_NULL_PTR;

    /*分配内存*/
    pstLmmUtranModReq = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(LRRC_LMM_UTRAN_MODE_REQ_STRU));
    if(NAS_EMM_NULL_PTR == pstLmmUtranModReq)
    {
        return NAS_EMM_SEND_RRC_ERR;
    }

    /*清空申请到的消息空间*/
    NAS_LMM_MEM_SET_S(  pstLmmUtranModReq,
                        sizeof(LRRC_LMM_UTRAN_MODE_REQ_STRU),
                        0,
                        sizeof(LRRC_LMM_UTRAN_MODE_REQ_STRU));

    /*填充VOS消息头*/
    NAS_EMM_SET_RRC_MSG_HEADER(pstLmmUtranModReq, sizeof(LRRC_LMM_UTRAN_MODE_REQ_STRU)-VOS_MSG_HEAD_LENGTH);

    /* 填充消息ID */
    pstLmmUtranModReq->enMsgId       = ID_LRRC_LMM_UTRAN_MODE_REQ;

    /* 填充消息体 */
    pstLmmUtranModReq->enUtranMode   = enUtranMode;

    /* 发送ID_LRRC_LMM_UTRAN_MODE_NTF */
    NAS_LMM_SEND_MSG(pstLmmUtranModReq);

    return NAS_EMM_SEND_RRC_OK;
}
/*lint +e961*/
/*lint +e960*/


/*****************************************************************************
 Function Name   : NAS_LMM_PreProcUtranModeNotifyReq
 Description     :  对MMC发来的修改Utran能力的指示进行预处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunjitan 00193151      2012-07-21  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LMM_PreProcMmcUtranModeReq( MsgBlock  *pMsg )
{
    MMC_LMM_UTRAN_MODE_REQ_STRU     *pstMmcUtranModReq = NAS_EMM_NULL_PTR;

    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_PreProcUtranModeReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcMmcUtranModeReq_ENUM,LNAS_ENTRY);

    pstMmcUtranModReq = (MMC_LMM_UTRAN_MODE_REQ_STRU *)(VOS_VOID *)pMsg;

    if ( NAS_EMM_NULL_PTR == pstMmcUtranModReq )
    {
        NAS_EMM_PUBU_LOG_ERR("NAS_LMM_PreProcUtranModeReq: NULL  Msg!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_PreProcMmcUtranModeReq_ENUM,LNAS_NULL_PTR);
        return NAS_LMM_MSG_HANDLED;
    }

    /* 只有开机完成或收到系统消息MMC才可能下发，因此开关机过程中收到丢弃 */
    if ( EMM_MS_NULL == NAS_EMM_CUR_MAIN_STAT )
    {
        NAS_LMM_PUBM_LOG_INFO("NAS_LMM_PreProcUtranModeReq : Power_on or power_off, discard message!");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcMmcUtranModeReq_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_LMM_MSG_HANDLED;
    }

    /* 收到的模式变更类型非法，丢弃 */
    if ( MMC_LMM_UTRAN_MODE_BUTT <= pstMmcUtranModReq->enUtranMode )
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_PreProcUtranModeReq: ERROR: Utran mode is invalid.");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_PreProcMmcUtranModeReq_ENUM,LNAS_FUNCTION_LABEL2);
        return NAS_LMM_MSG_HANDLED;
    }

    /*sunbing 49683 2013-10-14 VoLTE begin*/
    /*记录UTRAN模式，在classmark3编码时需要*/
    NAS_LMM_SetEmmInfoUtranMode(pstMmcUtranModReq->enUtranMode);
    /*sunbing 49683 2013-10-14 VoLTE end*/

    /* 向RRC发系统配置请求消息*/
    (VOS_VOID)NAS_LMM_SendRrcUtranModeReq(pstMmcUtranModReq->enUtranMode);

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_LMM_PreProcRrcUtranModeNotifyCnf
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32
 History         :
    1.sunjitan 00193151     2012-07-21  Draft Enact
    2.lihong 00150010       2012-12-22  Modify:DTS2012121306127，系统消息机制变更
*****************************************************************************/
VOS_UINT32  NAS_LMM_PreProcRrcUtranModeCnf( MsgBlock  *pMsg )
{
    /*VOS_UINT32                            ulRslt = NAS_LMM_MSG_DISCARD;*/
    LRRC_LMM_UTRAN_MODE_CNF_STRU  *pstRrcUtranModCnf = NAS_EMM_NULL_PTR;

    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_PreProcRrcUtranModeCnf  is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcRrcUtranModeCnf_ENUM,LNAS_ENTRY);

    pstRrcUtranModCnf = (LRRC_LMM_UTRAN_MODE_CNF_STRU*)(VOS_VOID*)pMsg;

    if (NAS_EMM_NULL_PTR == pstRrcUtranModCnf)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_PreProcRrcUtranModeCnf: NULL  Msg!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_PreProcRrcUtranModeCnf_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_HANDLED;
    }

    /* Utran能力未发生变化 */
    if (LRRC_LNAS_UE_CAPABILITY_CHANGE != pstRrcUtranModCnf->enCapChangeInd)
    {
        NAS_LMM_PUBM_LOG_INFO("NAS_LMM_PreProcRrcUtranModeNotifyCnf: Utran mode isn't changed.");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcRrcUtranModeCnf_ENUM,LNAS_FUNCTION_LABEL1);

        /* 给MMC回成功 */
        (VOS_VOID)NAS_LMM_SendMmcUtranModeCnf();
        return NAS_LMM_MSG_HANDLED;
    }

    /* Utran能力发生变化 */
    /* 无论主从模，只要不是非注册态，均进入 */
    if (NAS_EMM_NO == NAS_EMM_IsDeregState())
    {
        /* 只有当前不是LTE能力变更或GU能力变更时才记录，防止冲掉LTE变更 */
        if ( NAS_LMM_UE_RADIO_CAP_NOT_CHG == NAS_LMM_GetEmmInfoUeRadioCapChgFlag() )
        {
            /* 记录Utran能力的变化情况*/
            NAS_LMM_SetEmmInfoUeRadioCapChgFlag(NAS_LMM_UE_RADIO_CAP_GU_CHG);
        }
    }


    /* 如果是DEREG态则不处理*/
    /* 给MMC回成功 */
    (VOS_VOID)NAS_LMM_SendMmcUtranModeCnf();

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_IsIntraHoIgnoreForbSysInfo
 Description     : 定制系统内切换到被禁小区,忽略被禁:当存在L小区A和B(A能力稍差)
                    UE在小区B上驻留，由于MME某些异常,给UE下发原因值#15，但MME未将
                    TA放入被禁列表中(未真被禁，只是临时被禁)，当UE收到#15原因值,
                    主动释重新驻留在A小区，之后网侧让UE切换到B小区，而切换时LRRC
                    不会判断小区是否被禁，LMM收到系统消息后，由B小区上收到过#15原
                    因值,LMM主动释放进入限制服务态，LRRC释放后在小区A上驻留，从而导致乒乓切换
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    leixiantiao 00258641 2015-6-3  初稿
*****************************************************************************/
VOS_UINT32 NAS_EMM_IsIntraHoIgnoreForbSysInfo(VOS_VOID)
{
    /* 非测试卡,NV开关打开且当前连接状态为连接态时忽略被禁 */
    if((PS_TRUE == g_ulIntraHoIgnoreForbidTaFlag)
        &&(PS_SUCC != LPS_OM_IsTestMode())
        &&(NAS_EMM_CONN_DATA == NAS_EMM_GetConnState()))
    {
        return NAS_EMM_YES;
    }
    return NAS_EMM_NO;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif




