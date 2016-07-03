

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
#include "NasMmcFsmInterSysCco.h"
#include "NasMmcFsmInterSysCcoTbl.h"




#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_FSM_INTER_SYS_CCO_TBL_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/* NAS MMC状态机数组:挂起层二状态机名称*/
NAS_FSM_DESC_STRU                       g_stNasMmcInterSysCcoFsmDesc;

/* NAS_MMC_FSM_L2_InterSysCco:NAS_MMC_InterSysCco_STA_INIT动作表 */
NAS_ACT_STRU   g_astNasInterSysCcoInitActTbl[]             =
{
    /* 收到was的异系统重选指示 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SUSPEND_IND,
                      NAS_MMC_RcvWasSuspendInd_InterSysCco_Init),

    /* 收到Gas的异系统重选指示 */
    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_SUSPEND_IND,
                      NAS_MMC_RcvGasSuspendInd_InterSysCco_Init),

#if   (FEATURE_ON == FEATURE_LTE)
    /* 收到EMM的异系统重选指示 */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SUSPEND_IND,
                      NAS_MMC_RcvLmmSuspendInd_InterSysCco_Init),
#endif

};


/* NAS_MMC_InterSysCco_STA_wait for mm rsp动作表 */
NAS_ACT_STRU   g_astNasInterSysCcoWaitMmSuspendRspActTbl[]          =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMCMM_SUSPEND_RSP,
                      NAS_MMC_RcvMmSuspendRsp_InterSysCco_WaitMmSuspendRsp),

    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      MMCGMM_SUSPEND_RSP,
                      NAS_MMC_RcvGmmSuspendRsp_InterSysCco_WaitMmSuspendRsp),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_MM_SUSPEND_RSP,
                      NAS_MMC_RcvTiWaitMmSuspendRspExpired_InterSysCco_WaitMmSuspendRsp),

};

/* NAS_MMC_InterSysCco_STA_wait for As resume动作表 */
NAS_ACT_STRU   g_astNasInterSysCcoWaitAsResumeIndActTbl[]          =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_RESUME_IND,
                      NAS_MMC_RcvWasResumeInd_InterSysCco_WaitAsResumeInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_RESUME_IND,
                      NAS_MMC_RcvGasResumeInd_InterSysCco_WaitAsResumeInd),

#if   (FEATURE_ON == FEATURE_LTE)
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_RESUME_IND,
                      NAS_MMC_RcvLmmResumeInd_InterSysCco_WaitAsResumeInd),
#endif

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_AS_RESUME_IND,
                      NAS_MMC_RcvTiWaitAsResumeIndExpired_InterSysCco_WaitAsResumeInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_REL_IND,
                      NAS_MMC_RcvRrMmRelInd_InterSysCco_WaitAsResumeInd),

};

/* NAS_MMC_InterSysCco wait for Mm resume rsp动作表 */
NAS_ACT_STRU   g_astNasInterSysCcoWaitMmResumeRspActTbl[]          =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMCMM_RESUME_RSP,
                      NAS_MMC_RcvMmResumeRsp_InterSysCco_WaitMmResumeRsp),

    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      MMCGMM_RESUME_RSP,
                      NAS_MMC_RcvGmmResumeRsp_InterSysCco_WaitMmResumeRsp),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_MM_RESUME_RSP,
                      NAS_MMC_RcvTiWaitMmResumeRspExpired_InterSysCco_WaitMmResumeRsp),
};


/* NAS_MMC_INTER_SYS_CCO_STA_WAIT_WAS_SYSINFO_IND动作表 */
NAS_ACT_STRU   g_astNasInterSysCcoWaitWSysInfoIndActTbl[]          =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SYS_INFO_IND,
                      NAS_MMC_RcvSysInfoInd_InterSysCco_WaitWSysInfoInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_AREA_LOST_IND,
                      NAS_MMC_RcvAreaLostInd_InterSysCco_WaitWSysInfoInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_WAS_SYS_INFO,
                      NAS_MMC_RcvTiWaitWasSysInfoExpired_InterSysCco_WaitWSysInfoInd),
};

/* NAS_MMC_INTER_SYS_CCO_STA_WAIT_GAS_SYSINFO_IND动作表 */
NAS_ACT_STRU   g_astNasInterSysCcoWaitGSysInfoIndActTbl[]          =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      GRRMM_SYS_INFO_IND,
                      NAS_MMC_RcvSysInfoInd_InterSysCco_WaitGSysInfoInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_AREA_LOST_IND,
                      NAS_MMC_RcvAreaLostInd_InterSysCco_WaitGSysInfoInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_GAS_SYS_INFO,
                      NAS_MMC_RcvTiWaitGasSysInfoExpired_InterSysCco_WaitGSysInfoInd),
};

#if (FEATURE_ON == FEATURE_LTE)
/* NAS_MMC_INTER_SYS_CCO_STA_WAIT_LMM_SYSINFO_IND动作表 */
NAS_ACT_STRU   g_astNasInterSysCcoWaitLSysInfoIndActTbl[]          =
{

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SYS_INFO_IND,
                      NAS_MMC_RcvSysInfoInd_InterSysCco_WaitLSysInfoInd),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_AREA_LOST_IND,
                      NAS_MMC_RcvLmmAreaLostInd_InterSysCco_WaitLSysInfoInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_LMM_SYS_INFO,
                      NAS_MMC_RcvTiWaitLmmSysInfoExpired_InterSysCco_WaitLSysInfoInd),
};
#endif

/* NAS_MMC_InterSysCco wait EST Ind动作表 */
NAS_ACT_STRU   g_astNasInterSysCcoWaitEstIndActTbl[]          =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMCMM_RR_CONN_INFO_IND,
                      NAS_MMC_RcvMmRrConnInfoInd_InterSysCco_WaitEstInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      MMCGMM_SIGNALING_STATUS_IND,
                      NAS_MMC_RcvGmmSignalingStatusInd_InterSysCco_WaitEstInd),

#if (FEATURE_LTE == FEATURE_ON)
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_STATUS_IND,
                      NAS_MMC_RcvLmmMmcStatusInd_InterSysCco_WaitEstInd),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SUSPEND_IND,
                      NAS_MMC_RcvLmmSuspendInd_InterSysCco_WaitEstInd),
#endif

    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      MMCGMM_TBF_REL_IND,
                      NAS_MMC_RcvGmmTbfRelInd_InterSysCco_WaitEstInd),

     /* 收到was的异系统CCO指示 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SUSPEND_IND,
                      NAS_MMC_RcvWasSuspendInd_InterSysCco_WaitEstInd),

    /* 收到Gas的异系统CCO指示 */
    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_SUSPEND_IND,
                      NAS_MMC_RcvGasSuspendInd_InterSysCco_WaitEstInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_EST_IND,
                      NAS_MMC_RcvTiWaitEstIndExpired_InterSysCco_WaitEstInd),

};

/* NAS_MMC_FSM_L2_InterSysCco:NAS_MMC_InterSysCco_STA_WAIT_AS_SUSPEND_IND_FALLBACK动作表 */
NAS_ACT_STRU   g_astNasInterSysCcoWaitAsSuspendIndFallBackActTbl[]             =
{
    /* 收到was的异系统CCO指示 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SUSPEND_IND,
                      NAS_MMC_RcvWasSuspendInd_InterSysCco_WaitAsSuspendIndFallBack),

    /* 收到Gas的异系统CCO指示 */
    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_SUSPEND_IND,
                      NAS_MMC_RcvGasSuspendInd_InterSysCco_WaitAsSuspendIndFallBack),

#if   (FEATURE_ON == FEATURE_LTE)
    /* 收到EMM的异系统CCO指示 */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SUSPEND_IND,
                      NAS_MMC_RcvLmmSuspendInd_InterSysCco_WaitAsSuspendIndFallBack),
#endif

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_AS_SUSPEND_IND,
                      NAS_MMC_RcvTiWaitAsSuspendIndExpired_InterSysCco_WaitAsSuspendIndFallBack),
};

/* NAS_MMC_InterSysCco_STA_wait for mm rsp_fallbcak动作表 */
NAS_ACT_STRU   g_astNasInterSysCcoWaitMmSuspendRspFallBackActTbl[]          =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMCMM_SUSPEND_RSP,
                      NAS_MMC_RcvMmSuspendRsp_InterSysCco_WaitMmSuspendRspFallBack),

    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      MMCGMM_SUSPEND_RSP,
                      NAS_MMC_RcvGmmSuspendRsp_InterSysCco_WaitMmSuspendRspFallBack),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_MM_SUSPEND_RSP,
                      NAS_MMC_RcvTiWaitMmSuspendRspExpired_InterSysCco_WaitMmSuspendRspFallBack),
};

/* NAS_MMC_InterSysCco_STA_wait for As resume动作表 */
NAS_ACT_STRU   g_astNasInterSysCcoWaitAsResumeIndFallBackActTbl[]          =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_RESUME_IND,
                      NAS_MMC_RcvWasResumeInd_InterSysCco_WaitAsResumeIndFallBack),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_RESUME_IND,
                      NAS_MMC_RcvGasResumeInd_InterSysCco_WaitAsResumeIndFallBack),

#if   (FEATURE_ON == FEATURE_LTE)
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_RESUME_IND,
                      NAS_MMC_RcvLmmResumeInd_InterSysCco_WaitAsResumeIndFallBack),
#endif

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_AS_RESUME_IND,
                      NAS_MMC_RcvTiWaitAsResumeIndExpired_InterSysCco_WaitAsResumeIndFallBack),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_REL_IND,
                      NAS_MMC_RcvRrMmRelInd_InterSysCco_WaitAsResumeIndFallBack),

};

/* NAS_MMC_InterSysCco wait for Mm resume rsp动作表 */
NAS_ACT_STRU   g_astNasInterSysCcoWaitMmResumeRspFallBackActTbl[]          =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMCMM_RESUME_RSP,
                      NAS_MMC_RcvMmResumeRsp_InterSysCco_WaitMmResumeRspFallBack),

    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      MMCGMM_RESUME_RSP,
                      NAS_MMC_RcvGmmResumeRsp_InterSysCco_WaitMmResumeRspFallBack),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_MM_RESUME_RSP,
                      NAS_MMC_RcvTiWaitMmResumeRspExpired_InterSysCco_WaitMmResumeRspFallBack),
};


/* NAS_MMC_INTER_SYS_CCO_STA_WAIT_WAS_SYSINFO_IND_FALLBACK动作表 */
NAS_ACT_STRU   g_astNasInterSysCcoWaitWSysInfoIndFallBackActTbl[]          =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SYS_INFO_IND,
                      NAS_MMC_RcvSysInfoInd_InterSysCco_WaitWSysInfoIndFallBack),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_AREA_LOST_IND,
                      NAS_MMC_RcvAreaLostInd_InterSysCco_WaitWSysInfoIndFallBack),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_WAS_SYS_INFO,
                      NAS_MMC_RcvTiWaitWasSysInfoExpired_InterSysCco_WaitWSysInfoIndFallBack),
};

/* NAS_MMC_INTER_SYS_CCO_STA_WAIT_GAS_SYSINFO_IND_FALLBACK动作表 */
NAS_ACT_STRU   g_astNasInterSysCcoWaitGSysInfoIndFallBackActTbl[]          =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      GRRMM_SYS_INFO_IND,
                      NAS_MMC_RcvSysInfoInd_InterSysCco_WaitGSysInfoIndFallBack),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_AREA_LOST_IND,
                      NAS_MMC_RcvAreaLostInd_InterSysCco_WaitGSysInfoIndFallBack),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_GAS_SYS_INFO,
                      NAS_MMC_RcvTiWaitGasSysInfoExpired_InterSysCco_WaitGSysInfoIndFallBack),
};

#if (FEATURE_ON == FEATURE_LTE)
/* NAS_MMC_INTER_SYS_CCO_STA_WAIT_LMM_SYSINFO_IND_FALLBACK动作表 */
NAS_ACT_STRU   g_astNasInterSysCcoWaitLSysInfoIndFallBackActTbl[]          =
{

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SYS_INFO_IND,
                      NAS_MMC_RcvSysInfoInd_InterSysCco_WaitLSysInfoIndFallBack),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_AREA_LOST_IND,
                      NAS_MMC_RcvLmmAreaLostInd_InterSysCco_WaitLSysInfoIndFallBack),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_LMM_SYS_INFO,
                      NAS_MMC_RcvTiWaitLmmSysInfoExpired_InterSysCco_WaitLSysInfoIndFallBack),
};
#endif

/*InterSysCco状态机*/
NAS_STA_STRU g_astNasMmcInterSysCcoStaTbl[] =
{
     /* InterSysCco初始状态 */
    NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_CCO_STA_INIT,
                     g_astNasInterSysCcoInitActTbl ),

    /* 接入层发起的InterSysCco过程中等待MM的挂起 */
    NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_SUSPEND_RSP,
                      g_astNasInterSysCcoWaitMmSuspendRspActTbl ),

    /* 接入层发起的InterSysCco过程中等待接入层的恢复 */
    NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_CCO_STA_WAIT_AS_RESUME_IND,
                      g_astNasInterSysCcoWaitAsResumeIndActTbl ),

    /* 接入层发起的InterSysCco过程中等待MM的恢复 */
    NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_RESUME_RSP,
                      g_astNasInterSysCcoWaitMmResumeRspActTbl ),

    /* 接入层发起的InterSysCco过程中等待WAS的系统消息 */
    NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_CCO_STA_WAIT_WAS_SYSINFO_IND,
                      g_astNasInterSysCcoWaitWSysInfoIndActTbl ),

     /* 接入层发起的InterSysCco过程中等待GAS的系统消息 */
     NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_CCO_STA_WAIT_GAS_SYSINFO_IND,
                       g_astNasInterSysCcoWaitGSysInfoIndActTbl ),

#if (FEATURE_ON == FEATURE_LTE)
    /* 接入层发起的InterSysCco过程中等待L的系统消息 */
    NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_CCO_STA_WAIT_LMM_SYSINFO_IND,
                      g_astNasInterSysCcoWaitLSysInfoIndActTbl ),
#endif

    /* 接入层发起的InterSysCco过程中等待CS/PS/EPS的建链结果*/
    NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_CCO_STA_WAIT_EST_IND,
                      g_astNasInterSysCcoWaitEstIndActTbl ),

    /* 接入层发起的InterSysCco回退过程中等待接入层的挂起指示 */
    NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_CCO_STA_WAIT_AS_SUSPEND_IND_FALLBACK,
                      g_astNasInterSysCcoWaitAsSuspendIndFallBackActTbl ),

    /* 接入层发起的InterSysCco回退过程中等待MM的挂起回复*/
    NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_SUSPEND_RSP_FALLBACK,
                      g_astNasInterSysCcoWaitMmSuspendRspFallBackActTbl),

    /* 接入层发起的InterSysCco回退过程中等待接入层的恢复指示 */
    NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_CCO_STA_WAIT_AS_RESUME_IND_FALLBACK,
                      g_astNasInterSysCcoWaitAsResumeIndFallBackActTbl ),

    /* 接入层发起的InterSysCco回退过程中等待MM的恢复回复*/
    NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_RESUME_RSP_FALLBACK,
                      g_astNasInterSysCcoWaitMmResumeRspFallBackActTbl),

    /* 接入层发起的InterSysCco回退过程中等待WAS的系统消息 */
    NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_CCO_STA_WAIT_WAS_SYSINFO_IND_FALLBACK,
                      g_astNasInterSysCcoWaitWSysInfoIndFallBackActTbl ),

     /* 接入层发起的InterSysCco回退过程中等待GAS的系统消息 */
     NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_CCO_STA_WAIT_GAS_SYSINFO_IND_FALLBACK,
                       g_astNasInterSysCcoWaitGSysInfoIndFallBackActTbl ),

#if (FEATURE_ON == FEATURE_LTE)
    /* 接入层发起的InterSysCco回退过程中等待L的系统消息 */
    NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_CCO_STA_WAIT_LMM_SYSINFO_IND_FALLBACK,
                      g_astNasInterSysCcoWaitLSysInfoIndFallBackActTbl ),
#endif
};

/*****************************************************************************
  3 函数实现
****************************************************************************/

VOS_UINT32 NAS_MMC_GetInterSysCcoStaTblSize( VOS_VOID  )
{
    return (sizeof(g_astNasMmcInterSysCcoStaTbl)/sizeof(NAS_STA_STRU));
}




NAS_FSM_DESC_STRU * NAS_MMC_GetInterSysCcoFsmDescAddr(VOS_VOID)
{
    return (&g_stNasMmcInterSysCcoFsmDesc);
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



