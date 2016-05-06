


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "NasFsm.h"
#include  "NasMsccFsmSysCfg.h"
#include  "NasMsccFsmSysCfgTbl.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MSCC_FSM_SYS_CFG_TBL_C


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
NAS_FSM_DESC_STRU                       g_stNasMsccSysCfgFsmDesc;

/**************************************************************************/
/*新增状态动作处理表 */
/**************************************************************************/

/* NAS_MSCC_SYSCFG_STA_INIT Action table */
NAS_ACT_STRU        g_astNasMsccSysCfgInitActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      ID_MMA_MSCC_SYS_CFG_SET_REQ,
                      NAS_MSCC_RcvMmaSysCfgReq_SysCfg_Init)
};

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/* NAS_MSCC_SYSCFG_STA_WAIT_XSD_POWER_SAVE_CNF Action Table */
NAS_ACT_STRU        g_astNasMsccSysCfgWaitXsdPowerSaveCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_XSD,
                      ID_XSD_MSCC_POWER_SAVE_CNF,
                      NAS_MSCC_RcvXsdPowerSaveCnf_SysCfg_WaitXsdPowerSaveCnf ),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MSCC_WAIT_XSD_POWER_SAVE_CNF,
                      NAS_MSCC_RcvTiWaitXsdPowerSaveCnfExpired_SysCfg_WaitXsdPowerSaveCnf )

};

/* NAS_MSCC_SYSCFG_STA_WAIT_HSD_POWER_SAVE_CNF Action Table */
NAS_ACT_STRU        g_astNasMsccSysCfgWaitHsdPowerSaveCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_MSCC_POWER_SAVE_CNF,
                      NAS_MSCC_RcvHsdPowerSaveCnf_SysCfg_WaitHsdPowerSaveCnf ),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MSCC_WAIT_HSD_POWER_SAVE_CNF,
                      NAS_MSCC_RcvTiWaitHsdPowerSaveCnfExpired_SysCfg_WaitHsdPowerSaveCnf )

};
#endif

/* NAS_MSCC_SYSCFG_STA_WAIT_MMC_POWER_SAVE_CNF Action Table */
NAS_ACT_STRU        g_astNasMsccSysCfgWaitMmcPowerSaveCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_POWER_SAVE_CNF,
                      NAS_MSCC_RcvMmcPowerSaveCnf_SysCfg_WaitMmcPowerSaveCnf ),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MSCC_WAIT_MMC_POWER_SAVE_CNF,
                      NAS_MSCC_RcvTiWaitMmcPowerSaveCnfExpired_SysCfg_WaitMmcPowerSaveCnf )

};

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/* NAS_MSCC_SYSCFG_STA_WAIT_XSD_SYS_CFG_CNF Action Table */
NAS_ACT_STRU        g_astNasMsccSysCfgWaitXsdSysCfgCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_XSD,
                      ID_XSD_MSCC_SYS_CFG_CNF,
                      NAS_MSCC_RcvXsdSysCfgCnf_SysCfg_WaitXsdSysCfgCnf ),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MSCC_WAIT_XSD_SYS_CFG_CNF,
                      NAS_MSCC_RcvTiWaitXsdSysCfgCnfExpired_SysCfg_WaitXsdSysCfgCnf )

};

/* NAS_MSCC_SYSCFG_STA_WAIT_HSD_SYS_CFG_CNF Action Table */
NAS_ACT_STRU        g_astNasMsccSysCfgWaitHsdSysCfgCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_MSCC_SYS_CFG_CNF,
                      NAS_MSCC_RcvHsdSysCfgCnf_SysCfg_WaitHsdSysCfgCnf ),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MSCC_WAIT_HSD_SYS_CFG_CNF,
                      NAS_MSCC_RcvTiWaitHsdSysCfgCnfExpired_SysCfg_WaitHsdSysCfgCnf )

};
#endif

/* NAS_MSCC_SYSCFG_STA_WAIT_MMC_SYS_CFG_CNF Action Table */
NAS_ACT_STRU        g_astNasMsccSysCfgWaitMmcSysCfgCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_SYS_CFG_CNF,
                      NAS_MSCC_RcvMmcSysCfgCnf_SysCfg_WaitMmcSysCfgCnf ),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MSCC_WAIT_MMC_SYS_CFG_CNF,
                      NAS_MSCC_RcvTiWaitMmcSysCfgCnfExpired_SysCfg_WaitMmcSysCfgCnf )

};




/* NAS MSCC System config state table */
NAS_STA_STRU        g_astNasMsccSysCfgStaTbl[]   =
{

    /* Initial state fro system config FSM */
    NAS_STA_TBL_ITEM( NAS_MSCC_SYSCFG_STA_INIT,
                       g_astNasMsccSysCfgInitActTbl ),

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    /* MSCC Waits for Power Save confirm from XSD in System config FSM */
    NAS_STA_TBL_ITEM( NAS_MSCC_SYSCFG_STA_WAIT_XSD_POWER_SAVE_CNF,
                       g_astNasMsccSysCfgWaitXsdPowerSaveCnfActTbl ),

    /* MSCC Waits for Power Save confirm from HSD in System config FSM */
    NAS_STA_TBL_ITEM( NAS_MSCC_SYSCFG_STA_WAIT_HSD_POWER_SAVE_CNF,
                       g_astNasMsccSysCfgWaitHsdPowerSaveCnfActTbl ),
#endif

    /* MSCC Waits for Power Save confirm from MMC in System config FSM */
    NAS_STA_TBL_ITEM( NAS_MSCC_SYSCFG_STA_WAIT_MMC_POWER_SAVE_CNF,
                       g_astNasMsccSysCfgWaitMmcPowerSaveCnfActTbl ),

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    /* MSCC Waits for System Config confirm from XSD in System config FSM */
    NAS_STA_TBL_ITEM( NAS_MSCC_SYSCFG_STA_WAIT_XSD_SYS_CFG_CNF,
                       g_astNasMsccSysCfgWaitXsdSysCfgCnfActTbl ),

    /* MSCC Waits for System Config confirm from HSD in System config FSM */
    NAS_STA_TBL_ITEM( NAS_MSCC_SYSCFG_STA_WAIT_HSD_SYS_CFG_CNF,
                       g_astNasMsccSysCfgWaitHsdSysCfgCnfActTbl ),
#endif

    /* MSCC Waits for System Config confirm from MMC in System config FSM */
    NAS_STA_TBL_ITEM( NAS_MSCC_SYSCFG_STA_WAIT_MMC_SYS_CFG_CNF,
                       g_astNasMsccSysCfgWaitMmcSysCfgCnfActTbl )
};



VOS_UINT32 NAS_MSCC_GetSysCfgStaTblSize(VOS_VOID)
{
    return (sizeof(g_astNasMsccSysCfgStaTbl)/sizeof(NAS_STA_STRU));
}



NAS_FSM_DESC_STRU *NAS_MSCC_GetSysCfgFsmDescAddr(VOS_VOID)
{
    return (&g_stNasMsccSysCfgFsmDesc);
}



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



