/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXsdFsmPowerOffTbl.c
  版 本 号   : 初稿
  作    者   : y00245242
  生成日期   : 2014年07月03日
  功能描述   : 1X SD L2 关机状态机状态表
  函数列表   :
  修改历史   :
  1.日    期   : 2014年07月03日
    作    者   : y00245242
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "NasFsm.h"
#include "CnasXsdFsmPowerOff.h"
#include "CnasXsdFsmPowerOffTbl.h"
#include "CnasXsdComFunc.h"
#include "cas_1x_control_initialstate_nas_pif.h"
#include "cas_1x_control_main_nas_pif.h"
#include "xsd_xcc_pif.h"
#include "CnasXsdSndInternalMsg.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XSD_FSM_POWER_OFF_TBL_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/* CNAS XSD状态机数组:关机子状态机名称 */
NAS_FSM_DESC_STRU                       g_stCnasXsdPowerOffFsmDesc;

/* CNAS_XSD_POWER_OFF_STA_INIT状态下动作表 */
NAS_ACT_STRU g_astCnasXsdPoweroffInitActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_POWER_OFF_REQ,
                      CNAS_XSD_RcvMsccPowerOffReq_PowerOff_Init),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_POWER_SAVE_REQ,
                      CNAS_XSD_RcvMsccPowerSaveReq_PowerOff_Init)
};

/* CNAS_XSD_POWER_OFF_STA_WAIT_XCC_POWEROFF_CNF动作表 */
NAS_ACT_STRU g_astCnasXsdPoweroffWaitXccPoweroffCnfActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_XCC,
                      ID_XCC_XSD_POWER_OFF_CNF,
                      CNAS_XSD_RcvXccPowerOffCnf_PowerOff_WaitXccPowerOffCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_SYSTEM_DETERMIN_IND,
                      CNAS_XSD_RcvCasSysDeterminInd_PowerOff_WaitXccPowerOffCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_XCC,
                      ID_XCC_XSD_DEREGISTER_IND,
                      CNAS_XSD_RcvXccDeregisterInd_PowerOff_WaitXccPowerOffCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_WAIT_XCC_POWEROFF_CNF,
                      CNAS_XSD_RcvTiWaitXccPowerOffCnfExpired_PowerOff_WaitXccPowerOffCnf)
};


/* CNAS_XSD_POWER_OFF_STA_WAIT_XREG_POWEROFF_CNF动作表 */
NAS_ACT_STRU g_astCnasXsdPoweroffWaitXregPowerOffCnfActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_XREG,
                      ID_XREG_XSD_POWER_OFF_CNF,
                      CNAS_XSD_RcvXregPowerOffCnf_PowerOff_WaitXregPowerOffCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_WAIT_XREG_POWEROFF_CNF,
                      CNAS_XSD_RcvTiWaitXregPowerOffCnfExpired_PowerOff_WaitXregPowerOffCnf)
};

/* CNAS_XSD_POWER_OFF_STA_WAIT_CAS_POWEROFF_CNF动作表 */
NAS_ACT_STRU g_astCnasXsdPoweroffWaitCasPowerOffCnfActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_POWER_OFF_CNF,
                      CNAS_XSD_RcvCasPowerOffCnf_PowerOff_WaitCasPowerOffCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_WAIT_CAS_POWEROFF_CNF,
                      CNAS_XSD_RcvTiWaitCasPowerOffCnfExpired_PowerOff_WaitCasPowerOffCnf)
};

/* CNAS_XSD_POWER_OFF_STA_WAIT_CAS_SYS_DETERMIN_IND动作表 */
NAS_ACT_STRU g_astCnasXsdPoweroffWaitCasSysDeterminIndActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_SYSTEM_DETERMIN_IND,
                      CNAS_XSD_RcvCasSysDeterminInd_PowerOff_WaitCasSysDeterminInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_WAIT_CAS_SYSTEM_DETERMIN_IND,
                      CNAS_XSD_RcvTiWaitCasSysDeterminIndExpired_PowerOff_WaitCasSysDeterminInd)
};

/* CNAS_XSD_POWER_OFF_STA_WAIT_XSD_SYSTEM_ACQUIRE_RSLT_CNF动作表 */
NAS_ACT_STRU g_astCnasXsdPoweroffWaitXsdSystemAcquireRsltCnfActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_XSD,
                      ID_CNAS_XSD_XSD_SYSTEM_ACQUIRED_REQ,
                      CNAS_XSD_RcvInterXsdSystemAcquiredReq_PowerOff_WaitXsdSystemAcquireRsltCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_XSD,
                      ID_CNAS_XSD_XSD_SYSTEM_ACQUIRED_RSLT_CNF,
                      CNAS_XSD_RcvXsdSystemAcquiredRsltCnf_PowerOff_WaitXsdSystemAcquireRsltCnf)
};

/* CNAS_XSD_POWER_OFF_STA_WAIT_CAS_OOC_CNF Act Table */
NAS_ACT_STRU g_astCnasXsdPoweroffWaitCasSuspendCnfActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_SUSPEND_CNF,
                      CNAS_XSD_RcvCasSuspendCnf_PowerOff_WaitCasSuspendCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_WAIT_CAS_SUSPEND_CNF,
                      CNAS_XSD_RcvTiWaitCasSuspendCnfExpired_PowerOff_WaitCasSuspendCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_RRM,
                      ID_RRM_PS_STATUS_IND,
                      CNAS_XSD_RcvRrmStatusInd_PowerOff_WaitCasSuspendCnf)


};

/* 关机状态机消息 状态表 */
NAS_STA_STRU g_astCnasXsdPowerOffStaTbl[] =
{
    /*****************定义关机初始状态转移表**********************/
    NAS_STA_TBL_ITEM( CNAS_XSD_POWER_OFF_STA_INIT,
                      g_astCnasXsdPoweroffInitActTbl),

    /*****************定义XCC关机状态转移表**********************/
    NAS_STA_TBL_ITEM( CNAS_XSD_POWER_OFF_STA_WAIT_XCC_POWEROFF_CNF,
                      g_astCnasXsdPoweroffWaitXccPoweroffCnfActTbl ),

    /*****************定义XREG关机状态转移表**********************/
    NAS_STA_TBL_ITEM( CNAS_XSD_POWER_OFF_STA_WAIT_XREG_POWEROFF_CNF,
                      g_astCnasXsdPoweroffWaitXregPowerOffCnfActTbl),

    /*****************定义CAS关机状态转移表**********************/
    NAS_STA_TBL_ITEM( CNAS_XSD_POWER_OFF_STA_WAIT_CAS_POWEROFF_CNF,
                      g_astCnasXsdPoweroffWaitCasPowerOffCnfActTbl),

    /*****************定义等待CAS的SD指示转移表*********************/
    NAS_STA_TBL_ITEM( CNAS_XSD_POWER_OFF_STA_WAIT_CAS_SYS_DETERMIN_IND,
                      g_astCnasXsdPoweroffWaitCasSysDeterminIndActTbl),

    /*****************定义等待XSD的系统捕获结果转移表*********************/
    NAS_STA_TBL_ITEM( CNAS_XSD_POWER_OFF_STA_WAIT_XSD_SYSTEM_ACQUIRE_RSLT_CNF,
                      g_astCnasXsdPoweroffWaitXsdSystemAcquireRsltCnfActTbl),

    /***************** Wait for CAS OOC Cnf State for Power Save Process in XSD *********************/
    NAS_STA_TBL_ITEM( CNAS_XSD_POWER_OFF_STA_WAIT_CAS_SUSPEND_CNF,
                      g_astCnasXsdPoweroffWaitCasSuspendCnfActTbl)

};

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 函 数 名  : CNAS_XSD_GetPowerOffStaTblSize
 功能描述  : 获取关机状态机的大小
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32:关机状态机的大小
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月4日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_GetPowerOffStaTblSize(VOS_VOID)
{
    return (sizeof(g_astCnasXsdPowerOffStaTbl)/sizeof(NAS_STA_STRU));
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_GetPowerOffFsmDescAddr
 功能描述  : 获取关机状态机的描述表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_FSM_DESC_STRU:指向关机状态机的描述表
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月4日
    作    者   : h00246512
    修改内容   : 新生成函数


*****************************************************************************/
NAS_FSM_DESC_STRU * CNAS_XSD_GetPowerOffFsmDescAddr(VOS_VOID)
{
    return (&g_stCnasXsdPowerOffFsmDesc);
}
/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



