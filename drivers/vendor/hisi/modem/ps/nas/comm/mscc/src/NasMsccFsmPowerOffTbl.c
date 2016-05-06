/******************************************************************************

            Copyright 2014, Huawei Technologies Co. Ltd.

 ******************************************************************************
File Name       :   NasMsccFsmPowerOffTbl.c
Author          :   k902809
Version         :
Date            :   2015-01-30
Description     :   Contains FSM tables and act tables for MSCC Power-off flow FSM.
                    Interface definistions
Function list   :
History         :
    1) Date :
       Author:
       Modification:
******************************************************************************/

/*****************************************************************************
  1. Including header files
*****************************************************************************/
#include "NasFsm.h"
#include "NasComm.h"
#include "NasMsccFsmPowerOff.h"
#include "MmaMsccInterface.h"
#include "NasMsccFsmPowerOffTbl.h"
#include "MsccMmcInterface.h"

#if (FEATURE_IMS == FEATURE_ON)
#include "ImsaMsccInterface.h"
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#include "xsd_mscc_pif.h"
#include "hsd_mscc_pif.h"

#endif
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MSCC_FSM_POWER_OFF_TBL_C


/*****************************************************************************
  2. Global Variable.
*****************************************************************************/

NAS_FSM_DESC_STRU                       g_stNasMsccPowerOffFsmDesc;

/**************************************************************************/
/* 3. List of action tables */
/**************************************************************************/

/* NAS_MSCC_POWER_OFF_STA_INIT act table */
NAS_ACT_STRU        g_astNasMsccPowerOffInitActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      ID_MMA_MSCC_POWER_OFF_REQ,
                      NAS_MSCC_RcvMmaPowerOffReq_PowerOff_Init),

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MSCC_SCAN_TIMER,
                      NAS_MSCC_RcvTiScanTimerExpired_PowerOff_Init),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      ID_MMA_MSCC_CDMA_MO_CALL_SUCCESS_NTF,
                      NAS_MSCC_RcvMmaCdmaMoCallSuccessNtf_PowerOff_Init),
#endif


};

#if (FEATURE_IMS == FEATURE_ON)
/* NAS_MSCC_POWER_OFF_STA_WAIT_IMSA_POWER_OFF_CNF act table */
NAS_ACT_STRU        g_astNasMsccPowerOffWaitImsaPowerOffCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( PS_PID_IMSA,
                      ID_IMSA_MSCC_STOP_CNF,
                      NAS_MSCC_RcvImsaPowerOffCnf_PowerOff_WaitImsaPowerOffCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MSCC_WAIT_IMSA_POWER_OFF_CNF,
                      NAS_MSCC_RcvTiWaitImsaPowerOffCnfExpired_PowerOff_WaitImsaPowerOffCnf )

};
#endif

/* NAS_MSCC_POWER_OFF_STA_WAIT_MMC_POWER_OFF_CNF act table */
NAS_ACT_STRU        g_astNasMsccPowerOffWaitMmcPowerOffCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_POWER_OFF_CNF,
                      NAS_MSCC_RcvMmcPowerOffCnf_PowerOff_WaitMmcPowerOffCnf ),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MSCC_WAIT_MMC_POWER_OFF_CNF,
                      NAS_MSCC_RcvTiWaitMmcPowerOffCnfExpired_PowerOff_WaitMmcPowerOffCnf )
};

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/* NAS_MSCC_POWER_OFF_STA_WAIT_XSD_POWER_OFF_CNF act table */
NAS_ACT_STRU        g_astNasMsccPowerOffWaitXsdPowerOffCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_XSD,
                      ID_XSD_MSCC_POWER_OFF_CNF,
                      NAS_MSCC_RcvXsdPowerOffCnf_PowerOff_WaitXsdPowerOffCnf ),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MSCC_WAIT_XSD_POWER_OFF_CNF,
                      NAS_MSCC_RcvTiWaitXsdPowerOffCnfExpired_PowerOff_WaitXsdPowerOffCnf )

};
/* NAS_MSCC_POWER_OFF_STA_WAIT_HSD_POWER_OFF_CNF act table */
NAS_ACT_STRU        g_astNasMsccPowerOffWaitHsdPowerOffCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_MSCC_POWER_OFF_CNF,
                      NAS_MSCC_RcvHsdPowerOffCnf_PowerOff_WaitHsdPowerOffCnf ),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MSCC_WAIT_HSD_POWER_OFF_CNF,
                      NAS_MSCC_RcvTiWaitHsdPowerOffCnfExpired_PowerOff_WaitHsdPowerOffCnf )

};

/* NAS_MSCC_POWER_OFF_STA_WAIT_CL_POWER_SAVE_CNF act table */
NAS_ACT_STRU        g_astNasMsccPowerOffWaitCLPowerSaveCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_XSD,
                      ID_XSD_MSCC_POWER_SAVE_CNF,
                      NAS_MSCC_RcvXsdPowerSaveCnf_PowerOff_WaitCLPowerSaveCnf ),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_POWER_SAVE_CNF,
                      NAS_MSCC_RcvMmcPowerSaveCnf_PowerOff_WaitCLPowerSaveCnf ),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_MSCC_POWER_SAVE_CNF,
                      NAS_MSCC_RcvHsdPowerSaveCnf_PowerOff_WaitCLPowerSaveCnf ),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MSCC_WAIT_CL_POWER_SAVE_CNF,
                      NAS_MSCC_RcvTiWaitCLPowerSaveCnfExpired_PowerOff_WaitCLPowerSaveCnf )

};

NAS_ACT_STRU        g_astNasMsccPowerOffWaitHrpdLtePowerSaveCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_POWER_SAVE_CNF,
                      NAS_MSCC_RcvMmcPowerSaveCnf_PowerOff_WaitHrpdLtePowerSaveCnf ),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_MSCC_POWER_SAVE_CNF,
                      NAS_MSCC_RcvHsdPowerSaveCnf_PowerOff_WaitHrpdLtePowerSaveCnf ),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MSCC_WAIT_CL_POWER_SAVE_CNF,
                      NAS_MSCC_RcvTiWaitCLPowerSaveCnfExpired_PowerOff_WaitCLPowerSaveCnf )

};

#endif

/* NAS MSCC Power off state table */
NAS_STA_STRU        g_astNasMsccPowerOffStaTbl[]   =
{
    NAS_STA_TBL_ITEM( NAS_MSCC_POWER_OFF_STA_INIT,
                      g_astNasMsccPowerOffInitActTbl ),

#if (FEATURE_LTE == FEATURE_ON) && (FEATURE_IMS == FEATURE_ON)

    NAS_STA_TBL_ITEM( NAS_MSCC_POWER_OFF_STA_WAIT_IMSA_POWER_OFF_CNF,
                      g_astNasMsccPowerOffWaitImsaPowerOffCnfActTbl ),

#endif

    NAS_STA_TBL_ITEM( NAS_MSCC_POWER_OFF_STA_WAIT_MMC_POWER_OFF_CNF,
                      g_astNasMsccPowerOffWaitMmcPowerOffCnfActTbl ),

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

    NAS_STA_TBL_ITEM( NAS_MSCC_POWER_OFF_STA_WAIT_XSD_POWER_OFF_CNF,
                      g_astNasMsccPowerOffWaitXsdPowerOffCnfActTbl ),

    NAS_STA_TBL_ITEM( NAS_MSCC_POWER_OFF_STA_WAIT_HSD_POWER_OFF_CNF,
                      g_astNasMsccPowerOffWaitHsdPowerOffCnfActTbl ),


    NAS_STA_TBL_ITEM( NAS_MSCC_POWER_OFF_STA_WAIT_CL_POWER_SAVE_CNF,
                      g_astNasMsccPowerOffWaitCLPowerSaveCnfActTbl ),

    NAS_STA_TBL_ITEM( NAS_MSCC_POWER_OFF_STA_WAIT_HRPD_LTE_POWER_SAVE_CNF,
                      g_astNasMsccPowerOffWaitHrpdLtePowerSaveCnfActTbl ),


#endif
};


VOS_UINT32 NAS_MSCC_GetPowerOffStaTblSize(VOS_VOID)
{
    return (sizeof(g_astNasMsccPowerOffStaTbl)/sizeof(NAS_STA_STRU));
}


NAS_FSM_DESC_STRU * NAS_MSCC_GetPowerOffFsmDescAddr(VOS_VOID)
{
    return (&g_stNasMsccPowerOffFsmDesc);
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

