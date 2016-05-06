


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "NasFsm.h"
#include  "NasMsccFsmSwitchOn.h"
#include  "NasMsccFsmSwitchOnTbl.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MSCC_FSM_SWITCH_ON_TBL_C


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
NAS_FSM_DESC_STRU                       g_stNasMsccSwitchOnFsmDesc;

/**************************************************************************/
/*新增状态动作处理表 */
/**************************************************************************/

/* NAS_MSCC_SWITCHON_STA_INIT Action table */
NAS_ACT_STRU        g_astNasMsccSwitchOnInitActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      ID_MMA_MSCC_START_REQ,
                      NAS_MSCC_RcvMmaStartReq_SwitchOn_Init)
};

/* NAS_MSCC_SWITCHON_STA_WAIT_CARD_READ_CNF Action table */
#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)
NAS_ACT_STRU        g_astNasMsccSwitchOnWaitCardReadCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_USIM,
                      USIMM_READFILE_CNF,
                      NAS_MSCC_RcvUsimmReadFileCnf_SwitchOn_WaitCardReadCnf ),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MSCC_WAIT_CARD_READ_CNF,
                      NAS_MSCC_RcvTiWaitCardReadTimerExpire_SwitchOn_WaitCardReadCnf )

};
#endif

#if (FEATURE_IMS == FEATURE_ON)

/* NAS_MSCC_SWITCHON_STA_WAIT_IMSA_START_CNF Action table */
NAS_ACT_STRU        g_astNasMsccSwitchOnWaitImsaStartCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( PS_PID_IMSA,
                      ID_IMSA_MSCC_START_CNF,
                      NAS_MSCC_RcvImsaStartCnf_SwitchOn_WaitImsaStartCnf ),


    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MSCC_WAIT_IMSA_START_CNF,
                      NAS_MSCC_RcvTiWaitImsaStartCnfExpired_SwitchOn_WaitImsaStartCnf )

};

#endif

/* NAS_MSCC_SWITCHON_STA_WAIT_MMC_START_CNF Action Table */
NAS_ACT_STRU        g_astNasMsccSwitchOnWaitMmcStartCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_START_CNF,
                      NAS_MSCC_RcvMmcStartCnf_SwitchOn_WaitMmcStartCnf ),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MSCC_WAIT_MMC_START_CNF,
                      NAS_MSCC_RcvTiWaitMmcStartCnfExpired_SwitchOn_WaitMmcStartCnf )

};


#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/* NAS_MSCC_SWITCHON_STA_WAIT_XSD_START_CNF Action table */
NAS_ACT_STRU        g_astNasMsccSWitchOnWaitXsdStartCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_XSD,
                      ID_XSD_MSCC_START_CNF,
                      NAS_MSCC_RcvXsdStartCnf_SwitchOn_WaitXsdStartCnf ),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MSCC_WAIT_XSD_START_CNF,
                      NAS_MSCC_RcvTiWaitXsdStartCnfExpired_SwitchOn_WaitXsdStartCnf )

};

/* NAS_MSCC_SWITCHON_STA_WAIT_HSD_START_CNF Action Table */
NAS_ACT_STRU        g_astNasMsccSwitchOnWaitHsdStartCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_MSCC_START_CNF,
                      NAS_MSCC_RcvHsdStartCnf_SwitchOn_WaitHsdStartCnf ),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MSCC_WAIT_HSD_START_CNF,
                      NAS_MSCC_RcvTiWaitHsdStartCnfExpired_SwitchOn_WaitHsdStartCnf )

};
#endif


/* NAS MSCC Switch On state table */
NAS_STA_STRU        g_astNasMsccSwitchOnStaTbl[]   =
{
    /* 手机模式状态机的初始化状态 */
    NAS_STA_TBL_ITEM( NAS_MSCC_SWITCHON_STA_INIT,
                       g_astNasMsccSwitchOnInitActTbl ),

#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)
    NAS_STA_TBL_ITEM( NAS_MSCC_SWITCHON_STA_WAIT_CARD_READ_CNF,
                      g_astNasMsccSwitchOnWaitCardReadCnfActTbl ),
#endif

#if (FEATURE_LTE == FEATURE_ON) && (FEATURE_IMS == FEATURE_ON)

    /* 等待IMSA的开机回复状态 */
    NAS_STA_TBL_ITEM( NAS_MSCC_SWITCHON_STA_WAIT_IMSA_START_CNF,
                      g_astNasMsccSwitchOnWaitImsaStartCnfActTbl ),

#endif

    /* 等待MMC的开机回复状态 */
    NAS_STA_TBL_ITEM( NAS_MSCC_SWITCHON_STA_WAIT_MMC_START_CNF,
                      g_astNasMsccSwitchOnWaitMmcStartCnfActTbl ),

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    /* 等待XSD的开机回复状态 */
    NAS_STA_TBL_ITEM( NAS_MSCC_SWITCHON_STA_WAIT_XSD_START_CNF,
                      g_astNasMsccSWitchOnWaitXsdStartCnfActTbl ),


    /* 等待HSD的开机回复状态 */
    NAS_STA_TBL_ITEM( NAS_MSCC_SWITCHON_STA_WAIT_HSD_START_CNF,
                      g_astNasMsccSwitchOnWaitHsdStartCnfActTbl )

#endif
};



VOS_UINT32 NAS_MSCC_GetSwitchOnStaTblSize(VOS_VOID)
{
    return (sizeof(g_astNasMsccSwitchOnStaTbl)/sizeof(NAS_STA_STRU));
}



NAS_FSM_DESC_STRU *NAS_MSCC_GetSwitchOnFsmDescAddr(VOS_VOID)
{
    return (&g_stNasMsccSwitchOnFsmDesc);
}



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


