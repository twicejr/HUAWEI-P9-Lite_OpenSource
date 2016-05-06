/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcFsmInterSysHoTbl.c
  版 本 号   : 初稿
  作    者   : w00176964
  生成日期   : 2011年07月04日
  最近修改   :
  功能描述   : NAS 层Inter sys Ho状态机
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
#include "NasMmcFsmInterSysHo.h"
#include "NasMmcFsmInterSysHoTbl.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_FSM_INTER_SYS_HO_TBL_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/* NAS MMC状态机数组:挂起层二状态机名称*/
NAS_FSM_DESC_STRU                       g_stNasMmcInterSysHoFsmDesc;

/* NAS_MMC_FSM_InterSysHo::NAS_MMC_INTER_SYS_HO_STA_INIT动作表 */
NAS_ACT_STRU   g_astNasInterSysHoInitActTbl[]             =
{
    /* 收到was的异系统重选指示 */
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SUSPEND_IND,
                      NAS_MMC_RcvWasSuspendInd_InterSysHo_Init),

    /* 收到Gas的异系统重选指示 */
    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_SUSPEND_IND,
                      NAS_MMC_RcvGasSuspendInd_InterSysHo_Init),

#if   (FEATURE_ON == FEATURE_LTE)
    /* 收到EMM的异系统重选指示 */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SUSPEND_IND,
                      NAS_MMC_RcvLmmSuspendInd_InterSysHo_Init),
#endif

};

/* NAS_MMC_INTER_SYS_HO_STA_WAIT_MM_SUSPEND_RSP动作表 */
NAS_ACT_STRU   g_astNasInterSysHoWaitMmSuspendRspActTbl[]          =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMCMM_SUSPEND_RSP,
                      NAS_MMC_RcvMmSuspendRsp_InterSysHo_WaitMmSuspendRsp),

    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      MMCGMM_SUSPEND_RSP,
                      NAS_MMC_RcvGmmSuspendRsp_InterSysHo_WaitMmSuspendRsp),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_MM_SUSPEND_RSP,
                      NAS_MMC_RcvTiWaitMmSuspendRspExpired_InterSysHo_WaitMmSuspendRsp),
};


/* NAS_MMC_INTER_SYS_HO_STA_WAIT_AS_RESUME_IND动作表 */
NAS_ACT_STRU   g_astNasInterSysHoWaitAsResumeIndActTbl[]          =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_RESUME_IND,
                      NAS_MMC_RcvWasResumeInd_InterSysHo_WaitAsResumeInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_RESUME_IND,
                      NAS_MMC_RcvGasResumeInd_InterSysHo_WaitAsResumeInd),

#if   (FEATURE_ON == FEATURE_LTE)
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_RESUME_IND,
                      NAS_MMC_RcvLmmResumeInd_InterSysHo_WaitAsResumeInd),
#endif

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_AS_RESUME_IND,
                      NAS_MMC_RcvTiWaitAsResumeIndExpired_InterSysHo_WaitAsResumeInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_REL_IND,
                      NAS_MMC_RcvRrMmRelInd_InterSysHo_WaitAsResumeInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_HANDOVER_INFO_IND,
                      NAS_MMC_RcvRrMmHandoverInd_InterSysHo_WaitAsResumeInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_HANDOVER_INFO_IND,
                      NAS_MMC_RcvRrMmHandoverInd_InterSysHo_WaitAsResumeInd),

};

/* NAS_MMC_INTER_SYS_HO_STA_WAIT_MM_RESUME_RSP动作表 */
NAS_ACT_STRU   g_astNasInterSysHoWaitMmResumeRspActTbl[]          =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMCMM_RESUME_RSP,
                      NAS_MMC_RcvMmResumeRsp_InterSysHo_WaitMmResumeRsp),

    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      MMCGMM_RESUME_RSP,
                      NAS_MMC_RcvGmmResumeRsp_InterSysHo_WaitMmResumeRsp),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_MM_RESUME_RSP,
                      NAS_MMC_RcvTiWaitMmResumeRspExpired_InterSysHo_WaitMmResumeRsp),
};


/* InterSysHo状态机 */
NAS_STA_STRU g_astNasMmcInterSysHoStaTbl[] =
{
     /* InterSysHo初始状态 */
    NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_HO_STA_INIT,
                     g_astNasInterSysHoInitActTbl ),

    /* 接入层发起的InterSysHo过程中等待MM的挂起 */
    NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_HO_STA_WAIT_MM_SUSPEND_RSP,
                      g_astNasInterSysHoWaitMmSuspendRspActTbl ),

    /* 接入层发起的InterSysHo过程中等待接入层的恢复 */
    NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_HO_STA_WAIT_AS_RESUME_IND,
                      g_astNasInterSysHoWaitAsResumeIndActTbl ),

    /* 接入层发起的InterSysHo过程中等待MM的恢复 */
    NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_HO_STA_WAIT_MM_RESUME_RSP,
                      g_astNasInterSysHoWaitMmResumeRspActTbl ),
};


/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : NAS_MMC_GetInterSysHoStaTblSize
 功能描述  : 获取inter sys Ho状态机的大小
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32:inter sys Ho状态机的大小
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月19日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_GetInterSysHoStaTblSize( VOS_VOID  )
{
    return (sizeof(g_astNasMmcInterSysHoStaTbl)/sizeof(NAS_STA_STRU));
}



/*****************************************************************************
 函 数 名  : NAS_MMC_GetInterSysHoFsmDescAddr
 功能描述  : 获取挂起状态机的描述表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_FSM_DESC_STRU:指向挂起状态机的描述表
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月19日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
NAS_FSM_DESC_STRU * NAS_MMC_GetInterSysHoFsmDescAddr(VOS_VOID)
{
    return (&g_stNasMmcInterSysHoFsmDesc);
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


