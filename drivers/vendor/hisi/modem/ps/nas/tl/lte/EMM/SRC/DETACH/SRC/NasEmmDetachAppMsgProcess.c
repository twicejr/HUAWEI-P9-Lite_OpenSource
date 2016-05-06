


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/

#include    "NasEmmAttDetInclude.h"
#include    "NasLmmPubMPrint.h"
#include    "MmcLmmInterface.h"
#if (FEATURE_LPP == FEATURE_ON)
#include    "NasEmmLppMsgProc.h"
#include    "EmmLppInterface.h"
#include    "NasEmmSsMsgProc.h"
#include    "NasEmmSerProc.h"
#endif

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASEMMDETACHAPPMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASEMMDETACHAPPMSGPROC_C
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


/*****************************************************************************
  3 Function
*****************************************************************************/

/*****************************************************************************
 Function Name   : NAS_EMM_AppDetachReqMsgChk
 Description     : 检查APP发送消息内容是否正确
 Input           :
 Output          :
 Return          :

 History         :
    1.leili 00132387         2008-09-09  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_AppDetachReqMsgChk(const MMC_LMM_DETACH_REQ_STRU *pMsgMsg)
{

    /*消息内容检查 */
    if ((MMC_LMM_MO_DET_PS_ONLY == pMsgMsg->ulDetachType) ||
        (MMC_LMM_MO_DET_CS_ONLY == pMsgMsg->ulDetachType) ||
        (MMC_LMM_MO_DET_CS_PS == pMsgMsg->ulDetachType))
    {
        return  NAS_EMM_PARA_VALID;

    }
    else
    {
        return  NAS_EMM_PARA_INVALID;

    }

}


/*****************************************************************************
 Function Name   : NAS_EMM_MsRegInitSsWtCnAttCnfMsgAppDetachReq
 Description     : 主状态REG_INIT+子状态WAIT_CN_ATTACH_CNF下收到应用层的DETACH
                   REQUEST消息

 Input           :

 Return          :

 History         :
    1.leili 00132387    2008-09-09  Draft Enact
    2.lihong00150010    2012-11-01  Modify:emgergency

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegInitSsWtCnAttCnfMsgAppDetachReq(VOS_UINT32  ulMsgId,
                                                         VOS_VOID   *pMsgStru )
{
    MMC_LMM_DETACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_DETACH_REQ_STRU *) pMsgStru;

    /*打印进入该函数*/
    NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MsRegInitSsWtCnAttCnfMsgAppDetachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegInitSsWtCnAttCnfMsgAppDetachReq_ENUM,LNAS_ENTRY);

    /*检查状态是否匹配，若不匹配，退出*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG_INIT,EMM_SS_ATTACH_WAIT_CN_ATTACH_CNF))
    {
        /*打印出错信息*/
        NAS_EMM_DETACH_LOG_WARN("NAS_EMM_MsRegInitSsWtCnAttCnfMsgAppDetachReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegInitSsWtCnAttCnfMsgAppDetachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*消息内容检查,若有错，打印并退出*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppDetachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_DETACH_LOG_ERR("NAS_EMM_MsRegInitSsWtCnAttCnfMsgAppDetachReq: MMC_LMM_DETACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegInitSsWtCnAttCnfMsgAppDetachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }

    /* 如果是IMSI DETACH，则本地CS域DETACH，直接回复成功 */
    if (MMC_LMM_MO_DET_CS_ONLY == NAS_EMM_GLO_AD_GetDetTypeMo())
    {
        if (EMM_ATTACH_CAUSE_ESM_EMC_ATTACH == NAS_EMM_GLO_AD_GetAttCau())
        {
            NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MsRegInitSsWtCnAttCnfMsgAppDetachReq:receive cs detach during emergency attach!");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegInitSsWtCnAttCnfMsgAppDetachReq_ENUM,LNAS_FUNCTION_LABEL1);
            NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);
            return   NAS_LMM_MSG_HANDLED;
        }

        /*向MMC发送LMM_MMC_ATTACH_CNF或LMM_MMC_ATTACH_IND消息*/
        NAS_EMM_AppSendAttOtherType(MMC_LMM_ATT_RSLT_MO_DETACH_FAILURE);

        /*保存APP参数*/
        NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId, pRcvEmmMsg->ulOpId);

        /*停止定时器T3410*/
        NAS_LMM_StopStateTimer(          TI_NAS_EMM_T3410);

        /*修改状态：进入主状态DEREG子状态DEREG_NORMAL_SERVICE*/
        NAS_EMM_AdStateConvert(             EMM_MS_DEREG,
                                            EMM_SS_DEREG_PLMN_SEARCH,
                                            TI_NAS_EMM_STATE_NO_TIMER);
        /*向MMC发送APP_MM_DETACH_CNF*/
        NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);

        if (EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER == NAS_EMM_GLO_AD_GetAttCau())
        {
            NAS_EMM_AttResetAttAttempCounter();

            /* 通知ESM紧接着EMM还要做紧急注册，ESM不需要清除动态表中的紧急PDN建立记录 */
            NAS_EMM_AttSendEsmResult(EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);
        }
        else
        {
            /*向ESM发送ID_EMM_ESM_STATUS_IND消息*/
            NAS_EMM_EsmSendStatResult(EMM_ESM_ATTACH_STATUS_DETACHED);
        }

        /* 本地DETACH释放资源:动态内存、赋初值 */
        NAS_LMM_DeregReleaseResource();

        /* 如果处于CONN态,释放连接*/
        if (NAS_EMM_CONN_IDLE != NAS_EMM_GetConnState())
        {
            NAS_EMM_RelReq(                 NAS_LMM_NOT_BARRED);

        }

        return  NAS_LMM_MSG_HANDLED;
    }

    /*向MMC发送LMM_MMC_ATTACH_CNF或LMM_MMC_ATTACH_IND消息*/
    NAS_EMM_AppSendAttOtherType(MMC_LMM_ATT_RSLT_MO_DETACH_FAILURE);

    /*保存APP参数*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId, pRcvEmmMsg->ulOpId);

    /*停止定时器T3410*/
    NAS_LMM_StopStateTimer(          TI_NAS_EMM_T3410);

    /*发送DETACH REQUEST消息*/
    NAS_EMM_SendDetachReqMo();

    return   NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsRegSsAnyMsgAppStopReq
 Description     : 注册状态下收到关机请求的处理
                   首先要发送关机DETACH,连接释放后进行本地资源释放
 Input           : VOS_UINT32                              ulMsgId
                   VOS_VOID                                *pMsg
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.luojian 00107747      2009-2-13  Draft Enact

*****************************************************************************/
VOS_UINT32    NAS_EMM_MsRegSsAnyMsgAppStopReq(
                    VOS_UINT32                              ulMsgId,
                    VOS_VOID                                *pMsg )
{
    /*VOS_UINT32                          ulRst;*/
    NAS_LMM_FSM_STATE_STRU               stDestState;
    MMC_LMM_STOP_REQ_STRU              *pstAttStopReq;

    (VOS_VOID)ulMsgId;

    /*停止所有定时器*/
    NAS_LMM_StopAllPtlTimer();
    NAS_LMM_StopAllStateTimer();

    /* 打印进入该函数， INFO_LEVEL */
    NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MsRegSsAnyMsgAppStopReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsAnyMsgAppStopReq_ENUM,LNAS_ENTRY);

    pstAttStopReq                       = pMsg;

    /* 设置App消息的相关参数 */
    NAS_EMM_SaveAppMsgPara(pstAttStopReq->ulMsgId,pstAttStopReq->ulOpId);
    /* 保存关机标识,提供给LRRC,用于LRRC判断空口是否是关机detach 该标志
       在LMM收到LRRC的power off cnf、等待power off cnf超时或者开机时清除(即置为0) */
    NAS_LMM_SetEmmInfoLtePowerOffFlag(NAS_EMM_YES);
    if(NAS_EMM_SUCC != NAS_EMM_JudgeBarType(NAS_EMM_BAR_TYPE_MO_SIGNAL))
    {
        /*启动定时器TI_NAS_EMM_PTL_SWITCH_OFF_TIMER*/
        NAS_LMM_StartPtlTimer(         TI_NAS_EMM_PTL_SWITCH_OFF_TIMER);

        /* 将状态转移至MS_NULL + SS_NULL_WAIT_SWITCH_OFF状态 */
        stDestState.enFsmId                 = NAS_LMM_PARALLEL_FSM_EMM;
        stDestState.enMainState             = EMM_MS_NULL;
        stDestState.enSubState              = EMM_SS_NULL_WAIT_SWITCH_OFF;
        stDestState.enStaTId                = TI_NAS_EMM_STATE_NO_TIMER;
        NAS_LMM_StaTransProc(stDestState);

        /* 发送DEATCH for power off消息 */
        NAS_EMM_SendDetachForPowerOffReq();
    }
    else
    {
        NAS_EMM_ProcLocalStop();
    }

    return NAS_LMM_MSG_HANDLED;

}

/*****************************************************************************
 Function Name   : NAS_EMM_MsRegSsNmlSrvMsgAppDetachReq
 Description     : 主状态REG+子状态NORMAL_SERVICE下收到应用层的DETACH
                   REQUEST消息

 Input           :

 Return          :

 History         :
    1.leili 00132387         2008-09-09  Draft Enact
    2.zhengjunyan 00148421   2010-12-24  调整保存APP参数的位置，参数检查正确后
*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegSsNmlSrvMsgAppDetachReq(VOS_UINT32  ulMsgId,
                                                 VOS_VOID   *pMsgStru )
{
    MMC_LMM_TAU_RSLT_ENUM_UINT32        ulTauRslt = MMC_LMM_TAU_RSLT_BUTT;
    MMC_LMM_DETACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_DETACH_REQ_STRU *) pMsgStru;

    /*打印进入该函数*/
    NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MsRegSsNmlSrvMsgAppDetachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsNmlSrvMsgAppDetachReq_ENUM,LNAS_ENTRY);

    /*检查状态是否匹配，若不匹配，退出*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG,EMM_SS_REG_NORMAL_SERVICE))
    {
        /*打印出错信息*/
        NAS_EMM_DETACH_LOG_WARN("NAS_EMM_MsRegSsNmlSrvMsgAppDetachReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsNmlSrvMsgAppDetachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*消息内容检查,若有错，打印并退出*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppDetachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_DETACH_LOG_ERR("NAS_EMM_MsRegSsNmlSrvMsgAppDetachReq: MMC_LMM_DETACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegSsNmlSrvMsgAppDetachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }

    /* 设置App消息的相关参数 */
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId,pRcvEmmMsg->ulOpId);

    /* 如果是IMSI DETACH，且当前注册域为PS，则直接返回成功；如果当前注册域为
       CS+PS，则发起IMSI DETACH流程 */
    if (MMC_LMM_MO_DET_CS_ONLY == NAS_EMM_GLO_AD_GetDetTypeMo())
    {
        NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MsRegSsNmlSrvMsgAppDetachReq:Process Imsi Detach");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsNmlSrvMsgAppDetachReq_ENUM,LNAS_FUNCTION_LABEL1);

        if (NAS_LMM_REG_DOMAIN_PS == NAS_LMM_GetEmmInfoRegDomain())
        {
            /*向APP发送DETACH成功*/
            NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);

            /* IMSI DETACH后释放资源 */
            NAS_LMM_ImsiDetachReleaseResource();

            return  NAS_LMM_MSG_HANDLED;
        }

        /* 发起IMSI DETACH流程 */
        NAS_EMM_SendImsiDetachReqMo();
        return  NAS_LMM_MSG_HANDLED;
    }

    /* 如果3411在运行，需要给MMC报TAU结果，以让MMC退出搜网状态机；3402定时器在
       运行无需通知，MMC收到TAU结果尝试次数为5时，已退出搜网状态机 */
    if (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_T3411))
    {
        NAS_EMM_SetTauTypeNoProcedure();

        ulTauRslt = MMC_LMM_TAU_RSLT_MO_DETACH_FAILURE;
        NAS_EMM_MmcSendTauActionResultIndOthertype((VOS_VOID*)&ulTauRslt);



    }

    /*停止定时器*/
    NAS_LMM_StopPtlTimer(                TI_NAS_EMM_PTL_T3411);
    NAS_LMM_Stop3402Timer();

    /*发送DETACH REQUEST消息*/
    NAS_EMM_SendDetachReqMo();

    return  NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsRegSsRegAttemptUpdateMmMsgAppDetachReq
 Description     : 状态REG+REG_ATTEMPTING_TO_UPDATE_MM收到MMC的MMC_LMM_DETACH_REQ
                    消息
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2011-7-12  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegSsRegAttemptUpdateMmMsgAppDetachReq
(
    VOS_UINT32  ulMsgId,
    VOS_VOID   *pMsgStru
)
{
    MMC_LMM_TAU_RSLT_ENUM_UINT32        ulTauRslt = MMC_LMM_TAU_RSLT_BUTT;
    MMC_LMM_DETACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_DETACH_REQ_STRU *) pMsgStru;

    /*打印进入该函数*/
    NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MsRegSsRegAttemptUpdateMmMsgAppDetachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgAppDetachReq_ENUM,LNAS_ENTRY);

    /*检查状态是否匹配，若不匹配，退出*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG,EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM))
    {
        /*打印出错信息*/
        NAS_EMM_DETACH_LOG_WARN("NAS_EMM_MsRegSsRegAttemptUpdateMmMsgAppDetachReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgAppDetachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*消息内容检查,若有错，打印并退出*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppDetachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_DETACH_LOG_ERR("NAS_EMM_MsRegSsRegAttemptUpdateMmMsgAppDetachReq: MMC_LMM_DETACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgAppDetachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }

    /* 设置App消息的相关参数 */
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId,pRcvEmmMsg->ulOpId);

    /* 判断是否为IMSI DETACH */
    if (MMC_LMM_MO_DET_CS_ONLY == NAS_EMM_GLO_AD_GetDetTypeMo())
    {
        NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MsRegSsRegAttemptUpdateMmMsgAppDetachReq:Process imsi detach");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgAppDetachReq_ENUM,LNAS_FUNCTION_LABEL1);

        /* 设置注册域为PS */
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);

        /* 如果3411在运行，需要给MMC报TAU结果，以让MMC退出搜网状态机；3402定时器在
           运行无需通知，MMC收到TAU结果尝试次数为5时，已退出搜网状态机 */
        if (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_T3411))
        {
            NAS_EMM_SetTauTypeNoProcedure();
            NAS_EMM_MmcSendTauActionResultIndSuccWithoutPara();
        }

        /*停止定时器*/
        NAS_LMM_StopPtlTimer(       TI_NAS_EMM_PTL_T3411);
        NAS_LMM_Stop3402Timer();

        /*修改状态：进入主状态EMM_MS_REG子状态EMM_SS_REG_NORMAL_SERVICE*/
        NAS_EMM_AdStateConvert(     EMM_MS_REG,
                                    EMM_SS_REG_NORMAL_SERVICE,
                                    TI_NAS_EMM_STATE_NO_TIMER);

        NAS_EMM_SendDetRslt(MMC_LMM_DETACH_RSLT_SUCCESS);

        /* IMSI DETACH后释放资源 */
        NAS_LMM_ImsiDetachReleaseResource();
        return  NAS_LMM_MSG_HANDLED;
    }

    /* 如果3411在运行，需要给MMC报TAU结果，以让MMC退出搜网状态机；3402定时器在
       运行无需通知，MMC收到TAU结果尝试次数为5时，已退出搜网状态机 */
    if (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_T3411))
    {
        NAS_EMM_TAU_SaveTAUtype(NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_WITH_IMSI);

        ulTauRslt = MMC_LMM_TAU_RSLT_MO_DETACH_FAILURE;
        NAS_EMM_MmcSendTauActionResultIndOthertype((VOS_VOID*)&ulTauRslt);

    }

    /*停止定时器*/
    NAS_LMM_StopPtlTimer(       TI_NAS_EMM_PTL_T3411);
    NAS_LMM_Stop3402Timer();

    /*发送DETACH REQUEST消息*/
    NAS_EMM_SendDetachReqMo();

    return  NAS_LMM_MSG_HANDLED;
}



/*****************************************************************************
 Function Name   : NAS_EMM_AppSendDetCnf
 Description     : UE发起的DETACH过程完成后，向APP发送DETACH结果消息

 Input           :

 Return          : None

 History         :
    1.leili 00132387         2008-09-09  Draft Enact

*****************************************************************************/
/*lint -e960*/
/*lint -e961*/
VOS_VOID    NAS_EMM_AppSendDetCnf
(
    MMC_LMM_DETACH_RSLT_ENUM_UINT32 ulAppRslt
)
{
    LMM_MMC_DETACH_CNF_STRU              *pEmmAppDetCnfMsg;

    /*申请消息内存*/
    pEmmAppDetCnfMsg = (VOS_VOID *)NAS_LMM_GetLmmMmcMsgBuf(sizeof(LMM_MMC_DETACH_CNF_STRU));

    /*判断申请结果，若失败打印错误并退出*/
    if (NAS_EMM_NULL_PTR == pEmmAppDetCnfMsg)
    {
        /*打印错误*/
        NAS_EMM_DETACH_LOG_ERR("NAS_EMM_AppSendDetCnf: MSG ALLOC ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_AppSendDetCnf_ENUM,LNAS_NULL_PTR);
        return;

    }

    NAS_LMM_MEM_SET_S(  pEmmAppDetCnfMsg,
                        sizeof(LMM_MMC_DETACH_CNF_STRU),
                        0,
                        sizeof(LMM_MMC_DETACH_CNF_STRU));

    /*构造APP_MM_DETACH_CNF消息*/
    /*填充消息头*/
    NAS_EMM_COMP_AD_MMC_PS_MSG_HEADER(  pEmmAppDetCnfMsg,
                                        sizeof(LMM_MMC_DETACH_CNF_STRU)-
                                        NAS_EMM_LEN_VOS_MSG_HEADER);

    /*填充消息ID*/
    pEmmAppDetCnfMsg->ulMsgId           = ID_LMM_MMC_DETACH_CNF;

    /*填充消息内容*/
    pEmmAppDetCnfMsg->ulOpId            = NAS_EMM_GetAppMsgOpId();
    pEmmAppDetCnfMsg->ulDetachRslt      = ulAppRslt;
    pEmmAppDetCnfMsg->ulReqType         = NAS_EMM_GLO_AD_GetDetTypeMo();

    /*向MMC发送APP_MM_DETACH_CNF消息*/
    NAS_LMM_SendLmmMmcMsg(                   pEmmAppDetCnfMsg);

    /*清空APP参数*/
    NAS_EMM_ClearAppMsgPara();

    return;

}


/*****************************************************************************
 Function Name   : NAS_EMM_EsmSendStatResult
 Description     : 向ESM发送状态结果消息

 Input           :

 Return          : None

 History         :
    1.leili 00132387    2008-09-09  Draft Enact
    2.lihong00150010    2012-11-01  Modify:emgergency

*****************************************************************************/
VOS_VOID    NAS_EMM_EsmSendStatResult(EMM_ESM_ATTACH_STATUS_ENUM_UINT32 ulStatRst)
{
    EMM_ESM_STATUS_IND_STRU              *pEmmEsmStatMsg;


    /*打印进入该函数*/
    NAS_EMM_DETACH_LOG1_INFO("NAS_EMM_EsmSendStatResult is entered", ulStatRst);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_EsmSendStatResult_ENUM,LNAS_ENTRY,ulStatRst);

    /*申请消息内存*/
    pEmmEsmStatMsg = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(EMM_ESM_STATUS_IND_STRU));

    /*判断申请结果，若失败退出*/
    if (NAS_EMM_NULL_PTR == pEmmEsmStatMsg)
    {
        return;
    }

    /*构造ID_EMM_ESM_STATUS_IND消息*/
    /*填充消息头*/
    NAS_EMM_COMP_AD_ESM_MSG_HEADER(         pEmmEsmStatMsg,
                                            sizeof(EMM_ESM_STATUS_IND_STRU)-
                                            NAS_EMM_LEN_VOS_MSG_HEADER);

    /*填充消息ID*/
    pEmmEsmStatMsg->ulMsgId                 = ID_EMM_ESM_STATUS_IND;

    /*填充消息内容*/
    if (EMM_ESM_ATTACH_STATUS_ATTACHED == ulStatRst)
    {
        pEmmEsmStatMsg->enEMMStatus         = EMM_ESM_ATTACH_STATUS_ATTACHED;
    }
    else if (EMM_ESM_ATTACH_STATUS_EMC_ATTACHING == ulStatRst)
    {
        pEmmEsmStatMsg->enEMMStatus         = EMM_ESM_ATTACH_STATUS_EMC_ATTACHING;

        /*clear global:EpsContextStatusChange*/
        NAS_EMM_GetEpsContextStatusChange() = NAS_EMM_EPS_BEARER_STATUS_NOCHANGE;
    }
    else
    {
        pEmmEsmStatMsg->enEMMStatus         = EMM_ESM_ATTACH_STATUS_DETACHED;

        /*clear global:EpsContextStatusChange*/
        NAS_EMM_GetEpsContextStatusChange() = NAS_EMM_EPS_BEARER_STATUS_NOCHANGE;
    }


    /*向ESM发送ID_EMM_ESM_STATUS_IND消息*/
    NAS_LMM_SEND_MSG(                       pEmmEsmStatMsg);

    return;

}

/*****************************************************************************
 Function Name   : NAS_EMM_MsDrgSsPlmnSrcMsgAppDetachReq
 Description     : 主状态DEREG+子状态DEREG_PLMN_SEARCH下收到APP发送的
                   DETACH REQUEST消息
 Input           :
 Output          :
 Return          :

 History         :
    1.leili 00132387         2008-09-09  Draft Enact
    2.zhengjunyan 00148421   2010-11-16  MOD:删除冗余代码
*****************************************************************************/
VOS_UINT32    NAS_EMM_MsDrgSsPlmnSrcMsgAppDetachReq(VOS_UINT32  ulMsgId,
                                                 VOS_VOID   *pMsgStru)
{
    MMC_LMM_DETACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_DETACH_REQ_STRU *) pMsgStru;

    /*打印进入该函数*/
    NAS_EMM_DETACH_LOG_NORM("NAS_EMM_MsDrgSsPlmnSrcMsgAppDetachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDrgSsPlmnSrcMsgAppDetachReq_ENUM,LNAS_ENTRY);

    /*检查状态是否匹配，若不匹配，退出*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_DEREG,EMM_SS_DEREG_PLMN_SEARCH))
    {
        /*打印出错信息*/
        NAS_EMM_DETACH_LOG_WARN("NAS_EMM_MsDrgSsPlmnSrcMsgAppDetachReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDrgSsPlmnSrcMsgAppDetachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*消息内容检查,若有错，打印并退出*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppDetachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_DETACH_LOG_ERR("NAS_EMM_MsDrgSsPlmnSrcMsgAppDetachReq: MMC_LMM_DETACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsDrgSsPlmnSrcMsgAppDetachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }

    /*保存APP参数*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId, pRcvEmmMsg->ulOpId);

    /* 如果是IMSI DETACH，则直接返回成功 */
    if (MMC_LMM_MO_DET_CS_ONLY == NAS_EMM_GLO_AD_GetDetTypeMo())
    {
        /*向APP发送DETACH成功*/
        NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);
        return  NAS_LMM_MSG_HANDLED;
    }

    /*向ESM发送ID_EMM_ESM_STATUS_IND消息*/
    NAS_EMM_EsmSendStatResult(          EMM_ESM_ATTACH_STATUS_DETACHED);

    /* 自研CL版本，PS DETACH通知ESM删除所有EHRPD相关承载记录 */
    NAS_EMM_SndEsmClearAllClBearerNotify();

    /*向APP发送DETACH成功*/
    NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);

    /* 本地DETACH释放资源:动态内存、赋初值 */
    NAS_LMM_DeregReleaseResource();

    return  NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsDrgSsAttemptToAttMsgAppDetachReq
 Description     : 主状态DEREG+子状态DEREG_ATTEMPTING_TO_ATTACH下收到APP发送的
                   DETACH REQUEST消息
 Input           :
 Output          :
 Return          :

 History         :
    1.leili 00132387         2008-09-09  Draft Enact
    2.zhengjunyan 00148421   2010-11-16  MOD:删除冗余代码
*****************************************************************************/
VOS_UINT32    NAS_EMM_MsDrgSsAttemptToAttMsgAppDetachReq(VOS_UINT32  ulMsgId,
                                                 VOS_VOID   *pMsgStru)
{
    MMC_LMM_DETACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_DETACH_REQ_STRU *) pMsgStru;

    /*打印进入该函数*/
    NAS_EMM_DETACH_LOG_NORM("NAS_EMM_MsDrgSsAttemptToAttMsgAppDetachReq is entered");\
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDrgSsAttemptToAttMsgAppDetachReq_ENUM,LNAS_ENTRY);

    /*检查状态是否匹配，若不匹配，退出*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_DEREG,EMM_SS_DEREG_ATTEMPTING_TO_ATTACH))
    {
        /*打印出错信息*/
        NAS_EMM_DETACH_LOG_WARN("NAS_EMM_MsDrgSsAttemptToAttMsgAppDetachReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDrgSsAttemptToAttMsgAppDetachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*消息内容检查,若有错，打印并退出*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppDetachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_DETACH_LOG_ERR("NAS_EMM_MsDrgSsAttemptToAttMsgAppDetachReq: MMC_LMM_DETACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsDrgSsAttemptToAttMsgAppDetachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }

     /*保存APP参数*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId, pRcvEmmMsg->ulOpId);

    /* 如果是IMSI DETACH，则直接返回成功 */
    if (MMC_LMM_MO_DET_CS_ONLY == NAS_EMM_GLO_AD_GetDetTypeMo())
    {
        /*向APP发送DETACH成功*/
        NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);
        return  NAS_LMM_MSG_HANDLED;
    }

    /* 如果3411在运行，需要给MMC报ATTACH结果，以让MMC退出搜网状态机；3402定时器在
       运行无需通知，MMC收到ATTACH结果尝试次数为5时，已退出搜网状态机 */
    if (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_T3411))
    {
        NAS_EMM_SetAttType();
        NAS_EMM_AppSendAttOtherType(MMC_LMM_ATT_RSLT_MO_DETACH_FAILURE);
    }

    /*停止定时器T3411,T3402*/
    NAS_LMM_StopPtlTimer(                TI_NAS_EMM_PTL_T3411);
    NAS_LMM_Stop3402Timer();

    /*修改状态：进入主状态DEREG子状态DEREG_NORMAL_SERVICE*/
    NAS_EMM_AdStateConvert(             EMM_MS_DEREG,
                                        EMM_SS_DEREG_NORMAL_SERVICE,
                                        TI_NAS_EMM_STATE_NO_TIMER);

    /*向ESM发送ID_EMM_ESM_STATUS_IND消息*/
    NAS_EMM_EsmSendStatResult(          EMM_ESM_ATTACH_STATUS_DETACHED);

    /* 自研CL版本，PS DETACH通知ESM删除所有EHRPD相关承载记录 */
    NAS_EMM_SndEsmClearAllClBearerNotify();

    /*向APP发送DETACH成功*/
    NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);

    /* 本地DETACH释放资源:动态内存、赋初值 */
    NAS_LMM_DeregReleaseResource();


    return  NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsDrgSsLimitedSrvMsgAppDetachReq
 Description     : 主状态DEREG+子状态DEREG_LIMITED_SERVICE下收到APP发送的
                   DETACH REQUEST消息
 Input           :
 Output          :
 Return          :

 History         :
    1.leili 00132387         2008-09-09  Draft Enact
    2.zhengjunyan 00148421   2010-11-16  MOD:删除冗余代码
*****************************************************************************/
VOS_UINT32    NAS_EMM_MsDrgSsLimitedSrvMsgAppDetachReq(VOS_UINT32  ulMsgId,
                                                 VOS_VOID   *pMsgStru)
{
    MMC_LMM_DETACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg =                        (MMC_LMM_DETACH_REQ_STRU *) pMsgStru;

    /*打印进入该函数*/
    NAS_EMM_DETACH_LOG_NORM("NAS_EMM_MsDrgSsLimitedSrvMsgAppDetachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDrgSsLimitedSrvMsgAppDetachReq_ENUM,LNAS_ENTRY);

    /*检查状态是否匹配，若不匹配，退出*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_DEREG,EMM_SS_DEREG_LIMITED_SERVICE))
    {
        /*打印出错信息*/
        NAS_EMM_DETACH_LOG_WARN("NAS_EMM_MsDrgSsLimitedSrvMsgAppDetachReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDrgSsLimitedSrvMsgAppDetachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*消息内容检查,若有错，打印并退出*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppDetachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_DETACH_LOG_ERR("NAS_EMM_MsDrgSsLimitedSrvMsgAppDetachReq: MMC_LMM_DETACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsDrgSsLimitedSrvMsgAppDetachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }

    /*保存APP参数*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId, pRcvEmmMsg->ulOpId);

    /* 如果是IMSI DETACH，则直接返回成功 */
    if (MMC_LMM_MO_DET_CS_ONLY == NAS_EMM_GLO_AD_GetDetTypeMo())
    {
        /*向APP发送DETACH成功*/
        NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);
        return  NAS_LMM_MSG_HANDLED;
    }

    /*向ESM发送ID_EMM_ESM_STATUS_IND消息*/
    NAS_EMM_EsmSendStatResult(          EMM_ESM_ATTACH_STATUS_DETACHED);

    /* 自研CL版本，PS DETACH通知ESM删除所有EHRPD相关承载记录 */
    NAS_EMM_SndEsmClearAllClBearerNotify();

    /*向APP发送DETACH成功*/
    NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);

    /* 本地DETACH释放资源:动态内存、赋初值 */
    NAS_LMM_DeregReleaseResource();

    return  NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsDrgSsNoCellAvailMsgAppDetachReq
 Description     : 主状态DEREG+子状态DEREG_NO_CELL_AVAILABLE下收到APP发送的
                   DETACH REQUEST消息
 Input           :
 Output          :
 Return          :

 History         :
    1.leili 00132387         2008-09-09  Draft Enact

*****************************************************************************/
VOS_UINT32    NAS_EMM_MsDrgSsNoCellAvailMsgAppDetachReq(VOS_UINT32  ulMsgId,
                                                 VOS_VOID   *pMsgStru)
{
    MMC_LMM_DETACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_DETACH_REQ_STRU *) pMsgStru;

    /*打印进入该函数*/
    NAS_EMM_DETACH_LOG_NORM("NAS_EMM_MsDrgSsNoCellAvailMsgAppDetachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDrgSsNoCellAvailMsgAppDetachReq_ENUM,LNAS_ENTRY);

    /*检查状态是否匹配，若不匹配，退出*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_DEREG,EMM_SS_DEREG_NO_CELL_AVAILABLE))
    {
        /*打印出错信息*/
        NAS_EMM_DETACH_LOG_WARN("NAS_EMM_MsDrgSsNoCellAvailMsgAppDetachReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDrgSsNoCellAvailMsgAppDetachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*消息内容检查,若有错，打印并退出*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppDetachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_DETACH_LOG_ERR("NAS_EMM_MsDrgSsNoCellAvailMsgAppDetachReq: MMC_LMM_DETACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsDrgSsNoCellAvailMsgAppDetachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }

     /*保存APP参数*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId, pRcvEmmMsg->ulOpId);

    /* 如果是IMSI DETACH，则直接返回成功 */
    if (MMC_LMM_MO_DET_CS_ONLY == NAS_EMM_GLO_AD_GetDetTypeMo())
    {
        /*向APP发送DETACH成功*/
        NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);
        return  NAS_LMM_MSG_HANDLED;
    }

    /*向ESM发送ID_EMM_ESM_STATUS_IND消息*/
    NAS_EMM_EsmSendStatResult(          EMM_ESM_ATTACH_STATUS_DETACHED);

    /* 自研CL版本，PS DETACH通知ESM删除所有EHRPD相关承载记录 */
    NAS_EMM_SndEsmClearAllClBearerNotify();

    /*向APP发送DETACH成功*/
    NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);

    /* 本地DETACH释放资源:动态内存、赋初值 */
    NAS_LMM_DeregReleaseResource();

    return  NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsDrgSsAttNeedMsgAppDetachReq
 Description     : 主状态DEREG+子状态DEREG_ATTACH_NEEDED下收到APP发送的
                   DETACH REQUEST消息
 Input           :
 Output          :
 Return          :

 History         :
    1.leili 00132387         2008-09-09  Draft Enact
    2.zhengjunyan 00148421   2010-11-16  MOD:删除冗余代码
*****************************************************************************/
VOS_UINT32    NAS_EMM_MsDrgSsAttNeedMsgAppDetachReq(VOS_UINT32  ulMsgId,
                                                 VOS_VOID   *pMsgStru)
{
    MMC_LMM_DETACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_DETACH_REQ_STRU *) pMsgStru;

    /*打印进入该函数*/
    NAS_EMM_DETACH_LOG_NORM("NAS_EMM_MsDrgSsAttNeedMsgAppDetachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDrgSsAttNeedMsgAppDetachReq_ENUM,LNAS_ENTRY);

    /*检查状态是否匹配，若不匹配，退出*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_DEREG,EMM_SS_DEREG_ATTACH_NEEDED))
    {
        /*打印出错信息*/
        NAS_EMM_DETACH_LOG_WARN("NAS_EMM_MsDrgSsAttNeedMsgAppDetachReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDrgSsAttNeedMsgAppDetachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*消息内容检查,若有错，打印并退出*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppDetachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_DETACH_LOG_ERR("NAS_EMM_MsDrgSsAttNeedMsgAppDetachReq: MMC_LMM_DETACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsDrgSsAttNeedMsgAppDetachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }

    /*保存APP参数*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId, pRcvEmmMsg->ulOpId);

    /* 如果是IMSI DETACH，则直接返回成功 */
    if (MMC_LMM_MO_DET_CS_ONLY == NAS_EMM_GLO_AD_GetDetTypeMo())
    {
        /*向APP发送DETACH成功*/
        NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);
        return  NAS_LMM_MSG_HANDLED;
    }

    /*修改状态：进入主状态DEREG子状态DEREG_NORMAL_SERVICE*/
    NAS_EMM_AdStateConvert(             EMM_MS_DEREG,
                                        EMM_SS_DEREG_NORMAL_SERVICE,
                                        TI_NAS_EMM_STATE_NO_TIMER);

    /*向ESM发送ID_EMM_ESM_STATUS_IND消息*/
    NAS_EMM_EsmSendStatResult(          EMM_ESM_ATTACH_STATUS_DETACHED);

    /* 自研CL版本，PS DETACH通知ESM删除所有EHRPD相关承载记录 */
    NAS_EMM_SndEsmClearAllClBearerNotify();

    /*向APP发送DETACH成功*/
    NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);

    /* 本地DETACH释放资源:动态内存、赋初值 */
    NAS_LMM_DeregReleaseResource();

    return  NAS_LMM_MSG_HANDLED;
}
/*****************************************************************************
 Function Name   : NAS_EMM_MsRegSsWaitAccessGrantIndImsiDetachProc
 Description     : 在REG+WAIT_ACCESS_GRANT_IND状态下收到用户IMSI DETACH
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong 00150010   2011-09-29  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMM_MsRegSsWaitAccessGrantIndImsiDetachProc( VOS_VOID )
{
    /* 如果当前注册域不为CS+PS，则直接回复成功 */
    if (NAS_LMM_REG_DOMAIN_CS_PS != NAS_LMM_GetEmmInfoRegDomain())
    {
        NAS_EMM_SendDetRslt(MMC_LMM_DETACH_RSLT_SUCCESS);

        /* IMSI DETACH后释放资源 */
        NAS_LMM_ImsiDetachReleaseResource();

        return ;
    }

    /* 如果不是信令被罢，则发起IMSI DETACH流程 */
    if(NAS_EMM_SUCC != NAS_EMM_JudgeBarType(NAS_EMM_BAR_TYPE_MO_SIGNAL))
    {
        /*发送IMSI DETACH REQUEST消息*/
        NAS_EMM_SendImsiDetachReqMo();

        return ;
    }

    /* 设置注册域为PS */
    NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);

    NAS_EMM_SendDetRslt(MMC_LMM_DETACH_RSLT_SUCCESS);

    /* IMSI DETACH后释放资源 */
    NAS_LMM_ImsiDetachReleaseResource();

    return ;
}

VOS_UINT32 NAS_EMM_MsRegSsWaitAccessGrantIndMsgAppDetachReq(VOS_UINT32  ulMsgId,
                                                 VOS_VOID   *pMsgStru)
{
    MMC_LMM_DETACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_DETACH_REQ_STRU *) pMsgStru;

    NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MsRegSsWaitAccessGrantIndMsgAppDetachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsWaitAccessGrantIndMsgAppDetachReq_ENUM,LNAS_ENTRY);

    /*消息内容检查,若有错，打印并退出*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppDetachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_DETACH_LOG_ERR("NAS_EMM_MsRegSsWaitAccessGrantIndMsgAppDetachReq: MMC_LMM_DETACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegSsWaitAccessGrantIndMsgAppDetachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;
    }

     /*保存APP参数*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId, pRcvEmmMsg->ulOpId);

    /* 判断是否为IMSI DETACH */
    if (MMC_LMM_MO_DET_CS_ONLY == NAS_EMM_GLO_AD_GetDetTypeMo())
    {
        NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MsRegSsWaitAccessGrantIndMsgAppDetachReq:Process imsi detach");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsWaitAccessGrantIndMsgAppDetachReq_ENUM,LNAS_FUNCTION_LABEL1);

        /* 处理IMSI DETACH */
        NAS_EMM_MsRegSsWaitAccessGrantIndImsiDetachProc();

        return  NAS_LMM_MSG_HANDLED;
    }

    if(NAS_EMM_SUCC != NAS_EMM_JudgeBarType(NAS_EMM_BAR_TYPE_MO_SIGNAL))
    {

        /*发送DETACH REQUEST消息*/
        NAS_EMM_SendDetachReqMo();

        return  NAS_LMM_MSG_HANDLED;
    }

    /*修改状态：进入主状态DEREG子状态DEREG_NORMAL_SERVICE*/
    NAS_EMM_AdStateConvert(             EMM_MS_DEREG,
                                        EMM_SS_DEREG_NORMAL_SERVICE,
                                        TI_NAS_EMM_STATE_NO_TIMER);

    /*向ESM发送ID_EMM_ESM_STATUS_IND消息*/
    NAS_EMM_EsmSendStatResult(EMM_ESM_ATTACH_STATUS_DETACHED);

    /*向APP发送APP_MM_DETACH_CNF*/
    NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);

    /* 本地DETACH释放资源:动态内存、赋初值 */
    NAS_LMM_DeregReleaseResource();

    return  NAS_LMM_MSG_HANDLED;
}


VOS_UINT32  NAS_EMM_MsRegSsNoCellAvailMsgAppDetachReq( VOS_UINT32  ulMsgId,
                                                 VOS_VOID   *pMsgStru)
{
    MMC_LMM_DETACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_DETACH_REQ_STRU *) pMsgStru;

    NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MsRegSsNoCellAvailMsgAppDetachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsNoCellAvailMsgAppDetachReq_ENUM,LNAS_ENTRY);

    /*消息内容检查,若有错，打印并退出*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppDetachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_DETACH_LOG_ERR("NAS_EMM_MsRegSsNoCellAvailMsgAppDetachReq: MMC_LMM_DETACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegSsNoCellAvailMsgAppDetachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;
    }

    /*保存APP参数*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId, pRcvEmmMsg->ulOpId);

    /* 如果是IMSI DETACH，则本地CS域DETACH */
    if (MMC_LMM_MO_DET_CS_ONLY == NAS_EMM_GLO_AD_GetDetTypeMo())
    {
        NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MsRegSsNoCellAvailMsgAppDetachReq:Process imsi detach");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsNoCellAvailMsgAppDetachReq_ENUM,LNAS_FUNCTION_LABEL1);

        /* 设置注册域为PS */
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);

        NAS_EMM_SendDetRslt(MMC_LMM_DETACH_RSLT_SUCCESS);

        /* IMSI DETACH后释放资源 */
        NAS_LMM_ImsiDetachReleaseResource();

        return  NAS_LMM_MSG_HANDLED;
    }

    /*修改状态：进入主状态DEREG子状态DEREG_NORMAL_SERVICE*/
    NAS_EMM_AdStateConvert(             EMM_MS_DEREG,
                                        EMM_SS_DEREG_NO_CELL_AVAILABLE,
                                        TI_NAS_EMM_STATE_NO_TIMER);

    /*向ESM发送ID_EMM_ESM_STATUS_IND消息*/
    NAS_EMM_EsmSendStatResult(EMM_ESM_ATTACH_STATUS_DETACHED);

    /*向APP发送APP_MM_DETACH_CNF*/
    NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);

    /* 本地DETACH释放资源:动态内存、赋初值 */
    NAS_LMM_DeregReleaseResource();

    return  NAS_LMM_MSG_HANDLED;
}


/*****************************************************************************
 Function Name   : NAS_EMM_MsRegInitSsWtEsmPdnRspMsgAppDetachReq
 Description     : 主状态REG_INIT+子状态ATTACH_WAIT_ESM_PDN_RSP下收到APP发送的
                   DETACH REQUEST消息

 Input           :

 Return          :

 History         :
    1.leili 00132387         2008-09-09  Draft Enact

*****************************************************************************/
VOS_UINT32    NAS_EMM_MsRegInitSsWtEsmPdnRspMsgAppDetachReq(VOS_UINT32  ulMsgId,
                                                 VOS_VOID   *pMsgStru )
{
    MMC_LMM_DETACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_DETACH_REQ_STRU *) pMsgStru;

    /*打印进入该函数*/
    NAS_EMM_DETACH_LOG_NORM("NAS_EMM_MsRegInitSsWtEsmPdnRspMsgAppDetachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegInitSsWtEsmPdnRspMsgAppDetachReq_ENUM,LNAS_ENTRY);

    /*检查状态是否匹配，若不匹配，退出*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG_INIT,EMM_SS_ATTACH_WAIT_ESM_PDN_RSP))
    {
        /*打印出错信息*/
        NAS_EMM_DETACH_LOG_WARN("NAS_EMM_MsRegInitSsWtEsmPdnRspMsgAppDetachReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegInitSsWtEsmPdnRspMsgAppDetachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*消息内容检查,若有错，打印并退出*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppDetachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_DETACH_LOG_ERR("NAS_EMM_MsRegInitSsWtEsmPdnRspMsgAppDetachReq: MMC_LMM_DETACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegInitSsWtEsmPdnRspMsgAppDetachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }

    /* 如果是IMSI DETACH，则直接返回成功 */
    if (MMC_LMM_MO_DET_CS_ONLY == NAS_EMM_GLO_AD_GetDetTypeMo())
    {
        /*向APP发送DETACH成功*/
        NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);
        return  NAS_LMM_MSG_HANDLED;
    }

    /*向MMC发送LMM_MMC_ATTACH_CNF或LMM_MMC_ATTACH_IND消息*/
    NAS_EMM_AppSendAttRstDefaultReqType(MMC_LMM_ATT_RSLT_MO_DETACH_FAILURE);

    /*保存APP参数*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId, pRcvEmmMsg->ulOpId);

    /*停止定时器TI_NAS_EMM_WAIT_ESM_PDN_RSP*/
    NAS_LMM_StopStateTimer(                  TI_NAS_EMM_WAIT_ESM_PDN_RSP);

    /*修改状态：进入主状态DEREG子状态DEREG_NORMAL_SERVICE*/
    NAS_EMM_AdStateConvert(             EMM_MS_DEREG,
                                        EMM_SS_DEREG_NORMAL_SERVICE,
                                        TI_NAS_EMM_STATE_NO_TIMER);
    /*向MMC发送APP_MM_DETACH_CNF*/
    NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);

    /*向ESM发送ID_EMM_ESM_STATUS_IND消息*/
    NAS_EMM_EsmSendStatResult(          EMM_ESM_ATTACH_STATUS_DETACHED);

    /* 自研CL版本，PS DETACH通知ESM删除所有EHRPD相关承载记录 */
    NAS_EMM_SndEsmClearAllClBearerNotify();

    /* 本地DETACH释放资源:动态内存、赋初值 */
    NAS_LMM_DeregReleaseResource();

    /* 如果处于CONN态,释放连接*/
    if (NAS_EMM_CONN_IDLE != NAS_EMM_GetConnState())
    {
        NAS_EMM_RelReq(                 NAS_LMM_NOT_BARRED);

    }

    return  NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgAppDetachReq
 Description     : 主状态REG_INIT+子状态ATTACH_WAIT_ESM_BEARER_CNF下收到APP发送的
                   DETACH REQUEST消息

 Input           :

 Return          :

 History         :
    1.leili 00132387         2008-09-09  Draft Enact

*****************************************************************************/
VOS_UINT32    NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgAppDetachReq(VOS_UINT32  ulMsgId,
                                                 VOS_VOID   *pMsgStru )
{
    MMC_LMM_DETACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_DETACH_REQ_STRU *) pMsgStru;

    /*打印进入该函数*/
    NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgAppDetachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgAppDetachReq_ENUM,LNAS_ENTRY);

    /*检查状态是否匹配，若不匹配，退出*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG_INIT,EMM_SS_ATTACH_WAIT_ESM_BEARER_CNF))
    {
        /*打印出错信息*/
        NAS_EMM_DETACH_LOG_WARN("NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgAppDetachReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgAppDetachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*消息内容检查,若有错，打印并退出*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppDetachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_DETACH_LOG_ERR("NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgAppDetachReq: MMC_LMM_DETACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgAppDetachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }

    /* 如果是IMSI DETACH，则低优先级缓存 */
    if (MMC_LMM_MO_DET_CS_ONLY == NAS_EMM_GLO_AD_GetDetTypeMo())
    {
        NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgAppDetachReq:Lowly store imsi detach");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgAppDetachReq_ENUM,LNAS_FUNCTION_LABEL1);
        return  NAS_LMM_STORE_LOW_PRIO_MSG;
    }

    /*向MMC发送LMM_MMC_ATTACH_CNF或LMM_MMC_ATTACH_IND消息*/
    NAS_EMM_AppSendAttOtherType(MMC_LMM_ATT_RSLT_MO_DETACH_FAILURE);
    /*保存APP参数*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId, pRcvEmmMsg->ulOpId);

    /*停止定时器TI_NAS_EMM_WAIT_ESM_BEARER_CNF*/
    NAS_LMM_StopStateTimer(          TI_NAS_EMM_WAIT_ESM_BEARER_CNF);

    /*NAS_EMM_GLO_AD_GetDetMode()         = pRcvEmmMsg->ulDetacbMode;*/

    /*发送DETACH REQUEST消息*/
    NAS_EMM_SendDetachReqMo();

    return  NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsRegSsAtmpToUpdMsgAppDetachReq
 Description     : 主状态REG+子状态REG_ATTEMPTING_TO_UPDATE下收到APP发送的
                   DETACH REQUEST消息

 Input           :

 Return          :

 History         :
    1.leili 00132387         2008-09-09  Draft Enact
    2.zhengjunyan 00148421   2009.03.18  modified
*****************************************************************************/
VOS_UINT32    NAS_EMM_MsRegSsAtmpToUpdMsgAppDetachReq(VOS_UINT32  ulMsgId,
                                                 VOS_VOID   *pMsgStru )
{
    MMC_LMM_TAU_RSLT_ENUM_UINT32        ulTauRslt = MMC_LMM_TAU_RSLT_BUTT;
    MMC_LMM_DETACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_DETACH_REQ_STRU *) pMsgStru;

    /*打印进入该函数*/
    NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MsRegSsAtmpToUpdMsgAppDetachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsAtmpToUpdMsgAppDetachReq_ENUM,LNAS_ENTRY);

    /*检查状态是否匹配，若不匹配，退出*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG,EMM_SS_REG_ATTEMPTING_TO_UPDATE))
    {
        /*打印出错信息*/
        NAS_EMM_DETACH_LOG_WARN("NAS_EMM_MsRegSsAtmpToUpdMsgAppDetachReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsAtmpToUpdMsgAppDetachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*消息内容检查,若有错，打印并退出*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppDetachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_DETACH_LOG_ERR("NAS_EMM_MsRegSsAtmpToUpdMsgAppDetachReq: MMC_LMM_DETACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegSsAtmpToUpdMsgAppDetachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }

    /*保存APP参数*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId, pRcvEmmMsg->ulOpId);

    /* 如果是IMSI DETACH，则本地CS域DETACH */
    if (MMC_LMM_MO_DET_CS_ONLY == NAS_EMM_GLO_AD_GetDetTypeMo())
    {
        NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MsRegSsAtmpToUpdMsgAppDetachReq:Process imsi detach");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsAtmpToUpdMsgAppDetachReq_ENUM,LNAS_FUNCTION_LABEL1);

        /* 设置注册域为PS */
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);

        NAS_EMM_SendDetRslt(MMC_LMM_DETACH_RSLT_SUCCESS);

        /* IMSI DETACH后释放资源 */
        NAS_LMM_ImsiDetachReleaseResource();

        return  NAS_LMM_MSG_HANDLED;
    }

    /* 如果3411在运行，需要给MMC报TAU结果，以让MMC退出搜网状态机；3402定时器在
       运行无需通知，MMC收到TAU结果尝试次数为5时，已退出搜网状态机 */
    if (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_T3411))
    {
        NAS_EMM_SetTauTypeNoProcedure();

        ulTauRslt = MMC_LMM_TAU_RSLT_MO_DETACH_FAILURE;
        NAS_EMM_MmcSendTauActionResultIndOthertype((VOS_VOID*)&ulTauRslt);

    }

    /*停止定时器*/
    NAS_LMM_StopPtlTimer(                TI_NAS_EMM_PTL_T3411);
    NAS_LMM_Stop3402Timer();

    /*发送DETACH REQUEST消息*/
    NAS_EMM_SendDetachReqMo();

    /*清空TAU相关全局变量*/
    NAS_EMM_TAU_ClearResouce();

    return  NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsRegSsLimitedSrvMsgIntraDetReq
 Description     : 紧急呼特性合入后，TAU完成可能会进入REG+LIMIT_SERVICE态，
                   如果TAU是打断DETACH流程的，则会在REG+LIMIT_SERVICE态下
                   收到内部TAU消息
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong 00150010      2012-12-19  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegSsLimitedSrvMsgIntraDetReq
(
    VOS_UINT32                         ulMsgId,
    VOS_VOID                          *pMsgStru
)
{
    NAS_LMM_INTRA_DETACH_REQ_STRU              *pRcvEmmMsg = NAS_EMM_NULL_PTR;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (NAS_LMM_INTRA_DETACH_REQ_STRU *) pMsgStru;

    NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MsRegSsLimitedSrvMsgIntraDetReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsLimitedSrvMsgIntraDetReq_ENUM,LNAS_ENTRY);

    /*消息内容检查,若有错，打印并退出*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_IntraDetReqChk(pRcvEmmMsg))
    {
        NAS_EMM_DETACH_LOG_ERR("NAS_EMM_MsRegSsLimitedSrvMsgIntraDetReq: MMC_MM_SYS_INFO_IND_STRU para err!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegSsLimitedSrvMsgIntraDetReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;
    }

    /* 如果是IMSI DETACH，则本地CS域DETACH */
    if (MMC_LMM_MO_DET_CS_ONLY == NAS_EMM_GLO_AD_GetDetTypeMo())
    {
        NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MsRegSsLimitedSrvMsgIntraDetReq:Process imsi detach");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsLimitedSrvMsgIntraDetReq_ENUM,LNAS_FUNCTION_LABEL1);

        /* 当UE是正常注册且有紧急承载时:
           从正常小区切换至被禁小区，MME会显示发起承载区激活，去激活所有非紧急
           承载；从正常小区先丟网，然后ANYCELL搜到被禁小区，UE由于TAI不在TAI LIST
           中发起TAU，MME会在TAU ACCEPT中携带承载信息删除所有非紧急承载；
           因此如果UE是正常注册且有紧急承载时，不可能长时间处于REG+LIMIT_SERVICE
           态，收到CS DETACH可以本地DETACH，因为后续还有释放所有非紧急承载进入紧急注册 */

        /* 因此如果能发起IMSI DETACH，则不可能在被禁小区，因此IMSI DETACH成功完成，
           或者异常，都只会进入REG+NORMAL_SERVICE，而不会进入REG+LIMIT_SERVICE态，
           不需要状态修正 */

        /* 设置注册域为PS */
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);

        NAS_EMM_SendDetRslt(MMC_LMM_DETACH_RSLT_SUCCESS);

        /* IMSI DETACH后释放资源 */
        NAS_LMM_ImsiDetachReleaseResource();

        return  NAS_LMM_MSG_HANDLED;
    }

    if (NAS_EMM_CONN_DATA == NAS_EMM_GetConnState())
    {
        /*停止定时器*/
        NAS_LMM_StopPtlTimer(           TI_NAS_EMM_PTL_T3411);
        NAS_LMM_Stop3402Timer();

        /*发送DETACH REQUEST消息*/
        NAS_EMM_SendDetachReqMo();

        return  NAS_LMM_MSG_HANDLED;
    }

    /*修改状态：进入主状态DEREG子状态DEREG_NORMAL_SERVICE*/
    NAS_EMM_AdStateConvert(             EMM_MS_DEREG,
                                        EMM_SS_DEREG_LIMITED_SERVICE,
                                        TI_NAS_EMM_STATE_NO_TIMER);

    /*向APP发送APP_MM_DETACH_CNF*/
    NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);

    /* 本地DETACH释放资源:动态内存、赋初值 */
    NAS_LMM_DeregReleaseResource();

    NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_NULL);

    return  NAS_LMM_MSG_HANDLED;
}


VOS_UINT32  NAS_EMM_MsRegSsLimitedSrvMsgAppDetachReq( VOS_UINT32  ulMsgId,
                                                                          VOS_VOID   *pMsgStru )
{
    MMC_LMM_DETACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_DETACH_REQ_STRU *) pMsgStru;

    NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MsRegSsLimitedSrvMsgAppDetachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsLimitedSrvMsgAppDetachReq_ENUM,LNAS_ENTRY);

    /*消息内容检查,若有错，打印并退出*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppDetachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_DETACH_LOG_ERR("NAS_EMM_MsRegSsLimitedSrvMsgAppDetachReq: MMC_LMM_DETACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegSsLimitedSrvMsgAppDetachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;
    }

    /*保存APP参数*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId, pRcvEmmMsg->ulOpId);

    /* 如果是IMSI DETACH，则本地CS域DETACH */
    if (MMC_LMM_MO_DET_CS_ONLY == NAS_EMM_GLO_AD_GetDetTypeMo())
    {
        NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MsRegSsLimitedSrvMsgAppDetachReq:Process imsi detach");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsLimitedSrvMsgAppDetachReq_ENUM,LNAS_FUNCTION_LABEL1);

        /* 当UE是正常注册且有紧急承载时:
           从正常小区切换至被禁小区，MME会显示发起承载区激活，去激活所有非紧急
           承载；从正常小区先丟网，然后ANYCELL搜到被禁小区，UE由于TAI不在TAI LIST
           中发起TAU，MME会在TAU ACCEPT中携带承载信息删除所有非紧急承载；
           因此如果UE是正常注册且有紧急承载时，不可能长时间处于REG+LIMIT_SERVICE
           态，收到CS DETACH可以本地DETACH，因为后续还有释放所有非紧急承载进入紧急注册 */

        /* 因此如果能发起IMSI DETACH，则不可能在被禁小区，因此IMSI DETACH成功完成，
           或者异常，都只会进入REG+NORMAL_SERVICE，而不会进入REG+LIMIT_SERVICE态，
           不需要状态修正 */

        /* 设置注册域为PS */
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);

        NAS_EMM_SendDetRslt(MMC_LMM_DETACH_RSLT_SUCCESS);

        /* IMSI DETACH后释放资源 */
        NAS_LMM_ImsiDetachReleaseResource();

        return  NAS_LMM_MSG_HANDLED;
    }
    if (NAS_EMM_CONN_DATA == NAS_EMM_GetConnState())
    {
        /*停止定时器*/
        NAS_LMM_StopPtlTimer(           TI_NAS_EMM_PTL_T3411);
        NAS_LMM_Stop3402Timer();

        /*发送DETACH REQUEST消息*/
        NAS_EMM_SendDetachReqMo();

        return  NAS_LMM_MSG_HANDLED;
    }
    /*修改状态：进入主状态DEREG子状态DEREG_NORMAL_SERVICE*/
    NAS_EMM_AdStateConvert(             EMM_MS_DEREG,
                                        EMM_SS_DEREG_LIMITED_SERVICE,
                                        TI_NAS_EMM_STATE_NO_TIMER);

    /*向ESM发送ID_EMM_ESM_STATUS_IND消息*/
    NAS_EMM_EsmSendStatResult(EMM_ESM_ATTACH_STATUS_DETACHED);

    /*向APP发送APP_MM_DETACH_CNF*/
    NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);

    /* 本地DETACH释放资源:动态内存、赋初值 */
    NAS_LMM_DeregReleaseResource();
    NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_NULL);
    return  NAS_LMM_MSG_HANDLED;
}


VOS_UINT32  NAS_EMM_MsRegSsPlmnSrcMsgAppDetachReq(VOS_UINT32  ulMsgId,
                                                                      VOS_VOID   *pMsgStru )
{
    MMC_LMM_DETACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_DETACH_REQ_STRU *) pMsgStru;

    NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MsRegSsPlmnSrcMsgAppDetachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsPlmnSrcMsgAppDetachReq_ENUM,LNAS_ENTRY);

    /*消息内容检查,若有错，打印并退出*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppDetachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_DETACH_LOG_ERR("NAS_EMM_MsRegSsPlmnSrcMsgAppDetachReq: MMC_LMM_DETACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegSsPlmnSrcMsgAppDetachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;
    }

     /*保存APP参数*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId, pRcvEmmMsg->ulOpId);

    /* 如果是IMSI DETACH，则本地CS域DETACH */
    if (MMC_LMM_MO_DET_CS_ONLY == NAS_EMM_GLO_AD_GetDetTypeMo())
    {
        NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MsRegSsPlmnSrcMsgAppDetachReq:Process imsi detach");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsPlmnSrcMsgAppDetachReq_ENUM,LNAS_FUNCTION_LABEL1);

        /* 设置注册域为PS */
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);

        NAS_EMM_SendDetRslt(MMC_LMM_DETACH_RSLT_SUCCESS);

        /* IMSI DETACH后释放资源 */
        NAS_LMM_ImsiDetachReleaseResource();

        return  NAS_LMM_MSG_HANDLED;
    }

    /*修改状态：进入主状态DEREG子状态SS_DEREG_NO_CELL_AVAILABLE*/
    NAS_EMM_AdStateConvert(             EMM_MS_DEREG,
                                        EMM_SS_DEREG_NO_CELL_AVAILABLE,
                                        TI_NAS_EMM_STATE_NO_TIMER);

    /*向ESM发送ID_EMM_ESM_STATUS_IND消息*/
    NAS_EMM_EsmSendStatResult(EMM_ESM_ATTACH_STATUS_DETACHED);

    /*向APP发送APP_MM_DETACH_CNF*/
    NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);

    /* 本地DETACH释放资源:动态内存、赋初值 */
    NAS_LMM_DeregReleaseResource();

    return  NAS_LMM_MSG_HANDLED;
}

#if 0
/*****************************************************************************
 Function Name   : NAS_EMM_MsSomeStateSsWtRrcRelIndMsgAppDetachReq
 Description     : 在TAU_Init/Reg_Init/Ser_Init等待RrcRelInd的状态下收到AppDetachReq，
                   将消息缓存后发起去链接流程。
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.y00159566            2010-2-9      Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsSomeStateSsWtRrcRelIndMsgAppDetachReq( VOS_UINT32  ulMsgId,
                                                 VOS_VOID   *pMsgStru)
{
    MMC_LMM_DETACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_DETACH_REQ_STRU *) pMsgStru;

    /*消息内容检查,若有错，打印并退出*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppDetachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_DETACH_LOG_ERR("NAS_EMM_MsSomeStateSsWtRrcRelIndMsgAppDetachReq: MMC_LMM_DETACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsSomeStateSsWtRrcRelIndMsgAppDetachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;
    }

    /*打印进入该函数*/
    NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MsSomeStateSsWtRrcRelIndMsgAppDetachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsSomeStateSsWtRrcRelIndMsgAppDetachReq_ENUM,LNAS_ENTRY);

     /*保存APP参数*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId, pRcvEmmMsg->ulOpId);

    /*stop T3440*/
    NAS_LMM_StopStateTimer(              TI_NAS_EMM_STATE_T3440);

    /*保存RRC连接释放原因*/
    /*NAS_EMM_GLO_AD_GetConnRelCau()      = EMM_CONN_REL_CAUSE_REJVAL_OTHER;*/

    /*向MRRC发送NAS_EMM_MRRC_REL_REQ消息*/
    NAS_EMM_RelReq(                     NAS_LMM_NOT_BARRED);

    NAS_LMM_PrintFsmState(               NAS_LMM_PARALLEL_FSM_EMM);

    /*缓存AppDetachReq*/
    NAS_LMM_PUBM_LOG_NORM("NAS_EMM_MsSomeStateSsWtRrcRelIndMsgAppDetachReq:Store APP DETACH AT:");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsSomeStateSsWtRrcRelIndMsgAppDetachReq_ENUM,LNAS_FUNCTION_LABEL1);

    return  NAS_LMM_STORE_LOW_PRIO_MSG;
}
#endif

/*****************************************************************************
 Function Name   : NAS_EMM_MsgLppTauInitCnfMsgAppDetachReq
 Description     : 主状态TAU_INIT+子状态TAU_WAIT_CN_TAU_CNF下收到APP发送的
                   DETACH REQUEST消息,处理LPP流程
 Input           :
 Return          :

 History         :
    1.lifuxin   l00253982   2015-08-15
*****************************************************************************/
#if (FEATURE_LPP == FEATURE_ON)
VOS_VOID    NAS_EMM_MsgLppTauInitWtCnfAppDetachReqSsOrLppHandle(VOS_VOID)
{
    if(NAS_EMM_SER_START_CAUSE_LPP_EST_REQ == NAS_EMM_SER_GetSerStartCause())
    {
        NAS_EMM_SendLppEstCnf(LMM_LPP_EST_RESULT_FAIL_PS_ATTACH_NOT_ALLOWED);
        NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_BUTT);
    }

    if(NAS_EMM_SER_START_CAUSE_SS_EST_REQ == NAS_EMM_SER_GetSerStartCause())
    {
        NAS_LMM_SndLmmLcsEstCnf( LMM_LCS_EST_RSLT_FAIL_PS_ATTACH_NOT_ALLOWED,
                                NAS_EMM_SER_GetSsOrLppOpid());
        NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_BUTT);
    }
}
#endif


/*****************************************************************************
 Function Name   : NAS_EMM_MsTauInitSsWtCnTauCnfMsgAppDetachReq
 Description     : 主状态TAU_INIT+子状态TAU_WAIT_CN_TAU_CNF下收到APP发送的
                   DETACH REQUEST消息

 Input           :

 Return          :

 History         :
    1.leili 00132387         2008-09-09  Draft Enact
    2.sunbing 49683          2011-11-21  增加SMS的处理
*****************************************************************************/
VOS_UINT32    NAS_EMM_MsTauInitSsWtCnTauCnfMsgAppDetachReq( VOS_UINT32  ulMsgId,
                                                 VOS_VOID   *pMsgStru )
{
    MMC_LMM_TAU_RSLT_ENUM_UINT32        ulTauRslt = MMC_LMM_TAU_RSLT_BUTT;
    MMC_LMM_DETACH_REQ_STRU             *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_DETACH_REQ_STRU *) pMsgStru;

    /*打印进入该函数*/
    NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MsTauInitSsWtCnTauCnfMsgAppDetachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsTauInitSsWtCnTauCnfMsgAppDetachReq_ENUM,LNAS_ENTRY);

    /*检查状态是否匹配，若不匹配，退出*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_TAU_INIT,EMM_SS_TAU_WAIT_CN_TAU_CNF))
    {
        /*打印出错信息*/
        NAS_EMM_DETACH_LOG_WARN("NAS_EMM_MsTauInitSsWtCnTauCnfMsgAppDetachReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsTauInitSsWtCnTauCnfMsgAppDetachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*消息内容检查,若有错，打印并退出*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppDetachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_DETACH_LOG_ERR("NNAS_EMM_MsTauInitSsWtCnTauCnfMsgAppDetachReq: MMC_LMM_DETACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsTauInitSsWtCnTauCnfMsgAppDetachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }

    /*保存APP参数*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId, pRcvEmmMsg->ulOpId);

    /* 如果是IMSI DETACH，则低优先级缓存，等提案通过再根据提案处理 */
    if (MMC_LMM_MO_DET_CS_ONLY == NAS_EMM_GLO_AD_GetDetTypeMo())
    {
        NAS_EMM_DETACH_LOG_INFO("NNAS_EMM_MsTauInitSsWtCnTauCnfMsgAppDetachReq:Lowly store imsi detach");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsTauInitSsWtCnTauCnfMsgAppDetachReq_ENUM,LNAS_FUNCTION_LABEL1);
        if ((NAS_EMM_COLLISION_SERVICE == NAS_EMM_TAU_GetEmmCollisionCtrl())
            && (VOS_TRUE == NAS_EMM_SER_IsCsfbProcedure()))
        {
            NAS_EMM_SetCsfbProcedureFlag(PS_FALSE);

            /* 停止ESR流程,通知LRRC CSFB流程终止,LRRC收到该消息后,若等待网侧释放定时器启动时,停止定时器 */
            NAS_EMM_SndLrrcLmmCsfbNotify(LRRC_LNAS_CSFB_STATUS_END);

            NAS_EMM_MmSendCsfbSerEndInd(MM_LMM_CSFB_SERVICE_RSLT_MMC_DETACH_FAIL, NAS_LMM_CAUSE_NULL);
            NAS_EMM_TAU_SaveEmmCollisionCtrl(NAS_EMM_COLLISION_NONE);
        }
        if ((NAS_EMM_COLLISION_SERVICE == NAS_EMM_TAU_GetEmmCollisionCtrl())
            && (NAS_EMM_SER_START_CAUSE_SMS_EST_REQ == NAS_EMM_SER_GetSerStartCause()))
        {
            NAS_LMM_SndLmmSmsErrInd(LMM_SMS_ERR_CAUSE_CS_ATTACH_NOT_ALLOWED);
            NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_BUTT);
            NAS_EMM_TAU_SaveEmmCollisionCtrl(NAS_EMM_COLLISION_NONE);
        }
        return  NAS_LMM_STORE_LOW_PRIO_MSG;
    }

    /* 若TAU打断了SERVICE流程，则需要清楚ESM缓存消息 */
    if (NAS_EMM_COLLISION_SERVICE == NAS_EMM_TAU_GetEmmCollisionCtrl())
    {
        /*如果SR流程是由于SMS触发，UE需要去注册，需要回复SMS建链失败，并且清除SR的发起原因*/
        if(NAS_EMM_SER_START_CAUSE_SMS_EST_REQ == NAS_EMM_SER_GetSerStartCause())
        {
            NAS_LMM_SndLmmSmsErrInd(LMM_SMS_ERR_CAUSE_PS_ATTACH_NOT_ALLOWED);
            NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_BUTT);
        }

        #if (FEATURE_LPP == FEATURE_ON)
        NAS_EMM_MsgLppTauInitWtCnfAppDetachReqSsOrLppHandle();
        #endif

        if (VOS_TRUE == NAS_EMM_SER_IsCsfbProcedure())
        {
            NAS_EMM_SetCsfbProcedureFlag(PS_FALSE);

            /* 停止ESR流程,通知LRRC CSFB流程终止,LRRC收到该消息后,若等待网侧释放定时器启动时,停止定时器 */
            NAS_EMM_SndLrrcLmmCsfbNotify(LRRC_LNAS_CSFB_STATUS_END);

            NAS_EMM_MmSendCsfbSerEndInd(MM_LMM_CSFB_SERVICE_RSLT_MMC_DETACH_FAIL, NAS_LMM_CAUSE_NULL);
            NAS_EMM_TAU_SaveEmmCollisionCtrl(NAS_EMM_COLLISION_NONE);
        }

        /*清空ESM_DATA缓存*/
        NAS_EMM_SerClearEsmDataBuf();
    }


    /* 不存在TAU打断了DETACH的情况下，又收到用户DETACH消息的场景，因为AT命令
       未回复之前不能再下发AT指令 */

    /*调用TAU模块提供的函数*/
    NAS_EMM_TAU_AbnormalOver();

    #if (FEATURE_ON == FEATURE_DSDS)
    /*发送end notify消息给RRC，通知RRC释放资源*/
    NAS_EMM_TAU_SendRrcDsdsEndNotify();
    #endif

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    NAS_EMM_SendMtcTAUEndType();
#endif

    /* 向MMC发被 MO DETACH 打断 LMM_MMC_TAU_RESULT_IND*/

    ulTauRslt = MMC_LMM_TAU_RSLT_MO_DETACH_FAILURE;
    NAS_EMM_MmcSendTauActionResultIndOthertype((VOS_VOID*)&ulTauRslt);

    /* Svlte或CL离网重选时必须进行本地DETACH(接口约定必须PS DETACH),此时不能发送空口消息 */
    if((NAS_EMM_YES == NAS_LMM_IsSvlteOrLcNeedLocalDetach())
        &&(MMC_LMM_MO_DET_PS_ONLY == pRcvEmmMsg->ulDetachType))
    {
        /* 给MMC回复DETACH成功，同时DETACH掉ESM */
        NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);
        NAS_EMM_EsmSendStatResult(EMM_ESM_ATTACH_STATUS_DETACHED);
        NAS_EMM_AdStateConvert(EMM_MS_DEREG,
                               EMM_SS_DEREG_NORMAL_SERVICE,
                               TI_NAS_EMM_STATE_NO_TIMER);

        /* 本地DETACH释放资源:动态内存、赋初值,释放链路 */
        NAS_LMM_DeregReleaseResource();
        NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);

        /* 清除标识 */
        NAS_MML_SetPsLocalDetachFlag(NAS_LMM_LOCAL_DETACH_FLAG_INVALID);
        return  NAS_LMM_MSG_HANDLED;
    }

    /* CL多模时MMC指示LMM必须进行本地DETACH */
    if(MMC_LMM_DETACH_RESEAON_NON_3GPP_ATTACH == pRcvEmmMsg->ulDetachReason)
    {
        /* 给MMC回复DETACH成功，同时DETACH掉ESM */
        NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);
        NAS_EMM_EsmSendStatResult(EMM_ESM_ATTACH_STATUS_DETACHED);
        NAS_EMM_AdStateConvert(EMM_MS_DEREG,
                               EMM_SS_DEREG_NORMAL_SERVICE,
                               TI_NAS_EMM_STATE_NO_TIMER);

        /* 本地DETACH释放资源:动态内存、赋初值,释放链路 */
        NAS_LMM_DeregReleaseResource();
        NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);
    }
    else
    {
        /*发送DETACH REQUEST消息*/
        NAS_EMM_SendDetachReqMo();
    }

    return  NAS_LMM_MSG_HANDLED;
}
/*lint +e961*/
/*lint +e960*/
/*****************************************************************************
 Function Name   : NAS_EMM_MsSerInitSsWtCnSerCnfImsiDetachProc
 Description     : 在EMM_MS_SER_INIT+EMM_SS_SER_WAIT_CN_SER_CNF状态下收到用户
                   IMSI DETACH
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong 00150010   2011-09-29  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMM_MsSerInitSsWtCnSerCnfImsiDetachProc( VOS_VOID )
{
    /* 如果当前注册域不为CS+PS，则直接回复成功 */
    if (NAS_LMM_REG_DOMAIN_CS_PS != NAS_LMM_GetEmmInfoRegDomain())
    {
        /* 如果是REG+ATTEMPT_TO_UPDATE_MM状态下发起的SERVICE流程，且3411在运行，
           需要给MMC报TAU结果，以让MMC退出搜网状态机；3402定时器在运行无需通知，
           MMC收到TAU结果尝试次数为5时，已退出搜网状态机 */
        if ((NAS_EMM_YES == NAS_EMM_TAU_CanTriggerComTauWithIMSI())
            && (0 < NAS_EMM_TAU_GetEmmTAUAttemptCnt())
            && (5 > NAS_EMM_TAU_GetEmmTAUAttemptCnt()))
        {
             NAS_EMM_SetTauTypeNoProcedure();
            NAS_EMM_MmcSendTauActionResultIndSuccWithoutPara();
        }

        NAS_EMM_SendDetRslt(MMC_LMM_DETACH_RSLT_SUCCESS);

        /* IMSI DETACH后释放资源 */
        NAS_LMM_ImsiDetachReleaseResource();

        return ;
    }

    /*调用SER_INIT模块提供的函数*/
    NAS_EMM_SER_AbnormalOver();

    /*发送DETACH REQUEST消息*/
    NAS_EMM_SendImsiDetachReqMo();

    return ;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsSerInitSsWtCnSerCnfMsgAppDetachReq
 Description     : 主状态SER_INIT+子状态SER_WAIT_CN_SER_CNF下收到APP发送的
                   DETACH REQUEST消息

 Input           :

 Return          :

 History         :
    1.leili 00132387         2008-09-09  Draft Enact

*****************************************************************************/
VOS_UINT32    NAS_EMM_MsSerInitSsWtCnSerCnfMsgAppDetachReq( VOS_UINT32  ulMsgId,
                                                 VOS_VOID   *pMsgStru )
{
    MMC_LMM_TAU_RSLT_ENUM_UINT32        ulTauRslt = MMC_LMM_TAU_RSLT_BUTT;
    MMC_LMM_DETACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_DETACH_REQ_STRU *) pMsgStru;

    /*打印进入该函数*/
    NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MsSerInitSsWtCnSerCnfMsgAppDetachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsSerInitSsWtCnSerCnfMsgAppDetachReq_ENUM,LNAS_ENTRY);

    /*检查状态是否匹配，若不匹配，退出*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_SER_INIT,EMM_SS_SER_WAIT_CN_SER_CNF))
    {
        /*打印出错信息*/
        NAS_EMM_DETACH_LOG_WARN("NAS_EMM_MsSerInitSsWtCnSerCnfMsgAppDetachReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsSerInitSsWtCnSerCnfMsgAppDetachReq_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*消息内容检查,若有错，打印并退出*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_AppDetachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_DETACH_LOG_ERR("NAS_EMM_MsSerInitSsWtCnSerCnfMsgAppDetachReq: MMC_LMM_DETACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsSerInitSsWtCnSerCnfMsgAppDetachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }

     /*保存APP参数*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId, pRcvEmmMsg->ulOpId);

    if (VOS_TRUE == NAS_EMM_SER_IsCsfbProcedure())
    {
        NAS_EMM_SetCsfbProcedureFlag(PS_FALSE);

        NAS_EMM_MmSendCsfbSerEndInd(MM_LMM_CSFB_SERVICE_RSLT_MMC_DETACH_FAIL, NAS_LMM_CAUSE_NULL);
    }

    /* 判断是否为IMSI DETACH */
    if (MMC_LMM_MO_DET_CS_ONLY == NAS_EMM_GLO_AD_GetDetTypeMo())
    {
        NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MsSerInitSsWtCnSerCnfMsgAppDetachReq:Process imsi detach");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsSerInitSsWtCnSerCnfMsgAppDetachReq_ENUM,LNAS_FUNCTION_LABEL1);

        /* 处理IMSI DETACH */
        NAS_EMM_MsSerInitSsWtCnSerCnfImsiDetachProc();
        NAS_LMM_Stop3402Timer();
        NAS_LMM_StopPtlTimer(TI_NAS_EMM_PTL_T3411);

        return  NAS_LMM_MSG_HANDLED;
    }

    /*调用SER_INIT模块提供的函数*/
    NAS_EMM_SER_AbnormalOver();

    /* 如果是REG+ATTEMPT_TO_UPDATE_MM状态下发起的SERVICE流程，且3411在运行，
       需要给MMC报TAU结果，以让MMC退出搜网状态机；3402定时器在运行无需通知，
       MMC收到TAU结果尝试次数为5时，已退出搜网状态机 */
    if ((NAS_EMM_YES == NAS_EMM_TAU_CanTriggerComTauWithIMSI())
        && (0 < NAS_EMM_TAU_GetEmmTAUAttemptCnt())
        && (5 > NAS_EMM_TAU_GetEmmTAUAttemptCnt()))
    {
        NAS_EMM_TAU_SaveTAUtype(NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_WITH_IMSI);

        ulTauRslt = MMC_LMM_TAU_RSLT_MO_DETACH_FAILURE;
        NAS_EMM_MmcSendTauActionResultIndOthertype((VOS_VOID*)&ulTauRslt);
    }
    NAS_LMM_Stop3402Timer();
    NAS_LMM_StopPtlTimer(TI_NAS_EMM_PTL_T3411);

    /* Svlte或CL离网重选时必须进行本地DETACH(接口约定必须PS DETACH),此时不能发送空口消息 */
    if((NAS_EMM_YES == NAS_LMM_IsSvlteOrLcNeedLocalDetach())
        &&(MMC_LMM_MO_DET_PS_ONLY == pRcvEmmMsg->ulDetachType))
    {
        /* 给MMC回复DETACH成功，同时DETACH掉ESM */
        NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);
        NAS_EMM_EsmSendStatResult(EMM_ESM_ATTACH_STATUS_DETACHED);
        NAS_EMM_AdStateConvert(EMM_MS_DEREG,
                               EMM_SS_DEREG_NORMAL_SERVICE,
                               TI_NAS_EMM_STATE_NO_TIMER);

        /* 本地DETACH释放资源:动态内存、赋初值,释放链路 */
        NAS_LMM_DeregReleaseResource();
        NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);

        /* 清除标识 */
        NAS_MML_SetPsLocalDetachFlag(NAS_LMM_LOCAL_DETACH_FLAG_INVALID);
        return  NAS_LMM_MSG_HANDLED;
    }

    /* CL多模时MMC指示LMM必须进行本地DETACH */
    if(MMC_LMM_DETACH_RESEAON_NON_3GPP_ATTACH == pRcvEmmMsg->ulDetachReason)
    {
        /* 给MMC回复DETACH成功，同时DETACH掉ESM */
        NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);
        NAS_EMM_EsmSendStatResult(EMM_ESM_ATTACH_STATUS_DETACHED);
        NAS_EMM_AdStateConvert(EMM_MS_DEREG,
                               EMM_SS_DEREG_NORMAL_SERVICE,
                               TI_NAS_EMM_STATE_NO_TIMER);

        /* 本地DETACH释放资源:动态内存、赋初值,释放链路 */
        NAS_LMM_DeregReleaseResource();
        NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);
    }
    else
    {
        /*发送DETACH REQUEST消息*/
        NAS_EMM_SendDetachReqMo();
    }

    return  NAS_LMM_MSG_HANDLED;
}



VOS_UINT32    NAS_EMM_EmmMsRegInitSsWaitRrcDataCnfMsgAppDetachReq(
                                                 VOS_UINT32  ulMsgId,
                                                 VOS_VOID   *pMsgStru )
{
    MMC_LMM_DETACH_REQ_STRU              *pRcvEmmMsg;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (MMC_LMM_DETACH_REQ_STRU *) pMsgStru;

    /*打印进入该函数*/
    NAS_EMM_DETACH_LOG_INFO(            "NAS_EMM_EmmMsRegInitSsWaitRrcDataCnfMsgAppDetachReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_EmmMsRegInitSsWaitRrcDataCnfMsgAppDetachReq_ENUM,LNAS_ENTRY);


    /*消息内容检查,若有错，打印并退出*/
    if (NAS_EMM_PARA_INVALID            == NAS_EMM_AppDetachReqMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_DETACH_LOG_ERR(         "NAS_EMM_EmmMsRegInitSsWaitRrcDataCnfMsgAppDetachReq: MMC_LMM_DETACH_REQ_STRU PARA ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_EmmMsRegInitSsWaitRrcDataCnfMsgAppDetachReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }

    /* 如果是IMSI DETACH，则低优先级缓存 */
    if (MMC_LMM_MO_DET_CS_ONLY == NAS_EMM_GLO_AD_GetDetTypeMo())
    {
        NAS_EMM_DETACH_LOG_INFO("NAS_EMM_EmmMsRegInitSsWaitRrcDataCnfMsgAppDetachReq:Lowly store imsi detach");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_EmmMsRegInitSsWaitRrcDataCnfMsgAppDetachReq_ENUM,LNAS_FUNCTION_LABEL1);

        /*保存APP参数*/
        NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId, pRcvEmmMsg->ulOpId);
        return  NAS_LMM_STORE_LOW_PRIO_MSG;
    }

    NAS_LMM_StopStateTimer(TI_NAS_EMM_WAIT_RRC_DATA_CNF);

    /*向MMC发送LMM_MMC_ATTACH_CNF或LMM_MMC_ATTACH_IND消息*/
    NAS_EMM_AppSendAttOtherType(MMC_LMM_ATT_RSLT_MO_DETACH_FAILURE);

    /*保存APP参数*/
    NAS_EMM_SaveAppMsgPara(pRcvEmmMsg->ulMsgId, pRcvEmmMsg->ulOpId);

    /*发送DETACH REQUEST消息*/
    NAS_EMM_SendDetachReqMo();

    return  NAS_LMM_MSG_HANDLED;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

















































