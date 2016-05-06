/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasUtralCtrlFsmModeChangeTbl.c
  版 本 号   : 初稿
  作    者   : s00217060
  生成日期   : 2012年8月7日
  最近修改   :
  功能描述   : UTRAN控制模块模式改变状态转移表
  函数列表   :
  修改历史   :
  1.日    期   : 2012年8月7日
    作    者   : s00217060
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "PsTypeDef.h"
#include "NasMmcMain.h"
#include "Nasrrcinterface.h"
#include "NasUtranCtrlFsmModeChangeTbl.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#endif

#include "NasUtranCtrlCtx.h"
#include "NasUtranCtrlFsmModeChange.h"
/* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
#include "MsccMmcInterface.h"
/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, begin */
/* 删除ExtAppMmcInterface.h*/
/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, end */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NASUTRANCTRLFSMMODECHANGETBL_C


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_TDS)

/* UTRANCTRL模块的模式变更状态机 */
NAS_FSM_DESC_STRU                       g_stNasUtranCtrlModeChangeFsmDesc;

/**************************************************************************/
/*新增状态动作处理表 */
/**************************************************************************/

/* NAS_UTRANCTRL_Mode_Change_STA_INIT 动作表 */
NAS_ACT_STRU        g_astNasUtranCtrlModeChangeInitActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SYS_INFO_IND,
                      NAS_UTRANCTRL_RcvWasSysInfo_ModeChange_Init),

    NAS_ACT_TBL_ITEM( TPS_PID_RRC,
                      RRMM_SYS_INFO_IND,
                      NAS_UTRANCTRL_RcvTdSysInfo_ModeChange_Init),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      GRRMM_SYS_INFO_IND,
                      NAS_UTRANCTRL_RcvGasSysInfo_ModeChange_Init),

#if (FEATURE_ON == FEATURE_LTE)
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SYS_INFO_IND,
                      NAS_UTRANCTRL_RcvLmmSysInfo_ModeChange_Init)
#endif
};

/* NAS_UTRANCTRL_MODE_CHANGE_STA_WAIT_SlaveMode_CNF 动作表 */
NAS_ACT_STRU        g_astNasUtranCtrlModeChangeWaitSlaveModeCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_UTRAN_MODE_CNF,
                      NAS_UTRANCTRL_RcvWasUtranModeCnf_ModeChange_WaitSlaveModeCnf ),

    NAS_ACT_TBL_ITEM( TPS_PID_RRC,
                      RRMM_UTRAN_MODE_CNF,
                      NAS_UTRANCTRL_RcvTdUtranModeCnf_ModeChange_WaitSlaveModeCnf ),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_UTRAN_MODE_CNF,
                      NAS_UTRANCTRL_RcvGasUtranModeCnf_ModeChange_WaitSlaveModeCnf ),

#if (FEATURE_ON == FEATURE_LTE)
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_UTRAN_MODE_CNF,
                      NAS_UTRANCTRL_RcvLmmUtranModeCnf_ModeChange_WaitSlaveModeCnf ),
#endif

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_UTRANCTRL_WAIT_SLAVEMODE_UTRAN_MODE_CNF,
                      NAS_UTRANCTRL_RcvTiWaitSlaveModeUtranModeCnfExpired_ModeChange_WaitSlaveModeCnf )
};

/* NAS_UTRANCTRL_MODE_CHANGE_STA_WAIT_MASTERMODE_CNF 动作表 */
NAS_ACT_STRU        g_astNasUtranCtrlModeChangeWaitMasterModeCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_UTRAN_MODE_CNF,
                      NAS_UTRANCTRL_RcvMasterModeCnf_ModeChange_WaitMasterModeCnf ),

    NAS_ACT_TBL_ITEM( TPS_PID_RRC,
                      RRMM_UTRAN_MODE_CNF,
                      NAS_UTRANCTRL_RcvMasterModeCnf_ModeChange_WaitMasterModeCnf ),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_UTRAN_MODE_CNF,
                      NAS_UTRANCTRL_RcvMasterModeCnf_ModeChange_WaitMasterModeCnf ),

#if (FEATURE_ON == FEATURE_LTE)
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_UTRAN_MODE_CNF,
                      NAS_UTRANCTRL_RcvMasterModeCnf_ModeChange_WaitMasterModeCnf ),
#endif

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_UTRANCTRL_WAIT_MASTERMODE_UTRAN_MODE_CNF,
                      NAS_UTRANCTRL_RcvTiWaitMasterModeCnfExpired_ModeChange_WaitMasterModeCnf )
};

#if(FEATURE_ON == FEATURE_TDS_WCDMA_DYNAMIC_LOAD)
NAS_ACT_STRU        g_astNasUtranCtrlModeChangeWaitMasterModeRelCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_UTRAN_MODE_CNF,
                      NAS_UTRANCTRL_RcvGasMasterModeRelCnf_ModeChange_WaitMasterModeRelCnf ),

#if (FEATURE_ON == FEATURE_LTE)
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_UTRAN_MODE_CNF,
                      NAS_UTRANCTRL_RcvLmmMasterModeRelCnf_ModeChange_WaitMasterModeRelCnf ),
#endif

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_UTRANCTRL_WAIT_MASTERMODE_UTRAN_MODE_REL_CNF,
                      NAS_UTRANCTRL_RcvTiWaitMasterModeRelCnfExpired_ModeChange_WaitMasterModeRelCnf )
};
#endif


/* 模式变更状态机处理的消息 状态表 */
NAS_STA_STRU        g_astNasUtranCtrlModeChangeStaTbl[]   =
{
    /* 模式变更状态机初始化状态 */
    NAS_STA_TBL_ITEM( NAS_UTRANCTRL_MODE_CHANGE_STA_INIT,
                      g_astNasUtranCtrlModeChangeInitActTbl ),

    /* 模式变更状态机等待从模回复状态 */
    NAS_STA_TBL_ITEM( NAS_UTRANCTRL_MODE_CHANGE_STA_WAIT_SLAVEMODE_CNF,
                      g_astNasUtranCtrlModeChangeWaitSlaveModeCnfActTbl ),

    /* 模式变更状态机等待主模回复状态 */
    NAS_STA_TBL_ITEM( NAS_UTRANCTRL_MODE_CHANGE_STA_WAIT_MASTERMODE_CNF,
                      g_astNasUtranCtrlModeChangeWaitMasterModeCnfActTbl ),

#if (FEATURE_ON == FEATURE_TDS_WCDMA_DYNAMIC_LOAD)
    /* 模式变更状态机等待主模释放回复状态 */
    NAS_STA_TBL_ITEM( NAS_UTRANCTRL_MODE_CHANGE_STA_WAIT_MASTERMODE_REL_CNF,
                      g_astNasUtranCtrlModeChangeWaitMasterModeRelCnfActTbl )
#endif
};

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_GetModeChangeStaTblSize
 功能描述  : 获取适配层模式变更状态机的大小
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32:适配层模式变更状态机的大小
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月9日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_GetModeChangeStaTblSize(VOS_VOID)
{
    return (sizeof(g_astNasUtranCtrlModeChangeStaTbl)/sizeof(NAS_STA_STRU));
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_GetModeChangeFsmDescAddr
 功能描述  : 获取适配层模式变更状态机的描述表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_FSM_DESC_STRU:指向适配层模式变更状态机的描述表
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月9日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
NAS_FSM_DESC_STRU * NAS_UTRANCTRL_GetModeChangeFsmDescAddr(VOS_VOID)
{
    return (&g_stNasUtranCtrlModeChangeFsmDesc);
}

#endif





#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

