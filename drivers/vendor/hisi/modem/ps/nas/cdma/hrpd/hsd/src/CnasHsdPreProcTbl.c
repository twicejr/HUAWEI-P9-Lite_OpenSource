

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "CnasHsdPreProcTbl.h"
#include  "CnasHsdFsmMainTbl.h"
#include  "CnasHsdTimer.h"
#include  "CnasHsdPreProcAct.h"
#include  "cas_hrpd_idlestate_nas_pif.h"
#include  "hsm_hsd_pif.h"
#include  "PsRrmInterface.h"
#include  "CnasHsdSndInternalMsg.h"
#include  "cas_hrpd_routeupdate_nas_pif.h"
#include  "hsd_mscc_pif.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSD_PRE_PROC_TBL_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/* 预处理状态机 */
NAS_FSM_DESC_STRU                       g_stCnasHsdPreFsmDesc;

/* 预处理的消息动作表 */
NAS_ACT_STRU g_astCnasHsdPreProActTbl[] =
{
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_HSD_SLICE_REVERSE_PROTECT_TIMER,
                      CNAS_HSD_RcvSliceReverseProtectTimerExpired_PreProc),

#if 0
/* 该消息在迭代15不再由HRUP发送，移至Network lost原因值中，后续需要作适应修改 */
    NAS_ACT_TBL_ITEM( UEPS_PID_HRUP,
                      ID_CAS_CNAS_HRPD_TCH_ASSIGN_TIMEOUT_IND,
                      CNAS_HSD_RcvTchAssignTimeoutInd_PreProc),
#endif
    NAS_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_HSM_HSD_CAS_STATUS_IND,
                      CNAS_HSD_RcvCasStatusInd_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_RRM,
                      ID_RRM_PS_STATUS_IND,
                      CNAS_HSD_RcvPsStatusInd_PreProc),

    NAS_ACT_TBL_ITEM(UEPS_PID_MSCC,
                     ID_MSCC_HSD_1X_SYS_CHANGE_IND,
                     CNAS_HSD_Rcv1xSysChgInd_PreProc),

    NAS_ACT_TBL_ITEM(UEPS_PID_MSCC,
                     ID_MSCC_HSD_QRY_HRPD_SYS_INFO_REQ,
                     CNAS_HSD_RcvMsccQryHrpdSysInfoReq_PreProc),

    NAS_ACT_TBL_ITEM(UEPS_PID_MSCC,
                     ID_MSCC_HSD_DISABLE_LTE_NTF,
                     CNAS_HSD_RcvMsccDisableLteNtf_PreProc),

    NAS_ACT_TBL_ITEM(UEPS_PID_MSCC,
                     ID_MSCC_HSD_BG_SEARCH_REQ,
                     CNAS_HSD_RcvMsccBgSearchReq_PreProc),

    NAS_ACT_TBL_ITEM(UEPS_PID_MSCC,
                     ID_MSCC_HSD_STOP_BG_SEARCH_REQ,
                     CNAS_HSD_RcvMsccStopBgSearchReq_PreProc),

    NAS_ACT_TBL_ITEM(UEPS_PID_HALMP,
                     ID_CAS_CNAS_HRPD_BSR_LTE_CNF,
                     CNAS_HSD_RcvCasBsrLteCnf_PreProc),

    NAS_ACT_TBL_ITEM(UEPS_PID_HALMP,
                     ID_CAS_CNAS_HRPD_BSR_FREQ_LIST_QUERY_REQ,
                     CNAS_HSD_RcvCasFreqListReq_PreProc),

    NAS_ACT_TBL_ITEM(UEPS_PID_HALMP,
                     ID_CAS_CNAS_HRPD_STOP_BSR_LTE_CNF,
                     CNAS_HSD_RcvCasStopBsrLteCnf_PreProc),
#ifdef DMT
    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_CNAS_HSD_HSD_TEST_CFG_REQ,
                      CNAS_HSD_RcvHsdTestCfgREQ_PreProc),
#endif

    NAS_ACT_TBL_ITEM(UEPS_PID_MSCC,
                     ID_MSCC_HSD_SYS_CFG_REQ,
                     CNAS_HSD_RcvMsccSysCfgSet_PreProc),

    NAS_ACT_TBL_ITEM(UEPS_PID_HALMP,
                     ID_CAS_CNAS_HRPD_SYS_CFG_CNF,
                     CNAS_HSD_RcvCasSysCfgCnf_PreProc),

    NAS_ACT_TBL_ITEM(UEPS_PID_HSP,
                     ID_CAS_CNAS_HRPD_OHM_NOT_CURRENT_IND,
                     CNAS_HSD_RcvCasOhmNotCurrentInd_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_HALMP,
                      ID_CAS_CNAS_HRPD_NETWORK_LOST_IND,
                      CNAS_HSD_RcvCasNetworkLostIndProc_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_CFREQLOCK_NTF,
                      CNAS_HSD_RcvMsccCFreqLockSetNtf_PreProc),
#if 0
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_DATA_CALL_START_NTF,
                      CNAS_HSD_RcvMsccDataCallStartNtf_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_DATA_CALL_SUCC_NTF,
                      CNAS_HSD_RcvMsccDataCallSuccNtf_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_DATA_CALL_END_NTF,
                      CNAS_HSD_RcvMsccDataCallEndNtf_PreProc),
#endif

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_HSD_WAIT_RRM_STATUS_IND,
                      CNAS_HSD_RcvNoRFProtectTimerExpired_PreProc),

    NAS_ACT_TBL_ITEM(UEPS_PID_HALMP,
                     ID_CAS_CNAS_HRPD_SUSPEND_IND,
                     CNAS_HSD_RcvCasSuspendInd_PreProc),

    NAS_ACT_TBL_ITEM(UEPS_PID_MSCC,
                     ID_MSCC_HSD_HDR_CSQ_SET_REQ,
                     CNAS_HSD_RcvMsccHdrCsqSetReq_PreProc),

    NAS_ACT_TBL_ITEM(UEPS_PID_HRUP,
                     ID_CAS_CNAS_HRPD_SET_SIGNAL_QUALITY_CNF,
                     CNAS_HSD_RcvCasHdrCsqSetCnf_PreProc),

    NAS_ACT_TBL_ITEM(UEPS_PID_HRUP,
                     ID_CAS_CNAS_HRPD_SIGNAL_QUALITY_IND,
                     CNAS_HSD_RcvMsccHdrCsqQualityInd_PreProc),




};

/* 预处理的消息状态表 */
NAS_STA_STRU g_astCnasHsdPreStaTbl[] =
{
    NAS_STA_TBL_ITEM( CNAS_HSD_L1_STA_PREPROC,
                      g_astCnasHsdPreProActTbl)
};


/*****************************************************************************
  3 函数定义
*****************************************************************************/


VOS_UINT32 CNAS_HSD_GetPreProcessStaTblSize(VOS_VOID)
{
    return (sizeof(g_astCnasHsdPreStaTbl)/sizeof(NAS_STA_STRU));
}


NAS_FSM_DESC_STRU *CNAS_HSD_GetPreFsmDescAddr(VOS_VOID)
{
    return (&g_stCnasHsdPreFsmDesc);
}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



