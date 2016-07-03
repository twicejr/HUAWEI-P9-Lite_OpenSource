

/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "NasFsm.h"
#include "Nasrrcinterface.h"
#include "MmcGmmInterface.h"
#include "MmcMmInterface.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#endif
#include "UsimPsApi.h"
/* 删除ExtAppMmcInterface.h*/
#include "NasMmcFsmSwitchOn.h"
#include "NasMmcFsmSwitchOnTbl.h"
#include "NasMmcTimerMgmt.h"

#include "MsccMmcInterface.h"
#include "UsimPsInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_FSM_SWITCH_ON_TBL_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/* NAS MMC状态机数组:开机层二状态机名称 */
NAS_FSM_DESC_STRU                       g_stNasMmcSwitchOnFsmDesc;

/* NAS_MMC_L2_STA_SWITCH_ON动作表 */
NAS_ACT_STRU   g_astNasSwitchOnInitActTbl[]                =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_START_REQ,
                      NAS_MMC_RcvStartReq_SwitchOn_Init)
};

/* NAS_MMC_L1_STA_SWITCH_ON::NAS_MMC_L2_STA_WAIT_SIM_FILES_CNF动作表 */
NAS_ACT_STRU   g_astNasSwitchOnWaitSimFilesCnfActTbl[]      =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_USIM,
                      USIMM_READFILE_CNF,
                      NAS_MMC_RcvUsimGetFileRsp_SwitchOn_WaitSimFilesCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_READ_SIM_FILES,
                      NAS_MMC_RcvTiReadSimFilesExpired_SwitchOn_WaitSimFilesCnf)
};

/* NAS_MMC_L1_STA_SWITCH_ON::NAS_MMC_L2_STA_WAIT_MM_START_CNF动作表 */
NAS_ACT_STRU   g_astNasSwitchOnWaitMmStartCnfActTbl[]       =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMCMM_START_CNF,
                      NAS_MMC_RcvMmStartCnf_SwitchOn_WaitMmStartCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      MMCGMM_START_CNF,
                      NAS_MMC_RcvGmmStartCnf_SwitchOn_WaitMmStartCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_MM_START_CNF,
                      NAS_MMC_RcvTiMmStartCnfExpired_SwitchOn_WaitMmStartCnf)
};

/* NAS_MMC_L1_STA_SWITCH_ON::NAS_MMC_L2_STA_WAIT_GAS_START_CNF动作表 */
NAS_ACT_STRU   g_astNasSwitchOnWaitGasStartCnfActTbl[]       =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_START_CNF,
                      NAS_MMC_RcvGasStartCnf_SwitchOn_WaitGasStartCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_GAS_START_CNF,
                      NAS_MMC_RcvTiWaitGasStartCnfExpired_SwitchOn_WaitGasStartCnf),

};

/* NAS_MMC_L1_STA_SWITCH_ON::NAS_MMC_L2_STA_WAIT_WAS_START_CNF动作表 */
NAS_ACT_STRU   g_astNasSwitchOnWaitWasStartCnfActTbl[]       =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_START_CNF,
                      NAS_MMC_RcvWasStartCnf_SwitchOn_WaitWasStartCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_WAS_START_CNF,
                      NAS_MMC_RcvTiWaitWasStartCnfExpired_SwitchOn_WaitWasStartCnf),

};


#if   (FEATURE_ON == FEATURE_LTE)

/* NAS_MMC_L1_STA_SWITCH_ON::NAS_MMC_L2_STA_WAIT_L_START_CNF动作表 */
NAS_ACT_STRU   g_astNasSwitchOnWaitLStartCnfActTbl[]        =
{
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_START_CNF,
                      NAS_MMC_RcvLmmStartCnf_SwitchOn_WaitLStartCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_LMM_START_CNF,
                      NAS_MMC_RcvTiLmmStartCnfExpired_SwitchOn_WaitLStartCnf)
};

#endif


/* 协议栈开机L2状态机 */
NAS_STA_STRU g_astNasMmcSwitchOnStaTbl[] =
{
    /*****************定义在无任何网络时候的状态转移表**********************/
    NAS_STA_TBL_ITEM( NAS_MMC_SWITCH_ON_STA_SWITCH_ON_INIT,
                      g_astNasSwitchOnInitActTbl ),

    NAS_STA_TBL_ITEM( NAS_MMC_SWITCH_ON_STA_WAIT_SIM_FILES_CNF,
                      g_astNasSwitchOnWaitSimFilesCnfActTbl ),

    NAS_STA_TBL_ITEM( NAS_MMC_SWITCH_ON_STA_WAIT_MM_START_CNF,
                      g_astNasSwitchOnWaitMmStartCnfActTbl ),

    NAS_STA_TBL_ITEM( NAS_MMC_SWITCH_ON_STA_WAIT_GAS_START_CNF,
                      g_astNasSwitchOnWaitGasStartCnfActTbl ),

    NAS_STA_TBL_ITEM( NAS_MMC_SWITCH_ON_STA_WAIT_WAS_START_CNF,
                      g_astNasSwitchOnWaitWasStartCnfActTbl ),

#if   (FEATURE_ON == FEATURE_LTE)

    NAS_STA_TBL_ITEM( NAS_MMC_SWITCH_ON_STA_WAIT_L_START_CNF,
                      g_astNasSwitchOnWaitLStartCnfActTbl ),
#endif

};

/*****************************************************************************
  3 函数实现
*****************************************************************************/

VOS_UINT32 NAS_MMC_GetSwitchOnStaTblSize( VOS_VOID  )
{
    return (sizeof(g_astNasMmcSwitchOnStaTbl)/sizeof(NAS_STA_STRU));
}



NAS_FSM_DESC_STRU * NAS_MMC_GetSwitchOnFsmDescAddr(VOS_VOID)
{
    return (&g_stNasMmcSwitchOnFsmDesc);
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

