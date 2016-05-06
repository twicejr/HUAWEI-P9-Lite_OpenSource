/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMsccPreProcTbl.c
  版 本 号   : 初稿
  作    者   : y00245242
  生成日期   : 2015年01月26日
  功能描述   : MSCC module预处理事件处理
  函数列表   :
  修改历史   :
  1.日    期   : 2015年01月26日
    作    者   : y00245242
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "MsccMmcInterface.h"
#include "MmaMsccInterface.h"
#if (FEATURE_ON == FEATURE_IMS)
#include "ImsaMsccInterface.h"
#endif
#include "NasMsccFsmMainTbl.h"
#include "NasMsccPreProcAct.h"
#include "NasMsccPreProcTbl.h"
#include "NasMsccTimerMgmt.h"

#include "hsd_mscc_pif.h"
// todo: delete after had_mma_pif.h had been refractured

#include "NasMsccMntn.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_NAS_MSCC_PRE_PROC_TBL_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
NAS_FSM_DESC_STRU                       g_stNasMsccPreFsmDesc;

/* 预处理的消息动作表 */
NAS_ACT_STRU g_astNasMsccPreProActTbl[] =
{

    NAS_ACT_TBL_ITEM(WUEPS_PID_MMC,
                     ID_MMC_MSCC_SYS_INFO_IND,
                     NAS_MSCC_RcvMmcSysInfoInd_PreProc),

    NAS_ACT_TBL_ITEM(WUEPS_PID_MMC,
                     ID_MMC_MSCC_REG_RESULT_IND,
                     NAS_MSCC_RcvMmcRegResultInd_PreProc),

    NAS_ACT_TBL_ITEM(WUEPS_PID_MMC,
                     ID_MMC_MSCC_SERVICE_STATUS_IND,
                     NAS_MSCC_RcvMmcServiceStatusInd_PreProc),

    NAS_ACT_TBL_ITEM(WUEPS_PID_MMC,
                     ID_MMC_MSCC_RSSI_IND,
                     NAS_MSCC_RcvMmcPhoneRssiInd_PreProc),

    NAS_ACT_TBL_ITEM(WUEPS_PID_MMC,
                     ID_MMC_MSCC_MM_INFO_IND,
                     NAS_MSCC_RcvMmcStaMmInfo_PreProc),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_PLMN_SELE_START_IND,
                      NAS_MSCC_RcvMmcPlmnSelectStartInd_PreProc),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_EOPLMN_SET_CNF,
                      NAS_MSCC_RcvMmcEOPlmnSetCnf_PreProc),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_UMTS_CIPHER_INFO_IND,
                      NAS_MSCC_RcvMmcWCipherInfo_PreProc),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_GPRS_CIPHER_INFO_IND,
                      NAS_MSCC_RcvMmcGCipherInfo_PreProc),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_AC_INFO_CHANGE_IND,
                      NAS_MSCC_RcvMmcAcInfoChangeInd_PreProc),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_CAMP_ON_IND,
                      NAS_MSCC_RcvMmcCampOnInd_PreProc),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_RF_AVAILABLE_IND,
                      NAS_MSCC_RcvMmcRfAvailableInd_PreProc),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_DATATRAN_ATTRI_IND,
                      NAS_MSCC_RcvMmcStaDataTranAttri_PreProc),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_COVERAGE_AREA_IND,
                      NAS_MSCC_RcvMmcStaCoverageAreaInd_PreProc),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_NET_SCAN_CNF,
                      NAS_MSCC_RcvMmcNetScanCnf_PreProc ),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_ABORT_NET_SCAN_CNF,
                      NAS_MSCC_RcvMmcAbortNetScanCnf_PreProc ),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_EPLMN_INFO_IND,
                      NAS_MSCC_RcvMmcEplmnInfoInd_PreProc ),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_USIM_AUTH_FAIL_IND,
                      NAS_MSCC_RcvMmcUsimAuthFailInd_PreProc ),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_CS_SERVICE_CONN_STATUS_IND,
                      NAS_MSCC_RcvMmcCsServiceConnStatusInd_PreProc ),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_DETACH_IND,
                      NAS_MSCC_RcvMmcDetachInd_PreProc ),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_ATTACH_CNF,
                      NAS_MSCC_RcvMmcAttachCnf_PreProc),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_ACQ_CNF,
                      NAS_MSCC_RcvMmcAcqCnf_PreProc),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_REG_CNF,
                      NAS_MSCC_RcvMmcRegCnf_PreProc),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_POWER_SAVE_CNF,
                      NAS_MSCC_RcvMmcPowerSaveCnf_PreProc),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_DETACH_CNF,
                      NAS_MSCC_RcvMmcDetachCnf_PreProc),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_PLMN_LIST_CNF,
                      NAS_MSCC_RcvMmcPlmnListCnf_PreProc),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_SRCHED_PLMN_INFO_IND,
                      NAS_MSCC_RcvMmcSrchedPlmnInfo_PreProc),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_PLMN_LIST_REJ,
                      NAS_MSCC_RcvMmcPlmnListRej_PreProc),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_PLMN_SPECIAL_SEL_CNF,
                      NAS_MSCC_RcvMmcPlmnSpecialSelCnf_PreProc),


    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_PLMN_LIST_ABORT_CNF,
                      NAS_MSCC_RcvMmcPlmnListAbortCnf_PreProc),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_SPEC_PLMN_SEARCH_ABORT_CNF,
                      NAS_MSCC_RcvMmcSpecPlmnSearchAbortCnf_PreProc),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_PLMN_SPECIAL_SEL_REJ,
                      NAS_MSCC_RcvMmcPlmnSpecialSelRej_PreProc),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_PLMN_RESEL_CNF,
                      NAS_MSCC_RcvMmcPlmnReselCnf_PreProc),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_NETWORK_CAPABILITY_INFO_IND,
                      NAS_MSCC_RcvMmcNetworkCapabilityInfoInd_PreProc),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_LMM_CELL_SIGN_INFO_REPORT_IND,
                      NAS_MSCC_RcvMmcMsgLmmCellSignInfoInd_PreProc),

    NAS_ACT_TBL_ITEM(WUEPS_PID_MMA,
                     ID_MMA_MSCC_SIGN_REPORT_REQ,
                     NAS_MSCC_RcvMmaSignReportReq_PreProc),

    NAS_ACT_TBL_ITEM(WUEPS_PID_MMA,
                     ID_MMA_MSCC_MODE_CHANGE_REQ,
                     NAS_MSCC_RcvMmaModeChangeReq_PreProc),

    NAS_ACT_TBL_ITEM(WUEPS_PID_MMA,
                     ID_MMA_MSCC_ATTACH_REQ,
                     NAS_MSCC_RcvMmaAttachReq_PreProc),

    NAS_ACT_TBL_ITEM(WUEPS_PID_MMA,
                     ID_MMA_MSCC_DETACH_REQ,
                     NAS_MSCC_RcvMmaDetachReq_PreProc),

    NAS_ACT_TBL_ITEM(WUEPS_PID_MMA,
                     ID_MMA_MSCC_PLMN_LIST_REQ,
                     NAS_MSCC_RcvMmaPlmnListReq_PreProc),

    NAS_ACT_TBL_ITEM(WUEPS_PID_MMA,
                     ID_MMA_MSCC_PLMN_LIST_ABORT_REQ,
                     NAS_MSCC_RcvMmaPlmnListAbortReq_PreProc),

    NAS_ACT_TBL_ITEM(WUEPS_PID_MMA,
                     ID_MMA_MSCC_PLMN_USER_RESEL_REQ,
                     NAS_MSCC_RcvMmaUserReselReq_PreProc),

    NAS_ACT_TBL_ITEM(WUEPS_PID_MMA,
                     ID_MMA_MSCC_PLMN_SPECIAL_REQ,
                     NAS_MSCC_RcvMmaUserSpecPlmnSearch_PreProc),



    NAS_ACT_TBL_ITEM(WUEPS_PID_MMA,
                     ID_MMA_MSCC_SPEC_PLMN_SEARCH_ABORT_REQ,
                     NAS_MSCC_RcvMmaSpecPlmnSearchAbortReq_PreProc),

    NAS_ACT_TBL_ITEM(WUEPS_PID_MMA,
                     ID_MMA_MSCC_OM_MAINTAIN_INFO_IND,
                     NAS_MSCC_RcvMmaOmMaintainInfoInd_PreProc),

    NAS_ACT_TBL_ITEM(WUEPS_PID_MMA,
                     ID_MMA_MSCC_UPDATE_UPLMN_NTF,
                     NAS_MSCC_RcvMmaUpdateUplmnNotify_PreProc),

    NAS_ACT_TBL_ITEM(WUEPS_PID_MMA,
                     ID_MMA_MSCC_EOPLMN_SET_REQ,
                     NAS_MSCC_RcvMmaEOPlmnSetReq_PreProc),

    NAS_ACT_TBL_ITEM(WUEPS_PID_MMA,
                     ID_MMA_MSCC_NET_SCAN_REQ,
                     NAS_MSCC_RcvMmaNetScanReq_PreProc),

    NAS_ACT_TBL_ITEM(WUEPS_PID_MMA,
                     ID_MMA_MSCC_ABORT_NET_SCAN_REQ,
                     NAS_MSCC_RcvMmaAbortNetScanReq_PreProc),


    NAS_ACT_TBL_ITEM(WUEPS_PID_MMA,
                     ID_MMA_MSCC_ACQ_REQ,
                     NAS_MSCC_RcvMmaAcqReq_PreProc),

    NAS_ACT_TBL_ITEM(WUEPS_PID_MMA,
                     ID_MMA_MSCC_REG_REQ,
                     NAS_MSCC_RcvMmaRegReq_PreProc),

    NAS_ACT_TBL_ITEM(WUEPS_PID_MMA,
                     ID_MMA_MSCC_POWER_SAVE_REQ,
                     NAS_MSCC_RcvMmaPowerSaveReq_PreProc),

    NAS_ACT_TBL_ITEM(WUEPS_PID_MMA,
                     ID_MMA_MSCC_PREF_PLMN_SET_REQ,
                     NAS_MSCC_RcvMmaPrefPlmnSetReq_PreProc),

    NAS_ACT_TBL_ITEM(WUEPS_PID_MMA,
                     ID_MMA_MSCC_PREF_PLMN_QUERY_REQ,
                     NAS_MSCC_RcvMmaPrefPlmnQueryReq_PreProc),

    NAS_ACT_TBL_ITEM(WUEPS_PID_MMC,
                     ID_MMC_MSCC_PREF_PLMN_QUERY_CNF,
                     NAS_MSCC_RcvMmcPrefPlmnQueryCnf_PreProc),

    NAS_ACT_TBL_ITEM(WUEPS_PID_MMC,
                     ID_MMC_MSCC_PREF_PLMN_SET_CNF,
                     NAS_MSCC_RcvMmcPrefPlmnSetCnf_PreProc),

    NAS_ACT_TBL_ITEM(WUEPS_PID_MMA,
                     ID_MMA_MSCC_CFPLMN_SET_REQ,
                     NAS_MSCC_RcvMmaCFPlmnSetReq_PreProc),

    NAS_ACT_TBL_ITEM(WUEPS_PID_MMA,
                     ID_MMA_MSCC_CFPLMN_QUERY_REQ,
                     NAS_MSCC_RcvMmaCFPlmnQueryReq_PreProc),

    NAS_ACT_TBL_ITEM(WUEPS_PID_MMC,
                     ID_MMC_MSCC_CFPLMN_SET_CNF,
                     NAS_MSCC_RcvMmcCFPlmnSetCnf_PreProc),

    NAS_ACT_TBL_ITEM(WUEPS_PID_MMC,
                     ID_MMC_MSCC_CFPLMN_QUERY_CNF,
                     NAS_MSCC_RcvMmcCFPlmnQueryCnf_PreProc),

    NAS_ACT_TBL_ITEM(WUEPS_PID_MMA,
                     ID_MMA_MSCC_SDT_CONNECTED_IND,
                     NAS_MSCC_RcvMmaSdtConnedInd_PreProc),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_SRV_REJ_IND,
                      NAS_MSCC_RcvMmcServRejInd_PreProc),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_PREF_PLMN_INFO_IND,
                      NAS_MSCC_RcvMmcPrefPlmnInfoInd_PreProc),

#if (FEATURE_ON == FEATURE_CSG)
    NAS_ACT_TBL_ITEM(WUEPS_PID_MMA,
                     ID_MMA_MSCC_CSG_LIST_SEARCH_REQ,
                     NAS_MSCC_RcvMmaCsgListSearchReq_PreProc),

    NAS_ACT_TBL_ITEM(WUEPS_PID_MMA,
                     ID_MMA_MSCC_CSG_LIST_ABORT_REQ,
                     NAS_MSCC_RcvMmaCsgListAbortReq_PreProc),

    NAS_ACT_TBL_ITEM(WUEPS_PID_MMC,
                     ID_MMC_MSCC_CSG_LIST_SEARCH_CNF,
                     NAS_MSCC_RcvMmcCsgListSearchCnf_PreProc),


    NAS_ACT_TBL_ITEM(WUEPS_PID_MMC,
                     ID_MMC_MSCC_CSG_LIST_REJ,
                     NAS_MSCC_RcvMmcCsgListRej_PreProc),

    NAS_ACT_TBL_ITEM(WUEPS_PID_MMC,
                     ID_MMC_MSCC_CSG_LIST_ABORT_CNF,
                     NAS_MSCC_RcvMmcCsgListAbortCnf_PreProc),
#endif
    NAS_ACT_TBL_ITEM(WUEPS_PID_MMA,
                     ID_MMA_MSCC_GET_GEO_REQ,
                     NAS_MSCC_RcvMmaGetGeoReq_PreProc),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_GET_GEO_CNF,
                      NAS_MSCC_RcvMmcGetGeoCnf_PreProc),

    NAS_ACT_TBL_ITEM(WUEPS_PID_MMA,
                     ID_MMA_MSCC_STOP_GET_GEO_REQ,
                     NAS_MSCC_RcvMmaStopGetGeoReq_PreProc),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_STOP_GET_GEO_CNF,
                      NAS_MSCC_RcvMmcStopGetGeoCnf_PreProc),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      ID_MMA_MSCC_DPLMN_SET_REQ,
                      NAS_MSCC_RcvMmaDplmnSetReq_PreProc),


    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_DPLMN_SET_CNF,
                      NAS_MSCC_RcvMmcDplmnSetCnf_PreProc),

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    NAS_ACT_TBL_ITEM(WUEPS_PID_MMA,
                     ID_MMA_MSCC_CDMA_MO_CALL_START_NTF,
                     NAS_MSCC_RcvMmaCdmaMoCallStartNtf_PreProc),

    NAS_ACT_TBL_ITEM(WUEPS_PID_MMA,
                     ID_MMA_MSCC_CDMA_MO_CALL_REDIAL_SYS_ACQ_NTF,
                     NAS_MSCC_RcvMmaCdmaMoCallRedialSysAcqNtf_PreProc),

    NAS_ACT_TBL_ITEM(WUEPS_PID_MMA,
                     ID_MMA_MSCC_CDMA_MO_CALL_SUCCESS_NTF,
                     NAS_MSCC_RcvMmaCdmaMoCallSuccessNtf_PreProc),

    NAS_ACT_TBL_ITEM(WUEPS_PID_MMA,
                     ID_MMA_MSCC_CDMA_MO_CALL_END_NTF,
                     NAS_MSCC_RcvMmaCdmaMoCallEndNtf_PreProc),

    NAS_ACT_TBL_ITEM(WUEPS_PID_MMA,
                     ID_MMA_MSCC_CFREQ_LOCK_NTF,
                     NAS_MSCC_RcvMmaCfreqLockNtf_PreProc),

    NAS_ACT_TBL_ITEM(WUEPS_PID_MMA,
                     ID_MMA_MSCC_CDMACSQ_SET_REQ,
                     NAS_MSCC_RcvMmaCdmacsqSetReq_PreProc),

    NAS_ACT_TBL_ITEM(UEPS_PID_XSD,
                     ID_XSD_MSCC_CDMACSQ_SET_CNF,
                     NAS_MSCC_RcvXsdCdmacsqSetCnf_PreProc),

    NAS_ACT_TBL_ITEM(UEPS_PID_XSD,
                     ID_XSD_MSCC_CDMACSQ_SIGNAL_QUALITY_IND,
                     NAS_MSCC_RcvXsdCdmacsqSignalQualityInd_PreProc),

    NAS_ACT_TBL_ITEM(UEPS_PID_XSD,
                     ID_XSD_MSCC_1X_SYSTEM_SERVICE_INFO_IND,
                     NAS_MSCC_RcvXsd1xSystemServiceInfoInd_PreProc),

    NAS_ACT_TBL_ITEM(UEPS_PID_XSD,
                     ID_XSD_MSCC_1X_SYSTEM_TIME_IND,
                     NAS_MSCC_RcvXsd1xSystemTimeInd_PreProc),

    NAS_ACT_TBL_ITEM(UEPS_PID_XSD,
                     ID_XSD_MSCC_SID_NID_IND,
                     NAS_MSCC_RcvXsdSidNidInd_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_MSCC_SESSION_NEG_RSLT_IND,
    /* function name modify */
                      NAS_MSCC_RcvHsdSessionNegRsltInd_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_MSCC_OVERHEAD_MSG_IND,
                      NAS_MSCC_RcvHsdOverheadMsgInd_PreProc),


    /* To handle the data call redial acquire confirmation from HSD */
    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_MSCC_DATA_CALL_REDIAL_SYS_ACQ_CNF,
                      NAS_MSCC_RcvHsdDataCallRedialAcqCnf_PreProc),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MSCC_BSR_TIMER,
                      NAS_MSCC_RcvTiBsrTimerExpired_PreProc),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MSCC_PERIOD_TRYING_HIGH_PRI_SYSTEM_SEARCH,
                      NAS_MSCC_RcvTiPeriodTryingHighPrioNetworkSearchTimerExpired_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_MSCC_CAS_STATUS_IND,
                      NAS_MSCC_RcvHsdHrpdCasStatusInd_PreProc),


    NAS_ACT_TBL_ITEM( UEPS_PID_XSD,
                      ID_XSD_MSCC_SYSTEM_ACQUIRE_IND,
                      NAS_MSCC_RcvXsdSysAcqInd_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_XSD,
                      ID_XSD_MSCC_SYSTEM_ACQUIRE_START_IND,
                      NAS_MSCC_RcvXsdSysAcqStartInd_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_MSCC_SYSTEM_ACQUIRE_START_IND,
                      NAS_MSCC_RcvHsdSysAcqStartInd_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_XSD,
                      ID_XSD_MSCC_POWER_SAVE_CNF,
                      NAS_MSCC_RcvXsdPowerSaveCnf_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_MSCC_POWER_SAVE_CNF,
                      NAS_MSCC_RcvHsdPowerSaveCnf_PreProc),

    NAS_ACT_TBL_ITEM(WUEPS_PID_MMA,
                     ID_MMA_MSCC_HANDSET_INFO_QRY_REQ,
                     NAS_MSCC_RcvMmaHandsetInfoQryReq_PreProc),

    NAS_ACT_TBL_ITEM(UEPS_PID_XSD,
                     ID_XSD_MSCC_HANDSET_INFO_QRY_CNF,
                     NAS_MSCC_RcvXsdHandsetInfoQryCnf_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_MSCC_RF_AVAILABLE_IND,
                      NAS_MSCC_RcvHsdRfAvailableInd_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_XSD,
                      ID_XSD_MSCC_RF_AVAILABLE_IND,
                      NAS_MSCC_RcvXsdRfAvailableInd_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_MSCC_INTERSYS_END_IND,
                      NAS_MSCC_RcvHsdInterSysEndInd_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_MSCC_INTERSYS_START_IND,
                      NAS_MSCC_RcvHsdInterSysStartInd_PreProc),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_INTERSYS_START_IND,
                      NAS_MSCC_RcvMmcInterSysStartInd_PreProc),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_INTERSYS_END_IND,
                      NAS_MSCC_RcvMmcInterSysEndInd_PreProc),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      ID_MMA_MSCC_PS_RAT_TYPE_NTF,
                      NAS_MSCC_RcvMmaPsRatTypeNtf_Main_PreProc),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      ID_MMA_MSCC_QUIT_CALL_BACK_NTF,
                      NAS_MSCC_RcvMmaQuitCallBackNtf_PreProc),
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      ID_MMA_MSCC_SET_CSIDLIST_REQ ,
                      NAS_MSCC_RcvMmaSetCSidListReq_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_XSD,
                      ID_XSD_MSCC_SET_CSIDLIST_CNF,
                      NAS_MSCC_RcvXsdSetCSidListCnf_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_XSD,
                      ID_XSD_MSCC_EMC_CALLBACK_IND,
                      NAS_MSCC_RcvXsdEmcCallBackNtf_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_XSD,
                      ID_XSD_MSCC_SYNC_SERVICE_AVAILABLE_IND,
                      NAS_MSCC_RcvXsdSyncServiceAvailableInd_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_XSD,
                      ID_XSD_MSCC_CDMA_UE_STATUS_IND,
                      NAS_MSCC_RcvXsdCurUeStatusInd_PreProc),

    NAS_ACT_TBL_ITEM(WUEPS_PID_MMA,
                     ID_MMA_MSCC_HDR_CSQ_SET_REQ,
                     NAS_MSCC_RcvMmaHdrcsqSetReq_PreProc),

    NAS_ACT_TBL_ITEM(UEPS_PID_HSD,
                     ID_HSD_MSCC_HDR_CSQ_SET_CNF,
                     NAS_MSCC_RcvHsdHdrcsqSetCnf_PreProc),


    NAS_ACT_TBL_ITEM(UEPS_PID_HSD,
                     ID_HSD_MSCC_HDR_CSQ_IND,
                     NAS_MSCC_RcvHsdHdrcsqInd_PreProc),




#endif

#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_ACQ_IND,
                      NAS_MSCC_RcvMmcAcqInd_PreProc ),
#endif


#if (FEATURE_ON == FEATURE_MULTI_MODEM)

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_PS_SERVICE_CONN_STATUS_IND,
                      NAS_MSCC_RcvMmcPsServiceConnStatusInd_PreProc),

    NAS_ACT_TBL_ITEM(WUEPS_PID_MMA,
                     ID_MMA_MSCC_OTHER_MODEM_INFO_NOTIFY,
                     NAS_MSCC_RcvMmaOtherModemInfoNotify_PreProc),

    NAS_ACT_TBL_ITEM(WUEPS_PID_MMA,
                     ID_MMA_MSCC_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY,
                     NAS_MSCC_RcvMmaOtherModemDplmnNplmnInfoNotify_PreProc),

    NAS_ACT_TBL_ITEM(WUEPS_PID_MMA,
                     ID_MMA_MSCC_NCELL_INFO_NOTIFY,
                     NAS_MSCC_RcvMmaNcellInfoNotify_PreProc),

    NAS_ACT_TBL_ITEM(WUEPS_PID_MMA,
                     ID_MMA_MSCC_PS_TRANSFER_NOTIFY,
                     NAS_MSCC_RcvMmaPsTransferNotify_PreProc),
#endif

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_SRV_ACQ_CNF,
                      NAS_MSCC_RcvMmcSrvAcqCnf_PreProc),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      ID_MMA_MSCC_SRV_ACQ_REQ,
                      NAS_MSCC_RcvMmaSrvAcqReq_PreProc),

    NAS_ACT_TBL_ITEM(WUEPS_PID_MMA,
                     ID_MMA_MSCC_BEGIN_SESSION_NOTIFY,
                     NAS_MSCC_RcvMmaBeginSessionNotify_PreProc),

    NAS_ACT_TBL_ITEM(WUEPS_PID_MMA,
                     ID_MMA_MSCC_END_SESSION_NOTIFY,
                     NAS_MSCC_RcvMmaEndSessionNotify_PreProc),

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    NAS_ACT_TBL_ITEM( UEPS_PID_XSD,
                      ID_XSD_MSCC_SRV_ACQ_CNF,
                      NAS_MSCC_RcvXsdSrvAcqCnf_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_MSCC_SRV_ACQ_CNF,
                      NAS_MSCC_RcvHsdSrvAcqCnf_PreProc),
#endif



#if (FEATURE_ON == FEATURE_IMS)
    NAS_ACT_TBL_ITEM(WUEPS_PID_MMA,
                     ID_MMA_MSCC_IMS_SRV_INFO_NOTIFY,
                     NAS_MSCC_RcvMmaImsSrvInfoNotify_PreProc),

    NAS_ACT_TBL_ITEM(PS_PID_IMSA,
                     ID_IMSA_MSCC_IMS_VOICE_CAP_NOTIFY,
                     NAS_MSCC_RcvImsaImsVoiceCapNotify_PreProc),

    NAS_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_NAS_MSCC_WAIT_IMSA_IMS_VOICE_CAP_NOTIFY,
                     NAS_MSCC_RcvTiWaitImsaImsVoiceCapNtfExpired_PreProc),

    NAS_ACT_TBL_ITEM(WUEPS_PID_MMA,
                     ID_MMA_MSCC_IMS_START_REQ,
                     NAS_MSCC_RcvMmaImsStartReq_PreProc),

    NAS_ACT_TBL_ITEM(WUEPS_PID_MMA,
                     ID_MMA_MSCC_IMS_STOP_REQ,
                     NAS_MSCC_RcvMmaImsStopReq_PreProc),

    NAS_ACT_TBL_ITEM(WUEPS_PID_MMA,
                     ID_MMA_MSCC_VOICE_DOMAIN_CHANGE_IND,
                     NAS_MSCC_RcvMmaVoiceDomainChangeInd_PreProc),

    NAS_ACT_TBL_ITEM(PS_PID_IMSA,
                     ID_IMSA_MSCC_START_CNF,
                     NAS_MSCC_RcvImsaStartCnf_PreProc),

    NAS_ACT_TBL_ITEM(PS_PID_IMSA,
                     ID_IMSA_MSCC_STOP_CNF,
                     NAS_MSCC_RcvImsaStopCnf_PreProc),

    NAS_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_NAS_MSCC_WAIT_IMSA_START_CNF,
                     NAS_MSCC_RcvTiWaitImsaStartCnfExpired_PreProc),

    NAS_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_NAS_MSCC_WAIT_IMSA_POWER_OFF_CNF,
                     NAS_MSCC_RcvTiWaitImsaPowerOffCnfExpired_PreProc),

#endif
    NAS_ACT_TBL_ITEM(WUEPS_PID_MMA,
                     ID_MMA_MSCC_AUTO_RESEL_SET_REQ,
                     NAS_MSCC_RcvMmaAutoReselSetReq_PreProc),
#ifdef DMT

    NAS_ACT_TBL_ITEM(UEPS_PID_MSCC,
                     ID_NAS_MSCC_MODIFY_MLPL_RECORD_REQ,
                     NAS_MSCC_RcvMsccMofiyMlplRecordReq_PreProc),

    NAS_ACT_TBL_ITEM(UEPS_PID_MSCC,
                     ID_NAS_MSCC_MODIFY_MSPL_ID_REQ,
                     NAS_MSCC_RcvMsccMofiyMsplIdReq_PreProc),

    NAS_ACT_TBL_ITEM(UEPS_PID_MSCC,
                     ID_NAS_MSCC_SET_CARD_READ_STUB_TYPE_REQ,
                     NAS_MSCC_RcvSetCardReadStubTypeReq_PreProc),

#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    NAS_ACT_TBL_ITEM(UEPS_PID_HSD,
                     ID_HSD_MSCC_HRPD_NO_SERVICE_IND,
                     NAS_MSCC_RcvHsdHrpdNoSrv_PreProc),

    NAS_ACT_TBL_ITEM(UEPS_PID_XSD,
                     ID_XSD_MSCC_1X_NO_SERVICE_IND,
                     NAS_MSCC_RcvXsd1xNoSrv_PreProc),
#endif

};

/* 预处理的消息状态表 */
NAS_STA_STRU g_astNasMsccPreStaTbl[] =
{
    NAS_STA_TBL_ITEM( NAS_MSCC_L1_STA_PREPROC,
                      g_astNasMsccPreProActTbl)
};

/*****************************************************************************
  3 函数定义
*****************************************************************************/

/*****************************************************************************
 函 数 名  : NAS_MSCC_GetPreProcessStaTblSize
 功能描述  : 获取预处理状态机的大小
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32:预处理状态机的大小
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年01月27日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MSCC_GetPreProcessStaTblSize(VOS_VOID)
{
    return (sizeof(g_astNasMsccPreStaTbl)/sizeof(NAS_STA_STRU));
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_GetPreFsmDescAddr
 功能描述  : 获取预处理状态机的描述表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_FSM_DESC_STRU:指向预处理状态机的描述表
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年01月27日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
NAS_FSM_DESC_STRU *NAS_MSCC_GetPreFsmDescAddr(VOS_VOID)
{
    return (&g_stNasMsccPreFsmDesc);
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



