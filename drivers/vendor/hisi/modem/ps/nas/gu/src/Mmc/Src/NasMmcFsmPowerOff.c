/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcFsmPowerOff.c
  版 本 号   : 初稿
  作    者   : zhoujun /40661
  生成日期   : 2011年4月01日
  最近修改   :
  功能描述   : 关机状态机的处理
  函数列表   :
  修改历史   :
  1.日    期   : 2011年04月01日
    作    者   : zhoujun /40661
    修改内容   : 创建文件
  2.日    期   : 2011年7月25日
    作    者   : w00176964
    修改内容   : V7R1 PhaseII 全局变量 状态名调整

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "PsTypeDef.h"
#include "NasMmcFsmPoweroffTbl.h"
#include "NasMmcTimerMgmt.h"
#include "NasMmcMain.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#endif
#include "NasMmcSndLmm.h"
#include "NasMmcSndInternalMsg.h"
#include "NasMmcCtx.h"
#include "NasMmlCtx.h"
#include "NasMmcSndMm.h"
#include "NasMmcSndMscc.h"
#include "NasMmcSndGmm.h"
#include "NasMmcSndGuAs.h"
#include "NasMmcProcNvim.h"
#include "NasComm.h"
#include "NasMmcFsmPowerOff.h"
#include "NasMmlLib.h"
#include "NasMmcComFunc.h"

#include "PsRrmInterface.h"

#include "NasUtranCtrlInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMCFSMPOWEROFF_C

/*****************************************************************************
  2 全局变量
*****************************************************************************/


/*****************************************************************************
  3 宏定义
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTafPowerOffReq_PowerOff_Init
 功能描述  : POWER_OFF状态机初始化状态收到ID_MSCC_MMC_POWER_OFF_REQ消息的处理
 输入参数  : ID_MSCC_MMC_POWER_OFF_REQ消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月1日
    作    者   : w00167002
    修改内容   : 新生成函数
  2.日    期   : 2011年7月25日
    作    者   : w00176964
    修改内容   : V7R1 PhaseII 全局变量 状态名调整
  3.日    期   : 2012年03月15日
    作    者   : l00130025
    修改内容   : DTS2012021407803,Eplmn维护修改，关机时不在更新Eplmn，修改为MM/GMM/MMC实时更新
  4.日    期   : 2014年4月11日
    作    者   : w00166186
    修改内容   : DTS20120040600670,LTE主模时关机顺序不正确，导致单板复位
  5.日    期   : 2012年8月4日
    作    者   : w00167002
    修改内容   : V7R1C50_GUTL_PhaseII:G/U/L主模先关机;
  6.日    期   : 2012年12月26日
    作    者   : s00217060
    修改内容   : for DSDA GUNAS C CORE:调整为只给平台支持的接入层发送关机请求
  7.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  8.日    期   : 2014年1月23日
    作    者   : w00242748
    修改内容   : DTS2014012009913:PS only的场景下，AT+CFUN=0关机后,AT+COPS?和AT+CGREG?
                 状态维护不一致。
  9.日    期   : 2014年1月20日
    作    者   : w00167002
    修改内容   : SVLTE共天线项目:开机时候MMC通知RRM进行注册搜网信息，这样在RRM资源
                 可用时，RRM会通知给注册的Modem；在关机时候进行去注册。
                 Modem0的W与Modem1的G存在共用天线。
 10.日    期   : 2013年3月28日
    作    者   : y00176023
    修改内容   : DSDS GUNAS II项目:取消关机时向RRM的去注册动作，目前的方案是收到消息可用去注册
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTafPowerOffReq_PowerOff_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
#if   (FEATURE_ON == FEATURE_LTE)
    MSCC_MMC_POWER_OFF_REQ_STRU          *pstPowerOffMsg = VOS_NULL_PTR;
#endif
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enMasterModeRat;

#if   (FEATURE_ON == FEATURE_LTE)
    pstPowerOffMsg = (MSCC_MMC_POWER_OFF_REQ_STRU*)pstMsg;
#endif

    /* 保存入口消息 */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

    NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_USER_POWER_OFF);

    /* 停止所有定时器 */
    NAS_MMC_StopAllTimer();


    /*向RRM发送去注册消息*/
    NAS_MMC_DeregisterRrmResourceNtfAllRat(RRM_PS_TASK_TYPE_NAS_SEARCH);

    /* 设置当前的主模上下文 */
    NAS_MMC_SetMasterModeRat_PowerOff( NAS_MML_GetCurrNetRatType() );
    /* 获取当前主模 */
    enMasterModeRat = NAS_MMC_GetMasterModeRat_PowerOff();

    /* 主模确定以后，构造从模列表，以便后面给从模发关机请求时使用 */
    NAS_MMC_BuildSlaveModeRatList_PowerOff(enMasterModeRat);

#if   (FEATURE_ON == FEATURE_LTE)

    /* 掉卡引起的关机请求 */
    if ( ( NAS_MML_NET_RAT_TYPE_LTE         ==  enMasterModeRat)
      && ( NAS_MSCC_PIF_POWER_OFF_CAUSE_SIM_REMOVE ==  pstPowerOffMsg->enCause) )
    {

        /* 通知LMM卡状态发生变化 */
        NAS_MMC_SndLmmUsimStatusReq(MMC_LMM_USIM_INVALID);

        /* 迁移到 NAS_MMC_L2_STA_POWER_OFF:NAS_MMC_POWER_OFF_STA_WAIT_LMM_USIM_STATUS_CNF状态,启动保护定时器*/
        NAS_MMC_FSM_SetCurrState(NAS_MMC_POWER_OFF_STA_WAIT_LMM_USIM_STATUS_CNF);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_USIM_STATUS_CNF,TI_NAS_MMC_WAIT_LMM_USIM_STATUS_CNF_LEN);

        return VOS_TRUE;
    }


    if ( NAS_MML_NET_RAT_TYPE_LTE == enMasterModeRat )
    {

        /* 给LTE发送关机消息 */
        NAS_MMC_SndLmmStopReq();

        /* 迁移状态到NAS_MMC_POWEROFF::NAS_MMC_POWER_OFF_STA_WAIT_MASTER_MODE_POWEROFF_CNF,并启动保护定时器 */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_POWER_OFF_STA_WAIT_MASTER_MODE_POWEROFF_CNF);
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MASTER_MODE_POWEROFF_CNF, TI_NAS_MMC_WAIT_MASTER_MODE_POWEROFF_CNF_LEN);

        return VOS_TRUE;
    }

#endif

    /* 通知MM关机，并设置等待MM回复标志 */
    NAS_MMC_SndMmPowerOffReq();

    NAS_MMC_SetMmPowerOffCnfFlag_PowerOff( NAS_MMC_MM_POWER_OFF_FLG );

    /* 通知GMM关机，并设置等待GMM回复标志 */
    NAS_MMC_SndGmmPowerOffReq();

    NAS_MMC_SetMmPowerOffCnfFlag_PowerOff( NAS_MMC_GMM_POWER_OFF_FLG );

    /*****************************************************************
       规避场景:
       PS only的场景下，AT+CFUN=0关机，进行PS detach
       GMM给网侧发送detach请求后，网侧未回复detach accept或者rel ind时，
       这时通过另一个通道下发AT+CGREG进行注册状态查询。关机时，MMC给MM/
       GMM发送关机请求时，MM和GMM迁状态，迁完状态后，判断当前需要给MMC
       发送Service Status Ind指示当前CS/PS域服务状态，MMC收到MM/GMM服务
       状态上报后，会给MSCC上报当前服务状态。该服务状态在AT+COPS?时会使用
       ，所以MMC给MM/GMM模块发送POWER OFF REQ之后，AT+COPS?查询结果为
       无服务。但此时CS/PS注册状态还是处于注册，注册状态将在收到MM/GMM
       CNF之后进行更新。当网侧不回复detach accept或者rel ind，GMM便不会
       MMC上报POWER OFF CNF，所以这段时间内查询AT+CGREG?和AT+COPS?将导致
       两者维护状态不一致。

       问题:MMC给MSCC发送注册状态后，如果GMM还未将服务状态给MMC上报时，在
            该段时间内查询同样会出现不一致。
    *******************************************************************/
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

    /* 迁移到 NAS_MMC_L2_STA_POWER_OFF:NAS_MMC_POWER_OFF_STA_WAIT_MM_POWEROFF_CNF状态,并启动保护定时器TI_NAS_MMC_WAIT_MM_POWEROFF_CNF */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_POWER_OFF_STA_WAIT_MM_POWEROFF_CNF);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_POWEROFF_CNF, TI_NAS_MMC_WAIT_MM_POWEROFF_CNF_LEN);

    return VOS_TRUE;
}

/* Added by s00246516 for L-C互操作项目, 2014-01-28, Begin */
/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMsccPowerSaveReq_PowerOff_Init
 功能描述  : POWER_OFF状态机初始化状态收到ID_MSCC_MMC_POWER_SAVE_REQ消息的处理
 输入参数  : ID_MSCC_MMC_POWER_SAVE_REQ消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月28日
    作    者   : s00246516
    修改内容   : 新生成函数

  2.日    期   : 2015年4月16日
    作    者   : w00242748
    修改内容   : iteration 13开发
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMsccPowerSaveReq_PowerOff_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enNetRatType;

    /* Added by w00167002 for L-C互操作项目, 2014-2-26, begin */
    /* 保存入口消息 */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);
    /* Added by w00167002 for L-C互操作项目, 2014-2-26, end */

    if (VOS_TRUE == NAS_MML_GetCsServiceExistFlg())
    {
        NAS_MMC_SndMsccPowerSaveCnf(NAS_MSCC_PIF_POWER_SAVE_FAILURE);

        /* 关机完成，退出层二状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 获取当前接入技术 */
    enNetRatType = NAS_MML_GetCurrNetRatType();

    /* 信令连接存在 */
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        /* 根据当前不同的接入技术,发送释放请求,迁移到不同的等待连接释放的L2状态，并启动保护定时器 */
        NAS_MMC_SndRelReq_PowerOff(enNetRatType);

        return VOS_TRUE;
    }

    /* 向MM/GMM发送Cover lost指示 */
    NAS_MMC_SndMmCoverageLostInd();
    NAS_MMC_SndGmmCoverageLostInd();

    /* 向TAF报出服务区流程 */
    NAS_MMC_SndMsccCoverageInd(NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST);

    /* 给当前接入结束发送SUSPEND REQ请求，指示当前接入层进入POWER SAVE模式 */
    NAS_MMC_SndSuspendReq_PowerOff(NAS_MML_GetCurrNetRatType());

    return VOS_TRUE;
}
/* Added by s00246516 for L-C互操作项目, 2014-01-28, End */

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcMmcMmPowerOffCnfInPoweroffWaitMmPoweroffCnf
 功能描述  : MMC在WaitMmPoweroffCnf时候收到MM关机确认消息处理
 输入参数  : MM模块发给MMC关机确认消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月9日
    作    者   : W00167002
    修改内容   : 新生成函数
  2.日    期   : 2011年7月25日
    作    者   : w00176964
    修改内容   : V7R1 PhaseII 全局变量 状态名调整

  3.日    期   : 2011年12月27日
    作    者   : w00167002
    修改内容   : DTS2011081106705:新需求:关机时若当前L模为主模，则先给L模发送关机请求,收到L模的关机
                  回复后再给GU模发送关机请求；否则当驻留在L模下关机时L模无法
                  完成DETACH.
                  若当前的主模不是L模，则给G/W/L同时发送关机请求。
  4.日    期   : 2014年4月11日
    作    者   : w00166186
    修改内容   : DTS20120040600670,LTE主模时关机顺序不正确，导致单板复位

  5.日    期   : 2012年8月4日
    作    者   : w00167002
    修改内容   : V7R1C50_GUTL_PhaseII:G/U/L主模先关机;
  6.日    期   : 2012年12月26日
    作    者   : s00217060
    修改内容   : for DSDA GUNAS C CORE:调整为只给平台支持的接入层发送关机请求
  7.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  8.日    期   : 2014年2月14日
    作    者   : s00246516
    修改内容   : L-C互操作项目:增加获取和注册请求的处理
  9.日    期   : 2014年4月9日
    作    者   : s00261364
    修改内容   : V3R360_eCall项目:更新CSPS服务状态
 10.日    期   : 2015年3月11日
    作    者   : wx270776
    修改内容   : DTS2015011212939:增加复位场景
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmPowerOffCnf_PowerOff_WaitMmPoweroffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enMasterModeRat;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstSlaveModeRatList = VOS_NULL_PTR;

    /* 获取从模关机列表 */
    pstSlaveModeRatList = NAS_MMC_GetSlaveModeRatList_PowerOff();
    enMasterModeRat     = NAS_MMC_GetMasterModeRat_PowerOff();

    /* 更新MM的关机确认标志 */
    NAS_MMC_ClearMmPowerOffCnfFlag_PowerOff( NAS_MMC_MM_POWER_OFF_FLG );

    NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

    /* Added by s00261364 for V3R360_eCall项目, 2014-4-4, begin */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_NO_SERVICE);
    /* Added by s00261364 for V3R360_eCall项目, 2014-4-4, end */

    /* 未收齐MM和GMM的关机确认消息，返回继续等待 */
    if ( NAS_MMC_MMGMM_POWER_OFF_NULL_FLG != NAS_MMC_GetMmPowerOffCnfFlg_PowerOff())
    {
        return VOS_TRUE;
    }

    NAS_MMC_StopTimer ( TI_NAS_MMC_WAIT_MM_POWEROFF_CNF );

    /* 收齐MM/GMM的关机回复后，若当前主模为LTE,则此时L主模已被关闭，见DTS20120040600670；
       若当前的主模为G/U时，则需先关闭主模，再给从模发关机 */
    switch ( enMasterModeRat )
    {

#if (FEATURE_ON == FEATURE_LTE)

        case NAS_MML_NET_RAT_TYPE_LTE:

            /* 如果从模个数为0，表示平台支持单模，不需要再给其他模发送关机消息，直接退状态机 */
            if (0 == pstSlaveModeRatList->ucRatNum)
            {
                /* 清空GAS、WAS、LMM的关机确认消息记录标志 */
                NAS_MMC_ClearAllAsPowerOffCnfFlag_PowerOff();

                /* 上报给TAF，关机成功 */
                NAS_Mmc_SndMsccPowerOffCnf();

                /* Modified by s00246516 for L-C互操作项目, 2014-02-14, Begin */
                /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
                NAS_MMC_SndPowerOffRslt(NAS_MMC_POWEROFF_RSLT_POWER_OFF);
                /* Modified by s00246516 for L-C互操作项目, 2014-02-14, End */

                /* 关机完成，退出层二状态机*/
                NAS_MMC_FSM_QuitFsmL2();

                return VOS_TRUE;
            }
            else
            {
                /* 给从模发送关机请求 */
                NAS_MMC_SndSlaveModePowerOffReq_PowerOff();

                /* 迁移状态到NAS_MMC_POWEROFF::NAS_MMC_POWER_OFF_STA_WAIT_SLAVE_MODE_POWEROFF_CNF,并启动保护定时器 */
                NAS_MMC_FSM_SetCurrState(NAS_MMC_POWER_OFF_STA_WAIT_SLAVE_MODE_POWEROFF_CNF);
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_SLAVE_MODE_POWEROFF_CNF, TI_NAS_MMC_WAIT_SLAVE_MODE_POWEROFF_CNF_LEN);
            }
            break;
#endif

        case NAS_MML_NET_RAT_TYPE_WCDMA:

            /* 给WAS主模发送关机消息,设置等待Was回复标志 */
            NAS_MMC_SndAsPowerOffReq(WUEPS_PID_WRR);

            /* 迁移状态到NAS_MMC_POWEROFF::NAS_MMC_POWER_OFF_STA_WAIT_MASTER_MODE_POWEROFF_CNF,并启动保护定时器 */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_POWER_OFF_STA_WAIT_MASTER_MODE_POWEROFF_CNF);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MASTER_MODE_POWEROFF_CNF, TI_NAS_MMC_WAIT_MASTER_MODE_POWEROFF_CNF_LEN);

            break;

        case NAS_MML_NET_RAT_TYPE_GSM:

            /* 给GAS主模发送关机消息,设置等待gas回复标志 */
            NAS_MMC_SndAsPowerOffReq(UEPS_PID_GAS);

            /* 迁移状态到NAS_MMC_POWEROFF::NAS_MMC_POWER_OFF_STA_WAIT_MASTER_MODE_POWEROFF_CNF,并启动保护定时器 */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_POWER_OFF_STA_WAIT_MASTER_MODE_POWEROFF_CNF);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MASTER_MODE_POWEROFF_CNF, TI_NAS_MMC_WAIT_MASTER_MODE_POWEROFF_CNF_LEN);

            break;

        /* 当前没有主模 */
        default:

            /* 如果从模个数为0，又没有主模，复位 */
            if (0 == pstSlaveModeRatList->ucRatNum)
            {
                /* 不可恢复错误,调用底软接口RESET */
                NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_NO_MASTER_AND_SLAVE_MODE);

                return VOS_TRUE;
            }
            else
            {
                /* 给从模发送关机请求 */
                NAS_MMC_SndSlaveModePowerOffReq_PowerOff();

                /* 迁移状态到NAS_MMC_POWEROFF::NAS_MMC_POWER_OFF_STA_WAIT_SLAVE_MODE_POWEROFF_CNF,并启动保护定时器 */
                NAS_MMC_FSM_SetCurrState(NAS_MMC_POWER_OFF_STA_WAIT_SLAVE_MODE_POWEROFF_CNF);
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_SLAVE_MODE_POWEROFF_CNF, TI_NAS_MMC_WAIT_SLAVE_MODE_POWEROFF_CNF_LEN);
            }
            break;
    }


    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGmmPowerOffCnf_PowerOff_WaitMmPoweroffCnf
 功能描述  : MMC在WaitMmPoweroffCnf时候收到GMM关机确认消息处理
 输入参数  : GMM模块发给MMC关机确认消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月9日
    作    者   : W00167002
    修改内容   : 新生成函数
  2.日    期   : 2011年7月25日
    作    者   : w00176964
    修改内容   : V7R1 PhaseII 全局变量 状态名调整
  3.日    期   : 2011年12月27日
    作    者   : w00167002
    修改内容   : DTS2011081106705:新需求:关机时若当前L模为主模，则先给L模发送关机请求,收到L模的关机
                  回复后再给GU模发送关机请求；否则当驻留在L模下关机时L模无法
                  完成DETACH.
                  若当前的主模不是L模，则给G/W/L同时发送关机请求。
  4.日    期   : 2014年4月11日
    作    者   : w00166186
    修改内容   : DTS20120040600670,LTE主模时关机顺序不正确，导致单板复位

  5.日    期   : 2012年8月4日
    作    者   : w00167002
    修改内容   : V7R1C50_GUTL_PhaseII:G/U/L主模先关机;
  6.日    期   : 2012年12月26日
    作    者   : s00217060
    修改内容   : for DSDA GUNAS C CORE:调整为只给平台支持的接入层发送关机请求
  7.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  8.日    期   : 2014年2月14日
    作    者   : s00246516
    修改内容   : L-C互操作项目:增加获取和注册请求的处理
  9.日    期   : 2014年4月9日
    作    者   : s00261364
    修改内容   : V3R360_eCall项目:更新CSPS服务状态
 10.日    期   : 2015年3月11日
    作    者   : wx270776
    修改内容   : DTS2015011212939:增加复位场景
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvGmmPowerOffCnf_PowerOff_WaitMmPoweroffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enMasterModeRat;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstSlaveModeRatList = VOS_NULL_PTR;

    /* 获取从模关机列表 */
    pstSlaveModeRatList = NAS_MMC_GetSlaveModeRatList_PowerOff();
    enMasterModeRat = NAS_MMC_GetMasterModeRat_PowerOff();

    /* 更新GMM的关机确认标志 */
    NAS_MMC_ClearMmPowerOffCnfFlag_PowerOff( NAS_MMC_GMM_POWER_OFF_FLG );

    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

    /* Added by s00261364 for V3R360_eCall项目, 2014-4-4, begin */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_NO_SERVICE);
    /* Added by s00261364 for V3R360_eCall项目, 2014-4-4, end */

    /*  未收齐MM和GMM的关机确认消息，返回继续等待 */
    if ( NAS_MMC_MMGMM_POWER_OFF_NULL_FLG != NAS_MMC_GetMmPowerOffCnfFlg_PowerOff())
    {
        return VOS_TRUE;
    }

    NAS_MMC_StopTimer ( TI_NAS_MMC_WAIT_MM_POWEROFF_CNF );

    /* 收齐MM/GMM的关机回复后，若当前主模为LTE,则此时L主模已被关闭，见DTS20120040600670；
       若当前的主模为G/U时，则需先关闭主模，再给从模发关机 */
    switch ( enMasterModeRat )
    {

#if (FEATURE_ON == FEATURE_LTE)

        case NAS_MML_NET_RAT_TYPE_LTE:

            /* 如果从模个数为0，表示平台支持单模，不需要再给其他模发送关机消息，直接退状态机 */
            if (0 == pstSlaveModeRatList->ucRatNum)
            {
                /* 清空GAS、WAS、LMM的关机确认消息记录标志 */
                NAS_MMC_ClearAllAsPowerOffCnfFlag_PowerOff();

                /* 上报给TAF，关机成功 */
                NAS_Mmc_SndMsccPowerOffCnf();

                /* Modified by s00246516 for L-C互操作项目, 2014-02-14, Begin */
                /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
                NAS_MMC_SndPowerOffRslt(NAS_MMC_POWEROFF_RSLT_POWER_OFF);
                /* Modified by s00246516 for L-C互操作项目, 2014-02-14, End */

                /* 关机完成，退出层二状态机*/
                NAS_MMC_FSM_QuitFsmL2();

                return VOS_TRUE;
            }
            else
            {
                /* 给从模发送关机请求 */
                NAS_MMC_SndSlaveModePowerOffReq_PowerOff();

                /* 迁移状态到NAS_MMC_POWEROFF::NAS_MMC_POWER_OFF_STA_WAIT_SLAVE_MODE_POWEROFF_CNF,并启动保护定时器 */
                NAS_MMC_FSM_SetCurrState(NAS_MMC_POWER_OFF_STA_WAIT_SLAVE_MODE_POWEROFF_CNF);
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_SLAVE_MODE_POWEROFF_CNF, TI_NAS_MMC_WAIT_SLAVE_MODE_POWEROFF_CNF_LEN);
            }
            break;
#endif

        case NAS_MML_NET_RAT_TYPE_WCDMA:

            /* 给WAS发送关机消息,设置等待Was回复标志 */
            NAS_MMC_SndAsPowerOffReq(WUEPS_PID_WRR);

            /* 迁移状态到NAS_MMC_POWEROFF::NAS_MMC_POWER_OFF_STA_WAIT_MASTER_MODE_POWEROFF_CNF,并启动保护定时器 */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_POWER_OFF_STA_WAIT_MASTER_MODE_POWEROFF_CNF);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MASTER_MODE_POWEROFF_CNF, TI_NAS_MMC_WAIT_MASTER_MODE_POWEROFF_CNF_LEN);
            break;

        case NAS_MML_NET_RAT_TYPE_GSM:

            /* 给GAS发送关机消息,设置等待gas回复标志 */
            NAS_MMC_SndAsPowerOffReq(UEPS_PID_GAS);

            /* 迁移状态到NAS_MMC_POWEROFF::NAS_MMC_POWER_OFF_STA_WAIT_MASTER_MODE_POWEROFF_CNF,并启动保护定时器 */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_POWER_OFF_STA_WAIT_MASTER_MODE_POWEROFF_CNF);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MASTER_MODE_POWEROFF_CNF, TI_NAS_MMC_WAIT_MASTER_MODE_POWEROFF_CNF_LEN);

            break;

        /* 当前没有主模 */
        default:

            /* 如果从模个数为0，又没有主模，复位 */
            if (0 == pstSlaveModeRatList->ucRatNum)
            {
                /* 不可恢复错误,调用底软接口RESET */
                NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_NO_MASTER_AND_SLAVE_MODE);

                return VOS_TRUE;
            }
            else
            {
                /* 给从模发送关机请求 */
                NAS_MMC_SndSlaveModePowerOffReq_PowerOff();

                /* 迁移状态到NAS_MMC_POWEROFF::NAS_MMC_POWER_OFF_STA_WAIT_SLAVE_MODE_POWEROFF_CNF,并启动保护定时器 */
                NAS_MMC_FSM_SetCurrState(NAS_MMC_POWER_OFF_STA_WAIT_SLAVE_MODE_POWEROFF_CNF);
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_SLAVE_MODE_POWEROFF_CNF, TI_NAS_MMC_WAIT_SLAVE_MODE_POWEROFF_CNF_LEN);
            }
            break;
    }


    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmPowerOffCnfTimeOut_WaitMmPowerOffCnf
 功能描述  : MM和GMM关机回复超时保护定时器超时后的处理
 输入参数  : TI_NAS_MMC_WAIT_MM_POWEROFF_CNF消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年3月19日
    作    者   : W00167002
    修改内容   : 新生成函数
  2.日    期   : 2011年7月25日
    作    者   : w00176964
    修改内容   : V7R1 PhaseII 全局变量 状态名调整
  3.日    期   : 2011年12月27日
    作    者   : w00167002
    修改内容   : DTS2011081106705:新需求:关机时若当前L模为主模，则先给L模发送关机请求,收到L模的关机
                  回复后再给GU模发送关机请求；否则当驻留在L模下关机时L模无法
                  完成DETACH.
                  若当前的主模不是L模，则给G/W/L同时发送关机请求。
  4.日    期   : 2014年4月11日
    作    者   : w00166186
    修改内容   : DTS20120040600670,LTE主模时关机顺序不正确，导致单板复位

  5.日    期   : 2012年8月4日
    作    者   : w00167002
    修改内容   : V7R1C50_GUTL_PhaseII:G/U/L主模先关机;
  6.日    期   : 2012年12月26日
    作    者   : s00217060
    修改内容   : for DSDA GUNAS C CORE:调整为只给平台支持的接入层发送关机请求
  7.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  8.日    期   : 2014年2月14日
    作    者   : s00246516
    修改内容   : L-C互操作项目:增加获取和注册请求的处理
  9.日    期   : 2014年4月18日
    作    者   : s00261364
    修改内容   : V3R360_eCall项目:增加服务状态上报的处理
 10.日    期   : 2015年3月11日
    作    者   : wx270776
    修改内容   : DTS2015011212939:增加复位场景
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitMmPowerOffCnfExpired_PowerOff_WaitMmPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enMasterModeRat;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstSlaveModeRatList = VOS_NULL_PTR;

    /* 获取从模关机列表 */
    pstSlaveModeRatList = NAS_MMC_GetSlaveModeRatList_PowerOff();
    enMasterModeRat = NAS_MMC_GetMasterModeRat_PowerOff();

    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitMmPowerOffCnfExpired_PowerOff_WaitMmPowerOffCnf ENTERED");

    /* 清空MM的关机确认标志 */
    NAS_MMC_ClearAllMmPowerOffCnfFlag_PowerOff();

    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

    /* Added by s00261364 for V3R360_eCall项目, 2014-4-18, begin */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NO_SERVICE);
    /* Added by s00261364 for V3R360_eCall项目, 2014-4-18, end */


    /* 收齐MM/GMM的关机回复后，若当前主模为LTE,则此时L主模已被关闭，见DTS20120040600670；
       若当前的主模为G/U时，则需先关闭主模，再给从模发关机 */
    switch ( enMasterModeRat )
    {

#if (FEATURE_ON == FEATURE_LTE)

        case NAS_MML_NET_RAT_TYPE_LTE:

            /* 如果从模个数为0，表示平台支持单模，不需要再给其他模发送关机消息，直接退状态机 */
            if (0 == pstSlaveModeRatList->ucRatNum)
            {
                /* 清空GAS、WAS、LMM的关机确认消息记录标志 */
                NAS_MMC_ClearAllAsPowerOffCnfFlag_PowerOff();

                /* 上报给TAF，关机成功 */
                NAS_Mmc_SndMsccPowerOffCnf();

                /* Modified by s00246516 for L-C互操作项目, 2014-02-14, Begin */
                /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
                NAS_MMC_SndPowerOffRslt(NAS_MMC_POWEROFF_RSLT_POWER_OFF);
                /* Modified by s00246516 for L-C互操作项目, 2014-02-14, End */

                /* 关机完成，退出层二状态机*/
                NAS_MMC_FSM_QuitFsmL2();

                return VOS_TRUE;
            }
            else
            {
                /* 给从模发送关机请求 */
                NAS_MMC_SndSlaveModePowerOffReq_PowerOff();

                /* 迁移状态到NAS_MMC_POWEROFF::NAS_MMC_POWER_OFF_STA_WAIT_SLAVE_MODE_POWEROFF_CNF,并启动保护定时器 */
                NAS_MMC_FSM_SetCurrState(NAS_MMC_POWER_OFF_STA_WAIT_SLAVE_MODE_POWEROFF_CNF);
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_SLAVE_MODE_POWEROFF_CNF, TI_NAS_MMC_WAIT_SLAVE_MODE_POWEROFF_CNF_LEN);
            }
            break;
#endif

        case NAS_MML_NET_RAT_TYPE_WCDMA:

            /* 给WAS发送关机消息,设置等待Was回复标志 */
            NAS_MMC_SndAsPowerOffReq(WUEPS_PID_WRR);

            /* 迁移状态到NAS_MMC_POWEROFF::NAS_MMC_POWER_OFF_STA_WAIT_MASTER_MODE_POWEROFF_CNF,并启动保护定时器 */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_POWER_OFF_STA_WAIT_MASTER_MODE_POWEROFF_CNF);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MASTER_MODE_POWEROFF_CNF, TI_NAS_MMC_WAIT_MASTER_MODE_POWEROFF_CNF_LEN);

            break;

        case NAS_MML_NET_RAT_TYPE_GSM:

            /* 给GAS发送关机消息,设置等待gas回复标志 */
            NAS_MMC_SndAsPowerOffReq(UEPS_PID_GAS);

            /* 迁移状态到NAS_MMC_POWEROFF::NAS_MMC_POWER_OFF_STA_WAIT_MASTER_MODE_POWEROFF_CNF,并启动保护定时器 */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_POWER_OFF_STA_WAIT_MASTER_MODE_POWEROFF_CNF);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MASTER_MODE_POWEROFF_CNF, TI_NAS_MMC_WAIT_MASTER_MODE_POWEROFF_CNF_LEN);

            break;

        /* 当前没有主模 */
        default:

            /* 如果从模个数为0，又没有主模，复位 */
            if (0 == pstSlaveModeRatList->ucRatNum)
            {
                /* 不可恢复错误,调用底软接口RESET */
                NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_NO_MASTER_AND_SLAVE_MODE);

                return VOS_TRUE;
            }
            else
            {
                /* 给从模发送关机请求 */
                NAS_MMC_SndSlaveModePowerOffReq_PowerOff();

                /* 迁移状态到NAS_MMC_POWEROFF::NAS_MMC_POWER_OFF_STA_WAIT_SLAVE_MODE_POWEROFF_CNF,并启动保护定时器 */
                NAS_MMC_FSM_SetCurrState(NAS_MMC_POWER_OFF_STA_WAIT_SLAVE_MODE_POWEROFF_CNF);
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_SLAVE_MODE_POWEROFF_CNF, TI_NAS_MMC_WAIT_SLAVE_MODE_POWEROFF_CNF_LEN);
            }
            break;
    }


    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGasPowerOffCnf_PowerOff_WaitMasterModePowerOffCnf
 功能描述  : 收到GAS主模的关机回复确认消息的处理
 输入参数  : RRMM_POWER_OFF_CNF 消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月4日
    作    者   : w00167002
    修改内容   : V7R1C50_GUTL_PhaseII:G/U/L主模先关机;
  2.日    期   : 2012年12月26日
    作    者   : s00217060
    修改内容   : for DSDA GUNAS C CORE:调整为只给平台支持的接入层发送关机请求
  3.日    期   : 2014年2月14日
    作    者   : s00246516
    修改内容   : L-C互操作项目:增加获取和注册请求的处理
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvGasPowerOffCnf_PowerOff_WaitMasterModePowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstSlaveModeRatList = VOS_NULL_PTR;

    NAS_TRACE_HIGH("Enter!");

    /* 获取从模关机列表 */
    pstSlaveModeRatList = NAS_MMC_GetSlaveModeRatList_PowerOff();

    /* 停止收到主模回复定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_MASTER_MODE_POWEROFF_CNF);

    /* 如果从模个数为0，表示平台支持单模，不需要再给其他模发送关机消息，直接退状态机 */
    if (0 == pstSlaveModeRatList->ucRatNum)
    {
        /* 清空GAS、WAS、LMM的关机确认消息记录标志 */
        NAS_MMC_ClearAllAsPowerOffCnfFlag_PowerOff();

        /* 上报给TAF，关机成功 */
        NAS_Mmc_SndMsccPowerOffCnf();

        /* Modified by s00246516 for L-C互操作项目, 2014-02-14, Begin */
        /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
        NAS_MMC_SndPowerOffRslt(NAS_MMC_POWEROFF_RSLT_POWER_OFF);
        /* Modified by s00246516 for L-C互操作项目, 2014-02-14, End */

        /* 关机完成，退出层二状态机*/
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }
    else
    {
        /* 给从模发送关机请求 */
        NAS_MMC_SndSlaveModePowerOffReq_PowerOff();

        /* 迁移状态到NAS_MMC_POWEROFF::NAS_MMC_POWER_OFF_STA_WAIT_SLAVE_MODE_POWEROFF_CNF,并启动保护定时器 */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_POWER_OFF_STA_WAIT_SLAVE_MODE_POWEROFF_CNF);
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_SLAVE_MODE_POWEROFF_CNF, TI_NAS_MMC_WAIT_SLAVE_MODE_POWEROFF_CNF_LEN);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvWasPowerOffCnf_PowerOff_WaitMasterModePowerOffCnf
 功能描述  : 收到Was主模的关机回复确认消息的处理
 输入参数  : RRMM_POWER_OFF_CNF 消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月4日
    作    者   : w00167002
    修改内容   : V7R1C50_GUTL_PhaseII:G/U/L主模先关机;
  2.日    期   : 2012年12月26日
    作    者   : s00217060
    修改内容   : for DSDA GUNAS C CORE:调整为只给平台支持的接入层发送关机请求
  3.日    期   : 2013年7月4日
    作    者   : z00234330
    修改内容   : 增加开机LOG
  4.日    期   : 2014年2月14日
    作    者   : s00246516
    修改内容   : L-C互操作项目:增加获取和注册请求的处理
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvWasPowerOffCnf_PowerOff_WaitMasterModePowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstSlaveModeRatList = VOS_NULL_PTR;

    NAS_TRACE_HIGH("%s", (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode()) ? "FDD" : "TDD");

    /* 获取从模关机列表 */
    pstSlaveModeRatList = NAS_MMC_GetSlaveModeRatList_PowerOff();

    /* 停止收到主模回复定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_MASTER_MODE_POWEROFF_CNF);

    /* Modified by z00234330 for 开机LOG, 2013-6-24, begin */
    (VOS_VOID)vos_printf("NAS_MMC_RcvWasPowerOffCnf_PowerOff_WaitMasterModePowerOffCnf, tick = 0x%x\r\n ", VOS_GetSlice());
    /* Modified by z00234330 for 开机LOG, 2013-6-24, begin */

    /* 如果从模个数为0，表示平台支持单模，不需要再给其他模发送关机消息，直接退状态机 */
    if (0 == pstSlaveModeRatList->ucRatNum)
    {
        /* 清空GAS、WAS、LMM的关机确认消息记录标志 */
        NAS_MMC_ClearAllAsPowerOffCnfFlag_PowerOff();

        /* 上报给TAF，关机成功 */
        NAS_Mmc_SndMsccPowerOffCnf();

        /* Modified by s00246516 for L-C互操作项目, 2014-02-14, Begin */
        /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
        NAS_MMC_SndPowerOffRslt(NAS_MMC_POWEROFF_RSLT_POWER_OFF);
        /* Modified by s00246516 for L-C互操作项目, 2014-02-14, End */

        /* 关机完成，退出层二状态机*/
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }
    else
    {
        /* 给从模发送关机请求 */
        NAS_MMC_SndSlaveModePowerOffReq_PowerOff();

        /* 迁移状态到NAS_MMC_POWEROFF::NAS_MMC_POWER_OFF_STA_WAIT_SLAVE_MODE_POWEROFF_CNF,并启动保护定时器 */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_POWER_OFF_STA_WAIT_SLAVE_MODE_POWEROFF_CNF);
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_SLAVE_MODE_POWEROFF_CNF, TI_NAS_MMC_WAIT_SLAVE_MODE_POWEROFF_CNF_LEN);
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitMasterModePowerOffCnfExpired_PowerOff_WaitMasterModePowerOffCnf
 功能描述  : 等待主模GAS/WAS/LMM的关机确认消息时超时
 输入参数  : 保护定时器消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月4日
    作    者   : w00167002
    修改内容   : V7R1C50_GUTL_PhaseII:G/U/L主模先关机;
  2.日    期   : 2012年12月26日
    作    者   : s00217060
    修改内容   : for DSDA GUNAS C CORE:调整为只给平台支持的接入层发送关机请求
  3.日    期   : 2014年2月14日
    作    者   : s00246516
    修改内容   : L-C互操作项目:增加获取和注册请求的处理
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitMasterModePowerOffCnfExpired_PowerOff_WaitMasterModePowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enMasterModeRat;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstSlaveModeRatList = VOS_NULL_PTR;

    /* 获取从模关机列表 */
    pstSlaveModeRatList = NAS_MMC_GetSlaveModeRatList_PowerOff();
    enMasterModeRat = NAS_MMC_GetMasterModeRat_PowerOff();

    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitMasterModePowerOffCnfExpired_PowerOff_WaitMasterModePowerOffCnf:ENTERED");

    NAS_TRACE_HIGH("Enter!");

    /* 收齐MM/GMM的关机回复后，若当前主模为LTE,则此时L主模已被关闭，见DTS20120040600670；
       若当前的主模为G/U时，则需先关闭主模，再给从模发关机 */
    switch ( enMasterModeRat )
    {

#if (FEATURE_ON == FEATURE_LTE)

        case NAS_MML_NET_RAT_TYPE_LTE:

            /* 通知MM关机，并设置等待MM回复标志 */
            NAS_MMC_SndMmPowerOffReq();
            NAS_MMC_SetMmPowerOffCnfFlag_PowerOff( NAS_MMC_MM_POWER_OFF_FLG );

            /* 通知GMM关机，并设置等待GMM回复标志 */
            NAS_MMC_SndGmmPowerOffReq();
            NAS_MMC_SetMmPowerOffCnfFlag_PowerOff( NAS_MMC_GMM_POWER_OFF_FLG );

            /* 迁移到 NAS_MMC_L2_STA_POWER_OFF:NAS_MMC_POWER_OFF_STA_WAIT_MM_POWEROFF_CNF状态,并启动保护定时器TI_NAS_MMC_WAIT_MM_POWEROFF_CNF*/
            NAS_MMC_FSM_SetCurrState(NAS_MMC_POWER_OFF_STA_WAIT_MM_POWEROFF_CNF);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_POWEROFF_CNF, TI_NAS_MMC_WAIT_MM_POWEROFF_CNF_LEN);

            break;
#endif

        case NAS_MML_NET_RAT_TYPE_WCDMA:

            /* 如果从模个数为0，表示平台支持单模，不需要再给其他模发送关机消息，直接退状态机 */
            if (0 == pstSlaveModeRatList->ucRatNum)
            {
                /* 清空GAS、WAS、LMM的关机确认消息记录标志 */
                NAS_MMC_ClearAllAsPowerOffCnfFlag_PowerOff();

                /* 上报给TAF，关机成功 */
                NAS_Mmc_SndMsccPowerOffCnf();

                /* Modified by s00246516 for L-C互操作项目, 2014-02-14, Begin */
                /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
                NAS_MMC_SndPowerOffRslt(NAS_MMC_POWEROFF_RSLT_POWER_OFF);
                /* Modified by s00246516 for L-C互操作项目, 2014-02-14, End */

                /* 关机完成，退出层二状态机*/
                NAS_MMC_FSM_QuitFsmL2();

                return VOS_TRUE;
            }
            else
            {
                /* 给从模发送关机请求 */
                NAS_MMC_SndSlaveModePowerOffReq_PowerOff();

                /* 迁移状态到NAS_MMC_POWEROFF::NAS_MMC_POWER_OFF_STA_WAIT_SLAVE_MODE_POWEROFF_CNF,并启动保护定时器 */
                NAS_MMC_FSM_SetCurrState(NAS_MMC_POWER_OFF_STA_WAIT_SLAVE_MODE_POWEROFF_CNF);
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_SLAVE_MODE_POWEROFF_CNF, TI_NAS_MMC_WAIT_SLAVE_MODE_POWEROFF_CNF_LEN);
            }
            break;

        case NAS_MML_NET_RAT_TYPE_GSM:

            /* 如果从模个数为0，表示平台支持单模，不需要再给其他模发送关机消息，直接退状态机 */
            if (0 == pstSlaveModeRatList->ucRatNum)
            {
                /* 清空GAS、WAS、LMM的关机确认消息记录标志 */
                NAS_MMC_ClearAllAsPowerOffCnfFlag_PowerOff();

                /* 上报给TAF，关机成功 */
                NAS_Mmc_SndMsccPowerOffCnf();

                /* Modified by s00246516 for L-C互操作项目, 2014-02-14, Begin */
                /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
                NAS_MMC_SndPowerOffRslt(NAS_MMC_POWEROFF_RSLT_POWER_OFF);
                /* Modified by s00246516 for L-C互操作项目, 2014-02-14, End */

                /* 关机完成，退出层二状态机*/
                NAS_MMC_FSM_QuitFsmL2();

                return VOS_TRUE;
            }
            else
            {
                /* 给从模发送关机请求 */
                NAS_MMC_SndSlaveModePowerOffReq_PowerOff();

                /* 迁移状态到NAS_MMC_POWEROFF::NAS_MMC_POWER_OFF_STA_WAIT_SLAVE_MODE_POWEROFF_CNF,并启动保护定时器 */
                NAS_MMC_FSM_SetCurrState(NAS_MMC_POWER_OFF_STA_WAIT_SLAVE_MODE_POWEROFF_CNF);
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_SLAVE_MODE_POWEROFF_CNF, TI_NAS_MMC_WAIT_SLAVE_MODE_POWEROFF_CNF_LEN);
            }
            break;

        /* 当前没有主模 */
        default:
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitMasterModePowerOffCnfExpired_PowerOff_WaitMasterModePowerOffCnf:NO MASTER MODE!");
            break;
    }

    return VOS_TRUE;

}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGasPowerOffCnf_PowerOff_WaitSlaveModePowerOffCnf
 功能描述  : 从模GAS关机确认消息处理
 输入参数  : RRMM_POWER_OFF_CNF 消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月4日
    作    者   : w00167002
    修改内容   : V7R1C50_GUTL_PhaseII:G/U/L主模先关机;
  2.日    期   : 2014年2月14日
    作    者   : s00246516
    修改内容   : L-C互操作项目:增加获取和注册请求的处理
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvGasPowerOffCnf_PowerOff_WaitSlaveModePowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Enter!");

    /* 更新GAS接入层的关机确认消息记录标志 */
    NAS_MMC_ClearAsPowerOffCnfFlag_PowerOff( NAS_MMC_GAS_POWER_OFF_FLG );

    /* 未收齐所有接入层的关机确认消息，返回继续等待 */
    if ( NAS_MMC_AS_POWER_OFF_NULL_FLG != NAS_MMC_GetAsPowerOffCnfFlg_PowerOff() )
    {
        return VOS_TRUE;
    }


    /* 当前G模为从模且收到了所有接入层的关机回复 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_SLAVE_MODE_POWEROFF_CNF);

    /* 上报给TAF，关机成功 */
    NAS_Mmc_SndMsccPowerOffCnf();

    /* Modified by s00246516 for L-C互操作项目, 2014-02-14, Begin */
    /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
    NAS_MMC_SndPowerOffRslt(NAS_MMC_POWEROFF_RSLT_POWER_OFF);
    /* Modified by s00246516 for L-C互操作项目, 2014-02-14, End */

    /* 关机完成，退出层二状态机*/
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvWasPowerOffCnf_PowerOff_WaitSlaveModePowerOffCnf
 功能描述  : WAS关机确认消息处理
 输入参数  : RRMM_POWER_OFF_CNF 消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月4日
    作    者   : w00167002
    修改内容   : V7R1C50_GUTL_PhaseII:G/U/L主模先关机;
  2.日    期   : 2014年2月14日
    作    者   : s00246516
    修改内容   : L-C互操作项目:增加获取和注册请求的处理
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvWasPowerOffCnf_PowerOff_WaitSlaveModePowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("%s", (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode()) ? "FDD" : "TDD");

    /* 更新接入层WAS的关机确认消息记录标志 */
    NAS_MMC_ClearAsPowerOffCnfFlag_PowerOff( NAS_MMC_WAS_POWER_OFF_FLG );

    /* 未收齐所有接入层的关机确认消息,返回继续等待 */
    if ( NAS_MMC_AS_POWER_OFF_NULL_FLG != NAS_MMC_GetAsPowerOffCnfFlg_PowerOff() )
    {
        return VOS_TRUE;
    }

    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_SLAVE_MODE_POWEROFF_CNF);

    /* 上报给TAF，关机成功 */
    NAS_Mmc_SndMsccPowerOffCnf();

    /* Modified by s00246516 for L-C互操作项目, 2014-02-14, Begin */
    /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
    NAS_MMC_SndPowerOffRslt(NAS_MMC_POWEROFF_RSLT_POWER_OFF);
    /* Modified by s00246516 for L-C互操作项目, 2014-02-14, End */

    /* 关机完成，退出层二状态机*/
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvAsPowerOffCnfTimeOut_WaitSlaveModePowerOffCnf
 功能描述  : 等待从模GAS、WAS、LMM的关机确认消息时超时
 输入参数  : 保护定时器消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月4日
    作    者   : w00167002
    修改内容   : V7R1C50_GUTL_PhaseII:G/U/L主模先关机;
  2.日    期   : 2014年2月14日
    作    者   : s00246516
    修改内容   : L-C互操作项目:增加获取和注册请求的处理
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitSlaveModePowerOffCnfExpired_PowerOff_WaitSlaveModePowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitSlaveModePowerOffCnfExpired_PowerOff_WaitSlaveModePowerOffCnf:ENTERED");

    NAS_TRACE_HIGH("Enter!");

    /* 清空GAS、WAS、LMM的关机确认消息记录标志 */
    NAS_MMC_ClearAllAsPowerOffCnfFlag_PowerOff();

    /* 上报给TAF，关机成功 */
    NAS_Mmc_SndMsccPowerOffCnf();

    /* Modified by s00246516 for L-C互操作项目, 2014-02-14, Begin */
    /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
    NAS_MMC_SndPowerOffRslt(NAS_MMC_POWEROFF_RSLT_POWER_OFF);
    /* Modified by s00246516 for L-C互操作项目, 2014-02-14, End */

    /* 关机完成，退出层二状态机*/
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;

}



#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLtePowerOffCnf_PowerOff_WaitMasterModePowerOffCnf
 功能描述  : LMM/WAS/GAS关机确认消息处理
 输入参数  : RRMM_POWER_OFF_CNF 消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月4日
    作    者   : w00167002
    修改内容   : V7R1C50_GUTL_PhaseII:关机时若当前L模为主模，则先给L模发送关机请求,收到L模的关机
                  回复后再给GU模发送关机请求;
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmStopCnf_PowerOff_WaitMasterModePowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Enter!");

    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_MASTER_MODE_POWEROFF_CNF);

    /* 通知MM关机，并设置等待MM回复标志 */
    NAS_MMC_SndMmPowerOffReq();

    NAS_MMC_SetMmPowerOffCnfFlag_PowerOff( NAS_MMC_MM_POWER_OFF_FLG );

    /* 通知GMM关机，并设置等待GMM回复标志 */
    NAS_MMC_SndGmmPowerOffReq();

    NAS_MMC_SetMmPowerOffCnfFlag_PowerOff( NAS_MMC_GMM_POWER_OFF_FLG );

    /* 迁移到 NAS_MMC_L2_STA_POWER_OFF:NAS_MMC_POWER_OFF_STA_WAIT_MM_POWEROFF_CNF状态,并启动保护定时器TI_NAS_MMC_WAIT_MM_POWEROFF_CNF*/
    NAS_MMC_FSM_SetCurrState(NAS_MMC_POWER_OFF_STA_WAIT_MM_POWEROFF_CNF);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_POWEROFF_CNF, TI_NAS_MMC_WAIT_MM_POWEROFF_CNF_LEN);

    return VOS_TRUE;

}

/* Added by s00246516 for L-C互操作项目, 2014-01-28, Begin */
/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmSuspendCnf_PowerOff_WaitLmmSuspendCnf
 功能描述  : POWER_OFF状态机等待LMM挂起回复状态收到消息的处理
 输入参数  : 消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月28日
    作    者   : s00246516
    修改内容   : 新生成函数
  2.日    期   : 2015年3月11日
    作    者   : wx270776
    修改内容   : DTS2015011212939:增加复位场景
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmSuspendCnf_PowerOff_WaitLmmSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_SUSPEND_CNF_STRU           *pstSuspendCnf = VOS_NULL_PTR;

    pstSuspendCnf = (LMM_MMC_SUSPEND_CNF_STRU*)pstMsg;

    /* 停止保护定时器TI_NAS_MMC_WAIT_LMM_SUSPEND_CNF */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_SUSPEND_CNF);

    /* 如果挂起失败直接复位 */
    if (MMC_LMM_FAIL == pstSuspendCnf->ulRst)
    {
        /* 异常打印 */
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmSuspendCnf_PowerOff_WaitLmmSuspendCnf: SUSPEND FAIL !");

        /* 不可恢复错误,调用底软接口RESET */
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_LMM_SUSPEND_FAILURE);

        return VOS_TRUE;
    }

    /* 设置当前接入技术为BUTT */
    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

    /* 上报给MSCC Power Save成功 */
    NAS_MMC_SndMsccPowerSaveCnf(NAS_MSCC_PIF_POWER_SAVE_SUCCESS);

    /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
    NAS_MMC_SndPowerOffRslt(NAS_MMC_POWEROFF_RSLT_POWER_SAVE);

    /* 关机完成，退出层二状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitLmmSuspendCnfExpired_PowerOff_WaitLmmSuspendCnf
 功能描述  : POWER_OFF状态机等待LMM挂起回复超时的处理
 输入参数  : 消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月28日
    作    者   : s00246516
    修改内容   : 新生成函数
  2.日    期   : 2015年3月11日
    作    者   : wx270776
    修改内容   : DTS2015011212939:增加复位场景
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitLmmSuspendCnfExpired_PowerOff_WaitLmmSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 异常打印 */
    NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitLmmSuspendCnfExpired_PowerOff_WaitLmmSuspendCnf: Enter !");

    /* 复位 */
    NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_LMM_SUSPEND_CNF_EXPIRED);

    return VOS_TRUE;
}
/* Added by s00246516 for L-C互操作项目, 2014-01-28, End */

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLtePowerOffCnf_PowerOff_WaitSlaveModePowerOffCnf
 功能描述  : LMM从模关机确认消息处理
 输入参数  : RRMM_POWER_OFF_CNF 消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月4日
    作    者   : w00167002
    修改内容   : V7R1C50_GUTL_PhaseII:新增函数;
  2.日    期   : 2014年2月14日
    作    者   : s00246516
    修改内容   : L-C互操作项目:增加获取和注册请求的处理
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmStopCnf_PowerOff_WaitSlaveModePowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Enter!");

    /* 更新接入层LTE的关机确认消息记录标志 */
    NAS_MMC_ClearAsPowerOffCnfFlag_PowerOff( NAS_MMC_LTE_POWER_OFF_FLG );

    /* 未收齐所有接入层的关机确认消息，返回继续等待 */
    if ( NAS_MMC_AS_POWER_OFF_NULL_FLG != NAS_MMC_GetAsPowerOffCnfFlg_PowerOff() )
    {
        return VOS_TRUE;
    }

    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_SLAVE_MODE_POWEROFF_CNF);

    /* 上报给TAF，关机成功 */
    NAS_Mmc_SndMsccPowerOffCnf();

    /* Modified by s00246516 for L-C互操作项目, 2014-02-14, Begin */
    /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
    NAS_MMC_SndPowerOffRslt(NAS_MMC_POWEROFF_RSLT_POWER_OFF);
    /* Modified by s00246516 for L-C互操作项目, 2014-02-14, End */

    /* 关机完成，退出层二状态机*/
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmUsimStatusCnf_WaitLmmUsimStatusCnf
 功能描述  : ID_LMM_MMC_USIM_STATUS_CNF消息的处理
 输入参数  : ID_LMM_MMC_USIM_STATUS_CNF消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月1日
    作    者   : W00167002
    修改内容   : 新生成函数
  2.日    期   : 2011年7月25日
    作    者   : w00176964
    修改内容   : V7R1 PhaseII 全局变量 状态名调整
  3.日    期   : 2014年4月11日
    作    者   : w00166186
    修改内容   : DTS20120040600670,LTE主模时关机顺序不正确，导致单板复位
  4.日    期   : 2012年8月4日
    作    者   : w00167002
    修改内容   : V7R1C50_GUTL_PhaseII:G/U/L主模从上下文中获取;
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmUsimStatusCnf_PowerOff_WaitLmmUsimStatusCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* MMC停止定时器: TI_NAS_MMC_WAIT_LMM_USIM_STATUS_CNF */
    NAS_MMC_StopTimer( TI_NAS_MMC_WAIT_LMM_USIM_STATUS_CNF );

#if   (FEATURE_ON == FEATURE_LTE)

    if ( NAS_MML_NET_RAT_TYPE_LTE == NAS_MMC_GetMasterModeRat_PowerOff() )
    {

        /* 给LTE主模发送关机消息 */
        NAS_MMC_SndLmmStopReq();

        /* 迁移状态到NAS_MMC_POWEROFF::NAS_MMC_POWER_OFF_STA_WAIT_MASTER_MODE_POWEROFF_CNF,并启动10s保护定时器 */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_POWER_OFF_STA_WAIT_MASTER_MODE_POWEROFF_CNF);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MASTER_MODE_POWEROFF_CNF, TI_NAS_MMC_WAIT_MASTER_MODE_POWEROFF_CNF_LEN);

        return VOS_TRUE;
    }

#endif

    /* 通知MM关机，并设置等待MM回复标志 */
    NAS_MMC_SndMmPowerOffReq();

    NAS_MMC_SetMmPowerOffCnfFlag_PowerOff( NAS_MMC_MM_POWER_OFF_FLG );

    /* 通知GMM关机，并设置等待GMM回复标志 */
    NAS_MMC_SndGmmPowerOffReq();

    NAS_MMC_SetMmPowerOffCnfFlag_PowerOff( NAS_MMC_GMM_POWER_OFF_FLG );

    /* 迁移到 NAS_MMC_L2_STA_POWER_OFF:NAS_MMC_POWER_OFF_STA_WAIT_MM_POWEROFF_CNF状态,并启动保护定时器TI_NAS_MMC_WAIT_MM_POWEROFF_CNF*/
    NAS_MMC_FSM_SetCurrState(NAS_MMC_POWER_OFF_STA_WAIT_MM_POWEROFF_CNF);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_POWEROFF_CNF, TI_NAS_MMC_WAIT_MM_POWEROFF_CNF_LEN);

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmUsimStatusTimeOut_WaitLmmUsimStatusCnf
 功能描述  : TI_NAS_MMC_WAIT_LMM_USIM_STATUS_CNF 超时的处理
 输入参数  : TI_NAS_MMC_WAIT_LMM_USIM_STATUS_CNF 的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月1日
    作    者   : W00167002
    修改内容   : 新生成函数
  2.日    期   : 2011年7月25日
    作    者   : w00176964
    修改内容   : V7R1 PhaseII 全局变量 状态名调整
  3.日    期   : 2014年4月11日
    作    者   : w00166186
    修改内容   : DTS20120040600670,LTE主模时关机顺序不正确，导致单板复位
  4.日    期   : 2012年8月4日
    作    者   : w00167002
    修改内容   : V7R1C50_GUTL_PhaseII:G/U/L主模先关机;
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiWaitLmmUsimStatusExpired_PowerOff_WaitLmmUsimStatusCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
#if   (FEATURE_ON == FEATURE_LTE)

    if ( NAS_MML_NET_RAT_TYPE_LTE == NAS_MMC_GetMasterModeRat_PowerOff() )
    {

        /* 给LTE发送关机消息 */
        NAS_MMC_SndLmmStopReq();

        /* 迁移状态到NAS_MMC_POWEROFF::NAS_MMC_POWER_OFF_STA_WAIT_AS_POWEROFF_CNF,并启动10s保护定时器 */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_POWER_OFF_STA_WAIT_MASTER_MODE_POWEROFF_CNF);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MASTER_MODE_POWEROFF_CNF, TI_NAS_MMC_WAIT_MASTER_MODE_POWEROFF_CNF_LEN);

        return VOS_TRUE;
    }
#endif

    /* 通知MM关机，并设置等待MM回复标志 */
    NAS_MMC_SndMmPowerOffReq();

    NAS_MMC_SetMmPowerOffCnfFlag_PowerOff( NAS_MMC_MM_POWER_OFF_FLG );

    /* 通知GMM关机，并设置等待GMM回复标志 */
    NAS_MMC_SndGmmPowerOffReq();

    NAS_MMC_SetMmPowerOffCnfFlag_PowerOff( NAS_MMC_GMM_POWER_OFF_FLG );

    /* 迁移到 NAS_MMC_L2_STA_POWER_OFF:NAS_MMC_POWER_OFF_STA_WAIT_MM_POWEROFF_CNF状态,并启动保护定时器TI_NAS_MMC_WAIT_MM_POWEROFF_CNF*/
    NAS_MMC_FSM_SetCurrState(NAS_MMC_POWER_OFF_STA_WAIT_MM_POWEROFF_CNF);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_POWEROFF_CNF, TI_NAS_MMC_WAIT_MM_POWEROFF_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmMmcStatusInd_PowerOff_WaitEpsConnRelInd
 功能描述  : MMC收到LMM上报的Status Ind消息
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年4月10日
   作    者   : w00242748
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmMmcStatusInd_PowerOff_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_STATUS_IND_STRU                                *pstLmmStatusIndMsg = VOS_NULL_PTR;

    pstLmmStatusIndMsg  = ( LMM_MMC_STATUS_IND_STRU* )pstMsg;

    /* 更新EPS域的链接存在状态 */
    if ( (MMC_LMM_CONN_ESTING == pstLmmStatusIndMsg->ulConnState)
      || (MMC_LMM_CONNECTED_SIG == pstLmmStatusIndMsg->ulConnState) )
    {
        /* 设置存在EPS信令连接 */
        NAS_MML_SetEpsSigConnStatusFlg(VOS_TRUE);
    }
    else if (MMC_LMM_CONNECTED_DATA == pstLmmStatusIndMsg->ulConnState)
    {
        /* 设置存在EPS业务连接 */
        NAS_MML_SetEpsServiceConnStatusFlg(VOS_TRUE);
    }
    else if (MMC_LMM_CONN_IDLE == pstLmmStatusIndMsg->ulConnState)
    {
        /* 设置不存在EPS信令连接 */
        NAS_MML_SetEpsSigConnStatusFlg(VOS_FALSE);
        NAS_MML_SetEpsServiceConnStatusFlg(VOS_FALSE);
    }
    else
    {
        ;
    }

    /*  如果存在信令连接，则继续等待  */
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        return VOS_TRUE;
    }

    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND);

    /* 向MM/GMM发送Cover lost指示 */
    NAS_MMC_SndMmCoverageLostInd();
    NAS_MMC_SndGmmCoverageLostInd();

    /* 向TAF报出服务区流程 */
    NAS_MMC_SndMsccCoverageInd(NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST);

    /* 给当前接入结束发送SUSPEND REQ请求，指示当前接入层进入POWER SAVE模式 */
    NAS_MMC_SndSuspendReq_PowerOff(NAS_MML_GetCurrNetRatType());

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitEpsConnRelIndExpired_PowerOff_WaitEpsConnRelInd
 功能描述  : 等待连接释放定时器超时的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年4月10日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitEpsConnRelIndExpired_PowerOff_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 定时器超时，直接给当前接入技术发挂起 */
    /* 向MM/GMM发送Cover lost指示 */
    NAS_MMC_SndMmCoverageLostInd();
    NAS_MMC_SndGmmCoverageLostInd();

    /* 向TAF报出服务区流程 */
    NAS_MMC_SndMsccCoverageInd(NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST);

    /* 给当前接入结束发送SUSPEND REQ请求，指示当前接入层进入POWER SAVE模式 */
    NAS_MMC_SndSuspendReq_PowerOff(NAS_MML_GetCurrNetRatType());

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmSuspendInd_PowerOff_WaitEpsConnRelInd
 功能描述  : LMM上报的SUSPEND_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:返回处理成功
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年4月11日
   作    者   : w00242748
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmSuspendInd_PowerOff_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_SndLmmSuspendRsp(MMC_LMM_FAIL);

    return VOS_TRUE;
}

#endif

/*****************************************************************************
 函 数 名  : NAS_MMC_SndSlaveModePowerOffReq_PowerOff
 功能描述  : 给从模发送关机请求的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月26日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_SndSlaveModePowerOffReq_PowerOff(VOS_VOID)
{
    NAS_MML_PLMN_RAT_PRIO_STRU                 *pstSlaveModeRatList = VOS_NULL_PTR;
    VOS_UINT32                                  i;

    /* 获取从模关机列表 */
    pstSlaveModeRatList = NAS_MMC_GetSlaveModeRatList_PowerOff();

    /* 平台不是单模时，给从模发送关机消息 */
    for (i = 0; i < pstSlaveModeRatList->ucRatNum; i++)
    {
        /* 给GAS发送关机消息,设置等待gas回复标志 */
        if (NAS_MML_NET_RAT_TYPE_GSM == pstSlaveModeRatList->aucRatPrio[i])
        {
            NAS_MMC_SndAsPowerOffReq(UEPS_PID_GAS);
            NAS_MMC_SetAsPowerOffCnfFlag_PowerOff( NAS_MMC_GAS_POWER_OFF_FLG );
        }

        /* 给WAS发送关机消息,设置等待Was回复标志 */
        else if (NAS_MML_NET_RAT_TYPE_WCDMA == pstSlaveModeRatList->aucRatPrio[i])
        {
            NAS_MMC_SndAsPowerOffReq(WUEPS_PID_WRR);
            NAS_MMC_SetAsPowerOffCnfFlag_PowerOff( NAS_MMC_WAS_POWER_OFF_FLG );
        }

        /* 给LMM发送关机消息,设置等待LMM回复标志 */
#if (FEATURE_ON == FEATURE_LTE)
        else if (NAS_MML_NET_RAT_TYPE_LTE == pstSlaveModeRatList->aucRatPrio[i])
        {
            NAS_MMC_SndLmmStopReq();
            NAS_MMC_SetAsPowerOffCnfFlag_PowerOff( NAS_MMC_LTE_POWER_OFF_FLG );
        }
#endif
        else
        {
        }
    }

    return;

}



#if (FEATURE_ON == FEATURE_DSDS)
/*****************************************************************************
 函 数 名  : NAS_MMC_ProcRrmDeRegister_PowerOff
 功能描述  : 关机时处理向RRM发送去注册信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年1月22日
   作    者   : w00167002
   修改内容   : 新生成函数
                注:在后续的DSDS演进中，MMC在收到NO RF时候，才通知RRM进行当前接入
                技术的注册，在收到资源可用时候，则进行去注册。
 2.日    期   : 2014年7月26日
   作    者   : B00269685
   修改内容   : 接口变更
*****************************************************************************/
VOS_VOID NAS_MMC_ProcRrmDeRegister_PowerOff(VOS_VOID)
{
    MODEM_ID_ENUM_UINT16                usModemId;

    /* 取得当前MODEM的ID信息  */
    usModemId = VOS_GetModemIDFromPid(WUEPS_PID_MMC);

    /* 如果当前NV未开启DSDS,则不向RRM发送关机去注册 */
    if ( VOS_FALSE == NAS_MML_GetDsdsRfShareFlg() )
    {
        return;
    }

    /* 在MODEM0时候，向RRM发送W下的去注册信息 */
    if ( MODEM_ID_0 == usModemId )
    {
        NAS_MMC_SndRrmDeRegisterInd(MODEM_ID_0,
                                    RRM_PS_TASK_TYPE_NAS_SEARCH,
                                    VOS_RATMODE_WCDMA);
    }

    /* 在MODEM1时候，向RRM发送G下的去注册信息 */
    if ( MODEM_ID_1 == usModemId )
    {
        NAS_MMC_SndRrmDeRegisterInd(MODEM_ID_1,
                                    RRM_PS_TASK_TYPE_NAS_SEARCH,
                                    VOS_RATMODE_GSM);
    }

    return;
}

#endif

/* Added by s00246516 for L-C互操作项目, 2014-01-28, Begin */
/*****************************************************************************
 函 数 名  : NAS_MMC_SndSuspendReq_PowerOff
 功能描述  : 根据不同的接入技术向接入层或者LMM发送挂起请求
 输入参数  : enRat
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年2月14日
   作    者   : s00246516
   修改内容   : 新生成函数
 2.日    期   : 2014年1月28日
   作    者   : s00246516
   修改内容   : L-C互操作项目:增加获取和注册请求的处理
 3.日    期   : 2015年4月16日
   作    者   : w00242748
   修改内容   : iteration 13开发
*****************************************************************************/
VOS_VOID NAS_MMC_SndSuspendReq_PowerOff(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    /* 状态更新为当前未驻留 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

    NAS_MMC_SetAsAnyCampOn(VOS_FALSE);

    /* 根据不同的接入技术设置等待搜网回复的状态 */
    switch (enRat)
    {
#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:
            NAS_MMC_SndLmmSuspendReq();
            NAS_MMC_FSM_SetCurrState(NAS_MMC_POWER_OFF_STA_WAIT_LMM_SUSPEND_CNF);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_SUSPEND_CNF, TI_NAS_MMC_WAIT_LMM_SUSPEND_CNF_LEN);
            break;
#endif

        case NAS_MML_NET_RAT_TYPE_WCDMA:
            NAS_MMC_SndAsSuspendReq(WUEPS_PID_WRR);
            NAS_MMC_FSM_SetCurrState(NAS_MMC_POWER_OFF_STA_WAIT_WAS_SUSPEND_CNF);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF, TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF_LEN);
            break;

        case NAS_MML_NET_RAT_TYPE_GSM:
            NAS_MMC_SndAsSuspendReq(UEPS_PID_GAS);
            NAS_MMC_FSM_SetCurrState(NAS_MMC_POWER_OFF_STA_WAIT_GAS_SUSPEND_CNF);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF, TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF_LEN);
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndSuspendReq_PowerOff: Rat not support.");
            break;
    }

    return;
}
/* Added by s00246516 for L-C互操作项目, 2014-01-28, End */

/*****************************************************************************
 函 数 名  : NAS_MMC_SndRelReq_PowerOFf
 功能描述  : 根据不同的接入技术向MM/GMM或EPS发送释放请求，并迁移状态启动保护定时器
 输入参数  : enRat
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年4月10日
   作    者   : w00242748
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SndRelReq_PowerOff(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    /* 根据不同的接入技术分别处理 */
    switch (enRat)
    {
#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:

            /* 向EMM发送释放请求 */
            NAS_MMC_SndLmmRelReq();
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND, TI_NAS_MMC_WAIT_EPS_CONN_REL_IND_LEN);
            NAS_MMC_FSM_SetCurrState(NAS_MMC_POWER_OFF_STA_WAIT_EPS_CONN_REL_IND);
            break;
#endif

        case NAS_MML_NET_RAT_TYPE_WCDMA:
        case NAS_MML_NET_RAT_TYPE_GSM:

            /* 向MM/GMM发送释放请求 */
            NAS_MMC_SndMmRelReq();
            NAS_MMC_SndGmmRelReq();
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL, TI_NAS_MMC_WAIT_RRC_CONN_REL_LEN);

            NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);
            NAS_MMC_FSM_SetCurrState(NAS_MMC_POWER_OFF_STA_WAIT_RRC_CONN_REL_IND);

            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndRelReq_PowerOff: Rat not support.");
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGmmSignalingStatusInd_PowerOff_WaitRrcConnRelInd
 功能描述  : MMCGMM_SIGNALING_STATUS_IND链接消息处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年4月10日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvGmmSignalingStatusInd_PowerOff_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /*  如果存在信令连接，则继续等待  */
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        return VOS_TRUE;
    }

    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);

    /* 向MM/GMM发送Cover lost指示 */
    NAS_MMC_SndMmCoverageLostInd();
    NAS_MMC_SndGmmCoverageLostInd();

    /* 向TAF报出服务区流程 */
    NAS_MMC_SndMsccCoverageInd(NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST);

    /* 给当前接入结束发送SUSPEND REQ请求，指示当前接入层进入POWER SAVE模式 */
    NAS_MMC_SndSuspendReq_PowerOff(NAS_MML_GetCurrNetRatType());

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGmmTbfRelInd_PowerOff_WaitRrcConnRelInd
 功能描述  : 处理TBF连接消息
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年4月10日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvGmmTbfRelInd_PowerOff_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /*  如果存在信令连接，则继续等待  */
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        return VOS_TRUE;
    }

    /* 停止等待连接释放定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);

    /* 向MM/GMM发送Cover lost指示 */
    NAS_MMC_SndMmCoverageLostInd();
    NAS_MMC_SndGmmCoverageLostInd();

    /* 向TAF报出服务区流程 */
    NAS_MMC_SndMsccCoverageInd(NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST);

    /* 给当前接入结束发送SUSPEND REQ请求，指示当前接入层进入POWER SAVE模式 */
    NAS_MMC_SndSuspendReq_PowerOff(NAS_MML_GetCurrNetRatType());

    return VOS_TRUE;
}

/*************************************?****************************************
 函 数 名  : NAS_MMC_RcvMmConnInfoInd_PowerOff_WaitRrcConnRelInd
 功能描述  : MMCMM_RR_CONN_INFO_IND链接消息处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年4月10日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvMmConnInfoInd_PowerOff_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /*  如果存在信令连接，则继续等待  */
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        return VOS_TRUE;
    }

    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);

    /* 向MM/GMM发送Cover lost指示 */
    NAS_MMC_SndMmCoverageLostInd();
    NAS_MMC_SndGmmCoverageLostInd();

    /* 向TAF报出服务区流程 */
    NAS_MMC_SndMsccCoverageInd(NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST);

    /* 给当前接入结束发送SUSPEND REQ请求，指示当前接入层进入POWER SAVE模式 */
    NAS_MMC_SndSuspendReq_PowerOff(NAS_MML_GetCurrNetRatType());

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmRrRelInd_PowerOff_WaitRrcConnRelInd
 功能描述  : MMCMM_RR_CONN_INFO_IND链接消息处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年4月10日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmRrRelInd_PowerOff_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /*  如果存在信令连接，则继续等待  */
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        return VOS_TRUE;
    }

    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);

    /* 向MM/GMM发送Cover lost指示 */
    NAS_MMC_SndMmCoverageLostInd();
    NAS_MMC_SndGmmCoverageLostInd();

    /* 向TAF报出服务区流程 */
    NAS_MMC_SndMsccCoverageInd(NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST);

    /* 给当前接入结束发送SUSPEND REQ请求，指示当前接入层进入POWER SAVE模式 */
    NAS_MMC_SndSuspendReq_PowerOff(NAS_MML_GetCurrNetRatType());

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmRelInd_PowerOff_WaitRrcConnRelInd
 功能描述  : RRMM_REL_IND处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月10日
    作    者   : w00242748
    修改内容   : 新生成函数
*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvRrMmRelInd_PowerOff_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_REL_IND_STRU                  *pstRelIndMsg = VOS_NULL_PTR;

    pstRelIndMsg = ( RRMM_REL_IND_STRU * )pstMsg;

    /* 清除连接存在标志 */
    if (RRC_RRC_CONN_STATUS_ABSENT == pstRelIndMsg->ulRrcConnStatus)
    {
        NAS_MML_SetRrcConnStatusFlg(VOS_FALSE);
    }

    /*  如果存在信令连接，则继续等待  */
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        return VOS_TRUE;
    }

    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);

    /* 向MM/GMM发送Cover lost指示 */
    NAS_MMC_SndMmCoverageLostInd();
    NAS_MMC_SndGmmCoverageLostInd();

    /* 向TAF报出服务区流程 */
    NAS_MMC_SndMsccCoverageInd(NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST);

    /* 给当前接入结束发送SUSPEND REQ请求，指示当前接入层进入POWER SAVE模式 */
    NAS_MMC_SndSuspendReq_PowerOff(NAS_MML_GetCurrNetRatType());

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmSuspendCnf_PowerOff_WaitWasSuspendCnf
 功能描述  : 收到AS的suspend cnf消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年4月10日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvRrMmSuspendCnf_PowerOff_WaitWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_CNF_ST                *pstSuspendCnf = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU          stDestPlmn;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    pstSuspendCnf = (RRMM_SUSPEND_CNF_ST*)pstMsg;

    /* 解决版本Coverity问题 */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    enCurRat      = NAS_MML_GetCurrNetRatType();

    /* 停止定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF);

    if (MMC_AS_SUSPEND_FAILURE == pstSuspendCnf->ucResult)
    {
        /* 不可恢复错误,调用底软接口RESET */

        if ( (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
          && (NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat) )
        {
            NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_WAS_SUSPEND_FAILURE);
        }
        else
        {
            NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_TD_SUSPEND_FAILURE);
        }

        return VOS_TRUE;
    }


    /* 设置当前接入技术为BUTT */
    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

    /* 上报给MSCC Power Save成功 */
    NAS_MMC_SndMsccPowerSaveCnf(NAS_MSCC_PIF_POWER_SAVE_SUCCESS);

    /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
    NAS_MMC_SndPowerOffRslt(NAS_MMC_POWEROFF_RSLT_POWER_SAVE);

    /* 关机完成，退出层二状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitAsSuspendCnfExpired_PowerOff_WaitAsSuspendCnf
 功能描述  : suspend CNF过程中保护定时器超时
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年4月10日
   作    者   : w00242748
   修改内容   : 新生成函数

****************************************************************************/

VOS_UINT32 NAS_MMC_RcvTiWaitAsSuspendCnfExpired_PowerOff_WaitAsSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    enCurRat      = NAS_MML_GetCurrNetRatType();

    /* 不可恢复故障，复位 */

    if ( (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
      && (NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat) )
    {
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_WAS_SUSPEND_CNF_EXPIRED);
    }
    else if ( NAS_MML_NET_RAT_TYPE_GSM == enCurRat )
    {
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_GAS_SUSPEND_CNF_EXPIRED);
    }
    else
    {
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_TD_SUSPEND_CNF_EXPIRED);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmSuspendCnf_PowerOff_WaitGasSuspendCnf
 功能描述  : 收到GAS的suspend cnf消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年4月10日
   作    者   : w00242748
   修改内容  :  新生成函数
*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvRrMmSuspendCnf_PowerOff_WaitGasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_CNF_ST                *pstSuspendCnf = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU          stDestPlmn;

    pstSuspendCnf = (RRMM_SUSPEND_CNF_ST*)pstMsg;

    /* 解决版本Coverity问题 */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    /* 停止定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF);

    if (MMC_AS_SUSPEND_FAILURE == pstSuspendCnf->ucResult)
    {
        /* 不可恢复错误,调用底软接口RESET */

        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_GAS_SUSPEND_FAILURE);

        return VOS_TRUE;
    }

    /* 设置当前接入技术为BUTT */
    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

    /* 上报给MSCC Power Save成功 */
    NAS_MMC_SndMsccPowerSaveCnf(NAS_MSCC_PIF_POWER_SAVE_SUCCESS);

    /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
    NAS_MMC_SndPowerOffRslt(NAS_MMC_POWEROFF_RSLT_POWER_SAVE);

    /* 关机完成，退出层二状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitRrcConnRelExpired_PowerOff_WaitRrcConnRelInd
 功能描述  : 链接释放状态超时处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年4月10日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitRrcConnRelExpired_PowerOff_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 定时器超时，直接给当前接入技术发挂起 */
    /* 向MM/GMM发送Cover lost指示 */
    NAS_MMC_SndMmCoverageLostInd();
    NAS_MMC_SndGmmCoverageLostInd();

    /* 向TAF报出服务区流程 */
    NAS_MMC_SndMsccCoverageInd(NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST);

    /* 给当前接入结束发送SUSPEND REQ请求，指示当前接入层进入POWER SAVE模式 */
    NAS_MMC_SndSuspendReq_PowerOff(NAS_MML_GetCurrNetRatType());

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvWasSuspendInd_PowerOff_WaitRrcConnRelInd
 功能描述  : WAS上报的SUSPEND_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年4月11日
   作    者   : w00242748
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvWasSuspendInd_PowerOff_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_SndAsSuspendRsp(RRC_NAS_SUSPEND_FAILURE, WUEPS_PID_WRR);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGasSuspendInd_PowerOff_WaitRrcConnRelInd
 功能描述  : GAS上报的SUSPEND_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年4月11日
   作    者   : w00242748
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvGasSuspendInd_PowerOff_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_SndAsSuspendRsp(RRC_NAS_SUSPEND_FAILURE, UEPS_PID_GAS);

    return VOS_TRUE;
}



/*lint -restore */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

