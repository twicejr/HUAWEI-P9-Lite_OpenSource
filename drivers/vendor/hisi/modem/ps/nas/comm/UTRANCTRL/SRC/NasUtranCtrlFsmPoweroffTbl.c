


/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "PsTypeDef.h"
#include "NasFsm.h"
#include "Nasrrcinterface.h"
#include "NasUtranCtrlFsmPowerOff.h"
#include "NasUtranCtrlFsmPoweroffTbl.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#endif
#include "NasMmcTimerMgmt.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_UTRANCTRL_FSM_POWEROFF_TBL_C

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/* NAS MMC状态机数组:关机子状态机名称 */
NAS_FSM_DESC_STRU                       g_stNasUtranCtrlPowerOffFsmDesc;


/* NAS_UTRANCTRL_FSM_POWER_OFF::NAS_UTRANCTRL_L2_STA_POWEROFF_INIT动作表 */
NAS_ACT_STRU   g_astNasUtranCtrlPoweroffInitActTbl[]             =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_POWER_OFF_CNF,
                      NAS_UTRANCTRL_RcvWasPowerOffCnf_PowerOff_Init),

    /* 收到WAS的关机回复超时消息 */
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_UTRANCTRL_WAIT_WAS_POWER_OFF_CNF,
                      NAS_UTRANCTRL_RcvTiWaitWasPowerOffCnfExpired_PowerOff_Init),

    NAS_ACT_TBL_ITEM( TPS_PID_RRC,
                      RRMM_POWER_OFF_CNF,
                      NAS_UTRANCTRL_RcvTdPowerOffCnf_PowerOff_Init),

    /* 收到TD的关机回复超时消息 */
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_UTRANCTRL_WAIT_TD_POWER_OFF_CNF,
                      NAS_UTRANCTRL_RcvTiWaitTdPowerOffCnfExpired_PowerOff_Init),

};

/* NAS_UTRANCTRL_FSM_POWER_OFF::NAS_UTRANCTRL_POWER_OFF_STA_WAIT_WAS_POWEROFF_CNF动作表 */
NAS_ACT_STRU   g_astNasUtranCtrlPoweroffWaitWasPowerOffCnfActTbl[]             =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_POWER_OFF_CNF,
                      NAS_UTRANCTRL_RcvWasPowerOffCnf_PowerOff_WaitWasPowerOffCnf),

    /* 丢弃异常消息 */
    NAS_ACT_TBL_ITEM( TPS_PID_RRC,
                      RRMM_POWER_OFF_CNF,
                      NAS_UTRANCTRL_RcvTdPowerOffCnf_PowerOff_WaitWasPowerOffCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_UTRANCTRL_WAIT_WAS_POWER_OFF_CNF,
                      NAS_UTRANCTRL_RcvTiWaitWasPowerOffCnfExpired_PowerOff_WaitWasPowerOffCnf),
};

/* NAS_UTRANCTRL_FSM_POWER_OFF::NAS_UTRANCTRL_POWER_OFF_STA_WAIT_TD_POWEROFF_CNF动作表 */
NAS_ACT_STRU   g_astNasUtranCtrlPoweroffWaitTdPowerOffCnfActTbl[]             =
{
    NAS_ACT_TBL_ITEM( TPS_PID_RRC,
                      RRMM_POWER_OFF_CNF,
                      NAS_UTRANCTRL_RcvTdPowerOffCnf_PowerOff_WaitTdPowerOffCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_POWER_OFF_CNF,
                      NAS_UTRANCTRL_RcvWasPowerOffCnf_PowerOff_WaitTdPowerOffCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_UTRANCTRL_WAIT_TD_POWER_OFF_CNF,
                      NAS_UTRANCTRL_RcvTiWaitTdPowerOffCnfExpired_PowerOff_WaitTdPowerOffCnf)
};




/* 协议栈关机L2状态机 */
NAS_STA_STRU g_astNasUtranCtrlPowerOffStaTbl[] =
{
    /*****************定义关机初始化时的状态转移表**********************/
    NAS_STA_TBL_ITEM( NAS_UTRANCTRL_POWER_OFF_STA_INIT,
                      g_astNasUtranCtrlPoweroffInitActTbl ),

    /*****************定义等待Was关机回复状态转移表**********************/
    NAS_STA_TBL_ITEM( NAS_UTRANCTRL_POWER_OFF_STA_WAIT_WAS_POWEROFF_CNF,
                      g_astNasUtranCtrlPoweroffWaitWasPowerOffCnfActTbl ),

    /*****************定义等待TD关机回复状态转移表**********************/
    NAS_STA_TBL_ITEM( NAS_UTRANCTRL_POWER_OFF_STA_WAIT_TD_POWEROFF_CNF,
                      g_astNasUtranCtrlPoweroffWaitTdPowerOffCnfActTbl ),
};


/*****************************************************************************
  3 函数实现
*****************************************************************************/


VOS_UINT32 NAS_UTRANCTRL_GetPowerOffStaTblSize( VOS_VOID  )
{
    return (sizeof(g_astNasUtranCtrlPowerOffStaTbl)/sizeof(NAS_STA_STRU));
}



NAS_FSM_DESC_STRU * NAS_UTRANCTRL_GetPowerOffFsmDescAddr(VOS_VOID)
{
    return (&g_stNasUtranCtrlPowerOffFsmDesc);
}

#endif  /* end of #if (FEATURE_ON == FEATURE_UE_MODE_TDS) */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



