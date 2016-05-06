/******************************************************************************

   Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : NasEmmPlmn.c
  Description     : PLMN模块处理流程
  History         :
     1.lining 00141619       2008-9-11   Draft Enact
     2.hanlufeng 41410 BJ9D00494 ATTEMPING TO ATTACH状态下收到系统消息后
                                 发起ATTACH，不再和SM交互，因此改为直接
                                 调用ATTACH 模块提供的接口。
******************************************************************************/


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include  "NasLmmPubMInclude.h"
#include  "NasMmlCtx.h"
#include  "NasEmmAttachEsmMsgProcess.h"
#include  "NasEmmAttDetInclude.h"
#if(FEATURE_LPP == FEATURE_ON)
#include  "NasEmmLppMsgProc.h"
#endif
/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASEMMPLMN_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASEMMPLMN_C
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
  3.1  消息发送 Function
*****************************************************************************/
/*****************************************************************************
 Function Name   : NAS_EMM_PLMN_SendAppStartCnf
 Description     : 向APP发送APP_MM_START_CNF消息
 Input           : ulAppMmStartParam -- 启动消息参数
 Output          : None
 Return          : NAS_EMM_PLMN_OK  -- 发送成功
                   an error code    -- 发送失败

 History         :
    1.lining 00141619      2008-9-16  Draft Enact
    2.zhengjunyan 00148421 2010-11-16  MMC和LMM之间的消息修改为MMC内部消息
*****************************************************************************/
/*lint -e960*/
/*lint -e961*/
VOS_UINT32  NAS_EMM_PLMN_SendAppStartCnf(
                    VOS_UINT32                              ulAppRslt,
                    VOS_UINT32                              ulOpId)
{
    LMM_MMC_START_CNF_STRU             *pstAppStartCnfMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulSendResult;

    /* 申请MMC内部消息 */
    pstAppStartCnfMsg  = (VOS_VOID *)NAS_LMM_GetLmmMmcMsgBuf(sizeof(LMM_MMC_START_CNF_STRU));

    if (NAS_EMM_PLMN_NULL_PTR == pstAppStartCnfMsg)
    {
        /* 打印异常，ERROR_LEVEL */
        NAS_LMM_EMM_PLMN_LOG_ERR("NAS_EMM_PLMN_SendAppStartCnf: MSG ALLOC ERROR!!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_PLMN_SendAppStartCnf_ENUM,LNAS_NULL_PTR);
        return NAS_EMM_PLMN_ERR;
    }

    NAS_LMM_MEM_SET_S(pstAppStartCnfMsg,sizeof(LMM_MMC_START_CNF_STRU),0,sizeof(LMM_MMC_START_CNF_STRU));

    /* 打包VOS消息头 */
    EMM_PUBU_COMP_MMC_MSG_HEADER((pstAppStartCnfMsg),
                             NAS_EMM_PLMN_MSG_LENGTH_NO_HEADER(LMM_MMC_START_CNF_STRU));

    /* 填充消息ID */
    pstAppStartCnfMsg->ulMsgId          = ID_LMM_MMC_START_CNF;

    /* 填充消息体 */
    pstAppStartCnfMsg->ulOpId           = ulOpId;
    pstAppStartCnfMsg->ulRst            = ulAppRslt;

    /* 发送MMC消息 */
    NAS_LMM_SendLmmMmcMsg((VOS_VOID*)pstAppStartCnfMsg);

    ulSendResult                        = NAS_EMM_OK;

    return ulSendResult;
}

/*****************************************************************************
 Function Name   : NAS_EMM_PLMN_SendAppStopCnf
 Description     : 向APP发送APP_MM_STOP_CNF消息
 Input           : ulAppMmStopParam -- 停止消息参数
 Output          : None
 Return          : NAS_EMM_PLMN_OK  -- 发送成功
                   an error code    -- 发送失败

 History         :
    1.lining 00141619      2008-9-16  Draft Enact
    2.zhengjunyan 00148421 2010-11-16  MMC和LMM之间的消息修改为MMC内部消息

*****************************************************************************/
VOS_UINT32  NAS_EMM_PLMN_SendAppStopCnf(
                    VOS_UINT32                              ulAppRslt,
                    VOS_UINT32                              ulOpId)
{
    LMM_MMC_STOP_CNF_STRU              *pstAppStopCnfMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulSendResult;

    (void)(ulAppRslt);

    /* 申请MMC内部消息 */
    pstAppStopCnfMsg = (VOS_VOID *)NAS_LMM_GetLmmMmcMsgBuf(sizeof(LMM_MMC_STOP_CNF_STRU));
    if (NAS_EMM_PLMN_NULL_PTR == pstAppStopCnfMsg)
    {
        /* 打印异常，ERROR_LEVEL */
        NAS_LMM_EMM_PLMN_LOG_ERR("NAS_EMM_PLMN_SendAppStopCnf: MSG ALLOC ERROR!!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_PLMN_SendAppStopCnf_ENUM,LNAS_NULL_PTR);
        return NAS_EMM_PLMN_ERR;
    }
    NAS_LMM_MEM_SET_S(pstAppStopCnfMsg, sizeof(LMM_MMC_STOP_CNF_STRU), 0, sizeof(LMM_MMC_STOP_CNF_STRU));

    /* 打包VOS消息头 */
    EMM_PUBU_COMP_MMC_MSG_HEADER((pstAppStopCnfMsg),
         NAS_EMM_PLMN_MSG_LENGTH_NO_HEADER(LMM_MMC_STOP_CNF_STRU));

    /* 填充消息ID */
    pstAppStopCnfMsg->ulMsgId           = ID_LMM_MMC_STOP_CNF;

    /* 填充消息体 */
    pstAppStopCnfMsg->ulOpId            = ulOpId;

    /* 发送MMC消息 */
    NAS_LMM_SendLmmMmcMsg((VOS_VOID*)pstAppStopCnfMsg);

    ulSendResult                        = NAS_EMM_OK;

    return ulSendResult;
}


/*****************************************************************************
 Function Name   : NAS_EMM_PLMN_SendRrcStartReq
 Description     : 向RRC发送RRC_MM_START_REQ消息
 Input           : None
 Output          : None
 Return          : NAS_EMM_PLMN_OK  -- 发送成功
                   an error code    -- 发送失败

 History         :
    1.lining 00141619      2008-9-16  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_PLMN_SendRrcStartReq( VOS_VOID )
{
    LRRC_LMM_START_REQ_STRU            *pstRrcStartReqMsg;
    VOS_UINT32                          ulSendResult;


    /* 申请DOPRA消息 */
    pstRrcStartReqMsg = (VOS_VOID *) NAS_LMM_ALLOC_MSG(sizeof(LRRC_LMM_START_REQ_STRU));
    if(NAS_EMM_PLMN_NULL_PTR == pstRrcStartReqMsg)
    {
        return NAS_EMM_PLMN_ERR;
    }

    /* 设置为0 */
    NAS_LMM_MEM_SET_S(  pstRrcStartReqMsg,
                        sizeof(LRRC_LMM_START_REQ_STRU),
                        0,
                        sizeof(LRRC_LMM_START_REQ_STRU));

    /* 打包VOS消息头 */
    NAS_EMM_PLMN_COMP_RRC_MSG_HEADER((pstRrcStartReqMsg),
                                      NAS_EMM_PLMN_MSG_LENGTH_NO_HEADER(LRRC_LMM_START_REQ_STRU));

    /* 填充消息ID */
    pstRrcStartReqMsg->enMsgId          = ID_LRRC_LMM_START_REQ;

    /* 填充消息体 */
    /* 填充卡状态 */
    NAS_EMM_SET_LRRCLMM_INF_USIM_STATE(pstRrcStartReqMsg->enSimStatus);


    pstRrcStartReqMsg->enLteRatPrio                             = NAS_LMM_GetCurLtePrio();


    pstRrcStartReqMsg->aucRatPrioList[NAS_LMM_RAT_TYPE_GSM]     = NAS_LMM_GetCurGsmPrio();
    pstRrcStartReqMsg->aucRatPrioList[NAS_LMM_RAT_TYPE_WCDMA]   = NAS_LMM_GetCurWcdmaPrio();
    pstRrcStartReqMsg->aucRatPrioList[NAS_LMM_RAT_TYPE_LTE]     = NAS_LMM_GetCurLtePrio();
    pstRrcStartReqMsg->aucRatPrioList[NAS_LMM_RAT_TYPE_CDMA1X]   = NAS_LMM_GetCurCdma1xPrio();
    pstRrcStartReqMsg->aucRatPrioList[NAS_LMM_RAT_TYPE_HRPD]     = NAS_LMM_GetCurHrpdPrio();

    pstRrcStartReqMsg->enUtranMode = NAS_LMM_GetEmmInfoUtranMode();

    /* 发送DOPRA消息 */
    NAS_LMM_SEND_MSG(                   pstRrcStartReqMsg);

    ulSendResult                        = NAS_EMM_OK;


    return ulSendResult;
}


/*****************************************************************************
 Function Name   : NAS_EMM_PLMN_SendRrcStopReq
 Description     : 向RRC发送MM_RRC_STOP_REQ消息
 Input           : None
 Output          : None
 Return          : NAS_EMM_PLMN_OK  -- 发送成功
                   an error code    -- 发送失败

 History        :
    1.lining 00141619      2008-9-16  Draft Enact
    2.sunbing 49683        2010-9-11  在RRC消息队列中消息超过10条的场景下，
                                      关机消息已紧急消息形式插入到消息队列中，确保关机消息得到处理
*****************************************************************************/
VOS_UINT32  NAS_EMM_PLMN_SendRrcStopReq( VOS_VOID )
{
    RRC_MM_STOP_REQ_STRU                *pstRrcStopReqMsg;
    VOS_UINT32                          ulSendResult;

    /* 申请DOPRA消息 */
    pstRrcStopReqMsg = (VOS_VOID *) NAS_LMM_ALLOC_MSG(sizeof(RRC_MM_STOP_REQ_STRU));
    if (NAS_EMM_PLMN_NULL_PTR == pstRrcStopReqMsg)
    {
        return NAS_EMM_PLMN_ERR;
    }

    NAS_LMM_MEM_SET_S(pstRrcStopReqMsg, sizeof(RRC_MM_STOP_REQ_STRU), 0, sizeof(RRC_MM_STOP_REQ_STRU));

    /* 打包VOS消息头 */
    NAS_EMM_PLMN_COMP_RRC_MSG_HEADER((pstRrcStopReqMsg),
                                    NAS_EMM_PLMN_MSG_LENGTH_NO_HEADER(RRC_MM_STOP_REQ_STRU))

    /* 填充消息ID */
    pstRrcStopReqMsg->enMsgId           = ID_LRRC_LMM_POWER_OFF_REQ;

    /*单板环境下，RRC消息队列中的消息超过10条，则以紧急消息形式发送关机消息*/
    #if (VOS_OS_VER != VOS_WIN32)
    if(VOS_ERR == VOS_CheckTaskQueue(PS_PID_ERMM, NAS_EMM_PLMN_10_MSG_IN_QUEUE))
    {
        NAS_LMM_EMM_PLMN_LOG_ERR("NAS_EMM_PLMN_SendRrcStopReq: Snd Urgent Msg!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_PLMN_SendRrcStopReq_ENUM,LNAS_FUNCTION_LABEL1);

        /*如果RRC的消息队列超过10个消息，则以紧急消息方式发送关机消息*/
        NAS_LMM_SEND_URGENT_MSG(         pstRrcStopReqMsg);
    }
    else
    #endif
    {
        /*否则以普通消息形式发送*/
        NAS_LMM_SEND_MSG(                pstRrcStopReqMsg);
    }

    ulSendResult                        = NAS_EMM_OK;

    return ulSendResult;
}


/*****************************************************************************
 Function Name   : NAS_EMM_PLMN_SendMmcStartReq
 Description     : 向MMC发送MMC_EMM_START_REQ消息
 Input           : None
 Output          : None
 Return          : NAS_EMM_PLMN_OK  -- 发送成功
                   NAS_EMM_PLMN_ERR -- 发送失败

 History         :
    1.lining 00141619      2008-9-16  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_PLMN_SendMmcStartReq(
                    VOS_UINT32                              ulStartCause )
{
    EMMC_EMM_START_REQ_STRU              *pstMmcStartReqMsg;
    VOS_UINT32                          ulMsgLengthNoHeader;
    VOS_UINT32                          ulSendResult;

    /* 计算EMM要发给内部其它模块的内部消息长度, 不包含VOS头 */
    ulMsgLengthNoHeader = NAS_EMM_PLMN_INTRAMSG_LENGTH_NO_HEADER(EMMC_EMM_START_REQ_STRU);

    /* 获取内部消息地址 */
    pstMmcStartReqMsg = (EMMC_EMM_START_REQ_STRU *) NAS_LMM_GetSendIntraMsgBuffAddr(ulMsgLengthNoHeader);
    if (NAS_EMM_PLMN_NULL_PTR == pstMmcStartReqMsg)
    {
        /* 打印异常，ERROR_LEVEL */
        NAS_LMM_EMM_PLMN_LOG_ERR("NAS_EMM_PLMN_SendMmcStartReq: GET INTRAMSG ADDR ERROR!!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_PLMN_SendMmcStartReq_ENUM,LNAS_NULL_PTR);
        return NAS_EMM_PLMN_ERR;
    }

    /* 打包内部消息头 */
    NAS_EMM_PLMN_COMP_MM_INTRAMSG_HEADER((pstMmcStartReqMsg), ulMsgLengthNoHeader);

    /* 填充内部消息ID */
    pstMmcStartReqMsg ->enMsgId         = ID_EMMC_EMM_START_REQ;

    /* 填充消息体 */
    pstMmcStartReqMsg->enCause          = ulStartCause;

    /* PLMN子模块向MMC发送MMC_EMM_START_REQ内部消息 */
    ulSendResult =                      NAS_EMM_PLMN_OK;
    NAS_EMM_SEND_INTRA_MSG(             pstMmcStartReqMsg);

    return ulSendResult;
}


/*****************************************************************************
 Function Name   : NAS_EMM_PLMN_SendMmcStopReq
 Description     : 向MMC发送MMC_EMM_STOP_REQ消息
 Input           : None
 Output          : None
 Return          : NAS_EMM_PLMN_OK  -- 发送成功
                   NAS_EMM_PLMN_ERR -- 发送失败

 History         :
    1.lining 00141619      2008-9-16  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_PLMN_SendMmcStopReq( VOS_VOID )
{
    EMMC_EMM_STOP_REQ_STRU               *pstMmcStopReqMsg;
    VOS_UINT32                          ulMsgLengthNoHeader;
    VOS_UINT32                          ulSendResult;

    /* 计算EMM要发给内部其它模块的内部消息长度, 不包含VOS头 */
    ulMsgLengthNoHeader = NAS_EMM_PLMN_INTRAMSG_LENGTH_NO_HEADER(EMMC_EMM_STOP_REQ_STRU);

    /* 获取内部消息地址 */
    pstMmcStopReqMsg = (VOS_VOID *) NAS_LMM_GetSendIntraMsgBuffAddr(ulMsgLengthNoHeader);
    if (NAS_EMM_PLMN_NULL_PTR == pstMmcStopReqMsg)
    {
        /* 打印异常，ERROR_LEVEL */
        NAS_LMM_EMM_PLMN_LOG_ERR("NAS_EMM_PLMN_SendMmcStopReq: GET INTRAMSG ADDR ERROR!!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_PLMN_SendMmcStopReq_ENUM,LNAS_NULL_PTR);
        return NAS_EMM_PLMN_ERR;
    }

    /* 打包内部消息头 */
    NAS_EMM_PLMN_COMP_MM_INTRAMSG_HEADER((pstMmcStopReqMsg), ulMsgLengthNoHeader);

    /* 填充内部消息ID */
    pstMmcStopReqMsg->enMsgId           = ID_EMMC_EMM_STOP_REQ;

    ulSendResult =                      NAS_EMM_PLMN_OK;
    NAS_EMM_SEND_INTRA_MSG(             pstMmcStopReqMsg);

    return ulSendResult;
}


/*****************************************************************************
 Function Name   : NAS_EMM_PLMN_SendEmmEsmStautsInd
 Description     : 向ESM发送EMM_ESM_STATUS_IND消息
 Input           : ulStatRst    -状态类型
 Output          : None
 Return          : NONE
 History         :
    1.leili 00132387      2009-02-06  Draft Enact

*****************************************************************************/

VOS_VOID NAS_EMM_PLMN_SendEmmEsmStautsInd(EMM_ESM_ATTACH_STATUS_ENUM_UINT32 ulStatRst)
{
    EMM_ESM_STATUS_IND_STRU             *pEmmEsmStatMsg;

    NAS_EMM_PUBU_LOG1_NORM("NAS_EMM_PLMN_SendEmmEsmStautsInd", ulStatRst);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_PLMN_SendEmmEsmStautsInd_ENUM,LNAS_ENTRY,ulStatRst);

    /* 申请DOPRA消息 */
    pEmmEsmStatMsg = (VOS_VOID *) NAS_LMM_ALLOC_MSG(sizeof(EMM_ESM_STATUS_IND_STRU));
    if (NAS_EMM_PLMN_NULL_PTR == pEmmEsmStatMsg)
    {
        return;
    }

    /* 打包VOS消息头 */
    NAS_EMM_PLMN_COMP_ESM_MSG_HEADER(pEmmEsmStatMsg,
                                    NAS_EMM_PLMN_MSG_LENGTH_NO_HEADER(EMM_ESM_STATUS_IND_STRU));

    /* 填充消息ID */
    pEmmEsmStatMsg->ulMsgId             = ID_EMM_ESM_STATUS_IND;

    /*填充消息内容*/
    pEmmEsmStatMsg->enEMMStatus         = ulStatRst;

    /*clear global:EpsContextStatusChange*/
    if(ulStatRst == EMM_ESM_ATTACH_STATUS_DETACHED)
    {
        NAS_EMM_GetEpsContextStatusChange() = NAS_EMM_EPS_BEARER_STATUS_NOCHANGE;
    }
    /*向ESM发送ID_EMM_ESM_STATUS_IND消息*/

    NAS_LMM_SEND_MSG(                   pEmmEsmStatMsg);

    return;

}

/*****************************************************************************
 Function Name   : NAS_EMM_PLMN_ImsiPagingProc
 Description     : Process the Paging_Ind with Imsi
 Input           :
 Output          :
 Return          :
 History         :
    1.zhengjunyan 00148421 2009.03.24 New Draft
    2.yangfan     00159566 2010.03.30 Modify
    3.yangfan     00159566 2010.06.21 修改本地Detach
*****************************************************************************/

VOS_VOID NAS_EMM_PLMN_ImsiPagingProc(VOS_VOID)
{
    NAS_EMM_FSM_STATE_STRU              EmmState;
    VOS_UINT32                          ulRst;

    NAS_LMM_EMM_PLMN_LOG_INFO("NAS_EMM_PLMN_ImsiPagingProc is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PLMN_ImsiPagingProc_ENUM,LNAS_ENTRY);


    EmmState.enFsmId                    = NAS_LMM_PARALLEL_FSM_EMM;
    EmmState.enMainState                = EMM_MS_DEREG;
    EmmState.enSubState                 = EMM_SS_DEREG_NORMAL_SERVICE;
    EmmState.enStaTId                   = TI_NAS_EMM_STATE_NO_TIMER;
    NAS_LMM_StaTransProc(EmmState);

    /*向APP发送APP_MM_DETACH_IND消息*/
    NAS_EMM_MmcSendDetIndLocal(MMC_LMM_L_LOCAL_DETACH_IMSI_PAGING);
    /* 本地DETACH释放资源:动态内存、赋初值 */
    NAS_LMM_DeregReleaseResource();

    /* 删除GUTI后会自动保存EPS_LOC,所以需要先设置STATUS */
    NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_NOT_UPDATED_EU2);

    /*删除GUTI,KSIasme,TAI list,LVR TAI*/
    NAS_EMM_ClearRegInfo(NAS_EMM_NOT_DELETE_RPLMN);

    /*send INTRA ATTACH REQ*/
    ulRst = NAS_EMM_SendIntraAttachReq();
    if(NAS_EMM_PLMN_OK != ulRst)
    {
        NAS_LMM_EMM_PLMN_LOG_ERR("NAS_EMM_PLMN_ImsiPagingProc: send INTRA ATTACH REQ ERR !");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_PLMN_ImsiPagingProc_ENUM,LNAS_ERROR);
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_PLMN_STmsiPagingProc
 Description     : Process the Paging_Ind with S-TMSI
 Input           :
 Output          :
 Return          :
 History         :
    1.zhengjunyan 00148421 2009.03.24 New Draft
    2.X00148705            2010-03-02 在EmmMsRegSsAttemptToUpdate响应TMSI Paging
*****************************************************************************/

VOS_VOID NAS_EMM_PLMN_STmsiPagingProc(VOS_VOID)
{
    VOS_UINT32                          ulCurEmmStat;
    NAS_LMM_EMM_PLMN_LOG_INFO(           "NAS_EMM_PLMN_STmsiPagingProc is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PLMN_STmsiPagingProc_ENUM,LNAS_ENTRY);

    ulCurEmmStat                        = NAS_LMM_PUB_COMP_EMMSTATE(
                                        NAS_EMM_CUR_MAIN_STAT,
                                        NAS_EMM_CUR_SUB_STAT);

    if (ulCurEmmStat == NAS_LMM_PUB_COMP_EMMSTATE( EMM_MS_REG, EMM_SS_REG_NORMAL_SERVICE))
    {
        NAS_EMM_SER_RcvRrcStmsiPagingInd();
    }
    else if (ulCurEmmStat == NAS_LMM_PUB_COMP_EMMSTATE( EMM_MS_REG, EMM_SS_REG_WAIT_ACCESS_GRANT_IND))
    {
        if(NAS_EMM_SUCC != NAS_EMM_JudgeBarType(NAS_EMM_BAR_TYPE_MT))
        {
            NAS_EMM_SER_RcvRrcStmsiPagingInd();
        }
        else
        {
            #if (FEATURE_ON == FEATURE_PTM)
            /* 由于在该状态下丢弃了PS域的PAGING，所以增加CHR上报 */
            NAS_EMM_PagingErrRecord(EMM_OM_ERRLOG_PAGING_PS,EMM_OM_LMM_PAGING_FAIL_CAUSE_ABNORMAL_STATUS);
            #endif
        }
    }
    else if (ulCurEmmStat == NAS_LMM_PUB_COMP_EMMSTATE( EMM_MS_REG, EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM))
    {
        /* 记录UPDATE_MM标识 */
        /*NAS_LMM_SetEmmInfoUpdateMmFlag(NAS_EMM_UPDATE_MM_FLAG_VALID);*/

        NAS_EMM_SER_RcvRrcStmsiPagingInd();
    }
    else if (ulCurEmmStat == NAS_LMM_PUB_COMP_EMMSTATE( EMM_MS_REG, EMM_SS_REG_ATTEMPTING_TO_UPDATE))
    {
        /* 由于流程冲突标识为COLLISION_SERVICE，后续发起TAU流程active flag会置上，相当此次TAU也起到了发serviece的作用，
           后面TAU完成后也不会发起SERVICE，因为DRB已经建立成功。
           因此将SER参数都置上，代表也发起了service流程，后面TAU失败或者被拒，会通知erabm service失败*/

        /* 大数据: 设置SER类型为MT Ser */
        NAS_EMM_SetOmMtSerFlag(NAS_EMM_YES);

        /* 大数据: 记录Mt Ser流程启动时间 */
        NAS_EMM_SaveMtSerStartTimeStamp();

        /*Inform RABM that SER init*/
        NAS_EMM_SER_SendRabmReestInd(EMM_ERABM_REEST_STATE_INITIATE);

        /*设置SER触发原因为 NAS_EMM_SER_START_CAUSE_RRC_PAGING*/
        NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_RRC_PAGING);

        /*设置流程冲突标志位*/
        NAS_EMM_TAU_SaveEmmCollisionCtrl(NAS_EMM_COLLISION_SERVICE);

        /*设置TAU发起原因*/
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);

        /*启动TAU Procedure*/
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_PS_PAGING);
    }
    else
    {
       NAS_LMM_EMM_PLMN_LOG_WARN(    "NAS_EMM_PLMN_STmsiPagingProc:Not process the paging with S-TMSI:NAS State Error");
       TLPS_PRINT2LAYER_WARNING(NAS_EMM_PLMN_STmsiPagingProc_ENUM,LNAS_ERROR);
        #if (FEATURE_ON == FEATURE_PTM)
        /* 由于在该状态下丢弃了PS域的PAGING，所以增加CHR上报 */
        NAS_EMM_PagingErrRecord(EMM_OM_ERRLOG_PAGING_PS,EMM_OM_LMM_PAGING_FAIL_CAUSE_ABNORMAL_STATUS);
        #endif
    }

    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_PLMN_CsPagingProc
 Description     : 处理CS PAGING
 Input           : NONE
 Output          : NONE
 Return          : VOS_VOID
 History         :
    1.lihong 00150010       2012.02.22 New Draft
    2.leixiantiao 00258641  2015-06-24 DTS2015061001947不处理CS PAGING问题
    3.sunjitan 00193151     2015-07-09 Modify for MT_CSFB_IMPROVED_PHASEI
*****************************************************************************/
VOS_VOID NAS_EMM_PLMN_CsPagingProc
(
    LRRC_LNAS_PAGING_UE_ID_ENUM_UINT32  enPagingUeId
)
{
    VOS_UINT32                          ulCurEmmStat;
    NAS_LMM_EMM_PLMN_LOG_INFO("NAS_EMM_PLMN_CsPagingProc is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PLMN_CsPagingProc_ENUM, LNAS_ENTRY);

    ulCurEmmStat    = NAS_LMM_PUB_COMP_EMMSTATE(NAS_EMM_CUR_MAIN_STAT, NAS_EMM_CUR_SUB_STAT);

    switch (ulCurEmmStat)
    {
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_NORMAL_SERVICE)         :
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_ATTEMPTING_TO_UPDATE)   :
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_LIMITED_SERVICE)        :
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_WAIT_ACCESS_GRANT_IND)  :
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM):

                NAS_EMM_SER_RcvRrcCsPagingInd(enPagingUeId);
                break;

        default:
                NAS_LMM_EMM_PLMN_LOG_WARN("NAS_EMM_PLMN_CsPagingProc:NAS State cannot process cs paging!");
                TLPS_PRINT2LAYER_WARNING(NAS_EMM_PLMN_CsPagingProc_ENUM, LNAS_ERROR);
                break;
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_StartRatIsValid
 Description     :
 Input           :
 Output          :
 Return          : NAS_LMM_FAIL:非法
                   NAS_LMM_SUCC:合法
 History         :
    1.ZHANGCAIXIA      2011-9-9  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_StartRatIsValid(const MMC_LMM_START_REQ_STRU *pstAppStartReq)
{
    RRMM_RAT_PRIO_ENUM_UINT8    usGsmRatPrio   = pstAppStartReq->aucRatPrioList[RRMM_RAT_TYPE_GSM];
    RRMM_RAT_PRIO_ENUM_UINT8    usWcdmaRatPrio = pstAppStartReq->aucRatPrioList[RRMM_RAT_TYPE_WCDMA];
    RRMM_RAT_PRIO_ENUM_UINT8    usLteRatPrio   = pstAppStartReq->aucRatPrioList[RRMM_RAT_TYPE_LTE];
    RRMM_RAT_PRIO_ENUM_UINT8    usCdma1xRatPrio = pstAppStartReq->aucRatPrioList[RRMM_RAT_TYPE_CDMA1X];
    RRMM_RAT_PRIO_ENUM_UINT8    usHrpdRatPrio   = pstAppStartReq->aucRatPrioList[RRMM_RAT_TYPE_HRPD];

    if (  (RRMM_RAT_PRIO_BUTT <= usGsmRatPrio)
        ||(RRMM_RAT_PRIO_BUTT <= usWcdmaRatPrio)
        ||(RRMM_RAT_PRIO_BUTT <= usLteRatPrio)
        ||(RRMM_RAT_PRIO_BUTT <= usCdma1xRatPrio)
        ||(RRMM_RAT_PRIO_BUTT <= usHrpdRatPrio) )
    {
        NAS_LMM_EMM_PLMN_LOG_ERR("NAS_EMM_StartRatIsExist: MMC START REQ RAT LIST IS VALID ");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_StartRatIsValid_ENUM,LNAS_FAIL);
        return NAS_LMM_FAIL;
    }

    return NAS_LMM_SUCC;
}
/*****************************************************************************
 Function Name   : NAS_EMM_RatListIsValid
 Description     :
 Input           :
 Output          :
 Return          : NAS_LMM_FAIL:非法
                   NAS_LMM_SUCC:合法
 History         :
    1.ZHANGCAIXIA      2011-9-9  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_RatListIsValid(RRMM_RAT_PRIO_ENUM_UINT8    usGsmRatPrio,
                                            RRMM_RAT_PRIO_ENUM_UINT8    usWcdmaRatPrio,
                                            RRMM_RAT_PRIO_ENUM_UINT8    usLteRatPrio)
{
    if (  (RRMM_RAT_PRIO_BUTT <= usGsmRatPrio)
        &&(RRMM_RAT_PRIO_BUTT <= usWcdmaRatPrio)
        &&(RRMM_RAT_PRIO_BUTT <= usLteRatPrio) )
    {
        NAS_LMM_EMM_PLMN_LOG_ERR("NAS_EMM_StartRatIsExist: MMC START REQ RAT LIST IS VALID ");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_RatListIsValid_ENUM,LNAS_FAIL);
        return NAS_LMM_FAIL;
    }

    return NAS_LMM_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_EMM_lteRatIsOnlyExist
 Description     :
 Input           :
 Output          :
 Return          : NAS_LMM_FAIL:接入技术不只有L
                   NAS_LMM_SUCC:接入技术只有L
 History         :
    1.ZHANGCAIXIA      2011-9-9  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_lteRatIsOnlyExist(VOS_VOID)
{
    if (  ( (NAS_LMM_RAT_PRIO_NULL < NAS_LMM_GetCurLtePrio())&&(NAS_LMM_RAT_PRIO_BUTT >NAS_LMM_GetCurLtePrio()))
    &&( (NAS_LMM_RAT_PRIO_NULL == NAS_LMM_GetCurGsmPrio())||(NAS_LMM_RAT_PRIO_BUTT == NAS_LMM_GetCurGsmPrio()))
    &&( (NAS_LMM_RAT_PRIO_NULL == NAS_LMM_GetCurWcdmaPrio())||(NAS_LMM_RAT_PRIO_BUTT ==NAS_LMM_GetCurWcdmaPrio() )))
    {
        return NAS_LMM_SUCC;
    }

    NAS_LMM_EMM_PLMN_LOG_ERR("NAS_EMM_lteRatIsExist: MMC START REQ RAT LIST LTE IS NOT ONLY EXIST ");
    TLPS_PRINT2LAYER_ERROR(NAS_EMM_lteRatIsOnlyExist_ENUM,LNAS_FAIL);
    return NAS_LMM_FAIL;
}


/*****************************************************************************
  3.2  开机相关流程处理 Function
*****************************************************************************/


/*****************************************************************************
 Function Name   : NAS_EMM_MmcStartCheck
 Description     : MMC_LMM_START_REQ_STRU入参检查，若检查成功，将开机参数转换为
                   EMM自己的开机参数
 Input           : pstAppStartReq
 Output          : pstEmmStartInfo
 Return          : NAS_LMM_FAIL: 检查不通过
                   NAS_LMM_SUCC: 检查通过

 History         :
    1.HanLufeng 41410      2011-3-29  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MmcStartCheck(
                const MMC_LMM_START_REQ_STRU          *pstAppStartReq,
                      NAS_EMM_START_INFO_STRU         *pstEmmStartInfo)
{
    VOS_UINT32 ulCnt                    = NAS_COMM_NULL;


    /* EMM自己保存的接入技术赋初始值 */
    for(ulCnt = 0; ulCnt < NAS_LMM_RAT_TYPE_BUTT; ulCnt++)
    {
        pstEmmStartInfo->aucRatPrioList[ulCnt] = NAS_LMM_RAT_PRIO_BUTT;
    }

    /* 如果介入技术列表都为空，则返回错误 */
    if(NAS_LMM_FAIL == NAS_EMM_StartRatIsValid(pstAppStartReq))
    {
        NAS_LMM_EMM_PLMN_LOG_ERR("NAS_EMM_MmcStartCheck: MMC START REQ RAT LIST IS NULL ");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MmcStartCheck_ENUM,LNAS_FAIL);
        return  NAS_LMM_FAIL;
    }

    /* 保存接入技术 */
    for(ulCnt = 0; ulCnt < NAS_LMM_RAT_TYPE_BUTT; ulCnt++)
    {
        pstEmmStartInfo->aucRatPrioList[ulCnt] = pstAppStartReq->aucRatPrioList[ulCnt];
    }

    /*--------转换为LMM自己的待机类型 NAS_EMM_RAT_TYPE_ENUM_UINT8 -------*/
    if(MMC_LMM_TRANSCEIVER_TYPE_SINGLE == pstAppStartReq->ulTransceiverType)
    {
        pstEmmStartInfo->ulTransceiverType = NAS_EMM_TRANSCEIVER_TYPE_SINGLE;
    }
    else if(MMC_LMM_TRANSCEIVER_TYPE_DUAL == pstAppStartReq->ulTransceiverType)
    {
        pstEmmStartInfo->ulTransceiverType = NAS_EMM_TRANSCEIVER_TYPE_DUAL;
    }
    else
    {
        NAS_LMM_EMM_PLMN_LOG1_ERR("NAS_EMM_MmcStartCheck: ulTransceiverType = ",
                                 pstAppStartReq->ulTransceiverType);
        TLPS_PRINT2LAYER_ERROR1(NAS_EMM_MmcStartCheck_ENUM,LNAS_FUNCTION_LABEL1,
                                 pstAppStartReq->ulTransceiverType);
        return  NAS_LMM_FAIL;
    }



    /*--------检查卡状态参数 -------*/
    if( (MMC_LMM_USIM_VALID   != pstAppStartReq->ulUsimState) &&
        (MMC_LMM_USIM_INVALID != pstAppStartReq->ulUsimState))
    {
        NAS_LMM_EMM_PLMN_LOG1_ERR("NAS_EMM_MmcStartCheck: ulUsimState = ",
                                 pstAppStartReq->ulUsimState);
        TLPS_PRINT2LAYER_ERROR1(NAS_EMM_MmcStartCheck_ENUM,LNAS_FUNCTION_LABEL2,
                                 pstAppStartReq->ulUsimState);
        return  NAS_LMM_FAIL;
    }

    return  NAS_LMM_SUCC;


}

/*****************************************************************************
 Function Name   : NAS_EMM_EsmSendStartNotifyInd
 Description     : 向ESM发送ID_EMM_ESM_START_NOTIFY_IND消息
 Input           : VOS_VOID
 Output          : VOS_VOID
 Return          : VOS_VOID
 History         :
    1.sunjitan 00193151     2015-01-15  Draft Enact
*****************************************************************************/
VOS_VOID    NAS_EMM_EsmSendStartNotifyInd (VOS_VOID)
{
    EMM_ESM_START_NOTIFY_IND_STRU     *pEmmEsmStartNotifyMsg;

    pEmmEsmStartNotifyMsg = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(EMM_ESM_START_NOTIFY_IND_STRU));

    /*判断申请结果，若失败打印错误并退出*/
    if (NAS_EMM_NULL_PTR == pEmmEsmStartNotifyMsg)
    {
        /*打印错误*/
        NAS_LMM_EMM_PLMN_LOG_ERR("NAS_EMM_EsmSendStartNotifyInd: MSG ALLOC ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_EsmSendStartNotifyInd_ENUM,LNAS_NULL_PTR);
        return;
    }

    /*填充消息头*/
    NAS_EMM_COMP_AD_ESM_MSG_HEADER(pEmmEsmStartNotifyMsg,
                                    (sizeof(EMM_ESM_START_NOTIFY_IND_STRU)-
                                    NAS_EMM_LEN_VOS_MSG_HEADER));

    /*填充消息ID*/
    pEmmEsmStartNotifyMsg->ulMsgId  = ID_EMM_ESM_START_NOTIFY_IND;

    /*向ESM发送ID_EMM_ESM_STOP_NOTIFY_IND消息*/
    NAS_LMM_SEND_MSG(pEmmEsmStartNotifyMsg);

    return;

}

/*****************************************************************************
 Function Name   : NAS_EMM_MsNullSsWaitAppStartReqMsgAppStartReq
 Description     : 在MS_NULL + SS_NULL_WAIT_APP_START_REQ状态下，
                   收到APP_MM_START_REQ消息，消息响应处理程序
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lining 00141619      2008-10-16  Draft Enact
    2.yangfan 00159566     2009-09-24  Modify
    3.yangfan 00159566     2010-02-24  Modify  BJ9D02775
    4.sunbing 49683        2012-05-28  有卡但读IMSI失败，认为无卡，不再复位
*****************************************************************************/
VOS_UINT32    NAS_EMM_MsNullSsWaitAppStartReqMsgAppStartReq(
                    VOS_UINT32                              ulMsgId,
                    VOS_VOID                                *pMsg )
{
    NAS_EMM_FSM_STATE_STRU              stEmmState;
    MMC_LMM_START_REQ_STRU             *pstAppStartReq;
    VOS_UINT32                          ulSendResult;
#if (VOS_OS_VER != VOS_WIN32)
    FTM_TMODE_ENUM                      enMspFtmMode = EN_FTM_TMODE_SIGNAL ;
#endif
    NAS_EMM_START_INFO_STRU             stEmmStartInfo;
    VOS_UINT32                          ulRst;

    (VOS_VOID)ulMsgId;

    pstAppStartReq                      = pMsg;

    /* 打印进入该函数，INFO_LEVEL */
    NAS_LMM_EMM_PLMN_LOG_INFO("NAS_EMM_MsNullSsWaitAppStartReqMsgAppStartReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsNullSsWaitAppStartReqMsgAppStartReq_ENUM,LNAS_ENTRY);

    /* 入参检查，若成功，转换接口开机参数类型到EMM的参数类型 */
    ulRst = NAS_EMM_MmcStartCheck(pstAppStartReq, &stEmmStartInfo);
    if(NAS_LMM_FAIL ==  ulRst)
    {   /* 若出错，通知MMC开机失败  */

        /* 向APP发送APP_MM_START_CNF消息*/
        ulRst = NAS_EMM_PLMN_SendAppStartCnf(MMC_LMM_FAIL,
                                    pstAppStartReq->ulOpId);
        if (NAS_EMM_PLMN_OK != ulRst)
        {
            /* 打印函数，ERROR_LEVEL */
            NAS_LMM_EMM_PLMN_LOG1_ERR("NAS_EMM_MsNullSsWaitAppStartReqMsgAppStartReq : Send Msg Failure!!! ulSendOuterMsgResult=",
                                     ulRst);
            TLPS_PRINT2LAYER_ERROR1(NAS_EMM_MsNullSsWaitAppStartReqMsgAppStartReq_ENUM,LNAS_SND_RST,ulRst);
        }

        NAS_LMM_EMM_PLMN_LOG_WARN("NAS_EMM_MsNullSsWaitAppStartReqMsgAppStartReq: MSG IE ERROR!!!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsNullSsWaitAppStartReqMsgAppStartReq_ENUM,LNAS_MSG_INVALID);
        return  NAS_LMM_MSG_HANDLED;
    }
    /* 清除大数据本地存储信息 */
    NAS_LMM_MEM_SET_S(&g_stEmmOmEntity, sizeof(NAS_LMM_OM_ENTITY_STRU), 0, sizeof(NAS_LMM_OM_ENTITY_STRU));

    /*EMM&MMC 全局变量清空 */
    NAS_LMM_EmmAndMmcGlobInfoClear();

    /* 将保存上报信息的全局变量清除 */
    NAS_LMM_MEM_SET_S(&g_stEmmOmInfo, sizeof(OM_EMM_STATE_INFO_STRU), 0, sizeof(OM_EMM_STATE_INFO_STRU));

    /* EMM Info 赋初始值：与USIM/NV无关的赋值为有效值；
    与USIM/NV有关的，赋值为无效值，等读USIM/NV时再重新赋值为有效值 */
    NAS_LMM_EmmInfoInit();

    /* 保存开机MMC下发的UTRAN模式 */
    NAS_LMM_SetEmmInfoUtranMode(pstAppStartReq->enUtranMode);

    /* 各子模块控制变量赋初始值 */
    NAS_LMM_EmmSubModGlobInit();

    /* 通知ESM开机 */
    NAS_EMM_EsmSendStartNotifyInd();

    /* Added by wangchen 00209181 begin for 搜网优化 2015-05-30 */
    /* 通知CSS模块开机 */
    NAS_LMM_SendCssStartInd();
    /* Added by wangchen 00209181 begin for 搜网优化 2015-05-30 */


    /* 设置App消息的相关参数 */
    /*如果收到的OpId为0xffff,则StartReq为收到ErrInd后发起的内部消息 */
    /* 将保存参数移至发挂起之前 */
    if (NAS_EMM_INTRA_APP_START_OPID != pstAppStartReq->ulOpId)
    {
        NAS_EMM_SaveAppMsgPara(pstAppStartReq->ulMsgId,pstAppStartReq->ulOpId);

        /* 保存开机消息中的各种UE模式信息，以待给RRC发送开机消息时使 */
        NAS_EMM_SAVE_START_INFO(stEmmStartInfo);
    }
    /* V7R1，开机LNAS处于挂起态，也要通知ESM和ERABM挂起，不等响应 */
    /* 发送 ESM 挂起消息*/
    NAS_EMM_SendEsmSuspendInd();

    /* 发送 ERABM 挂起消息*/
    NAS_EMM_SendErabmSuspendInd();

#if (VOS_OS_VER != VOS_WIN32)
    /*产线上无卡模式，则关闭安全*/
    if((LPS_OM_GetTmode(&enMspFtmMode)== ERR_MSP_SUCCESS)&&( EN_FTM_TMODE_SIGNAL_NOCARD == enMspFtmMode))
    {
        NAS_LMM_EMM_PLMN_LOG_INFO("NAS_EMM_MsNullSsWaitAppStartReqMsgAppStartReq : EN_FTM_TMODE_SIGNAL_NOCARD, Set USIM feature as soft!");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsNullSsWaitAppStartReqMsgAppStartReq_ENUM,LNAS_FUNCTION_LABEL1);
        g_ulSmcControl = NAS_EMM_SMC_CLOSE;
    }
#endif
    /*读IMSI成功，才认为有卡，部分USIM文件是MMC读取的，LMM从MMC那里读到LMM中来 */
    if((MMC_LMM_USIM_VALID == pstAppStartReq->ulUsimState)
       &&(NAS_LMM_USIM_READ_SUCC == NAS_LMM_ReadUsimFileImsi()))
    {
        /* 设置保存在EMM中的卡状态全局变量 */
        NAS_EMM_SetUsimState(NAS_LMM_SIM_STATUS_AVAILABLE);
        /* 然后再读取LTE自己的文件 */
        NAS_LMM_ReadLteUsimFile();

        /* 启动TI_NAS_EMM_WAIT_MMC_START_CNF_TIMER */
        NAS_LMM_StartStateTimer(TI_NAS_LMM_TIMER_WAIT_USIM_CNF);

        /* 将状态转移至MS_NULL + SS_WAIT_MMC_START_CNF状态 */
        stEmmState.enFsmId                    = NAS_LMM_PARALLEL_FSM_EMM;
        stEmmState.enMainState                = EMM_MS_NULL;
        stEmmState.enSubState                 = EMM_SS_NULL_WAIT_READING_USIM;
        stEmmState.enStaTId                   = TI_NAS_LMM_TIMER_WAIT_USIM_CNF;
        NAS_LMM_StaTransProc(stEmmState);

        return  NAS_LMM_MSG_HANDLED;
    }

    /*卡不可用，给MMC/RRC发送开机消息，进入无卡开机*/
    NAS_LMM_EMM_PLMN_LOG_WARN("NAS_EMM_MsNullSsWaitAppStartReqMsgAppStartReq : Hard Usim UNAVAILABLE:");
    TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsNullSsWaitAppStartReqMsgAppStartReq_ENUM,LNAS_FUNCTION_LABEL2);

    /* 设置保存在EMM中的卡状态全局变量 */
    NAS_EMM_SetUsimState(NAS_LMM_SIM_STATUS_UNAVAILABLE);


    /* 向MMC发送MMC_EMM_START_REQ(正常启动)消息 */
    ulSendResult = NAS_EMM_PLMN_SendMmcStartReq(EMMC_EMM_START_REQ_CAUSE_NORMAL_START);
    if (NAS_EMM_PLMN_ERR == ulSendResult)
    {
        /* 打印函数，ERROR_LEVEL */
        NAS_LMM_EMM_PLMN_LOG_ERR("NAS_EMM_PLMN_SendMmcStartReq : Send IntraMsg Failure!!!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsNullSsWaitAppStartReqMsgAppStartReq_ENUM,LNAS_FUNCTION_LABEL3);
        return NAS_LMM_MSG_HANDLED;
    }

    /* 启动TI_NAS_EMM_WAIT_MMC_START_CNF_TIMER */
    NAS_LMM_StartStateTimer(TI_NAS_EMM_WAIT_MMC_START_CNF_TIMER);

    /* 将状态转移至MS_NULL + SS_WAIT_MMC_START_CNF状态 */
    stEmmState.enFsmId                    = NAS_LMM_PARALLEL_FSM_EMM;
    stEmmState.enMainState                = EMM_MS_NULL;
    stEmmState.enSubState                 = EMM_SS_NULL_WAIT_MMC_START_CNF;
    stEmmState.enStaTId                   = TI_NAS_EMM_WAIT_MMC_START_CNF_TIMER;
    NAS_LMM_StaTransProc(stEmmState);

    return NAS_LMM_MSG_HANDLED;
}

#if (VOS_OS_VER == VOS_WIN32)
/*****************************************************************************
 Function Name   : NAS_EMM_SendMmcErrInd
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.HanLufeng 41410      2011-3-4  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_SendMmcErrInd( VOS_UINT32 ulErrTpye )
{

    LMM_MMC_ERR_IND_STRU      *pLmmMmcErrIndMsg    = NAS_EMM_NULL_PTR;

    NAS_LMM_PUBM_LOG_INFO( "NAS_EMM_SendMmcErrInd: enter. RESET.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SendMmcErrInd_ENUM,LNAS_ENTRY);

    /*申请MMC内部消息 */
    pLmmMmcErrIndMsg = (VOS_VOID *)NAS_LMM_GetLmmMmcMsgBuf(sizeof(LMM_MMC_ERR_IND_STRU));

    if(NAS_EMM_NULL_PTR == pLmmMmcErrIndMsg)
    {
        NAS_LMM_PUBM_LOG_ERR( "NAS_EMM_SendMmcErrInd: MSG ALLOC ERR !!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SendMmcErrInd_ENUM,LNAS_NULL_PTR);
        return;
    }

    NAS_LMM_MEM_SET_S(pLmmMmcErrIndMsg,sizeof(LMM_MMC_ERR_IND_STRU),0,sizeof(LMM_MMC_ERR_IND_STRU));

    /* 填写LMM_MMC_ERR_IND_STRU 的DOPRA消息头 */
    EMM_PUBU_COMP_MMC_MSG_HEADER(pLmmMmcErrIndMsg,
            sizeof(LMM_MMC_ERR_IND_STRU) - EMM_LEN_VOS_MSG_HEADER);

    /* 填写EMM_RABM_RRC_CON_REL_IND 的消息ID标识 */
    pLmmMmcErrIndMsg->ulMsgId           = ID_LMM_MMC_ERR_IND;

    /* 发送消息 */
    NAS_LMM_SendLmmMmcMsg(                    pLmmMmcErrIndMsg);

    return;

}
#endif

/*****************************************************************************
 Function Name   : NAS_EMM_MsNotNullSsAnyStateMsgAppStartReq
 Description     : 在主状态非空状态下，收到APP_MM_START_REQ消息，消息响应处理程序
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lining 00141619      2008-10-16  Draft Enact

*****************************************************************************/
VOS_UINT32    NAS_EMM_MsNotNullSsAnyStateMsgAppStartReq(
                    VOS_UINT32                              ulMsgId,
                    VOS_VOID                                *pMsg )
{
    VOS_UINT32                          ulSendResult;
    NAS_EMM_FSM_STATE_STRU              EmmState;
    MMC_LMM_START_REQ_STRU             *pstAppStartReq;

    (VOS_VOID)ulMsgId;

    NAS_EMM_PLMN_INIT_EMMSTATE(EmmState);

    /* 打印进入该函数，INFO_LEVEL */
    NAS_LMM_EMM_PLMN_LOG_INFO("NAS_EMM_MsNotNullSsAnyStateMsgAppStartReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsNotNullSsAnyStateMsgAppStartReq_ENUM,LNAS_ENTRY);

    pstAppStartReq = pMsg;

    /* 函数输入指针参数检查 */
    if (VOS_NULL_PTR == pMsg)
    {
        /* 打印异常，ERROR_LEVEL */
        NAS_LMM_EMM_PLMN_LOG_ERR("NAS_EMM_MsNotNullSsAnyStateMsgAppStartReq: MSG PARAM NULL POINTER ERROR!!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsNotNullSsAnyStateMsgAppStartReq_ENUM,LNAS_NULL_PTR);
        return NAS_LMM_ERR_CODE_PARA_INVALID;
    }

    /* 状态匹配检查,若不匹配,退出 */
    if (EMM_MS_NULL == EmmState.enMainState)
    {
        NAS_LMM_EMM_PLMN_LOG_WARN("NAS_EMM_MsNotNullSsAnyStateMsgAppStartReq: STATE ERROR!!!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsNotNullSsAnyStateMsgAppStartReq_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    /* 向APP发送APP_MM_START_CNF消息(回复开机成功，已经开机) */
    ulSendResult = NAS_EMM_PLMN_SendAppStartCnf(MMC_LMM_SUCC, pstAppStartReq->ulOpId);
    if (NAS_EMM_PLMN_OK != ulSendResult)
    {
        /* 打印函数，ERROR_LEVEL */
        NAS_LMM_EMM_PLMN_LOG1_ERR("NAS_EMM_PLMN_SendAppStartCnf : Send Msg Failure!!! ulSendResult=",
                                 ulSendResult);
        TLPS_PRINT2LAYER_ERROR1(NAS_EMM_MsNotNullSsAnyStateMsgAppStartReq_ENUM,LNAS_SND_RST,ulSendResult);
        return NAS_LMM_MSG_HANDLED;
    }

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_WhenStopingThenMsgAppStartReq
 Description     : 在EMM_MS_NULL + EMM_SS_NULL_WAIT_SWITCH_OFF 或
                     EMM_MS_NULL + EMM_SS_NULL_WAIT_MMC_STOP_CNF 或
                     EMM_MS_NULL + EMM_SS_NULL_WAIT_SWITCH_OFF状态下，
                   收到APP发来的APP_MM_START_REQ消息，消息响应处理程序
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lining 00141619      2008-10-16  Draft Enact
    2.hanlufeng 41410      2009-06-22
    3.X00148705            2010-03-27  删除停定时器TI_NAS_EMM_WAIT_RRC_STOP_CNF_TIMER
*****************************************************************************/
VOS_UINT32    NAS_EMM_WhenStopingThenMsgAppStartReq(
                    VOS_UINT32                              ulMsgId,
                    VOS_VOID                                *pMsg )
{
    VOS_UINT32                          ulSendResult;
    MMC_LMM_START_REQ_STRU             *pstAppStartReq;

    (VOS_VOID)ulMsgId;

    /* 打印进入该函数， INFO_LEVEL */
    NAS_LMM_EMM_PLMN_LOG_INFO("NAS_EMM_WhenStopingThenMsgAppStartReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_WhenStopingThenMsgAppStartReq_ENUM,LNAS_ENTRY);

    pstAppStartReq                      = pMsg;

    /* 函数输入指针参数检查 */
    if (VOS_NULL_PTR == pMsg)
    {
        /* 打印异常，ERROR_LEVEL */
        NAS_LMM_EMM_PLMN_LOG_ERR("NAS_EMM_WhenStopingThenMsgAppStartReq: MSG PARAM NULL POINTER ERROR!!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_WhenStopingThenMsgAppStartReq_ENUM,LNAS_NULL_PTR);
        return NAS_LMM_ERR_CODE_PARA_INVALID;
    }

    /* 说明已经收到关机消息，但关机的整个过程没有完成，还没有回复APP_MM_STOP_CNF
    消息，直接回复APP开机失败－－APP_MM_START_CNF消息（回复开机失败，RRC在关机）*/
    ulSendResult = NAS_EMM_PLMN_SendAppStartCnf(MMC_LMM_FAIL, pstAppStartReq->ulOpId);
    if (NAS_EMM_PLMN_OK != ulSendResult)
    {
        /* 打印函数，ERROR_LEVEL */
        NAS_LMM_EMM_PLMN_LOG1_ERR("NAS_EMM_PLMN_SendAppStartCnf : Send Msg Failure!!! ulSendResult=",
                                 ulSendResult);
        TLPS_PRINT2LAYER_ERROR1(NAS_EMM_WhenStopingThenMsgAppStartReq_ENUM,LNAS_SND_RST,ulSendResult);
    }

    return NAS_LMM_MSG_HANDLED;
}


/*****************************************************************************
 Function Name   : NAS_EMM_MsNullSsWaitMmcStartCnfMsgMmcStartCnf
 Description     : 在MS_NULL + SS_NULL_WAIT_MMC_START_CNF状态下，收到MMC发来的
                   MMC_EMM_START_CNF消息，消息响应处理程序
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lining 00141619      2008-9-16  Draft Enact
    2.X00148705            2010-03-27 修改发送失败的处理

*****************************************************************************/
VOS_UINT32    NAS_EMM_MsNullSsWaitMmcStartCnfMsgMmcStartCnf(
                    VOS_UINT32                              ulMsgId,
                    VOS_VOID                                *pMsg )
{
    VOS_UINT32                          ulSendResult;
    NAS_EMM_FSM_STATE_STRU              EmmState;

    (VOS_VOID)ulMsgId;

    /* 打印进入该函数， INFO_LEVEL */
    NAS_LMM_EMM_PLMN_LOG_INFO("NAS_EMM_MsNullSsWaitMmcStartCnfMsgMmcStartCnf is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsNullSsWaitMmcStartCnfMsgMmcStartCnf_ENUM,LNAS_ENTRY);

    NAS_EMM_PLMN_INIT_EMMSTATE(EmmState);


    /* 函数输入指针参数检查 */
    if (VOS_NULL_PTR == pMsg)
    {
        /* 打印异常，ERROR_LEVEL */
        NAS_LMM_EMM_PLMN_LOG_ERR("NAS_EMM_MsNullSsWaitMmcStartCnfMsgMmcStartCnf: MSG PARAM NULL POINTER ERROR!!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsNullSsWaitMmcStartCnfMsgMmcStartCnf_ENUM,LNAS_NULL_PTR);
        return NAS_LMM_ERR_CODE_PARA_INVALID;
    }

    /* 状态匹配检查,若不匹配,退出 */
    if (NAS_EMM_PLMN_CHK_STAT_INVALID(EMM_MS_NULL, EMM_SS_NULL_WAIT_MMC_START_CNF))
    {
        NAS_LMM_EMM_PLMN_LOG_WARN("NAS_EMM_MsNullSsWaitMmcStartCnfMsgMmcStartCnf: STATE ERROR!!!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsNullSsWaitMmcStartCnfMsgMmcStartCnf_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    /*检查卡状态，当卡无效则重置全局变量*/
    if (NAS_LMM_SIM_STATUS_UNAVAILABLE == NAS_LMM_GetSimState())
    {
        NAS_EMM_NoUsimInit();
    }

    /* 停止TI_NAS_EMM_WAIT_MMC_START_CNF_TIMER */
    NAS_LMM_StopStateTimer(TI_NAS_EMM_WAIT_MMC_START_CNF_TIMER);

    /* 向RRC发送RRC_MM_START_REQ消息 */
    ulSendResult = NAS_EMM_PLMN_SendRrcStartReq();
    if (NAS_EMM_PLMN_OK != ulSendResult)
    {
        /* 打印函数，ERROR_LEVEL */
        NAS_LMM_EMM_PLMN_LOG1_ERR("NAS_EMM_PLMN_SendRrcStartReq : Send Msg Failure!!! ulSendResult=",
                                 ulSendResult);
        TLPS_PRINT2LAYER_ERROR1(NAS_EMM_MsNullSsWaitMmcStartCnfMsgMmcStartCnf_ENUM,LNAS_SND_RST,ulSendResult);
    }

    /* 启动TI_NAS_EMM_WAIT_RRC_START_CNF_TIMER */
    NAS_LMM_StartStateTimer(TI_NAS_EMM_WAIT_RRC_START_CNF_TIMER);

    /* 将状态转移至MS_NULL + SS_NULL_WAIT_RRC_START_CNF状态 */
    EmmState.enMainState                = EMM_MS_NULL;
    EmmState.enSubState                 = EMM_SS_NULL_WAIT_RRC_START_CNF;
    EmmState.enStaTId                   = TI_NAS_EMM_WAIT_RRC_START_CNF_TIMER;
    NAS_LMM_StaTransProc(EmmState);

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsNullSsWaitMmcStartCnfMsgTimerExp
 Description     : 在MS_NULL + SS_NULL_WAIT_MMC_START_CNF状态下，
                   TI_NAS_EMM_WAIT_MMC_START_CNF_TIMER超时处理程序
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lining 00141619      2008-10-16  Draft Enact

*****************************************************************************/
VOS_UINT32    NAS_EMM_MsNullSsWaitMmcStartCnfMsgTimerExp(
                    VOS_UINT32                              ulMsgId,
                    VOS_VOID                                *pMsg )
{
    VOS_UINT32                          ulSendResult;
    NAS_EMM_FSM_STATE_STRU              EmmState;

    (VOS_VOID)ulMsgId;


    NAS_EMM_PLMN_INIT_EMMSTATE(EmmState);

    /* 打印进入该函数， INFO_LEVEL */
    NAS_LMM_EMM_PLMN_LOG_NORM("NAS_EMM_MsNullSsWaitMmcStartCnfMsgTimerExp is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsNullSsWaitMmcStartCnfMsgTimerExp_ENUM,LNAS_ENTRY);

    /* 函数输入指针参数检查 */
    if (VOS_NULL_PTR == pMsg)
    {
        /* 打印异常，ERROR_LEVEL */
        NAS_LMM_EMM_PLMN_LOG_ERR("NAS_EMM_MsNullSsWaitMmcStartCnfMsgTimerExp: MSG PARAM NULL POINTER ERROR!!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsNullSsWaitMmcStartCnfMsgTimerExp_ENUM,LNAS_NULL_PTR);
        return NAS_LMM_ERR_CODE_PARA_INVALID;
    }

    /* 状态匹配检查,若不匹配,退出 */
    if (NAS_EMM_PLMN_CHK_STAT_INVALID(EMM_MS_NULL, EMM_SS_NULL_WAIT_MMC_START_CNF))
    {
        NAS_LMM_EMM_PLMN_LOG_WARN("NAS_EMM_MsNullSsWaitMmcStartCnfMsgTimerExp: STATE ERROR!!!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsNullSsWaitMmcStartCnfMsgTimerExp_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    if (NAS_EMM_PLMN_OK == NAS_EMM_CheckAppMsgPara(ID_MMC_LMM_START_REQ))
    {
        /* 向APP发送APP_MM_START_CNF消息（回复开机失败，等待MMC启动超时） */
        ulSendResult = NAS_EMM_PLMN_SendAppStartCnf(MMC_LMM_FAIL,NAS_EMM_GetAppMsgOpId());

        if (NAS_EMM_PLMN_OK != ulSendResult)
        {
            /* 打印函数，ERROR_LEVEL */
            NAS_LMM_EMM_PLMN_LOG1_ERR("NAS_EMM_PLMN_SendAppStartCnf : Send Msg Failure!!! ulSendResult=",
                                     ulSendResult);
            TLPS_PRINT2LAYER_ERROR1(NAS_EMM_MsNullSsWaitMmcStartCnfMsgTimerExp_ENUM,LNAS_SND_RST,ulSendResult);
            return NAS_LMM_MSG_HANDLED;
        }
    }

    /*清空APP参数*/
    NAS_EMM_ClearAppMsgPara();

    /* 将状态转移至MS_NULL + SS_NULL_WAIT_APP_START_REQ状态 */
    EmmState.enMainState                = EMM_MS_NULL;
    EmmState.enSubState                 = EMM_SS_NULL_WAIT_APP_START_REQ;
    EmmState.enStaTId                   = TI_NAS_EMM_STATE_NO_TIMER;
    NAS_LMM_StaTransProc(EmmState);

    return NAS_LMM_MSG_HANDLED;
}


/*****************************************************************************
 Function Name   : NAS_EMM_MsNullSsWaitRrcStartCnfMsgRrcStartCnf
 Description     : 在MS_NULL + SS_NULL_WAIT_RRC_START_CNF状态下，收到RRC发来的
                   RRC_MM_START_CNF消息，消息响应处理程序
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lining 00141619      2008-9-16  Draft Enact
    2.X00148705            2010-03-27 修改发送失败的处理

*****************************************************************************/
VOS_UINT32    NAS_EMM_MsNullSsWaitRrcStartCnfMsgRrcStartCnf(
                    VOS_UINT32                              ulMsgId,
                    VOS_VOID                                *pMsg )
{
    VOS_UINT32                          ulSendOuterMsgResult;
    VOS_UINT32                          ulSendInnerMsgResult;
    VOS_UINT32                          ulAppRslt;
    NAS_EMM_FSM_STATE_STRU              stEmmState;
    LRRC_LNAS_START_RESULT_ENUM_UINT32    enResult;
    NAS_LMM_SIM_STAT_ENUM_UINT32        ulSimState;
    LRRC_LMM_START_CNF_STRU               *pstRrcMmStartCnfMsg = (LRRC_LMM_START_CNF_STRU*)(pMsg);

    (VOS_VOID)ulMsgId;

    NAS_EMM_PLMN_INIT_EMMSTATE(stEmmState);

    /* 打印进入该函数， INFO_LEVEL */
    NAS_LMM_EMM_PLMN_LOG_NORM("NAS_EMM_MsNullSsWaitRrcStartCnfMsgRrcStartCnf is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsNullSsWaitRrcStartCnfMsgRrcStartCnf_ENUM,LNAS_ENTRY);

    /* 函数输入指针参数检查 */
    if (VOS_NULL_PTR == pMsg)
    {
        /* 打印异常，ERROR_LEVEL */
        NAS_LMM_EMM_PLMN_LOG_ERR("NAS_EMM_MsNullSsWaitRrcStartCnfMsgRrcStartCnf: MSG PARAM NULL POINTER ERROR!!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsNullSsWaitRrcStartCnfMsgRrcStartCnf_ENUM,LNAS_NULL_PTR);
        return NAS_LMM_ERR_CODE_PARA_INVALID;
    }

    /* 状态匹配检查,若不匹配,退出 */
    if (NAS_EMM_PLMN_CHK_STAT_INVALID(EMM_MS_NULL, EMM_SS_NULL_WAIT_RRC_START_CNF))
    {
        NAS_LMM_EMM_PLMN_LOG_WARN("NAS_EMM_MsNullSsWaitRrcStartCnfMsgRrcStartCnf: STATE ERROR!!!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsNullSsWaitRrcStartCnfMsgRrcStartCnf_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    /* 停止TI_NAS_EMM_WAIT_RRC_START_CNF_TIMER */
    NAS_LMM_StopStateTimer(TI_NAS_EMM_WAIT_RRC_START_CNF_TIMER);

    /* 处理RRCMmStartCnfMsg启动结果*/
    enResult                            = pstRrcMmStartCnfMsg->enResult;
    if(LRRC_LNAS_START_SUCCESS == enResult)
    {
        #if (FEATURE_LPP == FEATURE_ON)
        NAS_EMM_SndLppStartInd();
        #endif
        ulAppRslt = MMC_LMM_SUCC;
        if(PS_SUCC == LPS_OM_IsTestMode())
        {
            /* 开机之后根据之前保存在全局变量中的T3402，来修改T3402时长 */
            NAS_LMM_ModifyPtlTimer(TI_NAS_EMM_PTL_T3402,g_ulEmmT3402length);

            /* 给MMC发送当前的T3402时长 */
            NAS_EMM_SendMMCT3402LenNotify(g_ulEmmT3402length);
        }
    }
    else
    {
        ulAppRslt = MMC_LMM_FAIL;
        /*如果开机失败，则直接让封装底软的接口reboot modem以便保存现场*/
        NAS_EMM_SendMmcErrInd(NAS_EMM_REBOOT_TYPE_RRC_START_FAIL);
    }

    if (NAS_EMM_PLMN_OK == NAS_EMM_CheckAppMsgPara(ID_MMC_LMM_START_REQ))
    {
        /* 向APP发送APP_MM_START_CNF消息*/
        ulSendOuterMsgResult = NAS_EMM_PLMN_SendAppStartCnf(ulAppRslt,
                                    NAS_EMM_GetAppMsgOpId());
        if (NAS_EMM_PLMN_OK != ulSendOuterMsgResult)
        {
            /* 打印函数，ERROR_LEVEL */
            NAS_LMM_EMM_PLMN_LOG1_ERR("NAS_EMM_PLMN_SendAppStartCnf : Send Msg Failure!!! ulSendOuterMsgResult=",
                                     ulSendOuterMsgResult);
            TLPS_PRINT2LAYER_ERROR1(NAS_EMM_MsNullSsWaitRrcStartCnfMsgRrcStartCnf_ENUM,LNAS_SND_RST,ulSendOuterMsgResult);
        }
    }

    /*清空APP参数*/
    NAS_EMM_ClearAppMsgPara();

    /* 启动结果为RRC_NAS_START_SUCCESS的处理*/
    if(LRRC_LNAS_START_SUCCESS == enResult)
    {
        /*根据卡是否存在，转移EMM的状态*/
        ulSimState                          = NAS_LMM_GetSimState();

        if(NAS_LMM_SIM_STATUS_AVAILABLE == ulSimState)
        {
            /* 将状态转移至MS_DEREG + SS_PLMN_SEARCH状态 */
            stEmmState.enMainState          = EMM_MS_DEREG;
            stEmmState.enSubState           = EMM_SS_DEREG_NO_CELL_AVAILABLE;
            stEmmState.enStaTId             = TI_NAS_EMM_STATE_NO_TIMER;
        }
        else
        {
            /* 下发内部UsimStatusInd消息，通知卡无效，发起Any小区搜索 */
            /*NAS_EMMC_SendIntraUsimStatusInd(USIMM_CARD_STATUS_ABSENT);*/

            /* 将状态转移至MS_DEREG + SS_PLMN_SEARCH状态 */
            stEmmState.enMainState          = EMM_MS_DEREG;
            stEmmState.enSubState           = EMM_SS_DEREG_NO_IMSI;
            stEmmState.enStaTId             = TI_NAS_EMM_STATE_NO_TIMER;
        }
    }

    /* 启动结果不为RRC_NAS_START_SUCCESS的处理*/
    else
    {
        /* 向MMC发送MMC_EMM_STOP_REQ消息 */
        ulSendInnerMsgResult = NAS_EMM_PLMN_SendMmcStopReq();
        if (NAS_EMM_PLMN_ERR == ulSendInnerMsgResult)
        {
            /* 打印函数，ERROR_LEVEL */
            NAS_LMM_EMM_PLMN_LOG_ERR("NAS_EMM_PLMN_SendMmcStopReq : Send IntraMsg Failure!!!");
            TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsNullSsWaitRrcStartCnfMsgRrcStartCnf_ENUM,LNAS_FUNCTION_LABEL1);
        }

        /* 将状态转移至EMM_MS_NULL + EMM_SS_NULL_WAIT_APP_START_REQ状态 */
        stEmmState.enMainState          = EMM_MS_NULL;
        stEmmState.enSubState           = EMM_SS_NULL_WAIT_APP_START_REQ;
        stEmmState.enStaTId             = TI_NAS_EMM_STATE_NO_TIMER;
    }

    /* 改变状态 */
    NAS_LMM_StaTransProc(stEmmState);

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsNullSsWaitRrcStartCnfMsgTimerExp
 Description     : 在MS_NULL + SS_NULL_WAIT_RRC_START_CNF状态下，
                   TI_NAS_EMM_WAIT_RRC_START_CNF_TIMER超时处理程序
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lining 00141619      2008-10-16  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsNullSsWaitRrcStartCnfMsgTimerExp(
                VOS_UINT32              ulMsgId,
                VOS_VOID                *pMsg )
{
    (VOS_VOID)ulMsgId;

    /* 打印进入该函数， INFO_LEVEL */
    NAS_LMM_EMM_PLMN_LOG_NORM("NAS_EMM_MsNullSsWaitRrcStartCnfMsgTimerExp");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsNullSsWaitRrcStartCnfMsgTimerExp_ENUM,LNAS_ENTRY);

    /* 函数输入指针参数检查 */
    if (VOS_NULL_PTR == pMsg)
    {
        /* 打印异常，ERROR_LEVEL */
        NAS_LMM_EMM_PLMN_LOG_ERR("NAS_EMM_MsNullSsWaitRrcStartCnfMsgTimerExp: MSG PARAM NULL POINTER ERROR!!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsNullSsWaitRrcStartCnfMsgTimerExp_ENUM,LNAS_NULL_PTR);
        return( NAS_LMM_ERR_CODE_PARA_INVALID);
    }

    /* 状态匹配检查,若不匹配,退出 */
    if (NAS_EMM_PLMN_CHK_STAT_INVALID(EMM_MS_NULL, EMM_SS_NULL_WAIT_RRC_START_CNF))
    {
        NAS_LMM_EMM_PLMN_LOG_WARN("NAS_EMM_MsNullSsWaitRrcStartCnfMsgTimerExp: STATE ERROR!!!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsNullSsWaitRrcStartCnfMsgTimerExp_ENUM,LNAS_ERROR);
        return(NAS_LMM_MSG_DISCARD);
    }

    /*如果开机失败，则直接让封装底软的接口reboot modem以便保存现场*/
    NAS_EMM_SendMmcErrInd(NAS_EMM_REBOOT_TYPE_RRC_START_WAIT_RRC_TIMEOUT_FAIL);

    return(NAS_LMM_SUCC);
}



/*****************************************************************************
  3.3  关机相关流程处理 Function
*****************************************************************************/
/*****************************************************************************
 Function Name   : NAS_EMM_MsNullSsAnyReadUsimStateMsgAppStopReq
 Description     : 在MS_NULL + SS_NULL_WAIT_APP_START_REQ状态下，
                   收到APP_MM_STOP_REQ消息，消息响应处理程序
                   说明当前状态是关机状态或者整个关机过程已经执行完成，
                   直接向APP回复APP_MM_STOP_CNF消息
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lining 00141619      2008-10-16  Draft Enact
    1.yangfan 00159566     2010-3-16  Draft Enact
*****************************************************************************/
VOS_UINT32    NAS_EMM_MsNullSsAnyReadUsimStateMsgAppStopReq(
                    VOS_UINT32                              ulMsgId,
                    VOS_VOID                                *pMsg )
{
    VOS_UINT32                          ulSendResult;
    MMC_LMM_STOP_REQ_STRU              *pstAppStopReq;
    NAS_EMM_FSM_STATE_STRU              EmmState;

    (VOS_VOID)ulMsgId;

    /* 打印进入该函数，INFO_LEVEL */
    NAS_LMM_EMM_PLMN_LOG_INFO("NAS_EMM_MsNullSsAnyReadUsimStateMsgAppStopReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsNullSsAnyReadUsimStateMsgAppStopReq_ENUM,LNAS_ENTRY);

    pstAppStopReq                       = pMsg;

    /*停止所有定时器*/
    NAS_LMM_StopAllPtlTimer();
    NAS_LMM_StopAllStateTimer();

    /* 函数输入指针参数检查 */
    if (VOS_NULL_PTR == pMsg)
    {
        /* 打印异常，ERROR_LEVEL */
        NAS_LMM_EMM_PLMN_LOG_ERR("NAS_EMM_MsNullSsAnyReadUsimStateMsgAppStopReq: MSG PARAM NULL POINTER ERROR!!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsNullSsAnyReadUsimStateMsgAppStopReq_ENUM,LNAS_NULL_PTR);
        return NAS_LMM_ERR_CODE_PARA_INVALID;
    }

    /* 将状态转移至MS_NULL + EMM_SS_NULL_WAIT_APP_START_REQ状态 */
    EmmState.enFsmId                    = NAS_LMM_PARALLEL_FSM_EMM;
    EmmState.enMainState                = EMM_MS_NULL;
    EmmState.enSubState                 = EMM_SS_NULL_WAIT_APP_START_REQ;
    EmmState.enStaTId                   = TI_NAS_EMM_STATE_NO_TIMER;
    NAS_LMM_StaTransProc(EmmState);

    /* 向APP发送APP_MM_STOP_CNF消息（回复关机成功，已经关机） */
    ulSendResult = NAS_EMM_PLMN_SendAppStopCnf(MMC_LMM_SUCC,pstAppStopReq->ulOpId);
    if (NAS_EMM_PLMN_OK != ulSendResult)
    {
        /* 打印函数，ERROR_LEVEL */
        NAS_LMM_EMM_PLMN_LOG1_ERR("NAS_EMM_PLMN_SendAppStopCnf : Send Msg Failure!!! ulSendResult=",
                                 ulSendResult);
        TLPS_PRINT2LAYER_ERROR1(NAS_EMM_MsNullSsAnyReadUsimStateMsgAppStopReq_ENUM,LNAS_SND_RST,ulSendResult);
        return NAS_LMM_MSG_HANDLED;
    }

    return NAS_LMM_MSG_HANDLED;
}



VOS_UINT32    NAS_EMM_MsNullSsWaitSwitchOffMsgRrcRelInd(
                    VOS_UINT32                              ulMsgId,
                    VOS_VOID                         *pMsg )
{
    VOS_UINT32                          ulRet;

    (VOS_VOID)ulMsgId;

    /* 打印进入该函数， INFO_LEVEL */
    NAS_LMM_EMM_PLMN_LOG_NORM(           "NAS_EMM_MsNullSsWaitSwitchOffMsgRrcRelInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsNullSsWaitSwitchOffMsgRrcRelInd_ENUM,LNAS_ENTRY);

    /* 函数输入指针参数检查 */
    if (VOS_NULL_PTR                    == pMsg)
    {
        /* 打印异常，ERROR_LEVEL */
        NAS_LMM_EMM_PLMN_LOG_ERR(        "NAS_EMM_MsNullSsWaitSwitchOffMsgRrcRelInd: MSG PARAM NULL POINTER ERROR!!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsNullSsWaitSwitchOffMsgRrcRelInd_ENUM,LNAS_NULL_PTR);
        return(                         NAS_LMM_ERR_CODE_PARA_INVALID);
    }

    /* 状态匹配检查,若不匹配,退出 */
    if (NAS_EMM_PLMN_CHK_STAT_INVALID(  EMM_MS_NULL, EMM_SS_NULL_WAIT_SWITCH_OFF))
    {
        NAS_LMM_EMM_PLMN_LOG_WARN(       "NAS_EMM_MsNullSsWaitSwitchOffMsgRrcRelInd: STATE ERROR!!!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsNullSsWaitSwitchOffMsgRrcRelInd_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    /* 停止TI_NAS_EMM_PTL_SWITCH_OFF_TIMER */
    NAS_LMM_StopPtlTimer(               TI_NAS_EMM_PTL_SWITCH_OFF_TIMER);

    ulRet                               = NAS_EMM_MsNullSsWaitSwitchOffProcMsgRrcRelInd();

    return(                             ulRet);
}


VOS_VOID NAS_EMM_ProcLocalStop( VOS_VOID )
{

    VOS_UINT32                          ulSendResult;
    NAS_EMM_FSM_STATE_STRU              EmmState;
    VOS_UINT8                           ucImsiRefreshFlag;
    NAS_EMM_PLMN_INIT_EMMSTATE(EmmState);

    /*向ESM发送EMM_ESM_STATUS_IND消息*/
    NAS_EMM_PLMN_SendEmmEsmStautsInd(EMM_ESM_ATTACH_STATUS_DETACHED);
    /* 通知ESM关机 */
    NAS_EMM_EsmSendStopNotifyInd();


    /* Added by wangchen 00209181 begin for 搜网优化 2015-05-30 */
    /* 通知CSS模块关机 */
    NAS_LMM_SendCssStopInd();
    /* Added by wangchen 00209181 begin for 搜网优化 2015-05-30 */

    /*通知 RABM:RRC_CONN_REL_IND*/
    NAS_LMM_SendRabmRrcConRelInd(EMM_ERABM_REL_CAUSE_NULL);

    /* 通知ETC:REL_IND */
    NAS_EMM_TcSendRelInd();

    /* 如果是DEREG态，EMM参数无需重复写卡了，在进入DEREG态时已写安全上下文，在
       链路释放时已写PSLOC */
    if (EMM_MS_DEREG != NAS_EMM_CUR_MAIN_STAT)
    {
        /* 如果current安全上下文为mapped 且non-current native上下文存在，
           将后者设置为current，同时删除current mapped，以便关机时写入卡中
           依据:      24301协议     5.5.2.2.1*/
        NAS_EMM_SecuDeregClrSecuCntxt();

        /* 写入EMM NV相关信息 */
        ucImsiRefreshFlag = NAS_MML_GetImsiRefreshStatus();
        NAS_LMM_SndOmImsiRefreshStatus(ucImsiRefreshFlag);
        /* IMSI REFRESH 情况下不写卡 */
        if(VOS_FALSE == ucImsiRefreshFlag)
        {
            NAS_EMM_WriteNvMmInfo();
        }
    }

    /* 向MMC发送MMC_EMM_STOP_REQ消息 */
    ulSendResult = NAS_EMM_PLMN_SendMmcStopReq();
    if (NAS_EMM_PLMN_ERR == ulSendResult)
    {
        /* 打印函数，ERROR_LEVEL */
        NAS_LMM_EMM_PLMN_LOG_ERR("NAS_EMM_ProcLocalStop : Send Msg Failure!!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_ProcLocalStop_ENUM,LNAS_FAIL);
        return;
    }

    /* 启动TI_NAS_EMM_WAIT_MMC_STOP_CNF_TIMER */
    NAS_LMM_StartStateTimer(TI_NAS_EMM_WAIT_MMC_STOP_CNF_TIMER);

    /* 将状态转移至MS_NULL + SS_NULL_WAIT_MMC_STOP_CNF状态 */
    EmmState.enMainState                = EMM_MS_NULL;
    EmmState.enSubState                 = EMM_SS_NULL_WAIT_MMC_STOP_CNF;
    EmmState.enStaTId                   = TI_NAS_EMM_WAIT_MMC_STOP_CNF_TIMER;
    NAS_LMM_StaTransProc(EmmState);
    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsNotNullNotRegMsgAppStopReq
 Description     : 在主状态非空状态下，收到APP_MM_STOP_REQ消息，消息响应处理程序
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lining 00141619      2008-10-16  Draft Enact

*****************************************************************************/
VOS_UINT32    NAS_EMM_MsNotNullNotRegMsgAppStopReq(
                    VOS_UINT32                              ulMsgId,
                    VOS_VOID                                *pMsg )
{
    MMC_LMM_STOP_REQ_STRU              *pstAttStopReq;

    (VOS_VOID)ulMsgId;

    /* 打印进入该函数， INFO_LEVEL */
    NAS_LMM_EMM_PLMN_LOG_INFO("NAS_EMM_MsNotNullNotRegMsgAppStopReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsNotNullNotRegMsgAppStopReq_ENUM,LNAS_ENTRY);

    pstAttStopReq                       = pMsg;

    /*停止所有定时器*/
    NAS_LMM_StopAllPtlTimer();
    NAS_LMM_StopAllStateTimer();

    /* 设置App消息的相关参数 */
    NAS_EMM_SaveAppMsgPara(pstAttStopReq->ulMsgId,pstAttStopReq->ulOpId);

    NAS_EMM_ProcLocalStop();

    return NAS_LMM_MSG_HANDLED;
}


/*****************************************************************************
 Function Name   : NAS_EMM_MsNullSsWaitMmcStopCnfMsgMmcStopCnf
 Description     : 在MS_NULL + SS_NULL_WAIT_MMC_STOP_CNF状态下，收到MMC发来的
                   MMC_EMM_STOP_CNF消息，消息响应处理程序
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lining 00141619      2008-9-16  Draft Enact
    2.X00148705            2010-03-27 修改发送失败的处理

*****************************************************************************/
VOS_UINT32    NAS_EMM_MsNullSsWaitMmcStopCnfMsgMmcStopCnf(
                    VOS_UINT32                              ulMsgId,
                    VOS_VOID                         *pMsg )
{
    VOS_UINT32                          ulSendResult;
    NAS_EMM_FSM_STATE_STRU              EmmState;

    (VOS_VOID)ulMsgId;

    NAS_EMM_PLMN_INIT_EMMSTATE(EmmState);

    /* 打印进入该函数， INFO_LEVEL */
    NAS_LMM_EMM_PLMN_LOG_NORM("NAS_EMM_MsNullSsWaitMmcStopCnfMsgMmcStopCnf is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsNullSsWaitMmcStopCnfMsgMmcStopCnf_ENUM,LNAS_ENTRY);

    /* 函数输入指针参数检查 */
    if (VOS_NULL_PTR == pMsg)
    {
        /* 打印异常，ERROR_LEVEL */
        NAS_LMM_EMM_PLMN_LOG_ERR("NAS_EMM_MsNullSsWaitMmcStopCnfMsgMmcStopCnf: MSG PARAM NULL POINTER ERROR!!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsNullSsWaitMmcStopCnfMsgMmcStopCnf_ENUM,LNAS_NULL_PTR);
        return NAS_LMM_ERR_CODE_PARA_INVALID;
    }

    /* 状态匹配检查,若不匹配,退出 */
    if (NAS_EMM_PLMN_CHK_STAT_INVALID(EMM_MS_NULL, EMM_SS_NULL_WAIT_MMC_STOP_CNF))
    {
        NAS_LMM_EMM_PLMN_LOG_WARN("NAS_EMM_MsNullSsWaitMmcStopCnfMsgMmcStopCnf: STATE ERROR!!!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsNullSsWaitMmcStopCnfMsgMmcStopCnf_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    /* 清除本地资源 */
    /*NAS_EMM_ClearLocalResource();关机不清内存不读卡，等再次收到 START消息后再清内存，并读卡 */

    /* 停止TI_NAS_EMM_WAIT_MMC_STOP_CNF_TIMER */
    NAS_LMM_StopStateTimer(TI_NAS_EMM_WAIT_MMC_STOP_CNF_TIMER);

    /* 向RRC发送RRC_MM_STOP_REQ消息 */
    ulSendResult = NAS_EMM_PLMN_SendRrcStopReq();
    if (NAS_EMM_PLMN_OK != ulSendResult)
    {
        /* 打印函数，ERROR_LEVEL */
        NAS_LMM_EMM_PLMN_LOG1_ERR("NAS_EMM_PLMN_SendRrcStopReq : Send Msg Failure!!! ulSendResult=",
                                 ulSendResult);
        TLPS_PRINT2LAYER_ERROR1(NAS_EMM_MsNullSsWaitMmcStopCnfMsgMmcStopCnf_ENUM,LNAS_SND_RST,ulSendResult);
    }

    /* 启动TI_NAS_EMM_WAIT_RRC_STOP_CNF_TIMER */
    NAS_LMM_StartStateTimer(TI_NAS_EMM_WAIT_RRC_STOP_CNF_TIMER);

    /* 将状态转移至MS_NULL + SS_NULL_WAIT_RRC_STOP_CNF状态 */
    EmmState.enMainState                = EMM_MS_NULL;
    EmmState.enSubState                 = EMM_SS_NULL_WAIT_RRC_STOP_CNF;
    EmmState.enStaTId                   = TI_NAS_EMM_WAIT_RRC_STOP_CNF_TIMER;
    NAS_LMM_StaTransProc(EmmState);

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsNullSsWaitMmcStopCnfMsgTimerExp
 Description     : 在MS_NULL + SS_NULL_WAIT_MMC_START_CNF状态下，
                   TI_NAS_EMM_WAIT_MMC_STOP_CNF_TIMER超时处理程序
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lining 00141619      2008-10-16  Draft Enact

*****************************************************************************/
VOS_UINT32    NAS_EMM_MsNullSsWaitMmcStopCnfMsgTimerExp(
                    VOS_UINT32                              ulMsgId,
                    VOS_VOID                         *pMsg )
{
    VOS_UINT32                          ulSendResult;
    NAS_EMM_FSM_STATE_STRU              EmmState;

    (VOS_VOID)ulMsgId;

    NAS_EMM_PLMN_INIT_EMMSTATE(EmmState);

    /* 打印进入该函数， INFO_LEVEL */
    NAS_LMM_EMM_PLMN_LOG_NORM("NAS_EMM_MsNullSsWaitMmcStopCnfMsgTimerExp is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsNullSsWaitMmcStopCnfMsgTimerExp_ENUM,LNAS_ENTRY);

    /* 函数输入指针参数检查 */
    if (VOS_NULL_PTR == pMsg)
    {
        /* 打印异常，ERROR_LEVEL */
        NAS_LMM_EMM_PLMN_LOG_ERR("NAS_EMM_MsNullSsWaitMmcStopCnfMsgTimerExp: MSG PARAM NULL POINTER ERROR!!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsNullSsWaitMmcStopCnfMsgTimerExp_ENUM,LNAS_NULL_PTR);
        return NAS_LMM_ERR_CODE_PARA_INVALID;
    }

    /* 状态匹配检查,若不匹配,退出 */
    if (NAS_EMM_PLMN_CHK_STAT_INVALID(EMM_MS_NULL, EMM_SS_NULL_WAIT_MMC_STOP_CNF))
    {
        NAS_LMM_EMM_PLMN_LOG_WARN("NAS_EMM_MsNullSsWaitMmcStopCnfMsgTimerExp: STATE ERROR!!!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsNullSsWaitMmcStopCnfMsgTimerExp_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    /* 向RRC发送RRC_MM_STOP_REQ消息 */
    ulSendResult = NAS_EMM_PLMN_SendRrcStopReq();
    if (NAS_EMM_PLMN_OK != ulSendResult)
    {
        /* 打印函数，ERROR_LEVEL */
        NAS_LMM_EMM_PLMN_LOG1_ERR("NAS_EMM_MsNullSsWaitMmcStopCnfMsgTimerExp : Send Msg Failure!!! ulSendResult=",
                                 ulSendResult);
        TLPS_PRINT2LAYER_ERROR1(NAS_EMM_MsNullSsWaitMmcStopCnfMsgTimerExp_ENUM,LNAS_SND_RST,ulSendResult);
        return NAS_LMM_MSG_HANDLED;
    }

    /* 启动TI_NAS_EMM_WAIT_RRC_STOP_CNF_TIMER */
    NAS_LMM_StartStateTimer(TI_NAS_EMM_WAIT_RRC_STOP_CNF_TIMER);

    /* 将状态转移至MS_NULL + SS_NULL_WAIT_RRC_STOP_CNF状态 */
    EmmState.enMainState                = EMM_MS_NULL;
    EmmState.enSubState                 = EMM_SS_NULL_WAIT_RRC_STOP_CNF;
    EmmState.enStaTId                   = TI_NAS_EMM_WAIT_RRC_STOP_CNF_TIMER;
    NAS_LMM_StaTransProc(EmmState);

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsNullSsWaitRrcStopCnfMsgRrcStopCnf
 Description     : 在MS_NULL + SS_NULL_WAIT_RRC_STOP_CNF状态下，收到RRC发来的
                   RRC_MM_STOP_CNF消息，消息响应处理程序
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lining 00141619      2008-9-16  Draft Enact
    2.leili 00132387       2009-05-13 modify
    3.X00148705            2009-05-18 Modify

*****************************************************************************/
VOS_UINT32    NAS_EMM_MsNullSsWaitRrcStopCnfMsgRrcStopCnf(
                    VOS_UINT32                              ulMsgId,
                    VOS_VOID                                *pMsg )
{
    VOS_UINT32                          ulSendResult;

    (VOS_VOID)(ulMsgId);
    (VOS_VOID)(pMsg);

    /* 打印进入该函数， INFO_LEVEL */
    NAS_LMM_EMM_PLMN_LOG_NORM("NAS_EMM_MsNullSsWaitRrcStopCnfMsgRrcStopCnf is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsNullSsWaitRrcStopCnfMsgRrcStopCnf_ENUM,LNAS_ENTRY);

    /* 函数输入指针参数检查 */
    if (VOS_NULL_PTR == pMsg)
    {
        /* 打印异常，ERROR_LEVEL */
        NAS_LMM_EMM_PLMN_LOG_ERR("NAS_EMM_MsNullSsWaitRrcStopCnfMsgRrcStopCnf: MSG PARAM NULL POINTER ERROR!!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsNullSsWaitRrcStopCnfMsgRrcStopCnf_ENUM,LNAS_NULL_PTR);
        return NAS_LMM_ERR_CODE_PARA_INVALID;
    }

    /* 状态匹配检查,若不匹配,退出 */
    if (NAS_EMM_PLMN_CHK_STAT_INVALID(EMM_MS_NULL, EMM_SS_NULL_WAIT_RRC_STOP_CNF))
    {
        NAS_LMM_EMM_PLMN_LOG_WARN("NAS_EMM_MsNullSsWaitRrcStopCnfMsgRrcStopCnf: STATE ERROR!!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsNullSsWaitRrcStopCnfMsgRrcStopCnf_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    /* 停止TI_NAS_EMM_WAIT_RRC_STOP_CNF_TIMER */
    NAS_LMM_StopStateTimer(TI_NAS_EMM_WAIT_RRC_STOP_CNF_TIMER);

    /* 状态迁移到 Null.WtAppStartReq*/
    NAS_EMM_ProcRrcStopRslt();

    /* 向APP发送APP_MM_STOP_CNF消息（回复关机成功，正常关机） */
    if (NAS_EMM_PLMN_OK == NAS_EMM_CheckAppMsgPara(ID_MMC_LMM_STOP_REQ))
    {

        ulSendResult = NAS_EMM_PLMN_SendAppStopCnf(APP_SUCCESS,NAS_EMM_GetAppMsgOpId());

        if (NAS_EMM_PLMN_OK != ulSendResult)
        {
            /* 打印函数，ERROR_LEVEL */
            NAS_LMM_EMM_PLMN_LOG1_ERR("NAS_EMM_PLMN_SendAppStopCnf : Send Msg Failure!!! ulSendResult=",
                                     ulSendResult);
            TLPS_PRINT2LAYER_ERROR1(NAS_EMM_MsNullSsWaitRrcStopCnfMsgRrcStopCnf_ENUM,LNAS_SND_RST,ulSendResult);
        }
    }
    /* 清除关机标识,该标志提供给LRRC,用于LRRC判断空口是否是关机detach 该标志
       在LMM收到MMC的stop req时置为1 */
    NAS_LMM_SetEmmInfoLtePowerOffFlag(NAS_EMM_NO);
    /*清除APP参数*/
    NAS_EMM_ClearAppMsgPara();

    TLPS_SendPrintBufferInfo();

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsNullSsWaitRrcStopCnfMsgTimerExp
 Description     : 在MS_NULL + SS_NULL_WAIT_RRC_START_CNF状态下，
                   TI_NAS_EMM_WAIT_RRC_STOP_CNF_TIMER超时处理程序
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lining 00141619      2008-10-16  Draft Enact
    2.X00148705            2010-03-27  修改发送结果的处理

*****************************************************************************/
VOS_UINT32    NAS_EMM_MsNullSsWaitRrcStopCnfMsgTimerExp(
                    VOS_UINT32                              ulMsgId,
                    VOS_VOID                                *pMsg )
{
    VOS_UINT32                          ulResult;

    (VOS_VOID)ulMsgId;

    /* 打印进入该函数， INFO_LEVEL */
    NAS_LMM_EMM_PLMN_LOG_NORM("NAS_EMM_MsNullSsWaitRrcStopCnfMsgTimerExp is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsNullSsWaitRrcStopCnfMsgTimerExp_ENUM,LNAS_ENTRY);

    /* 函数输入指针参数检查 */
    if (VOS_NULL_PTR == pMsg)
    {
        /* 打印异常，ERROR_LEVEL */
        NAS_LMM_EMM_PLMN_LOG_ERR("NAS_EMM_MsNullSsWaitRrcStopCnfMsgTimerExp: MSG PARAM NULL POINTER ERROR!!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsNullSsWaitRrcStopCnfMsgTimerExp_ENUM,LNAS_NULL_PTR);
        return NAS_LMM_ERR_CODE_PARA_INVALID;
    }

    /* 状态匹配检查,若不匹配,退出 */
    if (NAS_EMM_PLMN_CHK_STAT_INVALID(EMM_MS_NULL, EMM_SS_NULL_WAIT_RRC_STOP_CNF))
    {
        NAS_LMM_EMM_PLMN_LOG_WARN("NAS_EMM_MsNullSsWaitRrcStopCnfMsgTimerExp: STATE ERROR!!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsNullSsWaitRrcStopCnfMsgTimerExp_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    /* 状态迁移到 Null.WtAppStartReq*/
    NAS_EMM_ProcRrcStopRslt();

    if (NAS_EMM_PLMN_OK == NAS_EMM_CheckAppMsgPara(ID_MMC_LMM_STOP_REQ))
    {
        /* 向APP发送APP_MM_STOP_CNF消息（回复关机失败，等待RRC停止超时） */
        ulResult = NAS_EMM_PLMN_SendAppStopCnf(MMC_LMM_FAIL,NAS_EMM_GetAppMsgOpId());

        if (NAS_EMM_PLMN_OK != ulResult)
        {
            /* 打印函数，ERROR_LEVEL */
            NAS_LMM_EMM_PLMN_LOG1_ERR("NAS_EMM_PLMN_SendAppStopCnf : Send Msg Failure!!! ulSendResult=",
                                     ulResult);
            TLPS_PRINT2LAYER_ERROR1(NAS_EMM_MsNullSsWaitRrcStopCnfMsgTimerExp_ENUM,LNAS_SND_RST,ulResult);
        }
    }
    /* 清除关机标识,该标志提供给LRRC,用于LRRC判断空口是否是关机detach 该标志
       在LMM收到MMC的stop req时置为1 */
    NAS_LMM_SetEmmInfoLtePowerOffFlag(NAS_EMM_NO);
    /*清除APP参数*/
    NAS_EMM_ClearAppMsgPara();

    TLPS_SendPrintBufferInfo();

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
  3.4  其它相关流程处理 Function
*****************************************************************************/
/*****************************************************************************
 Function Name   : NAS_EMM_MsNotNullSsAnyStateMsgMmcPlmnInd
 Description     : 在主状态非空状态下，收到MMC_EMM_PLMN_IND消息，消息响应处理程序
                   (在主状态非空状态下，都有可能收到MMC_EMM_PLMN_IND消息)
                   (MMC_EMM_PLMN_IND消息是在MMC收到APP的用户重选消息后，
                    设置MMC状态，并通知EMM发生用户重选，而不是MMC通知EMM的搜网结果，
                    搜网结果通过MMC_EMM_SYS_INFO_IND消息发给EMM。)
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lining 00141619      2008-9-16  Draft Enact
    2.zhengjunyan 00148421 2011-12-27 EMMC收到搜网请求时，已经对连接状态进行了判断，
                                      这里不需要再进行判断
*****************************************************************************/
VOS_UINT32    NAS_EMM_MsNotNullSsAnyStateMsgMmcPlmnInd(
                    VOS_UINT32                              ulMsgId,
                    VOS_VOID                         *pMsg)
{
    /*VOS_UINT32                          ulSendResult;*/
    NAS_EMM_FSM_STATE_STRU              EmmState;
    VOS_UINT32                          ulRslt;

    (VOS_VOID)ulMsgId;

    NAS_EMM_PLMN_INIT_EMMSTATE(EmmState);

    /* 打印进入该函数，INFO_LEVEL */
    NAS_LMM_EMM_PLMN_LOG_NORM("NAS_EMM_MsNotNullSsAnyStateMsgMmcPlmnInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsNotNullSsAnyStateMsgMmcPlmnInd_ENUM,LNAS_ENTRY);

    /* 函数输入指针参数检查 */
    if (VOS_NULL_PTR == pMsg)
    {
        /* 打印异常，ERROR_LEVEL */
        NAS_LMM_EMM_PLMN_LOG_ERR("NAS_EMM_MsNotNullSsAnyStateMsgMmcPlmnInd: MSG PARAM NULL POINTER ERROR!!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsNotNullSsAnyStateMsgMmcPlmnInd_ENUM,LNAS_NULL_PTR);
        return NAS_LMM_ERR_CODE_PARA_INVALID;
    }

    /* 状态匹配检查,若不匹配,退出 */
    if (EMM_MS_NULL == EmmState.enMainState)
    {
        NAS_LMM_EMM_PLMN_LOG_WARN("NAS_EMM_MsNotNullSsAnyStateMsgMmcPlmnInd: STATE ERROR!!!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsNotNullSsAnyStateMsgMmcPlmnInd_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    /*清除BAR标识*/
    NAS_EMM_ClearBarResouce();

    /* 判断若为挂起态，则通知ESM和ERABM激活，并获取GU的安全参数 */
    ulRslt = NAS_EMM_NoCellSuspendMsgMmcPlmnReq();
    if (NAS_LMM_MSG_HANDLED == ulRslt)
    {
        NAS_LMM_EMM_PLMN_LOG_NORM("NAS_EMM_MsNotNullSsAnyStateMsgMmcPlmnInd: MMC ACTIVE LNAS");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsNotNullSsAnyStateMsgMmcPlmnInd_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_LMM_MSG_HANDLED;
    }

    /*如果后续支持连接态下搜网，此处需增加判断USIM卡是否有效:如果卡无效且不存在连接，
      状态转换到DEREG+NO_IMSI，清除相应的资源通知MMC卡无效；如果卡无效且存在连接，
      状态转换到DEREG+WAIT_MRRC_REL+_CNF，发送RRC_MM_REL_REQ消息，等收到RRC_MM_REL_CNF
      消息后，状态转换到DEREG+NO_IMSI,清除相应的资源通知MMC卡无效*/

    /* 判断EMM当前状态*/
    /* 针对GCF9.2.3.1.5 用例临时方案 ,UE丢网,MMC发起搜网 ,搜网期间T3412超时,发起的TAU类型是combined TAU with IMSI类型，
       而仪器测试中,存在现网干扰下,UE在现网上受限驻留,导致无法转到no cell态。所以针对GCF测试此处EMM不转状态 */
    if((PS_SUCC == LPS_OM_IsTestMode())
        &&(EMM_MS_REG == EmmState.enMainState)
        && (EMM_SS_REG_LIMITED_SERVICE == EmmState.enSubState))
    {
        return NAS_LMM_MSG_HANDLED;
    }

    /* 针对GCF9.2.3.1.5 用例，UE丢网，MMC发起搜网，搜网期间T3412超时，发起的TAU类型是combined TAU with IMSI类型的*/
    if ((EMM_MS_REG == EmmState.enMainState)
        && (EMM_SS_REG_NO_CELL_AVAILABLE == EmmState.enSubState))
    {
        return NAS_LMM_MSG_HANDLED;

    }
    else if(EMM_MS_REG == EmmState.enMainState)
    {
        /* 将状态转移至MS_REG + SS_REG_PLMN_SEARCH状态 */
        EmmState.enMainState        = EMM_MS_REG;
        EmmState.enSubState         = EMM_SS_REG_PLMN_SEARCH;
        EmmState.enStaTId           = TI_NAS_EMM_STATE_NO_TIMER;

    }
    else
    {
        if (EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER == NAS_EMM_GLO_AD_GetAttCau())
        {
            /* 通知ESM紧接着EMM还要做紧急注册，ESM不需要清除动态表中的紧急PDN建立记录 */
            NAS_EMM_PLMN_SendEmmEsmStautsInd(EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);
        }
        else
        {
            /*向ESM发送ATTACH结果*/
            NAS_EMM_PLMN_SendEmmEsmStautsInd(EMM_ESM_ATTACH_STATUS_DETACHED);
        }
        /* 将状态转移至MS_DEREG + SS_DEREG_PLMN_SEARCH状态 */
        EmmState.enMainState        = EMM_MS_DEREG;
        EmmState.enSubState         = EMM_SS_DEREG_PLMN_SEARCH;
        EmmState.enStaTId           = TI_NAS_EMM_STATE_NO_TIMER;
    }

    NAS_LMM_StaTransProc(EmmState);

    return NAS_LMM_MSG_HANDLED;
}
/*****************************************************************************
 Function Name   : NAS_EMM_MsRegSsRegAttemptUpdateMmMsgMmcPlmnInd
 Description     : 处理在REG+ATTEMPT_TO_UPDATE_MM状态下收到PLMN IND消息
 Input           : ulMsgId-------------------------消息ID
                   pMsgStru------------------------消息指针
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong 00150010      2011-11-17  Draft Enact

*****************************************************************************/
VOS_UINT32    NAS_EMM_MsRegSsRegAttemptUpdateMmMsgMmcPlmnInd
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                     *pMsg
)
{
    /*VOS_UINT32                          ulSendResult;*/
    NAS_EMM_FSM_STATE_STRU              EmmState;

    (VOS_VOID)ulMsgId;

    NAS_EMM_PLMN_INIT_EMMSTATE(EmmState);

    /* 打印进入该函数，INFO_LEVEL */
    NAS_LMM_EMM_PLMN_LOG_NORM("NAS_EMM_MsRegSsRegAttemptUpdateMmMsgMmcPlmnInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgMmcPlmnInd_ENUM,LNAS_ENTRY);

    /* 函数输入指针参数检查 */
    if (VOS_NULL_PTR == pMsg)
    {
        /* 打印异常，ERROR_LEVEL */
        NAS_LMM_EMM_PLMN_LOG_ERR("NAS_EMM_MsRegSsRegAttemptUpdateMmMsgMmcPlmnInd: MSG PARAM NULL POINTER ERROR!!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgMmcPlmnInd_ENUM,LNAS_NULL_PTR);
        return NAS_LMM_ERR_CODE_PARA_INVALID;
    }

    /* 状态匹配检查,若不匹配,退出 */
    if (NAS_EMM_PLMN_CHK_STAT_INVALID(EMM_MS_REG, EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM))
    {
        NAS_LMM_EMM_PLMN_LOG_WARN("NAS_EMM_MsRegSsRegAttemptUpdateMmMsgMmcPlmnInd: STATE ERROR!!!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgMmcPlmnInd_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    /*清除BAR标识*/
    NAS_EMM_ClearBarResouce();

    /* 记录UPDATE_MM标识 */
    /*NAS_LMM_SetEmmInfoUpdateMmFlag(NAS_EMM_UPDATE_MM_FLAG_VALID);*/

    /* 将状态转移至MS_REG + SS_REG_PLMN_SEARCH状态 */
    EmmState.enMainState        = EMM_MS_REG;
    EmmState.enSubState         = EMM_SS_REG_PLMN_SEARCH;
    EmmState.enStaTId           = TI_NAS_EMM_STATE_NO_TIMER;
    NAS_LMM_StaTransProc(EmmState);

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsRegSsRegAttemptUpdateMmMsgIntraMrrcRelInd
 Description     : 处理在REG+ATTEMPT_TO_UPDATE_MM状态下收到内部链路释放消息
 Input           : ulMsgId-------------------------消息ID
                   pMsgStru------------------------消息指针
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2011-11-17  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegSsRegAttemptUpdateMmMsgIntraMrrcRelInd
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                            *pMsg
)
{
    /* 打印进入该函数， INFO_LEVEL */
    NAS_LMM_EMM_PLMN_LOG_INFO("NAS_EMM_MsRegSsRegAttemptUpdateMmMsgIntraMrrcRelInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgIntraMrrcRelInd_ENUM,LNAS_ENTRY);
    (VOS_VOID)ulMsgId;

    /* 函数输入指针参数检查 */
    if (VOS_NULL_PTR == pMsg)
    {
        /* 打印异常，ERROR_LEVEL */
        NAS_LMM_EMM_PLMN_LOG_ERR("NAS_EMM_MsRegSsRegAttemptUpdateMmMsgIntraMrrcRelInd: MSG PARAM NULL POINTER ERROR!!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgIntraMrrcRelInd_ENUM,LNAS_NULL_PTR);
        return NAS_LMM_ERR_CODE_PARA_INVALID;
    }

    /*发送内部消息 INTRA_CONN2IDLE_REQ,更新连接状态为IDLE*/
    NAS_EMM_CommProcConn2Ilde();

    return NAS_LMM_MSG_HANDLED;
}
/*****************************************************************************
 Function Name   : NAS_EMM_MsRegSsNormalServiceMsgMrrcRelInd
 Description     : 在reg.normal态下内部释放处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunbing49683      2010-12-29  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegSsNormalServiceMsgMrrcRelInd(
                    VOS_UINT32                              ulMsgId,
                    VOS_VOID                                *pMsg )
{
    /* 打印进入该函数， INFO_LEVEL */
    NAS_LMM_EMM_PLMN_LOG_INFO("NAS_EMM_MsRegSsNormalServiceMsgMrrcRelInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsNormalServiceMsgMrrcRelInd_ENUM,LNAS_ENTRY);
    (VOS_VOID)ulMsgId;

    /* 函数输入指针参数检查 */
    if (VOS_NULL_PTR == pMsg)
    {
        /* 打印异常，ERROR_LEVEL */
        NAS_LMM_EMM_PLMN_LOG_ERR("NAS_EMM_MsRegSsNormalServiceMsgMrrcRelInd: MSG PARAM NULL POINTER ERROR!!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegSsNormalServiceMsgMrrcRelInd_ENUM,LNAS_NULL_PTR);
        return NAS_LMM_ERR_CODE_PARA_INVALID;
    }

    /*发送内部消息 INTRA_CONN2IDLE_REQ,更新连接状态为IDLE*/
    NAS_EMM_CommProcConn2Ilde();

    return NAS_LMM_MSG_HANDLED;
}


/*****************************************************************************
 Function Name   : NAS_EMM_MsNotNullSsAnyStateMsgMmcCoverageLostInd
 Description     : 在主状态非空状态下，收到MMC_EMM_COVERAGE_LOST_IND消息，消息响应处理程序
                   (在主状态非空状态下，都有可能收到MMC_EMM_COVERAGE_LOST_IND消息)
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lining 00141619      2008-9-17  Draft Enact
    2.hanlufeng     41410  2009-05-21
*****************************************************************************/
VOS_UINT32    NAS_EMM_MsNotNullSsAnyStateMsgMmcCoverageLostInd(
                    VOS_UINT32                              ulMsgId,
                    VOS_VOID                                *pMsg )
{
    NAS_EMM_FSM_STATE_STRU                      EmmState;
    NAS_EMM_PLMN_INIT_EMMSTATE(EmmState);

    (VOS_VOID)(ulMsgId);
    (VOS_VOID)(pMsg);

    /* 打印进入该函数， INFO_LEVEL */
    NAS_LMM_EMM_PLMN_LOG_NORM("NAS_EMM_MsNotNullSsAnyStateMsgMmcCoverageLostInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsNotNullSsAnyStateMsgMmcCoverageLostInd_ENUM,LNAS_ENTRY);

    /* 函数输入指针参数检查 */
    if (VOS_NULL_PTR == pMsg)
    {
        /* 打印异常，ERROR_LEVEL */
        NAS_LMM_EMM_PLMN_LOG_ERR("NAS_EMM_MsNotNullSsAnyStateMsgMmcCoverageLostInd: MSG PARAM NULL POINTER ERROR!!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsNotNullSsAnyStateMsgMmcCoverageLostInd_ENUM,LNAS_NULL_PTR);
        return NAS_LMM_ERR_CODE_PARA_INVALID;
    }

    /* 状态匹配检查,若不匹配,退出 */
    if (EMM_MS_NULL == EmmState.enMainState)
    {
        NAS_LMM_EMM_PLMN_LOG_WARN("NAS_EMM_MsNotNullSsAnyStateMsgMmcCoverageLostInd: STATE ERROR!!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsNotNullSsAnyStateMsgMmcCoverageLostInd_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    /*清除BAR标识*/
    NAS_EMM_ClearBarResouce();

    /* 关闭当前EMM的除Del Forb Ta Proid之外的状态定时器, Del Forb Ta Proid只能在关机时停止*/
    NAS_LMM_StopAllStateTimerExceptDelForbTaProidTimer();

    /* 如果当前CSFB延时定时器在运行，说明在REG-NORMAL态下释放过程中收到CSFB，
       但是在释放后搜小区出现丢网，此时应触发去GU搜网继续CSFB */
    if(NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_CSFB_DELAY))
    {
        /* 停止CSFB时延定时器 */
        NAS_LMM_StopPtlTimer(TI_NAS_EMM_PTL_CSFB_DELAY);

        /* 给MMC上报SERVICE失败触发搜网去GU */
        NAS_EMM_MmcSendSerResultIndOtherType(MMC_LMM_SERVICE_RSLT_FAILURE);
    }

    if ((EMM_MS_REG         == EmmState.enMainState) ||
        (EMM_MS_TAU_INIT    == EmmState.enMainState) ||
        (EMM_MS_SER_INIT    == EmmState.enMainState)) /* 已经注册 */
    {
        /* 将状态转移至MS_REG + SS_NO_CELL_AVAILABLE状态 */
        EmmState.enMainState            = EMM_MS_REG;
        EmmState.enSubState             = EMM_SS_REG_NO_CELL_AVAILABLE;
        EmmState.enStaTId               = TI_NAS_EMM_STATE_NO_TIMER;
    }
    else
    {
        /*向ESM发送ID_EMM_ESM_STATUS_IND消息*/
        NAS_EMM_PLMN_SendEmmEsmStautsInd(      EMM_ESM_ATTACH_STATUS_DETACHED);

        /* 将状态转移至MS_DEREG + SS_NO_CELL_AVAILABLE状态 */
        EmmState.enMainState            = EMM_MS_DEREG;
        EmmState.enSubState             = EMM_SS_DEREG_NO_CELL_AVAILABLE;
        EmmState.enStaTId               = TI_NAS_EMM_STATE_NO_TIMER;
    }
    NAS_LMM_StaTransProc(EmmState);

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsRegSsRegAttemptUpdateMmMsgMmcCoverageLostInd
 Description     : 在REG+ATTEMPT_TO_UPDATE_MM状态下收到丟网消息
 Input           : ulMsgId----------------------消息ID
                   pMsg-------------------------丟网消息指针
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2011-11-16  Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_EMM_MsRegSsRegAttemptUpdateMmMsgMmcCoverageLostInd
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsg
)
{
    NAS_EMM_FSM_STATE_STRU                      EmmState;

    NAS_EMM_PLMN_INIT_EMMSTATE(EmmState);

    (VOS_VOID)(ulMsgId);
    (VOS_VOID)(pMsg);

    /* 打印进入该函数， INFO_LEVEL */
    NAS_LMM_EMM_PLMN_LOG_NORM("NAS_EMM_MsRegSsRegAttemptUpdateMmMsgMmcCoverageLostInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgMmcCoverageLostInd_ENUM,LNAS_ENTRY);

    /* 函数输入指针参数检查 */
    if (VOS_NULL_PTR == pMsg)
    {
        /* 打印异常，ERROR_LEVEL */
        NAS_LMM_EMM_PLMN_LOG_ERR("NAS_EMM_MsRegSsRegAttemptUpdateMmMsgMmcCoverageLostInd: MSG PARAM NULL POINTER ERROR!!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgMmcCoverageLostInd_ENUM,LNAS_NULL_PTR);
        return NAS_LMM_ERR_CODE_PARA_INVALID;
    }

    /* 状态匹配检查,若不匹配,退出 */
    if (NAS_EMM_PLMN_CHK_STAT_INVALID(EMM_MS_REG, EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM))
    {
        NAS_LMM_EMM_PLMN_LOG_WARN("NAS_EMM_MsRegSsRegAttemptUpdateMmMsgMmcCoverageLostInd: STATE ERROR!!!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgMmcCoverageLostInd_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    /*清除BAR标识*/
    NAS_EMM_ClearBarResouce();

    /* 关闭当前EMM的除Del Forb Ta Proid之外的状态定时器, Del Forb Ta Proid只能在关机时停止*/
    NAS_LMM_StopAllStateTimerExceptDelForbTaProidTimer();

    /* 记录UPDATE_MM标识 */
    /*NAS_LMM_SetEmmInfoUpdateMmFlag(NAS_EMM_UPDATE_MM_FLAG_VALID);*/

    /* 将状态转移至MS_REG + SS_NO_CELL_AVAILABLE状态 */
    EmmState.enMainState            = EMM_MS_REG;
    EmmState.enSubState             = EMM_SS_REG_NO_CELL_AVAILABLE;
    EmmState.enStaTId               = TI_NAS_EMM_STATE_NO_TIMER;
    NAS_LMM_StaTransProc(EmmState);

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsDeregSsAttemptToAttachMsgMmcSysInfoInd
 Description     : 在Dereg.AttemptToAttach状态下，收到MMC发来的MMC_EMM_SYS_INFO_IND消息，
                   响应处理程序
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.zhengjunyan   00148421    2009.03.10  New Draft
    2.hanlufeng     41410       2009-04-30  ATTEMPTING TO ATTACH状态下，发起
                                ATTACH，直接使用ATTACH模块缓存的PDN消息，不再
                                向SM模块请求
    3.leili         00132387    问题单BJ9D01091
    4.liuhua        00212067    2012-05-29 当收到小区被禁消息后，不需要停止T3411, T3402
    5.lihong00150010            2012-11-01  Modify:emgergency
*****************************************************************************/
VOS_UINT32    NAS_EMM_MsDeregSsAttemptToAttachMsgMmcSysInfoInd(
                    VOS_UINT32                              ulMsgId,
                    VOS_VOID                                *pMsg )
{
    NAS_LMM_FSM_STATE_STRU               stEmmState;
    EMMC_EMM_SYS_INFO_IND_STRU         *pstMmcSysInfoInd;
    VOS_UINT32                          ulSendResult;
    NAS_MM_TA_STRU                     *pstLastAttmpRegTa = NAS_EMM_NULL_PTR;
    NAS_MM_TA_STRU                      stCurTa;
    NAS_EMM_ESM_MSG_BUFF_STRU          *pstEsmMsg = NAS_EMM_NULL_PTR;

    NAS_LMM_MEM_SET_S(&stCurTa, sizeof(NAS_MM_TA_STRU), 0, sizeof(NAS_MM_TA_STRU));

    (VOS_VOID)ulMsgId;

    NAS_LMM_EMM_PLMN_LOG_NORM("NAS_EMM_MsDeregSsAttemptToAttachMsgMmcSysInfoInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDeregSsAttemptToAttachMsgMmcSysInfoInd_ENUM,LNAS_ENTRY);

    /*check the input params*/
    if (VOS_NULL_PTR == pMsg)
    {
        NAS_LMM_EMM_PLMN_LOG_ERR("NAS_EMM_MsDeregSsAttemptToAttachMsgMmcSysInfoInd: MSG PARAM NULL POINTER ERROR!!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsDeregSsAttemptToAttachMsgMmcSysInfoInd_ENUM,LNAS_NULL_PTR);
        return NAS_LMM_ERR_CODE_PARA_INVALID;
    }

    /*get the sys info*/
    pstMmcSysInfoInd = (EMMC_EMM_SYS_INFO_IND_STRU *) pMsg;

    /* 如果ATTACH的触发类型是紧急PDN建立引起的普通注册，且缓存的紧急PDN建立请求
       消息有效，则发起紧急注册 */
    pstEsmMsg = (NAS_EMM_ESM_MSG_BUFF_STRU*)(VOS_VOID*)NAS_LMM_GetEmmInfoEsmBuffAddr();
    if ((EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER == NAS_EMM_GLO_AD_GetAttCau())
        && (NAS_EMM_NULL_PTR != pstEsmMsg))
    {
        NAS_LMM_EMM_PLMN_LOG_WARN("NAS_EMM_MsDeregSsAttemptToAttachMsgMmcSysInfoInd: case ESM_ATTACH_FOR_INIT_EMC_BERER");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDeregSsAttemptToAttachMsgMmcSysInfoInd_ENUM,LNAS_EMM_ATTACH_EMC_BEAER);

        /*保存ESM消息*/
        NAS_LMM_MEM_CPY_S(  (VOS_VOID*)NAS_EMM_GLO_AD_GetEsmMsgAddr(),
                            sizeof(NAS_EMM_CN_MSGCON_STRU),
                            &(pstEsmMsg->stEsmMsg),
                            (pstEsmMsg->stEsmMsg.ulEsmMsgSize)+4);

        NAS_EMM_StartEmergencyAttach();

        return NAS_LMM_MSG_HANDLED;
    }

    /*判断当前小区是否被禁止*/
    if ((EMMC_EMM_NO_FORBIDDEN != pstMmcSysInfoInd->ulForbiddenInfo)
         || (EMMC_EMM_CELL_STATUS_ANYCELL == pstMmcSysInfoInd->ulCellStatus))
    {
        /*向ESM发送EMM_ESM_STATUS_IND消息*/
        NAS_EMM_PLMN_SendEmmEsmStautsInd(EMM_ESM_ATTACH_STATUS_DETACHED);


        stEmmState.enFsmId                = NAS_LMM_PARALLEL_FSM_EMM;
        stEmmState.enMainState            = EMM_MS_DEREG;
        stEmmState.enSubState             = EMM_SS_DEREG_LIMITED_SERVICE;
        stEmmState.enStaTId               = TI_NAS_EMM_STATE_NO_TIMER;
        NAS_LMM_StaTransProc(stEmmState);

        NAS_EMM_SetAttType();

        /*向MMC发送LMM_MMC_ATTACH_CNF或LMM_MMC_ATTACH_IND消息*/
        NAS_EMM_AppSendAttRsltForb(pstMmcSysInfoInd->ulForbiddenInfo);
        return NAS_LMM_MSG_HANDLED;
    }


    /* 获取当前TA和上次尝试注册的TA信息 */
    NAS_EMM_GetCurrentTa(&stCurTa);
    pstLastAttmpRegTa                  = NAS_LMM_GetEmmInfoNetInfoLastAttmpRegTaAddr();

    /* 判断是否需要等定时器超时再发起注册 */
    if (NAS_LMM_MATCH_SUCCESS == NAS_LMM_TaMatch(pstLastAttmpRegTa, &stCurTa))
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsDeregSsAttemptToAttachMsgMmcSysInfoInd: The same as last attempt TA.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDeregSsAttemptToAttachMsgMmcSysInfoInd_ENUM,LNAS_EMM_TA_NO_CHANGE);
        if (   (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_T3411))
            || (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_T3402)) )
        {
            return NAS_LMM_MSG_HANDLED;
        }
    }
    else
    {
        /*重设attach attempt counter*/
        NAS_EMM_AttResetAttAttempCounter();
    }

    stEmmState.enFsmId                = NAS_LMM_PARALLEL_FSM_EMM;
    stEmmState.enMainState            = EMM_MS_DEREG;
    stEmmState.enSubState             = EMM_SS_DEREG_NORMAL_SERVICE;
    stEmmState.enStaTId               = TI_NAS_EMM_STATE_NO_TIMER;
    NAS_LMM_StaTransProc(stEmmState);

    /*send Msg EMM_INTRA_ATTACH_REQ to ATTACH module*/
    ulSendResult = NAS_EMM_SendIntraAttachReq();

    if (NAS_EMM_PLMN_ERR == ulSendResult)
    {
        NAS_LMM_EMM_PLMN_LOG_ERR("NAS_EMM_MsDeregSsAttemptToAttachMsgMmcSysInfoInd : Send IntraMsg Failure!!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsDeregSsAttemptToAttachMsgMmcSysInfoInd_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsDeregSsNormalSrvMsgMmcSysInfoInd
 Description     : Dereg.Normal_Servie状态下收到系统消息，检查如果有禁止信息，状态
                    迁移到 Dereg.Limite_service状态，如果没有禁止信息，状态不变
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2009-8-20  Draft Enact
    2.lihong00150010            2012-12-13 Modify:Emergency
    3.leixiantiao 00258641      2015-07-03 fix DTS2015062301014
*****************************************************************************/
VOS_UINT32  NAS_EMM_MsDeregSsNormalSrvMsgMmcSysInfoInd(
                                    VOS_UINT32              ulMsgId,
                                    VOS_VOID               *pMsg )
{
    EMMC_EMM_SYS_INFO_IND_STRU          *pstMmcSysInfoInd;
    NAS_EMM_FSM_STATE_STRU              EmmState;
    VOS_UINT32                          ulSendResult;
    NAS_EMM_ESM_MSG_BUFF_STRU          *pstEsmMsg = NAS_EMM_NULL_PTR;

    (VOS_VOID)ulMsgId;

    NAS_EMM_PLMN_INIT_EMMSTATE(EmmState);

    /* 打印进入该函数， INFO_LEVEL */
    NAS_LMM_EMM_PLMN_LOG_NORM("NAS_EMM_MsDeregSsNormalSrvMsgMmcSysInfoInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDeregSsNormalSrvMsgMmcSysInfoInd_ENUM,LNAS_ENTRY);

    /* 函数输入指针参数检查 */
    if (VOS_NULL_PTR == pMsg)
    {
        NAS_LMM_EMM_PLMN_LOG_ERR("NAS_EMM_MsDeregSsNormalSrvMsgMmcSysInfoInd: MSG PARAM NULL POINTER ERROR!!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsDeregSsNormalSrvMsgMmcSysInfoInd_ENUM,LNAS_NULL_PTR);
        return NAS_LMM_ERR_CODE_PARA_INVALID;
    }

    /* 状态匹配检查,若不匹配,退出 */
    if(NAS_EMM_PLMN_CHK_STAT_INVALID(EMM_MS_DEREG, EMM_SS_DEREG_NORMAL_SERVICE))
    {
        NAS_LMM_EMM_PLMN_LOG_WARN("NAS_EMM_MsDeregSsNormalSrvMsgMmcSysInfoInd: STATE ERROR!!!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDeregSsNormalSrvMsgMmcSysInfoInd_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    pstMmcSysInfoInd = (EMMC_EMM_SYS_INFO_IND_STRU *) pMsg;
    /* 如果ATTACH的触发类型是紧急PDN建立引起的普通注册，且缓存的紧急PDN建立请求
       消息有效，则发起紧急注册 */
    pstEsmMsg = (NAS_EMM_ESM_MSG_BUFF_STRU*)(VOS_VOID*)NAS_LMM_GetEmmInfoEsmBuffAddr();
    if ((EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER == NAS_EMM_GLO_AD_GetAttCau())
        && (NAS_EMM_NULL_PTR != pstEsmMsg))
    {
        NAS_LMM_EMM_PLMN_LOG_WARN("NAS_EMM_MsDeregSsNormalSrvMsgMmcSysInfoInd: case ESM_ATTACH_FOR_INIT_EMC_BERER");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDeregSsNormalSrvMsgMmcSysInfoInd_ENUM,LNAS_EMM_ATTACH_EMC_BEAER);

        /*保存ESM消息*/
        NAS_LMM_MEM_CPY_S(  (VOS_VOID*)NAS_EMM_GLO_AD_GetEsmMsgAddr(),
                            sizeof(NAS_EMM_CN_MSGCON_STRU),
                            &(pstEsmMsg->stEsmMsg),
                            (pstEsmMsg->stEsmMsg.ulEsmMsgSize)+4);

        NAS_EMM_StartEmergencyAttach();

        return NAS_LMM_MSG_HANDLED;
    }
    if ((EMMC_EMM_NO_FORBIDDEN != pstMmcSysInfoInd->ulForbiddenInfo) /* TA在禁止的TA列表中 */
        || (EMMC_EMM_CELL_STATUS_ANYCELL == pstMmcSysInfoInd->ulCellStatus))
    {
        /* 将状态转移至MS_DEREG + SS_DEREG_LIMITED_SERVICE状态 */
        EmmState.enMainState            = EMM_MS_DEREG;
        EmmState.enSubState             = EMM_SS_DEREG_LIMITED_SERVICE;
        EmmState.enStaTId               = TI_NAS_EMM_STATE_NO_TIMER;
        NAS_LMM_StaTransProc(EmmState);

        NAS_EMM_SetAttType();

        /*向MMC发送LMM_MMC_ATTACH_CNF或LMM_MMC_ATTACH_IND消息*/
        NAS_EMM_AppSendAttRsltForb(pstMmcSysInfoInd->ulForbiddenInfo);
    }
    if(NAS_EMM_AUTO_ATTACH_NOT_ALLOW == NAS_EMM_GetPsAttachAllowFlg())
    {
        NAS_LMM_EMM_PLMN_LOG_ERR("NAS_EMM_MsDeregSsNormalSrvMsgMmcSysInfoInd : attach not allowed!!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsDeregSsNormalSrvMsgMmcSysInfoInd_ENUM,LNAS_FUNCTION_LABEL1);
        /* 网络信息更新,MMA不会立即更新网络信息,需要收到TAU/ATTACH才会更新,为规避该问题,
       LMM构造一条不带任何参数ATTACH结果消息上报给MMC */
        /* 在UE收到MMC发来的系统消息之后，若要发起attach流程，按照原有流程处理；若不需发attach，那么给MMC上报attach结果的假消息 */

        /* 向MMC上报ATTACH结果 */
        NAS_EMM_AppSendAttPsNotAllow();
        return NAS_LMM_MSG_HANDLED;
    }
    /* 向ATTACH模块发送EMM_INTRA_ATTACH_REQ消息 */
    ulSendResult = NAS_EMM_SendIntraAttachReq();
    if (NAS_EMM_PLMN_ERR == ulSendResult)
    {
        NAS_LMM_EMM_PLMN_LOG_ERR("NAS_EMM_MsDeregSsNormalSrvMsgMmcSysInfoInd : Send IntraMsg Failure!!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsDeregSsNormalSrvMsgMmcSysInfoInd_ENUM,LNAS_FUNCTION_LABEL2);
        return NAS_LMM_MSG_HANDLED;
    }

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsDeregSsLimitSrvMsgMmcSysInfoInd
 Description     : Dereg.Limit_Servie状态下收到系统消息，判断有没有禁止信息，
                   若没有，再根据Last TA和定时器判断是否需要等定时器超时，如果
                   不需要，则立即发起ATTACH
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2009-7-22   Draft Enact
    2.sunjitan 00193151         2012-07-10  Modify: Last attempt reg TA 维护,增加对定时器的判断
    3.lihong00150010            2012-11-01  Modify:emgergency
    4.leixiantiao 00258641      2015-07-03  fix DTS2015062301014
*****************************************************************************/
VOS_UINT32 NAS_EMM_MsDeregSsLimitSrvMsgMmcSysInfoInd(
                                    VOS_UINT32              ulMsgId,
                                    VOS_VOID               *pMsg )
{
    VOS_UINT32                          ulSendResult;
    EMMC_EMM_SYS_INFO_IND_STRU         *pstMmcSysInfoInd = NAS_EMM_NULL_PTR;
    NAS_EMM_FSM_STATE_STRU              EmmState;
    NAS_MM_TA_STRU                     *pstLastAttmpRegTa = NAS_EMM_NULL_PTR;
    NAS_MM_TA_STRU                      stCurTa;
    NAS_EMM_ESM_MSG_BUFF_STRU          *pstEsmMsg = NAS_EMM_NULL_PTR;

    NAS_LMM_MEM_SET_S(&stCurTa, sizeof(NAS_MM_TA_STRU), 0, sizeof(NAS_MM_TA_STRU));

    (VOS_VOID)ulMsgId;

    NAS_EMM_PLMN_INIT_EMMSTATE(EmmState);

    /* 打印进入该函数， INFO_LEVEL */
    NAS_LMM_EMM_PLMN_LOG_NORM("NAS_EMM_MsDeregSsLimitSrvMsgMmcSysInfoInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDeregSsLimitSrvMsgMmcSysInfoInd_ENUM,LNAS_ENTRY);

    /* 状态匹配检查,若不匹配,退出 */
    if(NAS_EMM_PLMN_CHK_STAT_INVALID(EMM_MS_DEREG, EMM_SS_DEREG_LIMITED_SERVICE))
    {
        NAS_LMM_EMM_PLMN_LOG_WARN("NAS_EMM_MsDeregSsLimitSrvMsgMmcSysInfoInd: STATE ERROR!!!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDeregSsLimitSrvMsgMmcSysInfoInd_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    pstMmcSysInfoInd = (EMMC_EMM_SYS_INFO_IND_STRU *) pMsg;

    /* 如果ATTACH的触发类型是紧急PDN建立引起的普通注册，且缓存的紧急PDN建立请求
       消息有效，则发起紧急注册 */
    pstEsmMsg = (NAS_EMM_ESM_MSG_BUFF_STRU*)(VOS_VOID*)NAS_LMM_GetEmmInfoEsmBuffAddr();
    if ((EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER == NAS_EMM_GLO_AD_GetAttCau())
        && (NAS_EMM_NULL_PTR != pstEsmMsg))
    {
        NAS_LMM_EMM_PLMN_LOG_WARN("NAS_EMM_MsDeregSsLimitSrvMsgMmcSysInfoInd: case ESM_ATTACH_FOR_INIT_EMC_BERER");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDeregSsLimitSrvMsgMmcSysInfoInd_ENUM,LNAS_EMM_ATTACH_EMC_BEAER);

        /*保存ESM消息*/
        NAS_LMM_MEM_CPY_S(  (VOS_VOID*)NAS_EMM_GLO_AD_GetEsmMsgAddr(),
                            sizeof(NAS_EMM_CN_MSGCON_STRU),
                            &(pstEsmMsg->stEsmMsg),
                            (pstEsmMsg->stEsmMsg.ulEsmMsgSize)+4);

        NAS_EMM_StartEmergencyAttach();

        return NAS_LMM_MSG_HANDLED;
    }

    if ((EMMC_EMM_NO_FORBIDDEN != pstMmcSysInfoInd->ulForbiddenInfo) /* TA在禁止的TA列表中 */
        || (EMMC_EMM_CELL_STATUS_ANYCELL == pstMmcSysInfoInd->ulCellStatus))
    {
        /* 将状态转移至MS_DEREG + SS_DEREG_LIMITED_SERVICE状态 */
        EmmState.enMainState            = EMM_MS_DEREG;
        EmmState.enSubState             = EMM_SS_DEREG_LIMITED_SERVICE;
        EmmState.enStaTId               = TI_NAS_EMM_STATE_NO_TIMER;
        NAS_LMM_StaTransProc(EmmState);

        NAS_EMM_SetAttType();

        /*向MMC发送LMM_MMC_ATTACH_CNF或LMM_MMC_ATTACH_IND消息*/
        NAS_EMM_AppSendAttRsltForb(pstMmcSysInfoInd->ulForbiddenInfo);

        return NAS_LMM_MSG_HANDLED;
    }

    /* 获取当前TA和上次尝试注册的TA信息 */
    NAS_EMM_GetCurrentTa(&stCurTa);
    pstLastAttmpRegTa                  = NAS_LMM_GetEmmInfoNetInfoLastAttmpRegTaAddr();

    /* 判断是否需要等定时器超时再发起注册 */
    if (NAS_LMM_MATCH_SUCCESS == NAS_LMM_TaMatch(pstLastAttmpRegTa, &stCurTa))
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsDeregSsLimitSrvMsgMmcSysInfoInd: The same as last attempt TA.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDeregSsLimitSrvMsgMmcSysInfoInd_ENUM,LNAS_EMM_TA_NO_CHANGE);

        if(NAS_EMM_YES == NAS_EMM_Attach_IsTimerRunning())
        {
            if (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_T3411))
            {
                /* 网络信息更新,MMA不会立即更新网络信息,需要收到TAU/ATTACH才会更新,为规避该问题,
                LMM构造一条不带任何参数ATTACH结果消息上报给MMC */
                /* 在UE收到MMC发来的系统消息之后，若要发起attach或tau流程，按照原有流程处理；若不发，那么给MMC上报attach结果的假消息 */
                NAS_EMM_AppSendAttRstDefaultReqType(MMC_LMM_ATT_RSLT_FAILURE);
            }
            return NAS_LMM_MSG_HANDLED;
        }
    }
    else
    {
        /*重设attach attempt counter*/
        NAS_EMM_AttResetAttAttempCounter();
    }

    /* 将状态转移至MS_DEREG + SS_DEREG_NORMAL_SERVICE状态 */
    EmmState.enMainState            = EMM_MS_DEREG;
    EmmState.enSubState             = EMM_SS_DEREG_NORMAL_SERVICE;
    EmmState.enStaTId               = TI_NAS_EMM_STATE_NO_TIMER;
    NAS_LMM_StaTransProc(EmmState);

    /* 向ATTACH模块发送EMM_INTRA_ATTACH_REQ消息 */
    ulSendResult = NAS_EMM_SendIntraAttachReq();
    if (NAS_EMM_PLMN_ERR == ulSendResult)
    {
        /* 打印函数，ERROR_LEVEL */
        NAS_LMM_EMM_PLMN_LOG_ERR("NAS_EMM_MsDeregSsLimitSrvMsgMmcSysInfoInd : Send IntraMsg Failure!!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsDeregSsLimitSrvMsgMmcSysInfoInd_ENUM,LNAS_FAIL);
        return NAS_LMM_MSG_HANDLED;
    }

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsDeregSsPlmnSearchMsgMmcSysInfoInd
 Description     : Dereg.Plmn_Search状态下收到系统消息，如果没有禁止信息，
                   再根据Last TA和定时器判断是否需要等待定时器超时，如果不需要，
                   则立即发起ATTACH, 否则转状态等定时器超时
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2009-7-22   Draft Enact
    2.sunjitan 00193151         2012-07-10  modify: Last attempt reg TA 维护,增加对定时器的判断
    3.lihong00150010            2012-11-01  Modify:emgergency
    4.leixiantiao 00258641      2015-07-03  fix DTS2015062301014
*****************************************************************************/
VOS_UINT32 NAS_EMM_MsDeregSsPlmnSearchMsgMmcSysInfoInd(
                                            VOS_UINT32              ulMsgId,
                                            VOS_VOID               *pMsg )
{
    VOS_UINT32                          ulSendResult;
    EMMC_EMM_SYS_INFO_IND_STRU         *pstMmcSysInfoInd = NAS_EMM_NULL_PTR;
    NAS_EMM_FSM_STATE_STRU              EmmState;
    NAS_MM_TA_STRU                     *pstLastAttmpRegTa = NAS_EMM_NULL_PTR;
    NAS_MM_TA_STRU                      stCurTa;
    NAS_EMM_ESM_MSG_BUFF_STRU          *pstEsmMsg = NAS_EMM_NULL_PTR;

    NAS_LMM_MEM_SET_S(&stCurTa, sizeof(NAS_MM_TA_STRU), 0, sizeof(NAS_MM_TA_STRU));
    (VOS_VOID)ulMsgId;

    NAS_EMM_PLMN_INIT_EMMSTATE(EmmState);

    /* 打印进入该函数， INFO_LEVEL */
    NAS_LMM_EMM_PLMN_LOG_NORM("NAS_EMM_MsDeregSsPlmnSearchMsgMmcSysInfoInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDeregSsPlmnSearchMsgMmcSysInfoInd_ENUM,LNAS_ENTRY);

    /* 状态匹配检查,若不匹配,退出 */
    if(NAS_EMM_PLMN_CHK_STAT_INVALID(EMM_MS_DEREG, EMM_SS_DEREG_PLMN_SEARCH))
    {
        NAS_LMM_EMM_PLMN_LOG_WARN("NAS_EMM_MsDeregSsPlmnSearchMsgMmcSysInfoInd: STATE ERROR!!!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDeregSsPlmnSearchMsgMmcSysInfoInd_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    pstMmcSysInfoInd = (EMMC_EMM_SYS_INFO_IND_STRU *) pMsg;

    /* 如果ATTACH的触发类型是紧急PDN建立引起的普通注册，且缓存的紧急PDN建立请求
       消息有效，则发起紧急注册 */
    pstEsmMsg = (NAS_EMM_ESM_MSG_BUFF_STRU*)(VOS_VOID*)NAS_LMM_GetEmmInfoEsmBuffAddr();
    if ((EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER == NAS_EMM_GLO_AD_GetAttCau())
        && (NAS_EMM_NULL_PTR != pstEsmMsg))
    {
        NAS_LMM_EMM_PLMN_LOG_WARN("NAS_EMM_MsDeregSsPlmnSearchMsgMmcSysInfoInd: case ESM_ATTACH_FOR_INIT_EMC_BERER");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDeregSsPlmnSearchMsgMmcSysInfoInd_ENUM,LNAS_EMM_ATTACH_EMC_BEAER);

        /*保存ESM消息*/
        NAS_LMM_MEM_CPY_S(  (VOS_VOID*)NAS_EMM_GLO_AD_GetEsmMsgAddr(),
                            sizeof(NAS_EMM_CN_MSGCON_STRU),
                            &(pstEsmMsg->stEsmMsg),
                            (pstEsmMsg->stEsmMsg.ulEsmMsgSize)+4);

        NAS_EMM_StartEmergencyAttach();

        return NAS_LMM_MSG_HANDLED;
    }

    if ((EMMC_EMM_NO_FORBIDDEN != pstMmcSysInfoInd->ulForbiddenInfo) /* TA在禁止的TA列表中 */
        || (EMMC_EMM_CELL_STATUS_ANYCELL == pstMmcSysInfoInd->ulCellStatus))
    {
        NAS_LMM_EMM_PLMN_LOG_NORM("NAS_EMM_MsDeregSsPlmnSearchMsgMmcSysInfoInd: FORBID SYS INFO");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDeregSsPlmnSearchMsgMmcSysInfoInd_ENUM,LNAS_EMM_FORB_INFO);

        /* 将状态转移至MS_DEREG + SS_DEREG_LIMITED_SERVICE状态 */
        EmmState.enMainState            = EMM_MS_DEREG;
        EmmState.enSubState             = EMM_SS_DEREG_LIMITED_SERVICE;
        EmmState.enStaTId               = TI_NAS_EMM_STATE_NO_TIMER;
        NAS_LMM_StaTransProc(EmmState);

        NAS_EMM_SetAttType();

        /*向MMC发送LMM_MMC_ATTACH_CNF或LMM_MMC_ATTACH_IND消息*/
        NAS_EMM_AppSendAttRsltForb(pstMmcSysInfoInd->ulForbiddenInfo);

        return NAS_LMM_MSG_HANDLED;
    }

    /* 获取当前TA和上次尝试注册的TA信息 */
    NAS_EMM_GetCurrentTa(&stCurTa);
    pstLastAttmpRegTa                  = NAS_LMM_GetEmmInfoNetInfoLastAttmpRegTaAddr();

    /* 判断是否需要等定时器超时再发起注册 */
    if (NAS_LMM_MATCH_SUCCESS == NAS_LMM_TaMatch(pstLastAttmpRegTa, &stCurTa))
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsDeregSsPlmnSearchMsgMmcSysInfoInd: The same as last attempt TA.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDeregSsPlmnSearchMsgMmcSysInfoInd_ENUM,LNAS_EMM_TA_NO_CHANGE);

        if(NAS_EMM_YES == NAS_EMM_Attach_IsTimerRunning())
        {
            if (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_T3411))
            {
                /* 网络信息更新,MMA不会立即更新网络信息,需要收到TAU/ATTACH才会更新,为规避该问题,
                LMM构造一条不带任何参数ATTACH结果消息上报给MMC */
                /* 在UE收到MMC发来的系统消息之后，若要发起attach或tau流程，按照原有流程处理；若不发，那么给MMC上报attach结果的假消息 */
                NAS_EMM_AppSendAttRstDefaultReqType(MMC_LMM_ATT_RSLT_FAILURE);
            }
            return NAS_LMM_MSG_HANDLED;
        }
    }
    else
    {
        /*重设attach attempt counter*/
        NAS_EMM_AttResetAttAttempCounter();
    }

    /* 将状态转移至MS_DEREG + SS_DEREG_NORMAL_SERVICE状态 */
    EmmState.enMainState            = EMM_MS_DEREG;
    EmmState.enSubState             = EMM_SS_DEREG_NORMAL_SERVICE;
    EmmState.enStaTId               = TI_NAS_EMM_STATE_NO_TIMER;
    NAS_LMM_StaTransProc(EmmState);

    /* 向ATTACH模块发送EMM_INTRA_ATTACH_REQ消息 */
    ulSendResult = NAS_EMM_SendIntraAttachReq();
    if (NAS_EMM_PLMN_ERR == ulSendResult)
    {
        /* 打印函数，ERROR_LEVEL */
        NAS_LMM_EMM_PLMN_LOG_ERR("NAS_EMM_MsDeregSsPlmnSearchMsgMmcSysInfoInd : Send IntraMsg Failure!!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsDeregSsPlmnSearchMsgMmcSysInfoInd_ENUM,LNAS_FAIL);
        return NAS_LMM_MSG_HANDLED;
    }

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsDeregSsNoCellAvailMsgMmcSysInfoInd
 Description     : Dereg.NoCellAvailable状态下收到系统消息，判断如果有禁止信
                   息，进入Dereg.Limit_Service状态，没有禁止信息，判断是否需要等
                   定时器超时，如果不需要，则立即发起ATTACH
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2009-7-22   Draft Enact
    2.zhengjunyan 00148421      2011-12-22
    3.sunjitan 00193151         2012-07-10  Modify: Last attempt reg TA 维护,增加对定时器的判断
    4.lihong00150010            2012-11-01  Modify:emgergency
    4.leixiantiao 00258641      2015-07-03  fix DTS2015062301014
*****************************************************************************/
VOS_UINT32 NAS_EMM_MsDeregSsNoCellAvailMsgMmcSysInfoInd
(
    VOS_UINT32              ulMsgId,
    VOS_VOID               *pMsg
)
{
    VOS_UINT32                          ulSendResult;
    EMMC_EMM_SYS_INFO_IND_STRU         *pstMmcSysInfoInd = NAS_EMM_NULL_PTR;
    NAS_EMM_FSM_STATE_STRU              EmmState;
    NAS_MM_TA_STRU                     *pstLastAttmpRegTa = NAS_EMM_NULL_PTR;
    NAS_MM_TA_STRU                      stCurTa;
    NAS_EMM_ESM_MSG_BUFF_STRU          *pstEsmMsg = NAS_EMM_NULL_PTR;

    NAS_LMM_MEM_SET_S(&stCurTa, sizeof(NAS_MM_TA_STRU), 0, sizeof(NAS_MM_TA_STRU));
    (VOS_VOID)ulMsgId;

    NAS_EMM_PLMN_INIT_EMMSTATE(EmmState);

    /* 打印进入该函数， INFO_LEVEL */
    NAS_LMM_EMM_PLMN_LOG_NORM("NAS_EMM_MsDeregSsNoCellAvailMsgMmcSysInfoInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDeregSsNoCellAvailMsgMmcSysInfoInd_ENUM,LNAS_ENTRY);

    /* 状态匹配检查,若不匹配,退出 */
    if(NAS_EMM_PLMN_CHK_STAT_INVALID(EMM_MS_DEREG, EMM_SS_DEREG_NO_CELL_AVAILABLE))
    {
        NAS_LMM_EMM_PLMN_LOG_WARN("NAS_EMM_MsDeregSsNoCellAvailMsgMmcSysInfoInd: STATE ERROR!!!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDeregSsNoCellAvailMsgMmcSysInfoInd_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    /* 如果当前处于挂起态，则不处理SYS_INFO,直接丢弃*/
    if(NAS_LMM_CUR_LTE_SUSPEND == NAS_EMM_GetCurLteState())
    {
        NAS_LMM_EMM_PLMN_LOG_ERR("NAS_EMM_MsDeregSsNoCellAvailMsgMmcSysInfoInd:LTE SUSPEND.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsDeregSsNoCellAvailMsgMmcSysInfoInd_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_LMM_MSG_HANDLED;
    }

    pstMmcSysInfoInd = (EMMC_EMM_SYS_INFO_IND_STRU *) pMsg;

    /* 如果ATTACH的触发类型是紧急PDN建立引起的普通注册，且缓存的紧急PDN建立请求
       消息有效，则发起紧急注册 */
    pstEsmMsg = (NAS_EMM_ESM_MSG_BUFF_STRU*)(VOS_VOID*)NAS_LMM_GetEmmInfoEsmBuffAddr();
    if ((EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER == NAS_EMM_GLO_AD_GetAttCau())
        && (NAS_EMM_NULL_PTR != pstEsmMsg))
    {
        NAS_LMM_EMM_PLMN_LOG_WARN("NAS_EMM_MsDeregSsAttemptToAttachMsgMmcSysInfoInd: case ESM_ATTACH_FOR_INIT_EMC_BERER");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDeregSsNoCellAvailMsgMmcSysInfoInd_ENUM,LNAS_EMM_ATTACH_EMC_BEAER);

        /*保存ESM消息*/
        NAS_LMM_MEM_CPY_S(  (VOS_VOID*)NAS_EMM_GLO_AD_GetEsmMsgAddr(),
                            sizeof(NAS_EMM_CN_MSGCON_STRU),
                            &(pstEsmMsg->stEsmMsg),
                            (pstEsmMsg->stEsmMsg.ulEsmMsgSize)+4);

        NAS_EMM_StartEmergencyAttach();

        return NAS_LMM_MSG_HANDLED;
    }

    if ((EMMC_EMM_NO_FORBIDDEN != pstMmcSysInfoInd->ulForbiddenInfo) /* TA在禁止的TA列表中 */
        || (EMMC_EMM_CELL_STATUS_ANYCELL == pstMmcSysInfoInd->ulCellStatus))
    {

        /* 将状态转移至MS_DEREG + SS_DEREG_LIMITED_SERVICE状态 */
        EmmState.enMainState            = EMM_MS_DEREG;
        EmmState.enSubState             = EMM_SS_DEREG_LIMITED_SERVICE;
        EmmState.enStaTId               = TI_NAS_EMM_STATE_NO_TIMER;
        NAS_LMM_StaTransProc(EmmState);

        NAS_EMM_SetAttType();

        /*向MMC发送LMM_MMC_ATTACH_CNF或LMM_MMC_ATTACH_IND消息*/
        NAS_EMM_AppSendAttRsltForb(pstMmcSysInfoInd->ulForbiddenInfo);
    }
    else
    {
        /* 获取当前TA和上次尝试注册的TA信息 */
        NAS_EMM_GetCurrentTa(&stCurTa);
        pstLastAttmpRegTa                  = NAS_LMM_GetEmmInfoNetInfoLastAttmpRegTaAddr();

        /* 判断是否需要等定时器超时再发起注册 */
        if (NAS_LMM_MATCH_SUCCESS == NAS_LMM_TaMatch(pstLastAttmpRegTa, &stCurTa))
        {
            NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsDeregSsNoCellAvailMsgMmcSysInfoInd: The same as last attempt TA.");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDeregSsNoCellAvailMsgMmcSysInfoInd_ENUM,LNAS_EMM_TA_NO_CHANGE);

            if(NAS_EMM_YES == NAS_EMM_Attach_IsTimerRunning())
            {
                if (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_T3411))
                {
                    /* 网络信息更新,MMA不会立即更新网络信息,需要收到TAU/ATTACH才会更新,为规避该问题,
                    LMM构造一条不带任何参数ATTACH结果消息上报给MMC */
                    /* 在UE收到MMC发来的系统消息之后，若要发起attach或tau流程，按照原有流程处理；若不发，那么给MMC上报attach结果的假消息 */
                    NAS_EMM_AppSendAttRstDefaultReqType(MMC_LMM_ATT_RSLT_FAILURE);

                }
                return NAS_LMM_MSG_HANDLED;
            }
        }
        else
        {
            /*重设attach attempt counter*/
            NAS_EMM_AttResetAttAttempCounter();
        }

        /* 将状态转移至MS_DEREG + SS_DEREG_NORMAL_SERVICE状态 */
        EmmState.enMainState            = EMM_MS_DEREG;
        EmmState.enSubState             = EMM_SS_DEREG_NORMAL_SERVICE;
        EmmState.enStaTId               = TI_NAS_EMM_STATE_NO_TIMER;
        NAS_LMM_StaTransProc(EmmState);

        /* 向ATTACH模块发送EMM_INTRA_ATTACH_REQ消息 */
        ulSendResult = NAS_EMM_SendIntraAttachReq();
        if (NAS_EMM_PLMN_ERR == ulSendResult)
        {
            NAS_LMM_EMM_PLMN_LOG_ERR("NAS_EMM_MsDeregSsNoCellAvailMsgMmcSysInfoInd : Send IntraMsg Failure!!!");
            TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsDeregSsNoCellAvailMsgMmcSysInfoInd_ENUM,LNAS_FAIL);
            return NAS_LMM_MSG_HANDLED;
        }
    }

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsNotNullSsAnyStateMsgRrcErrInd
 Description     : 在主状态非空状态下，收到RRC_MM_ERR_IND消息，消息响应处理程序
                   NAS收到该消息后会清除NAS当前的资源，发送内部AppStartReq消息，
                   进入开机流程
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lining 00141619      2008-10-17  Draft Enact

*****************************************************************************/
VOS_UINT32    NAS_EMM_MsNotNullSsAnyStateMsgRrcErrInd(
                    VOS_UINT32                              ulMsgId,
                    VOS_VOID                                *pMsg )
{
    NAS_EMM_FSM_STATE_STRU                      EmmState;

    (VOS_VOID)(ulMsgId);

    NAS_EMM_PLMN_INIT_EMMSTATE(EmmState);

    /* 打印进入该函数， INFO_LEVEL */
    NAS_LMM_EMM_PLMN_LOG_NORM("NAS_EMM_MsNotNullSsAnyStateMsgRrcErrInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsNotNullSsAnyStateMsgRrcErrInd_ENUM,LNAS_ENTRY);

    /* 函数输入指针参数检查 */
    if (VOS_NULL_PTR == pMsg)
    {
        /* 打印异常，ERROR_LEVEL */
        NAS_LMM_EMM_PLMN_LOG_ERR("NAS_EMM_MsNotNullSsAnyStateMsgRrcErrInd: MSG PARAM NULL POINTER ERROR!!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsNotNullSsAnyStateMsgRrcErrInd_ENUM,LNAS_NULL_PTR);
        return NAS_LMM_ERR_CODE_PARA_INVALID;
    }

    /* 状态匹配检查,若不匹配,退出 */
    if (EMM_MS_NULL == EmmState.enMainState)
    {
        NAS_LMM_EMM_PLMN_LOG_WARN("NAS_EMM_MsNotNullSsAnyStateMsgRrcErrInd: STATE ERROR!!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsNotNullSsAnyStateMsgRrcErrInd_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    /*停止所有定时器*/
    NAS_LMM_StopAllPtlTimer();
    NAS_LMM_StopAllStateTimer();

    /* 释放可能存在的动态内存 */
    NAS_LMM_FreeDynMem();

    /* 写入EMM NV相关信息 */
    NAS_EMM_WriteNvMmInfo();

    /* 写入MMC NV相关信息 */
    /*NAS_EMMC_WriteNvMmInfo();*/

    /*状态机清空，并状态赋初值*/
    NAS_LMM_PUBM_Init();

    /*向ESM发送ID_EMM_ESM_STATUS_IND消息*/
    NAS_EMM_EsmSendStatResult(          EMM_ESM_ATTACH_STATUS_DETACHED);
    /*通知 RABM:RRC_CONN_REL_IND*/
    NAS_LMM_SendRabmRrcConRelInd(EMM_ERABM_REL_CAUSE_NULL);

    /* 发送内部的AppStartReq */
    /*  V7R1不能自动开机，而是等待MMC的开机  */
    /*    NAS_LMM_SendStubIntraAppStartReq();*/

    /* 通知MMC */
    NAS_EMM_SendMmcErrInd(0xff);


    /* 状态转换 */
    /* 将状态转移至MS_NULL + EMM_SS_NULL_WAIT_APP_START_REQ状态 */
    EmmState.enFsmId                    = NAS_LMM_PARALLEL_FSM_EMM;
    EmmState.enMainState                = EMM_MS_NULL;
    EmmState.enSubState                 = EMM_SS_NULL_WAIT_APP_START_REQ;
    EmmState.enStaTId                   = TI_NAS_EMM_STATE_NO_TIMER;
    NAS_LMM_StaTransProc(EmmState);

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsNotNullSsAnyStateMsgRrcPagingInd
 Description     : 在主状态非空状态下，收到RRC_EMM_PAGING_IND消息
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.zhengjunyan 00148421 2009.03.24 New Draft
*****************************************************************************/
VOS_UINT32    NAS_EMM_MsNotNullSsAnyStateMsgRrcPagingInd(
                    VOS_UINT32                              ulMsgId,
                    VOS_VOID                                *pMsg )
{
    LRRC_LMM_PAGING_IND_STRU    * pMsgRrcPagingInd = NAS_EMM_NULL_PTR;

    (VOS_VOID)ulMsgId;

    NAS_LMM_EMM_PLMN_LOG_INFO("NAS_EMM_MsNotNullSsAnyStateMsgRrcPagingInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsNotNullSsAnyStateMsgRrcPagingInd_ENUM,LNAS_ENTRY);

    /*check the current state*/
    if (EMM_MS_NULL == NAS_EMM_CUR_MAIN_STAT)
    {
        NAS_LMM_EMM_PLMN_LOG_WARN("NAS_EMM_MsNotNullSsAnyStateMsgRrcPagingInd: STATE ERROR!!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsNotNullSsAnyStateMsgRrcPagingInd_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    /*get RRC_PAGING_IND Msg*/
    pMsgRrcPagingInd = (LRRC_LMM_PAGING_IND_STRU *)pMsg;

    /*check the CN domain:
       LRRC_LNAS_PAGING_TYPE1->CS;
       LRRC_LNAS_PAGING_TYPE2->PS*/
    if(LRRC_LNAS_PAGING_TYPE1 == pMsgRrcPagingInd->enPagingType)
    {
        NAS_EMM_PLMN_CsPagingProc(pMsgRrcPagingInd->enPagingUeId);

        return NAS_LMM_MSG_HANDLED;
    }

    /*Paging with IMSI*/
    if(LRRC_LNAS_IMSI_LTE == pMsgRrcPagingInd->enPagingUeId)
    {
        #if (FEATURE_PTM == FEATURE_ON)
        NAS_EMM_PagingErrRecord(EMM_OM_ERRLOG_PAGING_PS_IMSI, EMM_OM_LMM_PAGING_FAIL_CAUSE_NULL);
        #endif
        NAS_EMM_PLMN_ImsiPagingProc();
    }
    /*Paging with S-TMSI*/
    else if(LRRC_LNAS_S_TMSI_LTE == pMsgRrcPagingInd->enPagingUeId)
    {
        NAS_EMM_PLMN_STmsiPagingProc();
    }
    /*Paging with Other UeId*/
    else
    {
        NAS_LMM_EMM_PLMN_LOG_WARN("NAS_EMM_MsNotNullSsAnyStateMsgRrcPagingInd:Other UeId not support");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsNotNullSsAnyStateMsgRrcPagingInd_ENUM,LNAS_FUNCTION_LABEL1);
    }

    return NAS_LMM_MSG_HANDLED;
}
/*****************************************************************************
 Function Name   : NAS_EMM_MsTauInitSsTauWaitCnTauCnfMsgRrcPagingInd
 Description     : 在主状态TAU INIT收到RRC_EMM_PAGING_IND消息
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunjitan 00193151    2015-07-09   Draft Enact
*****************************************************************************/
VOS_UINT32    NAS_EMM_MsTauInitSsTauWaitCnTauCnfMsgRrcPagingInd(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsg
)
{
    LRRC_LMM_PAGING_IND_STRU           *pMsgRrcPagingInd = NAS_EMM_NULL_PTR;

    (VOS_VOID)ulMsgId;

    NAS_LMM_EMM_PLMN_LOG_INFO("NAS_EMM_MsTauInitSsTauWaitCnTauCnfMsgRrcPagingInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsTauInitSsTauWaitCnTauCnfMsgRrcPagingInd_ENUM, LNAS_ENTRY);

    pMsgRrcPagingInd = (LRRC_LMM_PAGING_IND_STRU *)pMsg;

    /* CS域的PAGING，直接处理 */
    if(LRRC_LNAS_PAGING_TYPE1 == pMsgRrcPagingInd->enPagingType)
    {
        NAS_EMM_SER_RcvRrcCsPagingInd(pMsgRrcPagingInd->enPagingUeId);
    }
    else
    {
        /* 其他PAGING，丢弃 */
        #if (FEATURE_ON == FEATURE_PTM)
        /* 由于在该状态下丢弃了PS域的PAGING，所以增加CHR上报 */
        NAS_EMM_PagingErrRecord(EMM_OM_ERRLOG_PAGING_PS,EMM_OM_LMM_PAGING_FAIL_CAUSE_ABNORMAL_STATUS);
        #endif
    }
    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsSerInitSsSerWaitCnSerCnfMsgRrcPagingInd
 Description     : 在主状态SER INIT收到RRC_EMM_PAGING_IND消息
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunjitan 00193151    2015-07-09   Draft Enact
*****************************************************************************/
VOS_UINT32    NAS_EMM_MsSerInitSsSerWaitCnSerCnfMsgRrcPagingInd(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsg
)
{
    LRRC_LMM_PAGING_IND_STRU           *pMsgRrcPagingInd = NAS_EMM_NULL_PTR;

    (VOS_VOID)ulMsgId;

    NAS_LMM_EMM_PLMN_LOG_INFO("NAS_EMM_MsSerInitSsSerWaitCnSerCnfMsgRrcPagingInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsSerInitSsSerWaitCnSerCnfMsgRrcPagingInd_ENUM, LNAS_ENTRY);

    pMsgRrcPagingInd = (LRRC_LMM_PAGING_IND_STRU *)pMsg;

    /* CS域的PAGING，直接处理 */
    if(LRRC_LNAS_PAGING_TYPE1 == pMsgRrcPagingInd->enPagingType)
    {
        NAS_EMM_SER_RcvRrcCsPagingInd(pMsgRrcPagingInd->enPagingUeId);
    }
    else
    {

        /* 其他PAGING，丢弃 */
        #if (FEATURE_ON == FEATURE_PTM)
        /* 由于在该状态下丢弃了PS域的PAGING，所以增加CHR上报 */
        NAS_EMM_PagingErrRecord(EMM_OM_ERRLOG_PAGING_PS,EMM_OM_LMM_PAGING_FAIL_CAUSE_ABNORMAL_STATUS);
        #endif
    }
    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsDeregSsNoImsiMsgMmcPlmnInd
 Description     : 在主状态DEREG下，子状态为NoImsi,收到MMC_EMM_PLMN_IND消息的处理；
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
 1. X00148705      2009-08-12  Draft Enact

*****************************************************************************/
VOS_UINT32    NAS_EMM_MsDeregSsNoImsiMsgMmcPlmnInd(
                    VOS_UINT32                              ulMsgId,
                    VOS_VOID                                *pMsg)
{
    /*VOS_UINT32                          ulSendResult;*/
    NAS_EMM_FSM_STATE_STRU              EmmState;

    (VOS_VOID)(ulMsgId);
    (VOS_VOID)(pMsg);

    NAS_EMM_PLMN_INIT_EMMSTATE(EmmState);

    /* 打印进入该函数，INFO_LEVEL */
    NAS_LMM_EMM_PLMN_LOG_NORM("NAS_EMM_MsDeregSsNoImsiMsgMmcPlmnInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDeregSsNoImsiMsgMmcPlmnInd_ENUM,LNAS_ENTRY);

    /* 函数输入指针参数检查 */
    if (VOS_NULL_PTR == pMsg)
    {
        /* 打印异常，ERROR_LEVEL */
        NAS_LMM_EMM_PLMN_LOG_ERR("NAS_EMM_MsDeregSsNoImsiMsgMmcPlmnInd: MSG PARAM NULL POINTER ERROR!!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsDeregSsNoImsiMsgMmcPlmnInd_ENUM,LNAS_NULL_PTR);
        return NAS_LMM_ERR_CODE_PARA_INVALID;
    }

    /* 状态匹配检查,若不匹配,退出 */
    if (EMM_MS_NULL == EmmState.enMainState)
    {
        NAS_LMM_EMM_PLMN_LOG_WARN("NAS_EMM_MsDeregSsNoImsiMsgMmcPlmnInd: STATE ERROR!!!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDeregSsNoImsiMsgMmcPlmnInd_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }
    NAS_LMM_EMM_PLMN_LOG_INFO("NAS_EMM_MsDeregSsNoImsiMsgMmcPlmnInd: Set NAS_EMM_PLMN_SRCH_NO_IMSI_TRUE!!!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDeregSsNoImsiMsgMmcPlmnInd_ENUM,LNAS_FUNCTION_LABEL1);

    /* 判断若为挂起态，则通知ESM和ERABM激活，但不获取GU的安全参数 */
    NAS_EMM_NoImsiSuspendMsgMmcPlmnReq();

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsNullSsAnyStateMsgRrcErrInd
 Description     : 处理在MS未NULL时的RRC_ERR_IND消息
 Input           :
                   在NULL状态下收到ErrInd，将其丢弃
                   1)等待RRC_Cnf时收到ErrInd，丢弃此消息。记时器超时后会回到WaitAppStartReq
                     状态。
                   2)关机过程中收到消息，将其丢弃，记时器超时后会继续完成关机过程

 Output          : None
 Return          : VOS_UINT32

 History         :
    1.X00148705    2009-11-2  Draft Enact
    2.y00159566    2010-6-10  Modify

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsNullSsAnyStateMsgRrcErrInd(
    VOS_UINT32                                              ulMsgId,
    VOS_VOID                                                *pMsg)

{
    (VOS_VOID)(ulMsgId);
    (VOS_VOID)(pMsg);

    NAS_LMM_EMM_PLMN_LOG_NORM(           "NAS_EMM_MsNullSsAnyStateMsgRrcErrInd: enter.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsNullSsAnyStateMsgRrcErrInd_ENUM,LNAS_ENTRY);


    return NAS_LMM_MSG_DISCARD;

}


/*****************************************************************************
 Function Name   : NAS_EMM_ProcRrcStopRslt
 Description     : 收到RRC_STOP_CNF或者等待RRC关机超时的公共处理，完成NAS关机
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-8-30  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_ProcRrcStopRslt( VOS_VOID )
{
    NAS_EMM_FSM_STATE_STRU              EmmState;

    NAS_EMM_PLMN_INIT_EMMSTATE(EmmState);

    /*关机初始化 PUBM*/
    NAS_LMM_PUBM_Init();

    /* 将状态转移至MS_NULL + SS_WAIT_APP_START_REQ状态 */
    EmmState.enFsmId                = NAS_LMM_PARALLEL_FSM_EMM;
    EmmState.enMainState            = EMM_MS_NULL;
    EmmState.enSubState             = EMM_SS_NULL_WAIT_APP_START_REQ;
    EmmState.enFsmId                = TI_NAS_EMM_STATE_NO_TIMER;
    NAS_LMM_StaTransProc(EmmState);

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsNullSsWaitSwitchOffProcMsgRrcRelInd
 Description     : 在状态MsNullSsWaitSwitchOff对RRC_REL_IND消息的处理,
                   在该状态下,对RRC_ERR_REL_IND的处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.X00148705    2009-11-2  Draft Enact,代码由原函数
                   NAS_EMM_MsNullSsWaitSwitchOffMsgRrcRelInd重构而成

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsNullSsWaitSwitchOffProcMsgRrcRelInd(VOS_VOID)
{
    VOS_UINT32                          ulSendResult;
    NAS_EMM_FSM_STATE_STRU              EmmState;
    VOS_UINT8                           ucImsiRefreshFlag;

    NAS_EMM_PLMN_INIT_EMMSTATE(         EmmState);

    /* 通知ESM清除资源 */
    NAS_EMM_PLMN_SendEmmEsmStautsInd(   EMM_ESM_ATTACH_STATUS_DETACHED);

    /* 通知ESM关机 */
    NAS_EMM_EsmSendStopNotifyInd();

    /* Added by wangchen 00209181 begin for 搜网优化 2015-05-30 */
    /* 通知CSS模块关机 */
    NAS_LMM_SendCssStopInd();
    /* Added by wangchen 00209181 begin for 搜网优化 2015-05-30 */

    /*通知 RABM:RRC_CONN_REL_IND*/
    NAS_LMM_SendRabmRrcConRelInd(EMM_ERABM_REL_CAUSE_NULL);

    /* 通知ETC:REL_IND */
    NAS_EMM_TcSendRelInd();

    /*sunbing 00265702/yanglei 关机定时器没有停 begin for DTS2015092904078*/
    /*停止定时器*/
    NAS_LMM_StopPtlTimer(              TI_NAS_EMM_PTL_SWITCH_OFF_TIMER);
    /*sunbing 00265702/yanglei 关机定时器没有停 end for DTS2015092904078*/

    #if (FEATURE_ON == FEATURE_DSDS)
    /*发送end notify消息给RRC，通知RRC释放资源*/
    NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_PS_DETACH);
    #endif

    /* 向MMC发送MMC_EMM_STOP_REQ消息 */
    ulSendResult                        = NAS_EMM_PLMN_SendMmcStopReq();
    if (NAS_EMM_PLMN_ERR                == ulSendResult)
    {
        /* 打印函数，ERROR_LEVEL */
        NAS_LMM_EMM_PLMN_LOG_ERR(        "NAS_EMM_MsNullSsWaitSwitchOffMsgRrcRelInd : Send Msg Failure!!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsNullSsWaitSwitchOffProcMsgRrcRelInd_ENUM,LNAS_FAIL);
        return(                         NAS_LMM_MSG_HANDLED);
    }

    /* 如果current安全上下文为mapped 且non-current native上下文存在，
       将后者设置为current，同时删除current mapped，以便关机时写入卡中
       依据:      24301协议     5.5.2.2.1*/
    NAS_EMM_SecuDeregClrSecuCntxt();

    /* 写入EMM NV相关信息 */
    ucImsiRefreshFlag = NAS_MML_GetImsiRefreshStatus();
    NAS_LMM_SndOmImsiRefreshStatus(ucImsiRefreshFlag);
    /* IMSI REFRESH 情况下不写卡 */
    if(VOS_FALSE == ucImsiRefreshFlag)
    {
        NAS_EMM_WriteNvMmInfo();
    }

    /* 启动TI_NAS_EMM_WAIT_MMC_STOP_CNF_TIMER */
    NAS_LMM_StartStateTimer(             TI_NAS_EMM_WAIT_MMC_STOP_CNF_TIMER);

    /* 将状态转移至MS_NULL + SS_NULL_WAIT_MMC_STOP_CNF状态 */
    EmmState.enMainState                = EMM_MS_NULL;
    EmmState.enSubState                 = EMM_SS_NULL_WAIT_MMC_STOP_CNF;
    EmmState.enStaTId                   = TI_NAS_EMM_WAIT_MMC_STOP_CNF_TIMER;
    NAS_LMM_StaTransProc(                EmmState);

    return(                             NAS_LMM_MSG_HANDLED);
}


/*****************************************************************************
 Function Name   : NAS_EMM_MsNullSsWaitSwitchOffMsgRrcErrInd
 Description     : 在状态MsNullSsWaitSwitchOff处理消息RRC_ERR_IND
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.X00148705    2009-11-2  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsNullSsWaitSwitchOffMsgRrcErrInd(
    VOS_UINT32                                              ulMsgId,
    VOS_VOID                                                *pMsg )
{
    VOS_UINT32                          ulRet;

    (VOS_VOID)(                         ulMsgId);
    (VOS_VOID)(                         pMsg);

    /* 打印进入该函数， INFO_LEVEL */
    NAS_LMM_EMM_PLMN_LOG_NORM(           "NAS_EMM_MsNullSsWaitSwitchOffMsgRrcErrInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsNullSsWaitSwitchOffMsgRrcErrInd_ENUM,LNAS_ENTRY);

    /* 函数输入指针参数检查 */
    if (VOS_NULL_PTR                    == pMsg)
    {
        /* 打印异常，ERROR_LEVEL */
        NAS_LMM_EMM_PLMN_LOG_ERR(        "NAS_EMM_MsNullSsWaitSwitchOffMsgRrcErrInd: MSG PARAM NULL POINTER ERROR!!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsNullSsWaitSwitchOffMsgRrcErrInd_ENUM,LNAS_NULL_PTR);
        return(                         NAS_LMM_ERR_CODE_PARA_INVALID);
    }

    /* 状态匹配检查,若不匹配,退出 */
    if (NAS_EMM_PLMN_CHK_STAT_INVALID(  EMM_MS_NULL, EMM_SS_NULL_WAIT_SWITCH_OFF))
    {
        NAS_LMM_EMM_PLMN_LOG_WARN(       "NAS_EMM_MsNullSsWaitSwitchOffMsgRrcErrInd: STATE ERROR!!!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsNullSsWaitSwitchOffMsgRrcErrInd_ENUM,LNAS_ERROR);
        return(                         NAS_LMM_MSG_DISCARD);
    }

    /* 停止TI_NAS_EMM_PTL_SWITCH_OFF_TIMER */
    NAS_LMM_StopPtlTimer(                TI_NAS_EMM_PTL_SWITCH_OFF_TIMER);

    ulRet                               = NAS_EMM_MsNullSsWaitSwitchOffProcMsgRrcRelInd();

    return(                             ulRet);
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsDrgSsNoImsiMsgSysInfoInd
 Description     : Dereg.NO_IMSI状态下收到系统消息，直接给MMC回复ATTACH失败
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.z00179470         2012-02-06  Draft Enact
    2.lihong00150010    2012-11-01  Modify:emgergency
*****************************************************************************/
VOS_UINT32 NAS_EMM_MsDrgSsNoImsiMsgSysInfoInd(
                                    VOS_UINT32              ulMsgId,
                                    VOS_VOID               *pMsg )
{
    NAS_EMM_ESM_MSG_BUFF_STRU          *pstEsmMsg = NAS_EMM_NULL_PTR;

    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsg;

    /* 打印进入该函数， INFO_LEVEL */
    NAS_LMM_EMM_PLMN_LOG_NORM("NAS_EMM_MsDrgSsNoImsiMsgSysInfoInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDrgSsNoImsiMsgSysInfoInd_ENUM,LNAS_ENTRY);

    /* 函数输入指针参数检查 */
    if (VOS_NULL_PTR == pMsg)
    {
        NAS_LMM_EMM_PLMN_LOG_ERR("NAS_EMM_MsDrgSsNoImsiMsgSysInfoInd: MSG PARAM NULL POINTER ERROR!!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsDrgSsNoImsiMsgSysInfoInd_ENUM,LNAS_NULL_PTR);
        return NAS_LMM_ERR_CODE_PARA_INVALID;
    }

    /* 状态匹配检查,若不匹配,退出 */
    if(NAS_EMM_PLMN_CHK_STAT_INVALID(EMM_MS_DEREG, EMM_SS_DEREG_NO_IMSI))
    {
        NAS_LMM_EMM_PLMN_LOG_WARN("NAS_EMM_MsDrgSsNoImsiMsgSysInfoInd: STATE ERROR!!!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDrgSsNoImsiMsgSysInfoInd_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    /* 如果ATTACH的触发类型是紧急PDN建立引起的普通注册，且缓存的紧急PDN建立请求
       消息有效，则发起紧急注册 */
    pstEsmMsg = (NAS_EMM_ESM_MSG_BUFF_STRU*)(VOS_VOID*)NAS_LMM_GetEmmInfoEsmBuffAddr();
    if ((EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER == NAS_EMM_GLO_AD_GetAttCau())
        && (NAS_EMM_NULL_PTR != pstEsmMsg))
    {
        NAS_LMM_EMM_PLMN_LOG_WARN("NAS_EMM_MsDrgSsNoImsiMsgSysInfoInd: case ESM_ATTACH_FOR_INIT_EMC_BERER");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDrgSsNoImsiMsgSysInfoInd_ENUM,LNAS_EMM_ATTACH_EMC_BEAER);

        /*保存ESM消息*/
        NAS_LMM_MEM_CPY_S(  (VOS_VOID*)NAS_EMM_GLO_AD_GetEsmMsgAddr(),
                            sizeof(NAS_EMM_CN_MSGCON_STRU),
                            &(pstEsmMsg->stEsmMsg),
                            (pstEsmMsg->stEsmMsg.ulEsmMsgSize)+4);

        NAS_EMM_StartEmergencyAttach();

        return NAS_LMM_MSG_HANDLED;
    }

    NAS_EMM_AppSendAttRstDefaultReqType(MMC_LMM_ATT_RSLT_FAILURE);

    return NAS_LMM_MSG_HANDLED;
}
/*lint +e961*/
/*lint +e960*/
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

