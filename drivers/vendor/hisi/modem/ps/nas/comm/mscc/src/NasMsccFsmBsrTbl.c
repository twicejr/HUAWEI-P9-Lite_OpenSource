



/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "NasFsm.h"
#include "NasMsccFsmBsrTbl.h"
#include "NasMsccSndInternalMsg.h"
#include "NasMsccFsmBsr.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_NAS_MSCC_FSM_BSR_TBL_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
NAS_FSM_DESC_STRU                       g_stNasMsccBsrFsmDesc;

/**************************************************************************/
/*新增状态动作处理表 */
/**************************************************************************/

/* NAS_MSCC_BSR_STA_INIT Action table */
NAS_ACT_STRU        g_astNasMsccBsrInitActTbl[]   =
{
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MSCC_BSR_TIMER,
                      NAS_MSCC_RcvTiBsrTimerExpired_BSR_Init ),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MSCC_PERIOD_TRYING_HIGH_PRI_SYSTEM_SEARCH,
                      NAS_MSCC_RcvTiRetryTimerExpired_BSR_Init )
};

/*************************LTE prefered begin*******************************/
/* NAS_MSCC_BSR_STA_WAIT_HSD_BG_SEARCH_CNF Action table */
NAS_ACT_STRU        g_astNasMsccBsrWaitHsdBgSearchCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_MSCC_BG_SEARCH_CNF,
                      NAS_MSCC_RcvHsdBgSearchCnf_BSR_WaitHsdBgSearchCnf ),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_NAS_MSCC_MSCC_ABORT_FSM_REQ,
                      NAS_MSCC_RcvMsccAbortFsm_BSR_WaitHsdBgSearchCnf ),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MSCC_WAIT_HSD_BG_SEARCH_CNF,
                      NAS_MSCC_RcvTiWaitHsdBgSearchCnfTimeExpired_BSR_WaitHsdBgSearchCnf )
};

/* NAS_MSCC_BSR_STA_WAIT_HSD_STOP_BG_SEARCH_CNF Action table */
NAS_ACT_STRU        g_astNasMsccBsrWaitHsdStopBgSearchCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_MSCC_STOP_BG_SEARCH_CNF,
                      NAS_MSCC_RcvHsdStopBgSearchCnf_BSR_WaitHsdStopBgSearchCnf ),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_NAS_MSCC_MSCC_ABORT_FSM_REQ,
                      NAS_MSCC_RcvMsccAbortFsm_BSR_WaitHsdStopBgSearchCnf ),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MSCC_WAIT_HSD_STOP_BG_SEARCH_CNF,
                      NAS_MSCC_RcvTiWaitHsdStopBgSearchCnfTimeExpired_BSR_WaitHsdStopBgSearchCnf )
};

/* NAS_MSCC_BSR_STA_WAIT_MMC_QRY_PLMN_PRI_CLASS_CNF Action table */
NAS_ACT_STRU        g_astNasMsccBsrWaitMmcPlmnPriClassQueryCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_PLMN_PRI_CLASS_QUERY_CNF,
                      NAS_MSCC_RcvMmcPlmnPriClassQueryCnf_BSR_WaitMmcPlmnPriClassQueryCnf ),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_NAS_MSCC_MSCC_ABORT_FSM_REQ,
                      NAS_MSCC_RcvMsccAbortFsm_BSR_WaitMmcPlmnPriClassQueryCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MSCC_WAIT_MMC_QRY_PLMN_PRI_CLASS_CNF,
                      NAS_MSCC_RcvTiWaitMmcPlmnPriClassQueryCnfTimeExpired_BSR_WaitMmcPlmnPriClassQueryCnf)
};

/* NAS_MSCC_BSR_STA_WAIT_HSD_POWER_SAVE_CNF Action table */
NAS_ACT_STRU        g_astNasMsccBsrWaitHsdPowerSaveCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_MSCC_POWER_SAVE_CNF,
                      NAS_MSCC_RcvHsdPowerSaveCnf_BSR_WaitHsdPowerSaveCnf ),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_NAS_MSCC_MSCC_ABORT_FSM_REQ,
                      NAS_MSCC_RcvMsccAbortFsm_BSR_WaitHsdPowerSaveCnf  ),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MSCC_WAIT_HSD_POWER_SAVE_CNF,
                      NAS_MSCC_RcvTiWaitHsdPowerSaveCnfTimeExpired_BSR_WaitHsdPowerSaveCnf  )
};

/* NAS_MSCC_BSR_STA_WAIT_MMC_PLMN_SEARCH_CNF Action table */
NAS_ACT_STRU        g_astNasMsccBsrWaitMmcPlmnSearchCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_PLMN_SELECTION_RLST_IND,
                      NAS_MSCC_RcvMmcPlmnSearchCnf_BSR_WaitMmcPlmnSearchCnf ),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_NAS_MSCC_MSCC_ABORT_FSM_REQ,
                      NAS_MSCC_RcvMsccAbortFsm_BSR_WaitMmcPlmnSearchCnf ),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MSCC_WAIT_MMC_PLMN_SEARCH_CNF,
                      NAS_MSCC_RcvTiWaitMmcPlmnSearchCnfTimeExpired_BSR_WaitMmcPlmnSearchCnf ),

    NAS_ACT_TBL_ITEM(WUEPS_PID_MMC,
                    ID_MMC_MSCC_INTERSYS_START_IND,
                    NAS_MSCC_RcvMmcIntersysStartInd_BSR_WaitMmcPlmnSearchCnf),

    NAS_ACT_TBL_ITEM(UEPS_PID_MSCC,
                     ID_NAS_MSCC_MSCC_CL_INTERSYS_RSLT_CNF,
                     NAS_MSCC_RcvMsccCLInterSysRsltCnf_BSR_WaitMmcPlmnSearchCnf),
};

/* NAS_MSCC_BSR_STA_WAIT_MMC_POWER_SAVE_CNF_REACQ_HRPD Action table */
NAS_ACT_STRU        g_astNasMsccBsrWaitMmcPowerSaveCnfReAcqHrpdActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_POWER_SAVE_CNF,
                      NAS_MSCC_RcvMmcPowerSaveCnf_BSR_WaitMmcPowerSaveReAcqHrpd ),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_NAS_MSCC_MSCC_ABORT_FSM_REQ,
                      NAS_MSCC_RcvMsccAbortFsm_BSR_WaitMmcPowerSaveReAcqHrpd ),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MSCC_WAIT_MMC_POWER_SAVE_CNF,
                      NAS_MSCC_RcvTiWaitMmcPowerSaveReAcqHrpdTimeExpired_BSR_WaitMmcPowerSaveReAcqHrpd )
};

/* NAS_MSCC_BSR_STA_WAIT_HSD_SYSTEM_ACQUIRE_CNF_REACQ_HRPD Action table */
NAS_ACT_STRU        g_astNasMsccBsrWaitHsdSystemAcquireCnfReAcqHrpdActTbl[]   =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_MSCC_SYSTEM_ACQUIRE_CNF,
                      NAS_MSCC_RcvHsdSystemAcquireCnf_BSR_WaitHsdAcquireCnfReAcqHrpd ),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_NAS_MSCC_MSCC_ABORT_FSM_REQ,
                      NAS_MSCC_RcvMsccAbortFsm_BSR_WaitHsdAcquireCnfReAcqHrpd ),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MSCC_WAIT_HSD_ACQUIRE_CNF,
                      NAS_MSCC_RcvTiWaitHsdAcqCnfReAcqHrpdTimeExpired_BSR_WaitHsdAcquireCnfReAcqHrpd )
};
/****************************LTE prefered end******************************************/


/* NAS_MSCC_BSR_STA_WAIT_MMC_BG_SEARCH_CNF Action table */
NAS_ACT_STRU        g_astNasMsccBsrWaitMmcBgSearchCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_BG_SEARCH_CNF,
                      NAS_MSCC_RcvMmcBgSearchCnf_BSR_WaitMmcBgSearchCnf ),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_NAS_MSCC_MSCC_ABORT_FSM_REQ,
                      NAS_MSCC_RcvMsccAbortFsmMsg_BSR_WaitMmcBgSearchCnf ),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_COVERAGE_AREA_IND,
                      NAS_MSCC_RcvMmcCoverageAreaInd_BSR_WaitMmcBgSearchCnf ),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MSCC_WAIT_MMC_BG_SEARCH_CNF,
                      NAS_MSCC_RcvTiWaitMmcBgSearchCnfExpired_BSR_WaitMmcBgSearchCnf ),
};

/* NAS_MSCC_BSR_STA_WAIT_MMC_STOP_BG_SEARCH_CNF Action table */
NAS_ACT_STRU        g_astNasMsccBsrWaitMmcStopBgSearchCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_STOP_BG_SEARCH_CNF,
                      NAS_MSCC_RcvMmcStopBgSearchCnf_BSR_WaitMmcStopBgSearchCnf ),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_COVERAGE_AREA_IND,
                      NAS_MSCC_RcvMmcCoverageAreaInd_BSR_WaitMmcStopBgSearchCnf ),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_NAS_MSCC_MSCC_ABORT_FSM_REQ,
                      NAS_MSCC_RcvMsccAbortFsmMsg_BSR_WaitMmcStopBgSearchCnf ),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MSCC_WAIT_MMC_STOP_BG_SEARCH_CNF,
                      NAS_MSCC_RcvTiWaitMmcStopBgSearchCnfExpired_BSR_WaitMmcStopBgSearchCnf ),
};

/* NAS_MSCC_BSR_STA_WAIT_HSD_QRY_HRPD_SYS_INFO_CNF Action table */
NAS_ACT_STRU        g_astNasMsccBsrWaitHsdQryHrpdSysInfoCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_MSCC_QRY_HRPD_SYS_INFO_CNF,
                      NAS_MSCC_RcvHsdQryHrpdSysInfoCnf_BSR_WaitHsdQryHrpdSysInfoCnf ),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_NAS_MSCC_MSCC_ABORT_FSM_REQ,
                      NAS_MSCC_RcvMsccAbortFsmMsg_BSR_WaitHsdQryHrpdSysInfoCnf ),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MSCC_WAIT_HSD_QRY_HRPD_SYS_INFO_CNF,
                      NAS_MSCC_RcvTiWaitHsdQryHrpdSysInfoCnfExpired_WaitHsdQryHrpdSysInfoCnf ),
};

/* NAS_MSCC_BSR_STA_WAIT_MMC_POWER_SAVE_CNF Action table */
NAS_ACT_STRU        g_astNasMsccBsrWaitMmcPowerSaveCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_POWER_SAVE_CNF,
                      NAS_MSCC_RcvMmcPowerSaveCnf_BSR_WaitMmcPowerSaveCnf ),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_NAS_MSCC_MSCC_ABORT_FSM_REQ,
                      NAS_MSCC_RcvMsccAbortFsmMsg_BSR_WaitMmcPowerSaveCnf ),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MSCC_WAIT_MMC_POWER_SAVE_CNF,
                      NAS_MSCC_RcvTiWaitMmcPowerSaveCnfExpired_BSR_WaitMmcPowerSaveCnf),
};

/* NAS_MSCC_BSR_STA_WAIT_HSD_SYSTEM_ACQUIRE_CNF Action table */
NAS_ACT_STRU        g_astNasMsccBsrWaitHsdSystemAcquireCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_MSCC_SYSTEM_ACQUIRE_CNF ,
                      NAS_MSCC_RcvHsdSystemAcquireCnf_BSR_WaitHsdSystemAcquireCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MSCC_WAIT_HSD_ACQUIRE_CNF ,
                      NAS_MSCC_RcvTiWaitHsdSystemAcquireCnfExpired_BSR_WaitHsdSystemAcquireCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_NAS_MSCC_MSCC_ABORT_FSM_REQ,
                      NAS_MSCC_RcvMsccAbortFsm_BSR_WaitHsdSystemAcquireCnf)
};

/* NAS_MSCC_BSR_STA_WAIT_HSD_POWER_SAVE_CNF_REACQ_LTE Action table */
NAS_ACT_STRU        g_astNasMsccBsrWaitHsdPowerSaveCnfReAcqLteActTbl[]   =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_MSCC_POWER_SAVE_CNF ,
                      NAS_MSCC_RcvHsdPowerSaveCnf_BSR_WaitHsdPowerSaveCnfReAcqLte),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_NAS_MSCC_MSCC_ABORT_FSM_REQ,
                      NAS_MSCC_RcvMsccAbortFsm_BSR_WaitHsdPowerSaveCnfReAcqLte),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MSCC_WAIT_HSD_POWER_SAVE_CNF,
                      NAS_MSCC_RcvTiWaitHsdPowerSaveCnfExpired_BSR_WaitHsdPowerSaveCnfReAcqLte)

};

/* NAS_MSCC_BSR_STA_WAIT_MMC_PLMN_SEARCH_CNF_REACQ_LTE Action table */
NAS_ACT_STRU        g_astNasMsccBsrWaitMmcPlmnSearchCnfReAcqLteActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_PLMN_SELECTION_RLST_IND,
                      NAS_MSCC_RcvMmcPlmnSeachCnf_BSR_WaitMmcPlmnSearchCnfReAcqLte),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_NAS_MSCC_MSCC_ABORT_FSM_REQ,
                      NAS_MSCC_RcvMsccAbortFsm_BSR_WaitMmcPlmnSearchCnfReAcqLte),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MSCC_WAIT_MMC_PLMN_SEARCH_CNF,
                      NAS_MSCC_RcvTiWaitMmcPlmnSeachCnfExpired_BSR_WaitMmcPlmnSearchCnfReAcqLte),

};

/* NAS MSCC better system reselection(BSR) state table */
NAS_STA_STRU        g_astNasMsccBsrStaTbl[]   =
{
    NAS_STA_TBL_ITEM( NAS_MSCC_BSR_STA_INIT,
                      g_astNasMsccBsrInitActTbl ),

    NAS_STA_TBL_ITEM( NAS_MSCC_BSR_STA_WAIT_HSD_BG_SEARCH_CNF,
                      g_astNasMsccBsrWaitHsdBgSearchCnfActTbl ),

    NAS_STA_TBL_ITEM( NAS_MSCC_BSR_STA_WAIT_HSD_STOP_BG_SEARCH_CNF,
                      g_astNasMsccBsrWaitHsdStopBgSearchCnfActTbl ),

    NAS_STA_TBL_ITEM( NAS_MSCC_BSR_STA_WAIT_MMC_QRY_PLMN_PRI_CLASS_CNF,
                      g_astNasMsccBsrWaitMmcPlmnPriClassQueryCnfActTbl ),

    NAS_STA_TBL_ITEM( NAS_MSCC_BSR_STA_WAIT_HSD_POWER_SAVE_CNF,
                      g_astNasMsccBsrWaitHsdPowerSaveCnfActTbl ),

    NAS_STA_TBL_ITEM( NAS_MSCC_BSR_STA_WAIT_MMC_PLMN_SEARCH_CNF,
                      g_astNasMsccBsrWaitMmcPlmnSearchCnfActTbl ),

    NAS_STA_TBL_ITEM( NAS_MSCC_BSR_STA_WAIT_MMC_POWER_SAVE_CNF_REACQ_HRPD,
                      g_astNasMsccBsrWaitMmcPowerSaveCnfReAcqHrpdActTbl ),

    NAS_STA_TBL_ITEM( NAS_MSCC_BSR_STA_WAIT_HSD_SYSTEM_ACQUIRE_CNF_REACQ_HRPD,
                      g_astNasMsccBsrWaitHsdSystemAcquireCnfReAcqHrpdActTbl ),

    NAS_STA_TBL_ITEM( NAS_MSCC_BSR_STA_WAIT_MMC_BG_SEARCH_CNF,
                      g_astNasMsccBsrWaitMmcBgSearchCnfActTbl ),

    NAS_STA_TBL_ITEM( NAS_MSCC_BSR_STA_WAIT_MMC_STOP_BG_SEARCH_CNF,
                      g_astNasMsccBsrWaitMmcStopBgSearchCnfActTbl ),

    NAS_STA_TBL_ITEM( NAS_MSCC_BSR_STA_WAIT_HSD_QRY_HRPD_SYS_INFO_CNF,
                      g_astNasMsccBsrWaitHsdQryHrpdSysInfoCnfActTbl ),

    NAS_STA_TBL_ITEM( NAS_MSCC_BSR_STA_WAIT_MMC_POWER_SAVE_CNF,
                      g_astNasMsccBsrWaitMmcPowerSaveCnfActTbl ),

    NAS_STA_TBL_ITEM( NAS_MSCC_BSR_STA_WAIT_HSD_SYSTEM_ACQUIRE_CNF,
                      g_astNasMsccBsrWaitHsdSystemAcquireCnfActTbl ),

    NAS_STA_TBL_ITEM( NAS_MSCC_BSR_STA_WAIT_HSD_POWER_SAVE_CNF_REACQ_LTE,
                      g_astNasMsccBsrWaitHsdPowerSaveCnfReAcqLteActTbl ),

    NAS_STA_TBL_ITEM( NAS_MSCC_BSR_STA_WAIT_MMC_PLMN_SEARCH_CNF_REACQ_LTE,
                      g_astNasMsccBsrWaitMmcPlmnSearchCnfReAcqLteActTbl )

};

/*****************************************************************************
  3 函数定义
*****************************************************************************/

VOS_UINT32 NAS_MSCC_GetBsrStaTblSize(VOS_VOID)
{
    return (sizeof(g_astNasMsccBsrStaTbl)/sizeof(NAS_STA_STRU));
}


NAS_FSM_DESC_STRU * NAS_MSCC_GetBsrFsmDescAddr(VOS_VOID)
{
    return (&g_stNasMsccBsrFsmDesc);
}

#endif /***********end of FEATURE_CDMA*******************/

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

