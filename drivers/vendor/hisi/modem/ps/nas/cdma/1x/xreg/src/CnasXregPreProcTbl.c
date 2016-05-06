/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXccPreProcTbl.c
  版 本 号   : 初稿
  作    者   : Y00213812
  生成日期   : 2014年06月27日
  功能描述   : 1X CC(call control)模块任务初始化，任务入口函数处理
  函数列表   :
  修改历史   :
  1.日    期   : 2014年06月27日
    作    者   : Y00213812
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "PsTypeDef.h"
#include "CnasXregPreProcTbl.h"
#include "CnasXregFsmMainTbl.h"
#include "CnasXregTimer.h"
#include "CnasXregSndInternalMsg.h"
#include "xsd_xreg_pif.h"
#include "CnasXregProcess.h"
#include "PsRrmInterface.h"
#include "UsimPsInterface.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XREG_PRE_PROC_TBL_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/* 预处理状态机 */
NAS_FSM_DESC_STRU                       g_stCnasXregPreFsmDesc;

/* 不进状态机处理的消息 动作表 */
NAS_ACT_STRU        g_astCnasXregPreProcessActTbl[]   =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_XSD,
                      ID_XSD_XREG_SYS_INFO_IND,
                      CNAS_XREG_RcvSysInfo_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_XSD,
                      ID_XSD_XREG_POWER_OFF_REQ,
                      CNAS_XREG_RcvPowerOffReq_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_XSD,
                      ID_XSD_XREG_DEREGISTER_IND,
                      CNAS_XREG_RcvXsdDeregisterInd_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_XSD,
                      ID_XSD_XREG_REDIRECTION_IND,
                      CNAS_XREG_RcvXsdRedirInd_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_PARA_NOT_CURRENT_IND,
                      CNAS_XREG_RcvNotCurrInd_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_TMSI_TIMER_EXPIRED_IND,
                      CNAS_XREG_RcvTMSITimeOut_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_XSD,
                      ID_XSD_XREG_UE_STATE_IND,
                      CNAS_XREG_RcvXsdStateInd_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_CSCH_DATA_IND,
                      CNAS_XREG_RcvOrderRegDataInd_PreProc),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XREG_TIMER_T57M,
                      CNAS_XREG_RcvT57TimeOut_PreProc),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XREG_TIMER_PERIOD_REG,
                      CNAS_XREG_RcvPrdRegTimeout_PreProc),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XREG_TIMER_ZONELIST_PT,
                      CNAS_XREG_RcvZoneListTimeout_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_P_VER_IND,
                      CNAS_XREG_RcvProVerInd_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_RRM,
                      ID_RRM_PS_STATUS_IND,
                      CNAS_XREG_RcvStatusInd_L1Main),

    NAS_ACT_TBL_ITEM( MSP_PID_DIAG_APP_AGENT,
                      ID_OM_NAS_CDMA_REG_INFO_REPORT_REQ,
                      CNAS_XREG_RcvOmRegReportReq_PreProc),

    NAS_ACT_TBL_ITEM( MAPS_PIH_PID,
                      USIMM_STKREFRESH_IND,
                      CNAS_XREG_RcvUsimRefreshInd_PreProc),

    NAS_ACT_TBL_ITEM( WUEPS_PID_USIM,
                      USIMM_READFILE_CNF,
                      CNAS_XREG_RcvUsimReadFileCnf_PreProc),
};

/* 不进状态机处理的消息 状态表 */
NAS_STA_STRU        g_astCnasXregPreProcessFsmTbl[]   =
{
    NAS_STA_TBL_ITEM( CNAS_XREG_L1_STA_PREPROC,
                      g_astCnasXregPreProcessActTbl )
};

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/

/*****************************************************************************
 函 数 名  : CNAS_XREG_GetPreProcessStaTblSize
 功能描述  : 获取预处理状态机的大小
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32:预处理状态机的大小
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月18日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XREG_GetPreProcessStaTblSize(VOS_VOID)
{
    return (sizeof(g_astCnasXregPreProcessFsmTbl)/sizeof(NAS_STA_STRU));
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_GetPreFsmDescAddr
 功能描述  : 获取预处理状态机的描述表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_FSM_DESC_STRU:指向预处理状态机的描述表
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月18日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
NAS_FSM_DESC_STRU * CNAS_XREG_GetPreFsmDescAddr(VOS_VOID)
{
    return (&g_stCnasXregPreFsmDesc);
}
/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

