/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXsdFsmMainTbl.c
  版 本 号   : 初稿
  作    者   : y00245242
  生成日期   : 2014年07月03日
  功能描述   : XSD L1主状态机table表
  函数列表   :
  修改历史   :
  1.日    期   : 2014年07月03日
    作    者   : y00245242
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "CnasXsdFsmMain.h"
#include "CnasXsdFsmMainTbl.h"
#include "CnasXsdSndInternalMsg.h"
#include "CnasXsdTimer.h"
#include "xsd_mscc_pif.h"

#include "cas_1x_control_main_nas_pif.h"
#include "cas_1x_idlectrl_proc_nas_pif.h"

#include "PsRrmInterface.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XSD_FSM_MAIN_TBL_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/* CNAS XSD 主状态机 */
NAS_FSM_DESC_STRU                       g_stCnasXsdMainFsmDesc;

/* XSD L1 null状态下事件处理表 */
NAS_ACT_STRU g_astCnasXsdNullActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_START_REQ,
                      CNAS_XSD_RcvStartReq_Null),

    NAS_ACT_TBL_ITEM( I1_UEPS_PID_MSCC,
                      ID_MSCC_XSD_START_REQ,
                      CNAS_XSD_RcvStartReq_Null),

    NAS_ACT_TBL_ITEM( UEPS_PID_XSD,
                      ID_CNAS_XSD_XSD_SWITCH_ON_RSLT_CNF,
                      CNAS_XSD_RcvSwitchOnRsltCnf_Null),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_POWER_OFF_REQ,
                      CNAS_XSD_RcvPowerOffReq_Null)
};

/* XSD L1 initial状态下事件处理表 */
NAS_ACT_STRU g_astCnasXsdInitialActTbl[] =
{
    /* If XSD receives a Start request from MSCC */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_START_REQ,
                      CNAS_XSD_RcvStartReq_Initial),

    NAS_ACT_TBL_ITEM( I1_UEPS_PID_MSCC,
                      ID_MSCC_XSD_START_REQ,
                      CNAS_XSD_RcvStartReq_Initial),

    /* 用户过来的请求 */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_POWER_OFF_REQ,
                      CNAS_XSD_RcvPowerOffReq_L1Main),

    NAS_ACT_TBL_ITEM( UEPS_PID_XSD,
                      ID_CNAS_XSD_XSD_POWER_OFF_RSLT_CNF,
                      CNAS_XSD_RcvPowerOffRsltCnf_L1Main),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_SYSTEM_ACQUIRE_REQ,
                      CNAS_XSD_RcvSysAcqReq_Initial),

    NAS_ACT_TBL_ITEM( UEPS_PID_XSD,
                      ID_CNAS_XSD_XSD_SYSTEM_ACQUIRED_REQ,
                      CNAS_XSD_RcvInternalSysAcqReq_Initial),

    NAS_ACT_TBL_ITEM( UEPS_PID_XSD,
                      ID_CNAS_XSD_XSD_SYSTEM_ACQUIRED_RSLT_CNF,
                      CNAS_XSD_RcvSysAcqRsltCnf_Initial),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_CALL_REDIAL_SYSTEM_ACQUIRE_NTF,
                      CNAS_XSD_RcvMsccCallRedialSystemAcquireNtf_Initial),

    NAS_ACT_TBL_ITEM( UEPS_PID_XSD,
                      ID_CNAS_XSD_XSD_REDIRECTION_IND,
                      CNAS_XSD_RcvInternalRedirectionInd_Initial),

    NAS_ACT_TBL_ITEM( UEPS_PID_XSD,
                      ID_CNAS_XSD_XSD_REDIRECTION_RSLT_CNF,
                      CNAS_XSD_RcvRedirectionRsltCnf_Initial),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_POWER_SAVE_REQ,
                      CNAS_XSD_RcvMsccPowerSaveReq_L1Main),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_SRV_ACQ_REQ,
                      CNAS_XSD_RcvMsccSrvAcqReq_Initial),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_MO_CALL_END_NTF,
                      CNAS_XSD_RcvMsccMoCallEndNtf_Initial),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_PROTECT_TIMER,
                      CNAS_XSD_RcvTiEmcCallBackNetWorkSrchTimerExpired_Initial),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_EMC_CALLBACK_MODE_PROTECT_TIMER,
                      CNAS_XSD_RcvTiEmcCallBackModeProtectTimerExpired_Initial),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_END_EMC_CALLBACK_NTF,
                      CNAS_XSD_RcvMsccEndEmcCallBackNtf_Initial),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_BREAK_TIMER,
                      CNAS_XSD_RcvTiEmcCallBackSrchBreakTimerExpired_Initial),
};

/* XSD L1 idle状态下事件处理表 */
NAS_ACT_STRU g_astCnasXsdIdleActTbl[] =
{
    /* 用户过来的请求 */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_POWER_OFF_REQ,
                      CNAS_XSD_RcvPowerOffReq_L1Main),

    NAS_ACT_TBL_ITEM( UEPS_PID_XSD,
                      ID_CNAS_XSD_XSD_POWER_OFF_RSLT_CNF,
                      CNAS_XSD_RcvPowerOffRsltCnf_L1Main),

    NAS_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_SYSTEM_DETERMIN_IND,
                      CNAS_XSD_RcvSysDeterminInd_Idle),

    NAS_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_OHM_IND,
                      CNAS_XSD_RcvCasOhmInd_Idle),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_CALL_REDIAL_SYSTEM_ACQUIRE_NTF,
                      CNAS_XSD_RcvMsccCallRedialSystemAcquireNtf_Idle),

    NAS_ACT_TBL_ITEM( UEPS_PID_XSD,
                      ID_CNAS_XSD_XSD_SYSTEM_ACQUIRED_REQ,
                      CNAS_XSD_RcvInternalSysAcqReq_Idle),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_POWER_SAVE_REQ,
                      CNAS_XSD_RcvMsccPowerSaveReq_L1Main),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_MO_CALL_END_NTF,
                      CNAS_XSD_RcvMsccMoCallEndNtf_Idle),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_EMC_CALLBACK_MODE_PROTECT_TIMER,
                      CNAS_XSD_RcvTiEmcCallBackModeProtectTimerExpired_Idle),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_END_EMC_CALLBACK_NTF,
                      CNAS_XSD_RcvMsccEndEmcCallBackNtf_Idle),
};

/* XSD L1 OOC状态下事件处理表 */
NAS_ACT_STRU g_astCnasXsdOocActTbl[] =
{
    /* 用户过来的请求 */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_POWER_OFF_REQ,
                      CNAS_XSD_RcvPowerOffReq_Ooc),

    NAS_ACT_TBL_ITEM( UEPS_PID_XSD,
                      ID_CNAS_XSD_XSD_POWER_OFF_RSLT_CNF,
                      CNAS_XSD_RcvPowerOffRsltCnf_L1Main),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_AVAILABLE_TIMER,
                      CNAS_XSD_RcvTiAvailTimerExpired_Ooc),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_CALL_REDIAL_SYSTEM_ACQUIRE_NTF,
                      CNAS_XSD_RcvMsccCallRedialSystemAcquireNtf_Ooc),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_AVAILABLE_MRU0_TIMER,
                      CNAS_XSD_RcvTiAvailMru0TimerExpired_Ooc),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_POWER_SAVE_REQ,
                      CNAS_XSD_RcvMsccPowerSaveReq_L1Main),

    NAS_ACT_TBL_ITEM( UEPS_PID_RRM,
                      ID_RRM_PS_STATUS_IND,
                      CNAS_XSD_RcvRrmStatusInd_Ooc),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_SRV_ACQ_REQ,
                      CNAS_XSD_RcvMsccSrvAcqReq_Ooc),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_MO_CALL_END_NTF,
                      CNAS_XSD_RcvMsccMoCallEndNtf_Ooc),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_PROTECT_TIMER,
                      CNAS_XSD_RcvTiEmcCallBackNetWorkSrchTimerExpired_Ooc),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_EMC_CALLBACK_MODE_PROTECT_TIMER,
                      CNAS_XSD_RcvTiEmcCallBackModeProtectTimerExpired_Ooc),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_END_EMC_CALLBACK_NTF,
                      CNAS_XSD_RcvMsccEndEmcCallBackNtf_Ooc),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_SYSTEM_ACQUIRE_REQ,
                      CNAS_XSD_RcvMsccXsdSysAcq_Ooc),
};

/* XSD L1 DEACTIVE Act Table */
NAS_ACT_STRU g_astCnasXsdDeactiveActTbl[] =
{

    NAS_ACT_TBL_ITEM(UEPS_PID_MSCC,
                     ID_MSCC_XSD_SYSTEM_ACQUIRE_REQ,
                     CNAS_XSD_RcvMsccSysAcqReq_SysAcq_Deactive),

    NAS_ACT_TBL_ITEM(UEPS_PID_MSCC,
                     ID_MSCC_XSD_POWER_OFF_REQ,
                     CNAS_XSD_RcvPowerOffReq_L1Main),

    NAS_ACT_TBL_ITEM(UEPS_PID_XSD,
                     ID_CNAS_XSD_XSD_POWER_OFF_RSLT_CNF,
                     CNAS_XSD_RcvPowerOffRsltCnf_L1Main),

    NAS_ACT_TBL_ITEM(UEPS_PID_MSCC,
                     ID_MSCC_XSD_POWER_SAVE_REQ,
                     CNAS_XSD_RcvMsccPowerSaveReq_Deactive),

    NAS_ACT_TBL_ITEM(UEPS_PID_RRM,
                     ID_RRM_PS_STATUS_IND,
                     CNAS_XSD_RcvRrmStatusInd_Deactive),

    NAS_ACT_TBL_ITEM(UEPS_PID_MSCC,
                     ID_MSCC_XSD_SRV_ACQ_REQ,
                     CNAS_XSD_RcvMsccSrvAcqReq_Deactive),

};


/* XSD L1 主状态机状态处理表 */
NAS_STA_STRU g_astCnasXsdL1MainStaTbl[] =
{
    /*****************定义及关机到开机初始化状态转移表**********************/
    NAS_STA_TBL_ITEM( CNAS_XSD_L1_STA_NULL,
                      g_astCnasXsdNullActTbl ),

    /*****************定义系统选择状态转移表**********************/
    NAS_STA_TBL_ITEM( CNAS_XSD_L1_STA_INITIAL,
                      g_astCnasXsdInitialActTbl ),

    /*****************定义在驻留及限制驻留时候的状态转移表**********************/
    NAS_STA_TBL_ITEM( CNAS_XSD_L1_STA_IDLE,
                      g_astCnasXsdIdleActTbl ),

    /*****************定义在无任何网络时候的状态转移表**********************/
    NAS_STA_TBL_ITEM( CNAS_XSD_L1_STA_OOC,
                      g_astCnasXsdOocActTbl ),

    /*****************定义在无任何网络时候的状态转移表**********************/
    NAS_STA_TBL_ITEM( CNAS_XSD_L1_STA_DEACTIVE,
                      g_astCnasXsdDeactiveActTbl)
};

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 函 数 名  : CNAS_XSD_GetL1MainStaTblSize
 功能描述  : 获取1X XSD主状态机状态表大小
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回XSD主状态机状态表size
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年07月03日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XSD_GetL1MainStaTblSize(VOS_VOID)
{
    return (sizeof(g_astCnasXsdL1MainStaTbl)/sizeof(NAS_STA_STRU));
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetMainFsmDescAddr
 功能描述  : 获取MAIN状态机的描述表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_FSM_DESC_STRU:指向MAIN状态机的描述表
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年07月03日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
NAS_FSM_DESC_STRU* CNAS_XSD_GetMainFsmDescAddr(VOS_VOID)
{
    return (&g_stCnasXsdMainFsmDesc);
}

/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



