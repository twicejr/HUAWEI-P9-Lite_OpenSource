/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmPreProc.c
  版 本 号   : 初稿
  作    者   : w00176964
  生成日期   : 2014年4月16日
  最近修改   :
  功能描述   : NasMmPreProc.c文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年4月16日
    作    者   : w00176964
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
   1 头文件包含
*****************************************************************************/
#include "MM_Ext.h"
#include "NasMmlCtx.h"
#include "NasMmEcall.h"







#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_NAS_MM_PREPORC_C

/*****************************************************************************
   2 全局变量定义
*****************************************************************************/


/*****************************************************************************
   3 函数实现
*****************************************************************************/
/*lint -e958 修改人: w00176964 for RSE 2014-06-19 begin */
/*****************************************************************************
 函 数 名  : NAS_MM_ProcMmcMmSysInfoInd_CsNotSupport_PreProc
 功能描述  : CS不支持时对MMC转发给MM的系统消息的预处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月1日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MM_ProcMmcMmSysInfoInd_CsNotSupport_PreProc( VOS_VOID )
{
    /* 系统消息中指示CS不支持，MM在idle态下状态迁移到No cell available */
    if ((MM_IDLE_NORMAL_SERVICE         == g_MmGlobalInfo.ucState)
     || (MM_IDLE_ATTEMPTING_TO_UPDATE   == g_MmGlobalInfo.ucState)
     || (MM_IDLE_LIMITED_SERVICE        == g_MmGlobalInfo.ucState)
     || (MM_IDLE_PLMN_SEARCH            == g_MmGlobalInfo.ucState)
     || (MM_IDLE_LOCATION_UPDATE_NEEDED == g_MmGlobalInfo.ucState))
    {
        g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;
        Mm_ComSetMmState(MM_IDLE_NO_CELL_AVAILABLE);
    }

    /* 回复MMCMM_ATTACH_CNF的操作,清除等待ATTACH结果标志位 */
    if (MM_WAIT_CS_ATTACH == (g_MmGlobalInfo.stAttachInfo.enAttachType & MM_WAIT_CS_ATTACH))
    {
        NAS_MM_SndMmcAttachCnf();
    }

    g_MmGlobalInfo.stAttachInfo.enAttachType = MM_WAIT_NULL_ATTACH;

    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                MM_MMC_LU_RESULT_FAILURE,
                                NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);

    NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                             NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);


    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_IsNeedDiscardMmcMmSysInfoInd
 功能描述  : 判断是否需要丢弃MMC转发到MM的系统消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:丢弃系统消息
             VOS_FALSE:不需要丢弃系统消息
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月4日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 NAS_MM_IsNeedDiscardMmcMmSysInfoInd( VOS_VOID )
{
    /* MM在TC状态不处理来自MMC的系统消息。
       GMM中在Gmm_MsgDistribute_GMM_TC_ACTIVE 中已做了限制 */
    if (TEST_CONTROL_ACTIVE == g_MmGlobalInfo.ucState)
    {
        return VOS_TRUE;
    }

    /* 通话和等待建链过程，不处理系统消息，转发后丢弃，等待新的系统消息 */
    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {
        if ((WAIT_FOR_OUTGOING_MM_CONNECTION            == g_MmGlobalInfo.ucState)
         || (WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION == g_MmGlobalInfo.ucState)
         || (MM_CONNECTION_ACTIVE                       == g_MmGlobalInfo.ucState))
        {
            if ( MM_TIMER_RUNNING == NAS_MM_QryTimerStatus(MM_TIMER_CS_HO_WAIT_SYSINFO) )
            {
                Mm_TimerStop(MM_TIMER_CS_HO_WAIT_SYSINFO);

                /* 通知MMC HO SUCC */
                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE, MM_MMC_LU_RESULT_SUCCESS, NAS_MML_REG_FAIL_CAUSE_INTER_RAT_CHANGE_SUCC);
            }

            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_MM_ProcMmcMmSysInfoInd_NoImsi_PreProc
 功能描述  : CS卡无效时对MMC转发给MM的系统消息的预处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月1日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MM_ProcMmcMmSysInfoInd_NoImsi_PreProc( VOS_VOID )
{
    g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;

    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                MM_MMC_LU_RESULT_FAILURE,
                                NAS_MML_REG_FAIL_CAUSE_SIM_INVALID);

    NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                             NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS);

    /* 非空闲态,不处理CS卡无效 */
    if (VOS_TRUE == NAS_MM_IsIdleState())
    {
        g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;
        g_MmGlobalInfo.ucPreState       = g_MmGlobalInfo.ucState;
        Mm_ComSetMmState(MM_IDLE_NO_IMSI);
    }

#if (FEATURE_ON == FEATURE_ECALL)
    /* 停止ecall定时器以及清除ecall定时器标记 */        
    NAS_MM_ClearEcallTimerInfo();
#endif

    Mm_ComCheckDelayMmConn(MM_FALSE);

    return;
}

#if (FEATURE_ON == FEATURE_ECALL)
/*****************************************************************************
 函 数 名  : NAS_MM_ProcMmcMmSysInfoInd_ECallOnly_PreProc
 功能描述  : ecall only时对MMC转发给MM的系统消息的预处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
             VOS_FALSE:处理未完成
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月1日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 NAS_MM_ProcMmcMmSysInfoInd_ECallOnly_PreProc(
    VOS_VOID                           *pRcvMsg
)
{
    VOS_UINT32                          ulT3242Status;
    VOS_UINT32                          ulT3243Status;

    /* ecall only模式下,MM的行为必然按照NMOII处理,因为当前PS是不允许发起attach以及进行PS业务的
      因为设置likeB标记 */
    g_MmGlobalInfo.ucLikeB = MM_TRUE;

    /* 如果不是IDLE态按照现有流程处理;否则进行CS的detach后
       做ecall inactivity专有流程以及启动eCall相关定时器 */
    if ((VOS_FALSE              == NAS_MM_IsIdleState())    
     || (MM_IDLE_ECALL_INACTIVE == g_MmGlobalInfo.ucState))
    {
        return VOS_FALSE;
    }
    
    /* 启动ecall定时器 */
    NAS_MM_ProcEcallTimerStartNeededFlg();

    ulT3242Status = NAS_MM_QryTimerStatus(MM_TIMER_T3242);
    ulT3243Status = NAS_MM_QryTimerStatus(MM_TIMER_T3243);

    /* T3242或T3243在运行,不需要迁移到eCall Inactive状态 */
    if ((MM_TIMER_RUNNING       == ulT3242Status)
     || (MM_TIMER_RUNNING       == ulT3243Status))
    {
        return VOS_FALSE;
    }

    /* 进入eCall Inactive的处理 */
    NAS_MM_PerformECallInactivity();

    if (VOS_TRUE == NAS_MM_IsCsForbidden())
    {
        NAS_MM_SndMmcForbidenRslt();
    }
    else
    {
        /* 通知MMC当前CS的注册结果 */
        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    NAS_MML_REG_FAIL_CAUSE_ECALL_INACTIVE);
    }

    NAS_MM_ProcBufferMsg_MmIdleECallInactive();

    return VOS_TRUE;
}



#endif

/*****************************************************************************
 函 数 名  : NAS_MM_RcvMmcMmSysInfoInd_PreProc
 功能描述  : 预处理 SYS INFO消息
 输入参数  : VOS_VOID *pRcvMsg
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月17日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2014年10月22日
    作    者   : z00161729
    修改内容   : DTS2014102109190:勾gmm和mm的全局变量，增加可维可测信息
*****************************************************************************/
VOS_UINT8   NAS_MM_RcvMmcMmSysInfoInd_PreProc(
    VOS_VOID                           *pRcvMsg
)
{
    VOS_UINT8                           ucEventID;

    ucEventID       = 5;

    NAS_MM_LogMmCtxInfo();

    /* 停MM_TIMER_HO_WAIT_SYSINFO或MM_TIMER_EMERGENCY_CSFB_HO_WAIT_SYSINFO的处理与原来相同:
       只有在CSFB标志存在时，才停定时器. 如果需要做LAU，等待LAU结果;如果不需要做LAU, MM报注册假流程
       其他情况下不停定时器，等定时器超时 */
    if ( MM_TIMER_RUNNING == NAS_MM_QryTimerStatus(MM_TIMER_CS_HO_WAIT_SYSINFO) )
    {
        Mm_TimerStop(MM_TIMER_CS_HO_WAIT_SYSINFO);

        /* 通知MMC HO SUCC */
        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE, MM_MMC_LU_RESULT_SUCCESS, NAS_MML_REG_FAIL_CAUSE_INTER_RAT_CHANGE_SUCC);
    }

    /* 是否需要忽略系统消息 */
    if (VOS_TRUE == NAS_MM_IsNeedDiscardMmcMmSysInfoInd())
    {
        return MM_EVENT_ID_INVALID;
    }

    /* 检查系统消息的合法性 */
    if (VOS_FALSE == NAS_MM_CheckMmcMmSysInfoIE(pRcvMsg))
    {
        return MM_EVENT_ID_INVALID;
    }
    
    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {
        NAS_MM_UpdateNetworkInfo_GasSysInfo(pRcvMsg);
    }
    else
    {
        NAS_MM_UpdateNetworkInfo_WasSysInfo(pRcvMsg);
    }

    /* 在收到系统消息指示禁止正常服务时候，需要释放MM链接 */
    if (VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
    {
        if (VOS_FALSE == NAS_MML_GetCsSigConnStatusFlg())
        {
            NAS_MM_RelBufferedServiceEstReqExceptEmergencyCall(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);
        }
    }

    if (VOS_TRUE == NAS_MM_IsCsNotSupport(pRcvMsg))
    {
        NAS_MM_ProcMmcMmSysInfoInd_CsNotSupport_PreProc();
        
        return MM_EVENT_ID_INVALID;
    }

    if (VOS_FALSE == NAS_MML_GetSimCsRegStatus())
    {
        NAS_MM_ProcMmcMmSysInfoInd_NoImsi_PreProc();

        return MM_EVENT_ID_INVALID;
    }   

#if (FEATURE_ON == FEATURE_ECALL)
    if (NAS_MML_ECALL_ONLY == NAS_MML_GetCallMode())
    {
        if (VOS_TRUE == NAS_MM_ProcMmcMmSysInfoInd_ECallOnly_PreProc(pRcvMsg))
        {
            return MM_EVENT_ID_INVALID;
        }

        return ucEventID;
    }
#endif

    return ucEventID;
}
/*lint -e958 修改人: w00176964 for RSE 2014-06-19 end */


/*****************************************************************************
 函 数 名  : NAS_MM_RcvMmcCoverageLostInd_PreProc
 功能描述  : MMC收到MMCMM_COVERAGE_LOST_IND的预处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月4日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 NAS_MM_RcvMmcCoverageLostInd_PreProc(
    VOS_VOID                           *pRcvMsg
)
{
    VOS_UINT8                           ucEventID;

    ucEventID       = 21;

    /* 停MM_TIMER_NORMAL_CSFB_HO_WAIT_SYSINFO或MM_TIMER_EMERGENCY_CSFB_HO_WAIT_SYSINFO的处理与原来相同:
       只有在CSFB标志存在时，才停定时器. 如果需要做LAU，等待LAU结果;如果不需要做LAU, MM报注册假流程
       其他情况下不停定时器，等定时器超时 */
    if ( MM_TIMER_RUNNING == NAS_MM_QryTimerStatus(MM_TIMER_CS_HO_WAIT_SYSINFO) )
    {
        Mm_TimerStop(MM_TIMER_CS_HO_WAIT_SYSINFO);
    }

    return ucEventID;
}


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

