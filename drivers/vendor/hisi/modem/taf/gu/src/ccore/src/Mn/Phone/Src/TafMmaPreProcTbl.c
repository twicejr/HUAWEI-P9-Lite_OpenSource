/******************************************************************************

                  版权所有 (C), 2001-2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafMmaPreProcTbl.c
  版 本 号   : 初稿
  作    者   : W00176964
  生成日期   : 2013年7月9日
  最近修改   :
  功能描述   : MMA模块预处理状态表
  函数列表   :
  修改历史   :
  1.日    期   : 2013年7月9日
    作    者   : w00176964
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "TafFsm.h"
#include "TafMmaFsmMainTbl.h"
#include "TafMmaPreProcAct.h"
#include "TafMmaPreProcTbl.h"
#include "MmaMsccInterface.h"
#include "Taf_Tafm_Remote.h"
#include "MmaAppLocal.h"
#include "Taf_Status.h"
#include "TafMmaSndInternalMsg.h"
/* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-14, begin */
#if (FEATURE_ON == FEATURE_IMS)
#include "MmaMsccInterface.h"
#endif
/* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-14, end */
#include "MmaUphyInterface.h"


#include "TafMmaInterface.h"


#include "TafMmaProcUsim.h"

#include "xcc_mma_pif.h"
#include "hsm_mma_pif.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_MMA_PREPROC_TBL_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/* 预处理状态机 */
TAF_FSM_DESC_STRU                       g_stTafMmaPreFsmDesc;


/*新增状态动作处理表 */

/* 不进状态机处理的消息 动作表 */
TAF_ACT_STRU        g_astTafMmaPreProcessActTbl[]   =
{
#ifdef __PS_WIN32_RECUR__
    TAF_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      EVT_NAS_MMA_OUTSIDE_RUNNING_CONTEXT_FOR_PC_REPLAY,
                      NAS_MMA_RestoreContextData),

    TAF_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      EVT_NAS_MMA_FIXED_PART_CONTEXT,
                      NAS_MMA_RestoreFixedContextData),

#endif

    /* MMA的消息处理 */
    TAF_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      MMA_MMA_INTER_USIM_STATUS_CHANGE_IND,
                      TAF_MMA_RcvMmaInterUsimStatusChangeInd_PreProc ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      MMA_MMA_SIM_LOCK_STATUS_CHANGE_IND,
                      TAF_MMA_RcvMmaSimLockStatusChangeInd_PreProc ),

    /* OM的消息处理 */
    /* Deleted by wx270776 for OM融合, 2015-7-16, begin */

    /* Deleted by wx270776 for OM融合, 2015-7-16, end */


    TAF_ACT_TBL_ITEM( WUEPS_PID_SPY,
                      OAM_MMA_PHONE_MODE_SET_REQ,
                      TAF_MMA_RcvOmPhoneModeSetReq_PreProc),

    TAF_ACT_TBL_ITEM( CCPU_PID_CBT,
                      OAM_MMA_PHONE_MODE_SET_REQ,
                      TAF_MMA_RcvOmPhoneModeSetReq_PreProc),

    /* PHY初始化消息处理 */
    TAF_ACT_TBL_ITEM( DSP_PID_STARTUP,
                      ID_UPHY_MMA_INIT_STATUS_IND,
                      TAF_MMA_RcvUphyInitStatusInd_PreProc),

    /* USIM的消息处理 */
    /* 和hujun确认，USIM不会再报这条消息，通过PIH上报卡状态 */

    TAF_ACT_TBL_ITEM( MAPS_PIH_PID,
                      USIMM_CARDSTATUS_IND,
                      TAF_MMA_RcvPihUsimStatusInd_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_USIM,
                      USIMM_RACCESS_CNF,
                      MMA_UsimRestrictedAccessCnfMsgProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_USIM,
                      USIMM_HOTINOUT_IND,
                      MMA_ProcHotInOutUsimStatusInd),

    TAF_ACT_TBL_ITEM( WUEPS_PID_USIM,
                      USIMM_QUERYFILE_CNF,
                      MMA_USIMMaxRecordNumCnfProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_USIM,
                      USIMM_PINHANDLE_CNF,
                      MMA_UsimPINOperateMsgProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_USIM,
                      USIMM_READFILE_CNF,
                      TAF_MMA_UsimGetFileRspPreProc),

    TAF_ACT_TBL_ITEM( MAPS_PIH_PID,
                      USIMM_STKREFRESH_IND,
                      TAF_MMA_RcvPihUsimRefreshIndMsgProc),

    /* MSCC的消息处理 */
    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_RSSI_IND,
                      TAF_MMA_RcvMsccRssiInd_PreProc),
    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_LMM_CELL_SIGN_INFO_REPORT_IND,
                      TAF_MMA_RcvMsccLmmCellSignReportInd_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_MM_INFO_IND,
                      Sta_MmInfo),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_SYSTEM_ACQUIRE_END_IND,
                      TAF_MMA_RcvMsccSystemAcquireEndInd_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_SYSTEM_ACQUIRE_START_IND,
                      TAF_MMA_RcvMsccSystemAcquireStartInd_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_EOPLMN_SET_CNF,
                      TAF_MMA_RcvMsccEOPlmnSetCnf),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_UMTS_CIPHER_INFO_IND,
                      MMA_SaveWCipherInfo),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_GPRS_CIPHER_INFO_IND,
                      MMA_SaveGCipherInfo),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_AC_INFO_CHANGE_IND,
                      TAF_MMA_RcvMsccAcInfoChangeInd),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_SERVICE_STATUS_IND,
                      Sta_ServiceStatusInd),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_3GPP_SYS_INFO_IND,
                      TAF_MMA_Rcv3gppMsccSysInfoInd),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_CAMP_ON_IND,
                      TAF_MMA_RcvMsccCampOnInd_PreProc),
    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_RF_AVAILABLE_IND,
                      TAF_MMA_RcvMsccRfAvailableInd_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_DATATRAN_ATTRI_IND,
                      Sta_DataTranAttri),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_COVERAGE_AREA_IND,
                      Sta_CoverageAreaInd),

    /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, begin */
    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_REG_RESULT_IND,
                      TAF_MMA_RcvMsccRegResultInd_PreProc),
    /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, end */

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_NETWORK_CAPABILITY_INFO_IND,
                      TAF_MMA_RcvMsccNetworkCapabilityInfoInd_PreProc ),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_NET_SCAN_CNF,
                      TAF_MMA_RcvMsccNetScanCnf_PreProc ),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_ABORT_NET_SCAN_CNF,
                      TAF_MMA_RcvMsccAbortNetScanCnf_PreProc ),


    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_EPLMN_INFO_IND,
                      TAF_MMA_RcvMsccEplmnInfoInd_PreProc ),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_USIM_AUTH_FAIL_IND,
                      TAF_MMA_RcvMsccUsimAuthFailInd_PreProc ),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_CS_SERVICE_CONN_STATUS_IND,
                      TAF_MMA_RcvMsccCsServiceConnStatusInd_PreProc ),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_SRV_REJ_IND,
                      TAF_MMA_RcvMsccServRejInd_PreProc ),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_DETACH_IND,
                      TAF_MMA_RcvMsccDetachInd_PreProc ),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_ATTACH_CNF,
                      TAF_MMA_RcvMsccAttachCnf_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_DPLMN_SET_CNF,
                      TAF_MMA_RcvMsccDplmnSetCnf_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_SRCHED_PLMN_INFO_IND,
                      TAF_MMA_RcvMsccSrchedPlmnInfoInd_PreProc ),

    /* Added by s00261364 for L-C互操作项目, 2014-1-26, begin */
    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_ACQ_CNF,
                      TAF_MMA_RcvMsccAcqCnf_PreProc ),

#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_ACQ_IND,
                      TAF_MMA_RcvMsccAcqInd_PreProc ),
#endif

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_REG_CNF,
                      TAF_MMA_RcvMsccRegCnf_PreProc ),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_POWER_SAVE_CNF,
                      TAF_MMA_RcvMsccPowerSaveCnf_PreProc ),
    /* Added by s00261364 for L-C互操作项目, 2014-1-26, end */

    /* Add by j00174725 for K3V3 多模多天线特性, 2014-06-16, Begin */
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_PS_SERVICE_CONN_STATUS_IND,
                      TAF_MMA_RcvMsccPsServiceConnStatusInd_PreProc ),
#endif
    /* Add by j00174725 for K3V3 多模多天线特性, 2014-06-16, End */

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_PREF_PLMN_QUERY_CNF,
                      TAF_MMA_RcvMsccPrefPlmnQueryCnf_PreProc ),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_PREF_PLMN_SET_CNF,
                      TAF_MMA_RcvMsccPrefPlmnSetCnf_PreProc ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_SRV_ACQ_REQ,
                      TAF_MMA_RcvTafSrvAcqReq_PreProc),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_WAIT_MSCC_SRV_ACQ_CNF,
                      TAF_MMA_RcvTiWaitMsccSrvAcqCnfExpired_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_SRV_ACQ_CNF,
                      TAF_MMA_RcvMsccSrvAcqCnf_PreProc),

    /* 收到at的at+cops=0的预处理 */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_PLMN_AUTO_RESEL_REQ,
                      TAF_MMA_RcvPlmnAutoReselReq_PreProc),

    /* 收到at指定搜网请求的预处理 */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_PLMN_SPECIAL_SEL_REQ,
                      TAF_MMA_RcvPlmnSpecialSelReq_PreProc),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_WAIT_MSCC_PLMN_AUTO_RESEL_CNF,
                      TAF_MMA_RcvTiWaitMsccPlmnAutoSelCnfExpired_PreProc),

     TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_WAIT_MSCC_PLMN_SPECIAL_SEL_CNF,
                      TAF_MMA_RcvTiWaitMsccSpecPlmnSelCnfExpired_PreProc),

     TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_WAIT_MSCC_ABORT_SPEC_PLMN_SEL_CNF,
                      TAF_MMA_RcvTiWaitMsccAbortSpecPlmnSelCnfExpired_PreProc),

     TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_WAIT_MSCC_ABORT_PLMN_LIST_CNF,
                      TAF_MMA_RcvTiWaitMsccPlmnListAbortCnfExpired_PreProc),
    /* 收到at列表搜网请求的预处理 */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_PLMN_LIST_REQ,
                      TAF_MMA_RcvAtPlmnList_PreProc),

    /* 收到at syscfg请求的预处理 */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_SYS_CFG_SET_REQ,
                      TAF_MMA_RcvSysCfgSetReq_PreProc),


    /* AT的消息处理 */
    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_MSG_MMA_USIM_RESTRICTED_ACCESS,
                      MMA_UsimRestrictedAccessCommandProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_MSG_PARA_READ,
                      TAF_MMA_RcvAtParaReadReq_PreProc),





    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_SIM_INSERT_REQ,
                      TAF_MMA_RcvSimInsertReq_PreProc),



    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_MSG_MMA_USIM_INFO,
                      MMA_DbProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_MSG_MMA_CPNN_INFO,
                      MMA_DbProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_CIPHER_QRY_REQ,
                      TAF_MMA_RcvCipherQryReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_LOCATION_INFO_QRY_REQ,
                      TAF_MMA_RcvLocInfoQryReq_PreProc),



    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_AC_INFO_QRY_REQ,
                      TAF_MMA_RcvAcInfoQry_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_COPN_INFO_QRY_REQ,
                      TAF_MMA_RcvCopnInfoQry_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_EOPLMN_SET_REQ,
                      TAF_MMA_RcvEOPlmnSetReq_PreProc),
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_SPN_QRY_REQ,
                      TAF_MMA_RcvSpnQryReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_MMPLMNINFO_QRY_REQ,
                      TAF_MMA_RcvMMPlmnInfoQryReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_LAST_CAMP_PLMN_QRY_REQ,
                      TAF_MMA_RcvPlmnQryReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_EOPLMN_QRY_REQ,
                      TAF_MMA_RcvEOPlmnQryReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_NET_SCAN_REQ,
                      TAF_MMA_RcvNetScanReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_NET_SCAN_ABORT_REQ,
                      TAF_MMA_RcvAbortNetScanReq_PreProc),
    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_MSG_MMA_COPS_FORMAT_TYPE_SET_REQ,
                      TAF_MMA_RcvCopsFormatTypeSetReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_MSG_MMA_USIM_STUB_SET_REQ,
                      TAF_MMA_RcvUsimStubSetReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_MSG_MMA_REFRESH_STUB_SET_REQ,
                      TAF_MMA_RcvRefreshStubSetReq_PreProc),
    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_MSG_MMA_AUTO_RESEL_STUB_SET_REQ,
                      TAF_MMA_RcvAutoReselStubSetReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_ATTACH_STATUS_QRY_REQ,
                      TAF_MMA_RcvAttachStatusQry_PreProc),





    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_PREF_PLMN_TYPE_SET_REQ,
                      TAF_MMA_RcvPrefPlmnTypeSetReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_MT_POWER_DOWN_REQ,
                      TAF_MMA_RcvPowerDownReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_CERSSI_SET_REQ,
                      TAF_MMA_RcvCerssiSetReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_CERSSI_QRY_REQ,
                      TAF_MMA_RcvCerssiQryReq_PreProc),


    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_MSG_MMA_OP_PIN_REQ,
                      MMA_PhoneProc),


    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_MSG_MMA_ME_PERSONAL_REQ,
                      MMA_PhoneProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_MSG_MMA_SET_PIN,
                      MMA_SetCPin),

    /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, begin */
#if (FEATURE_ON == FEATURE_IMS)
    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_IMS_VOICE_CAP_IND,
                      TAF_MMA_RcvMsccImsVoiceCapInd_PreProc),

    /* 定时处理已经下移到MSCC模块，这里删除定时器处理逻辑 */
#endif
    /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, end */

    /* 定时器消息 */
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TAF_MMA,
                      MMA_TimeExpired),

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    TAF_ACT_TBL_ITEM( UEPS_PID_MTC,
                      ID_MTC_MMA_OTHER_MODEM_INFO_NOTIFY,
                      TAF_MMA_RcvMtcOtherModemInfoNotify_PreProc),
    TAF_ACT_TBL_ITEM( UEPS_PID_MTC,
                      ID_MTC_MMA_NCELL_INFO_IND,
                      TAF_MMA_RcvMtcNcellInfoInd_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_MTC,
                      ID_MTC_MMA_PS_TRANSFER_IND,
                      TAF_MMA_RcvMtcPsTransferInd_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_MTC,
                      ID_MTC_MMA_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY,
                      TAF_MMA_RcvMtcOtherModemDplmnNplmnInfoNotify_PreProc),

#endif



/* TAF的消息处理 */

    /* Added by w00167002 for L-C互操作项目, 2014-2-14, begin */

    /* 收到模式设置请求 */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_PHONE_MODE_SET_REQ,
                      TAF_MMA_ProcTafPhoneModeSetReq_PreProc),
    /* Added by w00167002 for L-C互操作项目, 2014-2-14, end */

    /* 收到AT的cfun查询请求 */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_PHONE_MODE_QRY_REQ,
                      TAF_MMA_RcvQryPhoneModeReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_SYSCFG_QRY_REQ,
                      TAF_MMA_RcvMmaQrySyscfgReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_SYSCFG_TEST_REQ,
                      TAF_MMA_RcvMmaTestSyscfgReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_CSNR_QRY_REQ,
                      TAF_MMA_RcvMmaCsnrQryReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_CSQ_QRY_REQ,
                      TAF_MMA_RcvMmaCsqQryReq_PreProc),
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_CSQLVL_QRY_REQ,
                      TAF_MMA_RcvMmaCsqLvlQryReq_PreProc),



    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_ACCESS_MODE_QRY_REQ,
                      TAF_MMA_RcvAccessModeQry_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_COPS_QRY_REQ,
                      TAF_MMA_RcvCopsQry_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_REG_STATE_QRY_REQ,
                      TAF_MMA_RcvRegStateQryReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_AUTO_ATTACH_QRY_REQ,
                      TAF_MMA_RcvMmaQryAutoAttachReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_SYSINFO_QRY_REQ,
                      TAF_MMA_RcvSysInfoQryReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_ANTENNA_INFO_QRY_REQ,
                      TAF_MMA_RcvAntennaInfoQryReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_HOME_PLMN_QRY_REQ,
                      TAF_MMA_RcvApHplmnQryReq_PreProc),


    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_DPLMN_SET_REQ,
                      TAF_MMA_RcvDplmnSetReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_DPLMN_QRY_REQ,
                      TAF_MMA_RcvDplmnQryReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_USER_SRV_STATE_QRY_REQ,
                      TAF_MMA_RcvUserSrvStateQry_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_POWER_ON_AND_REG_TIME_QRY_REQ,
                      TAF_MMA_RcvApPwrOnAndRegTimeQryReq_PreProc),



    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_AUTO_ATTACH_QRY_REQ,
                      TAF_MMA_RcvMmaQryAutoAttachReq_PreProc),

    /* Added by s00261364 for L-C互操作项目, 2014-1-26, begin */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_BATTERY_CAPACITY_QRY_REQ,
                      TAF_MMA_RcvBatteryCapacityQry_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_HAND_SHAKE_QRY_REQ,
                      TAF_MMA_RcvHandShakeQry_PreProc),
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_ACQ_BEST_NETWORK_REQ,
                      TAF_MMA_RcvMmaAcqReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_REG_REQ,
                      TAF_MMA_RcvMmaRegReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_POWER_SAVE_REQ,
                      TAF_MMA_RcvMmaPowerSaveReq_PreProc),
    /* Added by s00261364 for L-C互操作项目, 2014-1-26, end */

#if (FEATURE_ON == FEATURE_IMS)
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_IMS_SRV_INFO_NOTIFY,
                      TAF_MMA_RcvTafImsSrvInfoNotify_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_IMS_SWITCH_QRY_REQ,
                      TAF_MMA_RcvTafImsSwitchQryReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_VOICE_DOMAIN_SET_REQ,
                      TAF_MMA_RcvTafVoiceDomainSetReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_VOICE_DOMAIN_QRY_REQ,
                      TAF_MMA_RcvTafVoiceDomainQryReq_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_IMS_SWITCH_STATE_IND,
                      TAF_MMA_RcvMsccImsSwitchStateInd_PreProc ),

#endif


    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_PREF_PLMN_SET_REQ,
                      TAF_MMA_RcvMmaPrefPlmnSetReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_PREF_PLMN_TEST_REQ,
                      TAF_MMA_RcvMmaPrefPlmnTestReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_PREF_PLMN_QUERY_REQ,
                      TAF_MMA_RcvMmaPrefPlmnQueryReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MSG_MMA_EONS_UCS2_REQ,
                      TAF_MMA_RcvAtEonsUcs2Req_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_QUICKSTART_SET_REQ,
                      TAF_MMA_RcvMmaSetCqstReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_QUICKSTART_QRY_REQ,
                      TAF_MMA_RcvMmaQryQuickStartReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_CRPN_QRY_REQ,
                      TAF_MMA_RcvMmaQryCrpnReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_CMM_SET_REQ,
                      TAF_MMA_RcvMmaSetCmmReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_AUTO_ATTACH_SET_REQ,
                      TAF_MMA_RcvMmaSetAutoAttachReq_PreProc),


    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_AUTO_ATTACH_SET_REQ,
                      TAF_MMA_RcvMmaSetAutoAttachReq_PreProc),

	
#if (FEATURE_ON == FEATURE_CSG)
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_CSG_LIST_SEARCH_REQ,
                      TAF_MMA_RcvTafCsgListSearchReq_PreProc),
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_WAIT_MSCC_CSG_LIST_SEARCH_CNF,
                      TAF_MMA_RcvTiWaitMsccCsgListSearchCnfExpired_PreProc),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_WAIT_MSCC_CSG_LIST_ABORT_CNF,
                      TAF_MMA_RcvTiWaitMsccCsgListAbortCnfExpired_PreProc),
#endif
    /* Added by b00269685 for L-C互操作项目, 2014-3-4, begin */
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_WAIT_MSCC_ACQ_CNF,
                      TAF_MMA_RcvTiWaitMsccAcqCnfExpired_PreProc),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_WAIT_MSCC_REG_CNF,
                      TAF_MMA_RcvTiWaitMsccRegCnfExpired_PreProc),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_WAIT_MSCC_POWER_SAVE_CNF,
                      TAF_MMA_RcvTiWaitMsccPowerSaveExpired_PreProc),
    /* Added by b00269685 for L-C互操作项目, 2014-3-4, end */

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)



    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_1X_SYSTEM_SERVICE_INFO_IND,
                      TAF_MMA_RcvMscc1xSystemServiceInfoInd_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_SYNC_SERVICE_AVAIL_IND,
                      TAF_MMA_RcvMsccSyncServiceAvailInd_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_CDMA_MO_CALL_START_NTF,
                      TAF_MMA_RcvTafCdmaMoCallStartNtf_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_CDMA_MO_CALL_END_NTF,
                      TAF_MMA_RcvTafCdmaMoCallEndNtf_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_CDMA_MO_CALL_SUCCESS_NTF,
                      TAF_MMA_RcvTafCdmaMoCallSuccessNtf_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_CDMA_CALL_REDIAL_SYSTEM_ACQUIRE_NTF,
                      TAF_MMA_RcvTafCdmaCallRedialSystemAcquireNtf),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_CDMA_LOCINFO_QRY_REQ,
                      TAF_MMA_RcvAtQueryCLocInfo_PreProc),


    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_CDMA_FREQ_LOCK_SET_REQ,
                      TAF_MMA_RcvSetCFreqLock_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_CDMA_FREQ_LOCK_QRY_REQ,
                      TAF_MMA_RcvQueryCFreqLock_PreProc),


    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_QUIT_CALLBACK_SET_REQ,
                      TAF_MMA_RcvQuitCallBackInd_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_CSIDLIST_SET_REQ,
                      TAF_MMA_RcvSetCSidListReq_PreProc),
					  

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_1X_EMC_CALL_BACK_QRY_REQ,
                      TAF_MMA_RcvQryEmcCallBackMode_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_CDMACSQ_SET_REQ,
                      TAF_MMA_ProcCdmaCsqSetReq_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_CDMACSQ_SET_CNF,
                      TAF_MMA_RcvMsccCdmaCsqSetCnf_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_CDMACSQ_QRY_REQ,
                      TAF_MMA_RcvCdmaCsqQryReq_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_CDMACSQ_SIGNAL_QUALITY_IND,
                      TAF_MMA_RcvMsccCdmaCsqInd_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_HDR_CSQ_SET_REQ,
                      TAF_MMA_ProcHdrCsqSetReq_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_HDR_CSQ_SET_CNF,
                      TAF_MMA_RcvMsccHdrCsqSetCnf_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_HDR_CSQ_QUALITY_IND,
                      TAF_MMA_RcvMsccHdrCsqInd_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_HDR_CSQ_QRY_SETTING_REQ,
                      TAF_MMA_RcvHdrCsqQryReq_PreProc),



    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_DATA_CALL_REDIAL_SYS_ACQ_IND,
                      TAF_MMA_RcvMsccDataCallRedialSysAcqInd_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_CURR_SID_NID_QRY_REQ,
                      TAF_MMA_RcvQryCurrSidNid_PreProc),



    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_HRPD_SERVICE_STATUS_IND,
                      TAF_MMA_RcvMsccHrpdServiceStatusInd_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_HRPD_OVERHEAD_MSG_IND,
                      TAF_MMA_RcvMsccHrpdOverheadMsgInd_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_HRPD_SYS_ACQ_CNF,
                      TAF_MMA_RcvMsccHrpdSysAcqCnf_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_1X_SYSTEM_TIME_IND,
                      TAF_MMA_RcvMscc1xSystemTimeInd_PreProc),



    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_1XCHAN_SET_REQ,
                      TAF_MMA_Rcv1xChanSetReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_1XCHAN_QUERY_REQ,
                      TAF_MMA_RcvQuery1xChanReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_CVER_QUERY_REQ,
                      TAF_MMA_RcvQueryCVerReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_GETSTA_QUERY_REQ,
                      TAF_MMA_RcvQueryStateReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_CHIGHVER_QUERY_REQ,
                      TAF_MMA_RcvQueryHighVerReq_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_HANDSET_INFO_QRY_CNF,
                      TAF_MMA_RcvMsccHandsetInfoQryCnf_PreProc),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_WAIT_MSCC_STATE_QUERY_CNF,
                      TAF_MMA_RcvTiWaitMsccStateQryCnfExpired_PreProc),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_WAIT_MSCC_CHVER_QUERY_CNF,
                      TAF_MMA_RcvTiWaitMsccHVerQryCnfExpired_PreProc),

    /*可维可测消息 hrpd info msg from hsd*/

    TAF_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_HSM_MMA_HRPD_SYS_INFO_IND,
                      TAF_MMA_RcvHsmHrpdSysInfoInd_PreProc ),

    TAF_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_HSM_MMA_HARDWARE_SYS_INFO_IND,
                      TAF_MMA_RcvHsmHardwareSysInfoInd_PreProc ),

    TAF_ACT_TBL_ITEM( MSP_PID_DIAG_APP_AGENT,
                      ID_OM_NAS_MMA_CDMA_STATUS_INFO_REPORT_REQ,
                      TAF_MMA_RcvOmCdmaStatusInfoReportReq_PreProc ),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_FREQUENCE_OF_QRY_CDMA_SYS_INFO,
                      TAF_MMA_RcvTiCdmaSysInfoReport_PreProc),


    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_1X_SID_NID_IND,
                      TAF_MMA_RcvMscc1XSidNidInd_PreProc ),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_SET_CSIDLIST_CNF,
                      TAF_MMA_RcvMsccSetCSidListCnf ),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_1X_EMC_CALL_BACK_IND,
                      TAF_MMA_RcvMscc1XEmcCallBackNtf_PreProc ),

    TAF_ACT_TBL_ITEM( UEPS_PID_XCC,
                      ID_XCC_MMA_1X_CALL_STATE_IND,
                      TAF_MMA_RcvXcc1xCallStateInd_PreProc ),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_1X_UE_STATUS_IND,
                      TAF_MMA_RcvMsccUeStateInd_PreProc),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_CS_SERVICE_STATUS_DELAY_REPORT_IN_CL_MODE,
                      TAF_MMA_RcvTiCLDelayRptCsServiceStatusExpired_PreProc),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_PS_SERVICE_STATUS_DELAY_REPORT_IN_CL_MODE,
                      TAF_MMA_RcvTiCLDelayRptPsServiceStatusExpired_PreProc),

#endif

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_CFPLMN_SET_REQ,
                      TAF_MMA_RcvCFPlmnSetReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_CFPLMN_QUERY_REQ,
                      TAF_MMA_RcvCFPlmnQueryReq_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_CFPLMN_SET_CNF,
                      TAF_MMA_RcvMsccCFPlmnSetCnf_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_CFPLMN_QUERY_CNF,
                      TAF_MMA_RcvMsccCFPlmnQueryCnf_PreProc),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_WAIT_MSCC_CFPLMN_SET_CNF,
                      TAF_MMA_RcvTiWaitMsccCFPlmnSetCnfExpired_PreProc),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_WAIT_MSCC_CFPLMN_QUERY_CNF,
                      TAF_MMA_RcvTiWaitMsccCFPlmnQueryCnfExpired_PreProc),


    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_WAIT_MSCC_PREF_CPOL_SET_CNF,
                      TAF_MMA_RcvTiWaitMsccPrefPlmnSetCnfExpired_PreProc),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_WAIT_MSCC_PREF_CPOL_QUERY_CNF,
                      TAF_MMA_RcvTiWaitMsccPrefPlmnQueryCnfExpired_PreProc),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_WAIT_MSCC_PREF_CPOL_TEST_CNF,
                      TAF_MMA_RcvTiWaitMsccPrefPlmnTestCnfExpired_PreProc),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_WAIT_CS_SERVICE_DISCONN,
                      TAF_MMA_RcvCSServiceDisconnExpired_PreProc),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_WAIT_READ_SIM_FILES,
                      TAF_MMA_RcvWaitReadSimFilesExpired_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_PS_RAT_TYPE_NTF,
                      TAF_MMA_RcvTafPsRatTypeNtf_PreProc),


    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                       ID_TAF_MMA_DETACH_REQ,
                       TAF_MMA_RcvDetachReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                       ID_TAF_MMA_ATTACH_REQ,
                       TAF_MMA_RcvAttachReq_PreProc),


    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_DELAY_REPORT_SERVICE_STATUS,
                      TAF_MMA_RcvDelayReportServiceStatusExpired_PreProc),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_DELAY_RPT_APS_CL_NO_SERVICE,
                      TAF_MMA_RcvDelayReportCLNoServiceExpired_PreProc),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_DELAY_RPT_APS_DO_NO_SERVICE,
                      TAF_MMA_RcvDelayReportDONoServiceExpired_PreProc),

};

/* 不进状态机处理的消息 状态表 */
TAF_STA_STRU        g_astTafMmaPreProcessFsmTbl[]   =
{
    TAF_STA_TBL_ITEM( TAF_MMA_MAIN_STA_PREPROC,
                      g_astTafMmaPreProcessActTbl )
};

/*****************************************************************************
 函 数 名  : TAF_MMA_GetPreProcessStaTblSize
 功能描述  : 获取预处理状态机的大小
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32:预处理状态机的大小
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月9日
    作    者   : W00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_MMA_GetPreProcessStaTblSize( VOS_VOID  )
{
    return (sizeof(g_astTafMmaPreProcessFsmTbl)/sizeof(TAF_STA_STRU));
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetPreFsmDescAddr
 功能描述  : 获取预处理状态机的描述表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_FSM_DESC_STRU:指向预处理状态机的描述表
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月9日
    作    者   : zhoujun 40661
    修改内容   : 新生成函数

*****************************************************************************/
TAF_FSM_DESC_STRU * TAF_MMA_GetPreFsmDescAddr(VOS_VOID)
{
    return (&g_stTafMmaPreFsmDesc);
}




/*****************************************************************************
  3 函数实现
*****************************************************************************/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

