/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcFsmMain.c
  版 本 号   : 初稿
  作    者   : zhoujun /40661
  生成日期   : 2011年5月9日
  最近修改   :
  功能描述   : 主状态机处理函数
  函数列表   :
  修改历史   :
  1.日    期   : 2011年04月01日
    作    者   : zhoujun /40661
    修改内容   : 创建文件

******************************************************************************/
/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "NasMmcCtx.h"
#include "NasMmlLib.h"
#include "NasMmlCtx.h"
#include "NasMmlMsgProc.h"
#include "NasComm.h"
#include "NasMmcSndGuAs.h"
#include "NasMmcSndLmm.h"
#include "NasMmcSndMm.h"
#include "NasMmcSndGmm.h"
#include "NasMmcSndMscc.h"
#include "NasMmcSndInternalMsg.h"
#include "NasMmcFsmMain.h"
#include "NasMmcMain.h"
#include "NasMmcProcRegRslt.h"
#include "NasMmcProcNvim.h"
#include "NasMmcProcUsim.h"
#include "NasMmcTimerMgmt.h"
/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, begin */
/* 删除ExtAppMmcInterface.h*/
/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, end */
#include "NasMmcComFunc.h"
#include "NasMmcSndOm.h"
#include "NasMmcFsmSyscfg.h"
#include "NasMmcPreProcAct.h"
#include "NasMmcPlmnSelectionStrategy.h"
#include "NasMmcFsmMainTbl.h"
#include "NVIM_Interface.h"

#include "NasUtranCtrlInterface.h"
#include "NasMmlLib.h"

/* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
#include "MsccMmcInterface.h"
/* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

#include "NasMmcProcSuspend.h"
#include "NasMmcSndCss.h"
/* added by wx270776 for OM融合, 2015-08-21, begin */
#include "OmApi.h"
/* added by wx270776 for OM融合, 2014-08-21, end */

#include "NasMmcFsmPlmnSelection.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_FSMMAIN_C

/*****************************************************************************
  2 全局变量
*****************************************************************************/
/*****************************************************************************
  3 宏定义
*****************************************************************************/

extern VOS_VOID SLEEP_EnterLowPower(VOS_VOID);

/*lint -save -e958 */

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvStartReq_NULL
 功能描述  : NULL状态(刚上电时MMC PID初始化时MMC所处的状态，软关机后所处的状态)
             收到ID_MSCC_MMC_START_REQ后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:ID_MSCC_MMC_START_REQ消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年3月19日
    作    者   : luokaihui /l00167671
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvStartReq_NULL(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_SWITCH_ON);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvSwitchOnRslt_NULL
 功能描述  : 收到开机结果后，若成功则迁移到NAS_MMC_L1_STA_INITIAL状态
             若失败保持NAS_MMC_L1_STA_NULL状态不变
 输入参数  : ulEventType:消息类型
             pstMsg:开机消息
 输出参数  : 无
 返 回 值  : VOS_OK: 函数处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月23日
    作    者   : wenlutao /w00176964
    修改内容   : 新生成函数
  2.日    期   : 2011年12月15日
    作    者   : w00167002
    修改内容   : DTS2011120702166:开机失败，不进行软复位，删除复位信息。
  3.日    期   : 2015年5月4日
    作    者   : w00242748
    修改内容   : CMDA迭代13代码开发
  4.日    期   : 2015年8月24日
    作    者   : m00312079
    修改内容   : DTS2015082400829:CL模式切换到DEACT态，GUL模式切换到INITIAL态
*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvSwitchOnRslt_NULL(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_SWITCHON_RLST_STRU                 *pstSwitchOnMsg;

    pstSwitchOnMsg                      = (NAS_MMC_SWITCHON_RLST_STRU *)pstMsg;

    /* 收到开机结果后，若成功迁移到NAS_MMC_L1_STA_INITIAL状态，
       失败保持NAS_MMC_L1_STA_NULL状态
    */
    if (VOS_TRUE == pstSwitchOnMsg->ulResult)
    {
        if (VOS_TRUE == NAS_MML_IsGULModeConfigured())
        {
            NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);
        }
        else
        {
            NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_DEACT);
        }
    }
    else
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvSwitchOnRslt_NULL:开机失败");
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvPowerOffReq_NULL
 功能描述  : 在关机状态受到关机请求的处理
 输入参数  : ulEventType:消息类型
             pstMsg:开机消息
 输出参数  : 无
 返 回 值  : VOS_OK: 函数处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月30日
    作    者   : b00269685
    修改内容   : 新生成函数
*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvPowerOffReq_NULL(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvPowerOffReq_NULL:rcv power off req in NULL state");

    /* 已经为关机状态，直接回复MSCC成功 */
    NAS_Mmc_SndMsccPowerOffCnf();

    return VOS_TRUE;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_RcvPowerOffReq_L1Main
 功能描述  : 收到ID_MSCC_MMC_POWER_OFF_REQ消息的处理
 输入参数  : ulEventType:关机消息长度
             pstMsg: 关机消息
 输出参数  : 无
 返 回 值  : VOS_OK: 函数处理消息成功
              VOS_ERR: 函数处理消息失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月1日
    作    者   : w00167002
    修改内容   : 新生成函数

  2.日    期   : 2011年8月5日
    作    者   : w00176964
    修改内容   : V7R1 PhaseII 调整

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvPowerOffReq_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_POWER_OFF);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvPowerOffRslt_L1Main
 功能描述  : 在空闲态时候收到NAS_MM_LAYER_MMCMMC_POWER_OFF_RSLT消息的处理
 输入参数  : ulEventType:NAS_MM_LAYER_MMCMMC_POWER_OFF_RSLT消息类型
             pstMsg: NAS_MM_LAYER_MMCMMC_POWER_OFF_RSLT消息
 输出参数  : 无
 返 回 值  : VOS_TRUE: 函数处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月1日
    作    者   : w00167002
    修改内容   : 新生成函数

  2.日    期   : 2012年7月13日
    作    者   : w00167002
    修改内容   : V7R1C50_GUTL_PhaseI修改
  3.日    期   : 2015年4月7日
    作    者   : l00324781
    修改内容   : Mmc Power Save后，不再进入OOC状态，而是进入Deactive状态
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvPowerOffRslt_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMCMMC_POWEROFF_RSLT_STRU      *pstPowerOffRslt;    /* 关机的结果 */
    NAS_MMC_CONTEXT_STRU               *pstMmcCtx = VOS_NULL_PTR;
    NAS_MML_CTX_STRU                   *pstMmlCtx = VOS_NULL_PTR;

    pstPowerOffRslt = (NAS_MMCMMC_POWEROFF_RSLT_STRU*)pstMsg;

    /* 关机完成 */
    /* Modified by s00246516 for L-C互操作项目, 2014-01-28, Begin */
    if ( NAS_MMC_POWEROFF_RSLT_POWER_OFF == pstPowerOffRslt->enRslt )
    /* Modified by s00246516 for L-C互操作项目, 2014-01-28, End */
    {
        /* 初始化MML模块CTX */
        pstMmlCtx   = NAS_MML_GetMmlCtx();
        NAS_MML_InitCtx(NAS_MML_INIT_CTX_POWEROFF, pstMmlCtx);


        /* 支持TD时，对NASUTRANCTRL上下文进行初始化 */
        NAS_UTRANCTRL_InitCtx(NAS_MML_INIT_CTX_POWEROFF);

        /* 初始化MMC模块CTX */
        pstMmcCtx   = NAS_MMC_GetMmcCtxAddr();
        NAS_MMC_InitCtx(NAS_MMC_INIT_CTX_POWEROFF, pstMmcCtx);

        NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_NULL);
    }
    /* Added by s00246516 for L-C互操作项目, 2014-01-28, Begin */
    else if (NAS_MMC_POWEROFF_RSLT_POWER_SAVE == pstPowerOffRslt->enRslt)
    {
        NAS_MMC_StopAllTimer();

        NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_DEACT);

        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_BUTT);

        OM_SetDrxTimerWakeSrc(VOS_GetModemIDFromPid(WUEPS_PID_MMC));
        NAS_MMC_SndDrxTimerInfo(VOS_TRUE);
    }
    /* Added by s00246516 for L-C互操作项目, 2014-01-28, end */
    else
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvPowerOffRslt_L1Main:关机结果失败");
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvSysCfgReq_L1Main
 功能描述  : L1(onplmn/initial/ooc)状态机下收到SYSCFG设置
 输入参数  : ulEventType:消息类型
              pstMsg: ID_MSCC_MMC_SYS_CFG_SET_REQ消息首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE: 函数处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月10日
    作    者   : w00167002
    修改内容   : 新生成函数

  2.日    期   : 2011年8月5日
    作    者   : w00176964
    修改内容   : V7R1 PhaseII 调整

  3.日    期   : 2011年8月26日
    作    者   : w00176964
    修改内容   : V7R1 PhaseII 调整:临时解决缓存处理中不进预处理中的逻辑

  4.日    期   : 2012年5月15日
    作    者   : l00130025
    修改内容   : DTS2012041002516: L下默认承载存在数据连接时设置W only失败

  5.日    期   : 2012年11月7日
    作    者   : s00217060
    修改内容   : DTS2012060507813: GU下存在PS业务时，MMC向MM/GMM发送释放请求，连接释放后，下发SYSCFG
  6.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvSysCfgReq_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMC_SYS_CFG_SET_REQ_STRU        *pstSysCfgSetParm = VOS_NULL_PTR;
    VOS_UINT32                          ulSyscfgNeedPlmnSrchRslt;
    VOS_UINT32                          ulCsServiceExist;

    pstSysCfgSetParm         = (MSCC_MMC_SYS_CFG_SET_REQ_STRU*)pstMsg;

    /* 判断当前SYSCFG设置是否需要导致搜网 */
    ulSyscfgNeedPlmnSrchRslt = NAS_MMC_IsPlmnSelectionNeeded_SysCfg(pstSysCfgSetParm);

    /* 判断当前是否有CS业务存在 */
    ulCsServiceExist         = NAS_MML_GetCsServiceExistFlg();


    /* 如果SYSCFG导致需要搜网且当前有业务存在或者有缓存的业务存在
     那么不进行SYSCFG设置，向MSCC返回SYSCFG 设置失败*/

    /* GU下存在PS业务时，MMC给MM/GMM发送释放请求，连接释放后，可下发SYSCFG，和L的处理相同
       存在CS业务时，MMC向MSCC上报SYSCFG结果为有CS业务存在 */
    if (VOS_TRUE == ulSyscfgNeedPlmnSrchRslt)
    {
        if (VOS_TRUE == ulCsServiceExist)
        {
            NAS_MMC_SndMsccSysCfgCnf(NAS_MSCC_PIF_SYS_CFG_SET_FAILURE_CS_SERV_EXIST);
            return VOS_TRUE;
        }
        else
        {

        }
    }

    /* 调起SYSCFG子状态机 */
    NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_SYSCFG);

    return VOS_TRUE;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_MMC_ProcSyscfgRsltDisableEnable_OnPlmn
 功能描述  : 处理SYSCFG结果导致的disable/enable的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年6月26日
   作    者   : w00176964
   修改内容   : 新生成函数

  2.日    期   : 2012年06月13日
    作    者   : s46746
    修改内容   : For CS/PS mode 1，调整Disable/Enable L,按场景区分函数
  3.日    期   : 2012年7月27日
    作    者   : s00217060
    修改内容   : For CS/PS mode 1,带Disable LTE原因值
  4.日    期   : 2013年01月23日
    作    者   : s00217060
    修改内容   : 问题单: DTS2013012106172,Enable Lte时停止定时器TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER
  5.日    期   : 2013年11月01日
    作    者   : l00208543
    修改内容   : 根据卡类型禁止网络制式
  6.日    期   : 2015年1月5日
    作    者   : z00161729
    修改内容   : AT&T 支持DAM特性修改
  7.日    期   : 2015年2月26日
    作    者   : w00167002
    修改内容   : DTS2015021604972:在SYSCFG设置完后，MMA进行ATTACH流程。MMC已经退出
                 SYSCFG状态机，并触发搜网。在搜网时候，如果PS不准许ATTACH，则不搜索LTE.
                 现修改为在SYSCFG后,如果需要搜网，则判别是否ATTACH PS需要先ENABLE LTE。
*****************************************************************************/
VOS_VOID  NAS_MMC_ProcSyscfgRsltDisableEnable_OnPlmn(
    NAS_MMCMMC_SysCfg_RSLT_STRU        *pstSyscfgRsltMsg
)
{
    VOS_UINT32                                    ulDisablteRoamFlg;
    MMC_LMM_DISABLE_LTE_REASON_ENUM_UINT32        enDisablteReason;
    /* 接入模式改变后判断是否需要disable LTE */
    ulDisablteRoamFlg = NAS_MML_GetDisableLteRoamFlg();

    if (VOS_TRUE == NAS_MMC_IsNeedDisableLte_SysCfg(pstSyscfgRsltMsg))
    {
        /* 如果这时LTE在禁止接入技术列表里，将reason设置为MMC_LMM_DISABLE_LTE_REASON_IMSI_IN_FORBIDDEN_LIST */
        if (VOS_TRUE == NAS_MML_IsRatInForbiddenList(NAS_MML_NET_RAT_TYPE_LTE))
        {
            NAS_MML_SetLteForbiddenStatusFlg(NAS_MML_RAT_CAPABILITY_STATUS_DISABLE);
            enDisablteReason = MMC_LMM_DISABLE_LTE_REASON_IMSI_IN_FORBIDDEN_LIST;
        }
        /* 如果这时是SIM卡，则将reason设置为MMC_LMM_DISABLE_LTE_REASON_SIM_CARD_SWITCH_ON */
        else if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
        {
            enDisablteReason = MMC_LMM_DISABLE_LTE_REASON_SIM_CARD_SWITCH_ON;
        }
        else if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
        {
            enDisablteReason = MMC_LMM_DISABLE_LTE_REASON_PS_DETACH;
        }
        else
        {
            enDisablteReason = MMC_LMM_DISABLE_LTE_REASON_PS_USIM_INVALID;
        }

        /* 当前网络为LTE，则暂时不发送disable LTE消息 */
        if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
        {
            NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS);
        }
        else
        {
            /* 如果漫游导致的disable已经通知了GU接入层,此时不需要再重复通知 */
            if (VOS_FALSE == ulDisablteRoamFlg)
            {
                NAS_MMC_SndDisableLteNotify(enDisablteReason);

                /* 记录disable lte时驻留的网络信息 */
                NAS_MMC_SetDisabledLtePlmnId(NAS_MML_GetCurrCampPlmnId());
            }

            /* 更新disable LTE能力标记 */
            NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS);
        }
        NAS_MML_SetDisableLteReason(enDisablteReason);
    }
    /* 判断当前是否需要enable LTE */
    else if (VOS_TRUE == NAS_MMC_IsNeedEnableLte_SysCfg(pstSyscfgRsltMsg))
    {
        /* 如果由于禁止LTE国际漫游导致的disable LTE，再未回到国内之前此时也不通知enable LTE */
        if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == NAS_MML_GetLteCapabilityStatus())
         && (VOS_FALSE == ulDisablteRoamFlg))
        {
            NAS_MMC_SndEnableLteNotify();
            NAS_MMC_ClearDisabledLtePlmnId();
            NAS_MMC_SetEnableLteTimerExpireFlag(VOS_FALSE);
        }

        if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER))
        {
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER);
        }

        /* 更新disable LTE能力标记 */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_REENABLE_NOTIFIED_AS);
    }
    else
    {

    }
}
#endif

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvSysCfgRslt_TrigSrvStaPlmnSrch_OnPlmn
 功能描述  : 处理SYSCFG结果中，由于服务状态触发的搜网
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE 表示已经处理完
             VOS_FALSE 表示还未处理完
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年4月17日
   作    者   : w00242748
   修改内容   : 新生成函数
 2.日    期   : 2014年5月24日
   作    者   : w00242748
   修改内容   : DTS2014052106103:支持接入技术从0102设置成010203，触发高优先级接入
                技术搜网，由于L无覆盖，导致搜索LTE时间较长，15s内，AP侧下发detach
                请求，但此时MSCC的服务状态为正常服务，所以导致DETACH失败，从而AP侧
                主动进行复位。
  3.日    期   : 2014年7月14日
    作    者   : w00242748
    修改内容   : DTS2014063003419:SYSCFG触发高优先级接入技术搜网增加NV控制
  4.日    期   : 2014年10月23日
    作    者   : s00217060
    修改内容   : DTS2014101707757:SYSCFG触发高优先级接入技术搜网时，报服务状态时，
                 同时更新注册状态，否则服务状态为限制服务，注册状态为已注册，
                 AT+COPS?查询时，查询不到PLMN
 5.日    期   : 2015年8月6日
   作    者   : c00318887
   修改内容   : DTS2015041401965，syscfg设置只在增加接入技术且新增接入技术优先级高于当前接入技术才触发搜网
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvSysCfgRslt_TrigSrvStaPlmnSrch_OnPlmn(
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrePrioRatList
)
{
    VOS_UINT32                          ulFlg;
    VOS_UINT32                          ulSpecPlmnSearchFlg;
    VOS_UINT32                          ulCsServiceExistFlg;

    /* 判断当前是否在正常服务状态，若不是则发起搜网 */
    ulFlg               = NAS_MMC_IsNormalServiceStatus();
    ulSpecPlmnSearchFlg = NAS_MMC_GetSpecPlmnSearchState();

    if ((VOS_FALSE  == ulFlg )
     || (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == ulSpecPlmnSearchFlg))
    {

        /* 如果存在CS业务 */
        if (VOS_TRUE == NAS_MML_GetCsServiceExistFlg())
        {
            NAS_MMC_SetBufferedPlmnSearchInfo(VOS_TRUE, NAS_MMC_PLMN_SEARCH_SCENE_SYSCFG_SET);
            return VOS_TRUE;
        }

        /* 迁移到Intial状态 */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);


        /* 当前接入模被SYSCFG/SYSCFGEX设置为不支持，后续搜网无需挂起当前模 */

        if ( VOS_FALSE == NAS_MML_IsNetRatSupported(NAS_MML_GetCurrNetRatType()) )
        {
            /* SYSCFG搜网不需要进行挂起操作，设置当前接入技术为BUTT */
            NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

            /* 设置进入搜网状态 */
            NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);
        }

        if (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == NAS_MMC_GetSpecPlmnSearchState())
        {
            /* 设置当前驻留网络的系统模式为BUTT  */
            NAS_MML_SetCurrSysSubMode(NAS_MML_RRC_SYS_SUBMODE_BUTT);
        }

        /* 构造并发送内部搜网信息:场景SYSCFG */
        NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_SYSCFG_SET, VOS_NULL_PTR, 0);
        return VOS_TRUE;
    }


    if ( VOS_TRUE == NAS_MML_GetSyscfgTriHighRatSrchFlg() )
    {
        ulCsServiceExistFlg = NAS_MML_GetCsServiceExistFlg();
        if ( (VOS_TRUE == NAS_MMC_IsRatPrioChangeTriggerPlmnSrch(pstPrePrioRatList, NAS_MML_GetMsPrioRatList()))
          && (VOS_FALSE == ulCsServiceExistFlg) )
        {
            if ( VOS_TRUE == NAS_MMC_IsNormalServiceStatus() )
            {
                /* SYSCFG设置后需要搜网，更新为限制服务状态并上报 */
                NAS_MMC_SetCsServiceStatus(NAS_MMC_LIMITED_SERVICE);
                NAS_MMC_SetPsServiceStatus(NAS_MMC_LIMITED_SERVICE);
                NAS_MMC_SndMsccServiceStatusInd(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MSCC_PIF_SERVICE_STATUS_LIMITED_SERVICE);
                NAS_MMC_UpdateRegStateSpecPlmnSearch();
            }

            /* 迁移到Intial状态 */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

            /* 构造并发送内部搜网信息:场景SYSCFG */
            NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_SYSCFG_SET, VOS_NULL_PTR, 0);

            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ProcSyscfgRsltPlmnSrch_OnPlmn
 功能描述  : 处理SYSCFG结果导致搜网的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年6月26日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2012年10月31日
   作    者   : t00212959
   修改内容   : DTS2012103100827:syscfg 之后导致的搜网在正常服务时才上报refresh
 3.日    期   : 2013年3月30日
   作    者   : l00167671
   修改内容   : 主动上报AT命令控制下移至C核
 4.日    期   : 2014年10月23日
   作    者   : s00217060
   修改内容   : DTS2014101707757:SYSCFG触发高优先级接入技术搜网时，报服务状态时，
                同时更新注册状态，否则服务状态为限制服务，注册状态为已注册，
                AT+COPS?查询时，查询不到PLMN
*****************************************************************************/
VOS_VOID  NAS_MMC_ProcSyscfgRsltPlmnSrch_OnPlmn(VOS_VOID)
{
    /* 迁移到Intial状态 */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);


    /* 当前接入模被SYSCFG/SYSCFGEX设置为不支持，后续搜网无需挂起当前模 */


    if ( VOS_FALSE == NAS_MML_IsNetRatSupported(NAS_MML_GetCurrNetRatType()) )
    {
        /* SYSCFG搜网不需要进行挂起操作，设置当前接入技术为BUTT */
        NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

        /* 设置进入搜网状态 */
        NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

    }

    if (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == NAS_MMC_GetSpecPlmnSearchState())
    {
        /* 设置当前驻留网络的系统模式为BUTT  */
        NAS_MML_SetCurrSysSubMode(NAS_MML_RRC_SYS_SUBMODE_BUTT);
    }


    if ( VOS_TRUE == NAS_MMC_IsNormalServiceStatus() )
    {
        /* SYSCFG设置后需要搜网，更新为限制服务状态并上报 */
        NAS_MMC_SetCsServiceStatus(NAS_MMC_LIMITED_SERVICE);
        NAS_MMC_SetPsServiceStatus(NAS_MMC_LIMITED_SERVICE);
        NAS_MMC_SndMsccServiceStatusInd(NAS_MSCC_PIF_SRVDOMAIN_NOT_REG_PLMN_SEARCHING, NAS_MSCC_PIF_SERVICE_STATUS_LIMITED_SERVICE);
        NAS_MMC_UpdateRegStateSpecPlmnSearch();
}

    /* 构造并发送内部搜网信息:场景SYSCFG */
    NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_SYSCFG_SET, VOS_NULL_PTR, 0);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvSyscfgRsltCnf_L1Main
 功能描述  : L1(onplmn/initial/ooc)状态机下收到SYSCFG结果的处理
 输入参数  : ulEventType:消息类型
             pstMsg: MMCMMC_SYSCFG_RSLT_CNF消息首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE: 函数处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月22日
   作    者   : w00176964
   修改内容   : 新生成函数

 2.日    期   : 2011年8月22日
   作    者   : w00167002
   修改内容   : V7R1 Phase II 调整:增加对SYSCFG结果的处理

 3.日    期   : 2011年10月18日
   作    者   : w00167002
   修改内容   : V7R1 Phase II 调整:当前接入模被SYSCFG/SYSCFGEX设置为不支持，
                后续搜网无需挂起当前模

  4.日    期   : 2011年12月01日
    作    者   : w00176964
    修改内容   : V7R1 Phase IV调整:disable/enable 调整
  5.日    期   : 2012年3月17日
    作    者   : w00176964
    修改内容   : DTS2012031900095 V7R1 C30 SBM&EM定制需求:增加LTE国家漫游功能定制
  6.日    期   : 2012年4月25日
    作    者   : w00166186
    修改内容   : DTS2012042305019 PS ONLY驻留LTE情况下，SYSCFG设置L->LU后又搜索
                 当前网络
  7.日    期   : 2012年5月22日
    作    者   : L60609
    修改内容   : DTS2012051707660:L单模设置W单模，W搜网过程中设置L单模，L模注册成功后g_StatusContext.ucCurRaForSysInfo
                 未更新
  8.日    期   : 2012年6月8日
    作    者   : z40661
    修改内容   : DTS2012060503632: 接入模式设置为butt时,有可能需要触发搜网,需要将搜网标识置上。
  9.日    期   : 2012年6月21日
    作    者   : l00130025
    修改内容   : DTS2012061908446: 非驻留状态设置，系统的子模式，需要设置为BUTT,以触发MMA Mode更新
 10.日    期   : 2012年6月26日
    作    者   : w00176964
    修改内容   : DTS2012061908446: 降圈复杂度

  11.日    期   : 2012年7月6日
    作    者   : z00161729
    修改内容   : DTS2012062502088:hplmn为23002，驻留W的46002，UPLMN为L的46002，syscfg设置不支持L,不启动hplmn定时器，
                 后续syscfg设置支持L,标杆会立即启动hplmn，NAS不会，修改与标杆做成一致
 12.日    期   : 2012年08月26日
    作    者   : l65478
    修改内容   : DTS2012081507333:在快速指定搜网过程中设置SYSCFG,设置结束后没有发起搜网

  13.日    期   : 2012年9月25日
    作    者   : z40661
    修改内容   : DTS2012082006273,anycell搜网状态机被打断时，设置syscfg命令
                 ，此时卡无效，但未发起搜索

  14.日    期   : 2013年6月25日
     作    者   : z00234330
     修改内容   : DTS2013061808384,syscfgex状态机退出时，未判断业务存在情况
  15.日    期   : 2014年2月10日
     作    者   : w00242748
     修改内容   : DTS2014020700426:syscfg打断内部列表搜后，不发起搜网。SVLTE需要
                  快速找回TL，所以应尽量让其快速找回。
  16.日    期   : 2014年2月24日
     作    者   : w00176964
     修改内容   : High_Rat_Hplmn_Search特性调整:增加High_Prio_rat_hplmn定时器的启动处理
  17.日    期   : 2014年4月16日
     作    者   : w00242748
     修改内容   : DTS2014041704339:SYSCFG设置0201后，注册在W上，然后再设置030201后
                  需要触发高优先级搜网。
  18.日    期   : 2014年10月27日
     作    者   : b00269685
     修改内容   : 增加High_Prio_rat_hplmn TD Count的处理
  19.日    期   : 2015年08月06日
     作    者   : c00318887
     修改内容   : DTS2015041401965，syscfg设置只在增加接入技术且新增接入技术优先级高于当前接入技术才触发搜网
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvSyscfgRsltCnf_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulUsimStausFlg;
    VOS_UINT32                          ulSpecPlmnSearchFlg;
    NAS_MMCMMC_SysCfg_RSLT_STRU        *pstSysCfgMsg    = VOS_NULL_PTR;

    VOS_UINT8                           ucCsAttachAllow;
    VOS_UINT8                           ucPsAttachAllow;
    VOS_UINT8                           ucSvlteSupportFlg;

    /* 转换为SysCfg结果消息 */
    pstSysCfgMsg        = (NAS_MMCMMC_SysCfg_RSLT_STRU *)pstMsg;

#if (FEATURE_ON == FEATURE_LTE)

    NAS_MMC_ProcSyscfgRsltDisableEnable_OnPlmn(pstSysCfgMsg);
#endif

    /* 处于Deactive 主状态时，不需要搜网 */
    if(NAS_MMC_L1_STA_DEACT == NAS_MMC_GetFsmTopState())
    {
        return VOS_TRUE;
    }


    /* 若SysCfg结果需要搜网，直接迁移到INITIAL状态进行搜网 */
    if ( VOS_TRUE == pstSysCfgMsg->ulNeedPlmnSrch )
    {
        NAS_MMC_ProcSyscfgRsltPlmnSrch_OnPlmn();

        return VOS_TRUE;
    }

    /* 当前卡无效，直接返回，不需要搜网 */
    ulUsimStausFlg = NAS_MML_IsUsimStausValid();
    ulSpecPlmnSearchFlg = NAS_MMC_GetSpecPlmnSearchState();

    if ( ( VOS_FALSE == ulUsimStausFlg )
       && (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING != ulSpecPlmnSearchFlg))
    {
        return VOS_TRUE;
    }

    ucSvlteSupportFlg = NAS_MML_GetSvlteSupportFlag();

    ucCsAttachAllow =  NAS_MML_GetCsAttachAllowFlg();
    ucPsAttachAllow =  NAS_MML_GetPsAttachAllowFlg();
    if((NAS_MMC_L1_STA_ON_PLMN == NAS_MMC_GetFsmTopState())
    && (VOS_FALSE == ucSvlteSupportFlg)
    && (VOS_FALSE == ucCsAttachAllow)
    && (VOS_FALSE == ucPsAttachAllow)
    && (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING != ulSpecPlmnSearchFlg))
    {
        return VOS_TRUE;
    }

    if ( VOS_TRUE == NAS_MMC_RcvSysCfgRslt_TrigSrvStaPlmnSrch_OnPlmn(&pstSysCfgMsg->stPrePrioRatList) )
    {
        return VOS_TRUE;
    }

    /* syscfg设置不需搜网时，需要判断是否需要启动HPLMN定时器 */
    if (VOS_TRUE == NAS_MMC_IsNeedStartHPlmnTimer())
    {
        /* 启动定时器 */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_HPLMN_TIMER, NAS_MMC_GetHplmnTimerLen());

        /* HPLMN TIMER启动事件上报 */
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_HPLMN_TIMER_START,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        /* 将HPLMN启动类型设置为非首次启动 */
        NAS_MMC_SetFirstStartHPlmnTimerFlg(VOS_FALSE);
    }

    if (VOS_TRUE == NAS_MMC_IsNeedStartHighPrioRatHPlmnTimer())
    {
        /* 启动定时器 */
        if (VOS_TRUE == NAS_MMC_StartTimer(TI_NAS_MMC_HIGH_PRIO_RAT_HPLMN_TIMER, NAS_MMC_GetHighPrioRatHplmnTimerLen()))
        {
            NAS_MMC_AddCurHighPrioRatHplmnTimerFirstSearchCount_L1Main();
            NAS_MMC_UpdateHighPrioRatHPlmnTimerTdCount();
        }
    }


    return VOS_TRUE;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_RcvPlmnListReq_L1Main
 功能描述  : L1状态机下收到列表搜网请求
 输入参数  : ulEventType:消息类型
 输出参数  : pstMsg:消息指针
 返 回 值  : VOS_TRUE:消息处理完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年4月1日
   作    者   : zhoujun /40661
   修改内容   : 新生成函数

 2.日    期   : 2011年8月5日
   作    者   : w00176964
   修改内容   : V7R1 PhaseII 调整

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTafPlmnListReq_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 启动LIST搜网状态机 */
    NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_PLMN_LIST);

    return VOS_TRUE;
}

#if (FEATURE_ON == FEATURE_CSG)
/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMsccCsgListSearchReq_L1Main
 功能描述  : L1状态机下收到CSG列表搜网请求
 输入参数  : ulEventType:消息类型
 输出参数  : pstMsg:消息指针
 返 回 值  : VOS_TRUE:消息处理完成
            VOS_FALSE:消息处理未完成
 调用函数  :
 被调函数  :

 修改历史      :
1.日    期   : 2015年9月6日
  作    者   : z00161729
  修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccCsgListSearchReq_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 启动LIST搜网状态机 */
    NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_PLMN_LIST);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiPeriodTryingUserCsgListExpired_L1Main
 功能描述  : 处理TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH消息
 输入参数  : ulEventType - 消息类型
             pstMsg      - 消息
 输出参数  : 无
 返 回 值  : VOS_TRUE:函数处理完成
             VOS_FALSE:函数处理未完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年10月13日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiPeriodTryingUserCsgListExpired_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 启动LIST搜网状态机 */
    NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_PLMN_LIST);

    return VOS_TRUE;
}
#endif

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvPlmnSpecialReq_L1Main
 功能描述  : L1状态机下收到指定搜网请求
 输入参数  : ulEventType:消息类型
              pstMsg:消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE:消息处理完成
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月1日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数

  2.日    期   : 2011年8月5日
    作    者   : w00176964
    修改内容   : V7R1 PhaseII 调整
  3.日    期   : 2011年12月20日
    作    者   : h44270
    修改内容   : 启动搜网状态机时，认为当前无网络

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvPlmnSpecialReq_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 迁移到Initial状态 */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

    /* 启动搜网状态机 */
    NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_PLMN_SELECTION);

    NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,
                             NAS_MML_GetSimPsRegStatus());

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ProcAvailablePlmnListRslt_L1Main
 功能描述  : 收到PLMNListRslt对available定时器的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年11月1日
   作    者   : t00212959
   修改内容   : 新生成函数,NAS_MMC_RcvMmcPlmnListRsltCnf_L1Main降圈复杂度
 2.日    期   : 2012年10月7日
   作    者   : s46746
   修改内容   : for V7R1C50_At_Abort，内部列表搜索过程中，发起用户列表搜索，之后打断用户列表搜索，
                后续没有启动Available定时器再次出发内部列表搜索
 3.日    期   : 2013年12月25日
   作    者   : z00161729
   修改内容   : SVLTE支持NCELL搜网
 4.日    期   : 2015年5月26日
   作    者   : w00167002
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0项目修改
*****************************************************************************/
VOS_VOID  NAS_MMC_ProcAvailablePlmnListRslt_L1Main()
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;
    VOS_UINT32                                              ulPlmnLaType;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                                              ulCsPsMode1NeedPeriodSearchGU;

    ulCsPsMode1NeedPeriodSearchGU = NAS_MMC_IsCsPsMode1NeedPeriodSearchGU();
#endif
    enAdditionalAction            = NAS_MMC_GetPrioAddtionalAction(NAS_MMC_GetCsRegAdditionalAction_L1Main(),
                                                            NAS_MMC_GetPsRegAdditionalAction_L1Main());
    ulPlmnLaType                  = NAS_MMC_GetCurrentLaiForbbidenType();

    /* 当前正常服务时，Available Timer启动次数清零 */
    if ((VOS_TRUE == NAS_MMC_IsNormalServiceStatus())
#if (FEATURE_ON == FEATURE_LTE)
     && (VOS_FALSE == ulCsPsMode1NeedPeriodSearchGU)
#endif
        )
    {
        NAS_MMC_ResetOosPlmnSearchTimerCount_OnPlmn();

        NAS_MMC_StopTimer(TI_NAS_MMC_AVAILABLE_TIMER);

        /* Added by c00318887 for 预置频点搜网优化, 2015-9-1, begin */
        NAS_MMC_StopTimer(TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER);
        /* Added by c00318887 for 预置频点搜网优化, 2015-9-1, end */
    }
    else
    {
        /* 当前非正常服务而且卡有效、驻留小区非禁止小区、非接入受限，需要
           启动Available Timer尝试内部列表搜索 */
        if ( (VOS_TRUE == NAS_MML_IsUsimStausValid())
          && (NAS_MML_PLMN_FORBID_NULL  == ulPlmnLaType)
          && (NAS_MMC_ADDITIONAL_ACTION_ACCESS_BARRED != enAdditionalAction) )
        {
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_AVAILABLE_TIMER, NAS_MMC_GetNextAvailableTimerValue());

            /* 递增 availble timer当前启动的次数或ncell搜网次数 */
            /* 下方函數原本會將count++, 但將count++搬動到 , 所以改函數名稱. 新函數中只处理timer type*/
            NAS_MMC_SetAvailableTimerTypebySearchType_OnPlmn();

            /* Added by c00318887 for 预置频点搜网优化, 2015-9-1, begin */
            (VOS_VOID)NAS_MMC_StartPlmnSearchPhaseOneTotalTimer();
            /* Added by c00318887 for 预置频点搜网优化, 2015-9-1, end */
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetAvailableTimerTypebySearchType_OnPlmn
 功能描述  : 判断递增 availble timer当前启动的次数或ncell搜网次数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月24日
   作    者   : z00161729
   修改内容   : SVLTE支持NCELL搜网
 2.日    期   : 2014年2月7日
   作    者   : z00161729
   修改内容   : DTS2014012305088：支持增强NCELL搜网，如果Modem1传递过来的邻区信息不存在的情况下，通过历史频点支持NCELL搜索
 3.日    期   : 2015年5月25日
   作    者   : s00217060
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0修改
 4.日    期   : 2015年10月30日
   作    者   : h00281185
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0修改
*****************************************************************************/
VOS_VOID  NAS_MMC_SetAvailableTimerTypebySearchType_OnPlmn(VOS_VOID)
{
    if (VOS_TRUE == NAS_MMC_IsNeedStartHistoryTimer())
    {

        NAS_MMC_SetAvailableTimerType_OnPlmn(NAS_MMC_AVAILABLE_TIMER_TYPE_HISTORY);

        return;
    }

    if (VOS_TRUE == NAS_MMC_IsNeedStartPrefBandTimer())
    {

        NAS_MMC_SetAvailableTimerType_OnPlmn(NAS_MMC_AVAILABLE_TIMER_TYPE_PREFBAND);

        return;
    }

    /* 递增 availble timer当前启动的次数或ncell搜网次数 */
    if (VOS_TRUE == NAS_MMC_IsNeedStartNcellAvailableTimer())
    {

        NAS_MMC_SetAvailableTimerType_OnPlmn(NAS_MMC_AVAILABLE_TIMER_TYPE_NCELL);

        return;
    }


    NAS_MMC_SetAvailableTimerType_OnPlmn(NAS_MMC_AVAILABLE_TIMER_TYPE_NORMAL);

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcPlmnListRsltCnf_L1Main
 功能描述  : L1状态机下收到LIST搜网状态机结果的处理
 输入参数  : ulEventType:消息类型
              pstMsg:消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE:消息处理完成
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月14日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2011年10月14日
    作    者   : z00161729
    修改内容   : list搜网结果更新高优先级搜网列表需要更新所有支持的接入技术
  3.日    期   : 2011年11月22日
    作    者   : s46746
    修改内容   : 设置层1的Addition action时应该判断消息中Addition action是否有效，问题单号DTS2011112208047
  4.日    期   : 2011年11月30日
    作    者   : w00176964
    修改内容   : V7R1 Phase IV调整:disable/enable 调整
  5.日    期   : 2012年4月16日
    作    者   : w00166186
    修改内容   : DTS2012041208026,列表搜过程中注册成功，没有启动HPLMN定时器
  6.日    期   : 2012年5月9日
    作    者   : t00212959
    修改内容   : V7R1C50 GUL BG修改，根据结果消息发起搜网
  7.日    期   : 2012年5月24日
    作    者   : z00161729
    修改内容   : V7R1C50 GUL BG修改
  8.日    期   : 2012年6月8日
    作    者   : s46746
    修改内容   : for CS/PS mode 1，列表搜网完成后增加判断LTE是否已经被Disable但未通知接入层
                  对应场景是选网状态机中需要Disable L,但还未挂起LTE时被列表搜网打断
  8.日    期   : 2012年10月7日
    作    者   : s46746
    修改内容   : for V7R1C50_At_Abort，内部列表搜索过程中，发起用户列表搜索，之后打断用户列表搜索，
                  后续没有启动Available定时器再次出发内部列表搜索
  9.日    期   : 2012年11月1日
    作    者   : t00212959
    修改内容   : DTS2012103007750，列表搜索过程中，接入层上报异常的保护
 10.日    期   : 2012年11月30日
    作    者   : w00176964
    修改内容   : DTS2012112911167:在一个小区上反复尝试注册中被RRC LISTrej后错误启动
                 available定时器
                  快速找回TL，所以应尽量让其快速找回。
 11.日    期   : 2014年2月24日
    作    者   : w00176964
    修改内容   : High_Rat_Hplmn_Search特性调整:增加High_Prio_rat_hplmn定时器的启动处理
 12.日    期   : 2013年4月4日
    作    者   : y00176023
    修改内容   : DSDS GUNAS II项目:收到NO RF迁移到OOC状态，启动Available定时器
                 在PLMN LIST时候收到NO RF，则按照FAIL处理，不设置NO RF标志。
 13.日    期   : 2014年5月15日
    作    者   : w00167002
    修改内容   : DTS2014051501018:DSDS副MODEM发起电话，主MODEM搜网失败启动AVAILABLE
                 定时器，用户发起列表搜，在列表搜过程中，周期搜网定时器超时，列表搜
                 结束后，MMC没有启动周期搜网定时器。
                 修改为:在列表搜NO RF后，都启动AVAILABLE定时器，在AVAILABLE定时器
                 超时后，增加如果当前被拒#12则不搜网，当前ACCESS BAR则不搜网。
 14.日    期   : 2014年7月9日
    作    者   : w00176964
    修改内容   : DSDS III调整:收到LIST NO RF的处理
 15.日    期   : 2014年10月27日
    作    者   : b00269685
    修改内容   : 增加High_Prio_rat_hplmn TD Count的处理
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcPlmnListRsltCnf_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMCMMC_PLMN_LIST_RSLT_STRU                         *pstListRslt    = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList = VOS_NULL_PTR;
    VOS_UINT32                                              i;

    NAS_MMC_AS_CELL_CAMP_ON_ENUM_UINT8                      enAsCellCampOn;     /* 接入层是否Camp On */

    pstListRslt    = (NAS_MMCMMC_PLMN_LIST_RSLT_STRU*)pstMsg;
    pstPrioRatList = NAS_MML_GetMsPrioRatList();

    enAsCellCampOn = NAS_MMC_GetAsCellCampOn();

    /* list搜网结果为NO RF FAIL的且非驻留态的处理,进入OOC状态 */
    if  ((NAS_MMC_AS_CELL_NOT_CAMP_ON  == enAsCellCampOn)
      && (NAS_MMC_PLMN_LIST_NO_RF_FAIL == pstListRslt->enRslt))
    {
        /* 处理丢网状态，上报服务状态，迁移到ooc，启动available定时器 */
        /* Modified by c00318887 for 预置频点搜网优化, 2015-9-10, begin */
        NAS_MMC_ProcCoverageLost_L1Main(NAS_MMC_PLMN_SEARCH_SCENE_BUTT);
        /* Modified by c00318887 for 预置频点搜网优化, 2015-9-10, end */

        return VOS_TRUE;
    }

    for (i = 0; i < pstPrioRatList->ucRatNum; i++)
    {
       /* 更新高优先级列表 */
       NAS_MMC_UpdatePlmnListInPlmnSelectionList(&(pstListRslt->astPlmnSearchInfo[i]),
                                                   NAS_MMC_GetHighPrioPlmnList(),
                                                   VOS_FALSE,
                                                   VOS_TRUE);

       /* 可维可测,将选网列表输出 */
       NAS_MMC_LogPlmnSelectionList(NAS_MMC_GetHighPrioPlmnList());
    }

    /* 根据返回的addition值对当前的addition进行更新 */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != pstListRslt->enCsRegAdditionalAction)
    {
        NAS_MMC_SetCsRegAdditionalAction_L1Main(pstListRslt->enCsRegAdditionalAction);
    }

    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != pstListRslt->enPsRegAdditionalAction)
    {
        NAS_MMC_SetPsRegAdditionalAction_L1Main(pstListRslt->enPsRegAdditionalAction);
    }

    if (VOS_TRUE == NAS_MMC_ProcPlmnListTriggerPlmnSearch_L1Main(pstListRslt))
    {
        return VOS_TRUE;
    }

    /* 接入层上报错误时的保护，列表搜打断指定搜时，防止接入层按指定搜流程上报*/
    if ( NAS_MMC_SPEC_PLMN_SEARCH_STOP == NAS_MMC_GetSpecPlmnSearchState())
    {
        NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_ON_PLMN);
    }



    /* 如果搜网注册成功，需要判断是否需要启动HPLMN定时器,增加在驻留态起背景搜定时器 */
    if ( (VOS_TRUE                  == NAS_MMC_IsNeedStartHPlmnTimer())
      && (NAS_MMC_AS_CELL_CAMP_ON   == enAsCellCampOn) )
    {
        /* 启动定时器 */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_HPLMN_TIMER, NAS_MMC_GetHplmnTimerLen());

        /* HPLMN TIMER启动事件上报 */
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_HPLMN_TIMER_START,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        /* 将HPLMN启动类型设置为非首次启动 */
        NAS_MMC_SetFirstStartHPlmnTimerFlg(VOS_FALSE);
    }

    if (VOS_TRUE == NAS_MMC_IsNeedStartHighPrioRatHPlmnTimer())
    {
        /* 启动定时器 */
        if (VOS_TRUE == NAS_MMC_StartTimer(TI_NAS_MMC_HIGH_PRIO_RAT_HPLMN_TIMER, NAS_MMC_GetHighPrioRatHplmnTimerLen()))
        {
            NAS_MMC_AddCurHighPrioRatHplmnTimerFirstSearchCount_L1Main();
            NAS_MMC_UpdateHighPrioRatHPlmnTimerTdCount();
        }
    }

    /* 只有打断退出状态机时才需要判断是否有available 定时器的停止以及内部LIST搜网触发 */
    if (NAS_MMC_PLMN_LIST_ABORTED == pstListRslt->enRslt)
    {
        /* 函数提取降圈复杂度 */
        NAS_MMC_ProcAvailablePlmnListRslt_L1Main();
    }

    if ( NAS_MMC_PLMN_LIST_NO_RF_FAIL == pstListRslt->enRslt )
    {
        /* 判断LIST搜网失败NO RF后，判断是否需要启动AVAILABLE定时器 */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_AVAILABLE_TIMER, NAS_MMC_GetNextAvailableTimerValue());
    }

    return VOS_TRUE;
}

#if (FEATURE_ON == FEATURE_DSDS)
/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMsccSrvAcqReq_L1Main
 功能描述  : 收到MSCC的ID_MSCC_MMC_SRV_ACQ_REQ启动搜网状态机
 输入参数  : ulEventType:消息类型
           : pstMsg:消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE:消息处理完成
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月23日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccSrvAcqReq_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMC_SRV_ACQ_REQ_STRU           *pstSrvAcqReq = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU          stAnycellSrchRatList;

    pstSrvAcqReq = (MSCC_MMC_SRV_ACQ_REQ_STRU*)pstMsg;

    /* 不在on plmn时搜到紧急呼叫，发起anycell搜网 */
    if (NAS_MSCC_PIF_SRV_TYPE_CS_MO_EMERGENCY_CALL == pstSrvAcqReq->enSrvType)
    {
        NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

        pstPrioRatList = NAS_MML_GetMsPrioRatList();
        NAS_MMC_BuildCoverageRatPrioListEmgCall_L1Main(pstPrioRatList, &stAnycellSrchRatList);

        NAS_MMC_SndInterAnyCellSearchReq(&stAnycellSrchRatList, NAS_MMC_ANYCELL_SEARCH_SCENE_SRV_TRIG_PLMN_SEARCH);

        /*停止Available定时器*/
        NAS_MMC_StopTimer(TI_NAS_MMC_AVAILABLE_TIMER);
        return VOS_TRUE;
    }

    NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

    NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_SRV_TRIG_PLMN_SEARCH, VOS_NULL_PTR, 0);

    /*停止Available定时器*/
    NAS_MMC_StopTimer(TI_NAS_MMC_AVAILABLE_TIMER);

    return VOS_TRUE;
}


#endif

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMsccPlmnSrchReq_L1Main
 功能描述  : 开机后进入INITIAL后收到TAF的搜网请求启动搜网状态机
 输入参数  : ulEventType:消息类型
            : pstMsg:消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE:
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月1日
    作    者   : luokaihui / 00167671
    修改内容   : 新生成函数
  2.日    期   : 2011年12月20日
    作    者   : h44270
    修改内容   : 启动搜网状态机时，认为当前无网络
  3.日    期   : 2015年6月9日
    作    者   : w00176964
    修改内容   : DTS2015052903319
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccPlmnSrchReq_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 卡无效，启动ANY CELL状态机 */
    if ( VOS_FALSE == NAS_MML_IsUsimStausValid())
    {
        NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_ANYCELL_SEARCH);
    }
    else
    {
        NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_PLMN_SELECTION);
    }

    NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,
                             NAS_MML_GetSimPsRegStatus());

    return VOS_TRUE;
}

/* Added by s00246516 for L-C互操作项目, 2014-01-27, Begin */
/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMsccAcqReq_L1Main
 功能描述  : 收到MSCC的获取搜网请求启动搜网状态机
 输入参数  : ulEventType:消息类型
           : pstMsg:消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE:
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月27日
    作    者   : s00246516
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccAcqReq_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_PLMN_ID_STRU               *pstPlmnId = VOS_NULL_PTR;
    VOS_UINT32                          ulArfcn;

    /* 正常服务回复获取成功 */
    if (VOS_TRUE == NAS_MMC_IsNormalServiceStatus())
    {
        pstPlmnId = NAS_MML_GetCurrCampPlmnId();
        ulArfcn   = NAS_MML_GetCurrCampArfcn();

        /* 回复获取成功 */
        NAS_MMC_SndMsccAcqCnf(NAS_MSCC_PIF_ACQ_RESULT_SUCCESS, pstPlmnId, ulArfcn);

        return VOS_TRUE;
    }

    /* 状态迁移到initial */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

    /* 启动选网状态机进行网络获取 */
    NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_PLMN_SELECTION);


    NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,
                             NAS_MML_GetSimPsRegStatus());

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMsccRegReq_L1Main
 功能描述  : 收到MSCC的注册网络请求启动搜网状态机
 输入参数  : ulEventType:消息类型
           : pstMsg:消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE:
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月27日
    作    者   : s00246516
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccRegReq_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32         enPlmnSearchScene;
    VOS_UINT32                                    ulArfcn;
    MSCC_MMC_REG_REQ_STRU                         *pstRegReq             = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                         *pstPlmnId             = VOS_NULL_PTR;

    pstRegReq = (MSCC_MMC_REG_REQ_STRU*)pstMsg;

    /* 当前如果已经在注册成功并且注册网络满足REG请求消息中的要求，则不需要发起搜网 */
    if (VOS_FALSE == NAS_MMC_IsRegReqTriggerPlmnSrch_L1Main(pstRegReq))
    {
        pstPlmnId = NAS_MML_GetCurrCampPlmnId();
        ulArfcn   = NAS_MML_GetCurrCampArfcn();
        NAS_MMC_SndMsccRegCnf(MMC_LMM_CL_REG_STATUS_BUTT, NAS_MSCC_PIF_REG_RESULT_SUCCESS, pstPlmnId, ulArfcn);
        return VOS_TRUE;
    }

    /* 保存NCELL信息 */
    if (VOS_TRUE == pstRegReq->bitOpCellInfo)
    {
        NAS_MMC_SaveRegReqNCellInfo(&(pstRegReq->stCellInfo));
    }

    enPlmnSearchScene = NAS_MMC_GetPlmnSearchSceneMsccRegReq(pstRegReq);

    /* 启动选网状态机进行网络获取和注册 */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

    NAS_MMC_SndInterPlmnSearchReq(enPlmnSearchScene, VOS_NULL_PTR, 0);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMsccPowerSaveReq_L1Main
 功能描述  : 收到MSCC的Power Save请求启动搜网状态机
 输入参数  : ulEventType:消息类型
           : pstMsg:消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE:
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月27日
    作    者   : s00246516
    修改内容   : 新生成函数
  2.日    期   : 2015年4月7日
    作    者   : l00324781
    修改内容   : Mmc Power Save后，不再进入OOC状态，而是进入Deactive状态
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccPowerSaveReq_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 如果当前接入技术为BUTT，表示已经是PowerSave，直接回复 */
    if (NAS_MML_NET_RAT_TYPE_BUTT == NAS_MML_GetCurrNetRatType())
    {
        /* 状态迁移到OOC状态，并且停止定时器 */

        /* MMC Recived Power Save, The fsm do not transport OOC, transport deactive state */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_DEACT);

        NAS_MMC_StopAllTimer();

        OM_SetDrxTimerWakeSrc(VOS_GetModemIDFromPid(WUEPS_PID_MMC));
        NAS_MMC_SndDrxTimerInfo(VOS_TRUE);

        /* 回复成功 */
        NAS_MMC_SndMsccPowerSaveCnf(NAS_MSCC_PIF_POWER_SAVE_SUCCESS);

        return VOS_TRUE;
    }


    /* 扩展Power Off状态机进行挂起操作 */
    NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_POWER_OFF);

    NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,
                             NAS_MML_GetSimPsRegStatus());

    return VOS_TRUE;
}
/* Added by s00246516 for L-C互操作项目, 2014-01-27, End */



/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMsccGetGeoReq_L1Main
 功能描述  : 收到MSCC的GET GEO请求启动获取地理信息状态机
 输入参数  : ulEventType:消息类型
           : pstMsg:消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE:
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月27日
    作    者   : w0167002
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccGetGeoReq_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 启动GET GEO流程 */
    NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_GET_GEO);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvInterPlmnSrchReq_L1Main
 功能描述  : INITIAL时收到内部的搜网请求启动搜网状态机
 输入参数  : ulEventType:消息类型
 输出参数  : pstMsg:消息指针
 返 回 值  : VOS_TRUE:
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月1日
    作    者   : luokaihui / 00167671
    修改内容   : 新生成函数
  2.日    期   : 2011年12月20日
    作    者   : h44270
    修改内容   : 启动搜网状态机时，认为当前无网络

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvInterPlmnSrchReq_Initial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 卡无效，启动ANY CELL状态机 */
    if ( VOS_FALSE == NAS_MML_IsUsimStausValid())
    {
        NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_ANYCELL_SEARCH);
    }
    else
    {
        NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_PLMN_SELECTION);
    }

    NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,
                             NAS_MML_GetSimPsRegStatus());

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvInterAnyCellSrchReq_Initial
 功能描述  : INITIAL时收到内部的ANYCELL搜网请求启动搜网状态机
 输入参数  : ulEventType:消息类型
 输出参数  : pstMsg:消息指针
 返 回 值  : VOS_TRUE:
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年8月5日
    作    者   : w00176964
    修改内容   : 新生成函数

  2.日    期   : 2011年11月25日
    作    者   : w00166186
    修改内容   : DTS2011112308343,G下pdp激活后，丢网后到W注册PS成功，CS13拒绝，PS链路不释放
                 后续释放后，没有搜网。

  3.日    期   : 2011年12月1日
    作    者   : w00167002
    修改内容   : DTS2011112308343: 在问题单DTS2011112308343中的修改放到收到选网状态机
                 的结果中进行处理。若注册失败，且当前有紧急呼叫业务，则启动
                 周期搜网定时器。
  4.日    期   : 2012年6月6日
    作    者   : l00130025
    修改内容   : DTS2012060702423:Anycell驻留后，注册成功时，没有通知通知CDS消息，无法数传
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvInterAnyCellSrchReq_Initial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_ANYCELL_SEARCH);


    NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,
                             NAS_MML_GetSimPsRegStatus());


    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAnycellSearchRslt_Initial
 功能描述  : INITIAL时收到内部的Anycell搜网状态机结果处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE:
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月19日
   作    者   : l00130025
   修改内容   : 新生成函数

 2.日    期   : 2011年12月02日
   作    者   : w00167002
   修改内容   : DTS2011112804719:在ANYCELL等系统消息时候收到ABORT消息，若当期已经
                是驻留态，则迁移到 ON PLMN状态。
 3.日    期   : 2012年6月6日
   作    者   : l00130025
   修改内容   : DTS2012060702423:Anycell驻留后，注册成功时，没有通知通知CDS消息，无法数传
 4.日    期   : 2012年6月25日
   作    者   : W00176964
   修改内容   : DTS2012062501067:Anycell驻留后启动available定时器未递增启动次数
 5.日    期   : 2012年10月23日
   作    者   : w00176964
   修改内容   : DTS2012101205055:驻留G数传态下长时间丢网,搜索过程中再次搜索L网络
                失败丢网后,NAS导致小区恢复后数传不恢复
 6.日    期   : 2012年10月29日
   作    者   : w00176964
   修改内容   : DTS201201003747:anycell搜网状态机对于anycell搜网状态机的打断结果应该是
                anycell_srch_abort
 7.日    期   : 2012年11月7日
   作    者   : l00167671
   修改内容   : DTS2012110607212: availble定时器定时器启动成功,才能进行定时器计数
 8.日    期   : 2012年11月10日
   作    者   : s00217060
   修改内容   : DTS2012102902559: SIM卡并且是LTE only时,不启动Available定时器,其他情况下有卡启动Available定时器
 9.日    期   : 2012年12月31日
   作    者   : s00217060
   修改内容   : for DSDA GUNAS C CORE,G单模，USIM禁止GSM接入时，不启动Available定时器,
                 和其他一些是否需要启Available定时器的判断封装成函数
 10.日    期   : 2013年12月24日
    作    者   : z00161729
    修改内容   : SVLTE支持NCELL搜网
 11.日    期   : 2014年4月24日
    作    者   : w00242748
    修改内容   : DTS2014042405819:无卡状态下，紧急呼被拒#5，后发起ANYCELL搜，导致退状态机
                 后下发RRMM_UE_OOC_STATUS_NOTIFY_IND，导致网络不断下发CM SERVICE REJ
 12.日    期   : 2014年10月13日
    作    者   : w00167002
    修改内容   : DTS2014102005694:G下，CS注册成功后，PS还未注册成功时候，则
               发起电话业务，在电话业务建联时候丢网，MM没有释放信令，MMC没有发起ANY
               CELL搜网。
               在发起ANYCELL时候，MM的信令链接还存在，直接REJ了，跟闻晓确认此处内部保护
               场景是代码走读额外加上去得，没有明确问题场景,先作回退处理。
13.日    期   : 2014年11月4日
   作    者   : w00167002
   修改内容   : DTS2014103102839:L下拨打电话HO到W失败回退到L，则尝试搜网发起紧急呼
                ，ANYCELL挂起L到GU下搜网，当前L下支持链接态发起挂起操作。
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcAnycellSearchRslt_Initial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMCMMC_ANYCELL_SEARCH_RSLT_STRU      *pstAnycellRslt;

    pstAnycellRslt = (NAS_MMCMMC_ANYCELL_SEARCH_RSLT_STRU *)pstMsg;

    if (NAS_MMC_ANYCELL_SEARCH_REJECT == pstAnycellRslt->enResult)
    {
        NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_ON_PLMN);


        if ( VOS_TRUE == NAS_MMC_StartTimer(TI_NAS_MMC_AVAILABLE_TIMER, NAS_MMC_GetNextAvailableTimerValue()) )
        {
            /* 递增 availble timer当前启动的次数或ncell搜网次数 */
            NAS_MMC_SetAvailableTimerTypebySearchType_OnPlmn();

            /* Added by c00318887 for 预置频点搜网优化, 2015-9-1, begin */
            (VOS_VOID)NAS_MMC_StartPlmnSearchPhaseOneTotalTimer();
            /* Added by c00318887 for 预置频点搜网优化, 2015-9-1, end */
        }

        return VOS_TRUE;
    }

    /* 触发搜网后就清除additional的值 */
    NAS_MMC_ClearAllRegAdditionalAction_L1Main();

    /* 搜网成功,迁移到ON PLMN */
    if (NAS_MMC_ANYCELL_SEARCH_SUCC == pstAnycellRslt->enResult)
    {
        NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_ON_PLMN);

        /* 需要启动Available定时器 */
        if ( VOS_TRUE == NAS_MMC_IsAnycellSrchSuccStartAvailableTimer_Initial())
        {
            if ( VOS_TRUE == NAS_MMC_StartTimer(TI_NAS_MMC_AVAILABLE_TIMER, NAS_MMC_GetNextAvailableTimerValue()) )
            {
                /* 递增 availble timer当前启动的次数或ncell搜网次数 */
                NAS_MMC_SetAvailableTimerTypebySearchType_OnPlmn();

                /* Added by c00318887 for 预置频点搜网优化, 2015-9-1, begin */
                (VOS_VOID)NAS_MMC_StartPlmnSearchPhaseOneTotalTimer();
                /* Added by c00318887 for 预置频点搜网优化, 2015-9-1, end */

            }
        }

        /* 不需要启动available 定时器的情况和只启动一次的情况,更新注册状态 */
        NAS_MMC_UpdateRegStateAnyCellSearchSucc();

    }
    else if (NAS_MMC_ANYCELL_SEARCH_FAIL == pstAnycellRslt->enResult)
    {
        /* 处理丢网 */
        /* Modified by c00318887 for 预置频点搜网优化, 2015-9-10, begin */
        NAS_MMC_ProcCoverageLost_L1Main(NAS_MMC_PLMN_SEARCH_SCENE_BUTT);
        /* Modified by c00318887 for 预置频点搜网优化, 2015-9-10, end */
    }
    else if (NAS_MMC_ANYCELL_SEARCH_ABORTED == pstAnycellRslt->enResult)
    {

        /* 若在驻留态则迁移到ON PLMN状态 */
        if ( NAS_MMC_AS_CELL_CAMP_ON == NAS_MMC_GetAsCellCampOn() )
        {
            NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_ON_PLMN);
        }

    }
    else
    {
        /* 异常打印 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMmcAnycellSearchRslt_Initial:ENTERED");
    }

    /* 只有在驻留态才通知APS当前的接入技术,非驻留态下PDP已经激活情况下
       通知APS当前接入技术为W/L时,APS主动去激活SNDCP，后续回到G下无法恢复
       数传 */
    if (NAS_MMC_SPEC_PLMN_SEARCH_STOP == NAS_MMC_GetSpecPlmnSearchState())
    {
        NAS_MMC_NotifyModeChange(NAS_MML_GetCurrNetRatType(),
                                 NAS_MML_GetSimPsRegStatus());

    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcGetGeoRslt_Initial
 功能描述  : 收到GET_GEO结果的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月23日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2015年10月9日
    作    者   : s00217060
    修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0修改

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmcGetGeoRslt_Initial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMCMMC_GET_GEO_RSLT_STRU       *pstGetGeoRslt   = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU          stPlmnIdWithRat;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatList = VOS_NULL_PTR;

    pstGetGeoRslt   = (NAS_MMCMMC_GET_GEO_RSLT_STRU *)pstMsg;
    pstRatList      = NAS_MML_GetMsPrioRatList();

    PS_MEM_SET(&stPlmnIdWithRat, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    if (NAS_MMC_GET_GEO_SUCCESS == pstGetGeoRslt->enGetGeoRslt)
    {
        stPlmnIdWithRat.stPlmnId.ulMcc  = pstGetGeoRslt->stGetGeoPlmn.ulMcc;
        stPlmnIdWithRat.stPlmnId.ulMnc  = pstGetGeoRslt->stGetGeoPlmn.ulMnc;

        /* 通知CSS当前MCC */
        NAS_MMC_SndCssCurrGeoInd(VOS_FALSE, 1, &(pstGetGeoRslt->stGetGeoPlmn));
    }
    else
    {
        stPlmnIdWithRat.stPlmnId.ulMcc  = NAS_MML_INVALID_MCC;
        stPlmnIdWithRat.stPlmnId.ulMnc  = NAS_MML_INVALID_MNC;
    }

    stPlmnIdWithRat.enRat = pstRatList->aucRatPrio[0];

    NAS_MMC_SetGeoPlmn(&stPlmnIdWithRat);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedStartAvailableTimer_PlmnSelectionRsltSucc
 功能描述  : 搜网结果为成功时判断是否需要启动available定时器
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:需要启动
             VOS_FALSE:不需要启动
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期   : 2013年11月26日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2014年01月17日
    作    者   : l00198894
    修改内容   : V9R1C53 C+L 离网重选项目

*****************************************************************************/
VOS_UINT8 NAS_MMC_IsNeedStartAvailableTimer_PlmnSelectionRsltSucc(VOS_VOID)
{
    VOS_UINT8                           ucCsAttachAllowFlg;
    VOS_UINT8                           ucPsAttachAllowFlg;
    VOS_UINT32                          ulIsUsimStatusValid;
    VOS_UINT8                           ucSvlteSupportFlg;
    VOS_UINT8                           ucLcEnableFlg;

    ucCsAttachAllowFlg  = NAS_MML_GetCsAttachAllowFlg();
    ucPsAttachAllowFlg  = NAS_MML_GetPsAttachAllowFlg();
    ulIsUsimStatusValid = NAS_MML_IsUsimStausValid();
    ucSvlteSupportFlg   = NAS_MML_GetSvlteSupportFlag();
    ucLcEnableFlg       = NAS_MML_GetLcEnableFlg();

    /* SVLTE或C+L形态时，国内模式(PS Only)需要启动Avaliable定时器 */
    if ( (NAS_MML_MS_MODE_PS_ONLY == NAS_MML_GetMsMode())
      && (VOS_FALSE == ucCsAttachAllowFlg)
      && (VOS_FALSE == ucPsAttachAllowFlg)
      && (VOS_TRUE == ulIsUsimStatusValid)
      && ((VOS_TRUE == ucSvlteSupportFlg)
       || (VOS_TRUE == ucLcEnableFlg)))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/* Added by s00246516 for L-C互操作项目, 2014-01-27, Begin */
/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcPlmnSelectionRsltSucc_Initial
 功能描述  : INITIAL时收到内部的选网状态机结果为成功的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无:
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年2月20日
   作    者   : s00246516
   修改内容   : 新生成函数
 2.日    期   : 2014年10月27日
   作    者   : b00269685
   修改内容   : 增加High_Prio_rat_hplmn TD Count的处理
 3.日    期   : 2015年4月17日
   作    者   : w00176964
   修改内容   : CDMA 1X Iteration 10 Modified:add lte coverage flg and notify mscc
 4.日    期   : 2015年5月25日
   作    者   : s00217060
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0新增

*****************************************************************************/
VOS_VOID NAS_MMC_RcvMmcPlmnSelectionRsltSucc_Initial(
    VOS_UINT8                           ucLteCoverFlg
)
{
    NAS_MML_BG_SEARCH_CFG_INFO_STRU    *pstBgSearchCfg       = VOS_NULL_PTR;

    NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_ON_PLMN);

    pstBgSearchCfg       = NAS_MML_GetBgSearchCfg();

    /* 如果搜网注册成功，需要判断是否需要启动HPLMN定时器 */
    if (VOS_TRUE == NAS_MMC_IsNeedStartHPlmnTimer())
    {
        /* 启动定时器 */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_HPLMN_TIMER, NAS_MMC_GetHplmnTimerLen());


        /* HPLMN TIMER启动事件上报 */
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_HPLMN_TIMER_START,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);


        /* 将HPLMN启动类型设置为非首次启动 */
        NAS_MMC_SetFirstStartHPlmnTimerFlg(VOS_FALSE);
    }
    else
    {
        /* 法电定制，增强的Hplmn搜网特性打开时，开机不需要启动
           HPLMN定时器,后续再启动时,认为不是首次启动HPLMN定时器 */
        if (VOS_TRUE == pstBgSearchCfg->ucEnhancedHplmnSrchFlg)
        {
            NAS_MMC_SetFirstStartHPlmnTimerFlg(VOS_FALSE);
        }
    }

    if (VOS_TRUE == NAS_MMC_IsNeedStartHighPrioRatHPlmnTimer())
    {
        /* 启动定时器 */
        if (VOS_TRUE == NAS_MMC_StartTimer(TI_NAS_MMC_HIGH_PRIO_RAT_HPLMN_TIMER, NAS_MMC_GetHighPrioRatHplmnTimerLen()))
        {
            NAS_MMC_AddCurHighPrioRatHplmnTimerFirstSearchCount_L1Main();
            NAS_MMC_UpdateHighPrioRatHPlmnTimerTdCount();
        }
    }
    /* 当前正常服务时，Available Timer启动次数清零 */
    if (VOS_TRUE == NAS_MMC_IsNormalServiceStatus())
    {
        NAS_MMC_ResetOosPlmnSearchTimerCount_OnPlmn();

        NAS_MMC_StopTimer(TI_NAS_MMC_AVAILABLE_TIMER);

        /* Added by c00318887 for 预置频点搜网优化, 2015-9-1, begin */
        NAS_MMC_StopTimer(TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER);
        /* Added by c00318887 for 预置频点搜网优化, 2015-9-1, end */

        /* 根据不同的返回结果，向MSCC上报本次指定搜网的结果，触发RaomingBroker上报 */
        NAS_MMC_SndMsccPlmnSelectionRsltInd(NAS_MSCC_PIF_PLMN_SELECTION_RESULT_NORMAL_SERVICE, ucLteCoverFlg);
    }
    else
    {
        /* 根据不同的返回结果，向MSCC上报本次指定搜网的结果，触发RaomingBroker上报 */
        NAS_MMC_SndMsccPlmnSelectionRsltInd(NAS_MSCC_PIF_PLMN_SELECTION_RESULT_LIMITED_SERVICE, ucLteCoverFlg);

        if (VOS_TRUE == NAS_MMC_IsNeedStartAvailableTimer_PlmnSelectionRsltSucc())
        {
            if ( VOS_TRUE == NAS_MMC_StartTimer(TI_NAS_MMC_AVAILABLE_TIMER, NAS_MMC_GetNextAvailableTimerValue()) )
            {
                /* 递增 availble timer当前启动的次数或ncell搜网次数 */
                NAS_MMC_SetAvailableTimerTypebySearchType_OnPlmn();

                /* Added by c00318887 for 预置频点搜网优化, 2015-9-1, begin */
                (VOS_VOID)NAS_MMC_StartPlmnSearchPhaseOneTotalTimer();
                /* Added by c00318887 for 预置频点搜网优化, 2015-9-1, end */
            }
        }
    }
}
/* Added by s00246516 for L-C互操作项目, 2014-01-27, End */

/* Modified by c00318887 for 预置频点搜网优化, 2015-9-9, begin */
/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcPlmnSelectionRsltFail_Initial
 功能描述  : INITIAL时收到内部的选网状态机结果为失败的处理
 输入参数  : pstPlmnSelectionRslt   --搜网结果
             ucLteCoverFlg          --LTE 覆盖标记
 输出参数  : 无
 返 回 值  : 无:
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年9月11日
   作    者   : c00318887
   修改内容   : 预置频点搜网优化提炼成函数

*****************************************************************************/
VOS_VOID NAS_MMC_RcvMmcPlmnSelectionRsltFail_Initial(
    NAS_MMCMMC_PLMN_SELECTION_RSLT_STRU                    *pstPlmnSelectionRslt,
    VOS_UINT8                                               ucLteCoverFlg
)
{
    NAS_MML_CONN_STATUS_INFO_STRU                          *pstConnStatus        = VOS_NULL_PTR;

    pstConnStatus           = NAS_MML_GetConnStatus();

    /* CS域有当前有紧急呼叫业务存在 */
    if ( (VOS_TRUE == NAS_MML_GetCsEmergencyServiceFlg())
      && ((VOS_TRUE == pstConnStatus->ucCsServiceConnStatusFlg)) )
    {
        /* 如果卡有效启动Available定时器 */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_ON_PLMN);

        if ( VOS_TRUE == NAS_MMC_StartTimer(TI_NAS_MMC_AVAILABLE_TIMER, NAS_MMC_GetNextAvailableTimerValue()) )
        {
            /* 递增 availble timer当前启动的次数或ncell搜网次数 */
            NAS_MMC_SetAvailableTimerTypebySearchType_OnPlmn();

            /* Added by c00318887 for 预置频点搜网优化, 2015-9-1, begin */
            (VOS_VOID)NAS_MMC_StartPlmnSearchPhaseOneTotalTimer();
            /* Added by c00318887 for 预置频点搜网优化, 2015-9-1, end */

        }

        /* 根据不同的返回结果，向MSCC上报本次指定搜网的结果，触发RaomingBroker上报 */
        NAS_MMC_SndMsccPlmnSelectionRsltInd(NAS_MSCC_PIF_PLMN_SELECTION_RESULT_LIMITED_SERVICE, ucLteCoverFlg);

        /* 只有在驻留态才通知APS当前的接入技术,非驻留态下PDP已经激活情况下
           通知APS当前接入技术为W/L时,APS主动去激活SNDCP，后续回到G下无法恢复
           数传 */
        if (NAS_MMC_SPEC_PLMN_SEARCH_STOP == NAS_MMC_GetSpecPlmnSearchState())
        {
            NAS_MMC_NotifyModeChange(NAS_MML_GetCurrNetRatType(),
                                     NAS_MML_GetSimPsRegStatus());
        }

        return;
    }

    /* 如果当前存在NO RF，则迁移到OOC状态 */
    if (VOS_FALSE == NAS_MML_GetRfAvailFlg())
    {
        NAS_MMC_SndMsccPlmnSelectionRsltInd(NAS_MSCC_PIF_PLMN_SELECTION_RESULT_NO_RF, ucLteCoverFlg);

        /* 处理丢网状态，上报服务状态，迁移到ooc，启动available定时器 */
        /* Modified by c00318887 for 预置频点搜网优化, 2015-9-10, begin */
        NAS_MMC_ProcCoverageLost_L1Main(NAS_MMC_PLMN_SEARCH_SCENE_BUTT);
        /* Modified by c00318887 for 预置频点搜网优化, 2015-9-10, end */


        return;
    }

    /* 无任何网络覆盖 */
    if (0 == pstPlmnSelectionRslt->ulRatNum)
    {
        /* 处理丢网 */
        /* Modified by c00318887 for 预置频点搜网优化, 2015-9-10, begin */
        NAS_MMC_ProcCoverageLost_L1Main(pstPlmnSelectionRslt->ulPlmnSearchScene);
        /* Modified by c00318887 for 预置频点搜网优化, 2015-9-10, end */

        /* 根据不同的返回结果，向MSCC上报本次指定搜网的结果，触发RaomingBroker上报 */
        NAS_MMC_SndMsccPlmnSelectionRsltInd(NAS_MSCC_PIF_PLMN_SELECTION_RESULT_NO_SERVICE, ucLteCoverFlg);

    }
    else
    {
        /* 有网络覆盖的处理 */
        NAS_MMC_ProcOutOfService_L1Main(pstPlmnSelectionRslt);

        /* 根据不同的返回结果，向MSCC上报本次指定搜网的结果，触发RaomingBroker上报 */
        NAS_MMC_SndMsccPlmnSelectionRsltInd(NAS_MSCC_PIF_PLMN_SELECTION_RESULT_LIMITED_SERVICE, ucLteCoverFlg);
    }

    /* Added by c00318887 for 预置频点搜网优化, 2015-9-10, begin */
    return;
    /* Added by c00318887 for 预置频点搜网优化, 2015-9-10, end */

}

/* Modified by c00318887 for 预置频点搜网优化, 2015-9-9, end */

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcPlmnSelectionRslt_Initial
 功能描述  : INITIAL时收到内部的选网状态机结果处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE:
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月15日
   作    者   : s46746
   修改内容   : 新生成函数

 2.日    期   : 2011年9月23日
   作    者   : z00161729
   修改内容   : V7R1 Phase II 高优先级搜网调整

 3.日    期   : 2011年10月22日
   作    者   : w00167002
   修改内容   : V7R1 Phase II-2 增加HPLMN TIMER的事件上报

 4.日    期   : 2011年12月1日
   作    者   : w00167002
   修改内容   : DTS2011112308343: 若选网状态机回复结果为失败，若当前有紧急
                 呼叫业务，则启动周期搜网定时器。
 5.日    期   : 2011年12月20日
   作    者   : h44270
   修改内容   : 退出Plmen selection状态机，结果为成功时，发送当前的网络类型

 6.日    期   : 2011年11月30日
   作    者   : w00176964
   修改内容   : V7R1 Phase IV调整:disable/enable 调整

 7.日    期   : 2012年9月20日
   作    者   : z40661
   修改内容   : DTS2012082006273,未通知L模disable时,可用将L模的网络放在最后

 8.日    期   : 2012年10月23日
   作    者   : w00176964
   修改内容   : DTS2012101205055:驻留G数传态下长时间丢网,搜索过程中再次搜索L网络
                失败丢网后,NAS导致小区恢复后数传不恢复
 9.日    期   : 2012年11月7日
   作    者   : l00167671
   修改内容   : DTS2012110607212: availble定时器定时器启动成功,才能进行定时器计数
10.日    期   : 2013年3月30日
   作    者   : l00167671
   修改内容   : 主动上报AT命令控制下移至C核
11.日    期   : 2013年05月08日
   作    者   : s46746
   修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
12.日    期   : 2013年11月23日
   作    者   : z00161729
   修改内容   : SVLTE优化G-TL ps切换性能修改
13.日    期   : 2013年12月24日
   作    者   : z00161729
   修改内容   : SVLTE支持NCELL搜网
                快速找回TL，所以应尽量让其快速找回。
14.日    期   : 2014年2月24日
   作    者   : w00176964
   修改内容   : High_Rat_Hplmn_Search特性调整:增加High_Prio_rat_hplmn定时器的启动处理
15.日    期   : 2014年3月7日
   作    者   : f00261443
   修改内容   : DTS2014022703617:搜网失败时判断是否是由于No Rf导致，如果是No Rf上报 搜网被打断而不是搜网失败
16.日    期   : 2013年4月8日
   作    者   : y00176023
   修改内容   : DSDS GUNAS II项目:如果是NO RF迁移到OOC
17.日    期   : 2014年1月27日
   作    者   : s00246516
   修改内容   : L-C互操作项目:增加异系统到HRPD的处理
18.日    期   : 2014年4月14日
   作    者   : s00261364
   修改内容   : V3R360_eCall项目:搜网时更新服务状态
19.日    期   : 2015年4月17日
   作    者   : w00176964
   修改内容   : CDMA 1X Iteration 10 Modified:add lte coverage flg and notify mscc
20.日    期   : 2015年5月30日
   作    者   : l00324781
   修改内容   : CDMA 1X Iteration 12: plmn搜网返回结果类型是hrpd，mmc当前状态设为DEACT
21.日    期   : 2015年08月25日
   作    者   : m00312079
   修改内容   : DTS2015082004682:新增搜网结果原因值NAS_MSCC_PIF_PLMN_SELECTION_RESULT_L2C
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcPlmnSelectionRslt_Initial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMCMMC_PLMN_SELECTION_RSLT_STRU                    *pstPlmnSelectionRslt = VOS_NULL_PTR;

    VOS_UINT8                                               ucLteCoverFlg;

    pstPlmnSelectionRslt = (NAS_MMCMMC_PLMN_SELECTION_RSLT_STRU *)pstMsg;

    ucLteCoverFlg = NAS_MMC_GetLteCoverageFlg_L1Main(pstPlmnSelectionRslt);

    NAS_MMC_SetRegRsltAdditionalAction_L1Main();

    /* 搜网注册成功,迁移到ON PLMN */
    if (NAS_MMC_PLMN_SELECTION_SUCC == pstPlmnSelectionRslt->enResult)
    {
        NAS_MMC_RcvMmcPlmnSelectionRsltSucc_Initial(ucLteCoverFlg);
    }
    else if (NAS_MMC_PLMN_SELECTION_FAIL == pstPlmnSelectionRslt->enResult)
    {
        /* Modified by c00318887 for 预置频点搜网优化, 2015-9-9, begin */
        NAS_MMC_RcvMmcPlmnSelectionRsltFail_Initial(pstPlmnSelectionRslt, ucLteCoverFlg);
        /* Modified by c00318887 for 预置频点搜网优化, 2015-9-9, end */
    }

    else if (NAS_MMC_PLMN_SELECTION_ABORTED == pstPlmnSelectionRslt->enResult)
    {
        /* 根据不同的返回结果，向MSCC上报本次指定搜网的结果，触发RaomingBroker上报 */
        NAS_MMC_SndMsccPlmnSelectionRsltInd(NAS_MSCC_PIF_PLMN_SELECTION_RESULT_INTERRUPT, ucLteCoverFlg);

        /* 如果当前驻留 应该更新L1状态 */
        if ( NAS_MMC_SPEC_PLMN_SEARCH_STOP == NAS_MMC_GetSpecPlmnSearchState())
        {
            NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_ON_PLMN);
        }
    }
    /* Added by s00246516 for L-C互操作项目, 2014-01-27, Begin */

#if ((FEATURE_ON == FEATURE_CL_INTERWORK) || (FEATURE_ON == FEATURE_UE_MODE_CDMA))
    else if (NAS_MMC_PLMN_SELECTION_INTER_SYS_HRPD == pstPlmnSelectionRslt->enResult)
    {

#if (FEATURE_ON == FEATURE_CL_INTERWORK)
        NAS_MMC_SndMsccPlmnSelectionRsltInd(NAS_MSCC_PIF_PLMN_SELECTION_RESULT_NO_SERVICE, ucLteCoverFlg);
#else
        NAS_MMC_SndMsccPlmnSelectionRsltInd(NAS_MSCC_PIF_PLMN_SELECTION_RESULT_L2C, ucLteCoverFlg);
#endif

        NAS_MMC_StopAllTimer();

        /* 修改 NAS_MMC_L1_STA_OOC--> NAS_MMC_L1_STA_DEACT， 搜网，选的hrpd, lte会进入从模
           mmc状态迁移到NAS_MMC_L1_STA_DEACT  */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_DEACT);

        OM_SetDrxTimerWakeSrc(VOS_GetModemIDFromPid(WUEPS_PID_MMC));
        NAS_MMC_SndDrxTimerInfo(VOS_TRUE);

        return VOS_TRUE;
    }
#endif
    /* Added by s00246516 for L-C互操作项目, 2014-01-27, End */
    else
    {
        /* 异常打印 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMmcPlmnSelectionRslt_Initial:ENTERED");
    }

    /* 只有在驻留态才通知APS当前的接入技术,非驻留态下PDP已经激活情况下
       通知APS当前接入技术为W/L时,APS主动去激活SNDCP，后续回到G下无法恢复
       数传 */
    if (NAS_MMC_SPEC_PLMN_SEARCH_STOP == NAS_MMC_GetSpecPlmnSearchState())
    {
        NAS_MMC_NotifyModeChange(NAS_MML_GetCurrNetRatType(),
                                 NAS_MML_GetSimPsRegStatus());
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmCmServiceInd_Initial
 功能描述  : INITIAL时收到MM模块紧急呼叫指示处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE:
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月15日
   作    者   : s46746
   修改内容   : 新生成函数

 2.日    期   : 2011年8月5日
   作    者   : w00176964
   修改内容   : V7R1 PhaseII 调整
 3.日    期   : 2012年8月13日
   作    者   : z00161729
   修改内容   : DCM定制需求和遗留问题修改,支持L紧急呼叫

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmCmServiceInd_Initial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMCMM_CM_SERVICE_IND_STRU          *pstServiceIndMsg;

    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-14, begin */
    NAS_MML_PLMN_RAT_PRIO_STRU          stAnycellSrchRatList;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList = VOS_NULL_PTR;

    pstPrioRatList      = NAS_MML_GetMsPrioRatList();

    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-14, begin */

    pstServiceIndMsg    = (MMCMM_CM_SERVICE_IND_STRU*)pstMsg;

    if (MM_EMERGENCY_CALL_TRUE == pstServiceIndMsg->ulEmcFlg)
    {
        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-14, begin */
        /* 触发ANYCELL搜网,构造需要anycell搜的接入技术为GU,优先顺序按照syscfg设置 */
        NAS_MMC_BuildCoverageRatPrioListEmgCall_L1Main(pstPrioRatList, &stAnycellSrchRatList);

        NAS_MMC_SndInterAnyCellSearchReq(&stAnycellSrchRatList, NAS_MMC_ANYCELL_SEARCH_SCENE_BUTT);
        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-14, end */
    }

    return VOS_TRUE;
}


#if   (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmCsfbAbortInd_Initial
 功能描述  : INITIAL时收到MM模块紧急呼叫指示处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE:
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年5月7日
   作    者   : b00269685
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmCsfbAbortInd_Initial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == NAS_MMC_GetSpecPlmnSearchState())
    {
        /* 设置当前驻留网络的系统模式为BUTT  */
        NAS_MML_SetCurrSysSubMode(NAS_MML_RRC_SYS_SUBMODE_BUTT);
    }

    /* 构造并发送内部搜网信息:场景CSFB ABORT */
    NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_CSFB_ABORT, VOS_NULL_PTR, 0);

    return VOS_TRUE;
}
#endif

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmCsfbAbortInd_Initial
 功能描述  : INITIAL时收到MM模块MMCMM_PLMN_SEARCH_IND的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE:
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期   : 2015年8月13日
    作    者   : l00289540
    修改内容   : 新生成函数
  2.日    期   : 2015年11月30日
    作    者   : s00217060
    修改内容   : DTS2015102401241修改：异系统到GU失败，回退到LTE的流程不等系
                 统消息就退状态机

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmPlmnSearchInd_Initial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMCMM_PLMN_SEARCH_IND_STRU         *pstPlmnSearchInd;

    pstPlmnSearchInd = (MMCMM_PLMN_SEARCH_IND_STRU *)pstMsg;

    /* 有业务时，重定向失败回退到LTE的流程不等LTE的系统消息就退出异系统状态机，
       需要在NAS_MMC_L1_STA_INITIAL处理这条消息 */
    if ( MM_MMC_PLMN_SEARCH_TYPE_CSFB_BACK_LTE == pstPlmnSearchInd->enPlmnSearchType )
    {
        return NAS_MMC_ProcCsfbRedirFailBackLte_L1Main(ulEventType, pstMsg);
    }

    /* CSFB过程中出服务区或者注册被拒触发的搜网,用户挂断电话触发搜网 */
    if ( MM_MMC_PLMN_SEARCH_TYPE_CSFB_END == pstPlmnSearchInd->enPlmnSearchType )
    {
        if ( NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == NAS_MMC_GetSpecPlmnSearchState() )
        {
            /* 设置当前驻留网络的系统模式为BUTT  */
            NAS_MML_SetCurrSysSubMode(NAS_MML_RRC_SYS_SUBMODE_BUTT);
        }

        /* 构造并发送内部搜网信息:场景CSFB ABORT */
        NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_CSFB_END, VOS_NULL_PTR, 0);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcInterDplmnSetReq_Initial
 功能描述  : INITIAL时收到MSCC模块ID_MSCC_MMC_DPLMN_SET_REQ的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE:
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期   : 2015年10月21日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcInterDplmnSetReq_Initial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 构造并发送内部搜网信息:场景NAS_MMC_PLMN_SEARCH_SCENE_DPLMN_SET */
    NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_DPLMN_SET, VOS_NULL_PTR, 0);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvAreaLostInd_Initial
 功能描述  : On plmn情况下收到丢网消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:RRMM_AREA_LOST_IND消息首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:消息处理完成
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月4日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2013年4月4日
    作    者   : y00176023
    修改内容   : DSDS GUNAS II项目:收到NO RF 迁移到OOC
  3.日    期   : 2014年1月28日
    作    者   : s00246516
    修改内容   : L-C互操作项目:增加获取和注册请求的处理

  4.日    期   : 2014年5月4日
    作    者   : t00173447
    修改内容   : DTS2014042105390,软银定制需求
  5.日    期   : 2014年5月31日
    作    者   : y00245242
    修改内容   : 修改服务状态上报

  6.日    期   : 2015年3月9日
    作    者   : wx270776
    修改内容   : DTS2015031107328, 修改NO_SERVICE上报
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvAreaLostInd_Initial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRatType;

    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());

    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);

    NAS_MMC_StopTimer(TI_NAS_MMC_AVAILABLE_TIMER);

    /* Added by s00246516 for L-C互操作项目, 2014-01-28, Begin */
    NAS_MMC_SetAsAnyCampOn(VOS_FALSE);
    /* Added by s00246516 for L-C互操作项目, 2014-01-28, End */
    /* Modified by c00318887 for 预置频点搜网优化, 2015-9-9, begin */
    NAS_MMC_SaveLastCampedPlmnWithRat(NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMcc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMnc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.enCampPlmnNetRat);
    /* Modified by c00318887 for 预置频点搜网优化, 2015-9-9, end */

    /* 删除NV中的不同国家码的Plmn */
    NAS_MMC_DelDiffMccRplmnInNv_L1Main();

    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* 如果当前为NO RF退出搜网流程 */
    if (VOS_FALSE == NAS_MML_GetRfAvailFlg())
    {
        /* 处理丢网状态，上报服务状态，迁移到ooc，启动available定时器 */
        /* Modified by c00318887 for 预置频点搜网优化, 2015-9-10, begin */
        NAS_MMC_ProcCoverageLost_L1Main(NAS_MMC_PLMN_SEARCH_SCENE_BUTT);
        /* Modified by c00318887 for 预置频点搜网优化, 2015-9-10, end */
        return VOS_TRUE;
    }

    /* Modified by y00245242 for V3R3C60_eCall项目, 2014-5-31, begin */

    enCurRatType = NAS_MML_GetCurrNetRatType();

    if ( (NAS_MML_NET_RAT_TYPE_GSM == enCurRatType)
      || (NAS_MML_NET_RAT_TYPE_WCDMA == enCurRatType) )
    {
        NAS_MMC_SndMmCoverageLostInd();

        NAS_MMC_SndGmmCoverageLostInd();
    }

    /* 更新服务状态 */
    NAS_MMC_SndMsccCoverageInd( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );

    /* 通知TAF当前的服务状态 */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NO_SERVICE);
    /* Modified by y00245242 for V3R3C60_eCall项目, 2014-5-31, end */

    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                            VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    return VOS_TRUE;

}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvSuspendInd_Initial
 功能描述  : 在INITIAL时候收到WAS/GAS/LMM SUSPEND IND 消息的处理
 输入参数  : ulEventType:异系统重选消息类型
              pstMsg: 异系统重选消息首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE: 函数处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月1日
    作    者   : w00167002
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvSuspendInd_Initial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 直接回复失败 */
    NAS_MMC_SndSuspendRsp(NAS_MML_GetCurrNetRatType(), RRC_NAS_SUSPEND_FAILURE);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcInterPlmnListReq_OnPlmn
 功能描述  : ON PLMN下收到内部LIST搜网的处理
 输入参数  : ulEventType:消息类型
             pstMsg:MMCMMC_INTER_PLMN_LIST_REQ消息首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年12月17日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数
  2.日    期   : 2011年09月21日
    作    者   : W00166186
    修改内容   : V7R1 PHASE II LIST开发
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcInterPlmnListReq_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
)
{
    /* 启动LIST搜网状态机 */
    NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_PLMN_LIST);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmSuspendInd_OnPlmn
 功能描述  : 在ON PLMN时候收到WAS/GAS SUSPEND IND 消息的处理
 输入参数  : ulEventType:异系统重选消息类型
              pstMsg: 异系统重选消息首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE: 函数处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月1日
    作    者   : w00167002
    修改内容   : 新生成函数
  2.日    期   : 2011年07月13日
    作    者   : w00176964
    修改内容   : GUNAS V7R1 PhaseII 阶段调整
  3.日    期   : 2011年12月20日
    作    者   : h44270
    修改内容   : 启动异系统状态机时，认为当前无网络，此时APS挂起
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvRrMmSuspendInd_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_IND_ST             *pstSuspendMsg = VOS_NULL_PTR;

    pstSuspendMsg = (RRMM_SUSPEND_IND_ST*)pstMsg;

    /* 根据不同的挂起原因值，启动不同的状态机 */
    switch(pstSuspendMsg->ucSuspendCause)
    {
        case MMC_SUSPEND_CAUSE_CELLRESELECT:
        case MMC_SUSPEND_CAUSE_REDIRECTION:
            NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_INTER_SYS_CELLRESEL);
            break;

        case MMC_SUSPEND_CAUSE_PLMNSEARCH:
            NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_INTER_SYS_OOS);
            break;
        case MMC_SUSPEND_CAUSE_HANDOVER:
            NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_INTER_SYS_HO);
            break;

        case MMC_SUSPEND_CAUSE_CELLCHANGE:
            NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_INTER_SYS_CCO);
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvRrMmSuspendInd_OnPlmn:ENTERED");
            break;
    }

    if ( (MMC_SUSPEND_CAUSE_BUTT != pstSuspendMsg->ucSuspendCause)
      && (MMC_SUSPEND_CAUSE_CELLCHANGE_FALLBACK != pstSuspendMsg->ucSuspendCause) )
    {
        NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,
                                 NAS_MML_GetSimPsRegStatus());
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmCmServiceInd_Ooc
 功能描述  : OOC时收到MM模块呼叫指示处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE:
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年12月29日
   作    者   : z00161729
   修改内容   : DSDS业务重拨时no rf未触发搜网导致业务失败，mm在no cell available
                状态no rf时给mmc发送cm service ind触发搜网
 2.日    期   : 2015年10月08日
   作    者   : zwx247453
   修改内容   : 清除Coverity告警
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmCmServiceInd_Ooc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMCMM_CM_SERVICE_IND_STRU          *pstCmServiceInd = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU          stAnycellSrchRatList;
    /* Modified by c00318887 for 预置频点搜网优化, 2015-9-10, begin */
    NAS_MML_PLMN_RAT_PRIO_STRU          stPrioRatList;

    PS_MEM_SET(&stPrioRatList, 0x00, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));
    pstCmServiceInd = (MMCMM_CM_SERVICE_IND_STRU *)pstMsg;
    PS_MEM_CPY(&stPrioRatList, NAS_MML_GetMsPrioRatList(), sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));
    /* Modified by c00318887 for 预置频点搜网优化, 2015-9-10, end */

    PS_MEM_SET(&stAnycellSrchRatList, 0, sizeof(stAnycellSrchRatList));

    if (MM_CS_SERV_NOT_EXIST == pstCmServiceInd->ulCsServFlg)
    {
        return VOS_TRUE;
    }

    if (VOS_FALSE == NAS_MML_GetRfAvailFlg())
    {
        /* 紧急呼叫触发anycell搜网，其他业务触发rf enable 场景搜网 */
        if (MM_EMERGENCY_CALL_TRUE == pstCmServiceInd->ulEmcFlg)
        {
            /* 业务重发，如果存在NO RF标记信息，则触发搜网  */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

            /* Modified by c00318887 for 预置频点搜网优化, 2015-9-10, begin */
            /* 触发ANYCELL搜网,构造需要anycell搜的接入技术为GU,优先顺序按照syscfg设置 */
            NAS_MMC_BuildCoverageRatPrioListEmgCall_L1Main(&stPrioRatList, &stAnycellSrchRatList);
            /* Modified by c00318887 for 预置频点搜网优化, 2015-9-10, end */

            NAS_MMC_SndInterAnyCellSearchReq(&stAnycellSrchRatList, NAS_MMC_ANYCELL_SEARCH_SCENE_BUTT);

            /*停止Available定时器*/
            NAS_MMC_StopTimer(TI_NAS_MMC_AVAILABLE_TIMER);
            return VOS_TRUE;
        }

        NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

        /* 构造搜网消息 */
        NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_RF_ENABLE, VOS_NULL_PTR, 0);

        /*停止Available定时器*/
        NAS_MMC_StopTimer(TI_NAS_MMC_AVAILABLE_TIMER);
    }
    /* Added by c00318887 for 预置频点搜网优化, 2015-9-8, begin */
    else
    {
        /* 紧急呼叫触发anycell搜网，其他业务不触发搜网 */
        if (MM_EMERGENCY_CALL_TRUE == pstCmServiceInd->ulEmcFlg)
        {
            NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

            NAS_MML_SortSpecRatPrioHighest(NAS_MMC_GetLastCampedPlmnRat(), &stPrioRatList);

            /* 触发ANYCELL搜网,构造需要anycell搜的接入技术为GU,优先顺序按照syscfg设置 */
            NAS_MMC_BuildCoverageRatPrioListEmgCall_L1Main(&stPrioRatList, &stAnycellSrchRatList);

            NAS_MMC_SndInterAnyCellSearchReq(&stAnycellSrchRatList, NAS_MMC_ANYCELL_SEARCH_SCENE_BUTT);

            /*停止Available定时器*/
            NAS_MMC_StopTimer(TI_NAS_MMC_AVAILABLE_TIMER);

            return VOS_TRUE;
        }

    }

    /* Added by c00318887 for 预置频点搜网优化, 2015-9-8, end */

    return VOS_TRUE;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmCmServiceInd_OnPlmn
 功能描述  : ON PLMN时收到MM模块呼叫指示处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE:
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年10月18日
   作    者   : t00212959
   修改内容   : 新生成函数
 2.日    期   : 2012年11月12日
   作    者   : l65478
   修改内容   : DTS2012111202844,列表搜索过程中被LU终止导致列表搜索失败
 3.日    期   : 2015年9月26日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmCmServiceInd_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulCsServFlg;

    ulCsServFlg = NAS_MML_GetCsServiceExistFlg();

    /* 收到CS业务时，可能周期性用户列表搜定时器正在运行，AT没有释放，不能及时相应*/
    if ((NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST))
     && (VOS_TRUE == ulCsServFlg))
    {
        /* 停止TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST */
        NAS_MMC_StopTimer(TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST);

        /* 向MSCC发送REJ */
        NAS_Mmc_SndMsccPlmnListRej();
    }

#if (FEATURE_ON == FEATURE_CSG)
    if ((NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH))
     && (VOS_TRUE == ulCsServFlg))
    {
        NAS_MMC_StopTimer(TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH);

        /* 向MSCC发送rej */
        NAS_MMC_SndMsccCsgListSearchRej();
    }
#endif

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmCmServiceInd_OnPlmn
 功能描述  : ON PLMN时收到MM模块搜网指示处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE:
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年1月18日
   作    者   : w00242748
   修改内容   : 新生成函数
 2.日    期   : 2014年6月17日
   作    者   : w00176964
   修改内容   : DTS2014061606181:区分紧急呼叫场景需要进行anycell搜网
 3.日    期   : 2015年8月13日
   作    者   : l00289540
   修改内容   : User_Exp_Improve修改
 4.日    期   : 2015年10月08日
   作    者   : zwx247453
   修改内容   : 清除Coverity告警
 5.日    期   : 2015年11月30日
   作    者   : s00217060
   修改内容   : DTS2015102401241修改：异系统到GU失败，回退到LTE，不等消息就
                 退出状态机

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmPlmnSearchInd_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMCMM_PLMN_SEARCH_IND_STRU                             *pstPlmnSearchInd;

    pstPlmnSearchInd = (MMCMM_PLMN_SEARCH_IND_STRU *)pstMsg;

    /* 如果MM在通知LMM CSFB后，L重选到GU失败回退到L后，MMC给MM发送L的resume ind
       后，MM给MMC发送的搜网请求即为CSFB类型 */
    if ( MM_MMC_PLMN_SEARCH_TYPE_CSFB_BACK_LTE == pstPlmnSearchInd->enPlmnSearchType )
    {
        /* 提取函数 */
        return NAS_MMC_ProcCsfbRedirFailBackLte_L1Main(ulEventType, pstMsg);
    }

    if (MM_MMC_PLMN_SEARCH_TYPE_CSFB_END == pstPlmnSearchInd->enPlmnSearchType)
    {
        if (VOS_TRUE == NAS_MMC_IsNeedStartHighPrioRatHPlmnTimer_CsfbEnd())
        {
            /* 启动定时器，时长为5s */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_HIGH_PRIO_RAT_HPLMN_TIMER, 5*NAS_MML_ONE_THOUSAND_MILLISECOND);
        }
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmRrConnInfoInd_OnPlmn
 功能描述  : 在ON PLMN时候收到MM发送的链接请求的处理
 输入参数  : ulEventType:消息类型
             pstMsg: MMCMM_RR_CONN_INFO_IND消息首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE: 函数处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月1日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数
  2.日    期   : 2011年7月28日
    作    者   : w00176964
    修改内容   : V7R1 Phase II调整

  3.日    期   : 2011年10月12日
    作    者   : zhoujun 40661
    修改内容   : CTX中增加需要搜网的变量，判断是否需要搜索

  4.日    期   : 2011年11月17日
    作    者   : w00167002
    修改内容   : DTS2011111603447:进行缓存的搜网的处理
  5.日    期   : 2012年5月24日
    作    者   : w00176964
    修改内容   : GUL BG项目调整:处理缓存的指定搜网时先判断下是否已经正常服务了
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmRrConnInfoInd_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    VOS_UINT32                          ulRrcConnExistFlag;

    /* 判断信令链接是否已经完成释放 */
    ulRrcConnExistFlag  = NAS_MML_IsRrcConnExist();

    if ( VOS_TRUE == ulRrcConnExistFlag )
    {
        /* 信令链接未释放完成，继续等待信令链接释放消息 */
        return VOS_TRUE;
    }

    /* 需要已注册失败导致需要搜网的为优先 */
    if ( VOS_TRUE == NAS_MMC_IsPlmnSearchNeeded_L1Main())
    {
        return NAS_MMC_PerformPlmnSearch_L1Main();
    }

    /* 如果注册失败不需要发起搜网,则判断是否有缓存的搜网标志 */
    NAS_MMC_PerformBufferedPlmnSearch_L1Main();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGmmSignalingStatusInd_OnPlmn
 功能描述  : 在ON PLMN时候收到GMM发送的链接请求的处理
 输入参数  : ulEventType:消息类型
             pstMsg: MMCGMM_SIGNALING_STATUS_IND消息首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE: 函数处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月1日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数
  2.日    期   : 2011年7月28日
    作    者   : w00176964
    修改内容   : V7R1 Phase II调整

  3.日    期   : 2011年10月12日
    作    者   : zhoujun 40661
    修改内容   : CTX中增加需要搜网的变量，判断是否需要搜索

  4.日    期   : 2011年11月17日
    作    者   : w00167002
    修改内容   : DTS2011111603447:进行缓存的搜网的处理
  5.日    期   : 2012年5月24日
    作    者   : w00176964
    修改内容   : GUL BG项目调整:处理缓存的指定搜网时先判断下是否已经正常服务了
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvGmmSignalingStatusInd_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    VOS_UINT32                          ulRrcConnExistFlag;

    /* 判断信令链接是否已经完成释放 */
    ulRrcConnExistFlag  = NAS_MML_IsRrcConnExist();

    if ( VOS_TRUE == ulRrcConnExistFlag )
    {
        /* 信令链接未释放完成，继续等待信令链接释放消息 */
        return VOS_TRUE;
    }

    /* 需要已注册失败导致需要搜网的为优先 */
    if ( VOS_TRUE == NAS_MMC_IsPlmnSearchNeeded_L1Main())
    {
        return NAS_MMC_PerformPlmnSearch_L1Main();
    }

    /* 如果注册失败不需要发起搜网,则判断是否有缓存的搜网标志 */
    NAS_MMC_PerformBufferedPlmnSearch_L1Main();


    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGmmTbfRelInd_OnPlmn
 功能描述  : 在ON PLMN时候收到TBF释放请求的处理
 输入参数  : ulEventType:消息类型
             pstMsg: MMCGMM_TBF_REL_IND消息首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE: 函数处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月1日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数
  2.日    期   : 2011年7月28日
    作    者   : w00176964
    修改内容   : V7R1 Phase II调整

  3.日    期   : 2011年10月12日
    作    者   : zhoujun 40661
    修改内容   : CTX中增加需要搜网的变量，判断是否需要搜索

  4.日    期   : 2011年11月17日
    作    者   : w00167002
    修改内容   : DTS2011111603447:进行缓存的搜网的处理
  5.日    期   : 2012年5月24日
    作    者   : w00176964
    修改内容   : GUL BG项目调整:处理缓存的指定搜网时先判断下是否已经正常服务了
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvGmmTbfRelInd_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    VOS_UINT32                          ulRrcConnExistFlag;

    /* 判断信令链接是否已经完成释放 */
    ulRrcConnExistFlag  = NAS_MML_IsRrcConnExist();

    if ( VOS_TRUE == ulRrcConnExistFlag )
    {
        /* 信令链接未释放完成，继续等待信令链接释放消息 */
        return VOS_TRUE;
    }

    /* 需要已注册失败导致需要搜网的为优先 */
    if ( VOS_TRUE == NAS_MMC_IsPlmnSearchNeeded_L1Main())
    {
        return NAS_MMC_PerformPlmnSearch_L1Main();
    }

    /* 如果注册失败不需要发起搜网,则判断是否有缓存的搜网标志 */
    NAS_MMC_PerformBufferedPlmnSearch_L1Main();


    return VOS_TRUE;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmRrRelInd_OnPlmn
 功能描述  : 在ON PLMN时候收到MM链接释放请求的处理
 输入参数  : ulEventType:消息类型
             pstMsg: MMCMM_RR_REL_IND消息首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE: 函数处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年4月1日
   作    者   : zhoujun /40661
   修改内容   : 新生成函数
 2.日    期   : 2011年7月28日
   作    者   : w00176964
   修改内容   : V7R1 Phase II调整

 3.日    期   : 2011年10月12日
   作    者   : zhoujun 40661
   修改内容   : CTX中增加需要搜网的变量，判断是否需要搜索
 4.日    期   : 2011年11月17日
    作    者   : w00167002
    修改内容   : DTS2011111603447:进行缓存的搜网的处理
  5.日    期   : 2012年5月24日
    作    者   : w00176964
    修改内容   : GUL BG项目调整:处理缓存的指定搜网时先判断下是否已经正常服务了
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmRrRelInd_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    VOS_UINT32                          ulRrcConnExistFlag;

    /* 判断信令链接是否已经完成释放 */
    ulRrcConnExistFlag  = NAS_MML_IsRrcConnExist();

    if ( VOS_TRUE == ulRrcConnExistFlag )
    {
        /* 信令链接未释放完成，继续等待信令链接释放消息 */
        return VOS_TRUE;
    }

    /* 需要已注册失败导致需要搜网的为优先 */
    if ( VOS_TRUE == NAS_MMC_IsPlmnSearchNeeded_L1Main())
    {
        return NAS_MMC_PerformPlmnSearch_L1Main();
    }

    /* 如果注册失败不需要发起搜网,则判断是否有缓存的搜网标志 */
    NAS_MMC_PerformBufferedPlmnSearch_L1Main();


    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmRelIndInMmcIdle
 功能描述  : ON PLMN时收到AS发送的链接释放请求
 输入参数  : ulEventType:消息类型
             pstMsg: RRMM_REL_IND消息首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE: 函数处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月1日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数
  2.日    期   : 2011年7月28日
    作    者   : w00176964
    修改内容   : V7R1 Phase II调整

  3.日    期   : 2011年10月12日
    作    者   : zhoujun 40661
    修改内容   : CTX中增加需要搜网的变量，判断是否需要搜索

  4.日    期   : 2011年11月17日
    作    者   : w00167002
    修改内容   : DTS2011111603447:进行缓存的搜网的处理
  5.日    期   : 2012年5月24日
    作    者   : w00176964
    修改内容   : GUL BG项目调整:处理缓存的指定搜网时先判断下是否已经正常服务了
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmRelInd_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    VOS_UINT32                          ulRrcConnExistFlag;

    /* 判断信令链接是否已经完成释放 */
    ulRrcConnExistFlag  = NAS_MML_IsRrcConnExist();

    if ( VOS_TRUE == ulRrcConnExistFlag )
    {
        /* 信令链接未释放完成，继续等待信令链接释放消息 */
        return VOS_TRUE;
    }

    /* 需要已注册失败导致需要搜网的为优先 */
    if ( VOS_TRUE == NAS_MMC_IsPlmnSearchNeeded_L1Main())
    {
        return NAS_MMC_PerformPlmnSearch_L1Main();
    }

    /* 如果注册失败不需要发起搜网,则判断是否有缓存的搜网标志 */
    NAS_MMC_PerformBufferedPlmnSearch_L1Main();

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvCmServiceRejectInd_OnPlmn
 功能描述  : ON PLMN时收到CS业务导致卡无效的消息
 输入参数  : ulEventType:消息类型
             pstMsg: MMCMM_CM_SERVICE_REJECT_IND消息首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE: 函数处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年4月1日
   作    者   : zhoujun /40661
   修改内容   : 新生成函数
 2.日    期   : 2011年7月28日
   作    者   : w00176964
   修改内容   : V7R1 Phase II调整
 3.日    期   : 2011年12月5日
   作    者   : z00161729
   修改内容   : V7R1 Phase IV调整,当前SYSCFG中L不在时，也需要向LMM通知ID_MMC_LMM_ACTION_RESULT_REQ
 4.日    期   : 2014年4月24日
   作    者   : w00242748
   修改内容   : DTS2014042405819:无卡状态下，紧急呼被拒#5，后发起ANYCELL搜，导致退状态机
                后下发RRMM_UE_OOC_STATUS_NOTIFY_IND，导致网络不断下发CM SERVICE REJ
 5.日    期   : 2014年4月29日
   作    者   : s00261364
   修改内容   : ecall项目修改服务状态上报

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvCmServiceRejectInd_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
)
{
#if (FEATURE_ON == FEATURE_LTE)
    MMCMM_CM_SERVICE_REJECT_IND_STRU   *pstRcvMsg = VOS_NULL_PTR;
    NAS_MMC_GU_ACTION_RSLT_INFO_STRU    stActionRslt;

    pstRcvMsg           = ( MMCMM_CM_SERVICE_REJECT_IND_STRU* )pstMsg;

#endif
    /* Deleted by s00261364 for V3R360_eCall项目, 2014-4-30, begin */

    /* Deleted by s00261364 for V3R360_eCall项目, 2014-4-30, end */

#if (FEATURE_ON == FEATURE_LTE)
    /* 当前SYSCFG中L不在时，也需要向LMM通知 */
    stActionRslt.enProcType     = NAS_MML_PROC_CM_SER;
    stActionRslt.enRegRst       = NAS_MML_REG_RESULT_FAILURE;
    stActionRslt.enReqDomain    = NAS_MMC_REG_DOMAIN_CS;
    stActionRslt.enRstDomain    = NAS_MMC_REG_DOMAIN_CS;
    stActionRslt.enCnCause      = (NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16)pstRcvMsg->ulCause;
    stActionRslt.ulAttemptCount = 0;

    NAS_MMC_SndLmmRegActionResultReq(&stActionRslt);
#endif

    if (VOS_FALSE == NAS_MML_IsUsimStausValid())
    {
        if ( VOS_FALSE == NAS_MML_IsRrcConnExist() )
        {
            /* 迁移到Initial状态 */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

            /* 根据结果中的接入技术覆盖信息启动anycell状态机，优先搜索当前接入技术 */
            NAS_MMC_SndInterAnyCellSearchReq(VOS_NULL_PTR, NAS_MMC_ANYCELL_SEARCH_SCENE_BUTT);
        }
        else
        {
            NAS_MMC_SetCsRegAdditionalAction_L1Main(NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL);
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvNetworkDetachInd_OnPlmn
 功能描述  : On plmn情况下收到GMM注册结果的处理
 输入参数  : ulEventType:消息类型
             pstMsg:MMCGMM_NETWORK_DETACH_IND消息首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:消息处理完成
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月28日
    作    者   : luokaihui / l00167671
    修改内容   : 新生成函数
  2.日    期   : 2011年7月28日
    作    者   : w00176964
    修改内容   : V7R1 Phase II调整
  3.日    期   : 2012年2月13日
    作    者   : w00167002
    修改内容   : DTS2011122704039:additional action值若为无效值NAS_MMC_ADDITIONAL_ACTION_BUTT
                 则不更新当前的additional action
  4.日    期   : 2013年12月25日
    作    者   : z00161729
    修改内容   : SVLTE支持NCELL搜网
  5.日    期   : 2015年6月6日
    作    者   : s00217060
    修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0修改
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvNetworkDetachInd_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMCGMM_NETWORK_DETACH_IND_STRU                         *pstDetachMsg = VOS_NULL_PTR;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;
    VOS_UINT32                                              ulRrcConnExistFlag;

    pstDetachMsg        = (MMCGMM_NETWORK_DETACH_IND_STRU *)pstMsg;

    enAdditionalAction = NAS_MMC_ProcGmmNetworkDetachInd(pstDetachMsg);

    /* AdditionalAction有效，更新PS的下一步的动作类型 */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enAdditionalAction )
    {
        NAS_MMC_SetPsRegAdditionalAction_L1Main(enAdditionalAction);
    }

#if   (FEATURE_ON == FEATURE_LTE)
    /* 给LMM发送detach结果消息 */
    NAS_MMC_SndLmmMtDetachIndActionResultReq(pstDetachMsg->ulDetachType,
        (NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16)pstDetachMsg->ulDetachCause);
#endif

    /* 不需要搜网直接返回 */
    if (VOS_FALSE == NAS_MMC_IsPlmnSearchNeeded_L1Main())
    {
        /* 正常服务则停止available定时器 */
        if ( VOS_TRUE == NAS_MMC_IsNormalServiceStatus())
        {
            NAS_MMC_ResetOosPlmnSearchTimerCount_OnPlmn();

            NAS_MMC_StopTimer(TI_NAS_MMC_AVAILABLE_TIMER);

            /* Added by c00318887 for 预置频点搜网优化, 2015-9-1, begin */
            NAS_MMC_StopTimer(TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER);
            /* Added by c00318887 for 预置频点搜网优化, 2015-9-1, end */

        }

        return VOS_TRUE;
    }

    /* 判断信令链接是否已经完成释放 */
    ulRrcConnExistFlag  = NAS_MML_IsRrcConnExist();

    if ( VOS_TRUE == ulRrcConnExistFlag )
    {
        /* 信令链接未释放完成，继续等待信令链接释放消息 */
        return VOS_TRUE;
    }

    /* 发起搜网 */
    (VOS_VOID)NAS_MMC_PerformPlmnSearch_L1Main();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiAvailTimerExpired_HistorySearch_OnPlmn
 功能描述  : available定时器超时后进行history搜的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月25日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MMC_RcvTiAvailTimerExpired_HistorySearch_OnPlmn(VOS_VOID)
{
    /* 设置为 initail 状态 */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

    /* 构造内部搜网消息 */
    NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED_HISTORY_PLMN_SEARCH,
                                  VOS_NULL_PTR, 0);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiAvailTimerExpired_PrefBandSearch_OnPlmn
 功能描述  : available定时器超时后进行PrefBand搜的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月09日
    作    者   : h00281185
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MMC_RcvTiAvailTimerExpired_PrefBandSearch_OnPlmn(VOS_VOID)
{
    /* 设置为 initail 状态 */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

    /* 构造内部搜网消息 */
    NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED_PREFBAND_PLMN_SEARCH,
                                  VOS_NULL_PTR, 0);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiAvailTimerExpired_NCellSearch_OnPlmn
 功能描述  : 进行NCELL搜处理
 输入参数  : VOS_VOID
 输出参数  : VOS_VOID
 返 回 值  : VOS_VOID
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年4月27日
   作    者   : w00242748
   修改内容   : 新生成函数
 2.日    期   : 2014年1月26日
   作    者   : z00161729
   修改内容   : DTS2014012305088：支持增强NCELL搜网，如果Modem1传递过来的邻区信息不存在的情况下，通过历史频点支持NCELL搜索
 3.日    期   : 2014年2月25日
   作    者   : w00242748
   修改内容   : DTS2014022110695：增加NCELL搜网的可能性，当前存在TD邻区的时候，
                也得去搜网LTE，反之亦然。总言之，不管邻区在不在，均需要搜索TD/LTE
*****************************************************************************/
VOS_VOID  NAS_MMC_RcvTiAvailTimerExpired_NcellSearch_OnPlmn(VOS_VOID)
{
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pastSearchedPlmnListInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstRatPrioList        = VOS_NULL_PTR;
    NAS_MML_SIM_EHPLMN_INFO_STRU                           *pstEHPlmnInfo = VOS_NULL_PTR;
    VOS_UINT32                                              ulRatCnt;
    NAS_MML_PLMN_ID_STRU                                    stPlmnId;
    NAS_MML_PLMN_WITH_RAT_STRU         *pstUserSpecPlmn     = VOS_NULL_PTR;

    /* 获取优先级列表 */
    pstRatPrioList     = NAS_MML_GetMsPrioRatList();

    /* 获取EHPLMN */
    pstEHPlmnInfo   = NAS_MML_GetSimEhplmnList();
    pstUserSpecPlmn = NAS_MMC_GetUserSpecPlmnId();

    /* 自动搜网模式添加hplmn，手动搜网模式添加用户指定网络 */
    if (NAS_MMC_PLMN_SELECTION_MODE_AUTO == NAS_MMC_GetPlmnSelectionMode())
    {
        stPlmnId.ulMcc = pstEHPlmnInfo->astEhPlmnInfo[0].stPlmnId.ulMcc;
        stPlmnId.ulMnc = pstEHPlmnInfo->astEhPlmnInfo[0].stPlmnId.ulMnc;
    }
    else
    {
        stPlmnId.ulMcc = pstUserSpecPlmn->stPlmnId.ulMcc;
        stPlmnId.ulMnc = pstUserSpecPlmn->stPlmnId.ulMnc;
    }

    pastSearchedPlmnListInfo = (NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMC,
                             sizeof(NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU) * NAS_MML_MAX_RAT_NUM);

    /* 分配内存失败 */
    if (VOS_NULL_PTR == pastSearchedPlmnListInfo)
    {
        return;
    }

    PS_MEM_SET(pastSearchedPlmnListInfo, 0, sizeof(NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU) * NAS_MML_MAX_RAT_NUM);

    for (ulRatCnt = 0; ulRatCnt < NAS_MML_MAX_RAT_NUM; ulRatCnt++)
    {
        pastSearchedPlmnListInfo[ulRatCnt].enRatType = NAS_MML_NET_RAT_TYPE_BUTT;
    }

    NAS_MMC_InitSearchedPlmnListInfo(pastSearchedPlmnListInfo);

    /* 根据T和L的邻区频点信息构造搜网列表,如果邻区个数为0，也需要构造搜网列表 */
    for (ulRatCnt =0; ulRatCnt< pstRatPrioList->ucRatNum; ulRatCnt++)
    {
        /* 初始化上报的接入技术列表 */
        pastSearchedPlmnListInfo[ulRatCnt].enRatType        = pstRatPrioList->aucRatPrio[ulRatCnt];
        pastSearchedPlmnListInfo[ulRatCnt].ulHighPlmnNum    = 0;
        pastSearchedPlmnListInfo[ulRatCnt].ulLowPlmnNum     = 0;

        if (NAS_MML_NET_RAT_TYPE_LTE == pastSearchedPlmnListInfo[ulRatCnt].enRatType)
        {
            pastSearchedPlmnListInfo[ulRatCnt].ulHighPlmnNum            = 1;
            pastSearchedPlmnListInfo[ulRatCnt].astHighPlmnList[0].ulMcc = stPlmnId.ulMcc;
            pastSearchedPlmnListInfo[ulRatCnt].astHighPlmnList[0].ulMnc = stPlmnId.ulMnc;
        }

        if (NAS_MML_NET_RAT_TYPE_WCDMA == pastSearchedPlmnListInfo[ulRatCnt].enRatType)
        {
            pastSearchedPlmnListInfo[ulRatCnt].ulHighPlmnNum    = 1;
            pastSearchedPlmnListInfo[ulRatCnt].astHighPlmnList[0].ulMcc = stPlmnId.ulMcc;
            pastSearchedPlmnListInfo[ulRatCnt].astHighPlmnList[0].ulMnc = stPlmnId.ulMnc;
        }
    }

    /* 定时器超时，设置为 initail 状态 */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

    /* 构造搜网消息 */
    NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED_NCELL_SEARCH,
                                  pastSearchedPlmnListInfo, NAS_MML_MAX_RAT_NUM);

    PS_MEM_FREE(WUEPS_PID_MMC, pastSearchedPlmnListInfo);

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiAvailTimerExpired_L1Main
 功能描述  : ON PLMN和OOC下Available Timer 定时器超时的处理
 输入参数  : ulEventType:消息类型
             pstMsg:TI_NAS_MMC_AVAILABLE_TIMER消息首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:消息处理完成
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年4月27日
   作    者   : zhoujun /40661
   修改内容   : 新生成函数
 2.日    期   : 2011年9月20日
   作    者   : w00176964
   修改内容   : V7R1 PhaseII 内部LIST搜网调整
 3.日    期   : 2011年9月24日
   作    者   : w00166186
   修改内容   : V7R1 PhaseII 内部LIST搜网调整
 4.日    期   : 2011年12月20日
   作    者   : w00167002
   修改内容   : DTS2011122001697: 当前处在正常服务状态且未进行过搜网，否则在
                高优先级指定搜网时或者快速指定搜时，被用户指定搜打断，若用户
                指定的网络和先前驻留的网络相同，高优先级搜网状态机退出后，
                会不进行用户指定搜。
 5.日    期   : 2012年4月26日
   作    者   : w00176964
   修改内容   : GUL BG项目调整
 6.日    期   : 2013年12月25日
   作    者   : z00161729
   修改内容   : SVLTE支持NCELL搜网
 7.日    期   : 2014年1月2日
  作    者   : z00234330
  修改内容   : 如果当前时GTL模式，且gas上报了临区信息，且临区信息存在时则
             本次available timer不搜索，继续启动
 8.日    期   : 2014年1月22日
   作    者   : w00167002
   修改内容   : SVLTE共天线项目:周期搜网定时器超时时候，进行NO RF可用搜网。
 9.日    期   : 2014年01月17日
   作    者   : l00198894
   修改内容   : V9R1C53 C+L 离网重选项目
10.日    期   : 2013年3月28日
   作    者   : y00176023
   修改内容   : DSDS GUNAS II项目:NO RF时定时器超时重启定时器，不搜网
11.日    期   : 2013年4月4日
   作    者   : y00176023
   修改内容   : DSDS GUNAS II项目:收到NO RF 退状态机，不搜网
12.日    期   : 2014年4月21日
   作    者   : w00167002
   修改内容   : DSDS GUNAS II项目:收到NO RF,调整到预处理进行处理
13.日    期   : 2015年5月25日
   作    者   : s00217060
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0修改
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiAvailTimerExpired_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 是否需要触发搜网 */
    if (VOS_TRUE == NAS_MMC_IsAvailTimerExpiredTriggerPlmnSearch_L1Main())
    {
        return NAS_MMC_ProcTiAvailableTimerExpiredTriggerPlmnSearch_L1Main();

    }

    return VOS_TRUE;

}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrmPsStatusInd_L1Main
 功能描述  : ON PLMN/INITIAL/OOC下收到RRM通知的资源可用通知时的处理
 输入参数  : ulEventType:消息类型
             pstMsg:ID_RRM_PS_STATUS_IND消息首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:消息处理完成
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年1月22日
   作    者   : w00167002
   修改内容   : 新生成函数
 2.日    期   : 2013年3月29日
   作    者   : y00176023
   修改内容   : DSDS GUNAS II项目:NO RF情况下向RRM发起去注册，只考虑GU不考虑LTE搜网产生的NO RF

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrmPsStatusInd_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 在收到RRM的资源可用通知时候，需要判断当前是否存在NO RF标记，如果不存在，则不触发搜网 */
    if (VOS_TRUE == NAS_MML_GetRfAvailFlg())
    {
        return VOS_TRUE;
    }

    /* 如果存在NO RF标记信息，则触发搜网  */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

    /* 构造搜网消息 */
    NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_RF_ENABLE, VOS_NULL_PTR, 0);

    /*停止Available定时器*/
    NAS_MMC_StopTimer(TI_NAS_MMC_AVAILABLE_TIMER);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrmPsStatusInd_L1Main_Deactive
 功能描述  : deactive下收到RRM通知的资源可用通知时的处理
 输入参数  : ulEventType:消息类型
             pstMsg:ID_RRM_PS_STATUS_IND消息首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:消息处理完成
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年5月28日
   作    者   : w00242748
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrmPsStatusInd_L1Main_Deactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (VOS_TRUE == NAS_MML_GetRfAvailFlg())
    {
        return VOS_TRUE;
    }

    /* 当前处于NO RF 向MSCC透传消息,不触发搜网，由MSCC控制是否触发搜网 */
    NAS_MMC_SndMsccRfAvailInd(VOS_TRUE);

    /* 设置当前RF可用标记为:RF可用 */
    NAS_MML_SetRfAvailFlg(VOS_TRUE);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmSysInfo_OnPlmn
 功能描述  : On plmn情况下收到W的系统消息
 输入参数  : ulEventType:消息类型
             pstMsg:RRMM_SYS_INFO_IND消息首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:消息处理完成
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月3日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数

  2.日    期   : 2011年8月05日
    作    者   : w00176964
    修改内容   : V7R1 Phase II全局变量调整
  3.日    期   : 2012年6月16日
    作    者   : l00171473
    修改内容   : DTS2012061409086, 收到W或G的系统消息时通知L模
  4.日    期   : 2012年8月21日
    作    者   : z00161729
    修改内容   : DCM定制需求和遗留问题修改
  5.日    期   : 2012年12月11日
    作    者   : w00176964
    修改内容   : 收到系统消息接入禁止信息变化则通知MMA
  6.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核

  7.日    期   : 2014年1月18日
    作    者   : z00234330
    修改内容   : dts2014011801513,接入层上报的系统消息里面有可能没有携带plmnid,
                 此处判断并没有判断plmnid是否有效
  8.日    期   : 2014年2月14日
    作    者   : z00161729
    修改内容   : DTS2014021000537:sim卡anycell驻留l的小区mmc收到系统消息转给mma时应该将禁止网络标识置为TRUE，
                 不上报pstransfer:1,否则导致ps迁移到modem0后l不注册，乒乓ps迁移

  9.日    期   : 2014年5月4日
    作    者   : t00173447
    修改内容   : DTS2014042105390,软银定制需求
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmSysInfo_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, begin */
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurCsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldCsRestrictInfo;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurPsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldPsRestrictInfo;
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, end */

    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, begin */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;

    /* 获取LTE能力状态 */
    enLCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();

    NAS_MMC_RcvGuSysInfoIndSetLteAbility(pstMsg,enLCapabilityStatus);
#endif
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, end */

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    PS_MEM_SET(&stOldCsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_SET(&stOldPsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

    /* 更新驻留状态 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

    /* 保留老的驻留网络信息 */
    pstCurCampInfo  = NAS_MML_GetCurrCampPlmnInfo();
    PS_MEM_CPY(&stOldCampInfo, pstCurCampInfo, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, begin */
    pstCurCsRestrictInfo    = NAS_MML_GetCsAcRestrictionInfo();
    pstCurPsRestrictInfo    = NAS_MML_GetPsAcRestrictionInfo();

    PS_MEM_CPY(&stOldCsRestrictInfo, pstCurCsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_CPY(&stOldPsRestrictInfo, pstCurPsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, end */

    /* 根据系统消息，更新MML的全部变量 */
    NAS_MMC_UpdateNetworkInfo_WasSysInfo(pstMsg);

    /* 驻留小区变化时，上报系统消息 ,或者从bar到不bar */
    if ((VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
     || ((VOS_TRUE == stOldPsRestrictInfo.ucRestrictRegister)
      && (VOS_FALSE == pstCurPsRestrictInfo->ucRestrictRegister)))
    {
        /* 主动上报 */
        NAS_MMC_SndMsccSysInfo();

    }

    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
    /* 驻留小区的接入受限信息变化时,通知MSCC模块当前接入受限信息 */
    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldCsRestrictInfo, pstCurCsRestrictInfo))
    {
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_CS, pstCurCsRestrictInfo);
    }

    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldPsRestrictInfo, pstCurPsRestrictInfo))
    {
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_PS, pstCurPsRestrictInfo);
    }
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, end */

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))
    /* CBS上报*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_WCDMA);
#endif

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, end */

    /*转发系统消息通知 给 MM/GMM */
    NAS_MMC_SndMmWasSysInfoInd (NAS_MMC_GetCurrentLaiForbbidenType(), VOS_FALSE, pstMsg);
    NAS_MMC_SndGmmWasSysInfoInd (NAS_MMC_GetCurrentLaiForbbidenType(),VOS_FALSE, pstMsg);

#if (FEATURE_ON == FEATURE_LTE)

    NAS_MMC_SndLmmWcdmaSysInfoInd(pstMsg);
#endif

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGrrMmSysInfo_OnPlmn
 功能描述  : On plmn情况下收到G下系统消息
 输入参数  : ulEventType:消息类型
              pstMsg:GRRMM_SYS_INFO_IND消息地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:消息处理完成
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月3日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数
  2.日    期   : 2012年6月16日
    作    者   : l00171473
    修改内容   : DTS2012061409086, 收到W或G的系统消息时通知L模
  3.日    期   : 2012年8月21日
    作    者   : z00161729
    修改内容   : DCM定制需求和遗留问题修改
  4.日    期   : 2012年12月11日
    作    者   : w00176964
    修改内容   : 收到系统消息接入禁止信息变化则通知MMA
  5.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  6.日    期   : 2013年11月01日
    作    者   : l00208543
    修改内容   : 根据卡类型禁止网络制式

  7.日    期   : 2014年5月4日
    作    者   : t00173447
    修改内容   : DTS2014042105390,软银定制需求
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvGrrMmSysInfo_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, begin */
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurCsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldCsRestrictInfo;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurPsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldPsRestrictInfo;
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, end */

    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, begin */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;

    /* 获取LTE能力状态 */
    enLCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();

    NAS_MMC_RcvGuSysInfoIndSetLteAbility(pstMsg, enLCapabilityStatus);

#endif
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, end */

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    PS_MEM_SET(&stOldCsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_SET(&stOldPsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

    /* 如果收到GAS的系统消息，且目前Utran被Enable，则重新Disable Utran */
    NAS_MMC_RcvGasSysInfoSetUtranCapabilityStatus();

    /* 更新驻留状态 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

    /* 保留老的驻留网络信息 */
    pstCurCampInfo  = NAS_MML_GetCurrCampPlmnInfo();
    PS_MEM_CPY(&stOldCampInfo, pstCurCampInfo, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, begin */
    pstCurCsRestrictInfo    = NAS_MML_GetCsAcRestrictionInfo();
    pstCurPsRestrictInfo    = NAS_MML_GetPsAcRestrictionInfo();

    PS_MEM_CPY(&stOldCsRestrictInfo, pstCurCsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_CPY(&stOldPsRestrictInfo, pstCurPsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, end */

    /* 根据系统消息，更新MML的全部变量 */
    NAS_MMC_UpdateNetworkInfo_GasSysInfo(pstMsg);

    /* 驻留小区变化时，上报系统消息 */
    if (VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
    {
        /* 主动上报 */
        NAS_MMC_SndMsccSysInfo();

    }

    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
    /* 驻留小区的接入受限信息变化时,通知MSCC模块当前接入受限信息 */
    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldCsRestrictInfo, pstCurCsRestrictInfo))
    {
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_CS, pstCurCsRestrictInfo);
    }

    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldPsRestrictInfo, pstCurPsRestrictInfo))
    {
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_PS, pstCurPsRestrictInfo);
    }
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, end */

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))
    /* CBS上报*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_GSM);
#endif

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, end */

    /*转发系统消息通知 给 MM/GMM */
    NAS_MMC_SndMmGsmSysInfoInd (NAS_MMC_GetCurrentLaiForbbidenType(), VOS_FALSE, pstMsg);
    NAS_MMC_SndGmmGsmSysInfoInd (NAS_MMC_GetCurrentLaiForbbidenType(), VOS_FALSE, pstMsg);

#if (FEATURE_ON == FEATURE_LTE)

    NAS_MMC_SndLmmGsmSysInfoInd(pstMsg);
#endif

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_EnterOocStatus_OnPlmn
 功能描述  : 进入OOC的状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月31日
    作    者   : z40661
    修改内容   : 新生成函数

  2.日    期   : 2012年11月9日
    作    者   : z40661
    修改内容   : DRX Timer
  3.日    期   : 2013年3月25日
    作    者   : z60575
    修改内容   : DTS2013032501170，低功耗合入
  4.日    期   : 2013年10月29日
    作    者   : z00234330
    修改内容   : 低功耗接口合入  dts2013102911530
*****************************************************************************/
VOS_VOID  NAS_MMC_EnterOocStatus_OnPlmn( VOS_VOID )
{
    VOS_UINT32                          ulReceivePid;

#if (FEATURE_ON == FEATURE_LTE)
    if ( NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        NAS_MMC_SndLmmUeOocStatusInd();
        /* 进入搜网低功耗时，需要打开drx开关 */
        OM_SetDrxTimerWakeSrc(VOS_GetModemIDFromPid(WUEPS_PID_MMC));

        NAS_MMC_SndDrxTimerInfo(VOS_TRUE);
        return ;
    }
#endif

    if ( NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {
        ulReceivePid = UEPS_PID_GAS;
    }
    else if ( NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        ulReceivePid = WUEPS_PID_WRR;
    }
    else
    {
        return;
    }

    NAS_MMC_SndGuAsUeOocStatus(ulReceivePid);

    /* 进入搜网低功耗时，需要打开drx开关 */
    OM_SetDrxTimerWakeSrc(VOS_GetModemIDFromPid(WUEPS_PID_MMC));
    NAS_MMC_SndDrxTimerInfo(VOS_TRUE);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvAreaLostInd_OnPlmn
 功能描述  : On plmn情况下收到丢网消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:RRMM_AREA_LOST_IND消息首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:消息处理完成
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月26日
    作    者   : z40661
    修改内容   : 新生成函数
  2.日    期   : 2011年7月28日
    作    者   : w00176964
    修改内容   : V7R1 Phase II调整
  3.日    期   : 2012年04月07日
    作    者   : l00130025
    修改内容   : 问题单号:DTS2012040106098,调整CoverageLost和service的上报顺序，以更新MMA的状态到DeepSleep
  4.日    期   : 2012年3月31日
    作    者   : z40661
    修改内容   : V7R1修改搜网低功耗
  5.日    期   : 2012年11月7日
    作    者   : l00167671
    修改内容   : DTS2012110607212: availble定时器定时器启动成功,才能进行定时器计数
  6.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  7.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  8.日    期   : 2013年7月15日
    作    者   : z00161729
    修改内容   : DTS2013062406563:WAS连接态OOS,T305运行期间只会在本系统下搜等效plmn，
               不会驻留到本系统其他网络，也不会异系统下进行搜网，导致无法很快在软银网络注册，nas配合修改
  9.日    期   : 2013年12月24日
    作    者   : z00161729
    修改内容   : SVLTE支持NCELL搜网
 10.日    期   : 2013年4月4日
    作    者   : y00176023
    修改内容   : DSDS GUNAS II项目:收到NO RF 迁移到OOC
 11.日    期   : 2014年5月4日
    作    者   : t00173447
    修改内容   : DTS2014042105390,软银定制需求
 12.日    期   : 2014年5月31日
    作    者   : y00245242
    修改内容   : 修改服务状态上报
 13.日    期   : 2015年3月9日
    作    者   : wx270776
    修改内容   : DTS2015031107328, 修改NO_SERVICE上报
 14.日    期   : 2015年6月10日
    作    者   : w00242748
    修改内容   : CDMA Iteration 15 modified
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvAreaLostInd_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList  = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU          stRatSrchList;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRatType;
    NAS_MMC_SEARCHED_TYPE_STRU          stNasSearchedType;

    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstPlmnListInfo = VOS_NULL_PTR;
    RRMM_AREA_LOST_IND_STRU                                *pstAreaLostInd = VOS_NULL_PTR;

    PS_MEM_SET(&stRatSrchList, 0, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));


    pstAreaLostInd = (RRMM_AREA_LOST_IND_STRU*)pstMsg;


    pstPrioRatList = NAS_MML_GetMsPrioRatList();

    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());

    /* Modified by c00318887 for 预置频点搜网优化, 2015-9-9, begin */
    NAS_MMC_SaveLastCampedPlmnWithRat(NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMcc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMnc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.enCampPlmnNetRat);
    /* Modified by c00318887 for 预置频点搜网优化, 2015-9-9, end */

    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);

    NAS_MMC_StopTimer(TI_NAS_MMC_AVAILABLE_TIMER);

    /* 删除NV中的不同国家码的Plmn */
    NAS_MMC_DelDiffMccRplmnInNv_L1Main();

    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* 如果当前为NO RF退出搜网流程 */
    if (VOS_FALSE == NAS_MML_GetRfAvailFlg())
    {
        /* 处理丢网状态，上报服务状态，迁移到ooc，启动available定时器 */
        /* Modified by c00318887 for 预置频点搜网优化, 2015-9-10, begin */
        NAS_MMC_ProcCoverageLost_L1Main(NAS_MMC_PLMN_SEARCH_SCENE_BUTT);
        /* Modified by c00318887 for 预置频点搜网优化, 2015-9-10, end */




        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                            VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        return VOS_TRUE;
    }

    /* Modified by y00245242 for V3R3C60_eCall项目, 2014-5-31, begin */

    /* 向TAF报出服务区流程, GU下向MM/GMM/报丢网 */
    enCurRatType = NAS_MML_GetCurrNetRatType();
    if ( (NAS_MML_NET_RAT_TYPE_GSM == enCurRatType)
      || (NAS_MML_NET_RAT_TYPE_WCDMA == enCurRatType) )
    {
        NAS_MMC_SndMmCoverageLostInd();

        NAS_MMC_SndGmmCoverageLostInd();
    }

    /* 更新服务状态 */
    NAS_MMC_SndMsccCoverageInd( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );

    /* 通知TAF当前的服务状态 */

    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NO_SERVICE);

    /* Modified by y00245242 for V3R3C60_eCall项目, 2014-5-31, end */

    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                            VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);



    pstPlmnListInfo = (NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                         sizeof(NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU) * NAS_MML_MAX_RAT_NUM);

    if (VOS_NULL_PTR == pstPlmnListInfo)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvAreaLostInd_OnPlmn: ALLOC MEM FAIL!");
        return VOS_TRUE;

    }

    PS_MEM_SET(&stNasSearchedType, 0, sizeof(NAS_MMC_SEARCHED_TYPE_STRU));
    stNasSearchedType.ucHistorySearchedFlg  = pstAreaLostInd->stSearchedType.ucHistorySearchedFlg;
    stNasSearchedType.ucPrefBandSearchedFlg = pstAreaLostInd->stSearchedType.ucPrefBandSearchedFlg;
    stNasSearchedType.ucSpecSearchedFlg     = pstAreaLostInd->stSearchedType.ucSpecSearchedFlg;

    if (VOS_TRUE == NAS_MMC_IsNeedEnterOocStatusWhenAreaLost_OnPlmn(&stNasSearchedType))
    {
        NAS_MMC_EnterOocStatus_OnPlmn();

        NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_OOC);

        NAS_MMC_UpdateRegStateSpecPlmnSearch();

        if ( VOS_TRUE == NAS_MMC_StartTimer(TI_NAS_MMC_AVAILABLE_TIMER, NAS_MMC_GetNextAvailableTimerValue()) )
        {
            /* 递增 availble timer当前启动的次数或ncell搜网次数 */
            NAS_MMC_SetAvailableTimerTypebySearchType_OnPlmn();

            /* Added by c00318887 for 预置频点搜网优化, 2015-9-1, begin */
            (VOS_VOID)NAS_MMC_StartPlmnSearchPhaseOneTotalTimer();
            /* Added by c00318887 for 预置频点搜网优化, 2015-9-1, end */
        }
    }
    else
    {
        /*收到丢网指示后，迁移状态NAS_MMC_L1_STA_INITIAL,处理丢网搜网  */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

        if (VOS_TRUE == NAS_MML_IsUsimStausValid())
        {
            NAS_MMC_InitSearchedPlmnListInfo(pstPlmnListInfo);

            /* 根据area lost消息里带的已搜索类型和高低质量plmn更新内部选网消息 */
            NAS_MMC_UpdateSearchedPlmnListInfo(&stNasSearchedType, &(pstAreaLostInd->PlmnIdList), pstPlmnListInfo);

            if(VOS_TRUE == NAS_MMC_IsInterNationalRoamingSearchRPLMN(NAS_MMC_GetLastCampedPlmnid()->ulMcc))
            {
                NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_AREA_LOST_ROAMING_CFG, pstPlmnListInfo, NAS_MML_MAX_RAT_NUM);
            }
            else
            {
                NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_AREA_LOST, pstPlmnListInfo, NAS_MML_MAX_RAT_NUM);
            }

        }
        else
        {
            /* 构造丢网后，需要搜索的接入技术列表 ，Anycell搜网时，需要使用*/
            PS_MEM_CPY(&stRatSrchList, pstPrioRatList, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));
            NAS_MML_SortSpecRatPrioLowest(NAS_MML_GetCurrNetRatType(), &stRatSrchList);

            NAS_MMC_SndInterAnyCellSearchReq(&stRatSrchList, NAS_MMC_ANYCELL_SEARCH_SCENE_BUTT);
        }

    }

    /* 释放内存 */
    PS_MEM_FREE(WUEPS_PID_MMC, pstPlmnListInfo);


    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcMmcSuspendRslt_OnPlmn
 功能描述  : 在ON PLMN时候收到MMCMMC_SUSPEND_RSLT_CNF消息的处理
 输入参数  : ulEventType:MMCMMC_SUSPEND_RSLT_CNF消息类型
             pstMsg: MMCMMC_SUSPEND_RSLT_CNF消息首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE: 函数处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月1日
    作    者   : w00167002
    修改内容   : 新生成函数
  2.日    期   : 2011年07月13日
    作    者   : w00176964
    修改内容   : GUNAS V7R1 PhaseII 阶段调整
  3.日    期   : 2011年11月29日
    作    者   : w00166186
    修改内容   : DTS2011101802330,OOS后出服务区的处理
  4.日    期   : 2011年12月30日
    作    者   : l65478
    修改内容   : 在迁到L模时,不立刻把CS设置成可选搜网,而是等待PS注册结果时
                 根据具体的原因值再设置
  5.日    期   : 2011年12月20日
    作    者   : h44270
    修改内容   : 退出异系统状态机时，通知APS当前所在网络
  6.日    期   : 2013年9月17日
    作    者   : w00242748
    修改内容   : DTS2013091404846 OOS过程中，拨打紧急呼，打断OOS状态机之后，无响应
                 既不搜网也不发起紧急呼
  7.日    期   : 2013年4月8日
    作    者   : y00176023
    修改内容   : DSDS GUNAS II项目:收到NO RF 迁移到OOC状态
  8.日    期   : 2014年1月27日
    作    者   : s00246516
    修改内容   : L-C互操作项目:增加异系统到HRPD的处理

  9.日    期   : 2014年5月4日
    作    者   : t00173447
    修改内容   : DTS2014042105390,软银定制需求

 10.日    期   : 2015年5月30日
    作    者   : l00324781
    修改内容   : CDMA 1X Iteration 12: 增加功能；CL模式下，L2C， lte重选或重定向到hrpd
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmcMmcSuspendRslt_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMCMMC_SUSPEND_RSLT_STRU       *pstSuspendRslt = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU                              stAnycellSrchRatList;
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList = VOS_NULL_PTR;

    /* Modified by s00246516 for L-C互操作项目, 2014-01-27, Begin */
    pstSuspendRslt  = (NAS_MMCMMC_SUSPEND_RSLT_STRU*)pstMsg;

/* 增加((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_LTE))，处理方式和原有的CL相同 */
#if ((FEATURE_ON == FEATURE_CL_INTERWORK) || ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_LTE)))

    /* 重选到HRPD后,MMC状态迁移到DEACT */
    if ((NAS_MML_NET_RAT_TYPE_BUTT == NAS_MML_GetCurrNetRatType())
     && (NAS_MMC_SUSPEND_SUCCESS == pstSuspendRslt->enRslt))
    {
        NAS_MMC_StopAllTimer();

        /* 修改:NAS_MMC_L1_STA_OOC--> NAS_MMC_L1_STA_DEACT
            重选到HRPD，当前LTE处于从模。MMC状态应该切到DEACT */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_DEACT);

        OM_SetDrxTimerWakeSrc(VOS_GetModemIDFromPid(WUEPS_PID_MMC));
        NAS_MMC_SndDrxTimerInfo(VOS_TRUE);

        return VOS_TRUE;
    }
#endif

    pstPrioRatList   = NAS_MML_GetMsPrioRatList();
    PS_MEM_SET(&stAnycellSrchRatList, 0, sizeof(stAnycellSrchRatList));

    NAS_MMC_NotifyModeChange(NAS_MML_GetCurrNetRatType(),
                             NAS_MML_GetSimPsRegStatus());
    /* Modified by s00246516 for L-C互操作项目, 2014-01-27, End */

#if (FEATURE_ON == FEATURE_LTE)

    if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        NAS_MMC_SetCsRegAdditionalAction_L1Main(NAS_MMC_ADDITIONAL_ACTION_BUTT);
    }

#endif

    /* suspend 异系统重选完成 */
    NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMmcMmcSuspendRslt_OnPlmn:SUSPEND COMPLETE");

    /* 根据状态机退出结果 进行相应的处理 */
    if ( (NAS_MMC_SUSPEND_FAIL == pstSuspendRslt->enRslt)
      && (NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST == pstSuspendRslt->enFailCause))
    {

        /* 如果当前存在NO RF，则迁移到OOC状态 */
        if (VOS_FALSE == NAS_MML_GetRfAvailFlg())
        {
            /* 处理丢网状态，上报服务状态，迁移到ooc，启动available定时器 */
            /* Modified by c00318887 for 预置频点搜网优化, 2015-9-10, begin */
            NAS_MMC_ProcCoverageLost_L1Main(NAS_MMC_PLMN_SEARCH_SCENE_BUTT);
            /* Modified by c00318887 for 预置频点搜网优化, 2015-9-10, end */

            return VOS_TRUE;
        }

        /* 迁移状态到INITIAL 状态 */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

        if (MMC_SUSPEND_CAUSE_PLMNSEARCH == pstSuspendRslt->enSuspendCause)
        {
            /* 构造搜网消息 */
            NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_INTER_SYS_OOS, &(pstSuspendRslt->astPlmnSearchInfo[0]), NAS_MML_MAX_RAT_NUM);
        }
        else
        {
            /* 构造搜网消息 */
            if(VOS_TRUE == NAS_MMC_IsInterNationalRoamingSearchRPLMN(NAS_MMC_GetLastCampedPlmnid()->ulMcc))
            {
                NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_AREA_LOST_ROAMING_CFG, &(pstSuspendRslt->astPlmnSearchInfo[0]), NAS_MML_MAX_RAT_NUM);
            }
            else
            {
                NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_AREA_LOST, &(pstSuspendRslt->astPlmnSearchInfo[0]), NAS_MML_MAX_RAT_NUM);
            }

        }
    }

    if ( (VOS_TRUE == NAS_MML_IsExistBufferedEmgCall())
      && (NAS_MMC_SUSPEND_ABORTED == pstSuspendRslt->enRslt))
    {
        /* 迁移到Intial状态  */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

        /* 存在紧急呼叫触发ANYCELL搜网,构造需要anycell搜的接入技术为GU,优先顺序按照syscfg设置 */
        NAS_MMC_BuildCoverageRatPrioListEmgCall_L1Main(pstPrioRatList, &stAnycellSrchRatList);

        NAS_MMC_SndInterAnyCellSearchReq(&stAnycellSrchRatList, NAS_MMC_ANYCELL_SEARCH_SCENE_BUTT);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvUserSpecPlmnSearch_OnPlmn
 功能描述  : ON PLMN状态下收到用户指定搜请求的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月01日
   作    者   : L00171473
   修改内容   : 新生成函数

 2.日    期   : 2011年8月26日
   作    者   : w00176964
   修改内容   : V7R1 PhaseII 调整:临时解决缓存处理中不进预处理中的逻辑

 3.日    期   : 2011年12月20日
   作    者   : w00167002
   修改内容   : DTS2011122001697:在ON PLMN状态，当前指定搜的网络先前驻留的网络
                 相同，当前处在正常服务状态且不在搜网过程中，才不处理用户指定搜网
                 否则在高优先级指定搜网时或者快速指定搜时，被用户指定搜打断，
                 若用户指定的网络和先前驻留的网络相同，高优先级搜网状态机退出后，
                 会不进行用户指定搜。

 4.日    期   : 2011年12月20日
   作    者   : h44270
   修改内容   : 启动搜网状态机时，认为当前无网络
 5.日    期   : 2012年6月6日
   作    者   : l00130025
   修改内容   : DTS2012060604313:单个域注册成功，用户发起对该网络的指定搜网时需要发起搜网注册
 6.日    期   : 2013年3月14日
   作    者   : W00176964
   修改内容   : DTS2013031400138, 产品线新需求:PS业务存在时可以指定搜网
 7.日    期   : 2013年3月30日
   作    者   : l00167671
   修改内容   : 主动上报AT命令控制下移至C核
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvUserSpecPlmnSearch_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMC_PLMN_SPECIAL_REQ_STRU      *pstUserSelReqMsg  = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU               *pstUserSpecPlmnId = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrRatType;
    VOS_UINT32                          ulCsServiceStatusFlg;
    VOS_UINT32                          ulRslt;

    VOS_UINT32                          ulSpecPlmnSearchFlg;

    pstUserSelReqMsg    = (MSCC_MMC_PLMN_SPECIAL_REQ_STRU*)pstMsg;

    /* 指向用户指定搜网消息中的PlmnId */
    pstUserSpecPlmnId   = (NAS_MML_PLMN_ID_STRU*)(&pstUserSelReqMsg->stPlmnId);

    /* 判断用户指定的网络和当前驻留的网络是否相同 */
    ulRslt = NAS_MML_CompareBcchPlmnwithSimPlmn(NAS_MML_GetCurrCampPlmnId(),
                                               pstUserSpecPlmnId);
    enCurrRatType = NAS_MML_GetCurrNetRatType();

    if ( (VOS_TRUE == ulRslt)
     && (pstUserSelReqMsg->enAccessMode == enCurrRatType) )
    {

        /* 当前处在正常服务状态且未进行过搜网，否则在高优先级指定搜网时
           或者快速指定搜时，被用户指定搜打断，若用户指定的网络和先前驻留的
           网络相同，高优先级搜网状态机退出后，会不进行用户指定搜 */
        ulSpecPlmnSearchFlg = NAS_MMC_GetSpecPlmnSearchState();

        if ( (VOS_FALSE == NAS_MMC_NeedTrigPlmnSrch_UserSpecCurrentPlmn())
          && (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING != ulSpecPlmnSearchFlg) )
        {

            /* 更新手动搜网参数 */
            NAS_MMC_UpdateUserSpecPlmnSearchInfo_PreProc(pstUserSpecPlmnId,
                                                              pstUserSelReqMsg->enAccessMode);

            /* 设置当前注册状态为成功 */
            NAS_MMC_SetUserSpecPlmnRegisterStatus(VOS_TRUE);

            /* 向MSCC发送用户指定搜网成功 */
            NAS_MMC_SndMsccUserSpecPlmnSearchCnf(NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_SUCCESS);
            return VOS_TRUE;
        }
    }

    ulCsServiceStatusFlg = NAS_MML_GetCsServiceExistFlg();

    if (VOS_TRUE == ulCsServiceStatusFlg)
    {
        /* 向MSCC发送用户指定搜网失败 */
        NAS_MMC_SndMsccUserSpecPlmnSearchCnf(NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_FAIL);
        return VOS_TRUE;
    }

    NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

    NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_PLMN_SELECTION);

    NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,
                             NAS_MML_GetSimPsRegStatus());

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvUserReselReq_L1Main
 功能描述  : ON PLMN,Initial状态下收到用户自动重选请求的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月15日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2011年7月28日
   作    者   : w00176964
   修改内容   : V7R1 Phase II调整
 3.日    期   : 2012年5月15日
   作    者   : l00130025
   修改内容   : DTS2012012903053:Ts23.122 ch4.4.3.2.1 Auto user reselecton功能支持
 4.日    期   : 2013年4月7日
   作    者   : z00161729
   修改内容   : 主动上报AT命令控制下移至C核及mma和mmc接口调整

 5.日    期   : 2013年6月4日
   作    者   : z00161729
   修改内容   : SVLTE 和usim接口调整修改
 6.日    期   : 2014年2月12日
   作    者   : w00242748
   修改内容   : DTS2014021003925:en_NV_Item_User_Auto_Resel_Switch该NV打开时，CS域
                正常服务，PS域DEREGISTER LIMIT SERVICE状态，下发AT+COPS=0触发搜网，
                搜网过程中，由于未更新服务状态，所以在搜网过程中，下发AT+COPS?查询
                结果仍为正常服务。但在搜网过程中，MMC已将CS/PS注册状态设置成未注册
                需要搜网。

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvUserReselReq_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene;

    /* 当前为自动选网模式 */
    if ( NAS_MMC_PLMN_SELECTION_MODE_AUTO == NAS_MMC_GetPlmnSelectionMode())
    {
        /* 记录搜网场景 */


        if (VOS_TRUE == NAS_MML_GetUserAutoReselActiveFlg())
        {
            enPlmnSearchScene = NAS_MMC_PLMN_SEARCH_SCENE_USER_AUTO_RESEL;
        }
        else
        {
            enPlmnSearchScene = NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED;
        }

    }
    else
    {
        /* 更新选网模式 */
        NAS_MMC_SetPlmnSelectionMode(NAS_MMC_PLMN_SELECTION_MODE_AUTO);

        /* 将当前重选模式写入NVIM中 */
        NAS_MMC_WritePlmnSelectionModeNvim();

        /* 模式改变调用STK相关事件,MMC在调用前判断下，SVLTE形态下，如果没有CS域能力，就不调用*/
        if (VOS_TRUE == NAS_MMC_IsNeedSndStkSearchModeChgEvt())
        {
            NAS_MMC_SndStkSearchModeChgEvt(NAS_MMC_PLMN_SELECTION_MODE_AUTO);
        }

        /* 记录搜网场景 */

        if (VOS_TRUE == NAS_MML_GetUserAutoReselActiveFlg())
        {
            enPlmnSearchScene = NAS_MMC_PLMN_SEARCH_SCENE_USER_AUTO_RESEL;
        }
        else
        {
            enPlmnSearchScene = NAS_MMC_PLMN_SEARCH_SCENE_MANUAL_CHANGE_AUTO_MODE;
        }

    }

    /* 无业务时发起搜网 */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

    NAS_MMC_SndInterPlmnSearchReq(enPlmnSearchScene,VOS_NULL_PTR, 0);

    if ( VOS_TRUE == NAS_MMC_IsNormalServiceStatus() )
    {
        NAS_MMC_SetCsServiceStatus(NAS_MMC_LIMITED_SERVICE);
        NAS_MMC_SetPsServiceStatus(NAS_MMC_LIMITED_SERVICE);

        NAS_MMC_SndMsccServiceStatusInd(NAS_MSCC_PIF_SRVDOMAIN_NOT_REG_PLMN_SEARCHING, NAS_MSCC_PIF_SERVICE_STATUS_LIMITED_SERVICE);
        NAS_MMC_UpdateRegStateSpecPlmnSearch();
    }

    /* 返回设置成功 */
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, begin */
    NAS_MMC_SndMsccPlmnReselCnf(NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_SUCCESS);
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, end */

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvPsRegResultInd_OnPlmn
 功能描述  : ON PLMN时收到PS域注册结果的消息
 输入参数  : ulEventType:消息类型
             pstMsg: GMMMMC_PS_REG_RESULT_IND消息首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE: 函数处理消息成功
 调用函数  :
 被调函数  :

 修改历史    :
 1.日    期   : 2011年7月19日
   作    者   : h44270
   修改内容   : 新生成函数

 2.日    期   : 2011年7月28日
   作    者   : w00176964
   修改内容   : V7R1 Phase II调整

 3.日    期   : 2011年9月20日
   作    者   : w00176964
   修改内容   : V7R1 Phase II 内部LIST搜网调整

 4.日    期   : 2011年9月25日
   作    者   : z00161729
   修改内容   : V7R1 Phase II 高优先级搜网调整

 5.日    期   : 2011年10月22日
   作    者   : w00167002
   修改内容   : V7R1 Phase II-2 增加HPLMN TIMER的事件上报

 6.日    期   : 2011年11月20日
   作    者   : l00130025
   修改内容   : 问题单号:DTS2111111507462,假流程，单个域注册成功，时错误地停止了AvailTimer

 7.日    期   : 2013年10月17日
   作    者   : l65478
   修改内容   : DTS2013102103487:DT需求:在单域失败时也需要发起搜网
 8.日    期   : 2013年12月25日
   作    者   : z00161729
   修改内容   : SVLTE支持NCELL搜网
                  快速找回TL，所以应尽量让其快速找回。
 9.日    期   : 2014年2月24日
   作    者   : w00176964
   修改内容   : High_Rat_Hplmn_Search特性调整:增加High_Prio_rat_hplmn定时器的启动处理
10.日    期   : 2014年10月27日
   作    者   : b00269685
   修改内容   : 增加High_Prio_rat_hplmn TD Count的处理
11.日    期   : 2015年6月6日
   作    者   : s00217060
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0修改
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvPsRegResultInd_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    GMMMMC_PS_REG_RESULT_IND_STRU      *pstPsRegRslt = VOS_NULL_PTR;
    VOS_UINT32                          ulRrcConnExistFlag;

    pstPsRegRslt = (GMMMMC_PS_REG_RESULT_IND_STRU*)pstMsg;

    /* ON PLMN下如果发生重选，切换以及CCO，可能网络会发生改变，
       如果ON PLMN下收到缓存的注册结果消息，需要判断当前网络是
       否发生改变，发生改变则丢弃当前注册结果 */
    if ( pstPsRegRslt->enNetType != NAS_MML_GetCurrNetRatType())
    {
        return VOS_TRUE;
    }

    NAS_MMC_ProcPsRegRslt_L1Main(pstPsRegRslt);

    NAS_MMC_LogFsmL1MainCtxRelatedInfo(NAS_MMC_GetL1MainCtx_L1Main());

    /* 不需要搜网直接返回 */
    if (VOS_FALSE == NAS_MMC_IsPlmnSearchNeeded_L1Main())
    {
        /* ON PLMN时收到PS域注册结果后续不需搜网，需要判断是否需要启动HPLMN定时器 */
        if (VOS_TRUE == NAS_MMC_IsNeedStartHPlmnTimer())
        {
            /* 启动定时器 */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_HPLMN_TIMER, NAS_MMC_GetHplmnTimerLen());


            /* HPLMN TIMER启动事件上报 */
            NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_HPLMN_TIMER_START,
                            VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);


            /* 将HPLMN启动类型设置为非首次启动 */
            NAS_MMC_SetFirstStartHPlmnTimerFlg(VOS_FALSE);

        }

        if (VOS_TRUE == NAS_MMC_IsNeedStartHighPrioRatHPlmnTimer())
        {
            /* 启动定时器 */
            if (VOS_TRUE == NAS_MMC_StartTimer(TI_NAS_MMC_HIGH_PRIO_RAT_HPLMN_TIMER, NAS_MMC_GetHighPrioRatHplmnTimerLen()))
            {
                NAS_MMC_AddCurHighPrioRatHplmnTimerFirstSearchCount_L1Main();
                NAS_MMC_UpdateHighPrioRatHPlmnTimerTdCount();
            }
        }


        /* 单域注册失败原因值为other cause需要发起搜网特性打开时,当CS域注册失败时不能停止定时器 */
        /* 正常服务则停止available定时器 */
        if ( VOS_TRUE == NAS_MMC_IsPsNormalService())
        {
            if (VOS_FALSE == NAS_MMC_IsSingleDomainRegFailNeedPlmnSrch(NAS_MSCC_PIF_SRVDOMAIN_CS))
            {
                NAS_MMC_ResetOosPlmnSearchTimerCount_OnPlmn();

                NAS_MMC_StopTimer(TI_NAS_MMC_AVAILABLE_TIMER);

                /* Added by c00318887 for 预置频点搜网优化, 2015-9-1, begin */
                NAS_MMC_StopTimer(TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER);
                /* Added by c00318887 for 预置频点搜网优化, 2015-9-1, end */

            }
        }


        return VOS_TRUE;
    }

    /* 判断是否可以进行内部LIST搜网 */
    if ( VOS_TRUE == NAS_MMC_IsGURegFailTriggerInterPlmnList_L1Main())
    {
        NAS_MMC_SndInterPlmnListReq();

        /* 触发搜网后就清除additional的值 */
        NAS_MMC_ClearAllRegAdditionalAction_L1Main();

        /* 触发搜网后同时清除CS/PS的注册尝试次数 */
        NAS_MMC_ClearAllRegAttemptCount_L1Main();

        return VOS_TRUE;
    }

    /* 判断信令链接是否已经完成释放 */
    ulRrcConnExistFlag  = NAS_MML_IsRrcConnExist();

    if ( VOS_TRUE == ulRrcConnExistFlag )
    {
        /* 信令链接未释放完成，继续等待信令链接释放消息 */
        return VOS_TRUE;
    }

    /* 发起搜网 */
    (VOS_VOID)NAS_MMC_PerformPlmnSearch_L1Main();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvCsRegResultInd_OnPlmn
 功能描述  : ON PLMN时收到CS域注册结果的消息
 输入参数  : ulEventType:消息类型
              pstMsg: MMMMC_CS_REG_RESULT_IND消息首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE: 函数处理消息成功
 调用函数  :
 被调函数  :

 修改历史    :
 1.日    期   : 2011年7月19日
   作    者   : h44270
   修改内容   : 新生成函数

 2.日    期   : 2011年7月28日
   作    者   : w00176964
   修改内容   : V7R1 Phase II调整

 3.日    期   : 2011年9月20日
   作    者   : w00176964
   修改内容   : V7R1 Phase II 内部LIST搜网调整

 4.日    期   : 2011年10月22日
   作    者   : w00167002
   修改内容   : V7R1 Phase II-2 增加HPLMN TIMER的事件上报

 5.日    期   : 2011年11月20日
   作    者   : l00130025
   修改内容   : 问题单号:DTS2111111507462,假流程，单个域注册成功，时错误地停止了AvailTimer
 6.日    期   : 2013年10月17日
   作    者   : l65478
   修改内容   : DTS2013102103487:DT需求:在单域失败时也需要发起搜网
 7.日    期   : 2013年12月25日
   作    者   : z00161729
   修改内容   : SVLTE支持NCELL搜网
                  快速找回TL，所以应尽量让其快速找回。
 8.日    期   : 2014年2月24日
   作    者   : w00176964
   修改内容   : High_Rat_Hplmn_Search特性调整:增加High_Prio_rat_hplmn定时器的启动处理
 9.日    期   : 2014年10月27日
   作    者   : b00269685
   修改内容   : 增加High_Prio_rat_hplmn TD Count的处理
10.日    期   : 2015年5月26日
   作    者   : w00167002
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0项目修改
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvCsRegResultInd_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
)
{
    MMMMC_CS_REG_RESULT_IND_STRU       *pstCsRegRslt = VOS_NULL_PTR;
    VOS_UINT32                          ulRrcConnExistFlag;

    pstCsRegRslt = (MMMMC_CS_REG_RESULT_IND_STRU*)pstMsg;

    /* ON PLMN下如果发生重选，切换以及CCO，可能网络会发生改变，
       如果ON PLMN下收到缓存的注册结果消息，需要判断当前网络是
       否发生改变，发生改变则丢弃当前注册结果 */
    if ( pstCsRegRslt->enNetType != NAS_MML_GetCurrNetRatType())
    {
        return VOS_FALSE;
    }

    NAS_MMC_ProcCsRegRslt_L1Main(pstCsRegRslt);

    NAS_MMC_LogFsmL1MainCtxRelatedInfo(NAS_MMC_GetL1MainCtx_L1Main());

    /* 不需要搜网直接返回 */
    if (VOS_FALSE == NAS_MMC_IsPlmnSearchNeeded_L1Main())
    {
        /* ON PLMN时收到CS域注册结果后续不需搜网，需要判断是否需要启动HPLMN定时器 */
        if (VOS_TRUE == NAS_MMC_IsNeedStartHPlmnTimer())
        {
            /* 启动定时器 */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_HPLMN_TIMER, NAS_MMC_GetHplmnTimerLen());


            /* HPLMN TIMER启动事件上报 */
            NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_HPLMN_TIMER_START,
                            VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);


            /* 将HPLMN启动类型设置为非首次启动 */
            NAS_MMC_SetFirstStartHPlmnTimerFlg(VOS_FALSE);
        }

        if (VOS_TRUE == NAS_MMC_IsNeedStartHighPrioRatHPlmnTimer())
        {
            /* 启动定时器 */
            if (VOS_TRUE == NAS_MMC_StartTimer(TI_NAS_MMC_HIGH_PRIO_RAT_HPLMN_TIMER, NAS_MMC_GetHighPrioRatHplmnTimerLen()))
            {
                NAS_MMC_AddCurHighPrioRatHplmnTimerFirstSearchCount_L1Main();
                NAS_MMC_UpdateHighPrioRatHPlmnTimerTdCount();
            }
        }


        /* 正常服务则停止available定时器 */
        if ( VOS_TRUE == NAS_MMC_IsCsNormalService())
        {
            /* 单域注册失败原因值为network fail需要发起搜网特性打开时,当CS域注册失败时不能停止定时器 */
            if (VOS_FALSE == NAS_MMC_IsSingleDomainRegFailNeedPlmnSrch(NAS_MSCC_PIF_SRVDOMAIN_PS))
            {
                NAS_MMC_ResetOosPlmnSearchTimerCount_OnPlmn();

                NAS_MMC_StopTimer(TI_NAS_MMC_AVAILABLE_TIMER);

                /* Added by c00318887 for 预置频点搜网优化, 2015-9-1, begin */
                NAS_MMC_StopTimer(TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER);
                /* Added by c00318887 for 预置频点搜网优化, 2015-9-1, end */

            }
        }

        return VOS_TRUE;
    }

    /* 判断是否可以进行内部LIST搜网 */
    if ( VOS_TRUE == NAS_MMC_IsGURegFailTriggerInterPlmnList_L1Main())
    {
        NAS_MMC_SndInterPlmnListReq();

        /* 触发搜网后就清除additional的值 */
        NAS_MMC_ClearAllRegAdditionalAction_L1Main();

        /* 触发搜网后同时清除CS/PS的注册尝试次数 */
        NAS_MMC_ClearAllRegAttemptCount_L1Main();

        return VOS_TRUE;
    }

    /* 判断信令链接是否已经完成释放 */
    ulRrcConnExistFlag  = NAS_MML_IsRrcConnExist();

    if ( VOS_TRUE == ulRrcConnExistFlag )
    {
        /* 信令链接未释放完成，继续等待信令链接释放消息 */
        return VOS_TRUE;
    }

    /* 发起搜网 */
    (VOS_VOID)NAS_MMC_PerformPlmnSearch_L1Main();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmAbortInd_OnPlmn
 功能描述  : On Plmn过程中收到MM Abort消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年7月12日
   作    者   : s00217060
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmAbortInd_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMMMC_ABORT_IND_STRU               *pstMmAbortInd   = VOS_NULL_PTR;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_GU_ACTION_RSLT_INFO_STRU    stGuActionRslt;
#endif

    pstMmAbortInd = (MMMMC_ABORT_IND_STRU*)pstMsg;

    /* 如果原因值不为#6，且不为#17，直接返回 */
    if ((NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME != pstMmAbortInd->enAbortCause)
     && (NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE != pstMmAbortInd->enAbortCause))
    {
        return VOS_TRUE;
    }

    /* 如果原因值#6，设置CS Addition为Anycell驻留 */
    if (NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME == pstMmAbortInd->enAbortCause)
    {
        NAS_MMC_SetCsRegAdditionalAction_L1Main(NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL);
    }

#if (FEATURE_ON == FEATURE_LTE)

    /* 给LMM发送ID_MMC_LMM_ACTION_RESULT_REQ */
    /* 构造ActionRslt消息，结果为CN_Rej,类型填为新增NAS_MML_PROC_MM_ABORT类型
       请求和结果域都是CS，原因值为Abort带的原因值 */
    stGuActionRslt.enProcType     = NAS_MML_PROC_MM_ABORT;
    stGuActionRslt.enRegRst       = NAS_MML_REG_RESULT_CN_REJ;
    stGuActionRslt.enReqDomain    = NAS_MMC_REG_DOMAIN_CS;
    stGuActionRslt.enRstDomain    = NAS_MMC_REG_DOMAIN_CS;
    stGuActionRslt.enCnCause      = pstMmAbortInd->enAbortCause;
    stGuActionRslt.ulAttemptCount = 0x0;

    NAS_MMC_SndLmmRegActionResultReq(&stGuActionRslt);
#endif

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGmmServiceRequestResultInd_OnPlmn
 功能描述  : ON PLMN时收到PS域SR结果的消息
 输入参数  : ulEventType:消息类型
             pstMsg: GMMMMC_SERVICE_REQUEST_RESULT_IND消息首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE: 函数处理消息成功
 调用函数  :
 被调函数  :

 修改历史    :
 1.日    期   : 2011年8月11日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2013年12月25日
   作    者   : z00161729
   修改内容   : SVLTE支持NCELL搜网
 3.日    期   : 2015年6月6日
   作    者   : s00217060
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0修改
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvGmmServiceRequestResultInd_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
)
{
    GMMMMC_SERVICE_REQUEST_RESULT_IND_STRU                 *pstSrRsltInd = VOS_NULL_PTR;
    VOS_UINT32                                              ulRrcConnExistFlag;

    pstSrRsltInd = (GMMMMC_SERVICE_REQUEST_RESULT_IND_STRU*)pstMsg;

    /* 处理SR的结果消息 */
    NAS_MMC_ProcGmmServiceRequestResultInd_L1Main(pstSrRsltInd);

    /* 不需要搜网直接返回 */
    if (VOS_FALSE == NAS_MMC_IsPlmnSearchNeeded_L1Main())
    {
        /* 正常服务则停止available定时器 */
        if ( VOS_TRUE == NAS_MMC_IsNormalServiceStatus())
        {
            NAS_MMC_ResetOosPlmnSearchTimerCount_OnPlmn();

            NAS_MMC_StopTimer(TI_NAS_MMC_AVAILABLE_TIMER);

            /* Added by c00318887 for 预置频点搜网优化, 2015-9-1, begin */
            NAS_MMC_StopTimer(TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER);
            /* Added by c00318887 for 预置频点搜网优化, 2015-9-1, end */

        }

        return VOS_TRUE;
    }

    /* 判断信令链接是否已经完成释放 */
    ulRrcConnExistFlag  = NAS_MML_IsRrcConnExist();

    if ( VOS_TRUE == ulRrcConnExistFlag )
    {
        /* 信令链接未释放完成，继续等待信令链接释放消息 */
        return VOS_TRUE;
    }

    /* 发起搜网 */
    (VOS_VOID)NAS_MMC_PerformPlmnSearch_L1Main();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvCustomizedForbLaTimerExpired_OnPlmn
 功能描述  : 处理CUSTOMIZED_FORBLA_TIMER消息
 输入参数  : ulEventType:消息类型
             pstMsg:当前处理的消息
 输出参数  : 无
 返 回 值  : VOS_TRUE:函数处理完成
             VOS_FALSE:函数处理未完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年10月12日
   作    者   : z00359541
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvCustomizedForbLaTimerExpired_OnPlmn(
    VOS_UINT32                                              ulEventType,
    struct MsgCB                                           *pstMsg
)
{
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_LIST_STRU            *pstForbLaWithValidPeriod    = VOS_NULL_PTR;
    VOS_UINT32                                              ulTriggerPlmnSearchFlg;

    NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvCustomizedForbLaTimerExpired_OnPlmn");

    pstForbLaWithValidPeriod            = NAS_MML_GetForbLaWithValidPeriodList();
    ulTriggerPlmnSearchFlg              = NAS_MML_IsNeedTriggerPlmnSearchWhenRemoveCustomizedFrobLa();

    if (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == NAS_MMC_GetPlmnSelectionMode())
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvCustomizedForbLaTimerExpired_OnPlmn: Manual PLMN Sel Mode");
        (VOS_VOID)NAS_MML_DeleteExpiredLaFromForbLaWithValidPeriodList(pstForbLaWithValidPeriod);

        /* 启动定时器 */
        NAS_MML_StartCustomizedForbLaTimer();

        return VOS_TRUE;
    }

    /* 定制禁止LA列表有变化 */
    if (VOS_TRUE == NAS_MML_DeleteExpiredLaFromForbLaWithValidPeriodList(pstForbLaWithValidPeriod))
    {
        /* 判断删除LAI后，是否需要发起搜网 */
        if ((VOS_TRUE == NAS_MML_IsCurrGURatMode())
         && (VOS_TRUE == ulTriggerPlmnSearchFlg))
        {

            NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvCustomizedForbLaTimerExpired_OnPlmn: Snd Inter PLMN Search Req");
            /* 发生内部搜网消息为定时器超时 */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

            /* 构造搜网消息 */
            NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED, VOS_NULL_PTR, 0);
        }
        else
        {
            /* 通知接入层，CUSTOMIZED FORB LA发生变化 */
            NAS_MMC_SndRrMmCellSelReq(RRC_NAS_FORBLA_CHANGE);
        }
    }

    /* 启动定时器 */
    NAS_MML_StartCustomizedForbLaTimer();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvForbLaTimerExpired_OnPlmn
 功能描述  : 处理MMC_FORBLA_TIMER消息
 输入参数  : ulEventType:消息类型
             pstMsg:当前处理的消息
 输出参数  : 无
 返 回 值  : VOS_TRUE:函数预处理完成
             VOS_FALSE:函数预处理未完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2010年11月29日
   作    者   : zhoujun /40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvForbLaTimerExpired_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampPlmnInfo     = VOS_NULL_PTR;
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU   *pstForbidPlmnInfo   = VOS_NULL_PTR;
    VOS_UINT32                          ulLaiValidFlg;
    VOS_UINT32                          ulRlstLaiInForbidRegLaiList;
    ulLaiValidFlg       = VOS_TRUE;

    /* 获取FPLMN信息*/
    pstForbidPlmnInfo   = NAS_MML_GetForbidPlmnInfo();

    /* 获取当前驻留PLMN信息 */
    pstCampPlmnInfo     = NAS_MML_GetCurrCampPlmnInfo();

    ulRlstLaiInForbidRegLaiList = NAS_MML_IsLaiInDestLaiList(&(pstCampPlmnInfo->stLai),
        pstForbidPlmnInfo->ucForbRegLaNum, pstForbidPlmnInfo->astForbRegLaList);

    if (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == NAS_MMC_GetPlmnSelectionMode())
    {
        pstForbidPlmnInfo->ucForbRegLaNum    = 0;
        pstForbidPlmnInfo->ucForbRoamLaNum   = 0;
        return VOS_TRUE;
    }

    /* 驻留PLMN在禁止FPLMN列表中 */
    if (VOS_TRUE == NAS_MML_IsPlmnIdInForbidPlmnList(&(pstCampPlmnInfo->stLai.stPlmnId)))
    {
        ulLaiValidFlg =  VOS_FALSE;
    }

    /* 驻留的LAI在禁止LAI列表中 */
    if ((VOS_TRUE == NAS_MML_IsLaiInDestLaiList(&(pstCampPlmnInfo->stLai),
            pstForbidPlmnInfo->ucForbRoamLaNum, pstForbidPlmnInfo->astForbRomLaList)) ||
        (VOS_TRUE == ulRlstLaiInForbidRegLaiList))
    {
        ulLaiValidFlg =  VOS_FALSE;
    }

    pstForbidPlmnInfo->ucForbRegLaNum    = 0;
    pstForbidPlmnInfo->ucForbRoamLaNum   = 0;

    switch ( NAS_MML_GetCurrNetRatType())
    {
#if (FEATURE_ON == FEATURE_LTE)
    case NAS_MML_NET_RAT_TYPE_LTE:
        /* L模需要对ForbTAI处理，目前由L完成 */
        return VOS_TRUE;
#endif
    case NAS_MML_NET_RAT_TYPE_WCDMA:
    case NAS_MML_NET_RAT_TYPE_GSM:

        break;

    default:
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvForbLaTimerExpired_L1Main:Net RAT ERROR! ");
        return VOS_TRUE;
    }

    /* 当前位置处于Forb LA中时，删除后，需要发起搜网，做一次注册 */
    if ( VOS_FALSE == ulLaiValidFlg )
    {
        /* 发生内部搜网消息为定时器超时 */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

        /* 构造搜网消息 */
        NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED, VOS_NULL_PTR, 0);
    }
    else
    {
        /* 通知接入层，当前ForbLa无效 */
        NAS_MMC_SndRrMmCellSelReq(RRC_NAS_FORBLA_CHANGE);
    }

    return VOS_TRUE;

}

#if   (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmDetachCnf_L1Main
 功能描述  : MMC收到LMM DETACH CNF的处理
 输入参数  : ulEventType - 消息类型
             pstMsg      - 消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:函数预处理完成
             VOS_FALSE:函数预处理未完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月19日
   作    者   : 王毛/00166186
   修改内容   : 新生成函数
 2.日    期   : 2011年8月11日
   作    者   : W00167002
   修改内容   : 修改为调用detach函数
 3.日    期   : 2011年10月26日
   作    者   : w00176964
   修改内容   : V7R1 Phase III调整:联合注册修改
 4.日    期   : 2012年5月15日
   作    者   : w00176964
   修改内容   : GUL BG项目调整
 5.日    期   : 2014年4月24日
   作    者   : w00242748
   修改内容   : DTS2014042405819:无卡状态下，紧急呼被拒#5，后发起ANYCELL搜，导致退状态机
                后下发RRMM_UE_OOC_STATUS_NOTIFY_IND，导致网络不断下发CM SERVICE REJ
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmDetachCnf_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_DETACH_CNF_STRU            *pstLmmDetachCnf     = VOS_NULL_PTR;

    pstLmmDetachCnf = (LMM_MMC_DETACH_CNF_STRU*)pstMsg;

    switch (pstLmmDetachCnf->ulDetachRslt)
    {
        case MMC_LMM_DETACH_RSLT_AUTH_REJ:

            /* 存在链接的时候，已经在与处理处理完，进状态机后不会有链接存在 */
            /* 迁移到Initial状态 */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

            /* 根据结果中的接入技术覆盖信息启动anycell状态机，优先搜索当前接入技术 */
            NAS_MMC_SndInterAnyCellSearchReq(VOS_NULL_PTR, NAS_MMC_ANYCELL_SEARCH_SCENE_BUTT);

            break;

        case MMC_LMM_DETACH_RSLT_ACCESS_BARED:
        case MMC_LMM_DETACH_RSLT_FAILURE:
        case MMC_LMM_DETACH_RSLT_SUCCESS:

            NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

            /* 发起内部搜网 */
            NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_DISABLE_LTE, VOS_NULL_PTR, 0);

            break;

        default:

            /* 异常打印 */
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmDetachCnf_L1Main:Unexpected detach result!");

            break;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLSysInfoInd_OnPlmn
 功能描述  : 在空闲态时候收到ID_LMM_MMC_SYS_INFO_IND消息的处理
 输入参数  : ulEventType:ID_LMM_MMC_SYS_INFO_IND消息长度
             pstMsg: ID_LMM_MMC_SYS_INFO_IND消息
 输出参数  : 无
 返 回 值  : VOS_TRUE: 函数处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月1日
    作    者   : w00167002
    修改内容   : 新生成函数
  2.日    期   : 2011年7月28日
    作    者   : w00176964
    修改内容   : V7R1 Phase II调整
  3.日    期   : 2011年10月20日
    作    者   : w00167002
    修改内容   : V7R1 Phase II ST: 删除代码NAS_MMC_SetPsRegAdditionalAction_L1Main(NAS_MMC_ADDITIONAL_ACTION_BUTT);
  4.日    期   : 2011年11月2日
    作    者   : w00167002
    修改内容   : V7R1 Phase II ST: 删除代码NAS_MMC_SetCsRegAdditionalAction_L1Main(NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION);
                 修改原因:在L模下高优先级搜网注册被拒原因值6，导致卡无效，
                 需要进行ANYCELL搜网，ANYCELL搜网后受到L模的系统消息后，CS域被设置为
                 NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION后，收到MM的链接
                 不存在指示消息后，则会立即触发ANYCELL搜网。
  5.日    期   : 2012年4月18日
    作    者   : l00130025
    修改内容   : DTS2012040200480,单独维护EPS注册状态,供L模下CEREG/CGREG查询和上报使用
  6.日    期   : 2012年4月28日
    作    者   : W00166186
    修改内容   : DTS2012042602593,MM没有保存当前驻留的PLMN，导致后续判断出错
  7.日    期   : 2012年11月29日
    作    者   : w00176964
    修改内容   : DTS2012042804167:通知CBA模块当前接入模式为LTE
  8.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  9.日    期   : 2012年12月20日
    作    者   : w00176964
    修改内容   : DTS2012121906946:收到L的系统消息转发给LMM
 10.日    期   : 2013年1月19日
    作    者   : t00212959
    修改内容   : DTS2012122900189:EPS注册状态完全由L上报
 11.日    期   : 2015年02月11日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseII 项目修改
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLSysInfoInd_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    /* 更新驻留状态 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

    /* 保留老的驻留网络信息 */
    pstCurCampInfo  = NAS_MML_GetCurrCampPlmnInfo();
    PS_MEM_CPY(&stOldCampInfo, pstCurCampInfo, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

    /* 根据系统消息，更新MML的全部变量 */
    NAS_MMC_UpdateNetworkInfo_LmmSysInfo(pstMsg);
    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_STOP);



    /* CBS上报*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_LTE);

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, end */
    /*方案优化后，LTE下的小区发生变化，LMM会通过系统消息通知MMC*/
    /* 驻留小区变化时*/
    if (VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
    {
        /* 主动上报 */
        NAS_MMC_SndMsccSysInfo();

    }


    /* 转发GMM系统消息,供rabm使用 */
    NAS_MMC_SndGmmLteSysinfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);
    NAS_MMC_SndMmLteSysinfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);

    NAS_MMC_SndLmmLteSysInfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmAreaLostInd_OnPlmn
 功能描述  : ON PLMN状态收到LMM的ID_LMM_MMC_AREA_LOST_IND的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月21日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2015年12月15日
    作    者   : w00176964
    修改内容   : CL_MUTIMODE_OPTIMIZE调整
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmAreaLostInd_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_SEARCHED_TYPE_STRU                              stNasSearchedType;
    NAS_MML_PLMN_RAT_PRIO_STRU                              stRatSrchList;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstPlmnListInfo = VOS_NULL_PTR;
    LMM_MMC_AREA_LOST_IND_STRU                             *pstAreaLostInd  = VOS_NULL_PTR;
    RRC_PLMN_ID_LIST_STRU                                  *pstGuPlmnIdList = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList  = VOS_NULL_PTR;

    pstAreaLostInd  = (LMM_MMC_AREA_LOST_IND_STRU*)pstMsg;
    pstPrioRatList  = NAS_MML_GetMsPrioRatList();
    pstGuPlmnIdList = (RRC_PLMN_ID_LIST_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                   sizeof(RRC_PLMN_ID_LIST_STRU));

    if (VOS_NULL_PTR == pstGuPlmnIdList)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmAreaLostInd_OnPlmn:ERROR: Memory Alloc Error");
        return VOS_TRUE;
    }

    /* RSSI初始化 */
    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());

    /* 驻留信息和驻留状态更新 */
    NAS_MMC_SaveLastCampedPlmnWithRat(NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMcc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMnc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.enCampPlmnNetRat);

    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);

    NAS_MMC_StopTimer(TI_NAS_MMC_AVAILABLE_TIMER);

    /* 删除NV中的不同国家码的Plmn */
    NAS_MMC_DelDiffMccRplmnInNv_L1Main();

    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* 如果当前为NO RF退出搜网流程 */
    if (VOS_FALSE == NAS_MML_GetRfAvailFlg())
    {
        /* 处理丢网状态，上报服务状态，迁移到ooc，启动available定时器 */
        NAS_MMC_ProcCoverageLost_L1Main(NAS_MMC_PLMN_SEARCH_SCENE_BUTT);

        /* CL模式下L单模注册失败立即搜DO */
        if (VOS_FALSE == NAS_MML_IsGULModeConfigured())
        {
            NAS_MMC_SndMsccMmssLteUnAvailableInd(MSCC_MMC_MMSS_LTE_UNAVIALBLE_REASON_NO_RF);
        }

        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                            VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        PS_MEM_FREE(WUEPS_PID_MMC, pstGuPlmnIdList);

        return VOS_TRUE;
    }

    /* 更新服务状态 */
    NAS_MMC_SndMsccCoverageInd( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );

    /* 通知TAF当前的服务状态 */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NO_SERVICE);


    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                            VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);



    pstPlmnListInfo = (NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                         sizeof(NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU) * NAS_MML_MAX_RAT_NUM);

    if (VOS_NULL_PTR == pstPlmnListInfo)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmAreaLostInd_OnPlmn: ALLOC MEM FAIL!");

        PS_MEM_FREE(WUEPS_PID_MMC, pstGuPlmnIdList);

        return VOS_TRUE;

    }



    PS_MEM_SET(&stNasSearchedType, 0, sizeof(NAS_MMC_SEARCHED_TYPE_STRU));
    stNasSearchedType.ucHistorySearchedFlg  = pstAreaLostInd->stSearchedType.ucHistorySearchedFlg;
    stNasSearchedType.ucPrefBandSearchedFlg = pstAreaLostInd->stSearchedType.ucPrefBandSearchedFlg;
    stNasSearchedType.ucSpecSearchedFlg     = pstAreaLostInd->stSearchedType.ucSpecSearchedFlg;

    /* 根据AS/LRRC已搜索过的情况判断是否要立即进入OOC状态 */
    if (VOS_TRUE == NAS_MMC_IsNeedEnterOocStatusWhenAreaLost_OnPlmn(&stNasSearchedType))
    {
        NAS_MMC_EnterOocStatus_OnPlmn();

        NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_OOC);

        NAS_MMC_UpdateRegStateSpecPlmnSearch();

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        /* CL模式下L单模注册失败立即搜DO */
        if (VOS_FALSE == NAS_MML_IsGULModeConfigured())
        {
            NAS_MMC_SndMsccMmssLteUnAvailableInd(MSCC_MMC_MMSS_LTE_UNAVIALBLE_REASON_AREA_LOST);

            /* 释放内存 */
            PS_MEM_FREE(WUEPS_PID_MMC, pstPlmnListInfo);

            PS_MEM_FREE(WUEPS_PID_MMC, pstGuPlmnIdList);

            return VOS_TRUE;
        }
#endif

        if ( VOS_TRUE == NAS_MMC_StartTimer(TI_NAS_MMC_AVAILABLE_TIMER, NAS_MMC_GetNextAvailableTimerValue()) )
        {
            /* 递增 availble timer当前启动的次数或ncell搜网次数 */
            NAS_MMC_SetAvailableTimerTypebySearchType_OnPlmn();

            (VOS_VOID)NAS_MMC_StartPlmnSearchPhaseOneTotalTimer();
        }
    }
    else
    {
        /*收到丢网指示后，迁移状态NAS_MMC_L1_STA_INITIAL,处理丢网搜网  */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

        if (VOS_TRUE == NAS_MML_IsUsimStausValid())
        {
            NAS_MMC_InitSearchedPlmnListInfo(pstPlmnListInfo);

            /* 将搜网消息中携带的网络信息转换为内部消息中网络信息 */
            NAS_MMC_ConvertLmmPlmnIdListToGUFormat(&(pstAreaLostInd->stPlmnIdList),
                                                   pstGuPlmnIdList);

            /* 根据area lost消息里带的已搜索类型和高低质量plmn更新内部选网消息 */
            NAS_MMC_UpdateSearchedPlmnListInfo(&stNasSearchedType, pstGuPlmnIdList, pstPlmnListInfo);

            /* LMM的搜网类型转换成NAS的搜网类型 */
            if(VOS_TRUE == NAS_MMC_IsInterNationalRoamingSearchRPLMN(NAS_MMC_GetLastCampedPlmnid()->ulMcc))
            {
                NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_AREA_LOST_ROAMING_CFG, pstPlmnListInfo, NAS_MML_MAX_RAT_NUM);
            }
            else
            {
                NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_AREA_LOST, pstPlmnListInfo, NAS_MML_MAX_RAT_NUM);
            }
        }
        else
        {
            /* 构造丢网后，需要搜索的接入技术列表 ，Anycell搜网时，需要使用*/
            PS_MEM_SET(&stRatSrchList, 0, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));
            PS_MEM_CPY(&stRatSrchList, pstPrioRatList, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));
            NAS_MML_SortSpecRatPrioLowest(NAS_MML_GetCurrNetRatType(), &stRatSrchList);

            NAS_MMC_SndInterAnyCellSearchReq(&stRatSrchList, NAS_MMC_ANYCELL_SEARCH_SCENE_BUTT);
        }

    }

    /* 释放内存 */
    PS_MEM_FREE(WUEPS_PID_MMC, pstPlmnListInfo);

    PS_MEM_FREE(WUEPS_PID_MMC, pstGuPlmnIdList);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmMmcStatusInd_OnPlmn
 功能描述  : 在ON PLMN时候收到ID_LMM_MMC_STATUS_IND消息的处理
 输入参数  : ulEventType:ID_LMM_MMC_STATUS_IND消息长度
             pstMsg: ID_LMM_MMC_STATUS_IND消息
 输出参数  : 无
 返 回 值  : VOS_TRUE: 函数处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月1日
    作    者   : w00167002
    修改内容   : 新生成函数
  2.日    期   : 2011年7月28日
    作    者   : w00176964
    修改内容   : V7R1 Phase II调整
  3.日    期   : 2011年12月8日
    作    者   : w00176964
    修改内容   : V7R1 Phase IV调整:缓存搜网的处理
  4.日    期   : 2012年5月24日
    作    者   : w00176964
    修改内容   : GUL BG项目调整:处理缓存的指定搜网时先判断下是否已经正常服务了
  5.日    期   : 2015年9月16日
    作    者   : y00346957
    修改内容   : DTS2015070910885 增加当前驻留的plmn是否允许搜的判断
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmMmcStatusInd_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_STATUS_IND_STRU            *pstLmmStatusIndMsg = VOS_NULL_PTR;
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    NAS_MML_PLMN_ID_STRU               *pstCurrPlmn        = VOS_NULL_PTR;

    pstCurrPlmn = NAS_MML_GetCurrCampPlmnId();
#endif

    pstLmmStatusIndMsg  = ( LMM_MMC_STATUS_IND_STRU* )pstMsg;

    /* 更新LMM的链接状态 */
    switch (pstLmmStatusIndMsg->ulConnState)
    {
        case MMC_LMM_CONN_ESTING:
        case MMC_LMM_CONNECTED_SIG:
            NAS_MML_SetEpsSigConnStatusFlg(VOS_TRUE);
            break;

        case MMC_LMM_CONNECTED_DATA:
            NAS_MML_SetEpsServiceConnStatusFlg(VOS_TRUE);
            break;

        case MMC_LMM_CONN_IDLE:
            NAS_MML_SetEpsSigConnStatusFlg(VOS_FALSE);
            NAS_MML_SetEpsServiceConnStatusFlg(VOS_FALSE);
            break;

        default:
            break;
    }

    /* 判断信令链接是否已经完成释放 */
    if ( VOS_TRUE == NAS_MML_IsRrcConnExist() )
    {
        /* 信令链接未释放完成，继续等待信令链接释放消息 */
        return VOS_TRUE;
    }

    /* 需要已注册失败导致需要搜网的为优先 */
    if ( VOS_TRUE == NAS_MMC_IsPlmnSearchNeeded_L1Main())
    {
        return NAS_MMC_PerformPlmnSearch_L1Main();
    }

    /* 如果注册失败不需要发起搜网,则判断是否有缓存的搜网标志 */
    NAS_MMC_PerformBufferedPlmnSearch_L1Main();
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (VOS_TRUE == NAS_MMC_IsCampLteNormalService())
    {
        if (VOS_FALSE == NAS_MMC_IsCurrLtePlmnAllowSrchInCLMode(pstCurrPlmn))
        {
            NAS_WARNING_LOG2(WUEPS_PID_MMC, "NAS_MMC_RcvLmmMmcStatusInd_OnPlmn:WARNING: Current Lte Plmn is not Allowed Srch In CL Mode,ulMcc and ulMnc are",
                                                 pstCurrPlmn->ulMcc, pstCurrPlmn->ulMnc);

            NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

            /* 发送内部搜网请求 */
            NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_AREA_LOST, VOS_NULL, 0);

            return VOS_TRUE;
        }
    }
#endif

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmMmcAttachInd_OnPlmn
 功能描述  : 在ON PLMN时候收到ID_LMM_MMC_ATTACH_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg: ID_LMM_MMC_ATTACH_IND消息
 输出参数  : 无
 返 回 值  : VOS_TRUE: 函数处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年4月1日
   作    者   : w00167002
   修改内容   : 新生成函数

 2.日    期   : 2011年7月28日
   作    者   : w00176964
   修改内容   : V7R1 Phase II调整

 3.日    期   : 2011年10月22日
   作    者   : w00167002
   修改内容   : V7R1 Phase II-2 增加HPLMN TIMER的事件上报

 4.日    期   : 2011年11月20日
   作    者   : l00130025
   修改内容   : 问题单号:DTS2111111507462,假流程，单个域注册成功，时错误地停止了AvailTimer
 5.日    期   : 2011年10月25日
   作    者   : z00161729
   修改内容   : V7R1 Phase III联合注册调整
 6.日    期   : 2012年1月8日
   作    者   : z00161729
   修改内容   : V7R1 Phase IV调整
 7.日    期   : 2012年4月26日
   作    者   : w00176964
   修改内容   : GUL BG项目调整
 8.日    期   : 2012年11月22日
   作    者   : t00212959
   修改内容   : DTS2012112006974
 9.日    期   : 2012年12月26日
   作    者   : l00171473
   修改内容   : DTS2012122502264, 如果需要周期性搜索GU网络则不能停止AVAILABLE定时器
 10.日    期   : 2013年12月25日
    作    者   : z00161729
    修改内容   : SVLTE支持NCELL搜网
                  快速找回TL，所以应尽量让其快速找回。
 11.日    期   : 2014年2月24日
    作    者   : w00176964
    修改内容   : High_Rat_Hplmn_Search特性调整:增加High_Prio_rat_hplmn定时器的启动处理
 12.日    期   : 2014年10月27日
   作    者   : b00269685
   修改内容   : 增加High_Prio_rat_hplmn TD Count的处理
 13.日    期   : 2015年5月26日
    作    者   : w00167002
    修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0项目修改
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmMmcAttachInd_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_ATTACH_IND_STRU                                *pstLmmAttachIndMsg = VOS_NULL_PTR;
    VOS_UINT32                                              ulRrcConnExistFlag;
    NAS_MMC_CL_ADDITIONAL_ACTION_ENUM_UINT8                 enClRegAddition;

    NAS_MML_LTE_UE_OPERATION_MODE_ENUM_UINT8                enUeOperationMode;

    enUeOperationMode   =  NAS_MML_GetLteUeOperationMode();
    pstLmmAttachIndMsg  = (LMM_MMC_ATTACH_IND_STRU*)pstMsg;

    /* LMM在搜网未回复search cnf时收到用户detach ps请求后，后续不会做注册给mmc回复attach result
       为MMC_LMM_ATT_RSLT_PS_ATT_NOT_ALLOW，请求类型填的是MMC_LMM_ATT_TYPE_BUTT，
       MMC需要根据当前ue operation mode给请求类型重新赋值 */
    if ((MMC_LMM_ATT_TYPE_BUTT == pstLmmAttachIndMsg->ulReqType)
     && (MMC_LMM_ATT_RSLT_PS_ATT_NOT_ALLOW == pstLmmAttachIndMsg->ulAttachRslt))
    {
        pstLmmAttachIndMsg->ulReqType = NAS_MMC_ConvertLmmAttachReqType(enUeOperationMode);
    }

    /* 向GMM和MM转发注册结果消息 */
    NAS_MMC_SndMmLmmAttachInd(pstLmmAttachIndMsg);
    NAS_MMC_SndGmmLmmAttachInd(pstLmmAttachIndMsg);

    /* 处理attach结果 */
    NAS_MMC_ProcLmmAttachInd_OnPlmn(pstLmmAttachIndMsg);

    NAS_MMC_LogFsmL1MainCtxRelatedInfo(NAS_MMC_GetL1MainCtx_L1Main());

    enClRegAddition = NAS_MMC_GetCLRegAdditionalAction_L1Main();

    /* CL模式下,如果CL的reg addition为anycell搜网或受限驻留,需要通知
       MSCC此时LTE不可用,搜索HRPD */
    if ((VOS_FALSE                                       == NAS_MML_IsGULModeConfigured())
     && ((NAS_MMC_CL_ADDITIONAL_ACTION_ANYCELL_SELECTION == enClRegAddition)
      || (NAS_MMC_CL_ADDITIONAL_ACTION_LIMITED_CAMP_ON   == enClRegAddition)))
    {
        NAS_MMC_SndMsccMmssLteUnAvailableInd(MSCC_MMC_MMSS_LTE_UNAVIALBLE_REASON_REG_FAILURE);
    }

    /* 不需要搜网直接返回 */
    if (VOS_FALSE == NAS_MMC_IsPlmnSearchNeeded_L1Main())
    {
        /* ON PLMN时收到注册结果后续不需搜网，需要判断是否需要启动HPLMN定时器 */
        if (VOS_TRUE == NAS_MMC_IsNeedStartHPlmnTimer())
        {
            /* 启动定时器 */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_HPLMN_TIMER, NAS_MMC_GetHplmnTimerLen());


            /* HPLMN TIMER启动事件上报 */
            NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_HPLMN_TIMER_START,
                            VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);


            /* 将HPLMN启动类型设置为非首次启动 */
            NAS_MMC_SetFirstStartHPlmnTimerFlg(VOS_FALSE);

        }

        if (VOS_TRUE == NAS_MMC_IsNeedStartHighPrioRatHPlmnTimer())
        {
            /* 启动定时器 */
            if (VOS_TRUE == NAS_MMC_StartTimer(TI_NAS_MMC_HIGH_PRIO_RAT_HPLMN_TIMER, NAS_MMC_GetHighPrioRatHplmnTimerLen()))
            {
                NAS_MMC_AddCurHighPrioRatHplmnTimerFirstSearchCount_L1Main();
                NAS_MMC_UpdateHighPrioRatHPlmnTimerTdCount();
            }
        }


        /* 正常服务则停止available定时器 */
        if ( VOS_TRUE == NAS_MMC_IsPsNormalService())
        {

            /* 不需要周期性搜索GU网络, 才停止available定时器 */
            if ( VOS_FALSE == NAS_MMC_IsCsPsMode1NeedPeriodSearchGU() )
            {
                NAS_MMC_ResetOosPlmnSearchTimerCount_OnPlmn();

                NAS_MMC_StopTimer(TI_NAS_MMC_AVAILABLE_TIMER);

                /* Added by c00318887 for 预置频点搜网优化, 2015-9-1, begin */
                NAS_MMC_StopTimer(TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER);
                /* Added by c00318887 for 预置频点搜网优化, 2015-9-1, end */

            }
        }


        return VOS_TRUE;
    }



    /* 增加内部列表搜网判断 */
    if ( VOS_TRUE == NAS_MMC_IsLRegFailTriggerInterPlmnList_L1Main())
    {
        NAS_MMC_SndInterPlmnListReq();

        /* 触发搜网后就清除additional的值 */
        NAS_MMC_ClearAllRegAdditionalAction_L1Main();

        /* 触发搜网后同时清除CS/PS的注册尝试次数 */
        NAS_MMC_ClearAllRegAttemptCount_L1Main();

        return VOS_TRUE;
    }

    /* 判断信令链接是否已经完成释放 */
    ulRrcConnExistFlag  = NAS_MML_IsRrcConnExist();

    if ( VOS_TRUE == ulRrcConnExistFlag )
    {
        if (VOS_TRUE == NAS_MMC_IsDisableLteNeedLocalReleaseEpsConn())
        {
            NAS_MMC_SndLmmRelReq();
        }

        /* 信令链接未释放完成，继续等待信令链接释放消息 */
        return VOS_TRUE;
    }

    /* 发起搜网 */
    (VOS_VOID)NAS_MMC_PerformPlmnSearch_L1Main();

    return VOS_TRUE;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmMmcTauResultInd_OnPlmn
 功能描述  : 在ON PLMN时候收到ID_LMM_MMC_TAU_RESULT_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg: ID_LMM_MMC_TAU_RESULT_IND消息首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE: 函数处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年4月1日
   作    者   : w00167002
   修改内容   : 新生成函数

 2.日    期   : 2011年7月28日
   作    者   : w00176964
   修改内容   : V7R1 Phase II调整

 3.日    期   : 2011年10月22日
   作    者   : w00167002
   修改内容   : V7R1 Phase II-2 增加HPLMN TIMER的事件上报

 4.日    期   : 2011年11月20日
   作    者   : l00130025
   修改内容   : 问题单号:DTS2111111507462,假流程，单个域注册成功，时错误地停止了AvailTimer
 5.日    期   : 2011年10月26日
   作    者   : w00176964
   修改内容   : V7R1 Phase III调整:联合注册修改
 6.日    期   : 2012年4月26日
   作    者   : w00176964
   修改内容   : GUL BG项目调整
 7.日    期   : 2012年11月22日
   作    者   : t00212959
   修改内容   : DTS2012112006974
 8.日    期   : 2012年12月26日
   作    者   : l00171473
   修改内容   : DTS2012122502264, 如果需要周期性搜索GU网络则不能停止AVAILABLE定时器
 9.日    期   : 2013年12月25日
   作    者   : z00161729
   修改内容   : SVLTE支持NCELL搜网
                  快速找回TL，所以应尽量让其快速找回。
10.日    期   : 2014年2月24日
   作    者   : w00176964
   修改内容   : High_Rat_Hplmn_Search特性调整:增加High_Prio_rat_hplmn定时器的启动处理
11.日    期   : 2014年10月27日
   作    者   : b00269685
   修改内容   : 增加High_Prio_rat_hplmn TD Count的处理
12.日    期   : 2015年5月26日
   作    者   : w00167002
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0项目修改
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmMmcTauResultInd_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_TAU_RESULT_IND_STRU        *pstLmmTauIndMsg;
    VOS_UINT32                          ulRrcConnExistFlag;
    NAS_MMC_CL_ADDITIONAL_ACTION_ENUM_UINT8                 enClRegAddition;

    pstLmmTauIndMsg  = (LMM_MMC_TAU_RESULT_IND_STRU*)pstMsg;

    /* 向GMM和MM转发注册结果消息 */
    NAS_MMC_SndMmLmmTauResultInd(pstLmmTauIndMsg);
    NAS_MMC_SndGmmLmmTauResultInd(pstLmmTauIndMsg);

    /* 处理tau结果 */
    NAS_MMC_ProcLmmTauResultInd_OnPlmn(pstLmmTauIndMsg);

    NAS_MMC_LogFsmL1MainCtxRelatedInfo(NAS_MMC_GetL1MainCtx_L1Main());

    enClRegAddition = NAS_MMC_GetCLRegAdditionalAction_L1Main();

    /* CL模式下,如果CL的reg addition为anycell搜网或受限驻留,需要通知
       MSCC此时LTE不可用,搜索HRPD */
    if ((VOS_FALSE                                       == NAS_MML_IsGULModeConfigured())
     && ((NAS_MMC_CL_ADDITIONAL_ACTION_ANYCELL_SELECTION == enClRegAddition)
      || (NAS_MMC_CL_ADDITIONAL_ACTION_LIMITED_CAMP_ON   == enClRegAddition)))
    {
        NAS_MMC_SndMsccMmssLteUnAvailableInd(MSCC_MMC_MMSS_LTE_UNAVIALBLE_REASON_REG_FAILURE);
    }

    /* 不需要搜网直接返回 */
    if (VOS_FALSE == NAS_MMC_IsPlmnSearchNeeded_L1Main())
    {
        /* ON PLMN时收到注册结果后续不需搜网，需要判断是否需要启动HPLMN定时器 */
        if (VOS_TRUE == NAS_MMC_IsNeedStartHPlmnTimer())
        {
            /* 启动定时器 */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_HPLMN_TIMER, NAS_MMC_GetHplmnTimerLen());


            /* HPLMN TIMER启动事件上报 */
            NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_HPLMN_TIMER_START,
                            VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);


            /* 将HPLMN启动类型设置为非首次启动 */
            NAS_MMC_SetFirstStartHPlmnTimerFlg(VOS_FALSE);

        }

        if (VOS_TRUE == NAS_MMC_IsNeedStartHighPrioRatHPlmnTimer())
        {
            /* 启动定时器 */
            if (VOS_TRUE == NAS_MMC_StartTimer(TI_NAS_MMC_HIGH_PRIO_RAT_HPLMN_TIMER, NAS_MMC_GetHighPrioRatHplmnTimerLen()))
            {
                NAS_MMC_AddCurHighPrioRatHplmnTimerFirstSearchCount_L1Main();
                NAS_MMC_UpdateHighPrioRatHPlmnTimerTdCount();
            }
        }


        /* 正常服务则停止available定时器 */
        if ( VOS_TRUE == NAS_MMC_IsPsNormalService())
        {

            /* 不需要周期性搜索GU网络, 才停止available定时器 */
            if ( VOS_FALSE == NAS_MMC_IsCsPsMode1NeedPeriodSearchGU() )
            {
                NAS_MMC_ResetOosPlmnSearchTimerCount_OnPlmn();

                NAS_MMC_StopTimer(TI_NAS_MMC_AVAILABLE_TIMER);

                /* Added by c00318887 for 预置频点搜网优化, 2015-9-1, begin */
                NAS_MMC_StopTimer(TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER);
                /* Added by c00318887 for 预置频点搜网优化, 2015-9-1, end */

            }
        }


        return VOS_TRUE;
    }



    /* 增加内部列表搜网判断 */
    if ( VOS_TRUE == NAS_MMC_IsLRegFailTriggerInterPlmnList_L1Main())
    {
        NAS_MMC_SndInterPlmnListReq();

        /* 触发搜网后就清除additional的值 */
        NAS_MMC_ClearAllRegAdditionalAction_L1Main();

        /* 触发搜网后同时清除CS/PS的注册尝试次数 */
        NAS_MMC_ClearAllRegAttemptCount_L1Main();

        return VOS_TRUE;
    }

    /* 判断信令链接是否已经完成释放 */
    ulRrcConnExistFlag  = NAS_MML_IsRrcConnExist();

    if ( VOS_TRUE == ulRrcConnExistFlag )
    {
        if (VOS_TRUE == NAS_MMC_IsDisableLteNeedLocalReleaseEpsConn())
        {
            NAS_MMC_SndLmmRelReq();
        }

        /* 信令链接未释放完成，继续等待信令链接释放消息 */
        return VOS_TRUE;
    }

    /* 发起搜网 */
    (VOS_VOID)NAS_MMC_PerformPlmnSearch_L1Main();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmMmcDetachInd_OnPlmn
 功能描述  : 在ON PLMN时候收到ID_LMM_MMC_DETACH_IND消息的处理
 输入参数  : ulEventType:消息首地址
             pstMsg: ID_LMM_MMC_DETACH_IND首地址消息
 输出参数  : 无
 返 回 值  : VOS_TRUE: 函数处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年4月1日
   作    者   : w00167002
   修改内容   : 新生成函数
 2.日    期   : 2011年7月28日
   作    者   : w00176964
   修改内容   : V7R1 Phase II调整

 3.日    期   : 2011年10月26日
   作    者   : w00176964
   修改内容   : V7R1 Phase III调整:联合注册修改
 4.日    期   : 2012年12月26日
   作    者   : l00171473
   修改内容   : DTS2012122502264, 如果需要周期性搜索GU网络则不能停止AVAILABLE定时器
 5.日    期   : 2013年12月25日
   作    者   : z00161729
   修改内容   : SVLTE支持NCELL搜网
 6.日    期   : 2015年6月6日
   作    者   : s00217060
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0修改
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmMmcDetachInd_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_DETACH_IND_STRU                                *pstDetachMsg = VOS_NULL_PTR;
    VOS_UINT32                                              ulRrcConnExistFlag;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsAdditionalAction;
    NAS_MMC_CL_ADDITIONAL_ACTION_ENUM_UINT8                 enClRegAddition;

    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, begin */
    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, end */

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));
    pstDetachMsg        = (LMM_MMC_DETACH_IND_STRU*)pstMsg;

    /* 处理DETACH消息，返回下一步动作 */
    NAS_MMC_ProcLmmDetachInd(pstDetachMsg, &enCsAdditionalAction, &enPsAdditionalAction);

    if (VOS_TRUE == NAS_MMC_IsNeedSndEplmn())
    {
        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, begin */
        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildSndLmmEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndLmmEquPlmnReq(&stSndEquPlmnInfo);
        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, end */

        NAS_MMC_SndOmEquPlmn();
    }

    /*更新EPS的下一步的动作类型*/
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enPsAdditionalAction)
    {
        NAS_MMC_SetPsRegAdditionalAction_L1Main(enPsAdditionalAction);
    }

    /*更新CS的下一步的动作类型*/
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enCsAdditionalAction)
    {
        NAS_MMC_SetCsRegAdditionalAction_L1Main(enCsAdditionalAction);
    }

    enClRegAddition = NAS_MMC_GetCLRegAdditionalAction_L1Main();

    /* CL模式下,如果CL的reg addition为anycell搜网或受限驻留,需要通知
       MSCC此时LTE不可用,搜索HRPD */
    if ((VOS_FALSE                                       == NAS_MML_IsGULModeConfigured())
     && ((NAS_MMC_CL_ADDITIONAL_ACTION_ANYCELL_SELECTION == enClRegAddition)
      || (NAS_MMC_CL_ADDITIONAL_ACTION_LIMITED_CAMP_ON   == enClRegAddition)))
    {
        NAS_MMC_SndMsccMmssLteUnAvailableInd(MSCC_MMC_MMSS_LTE_UNAVIALBLE_REASON_MT_DETACH);
    }

    /* 不需要搜网直接返回 */
    if (VOS_FALSE == NAS_MMC_IsPlmnSearchNeeded_L1Main())
    {
        /* 正常服务则停止available定时器 */
        if ( VOS_TRUE == NAS_MMC_IsNormalServiceStatus())
        {

            /* 不需要周期性搜索GU网络, 才停止available定时器 */
            if ( VOS_FALSE == NAS_MMC_IsCsPsMode1NeedPeriodSearchGU() )
            {
                NAS_MMC_ResetOosPlmnSearchTimerCount_OnPlmn();

                NAS_MMC_StopTimer(TI_NAS_MMC_AVAILABLE_TIMER);

                /* Added by c00318887 for 预置频点搜网优化, 2015-9-1, begin */
                NAS_MMC_StopTimer(TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER);
                /* Added by c00318887 for 预置频点搜网优化, 2015-9-1, end */

            }
        }


        return VOS_TRUE;
    }



    /* 判断信令链接是否已经完成释放 */
    ulRrcConnExistFlag  = NAS_MML_IsRrcConnExist();

    if ( VOS_TRUE == ulRrcConnExistFlag )
    {
        /* 信令链接未释放完成，继续等待信令链接释放消息 */
        return VOS_TRUE;
    }

    /* 发起搜网 */
    (VOS_VOID)NAS_MMC_PerformPlmnSearch_L1Main();

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmMmcServiceRsltInd_OnPlmn
 功能描述  : 在ON PLMN时候收到ID_LMM_MMC_SERVICE_RESULT_IND消息的处理
             LMM的SERVICE流程结果通过此原语通知MMC。结构中的bit域来表示该项是否有效。
             SERVICE流程成功，不需通知MMC；
             SERVICE流程被网侧拒绝，通过SERVICE结果中MMC_LMM_SERVICE_RSLT_FAILURE通知MMC，并携带相应的原因值。
             如果UE触发EXTENDED SERVICE流程，需携带SERVICE类型。
             注：SERIVE类型暂时不使用
 输入参数  : ulEventType:消息类型
             pstMsg: ID_LMM_MMC_SERVICE_RESULT_IND消息首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE: 函数处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年4月1日
   作    者   : w00167002
   修改内容   : 新生成函数
 2.日    期   : 2011年7月28日
   作    者   : w00176964
   修改内容   : V7R1 Phase II调整
 3.日    期   : 2012年2月13日
   作    者   : w00167002
   修改内容   : DTS2011122704039:additional action值若为无效值NAS_MMC_ADDITIONAL_ACTION_BUTT
                 则不更新当前的additional action
 4.日    期   : 2012年06月01日
   作    者   : sunxibo /46746
   修改内容   : Added for V7R1 C50 CS/PS mode 1
 5.日    期   : 2012年8月21日
   作    者   : z00161729
   修改内容   : DCM定制需求和遗留问题修改DTS2012090401249
 6.日    期   : 2012年12月26日
   作    者   : l00171473
   修改内容   : DTS2012122502264, 如果需要周期性搜索GU网络则不能停止AVAILABLE定时器
 7.日    期   : 2013年12月25日
   作    者   : z00161729
   修改内容   : SVLTE支持NCELL搜网
 8.日    期   : 2015年5月26日
   作    者   : w00167002
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0项目修改
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmMmcServiceRsltInd_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_SERVICE_RESULT_IND_STRU                        *pstSerRsltMsg = VOS_NULL_PTR;
    VOS_UINT32                                              ulRrcConnExistFlag;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;
    NAS_MMC_CL_ADDITIONAL_ACTION_ENUM_UINT8                 enClRegAddition;

    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, begin */
    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, end */

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));
    pstSerRsltMsg     = (LMM_MMC_SERVICE_RESULT_IND_STRU*)pstMsg;

    /* 根据LMM的service result结果返回下一步处理动作 */
    enAdditionalAction = NAS_MMC_ProcLmmServiceRsltInd(pstSerRsltMsg);

    /* AdditionalAction有效，更新EPS的下一步的动作类型 */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enAdditionalAction )
    {
        NAS_MMC_SetPsRegAdditionalAction_L1Main(enAdditionalAction);
    }

    NAS_MMC_LogFsmL1MainCtxRelatedInfo(NAS_MMC_GetL1MainCtx_L1Main());

    if (VOS_TRUE == NAS_MMC_IsNeedSndEplmn())
    {
        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, begin */
        pstEquPlmnInfo     = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildSndLmmEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndLmmEquPlmnReq(&stSndEquPlmnInfo);
        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, end */

        NAS_MMC_SndOmEquPlmn();
    }

    enClRegAddition = NAS_MMC_GetCLRegAdditionalAction_L1Main();

    /* CL模式下,如果CL的reg addition为anycell搜网或受限驻留,需要通知
       MSCC此时LTE不可用,搜索HRPD */
    if ((VOS_FALSE                                       == NAS_MML_IsGULModeConfigured())
     && ((NAS_MMC_CL_ADDITIONAL_ACTION_ANYCELL_SELECTION == enClRegAddition)
      || (NAS_MMC_CL_ADDITIONAL_ACTION_LIMITED_CAMP_ON   == enClRegAddition)))
    {
        NAS_MMC_SndMsccMmssLteUnAvailableInd(MSCC_MMC_MMSS_LTE_UNAVIALBLE_REASON_SERVICE_FAILURE);
    }

    /* 不需要搜网直接返回 */
    if (VOS_FALSE == NAS_MMC_IsPlmnSearchNeeded_L1Main())
    {
        /* 正常服务则停止available定时器 */
        if ( VOS_TRUE == NAS_MMC_IsNormalServiceStatus())
        {

            /* 不需要周期性搜索GU网络, 才停止available定时器 */
            if ( VOS_FALSE == NAS_MMC_IsCsPsMode1NeedPeriodSearchGU() )
            {
                NAS_MMC_ResetOosPlmnSearchTimerCount_OnPlmn();

                NAS_MMC_StopTimer(TI_NAS_MMC_AVAILABLE_TIMER);

                /* Added by c00318887 for 预置频点搜网优化, 2015-9-1, begin */
                NAS_MMC_StopTimer(TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER);
                /* Added by c00318887 for 预置频点搜网优化, 2015-9-1, end */

            }
        }


        return VOS_TRUE;
    }



    /* 判断信令链接是否已经完成释放 */
    ulRrcConnExistFlag  = NAS_MML_IsRrcConnExist();

    if ( VOS_TRUE == ulRrcConnExistFlag )
    {
       /* 信令链接未释放完成，继续等待信令链接释放消息 */
       return VOS_TRUE;
    }

    /* 发起搜网 */
    (VOS_VOID)NAS_MMC_PerformPlmnSearch_L1Main();

    return VOS_TRUE;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmMmcSuspendInd_OnPlmn
 功能描述  : 在ON PLMN时候收到ID_LMM_MMC_SUSPEND_IND消息的处理
 输入参数  : ulEventType:LMM 异系统重选消息类型
             pstMsg: LMM异系统重选消息首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE: 函数处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月1日
    作    者   : w00167002
    修改内容   : 新生成函数
  2.日    期   : 2011年07月13日
    作    者   : w00176964
    修改内容   : GUNAS V7R1 PhaseII 阶段调整
  3.日    期   : 2011年12月20日
    作    者   : h44270
    修改内容   : 启动异系统状态机时，认为当前无网络，此时APS挂起

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmMmcSuspendInd_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_SUSPEND_IND_STRU           *pstLSuspendMsg  = VOS_NULL_PTR;

    pstLSuspendMsg = (LMM_MMC_SUSPEND_IND_STRU*)pstMsg;

    /* 根据不同的挂起原因值，启动不同的状态机 */
    switch(pstLSuspendMsg->ulSysChngType)
    {
        case MMC_LMM_SUS_TYPE_RSL:
        case MMC_LMM_SUS_TYPE_REDIR:
            NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_INTER_SYS_CELLRESEL);
            break;

        case MMC_LMM_SUS_TYPE_HO:
            /* Added by s00261364 for L-C互操作项目, 2014-3-12, begin */
            /*读全局变量进行模式判断，如果不为C+L互操作模式，则发搜网注册请求*/
            if (MMC_LMM_SYS_CHNG_DIR_L2C == pstLSuspendMsg->ulSysChngDir)
            {
                /* C+L模式不支持异系统切换，回复LMM挂起失败 */
                NAS_MMC_SndLmmSuspendRsp(MMC_LMM_FAIL);
                return VOS_TRUE;
            }
            /* Added by s00261364 for L-C互操作项目, 2014-3-12, end */

            NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_INTER_SYS_HO);
            break;

        case MMC_LMM_SUS_TYPE_CCO:
            /* Added by s00261364 for L-C互操作项目, 2014-3-12, begin */
            /*读全局变量进行模式判断，如果不为C+L互操作模式，则发搜网注册请求*/
            if (MMC_LMM_SYS_CHNG_DIR_L2C == pstLSuspendMsg->ulSysChngDir)
            {
                /* C+L模式不支持异系统切换，回复LMM挂起失败 */
                NAS_MMC_SndLmmSuspendRsp(MMC_LMM_FAIL);
                return VOS_TRUE;
            }
            /* Added by s00261364 for L-C互操作项目, 2014-3-12, end */

            NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_INTER_SYS_CCO);
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmMmcSuspendInd_OnPlmn:Unexpected Suspend Type!");
            break;
    }

    if ( (MMC_LMM_SUS_TYPE_BUTT != pstLSuspendMsg->ulSysChngType)
      && (MMC_LMM_SUS_TYPE_CCO_REVERSE != pstLSuspendMsg->ulSysChngType) )
    {
        NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,
                                 NAS_MML_GetSimPsRegStatus());
    }

    return VOS_TRUE;
}
/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmAttachCnf_L1Main
 功能描述  : 层一状态机收到Attach_Cnf消息时，需要搜网的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月4日
    作    者   : z40661
    修改内容   : 新生成函数
  2.日    期   : 2012年9月5日
    作    者   : s00217060
    修改内容   : DTS2012082703201:修改函数名称

  3.日    期   : 2013年11月15日
    作    者   : w00167002
    修改内容   : L-->LWG时候，需要触发搜网。禁止接入技术L时候，用户设置为LWG，MMA
                 先回DETACH CS/PS.在SYSCFG设置完成后进行CSPS的ATTACH,在收到LMM的
                 ATTACH CNF时候，
  4.日    期   : 2014年4月24日
    作    者   : w00242748
    修改内容   : DTS2014042405819:无卡状态下，紧急呼被拒#5，后发起ANYCELL搜，导致退状态机
                 后下发RRMM_UE_OOC_STATUS_NOTIFY_IND，导致网络不断下发CM SERVICE REJ
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmAttachCnf_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (VOS_FALSE == NAS_MML_IsUsimStausValid())
    {
        if ( VOS_FALSE == NAS_MML_IsRrcConnExist() )
        {
            /* 需要进行搜网 */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

            /* 卡无效发起anycell搜网 */
            NAS_MMC_SndInterAnyCellSearchReq(VOS_NULL_PTR, NAS_MMC_ANYCELL_SEARCH_SCENE_BUTT);
        }
        else
        {
            NAS_MMC_SetPsRegAdditionalAction_L1Main(NAS_MMC_ADDITIONAL_ACTION_CSPS_ANYCELL);
        }

        return VOS_TRUE;
    }

    /* 需要进行搜网 */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

    /* DISABLE lte搜网场景 */
    if ( NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS == NAS_MML_GetLteCapabilityStatus() )
    {
        /* 卡有效发起内部指定搜网 */
        NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_DISABLE_LTE, VOS_NULL_PTR, 0);

        return VOS_TRUE;
    }

    /* 卡有效发起内部指定搜网 */
    NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED, VOS_NULL_PTR, 0);


    return VOS_TRUE;
}


/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-14, begin */
/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmServiceResultInd_Initial
 功能描述  : INITIAL时收到LMM模块ID_LMM_MMC_SERVICE_RESULT_IND紧急呼叫指示处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE:函数处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年8月14日
   作    者   : z00161729
   修改内容   : 新生成函数

 2.日    期   : 2015年9月6日
   作    者   : z00359541
   修改内容   : DTS2015081407087: 接口调整，删除bitOpReqType项
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmServiceResultInd_Initial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU                              stAnycellSrchRatList;
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList;

    pstPrioRatList       = NAS_MML_GetMsPrioRatList();

    if (NAS_MML_CSFB_SERVICE_STATUS_MO_EMERGENCY_EXIST == NAS_MML_GetCsfbServiceStatus())
    {
        /* 触发ANYCELL搜网,构造需要anycell搜的接入技术为GU,优先顺序按照syscfg设置 */
        NAS_MMC_BuildCoverageRatPrioListEmgCall_L1Main(pstPrioRatList, &stAnycellSrchRatList);

        NAS_MMC_SndInterAnyCellSearchReq(&stAnycellSrchRatList, NAS_MMC_ANYCELL_SEARCH_SCENE_BUTT);
    }

    return VOS_TRUE;
}

/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-14, end */
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMsccCLAssociatedInfoNtf_OnPlmn
 功能描述  : 驻留时收到MSCCM模块ID_MSCC_MMC_CL_ASSOCIATED_INFO_NTF的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE:函数处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年9月17日
   作    者   : y00346957
   修改内容   : DTS2015070910885 新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccCLAssociatedInfoNtf_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
     NAS_MML_PLMN_ID_STRU               *pstCurrPlmn        = VOS_NULL_PTR;

    pstCurrPlmn = NAS_MML_GetCurrCampPlmnId();

    if (VOS_TRUE != NAS_MMC_IsCampLteNormalService())
    {
        return VOS_TRUE;
    }

    if (VOS_TRUE == NAS_MMC_IsCurrLtePlmnAllowSrchInCLMode(pstCurrPlmn))
    {
        return VOS_TRUE;
    }

    NAS_WARNING_LOG2(WUEPS_PID_MMC, "NAS_MMC_RcvMsccCLAssociatedInfoNtf_OnPlmn:WARNING: Current Lte Plmn is not Allowed Srch In CL Mode,ulMcc and ulMnc are",
                                                 pstCurrPlmn->ulMcc, pstCurrPlmn->ulMnc);

    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        /* 主动请求释放链接 */
        NAS_MMC_SndLmmRelReq();
    }
    else
    {
        NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

        /* 发送内部搜网请求 */
        NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_AREA_LOST, VOS_NULL, 0);
    }

    return VOS_TRUE;
}
#endif
#endif

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiHplmnTimerExpired_OnPlmn
 功能描述  : On plmn情况下收到HPLMN定时器超时消息
 输入参数  : ulEventType:消息类型
             pstMsg:HPLMN定时器超时消息
 输出参数  : 无
 返 回 值  : VOS_TRUE:消息处理完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月13日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   : 2011年12月31日
   作    者   : w00166186
   修改内容   : DTS2011082902017,ON PLMN下注册被拒,搜网状态机重复搜索该网络
 3.日    期   : 2012年4月27日
   作    者   : w00176964
   修改内容   : GUL BG搜网调整:状态机合一
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiHplmnTimerExpired_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU *pstHighPrioPlmnSearchList = VOS_NULL_PTR;

    /* 获取高优先级搜网列表信息 */
    pstHighPrioPlmnSearchList = NAS_MMC_GetHighPrioPlmnList();

    /* 初始化高优先级搜网列表 */
    NAS_MMC_InitPlmnSelectionList(NAS_MMC_PLMN_SEARCH_SCENE_HIGH_PRIO_PLMN_SEARCH,
                                  VOS_NULL_PTR,
                                  pstHighPrioPlmnSearchList);

    /* 启动BG搜索状态机 */
    NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_BG_PLMN_SEARCH);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiTryingHighPrioPlmnSearchExpired_OnPlmn
 功能描述  : On plmn情况下收到周期性尝试高优先级搜网定时器超时消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:HPLMN定时器超时消息
 输出参数  : 无
 返 回 值  : VOS_TRUE:消息处理完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月13日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   : 2012年4月27日
   作    者   : w00176964
   修改内容   : GUL BG搜网调整:状态机合一
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiTryingHighPrioPlmnSearchExpired_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    NAS_MMC_LogFsmL1MainCtxRelatedInfo(NAS_MMC_GetL1MainCtx_L1Main());

    /* 启动BG搜索状态机 */
    NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_BG_PLMN_SEARCH);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiHighPrioRatHplmnSrchTimerExpired_OnPlmn
 功能描述  : On plmn情况下收到TI_NAS_MMC_HIGH_PRIO_RAT_HPLMN_TIMER定时器超时消息
 输入参数  : ulEventType:消息类型
             pstMsg:HPLMN定时器超时消息
 输出参数  : 无
 返 回 值  : VOS_TRUE:消息处理完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年2月15日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiHighPrioRatHplmnSrchTimerExpired_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU *pstHighPrioPlmnSearchList = VOS_NULL_PTR;

    /* 获取高优先级搜网列表信息 */
    pstHighPrioPlmnSearchList = NAS_MMC_GetHighPrioPlmnList();

    /* 初始化高优先级搜网列表 */
    NAS_MMC_InitPlmnSelectionList(NAS_MMC_PLMN_SEARCH_SCENE_HIGH_PRIO_RAT_HPLMN_SEARCH,
                                  VOS_NULL_PTR,
                                  pstHighPrioPlmnSearchList);

    /* 启动BG搜索状态机 */
    NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_BG_PLMN_SEARCH);

    return VOS_TRUE;
}



/**************************L1 Main公共函数**************************************************/
/*****************************************************************************
 函 数 名  : NAS_MMC_BuildCoverageRatPrioList_L1Main
 功能描述  : 从搜网结果的结构中，构造当前存在网络的优先接入技术列表;
             所有接入技术不存在时，使用 SYSCFG设定的接入技术，以当前模为最优先
 输入参数  : pstPlmnSelectionRslt-搜网结果
 输出参数  : pstRatPrioList-优先级列表
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年8月13日
    作    者   : w00176964
    修改内容   : 新生成函数

  2.日    期   : 2011年11月30日
    作    者   : w00176964
    修改内容   : V7R1 Phase IV调整:disable LTE后ANYCELL时不选择LTE的网络

  3.日    期   : 2012年9月20日
    作    者   : z40661
    修改内容   : DTS2012082006273,未通知L模disable时,可用将L模的网络放在最后

  4.日    期   : 2012年11月05日
    作    者   : w00176964
    修改内容   : DTS2011082405001:更新搜网结果中的网络覆盖类型对RAT的列表进行排序
  5.日    期   : 2014年6月17日
    作    者   : z00234330
    修改内容   : PCINT清理
*****************************************************************************/
VOS_VOID NAS_MMC_BuildCoverageRatPrioList_L1Main(
    NAS_MMCMMC_PLMN_SELECTION_RSLT_STRU                    *pstPlmnSelectionRslt,
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstRatPrioList
)
{
    NAS_MMC_RAT_SEARCH_INFO_STRU                           *pstRatSearchInfo = VOS_NULL_PTR;
    VOS_UINT32                                              i;
    VOS_UINT32                                              ulIdx;
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;
#endif
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT8                                               ucFoundLteRat;
#endif
    NAS_MMC_COVERAGE_TYPE_ENUM_UINT8                        enFirstCovType;
    NAS_MMC_COVERAGE_TYPE_ENUM_UINT8                        enSecondCovType;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enTmpRat;
    VOS_UINT32                                              j;

    ulIdx               =  0;
    pstRatSearchInfo    =  pstPlmnSelectionRslt->astSearchRatInfo;
#if (FEATURE_ON == FEATURE_LTE)
    ucFoundLteRat       = VOS_FALSE;
#endif

    /* 从搜网结果结构中，获取当前存在网络的优先接入技术列表 */
    for ( i = 0 ; i < NAS_MML_MAX_RAT_NUM; i++ )
    {
        if (VOS_TRUE == NAS_MML_IsNetRatSupported(pstRatSearchInfo[i].enRatType))
        {
#if (FEATURE_ON == FEATURE_LTE)

            /* 获取LTE的能力状态 */
            enLteCapabilityStatus   = NAS_MML_GetLteCapabilityStatus();


            /* 接入技术为LTE且当前LTE状态为disable时，不选择LTE的网络 */
            if (((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS  == enLteCapabilityStatus)
              || (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS  == enLteCapabilityStatus))
             && (NAS_MML_NET_RAT_TYPE_LTE   == pstRatSearchInfo[i].enRatType))
            {
                if (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS  == enLteCapabilityStatus)
                {
                    ucFoundLteRat = VOS_TRUE;
                }
                continue;
            }
#endif
            /* Modified by z00234330 for PCLINT清理, 2014-06-16, begin */
            if (VOS_FALSE == pstRatSearchInfo[i].ucSearchAllBand)
            {
                pstRatPrioList->aucRatPrio[ulIdx] = pstRatSearchInfo[i].enRatType;
                ulIdx++;
            }
            else if ((NAS_MMC_COVERAGE_TYPE_HIGH == pstRatSearchInfo[i].enCoverageType)
                  || (NAS_MMC_COVERAGE_TYPE_LOW  == pstRatSearchInfo[i].enCoverageType))
            {
                pstRatPrioList->aucRatPrio[ulIdx] = pstRatSearchInfo[i].enRatType;
                ulIdx++;
            }
            else
            {

            }
            /* Modified by z00234330 for PCLINT清理, 2014-06-16, end */
        }
    }

#if (FEATURE_ON == FEATURE_LTE)
    /* Modified by z00234330 for PCLINT清理, 2014-06-16, begin */
    if (VOS_TRUE == ucFoundLteRat)
    {
        pstRatPrioList->aucRatPrio[ulIdx] = NAS_MML_NET_RAT_TYPE_LTE;
        ulIdx++;
    }
    /* Modified by z00234330 for PCLINT清理, 2014-06-16, end */
#endif

    /* 所有接入技术不存在时，使用 SYSCFG设定的接入技术 */
    pstRatPrioList->ucRatNum = (VOS_UINT8)ulIdx;

    /* 当前接入技术支持时，以当前接入技术最优先 */
    NAS_MML_SortSpecRatPrioHighest(NAS_MML_GetCurrNetRatType(), pstRatPrioList);

    /* 按照每种接入技术的覆盖类型排序,覆盖类型高的排在前面 */
    for (i = 0; i < pstRatPrioList->ucRatNum; i++)
    {
        for (j = i+1; j < pstRatPrioList->ucRatNum; j++)
        {
            enFirstCovType = NAS_MMC_GetSpecRatCoverageTypeInRatSearchInfoList(pstRatSearchInfo, pstRatPrioList->aucRatPrio[i]);
            enSecondCovType = NAS_MMC_GetSpecRatCoverageTypeInRatSearchInfoList(pstRatSearchInfo, pstRatPrioList->aucRatPrio[j]);

            /* 覆盖类型高的优先级高,排在前面,优先进行anycell搜网 */
            if ((enFirstCovType     < enSecondCovType)
             && (enFirstCovType     != NAS_MMC_COVERAGE_TYPE_BUTT)
             && (enSecondCovType    != NAS_MMC_COVERAGE_TYPE_BUTT))
            {
                enTmpRat                            = pstRatPrioList->aucRatPrio[i];
                pstRatPrioList->aucRatPrio[i]       = pstRatPrioList->aucRatPrio[j];
                pstRatPrioList->aucRatPrio[j]       = enTmpRat;
            }
        }
    }
}

/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-14, begin */
/*****************************************************************************
 函 数 名  : NAS_MMC_BuildCoverageRatPrioListEmgCall_L1Main
 功能描述  : 触发ANYCELL搜网,构造需要anycell搜的接入技术为GU,优先顺序按照syscfg设置
 输入参数  : pstSyscfgRatPrioList - syscfg设置的接入技术优先级
 输出参数  : pstRatPrioList       - 优先级列表
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月14日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_BuildCoverageRatPrioListEmgCall_L1Main(
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstSyscfgRatPrioList,
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatPrioList
)
{
    VOS_UINT32                          i;
    VOS_UINT8                           ucRatNum;
    NAS_MML_PLMN_RAT_PRIO_STRU          stAnycellSrchRatList;

    ucRatNum = 0;

    for (i = 0; i < pstSyscfgRatPrioList->ucRatNum; i++)
    {
        if (pstSyscfgRatPrioList->aucRatPrio[i] != NAS_MML_NET_RAT_TYPE_LTE)
        {
            stAnycellSrchRatList.aucRatPrio[ucRatNum] = pstSyscfgRatPrioList->aucRatPrio[i];
            ucRatNum++;
        }
    }

    stAnycellSrchRatList.ucRatNum = ucRatNum;
   *pstRatPrioList                = stAnycellSrchRatList;

}

/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-14, end */


/*****************************************************************************
 函 数 名  : NAS_MMC_DelDiffMccRplmnInNv_L1Main
 功能描述  : 在NV中的RPLMN和当前的RPLMN国家码不同时，删除NV中的RPLMN
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月29日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_DelDiffMccRplmnInNv_L1Main(VOS_VOID)
{
    VOS_UINT32                          i;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList;
    NAS_MML_PLMN_ID_STRU               *pstNVRplmn;
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampPlmnInfo = VOS_NULL_PTR;
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo = VOS_NULL_PTR;

    pstRplmnCfgInfo     = NAS_MML_GetRplmnCfg();

    /* 双模情况下，如果当前驻留的网络有效，并且NV中的RPLMN和当前的网络国家码
       不同，删除NV中的RPLMN */
    pstCampPlmnInfo = NAS_MML_GetCurrCampPlmnInfo();

    if (VOS_FALSE == NAS_MML_IsPlmnIdValid(&(pstCampPlmnInfo->stLai.stPlmnId)))
    {
        return;
    }

    /* 对当前支持的所有接入技术，逐项进行设置 */
    pstPrioRatList = NAS_MML_GetMsPrioRatList();

    pstNVRplmn = &(pstRplmnCfgInfo->stGRplmnInNV);

    for ( i = 0 ; i < pstPrioRatList->ucRatNum; i++ )
    {
        switch (pstPrioRatList->aucRatPrio[i] )
        {
            case NAS_MML_NET_RAT_TYPE_GSM:
                pstNVRplmn = &(pstRplmnCfgInfo->stGRplmnInNV);
                break;

            case NAS_MML_NET_RAT_TYPE_WCDMA:
                pstNVRplmn = &(pstRplmnCfgInfo->stWRplmnInNV);
                break;

            default:
                continue;
        }
        /* 当前 */
        if (pstNVRplmn->ulMcc != pstCampPlmnInfo->stLai.stPlmnId.ulMcc)
        {
            pstNVRplmn->ulMcc = NAS_MML_INVALID_MCC;
            pstNVRplmn->ulMnc = NAS_MML_INVALID_MNC;
        }

    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsPlmnSearchNeeded_L1Main
 功能描述  : 根据CS/PS的additional，确定状态机是否需要搜网
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE: 需要搜网
             VOS_FALSE: 不需要搜网
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月28日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsPlmnSearchNeeded_L1Main(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                        enAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                        enCsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                        enPsAdditionalAction;

    /* 调用优先级比较表格得出CS/PS的处理优先级，并转换为状态机下一步行为 */
    enCsAdditionalAction = NAS_MMC_GetCsRegAdditionalAction_L1Main();
    enPsAdditionalAction = NAS_MMC_GetPsRegAdditionalAction_L1Main();

    enAdditionalAction = NAS_MMC_GetPrioAddtionalAction(enCsAdditionalAction, enPsAdditionalAction);

    /* 判断是否需要搜网，不需要搜网直接返回 */
    if ( VOS_FALSE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(enAdditionalAction))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_MMC_IsLRegFailTriggerInterPlmnList_L1Main
 功能描述  : L下注册失败是否触发内部列表搜网
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:  需要触发内部列表搜网
             VOS_FALSE: 不需要触发内部列表搜网
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月20日
    作    者   : w00176964
    修改内容   : 新生成函数
    修改内容   : 新生成函数
  2.日    期   : 2013年3月11日
    作    者   : w00176964
    修改内容   : DTS2014030508059:GTL模式内部LIST搜网转化为指定搜网发起
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsLRegFailTriggerInterPlmnList_L1Main(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsAdditionalAction;
    VOS_UINT8                                               ucInterPlmnListFlg;

    ucInterPlmnListFlg  = VOS_FALSE;

    /* 调用优先级比较表格得出CS/PS的处理优先级，并转换为状态机下一步行为 */
    enCsAdditionalAction = NAS_MMC_GetCsRegAdditionalAction_L1Main();
    enPsAdditionalAction = NAS_MMC_GetPsRegAdditionalAction_L1Main();

    /* Added by s00261364 for L-C互操作项目, 2014-3-7, begin */
    if (NAS_MMC_REG_CONTROL_BY_3GPP_MMC != NAS_MMC_GetRegCtrl())
    {
        return VOS_FALSE;
    }
    /* Added by s00261364 for L-C互操作项目, 2014-3-7, end */

    /* 根据手机模式判断是否需要内部LIST搜网 */
    switch (NAS_MML_GetMsMode())
    {
        case NAS_MML_MS_MODE_PS_ONLY:

            /* PS ONLY时注册达到最大次数触发内部LIST搜网 */
            if ((NAS_MML_MAX_PS_REG_FAIL_CNT <= NAS_MMC_GetPsRegAttemptCount_L1Main())
             && (NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION == enPsAdditionalAction))
            {
                ucInterPlmnListFlg =  VOS_TRUE;
            }

            break;

        case NAS_MML_MS_MODE_PS_CS:

            /* LTE下CS+PS时不设置CS尝试次数,所以只判断PS次数*/
            if ((NAS_MML_MAX_PS_REG_FAIL_CNT <= NAS_MMC_GetPsRegAttemptCount_L1Main())
             && (NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION == enCsAdditionalAction)
             && (NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION == enPsAdditionalAction))
            {
                ucInterPlmnListFlg =  VOS_TRUE;
            }

            break;

        default:

            /* 异常打印 */
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_IsLRegFailTrigerInterPlmnList_L1Main:Unexpected MS mode!");

            break;
    }

    /* 由于tds不支持背景搜,支持TD的GTL模式下跳过内部list搜因为搜网时间太长，直接做指定搜网 */
    if (VOS_TRUE == ucInterPlmnListFlg)
    {
        if (VOS_TRUE == NAS_MMC_IsNetRatSupportedTdscdma())
        {
            return VOS_FALSE;
        }

        return VOS_TRUE;
    }

    return VOS_FALSE;
}

#endif

/*****************************************************************************
 函 数 名  : NAS_MMC_IsGURegFailTriggerIntraPlmnList_L1Main
 功能描述  : GU下注册失败是否触发内部列表搜网
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:  需要触发内部列表搜网
             VOS_FALSE: 不需要触发内部列表搜网
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月20日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2013年3月11日
    作    者   : w00176964
    修改内容   : DTS2014030508059:GTL模式内部LIST搜网转化为指定搜网发起
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsGURegFailTriggerInterPlmnList_L1Main(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsAdditionalAction;
    VOS_UINT32                                              ulCsRegCount;
    VOS_UINT32                                              ulPsRegCount;
    VOS_UINT8                                               ucInterPlmnListFlg;

    ucInterPlmnListFlg  = VOS_FALSE;

    /* 调用优先级比较表格得出CS/PS的处理优先级，并转换为状态机下一步行为 */
    enCsAdditionalAction = NAS_MMC_GetCsRegAdditionalAction_L1Main();
    enPsAdditionalAction = NAS_MMC_GetPsRegAdditionalAction_L1Main();

    /* 获取CS/PS的注册尝试次数 */
    ulCsRegCount = NAS_MMC_GetCsRegAttemptCount_L1Main();
    ulPsRegCount = NAS_MMC_GetPsRegAttemptCount_L1Main();

    /* 根据手机模式判断是否需要内部LIST搜网 */
    switch (NAS_MML_GetMsMode())
    {
        case NAS_MML_MS_MODE_CS_ONLY:

            /* CS ONLY时注册达到最大次数触发内部LIST搜网 */
            if ((NAS_MML_GetRoamBrokerRegisterFailCnt() <= ulCsRegCount)
             && (NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION == enCsAdditionalAction))
            {
                ucInterPlmnListFlg =  VOS_TRUE;
            }

            break;

        case NAS_MML_MS_MODE_PS_ONLY:

            /* PS ONLY时注册达到最大次数触发内部LIST搜网 */
            if ((NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION == enPsAdditionalAction)
             && (NAS_MML_MAX_PS_REG_FAIL_CNT <= ulPsRegCount))
            {
                ucInterPlmnListFlg =  VOS_TRUE;
            }

            break;

        case NAS_MML_MS_MODE_PS_CS:

            /* CS+PS时如果CS/PS注册同时达到最大次数触发内部LIST搜网 */
            if ((NAS_MML_GetRoamBrokerRegisterFailCnt() <= ulCsRegCount)
             && (NAS_MML_MAX_PS_REG_FAIL_CNT <= ulPsRegCount)
             && (NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION == enCsAdditionalAction)
             && (NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION == enPsAdditionalAction))
            {
                ucInterPlmnListFlg =  VOS_TRUE;
            }

            break;

        default:

            /* 异常打印 */
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_IsGuRegFailTrigerInterPlmnList_L1Main:Unexpected MS mode!");

            break;
    }

    /* 由于tds不支持背景搜,支持TD的GTL模式下跳过内部list搜因为搜网时间太长，直接做指定搜网 */
    if (VOS_TRUE == ucInterPlmnListFlg)
    {
        if (VOS_TRUE == NAS_MMC_IsNetRatSupportedTdscdma())
        {
            return VOS_FALSE;
        }

        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsAvailTimerExpiredTriggerPlmnSearch_L1Main
 功能描述  : availtimer 超时是否触发搜网
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:  需要触发搜网
             VOS_FALSE: 不需要触发搜网
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月1日
    作    者   : s46746
    修改内容   : 新生成函数
  2.日    期   : 2013年1月16日
    作    者   : t00212959
    修改内容   : DTS2013011501766:OnPlmn时卡无效不需要搜网
  3.日    期   : 2013年10月17日
    作    者   : l65478
    修改内容   : DTS2013102103487:DT需求:在单域失败时也需要发起搜网
  4.日    期   : 2014年5月15日
    作    者   : w00167002
    修改内容   : DTS2014051501018:DSDS副MODEM发起电话，主MODEM搜网失败启动AVAILABLE
                 定时器，用户发起列表搜，在列表搜过程中，周期搜网定时器超时，列表搜
                 结束后，MMC没有启动周期搜网定时器。
                 修改为:在列表搜NO RF后，都启动AVAILABLE定时器，在AVAILABLE定时器
                 超时后，增加如果当前被拒#12则不搜网，当前ACCESS BAR则不搜网。
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsAvailTimerExpiredTriggerPlmnSearch_L1Main(VOS_VOID)
{
    VOS_UINT32                          ulUsimStatusValid;

    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                        enCsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                        enPsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                        enPrioAdditionalAction;

    ulUsimStatusValid   = NAS_MML_IsUsimStausValid();

    /* 取得CS/PS的addition值 */
    enCsAdditionalAction    = NAS_MMC_GetCsRegAdditionalAction_L1Main();
    enPsAdditionalAction    = NAS_MMC_GetPsRegAdditionalAction_L1Main();
    enPrioAdditionalAction  = NAS_MMC_GetPrioAddtionalAction(enCsAdditionalAction, enPsAdditionalAction);


    /* OnPLmn卡无效不需要搜网 */
    if (NAS_MMC_AS_CELL_CAMP_ON == NAS_MMC_GetAsCellCampOn())
    {
        /* OnPLmn卡无效不需要搜网 */
        if ( VOS_FALSE == ulUsimStatusValid )
        {
            /* Added by w00167002 for 预置频点搜网优化项目, 2015-9-15, begin */
            NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsAvailTimerExpiredTriggerPlmnSearch_L1Main:ulUsimStatusValid IS FALSE AND CAMP ON! ");
            /* Added by w00167002 for 预置频点搜网优化项目, 2015-9-15, end */
            return VOS_FALSE;
        }


        /* 如果当前驻留网络被#12拒绝则不需要搜网 */
        if (NAS_MMC_ADDITIONAL_ACTION_CELL_SELECTION == enPrioAdditionalAction)
        {
            /* Added by w00167002 for 预置频点搜网优化项目, 2015-9-15, begin */
            NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsAvailTimerExpiredTriggerPlmnSearch_L1Main: #12.");
            /* Added by w00167002 for 预置频点搜网优化项目, 2015-9-15, end */

            return VOS_FALSE;
        }

        /* 如果当前驻留网络处在ACCESS BAR，则不需要搜网 */
        if (NAS_MMC_ADDITIONAL_ACTION_ACCESS_BARRED == enPrioAdditionalAction)
        {
            /* Added by w00167002 for 预置频点搜网优化项目, 2015-9-15, begin */
            NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsAvailTimerExpiredTriggerPlmnSearch_L1Main: ACCESS BAR.");
            /* Added by w00167002 for 预置频点搜网优化项目, 2015-9-15, end */

            return VOS_FALSE;
        }

    }



    /* 当前处在非正常服务状态发起搜网 */
    if (VOS_FALSE == NAS_MMC_IsNormalServiceStatus())
    {
        /* Added by w00167002 for 预置频点搜网优化项目, 2015-9-15, begin */
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsAvailTimerExpiredTriggerPlmnSearch_L1Main: NORMAL SERVICE IS FALSE.");
        /* Added by w00167002 for 预置频点搜网优化项目, 2015-9-15, end */
        return VOS_TRUE;
    }

    /* 当前NAS为未驻留状态 */
    if (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == NAS_MMC_GetSpecPlmnSearchState())
    {
        /* Added by w00167002 for 预置频点搜网优化项目, 2015-9-15, begin */
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsAvailTimerExpiredTriggerPlmnSearch_L1Main: PLMN SEARCH RUNNING.");
        /* Added by w00167002 for 预置频点搜网优化项目, 2015-9-15, end */
        return VOS_TRUE;
    }

#if (FEATURE_ON == FEATURE_LTE)
    if (VOS_TRUE == NAS_MMC_IsCsPsMode1NeedPeriodSearchGU())
    {
        /* Added by w00167002 for 预置频点搜网优化项目, 2015-9-15, begin */
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsAvailTimerExpiredTriggerPlmnSearch_L1Main: NAS_MMC_IsCsPsMode1NeedPeriodSearchGU true.");
        /* Added by w00167002 for 预置频点搜网优化项目, 2015-9-15, end */

        return VOS_TRUE;
    }
#endif

    if (VOS_TRUE == NAS_MMC_IsSingleDomainRegFailNeedPlmnSrch(NAS_MSCC_PIF_SRVDOMAIN_CS))
    {
        return VOS_TRUE;
    }

    if (VOS_TRUE == NAS_MMC_IsSingleDomainRegFailNeedPlmnSrch(NAS_MSCC_PIF_SRVDOMAIN_PS))
    {
        return VOS_TRUE;
    }

    /* Added by w00167002 for 预置频点搜网优化项目, 2015-9-15, begin */
    NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsAvailTimerExpiredTriggerPlmnSearch_L1Main:RETURN FALSE END.");
    /* Added by w00167002 for 预置频点搜网优化项目, 2015-9-15, end */

    return VOS_FALSE;

}


/*****************************************************************************
 函 数 名  : NAS_MMC_IsAvailTimerExpiredTriggerInterPlmnList_L1Main
 功能描述  : availtimer 超时是否触发内部列表搜网
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:  需要触发内部列表搜网
             VOS_FALSE: 不需要触发内部列表搜网
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月20日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2012年7月2日
    作    者   : z00161729
    修改内容   : DTS2012063000279:L内部list搜forbidden tai判定条件需要与GU保持一致
  3.日    期   : 2012年7月19日
    作    者   : s46746
    修改内容   : For CS/PS mode 1，LTE下PS卡无效需要触发指定搜网
  4.日    期   : 2013年10月17日
    作    者   : l65478
    修改内容   : DTS2013102207188:DT需求:在PS单域失败#14时也需要发起搜网
  5.日    期   : 2014年1月26日
    作    者   : z00161729
    修改内容   : DTS2014012305088：支持增强NCELL搜网，如果Modem1传递过来的邻区信息不存在的情况下，通过历史频点支持NCELL搜索。
  6.日    期   : 2014年1月27日
    作    者   : s00246516
    修改内容   : L-C互操作项目:增加获取和注册请求的处理
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsAvailTimerExpiredTriggerInterPlmnList_L1Main(VOS_VOID)
{
    VOS_UINT32                          ulUsimStatusValid;
    NAS_MMC_AS_CELL_CAMP_ON_ENUM_UINT8  enCampStatus;
    VOS_UINT32                          ulForbidFlag;

    VOS_UINT32                          ulForbidType;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT8                           ucSimPsRegStatus;
#endif

    /* 默认不在禁止列表中 */
    ulForbidFlag        = VOS_FALSE;

    ulUsimStatusValid   = NAS_MML_IsUsimStausValid();

#if (FEATURE_ON == FEATURE_LTE)

    ucSimPsRegStatus = NAS_MML_GetSimPsRegStatus();

    /* LTE单模的情况PS卡无效的时候也认为此时卡无效 */
    if ((NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
     && (VOS_FALSE == ucSimPsRegStatus))
    {
        ulUsimStatusValid = VOS_FALSE;
    }
#endif

    /* 判断available timer超时是否触发内部列表搜网，
       由于tds不支持背景搜，GTL模式下跳过内部list搜因为搜网时间太长，直接做指定搜网 */
    if (VOS_TRUE == NAS_MMC_IsNetRatSupportedTdscdma())
    {
        return VOS_FALSE;
    }

    /* Added by s00246516 for L-C互操作项目, 2014-03-04, Begin */
    if (NAS_MMC_REG_CONTROL_BY_3GPP_MMC != NAS_MMC_GetRegCtrl())
    {
        return VOS_FALSE;
    }
    /* Added by s00246516 for L-C互操作项目, 2014-03-04, End */

    /* 是否满足触发内部LIST搜网的条件:当前卡有效,且为驻留状态，且不在禁止网络信息中 */
    enCampStatus = NAS_MMC_GetAsCellCampOn();

    /* 获取当前的LA(GU下)或TA(L下)是否在禁止列表中 */
    ulForbidType = NAS_MMC_GetCurrentLaiForbbidenType();
    if (NAS_MML_PLMN_FORBID_NULL != ulForbidType)
    {
        if ((NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION == NAS_MMC_GetSingleDomainFailAction(NAS_MML_REG_DOMAIN_PS, NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN))
         && (NAS_MML_PLMN_FORBID_PLMN_FOR_GPRS == ulForbidType))
        {
            ulForbidFlag = VOS_FALSE;
        }
        else
        {
            ulForbidFlag = VOS_TRUE;
        }
    }

    /* 当前驻留态,卡有效,不在禁止LA/TA列表中允许触发内部列表搜网 */
    if ((VOS_TRUE  == ulUsimStatusValid)
     && (VOS_FALSE == ulForbidFlag)
     && (NAS_MMC_AS_CELL_CAMP_ON == enCampStatus))
    {

        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_PerformPlmnSearch_L1Main
 功能描述  : 根据CS/PS的additional，进行搜网的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE: 需要搜网
             VOS_FALSE: 不需要搜网
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月28日
    作    者   : w00176964
    修改内容   : 新生成函数

  2.日    期   : 2011年11月5日
    作    者   : w00176964
    修改内容   : V7R1 PhaseIII:联合注册调整
 3.日    期   : 2011年11月17日
   作    者   : w00167002
   修改内容   : L1Main触发搜网后就清楚缓存的搜网

 4.日    期   : 2011年11月30日
    作    者   : w00176964
    修改内容   : V7R1 Phase IV调整:disable LTE需要搜网回GU的调整
 4.日    期   : 2012年2月16日
    作    者   : h00202780
    修改内容   : CSFB&PPAC&ETWS&ISR CSFB失败需要搜网回GU的场景的搜网的修改
 5.日    期   : 2012年3月27日
   作    者   : w00166186
   修改内容   : CSFB&PPAC&ETWS&ISR 开发 ENERGENCY CALL
 6.日    期   : 2012年4月17日
   作    者   : z00161729
   修改内容   : DTS2012041400766
 7.日    期   : 2012年8月14日
   作    者   : z00161729
   修改内容   : DCM定制需求和遗留问题修改,支持L紧急呼叫
 8.日    期   : 2013年10月17日
   作    者   : l65478
   修改内容   : DTS2013102103487:DT需求:在单域失败时也需要发起搜网
 9.日    期   : 2013年3月11日
   作    者   : w00176964
   修改内容   : DTS2014030508059:GTL模式内部LIST搜网转化为指定搜网发起
*****************************************************************************/
VOS_UINT32 NAS_MMC_PerformPlmnSearch_L1Main(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsAdditionalAction;
    VOS_UINT32                                              ulSingleDomainPlmnListFlg;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enCurrentRat;
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8                        enRegRsltType;

    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-13, begin */
    NAS_MML_CSFB_SERVICE_STATUS_ENUM_UINT8                  enCsfbServiceStatus;
    NAS_MML_PLMN_RAT_PRIO_STRU                              stAnycellSrchRatList;
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList = VOS_NULL_PTR;

    enCsfbServiceStatus  = NAS_MML_GetCsfbServiceStatus();
    pstPrioRatList       = NAS_MML_GetMsPrioRatList();

    /* 获取当前LTE能力是否可用 */
    enCurrentRat   = NAS_MML_GetCurrNetRatType();

    /* 获取当前的注册结果类型 */
    enRegRsltType  = NAS_MMC_GetRegRsltType();
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-13, end */
#endif

    /* 德电需求:单域注册失败发起搜网特性打开时,如果注册失败原因值是#17,需要发起搜网 */
    ulSingleDomainPlmnListFlg = NAS_MMC_IsSingleDomainRegFailNeedPlmnSrch(NAS_MSCC_PIF_SRVDOMAIN_CS);
    ulSingleDomainPlmnListFlg |= NAS_MMC_IsSingleDomainRegFailNeedPlmnSrch(NAS_MSCC_PIF_SRVDOMAIN_PS);

    /* 调用优先级比较表格得出CS/PS的处理优先级，并转换为状态机下一步行为 */
    enCsAdditionalAction = NAS_MMC_GetCsRegAdditionalAction_L1Main();
    enPsAdditionalAction = NAS_MMC_GetPsRegAdditionalAction_L1Main();

    enAdditionalAction = NAS_MMC_GetPrioAddtionalAction(enCsAdditionalAction, enPsAdditionalAction);


    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-14, begin */
    /* 如果是csfb 紧急呼叫，需要anycell搜网 */
#if (FEATURE_ON == FEATURE_LTE)
    if ((NAS_MML_CSFB_SERVICE_STATUS_MO_EMERGENCY_EXIST == enCsfbServiceStatus)
     && (LMM_MMC_SERVICE_RESULT_IND == enRegRsltType))
    {
        NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

        /* 触发ANYCELL搜网,构造需要anycell搜的接入技术为GU,优先顺序按照syscfg设置 */
        NAS_MMC_BuildCoverageRatPrioListEmgCall_L1Main(pstPrioRatList, &stAnycellSrchRatList);

        NAS_MMC_SndInterAnyCellSearchReq(&stAnycellSrchRatList, NAS_MMC_ANYCELL_SEARCH_SCENE_BUTT);

        /* 触发搜网后就清除additional的值 */
        NAS_MMC_ClearAllRegAdditionalAction_L1Main();

        /* 触发搜网后就清除缓存的搜网 */
        NAS_MMC_SetBufferedPlmnSearchInfo(VOS_FALSE, NAS_MMC_PLMN_SEARCH_SCENE_BUTT);
        return VOS_TRUE;
    }

    /* 当前是由于L下联合注册被拒#7导致的，需要挂起L到GU下搜网 */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS  == NAS_MML_GetLteCapabilityStatus())
     && (NAS_MML_NET_RAT_TYPE_LTE == enCurrentRat))
    {
        NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

        /* 构造搜网消息 */
        NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_DISABLE_LTE, VOS_NULL_PTR, 0);

        /* 触发搜网后就清除additional的值 */
        NAS_MMC_ClearAllRegAdditionalAction_L1Main();


        /* 触发搜网后就清除缓存的搜网 */
        NAS_MMC_SetBufferedPlmnSearchInfo(VOS_FALSE, NAS_MMC_PLMN_SEARCH_SCENE_BUTT);

        return VOS_TRUE;
    }

#endif
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-14, end */

    /* 由于tds不支持背景搜,支持TD的GTL模式下跳过内部list搜因为搜网时间太长，直接做指定搜网 */
    if ((VOS_TRUE == NAS_MMC_IsNetRatSupportedTdscdma())
     && (VOS_TRUE == ulSingleDomainPlmnListFlg))
    {
        ulSingleDomainPlmnListFlg =  VOS_FALSE;
    }

    if ((NAS_MMC_ADDITIONAL_ACTION_CSPS_ANYCELL == enAdditionalAction)
     || (NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL == enAdditionalAction))
    {
        NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

        NAS_MMC_SndInterAnyCellSearchReq(VOS_NULL_PTR, NAS_MMC_ANYCELL_SEARCH_SCENE_BUTT);
    }
    else if (NAS_MMC_ADDITIONAL_ACTION_SEARCH_SUITABLE_CELL_IN_SAME_PLMN == enAdditionalAction)
    {
        NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

        /* 构造搜网消息 */
        NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_REG_REJ_CURRENT_PLMN_SEARCH,VOS_NULL_PTR, 0);
    }
    /* CSFB流程中，L下service被拒需要搜网 */
#if (FEATURE_ON == FEATURE_LTE)
    else if ( (VOS_TRUE                   == NAS_MML_IsCsfbServiceStatusExist())
           && (LMM_MMC_SERVICE_RESULT_IND == enRegRsltType) )
    {
        NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

        NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_CSFB_SERVIEC_REJ, VOS_NULL_PTR, 0);

    }
#endif
    else if (VOS_TRUE == ulSingleDomainPlmnListFlg)
    {
        NAS_MMC_SndInterPlmnListReq();

        /* 触发搜网后同时清除CS/PS的注册尝试次数 */
        NAS_MMC_ClearAllRegAttemptCount_L1Main();
    }
    else
    {
        NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

        /* 构造搜网消息 */
        NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_REG_REJ_PLMN_SEARCH, VOS_NULL_PTR, 0);
    }

    /* 触发搜网后就清除additional的值 */
    NAS_MMC_ClearAllRegAdditionalAction_L1Main();


    /* 触发搜网后就清除缓存的搜网 */
    NAS_MMC_SetBufferedPlmnSearchInfo(VOS_FALSE, NAS_MMC_PLMN_SEARCH_SCENE_BUTT);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_PerformBufferedPlmnSearch_L1Main
 功能描述  : 处理缓存的指定搜网
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月25日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2012年06月07日
    作    者   : s46746
    修改内容   : For CS/PS mode 1，处理缓存的Availabe Timer超时，需要区分内部列表搜和指定搜网
  3.日    期   : 2013年1月11日
    作    者   : w00176964
    修改内容   : VoLTE_PhaseIII 项目修改:增加IMS不可用缓存的disable LTE场景的内部搜网触发条件
  4.日    期   : 2014年2月19日
    作    者   : s00217060
    修改内容   : coverity清理
*****************************************************************************/
VOS_VOID NAS_MMC_PerformBufferedPlmnSearch_L1Main(VOS_VOID)
{
    VOS_UINT32                          ulSpecPlmnSearchFlg;
    VOS_UINT32                          ulIsNeedPlmnSearch;
    VOS_UINT32                          ulIsNeedInterPlmnList;
    /* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-1-11, begin */
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32   enPlmnSearchScene;
    /* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-1-11, end */

    /* 如果注册失败不需要发起搜网,则判断是否有缓存的搜网标志 */
    if (VOS_FALSE == NAS_MMC_GetBufferedPlmnSearchFlg())
    {
        return;
    }

    ulIsNeedPlmnSearch    = NAS_MMC_IsAvailTimerExpiredTriggerPlmnSearch_L1Main();
    ulIsNeedInterPlmnList = NAS_MMC_IsAvailTimerExpiredTriggerInterPlmnList_L1Main();
    ulSpecPlmnSearchFlg   = NAS_MMC_GetSpecPlmnSearchState();
    /* Modified by s00217060 for coverity清理, 2014-02-19, begin */
    enPlmnSearchScene = NAS_MMC_GetBufferedPlmnSearchScene();

    if ((NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED == enPlmnSearchScene)
     && (VOS_TRUE == ulIsNeedPlmnSearch)
     && (VOS_TRUE == ulIsNeedInterPlmnList))
    {
        NAS_MMC_SndInterPlmnListReq();

        /* 触发搜网后就清除additional的值 */
        NAS_MMC_ClearAllRegAdditionalAction_L1Main();

        /* 触发搜网后同时清除CS/PS的注册尝试次数 */
        NAS_MMC_ClearAllRegAttemptCount_L1Main();
    }
    else
    {
        /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2014-1-11, begin */

        /* 当前非正常服务或在指定搜网状态或disable LTE时才处理缓存的指定搜网 */
        if ((VOS_FALSE                              == NAS_MMC_IsNormalServiceStatus())
         || (NAS_MMC_PLMN_SEARCH_SCENE_DISABLE_LTE  == enPlmnSearchScene)
         || (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING       == ulSpecPlmnSearchFlg))
        /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2014-1-11, end */
        {
            NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

            NAS_MMC_SndInterPlmnSearchReq(enPlmnSearchScene, VOS_NULL_PTR, 0);
        }
    }
    /* Modified by s00217060 for coverity清理, 2014-02-19, end */

    /* 清空缓存的搜网标志 */
    NAS_MMC_SetBufferedPlmnSearchInfo(VOS_FALSE, NAS_MMC_PLMN_SEARCH_SCENE_BUTT);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcGmmServiceRequestResultInd_L1Main
 功能描述  : 对GMM的GMMMMC_SERVICE_REQUEST_RESULT_IND消息的处理
 输入参数  : pstServiceRsltInd GMMMMC_SERVICE_REQUEST_RESULT_IND消息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月28日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2011年12月5日
    作    者   : z00161729
    修改内容   : V7R1 Phase IV调整,当前SYSCFG中L不在时，也需要向LMM通知ID_MMC_LMM_ACTION_RESULT_REQ
  3.日    期   : 2012年2月13日
    作    者   : w00167002
    修改内容   : DTS2011122704039:additional action值若为无效值NAS_MMC_ADDITIONAL_ACTION_BUTT
                  则不更新当前的additional action
  4.日    期   : 2013年12月24日
    作    者   : z00161729
    修改内容   : SVLTE支持NCELL搜网
*****************************************************************************/
VOS_VOID NAS_MMC_ProcGmmServiceRequestResultInd_L1Main(
    GMMMMC_SERVICE_REQUEST_RESULT_IND_STRU                 *pstServiceRsltInd
)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;

    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_GU_ACTION_RSLT_INFO_STRU                        stActionRslt;
#endif

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));

    enAdditionalAction      = NAS_MMC_ADDITIONAL_ACTION_BUTT;

    /* 根据Service Reqest Result 更新做不同处理 */
    if (GMM_MMC_ACTION_RESULT_SUCCESS == pstServiceRsltInd->enActionResult)
    {
        /* 更新PS的AdditionalAction */
        enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;

#if (FEATURE_ON == FEATURE_LTE)
        /* 当前SYSCFG中L不在时，也需要向LMM通知 ，给LMM发送Service requestResult结果消息处理*/
        stActionRslt.enProcType     = NAS_MML_PROC_SER;
        stActionRslt.enRegRst       = NAS_MML_REG_RESULT_SUCCESS;
        stActionRslt.enReqDomain    = NAS_MMC_REG_DOMAIN_PS;
        stActionRslt.enRstDomain    = NAS_MMC_REG_DOMAIN_PS;
        stActionRslt.enCnCause      = NAS_MML_REG_FAIL_CAUSE_NULL;
        stActionRslt.ulAttemptCount = 0;

        NAS_MMC_SndLmmRegActionResultReq(&stActionRslt);
#endif

    }
    else
    {
        enAdditionalAction = NAS_MMC_ProcPsServiceRegFail(pstServiceRsltInd);

#if (FEATURE_ON == FEATURE_LTE)
        /* 当前SYSCFG中L不在时，也需要向LMM通知，给LMM发送Service requestResult结果消息处理 */
        stActionRslt.enProcType     = NAS_MML_PROC_SER;
        stActionRslt.enRegRst       = NAS_MML_REG_RESULT_FAILURE;
        stActionRslt.enReqDomain    = NAS_MMC_REG_DOMAIN_PS;
        stActionRslt.enRstDomain    = NAS_MMC_REG_DOMAIN_PS;
        stActionRslt.enCnCause      = pstServiceRsltInd->enRegFailCause;
        stActionRslt.ulAttemptCount = 0;

        NAS_MMC_SndLmmRegActionResultReq(&stActionRslt);
#endif
    }

    /* AdditionalAction有效，更新PS的下一步的动作类型 */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enAdditionalAction )
    {
        NAS_MMC_SetPsRegAdditionalAction_L1Main(enAdditionalAction);
    }

    if (VOS_TRUE == NAS_MMC_IsNeedSndEplmn())
    {
        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndGuAsEquPlmnReq(&stSndEquPlmnInfo, NAS_MML_GetCurrNetRatType());
        NAS_MMC_SndOmEquPlmn();

        NAS_MMC_SndMsccEplmnInfoInd(&stSndEquPlmnInfo);
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcPsRegRslt_L1Main
 功能描述  : 对Ps注册结果的处理
 输入参数  : pstPsRegRsltInd PS注册结果消息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月28日
   作    者   : w00176964
   修改内容   : 新生成函数

 2.日    期   : 2011年11月21日
   作    者   : w00167002
   修改内容   : DTS2011111806904:手动模式下异系统重选,在EPLMN上注册被拒原因值
                 #17，导致EPLMN被清除，收到系统消息后，MMC转发给MM/GMM的系统
                 消息时会带FORB PLMN标志，导致T3211超时后，不进行注册。
                 修改方案是在上述情况下，则进行搜网回用户指定的PLMN。

 3.日    期   : 2011年11月28日
   作    者   : w00167002
   修改内容   : DTS2011112406707:若当前为假流程且当前的AdditionalAction不为
                初始无效值，则不更新当前的AdditionalAction的值，否则若当前为
                真流程或当前为假流程且AdditionalAction为初始无效值，则更新
                当前的AdditionalAction的值.
                修改原因:在ROAMING BROKER时候，设置1次失败,注册失败1次后，
                MMC需要搜网，但是MMC可能要等两个域的结果(如在选网状态机)，
                当收到系统消息的时候，假流程会更改MMC的AdditionalAction的值,
                导致ROMING BROKER特性失效。

  4.日    期   : 2011年12月5日
    作    者   : z00161729
    修改内容   : V7R1 Phase IV调整,当前SYSCFG中L不在时，也需要向LMM通知ID_MMC_LMM_ACTION_RESULT_REQ

 5.日    期   : 2011年12月17日
   作    者   : w00166186
   修改内容   : dts2011120603107，从一个正常服务小区重选到一个不支持GPRS的小区，不停发起LAU

 6.日    期   : 2012年1月3日
   作    者   : w00167002
   修改内容   : DTS2011122006209:g下PS ONLY注册成功_更改为CS后注册失败4次后未发起搜网
                统一调整注册ADDITIONAL ACTION的值，若是用户自定义的原因值(>=256)，则
                不保存注册结果。若当前支持L模，则注册原因值小于260时通知LMM当前的注册结果.
                调整假流程，MMC不需要知道MM/GMM上报的是否是真假流程。

  7.日    期   : 2012年1月6日
    作    者   : w00167002
    修改内容   : DTS2011122006209:删除DTS2011111806904在此函数中所作的修改，
                 将此改动的内容调整到处理OTHER CAUSE的函数中。
  8.日    期   : 2012年3月1日
    作    者   : w00176964
    修改内容   : DTS2012022407450:增加GMM的联合RAU/ATTACH类型，MMC转发给LMM
  9.日    期   : 2012年03月30日
    作    者   : l00130025
    修改内容   : DTS2012032307791,发给LMM注册结果,CombineReg时需要区分结果域
 10.日    期   : 2012年6月4日
    作    者   : l00171473
    修改内容   : DTS2012053003921, 用户手动指定网络的注册状态标志清理
 11.日    期   : 2012年6月8日
    作    者   : l00130025
    修改内容   : DTS2012060702423:Anycell驻留后，注册成功时，没有通知通知APS/CDS消息，无法数传
 12.日    期   : 2012年08月20日
    作    者   : l65478
    修改内容   : DTS2012081703289，手动搜网失败后关机，重新开机注册成功
                   后出服务区后不驻留EPLMN上
 13.日    期   : 2012年12月6日
    作    者   : s00217060
    修改内容   : DTS2012120410842:注册成功时，需要删除ForbPlmn,ForbLa,ForbGprs等信息
 14.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
 15.日    期   : 2013年12月24日
    作    者   : z00161729
    修改内容   : SVLTE支持NCELL搜网
 16.日    期   : 2014年01月10日
    作    者   : w00176964
    修改内容   : VoLTE_PhaseIII项目
 17.日    期   : 2014年04月9日
    作    者   : s00261364
    修改内容   : V3R360_eCall项目:增加服务状态上报处理
 18.日    期   : 2015年10月14日
    作    者   : c00318887
    修改内容   : DTS2015082002854: 漫游标记不准
*****************************************************************************/
VOS_VOID NAS_MMC_ProcPsRegRslt_L1Main(
    GMMMMC_PS_REG_RESULT_IND_STRU      *pstPsRegRsltInd
)
{
    NAS_MML_LAI_STRU                                       *pstLai         = VOS_NULL_PTR;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;
    /* Deleted by s00261364 for V3R360_eCall项目, 2014-4-10, begin */

    /* Deleted by s00261364 for V3R360_eCall项目, 2014-4-10, end */

    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_GU_ACTION_RSLT_INFO_STRU                        stActionRslt;
    NAS_MML_PROC_TYPE_ENUM_U32                              enProcType;

    /* 转换发送给L的proctype */
    enProcType = NAS_MML_PROC_BUTT;

    NAS_MMC_ConverGmmActionTypeToMml(pstPsRegRsltInd->enGmmActionType, &enProcType);


    NAS_MMC_ConvertGmmRegDomainToMmcDomain(pstPsRegRsltInd->enReqDomain, &stActionRslt.enReqDomain);

    NAS_MMC_ConvertGmmRegDomainToMmcDomain(pstPsRegRsltInd->enRsltDomain, &stActionRslt.enRstDomain);



#endif
    pstLai              = NAS_MML_GetCurrCampLai();

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));

    /* Deleted by s00261364 for V3R360_eCall项目, 2014-4-10, begin */

    /* Deleted by s00261364 for V3R360_eCall项目, 2014-4-10, end */

    if (GMM_MMC_ACTION_RESULT_SUCCESS == pstPsRegRsltInd->enActionResult)
    {
        enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;

        /* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-10, begin */
        /* 保存注册结果消息 */
        NAS_MMC_SaveRegRsltCtx(GMM_MMC_PS_REG_RESULT_IND, pstPsRegRsltInd);
        /* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-10, end */

        /* 根据注册结果更新注册信息表 */
        NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_PS, NAS_MML_REG_FAIL_CAUSE_NULL);

        NAS_MMC_ClearHplmnRejDomainInfo(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_PS);

        if (VOS_TRUE == NAS_MML_GetKeepCsForbInfoCfg())
        {
            /* 只删除Forb GPRS PLMN信息，CS相关FORB信息依然保留 */
            NAS_MML_DelForbGprsPlmn(&(pstLai->stPlmnId));
        }
        else
        {
            /* 注册成功时，需要删除ForbPlmn,ForbLa,ForbGprs等信息 */
            NAS_MMC_DelForbInfo_GuRegRsltSucc(NAS_MMC_REG_DOMAIN_PS);
        }


        NAS_MMC_NotifyModeChange(NAS_MML_GetCurrNetRatType(),
                             NAS_MML_GetSimPsRegStatus());


        NAS_MMC_SetUserSpecPlmnRegisterStatus(VOS_TRUE);

        NAS_MMC_UpdateServiceState_RegSucc(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_NORMAL_SERVICE);

#if   (FEATURE_ON == FEATURE_LTE)
        /* 当前SYSCFG中L不在时，需要向LMM通知 */
        /* 假流程不通知给LMM */
        if ( VOS_TRUE == NAS_MML_IsRegFailCauseNotifyLmm(pstPsRegRsltInd->enRegFailCause) )
        {
            stActionRslt.enProcType     = enProcType;
            stActionRslt.enRegRst       = NAS_MML_REG_RESULT_SUCCESS;
            stActionRslt.enCnCause      = NAS_MML_REG_FAIL_CAUSE_NULL;
            stActionRslt.ulAttemptCount = 0;

            NAS_MMC_SndLmmRegActionResultReq(&stActionRslt);
        }
#endif

        /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, begin */
        NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_PS, VOS_TRUE, pstPsRegRsltInd->enRegFailCause);
        /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, end */
    }
    else
    {
        enAdditionalAction = NAS_MMC_ProcPsRegFail(GMM_MMC_PS_REG_RESULT_IND,
                                                   pstPsRegRsltInd);

        /* 小于 NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE的拒绝原因是与网侧实际交互得到的值，需要通知LMM */
        if ( VOS_TRUE == NAS_MML_IsNetworkRegFailCause(pstPsRegRsltInd->enRegFailCause) )
        {
            /* 只在跟网测真实发生交互的时候才更新注册信息表 */
            NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_PS, pstPsRegRsltInd->enRegFailCause);
        }

        NAS_MMC_UpdateUserSpecPlmnRegisterStatusWhenRegFail(pstPsRegRsltInd->enRegFailCause);

#if   (FEATURE_ON == FEATURE_LTE)

        /* 小于 NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE的拒绝原因是UE尝试发起注册的原因值，需要通知LMM */
        if ( VOS_TRUE == NAS_MML_IsRegFailCauseNotifyLmm(pstPsRegRsltInd->enRegFailCause) )
        {
            stActionRslt.enProcType     = enProcType;
            stActionRslt.enRegRst       = NAS_MML_REG_RESULT_FAILURE;
            stActionRslt.enCnCause      = pstPsRegRsltInd->enRegFailCause;
            stActionRslt.ulAttemptCount = pstPsRegRsltInd->ulRegCounter;

            NAS_MMC_SndLmmRegActionResultReq(&stActionRslt);
        }
#endif

    }

    /* AdditionalAction有效，更新PS的下一步的动作类型 */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enAdditionalAction )
    {
        NAS_MMC_SetPsRegAdditionalAction_L1Main(enAdditionalAction);
    }

    NAS_MMC_SetPsRegAttemptCount_L1Main(pstPsRegRsltInd->ulRegCounter);

    if (VOS_TRUE == NAS_MMC_IsNeedSndEplmn())
    {
        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndGuAsEquPlmnReq(&stSndEquPlmnInfo, NAS_MML_GetCurrNetRatType());
        NAS_MMC_SndOmEquPlmn();

        NAS_MMC_SndMsccEplmnInfoInd(&stSndEquPlmnInfo);

        /* 通知CSS GEO信息 */
        NAS_MMC_SndCssCurrGeoInd(VOS_TRUE, stSndEquPlmnInfo.ucEquPlmnNum, stSndEquPlmnInfo.astEquPlmnAddr);
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ProcCsRegRslt_L1Main
 功能描述  : 对Cs注册结果的处理
 输入参数  : pstCsRegRsltInd CS注册结果消息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月28日
   作    者   : w00176964
   修改内容   : 新生成函数

 2.日    期   : 2011年11月21日
   作    者   : w00167002
   修改内容   : DTS2011111806904:手动模式下异系统重选,在EPLMN上注册被拒原因值
                 #17，导致EPLMN被清除，收到系统消息后，MMC转发给MM/GMM的系统
                 消息时会带FORB PLMN标志，导致T3211超时后，不进行注册。
                 修改方案是在上述情况下，则进行搜网回用户指定的PLMN。

 3.日    期   : 2011年11月28日
   作    者   : w00167002
   修改内容   : DTS2011112406707:若当前为假流程且当前的AdditionalAction不为
                初始无效值，则不更新当前的AdditionalAction的值，否则若当前为
                真流程或当前为假流程且AdditionalAction为初始无效值，则更新
                当前的AdditionalAction的值.
                修改原因:在ROAMING BROKER时候，设置1次失败,注册失败1次后，
                MMC需要搜网，但是MMC可能要等两个域的结果(如在选网状态机)，
                当收到系统消息的时候，假流程会更改MMC的AdditionalAction的值,
                导致ROMING BROKER特性失效。
  4.日    期   : 2011年12月5日
    作    者   : z00161729
    修改内容   : V7R1 Phase IV调整,当前SYSCFG中L不在时，也需要向LMM通知ID_MMC_LMM_ACTION_RESULT_REQ

  5.日    期   : 2012年1月3日
    作    者   : w00167002
    修改内容   : DTS2011122006209:g下PS ONLY注册成功_更改为CS后注册失败4次后未发起搜网
                  统一调整注册ADDITIONAL ACTION的值，若是用户自定义的原因值(>=256)，则
                  不保存注册结果。若当前支持L模，则注册原因值小于260时通知LMM.

  6.日    期   : 2012年1月6日
    作    者   : w00167002
    修改内容   : DTS2011122006209:删除DTS2011111806904在此函数中所作的修改，
                 将此改动的内容调整到处理OTHER CAUSE的函数中。
  7.日    期   : 2012年1月20日
    作    者   : w00167002
    修改内容   : DTS2011122006209:将注册失败的消息通知给处理注册结果函数，
                  能进行更好的扩展.
  8.日    期   : 2012年3月1日
    作    者   : w00176964
    修改内容   : DTS2012022407450:联合ATTACH时,MM不能通知LMM此时CS的注册结果，否则导致TAU的类型不正确
  9.日    期   : 2012年6月4日
    作    者   : l00171473
    修改内容   : DTS2012053003921, 用户手动指定网络的注册状态标志清理
 10.日    期   : 2012年08月20日
    作    者   : l65478
    修改内容   : DTS2012081703289，手动搜网失败后关机，重新开机注册成功
                   后出服务区后不驻留EPLMN上
 11.日    期   : 2012年12月6日
    作    者   : s00217060
    修改内容   : DTS2012120410842:注册成功时，需要删除ForbPlmn,ForbLa,ForbGprs等信息
 12.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
 13.日    期   : 2013年12月24日
    作    者   : z00161729
    修改内容   : SVLTE支持NCELL搜网
 14.日    期   : 2014年01月10日
    作    者   : w00176964
    修改内容   : VoLTE_PhaseIII项目
 15.日    期   : 2014年04月9日
    作    者   : s00261364
    修改内容   : V3R360_eCall项目:增加服务状态上报处理
 16.日    期   : 2014年11月3日
    作    者   : z00161729
    修改内容   : 开机漫游搜网项目修改
*****************************************************************************/
VOS_VOID NAS_MMC_ProcCsRegRslt_L1Main(
    MMMMC_CS_REG_RESULT_IND_STRU       *pstCsRegRsltInd
)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;

    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_GU_ACTION_RSLT_INFO_STRU                        stActionRslt;
#endif

    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo = VOS_NULL_PTR;
    pstDPlmnNPlmnCfgInfo  = NAS_MMC_GetDPlmnNPlmnCfgInfo();

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-5-4, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-5-4, end */

    if (MM_MMC_LU_RESULT_SUCCESS == pstCsRegRsltInd->enLuResult)
    {
        enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;

        /* 根据注册结果更新注册信息表 */
        NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_CS, NAS_MML_REG_FAIL_CAUSE_NULL);

        /* 更新DPLMN NPLMN列表 */
        if (VOS_TRUE == NAS_MMC_IsRoam())
        {
            NAS_MMC_UpdateDPlmnNPlmnList(NAS_MML_GetCurrCampLai(), NAS_MMC_REG_DOMAIN_CS, NAS_MMC_MAX_CFG_DPLMN_NUM, &pstDPlmnNPlmnCfgInfo->usDplmnListNum,pstDPlmnNPlmnCfgInfo->astDPlmnList);
            NAS_MMC_DeleteDPlmnNPlmnList(NAS_MML_GetCurrCampLai(), NAS_MMC_REG_DOMAIN_CS, &pstDPlmnNPlmnCfgInfo->usNplmnListNum, pstDPlmnNPlmnCfgInfo->astNPlmnList);
            NAS_MMC_WriteSelfLearnDplmnNplmnToNvim(pstDPlmnNPlmnCfgInfo);

            NAS_MMC_LogDplmnNplmnList();
        }
        /* 对Hplmn的Rej Lai信息的清除 */
        NAS_MMC_ClearHplmnRejDomainInfo(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_CS);

        /* 注册成功时，需要删除ForbPlmn,ForbLa,ForbGprs等信息 */
        NAS_MMC_DelForbInfo_GuRegRsltSucc(NAS_MMC_REG_DOMAIN_CS);

        NAS_MMC_SetUserSpecPlmnRegisterStatus(VOS_TRUE);

        NAS_MMC_UpdateCsRegStateCsRegSucc();

        /* Added by s00261364 for V3R360_eCall项目, 2014-4-3, begin */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_NORMAL_SERVICE);
        /* Added by s00261364 for V3R360_eCall项目, 2014-4-3, end */


#if   (FEATURE_ON == FEATURE_LTE)

        /* 联合注册时不通知LMM此时LU的结果 */
        if ((VOS_TRUE  == NAS_MML_IsRegFailCauseNotifyLmm(pstCsRegRsltInd->enRegFailCause))
         && (VOS_FALSE == pstCsRegRsltInd->ucIsComBined))
        {
            /* 当前SYSCFG中L不在时，需要向LMM通知 */
            stActionRslt.enProcType     = NAS_MML_PROC_LAU;
            stActionRslt.enRegRst       = NAS_MML_REG_RESULT_SUCCESS;
            stActionRslt.enReqDomain    = NAS_MMC_REG_DOMAIN_CS;
            stActionRslt.enRstDomain    = NAS_MMC_REG_DOMAIN_CS;
            stActionRslt.enCnCause      = NAS_MML_REG_FAIL_CAUSE_NULL;
            stActionRslt.ulAttemptCount = 0;

            NAS_MMC_SndLmmRegActionResultReq(&stActionRslt);
        }


#endif

        /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, begin */
        NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_CS, VOS_TRUE, pstCsRegRsltInd->enRegFailCause);
        /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, end */
    }
    else
    {
        enAdditionalAction = NAS_MMC_ProcCsRegFail(MM_MMC_CS_REG_RESULT_IND,
                                                   pstCsRegRsltInd);

        if ( VOS_TRUE == NAS_MML_IsNetworkRegFailCause(pstCsRegRsltInd->enRegFailCause) )
        {
            /* 只在跟网测真实发生交互的时候才更新注册信息表 */
            NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_CS, pstCsRegRsltInd->enRegFailCause);

            /* 更新DPLMN NPLMN列表 */
            if (VOS_TRUE == NAS_MMC_IsRoam())
            {
                NAS_MMC_UpdateDPlmnNPlmnList(NAS_MML_GetCurrCampLai(), NAS_MMC_REG_DOMAIN_CS, NAS_MMC_MAX_CFG_NPLMN_NUM, &pstDPlmnNPlmnCfgInfo->usNplmnListNum,pstDPlmnNPlmnCfgInfo->astNPlmnList);
                NAS_MMC_DeleteDPlmnNPlmnList(NAS_MML_GetCurrCampLai(), NAS_MMC_REG_DOMAIN_CS, &pstDPlmnNPlmnCfgInfo->usDplmnListNum, pstDPlmnNPlmnCfgInfo->astDPlmnList);
                NAS_MMC_WriteSelfLearnDplmnNplmnToNvim(pstDPlmnNPlmnCfgInfo);

                NAS_MMC_LogDplmnNplmnList();
            }

        }

        NAS_MMC_UpdateUserSpecPlmnRegisterStatusWhenRegFail(pstCsRegRsltInd->enRegFailCause);

#if   (FEATURE_ON == FEATURE_LTE)

        /* 小于 NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE的拒绝原因是UE尝试发起注册的原因值，需要通知LMM */
        /* 联合注册时不通知LMM此时LU的结果 */
        if ((VOS_TRUE  == NAS_MML_IsRegFailCauseNotifyLmm(pstCsRegRsltInd->enRegFailCause))
         && (VOS_FALSE == pstCsRegRsltInd->ucIsComBined))
        {
            /* 当前SYSCFG中L不在时，需要向LMM通知 */
            stActionRslt.enProcType     = NAS_MML_PROC_LAU;
            stActionRslt.enRegRst       = NAS_MML_REG_RESULT_FAILURE;
            stActionRslt.enReqDomain    = NAS_MMC_REG_DOMAIN_CS;
            stActionRslt.enRstDomain    = NAS_MMC_REG_DOMAIN_CS;
            stActionRslt.enCnCause      = pstCsRegRsltInd->enRegFailCause;
            stActionRslt.ulAttemptCount = pstCsRegRsltInd->ulLuAttemptCnt;

            NAS_MMC_SndLmmRegActionResultReq(&stActionRslt);
        }
#endif

    }

    /* AdditionalAction有效，更新CS的下一步的动作类型 */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enAdditionalAction )
    {
        NAS_MMC_SetCsRegAdditionalAction_L1Main(enAdditionalAction);
    }

    /* 更新CS注册的尝试次数 */
    NAS_MMC_SetCsRegAttemptCount_L1Main(pstCsRegRsltInd->ulLuAttemptCnt);

    if (VOS_TRUE == NAS_MMC_IsNeedSndEplmn())
    {
        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndGuAsEquPlmnReq(&stSndEquPlmnInfo, NAS_MML_GetCurrNetRatType());
        NAS_MMC_SndOmEquPlmn();

        NAS_MMC_SndMsccEplmnInfoInd(&stSndEquPlmnInfo);

        /* 通知CSS GEO信息 */
        NAS_MMC_SndCssCurrGeoInd(VOS_TRUE, stSndEquPlmnInfo.ucEquPlmnNum, stSndEquPlmnInfo.astEquPlmnAddr);
    }

    return;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_AdjustOtherCauseAdditionalAction_OnPlmn
 功能描述  : OnPlmn注册失败时，对原因值OTHER CAUSE的ADDITIONAL调整
 输入参数  : penAdditionalAction: 注册原因值映射的ADDITIONAL ACTION
 输出参数  : penAdditionalAction: 在满足手动模式下，当前Plmn不是用户指定的PLMN,
             且当前PLMN不在EPlmn列表里，且当前的Additional值为WAIT_REG_ATTEMPT，
             则需要进行搜网
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年11月21日
   作    者   : w00167002
   修改内容   : DTS2011111806904:手动模式下异系统重选,在EPLMN上注册被拒原因值
                 #17等，导致EPLMN被清除，收到系统消息后，MMC转发给MM/GMM的系统
                 消息时会带FORB PLMN标志，导致T3211超时后，MM不进行注册。
                 修改方案是在上述情况下，在EPLMN上注册失败(原因值为OTHER CAUSE)
                 则尝试搜网回用户指定的PLMN，而不在当前网络上继续尝试注册。
 2.日    期   : 2011年11月24日
   作    者   : w00167002
   修改内容   : DTS2011112405567:原有的函数名NAS_MML_IsPlmnIdInDestPlmnList
               更改为NAS_MML_IsBcchPlmnIdInDestSimPlmnList,用于明确判断
               网络的类型，否则网络比较可能会出错
*****************************************************************************/
VOS_VOID NAS_MMC_AdjustOtherCauseAdditionalAction_OnPlmn(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penAdditionalAction
)
{
    NAS_MML_LAI_STRU                   *pstCurrentLai       = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU          *pstEplmnInfo        = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU         *pstUserSpecPlmn     = VOS_NULL_PTR;
    VOS_UINT32                          ulInEplmnListFlag;
    VOS_UINT32                          ulUserSpecPlmnFlag;

    pstCurrentLai      = NAS_MML_GetCurrCampLai();

    /* 判断当前网络是否是用户指定的网络 */
    pstUserSpecPlmn    = NAS_MMC_GetUserSpecPlmnId();
    ulUserSpecPlmnFlag = NAS_MML_CompareBcchPlmnwithSimPlmn(&(pstCurrentLai->stPlmnId),
                                                &(pstUserSpecPlmn->stPlmnId));

    /* 判断当前网络是否在EPlmn列表里 */
    pstEplmnInfo       = NAS_MML_GetEquPlmnList();

    ulInEplmnListFlag  = NAS_MML_IsBcchPlmnIdInDestSimPlmnList(&(pstCurrentLai->stPlmnId),
                                              pstEplmnInfo->ucEquPlmnNum,
                                              pstEplmnInfo->astEquPlmnAddr);

    /* 手动模式下，当前Plmn不是用户指定的PLMN,且当前PLMN不在EPlmn列表里，
       且当前域的Additional值为WAIT_REG_ATTEMPT，则需要进行搜网 */
    if ( (NAS_MMC_PLMN_SELECTION_MODE_MANUAL         == NAS_MMC_GetPlmnSelectionMode())
      && (VOS_FALSE                                  == ulUserSpecPlmnFlag)
      && (VOS_FALSE                                  == ulInEplmnListFlag)
      && (NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT == *penAdditionalAction) )
    {
        *penAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
    }

    return;
}

#if   (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_MMC_ProcLmmEpsOnlyAttachInd_OnPlmn
 功能描述  : Lmm attach结果的处理函数
 输入参数  : pstLmmAttachIndMsg L的ATTACH消息
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月28日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2011年12月5日
    作    者   : z00161729
    修改内容   : V7R1 phaseIV修改合并原NAS_MMC_HPLMN_REG_REJ_STRU和NAS_MMC_PLMN_REG_INFO_STRU
  3.日    期   : 2011年12月14日
    作    者   : w00176964
    修改内容   : V7R1 phaseIV调整:EPS单域注册假流程调整

  4.日    期   : 2011年12月15日
    作    者   : w00167002
    修改内容   : DTS2011121307570: MMC没有维护LMM的EPLMN信息，现在统一调整
                  ATTACH/TAU/DETACH/SERVICE中被拒时EPLMN的维护。
                  将函数名由NAS_MMC_ProcEpsRegFail更改为NAS_MMC_ProcEpsAttachRegFail
                  调用ATTACH的注册原因值表进行处理。
  5.日    期   : 2012年1月8日
    作    者   : z00161729
    修改内容   : V7R1 phaseIV调整:EPS单域注册假流程调整
  6.日    期   : 2012年2月4日
    作    者   : w00167002
    修改内容   : DTS2011122704039:将注册结果类型以及注册消息传递给处理注册结果
                  函数，扩展注册结果函数的处理能力。
                  additional action值若为无效值NAS_MMC_ADDITIONAL_ACTION_BUTT
                 则不更新当前的additional action
  7.日    期   : 2012年4月25日
    作    者   : w00176964
    修改内容   : GUL_BG项目调整
  8.日    期   : 2012年06月01日
    作    者   : sunxibo /46746
    修改内容   : Added for V7R1 C50 CS/PS mode 1
  9.日    期   : 2012年6月4日
    作    者   : l00171473
    修改内容   : DTS2012053003921, 用户手动指定网络的注册状态标志清理
  9.日    期   : 2012年6月8日
    作    者   : l00130025
    修改内容   : DTS2012060702423:Anycell驻留后，注册成功时，没有通知通知APS/CDS消息，无法数传
 10.日    期   : 2012年08月20日
    作    者   : l65478
    修改内容   : DTS2012081703289，手动搜网失败后关机，重新开机注册成功
                   后出服务区后不驻留EPLMN上
  11.日    期   : 2012年8月21日
     作    者   : z00161729
     修改内容   : DCM定制需求和遗留问题修改DTS2012090401249

  12.日    期   : 2012年09月12日
     作    者   : z00161729
     修改内容  : DTS2012082904888：cs ps mode1，on plmn、plmn list、bg plmn search状态机在eps only注册成功未调用NAS_MMC_IsNeedDisableL_EpsOnlyRegSucc判断是否需要disable lte
  13.日    期   : 2012年12月6日
     作    者   : s00217060
     修改内容   : DTS2012120410842:注册成功时，需要删除ForbPlmn,ForbGprs等信息
  14.日    期   : 2013年3月30日
     作    者   : l00167671
     修改内容   : 主动上报AT命令控制下移至C核
  15.日    期   : 2013年05月08日
     作    者   : s46746
     修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  16.日    期   : 2013年12月10日
     作    者   : w00176964
     修改内容   : VoLTE_PhaseIII 项目:修改Disable L模的逻辑
  17.日    期   : 2014年5月6日
     作    者   : z00161729
     修改内容   : DTS2014050602850:l下联合注册eps成功，cs注册被#18拒绝，disable lte到gu下搜网注册成功，后指定搜l cs注册被#18拒绝的网络，l发起eps单域注册成功，mmc没有disable lte
  18.日    期   : 2014年5月5日
     作    者   : w00242748
     修改内容   : DTS2014043000311:注册状态服务状态不一致，将MMC中报服务状态的场景，都加
                  注册状态的上报。
  19.日    期   : 2015年4月18日
     作    者   : z00161729
     修改内容   : 24301 R11 CR升级项目修改
  20.日    期   : 2015年02月11日
     作    者   : l00305157
     修改内容   : Service_State_Optimize_PhaseII 项目修改
                    MMC接收到LMM模块注册结果ATTACH (EPS ONLY)成功，上报注册状态
  21.日    期   : 2015年06月09日
     作    者   : l00305157
     修改内容   : Service_State_Optimize_PhaseII 项目修改
                    MMC接收到LMM模块注册结果，先更新EPLMN LIST，在处理注册状态的上报
*****************************************************************************/
VOS_VOID  NAS_MMC_ProcLmmEpsOnlyAttachInd_OnPlmn(
    LMM_MMC_ATTACH_IND_STRU            *pstLmmAttachIndMsg
)
{
    VOS_UINT32                                              ulEquPlmnNum;
    MMC_LMM_PLMN_ID_STRU                                   *pstLmmEquPlmnList = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stLEplmnInfo;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enRegRsltCause;

    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, begin */
    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, end */
    VOS_UINT8                                               ucSimCsRegStatus;

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));

    NAS_MMC_ConverLmmAttachRsltToMMLCause(pstLmmAttachIndMsg,&enRegRsltCause);

    if (MMC_LMM_ATT_RSLT_SUCCESS == pstLmmAttachIndMsg->ulAttachRslt)
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_NORMAL_CAMP_ON);

        enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;

        NAS_MMC_SaveRegRsltCtx(LMM_MMC_ATTACH_IND, pstLmmAttachIndMsg);

        /* 根据注册结果更新注册信息表 */
        NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_EPS, NAS_MML_REG_FAIL_CAUSE_NULL);

        /*注意: 需要先更新EPLMN LIST，在处理注册状态的上报,因为NAS_MMC_UpdatePsRegStatePsRegSucc()函数中会根据EPLMN LIST上报注册状态 */
        /* 更新EPLMN */
        if ( VOS_TRUE == pstLmmAttachIndMsg->bitOpEplmn)
        {
            ulEquPlmnNum        = pstLmmAttachIndMsg->stEplmnList.ulPlmnNum;
            pstLmmEquPlmnList   = pstLmmAttachIndMsg->stEplmnList.astEplmnList;

            /* LMM PLMN ID格式转换为MMC的PLMN ID的格式  */
            NAS_MMC_ConvertLmmPlmnToGUNasPlmn(ulEquPlmnNum, pstLmmEquPlmnList, (stLEplmnInfo.astEquPlmnAddr));

            /* 将EPLMN信息保存在内存中 */
            NAS_MML_SaveEquPlmnList(ulEquPlmnNum, (stLEplmnInfo.astEquPlmnAddr));

            NAS_MMC_WriteEplmnNvim();
        }

        NAS_MMC_UpdateServiceState_RegSucc(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_NORMAL_SERVICE);

        /* EPS单域注册成功时，需要删除ForbPlmn,ForbGprs等信息 */
        NAS_MMC_DelForbInfo_LmmAttRsltSucc(VOS_NULL_PTR, NAS_MMC_IsEpsEmergencyAttachType(pstLmmAttachIndMsg->ulReqType));

        /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, begin */
        /* 如果CS允许注册而且CS卡有效则更改CS注册状态为NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
        ucSimCsRegStatus = NAS_MML_GetSimCsRegStatus();
        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (VOS_TRUE == ucSimCsRegStatus))
        {
            NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_EPS_ONLY_ATTACH);

            NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        }
        /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, end */


        /*注意: 需要先更新EPLMN LIST，在处理注册状态的上报,因为NAS_MMC_UpdatePsRegStatePsRegSucc()函数中会根据EPLMN LIST上报注册状态 */
        NAS_MMC_UpdateGURegRlstRPlmnIdInNV();


        NAS_MMC_NotifyModeChange(NAS_MML_GetCurrNetRatType(),
                                 NAS_MML_GetSimPsRegStatus());


        NAS_MMC_SetUserSpecPlmnRegisterStatus(VOS_TRUE);

        /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, begin */
        NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_PS, VOS_TRUE, NAS_MML_REG_FAIL_CAUSE_NULL);
        /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, end */
    }
    else if ((MMC_LMM_ATT_RSLT_FAILURE == pstLmmAttachIndMsg->ulAttachRslt)
          && (VOS_FALSE == pstLmmAttachIndMsg->bitOpAtmpCnt))
    {
        /* LNAS后续还有注册尝试流程-这里继续等待下 */
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT);

        NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_EPS_ONLY_ATTACH);

        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS,NAS_MMC_LIMITED_SERVICE);
        enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;

        /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, begin */
        NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_PS, VOS_FALSE, NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);
        /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, end */
    }
    else
    {
        enAdditionalAction= NAS_MMC_ProcEpsAttachRegFail(LMM_MMC_ATTACH_IND, pstLmmAttachIndMsg);

        NAS_MMC_UpdateUserSpecPlmnRegisterStatusWhenRegFail(enRegRsltCause);
    }

    /* AdditionalAction有效，更新EPS的下一步的动作类型 */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enAdditionalAction )
    {
        NAS_MMC_SetPsRegAdditionalAction_L1Main(enAdditionalAction);
    }

    if (VOS_TRUE == NAS_MMC_IsNeedSndEplmn())
    {
        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, begin */
        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildSndLmmEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndLmmEquPlmnReq(&stSndEquPlmnInfo);
        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, end */

        NAS_MMC_SndOmEquPlmn();

        /* 通知CSS GEO信息 */
        NAS_MMC_SndCssCurrGeoInd(VOS_TRUE, stSndEquPlmnInfo.ucEquPlmnNum, stSndEquPlmnInfo.astEquPlmnAddr);
    }

    /* 设置PS的注册尝试次数 */
    if (VOS_TRUE == pstLmmAttachIndMsg->bitOpAtmpCnt)
    {
        NAS_MMC_SetPsRegAttemptCount_L1Main(pstLmmAttachIndMsg->ulAttemptCount);
    }

    return ;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcLmmAttachInd_OnPlmn
 功能描述  : Lmm attach结果的处理函数
 输入参数  : pstLmmAttachIndMsg L的ATTACH消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月30日
    作    者   : z00161729
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_ProcLmmAttachInd_OnPlmn(
    LMM_MMC_ATTACH_IND_STRU            *pstLmmAttachIndMsg
)
{
    switch (pstLmmAttachIndMsg->ulReqType)
    {
        case MMC_LMM_ATT_TYPE_COMBINED_EPS_IMSI:

            /* 处理lmm的联合attach结果 */
            NAS_MMC_ProcLmmCombinedAttachInd_OnPlmn(pstLmmAttachIndMsg);
            break;

        case MMC_LMM_ATT_TYPE_EPS_ONLY:

            /* 处理lmm的非联合attach，EPS only注册的结果 */
            NAS_MMC_ProcLmmEpsOnlyAttachInd_OnPlmn(pstLmmAttachIndMsg);
            break;

        case MMC_LMM_ATT_TYPE_EPS_EMERGENCY:

            /* 暂不支持未实现 */
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcLmmAttachInd_OnPlmn:Unsupported attach req type!");
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcLmmAttachInd_OnPlmn:Unexpected attach req type!");
            break;

    }
    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ProcLmmEpsOnlyTauResultInd_OnPlmn
 功能描述  : Lmm TAU结果的处理函数
 输入参数  : pstLmmTauIndMsg L的TAU消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月28日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2011年12月5日
    作    者   : z00161729
    修改内容   : V7R1 phaseIV修改合并原NAS_MMC_HPLMN_REG_REJ_STRU和NAS_MMC_PLMN_REG_INFO_STRU
  3.日    期   : 2011年12月14日
    作    者   : w00176964
    修改内容   : V7R1 phaseIV调整:EPS单域注册假流程调整
  4.日    期   : 2011年12月15日
    作    者   : w00167002
    修改内容   : DTS2011121307570: MMC没有维护LMM的EPLMN信息，现在统一调整
                  ATTACH/TAU/DETACH/SERVICE中被拒时EPLMN的维护。
                  将函数名由NAS_MMC_ProcEpsRegFail更改为NAS_MMC_ProcEpsTauRegFail
                  调用TAU的注册原因值表进行处理
  5.日    期   : 2012年1月8日
    作    者   : z00161729
    修改内容   : V7R1 phaseIV调整:EPS单域注册假流程调整
  6.日    期   : 2012年2月4日
    作    者   : w00167002
    修改内容   : DTS2011122704039:将注册结果类型以及注册消息传递给处理注册结果
                  函数，扩展注册结果函数的处理能力。
                  additional action值若为无效值NAS_MMC_ADDITIONAL_ACTION_BUTT
                 则不更新当前的additional action
  7.日    期   : 2012年4月25日
    作    者   : w00176964
    修改内容   : GUL_BG项目调整
  8.日    期   : 2012年06月01日
    作    者   : sunxibo /46746
    修改内容   : Added for V7R1 C50 CS/PS mode 1
  9.日    期   : 2012年6月4日
    作    者   : l00171473
    修改内容   : DTS2012053003921, 用户手动指定网络的注册状态标志清理
 10.日    期   : 2012年6月8日
    作    者   : l00130025
    修改内容   : DTS2012060702423:Anycell驻留后，注册成功时，没有通知通知APS/CDS消息，无法数传
 11.日    期   : 2012年08月20日
    作    者   : l65478
    修改内容   : DTS2012081703289，手动搜网失败后关机，重新开机注册成功
                   后出服务区后不驻留EPLMN上
 12.日    期   : 2012年8月21日
    作    者   : z00161729
    修改内容   : DCM定制需求和遗留问题修改DTS2012090401249
 13.日    期   : 2012年09月12日
    作    者   : z00161729
    修改内容   : DTS2012082904888：cs ps mode1，on plmn、plmn list、bg plmn search状态机在eps only注册成功未调用NAS_MMC_IsNeedDisableL_EpsOnlyRegSucc判断是否需要disable lte
 14.日    期   : 2012年12月6日
    作    者   : s00217060
    修改内容   : DTS2012120410842:注册成功时，需要删除ForbPlmn,ForbGprs等信息
 15.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
 16.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
 17.日    期   : 2013年12月10日
     作    者  : w00176964
     修改内容  : VoLTE_PhaseIII 项目:修改Disable L模的逻辑
 18.日    期   : 2014年5月6日
    作    者   : z00161729
    修改内容   : DTS2014050602850:l下联合注册eps成功，cs注册被#18拒绝，disable lte到gu下搜网注册成功，后指定搜l cs注册被#18拒绝的网络，l发起eps单域注册成功，mmc没有disable lte
 19.日    期   : 2014年5月5日
    作    者   : w00242748
    修改内容   : DTS2014043000311:注册状态服务状态不一致，将MMC中报服务状态的场景，都加
                 注册状态的上报。
 20.日    期   : 2014年5月14日
    作    者   : w00242748
    修改内容   : DTS2014051206381:枚举值使用不对
 21.日    期   : 2015年4月18日
    作    者   : z00161729
    修改内容   : 24301 R11 CR升级项目修改
 22.日    期   : 2015年02月11日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseII 项目修改
                    MMC接收到LMM模块注册结果(EPS ONLY)成功，上报注册状态
 23.日    期   : 2015年06月09日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseII 项目修改
                    MMC接收到LMM模块注册结果，先更新EPLMN LIST，在处理注册状态的上报
 24.日    期   : 2015年10月14日
    作    者   : c00318887
    修改内容   : DTS2015082002854: 漫游标记不准
*****************************************************************************/
VOS_VOID  NAS_MMC_ProcLmmEpsOnlyTauResultInd_OnPlmn(
    LMM_MMC_TAU_RESULT_IND_STRU        *pstLmmTauIndMsg
)
{
    VOS_UINT32                                              ulEquPlmnNum;
    MMC_LMM_PLMN_ID_STRU                                   *pstLmmEquPlmnList = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stLEplmnInfo;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enRegRsltCause;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;

    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, begin */
    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, end */
    VOS_UINT8                                               ucSimCsRegStatus;

    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                enCsRegAdditionalAction;

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));

    NAS_MMC_ConverTauResultToMMLCause(pstLmmTauIndMsg, &enRegRsltCause);

    if (MMC_LMM_TAU_RSLT_SUCCESS == pstLmmTauIndMsg->ulTauRst)
    {
        enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;

        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_NORMAL_CAMP_ON);

        NAS_MMC_SaveRegRsltCtx(LMM_MMC_TAU_RESULT_IND, pstLmmTauIndMsg);

        /* 根据注册结果更新注册信息表 */
        NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_EPS, NAS_MML_REG_FAIL_CAUSE_NULL);

        /*注意: 需要先更新EPLMN LIST，在处理注册状态的上报,因为NAS_MMC_UpdatePsRegStatePsRegSucc()函数中会根据EPLMN LIST上报注册状态 */
        /* 更新EPLMN */
        if ( VOS_TRUE == pstLmmTauIndMsg->bitOpEplmn)
        {
            ulEquPlmnNum        = pstLmmTauIndMsg->stEplmnList.ulPlmnNum;
            pstLmmEquPlmnList   = pstLmmTauIndMsg->stEplmnList.astEplmnList;

            NAS_MMC_ConvertLmmPlmnToGUNasPlmn(ulEquPlmnNum, pstLmmEquPlmnList, stLEplmnInfo.astEquPlmnAddr);

            /* 将EPLMN信息保存在内存中 */
            NAS_MML_SaveEquPlmnList(ulEquPlmnNum, (stLEplmnInfo.astEquPlmnAddr));

            NAS_MMC_WriteEplmnNvim();
        }

        NAS_MMC_UpdateServiceState_RegSucc(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_NORMAL_SERVICE);

        /* EPS单域注册成功时，需要删除ForbPlmn,ForbGprs等信息 */
        NAS_MMC_DelForbInfo_LmmAttRsltSucc(VOS_NULL_PTR, VOS_FALSE);

        /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, begin */
        /* 如果CS允许注册而且CS卡有效则更改CS注册状态为NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
        ucSimCsRegStatus = NAS_MML_GetSimCsRegStatus();

        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (VOS_TRUE == ucSimCsRegStatus))
        {
            NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_EPS_ONLY_ATTACH);

            NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        }
        /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, end */

        /*注意: 需要先更新EPLMN LIST，在处理注册状态的上报,因为NAS_MMC_UpdatePsRegStatePsRegSucc()函数中会根据EPLMN LIST上报注册状态 */

        NAS_MMC_UpdateGURegRlstRPlmnIdInNV();


        NAS_MMC_NotifyModeChange(NAS_MML_GetCurrNetRatType(),
                                 NAS_MML_GetSimPsRegStatus());


        NAS_MMC_SetUserSpecPlmnRegisterStatus(VOS_TRUE);

        /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, begin */
        NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_PS, VOS_TRUE, NAS_MML_REG_FAIL_CAUSE_NULL);
        /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, end */
    }
    else if ((MMC_LMM_TAU_RSLT_FAILURE == pstLmmTauIndMsg->ulTauRst)
          && (VOS_FALSE == pstLmmTauIndMsg->bitOpAtmpCnt))
    {
        /* LNAS后续还有注册尝试流程-这里继续等待下 */
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT);

        enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;

        /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, begin */
        NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_PS, VOS_FALSE, NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);
        /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, end */
    }
    else if (MMC_LMM_TAU_RSLT_T3402_RUNNING_EPS_ONLY_SUCC == pstLmmTauIndMsg->ulTauRst)
    {
        NAS_MMC_ProcCombinedEpsRegFailCauseT3402RunningEpsOnlySucc(LMM_MMC_TAU_RESULT_IND, pstLmmTauIndMsg,
                                          &enAdditionalAction, &enCsRegAdditionalAction);
    }
    else
    {
        enAdditionalAction = NAS_MMC_ProcEpsTauRegFail(LMM_MMC_TAU_RESULT_IND, pstLmmTauIndMsg);

        NAS_MMC_UpdateUserSpecPlmnRegisterStatusWhenRegFail(enRegRsltCause);
    }

    /* AdditionalAction有效，更新EPS的下一步的动作类型 */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enAdditionalAction )
    {
        NAS_MMC_SetPsRegAdditionalAction_L1Main(enAdditionalAction);
    }

    if (VOS_TRUE == NAS_MMC_IsNeedSndEplmn())
    {
        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, begin */
        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildSndLmmEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndLmmEquPlmnReq(&stSndEquPlmnInfo);
        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, end */

        NAS_MMC_SndOmEquPlmn();

        /* 通知CSS GEO信息 */
        NAS_MMC_SndCssCurrGeoInd(VOS_TRUE, stSndEquPlmnInfo.ucEquPlmnNum, stSndEquPlmnInfo.astEquPlmnAddr);
    }

    /* 设置PS的注册尝试次数 */
    if (VOS_TRUE == pstLmmTauIndMsg->bitOpAtmpCnt)
    {
        NAS_MMC_SetPsRegAttemptCount_L1Main(pstLmmTauIndMsg->ulAttemptCount);
    }

    return ;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcLmmTauResultInd_OnPlmn
 功能描述  : Lmm TAU结果的处理函数
 输入参数  : pstLmmTauIndMsg L的TAU消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月30日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2011年12月28日
    作    者   : z00161729
    修改内容   : V7R1 phaseIV修改周期性tau处理
*****************************************************************************/
VOS_VOID NAS_MMC_ProcLmmTauResultInd_OnPlmn(
    LMM_MMC_TAU_RESULT_IND_STRU        *pstLmmTauIndMsg
)
{
    switch (pstLmmTauIndMsg->ulReqType)
    {
        case MMC_LMM_COMBINED_TA_LA_UPDATING:
        case MMC_LMM_COMBINED_TA_LA_WITH_IMSI:
        case MMC_LMM_CS_PS_PERIODIC_UPDATING:

            /* 处理lmm的联合tau结果 */
            NAS_MMC_ProcLmmCombinedTauResultInd_OnPlmn(pstLmmTauIndMsg);
            break;

        case MMC_LMM_TA_UPDATING:
        case MMC_LMM_PS_PERIODIC_UPDATING:

            /* 处理lmm的非联合tau，EPS only注册的结果 */
            NAS_MMC_ProcLmmEpsOnlyTauResultInd_OnPlmn(pstLmmTauIndMsg);
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcLmmTauResultInd_OnPlmn:Unexpected tau req type!");
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcLmmCombinedAttachInd_OnPlmn
 功能描述  : Lmm combined attach结果的处理函数
 输入参数  : pstLmmAttachIndMsg - ID_LMM_MMC_ATTACH_IND消息的首地址
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月25日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2011年12月8日
    作    者   : w00176964
    修改内容   : V7R1 PhaseIV 调整
  3.日    期   : 2011年12月5日
    作    者   : z00161729
    修改内容   : V7R1 phaseIV修改合并原NAS_MMC_HPLMN_REG_REJ_STRU和NAS_MMC_PLMN_REG_INFO_STRU
  4.日    期   : 2011年12月13日
    作    者   : z00161729
    修改内容   : DTS2011121302231:attach被拒#9/#10按协议应该按other cause处理
  5.日    期   : 2011年12月20日
    作    者   : w00176964
    修改内容   : V7R1 phaseIV 调整:联合注册成功需要设置NAS_MMC_SetUserSpecPlmnRegisterStatus为VOS_TRUE
  6.日    期   : 2012年2月4日
    作    者   : w00167002
    修改内容   : DTS2011122704039:将注册结果类型以及注册消息传递给处理注册结果
                  函数，扩展注册结果函数的处理能力。
                  additional action值若为无效值NAS_MMC_ADDITIONAL_ACTION_BUTT
                 则不更新当前的additional action
  7.日    期   : 2012年4月25日
    作    者   : w00176964
    修改内容   : GUL_BG项目调整
  8.日    期   : 2012年06月01日
    作    者   : sunxibo /46746
    修改内容   : Added for V7R1 C50 CS/PS mode 1
  9.日    期   : 2012年08月20日
    作    者   : l65478
    修改内容   : DTS2012081703289，手动搜网失败后关机，重新开机注册成功
                   后出服务区后不驻留EPLMN上
  10.日    期   : 2012年8月21日
    作    者   : z00161729
    修改内容   : DCM定制需求和遗留问题修改DTS2012090401249
 11.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
 12.日    期   : 2014年5月5日
    作    者   : w00242748
    修改内容   : DTS2014043000311:注册状态服务状态不一致，将MMC中报服务状态的场景，都加
                 注册状态的上报。
 *****************************************************************************/
VOS_VOID  NAS_MMC_ProcLmmCombinedAttachInd_OnPlmn(
    LMM_MMC_ATTACH_IND_STRU            *pstLmmAttachIndMsg
)
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enPsRegRsltCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsRegRsltCause;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsAdditionalAction;

    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, begin */
    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, end */

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));


    enPsAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_BUTT;
    enCsAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_BUTT;

    NAS_MMC_ConverLmmCombinedAttachRsltToMMLCause(pstLmmAttachIndMsg,&enPsRegRsltCause, &enCsRegRsltCause);

    switch (pstLmmAttachIndMsg->ulAttachRslt)
    {
        case MMC_LMM_ATT_RSLT_SUCCESS:
            NAS_MMC_ProcLmmCombinedAttachInd_AttRsltSucc(pstLmmAttachIndMsg,
                       enCsRegRsltCause, &enCsAdditionalAction, &enPsAdditionalAction);

            break;

        case MMC_LMM_ATT_RSLT_FAILURE:
            if (VOS_FALSE == pstLmmAttachIndMsg->bitOpAtmpCnt)
            {
                enPsAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
                enCsAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;

                /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, begin */
                NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, VOS_FALSE, NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);
                /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, end */

                /* LNAS后续还有注册尝试流程-这里继续等待下 */
                NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT);
            }
            else
            {
                /* EPS/CS 均注册失败 */
                NAS_MMC_ProcCombinedAttachEpsRegFail(LMM_MMC_ATTACH_IND,
                                                     pstLmmAttachIndMsg,
                                                     &enPsAdditionalAction,
                                                     &enCsAdditionalAction);
            }
            break;

        case MMC_LMM_ATT_RSLT_ESM_FAILURE:
        case MMC_LMM_ATT_RSLT_MO_DETACH_FAILURE:
        case MMC_LMM_ATT_RSLT_MT_DETACH_FAILURE:
        case MMC_LMM_ATT_RSLT_T3402_RUNNING:
        case MMC_LMM_ATT_RSLT_TIMER_EXP:
        case MMC_LMM_ATT_RSLT_ACCESS_BAR:
        case MMC_LMM_ATT_RSLT_FORBID_PLMN:
        case MMC_LMM_ATT_RSLT_FORBID_TA_FOR_RPOS:
        case MMC_LMM_ATT_RSLT_FORBID_PLMN_FOR_GPRS:
        case MMC_LMM_ATT_RSLT_FORBID_TA_FOR_ROAMING:
        case MMC_LMM_ATT_RSLT_AUTH_REJ:
        case MMC_LMM_ATT_RSLT_PS_ATT_NOT_ALLOW:
            /* EPS/CS 均注册失败 */
            NAS_MMC_ProcCombinedAttachEpsRegFail(LMM_MMC_ATTACH_IND,
                                                pstLmmAttachIndMsg,
                                                &enPsAdditionalAction,
                                                &enCsAdditionalAction);
            break;

        case MMC_LMM_ATT_RSLT_CN_REJ:
            if ((VOS_TRUE == pstLmmAttachIndMsg->bitOpCnRslt)
             && (MMC_LMM_ATT_CN_RSLT_EPS_ONLY == pstLmmAttachIndMsg->ulCnRslt))
            {
                /* 当ATTACH请求类型为联合，网侧相应的ATTACH结果类型为EPS ONLY，
                   且原因值不为协议24301 5.5.1.3.4.3章节所列或者没有携带原因值，
                   则LMM通过ATTACH结果中MMC_LMM_ATT_RSLT_CN_REJ通知MMC，
                   且携带相应的ATTACH请求类型、网侧响应的ATTCH结果类型、原因值，
                   并携带处理该原因后的attach attempt counter值 */
                NAS_MMC_ProcLmmCombinedAttachInd_AttRsltEpsOnlySucc(pstLmmAttachIndMsg,enCsRegRsltCause,
                                  &enCsAdditionalAction, &enPsAdditionalAction);
            }
            else
            {
                /* EPS/CS 均注册失败 */
                NAS_MMC_ProcCombinedAttachEpsRegFail(LMM_MMC_ATTACH_IND,
                                                     pstLmmAttachIndMsg,
                                                     &enPsAdditionalAction,
                                                     &enCsAdditionalAction);

            }
            break;

        default:
            /* 异常打印 */
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcLmmCombinedAttachInd_OnPlmn:Unexpected attach result!");
            enPsAdditionalAction = NAS_MMC_GetPsRegAdditionalAction_L1Main();
            enCsAdditionalAction = NAS_MMC_GetCsRegAdditionalAction_L1Main();
            break;
    }

    /* AdditionalAction有效，更新EPS的下一步的动作类型 */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enPsAdditionalAction )
    {
        NAS_MMC_SetPsRegAdditionalAction_L1Main(enPsAdditionalAction);
    }

    /* AdditionalAction有效，更新CS的下一步的动作类型 */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enCsAdditionalAction )
    {
        NAS_MMC_SetCsRegAdditionalAction_L1Main(enCsAdditionalAction);
    }

    if (VOS_TRUE == NAS_MMC_IsNeedSndEplmn())
    {
        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, begin */
        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildSndLmmEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndLmmEquPlmnReq(&stSndEquPlmnInfo);
        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, end */

        NAS_MMC_SndOmEquPlmn();

        /* 通知CSS GEO信息 */
        NAS_MMC_SndCssCurrGeoInd(VOS_TRUE, stSndEquPlmnInfo.ucEquPlmnNum, stSndEquPlmnInfo.astEquPlmnAddr);
    }


    /* 更新PS的注册尝试次数 */
    if (VOS_TRUE == pstLmmAttachIndMsg->bitOpAtmpCnt)
    {
        NAS_MMC_SetPsRegAttemptCount_L1Main(pstLmmAttachIndMsg->ulAttemptCount);
    }

    NAS_MMC_UpdateUserSpecPlmnRegisterStatus(enPsRegRsltCause);
    return;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcLmmCombinedTauResultInd_OnPlmn
 功能描述  : Lmm 联合TAU结果的处理函数
 输入参数  : pstLmmTauIndMsg L的TAU消息
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月26日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2011年12月8日
    作    者   : w00176964
    修改内容   : V7R1 PhaseIV 调整
  3.日    期   : 2011年12月5日
    作    者   : z00161729
    修改内容   : V7R1 phaseIV修改合并原NAS_MMC_HPLMN_REG_REJ_STRU和NAS_MMC_PLMN_REG_INFO_STRU
  4.日    期   : 2011年12月13日
    作    者   : z00161729
    修改内容   : DTS2011121302231:attach被拒#9/#10按协议应该按other cause处理
  5.日    期   : 2011年12月20日
    作    者   : w00176964
    修改内容   : V7R1 phaseIV 调整:联合注册成功需要设置NAS_MMC_SetUserSpecPlmnRegisterStatus为VOS_TRUE
  6.日    期   : 2012年2月4日
    作    者   : w00167002
    修改内容   : DTS2011122704039:将注册结果类型以及注册消息传递给处理注册结果
                  函数，扩展注册结果函数的处理能力。
                  additional action值若为无效值NAS_MMC_ADDITIONAL_ACTION_BUTT
                 则不更新当前的additional action
  7.日    期   : 2012年4月25日
    作    者   : w00176964
    修改内容   : GUL_BG项目调整
  8.日    期   : 2012年06月01日
    作    者   : sunxibo /46746
    修改内容   : Added for V7R1 C50 CS/PS mode 1
  9.日    期   : 2012年6月7日
    作    者   : z00161729
    修改内容   : GUL_BG项目调整将圈复杂度
 10.日    期   : 2012年08月20日
    作    者   : l65478
    修改内容   : DTS2012081703289，手动搜网失败后关机，重新开机注册成功
                   后出服务区后不驻留EPLMN上
  11.日    期   : 2012年8月21日
     作    者   : z00161729
     修改内容   : DCM定制需求和遗留问题修改DTS2012090401249
*****************************************************************************/
VOS_VOID  NAS_MMC_ProcLmmCombinedTauResultInd_OnPlmn(
    LMM_MMC_TAU_RESULT_IND_STRU        *pstLmmTauIndMsg
)
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enPsRegRsltCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsRegRsltCause;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsAdditionalAction;

    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, begin */
    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, end */

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));
    enPsAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_BUTT;
    enCsAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_BUTT;

    NAS_MMC_ConverLmmCombinedTauRsltToMMLCause(pstLmmTauIndMsg, &enPsRegRsltCause, &enCsRegRsltCause);

    NAS_MMC_ProcLmmCombinedTauResult(pstLmmTauIndMsg, enCsRegRsltCause,
                                    &enPsAdditionalAction, &enCsAdditionalAction);

    /* AdditionalAction有效，更新EPS的下一步的动作类型 */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enPsAdditionalAction )
    {
        NAS_MMC_SetPsRegAdditionalAction_L1Main(enPsAdditionalAction);
    }

    /* AdditionalAction有效，更新CS的下一步的动作类型 */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enCsAdditionalAction )
    {
        NAS_MMC_SetCsRegAdditionalAction_L1Main(enCsAdditionalAction);
    }

    if (VOS_TRUE == NAS_MMC_IsNeedSndEplmn())
    {
        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, begin */
        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildSndLmmEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndLmmEquPlmnReq(&stSndEquPlmnInfo);
        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, end */

        NAS_MMC_SndOmEquPlmn();

        /* 通知CSS GEO信息 */
        NAS_MMC_SndCssCurrGeoInd(VOS_TRUE, stSndEquPlmnInfo.ucEquPlmnNum, stSndEquPlmnInfo.astEquPlmnAddr);
    }


    /* 更新PS的注册尝试次数 */
    if (VOS_TRUE == pstLmmTauIndMsg->bitOpAtmpCnt)
    {
        NAS_MMC_SetPsRegAttemptCount_L1Main(pstLmmTauIndMsg->ulAttemptCount);
    }

    NAS_MMC_UpdateUserSpecPlmnRegisterStatus(enPsRegRsltCause);
    return;
}
#endif

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcCoverageLost_L1Main
 功能描述  : 处理出服务区的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年08月09日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2012年03月03日
   作    者   : s62952
   修改内容   : BalongV300R002 Build优化项目
 3.日    期   : 2012年04月07日
   作    者   : l00130025
   修改内容   : 问题单号:DTS2012040106098,调整CoverageLost和service的上报顺序，以更新MMA的状态到DeepSleep
 4.日    期   : 2012年4月9日
   作    者   : l00130025
   修改内容   : DTS2012033006643,开机搜网或Syscfg触发搜网失败时，上报RSSI为无效
 5.日    期   : 2012年3月31日
   作    者   : z40661
   修改内容   : V7R1支持搜网低功耗
 6.日    期   : 2012年9月14日
   作    者   : t00212959
   修改内容   : DTS2012082808241,进入OOC状态，应该将驻留标志清除，列表搜成功但带上来0个网络时，available超时搜网类型有误
 7.日    期   : 2012年11月7日
   作    者   : l00167671
   修改内容   : DTS2012110607212: availble定时器定时器启动成功,才能进行定时器计数
 8.日    期   : 2012年11月21日
   作    者   : z00161729
   修改内容   : 支持cerssi和nmr
9.日    期   : 2013年3月30日
  作    者   : l00167671
  修改内容   : 主动上报AT命令控制下移至C核
10.日    期   : 2013年12月24日
   作    者   : z00161729
   修改内容   : SVLTE支持NCELL搜网
11.日    期   : 2013年4月4日
   作    者   : y00176023
   修改内容   : DSDS GUNAS II项目:更改NO RF 相关变量名称
12.日    期   : 2014年1月28日
   作    者   : s00246516
   修改内容   : L-C互操作项目:增加获取和注册请求的处理
13.日    期   : 2014年6月4日
   作    者   : b00269685
   修改内容   : NAS_MMC_SndMsccRssiInd()修改
14.日    期   : 2014年7月3日
   作    者   : z00161729
   修改内容   : DSDS III新增
15.日    期   : 2015年5月25日
   作    者   : s00217060
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0修改
16.日    期   : 2015年9月10日
   作    者   : c00318887
   修改内容   : 预置频点搜网优化修改
17.日    期   : 2015年11月14日
   作    者   : l00289540
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0 修改
*****************************************************************************/
/* Modified by c00318887 for 预置频点搜网优化, 2015-9-10, begin */
VOS_VOID    NAS_MMC_ProcCoverageLost_L1Main(
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32          ulPlmnSearchScene
)
/* Modified by c00318887 for 预置频点搜网优化, 2015-9-10, end */
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;

    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    NAS_MML_CAMP_CELL_INFO_STRU        *pstCampCellInfo = VOS_NULL_PTR;


    MSCC_MMC_SCELL_MEAS_REPORT_TYPE_UN   unMeasReportType;

    pstCampCellInfo         = NAS_MML_GetCampCellInfo();
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */

    enRatType = NAS_MML_GetCurrNetRatType();

    PS_MEM_SET(((VOS_UINT8*)&unMeasReportType), 0, sizeof(MSCC_MMC_SCELL_MEAS_REPORT_TYPE_UN));
    unMeasReportType.ucMeasReportType |= NAS_MSCC_PIF_SCELL_MEAS_TYPE_RXLEV;

    if (VOS_FALSE == NAS_MML_GetRfAvailFlg())
    {
        NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,
                                 NAS_MML_GetSimPsRegStatus());

    }

    if (((NAS_MML_NET_RAT_TYPE_GSM == enRatType)
      && (NAS_MML_RSSI_UNVALID != pstCampCellInfo->astRssiInfo[0].sRssiValue))
     || ((NAS_MML_NET_RAT_TYPE_WCDMA == enRatType)
      && (NAS_MML_UTRA_RSCP_UNVALID != pstCampCellInfo->astRssiInfo[0].sRscpValue)))
    {
        NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());
        NAS_MMC_SndMsccRssiInd(&unMeasReportType);
    }

    /* 已经丢网，应为非驻留态，否则列表搜没有带上网络引起的丢网，available超时后会在CCO状态发出列表搜请求*/
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);

    /* Added by s00246516 for L-C互操作项目, 2014-01-28, Begin */
    NAS_MMC_SetAsAnyCampOn(VOS_FALSE);
    /* Added by s00246516 for L-C互操作项目, 2014-01-28, End */


    /* Deleted by s00261364 for V3R360_eCall项目, 2014-4-30, begin */

    /* Deleted by s00261364 for V3R360_eCall项目, 2014-4-30, end */
    /* 通知MM 覆盖区丢失 */
    NAS_MMC_SndMmCoverageLostInd();

    /* 通知GMM 覆盖区丢失 */
    NAS_MMC_SndGmmCoverageLostInd();

    NAS_MMC_SndMsccCoverageInd(NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );

    /* Deleted by s00261364 for V3R360_eCall项目, 2014-4-30, begin */

    /* Deleted by s00261364 for V3R360_eCall项目, 2014-4-30, end */

    /* Modified by c00318887 for 预置频点搜网优化, 2015-9-10, begin */
    if (NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED_HISTORY_PLMN_SEARCH != ulPlmnSearchScene)
    {
        /* Added by s00261364 for V3R360_eCall项目, 2014-4-30, begin */
        /* 上报对应的CS/PS服务状态MSCC_MMC_SERVICE_STATUS_NO_SERVICE */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NO_SERVICE);
        NAS_MMC_UpdateRegStateSpecPlmnSearch();
        /* Added by s00261364 for V3R360_eCall项目, 2014-4-30, end */
    }
    /* Modified by c00318887 for 预置频点搜网优化, 2015-9-10, end */


    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    NAS_MMC_EnterOocStatus_OnPlmn();

    NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_OOC);



    /* 搜网NO RF失败时候，则启动周期搜网定时器，但不增加COUNTER */
    if (VOS_TRUE == NAS_MMC_StartTimer(TI_NAS_MMC_AVAILABLE_TIMER, NAS_MMC_GetNextAvailableTimerValue()))
    {
        NAS_MMC_SetAvailableTimerTypebySearchType_OnPlmn();

        if (VOS_TRUE == NAS_MML_GetRfAvailFlg())
        {
            /* Added by c00318887 for 预置频点搜网优化, 2015-9-1, begin */
            (VOS_VOID)NAS_MMC_StartPlmnSearchPhaseOneTotalTimer();
            /* Added by c00318887 for 预置频点搜网优化, 2015-9-1, end */
        }
    }


}


/*****************************************************************************
 函 数 名  : NAS_MMC_ProcOutOfService_L1Main
 功能描述  : 处理有网络覆盖的处理
 输入参数  : ulCampFlg:当前是否驻留 VOS_TRUE  - 驻留
                                    VOS_FALSE - 非驻留
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年08月09日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2012年8月10日
   作    者   : L00171473
   修改内容   : DTS2012082204471, TQE清理
 3.日    期   : 2012年07月14日
   作    者   : l65478
   修改内容   : DTS2012071303294在连接建立失败时没有清除CS连接标志

  4.日    期   : 2012年9月25日
    作    者   : z40661
    修改内容   : DTS2012082006273
 5.日    期   : 2012年11月7日
   作    者   : l00167671
   修改内容   : DTS2012110607212: availble定时器定时器启动成功,才能进行定时器计数
 6.日    期   : 2013年12月24日
   作    者   : z00161729
   修改内容   : SVLTE支持NCELL搜网
 7.日    期   : 2013年4月4日
   作    者   : y00176023
   修改内容   : DSDS GUNAS II项目:更改NO RF 相关变量名称

 8.日    期   : 2015年1月23日
   作    者   : w00167002
   修改内容   : CL_ACCESSBAR_STUB:via控制L下搜网注册时候，L下ACCESS BAR，后续
                选网结束后，L自己触发了注册。VIA无法配合，MODEM进行配合修改。
                修改为在注册状态收到ACCESS BAR后，继续等待L的注册结果。

*****************************************************************************/
VOS_VOID    NAS_MMC_ProcOutOfService_L1Main(
    NAS_MMCMMC_PLMN_SELECTION_RSLT_STRU                    *pstPlmnSelectionRslt
)
{
    VOS_UINT32                          ulPlmnLaType;
    NAS_MML_PLMN_RAT_PRIO_STRU          stAnycellSrchRatList;
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulRecampFlg;
#endif

    NAS_MMC_AS_CELL_CAMP_ON_ENUM_UINT8  enCampOnFlg;

    VOS_UINT8                           ucRfAvailFlg;

    NAS_MMC_REG_CONTROL_ENUM_UINT8      enRegCtrl;

    enRegCtrl  = NAS_MMC_GetRegCtrl();

    ucRfAvailFlg    = NAS_MML_GetRfAvailFlg();

    enCampOnFlg  = NAS_MMC_GetAsCellCampOn();

    PS_MEM_SET(&stAnycellSrchRatList, 0x00, sizeof(stAnycellSrchRatList));


    /* 获取当前的LA是否在禁止列表中 */
    ulPlmnLaType = NAS_MMC_GetCurrentLaiForbbidenType();

    /* 当前卡有效,且为驻留状态，且不在禁止网络信息中 */
#if (FEATURE_ON == FEATURE_LTE)
    ulRecampFlg = VOS_FALSE;
    ulRecampFlg = NAS_MMC_IsReCampLteLimitedService();
#endif

    if ( (VOS_TRUE == NAS_MML_IsUsimStausValid())
       &&(NAS_MML_PLMN_FORBID_NULL  == ulPlmnLaType)
       &&(VOS_TRUE                  == pstPlmnSelectionRslt->ulCampFlg)
       &&(NAS_MMC_AS_CELL_CAMP_ON   == enCampOnFlg)
       &&(NAS_MMC_REG_CONTROL_BY_3GPP2_CBP != enRegCtrl))
    {
#if   (FEATURE_ON == FEATURE_LTE)
        /* 需要disalbe lte,同时不驻留在LTE下面 */
        if ( (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS == NAS_MML_GetLteCapabilityStatus())
          && ( VOS_FALSE == ulRecampFlg ))
        {
            /* 根据搜网结果 构造ANYCELL搜网的RAT搜索技术 */
            NAS_MMC_BuildCoverageRatPrioList_L1Main(pstPlmnSelectionRslt, &stAnycellSrchRatList);

            /* 根据结果中的接入技术覆盖信息启动anycell状态机，优先搜索当前接入技术 */
            NAS_MMC_SndInterAnyCellSearchReq(&stAnycellSrchRatList, NAS_MMC_ANYCELL_SEARCH_SCENE_BUTT);
        }
        else
#endif
        {
            /* 如果卡有效启动Available定时器 */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_ON_PLMN);



            /* 搜网失败为NO RF，则不增加COUNTER,防止后续搜网速度减慢 */
            if ( (VOS_TRUE  == NAS_MMC_StartTimer(TI_NAS_MMC_AVAILABLE_TIMER, NAS_MMC_GetNextAvailableTimerValue()))
               && (VOS_TRUE == ucRfAvailFlg) )
            {
                /* 递增 availble timer当前启动的次数或ncell搜网次数 */
                NAS_MMC_SetAvailableTimerTypebySearchType_OnPlmn();

                /* Added by c00318887 for 预置频点搜网优化, 2015-9-1, begin */
                (VOS_VOID)NAS_MMC_StartPlmnSearchPhaseOneTotalTimer();
                /* Added by c00318887 for 预置频点搜网优化, 2015-9-1, end */

            }
        }
    }
    else
    {
        /* 根据搜网结果 构造ANYCELL搜网的RAT搜索技术 */
        NAS_MMC_BuildCoverageRatPrioList_L1Main(pstPlmnSelectionRslt, &stAnycellSrchRatList);

        /* 根据结果中的接入技术覆盖信息启动anycell状态机，优先搜索当前接入技术 */
        NAS_MMC_SndInterAnyCellSearchReq(&stAnycellSrchRatList, NAS_MMC_ANYCELL_SEARCH_SCENE_BUTT);
    }

}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcPlmnListTriggerPlmnSearch_L1Main
 功能描述  : L1状态机下收到LIST搜网状态机结果,并且需要搜网时的处理
 输入参数  : pstListRslt:List搜网状态机结果
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
              VOS_FALSE:处理未完成
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月13日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2012年8月21日
    作    者   : z00161729
    修改内容   : DCM定制需求和遗留问题修改
  3.日    期   : 2012年8月21日
    作    者   : w00176964
    修改内容   : DTS2012111404729:开机驻留到ACC BAR小区，发起用户LIST搜网
                 只搜到当前网络后,后续反复触发内部LIST搜网
  4.日    期   : 2012年12月07日
    作    者   : w00176964
    修改内容   : DTS2012120401487:L下detach CS/PS后用户LIST搜网结束应该不搜网
  5.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  6.日    期   : 2014年5月31日
    作    者   : y00245242
    修改内容   : 修改服务状态上报
*****************************************************************************/
VOS_UINT32 NAS_MMC_ProcPlmnListTriggerPlmnSearch_L1Main(
    NAS_MMCMMC_PLMN_LIST_RSLT_STRU     *pstListRslt
)
{
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene;
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-22, begin */
    NAS_MML_PLMN_RAT_PRIO_STRU                              stAnycellSrchRatList;
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList = VOS_NULL_PTR;
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-22, end */

    /* 判断是否需要触发搜网,不需要则直接返回 */
    if (VOS_FALSE == NAS_MMC_IsPlmnListTriggerPlmnSrch_L1Main(pstListRslt))
    {
        return VOS_FALSE;
    }

    /* 收到丢网指示后，迁移状态NAS_MMC_L1_STA_INITIAL */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

   /* L下idle态detach,收到L detach cnf缓存了disable搜网和限制服务消息后发起用户list搜网,
      L下list搜网成功退出需要搜网,按用户list搜网场景搜网,需要清空缓存的搜网标志 */
    NAS_MMC_SetBufferedPlmnSearchInfo(VOS_FALSE, NAS_MMC_PLMN_SEARCH_SCENE_BUTT);

#if (FEATURE_ON == FEATURE_LTE)
    /* 如果disable LTE后，LIST搜网回到L下，此时搜网场景需要重新设置 */
    if (NAS_MMC_PLMN_LIST_SEARCH_SCENE_DISABLE_LTE == pstListRslt->enPlmnListSearchScene)
    {
        /* 发送搜网消息 */
        enPlmnSearchScene = NAS_MMC_PLMN_SEARCH_SCENE_DISABLE_LTE;
    }
    else
#endif
    {
        /* 发送用户列表搜网消息 */
        enPlmnSearchScene = NAS_MMC_PLMN_SEARCH_SCENE_USER_LIST;
    }

    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-22, begin */
    if (VOS_FALSE == NAS_MMC_IsNeedAnycell_OnPlmn())
    {
        /* 非驻留时更新为无服务状态并上报 */
        if (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == NAS_MMC_GetSpecPlmnSearchState())
        {
            /* Modified by y00245242 for V3R3C60_eCall项目, 2014-5-31, begin */
            NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NO_SERVICE);
            /* Modified by y00245242 for V3R3C60_eCall项目, 2014-5-31, end */
        }

        /* 构造并发送内部搜网信息 */
        NAS_MMC_SndInterPlmnSearchReq(enPlmnSearchScene, &(pstListRslt->astPlmnSearchInfo[0]), NAS_MML_MAX_RAT_NUM);
        return VOS_TRUE;
    }

    if (VOS_FALSE == NAS_MML_IsExistBufferedEmgCall())
    {
        /* 更新为限制服务状态并上报 */
        /* Modified by y00245242 for V3R3C60_eCall项目, 2014-5-31, begin */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_LIMITED_SERVICE);
        /* Modified by y00245242 for V3R3C60_eCall项目, 2014-5-31, end */

        /* 注册被拒导致卡无效触发Anycell搜网 */
        NAS_MMC_SndInterAnyCellSearchReq(VOS_NULL_PTR, NAS_MMC_ANYCELL_SEARCH_SCENE_BUTT);
    }
    else
    {
        /* 存在紧急呼叫触发ANYCELL搜网,构造需要anycell搜的接入技术为GU,优先顺序按照syscfg设置 */
        pstPrioRatList = NAS_MML_GetMsPrioRatList();
        NAS_MMC_BuildCoverageRatPrioListEmgCall_L1Main(pstPrioRatList, &stAnycellSrchRatList);

        NAS_MMC_SndInterAnyCellSearchReq(&stAnycellSrchRatList, NAS_MMC_ANYCELL_SEARCH_SCENE_BUTT);
    }
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-22, end */

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcTiAvailableTimerExpiredTriggerPlmnSearch_L1Main
 功能描述  : available定时器超时之后需要搜网的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月25日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_ProcTiAvailableTimerExpiredTriggerPlmnSearch_L1Main(VOS_VOID)
{
    NAS_MML_PLMN_ID_STRU                                   *pstCampPlmnId    = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                                   *pstOtherPlmnId   = VOS_NULL_PTR;

    VOS_UINT8                                               ucRrcLteNcellExistFlg;
    VOS_UINT8                                               ucRrcUtranNcellExistFlg;
    VOS_UINT8                                               ucIsCampSamePlmn;
    VOS_UINT8                                               ucSvlteSupportFlg;
    VOS_UINT8                                               ucLcEnableFlg;
    NAS_MMC_OOS_PHASE_ENUM_UINT8                            enOosPhaseNum;


    pstOtherPlmnId              = NAS_MMC_GetOtherModemPlmnId();
    pstCampPlmnId               = NAS_MML_GetCurrCampPlmnId();
    ucRrcLteNcellExistFlg       = NAS_MML_GetRrcLteNcellExistFlg();
    ucRrcUtranNcellExistFlg     = NAS_MML_GetRrcUtranNcellExistFlg();
    ucSvlteSupportFlg           = NAS_MML_GetSvlteSupportFlag();
    ucLcEnableFlg               = NAS_MML_GetLcEnableFlg();

    ucIsCampSamePlmn            = VOS_FALSE;


    if ( ( pstOtherPlmnId->ulMcc == pstCampPlmnId->ulMcc)
      && ( pstOtherPlmnId->ulMnc == pstCampPlmnId->ulMnc)  )
    {
        ucIsCampSamePlmn = VOS_TRUE;
    }
    /* 可维可测 */
    NAS_MMC_LogOosPlmnSearchStrategyRelatedInfo();
    NAS_MMC_LogFsmL1MainCtxRelatedInfo(NAS_MMC_GetL1MainCtx_L1Main());

    /* available定时器超时对于history搜的处理 */
    if (VOS_TRUE == NAS_MMC_ProcTiAvailableTimerExpired_HistorySearch_L1Main())
    {
        return VOS_TRUE;
    }

    /* available定时器超时对于Pref-Band搜的处理 */
    if (VOS_TRUE == NAS_MMC_ProcTiAvailableTimerExpired_PrefBandSearch_L1Main())
    {
        return VOS_TRUE;
    }

    /* available定时器超时对于ncell搜的处理 */
    if (VOS_TRUE == NAS_MMC_ProcTiAvailableTimerExpired_NcellSearch_L1Main())
    {
        return VOS_TRUE;
    }
    enOosPhaseNum               = NAS_MMC_GetOosPhaseNum();

    /* SVLTE或C+L形态时，国内模式(PS Only)需要启动Avaliable定时器 */
    if ( (NAS_MML_MS_MODE_PS_ONLY == NAS_MML_GetMsMode())
      && ( (VOS_TRUE == ucSvlteSupportFlg)
        || (VOS_TRUE == ucLcEnableFlg) )
      && (NAS_MMC_OOS_PHASE_ONE == enOosPhaseNum)
      && (VOS_TRUE == ucIsCampSamePlmn )
      && ((VOS_TRUE == ucRrcLteNcellExistFlg)
       || (VOS_TRUE == ucRrcUtranNcellExistFlg)) )
    {
        if ( VOS_TRUE == NAS_MMC_StartTimer(TI_NAS_MMC_AVAILABLE_TIMER, NAS_MMC_GetNextAvailableTimerValue()) )
        {
            NAS_MMC_SetAvailableTimerTypebySearchType_OnPlmn();

            /* Added by c00318887 for 预置频点搜网优化, 2015-9-1, begin */
            (VOS_VOID)NAS_MMC_StartPlmnSearchPhaseOneTotalTimer();
            /* Added by c00318887 for 预置频点搜网优化, 2015-9-1, end */
        }
        return VOS_FALSE;
    }


    /* available定时器超时对于普通列表搜或普通指定搜的处理 */
    if (VOS_TRUE == NAS_MMC_ProcTiAvailableTimerExpired_NormalSearch_L1Main())
    {
        return VOS_TRUE;
    }

    return VOS_TRUE;
}
/*****************************************************************************
 函 数 名  : NAS_MMC_ProcTiAvailableTimerExpired_HistorySearch_L1Main
 功能描述  : available定时器超时对于history搜的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月9日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_ProcTiAvailableTimerExpired_HistorySearch_L1Main(VOS_VOID)
{


    /* Modified by w00167002 for 预置频点搜网优化项目, 2015-9-15, begin */

    /* 需要history搜 */
    if (VOS_FALSE == NAS_MMC_IsNeedHistorySearch_L1Main())
    {
        NAS_MMC_SetCurrOosSearchPhaseNum(NAS_MMC_GetOosPhaseNum());

        /* 不需要history搜的时候，继续处理，可能需要ncell搜或普通周期性搜网 */
        NAS_MMC_ResetCurHistorySearchTimerCount_OnPlmn();

        return VOS_FALSE;
    }

    NAS_MMC_AddCurHistorySearchTimerCount_OnPlmn();

    NAS_MMC_SetCurrOosSearchPhaseNum(NAS_MMC_GetOosPhaseNum());

    if(VOS_TRUE == NAS_MMC_IsNeedGoToNextPhaseByHistory())
    {
        NAS_MMC_AddOosPhaseNum();
        NAS_MMC_ResetCurHistorySearchTimerCount_OnPlmn();
    }

    /* 在启动第一阶段总控定时器时候，normal availuable 定时器现在配置时间比原来长，为防止不能及时响应，
       normal availuable以history时长启动，超时执行LIST 搜 */

    if (VOS_TRUE == NAS_MMC_IsAvailTimerExpiredTriggerInterPlmnList_L1Main())
    {
        /* 如果当前第一阶段总控定时器不在运行，如在第二阶段搜网，为降低功耗，则不用发LIST搜网，继续启动定时器 */
        if (NAS_MMC_OOS_PHASE_ONE != NAS_MMC_GetCurrOosSearchPhaseNum())
        {
            if (VOS_TRUE == NAS_MMC_StartTimer(TI_NAS_MMC_AVAILABLE_TIMER, NAS_MMC_GetNextSearchSleepTimerLen()))
            {
                NAS_MMC_SetAvailableTimerType_OnPlmn(NAS_MMC_AVAILABLE_TIMER_TYPE_HISTORY);
            }

            NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcTiAvailableTimerExpired_HistorySearch_L1Main: PHASE ONE TIMER IS NOT RUN,GO ON HISTORY TIMER.");

            return VOS_TRUE;
        }

        NAS_MMC_SndInterPlmnListReq();

        /* 触发搜网后就清除additional的值 */
        NAS_MMC_ClearAllRegAdditionalAction_L1Main();

        /* 触发搜网后同时清除CS/PS的注册尝试次数 */
        NAS_MMC_ClearAllRegAttemptCount_L1Main();
    }
    else
    {
        NAS_MMC_RcvTiAvailTimerExpired_HistorySearch_OnPlmn();
    }

    return VOS_TRUE;

    /* Modified by w00167002 for 预置频点搜网优化项目, 2015-9-15, end */

}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcTiAvailableTimerExpired_PrefBandSearch_L1Main
 功能描述  : available定时器超时对于PrefBand搜的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月9日
    作    者   : h00281185
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_ProcTiAvailableTimerExpired_PrefBandSearch_L1Main(VOS_VOID)
{


    /* 需要PrefBand搜 */
    if (VOS_FALSE == NAS_MMC_IsNeedPrefBandSearch_L1Main())
    {
        NAS_MMC_SetCurrOosSearchPhaseNum(NAS_MMC_GetOosPhaseNum());

        /* 不需要PrefBand搜的时候，继续处理，可能需要ncell搜或普通周期性搜网 */
        NAS_MMC_ResetCurPrefBandSearchTimerCount_OnPlmn();

        return VOS_FALSE;
    }

    NAS_MMC_AddCurPrefBandSearchTimerCount_OnPlmn();

    NAS_MMC_SetCurrOosSearchPhaseNum(NAS_MMC_GetOosPhaseNum());

    if(VOS_TRUE == NAS_MMC_IsNeedGoToNextPhaseByPrefBand())
    {
        NAS_MMC_SetCurrOosSearchPhaseNum(NAS_MMC_GetOosPhaseNum());
        NAS_MMC_AddOosPhaseNum();
        NAS_MMC_ResetCurPrefBandSearchTimerCount_OnPlmn();
    }

    NAS_MMC_RcvTiAvailTimerExpired_PrefBandSearch_OnPlmn();

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcTiAvailableTimerExpired_NcellSearch_L1Main
 功能描述  : available定时器超时对于ncell搜的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月9日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_ProcTiAvailableTimerExpired_NcellSearch_L1Main(VOS_VOID)
{
    /* 满足ncell搜网条件则直接进行ncell快速搜网 */
    if (VOS_TRUE == NAS_MMC_IsNeedNcellSearch())
    {
        /*
           遗留问题:
           当Ncell特性打开时,
           需要检查 OOS中的条件 "FullBandNum >= 1, PrefBandNum = 0, HistoryNum = 0"
        */
        NAS_MMC_AddCurNcellSearchTimerCount_OnPlmn();
        /* 进行NCELL搜 */
        NAS_MMC_RcvTiAvailTimerExpired_NcellSearch_OnPlmn();

        return VOS_TRUE;
    }


    /* 不需要ncell搜的时候，继续处理，可能需要普通周期性搜网 */
    NAS_MMC_ResetCurNcellSearchTimerCount_OnPlmn();

    return VOS_FALSE;

}


/*****************************************************************************
 函 数 名  : NAS_MMC_ProcTiAvailableTimerExpired_NormalSearch_L1Main
 功能描述  : available定时器超时对于普通列表搜或普通指定搜的处理
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月9日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_ProcTiAvailableTimerExpired_NormalSearch_L1Main(VOS_VOID)
{


    NAS_MMC_AddCurNormalAvailableTimerCount_L1Main();

    NAS_MMC_SetCurrOosSearchPhaseNum(NAS_MMC_GetOosPhaseNum());

    if(VOS_TRUE == NAS_MMC_IsNeedGoToNextPhaseByFullBand())
    {
        NAS_MMC_SetCurrOosSearchPhaseNum(NAS_MMC_GetOosPhaseNum());
        NAS_MMC_AddOosPhaseNum();
        NAS_MMC_ResetCurNormalAvailableTimerCount_L1Main();
    }

    /* 判断available timer超时是否触发内部列表搜网 */
    if (VOS_TRUE == NAS_MMC_IsAvailTimerExpiredTriggerInterPlmnList_L1Main())
    {
        NAS_MMC_SndInterPlmnListReq();

        /* 触发搜网后就清除additional的值 */
        NAS_MMC_ClearAllRegAdditionalAction_L1Main();

        /* 触发搜网后同时清除CS/PS的注册尝试次数 */
        NAS_MMC_ClearAllRegAttemptCount_L1Main();

        return VOS_TRUE;
    }

    /* 定时器超时，设置为 initail 状态 */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

    /* 构造搜网消息 */
    NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED,VOS_NULL_PTR, 0);

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetRegRsltAdditionalAction_L1Main
 功能描述  : 根据搜网或注册结果，设置CS和PS的AdditionalAction
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年8月27日
    作    者   : l00130025
    修改内容   : 新生成函数

  2.日    期   : 2012年1月13日
    作    者   : w00167002
    修改内容   : DTS2011122006209:在收到注册结果时，将CS/PS域的AdditionalAction
                 值分别封装进行获取，便于以后扩展和可读性。
*****************************************************************************/
VOS_VOID NAS_MMC_SetRegRsltAdditionalAction_L1Main( VOS_VOID )
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                        enCsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                        enPsAdditionalAction;

    /* 当状态机退到L1 MAIN时，取得CS/PS的addition值 */
    enCsAdditionalAction = NAS_MMC_GenerateRegRsltCsDomainAdditionalAction_L1Main();
    enPsAdditionalAction = NAS_MMC_GenerateRegRsltPsDomainAdditionalAction_L1Main();

    /* 设置CS/PS的addition值 */
    NAS_MMC_SetCsRegAdditionalAction_L1Main(enCsAdditionalAction);
    NAS_MMC_SetPsRegAdditionalAction_L1Main(enPsAdditionalAction);


}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvForbLaTimerExpired_OnPlmn
 功能描述  : 处理TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST消息
 输入参数  : ulEventType:消息类型
             pstMsg:TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST消息
 输出参数  : 无
 返 回 值  : VOS_TRUE:函数处理完成
             VOS_FALSE:函数处理未完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2010年9月13日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiPeriodTryingUserPlmnListExpired_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 启动LIST搜网状态机 */
    NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_PLMN_LIST);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiPeriodTryingInterPlmnListExpired_OnPlmn
 功能描述  : 处理TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST消息
 输入参数  : ulEventType:消息类型
             pstMsg:TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST消息
 输出参数  : 无
 返 回 值  : VOS_TRUE:函数处理完成
             VOS_FALSE:函数处理未完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2010年9月13日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiPeriodTryingInterPlmnListExpired_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 启动LIST搜网状态机 */
    NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_PLMN_LIST);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvBgPlmnSearchRsltCnfFail_OnPlmn
 功能描述  : 处理MMCMMC_BG_PLMN_SEARCH_RSLT_CNF消息，BG搜网结果为
             NAS_MMC_BG_PLMN_SEARCH_FAIL的处理
 输入参数  : ulEventType:消息类型
             pstMsg:     MMCMMC_BG_PLMN_SEARCH_RSLT_CNF消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年6月04日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   : 2012年8月21日
   作    者   : z00161729
   修改内容   : DCM定制需求和遗留问题修改
 3.日    期   : 2013年3月30日
   作    者   : l00167671
   修改内容   : 主动上报AT命令控制下移至C核
 4.日    期   : 2013年12月24日
   作    者   : z00161729
   修改内容   : SVLTE支持NCELL搜网

 5.日    期   : 2014年5月4日
   作    者   : t00173447
   修改内容   : DTS2014042105390,软银定制需求
 6.日    期   : 2014年4月29日
   作    者   : s00261364
   修改内容   : ecall项目修改服务状态上报
*****************************************************************************/
VOS_VOID  NAS_MMC_RcvBgPlmnSearchRsltCnfFail_OnPlmn(
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32    enBgPlmnSearchScene,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU    *pstIntraPlmnSrchInfo
)
{
    VOS_UINT32                                              ulCsServiceExist;
    VOS_UINT32                                              ulPsServiceExist;
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene;

    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-22, begin */
    NAS_MML_PLMN_RAT_PRIO_STRU                              stAnycellSrchRatList;
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList = VOS_NULL_PTR;
    VOS_UINT32                                              ulEmgCallFlg;

    pstPrioRatList   = NAS_MML_GetMsPrioRatList();
    ulCsServiceExist = NAS_MML_GetCsServiceExistFlg();
    ulPsServiceExist = NAS_MML_GetPsServiceExistFlg();
    ulEmgCallFlg     = NAS_MML_GetCsEmergencyServiceFlg();

    /* 如果当前存在业务链接，启动AVAILABLE搜网定时器,紧急呼叫需要进行anycell搜 */
    if (((VOS_TRUE == ulCsServiceExist)
      && (VOS_FALSE == ulEmgCallFlg))
     || (VOS_TRUE == ulPsServiceExist))
    {
        if ( VOS_TRUE == NAS_MMC_StartTimer(TI_NAS_MMC_AVAILABLE_TIMER, NAS_MMC_GetNextAvailableTimerValue()) )
        {
            /* 递增 availble timer当前启动的次数或ncell搜网次数 */
            NAS_MMC_SetAvailableTimerTypebySearchType_OnPlmn();

            /* Added by c00318887 for 预置频点搜网优化, 2015-9-1, begin */
            (VOS_VOID)NAS_MMC_StartPlmnSearchPhaseOneTotalTimer();
            /* Added by c00318887 for 预置频点搜网优化, 2015-9-1, end */
        }

        return;
    }

    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-22, end */

    /* 迁移到Intial状态  */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

    /* 根据BG搜网状态机传出的搜网场景转换为内部搜网消息中的搜网场景 */
    if ( NAS_MMC_BG_PLMN_SEARCH_SCENE_AREA_LOST ==  enBgPlmnSearchScene)
    {
        if(VOS_TRUE == NAS_MMC_IsInterNationalRoamingSearchRPLMN(NAS_MMC_GetLastCampedPlmnid()->ulMcc))
        {
            enPlmnSearchScene = NAS_MMC_PLMN_SEARCH_SCENE_AREA_LOST_ROAMING_CFG;
        }
        else
        {
            enPlmnSearchScene = NAS_MMC_PLMN_SEARCH_SCENE_AREA_LOST;
        }
    }
    else
    {
        enPlmnSearchScene = NAS_MMC_PLMN_SEARCH_SCENE_DISABLE_LTE;
    }

    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-22, begin */
    if (VOS_FALSE == NAS_MMC_IsNeedAnycell_OnPlmn())
    {
        NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_HIGH_PRO_PLMN_SRCH_BACK_TO_ORIG_PLMN_FAIL);

        /* Modified by y00245242 for V3R3C60_eCall项目, 2014-5-31, begin */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NO_SERVICE);
        /* Modified by y00245242 for V3R3C60_eCall项目, 2014-5-31, end */

        /* 构造并发送内部搜网信息:场景同丢网 */
        NAS_MMC_SndInterPlmnSearchReq(enPlmnSearchScene, pstIntraPlmnSrchInfo, 1);
        return;
    }

    if (VOS_FALSE == NAS_MML_IsExistBufferedEmgCall())
    {
        /* 更新为无服务状态并上报 */
        /* Modified by y00245242 for V3R3C60_eCall项目, 2014-5-31, begin */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_LIMITED_SERVICE);
        /* Modified by y00245242 for V3R3C60_eCall项目, 2014-5-31, end */

        /* 注册被拒导致卡无效触发Anycell搜网 */
        NAS_MMC_SndInterAnyCellSearchReq(VOS_NULL_PTR, NAS_MMC_ANYCELL_SEARCH_SCENE_BUTT);
    }
    else
    {
        /* 存在紧急呼叫触发ANYCELL搜网,构造需要anycell搜的接入技术为GU,优先顺序按照syscfg设置 */
        NAS_MMC_BuildCoverageRatPrioListEmgCall_L1Main(pstPrioRatList, &stAnycellSrchRatList);

        NAS_MMC_SndInterAnyCellSearchReq(&stAnycellSrchRatList, NAS_MMC_ANYCELL_SEARCH_SCENE_BUTT);
    }
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-22, end */

    return;
}




/*****************************************************************************
 函 数 名  : NAS_MMC_RcvBgPlmnSearchRsltCnf_OnPlmn
 功能描述  : 处理MMCMMC_BG_PLMN_SEARCH_RSLT_CNF消息
 输入参数  : ulEventType:消息类型
             pstMsg:     MMCMMC_BG_PLMN_SEARCH_RSLT_CNF消息
 输出参数  : 无
 返 回 值  : VOS_TRUE:函数处理完成
             VOS_FALSE:函数处理未完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2010年9月18日
   作    者   : z00161729
   修改内容   : 新生成函数

 2.日    期   : 2011年10月22日
   作    者   : w00167002
   修改内容   : V7R1 Phase II-2 增加HPLMN TIMER的事件上报

 3.日    期   : 2011年12月3日
   作    者   : w00167002
   修改内容   : DTS2011120300667:在背景搜时，可能有紧急呼业务，同时注册结果
                需要导致搜网，在等链接释放超时时，需要启动AVAILABLE 定时器，
                等此定时器超时后，发起搜网。
 4.日    期   : 2011年12月31日
   作    者   : w00166186
   修改内容   : DTS2011082902017,ON PLMN下注册被拒,搜网状态机重复搜索该网络
 5.日    期   : 2011年12月20日
   作    者   : h44270
   修改内容   : 退出BG搜网状态机时，通知APS当前所在网络
 6.日    期   : 2012年5月8日
   作    者   : z00161729
   修改内容   : GUL BG搜网调整:增加disable LTE场景
 7.日    期   : 2012年5月25日
   作    者   : w00176964
   修改内容   : GUL BG搜网调整:BG搜网退出时更新L1的additional值
 8.日    期   : 2012年6月11日
   作    者   : l60609
   修改内容   : AT&T&DCM：BG搜未完成后，时长非0，才启动10s周期性尝试定时器

 9.日    期   : 2012年9月3日
   作    者   : z40661
   修改内容   : DTS2012081801644,SIM卡的HPLMN长度为0时,其他周期性搜索特性打开时未启动周期性定时器
 10.日    期   : 2012年8月29日
    作    者   : w00176964
    修改内容   : 在UTRAN模式为FDD时候，时长非0或者支持ActingHplmn，才启动10s周期性尝试定时器
 11.日    期   : 2013年1月17日
    作    者   : s00217060
    修改内容   : for DSDA GUNAS C CORE:只有在UtranMode为TDD时，才不启HPLMN定时器
 12.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
 13.日    期   : 2013年12月20日
    作    者   : w00167002
    修改内容   : DTS2013112917981:guNAS删除在TD模式下不能进行bg搜的限制
                  快速找回TL，所以应尽量让其快速找回。
 14.日    期   : 2014年2月24日
    作    者   : w00176964
    修改内容   : High_Rat_Hplmn_Search特性调整:增加High_Prio_rat_hplmn定时器的启动处理
 15.日    期   : 2013年4月4日
    作    者   : y00176023
    修改内容   : DSDS GUNAS II项目:收到NO RF 启动定时器，迁移到ooc
 16.日    期   : 2014年3月21日
   作    者   : z00161729
   修改内容   : DTS2014032105704:国内TDS丢网瞬间找回原小区ps迁移modem1后不再回迁modem0
 17.日    期   : 2014年1月27日
    作    者   : s00246516
    修改内容   : L-C互操作项目:增加异系统到HRPD的处理
 18.日    期   : 2014年10月25日
    作    者   : b00269685
    修改内容   : 增加high rat TD count的处理
 19.日    期   : 2015年5月30日
    作    者   : l00324781
    修改内容   : CDMA 1X Iteration 12: lte下BG搜hrpd，成功，ue将要驻留到hrpd，lte处于从模，
                                        mmc状态设为hrpd
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvBgPlmnSearchRsltCnf_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMCMMC_BG_PLMN_SEARCH_RSLT_STRU                    *pstBgPlmnSearchRsltCnfMsg = VOS_NULL_PTR;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstHighPrioPlmnSearchList = VOS_NULL_PTR;

    VOS_UINT8                                               ucCsAttachAllowFlag;
    VOS_UINT8                                               ucPsAttachAllowFlag;
    NAS_MMC_TIMER_STATUS_ENUM_U8                            enAvailableTimerStatus;


    VOS_UINT32                                              ulSpecPlmnSearchFlg;

    /* 当前处在正常服务状态且未进行过搜网，则丢弃该消息，否则发起搜网 */
    ulSpecPlmnSearchFlg = NAS_MMC_GetSpecPlmnSearchState();


    /* 转换为BG搜结果消息 */
    pstBgPlmnSearchRsltCnfMsg = (NAS_MMCMMC_BG_PLMN_SEARCH_RSLT_STRU *)pstMsg;

    /* 获取高优先级搜网列表信息 */
    pstHighPrioPlmnSearchList = NAS_MMC_GetHighPrioPlmnList();

    /* 可维可测,将选网列表输出 */
    NAS_MMC_LogPlmnSelectionList(pstHighPrioPlmnSearchList);

    /* 如果当前存在NO RF，则迁移到OOC状态 */
    if (VOS_FALSE == NAS_MML_GetRfAvailFlg())
    {
        /* 处理丢网状态，上报服务状态，迁移到ooc，启动available定时器 */
        /* Modified by c00318887 for 预置频点搜网优化, 2015-9-10, begin */
        NAS_MMC_ProcCoverageLost_L1Main(NAS_MMC_PLMN_SEARCH_SCENE_BUTT);
        /* Modified by c00318887 for 预置频点搜网优化, 2015-9-10, end */

        return VOS_TRUE;
    }
    /* Added by s00246516 for L-C互操作项目, 2014-01-27, Begin */
#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    if (NAS_MMC_BG_PLMN_SEARCH_INTER_SYS_HRPD == pstBgPlmnSearchRsltCnfMsg->enRslt)
    {
        NAS_MMC_StopAllTimer();

        /* NAS_MMC_L1_STA_OOC-->NAS_MMC_L1_STA_DEACT, BG搜成功，UE会驻留到hRPD上，
            此时lte处于从模，mmc状态迁到DEACT
        */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_DEACT);

        OM_SetDrxTimerWakeSrc(VOS_GetModemIDFromPid(WUEPS_PID_MMC));
        NAS_MMC_SndDrxTimerInfo(VOS_TRUE);

        return VOS_TRUE;
    }
#endif
    /* Added by s00246516 for L-C互操作项目, 2014-01-27, End */
    NAS_MMC_StartHighPrioPlmnSearchTimer_BgSearch_OnPlmn(pstBgPlmnSearchRsltCnfMsg);

    if (VOS_TRUE == NAS_MMC_IsCampOnHighestPrioRatHplmn())
    {
        NAS_MMC_InitTdHighRatSearchCount();
    }

    NAS_MMC_NotifyModeChange(NAS_MML_GetCurrNetRatType(),
                             NAS_MML_GetSimPsRegStatus());

    /* 如果状态机退出结果为 NAS_MMC_BG_PLMN_SEARCH_SUCC，
       表明没有下一个可搜索高优先级网络且驻留在高优先级网络或vplmn上的情况，无需搜网 */
    if (NAS_MMC_BG_PLMN_SEARCH_SUCC == pstBgPlmnSearchRsltCnfMsg->enRslt)
    {
        /* 更新AdditionalAction的值 */
        NAS_MMC_SetRegRsltAdditionalAction_L1Main();

        ucCsAttachAllowFlag    = NAS_MML_GetCsAttachAllowFlg();
        ucPsAttachAllowFlag    = NAS_MML_GetPsAttachAllowFlg();
        enAvailableTimerStatus = NAS_MMC_GetTimerStatus(TI_NAS_MMC_AVAILABLE_TIMER);

        if((VOS_TRUE == NAS_MML_GetSvlteSupportFlag())
        && (VOS_FALSE == ucCsAttachAllowFlag)
        && (VOS_FALSE == ucPsAttachAllowFlag)
        && (NAS_MMC_TIMER_STATUS_RUNING != enAvailableTimerStatus))
        {
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_AVAILABLE_TIMER, NAS_MMC_GetNextAvailableTimerValue());
        }

        return VOS_TRUE;
    }

    /* 如果状态机退出结果为NAS_MMC_BG_PLMN_SEARCH_ABORTED,
       表明被外部消息打断，无需搜网，包含回vplmn失败和成功 */
    if (NAS_MMC_BG_PLMN_SEARCH_ABORTED == pstBgPlmnSearchRsltCnfMsg->enRslt)
    {
        /* 被外部打断退出状态机，需初始化高优先级列表 */
        NAS_MMC_InitPlmnSelectionList(NAS_MMC_PLMN_SEARCH_SCENE_HIGH_PRIO_PLMN_SEARCH,
                                      VOS_NULL_PTR,
                                      pstHighPrioPlmnSearchList);

        /* 当前MMC在搜网状态,如果MMC的服务状态为正常服务,先更新下服务状态 */
        if ((VOS_TRUE == NAS_MMC_IsNormalServiceStatus())
         && (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == ulSpecPlmnSearchFlg))
        {
            /* 更新为无服务状态并上报 */
            NAS_MMC_SetCsServiceStatus(NAS_MMC_NO_SERVICE);
            NAS_MMC_SetPsServiceStatus(NAS_MMC_NO_SERVICE);
            NAS_MMC_SndMsccServiceStatusInd(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MSCC_PIF_SERVICE_STATUS_NO_SERVICE);
        }

        /* abort退出有可能需要搜网,更新AdditionalAction的值 */
        NAS_MMC_SetRegRsltAdditionalAction_L1Main();

        return VOS_TRUE;
    }

    /* 若状态机退出结果为NAS_MMC_BG_PLMN_SEARCH_FAIL，有以下几种情况:
       1、无下一个高优先级网络且回VPLMN失败； 2、注册被拒导致卡无效；
       3、被接入层abort，被接入层abort无需初始化高优先级列表；4、等待系统消息超时；
       5、等待接入层搜网回复和等待停止搜网回复状态收到W的RRMM_REL_IND_STRU，且原因值为RRC_REL_CAUSE_OTHER_REASON */
    if ((NAS_MMC_BG_PLMN_SEARCH_FAIL == pstBgPlmnSearchRsltCnfMsg->enRslt)
     && (VOS_TRUE == pstBgPlmnSearchRsltCnfMsg->ulNeedPlmnSearch))
    {
        NAS_MMC_RcvBgPlmnSearchRsltCnfFail_OnPlmn(pstBgPlmnSearchRsltCnfMsg->enBgPlmnSearchScene,
                                                 &pstBgPlmnSearchRsltCnfMsg->stSearchedPlmnListInfo);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GenerateRegRsltCsDomainAdditionalAction_L1Main
 功能描述  : 在L1 MAIN状态收到选网状态机的注册结果时，获取到的CS域的AdditionalAction
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
              NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON:在正常服务状态
              NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL:卡无效
              NAS_MMC_ADDITIONAL_ACTION_BUTT
              NAS_MMC_ADDITIONAL_ACTION_CELL_SELECTION:注册被拒原因#12
              NAS_MMC_ADDITIONAL_ACTION_ACCESS_BARRED:接入受限
              NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON:在ON PLMN状态受限驻留
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月21日
    作    者   : w00167002
    修改内容   : 新增函数
  2.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_GenerateRegRsltCsDomainAdditionalAction_L1Main( VOS_VOID )
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsCause;          /* 存储注册区CS域被拒信息 */
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enPsCause;          /* 存储注册区PS域被拒信息 */

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_MS_MODE_ENUM_UINT8                              enMsMode;

    /* 获取LTE下的UE模式 */
    enMsMode = NAS_MML_GetMsMode();
#endif

    enCsCause = NAS_MML_REG_FAIL_CAUSE_BUTT;
    enPsCause = NAS_MML_REG_FAIL_CAUSE_BUTT;

    NAS_MMC_GetDomainRegStatusInRegInfoList( NAS_MML_GetCurrCampPlmnId(),
                                             NAS_MML_GetCurrNetRatType(),
                                             &enCsCause,
                                             &enPsCause );

    /* 根据CS的服务状态设置CS的addition值 */
    if ( VOS_TRUE == NAS_MMC_IsCsNormalService() )
    {
        return NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;
    }

    /* CS卡无效 */
    if (VOS_FALSE == NAS_MML_GetSimCsRegStatus())
    {
        return NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL;
    }

    /* 注册失败原因值#12的处理 */
    if ( NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW == enCsCause )
    {
        return NAS_MMC_ADDITIONAL_ACTION_CELL_SELECTION;
    }

    /* 接入受限ACCESS BAR 的处理 */
    if ( NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED == enCsCause )
    {
        return NAS_MMC_ADDITIONAL_ACTION_ACCESS_BARRED;
    }

#if (FEATURE_ON == FEATURE_LTE)

    /* L模下PS only时，CS域的Addition值为BUTT */
    if ( (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
      && (NAS_MML_MS_MODE_PS_ONLY  == enMsMode) )
    {
        return NAS_MMC_ADDITIONAL_ACTION_BUTT;
    }
#endif

    /* 否则在收到注册结果时设置当前为限制驻留 */
    return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;

}


/*****************************************************************************
 函 数 名  : NAS_MMC_GenerateRegRsltPsDomainAdditionalAction_L1Main
 功能描述  : 在L1 MAIN状态收到选网状态机的注册结果时，获取到的PS域的AdditionalAction
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
              NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON:在正常服务状态
              NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL:卡无效
              NAS_MMC_ADDITIONAL_ACTION_CELL_SELECTION:注册被拒原因#12
              NAS_MMC_ADDITIONAL_ACTION_ACCESS_BARRED:接入受限
              NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON:在ON PLMN状态受限驻留
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月21日
    作    者   : w00167002
    修改内容   : 新增函数
  2.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_GenerateRegRsltPsDomainAdditionalAction_L1Main( VOS_VOID )
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCsCause;                              /* 存储注册区CS域被拒信息 */
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enPsCause;                              /* 存储注册区PS域被拒信息 */

    enCsCause = NAS_MML_REG_FAIL_CAUSE_BUTT;
    enPsCause = NAS_MML_REG_FAIL_CAUSE_BUTT;

    NAS_MMC_GetDomainRegStatusInRegInfoList( NAS_MML_GetCurrCampPlmnId(),
                                             NAS_MML_GetCurrNetRatType(),
                                             &enCsCause,
                                             &enPsCause );
    /* PS卡无效 */
    if (VOS_FALSE == NAS_MML_GetSimPsRegStatus())
    {
        return NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL;
    }

    /* 注册失败原因值#12的处理 */
    if ( NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW == enPsCause )
    {
        return NAS_MMC_ADDITIONAL_ACTION_CELL_SELECTION;
    }

    /* 接入受限ACCESS BAR 的处理 */
    if ( NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED == enPsCause )
    {
        return NAS_MMC_ADDITIONAL_ACTION_ACCESS_BARRED;
    }

     /* 根据PS的服务状态设置PS的addition值 */
    if (VOS_TRUE == NAS_MMC_IsPsNormalService())
    {
        return NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;
    }

    /* 否则在收到注册结果时设置当前为限制驻留 */
    return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;

}


/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedEnterOocStatusWhenAreaLost_OnPlmn
 功能描述  : 判断接入层上报丢网之后是否需要立即进入OOC状态
 输入参数  : NAS_MMC_PLMN_SEARCH_TYPE_ENUM_UINT32                    enSearchedType
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月21日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MMC_IsNeedEnterOocStatusWhenAreaLost_OnPlmn(
    NAS_MMC_SEARCHED_TYPE_STRU                             *pstSearchedType
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList  = VOS_NULL_PTR;

    pstPrioRatList  = NAS_MML_GetMsPrioRatList();

    /* 多模时，不需要立即进入OOC状态 */
    if (1 != pstPrioRatList->ucRatNum)
    {
        return VOS_FALSE;
    }

    /* 没有信息时，默认没有搜过，不进入OOC状态 */
    if (VOS_NULL_PTR == pstSearchedType)
    {
        return VOS_FALSE;
    }

    /* 单模时，如果当前模式下已进行过spec搜索或pref band搜索，可以进入OOC状态 */
    if ((VOS_TRUE == pstSearchedType->ucPrefBandSearchedFlg)
     || (VOS_TRUE == pstSearchedType->ucSpecSearchedFlg))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-22, begin */
/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedAnycell_OnPlmn
 功能描述  : 判断是否需要进行anycell搜网
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 需要进行anycell搜网
             VOS_FALSE - 无需进行anycell搜网
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月21日
    作    者   : z00161729
    修改内容   : 新增函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedAnycell_OnPlmn( VOS_VOID )
{
    /* 卡无效需要进行anycell搜 */
    if (VOS_FALSE == NAS_MML_IsUsimStausValid())
    {
        return VOS_TRUE;
    }

    /* 如果存在缓存的紧急呼业务，需要anycell搜网 */
    if (VOS_TRUE == NAS_MML_IsExistBufferedEmgCall())
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-22, end */

/*****************************************************************************
 函 数 名  : NAS_MMC_IsPlmnListTriggerPlmnSrch_L1Main
 功能描述  : 判断PLMN LIST是否触发搜网
 输入参数  : pstListRslt-PLMN LIST退出结果
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 需要进行搜网
             VOS_FALSE - 无需进行搜网
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月7日
    作    者   : w0176964
    修改内容   : 新增函数
  2.日    期   : 2012年8月21日
    作    者   : w00176964
    修改内容   : DTS2012111404729:开机驻留到ACC BAR小区，发起用户LIST搜网
                 只搜到当前网络后,后续反复触发内部LIST搜网
  3.日    期   : 2012年12月07日
    作    者   : w00176964
    修改内容   : DTS2012120401487:L下detach CS/PS后用户LIST搜网结束应该不搜网
  4.日    期   : 2013年11月25日
    作    者   : z00161729
    修改内容    : SVLTE优化G-TL ps切换性能修改
  5.日    期   : 2014年1月17日
    作    者   : w00242748
    修改内容   : DTS2014011516578:UE当前驻留小区ACCESS BAR后，进行列表搜，UE再次
                 发起搜网，ACCESS BAR情况下不应发起搜网，enPsAdditionalAction误写成
                 enCsAdditionalAction。
  6.日    期   : 2014年01月17日
    作    者   : l00198894
    修改内容   : V9R1C53 C+L 离网重选项目
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsPlmnListTriggerPlmnSrch_L1Main(
    NAS_MMCMMC_PLMN_LIST_RSLT_STRU     *pstListRslt
)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;
    VOS_UINT32                                              ucSpecPlmnSearchFlg;
    VOS_UINT8                                               ucPsAttachAllow;

    VOS_UINT8                                   ucIsSvlteSupportFlg;
    VOS_UINT8                                   ucLcEnableFlg;

    ucIsSvlteSupportFlg  = NAS_MML_GetSvlteSupportFlag();
    ucLcEnableFlg        = NAS_MML_GetLcEnableFlg();

    enCsAdditionalAction = NAS_MMC_GetCsRegAdditionalAction_L1Main();
    enPsAdditionalAction = NAS_MMC_GetPsRegAdditionalAction_L1Main();
    enAdditionalAction   = NAS_MMC_GetPrioAddtionalAction(enCsAdditionalAction, enPsAdditionalAction);

    ucSpecPlmnSearchFlg = NAS_MMC_GetSpecPlmnSearchState();

    ucPsAttachAllow = NAS_MML_GetPsAttachAllowFlg();

    /* 驻留态时,当前为acc bar或被12拒绝或CS/PS被detach时不需要再次发起搜网 */
    if ((NAS_MMC_AS_CELL_CAMP_ON == NAS_MMC_GetAsCellCampOn())
     && (NAS_MMC_SPEC_PLMN_SEARCH_STOP == ucSpecPlmnSearchFlg))
    {
        /* 在非SVLTE或C+L形态时，CS/PS被禁无需再次发起搜网 */
        if ( (VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
          && (VOS_FALSE == ucIsSvlteSupportFlg)
          && (VOS_FALSE == ucLcEnableFlg)
          && (VOS_FALSE == ucPsAttachAllow) )
        {
            return VOS_FALSE;
        }

        if ((NAS_MMC_ADDITIONAL_ACTION_ACCESS_BARRED == enCsAdditionalAction)
         || (NAS_MMC_ADDITIONAL_ACTION_ACCESS_BARRED == enPsAdditionalAction))
        {
            return VOS_FALSE;
        }

        if ((NAS_MMC_ADDITIONAL_ACTION_CELL_SELECTION == enCsAdditionalAction)
         || (NAS_MMC_ADDITIONAL_ACTION_CELL_SELECTION == enPsAdditionalAction))
        {
            return VOS_FALSE;
        }
    }

    /* 如果LIST搜网退出后导致搜网需要触发搜网
       如果LIST搜网过程中注册被拒导致卡无效,退出后不会携带搜网标志,
       需要根据addition值进行一次判断 */
#if (FEATURE_ON == FEATURE_LTE)
    if (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS == NAS_MML_GetLteCapabilityStatus())
    {
        return VOS_TRUE;
    }
#endif

    if (VOS_TRUE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(enAdditionalAction))
    {
        return VOS_TRUE;
    }

    if (VOS_TRUE == pstListRslt->ucNeedPlmnSearch)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsAnycellSrchSuccStartAvailableTimer_Initial
 功能描述  : 判断Anycell搜网成功时是否需要启动Available定时器
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 需要启动Available定时器
             VOS_FALSE - 无需启动Available定时器
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月27日
    作    者   : s00217060
    修改内容   : 新增函数
  2.日    期   : 2013年11月01日
    作    者   : l00208543
    修改内容   : 根据卡类型禁止网络制式
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsAnycellSrchSuccStartAvailableTimer_Initial( VOS_VOID )
{
    VOS_UINT32                                ulLteOnlyFlg;
    VOS_UINT32                                ulGsmOnlyFlg;
    VOS_UINT32                                ulGsmForbFlg;
    NAS_MML_SIM_TYPE_ENUM_UINT8               enSimType;

    ulLteOnlyFlg   = NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList());
    ulGsmOnlyFlg   = NAS_MML_IsGsmOnlyMode(NAS_MML_GetMsPrioRatList());
    ulGsmForbFlg   = NAS_MML_GetGsmForbidFlg();
    enSimType      = NAS_MML_GetSimType();

    /* 如果UE配置的网络制式都被禁止，则不启动Available Timer定时器*/
    if (VOS_TRUE == NAS_MML_IsAllMsRatInForbiddenList())
    {
        return VOS_FALSE;
    }


    /* 满足以下条件中的任何一个时，不需要启动Available定时器
       1)卡无效
       2) 卡有效，卡类型是SIM卡并且是LTE only
       3) 卡有效，USIM卡禁止GSM并且用户设置GSM only */

    if ( VOS_FALSE == NAS_MML_IsUsimStausValid())
    {
        return VOS_FALSE;
    }

    /* SIM卡并且是LTE only时,不启动Available定时器 */
    if ( (NAS_MML_SIM_TYPE_SIM == enSimType)
      && (VOS_TRUE == ulLteOnlyFlg) )
    {
        return VOS_FALSE;
    }

    /* USIM卡禁止GSM并且用户设置GSM only,不启动Available定时器 */
    if ( (VOS_TRUE == ulGsmForbFlg)
      && (VOS_TRUE == ulGsmOnlyFlg) )
    {
        return VOS_FALSE;
    }

    /* 其他情况下有卡启动Available定时器 */
    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrmmLimitServiceCampInd_OnPlmn
 功能描述  : 处理RRMM_LIMIT_SERVICE_CAMP_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:     MMCMMC_BG_PLMN_SEARCH_RSLT_CNF消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年06月24日
   作    者   : l65478
   修改内容   : 新生成函数
 2.日    期   : 2015年10月21日
   作    者   : s00217060
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0修改
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrmmLimitServiceCampInd_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                *pastIntraPlmnSrchInfo = VOS_NULL_PTR;
    RRMM_LIMIT_SERVICE_CAMP_IND_STRU                    *pstRrmmLimitCampOnMsg;
    VOS_UINT32                                           ulRatCnt;

    pstRrmmLimitCampOnMsg = (RRMM_LIMIT_SERVICE_CAMP_IND_STRU *)pstMsg;

    pastIntraPlmnSrchInfo = (NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                                             sizeof(NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU) * NAS_MML_MAX_RAT_NUM);
    /* 分配内存失败 */
    if (VOS_NULL_PTR == pastIntraPlmnSrchInfo)
    {
        return VOS_FALSE;
    }

    PS_MEM_SET(pastIntraPlmnSrchInfo, 0, sizeof(NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU) * NAS_MML_MAX_RAT_NUM);

    for (ulRatCnt = 0; ulRatCnt < NAS_MML_MAX_RAT_NUM; ulRatCnt++)
    {
        pastIntraPlmnSrchInfo[ulRatCnt].enRatType = NAS_MML_NET_RAT_TYPE_BUTT;
    }

    NAS_MMC_InitSearchedPlmnListInfo(pastIntraPlmnSrchInfo);

    /* 转换W下的网络格式 */
    NAS_MMC_UpdateSearchedPlmnListInfo(VOS_NULL_PTR, &(pstRrmmLimitCampOnMsg->stPlmnIdList), pastIntraPlmnSrchInfo);

    /* 删除列表中禁止的PLMN */
    NAS_MMC_DelForbPlmnFromAsSrchedPlmnList(pastIntraPlmnSrchInfo);

    /* 手动搜网模式下删除非用户指定的PLMN */
    NAS_MMC_DelNotUserSpecPlmnFromSrchedPlmnList(pastIntraPlmnSrchInfo);

    /* 可维可测信息勾出 */
    NAS_MMC_LogAsPlmnList(pastIntraPlmnSrchInfo);

    if (VOS_TRUE == NAS_MMC_IsExistAvailPlmnInSearchedPlmnList(pastIntraPlmnSrchInfo))
    {
        NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

        NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_INTER_SYS_OOS, pastIntraPlmnSrchInfo, NAS_MML_MAX_RAT_NUM);
    }

    PS_MEM_FREE(WUEPS_PID_MMC, pastIntraPlmnSrchInfo);

    return VOS_TRUE;
}

/* NAS_MMC_DelForbPlmnFromAsSrchedPlmnList、NAS_MMC_DelNotUserSpecPlmnFromSrchedPlmnList
   函数移至NasMmcCommFunc.c中 */



#if (FEATURE_MULTI_MODEM == FEATURE_ON)
/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMsccNcellInfoNotify_OnPlmn
 功能描述  : 处理ID_MSCC_MMC_NCELL_INFO_NOTIFY消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:     消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月25日
   作    者   : z00161729
   修改内容   : SVLTE支持NCELL搜网
 2.日    期   : 2014年1月26日
   作    者   : z00161729
   修改内容   : DTS2014012305088：支持增强NCELL搜网，如果Modem1传递过来的邻区信息不存在的情况下，通过历史频点支持NCELL搜索
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccNcellInfoNotify_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_AVAILABLE_TIMER))
    {
        NAS_MMC_StopTimer(TI_NAS_MMC_AVAILABLE_TIMER);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_AVAILABLE_TIMER, TI_NAS_MMC_NCELL_PLMN_SEARCH_AVAILABLE_TIMER_LEN);
    }
    return VOS_TRUE;
}
#endif

/*****************************************************************************
 函 数 名  : NAS_MMC_IsSingleDomainRegFailNeedPlmnSrchCause
 功能描述  : 判断在单域注册失败时是否需要发起搜网
 输入参数  : VOS_VOID
 输出参数  : VOS_TRUE : 需要发起搜网
             VOS_FALSE: 不需要发起搜网
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年06月24日
   作    者   : l65478
   修改内容   : 新生成函数
 2.日    期   : 2013年10月17日
   作    者   : l65478
   修改内容   : DTS2013102207188:DT需求:在PS单域失败#14时也需要发起搜网
*****************************************************************************/
VOS_UINT32  NAS_MMC_IsSingleDomainRegFailNeedPlmnSrchCause(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause
)
{
    switch (enCause)
    {
    case NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE:
    case NAS_MML_REG_FAIL_CAUSE_SEMANTICALLY_INCORRECT_MSG:
    case NAS_MML_REG_FAIL_CAUSE_INVALID_MANDATORY_INF:
    case NAS_MML_REG_FAIL_CAUSE_MSG_NONEXIST_NOTIMPLEMENTE:
    case NAS_MML_REG_FAIL_CAUSE_IE_NONEXIST_NOTIMPLEMENTED:
    case NAS_MML_REG_FAIL_CAUSE_PROTOCOL_ERROR:
    case NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT:
    case NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL:
    case NAS_MML_REG_FAIL_CAUSE_RR_CONN_FAIL:
    case NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE:
    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
        return VOS_TRUE;
    default:
        return VOS_FALSE;
    }
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsSingleDomainRegFailNeedPlmnSrch
 功能描述  : 判断在单域注册失败时是否需要发起搜网
 输入参数  : VOS_VOID
 输出参数  : VOS_TRUE : 需要发起搜网
             VOS_FALSE: 不需要发起搜网
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年06月24日
   作    者   : l65478
   修改内容   : 新生成函数
 2.日    期   : 2013年10月17日
   作    者   : l65478
   修改内容   : DTS2013102207188:DT需求:在PS单域失败#14时也需要发起搜网

 3.日    期   : 2014年5月21日
   作    者   : w00167002
   修改内容   : DTS2014051602857:在SOR打开时候，如果CS注册失败达到4次，则等周期
                搜网定时器超时发起LIST搜网，如果当前仅有原有网络，则发起LAU,否则
                触发MM发起LAU;如果LIST搜后，发现有其他网络，则发起其他网络的搜网注册。

*****************************************************************************/
VOS_UINT32  NAS_MMC_IsSingleDomainRegFailNeedPlmnSrch(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16      enRegFailDomain
)
{
    VOS_UINT8                           ucSingleDomainSrchFlag;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCsCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enPsCause;
    NAS_MMC_SERVICE_ENUM_UINT8          enCsService;
    NAS_MMC_SERVICE_ENUM_UINT8          enPsService;

    ucSingleDomainSrchFlag    = NAS_MML_GetDtSingleDomainPlmnSearchFlag();


    /* 原因值初始化为BUT,默认不搜网 */
    enCsCause   = NAS_MML_REG_FAIL_CAUSE_BUTT;
    enPsCause   = NAS_MML_REG_FAIL_CAUSE_BUTT;

    enCsService = NAS_MMC_GetCsServiceStatus();
    enPsService = NAS_MMC_GetPsServiceStatus();

    NAS_MMC_GetDomainRegStatusInRegInfoList( NAS_MML_GetCurrCampPlmnId(),
                                             NAS_MML_GetCurrNetRatType(),
                                             &enCsCause,
                                             &enPsCause );


    /* SOR定制打开时候，CS注册失败#17，需要发起LIST搜网 */
    if ((VOS_TRUE                               == NAS_MML_GetCsRejSearchSupportFlg())
     && (NAS_MSCC_PIF_SRVDOMAIN_CS                   == enRegFailDomain)
     && (NAS_MMC_LIMITED_SERVICE                == enCsService)
     && (NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE == enCsCause))
    {
        return VOS_TRUE;
    }

    /* 单域功能打开,是限制服务,原因值是网络拒绝OTHER CAUSE,需要搜网 */
    if ((VOS_TRUE == NAS_MMC_IsSingleDomainRegFailNeedPlmnSrchCause(enCsCause))
     && (NAS_MSCC_PIF_SRVDOMAIN_CS    == enRegFailDomain)
     && (NAS_MMC_LIMITED_SERVICE == enCsService)
     && (VOS_TRUE                == ucSingleDomainSrchFlag))
    {
        return VOS_TRUE;
    }

    if ((VOS_TRUE == NAS_MMC_IsSingleDomainRegFailNeedPlmnSrchCause(enPsCause))
     && (NAS_MSCC_PIF_SRVDOMAIN_PS    == enRegFailDomain)
     && (NAS_MMC_LIMITED_SERVICE == enPsService)
     && (VOS_TRUE                == ucSingleDomainSrchFlag))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-10, begin */
/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMsccImsVoiceCapInd_OnPlmn
 功能描述  : 在ON PLMN时候收到ID_MSCC_MMC_IMS_VOICE_CAP_IND消息的处理
 输入参数  : ulEventType:ID_MSCC_MMC_IMS_VOICE_CAP_IND消息类型
             pstMsg: ID_MSCC_MMC_IMS_VOICE_CAP_IND消息首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE: 函数处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月10日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMsccImsVoiceCapInd_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
#if (FEATURE_ON == FEATURE_LTE)

    /* 进入ON PLMN的场景都是需要Disable L模的 */

    NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

    /* 发起内部搜网 */
    NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_DISABLE_LTE, VOS_NULL_PTR, 0);

#endif

    return VOS_TRUE;
}

/* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-10, end */


#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMsccImsSwitchStateInd_OnPlmn
 功能描述  : 在ON PLMN时候收到ID_MSCC_MMC_IMS_SWITCH_STATE_IND消息的处理
 输入参数  : ulEventType:ID_MSCC_MMC_IMS_SWITCH_STATE_IND消息类型
             pstMsg: ID_MSCC_MMC_IMS_SWITCH_STATE_IND消息首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE: 函数处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月04日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMsccImsSwitchStateInd_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 启动选网状态机进行网络获取和注册 */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

    /* enable lte后需要触发搜网，发送内部搜网消息 */
    NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_ENABLE_LTE_PLMN_SEARCH, VOS_NULL_PTR, 0);

    return VOS_TRUE;
}
#endif

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMsccVoiceDomainChangeInd_OnPlmn
 功能描述  : 在ON PLMN时候收到ID_MSCC_MMC_VOICE_DOMAIN_CHANGE_IND消息的处理
 输入参数  : ulEventType:ID_MSCC_MMC_VOICE_DOMAIN_CHANGE_IND消息类型
             pstMsg: ID_MSCC_MMC_VOICE_DOMAIN_CHANGE_IND消息首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE: 函数处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月04日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMsccVoiceDomainChangeInd_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 启动选网状态机进行网络获取和注册 */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

    /* enable lte后需要触发搜网，发送内部搜网消息 */
    NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_ENABLE_LTE_PLMN_SEARCH, VOS_NULL_PTR, 0);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_StartHighPrioRatHplmnTimer_BgSearch_OnPlmn
 功能描述  : 处理BG搜网状态机退出结果后启动高优先级搜网相关定时器的处理
 输入参数  : pstBgPlmnSearchRsltCnfMsg:BG搜退出结果消息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年2月24日
   作    者   : w00176964
   修改内容   : 新建函数
 2.日    期   : 2014年4月10日
   作    者   : w00242748
   修改内容   : DTS2014040905679:接入技术顺序030201，当前驻留在GSM上，
                高优先级接入技术HPLMN搜索L失败，搜索W成功并成功注册后，再次
                启动高优先级接入技术HPLMN时，定时器时长不正确。
13.日    期   : 2014年10月27日
   作    者   : b00269685
   修改内容   : 增加High_Prio_rat_hplmn TD Count的处理
*****************************************************************************/
VOS_VOID  NAS_MMC_StartHighPrioPlmnSearchTimer_BgSearch_OnPlmn(
    NAS_MMCMMC_BG_PLMN_SEARCH_RSLT_STRU                    *pstBgPlmnSearchRsltCnfMsg
)
{
    VOS_UINT32                          ulHplmnTimerLen;
    VOS_UINT8                           ucActingHplmnSupportFlg;

    if (VOS_TRUE == NAS_MMC_IsNeedStartHighPrioRatHPlmnTimer())
    {
        if (VOS_TRUE == pstBgPlmnSearchRsltCnfMsg->ulSearchCompleted)
        {
           ulHplmnTimerLen = NAS_MMC_GetHighPrioRatHplmnTimerLen();
        }
        else
        {
           ulHplmnTimerLen = NAS_MMC_GetHighPrioRatHplmnTimerRetryLen();
        }

        if (VOS_TRUE == NAS_MMC_StartTimer(TI_NAS_MMC_HIGH_PRIO_RAT_HPLMN_TIMER, ulHplmnTimerLen))
        {
            if (VOS_TRUE == pstBgPlmnSearchRsltCnfMsg->ulSearchCompleted)
            {
                NAS_MMC_AddCurHighPrioRatHplmnTimerFirstSearchCount_L1Main();
                NAS_MMC_UpdateHighPrioRatHPlmnTimerTdCount();
            }
        }

        /* 高RAT的BG搜网定时器需要启动时,Hplmn或10S周期性尝试BG搜网定时器可不自动 */
        return;
    }

    if (VOS_TRUE == pstBgPlmnSearchRsltCnfMsg->ulSearchCompleted)
    {
        if (VOS_TRUE == NAS_MMC_IsNeedStartHPlmnTimer())
        {
            /* 启动定时器 */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_HPLMN_TIMER, NAS_MMC_GetHplmnTimerLen());

            /* HPLMN TIMER启动事件上报 */
            NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_HPLMN_TIMER_START,
                            VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

            /* 将HPLMN启动类型设置为非首次启动 */
            NAS_MMC_SetFirstStartHPlmnTimerFlg(VOS_FALSE);
        }
    }
    else
    {
        /* 在UTRAN模式为FDD时候，时长非0或者支持ActingHplmn，才启动10s周期性尝试定时器 */
        ucActingHplmnSupportFlg = NAS_MML_GetActingHplmnSupportFlg();

        /* 驻留到HPLMN时,Hplmn或10S周期性尝试BG搜网定时器可不自动 */
        if (VOS_TRUE == NAS_MML_ComparePlmnIdWithHplmn(NAS_MML_GetCurrCampPlmnId()))
        {
            return;
        }

        if ((0 != NAS_MMC_GetHplmnTimerLen())
         || (VOS_TRUE == ucActingHplmnSupportFlg))
        {
            /* FDD下启动周期高优先级尝试定时器 */
            if ( NAS_UTRANCTRL_UTRAN_MODE_TDD != NAS_UTRANCTRL_GetCurrUtranMode() )
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_HIGH_PRIO_PLMN_SEARCH, TI_NAS_MMC_PERIOD_TRYING_HIGH_PRIO_PLMN_SEARCH_LEN);
            }
            /* TDD下重新启动高优先级搜定时器 */
            else
            {
                /* 启动定时器 */
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_HPLMN_TIMER, NAS_MMC_GetHplmnTimerLen());

                /* HPLMN TIMER启动事件上报 */
                NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_HPLMN_TIMER_START,
                                VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

                /* 将HPLMN启动类型设置为非首次启动 */
                NAS_MMC_SetFirstStartHPlmnTimerFlg(VOS_FALSE);
            }
        }
    }

    return;
}

/* Added by s00246516 for L-C互操作项目, 2014-02-13, Begin */
/*****************************************************************************
 函 数 名  : NAS_MMC_IsRegReqTriggerPlmnSrch_L1Main
 功能描述  : 判断MSCC的REG REQ是否触发搜网
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 需要进行搜网
             VOS_FALSE - 无需进行搜网
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月13日
    作    者   : s00246516
    修改内容   : 新增函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsRegReqTriggerPlmnSrch_L1Main(
    MSCC_MMC_REG_REQ_STRU                         *pstRegReq
)
{
    NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM_UINT8        enRegPlmnPrioClass;

    /* 非正常服务需要发起搜网 */
    if (VOS_FALSE == NAS_MMC_IsNormalServiceStatus())
    {
        return VOS_TRUE;
    }

    enRegPlmnPrioClass = NAS_MMC_GetPlmnPrioClass(NAS_MML_GetCurrCampPlmnId());

    /* 当前网络为满足要求网络则不需要发起搜网 */
    if (VOS_TRUE == pstRegReq->bitOpPrioClass)
    {
        if (VOS_TRUE == NAS_MMC_ComParePlmnPrioClass(enRegPlmnPrioClass, pstRegReq->enPrioClass))
        {
            return VOS_FALSE;
        }
    }
    else if (VOS_TRUE == pstRegReq->bitOpCellInfo)
    {
        if (VOS_TRUE == NAS_MMC_IsSuccRegInSpecCellInfo(&(pstRegReq->stCellInfo)))
        {
            return VOS_FALSE;
        }
    }
    else
    {
        /* 正常服务，REG请求中没有指定需要注册的条件，这种情况属于异常保护，不发起搜网 */
        return VOS_FALSE;
    }

    return VOS_TRUE;
}
/* Added by s00246516 for L-C互操作项目, 2014-02-13, End */

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMsccPlmnSrchReq_Ooc
 功能描述  : OOC状态收到MSCC的PLMN搜索请求的处理
 输入参数  : ulEventType:消息类型
            : pstMsg:消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE:
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月2日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccPlmnSrchReq_Ooc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

    /* 卡无效，启动ANY CELL状态机 */
    if ( VOS_FALSE == NAS_MML_IsUsimStausValid())
    {
        NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_ANYCELL_SEARCH);
    }
    else
    {
        NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_PLMN_SELECTION);
    }

    NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,
                             NAS_MML_GetSimPsRegStatus());

    return VOS_TRUE;
}




/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMsccPlmnSrchReq_Deact
 功能描述  : Deactive状态收到MSCC的PLMN搜索请求的处理,处理方式和OCC状态下相同，
            直接调用NAS_MMC_RcvMsccPlmnSrchReq_Ooc
 输入参数  : ulEventType:消息类型
            : pstMsg:消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE:
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月日
    作    者   : l00324781
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccPlmnSrchReq_Deact(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    return NAS_MMC_RcvMsccPlmnSrchReq_Ooc(ulEventType, pstMsg);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetLteCoverageFlg_L1Main
 功能描述  : 根据搜网结果获取LTE的覆盖标记
 输入参数  : pstPlmnSelectionRslt ---- 搜网结果
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月17日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8  NAS_MMC_GetLteCoverageFlg_L1Main(
    NAS_MMCMMC_PLMN_SELECTION_RSLT_STRU                    *pstPlmnSelectionRslt
)
{
    VOS_UINT8                           ucRatIndex;

    for (ucRatIndex = 0; ucRatIndex < NAS_MML_MAX_RAT_NUM; ucRatIndex++)
    {
        if (NAS_MML_NET_RAT_TYPE_LTE == pstPlmnSelectionRslt->astSearchRatInfo[ucRatIndex].enRatType)
        {
            if (NAS_MMC_COVERAGE_TYPE_NONE == pstPlmnSelectionRslt->astSearchRatInfo[ucRatIndex].enCoverageType)
            {
                return VOS_FALSE;
            }
            else
            {
                return VOS_TRUE;
            }
        }
    }

    return VOS_FALSE;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedHistorySearch_L1Main
 功能描述  : 是否需要进行history搜网
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月25日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8  NAS_MMC_IsNeedHistorySearch_L1Main(VOS_VOID)
{

    NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU              *pstPhaseOneOosPlmnSearchPatternInfo  = VOS_NULL_PTR;
    NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU              *pstPhaseTwoOosPlmnSearchPatternInfo  = VOS_NULL_PTR;
    VOS_UINT32                                              ulCurHistoryCount = 0;
    VOS_UINT8                                               ucTotalHistoryCount = 0;


    pstPhaseOneOosPlmnSearchPatternInfo         = NAS_MMC_GetPhaseOneOosPlmnSearchPatternInfo();
    pstPhaseTwoOosPlmnSearchPatternInfo         = NAS_MMC_GetPhaseTwoOosPlmnSearchPatternInfo();
    ulCurHistoryCount                           = NAS_MMC_GetCurHistorySearchTimerCount_OnPlmn();


    /* 定时器类型不是history类型，不需要history搜 */
    if (NAS_MMC_AVAILABLE_TIMER_TYPE_HISTORY != NAS_MMC_GetAvailableTimerType_OnPlmn())
    {
        return VOS_FALSE;
    }

    if (NAS_MMC_OOS_PHASE_ONE == NAS_MMC_GetOosPhaseNum())
    {
        /* 第一阶段 */
        ucTotalHistoryCount = pstPhaseOneOosPlmnSearchPatternInfo->ucHistoryNum;
    }
    else
    {
         /* 第二阶段 */
        ucTotalHistoryCount = pstPhaseTwoOosPlmnSearchPatternInfo->ucHistoryNum;
    }

    /* 设定历史搜次数为0，不需要历史搜 */
    if (0 == ucTotalHistoryCount)
    {
        return VOS_FALSE;
    }

    /* 当前历史启动次数 < 设定历史搜次数，需要history搜 */
    if (ulCurHistoryCount < ucTotalHistoryCount)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;


}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedPrefBandSearch_L1Main
 功能描述  : 是否需要进行PrefBand搜网
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月10日
    作    者   : h00281185
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8  NAS_MMC_IsNeedPrefBandSearch_L1Main(VOS_VOID)
{
    NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU              *pstPhaseOneOosPlmnSearchPatternInfo  = VOS_NULL_PTR;
    NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU              *pstPhaseTwoOosPlmnSearchPatternInfo  = VOS_NULL_PTR;
    NAS_MMC_AVAILABLE_TIMER_TYPE_ENUM_UINT8                 enAvailableType;
    VOS_UINT32                                              ulCurPrefBandCount;
    VOS_UINT8                                               ucTotalPrefBandCount = 0;


    pstPhaseOneOosPlmnSearchPatternInfo          = NAS_MMC_GetPhaseOneOosPlmnSearchPatternInfo();
    pstPhaseTwoOosPlmnSearchPatternInfo          = NAS_MMC_GetPhaseTwoOosPlmnSearchPatternInfo();
    ulCurPrefBandCount                           = NAS_MMC_GetCurPrefBandSearchTimerCount_OnPlmn();
    enAvailableType                              = NAS_MMC_GetAvailableTimerType_OnPlmn();


    /* 定时器类型不是history类型也不是PrefBand类型，不需要PrefBand搜 */
    if ((NAS_MMC_AVAILABLE_TIMER_TYPE_HISTORY   != enAvailableType)
     && (NAS_MMC_AVAILABLE_TIMER_TYPE_PREFBAND  != enAvailableType))
    {
        return VOS_FALSE;
    }

    if (NAS_MMC_OOS_PHASE_ONE == NAS_MMC_GetOosPhaseNum())
    {
        /* 第一阶段 */
        ucTotalPrefBandCount = pstPhaseOneOosPlmnSearchPatternInfo->ucPrefBandNum;
    }
    else
    {
         /* 第二阶段 */
        ucTotalPrefBandCount = pstPhaseTwoOosPlmnSearchPatternInfo->ucPrefBandNum;
    }

    /* PrefBand搜次数设定为0，不需要PrefBand搜 */
    if (0 == ucTotalPrefBandCount)
    {
        return VOS_FALSE;
    }

    /* 当前PrefBand启动次数 < 设定PrefBand搜次数，需要PrefBand搜 */
    if (ulCurPrefBandCount < ucTotalPrefBandCount)
    {
        return VOS_TRUE;
    }


    return VOS_FALSE;

}


#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmResumeInd_Deact
 功能描述  : 处理LMM消息lMM_MMC_RESUME_IND
 输入参数  : ulEventType  VOS_UINT32
           : pstMsg         struct MsgCB *
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月2日
    作    者   : l00324781
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmResumeInd_Deact(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_ON_PLMN);

    /* 复用以前代码: 异系统切换LTE-->HRPD,失败，回退到LTE, 收到RESUME_IND消息的处理流程
        实现功能相同，收到RESUME_IND消息，设置状态机、起定时器，等待LMM_MMC_SYS_INFO_IND消息
    */
    NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_INTER_SYS_CELLRESEL);

    return VOS_TRUE;
}
/*****************************************************************************
 函 数 名  : NAS_MMC_ProcCsfbRedirFailBackLte_L1Main
 功能描述  : 收到MMCMM_PLMN_SEARCH_IND，回退到LTE的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月30日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_ProcCsfbRedirFailBackLte_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU                              stAnycellSrchRatList;
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList;

    /* 紧急呼时发anycell搜 */
    if (NAS_MML_CSFB_SERVICE_STATUS_MO_EMERGENCY_EXIST == NAS_MML_GetCsfbServiceStatus())
    {
        pstPrioRatList       = NAS_MML_GetMsPrioRatList();

        /* 触发ANYCELL搜网,构造需要anycell搜的接入技术为GU,优先顺序按照syscfg设置 */
        NAS_MMC_BuildCoverageRatPrioListEmgCall_L1Main(pstPrioRatList, &stAnycellSrchRatList);

        NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

        NAS_MMC_SndInterAnyCellSearchReq(&stAnycellSrchRatList, NAS_MMC_ANYCELL_SEARCH_SCENE_BUTT);
        return VOS_TRUE;
    }

    /* 非紧急呼时发CSFB_SERVIEC_REJ类型的内部搜网 */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

    NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_CSFB_SERVIEC_REJ, VOS_NULL_PTR, 0);

    return VOS_TRUE;
}
#endif

/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

