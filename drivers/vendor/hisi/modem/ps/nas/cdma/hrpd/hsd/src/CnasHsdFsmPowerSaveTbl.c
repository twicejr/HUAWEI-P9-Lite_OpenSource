/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasHsdFsmPowerOffTbl.c
  版 本 号   : 初稿
  作    者   : z00316370
  生成日期   : 2015年04月09日
  功能描述   : HRPD L2 关机状态机状态表
  函数列表   :
  修改历史   :
  1.日    期   : 2015年04月09日
    作    者   : z00316370
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "NasFsm.h"
#include "CnasHsdFsmPowerSave.h"
#include "CnasHsdFsmPowerSaveTbl.h"
#include "CnasHsdComFunc.h"
#include "hsd_mscc_pif.h"
#include "CnasHsdTimer.h"
#include "cas_hrpd_airlinkmgmt_nas_pif.h"
#include "hsm_hsd_pif.h"

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
/* CNAS HSD状态机数组:POWER_SAVE子状态机名称 */
NAS_FSM_DESC_STRU                       g_stCnasHsdPowerSaveFsmDesc;

/* CNAS_HSD_POWER_SAVE_STA_INIT状态下动作表 */
NAS_ACT_STRU g_astCnasHsdPowerSaveInitActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_POWER_SAVE_REQ,
                      CNAS_HSD_RcvMsccPowerSaveReq_PowerSave_Init),
};


/* CNAS_HSD_POWER_SAVE_STA_WAIT_CAS_OOC_CNF动作表 */
NAS_ACT_STRU g_astCnasHsdPowerSavewaitCasSuspendCnfActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_HALMP,
                      ID_CAS_CNAS_HRPD_SUSPEND_CNF,
                      CNAS_HSD_RcvCasSuspendCnf_PowerSave_WaitCasSuspendCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_HSD_WAIT_CAS_SUSPEND_CNF,
                      CNAS_HSD_RcvTiWaitCasSuspendCnfExpired_PowerSave_WaitCasSuspendCnf),

    NAS_ACT_TBL_ITEM(UEPS_PID_RRM,
                     ID_RRM_PS_STATUS_IND,
                     CNAS_HSD_RcvRrmStatusInd_PowerSave),
};

NAS_ACT_STRU g_astCnasHsdPowerSavewaitHsmPowerSaveCnfActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_HSM_HSD_POWER_SAVE_CNF,
                      CNAS_HSD_RcvHsmPowerSaveCnf_PowerSave_WaitHsmPowerSaveCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_HSD_WAIT_HSM_POWERSAVE_CNF,
                      CNAS_HSD_RcvTiWaitHsmPowerSaveCnfExpired_PowerSave_WaitHsmPowerSaveCnf),

    NAS_ACT_TBL_ITEM(UEPS_PID_RRM,
                     ID_RRM_PS_STATUS_IND,
                     CNAS_HSD_RcvRrmStatusInd_PowerSave),
};

/* POWER_SAVE状态机消息 状态表 */
NAS_STA_STRU g_astCnasHsdPowerSaveStaTbl[] =
{

    /*****************定义关机初始状态转移表**********************/
    NAS_STA_TBL_ITEM( CNAS_HSD_POWER_SAVE_STA_INIT,
                      g_astCnasHsdPowerSaveInitActTbl),

    /*****************定义CAS回复Suspend状态转移表**********************/
    NAS_STA_TBL_ITEM( CNAS_HSD_POWER_SAVE_STA_WAIT_CAS_SUSPEND_CNF,
                      g_astCnasHsdPowerSavewaitCasSuspendCnfActTbl),

    /*****************定义CAS回复Suspend状态转移表**********************/
    NAS_STA_TBL_ITEM( CNAS_HSD_POWER_SAVE_STA_WAIT_HSM_POWERSAVE_CNF,
                      g_astCnasHsdPowerSavewaitHsmPowerSaveCnfActTbl),

};

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 函 数 名  : CNAS_HSD_GetPowerSaveStaTblSize
 功能描述  : 获取PowerSave状态机的大小
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32:PowerSave状态机的大小
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年04月09日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_GetPowerSaveStaTblSize(VOS_VOID)
{
    return (sizeof(g_astCnasHsdPowerSaveStaTbl)/sizeof(NAS_STA_STRU));
}


/*****************************************************************************
 函 数 名  : CNAS_HSD_GetPowerSaveFsmDescAddr
 功能描述  : 获取PowerSave状态机的描述表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_FSM_DESC_STRU:指向关机状态机的描述表
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年04月09日
    作    者   : z00316370
    修改内容   : 新生成函数


*****************************************************************************/
NAS_FSM_DESC_STRU * CNAS_HSD_GetPowerSaveFsmDescAddr(VOS_VOID)
{
    return (&g_stCnasHsdPowerSaveFsmDesc);
}
/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



