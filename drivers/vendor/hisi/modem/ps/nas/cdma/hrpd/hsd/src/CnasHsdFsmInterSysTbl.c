/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasHsdFsmInterSysTbl.c
  版 本 号   : 初稿
  作    者   : z00316370
  生成日期   : 2015年06月03日
  功能描述   : HRPD L2 异系统状态表
  函数列表   :
  修改历史   :
  1.日    期   : 2015年06月03日
    作    者   : z00316370
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "NasFsm.h"
#include "CnasHsdFsmInterSys.h"
#include "CnasHsdFsmInterSysTbl.h"
#include "CnasHsdComFunc.h"
#include "hsd_mscc_pif.h"
#include "CnasHsdTimer.h"
#include "cas_hrpd_airlinkmgmt_nas_pif.h"
#include "CnasHsdSndInternalMsg.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSD_FSM_INTER_SYS_TBL_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/* CNAS HSD状态机数组:INTER_SYS子状态机名称 */
NAS_FSM_DESC_STRU                       g_stCnasHsdInterSysFsmDesc;

/* CNAS_HSD_INTER_SYS_STA_INIT状态下动作表 */
NAS_ACT_STRU g_astCnasHsdInterSysInitActTbl[] =
{
    /* 从LTE切换到HRPD */
    NAS_ACT_TBL_ITEM( UEPS_PID_HALMP,
                      ID_CAS_CNAS_HRPD_IRAT_FROM_LTE_NTF,
                      CNAS_HSD_RcvHsdIratFromLteNtf_InterSys_Init),

    /* 从HRPD切换到LTE */
    NAS_ACT_TBL_ITEM(UEPS_PID_HALMP,
                     ID_CAS_CNAS_HRPD_SUSPEND_IND,
                     CNAS_HSD_RcvCasSuspendInd_InterSys_Init),
};

/* 切换到HRPD系统时等待CAS上报Ohm状态机 */
NAS_ACT_STRU g_astCnasHsdInterSysWaitOhmIndActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_HSP,
                      ID_CAS_CNAS_HRPD_OVERHEAD_MSG_IND,
                      CNAS_HSD_RcvCasOhmInd_InterSys_WaitCasOhmInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_HSD_WAIT_CAS_OHM_IND,
                      CNAS_HSD_RcvTiWaitCasOhmIndExpired_InterSys_WaitCasOhmInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_POWER_SAVE_REQ,
                      CNAS_HSD_RcvMsccPowerSaveReq_InterSys_WaitCasOhmInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_POWER_OFF_REQ,
                      CNAS_HSD_RcvMsccPowerOffReq_InterSys_WaitCasOhmInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_DATA_CALL_REDIAL_SYS_ACQ_REQ,
                      CNAS_HSD_RcvMsccDataCallReq_InterSys_WaitCasOhmInd),

    /* 本迭代SYS_CFG不会打断流程，不用考虑SYS_CFG */

    NAS_ACT_TBL_ITEM( UEPS_PID_HALMP,
                      ID_CAS_CNAS_HRPD_NETWORK_LOST_IND,
                      CNAS_HSD_RcvCasNetworkLost_InterSys_WaitCasOhmInd),
};

NAS_ACT_STRU g_astCnasHsdInterSysWaitIratOrResumeActTbl[] =
{
    NAS_ACT_TBL_ITEM(UEPS_PID_HALMP,
                     ID_CAS_CNAS_HRPD_IRAT_TO_LTE_NTF,
                     CNAS_HSD_RcvCasIratToLte_InterSys_WaitIratOrResume),

    NAS_ACT_TBL_ITEM(UEPS_PID_HALMP,
                     ID_CAS_CNAS_HRPD_RESUME_IND,
                     CNAS_HSD_RcvCasResumeInd_InterSys_WaitIratOrResume),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_HSD_WAIT_CAS_IRAT_OR_RESUME_IND,
                      CNAS_HSD_RcvTiWaitIratOrResumeExpired_InterSys_WaitIratOrResume),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_POWER_SAVE_REQ,
                      CNAS_HSD_RcvMsccPowerSaveReq_InterSys_WaitIratOrResume),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_POWER_OFF_REQ,
                      CNAS_HSD_RcvMsccPowerOffReq_InterSys_WaitIratOrResume),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_DATA_CALL_REDIAL_SYS_ACQ_REQ,
                      CNAS_HSD_RcvMsccDataCallReq_InterSys_WaitIratOrResume),

    NAS_ACT_TBL_ITEM( UEPS_PID_HALMP,
                      ID_CAS_CNAS_HRPD_NETWORK_LOST_IND,
                      CNAS_HSD_RcvCasNetworkLost_InterSys_WaitIratOrResume),
};

NAS_ACT_STRU g_astCnasHsdInterSysWaitSuspendRelCnfActTbl[] =
{
    NAS_ACT_TBL_ITEM(UEPS_PID_HALMP,
                     ID_CAS_CNAS_HRPD_SUSPEND_REL_CNF,
                     CNAS_HSD_RcvCasSuspendRelCnf_InterSys_WaitSuspendRelCnf),

    NAS_ACT_TBL_ITEM(UEPS_PID_HALMP,
                     ID_CAS_CNAS_HRPD_IRAT_TO_LTE_NTF,
                     CNAS_HSD_RcvCasIratToLte_InterSys_WaitSuspendRelCnf),

    NAS_ACT_TBL_ITEM(UEPS_PID_HALMP,
                     ID_CAS_CNAS_HRPD_RESUME_IND,
                     CNAS_HSD_RcvCasResumeInd_InterSys_WaitSuspendRelCnf),

    NAS_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_CNAS_HSD_WAIT_CAS_SUSPEND_REL_CNF,
                     CNAS_HSD_RcvTiWaitSuspendRelCnfExpired_InterSys_WaitSuspendRelCnf),

    NAS_ACT_TBL_ITEM(UEPS_PID_MSCC,
                     ID_MSCC_HSD_POWER_OFF_REQ,
                     CNAS_HSD_RcvMsccPowerOffReq_InterSys_WaitSuspendRelCnf),

    NAS_ACT_TBL_ITEM(UEPS_PID_MSCC,
                     ID_MSCC_HSD_DATA_CALL_REDIAL_SYS_ACQ_REQ,
                     CNAS_HSD_RcvMsccDataCallReq_InterSys_WaitSuspendRelCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HALMP,
                      ID_CAS_CNAS_HRPD_NETWORK_LOST_IND,
                      CNAS_HSD_RcvCasNetworkLost_InterSys_WaitSuspendRelCnf),
};

/* INTER_SYS状态机消息 状态表 */
NAS_STA_STRU g_astCnasHsdInterSysStaTbl[] =
{
    /*****************定义异系统初始状态转移表**********************/
    NAS_STA_TBL_ITEM( CNAS_HSD_INTER_SYS_STA_INIT,
                      g_astCnasHsdInterSysInitActTbl),

    NAS_STA_TBL_ITEM( CNAS_HSD_INTER_SYS_STA_WAIT_OHM_IND,
                      g_astCnasHsdInterSysWaitOhmIndActTbl),

    NAS_STA_TBL_ITEM( CNAS_HSD_INTER_SYS_STA_WAIT_IRAT_OR_RESUME_IND,
                      g_astCnasHsdInterSysWaitIratOrResumeActTbl),

    NAS_STA_TBL_ITEM( CNAS_HSD_INTER_SYS_STA_WAIT_SUSPEND_REL_CNF,
                      g_astCnasHsdInterSysWaitSuspendRelCnfActTbl),

};

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 函 数 名  : CNAS_HSD_GetInterSysStaTblSize
 功能描述  : 获取InterSys状态机的大小
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32:InterSys状态机的大小
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月03日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_GetInterSysStaTblSize(VOS_VOID)
{
    return (sizeof(g_astCnasHsdInterSysStaTbl)/sizeof(NAS_STA_STRU));
}


/*****************************************************************************
 函 数 名  : CNAS_HSD_GetInterSysFsmDescAddr
 功能描述  : 获取InterSys状态机的描述表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_FSM_DESC_STRU:指向异系统状态机的描述表
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月03日
    作    者   : z00316370
    修改内容   : 新生成函数


*****************************************************************************/
NAS_FSM_DESC_STRU * CNAS_HSD_GetInterSysFsmDescAddr(VOS_VOID)
{
    return (&g_stCnasHsdInterSysFsmDesc);
}
/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



