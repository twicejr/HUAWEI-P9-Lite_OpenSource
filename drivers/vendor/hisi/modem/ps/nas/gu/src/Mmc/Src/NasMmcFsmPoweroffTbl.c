/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcFsmPowerOffTbl.c
  版 本 号   : 初稿
  作    者   : w00176964
  生成日期   : 2011年7月20日
  最近修改   :
  功能描述   : POWEROFF状态机状态机转移矩阵
  函数列表   :
  修改历史   :
  1.日    期   : 2011年7月20日
    作    者   : w00176964
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "NasFsm.h"
#include "MsccMmcInterface.h"
#include "Nasrrcinterface.h"
#include "MmcGmmInterface.h"
#include "MmcMmInterface.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#endif
/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, begin */
/* 删除ExtAppMmcInterface.h*/
/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, end */
#include "NasMmcFsmPowerOff.h"
#include "NasMmcFsmPoweroffTbl.h"
#include "NasMmcTimerMgmt.h"

/* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
#include "MsccMmcInterface.h"
/* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_FSM_POWER_OFF_TBL_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/* NAS MMC状态机数组:关机子状态机名称 */
NAS_FSM_DESC_STRU                       g_stNasMmcPowerOffFsmDesc;

/* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
/* NAS_MMC_FSM_L2_POWER_OFF::NAS_MMC_L2_STA_POWEROFF_INIT动作表 */
NAS_ACT_STRU   g_astNasPoweroffInitActTbl[]             =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_POWER_OFF_REQ,
                      NAS_MMC_RcvTafPowerOffReq_PowerOff_Init),

    /* Added by s00246516 for L-C互操作项目, 2014-01-28, Begin */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_POWER_SAVE_REQ,
                      NAS_MMC_RcvMsccPowerSaveReq_PowerOff_Init),
    /* Added by s00246516 for L-C互操作项目, 2014-01-28, End */

};
/* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

/* NAS_MMC_FSM_L2_POWER_OFF::NAS_MMC_L2_STA_WAIT_MM_POWEROFF_CNF动作表 */
NAS_ACT_STRU   g_astNasPoweroffWaitMmPoweroffCnfActTbl[]             =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMCMM_POWER_OFF_CNF,
                      NAS_MMC_RcvMmPowerOffCnf_PowerOff_WaitMmPoweroffCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      MMCGMM_POWER_OFF_CNF,
                      NAS_MMC_RcvGmmPowerOffCnf_PowerOff_WaitMmPoweroffCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_MM_POWEROFF_CNF,
                      NAS_MMC_RcvTiWaitMmPowerOffCnfExpired_PowerOff_WaitMmPowerOffCnf),
};

/* POWER OFF:等待主模关机回复状态表 */
NAS_ACT_STRU   g_astNasPoweroffWaitMasterModePowerOffCnfActTbl[]             =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_POWER_OFF_CNF,
                      NAS_MMC_RcvGasPowerOffCnf_PowerOff_WaitMasterModePowerOffCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_POWER_OFF_CNF,
                      NAS_MMC_RcvWasPowerOffCnf_PowerOff_WaitMasterModePowerOffCnf),

#if   (FEATURE_ON == FEATURE_LTE)

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_STOP_CNF,
                      NAS_MMC_RcvLmmStopCnf_PowerOff_WaitMasterModePowerOffCnf),
#endif

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_MASTER_MODE_POWEROFF_CNF,
                      NAS_MMC_RcvTiWaitMasterModePowerOffCnfExpired_PowerOff_WaitMasterModePowerOffCnf)
};


NAS_ACT_STRU   g_astNasPoweroffWaitSlaveModePowerOffCnfActTbl[]             =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_POWER_OFF_CNF,
                      NAS_MMC_RcvGasPowerOffCnf_PowerOff_WaitSlaveModePowerOffCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_POWER_OFF_CNF,
                      NAS_MMC_RcvWasPowerOffCnf_PowerOff_WaitSlaveModePowerOffCnf),

#if   (FEATURE_ON == FEATURE_LTE)

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_STOP_CNF,
                      NAS_MMC_RcvLmmStopCnf_PowerOff_WaitSlaveModePowerOffCnf),
#endif

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_SLAVE_MODE_POWEROFF_CNF,
                      NAS_MMC_RcvTiWaitSlaveModePowerOffCnfExpired_PowerOff_WaitSlaveModePowerOffCnf)
};


#if   (FEATURE_ON == FEATURE_LTE)

/* NAS_MMC_L1_STA_POWER_OFF::NAS_MMC_L2_STA_WAIT_LMM_USIM_STATUS_CNF动作表 */
NAS_ACT_STRU   g_astNasPoweroffWaitLmmUsimStatusCnfActTbl[]             =
{
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_USIM_STATUS_CNF,
                      NAS_MMC_RcvLmmUsimStatusCnf_PowerOff_WaitLmmUsimStatusCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_LMM_USIM_STATUS_CNF,
                      NAS_MMC_RcvTiWaitLmmUsimStatusExpired_PowerOff_WaitLmmUsimStatusCnf),
};

/* Added by s00246516 for L-C互操作项目, 2014-01-28, Begin */
NAS_ACT_STRU   g_astNasPoweroffWaitLmmSuspendCnfActTbl[]             =
{
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SUSPEND_CNF,
                      NAS_MMC_RcvLmmSuspendCnf_PowerOff_WaitLmmSuspendCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_LMM_SUSPEND_CNF,
                      NAS_MMC_RcvTiWaitLmmSuspendCnfExpired_PowerOff_WaitLmmSuspendCnf),
};
/* Added by s00246516 for L-C互操作项目, 2014-01-28, End */
#endif

NAS_ACT_STRU   g_astNasMmcPoweroffWaitEpsConnRelIndTbl[]               =
{
    /* L模注册的过程中会收到信令链接存在的标志需要处理 */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_STATUS_IND,
                      NAS_MMC_RcvLmmMmcStatusInd_PowerOff_WaitEpsConnRelInd),

    /* 等链接释放定时器超时 */
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_EPS_CONN_REL_IND,
                      NAS_MMC_RcvTiWaitEpsConnRelIndExpired_PowerOff_WaitEpsConnRelInd),

    /* 调用suspend状态机 */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SUSPEND_IND,
                      NAS_MMC_RcvLmmSuspendInd_PowerOff_WaitEpsConnRelInd),
};

/* NAS_MMC_POWER_OFF_STA_WAIT_RRC_CONN_REL_IND 动作表 */
NAS_ACT_STRU   g_astNasMmcPowerOffWaitCsPsConnRelActTbl[]              =
{
    /* 收到 GMM 的 SIGNALING_STATUS_IND 消息的处理 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      MMCGMM_SIGNALING_STATUS_IND,
                      NAS_MMC_RcvGmmSignalingStatusInd_PowerOff_WaitRrcConnRelInd),

    /* 收到 GMM 的的 TBF_REL_IND 消息的处理  */
    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      MMCGMM_TBF_REL_IND,
                      NAS_MMC_RcvGmmTbfRelInd_PowerOff_WaitRrcConnRelInd),

    /* 收到 MM 的 MMCMM_RR_CONN_INFO_IND 消息的处理  */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMCMM_RR_CONN_INFO_IND,
                      NAS_MMC_RcvMmConnInfoInd_PowerOff_WaitRrcConnRelInd),

    /* 收到 MM 的 RR_REL_IND 消息的处理  */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMCMM_RR_REL_IND,
                      NAS_MMC_RcvMmRrRelInd_PowerOff_WaitRrcConnRelInd),

    /* 收到 WAS 的 RRMM_REL_IND 消息的处理  */
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_REL_IND,
                      NAS_MMC_RcvRrMmRelInd_PowerOff_WaitRrcConnRelInd),

    /* 收到 WAS 的 RRMM_SUSPEND_IND 消息的处理  */
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SUSPEND_IND,
                      NAS_MMC_RcvWasSuspendInd_PowerOff_WaitRrcConnRelInd),

    /* 收到 GAS 的 RRMM_SUSPEND_IND 消息的处理  */
    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_SUSPEND_IND,
                      NAS_MMC_RcvGasSuspendInd_PowerOff_WaitRrcConnRelInd),

    /* 收到定时器超时消息的处理  */
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_RRC_CONN_REL,
                      NAS_MMC_RcvTiWaitRrcConnRelExpired_PowerOff_WaitRrcConnRelInd),

};

NAS_ACT_STRU   g_astNasMmcPowerOffWaitWasSuspendCnfActTbl[]             =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SUSPEND_CNF,
                      NAS_MMC_RcvRrMmSuspendCnf_PowerOff_WaitWasSuspendCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF,
                      NAS_MMC_RcvTiWaitAsSuspendCnfExpired_PowerOff_WaitAsSuspendCnf),
};

NAS_ACT_STRU   g_astNasMmcPowerOffWaitGasSuspendCnfActTbl[]             =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_SUSPEND_CNF,
                      NAS_MMC_RcvRrMmSuspendCnf_PowerOff_WaitGasSuspendCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF,
                      NAS_MMC_RcvTiWaitAsSuspendCnfExpired_PowerOff_WaitAsSuspendCnf),

};




/* 协议栈关机L2状态机 */
NAS_STA_STRU g_astNasMmcPowerOffStaTbl[] =
{
    /*****************定义在无任何网络时候的状态转移表**********************/
    NAS_STA_TBL_ITEM( NAS_MMC_POWER_OFF_STA_POWEROFF_INIT,
                      g_astNasPoweroffInitActTbl ),

    /*****************定义及关机到开机初始化状态转移表**********************/
    NAS_STA_TBL_ITEM( NAS_MMC_POWER_OFF_STA_WAIT_MM_POWEROFF_CNF,
                      g_astNasPoweroffWaitMmPoweroffCnfActTbl ),

    /*****************定义主模关机状态转移表**********************/
    NAS_STA_TBL_ITEM( NAS_MMC_POWER_OFF_STA_WAIT_MASTER_MODE_POWEROFF_CNF,
                      g_astNasPoweroffWaitMasterModePowerOffCnfActTbl ),

    /*****************定义从模关机状态转移表**********************/
    NAS_STA_TBL_ITEM( NAS_MMC_POWER_OFF_STA_WAIT_SLAVE_MODE_POWEROFF_CNF,
                      g_astNasPoweroffWaitSlaveModePowerOffCnfActTbl ),

#if   (FEATURE_ON == FEATURE_LTE)
    /*****************定义在驻留及限制驻留时候的状态转移表**********************/
    NAS_STA_TBL_ITEM( NAS_MMC_POWER_OFF_STA_WAIT_LMM_USIM_STATUS_CNF,
                      g_astNasPoweroffWaitLmmUsimStatusCnfActTbl ),

    /* Added by s00246516 for L-C互操作项目, 2014-01-28, Begin */
    NAS_STA_TBL_ITEM( NAS_MMC_POWER_OFF_STA_WAIT_LMM_SUSPEND_CNF,
                      g_astNasPoweroffWaitLmmSuspendCnfActTbl ),
    /* Added by s00246516 for L-C互操作项目, 2014-01-28, End */
#endif

    NAS_STA_TBL_ITEM( NAS_MMC_POWER_OFF_STA_WAIT_EPS_CONN_REL_IND,
                      g_astNasMmcPoweroffWaitEpsConnRelIndTbl ),

    /*  等待链接释放结果 */
    NAS_STA_TBL_ITEM( NAS_MMC_POWER_OFF_STA_WAIT_RRC_CONN_REL_IND,
                      g_astNasMmcPowerOffWaitCsPsConnRelActTbl ),

    NAS_STA_TBL_ITEM( NAS_MMC_POWER_OFF_STA_WAIT_GAS_SUSPEND_CNF,
                      g_astNasMmcPowerOffWaitGasSuspendCnfActTbl ),

    NAS_STA_TBL_ITEM( NAS_MMC_POWER_OFF_STA_WAIT_WAS_SUSPEND_CNF,
                      g_astNasMmcPowerOffWaitWasSuspendCnfActTbl ),

};


/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : NAS_MMC_GetPowerOffStaTblSize
 功能描述  : 获取关机状态机的大小
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32:关机状态机的大小
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月9日
    作    者   : zhoujun 40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_GetPowerOffStaTblSize( VOS_VOID  )
{
    return (sizeof(g_astNasMmcPowerOffStaTbl)/sizeof(NAS_STA_STRU));
}


/*****************************************************************************
 函 数 名  : NAS_MMC_GetPowerOffFsmDescAddr
 功能描述  : 获取关机状态机的描述表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_FSM_DESC_STRU:指向关机状态机的描述表
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月9日
    作    者   : zhoujun 40661
    修改内容   : 新生成函数

*****************************************************************************/
NAS_FSM_DESC_STRU * NAS_MMC_GetPowerOffFsmDescAddr(VOS_VOID)
{
    return (&g_stNasMmcPowerOffFsmDesc);
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

