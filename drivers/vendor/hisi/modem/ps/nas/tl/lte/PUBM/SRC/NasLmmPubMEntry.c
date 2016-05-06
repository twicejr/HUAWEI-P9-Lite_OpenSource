/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasLmmPubMEntry.c
    Description : EMM模块收到的所有外部PID的消息, 从这里入口
    History     :
      1.  Name+ID  yyyy-mm-dd  Draft Enact
      2.zhengjunyan 00148421   2010-12-30 添加ID_APP_MM_INQ_PLMN_SEL_REQ消息处理
      3.zhengjunyan 00148421   2011-05-28 文件名由 NasMmPubMEntry.c修改为
                                           NasLmmPubMEntry.c
******************************************************************************/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasLmmPubMInclude.h"
#include    "NasLmmPubMTimer.h"
#include    "NasLmmTest.h"
#include    "NasCommBuffer.h"
#include    "NasEmmAttDetInclude.h"
#include    "NasEmmSmsInterface.h"
#include    "NasMmlCtx.h"
#include    "omerrorlog.h"
#include    "NasEmmSecuOm.h"
#include    "TlPsDrv.h"
#include    "NasEmmSecuAuth.h"

#if (FEATURE_LPP == FEATURE_ON)
#include    "EmmLppInterface.h"
#include    "LmmLcsInterface.h"
#include    "NasEmmSsMsgProc.h"
#include    "NasEmmLppMsgProc.h"
#endif

#include    "NasMtaInterface.h"


/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASMMPUBMENTRY_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASMMPUBMENTRY_C
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
  3 Declare the local function
*****************************************************************************/
static  VOS_UINT32  NAS_LMM_PreProcRrcRelInd ( MsgBlock *        pMsg );
static  VOS_UINT32  NAS_LMM_PreProcMsgEsmEstReq     ( MsgBlock *        pMsg );
static  VOS_UINT32  NAS_LMM_PreProcIntraConn2IdleReq( MsgBlock *        pMsg );
static  VOS_UINT32  NAS_EMM_PreProcMsgEsmBearStatusReq( MsgBlock *     pMsg );
static  VOS_UINT32  NAS_EMM_PreProcMsgRrcErrInd( MsgBlock *            pMsg );
VOS_UINT32  NAS_LMM_PreProcMsgEsmDataReq( MsgBlock *          pMsg );
#if (FEATURE_PTM == FEATURE_ON)
VOS_UINT32 NAS_LMM_PreProcMsgEsmSaveErrlogInd(MsgBlock *     pMsg);
VOS_VOID  LNAS_InitErrLogGloInfo(LNAS_ERRLOG_GLO_INFO_STRU *pstErrlogGloInfo);
#endif

#if (FEATURE_LPP == FEATURE_ON)
VOS_UINT32 NAS_EMM_RcvLppMsgEstReq(MsgBlock *  pMsg);
VOS_UINT32 NAS_EMM_RcvLppMsgDataReq(MsgBlock *  pMsg);
#endif

#ifdef PS_ITT_PC_TEST
extern  VOS_UINT32 PS_NVIM_Init();
#endif
VOS_UINT32  NAS_LMM_PreProcInterOptIndMsg( MsgBlock  *pMsg );




NAS_LMM_COMM_ACT_STRU               g_astMmPreProcMap[] =
{
    /* MM_MSG_TYPE_ENUM_UINT32          NAS_LMM_COMM_ACTION_FUN */

    /*========== APP_MM_MSG ==========*/
    {ID_MMC_LMM_START_REQ,                         WUEPS_PID_MMC,              NAS_LMM_PreProcAppStartReq},
    {ID_MMC_LMM_STOP_REQ,                          WUEPS_PID_MMC,              NAS_LMM_PreProcAppStopReq},
    {ID_MMC_LMM_DETACH_REQ,                        WUEPS_PID_MMC,              NAS_LMM_PreProcAppDetReq},
    {ID_MMC_LMM_ATTACH_REQ,                        WUEPS_PID_MMC,              NAS_LMM_PreProcMsgAppMmAttachReq},

    /*========== SM_MM_MSG  ==========*/
    {ID_EMM_ESM_BEARER_STATUS_REQ,                 PS_PID_ESM,              NAS_EMM_PreProcMsgEsmBearStatusReq},
    {ID_EMM_ESM_BEARER_MODIFY_REQ,                 PS_PID_ESM,              NAS_EMM_PreProcMsgEsmBearModifyReq},
    {ID_EMM_ESM_EST_REQ,                           PS_PID_ESM,              NAS_LMM_PreProcMsgEsmEstReq},

    #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    {ID_EMM_ESM_CL_LOCAL_DETACH_NOTIFY,            PS_PID_ESM,              NAS_LMM_PreProcMsgEsmClLocalDetachNotify},
    #endif

    {ID_EMM_ESM_DATA_REQ,                          PS_PID_ESM,              NAS_LMM_PreProcMsgEsmDataReq},

    {ID_EMM_ESM_CLR_ESM_PROC_RES_NOTIFY,           PS_PID_ESM,              NAS_LMM_PreProcMsgEsmClrEsmPrcResNotify},

     #if (FEATURE_ON == FEATURE_DSDS)
     {ID_EMM_ESM_BEGIN_SESSION_NOTITY,             PS_PID_ESM,              NAS_LMM_PreProcDsdsBeginSessionNotify},
     {ID_EMM_ESM_END_SESSION_NOTITY,               PS_PID_ESM,              NAS_LMM_PreProcDsdsEndSessionNotify},
     #endif

    /*========== RRC_MM_MSG ==========*/
    {ID_LRRC_LMM_ERR_IND,                          PS_PID_ERRC,             NAS_EMM_PreProcMsgRrcErrInd},
    {ID_LRRC_LMM_REL_IND,                          PS_PID_ERRC,             NAS_LMM_PreProcRrcRelInd},
    {ID_LRRC_LMM_SYS_CFG_CNF,                      PS_PID_ERRC,             NAS_LMM_PreProcRrcSysCfgCnf},
    {ID_LRRC_LMM_UTRAN_MODE_CNF,                   PS_PID_ERRC,             NAS_LMM_PreProcRrcUtranModeCnf},
    {ID_LRRC_LMM_DATA_CNF,                         PS_PID_ERRC,             NAS_LMM_PreProcRrcDataCnf},

    {ID_LRRC_LMM_SUSPEND_REL_CNF,                  PS_PID_ERRC,             NAS_EMM_PreProcMsgRrcSuspendRelCnf},

    {ID_LRRC_LMM_EST_CNF,                          PS_PID_ERRC,             NAS_EMM_PreProcMsgRrcMmEstCnf},
    {ID_LRRC_LMM_REL_CNF,                          PS_PID_ERRC,             NAS_EMM_PreProcMsgRrcMmRelCnf},

    {ID_LRRC_LMM_SUSPEND_INFO_CHANGE_IND,          PS_PID_ERRC,             NAS_EMM_PreProcMsgRrcSuspendInfoChangeInd },
    {ID_LRRC_LMM_CELL_SIGN_REPORT_IND,             PS_PID_ERRC,             NAS_EMM_PreProcMsgRrcCellSignReportInd },
    {ID_LRRC_LMM_PAGING_IND,                       PS_PID_ERRC,             NAS_EMM_PreProcMsgRrcPagingInd},
    {ID_LRRC_LMM_UE_CAP_CHANGE_IND,                PS_PID_ERRC,             NAS_EMM_PreProcMsgUeCapChangeInd},
    /*========== MM_INTRA_MSG =========*/
    {ID_NAS_LMM_INTRA_EMMC_EMM_SYS_INFO_IND,        PS_PID_MM,              NAS_LMM_PreProcIntraSystemInfoInd},
    {ID_NAS_LMM_INTRA_EMMC_EMM_COVERAGE_LOST_IND,   PS_PID_MM,              NAS_LMM_PreProcIntraCoverageLostInd},
    {ID_NAS_LMM_INTRA_CONN2IDLE_REQ,                PS_PID_MM,              NAS_LMM_PreProcIntraConn2IdleReq},
    {ID_NAS_LMM_INTRA_TAU_REQ,                      PS_PID_MM,              NAS_LMM_PreProcIntraTauReq},


    /*========== MM_USIM_CNF ==========*/
    {USIMM_READFILE_CNF,                         WUEPS_PID_USIM,          NAS_LMM_MsNullSsNullReadingUsimMsgUsimCnf},
    {ID_MMC_LMM_USIM_STATUS_REQ,                   WUEPS_PID_MMC,           NAS_LMM_PreProcMsgUsimStatusInd},
    {NAS_LMM_TIMER_EXP_MSG_ET(TI_NAS_LMM_TIMER_WAIT_USIM_CNF),
                                                   VOS_PID_TIMER,           NAS_LMM_MsNullSsNullReadingUsimTimerExp},
    {USIMM_UPDATEFILE_CNF,                         WUEPS_PID_USIM,          NAS_LMM_PreProcUsimSetCnf},
    {USIMM_AUTHENTICATION_CNF,                   WUEPS_PID_USIM,          NAS_LMM_PreProcUsimAuthCnf},


    /*========== TIMER EXP ==========*/
    {NAS_LMM_TIMER_EXP_MSG_ET(TI_NAS_EMM_PTL_T3416),
                                                    VOS_PID_TIMER,          NAS_EMM_PreProcMsgT3416Exp},
    {NAS_LMM_TIMER_EXP_MSG_ET(TI_NAS_EMM_PTL_SWITCH_OFF_TIMER),
                                                    VOS_PID_TIMER,          NAS_EMM_PreProcMsgSwithOffTimerExp},

    {NAS_LMM_TIMER_EXP_MSG_ET(TI_NAS_EMM_STATE_DEL_FORB_TA_PROID),
                                                    VOS_PID_TIMER,          NAS_EMM_PreProcMsgDelForbTaTimerExpire},
    {NAS_LMM_TIMER_EXP_MSG_ET(TI_NAS_EMM_STATE_WAIT_SYSCFG_CNF_TIMER),
                                                    VOS_PID_TIMER,          NAS_EMM_PreProcMsgWaitSyscfgCnfTimerExpire},
    {NAS_LMM_TIMER_EXP_MSG_ET(TI_NAS_EMM_PTL_T3412),
                                                    VOS_PID_TIMER,          NAS_EMM_PreProcMsgT3412Exp},
    {NAS_LMM_TIMER_EXP_MSG_ET(TI_NAS_EMM_PTL_T3423),
                                                    VOS_PID_TIMER,          NAS_EMM_PreProcMsgT3423Exp},
    {NAS_LMM_TIMER_EXP_MSG_ET(TI_NAS_EMM_PTL_T3402),
                                                    VOS_PID_TIMER,          NAS_EMM_PreProcMsgT3402Exp},

    {NAS_LMM_TIMER_EXP_MSG_ET(TI_NAS_EMM_PTL_CSFB_DELAY), VOS_PID_TIMER,    NAS_EMM_PreProcMsgCsfbDelayTimerExp},
    {NAS_LMM_TIMER_EXP_MSG_ET(TI_NAS_EMM_MRRC_WAIT_RRC_CONN_CNF),
                                                    VOS_PID_TIMER,          NAS_EMM_PreProcMsgTIWaitRrcConnTO},
    {NAS_LMM_TIMER_EXP_MSG_ET(TI_NAS_EMM_MRRC_WAIT_RRC_REL_CNF),
                                                    VOS_PID_TIMER,          NAS_EMM_PreProcMsgTiWaitRrcRelTO},
    {NAS_LMM_TIMER_EXP_MSG_ET(TI_NAS_EMM_STATE_T3440),
                                                    VOS_PID_TIMER,          NAS_EMM_PreProcMsgWaitRrcRel3440TO},
    {NAS_LMM_TIMER_EXP_MSG_ET(TI_NAS_EMM_PTL_REATTACH_DELAY),
                                                    VOS_PID_TIMER,          NAS_EMM_PreProcMsgReAttachDelayTO},
    {NAS_LMM_TIMER_EXP_MSG_ET(TI_NAS_EMM_PTL_GRADUAL_FORB_TIMER),
                                                    VOS_PID_TIMER,          NAS_LMM_PreProcMsgGradualForbTimerExpire},
    {NAS_LMM_TIMER_EXP_MSG_ET(TI_NAS_EMM_PTL_GRADUAL_FORB_AGING_TIMER),
                                                    VOS_PID_TIMER,          NAS_LMM_PreProcMsgGradualForbAgingTimerExpire},
    /*========== CN MSG ==========*/
    {ID_LRRC_LMM_DATA_IND,                         PS_PID_ERRC,             NAS_LMM_PreProcrRrcDataInd},

    /*========== GMM =============*/
    {ID_GMM_LMM_RESEL_SECU_INFO_REQ,               WUEPS_PID_GMM,               NAS_LMM_PreProcReselSecuInfoReq},
    {ID_GMM_LMM_HO_SECU_INFO_REQ,                  WUEPS_PID_GMM,               NAS_LMM_PreProcHoSecuInfoReq},
    {ID_GMM_LMM_INFO_CHANGE_NOTIFY_REQ,            WUEPS_PID_GMM,               NAS_LMM_PreProcInfoChangeNotifyReq},
     #if (FEATURE_ON == FEATURE_DSDS)
     {ID_GMM_LMM_BEGIN_SESSION_NOTIFY,             WUEPS_PID_GMM,           NAS_LMM_PreProcDsdsBeginSessionNotify},
     {ID_GMM_LMM_END_SESSION_NOTIFY,               WUEPS_PID_GMM,           NAS_LMM_PreProcDsdsEndSessionNotify},
     #endif

    /*========== MMC =============*/
    {ID_MMC_LMM_REL_REQ,                           WUEPS_PID_MMC,           NAS_LMM_PreProcMmcRelReq},
    {ID_MMC_LMM_SYS_CFG_REQ,                       WUEPS_PID_MMC,           NAS_LMM_PreProcMmcSysCfgReq},
    {ID_MMC_LMM_UTRAN_MODE_REQ,                    WUEPS_PID_MMC,           NAS_LMM_PreProcMmcUtranModeReq},
    {ID_MMC_LMM_DISABLE_LTE_NOTIFY,                WUEPS_PID_MMC,           NAS_LMM_PreProcMmcDisableReq},
    {ID_MMC_LMM_ENABLE_LTE_NOTIFY,                 WUEPS_PID_MMC,           NAS_LMM_PreProcMmcEnableReq},

    {ID_MMC_LMM_UE_OOC_STATUS_NOTIFY,              WUEPS_PID_MMC,           NAS_LMM_PreProcMmcOocStateReq},

    {ID_MMC_LMM_IMS_VOICE_CAP_CHANGE_NOTIFY,       WUEPS_PID_MMC,           NAS_LMM_PreProcMmcImsVoiceCapChangeNotify},

     #if (FEATURE_ON == FEATURE_DSDS)
     {ID_MMC_LMM_BEGIN_SESSION_NOTIFY,             WUEPS_PID_MMC,           NAS_LMM_PreProcDsdsBeginSessionNotify},
     {ID_MMC_LMM_END_SESSION_NOTIFY,               WUEPS_PID_MMC,           NAS_LMM_PreProcDsdsEndSessionNotify},
     #endif

    {ID_MMC_LMM_CELL_SIGN_REPORT_NOTIFY,           WUEPS_PID_MMC,           NAS_LMM_PreProcMmcCellSignReportNotify},

    {ID_MMC_LMM_VOICE_DOMAIN_CHANGE_IND,           WUEPS_PID_MMC,           NAS_LMM_PreProcMmcImsVoiceDomainChangeInd},
    {ID_MMC_LMM_CS_CONN_STATUS_NOTIFY,              WUEPS_PID_MMC,           NAS_LMM_PreProcMmcCsConnStatusNotify},
    /*========== SUSPEND =========*/
    {ID_MMC_LMM_SUSPEND_REQ,                       WUEPS_PID_MMC,           NAS_EMM_PreProcMsgMmcSuspendReq},
    {ID_LRRC_LMM_SUSPEND_IND,                      PS_PID_ERRC,             NAS_EMM_PreProcMsgRrcSuspendInd},
    {ID_MMC_LMM_ACTION_RESULT_REQ,                 WUEPS_PID_MMC,           NAS_EMM_PreProcMsgMmcActionRstReq},

    /*========== ERABM ==============*/
    {ID_EMM_ERABM_DRB_SETUP_IND,                   PS_PID_RABM,             NAS_EMM_PreProcMsgRabmDrbSetupInd},

    /*========== SMS ==============*/
    {ID_SMS_LMM_EST_REQ,                           WUEPS_PID_SMS,           NAS_EMM_PreProcMsgSmsEstReq},
    {ID_SMS_LMM_DATA_REQ,                          WUEPS_PID_SMS,           NAS_EMM_PreProcMsgSmsDataReq},

    /*========== MM ==============*/
    {ID_MM_LMM_CSFB_SERVICE_START_NOTIFY,          WUEPS_PID_MM,            NAS_EMM_PreProcMsgMmCsfbSerStartNotify},
    {ID_MM_LMM_CSFB_SERVICE_ABORT_NOTIFY,          WUEPS_PID_MM,            NAS_EMM_PreProcMsgMmCsfbSerAbortNotify},

    {ID_MM_LMM_HO_SECU_INFO_REQ,                   WUEPS_PID_MM,            NAS_LMM_PreProcMsgMmHoSecuInfoReq},

    {ID_MM_LMM_SRVCC_STATUS_NOTIFY,                WUEPS_PID_MM,           NAS_LMM_PreProcMsgSrvccNofify},

     #if (FEATURE_ON == FEATURE_DSDS)
     {ID_MM_LMM_BEGIN_SESSION_NOTIFY,              WUEPS_PID_MM,            NAS_LMM_PreProcDsdsBeginSessionNotify},
     {ID_MM_LMM_END_SESSION_NOTIFY,                WUEPS_PID_MM,            NAS_LMM_PreProcDsdsEndSessionNotify},
     #endif

    /*========== GMM ==============*/
    {ID_GMM_LMM_TIMER_STATE_NOTIFY,          WUEPS_PID_GMM,            NAS_EMM_PreProcMsgGmmTimerStateNotifyMsg},

    {ID_OM_EMM_INFO_REPORT_REQ,                  MSP_PID_DIAG_APP_AGENT,  NAS_EMM_OmInfoIndMsgProc },

    /*========== OM ==============*/
    #if (FEATURE_PTM == FEATURE_ON)
    {ID_OM_FTM_CTRL_IND,                         MSP_PID_DIAG_APP_AGENT,             NAS_LMM_RevOmFtmCtrlMsg},
    {ID_OM_LNAS_ERR_LOG_CTRL_IND,                MSP_PID_DIAG_APP_AGENT,             NAS_LMM_RevOmErrlogCtrlMsg},
    {ID_OM_LNAS_ERR_LOG_REPORT_REQ,              MSP_PID_DIAG_APP_AGENT,             NAS_LMM_RevOmReadErrlogReq},
    {ID_EMM_ESM_SAVE_ERRLOG_IND,                 PS_PID_ESM,                         NAS_LMM_PreProcMsgEsmSaveErrlogInd},
    #endif
    {ID_MMC_LMM_OTHER_MODEM_INFO_NOTIFY,          WUEPS_PID_MMC,           NAS_LMM_RevMmcModemInfoReq},

    {ID_LRRC_LMM_INTER_OPT_IND,                   PS_PID_ERRC,             NAS_LMM_PreProcInterOptIndMsg},
    #if (FEATURE_LPP == FEATURE_ON)
    {ID_LPP_LMM_EST_REQ,                          PS_PID_LPP,              NAS_EMM_RcvLppMsgEstReq},
    {ID_LPP_LMM_DATA_REQ,                         PS_PID_LPP,              NAS_EMM_RcvLppMsgDataReq},

    /* LCS模块PID变更为WUEPS_PID_LCS */
    {ID_LCS_LMM_EST_REQ,                          WUEPS_PID_LCS,           NAS_EMM_RcvLcsMsgEstReq},
    {ID_LCS_LMM_DATA_REQ,                         WUEPS_PID_LCS,           NAS_EMM_RcvLcsMsgDataReq},
    #endif
    {ID_MTA_LNAS_SET_UE_CENTER_REQ,               UEPS_PID_MTA,            NAS_EMM_RcvMtaSetUECenterReq},
    {ID_MTA_LNAS_QRY_UE_CENTER_REQ,               UEPS_PID_MTA,            NAS_EMM_RcvMtaQryUECenterReq}

};

static VOS_UINT32   g_astMmPreProcMapNum
        = sizeof(g_astMmPreProcMap)/sizeof(NAS_LMM_COMM_ACT_STRU);
VOS_UINT32 g_ulSendMsgCounter = 0;
NAS_LMM_USIM_FILE_TYPE_ENUM_UINT32 g_enReadUsimFileType;
/*****************************************************************************
  3 Function
*****************************************************************************/


/*****************************************************************************
 Function Name  : MM_FidInit
 Discription    : mm的FID初始化函数
 Input          :
 Output         : None
 Return         : None
 History:
      1.  韩鲁峰 41410  yyyy-mm-dd  Draft Enact
*****************************************************************************/
VOS_UINT32 MM_FidInit ( enum VOS_INIT_PHASE_DEFINE ip )
{
    VOS_UINT32                              ulRet = 0;

    (VOS_VOID)ulRet;
    (VOS_VOID)ip;
    #if (VOS_OS_VER == VOS_WIN32)/*在PC环境下，才会调用PID初始化函数，单板环境下，由GU MM负责初始化*/
    switch( ip )
    {
        case    VOS_IP_LOAD_CONFIG:

                ulRet = VOS_RegisterPIDInfo(PS_PID_MM,
                                            NAS_MM_PidInit,
                                            NAS_MM_PidMsgEntry);
                if( VOS_OK != ulRet )
                {
                    return VOS_ERR;
                }

                ulRet = VOS_RegisterPIDInfo(WUEPS_PID_MMC,
                                            NAS_MMC_PidInit,
                                            NAS_MmcStub_TaskEntry);
                if( VOS_OK != ulRet )
                {
                    return VOS_ERR;
                }

                ulRet = VOS_RegisterPIDInfo(WUEPS_PID_GMM,
                                            NAS_GMM_PidInit,
                                            NAS_GmmStub_TaskEntry);
                if( VOS_OK != ulRet )
                {
                    return VOS_ERR;
                }

                ulRet = VOS_RegisterPIDInfo(WUEPS_PID_MM,
                                            NAS_GUMM_PidInit,
                                            NAS_GUMmStub_TaskEntry);
                if( VOS_OK != ulRet )
                {
                    return VOS_ERR;
                }

                ulRet = VOS_RegisterPIDInfo(WUEPS_PID_SMS,
                                            NAS_SMS_PidInit,
                                            NAS_SmsStub_TaskEntry);
                if( VOS_OK != ulRet )
                {
                    return VOS_ERR;
                }
                ulRet = VOS_RegisterMsgTaskPrio(PS_FID_MM, VOS_PRIORITY_M4);
                if( PS_SUCC != ulRet )
                {
                    return ulRet;
                }
                break;

        case    VOS_IP_FARMALLOC:
        case    VOS_IP_INITIAL:
        case    VOS_IP_ENROLLMENT:
        case    VOS_IP_LOAD_DATA:
        case    VOS_IP_FETCH_DATA:
        case    VOS_IP_STARTUP:
        case    VOS_IP_RIVAL:
        case    VOS_IP_KICKOFF:
        case    VOS_IP_STANDBY:
        case    VOS_IP_BROADCAST_STATE:
        case    VOS_IP_RESTART:
        case    VOS_IP_BUTT:
                break;

        default:
                break;
    }
    #endif

    return VOS_OK;
}

/*****************************************************************************
 Function Name  : EMM_PidInit
 Discription    : emm的PID初始化函数
 Input          :
 Output         : None
 Return         : None
 History:
      1.  韩鲁峰 41410  yyyy-mm-dd  Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_MM_PidInit ( enum VOS_INIT_PHASE_DEFINE ip )
{

    switch( ip )
    {
        case    VOS_IP_LOAD_CONFIG:
                {
                    /*NAS_EMMC_FsmReg();*/
                    NAS_EMM_FsmReg();
                    NAS_LMM_SECU_FsmReg();

                    /*上电开机需将T3402设置为默认值12min*/
                    g_ulEmmT3402length = NAS_LMM_TIMER_T3402_LEN;

                    /*创建 NVIM 桩文件，读取文件长度*/
                    #ifdef PS_ITT_PC_TEST
                        PS_NVIM_Init();
                    #endif
                }
                break;

        case    VOS_IP_FARMALLOC:
                break;
        case    VOS_IP_INITIAL:
                {
                    NAS_LMM_PUBM_LOG_NORM(
                    "===============================================");
                    NAS_LMM_PUBM_LOG_NORM(
                    "NAS_LMM                            START INIT...");
                    TLPS_PRINT2LAYER_INFO(NAS_MM_PidInit_ENUM,LNAS_BEGIN);
                    /*PUBM,MMC,EMM模块初始化,EMM初始化必须在MMC之前*/
                    NAS_LMM_PUBM_Init_FidInit();
                }
                break;
        case    VOS_IP_ENROLLMENT:
        case    VOS_IP_LOAD_DATA:
        case    VOS_IP_FETCH_DATA:
        case    VOS_IP_STARTUP:
        case    VOS_IP_RIVAL:
        case    VOS_IP_KICKOFF:
        case    VOS_IP_STANDBY:
        case    VOS_IP_BROADCAST_STATE:
        case    VOS_IP_RESTART:
        case    VOS_IP_BUTT:
                break;

        default:
                break;
    }

    return VOS_OK;
}


/*****************************************************************************
 Function Name  :
 Discription    : NAS_LMM 注册给dopra的消息处理函数
 Input          :
 Output         : None
 Return         : None
 History:
      1.  Name+ID  yyyy-mm-dd  Draft Enact
*****************************************************************************/
void    NAS_MM_PidMsgEntry( MsgBlock *pMsg)
{
    VOS_UINT32                          ulRst;
    /*如果消息为空*/
    if(NAS_LMM_NULL_PTR == pMsg)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_MM_PidMsgEntry: BUF_MSG is NULL_PTR");
        TLPS_PRINT2LAYER_ERROR(NAS_MM_PidMsgEntry_ENUM,LNAS_NULL_PTR);
        return;
    }

#if (VOS_WIN32 != VOS_OS_VER)
    TLPS_ExcLog_SaveMsgList(pMsg);
#endif

    /* 进入 函数 NAS_LMM_Entry   */
    ulRst = NAS_LMM_Entry(pMsg);
/*    NAS_LMM_PUBM_LOG1_INFO("NAS_MM_PidMsgEntry: ulRst = ", ulRst);*/
    (VOS_VOID)(ulRst);

    return;
}



/*****************************************************************************
 Function Name  : NAS_LMM_Entry
 Discription    : NAS_LMM层入口函数,包括MMC模块和EMM模块
 Input          :
 Output         : None
 Return         : 完成该消息的流程处理
                  该消息需要缓存
                  丢弃该消息
 History:
      1.  Name+ID  yyyy-mm-dd  Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LMM_Entry(MsgBlock *pMsg)
{
    VOS_UINT32                          ulRst;
    NAS_EMM_EVENT_TYPE_ENUM_UINT32      ulEt;
    /*z00282933，多模OM融合添加 - BEGIN*/
    #if (VOS_WIN32 != VOS_OS_VER)
    DIAG_TRANS_IND_STRU stDiagTransInd;
    #endif
    /*z00282933, 多模OM融合添加 - END*/

    /*如果是空口消息则解保护，其他消息不处理*/
    ulRst = NAS_EMM_SecuUnProtect(pMsg);
    if(NAS_EMM_NOT_GO_INTO_EMM_FSM == ulRst)
    {
        NAS_LMM_PUBM_LOG_NORM("NAS_LMM_Entry:UnProt Err OR SMC Finish.");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_Entry_ENUM,LNAS_FUNCTION_LABEL1);
        return ulRst;
    }

    /* 对在处理接收到的消息之前，先获取EventType */
    ulRst = NAS_LMM_GetEventType(pMsg, &ulEt);
    if(NAS_EMM_FAIL == ulRst)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_Entry: WARN, Get Event Type ERR !!");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_Entry_ENUM,LNAS_FUNCTION_LABEL2);
        return  ulRst;
    }
    /* 保存消息队列,用于复位分析 */
    NAS_EMM_SaveRecvMsgList((VOS_VOID *)pMsg);

    /* 进入MMC和EMM状态机处理 */
    ulRst = NAS_LMM_MsgHandle(pMsg, ulEt);

    /* 然后MM内部消息处理 */
    ulRst = NAS_LMM_IntraMsgProcess();

    /*开始buff的处理*/
    ulRst = NAS_LMM_BufMsgProcess();


    /* 如果EMM模块的维护信息发生变化，则更新用于上报EMM信息的全局变量，
    同时将最新的信息上报 */
    if (OM_EMM_REPORT_INFO_OPEN == g_NasEmmOmInfoIndFlag )
    {
        if (NAS_EMM_FAIL == NAS_LMM_CompareEmmInfo())
        {
            /*z00282933，多模OM融合添加 - BEGIN*/
            #if (VOS_WIN32 != VOS_OS_VER)

            NAS_LMM_MEM_SET_S(  &stDiagTransInd,
                                sizeof(DIAG_TRANS_IND_STRU),
                                0,
                                sizeof(DIAG_TRANS_IND_STRU));

            stDiagTransInd.ulMsgId = DIAG_CMD_EMM_APP_EMM_INFO_IND;
            stDiagTransInd.ulLength = sizeof(OM_EMM_STATE_INFO_STRU);
            stDiagTransInd.pData = (VOS_VOID *)(&g_stEmmOmInfo);
            stDiagTransInd.ulModule = LPS_OM_ID(PS_PID_MM, PS_PRINT_INFO);
            stDiagTransInd.ulPid = PS_PID_MM;

            /* 通过DIAG上报 */
            (VOS_VOID)LDRV_DIAG_COMMONREPORT(&stDiagTransInd);
            #endif
            /*z00282933, 多模OM融合添加 - END*/
        }
    }

    /*EMM模块需要上报路测的信息有变的话，则主动上报*/
    NAS_LMM_DtJudgeifNeedRpt();
    #if (FEATURE_PTM == FEATURE_ON)
    NAS_LMM_OmInfoIndProc();
    #endif
    /* EMM消息处理完推送打印 */
    TLPS_SendPrintBufferInfo();
    return  ulRst;
}


/*****************************************************************************
 Function Name   : NAS_LMM_MsgHandle
 Description     : 消息进入MMC和EMM状态机处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.h41410      2008-10-10  Draft Enact
    2.h41410      2009-05-07  采用UE的思路，先进EMM处理
    3.X00148705   2009-08-17  添加对消息缓存的处理
    4.X00148705   2009-10-22  添加打印,提示当前收到的消息没有被处理
*****************************************************************************/
VOS_UINT32  NAS_LMM_MsgHandle(           MsgBlock *          pMsg,
                                        VOS_UINT32          ulEventType)
{
    VOS_UINT32                          ulRst;
    VOS_UINT32                          ulProcessFlag;

    /* MM层预处理 */
    ulRst = NAS_LMM_MsgPreProcess(pMsg);

    /* 若状态机中处理发现该消息需要缓存，则缓存 */
    if( (NAS_LMM_STORE_HIGH_PRIO_MSG == ulRst) ||
        (NAS_LMM_STORE_MID_PRIO_MSG  == ulRst) ||
        (NAS_LMM_STORE_LOW_PRIO_MSG  == ulRst))
    {

        NAS_LMM_PUBM_LOG_NORM("NAS_LMM_MsgHandle: PreProcess Store Msg !!");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_MsgHandle_ENUM,LNAS_FUNCTION_LABEL1);
        ulProcessFlag               = ulRst;
        ulRst = NAS_LMM_StoreMsgToQue(NAS_LMM_PARALLEL_FSM_EMM,
                                        ulProcessFlag,
                                        ulEventType,
                                        (VOS_VOID *)pMsg);
    }

    /*如果该消息被预处理模块处理了,则不再进入EMM模块处理*/
    if ( NAS_LMM_MSG_DISCARD == ulRst)
    {
        ulRst = NAS_EMM_MsgProcessInFsm(pMsg, ulEventType );

        /* 若状态机中处理发现该消息需要缓存，则缓存 */
        if( (NAS_LMM_STORE_HIGH_PRIO_MSG == ulRst) ||
            (NAS_LMM_STORE_MID_PRIO_MSG  == ulRst) ||
            (NAS_LMM_STORE_LOW_PRIO_MSG  == ulRst))
        {
            ulProcessFlag               = ulRst;
            ulRst = NAS_LMM_StoreMsgToQue(NAS_LMM_PARALLEL_FSM_EMM,
                                            ulProcessFlag,
                                            ulEventType,
                                            (VOS_VOID *)pMsg);
        }
    }

    /*如果该消息被EMM模块处理了,则不再进入MMC模块处理*/
    if( NAS_LMM_MSG_DISCARD == ulRst)
    {
        ulRst = NAS_EMMC_MsgDistr(pMsg);

    }

    /* 打印提示当前收到的消息没有被EMM处理
    */
    if ( NAS_LMM_MSG_DISCARD == ulRst)
    {
        NAS_LMM_PUBM_LOG_NORM("NAS_LMM_MsgHandle: Current Receive Message Is Discarded !!");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_MsgHandle_ENUM,LNAS_FUNCTION_LABEL2);
    }
    return ulRst;
}




/*****************************************************************************
 Function Name   : NAS_LMM_GetEventType
 Description     : MM层收到的消息，计算出EVENT TYPE
 Input           : pMsg
 Output          : pulEt
 Return          : NAS_EMM_SUCC : 计算成功
                   NAS_EMM_FAIL : 计算失败
 History         :
    1.h41410      2008-9-25  Draft Enact

*****************************************************************************/
/*lint -e960*/
/*lint -e961*/
VOS_UINT32  NAS_LMM_GetEventType(        MsgBlock                        *pMsg,
                                        NAS_EMM_EVENT_TYPE_ENUM_UINT32  *pulEmmEt )
{
    REL_TIMER_MSG                      *pTimerMsg;
    NAS_LMM_PID_MSG_STRU                *pMmPidMsg;
    LRRC_LMM_DATA_IND_STRU               *pRrcMmDataIndMsg;
    VOS_UINT32                          ulMmCnMsgType;


    pMmPidMsg                           = (NAS_LMM_PID_MSG_STRU *)pMsg;
    pRrcMmDataIndMsg                    = (LRRC_LMM_DATA_IND_STRU *)pMsg;


    /* 若接收模块不是MM */
    if( PS_PID_MM != pMmPidMsg->ulReceiverPid)
    {

        /* 若不是超时消息，打印RCV_PID, PS_PID_MM, 和消息ID */
        if( VOS_PID_TIMER != pMmPidMsg->ulSenderPid)
        {
            NAS_LMM_PUBM_LOG3_ERR("NAS_LMM_GetEventType, Rcv_pid err!! Rcv_pid =, PS_PID_MM =, MsgId = ",
                                            pMsg->ulReceiverPid,
                                            PS_PID_MM,
                                            pMmPidMsg->ulMsgId);
            TLPS_PRINT2LAYER_INFO1(NAS_LMM_GetEventType_ENUM,LNAS_FUNCTION_LABEL1,
                                            pMsg->ulReceiverPid);
            TLPS_PRINT2LAYER_INFO2(NAS_LMM_GetEventType_ENUM,LNAS_FUNCTION_LABEL2,
                                            PS_PID_MM,
                                            pMmPidMsg->ulMsgId);
        }
        else
        {   /* 否则，打印RCV_PID, PS_PID_MM,  */
            NAS_LMM_PUBM_LOG2_ERR("NAS_LMM_GetEventType, TIMER MSG Rcv_pid err!! Rcv_pid =, PS_PID_MM =",
                                            pMsg->ulReceiverPid,
                                            PS_PID_MM);
            TLPS_PRINT2LAYER_ERROR2(NAS_LMM_GetEventType_ENUM,LNAS_FUNCTION_LABEL3,
                                            pMsg->ulReceiverPid,
                                            PS_PID_MM);
        }

        return  NAS_EMM_FAIL;
    }

    /*输出当前MM和MMC的主状态和子状态*/
    NAS_LMM_PUBM_LOG_NORM("\n");
    NAS_LMM_PUBM_LOG_NORM("======NAS_EMM Current State:======");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_GetEventType_ENUM,LNAS_FUNCTION_LABEL4);
    NAS_LMM_PrintFsmState(NAS_LMM_PARALLEL_FSM_EMM);
    /*NAS_LMM_PrintFsmState(NAS_LMM_PARALLEL_FSM_MMC);*/

    /* 打印消息ID */
    NAS_LMM_PUBM_PrintRevMsg((const PS_MSG_HEADER_STRU *)pMmPidMsg,
                             NAS_COMM_GET_MM_PRINT_BUF());



    /*打印消息码流*/
    NAS_LMM_PUBM_LOG_NORM("====================IN MSG CONTENT is : ============");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_GetEventType_ENUM,LNAS_FUNCTION_LABEL5);
    NAS_COMM_PrintArray(             NAS_COMM_GET_MM_PRINT_BUF(),
                                     (VOS_UINT8 *)pMmPidMsg,
                                     (pMmPidMsg->ulLength + NAS_EMM_LEN_VOS_MSG_HEADER));
    NAS_LMM_PUBM_LOG_NORM("====================================================");

    /* 若是超时消息 */
    if( VOS_PID_TIMER == pMmPidMsg->ulSenderPid)
    {

        pTimerMsg                       = (REL_TIMER_MSG *)pMsg;
        (*pulEmmEt)                     = NAS_LMM_TIMER_EXP_MSG_ET(pTimerMsg->ulName);

    }
    else
    {
        /* 所有收到消息, pMmPidMsg中的BYTE4 清为0 */
        *pulEmmEt = pMmPidMsg->ulMsgId  & NAS_LMM_MSGID_DPID_POS;

        /* 若是RRC发来的 带有CN消息的消息，将pMmPidMsg中的BYTE4改为CNMT: CN Msg Type */
        if(ID_LRRC_LMM_DATA_IND == pMmPidMsg->ulMsgId)
        {

            /* 获取CN 的MSG_TYPE */
            ulMmCnMsgType   = pRrcMmDataIndMsg->stNasMsg.aucNasMsg[NAS_LMM_CN_MSG_MT_POS];

            /* 将pMmPidMsg中的BYTE4改为CNMT: CN Msg Type */
            ulMmCnMsgType   = ulMmCnMsgType<<NAS_LMM_MOVEMENT_24_BITS;
            (*pulEmmEt)     = (*pulEmmEt)| ulMmCnMsgType;

            /* 若是 ID_LRRC_LMM_DATA_IND 消息，打印 CN消息码流 */
            NAS_LMM_PrintCnMsgAndData(&(pRrcMmDataIndMsg->stNasMsg));
/*            NAS_LMM_PrintCnMsg(pRrcMmDataIndMsg);*/
        }

        /*如果是内部空口消息，伪装为真正的空口消息*/
        if(ID_NAS_LMM_INTRA_DATA_IND == pMmPidMsg->ulMsgId)
        {
            *pulEmmEt = ID_LRRC_LMM_DATA_IND & NAS_LMM_MSGID_DPID_POS;

            /* 获取CN 的MSG_TYPE */
            ulMmCnMsgType   = pRrcMmDataIndMsg->stNasMsg.aucNasMsg[NAS_LMM_INTRA_DATA_IND_MT_POS];

            /* 将pMmPidMsg中的BYTE4改为CNMT: CN Msg Type */
            ulMmCnMsgType   = ulMmCnMsgType<<NAS_LMM_MOVEMENT_24_BITS;
            (*pulEmmEt)     = (*pulEmmEt)| ulMmCnMsgType;
        }

    }
    /*把主要信息和其它信息再空一行*/
/*    NAS_LMM_PUBM_LOG_INFO("\n");*/

    /*
    NAS_LMM_PUBM_LOG_INFO(".......................................................................................................................................................");
    NAS_LMM_PrintFsmState(NAS_LMM_PARALLEL_FSM_EMM);
    NAS_LMM_PrintFsmState(NAS_LMM_PARALLEL_FSM_MMC);
    NAS_LMM_PUBM_LOG_INFO(".......................................................................................................................................................");
    */
    return  NAS_EMM_SUCC;
}


/*******************************************************************************
  Module   :
  Function : NAS_LMM_SendRabmRrcConRelInd
  Input    :
  Output   :
  NOTE     :
  Return   :
  History  :
    1.  lihong  00150010  2009.06.01  新规作成
    2.  leixiantiao 00258641
*******************************************************************************/
VOS_VOID    NAS_LMM_SendRabmRrcConRelInd(EMM_ERABM_REL_CAUSE_ENUM_UINT32      enRelCause)
{
    EMM_ERABM_RRC_CON_REL_IND_STRU      *pRabmRrcConRelIndMsg    = NAS_EMM_NULL_PTR;

    NAS_LMM_PUBM_LOG_NORM( "NAS_LMM_SendRabmRrcConRelInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_SendRabmRrcConRelInd_ENUM,LNAS_ENTRY);

    /* 申请DOPRA消息 */
    pRabmRrcConRelIndMsg = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(EMM_ERABM_RRC_CON_REL_IND_STRU));

    if(NAS_EMM_NULL_PTR == pRabmRrcConRelIndMsg)
    {
        return;
    }

    /* 填写EMM_RABM_RRC_CON_REL_IND 的DOPRA消息头 */
    EMM_COMP_ERABM_MSG_HEADER(pRabmRrcConRelIndMsg, sizeof(EMM_ERABM_RRC_CON_REL_IND_STRU) -
                                        EMM_LEN_VOS_MSG_HEADER);

    /* 填写EMM_RABM_RRC_CON_REL_IND 的消息ID标识 */
    pRabmRrcConRelIndMsg->ulMsgId           = ID_EMM_ERABM_RRC_CON_REL_IND;
    pRabmRrcConRelIndMsg->enRelCause        = enRelCause;

    /* 发送消息(Send the msg of) EMM_RABM_RRC_CON_REL_IND */
    NAS_LMM_SEND_MSG(                       pRabmRrcConRelIndMsg);

    return;

}

/*****************************************************************************
 Function Name   : NAS_EMM_TcSendRelInd
 Description     : 向TC发送ID_EMM_ETC_DATA_IND消息
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1. wangchen 00209181    2013-11-12   Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_TcSendRelInd(VOS_VOID)
{
    EMM_ETC_REL_IND_STRU                *pEmmTcRelIndMsg = VOS_NULL_PTR;

    pEmmTcRelIndMsg = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(EMM_ETC_REL_IND_STRU));


    /*判断申请结果，若失败退出*/
    if (NAS_EMM_NULL_PTR == pEmmTcRelIndMsg)
    {
        return;
    }

    /*构造ID_EMM_ETC_REL_IND消息*/
    /*填充消息头*/
    NAS_EMM_COMP_AD_TC_MSG_HEADER(pEmmTcRelIndMsg, sizeof(EMM_ETC_REL_IND_STRU) -
                                        EMM_LEN_VOS_MSG_HEADER);

    /*填充消息ID*/
    pEmmTcRelIndMsg->ulMsgId         = ID_EMM_ETC_REL_IND;


    /*向TC发送ID_EMM_ETC_REL_IND消息*/
    NAS_LMM_SEND_MSG(                   pEmmTcRelIndMsg);

    /* 打印发送消息 */
    NAS_LMM_PUBM_LOG_NORM("NAS_EMM_TcSendRelInd:NORM:Send ID_EMM_ETC_REL_IND!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TcSendRelInd_ENUM,LNAS_FUNCTION_LABEL1);
}

/*****************************************************************************
 Function Name   : NAS_LMM_PreProcIntraConn2IdleReq
 Description     : 1)将NAS连接态从CONN修改为IDLE
                   2)断开安全连接
                   3)通知RABM RRC_CONN_REL_IND
                   4)根据当前状态，启动T3412
                   该消息不进状态机处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2009-9-28  Draft Enact
    2.zhengjunyan 00148421      2010-2-26  BJ9D02767
    3.lihong00150010            2012-12-18 Modify:Emergency
*****************************************************************************/
static VOS_UINT32  NAS_LMM_PreProcIntraConn2IdleReq( MsgBlock *          pMsg )
{
    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_PreProcIntraConn2IdleReq is enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcIntraConn2IdleReq_ENUM,LNAS_ENTRY);

    ( VOS_VOID )pMsg;

    /*通知 RABM:RRC_CONN_REL_IND*/
    /* 从内部释放消息处理中移出到LRRC REL IND，EMM主动释放处理中 */
    /* NAS_LMM_SendRabmRrcConRelInd(); */

    /*检查当前状态，启动T3412*/
    if(EMM_MS_REG == NAS_LMM_GetEmmCurFsmMS())
    {
        NAS_LMM_StartInactivePtlTimer(TI_NAS_EMM_PTL_T3412);

        /*通知GU模T3412停止*/
        NAS_EMM_SendTimerStateNotify(TI_NAS_EMM_PTL_T3412, LMM_MMC_TIMER_START);
    }

    /*停止T3416，删除RAND和RES*/
    if((EMM_MS_DEREG == NAS_LMM_GetEmmCurFsmMS())
         || NAS_RELEASE_R11)
    {
        NAS_LMM_StopPtlTimer(            TI_NAS_EMM_PTL_T3416);
        NAS_EMM_SecuClearRandRes();
    }

    /*保存安全上下文和PSLOC(GUTI,LVR TAI,EU)信息*/
    /*NAS_LMM_WriteEpsSecuContext(NAS_NV_ITEM_UPDATE);*/
    /*NAS_LMM_WritePsLoc(NAS_NV_ITEM_UPDATE);*/

    /* 由于RRC链路释放原因值的缓存消息不删除，在后面收到系统消息时需要重发 */
    NAS_EMM_ClrAllUlDataReqBufferMsgExceptConnRelWaitSysInfoMsg();

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_LMM_PreProcRrcRelInd
 Description     : RRC_REL_IND消息的预处理函数:
                   IDLE模式下收到RRC_REL_IND消息，如果是正在建链期间，则进入状态
                   机处理，其他情况下直接丢弃；
                   CONN模式下收到RRC_REL_IND消息，直接进入状态机处理。
 Input           : MsgBlock
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.X00148705      2009-9-25  Draft Enact
    2.lifuxin 00253982 2014.10.29 建链重构
*****************************************************************************/
static VOS_UINT32  NAS_LMM_PreProcRrcRelInd(    MsgBlock *          pMsg )
{
    VOS_UINT32                          ulRet = NAS_LMM_MSG_DISCARD;
    LRRC_LMM_REL_IND_STRU              *pLrrcRelInd;

    pLrrcRelInd = (LRRC_LMM_REL_IND_STRU*)pMsg;
    /* 由LRRC释放时关闭CIPHER时钟转移到LMM释放时关闭:解决由于任务优先级低，当LMM在使用CIPHER的时候，
       任务抢占，LRRC把CIPHER时钟关闭，导致LMM DATA ABORT问题 */
    #if (VOS_OS_VER != VOS_WIN32)
    /*低功耗方案为了省功耗，在LTE模LNAS收到LRRC释放的时候调底软接口关掉 cipher 时钟以及投票是否关pll，
     协议栈只看到这一个接口，版本共分支由底软在此接口内部进行封装*/
    (VOS_VOID)LDRV_CIPHER_DISABLE();
    #endif
    NAS_LMM_StopStateTimer(TI_NAS_EMM_WAIT_RRC_DATA_CNF);

    #if (FEATURE_LPP == FEATURE_ON)
    /*lint -e746*/
    NAS_EMM_SendLppRelInd();
    /*lint +e746*/
    #endif

    /* 如果释放原因值是CSFB高优先级，需记录到MML供GU NAS使用，此标识由GU负责清除 */
    /*lint -e40*/
    if(LRRC_LNAS_REL_CAUSE_CSFB_HIGH_PRIOR == pLrrcRelInd->enRelCause)
    /*lint +e40*/
    {
        NAS_MML_SetRelCauseCsfbHighPrioFlg(VOS_TRUE);
    }
    else
    {
        NAS_MML_SetRelCauseCsfbHighPrioFlg(VOS_FALSE);
    }

    if (NAS_EMM_GetConnState()!= NAS_EMM_CONN_IDLE)
    {
        if(LRRC_LNAS_REL_CAUSE_NO_RF == pLrrcRelInd->enRelCause)
        {
            /*通知 RABM:RRC_CONN_REL_IND,带NO_RF原因值*/
            NAS_LMM_SendRabmRrcConRelInd(EMM_ERABM_REL_CAUSE_NO_RF);
            /* REL IND原因值为NO RF时，当做LRRC_LNAS_REL_CAUSE_CONN_FAIL处理,
               即LMM在收到LRRC的系统消息后,若存在上行数据阻塞标志则发起SR流程，无该标志时发起TAU流程,使UE和网侧连接状态达成一致 */
            NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
            NAS_LMM_SetEmmInfoTriggerTauRrcRel(NAS_EMM_TRIGGER_TAU_RRC_REL_CONN_FAILURE);
        }
        else
        {
            /*通知 RABM:RRC_CONN_REL_IND*/
            NAS_LMM_SendRabmRrcConRelInd(EMM_ERABM_REL_CAUSE_NULL);
        }
    }
    /* 若LMM是挂起过程中，或已经挂起，要给ERABM通知一下，*/
    if(   (NAS_LMM_CUR_LTE_SUSPEND == NAS_EMM_GetCurLteState())
       || (EMM_MS_SUSPEND == NAS_LMM_GetEmmCurFsmMS())
       || (EMM_MS_RESUME  == NAS_LMM_GetEmmCurFsmMS()))
    {

        if (NAS_EMM_GetConnState()!= NAS_EMM_CONN_IDLE)
        {
            /* 切换或CCO 挂起流程中，或挂起完成后，或挂起回退过程中，进入IDLE态 */
            NAS_EMM_CommProcConn2Ilde();
        }

        /*NAS_EMM_MrrcChangeRrcStatusToIdle();
        NAS_LMM_SendRabmRrcConRelInd();*/

        NAS_LMM_PUBM_LOG_INFO("NAS_LMM_PreProcRrcRelInd: SUSPENDING or SUSPENDED ");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcRrcRelInd_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_LMM_MSG_DISCARD;
    }

    /*当前的连接状态是NAS_EMM_CONN_ESTING，表示RRC还没有回复est cnf的期间，
      收到了RRC的链路释放消息，此时我们认为建链失败，发送内部消息进入相应的
      状态机处理。
    */
    if(NAS_EMM_CONN_ESTING == NAS_EMM_GetConnState())
    {
        NAS_LMM_StopStateTimer(TI_NAS_EMM_MRRC_WAIT_RRC_CONN_CNF);

        NAS_EMM_SecuCurrentContextUpNasCountBack();

        NAS_EMM_SetConnState(NAS_EMM_CONN_RELEASING);

        /*发MRRC_CONNECT_FAIL_IND*/
        NAS_EMM_MrrcConnectFailInd(LRRC_EST_EST_CONN_FAIL);

        return  NAS_LMM_MSG_HANDLED;
    }

    if((NAS_EMM_CONN_RELEASING == NAS_EMM_GetConnState())
       || (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsStaTimerRunning(TI_NAS_EMM_STATE_T3440))
       || (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_REATTACH_DELAY)))
    {
        /*停止定时器*/
        NAS_LMM_StopStateTimer(TI_NAS_EMM_MRRC_WAIT_RRC_REL_CNF);

        NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_T3440);

        NAS_LMM_StopPtlTimer(TI_NAS_EMM_PTL_REATTACH_DELAY);

        NAS_EMM_CommProcConn2Ilde();
        if((EMM_MS_REG == NAS_LMM_GetEmmCurFsmMS())
            &&((EMM_SS_REG_NORMAL_SERVICE == NAS_LMM_GetEmmCurFsmSS())
                ||(EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM == NAS_LMM_GetEmmCurFsmSS())))
        {
            NAS_EMM_TAU_MsRegMsgRelInd(pLrrcRelInd->enRelCause);
        }

        if (EMM_MS_AUTH_INIT == NAS_LMM_GetEmmCurFsmMS())
        {
            /* AUTH失败次数清零*/
            NAS_EMM_GetAuthFailTimes() = 0;

            /* 状态出栈*/
            NAS_EMM_FSM_PopState();

            //NAS_EMM_MsAuthInitEnterIdleProc(pLrrcRelInd->enRelCause);
        }

        return NAS_LMM_MSG_HANDLED;

    }

    /* 如果释放原因值为 HO_FAIL，则需要进入状态机处理*/
    if(LRRC_LNAS_REL_CAUSE_GU2L_HO_ERR == pLrrcRelInd->enRelCause)
    {
        ulRet = NAS_LMM_MSG_DISCARD;
    }
    else
    {
        /*在IDLE态下收到RRC_REL_IND,直接丢弃
          若LMM是恢复过程中，则此时状态为CONNECT，进入状态机处理 */
        if(NAS_EMM_CONN_IDLE == NAS_EMM_GetConnState())
        {
            ulRet = NAS_LMM_MSG_HANDLED;
        }
        else if(EMM_MS_DEREG == NAS_LMM_GetEmmCurFsmMS())
        {
            NAS_EMM_CommProcConn2Ilde();
            ulRet = NAS_LMM_MSG_HANDLED;
        }
    }


    NAS_LMM_PUBM_LOG1_INFO("NAS_LMM_PreProcRrcRelInd: ulRet = ", ulRet);
    TLPS_PRINT2LAYER_INFO1(NAS_LMM_PreProcRrcRelInd_ENUM,LNAS_FUNCTION_LABEL2,ulRet);
    return(ulRet);
}


/*****************************************************************************
 Function Name   : NAS_LMM_PreProcMmcRelReq
 Description     : 收到MMC_LMM_REL_REQ消息的处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-5-12  Draft Enact
    2.leili       00132387      2011-6-09  Modify 增加了在各子状态下收到
                                                  MMC_LMM_REL_REQ消息的处理
*****************************************************************************/
VOS_UINT32  NAS_LMM_PreProcMmcRelReq( MsgBlock *          pMsg )
{
    VOS_UINT32                          ulCurEmmStat;

    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_PreProcMmcRelReq Enter.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcMmcRelReq_ENUM,LNAS_ENTRY);

    (VOS_VOID)pMsg;
    if (NAS_EMM_NULL_PTR == pMsg)
    {
        NAS_LMM_PUBM_LOG_INFO("NAS_LMM_PreProcMmcRelReq: Input para is null");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcMmcRelReq_ENUM,LNAS_NULL_PTR);
        return NAS_LMM_MSG_HANDLED;
    }

    if (NAS_EMM_CONN_IDLE == NAS_EMM_GetConnState())
    {
        NAS_LMM_PUBM_LOG_NORM("NAS_LMM_PreProcMmcRelReq: Idle");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcMmcRelReq_ENUM,LNAS_FUNCTION_LABEL1);
        NAS_EMM_SendMmcStatusInd(       MMC_LMM_STATUS_TYPE_CONN_STATE,
                                        MMC_LMM_CONN_IDLE);

        return NAS_LMM_MSG_HANDLED;
    }

    NAS_LMM_EstingOrReleasingProcessTimerHandle();

    if( (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsStaTimerRunning(TI_NAS_EMM_STATE_T3440))
        || (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_REATTACH_DELAY)))
    {
        NAS_LMM_PUBM_LOG_NORM("NAS_LMM_PreProcMmcRelReq: conn state is not releasing");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcMmcRelReq_ENUM,LNAS_FUNCTION_LABEL2);
        NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_T3440);
        NAS_LMM_StopPtlTimer(TI_NAS_EMM_PTL_REATTACH_DELAY);

        if(NAS_EMM_TAU_COMPLETE_VALID == NAS_EMM_TAU_GetEmmTauCompleteFlag())
        {
           NAS_LMM_PUBM_LOG_NORM("NAS_LMM_PreProcMmcRelReq,TAU COMPLETE NEEDED DELAY");
           TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcMmcRelReq_ENUM,LNAS_FUNCTION_LABEL3);

           /* 延迟500ms，是为了使得TAU COMPLETE消息能够尽量发送出去 */
           (VOS_VOID)TLPS_TaskDelay(500);
        }

        /*启动定时器TI_NAS_EMM_MRRC_WAIT_RRC_CNF*/
        NAS_LMM_StartStateTimer(TI_NAS_EMM_MRRC_WAIT_RRC_REL_CNF);

        /*发送RRC_MM_REL_REQ*/
        NAS_EMM_SndRrcRelReq(NAS_LMM_NOT_BARRED);

        /* 给RRC发释放后，连接状态改为释放过程中 */
        NAS_EMM_SetConnState(NAS_EMM_CONN_RELEASING);

        return NAS_LMM_MSG_HANDLED;
    }

    NAS_LMM_IfEmmHasBeenPushedThenPop();

    ulCurEmmStat = NAS_LMM_PUB_COMP_EMMSTATE(NAS_EMM_CUR_MAIN_STAT,
                                                NAS_EMM_CUR_SUB_STAT);

    switch(ulCurEmmStat)
    {
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG_INIT, EMM_SS_ATTACH_WAIT_ESM_PDN_RSP):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG_INIT, EMM_SS_ATTACH_WAIT_CN_ATTACH_CNF):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG_INIT, EMM_SS_ATTACH_WAIT_ESM_BEARER_CNF):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG_INIT, EMM_SS_ATTACH_WAIT_RRC_DATA_CNF):
                NAS_LMM_PUBM_LOG_NORM("NAS_LMM_PreProcMmcRelReq: REG_INIT");
                TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcMmcRelReq_ENUM,LNAS_FUNCTION_LABEL4);
                NAS_EMM_ProcDeregMmcRelReq();
                break;

        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_DEREG_INIT,EMM_SS_DETACH_WAIT_CN_DETACH_CNF):
                NAS_LMM_PUBM_LOG_NORM("NAS_LMM_PreProcMmcRelReq: DEREG_INIT is discard");
                TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcMmcRelReq_ENUM,LNAS_FUNCTION_LABEL5);
                NAS_EMM_ProcDetachMmcRelReq();
                break;
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_NORMAL_SERVICE):
                NAS_LMM_PUBM_LOG_NORM("NAS_LMM_PreProcMmcRelReq: REG+NORMAL_SERVICE");
                TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcMmcRelReq_ENUM,LNAS_FUNCTION_LABEL6);
                NAS_EMM_DisableLteCommonProc();
                break;

        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_TAU_INIT, EMM_SS_TAU_WAIT_CN_TAU_CNF):
                NAS_LMM_PUBM_LOG_NORM("NAS_LMM_PreProcMmcRelReq: TauInit+WaitCnTauCnf");
                TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcMmcRelReq_ENUM,LNAS_FUNCTION_LABEL7);
                NAS_EMM_ProcRegMmcRelReqWhileTauInit();
                break;

        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_SER_INIT, EMM_SS_SER_WAIT_CN_SER_CNF):
                NAS_LMM_PUBM_LOG_NORM("NAS_LMM_PreProcMmcRelReq: SerInit+WaitCnSerCnf");
                TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcMmcRelReq_ENUM,LNAS_FUNCTION_LABEL8);
                NAS_EMM_ProcRegMmcRelReqWhileSerInit();
                break;

        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_IMSI_DETACH_WATI_CN_DETACH_CNF):
                NAS_LMM_PUBM_LOG_NORM("NAS_LMM_PreProcMmcRelReq: EMM_SS_REG_IMSI_DETACH_WATI_CN_DETACH_CNF");
                TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcMmcRelReq_ENUM,LNAS_FUNCTION_LABEL9);
                NAS_EMM_ProcRegMmcRelReqWhileImsiDetach();
                break;
                /*改动背景: 德电外场测试，打电话CSFB HO到W失败，想切换到G模继续业务，此时需要做以下
                步骤: 从W回退到L, rrc给nas发起resume流程，在resume的过程中， MMC下发链路释放请求，
                链路释放成功后， 然后走挂起流程， 最后到G模继续业务， 在这里NAS是在
                EMM_MS_RESUME + EMM_SS_RESUME_RRCORI_WAIT_SYS_INFO_IND状态的时候，收到MMC的rel req，
                将链路释放请求发给RRC即可*/
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_RESUME, EMM_SS_RESUME_RRCORI_WAIT_SYS_INFO_IND):
                NAS_LMM_PUBM_LOG_NORM("NAS_LMM_PreProcMmcRelReq: EMM_MS_RESUME");
                TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcMmcRelReq_ENUM,LNAS_FUNCTION_LABEL10);
                NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);
                break;
        default:
                /*
                EMM_MS_DEREG+EMM_SS_DEREG_WAIT_MRRC_REL_CNF
                EMM_MS_REG+EMM_SS_REG_WAIT_MRRC_REL_CNF
                EMM_MS_TAU_INIT+EMM_SS_TAU_WAIT_RRC_REL_IND
                EMM_MS_SER_INIT+EMM_SS_SER_WAIT_RRC_REL_IND
                EMM_MS_REG_INIT+EMM_SS_ATTACH_WAIT_RRC_REL_IND
                EMM_MS_DEREG_INIT+EMM_SS_DETACH_WAIT_RRC_REL_IND
                */
                /*丢弃*/
                break;

    }

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_IsSuspended
 Description     : 判断L是否为从模
 Input           : pMsg
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.z00179470      2011-11-17  Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_EMM_IsSuspended( VOS_VOID )
{
    if( ((EMM_MS_REG == NAS_LMM_GetEmmCurFsmMS())&&(EMM_SS_REG_NO_CELL_AVAILABLE ==NAS_LMM_GetEmmCurFsmSS()))
       ||((EMM_MS_DEREG == NAS_LMM_GetEmmCurFsmMS())&&(EMM_SS_DEREG_NO_CELL_AVAILABLE ==NAS_LMM_GetEmmCurFsmSS()))
       ||((EMM_MS_DEREG == NAS_LMM_GetEmmCurFsmMS())&&(EMM_SS_DEREG_NO_IMSI ==NAS_LMM_GetEmmCurFsmSS())))
    {
        if(NAS_LMM_CUR_LTE_SUSPEND == NAS_EMM_GetCurLteState())
        {
            return NAS_EMM_IS_SUSPEND;
        }
    }

    return NAS_EMM_NOT_SUSPEND;
}

/*****************************************************************************
 Function Name   : NAS_LMM_SupendResumeAttachRslt
 Description     : LMM在SUSPEND和RESUME状态下收到不同类型的ATTACH,根据注册域及ATTACH的类型进行回复
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :NAS_EMM_CompCnAttachReqNasMsg
    1.z00179470      2011-11-11  Draft Enact

*****************************************************************************/
MMC_LMM_ATTACH_RSLT_ENUM_UINT32  NAS_LMM_SupendResumeAttachRslt( MsgBlock  *pMsg )
{
    MMC_LMM_ATTACH_RSLT_ENUM_UINT32     ulAttachRslt = MMC_LMM_ATT_RSLT_BUTT;
    MMC_LMM_ATTACH_REQ_STRU            *pstMmcAttReq = VOS_NULL_PTR;

    pstMmcAttReq            = (MMC_LMM_ATTACH_REQ_STRU*)pMsg;
    /* ATTACH类型为IMSI */
    if(MMC_LMM_ATT_REQ_TYPE_CS_ONLY == pstMmcAttReq->ulAttachType)
    {
        if(NAS_EMM_NO == NAS_EMM_IsCsPsUeMode())
        {
            return MMC_LMM_ATT_RSLT_FAILURE;
        }

        if((NAS_LMM_REG_DOMAIN_CS_PS == NAS_LMM_GetEmmInfoRegDomain())
            || (NAS_LMM_REG_DOMAIN_CS == NAS_LMM_GetEmmInfoRegDomain()))
        {
             return MMC_LMM_ATT_RSLT_SUCCESS;
        }

        return MMC_LMM_ATT_RSLT_FAILURE;
    }

    /* ATTACH类型为EPS */
    else if(MMC_LMM_ATT_REQ_TYPE_PS_ONLY == pstMmcAttReq->ulAttachType)
    {
        if((NAS_LMM_REG_DOMAIN_NULL == NAS_LMM_GetEmmInfoRegDomain())
            || (NAS_LMM_REG_DOMAIN_CS == NAS_LMM_GetEmmInfoRegDomain()))
        {
            return  MMC_LMM_ATT_RSLT_FAILURE;
        }

        return MMC_LMM_ATT_RSLT_SUCCESS;

    }

    /* ATTACH类型为COMBINED */
    else if(MMC_LMM_ATT_REQ_TYPE_CS_PS== pstMmcAttReq->ulAttachType)
    {
        if(NAS_EMM_NO == NAS_EMM_IsCsPsUeMode())
        {
            return MMC_LMM_ATT_RSLT_FAILURE;
        }

        if(NAS_LMM_REG_DOMAIN_CS_PS == NAS_LMM_GetEmmInfoRegDomain())
        {
            return MMC_LMM_ATT_RSLT_SUCCESS;
        }

        return  MMC_LMM_ATT_RSLT_FAILURE;

    }
    else
    {
        /*dayin*/
    }
    return ulAttachRslt;
}

/*****************************************************************************
 Function Name   : NAS_LMM_PreProcMsgAppMmAttachReq
 Description     : 对APPMmAttachRequest消息的处理
 Input           : pMsg
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.X00148705      2009-9-25  Draft Enact
    2.Z00148421      2010-12-20 mod:NULL状态(开机或者关机过程中，收到APP_ATTACH_REQ),
                                设置AUTO_ATTACH_ALLOW,并回复APP_ATTACH_CNF
    3.lifuxin        2014-10-31 建链流程重构
*****************************************************************************/
VOS_UINT32  NAS_LMM_PreProcMsgAppMmAttachReq( MsgBlock *          pMsg )
{

    VOS_UINT32                          ulRet = NAS_LMM_MSG_DISCARD;
    VOS_UINT32                          ulCurEmmStat;
    MMC_LMM_ATTACH_REQ_STRU             *pstMmcAttachReq = VOS_NULL_PTR;
    VOS_UINT32                          ulAttachRst = MMC_LMM_ATT_RSLT_SUCCESS;

    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_PreProcMsgAppMmAttachReq: enter.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcMsgAppMmAttachReq_ENUM,LNAS_ENTRY);

    pstMmcAttachReq                        = (VOS_VOID*)pMsg;
    /* 若当前LTE挂起，则丢弃此消息 */

    pstMmcAttachReq = (MMC_LMM_ATTACH_REQ_STRU *)pMsg;

    /*NULL状态下直接丢弃*/
    if  (EMM_MS_NULL == NAS_LMM_GetEmmCurFsmMS())
    {

        NAS_LMM_PUBM_LOG_NORM("NAS_LMM_PreProcMsgAppMmAttachReq, LTE CUR NULL,discard it.");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcMsgAppMmAttachReq_ENUM,LNAS_NULL_PTR);

        return NAS_LMM_MSG_HANDLED;
    }
    if(NAS_EMM_IS_SUSPEND == NAS_EMM_IsSuspended())
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_LMM_PreProcMsgAppMmAttachReq: LTE CUR SUSPEND");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcMsgAppMmAttachReq_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_LMM_MSG_HANDLED;

    }


    /*保存用户发起ATTACH的请求类型*/
    NAS_EMM_GLO_SetAttReqType(pstMmcAttachReq->ulAttachType);
    /*保存用户发起ATTACH的原因值*/
    NAS_LMM_SetEmmInfoMmcAttachReason(pstMmcAttachReq->ulAttachReason);

    if (MMC_LMM_ATT_REQ_TYPE_PS_ONLY == pstMmcAttachReq->ulAttachType)
    {
        /* 设置允许PS自动ATTACH*/
        NAS_MML_SetPsAttachAllowFlg(NAS_EMM_AUTO_ATTACH_ALLOW);
    }
    else if (MMC_LMM_ATT_REQ_TYPE_CS_ONLY == pstMmcAttachReq->ulAttachType)
    {
        /* 设置允许CS自动ATTACH*/
         NAS_MML_SetCsAttachAllowFlg(NAS_EMM_AUTO_ATTACH_ALLOW);
    }
    else if(MMC_LMM_ATT_REQ_TYPE_CS_PS == pstMmcAttachReq->ulAttachType)
    {
        /* 设置允许PS自动ATTACH*/
        NAS_MML_SetPsAttachAllowFlg(NAS_EMM_AUTO_ATTACH_ALLOW);

        /* 设置允许CS自动ATTACH*/
        NAS_MML_SetCsAttachAllowFlg(NAS_EMM_AUTO_ATTACH_ALLOW);
    }
    else
    {

    }



    if( (EMM_MS_SUSPEND == NAS_LMM_GetEmmCurFsmMS())
        ||(EMM_MS_RESUME == NAS_LMM_GetEmmCurFsmMS()))
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_LMM_PreProcMsgAppMmAttachReq: LTE CUR SUSPEND ING OR RESUME");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcMsgAppMmAttachReq_ENUM,LNAS_FUNCTION_LABEL2);
        /*保存APP参数*/
        NAS_EMM_SaveAppMsgPara(pstMmcAttachReq->ulMsgId,pstMmcAttachReq->ulOpId);
        ulAttachRst = NAS_LMM_SupendResumeAttachRslt(pMsg);
        NAS_EMM_MmcSendAttCnf(ulAttachRst);
        return NAS_LMM_MSG_HANDLED;

    }

    /*获取EMM当前状态*/
    ulCurEmmStat = NAS_LMM_PUB_COMP_EMMSTATE(NAS_EMM_CUR_MAIN_STAT,
                                            NAS_EMM_CUR_SUB_STAT);

    if(NAS_EMM_CONN_ESTING == NAS_EMM_GetConnState())
    {
        return  NAS_LMM_STORE_HIGH_PRIO_MSG;
    }

    if((NAS_EMM_CONN_RELEASING == NAS_EMM_GetConnState())
        || (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsStaTimerRunning(TI_NAS_EMM_STATE_T3440))
        || (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_REATTACH_DELAY)))
    {
        return NAS_LMM_STORE_HIGH_PRIO_MSG;
    }

    switch(ulCurEmmStat)
    {
        /*在AUTH_INIT+WAIT_CN_AUTH_CNF过程中，低优先级缓存 */
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_AUTH_INIT, EMM_SS_AUTH_WAIT_CN_AUTH):

                ulRet = NAS_LMM_STORE_LOW_PRIO_MSG;
                break;
        default:
                ulRet = NAS_LMM_MSG_DISCARD;
                break;
    }
    return(ulRet);
}

/*****************************************************************************
 Function Name   : NAS_LMM_PreProcMsgEsmDataReq
 Description     : 对EsmDataRequest消息的处理
 Input           : pMsg
 Output          : None
 Return          : VOS_UINT32
 History         :
    1.lifuxin      2014-07-08 Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LMM_PreProcMsgEsmDataReq( MsgBlock *          pMsg )
{
    EMM_ESM_DATA_REQ_STRU               *pstEmmEsmDataReq = VOS_NULL;
    VOS_UINT32                          ulRet = NAS_LMM_MSG_DISCARD;
    VOS_UINT32                          ulCurEmmStat;

    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_PreProcMsgEsmDataReq Enter.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcMsgEsmDataReq_ENUM,LNAS_ENTRY);

    pstEmmEsmDataReq = (EMM_ESM_DATA_REQ_STRU*)pMsg;
    ulCurEmmStat = NAS_LMM_PUB_COMP_EMMSTATE(NAS_EMM_CUR_MAIN_STAT, NAS_EMM_CUR_SUB_STAT);
    NAS_LMM_PUBM_LOG1_INFO("NAS_LMM_PreProcMsgEsmDataReq, EmmEsmOpId = ", pstEmmEsmDataReq->ulOpId);
    TLPS_PRINT2LAYER_INFO1(NAS_LMM_PreProcMsgEsmDataReq_ENUM,LNAS_FUNCTION_LABEL1,pstEmmEsmDataReq->ulOpId);
    if(NAS_EMM_CONN_ESTING == NAS_EMM_GetConnState())
    {
        return  NAS_LMM_MSG_DISCARD;
    }

    if( (NAS_EMM_CONN_RELEASING == NAS_EMM_GetConnState())
        || (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsStaTimerRunning(TI_NAS_EMM_STATE_T3440))
        || (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_REATTACH_DELAY)))
    {
        return NAS_LMM_MSG_DISCARD;
    }

    switch(ulCurEmmStat)
    {
        /*在下面这些场景需要进入状态机处理*/
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG_INIT,          EMM_SS_ATTACH_WAIT_CN_ATTACH_CNF):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG_INIT,          EMM_SS_ATTACH_WAIT_ESM_BEARER_CNF):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG_INIT,          EMM_SS_ATTACH_WAIT_RRC_DATA_CNF):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG,               EMM_SS_REG_NORMAL_SERVICE):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG,               EMM_SS_REG_ATTEMPTING_TO_UPDATE):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG,               EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG,               EMM_SS_REG_LIMITED_SERVICE):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG,               EMM_SS_REG_WAIT_ACCESS_GRANT_IND):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG,               EMM_SS_REG_IMSI_DETACH_WATI_CN_DETACH_CNF):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_TAU_INIT,          EMM_SS_TAU_WAIT_CN_TAU_CNF):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_SER_INIT,          EMM_SS_SER_WAIT_CN_SER_CNF):
                ulRet = NAS_LMM_MSG_DISCARD;
                break;
        default :
                /*除开上面这些场景，LMM直接丢弃ESM_EMM_DATA_REQ消息，然后回复ESM*/
                NAS_EMM_SendEsmDataCnf(EMM_ESM_SEND_RSLT_EMM_DISCARD, pstEmmEsmDataReq->ulOpId);
                ulRet = NAS_LMM_MSG_HANDLED;
                break;
    }

    return  ulRet;
}

/*****************************************************************************
 Function Name   : NAS_LMM_PreProcMsgEsmEstReq
 Description     : 对EsmEstRequest消息的处理
 Input           : pMsg
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.X00148705      2009-9-25  Draft Enact

*****************************************************************************/
static VOS_UINT32  NAS_LMM_PreProcMsgEsmEstReq( MsgBlock *          pMsg )
{
    (VOS_VOID)                            pMsg;

    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_PreProcMsgEsmEstReq Enter.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcMsgEsmEstReq_ENUM,LNAS_ENTRY);

    /*在svlte的某些场景下，需要从主modem切到副modem，此时主modem detach ps，并设为ps not allow
      副modem attach到ps， 同时app下发了ndis_req又触发了主modem重新激活，从而导致双ps attach，
      为了避免这种情况，当主modem在ps not allow的情况下收到ndis_req不再重新激活，直接回复建链失败*/
    if((NAS_EMM_NO == NAS_MML_GetCsOnlyDataServiceSupportFlg())
        && (NAS_EMM_AUTO_ATTACH_NOT_ALLOW == NAS_MML_GetPsAttachAllowFlg()))
    {
        NAS_LMM_PUBM_LOG_INFO("NAS_LMM_PreProcMsgEsmEstReq: have enabled ps_not_allow, don't est process");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcMsgEsmEstReq_ENUM,LNAS_FUNCTION_LABEL1);
        NAS_EMM_EsmSendEstCnf(EMM_ESM_ATTACH_RESULT_FAIL);
        return NAS_LMM_MSG_HANDLED;
    }
    NAS_MML_SetPsAttachAllowFlg(NAS_EMM_AUTO_ATTACH_ALLOW);

    return NAS_LMM_MSG_DISCARD;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 Function Name   : NAS_LMM_PreProcMsgEsmClLocalDetachNotify
 Description     : 对ID_EMM_ESM_CL_LOCAL_DETACH_NOTIFY消息的处理
 Input           : pMsg
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LMM_PreProcMsgEsmClLocalDetachNotify(
    MsgBlock                           *pMsg
)
{
    (VOS_VOID)pMsg;

    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_PreProcMsgEsmClLocalDetachNotify is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcMsgEsmClLocalDetachNotify_ENUM,LNAS_ENTRY);

    if (NAS_EMM_IS_SUSPEND == NAS_EMM_IsSuspended())
    {
        if (EMM_MS_REG == NAS_LMM_GetEmmCurFsmMS())
        {
            NAS_EMM_AdStateConvert(EMM_MS_DEREG,
                                   EMM_SS_DEREG_NO_CELL_AVAILABLE,
                                   TI_NAS_EMM_STATE_NO_TIMER);

            /* 本地DETACH释放资源:动态内存、赋初值 */
            NAS_LMM_DeregReleaseResource();

            /*向MMC发送本地LMM_MMC_DETACH_IND消息*/
            NAS_EMM_MmcSendDetIndLocal(MMC_LMM_L_LOCAL_DETACH_OTHERS);
        }
    }

    return NAS_LMM_MSG_HANDLED;
}
#endif

/*****************************************************************************
 Function Name   : NAS_LMM_PreProcMsgEsmClrEsmPrcResNotify
 Description     : 对EMM_ESM_CLR_ESM_PROC_RES_NOTIFY消息的处理
 Input           : pMsg
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2012-11-01  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LMM_PreProcMsgEsmClrEsmPrcResNotify
(
    MsgBlock                           *pMsg
)
{
    EMM_ESM_CLR_ESM_PROC_RES_NOTIFY_STRU   *pstEsmClrEsmProcResNotify   = NAS_EMM_NULL_PTR;

    pstEsmClrEsmProcResNotify = (EMM_ESM_CLR_ESM_PROC_RES_NOTIFY_STRU*)pMsg;

    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_PreProcMsgEsmClrEsmPrcResNotify Enter.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcMsgEsmClrEsmPrcResNotify_ENUM,LNAS_ENTRY);
    /* 根据OPID删除缓存的ESM消息 */
    NAS_EMM_SER_DeleteEsmMsg(pstEsmClrEsmProcResNotify->ulOpId);
    /* 如果是紧急类型，则更新状态为没有紧急PDN建立请求，清除ATTACH,TAU,SERVICE
       触发原因值，清除缓存的紧急PDN连接请求消息 */
    if (VOS_TRUE == pstEsmClrEsmProcResNotify->ulIsEmcType)
    {
        NAS_LMM_SetEmmInfoIsEmerPndEsting(VOS_FALSE);

        if ((EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER == NAS_EMM_GLO_AD_GetAttCau())
            || (EMM_ATTACH_CAUSE_ESM_EMC_ATTACH == NAS_EMM_GLO_AD_GetAttCau()))
        {
            NAS_EMM_GLO_AD_GetAttCau() = EMM_ATTACH_CAUSE_OTHER;
        }
        if (NAS_EMM_TAU_START_CAUSE_ESM_EMC_PDN_REQ == NAS_EMM_TAU_GetEmmTAUStartCause())
        {
            NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
        }

        if ((NAS_EMM_SER_START_CAUSE_ESM_DATA_REQ_EMC == NAS_EMM_SER_GetEmmSERStartCause())
            || (NAS_EMM_SER_START_CAUSE_RABM_REEST_EMC == NAS_EMM_SER_GetEmmSERStartCause()))
        {
            NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_BUTT);
        }
        NAS_EMM_ClearEmcEsmMsg();
    }

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_PreProcMsgSwithOffTimerExp
 Description     : 关机定时器超时预处理
 Input           : pMsg
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunbing49683      2010-1-29  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_PreProcMsgSwithOffTimerExp( MsgBlock *        pMsg )/*lint -e818*/
{
    VOS_UINT32                          ulRet;

    (VOS_VOID)pMsg;

    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_PreProcMsgSwithOffTimerExp enter!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgSwithOffTimerExp_ENUM,LNAS_ENTRY);

    /*sunbing 00265702/yanglei 关机定时器没有停 begin for DTS2015092904078*/
    /*仅在关机detach状态下处理*/
    if ((EMM_MS_NULL != NAS_LMM_GetEmmCurFsmMS())
        ||(EMM_SS_NULL_WAIT_SWITCH_OFF != NAS_LMM_GetEmmCurFsmSS()))
    {
        return NAS_LMM_MSG_HANDLED;
    }
    /*sunbing 00265702/yanglei 关机定时器没有停 end for DTS2015092904078*/

    NAS_LMM_EstingOrReleasingProcessTimerHandle();
    NAS_LMM_IfEmmHasBeenPushedThenPop();

    ulRet = NAS_EMM_MsNullSsWaitSwitchOffProcMsgRrcRelInd();

    return ulRet;
}/*lint  +e818*/

/*****************************************************************************
 Function Name   : NAS_EMMC_DelForbTaTimerExpireProcess
 Description     : 周期删除禁止TA列表定时器超时处理
 Input           :VOS_VOID
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.luojian 00107747      2008-12-11  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_EMM_PreProcMsgDelForbTaTimerExpire( MsgBlock *pMsg )
{
    NAS_LMM_NETWORK_INFO_STRU           *pstNetInfo;
    VOS_UINT32                          ulNum;

    NAS_LMM_PUBM_LOG_NORM("NAS_EMM_PreProcMsgDelForbTaTimerExpire is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgDelForbTaTimerExpire_ENUM,LNAS_ENTRY);

    (void)pMsg;

    /* 入参检查 */
    if ( NAS_EMM_NULL_PTR == pMsg)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_EMM_PreProcMsgDelForbTaTimerExpire:input ptr null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_PreProcMsgDelForbTaTimerExpire_ENUM,LNAS_NULL_PTR);
        return  NAS_LMM_ERR_CODE_PTR_NULL;
    }


    /* 删除禁止TA列表 */
    pstNetInfo = NAS_LMM_GetEmmInfoNetInfoAddr();

    ulNum                               = pstNetInfo->stForbTaForRoam.ulTaNum;

    /*delete list of "forbidden tracking areas for roaming"*/
    pstNetInfo->bitOpFoibTaForRoam = NAS_EMM_BIT_NO_SLCT;
    NAS_LMM_ClearTaList(&pstNetInfo->stForbTaForRoam);

    /*delete list of "forbidden tracking areas for regional provision of service"*/
    pstNetInfo->bitOpFoibTaForRpos = NAS_EMM_BIT_NO_SLCT;
    NAS_LMM_ClearTaList(&pstNetInfo->stForbTaForRpos);

    if (ulNum != pstNetInfo->stForbTaForRoam.ulTaNum)
    {
        NAS_LMM_PUBM_LOG_NORM("NAS_EMM_PreProcMsgDelForbTaTimerExpire:Forb TA FOR Roaming is change");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgDelForbTaTimerExpire_ENUM,LNAS_FUNCTION_LABEL1);
        NAS_EMMC_SendRrcCellSelectionReq(LRRC_LNAS_FORBTA_CHANGE);
    }

    return NAS_LMM_MSG_HANDLED;
}
/*****************************************************************************
 Function Name   : NAS_EMM_PreProcMsgWaitSyscfgCnfTimerExpire
 Description     : 等待SYSCFG_CNF消息超时的处理
 Input           : MsgBlock *pMsg
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.wangchen 00209181         2012-05-28

*****************************************************************************/
VOS_UINT32  NAS_EMM_PreProcMsgWaitSyscfgCnfTimerExpire( MsgBlock *pMsg )
{
    (void)pMsg;

    NAS_LMM_PUBM_LOG_NORM("NAS_EMM_PreProcMsgWaitSyscfgCnfTimerExpire is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgWaitSyscfgCnfTimerExpire_ENUM,LNAS_ENTRY);

    NAS_LMM_SetEmmInfoSyscfgCtrl(NAS_LMM_SYSCFG_FLAG_INVALID);

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_LMM_PreProcrRrcDataInd
 Description     : CN_DETACH_REQ消息预处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-3-23  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LMM_PreProcrRrcDataInd( MsgBlock *          pMsg )
{
    LRRC_LMM_DATA_IND_STRU             *pRrcMmDataIndMsg    = VOS_NULL_PTR;
    VOS_UINT8                           ucMsgType           = NAS_EMM_NULL;
    VOS_UINT8                           ucPD                = NAS_EMM_NULL;

    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_PreProcrRrcDataInd Enter.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcrRrcDataInd_ENUM,LNAS_ENTRY);

    pRrcMmDataIndMsg = (LRRC_LMM_DATA_IND_STRU *)pMsg;
    ucMsgType = pRrcMmDataIndMsg->stNasMsg.aucNasMsg[NAS_LMM_CN_MSG_MT_POS];

    /*取出PD*/
    ucPD = pRrcMmDataIndMsg->stNasMsg.aucNasMsg[NAS_EMM_NULL] & EMM_CN_MSG_PDMASK;

    /* 如果在AuthInit状态下收到ESM消息， 终止AUTH流程，出栈 */
    if  ((EMM_CN_MSG_PD_ESM == ucPD)
        && (EMM_MS_AUTH_INIT == NAS_LMM_GetEmmCurFsmMS()))
    {
        NAS_EMM_AbortAuthProcedure();
    }

    /*如果在AuthInit状态下收到CN_DETACH_REQ消息，终止AUTH流程，出栈*/
    if((NAS_EMM_CN_MT_DETACH_REQ_MT == ucMsgType)
        && (EMM_MS_AUTH_INIT == NAS_LMM_GetEmmCurFsmMS()))
    {
        NAS_EMM_AbortAuthProcedure();
    }

    return NAS_LMM_MSG_DISCARD;

}


static VOS_UINT32  NAS_EMM_PreProcMsgEsmBearStatusReq( MsgBlock *          pMsg )
{
    VOS_UINT32              ulRet       = NAS_LMM_MSG_DISCARD;

    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_PreProcMsgEsmBearStatusReq Enter");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgEsmBearStatusReq_ENUM,LNAS_ENTRY);

    ulRet                               = NAS_EMM_MsAnyStateSsAnySateEsmBearStatusReq((VOS_VOID*)pMsg);

    return(ulRet);

}

/*****************************************************************************
 Function Name   : NAS_EMM_PreProcMsgRrcErrInd
 Description     : 预处理RRC_ERR_IND消息，不再进状态机处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.X00148705      2009-9-27  Draft Enact
    2.X00148705      2009-11-02 修改为:根据不同的状态做相关的处理

*****************************************************************************/
static VOS_UINT32  NAS_EMM_PreProcMsgRrcErrInd( MsgBlock *          pMsg  )
{
    VOS_UINT32              ulRet       = NAS_LMM_MSG_DISCARD;

    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_PreProcMsgRrcErrInd Enter");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgRrcErrInd_ENUM,LNAS_ENTRY);


    (VOS_VOID)vos_printf("\r\n NAS_EMM_PreProcMsgRrcErrInd: receive LRRC_LMM_ERR_IND! \r\n");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgRrcErrInd_ENUM,LNAS_FUNCTION_LABEL1);

    NAS_LMM_EstingOrReleasingProcessTimerHandle();
    /* 出栈,目的是:维护栈的管理数据
    */
    NAS_LMM_IfEmmHasBeenPushedThenPop();

    /* 如果当前主状态在NULL,需要根据当前的子状态做相关的处理
    */
    if(EMM_MS_NULL                      ==  NAS_EMM_CUR_MAIN_STAT)
    {


        ulRet                           = NAS_EMM_MsNullSsAnyStateMsgRrcErrInd(ID_LRRC_LMM_ERR_IND,
                                                                              (VOS_VOID*)pMsg);
    }
    else
    {
        ulRet                           = NAS_EMM_MsNotNullSsAnyStateMsgRrcErrInd(ID_LRRC_LMM_ERR_IND,
                                                                                   (VOS_VOID*)pMsg);
    }
    return(                              ulRet);

}

/*****************************************************************************
 Function Name   : NAS_EMM_PreProcMsgT3416Exp
 Description     : T3416超时消息的处理函数
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2009-11-2  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_PreProcMsgT3416Exp( MsgBlock *          pMsg )/*lint  -e818*/
{
    (VOS_VOID)pMsg;

    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_PreProcMsgT3416Exp enter!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgT3416Exp_ENUM,LNAS_ENTRY);

    NAS_EMM_SecuClearRandRes();

    return NAS_LMM_MSG_HANDLED;
}/*lint +e818*/

/*****************************************************************************
 Function Name   : NAS_EMM_PreProcMsgT3402Exp
 Description     : T3402超时消息的处理函数
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2012-10-17  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_PreProcMsgT3402Exp( MsgBlock *          pMsg )
{
    (VOS_VOID)pMsg;

    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_PreProcMsgT3402Exp enter!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgT3402Exp_ENUM,LNAS_ENTRY);
    
    NAS_EMM_SendTimerStateNotify(TI_NAS_EMM_PTL_T3402, LMM_MMC_TIMER_EXP);

    NAS_EMM_TAU_SaveEmmTAUAttemptCnt(NAS_EMM_TAU_ATTEMPT_CNT_ZERO);
    NAS_EMM_AttResetAttAttempCounter();

    return NAS_LMM_MSG_DISCARD;
}

/*****************************************************************************
 Function Name   : NAS_EMM_PreProcMsgCsfbDelayTimerExp
 Description     : CSFB延时定时器超时消息的处理函数，此定时器目前只会在REG-NORMAL
                   态下启动，超时也只能在REG-NORMAL态下超时，如果是其他状态下超时，
                   说明出现了异常。
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunjitan 00193151      2014-05-15  Draft Enact
    2.sunjitan 00193151      2014-10-11  Mod: CSFB err log上报
*****************************************************************************/
VOS_UINT32  NAS_EMM_PreProcMsgCsfbDelayTimerExp(
    MsgBlock                           *pMsg
)
{
    (VOS_VOID)pMsg;

    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_PreProcMsgCsfbDelayTimerExp enter!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgCsfbDelayTimerExp_ENUM,LNAS_ENTRY);

    /* 给MMC上报SERVICE失败触发搜网去GU */
    NAS_EMM_MmcSendSerResultIndOtherType(MMC_LMM_SERVICE_RSLT_FAILURE);

    /* 由于T3440启动期间可能启动delay定时器，因此超时时如果还是连接态则需要释放 */
    NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);

    /* 2014-10-11 s00193151 add: CSFB ERR LOG上报，在此记录失败原因 DTS2014102701776*/
    #if (FEATURE_PTM == FEATURE_ON)
    if (VOS_TRUE == NAS_EMM_SER_IsCsfbProcedure())
    {
        NAS_EMM_ExtServiceErrRecord(EMM_OM_ERRLOG_CN_CAUSE_NULL, EMM_OM_LMM_CSFB_FAIL_CAUSE_DELAY_TIMER_EXP);
    }
    #endif

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_LMM_MsgPreProcess
 Description     : MM层消息预处理，目前主要是OM的操作维护，
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.h41410      2008-9-25  Draft Enact
    2.z00148421   2009.03.06  添加EPS bearer context的维护
    3.X00148705   2009.09.25 MM的预处理函数统一放到函数列表中处理
*****************************************************************************/
VOS_UINT32  NAS_LMM_MsgPreProcess(       MsgBlock *          pMsg)
{
    VOS_UINT32                          ulRet               = NAS_LMM_MSG_DISCARD;
    NAS_LMM_COMM_ACTION_FUN              pActFun             = NAS_LMM_NULL_PTR;
    VOS_UINT32                          ulMsgId;
    PS_MSG_HEADER_STRU                 *pHeader     = VOS_NULL_PTR;


    /* 获取消息头指针*/
    pHeader = (PS_MSG_HEADER_STRU *) pMsg;

    /*OM预处理消息*/
    ulRet = NAS_LMM_OmMaintain(pMsg);
    if(NAS_LMM_MSG_HANDLED == ulRet)
    {
        return  ulRet;
    }

    /*其他预处理消息*/
    NAS_LMM_GetNameFromMsg(ulMsgId, pMsg);   /* 获取消息ID */
    pActFun = NAS_LMM_CommFindFun(       (NAS_LMM_COMM_ACT_STRU *)g_astMmPreProcMap,
                                        g_astMmPreProcMapNum,
                                        ulMsgId,
                                        pHeader->ulSenderPid);
    if (NAS_LMM_NULL_PTR != pActFun)
    {   /* 若这里找到了，就在这里执行 */
        ulRet = (*pActFun)(pMsg);
    }

    return  ulRet;
}

/*****************************************************************************
 Function Name   : NAS_LMM_PreProcAppStartReq
 Description     : 开机消息预处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.h41410      2009-6-22  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_LMM_PreProcAppStartReq(   MsgBlock  * pMsg)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulCurEmmStat;
    VOS_UINT32                          ulMsgId;

    /* 获取消息ID */
    NAS_LMM_GetNameFromMsg(ulMsgId, pMsg);

    ulRet                               = NAS_LMM_MSG_DISCARD;
    ulCurEmmStat = NAS_LMM_PUB_COMP_EMMSTATE(NAS_EMM_CUR_MAIN_STAT,
                                            NAS_EMM_CUR_SUB_STAT);

    switch(ulCurEmmStat)
    {   /* EMM 状态 */

                /* 等待开机 */
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_NULL, EMM_SS_NULL_WAIT_APP_START_REQ):
                ulRet = NAS_EMM_MsNullSsWaitAppStartReqMsgAppStartReq(ulMsgId, (VOS_VOID *)pMsg);
                break;
/* V7R1
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_NULL, EMM_SS_NULL_WAITING_USIM_READY):
                ulRet = NAS_EMM_MsNullSsWaitingUsimReadyMsgAppStartReq(ulMsgId, (VOS_VOID *)pMsg);
                break;
*/
                /* 开机过程中 */

        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_NULL,EMM_SS_NULL_WAIT_READING_USIM):

        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_NULL, EMM_SS_NULL_WAIT_MMC_START_CNF):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_NULL, EMM_SS_NULL_WAIT_RRC_START_CNF):
                /* 开机过程中丢弃开机消息 */
                NAS_LMM_PUBM_LOG_NORM("NAS_LMM_PreProcAppStartReq: Power oning..., discard it.");
                TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcAppStartReq_ENUM,LNAS_FUNCTION_LABEL1);
                break;

                /* 关机过程中 */
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_NULL, EMM_SS_NULL_WAIT_SWITCH_OFF):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_NULL, EMM_SS_NULL_WAIT_MMC_STOP_CNF):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_NULL, EMM_SS_NULL_WAIT_RRC_STOP_CNF):
                /* 关机过程中，向APP响应开机出错 */
                ulRet = NAS_EMM_WhenStopingThenMsgAppStartReq(ulMsgId, (VOS_VOID *)pMsg);
                break;

                /* 其他状态: 开机完成后，未收到关机请求消息前 */
        default :
                ulRet = NAS_EMM_MsNotNullSsAnyStateMsgAppStartReq(ulMsgId, (VOS_VOID *)pMsg);
                break;
    }

    return  ulRet;
}


VOS_VOID NAS_LMM_EstingOrReleasingProcessTimerHandle(VOS_VOID)
{
    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_EstingOrReleasingTimerHandle!!!");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_EstingOrReleasingProcessTimerHandle_ENUM,LNAS_ENTRY);

    if(NAS_EMM_CONN_ESTING == NAS_EMM_GetConnState())
    {
        NAS_LMM_StopStateTimer(TI_NAS_EMM_MRRC_WAIT_RRC_CONN_CNF);
    }

    if( (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsStaTimerRunning(TI_NAS_EMM_STATE_T3440))
        || (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_REATTACH_DELAY)))
    {
        NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_T3440);
        NAS_LMM_StopPtlTimer(TI_NAS_EMM_PTL_REATTACH_DELAY);
    }
    if(NAS_EMM_CONN_RELEASING == NAS_EMM_GetConnState())
    {
        NAS_LMM_StopStateTimer(TI_NAS_EMM_MRRC_WAIT_RRC_REL_CNF);
        NAS_EMM_CommProcConn2Ilde();
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_LMM_IfEmmHasBeenPushedThenPop
 Description     : 若EMM的当前状态为压栈状态，则出栈
 Input           :VOS_VOID
 Output          : None
 Return          : VOS_VOID

 History         :
    1.h41410      2009-10-28  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LMM_IfEmmHasBeenPushedThenPop( VOS_VOID )
{
    NAS_LMM_PUBM_LOG1_INFO("NAS_LMM_IfEmmHasBeenPushedThenPop: NAS_EMM_CUR_MAIN_STAT = .",
                            NAS_EMM_CUR_MAIN_STAT);
    TLPS_PRINT2LAYER_INFO1(NAS_LMM_IfEmmHasBeenPushedThenPop_ENUM,LNAS_EMM_MAIN_STATE,
                            NAS_EMM_CUR_MAIN_STAT);

    switch(NAS_EMM_CUR_MAIN_STAT)
    {
        case    EMM_MS_AUTH_INIT:
                /*终止AUTH流程*/
                NAS_EMM_AbortAuthProcedure();
                break;

        default:
                NAS_LMM_PUBM_LOG_INFO("NAS_LMM_IfEmmHasBeenPushedThenPop: No Push.");
                TLPS_PRINT2LAYER_INFO(NAS_LMM_IfEmmHasBeenPushedThenPop_ENUM,LNAS_FUNCTION_LABEL1);
                break;
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_LMM_FreeDynMem
 Description     : 释放MM层所有动态内存
 Input           : VOS_VOID
 Output          : None
 Return          : VOS_VOID

 History         :
    1.h41410      2010-6-2  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LMM_FreeDynMem( VOS_VOID )
{

    /* 释放MM层各状态机的缓存消息队列 */
    NAS_LMM_BufMsgQueFree();

    /* 释放子模块缓存 */
    NAS_LMM_SubModFreeDyn();
}

/*****************************************************************************
 Function Name   : NAS_LMM_SubModFreeDyn
 Description     : 释放各个子模块的动态内存
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.y00159566      2010-6-10  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LMM_SubModFreeDyn( VOS_VOID )
{
    /* 释放Attach模块缓存 */
    NAS_EMM_FreeAttDyn();

    /* 释放Detach模块缓存 */
    NAS_EMM_FreeDetDyn();

    /* 释放TAU模块缓存 */
    NAS_EMM_FreeTauDyn();

    /* 释放Guti模块缓存 */
    NAS_EMM_FreeGutiDyn();

    /* 释放SERVICE模块缓存 */
    NAS_EMM_FreeSerDyn();

    /* 释放IDEN模块缓存 */
    NAS_EMM_FreeIdenDyn();

    /* 释放SECU模块缓存 */
    NAS_EMM_FreeSecuDyn();

    /* 释放Mrrc模块缓存 */
    NAS_EMM_FreeMrrcDyn();

    return;
}


/*****************************************************************************
 Function Name   : NAS_LMM_PreProcAppStopReq
 Description     : APP的关机消息
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.h41410      2009-8-17  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LMM_PreProcAppStopReq(   MsgBlock  * pMsg)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulCurEmmStat;
    VOS_UINT32                          ulMsgId;

    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_PreProcAppStopReq: enter.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcAppStopReq_ENUM,LNAS_ENTRY);

    /* 获取消息ID */
    NAS_LMM_GetNameFromMsg(ulMsgId, pMsg);

    NAS_LMM_EstingOrReleasingProcessTimerHandle();

    /* 如果是如下状态: 建链初始化状态；放链初始化状态；鉴权过程中状态；
       则，停止当前的定时器，状态出栈，*/
    NAS_LMM_IfEmmHasBeenPushedThenPop();

    /* 释放可能存在的动态内存 */
    NAS_LMM_FreeDynMem();

    NAS_LMM_SetEmmInfoRejCause2Flag(NAS_EMM_REJ_NO);

    NAS_LMM_SetPsSimValidity(NAS_LMM_SIM_VALID);


    NAS_EMM_ClearEmergencyList();


    /* 关机清除所有Gradual Forb TA列表本地维护信息 */
    NAS_LMM_ClearAllGradualForbTaList();
    #if (FEATURE_LPP == FEATURE_ON)
    NAS_EMM_SndLppStopInd();
    #endif

    /* 关机时清除所有上行空口缓存: 解决Reginit等状态下发送上行空口和关机对冲场景(如Attach Cmp发送过程中收到MMC的关机消息)，
        当收到空口消息的Data Cnf时NULL状态被切走，从而导致LMM不走关机流程，从而出现关机异常复位*/
    NAS_EMM_ClrAllUlDataReqBufferMsg();

    ulRet                                 = NAS_LMM_MSG_DISCARD;
    ulCurEmmStat = NAS_LMM_PUB_COMP_EMMSTATE(NAS_EMM_CUR_MAIN_STAT,
                                            NAS_EMM_CUR_SUB_STAT);

    switch(ulCurEmmStat)
    {   /* EMM 状态 */

                /* 未开机，直接给APP回复关机成功 */
        /*case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_NULL, EMM_SS_NULL_WAITING_USIM_READY):*/
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_NULL, EMM_SS_NULL_WAIT_READING_USIM):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_NULL, EMM_SS_NULL_WAIT_APP_START_REQ):
                ulRet = NAS_EMM_MsNullSsAnyReadUsimStateMsgAppStopReq(ulMsgId, (VOS_VOID *)pMsg);
                break;

                /* 关机过程中, 丢弃不处理 */
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_NULL, EMM_SS_NULL_WAIT_MMC_STOP_CNF):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_NULL, EMM_SS_NULL_WAIT_RRC_STOP_CNF):

        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_NULL, EMM_SS_NULL_WAIT_SWITCH_OFF):

                break;

                /* 已注册成功, 或给CN发了注册消息, 则先给CN发送关机DETACH，
                   再给相关模块SM/MMC/RRC发关机消息，再给APP回复关机成功  */
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG_INIT, EMM_SS_ATTACH_WAIT_CN_ATTACH_CNF):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG_INIT, EMM_SS_ATTACH_WAIT_ESM_BEARER_CNF):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG_INIT, EMM_SS_ATTACH_WAIT_RRC_DATA_CNF):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_NORMAL_SERVICE):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_WAIT_ACCESS_GRANT_IND):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_ATTEMPTING_TO_UPDATE):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_IMSI_DETACH_WATI_CN_DETACH_CNF):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_TAU_INIT, EMM_SS_TAU_WAIT_CN_TAU_CNF):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_SER_INIT, EMM_SS_SER_WAIT_CN_SER_CNF):
                ulRet = NAS_EMM_MsRegSsAnyMsgAppStopReq(ulMsgId, (VOS_VOID *)pMsg);
                break;

        default:

                /* 本地DETACH: 先给相关模块SM/MMC/RRC发关机消息，再给APP回复关机成功 */
                ulRet = NAS_EMM_MsNotNullNotRegMsgAppStopReq(ulMsgId, (VOS_VOID *)pMsg);
                break;

    }

    return  ulRet;
}


/*****************************************************************************
 Function Name   : NAS_LMM_SetAttachAllowFlgByDetachType
 Description     : 根据Detach类型设置是否允许自动Attach标识
 Input           : None
 Output          : None
 Return          : None

 History         :
    1.liuhua      00212067      2012-06-21 Draft Enact
*****************************************************************************/
VOS_VOID NAS_LMM_SetAttachAllowFlgByDetachType(
                               MMC_LMM_MO_DETACH_TYPE_ENUM_UINT32 ulDetachType)
{
    if (MMC_LMM_MO_DET_PS_ONLY == ulDetachType)
    {
        /* 设置不允许PS自动ATTACH*/
        NAS_MML_SetPsAttachAllowFlg(NAS_EMM_AUTO_ATTACH_NOT_ALLOW);
    }
    else if (MMC_LMM_MO_DET_CS_ONLY == ulDetachType)
    {
        /* 设置不允许CS自动ATTACH*/
        NAS_MML_SetCsAttachAllowFlg(NAS_EMM_AUTO_ATTACH_NOT_ALLOW);
    }
    else
    {
        /* 设置不允许PS自动ATTACH*/
        NAS_MML_SetPsAttachAllowFlg(NAS_EMM_AUTO_ATTACH_NOT_ALLOW);

        /* 设置不允许CS自动ATTACH*/
        NAS_MML_SetCsAttachAllowFlg(NAS_EMM_AUTO_ATTACH_NOT_ALLOW);
    }
}

/*lint -e818*/
/*lint -e830*/
/*****************************************************************************
 Function Name   : NAS_LMM_LteCurrentSuspendProcAppDetReq
 Description     : LTE从模下对APP_DETACH_REQ消息的预处理。
 Input           : MMC_LMM_DETACH_REQ_STRU
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunjitan 00193151      2013-12-30  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LMM_LteCurrentSuspendProcAppDetReq
(
    const MMC_LMM_DETACH_REQ_STRU            *pstAppDetReq
)
{
    if(EMM_MS_REG == NAS_LMM_GetEmmCurFsmMS())
    {
        /* 如果只是DETACH CS域，那么只修改注册域回成功即可 */
        if(MMC_LMM_MO_DET_CS_ONLY == pstAppDetReq->ulDetachType)
        {
            NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
            return;
        }

        /* DETACH PS域，转到DEREG态，清空注册域(转状态自然会清)，也可能是处于紧急注册的无卡状态 */
        if (NAS_LMM_SIM_STATUS_UNAVAILABLE == NAS_LMM_GetSimState())
        {
            NAS_EMM_AdStateConvert(EMM_MS_DEREG,
                                   EMM_SS_DEREG_NO_IMSI,
                                   TI_NAS_EMM_STATE_NO_TIMER);
        }
        else
        {
            /* 有卡 */
            NAS_EMM_AdStateConvert(EMM_MS_DEREG,
                                   EMM_SS_DEREG_NO_CELL_AVAILABLE,
                                   TI_NAS_EMM_STATE_NO_TIMER);
        }

    }

   return;

}
/*****************************************************************************
 Function Name   : NAS_LMM_MsSuspendOrResumePreProcAppDetReq
 Description     : 挂起或解挂过程中对APP_DETACH_REQ消息的预处理。
 Input           : MMC_LMM_DETACH_REQ_STRU
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunjitan 00193151      2013-12-30  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LMM_MsSuspendOrResumePreProcAppDetReq
(
    const MMC_LMM_DETACH_REQ_STRU            *pstAppDetReq
)
{
    VOS_UINT32                          ulRet = NAS_LMM_MSG_DISCARD;

    /* 等挂起END和解挂等ESM和ERABM回复这两个子状态不可能收到，为保护若收到直接回成功 */
    if((EMM_SS_SUSPEND_WAIT_END == NAS_LMM_GetEmmCurFsmSS())
        ||(EMM_SS_RESUME_RRCRSM_WAIT_OTHER_RESUME == NAS_LMM_GetEmmCurFsmSS()))
    {
        NAS_LMM_PUBM_LOG_NORM("NAS_LMM_MsSuspendOrResumePreProcAppDetReq: SUSPEND_WAIT_END or RRCRSM_WAIT_OTHER_RESUME.");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_MsSuspendOrResumePreProcAppDetReq_ENUM,LNAS_FUNCTION_LABEL1);
        NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);
        return NAS_LMM_MSG_HANDLED;
    }

    /* 如果恰好是等MMC挂起回复状态，高优先级缓存到下一状态处理 */
    if(EMM_SS_SUSPEND_RRCORI_WAIT_MMC_SUSPEND == NAS_LMM_GetEmmCurFsmSS())
    {
        return NAS_LMM_STORE_HIGH_PRIO_MSG;
    }

    /* 其它状态根据当前UE的注册域和DETACH类型，判断是否可以直接回成功 */
    switch(NAS_LMM_GetEmmInfoRegDomain())
    {
                /* 注册域NULL直接回成功 */
        case    NAS_LMM_REG_DOMAIN_NULL:

                NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);
                ulRet = NAS_LMM_MSG_HANDLED;

                break;

                /* 注册域为CS直接回成功， 除PS DETACH之外需清空注册域 */
        case    NAS_LMM_REG_DOMAIN_CS:

                if(MMC_LMM_MO_DET_PS_ONLY != pstAppDetReq->ulDetachType)
                {
                    NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_NULL);
                }

                NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);
                ulRet = NAS_LMM_MSG_HANDLED;

                break;

                /* 注册域为PS仅CS DETACH直接回成功，其余进状态机处理 */
        case    NAS_LMM_REG_DOMAIN_PS:

                if(MMC_LMM_MO_DET_CS_ONLY == pstAppDetReq->ulDetachType)
                {
                    NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);
                    ulRet = NAS_LMM_MSG_HANDLED;
                }

                break;

                /* 注册域为CS_PS，收到CS DETACH，除CSFB场景外，全都直接在此回复MMC*/
        case    NAS_LMM_REG_DOMAIN_CS_PS:

                /* 无论挂起还是解挂过程中，只要不是CSFB流程均在此直接回复CS DETACH */
                if ((LRRC_LMM_SUS_CAUSE_CSFB != NAS_EMM_GetSuspendCause())
                    &&(MMC_LMM_MO_DET_CS_ONLY == pstAppDetReq->ulDetachType))
                {
                    NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
                    NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);
                    ulRet = NAS_LMM_MSG_HANDLED;
                }

                break;

        default:
                break;
    }

    #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

    /* 如果是PS DETACH，且不用进状态机处理，在此处通知ESM清除所有EHRPD承载记录 */
    if ((NAS_LMM_MSG_HANDLED == ulRet)
      &&(MMC_LMM_MO_DET_CS_ONLY != pstAppDetReq->ulDetachType))
    {
        NAS_EMM_SndEsmClearAllClBearerNotify();
    }
    #endif

    return ulRet;

}
/*lint +e830*/
/*lint +e818*/
/*****************************************************************************
 Function Name   : NAS_LMM_IsSvlteOrLcNeedLocalDetach
 Description     : 是否因Svlte或CL离网脱网重选等原因需要本地DETACH
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunjitan 00193151      2013-12-30  Draft enact
*****************************************************************************/
VOS_UINT32  NAS_LMM_IsSvlteOrLcNeedLocalDetach(VOS_VOID)
{
    if (((NAS_EMM_YES == NAS_MML_GetSvlteSupportFlag())||(NAS_EMM_YES == NAS_MML_GetLcEnableFlg()))
        &&(NAS_LMM_LOCAL_DETACH_FLAG_VALID == NAS_MML_GetPsLocalDetachFlag()))
    {
        NAS_LMM_PUBM_LOG_INFO("NAS_LMM_IsSvlteOrLcNeedLocalDetach: Need local detach.");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_IsSvlteOrLcNeedLocalDetach_ENUM,LNAS_FUNCTION_LABEL1);
        return  NAS_EMM_YES;
    }

    return NAS_EMM_NO;
}

/*****************************************************************************
 Function Name   : NAS_LMM_MsRegSsAnyLocalDetStateTrans
 Description     : 主状态为REG时LMM做本地DETACH时目标状态的转换。
 Input           : VOS_VOID
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunjitan 00193151      2014-05-04  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LMM_MsRegSsAnyLocalDetStateTrans(VOS_VOID)
{
    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_MsRegSsAnyLocalDetStateTrans is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_MsRegSsAnyLocalDetStateTrans_ENUM,LNAS_ENTRY);

/* sunjitan delete protect for ESM承载数目为0的本地DETACH使用 */

    switch(NAS_LMM_GetEmmCurFsmSS())
    {
        case    EMM_SS_REG_LIMITED_SERVICE:
                NAS_EMM_AdStateConvert(EMM_MS_DEREG,
                                       EMM_SS_DEREG_LIMITED_SERVICE,
                                       TI_NAS_EMM_STATE_NO_TIMER);
                break;

        case    EMM_SS_REG_PLMN_SEARCH:
                NAS_EMM_AdStateConvert(EMM_MS_DEREG,
                                       EMM_SS_DEREG_PLMN_SEARCH,
                                       TI_NAS_EMM_STATE_NO_TIMER);
                break;

        case    EMM_SS_REG_WAIT_ACCESS_GRANT_IND:
                NAS_EMM_AdStateConvert(EMM_MS_DEREG,
                                       EMM_SS_DEREG_ATTACH_NEEDED,
                                       TI_NAS_EMM_STATE_NO_TIMER);
                break;

        case    EMM_SS_REG_NO_CELL_AVAILABLE:
                NAS_EMM_AdStateConvert(EMM_MS_DEREG,
                                       EMM_SS_DEREG_NO_CELL_AVAILABLE,
                                       TI_NAS_EMM_STATE_NO_TIMER);
                break;

        default:
                NAS_EMM_AdStateConvert(EMM_MS_DEREG,
                                       EMM_SS_DEREG_NORMAL_SERVICE,
                                       TI_NAS_EMM_STATE_NO_TIMER);
                break;

    }
    /*lint +e960*/

    return;
}

/*****************************************************************************
 Function Name   : NAS_LMM_SvlteOrLcPsLocalDetachProc
 Description     : 需要进行本地DETACH的公共处理，用于SVLTE和CL离网重选时
                   需要L本地DETACH的场景，这种情况下，LMM根据当前所处状态设置DETACH
                   结束后的状态，DETACH后L仍处于主模态。
 Input           : VOS_VOID
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunjitan 00193151      2014-01-04  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LMM_SvlteOrLcPsLocalDetachProc
(
    const MMC_LMM_DETACH_REQ_STRU            *pstAppDetReq
)
{
    VOS_UINT32                          ulRet = NAS_LMM_MSG_DISCARD;
    MMC_LMM_TAU_RSLT_ENUM_UINT32        ulTauRslt;

    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_SvlteOrLcPsLocalDetachProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_SvlteOrLcPsLocalDetachProc_ENUM,LNAS_ENTRY);

    /* NULL状态不会走到这里 */

    NAS_LMM_EstingOrReleasingProcessTimerHandle();

    /* 如果处于压栈状态先出栈，然后按照出栈后的状态进行相应处理 */
    NAS_LMM_IfEmmHasBeenPushedThenPop();

    switch(NAS_LMM_GetEmmCurFsmMS())
    {
        /* 当前已经处于未注册态，直接回成功 */
        case    EMM_MS_DEREG:
                NAS_EMM_SaveAppMsgPara(pstAppDetReq->ulMsgId, pstAppDetReq->ulOpId);
                NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);

                /* 自研CL版本，PS DETACH通知ESM删除所有EHRPD相关承载记录 */
                NAS_EMM_SndEsmClearAllClBearerNotify();

                /* 本地DETACH释放资源:动态内存、赋初值 */
                NAS_LMM_DeregReleaseResource();

                /* 清除标识 */
                NAS_MML_SetPsLocalDetachFlag(NAS_LMM_LOCAL_DETACH_FLAG_INVALID);
                ulRet = NAS_LMM_MSG_HANDLED;
                break;

        /* 当前处于注册过程中，直接本地DETACH */
        case    EMM_MS_REG_INIT:

                /*向MMC发送LMM_MMC_ATTACH_CNF或LMM_MMC_ATTACH_IND消息*/
                NAS_EMM_AppSendAttOtherType(MMC_LMM_ATT_RSLT_MO_DETACH_FAILURE);

                /* 通知ESM执行了本地DETACH，并给MMC回DETACH成功 */
                NAS_EMM_EsmSendStatResult(EMM_ESM_ATTACH_STATUS_DETACHED);

                /* 自研CL版本，PS DETACH通知ESM删除所有EHRPD相关承载记录 */
                NAS_EMM_SndEsmClearAllClBearerNotify();

                NAS_EMM_AdStateConvert(EMM_MS_DEREG,
                                       EMM_SS_DEREG_NORMAL_SERVICE,
                                       TI_NAS_EMM_STATE_NO_TIMER);

                NAS_EMM_SaveAppMsgPara(pstAppDetReq->ulMsgId, pstAppDetReq->ulOpId);
                NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);

                /* 本地DETACH释放资源:动态内存、赋初值 */
                NAS_LMM_DeregReleaseResource();
                NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);

                /* 清除标识 */
                NAS_MML_SetPsLocalDetachFlag(NAS_LMM_LOCAL_DETACH_FLAG_INVALID);
                ulRet = NAS_LMM_MSG_HANDLED;
                break;

        /* 当前处于注册态，直接本地DETACH */
        case    EMM_MS_REG:

                /* 如果3411在运行，需要给MMC报TAU结果，以让MMC退出搜网状态机 */
                if (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_T3411))
                {
                    NAS_EMM_SetTauTypeNoProcedure();

                    ulTauRslt = MMC_LMM_TAU_RSLT_MO_DETACH_FAILURE;
                    NAS_EMM_MmcSendTauActionResultIndOthertype((VOS_VOID*)&ulTauRslt);
                }

                /* 通知ESM执行了本地DETACH，并给MMC回DETACH成功 */
                NAS_EMM_EsmSendStatResult(EMM_ESM_ATTACH_STATUS_DETACHED);
                NAS_EMM_SaveAppMsgPara(pstAppDetReq->ulMsgId, pstAppDetReq->ulOpId);
                NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);

                /* 根据不同的注册状态转到对应的未注册状态 */
                NAS_LMM_MsRegSsAnyLocalDetStateTrans();

                /* 本地DETACH释放资源:动态内存、赋初值 */
                NAS_LMM_DeregReleaseResource();
                NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);

                /* 清除标识 */
                NAS_MML_SetPsLocalDetachFlag(NAS_LMM_LOCAL_DETACH_FLAG_INVALID);
                ulRet = NAS_LMM_MSG_HANDLED;
                break;

        /* 当前处于TAU、SER过程中，进入状态机处理，因当前可能打断了其他业务流程 */
        case    EMM_MS_TAU_INIT:
        case    EMM_MS_SER_INIT:
                ulRet = NAS_LMM_MSG_DISCARD;
                break;

        /* Svlte和CL多模方案中，这两种状态一般不可能收到，如果收到就按普通情况下的DETACH处理，
           这种情况即使进状态机，也只能是本地DETACH，标识可以就在此处清除，但不能释放链路，
           以免状态压栈导致收到异系统过程中的外部消息被误丢掉 */
        case    EMM_MS_SUSPEND:
        case    EMM_MS_RESUME:
                ulRet = NAS_LMM_MsSuspendOrResumePreProcAppDetReq(pstAppDetReq);

                /* 清除标识不释放链路(一般也不会有) */
                NAS_MML_SetPsLocalDetachFlag(NAS_LMM_LOCAL_DETACH_FLAG_INVALID);
                break;

        default:
                /* 其它状态统一转到DEREG_NORMAL */
                NAS_EMM_EsmSendStatResult(EMM_ESM_ATTACH_STATUS_DETACHED);
                NAS_EMM_AdStateConvert(EMM_MS_DEREG,
                                       EMM_SS_DEREG_NORMAL_SERVICE,
                                       TI_NAS_EMM_STATE_NO_TIMER);
                NAS_EMM_SaveAppMsgPara(pstAppDetReq->ulMsgId, pstAppDetReq->ulOpId);
                NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);

                /* 本地DETACH释放资源:动态内存、赋初值 */
                NAS_LMM_DeregReleaseResource();
                NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);

                /* 清除标识 */
                NAS_MML_SetPsLocalDetachFlag(NAS_LMM_LOCAL_DETACH_FLAG_INVALID);
                ulRet = NAS_LMM_MSG_HANDLED;
                break;
    }

    return ulRet;
}


/*****************************************************************************
 Function Name   : NAS_LMM_ProcDetReqWithReseaonNon3gppAttach
 Description     : CL多模情况下，关闭LTE的DETACH的处理。
 Input           : VOS_VOID
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunjitan 00193151      2014-02-17  Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LMM_ProcDetReqWithReseaonNon3gppAttach
(
    const MMC_LMM_DETACH_REQ_STRU            *pstAppDetReq
)
{
    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_ProcDetReqWithReseaonNon3gppAttach: enter.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_ProcDetReqWithReseaonNon3gppAttach_ENUM,LNAS_ENTRY);

    /* CL多模针对本地DETACH的处理与Svlte和CL离网脱网重选处理基本相同 */
    return NAS_LMM_SvlteOrLcPsLocalDetachProc(pstAppDetReq);

}

/*****************************************************************************
 Function Name   : NAS_LMM_ProcDetReqWithReseaonNon3gppAttach
 Description     : 根据当前状态处理app detach req
 Input           : VOS_VOID
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixintiao 00258641      2014-07-30  Draft Enact
*****************************************************************************/

VOS_UINT32  NAS_LMM_ProcAppDetReq
(
    const MMC_LMM_DETACH_REQ_STRU            *pstAppDetReq
)
{
    VOS_UINT32                          ulRet = NAS_LMM_MSG_DISCARD;
    VOS_UINT32                          ulCurEmmStat;

    /*获取EMM当前状态*/
    ulCurEmmStat = NAS_LMM_PUB_COMP_EMMSTATE(NAS_EMM_CUR_MAIN_STAT, NAS_EMM_CUR_SUB_STAT);

    if((NAS_EMM_CONN_ESTING == NAS_EMM_GetConnState())
       || (NAS_EMM_CONN_RELEASING == NAS_EMM_GetConnState())
       || (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsStaTimerRunning(TI_NAS_EMM_STATE_T3440))
       || (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_REATTACH_DELAY)))
    {
        NAS_EMM_SaveAppMsgPara(pstAppDetReq->ulMsgId, pstAppDetReq->ulOpId);
        return  NAS_LMM_STORE_HIGH_PRIO_MSG;
    }

    switch(ulCurEmmStat)
    {
        /*直接回复APP去注册成功,状态不转换*/
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_DEREG, EMM_SS_DEREG_NORMAL_SERVICE):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_DEREG, EMM_SS_DEREG_NO_IMSI):

                /* 如果是PS DETACH，且不用进状态机处理，在此处通知ESM清除所有EHRPD承载记录 */
                if (MMC_LMM_MO_DET_CS_ONLY != pstAppDetReq->ulDetachType)
                {
                    NAS_EMM_SndEsmClearAllClBearerNotify();
                }

                NAS_EMM_SaveAppMsgPara(pstAppDetReq->ulMsgId, pstAppDetReq->ulOpId);
                NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);
                ulRet = NAS_LMM_MSG_HANDLED;
                break;

        /*丢弃APP去注册请求消息*/
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_DEREG_INIT, EMM_SS_DETACH_WAIT_CN_DETACH_CNF):

                NAS_LMM_PUBM_LOG_NORM("NAS_LMM_PreProcAppDetReq: ESM or RABM ERROR, discard it.");
                TLPS_PRINT2LAYER_INFO(NAS_LMM_ProcAppDetReq_ENUM,LNAS_FUNCTION_LABEL1);
                NAS_EMM_SaveAppMsgPara(pstAppDetReq->ulMsgId, pstAppDetReq->ulOpId);
                ulRet = NAS_LMM_MSG_HANDLED;
                break;

        /*在AUTH_INIT+WAIT_CN_AUTH_CNF过程中，低优先级缓存 */
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_AUTH_INIT, EMM_SS_AUTH_WAIT_CN_AUTH):

                NAS_EMM_SaveAppMsgPara(pstAppDetReq->ulMsgId, pstAppDetReq->ulOpId);
                ulRet = NAS_LMM_STORE_LOW_PRIO_MSG;
                break;

        default:
                ulRet = NAS_LMM_MSG_DISCARD;
                break;
    }
    return ulRet;
}

/*****************************************************************************
 Function Name   : NAS_LMM_PreProcAppDetReq
 Description     : APP_DETACH_REQ消息预处理。
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2009-7-6  Draft Enact
    2.X00148705                 2009-08-17 添加缓存的处理
    3.Z00148421                 2009-08-19 BJ9D01716:收到APP_DETACH,UE不可以自动ATTACH
    4.Y00159566                 2010-02-08 梳理AppDetach流程
    5.zhengjunyan 00148421      2010-11-16 MOD:删除冗余代码+判断APP_DETACH的类型
    6.zhengjunyan 00148421      2010-12-20 mod:NULL状态(开机或者关机过程中，收到APP_DETACH_REQ,
                                           设置AUTO_ATTACH_NOT_ALLOW,并回复APP_DETACH_CNF
    7.sunjitan 00193151         2013-12-30 针对挂起和解挂过程中收到的场景进行了修改。
    8.sunjitan 00193151         2014-01-22 DTS2014012300601 mod again
    9.sunjitan 00193151         2014-05-05 DTS2014050404379 修改CL离网重选本地DETACH的处理
    10.lifuxin  00253982         2014-10-31 建链流程重构
*****************************************************************************/
VOS_UINT32  NAS_LMM_PreProcAppDetReq(MsgBlock  * pMsg)
{
    VOS_UINT32                          ulRet = NAS_LMM_MSG_DISCARD;
    MMC_LMM_DETACH_REQ_STRU             *pstAppDetReq = VOS_NULL_PTR;

    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_PreProcAppDetReq: enter.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcAppDetReq_ENUM,LNAS_ENTRY);

    pstAppDetReq                        = (VOS_VOID*)pMsg;

    /* DETACH类型错误，丢弃 */
    if(MMC_LMM_MO_DETACH_TYPE_BUTT <= pstAppDetReq->ulDetachType)
    {
        NAS_LMM_PUBM_LOG_NORM("NAS_LMM_PreProcAppDetReq: DetachType ERROR!");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcAppDetReq_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_HANDLED;
    }

    /* 根据DETACH类型对相应的域设置不允许注册标识 */
    NAS_LMM_SetAttachAllowFlgByDetachType(pstAppDetReq->ulDetachType);

    /*保存DETACH的请求类型*/
    NAS_EMM_GLO_SetDetTypeMo(pstAppDetReq->ulDetachType);

    /* NULL状态时直接回复成功 */
    if (EMM_MS_NULL == NAS_LMM_GetEmmCurFsmMS())
    {
        NAS_LMM_PUBM_LOG_NORM("NAS_LMM_PreProcAppDetReq: LTE CUR NULL.");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcAppDetReq_ENUM,LNAS_FUNCTION_LABEL1);

        /*保存APP参数，只能在各分支中保存，防止APP DETACH打断APP ATTACH导致之前记录的参数丢失 */
        NAS_EMM_SaveAppMsgPara(pstAppDetReq->ulMsgId, pstAppDetReq->ulOpId);
        NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);
        return NAS_LMM_MSG_HANDLED;
    }

    /* 从模状态时直接回复成功 */
    if (NAS_EMM_IS_SUSPEND == NAS_EMM_IsSuspended())
    {
        NAS_LMM_PUBM_LOG_NORM("NAS_LMM_PreProcAppDetReq: LTE CUR SUSPEND.");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcAppDetReq_ENUM,LNAS_FUNCTION_LABEL2);
        NAS_EMM_SaveAppMsgPara(pstAppDetReq->ulMsgId, pstAppDetReq->ulOpId);
        NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);
        NAS_LMM_LteCurrentSuspendProcAppDetReq(pstAppDetReq);
        return NAS_LMM_MSG_HANDLED;
    }

    /* 用户请求DETACH类型为IMSI，UE模式为PS，则直接回复成功 */
    if ((NAS_EMM_NO == NAS_EMM_IsCsPsUeMode()) && (MMC_LMM_MO_DET_CS_ONLY == pstAppDetReq->ulDetachType))
    {
        NAS_EMM_SaveAppMsgPara(pstAppDetReq->ulMsgId, pstAppDetReq->ulOpId);
        NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);
        return NAS_LMM_MSG_HANDLED;
    }

    /* CL多模情况下，关闭LTE时MMC会先下发DETACH请求，原因为NON_3GPP_ATTACH，
       此时LMM只能执行本地DETACH，不能发送空口消息 */
    if((MMC_LMM_MO_DET_CS_ONLY != pstAppDetReq->ulDetachType)
        &&(MMC_LMM_DETACH_RESEAON_NON_3GPP_ATTACH == pstAppDetReq->ulDetachReason))
    {
        return NAS_LMM_ProcDetReqWithReseaonNon3gppAttach(pstAppDetReq);
    }

    /* 当前支持SVLTE或者当前形态为C+L，且当前为PS ONLY场景(高层只能下发PS的DETACH，此为接口约定)，
       当GU标识只能进行本地DETACH时，不考虑当前是否能发起空口消息，均做本地DETACH */
    /*lint -e960*/
    if ((MMC_LMM_MO_DET_PS_ONLY == pstAppDetReq->ulDetachType)
        &&(NAS_EMM_YES == NAS_LMM_IsSvlteOrLcNeedLocalDetach()))
    /*lint +e960*/
    {
        /* 执行本地DETACH的处理 */
        return NAS_LMM_SvlteOrLcPsLocalDetachProc(pstAppDetReq);
    }

    /* 挂起或解挂过程中收到用户请求DETACH，进行特殊处理 */
    if((EMM_MS_SUSPEND == NAS_LMM_GetEmmCurFsmMS())
        ||(EMM_MS_RESUME == NAS_LMM_GetEmmCurFsmMS()))
    {
        NAS_EMM_SaveAppMsgPara(pstAppDetReq->ulMsgId, pstAppDetReq->ulOpId);
        return NAS_LMM_MsSuspendOrResumePreProcAppDetReq(pstAppDetReq);
    }
    /* leixiantiao 00258641 降低圈复杂度 2014-7-30 begin */
    ulRet = NAS_LMM_ProcAppDetReq(pstAppDetReq);
    /* leixiantiao 00258641 降低圈复杂度 2014-7-30 end */
    return ulRet;

}

/*****************************************************************************
 Function Name  : NAS_LMM_IntraMsgProcess
 Discription    : MM PID 内部消息处理
 Input          :
 Output         : None
 Return         : None
 History:
      1.  Name+ID  yyyy-mm-dd  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LMM_IntraMsgProcess(VOS_VOID)
{
    VOS_UINT32                          ulLoop;
    NAS_EMM_EVENT_TYPE_ENUM_UINT32      ulEventType;
    VOS_UINT32                          ulRet               = NAS_LMM_SUCC;
    VOS_UINT8                          *pucMsg              = NAS_LMM_NULL_PTR;


    /* 循环处理队列数据 */
    for ( ulLoop = 0; ulLoop < (NAS_LMM_INTRA_MSG_MAX_NUM - 1); ulLoop++ )
    {
        /* 获取队列中一条消息 */
        pucMsg = NAS_LMM_GetIntraMsgFromQueue();

        /*lint -e960*/
        if (NAS_LMM_NULL_PTR == pucMsg)
        {
            break;
        }
        /*lint +e960*/

        /* 获取事件类型*/
        ulRet = NAS_LMM_GetEventType((MsgBlock *)pucMsg, &ulEventType);
        if(NAS_EMM_SUCC != ulRet)
        {
            NAS_LMM_PUBM_LOG_ERR("NAS_LMM_IntraMsgProcess, ERR !!");
            TLPS_PRINT2LAYER_ERROR(NAS_LMM_IntraMsgProcess_ENUM,LNAS_ERROR);
            return ulRet;
        }

        /* 对内部消息进行状态机处理 */
        ulRet = NAS_LMM_MsgHandle((MsgBlock *)pucMsg, ulEventType);
    }

    return ulRet;
}


/*****************************************************************************
 Function Name  : NAS_LMM_BufMsgProcess
 Discription    : MM PID 缓存消息处理
                  缓存的消息要依次执行，
                  若某状态下缓存队列中的队头消息没有执行，则退出队列，不继续执
                  行缓存队列后续的消息;
                  若某状态下
 Input          :
 Output         : None
 Return         : None
 History:
      1.  Name+ID  yyyy-mm-dd  Draft Enact
      2.  X00148705 2009-08-17      稳态时处理完当前缓存的消息
*****************************************************************************/
VOS_UINT32 NAS_LMM_BufMsgProcess(VOS_VOID)
{

    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulProcBufferMsgFlag;
    VOS_UINT32                          ulProcBufferMsgCount = 0;

    NAS_LMM_ERROR_CODE_ENUM_UINT32       enEmmBufMsgProcRet;

    ulRet                               = NAS_LMM_SUCC;
    ulProcBufferMsgFlag                 = NAS_LMM_CONTINUE_TO_PROC_BUF_MSG;

    /* 分别处理MMC和EMM的两个并行状态机的buff 消息 */
    while ( NAS_LMM_CONTINUE_TO_PROC_BUF_MSG==ulProcBufferMsgFlag)
    {
        ulProcBufferMsgCount++;
        /* 如果当前缓存消息队列中有多于NAS_EMM_BUFFER_MSG_COUNT的消息，
        ** 清空消息队列并跳出循环
        */
        /*lint -e960*/
        if(NAS_EMM_BUFFER_MSG_COUNT<ulProcBufferMsgCount)
        {
            NAS_LMM_ClearBufMsgQue( NAS_LMM_PARALLEL_FSM_EMM , NAS_LMM_STORE_HIGH_PRIO_MSG );
            NAS_LMM_ClearBufMsgQue( NAS_LMM_PARALLEL_FSM_EMM , NAS_LMM_STORE_LOW_PRIO_MSG );

            NAS_LMM_PUBM_LOG_WARN("NAS_LMM_BufMsgProcess,Buffer Msg >NAS_EMM_BUFFER_MSG_COUNT");
            TLPS_PRINT2LAYER_WARNING(NAS_LMM_BufMsgProcess_ENUM,LNAS_FUNCTION_LABEL1);
            break;
        }
        /*lint +e960*/

        /* EMM缓存消息处理 */
        enEmmBufMsgProcRet = NAS_LMM_EmmBufMsgProcess();

        if(NAS_LMM_NOT_TRAVEL_BUFFER_MSG == enEmmBufMsgProcRet)
        {   /* 若两个状态机都不处理缓存消息，则跳出循环 */
            ulProcBufferMsgFlag         = NAS_LMM_STOP_PROCING_BUF_MSG;
        }
    }

    /* 如果要支持MMC的缓存处理，需要在此添加代码
    */

    return ulRet;
}


/*****************************************************************************
 Function Name   : NAS_LMM_EmmBufMsgProcess
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.h41410      2008-10-10  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LMM_EmmBufMsgProcess(    VOS_VOID)
{
    VOS_UINT32                          ulRsltOutMsgFromQue = NAS_LMM_NOT_TRAVEL_BUFFER_MSG;
    VOS_UINT32                          ulEmmStableOrNot;
    NAS_LMM_BUFF_MSG_STRU               stBufMsg;
    VOS_UINT32                          ulRslt;

    /* 初时化变量
    */
    stBufMsg.pBuffMsg                   = VOS_NULL_PTR;
    stBufMsg.ulEvtType                  = 0;

    /* 当前EMM是否进入了稳态 */
    ulEmmStableOrNot = NAS_EMM_JudgeStableState();

    if (NAS_LMM_STATE_IS_STABLE == ulEmmStableOrNot)
    {
        /*若当前EMM进入稳态，首先处理高优先级缓存消息 */
        ulRsltOutMsgFromQue = NAS_LMM_OutMsgFromQue(NAS_LMM_PARALLEL_FSM_EMM,
                                        NAS_LMM_STORE_HIGH_PRIO_MSG,
                                        &stBufMsg);

        if (VOS_NULL_PTR == stBufMsg.pBuffMsg)
        {
            /*若当前EMM进入稳态，处理低优先级缓存消息 */
            ulRsltOutMsgFromQue = NAS_LMM_OutMsgFromQue(NAS_LMM_PARALLEL_FSM_EMM,
                                        NAS_LMM_STORE_LOW_PRIO_MSG,
                                        &stBufMsg);
        }

    }
    else if (NAS_LMM_STATE_IS_UNSTABLE == ulEmmStableOrNot)
    {
        /*若当前EMM没有进入稳态，处理高优先级缓存消息 */
        ulRsltOutMsgFromQue = NAS_LMM_OutMsgFromQue(NAS_LMM_PARALLEL_FSM_EMM,
                                        NAS_LMM_STORE_HIGH_PRIO_MSG,
                                        &stBufMsg);
    }
    else
    {
        /*不处理*/
    }

    if (VOS_NULL_PTR != stBufMsg.pBuffMsg)
    {
        /* 打印消息类型 */
        NAS_LMM_PUBM_LOG1_NORM( "NAS_LMM_EmmBufMsgProcess:ulEvtType = ",
                            stBufMsg.ulEvtType );
        TLPS_PRINT2LAYER_INFO1(NAS_LMM_EmmBufMsgProcess_ENUM,LNAS_FUNCTION_LABEL1,
                            stBufMsg.ulEvtType);

        /* 进入状态机处理 */
        (VOS_VOID)NAS_LMM_MsgHandle((MsgBlock *)stBufMsg.pBuffMsg, stBufMsg.ulEvtType);

        /* 释放申请存放消息缓存的Buffer */
        ulRslt = NAS_COMM_FreeBuffItem(NAS_COMM_BUFF_TYPE_EMM,stBufMsg.pBuffMsg);

        if (NAS_COMM_BUFF_SUCCESS != ulRslt)
        {
            NAS_LMM_PUBM_LOG_WARN("NAS_LMM_EmmBufMsgProcess, Memory Free is not succ");
            TLPS_PRINT2LAYER_WARNING(NAS_LMM_EmmBufMsgProcess_ENUM,LNAS_FUNCTION_LABEL2);
        }

        /*再处理由该刚处理的buff消息可能产生的内部消息*/
        (VOS_VOID)NAS_LMM_IntraMsgProcess();
    }
    return ulRsltOutMsgFromQue;
}


VOS_UINT32  NAS_LMM_MmcBufMsgProcess(VOS_VOID)
{
    /* STUB FUNCTION */

    return NAS_LMM_NOT_TRAVEL_BUFFER_MSG;
}


VOS_UINT32  NAS_LMM_IsTransient(VOS_VOID)
{
    if ((NAS_EMM_CONN_RELEASING == NAS_EMM_GetConnState())
            ||(NAS_LMM_TIMER_RUNNING == NAS_LMM_IsStaTimerRunning(TI_NAS_EMM_STATE_T3440))
            ||(NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_REATTACH_DELAY))
            ||(NAS_EMM_CONN_ESTING == NAS_EMM_GetConnState())
            ||((EMM_MS_SUSPEND == NAS_LMM_GetEmmCurFsmMS())
                &&(EMM_SS_SUSPEND_RRCORI_WAIT_MMC_SUSPEND == NAS_LMM_GetEmmCurFsmSS()))
    /* 解决REG NORMAL_SERVICE、UPDATE和UPDATE_MM态下LRRC REL搜小区驻留前收到ESM紧急承载建立请求，由于空口发送失败，
       本地detach,发起紧急ATTACH问题
       方案:这三个子状态下，且当前Conn State为wait sysinfo，收到ESM紧急承载建立请求，先高优先级缓存，
       等到收到LRRC系统消息后处理(收到系统消息后CONN State会转到idle态)*/
            ||((NAS_EMM_CONN_WAIT_SYS_INFO == NAS_EMM_GetConnState())
                /*&&(VOS_TRUE == NAS_LMM_GetEmmInfoIsEmerPndEsting())*/
                &&((EMM_MS_REG == NAS_LMM_GetEmmCurFsmMS())
                    &&((EMM_SS_REG_NORMAL_SERVICE == NAS_LMM_GetEmmCurFsmSS())
                        ||(EMM_SS_REG_ATTEMPTING_TO_UPDATE == NAS_LMM_GetEmmCurFsmSS())
                        ||(EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM == NAS_LMM_GetEmmCurFsmSS())))))
    {
        return NAS_EMM_YES;
    }
    else
    {
        return NAS_EMM_NO;
    }
}

/*****************************************************************************
 Function Name   : NAS_EMM_JudgeStableState
 Description     : 判断EMM是否进入稳态了
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.h41410      2008-11-12  Draft Enact
    2.X00148705   2009-08-17  修改稳态的判断
    3.lifuxin     2014-11-06  建链重构
*****************************************************************************/
VOS_UINT32  NAS_EMM_JudgeStableState(   VOS_VOID)
{
    /*对于高优先级的判断必须放在开头*/
    if(NAS_EMM_YES == NAS_LMM_IsTransient())
    {
        return NAS_LMM_STATE_IS_TRANSIENT;
    }
    /* 主状态为REG时，子状态除了EMM_SS_REG_IMSI_DETACH_WATI_CN_DETACH_CNF和
       EMM_SS_REG_IMSI_DETACH_WAIT_RRC_REL_IND之外，都是稳态 */
    else if(EMM_MS_REG == NAS_LMM_GetEmmCurFsmMS())
    {
        if (EMM_SS_REG_IMSI_DETACH_WATI_CN_DETACH_CNF == NAS_LMM_GetEmmCurFsmSS())
        {
            return  NAS_LMM_STATE_IS_UNSTABLE;
        }

        return  NAS_LMM_STATE_IS_STABLE;
    }
     /*add by lifuxin for Lnas est&rel process re-construct*/
    else if(EMM_MS_DEREG == NAS_LMM_GetEmmCurFsmMS())
    {
        return  NAS_LMM_STATE_IS_STABLE;
    }
    else
    {
        return  NAS_LMM_STATE_IS_UNSTABLE;
    }
}




/*****************************************************************************
 Function Name   : NAS_LMM_PUBM_Init
 Description     : PUBM模块初始化
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.h41410      2008-10-22  此函数仅用于 上电PID初始化，
                              其他情况的PUBM初始化请使用:  NAS_LMM_PUBM_Init
    2.X00148705             2009-12-31 增加自动开机检查
    3.Z00148421   2010-12-20   添加:自动ATTACH初始化
*****************************************************************************/
VOS_VOID  NAS_LMM_PUBM_Init_FidInit( VOS_VOID )
{

    NAS_LMM_FSM_STATE_STRU              stEmmDstState;

    NAS_LMM_PUBM_LOG_INFO(
    "NAS_LMM_PUBM_Init_FidInit          START INIT...");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_PUBM_Init_FidInit_ENUM,LNAS_ENTRY);

    /*清空 PUBM 内存为全 0*/
    /*lint -e960*/
    NAS_LMM_MEM_SET_S(  &(g_stMmMainContext),
                        sizeof(NAS_LMM_MAIN_CONTEXT_STRU),
                        0,
                        sizeof(NAS_LMM_MAIN_CONTEXT_STRU));

    /* g_stMmMainContext.stNasMmFsm MM状态机 初始化 */
    NAS_LMM_MainContextInit();

    /* g_stMmMainContext.stNasMmAuxFsm 辅助状态机 初始化 */
    NAS_LMM_AuxFsmInit();

    /* g_stMmMainContext.astMmTimerSta 定时器 初始化 */
    NAS_LMM_TimerInit();

    /* g_stMmMainContext.pstMmIntraMsgQueue 内部消息队列 初始化  */
    NAS_LMM_IntraMsgQueueInit();

    /* 初始化全局变量g_stSMsgSysInfCounter,用于记录边缘状态下收到系统消息的次数 */
    NAS_LMM_MEM_SET_S(  &(g_stMsgSysInfCnt),
                        sizeof(NAS_LMM_SYSINFO_COUNT_STRU),
                        0,
                        sizeof(NAS_LMM_SYSINFO_COUNT_STRU));
    /*lint +e960*/

    #ifdef PS_ITT_PC_TEST_NAS_ST
    /* 初始化 g_ulMmcSerRegFlag */
    NAS_Emm_Get_Mmc_Srv_Reg_Flag()= NAS_LMM_MMC_SER_REG_STAT_CLOSE_FLAG;
    #else
    NAS_Emm_Get_Mmc_Srv_Reg_Flag()= NAS_LMM_MMC_SER_REG_STAT_OPEN_FLAG;
    #endif

    /* 主状态设置为NULL */
    stEmmDstState.enFsmId               = NAS_LMM_PARALLEL_FSM_EMM;
    stEmmDstState.enMainState           = EMM_MS_NULL;
    stEmmDstState.enStaTId              = TI_NAS_EMM_STATE_NO_TIMER;


    stEmmDstState.enSubState            = EMM_SS_NULL_WAIT_APP_START_REQ;

    NAS_LMM_StaTransProc(stEmmDstState);

    /* MM软调初始化 */
    NAS_LMM_DebugInit();

    #if (FEATURE_PTM == FEATURE_ON)
    NAS_LMM_FtmInfoInit();
    /*全局信息放在pid初始化的时候执行，执行一次，后面不再重复*/
    LNAS_InitErrLogGloInfo(NAS_EMM_GetErrlogGloInfoAddr());
    #endif

    NAS_EMM_SecuDmaMalloc();
    NAS_EMM_SetLteNoSubscribeLteRegFlag(NAS_LMM_NO_REG_SUCC_ON_LTE);

    return;
}


/*****************************************************************************
 Function Name   : NAS_LMM_PUBM_Init
 Description     : PUBM模块初始化
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.h41410      2008-10-22  Draft Enact
    2.z00148421   2010-12-27  添加自动ATTACH
*****************************************************************************/
VOS_VOID  NAS_LMM_PUBM_Init( VOS_VOID )
{
    NAS_LMM_PUBM_LOG_NORM("NAS_LMM_PUBM_Init                  START INIT...");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_PUBM_Init_ENUM,LNAS_ENTRY);

    /*清空 PUBM 内存为全 0*/
    /*lint -e960*/
    NAS_LMM_MEM_SET_S(  &(g_stMmMainContext),
                        sizeof(NAS_LMM_MAIN_CONTEXT_STRU),
                        0,
                        sizeof(NAS_LMM_MAIN_CONTEXT_STRU));
    /*lint +e960*/

    /* g_stMmMainContext.stNasMmFsm MM状态机 初始化 */
    NAS_LMM_MainContextInit();

    /* g_stMmMainContext.stNasMmAuxFsm 辅助状态机 初始化 */
    NAS_LMM_AuxFsmInit();

    /* g_stMmMainContext.astMmTimerSta 定时器 初始化 */
    NAS_LMM_TimerInit();

    /* g_stMmMainContext.pstMmIntraMsgQueue 内部消息队列 初始化 */
    NAS_LMM_IntraMsgQueueInit();

    #if (FEATURE_ON == FEATURE_DSDS)
    NAS_LMM_DebugInit();
    #endif

    return;
}

/*****************************************************************************
 Function Name   : NAS_LMM_MainContextInit
 Description     : g_stMmMainContext.stNasMmFsm 主控制结构 初始化
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.h41410      2008-10-23  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_LMM_MainContextInit( VOS_VOID )
{
    /* g_stMmMainContext.stNasMmFsm--EMM状态机 初始化*/
    NAS_EMM_FsmInit();

    /* g_stMmMainContext.stNasMmFsm--MMC状态机 初始化*/
    /*NAS_EMMC_FsmInit();*/

    /* g_stMmMainContext.stNasMmFsm--SECU状态机 初始化*/
    NAS_Secu_FsmInit();

    /* 初始化EMM缓存区 */
    NAS_COMM_InitBuff(NAS_COMM_BUFF_TYPE_EMM);

    return;
}


/*****************************************************************************
 Function Name   : NAS_LMM_AuxFsmInit
 Description     : g_stMmMainContext.stNasMmAuxFsm 辅助状态机 初始化
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.h41410      2008-10-23  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_LMM_AuxFsmInit( VOS_VOID)
{
    NAS_LMM_AUXILIARY_FSM_STRU          *pMmAuxFsm;


    NAS_LMM_PUBM_LOG_NORM(
    "NAS_LMM_AuxFsmInit                 START INIT...");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_AuxFsmInit_ENUM,LNAS_ENTRY);
    /* 当前状态初始化 */
    pMmAuxFsm = NAS_LMM_GetMmAuxFsmAddr();

    /*RRC连接状态*/
    pMmAuxFsm->ucRrcConnState           = NAS_EMM_CONN_IDLE;

    /*NAS APP注册状态*/
    pMmAuxFsm->enNasAppRegState         = NAS_APP_RS_NOT_REG_AND_NOT_SRCH_OPERATOR;

    /*UPDATE STATUS*/
    NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_UPDATED_EU1);

    /* LTE状态设置为挂起 */
    NAS_EMM_GetCurLteState()            = NAS_LMM_CUR_LTE_SUSPEND;
    /* 注册/服务状态上报上移MMC，删除注册/服务状态相关代码 */
    return;
}

/*****************************************************************************
 Function Name   : NAS_LMM_TimerInit
 Description     : g_stMmMainContext.astMmTimerSta 定时器 初始化
                   g_stMmMainContext.astMmTimerPtl 定时器 初始化
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.h41410      2008-10-23  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_LMM_TimerInit(           VOS_VOID)
{
    /*初始化所有状态定时器*/
    NAS_LMM_InitAllStateTimer();

    /*初始化所有协议定时器*/
    NAS_LMM_InitAllPtlTimer();

    return;
}

/*****************************************************************************
 Function Name   : NAS_LMM_IntraMsgQueueInit
 Description     : g_stMmMainContext.stMmIntraMsgQueue 定时器 初始化
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.h41410      2008-10-23  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LMM_IntraMsgQueueInit(   VOS_VOID)
{
    NAS_LMM_INTRA_MSG_QUEUE_STRU        *pstMmIntraMsgQueue;

    NAS_LMM_PUBM_LOG_NORM("NAS_LMM_IntraMsgQueueInit: ENTER.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_IntraMsgQueueInit_ENUM,LNAS_ENTRY);

    pstMmIntraMsgQueue = NAS_LMM_GetMmIntrMsgQueueAddr();

    pstMmIntraMsgQueue->usHeader        =NAS_LMM_INTRA_MSG_HEAD_INIT;
    pstMmIntraMsgQueue->usTail          =NAS_LMM_INTRA_MSG_TAIL_INIT;


    return;
}


/*****************************************************************************
 Function Name   : NAS_LMM_PreProcIntraSystemInfoInd
 Description     : ID_NAS_LMM_INTRA_MMC_EMM_SYS_INFO_IND消息预处理。
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.X00148705      2009-08-17  Draft Enact
    2.z00148421      2011-04-25  MOD:intra_rat
*****************************************************************************/
VOS_UINT32  NAS_LMM_PreProcIntraSystemInfoInd(MsgBlock  * pMsg)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulCurEmmStat;
    EMMC_EMM_SYS_INFO_IND_STRU          *pstsysinfo;

    pstsysinfo = (EMMC_EMM_SYS_INFO_IND_STRU *)pMsg;

    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_PreProcIntraSystemInfoInd: enter.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcIntraSystemInfoInd_ENUM,LNAS_ENTRY);
    /*l00258641 消除fortify告警 begin*/
    /*ulRet                               = NAS_LMM_MSG_DISCARD;*/
    /*l00258641 消除fortify告警 begin*/


    /* 如果RRC连接状态处于释放过程中，设置为IDLE */
    /*lint -e960*/
    /*收到系统消息，当前RRC已经驻留成功，设置成IDLE态，以便后续建链*/
    if(NAS_EMM_CONN_WAIT_SYS_INFO == NAS_EMM_GetConnState())
    {
        NAS_EMM_SetConnState(NAS_EMM_CONN_IDLE);
    }

    /*lint +e960*/

    if(NAS_LMM_TIMER_RUNNING == NAS_LMM_IsStaTimerRunning(TI_NAS_EMM_STATE_T3440))
    {
        return NAS_LMM_MSG_HANDLED;
    }

    /*获取EMM当前状态*/
    ulCurEmmStat = NAS_LMM_PUB_COMP_EMMSTATE(NAS_EMM_CUR_MAIN_STAT,
                                            NAS_EMM_CUR_SUB_STAT);

    if((EMMC_EMM_CELL_STATUS_ANYCELL == pstsysinfo->ulCellStatus)
     &&(NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_DEREG, EMM_SS_DEREG_NO_IMSI) == ulCurEmmStat))
     {
         NAS_LMM_PUBM_LOG_ERR("NAS_LMM_PreProcIntraSystemInfoInd:DEREG NO IMSI anycell");
         TLPS_PRINT2LAYER_ERROR(NAS_LMM_PreProcIntraSystemInfoInd_ENUM,LNAS_FUNCTION_LABEL1);
         return NAS_LMM_MSG_DISCARD;
    }

    switch(ulCurEmmStat)
    {
        /* 这个过程中收到系统消息，丢弃处理*/

        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_RESUME, EMM_SS_RESUME_RRCORI_WAIT_SYS_INFO_IND):
                ulRet = NAS_EMM_PreProcSysWhenResumingReverse(pstsysinfo);
                break;

        default:
                ulRet = NAS_LMM_MSG_DISCARD;
                break;
    }

    return ulRet;

}


VOS_UINT32  NAS_LMM_MsNullSsNullReadingUsimTimerExp (MsgBlock  * pMsg)
{
    NAS_LMM_FSM_STATE_STRU               EmmState;
    VOS_UINT32                          ulSendResult;

    NAS_LMM_UEID_STRU                    *pstUeId;


    (VOS_VOID)                          (pMsg);

    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_MsNullSsNullReadingUsimTimerExp is entered");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_MsNullSsNullReadingUsimTimerExp_ENUM,LNAS_ENTRY);

    /*如果读取到的GUTI无效但是安全上下文有效，则删除本地和NV中的上下文*/
    pstUeId                             = NAS_LMM_GetEmmInfoUeidAddr();

    if((NAS_EMM_BIT_NO_SLCT == pstUeId->bitOpGuti)
        &&(EMM_CUR_SECU_NOT_EXIST!= NAS_LMM_GetSecuCurFsmCS()))
    {
        NAS_EMM_ClearCurSecuCntxt();
        NAS_LMM_WriteEpsSecuContext(NAS_NV_ITEM_DELETE);
    }

    /* Read NV Files*/
    NAS_LMM_ProcessNvData();

    /* 向MMC发送MMC_EMM_START_REQ(正常启动)消息 */
    ulSendResult = NAS_EMM_PLMN_SendMmcStartReq(EMMC_EMM_START_REQ_CAUSE_NORMAL_START);
    if (NAS_EMM_SEND_MMC_ERR == ulSendResult)
    {
        /* 打印函数，ERROR_LEVEL */
        NAS_LMM_PUBM_LOG_ERR("NAS_EMM_PLMN_SendMmcStartReq : Send IntraMsg Failure!!!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_MsNullSsNullReadingUsimTimerExp_ENUM,LNAS_FAIL);
        return NAS_LMM_MSG_HANDLED;
    }

    /* 启动TI_NAS_EMM_WAIT_MMC_START_CNF_TIMER */
    NAS_LMM_StartStateTimer(TI_NAS_EMM_WAIT_MMC_START_CNF_TIMER);

    /* 将状态转移至MS_NULL + SS_WAIT_MMC_START_CNF状态 */
    EmmState.enFsmId                    = NAS_LMM_PARALLEL_FSM_EMM;
    EmmState.enMainState                = EMM_MS_NULL;
    EmmState.enSubState                 = EMM_SS_NULL_WAIT_MMC_START_CNF;
    EmmState.enStaTId                   = TI_NAS_EMM_WAIT_MMC_START_CNF_TIMER;
    NAS_LMM_StaTransProc(EmmState);

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_LMM_EmmAndMmcGlobInfoClear
 Description     : 全局变量的清零
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.yangfan 00159566      2009-9-19  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_LMM_EmmAndMmcGlobInfoClear( VOS_VOID )
{
    /* EMM g_stEmmInfo 清空 */
    /*lint -e960*/
    NAS_LMM_MEM_SET_S(  NAS_LMM_GetEmmInfoAddr(),
                        sizeof(NAS_LMM_PUB_INFO_STRU),
                        0,
                        sizeof(NAS_LMM_PUB_INFO_STRU));
    /*lint +e960*/

    /*计数器全局变量清零*/
    NAS_EMM_GET_SEND_COUNTER() = NAS_NVIM_SEND_COUNTER_NONE;

    /*开机初始化安全文件长度为0 */
    NAS_EMM_GET_USIM_SECU_FILE_LEN() = 0 ;

    NAS_EMM_GET_USIM_FILE_TYPE() = NAS_LMM_USIM_OPTIONAL_FILE;

    return;
}

/*****************************************************************************
 Function Name   : NAS_LMM_EmmSubModGlobInit
 Description     : EMM的各子模块的控制结构的清空和初始化
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.h41410      2009-10-29  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_LMM_EmmSubModGlobInit(VOS_VOID )
{
    NAS_EMM_AttachInit();
    NAS_EMM_DetachInit();
    NAS_EMM_TAU_Init();
    NAS_EMM_SER_Init();
    NAS_EMM_GutiInit();
    NAS_EMM_IdenInit();
    NAS_EMM_MrrcInit();
    NAS_EMM_SecuInit();

    return;
}

/*****************************************************************************
 Function Name   : NAS_LMM_EmmSubModGlobClear
 Description     : 清除EMM子模块资源
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.liuwenyu 00143951      2010-5-6  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LMM_EmmSubModGlobClear(VOS_VOID)
{
    NAS_EMM_AttachInit();
    NAS_EMM_DetachInit();
    /*NAS_EMM_TauClearResouce();*/
    /*NAS_EMM_SER_RelResource();*/
    NAS_EMM_TAU_ClearResouce();
    NAS_EMM_SER_ClearResource();
    NAS_EMM_GutiInit();
    NAS_EMM_IdenInit();
    NAS_EMM_SecuInit();
    NAS_EMM_MrrcInit();

    return;
}
/*****************************************************************************
 Function Name   : NAS_LMM_SetUsimInvalidDetachType
 Description     : 设置拔卡时的DETACH类型
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong 00150010      2011-09-29  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LMM_SetUsimInvalidDetachType( VOS_VOID )
{
    VOS_UINT32                          ulCurEmmStat;

    /* 编码DETACH REQ消息中的DETACH类型是有统一原则的，需要考虑的因素有用户请求的
       DETACH类型，UE模式和注册域，拔卡时不存在用户请求的DETACH类型，如果还想使用
       统一的编码原则，则需要在编码前先赋一个合适的值作为用户请求的DETACH类型；
       目前的填写原则:如果是ATTACH过程中，则根据ATTACH类型填写用户请求的DETACH
       类型；如果不是ATTACH过程中，则填为EPS/IMSI */

    /* 如果以后拔卡发起DETACH流程的场景增加，则需要考虑增加的场景该如何填写用户
       请求的DETACH类型*/

    ulCurEmmStat = NAS_LMM_PUB_COMP_EMMSTATE(NAS_EMM_CUR_MAIN_STAT,
                                            NAS_EMM_CUR_SUB_STAT);


    if ((ulCurEmmStat != NAS_LMM_PUB_COMP_EMMSTATE(    EMM_MS_REG_INIT,
                                                        EMM_SS_ATTACH_WAIT_CN_ATTACH_CNF))
        && (ulCurEmmStat != NAS_LMM_PUB_COMP_EMMSTATE(  EMM_MS_REG_INIT,
                                                        EMM_SS_ATTACH_WAIT_ESM_BEARER_CNF))
        && (ulCurEmmStat != NAS_LMM_PUB_COMP_EMMSTATE(  EMM_MS_REG_INIT,
                                                        EMM_SS_ATTACH_WAIT_RRC_DATA_CNF)))
    {
        NAS_EMM_GLO_SetDetTypeMo(MMC_LMM_MO_DET_CS_PS);

        return ;
    }

    /* 如果是ATTACH过程中的拔卡，则根据ATTACH类型填写DETACH类型 */
    if (MMC_LMM_ATT_TYPE_COMBINED_EPS_IMSI == NAS_EMM_GLO_GetCnAttReqType())
    {
        NAS_EMM_GLO_SetDetTypeMo(MMC_LMM_MO_DET_CS_PS);
    }
    else
    {
        NAS_EMM_GLO_SetDetTypeMo(MMC_LMM_MO_DET_PS_ONLY);
    }
}

/*****************************************************************************
 Function Name   : NAS_LMM_PreProcMsgUsimStatusInd
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.yangfan 00159566      2009-9-19  Draft Enact
    2.yangfan 00159566      2010-7-31  Modify 问题单DTS2010072200928
    3.lihong 00150010       2011-7-02  Modify
    4.lihong 00150010       2012-12-17 Modify:Emergency
    5.lifuxin 00253982      2014-10-31 建链流程重构
*****************************************************************************/
VOS_UINT32  NAS_LMM_PreProcMsgUsimStatusInd( MsgBlock  *pMsg )
{
    VOS_UINT32                          ulRslt         = NAS_LMM_MSG_DISCARD;
    VOS_UINT32                          ulCurEmmStat;
    MMC_LMM_USIM_STATUS_REQ_STRU       *pstUsimStatus  = NAS_LMM_NULL_PTR;

    pstUsimStatus                     = (MMC_LMM_USIM_STATUS_REQ_STRU*)pMsg;

    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_PreProcMsgUsimStatusInd is entered");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcMsgUsimStatusInd_ENUM,LNAS_ENTRY);

    /* 如果有状态压栈，先弹出状态 */
    /*NAS_LMM_IfEmmHasBeenPushedThenPop();*/

    ulCurEmmStat = NAS_LMM_PUB_COMP_EMMSTATE(NAS_EMM_CUR_MAIN_STAT,
                                            NAS_EMM_CUR_SUB_STAT);

    NAS_LMM_SetEmmInfoRejCause2Flag(NAS_EMM_REJ_NO);

    /*清除拒绝#18标识*/
    NAS_EMMC_SetRejCause18Flag( NAS_EMM_REJ_NO);

    /*清除拒绝#18列表*/
    /*lint -e960*/
    NAS_LMM_MEM_SET_S(  NAS_EMMC_GetRej18PlmnListAddr(),
                        sizeof(NAS_MM_PLMN_LIST_STRU),
                        0,
                        sizeof(NAS_MM_PLMN_LIST_STRU));
    /*lint +e960*/

    /* 如果卡有效 */
    if (MMC_LMM_USIM_VALID == pstUsimStatus->ulUsimState)
    {
        /* 热插卡操作，赞不支持 */

    }
    else /* 如果卡无效 */
    {
        /*设置USIM卡无效*/
        NAS_LMM_GetSimState() =  NAS_LMM_SIM_STATUS_UNAVAILABLE;

        NAS_LMM_SetPsSimValidity(NAS_LMM_SIM_VALID);
        if((NAS_EMM_CONN_ESTING == NAS_EMM_GetConnState())
           || (NAS_EMM_CONN_RELEASING == NAS_EMM_GetConnState())
           || (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsStaTimerRunning(TI_NAS_EMM_STATE_T3440))
           || (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_REATTACH_DELAY)))
        {
            return  NAS_LMM_STORE_HIGH_PRIO_MSG;
        }

        switch(ulCurEmmStat)
        {
            /* 在开机或者关机过程中，MMC不会下发卡状态报告，不处理 */
            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_NULL, EMM_SS_NULL_WAIT_APP_START_REQ):
            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_NULL, EMM_SS_NULL_WAIT_READING_USIM):
            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_NULL, EMM_SS_NULL_WAIT_MMC_START_CNF):
            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_NULL, EMM_SS_NULL_WAIT_RRC_START_CNF):
            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_NULL, EMM_SS_NULL_WAIT_SWITCH_OFF):
            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_NULL, EMM_SS_NULL_WAIT_MMC_STOP_CNF):
            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_NULL, EMM_SS_NULL_WAIT_RRC_STOP_CNF):

            /* GU->L的重选、重定向或者切换，GU模挂起后，MMC在收到L模的解挂或者GU模的回退解挂前，不会下发卡状态报告；
               L->GU的重选、重定向或者切换，L模挂起后，MMC在收到GU模的解挂或者L模的回退解挂前，不会下发卡状态报告
               因此以下状态不处理 */
            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_SUSPEND,EMM_SS_SUSPEND_WAIT_END):
            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_RESUME,EMM_SS_RESUME_RRCRSM_WAIT_OTHER_RESUME):
            /* MMC会在收到LMM的挂起回复后，才下发卡状态报告，不处理 */
            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_SUSPEND,EMM_SS_SUSPEND_MMCORI_WAIT_OTHER_SUSPEND):
                    ulRslt = NAS_LMM_MSG_HANDLED;
                    break;
            /* 已经将卡设为无卡状态，DETACH正常或者异常流程完成后，会处理拔卡流程 */
            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_DEREG_INIT,EMM_SS_DETACH_WAIT_CN_DETACH_CNF):
                    /* 设置拔卡标识 */
                    NAS_EMM_GLO_AD_GetUsimPullOutFlag() = VOS_TRUE;
                    ulRslt = NAS_LMM_MSG_HANDLED;
                    break;

            /* 直接回复MMC_LMM_USIM_STATUS_CNF */
            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_DEREG, EMM_SS_DEREG_NO_IMSI):
                    NAS_EMM_SendMmcUsimStatusCnf();
                    ulRslt = NAS_LMM_MSG_HANDLED;
                    break;

            /*注册状态下被bar，根据bar类型进行不同处理*/
            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_WAIT_ACCESS_GRANT_IND):
                    ulRslt = NAS_LMM_MsRegSsWaitAccessGrantIndMsgUsimStausInd();
                    break;

            /*注册过程中,根据有无连接进行不同处理*/
            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG_INIT,EMM_SS_ATTACH_WAIT_ESM_PDN_RSP):
                    ulRslt = NAS_LMM_MsRegInitSsAttachWaitEsmPdnRspMsgUsimStausInd();
                    break;

            /* 已经将卡设为无卡状态，发送内部链路释放消息，收到内部链路释放消息后，再处理拔卡流程 */


            /*转DEREG_WAIT_MRRC_REL_CNF，发送内部链路释放消息*/

            /*各状态等待连接释放中，状态转换到DEREG等待连接释放，发送REL_REQ消息*/
            /*case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG_INIT,EMM_SS_ATTACH_WAIT_RRC_REL_IND):*/
            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_AUTH_INIT,EMM_SS_AUTH_WAIT_CN_AUTH):
                    ulRslt = NAS_LMM_MsAnyStateSsWaitRrcRelIndMsgUsimStausInd();
                    break;

            /*注册状态下，需向网侧发送DETACH REQ消息*/
            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG_INIT,EMM_SS_ATTACH_WAIT_CN_ATTACH_CNF):
            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG_INIT,EMM_SS_ATTACH_WAIT_ESM_BEARER_CNF):
            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG_INIT,EMM_SS_ATTACH_WAIT_RRC_DATA_CNF):
            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG,EMM_SS_REG_NORMAL_SERVICE):
            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG,EMM_SS_REG_ATTEMPTING_TO_UPDATE):
            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_TAU_INIT,EMM_SS_TAU_WAIT_CN_TAU_CNF):
            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_SER_INIT,EMM_SS_SER_WAIT_CN_SER_CNF):
                    NAS_LMM_SetUsimInvalidDetachType();
                    /* 设置拔卡标识 */
                    NAS_EMM_GLO_AD_GetUsimPullOutFlag() = VOS_TRUE;
                    NAS_EMM_SendDetachReqMo();
                    ulRslt = NAS_LMM_MSG_HANDLED;
                    break;

            /* 根据有无连接进行不同处理 */
            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_RESUME,EMM_SS_RESUME_RRCORI_WAIT_SYS_INFO_IND):
                    ulRslt = NAS_LMM_MsResumeSsResumeRrcOriWaitSysInfoIndMsgUsimStausInd();
                    break;

            /* 其他状态(包含EMM_MS_RESUME+EMM_SS_RESUME_MMCORI_WAIT_SYS_INFO_IND):
                本地释放资源，转DEREG+NOIMSI，给MMC回复MMC_LMM_USIM_STATUS_CNF;
               MMC先发了卡状态报告，后收到LMM的挂起消息，这种异常就会造成
               EMM_MS_SUSPEND+EMM_SS_SUSPEND_RRCORI_WAIT_OTHER_SUSPEND状态下收到卡状态报告
               */
            default :

                    /*向ESM发送ID_EMM_ESM_STATUS_IND消息*/
                    NAS_EMM_PUB_SendEsmStatusInd(       EMM_ESM_ATTACH_STATUS_DETACHED);
                    /* 通知APP_DETACH_IND(APP_MM_DETACH_ENTITY_ME)*/
                    NAS_EMM_MmcSendDetIndLocal(MMC_LMM_L_LOCAL_DETACH_OTHERS);
                    #if (FEATURE_PTM == FEATURE_ON)
                    NAS_EMM_LocalDetachErrRecord(EMM_ERR_LOG_LOCAL_DETACH_TYPE_OTHER);
                    #endif
                    NAS_EMM_ClearAppMsgPara();
                    NAS_EMM_ProcLocalNoUsim();
                    ulRslt = NAS_LMM_MSG_HANDLED;
                    break;
        }
    }

    return ulRslt;
}


/*****************************************************************************
 Function Name   : NAS_LMM_PreProcUsimSetCnf
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.h41410      2009-6-22  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_LMM_PreProcUsimSetCnf(   MsgBlock  * pMsg)
{
    USIMM_UPDATEFILE_CNF_STRU          *pUsimSetCnf;
    USIMM_DEF_FILEID_ENUM_UINT32        enDefFileID;

    (void)(pMsg);

    pUsimSetCnf = (USIMM_UPDATEFILE_CNF_STRU *)pMsg;

    /* 调用USIM提供的接口，将文件路径转换为FileID */
    if(VOS_OK != USIMM_ChangePathToDefFileID(USIMM_GUTL_APP, pUsimSetCnf->stFilePath.ulPathLen, pUsimSetCnf->stFilePath.acPath, &enDefFileID))
    {
        /* 如果转换失败，表示没有对应的FileID */
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_ProcessHardUsimCnf: USIMM_ChangePathToDefFileID err");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_PreProcUsimSetCnf_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_HANDLED;
    }

    NAS_LMM_PUBM_LOG2_INFO("NAS_LMM_PreProcUsimSetCnf: usEfId = , ulResult = ",
                                        enDefFileID,
                                        pUsimSetCnf->stCmdResult.ulResult);
    TLPS_PRINT2LAYER_INFO2(NAS_LMM_PreProcUsimSetCnf_ENUM,LNAS_FUNCTION_LABEL1,
                                        enDefFileID,
                                        pUsimSetCnf->stCmdResult.ulResult);

    return  NAS_LMM_MSG_HANDLED;
}



VOS_VOID  NAS_LMM_SetImsiUnavail( VOS_VOID )
{
    NAS_LMM_UEID_STRU                    *pstUeId;

    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_SetImsiUnavail IS ENTERED ");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_SetImsiUnavail_ENUM,LNAS_ENTRY);
    pstUeId                             = NAS_LMM_GetEmmInfoUeidAddr();

    /*填充新的IMSI*/
    pstUeId->bitOpImsi                  = NAS_EMM_BIT_NO_SLCT;

    /*lint -e960*/
    NAS_LMM_MEM_SET_S(  NAS_LMM_GetEmmInfoUeidImsiAddr(),
                        NAS_MM_MAX_UEID_BUF_SIZE,
                        0,
                        NAS_MM_MAX_UEID_BUF_SIZE);
    /*lint +e960*/

    return;
}


/*****************************************************************************
 Function Name   : NAS_PUB_GetSleepInfo
 Description     : 根据NAS状态判断允不允许睡眠
 Input           : None
 Output          : None
 Return          : VOS_UINT32
                   0 不允许
                   1 允许
 History         :
    1.sunbing49683      2009-8-17  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_PUB_GetSleepInfo( VOS_VOID)
{

    return 0;
}



VOS_VOID NAS_LMM_ReadUsimEmmInfoFile( VOS_VOID )
{
    VOS_UINT32                          ulRslt;
    VOS_UINT32                          ulUsimSerEpsSecu;

    /*读取NV中的IMSI*/
    ulRslt = NAS_LMM_MatchNvImsi();
    if (NAS_EMM_SUCC != ulRslt)
    {   /* IMSI 不相同 */
        NAS_LMM_PUBM_LOG_INFO("NAS_LMM_ReadUsimEmmInfoFile: IMSI DIFF !!");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_ReadUsimEmmInfoFile_ENUM,LNAS_FAIL);

        /*删除NV中的EPS SECURITY CONTEXT*/
        NAS_LMM_WriteNvEpsSecurityContext(NAS_NV_ITEM_DELETE);

        /*删除NV中的PS LOC*/
        NAS_LMM_WriteNvPsLoc(NAS_NV_ITEM_DELETE);


        NAS_LMM_UpdateNvImsi(NAS_LMM_GetEmmInfoUeidImsiAddr());
    }
    /* 判断SerTable是否支持安全上下文 */
    /* ulRslt = NAS_LMM_GetUsimOptionFileStatus(NAS_LMM_SER_TABLE_EMMINFO_BIT);*/
    ulUsimSerEpsSecu = NAS_EMM_IsServiceAvailable(USIM_SVR_EPS_INFO);
    if(PS_USIM_SERVICE_AVAILIABLE == ulUsimSerEpsSecu)

    {/* 硬USIM条件下，并且支持安全上下文 */

        /* 硬USIM支持安全上下文 */
        NAS_LMM_PUBM_LOG_INFO("NAS_LMM_ReadUsimEmmInfoFile:Read Hard USIM secu Para");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_ReadUsimEmmInfoFile_ENUM,LNAS_FUNCTION_LABEL1);

        /*读取硬USIM中的EPS SECURITY CONTEXT*/
        NAS_LMM_ReadSimEpsSecContext();

        /*读取硬USIM中的PS LOC*/
        NAS_LMM_ReadSimPsLoc();
    }
    else
    {
        /* USIM不支持安全上下文，则读取NV中的安全上下文 */
        NAS_LMM_PUBM_LOG1_INFO(
            "NAS_LMM_ReadUsimEmmInfoFile: Usim not support EPS LOC: ulUsimSerEpsSecu,",
            ulUsimSerEpsSecu);
        TLPS_PRINT2LAYER_INFO1(NAS_LMM_ReadUsimEmmInfoFile_ENUM,LNAS_FUNCTION_LABEL2,
            ulUsimSerEpsSecu);

        /*读取NV中的EPS SECURITY CONTEXT*/
        NAS_LMM_ReadNvEpsSecContext();

        /*读取NV中的PS LOC*/
        NAS_LMM_ReadNvPsLoc();
    }

    return;
}


VOS_UINT32  NAS_LMM_MsNullSsWaitUsimReadyMsgUsimStatusInd(VOS_VOID)
{
    NAS_LMM_FSM_STATE_STRU               stEmmState;

    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_MsNullSsWaitUsimReadyMsgUsimStatusInd is entered");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_MsNullSsWaitUsimReadyMsgUsimStatusInd_ENUM,LNAS_ENTRY);

    /*停止定时器*/
    NAS_LMM_StopStateTimer(TI_NAS_LMM_TIMER_WAIT_USIM_READY_START);

    /*转状态EMM_MS_NULL，EMM_SS_NULL_WAIT_APP_START_REQ*/
    stEmmState.enFsmId                    = NAS_LMM_PARALLEL_FSM_EMM;
    stEmmState.enMainState                = EMM_MS_NULL;
    stEmmState.enSubState                 = EMM_SS_NULL_WAIT_APP_START_REQ;
    stEmmState.enStaTId                   = TI_NAS_EMM_STATE_NO_TIMER;
    NAS_LMM_StaTransProc(stEmmState);

    /* 有卡时,检查是否需要自动开机*/
    /* V7R1不再自动开机， */
    /*NAS_EMM_CheckAutoStartFeature();*/

    return NAS_LMM_MSG_HANDLED;

}

/*****************************************************************************
 Function Name   : NAS_LMM_PUBM_ClearResource
 Description     : DETACH后，
                    释放动态内存；
                    停止定时器；
                    全局变量赋初始值；
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1. h41410 DRAFT 2010 10 15

*****************************************************************************/
VOS_VOID    NAS_LMM_PUBM_ClearResource(VOS_VOID)
{
    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_PUBM_ClearResource: enter.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_PUBM_ClearResource_ENUM,LNAS_ENTRY);

    /*释放stNasMmFsm 中的状态压栈*/
    NAS_LMM_FSM_ClearStackResource();

    /*释放stNasMmFsm 中3个状态机的消息缓存*/
    NAS_LMM_BufMsgQueFree();

    /*释放内部消息队列不能清理，
    因为DETACH完成后，有时会通知MMC ACTION_RESULT，清理将
    导致MMC收不到消息，
    例如NAS_EMM_MsDrgInitSsWtCnDetCnfMsgIntraConnectFailInd*/
    /*NAS_LMM_IntraMsgQueueInit();*/

    return;
}

/*****************************************************************************
 Function Name   : NAS_LMM_DeregReleaseResource
 Description     : LOCAL DETACH后，
                    停止EMM定时器；
                    各模块全局变量赋初始值；
                    该函数不影响MMC的参数；
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1. h41410 DRAFT 2010 10 15

*****************************************************************************/
VOS_VOID    NAS_LMM_DeregReleaseResource(VOS_VOID)
{

    NAS_LMM_PUBM_LOG_NORM("NAS_LMM_DeregReleaseResource: enter.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_DeregReleaseResource_ENUM,LNAS_ENTRY);

    /* 关闭当前EMM的除Del Forb Ta Proid之外的状态定时器, Del Forb Ta Proid只能在关机时停止*/
    NAS_LMM_StopAllStateTimerExceptDelForbTaProidTimer();

    /* 停止所有EMM协议定时器*/
    NAS_LMM_StopAllEmmPtlTimer();

    /*PUBM清理*/
    NAS_LMM_PUBM_ClearResource();

    /*EMM各子模块清理*/
    NAS_EMM_PUBU_ClearResource();
    NAS_EMM_SECU_ClearResource();

    NAS_EMM_Attach_ClearResourse();
    NAS_EMM_Detach_ClearResourse();

    NAS_EMM_TAU_ClearResouce();
    NAS_EMM_SER_ClearResource();

    /*GUTI/IDEN/MRRC/PLMN模块均无需要释放的内容,若将来需要，
    补充子模块的函数，并在这里调用*/

    return;
}
/*****************************************************************************
 Function Name   : NAS_LMM_ImsiDetachReleaseResource
 Description     : IMSI DETACH之后清理资源
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1. lihong00150010   2011-09-28  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LMM_ImsiDetachReleaseResource( VOS_VOID )
{

    NAS_LMM_PUBM_LOG_NORM("NAS_LMM_ImsiDetachReleaseResource: enter.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_ImsiDetachReleaseResource_ENUM,LNAS_ENTRY);

    NAS_EMM_Detach_ClearResourse();

    return;
}
/*****************************************************************************
 Function Name   : NAS_LMM_MsRegSsWaitAccessGrantIndMsgUsimStausInd
 Description     : 在状态REG+ACCESS_GRANT_IND下收到USIM STATUS IND消息(卡无效)
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.    leili  00132387      2010-11-12  Draft Enact
    2.    lihong 00150010      2012-12-17  Modify:Emergency

*****************************************************************************/
VOS_UINT32  NAS_LMM_MsRegSsWaitAccessGrantIndMsgUsimStausInd(VOS_VOID)
{
    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_MsRegSsWaitAccessGrantIndMsgUsimStausInd is enter.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_MsRegSsWaitAccessGrantIndMsgUsimStausInd_ENUM,LNAS_ENTRY);

    if(NAS_EMM_SUCC != NAS_EMM_JudgeBarType(NAS_EMM_BAR_TYPE_MO_SIGNAL))
    {
        NAS_LMM_PUBM_LOG_NORM("NAS_LMM_MsRegSsWaitAccessGrantIndMsgUsimStausInd: MO-SIGNALLING is not bar");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_MsRegSsWaitAccessGrantIndMsgUsimStausInd_ENUM,LNAS_ENTRY);

        NAS_LMM_SetUsimInvalidDetachType();

        /* 设置拔卡标识 */
        NAS_EMM_GLO_AD_GetUsimPullOutFlag() = VOS_TRUE;

        NAS_EMM_SendDetachReqMo();

        return  NAS_LMM_MSG_HANDLED;
    }

    /*向ESM发送ID_EMM_ESM_STATUS_IND消息*/
    NAS_EMM_PUB_SendEsmStatusInd(       EMM_ESM_ATTACH_STATUS_DETACHED);

    /* 通知APP_DETACH_IND(APP_MM_DETACH_ENTITY_ME)*/
    NAS_EMM_MmcSendDetIndLocal(MMC_LMM_L_LOCAL_DETACH_OTHERS);

    #if (FEATURE_PTM == FEATURE_ON)
    NAS_EMM_LocalDetachErrRecord(EMM_ERR_LOG_LOCAL_DETACH_TYPE_OTHER);
    #endif
    NAS_EMM_ClearAppMsgPara();

    NAS_EMM_ProcLocalNoUsim();

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_LMM_MsRegInitSsAttachWaitEsmPdnRspMsgUsimStausInd
 Description     : 在状态REG_INIT+ATTACH_WAIT_ESM_PDN_RSP下收到USIM STATUS IND消息(卡无效)
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.    leili  00132387      2010-11-12  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LMM_MsRegInitSsAttachWaitEsmPdnRspMsgUsimStausInd( VOS_VOID )
{
    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_MsRegInitSsAttachWaitEsmPdnRspMsgUsimStausInd is enter.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_MsRegInitSsAttachWaitEsmPdnRspMsgUsimStausInd_ENUM,LNAS_ENTRY);

    /*向ESM发送ID_EMM_ESM_STATUS_IND消息*/
    NAS_EMM_PUB_SendEsmStatusInd(       EMM_ESM_ATTACH_STATUS_DETACHED);

    /* 通知APP_DETACH_IND(APP_MM_DETACH_ENTITY_ME)*/
    NAS_EMM_MmcSendDetIndLocal(MMC_LMM_L_LOCAL_DETACH_OTHERS);

    #if (FEATURE_PTM == FEATURE_ON)
    NAS_EMM_LocalDetachErrRecord(EMM_ERR_LOG_LOCAL_DETACH_TYPE_OTHER);
    #endif
    NAS_EMM_ClearAppMsgPara();

    NAS_EMM_ProcLocalNoUsim();

    if (NAS_EMM_CONN_IDLE != NAS_EMM_GetConnState())
    {

        /* 下发RelReq */
        NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);
    }

    return NAS_LMM_MSG_HANDLED;

}
/*****************************************************************************
 Function Name   : NAS_LMM_MsResumeSsResumeRrcOriWaitSysInfoIndMsgUsimStausInd
 Description     : 在状态RESUME+RESUME_WAIT_SYS_INFO_IND下收到USIM STATUS IND消息(卡无效)
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2011-7-2  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LMM_MsResumeSsResumeRrcOriWaitSysInfoIndMsgUsimStausInd( VOS_VOID )
{
    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_MsResumeSsResumeRrcOriWaitSysInfoIndMsgUsimStausInd is enter.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_MsResumeSsResumeRrcOriWaitSysInfoIndMsgUsimStausInd_ENUM,LNAS_ENTRY);

    /*向ESM发送ID_EMM_ESM_STATUS_IND消息*/
    NAS_EMM_PUB_SendEsmStatusInd(       EMM_ESM_ATTACH_STATUS_DETACHED);

    /* 通知APP_DETACH_IND(APP_MM_DETACH_ENTITY_ME)*/
    NAS_EMM_MmcSendDetIndLocal(MMC_LMM_L_LOCAL_DETACH_OTHERS);

    #if (FEATURE_PTM == FEATURE_ON)
    NAS_EMM_LocalDetachErrRecord(EMM_ERR_LOG_LOCAL_DETACH_TYPE_OTHER);
    #endif
    NAS_EMM_ClearAppMsgPara();

    NAS_EMM_ProcLocalNoUsim();

    if (NAS_EMM_CONN_IDLE != NAS_EMM_GetConnState())
    {
        /* 下发RelReq */
        NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);
    }

    return NAS_LMM_MSG_HANDLED;

}


VOS_VOID  NAS_EMM_ProcLocalNoUsim( VOS_VOID )
{
    NAS_LMM_FSM_STATE_STRU               stEmmState;

    NAS_LMM_PUBM_LOG_NORM("NAS_EMM_ProcLocalNoUsim is enter.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcLocalNoUsim_ENUM,LNAS_ENTRY);


    /*修改状态：进入主状态DEREG子状态DEREG_NORMAL_SERVICE*/
    stEmmState.enFsmId                    = NAS_LMM_PARALLEL_FSM_EMM;
    stEmmState.enMainState                = EMM_MS_DEREG;
    stEmmState.enSubState                 = EMM_SS_DEREG_NO_IMSI;
    stEmmState.enStaTId                   = TI_NAS_EMM_STATE_NO_TIMER;
    NAS_LMM_StaTransProc(stEmmState);

    /* 本地DETACH释放资源:动态内存、赋初值 */
    NAS_LMM_DeregReleaseResource();

    /* 清除拔卡标识 */
    NAS_EMM_GLO_AD_GetUsimPullOutFlag() = VOS_FALSE;

    /* 给MMC回复LMM_MMC_USIM_STATUS_CNF */
    NAS_EMM_SendMmcUsimStatusCnf();

    return;
}



VOS_UINT32  NAS_LMM_MsAnyStateSsWaitRrcRelIndMsgUsimStausInd(  )
{
    NAS_LMM_PUBM_LOG_NORM("NAS_LMM_MsAnyStateSsWaitRrcRelIndMsgUsimStausInd is enter.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_MsAnyStateSsWaitRrcRelIndMsgUsimStausInd_ENUM,LNAS_ENTRY);

    /*向ESM发送ID_EMM_ESM_STATUS_IND消息*/
    NAS_EMM_PUB_SendEsmStatusInd(       EMM_ESM_ATTACH_STATUS_DETACHED);

    /* 通知APP_DETACH_IND(APP_MM_DETACH_ENTITY_ME)*/
    NAS_EMM_MmcSendDetIndLocal(MMC_LMM_L_LOCAL_DETACH_OTHERS);

    #if (FEATURE_PTM == FEATURE_ON)
    NAS_EMM_LocalDetachErrRecord(EMM_ERR_LOG_LOCAL_DETACH_TYPE_OTHER);
    #endif
    NAS_EMM_ClearAppMsgPara();

    NAS_EMM_ProcLocalNoUsim();

    /* 下发RelReq */
    NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);

    return NAS_LMM_MSG_HANDLED;

}


VOS_VOID  NAS_LMM_SaveCurRatToPreRat(VOS_VOID )
{
   NAS_LMM_GetPreGsmPrio()      = NAS_LMM_GetCurGsmPrio();
   NAS_LMM_GetPreWcdmaPrio()    = NAS_LMM_GetCurWcdmaPrio();
   NAS_LMM_GetPreLtePrio()      = NAS_LMM_GetCurLtePrio();
   /*NAS_LMM_GetPreButtPrio()     = NAS_LMM_GetCurButtPrio();*/
}
/*****************************************************************************
 Function Name   : NAS_LMM_PreProcInfoChangeNotifyReq
 Description     : 处理GMM发来的GMM_LMM_INFO_CHANGE_NOTIFY_REQ消息
 Input           : pstMsg------------------------消息指针
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2011-08-27  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_LMM_PreProcInfoChangeNotifyReq
(
    MsgBlock                           *pstMsg
)
{
    GMM_LMM_INFO_CHANGE_NOTIFY_REQ_STRU *pstGmmInfoChange = NAS_EMM_NULL_PTR;

    NAS_LMM_PUBM_LOG_NORM("NAS_LMM_PreProcInfoChangeNotifyReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcInfoChangeNotifyReq_ENUM,LNAS_ENTRY);

    pstGmmInfoChange = (GMM_LMM_INFO_CHANGE_NOTIFY_REQ_STRU*)(VOS_VOID *)pstMsg;

    /* 入参检查 */
    if ( NAS_EMM_NULL_PTR == pstMsg)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_PreProcInfoChangeNotifyReq:input ptr null!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_PreProcInfoChangeNotifyReq_ENUM,LNAS_NULL_PTR);
        return  NAS_LMM_MSG_HANDLED;
    }

    /* 存储G模连接状态 */
    if (NAS_EMM_BIT_SLCT == pstGmmInfoChange->bitOpGprsMmState)
    {
        NAS_LMM_SetEmmInfoGConnState(pstGmmInfoChange->enGprsMmState);
    }

    /* 存储U模连接状态 */
    if (NAS_EMM_BIT_SLCT == pstGmmInfoChange->bitOpPacketMmState)
    {
        NAS_LMM_SetEmmInfoUConnState(pstGmmInfoChange->enPacketMmState);
    }

    /* 存储PS域状态 */
    if (NAS_EMM_BIT_SLCT == pstGmmInfoChange->bitOpGprsSuspensionState)
    {
        NAS_LMM_SetEmmInfoPsState(pstGmmInfoChange->enGprsSuspensionState);
    }

    return NAS_LMM_MSG_HANDLED;
}
/*lint +e826*/
/*****************************************************************************
 Function Name   : NAS_LMM_SendRrcSysCfgReq
 Description     : 向RRC发送RRC_MM_SYS_CFG_REQ消息
 Input           : None
 Output          : None
 Return          : NAS_LMM_SUCC  -- 发送成功
                     -- 发送失败

 History         :
    1.ZHANGCAIXIA 0079470      2011-9-10  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LMM_SendRrcSysCfgReq( MsgBlock  *pMsg )
{
    LRRC_LNAS_SYS_CFG_REQ_STRU         *pstRrcSysCfgReqMsg = VOS_NULL_PTR;
    MMC_LMM_SYS_CFG_REQ_STRU           *pstMmcSysCfgReqMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulSendResult;
    VOS_UINT32                          ulMsgLen;

    pstMmcSysCfgReqMsg              = (VOS_VOID*)pMsg;

    /*计算长度不包含VOS消息头*/
    ulMsgLen     = sizeof(LRRC_LNAS_SYS_CFG_REQ_STRU);

    /*分配内存*/
    pstRrcSysCfgReqMsg = (VOS_VOID *)NAS_LMM_ALLOC_MSG(ulMsgLen);
    if(NAS_EMM_NULL_PTR == pstRrcSysCfgReqMsg)
    {
        ulSendResult = NAS_EMM_SEND_MMC_ERR;
        return ulSendResult;
    }

    /*清空申请到的消息空间*/
    NAS_LMM_MEM_SET_S(  pstRrcSysCfgReqMsg,
                        sizeof(LRRC_LNAS_SYS_CFG_REQ_STRU),
                        0,
                        sizeof(LRRC_LNAS_SYS_CFG_REQ_STRU));

    /*填充VOS消息头*/
    /*lint -e960*/
    NAS_EMM_SET_RRC_MSG_HEADER(pstRrcSysCfgReqMsg, ulMsgLen-VOS_MSG_HEAD_LENGTH);

    /* 填充消息ID */
    pstRrcSysCfgReqMsg->ulMsgId         = ID_LRRC_LMM_SYS_CFG_REQ;

    /* 填充消息体 */
    /* opId,暂时填为固定值*/
    pstRrcSysCfgReqMsg->ulOpId          = 0x01;

    /* BAND */
    if (NAS_EMM_BIT_SLCT == pstMmcSysCfgReqMsg->bitOpBand)
    {
        pstRrcSysCfgReqMsg->bitOpBand = NAS_EMM_BIT_SLCT;
        NAS_LMM_MEM_CPY_S(  &(pstRrcSysCfgReqMsg->stBand),
                            sizeof(NAS_RRC_USER_SET_FREQ_BAND_STRU),
                            &(pstMmcSysCfgReqMsg->stBand),
                            sizeof(NAS_RRC_USER_SET_FREQ_BAND_STRU));

    }
    /*RAT*/
    if (NAS_EMM_BIT_SLCT == pstMmcSysCfgReqMsg->bitOpRat)
    {
        pstRrcSysCfgReqMsg->bitOpRat = NAS_EMM_BIT_SLCT;
        NAS_LMM_MEM_CPY_S(  pstRrcSysCfgReqMsg->aucRatPrioList,
                            sizeof(LRRC_LNAS_RAT_PRIO_ENUM_UINT8) * LRRC_LNAS_RAT_TYPE_BUTT,
                            pstMmcSysCfgReqMsg->aucRatPrioList,
                            sizeof(RRMM_RAT_PRIO_ENUM_UINT8)*RRMM_RAT_TYPE_BUTT);
    }

    /* 填写UTRAN MODE */
    if (MMC_LMM_UTRAN_MODE_FDD == pstMmcSysCfgReqMsg->enUtranMode)
    {
        pstRrcSysCfgReqMsg->enUtranMode = LRRC_LNAS_UTRAN_MODE_WCDMA;
    }
    else if (MMC_LMM_UTRAN_MODE_TDD == pstMmcSysCfgReqMsg->enUtranMode)
    {
        pstRrcSysCfgReqMsg->enUtranMode = LRRC_LNAS_UTRAN_MODE_TDSCDMA;
    }
    else
    {
        pstRrcSysCfgReqMsg->enUtranMode = pstMmcSysCfgReqMsg->enUtranMode;
    }

    /* 发送ID_LRRC_LMM_SYS_CFG_REQ */
    NAS_LMM_SEND_MSG(pstRrcSysCfgReqMsg);
    /*lint +e960*/

    ulSendResult                        = NAS_EMM_SEND_RRC_OK;

    return ulSendResult;
}


/*****************************************************************************
 Function Name   : NAS_LMM_PreProcMmcSysCfgReq
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhangcaxia 00179470      2011-9-9  Draft Enact
    2.wangchen    00209181 2012-05-28 MODIFY:SysCfg与RRC的挂起请求对冲
*****************************************************************************/
VOS_UINT32  NAS_LMM_PreProcMmcSysCfgReq( MsgBlock  *pMsg )
{

    VOS_UINT32                          ulSendResult;

    MMC_LMM_RESULT_ID_ENUM_UINT32       ulRslt = MMC_LMM_SUCC;

    MMC_LMM_SYS_CFG_REQ_STRU           *pMmcLmmSysCfgReq = VOS_NULL_PTR;

    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_PreProcMmcSysCfgReq Enter.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcMmcSysCfgReq_ENUM,LNAS_ENTRY);


    pMmcLmmSysCfgReq = (MMC_LMM_SYS_CFG_REQ_STRU *)(VOS_VOID *)pMsg;
    /* 处于开关机过程中收到SYSCFGEX丢弃 */
    if(EMM_MS_NULL == NAS_EMM_CUR_MAIN_STAT)
    {
        NAS_LMM_PUBM_LOG_INFO("NAS_LMM_SendRrcSysCfgReq : POWER_ON OR POWER_OFF ING,DISCARD!");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcMmcSysCfgReq_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_LMM_MSG_HANDLED;
    }

    if (  (NAS_LMM_RAT_PRIO_BUTT <= pMmcLmmSysCfgReq->aucRatPrioList[NAS_LMM_RAT_TYPE_GSM])
        ||(NAS_LMM_RAT_PRIO_BUTT <= pMmcLmmSysCfgReq->aucRatPrioList[NAS_LMM_RAT_TYPE_WCDMA])
        ||(NAS_LMM_RAT_PRIO_BUTT <= pMmcLmmSysCfgReq->aucRatPrioList[NAS_LMM_RAT_TYPE_LTE]) )
    {
        NAS_LMM_EMM_PLMN_LOG_ERR("NAS_LMM_PreProcMmcSysCfgReq: MMC SYSCFG RAT LIST IS VALID ");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_PreProcMmcSysCfgReq_ENUM,LNAS_FUNCTION_LABEL2);

        /* 向MMC回复SYS CFG结果*/
        ulSendResult = NAS_LMM_SendMmcSysCfgCnf(ulRslt);

        if (NAS_EMM_SEND_RRC_OK != ulSendResult)
        {
            /* 打印函数，ERROR_LEVEL */
            NAS_LMM_PUBM_LOG1_INFO("NAS_LMM_SendMmcSysCfgCnf : Send Msg Failure!!! ulSendResult=",
                                     ulSendResult);
            TLPS_PRINT2LAYER_INFO1(NAS_LMM_PreProcMmcSysCfgReq_ENUM,LNAS_FUNCTION_LABEL3,
                                     ulSendResult);
        }
        return NAS_LMM_MSG_HANDLED;
    }

    /*保存系统配置的接入技术，使之生效*/
    NAS_LMM_SaveCurRatToPreRat();

    /* 保存到本地 */
    NAS_LMM_GetCurGsmPrio()         = pMmcLmmSysCfgReq->aucRatPrioList[NAS_LMM_RAT_TYPE_GSM];
    NAS_LMM_GetCurWcdmaPrio()       = pMmcLmmSysCfgReq->aucRatPrioList[NAS_LMM_RAT_TYPE_WCDMA];
    NAS_LMM_GetCurLtePrio()         = pMmcLmmSysCfgReq->aucRatPrioList[NAS_LMM_RAT_TYPE_LTE];

    #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    NAS_LMM_GetCurCdma1xPrio()      = pMmcLmmSysCfgReq->aucRatPrioList[NAS_LMM_RAT_TYPE_CDMA1X];
    NAS_LMM_GetCurHrpdPrio()        = pMmcLmmSysCfgReq->aucRatPrioList[NAS_LMM_RAT_TYPE_HRPD];
    #endif

    /* 向RRC发系统配置请求消息*/
    ulSendResult = NAS_LMM_SendRrcSysCfgReq(pMsg);

    if (NAS_EMM_SEND_RRC_OK != ulSendResult)
    {
        /* 打印函数，ERROR_LEVEL */
        NAS_LMM_PUBM_LOG1_INFO("NAS_LMM_SendRrcSysCfgReq : Send Msg Failure!!! ulSendResult=",
                                 ulSendResult);
        TLPS_PRINT2LAYER_INFO1(NAS_LMM_PreProcMmcSysCfgReq_ENUM,LNAS_FUNCTION_LABEL4,
                                     ulSendResult);

        return NAS_LMM_MSG_HANDLED;

    }
    NAS_LMM_SetEmmInfoSyscfgCtrl(NAS_LMM_SYSCFG_FLAG_VALID);
    NAS_LMM_StartStateTimer(TI_NAS_EMM_STATE_WAIT_SYSCFG_CNF_TIMER);

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_LMM_SendMmcSysCfgCnf
 Description     : 向RRC发送RRC_MM_SYS_CFG_CNF消息
 Input           : None
 Output          : None
 Return          : NAS_LMM_SUCC  -- 发送成功
                     -- 发送失败

 History         :
    1.ZHANGCAIXIA 0079470      2011-9-10  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LMM_SendMmcSysCfgCnf( MMC_LMM_RESULT_ID_ENUM_UINT32 ulRst )
{
    LMM_MMC_SYS_CFG_CNF_STRU           *pstMmcSysCfgCnfMsg    = NAS_EMM_NULL_PTR;
    VOS_UINT32                          ulSendResult;

    NAS_LMM_PUBM_LOG_INFO( "NAS_LMM_SendMmcSysCfgCnf: enter");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_SendMmcSysCfgCnf_ENUM,LNAS_ENTRY);

    /* 申请MMC内部消息 */
    pstMmcSysCfgCnfMsg = (VOS_VOID *)NAS_LMM_GetLmmMmcMsgBuf(sizeof(LMM_MMC_SYS_CFG_CNF_STRU));

    if(NAS_EMM_NULL_PTR == pstMmcSysCfgCnfMsg)
    {
        NAS_LMM_PUBM_LOG_ERR( "NAS_LMM_SendMmcSysCfgCnf: MSG ALLOC ERR !!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_SendMmcSysCfgCnf_ENUM,LNAS_ERROR);
        ulSendResult = NAS_EMM_SEND_MMC_ERR;
        return ulSendResult;
    }

    /*lint -e960*/
    NAS_LMM_MEM_SET_S(  pstMmcSysCfgCnfMsg,
                        sizeof(LMM_MMC_SYS_CFG_CNF_STRU),
                        0,
                        sizeof(LMM_MMC_SYS_CFG_CNF_STRU));

    /* 填写LMM_MMC_SYS_CFG_CNF_STRU 的DOPRA消息头 */
    EMM_PUBU_COMP_MMC_MSG_HEADER(pstMmcSysCfgCnfMsg,
            sizeof(LMM_MMC_SYS_CFG_CNF_STRU) - EMM_LEN_VOS_MSG_HEADER);
    /*lint +e960*/

    /* 填写LMM_MMC_SYS_CFG_CNF 的消息ID标识 */
    pstMmcSysCfgCnfMsg->ulMsgId           = ID_LMM_MMC_SYS_CFG_CNF;

    /* 填写结果*/
    pstMmcSysCfgCnfMsg->ulRst             = ulRst;

    /* 发送消息 */
    NAS_LMM_SendLmmMmcMsg(                    pstMmcSysCfgCnfMsg);

    ulSendResult                          = NAS_EMM_SEND_RRC_OK;
    return ulSendResult;
}

/*****************************************************************************
 Function Name   : NAS_LMM_PreProcRrcSysCfgCnf
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhangcaxia 00179470      2011-9-9  Draft Enact
    2.sunjitan 00193151        2012-01-31 Modify for UE capability
    3.wangchen 00209181        2012-05-28   SysCfg和挂起消息对冲
*****************************************************************************/
VOS_UINT32  NAS_LMM_PreProcRrcSysCfgCnf( MsgBlock  *pMsg )
{

    LRRC_LNAS_SYS_CFG_CNF_STRU         *pstRrcLmmSysCfgCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt = NAS_LMM_MSG_DISCARD;
    NAS_UE_CAP_CHG_UPDATE_TYPE_ENUM_UINT32      enResult = NAS_UE_CAP_CHG_BUTT;

    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_PreProcRrcSysCfgCnf Enter.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcRrcSysCfgCnf_ENUM,LNAS_ENTRY);

    pstRrcLmmSysCfgCnf                        = (VOS_VOID*)pMsg;

    (void)pMsg;
    if (NAS_EMM_NULL_PTR == pMsg)
    {
        NAS_LMM_PUBM_LOG_INFO("NAS_LMM_PreProcRrcSysCfgCnf: Input para is null");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcRrcSysCfgCnf_ENUM,LNAS_NULL_PTR);

        return NAS_LMM_MSG_HANDLED;
    }
    NAS_LMM_SetEmmInfoSyscfgCtrl(NAS_LMM_SYSCFG_FLAG_INVALID);
    NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_WAIT_SYSCFG_CNF_TIMER);

    enResult = NAS_EMM_RecordUeRadioAccCapChg(pstRrcLmmSysCfgCnf->ucRadioAccCapChgInd);
    /* 保存RRC的SUSPEND结果 */
    NAS_EMM_GetRrcSysCfgSusType()   = pstRrcLmmSysCfgCnf->enSusNotify;

    /* 根据不同结果进行不同的处理，三种情况 */
    switch(NAS_EMM_GetRrcSysCfgSusType())
    {
        case    LRRC_LNAS_SUSPEND_LTE_BAND_NOT_SUPPORT:

                NAS_LMM_ProcRrcSysCfgCnfBandNotSupport();

                ulRslt = NAS_LMM_MSG_HANDLED;
                break;

        case    LRRC_LNAS_SUSPEND_LTE_RAT_NOT_ACTIVE:

                NAS_LMM_ProcRrcSysCfgCnfLteNotActive();

                ulRslt = NAS_LMM_MSG_HANDLED;
                break;

        case    LRRC_LNAS_NOT_SUSPEND:
                if(NAS_UE_CAP_CHG_NO_UPDATE == enResult)
                {
                    /* 直接给MMC回复结果 */
                    (VOS_VOID)NAS_LMM_SendMmcSysCfgCnf(MMC_LMM_SUCC);
                }
                else
                {
                    ulRslt = NAS_LMM_ProcRrcSysCfgCnfNotSuspend();
                }
                break;

        default:

                /* 丢弃消息*/
                NAS_LMM_PUBM_LOG1_INFO("ERROR  enSusNotify, value = ", pstRrcLmmSysCfgCnf->enSusNotify);
                TLPS_PRINT2LAYER_INFO1(NAS_LMM_PreProcRrcSysCfgCnf_ENUM,LNAS_FUNCTION_LABEL1,
                                        pstRrcLmmSysCfgCnf->enSusNotify);
                break;
    }

    return ulRslt;
}

/*****************************************************************************
 Function Name   : NAS_LMM_PreProcMmcOocStateReq
 Description     : 收到MMC 丢网指示的命令的处理

 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :dongning 00130305  2012-4-16  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LMM_PreProcMmcOocStateReq( MsgBlock  *pMsg )
{
    (void)pMsg;
    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_PreProcMmcOocStateReq Enter.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcMmcOocStateReq_ENUM,LNAS_ENTRY);

    /*判决LTE是否主模，是则启动从模切换处理，否不需要任何处理 */
    if(NAS_LMM_CUR_LTE_ACTIVE == NAS_EMM_GetCurLteState())
    {
        /*向RRC发送丢网挂起操作*/
        NAS_EMM_SendLrrcOssStateReq();

        /*内部状态转到丢网状态 */
        switch(NAS_LMM_GetEmmCurFsmMS())
        {
            case EMM_MS_REG:
            NAS_EMM_AdStateConvert( EMM_MS_REG,
                                    EMM_SS_REG_NO_CELL_AVAILABLE,
                                    TI_NAS_EMM_STATE_NO_TIMER);
            break;

            case EMM_MS_DEREG:
            if (EMM_SS_DEREG_NO_IMSI != NAS_LMM_GetEmmCurFsmSS())
            {
                NAS_EMM_AdStateConvert( EMM_MS_DEREG,
                                        EMM_SS_DEREG_NO_CELL_AVAILABLE,
                                        TI_NAS_EMM_STATE_NO_TIMER);
            }
            break;

            default:
            break;
        }
    }

    return NAS_LMM_MSG_HANDLED;
}

VOS_VOID  NAS_EMM_SendLrrcOssStateReq( VOS_VOID )
{
    LRRC_LMM_OOS_STATE_REQ_STRU           *pstLrrcOssStateReqMsg;

    /* 申请DOPRA消息 */
    pstLrrcOssStateReqMsg = (VOS_VOID *) NAS_LMM_ALLOC_MSG(sizeof(LRRC_LMM_OOS_STATE_REQ_STRU));
    if (NAS_LMM_NULL_PTR == pstLrrcOssStateReqMsg)
    {
        return ;
    }

    /*lint -e960*/

    /* 清空 */
    NAS_LMM_MEM_SET_S(  pstLrrcOssStateReqMsg,
                        sizeof(LRRC_LMM_SUSPEND_REQ_STRU),
                        0,
                        sizeof(LRRC_LMM_SUSPEND_REQ_STRU));

    /* 打包VOS消息头 */
    NAS_EMM_SET_RRC_MSG_HEADER((pstLrrcOssStateReqMsg),
            NAS_EMM_GET_MSG_LENGTH_NO_HEADER(LRRC_LMM_OOS_STATE_REQ_STRU));

    /* 填充消息ID */
    pstLrrcOssStateReqMsg->enMsgId       = ID_LRRC_LMM_OOS_STATE_REQ;

    /* 发送DOPRA消息 */
    NAS_LMM_SEND_MSG(pstLrrcOssStateReqMsg);

    /*lint +e960*/

    return;
}

VOS_UINT32  NAS_LMM_PreProcRrcDataCnf( MsgBlock  *pMsg )
{
    LRRC_LMM_DATA_CNF_STRU              *pRrcDataCnf;
    VOS_UINT32                           ulIndex = 0;
    NAS_LMM_SEND_MSG_RESULT_FAIL_ACTION_FUN   pFailActFun;
    NAS_LMM_SEND_MSG_RESULT_SUCC_ACTION_FUN   pSuccActFun;
    VOS_UINT32                           ulRslt = VOS_FALSE;
    NAS_EMM_MRRC_MGMT_DATA_STRU         *pEmmMrrcMgmtData = NAS_EMM_NULL_PTR;
    VOS_UINT32                           ulIsDelBuff = VOS_FALSE;


    pRrcDataCnf = (LRRC_LMM_DATA_CNF_STRU *)(VOS_VOID*)pMsg;

    /*参数非法则直接丢弃 */
    if (LRRC_LMM_SEND_RSLT_BUTT == pRrcDataCnf->enSendRslt)
    {
        NAS_EMM_PUBU_LOG_NORM("NAS_LMM_PreProcRrcDataCnf: Invalid Parameter");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcRrcDataCnf_ENUM,LNAS_PARAM_INVALID);
        return NAS_LMM_MSG_HANDLED;
    }


    /*查不到该消息记录,则直接丢弃 */
    pEmmMrrcMgmtData = NAS_EMM_FindMsgInDataReqBuffer(pRrcDataCnf->ulOpId);

    if (NAS_EMM_NULL_PTR == pEmmMrrcMgmtData)
    {
        NAS_EMM_PUBU_LOG_WARN("NAS_LMM_PreProcRrcDataCnf(WARN): OpId mismatch!");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_PreProcRrcDataCnf_ENUM,LNAS_NULL_PTR);
        return  NAS_LMM_MSG_HANDLED;
    }

    /* 停止保护定时器*/
    NAS_LMM_StopStateTimer(TI_NAS_EMM_WAIT_RRC_DATA_CNF);

    ulRslt = VOS_FALSE;


    /*根据回复结果,查询处理函数 ,并做相应处理*/
    for (ulIndex = 0; ulIndex < g_ulSendMsgResultActTblLen; ulIndex++)
    {
        /* 通过MSG ID查找处理函数 */
        if(pEmmMrrcMgmtData->enLastMsgId == gstEmmMrrcSendMsgResultActTbl[ulIndex].enMsgId)
        {
            ulRslt = VOS_TRUE;

            /* 发送成功的处理 */
            if (LRRC_LMM_SEND_RSLT_SUCCESS == pRrcDataCnf->enSendRslt)
            {
                pSuccActFun = gstEmmMrrcSendMsgResultActTbl[ulIndex].pfSuccActionFun;

                /* 有处理函数 */
                if (VOS_NULL_PTR != pSuccActFun)
                {
                    (VOS_VOID)(pSuccActFun)(pMsg);
                }

                NAS_EMM_ClrDataReqBufferMsg(pRrcDataCnf->ulOpId);

                return NAS_LMM_MSG_HANDLED;

            }
            else
            {
                #if (FEATURE_PTM == FEATURE_ON)
                NAS_EMM_ProcErrlogEstCnfOrDataCnfFail((VOS_VOID*)pRrcDataCnf, EMM_OM_ERRLOG_TYPE_DATA_CNF_FAIL);
                #endif

                /* 发送失败的处理 */
                pFailActFun = gstEmmMrrcSendMsgResultActTbl[ulIndex].pfFailActionFun;

                /* 有处理函数 */
                if (VOS_NULL_PTR != pFailActFun)
                {
                    (VOS_VOID)(pFailActFun)(pMsg,&ulIsDelBuff);

                    /* 需要清除缓存 */
                    if (VOS_TRUE == ulIsDelBuff)
                    {
                        NAS_EMM_ClrDataReqBufferMsg(pRrcDataCnf->ulOpId);
                    }
                    return NAS_LMM_MSG_HANDLED;
                }
                else
                {
                    /* 没有处理函数，清除缓存消息 */
                    NAS_EMM_ClrDataReqBufferMsg(pRrcDataCnf->ulOpId);
                    return NAS_LMM_MSG_HANDLED;
                }
            }
        }
    }
    /* 没有找到处理函数 */
    if (VOS_FALSE == ulRslt)
    {
        NAS_EMM_ClrDataReqBufferMsg(pRrcDataCnf->ulOpId);

    }
    return NAS_LMM_MSG_HANDLED;
}
/*****************************************************************************
 Function Name   : NAS_LMM_PreProcIntraCoverageLostInd
 Description     : 预处理LMM内部的丢网消息
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunjitan 00193151     2012-10-18    Draft Enact
    2.lifuxin  00253982     2014-10-29    建链流程重构
*****************************************************************************/
VOS_UINT32  NAS_LMM_PreProcIntraCoverageLostInd( MsgBlock  *pMsg )
{
    (VOS_VOID)pMsg;

    /*当前的连接状态时NAS_EMM_CONN_ESTING，说明建链过程中，RRC
      还没有回复EST_CNF， 再此期间收到了RRC的丢网消息，此时认为建链失败，
      停止TI_NAS_EMM_MRRC_WAIT_RRC_CONN_CNF， 发送内部建链失败消息然后
      进入相应的状态机处理， 同时也发送内部丢网消息， 进入相应的状态机
      处理。
    */
    if(NAS_EMM_CONN_ESTING == NAS_EMM_GetConnState())
    {
        NAS_LMM_StopStateTimer(TI_NAS_EMM_MRRC_WAIT_RRC_CONN_CNF);

        NAS_EMM_SecuCurrentContextUpNasCountBack();

        /*发MRRC_CONNECT_FAIL_IND*/
        NAS_EMM_MrrcConnectFailInd(LRRC_EST_EST_CONN_FAIL);

        /* EMM给EMM自己发送AREA LOST消息，以给压栈前的流程处理 */
        NAS_EMMC_SendEmmCoverageLostInd();
    }

    /* 如果RRC连接状态处于释放过程中，设置为IDLE */
    if(NAS_EMM_CONN_RELEASING == NAS_EMM_GetConnState())
    {
        NAS_EMM_SetConnState(NAS_EMM_CONN_IDLE);
    }

    /* 进状态机处理 */
    return NAS_LMM_MSG_DISCARD;
}

/*****************************************************************************
 Function Name   : NAS_LMM_SendMmcSuspendInfoChange
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.HANLUFENG 41410      2013-6-19  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LMM_SendMmcSuspendInfoChangeRatChange(
                LMM_MMC_RAT_CHANGE_TYPE_ENUM_UINT32 ulRatChangeType)
{
    LMM_MMC_SUSPEND_INFO_CHANGE_NOTIFY_STRU           *pstSuspendInfoChangeMsg    = NAS_EMM_NULL_PTR;

    NAS_LMM_PUBM_LOG_INFO( "NAS_LMM_SendMmcSuspendInfoChange: enter");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_SendMmcSuspendInfoChangeRatChange_ENUM,LNAS_ENTRY);

    /* 申请MMC内部消息 */
    pstSuspendInfoChangeMsg =
        (VOS_VOID *)NAS_LMM_GetLmmMmcMsgBuf(
                        sizeof(LMM_MMC_SUSPEND_INFO_CHANGE_NOTIFY_STRU));

    if(NAS_EMM_NULL_PTR == pstSuspendInfoChangeMsg)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_SendMmcSuspendInfoChange: MSG ALLOC ERR !!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_SendMmcSuspendInfoChangeRatChange_ENUM,LNAS_NULL_PTR);
        /*
        NAS_LMM_PUBM_LOG1_ERR( "NAS_LMM_SendMmcSuspendInfoChange: MSG ALLOC ERR !!",
                                pstSuspendInfoChangeMsg);
        */
        return ;
    }

    /*lint -e960*/

    NAS_LMM_MEM_SET_S(  pstSuspendInfoChangeMsg,
                        sizeof(LMM_MMC_SUSPEND_INFO_CHANGE_NOTIFY_STRU),
                        0,
                        sizeof(LMM_MMC_SUSPEND_INFO_CHANGE_NOTIFY_STRU));


    /* 填写LMM_MMC_SYS_CFG_CNF_STRU 的DOPRA消息头 */
    EMM_PUBU_COMP_MMC_MSG_HEADER(pstSuspendInfoChangeMsg,
            sizeof(LMM_MMC_SUSPEND_INFO_CHANGE_NOTIFY_STRU) - EMM_LEN_VOS_MSG_HEADER);

    /*lint +e960*/

    /* 填写LMM_MMC_SYS_CFG_CNF 的消息ID标识 */
    pstSuspendInfoChangeMsg->ulMsgId           = ID_LMM_MMC_SUSPEND_INFO_CHANGE_NOTIFY;

    /* 填写结果*/
    pstSuspendInfoChangeMsg->ulInfoType     = LMM_MMC_SUSPEND_RAT_INFO_CHANGE;
    pstSuspendInfoChangeMsg->ulRatChangeType= ulRatChangeType;

    NAS_LMM_PUBM_LOG1_INFO( "NAS_LMM_SendMmcSuspendInfoChange: ulRatChangeType =",
                            pstSuspendInfoChangeMsg->ulRatChangeType);
    TLPS_PRINT2LAYER_INFO1(NAS_LMM_SendMmcSuspendInfoChangeRatChange_ENUM,LNAS_FUNCTION_LABEL1,
                            pstSuspendInfoChangeMsg->ulRatChangeType);

    NAS_LMM_PUBM_LOG1_INFO( "NAS_LMM_SendMmcSuspendInfoChange: pulInfoType =",
                            pstSuspendInfoChangeMsg->ulInfoType);
    TLPS_PRINT2LAYER_INFO1(NAS_LMM_SendMmcSuspendInfoChangeRatChange_ENUM,LNAS_FUNCTION_LABEL2,
                            pstSuspendInfoChangeMsg->ulInfoType);
    /* 发送消息 */
    NAS_LMM_SendLmmMmcMsg(                    pstSuspendInfoChangeMsg);

    return ;
}


/*****************************************************************************
 Function Name   : NAS_EMM_PreProcMsgRrcSuspendInfoChangeInd
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.HANLUFENG 41410      2013-6-19  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_PreProcMsgRrcSuspendInfoChangeInd( MsgBlock  *pstMsg )
{

    LRRC_LMM_SUSPEND_INFO_CHANGE_IND_STRU *pstInfoChange = NAS_EMM_NULL_PTR;

    NAS_LMM_PUBM_LOG_NORM("NAS_EMM_PreProcMsgRrcSuspendInfoChangeInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgRrcSuspendInfoChangeInd_ENUM,LNAS_ENTRY);

    pstInfoChange = (LRRC_LMM_SUSPEND_INFO_CHANGE_IND_STRU*)(VOS_VOID *)pstMsg;

    /* 参数检查 */
    if(LRRC_LNAS_SUSPEND_RAT_INFO_CHANGE != pstInfoChange->ulInfoType)
    {
        NAS_LMM_PUBM_LOG1_NORM("NAS_EMM_PreProcMsgRrcSuspendInfoChangeInd,ERROR : ulInfoType = ",
                                pstInfoChange->ulInfoType);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_PreProcMsgRrcSuspendInfoChangeInd_ENUM,LNAS_FUNCTION_LABEL1,
                                pstInfoChange->ulInfoType);
        return  NAS_LMM_MSG_HANDLED;
    }

    NAS_LMM_PUBM_LOG1_NORM("NAS_EMM_PreProcMsgRrcSuspendInfoChangeInd,ERROR : ulRatChangeType = ",
                                pstInfoChange->ulRatChangeType);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_PreProcMsgRrcSuspendInfoChangeInd_ENUM,LNAS_FUNCTION_LABEL2,
                                pstInfoChange->ulRatChangeType);

    if(LRRC_LNAS_RAT_CHANGE_G2W == pstInfoChange->ulRatChangeType)
    {
        NAS_EMM_SetSuspendDir(LRRC_LMM_SUS_SYS_CHNG_DIR_L2W);
        NAS_LMM_SendMmcSuspendInfoChangeRatChange(LMM_MMC_RAT_CHANGE_G2W);
    }
    else if(LRRC_LNAS_RAT_CHANGE_W2G == pstInfoChange->ulRatChangeType)
    {
        NAS_EMM_SetSuspendDir(LRRC_LMM_SUS_SYS_CHNG_DIR_L2G);
        NAS_LMM_SendMmcSuspendInfoChangeRatChange(LMM_MMC_RAT_CHANGE_W2G);
    }
    else
    {
        NAS_LMM_PUBM_LOG_NORM("NAS_EMM_PreProcMsgRrcSuspendInfoChangeInd,ERROR : ulRatChangeType");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgRrcSuspendInfoChangeInd_ENUM,LNAS_FUNCTION_LABEL3);
    }

    return  NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_LMM_RevMmcInfoReq
 Description     : 处理从MMC层传过来的消息
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lifuxin 00253982  2013-11-26    Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LMM_RevMmcModemInfoReq(MsgBlock *  pMsg)
{
    MMC_LMM_OTHER_MODEM_INFO_NOTIFY_STRU *pstMmcRevInfo;
    LMM_LRRC_OTHER_MODEM_INFO_NOTIFY_STRU *pModemInfoMsg;


    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_RevMmcInfoReq!");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_RevMmcModemInfoReq_ENUM,LNAS_ENTRY);

    pstMmcRevInfo = (MMC_LMM_OTHER_MODEM_INFO_NOTIFY_STRU *)(VOS_VOID*)pMsg;
    /*申请消息内存*/
    pModemInfoMsg = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(LMM_LRRC_OTHER_MODEM_INFO_NOTIFY_STRU));

    /*判断申请结果，若失败退出*/
    if (VOS_NULL_PTR == pModemInfoMsg)
    {
        return NAS_LMM_MSG_DISCARD;
    }

    /*lint -e960*/
    NAS_LMM_MEM_SET_S(  pModemInfoMsg,
                        sizeof(LMM_LRRC_OTHER_MODEM_INFO_NOTIFY_STRU),
                        0,
                        sizeof(LMM_LRRC_OTHER_MODEM_INFO_NOTIFY_STRU));

    /*构造ID_LMM_LRRC_OTHER_MODEM_INFO_NOTIFY消息*/
    /*填充消息头*/
    NAS_EMM_SET_RRC_MSG_HEADER( pModemInfoMsg,
                                (sizeof(LMM_LRRC_OTHER_MODEM_INFO_NOTIFY_STRU)-
                                 NAS_EMM_LEN_VOS_MSG_HEADER));
    /*填充消息ID*/
    pModemInfoMsg->ulMsgId = ID_LRRC_LMM_OTHER_MODEM_INFO_NOTIFY;
    pModemInfoMsg->bitOpCurrCampPlmnId = pstMmcRevInfo->bitOpCurrCampPlmnId;
    pModemInfoMsg->stCurrCampPlmnId.aucPlmnId[0] =
                    pstMmcRevInfo->stCurrCampPlmnId.aucPlmnId[0];
    pModemInfoMsg->stCurrCampPlmnId.aucPlmnId[1] =
                    pstMmcRevInfo->stCurrCampPlmnId.aucPlmnId[1];
    pModemInfoMsg->stCurrCampPlmnId.aucPlmnId[2] =
                    pstMmcRevInfo->stCurrCampPlmnId.aucPlmnId[2];

    /*向RRC模块发送状态变化消息*/
    NAS_LMM_SEND_MSG(pModemInfoMsg);
    /*lint +e960*/

    return NAS_LMM_MSG_HANDLED;
}
/*****************************************************************************
 Function Name   : NAS_LMM_SendRrcCellSignReportNotify
 Description     : 将MMC传过来的小区信号门限值和时间间隔信息发送给RRC
 Input           : 时间间隔、门限值
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.chengmin 00285307  2014-12-15    Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LMM_SendRrcCellSignReportNotify(VOS_UINT8 ucMinRptTimerInterval, VOS_UINT8 ucSignThreshold)
{
    LRRC_LMM_CELL_SIGN_REPORT_NOTIFY_STRU     *pstRrcCellSignReptNotify;

    /* 申请DOPRA消息 */
    pstRrcCellSignReptNotify = (VOS_VOID *) NAS_LMM_ALLOC_MSG(sizeof(LRRC_LMM_CELL_SIGN_REPORT_NOTIFY_STRU));
    if (NAS_LMM_NULL_PTR == pstRrcCellSignReptNotify)
    {
        return NAS_EMM_SEND_RRC_ERR;
    }

    /* 清空 */
    NAS_LMM_MEM_SET_S(  pstRrcCellSignReptNotify,
                        sizeof(LRRC_LMM_CELL_SIGN_REPORT_NOTIFY_STRU),
                        0,
                        sizeof(LRRC_LMM_CELL_SIGN_REPORT_NOTIFY_STRU));

    /* 打包VOS消息头 */
    NAS_EMM_SET_RRC_MSG_HEADER((pstRrcCellSignReptNotify),
            NAS_EMM_GET_MSG_LENGTH_NO_HEADER(LRRC_LMM_CELL_SIGN_REPORT_NOTIFY_STRU));

    /* 填充消息 */
    pstRrcCellSignReptNotify->ulMsgId = ID_LRRC_LMM_CELL_SIGN_REPORT_NOTIFY;
    pstRrcCellSignReptNotify->ucMinRptTimerInterval = ucMinRptTimerInterval;
    pstRrcCellSignReptNotify->ucSignThreshold = ucSignThreshold;

    /* 发送DOPRA消息 */
    NAS_LMM_SEND_MSG(pstRrcCellSignReptNotify);

    NAS_LMM_PUBM_LOG2_INFO("NAS_LMM_SendRrcCellSignReportNotify:rptTimer,signThreshold:",ucMinRptTimerInterval,ucSignThreshold);
    TLPS_PRINT2LAYER_INFO2(NAS_LMM_SendRrcCellSignReportNotify_ENUM,LNAS_FUNCTION_LABEL1,
                            ucMinRptTimerInterval,ucSignThreshold);

    return NAS_EMM_SEND_RRC_OK;
}

/*****************************************************************************
 Function Name   : NAS_LMM_PreProcMmcCellSignReportNotify
 Description     : 处理从MMC层传过来的CELL_SIGN_REPORT_NOTIFY消息
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.chengmin 00285307  2014-12-15    Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LMM_PreProcMmcCellSignReportNotify(MsgBlock  *pstMsg)
{
    MMC_LMM_CELL_SIGN_REPORT_NOTIFY_STRU      *pstMmcCellSignReport = NAS_EMM_NULL_PTR;


    NAS_LMM_PUBM_LOG_NORM("NAS_LMM_PreProcMmcCellSignReportNotify is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcMmcCellSignReportNotify_ENUM,LNAS_ENTRY);

    /* 入参检查 */
    if ( NAS_EMM_NULL_PTR == pstMsg)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_PreProcMmcCellSignReportNotify:input ptr null!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_PreProcMmcCellSignReportNotify_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_HANDLED;
    }

    pstMmcCellSignReport = (MMC_LMM_CELL_SIGN_REPORT_NOTIFY_STRU*)(VOS_VOID*)pstMsg;

    /*不作处理直接通知LRRC*/
    (VOS_VOID)NAS_LMM_SendRrcCellSignReportNotify(pstMmcCellSignReport->ucMinRptTimerInterval, pstMmcCellSignReport->ucSignThreshold);

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_LMM_SendMccCellSignReportInd
 Description     : 当收到LRRC上报的信号质量信息后，向MMC上报该信息
 Input           : 信号质量结构体指针
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.chengmin 00285307  2014-12-15    Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LMM_SendMccCellSignReportInd(MsgBlock  *pstMsg)
{
    LMM_MMC_CELL_SIGN_REPORT_IND_STRU           *pstMmcCellSignRptInd    = NAS_EMM_NULL_PTR;
    LRRC_LMM_CELL_SIGN_REPORT_IND_STRU          *pstRrcCellSignPptInd    = NAS_EMM_NULL_PTR;

    NAS_LMM_PUBM_LOG_INFO( "NAS_LMM_SendMccCellSignReportInd: enter");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_SendMccCellSignReportInd_ENUM,LNAS_ENTRY);

    /* 入参检查 */
    if ( NAS_EMM_NULL_PTR == pstMsg)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_SendMccCellSignReportInd:input ptr null!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_SendMccCellSignReportInd_ENUM,LNAS_NULL_PTR);
        return  NAS_EMM_SEND_MMC_ERR;
    }
    pstRrcCellSignPptInd = (LRRC_LMM_CELL_SIGN_REPORT_IND_STRU*)(VOS_VOID*)pstMsg;

    /* 申请MMC内部消息 */
    pstMmcCellSignRptInd = (VOS_VOID *)NAS_LMM_GetLmmMmcMsgBuf(sizeof(LMM_MMC_CELL_SIGN_REPORT_IND_STRU));
    if(NAS_EMM_NULL_PTR == pstMmcCellSignRptInd)
    {
        NAS_LMM_PUBM_LOG_ERR( "NAS_LMM_SendMccCellSignReportInd: MSG ALLOC ERR !!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_SendMccCellSignReportInd_ENUM,LNAS_ERROR);
        return NAS_EMM_SEND_MMC_ERR;
    }

    NAS_LMM_MEM_SET_S(  pstMmcCellSignRptInd,
                        sizeof(LMM_MMC_CELL_SIGN_REPORT_IND_STRU),
                        0,
                        sizeof(LMM_MMC_CELL_SIGN_REPORT_IND_STRU));

    /* 填写DOPRA消息头 */
    EMM_PUBU_COMP_MMC_MSG_HEADER(pstMmcCellSignRptInd,
            sizeof(LMM_MMC_CELL_SIGN_REPORT_IND_STRU) - EMM_LEN_VOS_MSG_HEADER);

    /* 填写消息ID标识 */
    pstMmcCellSignRptInd->ulMsgId              = ID_LMM_MMC_CELL_SIGN_REPORT_IND;

    /*填消息内容*/
    pstMmcCellSignRptInd->sRssi                = pstRrcCellSignPptInd->sRssi;
    pstMmcCellSignRptInd->sRsd                 = pstRrcCellSignPptInd->sRsd;
    pstMmcCellSignRptInd->sRsrp                = pstRrcCellSignPptInd->sRsrp;
    pstMmcCellSignRptInd->sRsrq                = pstRrcCellSignPptInd->sRsrq;
    pstMmcCellSignRptInd->lSinr                = pstRrcCellSignPptInd->lSinr;
    pstMmcCellSignRptInd->stCQI.usRI           = pstRrcCellSignPptInd->stCQI.usRI;
    pstMmcCellSignRptInd->stCQI.aucRes[0]      = pstRrcCellSignPptInd->stCQI.aucRes[0];
    pstMmcCellSignRptInd->stCQI.aucRes[1]      = pstRrcCellSignPptInd->stCQI.aucRes[1];
    pstMmcCellSignRptInd->stCQI.ausCQI[0]      = pstRrcCellSignPptInd->stCQI.ausCQI[0];
    pstMmcCellSignRptInd->stCQI.ausCQI[1]      = pstRrcCellSignPptInd->stCQI.ausCQI[1];

    /* 发送消息 */
    NAS_LMM_SendLmmMmcMsg(                    pstMmcCellSignRptInd);

    NAS_LMM_PUBM_LOG3_INFO("NAS_LMM_SendMccCellSignReportInd:sRssi,sRsd,sRsrp:",pstRrcCellSignPptInd->sRssi,pstRrcCellSignPptInd->sRsd,pstRrcCellSignPptInd->sRsrp);
    TLPS_PRINT2LAYER_INFO1(NAS_LMM_SendMccCellSignReportInd_ENUM,LNAS_FUNCTION_LABEL1,
                                                (VOS_UINT16)pstRrcCellSignPptInd->sRssi);
    TLPS_PRINT2LAYER_INFO2(NAS_LMM_SendMccCellSignReportInd_ENUM,LNAS_FUNCTION_LABEL2,
                                                (VOS_UINT16)pstRrcCellSignPptInd->sRsd,
                                                (VOS_UINT16)pstRrcCellSignPptInd->sRsrp);

    NAS_LMM_PUBM_LOG3_INFO("NAS_LMM_SendMccCellSignReportInd:sRsrq,lSinr,stCQI.usRI:",pstRrcCellSignPptInd->sRsrq,pstRrcCellSignPptInd->lSinr,pstRrcCellSignPptInd->stCQI.usRI);
    TLPS_PRINT2LAYER_INFO1(NAS_LMM_SendMccCellSignReportInd_ENUM,LNAS_FUNCTION_LABEL3,
                                                (VOS_UINT16)pstRrcCellSignPptInd->sRsrq);
    TLPS_PRINT2LAYER_INFO2(NAS_LMM_SendMccCellSignReportInd_ENUM,LNAS_FUNCTION_LABEL4,
                                                pstRrcCellSignPptInd->lSinr,
                                                pstRrcCellSignPptInd->stCQI.usRI);
    NAS_LMM_PUBM_LOG3_INFO("NAS_LMM_SendMccCellSignReportInd:aucRes[0],aucRes[1],ausCQI[0]:",
                                                            pstRrcCellSignPptInd->stCQI.aucRes[0],
                                                            pstRrcCellSignPptInd->stCQI.aucRes[1],
                                                            pstRrcCellSignPptInd->stCQI.ausCQI[0]);
    TLPS_PRINT2LAYER_INFO1(NAS_LMM_SendMccCellSignReportInd_ENUM,LNAS_FUNCTION_LABEL5,
                                                pstRrcCellSignPptInd->stCQI.aucRes[0]);
    TLPS_PRINT2LAYER_INFO2(NAS_LMM_SendMccCellSignReportInd_ENUM,LNAS_FUNCTION_LABEL6,
                                                pstRrcCellSignPptInd->stCQI.aucRes[1],
                                                pstRrcCellSignPptInd->stCQI.ausCQI[0]);
    NAS_LMM_PUBM_LOG1_INFO("NAS_LMM_SendMccCellSignReportInd:ausCQI[1]:",pstRrcCellSignPptInd->stCQI.ausCQI[1]);
    TLPS_PRINT2LAYER_INFO1(NAS_LMM_SendMccCellSignReportInd_ENUM,LNAS_FUNCTION_LABEL7,
                                               pstRrcCellSignPptInd->stCQI.ausCQI[1]);

    return NAS_EMM_SEND_MMC_OK;
}

/*****************************************************************************
 Function Name   : NAS_EMM_PreProcMsgRrcCellSignReportInd
 Description     : 处理从LRRC传过来的CELL_SIGN_REPORT_IND消息
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.chengmin 00285307  2014-12-15    Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_EMM_PreProcMsgRrcCellSignReportInd(MsgBlock  *pstMsg)
{
    NAS_LMM_PUBM_LOG_NORM("NAS_EMM_PreProcMsgRrcCellSignReportInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgRrcCellSignReportInd_ENUM,LNAS_ENTRY);

    /* 入参检查 */
    if ( NAS_EMM_NULL_PTR == pstMsg)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_EMM_PreProcMsgRrcCellSignReportInd:input ptr null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_PreProcMsgRrcCellSignReportInd_ENUM,LNAS_NULL_PTR);
        return  NAS_LMM_MSG_HANDLED;
    }

    /*不作处理直接通知MMC*/
    (VOS_VOID)NAS_LMM_SendMccCellSignReportInd(pstMsg);

    return NAS_LMM_MSG_HANDLED;
}
/*****************************************************************************
 Function Name   : NAS_EMM_PreProcMsgRrcPagingInd
 Description     : 预处理Lrrc paging ind消息
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixiantiao 00258641  2015-01-27    Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_EMM_PreProcMsgRrcPagingInd(MsgBlock  *pstMsg)
{
    #if (FEATURE_PTM == FEATURE_ON)
    VOS_UINT32                          ulCurEmmStat = NAS_EMM_NULL;
    LRRC_LMM_PAGING_IND_STRU           *pMsgRrcPagingInd = NAS_EMM_NULL_PTR;

    //(VOS_VOID)pstMsg;

    ulCurEmmStat = NAS_LMM_PUB_COMP_EMMSTATE(NAS_EMM_CUR_MAIN_STAT,
                                            NAS_EMM_CUR_SUB_STAT);

    pMsgRrcPagingInd = (LRRC_LMM_PAGING_IND_STRU *)(VOS_VOID *)pstMsg;

    /* 都进状态机处理，TAU和SER都改为在状态机中处理 */
    switch(ulCurEmmStat)
    {
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG,EMM_SS_REG_NORMAL_SERVICE):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG,EMM_SS_REG_ATTEMPTING_TO_UPDATE):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG,EMM_SS_REG_LIMITED_SERVICE):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG,EMM_SS_REG_WAIT_ACCESS_GRANT_IND):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG,EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_SER_INIT,EMM_SS_SER_WAIT_CN_SER_CNF):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_TAU_INIT,EMM_SS_TAU_WAIT_CN_TAU_CNF):

            break;
            /* 上面几个状态，收到PAGING时，都直接进状态机进行处理，其他状态会直接丢弃；所以在
            其他状态下收到PAGING，增加CHR的主动上报 */
        default:
            if (LRRC_LNAS_PAGING_TYPE1 == pMsgRrcPagingInd->enPagingType)
            {
                NAS_EMM_PagingErrRecord(EMM_OM_ERRLOG_PAGING_CS,EMM_OM_LMM_PAGING_FAIL_CAUSE_ABNORMAL_STATUS);
            }
            else
            {
                NAS_EMM_PagingErrRecord(EMM_OM_ERRLOG_PAGING_PS,EMM_OM_LMM_PAGING_FAIL_CAUSE_ABNORMAL_STATUS);
            }
            break;
    }
    #else
    (VOS_VOID)pstMsg;
    #endif
    return NAS_LMM_MSG_DISCARD;
}

#if (FEATURE_PTM == FEATURE_ON)
NAS_LMM_ERRLOG_ACT_STRU  gstEmmErrlogActTbl[]=
{
    {EMM_MS_REG_INIT,               NAS_EMM_AttachErrRecord},
    {EMM_MS_TAU_INIT,               NAS_EMM_TAUErrRecord},
    {EMM_MS_SER_INIT,               NAS_EMM_NorServiceErrRecord}
};
VOS_UINT32        g_ulEmmErrlogActTblLen = sizeof(gstEmmErrlogActTbl)
                                                / sizeof(NAS_LMM_ERRLOG_ACT_STRU);
/*******************************************************************************
  Function : NAS_EMM_ProcErrlogEstCnfOrDataCnfFail
  Input    : NONE
  Output   : NONE
  NOTE     : 商用Errlog在建链失败或者直传失败的时候的处理
  Return   : NONE
  History  :
    1.lifuxin 00253982     2015-02-10  NEW draf
*******************************************************************************/
VOS_VOID NAS_EMM_ProcErrlogEstCnfOrDataCnfFail(
                 VOS_VOID*                         pstEmmProcessFail,
                 EMM_OM_ERRLOG_TYPE_ENUM_UINT16    enErrType)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT16                          usCurState;
    NAS_LMM_ERRLOG_ACT_FUN              pActFun;

    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_ProcErrlogEstCnfOrDataCnfFail!!");

    usCurState = NAS_EMM_CUR_MAIN_STAT;
    if((EMM_MS_REG_INIT != usCurState)
      && (EMM_MS_TAU_INIT != usCurState)
      && (EMM_MS_SER_INIT != usCurState))
    {
        return;
    }

    /*根据当前主状态去找对应的errlog处理函数*/
    for(ulLoop = 0; ulLoop < g_ulEmmErrlogActTblLen; ulLoop++)
    {
        if(gstEmmErrlogActTbl[ulLoop].enCurState == usCurState)
        {
            pActFun = gstEmmErrlogActTbl[ulLoop].pfErrlogFun;
            if(VOS_NULL_PTR != pActFun)
            {
                (VOS_VOID)pActFun(pstEmmProcessFail, enErrType);
            }
            break;
        }
    }

    return;
}
#endif

/*****************************************************************************
 Function Name   : NAS_LMM_SendRrcDisableLteNotify
 Description     : 向RRC发送ID_LRRC_LMM_DISABLE_LTE_NOTIFY消息
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunjitan 00193151      2015-01-04  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LMM_SendRrcDisableLteNotify(VOS_VOID)
{
    LRRC_LMM_DISABLE_LTE_NOTIFY_STRU   *pstRrcDisableLteMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgLen;

    NAS_LMM_PUBM_LOG_INFO( "NAS_LMM_SendRrcDisableLteNotify: enter");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_SendRrcDisableLteNotify_ENUM,LNAS_ENTRY);

    /*计算长度不包含VOS消息头*/
    ulMsgLen     = sizeof(LRRC_LMM_DISABLE_LTE_NOTIFY_STRU);

    /*分配内存*/
    pstRrcDisableLteMsg = (VOS_VOID *)NAS_LMM_ALLOC_MSG(ulMsgLen);
    if(NAS_EMM_NULL_PTR == pstRrcDisableLteMsg)
    {
        NAS_LMM_PUBM_LOG_INFO("NAS_LMM_SendRrcDisableLteNotify: ALLOC MSG FAIL!");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_SendRrcDisableLteNotify_ENUM,LNAS_NULL_PTR);
        return;
    }

    /*清空申请到的消息空间*/
    NAS_LMM_MEM_SET_S(  pstRrcDisableLteMsg,
                        sizeof(LRRC_LMM_DISABLE_LTE_NOTIFY_STRU),
                        0,
                        sizeof(LRRC_LMM_DISABLE_LTE_NOTIFY_STRU));

    /*填充VOS消息头*/
    NAS_EMM_SET_RRC_MSG_HEADER(pstRrcDisableLteMsg, ulMsgLen-VOS_MSG_HEAD_LENGTH);

    /* 填充消息ID */
    pstRrcDisableLteMsg->ulMsgId = ID_LRRC_LMM_DISABLE_LTE_NOTIFY;

    /* 发送ID_LRRC_LMM_DISABLE_LTE_NOTIFY */
    NAS_LMM_SEND_MSG(pstRrcDisableLteMsg);
    return;
}


/*****************************************************************************
 Function Name   : NAS_EMMC_GuCampTaPlmnIsInLteForbTaPlmn
 Description     : LRRC指示LNAS发生了异系统流程，并将带过来TALIST是否在
                   被禁列表的TALIST里面
 Input           : pstTaiList --LRRC带上来TAILIST
                   pstPlmn    --用于存储plmn
                   pulPlmn    --用于存储plmn计数
 Output          : None
 Return          : PS_TRUE  都在被禁列表里面
                   PS_FALSE 部分在被禁列表里面
 History         :
    1.lifuxin 00253982      2015-03-27  Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_EMM_RatTaListIsInForbTaList(
                    const LRRC_LNAS_OPT_INFO_TAILIST_STRU *pstTaiList,
                    MMC_LMM_LTE_NO_SUBSCRIBE_PLMN_LIST_STRU *pstLteNoSubsPlmnList)
{
    NAS_MM_FORB_TA_LIST_STRU    *pstForbTaForRoam = NAS_EMM_NULL_PTR;
    VOS_UINT32                  i = 0;
    VOS_UINT32                  j = 0;
    VOS_UINT32                  ulForbTaNum = 0;

    NAS_EMM_PUBU_LOG_NORM("NAS_EMM_RatTaListIsInForbTaList is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_RatTaListIsInForbTaList_ENUM,LNAS_ENTRY);

    /*获取漫游不允许的TAILIST列表*/
    pstForbTaForRoam = NAS_LMM_GetEmmInfoNetInfoForbTaForRoamAddr();
    for(i = 0; i < pstTaiList->ulTaiNum; i++)
    {
        for(j = 0; j < pstForbTaForRoam->ulTaNum; j++)
        {
            if(NAS_LMM_MATCH_SUCCESS == NAS_LMM_PlmnMatch((NAS_MM_PLMN_ID_STRU*)&(pstTaiList->stTaiList[i].stPlmnId),
                                                            &(pstForbTaForRoam->astTa[j].stPlmnId)))
            {
                NAS_LMM_MEM_CPY_S(  (pstLteNoSubsPlmnList->astPlmnId + ulForbTaNum),
                                    sizeof(MMC_LMM_PLMN_ID_STRU),
                                    (NAS_MM_PLMN_ID_STRU*)&(pstTaiList->stTaiList[i].stPlmnId),
                                    sizeof(MMC_LMM_PLMN_ID_STRU));
                ulForbTaNum++;
                break;
            }
        }
        /*加保护，如果带的小区个数大于最大的小区计数了，则退出循环*/
        if(ulForbTaNum >= MMC_LMM_MAX_EUTRAN_NOT_ALLOW_PLMN_NUM)
        {
            break;
        }
    }

    pstLteNoSubsPlmnList->ulPlmnNum = ulForbTaNum;

    if(0 == ulForbTaNum)
    {
        /*都没有在FORB列表里面*/
        return NAS_EMM_RAT_LRRC_TAILIST_STATUS_ALL_NOT_IN_FORB_LIST;
    }
    else if(ulForbTaNum > 0 && ulForbTaNum < pstTaiList->ulTaiNum)
    {
        /*部分在FORB列表里面*/
        return NAS_EMM_RAT_LRRC_TAILIST_STATUS_PART_IN_FORB_LIST;
    }
    else
    {
        /*都在FORB列表里面*/
        return NAS_EMM_RAT_LRRC_TAILIST_STATUS_ALL_IN_FORB_LIST;
    }

}

/*****************************************************************************
 Function Name   : NAS_LMM_PreProcInterOptIndMsg
 Description     : 收到LRRC的异系统操作指示的处理，目前主要用于4G未开户问题
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lifuxin 00253982  2015-2-27    Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LMM_PreProcInterOptIndMsg( MsgBlock  *pMsg)
{
    LRRC_LMM_INTER_OPT_IND                  *pstLrrcLmmInerOptInd;
    VOS_UINT32                              enRatLrrcTalistStatus = 0;
    MMC_LMM_LTE_NO_SUBSCRIBE_PLMN_LIST_STRU  stLteNoSubsPlmnList;

    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_PreProcInterOptIndMsg!");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcInterOptIndMsg_ENUM,LNAS_ENTRY);

    pstLrrcLmmInerOptInd = (LRRC_LMM_INTER_OPT_IND *)(VOS_VOID*)pMsg;
    /*测试模式,直接丢弃*/
    if(PS_SUCC == LPS_OM_IsTestMode())
    {
        return NAS_LMM_MSG_HANDLED;
    }

    /*如果TALIST信元无效，则丢弃该消息*/
    if(0 == pstLrrcLmmInerOptInd->ulBitOpTaList)
    {
        return NAS_LMM_MSG_HANDLED;
    }

    /*当前是非从模态，则直接丢弃该消息*/
    if (NAS_EMM_IS_SUSPEND != NAS_EMM_IsSuspended())
    {
        return NAS_LMM_MSG_HANDLED;
    }

    enRatLrrcTalistStatus = NAS_EMM_RatTaListIsInForbTaList(
                            &(pstLrrcLmmInerOptInd->stOptInfoTaiList),
                            &stLteNoSubsPlmnList);
    if((NAS_EMM_RAT_LRRC_TAILIST_STATUS_ALL_IN_FORB_LIST == enRatLrrcTalistStatus)
      || NAS_EMM_RAT_LRRC_TAILIST_STATUS_PART_IN_FORB_LIST == enRatLrrcTalistStatus)
    {
        NAS_LMM_PUBM_LOG_INFO("NAS_LMM_PreProcInterOptIndMsg: TaiList is all in ForbList OR Part Tailist is in Forblist!");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcInterOptIndMsg_ENUM,LNAS_FUNCTION_LABEL1);
        NAS_LMM_LteNoSubscribeWithOutExtCauseHandle(&stLteNoSubsPlmnList);
    }
    else
    {
        /*TA都不在被禁列表里面，不需要处理*/
        NAS_LMM_PUBM_LOG_INFO("NAS_LMM_PreProcInterOptIndMsg: TaiList is not Forb List!");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcInterOptIndMsg_ENUM,LNAS_FUNCTION_LABEL2);
    }

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_LMM_PreProcMsgGradualForbTimerExpire
 Description     : Gradual Forb惩罚定时器超时处理函数
 Input           : pstMsg :消息
 Output          : None
 Return          : None
 History         :
    1.leixiantiao 00258641      2015-07-31  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_LMM_PreProcMsgGradualForbTimerExpire(MsgBlock *pstMsg)
{
    VOS_UINT32                          ulTimerPara;
    VOS_UINT32                          ulIndex;
    NAS_LMM_MATCH_RESULT_ENUM_UINT32    enMatchResult  = NAS_LMM_MATCH_FAIL;
    NAS_LMM_MAIN_STATE_ENUM_UINT16      enEmmMainState = NAS_LMM_GetEmmCurFsmMS();
    NAS_MM_TA_STRU                      stTimerOutTa;
    REL_TIMER_MSG                      *pTimerMsg;

    /* 检查入参 */
    if (NAS_EMM_NULL_PTR == pstMsg)
    {
        return NAS_LMM_MSG_HANDLED;
    }

    /* 关机的时候会清掉Gradual Forb本地维护信息, 所以关机过程中收到定时器超时, 不需要处理 */
    if (EMM_MS_NULL == enEmmMainState)
    {
        return NAS_LMM_MSG_HANDLED;
    }

    /* 获取对应Opid, 此Opid在起定时器传入, 且是唯一 */
    pTimerMsg                       = (REL_TIMER_MSG *)(VOS_VOID *)pstMsg;
    ulTimerPara                     = pTimerMsg->ulPara;

    /* 根据Opid从列表中查找对应TA */
    enMatchResult = NAS_LMM_TimerParaMatchGradualForbTaList(ulTimerPara, &ulIndex);

    /* 未找到对应TA, 返回 */
    if (NAS_LMM_MATCH_SUCCESS != enMatchResult)
    {
        NAS_LMM_PUBM_LOG1_WARN("NAS_EMM_PreProcMsgGradualForbTimerExpire Can't Find; ulTimerPara = ", ulTimerPara);
        return NAS_LMM_MSG_HANDLED;
    }
    /* 停定时器: 防止在超时消息未处理前又启动了定时器的情况, 如切换到Forb TA发起TAU被#15拒了,
       此时定时器超时, 超时消息在OSA消息队列里, 该情况下新起定时器, 处理定时器超消息时定时器时运行着的 */
    if (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsGradualForbiddenTimerRunning(ulIndex, TI_NAS_EMM_PTL_GRADUAL_FORB_TIMER))
    {
        /* 该情况下丢掉定时器超时消息 */
        return NAS_LMM_MSG_HANDLED;
    }

    /* 获取当前惩罚定时器超时TA */
    NAS_LMM_GetGradualForbTaWithIndex(ulIndex, &stTimerOutTa);

    /* 勾出当前临时TA LIST列表 */
    NAS_EMM_SndOmGradualForbTaInfo(&stTimerOutTa, NAS_LMM_GRADUAL_FORB_TA_OPERATION_TYPE_TIMER_OUT);

    /* 通知LRRC Forb Ta列表更新 */
    NAS_EMMC_SendRrcCellSelectionReq(LRRC_LNAS_FORBTA_CHANGE);

    return NAS_LMM_MSG_HANDLED;
}
/*****************************************************************************
 Function Name   : NAS_LMM_PreProcMsgGradualForbAgingTimerExpire
 Description     : Gradual Forb老化定时器超时处理函数
 Input           : pstMsg :消息
 Output          : None
 Return          : None
 History         :
    1.leixiantiao 00258641      2015-07-31  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_LMM_PreProcMsgGradualForbAgingTimerExpire(MsgBlock *pstMsg)
{
    VOS_UINT32                          ulTimerPara;
    VOS_UINT32                          ulIndex;
    NAS_LMM_MATCH_RESULT_ENUM_UINT32    enMatchResult  = NAS_LMM_MATCH_FAIL;
    NAS_LMM_MAIN_STATE_ENUM_UINT16      enEmmMainState = NAS_LMM_GetEmmCurFsmMS();
    NAS_MM_TA_STRU                      stTimerOutTa;
    REL_TIMER_MSG                      *pTimerMsg;

    /* 检查入参 */
    if (NAS_EMM_NULL_PTR == pstMsg)
    {
        return NAS_LMM_MSG_HANDLED;
    }

    /* 关机的时候会清掉Gradual Forb本地维护信息, 所以关机过程中收到定时器超时, 不需要处理 */
    if (EMM_MS_NULL == enEmmMainState)
    {
        return NAS_LMM_MSG_HANDLED;
    }

    /* 获取对应Opid, 此Opid在起定时器传入, 且是唯一 */
    pTimerMsg                       = (REL_TIMER_MSG *)(VOS_VOID *)pstMsg;
    ulTimerPara                     = pTimerMsg->ulPara;

    /* 根据Opid从列表中查找对应TA */
    enMatchResult = NAS_LMM_TimerParaMatchGradualForbTaList(ulTimerPara, &ulIndex);

    /* 未找到对应TA, 返回 */
    if (NAS_LMM_MATCH_SUCCESS != enMatchResult)
    {
        NAS_LMM_PUBM_LOG1_WARN("NAS_LMM_PreProcMsgGradualForbAgingTimerExpire Can't Find; Timer Para = ", ulTimerPara);
        return NAS_LMM_MSG_HANDLED;
    }

    /* 停定时器: 防止在超时消息未处理前又启动了定时器的情况, 如切换到Forb TA发起TAU被#15拒了,
       此时定时器超时, 超时消息在OSA消息队列里, 该情况下新起定时器, 处理定时器超消息时定时器时运行着的 */
    if (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsGradualForbiddenTimerRunning(ulIndex, TI_NAS_EMM_PTL_GRADUAL_FORB_TIMER))
    {
        /* 该情况下丢掉定时器超时消息 */
        return NAS_LMM_MSG_HANDLED;
    }

    /* 在剔除该TA前, 获取当前老化定时器超时TA, 用于判断是否和当前驻留的TA相同 */
    NAS_LMM_GetGradualForbTaWithIndex(ulIndex, &stTimerOutTa);

    /* 从Gradual Forb临时列表中剔除该TA */
    NAS_LMM_DelTaFromTempForbList(ulIndex);

    /* 勾出当前临时TA LIST列表 */
    NAS_EMM_SndOmGradualForbTaInfo(&stTimerOutTa, NAS_LMM_GRADUAL_FORB_TA_OPERATION_TYPE_TIMER_OUT);

    /* 通知LRRC Forb Ta列表更新 */
    NAS_EMMC_SendRrcCellSelectionReq(LRRC_LNAS_FORBTA_CHANGE);

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SendSetUECenterCnf
 Description     : 给MTC发送配置UE模式结果的函数
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         : zhaochen 00308719  2015-09-10  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_SendSetUECenterCnf( VOS_UINT32 ulRslt )
{
    LNAS_MTA_SET_UE_CENTER_CNF_STRU    *pstSetUECenterCnf;

    /* 申请DOPRA消息 */
    pstSetUECenterCnf = (VOS_VOID *) NAS_LMM_ALLOC_MSG(sizeof(LNAS_MTA_SET_UE_CENTER_CNF_STRU));
    if (NAS_LMM_NULL_PTR == pstSetUECenterCnf)
    {
        return ;
    }

    /*lint -e960*/

    /* 清空 */
    NAS_LMM_MEM_SET_S(  pstSetUECenterCnf,
                        sizeof(LNAS_MTA_SET_UE_CENTER_CNF_STRU),
                        0,
                        sizeof(LNAS_MTA_SET_UE_CENTER_CNF_STRU));

    /* 打包VOS消息头 */
    NAS_EMM_SET_MTA_MSG_HEADER((pstSetUECenterCnf),
            NAS_EMM_GET_MSG_LENGTH_NO_HEADER(LNAS_MTA_SET_UE_CENTER_CNF_STRU));

    /* 填充消息ID */
    pstSetUECenterCnf->ulMsgId       = ID_LNAS_MTA_SET_UE_CENTER_CNF;
    pstSetUECenterCnf->ulRslt        = ulRslt;

    /* 发送DOPRA消息 */
    NAS_LMM_SEND_MSG(pstSetUECenterCnf);

    /*lint +e960*/

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_RcvMtaSetUECenterReq
 Description     : AT命令设置UE模式处理函数
 Input           : pstMsg :消息
 Output          : None
 Return          : None
 History         :
    1.zhaochen 00308719      2015-09-10  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_EMM_RcvMtaSetUECenterReq(MsgBlock *pstMsg)
{
    LNAS_LMM_NV_UE_CENTER_STRU          stUECenter;
    VOS_UINT32                          ulRst;
    MTA_LNAS_SET_UE_CENTER_REQ_STRU    *pstSetUECenterReq;

    /* 检查入参 */
    if (NAS_EMM_NULL_PTR == pstMsg)
    {
        /* 入参为空，直接返回错误 */
        NAS_EMM_SendSetUECenterCnf(VOS_ERR);
        return NAS_LMM_MSG_HANDLED;
    }

    pstSetUECenterReq                   = (MTA_LNAS_SET_UE_CENTER_REQ_STRU *)(VOS_VOID *)pstMsg;

    /* 写入NV */
    NAS_LMM_MEM_SET_S(                  &stUECenter,
                                        sizeof(LNAS_LMM_NV_UE_CENTER_STRU),
                                        0,
                                        sizeof(LNAS_LMM_NV_UE_CENTER_STRU));

    stUECenter.bitOpUeCenter            = VOS_TRUE;
    stUECenter.enUeCenter               = pstSetUECenterReq->enUeCenter;

    ulRst = NAS_LMM_NvimWrite(          EN_NV_ID_UE_CENTER,
                                        &stUECenter,
                                        sizeof(LNAS_LMM_NV_UE_CENTER_STRU));

    /* 写入成功，则回复结果为成功，否则回复失败 */
    if(EN_NV_OK == ulRst)
    {
        NAS_EMM_SendSetUECenterCnf(VOS_OK);
    }

    else
    {
        NAS_EMM_SendSetUECenterCnf(VOS_ERR);
    }

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_RcvMtaSetUECenterReq
 Description     : AT命令查询UE模式处理函数
 Input           : pstMsg :消息
 Output          : None
 Return          : None
 History         :
    1.zhaochen 00308719      2015-09-10  Draft Enact

*****************************************************************************/

VOS_UINT32  NAS_EMM_RcvMtaQryUECenterReq(MsgBlock *pMsg)
{
    LNAS_MTA_QRY_UE_CENTER_CNF_STRU    *pstQryUECenterCnf;

    (VOS_VOID)pMsg;

    /* 为消息分配地址 */
    pstQryUECenterCnf = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(LNAS_MTA_QRY_UE_CENTER_CNF_STRU));
    if(NAS_LMM_NULL_PTR  == pstQryUECenterCnf)
    {
        return NAS_LMM_MSG_HANDLED;
    }

    /*lint -e960*/

    /* 清空 */
    NAS_LMM_MEM_SET_S(  pstQryUECenterCnf,
                        sizeof(LNAS_MTA_QRY_UE_CENTER_CNF_STRU),
                        0,
                        sizeof(LNAS_MTA_QRY_UE_CENTER_CNF_STRU));

    /* 打包VOS消息头 */
    NAS_EMM_SET_MTA_MSG_HEADER((pstQryUECenterCnf),
            NAS_EMM_GET_MSG_LENGTH_NO_HEADER(LNAS_MTA_QRY_UE_CENTER_CNF_STRU));


    /*设置消息体*/
    pstQryUECenterCnf->ulMsgId    = ID_LNAS_MTA_QRY_UE_CENTER_CNF;
    pstQryUECenterCnf->enResult   = VOS_OK;
    pstQryUECenterCnf->enUeCenter = NAS_LMM_GetEmmInfoUeCenter();

    /* 发送消息 */
    NAS_LMM_SEND_MSG(pstQryUECenterCnf);
    /*lint +e960*/

    return NAS_LMM_MSG_HANDLED;
}


/*****************************************************************************
 Function Name   : NAS_EMM_PreProcMsgUeCapChangeInd
 Description     : 收到rrc的ue能力变更的消息
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.yanglei 00307272      2015-10-28  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_EMM_PreProcMsgUeCapChangeInd( MsgBlock  *pMsg )
{
    VOS_UINT32                          ulRslt = NAS_LMM_MSG_DISCARD;

    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_PreProcMsgUeCapChangeInd Enter.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgUeCapChangeInd_ENUM,LNAS_ENTRY);

    (void)pMsg;
    if (NAS_EMM_NULL_PTR == pMsg)
    {
        NAS_LMM_PUBM_LOG_INFO("NAS_EMM_PreProcMsgUeCapChangeInd: Input para is null");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgUeCapChangeInd_ENUM,LNAS_NULL_PTR);

        return NAS_LMM_MSG_HANDLED;
    }
    /* 设置LTE变更标识 */
    (VOS_VOID)NAS_LMM_SetEmmInfoUeRadioCapChg(    NAS_LMM_UE_RADIO_CAP_LTE_CHG,
                                        NAS_LMM_GetEmmInfoUeRadioCapChgFlag());

    ulRslt = NAS_LMM_ProcRrcUeCapChangeIndComm();

    return ulRslt;
}
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of 子系统+模块+文件名.c */
