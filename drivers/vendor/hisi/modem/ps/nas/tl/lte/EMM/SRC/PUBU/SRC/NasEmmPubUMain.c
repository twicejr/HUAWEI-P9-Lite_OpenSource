/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasEmmPubUMain.c
    Description :
    History     :
      1.  hanlufeng 41410  Draft Enact
      2.  leili 00132387        2009-02-20 问题单BA8D00962
     描述:增加了在REG + REG_WAIT_MRRC_REL_CNF状态下的处理函数
      3.  zhengjunyan 00148421  2010-12-29  在Reg.Normal_Service和TauInit.WtTauCnf
                                            状态下添加对ID_EMM_ERABM_REL_REQ的处理
******************************************************************************/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasEmmPubUInclude.h"
#include    "EmmUeModeInterface.h"
#include    "NasEmmcEmmInterface.h"

#if (FEATURE_LPP == FEATURE_ON)
#include    "LmmLcsInterface.h"
#endif

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASEMMPUBUMAIN_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASEMMPUBUMAIN_C
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
    /*
    以下调用的函数返回值为以下四种
    NAS_LMM_STORE_HIGH_PRIO_MSG       需要缓存的消息返回此值
    NAS_LMM_ERR_CODE_PARA_INVALID     消息内的参数有错返回此值
    NAS_LMM_MSG_DISCARD               收到当前状态下不能处理的消息返回此值
    NAS_LMM_MSG_HANDLED              本模块已经处理了该消息返回此值
    */

/* PUB UT 先注销下述函数 */

/*================== 状态事件函数对照表 ===================================*/
/* EMM_MS_NULL BEGIN ========================================================*/
/*================= EMM_SS_NULL_WAIT_APP_START_REQ ================*/

/*================= EMM_SS_NULL_WAIT_MMC_START_CNF ================*/
NAS_EMM_ACT_STRU    g_astEmmMsNullSsWaitMmcStartCnfTable[] =
{
    /*============= PLMN ==========================================*/
    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_EMMC_EMM_START_CNF,
                    NAS_EMM_MsNullSsWaitMmcStartCnfMsgMmcStartCnf),

    NAS_EMM_ACT_TI_TBL_ITEM(VOS_PID_TIMER,
                    TI_NAS_EMM_WAIT_MMC_START_CNF_TIMER,
                    NAS_EMM_MsNullSsWaitMmcStartCnfMsgTimerExp),


    /*============= ATTACH ========================================*/
    /*============= DETACH ========================================*/
    /*============= TAU ===========================================*/
    /*============= SERVICE =======================================*/
    /*============= GUTI ==========================================*/
    /*============= IDEN ==========================================*/
    /*============= MRRC ==========================================*/
};

/*================= EMM_SS_NULL_WAIT_RRC_START_CNF ================*/
NAS_EMM_ACT_STRU    g_astEmmMsNullSsWaitRrcStartCnfTable[] =
{
    /*============= PLMN ==========================================*/
    NAS_EMM_ACT_TBL_ITEM(PS_PID_ERRC,
                    ID_LRRC_LMM_START_CNF,
                    NAS_EMM_MsNullSsWaitRrcStartCnfMsgRrcStartCnf),

    NAS_EMM_ACT_TI_TBL_ITEM(VOS_PID_TIMER,
                    TI_NAS_EMM_WAIT_RRC_START_CNF_TIMER,
                    NAS_EMM_MsNullSsWaitRrcStartCnfMsgTimerExp),


    /*============= ATTACH ========================================*/
    /*============= DETACH ========================================*/
    /*============= TAU ===========================================*/
    /*============= SERVICE =======================================*/
    /*============= GUTI ==========================================*/
    /*============= IDEN ==========================================*/
    /*============= MRRC ==========================================*/
};

/*================= EMM_SS_NULL_WAIT_MMC_STOP_CNF =================*/
NAS_EMM_ACT_STRU    g_astEmmMsNullSsWaitMmcStopCnfTable[] =
{
    /*============= PLMN ==========================================*/
    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_EMMC_EMM_STOP_CNF,
                    NAS_EMM_MsNullSsWaitMmcStopCnfMsgMmcStopCnf),

    NAS_EMM_ACT_TI_TBL_ITEM(VOS_PID_TIMER,
                    TI_NAS_EMM_WAIT_MMC_STOP_CNF_TIMER,
                    NAS_EMM_MsNullSsWaitMmcStopCnfMsgTimerExp),


    /*============= ATTACH ========================================*/
    /*============= DETACH ========================================*/
    /*============= TAU ===========================================*/
    /*============= SERVICE =======================================*/
    /*============= GUTI ==========================================*/
    /*============= IDEN ==========================================*/
    /*============= MRRC ==========================================*/
};

/*================= EMM_SS_NULL_WAIT_RRC_STOP_CNF =================*/
NAS_EMM_ACT_STRU    g_astEmmMsNullSsWaitRrcStopCnfTable[] =
{
    /*============= PLMN ==========================================*/
    NAS_EMM_ACT_TBL_ITEM(PS_PID_ERRC,
                    ID_LRRC_LMM_POWER_OFF_CNF,
                    NAS_EMM_MsNullSsWaitRrcStopCnfMsgRrcStopCnf),

    NAS_EMM_ACT_TI_TBL_ITEM(VOS_PID_TIMER,
                    TI_NAS_EMM_WAIT_RRC_STOP_CNF_TIMER,
                    NAS_EMM_MsNullSsWaitRrcStopCnfMsgTimerExp),


    /*============= ATTACH ========================================*/
    /*============= DETACH ========================================*/
    /*============= TAU ===========================================*/
    /*============= SERVICE =======================================*/
    /*============= GUTI ==========================================*/
    /*============= IDEN ==========================================*/
    /*============= MRRC ==========================================*/
};

/*================= EMM_SS_NULL_WAIT_SWITCH_OFF =================*/
NAS_EMM_ACT_STRU    g_astEmmMsNullSsWaitSwitchOffTable[] =
{
    /*============= PLMN ==========================================*/
    NAS_EMM_ACT_TBL_ITEM(PS_PID_ERRC,
                    ID_LRRC_LMM_REL_IND,
                    NAS_EMM_MsNullSsWaitSwitchOffMsgRrcRelInd),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_MRRC_CONNECT_FAIL_IND,
                    NAS_EMM_MsNullSsWaitSwitchOffMsgRrcRelInd),

    /*============= ATTACH ========================================*/
    /*============= DETACH ========================================*/
    /*============= TAU ===========================================*/
    /*============= SERVICE =======================================*/
    /*============= GUTI ==========================================*/
    /*============= IDEN ==========================================*/
    /*============= MRRC ==========================================*/
    /*NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_MRRC_DATA_REQ,
                    NAS_EMM_MsNoRrcConnInitSsAllMsgMrrcDataReq),*/


};


/* EMM_MS_DEREG =============================================================*/
/*================= EMM_SS_DEREG_NORMAL_SERVICE ===================*/
NAS_EMM_ACT_STRU    g_astEmmMsDeregSsNormalServiceTable[] =
{
    /*============= PLMN ==========================================*/
    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_EMMC_EMM_PLMN_IND,
                    NAS_EMM_MsNotNullSsAnyStateMsgMmcPlmnInd),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_EMMC_EMM_COVERAGE_LOST_IND,
                    NAS_EMM_MsNotNullSsAnyStateMsgMmcCoverageLostInd),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_EMMC_EMM_SYS_INFO_IND,
                    NAS_EMM_MsDeregSsNormalSrvMsgMmcSysInfoInd),
    /*============= ATTACH ======DETACH============================*/
    NAS_EMM_ACT_TBL_ITEM(WUEPS_PID_MMC,
                    ID_MMC_LMM_ATTACH_REQ,
                    NAS_EMM_MsDrgSsNmlSrvMsgAppAttachReq),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_ESM,
                    ID_EMM_ESM_EST_REQ,
                    NAS_EMM_MsDrgSsNmlSrvMsgEsmEstReq),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_ATTACH_REQ,
                    NAS_EMM_MsDrgSsNmlSrvMsgIntraAttReq),

    /*============= TAU ===========================================*/
    /*============= SERVICE =======================================*/
    /*============= GUTI ==========================================*/
    /*============= IDEN ==========================================*/

    /*============= MRRC ==========================================*/

};

/*================= EMM_SS_DEREG_LIMITED_SERVICE ==================*/
NAS_EMM_ACT_STRU    g_astEmmMsDeregSsLimitServiceTable[] =
{
    /*============= PLMN ==========================================*/
    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_EMMC_EMM_PLMN_IND,
                    NAS_EMM_MsNotNullSsAnyStateMsgMmcPlmnInd),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_EMMC_EMM_COVERAGE_LOST_IND,
                    NAS_EMM_MsNotNullSsAnyStateMsgMmcCoverageLostInd),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_EMMC_EMM_SYS_INFO_IND,
                    NAS_EMM_MsDeregSsLimitSrvMsgMmcSysInfoInd),

    /*============= ATTACH ======DETACH============================*/
    NAS_EMM_ACT_TBL_ITEM(WUEPS_PID_MMC,
                    ID_MMC_LMM_ATTACH_REQ,
                    NAS_EMM_MsDrgSsLimitedSrvMsgAppAttachReq),

    NAS_EMM_ACT_TBL_ITEM(WUEPS_PID_MMC,
                    ID_MMC_LMM_DETACH_REQ,
                    NAS_EMM_MsDrgSsLimitedSrvMsgAppDetachReq),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_ESM,
                    ID_EMM_ESM_EST_REQ,
                    NAS_EMM_MsDrgSsLimitedSrvMsgEsmEstReq),

    /*============= TAU ===========================================*/
    /*============= SERVICE =======================================*/
    /*============= GUTI ==========================================*/
    /*============= IDEN ==========================================*/
    /*============= MRRC ==========================================*/
};

/*================= EMM_SS_DEREG_ATTEMPTING_TO_ATTACH =============*/
NAS_EMM_ACT_STRU    g_astEmmMsDeregSsAttempToAttachTable[] =
{
    /*============= PLMN ==========================================*/
    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_EMMC_EMM_PLMN_IND,
                    NAS_EMM_MsNotNullSsAnyStateMsgMmcPlmnInd),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_EMMC_EMM_COVERAGE_LOST_IND,
                    NAS_EMM_MsNotNullSsAnyStateMsgMmcCoverageLostInd),

    /*============= ATTACH ======DETACH============================*/
    NAS_EMM_ACT_TBL_ITEM(WUEPS_PID_MMC,
                    ID_MMC_LMM_ATTACH_REQ,
                    NAS_EMM_MsDrgSsAttemptToAttMsgAppAttachReq),

    NAS_EMM_ACT_TBL_ITEM(WUEPS_PID_MMC,
                    ID_MMC_LMM_DETACH_REQ,
                    NAS_EMM_MsDrgSsAttemptToAttMsgAppDetachReq),

    NAS_EMM_ACT_TI_TBL_ITEM(VOS_PID_TIMER,
                    TI_NAS_EMM_PTL_T3411,
                    NAS_EMM_MsDrgSsAttemptToAttMsgT3411Exp),

    NAS_EMM_ACT_TI_TBL_ITEM(VOS_PID_TIMER,
                    TI_NAS_EMM_PTL_T3402,
                    NAS_EMM_MsDrgSsAttemptToAttMsgT3402Exp),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                     ID_NAS_LMM_INTRA_EMMC_EMM_SYS_INFO_IND,
                     NAS_EMM_MsDeregSsAttemptToAttachMsgMmcSysInfoInd),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_ESM,
                    ID_EMM_ESM_EST_REQ,
                    NAS_EMM_MsDrgSsAttemptToAttMsgEsmEstReq),

    /*============= TAU ===========================================*/
    /*============= SERVICE =======================================*/
    /*============= GUTI ==========================================*/
    /*============= IDEN ==========================================*/
    /*============= MRRC ==========================================*/

};

/*================= EMM_SS_DEREG_PLMN_SEARCH ======================*/
NAS_EMM_ACT_STRU    g_astEmmMsDeregSsPlmnSearchTable[] =
{
    /*============= PLMN ==========================================*/
    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_EMMC_EMM_PLMN_IND,
                    NAS_EMM_MsNotNullSsAnyStateMsgMmcPlmnInd),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_EMMC_EMM_COVERAGE_LOST_IND,
                    NAS_EMM_MsNotNullSsAnyStateMsgMmcCoverageLostInd),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_EMMC_EMM_SYS_INFO_IND,
                    NAS_EMM_MsDeregSsPlmnSearchMsgMmcSysInfoInd),

    /*============= ATTACH ======DETACH============================*/
    NAS_EMM_ACT_TBL_ITEM(WUEPS_PID_MMC,
                    ID_MMC_LMM_ATTACH_REQ,
                    NAS_EMM_MsDrgSsPlmnSrcMsgAppAttachReq),

    NAS_EMM_ACT_TBL_ITEM(WUEPS_PID_MMC,
                    ID_MMC_LMM_DETACH_REQ,
                    NAS_EMM_MsDrgSsPlmnSrcMsgAppDetachReq),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_ESM,
                    ID_EMM_ESM_EST_REQ,
                    NAS_EMM_MsDrgSsPlmnSrcMsgMsgEsmEstReq),
};

/*================= EMM_SS_DEREG_NO_IMSI ==========================*/
NAS_EMM_ACT_STRU    g_astEmmMsDeregSsNoImsiTable[] =
{
    /*============= PLMN ==========================================*/
    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_EMMC_EMM_PLMN_IND,
                    NAS_EMM_MsDeregSsNoImsiMsgMmcPlmnInd),

    /*============= ATTACH ======DETACH============================*/
    NAS_EMM_ACT_TBL_ITEM(WUEPS_PID_MMC,
                    ID_MMC_LMM_ATTACH_REQ,
                    NAS_EMM_MsDrgSsNoImsiMsgAppAttachReq),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_ERRC,
                    ID_LRRC_LMM_RESUME_IND,
                    NAS_EMM_MsAnySsNoCellAvailMsgRrcRsumeInd),

    /*============= SYSINFO========================================*/
    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_EMMC_EMM_SYS_INFO_IND,
                    NAS_EMM_MsDrgSsNoImsiMsgSysInfoInd),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_ESM,
                    ID_EMM_ESM_EST_REQ,
                    NAS_EMM_MsDrgSsNoImsiMsgEsmEstReq),
};

/*================= EMM_SS_DEREG_ATTACH_NEEDED ====================*/
NAS_EMM_ACT_STRU    g_astEmmMsDeregSsAttachNeededTable[] =
{
    /*============= PLMN ==========================================*/
    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_EMMC_EMM_PLMN_IND,
                    NAS_EMM_MsNotNullSsAnyStateMsgMmcPlmnInd),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_EMMC_EMM_COVERAGE_LOST_IND,
                    NAS_EMM_MsNotNullSsAnyStateMsgMmcCoverageLostInd),

    /*============= ATTACH ======DETACH============================*/
    NAS_EMM_ACT_TBL_ITEM(WUEPS_PID_MMC,
                    ID_MMC_LMM_ATTACH_REQ,
                    NAS_EMM_MsDrgSsAttNeedMsgAppAttachReq),

    NAS_EMM_ACT_TBL_ITEM(WUEPS_PID_MMC,
                    ID_MMC_LMM_DETACH_REQ,
                    NAS_EMM_MsDrgSsAttNeedMsgAppDetachReq),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_ERRC,
                    ID_LRRC_LMM_ACCESS_GRANT_IND,
                    NAS_EMM_MsDeregSsAttachNeededMsgRrcAccessGrantInd),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_EMMC_EMM_SYS_INFO_IND,
                    NAS_EMM_MsDeregSsAttachNeededMsgMmcSysInfoInd),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_ESM,
                    ID_EMM_ESM_EST_REQ,
                    NAS_EMM_MsDrgSsAttachNeededMsgEsmEstReq),

    /*============= TAU ===========================================*/
    /*============= SERVICE =======================================*/
    /*============= GUTI ==========================================*/
    /*============= IDEN ==========================================*/
    /*============= MRRC ==========================================*/
};

/*================= EMM_SS_DEREG_NO_CELL_AVAILABLE ================*/
NAS_EMM_ACT_STRU    g_astEmmMsDeregSsNoCellAvailTable[] =
{
    /*============= PLMN ==========================================*/
    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_EMMC_EMM_PLMN_IND,
                    NAS_EMM_MsNotNullSsAnyStateMsgMmcPlmnInd),


    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_EMMC_EMM_SYS_INFO_IND,
                    NAS_EMM_MsDeregSsNoCellAvailMsgMmcSysInfoInd),

    /*============= ATTACH ======DETACH============================*/
    NAS_EMM_ACT_TBL_ITEM(WUEPS_PID_MMC,
                    ID_MMC_LMM_ATTACH_REQ,
                    NAS_EMM_MsDrgSsNoCellAvailMsgAppAttachReq),

    NAS_EMM_ACT_TBL_ITEM(WUEPS_PID_MMC,
                    ID_MMC_LMM_DETACH_REQ,
                    NAS_EMM_MsDrgSsNoCellAvailMsgAppDetachReq),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_ERRC,
                    ID_LRRC_LMM_RESUME_IND,
                    NAS_EMM_MsAnySsNoCellAvailMsgRrcRsumeInd),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_ESM,
                    ID_EMM_ESM_EST_REQ,
                    NAS_EMM_MsDrgSsNoCellAvailMsgMsgEsmEstReq),

    /*============= TAU ===========================================*/
    /*============= SERVICE =======================================*/
    /*============= GUTI ==========================================*/
    /*============= IDEN ==========================================*/
    /*============= MRRC ==========================================*/
};

/* EMM_MS_REG_INIT ==========================================================*/
/*================= EMM_SS_ATTACH_WAIT_ESM_PDN_RSP =================*/
NAS_EMM_ACT_STRU    g_astEmmMsRegInitSsWaitEsmPdnRspTable[] =
{
    /*============= PLMN ==========================================*/
    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_EMMC_EMM_PLMN_IND,
                    NAS_EMM_MsNotNullSsAnyStateMsgMmcPlmnInd),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_EMMC_EMM_COVERAGE_LOST_IND,
                    NAS_EMM_MsNotNullSsAnyStateMsgMmcCoverageLostInd),

    /*============= ATTACH ======DETACH============================*/
    NAS_EMM_ACT_TBL_ITEM(WUEPS_PID_MMC,
                    ID_MMC_LMM_ATTACH_REQ,
                    NAS_EMM_MsRegInitSsWtEsmPdnRspMsgAppAttachReq),

    NAS_EMM_ACT_TBL_ITEM(WUEPS_PID_MMC,
                    ID_MMC_LMM_DETACH_REQ,
                    NAS_EMM_MsRegInitSsWtEsmPdnRspMsgAppDetachReq),

    NAS_EMM_ACT_CN_TBL_ITEM(PS_PID_ERRC,
                    NAS_EMM_CN_MT_DETACH_REQ_MT,
                    NAS_EMM_MsRegInitMsgCnDetachReq),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_ERRC,
                    ID_LRRC_LMM_REL_IND,
                    NAS_EMM_MsRegInitSsWtEsmPdnRspMsgRrcRelInd),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_ESM,
                    ID_EMM_ESM_PDN_CON_RSP,
                    NAS_EMM_MsRegInitSsWtEsmPdnRspMsgEsmPdnRsp),

    NAS_EMM_ACT_TI_TBL_ITEM(VOS_PID_TIMER,
                    TI_NAS_EMM_WAIT_ESM_PDN_RSP,
                    NAS_EMM_MsRegInitSsWtEsmPdnRspMsgTimerWtEsmRspExp),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_ESM,
                    ID_EMM_ESM_EST_REQ,
                    NAS_EMM_MsRegInitMsgEsmEstReq),

    /*============= TAU ===========================================*/
    /*============= SERVICE =======================================*/
    /*============= GUTI ==========================================*/
    /*============= IDEN ==========================================*/
    /*============= MRRC ==========================================*/
};

/*================= EMM_SS_ATTACH_WAIT_CN_ATTACH_CNF ==============*/
NAS_EMM_ACT_STRU    g_astEmmMsRegInitSsWaitCnAttachCnfTable[] =
{
    /*============= PLMN ==========================================*/
    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_EMMC_EMM_PLMN_IND,
                    NAS_EMM_MsNotNullSsAnyStateMsgMmcPlmnInd),

    /*============= ATTACH ======DETACH============================*/
    NAS_EMM_ACT_TBL_ITEM(WUEPS_PID_MMC,
                    ID_MMC_LMM_ATTACH_REQ,
                    NAS_EMM_MsRegInitSsWtCnAttCnfMsgAppAttachReq),

    NAS_EMM_ACT_TBL_ITEM(WUEPS_PID_MMC,
                    ID_MMC_LMM_DETACH_REQ,
                    NAS_EMM_MsRegInitSsWtCnAttCnfMsgAppDetachReq),

    NAS_EMM_ACT_CN_TBL_ITEM(PS_PID_ERRC,
                    NAS_EMM_CN_MT_ATTACH_ACP,
                    NAS_EMM_MsRegInitSsWtCnAttCnfMsgCnAttachAcp),

    NAS_EMM_ACT_CN_TBL_ITEM(PS_PID_ERRC,
                    NAS_EMM_CN_MT_ATTACH_REJ,
                    NAS_EMM_MsRegInitSsWtCnAttCnfMsgCnAttachReject),

    NAS_EMM_ACT_CN_TBL_ITEM(PS_PID_ERRC,
                    NAS_EMM_CN_MT_DETACH_REQ_MT,
                    NAS_EMM_MsRegInitMsgCnDetachReq),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_EMMC_EMM_SYS_INFO_IND,/*X00148705 处理可能有问题*/
                    NAS_EMM_MsRegInitSsWtCnAttCnfMsgSysInfo),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_MRRC_CONNECT_FAIL_IND,
                    NAS_EMM_MsRegInitSsWtCnAttCnfMsgIntraConncetFailInd),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_ERRC,
                    ID_LRRC_LMM_REL_IND,
                    NAS_EMM_MsRegInitSsWtCnAttCnfMsgRrcRelInd),

    NAS_EMM_ACT_TI_TBL_ITEM(VOS_PID_TIMER,
                    TI_NAS_EMM_T3410,
                    NAS_EMM_MsRegInitSsWtCnAttCnfMsgT3410Exp),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_ESM,
                    ID_EMM_ESM_DATA_REQ,
                    NAS_EMM_MsRegInitSsWaitCnAttachCnfMsgEsmDataReq),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_ESM,
                    ID_EMM_ESM_EST_REQ,
                    NAS_EMM_MsRegInitMsgEsmEstReq),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_TC,
                    ID_EMM_ETC_DATA_REQ,
                    NAS_EMM_MsRegInitSsWaitCnAttachCnfMsgTcDataReq),
    /*============= TAU ===========================================*/
    /*============= SERVICE =======================================*/
    /*============= GUTI ==========================================*/
    /*============= IDEN ==========================================*/
    /*============= AUTH ==========================================*/
    NAS_EMM_ACT_CN_TBL_ITEM(PS_PID_ERRC,
                    NAS_EMM_CN_MT_AUTH_REQ,
                    NAS_EMM_MsAnyStateSsAnyStateMsgCnAuthReq),

    NAS_EMM_ACT_TBL_ITEM(WUEPS_PID_USIM,
                    USIMM_AUTHENTICATION_CNF,
                    NAS_EMM_MsAnyStateSsAnyStateMsgUsimAuthCnf),

    NAS_EMM_ACT_CN_TBL_ITEM(PS_PID_ERRC,
                    NAS_EMM_CN_MT_AUTH_REJ,
                    NAS_EMM_MsRegInitSsWtCnAttCnfMsgAuthRej),

    /*============= MRRC ==========================================*/
    NAS_EMM_ACT_CN_TBL_ITEM(PS_PID_ERRC,
                    NAS_EMM_CN_MT_IDEN_REQ,
                    NAS_EMM_AnyStateMsgIdenReq),

    /*NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_MRRC_DATA_REQ,
                    NAS_EMM_MsNoRrcConnInitSsAllMsgMrrcDataReq),*/
};
/*================= EMM_SS_ATTACH_WAIT_ESM_BEARER_CNF ==============*/
NAS_EMM_ACT_STRU    g_astEmmMsRegInitSsWaitEsmBearerCnfTable[] =
{
    /*============= PLMN ==========================================*/
    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_EMMC_EMM_PLMN_IND,
                    NAS_EMM_MsNotNullSsAnyStateMsgMmcPlmnInd),

    /*============= ATTACH ======DETACH============================*/
    NAS_EMM_ACT_TBL_ITEM(WUEPS_PID_MMC,
                    ID_MMC_LMM_ATTACH_REQ,
                    NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgAppAttachReq),

    NAS_EMM_ACT_TBL_ITEM(WUEPS_PID_MMC,
                    ID_MMC_LMM_DETACH_REQ,
                    NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgAppDetachReq),

    NAS_EMM_ACT_CN_TBL_ITEM(PS_PID_ERRC,
                    NAS_EMM_CN_MT_DETACH_REQ_MT,
                    NAS_EMM_MsRegInitMsgCnDetachReq),
    NAS_EMM_ACT_TBL_ITEM(PS_PID_ESM,
                    ID_EMM_ESM_PDN_CON_SUCC_REQ,
                    NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgEsmBearerCnf),

    NAS_EMM_ACT_TI_TBL_ITEM(VOS_PID_TIMER,
                    TI_NAS_EMM_WAIT_ESM_BEARER_CNF,
                    NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgTimerWtEsmBearerCnfExp),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_EMMC_EMM_SYS_INFO_IND,
                    NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgSysInfo),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_ESM,
                    ID_EMM_ESM_DATA_REQ,
                    NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgEsmDataReq),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_ESM,
                    ID_EMM_ESM_EST_REQ,
                    NAS_EMM_MsRegInitMsgEsmEstReq),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_ERRC,
                    ID_LRRC_LMM_REL_IND,
                    NAS_EMM_EmmMsRegInitSsWaitEsmBearerCnfMsgRrcRelInd),

    /*============= AUTH ==========================================*/
};

/*================= EMM_SS_ATTACH_WAIT_RRC_DATA_REQ_CNF ==============*/
NAS_EMM_ACT_STRU    g_astEmmMsRegInitSsWaitRrcDataCnfTable[] =
{

    /*============= PLMN ==========================================*/

    /*============= ATTACH ======DETACH============================*/
    NAS_EMM_ACT_TBL_ITEM(WUEPS_PID_MMC,
                    ID_MMC_LMM_ATTACH_REQ,
                    NAS_EMM_MsRegInitSsWaitRrcDataCnfMsgAppAttachReq),

    NAS_EMM_ACT_TBL_ITEM(WUEPS_PID_MMC,
                    ID_MMC_LMM_DETACH_REQ,
                    NAS_EMM_EmmMsRegInitSsWaitRrcDataCnfMsgAppDetachReq),

    NAS_EMM_ACT_CN_TBL_ITEM(PS_PID_ERRC,
                    NAS_EMM_CN_MT_DETACH_REQ_MT,
                    NAS_EMM_MsRegInitMsgCnDetachReq),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_EMMC_EMM_SYS_INFO_IND,
                    NAS_EMM_EmmMsRegInitSsWaitRrcDataCnfMsgSysInfo),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_ESM,
                    ID_EMM_ESM_DATA_REQ,
                    NAS_EMM_EmmMsRegInitSsWaitRrcDataCnfMsgEsmDataReq),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_ESM,
                    ID_EMM_ESM_EST_REQ,
                    NAS_EMM_MsRegInitMsgEsmEstReq),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_ERRC,
                    ID_LRRC_LMM_REL_IND,
                    NAS_EMM_EmmMsRegInitSsWaitRrcDataCnfMsgRrcRelInd),

    NAS_EMM_ACT_TI_TBL_ITEM(VOS_PID_TIMER,
                    TI_NAS_EMM_WAIT_RRC_DATA_CNF,
                    NAS_EMM_EmmMsRegInitSsWaitRrcDataCnfMsgTmrRrcDataCnfExp),

    /*NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_MRRC_DATA_REQ,
                    NAS_EMM_MsNoRrcConnInitSsAllMsgMrrcDataReq),*/

    /*============= AUTH ==========================================*/
};

/* EMM_MS_REG ===============================================================*/
/*================= EMM_SS_REG_NORMAL_SERVICE =====================*/
NAS_EMM_ACT_STRU    g_astEmmMsRegSsNormalServiceTable[] =
{
    /*============= PLMN ==========================================*/
    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_EMMC_EMM_PLMN_IND,
                    NAS_EMM_MsNotNullSsAnyStateMsgMmcPlmnInd),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_EMMC_EMM_COVERAGE_LOST_IND,
                    NAS_EMM_MsNotNullSsAnyStateMsgMmcCoverageLostInd),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_ERRC,
                    ID_LRRC_LMM_PAGING_IND,
                    NAS_EMM_MsNotNullSsAnyStateMsgRrcPagingInd),



    /*============= ATTACH ======DETACH============================*/
    NAS_EMM_ACT_TBL_ITEM(WUEPS_PID_MMC,
                    ID_MMC_LMM_ATTACH_REQ,
                    NAS_EMM_MsRegSsNmlSrvMsgAppAttachReq),

    NAS_EMM_ACT_TBL_ITEM(WUEPS_PID_MMC,
                    ID_MMC_LMM_DETACH_REQ,
                    NAS_EMM_MsRegSsNmlSrvMsgAppDetachReq),

    NAS_EMM_ACT_CN_TBL_ITEM(PS_PID_ERRC,
                    NAS_EMM_CN_MT_DETACH_REQ_MT,
                    NAS_EMM_MsRegSsNmlSrvMsgCnDetachReq),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_DETACH_REQ,
                    NAS_EMM_MsRegSsRegNmlSrvMsgIntraDetReq),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_ESM,
                    ID_EMM_ESM_EST_REQ,
                    NAS_EMM_MsRegSsNormalMsgMsgEsmEstReq),

    /*============= TAU ===========================================*/
    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_EMMC_EMM_SYS_INFO_IND,
                    NAS_EMM_MsRegSsNormalMsgSysinfo),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_ERRC,
                    ID_LRRC_LMM_REL_IND,
                    NAS_EMM_MsRegSsNmlSrvMsgRrcRelInd),

    NAS_EMM_ACT_TI_TBL_ITEM(VOS_PID_TIMER,
                    TI_NAS_EMM_PTL_T3411,
                    NAS_EMM_MsRegSsNormalMsgT3411Exp),

    NAS_EMM_ACT_TI_TBL_ITEM(VOS_PID_TIMER,
                    TI_NAS_EMM_PTL_T3412,
                    NAS_EMM_MsRegSsNormalMsgT3412Exp),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_TAU_REQ,
                    NAS_EMM_MsRegSsNormalServiceMsgIntraTauReq),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_ESM,
                    ID_EMM_ESM_BEARER_STATUS_REQ,
                    NAS_EMM_MsRegSsNormalMsgBearerStatusReq),
    /*============= SERVICE =======================================*/
    NAS_EMM_ACT_TBL_ITEM(PS_PID_RABM,
                    ID_EMM_ERABM_REEST_REQ,
                    NAS_EMM_MsRegSsNormalMsgRabmReestReq),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_RABM,
                    ID_EMM_ERABM_REL_REQ,
                    NAS_EMM_MsRegSsNormalMsgRabmRelReq),


    NAS_EMM_ACT_TBL_ITEM(PS_PID_ESM,
                    ID_EMM_ESM_DATA_REQ,
                    NAS_EMM_MsRegSsNormalMsgEsmDataReq),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_TC,
                    ID_EMM_ETC_DATA_REQ,
                    NAS_EMM_MsRegSsNormalMsgTcDataReq),

    NAS_EMM_ACT_TBL_ITEM(WUEPS_PID_SMS,
                    ID_SMS_LMM_EST_REQ,
                    NAS_EMM_MsRegSsNormalMsgSmsEstReq),
    NAS_EMM_ACT_TBL_ITEM(WUEPS_PID_MM,
                    ID_MM_LMM_CSFB_SERVICE_START_NOTIFY,
                    NAS_EMM_MsRegSsNormalMsgMmCsfbSerStartNotify),
    #if (FEATURE_LPP == FEATURE_ON)
    NAS_EMM_ACT_TBL_ITEM(PS_PID_LPP,
                    ID_LPP_LMM_EST_REQ,
                    NAS_EMM_MsRegSsNormalMsgLppEstReq),

    /* LCS模块PID变更为WUEPS_PID_LCS */
    NAS_EMM_ACT_TBL_ITEM(WUEPS_PID_LCS,
                    ID_LCS_LMM_EST_REQ,
                    NAS_EMM_MsRegSsNormalMsgLcsEstReq),
   #endif

    /*============= GUTI ==========================================*/
    /*============= IDEN ==========================================*/
    /*============= AUTH ==========================================*/
    NAS_EMM_ACT_CN_TBL_ITEM(PS_PID_ERRC,
                    NAS_EMM_CN_MT_AUTH_REQ,
                    NAS_EMM_MsAnyStateSsAnyStateMsgCnAuthReq),

    NAS_EMM_ACT_TBL_ITEM(WUEPS_PID_USIM,
                    USIMM_AUTHENTICATION_CNF,
                    NAS_EMM_MsAnyStateSsAnyStateMsgUsimAuthCnf),

    NAS_EMM_ACT_CN_TBL_ITEM(PS_PID_ERRC,
                    NAS_EMM_CN_MT_AUTH_REJ,
                    NAS_EMM_MsRegSsNmlSrvMsgAuthRej),

    NAS_EMM_ACT_TI_TBL_ITEM(VOS_PID_TIMER,
                    TI_NAS_EMM_T3418,
                    NAS_EMM_MsRegSsNorOrUpdateMmMsgT3418Exp),

    NAS_EMM_ACT_TI_TBL_ITEM(VOS_PID_TIMER,
                    TI_NAS_EMM_T3420,
                    NAS_EMM_MsRegSsNorOrUpdateMmMsgT3420Exp),

    /*============= AUTH ==========================================*/
    /*============= MRRC ==========================================*/
    NAS_EMM_ACT_CN_TBL_ITEM(PS_PID_ERRC,
                    NAS_EMM_CN_MT_GUTI_CMD,
                    NAS_EMM_AnyStateMsgGtReCmd),

    NAS_EMM_ACT_CN_TBL_ITEM(PS_PID_ERRC,
                    NAS_EMM_CN_MT_IDEN_REQ,
                    NAS_EMM_AnyStateMsgIdenReq),

    /*NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_MRRC_DATA_REQ,
                    NAS_EMM_MsNoRrcConnInitSsAllMsgMrrcDataReq),*/

};

/*================= EMM_SS_REG_ATTEMPTING_TO_UPDATE ===============*/
NAS_EMM_ACT_STRU    g_astEmmMsRegSsAttemptToUpdateTable[] =
{
    /*============= PLMN ==========================================*/
    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_EMMC_EMM_PLMN_IND,
                    NAS_EMM_MsNotNullSsAnyStateMsgMmcPlmnInd),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_EMMC_EMM_COVERAGE_LOST_IND,
                    NAS_EMM_MsNotNullSsAnyStateMsgMmcCoverageLostInd),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_ERRC,
                    ID_LRRC_LMM_PAGING_IND,
                    NAS_EMM_MsNotNullSsAnyStateMsgRrcPagingInd),
    /*============= ATTACH ======DETACH============================*/
    NAS_EMM_ACT_TBL_ITEM(WUEPS_PID_MMC,
                    ID_MMC_LMM_ATTACH_REQ,
                    NAS_EMM_MsRegSsAtmpToUpdMsgAppAttachReq),

    NAS_EMM_ACT_TBL_ITEM(WUEPS_PID_MMC,
                    ID_MMC_LMM_DETACH_REQ,
                    NAS_EMM_MsRegSsAtmpToUpdMsgAppDetachReq),

    /*============= TAU ===========================================*/
    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_EMMC_EMM_SYS_INFO_IND,
                    NAS_EMM_MsRegSsAtpUpdataMsgSysinfo),

    NAS_EMM_ACT_TI_TBL_ITEM(VOS_PID_TIMER,
                    TI_NAS_EMM_PTL_T3411,
                    NAS_EMM_MsRegSsAtpUpdataMsgT3411Exp),

    NAS_EMM_ACT_TI_TBL_ITEM(VOS_PID_TIMER,
                    TI_NAS_EMM_PTL_T3402,
                    NAS_EMM_MsRegSsAtpUpdataMsgT3402Exp),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_TAU_REQ,
                    NAS_EMM_MsRegSsSomeStatusMsgIntraTauReq),
    NAS_EMM_ACT_TBL_ITEM(PS_PID_ESM,
                    ID_EMM_ESM_DATA_REQ,
                    NAS_EMM_MsRegSsSomeStateMsgEsmDataReq),
    NAS_EMM_ACT_TI_TBL_ITEM(VOS_PID_TIMER,
                    TI_NAS_EMM_PTL_T3346,
                    NAS_EMM_MsRegSsAtpUpdataMsgT3346Exp),
    /*============= SERVICE =======================================*/
/*  全编译时此函数未定义
    NAS_EMM_ACT_TBL_ITEM(PS_PID_RABM,//X00148705 处理可能有问题
                    ID_EMM_ERABM_REEST_REQ,
                    NAS_EMM_MsRegSsAtpUpdataMsgRabmReestReq),
*/
    /*============= GUTI ==========================================*/
    /*============= IDEN ==========================================*/
    /*============= AUTH ==========================================*/
};

/*================= EMM_SS_REG_LIMITED_SERVICE ====================*/
NAS_EMM_ACT_STRU    g_astEmmMsRegSsLimitServiceTable[] =
{
    /*============= PLMN ==========================================*/
    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_EMMC_EMM_PLMN_IND,
                    NAS_EMM_MsNotNullSsAnyStateMsgMmcPlmnInd),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_EMMC_EMM_COVERAGE_LOST_IND,
                    NAS_EMM_MsNotNullSsAnyStateMsgMmcCoverageLostInd),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_ERRC,
                    ID_LRRC_LMM_PAGING_IND,
                    NAS_EMM_MsNotNullSsAnyStateMsgRrcPagingInd),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_ERRC,
                        ID_LRRC_LMM_REL_IND,
                        NAS_EMM_MsRegSsLimitedSrvMsgRrcRelInd),



    /*============= ATTACH ======DETACH============================*/
    NAS_EMM_ACT_TBL_ITEM(WUEPS_PID_MMC,
                    ID_MMC_LMM_ATTACH_REQ,
                    NAS_EMM_MsRegSsLimitedSrvMsgAppAttachReq),

    NAS_EMM_ACT_TBL_ITEM(WUEPS_PID_MMC,
                    ID_MMC_LMM_DETACH_REQ,
                    NAS_EMM_MsRegSsLimitedSrvMsgAppDetachReq),
    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_DETACH_REQ,
                    NAS_EMM_MsRegSsLimitedSrvMsgIntraDetReq),

    NAS_EMM_ACT_CN_TBL_ITEM(PS_PID_ERRC,
                    NAS_EMM_CN_MT_DETACH_REQ_MT,
                    NAS_EMM_MsRegSsLimitedSrvMsgCnDetachReq),
    NAS_EMM_ACT_TBL_ITEM(PS_PID_ESM,
                    ID_EMM_ESM_DATA_REQ,
                    NAS_EMM_MsRegSsLimitedSrvMsgEsmDataReq),

    /*============= TAU ===========================================*/
    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_EMMC_EMM_SYS_INFO_IND,
                    NAS_EMM_MsRegSsLimitSRMsgSysinfo),

    NAS_EMM_ACT_TI_TBL_ITEM(VOS_PID_TIMER,
                    TI_NAS_EMM_PTL_T3412,
                    NAS_EMM_MsRegSsAnyStatusMsgT3412Exp),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_TAU_REQ,
                    NAS_EMM_MsRegSsSomeStatusMsgIntraTauReq),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_ESM,
                    ID_EMM_ESM_BEARER_STATUS_REQ,
                    NAS_EMM_MsRegSsSomeStateMsgBearerStatusReq),
    /*============= SERVICE =======================================*/
    NAS_EMM_ACT_TBL_ITEM(PS_PID_RABM,
                    ID_EMM_ERABM_REEST_REQ,
                    NAS_EMM_MsRegSsLimitedSrvMsgRabmReestReq),

     NAS_EMM_ACT_TBL_ITEM(PS_PID_RABM,
                    ID_EMM_ERABM_REL_REQ,
                    NAS_EMM_MsRegSsLimitedSrvMsgRabmRelReq),

    /*============= GUTI ==========================================*/
    /*============= IDEN ==========================================*/
    /*============= AUTH ==========================================*/
    NAS_EMM_ACT_CN_TBL_ITEM(PS_PID_ERRC,
                    NAS_EMM_CN_MT_AUTH_REQ,
                    NAS_EMM_MsAnyStateSsAnyStateMsgCnAuthReq),

    NAS_EMM_ACT_TBL_ITEM(WUEPS_PID_USIM,
                    USIMM_AUTHENTICATION_CNF,
                    NAS_EMM_MsAnyStateSsAnyStateMsgUsimAuthCnf),

    NAS_EMM_ACT_CN_TBL_ITEM(PS_PID_ERRC,
                    NAS_EMM_CN_MT_AUTH_REJ,
                    NAS_EMM_MsRegSsLimitedSrvMsgAuthRej),

    /*============= AUTH ==========================================*/
    /*============= MRRC ==========================================*/
    NAS_EMM_ACT_CN_TBL_ITEM(PS_PID_ERRC,
                    NAS_EMM_CN_MT_GUTI_CMD,
                    NAS_EMM_AnyStateMsgGtReCmd),

    NAS_EMM_ACT_CN_TBL_ITEM(PS_PID_ERRC,
                    NAS_EMM_CN_MT_IDEN_REQ,
                    NAS_EMM_AnyStateMsgIdenReq),
};

/*================= EMM_SS_REG_PLMN_SEARCH ========================*/
NAS_EMM_ACT_STRU    g_astEmmMsRegSsPlmnSearchTable[] =
{
    /*============= PLMN ==========================================*/
    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_EMMC_EMM_PLMN_IND,
                    NAS_EMM_MsNotNullSsAnyStateMsgMmcPlmnInd),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_EMMC_EMM_COVERAGE_LOST_IND,
                    NAS_EMM_MsNotNullSsAnyStateMsgMmcCoverageLostInd),


    /*============= ATTACH ======DETACH============================*/
    NAS_EMM_ACT_TBL_ITEM(WUEPS_PID_MMC,
                    ID_MMC_LMM_ATTACH_REQ,
                    NAS_EMM_MsRegSsPlmnSrcMsgAppAttachReq),

    NAS_EMM_ACT_TBL_ITEM(WUEPS_PID_MMC,
                    ID_MMC_LMM_DETACH_REQ,
                    NAS_EMM_MsRegSsPlmnSrcMsgAppDetachReq),

    /*============= TAU ===========================================*/
    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_EMMC_EMM_SYS_INFO_IND,
                    NAS_EMM_MsRegSsPLMNSearchMsgSysinfo),

    NAS_EMM_ACT_TI_TBL_ITEM(VOS_PID_TIMER,
                    TI_NAS_EMM_PTL_T3412,
                    NAS_EMM_MsRegSsAnyStatusMsgT3412Exp),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_TAU_REQ,
                    NAS_EMM_MsRegSsSomeStatusMsgIntraTauReq),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_ESM,
                    ID_EMM_ESM_BEARER_STATUS_REQ,
                    NAS_EMM_MsRegSsSomeStateMsgBearerStatusReq),
    /*============= SERVICE =======================================*/
    /*============= GUTI ==========================================*/
    /*============= IDEN ==========================================*/

    /*============= AUTH ==========================================*/

    /*============= MRRC ==========================================*/

};

/*================= EMM_SS_REG_WAIT_ACCESS_GRANT_IND ======================*/
NAS_EMM_ACT_STRU    g_astEmmMsRegSsWaitAccessGrantIndTable[] =
{
    /*============= PLMN ==========================================*/
    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_EMMC_EMM_PLMN_IND,
                    NAS_EMM_MsNotNullSsAnyStateMsgMmcPlmnInd),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_EMMC_EMM_COVERAGE_LOST_IND,
                    NAS_EMM_MsNotNullSsAnyStateMsgMmcCoverageLostInd),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_ERRC,
                    ID_LRRC_LMM_PAGING_IND,
                    NAS_EMM_MsNotNullSsAnyStateMsgRrcPagingInd),
    /*============= ATTACH ======DETACH============================*/
    NAS_EMM_ACT_TBL_ITEM(WUEPS_PID_MMC,
                    ID_MMC_LMM_ATTACH_REQ,
                    NAS_EMM_MsRegSsWaitAccessGrantIndMsgAppAttachReq),

    NAS_EMM_ACT_TBL_ITEM(WUEPS_PID_MMC,
                    ID_MMC_LMM_DETACH_REQ,
                    NAS_EMM_MsRegSsWaitAccessGrantIndMsgAppDetachReq),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_ERRC,
                    ID_LRRC_LMM_ACCESS_GRANT_IND,
                    NAS_EMM_MsRegSsWaitAccessGrantIndMsgRrcGrantInd),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_EMMC_EMM_SYS_INFO_IND,
                    NAS_EMM_MsRegSsWaitAccessGrantIndMsgSysinfoInd),


    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_TAU_REQ,
                    NAS_EMM_MsRegSsWaitAccessGrantIndMsgIntraTauReq),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_ESM,
                    ID_EMM_ESM_BEARER_STATUS_REQ,
                    NAS_EMM_MsRegSsWaitAccessGrantIndMsgBearerStatusReq),

    NAS_EMM_ACT_TI_TBL_ITEM(VOS_PID_TIMER,
                    TI_NAS_EMM_PTL_T3412,
                    NAS_EMM_MsRegSsWaitAccessGrantIndMsgT3412Exp),

    NAS_EMM_ACT_TI_TBL_ITEM(VOS_PID_TIMER,
                    TI_NAS_EMM_PTL_T3411,
                    NAS_EMM_MsRegSsWaitAccessGrantIndMsgT3411Exp),

    NAS_EMM_ACT_TBL_ITEM(WUEPS_PID_MM,
                    ID_MM_LMM_CSFB_SERVICE_START_NOTIFY,
                    NAS_EMM_MsRegSsWaitAccessGrantIndMsgMmCsfbSerStartNotify),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_ESM,
                    ID_EMM_ESM_DATA_REQ,
                    NAS_EMM_MsRegSsSomeStateMsgEsmDataReq),

    /*============= GUTI ==========================================*/
    /*============= IDEN ==========================================*/

    /* liuwenyu 143951 20081225 begin 增加Auth,SMC处理*/
    /*============= AUTH ==========================================*/
};

/*================= EMM_SS_REG_NO_CELL_AVAILABLE ==================*/
NAS_EMM_ACT_STRU    g_astEmmMsRegSsNoCellAvailTable[] =
{
    /*============= PLMN ==========================================*/
    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_EMMC_EMM_PLMN_IND,
                    NAS_EMM_MsNotNullSsAnyStateMsgMmcPlmnInd),

    /*============= ATTACH ======DETACH============================*/
    NAS_EMM_ACT_TBL_ITEM(WUEPS_PID_MMC,
                    ID_MMC_LMM_ATTACH_REQ,
                    NAS_EMM_MsRegSsNoCellAvailMsgAppAttachReq),

    NAS_EMM_ACT_TBL_ITEM(WUEPS_PID_MMC,
                    ID_MMC_LMM_DETACH_REQ,
                    NAS_EMM_MsRegSsNoCellAvailMsgAppDetachReq),

    /*============= TAU ===========================================*/
    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_EMMC_EMM_SYS_INFO_IND,
                    NAS_EMM_MsRegSsNocellMsgSysinfo),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_TAU_REQ,
                    NAS_EMM_MsRegSsSomeStatusMsgIntraTauReq),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_ESM,
                    ID_EMM_ESM_BEARER_STATUS_REQ,
                    NAS_EMM_MsRegSsSomeStateMsgBearerStatusReq),

    NAS_EMM_ACT_TI_TBL_ITEM(VOS_PID_TIMER,
                    TI_NAS_EMM_PTL_T3412,
                    NAS_EMM_MsRegSsNoVailableCellMsgT3412Exp),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_ERRC,
                    ID_LRRC_LMM_RESUME_IND,
                    NAS_EMM_MsAnySsNoCellAvailMsgRrcRsumeInd),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_ERRC,
                    ID_LRRC_LMM_SECU_PARA_IND,
                    NAS_EMM_MsRegSsNoCellAvailMsgRrcSecuParaInd),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_ERRC,
                    ID_LRRC_LMM_REL_IND,
                    NAS_EMM_MsRegSsNoCellAvailMsgRrcRelInd),

    /*============= SERVICE =======================================*/
    /*============= GUTI ==========================================*/
    /*============= IDEN ==========================================*/
    /*============= MRRC ==========================================*/

    /*============= AUTH ==========================================*/
};

/*================= EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM ==================*/
NAS_EMM_ACT_STRU    g_astEmmMsRegSsRegAttemptingToUpdateMMTable[] =
{
    /*============= PLMN ==========================================*/
    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_EMMC_EMM_PLMN_IND,
                    NAS_EMM_MsRegSsRegAttemptUpdateMmMsgMmcPlmnInd),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_EMMC_EMM_COVERAGE_LOST_IND,
                    NAS_EMM_MsRegSsRegAttemptUpdateMmMsgMmcCoverageLostInd),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_ERRC,
                    ID_LRRC_LMM_PAGING_IND,
                    NAS_EMM_MsNotNullSsAnyStateMsgRrcPagingInd),



    /*============= ATTACH ======DETACH============================*/
    NAS_EMM_ACT_TBL_ITEM(WUEPS_PID_MMC,
                    ID_MMC_LMM_ATTACH_REQ,
                    NAS_EMM_MsRegSsRegAttemptUpdateMmMsgAppAttachReq),

    NAS_EMM_ACT_TBL_ITEM(WUEPS_PID_MMC,
                    ID_MMC_LMM_DETACH_REQ,
                    NAS_EMM_MsRegSsRegAttemptUpdateMmMsgAppDetachReq),

    NAS_EMM_ACT_CN_TBL_ITEM(PS_PID_ERRC,
                    NAS_EMM_CN_MT_DETACH_REQ_MT,
                    NAS_EMM_MsRegSsRegAttemptUpdateMmMsgCnDetachReq),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_DETACH_REQ,
                    NAS_EMM_MsRegSsRegAttemptUpdateMmMsgIntraDetReq),/* 需要处理，联合TAU打断DETACH，结果值为TA UPDATED ONLY，原因值为16,17,22 */

    NAS_EMM_ACT_TBL_ITEM(PS_PID_ESM,
                    ID_EMM_ESM_EST_REQ,
                    NAS_EMM_MsRegSsRegAttemptUpdateMmMsgEsmEstReq),

    /*============= TAU ===========================================*/
    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_EMMC_EMM_SYS_INFO_IND,
                    NAS_EMM_MsRegSsRegAttemptUpdateMmMsgSysinfo),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_ERRC,
                    ID_LRRC_LMM_REL_IND,
                    NAS_EMM_MsRegSsRegAttemptUpdateMmMsgRrcRelInd),

    NAS_EMM_ACT_TI_TBL_ITEM(VOS_PID_TIMER,
                    TI_NAS_EMM_PTL_T3411,
                    NAS_EMM_MsRegSsRegAttemptUpdateMmMsgT3411Exp),

    NAS_EMM_ACT_TI_TBL_ITEM(VOS_PID_TIMER,
                    TI_NAS_EMM_PTL_T3402,
                    NAS_EMM_MsRegSsRegAttemptUpdateMmMsgT3402Exp),

    NAS_EMM_ACT_TI_TBL_ITEM(VOS_PID_TIMER,
                    TI_NAS_EMM_PTL_T3412,
                    NAS_EMM_MsRegSsRegAttemptUpdateMmMsgT3412Exp),

    /*NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_TAU_REQ,
                    NAS_EMM_MsRegSsRegAttemptUpdateMmMsgIntraTauReq),*/

    NAS_EMM_ACT_TBL_ITEM(PS_PID_ESM,
                    ID_EMM_ESM_BEARER_STATUS_REQ,
                    NAS_EMM_MsRegSsRegAttemptUpdateMmMsgBearerStatusReq),

    /*============= SERVICE =======================================*/
    NAS_EMM_ACT_TBL_ITEM(PS_PID_RABM,
                    ID_EMM_ERABM_REEST_REQ,
                    NAS_EMM_MsRegSsRegAttemptUpdateMmMsgRabmReestReq),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_RABM,
                    ID_EMM_ERABM_REL_REQ,
                    NAS_EMM_MsRegSsRegAttemptUpdateMmMsgRabmRelReq),


    NAS_EMM_ACT_TBL_ITEM(PS_PID_ESM,
                    ID_EMM_ESM_DATA_REQ,
                    NAS_EMM_MsRegSsRegAttemptUpdateMmMsgEsmDataReq),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_TC,
                    ID_EMM_ETC_DATA_REQ,
                    NAS_EMM_MsRegSsRegAttemptUpdateMmMsgTcDataReq),
    /* 解决Reg Update MM下不处理CS Paging问题 */
    NAS_EMM_ACT_TBL_ITEM(WUEPS_PID_MM,
                    ID_MM_LMM_CSFB_SERVICE_START_NOTIFY,
                    NAS_EMM_MsRegSsAttempToUpdateMmMsgMmCsfbSerStartNotify),

    #if (FEATURE_LPP == FEATURE_ON)
    NAS_EMM_ACT_TBL_ITEM(PS_PID_LPP,
                    ID_LPP_LMM_EST_REQ,
                    NAS_EMM_MsRegSsRegAttemptUpdateMmMsgLppEstReq),

    /* LCS模块PID变更为WUEPS_PID_LCS */
    NAS_EMM_ACT_TBL_ITEM(WUEPS_PID_LCS,
                    ID_LCS_LMM_EST_REQ,
                    NAS_EMM_MsRegSsRegAttemptUpdateMmMsgLcsEstReq),
   #endif
    /*============= GUTI ==========================================*/
    /*============= IDEN ==========================================*/
    /*============= AUTH ==========================================*/
    NAS_EMM_ACT_CN_TBL_ITEM(PS_PID_ERRC,
                    NAS_EMM_CN_MT_AUTH_REQ,
                    NAS_EMM_MsAnyStateSsAnyStateMsgCnAuthReq),

    NAS_EMM_ACT_TBL_ITEM(WUEPS_PID_USIM,
                    USIMM_AUTHENTICATION_CNF,
                    NAS_EMM_MsAnyStateSsAnyStateMsgUsimAuthCnf),

    NAS_EMM_ACT_CN_TBL_ITEM(PS_PID_ERRC,
                    NAS_EMM_CN_MT_AUTH_REJ,
                    NAS_EMM_MsRegSsRegAttemptUpdateMmMsgAuthRej),

    NAS_EMM_ACT_TI_TBL_ITEM(VOS_PID_TIMER,
                    TI_NAS_EMM_T3418,
                    NAS_EMM_MsRegSsNorOrUpdateMmMsgT3418Exp),

    NAS_EMM_ACT_TI_TBL_ITEM(VOS_PID_TIMER,
                    TI_NAS_EMM_T3420,
                    NAS_EMM_MsRegSsNorOrUpdateMmMsgT3420Exp),

    /*============= AUTH ==========================================*/
    /*============= MRRC ==========================================*/
    NAS_EMM_ACT_CN_TBL_ITEM(PS_PID_ERRC,
                    NAS_EMM_CN_MT_GUTI_CMD,
                    NAS_EMM_AnyStateMsgGtReCmd),

    NAS_EMM_ACT_CN_TBL_ITEM(PS_PID_ERRC,
                    NAS_EMM_CN_MT_IDEN_REQ,
                    NAS_EMM_AnyStateMsgIdenReq),

    /*NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_MRRC_DATA_REQ,
                    NAS_EMM_MsNoRrcConnInitSsAllMsgMrrcDataReq),*/
};

/*================= EMM_SS_REG_IMSI_DETACH_WATI_CN_DETACH_CNF ==================*/
NAS_EMM_ACT_STRU    g_astEmmMsRegSsRegImsiDetachWaitCnDetachCnfTable[] =
{
    /*============= PLMN ==========================================*/
    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_EMMC_EMM_PLMN_IND,
                    NAS_EMM_MsNotNullSsAnyStateMsgMmcPlmnInd),

    NAS_EMM_ACT_CN_TBL_ITEM(PS_PID_ERRC,
                    NAS_EMM_CN_MT_DETACH_REQ_MT,
                    NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgCnDetachReq),

    NAS_EMM_ACT_CN_TBL_ITEM(PS_PID_ERRC,
                    NAS_EMM_CN_MT_DETACH_ACP_MO,
                    NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgCnDetachAcp),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_ERRC,
                    ID_LRRC_LMM_REL_IND,
                    NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgRrcRelInd),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_MRRC_CONNECT_FAIL_IND,
                    NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgIntraConnectFailInd),

    NAS_EMM_ACT_TI_TBL_ITEM(VOS_PID_TIMER,
                    TI_NAS_EMM_T3421,
                    NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgT3421Exp),

    /*============= TAU ===========================================*/
    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_EMMC_EMM_SYS_INFO_IND,
                    NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgSysinfo),

    /*============= SERVICE =======================================*/
    NAS_EMM_ACT_TBL_ITEM(PS_PID_RABM,
                    ID_EMM_ERABM_REL_REQ,
                    NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgRabmRelReq),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_ESM,
                    ID_EMM_ESM_DATA_REQ,
                    NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgEsmDataReq),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_TC,
                    ID_EMM_ETC_DATA_REQ,
                    NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgTcDataReq),

    /*============= GUTI ==========================================*/
    NAS_EMM_ACT_CN_TBL_ITEM(PS_PID_ERRC,
                    NAS_EMM_CN_MT_GUTI_CMD,
                    NAS_EMM_AnyStateMsgGtReCmd),

    /*============= IDEN ==========================================*/
    NAS_EMM_ACT_CN_TBL_ITEM(PS_PID_ERRC,
                    NAS_EMM_CN_MT_IDEN_REQ,
                    NAS_EMM_AnyStateMsgIdenReq),

    /*============= MRRC ==========================================*/
    /*NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_MRRC_DATA_REQ,
                    NAS_EMM_MsNoRrcConnInitSsAllMsgMrrcDataReq),*/

    /*============= AUTH ==========================================*/
    NAS_EMM_ACT_CN_TBL_ITEM(PS_PID_ERRC,
                    NAS_EMM_CN_MT_AUTH_REQ,
                    NAS_EMM_MsAnyStateSsAnyStateMsgCnAuthReq),

    NAS_EMM_ACT_TBL_ITEM(WUEPS_PID_USIM,
                    USIMM_AUTHENTICATION_CNF,
                    NAS_EMM_MsAnyStateSsAnyStateMsgUsimAuthCnf),

    NAS_EMM_ACT_CN_TBL_ITEM(PS_PID_ERRC,
                    NAS_EMM_CN_MT_AUTH_REJ,
                    NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgAuthRej),

    NAS_EMM_ACT_TBL_ITEM(WUEPS_PID_MMC,
                    ID_MMC_LMM_ATTACH_REQ,
                    NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgAppAttachReq),
};


/* EMM_MS_SUSPEND =================================================*/
/*================= EMM_SS_SUSPEND_RRCORI_WAIT_OTHER_SUSPEND ===========*/

NAS_EMM_ACT_STRU    g_astEmmMsSuspendSsRrcOriWaitOtherSusPendTable[] =
{
    /*============= ESM ==========================================*/
    NAS_EMM_ACT_TBL_ITEM(PS_PID_ESM,
                    ID_EMM_ESM_SUSPEND_RSP,
                    NAS_EMM_MsSuspendSsRrcOriWaitOtherMsgSusRsp),

    /*============= ERABM =======================================*/
    NAS_EMM_ACT_TBL_ITEM(PS_PID_RABM,
                    ID_EMM_ERABM_SUSPEND_RSP,
                     NAS_EMM_MsSuspendSsRrcOriWaitOtherMsgSusRsp),

    /*============= MMC =======================================*/
    NAS_EMM_ACT_TBL_ITEM(WUEPS_PID_MMC,
                    ID_MMC_LMM_SUSPEND_REL_REQ,
                    NAS_EMM_MsSuspendSsRrcOriWaitOtherMsgMmcSuspendRelReq),

    NAS_EMM_ACT_TBL_ITEM(WUEPS_PID_MMC,
                    ID_MMC_LMM_DETACH_REQ,
                    NAS_EMM_MsSuspendSsRrcOriWaitOtherMsgMmcDetachReq),

    /*============= LRRC ==========================================*/
    NAS_EMM_ACT_TBL_ITEM(PS_PID_ERRC,
                    ID_LRRC_LMM_ACCESS_GRANT_IND,
                    NAS_EMM_MsSuspendSsRrcOriMsgRrcAccessGrantInd),

    /*============= TIMER =======================================*/
    NAS_EMM_ACT_TI_TBL_ITEM(VOS_PID_TIMER,
                     TI_NAS_EMM_RRCORI_WAIT_OTHER_SUSPEND_RSP_TIMER,
                     NAS_EMM_MsSuspendSsWaitOtherMsgTimerExp),

    NAS_EMM_ACT_TI_TBL_ITEM(VOS_PID_TIMER,
                    TI_NAS_EMM_PTL_T3412,
                    NAS_EMM_MsSuspendSsAnyMsgT3412Exp),
    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_TAU_REQ,
                    NAS_EMM_MsSuspendSsSomeStatusMsgIntraTauReq),
};

/* EMM_MS_SUSPEND =================================================*/
/*================= EMM_SS_SUSPEND_RRCORI_WAIT_MMC_SUSPEND ===========*/

NAS_EMM_ACT_STRU    g_astEmmMsSuspendSsRrcOriWaitMmcSusPendTable[] =
{
    /*============= MMC ==========================================*/
    NAS_EMM_ACT_TBL_ITEM(WUEPS_PID_MMC,
                    ID_MMC_LMM_SUSPEND_RSP,
                    NAS_EMM_MsSuspendSsRrcOriWaitMmcSuspendMmcSusRsp),

    /*============= LRRC ==========================================*/
    NAS_EMM_ACT_TBL_ITEM(PS_PID_ERRC,
                    ID_LRRC_LMM_ACCESS_GRANT_IND,
                    NAS_EMM_MsSuspendSsRrcOriMsgRrcAccessGrantInd),

    /*============= TIMER =======================================*/
    NAS_EMM_ACT_TI_TBL_ITEM(VOS_PID_TIMER,
                     TI_NAS_EMM_RRCORI_WAIT_OTHER_SUSPEND_RSP_TIMER,
                     NAS_EMM_SsRrcOriWaitMmcSuspenTimerExp),

    NAS_EMM_ACT_TI_TBL_ITEM(VOS_PID_TIMER,
                    TI_NAS_EMM_PTL_T3412,
                    NAS_EMM_MsSuspendSsAnyMsgT3412Exp),
    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_TAU_REQ,
                    NAS_EMM_MsSuspendSsSomeStatusMsgIntraTauReq),
};

/* EMM_MS_SUSPEND =================================================*/
/*================= EMM_SS_SUSPEND_MMCORI_WAIT_OTHER_SUSPEND ===========*/

NAS_EMM_ACT_STRU    g_astEmmMsSuspendSsMmcOriWaitOtherSusPendTable[] =
{
    /*============= ESM ==========================================*/
    NAS_EMM_ACT_TBL_ITEM(PS_PID_ESM,
                    ID_EMM_ESM_SUSPEND_RSP,
                    NAS_EMM_MsSuspendSsMmcOriWaitOtherMsgSusRsp),

    /*============= ERABM =======================================*/
    NAS_EMM_ACT_TBL_ITEM(PS_PID_RABM,
                     ID_EMM_ERABM_SUSPEND_RSP,
                     NAS_EMM_MsSuspendSsMmcOriWaitOtherMsgSusRsp),

    /*============= MMC =======================================*/
    NAS_EMM_ACT_TBL_ITEM(WUEPS_PID_MMC,
                     ID_MMC_LMM_DETACH_REQ,
                     NAS_EMM_MsSuspendSsMmcOrSyscfgOriWaitOtherMsgMmcDetachReq),

    /*============= LRRC =======================================*/
    NAS_EMM_ACT_TBL_ITEM(PS_PID_ERRC,
                     ID_LRRC_LMM_SUSPEND_CNF,
                     NAS_EMM_MsSuspendSsMmcOriWaitOtherMsgSusRsp),

    /*============= TIMER =======================================*/
    NAS_EMM_ACT_TI_TBL_ITEM(VOS_PID_TIMER,
                    TI_NAS_EMM_MMCORI_WAIT_OTHER_SUSPEND_RSP_TIMER,
                    NAS_EMM_MsSuspendSsWaitOtherMsgTimerExp),

    NAS_EMM_ACT_TI_TBL_ITEM(VOS_PID_TIMER,
                    TI_NAS_EMM_PTL_T3412,
                    NAS_EMM_MsSuspendSsAnyMsgT3412Exp),
    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_TAU_REQ,
                    NAS_EMM_MsSuspendSsSomeStatusMsgIntraTauReq),
};

/* EMM_MS_SUSPEND =================================================*/
/*================= EMM_SS_SUSPEND_WAIT_END ================*/

NAS_EMM_ACT_STRU    g_astEmmMsSuspendSsWaitEndTable[] =
{
    /*============= MMC ==========================================*/
    NAS_EMM_ACT_TBL_ITEM(WUEPS_PID_MMC,
                    ID_MMC_LMM_RESUME_NOTIFY,
                    NAS_EMM_MsSuspendSsWaitEndMsgMmcResumeNotify),

    NAS_EMM_ACT_TBL_ITEM(WUEPS_PID_MMC,
                    ID_MMC_LMM_SUSPEND_REL_REQ,
                    NAS_EMM_MsSuspendSsWaitEndMsgMmcSuspendRelReq),
    /*============= LRRC =======================================*/
    NAS_EMM_ACT_TBL_ITEM(PS_PID_ERRC,
                    ID_LRRC_LMM_RESUME_IND,
                    NAS_EMM_MsSuspendSsWaitEndMsgLrrcResumeInd),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_ERRC,
                    ID_LRRC_LMM_ACCESS_GRANT_IND,
                    NAS_EMM_MsSuspendSsRrcOriMsgRrcAccessGrantInd),

    /*============= TIMER =======================================*/
    NAS_EMM_ACT_TI_TBL_ITEM(VOS_PID_TIMER,
                    TI_NAS_EMM_WAIT_SUSPEND_END_TIMER,
                    NAS_EMM_MsSuspendSsWaitEndMsgWtEndTimerExp),

    NAS_EMM_ACT_TI_TBL_ITEM(VOS_PID_TIMER,
                    TI_NAS_EMM_PTL_T3412,
                    NAS_EMM_MsSuspendSsAnyMsgT3412Exp),
    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_TAU_REQ,
                    NAS_EMM_MsSuspendSsSomeStatusMsgIntraTauReq),
};
/* EMM_MS_SUSPEND =================================================*/
/*================= EMM_SS_SUSPEND_SYSCFGORI_WAIT_OTHER_SUSPEND ===========*/

NAS_EMM_ACT_STRU    g_astEmmMsSuspendSsSysCfgOriWaitOtherSusPendTable[] =
{
    /*============= ESM ==========================================*/
    NAS_EMM_ACT_TBL_ITEM(PS_PID_ESM,
                    ID_EMM_ESM_SUSPEND_RSP,
                    NAS_EMM_MsSuspendSsSysCfgOriWaitOtherMsgSusRsp),

    /*============= ERABM =======================================*/
    NAS_EMM_ACT_TBL_ITEM(PS_PID_RABM,
                     ID_EMM_ERABM_SUSPEND_RSP,
                     NAS_EMM_MsSuspendSsSysCfgOriWaitOtherMsgSusRsp),

    /*============= MMC =======================================*/
    NAS_EMM_ACT_TBL_ITEM(WUEPS_PID_MMC,
                     ID_MMC_LMM_DETACH_REQ,
                     NAS_EMM_MsSuspendSsMmcOrSyscfgOriWaitOtherMsgMmcDetachReq),

    /*============= LRRC =======================================*/
    NAS_EMM_ACT_TBL_ITEM(PS_PID_ERRC,
                     ID_LRRC_LMM_SUSPEND_CNF,
                     NAS_EMM_MsSuspendSsSysCfgOriWaitOtherMsgSusRsp),

    /*============= TIMER =======================================*/
    NAS_EMM_ACT_TI_TBL_ITEM(VOS_PID_TIMER,
                    TI_NAS_EMM_SYSCFGORI_WAIT_OTHER_SUSPEND_RSP_TIMER,
                    NAS_EMM_MsSuspendSsSyscfgWaitOtherMsgTimerExp),

    NAS_EMM_ACT_TI_TBL_ITEM(VOS_PID_TIMER,
                    TI_NAS_EMM_PTL_T3412,
                    NAS_EMM_MsSuspendSsAnyMsgT3412Exp),
    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_TAU_REQ,
                    NAS_EMM_MsSuspendSsSomeStatusMsgIntraTauReq)

};

/* EMM_MS_RESUME =================================================*/
/*================= EMM_SS_RESUME_RRCRSM_WAIT_OTHER_RESUME =======*/

NAS_EMM_ACT_STRU    g_astEmmMsResumeSsWaitCmResumeTable[] =
{
    /*============= ESM ==========================================*/
    NAS_EMM_ACT_TBL_ITEM(PS_PID_ESM,
                    ID_EMM_ESM_RESUME_RSP,
                    NAS_EMM_MsResumeSsRrcRsmWaitOtherMsgRsmRsp),

    /*============= ERABM =======================================*/
    NAS_EMM_ACT_TBL_ITEM(PS_PID_RABM,
                    ID_EMM_ERABM_RESUME_RSP,
                    NAS_EMM_MsResumeSsRrcRsmWaitOtherMsgRsmRsp),

    /*============= LRRC ==========================================*/
    NAS_EMM_ACT_TBL_ITEM(PS_PID_ERRC,
                    ID_LRRC_LMM_ACCESS_GRANT_IND,
                    NAS_EMM_MsResumeReverseMsgRrcAccessGrantInd),

    /*============= TIMER =======================================*/
    NAS_EMM_ACT_TI_TBL_ITEM(VOS_PID_TIMER,
                     TI_NAS_EMM_RRCRSM_WAIT_OTHER_RESUME_RSP_TIMER,
                     NAS_EMM_MsResumeSsRrcRsmWaitOtherMsgWtOtherTimerExp),

    NAS_EMM_ACT_TI_TBL_ITEM(VOS_PID_TIMER,
                    TI_NAS_EMM_PTL_T3412,
                    NAS_EMM_MsResumeSsRrcOriMsgT3412Exp),
};


/* EMM_MS_RESUME =================================================*/
/*================= EMM_SS_RESUME_RRCORI_WAIT_SYS_INFO_IND ================*/

NAS_EMM_ACT_STRU    g_astEmmMsResumeSsRrcOriWaitSysInfoIndTable[] =
{
    /*============= PLMN ==========================================*/
    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_EMMC_EMM_PLMN_IND,
                    NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgMmcPlmnInd),

    /*============= ATTACH ======DETACH============================*/
    NAS_EMM_ACT_TBL_ITEM(WUEPS_PID_MMC,
                     ID_MMC_LMM_DETACH_REQ,
                     NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgMmcDetachReq),


    /*============= LRRC =======================================*/
    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_EMMC_EMM_SYS_INFO_IND,
                    NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgSysInfoInd),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_EMMC_EMM_COVERAGE_LOST_IND,
                    NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgAreaLostInd),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_ERRC,
                    ID_LRRC_LMM_REL_IND,
                    NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgRrcRelInd),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_ERRC,
                    ID_LRRC_LMM_ACCESS_GRANT_IND,
                    NAS_EMM_MsResumeReverseMsgRrcAccessGrantInd),

    /*============= TAU ===========================================*/
    NAS_EMM_ACT_TI_TBL_ITEM(VOS_PID_TIMER,
                    TI_NAS_EMM_PTL_T3412,
                    NAS_EMM_MsResumeSsRrcOriMsgT3412Exp),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_ESM,
                    ID_EMM_ESM_BEARER_STATUS_REQ,
                    NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgBearStatusReq),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_TAU_REQ,
                    NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgIntraTauReq),

    /*============= TIMER =======================================*/
    NAS_EMM_ACT_TI_TBL_ITEM(VOS_PID_TIMER,
                     TI_NAS_EMM_WAIT_SYS_INFO_IND_TIMER,
                     NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgWtSysInfoTimerExp),

};

/* EMM_MS_RESUME =================================================*/
/*================= EMM_SS_RESUME_MMCORI_WAIT_SYS_INFO_IND ================*/

NAS_EMM_ACT_STRU    g_astEmmMsResumeSsMmcOriWaitSysInfoIndTable[] =
{
    /*============= PLMN ==========================================*/
    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_EMMC_EMM_PLMN_IND,
                    NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgMmcPlmnInd),
    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_EMMC_EMM_COVERAGE_LOST_IND,
                    NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgAreaLostInd),

    /*============= ATTACH ======DETACH============================*/
    NAS_EMM_ACT_TBL_ITEM(WUEPS_PID_MMC,
                     ID_MMC_LMM_DETACH_REQ,
                     NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgMmcDetachReq),

    /*============= LRRC =======================================*/
    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_EMMC_EMM_SYS_INFO_IND,
                     NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgSysInfoInd),
    /*============= TAU ===========================================*/
    NAS_EMM_ACT_TI_TBL_ITEM(VOS_PID_TIMER,
                    TI_NAS_EMM_PTL_T3412,
                    NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgT3412Exp),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_ESM,
                    ID_EMM_ESM_BEARER_STATUS_REQ,
                    NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgBearStatusReq),
    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_TAU_REQ,
                    NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgIntraTauReq),

    /*============= TIMER =======================================*/


};


/* EMM_MS_TAU_INIT ==========================================================*/
/*================= EMM_SS_TAU_WAIT_CN_TAU_CNF ====================*/
NAS_EMM_ACT_STRU    g_astEmmMsTauInitSsWaitCnTauCnfTable[] =
{
    /*============= PLMN ==========================================*/
    NAS_EMM_ACT_TBL_ITEM(PS_PID_ERRC,
                    ID_LRRC_LMM_PAGING_IND,
                    NAS_EMM_MsTauInitSsTauWaitCnTauCnfMsgRrcPagingInd),

    /*============= ATTACH ======DETACH============================*/
    NAS_EMM_ACT_TBL_ITEM(WUEPS_PID_MMC,
                    ID_MMC_LMM_ATTACH_REQ,
                    NAS_EMM_MsTauInitSsWtCnTauCnfMsgAppAttachReq),

    NAS_EMM_ACT_TBL_ITEM(WUEPS_PID_MMC,
                    ID_MMC_LMM_DETACH_REQ,
                    NAS_EMM_MsTauInitSsWtCnTauCnfMsgAppDetachReq),

    NAS_EMM_ACT_CN_TBL_ITEM(PS_PID_ERRC,
                    NAS_EMM_CN_MT_DETACH_REQ_MT,
                    NAS_EMM_MsTauInitSsWtCnTauCnfMsgCnDetatchReq),

    /*============= TAU ===========================================*/
    NAS_EMM_ACT_TI_TBL_ITEM(VOS_PID_TIMER,
                    TI_NAS_EMM_STATE_TAU_T3430,
                    NAS_EMM_MsTauInitSsWaitCNCnfMsgT3430Exp),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_ERRC,
                    ID_LRRC_LMM_REL_IND,
                    NAS_EMM_MsTauInitSsWaitCnCnfMsgRrcRelInd),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_RABM,
                    ID_EMM_ERABM_DRB_SETUP_IND,
                    NAS_EMM_MsTauInitSsWaitCnCnfMsgDrbSetupInd),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_MRRC_CONNECT_FAIL_IND,
                    NAS_EMM_MsTauInitSsWaitCNCnfMsgIntraConnectFailInd),

    NAS_EMM_ACT_CN_TBL_ITEM(PS_PID_ERRC,
                    NAS_EMM_CN_MT_TAU_ACP,
                    NAS_EMM_MsTauInitSsWaitCNCnfMsgTAUAcp),

    NAS_EMM_ACT_CN_TBL_ITEM(PS_PID_ERRC,
                    NAS_EMM_CN_MT_TAU_REJ,
                    NAS_EMM_MsTauInitSsWaitCNCnfMsgTAURej),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_EMMC_EMM_SYS_INFO_IND,
                    NAS_EMM_MsTauInitSsWaitCNCnfMsgSysinfo),

/*    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_TAU_REQ,
                    NAS_EMM_MsTauInitSsAnyStatusMsgIntraTauReq),*/

    NAS_EMM_ACT_TBL_ITEM(PS_PID_ESM,
                    ID_EMM_ESM_BEARER_STATUS_REQ,
                    NAS_EMM_MsTauInitSsWaitCnCnfMsgBearerStatusReq),
    /*============= SERVICE =======================================*/
    NAS_EMM_ACT_TBL_ITEM(PS_PID_RABM,
                    ID_EMM_ERABM_REEST_REQ,
                    NAS_EMM_MsTauInitMsgRabmReestReq),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_ESM,
                    ID_EMM_ESM_DATA_REQ,
                    NAS_EMM_MsTauInitMsgEsmdataReq),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_RABM,
                    ID_EMM_ERABM_REL_REQ,
                    NAS_EMM_MsTauInitMsgRabmRelReq),

    /*============= GUTI ==========================================*/
    /*============= IDEN ==========================================*/
    /*============= AUTH ==========================================*/
    NAS_EMM_ACT_CN_TBL_ITEM(PS_PID_ERRC,
                    NAS_EMM_CN_MT_AUTH_REQ,
                    NAS_EMM_MsAnyStateSsAnyStateMsgCnAuthReq),

    NAS_EMM_ACT_TBL_ITEM(WUEPS_PID_USIM,
                    USIMM_AUTHENTICATION_CNF,
                    NAS_EMM_MsAnyStateSsAnyStateMsgUsimAuthCnf),

    NAS_EMM_ACT_CN_TBL_ITEM(PS_PID_ERRC,
                    NAS_EMM_CN_MT_AUTH_REJ,
                    NAS_EMM_MsTauInitSsWaitCnCnfMsgAuthRej),

    /*============= AUTH ==========================================*/
    /*============= MRRC ==========================================*/

    NAS_EMM_ACT_CN_TBL_ITEM(PS_PID_ERRC,
                    NAS_EMM_CN_MT_IDEN_REQ,
                    NAS_EMM_AnyStateMsgIdenReq),

    /*NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_MRRC_DATA_REQ,
                    NAS_EMM_MsNoRrcConnInitSsAllMsgMrrcDataReq),*/
};

/* EMM_MS_SER_INIT ==========================================================*/
/*================= EMM_SS_SER_WAIT_CN_SER_CNF ====================*/
NAS_EMM_ACT_STRU    g_astEmmMsSerInitSsWaitCnSerCnfTable[] =
{
    /*============= PLMN ==========================================*/
    NAS_EMM_ACT_TBL_ITEM(PS_PID_ERRC,
                    ID_LRRC_LMM_PAGING_IND,
                    NAS_EMM_MsSerInitSsSerWaitCnSerCnfMsgRrcPagingInd),

    /*============= ATTACH ======DETACH============================*/
    NAS_EMM_ACT_TBL_ITEM(WUEPS_PID_MMC,
                    ID_MMC_LMM_ATTACH_REQ,
                    NAS_EMM_MsSerInitSsWtCnSerCnfMsgAppAttachReq),

    NAS_EMM_ACT_TBL_ITEM(WUEPS_PID_MMC,
                    ID_MMC_LMM_DETACH_REQ,
                    NAS_EMM_MsSerInitSsWtCnSerCnfMsgAppDetachReq),

    /*============= TAU ===========================================*/
    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_EMMC_EMM_SYS_INFO_IND,
                    NAS_EMM_MsSerInitSsWaitCNCnfMsgSysinfo),

    /*============= SERVICE =======================================*/
    NAS_EMM_ACT_TBL_ITEM(PS_PID_ERRC,
                    ID_LRRC_LMM_REL_IND,
                    NAS_EMM_MsSerInitSsWaitCnSerCnfMsgRrcRelInd),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_MRRC_CONNECT_FAIL_IND,
                    NAS_EMM_MsSerInitSsWaitCnSerCnfMsgIntraConnectFailInd),

    NAS_EMM_ACT_CN_TBL_ITEM(PS_PID_ERRC,
                    NAS_EMM_CN_MT_DETACH_REQ_MT,
                    NAS_EMM_MsSerInitSsWtCnSerCnfMsgCnDetatchReq),

    NAS_EMM_ACT_TI_TBL_ITEM(VOS_PID_TIMER,
                    TI_NAS_EMM_STATE_SERVICE_T3417,
                    NAS_EMM_MsSerInitSsWaitCnSerCnfMsgTimer3417Exp),

    NAS_EMM_ACT_TI_TBL_ITEM(VOS_PID_TIMER,
                    TI_NAS_EMM_STATE_SERVICE_T3417_EXT,
                    NAS_EMM_MsSerInitSsWaitCnSerCnfMsgTimer3417ExtExp),

    NAS_EMM_ACT_CN_TBL_ITEM(PS_PID_ERRC,
                    NAS_EMM_CN_MT_SER_REJ,
                    NAS_EMM_MsSerInitSsWaitCNSerCnfMsgServiceReject),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_RABM,
                    ID_EMM_ERABM_DRB_SETUP_IND,
                    NAS_EMM_MsSerInitMsgRabmDrbSetupInd),
    NAS_EMM_ACT_TBL_ITEM(PS_PID_ESM,
                    ID_EMM_ESM_DATA_REQ,
                    NAS_EMM_MsSerInitMsgEsmdataReq),
    /*============= GUTI ==========================================*/
    /*============= IDEN ==========================================*/
    /*============= AUTH ==========================================*/
    NAS_EMM_ACT_CN_TBL_ITEM(PS_PID_ERRC,
                    NAS_EMM_CN_MT_AUTH_REQ,
                    NAS_EMM_MsAnyStateSsAnyStateMsgCnAuthReq),

    NAS_EMM_ACT_TBL_ITEM(WUEPS_PID_USIM,
                    USIMM_AUTHENTICATION_CNF,
                    NAS_EMM_MsAnyStateSsAnyStateMsgUsimAuthCnf),

    NAS_EMM_ACT_CN_TBL_ITEM(PS_PID_ERRC,
                    NAS_EMM_CN_MT_AUTH_REJ,
                    NAS_EMM_MsSerInitSsWaitCnSerCnfMsgAuthRej),

    /*============= MRRC ==========================================*/
    NAS_EMM_ACT_CN_TBL_ITEM(PS_PID_ERRC,
                    NAS_EMM_CN_MT_GUTI_CMD,
                    NAS_EMM_AnyStateMsgGtReCmd),

     NAS_EMM_ACT_CN_TBL_ITEM(PS_PID_ERRC,
                    NAS_EMM_CN_MT_IDEN_REQ,
                    NAS_EMM_AnyStateMsgIdenReq),

    /*NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_MRRC_DATA_REQ,
                    NAS_EMM_MsNoRrcConnInitSsAllMsgMrrcDataReq),*/
};


/* EMM_MS_DEREG_INIT ========================================================*/
/*================= EMM_SS_DETACH_WAIT_CN_DETACH_CNF ==============*/
NAS_EMM_ACT_STRU    g_astEmmMsDeregInitSsWaitCnDetachCnfTable[] =
{
    /*============= PLMN ==========================================*/
    /*NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_EMMC_EMM_PLMN_IND,
                    NAS_EMM_MsNotNullSsAnyStateMsgMmcPlmnInd),*/

    /*============= ATTACH ======DETACH============================*/
    NAS_EMM_ACT_TBL_ITEM(WUEPS_PID_MMC,
                    ID_MMC_LMM_ATTACH_REQ,
                    NAS_EMM_MsDrgInitSsWtCnDetCnfMsgAppAttachReq),

    NAS_EMM_ACT_CN_TBL_ITEM(PS_PID_ERRC,
                    NAS_EMM_CN_MT_DETACH_REQ_MT,
                    NAS_EMM_MsDrgInitSsWtCnDetCnfMsgCnDetachReq),

    NAS_EMM_ACT_CN_TBL_ITEM(PS_PID_ERRC,
                    NAS_EMM_CN_MT_DETACH_ACP_MO,
                    NAS_EMM_MsDrgInitSsWtCnDetCnfMsgCnDetachAcp),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_ERRC,
                    ID_LRRC_LMM_REL_IND,
                    NAS_EMM_MsDrgInitSsWtCnDetCnfMsgRrcRelInd),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_MRRC_CONNECT_FAIL_IND,
                    NAS_EMM_MsDrgInitSsWtCnDetCnfMsgIntraConnectFailInd),

    NAS_EMM_ACT_TI_TBL_ITEM(VOS_PID_TIMER,
                    TI_NAS_EMM_T3421,
                    NAS_EMM_MsDrgInitSsWtCnDetCnfMsgT3421Exp),

    /*============= TAU ===========================================*/
    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_EMMC_EMM_SYS_INFO_IND,
                    NAS_EMM_MsDeRegInitSsWaitCNDetachCnfMsgSysinfo),

    /*============= SERVICE =======================================*/
    /*============= GUTI ==========================================*/
    /*============= IDEN ==========================================*/
    /*============= MRRC ==========================================*/
    NAS_EMM_ACT_CN_TBL_ITEM(PS_PID_ERRC,
                    NAS_EMM_CN_MT_IDEN_REQ,
                    NAS_EMM_AnyStateMsgIdenReq),

    /*NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_MRRC_DATA_REQ,
                    NAS_EMM_MsNoRrcConnInitSsAllMsgMrrcDataReq),*/
    /*============= AUTH ==========================================*/
    NAS_EMM_ACT_CN_TBL_ITEM(PS_PID_ERRC,
                    NAS_EMM_CN_MT_AUTH_REQ,
                    NAS_EMM_MsAnyStateSsAnyStateMsgCnAuthReq),

    NAS_EMM_ACT_TBL_ITEM(WUEPS_PID_USIM,
                    USIMM_AUTHENTICATION_CNF,
                    NAS_EMM_MsAnyStateSsAnyStateMsgUsimAuthCnf),

    NAS_EMM_ACT_CN_TBL_ITEM(PS_PID_ERRC,
                    NAS_EMM_CN_MT_AUTH_REJ,
                    NAS_EMM_MsDrgInitSsWtCnDetCnfMsgAuthRej),
};

/* EMM_MS_AUTH_INIT ==================================================*/
/*================= EMM_SS_AUTH_WAIT_CN_AUTH =========================*/
NAS_EMM_ACT_STRU    g_astEmmMsAuthInitSsWaitCnAuthTable[] =
{
    /*============= ATTACH ==========================================*/
    NAS_EMM_ACT_CN_TBL_ITEM(PS_PID_ERRC,
                    NAS_EMM_CN_MT_ATTACH_REJ,
                    NAS_EMM_MsAuthInitSsWtCnAuthMsgAttachRej),

    NAS_EMM_ACT_CN_TBL_ITEM(PS_PID_ERRC,
                    NAS_EMM_CN_MT_ATTACH_ACP,
                    NAS_EMM_MsAuthInitSsWtCnAuthMsgAttachAccept),

    /*============= TAU ==========================================*/
    NAS_EMM_ACT_CN_TBL_ITEM(PS_PID_ERRC,
                    NAS_EMM_CN_MT_TAU_REJ,
                    NAS_EMM_MsAuthInitSsWtCnAuthMsgTauRej),

    NAS_EMM_ACT_CN_TBL_ITEM(PS_PID_ERRC,
                    NAS_EMM_CN_MT_TAU_ACP,
                    NAS_EMM_MsAuthInitSsWtCnAuthMsgTauAccept),

    /*============= SER ==========================================*/
    NAS_EMM_ACT_CN_TBL_ITEM(PS_PID_ERRC,
                    NAS_EMM_CN_MT_SER_REJ,
                    NAS_EMM_MsAuthInitSsWtCnAuthMsgSerRej),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_RABM,
                    ID_EMM_ERABM_DRB_SETUP_IND,
                    NAS_EMM_MsAuthInitSsWtCnAuthMsgRabmDrbSetupInd),

    /*============= DETACH ==========================================*/
    NAS_EMM_ACT_CN_TBL_ITEM(PS_PID_ERRC,
                    NAS_EMM_CN_MT_DETACH_ACP_MO,
                    NAS_EMM_MsAuthInitSsWtCnAuthMsgCnDetachAcp),

    /*============= AUTH ==========================================*/
    NAS_EMM_ACT_CN_TBL_ITEM(PS_PID_ERRC,
                    NAS_EMM_CN_MT_AUTH_REQ,
                    NAS_EMM_MsAuthInitSsWtCnAuthMsgCnAuthReq),

    NAS_EMM_ACT_TBL_ITEM(WUEPS_PID_USIM,
                    USIMM_AUTHENTICATION_CNF,
                    NAS_EMM_MsAnyStateSsAnyStateMsgUsimAuthCnf),

    NAS_EMM_ACT_CN_TBL_ITEM(PS_PID_ERRC,
                    NAS_EMM_CN_MT_AUTH_REJ,
                    NAS_EMM_MsAuthInitSsWtCnAuthMsgCnAuthRej),

    NAS_EMM_ACT_TI_TBL_ITEM(VOS_PID_TIMER,
                    TI_NAS_EMM_T3418,
                    NAS_EMM_MsAuthInitSsWtCnAuthMsgT3418Exp),

    NAS_EMM_ACT_TI_TBL_ITEM(VOS_PID_TIMER,
                    TI_NAS_EMM_T3420,
                    NAS_EMM_MsAuthInitSsWtCnAuthMsgT3420Exp),

    /*============= IDEN ==========================================*/
    /*============= MRRC ==========================================*/
    NAS_EMM_ACT_CN_TBL_ITEM(PS_PID_ERRC,
                    NAS_EMM_CN_MT_IDEN_REQ,
                    NAS_EMM_AnyStateMsgIdenReq),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_ERRC,
                    ID_LRRC_LMM_REL_IND,
                    NAS_EMM_MsAuthInitSsWtCnAuthMsgRrcRelInd),

    NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_EIA0_ACT_NOTIFY,
                    NAS_EMM_MsAuthInitSsWtCnAuthMsgEia0ActNotify),
    /*NAS_EMM_ACT_TBL_ITEM(PS_PID_MM,
                    ID_NAS_LMM_INTRA_MRRC_DATA_REQ,
                    NAS_EMM_MsNoRrcConnInitSsAllMsgMrrcDataReq),*/
        /*X00148705 没有对APP DETACH,REL IND消息处理*/

};

/* 状态转移表 */
NAS_EMM_STA_STRU     g_astEmmStaTbl[] =
{

    /*================= EMM_MS_NULL 状态机的描述表 ================*/
    NAS_LMM_STA_TBL_ITEM(EMM_MS_NULL,
                        EMM_SS_NULL_WAIT_MMC_START_CNF,
                        g_astEmmMsNullSsWaitMmcStartCnfTable),

    NAS_LMM_STA_TBL_ITEM(EMM_MS_NULL,
                        EMM_SS_NULL_WAIT_RRC_START_CNF,
                        g_astEmmMsNullSsWaitRrcStartCnfTable),

    NAS_LMM_STA_TBL_ITEM(EMM_MS_NULL,
                        EMM_SS_NULL_WAIT_MMC_STOP_CNF,
                        g_astEmmMsNullSsWaitMmcStopCnfTable),

    NAS_LMM_STA_TBL_ITEM(EMM_MS_NULL,
                        EMM_SS_NULL_WAIT_RRC_STOP_CNF,
                        g_astEmmMsNullSsWaitRrcStopCnfTable),

    NAS_LMM_STA_TBL_ITEM(EMM_MS_NULL,
                        EMM_SS_NULL_WAIT_SWITCH_OFF,
                        g_astEmmMsNullSsWaitSwitchOffTable),

    /* ================ EMM_MS_DEREG 状态机的描述表 ===============*/
    NAS_LMM_STA_TBL_ITEM(EMM_MS_DEREG,
                        EMM_SS_DEREG_NORMAL_SERVICE,
                        g_astEmmMsDeregSsNormalServiceTable),

    NAS_LMM_STA_TBL_ITEM(EMM_MS_DEREG,
                        EMM_SS_DEREG_LIMITED_SERVICE,
                        g_astEmmMsDeregSsLimitServiceTable),

    NAS_LMM_STA_TBL_ITEM(EMM_MS_DEREG,
                        EMM_SS_DEREG_ATTEMPTING_TO_ATTACH,
                        g_astEmmMsDeregSsAttempToAttachTable),

    NAS_LMM_STA_TBL_ITEM(EMM_MS_DEREG,
                        EMM_SS_DEREG_PLMN_SEARCH,
                        g_astEmmMsDeregSsPlmnSearchTable),

    NAS_LMM_STA_TBL_ITEM(EMM_MS_DEREG,
                        EMM_SS_DEREG_NO_IMSI,
                        g_astEmmMsDeregSsNoImsiTable),

    NAS_LMM_STA_TBL_ITEM(EMM_MS_DEREG,
                        EMM_SS_DEREG_ATTACH_NEEDED,
                        g_astEmmMsDeregSsAttachNeededTable),

    NAS_LMM_STA_TBL_ITEM(EMM_MS_DEREG,
                        EMM_SS_DEREG_NO_CELL_AVAILABLE,
                        g_astEmmMsDeregSsNoCellAvailTable),



    /* ================ EMM_MS_REG_INIT 状态机的描述表 ============*/
    NAS_LMM_STA_TBL_ITEM(EMM_MS_REG_INIT,
                        EMM_SS_ATTACH_WAIT_ESM_PDN_RSP,
                        g_astEmmMsRegInitSsWaitEsmPdnRspTable),

    NAS_LMM_STA_TBL_ITEM(EMM_MS_REG_INIT,
                        EMM_SS_ATTACH_WAIT_CN_ATTACH_CNF,
                        g_astEmmMsRegInitSsWaitCnAttachCnfTable),

    NAS_LMM_STA_TBL_ITEM(EMM_MS_REG_INIT,
                        EMM_SS_ATTACH_WAIT_ESM_BEARER_CNF,
                        g_astEmmMsRegInitSsWaitEsmBearerCnfTable),

    NAS_LMM_STA_TBL_ITEM(EMM_MS_REG_INIT,
                        EMM_SS_ATTACH_WAIT_RRC_DATA_CNF,
                        g_astEmmMsRegInitSsWaitRrcDataCnfTable),





    /* ================ EMM_MS_REG 状态机的描述表 =================*/
    NAS_LMM_STA_TBL_ITEM(EMM_MS_REG,
                        EMM_SS_REG_NORMAL_SERVICE,
                        g_astEmmMsRegSsNormalServiceTable),

    NAS_LMM_STA_TBL_ITEM(EMM_MS_REG,
                        EMM_SS_REG_ATTEMPTING_TO_UPDATE,
                        g_astEmmMsRegSsAttemptToUpdateTable),

    NAS_LMM_STA_TBL_ITEM(EMM_MS_REG,
                        EMM_SS_REG_LIMITED_SERVICE,
                        g_astEmmMsRegSsLimitServiceTable),

    NAS_LMM_STA_TBL_ITEM(EMM_MS_REG,
                        EMM_SS_REG_PLMN_SEARCH,
                        g_astEmmMsRegSsPlmnSearchTable),

    NAS_LMM_STA_TBL_ITEM(EMM_MS_REG,
                        EMM_SS_REG_WAIT_ACCESS_GRANT_IND,
                        g_astEmmMsRegSsWaitAccessGrantIndTable),

    NAS_LMM_STA_TBL_ITEM(EMM_MS_REG,
                        EMM_SS_REG_NO_CELL_AVAILABLE,
                        g_astEmmMsRegSsNoCellAvailTable),

    NAS_LMM_STA_TBL_ITEM(EMM_MS_REG,
                        EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM,
                        g_astEmmMsRegSsRegAttemptingToUpdateMMTable),

    NAS_LMM_STA_TBL_ITEM(EMM_MS_REG,
                        EMM_SS_REG_IMSI_DETACH_WATI_CN_DETACH_CNF,
                        g_astEmmMsRegSsRegImsiDetachWaitCnDetachCnfTable),




    /* ================ EMM_MS_TAU_INIT 状态机的描述表 ============*/
    NAS_LMM_STA_TBL_ITEM(EMM_MS_TAU_INIT,
                        EMM_SS_TAU_WAIT_CN_TAU_CNF,
                        g_astEmmMsTauInitSsWaitCnTauCnfTable),



    /* ================ EMM_MS_SER_INIT 状态机的描述表 ============*/
    NAS_LMM_STA_TBL_ITEM(EMM_MS_SER_INIT,
                        EMM_SS_SER_WAIT_CN_SER_CNF,
                        g_astEmmMsSerInitSsWaitCnSerCnfTable),



    /* ================ EMM_MS_DEREG_INIT 状态机的描述表 ==========*/
    NAS_LMM_STA_TBL_ITEM(EMM_MS_DEREG_INIT,
                        EMM_SS_DETACH_WAIT_CN_DETACH_CNF,
                        g_astEmmMsDeregInitSsWaitCnDetachCnfTable),

    /* ================ EMM_MS_AUTH_INIT 状态机的描述表 ===*/
    NAS_LMM_STA_TBL_ITEM(EMM_MS_AUTH_INIT,
                        EMM_SS_AUTH_WAIT_CN_AUTH,
                        g_astEmmMsAuthInitSsWaitCnAuthTable),



    /* ================ EMM_MS_SUSPEND 状态机的描述表 ===*/

    NAS_LMM_STA_TBL_ITEM(EMM_MS_SUSPEND,
                        EMM_SS_SUSPEND_RRCORI_WAIT_MMC_SUSPEND,
                        g_astEmmMsSuspendSsRrcOriWaitMmcSusPendTable),
    NAS_LMM_STA_TBL_ITEM(EMM_MS_SUSPEND,
                        EMM_SS_SUSPEND_RRCORI_WAIT_OTHER_SUSPEND,
                        g_astEmmMsSuspendSsRrcOriWaitOtherSusPendTable),
    NAS_LMM_STA_TBL_ITEM(EMM_MS_SUSPEND,
                        EMM_SS_SUSPEND_MMCORI_WAIT_OTHER_SUSPEND,
                        g_astEmmMsSuspendSsMmcOriWaitOtherSusPendTable),
    NAS_LMM_STA_TBL_ITEM(EMM_MS_SUSPEND,
                        EMM_SS_SUSPEND_SYSCFGORI_WAIT_OTHER_SUSPEND,
                        g_astEmmMsSuspendSsSysCfgOriWaitOtherSusPendTable),

    NAS_LMM_STA_TBL_ITEM(EMM_MS_SUSPEND,
                        EMM_SS_SUSPEND_WAIT_END,
                        g_astEmmMsSuspendSsWaitEndTable),




    /* ================ EMM_MS_RESUME 状态机的描述表 ===*/
    NAS_LMM_STA_TBL_ITEM(EMM_MS_RESUME,
                        EMM_SS_RESUME_RRCRSM_WAIT_OTHER_RESUME,
                        g_astEmmMsResumeSsWaitCmResumeTable),
    NAS_LMM_STA_TBL_ITEM(EMM_MS_RESUME,
                        EMM_SS_RESUME_RRCORI_WAIT_SYS_INFO_IND,
                        g_astEmmMsResumeSsRrcOriWaitSysInfoIndTable),
    NAS_LMM_STA_TBL_ITEM(EMM_MS_RESUME,
                        EMM_SS_RESUME_MMCORI_WAIT_SYS_INFO_IND,
                        g_astEmmMsResumeSsMmcOriWaitSysInfoIndTable)

};

VOS_UINT32  g_ulSizeof_g_astEmmStaTbl    = sizeof(g_astEmmStaTbl);



/*****************************************************************************
  3 Function
*****************************************************************************/

/*****************************************************************************
 Function Name  :
 Discription    :
 Input          :
 Output         : None
 Return         : None
 History:
      1.  Name+ID  yyyy-mm-dd  Draft Enact
*****************************************************************************/



LRRC_NAS_UEID_STRU                       gstRrcNasUeId;
LRRC_NAS_AC_CLASS_STRU                   gstRrcNasAc;
LRRC_LNAS_PLMN_ID_STRU                    gstRrcNasPlmnId;



/*****************************************************************************
 Function Name   : LRRC_LNAS_GetPrioSelectPlmn
 Description     : 该函数的获取结果是在系统消息中优先选择的PLMN
                   主要适用于在共享网络中一个小区有多个PLMN的场景
                   目的是解决切换之后计算KASME使用的PLMN参数问题
 Input           :VOS_VOID
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunjitan 00193151      2012-08-11  Draft Enact

*****************************************************************************/
/*lint -e960*/
/*lint -e961*/
VOS_UINT32  Nas_GetPrioSelectPlmn
(
    LRRC_LNAS_PLMN_ID_STRU             *pstRrcNasPlmnId
)
{
    NAS_GUMM_INFO_STRU                  stGuInfo;
    NAS_LMM_UEID_STRU                  *pstMmUeId = NAS_EMM_NULL_PTR;
    NAS_MM_GUTI_STRU                   *pstGuti  = NAS_EMM_NULL_PTR;

    pstGuti   = NAS_LMM_GetEmmInfoUeidGutiAddr();
    pstMmUeId = NAS_LMM_GetEmmInfoUeidAddr();

    if ( NAS_EMM_BIT_SLCT == pstMmUeId->bitOpGuti )
    {
        pstRrcNasPlmnId->aucPlmnId[0] = pstGuti->stPlmnId.aucPlmnId[0];
        pstRrcNasPlmnId->aucPlmnId[1] = pstGuti->stPlmnId.aucPlmnId[1];
        pstRrcNasPlmnId->aucPlmnId[2] = pstGuti->stPlmnId.aucPlmnId[2];

        /* 打印获取到的值 */
        NAS_LMM_PUBM_LOG3_INFO("GetPrioSelectPlmn: GUTI's plmn is:",
                                  pstRrcNasPlmnId->aucPlmnId[0],
                                  pstRrcNasPlmnId->aucPlmnId[1],
                                  pstRrcNasPlmnId->aucPlmnId[2]);
        TLPS_PRINT2LAYER_INFO1(Nas_GetPrioSelectPlmn_ENUM,LNAS_EMM_GUTI_PLMN,
                                  pstRrcNasPlmnId->aucPlmnId[0]);
        TLPS_PRINT2LAYER_INFO2(Nas_GetPrioSelectPlmn_ENUM,LNAS_EMM_GUTI_PLMN,
                                  pstRrcNasPlmnId->aucPlmnId[1],
                                  pstRrcNasPlmnId->aucPlmnId[2]);

        return NAS_EMM_SUCC;
    }

    if ( NAS_EMM_SUCC == NAS_EMM_CheckPtmsiAndRaiValidity() )
    {
        NAS_LMM_PUBM_LOG_NORM("GetPrioSelectPlmn: P-TMSI and RAI  is  valid!");
        TLPS_PRINT2LAYER_INFO(Nas_GetPrioSelectPlmn_ENUM,LNAS_FUNCTION_LABEL1);
        if (MMC_LMM_SUCC == NAS_EMM_GetGuInfo(NAS_GUMM_RAI,&stGuInfo))
        {
            pstRrcNasPlmnId->aucPlmnId[0] = stGuInfo.u.stRAI.stLai.stPlmnId.aucPlmnId[0];
            pstRrcNasPlmnId->aucPlmnId[1] = stGuInfo.u.stRAI.stLai.stPlmnId.aucPlmnId[1];
            pstRrcNasPlmnId->aucPlmnId[2] = stGuInfo.u.stRAI.stLai.stPlmnId.aucPlmnId[2];

            /* 打印获取到的值 */
            NAS_LMM_PUBM_LOG3_INFO("GetPrioSelectPlmn: RAI's plmn is:",
                                  pstRrcNasPlmnId->aucPlmnId[0],
                                  pstRrcNasPlmnId->aucPlmnId[1],
                                  pstRrcNasPlmnId->aucPlmnId[2]);
            TLPS_PRINT2LAYER_INFO1(Nas_GetPrioSelectPlmn_ENUM,LNAS_EMM_RAI_PLMN,
                                  pstRrcNasPlmnId->aucPlmnId[0]);
            TLPS_PRINT2LAYER_INFO2(Nas_GetPrioSelectPlmn_ENUM,LNAS_EMM_RAI_PLMN,
                                  pstRrcNasPlmnId->aucPlmnId[1],
                                  pstRrcNasPlmnId->aucPlmnId[2]);

            return NAS_EMM_SUCC;
        }
    }

    /* 既没有获取到GUTI中的PLMN，也没获取到RAI中的PLMN */
    return NAS_EMM_FAIL;

}

/*****************************************************************************
 Function Name   : NAS_EMM_GetMmInfoNoSimOrSimInvlid
 Description     : 当无卡或者卡无效时，获取MM信息
 Input           :LRRC_LNAS_INFO_TYPE_ENUM_UINT32  enInfoType
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong 00150010       2014-01-23  Draft Enact

*****************************************************************************/
VOS_VOID*  NAS_EMM_GetMmInfoNoSimOrSimInvlid
(
    LRRC_LNAS_INFO_TYPE_ENUM_UINT32     enInfoType
)
{
    LRRC_NAS_UEID_STRU                 *pstUeId         = VOS_NULL_PTR;
    NAS_LMM_NETWORK_INFO_STRU          *pstMmNetInfo    = VOS_NULL_PTR;

    pstUeId                             = &gstRrcNasUeId;
    pstMmNetInfo                        = NAS_LMM_GetEmmInfoNetInfoAddr();

    NAS_LMM_MEM_SET_S(pstUeId, sizeof(LRRC_NAS_UEID_STRU), 0, sizeof(LRRC_NAS_UEID_STRU));
    NAS_LMM_MEM_SET_S(&gstRrcNasAc,sizeof(LRRC_NAS_AC_CLASS_STRU),0,sizeof(LRRC_NAS_AC_CLASS_STRU));
    NAS_LMM_MEM_SET_S(&gstRrcNasPlmnId,sizeof(LRRC_LNAS_PLMN_ID_STRU),0,sizeof(LRRC_LNAS_PLMN_ID_STRU));

    if (LRRC_LNAS_INFO_TYPE_UEID == enInfoType)
    {
        return pstUeId;
    }
    else if (LRRC_LNAS_INFO_TYPE_AC == enInfoType)
    {
        return  &gstRrcNasAc;
    }
    else if (LRRC_LNAS_INFO_TYPE_PLMNID == enInfoType)
    {
        NAS_LMM_MEM_CPY_S(          &gstRrcNasPlmnId,
                                    sizeof(LRRC_LNAS_PLMN_ID_STRU),
                                    &(pstMmNetInfo->stPresentNetId.stPlmnId),
                                    sizeof(NAS_MM_PLMN_ID_STRU));
        return &gstRrcNasPlmnId;
    }
    else if(LRRC_LNAS_INFO_TYPE_RPLMN == enInfoType)
    {
        if((NAS_EMM_AD_BIT_SLCT == NAS_EMM_GetLVRTaiOpBit()) &&
            (VOS_FALSE == NAS_LMM_CheckPlmnIsInvalid(NAS_LMM_GetEmmInfoLastRegPlmnAddr())))
        {
            NAS_LMM_PUBM_LOG_INFO("Nas_GetLteInfo:RPLMN VALID");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_GetMmInfoNoSimOrSimInvlid_ENUM,LNAS_FUNCTION_LABEL1);
            NAS_LMM_MEM_CPY_S(          &gstRrcNasPlmnId,
                                        sizeof(LRRC_LNAS_PLMN_ID_STRU),
                                        NAS_LMM_GetEmmInfoLastRegPlmnAddr(),
                                        sizeof(NAS_MM_PLMN_ID_STRU));
        }
        else
        {
            NAS_LMM_MEM_CPY_S(          &gstRrcNasPlmnId,
                                        sizeof(LRRC_LNAS_PLMN_ID_STRU),
                                        &(pstMmNetInfo->stPresentNetId.stPlmnId),
                                        sizeof(NAS_MM_PLMN_ID_STRU));
        }

        return &gstRrcNasPlmnId;
    }
    else   /* 无卡状态不给RRC返回优先选择的PLMN，返回空指针 */
    {
        return VOS_NULL_PTR;
    }
}


VOS_VOID*  LRRC_LNAS_GetMmInfo( LRRC_LNAS_INFO_TYPE_ENUM_UINT32  enInfoType )
{
    LRRC_NAS_UEID_STRU                 *pstUeId;
    NAS_LMM_UEID_STRU                  *pstMmUeId;
    NAS_LMM_NETWORK_INFO_STRU          *pstMmNetInfo;
    MMC_LMM_PUB_INFO_STRU               stPubInfo;
    VOS_UINT32                          ulRslt;

    /*初始化*/
    NAS_LMM_MEM_SET_S(&stPubInfo, sizeof(MMC_LMM_PUB_INFO_STRU), 0, sizeof(MMC_LMM_PUB_INFO_STRU));


    pstUeId = &gstRrcNasUeId;

    pstMmUeId                           = NAS_LMM_GetEmmInfoUeidAddr();
    pstMmNetInfo                        = NAS_LMM_GetEmmInfoNetInfoAddr();
    if ((NAS_LMM_SIM_STATUS_UNAVAILABLE == NAS_LMM_GetSimState())
        || (NAS_LMM_SIM_INVALID == NAS_LMM_GetPsSimValidity()))
    {
        return NAS_EMM_GetMmInfoNoSimOrSimInvlid(enInfoType);
    }
    if (LRRC_LNAS_INFO_TYPE_UEID == enInfoType)
    {
        pstUeId->ucBitOpImsi            = pstMmUeId->bitOpImsi;
        NAS_LMM_MEM_CPY_S(              pstUeId->aucImsi,
                                        LRRC_LNAS_MAX_UEID_BUF_SIZE,
                                        pstMmUeId->aucImsi,
                                        LRRC_LNAS_MAX_UEID_BUF_SIZE);

        ulRslt = NAS_EMM_GetGulPubInfo(MMC_LMM_EHPLMN, &stPubInfo);
        if (MMC_LMM_SUCC == ulRslt)
        {
            pstUeId->ucBitOpEHplmn      = NAS_EMM_BIT_SLCT;

            if (LRRC_LNAS_MAX_EHPLMN_NUM < stPubInfo.u.stEHplmnList.ulPlmnNum)
            {
                pstUeId->stEHplmn.ulEHplmnIdNum = LRRC_LNAS_MAX_EHPLMN_NUM;
            }
            else
            {
                pstUeId->stEHplmn.ulEHplmnIdNum = stPubInfo.u.stEHplmnList.ulPlmnNum;
            }

            NAS_LMM_MEM_CPY_S(          pstUeId->stEHplmn.astEHplmnIdList,
                                        sizeof(LRRC_LNAS_PLMN_ID_STRU) * LRRC_LNAS_MAX_EHPLMN_NUM,
                                        stPubInfo.u.stEHplmnList.astPlmnId,
                                        pstUeId->stEHplmn.ulEHplmnIdNum * sizeof(NAS_MM_PLMN_ID_STRU));
        }

        ulRslt = NAS_EMM_GetGulPubInfo(MMC_LMM_HPLMN, &stPubInfo);
        if (MMC_LMM_SUCC == ulRslt)
        {
            pstUeId->ucBitOpHplmn       = NAS_EMM_BIT_SLCT;

            NAS_LMM_MEM_CPY_S(          &pstUeId->stHplmnId,
                                        sizeof(LRRC_LNAS_PLMN_ID_STRU),
                                        &stPubInfo.u.stHplmn,
                                        sizeof(LRRC_LNAS_PLMN_ID_STRU));
        }
        pstUeId->ucBitOpSTmsi           = pstMmUeId->bitOpGuti;
        pstUeId->stStmsi.ucMmec         = pstMmUeId->stGuti.stMmeCode.ucMmeCode;

        /*lint -e701*/
        pstUeId->stStmsi.ulMTmsi        = (pstMmUeId->stGuti.stMTmsi.ucMTmsi<<24)
                                        |(pstMmUeId->stGuti.stMTmsi.ucMTmsiCnt1<<16)
                                        |(pstMmUeId->stGuti.stMTmsi.ucMTmsiCnt2<<8)
                                        |(pstMmUeId->stGuti.stMTmsi.ucMTmsiCnt3);
        /*lint +e701*/

        return pstUeId;
    }
    else if(LRRC_LNAS_INFO_TYPE_AC == enInfoType)
    {
        /*gstRrcNasAc.usAccClassMask      = 0xF800;*/
        return  &gstRrcNasAc;
    }
    else if(LRRC_LNAS_INFO_TYPE_PLMNID == enInfoType)
    {
        NAS_LMM_MEM_CPY_S(                 &gstRrcNasPlmnId,
                                        sizeof(LRRC_LNAS_PLMN_ID_STRU),
                                        &(pstMmNetInfo->stPresentNetId.stPlmnId),
                                        sizeof(NAS_MM_PLMN_ID_STRU));
        return &gstRrcNasPlmnId;

    }
    else if ( LRRC_LNAS_INFO_TYPE_HO_PRIO_SELECT_PLMNID == enInfoType)
    {
        if (NAS_EMM_SUCC == Nas_GetPrioSelectPlmn(&gstRrcNasPlmnId) )
        {
             return &gstRrcNasPlmnId;
        }
    }
    else if(LRRC_LNAS_INFO_TYPE_RPLMN == enInfoType)
    {
        if((NAS_EMM_AD_BIT_SLCT == NAS_EMM_GetLVRTaiOpBit()) &&
            (VOS_FALSE == NAS_LMM_CheckPlmnIsInvalid(NAS_LMM_GetEmmInfoLastRegPlmnAddr())))
        {
            NAS_LMM_PUBM_LOG_INFO("Nas_GetLteInfo:RPLMN VALID");
            TLPS_PRINT2LAYER_INFO(LRRC_LNAS_GetMmInfo_ENUM,LNAS_FUNCTION_LABEL1);
            NAS_LMM_MEM_CPY_S(          &gstRrcNasPlmnId,
                                        sizeof(LRRC_LNAS_PLMN_ID_STRU),
                                        NAS_LMM_GetEmmInfoLastRegPlmnAddr(),
                                        sizeof(NAS_MM_PLMN_ID_STRU));
        }
        else
        {
            NAS_LMM_MEM_CPY_S(          &gstRrcNasPlmnId,
                                        sizeof(LRRC_LNAS_PLMN_ID_STRU),
                                        &(pstMmNetInfo->stPresentNetId.stPlmnId),
                                        sizeof(NAS_MM_PLMN_ID_STRU));
        }

        return &gstRrcNasPlmnId;
    }
    /* s00265702  为RRC增加保存GU系统消息  begin */
    else if(LRRC_LNAS_INFO_TYPE_GU_PLMN == enInfoType)
    {
        gstRrcNasPlmnId.aucPlmnId[0] = NAS_EMMC_GetGuSysInfoPlmnAddr()->aucPlmnId[0];
        gstRrcNasPlmnId.aucPlmnId[1] = NAS_EMMC_GetGuSysInfoPlmnAddr()->aucPlmnId[1];
        gstRrcNasPlmnId.aucPlmnId[2] = NAS_EMMC_GetGuSysInfoPlmnAddr()->aucPlmnId[2];
        return &gstRrcNasPlmnId;
    }
    /* s00265702  为RRC增加保存GU系统消息  end */
    else
    {
    }

    return VOS_NULL_PTR;

}

/*****************************************************************************
 Function Name   : LRRC_LNAS_GetSmcState
 Description     : RRC通过该函数获取NAS安全模式是否启动
 Input           :VOS_VOID
 Output          : None
 Return          : LRRC_LNAS_SMC_CTRL_ENUM_UINT8

 History         :
    1.zhengjunyan 00148421      2009-6-26  Draft Enact

*****************************************************************************/
LRRC_LNAS_SMC_CTRL_ENUM_UINT8 LRRC_LNAS_GetSmcState( VOS_VOID )
{
    NAS_LMM_PUBM_LOG_INFO("LRRC_LNAS_GetSmcState: entered!");
    TLPS_PRINT2LAYER_INFO(LRRC_LNAS_GetSmcState_ENUM,LNAS_ENTRY);

    if(NAS_EMM_SMC_OPEN == g_ulSmcControl)
    {
        return LRRC_LNAS_SMC_OPEN;
    }

    return LRRC_LNAS_SMC_CLOSE;
}

/*****************************************************************************
 Function Name   : NAS_EMM_ReadAccClassMask
 Description     : 从NV读取AC，给AC附初值
 Input           : VOS_VOID
 Output          : None
 Return          : NAS_LMM_SUCC
                   NAS_LMM_FAIL
                   NAS_LMM_ERR_CODE_HARD_USIM: 硬卡已发出读卡请求
 History         :
    1.h41410             2009-12-28   Draft Enact
    2.sunjitan 00193151  2015-03-15   Modify
*****************************************************************************/
VOS_VOID NAS_EMM_ReadAccClassMask( VOS_VOID )
{
    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_ReadAccClassMask is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_ReadAccClassMask_ENUM,LNAS_ENTRY);

    gstRrcNasAc.usAccClassMask = 0xF800;

    NAS_LMM_UsimFileRead(USIMM_USIM_EFACC_ID);
    return;
}

/* leixiantiao 00258641 降低圈复杂度 2014-7-30 begin */


VOS_UINT32 NAS_LMM_GetLteGutiInfo
(
    NAS_LMM_INFO_STRU             *pstLmmInfo,
    const NAS_LMM_UEID_STRU             *pstMmUeId
)
{
    VOS_UINT32 ulRslt;
    if (NAS_EMM_BIT_SLCT == pstMmUeId->bitOpGuti)
    {
        NAS_LMM_PUBM_LOG_INFO("Nas_GetLteInfo:GUTI VALID");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_GetLteGutiInfo_ENUM,LNAS_FUNCTION_LABEL1);
        NAS_LMM_MEM_CPY_S(          &pstLmmInfo->u.stGuti,
                                    sizeof(NAS_LMM_GUTI_STRU),
                                    &pstMmUeId->stGuti,
                                    sizeof(NAS_LMM_GUTI_STRU));

        ulRslt = MMC_LMM_SUCC;
    }
    else
    {
        ulRslt = MMC_LMM_FAIL;
    }
    return ulRslt;

}
/* leixiantiao 00258641 降低圈复杂度 2014-7-30 end */
/*****************************************************************************
 Function Name   : Nas_GetLteInfo
 Description     : 提供给MMC LTE相关信息
 Input           : ulInfoType       ---MMC当前获取的LTE信息类型
                   pstLmmInfo       ---MMC当前获取的LTE信息
 Output          : pstLmmInfo       ---提供给MMC的信息
 Return          : NAS_LMM_SUCC
                   NAS_LMM_FAIL

 History         :
    1.leili 00132387      2012-5-10     Draft Enact
    2.wangchen 00209181   2012-06-28    Modify:cs/ps1

*****************************************************************************/
MMC_LMM_RESULT_ID_ENUM_UINT32  Nas_GetLteInfo
(
    NAS_LMM_INFO_TYPE_ENUM_UINT32  ulInfoType,
    NAS_LMM_INFO_STRU             *pstLmmInfo
)
{
    NAS_LMM_UEID_STRU                  *pstMmUeId   = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt      = MMC_LMM_FAIL;
    NAS_MM_FORB_TA_LIST_STRU             *pstForbRoamTaiList = NAS_EMM_NULL_PTR;
    NAS_MM_FORB_TA_LIST_STRU             *pstForbRposTaiList = NAS_EMM_NULL_PTR;

    NAS_EMMC_GLOBAL_STRU               *pstEmmcInfo = VOS_NULL_PTR;

    pstEmmcInfo = NAS_EMMC_GetEmmcInfoAddr();
    pstMmUeId   = NAS_LMM_GetEmmInfoUeidAddr();

    if (NAS_EMM_NULL_PTR == pstLmmInfo)
    {
        NAS_LMM_PUBM_LOG_INFO("Nas_GetLteInfo:Input para invalid");
        TLPS_PRINT2LAYER_INFO(Nas_GetLteInfo_ENUM,LNAS_FUNCTION_LABEL1);
        return ulRslt;
    }

    NAS_LMM_MEM_SET_S(pstLmmInfo, sizeof(NAS_LMM_INFO_STRU), 0, sizeof(NAS_LMM_INFO_STRU));

    if (NAS_LMM_GUTI == ulInfoType)
    {
        /* leixiantiao 00258641 降低圈复杂度 2014-7-30 begin */
        ulRslt = NAS_LMM_GetLteGutiInfo(pstLmmInfo,pstMmUeId);
        /* leixiantiao 00258641 降低圈复杂度 2014-7-30 end */

    }
    else if (NAS_LMM_FORB_TAI_ROAM_LIST == ulInfoType)
    {
        pstForbRoamTaiList = NAS_LMM_GetEmmInfoNetInfoForbTaForRoamAddr();

        if (pstForbRoamTaiList->ulTaNum > MMC_LMM_MAX_FORB_ROAM_TAI_NUM)
        {
            pstLmmInfo->u.stForbRoamTaiList.ulTaNum = MMC_LMM_MAX_FORB_ROAM_TAI_NUM;
        }
        else
        {
            pstLmmInfo->u.stForbRoamTaiList.ulTaNum = pstForbRoamTaiList->ulTaNum;
        }

        NAS_LMM_MEM_CPY_S(  pstLmmInfo->u.stForbRoamTaiList.astTa,
                            sizeof(NAS_LMM_TAI_STRU) * MMC_LMM_MAX_FORB_ROAM_TAI_NUM,
                            pstForbRoamTaiList->astTa,
                            pstLmmInfo->u.stForbRoamTaiList.ulTaNum * sizeof(NAS_LMM_TAI_STRU));

        ulRslt = MMC_LMM_SUCC;
    }
    else if (NAS_LMM_FORB_TAI_RPOS_LIST == ulInfoType)
    {
        pstForbRposTaiList = NAS_LMM_GetEmmInfoNetInfoForbTaForRposAddr();

        if (pstForbRposTaiList->ulTaNum > MMC_LMM_MAX_FORB_RPOS_TAI_NUM)
        {
            pstLmmInfo->u.stForbRposTaiList.ulTaNum = MMC_LMM_MAX_FORB_RPOS_TAI_NUM;
        }
        else
        {
            pstLmmInfo->u.stForbRposTaiList.ulTaNum = pstForbRposTaiList->ulTaNum;
        }

        NAS_LMM_MEM_CPY_S(  pstLmmInfo->u.stForbRposTaiList.astTa,
                            sizeof(NAS_LMM_TAI_STRU) * MMC_LMM_MAX_FORB_ROAM_TAI_NUM,
                            pstForbRposTaiList->astTa,
                            pstLmmInfo->u.stForbRposTaiList.ulTaNum * sizeof(NAS_LMM_TAI_STRU));

        ulRslt = MMC_LMM_SUCC;
    }
    else if (NAS_LMM_RPLMN == ulInfoType)
    {
        if((NAS_EMM_AD_BIT_SLCT == NAS_EMM_GetLVRTaiOpBit()) &&
        (VOS_FALSE == NAS_LMM_CheckPlmnIsInvalid(NAS_LMM_GetEmmInfoLastRegPlmnAddr())))
        {
            NAS_LMM_PUBM_LOG_INFO("Nas_GetLteInfo:RPLMN VALID");
            TLPS_PRINT2LAYER_INFO(Nas_GetLteInfo_ENUM,LNAS_FUNCTION_LABEL2);
            NAS_LMM_MEM_CPY_S(          &pstLmmInfo->u.stPlmn,
                                        sizeof(MMC_LMM_PLMN_ID_STRU),
                                        NAS_LMM_GetEmmInfoLastRegPlmnAddr(),
                                        sizeof(NAS_MM_PLMN_ID_STRU));

            ulRslt = MMC_LMM_SUCC;
        }
        else
        {
            ulRslt = MMC_LMM_FAIL;
        }
    }
    else if (NAS_LMM_CS_DOMAIN_UNAVAILABLE_PLMN_LIST == ulInfoType)
    {
        NAS_LMM_MEM_CPY_S(  &pstLmmInfo->u.stCsDomainUnAvailPlmnList,
                            sizeof(MMC_LMM_PLMN_LIST_STRU),
                            &pstEmmcInfo->stRej18PlmnList,
                            sizeof(MMC_LMM_PLMN_LIST_STRU));

        ulRslt = MMC_LMM_SUCC;
    }
    else
    {
        NAS_LMM_PUBM_LOG_INFO("Nas_GetLteInfo:type is err!");
        TLPS_PRINT2LAYER_INFO(Nas_GetLteInfo_ENUM,LNAS_ERROR);
    }
    return ulRslt;

}

/*****************************************************************************
 Function Name   : Nas_GetEutraUeCap
 Description     : 获取LTE当前UE能力信息
 Input           : stPlmnId:当前PLMN信息
 Output          : pusEUeCapDataLen:ue能力长度
                    pucEUeCapData:ue能力信息，最长128字节
 Return          : NAS_LMM_SUCC
                   NAS_LMM_FAIL
 History         :
    1.w00151278      2012-05-15  Draft Enact

*****************************************************************************/
MMC_LMM_RESULT_ID_ENUM_UINT32  Nas_GetEutraUeCap(
    MMC_LMM_PLMN_ID_STRU stPlmnId, VOS_UINT16 *pusEUeCapDataLen, VOS_UINT8 *pucEUeCapData)
{
    LRRC_LNAS_PLMN_ID_STRU   stRrcNasPlmnId;

    NAS_LMM_MEM_SET_S(  &stRrcNasPlmnId,
                        sizeof(LRRC_LNAS_PLMN_ID_STRU),
                        0,
                        sizeof(LRRC_LNAS_PLMN_ID_STRU));

    stRrcNasPlmnId.aucPlmnId[0] = stPlmnId.aucPlmnId[0];
    stRrcNasPlmnId.aucPlmnId[1] = stPlmnId.aucPlmnId[1];
    stRrcNasPlmnId.aucPlmnId[2] = stPlmnId.aucPlmnId[2];

    if (LRRC_LNAS_SUCC != LRRC_GetEutraUeCap(stRrcNasPlmnId, pusEUeCapDataLen, pucEUeCapData))
    {
        return MMC_LMM_FAIL;
    }

    return MMC_LMM_SUCC;
}

/*****************************************************************************
 Function Name   : Nas_GetLrrcConnFailureFlag
 Description     : 获取rrc connection failure标识，LNAS提供给GU NAS调用
 Input           : None
 Output          : None
 Return          : VOS_TRUE表示标识有效，异系统到GU需要发起RAU
                   VOS_FALSE表示标识无效
 History         :
    1.l00150010      2013-11-02  Draft Enact

*****************************************************************************/
VOS_UINT32  Nas_GetLrrcConnFailureFlag( VOS_VOID )
{
    NAS_EMM_TRIGGER_TAU_RRC_REL_ENUM_UINT32      enTriggerTauRrcRel = NAS_EMM_TRIGGER_TAU_RRC_REL_NO;

    enTriggerTauRrcRel = NAS_LMM_GetEmmInfoTriggerTauRrcRel();

    NAS_LMM_PUBM_LOG1_INFO("Nas_GetLrrcConnFailureFlag:rrc rel flag:", enTriggerTauRrcRel);
    TLPS_PRINT2LAYER_INFO1(Nas_GetLrrcConnFailureFlag_ENUM,LNAS_EMM_RRC_REL_FLAG,enTriggerTauRrcRel);

    if (NAS_EMM_TRIGGER_TAU_RRC_REL_CONN_FAILURE == enTriggerTauRrcRel)
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}
/*****************************************************************************
 Function Name   : LRRC_LNAS_GetPowerOffFlag
 Description     : LRRC通过该接口获取EMM关机标识，用于判断LRRC收到的空口是否是关机detach
                   该标志在LMM收到MMC关机请求置上，在收到LRRC power off cnf、收到开机请求
                   或者等待LRRC power off cnf超时时清除
 Input           : None
 Output          : None
 Return          : 1 表示标识有效，即LMM正在关机过程中
                   0 表示标识无效
 History         :
    1.leixiantiao 00258641      2014-07-14  Draft Enact

*****************************************************************************/

VOS_UINT8 LRRC_LNAS_GetPowerOffFlag(VOS_VOID)
{
    return NAS_LMM_GetEmmInfoLtePowerOffFlag();
}

/*****************************************************************************
 Function Name   : LRRC_LNAS_IsDamConfitionSatisfied
 Description     : LRRC通过该接口获取是否需要使用DAM
 Input           : None
 Output          : Nones
 Return          : 1 表示需使用
                   0 表示不需使用
 History         :
    1.sunjitan 00193151      2014-07-14  Draft Enact
*****************************************************************************/

VOS_UINT8 LRRC_LNAS_IsDamConfitionSatisfied(VOS_VOID)
{
    return NAS_EMM_IsDamConfitionSatisfied();
}

/*****************************************************************************
 Function Name   : LRRC_LNAS_IsMsgContainsSMS
 Description     : LRRC通过该接口获取空口消息中是否含有短信内容
 Input           : None
 Output          : None
 Return          : 1 表示含有短信
                   0 表示不含有短信
 History         :
    1.zhaochen 00308719      2015-07-21  Draft Enact
*****************************************************************************/

VOS_UINT8 LRRC_LNAS_IsMsgContainsSMS(VOS_UINT32 ulMsgSize, VOS_UINT8 *pstMsg)
{
    return NAS_LMM_IsMsgContainsSMS(ulMsgSize, pstMsg);
}

/*lint +e961*/
/*lint +e960*/
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of 子系统+模块+文件名.c */
