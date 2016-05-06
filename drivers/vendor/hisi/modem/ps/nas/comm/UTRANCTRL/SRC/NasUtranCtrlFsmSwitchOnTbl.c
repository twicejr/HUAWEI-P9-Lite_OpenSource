/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasUtranCtrlFsmSwitchOnTbl.c
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
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#endif
#include "NasMmcTimerMgmt.h"
#include "NasUtranCtrlFsmSwitchOn.h"
#include "NasUtranCtrlFsmSwitchOnTbl.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_UTRANCTRL_FSM_SWITCHON_TBL_C

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/* NAS UtranCtrl状态机数组:开机层二状态机名称 */
NAS_FSM_DESC_STRU                       g_stNasUtranCtrlSwitchOnFsmDesc;

/* NAS_UTRANCTRL_FSM_SWITCH_ON::NAS_UTRANCTRL_SWITCH_ON_STA_SWITCH_ON_INIT */
NAS_ACT_STRU   g_astNasUtranCtrlSwitchOnInitActTbl[]                =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_START_CNF,
                      NAS_UTRANCTRL_RcvWasStartCnf_SwitchOn_Init),

    NAS_ACT_TBL_ITEM( TPS_PID_RRC,
                      RRMM_START_CNF,
                      NAS_UTRANCTRL_RcvTdStartCnf_SwitchOn_Init),

};

/* NAS_UTRANCTRL_FSM_SWITCH_ON::NAS_UTRANCTRL_SWITCH_ON_STA_WAIT_WAS_START_CNF动作表 */
NAS_ACT_STRU   g_astNasUtranCtrlSwitchOnWaitWasStartCnfActTbl[]       =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_START_CNF,
                      NAS_UTRANCTRL_RcvWasStartCnf_SwitchOn_WaitWasStartCnf),

    /* 丢弃非法消息 */
    NAS_ACT_TBL_ITEM( TPS_PID_RRC,
                      RRMM_START_CNF,
                      NAS_UTRANCTRL_RcvTdStartCnf_SwitchOn_WaitWasStartCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_UTRANCTRL_WAIT_WAS_START_CNF,
                      NAS_UTRANCTRL_RcvTiWaitWasStartCnfExpired_SwitchOn_WaitWasStartCnf),

};

/* NAS_UTRANCTRL_FSM_SWITCH_ON::NAS_UTRANCTRL_SWITCH_ON_STA_WAIT_TD_START_CNF动作表 */
NAS_ACT_STRU   g_astNasUtranCtrlSwitchOnWaitTdStartCnfActTbl[]       =
{
    NAS_ACT_TBL_ITEM( TPS_PID_RRC,
                      RRMM_START_CNF,
                      NAS_UTRANCTRL_RcvTdStartCnf_SwitchOn_WaitTdStartCnf),

    /* 丢弃非法消息 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_START_CNF,
                      NAS_UTRANCTRL_RcvWasStartCnf_SwitchOn_WaitTdStartCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_UTRANCTRL_WAIT_TD_START_CNF,
                      NAS_UTRANCTRL_RcvTiWaitTdStartCnfExpired_SwitchOn_WaitTdStartCnf),

};

/* 协议栈开机L2状态机 */
NAS_STA_STRU g_astNasUtranCtrlSwitchOnStaTbl[] =
{
    /*****************定义在无任何网络时候的状态转移表**********************/
    NAS_STA_TBL_ITEM( NAS_UTRANCTRL_SWITCH_ON_STA_INIT,
                      g_astNasUtranCtrlSwitchOnInitActTbl ),


    NAS_STA_TBL_ITEM( NAS_UTRANCTRL_SWITCH_ON_STA_WAIT_WAS_START_CNF,
                      g_astNasUtranCtrlSwitchOnWaitWasStartCnfActTbl ),

    NAS_STA_TBL_ITEM( NAS_UTRANCTRL_SWITCH_ON_STA_WAIT_TD_START_CNF,
                      g_astNasUtranCtrlSwitchOnWaitTdStartCnfActTbl ),
};

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_GetSwitchOnStaTblSize
 功能描述  : 获取开机状态机的大小
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32:开机状态机的大小
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月7日
    作    者   : w00167002
    修改内容   : V7R1C50_GUTL_PhaseII:新生成函数

*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_GetSwitchOnStaTblSize( VOS_VOID  )
{
    return (sizeof(g_astNasUtranCtrlSwitchOnStaTbl)/sizeof(NAS_STA_STRU));
}


/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_GetSwitchOnFsmDescAddr
 功能描述  : 获取开机状态机的描述表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_FSM_DESC_STRU:指向开机状态机的描述表
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月7日
    作    者   : w00167002
    修改内容   : V7R1C50_GUTL_PhaseII:新生成函数
*****************************************************************************/
NAS_FSM_DESC_STRU * NAS_UTRANCTRL_GetSwitchOnFsmDescAddr(VOS_VOID)
{
    return (&g_stNasUtranCtrlSwitchOnFsmDesc);
}

#endif  /* end of #if (FEATURE_ON == FEATURE_UE_MODE_TDS) */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

