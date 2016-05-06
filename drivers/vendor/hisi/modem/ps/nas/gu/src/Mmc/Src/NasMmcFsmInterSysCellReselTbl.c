/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcFsmInterSysCellReselTbl.c
  版 本 号   : 初稿
  作    者   : w00176964
  生成日期   : 2011年07月04日
  最近修改   :
  功能描述   : NAS 层InterSysCellResel状态机状态描述表
  函数列表   :
  修改历史   :
  1.日    期   : 2011年07月04日
    作    者   : w00176964
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "NasFsm.h"
#include "NasMmcTimerMgmt.h"
/* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
#include "MsccMmcInterface.h"
/* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */
#include "Nasrrcinterface.h"
#include "MmcGmmInterface.h"
#include "MmcMmInterface.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#endif
#include "NasMmcFsmInterSysCellResel.h"
#include "NasMmcFsmInterSysCellReselTbl.h"
#include "NasMmcSndInternalMsg.h"

/* Added by s00246516 for L-C互操作项目, 2014-01-27, Begin */
#include "CmmcaMmcInterface.h"
/* Added by s00246516 for L-C互操作项目, 2014-01-27, End */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_FSM_INTER_SYS_CELLRESEL_TBL_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/* NAS MMC状态机数组:挂起层二状态机名称*/
NAS_FSM_DESC_STRU                       g_stNasMmcInterSysCellReselFsmDesc;

/* NAS_MMC_INTER_SYS_CELLRESEL_STA_INIT动作表 */
NAS_ACT_STRU   g_astNasInterSysCellReselInitActTbl[]             =
{
    /* 收到was的异系统重选指示 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SUSPEND_IND,
                      NAS_MMC_RcvWasSuspendInd_InterSysCellResel_Init),

    /* 收到Gas的异系统重选指示 */
    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_SUSPEND_IND,
                      NAS_MMC_RcvGasSuspendInd_InterSysCellResel_Init),

#if   (FEATURE_ON == FEATURE_LTE)
    /* 收到EMM的异系统重选指示 */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SUSPEND_IND,
                      NAS_MMC_RcvLmmSuspendInd_InterSysCellResel_Init),
#endif

#if (FEATURE_ON == FEATURE_LTE)
    /* 收到EMM的异系统恢复指示 */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_RESUME_IND,
                      NAS_MMC_RcvLmmResumeInd_InterSysCellResel_Init),
#endif
};

/* NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_SUSPEND_RSP动作表 */
NAS_ACT_STRU   g_astNasInterSysCellReselWaitMmSuspendRspActTbl[]          =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      MMCGMM_SUSPEND_RSP,
                      NAS_MMC_RcvGmmSuspendRsp_InterSysCellResel_WaitMmSuspendRsp),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMCMM_SUSPEND_RSP,
                      NAS_MMC_RcvMmSuspendRsp_InterSysCellResel_WaitMmSuspendRsp),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_MM_SUSPEND_RSP,
                      NAS_MMC_RcvTiWaitMmSuspendRspExpired_InterSysCellResel_WaitMmSuspendRsp),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_InterSysCellResel_WaitMmSuspendRsp),
};

/* NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_AS_RESUME_IND动作表 */
NAS_ACT_STRU   g_astNasInterSysCellReselWaitAsResumeIndActTbl[]          =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_RESUME_IND,
                      NAS_MMC_RcvWasResumeInd_InterSysCellResel_WaitAsResumeInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_RESUME_IND,
                      NAS_MMC_RcvGasResumeInd_InterSysCellResel_WaitAsResumeInd),

#if   (FEATURE_ON == FEATURE_LTE)
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_RESUME_IND,
                      NAS_MMC_RcvLmmResumeInd_InterSysCellResel_WaitAsResumeInd),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SUSPEND_INFO_CHANGE_NOTIFY,
                      NAS_MMC_RcvLmmSuspendInfoChangeNotify_InterSysCellResel_WaitAsResumeInd),


#endif

    /* Added by s00246516 for L-C互操作项目, 2014-01-27, Begin */
#if   (FEATURE_ON == FEATURE_CL_INTERWORK)
    NAS_ACT_TBL_ITEM( WUEPS_PID_CMMCA,
                      ID_CMMCA_MMC_RESUME_IND,
                      NAS_MMC_RcvCmmcaResumeInd_InterSysCellResel_WaitAsResumeInd),

    /* Added by w00167002 for L-C互操作项目, 2014-2-26, begin */
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_CMMCA_RESUME_IND,
                      NAS_MMC_RcvTiWaitCmmcaResumeIndExpired_InterSysCellResel_WaitAsResumeInd),
    /* Added by w00167002 for L-C互操作项目, 2014-2-26, end */
#endif
    /* Added by s00246516 for L-C互操作项目, 2014-01-27, End */

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_AS_RESUME_IND,
                      NAS_MMC_RcvTiWaitAsResumeIndExpired_InterSysCellResel_WaitAsResumeInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_REL_IND,
                      NAS_MMC_RcvRrMmRelInd_InterSysCellResel_WaitAsResumeInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_InterSysCellResel_WaitAsResumeInd),

#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_LTE))
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_INTERSYS_HRPD_NTF,
                      NAS_MMC_RcvMsccInterSysHrpdNtf_InterSysCellResel_WaitAsResumeInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_MSCC_INTERSYS_HRPD_NTF,
                      NAS_MMC_RcvTiWaitMsccInterSysHrpdNtfExpired_InterSysCellResel_WaitAsResumeInd),
#endif

};

/* NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP动作表 */
NAS_ACT_STRU   g_astNasInterSysCellReselWaitMmResumeRspActTbl[]          =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      MMCGMM_RESUME_RSP,
                      NAS_MMC_RcvGmmResumeRsp_InterSysCellResel_WaitMmResumeRsp),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMCMM_RESUME_RSP,
                      NAS_MMC_RcvMmResumeRsp_InterSysCellResel_WaitMmResumeRsp),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_MM_RESUME_RSP,
                      NAS_MMC_RcvTiWaitMmResumeRspExpired_InterSysCellResel_WaitMmResumeRsp),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_InterSysCellResel_WaitMmResumeRsp),

};

/* NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_WAS_SYSINFO_IND动作表 */
NAS_ACT_STRU   g_astNasInterSysCellReselWaitWSysInfoIndActTbl[]       =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SYS_INFO_IND,
                      NAS_MMC_RcvSysInfoInd_InterSysCellResel_WaitWasSysInfoInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_AREA_LOST_IND,
                      NAS_MMC_RcvAreaLostInd_InterSysCellResel_WaitWasSysInfoInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_WAS_SYS_INFO,
                      NAS_MMC_RcvTiWaitSysInfoExpired_InterSysCellResel_WaitWasSysInfoInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_InterSysCellResel_WaitWasSysInfoInd),
};

/* NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_WAS_SYSINFO_IND动作表 */
NAS_ACT_STRU   g_astNasInterSysCellReselWaitGSysInfoIndActTbl[]       =
{

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      GRRMM_SYS_INFO_IND,
                      NAS_MMC_RcvSysInfoInd_InterSysCellResel_WaitGasSysInfoInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_AREA_LOST_IND,
                      NAS_MMC_RcvAreaLostInd_InterSysCellResel_WaitGasSysInfoInd),


    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_GAS_SYS_INFO,
                      NAS_MMC_RcvTiWaitSysInfoExpired_InterSysCellResel_WaitGasSysInfoInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_InterSysCellResel_WaitGasSysInfoInd),
};

/* g_astNasInterSysCellReselWaitWasSuspendRelCnfActTbl动作表 */
NAS_ACT_STRU   g_astNasInterSysCellReselWaitWasSuspendRelCnfActTbl[]              =
{
    /* 收到WAS的SUSPEND_REL_CNF的处理 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SUSPEND_REL_CNF,
                      NAS_MMC_RcvWasSuspendRelCnf_InterSysCellResel_WaitWasSuspendRelCnf),

    /* 收到WAS的RRMM_RESUME_IND的处理 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_RESUME_IND,
                      NAS_MMC_RcvWasResumeInd_InterSysCellResel_WaitAsSuspendRelCnf),

    /* 收到GAS的RRMM_RESUME_IND的处理 */
    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_RESUME_IND,
                      NAS_MMC_RcvGasResumeInd_InterSysCellResel_WaitAsSuspendRelCnf),

#if   (FEATURE_ON == FEATURE_LTE)
    /* 收到LMM的RRMM_RESUME_IND的处理 */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_RESUME_IND,
                      NAS_MMC_RcvLmmResumeInd_InterSysCellResel_WaitAsSuspendRelCnf),
#endif

    /* 等待WAS的SUSPEND_REL_CNF超时的处理 */
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_WAS_SUSPEND_REL_CNF,
                      NAS_MMC_RcvTiWaitWasSuspendRelCnf_InterSysCellResel_WaitWasSuspendRelCnf),

    /* 收到WAS的RRMM_REL_IND的处理 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_REL_IND,
                      NAS_MMC_RcvRrmmRelInd_InterSysCellResel_WaitWasSuspendRelCnf),

};

/* g_astNasInterSysCellReselWaitGasSuspendRelCnfActTbl动作表 */
NAS_ACT_STRU   g_astNasInterSysCellReselWaitGasSuspendRelCnfActTbl[]              =
{
    /* 收到GAS的SUSPEND_REL_CNF的处理 */
    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_SUSPEND_REL_CNF,
                      NAS_MMC_RcvGasSuspendRelCnf_InterSysCellResel_WaitGasSuspendRelCnf),

    /* 收到WAS的RRMM_RESUME_IND的处理 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_RESUME_IND,
                      NAS_MMC_RcvWasResumeInd_InterSysCellResel_WaitAsSuspendRelCnf),

    /* 收到GAS的RRMM_RESUME_IND的处理 */
    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_RESUME_IND,
                      NAS_MMC_RcvGasResumeInd_InterSysCellResel_WaitAsSuspendRelCnf),

#if   (FEATURE_ON == FEATURE_LTE)
    /* 收到LMM的RRMM_RESUME_IND的处理 */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_RESUME_IND,
                      NAS_MMC_RcvLmmResumeInd_InterSysCellResel_WaitAsSuspendRelCnf),
#endif

    /* 等待GAS的SUSPEND_REL_CNF超时的处理 */
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_GAS_SUSPEND_REL_CNF,
                      NAS_MMC_RcvTiWaitGasSuspendRelCnf_InterSysCellResel_WaitGasSuspendRelCnf),
};

#if   (FEATURE_ON == FEATURE_LTE)
/* g_astNasInterSysCellReselWaitLmmSuspendRelCnfActTbl动作表 */
NAS_ACT_STRU   g_astNasInterSysCellReselWaitLmmSuspendRelCnfActTbl[]              =
{
    /* 收到LMM的SUSPEND_REL_CNF的处理 */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SUSPEND_REL_CNF,
                      NAS_MMC_RcvLmmSuspendRelCnf_InterSysCellResel_WaitLmmSuspendRelCnf),

    /* 等待LMM的SUSPEND_REL_CNF超时的处理 */
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_LMM_SUSPEND_REL_CNF,
                      NAS_MMC_RcvTiWaitLmmSuspendRelCnf_InterSysCellResel_WaitLmmSuspendRelCnf),

    /* 收到WAS的RRMM_RESUME_IND的处理 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_RESUME_IND,
                      NAS_MMC_RcvWasResumeInd_InterSysCellResel_WaitAsSuspendRelCnf),

    /* 收到GAS的RRMM_RESUME_IND的处理 */
    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_RESUME_IND,
                      NAS_MMC_RcvGasResumeInd_InterSysCellResel_WaitAsSuspendRelCnf),

    /* 收到LMM的RRMM_RESUME_IND的处理 */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_RESUME_IND,
                      NAS_MMC_RcvLmmResumeInd_InterSysCellResel_WaitAsSuspendRelCnf),

#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_LTE))
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_INTERSYS_HRPD_NTF,
                      NAS_MMC_RcvMsccInterSysHrpdNtf_InterSysCellResel_WaitAsSuspendRelCnf),

#endif
};
#endif

#if   (FEATURE_ON == FEATURE_LTE)
/* NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_WAS_SYSINFO_IND动作表 */
NAS_ACT_STRU   g_astNasInterSysCellReselWaitLSysInfoIndActTbl[]              =
{
    /* 收到L模的系统消息的处理 */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SYS_INFO_IND,
                      NAS_MMC_RcvLSysInfoInd_InterSysCellResel_WaitLSysInfoInd),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_AREA_LOST_IND,
                      NAS_MMC_RcvAreaLostInd_InterSysCellResel_WaitLSysInfoInd),

    /* 等L模的系统消息超时的处理 */
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_LMM_SYS_INFO,
                      NAS_MMC_RcvTiWaitLSysInfoExpired_InterSysCellResel_WaitLSysInfoInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_InterSysCellResel_WaitLSysInfoInd),
};
#endif


/* 协议栈Inter Sys CellResel状态机 */
NAS_STA_STRU g_astNasMmcInterSysCellReselStaTbl[] =
{
     /* 异系统重选初始状态 */
    NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_CELLRESEL_STA_INIT,
                     g_astNasInterSysCellReselInitActTbl ),

    /* 接入层发起的异系统重选过程中等待MM的挂起 */
    NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_SUSPEND_RSP,
                      g_astNasInterSysCellReselWaitMmSuspendRspActTbl ),

    /* 接入层发起的异系统重选过程中等待接入层的恢复 */
    NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_AS_RESUME_IND,
                      g_astNasInterSysCellReselWaitAsResumeIndActTbl ),

    /* 接入层发起的异系统重选过程中等待MM的恢复 */
    NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP,
                      g_astNasInterSysCellReselWaitMmResumeRspActTbl ),

     /* 接入层发起的异系统重选过程中等待WAS系统消息 */
     NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_WAS_SYSINFO_IND,
                       g_astNasInterSysCellReselWaitWSysInfoIndActTbl ),

     /* 接入层发起的异系统重选过程中等待GAS系统消息 */
     NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_GAS_SYSINFO_IND,
                       g_astNasInterSysCellReselWaitGSysInfoIndActTbl ),

     NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_WAS_SUSPEND_REL_CNF,
                       g_astNasInterSysCellReselWaitWasSuspendRelCnfActTbl ),

     NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_GAS_SUSPEND_REL_CNF,
                       g_astNasInterSysCellReselWaitGasSuspendRelCnfActTbl ),

#if (FEATURE_ON == FEATURE_LTE)
     /* 接入层发起的异系统重选过程中等待LTE系统消息 */
     NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_LMM_SYSINFO_IND,
                       g_astNasInterSysCellReselWaitLSysInfoIndActTbl ),

    /* 接入层发起的异系统重选过程中等待LTE消息 */
    NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_LMM_SUSPEND_REL_CNF,
                      g_astNasInterSysCellReselWaitLmmSuspendRelCnfActTbl),

#endif
};



/*****************************************************************************
 函 数 名  : NAS_MMC_GetInterSysCellReselStaTblSize
 功能描述  : 获取inter sys CellResel状态机的大小
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32:inter sys CellResel状态机的大小
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月9日
    作    者   : zhoujun 40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_GetInterSysCellReselStaTblSize( VOS_VOID  )
{
    return (sizeof(g_astNasMmcInterSysCellReselStaTbl)/sizeof(NAS_STA_STRU));
}



/*****************************************************************************
 函 数 名  : NAS_MMC_GetInterSysCellReselFsmDescAddr
 功能描述  : 获取挂起状态机的描述表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_FSM_DESC_STRU:指向挂起状态机的描述表
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月9日
    作    者   : zhoujun 40661
    修改内容   : 新生成函数

*****************************************************************************/
NAS_FSM_DESC_STRU * NAS_MMC_GetInterSysCellReselFsmDescAddr(VOS_VOID)
{
    return (&g_stNasMmcInterSysCellReselFsmDesc);
}



/*****************************************************************************
  3 函数实现
*****************************************************************************/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


