/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasHsdFsmMainTbl.c
  版 本 号   : 初稿
  作    者   : g00256031
  生成日期   : 2014年12月09日
  功能描述   : HRPD L1主状态机table表
  函数列表   :
  修改历史   :
  1.日    期   : 2014年12月09日
    作    者   : g00256031
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "CnasHsdFsmMain.h"
#include "CnasHsdFsmMainTbl.h"
#include "CnasHsdSndInternalMsg.h"
#include "CnasHsdTimer.h"
#include "hsd_mscc_pif.h"
#include "cas_hrpd_airlinkmgmt_nas_pif.h"
#include "cas_hrpd_overheadmsg_nas_pif.h"
#include "cas_hrpd_idlestate_nas_pif.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSD_FSM_MAIN_TBL_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/* CNAS HSD 主状态机 */
NAS_FSM_DESC_STRU                       g_stCnasHsdMainFsmDesc;

/* HSD L1 null状态下事件处理表 */
NAS_ACT_STRU g_astCnasHsdNullActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_START_REQ,
                      CNAS_HSD_RcvStartReq_Null),

    NAS_ACT_TBL_ITEM( I1_UEPS_PID_MSCC,
                      ID_MSCC_HSD_START_REQ,
                      CNAS_HSD_RcvStartReq_Null),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_CNAS_HSD_HSD_SWITCH_ON_RSLT_CNF,
                      CNAS_HSD_RcvSwitchOnRsltCnf_Null),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_POWER_OFF_REQ,
                      CNAS_HSD_RcvPowerOffReq_Null),
};

/* HSD L1 INACTIVE状态下事件处理表 */
NAS_ACT_STRU g_astCnasHsdInactiveActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_POWER_OFF_REQ,
                      CNAS_HSD_RcvPowerOffReq_L1Main),

    NAS_ACT_TBL_ITEM(UEPS_PID_HSD,
                     ID_CNAS_HSD_HSD_POWER_OFF_RSLT_CNF,
                     CNAS_HSD_RcvPowerOffRsltCnf_L1Main),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_START_REQ,
                      CNAS_HSD_RcvStartReq_Inactive),

    NAS_ACT_TBL_ITEM( I1_UEPS_PID_MSCC,
                      ID_MSCC_HSD_START_REQ,
                      CNAS_HSD_RcvStartReq_Inactive),

    NAS_ACT_TBL_ITEM( UEPS_PID_HALMP,
                      ID_CAS_CNAS_HRPD_PILOT_SEARCH_REQ_IND,
                      CNAS_HSD_RcvPilotSearch_Inactive),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_SYSTEM_ACQUIRE_REQ,
                      CNAS_HSD_RcvSysAcqReq_Inactive),

    /* 在混合模式下1X给HSD发的1X搜网成功消息 */
    NAS_ACT_TBL_ITEM(UEPS_PID_MSCC,
                     ID_MSCC_HSD_1X_SYS_CHANGE_IND,
                     CNAS_HSD_Rcv1xSysChgInd_Inactive),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_POWER_SAVE_REQ,
                      CNAS_HSD_RcvPowerSaveReq_Inactive),

    NAS_ACT_TBL_ITEM(UEPS_PID_HSD,
                     ID_CNAS_HSD_HSD_POWER_SAVE_RSLT_CNF,
                     CNAS_HSD_RcvPowerSaveRsltCnf_L1Main),

    NAS_ACT_TBL_ITEM(UEPS_PID_HALMP,
                     ID_CAS_CNAS_HRPD_SUBNET_ID_CHECK_REQ,
                     CNAS_HSD_RcvCasSubnetIdChkReq_Inactive),

    NAS_ACT_TBL_ITEM(UEPS_PID_HALMP,
                     ID_CAS_CNAS_HRPD_IRAT_FROM_LTE_NTF,
                     CNAS_HSD_RcvCasIratFromLteNtf_Inactive),

    NAS_ACT_TBL_ITEM(UEPS_PID_HSD,
                     ID_CNAS_HSD_HSD_INTER_SYS_RSLT_CNF,
                     CNAS_HSD_RcvInterSysRsltCnf_Inactive),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_DATA_CALL_REDIAL_SYS_ACQ_REQ,
                      CNAS_HSD_RcvMsccDataCallRedialSysAcqReq_Inactive),

    NAS_ACT_TBL_ITEM(UEPS_PID_RRM,
                     ID_RRM_PS_STATUS_IND,
                     CNAS_HSD_RcvRrmStatusInd_Deactive),
};

/* HSD L1 initial状态下事件处理表 */
NAS_ACT_STRU g_astCnasHsdInitialActTbl[] =
{
    NAS_ACT_TBL_ITEM(UEPS_PID_MSCC,
                     ID_MSCC_HSD_POWER_OFF_REQ,
                     CNAS_HSD_RcvPowerOffReq_L1Main),

    NAS_ACT_TBL_ITEM(UEPS_PID_HSD,
                     ID_CNAS_HSD_HSD_POWER_OFF_RSLT_CNF,
                     CNAS_HSD_RcvPowerOffRsltCnf_L1Main),

    NAS_ACT_TBL_ITEM(UEPS_PID_HSD,
                     ID_CNAS_HSD_HSD_SYSTEM_ACQUIRED_RSLT_CNF,
                     CNAS_HSD_RcvSysAcqRsltCnfProc_Initial),

    NAS_ACT_TBL_ITEM(UEPS_PID_HSD,
                     ID_CNAS_HSD_HSD_SYSTEM_ACQUIRED_REQ,
                     CNAS_HSD_RcvInternalSysAcqReq_Initial),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_POWER_SAVE_REQ,
                      CNAS_HSD_RcvPowerSaveReq_L1Main),

    NAS_ACT_TBL_ITEM(UEPS_PID_HSD,
                     ID_CNAS_HSD_HSD_POWER_SAVE_RSLT_CNF,
                     CNAS_HSD_RcvPowerSaveRsltCnf_L1Main),
};

/* HSD L1 idle状态下事件处理表 */
NAS_ACT_STRU g_astCnasHsdIdleActTbl[] =
{
    /* 用户过来的请求 */
    NAS_ACT_TBL_ITEM(UEPS_PID_MSCC,
                     ID_MSCC_HSD_POWER_OFF_REQ,
                     CNAS_HSD_RcvPowerOffReq_L1Main),

    NAS_ACT_TBL_ITEM(UEPS_PID_HSD,
                     ID_CNAS_HSD_HSD_POWER_OFF_RSLT_CNF,
                     CNAS_HSD_RcvPowerOffRsltCnf_L1Main),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSP,
                      ID_CAS_CNAS_HRPD_OVERHEAD_MSG_IND,
                      CNAS_HSD_RcvCasOhmInd_Idle),

    /* 在混合模式下1X给HSD发的1X搜网成功消息 */
    NAS_ACT_TBL_ITEM(UEPS_PID_MSCC,
                     ID_MSCC_HSD_1X_SYS_CHANGE_IND,
                     CNAS_HSD_Rcv1xSysChgInd_Idle),

    NAS_ACT_TBL_ITEM( UEPS_PID_HALMP,
                      ID_CAS_CNAS_HRPD_NETWORK_LOST_IND,
                      CNAS_HSD_RcvCasNetworkLostIndProc_Idle),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_DATA_CALL_REDIAL_SYS_ACQ_REQ,
                      CNAS_HSD_RcvMsccDataCallRedialSysAcqReq_Idle),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_POWER_SAVE_REQ,
                      CNAS_HSD_RcvPowerSaveReq_L1Main),

    NAS_ACT_TBL_ITEM(UEPS_PID_HSD,
                     ID_CNAS_HSD_HSD_POWER_SAVE_RSLT_CNF,
                     CNAS_HSD_RcvPowerSaveRsltCnf_L1Main),

    NAS_ACT_TBL_ITEM(UEPS_PID_HALMP,
                     ID_CAS_CNAS_HRPD_SUSPEND_IND,
                     CNAS_HSD_RcvCasSuspendInd_Idle),

    NAS_ACT_TBL_ITEM(UEPS_PID_HSD,
                     ID_CNAS_HSD_HSD_INTER_SYS_RSLT_CNF,
                     CNAS_HSD_RcvInterSysRsltCnf_Idle),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_HSM_HSD_SESSION_NEG_RESULT_IND,
                      CNAS_HSD_RcvHsmSessionNegResultInd_Idle),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_HSM_HSD_CONN_OPEN_IND,
                      CNAS_HSD_RcvHsmConnOpenInd_Idle),
};

/* HSD L1 OOC状态下事件处理表 */
NAS_ACT_STRU g_astCnasHsdOocActTbl[] =
{
    /* 用户过来的请求 */
    NAS_ACT_TBL_ITEM(UEPS_PID_MSCC,
                     ID_MSCC_HSD_POWER_OFF_REQ,
                     CNAS_HSD_RcvPowerOffReq_L1Main),

    NAS_ACT_TBL_ITEM(UEPS_PID_HSD,
                     ID_CNAS_HSD_HSD_POWER_OFF_RSLT_CNF,
                     CNAS_HSD_RcvPowerOffRsltCnf_L1Main),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_HSD_AVAILABLE_TIMER,
                      CNAS_HSD_RcvTiAvailTimerExpired_Ooc),

    /* 在混合模式下1X给HSD发的1X搜网成功消息 */
    NAS_ACT_TBL_ITEM(UEPS_PID_MSCC,
                     ID_MSCC_HSD_1X_SYS_CHANGE_IND,
                     CNAS_HSD_Rcv1xSysChgInd_Ooc),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_HSD_AVAILABLE_MRU0_TIMER,
                      CNAS_HSD_RcvTiAvailMru0TimerExpired_Ooc),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_DATA_CALL_REDIAL_SYS_ACQ_REQ,
                      CNAS_HSD_RcvMsccDataCallRedialSysAcqReq_Ooc),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_POWER_SAVE_REQ,
                      CNAS_HSD_RcvPowerSaveReq_L1Main),

    NAS_ACT_TBL_ITEM(UEPS_PID_HSD,
                     ID_CNAS_HSD_HSD_POWER_SAVE_RSLT_CNF,
                     CNAS_HSD_RcvPowerSaveRsltCnf_L1Main),

    NAS_ACT_TBL_ITEM( UEPS_PID_RRM,
                      ID_RRM_PS_STATUS_IND,
                      CNAS_HSD_RcvRrmStatusInd_Ooc),
};

/* HSD L1 主状态机状态处理表 */
NAS_STA_STRU g_astCnasHsdL1MainStaTbl[] =
{
    /*****************定义及关机到开机初始化状态转移表**********************/
    NAS_STA_TBL_ITEM( CNAS_HSD_L1_STA_NULL,
                      g_astCnasHsdNullActTbl ),

    /*****************定义在HRPD休眠时候的状态转移表**********************/
    NAS_STA_TBL_ITEM( CNAS_HSD_L1_STA_INACTIVE,
                      g_astCnasHsdInactiveActTbl),

    /*****************定义系统选择状态转移表**********************/
    NAS_STA_TBL_ITEM( CNAS_HSD_L1_STA_INITIAL,
                      g_astCnasHsdInitialActTbl ),

    /*****************定义在驻留及限制驻留时候的状态转移表**********************/
    NAS_STA_TBL_ITEM( CNAS_HSD_L1_STA_IDLE,
                      g_astCnasHsdIdleActTbl ),

    /*****************定义在无任何网络时候的状态转移表**********************/
    NAS_STA_TBL_ITEM( CNAS_HSD_L1_STA_OOC,
                      g_astCnasHsdOocActTbl )
};

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 函 数 名  : CNAS_HSD_GetL1MainStaTblSize
 功能描述  : 获取HRPD HSD主状态机状态表大小
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回HSD主状态机状态表size
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年12月12日
   作    者   : h00300778
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_HSD_GetL1MainStaTblSize(VOS_VOID)
{
    return (sizeof(g_astCnasHsdL1MainStaTbl)/sizeof(NAS_STA_STRU));
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetMainFsmDescAddr
 功能描述  : 获取MAIN状态机的描述表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_FSM_DESC_STRU:指向MAIN状态机的描述表
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月12日
    作    者   : h00300778
    修改内容   : 新生成函数

*****************************************************************************/
NAS_FSM_DESC_STRU* CNAS_HSD_GetMainFsmDescAddr(VOS_VOID)
{
    return (&g_stCnasHsdMainFsmDesc);
}

/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



