



/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "UsimPsInterface.h"
#include "PsTypeDef.h"
#include "MnComm.h"
#include "NasComm.h"
#include "NasFsm.h"
#include "NasMsccFsmMain.h"
#include "NasMsccFsmMainTbl.h"
#include "NasMsccSndInternalMsg.h"
#include "MmaMsccInterface.h"
#include "MsccMmcInterface.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_NAS_MSCC_FSM_MAIN_TBL_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/* NAS MSCC 状态机数 */
NAS_FSM_DESC_STRU                       g_stNasMsccMainFsmDesc;

/* NAS_MSCC_MAIN_STA_NULL act table */
NAS_ACT_STRU g_astNasMsccMainNullActTbl[] =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      ID_MMA_MSCC_START_REQ,
                      NAS_MSCC_RcvMmaStartReq_Main_Null),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_NAS_MSCC_MSCC_SWITCH_ON_RSLT_CNF,
                      NAS_MSCC_RcvMsccStartCnf_Main_Null)

};

/* NAS_MSCC_MAIN_STA_DEACTIVE act table */
NAS_ACT_STRU g_astNasMsccMainDeactiveActTbl[] =
{

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      ID_MMA_MSCC_START_REQ,
                      NAS_MSCC_RcvMmaStartReq_Main_Deactive),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      ID_MMA_MSCC_POWER_OFF_REQ,
                      NAS_MSCC_RcvMmaPowerOffReq_Main_Deactive),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      ID_MMA_MSCC_SYSTEM_ACQUIRE_REQ,
                      NAS_MSCC_RcvMmaSysAcquireReq_Main_Deactive),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_NAS_MSCC_MSCC_POWER_OFF_RSLT_CNF,
                      NAS_MSCC_RcvMsccPowerOffCnf_Main_Deactive),

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MSCC_SLEEP_TIMER,
                      NAS_MSCC_RcvTiSleepTimerExpired_Main_Deactive),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_RF_AVAILABLE_IND,
                      NAS_MSCC_RcvMmcMsccRfAvailableInd_Main_Deactive),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_MSCC_RF_AVAILABLE_IND,
                      NAS_MSCC_RcvHsdMsccRfAvailableInd_Main_Deactive),

    NAS_ACT_TBL_ITEM( UEPS_PID_XSD,
                      ID_XSD_MSCC_RF_AVAILABLE_IND,
                      NAS_MSCC_RcvXsdMsccRfAvailableInd_Main_Deactive),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      ID_MMA_MSCC_SRV_ACQ_REQ,
                      NAS_MSCC_RcvMmaSrvAcqReq_Main_Deactive),
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      ID_MMA_MSCC_CDMA_MO_CALL_START_NTF,
                      NAS_MSCC_RcvMmaCdmaMoCallStartNtf_Main_Deactive),


    NAS_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      ID_MMA_MSCC_PLMN_USER_RESEL_REQ,
                      NAS_MSCC_RcvMmaPlmnUserReselReq_Main_Deactive),
#endif


    NAS_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      ID_MMA_MSCC_SYS_CFG_SET_REQ,
                      NAS_MSCC_RcvMmaSysCfgReq_Main_L1Main),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_NAS_MSCC_MSCC_SYS_CFG_RSLT_CNF,
                      NAS_MSCC_RcvMsccSysCfgCnf_Main_Deactive)
};

/* NAS_MSCC_MAIN_STA_ACTIVE act table */
NAS_ACT_STRU g_astNasMsccMainActiveActTbl[] =
{

   NAS_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      ID_MMA_MSCC_POWER_OFF_REQ,
                      NAS_MSCC_RcvMmaPowerOffReq_Main_Active),

   /* To handle the system acquire confirmation from MMC */
   NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_PLMN_SELECTION_RLST_IND,
                      NAS_MSCC_RcvMmcPlmnSelectionRsltInd_Main_Active),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_NAS_MSCC_MSCC_POWER_OFF_RSLT_CNF,
                      NAS_MSCC_RcvMsccPowerOffCnf_Main_Active),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      ID_MMA_MSCC_SYS_CFG_SET_REQ,
                      NAS_MSCC_RcvMmaSysCfgReq_Main_L1Main),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_NAS_MSCC_MSCC_SYS_CFG_RSLT_CNF,
                      NAS_MSCC_RcvMsccSysCfgCnf_Main_Active),

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

    /* To handle the system acquire confirmation from HSD */
    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_MSCC_SYSTEM_ACQUIRE_END_IND,
                      NAS_MSCC_RcvHsdSysAcqInd_Main_Active),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_NAS_MSCC_MSCC_SYS_ACQ_RSLT_CNF,
                      NAS_MSCC_RcvInterSysAcqRsltCnf_Main_Active),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MSCC_AVAILABLE_TIMER,
                      NAS_MSCC_RcvTiAvailableTimerExpired_Main_Active),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_ONE_TOTAL_TIMER,
                      NAS_MSCC_RcvTi1xSrvClSysAcqPhaseOneTotalTimerExpired_Main_Active),


    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MSCC_SCAN_TIMER,
                      NAS_MSCC_RcvTiScanTimerExpired_Main_Active),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_NAS_MSCC_MSCC_SYS_ACQ_REQ,
                      NAS_MSCC_RcvInternalSysAcqReq_Main_Active),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_MMSS_LTE_UNAVAILABLE_IND,
                      NAS_MSCC_RcvMmcMmssLteUnavailableInd_Main_Active),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_NAS_MSCC_MSCC_BSR_RSLT_CNF,
                      NAS_MSCC_RcvInternalBsrRsltCnf_Main_Active),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MSCC_BSR_TIMER,
                      NAS_MSCC_RcvTiBsrTimerExpired_Main_Active),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MSCC_PERIOD_TRYING_HIGH_PRI_SYSTEM_SEARCH,
                      NAS_MSCC_RcvTiPeriodTryingHighPrioNetworkSearchExpired_Main_Active),

    /* XSD模块不可能在XSD处于deactive状态收到ID_XSD_MSCC_RF_AVAILABLE_IND消息 */
    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_MSCC_RF_AVAILABLE_IND,
                      NAS_MSCC_RcvHsdRfAvailableInd_Main_Active),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_RF_AVAILABLE_IND,
                      NAS_MSCC_RcvMmcRfAvailableInd_Main_Active),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_MSCC_INTERSYS_START_IND,
                      NAS_MSCC_RcvHsdInterSysStartInd_Main_Active),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_INTERSYS_START_IND,
                      NAS_MSCC_RcvMmcInterSysStartInd_Main_Active),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_NAS_MSCC_MSCC_CL_INTERSYS_RSLT_CNF,
                      NAS_MSCC_RcvMsccCLInterSysRsltCnf_Main_Active),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      ID_MMA_MSCC_CDMA_MO_CALL_SUCCESS_NTF,
                      NAS_MSCC_RcvMmaCdmaMoCallSusccessNtf_Main_Active),

    NAS_ACT_TBL_ITEM( UEPS_PID_XSD,
                      ID_XSD_MSCC_EMC_CALLBACK_IND,
                      NAS_MSCC_RcvXsdEmcCallBackInd_Main_Active),
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      ID_MMA_MSCC_PLMN_USER_RESEL_REQ,
                      NAS_MSCC_RcvMmaPlmnUserReselReq_Main_Active),
#endif

};

/* Redirection state table */
NAS_STA_STRU g_astNasMsccMainStaTbl[] =
{
    /***************************************/
    NAS_STA_TBL_ITEM( NAS_MSCC_L1_STA_NULL,
                      g_astNasMsccMainNullActTbl),

    /**************************************/
    NAS_STA_TBL_ITEM( NAS_MSCC_L1_STA_DEACTIVE,
                      g_astNasMsccMainDeactiveActTbl ),

    /*************************************/
    NAS_STA_TBL_ITEM( NAS_MSCC_L1_STA_ACTIVE,
                      g_astNasMsccMainActiveActTbl),

};

/*****************************************************************************
  3 函数定义
*****************************************************************************/



VOS_UINT32 NAS_MSCC_GetMainStaTblSize(VOS_VOID)
{
    return (sizeof(g_astNasMsccMainStaTbl)/sizeof(NAS_STA_STRU));
}



NAS_FSM_DESC_STRU *NAS_MSCC_GetMainFsmDescAddr(VOS_VOID)
{
    return (&g_stNasMsccMainFsmDesc);
}
/*lint -restore*/


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */




