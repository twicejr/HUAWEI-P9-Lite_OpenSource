/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcFsmSwitchOnTbl.c
  版 本 号   : 初稿
  作    者   : w00176964
  生成日期   : 2011年7月20日
  最近修改   :
  功能描述   : Switch on状态机状态转移矩阵
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
#include "Nasrrcinterface.h"
#include "MmcGmmInterface.h"
#include "MmcMmInterface.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#endif
#include "UsimPsApi.h"
/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, begin */
/* 删除ExtAppMmcInterface.h*/
/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, end */
#include "NasMmcFsmSwitchOn.h"
#include "NasMmcFsmSwitchOnTbl.h"
#include "NasMmcTimerMgmt.h"

/* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
#include "MsccMmcInterface.h"
/* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */
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

/* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
/* NAS_MMC_L2_STA_SWITCH_ON动作表 */
NAS_ACT_STRU   g_astNasSwitchOnInitActTbl[]                =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_START_REQ,
                      NAS_MMC_RcvStartReq_SwitchOn_Init)
};
/* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

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
/*****************************************************************************
 函 数 名  : NAS_MMC_GetSwitchOnStaTblSize
 功能描述  : 获取开机状态机的大小
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32:开机状态机的大小
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月9日
    作    者   : zhoujun 40661
    修改内容   : 新生成函数
  2.日    期   : 2011年7月18日
    作    者   : w00176964
    修改内容   : V7R1 PhaseII 调整
*****************************************************************************/
VOS_UINT32 NAS_MMC_GetSwitchOnStaTblSize( VOS_VOID  )
{
    return (sizeof(g_astNasMmcSwitchOnStaTbl)/sizeof(NAS_STA_STRU));
}


/*****************************************************************************
 函 数 名  : NAS_MMC_GetSwitchOnFsmDescAddr
 功能描述  : 获取开机状态机的描述表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_FSM_DESC_STRU:指向开机状态机的描述表
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月9日
    作    者   : zhoujun 40661
    修改内容   : 新生成函数
  2.日    期   : 2011年7月18日
    作    者   : w00176964
    修改内容   : V7R1 PhaseII 调整

*****************************************************************************/
NAS_FSM_DESC_STRU * NAS_MMC_GetSwitchOnFsmDescAddr(VOS_VOID)
{
    return (&g_stNasMmcSwitchOnFsmDesc);
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

