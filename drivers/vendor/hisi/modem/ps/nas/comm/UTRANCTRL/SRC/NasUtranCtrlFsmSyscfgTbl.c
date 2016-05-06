/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasUtranCtrlFsmSyscfgTbl.c
  版 本 号   : 初稿
  作    者   : w00167002
  生成日期   : 2012年8月7日
  最近修改   :
  功能描述   : SYSCFG状态机
  函数列表   :
  修改历史   :
  1.日    期   : 2012年8月7日
    作    者   : w00167002
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "NasFsm.h"
#include "Nasrrcinterface.h"
#include "NasUtranCtrlFsmSyscfg.h"
#include "NasUtranCtrlFsmSyscfgTbl.h"
#include "NasMmcTimerMgmt.h"

/* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
#include "MsccMmcInterface.h"
/* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_UTRANCTRL_FSM_SYSCFG_TBL_C

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/* NAS MMC状态机数组:SYSCFG子层状态机名称 */
NAS_FSM_DESC_STRU                       g_stNasUtranCtrlSysCfgFsmDesc;


/* NAS_UTRANCTRL_SYSCFG_STA_INIT动作表  */
NAS_ACT_STRU   g_astNasUtranCtrlSyscfgInitActTbl[]             =
{
    /* 收到Was的syscfg设置回复消息 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SYS_CFG_CNF,
                      NAS_UTRANCTRL_RcvWasSysCfgCnf_SysCfg_Init),

    /* 收到Td的syscfg设置回复消息 */
    NAS_ACT_TBL_ITEM( TPS_PID_RRC,
                      RRMM_SYS_CFG_CNF,
                      NAS_UTRANCTRL_RcvTdSysCfgCnf_SysCfg_Init),

};

/* NAS_UTRANCTRL_SYSCFG_STA_WAIT_WAS_SYSCFG_CNF动作表 */
NAS_ACT_STRU   g_astNasUtranCtrlSyscfgWaitWasSyscfgCnfActTbl[]          =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SYS_CFG_CNF,
                      NAS_UTRANCTRL_RcvWasSysCfgCnf_SysCfg_WaitWasSysCfgCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SUSPEND_IND,
                      NAS_UTRANCTRL_RcvWasSuspendInd_SysCfg_WaitWasSysCfgCnf),

    /* 异常消息处理 */
    NAS_ACT_TBL_ITEM( TPS_PID_RRC,
                      RRMM_SYS_CFG_CNF,
                      NAS_UTRANCTRL_RcvTdSysCfgCnf_SysCfg_WaitWasSysCfgCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_UTRANCTRL_WAIT_WAS_SYSCFG_CNF,
                      NAS_UTRANCTRL_RcvTiWasSysCfgCnfExpired_SysCfg_WaitWasSysCfgCnf),
};

/* NAS_UTRANCTRL_SYSCFG_STA_WAIT_TD_SYSCFG_CNF动作表 */
NAS_ACT_STRU   g_astNasUtranCtrlSyscfgWaitTdSyscfgCnfActTbl[]          =
{
    NAS_ACT_TBL_ITEM( TPS_PID_RRC,
                      RRMM_SYS_CFG_CNF,
                      NAS_UTRANCTRL_RcvTdSysCfgCnf_SysCfg_WaitTdSysCfgCnf),

    NAS_ACT_TBL_ITEM( TPS_PID_RRC,
                      RRMM_SUSPEND_IND,
                      NAS_UTRANCTRL_RcvTdSuspendInd_SysCfg_WaitTdSysCfgCnf),

    /* 异常消息处理 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SYS_CFG_CNF,
                      NAS_UTRANCTRL_RcvWasSysCfgCnf_SysCfg_WaitTdSysCfgCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_UTRANCTRL_WAIT_TD_SYSCFG_CNF,
                      NAS_UTRANCTRL_RcvTiTdSysCfgCnfExpired_SysCfg_WaitTdSysCfgCnf),
};


/* SYSCFG状态机 */
NAS_STA_STRU g_astNasUtranCtrlSyscfgStaTbl[] =
{
     /* Syscfg初始状态 */
    NAS_STA_TBL_ITEM(NAS_UTRANCTRL_SYSCFG_STA_INIT,
                     g_astNasUtranCtrlSyscfgInitActTbl),

    /* SYSCFG过程，等待WAS的RRMM_SYS_CFG_CNF设置回复消息 */
    NAS_STA_TBL_ITEM(NAS_UTRANCTRL_SYSCFG_STA_WAIT_WAS_SYSCFG_CNF,
                     g_astNasUtranCtrlSyscfgWaitWasSyscfgCnfActTbl),

    /* SYSCFG过程，等待TD的RRMM_SYS_CFG_CNF设置回复消息 */
    NAS_STA_TBL_ITEM(NAS_UTRANCTRL_SYSCFG_STA_WAIT_TD_SYSCFG_CNF,
                     g_astNasUtranCtrlSyscfgWaitTdSyscfgCnfActTbl),

};


/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_GetSysCfgStaTblSize
 功能描述  : 获取SYSCFG状态机的大小
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32:SYSCFG状态机的大小
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月8日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_GetSysCfgStaTblSize( VOS_VOID  )
{
    return (sizeof(g_astNasUtranCtrlSyscfgStaTbl)/sizeof(NAS_STA_STRU));
}



/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_GetPlmnSelectionFsmDescAddr
 功能描述  : 获取自动搜网状态机的描述表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_FSM_DESC_STRU:指向PLMN SELECTION状态机的描述表
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月8日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/

NAS_FSM_DESC_STRU * NAS_UTRANCTRL_GetSysCfgFsmDescAddr(VOS_VOID)
{
    return (&g_stNasUtranCtrlSysCfgFsmDesc);
}


#endif  /* end of #if (FEATURE_ON == FEATURE_UE_MODE_TDS) */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

