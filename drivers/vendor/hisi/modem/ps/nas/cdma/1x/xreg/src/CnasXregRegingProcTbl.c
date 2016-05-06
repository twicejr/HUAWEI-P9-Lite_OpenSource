/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXregRegingProcTbl.c
  版 本 号   : 初稿
  作    者   : y00245242
  生成日期   : 2014年07月03日
  功能描述   : 1X SD L2开机状态机事件函数处理
  函数列表   :
  修改历史   :
  1.日    期   : 2014年07月03日
    作    者   : y00245242
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "CnasXregRegingProcTbl.h"
#include "CnasXregSndInternalMsg.h"
#include "cas_1x_access_ctrl_proc_nas_pif.h"
#include "CnasXregTimer.h"



#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XREG_REGING_PROC_TBL_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/* CNAS XREG状态机数组:关机子状态机名称 */
NAS_FSM_DESC_STRU                       g_stCnasXregRegingFsmDesc;

/* CNAS_XREG_REGING_STA_INIT状态下动作表 */
NAS_ACT_STRU g_astCnasXregRegingInitActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_XREG,
                      ID_CNAS_XREG_XREG_REG_REQ,
                      CNAS_XREG_RcvRegReq_Reging_Init),
};

/* CNAS_XREG_REGING_WAIT_EST_CNF动作表 */
NAS_ACT_STRU g_astCnasXregRegingWaitEstCnfActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_XREG,
                      ID_CNAS_XREG_ABORT_FSM_REQ,
                      CNAS_XREG_RcvAbortFsm_Reging_WaitEstCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_EST_CNF,
                      CNAS_XREG_RcvEstCnf_Reging_WaitEstCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_REG_ABORT_IND,
                      CNAS_XREG_RcvAbortInd_Reging_WaitEstCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XREG_TIMER_ESTCNF_PT,
                      CNAS_XREG_RcvTimeOut_Reging_WaitEstCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XREG_TIMER_PWROFF_ESTCNF_PT,
                      CNAS_XREG_RcvPwrOffTimeOut_Reging_WaitEstCnf),
};

/* CNAS_XREG_REGING_WAIT_ABORT_IND动作表 */
NAS_ACT_STRU g_astCnasXregRegingWaitAbortIndActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_REG_ABORT_IND,
                      CNAS_XREG_RcvAbortInd_Reging_WaitAbortInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XREG_TIMER_ABORTCNF_PT,
                      CNAS_XREG_RcvTimeOut_Reging_WaitAbortInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XREG_TIMER_PWROFF_ESTCNF_PT,
                      CNAS_XREG_RcvPwrOffTimeOut_Reging_WaitEstCnf),
};

/* Reging状态机消息 状态表 */
NAS_STA_STRU g_astCnasXregRegingStaTbl[] =
{
    /*****************定义开机初始状态转移表**********************/
    NAS_STA_TBL_ITEM( CNAS_XREG_REGING_STA_INIT,
                      g_astCnasXregRegingInitActTbl),

    /*****************定义等待XREG等待EST回复状态转移表**********************/
    NAS_STA_TBL_ITEM( CNAS_XREG_REGING_WAIT_EST_CNF,
                      g_astCnasXregRegingWaitEstCnfActTbl ),

    /*****************定义等待XREG等待ABORT回复消息状态转移表**********************/
    NAS_STA_TBL_ITEM( CNAS_XREG_REGING_WAIT_ABORT_IND,
                      g_astCnasXregRegingWaitAbortIndActTbl)
};

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 函 数 名  : CNAS_XREG_GetRegingStaTblSize
 功能描述  : 获取开机状态机的大小
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32:开机状态机的大小
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月4日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XREG_GetRegingStaTblSize(VOS_VOID)
{
    return (sizeof(g_astCnasXregRegingStaTbl)/sizeof(NAS_STA_STRU));
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_GetRegingFsmDescAddr
 功能描述  : 获取开机状态机的描述表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_FSM_DESC_STRU:指向开机状态机的描述表
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月4日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
NAS_FSM_DESC_STRU * CNAS_XREG_GetRegingFsmDescAddr(VOS_VOID)
{
    return (&g_stCnasXregRegingFsmDesc);
}
/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



