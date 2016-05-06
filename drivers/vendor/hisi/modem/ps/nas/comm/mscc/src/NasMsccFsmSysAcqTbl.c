


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "NasFsm.h"
#include  "NasMsccFsmSysAcq.h"
#include  "NasMsccFsmSysAcqTbl.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MSCC_FSM_SYS_ACQ_TBL_C
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
NAS_FSM_DESC_STRU                       g_stNasMsccSysAcqFsmDesc;

/**************************************************************************/
/*新增状态动作处理表 */
/**************************************************************************/
/* NAS_MSCC_SYSACQ_STA_INIT Action table */
NAS_ACT_STRU        g_astNasMsccSysAcqInitActTbl[]   =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_NAS_MSCC_MSCC_SYS_ACQ_REQ,
                      NAS_MSCC_RcvMsccSysAcqReq_SysAcq_Init)
};


/* NAS_MSCC_SYSACQ_STA_WAIT_HSD_ACQUIRE_CNF Action Table */
NAS_ACT_STRU        g_astNasMsccSysAcqWaitHsdAcqCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_MSCC_SYSTEM_ACQUIRE_CNF,
                      NAS_MSCC_RcvHsdSysAcqCnf_SysAcq_WaitHsdSysAcqCnf ),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_NAS_MSCC_MSCC_ABORT_FSM_REQ,
                      NAS_MSCC_RcvMsccAbortFsmReq_SysAcq_WaitHsdSysAcqCnf ),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_MSCC_SYSTEM_SYNC_IND,
                      NAS_MSCC_RcvHsdSysSyncInd_SysAcq_WaitHsdSysAcqCnf ),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MSCC_WAIT_HSD_ACQUIRE_CNF,
                      NAS_MSCC_RcvTiWaitHsdSysAcqCnfExpired_SysAcq_WaitHsdSysAcqCnf )

};

/* NAS_MSCC_SYSACQ_STA_WAIT_HSD_POWER_SAVE_CNF Action Table */
NAS_ACT_STRU        g_astNasMsccSysAcqWaitHsdPowerSaveCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_MSCC_POWER_SAVE_CNF,
                      NAS_MSCC_RcvHsdPowerSaveCnf_SysAcq_WaitHsdPowerSaveCnf ),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_NAS_MSCC_MSCC_ABORT_FSM_REQ,
                      NAS_MSCC_RcvMsccAbortFsmReq_SysAcq_WaitHsdPowerSaveCnf ),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MSCC_WAIT_HSD_POWER_SAVE_CNF,
                      NAS_MSCC_RcvTiWaitHsdPowerSaveCnfExpired_SysAcq_WaitHsdPowerSaveCnf )

};

/* NAS_MSCC_SYSACQ_STA_WAIT_MMC_PLMN_SEARCH_CNF Action Table */
NAS_ACT_STRU        g_astNasMsccSysAcqWaitMmcPlmnSrchCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_PLMN_SELECTION_RLST_IND,
                      NAS_MSCC_RcvMmcPlmnSrchCnf_SysAcq_WaitMmcPlmnSrchCnf ),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_NAS_MSCC_MSCC_ABORT_FSM_REQ,
                      NAS_MSCC_RcvMsccAbortFsmReq_SysAcq_WaitMmcPlmnSrchCnf ),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_INTERSYS_START_IND,
                      NAS_MSCC_RcvMmcInterSysStartInd_SysAcq_WaitMmcPlmnSrchCnf ),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_NAS_MSCC_MSCC_CL_INTERSYS_RSLT_CNF,
                      NAS_MSCC_RcvMsccCLInterSysRsltCnf_SysAcq_WaitMmcPlmnSrchCnf ),
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MSCC_WAIT_MMC_PLMN_SEARCH_CNF,
                      NAS_MSCC_RcvTiWaitMmcPlmnSrchCnfExpired_SysAcq_WaitMmcPlmnSrchCnf )

};

/* NAS_MSCC_SYSACQ_STA_WAIT_MMC_POWER_SAVE_CNF Action Table */
NAS_ACT_STRU        g_astNasMsccSysAcqWaitMmcPowerSaveCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_POWER_SAVE_CNF,
                      NAS_MSCC_RcvMmcPowerSaveCnf_SysAcq_WaitMmcPowerSaveCnf ),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_NAS_MSCC_MSCC_ABORT_FSM_REQ,
                      NAS_MSCC_RcvMsccAbortFsmReq_SysAcq_WaitMmcPowerSaveCnf ),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MSCC_WAIT_MMC_POWER_SAVE_CNF,
                      NAS_MSCC_RcvTiWaitMmcPowerSaveCnfExpired_SysAcq_WaitMmcPowerSaveCnf )

};

/* NAS_MSCC_SYSACQ_STA_WAIT_INIT_LOC_INFO_IND Action Table */
NAS_ACT_STRU        g_astNasMsccSysAcqWaitInitlocInfoIndActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_ACQ_CNF,
                      NAS_MSCC_RcvMmcAcqCnf_SysAcq_WaitInitlocInfoInd ),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_NAS_MSCC_MSCC_ABORT_FSM_REQ,
                      NAS_MSCC_RcvMsccAbortFsmReq_SysAcq_WaitInitlocInfoInd ),

    NAS_ACT_TBL_ITEM( UEPS_PID_XSD,
                      ID_XSD_MSCC_1X_SYSTEM_SERVICE_INFO_IND,
                      NAS_MSCC_RcvXsd1xSystemServiceInfoInd_SysAcq_WaitInitlocInfoInd ),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MSCC_WAIT_INIT_LOC_INFO_IND,
                      NAS_MSCC_RcvTiInitLocInfoIndExpired_SysAcq_WaitInitlocInfoInd )


};

/* NAS MSCC System Acquire state table */
NAS_STA_STRU        g_astNasMsccSysAcqStaTbl[]   =
{
    NAS_STA_TBL_ITEM( NAS_MSCC_SYSACQ_STA_INIT,
                      g_astNasMsccSysAcqInitActTbl ),

    NAS_STA_TBL_ITEM( NAS_MSCC_SYSACQ_STA_WAIT_HSD_ACQUIRE_CNF,
                      g_astNasMsccSysAcqWaitHsdAcqCnfActTbl ),

    NAS_STA_TBL_ITEM( NAS_MSCC_SYSACQ_STA_WAIT_HSD_POWER_SAVE_CNF,
                      g_astNasMsccSysAcqWaitHsdPowerSaveCnfActTbl ),

    NAS_STA_TBL_ITEM( NAS_MSCC_SYSACQ_STA_WAIT_MMC_PLMN_SEARCH_CNF,
                      g_astNasMsccSysAcqWaitMmcPlmnSrchCnfActTbl ),

    NAS_STA_TBL_ITEM( NAS_MSCC_SYSACQ_STA_WAIT_MMC_POWER_SAVE_CNF,
                      g_astNasMsccSysAcqWaitMmcPowerSaveCnfActTbl ),

    NAS_STA_TBL_ITEM( NAS_MSCC_SYSACQ_STA_WAIT_INIT_LOC_INFO_IND,
                      g_astNasMsccSysAcqWaitInitlocInfoIndActTbl ),

};



VOS_UINT32 NAS_MSCC_GetSysAcqStaTblSize(VOS_VOID)
{
    return (sizeof(g_astNasMsccSysAcqStaTbl)/sizeof(NAS_STA_STRU));
}



NAS_FSM_DESC_STRU *NAS_MSCC_GetSysAcqFsmDescAddr(VOS_VOID)
{
    return (&g_stNasMsccSysAcqFsmDesc);
}

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



