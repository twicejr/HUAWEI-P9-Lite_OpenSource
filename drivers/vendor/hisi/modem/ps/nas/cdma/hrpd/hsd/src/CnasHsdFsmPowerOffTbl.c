/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasHsdFsmPowerOffTbl.c
  版 本 号   : 初稿
  作    者   : h00300778
  生成日期   : 2014年12月9日
  功能描述   : HRPD L2 关机状态机状态表
  函数列表   :
  修改历史   :
  1.日    期   : 2014年12月9日
    作    者   : h00300778
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "NasFsm.h"
#include "CnasHsdFsmPowerOff.h"
#include "CnasHsdFsmPowerOffTbl.h"
#include "CnasHsdComFunc.h"
#include "hsd_mscc_pif.h"
#include "hsm_hsd_pif.h"
#include "hsd_hlu_pif.h"
#include "CnasXsdTimer.h"
#include "cas_hrpd_airlinkmgmt_nas_pif.h"
#include "ehsm_hsd_pif.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSD_FSM_POWER_OFF_TBL_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/* CNAS HSD状态机数组:关机子状态机名称 */
NAS_FSM_DESC_STRU                       g_stCnasHsdPowerOffFsmDesc;

/* CNAS_HSD_POWER_OFF_STA_INIT状态下动作表 */
NAS_ACT_STRU g_astCnasHsdPoweroffInitActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_POWER_OFF_REQ,
                      CNAS_HSD_RcvMsccPowerOffReq_PowerOff_Init),
};

/* CNAS_HSD_POWER_OFF_STA_WAIT_EHSM_POWEROFF_CNF动作表 */
NAS_ACT_STRU g_astCnasHsdPoweroffWaitEhsmPoweroffCnfActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_EHSM,
                      ID_EHSM_HSD_POWER_OFF_CNF,
                      CNAS_HSD_RcvEhsmPowerOffCnf_PowerOff_WaitEhsmPowerOffCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_HSD_WAIT_EHSM_POWEROFF_CNF,
                      CNAS_HSD_RcvTiWaitEhsmPowerOffCnfExpired_PowerOff_WaitEhsmPowerOffCnf)
};

/* CNAS_HSD_POWER_OFF_STA_WAIT_HSM_POWEROFF_CNF动作表 */
NAS_ACT_STRU g_astCnasHsdPoweroffWaitHsmPoweroffCnfActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_HSM_HSD_POWEROFF_CNF,
                      CNAS_HSD_RcvHsmPowerOffCnf_PowerOff_WaitHsmPowerOffCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_HSD_WAIT_HSM_POWEROFF_CNF,
                      CNAS_HSD_RcvTiWaitHsmPowerOffCnfExpired_PowerOff_WaitHsmPowerOffCnf)
};

/* CNAS_HSD_POWER_OFF_STA_WAIT_HLU_POWEROFF_CNF动作表 */
NAS_ACT_STRU g_astCnasHsdPoweroffWaitHluPowerOffCnfActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_HLU,
                      ID_HLU_HSD_POWER_OFF_CNF,
                      CNAS_HSD_RcvHluPowerOffCnf_PowerOff_WaitHluPowerOffCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_HSD_WAIT_HLU_POWEROFF_CNF,
                      CNAS_HSD_RcvTiWaitHluPowerOffCnfExpired_PowerOff_WaitHluPowerOffCnf)
};

/* CNAS_HSD_POWER_OFF_STA_WAIT_CAS_POWEROFF_CNF动作表 */
NAS_ACT_STRU g_astCnasHsdPoweroffWaitCasPowerOffCnfActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_HALMP,
                      ID_CAS_CNAS_HRPD_POWER_OFF_CNF,
                      CNAS_HSD_RcvCasPowerOffCnf_PowerOff_WaitCasPowerOffCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_HSD_WAIT_CAS_POWEROFF_CNF,
                      CNAS_HSD_RcvTiWaitCasPowerOffCnfExpired_PowerOff_WaitCasPowerOffCnf)
};

/* 关机状态机消息 状态表 */
NAS_STA_STRU g_astCnasHsdPowerOffStaTbl[] =
{
    /*****************定义关机初始状态转移表**********************/
    NAS_STA_TBL_ITEM( CNAS_HSD_POWER_OFF_STA_INIT,
                      g_astCnasHsdPoweroffInitActTbl),

    /*****************定义EHSM关机状态转移表**********************/
    NAS_STA_TBL_ITEM( CNAS_HSD_POWER_OFF_STA_WAIT_EHSM_POWEROFF_CNF,
                      g_astCnasHsdPoweroffWaitEhsmPoweroffCnfActTbl ),


    /*****************定义HSM关机状态转移表**********************/
    NAS_STA_TBL_ITEM( CNAS_HSD_POWER_OFF_STA_WAIT_HSM_POWEROFF_CNF,
                      g_astCnasHsdPoweroffWaitHsmPoweroffCnfActTbl ),

    /*****************定义HLU关机状态转移表**********************/
    NAS_STA_TBL_ITEM( CNAS_HSD_POWER_OFF_STA_WAIT_HLU_POWEROFF_CNF,
                      g_astCnasHsdPoweroffWaitHluPowerOffCnfActTbl),

    /*****************定义CAS关机状态转移表**********************/
    NAS_STA_TBL_ITEM( CNAS_HSD_POWER_OFF_STA_WAIT_CAS_POWEROFF_CNF,
                      g_astCnasHsdPoweroffWaitCasPowerOffCnfActTbl)

};

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 函 数 名  : CNAS_HSD_GetPowerOffStaTblSize
 功能描述  : 获取关机状态机的大小
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32:关机状态机的大小
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月9日
    作    者   : h00300778
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_GetPowerOffStaTblSize(VOS_VOID)
{
    return (sizeof(g_astCnasHsdPowerOffStaTbl)/sizeof(NAS_STA_STRU));
}


/*****************************************************************************
 函 数 名  : CNAS_HSD_GetPowerOffFsmDescAddr
 功能描述  : 获取关机状态机的描述表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_FSM_DESC_STRU:指向关机状态机的描述表
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月9日
    作    者   : h00300778
    修改内容   : 新生成函数


*****************************************************************************/
NAS_FSM_DESC_STRU * CNAS_HSD_GetPowerOffFsmDescAddr(VOS_VOID)
{
    return (&g_stCnasHsdPowerOffFsmDesc);
}
/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



