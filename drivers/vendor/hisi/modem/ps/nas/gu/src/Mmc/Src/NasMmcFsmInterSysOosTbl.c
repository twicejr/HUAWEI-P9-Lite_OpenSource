

/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "NasFsm.h"
#include "NasMmcTimerMgmt.h"

#include "MsccMmcInterface.h"

#include "Nasrrcinterface.h"
#include "MmcGmmInterface.h"
#include "MmcMmInterface.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#endif
#include "NasMmcSndInternalMsg.h"
#include "NasMmcFsmInterSysOos.h"
#include "NasMmcFsmInterSysOosTbl.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_FSM_INTER_SYS_OOS_TBL_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/* NAS MMC状态机数组:挂起层二状态机名称*/
NAS_FSM_DESC_STRU                       g_stNasMmcInterSysOosFsmDesc;

/* NAS_MMC_INTER_SYS_OOS_STA_INIT动作表 */
NAS_ACT_STRU   g_astNasInterSysOosInitActTbl[]             =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SUSPEND_IND,
                      NAS_MMC_RcvWasSuspendInd_InterSysOos_Init),
};

/* NAS_MMC_INTER_SYS_OOS_STA_WAIT_MM_SUSPEND_RSP动作表 */
NAS_ACT_STRU   g_astNasInterSysOosWaitMmSuspendRspActTbl[]          =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      MMCGMM_SUSPEND_RSP,
                      NAS_MMC_RcvGmmSuspendRsp_InterSysOos_WaitMmSuspendRsp),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMCMM_SUSPEND_RSP,
                      NAS_MMC_RcvMmSuspendRsp_InterSysOos_WaitMmSuspendRsp),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_MM_SUSPEND_RSP,
                      NAS_MMC_RcvTiWaitMmSuspendRspExpired_InterSysOos_WaitMmSuspendRsp),
};

/* NAS_MMC_INTER_SYS_OOS_STA_WAIT_AS_RESUME_IND动作表 */
NAS_ACT_STRU   g_astNasInterSysOosWaitAsResumeIndActTbl[]          =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_RESUME_IND,
                      NAS_MMC_RcvWasResumeInd_InterSysOos_WaitAsResumeInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_AS_RESUME_IND,
                      NAS_MMC_RcvTiWaitAsResumeIndExpired_InterSysOos_WaitAsResumeInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_InterSysOos_WaitAsResumeInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_REL_IND,
                      NAS_MMC_RcvRrMmRelInd_InterSysOos_WaitAsResumeInd),

};


/* NAS_MMC_INTER_SYS_OOS_STA_WAIT_WAS_SUSPEND_REL_CNF动作表 */
NAS_ACT_STRU   g_astNasInterSysOosWaitWasSuspendRelCnfActTbl[]          =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SUSPEND_REL_CNF,
                      NAS_MMC_RcvWasSuspendRelCnf_InterSysOos_WaitWasSuspendRelCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_REL_IND,
                      NAS_MMC_RcvRrMmRelInd_InterSysOos_WaitWasSuspendRelCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_WAS_SUSPEND_REL_CNF,
                      NAS_MMC_RcvTiWaitWasSuspendRelCnf_InterSysOos_WaitWasSuspendRelCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_RESUME_IND,
                      NAS_MMC_RcvWasResumeInd_InterSysOos_WaitWasSuspendRelCnf),

};


/* NAS_MMC_INTER_SYS_OOS_STA_WAIT_MM_RESUME_RSP动作表 */
NAS_ACT_STRU   g_astNasInterSysOosWaitMmResumeRspActTbl[]          =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      MMCGMM_RESUME_RSP,
                      NAS_MMC_RcvGmmResumeRsp_InterSysOos_WaitMmResumeRsp),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMCMM_RESUME_RSP,
                      NAS_MMC_RcvMmResumeRsp_InterSysOos_WaitMmResumeRsp),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_MM_RESUME_RSP,
                      NAS_MMC_RcvTiWaitMmResumeRspExpired_InterSysOos_WaitMmResumeRsp),
};

/* oos状态机不再有等系统消息状态，删除g_astNasInterSysOosWaitWSysInfoIndActTbl，
   收到resume ind消息就退状态机 */


/* 协议栈Inter Sys OOS状态机 */
NAS_STA_STRU g_astNasMmcInterSysOosStaTbl[] =
{
     /* 出服务搜网状态机初始状态 */
    NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_OOS_STA_INIT,
                     g_astNasInterSysOosInitActTbl ),

    /* 接入层发起的出服务搜网过程中等待MM的挂起 */
    NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_OOS_STA_WAIT_MM_SUSPEND_RSP,
                      g_astNasInterSysOosWaitMmSuspendRspActTbl ),

    /* 接入层发起的出服务搜网过程中等待接入层的恢复 */
    NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_OOS_STA_WAIT_AS_RESUME_IND,
                      g_astNasInterSysOosWaitAsResumeIndActTbl ),

    /* 接入层发起的出服务搜网过程中等待WAS的SUSPPEND_REL_CNF恢复 */
    NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_OOS_STA_WAIT_WAS_SUSPEND_REL_CNF,
                      g_astNasInterSysOosWaitWasSuspendRelCnfActTbl ),

    /* 接入层发起的出服务搜网过程中等待MM的恢复 */
    NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_OOS_STA_WAIT_MM_RESUME_RSP,
                      g_astNasInterSysOosWaitMmResumeRspActTbl ),

    /* oos状态机不再有等系统消息状态，删除g_astNasInterSysOosWaitWSysInfoIndActTbl，
       收到resume ind消息就退状态机 */

};




VOS_UINT32 NAS_MMC_GetInterSysOosStaTblSize( VOS_VOID  )
{
    return (sizeof(g_astNasMmcInterSysOosStaTbl)/sizeof(NAS_STA_STRU));
}




NAS_FSM_DESC_STRU * NAS_MMC_GetInterSysOosFsmDescAddr(VOS_VOID)
{
    return (&g_stNasMmcInterSysOosFsmDesc);
}



/*****************************************************************************
  3 函数实现
*****************************************************************************/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

