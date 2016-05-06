/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcFsmPlmnSelection.c
  版 本 号   : 初稿
  作    者   : zhoujun /40661
  生成日期   : 2011年03月14日
  最近修改   :
  功能描述   : PlmnSelection状态机处理文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年03月14日
    作    者   : zhoujun /40661
    修改内容   : 创建文件
  2.日    期   : 2011年7月04日
    作    者   : s46746
    修改内容   : V7R1 phase II,autoplmnsrch状态机调整为PlmnSelection状态机

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "NasMmcFsmPlmnSelectionTbl.h"
#include "NasMmcCtx.h"
#include "NasMmcFsmPlmnSelection.h"
#include "NasMmcSndGuAs.h"
#include "NasMmcSndLmm.h"
#include "NasMmcSndGmm.h"
#include "NasMmcSndMm.h"
#include "NasMmcProcRegRslt.h"
#include "NasMmcPlmnSelectionStrategy.h"
#include "NasMmcTimerMgmt.h"
#include "NasComm.h"
#include "NasMmlLib.h"
#include "NasMmlCtx.h"
#include "NasMmlMsgProc.h"
#include "NasMmcSndMscc.h"
#include "NasMmcProcUsim.h"
#include "NasMmcProcSuspend.h"
#include "NasMmcSndOm.h"
#include "NasMmcProcNvim.h"
/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, begin */
/* 删除ExtAppMmcInterface.h*/
/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, end */
#include "MmcMmInterface.h"
#include "MmcGmmInterface.h"
#include "NasMmcComFunc.h"

/* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
#include "MsccMmcInterface.h"
/* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */
#include "NasUtranCtrlInterface.h"
#include "NasUtranCtrlCtx.h"
#include "NasUsimmApi.h"
#include "NasMmcSndCss.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_FSM_PLMN_SELECTION_C

/*lint -save -e958 */

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMsccPlmnSearchReq_PlmnSelection_Init
 功能描述  : PLMN选网状态机初始状态接收到开机搜网处理
 输入参数  : pMsg:ID_MSCC_MMC_PLMN_SEARCH_REQ消息
             ulEventType
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年4月22日
   作    者   : l00130025
   修改内容   : 新生成函数
 2.日    期   : 2011年7月11日
   作    者   : sunxibo 46746
   修改内容   : V7R1 phase II,autoplmnsrch状态机调整为PlmnSelection状态机
 3.日    期   : 2011年12月31日
   作    者   : w00166186
   修改内容   : DTS2011082902017,ON PLMN下注册被拒,搜网状态机重复搜索该网络

 4.日    期   : 2011年12月14日
   作    者   : w00176964
   修改内容   : V7R1 phaseIV 调整:驻留标记通过新的搜网控制上下文代替
 5.日    期   : 2012年3月17日
   作    者   : l65478
   修改内容   : DTS2012031907930 用户指定搜网注册失败#11重新开机后没有发起搜网
 6.日    期   : 2012年11月10日
   作    者   : s00217060
   修改内容   : DTS2012102902559 开机搜网时，根据卡类型更新Lte的能力，如果是SIM卡，需要Disable Lte
 7.日    期   : 2012年12月28日
   作    者   : s46746
   修改内容   : DSDA GUNAS C CORE项目，增加平台是否支持LTE判断
 8.日    期   : 2013年05月08日
   作    者   : s46746
   修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
 9.日    期   : 2013年8月27日
   作    者   : l00208543
   修改内容   : Coverity
10.日    期   : 2013年10月09日
   作    者   : l00208543
   修改内容   : DTS2013100904573
11.日    期   : 2013年11月01日
   作    者   : l00208543
   修改内容   : 根据卡类型禁止网络制式
12.日    期   : 2014年1月22日
   作    者   : w00167002
   修改内容   : SVLTE共天线:MMC又触发了新一轮的搜网，则清除NO RF标记信息。
13.日    期   : 2014年2月13日
   作    者   : s00246516
   修改内容   : L-C互操作项目:增加获取和注册请求的处理
14.日    期   : 2014年4月14日
   作    者   : s00261364
   修改内容   : V3R360_eCall项目:搜网时更新服务状态
15.日    期   : 2015年4月3日
   作    者   : w00176964
   修改内容   : CDMA Iteration 10 Modified
16.日    期   : 2015年5月30日
   作    者   : s00217060
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0修改
17.日    期   : 2015年6月12日
   作    者   : w00176964
   修改内容   : CDMA Iteration 12 Modified
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMsccPlmnSearchReq_PlmnSelection_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_PLMN_WITH_RAT_STRU                              stDestPlmn;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo = VOS_NULL_PTR;
    MSCC_MMC_PLMN_SEARCH_REQ_STRU                          *pstMsccPlmnSrchReq = VOS_NULL_PTR;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstPlmnListInfo    = VOS_NULL_PTR;

    pstMsccPlmnSrchReq = (MSCC_MMC_PLMN_SEARCH_REQ_STRU *)pstMsg;

    /* 解决版本Coverity问题 */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    pstPlmnSelectionListInfo = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();

    /* 上报AT搜网开始 */
    NAS_MMC_SndMsccPlmnSelectStartInd();

    /* 保存入口消息 */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

    /* 保存MMA带下来的PLMN */
    NAS_MMC_SaveGeoPlmn_PlmnSelection(pstMsccPlmnSrchReq);

    if (NAS_MSCC_PIF_ACQ_REASON_POWER_UP == pstMsccPlmnSrchReq->enAcqReason)
    {
        /* 根据场景初始化搜网列表信息 */
        NAS_MMC_InitPlmnSelectionList(NAS_MMC_PLMN_SEARCH_SCENE_SWITCH_ON,
                                      VOS_NULL_PTR,
                                      pstPlmnSelectionListInfo);
    }
    else if (NAS_MSCC_PIF_ACQ_REASON_OTHER == pstMsccPlmnSrchReq->enAcqReason)
    {
        NAS_MMC_InitPlmnSelectionList(NAS_MMC_PLMN_SEARCH_SCENE_AREA_LOST,
                                      VOS_NULL_PTR,
                                      pstPlmnSelectionListInfo);
    }
    else if (NAS_MSCC_PIF_ACQ_REASON_HIGH_PRIORITY == pstMsccPlmnSrchReq->enAcqReason)
    {
        pstPlmnListInfo = (NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                                 sizeof(NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU) * NAS_MML_MAX_RAT_NUM);

        if (VOS_NULL_PTR != pstPlmnListInfo)
        {
            NAS_MMC_InitSearchedPlmnListInfo(pstPlmnListInfo);

            NAS_MMC_ConvertMsccHighPrioPlmnListToMmcPlmnListInfo(&pstMsccPlmnSrchReq->stHighPrioPlmnList,
                                                                pstPlmnListInfo);

            NAS_MMC_InitPlmnSelectionList(NAS_MMC_PLMN_SEARCH_SCENE_HIGH_PRIO_LTE_PLMN_SEARCH,
                                          pstPlmnListInfo,
                                          pstPlmnSelectionListInfo);

            PS_MEM_FREE(WUEPS_PID_MMC, pstPlmnListInfo);

            /* hsd背景搜完成后，即lte已经完成了一次全频搜 */
            NAS_MMC_SetAllBandSearch_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE, VOS_TRUE);
        }
    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMsccPlmnSearchReq_PlmnSelection_Init: invalid acquire reason.");
    }

    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

    /* 获取需要搜索的网络及其接入技术 */
    if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        /* 根据获取的接入技术设置当前接入技术 */
        NAS_MML_SetCurrNetRatType(stDestPlmn.enRat);

        /* 向MM、GMM发送搜网指示 */
        NAS_MMC_SndGmmPlmnSchInit();
        NAS_MMC_SndMmPlmnSchInit();

        /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, begin */
        NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
        /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, end */

        NAS_MMC_UpdateRegStateSpecPlmnSearch();

        /* Added by s00261364 for V3R360_eCall项目, 2014-4-14, begin */
        NAS_MMC_UpdateServiceStateSpecPlmnSearch();
        /* Added by s00261364 for V3R360_eCall项目, 2014-4-14, end */

        /* 向接入层或LMM发送搜网请求，根据不同的搜网模式，迁移到不同的L2状态，并启动保护定时器 */
        NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);

#if   (FEATURE_ON == FEATURE_LTE)
        /* 开机搜网时，根据卡类型更新Lte的能力，如果是SIM卡，需要Disable Lte */
        /* Modified by s00246516 for L-C互操作项目, 2014-02-13, Begin */
        NAS_MMC_DisableLteForSimReason_PlmnSelection();
        /* Modified by s00246516 for L-C互操作项目, 2014-02-13, End */
#endif

    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMsccPlmnSearchReq_PlmnSelection_Init: Get Next Search Plmn fail at switch on.");

        /* 向上层状态机指示选网失败 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTafPlmnSpecialReq_PlmnSelection_Init
 功能描述  : PLMN选网状态机初始状态接收到用户指定搜网处理
 输入参数  : pMsg:ID_MSCC_MMC_PLMN_SPECIAL_REQ消息
             ulEventType
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月7日
   作    者   : sunxibo 46746
   修改内容   : 新生成函数
 2.日    期   : 2011年12月31日
   作    者   : w00166186
   修改内容   : DTS2011082902017,ON PLMN下注册被拒,搜网状态机重复搜索该网络

 3.日    期   : 2011年12月14日
   作    者   : w00176964
   修改内容   : V7R1 phaseIV 调整:驻留标记通过新的搜网控制上下文代替
 4.日    期   : 2012年06月02日
   作    者   : s00217060
   修改内容   : for CS/PS mode 1, 已经Disable L, PS卡有效且允许注册, Enable L
 5.日    期   : 2012年6月13日
   作    者   : w00176964
   修改内容   : DTS2012061202962:手动模式,指定网络加到禁止列表后,anycell搜网驻留
                后丢网,available定时器启动两次后不再启动
 6.日    期   : 2012年10月31日
   作    者   : t00212959
   修改内容   : DTS2012103100827:syscfg 之后导致的搜网在正常服务时才上报refresh
 7.日    期   : 2013年01月23日
   作    者   : s00217060
   修改内容   : 问题单: DTS2013012106172,Enable Lte时停止定时器TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER
 8.日    期   : 2013年05月08日
   作    者   : s46746
   修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
 9.日    期   : 2013年8月27日
   作    者   : l00208543
   修改内容   : Coverity
10.日    期   : 2013年10月09日
   作    者   : l00208543
   修改内容   : DTS2013100904573
11.日    期   : 2014年1月22日
   作    者   : w00167002
   修改内容   : SVLTE共天线:MMC又触发了新一轮的搜网，则清除NO RF标记信息。

12.日    期   : 2014年3月1日
   作    者   : z00234330
   修改内容   : DTS2014022805826,指定搜网时服务状态上报不正确
13.日    期   : 2014年4月2日
   作    者   : B00269685
   修改内容   : CS,PS正常服务，使用COPS改变网络，搜网过程中，由于未更新注册状态，
                所以在搜网过程中，AT+CREG?查询结果仍为正常状态。修改为搜网时同步更新注册状态。

14.日    期   : 2014年4月11日
   作    者   : B00269685
   修改内容   : CS,PS正常服务，使用COPS改变网络，搜网过程中，由于未更新注册状态，
                所以在搜网过程中，AT+CREG?查询结果仍为正常服务。
                修改为搜网时同步更新注册状态。
15.日    期   : 2014年5月21日
   作    者   : w00167002
   修改内容   : DTS2014051602857:在SOR打开时候，如果CS注册失败达到4次，则等周期
                搜网定时器超时发起LIST搜网，如果当前仅有原有网络，则发起LAU,否则
                触发MM发起LAU;如果LIST搜后，发现有其他网络.指定搜网上报结束后更新
                选网类型，保持整个选网机制一致。
16.日    期   : 2015年1月5日
   作    者   : z00161729
   修改内容   : AT&T 支持DAM特性修改

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTafPlmnSpecialReq_PlmnSelection_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_PLMN_WITH_RAT_STRU                              stDestPlmn;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enNetRatType;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo = VOS_NULL_PTR;

    /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, begin*/
    MSCC_MMC_PLMN_SPECIAL_REQ_STRU                          *pstUserSelReqMsg  = VOS_NULL_PTR;
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, end*/

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;
#endif

    /* 解决版本Coverity问题 */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    /* 上报AT搜网开始 */
    NAS_MMC_SndMsccPlmnSelectStartInd();

    /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, begin*/
    pstUserSelReqMsg    = (MSCC_MMC_PLMN_SPECIAL_REQ_STRU*)pstMsg;
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, end*/

    pstPlmnSelectionListInfo = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();

#if (FEATURE_ON == FEATURE_LTE)
    enLteCapabilityStatus = NAS_MML_GetLteCapabilityStatus();
#endif

    /* 保存入口消息 */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

    NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_USER_SPEC_SRCH);

    /* 保存手动搜网信息 */
    NAS_MMC_UpdateUserSpecPlmnSearchInfo_PlmnSelection((NAS_MML_PLMN_ID_STRU*)(&pstUserSelReqMsg->stPlmnId),
                                                       pstUserSelReqMsg->enAccessMode);

    /* 根据场景初始化搜网列表信息 */
    NAS_MMC_InitPlmnSelectionList(NAS_MMC_PLMN_SEARCH_SCENE_USER_SPEC_PLMN_SEARCH,
                                  VOS_NULL_PTR,
                                  pstPlmnSelectionListInfo);



    if ( VOS_TRUE == NAS_MMC_IsNormalServiceStatus() )
    {
        /* SYSCFG设置后需要搜网，更新为限制服务状态并上报 */
        NAS_MMC_SetCsServiceStatus(NAS_MMC_LIMITED_SERVICE);
        NAS_MMC_SetPsServiceStatus(NAS_MMC_LIMITED_SERVICE);

        /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, begin*/
        NAS_MMC_SndMsccServiceStatusInd(NAS_MSCC_PIF_SRVDOMAIN_NOT_REG_PLMN_SEARCHING, NAS_MSCC_PIF_SERVICE_STATUS_LIMITED_SERVICE);
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, end*/

        NAS_MMC_UpdateRegStateSpecPlmnSearch();
    }


    /* 当前未驻留,发起搜网时先设置搜网标记,触发状态机退出后的anycell搜网 */
    if (NAS_MMC_AS_CELL_NOT_CAMP_ON  == NAS_MMC_GetAsCellCampOn())
    {
        NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);
    }

    /* 获取当前接入技术 */
    enNetRatType = NAS_MML_GetCurrNetRatType();

#if (FEATURE_ON == FEATURE_LTE)
    if ( VOS_TRUE == NAS_MMC_IsNeedEnableLte_PlmnSelection(NAS_MMC_PLMN_SEARCH_SCENE_USER_SPEC_PLMN_SEARCH) )
    {
        if ((VOS_FALSE == NAS_MML_GetDisableLteRoamFlg())
         && (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == enLteCapabilityStatus))
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
#endif

    /* 信令连接存在 */
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        /* 根据当前不同的接入技术,发送释放请求,迁移到不同的等待连接释放的L2状态，并启动保护定时器 */
        NAS_MMC_SndRelReq_PlmnSelection(enNetRatType);

        return VOS_TRUE;
    }

    /* 获取下个网络失败，则退出状态机 */
    if (VOS_TRUE != NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        /* 打印异常 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTafPlmnSpecialReq_PlmnSelection_Init: Get Next Search Plmn fail at user spec search.");

        /* 向MMA报指定搜网失败 */
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, begin*/
        NAS_MMC_SndMsccUserSpecPlmnSearchCnf(NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_FAIL);
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, end*/


        /*更新入口消息为普通的搜网请求，后续有新的用户请求时，可以打断该状态机*/
        NAS_MMC_SaveCommonPlmnSrchEntryMsg_PlmnSelection();

        /* 向上层状态机指示选网失败 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);

        /* 退出层二状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 向MM、GMM发送搜网指示 */
    NAS_MMC_SndGmmPlmnSchInit();
    NAS_MMC_SndMmPlmnSchInit();

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, end */


    /* 判断需要搜索网络接入技术与当前接入技术是否相同,或者当前接入技术为Butt,
       对应的场景是选网状态机挂起接入层状态接收到Abort消息,接入层回复SUSPNED CNF
       后会将当前接入模式设置为Butt再退出,表示可以向任何接入技术直接发起搜网 */
    if ((enNetRatType == stDestPlmn.enRat)
     || (NAS_MML_NET_RAT_TYPE_BUTT == enNetRatType))
    {
        /* 根据获取的接入技术设置当前接入技术 */
        NAS_MML_SetCurrNetRatType(stDestPlmn.enRat);

        /* 向接入层或LMM发送搜网请求，根据不同的搜网模式，迁移到不同的L2状态，并启动保护定时器 */
        NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
    }
    else
    {
        /* 向接入层或LMM发送挂起请求，根据当前不同的接入技术，迁移到不同的L2状态，并启动保护定时器 */
        NAS_MMC_SndSuspendReq_PlmnSelection(enNetRatType);
    }

    NAS_MMC_UpdateRegStateSpecPlmnSearch();


    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcMmcInterPlmnSearchReq_PlmnSelection_Init
 功能描述  : PLMN选网状态机初始状态接收到内部搜网请求处理，初始化搜网列表后发起搜网
 输入参数  : pMsg:搜网请求消息
             ulEventType
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年4月22日
   作    者   : l00130025
   修改内容   : 新生成函数
 2.日    期   : 2011年7月11日
   作    者   : sunxibo 46746
   修改内容   : V7R1 phase II,autoplmnsrch状态机调整为PlmnSelection状态机
 3.日    期   : 2011年11月29日
   作    者   : w00166186
   修改内容   : DTS2011101802330,OOS后出服务区的处理
 4.日    期   : 2011年12月31日
   作    者   : w00166186
   修改内容   : DTS2011082902017,ON PLMN下注册被拒搜网,当前网络被重复搜索

 5.日    期   : 2011年12月14日
   作    者   : w00176964
   修改内容   : V7R1 phaseIV 调整:驻留标记通过新的搜网控制上下文代替
 6.日    期   : 2011年6月9日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL背景搜修改，list搜网场景无需再搜之前被拒的网络
 7.日    期   : 2012年06月27日
   作    者   : s00217060
   修改内容   : for CS/PS mode 1, 调整:无条件更新选网列表
 8.日    期   : 2012年6月13日
   作    者   : w00176964
   修改内容   : DTS2012061202962:手动模式,指定网络加到禁止列表后,anycell搜网驻留
                后丢网,available定时器启动两次后不再启动
 9.日    期   : 2012年10月16日
   作    者   : z00161729
   修改内容   : DTS2012081604223:已经驻留在L网络提供正常服务，CS/PS mode 1重回LTE后，需要周期性搜GU网络时才需更新当前驻留网络为已注册
10.日    期   : 2012年12月15日
   作    者   : l65478
   修改内容   : DTS2012120508936:在发起紧急呼叫时需要disable LTE
11.日    期   : 2013年01月23日
   作    者   : s00217060
   修改内容   : 问题单: DTS2013012106172,Enable Lte时停止定时器TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER
12.日    期   : 2013年05月08日
   作    者   : s46746
   修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
13.日    期   : 2013年8月27日
   作    者   : l00208543
   修改内容   : Coverity
14.日    期   : 2013年10月09日
   作    者   : l00208543
   修改内容   : DTS2013100904573
15.日    期   : 2013年10月17日
   作    者   : l65478
   修改内容   : DTS2013102103487:DT需求:在单域失败时也需要发起搜网
16.日    期   : 2013年11月25日
   作    者   : z00161729
   修改内容   : SVLTE优化G-TL ps切换性能修改
17.日    期   : 2013年12月25日
   作    者   : z00161729
   修改内容   : SVLTE支持NCELL搜网
18.日    期   : 2014年1月22日
   作    者   : w00167002
   修改内容   : SVLTE共天线:MMC又触发了新一轮的搜网，则清除NO RF标记信息。
19.日    期   : 2014年4月14日
   作    者   : s00261364
   修改内容   : V3R360_eCall项目:搜网时更新服务状态
20.日    期   : 2014年5月21日
   作    者   : w00167002
   修改内容   : DTS2014051602857:在SOR打开时候，如果CS注册失败达到4次，则等周期
                搜网定时器超时发起LIST搜网，如果当前仅有原有网络，则发起LAU,否则
                触发MM发起LAU;如果LIST搜后，发现有其他网络，则发起其他网络的搜网注册。
21.日    期   : 2014年6月30日
   作    者   : w00176964
   修改内容   : DSDS III调整:修改函数名以及清除NO RF标记场景修改为选网流程中
22.日    期   : 2014年6月30日
   作    者   : z00161729
   修改内容   : DSDS III新增
23.日    期   : 2015年1月5日
   作    者   : z00161729
   修改内容   : AT&T 支持DAM特性修改
24.日    期   : 2015年1月5日
   作    者   : h00285180
   修改内容   : LTE #14拒绝优化:DTS2015010401946
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcMmcInterPlmnSearchReq_PlmnSelection_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_INTER_PLMN_SEARCH_REQ_STRU                     *pstPlmnSearchReq = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stDestPlmn;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enNetRatType;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo = VOS_NULL_PTR;

    VOS_UINT32                                              ulIsNormalService;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enCampPlmnNetRat;
    NAS_MML_LAI_STRU                                       *pstLai;
    VOS_UINT32                                              ucSpecPlmnSearchFlg;
    VOS_UINT32                                              ulSingleDomainPlmnListFlg;
    MMC_LMM_DISABLE_LTE_REASON_ENUM_UINT32                  enDisableLteReason;



    VOS_UINT8                                               ucCsAttachAllowFlg;
    VOS_UINT8                                               ucPsAttachAllowFlg;


#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo           = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stCurPlmn;

    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;

    VOS_UINT32                                              ulIsCsPsMode1NeedPeriodSearchGU;

    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene;
    VOS_UINT8                                               ucEmcFlg;
    NAS_MMC_TIMER_STATUS_ENUM_U8                            enTimerStatus;

    /* 获取当前驻留的网络信息 */
    pstCurCampInfo     = NAS_MML_GetCurrCampPlmnInfo();
    stCurPlmn.stPlmnId = pstCurCampInfo->stLai.stPlmnId;
    stCurPlmn.enRat    = pstCurCampInfo->enNetRatType;
    enLteCapabilityStatus = NAS_MML_GetLteCapabilityStatus();
#endif

    ucCsAttachAllowFlg = NAS_MML_GetCsAttachAllowFlg();
    ucPsAttachAllowFlg = NAS_MML_GetPsAttachAllowFlg();

    /* 德电需求:单域注册失败发起搜网特性打开时,如果注册失败原因值是#17,需要发起搜网 */
    ulSingleDomainPlmnListFlg = NAS_MMC_IsSingleDomainRegFailNeedPlmnSrch(NAS_MSCC_PIF_SRVDOMAIN_CS);
    ulSingleDomainPlmnListFlg |= NAS_MMC_IsSingleDomainRegFailNeedPlmnSrch(NAS_MSCC_PIF_SRVDOMAIN_PS);

    /* 解决版本Coverity问题 */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    /* 上报AT搜网开始 */
    NAS_MMC_SndMsccPlmnSelectStartInd();

    ucSpecPlmnSearchFlg = NAS_MMC_GetSpecPlmnSearchState();
    pstLai              = NAS_MML_GetCurrCampLai();
    enCampPlmnNetRat    = pstLai->enCampPlmnNetRat;

    pstPlmnSelectionListInfo = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();

    /* 内部搜网请求处理  */
    pstPlmnSearchReq = (NAS_MMC_INTER_PLMN_SEARCH_REQ_STRU*)pstMsg;

    /* 保存入口消息 */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

    /* 搜网场景时业务触发时需要更新全局变量退状态机时用于发送end session*/
    if (NAS_MMC_PLMN_SEARCH_SCENE_SRV_TRIG_PLMN_SEARCH == pstPlmnSearchReq->enPlmnSearchScene)
    {
        NAS_MMC_SetSrvTrigPlmnSearchFlag_PlmnSelection(VOS_TRUE);
    }

    /* 根据场景初始化搜网列表信息 */
    NAS_MMC_InitPlmnSelectionList(pstPlmnSearchReq->enPlmnSearchScene,
                                  &(pstPlmnSearchReq->astInterPlmnSearchInfo[0]),
                                  pstPlmnSelectionListInfo);



    /* 不区分搜网场景统一根据消息中携带的搜网信息更新搜网列表 */
    NAS_MMC_UpdatePlmnSearchInfo_PlmnSelection(pstPlmnSearchReq, pstPlmnSelectionListInfo);
#if (FEATURE_ON == FEATURE_LTE)
    /* 存在CSFB的EMC或者缓存的EMC，并且ENABLE LTE定时器运行期间,不ENABLE LTE */
    ucEmcFlg           = NAS_MML_GetCsEmergencyServiceFlg();
    enTimerStatus      = NAS_MMC_GetTimerStatus(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER);
    enDisableLteReason = NAS_MML_GetDisableLteReason();
    if (( (MMC_LMM_DISABLE_LTE_REASON_EMERGENCY_CALL   == enDisableLteReason)
       || (MMC_LMM_DISABLE_LTE_REASON_LTE_REJ_CAUSE_14 == enDisableLteReason)
       || (VOS_TRUE == ucEmcFlg))
     && (NAS_MMC_TIMER_STATUS_RUNING == enTimerStatus))
    {
        enPlmnSearchScene = NAS_MMC_PLMN_SEARCH_SCENE_DISABLE_LTE;
    }
    else
    {
        enPlmnSearchScene = pstPlmnSearchReq->enPlmnSearchScene;
    }
    if ( VOS_TRUE == NAS_MMC_IsNeedEnableLte_PlmnSelection(enPlmnSearchScene) )
    {
        if ((VOS_FALSE == NAS_MML_GetDisableLteRoamFlg())
         && (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == enLteCapabilityStatus))
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

    /*判断当前是否已经驻留在L网络提供正常服务，
      对应的场景是CS/PS mode 1重回LTE后，周期性搜GU网络*/
    ulIsCsPsMode1NeedPeriodSearchGU = NAS_MMC_IsCsPsMode1NeedPeriodSearchGU();

    if ((VOS_TRUE == NAS_MMC_IsCampLteNormalService())
     && (VOS_TRUE == ulIsCsPsMode1NeedPeriodSearchGU))
    {
        /* 保存当前网络到状态机上下文 */
        NAS_MMC_SetCsPsMode1ReCampLtePlmn_PlmnSelection(NAS_MML_GetCurrCampPlmnId());

        /* 更新选网列表中当前网络状态为已注册 */
        NAS_MMC_UpdatePlmnNetStatusInPlmnSelectionList(&stCurPlmn,
                                                       NAS_MMC_NET_STATUS_SEARCHED_REGISTERED,
                                                       pstPlmnSelectionListInfo);
    }
#endif

    /* list搜网状态机退出有两种搜网场景NAS_MMC_PLMN_SEARCH_SCENE_USER_LIST和NAS_MMC_PLMN_SEARCH_SCENE_DISABLE_LTE*/
    if ((NAS_MMC_PLMN_SEARCH_SCENE_USER_LIST == pstPlmnSearchReq->enPlmnSearchScene)
     || (NAS_MMC_PLMN_SEARCH_SCENE_DISABLE_LTE == pstPlmnSearchReq->enPlmnSearchScene))
    {
        /* 如果cs和ps都是限制服务，list搜网结果中有当前网络，无需重复搜索当前网络*/
        ulIsNormalService = NAS_MMC_IsNormalServiceStatus();

        if (((VOS_FALSE == ulIsNormalService)
          || (VOS_TRUE  == ulSingleDomainPlmnListFlg))
         && (NAS_MMC_SPEC_PLMN_SEARCH_STOP == ucSpecPlmnSearchFlg))
        {
            /* svlte modem0 ps迁移到modem1，g下限制驻留，available定时器超时，g下内部列表搜带上来l的网络和g当前驻留
               网络，用户列表搜场景搜网无需删除当前驻留g的网络，因为如果后续指定搜l的网络失败，需要重新回到g */
            if (!((VOS_TRUE == NAS_MML_GetSvlteSupportFlag())
              && (VOS_FALSE == ucCsAttachAllowFlg)
              && (VOS_FALSE == ucPsAttachAllowFlg)))
            {
                /* 删除当前注册被拒的网络 */
                NAS_MMC_DelSpecPlmnWithRatInPlmnList(NAS_MML_GetCurrCampPlmnId(),
                                                    enCampPlmnNetRat,
                                                    pstPlmnSelectionListInfo);
            }

        }

    }

    /* 当前未驻留,发起搜网时先设置搜网标记,触发状态机退出后的anycell搜网 */
    if (NAS_MMC_AS_CELL_NOT_CAMP_ON  == NAS_MMC_GetAsCellCampOn())
    {
        NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);
    }
    /* 获取下个网络失败，则退出状态机 */
    if (VOS_TRUE != NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        /* 打印异常 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMmcMmcInterPlmnSearchReq_PlmnSelection_Init: Get Next Search Plmn fail at inter search.");

        NAS_MMC_UpdateRfAvailFlgPlmnSrchFail_PlmnSelection();

        if ( (VOS_TRUE == NAS_MMC_IsSorTriggerAdditionalLau())
          && (NAS_MMC_PLMN_SEARCH_SCENE_USER_LIST == pstPlmnSearchReq->enPlmnSearchScene) )
        {
            /* 清除additional lau信息 */
            NAS_MML_InitSorAdditionalLauCtx();

            /* LIST搜结束后，通知MM发送触发SOR的LAU */
            NAS_MMC_SndMmLauReq(MMC_MM_LAU_REQ_REASON_SOR);
        }
        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();

        return VOS_TRUE;
    }

    /* 获取当前接入技术 */
    enNetRatType = NAS_MML_GetCurrNetRatType();

    /*信令连接存在*/
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        /* 根据当前不同的接入技术,发送释放请求,迁移到不同的等待连接释放的L2状态，并启动保护定时器 */
        NAS_MMC_SndRelReq_PlmnSelection(enNetRatType);

        return VOS_TRUE;
    }

    /* 向MM、GMM发送搜网指示 */
    NAS_MMC_SndGmmPlmnSchInit();
    NAS_MMC_SndMmPlmnSchInit();

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, end */

    /* 判断需要搜索网络接入技术与当前接入技术是否相同,或者当前接入技术为Butt,
       对应的场景是选网状态机挂起接入层状态接收到Abort消息,接入层回复SUSPNED CNF
       后会将当前接入模式设置为Butt再退出,表示可以向任何接入技术直接发起搜网 */
    if ((enNetRatType == stDestPlmn.enRat)
     || (NAS_MML_NET_RAT_TYPE_BUTT == enNetRatType))
    {
        /* 根据获取的接入技术设置当前接入技术 */
        NAS_MML_SetCurrNetRatType(stDestPlmn.enRat);

        /* 向接入层或LMM发送搜网请求，根据不同的搜网模式，迁移到不同的L2状态，并启动保护定时器 */
        NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
    }
    /*需要挂起当前模式，切换到等待挂起状态，启动保护定时器*/
    else
    {
        /* 向接入层或LMM发送挂起请求，根据当前不同的接入技术，迁移到不同的L2状态，并启动保护定时器 */
        NAS_MMC_SndSuspendReq_PlmnSelection(enNetRatType);
    }

    NAS_MMC_UpdateRegStateSpecPlmnSearch();

    /* Added by s00261364 for V3R360_eCall项目, 2014-4-14, begin */
    NAS_MMC_UpdateServiceStateSpecPlmnSearch();
    /* Added by s00261364 for V3R360_eCall项目, 2014-4-14, end */

    return VOS_TRUE;

}

/* Added by s00246516 for L-C互操作项目, 2014-01-28, Begin */
/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMsccAcqReq_PlmnSelection_Init
 功能描述  : PLMN选网状态机初始状态接收到获取网络处理
 输入参数  : pMsg:ID_MSCC_MMC_ACQ_REQ消息
             ulEventType
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年1月27日
   作    者   : s00246516
   修改内容   : 新生成函数
 2.日    期   : 2014年4月14日
   作    者   : s00261364
   修改内容   : V3R360_eCall项目:搜网时更新服务状态
 3.日    期   : 2014年7月1日
   作    者   : W00176964
   修改内容   : DSDS III:发起选网则清除NO RF标记
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMsccAcqReq_PlmnSelection_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enNetRatType;
    NAS_MML_PLMN_WITH_RAT_STRU                              stDestPlmn;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo = VOS_NULL_PTR;
    MSCC_MMC_ACQ_REQ_STRU                                   *pstAcqReq = VOS_NULL_PTR;

    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    pstPlmnSelectionListInfo = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();

    /* 上报AT搜网开始 */
    NAS_MMC_SndMsccPlmnSelectStartInd();

    /* 保存入口消息 */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

    pstAcqReq = (MSCC_MMC_ACQ_REQ_STRU*)pstMsg;

    /* 根据获取原因进行网络列表初始化 */
    if (NAS_MSCC_PIF_ACQ_REASON_POWER_UP == pstAcqReq->enAcqReason)
    {
        NAS_MMC_InitPlmnSelectionList(NAS_MMC_PLMN_SEARCH_SCENE_SWITCH_ON,
                                      VOS_NULL_PTR,
                                      pstPlmnSelectionListInfo);
    }
    else if (NAS_MSCC_PIF_ACQ_REASON_OTHER == pstAcqReq->enAcqReason)
    {
        NAS_MMC_InitPlmnSelectionList(NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED,
                                      VOS_NULL_PTR,
                                      pstPlmnSelectionListInfo);
    }
    else
    {
        NAS_MMC_InitPlmnSelectionList(NAS_MMC_PLMN_SEARCH_SCENE_HIGH_PRIO_PLMN_SEARCH,
                                      VOS_NULL_PTR,
                                      pstPlmnSelectionListInfo);
    }



    if (VOS_TRUE != NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        /* 打印异常 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMsccAcqReq_PlmnSelection_Init: Get Next Search Plmn fail at inter search.");

        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();

        return VOS_TRUE;
    }

    /* 获取当前接入技术 */
    enNetRatType = NAS_MML_GetCurrNetRatType();

    /*信令连接存在*/
    if ((VOS_TRUE == NAS_MML_IsRrcConnExist())
     && (NAS_MML_NET_RAT_TYPE_BUTT != enNetRatType))
    {
        /* 根据当前不同的接入技术,发送释放请求,迁移到不同的等待连接释放的L2状态，并启动保护定时器 */
        NAS_MMC_SndRelReq_PlmnSelection(enNetRatType);

        return VOS_TRUE;
    }

    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

    /* 向MM、GMM发送搜网指示 */
    NAS_MMC_SndGmmPlmnSchInit();
    NAS_MMC_SndMmPlmnSchInit();

    NAS_MMC_SndMsccCampOnInd(VOS_FALSE);

    /* 判断需要搜索网络接入技术与当前接入技术是否相同,或者当前接入技术为Butt,
       对应的场景是选网状态机挂起接入层状态接收到Abort消息,接入层回复SUSPNED CNF
       后会将当前接入模式设置为Butt再退出,表示可以向任何接入技术直接发起搜网 */
    if ((enNetRatType == stDestPlmn.enRat)
     || (NAS_MML_NET_RAT_TYPE_BUTT == enNetRatType))
    {
        /* 根据获取的接入技术设置当前接入技术 */
        NAS_MML_SetCurrNetRatType(stDestPlmn.enRat);

        /* 向接入层或LMM发送搜网请求，根据不同的搜网模式，迁移到不同的L2状态，并启动保护定时器 */
        NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
    }
    /*需要挂起当前模式，切换到等待挂起状态，启动保护定时器*/
    else
    {
        /* 向接入层或LMM发送挂起请求，根据当前不同的接入技术，迁移到不同的L2状态，并启动保护定时器 */
        NAS_MMC_SndSuspendReq_PlmnSelection(enNetRatType);
    }

#if   (FEATURE_ON == FEATURE_LTE)
    /* 如果开机获取，需要判断SIM卡进行Disable Lte操作 */
    if (NAS_MSCC_PIF_ACQ_REASON_POWER_UP == pstAcqReq->enAcqReason)
    {
        NAS_MMC_DisableLteForSimReason_PlmnSelection();
    }
#endif

    NAS_MMC_UpdateRegStateSpecPlmnSearch();
    /* Added by s00261364 for V3R360_eCall项目, 2014-4-14, begin */
    NAS_MMC_UpdateServiceStateSpecPlmnSearch();
    /* Added by s00261364 for V3R360_eCall项目, 2014-4-14, end */


    return VOS_TRUE;
}
/* Added by s00246516 for L-C互操作项目, 2014-01-28, End */

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitWasPlmnSearchCnf
 功能描述  : 等待WAS搜网回复过程中收到状态机退出消息的处理
 输入参数  : pMsg:MMCMMC_ABORT_FSM_REQ
             ulEventType
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年4月23日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2011年7月11日
   作    者   : sunxibo 46746
   修改内容   : V7R1 phase II,autoplmnsrch状态机调整为PlmnSelection状态机
 3.日    期   : 2014年2月18日
   作    者   : s00217060
   修改内容   : DTS2014021203453:设置打断标志，否则会在收到stop_cnf之后发起搜网

*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF);

    NAS_MMC_SetAbortFlag_PlmnSelection(VOS_TRUE);

    /* 通知AS停止指定搜网 */
    NAS_MMC_SndAsPlmnSrchStopReq(WUEPS_PID_WRR);

    /*根据不同的搜网模式，迁移到不同的L2状态，启动不同保护定时器*/
    NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_PLMN_STOP_CNF);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcUtranCtrlPlmnSelectionAbortFinishIndMsg_PlmnSelection_WaitWasPlmnSearchCnf
 功能描述  : 等待WAS搜网回复过程中收到MMC打断UTRANCTRL结束完成消息的处理
 输入参数  : pMsg:MMCMMC_INTER_UTRAN_CTRL_PLMN_SELECTION_ABORT_FINISH_IND
             ulEventType
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年12月17日
   作    者   : w00167002
   修改内容   : 在W下搜网失败，进UTRANCTRL选择TD网络时候，收到第一阶段定
                时器超时等消息，触发打断选网状态机。当前MMC选网状态机给W发STOP REQ请求，而不是
                给TD发STOP搜网请求，这样MMC后续又搜索Lte,出现双主模异常复位. 在消息打断选网状态机时候，
                需要先退出UTRANCTRL选网流程，再打断MMC选网状态机。此时MMC收到选网状态机被MMC发送的
                abort消息打断，则可退出选网状态机。

*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvMmcUtranCtrlAbortFinishIndMsg_PlmnSelection_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMmcUtranCtrlAbortFinishIndMsg_PlmnSelection_WaitWasPlmnSearchCnf");

    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF);

    NAS_MMC_SetAbortFlag_PlmnSelection(VOS_TRUE);

    NAS_MMC_UpdateRfAvailFlgPlmnSrchAborted_PlmnSelection();

    NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmRelInd_PlmnSelection_WaitWasPlmnSearchCnf
 功能描述  : 等待WAS搜网回复过程中收到RRMM_REL_IND消息的处理
 输入参数  : pMsg        - RRMM_REL_IND消息首地址
             ulEventType - 事件类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年11月28日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   : 2011年12月14日
   作    者   : w00176964
   修改内容   : V7R1 phaseIV 调整:驻留标记通过新的搜网控制上下文代替
 3.日    期   : 2012年06月02日
   作    者   : sunxibo /46746
   修改内容   : Added for V7R1 C50 CS/PS mode 1
 4.日    期   : 2012年6月18日
   作    者   : l00171473
   修改内容   : DTS2012051104124, WAS:接收到RRMM_PLMN_SEARCH_REQ时，不会上报正常原因的rel ind，
                只有异常原因的rel ind. 收到rel ind时认为搜网结束
 5.日    期   : 2013年8月27日
   作    者   : l00208543
   修改内容   : Coverity

 6.日    期   : 2014年6月17日
   作    者   : w00167002
   修改内容   : DSDS III:收到WAS的NO RF异常释放，则进入OOC

 7.日    期   : 2015年5月26日
   作    者   : w00167002
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0项目修改
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvRrMmRelInd_PlmnSelection_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulResult;
    NAS_MML_PLMN_WITH_RAT_STRU          stDestPlmn;
    RRMM_REL_IND_STRU                  *pstRrmmRelIndMsg    = VOS_NULL_PTR;

    pstRrmmRelIndMsg = (RRMM_REL_IND_STRU *)pstMsg;

    /* 无需判断原因值 */

    /* 解决版本Coverity问题 */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvRrMmRelInd_PlmnSelection_WaitWasPlmnSearchCnf: ENTERED");

    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF);


    /* 如果当前为NO RF，则直接退状态机 */
    if (RRC_REL_CAUSE_NO_RF == pstRrmmRelIndMsg->ulRelCause)
    {
        NAS_MMC_ProcNoRf_PlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA);

        return VOS_TRUE;
    }

    /* 如果当前是HISTORY搜，则设置UTRAN已经完成HISTORY搜索流程 */
    if (NAS_MMC_PLMN_SEARCH_TYPE_HISTORY == NAS_MMC_GetCurrSearchingType_PlmnSelection())
    {
        NAS_MMC_SetHistorySearchedFlag_PlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA, VOS_TRUE);
    }

    /* 搜网失败后更新RF可用标记 */
    NAS_MMC_UpdateRfAvailFlgPlmnSrchFail_PlmnSelection();

    /* 获取下一个要搜索的网络,若获取失败，则给上层状态机上报搜网失败，退出
       若获取成功，则判断下一个要搜索的网络是否与当前驻留网络相同，
       若相同则在当前模式发起搜网，否则挂起当前网络 */
    ulResult = NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn);

    /*  获取下个网络失败，则进行出服务区处理 */
    if (VOS_TRUE != ulResult)
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();

        return VOS_TRUE;
    }


    /*下一个要搜索的网络是否与当前驻留网络不同,需要挂起当前模式，切换到等待挂起状态，启动保护定时器 */
    if (stDestPlmn.enRat != NAS_MML_GetCurrNetRatType())
    {
        NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_GetCurrNetRatType());
    }
    else
    {
        /* 向接入层或LMM发送搜网请求，根据不同的搜网模式，迁移到不同的L2状态，并启动保护定时器 */
        NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitGasPlmnSearchCnf
 功能描述  : 等待GAS搜网回复过程中收到状态机退出消息的处理
 输入参数  : pMsg:MMCMMC_ABORT_FSM_REQ
             ulEventType
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年4月23日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2011年7月11日
   作    者   : sunxibo 46746
   修改内容   : V7R1 phase II,autoplmnsrch状态机调整为PlmnSelection状态机
 3.日    期   : 2014年2月18日
   作    者   : s00217060
   修改内容   : DTS2014021203453:设置打断标志，否则会在收到stop_cnf之后发起搜网

*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitGasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_SEARCH_CNF);

    NAS_MMC_SetAbortFlag_PlmnSelection(VOS_TRUE);

    /* 通知AS停止指定搜网 */
    NAS_MMC_SndAsPlmnSrchStopReq(UEPS_PID_GAS);

    NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_PLMN_STOP_CNF);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF_LEN);

    return VOS_TRUE;
}
/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedSortPlmnListRcvRrcPlmnSearchCnfFail_PlmnSelection
 功能描述  : 判断接入层搜网失败结果是否需要触发重新排序
 输入参数  : pstInterPlmnSearchInfo - 搜网失败带上来存在的网络信息
             enRat                  - 接入技术
 输出参数  : 无
 返 回 值  : VOS_TRUE - 需要
             VOS_FALSE - 不需要
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年11月1日
   作    者   : z00161729
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedSortPlmnListRcvRrcPlmnSearchCnfFail_PlmnSelection(
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstInterPlmnSearchInfo,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enRat
)
{
    VOS_UINT32                          i;
    NAS_MML_PLMN_WITH_RAT_STRU         *pstCurrSearchingPlmn = VOS_NULL_PTR;
    VOS_UINT8                           ucSearchedPlmnAllSameWithCurrSearchingPlmn;

    pstCurrSearchingPlmn                       = NAS_MMC_GetCurrSearchingPlmn_PlmnSelection();
    ucSearchedPlmnAllSameWithCurrSearchingPlmn = VOS_TRUE;

    if (VOS_FALSE == NAS_MMC_IsNeedSortRoamPlmnSelectionList_PlmnSelection(enRat))
    {
        return VOS_FALSE;
    }

    /* 如果搜网失败带上来存在的高质量网络或低质量网络中有一个国家码
       与rplmn或hplmn相同，则返回false */
    for (i = 0; i < pstInterPlmnSearchInfo->ulHighPlmnNum; i++)
    {
        if (VOS_TRUE == NAS_MMC_IsPlmnMccSameWithRplmn(pstInterPlmnSearchInfo->astHighPlmnList[i].ulMcc))
        {
            NAS_MMC_SetExistRplmnOrHplmnFlag_PlmnSelection(VOS_TRUE);
            return VOS_FALSE;
        }

        if (VOS_TRUE == NAS_MMC_IsPlmnMccSameWithHplmn(pstInterPlmnSearchInfo->astHighPlmnList[i].ulMcc))
        {
            NAS_MMC_SetExistRplmnOrHplmnFlag_PlmnSelection(VOS_TRUE);
            return VOS_FALSE;
        }

        if (VOS_FALSE == NAS_MML_ComparePlmnMcc(pstCurrSearchingPlmn->stPlmnId.ulMcc, pstInterPlmnSearchInfo->astHighPlmnList[i].ulMcc))
        {
            ucSearchedPlmnAllSameWithCurrSearchingPlmn = VOS_FALSE;
        }
    }

    for (i = 0; i < pstInterPlmnSearchInfo->ulLowPlmnNum; i++)
    {
        if (VOS_TRUE == NAS_MMC_IsPlmnMccSameWithRplmn(pstInterPlmnSearchInfo->astLowPlmnList[i].stPlmnId.ulMcc))
        {
            NAS_MMC_SetExistRplmnOrHplmnFlag_PlmnSelection(VOS_TRUE);
            return VOS_FALSE;
        }

        if (VOS_TRUE == NAS_MMC_IsPlmnMccSameWithHplmn(pstInterPlmnSearchInfo->astLowPlmnList[i].stPlmnId.ulMcc))
        {
            NAS_MMC_SetExistRplmnOrHplmnFlag_PlmnSelection(VOS_TRUE);
            return VOS_FALSE;
        }

        if (VOS_FALSE == NAS_MML_ComparePlmnMcc(pstCurrSearchingPlmn->stPlmnId.ulMcc, pstInterPlmnSearchInfo->astLowPlmnList[i].stPlmnId.ulMcc))
        {
            ucSearchedPlmnAllSameWithCurrSearchingPlmn = VOS_FALSE;
        }
    }

    /* 搜网失败带上来存在的网络都跟搜索的网络同一国家码，则不重新构造排序搜网列表 */
    if (VOS_TRUE == ucSearchedPlmnAllSameWithCurrSearchingPlmn)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;

}



/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmSpecPlmnSrchCnf_PlmnSelection_WaitWasPlmnSearchCnf
 功能描述  : 收到WAS全频段指定搜网CNF后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:rrmm_plmn_SEARCH_cnf消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年4月25日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2011年7月11日
   作    者   : sunxibo 46746
   修改内容   : V7R1 phase II,autoplmnsrch状态机调整为PlmnSelection状态机
 3.日    期   : 2011年12月15日
   作    者   : W00166186
   修改内容   : dts2011111502641,L下PLMN加入禁止TA后不再搜网

 4.日    期   : 2011年12月14日
   作    者   : w00176964
   修改内容   : V7R1 phaseIV 调整:驻留标记通过新的搜网控制上下文代替
 5.日    期   : 2012年06月02日
   作    者   : sunxibo /46746
   修改内容   : Added for V7R1 C50 CS/PS mode 1
 6.日    期   : 2013年8月27日
   作    者   : l00208543
   修改内容   : Coverity
 7.日    期   : 2014年1月21日
   作    者   : w00167002
   修改内容   : SVLTE共天线项目:在W下搜网失败为NO RF，表示当前天线资源不可用，
                则当前搜网结束。
 8.日    期   : 2013年3月29日
   作    者   : y00176023
   修改内容   : DSDS GUNAS II项目:NO RF情况下向RRM发起注册，只考虑GU不考虑LTE搜网产生的NO RF
 9.日    期   : 2014年6月21日
   作    者   : w00167002
   修改内容   : DSDS GUNAS III项目
10.日    期   : 2014年11月1日
   作    者   : z00161729
   修改内容   : 开机漫游搜网项目修改
11.日    期   : 2015年5月21日
   作    者   : w00167002
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0项目修改,用户全频段指定搜的处理逻辑
*****************************************************************************/
VOS_VOID NAS_MMC_RcvRrMmSpecPlmnSrchCnf_PlmnSelection_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU                              *pstSrchCnfMsg = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stDestPlmn;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    stPlmnSearchInfo;

    VOS_UINT32                                              ulIsNeedSortRoamPlmnList;
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                        stSearchedExistPlmnInfo;
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                        stNewRoamPlmnSelectionList;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSrchList   = VOS_NULL_PTR;

    /* 获取选网列表 */
    pstPlmnSrchList                = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();
    ulIsNeedSortRoamPlmnList       = VOS_FALSE;
    PS_MEM_SET(&stSearchedExistPlmnInfo, 0, sizeof(stSearchedExistPlmnInfo));
    PS_MEM_SET(&stNewRoamPlmnSelectionList, 0, sizeof(stNewRoamPlmnSelectionList));

    pstSrchCnfMsg = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;

    /* 解决版本Coverity问题 */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF);

    /* 更新当前模式的网络覆盖信息 */
    NAS_MMC_UpdateGUCoverageFlg_PlmnSelection(pstSrchCnfMsg);

    if (RRC_PLMN_SEARCH_RLT_SPEC == pstSrchCnfMsg->ulSearchRlt)
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_SUCCESS,
                VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_UpdateRfAvailFlgPlmnSrchSucc_PlmnSelection();

        /* 根据不同的搜网模式，迁移到不同的L2状态，启动保护定时器 */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_SYSINFO_IND);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO, TI_NAS_MMC_WAIT_WAS_SYS_INFO_LEN);

        return;
    }


    /* 如果当前为NO RF，则直接退状态机 */
    if (RRC_PLMN_SEARCH_RLT_SPEC_NO_RF == pstSrchCnfMsg->ulSearchRlt)
    {
        NAS_MMC_ProcNoRf_PlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA);

        return;
    }


    /* 将搜网消息中携带的网络信息转换为内部消息中网络信息 */
    NAS_MMC_ConvertRrcPlmnList2SearchedPlmnListInfo(NAS_MML_NET_RAT_TYPE_WCDMA,
                                                     &pstSrchCnfMsg->PlmnIdList,
                                                     &stPlmnSearchInfo);

    /* 根据消息中携带的搜网信息更新搜网列表 */
    NAS_MMC_UpdatePlmnSearchList_PlmnSelection(&stPlmnSearchInfo,
                                               NAS_MMC_IsNeedSortAvailablePlmnSelectionList_PlmnSelection(),
                                               VOS_TRUE);

    /* 搜网失败后更新RF可用标记 */
    NAS_MMC_UpdateRfAvailFlgPlmnSrchFail_PlmnSelection();

    /* 通知CSS当前MCC */
    NAS_MMC_SndCssCurrGeoIndAfterRcvPlmnSearchCnfFail_PlmnSelection(&stPlmnSearchInfo, VOS_TRUE);

    /* 如果搜网失败结果中带上来的网络没有一个跟rplmn或hplmn
       同一国家码且之前未排过序，需要构造漫游搜网列表插入原搜网列表头部*/
    ulIsNeedSortRoamPlmnList = NAS_MMC_IsNeedSortPlmnListRcvRrcPlmnSearchCnfFail_PlmnSelection(&stPlmnSearchInfo, NAS_MML_NET_RAT_TYPE_WCDMA);

    if (VOS_TRUE == ulIsNeedSortRoamPlmnList)
    {
        /* 把高低质量网络提取加入roam搜网列表 */
        NAS_MMC_BuildSearchedPlmnListInfoByRrcSearchCnfFail(NAS_MML_NET_RAT_TYPE_WCDMA, &stPlmnSearchInfo, &stSearchedExistPlmnInfo);
        NAS_MMC_BuildRoamPlmnSelectionListBySearchedExistPlmnInfo(NAS_MML_NET_RAT_TYPE_WCDMA,
                     &stSearchedExistPlmnInfo, &stNewRoamPlmnSelectionList);

        /* 把排过序的roam搜网列表插入搜网列表前面 */
        NAS_MMC_AddRoamPlmnSelectionListInPlmnSelectionList(&stNewRoamPlmnSelectionList, pstPlmnSrchList);

        /* 设置该接入技术已经收到过接入层searched plmn info ind进行过一轮排序 */
        NAS_MMC_SetSearchedRoamPlmnSortedFlag_PlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA, VOS_TRUE);


        /* 根据消息中携带的搜网信息更新搜网列表 */
        NAS_MMC_UpdatePlmnSearchList_PlmnSelection(&stPlmnSearchInfo,
                                                   NAS_MMC_IsNeedSortAvailablePlmnSelectionList_PlmnSelection(),
                                                   VOS_TRUE);

        /* 可维可测,将选网列表输出 */

        NAS_MMC_LogDplmnNplmnList();

    }


    /* 更新当前接入技术进行了全频搜网,如果在前面更新漫游网络可能无法加入漫游搜网列表，所以构造完漫游搜网列表后再更新进行过全频搜网*/
    NAS_MMC_SetAllBandSearch_PlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA, VOS_TRUE);

    /* 当还存在下一个需要搜索的网络时，继续进行搜网，否则，进入限制驻留 */
    if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        if (NAS_MML_NET_RAT_TYPE_WCDMA == stDestPlmn.enRat)
        {
            /* 向W接入层发送搜网请求，迁移到相应的L2状态，并启动保护定时器 */
            NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
        }
        else
        {
            /* 向W接入层发送挂起请求，迁移到相应的L2状态，并启动保护定时器 */
            NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA);
        }
    }
    else
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();
    }

    return;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmPrefBandPlmnSrchCnf_PlmnSelection_WaitWasPlmnSearchCnf
 功能描述  : 收到WAS pref band搜网CNF后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:rrmm_plmn_SEARCH_cnf消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年10月12日
   作    者   : s00217060
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_RcvRrMmPrefBandPlmnSrchCnf_PlmnSelection_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU                              *pstSrchCnfMsg = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stDestPlmn;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    stPlmnSearchInfo;

    VOS_UINT32                                              ulIsNeedSortRoamPlmnList;
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                        stSearchedExistPlmnInfo;
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                        stNewRoamPlmnSelectionList;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSrchList   = VOS_NULL_PTR;

    /* 获取选网列表 */
    pstPlmnSrchList                = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();
    ulIsNeedSortRoamPlmnList       = VOS_FALSE;
    PS_MEM_SET(&stSearchedExistPlmnInfo, 0, sizeof(stSearchedExistPlmnInfo));
    PS_MEM_SET(&stNewRoamPlmnSelectionList, 0, sizeof(stNewRoamPlmnSelectionList));

    pstSrchCnfMsg = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;

    /* 解决版本Coverity问题 */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF);

    /* 更新当前模式的网络覆盖信息 */
    NAS_MMC_UpdateGUCoverageFlg_PlmnSelection(pstSrchCnfMsg);

    if (RRC_PLMN_SEARCH_RLT_PREF_BAND_SUCC == pstSrchCnfMsg->ulSearchRlt)
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_SUCCESS,
                VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_UpdateRfAvailFlgPlmnSrchSucc_PlmnSelection();

        /* 根据不同的搜网模式，迁移到不同的L2状态，启动保护定时器 */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_SYSINFO_IND);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO, TI_NAS_MMC_WAIT_WAS_SYS_INFO_LEN);

        return;
    }

    /* 如果当前为NO RF，则直接退状态机 */
    if (RRC_PLMN_SEARCH_RLT_PREF_BAND_NO_RF == pstSrchCnfMsg->ulSearchRlt)
    {
        NAS_MMC_ProcNoRf_PlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA);

        return;
    }

    /* 将搜网消息中携带的网络信息转换为内部消息中网络信息 */
    NAS_MMC_ConvertRrcPlmnList2SearchedPlmnListInfo(NAS_MML_NET_RAT_TYPE_WCDMA,
                                                     &pstSrchCnfMsg->PlmnIdList,
                                                     &stPlmnSearchInfo);

    /* 根据消息中携带的搜网信息更新搜网列表 */
    NAS_MMC_UpdatePlmnSearchList_PlmnSelection(&stPlmnSearchInfo,
                                               NAS_MMC_IsNeedSortAvailablePlmnSelectionList_PlmnSelection(),
                                               VOS_TRUE);

    /* 搜网失败后更新RF可用标记 */
    NAS_MMC_UpdateRfAvailFlgPlmnSrchFail_PlmnSelection();

    /* 通知CSS当前MCC */
    NAS_MMC_SndCssCurrGeoIndAfterRcvPlmnSearchCnfFail_PlmnSelection(&stPlmnSearchInfo, VOS_TRUE);

    /* 如果搜网失败结果中带上来的网络没有一个跟rplmn或hplmn
       同一国家码且之前未排过序，需要构造漫游搜网列表插入原搜网列表头部*/
    ulIsNeedSortRoamPlmnList = NAS_MMC_IsNeedSortPlmnListRcvRrcPlmnSearchCnfFail_PlmnSelection(&stPlmnSearchInfo, NAS_MML_NET_RAT_TYPE_WCDMA);

    if (VOS_TRUE == ulIsNeedSortRoamPlmnList)
    {
        /* 把高低质量网络提取加入roam搜网列表 */
        NAS_MMC_BuildSearchedPlmnListInfoByRrcSearchCnfFail(NAS_MML_NET_RAT_TYPE_WCDMA, &stPlmnSearchInfo, &stSearchedExistPlmnInfo);
        NAS_MMC_BuildRoamPlmnSelectionListBySearchedExistPlmnInfo(NAS_MML_NET_RAT_TYPE_WCDMA,
                     &stSearchedExistPlmnInfo, &stNewRoamPlmnSelectionList);

        /* 把排过序的roam搜网列表插入搜网列表前面 */
        NAS_MMC_AddRoamPlmnSelectionListInPlmnSelectionList(&stNewRoamPlmnSelectionList, pstPlmnSrchList);

        /* 设置该接入技术已经收到过接入层searched plmn info ind进行过一轮排序 */
        NAS_MMC_SetSearchedRoamPlmnSortedFlag_PlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA, VOS_TRUE);


        /* 根据消息中携带的搜网信息更新搜网列表 */
        NAS_MMC_UpdatePlmnSearchList_PlmnSelection(&stPlmnSearchInfo,
                                                   NAS_MMC_IsNeedSortAvailablePlmnSelectionList_PlmnSelection(),
                                                   VOS_TRUE);

        /* 可维可测,将选网列表输出 */
        NAS_MMC_LogDplmnNplmnList();

    }

    /* 更新当前接入技术进行了全频搜网,如果在前面更新漫游网络可能无法加入漫游搜网列表，所以构造完漫游搜网列表后再更新进行过全频搜网*/
    NAS_MMC_SetAllBandSearch_PlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA, VOS_TRUE);

    /* 当还存在下一个需要搜索的网络时，继续进行搜网，否则，进入限制驻留 */
    if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        if (NAS_MML_NET_RAT_TYPE_WCDMA == stDestPlmn.enRat)
        {
            /* 向W接入层发送搜网请求，迁移到相应的L2状态，并启动保护定时器 */
            NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
        }
        else
        {
            /* 向W接入层发送挂起请求，迁移到相应的L2状态，并启动保护定时器 */
            NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA);
        }
    }
    else
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();
    }

    return;

}



/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmHistoryPlmnSrchCnf_PlmnSelection_WaitWasPlmnSearchCnf
 功能描述  : 收到WAS 历史频点搜网CNF后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:rrmm_plmn_SEARCH_cnf消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年5月21日
   作    者   : w00167002
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0项目修改,history搜的处理逻辑
*****************************************************************************/
VOS_VOID NAS_MMC_RcvRrMmHistoryPlmnSrchCnf_PlmnSelection_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU                              *pstSrchCnfMsg = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stDestPlmn;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    stPlmnSearchInfo;
    VOS_UINT32                                              ulIsNeedSortRoamPlmnList;
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                        stSearchedExistPlmnInfo;
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                        stNewRoamPlmnSelectionList;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSrchList   = VOS_NULL_PTR;

    /* 获取选网列表 */
    pstPlmnSrchList                = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();
    ulIsNeedSortRoamPlmnList       = VOS_FALSE;
    PS_MEM_SET(&stSearchedExistPlmnInfo, 0, sizeof(stSearchedExistPlmnInfo));
    PS_MEM_SET(&stNewRoamPlmnSelectionList, 0, sizeof(stNewRoamPlmnSelectionList));

    pstSrchCnfMsg = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;

    /* 解决版本Coverity问题 */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF);

    /* 更新HISTORY搜网的覆盖类型 */
    NAS_MMC_UpdateGUCoverageFlg_PlmnSelection(pstSrchCnfMsg);

    if (RRC_PLMN_SEARCH_RLT_HISTORY_SUCC == pstSrchCnfMsg->ulSearchRlt)
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_SUCCESS,
                VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        /* 设置UTRAN已经完成HISTORY搜索流程 */
        NAS_MMC_SetHistorySearchedFlag_PlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA, VOS_TRUE);

        NAS_MMC_UpdateRfAvailFlgPlmnSrchSucc_PlmnSelection();

        /* 根据不同的搜网模式，迁移到不同的L2状态，启动保护定时器 */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_SYSINFO_IND);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO, TI_NAS_MMC_WAIT_WAS_SYS_INFO_LEN);

        return;
    }

    /* 如果当前为NO RF，则直接退状态机 */
    if (RRC_PLMN_SEARCH_RLT_HISTORY_NO_RF == pstSrchCnfMsg->ulSearchRlt)
    {
        NAS_MMC_ProcNoRf_PlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA);

        return;
    }

    /* 设置UTRAN已经完成HISTORY搜索流程 */
    NAS_MMC_SetHistorySearchedFlag_PlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA, VOS_TRUE);


    /* 将搜网消息中携带的网络信息转换为内部消息中网络信息 */
    NAS_MMC_ConvertRrcPlmnList2SearchedPlmnListInfo(NAS_MML_NET_RAT_TYPE_WCDMA,
                                                     &pstSrchCnfMsg->PlmnIdList,
                                                     &stPlmnSearchInfo);

    /* 根据消息中携带的搜网信息更新搜网列表--- 没有进行全频段搜索，所以只能更新存在的网络 */
    NAS_MMC_UpdatePlmnSearchList_PlmnSelection(&stPlmnSearchInfo,
                                               NAS_MMC_IsNeedSortAvailablePlmnSelectionList_PlmnSelection(),
                                               VOS_FALSE);

    /* 搜网失败后更新RF可用标记 */
    NAS_MMC_UpdateRfAvailFlgPlmnSrchFail_PlmnSelection();

    /* 通知CSS当前MCC */
    NAS_MMC_SndCssCurrGeoIndAfterRcvPlmnSearchCnfFail_PlmnSelection(&stPlmnSearchInfo, VOS_TRUE);

    /* 如果搜网失败结果中带上来的网络没有一个跟rplmn或hplmn
       同一国家码且之前未排过序，需要构造漫游搜网列表插入原搜网列表头部*/
    ulIsNeedSortRoamPlmnList = NAS_MMC_IsNeedSortPlmnListRcvRrcPlmnSearchCnfFail_PlmnSelection(&stPlmnSearchInfo, NAS_MML_NET_RAT_TYPE_WCDMA);

    if (VOS_TRUE == ulIsNeedSortRoamPlmnList)
    {
        /* 把高低质量网络提取加入roam搜网列表 */
        NAS_MMC_BuildSearchedPlmnListInfoByRrcSearchCnfFail(NAS_MML_NET_RAT_TYPE_WCDMA, &stPlmnSearchInfo, &stSearchedExistPlmnInfo);
        NAS_MMC_BuildRoamPlmnSelectionListBySearchedExistPlmnInfo(NAS_MML_NET_RAT_TYPE_WCDMA,
                     &stSearchedExistPlmnInfo, &stNewRoamPlmnSelectionList);

        /* 把排过序的roam搜网列表插入搜网列表前面 */
        NAS_MMC_AddRoamPlmnSelectionListInPlmnSelectionList(&stNewRoamPlmnSelectionList, pstPlmnSrchList);

        /* 设置该接入技术已经收到过接入层searched plmn info ind进行过一轮排序 */
        NAS_MMC_SetSearchedRoamPlmnSortedFlag_PlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA, VOS_TRUE);


        /* 根据消息中携带的搜网信息更新搜网列表 */
        NAS_MMC_UpdatePlmnSearchList_PlmnSelection(&stPlmnSearchInfo,
                                                   NAS_MMC_IsNeedSortAvailablePlmnSelectionList_PlmnSelection(),
                                                   VOS_FALSE);                  /* 没有进行全BAND搜 */

        /* 可维可测,将选网列表输出 */
        NAS_MMC_LogDplmnNplmnList();

    }

    /* -------------注:HISTORY搜索失败，不能设置ALL BAND搜索------------- */

    /* 当还存在下一个需要搜索的网络时，继续进行搜网，否则，进入限制驻留 */
    if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        if (NAS_MML_NET_RAT_TYPE_WCDMA == stDestPlmn.enRat)
        {
            /* 向W接入层发送搜网请求，迁移到相应的L2状态，并启动保护定时器 */
            NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
        }
        else
        {
            /* 向W接入层发送挂起请求，迁移到相应的L2状态，并启动保护定时器 */
            NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA);
        }
    }
    else
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();
    }

    return;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmPlmnSrchCnf_PlmnSelection_WaitWasPlmnSearchCnf
 功能描述  : 收到WAS搜网CNF后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:rrmm_plmn_SEARCH_cnf消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年4月25日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2011年7月11日
   作    者   : sunxibo 46746
   修改内容   : V7R1 phase II,autoplmnsrch状态机调整为PlmnSelection状态机
 3.日    期   : 2011年12月15日
   作    者   : W00166186
   修改内容   : dts2011111502641,L下PLMN加入禁止TA后不再搜网

 4.日    期   : 2011年12月14日
   作    者   : w00176964
   修改内容   : V7R1 phaseIV 调整:驻留标记通过新的搜网控制上下文代替
 5.日    期   : 2012年06月02日
   作    者   : sunxibo /46746
   修改内容   : Added for V7R1 C50 CS/PS mode 1
 6.日    期   : 2013年8月27日
   作    者   : l00208543
   修改内容   : Coverity
 7.日    期   : 2014年1月21日
   作    者   : w00167002
   修改内容   : SVLTE共天线项目:在W下搜网失败为NO RF，表示当前天线资源不可用，
                则当前搜网结束。
 8.日    期   : 2013年3月29日
   作    者   : y00176023
   修改内容   : DSDS GUNAS II项目:NO RF情况下向RRM发起注册，只考虑GU不考虑LTE搜网产生的NO RF
 9.日    期   : 2014年6月21日
   作    者   : w00167002
   修改内容   : DSDS GUNAS III项目
10.日    期   : 2014年11月1日
   作    者   : z00161729
   修改内容   : 开机漫游搜网项目修改
11.日    期   : 2015年5月26日
   作    者   : w00167002
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0项目修改,分别处理指定搜和历史频点搜
12.日    期   : 2015年10月12日
   作    者   : s00217060
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0修改：增加pref band搜网结果
                 的处理
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvRrMmPlmnSrchCnf_PlmnSelection_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU                              *pstSrchCnfMsg = VOS_NULL_PTR;

    pstSrchCnfMsg = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;

    switch ( pstSrchCnfMsg->ulSearchRlt )
    {
        /* 全频段指定搜结果的处理 */
        case RRC_PLMN_SEARCH_RLT_SPEC:
        case RRC_PLMN_SEARCH_RLT_SPEC_NO_RF:
        case RRC_PLMN_SEARCH_RLT_SPEC_FAIL:
            NAS_MMC_RcvRrMmSpecPlmnSrchCnf_PlmnSelection_WaitWasPlmnSearchCnf(ulEventType, pstMsg);
            break;

        /* 历史频点指定搜结果的处理 */
        case RRC_PLMN_SEARCH_RLT_HISTORY_SUCC:
        case RRC_PLMN_SEARCH_RLT_HISTORY_NO_RF:
        case RRC_PLMN_SEARCH_RLT_HISTORY_FAIL:
            NAS_MMC_RcvRrMmHistoryPlmnSrchCnf_PlmnSelection_WaitWasPlmnSearchCnf(ulEventType, pstMsg);
            break;

        /* pref band搜结果的处理 */
        case RRC_PLMN_SEARCH_RLT_PREF_BAND_SUCC:
        case RRC_PLMN_SEARCH_RLT_PREF_BAND_NO_RF:
        case RRC_PLMN_SEARCH_RLT_PREF_BAND_FAIL:
            NAS_MMC_RcvRrMmPrefBandPlmnSrchCnf_PlmnSelection_WaitWasPlmnSearchCnf(ulEventType, pstMsg);
            break;

        default:
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvRrMmPlmnSrchCnf_PlmnSelection_WaitWasPlmnSearchCnf:UNEXPECTED SEARCH RSLT!!!");

            /* 异常保护按照指定搜失败处理 */
            NAS_MMC_RcvRrMmSpecPlmnSrchCnf_PlmnSelection_WaitWasPlmnSearchCnf(ulEventType, pstMsg);
            break;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvSearchedPlmnInfoInd_PlmnSelection_WaitWasPlmnSearchCnf
 功能描述  : 收到was RRMM_SEARCHED_PLMN_INFO_IND的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息内容
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年10月28日
   作    者   : z00161729
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_UpdateExistRplmnOrHplmnFlag_PlmnSelection(
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU   *pstSearchedExistPlmnInfo
)
{
    VOS_UINT32                          ulIndex;


    for (ulIndex = 0; ulIndex < pstSearchedExistPlmnInfo->usSearchPlmnNum; ulIndex++)
    {
        if (VOS_TRUE == NAS_MMC_IsPlmnMccSameWithRplmn(pstSearchedExistPlmnInfo->astPlmnSelectionList[ulIndex].stPlmnWithRat.stPlmnId.ulMcc))
        {
            NAS_MMC_SetExistRplmnOrHplmnFlag_PlmnSelection(VOS_TRUE);
            return;
        }

        if (VOS_TRUE == NAS_MMC_IsPlmnMccSameWithHplmn(pstSearchedExistPlmnInfo->astPlmnSelectionList[ulIndex].stPlmnWithRat.stPlmnId.ulMcc))
        {
            NAS_MMC_SetExistRplmnOrHplmnFlag_PlmnSelection(VOS_TRUE);
            return;
        }
    }

    return;

}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvSearchedPlmnInfoInd_PlmnSelection_WaitWasPlmnSearchCnf
 功能描述  : 收到was RRMM_SEARCHED_PLMN_INFO_IND的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息内容
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年10月28日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   : 2015年5月22日
   作    者   : b00269685
   修改内容   : 增加跳过搜W处理
 3.日    期   : 2015年10月9日
   作    者   : s00217060
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0修改
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvSearchedPlmnInfoInd_PlmnSelection_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SEARCHED_PLMN_INFO_IND_STRU                       *pstSearchedPlmnInfoMsg = VOS_NULL_PTR;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSrchList   = VOS_NULL_PTR;
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                        stNewRoamPlmnSelectionList;
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                        stSearchedExistPlmnInfo;
    VOS_UINT32                                              ulIsNeedStopPlmnSearch;

    pstSearchedPlmnInfoMsg        = (RRMM_SEARCHED_PLMN_INFO_IND_STRU *)pstMsg;
    PS_MEM_SET(&stNewRoamPlmnSelectionList, 0, sizeof(stNewRoamPlmnSelectionList));
    PS_MEM_SET(&stSearchedExistPlmnInfo, 0, sizeof(stSearchedExistPlmnInfo));

    NAS_MMC_SndMsccSrchedGuPlmnInfo(NAS_MSCC_PIF_NET_RAT_TYPE_WCDMA, pstSearchedPlmnInfoMsg);


    /* 获取选网列表 */
    pstPlmnSrchList = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();

    if (pstSearchedPlmnInfoMsg->ulAvailPlmnNum > NAS_RRC_MAX_AVAILPLMN_NUM)
    {
        pstSearchedPlmnInfoMsg->ulAvailPlmnNum = NAS_RRC_MAX_AVAILPLMN_NUM;
    }
    NAS_MMC_BuildSearchedPlmnInfoByRrcSearchedPlmnInfoInd(pstSearchedPlmnInfoMsg, &stSearchedExistPlmnInfo);

    NAS_MMC_UpdateExistRplmnOrHplmnFlag_PlmnSelection(&stSearchedExistPlmnInfo);

    /* 通知CSS当前MCC */
    NAS_MMC_SndCssCurrGeoIndAfterRcvPlmnInfoInd_PlmnSelection(&stSearchedExistPlmnInfo, VOS_TRUE);

    ulIsNeedStopPlmnSearch = NAS_MMC_IsNeedStopPlmnSearchRcvRrcSearchedPlmnInfoInd_PlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA,pstSearchedPlmnInfoMsg);

    if ((VOS_TRUE == NAS_MMC_IsNeedSortRoamPlmnSelectionList_PlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA))
     && (VOS_TRUE == ulIsNeedStopPlmnSearch))
    {
        /* 开机漫游场景对漫游搜网列表排序，原则如下:
         1、接入层上报存在的网络放在漫游搜网列表前面,在NPLMN中的网络不添加，
            支持的所有接入技术都添加，当前搜网的接入技术优先
         2、在gastNetworkNameTbl中找出跟当前存在网络相同国家码的plmn加入漫游搜网列表，
            在NPLMN中的网络不添加，支持的所有接入技术都添加，当前搜网的接入技术优先
         3、根据DPLMN->UPLMN->OPLMN->AVAILABLE PLMN顺序对漫游搜网列表进行排序
        */
        NAS_MMC_BuildRoamPlmnSelectionListBySearchedExistPlmnInfo(NAS_MML_NET_RAT_TYPE_WCDMA,
            &stSearchedExistPlmnInfo, &stNewRoamPlmnSelectionList);

        /* 把排过序的roam搜网列表插入搜网列表前面 */
        NAS_MMC_AddRoamPlmnSelectionListInPlmnSelectionList(&stNewRoamPlmnSelectionList, pstPlmnSrchList);

        /* 可维可测,将选网列表输出 */
        NAS_MMC_LogPlmnSelectionList(pstPlmnSrchList);
        NAS_MMC_LogDplmnNplmnList();

        /* 设置该接入技术已经收到过接入层searched plmn info ind进行过一轮排序 */
        NAS_MMC_SetSearchedRoamPlmnSortedFlag_PlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA, VOS_TRUE);

        /* 如果当前是HISTORY搜，则设置UTRAN已经完成HISTORY搜索流程 */
        if (NAS_MMC_PLMN_SEARCH_TYPE_HISTORY == NAS_MMC_GetCurrSearchingType_PlmnSelection())
        {
            NAS_MMC_SetHistorySearchedFlag_PlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA, VOS_TRUE);
        }
        /* 通知utran ctrl模块打断当前搜网，更新utran ctrl mode为fdd */
        NAS_MMC_SndInterAbortUtranCtrlPlmnSearchReqMsg();

        return VOS_TRUE;
    }

    if (VOS_TRUE == NAS_MMC_IsNeedSkipFddRcvRrcSearchedPlmnInfoInd_PlmnSelection(pstSearchedPlmnInfoMsg))
    {
        NAS_MMC_SndInterSkipSearchWIndMsg();

        return VOS_TRUE;
    }

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvInterAbortUtranCtrlPlmnSearchCnf_WaitWasPlmnSearchCnf
 功能描述  : 收到mmc内部消息inter abort utran ctrl plmn search cnf的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息内容
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年10月28日
   作    者   : z00161729
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvInterAbortUtranCtrlPlmnSearchCnf_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
     /* 停止保护定时器 */
     NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF);


     /* 通知AS停止指定搜网 */
     NAS_MMC_SndAsPlmnSrchStopReq(WUEPS_PID_WRR);

     /*根据不同的搜网模式，迁移到不同的L2状态，启动不同保护定时器*/
     NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_PLMN_STOP_CNF);

     (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF_LEN);

     return VOS_TRUE;

}




/*****************************************************************************
 函 数 名  : NAS_MMC_RcvSearchedPlmnInfoInd_PlmnSelection_WaitGasPlmnSearchCnf
 功能描述  : 收到GAS RRMM_SEARCHED_PLMN_INFO_IND的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息内容
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年10月28日
   作    者   : z00161729
   修改内容   : 开机漫游搜网项目修改
 2.日    期   : 2015年5月26日
   作    者   : w00167002
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0项目修改
 3.日    期   : 2015年10月9日
   作    者   : s00217060
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0修改
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvSearchedPlmnInfoInd_PlmnSelection_WaitGasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SEARCHED_PLMN_INFO_IND_STRU                       *pstSearchedPlmnInfoMsg = VOS_NULL_PTR;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSrchList   = VOS_NULL_PTR;
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                        stNewRoamPlmnSelectionList;
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                        stSearchedExistPlmnInfo;

    pstSearchedPlmnInfoMsg        = (RRMM_SEARCHED_PLMN_INFO_IND_STRU *)pstMsg;
    PS_MEM_SET(&stNewRoamPlmnSelectionList, 0, sizeof(stNewRoamPlmnSelectionList));
    PS_MEM_SET(&stSearchedExistPlmnInfo, 0, sizeof(stSearchedExistPlmnInfo));

    NAS_MMC_SndMsccSrchedGuPlmnInfo(NAS_MSCC_PIF_NET_RAT_TYPE_GSM, pstSearchedPlmnInfoMsg);

    /* 获取选网列表 */
    pstPlmnSrchList = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();
    if (pstSearchedPlmnInfoMsg->ulAvailPlmnNum > NAS_RRC_MAX_AVAILPLMN_NUM)
    {
        pstSearchedPlmnInfoMsg->ulAvailPlmnNum = NAS_RRC_MAX_AVAILPLMN_NUM;
    }

    NAS_MMC_BuildSearchedPlmnInfoByRrcSearchedPlmnInfoInd(pstSearchedPlmnInfoMsg, &stSearchedExistPlmnInfo);

    NAS_MMC_UpdateExistRplmnOrHplmnFlag_PlmnSelection(&stSearchedExistPlmnInfo);

    /* 通知CSS当前MCC */
    NAS_MMC_SndCssCurrGeoIndAfterRcvPlmnInfoInd_PlmnSelection(&stSearchedExistPlmnInfo, VOS_TRUE);

    if (VOS_FALSE == NAS_MMC_IsNeedSortRoamPlmnSelectionList_PlmnSelection(NAS_MML_NET_RAT_TYPE_GSM))
    {
        return VOS_TRUE;
    }

    if (VOS_TRUE == NAS_MMC_IsNeedStopPlmnSearchRcvRrcSearchedPlmnInfoInd_PlmnSelection(NAS_MML_NET_RAT_TYPE_GSM, pstSearchedPlmnInfoMsg))
    {
        /* 开机漫游场景对漫游搜网列表排序，原则如下:
         1、接入层上报存在的网络放在漫游搜网列表前面,在NPLMN中的网络不添加，
            支持的所有接入技术都添加，当前搜网的接入技术优先
         2、在gastNetworkNameTbl中找出跟当前存在网络相同国家码的plmn加入漫游搜网列表，
            在NPLMN中的网络不添加，支持的所有接入技术都添加，当前搜网的接入技术优先
         3、根据DPLMN->UPLMN->OPLMN->AVAILABLE PLMN顺序对漫游搜网列表进行排序
        */
        NAS_MMC_BuildRoamPlmnSelectionListBySearchedExistPlmnInfo(NAS_MML_NET_RAT_TYPE_GSM,
            &stSearchedExistPlmnInfo, &stNewRoamPlmnSelectionList);

        /* 把排过序的roam搜网列表插入搜网列表前面 */
        NAS_MMC_AddRoamPlmnSelectionListInPlmnSelectionList(&stNewRoamPlmnSelectionList, pstPlmnSrchList);

        /* 可维可测,将选网列表输出 */
        NAS_MMC_LogPlmnSelectionList(pstPlmnSrchList);
        NAS_MMC_LogDplmnNplmnList();

        /* 设置该接入技术已经收到过接入层searched plmn info ind进行过一轮排序 */
        NAS_MMC_SetSearchedRoamPlmnSortedFlag_PlmnSelection(NAS_MML_NET_RAT_TYPE_GSM, VOS_TRUE);

        /* 如果当前是HISTORY搜，则设置G下已经完成HISTORY搜索流程 */
        if (NAS_MMC_PLMN_SEARCH_TYPE_HISTORY == NAS_MMC_GetCurrSearchingType_PlmnSelection())
        {
            NAS_MMC_SetHistorySearchedFlag_PlmnSelection(NAS_MML_NET_RAT_TYPE_GSM, VOS_TRUE);
        }

        /* 停止保护定时器 */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_SEARCH_CNF);

        /* 通知接入层停止当前搜网 */
        NAS_MMC_SndAsPlmnSrchStopReq(UEPS_PID_GAS);

        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_PLMN_STOP_CNF);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF_LEN);
    }

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmPlmnSrchCnf_PlmnSelection_WaitGasPlmnSearchCnf
 功能描述  : 收到GAS搜网CNF后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:rrmm_plmn_SEARCH_cnf消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年4月25日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2011年7月11日
   作    者   : sunxibo 46746
   修改内容   : V7R1 phase II,autoplmnsrch状态机调整为PlmnSelection状态机
 3.日    期   : 2011年11月22日
   作    者   : w00166186
   修改内容   : DTS2011111603440,搜网失败，上报搜网成功
 4.日    期   : 2011年12月15日
   作    者   : W00166186
   修改内容   : dts2011111502641,L下PLMN加入禁止TA后不再搜网
 5.日    期   : 2011年12月14日
   作    者   : w00176964
   修改内容   : V7R1 phaseIV 调整:驻留标记通过新的搜网控制上下文代替
 6.日    期   : 2012年06月02日
   作    者   : sunxibo /46746
   修改内容   : Added for V7R1 C50 CS/PS mode 1
 7.日    期   : 2013年8月27日
   作    者   : l00208543
   修改内容   : Coverity
 8.日    期   : 2013年3月29日
   作    者   : y00176023
   修改内容   : DSDS GUNAS II项目:NO RF情况下向RRM发起注册，只考虑GU不考虑LTE搜网产生的NO RF
 9.日    期   : 2014年6月21日
   作    者   : b00269685
   修改内容   : DSDS III项目
10.日    期   : 2014年11月3日
   作    者   : z00161729
   修改内容   : 开机漫游搜网项目修改
11.日    期   : 2015年5月26日
   作    者   : w00167002
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0项目修改
*****************************************************************************/
VOS_VOID NAS_MMC_RcvRrMmSpecPlmnSrchCnf_PlmnSelection_WaitGasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU                              *pstSrchCnfMsg = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stDestPlmn;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    stPlmnSearchInfo;

    VOS_UINT32                                              ulIsNeedSortRoamPlmnList;
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                        stSearchedExistPlmnInfo;
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                        stNewRoamPlmnSelectionList;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSrchList   = VOS_NULL_PTR;

    /* 获取选网列表 */
    pstPlmnSrchList                  = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();
    ulIsNeedSortRoamPlmnList         = VOS_FALSE;
    PS_MEM_SET(&stSearchedExistPlmnInfo, 0, sizeof(stSearchedExistPlmnInfo));
    PS_MEM_SET(&stNewRoamPlmnSelectionList, 0, sizeof(stNewRoamPlmnSelectionList));

    pstSrchCnfMsg = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;

    /* 解决版本Coverity问题 */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_SEARCH_CNF);

    /* 设置当前模式是否进行全频搜网，是否存在网络覆盖 */
    NAS_MMC_UpdateGUCoverageFlg_PlmnSelection(pstSrchCnfMsg);

    if (RRC_PLMN_SEARCH_RLT_SPEC == pstSrchCnfMsg->ulSearchRlt)
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_SUCCESS,
                VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_UpdateRfAvailFlgPlmnSrchSucc_PlmnSelection();

        /* 根据不同的搜网模式，迁移到不同的L2状态，启动保护定时器 */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_SYSINFO_IND);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_SYS_INFO, TI_NAS_MMC_WAIT_GAS_SYS_INFO_LEN);

        return;
    }


    /* 如果当前为NO RF，则直接退状态机 */
    if (RRC_PLMN_SEARCH_RLT_SPEC_NO_RF == pstSrchCnfMsg->ulSearchRlt)
    {
        NAS_MMC_ProcNoRf_PlmnSelection(NAS_MML_NET_RAT_TYPE_GSM);

        return;
    }


    /* 将搜网消息中携带的网络信息转换为内部消息中网络信息 */
    NAS_MMC_ConvertRrcPlmnList2SearchedPlmnListInfo(NAS_MML_NET_RAT_TYPE_GSM,
                                                     &pstSrchCnfMsg->PlmnIdList,
                                                     &stPlmnSearchInfo);

    /* 根据消息中携带的搜网信息更新搜网列表 */
    NAS_MMC_UpdatePlmnSearchList_PlmnSelection(&stPlmnSearchInfo,
                                               NAS_MMC_IsNeedSortAvailablePlmnSelectionList_PlmnSelection(),
                                               VOS_TRUE);

    /* 搜网失败后更新RF可用标记 */
    NAS_MMC_UpdateRfAvailFlgPlmnSrchFail_PlmnSelection();

    /* 通知CSS当前MCC */
    NAS_MMC_SndCssCurrGeoIndAfterRcvPlmnSearchCnfFail_PlmnSelection(&stPlmnSearchInfo, VOS_TRUE);

    /* 如果搜网失败结果中带上来的网络没有一个跟rplmn或hplmn
       同一国家码且之前未排过序，需要构造漫游搜网列表插入原搜网头部*/
    ulIsNeedSortRoamPlmnList = NAS_MMC_IsNeedSortPlmnListRcvRrcPlmnSearchCnfFail_PlmnSelection(&stPlmnSearchInfo, NAS_MML_NET_RAT_TYPE_GSM);

    if (VOS_TRUE == ulIsNeedSortRoamPlmnList)
    {
        /* 把高低质量网络提取加入roam搜网列表 */
        NAS_MMC_BuildSearchedPlmnListInfoByRrcSearchCnfFail(NAS_MML_NET_RAT_TYPE_GSM, &stPlmnSearchInfo, &stSearchedExistPlmnInfo);
        NAS_MMC_BuildRoamPlmnSelectionListBySearchedExistPlmnInfo(NAS_MML_NET_RAT_TYPE_GSM,
            &stSearchedExistPlmnInfo, &stNewRoamPlmnSelectionList);

        /* 把排过序的roam搜网列表插入搜网列表前面 */
        NAS_MMC_AddRoamPlmnSelectionListInPlmnSelectionList(&stNewRoamPlmnSelectionList, pstPlmnSrchList);

        /* 设置该接入技术已经收到过接入层searched plmn info ind进行过一轮排序 */
        NAS_MMC_SetSearchedRoamPlmnSortedFlag_PlmnSelection(NAS_MML_NET_RAT_TYPE_GSM, VOS_TRUE);

        /* 根据消息中携带的搜网信息更新搜网列表 */
        NAS_MMC_UpdatePlmnSearchList_PlmnSelection(&stPlmnSearchInfo,
                                                   NAS_MMC_IsNeedSortAvailablePlmnSelectionList_PlmnSelection(),
                                                   VOS_TRUE);

        /* 可维可测,将选网列表输出 */
        NAS_MMC_LogDplmnNplmnList();

    }


    /* 更新当前接入技术进行了全频搜网,如果在前面更新漫游网络可能无法加入漫游搜网列表，所以构造完漫游搜网列表后再更新进行过全频搜网*/
    NAS_MMC_SetAllBandSearch_PlmnSelection(NAS_MML_NET_RAT_TYPE_GSM, VOS_TRUE);



    /* 当还存在下一个需要搜索的网络时，继续进行搜网，否则，进入限制驻留 */
    if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        if (NAS_MML_NET_RAT_TYPE_GSM == stDestPlmn.enRat)
        {
            /* 向G接入层发送搜网请求，迁移到相应的L2状态，并启动保护定时器 */
            NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
        }
        else
        {
            /* 向G接入层发送挂起请求，迁移到相应的L2状态，并启动保护定时器 */
            NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_NET_RAT_TYPE_GSM);
        }
    }
    else
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();
    }

    return;

}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmPlmnSrchCnf_PlmnSelection_WaitGasPlmnSearchCnf
 功能描述  : 收到GAS HISTORY搜网CNF后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:rrmm_plmn_SEARCH_cnf消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年5月25日
   作    者   : w00167002
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_RcvRrMmHistoryPlmnSrchCnf_PlmnSelection_WaitGasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU                              *pstSrchCnfMsg = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stDestPlmn;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    stPlmnSearchInfo;
    VOS_UINT32                                              ulIsNeedSortRoamPlmnList;
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                        stSearchedExistPlmnInfo;
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                        stNewRoamPlmnSelectionList;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSrchList   = VOS_NULL_PTR;

    /* 获取选网列表 */
    pstPlmnSrchList                  = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();
    ulIsNeedSortRoamPlmnList         = VOS_FALSE;
    PS_MEM_SET(&stSearchedExistPlmnInfo, 0, sizeof(stSearchedExistPlmnInfo));
    PS_MEM_SET(&stNewRoamPlmnSelectionList, 0, sizeof(stNewRoamPlmnSelectionList));

    pstSrchCnfMsg = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;

    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_SEARCH_CNF);

    /* 更新HISTORY搜网的覆盖类型 */
    NAS_MMC_UpdateGUCoverageFlg_PlmnSelection(pstSrchCnfMsg);

    if (RRC_PLMN_SEARCH_RLT_HISTORY_SUCC == pstSrchCnfMsg->ulSearchRlt)
    {
        /* 更新当前GAS已完成HISTORY搜索 */
        NAS_MMC_SetHistorySearchedFlag_PlmnSelection(NAS_MML_NET_RAT_TYPE_GSM, VOS_TRUE);

        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_SUCCESS,
                VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_UpdateRfAvailFlgPlmnSrchSucc_PlmnSelection();

        /* 根据不同的搜网模式，迁移到不同的L2状态，启动保护定时器 */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_SYSINFO_IND);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_SYS_INFO, TI_NAS_MMC_WAIT_GAS_SYS_INFO_LEN);

        return;
    }

    /* 如果当前为NO RF，则直接退状态机 */
    if (RRC_PLMN_SEARCH_RLT_HISTORY_NO_RF == pstSrchCnfMsg->ulSearchRlt)
    {
        NAS_MMC_ProcNoRf_PlmnSelection(NAS_MML_NET_RAT_TYPE_GSM);

        return;
    }

    /* 更新当前GAS已完成HISTORY搜索 */
    NAS_MMC_SetHistorySearchedFlag_PlmnSelection(NAS_MML_NET_RAT_TYPE_GSM, VOS_TRUE);

    /* 将搜网消息中携带的网络信息转换为内部消息中网络信息 */
    NAS_MMC_ConvertRrcPlmnList2SearchedPlmnListInfo(NAS_MML_NET_RAT_TYPE_GSM,
                                                     &pstSrchCnfMsg->PlmnIdList,
                                                     &stPlmnSearchInfo);

    /* 根据消息中携带的搜网信息更新搜网列表 */
    NAS_MMC_UpdatePlmnSearchList_PlmnSelection(&stPlmnSearchInfo,
                                               NAS_MMC_IsNeedSortAvailablePlmnSelectionList_PlmnSelection(),
                                               VOS_FALSE);

    /* 搜网失败后更新RF可用标记 */
    NAS_MMC_UpdateRfAvailFlgPlmnSrchFail_PlmnSelection();

    /* 通知CSS当前MCC */
    NAS_MMC_SndCssCurrGeoIndAfterRcvPlmnSearchCnfFail_PlmnSelection(&stPlmnSearchInfo, VOS_TRUE);

    /* 如果搜网失败结果中带上来的网络没有一个跟rplmn或hplmn
       同一国家码且之前未排过序，需要构造漫游搜网列表插入原搜网头部*/
    ulIsNeedSortRoamPlmnList = NAS_MMC_IsNeedSortPlmnListRcvRrcPlmnSearchCnfFail_PlmnSelection(&stPlmnSearchInfo, NAS_MML_NET_RAT_TYPE_GSM);

    if (VOS_TRUE == ulIsNeedSortRoamPlmnList)
    {
        /* 把高低质量网络提取加入roam搜网列表 */
        NAS_MMC_BuildSearchedPlmnListInfoByRrcSearchCnfFail(NAS_MML_NET_RAT_TYPE_GSM, &stPlmnSearchInfo, &stSearchedExistPlmnInfo);
        NAS_MMC_BuildRoamPlmnSelectionListBySearchedExistPlmnInfo(NAS_MML_NET_RAT_TYPE_GSM,
            &stSearchedExistPlmnInfo, &stNewRoamPlmnSelectionList);

        /* 把排过序的roam搜网列表插入搜网列表前面 */
        NAS_MMC_AddRoamPlmnSelectionListInPlmnSelectionList(&stNewRoamPlmnSelectionList, pstPlmnSrchList);

        /* 设置该接入技术已经收到过接入层searched plmn info ind进行过一轮排序 */
        NAS_MMC_SetSearchedRoamPlmnSortedFlag_PlmnSelection(NAS_MML_NET_RAT_TYPE_GSM, VOS_TRUE);

        /* 根据消息中携带的搜网信息更新搜网列表 */
        NAS_MMC_UpdatePlmnSearchList_PlmnSelection(&stPlmnSearchInfo,
                                                   NAS_MMC_IsNeedSortAvailablePlmnSelectionList_PlmnSelection(),
                                                   VOS_FALSE);
        /* 可维可测,将选网列表输出 */
        NAS_MMC_LogDplmnNplmnList();

    }


    /* 当还存在下一个需要搜索的网络时，继续进行搜网，否则，进入限制驻留 */
    if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        if (NAS_MML_NET_RAT_TYPE_GSM == stDestPlmn.enRat)
        {
            /* 向G接入层发送搜网请求，迁移到相应的L2状态，并启动保护定时器 */
            NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
        }
        else
        {
            /* 向G接入层发送挂起请求，迁移到相应的L2状态，并启动保护定时器 */
            NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_NET_RAT_TYPE_GSM);
        }
    }
    else
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();
    }

    return;

}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmPrefBandPlmnSrchCnf_PlmnSelection_WaitGasPlmnSearchCnf
 功能描述  : 等GAS的搜网结果时收到pref band搜网结果的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月12日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_RcvRrMmPrefBandPlmnSrchCnf_PlmnSelection_WaitGasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU                              *pstSrchCnfMsg = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stDestPlmn;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    stPlmnSearchInfo;

    VOS_UINT32                                              ulIsNeedSortRoamPlmnList;
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                        stSearchedExistPlmnInfo;
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                        stNewRoamPlmnSelectionList;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSrchList   = VOS_NULL_PTR;

    /* 获取选网列表 */
    pstPlmnSrchList                  = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();
    ulIsNeedSortRoamPlmnList         = VOS_FALSE;
    PS_MEM_SET(&stSearchedExistPlmnInfo, 0, sizeof(stSearchedExistPlmnInfo));
    PS_MEM_SET(&stNewRoamPlmnSelectionList, 0, sizeof(stNewRoamPlmnSelectionList));

    pstSrchCnfMsg = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;

    /* 解决版本Coverity问题 */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_SEARCH_CNF);

    /* 设置当前模式是否进行全频搜网，是否存在网络覆盖 */
    NAS_MMC_UpdateGUCoverageFlg_PlmnSelection(pstSrchCnfMsg);

    if (RRC_PLMN_SEARCH_RLT_PREF_BAND_SUCC == pstSrchCnfMsg->ulSearchRlt)
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_SUCCESS,
                VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_UpdateRfAvailFlgPlmnSrchSucc_PlmnSelection();

        /* 根据不同的搜网模式，迁移到不同的L2状态，启动保护定时器 */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_SYSINFO_IND);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_SYS_INFO, TI_NAS_MMC_WAIT_GAS_SYS_INFO_LEN);

        return;
    }


    /* 如果当前为NO RF，则直接退状态机 */
    if (RRC_PLMN_SEARCH_RLT_PREF_BAND_NO_RF == pstSrchCnfMsg->ulSearchRlt)
    {
        NAS_MMC_ProcNoRf_PlmnSelection(NAS_MML_NET_RAT_TYPE_GSM);

        return;
    }


    /* 将搜网消息中携带的网络信息转换为内部消息中网络信息 */
    NAS_MMC_ConvertRrcPlmnList2SearchedPlmnListInfo(NAS_MML_NET_RAT_TYPE_GSM,
                                                     &pstSrchCnfMsg->PlmnIdList,
                                                     &stPlmnSearchInfo);

    /* 根据消息中携带的搜网信息更新搜网列表 */
    NAS_MMC_UpdatePlmnSearchList_PlmnSelection(&stPlmnSearchInfo,
                                               NAS_MMC_IsNeedSortAvailablePlmnSelectionList_PlmnSelection(),
                                               VOS_TRUE);

    /* 搜网失败后更新RF可用标记 */
    NAS_MMC_UpdateRfAvailFlgPlmnSrchFail_PlmnSelection();

    /* 通知CSS当前MCC */
    NAS_MMC_SndCssCurrGeoIndAfterRcvPlmnSearchCnfFail_PlmnSelection(&stPlmnSearchInfo, VOS_TRUE);

    /* 如果搜网失败结果中带上来的网络没有一个跟rplmn或hplmn
       同一国家码且之前未排过序，需要构造漫游搜网列表插入原搜网头部*/
    ulIsNeedSortRoamPlmnList = NAS_MMC_IsNeedSortPlmnListRcvRrcPlmnSearchCnfFail_PlmnSelection(&stPlmnSearchInfo, NAS_MML_NET_RAT_TYPE_GSM);

    if (VOS_TRUE == ulIsNeedSortRoamPlmnList)
    {
        /* 把高低质量网络提取加入roam搜网列表 */
        NAS_MMC_BuildSearchedPlmnListInfoByRrcSearchCnfFail(NAS_MML_NET_RAT_TYPE_GSM, &stPlmnSearchInfo, &stSearchedExistPlmnInfo);
        NAS_MMC_BuildRoamPlmnSelectionListBySearchedExistPlmnInfo(NAS_MML_NET_RAT_TYPE_GSM,
            &stSearchedExistPlmnInfo, &stNewRoamPlmnSelectionList);

        /* 把排过序的roam搜网列表插入搜网列表前面 */
        NAS_MMC_AddRoamPlmnSelectionListInPlmnSelectionList(&stNewRoamPlmnSelectionList, pstPlmnSrchList);

        /* 设置该接入技术已经收到过接入层searched plmn info ind进行过一轮排序 */
        NAS_MMC_SetSearchedRoamPlmnSortedFlag_PlmnSelection(NAS_MML_NET_RAT_TYPE_GSM, VOS_TRUE);

        /* 根据消息中携带的搜网信息更新搜网列表 */
        NAS_MMC_UpdatePlmnSearchList_PlmnSelection(&stPlmnSearchInfo,
                                                   NAS_MMC_IsNeedSortAvailablePlmnSelectionList_PlmnSelection(),
                                                   VOS_TRUE);

        /* 可维可测,将选网列表输出 */
        NAS_MMC_LogDplmnNplmnList();

    }

    /* 更新当前接入技术进行了全频搜网,如果在前面更新漫游网络可能无法加入漫游搜网列表，所以构造完漫游搜网列表后再更新进行过全频搜网*/
    NAS_MMC_SetAllBandSearch_PlmnSelection(NAS_MML_NET_RAT_TYPE_GSM, VOS_TRUE);

    /* 当还存在下一个需要搜索的网络时，继续进行搜网，否则，进入限制驻留 */
    if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        if (NAS_MML_NET_RAT_TYPE_GSM == stDestPlmn.enRat)
        {
            /* 向G接入层发送搜网请求，迁移到相应的L2状态，并启动保护定时器 */
            NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
        }
        else
        {
            /* 向G接入层发送挂起请求，迁移到相应的L2状态，并启动保护定时器 */
            NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_NET_RAT_TYPE_GSM);
        }
    }
    else
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();
    }

    return;

}



/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmPlmnSrchCnf_PlmnSelection_WaitGasPlmnSearchCnf
 功能描述  : 收到GAS搜网CNF后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:rrmm_plmn_SEARCH_cnf消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年4月25日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2011年7月11日
   作    者   : sunxibo 46746
   修改内容   : V7R1 phase II,autoplmnsrch状态机调整为PlmnSelection状态机
 3.日    期   : 2011年11月22日
   作    者   : w00166186
   修改内容   : DTS2011111603440,搜网失败，上报搜网成功
 4.日    期   : 2011年12月15日
   作    者   : W00166186
   修改内容   : dts2011111502641,L下PLMN加入禁止TA后不再搜网
 5.日    期   : 2011年12月14日
   作    者   : w00176964
   修改内容   : V7R1 phaseIV 调整:驻留标记通过新的搜网控制上下文代替
 6.日    期   : 2012年06月02日
   作    者   : sunxibo /46746
   修改内容   : Added for V7R1 C50 CS/PS mode 1
 7.日    期   : 2013年8月27日
   作    者   : l00208543
   修改内容   : Coverity
 8.日    期   : 2013年3月29日
   作    者   : y00176023
   修改内容   : DSDS GUNAS II项目:NO RF情况下向RRM发起注册，只考虑GU不考虑LTE搜网产生的NO RF
 9.日    期   : 2014年6月21日
   作    者   : b00269685
   修改内容   : DSDS III项目
10.日    期   : 2014年11月3日
   作    者   : z00161729
   修改内容   : 开机漫游搜网项目修改
11.日    期   : 2015年5月26日
   作    者   : w00167002
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0项目修改
12.日    期   : 2015年10月12日
   作    者   : s00217060
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0:增加pref band搜结果的处理
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvRrMmPlmnSrchCnf_PlmnSelection_WaitGasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    RRMM_PLMN_SEARCH_CNF_STRU                              *pstSrchCnfMsg = VOS_NULL_PTR;

    pstSrchCnfMsg = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;

    switch ( pstSrchCnfMsg->ulSearchRlt )
    {
        /* 全频段指定搜结果的处理 */
        case RRC_PLMN_SEARCH_RLT_SPEC:
        case RRC_PLMN_SEARCH_RLT_SPEC_NO_RF:
        case RRC_PLMN_SEARCH_RLT_SPEC_FAIL:
            NAS_MMC_RcvRrMmSpecPlmnSrchCnf_PlmnSelection_WaitGasPlmnSearchCnf(ulEventType, pstMsg);
            break;

        /* 历史频点指定搜结果的处理 */
        case RRC_PLMN_SEARCH_RLT_HISTORY_SUCC:
        case RRC_PLMN_SEARCH_RLT_HISTORY_NO_RF:
        case RRC_PLMN_SEARCH_RLT_HISTORY_FAIL:
            NAS_MMC_RcvRrMmHistoryPlmnSrchCnf_PlmnSelection_WaitGasPlmnSearchCnf(ulEventType, pstMsg);
            break;

        case RRC_PLMN_SEARCH_RLT_PREF_BAND_SUCC:
        case RRC_PLMN_SEARCH_RLT_PREF_BAND_FAIL:
        case RRC_PLMN_SEARCH_RLT_PREF_BAND_NO_RF:
            NAS_MMC_RcvRrMmPrefBandPlmnSrchCnf_PlmnSelection_WaitGasPlmnSearchCnf(ulEventType, pstMsg);
            break;

        default:
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvRrMmPlmnSrchCnf_PlmnSelection_WaitGasPlmnSearchCnf:UNEXPECTED SEARCH RSLT!!!");

            /* 异常保护处理 */
            NAS_MMC_RcvRrMmSpecPlmnSrchCnf_PlmnSelection_WaitGasPlmnSearchCnf(ulEventType, pstMsg);
            break;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitWasSpecPlmnSearchCnfExpired_PlmnSelection_WaitWasPlmnSearchCnf
 功能描述  : 等待WAS全频段指定搜网回复过程中搜网定时器超时
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年4月23日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2011年7月11日
   作    者   : sunxibo 46746
   修改内容   : V7R1 phase II,autoplmnsrch状态机调整为PlmnSelection状态机
 3.日    期   : 2011年12月15日
   作    者   : W00166186
   修改内容   : dts2011111502641,L下PLMN加入禁止TA后不再搜网
 4.日    期   : 2011年12月14日
   作    者   : w00176964
   修改内容   : V7R1 phaseIV 调整:驻留标记通过新的搜网控制上下文代替
 5.日    期   : 2012年06月02日
   作    者   : sunxibo /46746
   修改内容   : Added for V7R1 C50 CS/PS mode 1
 6.日    期   : 2012年8月10日
   作    者   : L00171473
   修改内容   : DTS2012082204471, TQE清理
 7.日    期   : 2012年11月05日
   作    者   : w00176964
   修改内容   : DTS2011082405001:更新网络覆盖类型
 8.日    期   : 2013年8月27日
   作    者   : l00208543
   修改内容   : Coverity
 9.日    期   : 2014年6月6日
   作    者   : b00269685
   修改内容   : 定时器超时后，先通知WAS停止搜网
 10.日    期   : 2014年11月8日
    作    者   : z00161729
    修改内容   : 开机搜网优化项目修改
 11.日    期   : 2015年5月26日
    作    者   : w00167002
    修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0项目修改

*****************************************************************************/

VOS_VOID NAS_MMC_RcvTiWaitSpecPlmnSearchCnfExpired_PlmnSelection_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    stPlmnSearchInfo;


    PS_MEM_SET(&stPlmnSearchInfo, 0x00, sizeof(stPlmnSearchInfo));


    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitWasPlmnSearchCnfExpired_PlmnSelection_WaitWasPlmnSearchCnf: Timer Expired");

    /* 设置当前网络已经进行全频搜网 */
    NAS_MMC_SetAllBandSearch_PlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA, VOS_TRUE);

    /* 设置当前网络无覆盖 */
    NAS_MMC_SetRatCoverage_PlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA, NAS_MMC_COVERAGE_TYPE_NONE);

    /* 设置当前接入技术没有搜索到任何网络 */
    stPlmnSearchInfo.ulHighPlmnNum = 0x0;
    stPlmnSearchInfo.ulLowPlmnNum  = 0x0;
    stPlmnSearchInfo.enRatType     = NAS_MML_NET_RAT_TYPE_WCDMA;

    /* 根据消息中携带的搜网信息更新搜网列表 */
    NAS_MMC_UpdatePlmnSearchList_PlmnSelection(&stPlmnSearchInfo,
                                               NAS_MMC_IsNeedSortAvailablePlmnSelectionList_PlmnSelection(),
                                               VOS_TRUE);

    /* 通知AS停止指定搜网 */
    NAS_MMC_SndAsPlmnSrchStopReq(WUEPS_PID_WRR);

    /*根据不同的搜网模式，迁移到不同的L2状态，启动不同保护定时器*/
    NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_PLMN_STOP_CNF);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF_LEN);

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitWasHistoryPlmnSearchCnfExpired_PlmnSelection_WaitWasPlmnSearchCnf
 功能描述  : 等待WAS HISTORY搜网回复过程中搜网定时器超时
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年5月26日
   作    者   : w00167002
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0项目修改

*****************************************************************************/
VOS_VOID NAS_MMC_RcvTiWaitHistoryPlmnSearchCnfExpired_PlmnSelection_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitWasHistoryPlmnSearchCnfExpired_PlmnSelection_WaitWasPlmnSearchCnf: Timer Expired");

    /* 更新当前UTRAN已完成HISTORY搜索 */
    NAS_MMC_SetHistorySearchedFlag_PlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA, VOS_TRUE);

    /* 通知AS停止指定搜网 */
    NAS_MMC_SndAsPlmnSrchStopReq(WUEPS_PID_WRR);

    /*根据不同的搜网模式，迁移到不同的L2状态，启动不同保护定时器*/
    NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_PLMN_STOP_CNF);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF_LEN);

    return;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitWasPlmnSearchCnfExpired_PlmnSelection_WaitWasPlmnSearchCnf
 功能描述  : 等待WAS搜网回复过程中搜网定时器超时
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年4月23日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2011年7月11日
   作    者   : sunxibo 46746
   修改内容   : V7R1 phase II,autoplmnsrch状态机调整为PlmnSelection状态机
 3.日    期   : 2011年12月15日
   作    者   : W00166186
   修改内容   : dts2011111502641,L下PLMN加入禁止TA后不再搜网
 4.日    期   : 2011年12月14日
   作    者   : w00176964
   修改内容   : V7R1 phaseIV 调整:驻留标记通过新的搜网控制上下文代替
 5.日    期   : 2012年06月02日
   作    者   : sunxibo /46746
   修改内容   : Added for V7R1 C50 CS/PS mode 1
 6.日    期   : 2012年8月10日
   作    者   : L00171473
   修改内容   : DTS2012082204471, TQE清理
 7.日    期   : 2012年11月05日
   作    者   : w00176964
   修改内容   : DTS2011082405001:更新网络覆盖类型
 8.日    期   : 2013年8月27日
   作    者   : l00208543
   修改内容   : Coverity
 9.日    期   : 2014年6月6日
   作    者   : b00269685
   修改内容   : 定时器超时后，先通知WAS停止搜网
 10.日    期   : 2014年11月8日
    作    者   : z00161729
    修改内容   : 开机搜网优化项目修改
 11.日    期   : 2015年5月26日
    作    者   : w00167002
    修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0项目修改,增加HISTORY搜的处理
 12.日    期   : 2015年10月28日
    作    者   : s00217060
    修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0:增加pref band搜的处理

*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvTiWaitWasPlmnSearchCnfExpired_PlmnSelection_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRC_PLMN_SEARCH_TYPE_ENUM_UINT32    enCurrSearchingPlmnType;                /* 用于区别指定搜，history搜 */

    enCurrSearchingPlmnType = NAS_MMC_GetCurrSearchingType_PlmnSelection();

    switch (enCurrSearchingPlmnType)
    {
        case NAS_MMC_PLMN_SEARCH_TYPE_SPEC:
            NAS_MMC_RcvTiWaitSpecPlmnSearchCnfExpired_PlmnSelection_WaitWasPlmnSearchCnf(ulEventType, pstMsg);
            break;

        case NAS_MMC_PLMN_SEARCH_TYPE_HISTORY:
            NAS_MMC_RcvTiWaitHistoryPlmnSearchCnfExpired_PlmnSelection_WaitWasPlmnSearchCnf(ulEventType, pstMsg);
            break;

        case NAS_MMC_PLMN_SEARCH_TYPE_PREFBAND:
            NAS_MMC_RcvTiWaitSpecPlmnSearchCnfExpired_PlmnSelection_WaitWasPlmnSearchCnf(ulEventType, pstMsg);
            break;

        default:
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitWasPlmnSearchCnfExpired_PlmnSelection_WaitWasPlmnSearchCnf UNEXPECTED SEARCH TYPE!!!");

            /* 异常保护 */
            NAS_MMC_RcvTiWaitSpecPlmnSearchCnfExpired_PlmnSelection_WaitWasPlmnSearchCnf(ulEventType, pstMsg);
            break;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitGasSpecPlmnSearchCnfExpired_PlmnSelection_WaitGasPlmnSearchCnf
 功能描述  : 等待GAS搜网回复过程中搜网定时器超时
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年4月23日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2011年7月11日
   作    者   : sunxibo 46746
   修改内容   : V7R1 phase II,autoplmnsrch状态机调整为PlmnSelection状态机
 3.日    期   : 2011年12月15日
   作    者   : W00166186
   修改内容   : dts2011111502641,L下PLMN加入禁止TA后不再搜网
 4.日    期   : 2011年12月14日
   作    者   : w00176964
   修改内容   : V7R1 phaseIV 调整:驻留标记通过新的搜网控制上下文代替
 5.日    期   : 2012年06月02日
   作    者   : sunxibo /46746
   修改内容   : Added for V7R1 C50 CS/PS mode 1
 6.日    期   : 2012年8月10日
   作    者   : L00171473
   修改内容   : DTS2012082204471, TQE清理
 7.日    期   : 2012年11月05日
   作    者   : w00176964
   修改内容   : DTS2011082405001:更新网络覆盖类型
 8.日    期   : 2013年8月27日
   作    者   : l00208543
   修改内容   : Coverity
 9.日    期   : 2014年6月6日
   作    者   : b00269685
   修改内容   : 定时器超时后，先通知GAS停止搜网
 10.日    期   : 2014年11月8日
    作    者   : z00161729
    修改内容   : 开机搜网优化项目修改
 11.日    期   : 2015年5月26日
    作    者   : w00167002
    修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0项目修改
*****************************************************************************/

VOS_VOID NAS_MMC_RcvTiWaitSpecPlmnSearchCnfExpired_PlmnSelection_WaitGasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    stPlmnSearchInfo;


    PS_MEM_SET(&stPlmnSearchInfo, 0x00, sizeof(stPlmnSearchInfo));


    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitGasPlmnSearchCnfExpired_PlmnSelection_WaitGasPlmnSearchCnf: Timer Expired");

    /* 设置当前网络已经进行全频搜网 */
    NAS_MMC_SetAllBandSearch_PlmnSelection(NAS_MML_NET_RAT_TYPE_GSM, VOS_TRUE);

    /* 设置当前网络无覆盖 */
    NAS_MMC_SetRatCoverage_PlmnSelection(NAS_MML_NET_RAT_TYPE_GSM, NAS_MMC_COVERAGE_TYPE_NONE);

    /* 设置当前接入技术没有搜索到任何网络 */
    stPlmnSearchInfo.ulHighPlmnNum = 0x0;
    stPlmnSearchInfo.ulLowPlmnNum  = 0x0;
    stPlmnSearchInfo.enRatType     = NAS_MML_NET_RAT_TYPE_GSM;

    /* 根据消息中携带的搜网信息更新搜网列表 */
    NAS_MMC_UpdatePlmnSearchList_PlmnSelection(&stPlmnSearchInfo,
                                               NAS_MMC_IsNeedSortAvailablePlmnSelectionList_PlmnSelection(),
                                               VOS_TRUE);

    NAS_MMC_SndAsPlmnSrchStopReq(UEPS_PID_GAS);

    NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_PLMN_STOP_CNF);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF_LEN);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitGasHistoryPlmnSearchCnfExpired_PlmnSelection_WaitGasPlmnSearchCnf
 功能描述  : 等待GAS历史频点搜网回复过程中搜网定时器超时
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年5月26日
   作    者   : w00167002
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0项目新生成函数

*****************************************************************************/

VOS_VOID NAS_MMC_RcvTiWaitHistoryPlmnSearchCnfExpired_PlmnSelection_WaitGasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitGasHistoryPlmnSearchCnfExpired_PlmnSelection_WaitGasPlmnSearchCnf: Timer Expired");

    /* 更新当前UTRAN已完成HISTORY搜索 */
    NAS_MMC_SetHistorySearchedFlag_PlmnSelection(NAS_MML_NET_RAT_TYPE_GSM, VOS_TRUE);

    NAS_MMC_SndAsPlmnSrchStopReq(UEPS_PID_GAS);

    NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_PLMN_STOP_CNF);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF_LEN);

    return;
}




/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitGasPlmnSearchCnfExpired_PlmnSelection_WaitGasPlmnSearchCnf
 功能描述  : 等待GAS搜网回复过程中搜网定时器超时
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年4月23日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2011年7月11日
   作    者   : sunxibo 46746
   修改内容   : V7R1 phase II,autoplmnsrch状态机调整为PlmnSelection状态机
 3.日    期   : 2011年12月15日
   作    者   : W00166186
   修改内容   : dts2011111502641,L下PLMN加入禁止TA后不再搜网
 4.日    期   : 2011年12月14日
   作    者   : w00176964
   修改内容   : V7R1 phaseIV 调整:驻留标记通过新的搜网控制上下文代替
 5.日    期   : 2012年06月02日
   作    者   : sunxibo /46746
   修改内容   : Added for V7R1 C50 CS/PS mode 1
 6.日    期   : 2012年8月10日
   作    者   : L00171473
   修改内容   : DTS2012082204471, TQE清理
 7.日    期   : 2012年11月05日
   作    者   : w00176964
   修改内容   : DTS2011082405001:更新网络覆盖类型
 8.日    期   : 2013年8月27日
   作    者   : l00208543
   修改内容   : Coverity
 9.日    期   : 2014年6月6日
   作    者   : b00269685
   修改内容   : 定时器超时后，先通知GAS停止搜网
 10.日    期   : 2014年11月8日
    作    者   : z00161729
    修改内容   : 开机搜网优化项目修改
 11.日    期   : 2015年5月26日
    作    者   : w00167002
    修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0项目修改,增加对HISTORY搜网的处理
 12.日    期   : 2015年10月28日
    作    者   : s00217060
    修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0:增加pref band搜的处理
*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvTiWaitGasPlmnSearchCnfExpired_PlmnSelection_WaitGasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRC_PLMN_SEARCH_TYPE_ENUM_UINT32    enCurrSearchingPlmnType;                /* 用于区别指定搜，history搜 */

    enCurrSearchingPlmnType = NAS_MMC_GetCurrSearchingType_PlmnSelection();

    switch (enCurrSearchingPlmnType)
    {
        case NAS_MMC_PLMN_SEARCH_TYPE_SPEC:
            NAS_MMC_RcvTiWaitSpecPlmnSearchCnfExpired_PlmnSelection_WaitGasPlmnSearchCnf(ulEventType, pstMsg);
            break;

        case NAS_MMC_PLMN_SEARCH_TYPE_HISTORY:
            NAS_MMC_RcvTiWaitHistoryPlmnSearchCnfExpired_PlmnSelection_WaitGasPlmnSearchCnf(ulEventType, pstMsg);
            break;

        case NAS_MMC_PLMN_SEARCH_TYPE_PREFBAND:
            NAS_MMC_RcvTiWaitSpecPlmnSearchCnfExpired_PlmnSelection_WaitGasPlmnSearchCnf(ulEventType, pstMsg);
            break;

        default:
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitGasPlmnSearchCnfExpired_PlmnSelection_WaitGasPlmnSearchCnf UNEXPECTED SEARCH TYPE!!!");
            NAS_MMC_RcvTiWaitSpecPlmnSearchCnfExpired_PlmnSelection_WaitGasPlmnSearchCnf(ulEventType, pstMsg);
            break;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitAsSuspendCnf
 功能描述  : suspend CNF过程中当前状态机退出
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年4月23日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2011年7月11日
   作    者   : sunxibo 46746
   修改内容   : V7R1 phase II,autoplmnsrch状态机调整为PlmnSelection状态机

****************************************************************************/

VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitAsSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 记录需要终止当前状态机标志 */
    NAS_MMC_SetAbortFlag_PlmnSelection(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmSuspendCnf_PlmnSelection_WaitWasSuspendCnf
 功能描述  : 收到AS的suspend cnf消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年4月23日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2011年7月11日
   作    者   : sunxibo 46746
   修改内容   : V7R1 phase II,autoplmnsrch状态机调整为PlmnSelection状态机
 3.日    期   : 2011年12月15日
   作    者   : w00167002
   修改内容   : DTS2011120702166:MMC复位后无复位信息,在MML模块封装复位信息，
                  以供MM层调用，进行软复位。
 4.日    期   : 2011年12月14日
   作    者   : w00176964
   修改内容   : V7R1 phaseIV 调整:驻留标记通过新的搜网控制上下文代替
 5.日    期   : 2012年06月02日
   作    者   : sunxibo /46746
   修改内容   : Added for V7R1 C50 CS/PS mode 1
 6.日    期   : 2013年8月27日
   作    者   : l00208543
   修改内容   : Coverity
 7.日    期   : 2014年2月18日
   作    者  :  w00242748
   修改内容  :  DTS2014021803515:复位时明确是收到哪个接入技术的异常消息导致的。
 8.日    期   : 2014年6月23日
   作    者  :  b00269685
   修改内容  :  DSDS III开发
 9.日    期   : 2015年3月11日
   作    者   : wx270776
   修改内容   : DTS2015011212939:增加复位场景
*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvRrMmSuspendCnf_PlmnSelection_WaitWasSuspendCnf(
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

    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        NAS_MMC_UpdateRfAvailFlgPlmnSrchAborted_PlmnSelection();

        /* 设置当前接入技术为BUTT */
        NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

        /* 回复Plmn Selection执行结果 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 搜网失败后更新RF可用标记 */
    NAS_MMC_UpdateRfAvailFlgPlmnSrchFail_PlmnSelection();

    /* 获取需要搜索的网络及其接入技术 */
    if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        /* 根据获取的接入技术设置当前接入技术 */
        NAS_MML_SetCurrNetRatType(stDestPlmn.enRat);

        /* 向接入层或LMM发送搜网请求，根据不同的搜网模式，迁移到不同的L2状态，并启动保护定时器 */
        NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
    }
    else
    {
        /* Error级别打印 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvRrMmSuspendCnf_PlmnSelection_WaitWasSuspendCnf: Get next search plmn fail.");

        NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmSuspendCnf_PlmnSelection_WaitGasSuspendCnf
 功能描述  : 收到GAS的suspend cnf消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年4月23日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2011年7月11日
   作    者   : sunxibo 46746
   修改内容   : V7R1 phase II,autoplmnsrch状态机调整为PlmnSelection状态机
 3.日    期   : 2011年12月15日
   作    者   : w00167002
   修改内容   : DTS2011120702166:MMC复位后无复位信息,在MML模块封装复位信息，
                 以供MM层调用，进行软复位。
 4.日    期   : 2011年12月14日
   作    者   : w00176964
   修改内容   : V7R1 phaseIV 调整:驻留标记通过新的搜网控制上下文代替
 5.日    期   : 2012年06月02日
   作    者   : sunxibo /46746
   修改内容   : Added for V7R1 C50 CS/PS mode 1
 6.日    期   : 2013年8月27日
   作    者   : l00208543
   修改内容   : Coverity
 7.日    期   : 2014年6月23日
   作    者  :  b00269685
   修改内容  :  DSDS III开发
 8.日    期   : 2015年3月11日
   作    者   : wx270776
   修改内容   : DTS2015011212939:增加复位场景
*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvRrMmSuspendCnf_PlmnSelection_WaitGasSuspendCnf(
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

    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        NAS_MMC_UpdateRfAvailFlgPlmnSrchAborted_PlmnSelection();

        /* 设置当前接入技术为BUTT */
        NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

        /* 发送搜网结果,原因为退出状态机 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 搜网失败后更新RF可用标记 */
    NAS_MMC_UpdateRfAvailFlgPlmnSrchFail_PlmnSelection();

    /* 获取需要搜索的网络及其接入技术 */
    if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        /* 根据获取的接入技术设置当前接入技术 */
        NAS_MML_SetCurrNetRatType(stDestPlmn.enRat);

        /* 向接入层或LMM发送搜网请求，根据不同的搜网模式，迁移到不同的L2状态，并启动保护定时器 */
        NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
    }
    else
    {
        /* Error级别打印 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvRrMmSuspendCnf_PlmnSelection_WaitGasSuspendCnf: Get next search plmn fail.");

        NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitAsSuspendCnfExpired_PlmnSelection_WaitAsSuspendCnf
 功能描述  : suspend CNF过程中保护定时器超时
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年4月23日
   作    者   : w00176964
   修改内容   : 新生成函数

 2.日    期   : 2011年12月15日
   作    者   : w00167002
   修改内容   : DTS2011120702166:MMC复位后无复位信息,在MML模块封装复位信息，
                 以供MM层调用，进行软复位。
 3.日    期   : 2014年2月18日
   作    者  :  w00242748
   修改内容  :  DTS2014021803515:复位时明确是收到哪个接入技术的异常消息导致的。

 4.日    期   : 2015年3月11日
   作    者   : wx270776
   修改内容   : DTS2015011212939:增加复位场景
****************************************************************************/

VOS_UINT32 NAS_MMC_RcvTiWaitAsSuspendCnfExpired_PlmnSelection_WaitAsSuspendCnf(
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
    else if ( NAS_MML_NET_RAT_TYPE_LTE == enCurRat)
    {
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_LMM_SUSPEND_CNF_EXPIRED);
    }
    else
    {
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_TD_SUSPEND_CNF_EXPIRED);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmPlmnSearchStopCnf_PlmnSelection_WaitWasPlmnStopCnf
 功能描述  : 收到WAS的plmn search stop cnf消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年4月23日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2011年7月11日
   作    者   : sunxibo 46746
   修改内容   : V7R1 phase II,autoplmnsrch状态机调整为PlmnSelection状态机
 3.日    期   : 2011年12月14日
   作    者   : w00176964
   修改内容   : V7R1 phaseIV 调整:驻留标记通过新的搜网控制上下文代替
 4.日    期   : 2014年6月6日
   作    者   : b00269685
   修改内容   : 若是因为搜网定时器超时而发送的stop request，则需要启动搜网
 5.日    期   : 2014年6月21日
   作    者   : b00269685
   修改内容   : DSDS III项目

*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvRrMmPlmnSearchStopCnf_PlmnSelection_WaitWasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_PLMN_WITH_RAT_STRU                              stDestPlmn;

    /* 解决版本Coverity问题 */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    NAS_MMC_StopTimer( TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF );

    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        NAS_MMC_UpdateRfAvailFlgPlmnSrchAborted_PlmnSelection();

        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 搜网失败后更新RF可用标记 */
    NAS_MMC_UpdateRfAvailFlgPlmnSrchFail_PlmnSelection();

    /* 当还存在下一个需要搜索的网络时，继续进行搜网，否则，进入限制驻留 */
    if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        if (NAS_MML_NET_RAT_TYPE_WCDMA == stDestPlmn.enRat)
        {
            /* 向W接入层发送搜网请求，迁移到相应的L2状态，并启动保护定时器 */
            NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
        }
        else
        {
            /* 向W接入层发送挂起请求，迁移到相应的L2状态，并启动保护定时器 */
            NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA);
        }
    }
    else
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmRelInd_PlmnSelection_WaitWasPlmnStopCnf
 功能描述  : 收到WAS的RRMM_REL_IND消息的处理
 输入参数  : pMsg        - RRMM_REL_IND消息首地址
             ulEventType - 事件类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年11月28日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   : 2011年12月14日
   作    者   : w00176964
   修改内容   : V7R1 phaseIV 调整:驻留标记通过新的搜网控制上下文代替
 3.日    期   : 2012年6月18日
   作    者   : l00171473
   修改内容   : DTS2012051104124,WAS:接收到RRMM_PLMN_SEARCH_STOP_REQ时，
                可能发送有异常原因的rel ind或者RRMM_PLMN_SEARCH_STOP_CNF.
                收到rel ind认为停止搜网结束
 4.日    期   : 2014年6月23日
   作    者   : b00269685
   修改内容   : DSDS III项目开发
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvRrMmRelInd_PlmnSelection_WaitWasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 无需判断原因值 */

    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvRrMmRelInd_PlmnSelection_WaitWasPlmnStopCnf: ENTERED");

    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF);

    NAS_MMC_UpdateRfAvailFlgPlmnSrchAborted_PlmnSelection();

    NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}
/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmPlmnSearchStopCnf_PlmnSelection_WaitGasPlmnStopCnf
 功能描述  : 收到GAS的plmn search stop cnf消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年4月23日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2011年7月11日
   作    者   : sunxibo 46746
   修改内容   : V7R1 phase II,autoplmnsrch状态机调整为PlmnSelection状态机
 3.日    期   : 2011年12月14日
   作    者   : w00176964
   修改内容   : V7R1 phaseIV 调整:驻留标记通过新的搜网控制上下文代替
 4.日    期   : 2014年6月6日
   作    者   : b00269685
   修改内容   : 若是因为搜网定时器超时而发送的stop request，则需要启动搜网
 5.日    期   : 2014年6月23日
   作    者   : y00245242
   修改内容   : dts2014061701038修改
 6.日    期   : 2014年6月21日
   作    者   : b00269685
   修改内容   : DSDS III项目
*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvRrMmPlmnSearchStopCnf_PlmnSelection_WaitGasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_PLMN_WITH_RAT_STRU                              stDestPlmn;

    /* 解决版本Coverity问题 */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    NAS_MMC_StopTimer( TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF );

    /* 有打断时，退出状态机 */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        NAS_MMC_UpdateRfAvailFlgPlmnSrchAborted_PlmnSelection();

        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 搜网失败后更新RF可用标记 */
    NAS_MMC_UpdateRfAvailFlgPlmnSrchFail_PlmnSelection();

    /* 当还存在下一个需要搜索的网络时，继续进行搜网，否则，进入限制驻留 */
    if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        if (NAS_MML_NET_RAT_TYPE_GSM == stDestPlmn.enRat)
        {
            /* 向G接入层发送搜网请求，迁移到相应的L2状态，并启动保护定时器 */
            NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
        }
        else
        {
            /* 向G接入层发送挂起请求，迁移到相应的L2状态，并启动保护定时器 */
            NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_NET_RAT_TYPE_GSM);
        }
    }
    else
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();
    }


    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitWasStopCnfExpired_PlmnSelection_WaitWasPlmnStopCnf
 功能描述  : Was的plmn search stop CNF过程中保护定时器超时
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年4月23日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2011年7月11日
   作    者   : sunxibo 46746
   修改内容   : V7R1 phase II,autoplmnsrch状态机调整为PlmnSelection状态机
 3.日    期   : 2011年12月14日
   作    者   : w00176964
   修改内容   : V7R1 phaseIV 调整:驻留标记通过新的搜网控制上下文代替
 4.日    期   : 2014年6月6日
   作    者   : b00269685
   修改内容   : 若是因为搜网定时器超时而发送的stop request，则需要启动搜网
 5.日    期   : 2014年6月21日
   作    者   : b00269685
   修改内容   : DSDS III项目

****************************************************************************/

VOS_UINT32 NAS_MMC_RcvTiWaitWasStopCnfExpired_PlmnSelection_WaitWasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_PLMN_WITH_RAT_STRU                              stDestPlmn;

    /* 解决版本Coverity问题 */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitWasStopCnfExpired_PlmnSelection_WaitWasPlmnStopCnf: Timer Expired");

    /* 有打断时，退出状态机 */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        NAS_MMC_UpdateRfAvailFlgPlmnSrchAborted_PlmnSelection();

        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 搜网失败后更新RF可用标记 */
    NAS_MMC_UpdateRfAvailFlgPlmnSrchFail_PlmnSelection();

    /* 当还存在下一个需要搜索的网络时，继续进行搜网，否则，进入限制驻留 */
    if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        if (NAS_MML_NET_RAT_TYPE_WCDMA == stDestPlmn.enRat)
        {
            /* 向W接入层发送搜网请求，迁移到相应的L2状态，并启动保护定时器 */
            NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
        }
        else
        {
            /* 向W接入层发送挂起请求，迁移到相应的L2状态，并启动保护定时器 */
            NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA);
        }
    }
    else
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitGasStopCnfExpired_PlmnSelection_WaitGasPlmnStopCnf
 功能描述  : Gas的plmn search stop CNF过程中保护定时器超时
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年4月23日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2011年7月11日
   作    者   : sunxibo 46746
   修改内容   : V7R1 phase II,autoplmnsrch状态机调整为PlmnSelection状态机
 3.日    期   : 2011年12月14日
   作    者   : w00176964
   修改内容   : V7R1 phaseIV 调整:驻留标记通过新的搜网控制上下文代替
 4.日    期   : 2014年6月6日
   作    者   : b00269685
   修改内容   : 若是因为搜网定时器超时而发送的stop request，则需要启动搜网
 5.日    期   : 2014年6月23日
   作    者   : y00245242
   修改内容   : dts2014061701038修改
 6.日    期   : 2014年6月21日
   作    者   : b00269685
   修改内容   : DSDS III项目
****************************************************************************/

VOS_UINT32 NAS_MMC_RcvTiWaitGasStopCnfExpired_PlmnSelection_WaitGasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_PLMN_WITH_RAT_STRU                              stDestPlmn;

    /* 解决版本Coverity问题 */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitGasStopCnfExpired_PlmnSelection_WaitGasPlmnStopCnf: Timer Expired");

    /* 有打断时，退出状态机 */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        NAS_MMC_UpdateRfAvailFlgPlmnSrchAborted_PlmnSelection();

        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 搜网失败后更新RF可用标记 */
    NAS_MMC_UpdateRfAvailFlgPlmnSrchFail_PlmnSelection();

    /* 当还存在下一个需要搜索的网络时，继续进行搜网，否则，进入限制驻留 */
    if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        if (NAS_MML_NET_RAT_TYPE_GSM == stDestPlmn.enRat)
        {
            /* 向G接入层发送搜网请求，迁移到相应的L2状态，并启动保护定时器 */
            NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
        }
        else
        {
            /* 向G接入层发送挂起请求，迁移到相应的L2状态，并启动保护定时器 */
            NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_NET_RAT_TYPE_GSM);
        }
    }
    else
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmSpecPlmnSearchCnf_PlmnSelection_WaitWasPlmnStopCnf
 功能描述  : 收到WAS的spec plmn search cnf消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年6月03日
   作    者   : w00167002
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0项目修改
*****************************************************************************/

VOS_VOID NAS_MMC_RcvRrMmSpecPlmnSearchCnf_PlmnSelection_WaitWasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU                              *pstSrchCnfMsg = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stDestPlmn;

    pstSrchCnfMsg = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;

    /* 解决版本Coverity问题 */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    NAS_MMC_StopTimer( TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF );

    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        NAS_MMC_UpdateRfAvailFlgPlmnSrchAborted_PlmnSelection();

        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* 如果当前为NO RF，则直接退状态机 */
    if (RRC_PLMN_SEARCH_RLT_SPEC_NO_RF == pstSrchCnfMsg->ulSearchRlt)
    {
        NAS_MMC_ProcNoRf_PlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA);

        return;
    }

    /* 搜网失败后更新RF可用标记 */
    NAS_MMC_UpdateRfAvailFlgPlmnSrchFail_PlmnSelection();

    /* 当还存在下一个需要搜索的网络时，继续进行搜网，否则，进入限制驻留 */
    if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        if (NAS_MML_NET_RAT_TYPE_WCDMA == stDestPlmn.enRat)
        {
            /* 向W接入层发送搜网请求，迁移到相应的L2状态，并启动保护定时器 */
            NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
        }
        else
        {
            /* 向W接入层发送挂起请求，迁移到相应的L2状态，并启动保护定时器 */
            NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA);
        }
    }
    else
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmHistoryPlmnSearchCnf_PlmnSelection_WaitWasPlmnStopCnf
 功能描述  : 收到WAS的history plmn search cnf消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年6月03日
   作    者   : w00167002
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0项目修改
*****************************************************************************/

VOS_VOID NAS_MMC_RcvRrMmHistoryPlmnSearchCnf_PlmnSelection_WaitWasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU                              *pstSrchCnfMsg = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stDestPlmn;

    pstSrchCnfMsg = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;

    /* 解决版本Coverity问题 */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    NAS_MMC_StopTimer( TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF );

    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        NAS_MMC_UpdateRfAvailFlgPlmnSrchAborted_PlmnSelection();

        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* 如果当前为NO RF，则直接退状态机 */
    if (RRC_PLMN_SEARCH_RLT_HISTORY_NO_RF == pstSrchCnfMsg->ulSearchRlt)
    {
        NAS_MMC_ProcNoRf_PlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA);

        return;
    }

    /* 搜网失败后更新RF可用标记 */
    NAS_MMC_UpdateRfAvailFlgPlmnSrchFail_PlmnSelection();

    /* 当还存在下一个需要搜索的网络时，继续进行搜网，否则，进入限制驻留 */
    if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        if (NAS_MML_NET_RAT_TYPE_WCDMA == stDestPlmn.enRat)
        {
            /* 向W接入层发送搜网请求，迁移到相应的L2状态，并启动保护定时器 */
            NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
        }
        else
        {
            /* 向W接入层发送挂起请求，迁移到相应的L2状态，并启动保护定时器 */
            NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA);
        }
    }
    else
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmPrefBandPlmnSearchCnf_PlmnSelection_WaitWasPlmnStopCnf
 功能描述  : 收到WAS的pref band plmn search cnf消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年10月12日
   作    者   : s00217060
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_RcvRrMmPrefBandPlmnSearchCnf_PlmnSelection_WaitWasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU                              *pstSrchCnfMsg = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stDestPlmn;

    pstSrchCnfMsg = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;

    /* 解决版本Coverity问题 */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    NAS_MMC_StopTimer( TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF );

    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        NAS_MMC_UpdateRfAvailFlgPlmnSrchAborted_PlmnSelection();

        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* 如果当前为NO RF，则直接退状态机 */
    if (RRC_PLMN_SEARCH_RLT_PREF_BAND_NO_RF == pstSrchCnfMsg->ulSearchRlt)
    {
        NAS_MMC_ProcNoRf_PlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA);

        return;
    }

    /* 搜网失败后更新RF可用标记 */
    NAS_MMC_UpdateRfAvailFlgPlmnSrchFail_PlmnSelection();

    /* 当还存在下一个需要搜索的网络时，继续进行搜网，否则，进入限制驻留 */
    if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        if (NAS_MML_NET_RAT_TYPE_WCDMA == stDestPlmn.enRat)
        {
            /* 向W接入层发送搜网请求，迁移到相应的L2状态，并启动保护定时器 */
            NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
        }
        else
        {
            /* 向W接入层发送挂起请求，迁移到相应的L2状态，并启动保护定时器 */
            NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA);
        }
    }
    else
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmPlmnSearchCnf_PlmnSelection_WaitWasPlmnStopCnf
 功能描述  : 收到WAS的plmn search cnf消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年6月25日
   作    者   : b00269685
   修改内容   : DSDS III项目新增

 2.日    期   : 2015年6月3日
   作    者   : w00167002
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0项目修改
*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvRrMmPlmnSearchCnf_PlmnSelection_WaitWasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU                              *pstSrchCnfMsg = VOS_NULL_PTR;

    pstSrchCnfMsg = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;

    switch ( pstSrchCnfMsg->ulSearchRlt )
    {
        /* 全频段指定搜结果的处理 */
        case RRC_PLMN_SEARCH_RLT_SPEC:
        case RRC_PLMN_SEARCH_RLT_SPEC_NO_RF:
        case RRC_PLMN_SEARCH_RLT_SPEC_FAIL:
            NAS_MMC_RcvRrMmSpecPlmnSearchCnf_PlmnSelection_WaitWasPlmnStopCnf(ulEventType, pstMsg);
            break;

        /* 历史频点指定搜结果的处理 */
        case RRC_PLMN_SEARCH_RLT_HISTORY_SUCC:
        case RRC_PLMN_SEARCH_RLT_HISTORY_NO_RF:
        case RRC_PLMN_SEARCH_RLT_HISTORY_FAIL:
            NAS_MMC_RcvRrMmHistoryPlmnSearchCnf_PlmnSelection_WaitWasPlmnStopCnf(ulEventType, pstMsg);
            break;

         /* pref band搜结果的处理 */
         case RRC_PLMN_SEARCH_RLT_PREF_BAND_SUCC:
         case RRC_PLMN_SEARCH_RLT_PREF_BAND_NO_RF:
         case RRC_PLMN_SEARCH_RLT_PREF_BAND_FAIL:
             NAS_MMC_RcvRrMmPrefBandPlmnSearchCnf_PlmnSelection_WaitWasPlmnStopCnf(ulEventType, pstMsg);
             break;

        default:
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvRrMmPlmnSrchCnf_PlmnSelection_WaitWasPlmnSearchCnf:UNEXPECTED SEARCH RSLT!!!");
            NAS_MMC_RcvRrMmSpecPlmnSearchCnf_PlmnSelection_WaitWasPlmnStopCnf(ulEventType, pstMsg);
            break;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmSpecPlmnSearchCnf_PlmnSelection_WaitGasPlmnStopCnf
 功能描述  : 收到GAS的spec plmn search cnf消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年6月3日
   作    者   : w00167002
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0项目修改

*****************************************************************************/

VOS_VOID NAS_MMC_RcvRrMmSpecPlmnSearchCnf_PlmnSelection_WaitGasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU                              *pstSrchCnfMsg = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stDestPlmn;

    pstSrchCnfMsg = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;

    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    NAS_MMC_StopTimer( TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF );

    /* 有打断时，退出状态机 */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        NAS_MMC_UpdateRfAvailFlgPlmnSrchAborted_PlmnSelection();

        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* 如果当前为NO RF，则直接退状态机 */
    if (RRC_PLMN_SEARCH_RLT_SPEC_NO_RF == pstSrchCnfMsg->ulSearchRlt)
    {
        NAS_MMC_ProcNoRf_PlmnSelection(NAS_MML_NET_RAT_TYPE_GSM);

        return;
    }

    /* 搜网失败后更新RF可用标记 */
    NAS_MMC_UpdateRfAvailFlgPlmnSrchFail_PlmnSelection();

    /* 当还存在下一个需要搜索的网络时，继续进行搜网，否则，进入限制驻留 */
    if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        if (NAS_MML_NET_RAT_TYPE_GSM == stDestPlmn.enRat)
        {
            /* 向G接入层发送搜网请求，迁移到相应的L2状态，并启动保护定时器 */
            NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
        }
        else
        {
            /* 向G接入层发送挂起请求，迁移到相应的L2状态，并启动保护定时器 */
            NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_NET_RAT_TYPE_GSM);
        }
    }
    else
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_SUCCESS,
                VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmHistoryPlmnSearchCnf_PlmnSelection_WaitGasPlmnStopCnf
 功能描述  : 收到GAS的history plmn search cnf消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年6月3日
   作    者   : w00167002
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0项目修改

*****************************************************************************/

VOS_VOID NAS_MMC_RcvRrMmHistoryPlmnSearchCnf_PlmnSelection_WaitGasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU                              *pstSrchCnfMsg = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stDestPlmn;

    pstSrchCnfMsg = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;

    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    NAS_MMC_StopTimer( TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF );

    /* 有打断时，退出状态机 */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        NAS_MMC_UpdateRfAvailFlgPlmnSrchAborted_PlmnSelection();

        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* 如果当前为NO RF，则直接退状态机 */
    if (RRC_PLMN_SEARCH_RLT_HISTORY_NO_RF == pstSrchCnfMsg->ulSearchRlt)
    {
        NAS_MMC_ProcNoRf_PlmnSelection(NAS_MML_NET_RAT_TYPE_GSM);

        return;
    }

    /* 搜网失败后更新RF可用标记 */
    NAS_MMC_UpdateRfAvailFlgPlmnSrchFail_PlmnSelection();

    /* 当还存在下一个需要搜索的网络时，继续进行搜网，否则，进入限制驻留 */
    if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        if (NAS_MML_NET_RAT_TYPE_GSM == stDestPlmn.enRat)
        {
            /* 向G接入层发送搜网请求，迁移到相应的L2状态，并启动保护定时器 */
            NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
        }
        else
        {
            /* 向G接入层发送挂起请求，迁移到相应的L2状态，并启动保护定时器 */
            NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_NET_RAT_TYPE_GSM);
        }
    }
    else
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_SUCCESS,
                VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmPrefBandPlmnSearchCnf_PlmnSelection_WaitGasPlmnStopCnf
 功能描述  : 收到GAS的pref band plmn search cnf消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年6月3日
   作    者   : w00167002
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0项目修改

*****************************************************************************/
VOS_VOID NAS_MMC_RcvRrMmPrefBandPlmnSearchCnf_PlmnSelection_WaitGasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU                              *pstSrchCnfMsg = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stDestPlmn;

    pstSrchCnfMsg = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;

    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    NAS_MMC_StopTimer( TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF );

    /* 有打断时，退出状态机 */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        NAS_MMC_UpdateRfAvailFlgPlmnSrchAborted_PlmnSelection();

        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* 如果当前为NO RF，则直接退状态机 */
    if (RRC_PLMN_SEARCH_RLT_PREF_BAND_NO_RF == pstSrchCnfMsg->ulSearchRlt)
    {
        NAS_MMC_ProcNoRf_PlmnSelection(NAS_MML_NET_RAT_TYPE_GSM);

        return;
    }

    /* 搜网失败后更新RF可用标记 */
    NAS_MMC_UpdateRfAvailFlgPlmnSrchFail_PlmnSelection();

    /* 当还存在下一个需要搜索的网络时，继续进行搜网，否则，进入限制驻留 */
    if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        if (NAS_MML_NET_RAT_TYPE_GSM == stDestPlmn.enRat)
        {
            /* 向G接入层发送搜网请求，迁移到相应的L2状态，并启动保护定时器 */
            NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
        }
        else
        {
            /* 向G接入层发送挂起请求，迁移到相应的L2状态，并启动保护定时器 */
            NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_NET_RAT_TYPE_GSM);
        }
    }
    else
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_SUCCESS,
                VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmPlmnSearchCnf_PlmnSelection_WaitGasPlmnStopCnf
 功能描述  : 收到GAS的plmn search cnf消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年6月25日
   作    者   : b00269685
   修改内容   : DSDS III项目新增

*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvRrMmPlmnSearchCnf_PlmnSelection_WaitGasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU                              *pstSrchCnfMsg = VOS_NULL_PTR;

    pstSrchCnfMsg = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;

    switch ( pstSrchCnfMsg->ulSearchRlt )
    {
        /* 全频段指定搜结果的处理 */
        case RRC_PLMN_SEARCH_RLT_SPEC:
        case RRC_PLMN_SEARCH_RLT_SPEC_NO_RF:
        case RRC_PLMN_SEARCH_RLT_SPEC_FAIL:
            NAS_MMC_RcvRrMmSpecPlmnSearchCnf_PlmnSelection_WaitGasPlmnStopCnf(ulEventType, pstMsg);
            break;

        /* 历史频点指定搜结果的处理 */
        case RRC_PLMN_SEARCH_RLT_HISTORY_SUCC:
        case RRC_PLMN_SEARCH_RLT_HISTORY_NO_RF:
        case RRC_PLMN_SEARCH_RLT_HISTORY_FAIL:
            NAS_MMC_RcvRrMmHistoryPlmnSearchCnf_PlmnSelection_WaitGasPlmnStopCnf(ulEventType, pstMsg);
            break;

        /* pref band搜结果的处理 */
        case RRC_PLMN_SEARCH_RLT_PREF_BAND_SUCC:
        case RRC_PLMN_SEARCH_RLT_PREF_BAND_NO_RF:
        case RRC_PLMN_SEARCH_RLT_PREF_BAND_FAIL:
            NAS_MMC_RcvRrMmPrefBandPlmnSearchCnf_PlmnSelection_WaitGasPlmnStopCnf(ulEventType, pstMsg);
            break;

        default:
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvRrMmPlmnSearchCnf_PlmnSelection_WaitGasPlmnStopCnf:UNEXPECTED SEARCH RSLT!!!");
            NAS_MMC_RcvRrMmSpecPlmnSearchCnf_PlmnSelection_WaitGasPlmnStopCnf(ulEventType, pstMsg);
            break;
    }

    return VOS_TRUE;
}

/************************ 注册部分*************************************/

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitWasSysInfoInd
 功能描述  : MMC处理QUIT的系统消息
 输入参数  : ulEventType:消息类型
             pstMsg:QUIT消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE 消息处理成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月12日
    作    者   : l00130025
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitWasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    NAS_MMC_SetAbortFlag_PlmnSelection(VOS_TRUE);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitGasSysInfoInd
 功能描述  : MMC处理QUIT的系统消息
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE 消息处理成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月12日
    作    者   : l00130025
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitGasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    NAS_MMC_SetAbortFlag_PlmnSelection(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvSysInfoInd_PlmnSelection_WaitWasSysInfoInd
 功能描述  : 处理WAS系统消息,
             1)记录MML的全部变量 2)向MM/GMM转发系统消息通知 3)更新当前网络的搜索状态
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:状态机处理成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月20日
    作    者   : z40661 / 40661
    修改内容   : 新生成函数
  2.日    期   : 2011年7月11日
    作    者   : l00130025
    修改内容   : PhaseII修改
  3.日    期   : 2011年10月6日
    作    者   : w00167002
    修改内容   : PhaseII修改:删除更改当前的网络的注册状态为REGISTERED，
                  统一等注册结果后，才更改为REGISTERED
  4.日    期   : 2011年12月14日
    作    者   : w00176964
    修改内容   : V7R1 phaseIV 调整:驻留标记通过新的搜网控制上下文代替
  5.日    期   : 2012年3月17日
    作    者   : w00176964
    修改内容   : DTS2012031900095 V7R1 C30 SBM&EM定制需求:增加LTE国家漫游功能定制
  6.日    期   : 2012年6月16日
    作    者   : l00171473
    修改内容   : DTS2012061409086, 收到W或G的系统消息时通知L模
  7.日    期   : 2012年7月27日
    作    者   : s00217060
    修改内容   : for CS/PS mode 1,带Disable LTE原因值
  8 .日    期   : 2012年8月13日
     作    者   : z00161729
     修改内容   : DCM定制需求和遗留问题修改
  9.日    期   : 2012年12月11日
    作    者   : w00176964
    修改内容   : 收到系统消息接入禁止信息变化则通知MMA
  10.日    期   : 2012年12月11日
    作    者   : l00167671
    修改内容   : DTS2012121802573, TQE清理
 11.日    期   : 2013年9月14日
    作    者   : w00167002
    修改内容   : DTS2013090908249:开机用户指定搜网24003，CS注册被拒15，MM在LIMIT
                 状态，在选网状态机收到同一小区的SYSINFO后，通知MM当前没有FORB FLG,
                 导致MM发起循环注册；
                 在NAS_MMC_SndMmGsmSysInfoInd函数中，如果是用户指定搜网，则将FORBFLG设置为null，
                 将此耦合去除；
                 在选网状态机识别出是否是用户指定搜网，并配置正确的ulForbiddenFlg标志；

12.日    期   : 2014年1月18日
   作    者   : z00234330
   修改内容   : dts2014011801513,接入层上报的系统消息里面有可能没有携带plmnid,
               此处判断并没有判断plmnid是否有效
 13.日    期   : 2014年1月23日
    作    者   : z00161729
    修改内容   : DTS2014012305088:svlte特性tds或l上系统消息后pstransfer:1，注册随机接入失败，ps迁移
                到modem1后tds或l再次驻留mmc收到系统消息判断驻留信息未改变不会给mma发送系统消息导致
                mtc无法上报pstransfer:1,需要在搜网状态机退出后给mma再发次系统消息

 14.日    期   : 2014年5月4日
    作    者   : t00173447
    修改内容   : DTS2014042105390,软银定制需求
*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvSysInfoInd_PlmnSelection_WaitWasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo           = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;
    NAS_MMC_FSM_ID_ENUM_UINT32                              enCurrentFsmId;
    VOS_UINT32                                              ulCurrentEventType;
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, begin */
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurCsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldCsRestrictInfo;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurPsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldPsRestrictInfo;
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, end */

    NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8                enSpecPlmnSearchState;
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;

    /* 获取LTE能力状态 */
    enLCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();

#endif

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    PS_MEM_SET(&stOldCsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_SET(&stOldPsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

    /* 停止等待系统消息的定时器  */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO);

    /* 状态更新为当前已经驻留 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_RcvGuSysInfoIndSetLteAbility(pstMsg,enLCapabilityStatus);
#endif

    /* 如果当前需要退出状态机 */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        /* 回复Plmn Selection执行结果 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

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

    /* 驻留小区变化或重新搜网时，上报系统消息 */
    enSpecPlmnSearchState = NAS_MMC_GetSpecPlmnSearchState();

    if ((VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
     || (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == enSpecPlmnSearchState))
    {
        /* 主动上报 */
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, begin*/
        NAS_MMC_SndMsccSysInfo();
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, end*/

    }

    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
    /* 驻留小区的接入受限信息变化时,通知MMA模块当前接入受限信息 */
    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldCsRestrictInfo, pstCurCsRestrictInfo))
    {
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, begin*/
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_CS, pstCurCsRestrictInfo);
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, end*/
    }

    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldPsRestrictInfo, pstCurPsRestrictInfo))
    {
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, begin*/
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_PS, pstCurPsRestrictInfo);
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, end*/
    }
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, end */

    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_STOP);

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))

    /* CBS上报*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_WCDMA);
#endif

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, end */

    /* 更新当前等待CSPS的注册结果 */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnSelection();
    NAS_MMC_SetWaitRegRsltFlag_PlmnSelection(NAS_MMC_WAIT_REG_RESULT_IND_CS);
    NAS_MMC_SetWaitRegRsltFlag_PlmnSelection(NAS_MMC_WAIT_REG_RESULT_IND_PS);

    /* 更新CSPS的AdditionalAction */
    NAS_MMC_SetCsRegAdditionalAction_PlmnSelection(NAS_MMC_ADDITIONAL_ACTION_BUTT);
    NAS_MMC_SetPsRegAdditionalAction_PlmnSelection(NAS_MMC_ADDITIONAL_ACTION_BUTT);

    /* 更新CSPS的RegCause */
    NAS_MMC_SetCsRegCause_PlmnSelection(NAS_MML_REG_FAIL_CAUSE_BUTT);
    NAS_MMC_SetPsRegCause_PlmnSelection(NAS_MML_REG_FAIL_CAUSE_BUTT);

    enCurrentFsmId     = NAS_MMC_GetCurrFsmId();
    if (NAS_MMC_FSM_PLMN_SELECTION != enCurrentFsmId)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }

    ulCurrentEventType = NAS_MMC_GetCurrFsmEventType();

    if ( VOS_TRUE == NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enCurrentFsmId,ulCurrentEventType) )
    {
        /* 转发系统消息通知 给 MM/GMM */
        NAS_MMC_SndMmWasSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenTypeForUserSpecPlmnSrch(),
                                   VOS_TRUE,
                                   pstMsg);

        NAS_MMC_SndGmmWasSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenTypeForUserSpecPlmnSrch(),
                                   VOS_TRUE,
                                   pstMsg);
    }
    else
    {
        /* 转发系统消息通知 给 MM/GMM,并将当前系统消息的 Forbidden 类型携带过去 */
        NAS_MMC_SndMmWasSysInfoInd(NAS_MML_GetLaiForbType(&(pstCurCampInfo->stLai)),
                                   VOS_FALSE,
                                   pstMsg);

        NAS_MMC_SndGmmWasSysInfoInd(NAS_MML_GetLaiForbType(&(pstCurCampInfo->stLai)),
                                   VOS_FALSE,
                                   pstMsg);
    }

#if (FEATURE_ON == FEATURE_LTE)

    NAS_MMC_SndLmmWcdmaSysInfoInd(pstMsg);
#endif

    /* 收到系统消息后迁移到等待CS+PS域的注册结果并启动定时器 */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_CSPS_REG_IND);
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND, TI_NAS_MMC_WAIT_CSPS_REG_IND_LEN);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvSysInfoInd_PlmnSelection_WaitGasSysInfoInd
 功能描述  : 处理GAS系统消息
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:状态机处理成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月20日
    作    者   : z40661 / 40661
    修改内容   : 新生成函数
  2.日    期   : 2011年7月14日
    作    者   : l00130025
    修改内容   : PhaseII修改,PlmnSelection状态机调整
  3.日    期   : 2011年10月6日
    作    者   : w00167002
    修改内容   : PhaseII修改:删除更改当前的网络的注册状态为REGISTERED，
                  统一等注册结果后，才更改为REGISTERED
  4.日    期   : 2011年12月14日
    作    者   : w00176964
    修改内容   : V7R1 phaseIV 调整:驻留标记通过新的搜网控制上下文代替
  5.日    期   : 2012年6月16日
    作    者   : l00171473
    修改内容   : DTS2012061409086, 收到W或G的系统消息时通知L模
  6.日    期   : 2012年8月13日
    作    者   : t00212959
    修改内容   : DCM定制需求和遗留问题:增加LTE国家漫游功能定制
  7.日    期   : 2012年12月11日
    作    者   : w00176964
    修改内容   : 收到系统消息接入禁止信息变化则通知MMA
  8.日    期   : 2012年12月11日
    作    者   : l00167671
    修改内容   : DTS2012121802573, TQE清理
  9.日    期   : 2013年9月14日
    作    者   : w00167002
    修改内容   : DTS2013090908249:开机用户指定搜网24003，CS注册被拒15，MM在LIMIT
                 状态，在选网状态机收到同一小区的SYSINFO后，通知MM当前没有FORB FLG,
                 导致MM发起循环注册；
                 在NAS_MMC_SndMmGsmSysInfoInd函数中，如果是用户指定搜网，则将FORBFLG设置为null，
                 将此耦合去除；
                 在选网状态机识别出是否是用户指定搜网，并配置正确的ulForbiddenFlg标志；
 10.日    期   : 2013年11月01日
    作    者   : l00208543
    修改内容   : 根据卡类型禁止网络制式
 11.日    期   : 2014年1月23日
    作    者   : z00161729
    修改内容   : DTS2014012305088:svlte特性tds或l上系统消息后pstransfer:1，注册随机接入失败，ps迁移
                到modem1后tds或l再次驻留mmc收到系统消息判断驻留信息未改变不会给mma发送系统消息导致
                mtc无法上报pstransfer:1,需要在搜网状态机退出后给mma再发次系统消息

 12.日    期   : 2014年5月4日
    作    者   : t00173447
    修改内容   : DTS2014042105390,软银定制需求
*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvSysInfoInd_PlmnSelection_WaitGasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;
    NAS_MMC_FSM_ID_ENUM_UINT32                              enCurrentFsmId;
    VOS_UINT32                                              ulCurrentEventType;
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, begin */
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurCsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldCsRestrictInfo;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurPsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldPsRestrictInfo;
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, end */

    NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8                enSpecPlmnSearchState;
    /* Added by t00212959 for DCM定制需求和遗留问题, 2012-8-13, begin */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;


    /* 获取LTE能力状态 */
    enLCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();

#endif
    /* Added by t00212959 for DCM定制需求和遗留问题, 2012-8-13, end */

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    PS_MEM_SET(&stOldCsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_SET(&stOldPsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

    /* 如果收到GAS的系统消息，且目前Utran被Enable，则重新Disable Utran */
    NAS_MMC_RcvGasSysInfoSetUtranCapabilityStatus();

    /* 停止等待系统消息的定时器  */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_SYS_INFO);

    /* 状态更新为当前已经驻留 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

    /* Added by t00212959 for DCM定制需求和遗留问题, 2012-8-13, begin */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_RcvGuSysInfoIndSetLteAbility(pstMsg, enLCapabilityStatus);
#endif
    /* Added by t00212959 for DCM定制需求和遗留问题, 2012-8-13, end */

    /* 如果当前需要退出状态机 */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {

        /* 回复状态机退出成功 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

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

    /* 驻留小区变化或重新搜网时，上报系统消息 */
    enSpecPlmnSearchState = NAS_MMC_GetSpecPlmnSearchState();

    if ((VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
     || (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == enSpecPlmnSearchState))
    {
        /* 主动上报 */
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, begin*/
        NAS_MMC_SndMsccSysInfo();
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, end*/
    }

    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
    /* 驻留小区的接入受限信息变化时,通知MMA模块当前接入受限信息 */
    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldCsRestrictInfo, pstCurCsRestrictInfo))
    {
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, begin*/
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_CS, pstCurCsRestrictInfo);
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, end*/
    }

    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldPsRestrictInfo, pstCurPsRestrictInfo))
    {
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, begin*/
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_PS, pstCurPsRestrictInfo);
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, end*/
    }
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, end */

    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_STOP);

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))

    /* CBS上报*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_GSM);
#endif

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, end */

    /* 更新当前等待CSPS的注册结果 */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnSelection();
    NAS_MMC_SetWaitRegRsltFlag_PlmnSelection(NAS_MMC_WAIT_REG_RESULT_IND_CS);
    NAS_MMC_SetWaitRegRsltFlag_PlmnSelection(NAS_MMC_WAIT_REG_RESULT_IND_PS);

    /* 更新CSPS的AdditionalAction */
    NAS_MMC_SetCsRegAdditionalAction_PlmnSelection(NAS_MMC_ADDITIONAL_ACTION_BUTT);
    NAS_MMC_SetPsRegAdditionalAction_PlmnSelection(NAS_MMC_ADDITIONAL_ACTION_BUTT);

    /* 更新CSPS的RegCause */
    NAS_MMC_SetCsRegCause_PlmnSelection(NAS_MML_REG_FAIL_CAUSE_BUTT);
    NAS_MMC_SetPsRegCause_PlmnSelection(NAS_MML_REG_FAIL_CAUSE_BUTT);

    enCurrentFsmId     = NAS_MMC_GetCurrFsmId();
    if (NAS_MMC_FSM_PLMN_SELECTION != enCurrentFsmId)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }
    ulCurrentEventType = NAS_MMC_GetCurrFsmEventType();


    /* 在用户指定搜网时，不需要携带FORB类型 */
    if ( VOS_TRUE == NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enCurrentFsmId,ulCurrentEventType) )
    {
        /* 转发系统消息通知 给 MM/GMM */
        NAS_MMC_SndMmGsmSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenTypeForUserSpecPlmnSrch(),
                                   VOS_TRUE,
                                   pstMsg);

        NAS_MMC_SndGmmGsmSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenTypeForUserSpecPlmnSrch(),
                                   VOS_TRUE,
                                   pstMsg);
    }
    else
    {
        /* 转发系统消息通知 给 MM/GMM,并将当前系统消息的 Forbidden 类型携带过去 */
        NAS_MMC_SndMmGsmSysInfoInd(NAS_MML_GetLaiForbType(&(pstCurCampInfo->stLai)),
                                   VOS_FALSE,
                                   pstMsg);

        NAS_MMC_SndGmmGsmSysInfoInd(NAS_MML_GetLaiForbType(&(pstCurCampInfo->stLai)),
                                   VOS_FALSE,
                                   pstMsg);

    }

#if (FEATURE_ON == FEATURE_LTE)

    NAS_MMC_SndLmmGsmSysInfoInd(pstMsg);
#endif

    /* 收到系统消息后迁移到等待CS+PS域的注册结果并启动定时器 */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_CSPS_REG_IND);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND, TI_NAS_MMC_WAIT_CSPS_REG_IND_LEN);


    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitSysInfoExpired_PlmnSelection_WaitWasSysInfoInd
 功能描述  : 等待W系统消息超时，同丢网的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:状态机处理成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月25日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数
  2.日    期   : 2011年7月21日
    作    者   : l00130025
    修改内容   : PhaseII修改,PlmnSelection状态机调整
  3.日    期   : 2011年12月15日
    作    者   : W00166186
    修改内容   : dts2011111502641,L下PLMN加入禁止TA后不再搜网
  4.日    期   : 2011年12月14日
    作    者   : w00176964
    修改内容   : V7R1 phaseIV 调整:驻留标记通过新的搜网控制上下文代替
  5.日    期   : 2012年06月02日
    作    者   : sunxibo /46746
    修改内容   : Added for V7R1 C50 CS/PS mode 1
  6.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  7.日    期   : 2013年8月27日
    作    者   : l00208543
    修改内容   : Coverity
  8.日    期   : 2014年4月14日
    作    者   : s00261364
    修改内容   : V3R360_eCall项目:搜网时更新服务状态
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiWaitSysInfoExpired_PlmnSelection_WaitWasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_PLMN_WITH_RAT_STRU          stDestPlmn;
    VOS_UINT32                          ulResult;

	/* 解决版本Coverity问题 */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitSysInfoExpired_PlmnSelection_WaitWasSysInfoInd: Timer Expired");

    /*如果当前需要退出状态机 */
    if (VOS_TRUE  == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        /* 回复状态机退出成功 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

       /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 清除驻留状态 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* 当前信号更新 */
    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());

    /*获取下一个要搜索的网络,若获取失败，则给上层状态机上报搜网失败，退出
      若获取成功，则判断下一个要搜索的网络是否与当前驻留网络相同，
      若相同则在当前模式发起搜网，否则挂起当前网络
     */
    ulResult = NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn);

    /*  获取下个网络失败，则进行出服务区处理 */
    if (VOS_TRUE != ulResult)
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();

        return VOS_TRUE;
    }

    /* 向MM、GMM发送搜网指示 */
    NAS_MMC_SndGmmPlmnSchInit();
    NAS_MMC_SndMmPlmnSchInit();

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, end */

    NAS_MMC_UpdateRegStateSpecPlmnSearch();

    /* Added by s00261364 for V3R360_eCall项目, 2014-4-14, begin */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NO_SERVICE);
    /* Added by s00261364 for V3R360_eCall项目, 2014-4-14, end */

    /*下一个要搜索的网络是否与当前驻留网络不同,需要挂起当前模式，切换到等待挂起状态，启动保护定时器 */
    if (stDestPlmn.enRat != NAS_MML_GetCurrNetRatType())
    {
        NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_GetCurrNetRatType());
    }
    else
    {
        /* 向接入层或LMM发送搜网请求，根据不同的搜网模式，迁移到不同的L2状态，并启动保护定时器 */
        NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitSysInfoExpired_PlmnSelection_WaitGasSysInfoInd
 功能描述  : 等待g系统消息超时，同丢网的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:状态机处理成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月25日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数
  2.日    期   : 2011年7月21日
    作    者   : l00130025
    修改内容   : PhaseII修改,PlmnSelection状态机调整
  3.日    期   : 2011年12月15日
    作    者   : W00166186
    修改内容   : dts2011111502641,L下PLMN加入禁止TA后不再搜网
  4.日    期   : 2011年12月14日
    作    者   : w00176964
    修改内容   : V7R1 phaseIV 调整:驻留标记通过新的搜网控制上下文代替
  5.日    期   : 2012年06月02日
    作    者   : sunxibo /46746
    修改内容   : Added for V7R1 C50 CS/PS mode 1
  6.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  7.日    期   : 2013年8月27日
    作    者   : l00208543
    修改内容   : Coverity
  8.日    期   : 2014年4月14日
    作    者   : s00261364
    修改内容   : V3R360_eCall项目:搜网时更新服务状态
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiWaitSysInfoExpired_PlmnSelection_WaitGasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_PLMN_WITH_RAT_STRU          stDestPlmn;
    VOS_UINT32                          ulResult;

    /* 解决版本Coverity问题 */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitSysInfoExpired_PlmnSelection_WaitGasSysInfoInd: Timer Expired");

    /*如果当前需要退出状态机*/
    if (VOS_TRUE  == NAS_MMC_GetAbortFlag_PlmnSelection())
    {

        /* 回复状态机退出成功 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 清除驻留状态 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* 当前信号更新 */
    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());

    /*获取下一个要搜索的网络,若获取失败，则给上层状态机上报搜网失败，退出
      若获取成功，则判断下一个要搜索的网络是否与当前驻留网络相同，
      若相同则在当前模式发起搜网，否则挂起当前网络
     */
    ulResult = NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn);

    /*  获取下个网络失败，则进行出服务区处理*/
    if (VOS_TRUE != ulResult)
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();

        return VOS_TRUE;
    }

    /* 向MM、GMM发送搜网指示 */
    NAS_MMC_SndGmmPlmnSchInit();
    NAS_MMC_SndMmPlmnSchInit();

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, end */

    NAS_MMC_UpdateRegStateSpecPlmnSearch();

    /* Added by s00261364 for V3R360_eCall项目, 2014-4-14, begin */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NO_SERVICE);
    /* Added by s00261364 for V3R360_eCall项目, 2014-4-14, end */

    /*下一个要搜索的网络是否与当前驻留网络不同,需要挂起当前模式，切换到等待挂起状态，启动保护定时器*/
    if (stDestPlmn.enRat != NAS_MML_GetCurrNetRatType())
    {
        NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_GetCurrNetRatType());
    }
    else
    {
        /* 向接入层或LMM发送搜网请求，根据不同的搜网模式，迁移到不同的L2状态，并启动保护定时器 */
        NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitCsPsRegRsltInd
 功能描述  : 在等待CS+PS上报注册结果的时候收到QUIT消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月20日
    作    者   : z40661
    修改内容   : 新生成函数
  2.日    期   : 2011年7月14日
    作    者   : l00130025
    修改内容   : PhaseII修改,PlmnSelection状态机调整
  3.日    期   : 2011年11月8日
    作    者   : s46746
    修改内容   : V7R1 PhaseII阶段解决关机慢问题

  4.日    期   : 2011年11月29日
    作    者   : w00167002
    修改内容   : DTS2011112301233:增加打断事件ID，状态机可以知道是什么事件
                打断自己的。
                修改原因:用户下发关机命令后，当前可能在等注册结果或者在等连接
                释放，可能需要比较久的时间才能处理关机命令，通过增加打断事件，
                如归当前在等注册结果或者等链接释放状态，若收到关机命令，则直接
                退出当前状态机，处理用户的关机命令。
  5.日    期   : 2011年12月14日
    作    者   : w00176964
    修改内容   : V7R1 phaseIV 调整:驻留标记通过新的搜网控制上下文代替
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ABORT_FSM_STRU             *pstAbortMsg = VOS_NULL_PTR;
    VOS_UINT8                           ucWaitRegFlag;

    pstAbortMsg = (NAS_MMC_ABORT_FSM_STRU*)pstMsg;


    /* 若打断类型是用户请求的关机，则直接退出等注册结果状态机 */
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, begin*/
    if (NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_OFF_REQ) == pstAbortMsg->ulEventType)
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, end*/
    {
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);

        /* 回复状态机退出成功 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    ucWaitRegFlag = NAS_MMC_GetWaitRegRsltFlag_PlmnSelection();

    /* 当前没有链接可以直接退出；主要指cs/ps注册被拒，如cause17,需要继续等待注册结果的情况 */
    if (( VOS_FALSE == NAS_MML_IsRrcConnExist())
     || (NAS_MMC_WAIT_REG_RESULT_IND_NULL == ucWaitRegFlag))
    {

        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);

        /* 回复状态机退出成功 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 设置Abort标志 */
    NAS_MMC_SetAbortFlag_PlmnSelection(VOS_TRUE);

    /* 如果需要立即退出 */
    if (NAS_MMC_ABORT_FSM_IMMEDIATELY == pstAbortMsg->enAbortFsmType)
    {
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);
        NAS_MMC_SndRelReq_PlmnSelection(NAS_MML_GetCurrNetRatType());
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGmmPsRegResultInd_PlmnSelection_WaitCsPsRegRsltInd
 功能描述  : WAIT_CS_PS状态下PS域注册、RAU结果的处理入口函数
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月12日
   作    者   : l00130025
   修改内容   : 新生成函数

 2.日    期   : 2011年11月14日
   作    者   : w00167002
   修改内容   : DTS2011110907180:用户指定搜完，通知接入层RRC_NAS_FORBLA_CHANGE
                 消息
 3.日    期   : 2011年12月15日
   作    者   : W00166186
   修改内容   : dts2011111502641,L下PLMN加入禁止TA后不再搜网
 4.日    期   : 2011年12月14日
   作    者   : w00176964
   修改内容   : V7R1 phaseIV 调整:驻留标记通过新的搜网控制上下文代替
  5.日    期   : 2012年12月11日
    作    者   : l00167671
    修改内容   : DTS2012121802573, TQE清理
*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvGmmPsRegResultInd_PlmnSelection_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    GMMMMC_PS_REG_RESULT_IND_STRU      *pstPsRegRslt = VOS_NULL_PTR;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCsRegCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enPsRegCause;
    NAS_MMC_FSM_ID_ENUM_UINT32          enCurrentFsmId;
    VOS_UINT32                          ulCurrentEventType;

    enCurrentFsmId      = NAS_MMC_GetCurrFsmId();
    if (NAS_MMC_FSM_PLMN_SELECTION != enCurrentFsmId)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }
    ulCurrentEventType  = NAS_MMC_GetCurrFsmEventType();

    pstPsRegRslt        = (GMMMMC_PS_REG_RESULT_IND_STRU*)pstMsg;

    /* 针对CCO失败回退过程中收到的异系统的注册结果，不需要处理 */
    if (pstPsRegRslt->enNetType != NAS_MML_GetCurrNetRatType())
    {
        return VOS_TRUE;
    }

    /* 清除等待PS注册结果mask */
    NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnSelection(NAS_MMC_WAIT_REG_RESULT_IND_PS);

    /* 根据注册结果做对应处理: 设置服务状态，记录Cause值，设置下一步动作类型，通知对应结果 */
    NAS_MMC_ProcPsRegRslt_PlmnSelection(pstPsRegRslt);

    if (VOS_TRUE == NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enCurrentFsmId,ulCurrentEventType))
    {
        enCsRegCause = NAS_MMC_GetCsRegCause_PlmnSelection();
        enPsRegCause = NAS_MMC_GetPsRegCause_PlmnSelection();

        if (VOS_TRUE == NAS_MMC_ProcUserSearchRegRslt_PlmnSelection(enCsRegCause,enPsRegCause))
        {
            /* 更新入口消息为普通的搜网请求，后续有新的用户请求时，可以打断该状态机 */
            NAS_MMC_SaveCommonPlmnSrchEntryMsg_PlmnSelection();

            /* 用户指定搜完成后，需要将MML全局变量中的禁止漫游LA信息通知接入层*/
            NAS_MMC_SndRrMmCellSelReq(RRC_NAS_FORBLA_CHANGE);
        }
    }

    if (NAS_MMC_WAIT_REG_RESULT_IND_NULL != NAS_MMC_GetWaitRegRsltFlag_PlmnSelection())
    {
        return VOS_TRUE;
    }

    /* 如果当前需要退出状态机 */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        /* 向上层状态机发送搜网结果 ABORT */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        if (VOS_TRUE == NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enCurrentFsmId,ulCurrentEventType))
        {
            /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, begin*/
            NAS_MMC_SndMsccUserSpecPlmnSearchCnf(NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_FAIL);
            /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, end*/

#if   (FEATURE_ON == FEATURE_LTE)
            /* 向LMM发送用户搜网结束通知 */
            if ( VOS_TRUE == NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_LTE))
            {
                NAS_MMC_SndLmmUserSpecPlmnSearchEndNotify();
            }
#endif
        }

        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    NAS_MMC_PerformAdditionalActionRegFinished_PlmnSelection();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmCsRegResultInd_PlmnSelection_WaitCsPsRegRsltInd
 功能描述  : WAIT_CS_PS状态下LU结果(成功、失败)处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年4月20日
   作    者   : luokaihui / l00167671
   修改内容   : 新生成函数
 2.日    期   : 2011年7月14日
   作    者   : l00130025
   修改内容   : PhaseII修改,PlmnSelection状态机调整
 3.日    期   : 2011年11月14日
   作    者   : w00167002
   修改内容   : DTS2011110907180:用户指定搜完，通知接入层RRC_NAS_FORBLA_CHANGE
 4.日    期   : 2011年12月14日
   作    者   : w00176964
   修改内容   : V7R1 phaseIV 调整:驻留标记通过新的搜网控制上下文代替
                 消息
 5.日    期   : 2014年7月17日
   作    者   : w00167002
   修改内容   : DTS2014070304051:在GSM:A网络上CS注册成功后PS注册失败14，在B网络上
                CS/PS都注册成功，后再指定搜回到A网络上，发起CS注册成功后，由于A网络的PS加入了FORB GPRS中，
                因而此时没有发起PS注册，不能进行PDP激活。
                对比标杆可以在A网络上发起注册。
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmCsRegResultInd_PlmnSelection_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMMMC_CS_REG_RESULT_IND_STRU       *pstCsRegRslt = VOS_NULL_PTR;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCsRegCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enPsRegCause;
    NAS_MMC_FSM_ID_ENUM_UINT32          enCurrentFsmId;
    VOS_UINT32                          ulCurrentEventType;

    pstCsRegRslt = (MMMMC_CS_REG_RESULT_IND_STRU*)pstMsg;

    /* 针对CCO失败回退过程中收到的异系统的注册结果，不需要处理 */
    if (pstCsRegRslt->enNetType != NAS_MML_GetCurrNetRatType())
    {
        return VOS_TRUE;
    }

    /* 清除等待CS注册结果mask */
    NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnSelection(NAS_MMC_WAIT_REG_RESULT_IND_CS);

    /* 根据注册结果做对应处理: 设置服务状态，记录Cause值，设置下一步动作类型，通知对应结果 */
    NAS_MMC_ProcCsRegRslt_PlmnSelection(pstCsRegRslt);

    enCurrentFsmId     = NAS_MMC_GetCurrFsmId();
    if (NAS_MMC_FSM_PLMN_SELECTION != enCurrentFsmId)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }
    ulCurrentEventType = NAS_MMC_GetCurrFsmEventType();
    if (VOS_TRUE == NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enCurrentFsmId,ulCurrentEventType))
    {
        enCsRegCause = NAS_MMC_GetCsRegCause_PlmnSelection();
        enPsRegCause = NAS_MMC_GetPsRegCause_PlmnSelection();

        if (VOS_TRUE == NAS_MMC_ProcUserSearchRegRslt_PlmnSelection(enCsRegCause,enPsRegCause))
        {

            /* 在GSM下，如果CS注册成功，PS未注册，则删除FORB GPRS信息 */
            NAS_MMC_ProcUserSpecPlmnSrchForbGprsInfo_PlmnSelection();

            /*更新入口消息为普通的搜网请求，后续有新的用户请求时，可以打断该状态机*/
            NAS_MMC_SaveCommonPlmnSrchEntryMsg_PlmnSelection();

            /* 用户指定搜完成后，需要将MML全局变量中的禁止漫游LA信息通知接入层*/
            NAS_MMC_SndRrMmCellSelReq(RRC_NAS_FORBLA_CHANGE);
        }
    }

    if (NAS_MMC_WAIT_REG_RESULT_IND_NULL != NAS_MMC_GetWaitRegRsltFlag_PlmnSelection())
    {
        return VOS_TRUE;
    }

    /*如果当前需要退出状态机*/
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {

        /* 回复状态机退出成功 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    NAS_MMC_PerformAdditionalActionRegFinished_PlmnSelection();

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitCsPsRegRsltIndExpired_PlmnSelection_WaitCsPsRegRsltInd
 功能描述  : 等待两个域注册或者RAU结果时超时
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月20日
    作    者   : luokaihui / l00167671
    修改内容   : 新生成函数
  2.日    期   : 2011年7月14日
    作    者   : l00130025
    修改内容   : PhaseII修改,PlmnSelection状态机调整
  3.日    期   : 2011年12月15日
    作    者   : W00166186
    修改内容   : dts2011111502641,L下PLMN加入禁止TA后不再搜网
  4.日    期   : 2011年12月14日
    作    者   : w00176964
    修改内容   : V7R1 phaseIV 调整:驻留标记通过新的搜网控制上下文代替
  5.日    期   : 2011年2月11日
    作    者   : w00176964
    修改内容   : DTS2012012002472:GU下等待注册结果时有CS语音业务存在时，等待注册
                 结果定时器超时后，RRC连接释放后，MMC异常发起了搜网
  6.日    期   : 2012年12月11日
    作    者   : l00167671
    修改内容   : DTS2012121802573, TQE清理
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitCsPsRegRsltIndExpired_PlmnSelection_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enCsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enPsAdditionalAction;
    NAS_MMC_FSM_ID_ENUM_UINT32           enCurrentFsmId;
    VOS_UINT32                           ulCurrentEventType;

    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitCsPsRegRsltIndExpired_PlmnSelection_WaitCsPsRegRsltInd: Timer Expired");

    /* 清除当前等待注册的标识 */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnSelection();

    enCurrentFsmId     = NAS_MMC_GetCurrFsmId();
    if (NAS_MMC_FSM_PLMN_SELECTION != enCurrentFsmId)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }
    ulCurrentEventType = NAS_MMC_GetCurrFsmEventType();
    if (VOS_TRUE == NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enCurrentFsmId,ulCurrentEventType))
    {
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, begin*/
        NAS_MMC_SndMsccUserSpecPlmnSearchCnf(NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_FAIL);
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, end*/

        /* 更新入口消息为普通的搜网请求，后续有新的用户请求时，可以打断该状态机 */
        NAS_MMC_SaveCommonPlmnSrchEntryMsg_PlmnSelection();

#if   (FEATURE_ON == FEATURE_LTE)
        /* 向LMM发送用户搜网结束通知 */
        if ( VOS_TRUE == NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_LTE))
        {
            NAS_MMC_SndLmmUserSpecPlmnSearchEndNotify();
        }
#endif

    }

    /* 如果当前需要退出状态机 */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        /* 向上层状态机发送搜网结果 ABORT */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    enCsAdditionalAction = NAS_MMC_GetCsRegAdditionalAction_PlmnSelection();
    enPsAdditionalAction = NAS_MMC_GetPsRegAdditionalAction_PlmnSelection();

    /* 等待CS PS的注册结果时，有可能一个域发起注册后进行了呼叫以及紧急呼叫等业务
      (比如G下进行CS域进行呼叫，PS域无法发起注册),导致MMC一致等不到另外一个域的
      注册结果，此时MMC直接通过additional触发搜网不合理，MMC此时根据当前收到的注
      册结果更新的additional值来决定是否成功退出搜网状态机或者失败退出搜网状态机，
      由L1状态机根据搜网状态机的退出结果决定是否启动周期性选网定时器还是继续等待
      业务结束以及CSPS的注册结果 */

    enAdditionalAction = NAS_MMC_GetPrioAddtionalAction(enCsAdditionalAction, enPsAdditionalAction);

    /* 附加操作为驻留当前网络 */
    if ((NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON == enAdditionalAction)
     || (NAS_MMC_ADDITIONAL_ACTION_CELL_SELECTION == enAdditionalAction)
     || (NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON == enAdditionalAction)
     || (NAS_MMC_ADDITIONAL_ACTION_ACCESS_BARRED == enAdditionalAction))
    {
        /* 回复状态机退出成功 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_SUCC);
    }
    else
    {
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);
    }

    /* 直接退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGmmNetworkDetachInd_PlmnSelection_WaitCsPsRegRsltInd
 功能描述  : 等待注册结果时,收到网络发起的Detach操作,
             attach 过程中的detach 需要先发attach结果，再发detach结果
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月7日
   作    者   : sunxibo / 46746
   修改内容   : 新生成函数
 2.日    期   : 2011年7月14日
   作    者   : l00130025
   修改内容   : PhaseII修改,PlmnSelection状态机调整
 3.日    期   : 2011年11月14日
   作    者   : w00167002
   修改内容   : DTS2011110907180:用户指定搜完，通知接入层RRC_NAS_FORBLA_CHANGE
 4.日    期   : 2011年11月14日
   作    者   : w00167002
   修改内容   : DTS2011110907180:当前若为选网状态机，则添加禁止网络信息
                到选网状态机的禁止漫游LA变量里去
 5.日    期   : 2011年12月5日
   作    者   : z00161729
   修改内容   : V7R1 Phase IV调整,当前SYSCFG中L不在时，也需要向LMM通知ID_MMC_LMM_ACTION_RESULT_REQ
 6.日    期   : 2011年12月14日
   作    者   : w00176964
   修改内容   : V7R1 phaseIV 调整:驻留标记通过新的搜网控制上下文代替
 7.日    期   : 2012年2月13日
   作    者   : w00167002
   修改内容   : DTS2011122704039:additional action值若为无效值NAS_MMC_ADDITIONAL_ACTION_BUTT
                 则不更新当前的additional action
  8.日    期   : 2012年12月11日
    作    者   : l00167671
    修改内容   : DTS2012121802573, TQE清理
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvGmmNetworkDetachInd_PlmnSelection_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCsRegCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enPsRegCause;
    MMCGMM_NETWORK_DETACH_IND_STRU     *pstDetachMsg = VOS_NULL_PTR;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enAdditionalAction;
    NAS_MMC_FSM_ID_ENUM_UINT32           enCurrentFsmId;
    VOS_UINT32                           ulCurrentEventType;

    pstDetachMsg = (MMCGMM_NETWORK_DETACH_IND_STRU*)pstMsg;

    /* 根据当前的Detach类型， 做如下处理 */
    enAdditionalAction = NAS_MMC_ProcGmmNetworkDetachInd(pstDetachMsg);

    /* AdditionalAction有效，更新PS的下一步的动作类型 */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enAdditionalAction )
    {
        NAS_MMC_SetPsRegAdditionalAction_PlmnSelection(enAdditionalAction);
    }

    /* 记录Ps 的注册结果 */
    NAS_MMC_SetPsRegCause_PlmnSelection((NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16)pstDetachMsg->ulDetachCause);


    /* 若被拒原因值为#15, 则添加禁止网络信息到选网状态机的禁止漫游LA变量里去,
       当用户指定搜网时，则需要把禁止LA带给接入层 */
    enCurrentFsmId     = NAS_MMC_GetCurrFsmId();
    if (NAS_MMC_FSM_PLMN_SELECTION != enCurrentFsmId)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }
    ulCurrentEventType = NAS_MMC_GetCurrFsmEventType();
    if ( (VOS_TRUE == NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enCurrentFsmId, ulCurrentEventType))
      && (NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL == pstDetachMsg->ulDetachCause) )
    {
        NAS_MML_AddForbRoamLa( NAS_MML_GetCurrCampLai(),
                               NAS_MMC_GetForbRoamLaInfo_PlmnSelection() );
    }

    /* 需要继续注册时，不需要执行后续的动作 */
    if (NAS_MMC_GMM_NT_DETACH_REATTACH == pstDetachMsg->ulDetachType)
    {
        return VOS_TRUE;
    }

    NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnSelection(NAS_MMC_WAIT_REG_RESULT_IND_PS);

#if   (FEATURE_ON == FEATURE_LTE)
    /* 给LMM发送detach结果消息 */
    NAS_MMC_SndLmmMtDetachIndActionResultReq(pstDetachMsg->ulDetachType,
        (NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16)pstDetachMsg->ulDetachCause);
#endif

    if (VOS_TRUE == NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enCurrentFsmId,ulCurrentEventType))
    {
        enCsRegCause = NAS_MMC_GetCsRegCause_PlmnSelection();
        enPsRegCause = NAS_MMC_GetPsRegCause_PlmnSelection();

        if (VOS_TRUE == NAS_MMC_ProcUserSearchRegRslt_PlmnSelection(enCsRegCause,enPsRegCause))
        {
            /* 更新入口消息为普通的搜网请求，后续有新的用户请求时，可以打断该状态机 */
            NAS_MMC_SaveCommonPlmnSrchEntryMsg_PlmnSelection();

            /* 用户指定搜完成后，需要将MML全局变量中的禁止漫游LA信息通知接入层*/
            NAS_MMC_SndRrMmCellSelReq(RRC_NAS_FORBLA_CHANGE);
        }
    }

    if (NAS_MMC_WAIT_REG_RESULT_IND_NULL != NAS_MMC_GetWaitRegRsltFlag_PlmnSelection())
    {
        return VOS_TRUE;
    }

    /* 如果当前需要退出状态机 */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        /* 回复上层状态机搜网结果 ABORT */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    NAS_MMC_PerformAdditionalActionRegFinished_PlmnSelection();

    return VOS_TRUE;
}
/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGmmServiceRequestResultInd_PlmnSelection_WaitCsPsRegRsltInd
 功能描述  : 对ServiceRequest结果的操作处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成;
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月14日
   作    者   : l00130025
   修改内容   : PhaseII修改,PlmnSelection状态机调整

 2.日    期   : 2011年11月14日
   作    者   : w00167002
   修改内容   : DTS2011110907180:用户指定搜完，通知接入层RRC_NAS_FORBLA_CHANGE
                 消息
 3.日    期   : 2011年11月14日
   作    者   : w00167002
   修改内容   : DTS2011110907180:当前若为选网状态机，则添加禁止网络信息
                到选网状态机的禁止漫游LA变量里去
 4.日    期   : 2011年12月5日
   作    者   : z00161729
   修改内容   : V7R1 Phase IV调整,当前SYSCFG中L不在时，也需要向LMM通知ID_MMC_LMM_ACTION_RESULT_REQ
 5.日    期   : 2011年12月14日
   作    者   : w00176964
   修改内容   : V7R1 phaseIV 调整:驻留标记通过新的搜网控制上下文代替
 6.日    期   : 2012年2月13日
   作    者   : w00167002
   修改内容   : DTS2011122704039:additional action值若为无效值NAS_MMC_ADDITIONAL_ACTION_BUTT
                 则不更新当前的additional action
  7.日    期   : 2012年12月11日
    作    者   : l00167671
    修改内容   : DTS2012121802573, TQE清理
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvGmmServiceRequestResultInd_PlmnSelection_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    GMMMMC_SERVICE_REQUEST_RESULT_IND_STRU                 *pstServiceRsltInd = VOS_NULL_PTR;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsRegCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enPsRegCause;
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_GU_ACTION_RSLT_INFO_STRU                        stActionRslt;
#endif
    NAS_MMC_FSM_ID_ENUM_UINT32                              enCurrentFsmId;
    VOS_UINT32                                              ulCurrentEventType;

    pstServiceRsltInd = (GMMMMC_SERVICE_REQUEST_RESULT_IND_STRU*)pstMsg;

    enCurrentFsmId     = NAS_MMC_GetCurrFsmId();
    if (NAS_MMC_FSM_PLMN_SELECTION != enCurrentFsmId)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }
    ulCurrentEventType = NAS_MMC_GetCurrFsmEventType();

    /* 根据Service Reqest Result 更新做不同处理 */
    if (GMM_MMC_ACTION_RESULT_SUCCESS == pstServiceRsltInd->enActionResult)
    {
        /* 更新服务状态 */
        NAS_MMC_SetPsRegCause_PlmnSelection(NAS_MML_REG_FAIL_CAUSE_NULL);

        /* 更新PS的AdditionalAction */
        NAS_MMC_SetPsRegAdditionalAction_PlmnSelection(NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON);

#if (FEATURE_ON == FEATURE_LTE)
        /* 给LMM发送Service requestResult结果消息处理*/
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

        NAS_MMC_SetPsRegCause_PlmnSelection(pstServiceRsltInd->enRegFailCause);


        /* 若被拒原因值为#15, 则添加禁止网络信息到选网状态机的禁止漫游LA变量里去,
           当用户指定搜网时，则需要把禁止LA带给接入层 */
        if ( (VOS_TRUE == NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enCurrentFsmId, ulCurrentEventType))
          && (NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL == pstServiceRsltInd->enRegFailCause) )
        {
            NAS_MML_AddForbRoamLa( NAS_MML_GetCurrCampLai(),
                                   NAS_MMC_GetForbRoamLaInfo_PlmnSelection() );
        }

        /* AdditionalAction有效，更新PS的下一步的动作类型 */
        if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enAdditionalAction )
        {
            NAS_MMC_SetPsRegAdditionalAction_PlmnSelection(enAdditionalAction);
        }

#if (FEATURE_ON == FEATURE_LTE)
        /* 给LMM发送Service requestResult结果消息处理 */
        stActionRslt.enProcType     = NAS_MML_PROC_SER;
        stActionRslt.enRegRst       = NAS_MML_REG_RESULT_FAILURE;
        stActionRslt.enReqDomain    = NAS_MMC_REG_DOMAIN_PS;
        stActionRslt.enRstDomain    = NAS_MMC_REG_DOMAIN_PS;
        stActionRslt.enCnCause      = pstServiceRsltInd->enRegFailCause;
        stActionRslt.ulAttemptCount = 0;

        NAS_MMC_SndLmmRegActionResultReq(&stActionRslt);
#endif

    }

    if (VOS_TRUE == NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enCurrentFsmId,ulCurrentEventType))
    {
        enCsRegCause = NAS_MMC_GetCsRegCause_PlmnSelection();
        enPsRegCause = NAS_MMC_GetPsRegCause_PlmnSelection();

        if (VOS_TRUE == NAS_MMC_ProcUserSearchRegRslt_PlmnSelection(enCsRegCause, enPsRegCause))
        {
            /* 更新入口消息为普通的搜网请求，后续有新的用户请求时，可以打断该状态机 */
            NAS_MMC_SaveCommonPlmnSrchEntryMsg_PlmnSelection();

            /* 用户指定搜完成后，需要将MML全局变量中的禁止漫游LA信息通知接入层*/
            NAS_MMC_SndRrMmCellSelReq(RRC_NAS_FORBLA_CHANGE);
        }
    }

    if (NAS_MMC_WAIT_REG_RESULT_IND_NULL != NAS_MMC_GetWaitRegRsltFlag_PlmnSelection())
    {
        return VOS_TRUE;
    }

    /* 如果当前需要退出状态机 */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        /* 回复状态机退出成功 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }


    NAS_MMC_PerformAdditionalActionRegFinished_PlmnSelection();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvCmServiceRejectInd_PlmnSelection_WaitCsPsRegRsltInd
 功能描述  : 等待连接释放状态时收到CS业务导致卡无效的消息(MMCMM_CM_SERVICE_REJECT_IND)
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:消息处理成功
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月13日
   作    者   : L00171473
   修改内容   : 新生成函数

 2.日    期   : 2011年11月14日
   作    者   : w00167002
   修改内容   : DTS2011110907180:用户指定搜完，通知接入层RRC_NAS_FORBLA_CHANGE
                 消息
 3.日    期   : 2011年12月5日
   作    者   : z00161729
   修改内容   : V7R1 Phase IV调整,当前SYSCFG中L不在时，也需要向LMM通知ID_MMC_LMM_ACTION_RESULT_REQ
 4.日    期   : 2011年12月14日
   作    者   : w00176964
   修改内容   : V7R1 phaseIV 调整:驻留标记通过新的搜网控制上下文代替
 5.日    期   : 2012年12月11日
   作    者   : l00167671
   修改内容   : DTS2012121802573, TQE清理

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvCmServiceRejectInd_PlmnSelection_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    MMCMM_CM_SERVICE_REJECT_IND_STRU   *pstRcvMsg = VOS_NULL_PTR;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCsRegCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enPsRegCause;
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_GU_ACTION_RSLT_INFO_STRU    stActionRslt;
#endif
    NAS_MMC_FSM_ID_ENUM_UINT32          enCurrentFsmId;
    VOS_UINT32                          ulCurrentEventType;

    pstRcvMsg = (MMCMM_CM_SERVICE_REJECT_IND_STRU*)pstMsg;

#if (FEATURE_ON == FEATURE_LTE)
    stActionRslt.enProcType     = NAS_MML_PROC_CM_SER;
    stActionRslt.enRegRst       = NAS_MML_REG_RESULT_FAILURE;
    stActionRslt.enReqDomain    = NAS_MMC_REG_DOMAIN_CS;
    stActionRslt.enRstDomain    = NAS_MMC_REG_DOMAIN_CS;
    stActionRslt.enCnCause      = (NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16)pstRcvMsg->ulCause;
    stActionRslt.ulAttemptCount = 0;

    NAS_MMC_SndLmmRegActionResultReq(&stActionRslt);

#endif

    /*CmService Rej只在 #4和#6被拒时，会发送给MMC */
    if (NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME == pstRcvMsg->ulCause)
    {
        /* 清除CS域的等待标志 */
        NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnSelection(NAS_MMC_WAIT_REG_RESULT_IND_CS);

        /* 设置新的enCsAdditioalAction为Anycell */
        NAS_MMC_SetCsRegAdditionalAction_PlmnSelection(NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL);
    }


    enCurrentFsmId     = NAS_MMC_GetCurrFsmId();
    if (NAS_MMC_FSM_PLMN_SELECTION != enCurrentFsmId)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }
    ulCurrentEventType = NAS_MMC_GetCurrFsmEventType();
    if (VOS_TRUE == NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enCurrentFsmId,ulCurrentEventType))
    {
        enCsRegCause = NAS_MMC_GetCsRegCause_PlmnSelection();
        enPsRegCause = NAS_MMC_GetPsRegCause_PlmnSelection();

        if (VOS_TRUE == NAS_MMC_ProcUserSearchRegRslt_PlmnSelection(enCsRegCause,enPsRegCause))
        {
            /*更新入口消息为普通的搜网请求，后续有新的用户请求时，可以打断该状态机*/
            NAS_MMC_SaveCommonPlmnSrchEntryMsg_PlmnSelection();

            /* 用户指定搜完成后，需要将MML全局变量中的禁止漫游LA信息通知接入层*/
            NAS_MMC_SndRrMmCellSelReq(RRC_NAS_FORBLA_CHANGE);
        }
    }

    if (NAS_MMC_WAIT_REG_RESULT_IND_NULL != NAS_MMC_GetWaitRegRsltFlag_PlmnSelection())
    {
        return VOS_TRUE;
    }


    /* 如果当前需要退出状态机 */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        /* 回复状态机退出成功 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    NAS_MMC_PerformAdditionalActionRegFinished_PlmnSelection();

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvWasSuspendInd_PlmnSelection_WaitCsPsRegRsltInd
 功能描述  : WAS上报的SUSPEND_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : VOS_TRUE:返回处理成功
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年4月20日
   作    者   : W00167002
   修改内容   : 新生成函数
 2.日    期   : 2011年7月14日
   作    者   : l00130025
   修改内容   : PhaseII修改搜网状态机
 3.日    期   : 2013年8月5日
   作    者   : w00167002
   修改内容   : DTS2013073106748:开机手动模式G下搜24003 CS域注册成功，PS域
                注册失败17，在选网状态机，用户发起电话，切换到W下的46002网络上。
                电话挂断后，W上报丢网,选网状态机作ANYCELL搜网，没有搜原有的24003网络。
                修改为选网状态机等注册结果时候，如果收到HO切换成功后，则退出
                选网状态机,待电话结束后，再由L1 MAIN进入选网状态机。
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvWasSuspendInd_PlmnSelection_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_IND_ST                *pstSuspendMsg = VOS_NULL_PTR;

    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat;

    pstSuspendMsg = (RRMM_SUSPEND_IND_ST*)pstMsg;

    enRat         = NAS_MML_GetCurrNetRatType();

    /* 如果为OOS或者参数不正确, 则不允许进行异系统重选 */
    if ((MMC_SUSPEND_CAUSE_PLMNSEARCH == pstSuspendMsg->ucSuspendCause)
     || (MMC_SUSPEND_CAUSE_BUTT <= pstSuspendMsg->ucSuspendCause))
    {
        NAS_MMC_SndAsSuspendRsp(RRC_NAS_SUSPEND_FAILURE, WUEPS_PID_WRR);
    }
    else
    {
        NAS_MMC_SetInterSysSuspendRat_PlmnSelection(enRat);

        NAS_MMC_LoadInterSysFsm_PlmnSelection(pstSuspendMsg->ucSuspendCause);
    }


    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGasSuspendInd_PlmnSelection_WaitCsPsRegRsltInd
 功能描述  : GAS上报的SUSPEND_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : VOS_TRUE:返回处理成功
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月20日
    作    者   : W00167002
    修改内容   : 新生成函数
  2.日    期   : 2011年7月14日
    作    者   : l00130025
    修改内容   : PhaseII修改搜网状态机
  3.日    期   : 2013年8月5日
    作    者   : w00167002
    修改内容   : DTS2013073106748:开机手动模式G下搜24003 CS域注册成功，PS域
                注册失败17，在选网状态机，用户发起电话，切换到W下的46002网络上。
                电话挂断后，W上报丢网,选网状态机作ANYCELL搜网，没有搜原有的24003网络。
                修改为选网状态机等注册结果时候，如果收到HO切换成功后，则退出
                选网状态机,待电话结束后，再由L1 MAIN进入选网状态机。
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvGasSuspendInd_PlmnSelection_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    RRMM_SUSPEND_IND_ST                *pstSuspendMsg = VOS_NULL_PTR;

    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat;

    pstSuspendMsg = (RRMM_SUSPEND_IND_ST*)pstMsg;

    enRat         = NAS_MML_GetCurrNetRatType();

    /* 如果为OOS或者参数不正确, 则不允许进行异系统重选 */
    if ((MMC_SUSPEND_CAUSE_PLMNSEARCH == pstSuspendMsg->ucSuspendCause)
     || (MMC_SUSPEND_CAUSE_BUTT <= pstSuspendMsg->ucSuspendCause))
    {
        NAS_MMC_SndAsSuspendRsp(RRC_NAS_SUSPEND_FAILURE, UEPS_PID_GAS);
    }
    else
    {
        NAS_MMC_SetInterSysSuspendRat_PlmnSelection(enRat);

        NAS_MMC_LoadInterSysFsm_PlmnSelection(pstSuspendMsg->ucSuspendCause);
    }


    return VOS_TRUE;
}
/*****************************************************************************
 函 数 名  : NAS_MMC_RcvSuspendFailCauseArealost_WaitCsPsRegRsltInd
 功能描述  : 搜网状态机中收到MmcMmcSuspendRslt的结果为失败且原因值为area lost
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年2月27日
    作    者   : l00167671
    修改内容   : 新生成函数
  2.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  3.日    期   : 2013年8月27日
    作    者   : l00208543
    修改内容   : Coverity
  4.日    期   : 2014年4月14日
    作    者   : s00261364
    修改内容   : V3R360_eCall项目:搜网时更新服务状态
*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvSuspendFailCauseArealost_WaitCsPsRegRsltInd(VOS_VOID
)
{
    NAS_MML_PLMN_WITH_RAT_STRU          stDestPlmn;
    VOS_UINT32                          ulResult;

    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo           = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stCurPlmn;

	/* 解决版本Coverity问题 */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    /* 停止等待注册结果消息的定时器  */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);

    /* 获取高优先级网络列表 */
    pstPlmnSelectionListInfo = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();

    ulResult = NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn);

    /* 获取下个网络失败 */
    if (VOS_TRUE != ulResult)
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);
        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();
        return VOS_TRUE;
    }

    /* 获取当前驻留的网络信息 */
    pstCurCampInfo     = NAS_MML_GetCurrCampPlmnInfo();
    stCurPlmn.stPlmnId = stDestPlmn.stPlmnId;
    stCurPlmn.enRat    = pstCurCampInfo->enNetRatType;

    /* 更新当前网络的搜索状态为已注册过，在此轮高优先级搜网中，不会再搜此网络 */
    NAS_MMC_UpdatePlmnNetStatusInPlmnSelectionList(&stCurPlmn,
                                            NAS_MMC_NET_STATUS_SEARCHED_REGISTERED,
                                            pstPlmnSelectionListInfo);
    /* 清除驻留状态 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

    /* 当前信号更新 */
    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());

    /*获取下一个要搜索的网络,若获取失败，则给上层状态机上报搜网失败，退出
      若获取成功，则判断下一个要搜索的网络是否与当前驻留网络相同，
      若相同则在当前模式发起搜网，否则挂起当前网络
     */
    ulResult = NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn);

    /* 获取下个网络失败，则进行出服务区处理 */
    if (VOS_TRUE != ulResult)
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();

        return VOS_TRUE;
    }

    /* 向MM、GMM发送搜网指示 */
    NAS_MMC_SndGmmPlmnSchInit();
    NAS_MMC_SndMmPlmnSchInit();

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, end */

    NAS_MMC_UpdateRegStateSpecPlmnSearch();

    /* Added by s00261364 for V3R360_eCall项目, 2014-4-14, begin */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NO_SERVICE);
    /* Added by s00261364 for V3R360_eCall项目, 2014-4-14, end */

    /*下一个要搜索的网络是否与当前驻留网络不同,需要挂起当前模式，切换到等待挂起状态，启动保护定时器*/
    if (stDestPlmn.enRat != NAS_MML_GetCurrNetRatType())
    {
        NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_GetCurrNetRatType());
    }
    /* 不需要Suspend */
    else
    {
        /* 向接入层或LMM发送搜网请求，根据不同的搜网模式，迁移到不同的L2状态，并启动保护定时器 */
        NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvSuspendRsltHoSucc_PlmnSelection_WaitCsPsRegRsltInd
 功能描述  : 搜网状态机中收到MmcMmcSuspendRslt的结果为切换成功的处理
 输入参数  : ulEventType:消息类型
              pstMsg     :消息的首地址
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月6日
    作    者   : w00167002
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_RcvSuspendRsltHoSucc_PlmnSelection_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CONN_STATUS_INFO_STRU                          *pstConnStatus       = VOS_NULL_PTR;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;
    NAS_MMC_FSM_ID_ENUM_UINT32                              enCurrentFsmId;
    VOS_UINT32                                              ulCurrentEventType;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         ucInterSysSuspendRat;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         ucCurrRat;

    enCurrentFsmId       = NAS_MMC_GetCurrFsmId();
    pstConnStatus        = NAS_MML_GetConnStatus();
    ucInterSysSuspendRat = NAS_MMC_GetInterSysSuspendRat_PlmnSelection();
    ucCurrRat            = NAS_MML_GetCurrNetRatType();

#if (FEATURE_LTE == FEATURE_ON)

    /* 迁移到不同的接入技术时，需要迁移到不同的处理注册结果状态 */
    if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        /* 停止当前等待CS/PS注册结果的状态 */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);

        /* 回复状态机退出成功 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_SUCC);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

#endif

    /* 等注册结果时候，如果当前有CS业务链接时候发生了异系统切换，则退状态机到L1 */
    if ( (VOS_TRUE  == pstConnStatus->ucCsServiceConnStatusFlg)
      && (ucCurrRat != ucInterSysSuspendRat) )
    {
        /* 停止当前等待CS/PS注册结果的状态 */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);

        /* 当前用户发起的是指定搜网,则回复注册结果成功 */
        ulCurrentEventType = NAS_MMC_GetCurrFsmEventType();

        if (VOS_TRUE == NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enCurrentFsmId,ulCurrentEventType))
        {
            NAS_MMC_SndMsccUserSpecPlmnSearchCnf(NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_FAIL);

            /* 更新入口消息为普通的搜网请求，后续有新的用户请求时，可以打断该状态机 */
            NAS_MMC_SaveCommonPlmnSrchEntryMsg_PlmnSelection();

#if   (FEATURE_ON == FEATURE_LTE)
            /* 向LMM发送用户搜网结束通知 */
            if ( VOS_TRUE == NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_LTE))
            {
                NAS_MMC_SndLmmUserSpecPlmnSearchEndNotify();
            }
#endif
        }

        enCsAdditionalAction = NAS_MMC_GetCsRegAdditionalAction_PlmnSelection();
        enPsAdditionalAction = NAS_MMC_GetPsRegAdditionalAction_PlmnSelection();

        /* 等待CS PS的注册结果时，有可能一个域发起注册后进行了呼叫以及紧急呼叫等业务,
           发生了G<->W之间的异系统的切换(比如G下进行CS域进行呼叫，PS域无法发起注册),
           电话结束后，在先前发起电话的网络状态被更改为REGISTERED,因而在选网状态机不会再
           去选择先前尝试的网络。MMC此时根据当前收到的注册结果更新的additional值来决定
           是否成功退出搜网状态机或者失败退出搜网状态机,由L1状态机根据搜网状态机的退出
           结果决定是否启动周期性选网定时器还是继续等待业务结束以及CSPS的注册结果 */

        enAdditionalAction = NAS_MMC_GetPrioAddtionalAction(enCsAdditionalAction, enPsAdditionalAction);

        /* 附加操作为驻留当前网络 */
        if ((NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON  == enAdditionalAction)
         || (NAS_MMC_ADDITIONAL_ACTION_CELL_SELECTION  == enAdditionalAction)
         || (NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON == enAdditionalAction)
         || (NAS_MMC_ADDITIONAL_ACTION_ACCESS_BARRED   == enAdditionalAction))
        {
            /* 回复状态机退出成功 */
            NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_SUCC);
        }
        else
        {
            NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);
        }

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcMmcSuspendRslt_PlmnSelection_WaitCsPsRegRsltInd
 功能描述  : 处理SUSPEND状态机运行完成的函数
 输入参数  : ulEventType:消息类型
             pstMsg:NAS_MM_LAYER_MMCMMC_SUSPEND_RSLT消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月10日
    作    者   : W00167002
    修改内容   : 新生成函数
  2.日    期   : 2011年7月14日
    作    者   : l00130025
    修改内容   : 新生成函数
  3.日    期   : 2011年12月30日
    作    者   : l65478
    修改内容   : 在迁到L模时,不立刻把CS设置成可选搜网,而是等待PS注册结果时
                 根据具体的原因值再设置
  4.日    期   : 2011年12月14日
    作    者   : w00176964
    修改内容   : V7R1 phaseIV 调整:驻留标记通过新的搜网控制上下文代替
  5.日    期   : 2013年02月27日
    作    者   : l00167671
    修改内容   : DTS2013022608712出服务区后的搜网成功等待注册时重定向失败重新收到丢网消息
  6.日    期   : 2013年8月5日
    作    者   : w00167002
    修改内容   : DTS2013073106748:开机手动模式G下搜24003 CS域注册成功，PS域
                注册失败17，在选网状态机，用户发起电话，切换到W下的46002网络上。
                电话挂断后，W上报丢网,选网状态机作ANYCELL搜网，没有搜原有的24003网络。
                修改为选网状态机等注册结果时候，如果收到HO切换成功后，则退出
                选网状态机,待电话结束后，再由L1 MAIN进入选网状态机
  7.日    期   : 2013年2月7日
    作    者   : W00176964
    修改内容   : Volte_phase3项目调整:增加IMS不可用时disable L模的逻辑修改
  8.日    期   : 2013年4月9日
    作    者   : y00176023
    修改内容   : DSDS GUNAS II项目:收到NO RF 退状态机，发送失败迁移到ooc
  9.日    期   : 2014年6月30日
    作    者   : b00269685
    修改内容   : DSDS GUNAS III项目:修改函数名称

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcMmcSuspendRslt_PlmnSelection_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMCMMC_SUSPEND_RSLT_STRU       *pstSuspendRsltMsg = VOS_NULL_PTR;

    pstSuspendRsltMsg = (NAS_MMCMMC_SUSPEND_RSLT_STRU*)pstMsg;


    /* HO成功的处理 */
    if ( (MMC_SUSPEND_CAUSE_HANDOVER == pstSuspendRsltMsg->enSuspendCause)
      && (NAS_MMC_SUSPEND_SUCCESS    == pstSuspendRsltMsg->enRslt) )
    {
        NAS_MMC_RcvSuspendRsltHoSucc_PlmnSelection_WaitCsPsRegRsltInd(ulEventType, pstMsg);

        return VOS_TRUE;
    }

    /* 如果重选结果为失败,原因为出服务区,则当作注册过程中出服务区处理 */
    if ((NAS_MMC_SUSPEND_FAIL == pstSuspendRsltMsg->enRslt)
     && (NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST == pstSuspendRsltMsg->enFailCause))
    {
        if (VOS_FALSE == NAS_MML_GetRfAvailFlg())
        {
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);

            /* 状态机退出结果为失败，迁移到OOC */
            NAS_MMC_ProcNoRf_PlmnSelection(NAS_MML_GetCurrNetRatType());

            return VOS_TRUE;
        }

        /*如果当前需要退出状态机*/
        if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
        {
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);
            NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);

            /* 回复状态机退出成功 */
            NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

            /* 直接退出当前状态机 */
            NAS_MMC_FSM_QuitFsmL2();

            return VOS_TRUE;
        }
        else
        {
            return NAS_MMC_RcvSuspendFailCauseArealost_WaitCsPsRegRsltInd();
        }
    }

#if (FEATURE_LTE == FEATURE_ON)

    /* 迁移到不同的接入技术时，需要迁移到不同的处理注册结果状态 */
    if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        /* 停止当前等待CS/PS注册结果的状态 */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);


        /* HO成功的处理封装到NAS_MMC_RcvSuspendRsltHoSucc_PlmnSelection_WaitCsPsRegRsltInd */

        /* 更新当前等待EPS的注册结果 */
        NAS_MMC_ClearAllWaitRegRsltFlag_PlmnSelection();
        NAS_MMC_SetWaitRegRsltFlag_PlmnSelection(NAS_MMC_WAIT_REG_RESULT_IND_PS);

        /* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-7, begin */
#if (FEATURE_ON == FEATURE_IMS)
        /* 增加等待IMS是否可用结果FLG,MMA保证收到PS注册结果上报IMS是否可用指示到MMC */
        NAS_MMC_SetWaitRegRsltFlag_PlmnSelection(NAS_MMC_WAIT_REG_RESULT_IND_IMS);
#endif
        /* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-7, end */

        /* 更新CS的注册Cause和AdditionalAction */
        NAS_MMC_SetCsRegCause_PlmnSelection(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);
        NAS_MMC_SetCsRegAdditionalAction_PlmnSelection(NAS_MMC_ADDITIONAL_ACTION_BUTT);
        NAS_MMC_SetPsRegAdditionalAction_PlmnSelection(NAS_MMC_ADDITIONAL_ACTION_BUTT);

        /* 迁移到等待注册结果子状态PLMN_SRCH:NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_REG_IND, TI_NAS_MMC_WAIT_EPS_REG_IND_LEN);

        return VOS_TRUE;
    }

#endif

     /* 与Intersys状态机的配合待后续补充
     switch (pstSuspendRsltMsg->enRslt)
     {
         case NAS_MMC_SUSPEND_SUCCESS:
         break;

         case NAS_MMC_SUSPEND_FAIL :
         case NAS_MMC_SUSPEND_QUIT :

         break;

         case NAS_MMC_SUSPEND_AREA_LOST :
         break;

         default:

         break;
     }
     */


    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvAreaLostInd_PlmnSelection_WaitCsPsRegRsltInd
 功能描述  : 等待两个域注册结果时丢网
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月7日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2011年7月14日
    作    者   : l00130025
    修改内容   : PhaseII修改,PlmnSelection状态机调整
  3.日    期   : 2011年11月9日
    作    者   : w00167002
    修改内容   : 在注册过程中收到丢网指示，则更新当前的网络的注册状态为
                  NAS_MMC_NET_STATUS_SEARCHED_REGISTERED。
  4.日    期   : 2011年12月15日
    作    者   : W00166186
    修改内容   : dts2011111502641,L下PLMN加入禁止TA后不再搜网
  5.日    期   : 2011年12月14日
    作    者   : w00176964
    修改内容   : V7R1 phaseIV 调整:驻留标记通过新的搜网控制上下文代替
  6.日    期   : 2012年06月02日
    作    者   : sunxibo /46746
    修改内容   : Added for V7R1 C50 CS/PS mode 1
  7.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  8.日    期   : 2013年8月27日
    作    者   : l00208543
    修改内容   : Coverity
  9.日    期   : 2013年4月9日
    作    者   : y00176023
    修改内容   : DSDS GUNAS II项目:收到NO RF 退状态机，发送失败迁移到ooc
 10.日    期   : 2014年5月4日
    作    者   : t00173447
    修改内容   : DTS2014042105390,软银定制需求
 11.日    期   : 2014年4月14日
    作    者   : s00261364
    修改内容   : V3R360_eCall项目:搜网时更新服务状态
 12.日    期   : 2014年6月30日
    作    者   : b00269685
    修改内容   : 修改函数名称
 13.日    期   : 2014年10月13日
    作    者   : w00167002
    修改内容   : DTS2014102005694:G下，CS注册成功后，PS还未注册成功时候，则
               发起电话业务，在电话业务建联时候丢网，MM没有释放信令，MMC没有发起ANY
               CELL搜网。
 14.日    期   : 2015年1月8日
    作    者   : w00167002
    修改内容   : DTS2015010601540:在CS注册成功，PS注册失败时候，在继续等待注册过
                  程中，副卡抢占资源导致NO RF丢网。在等待资源可用后重新触发搜索当前
                  网络。
 15.日    期   : 2015年10月22日
    作    者   : s00217060
    修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0:RRMM_AREA_LOST_IND消息接口变更
*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvAreaLostInd_PlmnSelection_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_PLMN_WITH_RAT_STRU          stDestPlmn;
    VOS_UINT32                          ulResult;

    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo           = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stCurPlmn;

    RRMM_AREA_LOST_IND_STRU                                *pstAreaLost              = VOS_NULL_PTR;

    pstAreaLost     = (RRMM_AREA_LOST_IND_STRU*)pstMsg;

    /* 解决版本Coverity问题 */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    /* 停止等待注册结果消息的定时器  */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);


    /* 获取当前驻留的网络信息 */
    pstCurCampInfo     = NAS_MML_GetCurrCampPlmnInfo();
    stCurPlmn.stPlmnId = pstCurCampInfo->stLai.stPlmnId;
    stCurPlmn.enRat    = pstCurCampInfo->enNetRatType;

    /* Modified by c00318887 for 预置频点搜网优化, 2015-9-9, begin */
    NAS_MMC_SaveLastCampedPlmnWithRat(NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMcc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMnc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.enCampPlmnNetRat);
    /* Modified by c00318887 for 预置频点搜网优化, 2015-9-9, end */


    /* 获取高优先级网络列表 */
    pstPlmnSelectionListInfo = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();


    /* 在等待注册结果时候，如果因NO RF而丢网，则不更新当前为REGISTER状态，等待资源
       可用时候，可以继续搜网并在此网络上进行注册 */
    if (RRC_NAS_NO_RF_AREA_LOST != pstAreaLost->ulRptMode)
    {
        /* 更新当前网络的搜索状态为已注册过，在此轮高优先级搜网中，不会再搜此网络 */
        NAS_MMC_UpdatePlmnNetStatusInPlmnSelectionList(&stCurPlmn,
                                            NAS_MMC_NET_STATUS_SEARCHED_REGISTERED,
                                            pstPlmnSelectionListInfo);

        /* 更新是否进行过history标志,进行过pref band搜或spec搜时，也认为已经进行过history搜索 */
        if ((VOS_TRUE == pstAreaLost->stSearchedType.ucHistorySearchedFlg)
         || (VOS_TRUE == pstAreaLost->stSearchedType.ucPrefBandSearchedFlg)
         || (VOS_TRUE == pstAreaLost->stSearchedType.ucSpecSearchedFlg))
        {
            NAS_MMC_SetHistorySearchedFlag_PlmnSelection(NAS_MML_GetCurrNetRatType(), VOS_TRUE);
        }

    }
    else
    {
        /* 更新当前网络的搜索状态为存在，在NO RF资源恢复后继续搜索当前网络 */
        NAS_MMC_UpdatePlmnNetStatusInPlmnSelectionList(&stCurPlmn,
                                            NAS_MMC_NET_STATUS_SEARCHED_EXIST,
                                            pstPlmnSelectionListInfo);
    }

    /* 清除驻留状态 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

    /* 当前信号更新 */
    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());


    /* 通知MM/GMM进入丢网,MM会释放CS业务 */
    NAS_MMC_SndMmCoverageLostInd();
    NAS_MMC_SndGmmCoverageLostInd();

    if (RRC_NAS_NO_RF_AREA_LOST == pstAreaLost->ulRptMode)
    {
        /* 回复状态机失败 */
        NAS_MMC_ProcNoRfAreaLost_PlmnSelection(NAS_MML_GetCurrNetRatType());

        return VOS_TRUE;
    }

    /*如果当前需要退出状态机*/
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        /* 回复状态机退出成功 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /*获取下一个要搜索的网络,若获取失败，则给上层状态机上报搜网失败，退出
      若获取成功，则判断下一个要搜索的网络是否与当前驻留网络相同，
      若相同则在当前模式发起搜网，否则挂起当前网络
     */
    ulResult = NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn);

    /* 获取下个网络失败，则进行出服务区处理 */
    if (VOS_TRUE != ulResult)
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();

        return VOS_TRUE;
    }

    /* 向MM、GMM发送搜网指示 */
    NAS_MMC_SndGmmPlmnSchInit();
    NAS_MMC_SndMmPlmnSchInit();

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, end */

    NAS_MMC_UpdateRegStateSpecPlmnSearch();

    /* Added by s00261364 for V3R360_eCall项目, 2014-4-14, begin */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NO_SERVICE);
    /* Added by s00261364 for V3R360_eCall项目, 2014-4-14, end */

    /*下一个要搜索的网络是否与当前驻留网络不同,需要挂起当前模式，切换到等待挂起状态，启动保护定时器*/
    if (stDestPlmn.enRat != NAS_MML_GetCurrNetRatType())
    {
        NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_GetCurrNetRatType());
    }
    /* 不需要Suspend */
    else
    {
        /* 向接入层或LMM发送搜网请求，根据不同的搜网模式，迁移到不同的L2状态，并启动保护定时器 */
        NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvWasSysInfoInd_PlmnSelection_WaitCsPsRegRsltInd
 功能描述  : 在等待CS+PS注册过程中收到W模式系统消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月14日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数
  2.日    期   : 2011年7月14日
    作    者   : l00130025
    修改内容   : PhaseII修改,PlmnSelection状态机调整
  3.日    期   : 2011年10月6日
    作    者   : w00167002
    修改内容   : PhaseII修改:删除更改当前的网络的注册状态为REGISTERED，
                  统一等注册结果后，才更改为REGISTERED
  4.日    期   : 2011年11月28日
    作    者   : w00167002
    修改内容   : DTS2011112406707:删除将当前的Additional Action进行初始化的代码.
                修改原因:在ROAMING BROKER时候，设置1次失败,注册失败1次后，
                MMC需要搜网，但是MMC可能要等两个域的结果(如在选网状态机)，
                当收到系统消息的时候，假流程会更改MMC的AdditionalAction的值,
                导致ROMING BROKER特性失效。
  5.日    期   : 2012年5月10日
    作    者   : l65478
    修改内容   : DTS2012050500988:NMO I时,PS注册失败#11,收到系统信息后又发起了注册
  6.日    期   : 2012年6月16日
    作    者   : l00171473
    修改内容   : DTS2012061409086, 收到W或G的系统消息时通知L模
  7.日    期   : 2012年8月21日
    作    者   : z00161729
    修改内容   : DCM定制需求和遗留问题修改
  8.日    期   : 2012年12月11日
    作    者   : w00176964
    修改内容   : 收到系统消息接入禁止信息变化则通知MMA
  9.日    期   : 2012年12月11日
    作    者   : l00167671
    修改内容   : DTS2012121802573, TQE清理

 10.日    期   : 2013年9月14日
    作    者   : w00167002
    修改内容   : DTS2013090908249:开机用户指定搜网24003，CS注册被拒15，MM在LIMIT
                 状态，在选网状态机收到同一小区的SYSINFO后，通知MM当前没有FORB FLG,
                 导致MM发起循环注册；
                 在NAS_MMC_SndMmGsmSysInfoInd函数中，如果是用户指定搜网，则将FORBFLG设置为null，
                 将此耦合去除；
                 在选网状态机识别出是否是用户指定搜网，并配置正确的ulForbiddenFlg标志；
 11.日    期   : 2014年1月18日
    作    者   : z00234330
    修改内容   : dts2014011801513,接入层上报的系统消息里面有可能没有携带plmnid,
               此处判断并没有判断plmnid是否有效

 12.日    期   : 2014年5月4日
    作    者   : t00173447
    修改内容   : DTS2014042105390,软银定制需求
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvWasSysInfoInd_PlmnSelection_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;
    NAS_MMC_FSM_ID_ENUM_UINT32                              enCurrentFsmId;
    VOS_UINT32                                              ulCurrentEventType;
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

    enCurrentFsmId     = NAS_MMC_GetCurrFsmId();
    if (NAS_MMC_FSM_PLMN_SELECTION != enCurrentFsmId)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }
    ulCurrentEventType = NAS_MMC_GetCurrFsmEventType();

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

    /* 驻留小区变化时，上报系统消息 */
    if (VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
    {
        /* 主动上报 */
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, begin*/
        NAS_MMC_SndMsccSysInfo();
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, end*/

    }

    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
    /* 驻留小区的接入受限信息变化时,通知MMA模块当前接入受限信息 */
    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldCsRestrictInfo, pstCurCsRestrictInfo))
    {
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, begin*/
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_CS, pstCurCsRestrictInfo);
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, end*/
    }

    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldPsRestrictInfo, pstCurPsRestrictInfo))
    {
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, begin*/
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_PS, pstCurPsRestrictInfo);
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, end*/
    }
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, end */

    /* 状态更新为当前已经驻留 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))

    /* CBS上报*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_WCDMA);
#endif

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, end */

    /* 更新当前等待CSPS的注册结果 */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnSelection();
    NAS_MMC_SetWaitRegRsltFlag_PlmnSelection(NAS_MMC_WAIT_REG_RESULT_IND_CS);
    NAS_MMC_SetWaitRegRsltFlag_PlmnSelection(NAS_MMC_WAIT_REG_RESULT_IND_PS);

    /* 更新CSPS的RegCause */
    NAS_MMC_SetCsRegCause_PlmnSelection(NAS_MML_REG_FAIL_CAUSE_BUTT);
    NAS_MMC_SetPsRegCause_PlmnSelection(NAS_MML_REG_FAIL_CAUSE_BUTT);



    /* 转发系统消息通知 给 MM/GMM,并将当前系统消息的 Forbidden 类型携带过去 */

    if (VOS_TRUE == NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enCurrentFsmId,ulCurrentEventType))
    {
        NAS_MMC_SndMmWasSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenTypeForUserSpecPlmnSrch(),
                                   VOS_TRUE,
                                   pstMsg);

        NAS_MMC_SndGmmWasSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenTypeForUserSpecPlmnSrch(),
                                   VOS_TRUE,
                                   pstMsg);
    }
    else
    {
        NAS_MMC_SndMmWasSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenType(),
                                   VOS_FALSE,
                                   pstMsg);

        NAS_MMC_SndGmmWasSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenType(),
                                   VOS_FALSE,
                                   pstMsg);
    }


#if (FEATURE_ON == FEATURE_LTE)

    NAS_MMC_SndLmmWcdmaSysInfoInd(pstMsg);
#endif

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGasSysInfoInd_PlmnSelection_WaitCsPsRegRsltInd
 功能描述  : 在等待CS+PS注册过程中收到G模式系统消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月14日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数
  2.日    期   : 2011年7月14日
    作    者   : l00130025
    修改内容   : PhaseII修改,PlmnSelection状态机调整
  3.日    期   : 2011年10月6日
    作    者   : w00167002
    修改内容   : PhaseII修改:删除更改当前的网络的注册状态为REGISTERED，
                  统一等注册结果后，才更改为REGISTERED
  4.日    期   : 2011年11月28日
    作    者   : w00167002
    修改内容   : DTS2011112406707:删除将当前的Additional Action进行初始化的代码.
                修改原因:在ROAMING BROKER时候，设置1次失败,注册失败1次后，
                MMC需要搜网，但是MMC可能要等两个域的结果(如在选网状态机)，
                当收到系统消息的时候，假流程会更改MMC的AdditionalAction的值,
                导致ROMING BROKER特性失效。
  5.日    期   : 2012年5月10日
    作    者   : l65478
    修改内容   : DTS2012050500988:NMO I时,PS注册失败#11,收到系统信息后又发起了注册
  6.日    期   : 2012年6月16日
    作    者   : l00171473
    修改内容   : DTS2012061409086, 收到W或G的系统消息时通知L模
  7.日    期   : 2012年8月21日
    作    者   : z00161729
    修改内容   : DCM定制需求和遗留问题修改
  8.日    期   : 2012年12月11日
    作    者   : w00176964
    修改内容   : 收到系统消息接入禁止信息变化则通知MMA
  9.日    期   : 2012年12月11日
    作    者   : l00167671
    修改内容   : DTS2012121802573, TQE清理
 10.日    期   : 2013年9月14日
    作    者   : w00167002
    修改内容   : DTS2013090908249:开机用户指定搜网24003，CS注册被拒15，MM在LIMIT
                 状态，在选网状态机收到同一小区的SYSINFO后，通知MM当前没有FORB FLG,
                 导致MM发起循环注册；
                 在NAS_MMC_SndMmGsmSysInfoInd函数中，如果是用户指定搜网，则将FORBFLG设置为null，
                 将此耦合去除；
                 在选网状态机识别出是否是用户指定搜网，并配置正确的ulForbiddenFlg标志；
 11.日    期   : 2013年11月01日
    作    者   : l00208543
    修改内容   : 根据卡类型禁止网络制式

 12.日    期   : 2014年5月4日
    作    者   : t00173447
    修改内容   : DTS2014042105390,软银定制需求
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvGasSysInfoInd_PlmnSelection_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;
    NAS_MMC_FSM_ID_ENUM_UINT32                              enCurrentFsmId;
    VOS_UINT32                                              ulCurrentEventType;
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
#endif
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, end */

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    PS_MEM_SET(&stOldCsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_SET(&stOldPsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

    /* 如果收到GAS的系统消息，且目前Utran被Enable，则重新Disable Utran */
    NAS_MMC_RcvGasSysInfoSetUtranCapabilityStatus();

    enCurrentFsmId     = NAS_MMC_GetCurrFsmId();
    if (NAS_MMC_FSM_PLMN_SELECTION != enCurrentFsmId)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }
    ulCurrentEventType = NAS_MMC_GetCurrFsmEventType();

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
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, begin*/
        NAS_MMC_SndMsccSysInfo();
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, end*/

    }

    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
    /* 驻留小区的接入受限信息变化时,通知MMA模块当前接入受限信息 */
    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldCsRestrictInfo, pstCurCsRestrictInfo))
    {
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, begin*/
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_CS, pstCurCsRestrictInfo);
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, end*/
    }

    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldPsRestrictInfo, pstCurPsRestrictInfo))
    {
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, begin*/
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_PS, pstCurPsRestrictInfo);
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, end*/
    }
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, end */

    /* 状态更新为当前已经驻留 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, begin */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_RcvGuSysInfoIndSetLteAbility(pstMsg, enLCapabilityStatus);
#endif
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, end */

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))

    /* CBS上报*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_GSM);
#endif

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, end */

    /* 更新当前等待CSPS的注册结果 */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnSelection();
    NAS_MMC_SetWaitRegRsltFlag_PlmnSelection(NAS_MMC_WAIT_REG_RESULT_IND_CS);
    NAS_MMC_SetWaitRegRsltFlag_PlmnSelection(NAS_MMC_WAIT_REG_RESULT_IND_PS);

    /* 更新CSPS的RegCause */
    NAS_MMC_SetCsRegCause_PlmnSelection(NAS_MML_REG_FAIL_CAUSE_BUTT);
    NAS_MMC_SetPsRegCause_PlmnSelection(NAS_MML_REG_FAIL_CAUSE_BUTT);


    if (VOS_TRUE == NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enCurrentFsmId,ulCurrentEventType))
    {
        NAS_MMC_SndMmGsmSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenTypeForUserSpecPlmnSrch(),
                                   VOS_TRUE,
                                   pstMsg);

        NAS_MMC_SndGmmGsmSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenTypeForUserSpecPlmnSrch(),
                                   VOS_TRUE,
                                   pstMsg);
    }
    else
    {
        NAS_MMC_SndMmGsmSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenType(),
                                   VOS_FALSE,
                                   pstMsg);

        NAS_MMC_SndGmmGsmSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenType(),
                                   VOS_FALSE,
                                   pstMsg);
    }

#if (FEATURE_ON == FEATURE_LTE)

    NAS_MMC_SndLmmGsmSysInfoInd(pstMsg);
#endif

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTafSysCfgReq_PlmnSelection_WaitCsPsRegRsltInd
 功能描述  : MMC处理MSCC请求的SYSCFG设置消息
 输入参数  : ulEventType:消息类型
             pstMsg:SYSCFG设置消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE: 处理完成
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月04日
    作    者   : w00167002
    修改内容   : 新生成函数
  2.日    期   : 2011年7月14日
    作    者   : l00130025
    修改内容   : PhaseII修改,PlmnSelection状态机调整
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTafSysCfgReq_PlmnSelection_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 直接调起syscfg层二状态机 */
    NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_SYSCFG);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTafPlmnSpecialReq_PlmnSelection_WaitCsPsRegRsltInd
 功能描述  : MMC处理MSCC请求的指定搜网消息
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月04日
    作    者   : s46746
    修改内容   : 新生成函数
  2.日    期   : 2011年7月14日
    作    者   : l00130025
    修改内容   : PhaseII修改,PlmnSelection状态机调整
  3.日    期   : 2011年12月31日
    作    者   : w00166186
    修改内容   : DTS2011082902017,ON PLMN下注册被拒,搜网状态机重复搜索该网络
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTafPlmnSpecialReq_PlmnSelection_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSrchList   = VOS_NULL_PTR;

    /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, begin*/
    MSCC_MMC_PLMN_SPECIAL_REQ_STRU                          *pstUserSelReqMsg  = VOS_NULL_PTR;
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, end*/

    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsRegCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enPsRegCause;

    /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, begin*/
    pstUserSelReqMsg    = (MSCC_MMC_PLMN_SPECIAL_REQ_STRU*)pstMsg;
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, end*/

    /* 保存手动搜网信息 */
    NAS_MMC_UpdateUserSpecPlmnSearchInfo_PlmnSelection((NAS_MML_PLMN_ID_STRU*)(&pstUserSelReqMsg->stPlmnId),
                                                       pstUserSelReqMsg->enAccessMode);

    /* 获取选网列表 */
    pstPlmnSrchList = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();

    /* 根据用户指定搜网场景重新初始化选网列表, 目前只有当前注册网络与指定搜索网络相同时，才会走到这一步 */
    NAS_MMC_InitPlmnSelectionList(NAS_MMC_PLMN_SEARCH_SCENE_USER_SPEC_PLMN_SEARCH,
                                  VOS_NULL_PTR,
                                  pstPlmnSrchList);

    /* 将用户指定接入技术的网络(也是当前网络)更新为已搜索注册避免重复注册 */
    NAS_MMC_UpdatePlmnNetStatusInPlmnSelectionList(NAS_MMC_GetUserSpecPlmnId(),
                                                   NAS_MMC_NET_STATUS_SEARCHED_REGISTERED,
                                                   pstPlmnSrchList);

    enCsRegCause = NAS_MMC_GetCsRegCause_PlmnSelection();
    enPsRegCause = NAS_MMC_GetPsRegCause_PlmnSelection();

    if (VOS_TRUE == NAS_MMC_ProcUserSearchRegRslt_PlmnSelection(enCsRegCause, enPsRegCause))
    {
        return VOS_TRUE;
    }

    /* 保存入口消息 */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcSyscfgRsltCnf_PlmnSelection_WaitCsPsRegRsltInd
 功能描述  : 处理SYSCFG状态机返回的结果
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月20日
   作    者   : L00171473
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmcSyscfgRsltCnf_PlmnSelection_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmAbortInd_PlmnSelection_WaitCsPsRegRsltInd
 功能描述  : 处理MM的 Abort 消息
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年7月12日
   作    者   : s00217060
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmAbortInd_PlmnSelection_WaitCsPsRegRsltInd(
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
    if ((NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME != (pstMmAbortInd->enAbortCause))
     && (NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE != (pstMmAbortInd->enAbortCause)))
    {
        return VOS_TRUE;
    }

    /* 如果原因值#6，设置CS Addition为Anycell驻留 */
    if (NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME == pstMmAbortInd->enAbortCause)
    {
        NAS_MMC_SetCsRegAdditionalAction_PlmnSelection(NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL);
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

/* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-8, begin */
/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMsccImsVoiceCapInd_PlmnSelection_WaitCsPsRegRsltInd
 功能描述  : 处理MSCC的IMS VOICE不可用的消息
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年2月8日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMsccImsVoiceCapInd_PlmnSelection_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* GU下收到IMS VOICE是否可用目前暂不处理
       对于异系统过程中收到的IMS VOICE是否可用的场景由于可能是异系统导致的IMS VOICE
       不可用,此时用来决定disable L模不准确,暂不考虑该场景 */

    return VOS_TRUE;
}
/* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-8, end */


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitRrcConnRelInd
 功能描述  : 在等待链接释放的时候收到QUIT消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年4月20日
   作    者   : z40661
   修改内容   : 新生成函数

 2.日    期   : 2011年11月29日
   作    者   : w00167002
   修改内容   : DTS2011112301233:增加打断事件ID，状态机可以知道是什么事件
                打断自己的。
                修改原因:用户下发关机命令后，当前可能在等注册结果或者在等连接
                释放，可能需要比较久的时间才能处理关机命令，通过增加打断事件，
                如归当前在等注册结果或者等链接释放状态，若收到关机命令，则直接
                退出当前状态机，处理用户的关机命令。
 3.日    期   : 2011年12月14日
   作    者   : w00176964
   修改内容   : V7R1 phaseIV 调整:驻留标记通过新的搜网控制上下文代替

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ABORT_FSM_STRU             *pstAbortMsg = VOS_NULL_PTR;

    pstAbortMsg = (NAS_MMC_ABORT_FSM_STRU*)pstMsg;

    /* 若打断类型是用户请求的关机，则直接退出等链接释放结果状态机 */
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, begin*/
    if (NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_OFF_REQ) == pstAbortMsg->ulEventType)
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, end*/
    {
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);

        /* 回复状态机退出成功 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 记录 Abort标志 */
    NAS_MMC_SetAbortFlag_PlmnSelection(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGmmSignalingStatusInd_PlmnSelection_WaitRrcConnRelInd
 功能描述  : MMCGMM_SIGNALING_STATUS_IND链接消息处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年4月20日
   作    者   : luokaihui / l00167671
   修改内容   : 新生成函数
 2.日    期   : 2011年7月22日
   作    者   : L00171473
   修改内容   : PhaseII修改,PlmnSelection状态机调整
 3.日    期   : 2011年12月14日
   作    者   : w00176964
   修改内容   : V7R1 phaseIV 调整:驻留标记通过新的搜网控制上下文代替
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvGmmSignalingStatusInd_PlmnSelection_WaitRrcConnRelInd(
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

    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection() )
    {
        /* 向上层状态机指示选网ABORT */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 如果信令连接不存在而且不是主动释放连接则进行附加操作 */
    if (VOS_FALSE == NAS_MMC_GetRelRequestFlag_PlmnSelection())
    {
        NAS_MMC_PerformAdditionalActionConnRel_PlmnSelection();
    }
    else
    {
        NAS_MMC_SetRelRequestFlag_PlmnSelection(VOS_FALSE);

        NAS_MMC_SearchNextPlmn_PlmnSelection();
    }


    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGmmNetworkDetachInd_PlmnSelection_WaitRrcConnRelInd
 功能描述  : 等待连接释放过程中收到网络的detach消息
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年5月24日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数
 2.日    期   : 2011年7月11日
   作    者   : lijun 00171473
   修改内容   : 调用函数修改 for V7R1 phase II
 3.日    期   : 2011年11月14日
   作    者   : w00167002
   修改内容   : DTS2011110907180:当前若为选网状态机，则添加禁止网络信息
                到选网状态机的禁止漫游LA变量里去
 4.日    期   : 2011年12月5日
   作    者   : z00161729
   修改内容   : V7R1 Phase IV调整,当前SYSCFG中L不在时，也需要向LMM通知ID_MMC_LMM_ACTION_RESULT_REQ
 5.日    期   : 2012年2月13日
   作    者   : w00167002
   修改内容   : DTS2011122704039:additional action值若为无效值NAS_MMC_ADDITIONAL_ACTION_BUTT
                 则不更新当前的additional action
 6.日    期   : 2012年12月11日
   作    者   : l00167671
   修改内容   : DTS2012121802573, TQE清理
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvGmmNetworkDetachInd_PlmnSelection_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMCGMM_NETWORK_DETACH_IND_STRU     *pstDetachMsg = VOS_NULL_PTR;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enAdditionalAction;

    NAS_MMC_FSM_ID_ENUM_UINT32                              enCurrentFsmId;
    VOS_UINT32                                              ulCurrentEventType;

    pstDetachMsg = (MMCGMM_NETWORK_DETACH_IND_STRU *)pstMsg;

    enAdditionalAction = NAS_MMC_ProcGmmNetworkDetachInd(pstDetachMsg);

    /* AdditionalAction有效，更新PS的下一步的动作类型 */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enAdditionalAction )
    {
        NAS_MMC_SetPsRegAdditionalAction_PlmnSelection(enAdditionalAction);
    }

    /* 记录Ps 的注册结果 */
    NAS_MMC_SetPsRegCause_PlmnSelection((NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16)pstDetachMsg->ulDetachCause);


    /* 若被拒原因值为#15, 则添加禁止网络信息到选网状态机的禁止漫游LA变量里去,
       当用户指定搜网时，则需要把禁止LA带给接入层 */
    enCurrentFsmId     = NAS_MMC_GetCurrFsmId();
    if (NAS_MMC_FSM_PLMN_SELECTION != enCurrentFsmId)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }
   ulCurrentEventType = NAS_MMC_GetCurrFsmEventType();
    if ( (VOS_TRUE == NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enCurrentFsmId, ulCurrentEventType))
      && (NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL == pstDetachMsg->ulDetachCause) )
    {
        NAS_MML_AddForbRoamLa( NAS_MML_GetCurrCampLai(),
                               NAS_MMC_GetForbRoamLaInfo_PlmnSelection() );
    }


#if   (FEATURE_ON == FEATURE_LTE)
    /* 给LMM发送detach结果消息 */
    NAS_MMC_SndLmmMtDetachIndActionResultReq(pstDetachMsg->ulDetachType,
        (NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16)pstDetachMsg->ulDetachCause);
#endif

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGmmServiceRequestResultInd_PlmnSelection_WaitRrcConnRelInd
 功能描述  : 等待连接释放过程中收到ServiceRequestResultInd的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月15日
   作    者   : L00171473
   修改内容   : 新生成函数

 2.日    期   : 2011年11月14日
   作    者   : w00167002
   修改内容   : DTS2011110907180:当前若为选网状态机，则添加禁止网络信息
                到选网状态机的禁止漫游LA变量里去
 3.日    期   : 2011年12月5日
   作    者   : z00161729
   修改内容   : V7R1 Phase IV调整,当前SYSCFG中L不在时，也需要向LMM通知ID_MMC_LMM_ACTION_RESULT_REQ

 4.日    期   : 2012年2月13日
   作    者   : w00167002
   修改内容   : DTS2011122704039:additional action值若为无效值NAS_MMC_ADDITIONAL_ACTION_BUTT
                 则不更新当前的additional action
 5.日    期   : 2012年12月11日
   作    者   : l00167671
   修改内容   : DTS2012121802573, TQE清理

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvGmmServiceRequestResultInd_PlmnSelection_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    GMMMMC_SERVICE_REQUEST_RESULT_IND_STRU                 *pstServiceRsltInd = VOS_NULL_PTR;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;

    NAS_MMC_FSM_ID_ENUM_UINT32                              enCurrentFsmId;
    VOS_UINT32                                              ulCurrentEventType;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_GU_ACTION_RSLT_INFO_STRU                        stActionRslt;
#endif

    pstServiceRsltInd = (GMMMMC_SERVICE_REQUEST_RESULT_IND_STRU*)pstMsg;

    /* 根据Service Reqest Result 更新做不同处理 */
    if (GMM_MMC_ACTION_RESULT_SUCCESS == pstServiceRsltInd->enActionResult)
    {
        /* 更新服务状态 */
        enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;
        NAS_MMC_SetPsRegCause_PlmnSelection(NAS_MML_REG_FAIL_CAUSE_NULL);

#if (FEATURE_ON == FEATURE_LTE)
        /* 给LMM发送Service requestResult结果消息处理 */
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

        NAS_MMC_SetPsRegCause_PlmnSelection(pstServiceRsltInd->enRegFailCause);


        /* 若被拒原因值为#15, 则添加禁止网络信息到选网状态机的禁止漫游LA变量里去,
           当用户指定搜网时，则需要把禁止LA带给接入层 */
        enCurrentFsmId     = NAS_MMC_GetCurrFsmId();
        if (NAS_MMC_FSM_PLMN_SELECTION != enCurrentFsmId)
        {
            NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
        }
        ulCurrentEventType = NAS_MMC_GetCurrFsmEventType();
        if ( (VOS_TRUE == NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enCurrentFsmId, ulCurrentEventType))
          && (NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL == pstServiceRsltInd->enRegFailCause) )
        {
            NAS_MML_AddForbRoamLa( NAS_MML_GetCurrCampLai(),
                                   NAS_MMC_GetForbRoamLaInfo_PlmnSelection() );
        }

#if (FEATURE_ON == FEATURE_LTE)

        /* 给LMM发送Service requestResult结果消息处理 */
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
        NAS_MMC_SetPsRegAdditionalAction_PlmnSelection(enAdditionalAction);
    }

    return VOS_TRUE;
}

/*************************************?****************************************
 函 数 名  : NAS_MMC_RcvMmConnInfoInd_PlmnSelection_WaitRrcConnRelInd
 功能描述  : MMCMM_RR_CONN_INFO_IND链接消息处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年4月20日
   作    者   : luokaihui / l00167671
   修改内容   : 新生成函数
 2.日    期   : 2011年7月22日
   作    者   : L00171473
   修改内容   : PhaseII修改,PlmnSelection状态机调整
 3.日    期   : 2011年12月14日
   作    者   : w00176964
   修改内容   : V7R1 phaseIV 调整:驻留标记通过新的搜网控制上下文代替
*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvMmConnInfoInd_PlmnSelection_WaitRrcConnRelInd(
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

    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection() )
    {
        /* 回复状态机退出成功 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 如果信令连接不存在而且不是主动释放连接则进行附加操作 */
    if (VOS_FALSE == NAS_MMC_GetRelRequestFlag_PlmnSelection())
    {
        NAS_MMC_PerformAdditionalActionConnRel_PlmnSelection();
    }
    else
    {
        NAS_MMC_SetRelRequestFlag_PlmnSelection(VOS_FALSE);

        NAS_MMC_SearchNextPlmn_PlmnSelection();
    }


    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmRrRelInd_PlmnSelection_WaitRrcConnRelInd
 功能描述  : MMCMM_RR_CONN_INFO_IND链接消息处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年5月24日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数
 2.日    期   : 2011年7月22日
   作    者   : L00171473
   修改内容   : PhaseII修改,PlmnSelection状态机调整
 3.日    期   : 2011年12月14日
   作    者   : w00176964
   修改内容   : V7R1 phaseIV 调整:驻留标记通过新的搜网控制上下文代替
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmRrRelInd_PlmnSelection_WaitRrcConnRelInd(
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

    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection() )
    {
        /* 向上层状态机指示选网ABORT */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 如果信令连接不存在而且不是主动释放连接则进行附加操作 */
    if (VOS_FALSE == NAS_MMC_GetRelRequestFlag_PlmnSelection())
    {
        NAS_MMC_PerformAdditionalActionConnRel_PlmnSelection();
    }
    else
    {
        NAS_MMC_SetRelRequestFlag_PlmnSelection(VOS_FALSE);

        NAS_MMC_SearchNextPlmn_PlmnSelection();
    }


    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmRelInd_PlmnSelection_WaitRrcConnRelInd
 功能描述  : RRMM_REL_IND处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月20日
    作    者   : luokaihui / l00167671
    修改内容   : 新生成函数
  2.日    期   : 2011年7月22日
    作    者   : L00171473
    修改内容   : PhaseII修改,PlmnSelection状态机调整
  3.日    期   : 2011年12月14日
    作    者   : w00176964
    修改内容   : V7R1 phaseIV 调整:驻留标记通过新的搜网控制上下文代替
*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvRrMmRelInd_PlmnSelection_WaitRrcConnRelInd(
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

    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection() )
    {
        /* 向上层状态机指示选网ABORT */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 如果信令连接不存在而且不是主动释放连接则进行附加操作 */
    if (VOS_FALSE == NAS_MMC_GetRelRequestFlag_PlmnSelection())
    {
        NAS_MMC_PerformAdditionalActionConnRel_PlmnSelection();
    }
    else
    {
        NAS_MMC_SetRelRequestFlag_PlmnSelection(VOS_FALSE);

        NAS_MMC_SearchNextPlmn_PlmnSelection();
    }


    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGmmTbfRelInd_PlmnSelection_WaitRrcConnRelInd
 功能描述  : 处理TBF连接消息
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年4月20日
   作    者   : luokaihui / l00167671
   修改内容   : 新生成函数
 2.日    期   : 2011年7月22日
   作    者   : L00171473
   修改内容   : PhaseII修改,PlmnSelection状态机调整
 3.日    期   : 2011年12月14日
   作    者   : w00176964
   修改内容   : V7R1 phaseIV 调整:驻留标记通过新的搜网控制上下文代替
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvGmmTbfRelInd_PlmnSelection_WaitRrcConnRelInd(
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

    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection() )
    {
        /* 向上层状态机指示选网ABORT */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 如果信令连接不存在而且不是主动释放连接则进行附加操作 */
    if (VOS_FALSE == NAS_MMC_GetRelRequestFlag_PlmnSelection())
    {
        NAS_MMC_PerformAdditionalActionConnRel_PlmnSelection();
    }
    else
    {
        NAS_MMC_SetRelRequestFlag_PlmnSelection(VOS_FALSE);

        NAS_MMC_SearchNextPlmn_PlmnSelection();
    }


    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvWasSuspendInd_PlmnSelection_WaitRrcConnRelInd
 功能描述  : WAS上报的SUSPEND_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年4月20日
   作    者   : W00167002
   修改内容   : 新生成函数
 2.日    期   : 2011年7月11日
   作    者   : L00171473
   修改内容   : 根据不同的挂起原因启不同的状态机

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvWasSuspendInd_PlmnSelection_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    RRMM_SUSPEND_IND_ST                *pstSuspendMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulRelRequestFlg;

    pstSuspendMsg = (RRMM_SUSPEND_IND_ST*)pstMsg;

    ulRelRequestFlg = NAS_MMC_GetRelRequestFlag_PlmnSelection();

    /* 如果是主动释放或者已经接收到Abort消息,则不允许进行异系统重选 */
    if ((VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
     || (VOS_TRUE == ulRelRequestFlg)
     || (MMC_SUSPEND_CAUSE_PLMNSEARCH == pstSuspendMsg->ucSuspendCause)
     || (MMC_SUSPEND_CAUSE_BUTT <= pstSuspendMsg->ucSuspendCause))
    {
        NAS_MMC_SndAsSuspendRsp(RRC_NAS_SUSPEND_FAILURE, WUEPS_PID_WRR);
    }
    else
    {
        NAS_MMC_LoadInterSysFsm_PlmnSelection(pstSuspendMsg->ucSuspendCause);
    }


    return VOS_TRUE;
}
/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGasSuspendInd_PlmnSelection_WaitRrcConnRelInd
 功能描述  : GAS上报的SUSPEND_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年4月20日
   作    者   : W00167002
   修改内容   : 新生成函数
 2.日    期   : 2011年7月11日
   作    者   : L00171473
   修改内容   : 根据不同的挂起原因启不同的状态机

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvGasSuspendInd_PlmnSelection_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    RRMM_SUSPEND_IND_ST                *pstSuspendMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulRelRequestFlg;

    pstSuspendMsg = (RRMM_SUSPEND_IND_ST*)pstMsg;

    ulRelRequestFlg = NAS_MMC_GetRelRequestFlag_PlmnSelection();

    /* 如果是主动释放或者已经接收到Abort消息,则不允许进行异系统重选 */
    if ((VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
     || (VOS_TRUE == ulRelRequestFlg)
     || (MMC_SUSPEND_CAUSE_PLMNSEARCH == pstSuspendMsg->ucSuspendCause)
     || (MMC_SUSPEND_CAUSE_BUTT <= pstSuspendMsg->ucSuspendCause))

    {
        NAS_MMC_SndAsSuspendRsp(RRC_NAS_SUSPEND_FAILURE, UEPS_PID_GAS);
    }
    else
    {
        NAS_MMC_LoadInterSysFsm_PlmnSelection(pstSuspendMsg->ucSuspendCause);
    }


    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcSuspendRslt_PlmnSelection_WaitRrcConnRelInd
 功能描述  : 挂起状态机结果处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月04日
   作    者   : sunxibo / 46746
   修改内容   : 新生成函数
 2.日    期   : 2011年7月22日
   作    者   : L00171473
   修改内容   : PhaseII修改,PlmnSelection状态机调整
 3.日    期   : 2011年12月30日
   作    者   : l65478
   修改内容   : 在迁到L模时,不立刻把CS设置成可选搜网,而是等待PS注册结果时
                根据具体的原因值再设置

 4.日    期   : 2011年12月14日
   作    者   : w00176964
   修改内容   : V7R1 phaseIV 调整:驻留标记通过新的搜网控制上下文代替
 5.日    期   : 2013年2月7日
   作    者   : W00176964
   修改内容   : Volte_phase3项目调整:增加IMS不可用时disable L模的逻辑修改
 6.日    期   : 2013年4月9日
   作    者   : y00176023
   修改内容   : DSDS GUNAS II项目:收到NO RF 退状态机，发送失败迁移到ooc
 7.日    期   : 2014年6月30日
   作    者   : b00269685
   修改内容   : DSDS GUNAS III项目:修改函数名称

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmcSuspendRslt_PlmnSelection_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
#if (FEATURE_LTE == FEATURE_ON)

    NAS_MMCMMC_SUSPEND_RSLT_STRU       *pstSuspendRsltMsg = VOS_NULL_PTR;

    pstSuspendRsltMsg = (NAS_MMCMMC_SUSPEND_RSLT_STRU*)pstMsg;

     /* 迁移到不同的接入技术时，需要迁移到不同的处理注册结果状态 */

    if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        /* 停止当前等待CS/PS连接释放的状态 */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);

        /* GU handover 到 L 成功后，可能很长时间无法收到系统消息，转到L1处理  */
        if ((NAS_MMC_SUSPEND_SUCCESS == pstSuspendRsltMsg->enRslt)
         && (MMC_SUSPEND_CAUSE_HANDOVER == pstSuspendRsltMsg->enSuspendCause))
        {
            /* 回复状态机退出成功 */
            NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_SUCC);

            /* 直接退出当前状态机 */
            NAS_MMC_FSM_QuitFsmL2();

            return VOS_TRUE;
        }

        /* 更新当前等待EPS的注册结果 */
        NAS_MMC_ClearAllWaitRegRsltFlag_PlmnSelection();
        NAS_MMC_SetWaitRegRsltFlag_PlmnSelection(NAS_MMC_WAIT_REG_RESULT_IND_PS);

        /* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-7, begin */
#if (FEATURE_ON == FEATURE_IMS)
        /* 增加等待IMS是否可用结果FLG,MMA保证收到PS注册结果上报IMS是否可用指示到MMC */
        NAS_MMC_SetWaitRegRsltFlag_PlmnSelection(NAS_MMC_WAIT_REG_RESULT_IND_IMS);
#endif
        /* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-7, end */

        /* 更新CS的注册Cause和AdditionalAction */
        NAS_MMC_SetCsRegCause_PlmnSelection(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);
        NAS_MMC_SetCsRegAdditionalAction_PlmnSelection(NAS_MMC_ADDITIONAL_ACTION_BUTT);
        NAS_MMC_SetPsRegAdditionalAction_PlmnSelection(NAS_MMC_ADDITIONAL_ACTION_BUTT);

        /* 迁移到等待注册结果子状态PLMN_SRCH:NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_REG_IND, TI_NAS_MMC_WAIT_EPS_REG_IND_LEN);

        return VOS_TRUE;
    }

#endif

    /*  如果存在信令连接，则继续等待  */
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        return VOS_TRUE;
    }

    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);

    if (VOS_FALSE == NAS_MML_GetRfAvailFlg())
    {
        /* 状态机退出结果为失败，迁移到OOC */
        NAS_MMC_ProcNoRf_PlmnSelection(NAS_MML_GetCurrNetRatType());

        return VOS_TRUE;
    }

    /* 在重选之前已经判断,此时不可能存在Abort或者主动释放,如果信令连接不存在可能发起搜网 */
    NAS_MMC_PerformAdditionalActionConnRel_PlmnSelection();

   /* 与Intersys状态机的配合待后续补充
    switch (pstSuspendRsltMsg->enRslt)
    {
        case NAS_MMC_SUSPEND_SUCCESS:
        break;

        case NAS_MMC_SUSPEND_FAIL :
        case NAS_MMC_SUSPEND_QUIT :

        break;

        case NAS_MMC_SUSPEND_AREA_LOST :
        break;

        default:

        break;
    }
    */




    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvWasSysInfoInd_PlmnSelection_WaitRrcConnRelInd
 功能描述  : 等待连接释放状态收到W系统消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月15日
   作    者   : L00171473
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

 5.日    期   : 2014年1月18日
   作    者   : z00234330
   修改内容   : dts2014011801513,接入层上报的系统消息里面有可能没有携带plmnid,
                 此处判断并没有判断plmnid是否有效

 6.日    期   : 2014年5月4日
   作    者   : t00173447
   修改内容   : DTS2014042105390,软银定制需求
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvWasSysInfoInd_PlmnSelection_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU         stOldCampInfo;
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

#endif
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, end */

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    PS_MEM_SET(&stOldCsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_SET(&stOldPsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

    /* 如果是主动请求释放,由于需要立即进行搜网,系统消息不处理 */
    if (VOS_TRUE == NAS_MMC_GetRelRequestFlag_PlmnSelection())
    {
        return VOS_TRUE;
    }

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

    /* Added by t00212959 for DCM定制需求和遗留问题, 2012-8-25, begin */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_RcvGuSysInfoIndSetLteAbility(pstMsg,enLCapabilityStatus);
#endif
    /* Added by t00212959 for DCM定制需求和遗留问题, 2012-8-25, end */

    /* 驻留小区变化时，上报系统消息 */
    if (VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
    {
        /* 主动上报 */
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, begin*/
        NAS_MMC_SndMsccSysInfo();
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, end*/

    }

    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
    /* 驻留小区的接入受限信息变化时,通知MMA模块当前接入受限信息 */
    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldCsRestrictInfo, pstCurCsRestrictInfo))
    {
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, begin*/
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_CS, pstCurCsRestrictInfo);
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, end*/
    }

    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldPsRestrictInfo, pstCurPsRestrictInfo))
    {
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, begin*/
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_PS, pstCurPsRestrictInfo);
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, end*/
    }
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, end */

    /* 状态更新为当前已经驻留 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))

    /* CBS上报*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_WCDMA);
#endif

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, end */

    /*转发系统消息通知 给 MM/GMM,并将当前系统消息的 Forbidden 类型携带过去 */
    NAS_MMC_SndMmWasSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenType(), VOS_FALSE, pstMsg);
    NAS_MMC_SndGmmWasSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenType(), VOS_FALSE, pstMsg);

#if (FEATURE_ON == FEATURE_LTE)

    NAS_MMC_SndLmmWcdmaSysInfoInd(pstMsg);
#endif

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGasSysInfoInd_PlmnSelection_WaitRrcConnRelInd
 功能描述  : 等待连接释放状态收到G系统消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月15日
   作    者   : L00171473
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
 5.日    期   : 2013年11月01日
   作    者   : l00208543
   修改内容   : 根据卡类型禁止网络制式

 6.日    期   : 2014年5月4日
   作    者   : t00173447
   修改内容   : DTS2014042105390,软银定制需求
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvGasSysInfoInd_PlmnSelection_WaitRrcConnRelInd(
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
#endif
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, end */

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    PS_MEM_SET(&stOldCsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_SET(&stOldPsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

    /* 如果收到GAS的系统消息，且目前Utran被Enable，则重新Disable Utran */
    NAS_MMC_RcvGasSysInfoSetUtranCapabilityStatus();

    /* 如果是主动请求释放,由于需要立即进行搜网,系统消息不处理 */
    if (VOS_TRUE == NAS_MMC_GetRelRequestFlag_PlmnSelection())
    {
        return VOS_TRUE;
    }

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

    /* Added by t00212959 for DCM定制需求和遗留问题, 2012-8-25, begin */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_RcvGuSysInfoIndSetLteAbility(pstMsg, enLCapabilityStatus);
#endif
    /* Added by t00212959 for DCM定制需求和遗留问题, 2012-8-25, end */

    /* 驻留小区变化时，上报系统消息 */
    if (VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
    {
        /* 主动上报 */
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, begin*/
        NAS_MMC_SndMsccSysInfo();
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, end*/

    }

    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
    /* 驻留小区的接入受限信息变化时,通知MMA模块当前接入受限信息 */
    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldCsRestrictInfo, pstCurCsRestrictInfo))
    {
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, begin*/
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_CS, pstCurCsRestrictInfo);
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, end*/
    }

    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldPsRestrictInfo, pstCurPsRestrictInfo))
    {
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, begin*/
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_PS, pstCurPsRestrictInfo);
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, end*/
    }
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, end */

    /* 状态更新为当前已经驻留 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))

    /* CBS上报*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_GSM);
#endif

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, end */

    /*转发系统消息通知 给 MM/GMM,并将当前系统消息的 Forbidden 类型携带过去 */
    NAS_MMC_SndMmGsmSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenType(), VOS_FALSE, pstMsg);
    NAS_MMC_SndGmmGsmSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenType(), VOS_FALSE, pstMsg);

#if (FEATURE_ON == FEATURE_LTE)

    NAS_MMC_SndLmmGsmSysInfoInd(pstMsg);
#endif

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitRrcConnRelExpired_PlmnSelection_WaitRrcConnRelInd
 功能描述  : 链接释放状态超时处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年4月20日
   作    者   : luokaihui / l00167671
   修改内容   : 新生成函数
 2.日    期   : 2011年7月22日
   作    者   : L00171473
   修改内容   : PhaseII修改,PlmnSelection状态机调整
 3.日    期   : 2011年11月25日
   作    者   : w00166186
   修改内容   : DTS2011112308343,G下pdp激活后，丢网后到W注册PS成功，CS13拒绝，PS链路不释放
                后续释放后，没有搜网。
 4.日    期   : 2011年12月1日
   作    者   : w00176964
   修改内容   : GUNAS V7R1 PhaseIV 阶段调整
 5.日    期   : 2011年12月14日
   作    者   : w00176964
   修改内容   : V7R1 phaseIV 调整:驻留标记通过新的搜网控制上下文代替
 6.日    期   : 2012年06月02日
   作    者   : sunxibo /46746
   修改内容   : Added for V7R1 C50 CS/PS mode 1
 7.日    期   : 2013年8月27日
   作    者   : l00208543
   修改内容   : Coverity
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitRrcConnRelExpired_PlmnSelection_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulCsServiceStatusFlg;
    VOS_UINT32                          ulCsEmergencyServiceFlg;
    NAS_MML_PLMN_WITH_RAT_STRU          stDestPlmn;

    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitRrcConnRelExpired_PlmnSelection_WaitRrcConnRelInd ENTERED");

    /* 解决版本Coverity问题 */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));


    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection() )
    {
        /* 向上层状态机指示选网ABORT */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 如果信令连接存在, 而且是主动释放连接,则进行搜网动作 */
    if (VOS_TRUE == NAS_MMC_GetRelRequestFlag_PlmnSelection())
    {
        NAS_MMC_SetRelRequestFlag_PlmnSelection(VOS_FALSE);

        NAS_MMC_SearchNextPlmn_PlmnSelection();

        return VOS_TRUE;
    }

    /*
    Connrel 被动释放，
    判断是否有业务，有，则退出 (正常服务，返回成功，受限服务，返回失败)
    否则，获取下一个网络成功，发主动释放，置标志位，失败则退出
    */
    ulCsServiceStatusFlg    = NAS_MML_GetCsServiceExistFlg();
    ulCsEmergencyServiceFlg = NAS_MML_GetCsEmergencyServiceFlg();
    if ( (VOS_TRUE == ulCsServiceStatusFlg)
      && (VOS_TRUE == ulCsEmergencyServiceFlg))
    {
        /* 回复状态机搜网失败 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);

        /* 退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();
    }
    else
    {
        /* 获取下个网络，如果成功则主动释放，否则退出 */
        if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
        {
            /* 根据当前不同的接入技术,发送释放请求,迁移到不同的等待连接释放的L2状态，并启动保护定时器 */
            NAS_MMC_SndRelReq_PlmnSelection(NAS_MML_GetCurrNetRatType());
        }
        else
        {
            NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

            NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();
        }
    }


    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTafSysCfgReq_PlmnSelection_WaitRrcConnRelInd
 功能描述  : MMC处理MSCC请求的SYSCFG设置消息
 输入参数  : ulEventType:消息类型
             pstMsg:SYSCFG设置消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月04日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTafSysCfgReq_PlmnSelection_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 直接调起syscfg层二状态机 */
    NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_SYSCFG);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTafPlmnSpecialReq_PlmnSelection_WaitRrcConnRelInd
 功能描述  : 处理MSCC发送的用户指定搜请求,用户指定的PlmnId及RAT和当前驻留的PlmnId
             及RAT相同，才会进入该处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月11日
   作    者   : L00171473
   修改内容   : 新生成函数
 2.日    期   : 2011年12月31日
   作    者   : w00166186
   修改内容   : DTS2011082902017,ON PLMN下注册被拒,搜网状态机重复搜索该网络
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTafPlmnSpecialReq_PlmnSelection_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, begin*/
    MSCC_MMC_PLMN_SPECIAL_REQ_STRU                          *pstUserSelReqMsg  = VOS_NULL_PTR;
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, end*/

    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSrchList   = VOS_NULL_PTR;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enPsCause;

    /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, begin*/
    pstUserSelReqMsg    = (MSCC_MMC_PLMN_SPECIAL_REQ_STRU*)pstMsg;
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, end*/


    /* 保存手动搜网信息 */
    NAS_MMC_UpdateUserSpecPlmnSearchInfo_PlmnSelection((NAS_MML_PLMN_ID_STRU*)(&pstUserSelReqMsg->stPlmnId),
                                                       pstUserSelReqMsg->enAccessMode);

    /* 获取选网列表 */
    pstPlmnSrchList = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();

    /* 根据用户指定搜网场景重新初始化选网列表 */
    NAS_MMC_InitPlmnSelectionList(NAS_MMC_PLMN_SEARCH_SCENE_USER_SPEC_PLMN_SEARCH,
                                  VOS_NULL_PTR,
                                  pstPlmnSrchList);

    /* 将用户指定接入技术的网络(也是当前网络)更新为已搜索注册避免重复注册 */
    NAS_MMC_UpdatePlmnNetStatusInPlmnSelectionList(NAS_MMC_GetUserSpecPlmnId(),
                                                   NAS_MMC_NET_STATUS_SEARCHED_REGISTERED,
                                                   pstPlmnSrchList);

    enCsCause = NAS_MMC_GetCsRegCause_PlmnSelection();
    enPsCause = NAS_MMC_GetPsRegCause_PlmnSelection();

    /* 根据保存的CS/PS注册结果判断指定搜网处理是否已结束 */
    if (VOS_TRUE == NAS_MMC_ProcUserSearchRegRslt_PlmnSelection(enCsCause, enPsCause))
    {
        return VOS_TRUE;
    }

    /* 因为目前状态机更新为手动搜网流程,需要保存入口消息 , 目前应该用不到*/
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcSyscfgRsltCnf_PlmnSelection_WaitRrcConnRelInd
 功能描述  : 等待连接释放状态处理SYSCFG状态机返回的结果
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月20日
   作    者   : L00171473
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmcSyscfgRsltCnf_PlmnSelection_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMmcSyscfgRsltCnf_PlmnSelection_WaitRrcConnRelInd: ENTERED. ");
    return VOS_TRUE;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_RcvCmServiceRejectInd_PlmnSelection_WaitRrcConnRelInd
 功能描述  : 等待连接释放状态时收到CS业务导致卡无效的消息(MMCMM_CM_SERVICE_REJECT_IND)
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月13日
   作    者   : L00171473
   修改内容   : 新生成函数
 2.日    期   : 2011年12月5日
   作    者   : z00161729
   修改内容   : V7R1 Phase IV调整,当前SYSCFG中L不在时，也需要向LMM通知ID_MMC_LMM_ACTION_RESULT_REQ

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvCmServiceRejectInd_PlmnSelection_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMCMM_CM_SERVICE_REJECT_IND_STRU   *pstRcvMsg = VOS_NULL_PTR;
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_GU_ACTION_RSLT_INFO_STRU    stActionRslt;
#endif

    pstRcvMsg = (MMCMM_CM_SERVICE_REJECT_IND_STRU*)pstMsg;

#if (FEATURE_ON == FEATURE_LTE)
    stActionRslt.enProcType     = NAS_MML_PROC_CM_SER;
    stActionRslt.enRegRst       = NAS_MML_REG_RESULT_FAILURE;
    stActionRslt.enReqDomain    = NAS_MMC_REG_DOMAIN_CS;
    stActionRslt.enRstDomain    = NAS_MMC_REG_DOMAIN_CS;
    stActionRslt.enCnCause      = (NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16)pstRcvMsg->ulCause;
    stActionRslt.ulAttemptCount = 0;

    NAS_MMC_SndLmmRegActionResultReq(&stActionRslt);

#endif

    /* 对#6做特殊处理时 */
    if (NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME == pstRcvMsg->ulCause)
    {
        /* 设置新的enCsAdditioalAction，*/
        NAS_MMC_SetCsRegAdditionalAction_PlmnSelection(NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL);

    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGmmPsRegResultInd_PlmnSelection_WaitRrcConnRelInd
 功能描述  : 等待连接释放状态下PS域注册、RAU结果的处理入口函数
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月12日
    作    者   : l00130025
    修改内容   : 新生成函数

*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvGmmPsRegResultInd_PlmnSelection_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    GMMMMC_PS_REG_RESULT_IND_STRU      *pstPsRegRslt = VOS_NULL_PTR;

    pstPsRegRslt = (GMMMMC_PS_REG_RESULT_IND_STRU*)pstMsg;

    /* 针对CCO失败回退过程中收到的异系统的注册结果，不需要处理 */
    if (pstPsRegRslt->enNetType != NAS_MML_GetCurrNetRatType())
    {
        return VOS_TRUE;
    }

    /* 根据注册结果做对应处理: 设置服务状态，记录Cause值，设置下一步动作类型，通知对应结果 */
    NAS_MMC_ProcPsRegRslt_PlmnSelection(pstPsRegRslt);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmCsRegResultInd_PlmnSelection_WaitRrcConnRelInd
 功能描述  : 等待连接释放状态下LU结果(成功、失败)处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月20日
    作    者   : luokaihui / l00167671
    修改内容   : 新生成函数
  2.日    期   : 2011年7月14日
    作    者   : l00130025
    修改内容   : PhaseII修改,PlmnSelection状态机调整
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmCsRegResultInd_PlmnSelection_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMMMC_CS_REG_RESULT_IND_STRU       *pstCsRegRslt;

    pstCsRegRslt = (MMMMC_CS_REG_RESULT_IND_STRU*)pstMsg;

    /* 针对CCO失败回退过程中收到的异系统的注册结果，不需要处理 */
    if (pstCsRegRslt->enNetType != NAS_MML_GetCurrNetRatType())
    {
        return VOS_TRUE;
    }

    /* 根据注册结果做对应处理: 设置服务状态，记录Cause值，设置下一步动作类型，通知对应结果 */
    NAS_MMC_ProcCsRegRslt_PlmnSelection(pstCsRegRslt);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmAbortInd_PlmnSelection_WaitRrcConnRelInd
 功能描述  : 等待RRC连接释放过程中收到MM Abort消息的处理
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
VOS_UINT32 NAS_MMC_RcvMmAbortInd_PlmnSelection_WaitRrcConnRelInd(
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
        NAS_MMC_SetCsRegAdditionalAction_PlmnSelection(NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL);
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

/* Added by s00246516 for L-C互操作项目, 2014-01-28, Begin */
/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMsccRegReq_PlmnSelection_WaitMsccRegReq
 功能描述  : 等待MSCC注册请求过程中收到ID_MSCC_MMC_REG_REQ消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年1月28日
   作    者   : s00246516
   修改内容   : 新生成函数
 2.日    期   : 2014年8月1日
   作    者   : s00217060
   修改内容   : DTS2014072800477:VIA在EHRPD上搜到网给balong发送ID_CMMCA_MMC_RAT_NO_SERVICE_REQ时，
                balong刚好搜到LTE网络，等待VIA发送REG_REQ对冲场景的处理
 3.日    期   : 2015年4月22日
   作    者   : wx270776
   修改内容   : DTS2015031602665:给MSCC发送Reg CNF消息时增加CL ATTACH注册状态
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMsccRegReq_PlmnSelection_WaitMsccRegReq(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enNetRatType;
    NAS_MML_PLMN_WITH_RAT_STRU                              stDestPlmn;
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene;
    MSCC_MMC_PLMN_ID_STRU                                    stPlmnId;
    NAS_MMC_INTER_PLMN_SEARCH_REQ_STRU                     *pstInterPlmnSrchMsg = VOS_NULL_PTR;
    MSCC_MMC_REG_REQ_STRU                                   *pstRegReq = VOS_NULL_PTR;

    stPlmnId.ulMcc     = NAS_MML_INVALID_MCC;
    stPlmnId.ulMnc     = NAS_MML_INVALID_MNC;

    /* 停止保护定时器TI_NAS_MMC_WAIT_MSCC_REG_REQ */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_MSCC_REG_REQ);

    /* 如果有ABORT标志，直接退出 */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        /* 在没有打断时，才会构造内部搜网消息，搜网场景更新为REG_NCELL/REG_HPLMN/...
           所以有打断时，NAS_MMC_IsMsccRegReq_PlmnSelection不会为VOS_TRUE
           需要在这个分支里回reg_cnf */
        if (VOS_TRUE == NAS_MMC_IsNormalServiceStatus())
        {
            NAS_MMC_SndMsccRegCnf(MMC_LMM_CL_REG_STATUS_BUTT, NAS_MSCC_PIF_REG_RESULT_SUCCESS, NAS_MML_GetCurrCampPlmnId(),
                                 NAS_MML_GetCurrCampArfcn());
        }
        else
        {
            if (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING != NAS_MMC_GetSpecPlmnSearchState())
            {
                NAS_MMC_SndMsccRegCnf(NAS_MMC_GetLmmAttachClRegStatus_PlmnSelection(), NAS_MSCC_PIF_REG_RESULT_REG_FAILURE, NAS_MML_GetCurrCampPlmnId(),
                                 NAS_MML_GetCurrCampArfcn());
            }
            else
            {
                NAS_MMC_SndMsccRegCnf(NAS_MMC_GetLmmAttachClRegStatus_PlmnSelection(), NAS_MSCC_PIF_REG_RESULT_ACQ_FAILURE, &stPlmnId, 0x0);
            }
        }

        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    pstRegReq = (MSCC_MMC_REG_REQ_STRU*)pstMsg;

    /* 清除标志 */
    NAS_MMC_SetLmmAttachClRegStatus_PlmnSelection(MMC_LMM_CL_REG_STATUS_BUTT);

    /* 保存NCELL信息 */
    if (VOS_TRUE == pstRegReq->bitOpCellInfo)
    {
        NAS_MMC_SaveRegReqNCellInfo(&(pstRegReq->stCellInfo));
    }

    enPlmnSearchScene = NAS_MMC_GetPlmnSearchSceneMsccRegReq(pstRegReq);

    /* 将状态机入口消息替换为构造的内部搜网消息，后续搜到网络后可以直接发起注册 */
    pstInterPlmnSrchMsg = (NAS_MMC_INTER_PLMN_SEARCH_REQ_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC, sizeof(NAS_MMC_INTER_PLMN_SEARCH_REQ_STRU));
    if (VOS_NULL_PTR == pstInterPlmnSrchMsg)
    {
        /* 异常打印 */
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMsccRegReq_PlmnSelection_WaitMsccRegReq Alloc mem fail");

        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);

        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    NAS_MMC_BulidInterPlmnSearchReqMsg(enPlmnSearchScene, VOS_NULL_PTR, 0, pstInterPlmnSrchMsg);
    NAS_MMC_SaveCurEntryMsg(NAS_BuildEventType(WUEPS_PID_MMC, MMCMMC_INTER_PLMN_SEARCH_REQ),
                            (struct MsgCB*)pstInterPlmnSrchMsg);
    PS_MEM_FREE(WUEPS_PID_MMC, pstInterPlmnSrchMsg);

    /* 根据enPlmnSearchScene重新刷新选网列表，删除不满足优先级要求的网络 */
    NAS_MMC_RefreshPlmnSelectionListRcvMsccRegReq_PlmnSelection(enPlmnSearchScene);

    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    /* 获取当前接入技术 */
    enNetRatType = NAS_MML_GetCurrNetRatType();

    if (VOS_TRUE != NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();

        return VOS_TRUE;
    }

    if (enNetRatType == stDestPlmn.enRat)
    {
        /* 向接入层或LMM发送搜网请求，根据不同的搜网模式，迁移到不同的L2状态，并启动保护定时器 */
        NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
    }
    /*需要挂起当前模式，切换到等待挂起状态，启动保护定时器*/
    else
    {
        /* 向接入层或LMM发送挂起请求，根据当前不同的接入技术，迁移到不同的L2状态，并启动保护定时器 */
        NAS_MMC_SndSuspendReq_PlmnSelection(enNetRatType);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitMsccRegReq
 功能描述  : 等待MSCC注册请求过程中收到MMCMMC_ABORT_FSM_REQ消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年1月28日
   作    者   : s00246516
   修改内容   : 新生成函数
 2.日    期   : 2014年8月1日
   作    者   : s00217060
   修改内容   : DTS2014072800477:VIA在EHRPD上搜到网给balong发送ID_CMMCA_MMC_RAT_NO_SERVICE_REQ时，
                balong刚好搜到LTE网络，等待VIA发送REG_REQ对冲场景的处理
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitMsccRegReq(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Added by s00261364 for L-C互操作项目, 2014-2-11, begin */
    NAS_MMC_ABORT_FSM_STRU             *pstAbortMsg = VOS_NULL_PTR;

    pstAbortMsg = (NAS_MMC_ABORT_FSM_STRU*)pstMsg;

    /* 若打断类型是用户请求的关机，则直接退出等注册请求状态机 */
    /* 若打断类型是ID_MSCC_MMC_POWER_SAVE_REQ，也需要直接退出状态机 */
    if ( (NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_OFF_REQ) == pstAbortMsg->ulEventType)
      || (NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_SAVE_REQ) == pstAbortMsg->ulEventType)
      || (NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_ACQ_REQ)        == pstAbortMsg->ulEventType))
    {
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_MSCC_REG_REQ);

        /* 回复状态机退出成功 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }
    /* Added by s00261364 for L-C互操作项目, 2014-2-11, end */

    /* 记录打断标志 */
    NAS_MMC_SetAbortFlag_PlmnSelection(VOS_TRUE);


    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitMsccRegReqExpired_PlmnSelection_WaitMsccRegReq
 功能描述  : 等待MSCC注册请求超时的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年1月28日
   作    者   : s00246516
   修改内容   : 新生成函数
 2.日    期   : 2014年6月13日
   作    者   : b00269685
   修改内容   : 若有abort标志，则回复abort
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitMsccRegReqExpired_PlmnSelection_WaitMsccRegReq(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitMsccRegReqExpired_PlmnSelection_WaitMsccRegReq ENTERED");

    /* 若有abort标志则回复abort，否则回复失败 */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);
    }
    else
    {
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);
    }

    /* 直接退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}
/* Added by s00246516 for L-C互操作项目, 2014-01-28, End */

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitLmmPlmnSearchCnf
 功能描述  : 等待LTE搜网回复过程中收到状态机退出消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年4月23日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2011年7月11日
   作    者   : sunxibo 46746
   修改内容   : V7R1 phase II,autoplmnsrch状态机调整为PlmnSelection状态机
 3.日    期   : 2014年2月18日
   作    者   : s00217060
   修改内容   : DTS2014021203453:设置打断标志，否则会在收到stop_cnf之后发起搜网

*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF);

    /* 通知LMM停止指定搜网 */
    NAS_MMC_SndLmmPlmnSrchStopReq();

    NAS_MMC_SetAbortFlag_PlmnSelection(VOS_TRUE);

    /*根据不同的搜网模式，迁移到不同的L2状态，启动不同保护定时器*/
    NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_STOP_CNF);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedStopPlmnSearchRcvLteSearchedPlmnInfoInd_PlmnSelection
 功能描述  : 收到lte SEARCHED_PLMN_INFO_IND判断是否需要打断当前搜网
 输入参数  : ulEventType:消息类型
             pstMsg:消息内容
 输出参数  : 无
 返 回 值  : VOS_FALSE:不需要打断当前搜网
             VOS_TRUE:需要打断当前搜网
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年10月28日
   作    者   : z00161729
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedStopPlmnSearchRcvLteSearchedPlmnInfoInd_PlmnSelection(
    LMM_MMC_SEARCHED_PLMN_INFO_IND_STRU                    *pstSearchedPlmnInfoInd
)
{
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstCurrSearchingPlmn;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionList = VOS_NULL_PTR;
    VOS_UINT32                                              ulIndex;
    NAS_MML_PLMN_WITH_RAT_STRU                              stPlmnIdWithRat;
    VOS_UINT32                                              ulIsExistDiffMccWithCurrSearchingMcc;
    VOS_UINT8                                               ucIsExistSearchedPlmnPrioCurrSearchingPlmn;
    NAS_MML_PLMN_ID_STRU                                    stGUNasPlmnId;
    NAS_MMC_ROAM_PLMN_INFO_STRU                             stCurrSearchRoamPlmnInfo;
    NAS_MMC_ROAM_PLMN_INFO_STRU                             stSearchedExistRoamPlmnInfo;
    VOS_UINT8                                               ucIsAllSearchedPlmnDisableLteRoam;
    VOS_UINT8                                               ucAllSearchedPlmnForbiddenPlmnFlag;
    NAS_MMC_ROAM_PLMN_TYPE_ENUM_UINT8                       enRoamPlmnType;

    PS_MEM_SET(&stCurrSearchRoamPlmnInfo, 0, sizeof(stCurrSearchRoamPlmnInfo));
    PS_MEM_SET(&stSearchedExistRoamPlmnInfo, 0, sizeof(stSearchedExistRoamPlmnInfo));
    PS_MEM_SET(&stPlmnIdWithRat, 0, sizeof(stPlmnIdWithRat));
    PS_MEM_SET(&stGUNasPlmnId, 0, sizeof(stGUNasPlmnId));

    pstCurrSearchingPlmn                       = NAS_MMC_GetCurrSearchingPlmn_PlmnSelection();
    pstPlmnSelectionList                       = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();
    ulIsExistDiffMccWithCurrSearchingMcc       = VOS_FALSE;
    ucIsExistSearchedPlmnPrioCurrSearchingPlmn = VOS_FALSE;
    ucIsAllSearchedPlmnDisableLteRoam          = VOS_TRUE;
    ucAllSearchedPlmnForbiddenPlmnFlag         = VOS_TRUE;
    enRoamPlmnType                             = NAS_MMC_ROAM_PLMN_TYPE_BUTT;

    stCurrSearchRoamPlmnInfo.stPlmnWithRat.stPlmnId.ulMcc = pstCurrSearchingPlmn->stPlmnId.ulMcc;
    stCurrSearchRoamPlmnInfo.stPlmnWithRat.stPlmnId.ulMnc = pstCurrSearchingPlmn->stPlmnId.ulMnc;
    stCurrSearchRoamPlmnInfo.stPlmnWithRat.enRat          = pstCurrSearchingPlmn->enRat;
    stCurrSearchRoamPlmnInfo.enNetStatus                  = NAS_MMC_NET_STATUS_NO_SEARCHED;
    stCurrSearchRoamPlmnInfo.enPlmnType                   = NAS_MMC_GetRoamPlmnTypeInPlmnSelectionList(&stCurrSearchRoamPlmnInfo.stPlmnWithRat, pstPlmnSelectionList);
    stCurrSearchRoamPlmnInfo.aucLac[0]                    = NAS_MML_LAC_LOW_BYTE_INVALID;
    stCurrSearchRoamPlmnInfo.aucLac[1]                    = NAS_MML_LAC_HIGH_BYTE_INVALID;


    /* 接入层指示存在的网络跟rplmn或hplmn是同一国家码非漫游场景则不处理该消息*/
    for (ulIndex = 0; ulIndex < pstSearchedPlmnInfoInd->ulTaiNum; ulIndex++)
    {
        NAS_MMC_ConvertLmmPlmnToGUNasFormat(&pstSearchedPlmnInfoInd->stTaiList[ulIndex].stPlmnId,
                                            &stGUNasPlmnId);



        /* 如果当前搜索的网络和searched plmn info ind消息中的plmn相同则不处理，
            等接入层的search cnf success消息*/
        if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&pstCurrSearchingPlmn->stPlmnId, &stGUNasPlmnId))
        {
            return VOS_FALSE;
        }

        /* 判断带上来的网络是否都禁止lte 漫游，如果禁止lte漫游需要打断当前l搜网*/
        if (VOS_FALSE == NAS_MMC_IsNeedDisableLteRoam(stGUNasPlmnId.ulMcc))
        {
            ucIsAllSearchedPlmnDisableLteRoam = VOS_FALSE;
        }

        /* 判断searched plmn info ind中带上来的网络是否跟正在搜索的网络同MCC,
           如果都是相同MCC,则无需打断当前搜网，如果存在不同MCC的网络则打断当前搜网 */

        stSearchedExistRoamPlmnInfo.stPlmnWithRat.stPlmnId.ulMcc = stGUNasPlmnId.ulMcc;
        stSearchedExistRoamPlmnInfo.stPlmnWithRat.stPlmnId.ulMnc = stGUNasPlmnId.ulMnc;
        stSearchedExistRoamPlmnInfo.stPlmnWithRat.enRat          = NAS_MML_NET_RAT_TYPE_LTE;

        stSearchedExistRoamPlmnInfo.enNetStatus =  NAS_MMC_GetSpecPlmnWithRatNetStatusInPlmnSelectionList(&stSearchedExistRoamPlmnInfo.stPlmnWithRat, pstPlmnSelectionList);

        if (NAS_MMC_NET_STATUS_SEARCHED_REGISTERED != stSearchedExistRoamPlmnInfo.enNetStatus)
        {
            stSearchedExistRoamPlmnInfo.enNetStatus = NAS_MMC_NET_STATUS_SEARCHED_EXIST;
        }

        stSearchedExistRoamPlmnInfo.enPlmnType  = NAS_MMC_GetRoamPlmnTypeInPlmnSelectionList(&stSearchedExistRoamPlmnInfo.stPlmnWithRat, pstPlmnSelectionList);
        stSearchedExistRoamPlmnInfo.aucLac[0]   = pstSearchedPlmnInfoInd->stTaiList[ulIndex].stTac.ucTac;
        stSearchedExistRoamPlmnInfo.aucLac[1]   = pstSearchedPlmnInfoInd->stTaiList[ulIndex].stTac.ucTacCnt;

        if (VOS_FALSE == NAS_MML_ComparePlmnMcc(pstCurrSearchingPlmn->stPlmnId.ulMcc, stGUNasPlmnId.ulMcc))
        {
            ulIsExistDiffMccWithCurrSearchingMcc = VOS_TRUE;

            /* 如果带上来的网络都是nplmn或forbidden plmn，不同mcc也先不打断 */
            enRoamPlmnType = NAS_MMC_GetRoamPlmnType(&stSearchedExistRoamPlmnInfo);

            if ((NAS_MMC_ROAM_PLMN_TYPE_FORBIDDEN != enRoamPlmnType)
             && (NAS_MMC_ROAM_PLMN_TYPE_NPLMN != enRoamPlmnType))
            {
                ucAllSearchedPlmnForbiddenPlmnFlag = VOS_FALSE;
            }
        }
        else
        {
            /* 修改函数名 */
            /* 报上来的网络优先级高于当前搜索的网络，则需要打断当前搜网 */
            if (-1 == NAS_MMC_CompareRoamPlmnPrio(&stCurrSearchRoamPlmnInfo, &stSearchedExistRoamPlmnInfo, NAS_MML_GetMsPrioRatList()))
            {
                ucIsExistSearchedPlmnPrioCurrSearchingPlmn = VOS_TRUE;
            }
        }
    }

    if (VOS_TRUE == ucIsAllSearchedPlmnDisableLteRoam)
    {
        /* 更新disable LTE能力标记 */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS);
        NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_LTE_ROAMING_NOT_ALLOWED);
        return VOS_TRUE;
    }

    /* searched plmn info ind消息中带上来的网络存在与当前搜的网络不同国家码的网络，
       且不都是nplmn和forbidden plmn则打断当前搜网*/
    if ((VOS_TRUE == ulIsExistDiffMccWithCurrSearchingMcc)
     && (VOS_FALSE == ucAllSearchedPlmnForbiddenPlmnFlag))
    {
        return VOS_TRUE;
    }

    /* searched plmn info ind 消息中带上来的网络与当前搜的网络同国家码，
       但优先级高于或等于当前搜索的网，则打断当前搜网*/
    if (VOS_TRUE == ucIsExistSearchedPlmnPrioCurrSearchingPlmn)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmSearchedPlmnInfoInd_PlmnSelection_WaitLmmPlmnSearchCnf
 功能描述  : 收到LTE searched plmn info ind消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年10月31日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   : 2015年10月10日
   作    者   : s00217060
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0修改
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmSearchedPlmnInfoInd_PlmnSelection_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_SEARCHED_PLMN_INFO_IND_STRU                    *pstSearchedPlmnInfoInd = VOS_NULL_PTR;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSrchList   = VOS_NULL_PTR;
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                        stNewRoamPlmnSelectionList;
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                        stExistRoamPlmnSelectionList;
    NAS_MML_PLMN_ID_STRU                                    stGUNasPlmnId;

    pstSearchedPlmnInfoInd   = (LMM_MMC_SEARCHED_PLMN_INFO_IND_STRU*)pstMsg;
    PS_MEM_SET(&stExistRoamPlmnSelectionList, 0, sizeof(stExistRoamPlmnSelectionList));
    PS_MEM_SET(&stNewRoamPlmnSelectionList, 0, sizeof(stNewRoamPlmnSelectionList));
    PS_MEM_SET(&stGUNasPlmnId, 0, sizeof(stGUNasPlmnId));

    NAS_MMC_SndMsccSrchedLtePlmnInfo(pstSearchedPlmnInfoInd);

    /* 获取选网列表 */
    pstPlmnSrchList       = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();


    NAS_MMC_BuildSearchedPlmnInfoByLteSearchedPlmnInfoInd(pstSearchedPlmnInfoInd, &stExistRoamPlmnSelectionList);

    NAS_MMC_UpdateExistRplmnOrHplmnFlag_PlmnSelection(&stExistRoamPlmnSelectionList);

    /* 通知CSS当前MCC */
    NAS_MMC_SndCssCurrGeoIndAfterRcvPlmnInfoInd_PlmnSelection(&stExistRoamPlmnSelectionList, VOS_TRUE);

    if (VOS_FALSE == NAS_MMC_IsNeedSortRoamPlmnSelectionList_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE))
    {
        return VOS_TRUE;
    }

    /* 消息中ulAvailPlmnNum参数超过NAS_RRC_MAX_AVAILPLMN_NUM，认为非法，重新赋值*/
    if (pstSearchedPlmnInfoInd->ulTaiNum > LMM_MMC_MAX_SEARCHED_TAI_NUM)
    {
        pstSearchedPlmnInfoInd->ulTaiNum = LMM_MMC_MAX_SEARCHED_TAI_NUM;
    }

    if (VOS_TRUE == NAS_MMC_IsNeedStopPlmnSearchRcvLteSearchedPlmnInfoInd_PlmnSelection(pstSearchedPlmnInfoInd))
    {
        /* 开机漫游场景对漫游搜网列表排序，原则如下:
         1、接入层上报存在的网络放在漫游搜网列表前面,在NPLMN中的网络不添加，
            支持的所有接入技术都添加，当前搜网的接入技术优先
         2、在gastNetworkNameTbl中找出跟当前存在网络相同国家码的plmn加入漫游搜网列表，
            在NPLMN中德网络不添加，支持的所有接入技术都添加，当前搜网的接入技术优先
         3、根据DPLMN->UPLMN->OPLMN->AVAILABLE PLMN顺序对漫游搜网列表进行排序
        */
        NAS_MMC_BuildRoamPlmnSelectionListBySearchedExistPlmnInfo(NAS_MML_NET_RAT_TYPE_LTE,
            &stExistRoamPlmnSelectionList, &stNewRoamPlmnSelectionList);

        /* 把排过序的roam搜网列表插入搜网列表前面 */
        NAS_MMC_AddRoamPlmnSelectionListInPlmnSelectionList(&stNewRoamPlmnSelectionList, pstPlmnSrchList);

        /* 可维可测,将选网列表输出 */
        NAS_MMC_LogPlmnSelectionList(pstPlmnSrchList);
        NAS_MMC_LogDplmnNplmnList();


        /* 设置该接入技术已经收到过接入层searched plmn info ind进行过一轮排序 */
        NAS_MMC_SetSearchedRoamPlmnSortedFlag_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE, VOS_TRUE);

        if (NAS_MMC_PLMN_SEARCH_TYPE_HISTORY == NAS_MMC_GetCurrSearchingType_PlmnSelection())
        {
            NAS_MMC_SetHistorySearchedFlag_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE, VOS_TRUE);
        }

        /* 停止保护定时器 */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF);

        /* 通知LMM停止指定搜网 */
        NAS_MMC_SndLmmPlmnSrchStopReq();

        /*根据不同的搜网模式，迁移到不同的L2状态，启动不同保护定时器*/
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_STOP_CNF);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF_LEN);

    }

    return VOS_TRUE;
}




/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmPlmnCnf_PlmnSelection_WaitLmmPlmnSearchCnf
 功能描述  : 收到LTE搜网CNF后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:rrmm_plmn_SEARCH_cnf消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年4月25日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2011年7月11日
   作    者   : sunxibo 46746
   修改内容   : V7R1 phase II,autoplmnsrch状态机调整为PlmnSelection状态机
 3.日    期   : 2011年12月15日
   作    者   : W00166186
   修改内容   : dts2011111502641,L下PLMN加入禁止TA后不再搜网
 4.日    期   : 2011年12月14日
   作    者   : w00176964
   修改内容   : V7R1 phaseIV 调整:驻留标记通过新的搜网控制上下文代替
 5.日    期   : 2012年7月16日
   作    者   : s00217060
   修改内容   : for DTS2012071604442 调整:收到LMM搜网失败,并且获取下一个网络失败需要重新驻留LTE
 6.日    期   : 2013年8月27日
   作    者   : l00208543
   修改内容   : Coverity
 7.日    期   : 2014年6月10日
   作    者   : w00167002
   修改内容   : DSDS III:L下搜网NO RF场景处理
 8.日    期   : 2014年11月3日
   作    者   : z00161729
   修改内容   : 开机漫游搜网项目修改
 9.日    期   : 2015年5月26日
   作    者   : w00167002
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0项目修改，封装L下全频段指定搜网回复的处理
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmSpecPlmnSearchCnf_PlmnSelection_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_PLMN_SRCH_CNF_STRU                             *pstLmmSrchCnfMsg = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stDestPlmn;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    stPlmnSearchInfo;

    VOS_UINT32                                              ulIsNeedSortRoamPlmnList;
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                        stSearchedExistPlmnInfo;
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                        stNewRoamPlmnSelectionList;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSrchList   = VOS_NULL_PTR;

    /* 获取选网列表 */
    pstPlmnSrchList                  = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();
    ulIsNeedSortRoamPlmnList         = VOS_FALSE;
    PS_MEM_SET(&stSearchedExistPlmnInfo, 0, sizeof(stSearchedExistPlmnInfo));
    PS_MEM_SET(&stNewRoamPlmnSelectionList, 0, sizeof(stNewRoamPlmnSelectionList));

    /* 解决版本Coverity问题 */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    pstLmmSrchCnfMsg = (LMM_MMC_PLMN_SRCH_CNF_STRU*)pstMsg;

    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF);

    /* 设置当前模式是否进行全频搜网，是否存在网络覆盖 */
    NAS_MMC_UpdateLmmCoverageFlg_PlmnSelection(pstLmmSrchCnfMsg);

    if (MMC_LMM_PLMN_SRCH_RLT_SPEC_SUCC == pstLmmSrchCnfMsg->enRlst)
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_SUCCESS,
                VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_UpdateRfAvailFlgPlmnSrchSucc_PlmnSelection();

        /*根据不同的搜网模式，迁移到不同的L2状态，启动保护定时器 */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_SYSINFO_IND);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_SYS_INFO, TI_NAS_MMC_WAIT_LMM_SYS_INFO_LEN);

        return VOS_TRUE;
    }


    /* 如果当前为NO RF，则直接退状态机 */
    if (MMC_LMM_PLMN_SRCH_RLT_SPEC_NO_RF == pstLmmSrchCnfMsg->enRlst)
    {
        NAS_MMC_ProcNoRf_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE);

        return VOS_TRUE;
    }


    /* 将搜网消息中携带的网络信息转换为内部消息中网络信息 */
    NAS_MMC_ConvertLmmPlmnList2SearchedPlmnListInfo(&(pstLmmSrchCnfMsg->stPlmnIdList),
                                                     &stPlmnSearchInfo);


    /* 根据消息中携带的搜网信息更新搜网列表 */
    NAS_MMC_UpdatePlmnSearchList_PlmnSelection(&stPlmnSearchInfo,
                                               NAS_MMC_IsNeedSortAvailablePlmnSelectionList_PlmnSelection(),
                                               VOS_TRUE);

    /* 搜网失败后更新RF可用标记 */
    NAS_MMC_UpdateRfAvailFlgPlmnSrchFail_PlmnSelection();

    /* 通知CSS当前MCC */
    NAS_MMC_SndCssCurrGeoIndAfterRcvPlmnSearchCnfFail_PlmnSelection(&stPlmnSearchInfo, VOS_TRUE);

    /* 如果搜网失败结果中带上来的网络没有一个跟rplmn或hplmn
       同一国家码且之前未排过序，需要构造漫游搜网列表插入原搜网头部*/
    ulIsNeedSortRoamPlmnList = NAS_MMC_IsNeedSortPlmnListRcvRrcPlmnSearchCnfFail_PlmnSelection(&stPlmnSearchInfo, NAS_MML_NET_RAT_TYPE_LTE);

    if (VOS_TRUE == ulIsNeedSortRoamPlmnList)
    {
        /* 把高低质量网络提取加入roam搜网列表 */
        NAS_MMC_BuildSearchedPlmnListInfoByRrcSearchCnfFail(NAS_MML_NET_RAT_TYPE_LTE, &stPlmnSearchInfo, &stSearchedExistPlmnInfo);

        NAS_MMC_BuildRoamPlmnSelectionListBySearchedExistPlmnInfo(NAS_MML_NET_RAT_TYPE_LTE,
            &stSearchedExistPlmnInfo, &stNewRoamPlmnSelectionList);

        /* 把排过序的roam搜网列表插入搜网列表前面 */
        NAS_MMC_AddRoamPlmnSelectionListInPlmnSelectionList(&stNewRoamPlmnSelectionList, pstPlmnSrchList);

        /* 设置该接入技术已经收到过接入层searched plmn info ind进行过一轮排序 */
        NAS_MMC_SetSearchedRoamPlmnSortedFlag_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE, VOS_TRUE);

        /* 根据消息中携带的搜网信息更新搜网列表 */
        NAS_MMC_UpdatePlmnSearchList_PlmnSelection(&stPlmnSearchInfo,
                                                   NAS_MMC_IsNeedSortAvailablePlmnSelectionList_PlmnSelection(),
                                                   VOS_TRUE);


        /* 可维可测,将选网列表输出 */
        NAS_MMC_LogDplmnNplmnList();
    }


    /* 更新当前接入技术进行了全频搜网,如果在前面更新漫游网络可能无法加入漫游搜网列表，所以构造完漫游搜网列表后再更新进行过全频搜网*/
    NAS_MMC_SetAllBandSearch_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE, VOS_TRUE);

    /* 当还存在下一个需要搜索的网络时，继续进行搜网，否则，进入限制驻留 */
    if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        if (NAS_MML_NET_RAT_TYPE_LTE == stDestPlmn.enRat)
        {
            /* 向接入层或LMM发送搜网请求，根据不同的搜网模式，迁移到不同的L2状态，并启动保护定时器 */
            NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
        }
        else
        {
            /* 向接入层或LMM发送挂起请求，根据当前不同的接入技术，迁移到不同的L2状态，并启动保护定时器 */
            NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE);
        }
    }
    else
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();
    }


    return VOS_TRUE;

}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmHistoryPlmnSearchCnf_PlmnSelection_WaitLmmPlmnSearchCnf
 功能描述  : 收到LTE history搜网CNF后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:rrmm_plmn_SEARCH_cnf消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年5月26日
   作    者   : w00167002
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0项目新增:L下HISTORY搜结果的处理
*****************************************************************************/
VOS_VOID NAS_MMC_RcvLmmHistoryPlmnSearchCnf_PlmnSelection_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_PLMN_SRCH_CNF_STRU                             *pstLmmSrchCnfMsg = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stDestPlmn;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    stPlmnSearchInfo;

    VOS_UINT32                                              ulIsNeedSortRoamPlmnList;
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                        stSearchedExistPlmnInfo;
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                        stNewRoamPlmnSelectionList;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSrchList   = VOS_NULL_PTR;

    /* 获取选网列表 */
    pstPlmnSrchList                  = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();
    ulIsNeedSortRoamPlmnList         = VOS_FALSE;
    PS_MEM_SET(&stSearchedExistPlmnInfo, 0, sizeof(stSearchedExistPlmnInfo));
    PS_MEM_SET(&stNewRoamPlmnSelectionList, 0, sizeof(stNewRoamPlmnSelectionList));

    /* 解决版本Coverity问题 */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    pstLmmSrchCnfMsg = (LMM_MMC_PLMN_SRCH_CNF_STRU*)pstMsg;

    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF);

    /* 不设置当前模式进行了全频搜网，更新网络覆盖 */
    NAS_MMC_UpdateLmmCoverageFlg_PlmnSelection(pstLmmSrchCnfMsg);

    if (MMC_LMM_PLMN_SRCH_RLT_HISTORY_SUCC == pstLmmSrchCnfMsg->enRlst)
    {
        NAS_MMC_SetHistorySearchedFlag_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE, VOS_TRUE);

        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_SUCCESS,
                VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_UpdateRfAvailFlgPlmnSrchSucc_PlmnSelection();

        /*根据不同的搜网模式，迁移到不同的L2状态，启动保护定时器 */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_SYSINFO_IND);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_SYS_INFO, TI_NAS_MMC_WAIT_LMM_SYS_INFO_LEN);

        return;
    }

    /* 如果当前为NO RF，则直接退状态机 */
    if (MMC_LMM_PLMN_SRCH_RLT_HISTORY_NO_RF == pstLmmSrchCnfMsg->enRlst)
    {
        NAS_MMC_ProcNoRf_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE);

        return;
    }

    NAS_MMC_SetHistorySearchedFlag_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE, VOS_TRUE);

    /* 将搜网消息中携带的网络信息转换为内部消息中网络信息 */
    NAS_MMC_ConvertLmmPlmnList2SearchedPlmnListInfo(&(pstLmmSrchCnfMsg->stPlmnIdList),
                                                     &stPlmnSearchInfo);


    /* 根据消息中携带的搜网信息更新搜网列表 */
    NAS_MMC_UpdatePlmnSearchList_PlmnSelection(&stPlmnSearchInfo,
                                               NAS_MMC_IsNeedSortAvailablePlmnSelectionList_PlmnSelection(),
                                               VOS_FALSE);

    /* 搜网失败后更新RF可用标记 */
    NAS_MMC_UpdateRfAvailFlgPlmnSrchFail_PlmnSelection();

    NAS_MMC_SndCssCurrGeoIndAfterRcvPlmnSearchCnfFail_PlmnSelection(&stPlmnSearchInfo, VOS_TRUE);

    /* 如果搜网失败结果中带上来的网络没有一个跟rplmn或hplmn
       同一国家码且之前未排过序，需要构造漫游搜网列表插入原搜网头部*/
    ulIsNeedSortRoamPlmnList = NAS_MMC_IsNeedSortPlmnListRcvRrcPlmnSearchCnfFail_PlmnSelection(&stPlmnSearchInfo, NAS_MML_NET_RAT_TYPE_LTE);

    if (VOS_TRUE == ulIsNeedSortRoamPlmnList)
    {
        /* 把高低质量网络提取加入roam搜网列表 */
        NAS_MMC_BuildSearchedPlmnListInfoByRrcSearchCnfFail(NAS_MML_NET_RAT_TYPE_LTE, &stPlmnSearchInfo, &stSearchedExistPlmnInfo);

        NAS_MMC_BuildRoamPlmnSelectionListBySearchedExistPlmnInfo(NAS_MML_NET_RAT_TYPE_LTE,
            &stSearchedExistPlmnInfo, &stNewRoamPlmnSelectionList);

        /* 把排过序的roam搜网列表插入搜网列表前面 */
        NAS_MMC_AddRoamPlmnSelectionListInPlmnSelectionList(&stNewRoamPlmnSelectionList, pstPlmnSrchList);

        /* 设置该接入技术已经收到过接入层searched plmn info ind进行过一轮排序 */
        NAS_MMC_SetSearchedRoamPlmnSortedFlag_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE, VOS_TRUE);

        /* 根据消息中携带的搜网信息更新搜网列表 */
        NAS_MMC_UpdatePlmnSearchList_PlmnSelection(&stPlmnSearchInfo,
                                                   NAS_MMC_IsNeedSortAvailablePlmnSelectionList_PlmnSelection(),
                                                   VOS_FALSE);

        /* 可维可测,将选网列表输出 */
        NAS_MMC_LogDplmnNplmnList();
    }

    /* 当还存在下一个需要搜索的网络时，继续进行搜网，否则，进入限制驻留 */
    if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        if (NAS_MML_NET_RAT_TYPE_LTE == stDestPlmn.enRat)
        {
            /* 向接入层或LMM发送搜网请求，根据不同的搜网模式，迁移到不同的L2状态，并启动保护定时器 */
            NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
        }
        else
        {
            /* 向接入层或LMM发送挂起请求，根据当前不同的接入技术，迁移到不同的L2状态，并启动保护定时器 */
            NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE);
        }
    }
    else
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();
    }

    return;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmPrefBandPlmnSearchCnf_PlmnSelection_WaitLmmPlmnSearchCnf
 功能描述  : 收到LTE pref band搜网CNF后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:rrmm_plmn_SEARCH_cnf消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年10月13日
   作    者   : s00217060
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmPrefBandPlmnSearchCnf_PlmnSelection_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_PLMN_SRCH_CNF_STRU                             *pstLmmSrchCnfMsg = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stDestPlmn;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    stPlmnSearchInfo;

    VOS_UINT32                                              ulIsNeedSortRoamPlmnList;
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                        stSearchedExistPlmnInfo;
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                        stNewRoamPlmnSelectionList;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSrchList   = VOS_NULL_PTR;

    /* 获取选网列表 */
    pstPlmnSrchList                  = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();
    ulIsNeedSortRoamPlmnList         = VOS_FALSE;
    PS_MEM_SET(&stSearchedExistPlmnInfo, 0, sizeof(stSearchedExistPlmnInfo));
    PS_MEM_SET(&stNewRoamPlmnSelectionList, 0, sizeof(stNewRoamPlmnSelectionList));

    /* 解决版本Coverity问题 */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    pstLmmSrchCnfMsg = (LMM_MMC_PLMN_SRCH_CNF_STRU*)pstMsg;

    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF);

    /* 设置当前模式是否进行全频搜网，是否存在网络覆盖 */
    NAS_MMC_UpdateLmmCoverageFlg_PlmnSelection(pstLmmSrchCnfMsg);

    if (MMC_LMM_PLMN_SRCH_RLT_PREF_BAND_SUCC == pstLmmSrchCnfMsg->enRlst)
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_SUCCESS,
                VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_UpdateRfAvailFlgPlmnSrchSucc_PlmnSelection();

        /*根据不同的搜网模式，迁移到不同的L2状态，启动保护定时器 */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_SYSINFO_IND);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_SYS_INFO, TI_NAS_MMC_WAIT_LMM_SYS_INFO_LEN);

        return VOS_TRUE;
    }

    /* 如果当前为NO RF，则直接退状态机 */
    if (MMC_LMM_PLMN_SRCH_RLT_PREF_BAND_NO_RF == pstLmmSrchCnfMsg->enRlst)
    {
        NAS_MMC_ProcNoRf_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE);

        return VOS_TRUE;
    }

    /* 将搜网消息中携带的网络信息转换为内部消息中网络信息 */
    NAS_MMC_ConvertLmmPlmnList2SearchedPlmnListInfo(&(pstLmmSrchCnfMsg->stPlmnIdList),
                                                     &stPlmnSearchInfo);


    /* 根据消息中携带的搜网信息更新搜网列表 */
    NAS_MMC_UpdatePlmnSearchList_PlmnSelection(&stPlmnSearchInfo,
                                               NAS_MMC_IsNeedSortAvailablePlmnSelectionList_PlmnSelection(),
                                               VOS_TRUE);

    /* 搜网失败后更新RF可用标记 */
    NAS_MMC_UpdateRfAvailFlgPlmnSrchFail_PlmnSelection();

    /* 通知CSS当前MCC */
    NAS_MMC_SndCssCurrGeoIndAfterRcvPlmnSearchCnfFail_PlmnSelection(&stPlmnSearchInfo, VOS_TRUE);

    /* 如果搜网失败结果中带上来的网络没有一个跟rplmn或hplmn
       同一国家码且之前未排过序，需要构造漫游搜网列表插入原搜网头部*/
    ulIsNeedSortRoamPlmnList = NAS_MMC_IsNeedSortPlmnListRcvRrcPlmnSearchCnfFail_PlmnSelection(&stPlmnSearchInfo, NAS_MML_NET_RAT_TYPE_LTE);

    if (VOS_TRUE == ulIsNeedSortRoamPlmnList)
    {
        /* 把高低质量网络提取加入roam搜网列表 */
        NAS_MMC_BuildSearchedPlmnListInfoByRrcSearchCnfFail(NAS_MML_NET_RAT_TYPE_LTE, &stPlmnSearchInfo, &stSearchedExistPlmnInfo);

        NAS_MMC_BuildRoamPlmnSelectionListBySearchedExistPlmnInfo(NAS_MML_NET_RAT_TYPE_LTE,
            &stSearchedExistPlmnInfo, &stNewRoamPlmnSelectionList);

        /* 把排过序的roam搜网列表插入搜网列表前面 */
        NAS_MMC_AddRoamPlmnSelectionListInPlmnSelectionList(&stNewRoamPlmnSelectionList, pstPlmnSrchList);

        /* 设置该接入技术已经收到过接入层searched plmn info ind进行过一轮排序 */
        NAS_MMC_SetSearchedRoamPlmnSortedFlag_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE, VOS_TRUE);

        /* 根据消息中携带的搜网信息更新搜网列表 */
        NAS_MMC_UpdatePlmnSearchList_PlmnSelection(&stPlmnSearchInfo,
                                                   NAS_MMC_IsNeedSortAvailablePlmnSelectionList_PlmnSelection(),
                                                   VOS_TRUE);


        /* 可维可测,将选网列表输出 */
        NAS_MMC_LogDplmnNplmnList();
    }


    /* 更新当前接入技术进行了全频搜网,如果在前面更新漫游网络可能无法加入漫游搜网列表，所以构造完漫游搜网列表后再更新进行过全频搜网*/
    NAS_MMC_SetAllBandSearch_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE, VOS_TRUE);

    /* 当还存在下一个需要搜索的网络时，继续进行搜网，否则，进入限制驻留 */
    if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        if (NAS_MML_NET_RAT_TYPE_LTE == stDestPlmn.enRat)
        {
            /* 向接入层或LMM发送搜网请求，根据不同的搜网模式，迁移到不同的L2状态，并启动保护定时器 */
            NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
        }
        else
        {
            /* 向接入层或LMM发送挂起请求，根据当前不同的接入技术，迁移到不同的L2状态，并启动保护定时器 */
            NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE);
        }
    }
    else
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();
    }


    return VOS_TRUE;

}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmPlmnCnf_PlmnSelection_WaitLmmPlmnSearchCnf
 功能描述  : 收到LTE搜网CNF后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:rrmm_plmn_SEARCH_cnf消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年4月25日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2011年7月11日
   作    者   : sunxibo 46746
   修改内容   : V7R1 phase II,autoplmnsrch状态机调整为PlmnSelection状态机
 3.日    期   : 2011年12月15日
   作    者   : W00166186
   修改内容   : dts2011111502641,L下PLMN加入禁止TA后不再搜网
 4.日    期   : 2011年12月14日
   作    者   : w00176964
   修改内容   : V7R1 phaseIV 调整:驻留标记通过新的搜网控制上下文代替
 5.日    期   : 2012年7月16日
   作    者   : s00217060
   修改内容   : for DTS2012071604442 调整:收到LMM搜网失败,并且获取下一个网络失败需要重新驻留LTE
 6.日    期   : 2013年8月27日
   作    者   : l00208543
   修改内容   : Coverity
 7.日    期   : 2014年6月10日
   作    者   : w00167002
   修改内容   : DSDS III:L下搜网NO RF场景处理
 8.日    期   : 2014年11月3日
   作    者   : z00161729
   修改内容   : 开机漫游搜网项目修改
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmPlmnCnf_PlmnSelection_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_PLMN_SRCH_CNF_STRU                             *pstLmmSrchCnfMsg = VOS_NULL_PTR;

    pstLmmSrchCnfMsg = (LMM_MMC_PLMN_SRCH_CNF_STRU*)pstMsg;

    switch (pstLmmSrchCnfMsg->enRlst)
    {
        case MMC_LMM_PLMN_SRCH_RLT_SPEC_SUCC:
        case MMC_LMM_PLMN_SRCH_RLT_SPEC_NO_RF:
        case MMC_LMM_PLMN_SRCH_RLT_SPEC_FAIL:

            /* L下指定搜网的处理 */
            (VOS_VOID)NAS_MMC_RcvLmmSpecPlmnSearchCnf_PlmnSelection_WaitLmmPlmnSearchCnf(ulEventType, pstMsg);
            break;

        case MMC_LMM_PLMN_SRCH_RLT_HISTORY_SUCC:
        case MMC_LMM_PLMN_SRCH_RLT_HISTORY_NO_RF:
        case MMC_LMM_PLMN_SRCH_RLT_HISTORY_FAIL:

            /* L下HISTORY指定搜网的处理 */
            NAS_MMC_RcvLmmHistoryPlmnSearchCnf_PlmnSelection_WaitLmmPlmnSearchCnf(ulEventType, pstMsg);
            break;

        /* L下pref band搜网的处理 */
        case MMC_LMM_PLMN_SRCH_RLT_PREF_BAND_SUCC:
        case MMC_LMM_PLMN_SRCH_RLT_PREF_BAND_NO_RF:
        case MMC_LMM_PLMN_SRCH_RLT_PREF_BAND_FAIL:

            (VOS_VOID)NAS_MMC_RcvLmmPrefBandPlmnSearchCnf_PlmnSelection_WaitLmmPlmnSearchCnf(ulEventType, pstMsg);
            break;

        default:
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmPlmnCnf_PlmnSelection_WaitLmmPlmnSearchCnf: UNEXPECTED RSLT TYPE!!!");
            (VOS_VOID)NAS_MMC_RcvLmmSpecPlmnSearchCnf_PlmnSelection_WaitLmmPlmnSearchCnf(ulEventType, pstMsg);
            break;
    }

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmAttachCnf_PlmnSelection_WaitLmmPlmnSearchCnf
 功能描述  : 收到ID_LMM_MMC_ATTACH_CNF的处理
 输入参数  : ulEventType:消息类型
             pstMsg:ID_LMM_MMC_ATTACH_CNF消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年9月3日
   作    者   : s00217060
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmAttachCnf_PlmnSelection_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 当前LTE的能力状态不为DISABLE 状态，则不处理该消息 */
    if ( NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS != NAS_MML_GetLteCapabilityStatus())
    {
        /* 异常打印 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmAttachCnf_PlmnSelection_WaitLmmPlmnSearchCnf: unexpect message received");

        return VOS_TRUE;
    }

    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF);

    /* 通知LMM停止指定搜网 */
    NAS_MMC_SndLmmPlmnSrchStopReq();

    /*根据不同的搜网模式，迁移到不同的L2状态，启动不同保护定时器*/
    NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_STOP_CNF);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmDetachCnf_PlmnSelection_WaitLmmPlmnSearchCnf
 功能描述  : 收到ID_LMM_MMC_DETACH_CNF的处理
 输入参数  : ulEventType:消息类型
             pstMsg:ID_LMM_MMC_DETACH_CNF消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年12月01日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmDetachCnf_PlmnSelection_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 当前LTE的能力状态不为DISABLE 状态，则不处理该消息 */
    if ( NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS != NAS_MML_GetLteCapabilityStatus())
    {
        /* 异常打印 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmDetachCnf_PlmnSelection_WaitLmmPlmnSearchCnf: unexpect message received");

        return VOS_TRUE;
    }

    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF);

    /* 通知LMM停止指定搜网 */
    NAS_MMC_SndLmmPlmnSrchStopReq();

    /*根据不同的搜网模式，迁移到不同的L2状态，启动不同保护定时器*/
    NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_STOP_CNF);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitLmmPlmnSearchCnfExpired_PlmnSelection_WaitLmmPlmnSearchCnf
 功能描述  : 等待LTE全频段指定搜网回复过程中搜网定时器超时
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年4月23日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2011年7月11日
   作    者   : sunxibo 46746
   修改内容   : V7R1 phase II,autoplmnsrch状态机调整为PlmnSelection状态机
 3.日    期   : 2011年12月15日
   作    者   : W00166186
   修改内容   : dts2011111502641,L下PLMN加入禁止TA后不再搜网
 4.日    期   : 2011年12月14日
   作    者   : w00176964
   修改内容   : V7R1 phaseIV 调整:驻留标记通过新的搜网控制上下文代替
 5.日    期   : 2012年7月16日
   作    者   : s00217060
   修改内容   : for DTS2012071604442
                调整:LMM搜网定时器超时,并且获取下一个网络失败需要重新驻留LTE
 6.日    期   : 2012年11月05日
   作    者   : w00176964
   修改内容   : DTS2011082405001:更新网络覆盖类型
 7.日    期   : 2013年8月27日
   作    者   : l00208543
   修改内容   : Coverity
 8.日    期   : 2014年6月6日
   作    者   : b00269685
   修改内容   : 先通知LMM停止搜网
 9.日    期   : 2014年11月8日
   作    者   : z00161729
   修改内容   : 开机搜网优化项目修改
 7.日    期   : 2015年5月26日
   作    者   : w00167002
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0项目修改
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitSpecPlmnSearchCnfExpired_PlmnSelection_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    stPlmnSearchInfo;

    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitLmmPlmnSearchCnfExpired_PlmnSelection_WaitLmmPlmnSearchCnf: Timer Expired");

    /* 设置当前网络已经进行全频搜网 */
    NAS_MMC_SetAllBandSearch_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE, VOS_TRUE);

    /* 设置当前网络无覆盖 */
    NAS_MMC_SetRatCoverage_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE, NAS_MMC_COVERAGE_TYPE_NONE);

    /* 设置当前接入技术没有搜索到任何网络 */
    stPlmnSearchInfo.ulHighPlmnNum = 0x0;
    stPlmnSearchInfo.ulLowPlmnNum  = 0x0;
    stPlmnSearchInfo.enRatType     = NAS_MML_NET_RAT_TYPE_LTE;

    /* 根据消息中携带的搜网信息更新搜网列表 */
    NAS_MMC_UpdatePlmnSearchList_PlmnSelection(&stPlmnSearchInfo,
                                               NAS_MMC_IsNeedSortAvailablePlmnSelectionList_PlmnSelection(),
                                               VOS_TRUE);


    /* 通知LMM停止指定搜网 */
    NAS_MMC_SndLmmPlmnSrchStopReq();

    /*根据不同的搜网模式，迁移到不同的L2状态，启动不同保护定时器*/
    NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_STOP_CNF);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF_LEN);

    return VOS_TRUE;

}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitLmmPlmnSearchCnfExpired_PlmnSelection_WaitLmmPlmnSearchCnf
 功能描述  : 等待LTE历史频点搜网回复过程中搜网定时器超时
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年5月26日
   作    者   : w00167002
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0项目修改
*****************************************************************************/
VOS_VOID NAS_MMC_RcvTiWaitHistoryPlmnSrchCnfExpired_PlmnSelection_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitHistoryPlmnSearchCnfExpired_PlmnSelection_WaitLmmPlmnSearchCnf: Timer Expired");

    /* 设置当前网络无覆盖 */
    NAS_MMC_SetRatCoverage_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE, NAS_MMC_COVERAGE_TYPE_NONE);

    NAS_MMC_SetHistorySearchedFlag_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE, VOS_TRUE);

    /* 通知LMM停止指定搜网 */
    NAS_MMC_SndLmmPlmnSrchStopReq();

    /*根据不同的搜网模式，迁移到不同的L2状态，启动不同保护定时器*/
    NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_STOP_CNF);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF_LEN);

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitLmmPlmnSearchCnfExpired_PlmnSelection_WaitLmmPlmnSearchCnf
 功能描述  : 等待LTE搜网回复过程中搜网定时器超时
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年4月23日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2011年7月11日
   作    者   : sunxibo 46746
   修改内容   : V7R1 phase II,autoplmnsrch状态机调整为PlmnSelection状态机
 3.日    期   : 2011年12月15日
   作    者   : W00166186
   修改内容   : dts2011111502641,L下PLMN加入禁止TA后不再搜网
 4.日    期   : 2011年12月14日
   作    者   : w00176964
   修改内容   : V7R1 phaseIV 调整:驻留标记通过新的搜网控制上下文代替
 5.日    期   : 2012年7月16日
   作    者   : s00217060
   修改内容   : for DTS2012071604442
                调整:LMM搜网定时器超时,并且获取下一个网络失败需要重新驻留LTE
 6.日    期   : 2012年11月05日
   作    者   : w00176964
   修改内容   : DTS2011082405001:更新网络覆盖类型
 7.日    期   : 2013年8月27日
   作    者   : l00208543
   修改内容   : Coverity
 8.日    期   : 2014年6月6日
   作    者   : b00269685
   修改内容   : 先通知LMM停止搜网
 9.日    期   : 2014年11月8日
   作    者   : z00161729
   修改内容   : 开机搜网优化项目修改
10.日    期   : 2015年5月26日
   作    者   : w00167002
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0项目修改 增加对HISTORY搜网的处理
11.日    期   : 2015年10月28日
   作    者   : s00217060
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0:增加pref band搜的处理
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitLmmPlmnSearchCnfExpired_PlmnSelection_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    RRC_PLMN_SEARCH_TYPE_ENUM_UINT32    enCurrSearchingPlmnType;                /* 用于区别指定搜，history搜 */

    enCurrSearchingPlmnType = NAS_MMC_GetCurrSearchingType_PlmnSelection();

    switch (enCurrSearchingPlmnType)
    {
        case NAS_MMC_PLMN_SEARCH_TYPE_SPEC:
            (VOS_VOID)NAS_MMC_RcvTiWaitSpecPlmnSearchCnfExpired_PlmnSelection_WaitLmmPlmnSearchCnf(ulEventType, pstMsg);
            break;

        case NAS_MMC_PLMN_SEARCH_TYPE_HISTORY:
            NAS_MMC_RcvTiWaitHistoryPlmnSrchCnfExpired_PlmnSelection_WaitLmmPlmnSearchCnf(ulEventType, pstMsg);
            break;

        case NAS_MMC_PLMN_SEARCH_TYPE_PREFBAND:
            (VOS_VOID)NAS_MMC_RcvTiWaitSpecPlmnSearchCnfExpired_PlmnSelection_WaitLmmPlmnSearchCnf(ulEventType, pstMsg);
            break;

        default:
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitLmmPlmnSearchCnfExpired_PlmnSelection_WaitLmmPlmnSearchCnf UNEXPECTED SEARCH TYPE!!!");
            (VOS_VOID)NAS_MMC_RcvTiWaitSpecPlmnSearchCnfExpired_PlmnSelection_WaitLmmPlmnSearchCnf(ulEventType, pstMsg);
            break;
    }

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmSuspendCnf_PlmnSelection_WaitLmmSuspendCnf
 功能描述  : 收到LTE的suspend cnf消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年4月23日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2011年7月11日
   作    者   : sunxibo 46746
   修改内容   : V7R1 phase II,autoplmnsrch状态机调整为PlmnSelection状态机

 3.日    期   : 2011年12月15日
   作    者   : w00167002
   修改内容   : DTS2011120702166:MMC复位后无复位信息,在MML模块封装复位信息，
                 以供MM层调用，进行软复位。
 4.日    期   : 2011年12月14日
   作    者   : w00176964
   修改内容   : V7R1 phaseIV 调整:驻留标记通过新的搜网控制上下文代替
 5.日    期   : 2013年6月7日
   作    者   : w00176964
   修改内容   : SS FDN&Call Control项目:更新PS的注册状态
 6.日    期   : 2013年8月27日
   作    者   : l00208543
   修改内容   : Coverity
 7.日    期   : 2014年3月10日
   作    者   : f00261443
   修改内容   : 更新PS的注册状态,并不一定是NAS_MML_REG_NOT_REGISTERED_SEARCHING
 8.日    期   : 2014年2月13日
   作    者   : s00246516
   修改内容   : L-C互操作项目:增加获取和注册请求的处理
 9.日    期   : 2014年6月23日
   作    者  :  b00269685
   修改内容  :  DSDS III开发
10.日    期   : 2015年3月11日
   作    者   : wx270776
   修改内容   : DTS2015011212939:增加复位场景
*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvLmmSuspendCnf_PlmnSelection_WaitLmmSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_CNF_ST                *pstGuSuspendCnf = VOS_NULL_PTR;
    LMM_MMC_SUSPEND_CNF_STRU           *pstLmmSuspendCnf = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU          stDestPlmn;

    pstGuSuspendCnf = (RRMM_SUSPEND_CNF_ST*)pstMsg;

    /* 解决版本Coverity问题 */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    /* L模时，做如下格式转换 */
    pstLmmSuspendCnf = (LMM_MMC_SUSPEND_CNF_STRU*)pstMsg;

    pstGuSuspendCnf->ucResult = (VOS_UINT8)(pstLmmSuspendCnf->ulRst);

    /* 停止定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_SUSPEND_CNF);

    if (MMC_AS_SUSPEND_FAILURE == pstGuSuspendCnf->ucResult)
    {
        /* 不可恢复错误,调用底软接口RESET */

        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_LMM_SUSPEND_FAILURE);

        return VOS_TRUE;
    }


    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        NAS_MMC_UpdateRfAvailFlgPlmnSrchAborted_PlmnSelection();

        /* 设置当前接入技术为BUTT */
        NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* 发送搜网结果,原因为退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 搜网失败后更新RF可用标记 */
    NAS_MMC_UpdateRfAvailFlgPlmnSrchFail_PlmnSelection();

    /* 获取需要搜索的网络及其接入技术 */
    if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        /* 根据获取的接入技术设置当前接入技术 */
        NAS_MML_SetCurrNetRatType(stDestPlmn.enRat);

        /* 向接入层或LMM发送搜网请求，根据不同的搜网模式，迁移到不同的L2状态，并启动保护定时器 */
        NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);

        /* 保证挂起L回到GU时PS的注册状态始终为2,此处进行一次更新(挂起L时L可能上报的注册状态不为2) */
        NAS_MMC_UpdateRegStateSpecPlmnSearch();
    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmSuspendCnf_PlmnSelection_WaitLmmSuspendCnf,WARNING:CAN'T FIND THE NEXT PLMN");

        /* 设置当前接入技术为BUTT */
        NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

        /* Modified by s00246516 for L-C互操作项目, 2014-02-13, Begin */
        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();
        /* Modified by s00246516 for L-C互操作项目, 2014-02-13, End */
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmPlmnSearchStopCnf_PlmnSelection_WaitLmmPlmnStopCnf
 功能描述  : 收到LTE的plmn search stop cnf消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年4月23日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2011年7月11日
   作    者   : sunxibo 46746
   修改内容   : V7R1 phase II,autoplmnsrch状态机调整为PlmnSelection状态机

 3.日    期   : 2011年11月30日
   作    者   : w00176964
   修改内容   : V7R1 Phase IV调整:disable/enable 调整以及detach调整
 4.日    期   : 2011年12月14日
   作    者   : w00176964
   修改内容   : V7R1 phaseIV 调整:驻留标记通过新的搜网控制上下文代替
 5.日    期   : 2013年8月27日
   作    者   : l00208543
   修改内容   : Coverity
 6.日    期   : 2014年2月17日
   作    者   : s00217060
   修改内容   : DTS2014021203453:收到LmmStopCnf时如果已经Enable Lte，需要继续去LTE下搜网
 7.日    期   : 2014年2月13日
   作    者   : s00246516
   修改内容   : L-C互操作项目:增加获取和注册请求的处理
 8.日    期   : 2014年6月21日
   作    者   : b00269685
   修改内容   : DSDS III项目

*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvLmmPlmnSearchStopCnf_PlmnSelection_WaitLmmPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_PLMN_WITH_RAT_STRU          stDestPlmn;

    /* 解决版本Coverity问题 */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    NAS_MMC_StopTimer( TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF );

    /* 有打断时，退出状态机 */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        NAS_MMC_UpdateRfAvailFlgPlmnSrchAborted_PlmnSelection();

        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 搜网失败后更新RF可用标记 */
    NAS_MMC_UpdateRfAvailFlgPlmnSrchFail_PlmnSelection();

    /* 无打断时:如果当前LTE的能力状态为disable LTE，则搜索下个非LTE的网络
        如果当前LTE的能力状态为Enable LTE,则搜索下个可用的LTE网络
        Enable LTE对应的场景为:等LMM的搜网结果时收到LmmDetachCnf，需要Disable LTE,迁到等LmmStopCnf状态
        在等待LmmStopCnf时，收到LmmAttachCnf，又需要Enable LTE,此时在收到LmmStopCnf需要继续去LTE下搜网 */

    /* 当还存在下一个需要搜索的网络时，继续进行搜网，否则，进入限制驻留 */
    if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        if (NAS_MML_NET_RAT_TYPE_LTE == stDestPlmn.enRat)
        {
            /* 向LMM发送搜网请求，迁移状态，并启动保护定时器 */
            NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
        }
        else
        {
            /* 向接入层或LMM发送挂起请求，根据当前不同的接入技术，迁移到不同的L2状态，并启动保护定时器 */
            NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE);
        }
    }
    else
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

            /* Modified by s00246516 for L-C互操作项目, 2014-02-13, Begin */
            NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();
            /* Modified by s00246516 for L-C互操作项目, 2014-02-13, End */
    }

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmSpecPlmnSearchCnf_PlmnSelection_WaitLmmPlmnStopCnf
 功能描述  : 收到LTE的spec plmn search cnf消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年6月25日
   作    者   : b00269685
   修改内容   : DSDS III项目新增
 2.日    期   : 2015年5月26日
   作    者   : w00167002
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0项目修改
*****************************************************************************/
VOS_VOID NAS_MMC_RcvLmmSpecPlmnSearchCnf_PlmnSelection_WaitLmmPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_PLMN_SRCH_CNF_STRU         *pstLmmSrchCnfMsg = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU          stDestPlmn;

    pstLmmSrchCnfMsg = (LMM_MMC_PLMN_SRCH_CNF_STRU*)pstMsg;

    /* 解决版本Coverity问题 */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    NAS_MMC_StopTimer( TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF );

    /* 有打断时，退出状态机 */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        NAS_MMC_UpdateRfAvailFlgPlmnSrchAborted_PlmnSelection();

        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* 如果当前为NO RF，则直接退状态机 */
    if (MMC_LMM_PLMN_SRCH_RLT_SPEC_NO_RF == pstLmmSrchCnfMsg->enRlst)
    {
        NAS_MMC_ProcNoRf_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE);

        return;
    }

    /* 搜网失败后更新RF可用标记 */
    NAS_MMC_UpdateRfAvailFlgPlmnSrchFail_PlmnSelection();

    /* 无打断时:如果当前LTE的能力状态为disable LTE，则搜索下个非LTE的网络
        如果当前LTE的能力状态为Enable LTE,则搜索下个可用的LTE网络
        Enable LTE对应的场景为:等LMM的搜网结果时收到LmmDetachCnf，需要Disable LTE,迁到等LmmStopCnf状态
        在等待LmmStopCnf时，收到LmmAttachCnf，又需要Enable LTE,此时在收到LmmStopCnf需要继续去LTE下搜网 */

    /* 当还存在下一个需要搜索的网络时，继续进行搜网，否则，进入限制驻留 */
    if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        if (NAS_MML_NET_RAT_TYPE_LTE == stDestPlmn.enRat)
        {
            /* 向LMM发送搜网请求，迁移状态，并启动保护定时器 */
            NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
        }
        else
        {
            /* 向接入层或LMM发送挂起请求，根据当前不同的接入技术，迁移到不同的L2状态，并启动保护定时器 */
            NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE);
        }
    }
    else
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmSpecPlmnSearchCnf_PlmnSelection_WaitLmmPlmnStopCnf
 功能描述  : 收到LTE的history plmn search cnf消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年5月26日
   作    者   : w00167002
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0项目修改
*****************************************************************************/
VOS_VOID NAS_MMC_RcvLmmHistoryPlmnSearchCnf_PlmnSelection_WaitLmmPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_PLMN_SRCH_CNF_STRU         *pstLmmSrchCnfMsg = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU          stDestPlmn;

    pstLmmSrchCnfMsg = (LMM_MMC_PLMN_SRCH_CNF_STRU*)pstMsg;

    /* 解决版本Coverity问题 */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    NAS_MMC_StopTimer( TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF );

    /* 有打断时，退出状态机 */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        NAS_MMC_UpdateRfAvailFlgPlmnSrchAborted_PlmnSelection();

        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* 如果当前为NO RF，则直接退状态机 */
    if (MMC_LMM_PLMN_SRCH_RLT_HISTORY_NO_RF == pstLmmSrchCnfMsg->enRlst)
    {
        NAS_MMC_ProcNoRf_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE);

        return;
    }

    /* 搜网失败后更新RF可用标记 */
    NAS_MMC_UpdateRfAvailFlgPlmnSrchFail_PlmnSelection();

    /* 无打断时:如果当前LTE的能力状态为disable LTE，则搜索下个非LTE的网络
        如果当前LTE的能力状态为Enable LTE,则搜索下个可用的LTE网络
        Enable LTE对应的场景为:等LMM的搜网结果时收到LmmDetachCnf，需要Disable LTE,迁到等LmmStopCnf状态
        在等待LmmStopCnf时，收到LmmAttachCnf，又需要Enable LTE,此时在收到LmmStopCnf需要继续去LTE下搜网 */

    /* 当还存在下一个需要搜索的网络时，继续进行搜网，否则，进入限制驻留 */
    if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        if (NAS_MML_NET_RAT_TYPE_LTE == stDestPlmn.enRat)
        {
            /* 向LMM发送搜网请求，迁移状态，并启动保护定时器 */
            NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
        }
        else
        {
            /* 向接入层或LMM发送挂起请求，根据当前不同的接入技术，迁移到不同的L2状态，并启动保护定时器 */
            NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE);
        }
    }
    else
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmPrefBandPlmnSearchCnf_PlmnSelection_WaitLmmPlmnStopCnf
 功能描述  : 收到LTE的pref band plmn search cnf消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年10月13日
   作    者   : s00217060
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_RcvLmmPrefBandPlmnSearchCnf_PlmnSelection_WaitLmmPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_PLMN_SRCH_CNF_STRU         *pstLmmSrchCnfMsg = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU          stDestPlmn;

    pstLmmSrchCnfMsg = (LMM_MMC_PLMN_SRCH_CNF_STRU*)pstMsg;

    /* 解决版本Coverity问题 */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    NAS_MMC_StopTimer( TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF );

    /* 有打断时，退出状态机 */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        NAS_MMC_UpdateRfAvailFlgPlmnSrchAborted_PlmnSelection();

        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* 如果当前为NO RF，则直接退状态机 */
    if (MMC_LMM_PLMN_SRCH_RLT_PREF_BAND_NO_RF == pstLmmSrchCnfMsg->enRlst)
    {
        NAS_MMC_ProcNoRf_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE);

        return;
    }

    /* 搜网失败后更新RF可用标记 */
    NAS_MMC_UpdateRfAvailFlgPlmnSrchFail_PlmnSelection();

    /* 无打断时:如果当前LTE的能力状态为disable LTE，则搜索下个非LTE的网络
        如果当前LTE的能力状态为Enable LTE,则搜索下个可用的LTE网络
        Enable LTE对应的场景为:等LMM的搜网结果时收到LmmDetachCnf，需要Disable LTE,迁到等LmmStopCnf状态
        在等待LmmStopCnf时，收到LmmAttachCnf，又需要Enable LTE,此时在收到LmmStopCnf需要继续去LTE下搜网 */

    /* 当还存在下一个需要搜索的网络时，继续进行搜网，否则，进入限制驻留 */
    if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        if (NAS_MML_NET_RAT_TYPE_LTE == stDestPlmn.enRat)
        {
            /* 向LMM发送搜网请求，迁移状态，并启动保护定时器 */
            NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
        }
        else
        {
            /* 向接入层或LMM发送挂起请求，根据当前不同的接入技术，迁移到不同的L2状态，并启动保护定时器 */
            NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE);
        }
    }
    else
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmPlmnSearchCnf_PlmnSelection_WaitLmmPlmnStopCnf
 功能描述  : 收到LTE的plmn search cnf消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年6月25日
   作    者   : b00269685
   修改内容   : DSDS III项目新增
 2.日    期   : 2015年5月26日
   作    者   : w00167002
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0项目修改
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmPlmnSearchCnf_PlmnSelection_WaitLmmPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_PLMN_SRCH_CNF_STRU         *pstLmmSrchCnfMsg = VOS_NULL_PTR;

    pstLmmSrchCnfMsg = (LMM_MMC_PLMN_SRCH_CNF_STRU*)pstMsg;

    switch (pstLmmSrchCnfMsg->enRlst)
    {
        case MMC_LMM_PLMN_SRCH_RLT_SPEC_SUCC:
        case MMC_LMM_PLMN_SRCH_RLT_SPEC_NO_RF:
        case MMC_LMM_PLMN_SRCH_RLT_SPEC_FAIL:

            /* L下指定搜网的处理 */
            NAS_MMC_RcvLmmSpecPlmnSearchCnf_PlmnSelection_WaitLmmPlmnStopCnf(ulEventType, pstMsg);
            break;

        case MMC_LMM_PLMN_SRCH_RLT_HISTORY_SUCC:
        case MMC_LMM_PLMN_SRCH_RLT_HISTORY_NO_RF:
        case MMC_LMM_PLMN_SRCH_RLT_HISTORY_FAIL:

            /* L下HISTORY指定搜网的处理 */
            NAS_MMC_RcvLmmHistoryPlmnSearchCnf_PlmnSelection_WaitLmmPlmnStopCnf(ulEventType, pstMsg);
            break;

        /* L下pref band搜网的处理 */
        case MMC_LMM_PLMN_SRCH_RLT_PREF_BAND_SUCC:
        case MMC_LMM_PLMN_SRCH_RLT_PREF_BAND_NO_RF:
        case MMC_LMM_PLMN_SRCH_RLT_PREF_BAND_FAIL:

            NAS_MMC_RcvLmmPrefBandPlmnSearchCnf_PlmnSelection_WaitLmmPlmnStopCnf(ulEventType, pstMsg);
            break;

        default:
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmPlmnSearchCnf_PlmnSelection_WaitLmmPlmnStopCnf: UNEXPECTED RSLT TYPE!!!");
            NAS_MMC_RcvLmmSpecPlmnSearchCnf_PlmnSelection_WaitLmmPlmnStopCnf(ulEventType, pstMsg);
            break;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitLmmStopCnfExpired_PlmnSelection_WaitLmmPlmnStopCnf
 功能描述  : LTE的plmn search stop CNF过程中保护定时器超时
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年4月23日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2011年7月11日
   作    者   : sunxibo 46746
   修改内容   : V7R1 phase II,autoplmnsrch状态机调整为PlmnSelection状态机

 3.日    期   : 2011年11月30日
   作    者   : w00176964
   修改内容   : V7R1 Phase IV调整:disable/enable 调整
 4.日    期   : 2011年12月14日
   作    者   : w00176964
   修改内容   : V7R1 phaseIV 调整:驻留标记通过新的搜网控制上下文代替
 5.日    期   : 2013年8月27日
   作    者   : l00208543
   修改内容   : Coverity
 6.日    期   : 2014年2月17日
   作    者   : s00217060
   修改内容   : DTS2014021203453:收到LmmStopCnf时如果已经Enable Lte，需要继续去LTE下搜网
 7.日    期   : 2014年2月13日
   作    者   : s00246516
   修改内容   : L-C互操作项目:增加获取和注册请求的处理
 8.日    期   : 2014年6月21日
   作    者   : b00269685
   修改内容   : DSDS III项目
****************************************************************************/

VOS_UINT32 NAS_MMC_RcvTiWaitLmmStopCnfExpired_PlmnSelection_WaitLmmPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_PLMN_WITH_RAT_STRU                              stDestPlmn;

    /* 解决版本Coverity问题 */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitLmmStopCnfExpired_PlmnSelection_WaitLmmPlmnStopCnf: Timer Expired");

    /* 有打断时，退出状态机 */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        NAS_MMC_UpdateRfAvailFlgPlmnSrchAborted_PlmnSelection();

        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 搜网失败后更新RF可用标记 */
    NAS_MMC_UpdateRfAvailFlgPlmnSrchFail_PlmnSelection();

    /* 无打断时:如果当前LTE的能力状态为disable LTE，则搜索下个非LTE的网络
        如果当前LTE的能力状态为Enable LTE,则搜索下个可用的LTE网络
        Enable LTE对应的场景为:等LMM的搜网结果时收到LmmDetachCnf，需要Disable LTE,迁到等LmmStopCnf状态
        在等待LmmStopCnf时，收到LmmAttachCnf，又需要Enable LTE,此时在收到LmmStopCnf需要继续去LTE下搜网 */

    /* 当还存在下一个需要搜索的网络时，继续进行搜网，否则，进入限制驻留 */
    if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        if (NAS_MML_NET_RAT_TYPE_LTE == stDestPlmn.enRat)
        {
            /* 向LMM发送搜网请求，迁移状态，并启动保护定时器 */
            NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
        }
        else
        {
            /* 向接入层或LMM发送挂起请求，根据当前不同的接入技术，迁移到不同的L2状态，并启动保护定时器 */
            NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE);
        }
    }
    else
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        /* Modified by s00246516 for L-C互操作项目, 2014-02-13, Begin */
        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();
        /* Modified by s00246516 for L-C互操作项目, 2014-02-13, End */
    }

    return VOS_TRUE;


}
/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitLmmSysInfoInd
 功能描述  : MMC处理Aort消息
 输入参数  : ulEventType:消息类型
             pstMsg:Abort消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月12日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2011年7月14日
    作    者   : l00130025
    修改内容   : PhaseII修改,PlmnSelection状态机调整
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitLSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    NAS_MMC_SetAbortFlag_PlmnSelection(VOS_TRUE);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLSysInfoInd_PlmnSelection_WaitLSysInfoInd
 功能描述  : MMC处理LMM上报的系统消息
 输入参数  : ulEventType:消息类型
             pstMsg:LMM上报的系统消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月20日
    作    者   : W00167002
    修改内容   : 新生成函数
  2.日    期   : 2011年7月14日
    作    者   : l00130025
    修改内容   : PhaseII修改,PlmnSelection状态机调整
  3.日    期   : 2011年10月6日
    作    者   : w00167002
    修改内容   : PhaseII修改:删除更改当前的网络的注册状态为REGISTERED，
                 统一等注册结果后，才更改为REGISTERED
  4.日    期   : 2011年12月30日
    作    者   : l65478
    修改内容   : 在迁到L模时,不立刻把CS设置成可选搜网,而是等待PS注册结果时
                 根据具体的原因值再设置

  5.日    期   : 2011年12月14日
    作    者   : w00176964
    修改内容   : V7R1 phaseIV 调整:驻留标记通过新的搜网控制上下文代替
  6.日    期   : 2012年4月18日
    作    者   : l00130025
    修改内容   : DTS2012040200480,单独维护EPS注册状态,供查询和上报使用
  7.日    期   : 2012年4月28日
    作    者   : W00166186
    修改内容   : DTS2012042602593,MM没有保存当前驻留的PLMN，导致后续判断出错
  8.日    期   : 2012年6月11日
    作    者   : s00217060
    修改内容   : For CS/PS mode 1
  9.日    期   : 2012年11月29日
    作    者   : w00176964
    修改内容   : DTS2012042804167:通知CBA模块当前接入模式为LTE
 10.日    期   : 2012年12月20日
    作    者   : w00176964
    修改内容   : DTS2012121906946:收到L的系统消息转发给LMM
 11.日    期   : 2013年1月19日
    作    者   : t00212959
    修改内容   : DTS2012122900189:EPS注册状态完全由L上报
 12.日    期   : 2013年2月7日
    作    者   : W00176964
    修改内容   : Volte_phase3项目调整:增加IMS不可用时disable L模的逻辑修改
 13.日    期   : 2014年1月28日
    作    者   : s00246516
    修改内容   : L-C互操作项目:增加获取和注册请求的处理
 14.日    期   : 2014年6月13日
    作    者   : b00269685
    修改内容   : L-C互操作项目: 更新状态机入口消息
 15.日    期   : 2015年02月11日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseII 项目修改
                 方案优化后，LTE下的小区发生变化，LMM会通过系统消息通知MMC
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLSysInfoInd_PlmnSelection_WaitLSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;

    NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8                enSpecPlmnSearchState;
    /* Added by s00246516 for L-C互操作项目, 2014-01-28, Begin */
    MSCC_MMC_PLMN_ID_STRU                stPlmnId;
    VOS_UINT32                          ulCurrentEventType;
    LMM_MMC_SYS_INFO_IND_STRU          *pstLmmSysInfoMsg    = VOS_NULL_PTR;
    /* Added by s00246516 for L-C互操作项目, 2014-01-28, End */

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    PS_MEM_SET(&stPlmnId, 0, sizeof(MSCC_MMC_PLMN_ID_STRU));

    /* 停止等待系统消息的定时器  */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_SYS_INFO);

    /* 状态更新为当前已经驻留 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

    ulCurrentEventType = NAS_MMC_GetCurrFsmEventType();

    /* 如果当前需要退出状态机 */
    if (VOS_TRUE  == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        /* 回复状态机退出成功 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* Added by s00246516 for L-C互操作项目, 2014-01-28, Begin */
    if (VOS_FALSE == NAS_MMC_IsAllowedRegAfterAcqSucc_PlmnSelection())
    {
        /* 如果入口是获取请求，向MSCC回复获取成功，否则上报获取指示 */
        pstLmmSysInfoMsg  = (LMM_MMC_SYS_INFO_IND_STRU*)pstMsg;
        NAS_MMC_ConvertLmmPlmnToGUNasFormat(&(pstLmmSysInfoMsg->stLteSysInfo.stSpecPlmnIdList.astSuitPlmnList[0]), &stPlmnId);

        if (NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_ACQ_REQ) == ulCurrentEventType)
        {
            NAS_MMC_SndMsccAcqCnf(NAS_MSCC_PIF_ACQ_RESULT_SUCCESS, &stPlmnId, pstLmmSysInfoMsg->stLteSysInfo.ulArfcn);

            NAS_MMC_SaveCommonPlmnSrchEntryMsg_PlmnSelection();
        }
        else
        {
            NAS_MMC_SndMsccAcqInd(NAS_MSCC_PIF_ACQ_RESULT_SUCCESS, &stPlmnId, pstLmmSysInfoMsg->stLteSysInfo.ulArfcn);
        }

        /* 状态迁移到NAS_MMC_PLMN_SELECTION_STA_WAIT_MSCC_REG_REQ */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_MSCC_REG_REQ);

        /* 启动保护定时器 */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MSCC_REG_REQ, TI_NAS_MMC_WAIT_MSCC_REG_REQ_LEN);

        return VOS_TRUE;
    }
    /* Added by s00246516 for L-C互操作项目, 2014-01-28, End */

    /* 保留老的驻留网络信息 */
    pstCurCampInfo  = NAS_MML_GetCurrCampPlmnInfo();
    PS_MEM_CPY(&stOldCampInfo, pstCurCampInfo, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

    /* 根据系统消息，更新MML的全部变量 */
    NAS_MMC_UpdateNetworkInfo_LmmSysInfo(pstMsg);





    /* 更新当前等待EPS的注册结果 */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnSelection();
    NAS_MMC_SetWaitRegRsltFlag_PlmnSelection(NAS_MMC_WAIT_REG_RESULT_IND_PS);

    /* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-7, begin */
#if (FEATURE_ON == FEATURE_IMS)
    /* 增加等待IMS是否可用结果FLG,MMA保证收到PS注册结果上报IMS是否可用指示到MMC */
    NAS_MMC_SetWaitRegRsltFlag_PlmnSelection(NAS_MMC_WAIT_REG_RESULT_IND_IMS);
#endif
    /* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-7, end */

    /* 更新CS的注册Cause和AdditionalAction */
    NAS_MMC_SetCsRegCause_PlmnSelection(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);

    NAS_MMC_SetPsRegCause_PlmnSelection(NAS_MML_REG_FAIL_CAUSE_BUTT);

    NAS_MMC_SetCsRegAdditionalAction_PlmnSelection(NAS_MMC_ADDITIONAL_ACTION_BUTT);
    NAS_MMC_SetPsRegAdditionalAction_PlmnSelection(NAS_MMC_ADDITIONAL_ACTION_BUTT);

    /* CBS上报*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_LTE);

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, end */
    /*方案优化后，LTE下的小区发生变化，LMM会通过系统消息通知MMC*/
    enSpecPlmnSearchState = NAS_MMC_GetSpecPlmnSearchState();

    if ((VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
     || (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == enSpecPlmnSearchState))
    {
        /* 主动上报 */
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, begin*/
        NAS_MMC_SndMsccSysInfo();
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, end*/

    }

    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_STOP);

    /* 转发GMM系统消息,供rabm使用 */
    NAS_MMC_SndGmmLteSysinfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);
    NAS_MMC_SndMmLteSysinfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);

    NAS_MMC_SndLmmLteSysInfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);

    /* 迁移到等待注册结果子状态PLMN_SRCH:NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_REG_IND, TI_NAS_MMC_WAIT_EPS_REG_IND_LEN);

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitSysInfoExpired_PlmnSelection_WaitLSysInfoInd
 功能描述  : 等待系统消息定时器超时超时的处理
 输入参数  : ulEventType:消息类型
             pstMsg:TI_NAS_MMC_WAIT_SYS_INFO超时消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月20日
    作    者   : W00167002
    修改内容   : 新生成函数
  2.日    期   : 2011年7月14日
    作    者   : l00130025
    修改内容   : PhaseII修改,PlmnSelection状态机调整
  3.日    期   : 2011年12月15日
    作    者   : W00166186
    修改内容   : dts2011111502641,L下PLMN加入禁止TA后不再搜网
  4.日    期   : 2011年12月14日
    作    者   : w00176964
    修改内容   : V7R1 phaseIV 调整:驻留标记通过新的搜网控制上下文代替
  5.日    期   : 2012年7月16日
    作    者   : s00217060
    修改内容   : for DTS2012071604442
                 调整:LMM系统消息定时器超时,并且获取下一个网络失败需要重新驻留LTE
  6.日    期   : 2012年09月27日
    作    者   : z00161729
    修改内容   : DTS2012090303562:搜网状态机等L注册结果收到丢网消息获取下一个网络失败退状态机后又发起非法随机网络搜网
  7.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  8.日    期   : 2013年8月27日
    作    者   : l00208543
    修改内容   : Coverity
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitLSysInfoExpired_PlmnSelection_WaitLSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    NAS_MML_PLMN_WITH_RAT_STRU          stDestPlmn;
    VOS_UINT32                          ulResult;

    /* 解决版本Coverity问题 */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitLSysInfoExpired_PlmnSelection_WaitLSysInfoInd: Timer Expired");

    /* 清除驻留状态 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);

    /*如果当前需要退出状态机*/
    if (VOS_TRUE  == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        /* 回复状态机退出成功 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);
    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* 当前信号更新 */
    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());

    /*获取下一个要搜索的网络,若获取失败，则给上层状态机上报搜网失败，退出
      若获取成功，则判断下一个要搜索的网络是否与当前驻留网络相同，
      若相同则在当前模式发起搜网，否则挂起当前网络
     */
    ulResult = NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn);

    /*  获取下个网络失败，则进行出服务区处理*/
    if (VOS_TRUE != ulResult)
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();
        return VOS_TRUE;
    }

    /* 向MM、GMM发送搜网指示 */
    NAS_MMC_SndGmmPlmnSchInit();
    NAS_MMC_SndMmPlmnSchInit();

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, end */

    NAS_MMC_UpdateRegStateSpecPlmnSearch();

    /*下一个要搜索的网络是否与当前驻留网络不同,需要挂起当前模式，切换到等待挂起状态，启动保护定时器*/
    if (stDestPlmn.enRat != NAS_MML_GetCurrNetRatType())
    {
        NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_GetCurrNetRatType());
    }
    /* 不需要Suspend */
    else
    {
        /* 向接入层或LMM发送搜网请求，根据不同的搜网模式，迁移到不同的L2状态，并启动保护定时器 */
        NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
    }


    return VOS_TRUE;

}




/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnSrch_WaitEpsRegRsltInd
 功能描述  : 在等待EPS上报注册结果的时候收到QUIT消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg: Abort消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月20日
    作    者   : W00167002
    修改内容   : 新生成函数
  2.日    期   : 2011年7月14日
    作    者   : l00130025
    修改内容   : PhaseII修改,PlmnSelection状态机调整
  3.日    期   : 2011年11月29日
    作    者   : w00167002
    修改内容   : DTS2011112301233:增加打断事件ID，状态机可以知道是什么事件
                打断自己的。
                修改原因:用户下发关机命令后，当前可能在等注册结果或者在等连接
                释放，可能需要比较久的时间才能处理关机命令，通过增加打断事件，
                如归当前在等注册结果或者等链接释放状态，若收到关机命令，则直接
                退出当前状态机，处理用户的关机命令。
  4.日    期   : 2011年12月14日
    作    者   : w00176964
    修改内容   : V7R1 phaseIV 调整:驻留标记通过新的搜网控制上下文代替
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitEpsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ABORT_FSM_STRU             *pstAbortMsg;

    pstAbortMsg = (NAS_MMC_ABORT_FSM_STRU*)pstMsg;


    /* 若打断类型是用户请求的关机，则直接退出等注册结果状态机 */
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, begin*/
    if (NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_OFF_REQ) == pstAbortMsg->ulEventType)
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, end*/
    {
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

        /* 回复状态机退出成功 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 当前没有链接可以直接退出 */
    if ( VOS_FALSE == NAS_MML_IsRrcConnExist())
    {
        /* 停止等待eps注册结果消息的定时器  */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

        /* 回复状态机退出成功 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 设置Abort标志 */
    NAS_MMC_SetAbortFlag_PlmnSelection(VOS_TRUE);

    /* 如果需要立即退出 */
    if (NAS_MMC_ABORT_FSM_IMMEDIATELY == pstAbortMsg->enAbortFsmType)
    {
        /* 停止等待eps注册结果消息的定时器  */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

        /* 主动请求释放链接 */
        NAS_MMC_SndLmmRelReq();

        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_CONN_REL_IND);
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND, TI_NAS_MMC_WAIT_EPS_CONN_REL_IND_LEN);
    }

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmMmcDetachInd_PlmnSelection_WaitEpsConnRelInd
 功能描述  : 在等待EPS链路释放的时候网侧detach的的处理
 输入参数  : ulEventType:消息类型
             pstMsg: ID_LMM_MMC_DETACH_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月01日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2013年1月11日
    作    者   : w00176964
    修改内容   : DTS2013010706662:调整发送EPLMN逻辑调用位置
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmMmcDetachInd_PlmnSelection_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_DETACH_IND_STRU                                *pstDetachMsg = VOS_NULL_PTR;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsAdditionalAction;

    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));
    pstDetachMsg        = (LMM_MMC_DETACH_IND_STRU*)pstMsg;

    /* 处理DETACH消息，返回下一步动作 */
    NAS_MMC_ProcLmmDetachInd(pstDetachMsg, &enCsAdditionalAction, &enPsAdditionalAction);

    /*更新EPS的下一步的动作类型*/
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enPsAdditionalAction)
    {
        NAS_MMC_SetPsRegAdditionalAction_PlmnSelection(enPsAdditionalAction);
    }

    /*更新CS的下一步的动作类型*/
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enCsAdditionalAction)
    {
        NAS_MMC_SetCsRegAdditionalAction_PlmnSelection(enCsAdditionalAction);
    }

    if (VOS_TRUE == NAS_MMC_IsNeedSndEplmn_PlmnSelection())
    {
        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildSndLmmEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndLmmEquPlmnReq(&stSndEquPlmnInfo);
        NAS_MMC_SndOmEquPlmn();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmMmcDetachCnf_PlmnSelection_WaitEpsConnRelInd
 功能描述  : 在等待EPS链路释放的时候用户detach CNF的的处理
 输入参数  : ulEventType:消息类型
             pstMsg: ID_LMM_MMC_DETACH_CNF消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月14日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmMmcDetachCnf_PlmnSelection_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_DETACH_CNF_STRU                                *pstDetachCnfMsg = VOS_NULL_PTR;

    pstDetachCnfMsg        = (LMM_MMC_DETACH_CNF_STRU*)pstMsg;

    /* 不过detach结果不是鉴权被拒，不需要进状态机，预处理中就可以处理 */
    if ( MMC_LMM_DETACH_RSLT_AUTH_REJ != pstDetachCnfMsg->ulDetachRslt)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmMmcDetachCnf_PlmnSelection_WaitEpsConnRelInd: Unexpected detach result!");

        return VOS_TRUE;
    }

    /*更新EPS的下一步的动作类型*/
    NAS_MMC_SetPsRegAdditionalAction_PlmnSelection(NAS_MMC_ADDITIONAL_ACTION_CSPS_ANYCELL);

    /*更新CS的下一步的动作类型*/
    NAS_MMC_SetCsRegAdditionalAction_PlmnSelection(NAS_MMC_ADDITIONAL_ACTION_CSPS_ANYCELL);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmMmcStatusInd_PlmnSelection_WaitEpsRegRsltInd
 功能描述  : LMM上报的CONN Status Ind消息处理函数
 输入参数  : ulEventType:消息类型
             pstMsg:ID_LMM_MMC_STATUS_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:返回处理成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月20日
    作    者   : W00167002
    修改内容   : 新生成函数
  2.日    期   : 2011年7月14日
    作    者   : l00130025
    修改内容   : PhaseII修改,PlmnSelection状态机调整
  3.日    期   : 2015年9月17日
    作    者   : y00346957
    修改内容   : DTS2015070910885 增加当前搜索的plmn是否允许搜的判断
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmMmcStatusInd_PlmnSelection_WaitEpsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_STATUS_IND_STRU            *pstLmmStatusIndMsg = VOS_NULL_PTR;
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    NAS_MML_PLMN_WITH_RAT_STRU         *pstPlmnWithRat     = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                stPlmnId;
#endif

    pstLmmStatusIndMsg = (LMM_MMC_STATUS_IND_STRU*)pstMsg;

    if ( VOS_FALSE == pstLmmStatusIndMsg->bitOpConnState)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmMmcStatusInd_PlmnSelection_WaitEpsRegRsltInd:bitOpConnState IS VOS_FALSE");
        return VOS_TRUE;
    }

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

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        return VOS_TRUE;
    }

    pstPlmnWithRat      = NAS_MMC_GetCurrSearchingPlmn_PlmnSelection();
    stPlmnId.ulMcc      = pstPlmnWithRat->stPlmnId.ulMcc;
    stPlmnId.ulMnc      = pstPlmnWithRat->stPlmnId.ulMnc;

    /* 判断lte plmn是否允许搜索 */
    if (VOS_FALSE == NAS_MMC_IsCurrLtePlmnAllowSrchInCLMode(&stPlmnId))
    {
        NAS_WARNING_LOG2(WUEPS_PID_MMC, "NAS_MMC_RcvLmmMmcStatusInd_PlmnSelection_WaitEpsRegRsltInd:WARNING: Current Lte Plmn is not Allowed Srch In CL Mode,ulMcc and ulMnc are",
                                             stPlmnId.ulMcc, stPlmnId.ulMnc);

        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

        /* 搜下个plmn */
        NAS_MMC_SearchNextPlmn_PlmnSelection();
    }
#endif
    return VOS_TRUE;

}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmMmcAttachInd_PlmnSelection_WaitEpsRegRsltInd
 功能描述  : WaitEpsRegRsltInd时，LMM上报的ID_LMM_MMC_ATTACH_IND消息处理函数
 输入参数  : ulEventType:消息类型
             pstMsg:ID_LMM_MMC_ATTACH_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:返回处理成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月20日
    作    者   : W00167002
    修改内容   : 新生成函数
  2.日    期   : 2011年7月22日
    作    者   : l00130025
    修改内容   : PhaseII修改
  3.日    期   : 2011年10月25日
    作    者   : z00161729
    修改内容   : PhaseIII支持联合注册修改
  4.日    期   : 2011年12月14日
    作    者   : w00176964
    修改内容   : V7R1 phaseIV 调整:驻留标记通过新的搜网控制上下文代替
  5.日    期   : 2012年1月8日
    作    者   : z00161729
    修改内容   : V7R1 Phase IV调整
  6.日    期   : 2012年6月2日
    作    者   : s00217060
    修改内容   : For CS/PS mode 1, 如果当前已经设置需要Disable L,并且注册成功，
                  保存当前L网络到状态机上下文中
7.日    期   : 2012年12月07日
   作    者   : t00212959
   修改内容   : DTS2012120608079:Lattach之前下发列表搜，需要disableL时，退出状态机，无法获取CS服务
8.日    期   : 2012年12月11日
   作    者   : l00167671
   修改内容   : DTS2012121802573, TQE清理
 9.日    期   : 2015年4月22日
   作    者   : wx270776
   修改内容   : DTS2015031602665:将CL ATTACH注册状态存入全局变量
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmMmcAttachInd_PlmnSelection_WaitEpsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCsRegCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enPsRegCause;
    LMM_MMC_ATTACH_IND_STRU            *pstLmmAttachIndMsg = VOS_NULL_PTR;
    NAS_MMC_FSM_ID_ENUM_UINT32          enCurrentFsmId;
    VOS_UINT32                          ulCurrentEventType;

    NAS_MML_LTE_UE_OPERATION_MODE_ENUM_UINT8                enUeOperationMode;

    enUeOperationMode   =  NAS_MML_GetLteUeOperationMode();
    pstLmmAttachIndMsg  = (LMM_MMC_ATTACH_IND_STRU*)pstMsg;

    NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnSelection(NAS_MMC_WAIT_REG_RESULT_IND_PS);

    if ( VOS_TRUE == NAS_MMC_IsNeedUpdateLmmAttachClRegStatus_PlmnSelection(pstLmmAttachIndMsg->enClAttRegStatus) )
    {
        NAS_MMC_SetLmmAttachClRegStatus_PlmnSelection(pstLmmAttachIndMsg->enClAttRegStatus);
    }

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
    NAS_MMC_ProcLmmAttachInd_PlmnSelection(pstLmmAttachIndMsg);

    /* 已经Disable L并且注册成功,需要将当前网络保存在状态机上下文中,用于后续
       GU搜索失败重新回该网络提供PS业务*/
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS == NAS_MML_GetLteCapabilityStatus())
      && (MMC_LMM_ATT_RSLT_SUCCESS == pstLmmAttachIndMsg->ulAttachRslt))
    {
        /* 保存当前网络在状态机上下文中 */
        NAS_MMC_SetCsPsMode1ReCampLtePlmn_PlmnSelection(NAS_MML_GetCurrCampPlmnId());
    }

    enCurrentFsmId     = NAS_MMC_GetCurrFsmId();
    if (NAS_MMC_FSM_PLMN_SELECTION != enCurrentFsmId)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }
    ulCurrentEventType = NAS_MMC_GetCurrFsmEventType();
    if (VOS_TRUE == NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enCurrentFsmId,ulCurrentEventType))
    {
        enCsRegCause = NAS_MMC_GetCsRegCause_PlmnSelection();
        enPsRegCause = NAS_MMC_GetPsRegCause_PlmnSelection();

        if (VOS_TRUE == NAS_MMC_ProcUserSearchRegRslt_PlmnSelection(enCsRegCause,enPsRegCause))
        {
            /*更新入口消息为普通的搜网请求，后续有新的用户请求时，可以打断该状态机*/
            NAS_MMC_SaveCommonPlmnSrchEntryMsg_PlmnSelection();
        }
    }

    if (NAS_MMC_WAIT_REG_RESULT_IND_NULL != NAS_MMC_GetWaitRegRsltFlag_PlmnSelection())
    {
        return VOS_TRUE;
    }

    /* 如果当前需要退出状态机 */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {

        if (VOS_TRUE == NAS_MMC_IsDisableLteNeedLocalReleaseEpsConn())
        {
            NAS_MMC_SndLmmRelReq();

            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_CONN_REL_IND);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND, TI_NAS_MMC_WAIT_EPS_CONN_REL_IND_LEN);

            return VOS_TRUE;
        }


        /* 回复状态机退出成功 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* 停止等待eps注册结果消息的定时器  */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    NAS_MMC_PerformAdditionalActionRegFinished_PlmnSelection();

    return VOS_TRUE;

}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmMmcTauResultInd_PlmnSelection_WaitEpsRegRsltInd
 功能描述  : 在PLMN SRCH时候收到ID_LMM_MMC_TAU_RESULT_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:返回处理成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月20日
    作    者   : W00167002
    修改内容   : 新生成函数
  2.日    期   : 2011年7月22日
    作    者   : l00130025
    修改内容   : PhaseII修改
  3.日    期   : 2011年10月26日
    作    者   : w00176964
    修改内容   : V7R1 Phase III调整:联合注册修改
  4.日    期   : 2011年12月14日
    作    者   : w00176964
    修改内容   : V7R1 phaseIV 调整:驻留标记通过新的搜网控制上下文代替
  5.日    期   : 2012年6月2日
    作    者   : s00217060
    修改内容   : For CS/PS mode 1, 如果已经Disable L, 并且TAU成功，
                  保存当前网络到状态机上下文中
  6.日    期   : 2012年12月11日
    作    者   : l00167671
    修改内容   : DTS2012121802573, TQE清理
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmMmcTauResultInd_PlmnSelection_WaitEpsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCsRegCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enPsRegCause;
    LMM_MMC_TAU_RESULT_IND_STRU        *pstLmmTauIndMsg = VOS_NULL_PTR;
    NAS_MMC_FSM_ID_ENUM_UINT32          enCurrentFsmId;
    VOS_UINT32                          ulCurrentEventType;

    pstLmmTauIndMsg  = (LMM_MMC_TAU_RESULT_IND_STRU*)pstMsg;

    NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnSelection(NAS_MMC_WAIT_REG_RESULT_IND_PS);

    /* 向GMM和MM转发注册结果消息 */
    NAS_MMC_SndMmLmmTauResultInd(pstLmmTauIndMsg);
    NAS_MMC_SndGmmLmmTauResultInd(pstLmmTauIndMsg);

    /* 处理tau结果 */
    NAS_MMC_ProcLmmTauResultInd_PlmnSelection(pstLmmTauIndMsg);

    /* 已经Disable L并且注册成功,需要将当前网络保存在状态机上下文中,用于后续
       GU搜索失败重新回该网络提供PS业务*/
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS == NAS_MML_GetLteCapabilityStatus())
      && (MMC_LMM_TAU_RSLT_SUCCESS == pstLmmTauIndMsg->ulTauRst))
    {
        /* 保存当前网络在状态机上下文中 */
        NAS_MMC_SetCsPsMode1ReCampLtePlmn_PlmnSelection(NAS_MML_GetCurrCampPlmnId());
    }

    enCurrentFsmId     = NAS_MMC_GetCurrFsmId();
    if (NAS_MMC_FSM_PLMN_SELECTION != enCurrentFsmId)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }
    ulCurrentEventType = NAS_MMC_GetCurrFsmEventType();
    if (VOS_TRUE == NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enCurrentFsmId,ulCurrentEventType))
    {
        enCsRegCause = NAS_MMC_GetCsRegCause_PlmnSelection();
        enPsRegCause = NAS_MMC_GetPsRegCause_PlmnSelection();

        if (VOS_TRUE == NAS_MMC_ProcUserSearchRegRslt_PlmnSelection(enCsRegCause,enPsRegCause))
        {
            /*更新入口消息为普通的搜网请求，后续有新的用户请求时，可以打断该状态机*/
            NAS_MMC_SaveCommonPlmnSrchEntryMsg_PlmnSelection();
        }
    }

    if (NAS_MMC_WAIT_REG_RESULT_IND_NULL != NAS_MMC_GetWaitRegRsltFlag_PlmnSelection())
    {
        return VOS_TRUE;
    }

    /* 如果当前需要退出状态机 */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        /* 回复状态机退出成功 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* 停止等待eps注册结果消息的定时器  */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    NAS_MMC_PerformAdditionalActionRegFinished_PlmnSelection();

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmMmcDetachInd_PlmnSelection_WaitEpsRegRsltInd
 功能描述  : 在等待EPS注册结果的时候网侧detach的的处理
 输入参数  : ulEventType:消息类型
             pstMsg: ID_LMM_MMC_DETACH_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年06月19日
    作    者   : s46746
    修改内容   : 新生成函数
  2.日    期   : 2013年1月11日
    作    者   : w00176964
    修改内容   : DTS2013010706662:调整发送EPLMN逻辑调用位置
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmMmcDetachInd_PlmnSelection_WaitEpsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_DETACH_IND_STRU                                *pstDetachMsg = VOS_NULL_PTR;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsAdditionalAction;

    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));
    pstDetachMsg        = (LMM_MMC_DETACH_IND_STRU*)pstMsg;

    /* 处理DETACH消息，返回下一步动作 */
    NAS_MMC_ProcLmmDetachInd(pstDetachMsg, &enCsAdditionalAction, &enPsAdditionalAction);

    /*更新EPS的下一步的动作类型*/
    if (NAS_MMC_ADDITIONAL_ACTION_BUTT != enPsAdditionalAction)
    {
        NAS_MMC_SetPsRegAdditionalAction_PlmnSelection(enPsAdditionalAction);
    }

    /*更新CS的下一步的动作类型*/
    if (NAS_MMC_ADDITIONAL_ACTION_BUTT != enCsAdditionalAction)
    {
        NAS_MMC_SetCsRegAdditionalAction_PlmnSelection(enCsAdditionalAction);
    }

    if (VOS_TRUE == NAS_MMC_IsNeedSndEplmn_PlmnSelection())
    {
        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildSndLmmEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndLmmEquPlmnReq(&stSndEquPlmnInfo);
        NAS_MMC_SndOmEquPlmn();
    }

    /* 如果当前需要退出状态机 */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        /* 回复状态机退出成功 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* 停止等待eps注册结果消息的定时器  */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    NAS_MMC_PerformAdditionalActionRegFinished_PlmnSelection();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmMmcServiceRsltInd_PlmnSelection_WaitEpsRegRsltInd
 功能描述  : 在等待LTE注册结果时候收到ID_LMM_MMC_SERVICE_RESULT_IND消息的处理,
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息未完成
             VOS_TRUE:处理消息完成
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月26日
    作    者   : s46746
    修改内容   : 新生成函数
  2.日    期   : 2014年10月16日
    作    者   : b00269685
    修改内容   : 若存在CSFB标志且需要搜网，修改入口消息为CSFB触发的搜网

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmMmcServiceRsltInd_PlmnSelection_WaitEpsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_SERVICE_RESULT_IND_STRU                        *pstSerRsltMsg       = VOS_NULL_PTR;
    /* Added by b00269685 for 自主FR优化, 2014-10-16, begin */
    NAS_MMC_INTER_PLMN_SEARCH_REQ_STRU                     *pstInterPlmnSrchMsg = VOS_NULL_PTR;
    /* Added by b00269685 for 自主FR优化, 2014-10-16, end */
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;

    pstSerRsltMsg     = (LMM_MMC_SERVICE_RESULT_IND_STRU*)pstMsg;

    /* 根据LMM的service result结果返回下一步处理动作 */
    enAdditionalAction = NAS_MMC_ProcLmmServiceRsltInd(pstSerRsltMsg);

    /* AdditionalAction有效，更新EPS的下一步的动作类型 */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enAdditionalAction )
    {
        NAS_MMC_SetPsRegAdditionalAction_PlmnSelection(enAdditionalAction);
    }

    /* 如果当前需要退出状态机 */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        /* 回复状态机退出成功 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* 停止等待eps注册结果消息的定时器  */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* Added by b00269685 for 自主FR优化, 2014-10-16, begin */
    if ((VOS_TRUE                                 == NAS_MML_IsCsfbServiceStatusExist())
     && (NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION == enAdditionalAction))
    {
        pstInterPlmnSrchMsg = (NAS_MMC_INTER_PLMN_SEARCH_REQ_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC, sizeof(NAS_MMC_INTER_PLMN_SEARCH_REQ_STRU));
        if (VOS_NULL_PTR != pstInterPlmnSrchMsg)
        {
            /* 修改入口消息为CSFB触发的搜网 */
            NAS_MMC_BulidInterPlmnSearchReqMsg(NAS_MMC_PLMN_SEARCH_SCENE_CSFB_SERVIEC_REJ, VOS_NULL_PTR, 0, pstInterPlmnSrchMsg);
            NAS_MMC_SaveCurEntryMsg(NAS_BuildEventType(WUEPS_PID_MMC, MMCMMC_INTER_PLMN_SEARCH_REQ),
                                    (struct MsgCB*)pstInterPlmnSrchMsg);
            PS_MEM_FREE(WUEPS_PID_MMC, pstInterPlmnSrchMsg);
        }
        else
        {
            /* 异常打印 */
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmMmcServiceRsltInd_PlmnSelection_WaitEpsRegRsltInd Alloc mem fail");
        }
    }
    /* Added by b00269685 for 自主FR优化, 2014-10-16, end */

    NAS_MMC_PerformAdditionalActionRegFinished_PlmnSelection();

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmSuspendInd_PlmnSelection_WaitEpsRegRsltInd
 功能描述  : LMM上报的SUSPEND_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:返回处理成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月20日
    作    者   : W00167002
    修改内容   : 新生成函数
  2.日    期   : 2011年7月14日
    作    者   : l00130025
    修改内容   : PhaseII修改
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmSuspendInd_PlmnSelection_WaitEpsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    LMM_MMC_SUSPEND_IND_STRU           *pstLSuspendMsg = VOS_NULL_PTR;
    MMC_SUSPEND_CAUSE_ENUM_UINT8        enSuspendCause;

    pstLSuspendMsg = (LMM_MMC_SUSPEND_IND_STRU*)pstMsg;

    /* L模下，挂起原因定义与GU下不同，转换一下挂起原因定义 */
    NAS_MMC_ConvertLmmSysChngTypeToMmcType(pstLSuspendMsg->ulSysChngType, &enSuspendCause);

    /* 如果为OOS或者参数不正确, 则不允许进行异系统重选 */
    if ((MMC_SUSPEND_CAUSE_PLMNSEARCH == enSuspendCause)
     || (MMC_SUSPEND_CAUSE_BUTT <= enSuspendCause))
    {
        NAS_MMC_SndLmmSuspendRsp(MMC_LMM_FAIL);
    }
    else
    {
        /* 根据SUSPEND消息中的不同类型起相应的状态机 */
        NAS_MMC_LoadInterSysFsm_PlmnSelection(enSuspendCause);
    }


    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcSuspendRsltAreaLost_PlmnSelection_WaitEpsRegRsltInd
 功能描述  : 挂起状态机结果处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月8日
    作    者   : b00269685
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_ProcSuspendRsltAreaLost_PlmnSelection_WaitEpsRegRsltInd()
{
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stDestPlmn;
    VOS_UINT32                                              ulResult;

    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    /* 获取高优先级网络列表 */
    pstPlmnSelectionListInfo = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();

    /* 更新当前网络的搜索状态为已注册过，在此轮搜网中，不会再搜此网络 */
    NAS_MMC_UpdatePlmnNetStatusInPlmnSelectionList(NAS_MMC_GetCurrSearchingPlmn_PlmnSelection(),
                                            NAS_MMC_NET_STATUS_SEARCHED_REGISTERED,
                                            pstPlmnSelectionListInfo);

    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);

    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());

    /* 停止等待Eps注册结果消息的定时器  */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

    /* 如果当前需要退出状态机 */
    if (VOS_TRUE  == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        /* 回复状态机退出成功 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* 清空等待注册结果标志 */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnSelection();

    /* 如果是NCELL搜网，不需要再搜索其他网络了，退出状态机 */
    if (NAS_MMC_PLMN_SEARCH_SCENE_REG_NCELL == NAS_MMC_GetPlmnSearchScene_PlmnSelection())
    {
        /* 向上层状态机指示选网失败 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* 获取下一个要搜索的网络,若获取失败，则给上层状态机上报搜网失败，退出
      若获取成功，则判断下一个要搜索的网络是否与当前驻留网络相同，
      若相同则在当前模式发起搜网，否则挂起当前网络 */
    ulResult = NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn);

    /*  获取下个网络失败，则进行出服务区处理 */
    if (VOS_TRUE != ulResult)
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();
        return;

    }

    /* 向MM、GMM发送搜网指示 */
    NAS_MMC_SndGmmPlmnSchInit();
    NAS_MMC_SndMmPlmnSchInit();

    NAS_MMC_SndMsccCampOnInd(VOS_FALSE);

    NAS_MMC_UpdateRegStateSpecPlmnSearch();

    /* 下一个要搜索的网络是否与当前驻留网络不同,需要挂起当前模式，切换到等待挂起状态，启动保护定时器 */
    if (stDestPlmn.enRat != NAS_MML_GetCurrNetRatType())
    {
        NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_GetCurrNetRatType());
    }
    else
    {
        /* 向接入层或LMM发送搜网请求，根据不同的搜网模式，迁移到不同的L2状态，并启动保护定时器 */
        NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcMmcSuspendRslt_PlmnSelection_WaitEpsRegRsltInd
 功能描述  : 挂起状态机结果处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月04日
    作    者   : sunxibo / 46746
    修改内容   : 新生成函数
  2.日    期   : 2013年4月9日
    作    者   : y00176023
    修改内容   : DSDS GUNAS II项目:收到NO RF 退状态机，发送失败迁移到ooc
  3.日    期   : 2014年1月27日
    作    者   : s00246516
    修改内容   : L-C互操作项目:增加异系统到HRPD的处理
  4.日    期   : 2014年6月30日
    作    者   : b00269685
    修改内容   : DSDS GUNAS III项目:修改函数名称
  5.日    期   : 2014年6月30日
    作    者   : b00269685
    修改内容   : DTS2015051900500修改
  6.日    期   : 2014年08月25日
    作    者   : m00312079
    修改内容   : DTS2015082004682:L2C成功后退出搜网状态机
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmcMmcSuspendRslt_PlmnSelection_WaitEpsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;

    /* Added by s00246516 for L-C互操作项目, 2014-01-27, Begin */
    NAS_MMCMMC_SUSPEND_RSLT_STRU       *pstSuspendRslt = VOS_NULL_PTR;
     /* Added by s00246516 for L-C互操作项目, 2014-01-27, End */

     /* 迁移到不同的接入技术时，需要迁移到不同的处理注册结果状态 */

    enRatType = NAS_MML_GetCurrNetRatType();

    pstSuspendRslt  = (NAS_MMCMMC_SUSPEND_RSLT_STRU*)pstMsg;

    if (VOS_FALSE == NAS_MML_GetRfAvailFlg())
    {
        /* 停止当前等待EPS注册结果的定时器 */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

        /* 状态机退出结果为失败，迁移到OOC */
        NAS_MMC_ProcNoRf_PlmnSelection(enRatType);

        return VOS_TRUE;
    }

    if ((NAS_MML_NET_RAT_TYPE_WCDMA == enRatType)
     || (NAS_MML_NET_RAT_TYPE_GSM == enRatType))
    {
        /* 停止当前等待EPS注册结果的定时器 */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

        /* 更新当前等待CSPS的注册结果 */
        NAS_MMC_ClearAllWaitRegRsltFlag_PlmnSelection();
        NAS_MMC_SetWaitRegRsltFlag_PlmnSelection(NAS_MMC_WAIT_REG_RESULT_IND_CS);
        NAS_MMC_SetWaitRegRsltFlag_PlmnSelection(NAS_MMC_WAIT_REG_RESULT_IND_PS);

        /* 更新CSPS的AdditionalAction */
        NAS_MMC_SetCsRegAdditionalAction_PlmnSelection(NAS_MMC_ADDITIONAL_ACTION_BUTT);
        NAS_MMC_SetPsRegAdditionalAction_PlmnSelection(NAS_MMC_ADDITIONAL_ACTION_BUTT);

        /* 更新CSPS的RegCause */
        NAS_MMC_SetCsRegCause_PlmnSelection(NAS_MML_REG_FAIL_CAUSE_BUTT);
        NAS_MMC_SetPsRegCause_PlmnSelection(NAS_MML_REG_FAIL_CAUSE_BUTT);


        /* 收到系统消息后迁移到等待CS+PS域的注册结果并启动定时器 */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_CSPS_REG_IND);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND, TI_NAS_MMC_WAIT_CSPS_REG_IND_LEN);


        return VOS_TRUE;
    }


    if (NAS_MML_NET_RAT_TYPE_LTE == enRatType)
    {
        if ((NAS_MMC_SUSPEND_FAIL                 == pstSuspendRslt->enRslt)
         && (NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST == pstSuspendRslt->enFailCause))
        {
            NAS_MMC_ProcSuspendRsltAreaLost_PlmnSelection_WaitEpsRegRsltInd();

            return VOS_TRUE;
        }
    }

    /* Added by s00246516 for L-C互操作项目, 2014-01-27, Begin */
#if ((FEATURE_ON == FEATURE_CL_INTERWORK) || (FEATURE_ON == FEATURE_UE_MODE_CDMA))

    /* 重选到HRPD后,退出选网状态机 */
    if ((NAS_MML_NET_RAT_TYPE_BUTT == enRatType)
     && (NAS_MMC_SUSPEND_SUCCESS == pstSuspendRslt->enRslt))
    {
        /* 停止当前等待EPS注册结果的定时器 */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

        /* 向上层状态机发送搜索结果 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_INTER_SYS_HRPD);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }
#endif
    /* Added by s00246516 for L-C互操作项目, 2014-01-27, End */

    NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMmcMmcSuspendRslt_PlmnSelection_WaitEpsRegRsltInd:ENTERED");
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitEpsRegRsltIndExpired_PlmnSelection_WaitEpsRegRsltInd
 功能描述  : 等待EPS的REG CNF定时器超时
 输入参数  : ulEventType:消息类型
             pstMsg:TI_NAS_MMC_WAIT_EPS_REG_IND_TIMER超时的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:返回处理成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月20日
    作    者   : W00167002
    修改内容   : 新生成函数
  2.日    期   : 2011年12月15日
    作    者   : W00166186
    修改内容   : dts2011111502641,L下PLMN加入禁止TA后不再搜网
  3.日    期   : 2011年12月14日
    作    者   : w00176964
    修改内容   : V7R1 phaseIV 调整:驻留标记通过新的搜网控制上下文代替
  4.日    期   : 2012年5月24日
    作    者   : w00166186
    修改内容   : DTS2012052203028,L下出服务区重入服务区，尝试注册5次后，等待注册结果定时器超时后复位
  5.日    期   : 2012年12月11日
    作    者   : l00167671
    修改内容   : DTS2012121802573, TQE清理
  6.日    期   : 2014年5月5日
    作    者   : w00242748
    修改内容   : DTS2014043000311:注册状态服务状态不一致，将MMC中报服务状态的场景，都加
                 注册状态的上报。
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiWaitEpsRegRsltIndExpired_PlmnSelection_WaitEpsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_FSM_ID_ENUM_UINT32              enCurrentFsmId;
    VOS_UINT32                              ulCurrentEventType;

    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8    enAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8    enCsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8    enPsAdditionalAction;

    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitEpsRegRsltIndExpired_PlmnSelection_WaitEpsRegRsltInd: Timer Expired");

    /* 更新服务状态 */

	/* 通知TAF当前的服务状态 */

    enCurrentFsmId     = NAS_MMC_GetCurrFsmId();

    if (NAS_MMC_FSM_PLMN_SELECTION != enCurrentFsmId)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }

    ulCurrentEventType = NAS_MMC_GetCurrFsmEventType();
    if (VOS_TRUE == NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enCurrentFsmId,ulCurrentEventType))
    {
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, begin*/
        NAS_MMC_SndMsccUserSpecPlmnSearchCnf(NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_FAIL);
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, end*/

        /*更新入口消息为普通的搜网请求，后续有新的用户请求时，可以打断该状态机*/
        NAS_MMC_SaveCommonPlmnSrchEntryMsg_PlmnSelection();

        /* 向LMM发送用户搜网结束通知 */
        if ( VOS_TRUE == NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_LTE))
        {
            NAS_MMC_SndLmmUserSpecPlmnSearchEndNotify();
        }
    }

    /* 如果当前需要退出状态机 */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        /* 回复状态机退出成功 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    enCsAdditionalAction = NAS_MMC_GetCsRegAdditionalAction_PlmnSelection();
    enPsAdditionalAction = NAS_MMC_GetPsRegAdditionalAction_PlmnSelection();

    /* 等待CS PS的注册结果时，有可能一个域发起注册后进行了呼叫以及紧急呼叫等业务
      (比如G下进行CS域进行呼叫，PS域无法发起注册),导致MMC一致等不到另外一个域的
      注册结果，此时MMC直接通过additional触发搜网不合理，MMC此时根据当前收到的注
      册结果更新的additional值来决定是否成功退出搜网状态机或者失败退出搜网状态机，
      由L1状态机根据搜网状态机的退出结果决定是否启动周期性选网定时器还是继续等待
      业务结束以及CSPS的注册结果 */

    enAdditionalAction = NAS_MMC_GetPrioAddtionalAction(enCsAdditionalAction, enPsAdditionalAction);

    /* 附加操作为驻留当前网络 */
    if ((NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON == enAdditionalAction)
     || (NAS_MMC_ADDITIONAL_ACTION_CELL_SELECTION == enAdditionalAction)
     || (NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON == enAdditionalAction)
     || (NAS_MMC_ADDITIONAL_ACTION_ACCESS_BARRED == enAdditionalAction))
    {
        /* 回复状态机退出成功 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_SUCC);
    }
    else
    {
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);
    }

    /* 直接退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;

}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmAreaLostInd_PlmnSelection_WaitEpsRegRsltInd
 功能描述  : 在等待EPS上报注册结果的时候收到丢网指示，无链接，直接构造搜网消息
 输入参数  : ulEventType:消息类型
             pstMsg:ID_LMM_MMC_AREA_LOST_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:返回处理成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月20日
    作    者   : W00167002
    修改内容   : 新生成函数

  2.日    期   : 2011年11月9日
    作    者   : w00167002
    修改内容   : 在注册过程中收到丢网指示，则更新当前的网络的注册状态为
                  NAS_MMC_NET_STATUS_SEARCHED_REGISTERED,否则查找下一个网络依然为
                  已经丢网的网络。
  3.日    期   : 2011年12月15日
    作    者   : W00166186
    修改内容   : dts2011111502641,L下PLMN加入禁止TA后不再搜网
  4.日    期   : 2011年12月14日
    作    者   : w00176964
    修改内容   : V7R1 phaseIV 调整:驻留标记通过新的搜网控制上下文代替
  5.日    期   : 2012年06月13日
    作    者   : s46746
    修改内容   : For CS/PS mode 1，出服务区后更新驻留标志,保证退出状态机时会进行限制驻留
  6.日    期   : 2012年7月16日
    作    者   : s00217060
    修改内容   : for DTS2012071604442
                 调整:丢网,并且获取下一个网络失败需要重新驻留LTE
  7.日    期   : 2012年09月27日
    作    者   : z00161729
    修改内容   : DTS2012090303562:搜网状态机等L注册结果收到丢网消息获取下一个网络失败退状态机后又发起非法随机网络搜网
  8.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  9.日    期   : 2013年8月27日
    作    者   : l00208543
    修改内容   : Coverity
 10.日    期   : 2014年1月28日
    作    者   : s00246516
    修改内容   : L-C互操作项目:增加获取和注册请求的处理
 11.日    期   : 2014年6月12日
    作    者   : w00167002
    修改内容   : DSDS III:L下NO RF丢网后的处理
 12.日    期   : 2015年1月8日
    作    者   : w00167002
    修改内容   : DTS2015010601540:在CS注册成功，PS注册失败时候，在继续等待注册过
                 程中，副卡抢占资源导致NO RF丢网。在等待资源可用后重新触发搜索当前
                 网络。
 13.日    期   : 2015年10月22日
    作    者   : s00217060
    修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0:RRMM_AREA_LOST_IND消息接口变更
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmAreaLostInd_PlmnSelection_WaitEpsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_PLMN_WITH_RAT_STRU          stDestPlmn;
    VOS_UINT32                          ulResult;

    LMM_MMC_AREA_LOST_IND_STRU          *pstLmmAreaLostMsg  = VOS_NULL_PTR;

    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo           = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stCurPlmn;

    /* 解决版本Coverity问题 */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    pstLmmAreaLostMsg   =  (LMM_MMC_AREA_LOST_IND_STRU *)pstMsg;

    /* 获取当前驻留的网络信息 */
    pstCurCampInfo     = NAS_MML_GetCurrCampPlmnInfo();
    stCurPlmn.stPlmnId = pstCurCampInfo->stLai.stPlmnId;
    stCurPlmn.enRat    = pstCurCampInfo->enNetRatType;

    /* 获取高优先级网络列表 */
    pstPlmnSelectionListInfo = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();



    /* 停止等待Eps注册结果消息的定时器  */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

    /* 清除驻留状态 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

    /* 当前信号更新 */
    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());

    if (MMC_LMM_AREA_LOST_REASON_NO_RF == pstLmmAreaLostMsg->enAreaLostReason)
    {
        /* 更新当前网络状态为EXIT,资源恢复后再搜 */
        NAS_MMC_UpdatePlmnNetStatusInPlmnSelectionList(&stCurPlmn,
                                        NAS_MMC_NET_STATUS_SEARCHED_EXIST,
                                        pstPlmnSelectionListInfo);

        /* 回复状态机失败 */
        NAS_MMC_ProcNoRfAreaLost_PlmnSelection(NAS_MML_GetCurrNetRatType());

        return VOS_TRUE;
    }

    /* 在等待注册结果时候，如果因NO RF而丢网，则不更新当前为REGISTER状态，等待资源
       可用时候，可以继续搜网并在此网络上进行注册 */
    /* 更新当前网络的搜索状态为已注册过，在此轮搜网中，不会再搜此网络 */
    NAS_MMC_UpdatePlmnNetStatusInPlmnSelectionList(&stCurPlmn,
                                        NAS_MMC_NET_STATUS_SEARCHED_REGISTERED,
                                        pstPlmnSelectionListInfo);

    /* 更新是否进行过history搜 */
    if ((VOS_TRUE == pstLmmAreaLostMsg->stSearchedType.ucHistorySearchedFlg)
     || (VOS_TRUE == pstLmmAreaLostMsg->stSearchedType.ucPrefBandSearchedFlg)
     || (VOS_TRUE == pstLmmAreaLostMsg->stSearchedType.ucSpecSearchedFlg))
    {
        NAS_MMC_SetHistorySearchedFlag_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE, VOS_TRUE);
    }

    /* 如果当前需要退出状态机 */
    if (VOS_TRUE  == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        /* 回复状态机退出成功 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 清空等待注册结果标志 */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnSelection();

    /* Added by s00246516 for L-C互操作项目, 2014-01-28, Begin */
    /* 如果是NCELL搜网，不需要再搜索其他网络了，退出状态机 */
    if (NAS_MMC_PLMN_SEARCH_SCENE_REG_NCELL == NAS_MMC_GetPlmnSearchScene_PlmnSelection())
    {
        /* 向上层状态机指示选网失败 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }
    /* Added by s00246516 for L-C互操作项目, 2014-01-28, End */

    /* 获取下一个要搜索的网络,若获取失败，则给上层状态机上报搜网失败，退出
      若获取成功，则判断下一个要搜索的网络是否与当前驻留网络相同，
      若相同则在当前模式发起搜网，否则挂起当前网络 */
    ulResult = NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn);

    /*  获取下个网络失败，则进行出服务区处理 */
    if (VOS_TRUE != ulResult)
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();
        return VOS_TRUE;
    }

    /* 向MM、GMM发送搜网指示 */
    NAS_MMC_SndGmmPlmnSchInit();
    NAS_MMC_SndMmPlmnSchInit();

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, end */

    NAS_MMC_UpdateRegStateSpecPlmnSearch();

    /* 下一个要搜索的网络是否与当前驻留网络不同,需要挂起当前模式，切换到等待挂起状态，启动保护定时器 */
    if (stDestPlmn.enRat != NAS_MML_GetCurrNetRatType())
    {
        NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_GetCurrNetRatType());
    }
    else
    {
        /* 向接入层或LMM发送搜网请求，根据不同的搜网模式，迁移到不同的L2状态，并启动保护定时器 */
        NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
    }

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLSysInfoInd_PlmnSelection_WaitEpsRegRsltInd
 功能描述  : MMC处理LMM上报的系统消息
 输入参数  : ulEventType:消息类型
             pstMsg:LMM上报的系统消息地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:返回处理成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月20日
    作    者   : W00167002
    修改内容   : 新生成函数
  2.日    期   : 2011年10月6日
    作    者   : w00167002
    修改内容   : PhaseII修改:删除更改当前的网络的注册状态为REGISTERED，
                 统一等注册结果后，才更改为REGISTERED
  3.日    期   : 2012年4月18日
    作    者   : l00130025
    修改内容   : DTS2012040200480,单独维护EPS注册状态,供查询和上报使用
  4.日    期   : 2012年4月28日
    作    者   : W00166186
    修改内容   : DTS2012042602593,MM没有保存当前驻留的PLMN，导致后续判断出错
  5.日    期   : 2012年11月29日
    作    者   : w00176964
    修改内容   : DTS2012042804167:通知CBA模块当前接入模式为LTE
  6.日    期   : 2012年12月20日
    作    者   : w00176964
    修改内容   : DTS2012121906946:收到L的系统消息转发给LMM
  7.日    期   : 2013年1月19日
    作    者   : t00212959
    修改内容   : DTS2012122900189:EPS注册状态完全由L上报
  8.日    期   : 2015年02月11日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseII 项目修改
                 方案优化后，LTE下的小区发生变化，LMM会通过系统消息通知MMC
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLSysInfoInd_PlmnSelection_WaitEpsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    /* 保留老的驻留网络信息 */
    pstCurCampInfo  = NAS_MML_GetCurrCampPlmnInfo();
    PS_MEM_CPY(&stOldCampInfo, pstCurCampInfo, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

    /* 根据系统消息，更新MML的全部变量 */
    NAS_MMC_UpdateNetworkInfo_LmmSysInfo(pstMsg);



    /* 状态更新为当前已经驻留 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

    /* CBS上报*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_LTE);

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, end */
    /*方案优化后，LTE下的小区发生变化，LMM会通过系统消息通知MMC*/
    if (VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
    {
        NAS_MMC_SndMsccSysInfo();

    }

    /* 转发GMM系统消息,供rabm使用 */
    NAS_MMC_SndGmmLteSysinfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);
    NAS_MMC_SndMmLteSysinfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);

    NAS_MMC_SndLmmLteSysInfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTafPlmnSpecialReq_PlmnSelection_WaitEpsRegRsltInd
 功能描述  : MMC处理MMA请求的指定搜网消息
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月04日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2011年12月31日
   作    者   : w00166186
   修改内容   : DTS2011082902017,ON PLMN下注册被拒,搜网状态机重复搜索该网络
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTafPlmnSpecialReq_PlmnSelection_WaitEpsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, begin*/
    MSCC_MMC_PLMN_SPECIAL_REQ_STRU                          *pstUserSelReqMsg  = VOS_NULL_PTR;
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, end*/

    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSrchList   = VOS_NULL_PTR;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsRegCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enPsRegCause;

    /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, begin*/
    pstUserSelReqMsg    = (MSCC_MMC_PLMN_SPECIAL_REQ_STRU*)pstMsg;
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, end*/

    /* 保存用户指定搜网信息，更新当前的搜网类型为手动模式 */
    NAS_MMC_UpdateUserSpecPlmnSearchInfo_PlmnSelection((NAS_MML_PLMN_ID_STRU*)(&pstUserSelReqMsg->stPlmnId),
                                                        pstUserSelReqMsg->enAccessMode);

    /* 获取选网列表 */
    pstPlmnSrchList = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();

    /* 根据用户指定搜网场景重新初始化选网列表 */
    NAS_MMC_InitPlmnSelectionList(NAS_MMC_PLMN_SEARCH_SCENE_USER_SPEC_PLMN_SEARCH,
                                  VOS_NULL_PTR,
                                  pstPlmnSrchList);

    /* 将用户指定接入技术的网络(也是当前网络)更新为已搜索注册避免重复注册 */
    NAS_MMC_UpdatePlmnNetStatusInPlmnSelectionList(NAS_MMC_GetUserSpecPlmnId(),
                                                   NAS_MMC_NET_STATUS_SEARCHED_REGISTERED,
                                                   pstPlmnSrchList);

    enCsRegCause = NAS_MMC_GetCsRegCause_PlmnSelection();
    enPsRegCause = NAS_MMC_GetPsRegCause_PlmnSelection();

    if (VOS_TRUE == NAS_MMC_ProcUserSearchRegRslt_PlmnSelection(enCsRegCause, enPsRegCause))
    {
        return VOS_TRUE;
    }

    /* 保存入口消息 */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTafSysCfgReq_PlmnSelection_WaitEpsRegRsltInd
 功能描述  : MMC处理MSCC请求的SYSCFG设置消息
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月04日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTafSysCfgReq_PlmnSelection_WaitEpsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 直接调起syscfg层二状态机 */
    NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_SYSCFG);
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcSyscfgRsltCnf_PlmnSelection_WaitEpsRegRsltInd
 功能描述  : 处理SYSCFG状态机返回的结果
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月20日
   作    者   : L00171473
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmcSyscfgRsltCnf_PlmnSelection_WaitEpsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    return VOS_TRUE;
}

/* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-7, begin */

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMsccImsVoiceCapInd_PlmnSelection_WaitEpsRegRsltInd
 功能描述  : 处理MSCC的IMS VOICE是否可用消息
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
             VOS_FALSE:处理未完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年2月7日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMsccImsVoiceCapInd_PlmnSelection_WaitEpsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMC_IMS_VOICE_CAP_NOTIFY_STRU *pstImsVoiceNtf = VOS_NULL_PTR;
    VOS_UINT8                           ucWaitRegRsltFlag;

    ucWaitRegRsltFlag   = NAS_MMC_GetWaitRegRsltFlag_PlmnSelection();
    pstImsVoiceNtf      = (MSCC_MMC_IMS_VOICE_CAP_NOTIFY_STRU *)pstMsg;
    /* 如果在等待PS的注册结果则继续等待PS注册结果 */
    if (NAS_MMC_WAIT_REG_RESULT_IND_PS == (ucWaitRegRsltFlag & NAS_MMC_WAIT_REG_RESULT_IND_PS))
    {
        return VOS_TRUE;
    }

    NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnSelection(NAS_MMC_WAIT_REG_RESULT_IND_IMS);

    /* IMS不可用时判断是否需要disable LTE */
    if (VOS_FALSE  == pstImsVoiceNtf->ucAvail)
    {
        if (VOS_TRUE == NAS_MMC_IsNeedDisableLte_ImsVoiceNotAvail())
        {
            NAS_MMC_SetCsRegAdditionalAction_PlmnSelection(NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION);

            NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS);

            NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE);

            /* 已经Disable L并且注册成功,需要将当前网络保存在状态机上下文中,用于后续
               GU搜索失败重新回该网络提供PS业务*/
            NAS_MMC_SetCsPsMode1ReCampLtePlmn_PlmnSelection(NAS_MML_GetCurrCampPlmnId());
        }
    }

    /* 如果当前需要退出状态机 */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        if (VOS_TRUE == NAS_MMC_IsDisableLteNeedLocalReleaseEpsConn())
        {
            NAS_MMC_SndLmmRelReq();

            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_CONN_REL_IND);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND, TI_NAS_MMC_WAIT_EPS_CONN_REL_IND_LEN);

            return VOS_TRUE;
        }

        /* 回复状态机退出成功 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* 停止等待eps注册结果消息的定时器  */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    NAS_MMC_PerformAdditionalActionRegFinished_PlmnSelection();

    return VOS_TRUE;
}

/* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-7, end */


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnSrch_WaitEpsConnRelInd
 功能描述  : 等待L链接释放的过程中收到退出状态机的请求
 输入参数  : ulEventType:消息类型
             pstMsg: 消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年4月26日
   作    者   : W00167002
   修改内容   : 新生成函数

 2.日    期   : 2011年11月29日
   作    者   : w00167002
   修改内容   : DTS2011112301233:增加打断事件ID，状态机可以知道是什么事件
                打断自己的。
                修改原因:用户下发关机命令后，当前可能在等注册结果或者在等连接
                释放，可能需要比较久的时间才能处理关机命令，通过增加打断事件，
                如归当前在等注册结果或者等链接释放状态，若收到关机命令，则直接
                退出当前状态机，处理用户的关机命令。

 3.日    期   : 2011年12月14日
   作    者   : w00176964
   修改内容   : V7R1 phaseIV 调整:驻留标记通过新的搜网控制上下文代替

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ABORT_FSM_STRU             *pstAbortMsg = VOS_NULL_PTR;

    pstAbortMsg = (NAS_MMC_ABORT_FSM_STRU*)pstMsg;

    /* 若打断类型是用户请求的关机，则直接退出等链接释放结果状态机 */
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, begin*/
    if (NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_OFF_REQ) == pstAbortMsg->ulEventType)
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, end*/
    {
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND);

        /* 回复状态机退出成功 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 设置Abort标志, 等链接释放后进行quit */
    NAS_MMC_SetAbortFlag_PlmnSelection(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcSyscfgRsltCnf_PlmnSelection_WaitEpsConnRelInd
 功能描述  : 处理SYSCFG状态机返回的结果
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月20日
   作    者   : L00171473
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmcSyscfgRsltCnf_PlmnSelection_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmMmcStatusInd_PlmnSelection_WaitEpsConnRelInd
 功能描述  : MMC收到LMM上报的Status Ind消息
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年4月21日
   作    者   : W00167002
   修改内容   : 新生成函数
 2.日    期   : 2011年7月12日
   作    者   : L00171473
   修改内容   : 修改调用函数 for V7R1 phase II
 3.日    期   : 2011年12月14日
   作    者   : w00176964
   修改内容   : V7R1 phaseIV 调整:驻留标记通过新的搜网控制上下文代替
 4.日    期   : 2014年2月8日
   作    者   : w00176964
   修改内容   : VOLTE_Phase3调整:主动连接释放时也需要根据addition值刷新选网列表

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmMmcStatusInd_PlmnSelection_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_STATUS_IND_STRU            *pstLmmStatusIndMsg = VOS_NULL_PTR;
    /* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-8, begin */
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enAdditionalAction;
    /* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-8, end */

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

    /* 是否需要 Abort状态机 */
    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection() )
    {
        /* 向上层状态机指示选网ABORT */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 如果信令连接不存在而且不是主动释放连接则进行附加操作 */
    if (VOS_FALSE == NAS_MMC_GetRelRequestFlag_PlmnSelection())
    {
        NAS_MMC_PerformAdditionalActionConnRel_PlmnSelection();
    }
    else
    {
        NAS_MMC_SetRelRequestFlag_PlmnSelection(VOS_FALSE);

        /* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-8, begin */
        /* 主动释放连接时,由于addition也可能导致搜网,前面收到注册结果未刷新选网列表,此处需要再刷新一次 */
        enAdditionalAction   = NAS_MMC_GetPrioAddtionalAction(NAS_MMC_GetCsRegAdditionalAction_PlmnSelection(),
                                                              NAS_MMC_GetPsRegAdditionalAction_PlmnSelection());

        NAS_MMC_RefreshPlmnSelectionListAfterRegFail_PlmnSelection(enAdditionalAction);
        /* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-8, end */

        NAS_MMC_SearchNextPlmn_PlmnSelection();
    }


    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitEpsConnRelIndExpired_PlmnSelection_WaitEpsConnRelInd
 功能描述  : 等待连接释放定时器超时的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年4月21日
   作    者   : W00167002
   修改内容   : 新生成函数
 2.日    期   : 2011年7月22日
   作    者   : L00171473
   修改内容   : PhaseII修改,PlmnSelection状态机调整
 3.日    期   : 2011年12月1日
   作    者   : w00176964
   修改内容   : GUNAS V7R1 PhaseIV 阶段调整
 4.日    期   : 2011年12月14日
   作    者   : w00176964
   修改内容   : V7R1 phaseIV 调整:驻留标记通过新的搜网控制上下文代替
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitEpsConnRelIndExpired_PlmnSelection_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitEpsConnRelIndExpired_PlmnSelection_WaitEpsConnRelInd ENTERED");


    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection() )
    {
        /* 回复状态机退出成功 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 如果信令连接不存在而且不是主动释放连接则进行附加操作 */
    if (VOS_FALSE == NAS_MMC_GetRelRequestFlag_PlmnSelection())
    {
        /* 发送主动释放请求到MM、GMM，重新启动等待连接释放定时器 */
        NAS_MMC_SetRelRequestFlag_PlmnSelection(VOS_TRUE);

        NAS_MMC_SndLmmRelReq();
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND, TI_NAS_MMC_WAIT_EPS_CONN_REL_IND_LEN);
    }
    else
    {
        NAS_MMC_SetRelRequestFlag_PlmnSelection(VOS_FALSE);

        NAS_MMC_SearchNextPlmn_PlmnSelection();
    }


    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLSysInfoInd_PlmnSelection_WaitEpsConnRelInd
 功能描述  : MMC处理LMM上报的系统消息
 输入参数  : ulEventType:消息类型
             pstMsg:LMM上报的系统消息地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年4月20日
   作    者   : W00167002
   修改内容   : 新生成函数
 2.日    期   : 2011年7月26日
   作    者   : L00171473
   修改内容   : PhaseII修改,PlmnSelection状态机调整
 3.日    期   : 2012年4月18日
   作    者   : l00130025
   修改内容   : DTS2012040200480,单独维护EPS注册状态,供查询和上报使用
 4.日    期   : 2012年4月28日
   作    者   : W00166186
   修改内容   : DTS2012042602593,MM没有保存当前驻留的PLMN，导致后续判断出错
 5.日    期   : 2012年11月29日
   作    者   : w00176964
   修改内容   : DTS2012042804167:通知CBA模块当前接入模式为LTE
 6.日    期   : 2012年12月20日
   作    者   : w00176964
   修改内容   : DTS2012121906946:收到L的系统消息转发给LMM
 7.日    期   : 2013年1月19日
   作    者   : t00212959
   修改内容   : DTS2012122900189:EPS注册状态完全由L上报
 8.日    期   : 2015年02月11日
   作    者   : l00305157
   修改内容   : Service_State_Optimize_PhaseII 项目修改
                 方案优化后，LTE下的小区发生变化，LMM会通过系统消息通知MMC
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLSysInfoInd_PlmnSelection_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU         stOldCampInfo;

    NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8                enSpecPlmnSearchState;

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

    /* 状态更新为当前已经驻留 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

    /* 如果是主动请求释放,由于需要立即进行搜网,系统消息不处理 */
    if (VOS_TRUE == NAS_MMC_GetRelRequestFlag_PlmnSelection())
    {
        return VOS_TRUE;
    }

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

    enSpecPlmnSearchState = NAS_MMC_GetSpecPlmnSearchState();

    /*方案优化后，LTE下的小区发生变化，LMM会通过系统消息通知MMC*/
    if ((VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
     || (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == enSpecPlmnSearchState))
    {
        NAS_MMC_SndMsccSysInfo();

    }

    /* 转发GMM系统消息,供rabm使用 */
    NAS_MMC_SndGmmLteSysinfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);
    NAS_MMC_SndMmLteSysinfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);

    NAS_MMC_SndLmmLteSysInfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTafSysCfgReq_PlmnSelection_WaitEpsConnRelInd
 功能描述  : MMC处理MSCC请求的SYSCFG设置消息
 输入参数  : ulEventType:消息类型
             pstMsg:SYSCFG设置消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月04日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTafSysCfgReq_PlmnSelection_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 直接调起syscfg层二状态机 */
    NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_SYSCFG);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmSuspendInd_PlmnSelection_WaitEpsConnRelInd
 功能描述  : LMM上报的SUSPEND_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:返回处理成功
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年4月20日
   作    者   : W00167002
   修改内容   : 新生成函数
 2.日    期   : 2011年7月12日
   作    者   : L00171473
   修改内容   : PhaseII修改,PlmnSelection状态机调整

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmSuspendInd_PlmnSelection_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    LMM_MMC_SUSPEND_IND_STRU           *pstLSuspendMsg = VOS_NULL_PTR;
    MMC_SUSPEND_CAUSE_ENUM_UINT8        enSuspendCause;
    VOS_UINT32                          ulRelRequestFlg;

    pstLSuspendMsg = (LMM_MMC_SUSPEND_IND_STRU*)pstMsg;

    ulRelRequestFlg = NAS_MMC_GetRelRequestFlag_PlmnSelection();

    /* L模下，挂起原因定义与GU下不同，转换一下挂起原因定义 */
    NAS_MMC_ConvertLmmSysChngTypeToMmcType(pstLSuspendMsg->ulSysChngType, &enSuspendCause);

    /* 如果是主动释放或者已经接收到Abort消息,则不允许进行异系统重选 */
    if ((VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
     || (VOS_TRUE == ulRelRequestFlg)
     || (MMC_SUSPEND_CAUSE_PLMNSEARCH == enSuspendCause)
     || (MMC_SUSPEND_CAUSE_BUTT <= enSuspendCause))
    {
        NAS_MMC_SndLmmSuspendRsp(MMC_LMM_FAIL);
    }
    else
    {
        /* 根据SUSPEND消息中的不同类型起相应的状态机 */
        NAS_MMC_LoadInterSysFsm_PlmnSelection(enSuspendCause);
    }


    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcSuspendRslt_PlmnSelection_WaitEpsConnRelInd
 功能描述  : 挂起状态机结果处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月04日
   作    者   : sunxibo / 46746
   修改内容   : 新生成函数
 2.日    期   : 2011年7月22日
   作    者   : L00171473
   修改内容   : PhaseII修改,PlmnSelection状态机调整
 3.日    期   : 2011年12月14日
   作    者   : w00176964
   修改内容   : V7R1 phaseIV 调整:驻留标记通过新的搜网控制上下文代替
 4.日    期   : 2013年4月4日
   作    者   : y00176023
   修改内容   : DSDS GUNAS II项目:收到NO RF 退状态机，发送失败，迁移到OOC
 5.日    期   : 2014年1月27日
   作    者   : s00246516
   修改内容   : L-C互操作项目:增加异系统到HRPD的处理
 6.日    期   : 2014年6月30日
   作    者   : b00269685
   修改内容   : DSDS GUNAS III项目:修改函数名称

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmcSuspendRslt_PlmnSelection_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;

    /* Added by s00246516 for L-C互操作项目, 2014-01-27, Begin */
#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    NAS_MMCMMC_SUSPEND_RSLT_STRU       *pstSuspendRslt = VOS_NULL_PTR;
#endif
    /* Added by s00246516 for L-C互操作项目, 2014-01-27, End */

    /* 迁移到不同的接入技术时，需要迁移到不同的处理注册结果状态 */
    enRatType = NAS_MML_GetCurrNetRatType();

    if (VOS_FALSE == NAS_MML_GetRfAvailFlg())
    {
        /* 停止当前等待eps连接释放定时器 */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND);

        /* 状态机退出结果为失败，迁移到OOC */
        NAS_MMC_ProcNoRf_PlmnSelection(enRatType);

        return VOS_TRUE;
    }

    if ((NAS_MML_NET_RAT_TYPE_WCDMA == enRatType)
     || (NAS_MML_NET_RAT_TYPE_GSM == enRatType))
    {
        /* 停止当前等待eps连接释放定时器 */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND);

        /* 更新当前等待CSPS的注册结果 */
        NAS_MMC_ClearAllWaitRegRsltFlag_PlmnSelection();
        NAS_MMC_SetWaitRegRsltFlag_PlmnSelection(NAS_MMC_WAIT_REG_RESULT_IND_CS);
        NAS_MMC_SetWaitRegRsltFlag_PlmnSelection(NAS_MMC_WAIT_REG_RESULT_IND_PS);

        /* 更新CSPS的AdditionalAction */
        NAS_MMC_SetCsRegAdditionalAction_PlmnSelection(NAS_MMC_ADDITIONAL_ACTION_BUTT);
        NAS_MMC_SetPsRegAdditionalAction_PlmnSelection(NAS_MMC_ADDITIONAL_ACTION_BUTT);

        /* 更新CSPS的RegCause */
        NAS_MMC_SetCsRegCause_PlmnSelection(NAS_MML_REG_FAIL_CAUSE_BUTT);
        NAS_MMC_SetPsRegCause_PlmnSelection(NAS_MML_REG_FAIL_CAUSE_BUTT);


        /* 收到系统消息后迁移到等待CS+PS域的注册结果并启动定时器 */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_CSPS_REG_IND);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND, TI_NAS_MMC_WAIT_CSPS_REG_IND_LEN);


        return VOS_TRUE;
    }

    /* Added by s00246516 for L-C互操作项目, 2014-01-27, Begin */
#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    pstSuspendRslt  = (NAS_MMCMMC_SUSPEND_RSLT_STRU*)pstMsg;

    /* 重选到HRPD后,退出选网状态机 */
    if ((NAS_MML_NET_RAT_TYPE_BUTT == enRatType)
     && (NAS_MMC_SUSPEND_SUCCESS == pstSuspendRslt->enRslt))
    {
        /* 停止当前等待eps连接释放定时器 */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND);

        /* 向上层状态机发送高优先级搜索失败，需要搜网 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_INTER_SYS_HRPD);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }
#endif
    /* Added by s00246516 for L-C互操作项目, 2014-01-27, End */

    /*  如果存在信令连接，则继续等待  */
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        return VOS_TRUE;
    }

    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);

    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection() )
    {
        /* 回复状态机退出成功 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 如果信令连接不存在可能发起搜网 */
    NAS_MMC_PerformAdditionalActionConnRel_PlmnSelection();


    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTafPlmnSpecialReq_PlmnSelection_WaitEpsConnRelInd
 功能描述  : 处理MSCC发送的用户指定搜请求,用户指定的PlmnId及RAT和当前驻留的PlmnId
             及RAT相同，才会进入该处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:返回处理成功
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月12日
   作    者   : lijun 00171473
   修改内容   : 新生成函数
 2.日    期   : 2011年12月31日
   作    者   : w00166186
   修改内容   : DTS2011082902017,ON PLMN下注册被拒,搜网状态机重复搜索该网络
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTafPlmnSpecialReq_PlmnSelection_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, begin*/
    MSCC_MMC_PLMN_SPECIAL_REQ_STRU                          *pstUserSelReqMsg  = VOS_NULL_PTR;
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, end*/

    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSrchList;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enPsCause;

    /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, begin*/
    pstUserSelReqMsg    = (MSCC_MMC_PLMN_SPECIAL_REQ_STRU*)pstMsg;
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, end*/

    /* 保存手动搜网信息 */
    NAS_MMC_UpdateUserSpecPlmnSearchInfo_PlmnSelection((NAS_MML_PLMN_ID_STRU*)(&pstUserSelReqMsg->stPlmnId),
                                                       pstUserSelReqMsg->enAccessMode);

    /* 获取选网列表 */
    pstPlmnSrchList = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();

    /* 根据用户指定搜网场景重新初始化选网列表 */
    NAS_MMC_InitPlmnSelectionList(NAS_MMC_PLMN_SEARCH_SCENE_USER_SPEC_PLMN_SEARCH,
                                  VOS_NULL_PTR,
                                  pstPlmnSrchList);

    /* 将用户指定接入技术的网络(也是当前网络)更新为已搜索注册避免重复注册 */
    NAS_MMC_UpdatePlmnNetStatusInPlmnSelectionList(NAS_MMC_GetUserSpecPlmnId(),
                                                   NAS_MMC_NET_STATUS_SEARCHED_REGISTERED,
                                                   pstPlmnSrchList);

    /* 由于用户指定的PlmnId及RAT和当前驻留的PlmnId及RAT相同，直接返回指定搜网结果 */
    enCsCause = NAS_MMC_GetCsRegCause_PlmnSelection();
    enPsCause = NAS_MMC_GetPsRegCause_PlmnSelection();

    if (VOS_TRUE == NAS_MMC_ProcUserSearchRegRslt_PlmnSelection(enCsCause, enPsCause))
    {
        return VOS_TRUE;
    }

    /* 保存入口消息 */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmMmcServiceRsltInd_PlmnSelection_WaitEpsConnRelInd
 功能描述  : 在等待LTE链接释放时候收到ID_LMM_MMC_SERVICE_RESULT_IND消息的处理,
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息未完成
             VOS_TRUE:处理消息完成
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月22日
    作    者   : t00212959
    修改内容   : 新生成函数
  2.日    期   : 2014年10月16日
    作    者   : b00269685
    修改内容   : 若存在CSFB标志且需要搜网，修改入口消息为CSFB触发的搜网

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmMmcServiceRsltInd_PlmnSelection_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_SERVICE_RESULT_IND_STRU                        *pstSerRsltMsg       = VOS_NULL_PTR;
    /* Added by b00269685 for 自主FR优化, 2014-10-16, begin */
    NAS_MMC_INTER_PLMN_SEARCH_REQ_STRU                     *pstInterPlmnSrchMsg = VOS_NULL_PTR;
    /* Added by b00269685 for 自主FR优化, 2014-10-16, end */
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;

    pstSerRsltMsg     = (LMM_MMC_SERVICE_RESULT_IND_STRU*)pstMsg;

    /* 根据LMM的service result结果返回下一步处理动作 */
    enAdditionalAction = NAS_MMC_ProcLmmServiceRsltInd(pstSerRsltMsg);

    /* AdditionalAction有效，更新EPS的下一步的动作类型 */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enAdditionalAction )
    {
        NAS_MMC_SetPsRegAdditionalAction_PlmnSelection(enAdditionalAction);
    }

    /* 如果当前需要退出状态机 */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        /* 回复状态机退出成功 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* 停止等待eps注册结果消息的定时器  */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* Added by b00269685 for 自主FR优化, 2014-10-16, begin */
    if ((VOS_TRUE                                 == NAS_MML_IsCsfbServiceStatusExist())
     && (NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION == enAdditionalAction))
    {
        pstInterPlmnSrchMsg = (NAS_MMC_INTER_PLMN_SEARCH_REQ_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC, sizeof(NAS_MMC_INTER_PLMN_SEARCH_REQ_STRU));
        if (VOS_NULL_PTR != pstInterPlmnSrchMsg)
        {
            /* 修改入口消息为CSFB触发的搜网 */
            NAS_MMC_BulidInterPlmnSearchReqMsg(NAS_MMC_PLMN_SEARCH_SCENE_CSFB_SERVIEC_REJ, VOS_NULL_PTR, 0, pstInterPlmnSrchMsg);
            NAS_MMC_SaveCurEntryMsg(NAS_BuildEventType(WUEPS_PID_MMC, MMCMMC_INTER_PLMN_SEARCH_REQ),
                                    (struct MsgCB*)pstInterPlmnSrchMsg);
            PS_MEM_FREE(WUEPS_PID_MMC, pstInterPlmnSrchMsg);
        }
        else
        {
            /* 异常打印 */
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmMmcServiceRsltInd_PlmnSelection_WaitEpsConnRelInd Alloc mem fail");
        }
    }
    /* Added by b00269685 for 自主FR优化, 2014-10-16, end */

    NAS_MMC_PerformAdditionalActionRegFinished_PlmnSelection();

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitAsSuspendCnfCsPsMode1ReCampLte
 功能描述  : CS/PS mode 1重新驻留Lte模suspend CNF过程中接收到Abort消息
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息未完成
             VOS_TRUE:处理消息完成
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年6月01日
   作    者   : s46746
   修改内容   : 新生成函数

****************************************************************************/

VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitAsSuspendCnfCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 记录需要终止当前状态机标志 */
    NAS_MMC_SetAbortFlag_PlmnSelection(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmSuspendCnf_PlmnSelection_WaitWasSuspendCnfCsPsMode1ReCampLte
 功能描述  : CS/PS mode 1重新驻留Lte模收到WAS的suspend cnf消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息未完成
             VOS_TRUE:处理消息完成
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年6月01日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2014年2月18日
   作    者  :  w00242748
   修改内容  :  DTS2014021803515:复位时明确是收到哪个接入技术的异常消息导致的。
 3.日    期   : 2014年3月19日
   作    者   : w00242748
   修改内容   : DTS2014031200137:当NV特性打开时，自动开机或者搜网时，如果首次搜索RPLMN的话，
                需要将HPLMN/EHPLMN带给接入层。
 4.日    期   : 2015年3月11日
   作    者   : wx270776
   修改内容   : DTS2015011212939:增加复位场景
*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvRrMmSuspendCnf_PlmnSelection_WaitWasSuspendCnfCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_CNF_ST                *pstSuspendCnf = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU          stReCampLtePlmn;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;
    NAS_MML_PLMN_LIST_WITH_RAT_STRU     stDestPlmnList;
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene;

    PS_MEM_SET(&stReCampLtePlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));
    PS_MEM_SET(&stDestPlmnList, 0, sizeof(NAS_MML_PLMN_LIST_WITH_RAT_STRU));

    pstSuspendCnf            = (RRMM_SUSPEND_CNF_ST*)pstMsg;
    stReCampLtePlmn.enRat    = NAS_MML_NET_RAT_TYPE_LTE;

    PS_MEM_CPY(&(stReCampLtePlmn.stPlmnId),
               NAS_MMC_GetCsPsMode1ReCampLtePlmn_PlmnSelection(),
               sizeof(stReCampLtePlmn.stPlmnId));

    enCurRat      = NAS_MML_GetCurrNetRatType();

    enPlmnSearchScene  = NAS_MMC_GetPlmnSearchScene_PlmnSelection();

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

    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        /* 设置当前接入技术为BUTT */
        NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

        /* 回复Plmn Selection执行结果 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 搜索需要重新回LTE的网络，
       由于挂起过程中可能接收到用户Detach PS操作，此处需要再判断网络是否有效 */
    if (VOS_TRUE == NAS_MMC_IsReCampLtePlmnValid_PlmnSelection())
    {
        /* 设置当前接入技术为LTE */
        NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_LTE);

        /* 向LMM发送指定搜网 */
        PS_MEM_SET(&stDestPlmnList, 0x0, sizeof(stDestPlmnList));

        stDestPlmnList.ulPlmnNum = 1;
        PS_MEM_CPY(&stDestPlmnList.astPlmnId[0], &stReCampLtePlmn, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

        NAS_MMC_SndLmmSpecPlmnSearchReq(&stDestPlmnList, VOS_FALSE, enPlmnSearchScene);

        /* 状态迁移NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_SEARCH_CNF_CSPSMODE1_RECAMP_LTE */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_SEARCH_CNF_CSPSMODE1_RECAMP_LTE);

        /* 启动保护定时器TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF, TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF_LEN);
    }
    else
    {
        /* 设置当前接入技术为BUTT */
        NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

        /* 回复Plmn Selection执行结果 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmSuspendCnf_PlmnSelection_WaitGasSuspendCnfCsPsMode1ReCampLte
 功能描述  : CS/PS mode 1重新驻留Lte模收到GAS的suspend cnf消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息未完成
             VOS_TRUE:处理消息完成
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年6月01日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2014年3月19日
   作    者   : w00242748
   修改内容   : DTS2014031200137:当NV特性打开时，自动开机或者搜网时，如果首次搜索RPLMN的话，
                需要将HPLMN/EHPLMN带给接入层。
 3.日    期   : 2015年3月11日
   作    者   : wx270776
   修改内容   : DTS2015011212939:增加复位场景
*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvRrMmSuspendCnf_PlmnSelection_WaitGasSuspendCnfCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_CNF_ST                *pstSuspendCnf = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU          stReCampLtePlmn;
    NAS_MML_PLMN_LIST_WITH_RAT_STRU     stDestPlmnList;
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene;

    PS_MEM_SET(&stReCampLtePlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));
    PS_MEM_SET(&stDestPlmnList, 0, sizeof(NAS_MML_PLMN_LIST_WITH_RAT_STRU));

    pstSuspendCnf            = (RRMM_SUSPEND_CNF_ST*)pstMsg;
    stReCampLtePlmn.enRat    = NAS_MML_NET_RAT_TYPE_LTE;

    PS_MEM_CPY(&(stReCampLtePlmn.stPlmnId),
               NAS_MMC_GetCsPsMode1ReCampLtePlmn_PlmnSelection(),
               sizeof(stReCampLtePlmn.stPlmnId));

    enPlmnSearchScene  = NAS_MMC_GetPlmnSearchScene_PlmnSelection();

    /* 停止定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF);

    if (MMC_AS_SUSPEND_FAILURE == pstSuspendCnf->ucResult)
    {
        /* 不可恢复错误,调用底软接口RESET */
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_GAS_SUSPEND_FAILURE);

        return VOS_TRUE;
    }

    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        /* 设置当前接入技术为BUTT */
        NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

        /* 回复Plmn Selection执行结果 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 搜索需要重新回LTE的网络，
       由于挂起过程中可能接收到用户Detach PS操作，此处需要再判断网络是否有效 */
    if (VOS_TRUE == NAS_MMC_IsReCampLtePlmnValid_PlmnSelection())
    {
        /* 设置当前接入技术为LTE */
        NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_LTE);

        /* 向LMM发送指定搜网 */
        PS_MEM_SET(&stDestPlmnList, 0x0, sizeof(stDestPlmnList));

        stDestPlmnList.ulPlmnNum = 1;
        PS_MEM_CPY(&stDestPlmnList.astPlmnId[0], &stReCampLtePlmn, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

        NAS_MMC_SndLmmSpecPlmnSearchReq(&stDestPlmnList, VOS_FALSE, enPlmnSearchScene);

        /* 状态迁移NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_SEARCH_CNF_CSPSMODE1_RECAMP_LTE */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_SEARCH_CNF_CSPSMODE1_RECAMP_LTE);

        /* 启动保护定时器TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF, TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF_LEN);
    }
    else
    {
        /* 设置当前接入技术为BUTT */
        NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

        /* 回复Plmn Selection执行结果 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitAsSuspendCnfExpired_PlmnSelection_WaitAsSuspendCnfCsPsMode1ReCampLte
 功能描述  : CS/PS mode 1重新驻留Lte模suspend CNF过程中保护定时器超时
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息未完成
             VOS_TRUE:处理消息完成
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年6月01日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2014年2月18日
   作    者  :  w00242748
   修改内容  :  DTS2014021803515:复位时明确是收到哪个接入技术的异常消息导致的。
 3.日    期   : 2015年3月11日
   作    者   : wx270776
   修改内容   : DTS2015011212939:增加复位场景
****************************************************************************/

VOS_UINT32 NAS_MMC_RcvTiWaitAsSuspendCnfExpired_PlmnSelection_WaitAsSuspendCnfCsPsMode1ReCampLte(
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
    else if ( NAS_MML_NET_RAT_TYPE_LTE == enCurRat)
    {
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_LMM_SUSPEND_CNF_EXPIRED);
    }
    else
    {
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_TD_SUSPEND_CNF_EXPIRED);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitLmmPlmnSearchCnfCsPsMode1ReCampLte
 功能描述  : CS/PS mode 1重新驻留LTE等待LTE搜网回复过程中收到状态机退出消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息未完成
             VOS_TRUE:处理消息完成
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年6月01日
   作    者   : s46746
   修改内容   : 新生成函数

*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitLmmPlmnSearchCnfCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF);

    NAS_MMC_SetAbortFlag_PlmnSelection(VOS_TRUE);

    /* 通知LMM停止指定搜网 */
    NAS_MMC_SndLmmPlmnSrchStopReq();

    /*迁移到等待停止搜网确认状态，启动保护定时器*/
    NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_STOP_CNF_CSPSMODE1_RECAMP_LTE);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmPlmnCnf_PlmnSelection_WaitLmmPlmnSearchCnfCsPsMode1ReCampLte
 功能描述  : CS/PS mode 1重新驻留Lte模收到LTE搜网CNF后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:ID_LMM_MMC_PLMN_SRCH_CNF消息的首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息未完成
             VOS_TRUE:处理消息完成
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年6月01日
   作    者   : s46746
   修改内容   : 新生成函数

  2.日    期   : 2012年9月27日
    作    者   : z40661
    修改内容   : DTS2012091205098,L下无网络时,未设置全频段搜网
  3.日    期   : 2014年5月5日
    作    者   : w00242748
    修改内容   : DTS2014043000311:注册状态服务状态不一致，将MMC中报服务状态的场景，都加
                 注册状态的上报。
  4.日    期   : 2014年6月12日
    作    者   : w00167002
    修改内容   : DSDS III:在NO RF后进OOC状态
  5.日    期   : 2015年4月23日
    作    者   : z00161729
    修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmPlmnCnf_PlmnSelection_WaitLmmPlmnSearchCnfCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_PLMN_SRCH_CNF_STRU                             *pstLmmSrchCnfMsg = VOS_NULL_PTR;

    NAS_MML_PLMN_WITH_RAT_STRU                              stReCampLtePlmn;

    pstLmmSrchCnfMsg = (LMM_MMC_PLMN_SRCH_CNF_STRU*)pstMsg;

    /* 停止定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF);

    /* 设置当前模式是否进行全频搜网，是否存在网络覆盖 */
    NAS_MMC_UpdateLmmCoverageFlg_PlmnSelection(pstLmmSrchCnfMsg);

    if (MMC_LMM_PLMN_SRCH_RLT_SPEC_SUCC == pstLmmSrchCnfMsg->enRlst)
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_SUCCESS,
                VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        /* disable lte原因不是MMC_LMM_DISABLE_LTE_REASON_LMM_NOTIFY_EUTRAN_NOT_ALLOW时，
           如果该网络在禁止接入技术网络中则删除 */
        if (MMC_LMM_DISABLE_LTE_REASON_LMM_NOTIFY_EUTRAN_NOT_ALLOW != NAS_MML_GetDisableLteReason())
        {
            stReCampLtePlmn.enRat    = NAS_MML_NET_RAT_TYPE_LTE;
            PS_MEM_CPY(&(stReCampLtePlmn.stPlmnId),
               NAS_MMC_GetCsPsMode1ReCampLtePlmn_PlmnSelection(),
               sizeof(stReCampLtePlmn.stPlmnId));
            NAS_MML_DeleteSpecDisabledPlmnWithValidPeriodInPlmnList(&stReCampLtePlmn);
        }

        /*迁移状态，启动保护定时器 */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_SYSINFO_IND_CSPSMODE1_RECAMP_LTE);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_SYS_INFO, TI_NAS_MMC_WAIT_LMM_SYS_INFO_LEN);
    }
    else
    {

        /* 如果当前为NO RF，则直接退状态机 */
        if (MMC_LMM_PLMN_SRCH_RLT_SPEC_NO_RF == pstLmmSrchCnfMsg->enRlst)
        {
            NAS_MMC_ProcNoRf_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE);

            return VOS_TRUE;
        }

        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        /* 在注册结果中设置了CS/PS服务状态但未上报，此时需要更新 */



        /* 更新当前接入技术进行了全频搜网 */
        NAS_MMC_SetAllBandSearch_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE, VOS_TRUE);


        /* 向上层状态机指示选网失败 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);

        /* 退出层二状态机 */
        NAS_MMC_FSM_QuitFsmL2();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmAttachCnf_PlmnSelection_WaitLmmPlmnSearchCnfCsPsMode1ReCampLte
 功能描述  : CS/PS mode 1重新驻留Lte模收到ID_LMM_MMC_ATTACH_CNF的处理
 输入参数  : ulEventType:消息类型
             pstMsg:ID_LMM_MMC_ATTACH_CNF消息的首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息未完成
             VOS_TRUE:处理消息完成
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年9月3日
   作    者   : s00217060
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmAttachCnf_PlmnSelection_WaitLmmPlmnSearchCnfCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 当前LTE的能力状态不为DISABLE状态，则不处理该消息 */
    if (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS != NAS_MML_GetLteCapabilityStatus())
    {
        /* 异常打印 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmAttachCnf_PlmnSelection_WaitLmmPlmnSearchCnfCsPsMode1ReCampLte: unexpect message received");

        return VOS_TRUE;
    }

    /* 停止定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF);

    /* 通知LMM停止指定搜网 */
    NAS_MMC_SndLmmPlmnSrchStopReq();

    /*迁移状态，启动保护定时器*/
    NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_STOP_CNF_CSPSMODE1_RECAMP_LTE);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF_LEN);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmDetachCnf_PlmnSelection_WaitLmmPlmnSearchCnfCsPsMode1ReCampLte
 功能描述  : CS/PS mode 1重新驻留Lte模收到ID_LMM_MMC_DETACH_CNF的处理
 输入参数  : ulEventType:消息类型
             pstMsg:ID_LMM_MMC_DETACH_CNF消息的首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息未完成
             VOS_TRUE:处理消息完成
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年5月29日
   作    者   : s46746
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmDetachCnf_PlmnSelection_WaitLmmPlmnSearchCnfCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 当前LTE的能力状态不为DISABLE状态，则不处理该消息 */
    if (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS != NAS_MML_GetLteCapabilityStatus())
    {
        /* 异常打印 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmDetachCnf_PlmnSelection_WaitLmmPlmnSearchCnfCsPsMode1ReCampLte: unexpect message received");

        return VOS_TRUE;
    }

    /* 停止定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF);

    /* 通知LMM停止指定搜网 */
    NAS_MMC_SndLmmPlmnSrchStopReq();

    /*迁移状态，启动保护定时器*/
    NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_STOP_CNF_CSPSMODE1_RECAMP_LTE);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF_LEN);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitLmmPlmnSearchCnfExpired_PlmnSelection_WaitLmmPlmnSearchCnfCsPsMode1ReCampLte
 功能描述  : CS/PS mode 1重新驻留Lte模等待LTE搜网回复过程中搜网定时器超时
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息未完成
             VOS_TRUE:处理消息完成
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年5月29日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2014年5月5日
   作    者   : w00242748
   修改内容   : DTS2014043000311:注册状态服务状态不一致，将MMC中报服务状态的场景，都加
                注册状态的上报。
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitLmmPlmnSearchCnfExpired_PlmnSelection_WaitLmmPlmnSearchCnfCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitLmmPlmnSearchCnfExpired_PlmnSelection_WaitLmmPlmnSearchCnfCsPsMode1ReCampLte ENTERED");

    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                    VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    /* 在注册结果中设置了CS/PS服务状态但未上报，此时需要更新 */


    /* 向上层状态机指示选网失败 */
    NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);

    /* 退出层二状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmPlmnStopCnf_PlmnSelection_WaitLmmPlmnStopCnfCsPsMode1ReCampLte
 功能描述  : CS/PS mode 1重新驻留Lte模收到LTE的plmn search stop cnf消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息未完成
             VOS_TRUE:处理消息完成
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年6月2日
   作    者   : s46746
   修改内容   : 新生成函数

*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvLmmPlmnStopCnf_PlmnSelection_WaitLmmPlmnStopCnfCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止定时器 */
    NAS_MMC_StopTimer( TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF );

    /* 判断是否存在打断标志 */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        /* 向上层状态机指示选网被打断 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);
    }
    else
    {
        /* 向上层状态机指示选网失败 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);
    }

    /* 退出层二状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitLmmStopCnfExpired_PlmnSelection_WaitLmmPlmnStopCnfCsPsMode1ReCampLte
 功能描述  : CS/PS mode 1重新驻留Lte模等待LTE的plmn search stop CNF过程中保护定时器超时
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息未完成
             VOS_TRUE:处理消息完成
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年6月2日
   作    者   : s46746
   修改内容   : 新生成函数

****************************************************************************/

VOS_UINT32 NAS_MMC_RcvTiWaitLmmStopCnfExpired_PlmnSelection_WaitLmmPlmnStopCnfCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitLmmStopCnfExpired_PlmnSelection_WaitLmmPlmnStopCnfCsPsMode1ReCampLte: Timer Expired");

    /* 判断是否存在打断标志 */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        /* 向上层状态机指示选网被打断 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);
    }
    else
    {
        /* 向上层状态机指示选网失败 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);
    }

    /* 退出层二状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmPlmnSearchCnf_PlmnSelection_WaitLmmPlmnStopCnfCsPsMode1ReCampLte
 功能描述  : CS/PS mode 1重新驻留Lte模等待Lmm搜网回复状态收到LTE的plmn search cnf消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息未完成
             VOS_TRUE:处理消息完成
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年6月2日
   作    者   : s46746
   修改内容   : 新生成函数

*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvLmmPlmnSearchCnf_PlmnSelection_WaitLmmPlmnStopCnfCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_PLMN_SRCH_CNF_STRU          *pstLmmSrchCnfMsg = VOS_NULL_PTR;

    pstLmmSrchCnfMsg = (LMM_MMC_PLMN_SRCH_CNF_STRU*)pstMsg;

    /* 停止定时器 */
    NAS_MMC_StopTimer( TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF );

    /* 设置当前模式是否进行全频搜网，是否存在网络覆盖 */
    NAS_MMC_UpdateLmmCoverageFlg_PlmnSelection(pstLmmSrchCnfMsg);

    /* 判断是否存在打断标志 */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        /* 向上层状态机指示选网终止 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);
    }
    else
    {
        /* 向上层状态机指示选网失败 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);
    }

    /* 退出层二状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitLSysInfoIndCsPsMode1ReCampLte
 功能描述  : CS/PS mode 1重新驻留Lte模等待系统消息MMC处理Aort消息
 输入参数  : ulEventType:消息类型
             pstMsg:Abort消息的首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息未完成
             VOS_TRUE:处理消息完成
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月2日
    作    者   : s46746
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitLSysInfoIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 设置Abort标志 */
    NAS_MMC_SetAbortFlag_PlmnSelection(VOS_TRUE);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLSysInfoInd_PlmnSelection_WaitLSysInfoIndCsPsMode1ReCampLte
 功能描述  : CS/PS mode 1重新驻留Lte模MMC处理LMM上报的系统消息
 输入参数  : ulEventType:消息类型
             pstMsg:LMM上报的系统消息的首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息未完成
             VOS_TRUE:处理消息完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年6月2日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年11月29日
   作    者   : w00176964
   修改内容   : DTS2012042804167:通知CBA模块当前接入模式为LTE
 3.日    期   : 2012年12月20日
   作    者   : w00176964
   修改内容   : DTS2012121906946:收到L的系统消息转发给LMM
 4.日    期   : 2013年1月19日
   作    者   : t00212959
   修改内容   : DTS2012122900189:EPS注册状态完全由L上报
 5.日    期   : 2013年2月7日
   作    者   : W00176964
   修改内容   : Volte_phase3项目调整:增加IMS不可用时disable L模的逻辑修改
 6.日    期   : 2015年02月11日
   作    者   : l00305157
   修改内容   : Service_State_Optimize_PhaseII 项目修改
                 方案优化后，LTE下的小区发生变化，LMM会通过系统消息通知MMC
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLSysInfoInd_PlmnSelection_WaitLSysInfoIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;

    NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8                enSpecPlmnSearchState;

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

    /* 保留老的驻留网络信息 */
    pstCurCampInfo  = NAS_MML_GetCurrCampPlmnInfo();
    PS_MEM_CPY(&stOldCampInfo, pstCurCampInfo, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

    /* 停止等待系统消息的定时器  */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_SYS_INFO);

    /* 状态更新为当前已经驻留 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

    /* 如果当前需要退出状态机 */
    if (VOS_TRUE  == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        /* 回复状态机被打断 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 根据系统消息，更新MML的全部变量 */
    NAS_MMC_UpdateNetworkInfo_LmmSysInfo(pstMsg);



    /* 更新当前搜网状态结束 */
    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_STOP);

    /* 更新当前等待EPS的注册结果 */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnSelection();
    NAS_MMC_SetWaitRegRsltFlag_PlmnSelection(NAS_MMC_WAIT_REG_RESULT_IND_PS);

    /* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-7, begin */
#if (FEATURE_ON == FEATURE_IMS)
    /* 增加等待IMS是否可用结果FLG,MMA保证收到PS注册结果上报IMS是否可用指示到MMC */
    NAS_MMC_SetWaitRegRsltFlag_PlmnSelection(NAS_MMC_WAIT_REG_RESULT_IND_IMS);
#endif
    /* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-7, end */

    /* 更新CS/PS的注册Cause和AdditionalAction */
    NAS_MMC_SetCsRegCause_PlmnSelection(NAS_MML_REG_FAIL_CAUSE_BUTT);
    NAS_MMC_SetPsRegCause_PlmnSelection(NAS_MML_REG_FAIL_CAUSE_BUTT);

    NAS_MMC_SetCsRegAdditionalAction_PlmnSelection(NAS_MMC_ADDITIONAL_ACTION_BUTT);
    NAS_MMC_SetPsRegAdditionalAction_PlmnSelection(NAS_MMC_ADDITIONAL_ACTION_BUTT);

    /* CBS上报*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_LTE);

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, end */
    enSpecPlmnSearchState = NAS_MMC_GetSpecPlmnSearchState();

    /*方案优化后，LTE下的小区发生变化，LMM会通过系统消息通知MMC*/
    if ((VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
     || (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == enSpecPlmnSearchState))
    {
        NAS_MMC_SndMsccSysInfo();

    }


    /* 转发GMM系统消息 */
    NAS_MMC_SndGmmLteSysinfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);
    NAS_MMC_SndMmLteSysinfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);

    NAS_MMC_SndLmmLteSysInfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);

    /* 迁移到等待注册结果子状态PLMN_SRCH:NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND_CSPSMODE1_RECAMP_LTE);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_REG_IND, TI_NAS_MMC_WAIT_EPS_REG_IND_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitLSysInfoExpired_PlmnSelection_WaitLSysInfoIndCsPsMode1ReCampLte
 功能描述  : CS/PS mode 1重新驻留LTE等待系统消息定时器超时的处理
 输入参数  : ulEventType:消息类型
             pstMsg:TI_NAS_MMC_WAIT_SYS_INFO超时消息的首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息未完成
             VOS_TRUE:处理消息完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年6月2日
   作    者   : s46746
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitLSysInfoExpired_PlmnSelection_WaitLSysInfoIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitLSysInfoExpired_PlmnSelection_WaitLSysInfoIndCsPsMode1ReCampLte: Timer Expired");

    /* 清除驻留状态 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);

    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);
    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* 当前信号更新 */
    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());

    /*如果当前需要退出状态机*/
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        /* 回复状态机被打断 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);
    }
    else
    {
        /* 向上层状态机指示选网失败 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);
    }

    /* 退出层二状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte
 功能描述  : CS/PS mode 1重新驻留Lte模在等待EPS上报注册结果的时候收到QUIT消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg: Abort消息的首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息未完成
             VOS_TRUE:处理消息完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年6月2日
   作    者   : s46746
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ABORT_FSM_STRU             *pstAbortMsg;

    pstAbortMsg = (NAS_MMC_ABORT_FSM_STRU*)pstMsg;

    /* 若打断类型是用户请求的关机或立即打断或当前没有链接可以直接退出 */
    if ((VOS_FALSE == NAS_MML_IsRrcConnExist())
     || (NAS_MMC_ABORT_FSM_IMMEDIATELY == pstAbortMsg->enAbortFsmType)
     /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, begin*/
     || (NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_OFF_REQ) == pstAbortMsg->ulEventType))
     /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, end*/
    {
        /* 停止等待eps注册结果消息的定时器  */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

        /* 回复状态机被打断 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 设置Abort标志 */
    NAS_MMC_SetAbortFlag_PlmnSelection(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmMmcStatusInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte
 功能描述  : CS/PS mode 1重新驻留Lte模LMM上报的CONN Status Ind消息处理函数
 输入参数  : ulEventType:消息类型
             pstMsg:ID_LMM_MMC_STATUS_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息未完成
             VOS_TRUE:处理消息完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年6月2日
   作    者   : s46746
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmMmcStatusInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_STATUS_IND_STRU            *pstLmmStatusIndMsg = VOS_NULL_PTR;

    pstLmmStatusIndMsg = (LMM_MMC_STATUS_IND_STRU*)pstMsg;

    /* 更新LMM的链接状态 */
    NAS_MML_UpdateEpsConnectionStatus(pstLmmStatusIndMsg->ulConnState);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmMmcAttachInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte
 功能描述  : CS/PS mode 1重新驻留Lte模WaitEpsRegRsltInd时，LMM上报的ID_LMM_MMC_ATTACH_IND消息处理函数
 输入参数  : ulEventType:消息类型
             pstMsg:ID_LMM_MMC_ATTACH_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息未完成
             VOS_TRUE:处理消息完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年6月2日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2013年2月7日
   作    者   : W00176964
   修改内容   : Volte_phase3项目调整:增加IMS不可用时disable L模的逻辑修改
 3.日    期   : 2015年4月22日
   作    者   : wx270776
   修改内容   : DTS2015031602665:将CL ATTACH注册状态存入全局变量
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmMmcAttachInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    LMM_MMC_ATTACH_IND_STRU                                *pstLmmAttachIndMsg = VOS_NULL_PTR;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;

    pstLmmAttachIndMsg  = (LMM_MMC_ATTACH_IND_STRU*)pstMsg;

    /* 清除等待PS标志 */
    NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnSelection(NAS_MMC_WAIT_REG_RESULT_IND_PS);

    if ( VOS_TRUE == NAS_MMC_IsNeedUpdateLmmAttachClRegStatus_PlmnSelection(pstLmmAttachIndMsg->enClAttRegStatus) )
    {
        NAS_MMC_SetLmmAttachClRegStatus_PlmnSelection(pstLmmAttachIndMsg->enClAttRegStatus);
    }

    /* LMM在搜网未回复search cnf时收到用户detach ps请求后，后续不会做注册给mmc回复attach result
       为MMC_LMM_ATT_RSLT_PS_ATT_NOT_ALLOW，请求类型填的是MMC_LMM_ATT_TYPE_BUTT，
       MMC需要根据当前ue operation mode给请求类型重新赋值 */
    if ((MMC_LMM_ATT_TYPE_BUTT == pstLmmAttachIndMsg->ulReqType)
     && (MMC_LMM_ATT_RSLT_PS_ATT_NOT_ALLOW == pstLmmAttachIndMsg->ulAttachRslt))
    {
        pstLmmAttachIndMsg->ulReqType = NAS_MMC_ConvertLmmAttachReqType(NAS_MML_GetLteUeOperationMode());
    }

    /* 向GMM和MM转发注册结果消息 */
    NAS_MMC_SndMmLmmAttachInd(pstLmmAttachIndMsg);
    NAS_MMC_SndGmmLmmAttachInd(pstLmmAttachIndMsg);

    /* 处理attach结果 */
    NAS_MMC_ProcLmmAttachInd_PlmnSelection(pstLmmAttachIndMsg);

    /* 如果当前需要退出状态机 */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        /* 状态机退出结果为Abort */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* 停止等待eps注册结果消息的定时器  */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 调用优先级比较表格得出CS/PS的处理优先级，并转换为状态机下一步行为 */
    enAdditionalAction   = NAS_MMC_GetPrioAddtionalAction(NAS_MMC_GetCsRegAdditionalAction_PlmnSelection(),
                                                          NAS_MMC_GetPsRegAdditionalAction_PlmnSelection());

    if (NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT == enAdditionalAction)
    {
        return VOS_TRUE;
    }

    /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2014-2-7, begin */
    if (NAS_MMC_WAIT_REG_RESULT_IND_NULL != NAS_MMC_GetWaitRegRsltFlag_PlmnSelection())
    {
        return VOS_TRUE;
    }

    /* 停定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);
    /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2014-2-7, end */

    /* 附加操作为驻留当前网络 */
    if (VOS_FALSE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(enAdditionalAction))
    {
        /* 回复状态机退出成功 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_SUCC);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /*  如果存在信令连接，迁移到等待连接释放状态  */
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REL_IND_CSPSMODE1_RECAMP_LTE);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND, TI_NAS_MMC_WAIT_EPS_CONN_REL_IND_LEN);

        return VOS_TRUE;
    }

    /* 重新驻留LTE时将服务状态上报 */
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, begin*/
    NAS_MMC_SndMsccServiceStatusInd(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_GetServiceStatusForMscc(NAS_MSCC_PIF_SRVDOMAIN_CS));
    NAS_MMC_SndMsccServiceStatusInd(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_GetServiceStatusForMscc(NAS_MSCC_PIF_SRVDOMAIN_PS));
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, end*/

    /* 回复状态机退出失败 */
    NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);

    if (VOS_TRUE == NAS_MML_GetSimPsRegStatus())
    {
        /* 清除Disable L全局变量标志 */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_REENABLE_NOTIFIED_AS);
    }

    /* 直接退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmMmcTauResultInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte
 功能描述  : CS/PS mode 1重新驻留Lte模在等待LTE注册结果时候
              收到ID_LMM_MMC_TAU_RESULT_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息未完成
             VOS_TRUE:处理消息完成
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月2日
    作    者   : s46746
    修改内容   : 新生成函数
  2.日    期   : 2013年2月7日
    作    者   : W00176964
    修改内容   : Volte_phase3项目调整:增加IMS不可用时disable L模的逻辑修改

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmMmcTauResultInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_TAU_RESULT_IND_STRU                            *pstLmmTauIndMsg = VOS_NULL_PTR;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;

    pstLmmTauIndMsg  = (LMM_MMC_TAU_RESULT_IND_STRU*)pstMsg;

    /* 清除等待PS标志 */
    NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnSelection(NAS_MMC_WAIT_REG_RESULT_IND_PS);

    /* 向GMM和MM转发TAU结果消息 */
    NAS_MMC_SndMmLmmTauResultInd(pstLmmTauIndMsg);
    NAS_MMC_SndGmmLmmTauResultInd(pstLmmTauIndMsg);

    /* 处理TAU结果 */
    NAS_MMC_ProcLmmTauResultInd_PlmnSelection(pstLmmTauIndMsg);

    /* 如果当前需要退出状态机 */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        /* 状态机退出结果为Abort */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* 停止等待eps注册结果消息的定时器  */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 调用优先级比较表格得出CS/PS的处理优先级，并转换为状态机下一步行为 */
    enAdditionalAction   = NAS_MMC_GetPrioAddtionalAction(NAS_MMC_GetCsRegAdditionalAction_PlmnSelection(),
                                                          NAS_MMC_GetPsRegAdditionalAction_PlmnSelection());

    if (NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT == enAdditionalAction)
    {
        return VOS_TRUE;
    }

    /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2014-2-7, begin */
    if (NAS_MMC_WAIT_REG_RESULT_IND_NULL != NAS_MMC_GetWaitRegRsltFlag_PlmnSelection())
    {
        return VOS_TRUE;
    }

    /* 停定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);
    /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2014-2-7, end */

    /* 附加操作为驻留当前网络 */
    if (VOS_FALSE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(enAdditionalAction))
    {
        /* 回复状态机退出成功 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_SUCC);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /*  如果存在信令连接，迁移到等待连接释放状态  */
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REL_IND_CSPSMODE1_RECAMP_LTE);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND, TI_NAS_MMC_WAIT_EPS_CONN_REL_IND_LEN);

        return VOS_TRUE;
    }

    /* 重新驻留LTE时将服务状态上报 */
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, begin*/
    NAS_MMC_SndMsccServiceStatusInd(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_GetServiceStatusForMscc(NAS_MSCC_PIF_SRVDOMAIN_CS));
    NAS_MMC_SndMsccServiceStatusInd(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_GetServiceStatusForMscc(NAS_MSCC_PIF_SRVDOMAIN_PS));
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, end*/

    /* 回复状态机退出失败 */
    NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);

    if (VOS_TRUE == NAS_MML_GetSimPsRegStatus())
    {
        /* 清除Disable L全局变量标志 */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_REENABLE_NOTIFIED_AS);
    }

    /* 直接退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmMmcDetachInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte
 功能描述  : CS/PS mode 1重新驻留Lte模在等待LTE注册结果时候
              收到ID_LMM_MMC_DETACH_IND消息的处理,与LMM确认，该场景下只存在网络Detach PS类型
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息未完成
             VOS_TRUE:处理消息完成
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月9日
    作    者   : s46746
    修改内容   : 新生成函数
  2.日    期   : 2013年1月11日
    作    者   : w00176964
    修改内容   : DTS2013010706662:调整发送EPLMN逻辑调用位置

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmMmcDetachInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_DETACH_IND_STRU                                *pstDetachMsg = VOS_NULL_PTR;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;

    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));
    pstDetachMsg        = (LMM_MMC_DETACH_IND_STRU*)pstMsg;

    /* 处理DETACH消息，输出下一步动作 */
    NAS_MMC_ProcLmmDetachInd(pstDetachMsg, &enCsAdditionalAction, &enPsAdditionalAction);

    /*更新EPS的下一步的动作类型*/
    if (NAS_MMC_ADDITIONAL_ACTION_BUTT != enPsAdditionalAction)
    {
        NAS_MMC_SetPsRegAdditionalAction_PlmnSelection(enPsAdditionalAction);
    }

    /*更新CS的下一步的动作类型*/
    if (NAS_MMC_ADDITIONAL_ACTION_BUTT != enCsAdditionalAction)
    {
        NAS_MMC_SetCsRegAdditionalAction_PlmnSelection(enCsAdditionalAction);
    }

    if (VOS_TRUE == NAS_MMC_IsNeedSndEplmn_PlmnSelection())
    {
        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildSndLmmEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndLmmEquPlmnReq(&stSndEquPlmnInfo);
        NAS_MMC_SndOmEquPlmn();
    }

    /* 如果当前需要退出状态机 */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        /* 状态机退出结果为Abort */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* 停止等待eps注册结果消息的定时器  */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 调用优先级比较表格得出CS/PS的处理优先级，并转换为状态机下一步行为 */
    enAdditionalAction   = NAS_MMC_GetPrioAddtionalAction(NAS_MMC_GetCsRegAdditionalAction_PlmnSelection(),
                                                              NAS_MMC_GetPsRegAdditionalAction_PlmnSelection());

    /* 选网动作AdditionalAction为需要继续等待注册结果 */
    if (NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT == enAdditionalAction)
    {
        /*返回继续等待注册结果*/
        return VOS_TRUE;
    }

    /* 停定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

    /* 附加操作为驻留当前网络 */
    if (VOS_FALSE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(enAdditionalAction))
    {
        /* 回复状态机退出成功 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_SUCC);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /*  如果存在信令连接，迁移到等待连接释放状态  */
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REL_IND_CSPSMODE1_RECAMP_LTE);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND, TI_NAS_MMC_WAIT_EPS_CONN_REL_IND_LEN);
    }
    else
    {
        /* 回复状态机退出失败 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();
    }

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmMmcServiceRsltInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte
 功能描述  : CS/PS mode 1重新驻留Lte模在等待LTE注册结果时候
              收到ID_LMM_MMC_SERVICE_RESULT_IND消息的处理,
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息未完成
             VOS_TRUE:处理消息完成
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月26日
    作    者   : s46746
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmMmcServiceRsltInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_SERVICE_RESULT_IND_STRU                        *pstSerRsltMsg = VOS_NULL_PTR;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;

    pstSerRsltMsg     = (LMM_MMC_SERVICE_RESULT_IND_STRU*)pstMsg;

    /* 对LMM的服务结果进行处理，处理完成后返回需要进行的选网动作 */
    enAdditionalAction = NAS_MMC_ProcLmmServiceRsltInd(pstSerRsltMsg);

    /* 选网动作AdditionalAction有效，更新EPS的下一步的动作类型 */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enAdditionalAction )
    {
        NAS_MMC_SetPsRegAdditionalAction_PlmnSelection(enAdditionalAction);
    }

    /* 如果当前需要退出状态机 */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        /* 状态机退出结果为Abort */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* 停止等待eps注册结果消息的定时器  */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 调用优先级比较表格得出CS/PS的处理优先级，并转换为状态机下一步行为 */
    enAdditionalAction   = NAS_MMC_GetPrioAddtionalAction(NAS_MMC_GetCsRegAdditionalAction_PlmnSelection(),
                                                              NAS_MMC_GetPsRegAdditionalAction_PlmnSelection());

    /* 选网动作AdditionalAction为需要继续等待注册结果 */
    if (NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT == enAdditionalAction)
    {
        /*返回继续等待注册结果*/
        return VOS_TRUE;
    }

    /* 停定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

    /* 附加操作为驻留当前网络 */
    if (VOS_FALSE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(enAdditionalAction))
    {
        /* 回复状态机退出成功 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_SUCC);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /*  如果存在信令连接，迁移到等待连接释放状态  */
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REL_IND_CSPSMODE1_RECAMP_LTE);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND, TI_NAS_MMC_WAIT_EPS_CONN_REL_IND_LEN);

        return VOS_TRUE;
    }

    /* 回复状态机退出失败 */
    NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);

    /* 直接退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmSuspendInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte
 功能描述  : CS/PS mode 1重新驻留Lte模等待注册结果时LMM上报的SUSPEND_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息未完成
             VOS_TRUE:处理消息完成
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月2日
    作    者   : s46746
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmSuspendInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_SUSPEND_IND_STRU           *pstLSuspendMsg = VOS_NULL_PTR;
    MMC_SUSPEND_CAUSE_ENUM_UINT8        enSuspendCause;

    pstLSuspendMsg = (LMM_MMC_SUSPEND_IND_STRU*)pstMsg;

    /* L模下，挂起原因定义与GU下不同，转换一下挂起原因定义 */
    NAS_MMC_ConvertLmmSysChngTypeToMmcType(pstLSuspendMsg->ulSysChngType, &enSuspendCause);

    /* 如果为OOS或者参数不正确, 则不允许进行异系统重选 */
    if (MMC_SUSPEND_CAUSE_BUTT <= enSuspendCause)
    {
        NAS_MMC_SndLmmSuspendRsp(MMC_LMM_FAIL);
    }
    else
    {
        /* 根据SUSPEND消息中的不同类型起相应的状态机 */
        NAS_MMC_LoadInterSysFsm_PlmnSelection(enSuspendCause);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcMmcSuspendRslt_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte
 功能描述  : CS/PS mode 1重新驻留Lte模等待注册结果时挂起状态机结果处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息未完成
             VOS_TRUE:处理消息完成
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月2日
    作    者   : s46746
    修改内容   : 新生成函数
  2.日    期   : 2013年4月9日
    作    者   : y00176023
    修改内容   : DSDS GUNAS II项目:收到NO RF 退状态机，发送失败迁移到ooc
  3.日    期   : 2014年1月27日
    作    者   : s00246516
    修改内容   : L-C互操作项目:增加异系统到HRPD的处理
  4.日    期   : 2014年6月30日
    作    者   : b00269685
    修改内容   : DSDS GUNAS III项目:修改函数名称
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmcMmcSuspendRslt_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;

    enRatType = NAS_MML_GetCurrNetRatType();

    if (VOS_FALSE == NAS_MML_GetRfAvailFlg())
    {
        /* 停止等待eps注册结果消息的定时器  */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

        /* 状态机退出结果为失败，迁移到OOC */
        NAS_MMC_ProcNoRf_PlmnSelection(enRatType);

        return VOS_TRUE;
    }

    /* 如果当前异系统改变到GU,直接退出状态机 */
    if ((NAS_MML_NET_RAT_TYPE_WCDMA == enRatType)
     || (NAS_MML_NET_RAT_TYPE_GSM == enRatType))
    {
        /* 状态机退出结果为成功 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_SUCC);

        /* 停止等待eps注册结果消息的定时器  */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();
    }


    /* Added by s00246516 for L-C互操作项目, 2014-01-27, Begin */
#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    /* 重选到HRPD后,退出选网状态机 */
    if (NAS_MML_NET_RAT_TYPE_BUTT == enRatType)
    {
        /* 停止等待eps注册结果消息的定时器  */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

        /* 向上层状态机发送高优先级搜索失败，需要搜网 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_INTER_SYS_HRPD);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }
#endif
    /* Added by s00246516 for L-C互操作项目, 2014-01-27, End */

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitEpsRegRsltIndExpired_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte
 功能描述  : CS/PS mode 1重新驻留Lte模等待注册结果时定时器超时
 输入参数  : ulEventType:消息类型
             pstMsg:TI_NAS_MMC_WAIT_EPS_REG_IND_TIMER超时的首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息未完成
             VOS_TRUE:处理消息完成
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月2日
    作    者   : s46746
    修改内容   : 新生成函数
  2.日    期   : 2014年5月5日
    作    者   : w00242748
    修改内容   : DTS2014043000311:注册状态服务状态不一致，将MMC中报服务状态的场景，都加
                 注册状态的上报。

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiWaitEpsRegRsltIndExpired_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitEpsRegRsltIndExpired_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte: Timer Expired");

    /* 调用NAS_MMC_SetPsServiceStatus更新EPS服务状态NAS_MMC_LIMITED_SERVICE */

    /* 通知TAF当前的服务状态 */

    /* 如果当前需要退出状态机 */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        /* 回复状态机被打断 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);
    }
    else
    {
        /* 发送状态机退出结果消息，结果为失败 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);
    }

    /* 直接退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmAreaLostInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte
 功能描述  : CS/PS mode 1重新驻留Lte模在等待EPS上报注册结果的时候收到丢网指示，
              无链接，直接构造搜网消息
 输入参数  : ulEventType:消息类型
             pstMsg:ID_LMM_MMC_AREA_LOST_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息未完成
             VOS_TRUE:处理消息完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年6月2日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2014年5月5日
   作    者   : w00242748
   修改内容   : DTS2014043000311:注册状态服务状态不一致，将MMC中报服务状态的场景，都加
                注册状态的上报。
 3.日    期   : 2014年6月12日
   作    者   : w00167002
   修改内容   : DSDS III:L下NO RF丢网后的处理
 4.日    期   : 2015年10月22日
   作    者   : s00217060
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0:RRMM_AREA_LOST_IND消息接口变更
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmAreaLostInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_AREA_LOST_IND_STRU          *pstLmmAreaLostMsg  = VOS_NULL_PTR;


    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo      = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stCurPlmn;

    pstLmmAreaLostMsg   =  (LMM_MMC_AREA_LOST_IND_STRU *)pstMsg;


    /* 获取高优先级网络列表 */
    pstPlmnSelectionListInfo = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();

    /* 获取当前驻留的网络信息 */
    pstCurCampInfo     = NAS_MML_GetCurrCampPlmnInfo();
    stCurPlmn.stPlmnId = pstCurCampInfo->stLai.stPlmnId;
    stCurPlmn.enRat    = pstCurCampInfo->enNetRatType;

    /* 停止等待Eps注册结果消息的定时器  */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

    /* 清除驻留状态 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());
    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

    /* 当前信号更新 */
    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());

    if (MMC_LMM_AREA_LOST_REASON_NO_RF == pstLmmAreaLostMsg->enAreaLostReason)
    {
        /* 更新当前网络状态为EXIT,资源恢复后再搜 */
        NAS_MMC_UpdatePlmnNetStatusInPlmnSelectionList(&stCurPlmn,
                                        NAS_MMC_NET_STATUS_SEARCHED_EXIST,
                                        pstPlmnSelectionListInfo);

        /* 回复状态机失败 */
        NAS_MMC_ProcNoRfAreaLost_PlmnSelection(NAS_MML_GetCurrNetRatType());

        return VOS_TRUE;
    }

    /* 更新服务状态 */

    /* 如果当前需要退出状态机 */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        /* 回复状态机选网被打断 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);
    }
    else
    {
        /* 发送状态机退出结果消息，结果为失败 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);
    }

    /* 直接退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLSysInfoInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte
 功能描述  : CS/PS mode 1重新驻留Lte模等待注册结果时MMC处理LMM上报的系统消息
 输入参数  : ulEventType:消息类型
             pstMsg:LMM上报的系统消息地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息未完成
             VOS_TRUE:处理消息完成
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月2日
    作    者   : s46746
    修改内容   : 新生成函数
  2.日    期   : 2012年11月29日
    作    者   : w00176964
    修改内容   : DTS2012042804167:通知CBA模块当前接入模式为LTE
  3.日    期   : 2012年12月20日
    作    者   : w00176964
    修改内容   : DTS2012121906946:收到L的系统消息转发给LMM
 4. 日    期   : 2013年1月19日
    作    者   : t00212959
    修改内容   : DTS2012122900189:EPS注册状态完全由L上报
  5.日    期   : 2015年02月11日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseII 项目修改
                 方案优化后，LTE下的小区发生变化，LMM会通过系统消息通知MMC
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLSysInfoInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;

    NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8                enSpecPlmnSearchState;

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    /* 保留老的驻留网络信息 */
    pstCurCampInfo  = NAS_MML_GetCurrCampPlmnInfo();
    PS_MEM_CPY(&stOldCampInfo, pstCurCampInfo, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

    /* 根据系统消息，更新MML的全部变量 */
    NAS_MMC_UpdateNetworkInfo_LmmSysInfo(pstMsg);



    /* 状态更新为当前已经驻留 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

    /* CBS上报*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_LTE);

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, end */

    enSpecPlmnSearchState = NAS_MMC_GetSpecPlmnSearchState();

    /*方案优化后，LTE下的小区发生变化，LMM会通过系统消息通知MMC*/
    if ((VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
     || (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == enSpecPlmnSearchState))
    {
        NAS_MMC_SndMsccSysInfo();

    }

    /* 转发MM/GMM系统消息 */
    NAS_MMC_SndGmmLteSysinfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);
    NAS_MMC_SndMmLteSysinfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);

    NAS_MMC_SndLmmLteSysInfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTafPlmnSpecialReq_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte
 功能描述  : CS/PS mode 1重新驻留Lte模等待注册结果时MMC处理MSCC请求的指定搜网消息
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息未完成
             VOS_TRUE:处理消息完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年6月2日
   作    者   : s46746
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTafPlmnSpecialReq_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, begin*/
    MSCC_MMC_PLMN_SPECIAL_REQ_STRU                          *pstUserSelReqMsg  = VOS_NULL_PTR;
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, end*/

    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSrchList   = VOS_NULL_PTR;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsRegCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enPsRegCause;

    /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, begin*/
    pstUserSelReqMsg    = (MSCC_MMC_PLMN_SPECIAL_REQ_STRU*)pstMsg;
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, end*/

    /* 保存用户指定搜网信息，更新当前的搜网类型为手动模式 */
    NAS_MMC_UpdateUserSpecPlmnSearchInfo_PlmnSelection((NAS_MML_PLMN_ID_STRU*)(&pstUserSelReqMsg->stPlmnId),
                                                        pstUserSelReqMsg->enAccessMode);

    /* 获取选网列表 */
    pstPlmnSrchList = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();

    /* 根据用户指定搜网场景重新初始化选网列表 */
    NAS_MMC_InitPlmnSelectionList(NAS_MMC_PLMN_SEARCH_SCENE_USER_SPEC_PLMN_SEARCH,
                                  VOS_NULL_PTR,
                                  pstPlmnSrchList);

    /* 将用户指定接入技术的网络(也是当前网络)更新为已搜索注册避免重复注册 */
    NAS_MMC_UpdatePlmnNetStatusInPlmnSelectionList(NAS_MMC_GetUserSpecPlmnId(),
                                                   NAS_MMC_NET_STATUS_SEARCHED_REGISTERED,
                                                   pstPlmnSrchList);

    enCsRegCause = NAS_MMC_GetCsRegCause_PlmnSelection();
    enPsRegCause = NAS_MMC_GetPsRegCause_PlmnSelection();

    if (VOS_TRUE == NAS_MMC_ProcUserSearchRegRslt_PlmnSelection(enCsRegCause, enPsRegCause))
    {
        return VOS_TRUE;
    }

    /* 保存入口消息 */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

    /* 状态迁移到NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTafSysCfgReq_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte
 功能描述  : CS/PS mode 1重新驻留Lte模等待注册结果时MMC处理MSCC请求的SYSCFG设置消息
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息未完成
             VOS_TRUE:处理消息完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年6月2日
   作    者   : s46746
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTafSysCfgReq_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 直接调起syscfg层二状态机 */
    NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_SYSCFG);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcSyscfgRsltCnf_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte
 功能描述  : CS/PS mode 1重新驻留Lte模等待注册结果时处理SYSCFG状态机返回的结果
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息未完成
             VOS_TRUE:处理消息完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年6月2日
   作    者   : s46746
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmcSyscfgRsltCnf_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 状态机中不需要对SYSCFG状态机结果进行处理，直接返回 */
    return VOS_TRUE;
}

/* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-7, begin */
/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMsccImsVoiceCapInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte
 功能描述  : CS/PS mode 1重新驻留Lte模等待注册结果时处理MSCC的IMS VOICE不可用的消息
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息未完成
             VOS_TRUE:处理消息完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年2月7日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2015年4月23日
   作    者   : z00161729
   修改内容   : 24301 R11 CR升级项目修改

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMsccImsVoiceCapInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMC_IMS_VOICE_CAP_NOTIFY_STRU                     *pstImsVoiceNtf = VOS_NULL_PTR;
    VOS_UINT8                                               ucWaitRegRsltFlag;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;

    NAS_MML_PLMN_WITH_RAT_STRU                              stReCampLtePlmn;

    ucWaitRegRsltFlag   = NAS_MMC_GetWaitRegRsltFlag_PlmnSelection();
    pstImsVoiceNtf      = (MSCC_MMC_IMS_VOICE_CAP_NOTIFY_STRU *)pstMsg;

    /* 如果在等待PS的注册结果则继续等待PS注册结果 */
    if (NAS_MMC_WAIT_REG_RESULT_IND_PS == (ucWaitRegRsltFlag & NAS_MMC_WAIT_REG_RESULT_IND_PS))
    {
        return VOS_TRUE;
    }

    NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnSelection(NAS_MMC_WAIT_REG_RESULT_IND_IMS);

    /* IMS不可用时判断是否需要disable LTE */
    if (VOS_FALSE  == pstImsVoiceNtf->ucAvail)
    {
        if (VOS_TRUE == NAS_MMC_IsNeedDisableLte_ImsVoiceNotAvail())
        {
            NAS_MMC_SetCsRegAdditionalAction_PlmnSelection(NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION);

            NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS);

            NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE);
        }
    }

    /* L下A注册eps only成功被拒#16导致disable lte，到gu下无任何网络,回A网络注册被拒#16第一次就退状态机结果为成功，
      导致后续收到5次被拒又disable lte到gu下搜网，如此反复，需要判断如果additionalAction为reg attempt直接return*/
    /* 调用优先级比较表格得出CS/PS的处理优先级，并转换为状态机下一步行为 */
    enAdditionalAction   = NAS_MMC_GetPrioAddtionalAction(NAS_MMC_GetCsRegAdditionalAction_PlmnSelection(),
                                                          NAS_MMC_GetPsRegAdditionalAction_PlmnSelection());

    if (NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT == enAdditionalAction)
    {
        return VOS_TRUE;
    }

    /* 停定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

    /* disable lte原因不是MMC_LMM_DISABLE_LTE_REASON_LMM_NOTIFY_EUTRAN_NOT_ALLOW时，
       如果该网络在禁止接入技术网络中则删除 */
    if (MMC_LMM_DISABLE_LTE_REASON_LMM_NOTIFY_EUTRAN_NOT_ALLOW != NAS_MML_GetDisableLteReason())
    {
        stReCampLtePlmn.enRat    = NAS_MML_NET_RAT_TYPE_LTE;
        PS_MEM_CPY(&(stReCampLtePlmn.stPlmnId),
               NAS_MMC_GetCsPsMode1ReCampLtePlmn_PlmnSelection(),
               sizeof(stReCampLtePlmn.stPlmnId));
        NAS_MML_DeleteSpecDisabledPlmnWithValidPeriodInPlmnList(&stReCampLtePlmn);
    }

    if (VOS_FALSE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(enAdditionalAction))
    {
        /* 回复状态机退出成功 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_SUCC);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /*  如果存在信令连接，迁移到等待连接释放状态  */
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REL_IND_CSPSMODE1_RECAMP_LTE);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND, TI_NAS_MMC_WAIT_EPS_CONN_REL_IND_LEN);

        return VOS_TRUE;
    }

    /* 重新驻留LTE时将服务状态上报 */
    NAS_MMC_SndMsccServiceStatusInd(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_GetServiceStatusForMscc(NAS_MSCC_PIF_SRVDOMAIN_CS));
    NAS_MMC_SndMsccServiceStatusInd(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_GetServiceStatusForMscc(NAS_MSCC_PIF_SRVDOMAIN_PS));

    /* 回复状态机退出失败 */
    NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);

    if (VOS_TRUE == NAS_MML_GetSimPsRegStatus())
    {
        /* 清除Disable L全局变量标志 */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_REENABLE_NOTIFIED_AS);
    }

    /* 直接退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-7, end */

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitEpsRelIndCsPsMode1ReCampLte
 功能描述  : CS/PS mode 1重新驻留Lte模等待L链接释放的过程中收到退出状态机的请求
 输入参数  : ulEventType:消息类型
             pstMsg: 消息的首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息未完成
             VOS_TRUE:处理消息完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年7月2日
   作    者   : s46746
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitEpsRelIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ABORT_FSM_STRU             *pstAbortMsg = VOS_NULL_PTR;

    pstAbortMsg = (NAS_MMC_ABORT_FSM_STRU*)pstMsg;

    /* 若打断类型是用户请求的关机，则直接退出等链接释放结果状态机 */
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, begin*/
    if (NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_OFF_REQ) == pstAbortMsg->ulEventType)
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, end*/
    {
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND);

        /* 回复状态机退出成功 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 设置Abort标志, 等链接释放后进行quit */
    NAS_MMC_SetAbortFlag_PlmnSelection(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmMmcStatusInd_PlmnSelection_WaitEpsRelIndCsPsMode1ReCampLte
 功能描述  : CS/PS mode 1重新驻留Lte模等待L链接释放的过程中收到LMM上报的Status Ind消息
 输入参数  : ulEventType:消息类型
             pstMsg: 消息的首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息未完成
             VOS_TRUE:处理消息完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年7月2日
   作    者   : s46746
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmMmcStatusInd_PlmnSelection_WaitEpsRelIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_STATUS_IND_STRU            *pstLmmStatusIndMsg = VOS_NULL_PTR;

    pstLmmStatusIndMsg = (LMM_MMC_STATUS_IND_STRU*)pstMsg;

    /* 更新LMM的链接状态 */
    NAS_MML_UpdateEpsConnectionStatus(pstLmmStatusIndMsg->ulConnState);

    /*  如果存在信令连接，则继续等待  */
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        return VOS_TRUE;
    }

    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND);

    /* 是否需要 Abort状态机 */
    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection() )
    {
        /* 向上层状态机指示选网ABORT */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 重新驻留LTE时将服务状态上报 */
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, begin*/
    NAS_MMC_SndMsccServiceStatusInd(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_GetServiceStatusForMscc(NAS_MSCC_PIF_SRVDOMAIN_CS));
    NAS_MMC_SndMsccServiceStatusInd(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_GetServiceStatusForMscc(NAS_MSCC_PIF_SRVDOMAIN_PS));
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, end*/

    /* 回复状态机退出失败 */
    NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);

    if (VOS_TRUE == NAS_MML_GetSimPsRegStatus())
    {
        /* 清除Disable L全局变量标志 */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_REENABLE_NOTIFIED_AS);
    }

    /* 直接退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitEpsRelIndExpired_PlmnSelection_WaitEpsRelIndCsPsMode1ReCampLte
 功能描述  : CS/PS mode 1重新驻留Lte模等待L链接释放的过程中等待连接释放定时器超时的处理
 输入参数  : ulEventType:消息类型
             pstMsg: 消息的首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息未完成
             VOS_TRUE:处理消息完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年7月2日
   作    者   : s46746
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitEpsRelIndExpired_PlmnSelection_WaitEpsRelIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitEpsRelIndExpired_PlmnSelection_WaitEpsRelIndCsPsMode1ReCampLte ENTERED");

    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection() )
    {
        /* 回复状态机退出成功 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 重新驻留LTE时将服务状态上报 */
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, begin*/
    NAS_MMC_SndMsccServiceStatusInd(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_GetServiceStatusForMscc(NAS_MSCC_PIF_SRVDOMAIN_CS));
    NAS_MMC_SndMsccServiceStatusInd(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_GetServiceStatusForMscc(NAS_MSCC_PIF_SRVDOMAIN_PS));
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, end*/

    /* 回复状态机退出失败 */
    NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);

    if (VOS_TRUE == NAS_MML_GetSimPsRegStatus())
    {
        /* 清除Disable L全局变量标志 */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_REENABLE_NOTIFIED_AS);
    }

    /* 直接退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTafPlmnSpecialReq_PlmnSelection_WaitEpsRelIndCsPsMode1ReCampLte
 功能描述  : CS/PS mode 1重新驻留Lte模等待L链接释放的过程中MMC处理MSCC请求的指定搜网消息
 输入参数  : ulEventType:消息类型
             pstMsg: 消息的首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息未完成
             VOS_TRUE:处理消息完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年7月2日
   作    者   : s46746
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTafPlmnSpecialReq_PlmnSelection_WaitEpsRelIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, begin*/
    MSCC_MMC_PLMN_SPECIAL_REQ_STRU                          *pstUserSelReqMsg  = VOS_NULL_PTR;
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, end*/

    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSrchList   = VOS_NULL_PTR;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsRegCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enPsRegCause;

    /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, begin*/
    pstUserSelReqMsg    = (MSCC_MMC_PLMN_SPECIAL_REQ_STRU*)pstMsg;
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, end*/

    /* 保存用户指定搜网信息，更新当前的搜网类型为手动模式 */
    NAS_MMC_UpdateUserSpecPlmnSearchInfo_PlmnSelection((NAS_MML_PLMN_ID_STRU*)(&pstUserSelReqMsg->stPlmnId),
                                                        pstUserSelReqMsg->enAccessMode);

    /* 获取选网列表 */
    pstPlmnSrchList = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();

    /* 根据用户指定搜网场景重新初始化选网列表 */
    NAS_MMC_InitPlmnSelectionList(NAS_MMC_PLMN_SEARCH_SCENE_USER_SPEC_PLMN_SEARCH,
                                  VOS_NULL_PTR,
                                  pstPlmnSrchList);

    /* 将用户指定接入技术的网络(也是当前网络)更新为已搜索注册避免重复注册 */
    NAS_MMC_UpdatePlmnNetStatusInPlmnSelectionList(NAS_MMC_GetUserSpecPlmnId(),
                                                   NAS_MMC_NET_STATUS_SEARCHED_REGISTERED,
                                                   pstPlmnSrchList);

    enCsRegCause = NAS_MMC_GetCsRegCause_PlmnSelection();
    enPsRegCause = NAS_MMC_GetPsRegCause_PlmnSelection();

    if (VOS_TRUE == NAS_MMC_ProcUserSearchRegRslt_PlmnSelection(enCsRegCause, enPsRegCause))
    {
        return VOS_TRUE;
    }

    /* 保存入口消息 */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

    /* 状态迁移到NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_CONN_REL_IND);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTafSysCfgReq_PlmnSelection_WaitEpsRelIndCsPsMode1ReCampLte
 功能描述  : CS/PS mode 1重新驻留Lte模等待L链接释放的过程中MMC处理MSCC请求的SYSCFG设置消息
 输入参数  : ulEventType:消息类型
             pstMsg: 消息的首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息未完成
             VOS_TRUE:处理消息完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年7月2日
   作    者   : s46746
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTafSysCfgReq_PlmnSelection_WaitEpsRelIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 直接调起syscfg层二状态机 */
    NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_SYSCFG);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcSyscfgRsltCnf_PlmnSelection_WaitEpsRelIndCsPsMode1ReCampLte
 功能描述  : CS/PS mode 1重新驻留Lte模等待L链接释放的过程中处理SYSCFG状态机返回的结果
 输入参数  : ulEventType:消息类型
             pstMsg: 消息的首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息未完成
             VOS_TRUE:处理消息完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年7月2日
   作    者   : s46746
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmcSyscfgRsltCnf_PlmnSelection_WaitEpsRelIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 状态机中不需要对SYSCFG状态机结果进行处理，直接返回 */
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmMmcDetachInd_PlmnSelection_WaitEpsRelIndCsPsMode1ReCampLte
 功能描述  : CS/PS mode 1重新驻留Lte模等待L链接释放的过程中网侧detach的的处理
 输入参数  : ulEventType:消息类型
             pstMsg: 消息的首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息未完成
             VOS_TRUE:处理消息完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年7月2日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2013年1月11日
   作    者   : w00176964
   修改内容   : DTS2013010706662:调整发送EPLMN逻辑调用位置

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmMmcDetachInd_PlmnSelection_WaitEpsRelIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_DETACH_IND_STRU                                *pstDetachMsg = VOS_NULL_PTR;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsAdditionalAction;

    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, begin */
    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, end */

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));
    pstDetachMsg        = (LMM_MMC_DETACH_IND_STRU*)pstMsg;

    /* 处理DETACH消息，返回下一步动作 */
    NAS_MMC_ProcLmmDetachInd(pstDetachMsg, &enCsAdditionalAction, &enPsAdditionalAction);

    /*更新EPS的下一步的动作类型*/
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enPsAdditionalAction)
    {
        NAS_MMC_SetPsRegAdditionalAction_PlmnSelection(enPsAdditionalAction);
    }

    /*更新CS的下一步的动作类型*/
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enCsAdditionalAction)
    {
        NAS_MMC_SetCsRegAdditionalAction_PlmnSelection(enCsAdditionalAction);
    }

    if (VOS_TRUE == NAS_MMC_IsNeedSndEplmn_PlmnSelection())
    {
        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildSndLmmEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndLmmEquPlmnReq(&stSndEquPlmnInfo);
        NAS_MMC_SndOmEquPlmn();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmMmcDetachCnf_PlmnSelection_WaitEpsRelIndCsPsMode1ReCampLte
 功能描述  : CS/PS mode 1重新驻留Lte模等待L链接释放的过程中用户detach CNF的的处理
 输入参数  : ulEventType:消息类型
             pstMsg: 消息的首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息未完成
             VOS_TRUE:处理消息完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年7月2日
   作    者   : s46746
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmMmcDetachCnf_PlmnSelection_WaitEpsRelIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_DETACH_CNF_STRU            *pstDetachCnfMsg = VOS_NULL_PTR;

    pstDetachCnfMsg        = (LMM_MMC_DETACH_CNF_STRU*)pstMsg;

    /* 如果detach结果不是鉴权被拒，不需要进状态机，预处理中就可以处理 */
    if ( MMC_LMM_DETACH_RSLT_AUTH_REJ != pstDetachCnfMsg->ulDetachRslt)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmMmcDetachCnf_PlmnSelection_WaitEpsConnRelInd: Unexpected detach result!");

        return VOS_TRUE;
    }

    /*更新EPS的下一步的动作类型*/
    NAS_MMC_SetPsRegAdditionalAction_PlmnSelection(NAS_MMC_ADDITIONAL_ACTION_CSPS_ANYCELL);

    /*更新CS的下一步的动作类型*/
    NAS_MMC_SetCsRegAdditionalAction_PlmnSelection(NAS_MMC_ADDITIONAL_ACTION_CSPS_ANYCELL);

    return VOS_TRUE;
}


/* Added by s00246516 for L-C互操作项目, 2014-01-28, Begin */
/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLSysInfoInd_PlmnSelection_WaitMsccRegReq
 功能描述  : 等待MSCC注册请求过程中收到ID_LMM_MMC_SYS_INFO_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年1月28日
   作    者   : s00246516
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLSysInfoInd_PlmnSelection_WaitMsccRegReq(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_PLMN_WITH_RAT_STRU                              stPlmnId;
    LMM_MMC_SYS_INFO_IND_STRU                              *pstLmmSysInfoMsg    = VOS_NULL_PTR;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo    = VOS_NULL_PTR;

    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

    /* 解析系统消息中PLMNID，设置选网列表中该网络状态为存在 */
    pstLmmSysInfoMsg  = (LMM_MMC_SYS_INFO_IND_STRU*)pstMsg;
    NAS_MMC_ConvertLmmPlmnToGUNasFormat(&(pstLmmSysInfoMsg->stLteSysInfo.stSpecPlmnIdList.astSuitPlmnList[0]), &(stPlmnId.stPlmnId));

    stPlmnId.enRat           = NAS_MML_NET_RAT_TYPE_LTE;
    pstPlmnSelectionListInfo = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();
    NAS_MMC_UpdatePlmnNetStatusInPlmnSelectionList(&stPlmnId, NAS_MMC_NET_STATUS_SEARCHED_EXIST, pstPlmnSelectionListInfo);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmSuspendInd_PlmnSelection_WaitMsccRegReq
 功能描述  : 等待MSCC注册请求过程中收到ID_LMM_MMC_SUSPEND_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年1月28日
   作    者   : s00246516
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmSuspendInd_PlmnSelection_WaitMsccRegReq(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 该状态不允许进行异系统重选，回复LMM挂起失败 */
    NAS_MMC_SndLmmSuspendRsp(MMC_LMM_FAIL);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmAreaLostInd_PlmnSelection_WaitMsccRegReq
 功能描述  : 等待MSCC注册请求过程中收到ID_LMM_MMC_AREA_LOST_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年1月28日
   作    者   : s00246516
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmAreaLostInd_PlmnSelection_WaitMsccRegReq(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 设置接入层驻留状态为未驻留 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);

    return VOS_TRUE;
}
/* Added by s00246516 for L-C互操作项目, 2014-01-28, End */

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMsccCLAssociatedInfoNtf_PlmnSelection_WaitLmmPlmnSearchCnf
 功能描述  :等待L模上报搜网结果中收到ID_MSCC_MMC_CL_ASSOCIATED_INFO_NTF消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成

 修改历史     :
 1.日    期   : 2015年9月11日
   作    者   : y00346957
   修改内容   : DTS2015070910885 增加当前搜索的plmn是否允许搜的判断
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMsccCLAssociatedInfoNtf_PlmnSelection_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_PLMN_ID_STRU                stPlmnId;
    NAS_MML_PLMN_WITH_RAT_STRU         *pstPlmnWithRat;

    pstPlmnWithRat = NAS_MMC_GetCurrSearchingPlmn_PlmnSelection();
    stPlmnId.ulMcc = pstPlmnWithRat->stPlmnId.ulMcc;
    stPlmnId.ulMnc = pstPlmnWithRat->stPlmnId.ulMnc;

    if (VOS_FALSE == NAS_MMC_IsCurrLtePlmnAllowSrchInCLMode(&stPlmnId))
    {
        NAS_WARNING_LOG2(WUEPS_PID_MMC, "NAS_MMC_RcvMsccCLAssociatedInfoNtf_PlmnSelection_WaitLmmPlmnSearchCnf:WARNING: Current Lte Plmn is not Allowed Srch In CL Mode,ulMcc and ulMnc are",
                                             stPlmnId.ulMcc, stPlmnId.ulMnc);

        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF);

        /* 通知LMM停止搜网 */
        NAS_MMC_SndLmmPlmnSrchStopReq();

        /*迁移到等待停止搜网确认状态，启动保护定时器*/
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_STOP_CNF);

        NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF_LEN);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMsccLteSysPriClassInfoInd_PlmnSelection_WaitEpsRegRsltInd
 功能描述  :等待L模上报注册结果中收到ID_MSCC_MMC_MSPL_INFO_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成

 修改历史     :
 1.日    期   : 2015年9月11日
   作    者   : y00346957
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMsccCLAssociatedInfoNtf_PlmnSelection_WaitEpsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_PLMN_ID_STRU                stPlmnId;
    NAS_MML_PLMN_WITH_RAT_STRU         *pstPlmnWithRat;

    pstPlmnWithRat = NAS_MMC_GetCurrSearchingPlmn_PlmnSelection();
    stPlmnId.ulMcc = pstPlmnWithRat->stPlmnId.ulMcc;
    stPlmnId.ulMnc = pstPlmnWithRat->stPlmnId.ulMnc;

    if (VOS_TRUE == NAS_MMC_IsCurrLtePlmnAllowSrchInCLMode(&stPlmnId))
    {
        return VOS_TRUE;
    }

    NAS_WARNING_LOG2(WUEPS_PID_MMC, "NAS_MMC_RcvMsccCLAssociatedInfoNtf_PlmnSelection_WaitEpsRegRsltInd:WARNING: Current Lte Plmn is not Allowed Srch In CL Mode,ulMcc and ulMnc are",
                                         stPlmnId.ulMcc, stPlmnId.ulMnc);

    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
         /* 设置主动释放标志 */
        NAS_MMC_SetRelRequestFlag_PlmnSelection(VOS_TRUE);

        /* 主动请求释放链接 */
        NAS_MMC_SndLmmRelReq();

        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_CONN_REL_IND);
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND, TI_NAS_MMC_WAIT_EPS_CONN_REL_IND_LEN);

        return VOS_TRUE;
    }

    /* 搜下个plmn */
    NAS_MMC_SearchNextPlmn_PlmnSelection();

    return VOS_TRUE;
}
#endif


#endif  /* (FEATURE_ON == FEATURE_LTE) */

/*****************************************************************************
 函 数 名  : NAS_MMC_GetNextSearchPlmn_PlmnSelection
 功能描述  : 获取要选择的网络及其接入技术
 输入参数  : 无
 输出参数  : pstDestPlmn
 返 回 值  : VOS_UINT32 VOS_TRUE :获取成功
                        VOS_FALSE:获取失败

 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月11日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年11月09日
   作    者   : s00217060
   修改内容   : DTS2012102902559:SIM卡时设置成LTE only，不去掉L模，但此时搜网时不搜L模
 3.日    期   : 2012年12月27日
   作    者   : s00217060
   修改内容   : for DSDA GUNAS C CORE:如果USIM卡GSM禁止接入，则不选择GSM网络
 4.日    期   :2013年8月21日
   作    者   :z00161729
   修改内容   :DTS2013081607507:开机搜网过程中后台多次下发at+cops=0，mmc判断非正常服务不停打断当前搜网重新搜网导致开机速度慢
 5.日    期   : 2013年11月01日
   作    者   : l00208543
   修改内容   : 根据卡类型禁止网络制式
 6.日    期   : 2014年2月13日
   作    者   : s00246516
   修改内容   : L-C互操作项目:增加获取和注册请求的处理
 7.日    期   : 2015年5月26日
   作    者   : w00167002
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0项目修改   增加对HISTORY搜网的处理
*****************************************************************************/
VOS_UINT32 NAS_MMC_GetNextSearchPlmn_PlmnSelection(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstDestPlmn
)
{

    /* ========================== HISTORY搜网处理开始 ========================== */
    if (VOS_TRUE == NAS_MMC_IsNeedHistoryPlmnSearch_PlmnSelection())
    {
        /* 先找HISTORY搜的网络,找到了则进行HISTORY搜 */
        if (VOS_TRUE == NAS_MMC_GetNextHistorySearchPlmn_PlmnSelection(pstDestPlmn))
        {
            return VOS_TRUE;
        }
    }
    /* ========================== HISTORY搜网处理结束 ========================== */


    /* ========================== Pref Band搜网处理开始 ========================== */
    if (VOS_TRUE == NAS_MMC_IsNeedPrefBandPlmnSearch_PlmnSelection())
    {
        /* 先找Pref Band搜的网络,找到了则进行Pref Band搜 */
        if (VOS_TRUE == NAS_MMC_GetNextPrefBandSearchPlmn_PlmnSelection(pstDestPlmn))
        {
            return VOS_TRUE;
        }
    }

    /* ========================== Pref Band搜网处理结束 ========================== */

    if (VOS_TRUE == NAS_MMC_IsNeedSpecPlmnSearch_PlmnSelection())
    {
        /* 继续查找需要进行全BAND搜索的网络  */
        if (VOS_TRUE == NAS_MMC_GetNextSpecSearchPlmn_PlmnSelection(pstDestPlmn))
        {
            return VOS_TRUE;
        }
    }


    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetNextSearchPlmnFail_PlmnSelection
 功能描述  : 获取下一个要选择的网络失败处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年6月2日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年12月11日
   作    者   : l00167671
   修改内容   : DTS2012121802573, TQE清理
 3.日    期   : 2014年5月21日
   作    者   : w00167002
   修改内容   : DTS2014051602857:在SOR打开时候，如果CS注册失败达到4次，则等周期
                搜网定时器超时发起LIST搜网，如果当前仅有原有网络，则发起LAU,否则
                触发MM发起LAU;如果LIST搜后，发现有其他网络.指定搜网上报结束后更新
                选网类型，保持整个选网机制一致。
*****************************************************************************/
VOS_VOID NAS_MMC_GetNextSearchPlmnFail_PlmnSelection(VOS_VOID)
{
    NAS_MMC_FSM_ID_ENUM_UINT32          enCurrentFsmId;
    VOS_UINT32                          ulCurrentEventType;

    enCurrentFsmId     = NAS_MMC_GetCurrFsmId();
    if (NAS_MMC_FSM_PLMN_SELECTION != enCurrentFsmId)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }
    ulCurrentEventType = NAS_MMC_GetCurrFsmEventType();

    /* 如果是用户指定搜网，向上层回复搜网失败 */
    if (VOS_TRUE == NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enCurrentFsmId,ulCurrentEventType))
    {
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, begin*/
        NAS_MMC_SndMsccUserSpecPlmnSearchCnf(NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_FAIL);
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, end*/


        /*更新入口消息为普通的搜网请求，后续有新的用户请求时，可以打断该状态机*/
         NAS_MMC_SaveCommonPlmnSrchEntryMsg_PlmnSelection();

#if   (FEATURE_ON == FEATURE_LTE)
        /* 向LMM发送用户搜网结束通知 */
        if ( VOS_TRUE == NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_LTE))
        {

            NAS_MMC_SndLmmUserSpecPlmnSearchEndNotify();
        }
#endif
    }

#if   (FEATURE_ON == FEATURE_LTE)
    /* 判断是否需要重新驻留LTE网络 */
    if (VOS_TRUE == NAS_MMC_IsReCampLtePlmnValid_PlmnSelection())
    {
        NAS_MMC_ReCampLte_PlmnSelection();
    }
    else
#endif
    {
        /* 向上层状态机指示选网失败 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);

        /* 退出层二状态机 */
        NAS_MMC_FSM_QuitFsmL2();
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetNextHistorySearchPlmn_PlmnSelection
 功能描述  : 获取要选择的HISTORY搜索的网络及其接入技术
 输入参数  : 无
 输出参数  : pstDestPlmn
 返 回 值  : VOS_UINT32 VOS_TRUE :获取成功
                        VOS_FALSE:获取失败

 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年5月26日
   作    者   : w00167002
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0项目新增
*****************************************************************************/
VOS_UINT32 NAS_MMC_GetNextHistorySearchPlmn_PlmnSelection(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstDestPlmn
)
{
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionList = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList       = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU                              stPrioRatList;
    VOS_UINT32                                              i;
    VOS_UINT32                                              ulUserSpecPlmnSearch;
    NAS_MMC_FSM_ID_ENUM_UINT32                              enCurrentFsmId;
    VOS_UINT32                                              ulCurrentEventType;

    enCurrentFsmId       = NAS_MMC_GetCurrFsmId();

    if (enCurrentFsmId >= NAS_FSM_BUTT )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }

    ulCurrentEventType   = NAS_MMC_GetCurrFsmEventType();

    /* 获取是否用户指定搜网 */
    ulUserSpecPlmnSearch = NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enCurrentFsmId,ulCurrentEventType);

    /* 获取当前接入技术优先级信息 */
    pstPrioRatList = NAS_MML_GetMsPrioRatList();

    pstPlmnSelectionList = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();


    /* HISTORY搜索，需要删除当前已HISTORY搜索过的接入技术 */
    PS_MEM_SET(&stPrioRatList, 0X00, sizeof(stPrioRatList));

    for (i = 0 ; i < pstPrioRatList->ucRatNum; i++)
    {
        if (VOS_FALSE == NAS_MMC_GetHistorySearchedFlag_PlmnSelection(pstPrioRatList->aucRatPrio[i]))
        {
            stPrioRatList.aucRatPrio[stPrioRatList.ucRatNum] = pstPrioRatList->aucRatPrio[i];
            stPrioRatList.ucRatNum ++;
        }
    }

    /* 获取选网列表中排在最前面的状态为未搜索或者已搜索存在的网络 */
    if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn(pstDestPlmn, &stPrioRatList,
                                              ulUserSpecPlmnSearch, pstPlmnSelectionList))
    {
        NAS_MMC_SetCurrSearchingPlmn_PlmnSelection(pstDestPlmn);
        NAS_MMC_SetCurrSearchingType_PlmnSelection(NAS_MMC_PLMN_SEARCH_TYPE_HISTORY);

        /* 可维可测 */
        NAS_MMC_LogFsmPlmnSelectionCtxRelatedInfo(NAS_MMC_GetPlmnSelectionCtx_PlmnSelection());

        return VOS_TRUE;
    }

    /* 没找到下一个HISTORY搜的网络，返回VOS_FALSE */
    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetNextPrefBandSearchPlmn_PlmnSelection
 功能描述  : 获取下一个需要pref band搜的网络
 输入参数  : NAS_MML_PLMN_WITH_RAT_STRU         *pstDestPlmn
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月10日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_GetNextPrefBandSearchPlmn_PlmnSelection(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstDestPlmn
)
{
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionList = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList       = VOS_NULL_PTR;
    VOS_UINT32                                              i;
    VOS_UINT32                                              ulUserSpecPlmnSearch;
    NAS_MMC_FSM_ID_ENUM_UINT32                              enCurrentFsmId;
    VOS_UINT32                                              ulCurrentEventType;
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;

    NAS_MML_SIM_TYPE_ENUM_UINT8                             enSimType;
#endif


    enCurrentFsmId       = NAS_MMC_GetCurrFsmId();
    if (enCurrentFsmId >= NAS_FSM_BUTT )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }
    ulCurrentEventType   = NAS_MMC_GetCurrFsmEventType();

    /* 获取是否用户指定搜网 */
    ulUserSpecPlmnSearch = NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enCurrentFsmId,ulCurrentEventType);

    /* 获取当前接入技术优先级信息 */
    pstPrioRatList = NAS_MML_GetMsPrioRatList();

    pstPlmnSelectionList = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();

    /* 获取选网列表中排在最前面的状态为未搜索或者已搜索存在的网络 */
    if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn(pstDestPlmn, pstPrioRatList,
                                              ulUserSpecPlmnSearch, pstPlmnSelectionList))
    {
        NAS_MMC_SetCurrSearchingPlmn_PlmnSelection(pstDestPlmn);

        NAS_MMC_SetCurrSearchingType_PlmnSelection(NAS_MMC_PLMN_SEARCH_TYPE_PREFBAND);

        return VOS_TRUE;
    }

    /* 如果当前为自动选网 */
    if (VOS_TRUE == NAS_MMC_IsNeedSearchAvailPlmn_PlmnSelection())
    {
        /* 按SYSCFG设置的接入技术优先级判断是否有某个接入技术未进行全频搜网，
           如果有，返回VOS_TRUE,输出该接入技术的全F无效网络,指示接入层搜索,
           接入层搜索失败时会进行一次全频搜网 */
        for (i = 0; i < pstPrioRatList->ucRatNum; i++)
        {
            /* 增加判断，如果RAT被禁止的话，不需要搜RAT */
            if (VOS_TRUE == NAS_MML_IsRatInForbiddenList(pstPrioRatList->aucRatPrio[i]))
            {
                continue;
            }

#if (FEATURE_ON == FEATURE_LTE)
            enSimType = NAS_MML_GetSimType();

            /* 获取LTE能力状态 */
            enLCapabilityStatus = NAS_MML_GetLteCapabilityStatus();

            /* 满足如下条件,则不需要搜索LTE的网络:
                1)当前网络的接入技术为L且当前PS域卡无效
                2)当前网络的接入技术为L且当前DISABLE LTE
                3)卡类型为SIM卡:对应的场景为:SIM卡时设置成LTE only，不去掉L模，但此时搜网时不搜L模
            */
            if (((VOS_FALSE                             == NAS_MML_GetSimPsRegStatus())
              || ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == enLCapabilityStatus)
               || (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS == enLCapabilityStatus))
              ||(NAS_MML_SIM_TYPE_SIM == enSimType))
             && (NAS_MML_NET_RAT_TYPE_LTE == pstPrioRatList->aucRatPrio[i]))
            {
                continue;
            }
#endif
            /* 如果USIM卡GSM禁止接入，则不选择GSM网络 */
            if ( (VOS_TRUE == NAS_MML_GetGsmForbidFlg())
              && (NAS_MML_NET_RAT_TYPE_GSM == pstPrioRatList->aucRatPrio[i]) )
            {
                continue;
            }

            /* 依次查找所有支持的接入技术 */
            if (VOS_FALSE == NAS_MMC_GetAllBandSearch_PlmnSelection(pstPrioRatList->aucRatPrio[i]))
            {
                pstDestPlmn->stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
                pstDestPlmn->stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
                pstDestPlmn->enRat          = pstPrioRatList->aucRatPrio[i];

                NAS_MMC_SetCurrSearchingPlmn_PlmnSelection(pstDestPlmn);

                NAS_MMC_SetCurrSearchingType_PlmnSelection(NAS_MMC_PLMN_SEARCH_TYPE_PREFBAND);

                return VOS_TRUE;
            }
        }
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_GetNextSpecSearchPlmn_PlmnSelection
 功能描述  : 获取要选择的全频段指定搜的网络及其接入技术
 输入参数  : 无
 输出参数  : pstDestPlmn
 返 回 值  : VOS_UINT32 VOS_TRUE :获取成功
                        VOS_FALSE:获取失败

 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月11日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年11月09日
   作    者   : s00217060
   修改内容   : DTS2012102902559:SIM卡时设置成LTE only，不去掉L模，但此时搜网时不搜L模
 3.日    期   : 2012年12月27日
   作    者   : s00217060
   修改内容   : for DSDA GUNAS C CORE:如果USIM卡GSM禁止接入，则不选择GSM网络
 4.日    期   :2013年8月21日
   作    者   :z00161729
   修改内容   :DTS2013081607507:开机搜网过程中后台多次下发at+cops=0，mmc判断非正常服务不停打断当前搜网重新搜网导致开机速度慢
 5.日    期   : 2013年11月01日
   作    者   : l00208543
   修改内容   : 根据卡类型禁止网络制式
 6.日    期   : 2014年2月13日
   作    者   : s00246516
   修改内容   : L-C互操作项目:增加获取和注册请求的处理
 7.日    期   : 2015年5月26日
   作    者   : w00167002
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0项目修改，封装获取要搜索的全BAND指定搜网络的处理
*****************************************************************************/
VOS_UINT32 NAS_MMC_GetNextSpecSearchPlmn_PlmnSelection(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstDestPlmn
)
{
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionList = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList       = VOS_NULL_PTR;
    VOS_UINT32                                              i;
    VOS_UINT32                                              ulUserSpecPlmnSearch;
    NAS_MMC_FSM_ID_ENUM_UINT32                              enCurrentFsmId;
    VOS_UINT32                                              ulCurrentEventType;
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;

    NAS_MML_SIM_TYPE_ENUM_UINT8                             enSimType;
#endif


    NAS_MML_PLMN_ID_STRU                                    stPlmnId;

    PS_MEM_SET(&stPlmnId, 0x00, sizeof(NAS_MML_PLMN_ID_STRU));

    enCurrentFsmId       = NAS_MMC_GetCurrFsmId();
    if (enCurrentFsmId >= NAS_FSM_BUTT )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }
    ulCurrentEventType   = NAS_MMC_GetCurrFsmEventType();

    /* 获取是否用户指定搜网 */
    ulUserSpecPlmnSearch = NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enCurrentFsmId,ulCurrentEventType);

    /* 获取当前接入技术优先级信息 */
    pstPrioRatList = NAS_MML_GetMsPrioRatList();

    pstPlmnSelectionList = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();

    /* 获取选网列表中排在最前面的状态为未搜索或者已搜索存在的网络 */
    if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn(pstDestPlmn, pstPrioRatList,
                                              ulUserSpecPlmnSearch, pstPlmnSelectionList))
    {
        NAS_MMC_SetCurrSearchingPlmn_PlmnSelection(pstDestPlmn);

        NAS_MMC_SetCurrSearchingType_PlmnSelection(NAS_MMC_PLMN_SEARCH_TYPE_SPEC);

        return VOS_TRUE;
    }

    /* 如果当前为自动选网 */
    /* Modified by s00246516 for L-C互操作项目, 2014-01-28, Begin */
    if (VOS_TRUE == NAS_MMC_IsNeedSearchAvailPlmn_PlmnSelection())
    /* Modified by s00246516 for L-C互操作项目, 2014-01-28, End */
    {
        /* 按SYSCFG设置的接入技术优先级判断是否有某个接入技术未进行全频搜网，
           如果有，返回VOS_TRUE,输出该接入技术的全F无效网络,指示接入层搜索,
           接入层搜索失败时会进行一次全频搜网 */
        for (i = 0; i < pstPrioRatList->ucRatNum; i++)
        {
            /* 增加判断，如果RAT被禁止的话，不需要搜RAT */
            if (VOS_TRUE == NAS_MML_IsRatInForbiddenList(pstPrioRatList->aucRatPrio[i]))
            {
                continue;
            }

#if (FEATURE_ON == FEATURE_LTE)
            enSimType = NAS_MML_GetSimType();

            /* 获取LTE能力状态 */
            enLCapabilityStatus = NAS_MML_GetLteCapabilityStatus();

            /* 满足如下条件,则不需要搜索LTE的网络:
                1)当前网络的接入技术为L且当前PS域卡无效
                2)当前网络的接入技术为L且当前DISABLE LTE
                3)卡类型为SIM卡:对应的场景为:SIM卡时设置成LTE only，不去掉L模，但此时搜网时不搜L模
            */
            if (((VOS_FALSE                             == NAS_MML_GetSimPsRegStatus())
              || ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == enLCapabilityStatus)
               || (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS == enLCapabilityStatus))
              ||(NAS_MML_SIM_TYPE_SIM == enSimType))
             && (NAS_MML_NET_RAT_TYPE_LTE == pstPrioRatList->aucRatPrio[i]))
            {
                continue;
            }
#endif
            /* 如果USIM卡GSM禁止接入，则不选择GSM网络 */
            if ( (VOS_TRUE == NAS_MML_GetGsmForbidFlg())
              && (NAS_MML_NET_RAT_TYPE_GSM == pstPrioRatList->aucRatPrio[i]) )
            {
                continue;
            }

            /* 依次查找所有支持的接入技术 */
            if (VOS_FALSE == NAS_MMC_GetAllBandSearch_PlmnSelection(pstPrioRatList->aucRatPrio[i]))
            {
                pstDestPlmn->stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
                pstDestPlmn->stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
                pstDestPlmn->enRat          = pstPrioRatList->aucRatPrio[i];

                stPlmnId.ulMcc  = pstDestPlmn->stPlmnId.ulMcc;
                stPlmnId.ulMnc  = pstDestPlmn->stPlmnId.ulMnc;

                /* 全频搜全f的lte网络时，在cl模式下，根据cl关联信息，如果lte网络不允许搜索，直接返回 */
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
                if (VOS_FALSE == NAS_MMC_IsCurrLtePlmnAllowSrchInCLMode(&stPlmnId))
                {
                    NAS_WARNING_LOG2(WUEPS_PID_MMC, "NAS_MMC_GetNextSpecSearchPlmn_PlmnSelection:WARNING: Current Lte Plmn is not Allowed Srch In CL Mode,ulMcc and ulMnc are",
                                                         pstDestPlmn->stPlmnId.ulMcc, pstDestPlmn->stPlmnId.ulMnc);

                    return VOS_FALSE;
                }
#endif
                NAS_MMC_SetCurrSearchingPlmn_PlmnSelection(pstDestPlmn);


                NAS_MMC_SetCurrSearchingType_PlmnSelection(NAS_MMC_PLMN_SEARCH_TYPE_SPEC);

                return VOS_TRUE;
            }
        }
    }

    return VOS_FALSE;
}




/*****************************************************************************
 函 数 名  : NAS_MMC_ProcNoRf_PlmnSelection
 功能描述  : 搜网失败原因为NO RF
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年1月22日
   作    者   : w00167002
   修改内容   : 新生成函数
                在选网状态机下，如果当前搜网失败原因为NO RF,则退出选网状态机，按照
                出服务区进行处理。

 2.日    期   : 2013年3月29日
   作    者   : y00176023
   修改内容   : DSDS GUNAS II项目:NO RF情况下向RRM发起注册，只考虑GU不考虑LTE搜网产生的NO RF

 3.日    期   : 2014年5月21日
   作    者   : w00167002
   修改内容   : DTS2014051602857:在SOR打开时候，如果CS注册失败达到4次，则等周期
                搜网定时器超时发起LIST搜网，如果当前仅有原有网络，则发起LAU,否则
                触发MM发起LAU;如果LIST搜后，发现有其他网络.指定搜网上报结束后更新
                选网类型，保持整个选网机制一致。

 4.日    期   : 2014年6月28日
   作    者   : b00269685
   修改内容   : DSDS GUNAS III项目修改
 5.日    期   : 2015年05月26日
   作    者   : l00305157
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0
*****************************************************************************/
VOS_VOID NAS_MMC_ProcNoRf_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNasRat
)
{
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionList     = VOS_NULL_PTR;

    pstPlmnSelectionList = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();

    /* NO RF失败，需保存当前的选网状态机列表信息 */
    NAS_MMC_SetPlmnSelectionListType(NAS_MMC_BACKUP_PLMN_SELECTION_LIST);
    PS_MEM_CPY(NAS_MMC_GetHighPrioPlmnList(), pstPlmnSelectionList, sizeof(NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU));


    /* 增加存储各模式下HISTORY搜索的信息，以便于RF 资源可用后，继续进行HISTORY搜索 */
    NAS_MMC_BackupNoRfHistorySearchedInfo_PlmnSelection();

    /* 可维可测，输出选网列表信息 */
    NAS_MMC_LogPlmnSelectionList(pstPlmnSelectionList);

    /* 设置NO RF存在标记信息 */
    NAS_MML_SetCurrRatRfAvailFlg(enNasRat, VOS_FALSE);

    /* 向RRM发送注册消息 此处可能重复通知RRMM同一个RAT的NO RF,RRM保证能处理 */
    NAS_MMC_RegisterRrmResourceNtf(enNasRat, RRM_PS_TASK_TYPE_NAS_SEARCH);

    /* 向MSCC通知当前NO RF信息 */
    NAS_MMC_SndMsccRfAvailInd(VOS_FALSE);

    /* 向上层状态机指示选网失败,按照丢网处理:启动AVAILABLE定时器 */
    NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);

    /* 退出层二状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcNoRfAreaLost_PlmnSelection
 功能描述  : 选网状态机中收到area lost NO RF
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年7月4日
   作    者   : b00269685
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_ProcNoRfAreaLost_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNasRat
)
{
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionList     = VOS_NULL_PTR;

    pstPlmnSelectionList = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();

    /* NO RF失败，需保存当前的选网状态机列表信息 */
    NAS_MMC_SetPlmnSelectionListType(NAS_MMC_BACKUP_PLMN_SELECTION_LIST);
    PS_MEM_CPY(NAS_MMC_GetHighPrioPlmnList(), pstPlmnSelectionList, sizeof(NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU));

    /* 可维可测，输出选网列表信息 */
    NAS_MMC_LogPlmnSelectionList(pstPlmnSelectionList);

    /* 向上层状态机指示选网失败,按照丢网处理:启动AVAILABLE定时器 */
    NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);

    /* 退出层二状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_MMC_SndLmmSpecPlmnSearchReq_PlmnSelection
 功能描述  : 向LMM发送搜网请求消息
 输入参数  : pstDestPlmn    - 搜网plmn id
             ulUserSpecFlag - 用户指定搜网标识
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年12月25日
   作    者   : z00161729
   修改内容   : SVLTE支持NCELL搜网
 2.日    期   : 2014年1月26日
   作    者   : z00161729
   修改内容   : DTS2014012305088：支持增强NCELL搜网，如果Modem1传递过来的邻区信息不存在的情况下，通过历史频点支持NCELL搜索。
 3.日    期   : 2014年3月19日
   作    者   : w00242748
   修改内容   : DTS2014031200137:当NV特性打开时，自动开机或者搜网时，如果首次搜索RPLMN的话，
                需要将HPLMN/EHPLMN带给接入层。
 4.日    期   : 2014年2月14日
   作    者   : s00246516
   修改内容   : L-C互操作项目:增加获取和注册请求的处理
 5.日    期   : 2015年5月26日
   作    者   : w00167002
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0项目修改 增加对HISTORY搜的处理
 6.日    期   : 2015年10月28日
   作    者   : s00217060
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0:新增pref band搜的处理

*****************************************************************************/
VOS_VOID NAS_MMC_SndLmmSpecPlmnSearchReq_PlmnSelection(
    NAS_MML_PLMN_LIST_WITH_RAT_STRU    *pstDestPlmnList,
    VOS_UINT32                          ulUserSpecFlag
)
{
    NAS_MMC_NCELL_SEARCH_INFO_STRU                         *pstNcellSearchInfo = VOS_NULL_PTR;
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene;
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstDestPlmn = VOS_NULL_PTR;

    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(stSndEquPlmnInfo));

    pstNcellSearchInfo = NAS_MMC_GetNcellSearchInfo();
    enPlmnSearchScene  = NAS_MMC_GetPlmnSearchScene_PlmnSelection();

    pstDestPlmn = &(pstDestPlmnList->astPlmnId[0]);

    /* Modified by s00246516 for L-C互操作项目, 2014-02-14, Begin */
    /* ncell搜网场景 */
    if ((VOS_TRUE == NAS_MMC_IsInterPlmnSearch_PlmnSelection())
     && ((NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED_NCELL_SEARCH == enPlmnSearchScene)
      || (NAS_MMC_PLMN_SEARCH_SCENE_REG_NCELL == enPlmnSearchScene)))
    {
        if (NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED_NCELL_SEARCH == enPlmnSearchScene)
        {
            /* 构造ncell搜网等效plmn网络为modem1的等效plmn+modem0等效EHPLMN+modem0的RPLMN */
            NAS_MMC_BuildNcellPlmnSearchEquPlmnInfo_PlmnSelection(&stSndEquPlmnInfo, pstDestPlmn->enRat);
        }
        else
        {
            stSndEquPlmnInfo.ucEquPlmnNum = NAS_MML_MIN(NAS_MML_MAX_EQUPLMN_NUM, pstNcellSearchInfo->stOtherModemEplmnInfo.ucEquPlmnNum);
            PS_MEM_CPY(stSndEquPlmnInfo.astEquPlmnAddr, pstNcellSearchInfo->stOtherModemEplmnInfo.astEquPlmnAddr,
                       (stSndEquPlmnInfo.ucEquPlmnNum*sizeof(NAS_MML_PLMN_ID_STRU)));
        }

        /* 删除禁止网络 */
        NAS_MMC_BuildSndLmmEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndLmmNcellSpecPlmnSearchReq(&pstNcellSearchInfo->stLteNcellInfo,
                                     &stSndEquPlmnInfo);

    }
    /* Modified by s00246516 for L-C互操作项目, 2014-02-14, End */
    else if ( NAS_MMC_PLMN_SEARCH_TYPE_HISTORY == NAS_MMC_GetCurrSearchingType_PlmnSelection())
    {
        /* 通知L进行历史频点指点搜 */
        NAS_MMC_SndLmmHistoryPlmnSearchReq(pstDestPlmnList);
    }
    else if ( NAS_MMC_PLMN_SEARCH_TYPE_PREFBAND == NAS_MMC_GetCurrSearchingType_PlmnSelection())
    {
        /* 通知L进行pref band搜 */
        NAS_MMC_SndLmmPrefBandPlmnSearchReq(pstDestPlmnList, ulUserSpecFlag);
    }
    else
    {
        NAS_MMC_SndLmmSpecPlmnSearchReq(pstDestPlmnList, ulUserSpecFlag, enPlmnSearchScene);
    }

}

#endif

/*****************************************************************************
 函 数 名  : NAS_MMC_BuildNcellPlmnSearchEquPlmnInfo_PlmnSelection
 功能描述  : 构造ncell搜网时通知接入层的等效plmn信息
 输入参数  : pstOutEplmnInfo - 等效plmn信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年1月26日
   作    者   : z00161729
   修改内容   : DTS2014012305088：支持增强NCELL搜网，如果Modem1传递过来的邻区信息不存在的情况下，
                通过历史频点支持NCELL搜索,ncell搜索时带的eplmn为modem1等效plmn+modem0等效EHPLMN+modem0的RPLMN
 2.日    期   : 2014年2月19日
   作    者   : s00217060
   修改内容   : coverity清理
 3.日    期   : 2014年03月05日
   作    者   : z00161729
   修改内容   : DTS2014030304758：ncell搜网携带的等效plmn信息顺序优化，modem0 rplmn放在ehplmn前面，防止ehplmn过长导致等效plmn 超过最大个数16使rplmn无法加入
*****************************************************************************/
VOS_VOID NAS_MMC_BuildNcellPlmnSearchEquPlmnInfo_PlmnSelection(
    NAS_MML_EQUPLMN_INFO_STRU          *pstOutEplmnInfo,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType
)
{
    MSCC_MMC_PLMN_ID_STRU                astEquPlmnAddr[NAS_MSCC_PIF_MAX_EQUPLMN_NUM];
    NAS_MMC_NCELL_SEARCH_INFO_STRU     *pstNcellSearchInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulIndex;
    VOS_UINT8                           ucSndEplmnNum;
    NAS_MML_PLMN_ID_STRU                stRPlmnId;
    VOS_UINT32                          ulRplmnExistFlg;
    NAS_MML_SIM_EHPLMN_INFO_STRU       *pstSimEHPlmnInfo = VOS_NULL_PTR;

    PS_MEM_SET(astEquPlmnAddr, 0, sizeof(astEquPlmnAddr));
    PS_MEM_SET(&stRPlmnId, 0, sizeof(stRPlmnId));
    ucSndEplmnNum      = 0;
    ulIndex            = 0;
    pstSimEHPlmnInfo   = NAS_MML_GetSimEhplmnList();
    ulRplmnExistFlg    = VOS_FALSE;
    pstNcellSearchInfo = NAS_MMC_GetNcellSearchInfo();

    /* Modified by s00217060 for coverity清理, 2014-02-19, begin */
    if (NAS_MML_MAX_EQUPLMN_NUM < pstNcellSearchInfo->stOtherModemEplmnInfo.ucEquPlmnNum)
    {
        pstNcellSearchInfo->stOtherModemEplmnInfo.ucEquPlmnNum  = NAS_MML_MAX_EQUPLMN_NUM;

        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_BuildNcellPlmnSearchEquPlmnInfo_PlmnSelection:other modem eplmn num incorrect!");

    }

    /* 等效plmn信息中加入modem1的等效plmn信息 */
    for (ulIndex = 0; ulIndex < pstNcellSearchInfo->stOtherModemEplmnInfo.ucEquPlmnNum; ulIndex++)
    {


        astEquPlmnAddr[ucSndEplmnNum].ulMcc = pstNcellSearchInfo->stOtherModemEplmnInfo.astEquPlmnAddr[ulIndex].ulMcc;
        astEquPlmnAddr[ucSndEplmnNum].ulMnc = pstNcellSearchInfo->stOtherModemEplmnInfo.astEquPlmnAddr[ulIndex].ulMnc;
        ucSndEplmnNum++;
    }

    /* 等效plmn信息中加入modem0的RPLMN信息 */
#if (FEATURE_ON == FEATURE_LTE)
    if (NAS_MML_NET_RAT_TYPE_LTE == enRatType)
    {
        ulRplmnExistFlg = NAS_MML_GetLteRPlmn(&stRPlmnId);
    }
    else
#endif
    {
        ulRplmnExistFlg = NAS_MML_GetGURPlmn(&stRPlmnId);
    }

    if ((VOS_TRUE == ulRplmnExistFlg)
     && (ucSndEplmnNum < NAS_MSCC_PIF_MAX_EQUPLMN_NUM))
    {
        astEquPlmnAddr[ucSndEplmnNum].ulMcc = stRPlmnId.ulMcc;
        astEquPlmnAddr[ucSndEplmnNum].ulMnc = stRPlmnId.ulMnc;
        ucSndEplmnNum++;
    }

    if (NAS_MML_MAX_EHPLMN_NUM < pstSimEHPlmnInfo->ucEhPlmnNum)
    {
        pstSimEHPlmnInfo->ucEhPlmnNum   = NAS_MML_MAX_EHPLMN_NUM;

        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_BuildNcellPlmnSearchEquPlmnInfo_PlmnSelection:other modem ehplmn num incorrect!");
    }
    /* Modified by s00217060 for coverity清理, 2014-02-19, end */

    /* 等效plmn信息中加入modem0的EHPLMN信息 */
    for (ulIndex = 0; ulIndex < pstSimEHPlmnInfo->ucEhPlmnNum; ulIndex++)
    {
        if (ucSndEplmnNum >= NAS_MSCC_PIF_MAX_EQUPLMN_NUM)
        {
            pstOutEplmnInfo->ucEquPlmnNum = ucSndEplmnNum;
            PS_MEM_CPY(pstOutEplmnInfo->astEquPlmnAddr, astEquPlmnAddr, sizeof(pstOutEplmnInfo->astEquPlmnAddr));
            return;
        }

        astEquPlmnAddr[ucSndEplmnNum].ulMcc = pstSimEHPlmnInfo->astEhPlmnInfo[ulIndex].stPlmnId.ulMcc;
        astEquPlmnAddr[ucSndEplmnNum].ulMnc = pstSimEHPlmnInfo->astEhPlmnInfo[ulIndex].stPlmnId.ulMnc;
        ucSndEplmnNum++;
    }

    pstOutEplmnInfo->ucEquPlmnNum = ucSndEplmnNum;
    PS_MEM_CPY(pstOutEplmnInfo->astEquPlmnAddr, astEquPlmnAddr, sizeof(pstOutEplmnInfo->astEquPlmnAddr));

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_SndAsSpecPlmnSearchReq_PlmnSelection
 功能描述  : 向AS发送搜网请求消息
 输入参数  : pstDestPlmn    - 搜网plmn id
             ulUserSpecFlag - 用户指定搜网标识
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年12月25日
   作    者   : z00161729
   修改内容   : SVLTE支持NCELL搜网
 2.日    期   : 2014年1月26日
   作    者   : z00161729
   修改内容   : DTS2014012305088：支持增强NCELL搜网，如果Modem1传递过来的邻区信息不存在的情况下，
                通过历史频点支持NCELL搜索,ncell搜索时带的eplmn为modem1等效plmn+modem0等效EHPLMN+modem0的RPLMN
 3.日    期   : 2014年3月19日
   作    者   : w00242748
   修改内容   : DTS2014031200137:当NV特性打开时，自动开机或者搜网时，如果首次搜索RPLMN的话，
                需要将HPLMN/EHPLMN带给接入层。
 4.日    期   : 2015年10月28日
   作    者   : s00217060
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0:新增pref band搜的处理
*****************************************************************************/
VOS_VOID NAS_MMC_SndAsSpecPlmnSearchReq_PlmnSelection(
    NAS_MML_PLMN_LIST_WITH_RAT_STRU                        *pstDestPlmnList,
    NAS_MML_FORBIDPLMN_ROAMING_LAS_INFO_STRU               *pstForbRoamLaInfo
)
{
    NAS_MMC_NCELL_SEARCH_INFO_STRU                         *pstNcellSearchInfo = VOS_NULL_PTR;
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene;
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstDestPlmn = VOS_NULL_PTR;

    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(stSndEquPlmnInfo));

    pstNcellSearchInfo = NAS_MMC_GetNcellSearchInfo();
    enPlmnSearchScene  = NAS_MMC_GetPlmnSearchScene_PlmnSelection();
    pstDestPlmn        = &(pstDestPlmnList->astPlmnId[0]);

    if ((VOS_TRUE == NAS_MMC_IsInterPlmnSearch_PlmnSelection())
     && (NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED_NCELL_SEARCH == enPlmnSearchScene))
    {
        /* 构造ncell搜网等效plmn网络为modem1的等效plmn+modem0等效EHPLMN+modem0的RPLMN */
        NAS_MMC_BuildNcellPlmnSearchEquPlmnInfo_PlmnSelection(&stSndEquPlmnInfo, pstDestPlmn->enRat);

        /* 删除禁止网络 */
        NAS_MMC_BuildEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndAsNcellSpecPlmnSearchReq(&pstNcellSearchInfo->stTdsNcellInfo,
                                            &stSndEquPlmnInfo);
    }
    /* 判断当前需要进行HISTORY搜索，则通知接入层进行HISTORY搜 */
    else if ( NAS_MMC_PLMN_SEARCH_TYPE_HISTORY == NAS_MMC_GetCurrSearchingType_PlmnSelection() )
    {
        NAS_MMC_SndAsHistoryPlmnSearchReq(pstDestPlmnList, pstForbRoamLaInfo);
    }
    else if ( NAS_MMC_PLMN_SEARCH_TYPE_PREFBAND == NAS_MMC_GetCurrSearchingType_PlmnSelection() )
    {
        NAS_MMC_SndAsPrefBandPlmnSearchReq(pstDestPlmnList, pstForbRoamLaInfo);
    }
    else
    {
        NAS_MMC_SndAsSpecPlmnSearchReq(pstDestPlmnList, pstForbRoamLaInfo);
    }


}


/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedAddEplmnInDestPlmnList_PlmnSelection
 功能描述  : 判断是否需要将EHPLMN/HPLMN加入目的搜网列表
 输入参数  : pstDestPlmn    - 搜网plmn id

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年3月21日
   作    者   : w00242748
   修改内容   : 新建函数
 2.日    期   : 2014年11月19日
   作    者   : s00217060
   修改内容   : DTS2014111002343:available timer超时触发搜网时带EHPLMN/HPLMN
 3.日    期   : 2/4/2015
   作    者   : W00176964
   修改内容   : CDMA Iteration 10 Modfied
 4.日    期   : 2015年6月5日
   作    者   : s00217060
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0修改

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedAddEhplmnWhenSearchRplmn_PlmnSelection(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstDestPlmn
)
{
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene;
    NAS_MMC_PLMN_TYPE_ENUM_UINT8                            enPlmnType;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionList = VOS_NULL_PTR;
    VOS_UINT32                                              ulEventType;
    VOS_UINT8                                               ucSearchRplmnAndHplmnFlg;
    NAS_MMC_ENTRY_MSG_STRU                                 *pstEntryMsg    = VOS_NULL_PTR;
    MSCC_MMC_PLMN_SEARCH_REQ_STRU                          *pstMsccPlmnSearchReq = VOS_NULL_PTR;

    /* 根据FSM ID获取该FSM 入口消息 */
    pstEntryMsg              = NAS_MMC_GetCurrFsmMsgAddr();
    pstMsccPlmnSearchReq     = (MSCC_MMC_PLMN_SEARCH_REQ_STRU *)pstEntryMsg->aucEntryMsgBuffer;

    enPlmnSearchScene                = NAS_MMC_GetPlmnSearchScene_PlmnSelection();
    pstPlmnSelectionList             = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();
    enPlmnType                       = NAS_MMC_GetPlmnTypeInPlmnSelectionList(pstDestPlmn, pstPlmnSelectionList);
    ulEventType                      = NAS_MMC_GetCurrFsmEventType();
    ucSearchRplmnAndHplmnFlg         = NAS_MMC_GetSearchRplmnAndHplmnFlg_PlmnSelection(pstDestPlmn->enRat);

    /* 手动搜网模式或8464 NV特性关闭时，不带EHPLMN/HPLMN */
    if (VOS_FALSE == NAS_MMC_IsRPlmnFirstSearchWithHPlmn())
    {
        return VOS_FALSE;
    }

    /* 目标网络不是RPLMN时，不带EHPLMN/HPLMN */
    if (NAS_MMC_PLMN_TYPE_RPLMN != enPlmnType)
    {
        return VOS_FALSE;
    }

    /* 该接入技术下搜RPLMN时已经带过EHPLMN/HPLMN，退状态机前下次再去该接入技术下搜的时候不带EHPLMN/HPLMN */
    if (VOS_TRUE == ucSearchRplmnAndHplmnFlg)
    {
        return VOS_FALSE;
    }

    /* 上电第一次开机搜网时带EHPLMN/HPLMN */
    if ((ulEventType                      == NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_SEARCH_REQ))
     && (NAS_MSCC_PIF_ACQ_REASON_POWER_UP == pstMsccPlmnSearchReq->enAcqReason))
    {
        return VOS_TRUE;
    }

    /* 丢网之后触发搜网时带EHPLMN/HPLMN */
    if (NAS_MMC_PLMN_SEARCH_SCENE_AREA_LOST == enPlmnSearchScene)
    {
        return VOS_TRUE;
    }

    /* available timer超时触发搜网时带EHPLMN/HPLMN */
    if (NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED == enPlmnSearchScene)
    {
        return VOS_TRUE;
    }

    /* available timer超时触发history搜网时带EHPLMN/HPLMN */
    if (NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED_HISTORY_PLMN_SEARCH == enPlmnSearchScene)
    {
        return VOS_TRUE;
    }


    return VOS_FALSE;
}




/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedAddEhplmnWhenSearchHplmn_PlmnSelection
 功能描述  : 判断是否需要将EHPLMN/HPLMN加入目的搜网列表
 输入参数  : pstDestPlmn    - 搜网plmn id

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期   : 2015年9月30日
    作    者   : c00318887
    修改内容   : 新建函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedAddEhplmnWhenSearchHplmn_PlmnSelection(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstDestPlmn
)
{
    NAS_MMC_PLMN_TYPE_ENUM_UINT8                            enPlmnType;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionList = VOS_NULL_PTR;
    NAS_MML_HPLMN_CFG_INFO_STRU                            *pstHplmnCfgInfo      = VOS_NULL_PTR;
    VOS_UINT8                                               ucSearchRplmnAndHplmnFlg;


    pstHplmnCfgInfo                     = NAS_MML_GetHplmnCfg();
    pstPlmnSelectionList                = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();
    enPlmnType                          = NAS_MMC_GetPlmnTypeInPlmnSelectionList(pstDestPlmn, pstPlmnSelectionList);
    ucSearchRplmnAndHplmnFlg            = NAS_MMC_GetSearchRplmnAndHplmnFlg_PlmnSelection(pstDestPlmn->enRat);

    /* NV特性关闭时，不带EHPLMN/HPLMN */
    if (VOS_FALSE == pstHplmnCfgInfo->ucAddEhplmnWhenSrchHplmnFlg)
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsNeedAddEhplmnWhenSearchHplmn_PlmnSelection(): ucAddEhplmnWhenSrchHplmnFlg is false");
        return VOS_FALSE;
    }

    /* 该接入技术下搜RPLMN时已经带过EHPLMN/HPLMN，不带EHPLMN/HPLMN */
    if (VOS_TRUE == ucSearchRplmnAndHplmnFlg)
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsNeedAddEhplmnWhenSearchHplmn_PlmnSelection(): ucSearchRplmnAndHplmnFlg is true");

        return VOS_FALSE;
    }

    /* 测试卡时，不带EHPLMN/HPLMN */
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsNeedAddEhplmnWhenSearchHplmn_PlmnSelection(): is test card");
        return VOS_FALSE;
    }

    /* 目标网络不是HPLMN时，不带EHPLMN/HPLMN */
    if (NAS_MMC_PLMN_TYPE_HPLMN != enPlmnType)
    {
        NAS_NORMAL_LOG1(WUEPS_PID_MMC, "NAS_MMC_IsNeedAddEhplmnWhenSearchHplmn_PlmnSelection(): PlmnType isnot home:", enPlmnType);
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetNoSearchedEhplmn_PlmnSelection
 功能描述  : 获取网络状态是没搜索过的EHPLMN 列表
 输入参数  :
 输出参数  : pstDestEHPlmnInfo    - 没搜索过的EHPLMN 列表
 返 回 值  : VOS_VOID

 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年9月30日
   作    者   : c00318887
   修改内容   : 新建函数 : DTS2015091700173

*****************************************************************************/
VOS_VOID NAS_MMC_GetNoSearchedEhplmn_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat,
    NAS_MML_SIM_EHPLMN_INFO_STRU       *pstDestEHPlmnInfo
)
{
    NAS_MML_SIM_EHPLMN_INFO_STRU                           *pstEHPlmnInfo        = VOS_NULL_PTR;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionList = VOS_NULL_PTR;
    NAS_MMC_NET_STATUS_ENUM_UINT8                           enNetStatus;
    NAS_MML_PLMN_WITH_RAT_STRU                              stPlmnWithRat;
    VOS_UINT16                                              usConvertedSimRat;
    VOS_UINT8                                               ucLoop;
    VOS_UINT8                                               ucIndex             = 0;

    /* 获取EHPLMN */
    pstEHPlmnInfo                                           = NAS_MML_GetSimEhplmnList();
    pstPlmnSelectionList                                    = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();
    usConvertedSimRat                                       = NAS_MMC_ConvertNetRatToSimRat(enCurRat);

    pstDestEHPlmnInfo->enPLMNSelInd                         = pstEHPlmnInfo->enPLMNSelInd;
    pstDestEHPlmnInfo->enEHplmnPresentInd                   = pstEHPlmnInfo->enEHplmnPresentInd;
    pstDestEHPlmnInfo->enHplmnType                          = pstEHPlmnInfo->enHplmnType;

    PS_MEM_SET(&stPlmnWithRat, 0x0, sizeof(stPlmnWithRat));

    for (ucLoop = 0; ucLoop < NAS_MML_MIN(pstEHPlmnInfo->ucEhPlmnNum, NAS_MML_MAX_EHPLMN_NUM); ucLoop++)
    {
        /* Ehplmn的接入技术不支持当前接入技术 */
        if (usConvertedSimRat != (usConvertedSimRat & pstEHPlmnInfo->astEhPlmnInfo[ucLoop].usSimRat))
        {
            continue;
        }

        stPlmnWithRat.stPlmnId.ulMcc    = pstEHPlmnInfo->astEhPlmnInfo[ucLoop].stPlmnId.ulMcc;
        stPlmnWithRat.stPlmnId.ulMnc    = pstEHPlmnInfo->astEhPlmnInfo[ucLoop].stPlmnId.ulMnc;
        stPlmnWithRat.enRat             = enCurRat;

        enNetStatus                     = NAS_MMC_GetSpecPlmnWithRatNetStatusInPlmnSelectionList(
                                                            &stPlmnWithRat,
                                                            pstPlmnSelectionList);

        if ( (NAS_MMC_NET_STATUS_NO_SEARCHED    == enNetStatus)
          || (NAS_MMC_NET_STATUS_SEARCHED_EXIST == enNetStatus) )
        {
            PS_MEM_CPY(&pstDestEHPlmnInfo->astEhPlmnInfo[ucIndex++],
                            &pstEHPlmnInfo->astEhPlmnInfo[ucLoop],
                            sizeof(NAS_MML_SIM_PLMN_WITH_RAT_STRU));
        }

    }
    pstDestEHPlmnInfo->ucEhPlmnNum          = ucIndex;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_GetSpecSceneSrchRplmnCarryEplmnFlag
 功能描述  : 获取指定场景搜RPLMN是否需要携带EPLMN的标志
 输入参数  : enPlmnSearchScene搜网场景
             bIsRoam 是否漫游
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年8月13日
   作    者   : l00289540
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 NAS_MMC_GetSpecSceneSrchRplmnCarryEplmnFlag_PlmnSelection(
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32 enPlmnSearchScene,
    VOS_UINT8                             ucIsRoam
)
{
    NAS_MML_CARRY_EPLMN_WHEN_SRCH_RPLMN_CFG_STRU *pstCarryEplmnWhenSrchRplmnCfg;
    VOS_UINT8                                     ucRetVal;

    pstCarryEplmnWhenSrchRplmnCfg = NAS_MML_GetCarryEplmnWhenSrchRplmnCfg();

    /* 测试卡保护 */
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        return VOS_FALSE;
    }

    /* 此优化开关关闭的场景 */
    if (NAS_MML_CARRY_EPLMN_SWITCH_OFF == pstCarryEplmnWhenSrchRplmnCfg->enSwitchFlag)
    {
        return VOS_FALSE;
    }

    /* 此优化只在漫游场景下生效，而此时处于非漫游场景下 */
    if ((NAS_MML_CARRY_EPLMN_SWITCH_ON_FOR_ROAM == pstCarryEplmnWhenSrchRplmnCfg->enSwitchFlag)
     && (VOS_FALSE == ucIsRoam))
    {
        return VOS_FALSE;
    }

    /* 优化在漫游打开并且此时是漫游场景，或者优化在漫游非漫游都打开，则根据场景配置来确定是否打开优化 */
    switch(enPlmnSearchScene)
    {
    case NAS_MMC_PLMN_SEARCH_SCENE_SWITCH_ON:
        ucRetVal = pstCarryEplmnWhenSrchRplmnCfg->ucCarryEplmnSceneSwitchOn;
        break;

    case NAS_MMC_PLMN_SEARCH_SCENE_AREA_LOST:
        ucRetVal = pstCarryEplmnWhenSrchRplmnCfg->ucCarryEplmnSceneAreaLost;
        break;

    case NAS_MMC_PLMN_SEARCH_SCENE_SYSCFG_SET:
        ucRetVal = pstCarryEplmnWhenSrchRplmnCfg->ucCarryEplmnSceneSysCfgSet;
        break;

    case NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED:
    case NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED_HISTORY_PLMN_SEARCH:
    case NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED_PREFBAND_PLMN_SEARCH:
        ucRetVal = pstCarryEplmnWhenSrchRplmnCfg->ucCarryEplmnSceneAvailableTimerExpired;
        break;

    case NAS_MMC_PLMN_SEARCH_SCENE_DISABLE_LTE:
        ucRetVal = pstCarryEplmnWhenSrchRplmnCfg->ucCarryEplmnSceneDisableLte;
        break;

    case NAS_MMC_PLMN_SEARCH_SCENE_CSFB_SERVIEC_REJ:
        ucRetVal = pstCarryEplmnWhenSrchRplmnCfg->ucCarryEplmnSceneCSFBServiceRej;
        break;

    case NAS_MMC_PLMN_SEARCH_SCENE_ENABLE_LTE_PLMN_SEARCH:
        ucRetVal = pstCarryEplmnWhenSrchRplmnCfg->ucCarryEplmnSceneEnableLte;
        break;

    default:
        ucRetVal = VOS_FALSE;
        break;
    }

    return ucRetVal;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedAddEplmnWhenSearchRplmn_PlmnSelection
 功能描述  : 判断是否需要将EPLMN加入目的搜网列表
 输入参数  : pstDestPlmn    - 搜网plmn id
 输出参数  : 无
 返 回 值  : VOS_TRUE:需要将EPLMN加入目的搜网列表
             VOS_FALSE:不需要将EPLMN加入目的搜网列表
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年9月9日
   作    者   : z00161729
   修改内容   : 新建函数
 2.日    期   : 2015年8月13日
   作    者   : l00289540
   修改内容   : User_Exp_Improve修改

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedAddEplmnWhenSearchRplmn_PlmnSelection(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstDestPlmn
)
{
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene;
    NAS_MMC_PLMN_TYPE_ENUM_UINT8                            enPlmnType;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionList = VOS_NULL_PTR;
    VOS_UINT8                                               ucSearchRplmnAndEplmnFlg;
    VOS_UINT8                                               ucIsRoam;

    enPlmnSearchScene                = NAS_MMC_GetPlmnSearchScene_PlmnSelection();
    pstPlmnSelectionList             = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();
    enPlmnType                       = NAS_MMC_GetPlmnTypeInPlmnSelectionList(pstDestPlmn, pstPlmnSelectionList);
    ucSearchRplmnAndEplmnFlg         = NAS_MMC_GetSearchRplmnAndEplmnFlg_PlmnSelection(pstDestPlmn->enRat);

    ucIsRoam = VOS_FALSE;

    if (VOS_FALSE == NAS_MML_ComparePlmnIdWithHplmn(&pstDestPlmn->stPlmnId))
    {
        ucIsRoam = VOS_TRUE;
    }

    /* csfb搜网到gu场景，搜rplmn时需要携带eplmn信息增加搜网速度 */
    if ( (NAS_MMC_PLMN_TYPE_RPLMN == enPlmnType)
      && (VOS_FALSE == ucSearchRplmnAndEplmnFlg))
    {
        if  ((NAS_MMC_PLMN_SEARCH_SCENE_CSFB_SERVIEC_REJ == enPlmnSearchScene)
          && (NAS_MML_NET_RAT_TYPE_LTE != pstDestPlmn->enRat))
        {
            return VOS_TRUE;
        }

        if (VOS_TRUE == NAS_MMC_GetSpecSceneSrchRplmnCarryEplmnFlag_PlmnSelection(enPlmnSearchScene, ucIsRoam))
        {
            return VOS_TRUE;
        }

    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedAddDplmnOfSameCountryWhenSearchDPlmn_PlmnSelection
 功能描述  : 判断是否需要将DPLMN加入目的搜网列表
 输入参数  : pstDestPlmn    - 搜网plmn id
 输出参数  : 无
 返 回 值  : VOS_TRUE:需要将DPLMN加入目的搜网列表
             VOS_FALSE:不需要将DPLMN加入目的搜网列表
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月24日
    作    者   : l00289540
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_IsNeedAddDplmnOfSameCountryWhenSearchDPlmn_PlmnSelection(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstDestPlmn
)
{
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU            *pstDplmnNplmnCfgInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU                   *pstPrioRatList       = VOS_NULL_PTR;

    /* 获取当前接入技术优先级信息 */
    pstPrioRatList                      = NAS_MML_GetMsPrioRatList();
    pstDplmnNplmnCfgInfo                = NAS_MMC_GetDPlmnNPlmnCfgInfo();

    /* 漫游搜网优化定制关闭不处理 */
    if (VOS_FALSE == NAS_MMC_GetRoamPlmnSelectionSortActiveFlg())
    {
        return VOS_FALSE;
    }

    /* 手动模式，不处理 */
    if (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == NAS_MMC_GetPlmnSelectionMode())
    {
        return VOS_FALSE;
    }

    /* 当前没有进行漫游排序，则不处理 */
    if (VOS_FALSE == NAS_MMC_IsSpecRatListRoamSorted_PlmnSelection(pstPrioRatList))
    {
        return VOS_FALSE;
    }

    /* 目标网络不是DPLMN时，不处理 */
    if (VOS_FALSE == NAS_MMC_IsPlmnIdWithRatInSimPlmnWithRegDomainList(pstDestPlmn,
                           pstDplmnNplmnCfgInfo->usDplmnListNum, pstDplmnNplmnCfgInfo->astDPlmnList))
    {
        return VOS_FALSE;
    }

    /* 漫游搜网按照UPLMN->OPLMN->DPLMN->AVAILABLE的顺序执行的特性打开 */
    if (VOS_TRUE == NAS_MMC_GetSrchUOplmnPriorToDplmnFlg())
    {
        /* 目标网络是UPLMN时，不处理 */
        if (VOS_TRUE == NAS_MMC_ComparePlmnIdWithRatWithUplmn(pstDestPlmn))
        {
            return VOS_FALSE;
        }

        /* 目标网络是OPLMN时，不处理 */
        if (VOS_TRUE == NAS_MMC_ComparePlmnIdWithRatWithOplmn(pstDestPlmn))
        {
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedHistoryPlmnSearch_PlmnSelection
 功能描述  : 判断是否需要进行HISTROY搜索
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:需要进行HISTORY搜网
            VOS_FALSE:不需要进行HISTORY搜网
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年5月26日
   作    者   : w00167002
   修改内容   : 新建函数
 2.日    期   : 2015年5月21日
   作    者   : l00305157
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0
 3.日    期   : 2015年8月11日
   作    者   : z00161729
   修改内容   : DTS2015061609419：L下被拒搜网场景优化，先history搜再全频搜
 4.日    期   : 2015年12月11日
   作    者   : w00176964
   修改内容   : CL_MUTIMODE_OPTIMIZE调整
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedHistoryPlmnSearch_PlmnSelection(VOS_VOID)
{
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList       = VOS_NULL_PTR;
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene;
    VOS_UINT8                                               ucIsOosPLmnSearchScene;
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    NAS_MMC_PLMN_SEARCH_TYPE_ENUM_UINT32                    enSrchType;

    enSrchType = NAS_MMC_PLMN_SEARCH_TYPE_SPEC;

    if (VOS_TRUE == NAS_MMC_GetMsccTriggerPlmnSrchTypeInClMode_PlmnSelection(&enSrchType))
    {
        if (NAS_MMC_PLMN_SEARCH_TYPE_HISTORY == enSrchType)
        {
            return VOS_TRUE;
        }

        return VOS_FALSE;
    }
#endif

    /* 获取当前接入技术优先级信息 */
    pstPrioRatList = NAS_MML_GetMsPrioRatList();

    enPlmnSearchScene                   = NAS_MMC_GetPlmnSearchScene_PlmnSelection();

    if (NAS_MMC_PLMN_SEARCH_SCENE_RF_ENABLE == enPlmnSearchScene)
    {
        enPlmnSearchScene               = NAS_MMC_GetBackUpNoRfPlmnSearchScene_PlmnSelection();
    }

    if (VOS_FALSE == NAS_MMC_IsSpecSearchSceneInNeedHistorySearchSceneTbl(enPlmnSearchScene))
    {
        return VOS_FALSE;
    }

    ucIsOosPLmnSearchScene  = NAS_MMC_IsOosPlmnSearchScene(enPlmnSearchScene);

    /* 非OOS搜网场景时，检查history特性是否打开 */
    if ((VOS_FALSE == NAS_MMC_GetNonOosSceneHistorySearchActiveFlg())
     && (VOS_FALSE == ucIsOosPLmnSearchScene))
    {
        return VOS_FALSE;
    }

    /* OOS场景，该阶段history次数为0无需history搜 */
    if ((VOS_FALSE == NAS_MMC_IsHistorySearchSupportInCurrPhase())
     && (VOS_TRUE  == ucIsOosPLmnSearchScene))
    {
        return VOS_FALSE;
    }

    /* 如果是NAS_MMC_PLMN_SEARCH_SCENE_CSFB_SERVIEC_REJ搜网场景无需history搜L */
    if ((VOS_TRUE == NAS_MML_GetCmServiceSetupFlg())
     || (NAS_MMC_PLMN_SEARCH_SCENE_CSFB_SERVIEC_REJ == enPlmnSearchScene))
    {
        NAS_MMC_SetHistorySearchedFlag_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE, VOS_TRUE);
    }

    /* 当前各接入技术下都已HISTORY搜索过，则不需要HISTORY搜索 */
    if (VOS_TRUE == NAS_MMC_IsSpecRatListAllHistorySearched_PlmnSelection(pstPrioRatList))
    {
        return VOS_FALSE;
    }

    /* 当前进行了出国漫游排序，则优先搜索排序后的国外网络，不再HISTORY搜索 */
    if (VOS_TRUE == NAS_MMC_IsSpecRatListRoamSorted_PlmnSelection(pstPrioRatList) )
    {
        return VOS_FALSE;
    }

    /* 需要进行HISTORY搜索 */
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedPrefBandPlmnSearch_PlmnSelection
 功能描述  : 判断是否需要进行pref band搜索
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:需要进行pref band搜网
            VOS_FALSE:不需要进行pref band搜网
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年10月10日
   作    者   : s00217060
   修改内容   : 新生成函数
 2.日    期   : 2015年12月11日
   作    者   : w00176964
   修改内容   : CL_MUTIMODE_OPTIMIZE调整
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedPrefBandPlmnSearch_PlmnSelection(VOS_VOID)
{
    VOS_UINT8                                               ucIsOosPLmnSearchScene;
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene;
    NAS_MMC_NON_OOS_PLMN_SEARCH_FEATURE_SUPPORT_CFG_STRU   *pstNonOosCfg  = VOS_NULL_PTR;
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    NAS_MMC_PLMN_SEARCH_TYPE_ENUM_UINT32                    enSrchType;

    enSrchType = NAS_MMC_PLMN_SEARCH_TYPE_SPEC;

    if (VOS_TRUE == NAS_MMC_GetMsccTriggerPlmnSrchTypeInClMode_PlmnSelection(&enSrchType))
    {
        if (NAS_MMC_PLMN_SEARCH_TYPE_PREFBAND == enSrchType)
        {
            return VOS_TRUE;
        }

        return VOS_FALSE;
    }
#endif

    pstNonOosCfg        = NAS_MMC_GetNonOosPlmnSearchFeatureSupportCfg();
    enPlmnSearchScene   = NAS_MMC_GetPlmnSearchScene_PlmnSelection();

    if (NAS_MMC_PLMN_SEARCH_SCENE_RF_ENABLE == enPlmnSearchScene)
    {
        enPlmnSearchScene               = NAS_MMC_GetBackUpNoRfPlmnSearchScene_PlmnSelection();
    }

    /* 是否为pref band搜网场景 */
    if (VOS_FALSE == NAS_MMC_IsSpecSearchSceneInNeedPrefBandSearchSceneTbl(enPlmnSearchScene))
    {
        return VOS_FALSE;
    }

    ucIsOosPLmnSearchScene  = NAS_MMC_IsOosPlmnSearchScene(enPlmnSearchScene);

    /* 非OOS搜网场景时，检查prefband特性是否打开 */
    if ((VOS_FALSE == pstNonOosCfg->ucPrefBandActiveFlg)
     && (VOS_FALSE == ucIsOosPLmnSearchScene))
    {
        return VOS_FALSE;
    }

    /* area lost时需要根据NV判断是要pref band搜还是spec搜 */
    if ((NAS_MMC_PLMN_SEARCH_SCENE_AREA_LOST == enPlmnSearchScene)
     && (NAS_MMC_PLMN_SEARCH_TYPE_AFTER_HISTORY_PREF_BAND != pstNonOosCfg->enSearchTypeAfterHistoryInAreaLostScene))
    {
        return VOS_FALSE;
    }

    /* 需要进行pref band搜索 */
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedSpecPlmnSearch_PlmnSelection
 功能描述  : 是否进行spec搜索
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月28日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2015年12月11日
    作    者   : w00176964
    修改内容   : CL_MUTIMODE_OPTIMIZE调整

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedSpecPlmnSearch_PlmnSelection(VOS_VOID)
{
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene;
    NAS_MMC_NON_OOS_PLMN_SEARCH_FEATURE_SUPPORT_CFG_STRU   *pstNonOosCfg  = VOS_NULL_PTR;
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    NAS_MMC_PLMN_SEARCH_TYPE_ENUM_UINT32                    enSrchType;

    enSrchType = NAS_MMC_PLMN_SEARCH_TYPE_SPEC;

    if (VOS_TRUE == NAS_MMC_GetMsccTriggerPlmnSrchTypeInClMode_PlmnSelection(&enSrchType))
    {
        if (NAS_MMC_PLMN_SEARCH_TYPE_SPEC == enSrchType)
        {
            return VOS_TRUE;
        }

        return VOS_FALSE;
    }
#endif

    pstNonOosCfg        = NAS_MMC_GetNonOosPlmnSearchFeatureSupportCfg();
    enPlmnSearchScene   = NAS_MMC_GetPlmnSearchScene_PlmnSelection();

    if (NAS_MMC_PLMN_SEARCH_SCENE_RF_ENABLE == enPlmnSearchScene)
    {
        enPlmnSearchScene               = NAS_MMC_GetBackUpNoRfPlmnSearchScene_PlmnSelection();
    }

    /* 找不到HISTORY网络，如果只需要进行HISTORY搜，则不需要找下一个网络 */
    if (NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED_HISTORY_PLMN_SEARCH == enPlmnSearchScene)
    {
        return VOS_FALSE;
    }

    /* available超时之后，如果本次搜网只需要进行Pref Band搜，则不需要找下一个网络 */
    if (NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED_PREFBAND_PLMN_SEARCH == enPlmnSearchScene)
    {
        return VOS_FALSE;
    }

    /* area lost时需要根据NV判断是要pref band搜还是spec搜 */
    if ((NAS_MMC_PLMN_SEARCH_SCENE_AREA_LOST == enPlmnSearchScene)
     && (NAS_MMC_PLMN_SEARCH_TYPE_AFTER_HISTORY_SPEC != pstNonOosCfg->enSearchTypeAfterHistoryInAreaLostScene))
    {
        return VOS_FALSE;
    }

    /* 需要进行spec搜索 */
    return VOS_TRUE;
}


/* Modified by c00318887 for DPlmn扩容和优先接入HPLMN, 2015-5-18, begin */
/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedAddHplmnWhenSeachDplmn_PlmnSelection
 功能描述  : 判断是否需要将EPLMN加入目的搜网列表
 输入参数  : pstDestPlmn    - 搜网plmn id
 输出参数  : 无
 返 回 值  : VOS_TRUE:需要将EPLMN加入目的搜网列表
             VOS_FALSE:不需要将EPLMN加入目的搜网列表
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年5月18日
   作    者   : c00318887
   修改内容   : 新建函数
 2.日    期   : 2015年7月30日
   作    者   : c00318887
   修改内容   : 增加ROAM_PLMN_SELECTION_OPTIMIZE_2.0 处理

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedAddEhplmnWhenSeachDplmn_PlmnSelection(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstDestPlmn
)
{
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDplmnNplmnCfgInfo = VOS_NULL_PTR;
    VOS_UINT8                                               ucSearchDplmnAndHplmnFlg;

    /* Modified by  for c00318887 for DPlmn扩容和优先接入HPLMN, 2015-7-30, begin */
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList       = VOS_NULL_PTR;

    /* 获取当前接入技术优先级信息 */
    pstPrioRatList                      = NAS_MML_GetMsPrioRatList();
    pstDplmnNplmnCfgInfo                = NAS_MMC_GetDPlmnNPlmnCfgInfo();
    ucSearchDplmnAndHplmnFlg            = NAS_MMC_GetSearchDplmnAndHplmnFlg_PlmnSelection(pstDestPlmn->enRat);

    /* 漫游搜网优化定制关闭不处理 */
    if (VOS_FALSE == NAS_MMC_GetRoamPlmnSelectionSortActiveFlg())
    {
        return VOS_FALSE;
    }



    /* 当前没有进行漫游排序，则不处理 */
    if (VOS_FALSE == NAS_MMC_IsSpecRatListRoamSorted_PlmnSelection(pstPrioRatList) )
    {
        return VOS_FALSE;
    }


    /* 目标网络不是DPLMN时，不带EHPLMN/HPLMN */
    if (VOS_FALSE == NAS_MMC_IsPlmnIdWithRatInSimPlmnWithRegDomainList(pstDestPlmn,
                           pstDplmnNplmnCfgInfo->usDplmnListNum, pstDplmnNplmnCfgInfo->astDPlmnList))
    {
        return VOS_FALSE;
    }


    /* 自动模式，携带HPLMN */
    if ( (NAS_MMC_PLMN_SELECTION_MODE_AUTO == NAS_MMC_GetPlmnSelectionMode())
      && (VOS_FALSE == ucSearchDplmnAndHplmnFlg))
    {
        return VOS_TRUE;
    }
    /* Modified by  for c00318887 for DPlmn扩容和优先接入HPLMN, 2015-7-30, end */

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedAddHplmnWhenSeachDplmn_PlmnSelection
 功能描述  : 根据需要将EPLMN/hplmn加入目的搜网列表
 输入参数  : pstDestPlmn    - 搜网plmn id
 输出参数  : pstDestPlmnList --增加 EPLMN/hplmn 后的搜网列表
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年7月30日
   作    者   : c00318887
   修改内容   : 新建函数
 2.日    期   : 2015年9月30日
   作    者   : c00318887
   修改内容   : DTS2015091700173
*****************************************************************************/
VOS_VOID NAS_MMC_BuildDestPlmnListWhenSearchPlmn_PlmnSelection(
    NAS_MML_PLMN_LIST_WITH_RAT_STRU     *pstDestPlmnList,
    NAS_MML_PLMN_WITH_RAT_STRU          *pstDestPlmn
)
{
    NAS_MML_SIM_EHPLMN_INFO_STRU        stEHPlmnInfo;

    if ( VOS_TRUE == NAS_MMC_IsNeedAddEhplmnWhenSearchRplmn_PlmnSelection(pstDestPlmn) )
    {
        NAS_MMC_AddEHPlmnInDestPlmnList(pstDestPlmnList, NAS_MML_GetSimEhplmnList());


        /* 在HISTORY时候不设置搜索过，后续可以继续全频段指定搜 */
        if ( NAS_MMC_PLMN_SEARCH_TYPE_HISTORY != NAS_MMC_GetCurrSearchingType_PlmnSelection())
        {
            NAS_MMC_SetSearchRplmnAndHplmnFlg_PlmnSelection(pstDestPlmn->enRat, VOS_TRUE);
        }
    }
    /* Modified by c00318887 for DPlmn扩容和优先接入HPLMN, 2015-5-18, begin */
    else if (VOS_TRUE == NAS_MMC_IsNeedAddEhplmnWhenSeachDplmn_PlmnSelection(pstDestPlmn))
    {
        NAS_MMC_AddEHPlmnInDestPlmnList(pstDestPlmnList, NAS_MML_GetSimEhplmnList());

        if ( NAS_MMC_PLMN_SEARCH_TYPE_HISTORY != NAS_MMC_GetCurrSearchingType_PlmnSelection())
        {
            NAS_MMC_SetSearchDplmnAndHplmnFlg_PlmnSelection(pstDestPlmn->enRat, VOS_TRUE);
        }
    }
    else if ( VOS_TRUE == NAS_MMC_IsNeedAddEhplmnWhenSearchHplmn_PlmnSelection(pstDestPlmn) )
    {
        PS_MEM_SET(&stEHPlmnInfo, 0x0, sizeof(NAS_MML_SIM_EHPLMN_INFO_STRU));

        NAS_MMC_GetNoSearchedEhplmn_PlmnSelection(pstDestPlmn->enRat, &stEHPlmnInfo);

        NAS_MMC_AddEHPlmnInDestPlmnList(pstDestPlmnList, &stEHPlmnInfo);

        if ( NAS_MMC_PLMN_SEARCH_TYPE_HISTORY != NAS_MMC_GetCurrSearchingType_PlmnSelection())
        {
            NAS_MMC_SetSearchRplmnAndHplmnFlg_PlmnSelection(pstDestPlmn->enRat, VOS_TRUE);
        }

    }
    else
    {
    }
    /* Modified by c00318887 for DPlmn扩容和优先接入HPLMN, 2015-5-18, end */


    if (VOS_TRUE == NAS_MMC_IsNeedAddEplmnWhenSearchRplmn_PlmnSelection(pstDestPlmn))
    {
        NAS_MMC_AddEPlmnInDestPlmnList(pstDestPlmnList);

        if ( NAS_MMC_PLMN_SEARCH_TYPE_HISTORY != NAS_MMC_GetCurrSearchingType_PlmnSelection())
        {
            NAS_MMC_SetSearchRplmnAndEplmnFlg_PlmnSelection(pstDestPlmn->enRat, VOS_TRUE);
        }
    }

    if (VOS_TRUE == NAS_MMC_IsNeedAddDplmnOfSameCountryWhenSearchDPlmn_PlmnSelection(pstDestPlmn))
    {
        NAS_MMC_AddDplmnInDestPlmnList(pstDestPlmn, pstDestPlmnList);
    }
}

/* Modified by c00318887 for DPlmn扩容和优先接入HPLMN, 2015-5-18, end */

/*****************************************************************************
 函 数 名  : NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection
 功能描述  : 向接入层或者LMM发送搜网请求消息
 输入参数  : stDestPlmn
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月11日
   作    者   : s46746
   修改内容   : 新生成函数

 2.日    期   : 2011年11月11日
   作    者   : w00167002
   修改内容   : DTS2011110907180:将禁止漫游位置区信息作为参数传递进来，向
                接入层发送此FORB ROAM LAS即可
 3.日    期   : 2011年12月15日
   作    者   : W00166186
   修改内容   : dts2011111502641,L下PLMN加入禁止TA后不再搜网
 4.日    期   : 2012年3月17日
   作    者   : w00176964
   修改内容   : DTS2012031900095 V7R1 C30 SBM&EM定制需求:增加LTE国家漫游功能定制
 5.日    期   : 2012年12月11日
   作    者   : l00167671
   修改内容   : DTS2012121802573, TQE清理
 6.日    期   : 2013年1月15日
   作    者   : s00217060
   修改内容   : for DSDA GUNAS C CORE:等待WAS的搜网回复定时器长度封装成函数
 7.日    期   : 2013年01月23日
   作    者   : s00217060
   修改内容   : 问题单: DTS2013012106172,Enable Lte时停止定时器TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER
 8.日    期   : 2013年11月01日
   作    者   : l00208543
   修改内容   : 根据卡类型禁止网络制式
 9.日    期   : 2013年12月25日
   作    者   : z00161729
   修改内容   : SVLTE支持NCELL搜网
10.日    期   : 2014年3月19日
   作    者   : w00242748
   修改内容   : DTS2014031200137:当NV特性打开时，自动开机或者搜网时，如果首次搜索RPLMN的话，
                需要将HPLMN/EHPLMN带给接入层。
11.日    期   : 2014年1月28日
   作    者   : s00246516
   修改内容   : L-C互操作项目:增加获取和注册请求的处理
12.日    期   : 2014年9月9日
   作    者   : z00161729
   修改内容   : DTS2014082807343:csfb搜网到gu后mmc搜网请求需带rplmn+eplmn，否则存在搜网慢T303超时呼叫失败场景
13.日    期   : 2015年1月5日
   作    者   : z00161729
   修改内容   : AT&T 支持DAM特性修改

13.日    期   : 2015年02月11日
   作    者   : w00167002
   修改内容   : DTS2015021000324:当前在DSDS双卡中，GSM下搜网可能不回NAS 搜网NO RF,那么
                NAS搜网定时器超时，则上报无服务了。修改为延长NAS定时器时长。
14.日    期   : 2015年6月17日
   作    者   : w00167002
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0,在HISTORY搜索时候，不设置搜索过
                HPLMN/EPLMN.
15.日    期   : 2015-5-18
   作    者   : c00318887
   修改内容   : DPlmn扩容和优先接入HPLMN
16.日    期   : 2015年10月28日
   作    者   : s00217060
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0:新增Pref band搜的处理
*****************************************************************************/
VOS_VOID NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstDestPlmn
)
{

    VOS_UINT32                                              ulUserSpecPlmnSearch;
    NAS_MMC_FSM_ID_ENUM_UINT32                              enCurrentFsmId;
    VOS_UINT32                                              ulCurrentEventType;
    NAS_MML_FORBIDPLMN_ROAMING_LAS_INFO_STRU                stForbRoamLaInfo;
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU                        *pstForbPlmnInfo = VOS_NULL_PTR;
    VOS_UINT32                                              ulWaitWasPlmnSrchCnfTimerLen;
    NAS_MML_PLMN_LIST_WITH_RAT_STRU                         stDestPlmnList;
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;

    NAS_MML_RAT_CAPABILITY_STATUS_ENUM_UINT8                enLteForbiddenStatus;

    enLteForbiddenStatus = NAS_MML_GetLteForbiddenStatusFlg();

    /* 获取LTE能力状态 */
    enLCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();
#endif

    ulWaitWasPlmnSrchCnfTimerLen = NAS_MMC_GetWaitWasPlmnSrchCnfTimerLen();
    enCurrentFsmId     = NAS_MMC_GetCurrFsmId();
    if (NAS_MMC_FSM_PLMN_SELECTION != enCurrentFsmId)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }
    ulCurrentEventType = NAS_MMC_GetCurrFsmEventType();

    /* 获取是否用户指定搜网 */
    ulUserSpecPlmnSearch = NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enCurrentFsmId,ulCurrentEventType);
    if ( VOS_TRUE == ulUserSpecPlmnSearch )
    {
        /* 是用户指定搜网，从当前选网状态机中获取FORBIDEN ROAMING LAS信息 */
        PS_MEM_CPY( &stForbRoamLaInfo,
                    NAS_MMC_GetForbRoamLaInfo_PlmnSelection(),
                    sizeof(stForbRoamLaInfo) );
    }
    else
    {
        /* 非用户指定搜网，从全局变量中获取FORBIDEN ROAMING LAS信息 */
        pstForbPlmnInfo                  = NAS_MML_GetForbidPlmnInfo();
        stForbRoamLaInfo.ucForbRoamLaNum = pstForbPlmnInfo->ucForbRoamLaNum;
        PS_MEM_CPY( stForbRoamLaInfo.astForbRomLaList,
                    pstForbPlmnInfo->astForbRomLaList,
                    sizeof(pstForbPlmnInfo->astForbRomLaList) );

        NAS_MML_AddCustomizedForbLaToDestLaList(&(stForbRoamLaInfo.ucForbRoamLaNum),
                                                 stForbRoamLaInfo.astForbRomLaList);
    }



    /* 状态更新为当前未驻留 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

    /* Added by s00246516 for L-C互操作项目, 2014-01-28, Begin */
    NAS_MMC_SetAsAnyCampOn(VOS_FALSE);
    /* Added by s00246516 for L-C互操作项目, 2014-01-28, End */

#if (FEATURE_ON == FEATURE_LTE)
    /* 如果当前已经通知LTE disable,此时存在LTE的国内网络需要enable LTE */

    if ((VOS_TRUE == NAS_MML_GetDisableLteRoamFlg())
     && (NAS_MML_NET_RAT_TYPE_LTE == pstDestPlmn->enRat)
     && (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE != enLteForbiddenStatus))
    {
        /* 当前LTE能力恢复可用或者为默认值 */
        if ((NAS_MML_LTE_CAPABILITY_STATUS_BUTT == enLCapabilityStatus)
         || (NAS_MML_LTE_CAPABILITY_STATUS_REENABLE_NOTIFIED_AS == enLCapabilityStatus))
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
        NAS_MML_SetDisableLteRoamFlg(VOS_FALSE);
    }
#endif

    PS_MEM_SET(&stDestPlmnList, 0x0, sizeof(stDestPlmnList));
    stDestPlmnList.ulPlmnNum = 1;
    PS_MEM_CPY(&stDestPlmnList.astPlmnId[0], pstDestPlmn, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    /* Modified by  for c00318887 for DPlmn扩容和优先接入HPLMN, 2015-7-30, begin */
    NAS_MMC_BuildDestPlmnListWhenSearchPlmn_PlmnSelection(&stDestPlmnList, pstDestPlmn);
    /* Modified by  for c00318887 for DPlmn扩容和优先接入HPLMN, 2015-7-30, end */


    /* 根据不同的接入技术发送搜网请求 */
    switch (pstDestPlmn->enRat)
    {
#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:
            NAS_MMC_SndLmmSpecPlmnSearchReq_PlmnSelection(&stDestPlmnList, ulUserSpecPlmnSearch);

            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_SEARCH_CNF);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF, TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF_LEN);
            break;
#endif

        case NAS_MML_NET_RAT_TYPE_WCDMA:
            NAS_MMC_SndAsSpecPlmnSearchReq_PlmnSelection(&stDestPlmnList, &stForbRoamLaInfo);

            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_PLMN_SEARCH_CNF);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF, ulWaitWasPlmnSrchCnfTimerLen);
            break;

        case NAS_MML_NET_RAT_TYPE_GSM:

            if ( NAS_MMC_PLMN_SEARCH_TYPE_HISTORY == NAS_MMC_GetCurrSearchingType_PlmnSelection() )
            {
                NAS_MMC_SndAsHistoryPlmnSearchReq(&stDestPlmnList, &stForbRoamLaInfo);
            }
            else if ( NAS_MMC_PLMN_SEARCH_TYPE_PREFBAND == NAS_MMC_GetCurrSearchingType_PlmnSelection() )
            {
                NAS_MMC_SndAsPrefBandPlmnSearchReq(&stDestPlmnList, &stForbRoamLaInfo);
            }
            else
            {
                NAS_MMC_SndAsSpecPlmnSearchReq(&stDestPlmnList, &stForbRoamLaInfo);
            }

            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_PLMN_SEARCH_CNF);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_PLMN_SEARCH_CNF, NAS_MMC_GetWaitGasPlmnSearchCnfTimerLen(ulUserSpecPlmnSearch));

            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection: Rat not support.");
            break;
    }


    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndSuspendReq_PlmnSelection
 功能描述  : 根据不同的接入技术向接入层或者LMM发送挂起请求
 输入参数  : enRat
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月11日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2014年1月28日
   作    者   : s00246516
   修改内容   : L-C互操作项目:增加获取和注册请求的处理
*****************************************************************************/
VOS_VOID NAS_MMC_SndSuspendReq_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    /* 状态更新为当前未驻留 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

    /* Added by s00246516 for L-C互操作项目, 2014-01-28, Begin */
    NAS_MMC_SetAsAnyCampOn(VOS_FALSE);
    /* Added by s00246516 for L-C互操作项目, 2014-01-28, End */

    /* 根据不同的接入技术设置等待搜网回复的状态 */
    switch (enRat)
    {
#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:
            NAS_MMC_SndLmmSuspendReq();
            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_SUSPEND_CNF);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_SUSPEND_CNF, TI_NAS_MMC_WAIT_LMM_SUSPEND_CNF_LEN);
            break;
#endif

        case NAS_MML_NET_RAT_TYPE_WCDMA:
            NAS_MMC_SndAsSuspendReq(WUEPS_PID_WRR);
            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF, TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF_LEN);
            break;

        case NAS_MML_NET_RAT_TYPE_GSM:
            NAS_MMC_SndAsSuspendReq(UEPS_PID_GAS);
            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_SUSPEND_CNF);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF, TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF_LEN);
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndSuspendReq_PlmnSelection: Rat not support.");
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndRelReq_PlmnSelection
 功能描述  : 根据不同的接入技术向MM/GMM或EPS发送释放请求，并迁移状态启动保护定时器
 输入参数  : enRat
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月11日
   作    者   : s46746
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SndRelReq_PlmnSelection(
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
            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_CONN_REL_IND);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND, TI_NAS_MMC_WAIT_EPS_CONN_REL_IND_LEN);
            NAS_MMC_SetRelRequestFlag_PlmnSelection(VOS_TRUE);
            break;
#endif

        case NAS_MML_NET_RAT_TYPE_WCDMA:
        case NAS_MML_NET_RAT_TYPE_GSM:

            /* 向MM/GMM发送释放请求 */
            NAS_MMC_SndMmRelReq();
            NAS_MMC_SndGmmRelReq();

            NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_RRC_CONN_REL_IND);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL, TI_NAS_MMC_WAIT_RRC_CONN_REL_LEN);
            NAS_MMC_SetRelRequestFlag_PlmnSelection(VOS_TRUE);
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndRelReq_PlmnSelection: Rat not support.");
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_UpdateGUSearchInfo
 功能描述  : 根据搜网结果更新相应接入技术的网络覆盖信息
 输入参数  : pstSrchCnfMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月11日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年11月05日
   作    者   : w00176964
   修改内容   : DTS2011082405001:更新网络覆盖类型
*****************************************************************************/
VOS_VOID NAS_MMC_UpdateGUCoverageFlg_PlmnSelection(
    RRMM_PLMN_SEARCH_CNF_STRU          *pstSrchCnfMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat;
    NAS_MMC_COVERAGE_TYPE_ENUM_UINT8    enCoverType;

    if (WUEPS_PID_WRR == pstSrchCnfMsg->MsgHeader.ulSenderPid)
    {
        enRat = NAS_MML_NET_RAT_TYPE_WCDMA;
    }
    else
    {
        enRat = NAS_MML_NET_RAT_TYPE_GSM;
    }

    switch  (pstSrchCnfMsg->ulSearchRlt)
    {
        /* 指定搜失败的覆盖类型转换 */
        case RRC_PLMN_SEARCH_RLT_SPEC_FAIL:

            /* 将RRC的覆盖类型转换为NAS格式的覆盖类型 */
            NAS_MMC_ConvertRrcCoverTypeToNasFormat(pstSrchCnfMsg->enCoverageType, &enCoverType);

            /* 根据RRC的当前接入技术覆盖信息更新 */
            NAS_MMC_SetRatCoverage_PlmnSelection(enRat, enCoverType);
            break;

        /* 指定搜成功更新当前接入技术存在的覆盖 */
        case RRC_PLMN_SEARCH_RLT_SPEC:

            if (NAS_MMC_COVERAGE_TYPE_BUTT == NAS_MMC_GetSpecRatCoverageTypeInRatSearchInfoList(
                                              NAS_MMC_GetSearchRatInfo_PlmnSelection(), enRat))
            {
                NAS_MMC_SetRatCoverage_PlmnSelection(enRat, NAS_MMC_COVERAGE_TYPE_LOW);
            }
            break;

        /* 指定搜NO RF则不更新 */
        case RRC_PLMN_SEARCH_RLT_SPEC_NO_RF:
            break;

        /* HISTORY搜网失败 */
        case RRC_PLMN_SEARCH_RLT_HISTORY_FAIL:

            /* 将RRC的覆盖类型转换为NAS格式的覆盖类型 */
            NAS_MMC_ConvertRrcCoverTypeToNasFormat(pstSrchCnfMsg->enCoverageType, &enCoverType);

            /* 根据RRC的当前接入技术覆盖信息更新 */
            NAS_MMC_SetRatCoverage_PlmnSelection(enRat, enCoverType);
            break;

        /* HISTORY搜网成功，不知覆盖类型，不更新 */
        case RRC_PLMN_SEARCH_RLT_HISTORY_SUCC:

            if (NAS_MMC_COVERAGE_TYPE_BUTT == NAS_MMC_GetSpecRatCoverageTypeInRatSearchInfoList(
                                              NAS_MMC_GetSearchRatInfo_PlmnSelection(), enRat))
            {
                NAS_MMC_SetRatCoverage_PlmnSelection(enRat, NAS_MMC_COVERAGE_TYPE_LOW);
            }
            break;

        /* HISTORY搜网NO RF不更新覆盖 */
        case RRC_PLMN_SEARCH_RLT_HISTORY_NO_RF:
            break;

        /* pref band失败的覆盖类型转换 */
        case RRC_PLMN_SEARCH_RLT_PREF_BAND_FAIL:

            /* 将RRC的覆盖类型转换为NAS格式的覆盖类型 */
            NAS_MMC_ConvertRrcCoverTypeToNasFormat(pstSrchCnfMsg->enCoverageType, &enCoverType);

            /* 根据RRC的当前接入技术覆盖信息更新 */
            NAS_MMC_SetRatCoverage_PlmnSelection(enRat, enCoverType);
            break;

        /* pref band成功更新当前接入技术存在的覆盖 */
        case RRC_PLMN_SEARCH_RLT_PREF_BAND_SUCC:

            if (NAS_MMC_COVERAGE_TYPE_BUTT == NAS_MMC_GetSpecRatCoverageTypeInRatSearchInfoList(
                                              NAS_MMC_GetSearchRatInfo_PlmnSelection(), enRat))
            {
                NAS_MMC_SetRatCoverage_PlmnSelection(enRat, NAS_MMC_COVERAGE_TYPE_LOW);
            }
            break;

        /* pref band NO RF则不更新 */
        case RRC_PLMN_SEARCH_RLT_PREF_BAND_NO_RF:
            break;

        default:
            break;
    }

    return;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_MMC_UpdateLmmSearchInfo
 功能描述  : 根据搜网结果更新LTE的搜网信息
 输入参数  : enRat
             pstLmmSrchCnfMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月11日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年11月05日
   作    者   : w00176964
   修改内容   : DTS2011082405001:更新网络覆盖类型
 3.日    期   : 2015年6月9日
   作    者   : s00217060
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0修改
*****************************************************************************/
VOS_VOID NAS_MMC_UpdateLmmCoverageFlg_PlmnSelection(
    LMM_MMC_PLMN_SRCH_CNF_STRU         *pstLmmSrchCnfMsg
)
{
    NAS_MMC_COVERAGE_TYPE_ENUM_UINT8    enCoverType;

    switch(pstLmmSrchCnfMsg->enRlst)
    {
        /* 指定搜失败的覆盖类型转换 */
        case MMC_LMM_PLMN_SRCH_RLT_SPEC_FAIL:

            /* 将RRC的覆盖类型转换为NAS格式的覆盖类型 */
            NAS_MMC_ConvertLmmCoverTypeToNasFormat(pstLmmSrchCnfMsg->enCoverageType, &enCoverType);

            /* 根据RRC的当前接入技术覆盖信息更新 */
            NAS_MMC_SetRatCoverage_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE, enCoverType);

            break;

        /* 指定搜成功的覆盖类型转换 */
        case MMC_LMM_PLMN_SRCH_RLT_SPEC_SUCC:

            /* 更新当前接入技术存在覆盖 */
            if (NAS_MMC_COVERAGE_TYPE_BUTT == NAS_MMC_GetSpecRatCoverageTypeInRatSearchInfoList(
                                              NAS_MMC_GetSearchRatInfo_PlmnSelection(), NAS_MML_NET_RAT_TYPE_LTE))
            {
                NAS_MMC_SetRatCoverage_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE, NAS_MMC_COVERAGE_TYPE_LOW);
            }
            break;

        /* 指定搜NO RF则不更新 */
        case MMC_LMM_PLMN_SRCH_RLT_SPEC_NO_RF:
            break;

        case MMC_LMM_PLMN_SRCH_RLT_HISTORY_FAIL:

            /* 将RRC的覆盖类型转换为NAS格式的覆盖类型 */
            NAS_MMC_ConvertLmmCoverTypeToNasFormat(pstLmmSrchCnfMsg->enCoverageType, &enCoverType);

            NAS_MMC_SetRatCoverage_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE, enCoverType);

            break;

        case MMC_LMM_PLMN_SRCH_RLT_HISTORY_SUCC:

            if (NAS_MMC_COVERAGE_TYPE_BUTT == NAS_MMC_GetSpecRatCoverageTypeInRatSearchInfoList(
                                              NAS_MMC_GetSearchRatInfo_PlmnSelection(), NAS_MML_NET_RAT_TYPE_LTE))
            {
                NAS_MMC_SetRatCoverage_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE, NAS_MMC_COVERAGE_TYPE_LOW);
            }
            break;

        case MMC_LMM_PLMN_SRCH_RLT_HISTORY_NO_RF:
            break;

        /* pref band搜失败的覆盖类型转换 */
        case MMC_LMM_PLMN_SRCH_RLT_PREF_BAND_FAIL:

            /* 将RRC的覆盖类型转换为NAS格式的覆盖类型 */
            NAS_MMC_ConvertLmmCoverTypeToNasFormat(pstLmmSrchCnfMsg->enCoverageType, &enCoverType);

            /* 根据RRC的当前接入技术覆盖信息更新 */
            NAS_MMC_SetRatCoverage_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE, enCoverType);

            break;

        /* pref band搜成功的覆盖类型转换 */
        case MMC_LMM_PLMN_SRCH_RLT_PREF_BAND_SUCC:

            /* 更新当前接入技术存在覆盖 */
            if (NAS_MMC_COVERAGE_TYPE_BUTT == NAS_MMC_GetSpecRatCoverageTypeInRatSearchInfoList(
                                              NAS_MMC_GetSearchRatInfo_PlmnSelection(), NAS_MML_NET_RAT_TYPE_LTE))
            {
                NAS_MMC_SetRatCoverage_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE, NAS_MMC_COVERAGE_TYPE_LOW);
            }
            break;

        /* pref band搜NO RF则不更新 */
        case MMC_LMM_PLMN_SRCH_RLT_PREF_BAND_NO_RF:
            break;

        default:
            break;

    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_IsReCampLtePlmnValid_PlmnSelection
 功能描述  : 判断是否需要重新驻留回LTE网络
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:有效
             VOS_FALSE:无效
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年6月2日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2013年11月01日
   作    者   : l00208543
   修改内容   : 根据卡类型禁止网络制式
 3.日    期   : 2015年1月26日
   作    者   : z00161729
   修改内容   : AT&T 支持DAM特性修改
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsReCampLtePlmnValid_PlmnSelection(VOS_VOID)
{
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU                       *pstForbidPlmnInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                                   *pstReCampLtePlmn  = VOS_NULL_PTR;
    NAS_MMC_PLMN_SELECTION_MODE_ENUM_UINT8                  enPlmnSelectionMode;

    VOS_UINT32                                              ulIsPlmnSupportDam;

    pstReCampLtePlmn          = NAS_MMC_GetCsPsMode1ReCampLtePlmn_PlmnSelection();
    pstForbidPlmnInfo         = NAS_MML_GetForbidPlmnInfo();
    enPlmnSelectionMode       = NAS_MMC_GetPlmnSelectionMode();

    /* 当前不支持L时,重新回LTE的网络无效 */
    if ( VOS_FALSE == NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_LTE) )
    {
        return VOS_FALSE;
    }

    if (VOS_TRUE == NAS_MML_IsRatInForbiddenList(NAS_MML_NET_RAT_TYPE_LTE))
    {
        return VOS_FALSE;
    }

    /* 状态机上下文中回LTE网络无效 */
    if (VOS_FALSE == NAS_MML_IsPlmnIdValid(pstReCampLtePlmn))
    {
        return VOS_FALSE;
    }

    /* PS卡无效 */
    if ( VOS_FALSE == NAS_MML_GetSimPsRegStatus() )
    {
        return VOS_FALSE;
    }

    /* PS卡不允许注册 */
    if ( VOS_FALSE == NAS_MML_GetPsAttachAllowFlg() )
    {
        return VOS_FALSE;
    }

    /* 回LTE网络在禁止列表中,对应的场景是该网络在GU注册时被原因值#11拒绝*/
    if (VOS_TRUE == NAS_MML_IsSimPlmnIdInDestBcchPlmnList(pstReCampLtePlmn,
                                          pstForbidPlmnInfo->ucForbPlmnNum,
                                          pstForbidPlmnInfo->astForbPlmnIdList))
    {
        return VOS_FALSE;
    }

    /* 回LTE网络在禁止GPRS列表中,对应的场景是该网络在GU注册时被原因值#14拒绝 */
    if (VOS_TRUE == NAS_MML_IsSimPlmnIdInDestBcchPlmnList(pstReCampLtePlmn,
                                          pstForbidPlmnInfo->ucForbGprsPlmnNum,
                                          pstForbidPlmnInfo->astForbGprsPlmnList))
    {
        return VOS_FALSE;
    }

    /* 如果之前disable lte的网络是支持DAM的网络，且禁止接入技术网络列表特性9014 nv未开启，
       则无需enable lte,AT&T LTE-BTR-1-1840用例要求只禁止310410 lte网络，漫游lte网络可用，
       后该用例删除，如果后续有需要测试，可以开启DAM nv项进行测试 */
    ulIsPlmnSupportDam = NAS_MML_IsPlmnSupportDam(NAS_MMC_GetDisabledLtePlmnId());

    if (VOS_TRUE == ulIsPlmnSupportDam)
    {
        return VOS_FALSE;
    }

    /* 自动选网模式该网络有效 */
    if (NAS_MMC_PLMN_SELECTION_MODE_AUTO == enPlmnSelectionMode)
    {
        return VOS_TRUE;
    }

    /* 手动选网模式时重回LTE网络是否允许 */
    if (VOS_TRUE == NAS_MMC_IsPlmnAllowedInManualMode(pstReCampLtePlmn))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReCampLte_PlmnSelection
 功能描述  : 重新驻留LTE网络
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年6月2日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年7月16日
   作    者   : s00217060
   修改内容   : 如果之前已经Enable LTE,重新驻留回LTE时不需要通知接入层
 3.日    期   : 2012年09月27日
   作    者   : z00161729
   修改内容   : DTS2012090303562:搜网状态机等L注册结果收到丢网消息获取下一个网络失败退状态机后又发起非法随机网络搜网
 4.日    期   : 2013年01月23日
   作    者   : s00217060
   修改内容   : 问题单: DTS2013012106172,Enable Lte时停止定时器TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER
 5.日    期   : 2013年05月08日
   作    者   : s46746
   修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
 6.日    期   : 2014年3月19日
   作    者   : w00242748
   修改内容   : DTS2014031200137:当NV特性打开时，自动开机或者搜网时，如果首次搜索RPLMN的话，
                需要将HPLMN/EHPLMN带给接入层。
 7.日    期   : 2015年1月5日
   作    者   : z00161729
   修改内容   : AT&T 支持DAM特性修改

*****************************************************************************/
VOS_VOID NAS_MMC_ReCampLte_PlmnSelection(VOS_VOID)
{
    NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8   enSpecPlmnSearchFlg;
    VOS_UINT32                                  ulEqual;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8             enRat;
    NAS_MML_PLMN_WITH_RAT_STRU                  stReCampLtePlmn;
    NAS_MML_PLMN_LIST_WITH_RAT_STRU     stDestPlmnList;
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32   enLteCapabilityStatus;
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32       enPlmnSearchScene;

    PS_MEM_SET(&stReCampLtePlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));
    PS_MEM_SET(&stDestPlmnList, 0, sizeof(NAS_MML_PLMN_LIST_WITH_RAT_STRU));

    enLteCapabilityStatus               = NAS_MML_GetLteCapabilityStatus();

    stReCampLtePlmn.enRat               = NAS_MML_NET_RAT_TYPE_LTE;
    enSpecPlmnSearchFlg                 = NAS_MMC_GetSpecPlmnSearchState();
    enRat                               = NAS_MML_GetCurrNetRatType();

    enPlmnSearchScene                   = NAS_MMC_GetPlmnSearchScene_PlmnSelection();

    PS_MEM_CPY(&(stReCampLtePlmn.stPlmnId),
               NAS_MMC_GetCsPsMode1ReCampLtePlmn_PlmnSelection(),
               sizeof(stReCampLtePlmn.stPlmnId));

    ulEqual = NAS_MML_CompareBcchPlmnwithSimPlmn(&(stReCampLtePlmn.stPlmnId),
                                                  NAS_MML_GetCurrCampPlmnId());

    if (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == enLteCapabilityStatus)
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

    /* 当前已经驻留LTE网络,且该网络与需要重新驻留网络相同 */
    if ( (NAS_MML_NET_RAT_TYPE_LTE == enRat)
      && (NAS_MMC_SPEC_PLMN_SEARCH_STOP == enSpecPlmnSearchFlg)
      && (VOS_TRUE == ulEqual) )
    {
        /* 重新驻留LTE时将服务状态上报 */
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, begin*/
        NAS_MMC_SndMsccServiceStatusInd(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_GetServiceStatusForMscc(NAS_MSCC_PIF_SRVDOMAIN_CS));
        NAS_MMC_SndMsccServiceStatusInd(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_GetServiceStatusForMscc(NAS_MSCC_PIF_SRVDOMAIN_PS));
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, end*/

        /* 向上层状态机指示选网失败 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);

        /* 退出层二状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* 状态更新为当前未驻留 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);


    switch (enRat)
    {
        /* suspend过程中detach PS了，导致获取下一个网络失败 */
        case NAS_MML_NET_RAT_TYPE_BUTT:
        case NAS_MML_NET_RAT_TYPE_LTE:

            /* 向MM、GMM发送搜网指示 */
            NAS_MMC_SndGmmPlmnSchInit();
            NAS_MMC_SndMmPlmnSchInit();

            /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, begin */
            NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
            /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, end */

            NAS_MMC_UpdateRegStateSpecPlmnSearch();

            /* 向LMM发送指定搜网 */
            PS_MEM_SET(&stDestPlmnList, 0x0, sizeof(stDestPlmnList));

            stDestPlmnList.ulPlmnNum = 1;
            PS_MEM_CPY(&stDestPlmnList.astPlmnId[0], &stReCampLtePlmn, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

            NAS_MMC_SndLmmSpecPlmnSearchReq(&stDestPlmnList, VOS_FALSE, enPlmnSearchScene);

            /* 状态迁移NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_SEARCH_CNF_CSPSMODE1_RECAMP_LTE */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_SEARCH_CNF_CSPSMODE1_RECAMP_LTE);

            /* 启动保护定时器TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF, TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF_LEN);

            break;

        case NAS_MML_NET_RAT_TYPE_WCDMA:


            /* 向MM、GMM发送搜网指示 */
            NAS_MMC_SndGmmPlmnSchInit();
            NAS_MMC_SndMmPlmnSchInit();

            /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, begin */
            NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
            /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, end */

            NAS_MMC_UpdateRegStateSpecPlmnSearch();

            /* 向WRR发送挂起请求 */
            NAS_MMC_SndAsSuspendReq(WUEPS_PID_WRR);

            /* 状态迁移NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF_CSPSMODE1_RECAMP_LTE */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF_CSPSMODE1_RECAMP_LTE);

            /* 启动保护定时器TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF, TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF_LEN);

            break;

        case NAS_MML_NET_RAT_TYPE_GSM:


            /* 向MM、GMM发送搜网指示 */
            NAS_MMC_SndGmmPlmnSchInit();
            NAS_MMC_SndMmPlmnSchInit();

            /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, begin */
            NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
            /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, end */

            NAS_MMC_UpdateRegStateSpecPlmnSearch();

            /* 向Gas发送挂起请求 */
            NAS_MMC_SndAsSuspendReq(UEPS_PID_GAS);

            /* 状态迁移NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_SUSPEND_CNF_CSPSMODE1_RECAMP_LTE */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_SUSPEND_CNF_CSPSMODE1_RECAMP_LTE);

            /* 启动保护定时器TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF, TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF_LEN);

            break;

        default:

            /* 异常打印 */
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReCampLte_PlmnSelection,ERROR:Rat Error");

            break;
    }

    return;
}

#endif  /* (FEATURE_ON == FEATURE_LTE) */


/*****************************************************************************
 函 数 名  : NAS_MMC_UpdateUserPlmnList_PlmnSelection
 功能描述  : 根据用户列表搜网结果更新相应接入技术的信息
 输入参数  : pstPlmnSearchReq
 输出参数  : pstPlmnSelectionListInfo
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年8月3日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2011年10月12日
   作    者   : w00166186
   修改内容   : 新生成函数
 3.日    期   : 2012年11月05日
   作    者   : w00176964
   修改内容   : DTS2011082405001:更新网络覆盖类型
 4.日    期   : 2015年5月26日
   作    者   : w00167002
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0项目修改
 5.日    期   : 2015年10月22日
   作    者   : s00217060
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0修改
*****************************************************************************/
VOS_VOID NAS_MMC_UpdatePlmnSearchInfo_PlmnSelection(
    NAS_MMC_INTER_PLMN_SEARCH_REQ_STRU                     *pstPlmnSearchReq,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{
    VOS_UINT32                          i;

    for (i = 0; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        /* 接入技术无效不更新 */
        if (NAS_MML_NET_RAT_TYPE_BUTT == pstPlmnSearchReq->astInterPlmnSearchInfo[i].enRatType)
        {
            continue;
        }

        /* 接入技术无效或未进行过pref band搜/spec搜，不需要更新 */
        if (VOS_TRUE == NAS_MMC_IsNeedUpdateSpecRatPlmnSearchInfo_PlmnSelection(&(pstPlmnSearchReq->astInterPlmnSearchInfo[i])))
        {
            /* 设置当前接入技术进行了全频搜网 */
            NAS_MMC_SetAllBandSearch_PlmnSelection(pstPlmnSearchReq->astInterPlmnSearchInfo[i].enRatType, VOS_TRUE);

            /* 更新当前接入技术的网络覆盖类型 */
            NAS_MMC_SetRatCoverage_PlmnSelection(pstPlmnSearchReq->astInterPlmnSearchInfo[i].enRatType,
                                                 pstPlmnSearchReq->astInterPlmnSearchInfo[i].enCoverType);
        }


        /* 自动搜网 */
        if (NAS_MMC_PLMN_SELECTION_MODE_AUTO == NAS_MMC_GetPlmnSelectionMode())
        {
            /* 更新完毕需要将剩余网络补充到选网列表 */
            NAS_MMC_UpdatePlmnListInPlmnSelectionList(&(pstPlmnSearchReq->astInterPlmnSearchInfo[i]),
                                                      pstPlmnSelectionListInfo,
                                                      VOS_TRUE,
                                                      NAS_MMC_GetAllBandSearch_PlmnSelection(pstPlmnSearchReq->astInterPlmnSearchInfo[i].enRatType));

            /*重新对高质量网络进行排序*/
            NAS_MMC_SortAvailPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
        }
        else
        {
            /* 更新完毕不需要将剩余网络补充到选网列表 */
            NAS_MMC_UpdatePlmnListInPlmnSelectionList(&(pstPlmnSearchReq->astInterPlmnSearchInfo[i]),
                                                      pstPlmnSelectionListInfo,
                                                      VOS_FALSE,
                                                      NAS_MMC_GetAllBandSearch_PlmnSelection(pstPlmnSearchReq->astInterPlmnSearchInfo[i].enRatType));
        }
    }

    /* 更新是否进行过history搜标志 */
    if (NAS_MMC_PLMN_SEARCH_SCENE_AREA_LOST == pstPlmnSearchReq->enPlmnSearchScene)
    {
        for (i = 0; i < NAS_MML_MAX_RAT_NUM; i++)
        {
            if (pstPlmnSearchReq->astInterPlmnSearchInfo[i].enRatType == NAS_MML_GetCurrNetRatType())
            {
                /* 更新是否进行过history搜 */
                NAS_MMC_SetHistorySearchedFlag_PlmnSelection(pstPlmnSearchReq->astInterPlmnSearchInfo[i].enRatType,
                                                             pstPlmnSearchReq->astInterPlmnSearchInfo[i].stSearchedType.ucHistorySearchedFlg);
                break;
            }
        }
    }


    /* 可维可测，输出选网列表信息 */
    NAS_MMC_LogPlmnSelectionList(pstPlmnSelectionListInfo);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_UpdatePlmnSearchList_PlmnSelection
 功能描述  : 根据已搜索列表更新状态机上下文中搜网列表信息
 输入参数  : ucRatNum
             pstIntraPlmnSearchInfo
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月11日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2014年2月13日
   作    者   : s00246516
   修改内容   : L-C互操作项目:增加获取和注册请求的处理

 3.日    期   : 2014年11月15日
   作    者   : w00167002
   修改内容   : DTS2014111201728:CSFB搜网GU,携带AVAILABLE网络，没有将GU网络排序到
                前面。
 4.日    期   : 2014年11月8日
   作    者   : z00161729
   修改内容   : 开机漫游搜网优化项目修改
 5.日    期   : 2015年5月26日
   作    者   : w00167002
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0项目修改,对于HISTORY搜网，不能更新未找到的网络
   状态为不存在。
*****************************************************************************/
VOS_VOID NAS_MMC_UpdatePlmnSearchList_PlmnSelection(
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    *pstInterPlmnSearchInfo,
    VOS_UINT32                                               ulIsNeedSortAvailPlmnList,
    VOS_UINT8                                                ucIsAllBandSearch
)
{
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionList = VOS_NULL_PTR;

    VOS_UINT32                                              ulIsCsfbExist;

    pstPlmnSelectionList = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();

    ulIsCsfbExist        = NAS_MML_IsCsfbServiceStatusExist();

    /* Modified by s00246516 for L-C互操作项目, 2014-01-28, Begin */
    /* 自动搜网且搜网场景不为REG_HPLMN,也不为REG_PREF_PLMN,这两种搜网场景可以搜索的网络已经都在选网列表中了 */
    if (VOS_TRUE == NAS_MMC_IsNeedSearchAvailPlmn_PlmnSelection())
    /* Modified by s00246516 for L-C互操作项目, 2014-01-28, End */
    {
        if (VOS_TRUE == ulIsNeedSortAvailPlmnList)
        {
            /* 更新完毕需要将剩余网络补充到选网列表 */
            NAS_MMC_UpdatePlmnListInPlmnSelectionList(pstInterPlmnSearchInfo,
                                                     pstPlmnSelectionList,
                                                     VOS_TRUE,
                                                     ucIsAllBandSearch);


            /*重新对高质量网络进行排序*/
            NAS_MMC_SortAvailPlmnInPlmnSelectionList(pstPlmnSelectionList);
        }
        else
        {
            /* 判断search cnf fail带上来的网络是否在搜网列表中，如果不在且与rplmn和hplmn mcc
               不同则插入rplmn前面，如果rplmn不存在则插入hplmn前面 */
            NAS_MMC_UpdateRoamPlmnListInPlmnSelectionList(pstInterPlmnSearchInfo,
                                                          pstPlmnSelectionList,
                                                          VOS_TRUE,
                                                          ucIsAllBandSearch);
        }
    }
    else
    {

        /* 更新完毕将剩余网络补充到选网列表 */
        NAS_MMC_UpdatePlmnListInPlmnSelectionList(pstInterPlmnSearchInfo,
                                                  pstPlmnSelectionList,
                                                  VOS_FALSE,
                                                  ucIsAllBandSearch);
    }


    /* 如果当前是CSFB触发的搜网，则将L的网络排序到后面 */
    if ( (NAS_MMC_PLMN_SEARCH_SCENE_CSFB_SERVIEC_REJ == NAS_MMC_GetPlmnSearchScene_PlmnSelection())
      && (VOS_TRUE                                   == ulIsCsfbExist) )
    {
        NAS_MMC_SortPlmnSearchListSpecRatPrioLowest(NAS_MML_NET_RAT_TYPE_LTE,
                                                pstPlmnSelectionList);
    }

    /* 可维可测，输出选网列表信息 */
    NAS_MMC_LogPlmnSelectionList(pstPlmnSelectionList);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RefreshPlmnSelectionListAfterRegFail_PlmnSelection
 功能描述  : 根据注册被拒结果调整选网列表
 输入参数  : enAdditionalAction
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月11日
   作    者   : s46746
   修改内容   : 新生成函数
2. 日    期   : 2011年1月15日
   作    者  : l00171473
   修改内容   : For DTS2011111003965, 手动开机，用户指定网络被原因值13拒掉后，不应搜EPLMN
 3.日    期   : 2012年06月01日
   作    者   : s00217060
   修改内容   : For CS/PS mode 1, 如果Addition为PLMN SELECTION，并且已经Disable L,
                 刷新选网列表，把当前网络的GU接入技术放在列表的最前面
 4.日    期   : 2012年12月12日
   作    者   : t00212959
   修改内容   : For DTS2012121104779，不是因为CSPS mode 1导致的disable L,如被#7拒绝，不应该按照CSPS Mode1处理
 5.日    期   : 2014年11月25日
   作    者   : z00161729
   修改内容   : 开机搜网优化项目修改
*****************************************************************************/
VOS_VOID NAS_MMC_RefreshPlmnSelectionListAfterRegFail_PlmnSelection(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enAdditionalAction
)
{
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionList = VOS_NULL_PTR;
    NAS_MMC_RAT_SEARCH_INFO_STRU                           *pstSearchRatInfo     = VOS_NULL_PTR;
    NAS_MMC_PLMN_TYPE_ENUM_UINT8                            enPlmnType;
    NAS_MML_PLMN_WITH_RAT_STRU                              stCurrPlmnWithRat;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                                              ulDisableLteByCsPsModeOne;


    VOS_UINT32                                              ulIsNeedSortAvailablePlmnSelectionList;

    ulIsNeedSortAvailablePlmnSelectionList = NAS_MMC_IsNeedSortAvailablePlmnSelectionList_PlmnSelection();


    ulDisableLteByCsPsModeOne = NAS_MMC_IsDisableLteNeedLocalReleaseEpsConn();
#endif


    pstPlmnSelectionList = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();
    pstSearchRatInfo     = NAS_MMC_GetSearchRatInfo_PlmnSelection();

    stCurrPlmnWithRat.stPlmnId = (*NAS_MML_GetCurrCampPlmnId());
    stCurrPlmnWithRat.enRat    = NAS_MML_GetCurrNetRatType();

    /* 在选网列表中获取当前网络的类型 */
    enPlmnType = NAS_MMC_GetPlmnTypeInPlmnSelectionList(&stCurrPlmnWithRat, pstPlmnSelectionList);

    if ((NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION == enAdditionalAction)
     || (NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION == enAdditionalAction))
    {
#if (FEATURE_ON == FEATURE_LTE)
        if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS == NAS_MML_GetLteCapabilityStatus())
         && (VOS_TRUE == ulDisableLteByCsPsModeOne)
         && (VOS_TRUE == ulIsNeedSortAvailablePlmnSelectionList))
        {
            NAS_MMC_RefreshPlmnSelectionList_DisableLte_CsPsMode1RegSuccess(pstPlmnSelectionList, pstSearchRatInfo);
        }
        /* 当前网络搜索网络类型为Rplmn或者Eplmn时才需要对选网列表中EPLMN进行调整 */
        else if ((NAS_MMC_PLMN_TYPE_RPLMN == enPlmnType)
         || (NAS_MMC_PLMN_TYPE_EPLMN == enPlmnType)
         || (NAS_MMC_PLMN_TYPE_USER_SEPC_PLMN == enPlmnType))
        {
            /* 需要进行PLMN SELECTION时,自动选网模式后续搜网应该优先搜索EHPLMN,
               手动选网模式只能搜索用户指定网络 */
            NAS_MMC_RefreshEPlmnInPlmnSelectionList(pstPlmnSelectionList);
        }
        else
        {
        }
#else
        if ((NAS_MMC_PLMN_TYPE_RPLMN == enPlmnType)
         || (NAS_MMC_PLMN_TYPE_EPLMN == enPlmnType)
         || (NAS_MMC_PLMN_TYPE_USER_SEPC_PLMN == enPlmnType))
        {
            /* 需要进行PLMN SELECTION时,自动选网模式后续搜网应该优先搜索EHPLMN,
               手动选网模式只能搜索用户指定网络 */
            NAS_MMC_RefreshEPlmnInPlmnSelectionList(pstPlmnSelectionList);
        }
#endif
    }
    else if (NAS_MMC_ADDITIONAL_ACTION_SEARCH_SUITABLE_CELL_IN_SAME_PLMN == enAdditionalAction)
    {
        /* 需要搜索当前网络其它位置区时,需要将当前网络所有未尝试注册的接入技术
           放在选网列表最前面,当前接入技术放在其它接入技术前面 */

        NAS_MMC_RefreshCurPlmnInPlmnSelectionList(pstPlmnSelectionList, pstSearchRatInfo, enPlmnType);
    }
    else
    {
    }

    /* 可维可测，输出选网列表信息 */
    NAS_MMC_LogPlmnSelectionList(pstPlmnSelectionList);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SearchNextPlmn_PlmnSelection
 功能描述  : 当信令连接不存在时执行选网操作
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月11日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2011年12月14日
   作    者   : w00176964
   修改内容   : V7R1 phaseIV 调整:驻留标记通过新的搜网控制上下文代替

 3.日    期   : 2012年2月1日
   作    者   : l00130025
   修改内容   : DTS2012011905274，指定搜网L注册失败后，若后续没有网络没有上报指定搜网结果
 4.日    期   : 2012年06月02日
   作    者   : sunxibo /46746
   修改内容   : Added for V7R1 C50 CS/PS mode 1
 5.日    期   : 2013年05月08日
   作    者   : s46746
   修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
 6.日    期   : 2013年8月27日
   作    者   : l00208543
   修改内容   : Coverity
 7.日    期   : 2014年4月14日
   作    者   : s00261364
   修改内容   : V3R360_eCall项目:搜网时更新服务状态

*****************************************************************************/
VOS_VOID NAS_MMC_SearchNextPlmn_PlmnSelection(VOS_VOID)
{
    NAS_MML_PLMN_WITH_RAT_STRU          stDestPlmn;

    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    /*  获取下个网络失败，则进行出服务区处理 */
    if (VOS_TRUE != NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);


        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();

        return;
    }

    /* 向GMM发送搜网指示 */
    NAS_MMC_SndGmmPlmnSchInit();

    /* 向MM发送搜网指示 */
    NAS_MMC_SndMmPlmnSchInit();

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, end */

    NAS_MMC_UpdateRegStateSpecPlmnSearch();

    /* Added by s00261364 for V3R360_eCall项目, 2014-4-14, begin */
    NAS_MMC_UpdateServiceStateSpecPlmnSearch();
    /* Added by s00261364 for V3R360_eCall项目, 2014-4-14, end */

    /* 需要挂起当前模式，切换到等待挂起状态，启动保护定时器 */
    if (stDestPlmn.enRat == NAS_MML_GetCurrNetRatType())
    {
        /* 向接入层或LMM发送搜网请求，根据不同的搜网模式，迁移到不同的L2状态，并启动保护定时器 */
        NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
    }
    else
    {
        /* 向接入层或LMM发送挂起请求，根据当前不同的接入技术，迁移到不同的L2状态，并启动保护定时器 */
        NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_GetCurrNetRatType());
    }

    return;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_PerformAdditionalActionRegFinished_PlmnSelection
 功能描述  : 在等待注册状态接收到所有注册结果后根据保存的CS和PS的Addition Action 决定状态机下一步行为
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月11日
   作    者   : l00130025
   修改内容   : 新生成函数
 2.日    期   : 2011年10月6日
   作    者   : w00167002
   修改内容   : PhaseII修改:删除更改当前的网络的注册状态为REGISTERED，
                 统一等注册结果后，才更改为REGISTERED
 3.日    期   : 2011年12月14日
   作    者   : w00176964
   修改内容   : V7R1 phaseIV 调整:驻留标记通过新的搜网控制上下文代替
 4.日    期   : 2011年12月22日
   作    者   : w00176964
   修改内容   : V7R1 phaseIV 调整:迁移状态到等待EPS链路释放时启动定时器错误
 5.日    期   : 2012年11月22日
   作    者   : t00212959
   修改内容   : DTS2012112006974:L下只有PS注册成功#18，需要disable LTE需要向L发送释放链接请求
 6.日    期   : 2014年1月28日
   作    者   : s00246516
   修改内容   : L-C互操作项目:增加获取和注册请求的处理
 7.日    期   : 2015年8月13日
   作    者   : l00289540
   修改内容   : User_Exp_Improve修改
*****************************************************************************/
VOS_VOID NAS_MMC_PerformAdditionalActionRegFinished_PlmnSelection()
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsAdditionalAction;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo           = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stCurPlmn;

    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene;
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstCurrSearchingPlmn = VOS_NULL_PTR;

    enPlmnSearchScene     = NAS_MMC_GetPlmnSearchScene_PlmnSelection();
    pstCurrSearchingPlmn  = NAS_MMC_GetCurrSearchingPlmn_PlmnSelection();

    /* 获取当前驻留的网络信息 */
    pstCurCampInfo     = NAS_MML_GetCurrCampPlmnInfo();
    stCurPlmn.stPlmnId = pstCurCampInfo->stLai.stPlmnId;
    stCurPlmn.enRat    = pstCurCampInfo->enNetRatType;

    /* 获取高优先级网络列表 */
    pstPlmnSelectionListInfo = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();

    NAS_MMC_UpdateRegFinishedPlmnNetStatusInPlmnSelectionList(
                                            &stCurPlmn,
                                            pstPlmnSelectionListInfo);

    /* ncell搜网场景,系统消息上报的网络不一定是ncell搜的网络，所以刷新搜网列表时应该刷新之前搜索的plmn */
    if ((VOS_TRUE == NAS_MMC_IsInterPlmnSearch_PlmnSelection())
     && (NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED_NCELL_SEARCH == enPlmnSearchScene))
    {
        stCurPlmn.stPlmnId = pstCurrSearchingPlmn->stPlmnId;
        stCurPlmn.enRat    = pstCurrSearchingPlmn->enRat;
        NAS_MMC_UpdatePlmnNetStatusInPlmnSelectionList(&stCurPlmn,
                                            NAS_MMC_NET_STATUS_SEARCHED_REGISTERED,
                                            pstPlmnSelectionListInfo);
    }

    /* 调用优先级比较表格得出CS/PS的处理优先级，并转换为状态机下一步行为 */
    enCsAdditionalAction = NAS_MMC_GetCsRegAdditionalAction_PlmnSelection();
    enPsAdditionalAction = NAS_MMC_GetPsRegAdditionalAction_PlmnSelection();
    enAdditionalAction   = NAS_MMC_GetPrioAddtionalAction(enCsAdditionalAction, enPsAdditionalAction);

    if (NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT == enAdditionalAction)
    {
        return;
    }

    /* 由于L和GU的注册结果处理均会调用此函数，故两个定时器都停一下 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);

    /* 附加操作为驻留当前网络 */
    if ((NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON == enAdditionalAction)
     || (NAS_MMC_ADDITIONAL_ACTION_CELL_SELECTION == enAdditionalAction)
     || (NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON == enAdditionalAction)
     || (NAS_MMC_ADDITIONAL_ACTION_ACCESS_BARRED == enAdditionalAction))
    {
        /* 回复状态机退出成功 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_SUCC);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* Added by s00246516 for L-C互操作项目, 2014-01-28, Begin */
    /* 如果是NCELL搜网，不需要再搜索其他网络了，退出状态机 */
    if (NAS_MMC_PLMN_SEARCH_SCENE_REG_NCELL == NAS_MMC_GetPlmnSearchScene_PlmnSelection())
    {
        /* 向上层状态机指示选网失败 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }
    /* Added by s00246516 for L-C互操作项目, 2014-01-28, End */

    /* 信令链接存在，且当前需要搜网，则迁移到等待连接释放的状态 */
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
#if (FEATURE_ON == FEATURE_LTE)
        if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
        {
            if (VOS_FALSE == NAS_MMC_IsDisableLteNeedWaitEpsConnRel_PlmnSelection())
            {
                return;
            }

            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_CONN_REL_IND);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND, TI_NAS_MMC_WAIT_EPS_CONN_REL_IND_LEN);
        }
        else
#endif
        {
            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_RRC_CONN_REL_IND);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL, TI_NAS_MMC_WAIT_RRC_CONN_REL_LEN);
        }

        return;
    }

    if ((NAS_MMC_ADDITIONAL_ACTION_CSPS_ANYCELL == enAdditionalAction)
     || (NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL == enAdditionalAction))
    {
        /* 向上层状态机指示选网失败 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* 若enRegAdditionalAction为搜网，则根据类型更新列表 */
    NAS_MMC_RefreshPlmnSelectionListAfterRegFail_PlmnSelection(enAdditionalAction);

    NAS_MMC_SearchNextPlmn_PlmnSelection();

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_PerformAdditionalAction_PlmnSelection
 功能描述  : 在等待连接释放状态接收到所有连接释放后根据保存的CS和PS的Addition Action 决定状态机下一步行为
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月11日
   作    者   : l00130025
   修改内容   : 新生成函数
 2.日    期   : 2011年12月14日
   作    者   : w00176964
   修改内容   : V7R1 phaseIV 调整:驻留标记通过新的搜网控制上下文代替

*****************************************************************************/
VOS_VOID NAS_MMC_PerformAdditionalActionConnRel_PlmnSelection(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enCsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enPsAdditionalAction;

    /* 调用优先级比较表格得出CS/PS的处理优先级，并转换为状态机下一步行为 */
    enCsAdditionalAction = NAS_MMC_GetCsRegAdditionalAction_PlmnSelection();
    enPsAdditionalAction = NAS_MMC_GetPsRegAdditionalAction_PlmnSelection();
    enAdditionalAction   = NAS_MMC_GetPrioAddtionalAction(enCsAdditionalAction, enPsAdditionalAction);

    /* 如果附加操作为继续等待,表示等待连接过程中又接收到了注册结果,此时将状态迁回到等待注册结果 */
    if (NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT == enAdditionalAction)
    {
#if (FEATURE_ON == FEATURE_LTE)
        if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
        {
            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_REG_IND, TI_NAS_MMC_WAIT_EPS_REG_IND_LEN);
        }
        else
#endif
        {
            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_CSPS_REG_IND);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND, TI_NAS_MMC_WAIT_CSPS_REG_IND_LEN);
        }

        return;
    }

    /* 附加操作为驻留当前网络 */
    if ((NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON == enAdditionalAction)
     || (NAS_MMC_ADDITIONAL_ACTION_CELL_SELECTION == enAdditionalAction)
     || (NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON == enAdditionalAction)
     || (NAS_MMC_ADDITIONAL_ACTION_ACCESS_BARRED == enAdditionalAction))
    {
        /* 回复状态机退出成功 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_SUCC);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    if ((NAS_MMC_ADDITIONAL_ACTION_CSPS_ANYCELL == enAdditionalAction)
     || (NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL == enAdditionalAction))
    {
        /* 向上层状态机指示选网失败 */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* 若enRegAdditionalAction为搜网，则根据类型更新列表 */
    NAS_MMC_RefreshPlmnSelectionListAfterRegFail_PlmnSelection(enAdditionalAction);

    NAS_MMC_SearchNextPlmn_PlmnSelection();

    return;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_ProcUserSearchCsRegRslt_PlmnSelection
 功能描述  : 处理用户指定搜网的CS域的注册结果
 输入参数  : enCause: CS注册失败原因值
 输出参数  : 无
 返 回 值  : VOS_TRUE:  指定搜网处理结束(已向用户回结果)
             VOS_FASLE: 指定搜网处理未结束(未向用户回结果)
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月28日
   作    者   : l00130025
   修改内容   : 新生成函数
 2.日    期   : 2011年12月15日
   作    者   : W00166186
   修改内容   : dts2011111502641,L下PLMN加入禁止TA后不再搜网
 3.日    期   : 2012年6月4日
   作    者   : l00171473
   修改内容   : DTS2012053003921
*****************************************************************************/
VOS_UINT32 NAS_MMC_ProcUserSearchCsRegRslt_PlmnSelection(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCsCause
)
{
    VOS_UINT32                          ulRlst;

    ulRlst = VOS_FALSE;

    /* 只要有一个域注册成功，向MSCC发送用户指定搜网成功 */
    if (NAS_MML_REG_FAIL_CAUSE_NULL == enCsCause)
    {

        /* 设置当前注册状态为成功 */
        NAS_MMC_SetUserSpecPlmnRegisterStatus(VOS_TRUE);

        /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, begin*/
        NAS_MMC_SndMsccUserSpecPlmnSearchCnf(NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_SUCCESS);
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, end*/

#if   (FEATURE_ON == FEATURE_LTE)
        /* 向LMM发送用户搜网结束通知 */
        if ( VOS_TRUE == NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_LTE))
        {
            NAS_MMC_SndLmmUserSpecPlmnSearchEndNotify();
        }
#endif

        return VOS_TRUE;
    }

    /*
       注册失败时
       1、CS域首先注册失败，原因值是#2,#3,#6，根据PS注册结果通知TAF搜网结果
       2、某一个域中注册失败原因值是#11,#12,#13，通知TAF搜网失败
       3、CS Other Cause，继续等待PS的注册结果
    */

    switch(enCsCause)
    {
        /* 注册失败原因值是#11,#12,#13，通知TAF指定搜网失败 */
        case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_AUTH_REJ:

            /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, begin*/
            NAS_MMC_SndMsccUserSpecPlmnSearchCnf(NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_FAIL);
            /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, end*/

#if   (FEATURE_ON == FEATURE_LTE)
            /* 向LMM发送用户搜网结束通知 */
            if ( VOS_TRUE == NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_LTE))
            {
                NAS_MMC_SndLmmUserSpecPlmnSearchEndNotify();
            }
#endif

            ulRlst = VOS_TRUE;
            break;

        /* 其它原因值，暂不向MMA发送用户指定搜网结果，继续等待PS域的注册结果 */
        default:
            break;
    }
    return ulRlst;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcUserSearchPsRegRslt_PlmnSelection
 功能描述  : 处理用户指定搜网的PS域的注册结果
 输入参数  : enCause: PS注册失败原因值
 输出参数  : 无
 返 回 值  : VOS_TRUE:  指定搜网处理结束(已向用户回结果)
             VOS_FASLE: 指定搜网处理未结束(未向用户回结果)
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月28日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2011年12月15日
    作    者   : W00166186
    修改内容   : dts2011111502641,L下PLMN加入禁止TA后不再搜网
  3.日    期   : 2012年6月4日
    作    者   : l00171473
    修改内容   : DTS2012053003921
*****************************************************************************/
VOS_UINT32 NAS_MMC_ProcUserSearchPsRegRslt_PlmnSelection(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enPsCause
)
{
    VOS_UINT32                          ulRlst;

    ulRlst = VOS_FALSE;

    /* 只要有一个域注册成功，通知用户搜网成功, CAUSE_NULL表示注册成功 */
    if (NAS_MML_REG_FAIL_CAUSE_NULL == enPsCause)
    {

        /* 设置当前注册状态为成功 */
        NAS_MMC_SetUserSpecPlmnRegisterStatus(VOS_TRUE);

        /* 上报成功，更新当前搜网类型为手动搜网 */
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, begin*/
        NAS_MMC_SndMsccUserSpecPlmnSearchCnf(NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_SUCCESS);
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, end*/

#if   (FEATURE_ON == FEATURE_LTE)
        /* 向LMM发送用户搜网结束通知 */
        if ( VOS_TRUE == NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_LTE))
        {
            NAS_MMC_SndLmmUserSpecPlmnSearchEndNotify();
        }
#endif

        return VOS_TRUE;
    }

    /*  注册失败时
        1、PS域注册失败，原因值是#3,#6，进入无卡状态，通知TAF搜网失败
        2、某一个域中注册失败原因值是#11,#12,#13，通知TAF搜网失败
        3、PS注册失败#8，通知TAF搜网失败
        4、PS首先注册失败#7，继续等待CS的注册结果
        5、PS首先注册失败#7，继续等待CS的注册结果
        6、注册结果是#9,#10继续等待PS注册结果;如果PS注册结果成功，返回成功；如果PS注册失败，返回搜网失败
    */

    switch(enPsCause)
    {
        /* 原因值#3,#6,#8的处理 */
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:

            /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, begin*/
            NAS_MMC_SndMsccUserSpecPlmnSearchCnf(NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_FAIL);
            /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, end*/

#if   (FEATURE_ON == FEATURE_LTE)
            /* 向LMM发送用户搜网结束通知 */
            if ( VOS_TRUE == NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_LTE))
            {
                NAS_MMC_SndLmmUserSpecPlmnSearchEndNotify();
            }
#endif

            ulRlst = VOS_TRUE;
            break;

        /* 注册失败原因值是#11,#12,#13，通知TAF指定搜网失败 */
        case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_AUTH_REJ:

            /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, begin*/
            NAS_MMC_SndMsccUserSpecPlmnSearchCnf(NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_FAIL);
            /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, end*/

#if   (FEATURE_ON == FEATURE_LTE)
            /* 向LMM发送用户搜网结束通知 */
            if ( VOS_TRUE == NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_LTE))
            {
                NAS_MMC_SndLmmUserSpecPlmnSearchEndNotify();
            }
#endif

            ulRlst = VOS_TRUE;
            break;

        /* PS注册失败原因值#7,#9,#10,#14继续等待CS注册结果 */
        case NAS_MML_REG_FAIL_CAUSE_MS_ID_NOT_DERIVED:
        case NAS_MML_REG_FAIL_CAUSE_IMPLICIT_DETACHED:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
            break;

        /* 其它原因值的处理 ,等待CS的处理结果 */
        default:
            break;
    }

    return ulRlst;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcUserSearchRegCause15_PlmnSelection
 功能描述  : CS或PS注册15号原因值时,处理用户指定搜网的注册结果
 输入参数  : enCsCause: CS的注册结果
             enPsCause: PS的注册结果
 输出参数  : 无
 返 回 值  : VOS_TRUE:  指定搜网处理结束(已向用户回结果)
             VOS_FASLE: 指定搜网处理未结束(未向用户回结果)
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月8日
   作    者   : s46746
   修改内容   : 同步问题单DTS2011080101138
 2.日    期   : 2011年12月15日
   作    者   : W00166186
   修改内容   : dts2011111502641,L下PLMN加入禁止TA后不再搜网
*****************************************************************************/
VOS_UINT32 NAS_MMC_ProcUserSearchRegCause15_PlmnSelection(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCsCause,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enPsCause
)
{
    VOS_UINT32                          ulRlst;

    ulRlst = VOS_FALSE;

    /*  PS注册15号原因值时
        1、CS注册失败原因值是#11,#12,#13，通知TAF搜网失败
        2、CS注册失败其它原因值继续搜网注册

        CS注册15号原因值时
        1、PS域注册失败，原因值是#3,#6，进入无卡状态，通知TAF搜网失败
        2、PS注册失败原因值是#11,#12,#13，通知TAF搜网失败
        3、PS注册失败#8，通知TAF搜网失败
        4、PS注册失败其它原因值继续搜网注册
    */

    switch (enCsCause)
    {
        /* 注册失败原因值是#11,#12,#13，通知TAF指定搜网失败 */
        case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_AUTH_REJ:

            /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, begin*/
            NAS_MMC_SndMsccUserSpecPlmnSearchCnf(NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_FAIL);
            /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, end*/

#if   (FEATURE_ON == FEATURE_LTE)
            /* 向LMM发送用户搜网结束通知 */
            if ( VOS_TRUE == NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_LTE))
            {
                NAS_MMC_SndLmmUserSpecPlmnSearchEndNotify();
            }
#endif

            ulRlst = VOS_TRUE;
            break;

        /* 其它原因值，暂不向MMA发送用户指定搜网结果，继续下次搜网注册 */
        default:
            break;
    }

    switch (enPsCause)
    {
        /* 原因值#3,#6,#8的处理 */
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:

            /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, begin*/
            NAS_MMC_SndMsccUserSpecPlmnSearchCnf(NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_FAIL);
            /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, end*/
#if   (FEATURE_ON == FEATURE_LTE)
            /* 向LMM发送用户搜网结束通知 */
            if ( VOS_TRUE == NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_LTE))
            {
                NAS_MMC_SndLmmUserSpecPlmnSearchEndNotify();
            }
#endif
            ulRlst = VOS_TRUE;
            break;

        /* 注册失败原因值是#11,#12,#13，通知TAF指定搜网失败 */
        case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_AUTH_REJ:

            /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, begin*/
            NAS_MMC_SndMsccUserSpecPlmnSearchCnf(NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_FAIL);
            /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, end*/

#if   (FEATURE_ON == FEATURE_LTE)
            /* 向LMM发送用户搜网结束通知 */
            if ( VOS_TRUE == NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_LTE))
            {
                NAS_MMC_SndLmmUserSpecPlmnSearchEndNotify();
            }
#endif

            ulRlst = VOS_TRUE;
            break;

        /* 其它原因值，暂不向MSCC发送用户指定搜网结果，继续下次搜网注册 */
        default:
            break;
    }

    return ulRlst;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcUserSearchRegOtherCause_PlmnSelection
 功能描述  : CS或PS注册other cause原因值时,处理用户指定搜网的注册结果
 输入参数  : enCsCause: CS的注册结果
             enPsCause: PS的注册结果
 输出参数  : 无
 返 回 值  : VOS_TRUE:  指定搜网处理结束(已向用户回结果)
             VOS_FASLE: 指定搜网处理未结束(未向用户回结果)
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月8日
   作    者   : s46746
   修改内容   : 同步问题单DTS2011042803224
 2.日    期   : 2011年12月15日
   作    者   : W00166186
   修改内容   : dts2011111502641,L下PLMN加入禁止TA后不再搜网
 3.日    期   : 2012年6月4日
   作    者   : l00171473
   修改内容   : DTS2012053003921
*****************************************************************************/
VOS_UINT32 NAS_MMC_ProcUserSearchRegOtherCause_PlmnSelection(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCsCause,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enPsCause
)
{

    /* 只要有一个域注册成功，通知用户搜网成功, CAUSE_NULL表示注册成功 */
    if ((NAS_MML_REG_FAIL_CAUSE_NULL == enCsCause)
     || (NAS_MML_REG_FAIL_CAUSE_NULL == enPsCause))
    {

        /* 设置当前注册状态为成功 */
        NAS_MMC_SetUserSpecPlmnRegisterStatus(VOS_TRUE);

        /* 上报成功，更新当前搜网类型为手动搜网 */
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, begin*/
        NAS_MMC_SndMsccUserSpecPlmnSearchCnf(NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_SUCCESS);
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, end*/

#if   (FEATURE_ON == FEATURE_LTE)
        /* 向LMM发送用户搜网结束通知 */
        if ( VOS_TRUE == NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_LTE))
        {
            NAS_MMC_SndLmmUserSpecPlmnSearchEndNotify();
        }
#endif

        return VOS_TRUE;
    }

    /* 如果设置为CS ONLY或者PS ONLY,另一个域当前小区不支持时,需要搜索列表中下一
       个网络后回复指定搜网结果 */
    if ((NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT == enCsCause)
     && (NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT == enPsCause))
    {
        return VOS_FALSE;
    }

    if ((NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT == enCsCause)
     && (NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT == enPsCause))
    {
        return VOS_FALSE;
    }

    /* PS注册失败原因值#9,#10继续等待PS注册结果 */
    if ((NAS_MML_REG_FAIL_CAUSE_MS_ID_NOT_DERIVED == enPsCause)
     || (NAS_MML_REG_FAIL_CAUSE_IMPLICIT_DETACHED == enPsCause))
    {
        return VOS_FALSE;
    }

    /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, begin*/
    NAS_MMC_SndMsccUserSpecPlmnSearchCnf(NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_FAIL);
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, end*/

#if   (FEATURE_ON == FEATURE_LTE)
    /* 向LMM发送用户搜网结束通知 */
    if ( VOS_TRUE == NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_LTE))
    {
        NAS_MMC_SndLmmUserSpecPlmnSearchEndNotify();
    }
#endif

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ProcUserSearchRegRslt_PlmnSelection
 功能描述  : 处理用户指定搜网的注册结果
 输入参数  : enCsCause: CS的注册结果
             enPsCause: PS的注册结果
 输出参数  : 无
 返 回 值  : VOS_TRUE:  指定搜网处理结束(已向用户回结果)
             VOS_FASLE: 指定搜网处理未结束(未向用户回结果)
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月29日
   作    者   : 李军 l00171473
   修改内容   : 新生成函数
 2.日    期   : 2011年8月7日
   作    者   : l00130025
   修改内容   : 调整上报顺序
 3.日    期   : 2011年9月8日
   作    者   : s46746
   修改内容   : 同步V3R1版本问题单DTS2011080101138、DTS2011042803224
 4.日    期   : 2011年11月09日
   作    者   : w00166186
   修改内容   : 问题单DTS201110705494,手动搜网，PS被拒原因值14，CS成功，上报搜网失败
 5.日    期   : 2011年12月15日
   作    者   : W00166186
   修改内容   : dts2011111502641,L下PLMN加入禁止TA后不再搜网
 6.日    期   : 2012年6月4日
   作    者   : l00171473
   修改内容   : DTS2012053003921
 7.日    期   : 2013年9月14日
   作    者   : w00167002
   修改内容   : DTS2013090908249:开机用户指定搜网24003，CS注册被拒15，MM在LIMIT
                 状态，在选网状态机收到同一小区的SYSINFO后，通知MM当前没有FORB FLG,
                 导致MM发起循环注册；
                 CS注册被拒15后，上报系统消息，触发MM/GMM上报405，此时也不能直接
                 上报注册结果，需要再搜其它小区。
*****************************************************************************/
VOS_UINT32 NAS_MMC_ProcUserSearchRegRslt_PlmnSelection(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCsCause,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enPsCause
)
{
    /* Cause值为 NAS_MML_REG_FAIL_CAUSE_NULL 表示该域注册成功，
       Cause值为 NAS_MML_REG_FAIL_CAUSE_BUTT 表示该域还未收到注册结果 */

    /* 还未获取到注册结果,继续等待注册结果 */
    if ((NAS_MML_REG_FAIL_CAUSE_BUTT == enPsCause)
     && (NAS_MML_REG_FAIL_CAUSE_BUTT == enCsCause))
    {
        return VOS_FALSE;
    }

    /* 还未获取到PS注册结果，当前获取到CS注册结果, 处理CS的注册原因值 */
    if ( (NAS_MML_REG_FAIL_CAUSE_BUTT == enPsCause)
      && (NAS_MML_REG_FAIL_CAUSE_BUTT != enCsCause) )
    {
        return NAS_MMC_ProcUserSearchCsRegRslt_PlmnSelection(enCsCause);
    }

    /* 还未获取到CS注册结果，当前获取到PS注册结果，处理PS的注册原因值 */
    if ( (NAS_MML_REG_FAIL_CAUSE_BUTT == enCsCause)
      && (NAS_MML_REG_FAIL_CAUSE_BUTT != enPsCause) )
    {
        return NAS_MMC_ProcUserSearchPsRegRslt_PlmnSelection(enPsCause);
    }


    /* 两个域的注册结果都获取,CS或PS注册15号原因值时,对注册结果处理 */
    if ( (NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL       == enCsCause)
      || (NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL       == enPsCause)
      || (NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_ROAM == enCsCause)
      || (NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_ROAM == enPsCause))
    {
        return NAS_MMC_ProcUserSearchRegCause15_PlmnSelection(enCsCause, enPsCause);
    }

    /* 两个域的注册结果都获取,CS或PS注册15号原因值时,对注册结果处理 */
    if ((NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE <= enCsCause)
     || (NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE <= enPsCause))
    {
        return NAS_MMC_ProcUserSearchRegOtherCause_PlmnSelection(enCsCause, enPsCause);
    }

    /* 只要有一个域注册成功，向MMA发送用户指定搜网成功 */
    if ((NAS_MML_REG_FAIL_CAUSE_NULL == enCsCause)
     || (NAS_MML_REG_FAIL_CAUSE_NULL == enPsCause))
    {

        /* 设置当前注册状态为成功 */
        NAS_MMC_SetUserSpecPlmnRegisterStatus(VOS_TRUE);

        /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, begin*/
        NAS_MMC_SndMsccUserSpecPlmnSearchCnf(NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_SUCCESS);
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, end*/

#if   (FEATURE_ON == FEATURE_LTE)
        /* 向LMM发送用户搜网结束通知 */
        if ( VOS_TRUE == NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_LTE))
        {
            NAS_MMC_SndLmmUserSpecPlmnSearchEndNotify();
        }
#endif

        return VOS_TRUE;
    }

    /* 已获取到CS和PS的注册结果，且有明确原因值，非other cause和15,上报失败 */
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, begin*/
    NAS_MMC_SndMsccUserSpecPlmnSearchCnf(NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_FAIL);
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, end*/

#if   (FEATURE_ON == FEATURE_LTE)
    /* 向LMM发送用户搜网结束通知 */
    if ( VOS_TRUE == NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_LTE))
    {
        NAS_MMC_SndLmmUserSpecPlmnSearchEndNotify();
    }
#endif

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_LoadInterSysFsm_PlmnSelection
 功能描述  : 根据SUSPEND的原因值起不同的状态机
 输入参数  : MMC_SUSPEND_CAUSE_ENUM_UINT8        enSuspendCause
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月22日
   作    者   : L00171473
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_LoadInterSysFsm_PlmnSelection(
    MMC_SUSPEND_CAUSE_ENUM_UINT8        enSuspendCause
)
{
    switch ( enSuspendCause )
    {
        /* 启动HANDOVER状态机 */
        case MMC_SUSPEND_CAUSE_HANDOVER:
            NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_INTER_SYS_HO);
            break;

        /* 启动 CCO状态机 */
        case MMC_SUSPEND_CAUSE_CELLCHANGE:
            NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_INTER_SYS_CCO);
            break;

        /* 启动 小区重选 状态机 */
        case MMC_SUSPEND_CAUSE_CELLRESELECT:
        case MMC_SUSPEND_CAUSE_REDIRECTION:
            NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_INTER_SYS_CELLRESEL);
            break;

        /* 启动 系统出服务区搜网 状态机 */
        case MMC_SUSPEND_CAUSE_PLMNSEARCH:
            NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_INTER_SYS_OOS);
            break;

        default:
            NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_LoadInterSysFsm_PlmnSelection():default case");
            break;
    }

}


/*****************************************************************************
 函 数 名  : NAS_MMC_ProcUserSpecPlmnSrchForbGprsInfo_PlmnSelection
 功能描述  : 选网状态机中处理FORB GPRS信息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月16日
    作    者   : w00167002
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_ProcUserSpecPlmnSrchForbGprsInfo_PlmnSelection( VOS_VOID )
{
    NAS_MML_LAI_STRU                   *pstLai          = VOS_NULL_PTR;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCsRegCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enPsRegCause;

    pstLai              = NAS_MML_GetCurrCampLai();
    enCsRegCause        = NAS_MMC_GetCsRegCause_PlmnSelection();
    enPsRegCause        = NAS_MMC_GetPsRegCause_PlmnSelection();

    /* 在GSM下，如果CS注册成功，PS未注册，则删除FORB GPRS信息 */
    if ( (NAS_MML_NET_RAT_TYPE_GSM          == NAS_MML_GetCurrNetRatType())
      && (NAS_MML_REG_FAIL_CAUSE_NULL       == enCsRegCause)
      && (NAS_MML_REG_FAIL_CAUSE_BUTT       == enPsRegCause) )
    {
        NAS_MML_DelForbGprsPlmn(&(pstLai->stPlmnId));
    }

    return;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_SaveCommonPlmnSrchEntryMsg_PlmnSelection
 功能描述  : 指定搜网结束后，更新当前状态机的入口消息为普通搜网，可以被后续打断处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月22日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2015年4月13日
    作    者   : w00176964
    修改内容   : CDMA 1X Iteration 10 Modified

*****************************************************************************/
VOS_VOID NAS_MMC_SaveCommonPlmnSrchEntryMsg_PlmnSelection( VOS_VOID )
{
    MSCC_MMC_PLMN_SEARCH_REQ_STRU       stPlmnSrhReg;
    VOS_UINT32                          ulBuildEventType;

    PS_MEM_SET(&stPlmnSrhReg, 0x0, sizeof(MSCC_MMC_PLMN_SEARCH_REQ_STRU));
    stPlmnSrhReg.enAcqReason = NAS_MSCC_PIF_ACQ_REASON_POWER_UP;

    stPlmnSrhReg.MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    stPlmnSrhReg.MsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    stPlmnSrhReg.MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    stPlmnSrhReg.MsgHeader.ulReceiverPid     = WUEPS_PID_MMC;
    stPlmnSrhReg.MsgHeader.ulLength          = sizeof(MSCC_MMC_PLMN_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    stPlmnSrhReg.MsgHeader.ulMsgName         = ID_MSCC_MMC_PLMN_SEARCH_REQ;

    ulBuildEventType  = NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_SEARCH_REQ);

    /*设置当前入口消息为开机搜网*/
    NAS_MMC_SaveCurEntryMsg(ulBuildEventType, (struct MsgCB*)&stPlmnSrhReg);

}

/*****************************************************************************
 函 数 名  : NAS_MMC_UpdateUserSpecPlmnSearchInfo_PlmnSelection
 功能描述  : 更新用户指定搜网的参数
 输入参数  : pstPlmnId: 用户指定的PLMN
             ucAccessMode: 用户指定的接入模式
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月01日
   作    者   : L00171473
   修改内容   : 新生成函数

 2.日    期   : 2011年10月25日
   作    者   : w00167002
   修改内容   : DTS2011102405359:增加指定搜时，需要停止正在运行的高优先级/bg搜网

 3.日    期   : 2011年11月11日
   作    者   : w00167002
   修改内容   : 当前为指定搜，则初始化选网状态机的禁止漫游LA信息变量
 4.日    期   : 2011年11月24日
   作    者   : W00166186
   修改内容   : DT2011112308459,指定PLMN没有注册成功过,available定时器超时还会搜RPLMN

 5.日    期   : 2012年5月10日
   作    者   : l65478
   修改内容   : DTS2012050500988:NMO I时,PS注册失败#11,收到系统信息后又发起了注册
 6.日    期   : 2013年4月16日
   作    者   : z00161729
   修改内容   : 主动上报AT命令控制下移至C核及mma和mmc接口调整
 7.日    期   : 2013年6月4日
   作    者   : z00161729
   修改内容  : SVLTE 和usim接口调整修改
                  快速找回TL，所以应尽量让其快速找回。
 8.日    期   : 2014年2月24日
   作    者   : w00176964
   修改内容   : High_Rat_Hplmn_Search特性调整
 9.日    期   : 2014年10月25日
   作    者   : b00269685
   修改内容   : TD下High_Rat_Hplmn_Search特性调整

*****************************************************************************/
VOS_VOID  NAS_MMC_UpdateUserSpecPlmnSearchInfo_PlmnSelection(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId,
    VOS_UINT8                           ucAccessMode
)
{
    NAS_MML_PLMN_WITH_RAT_STRU          stUserSpecPlmn;

    /* 保存用户指定的PlmnID及其接入技术 */
    stUserSpecPlmn.stPlmnId.ulMcc = pstPlmnId->ulMcc;
    stUserSpecPlmn.stPlmnId.ulMnc = pstPlmnId->ulMnc;

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-16, begin */
    stUserSpecPlmn.enRat = ucAccessMode;
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-16, end */

    NAS_MMC_SetUserSpecPlmnId(&stUserSpecPlmn);

    /* 保存指定搜网前驻留的PlmnID及接入技术 */
    NAS_MMC_SaveUserReselPlmnInfo();


    /* 当前为指定搜，则初始化选网状态机的禁止漫游LA信息变量 */
    PS_MEM_SET( NAS_MMC_GetForbRoamLaInfo_PlmnSelection(),
                0X0, sizeof(NAS_MML_FORBIDPLMN_ROAMING_LAS_INFO_STRU) );

    PS_MEM_SET(NAS_MMC_GetForbPlmnForGrpsInfo_PlmnSelection(),
               0X0, sizeof(NAS_MML_PLMN_ID_STRU));

    /* 设置当前注册状态未注册 */
    NAS_MMC_SetUserSpecPlmnRegisterStatus(VOS_FALSE);

    /* 当前模式已是MANUAL，则不更新NV */
    if (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == NAS_MMC_GetPlmnSelectionMode())
    {
        return;
    }

    /* 设置当前搜网模式为手动模式 */
    NAS_MMC_SetPlmnSelectionMode(NAS_MMC_PLMN_SELECTION_MODE_MANUAL);


    /* 如果高优先级搜网定时器在运行过程中，则停止该定时器 */
    if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_HPLMN_TIMER))
    {
        NAS_MMC_StopTimer(TI_NAS_MMC_HPLMN_TIMER);

        /* HPLMN TIMER 停止事件上报 */
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_HPLMN_TIMER_STOP,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);
    }

    /* 如果周期高优先级搜网定时器在运行过程中，则停止该定时器 */
    if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_PERIOD_TRYING_HIGH_PRIO_PLMN_SEARCH))
    {
        NAS_MMC_StopTimer(TI_NAS_MMC_PERIOD_TRYING_HIGH_PRIO_PLMN_SEARCH);
    }

    if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_HIGH_PRIO_RAT_HPLMN_TIMER))
    {
        NAS_MMC_StopTimer(TI_NAS_MMC_HIGH_PRIO_RAT_HPLMN_TIMER);

        NAS_MMC_ResetCurHighPrioRatHplmnTimerFirstSearchCount_L1Main();
        NAS_MMC_InitTdHighRatSearchCount();
    }

    /* 将当前搜网模式写入NVIM中 */
    NAS_MMC_WritePlmnSelectionModeNvim();

    /* 搜网模式变化上报USIM */
    if (VOS_TRUE == NAS_MMC_IsNeedSndStkSearchModeChgEvt())
    {
        NAS_MMC_SndStkSearchModeChgEvt(NAS_MMC_PLMN_SELECTION_MODE_MANUAL);
    }

}
/*****************************************************************************
 函 数 名  : NAS_MMC_ProcCsRegRslt_PlmnSelection
 功能描述  : 对Cs注册结果的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月23日
   作    者   : l00130025
   修改内容   : 新生成函数

 2.日    期   : 2011年11月14日
   作    者   : w00167002
   修改内容   : DTS2011110907180:当前若为选网状态机，则添加禁止网络信息
                到选网状态机的禁止漫游LA变量里去
 3.日    期   : 2011年12月5日
   作    者   : z00161729
   修改内容   : V7R1 Phase IV调整,当前SYSCFG中L不在时，也需要向LMM通知ID_MMC_LMM_ACTION_RESULT_REQ
4.日    期   : 2011年11月28日
   作    者   : w00167002
   修改内容   : DTS2011112406707:若当前为假流程且当前的AdditionalAction不为
                初始无效值，则不更新当前的AdditionalAction的值，否则若当前为
                真流程或当前为假流程且AdditionalAction为初始无效值，则更新
                当前的AdditionalAction的值.
                修改原因:在ROAMING BROKER时候，设置1次失败,注册失败1次后，
                MMC需要搜网，但是MMC可能要等两个域的结果(如在选网状态机)，
                当收到系统消息的时候，假流程会更改MMC的AdditionalAction的值,
                导致ROMING BROKER特性失效。
 5.日    期   : 2011年12月5日
   作    者   : z00161729
   修改内容   : V7R1 Phase IV调整,当前SYSCFG中L不在时，也需要向LMM通知ID_MMC_LMM_ACTION_RESULT_REQ

 6.日    期   : 2012年1月3日
   作    者   : w00167002
   修改内容   : DTS2011122006209:g下PS ONLY注册成功_更改为CS后注册失败4次后未发起搜网
                统一调整注册ADDITIONAL ACTION的值，若是用户自定义的原因值(>=256)，则
                不保存注册结果。若当前支持L模，则注册原因值小于260时通知LMM.

 7.日    期   : 2012年1月20日
   作    者   : w00167002
   修改内容   : DTS2011122006209:将注册失败的消息通知给处理注册结果函数，
                  能进行更好的扩展.
 8.日    期   : 2012年3月1日
   作    者   : w00176964
   修改内容   : DTS2012022407450:联合ATTACH时,MM不能通知LMM此时CS的注册结果，否则导致TAU的类型不正确

 9.日    期   : 2012年5月10日
   作    者   : l65478
   修改内容   : DTS2012050500988:CS注册成功时,不能删除forbid PLMN for GPRS信息
10.日    期   : 2012年6月4日
   作    者   : l00171473
   修改内容   : DTS2012053003921, 用户手动指定网络的注册状态标志清理
11.日    期   : 2012年08月20日
   作    者   : l65478
   修改内容   : DTS2012081703289，手动搜网失败后关机，重新开机注册成功
                   后出服务区后不驻留EPLMN上
12.日    期   : 2012年8月13日
   作    者   : L65478
   修改内容   : DTS2012080301606:注册失败后发起手动搜网失败
13.日    期   : 2012年12月6日
   作    者   : s00217060
   修改内容   : DTS2012120410842:不仅是指定搜网注册成功，其他情况注册成功时，也需要删除ForbPlmn,ForbLa,ForbGprs等信息
14.日    期   : 2013年1月11日
   作    者   : w00176964
   修改内容   : DTS2013010706662:调整发送EPLMN逻辑判断函数
15.日    期   : 2013年05月08日
   作    者   : s46746
   修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
16.日    期   : 2013年12月24日
    作    者   : z00161729
    修改内容   : SVLTE支持NCELL搜网
17.日    期   : 2014年01月10日
   作    者   : w00176964
   修改内容   : VoLTE_PhaseIII项目
18.日    期   : 2014年05月4日
   作    者   : w00176964
   修改内容   : V3R3C60_eCall项目调整
19.日    期   : 2014年11月3日
  作    者   : z00161729
  修改内容   : 开机漫游搜网项目修改
*****************************************************************************/
VOS_VOID NAS_MMC_ProcCsRegRslt_PlmnSelection(
    MMMMC_CS_REG_RESULT_IND_STRU       *pstCsRegRsltInd
)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;

    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;
    NAS_MMC_FSM_ID_ENUM_UINT32                              enCurrentFsmId;
    VOS_UINT32                                              ulCurrentEventType;

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
        NAS_MMC_SetCsRegCause_PlmnSelection(NAS_MML_REG_FAIL_CAUSE_NULL);

        enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;

        /* 根据注册结果更新注册信息表 */
        NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_CS, NAS_MML_REG_FAIL_CAUSE_NULL);

        /* 更新DPLMN NPLMN列表 */
        if (VOS_TRUE == NAS_MMC_IsRoam())
        {
            NAS_MMC_UpdateDPlmnNPlmnList(NAS_MML_GetCurrCampLai(), NAS_MMC_REG_DOMAIN_CS, NAS_MMC_MAX_CFG_DPLMN_NUM, &pstDPlmnNPlmnCfgInfo->usDplmnListNum, pstDPlmnNPlmnCfgInfo->astDPlmnList);
            NAS_MMC_DeleteDPlmnNPlmnList(NAS_MML_GetCurrCampLai(), NAS_MMC_REG_DOMAIN_CS, &pstDPlmnNPlmnCfgInfo->usNplmnListNum, pstDPlmnNPlmnCfgInfo->astNPlmnList);
            NAS_MMC_WriteSelfLearnDplmnNplmnToNvim(pstDPlmnNPlmnCfgInfo);
            NAS_MMC_LogDplmnNplmnList();
        }

        /* 注册成功时，清除GEO PLMN，下次再搜网时，可以直接搜RPLMN */
        NAS_MMC_InitGeoPlmn();

        /* 对Hplmn的Rej Lai信息的清除 */
        NAS_MMC_ClearHplmnRejDomainInfo(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_CS);

        /* 注册成功时，需要删除ForbPlmn,ForbLa,ForbGprs等信息 */
        NAS_MMC_DelForbInfo_GuRegRsltSucc(NAS_MMC_REG_DOMAIN_CS);

        NAS_MMC_SetUserSpecPlmnRegisterStatus(VOS_TRUE);

        NAS_MMC_UpdateCsRegStateCsRegSucc();

        /* Added by w00176964 for V3R3C60_eCall项目, 2014-5-4, begin */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_NORMAL_SERVICE);
        /* Added by w00176964 for V3R3C60_eCall项目, 2014-5-4, end */

#if   (FEATURE_ON == FEATURE_LTE)

        /* 联合注册时不通知LMM此时LU的结果 */
        if ((VOS_TRUE  == NAS_MML_IsRegFailCauseNotifyLmm(pstCsRegRsltInd->enRegFailCause))
         && (VOS_FALSE == pstCsRegRsltInd->ucIsComBined))
        {
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
        enAdditionalAction = NAS_MMC_ProcCsRegFail(MM_MMC_CS_REG_RESULT_IND, pstCsRegRsltInd);


        /* 若被拒原因值为#15, 则添加禁止网络信息到选网状态机的禁止漫游LA变量里去,
           当用户指定搜网时，则需要把禁止LA带给接入层 */
        enCurrentFsmId     = NAS_MMC_GetCurrFsmId();
        if (NAS_MMC_FSM_PLMN_SELECTION != enCurrentFsmId)
        {
            NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
        }
        ulCurrentEventType = NAS_MMC_GetCurrFsmEventType();
        if ( (VOS_TRUE == NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enCurrentFsmId, ulCurrentEventType))
          && (NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL == pstCsRegRsltInd->enRegFailCause) )
        {
            NAS_MML_AddForbRoamLa( NAS_MML_GetCurrCampLai(),
                                   NAS_MMC_GetForbRoamLaInfo_PlmnSelection() );
        }

        /* 如果还需要等待下一次注册结果,则不更新注册原因值,等待conut达到最大后更新,
           以便于用户指定搜网回复结果 */
        if ((NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT != enAdditionalAction)
         && (NAS_MMC_ADDITIONAL_ACTION_BUTT             != enAdditionalAction))
        {
            NAS_MMC_SetCsRegCause_PlmnSelection(pstCsRegRsltInd->enRegFailCause);
        }

        if ( VOS_TRUE == NAS_MML_IsNetworkRegFailCause(pstCsRegRsltInd->enRegFailCause) )
        {
            /* 只在跟网测真实发生交互的时候才更新注册信息表 */
            NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_CS, pstCsRegRsltInd->enRegFailCause);

            /* 更新DPLMN NPLMN列表 */
            if (VOS_TRUE == NAS_MMC_IsRoam())
            {
                NAS_MMC_UpdateDPlmnNPlmnList(NAS_MML_GetCurrCampLai(), NAS_MMC_REG_DOMAIN_CS, NAS_MMC_MAX_CFG_NPLMN_NUM, &pstDPlmnNPlmnCfgInfo->usNplmnListNum, pstDPlmnNPlmnCfgInfo->astNPlmnList);
                NAS_MMC_DeleteDPlmnNPlmnList(NAS_MML_GetCurrCampLai(), NAS_MMC_REG_DOMAIN_CS, &pstDPlmnNPlmnCfgInfo->usDplmnListNum, pstDPlmnNPlmnCfgInfo->astDPlmnList);
                NAS_MMC_WriteSelfLearnDplmnNplmnToNvim(pstDPlmnNPlmnCfgInfo);
                NAS_MMC_LogDplmnNplmnList();
            }
        }

        /* PS注册成功, CS注册失败, 原因为11 12 13 15的情况, 需要清除该标志.
           因为此时CS的 RPLMN没有更新为用户指定的PLMN, 此后丢网等触发的搜网不能搜
           RPLMN及其EPLMN, 故需要清除该标志. */

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
        NAS_MMC_SetCsRegAdditionalAction_PlmnSelection(enAdditionalAction);
    }

    if (VOS_TRUE == NAS_MMC_IsNeedSndEplmn_PlmnSelection())
    {
        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndGuAsEquPlmnReq(&stSndEquPlmnInfo, NAS_MML_GetCurrNetRatType());
        NAS_MMC_SndOmEquPlmn();
        /* 通知CSS GEO信息 */
        NAS_MMC_SndCssCurrGeoInd(VOS_TRUE, stSndEquPlmnInfo.ucEquPlmnNum, stSndEquPlmnInfo.astEquPlmnAddr);

        NAS_MMC_SndMsccEplmnInfoInd(&stSndEquPlmnInfo);
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcPsRegRslt_PlmnSelection
 功能描述  : 对Ps注册结果的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月23日
   作    者   : l00130025
   修改内容   : 新生成函数

 2.日    期   : 2011年11月14日
   作    者   : w00167002
   修改内容   : DTS2011110907180:当前若为选网状态机，则添加禁止网络信息
                到选网状态机的禁止漫游LA变量里去
 3.日    期   : 2011年12月5日
   作    者   : z00161729
   修改内容   : V7R1 Phase IV调整,当前SYSCFG中L不在时，也需要向LMM通知ID_MMC_LMM_ACTION_RESULT_REQ
 4.日    期   : 2011年11月28日
   作    者   : w00167002
   修改内容   : DTS2011112406707:若当前为假流程且当前的AdditionalAction不为
                初始无效值，则不更新当前的AdditionalAction的值，否则若当前为
                真流程或当前为假流程且AdditionalAction为初始无效值，则更新
                当前的AdditionalAction的值.
                修改原因:在ROAMING BROKER时候，设置1次失败,注册失败1次后，
                MMC需要搜网，但是MMC可能要等两个域的结果(如在选网状态机)，
                当收到系统消息的时候，假流程会更改MMC的AdditionalAction的值,
                导致ROMING BROKER特性失效。
 5.日    期   : 2011年12月5日
   作    者   : z00161729
   修改内容   : V7R1 Phase IV调整,当前SYSCFG中L不在时，也需要向LMM通知ID_MMC_LMM_ACTION_RESULT_REQ

 6.日    期   : 2012年1月3日
   作    者   : w00167002
   修改内容   : DTS2011122006209:g下PS ONLY注册成功_更改为CS后注册失败4次后未发起搜网
                统一调整注册ADDITIONAL ACTION的值，若是用户自定义的原因值(>=256)，则
                不保存注册结果。若当前支持L模，则注册原因值小于260时通知LMM当前的注册结果.
 7.日    期   : 2012年3月1日
   作    者   : w00176964
   修改内容   : DTS2012022407450:增加GMM的联合RAU/ATTACH类型，MMC转发给LMM
 8.日    期   : 2012年03月30日
   作    者   : l00130025
   修改内容   : DTS2012032307791,发给LMM注册结果,CombineReg时需要区分结果域
 9.日    期   : 2012年5月10日
   作    者   : l65478
   修改内容   : DTS2012050500988:CS注册成功时,不能删除forbid PLMN for GPRS信息
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
13.日    期   : 2012年8月13日
   作    者   : L65478
   修改内容   : DTS2012080301606:注册失败后发起手动搜网失败
14.日    期   : 2012年12月6日
   作    者   : s00217060
   修改内容   : DTS2012120410842:不仅是指定搜网注册成功，其他情况注册成功时，也需要删除ForbPlmn,ForbLa,ForbGprs等信息
15.日    期   : 2013年1月11日
   作    者   : w00176964
   修改内容   : DTS2013010706662:调整发送EPLMN逻辑判断函数
16.日    期   : 2013年05月08日
   作    者   : s46746
   修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
17.日    期   : 2013年12月24日
   作    者   : z00161729
   修改内容   : SVLTE支持NCELL搜网
18.日    期   : 2014年01月10日
   作    者   : w00176964
   修改内容   : VoLTE_PhaseIII项目
19.日    期   : 2014年05月4日
   作    者   : w00176964
   修改内容   : V3R3C60_eCall项目调整

*****************************************************************************/
VOS_VOID NAS_MMC_ProcPsRegRslt_PlmnSelection(
    GMMMMC_PS_REG_RESULT_IND_STRU      *pstPsRegRsltInd
)
{
    NAS_MML_LAI_STRU                                       *pstLai         = VOS_NULL_PTR;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;

    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;


    NAS_MMC_FSM_ID_ENUM_UINT32                              enCurrentFsmId;
    VOS_UINT32                                              ulCurrentEventType;

    NAS_MML_PLMN_ID_STRU                                   *pstForbPlmnForGprs = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                                   *pstCurrCampOnPlmn = VOS_NULL_PTR;

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

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-5-4, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-5-4, end */


    if (GMM_MMC_ACTION_RESULT_SUCCESS == pstPsRegRsltInd->enActionResult)
    {
        /* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-10, begin */
        /* 保存注册结果消息 */
        NAS_MMC_SaveRegRsltCtx(GMM_MMC_PS_REG_RESULT_IND, pstPsRegRsltInd);
        /* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-10, end */

        NAS_MMC_SetPsRegCause_PlmnSelection(NAS_MML_REG_FAIL_CAUSE_NULL);
        enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;

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


        /* 注册成功时，清除GEO PLMN，下次再搜网时，可以直接搜RPLMN */
        NAS_MMC_InitGeoPlmn();

        NAS_MMC_SetUserSpecPlmnRegisterStatus(VOS_TRUE);

        NAS_MMC_UpdatePsRegStatePsRegSucc();

        /* Added by w00176964 for V3R3C60_eCall项目, 2014-5-4, begin */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_NORMAL_SERVICE);
        /* Added by w00176964 for V3R3C60_eCall项目, 2014-5-4, end */

#if   (FEATURE_ON == FEATURE_LTE)

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


        /* 若被拒原因值为#15, 则添加禁止网络信息到选网状态机的禁止漫游LA变量里去,
           当用户指定搜网时，则需要把禁止LA带给接入层 */
        enCurrentFsmId     = NAS_MMC_GetCurrFsmId();
        if (NAS_MMC_FSM_PLMN_SELECTION != enCurrentFsmId)
        {
            NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
        }
        ulCurrentEventType = NAS_MMC_GetCurrFsmEventType();
        if ( (VOS_TRUE == NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enCurrentFsmId, ulCurrentEventType))
          && (NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL == pstPsRegRsltInd->enRegFailCause) )
        {
            NAS_MML_AddForbRoamLa( NAS_MML_GetCurrCampLai(),
                                   NAS_MMC_GetForbRoamLaInfo_PlmnSelection() );
        }

        if ( (VOS_TRUE == NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enCurrentFsmId, ulCurrentEventType))
          && (NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN == pstPsRegRsltInd->enRegFailCause) )
        {
            pstForbPlmnForGprs = NAS_MMC_GetForbPlmnForGrpsInfo_PlmnSelection();
            pstCurrCampOnPlmn  = NAS_MML_GetCurrCampPlmnId();

            *pstForbPlmnForGprs = *pstCurrCampOnPlmn;
        }

        /* 如果还需要等待下一次注册结果,则不更新注册原因值,等待conut达到最大后更新,
           以便于用户指定搜网回复结果 */
        if ((NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT != enAdditionalAction)
         && (NAS_MMC_ADDITIONAL_ACTION_BUTT             != enAdditionalAction))
        {
            NAS_MMC_SetPsRegCause_PlmnSelection(pstPsRegRsltInd->enRegFailCause);
        }

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
        NAS_MMC_SetPsRegAdditionalAction_PlmnSelection(enAdditionalAction);
    }

    if (VOS_TRUE == NAS_MMC_IsNeedSndEplmn_PlmnSelection())
    {
        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndGuAsEquPlmnReq(&stSndEquPlmnInfo, NAS_MML_GetCurrNetRatType());
        NAS_MMC_SndOmEquPlmn();
        /* 通知CSS GEO信息 */
        NAS_MMC_SndCssCurrGeoInd(VOS_TRUE, stSndEquPlmnInfo.ucEquPlmnNum, stSndEquPlmnInfo.astEquPlmnAddr);

        NAS_MMC_SndMsccEplmnInfoInd(&stSndEquPlmnInfo);
    }

    return;
}

#if (FEATURE_ON == FEATURE_DSDS)
/*****************************************************************************
 函 数 名  : NAS_MMC_SndMsccSrvAcqCnfAccordingPlmnSearchRslt
 功能描述  : 根据选网结果给mscc发送业务触发搜网结果
 输入参数  : enPlmnSelectionRslt - 搜网结果
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年7月2日
   作    者   : z00161729
   修改内容   : DSDS III新增
*****************************************************************************/
VOS_VOID  NAS_MMC_SndMsccSrvAcqCnfAccordingPlmnSearchRslt(
    NAS_MMC_PLMN_SELECTION_RESULT_ENUM_UINT32               enPlmnSelectionRslt
)
{
    /* 搜网结果成功且是正常服务则上报mma搜网结果为成功 */
    if ((VOS_TRUE == NAS_MMC_IsNormalServiceStatus())
     && (NAS_MMC_PLMN_SELECTION_SUCC == enPlmnSelectionRslt))
    {
        NAS_MMC_SndMsccSrvAcqCnf(NAS_MSCC_PIF_SRV_ACQ_RESULT_SUCCESS);
    }
    else
    {
        NAS_MMC_SndMsccSrvAcqCnf(NAS_MSCC_PIF_SRV_ACQ_RESULT_FAIL);
    }

    return;
}

#endif


/*****************************************************************************
 函 数 名  : NAS_MMC_GetCoverageRatNum_PlmnSelection
 功能描述  : 获取当前存在覆盖的接入技术个数
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月27日
    作    者   : w00167002
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_GetCoverageRatNum_PlmnSelection(VOS_VOID)
{
    NAS_MMC_RAT_SEARCH_INFO_STRU       *pstSearchRatInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList   = VOS_NULL_PTR;
    VOS_UINT32                          i;
    VOS_UINT32                          ulRatNum;

    pstSearchRatInfo    = NAS_MMC_GetSearchRatInfo_PlmnSelection();
    pstPrioRatList      = NAS_MML_GetMsPrioRatList();
    ulRatNum            = pstPrioRatList->ucRatNum;

    /* 在HISTORY搜网场景，获取当前存在的覆盖网络模式 */
    if (NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED_HISTORY_PLMN_SEARCH == NAS_MMC_GetPlmnSearchScene_PlmnSelection())
    {
        for (i = 0; i < NAS_MML_MAX_RAT_NUM; i++)
        {
            /* 进行过全频搜网且当前没有覆盖 */
            if ((VOS_TRUE == NAS_MML_IsNetRatSupported(pstSearchRatInfo[i].enRatType))
             && (VOS_TRUE == pstSearchRatInfo[i].ucHistorySearchedFlag)
             && (NAS_MMC_COVERAGE_TYPE_NONE == pstSearchRatInfo[i].enCoverageType))
            {
                ulRatNum--;
            }

            /* 增加异常保护 */
            if (0 == ulRatNum)
            {
                break;
            }
        }

        return ulRatNum;

    }


    /* 全频段搜网场景，获取当前存在覆盖的网络模式 */
    for (i = 0; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        /* 进行过全频搜网且当前没有覆盖 */
        if ((VOS_TRUE == NAS_MML_IsNetRatSupported(pstSearchRatInfo[i].enRatType))
         && (VOS_TRUE == pstSearchRatInfo[i].ucSearchAllBand)
         && (NAS_MMC_COVERAGE_TYPE_NONE == pstSearchRatInfo[i].enCoverageType))
        {
            ulRatNum--;
        }

        /* 增加异常保护 */
        if (0 == ulRatNum)
        {
            break;
        }
    }

    return ulRatNum;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_SndRslt_PlmnSelection
 功能描述  : 选网状态机中发送PlmnSelection的搜网的结果
 输入参数  : enPlmnSelectionRslt
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月11日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2011年12月14日
   作    者   : w00176964
   修改内容   : V7R1 phaseIV 调整:驻留标记通过新的搜网控制上下文代替

 3.日    期   : 2014年1月22日
   作    者   : w00167002
   修改内容   : 函数调整，将当前全频段搜网且存在覆盖的逻辑从NAS_MMC_SndPlmnSelectionRslt
                移动到当前函数，扩展NAS_MMC_SndPlmnSelectionRslt函数的复用性。
 4.日    期   : 2014年1月27日
   作    者   : s00246516
   修改内容   : L-C互操作项目:增加获取和注册请求的处理

 5.日    期   : 2014年5月28日
   作    者   : w00167002
   修改内容   : DTS2014051602857:sor定制打开，用户指定搜23002，CS注册被拒17，ps注册
                被拒17，达到最大次数后制定搜网失败。接着用户在指定搜23002，CS失败
                4次后，PS回复失败401，MMC不回复指定搜网结果。
 6.日    期   : 2014年6月17日
   作    者   : z00234330
   修改内容   : TQE清理
 7.日    期   : 2014年6月23日
   作    者   : z00161729
   修改内容   : DSDS III新增
 8.日    期   : 2015年6月6日
   作    者   : w00167002
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0项目修改
 9.日    期   : 2015年4月22日
   作    者   : wx270776
   修改内容   : DTS2015031602665:给MMA发送Reg CNF消息时增加CL ATTACH注册状态
*****************************************************************************/
VOS_VOID  NAS_MMC_SndRslt_PlmnSelection(
    NAS_MMC_PLMN_SELECTION_RESULT_ENUM_UINT32               enPlmnSelectionRslt
)
{

    NAS_MMC_RAT_SEARCH_INFO_STRU           *pstSearchRatInfo = VOS_NULL_PTR;
    VOS_UINT32                              ulCampFlg;
    VOS_UINT32                              ulRatNum;

    /* Added by s00246516 for L-C互操作项目, 2014-01-28, Begin */
    MSCC_MMC_PLMN_ID_STRU                   stPlmnId;
    VOS_UINT32                              ulCurrentEventType;
    /* Added by s00246516 for L-C互操作项目, 2014-01-28, End */

    NAS_MMC_FSM_ID_ENUM_UINT32              enCurrentFsmId;

    /* Added by c00318887 for 预置频点搜网优化, 2015-9-2, begin */
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32   ulPlmnSearchScene;
    /* Added by c00318887 for 预置频点搜网优化, 2015-9-2, end */

    pstSearchRatInfo    = NAS_MMC_GetSearchRatInfo_PlmnSelection();

    enCurrentFsmId     = NAS_MMC_GetCurrFsmId();

    NAS_MMC_LogFsmPlmnSelectionCtxRelatedInfo(NAS_MMC_GetPlmnSelectionCtx_PlmnSelection());

    if (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == NAS_MMC_GetSpecPlmnSearchState())
    {
        ulCampFlg = VOS_FALSE;
    }
    else
    {
        ulCampFlg = VOS_TRUE;
    }

    /* Added by s00246516 for L-C互操作项目, 2014-01-28, Begin */
    stPlmnId.ulMcc     = NAS_MML_INVALID_MCC;
    stPlmnId.ulMnc     = NAS_MML_INVALID_MNC;
    ulCurrentEventType = NAS_MMC_GetCurrFsmEventType();

    /* 如果是获取网络操作，发送获取网络失败回复消息 */
    if (NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_ACQ_REQ) == ulCurrentEventType)
    {
        NAS_MMC_SndMsccAcqCnf(NAS_MSCC_PIF_ACQ_RESULT_FAILURE, &stPlmnId, 0);
    }

    /* Modified by z00234330 for coverity清理, 2014-06-16, begin */
    if (NAS_MMC_FSM_PLMN_SELECTION != enCurrentFsmId)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }
    /* Modified by z00234330 for coverity清理, 2014-06-16, end */


#if (FEATURE_ON == FEATURE_DSDS)
    if (VOS_TRUE == NAS_MMC_GetSrvTrigPlmnSearchFlag_PlmnSelection())
    {
        NAS_MMC_SndMsccSrvAcqCnfAccordingPlmnSearchRslt(enPlmnSelectionRslt);
    }
#endif

    /* 增加手动搜网异常处理，直接回复搜网失败 */
    if (VOS_TRUE == NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enCurrentFsmId, ulCurrentEventType))
    {
        NAS_MMC_SndMsccUserSpecPlmnSearchCnf(NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_FAIL);

        /*更新入口消息为普通的搜网请求，后续有新的用户请求时，可以打断该状态机*/
        NAS_MMC_SaveCommonPlmnSrchEntryMsg_PlmnSelection();

    #if (FEATURE_ON == FEATURE_LTE)
        if ( VOS_TRUE == NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_LTE))
        {
            NAS_MMC_SndLmmUserSpecPlmnSearchEndNotify();
        }
    #endif

        NAS_MMC_SndRrMmCellSelReq(RRC_NAS_FORBLA_CHANGE);
    }

    /* 如果是注册操作，发送注册回复消息 */
    if (VOS_TRUE == NAS_MMC_IsMsccRegReq_PlmnSelection())
    {
        if (VOS_TRUE == NAS_MMC_IsNormalServiceStatus())
        {
            NAS_MMC_SndMsccRegCnf(NAS_MMC_GetLmmAttachClRegStatus_PlmnSelection(), NAS_MSCC_PIF_REG_RESULT_SUCCESS, NAS_MML_GetCurrCampPlmnId(),
                                 NAS_MML_GetCurrCampArfcn());
        }
        else
        {
            if (VOS_TRUE == ulCampFlg)
            {
                NAS_MMC_SndMsccRegCnf(NAS_MMC_GetLmmAttachClRegStatus_PlmnSelection(), NAS_MSCC_PIF_REG_RESULT_REG_FAILURE, NAS_MML_GetCurrCampPlmnId(),
                                 NAS_MML_GetCurrCampArfcn());
            }
            else
            {
                NAS_MMC_SndMsccRegCnf(NAS_MMC_GetLmmAttachClRegStatus_PlmnSelection(), NAS_MSCC_PIF_REG_RESULT_ACQ_FAILURE, &stPlmnId, 0x0);
            }
        }
    }

    /* 清除标志 */
    NAS_MMC_SetLmmAttachClRegStatus_PlmnSelection(MMC_LMM_ATT_RSLT_BUTT);
    /* Added by s00246516 for L-C互操作项目, 2014-01-28, End */

    ulRatNum = NAS_MMC_GetCoverageRatNum_PlmnSelection();

    /* Modified by c00318887 for 预置频点搜网优化, 2015-9-2, begin */
    ulPlmnSearchScene = NAS_MMC_GetPlmnSearchScene_PlmnSelection();

    NAS_MMC_SndPlmnSelectionRslt(enPlmnSelectionRslt, ulCampFlg, pstSearchRatInfo, ulRatNum, ulPlmnSearchScene);
    /* Modified by c00318887 for 预置频点搜网优化, 2015-9-2, end */


    return;
}

#if   (FEATURE_ON == FEATURE_LTE)

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcLmmCombinedAttachInd_AttRsltSucc_PlmnSelection
 功能描述  : Lmm combined attach EPS和CS成功注册的处理函数
 输入参数  : pstLmmAttachIndMsg - ID_LMM_MMC_ATTACH_IND消息的首地址
             enCsRegRsltCause -  cs域被拒原因值
 输出参数  : penCsAddition    - CS域的后续动作
             penPsAddition    - PS域的后续动作
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月8日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年5月7日
    作    者   : w00166186
    修改内容   : DTS20120050302236:手动搜网指定的网络在禁止列表中，注册成功后，
                 没有向LMM发送等效PLMN
  3.日    期   : 2012年5月10日
    作    者   : l65478
    修改内容   : DTS2012050500988:CS注册成功时,不能删除forbid PLMN for GPRS信息
  4.日    期   : 2012年6月4日
    作    者   : l00171473
    修改内容   : DTS2012053003921, 用户手动指定网络的注册状态标志清理
  5.日    期   : 2012年6月8日
    作    者   : l00130025
    修改内容   : DTS2012060702423:Anycell驻留后，注册成功时，没有通知通知APS/CDS消息，无法数传
  6.日    期   : 2012年6月11日
    作    者   : s46746
    修改内容   : For CS/PS mode 1,联合TAU成功时，需要Disable L
  7.日    期   : 2012年7月27日
    作    者   : s00217060
    修改内容   : For CS/PS mode 1,带Disable LTE原因值
  8.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  9.日    期   : 2013年12月10日
    作    者   : w00176964
    修改内容   : VoLTE_PhaseIII 项目:修改Disable L模的逻辑
 10.日    期   : 2015年05月11日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseII 项目修改
 11.日    期   : 2015年10月14日
    作    者   : c00318887
    修改内容   : DTS2015082002854: 漫游标记不准
*****************************************************************************/
VOS_VOID  NAS_MMC_ProcLmmCombinedAttachInd_AttRsltSucc_PlmnSelection(
    LMM_MMC_ATTACH_IND_STRU                                *pstLmmAttachIndMsg,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsRegRsltCause,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsAddition,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsAddition
)
{
    if (VOS_TRUE == pstLmmAttachIndMsg->bitOpCnRslt)
    {
        if (MMC_LMM_ATT_CN_RSLT_COMBINED_EPS_IMSI == pstLmmAttachIndMsg->ulCnRslt)
        {
            NAS_MMC_ProcLmmCombinedAttachInd_AttRsltCsEpsSucc(pstLmmAttachIndMsg,
                          penCsAddition, penPsAddition);
        }
        else if (MMC_LMM_ATT_CN_RSLT_EPS_ONLY == pstLmmAttachIndMsg->ulCnRslt)
        {
            NAS_MMC_ProcLmmCombinedAttachInd_AttRsltEpsOnlySucc(pstLmmAttachIndMsg,enCsRegRsltCause,
                          penCsAddition, penPsAddition);
        }
        else
        {
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcLmmCombinedAttachInd_AttRsltSucc_PlmnSelection:Unexpected cn result!");
        }
    }
    else
    {
        /* 设置当前注册状态为成功 */
        NAS_MMC_SetUserSpecPlmnRegisterStatus(VOS_TRUE);

        /* 假流程注册成功上报正常服务返回 */
        *penPsAddition = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;

        /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-12, begin */
        *penCsAddition = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;
        /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-12, end */

        NAS_MMC_UpdateServiceState_RegSucc(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NORMAL_SERVICE);



        /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, begin */
        NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, VOS_TRUE, NAS_MML_REG_FAIL_CAUSE_NULL);
        /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, end */
    }


    NAS_MMC_NotifyModeChange(NAS_MML_GetCurrNetRatType(),
                             NAS_MML_GetSimPsRegStatus());


    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ProcLmmCombinedAttachInd_PlmnSelection
 功能描述  : Lmm combined attach结果的处理函数
 输入参数  : pstLmmAttachIndMsg - ID_LMM_MMC_ATTACH_IND消息的首地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月25日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2011年12月8日
    作    者   : w00176964
    修改内容   : V7R1 PhaseIV 调整
  3.日    期   : 2011年12月13日
    作    者   : z00161729
    修改内容   : DTS2011121302231:attach被拒#9/#10按协议应该按other cause处理
  4.日    期   : 2012年2月4日
    作    者   : w00167002
    修改内容   : DTS2011122704039:将注册结果类型以及注册消息传递给处理注册结果
                  函数，扩展注册结果函数的处理能力。
                  additional action值若为无效值NAS_MMC_ADDITIONAL_ACTION_BUTT
                  则不更新当前的additional action
  5.日    期   : 2012年5月7日
    作    者   : w00166186
    修改内容   : DTS20120050302236:手动搜网指定的网络在禁止列表中，注册成功后，
                 没有向LMM发送等效PLMN
  6.日    期   : 2012年5月10日
    作    者   : l65478
    修改内容   : DTS2012050500988:CS注册成功时,不能删除forbid PLMN for GPRS信息
  7.日    期   : 2012年06月01日
    作    者   : sunxibo /46746
    修改内容   : Added for V7R1 C50 CS/PS mode 1
  8.日    期   : 2012年6月30日
    作    者   : w00176964
    修改内容   : DTS2012063003332:联合注册单域成功,原因值不在协议规定的列表里,LNAS
                 给的结果为CN_REJ,此时不应该删除禁止列表
  9.日    期   : 2012年08月20日
    作    者   : l65478
    修改内容   : DTS2012081703289，手动搜网失败后关机，重新开机注册成功
                   后出服务区后不驻留EPLMN上
  10.日    期   : 2012年8月21日
    作    者   : z00161729
    修改内容   : DCM定制需求和遗留问题修改DTS2012090401249
  11.日    期   : 2013年1月11日
    作    者   : w00176964
    修改内容   : DTS2013010706662:调整发送EPLMN逻辑判断函数
 12.日    期   : 2014年5月5日
  作    者   : w00242748
  修改内容   : DTS2014043000311:注册状态服务状态不一致，将MMC中报服务状态的场景，都加
               注册状态的上报。
*****************************************************************************/
VOS_VOID  NAS_MMC_ProcLmmCombinedAttachInd_PlmnSelection(
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
            NAS_MMC_ProcLmmCombinedAttachInd_AttRsltSucc_PlmnSelection(pstLmmAttachIndMsg,
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
            }
            else
            {
                NAS_MMC_ProcCombinedAttachEpsRegFail(LMM_MMC_ATTACH_IND, pstLmmAttachIndMsg,
                                      &enPsAdditionalAction, &enCsAdditionalAction);
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
            NAS_MMC_ProcCombinedAttachEpsRegFail(LMM_MMC_ATTACH_IND, pstLmmAttachIndMsg,
                                  &enPsAdditionalAction, &enCsAdditionalAction);
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
                NAS_MMC_ProcCombinedAttachEpsRegFail(LMM_MMC_ATTACH_IND, pstLmmAttachIndMsg,
                                      &enPsAdditionalAction, &enCsAdditionalAction);
            }
            break;

        default:
            /* 异常打印 */
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcLmmCombinedAttachInd_PlmnSelection:Unexpected attach result!");
            enPsAdditionalAction = NAS_MMC_GetPsRegAdditionalAction_PlmnSelection();
            enCsAdditionalAction = NAS_MMC_GetCsRegAdditionalAction_PlmnSelection();
            break;
    }

    /* AdditionalAction有效，更新EPS的下一步的动作类型 */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enPsAdditionalAction )
    {
        NAS_MMC_SetPsRegAdditionalAction_PlmnSelection(enPsAdditionalAction);
    }

    /* AdditionalAction有效，更新CS的下一步的动作类型 */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enCsAdditionalAction )
    {
        NAS_MMC_SetCsRegAdditionalAction_PlmnSelection(enCsAdditionalAction);
    }

    /* 如果还需要等待下一次注册结果,则不更新注册原因值,等待conut达到最大后更新,
       以便于用户指定搜网回复结果 */
    if (NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT != enPsAdditionalAction)
    {
        NAS_MMC_SetPsRegCause_PlmnSelection(enPsRegRsltCause);
    }

    if (VOS_TRUE == NAS_MMC_IsNeedSndEplmn_PlmnSelection())
    {
        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, begin */
        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildSndLmmEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndLmmEquPlmnReq(&stSndEquPlmnInfo);
        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, end */

        /* 通知CSS GEO信息 */
        NAS_MMC_SndCssCurrGeoInd(VOS_TRUE, stSndEquPlmnInfo.ucEquPlmnNum, stSndEquPlmnInfo.astEquPlmnAddr);

        NAS_MMC_SndOmEquPlmn();
    }


    NAS_MMC_UpdateUserSpecPlmnRegisterStatus(enPsRegRsltCause);

    return;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcLmmMmcEpsOnlyAttachInd_PlmnSelection
 功能描述  : Lmm attach结果的处理函数
 输入参数  : ID_LMM_MMC_ATTACH_IND消息的首地址
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月20日
    作    者   : W00167002
    修改内容   : 新生成函数
  2.日    期   : 2011年7月24日
    作    者   : l00130025
    修改内容   : PhaseII修改
  3.日    期   : 2011年10月30日
    作    者   : z00161729
    修改内容   : PhaseIII修改函数名
  4.日    期   : 2011年12月5日
    作    者   : z00161729
    修改内容   : V7R1 phaseIV修改合并原NAS_MMC_HPLMN_REG_REJ_STRU和NAS_MMC_PLMN_REG_INFO_STRU
  5.日    期   : 2011年12月14日
    作    者   : w00176964
    修改内容   : V7R1 phaseIV调整:EPS单域注册假流程调整
  6.日    期   : 2011年12月15日
    作    者   : w00167002
    修改内容   : DTS2011121307570: MMC没有维护LMM的EPLMN信息，现在统一调整
                  ATTACH/TAU/DETACH/SERVICE中被拒时EPLMN的维护。
                  将函数名由NAS_MMC_ProcEpsRegFail更改为NAS_MMC_ProcEpsAttachRegFail
                  调用ATTACH的注册原因值表进行处理。
  7.日    期   : 2012年1月8日
    作    者   : z00161729
    修改内容   : V7R1 phaseIV调整:EPS单域注册假流程调整
  8.日    期   : 2012年2月4日
    作    者   : w00167002
    修改内容   : DTS2011122704039:将注册结果类型以及注册消息传递给处理注册结果
                  函数，扩展注册结果函数的处理能力。
                  additional action值若为无效值NAS_MMC_ADDITIONAL_ACTION_BUTT
                 则不更新当前的additional action
  9.日    期   : 2012年5月7日
    作    者   : w00166186
    修改内容   : DTS20120050302236:手动搜网指定的网络在禁止列表中，注册成功后，
                 没有向LMM发送等效PLMN
 10.日    期   : 2012年5月10日
    作    者   : l65478
    修改内容   : DTS2012050500988:CS注册成功时,不能删除forbid PLMN for GPRS信息
 11.日    期   : 2012年06月01日
    作    者   : s46746
    修改内容   : Added for V7R1 C50 CS/PS mode 1
 12.日    期   : 2012年06月01日
    作    者   : s00217060
    修改内容   : Added for V7R1 C50 CS/PS mode 1
 13.日    期   : 2012年6月4日
    作    者   : l00171473
    修改内容   : DTS2012053003921, 用户手动指定网络的注册状态标志清理
 14.日    期   : 2012年7月27日
    作    者   : s00217060
    修改内容   : For CS/PS mode 1,带Disable LTE原因值
 15.日    期   : 2012年08月20日
    作    者   : l65478
    修改内容   : DTS2012081703289，手动搜网失败后关机，重新开机注册成功
                   后出服务区后不驻留EPLMN上
 16.日    期   : 2012年8月21日
    作    者   : z00161729
    修改内容   : DCM定制需求和遗留问题修改DTS2012090401249
 17.日    期   : 2012年12月6日
    作    者   : s00217060
    修改内容   : DTS2012120410842:不仅是指定搜网注册成功，其他情况注册成功时，也需要删除ForbPlmn,ForbLa,ForbGprs等信息
18.日    期   : 2013年1月11日
   作    者   : w00176964
   修改内容   : DTS2013010706662:调整发送EPLMN逻辑判断函数
19.日    期   : 2013年05月08日
   作    者   : s46746
   修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
20.日    期   : 2013年12月10日
   作    者   : w00176964
   修改内容   : VoLTE_PhaseIII 项目:修改Disable L模的逻辑
21.日    期   : 2014年5月6日
   作    者   : z00161729
   修改内容   : DTS2014050602850:l下联合注册eps成功，cs注册被#18拒绝，disable lte到gu下搜网注册成功，后指定搜l cs注册被#18拒绝的网络，l发起eps单域注册成功，mmc没有disable lte
22.日    期   : 2014年5月5日
   作    者   : w00242748
   修改内容   : DTS2014043000311:注册状态服务状态不一致，将MMC中报服务状态的场景，都加
                注册状态的上报。
23.日    期   : 2015年02月11日
   作    者   : l00305157
   修改内容   : Service_State_Optimize_PhaseII 项目修改
                    MMC接收到LMM模块注册结果ATTACH (EPS ONLY)成功，上报注册状态
24.日    期   : 2015年06月09日
   作    者   : l00305157
   修改内容   : Service_State_Optimize_PhaseII 项目修改
                    MMC接收到LMM模块注册结果，先更新EPLMN LIST，在处理注册状态的上报
 25.日    期   : 2015年10月14日
    作    者   : c00318887
    修改内容   : DTS2015082002854: 漫游标记不准
*****************************************************************************/
VOS_VOID  NAS_MMC_ProcLmmMmcEpsOnlyAttachInd_PlmnSelection(
    LMM_MMC_ATTACH_IND_STRU            *pstLmmAttachIndMsg
)
{
    VOS_UINT32                          ulEquPlmnNum;
    MMC_LMM_PLMN_ID_STRU               *pstLmmEquPlmnList = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU           stLEplmnInfo;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enRegRsltCause;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enAdditionalAction;

    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, begin */
    NAS_MML_EQUPLMN_INFO_STRU          *pstEquPlmnInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU           stSndEquPlmnInfo;
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, end */
    VOS_UINT8                           ucSimCsRegStatus;

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));

    NAS_MMC_ConverLmmAttachRsltToMMLCause(pstLmmAttachIndMsg, &enRegRsltCause);

    if (MMC_LMM_ATT_RSLT_SUCCESS == pstLmmAttachIndMsg->ulAttachRslt)
    {
        enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;

        NAS_MMC_SaveRegRsltCtx(LMM_MMC_ATTACH_IND, pstLmmAttachIndMsg);

        /* 根据注册结果更新注册信息表 */
        NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_EPS, NAS_MML_REG_FAIL_CAUSE_NULL);

        /*注意: 需要先更新EPLMN LIST，在处理注册状态的上报,因为NAS_MMC_UpdatePsRegStatePsRegSucc()函数中会根据EPLMN LIST上报注册状态 */
        /* 更新EPLMN */
        if (VOS_TRUE == pstLmmAttachIndMsg->bitOpEplmn)
        {
            ulEquPlmnNum        = pstLmmAttachIndMsg->stEplmnList.ulPlmnNum;
            pstLmmEquPlmnList   = pstLmmAttachIndMsg->stEplmnList.astEplmnList;

            /* 将LMM的PLMN ID格式转换为GU的格式 */
            NAS_MMC_ConvertLmmPlmnToGUNasPlmn(ulEquPlmnNum, pstLmmEquPlmnList, (stLEplmnInfo.astEquPlmnAddr));
            NAS_MML_SaveEquPlmnList(ulEquPlmnNum, stLEplmnInfo.astEquPlmnAddr);

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


        /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, begin */
        NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_PS, VOS_TRUE, NAS_MML_REG_FAIL_CAUSE_NULL);
        /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, end */

        NAS_MMC_SetUserSpecPlmnRegisterStatus(VOS_TRUE);

        /* Added by w00176964 for APS服务状态通知清理, 2014-4-7, begin */
        NAS_MMC_NotifyModeChange(NAS_MML_GetCurrNetRatType(),
                                  NAS_MML_GetSimPsRegStatus());
        /* Added by w00176964 for APS服务状态通知清理, 2014-4-7, end */
    }
    else if ((MMC_LMM_ATT_RSLT_FAILURE == pstLmmAttachIndMsg->ulAttachRslt)
          && (VOS_FALSE == pstLmmAttachIndMsg->bitOpAtmpCnt))
    {
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
        NAS_MMC_SetPsRegAdditionalAction_PlmnSelection(enAdditionalAction);
    }

    /* 如果还需要等待下一次注册结果,则不更新注册原因值,等待conut达到最大后更新,
       以便于用户指定搜网回复结果 */
    if (NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT != enAdditionalAction)
    {
        NAS_MMC_SetPsRegCause_PlmnSelection(enRegRsltCause);
    }

    if (VOS_TRUE == NAS_MMC_IsNeedSndEplmn_PlmnSelection())
    {
        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, begin */
        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildSndLmmEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndLmmEquPlmnReq(&stSndEquPlmnInfo);
        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, end */
        /* 通知CSS GEO信息 */
        NAS_MMC_SndCssCurrGeoInd(VOS_TRUE, stSndEquPlmnInfo.ucEquPlmnNum, stSndEquPlmnInfo.astEquPlmnAddr);

        NAS_MMC_SndOmEquPlmn();
    }

    return ;

}


/*****************************************************************************
 函 数 名  : NAS_MMC_ProcLmmAttachInd_PlmnSelection
 功能描述  : 根据lmm的attach请求类型处理attach_ind消息
 输入参数  : pstLmmAttachIndMsg - lmm attach ind消息内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月28日
    作    者   : z00161729
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_MMC_ProcLmmAttachInd_PlmnSelection(
    LMM_MMC_ATTACH_IND_STRU            *pstLmmAttachIndMsg
)
{
    switch (pstLmmAttachIndMsg->ulReqType)
    {
        case MMC_LMM_ATT_TYPE_COMBINED_EPS_IMSI:

            /* 处理lmm的联合attach结果 */
            NAS_MMC_ProcLmmCombinedAttachInd_PlmnSelection(pstLmmAttachIndMsg);
            break;

        case MMC_LMM_ATT_TYPE_EPS_ONLY:

            /* 处理lmm的非联合attach，EPS only注册的结果 */
            NAS_MMC_ProcLmmMmcEpsOnlyAttachInd_PlmnSelection(pstLmmAttachIndMsg);
            break;

        case MMC_LMM_ATT_TYPE_EPS_EMERGENCY:

            /* 暂不支持未实现 */
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcLmmAttachInd_PlmnSelection:Unsupported attach req type!");
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcLmmAttachInd_PlmnSelection:Unexpected attach req type!");
            break;

    }
    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ProcLmmEpsOnlyTauResultInd_PlmnSelection
 功能描述  : Lmm TAU结果的处理函数
 输入参数  : ID_LMM_MMC_ATTACH_IND消息的首地址
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月20日
    作    者   : W00167002
    修改内容   : 新生成函数
  2.日    期   : 2011年7月24日
    作    者   : l00130025
    修改内容   : PhaseII修改
  3.日    期   : 2011年10月30日
    作    者   : z00161729
    修改内容   : PhaseIII修改函数名
  4.日    期   : 2011年12月5日
    作    者   : z00161729
    修改内容   : V7R1 phaseIV修改合并原NAS_MMC_HPLMN_REG_REJ_STRU和NAS_MMC_PLMN_REG_INFO_STRU
  5.日    期   : 2011年12月15日
    作    者   : w00167002
    修改内容   : DTS2011121307570: MMC没有维护LMM的EPLMN信息，现在统一调整
                  ATTACH/TAU/DETACH/SERVICE中被拒时EPLMN的维护。
                  将函数名由NAS_MMC_ProcEpsRegFail更改为NAS_MMC_ProcEpsTauRegFail
                  调用TAU的注册原因值表进行处理。
  6.日    期   : 2012年1月8日
    作    者   : z00161729
    修改内容   : V7R1 phaseIV调整:EPS单域注册假流程调整
  7.日    期   : 2012年2月4日
    作    者   : w00167002
    修改内容   : DTS2011122704039:将注册结果类型以及注册消息传递给处理注册结果
                  函数，扩展注册结果函数的处理能力.
                  additional action值若为无效值NAS_MMC_ADDITIONAL_ACTION_BUTT
                 则不更新当前的additional action
  8.日    期   : 2012年5月7日
    作    者   : w00166186
    修改内容   : DTS20120050302236:手动搜网指定的网络在禁止列表中，注册成功后，
                 没有向LMM发送等效PLMN
  9.日    期   : 2012年5月10日
    作    者   : l65478
    修改内容   : DTS2012050500988:CS注册成功时,不能删除forbid PLMN for GPRS信息
 10.日    期   : 2012年06月01日
    作    者   : s46746
    修改内容   : Added for V7R1 C50 CS/PS mode 1
 11.日    期   : 2012年06月01日
    作    者   : s00217060
    修改内容   : Added for V7R1 C50 CS/PS mode 1
 12.日    期   : 2012年6月4日
    作    者   : l00171473
    修改内容   : DTS2012053003921, 用户手动指定网络的注册状态标志清理
 13.日    期   : 2012年7月27日
    作    者   : s00217060
    修改内容   : For CS/PS mode 1,带Disable LTE原因值
 14.日    期   : 2012年08月20日
    作    者   : l65478
    修改内容   : DTS2012081703289，手动搜网失败后关机，重新开机注册成功
                   后出服务区后不驻留EPLMN上
 15.日    期   : 2012年8月21日
    作    者   : z00161729
    修改内容   : DCM定制需求和遗留问题修改DTS2012090401249
 16.日    期   : 2012年12月6日
    作    者   : s00217060
    修改内容   : DTS2012120410842:不仅是指定搜网注册成功，其他情况注册成功时，也需要删除ForbPlmn,ForbLa,ForbGprs等信息
 17.日    期   : 2013年1月11日
    作    者   : w00176964
    修改内容   : DTS2013010706662:调整发送EPLMN逻辑调用位置
 18.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
 19.日    期   : 2013年12月10日
     作    者  : w00176964
     修改内容  : VoLTE_PhaseIII 项目:修改Disable L模的逻辑
 20.日    期   : 2014年5月6日
    作    者   : z00161729
    修改内容   : DTS2014050602850:l下联合注册eps成功，cs注册被#18拒绝，disable lte到gu下搜网注册成功，后指定搜l cs注册被#18拒绝的网络，l发起eps单域注册成功，mmc没有disable lte
 21.日    期   : 2014年5月5日
    作    者   : w00242748
    修改内容   : DTS2014043000311:注册状态服务状态不一致，将MMC中报服务状态的场景，都加
                 注册状态的上报。
 22.日    期   : 2014年5月14日
    作    者   : w00242748
    修改内容   : DTS2014051206381:枚举值使用不对
 23.日    期   : 2015年4月18日
    作    者   : z00161729
    修改内容   : 24301 R11 CR升级项目修改
 24.日    期   : 2015年02月11日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseII 项目修改
                    MMC接收到LMM模块注册结果(EPS ONLY)成功，上报注册状态
 25.日    期   : 2015年06月09日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseII 项目修改
                    MMC接收到LMM模块注册结果，先更新EPLMN LIST，在处理注册状态的上报
 26.日    期   : 2015年10月14日
    作    者   : c00318887
    修改内容   : DTS2015082002854: 漫游标记不准
*****************************************************************************/
VOS_VOID  NAS_MMC_ProcLmmEpsOnlyTauResultInd_PlmnSelection(
    LMM_MMC_TAU_RESULT_IND_STRU        *pstLmmTauIndMsg
)
{
    VOS_UINT32                          ulEquPlmnNum;
    MMC_LMM_PLMN_ID_STRU               *pstLmmEquPlmnList = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU           stLEplmnAddr;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enRegRsltCause;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enAdditionalAction;

    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, begin */
    NAS_MML_EQUPLMN_INFO_STRU          *pstEquPlmnInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU           stSndEquPlmnInfo;
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, end */
    VOS_UINT8                           ucSimCsRegStatus;

    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8          enCsRegAdditionalAction;

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));

    NAS_MMC_ConverTauResultToMMLCause(pstLmmTauIndMsg, &enRegRsltCause);

    if (MMC_LMM_TAU_RSLT_SUCCESS == pstLmmTauIndMsg->ulTauRst)
    {
        enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;

        /* 保存注册结果消息 */
        NAS_MMC_SaveRegRsltCtx(LMM_MMC_TAU_RESULT_IND, pstLmmTauIndMsg);

        /* 根据注册结果更新注册信息表 */
        NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_EPS, NAS_MML_REG_FAIL_CAUSE_NULL);

        /*注意: 需要先更新EPLMN LIST，在处理注册状态的上报,因为NAS_MMC_UpdatePsRegStatePsRegSucc()函数中会根据EPLMN LIST上报注册状态 */
        /* 更新EPLMN */
        if (VOS_TRUE == pstLmmTauIndMsg->bitOpEplmn)
        {
            ulEquPlmnNum        = pstLmmTauIndMsg->stEplmnList.ulPlmnNum;
            pstLmmEquPlmnList   = pstLmmTauIndMsg->stEplmnList.astEplmnList;

            /* 将LMM的PLMN ID格式转换为MMC的格式 */
            NAS_MMC_ConvertLmmPlmnToGUNasPlmn(ulEquPlmnNum, pstLmmEquPlmnList, (stLEplmnAddr.astEquPlmnAddr));

            NAS_MML_SaveEquPlmnList(ulEquPlmnNum, stLEplmnAddr.astEquPlmnAddr);

            NAS_MMC_WriteEplmnNvim();
        }

        NAS_MMC_UpdateServiceState_RegSucc(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_NORMAL_SERVICE);

        /* EPS单域注册成功时，需要删除ForbPlmn,ForbGprs等信息 */
        NAS_MMC_DelForbInfo_LmmAttRsltSucc(VOS_NULL_PTR, VOS_FALSE);

        /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, begin */
        /* 此处更新CS addition原因是联合TAU仅EPS成功时,LMM启动T3411再次尝试TAU过程中,
           用户Detach CS,LMM会直接报TAU成功,不再尝试联合TAU */
        NAS_MMC_SetCsRegAdditionalAction_PlmnSelection(NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON);

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

        /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, begin */
        NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_PS, VOS_TRUE, NAS_MML_REG_FAIL_CAUSE_NULL);
        /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, end */

        NAS_MMC_SetUserSpecPlmnRegisterStatus(VOS_TRUE);

        /* Added by w00176964 for APS服务状态通知清理, 2014-4-7, begin */
        NAS_MMC_NotifyModeChange(NAS_MML_GetCurrNetRatType(),
                                  NAS_MML_GetSimPsRegStatus());
        /* Added by w00176964 for APS服务状态通知清理, 2014-4-7, end */
    }
    else if ((MMC_LMM_TAU_RSLT_FAILURE == pstLmmTauIndMsg->ulTauRst)
          && (VOS_FALSE == pstLmmTauIndMsg->bitOpAtmpCnt))
    {
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

    /* 如果还需要等待下一次注册结果,则不更新注册原因值,等待conut达到最大后更新,
       以便于用户指定搜网回复结果 */
    if (NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT != enAdditionalAction)
    {
        NAS_MMC_SetPsRegCause_PlmnSelection(enRegRsltCause);
    }

    /* AdditionalAction有效，更新EPS的下一步的动作类型 */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enAdditionalAction )
    {
        NAS_MMC_SetPsRegAdditionalAction_PlmnSelection(enAdditionalAction);
    }

    if (VOS_TRUE == NAS_MMC_IsNeedSndEplmn_PlmnSelection())
    {
        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, begin */
        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildSndLmmEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndLmmEquPlmnReq(&stSndEquPlmnInfo);
        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, end */
        /* 通知CSS GEO信息 */
        NAS_MMC_SndCssCurrGeoInd(VOS_TRUE, stSndEquPlmnInfo.ucEquPlmnNum, stSndEquPlmnInfo.astEquPlmnAddr);

        NAS_MMC_SndOmEquPlmn();
    }

    return ;

}


/*****************************************************************************
 函 数 名  : NAS_MMC_ProcLmmCombinedTauResultInd_TauRsltSucc_PlmnSelection
 功能描述  : Lmm TAU result结果为MMC_LMM_TAU_RSLT_SUCCESS的处理函数
 输入参数  : ID_LMM_MMC_TAU_RESULT_IND消息的首地址
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月07日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年5月7日
    作    者   : w00166186
    修改内容   : DTS20120050302236:手动搜网指定的网络在禁止列表中，注册成功后，
                 没有向LMM发送等效PLMN
  3.日    期   : 2012年5月10日
    作    者   : l65478
    修改内容   : DTS2012050500988:CS注册成功时,不能删除forbid PLMN for GPRS信息
  4.日    期   : 2012年6月4日
    作    者   : l00171473
    修改内容   : DTS2012053003921, 用户手动指定网络的注册状态标志清理
  5.日    期   : 2012年6月8日
    作    者   : l00130025
    修改内容   : DTS2012060702423:Anycell驻留后，注册成功时，没有通知通知APS/CDS消息，无法数传
  6.日    期   : 2012年6月11日
    作    者   : s46746
    修改内容   : For CS/PS mode 1,联合TAU成功时，需要Disable L
  7.日    期   : 2012年7月27日
    作    者   : s00217060
    修改内容   : For CS/PS mode 1,带Disable LTE原因值
  8.日    期   : 2012年12月6日
    作    者   : s00217060
    修改内容   : DTS2012120410842:不仅是指定搜网注册成功，其他情况注册成功时，也需要删除ForbPlmn,ForbLa,ForbGprs等信息
  9.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
 10.日    期   : 2013年3月30日
    作    者   : w00176964
    修改内容   : DTS2013030802929,周期性RAU需要通知LMM
 11.日    期   : 2013年12月10日
    作    者   : w00176964
    修改内容   : VoLTE_PhaseIII 项目:修改Disable L模的逻辑
 12.日    期   : 2015年05月11日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseII 项目修改
 13.日    期   : 2015年10月14日
    作    者   : c00318887
    修改内容   : DTS2015082002854: 漫游标记不准
*****************************************************************************/
VOS_VOID NAS_MMC_ProcLmmCombinedTauResultInd_TauRsltSucc_PlmnSelection(
    LMM_MMC_TAU_RESULT_IND_STRU                            *pstLmmTauIndMsg,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsRegRsltCause,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsAddition,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsAddition
)
{
    if (VOS_TRUE == pstLmmTauIndMsg->bitOpCnRst)
    {
        /* CS+PS的周期性TAU时,不论是否携带CS CAUSE值,都认为联合注册成功 */
        if ((MMC_LMM_COMBINED_TA_LA_UPDATED == pstLmmTauIndMsg->ulCnRst)
         || (MMC_LMM_COMBINED_TA_LA_UPDATED_ISR_ACTIVATED == pstLmmTauIndMsg->ulCnRst)
         || (MMC_LMM_CS_PS_PERIODIC_UPDATING == pstLmmTauIndMsg->ulReqType))
        {
            /* 和网侧交互EPS和CS均注册成功 */
            NAS_MMC_ProcLmmCombinedTauResultInd_TauRsltCsEpsSucc(pstLmmTauIndMsg,
                          penCsAddition, penPsAddition);

        }
        else if ((MMC_LMM_TA_UPDATED == pstLmmTauIndMsg->ulCnRst)
              || (MMC_LMM_TA_UPDATED_ISR_ACTIVATED == pstLmmTauIndMsg->ulCnRst))
        {
            /* 与网侧交互EPS成功CS失败，且原因值为协议24301 5.5.3.3.4.3章节所列 */
            NAS_MMC_ProcLmmCombinedTauResultInd_TauRsltEpsOnlySucc(pstLmmTauIndMsg,enCsRegRsltCause,
                          penCsAddition, penPsAddition);

        }
        else
        {
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcLmmCombinedTauResultInd_TauRsltSucc_PlmnSelection:Unexpected cn result!");
        }
    }
    else
    {
        /* 假流程注册成功上报正常服务返回 */
        *penPsAddition = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;

        /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-12, begin */
        *penCsAddition = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;
        /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-12, end */

        NAS_MMC_UpdateServiceState_RegSucc(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NORMAL_SERVICE);

        /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, begin */
        NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, VOS_TRUE, NAS_MML_REG_FAIL_CAUSE_NULL);
        /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, end */
    }

    NAS_MMC_NotifyModeChange(NAS_MML_GetCurrNetRatType(),
                             NAS_MML_GetSimPsRegStatus());


    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcLmmCombinedTauResultInd_PlmnSelection
 功能描述  : Lmm TAU结果的处理函数
 输入参数  : ID_LMM_MMC_TAU_RESULT_IND消息的首地址
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月27日
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
  5.日    期   : 2012年2月4日
    作    者   : w00167002
    修改内容   : DTS2011122704039:将注册结果类型以及注册消息传递给处理注册结果
                  函数，扩展注册结果函数的处理能力。
                   additional action值若为无效值NAS_MMC_ADDITIONAL_ACTION_BUTT
                 则不更新当前的additional action
  6.日    期   : 2012年5月7日
    作    者   : w00166186
    修改内容   : DTS20120050302236:手动搜网指定的网络在禁止列表中，注册成功后，
                 没有向LMM发送等效PLMN
  7.日    期   : 2012年5月10日
    作    者   : l65478
    修改内容   : DTS2012050500988:CS注册成功时,不能删除forbid PLMN for GPRS信息
  8.日    期   : 2012年05月28日
    作    者   : sunxibo /46746
    修改内容   : Added for V7R1 C50 CS/PS mode 1
  9.日    期   : 2012年6月30日
    作    者   : w00176964
    修改内容   : DTS2012063003332:联合注册单域成功,原因值不在协议规定的列表里,LNAS
                 给的结果为CN_REJ,此时不应该删除禁止列表
 10.日    期   : 2012年08月20日
    作    者   : l65478
    修改内容   : DTS2012081703289，手动搜网失败后关机，重新开机注册成功
                   后出服务区后不驻留EPLMN上
  11.日    期   : 2012年8月21日
     作    者   : z00161729
     修改内容   : DCM定制需求和遗留问题修改DTS2012090401249
  12.日    期   : 2013年1月11日
     作    者   : w00176964
     修改内容   : DTS2013010706662:调整发送EPLMN逻辑调用位置
  13.日    期   : 2014年5月5日
     作    者   : w00242748
     修改内容   : DTS2014043000311:注册状态服务状态不一致，将MMC中报服务状态的场景，都加
                  注册状态的上报。
*****************************************************************************/
VOS_VOID  NAS_MMC_ProcLmmCombinedTauResultInd_PlmnSelection(
    LMM_MMC_TAU_RESULT_IND_STRU        *pstLmmTauIndMsg
)
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enPsRegRsltCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsRegRsltCause;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsAdditionalAction;

     /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, begin */
    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo = VOS_NULL_PTR;
     NAS_MML_EQUPLMN_INFO_STRU                              stSndEquPlmnInfo;

    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, end */

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));

    enPsAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_BUTT;
    enCsAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_BUTT;

    NAS_MMC_ConverLmmCombinedTauRsltToMMLCause(pstLmmTauIndMsg, &enPsRegRsltCause, &enCsRegRsltCause);

    switch (pstLmmTauIndMsg->ulTauRst)
    {
        case MMC_LMM_TAU_RSLT_SUCCESS:
            NAS_MMC_ProcLmmCombinedTauResultInd_TauRsltSucc_PlmnSelection(pstLmmTauIndMsg,
                       enCsRegRsltCause, &enCsAdditionalAction, &enPsAdditionalAction);

            break;

        case MMC_LMM_TAU_RSLT_FAILURE:
            if (VOS_FALSE == pstLmmTauIndMsg->bitOpAtmpCnt)
            {
                enPsAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
                enCsAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;

                /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, begin */
                NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, VOS_FALSE, NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);
                /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, end */
            }
            else
            {
                /* EPS和CS注册均失败 */
                NAS_MMC_ProcCombinedTauEpsRegFail(LMM_MMC_TAU_RESULT_IND, pstLmmTauIndMsg,
                                              &enPsAdditionalAction, &enCsAdditionalAction);
            }
            break;

        case MMC_LMM_TAU_RSLT_MO_DETACH_FAILURE:
        case MMC_LMM_TAU_RSLT_MT_DETACH_FAILURE:
        case MMC_LMM_TAU_RSLT_T3402_RUNNING:
        case MMC_LMM_TAU_RSLT_TIMER_EXP:
        case MMC_LMM_TAU_RSLT_ACCESS_BARED:
        case MMC_LMM_TAU_RSLT_FORBID_PLMN:
        case MMC_LMM_TAU_RSLT_FORBID_TA_FOR_RPOS:
        case MMC_LMM_TAU_RSLT_FORBID_PLMN_FOR_GPRS:
        case MMC_LMM_TAU_RSLT_FORBID_TA_FOR_ROAMING:
        case MMC_LMM_TAU_RSLT_AUTH_REJ:
            /* EPS和CS注册均失败 */
            NAS_MMC_ProcCombinedTauEpsRegFail(LMM_MMC_TAU_RESULT_IND, pstLmmTauIndMsg,
                                          &enPsAdditionalAction, &enCsAdditionalAction);
            break;

        case MMC_LMM_TAU_RSLT_CN_REJ:
            if ((VOS_TRUE == pstLmmTauIndMsg->bitOpCnRst)
             && ((MMC_LMM_TA_UPDATED == pstLmmTauIndMsg->ulCnRst)
              || (MMC_LMM_TA_UPDATED_ISR_ACTIVATED == pstLmmTauIndMsg->ulCnRst)))
            {
                /* 当TAU请求类型为联合，网侧相应的TAU结果类型为TA UPDATED，
                   且原因值不为协议24301 5.5.3.3.4.3章节所列或者没有携带原因值，
                   则LMM通过TAU结果中MMC_LMM_TAU_RSLT_CN_REJ通知MMC，且携带相应
                   的TAU请求类型、网侧响应的TAU结果类型、原因值，并携带处理该原
                   因后的tau attempt counter值 */
                NAS_MMC_ProcLmmCombinedTauResultInd_TauRsltEpsOnlySucc(pstLmmTauIndMsg,enCsRegRsltCause,
                                  &enCsAdditionalAction, &enPsAdditionalAction);
            }
            else
            {
                /* EPS和CS注册均失败 */
                NAS_MMC_ProcCombinedTauEpsRegFail(LMM_MMC_TAU_RESULT_IND, pstLmmTauIndMsg,
                                              &enPsAdditionalAction, &enCsAdditionalAction);

            }
            break;

        case MMC_LMM_TAU_RSLT_T3402_RUNNING_EPS_ONLY_SUCC:
            NAS_MMC_ProcCombinedEpsRegFailCauseT3402RunningEpsOnlySucc(LMM_MMC_TAU_RESULT_IND, pstLmmTauIndMsg,
                                              &enPsAdditionalAction, &enCsAdditionalAction);
            break;

        default:
            /* 异常打印 */
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcLmmCombinedTauResultInd_PlmnSelection:Unexpected attach result!");
            enPsAdditionalAction = NAS_MMC_GetPsRegAdditionalAction_PlmnSelection();
            enCsAdditionalAction = NAS_MMC_GetCsRegAdditionalAction_PlmnSelection();
            break;

    }

    /* AdditionalAction有效，更新EPS的下一步的动作类型 */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enPsAdditionalAction )
    {
        NAS_MMC_SetPsRegAdditionalAction_PlmnSelection(enPsAdditionalAction);
    }

    /* AdditionalAction有效，更新CS的下一步的动作类型 */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enCsAdditionalAction )
    {
        NAS_MMC_SetCsRegAdditionalAction_PlmnSelection(enCsAdditionalAction);
    }

     /* 如果还需要等待下一次注册结果,则不更新注册原因值,等待conut达到最大后更新,
    以便于用户指定搜网回复结果 */
    if (NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT != enPsAdditionalAction)
    {
        NAS_MMC_SetPsRegCause_PlmnSelection(enPsRegRsltCause);
    }

    if (VOS_TRUE == NAS_MMC_IsNeedSndEplmn_PlmnSelection())
    {
        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, begin */
        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildSndLmmEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndLmmEquPlmnReq(&stSndEquPlmnInfo);
        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, end */
        /* 通知CSS GEO信息 */
        NAS_MMC_SndCssCurrGeoInd(VOS_TRUE, stSndEquPlmnInfo.ucEquPlmnNum, stSndEquPlmnInfo.astEquPlmnAddr);

        NAS_MMC_SndOmEquPlmn();
    }


    NAS_MMC_UpdateUserSpecPlmnRegisterStatus(enPsRegRsltCause);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcLmmTauResultInd_PlmnSelection
 功能描述  : Lmm TAU结果的处理函数
 输入参数  : ID_LMM_MMC_ATTACH_IND消息的首地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月30日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年1月8日
    作    者   : z00161729
    修改内容   : V7R1 phaseIV调整:周期性tau结果分联合和非联合
*****************************************************************************/
VOS_VOID  NAS_MMC_ProcLmmTauResultInd_PlmnSelection(
    LMM_MMC_TAU_RESULT_IND_STRU        *pstLmmTauIndMsg
)
{
    switch (pstLmmTauIndMsg->ulReqType)
    {
        case MMC_LMM_COMBINED_TA_LA_UPDATING:
        case MMC_LMM_COMBINED_TA_LA_WITH_IMSI:
        case MMC_LMM_CS_PS_PERIODIC_UPDATING:

            /* 处理lmm的联合tau结果 */
            NAS_MMC_ProcLmmCombinedTauResultInd_PlmnSelection(pstLmmTauIndMsg);
            break;

        case MMC_LMM_TA_UPDATING:
        case MMC_LMM_PS_PERIODIC_UPDATING:

            /* 处理lmm的非联合tau，EPS only注册的结果 */
            NAS_MMC_ProcLmmEpsOnlyTauResultInd_PlmnSelection(pstLmmTauIndMsg);
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcLmmTauResultInd_PlmnSelection:Unexpected tau req type!");
            break;

    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmMmcTauResultInd_PlmnSelection_WaitEpsConnRelInd
 功能描述  : 在等待EPS链路释放的时候收到ID_LMM_MMC_TAU_RESULT_IND的的处理
 输入参数  : ulEventType:消息类型
             pstMsg: ID_LMM_MMC_TAU_RESULT_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月12日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年12月11日
    作    者   : l00167671
    修改内容   : DTS2012121802573, TQE清理
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmMmcTauResultInd_PlmnSelection_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCsRegCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enPsRegCause;
    LMM_MMC_TAU_RESULT_IND_STRU        *pstLmmTauIndMsg = VOS_NULL_PTR;
    NAS_MMC_FSM_ID_ENUM_UINT32          enCurrentFsmId;
    VOS_UINT32                          ulCurrentEventType;

    pstLmmTauIndMsg  = (LMM_MMC_TAU_RESULT_IND_STRU*)pstMsg;

    NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnSelection(NAS_MMC_WAIT_REG_RESULT_IND_PS);

    /* 向GMM和MM转发注册结果消息 */
    NAS_MMC_SndMmLmmTauResultInd(pstLmmTauIndMsg);
    NAS_MMC_SndGmmLmmTauResultInd(pstLmmTauIndMsg);

    /* 搜网注册过程中 ,用户设置syscfg需要搜网场景，MMC会主动释放连接，
       在等待连接释放状态，L可能会上注册结果，需要处理 */
    NAS_MMC_ProcLmmTauResultInd_PlmnSelection(pstLmmTauIndMsg);

    enCurrentFsmId     = NAS_MMC_GetCurrFsmId();
    if (NAS_MMC_FSM_PLMN_SELECTION != enCurrentFsmId)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }
    ulCurrentEventType = NAS_MMC_GetCurrFsmEventType();
    if (VOS_TRUE == NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enCurrentFsmId,ulCurrentEventType))
    {
        enCsRegCause = NAS_MMC_GetCsRegCause_PlmnSelection();
        enPsRegCause = NAS_MMC_GetPsRegCause_PlmnSelection();

        if (VOS_TRUE == NAS_MMC_ProcUserSearchRegRslt_PlmnSelection(enCsRegCause,enPsRegCause))
        {
            /*更新入口消息为普通的搜网请求，后续有新的用户请求时，可以打断该状态机*/
            NAS_MMC_SaveCommonPlmnSrchEntryMsg_PlmnSelection();
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmMmcAttachInd_PlmnSelection_WaitEpsConnRelInd
 功能描述  : 在等待EPS链路释放的时候收到ID_LMM_MMC_ATTACH_IND的的处理
 输入参数  : ulEventType:消息类型
             pstMsg: ID_LMM_MMC_ATTACH_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月12日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年12月11日
    作    者   : l00167671
    修改内容   : DTS2012121802573, TQE清理
  3.日    期   : 2015年4月22日
    作    者   : wx270776
    修改内容   : DTS2015031602665:将CL ATTACH注册状态存入全局变量
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmMmcAttachInd_PlmnSelection_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsRegCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enPsRegCause;
    LMM_MMC_ATTACH_IND_STRU                                *pstLmmAttachIndMsg = VOS_NULL_PTR;
    NAS_MMC_FSM_ID_ENUM_UINT32                              enCurrentFsmId;
    VOS_UINT32                                              ulCurrentEventType;
    NAS_MML_LTE_UE_OPERATION_MODE_ENUM_UINT8                enUeOperationMode;

    enUeOperationMode   =  NAS_MML_GetLteUeOperationMode();
    pstLmmAttachIndMsg  = (LMM_MMC_ATTACH_IND_STRU*)pstMsg;

    NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnSelection(NAS_MMC_WAIT_REG_RESULT_IND_PS);

    if ( VOS_TRUE == NAS_MMC_IsNeedUpdateLmmAttachClRegStatus_PlmnSelection(pstLmmAttachIndMsg->enClAttRegStatus) )
    {
        NAS_MMC_SetLmmAttachClRegStatus_PlmnSelection(pstLmmAttachIndMsg->enClAttRegStatus);
    }

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

    /* 搜网注册过程中 ,用户设置syscfg需要搜网场景，MMC会主动释放连接，
      在等待连接释放状态，L可能会上注册结果，需要处理 */
    NAS_MMC_ProcLmmAttachInd_PlmnSelection(pstLmmAttachIndMsg);

    enCurrentFsmId     = NAS_MMC_GetCurrFsmId();
    if (NAS_MMC_FSM_PLMN_SELECTION != enCurrentFsmId)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }
    ulCurrentEventType = NAS_MMC_GetCurrFsmEventType();
    if (VOS_TRUE == NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enCurrentFsmId,ulCurrentEventType))
    {
        enCsRegCause = NAS_MMC_GetCsRegCause_PlmnSelection();
        enPsRegCause = NAS_MMC_GetPsRegCause_PlmnSelection();

        if (VOS_TRUE == NAS_MMC_ProcUserSearchRegRslt_PlmnSelection(enCsRegCause,enPsRegCause))
        {
            /*更新入口消息为普通的搜网请求，后续有新的用户请求时，可以打断该状态机*/
            NAS_MMC_SaveCommonPlmnSrchEntryMsg_PlmnSelection();
        }
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedEnableLte_PlmnSelection
 功能描述  : 根据不同的搜网场景判断是否需要 Enable L
 输入参数  : enPlmnSearchScene

 输出参数  : 无
 返 回 值  : VOS_FALSE:不需要 Enable L
              VOS_TRUE: 需要 Enable L
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年06月02日
   作    者   : s00217060
   修改内容   : 新生成函数
 2.日    期   : 2012年09月12日
   作    者   : z00161729
   修改内容   : DTS2012082702662：disable或enable lte不再判断当前syscfg是否支持L
 3.日    期   : 2012年11月10日
   作    者   : s00217060
   修改内容   : DTS2012102902559：USIM卡时，才需要Enable Lte;SIM卡时不需要
 4.日    期   : 2013年11月01日
   作    者   : l00208543
   修改内容   : 根据卡类型禁止网络制式
 5.日    期   : 2015年1月5日
   作    者   : z00161729
   修改内容   : AT&T 支持DAM特性修改

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedEnableLte_PlmnSelection(
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene
)
{
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;

    VOS_UINT32                                              ulIsPlmnSupportDam;


    enLteCapabilityStatus = NAS_MML_GetLteCapabilityStatus();

    /* 如果开机时已经根据en_NV_Item_Rat_Forbidden_List_Accord_Imsi_Config的配置禁止了LTE，则返回VOS_FALSE */
    if (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE == NAS_MML_GetLteForbiddenStatusFlg())
    {
        return VOS_FALSE;
    }

    /* 如果是SIM卡，不需要Enable Lte */
    if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
    {
        return VOS_FALSE;
    }

    /* PS卡无效, 不需要重新 Enable L */
    if ( VOS_FALSE == NAS_MML_GetSimPsRegStatus() )
    {
        return VOS_FALSE;
    }

    /* PS卡不允许注册,不需要重新 Enable L */
    if ( VOS_FALSE == NAS_MML_GetPsAttachAllowFlg() )
    {
        return VOS_FALSE;
    }

    /* 搜网场景是NAS_MMC_PLMN_SEARCH_SCENE_DISABLE_LTE,不需要重新 Enable L */
    if ( NAS_MMC_PLMN_SEARCH_SCENE_DISABLE_LTE == enPlmnSearchScene )
    {
        return VOS_FALSE;
    }

    /* disable 或enable lte不再判断syscfg是否支持L */

    /* 如果之前disable lte的网络是支持DAM的网络，且禁止接入技术网络列表特性9014 nv未开启，
       则无需enable lte,AT&T LTE-BTR-1-1840用例要求只禁止310410 lte网络，漫游lte网络可用，
       后该用例删除，如果后续有需要测试，可以开启DAM nv项进行测试 */
    ulIsPlmnSupportDam = NAS_MML_IsPlmnSupportDam(NAS_MMC_GetDisabledLtePlmnId());

    if ((VOS_FALSE == NAS_MML_GetAddDamPlmnInDisablePlmnWithRatListFlag())
      && (VOS_TRUE == ulIsPlmnSupportDam))
    {
        return VOS_FALSE;
    }

    /* 已经Disable L,需要重新 Enable L */
    if ( (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == enLteCapabilityStatus)
      || (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS == enLteCapabilityStatus) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsNotLastPlmnNeedRelEpsConn_PlmnSelection
 功能描述  : 判断是否需要释放EPS链接
 输入参数  : 无

 输出参数  : 无
 返 回 值  : VOS_FALSE:是最后一个网络，不用释放链接
              VOS_TRUE: 不是最后一个网络，需要释放EPS链接
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年11月22日
   作    者   : t00212959
   修改内容   : 新生成函数
 2.日    期   : 2013年8月27日
   作    者   : l00208543
   修改内容   : Coverity
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsDisableLteNeedWaitEpsConnRel_PlmnSelection(VOS_VOID)
{
    NAS_MML_PLMN_WITH_RAT_STRU                              stDestPlmn;

	/* 解决版本Coverity问题 */
	PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    if (VOS_TRUE == NAS_MMC_IsDisableLteNeedLocalReleaseEpsConn())
    {
        /* 最后一个网络*/
        if (VOS_FALSE == NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
        {
            /* 回复状态机退出成功 */
            NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);

            /* 直接退出当前状态机 */
            NAS_MMC_FSM_QuitFsmL2();

            return VOS_FALSE;
        }

        NAS_MMC_SetRelRequestFlag_PlmnSelection(VOS_TRUE);

        NAS_MMC_SndLmmRelReq();
    }

    return VOS_TRUE;
}

#endif

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTafSpecPlmnSearchAbortReq_PlmnSelection
 功能描述  : 收到ID_MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:ID_MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ超时的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:返回处理成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月30日
    作    者   : z00161729
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTafSpecPlmnSearchAbortReq_PlmnSelection(
     VOS_UINT32                         ulEventType,
     struct MsgCB                      *pstMsg
)
{
    /* 更新搜网状态机入口消息为普通搜网 */
    NAS_MMC_SaveCommonPlmnSrchEntryMsg_PlmnSelection();

#if (FEATURE_ON == FEATURE_LTE)
    /* 通知通知LMM当前在非用户指定搜网模式 */
    NAS_MMC_SndLmmUserSpecPlmnSearchEndNotify();
#endif

    /* 回复TAFMMC_SPEC_PLMN_SEARCH_ABORT_CNF给MMA */
    NAS_MMC_SndMsccSpecPlmnSearchAbortCnf();
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrmmLimitServiceCampInd_PlmnSelection_WaitCsPsRegRsltInd
 功能描述  : 搜网等注册结果时，对OOS RRMM_LIMIT_SERVICE_CAMP_IND消息的处理
 输入参数  : pstMsg        - RRMM_LIMIT_SERVICE_CAMP_IND消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_TRUE:返回处理成功
             VOS_FALSE:返回处理失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月15日
    作    者   : z00161729
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrmmLimitServiceCampInd_PlmnSelection_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    return NAS_MMC_RcvRrmmLimitServiceCampInd_PlmnSelection(ulEventType, pstMsg);

}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrmmLimitServiceCampInd_PlmnSelection_WaitRrcConnRelInd
 功能描述  : 搜网等连接释放时，对OOS RRMM_LIMIT_SERVICE_CAMP_IND消息的处理
 输入参数  : pstMsg        - RRMM_LIMIT_SERVICE_CAMP_IND消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_TRUE:返回处理成功
             VOS_FALSE:返回处理失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月15日
    作    者   : z00161729
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrmmLimitServiceCampInd_PlmnSelection_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    return NAS_MMC_RcvRrmmLimitServiceCampInd_PlmnSelection(ulEventType, pstMsg);

}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrmmLimitServiceCampInd_PlmnSelection
 功能描述  : 搜网时，对OOS消息的处理
 输入参数  : pstMsg        - RRMM_LIMIT_SERVICE_CAMP_IND消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_TRUE:返回处理成功
             VOS_FALSE:返回处理失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年06月27日
    作    者   : l65478
    修改内容   : 新生成函数
  2.日    期   : 2014年5月28日
    作    者   : z00234330
    修改内容   : covertity修改
  3.日    期   : 2014年11月8日
    作    者   : z00161729
    修改内容   : 开机搜网优化项目修改
  4.日    期   : 2015年10月21日
    作    者   : s00217060
    修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0修改
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrmmLimitServiceCampInd_PlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_LIMIT_SERVICE_CAMP_IND_STRU        *pstRrmmLimitCampOnMsg = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU               stDestPlmn;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU    *pastIntraPlmnSrchInfo = VOS_NULL_PTR;
    VOS_UINT32                               ulIndex;

    pstRrmmLimitCampOnMsg = (RRMM_LIMIT_SERVICE_CAMP_IND_STRU *)pstMsg;

    pastIntraPlmnSrchInfo = (NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                                             sizeof(NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU) * NAS_MML_MAX_RAT_NUM);
    /* 分配内存失败 */
    if (VOS_NULL_PTR == pastIntraPlmnSrchInfo)
    {
        return VOS_TRUE;
    }

    /* modified by z00234330 for coverity修改 2014-05-28 begin */
    PS_MEM_SET(&stDestPlmn, 0x00, sizeof(stDestPlmn));
    /* modified by z00234330 for coverity修改 2014-05-28 end */

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
        for (ulIndex = 0; ulIndex < NAS_MML_MAX_RAT_NUM; ulIndex++)
        {
            NAS_MMC_UpdatePlmnSearchList_PlmnSelection(&(pastIntraPlmnSrchInfo[ulIndex]),
                                                       VOS_TRUE,
                                                       VOS_TRUE);
        }

        /* 当还存在下一个需要搜索的网络时，继续进行搜网，否则，继续等待 */
        if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
        {
            /* 当前应该肯定存在信令连接,如果不存在连接,不用处理 */
            if (VOS_TRUE == NAS_MML_IsRrcConnExist())
            {
                /* 根据当前不同的接入技术,发送释放请求,迁移到不同的等待连接释放的L2状态，并启动保护定时器 */
                NAS_MMC_SndRelReq_PlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA);
            }
        }
    }

    PS_MEM_FREE(WUEPS_PID_MMC, pastIntraPlmnSrchInfo);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_UpdateOosAreaLostPlmnSearchInfo_PlmnSelection
 功能描述  : 根据接入层上报网络更新OOS丢网后的搜网列表
 输入参数  : pstPlmnSearchReq
 输出参数  : pstPlmnSelectionListInfo
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年11月28日
   作    者   : w00166186
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_UpdateOosAreaLostPlmnSearchInfo_PlmnSelection(
    NAS_MMC_INTER_PLMN_SEARCH_REQ_STRU                     *pstPlmnSearchReq,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU          stPrioRatList;
    NAS_MMC_PLMN_TYPE_ENUM_UINT8        enPlmnType;
    VOS_UINT32                          i;
    VOS_UINT32                          j;

    enPlmnType = NAS_MMC_PLMN_TYPE_AVAIL_PLMN;

    for (i = 0; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        if (NAS_MML_NET_RAT_TYPE_BUTT == pstPlmnSearchReq->astInterPlmnSearchInfo[i].enRatType)
        {
            continue;
        }

        stPrioRatList.aucRatPrio[0] = pstPlmnSearchReq->astInterPlmnSearchInfo[i].enRatType;
        stPrioRatList.ucRatNum      = 1;

        for (j = 0; j < pstPlmnSearchReq->astInterPlmnSearchInfo[i].ulHighPlmnNum; j++)
        {
            NAS_MMC_InsertPlmnToPlmnSelectionListHead(&pstPlmnSearchReq->astInterPlmnSearchInfo[i].astHighPlmnList[j],
                                                      enPlmnType,
                                                      &stPrioRatList,
                                                      pstPlmnSelectionListInfo);
        }

        for (j = 0; j < pstPlmnSearchReq->astInterPlmnSearchInfo[i].ulLowPlmnNum; j++)
        {
            NAS_MMC_InsertPlmnToPlmnSelectionListHead(&pstPlmnSearchReq->astInterPlmnSearchInfo[i].astLowPlmnList[j].stPlmnId,
                                                      enPlmnType,
                                                      &stPrioRatList,
                                                      pstPlmnSelectionListInfo);
        }
    }

    /* 可维可测，输出选网列表信息 */
    NAS_MMC_LogPlmnSelectionList(pstPlmnSelectionListInfo);

    return;
}
/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection
 功能描述  : 搜网状态机中被打断
 输入参数  : ulEventType:事件
             pstMsg     :消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE
 调用函数  :
 被调函数  :

 1.日    期   : 2012年11月6日
   作    者   : z40661
   修改内容   : DTS2012110501311
*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
     /* 记录需要退出当前状态机标志 */
    NAS_MMC_SetAbortFlag_PlmnSelection(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetPlmnSearchScene_PlmnSelection
 功能描述  : 状态机入口消息为内部搜网时，获取当前搜网状态机的搜网场景
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 搜网场景
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2013年12月24日
   作    者   : z00161729
   修改内容   : SVLTE支持NCELL搜网

 2.日    期   : 2015年6月3日
   作    者   : w00167002
   修改内容   : 增加开机选网和用户指定选网场景的解析。

 3.日    期   : 2015年12月12日
   作    者   : n00355355
   修改内容   : CL互操作从MSCC模块的plmn search请求消息中获得搜网场景
*****************************************************************************/
NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32 NAS_MMC_GetPlmnSearchScene_PlmnSelection(VOS_VOID)
{
    NAS_MMC_INTER_PLMN_SEARCH_REQ_STRU *pstInterPlmnSearchReq = VOS_NULL_PTR;
    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg           = VOS_NULL_PTR;
    MSCC_MMC_ACQ_REQ_STRU              *pstAcqReq             = VOS_NULL_PTR;

    /* 获取状态机的入口消息信息 */
    pstEntryMsg  = NAS_MMC_GetCurrEntryMsg();

    if (VOS_TRUE == NAS_MMC_IsInterPlmnSearch_PlmnSelection())
    {
        pstInterPlmnSearchReq = (NAS_MMC_INTER_PLMN_SEARCH_REQ_STRU*)(pstEntryMsg->aucEntryMsgBuffer);
        return pstInterPlmnSearchReq->enPlmnSearchScene;
    }

    /* 开机选网场景 */
    if (pstEntryMsg->ulEventType == NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_SEARCH_REQ))
    {
        return NAS_MMC_PLMN_SEARCH_SCENE_SWITCH_ON;
    }

    /* 用户指定搜搜网场景 */
    if ( pstEntryMsg->ulEventType == NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_SPECIAL_REQ) )
    {
        return NAS_MMC_PLMN_SEARCH_SCENE_USER_SPEC_PLMN_SEARCH;
    }

    /* CL互操作从MSCC模块的plmn search请求消息中获得搜网场景 */
    if (pstEntryMsg->ulEventType == NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_ACQ_REQ))
    {
        pstAcqReq = (MSCC_MMC_ACQ_REQ_STRU *)pstEntryMsg->aucEntryMsgBuffer;

        if (NAS_MSCC_PIF_ACQ_REASON_POWER_UP == pstAcqReq->enAcqReason)
        {
            return NAS_MMC_PLMN_SEARCH_SCENE_SWITCH_ON;
        }

        if (NAS_MSCC_PIF_ACQ_REASON_HIGH_PRIORITY == pstAcqReq->enAcqReason)
        {
            return NAS_MMC_PLMN_SEARCH_SCENE_HIGH_PRIO_LTE_PLMN_SEARCH;
        }

        if (NAS_MSCC_PIF_ACQ_REASON_OTHER == pstAcqReq->enAcqReason)
        {
            return NAS_MMC_PLMN_SEARCH_SCENE_AREA_LOST;
        }

        return NAS_MMC_PLMN_SEARCH_SCENE_BUTT;

    }

    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetPlmnSearchScene_PlmnSelection, UNKNOWN SCENE!");

    /* 其他异常则返回无效的搜网场景 */
    return NAS_MMC_PLMN_SEARCH_SCENE_BUTT;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsInterPlmnSearch_PlmnSelection
 功能描述  : 判断当前搜网状态机入口消息是否是内部搜网
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 内部搜网消息
             VOS_FALSE - 不是内部搜网消息
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月24日
    作    者   : z00161729
    修改内容   : SVLTE支持NCELL搜网

*****************************************************************************/
VOS_UINT32  NAS_MMC_IsInterPlmnSearch_PlmnSelection(VOS_VOID)
{
    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg    = VOS_NULL_PTR;

   /* 根据FSM ID获取该FSM 入口消息 */
    pstEntryMsg     = NAS_MMC_GetCurrFsmMsgAddr();

    if (MMCMMC_INTER_PLMN_SEARCH_REQ == NAS_ExtractMsgNameFromEvtType(pstEntryMsg->ulEventType))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedSortAvailablePlmnSelectionList_PlmnSelection
 功能描述  : 判断是否需要对搜网列表中available网络进行重新排序
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 需要
             VOS_FALSE - 不需要
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月8日
    作    者   : z00161729
    修改内容   : 开机搜网优化项目修改

*****************************************************************************/
VOS_UINT32  NAS_MMC_IsNeedSortAvailablePlmnSelectionList_PlmnSelection(VOS_VOID)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList  = VOS_NULL_PTR;
    VOS_UINT8                           i;

    pstPrioRatList       = NAS_MML_GetMsPrioRatList();

    if (VOS_FALSE == NAS_MMC_GetRoamPlmnSelectionSortActiveFlg())
    {
        return VOS_TRUE;
    }


    for (i = 0 ; i < pstPrioRatList->ucRatNum; i++)
    {
        if (VOS_TRUE == NAS_MMC_GetSearchedRoamPlmnSortedFlag_PlmnSelection(pstPrioRatList->aucRatPrio[i]))
        {
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedSortRoamPlmnSelectionList_PlmnSelection
 功能描述  : 判断是否满足开机漫游搜网是否需要对搜网列表进行排序
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 需要重新排序
             VOS_FALSE - 不需要重新排序
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月8日
    作    者   : z00161729
    修改内容   : 开机搜网优化项目修改

*****************************************************************************/
VOS_UINT32  NAS_MMC_IsNeedSortRoamPlmnSelectionList_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene;

    enPlmnSearchScene                   = NAS_MMC_GetPlmnSearchScene_PlmnSelection();

    if (NAS_MMC_PLMN_SEARCH_SCENE_RF_ENABLE == enPlmnSearchScene)

    {
        enPlmnSearchScene               = NAS_MMC_GetBackUpNoRfPlmnSearchScene_PlmnSelection();
    }

    /* 测试卡 */
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        return VOS_FALSE;
    }

    /* 漫游搜网优化定制关闭不处理 */
    if (VOS_FALSE == NAS_MMC_GetRoamPlmnSelectionSortActiveFlg())
    {
        return VOS_FALSE;
    }

    /* 手动搜网模式不处理该消息 */
    if (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == NAS_MMC_GetPlmnSelectionMode())
    {
        return VOS_FALSE;
    }

    /* 该模式已排过一次序，则不需要排第二次 */
    if (VOS_TRUE == NAS_MMC_GetSearchedRoamPlmnSortedFlag_PlmnSelection(enRat))
    {
        return VOS_FALSE;
    }

    /* 之前接入层上报的searched plmn info ind或search cnf中
       存在和rplmn或hplmn相同国家码的网络，则认为非漫游走原有流程，不打断当前搜网 */
    if (VOS_TRUE == NAS_MMC_GetExistRplmnOrHplmnFlag_PlmnSelection())
    {
        return VOS_FALSE;
    }


    /* 漫游搜网定制开启，则在开机选网、丢网、周期选网、SYSCFG触发的选网，进行漫游排序 */
    if ((NAS_MMC_PLMN_SEARCH_SCENE_SWITCH_ON != enPlmnSearchScene)
     && (NAS_MMC_PLMN_SEARCH_SCENE_AREA_LOST != enPlmnSearchScene)
     && (NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED_HISTORY_PLMN_SEARCH != enPlmnSearchScene)
     && (NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED != enPlmnSearchScene)
     && (NAS_MMC_PLMN_SEARCH_SCENE_SYSCFG_SET != enPlmnSearchScene))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedStopPlmnSearchRcvRrcSearchedPlmnInfoInd_PlmnSelection
 功能描述  : 收到RRMM_SEARCHED_PLMN_INFO_IND判断是否需要打断当前搜网
 输入参数  : ulEventType:消息类型
             pstMsg:消息内容
 输出参数  : 无
 返 回 值  : VOS_FALSE:不需要打断当前搜网
             VOS_TRUE:需要打断当前搜网
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年10月28日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   : 2015年10月08日
   作    者   : zwx247453
   修改内容   : 清除Coverity告警
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedStopPlmnSearchRcvRrcSearchedPlmnInfoInd_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    RRMM_SEARCHED_PLMN_INFO_IND_STRU   *pstSearchedPlmnInfoMsg
)
{
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstCurrSearchingPlmn = VOS_NULL_PTR;
    VOS_UINT32                                              ulIndex;
    NAS_MML_PLMN_WITH_RAT_STRU                              stPlmnIdWithRat;
    VOS_UINT32                                              ulIsExistDiffMccWithCurrSearchingMcc;
    VOS_UINT8                                               ucIsExistSearchedPlmnPrioCurrSearchingPlmn;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionList = VOS_NULL_PTR;
    NAS_MMC_ROAM_PLMN_INFO_STRU                             stCurrSearchRoamPlmnInfo;
    NAS_MMC_ROAM_PLMN_INFO_STRU                             stSearchedExistRoamPlmnInfo;
    RRMM_SEARCHED_PLMN_INFO_IND_STRU                        stSearchedPlmnInfoMsg;
    VOS_UINT8                                               ucAllSearchedPlmnForbiddenPlmnFlag;
    NAS_MMC_ROAM_PLMN_TYPE_ENUM_UINT8                       enRoamPlmnType;

    PS_MEM_SET(&stCurrSearchRoamPlmnInfo, 0, sizeof(stCurrSearchRoamPlmnInfo));
    PS_MEM_SET(&stSearchedExistRoamPlmnInfo, 0, sizeof(stSearchedExistRoamPlmnInfo));
    PS_MEM_SET(&stPlmnIdWithRat, 0, sizeof(stPlmnIdWithRat));
    PS_MEM_SET(&stSearchedPlmnInfoMsg, 0, sizeof(stSearchedPlmnInfoMsg));
    PS_MEM_CPY(&stSearchedPlmnInfoMsg, pstSearchedPlmnInfoMsg, sizeof(stSearchedPlmnInfoMsg));

    pstCurrSearchingPlmn                       = NAS_MMC_GetCurrSearchingPlmn_PlmnSelection();
    ulIsExistDiffMccWithCurrSearchingMcc       = VOS_FALSE;
    ucIsExistSearchedPlmnPrioCurrSearchingPlmn = VOS_FALSE;
    pstPlmnSelectionList                       = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();
    ucAllSearchedPlmnForbiddenPlmnFlag         = VOS_TRUE;
    enRoamPlmnType                             = NAS_MMC_ROAM_PLMN_TYPE_BUTT;

    stCurrSearchRoamPlmnInfo.stPlmnWithRat.stPlmnId.ulMcc = pstCurrSearchingPlmn->stPlmnId.ulMcc;
    stCurrSearchRoamPlmnInfo.stPlmnWithRat.stPlmnId.ulMnc = pstCurrSearchingPlmn->stPlmnId.ulMnc;
    stCurrSearchRoamPlmnInfo.stPlmnWithRat.enRat          = pstCurrSearchingPlmn->enRat;
    stCurrSearchRoamPlmnInfo.enNetStatus                  = NAS_MMC_NET_STATUS_NO_SEARCHED;
    stCurrSearchRoamPlmnInfo.enPlmnType                   = NAS_MMC_GetRoamPlmnTypeInPlmnSelectionList(&stCurrSearchRoamPlmnInfo.stPlmnWithRat, pstPlmnSelectionList);
    stCurrSearchRoamPlmnInfo.aucLac[0]                    = NAS_MML_LAC_LOW_BYTE_INVALID;
    stCurrSearchRoamPlmnInfo.aucLac[1]                    = NAS_MML_LAC_HIGH_BYTE_INVALID;


    /* 接入层指示存在的网络跟rplmn或hplmn是同一国家码非漫游场景则不处理该消息*/
    for (ulIndex = 0; ulIndex < stSearchedPlmnInfoMsg.ulAvailPlmnNum; ulIndex++)
    {


        /* 如果当前搜索的网络和searched plmn info ind消息中的plmn相同则不处理，
           等接入层的search cnf success消息*/
        if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&pstCurrSearchingPlmn->stPlmnId, (NAS_MML_PLMN_ID_STRU *)&stSearchedPlmnInfoMsg.astPlmnWithLacList[ulIndex].stPlmnId))
        {
            return VOS_FALSE;
        }

        /* 判断searched plmn info ind中带上来的网络是否跟正在搜索的网络同MCC,
           如果都是相同MCC,且带上来存在的网络不是禁止网络不在NPLMN且优先级高于当前搜索的网络,
           或与当前搜索的网络优先级相同，则需打断当前搜网，
           如果存在不同MCC的网络且不全是nplmn和forbidden plmn则打断当前搜网 */

        stSearchedExistRoamPlmnInfo.stPlmnWithRat.stPlmnId.ulMcc = stSearchedPlmnInfoMsg.astPlmnWithLacList[ulIndex].stPlmnId.ulMcc;
        stSearchedExistRoamPlmnInfo.stPlmnWithRat.stPlmnId.ulMnc = stSearchedPlmnInfoMsg.astPlmnWithLacList[ulIndex].stPlmnId.ulMnc;
        stSearchedExistRoamPlmnInfo.stPlmnWithRat.enRat          = enRat;
        stSearchedExistRoamPlmnInfo.enNetStatus =  NAS_MMC_GetSpecPlmnWithRatNetStatusInPlmnSelectionList(&stSearchedExistRoamPlmnInfo.stPlmnWithRat, pstPlmnSelectionList);

        if (NAS_MMC_NET_STATUS_SEARCHED_REGISTERED != stSearchedExistRoamPlmnInfo.enNetStatus)
        {
            stSearchedExistRoamPlmnInfo.enNetStatus = NAS_MMC_NET_STATUS_SEARCHED_EXIST;
        }

        stSearchedExistRoamPlmnInfo.enPlmnType  = NAS_MMC_GetRoamPlmnTypeInPlmnSelectionList(&stSearchedExistRoamPlmnInfo.stPlmnWithRat, pstPlmnSelectionList);
        stSearchedExistRoamPlmnInfo.aucLac[0]   = (stSearchedPlmnInfoMsg.astPlmnWithLacList[ulIndex].usLac & 0xFF00) >> 8;
        stSearchedExistRoamPlmnInfo.aucLac[1]   = (stSearchedPlmnInfoMsg.astPlmnWithLacList[ulIndex].usLac & 0x00FF);

        if (VOS_FALSE == NAS_MML_ComparePlmnMcc(pstCurrSearchingPlmn->stPlmnId.ulMcc, stSearchedPlmnInfoMsg.astPlmnWithLacList[ulIndex].stPlmnId.ulMcc))
        {
            ulIsExistDiffMccWithCurrSearchingMcc  = VOS_TRUE;

            /* 如果带上来的网络都是nplmn或forbidden plmn，不同mcc也先不打断 */
            enRoamPlmnType = NAS_MMC_GetRoamPlmnType(&stSearchedExistRoamPlmnInfo);

            if ((NAS_MMC_ROAM_PLMN_TYPE_FORBIDDEN != enRoamPlmnType)
             && (NAS_MMC_ROAM_PLMN_TYPE_NPLMN != enRoamPlmnType))
            {
                ucAllSearchedPlmnForbiddenPlmnFlag = VOS_FALSE;
            }
        }
        else
        {
            /* 修改函数名 */
            if (-1 == NAS_MMC_CompareRoamPlmnPrio(&stCurrSearchRoamPlmnInfo, &stSearchedExistRoamPlmnInfo, NAS_MML_GetMsPrioRatList()))
            {
                ucIsExistSearchedPlmnPrioCurrSearchingPlmn = VOS_TRUE;
            }
        }

    }


     /* searched plmn info ind消息中带上来的网络存在与当前搜的网络不同国家码的网络，
       且不都是nplmn和forbidden plmn则打断当前搜网*/
    if ((VOS_TRUE == ulIsExistDiffMccWithCurrSearchingMcc)
     && (VOS_FALSE == ucAllSearchedPlmnForbiddenPlmnFlag))
    {
        return VOS_TRUE;
    }

    if (VOS_TRUE == ucIsExistSearchedPlmnPrioCurrSearchingPlmn)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;

}



/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedSkipFddRcvRrcSearchedPlmnInfoInd_PlmnSelection
 功能描述  : 收到RRMM_SEARCHED_PLMN_INFO_IND判断是否需要打断当前搜网
 输入参数  : ulEventType:消息类型
             pstMsg:消息内容
 输出参数  : 无
 返 回 值  : VOS_FALSE:不需要打断当前搜网
             VOS_TRUE:需要打断当前搜网
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年5月22日
   作    者   : b00269685
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedSkipFddRcvRrcSearchedPlmnInfoInd_PlmnSelection(
    RRMM_SEARCHED_PLMN_INFO_IND_STRU   *pstSearchedPlmnInfoMsg
)
{
    VOS_UINT32                          i;

    /* 当前不是自动切换模式，不需要skip */
    if (NAS_UTRANCTRL_UTRAN_SWITCH_MODE_AUTO != NAS_UTRANCTRL_GetCurUtranSwitchMode())
    {
        return VOS_FALSE;
    }

    /* 上报的plmn info ind中存在td list中的国家码，需要skip */
    for (i = 0; i < pstSearchedPlmnInfoMsg->ulAvailPlmnNum; i++)
    {
        if (VOS_TRUE == NAS_MML_IsMccInDestMccList(pstSearchedPlmnInfoMsg->astPlmnWithLacList[i].stPlmnId.ulMcc,
                                   NAS_UTRANCTRL_GetSpecTdMccListNum(),
                                   NAS_UTRANCTRL_GetSpecTdMccList()))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndCssCurrGeoIndAfterRcvPlmnInfoInd_PlmnSelection
 功能描述  : 收到接入层的PLMN INFO IND时通知CSS当前MCC
 输入参数  : NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                       *pstSearchedExistPlmnInfo
             VOS_UINT8                                               ucIsPowerOn
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月10日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SndCssCurrGeoIndAfterRcvPlmnInfoInd_PlmnSelection(
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                       *pstSearchedExistPlmnInfo,
    VOS_UINT8                                               ucIsPowerOn
)
{
    NAS_MML_PLMN_ID_STRU                                    astGeoPlmn[CSS_MAX_PLMN_ID_NUM];
    VOS_UINT32                                              ulPlmnNum;
    VOS_UINT32                                              i;

    /* plmn个数为0时不需要通知 */
    if (0 == pstSearchedExistPlmnInfo->usSearchPlmnNum)
    {
        return;
    }

    /* 搜网时最多带(RRC_MAX_EQUPLMN_NUM)16个plmn，如果列表中个数大于16，只取列表中的前16个 */

    ulPlmnNum   = pstSearchedExistPlmnInfo->usSearchPlmnNum;

    if (CSS_MAX_PLMN_ID_NUM < pstSearchedExistPlmnInfo->usSearchPlmnNum)
    {
        ulPlmnNum   = CSS_MAX_PLMN_ID_NUM;
    }

    for (i = 0; i < ulPlmnNum; i++)
    {
        astGeoPlmn[i].ulMcc = pstSearchedExistPlmnInfo->astPlmnSelectionList[i].stPlmnWithRat.stPlmnId.ulMcc;
        astGeoPlmn[i].ulMnc = pstSearchedExistPlmnInfo->astPlmnSelectionList[i].stPlmnWithRat.stPlmnId.ulMnc;
    }

    NAS_MMC_SndCssCurrGeoInd(ucIsPowerOn, ulPlmnNum, astGeoPlmn);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndCssCurrGeoIndAfterRcvPlmnSearchCnfFail_PlmnSelection
 功能描述  : 收到接入层的搜网失败消息时通知CSS当前MCC
 输入参数  : NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedExistPlmnInfo
             VOS_UINT8                                               ucIsPowerOn
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月10日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2015年12月12日
    作    者   : s00217060
    修改内容   : DTS2015120901555修改：NAS_MML_MIN参数不能用表达式

*****************************************************************************/
VOS_VOID NAS_MMC_SndCssCurrGeoIndAfterRcvPlmnSearchCnfFail_PlmnSelection(
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedExistPlmnInfo,
    VOS_UINT8                                               ucIsPowerOn
)
{
    NAS_MML_PLMN_ID_STRU                                    astGeoPlmn[CSS_MAX_PLMN_ID_NUM];
    VOS_UINT32                                              ulHighPlmnNum;
    VOS_UINT32                                              ulLowPlmnNum;
    VOS_UINT32                                              ulPlmnNum;
    VOS_UINT32                                              ulTotalNum;
    VOS_UINT32                                              i;

    ulHighPlmnNum   = pstSearchedExistPlmnInfo->ulHighPlmnNum;
    ulLowPlmnNum    = pstSearchedExistPlmnInfo->ulLowPlmnNum;

    /* high plmn和low plmn个数为0时不需要通知 */
    if ((0 == ulHighPlmnNum)
     && (0 == ulLowPlmnNum))
    {
        return;
    }

    /* 搜网时最多带(RRC_MAX_EQUPLMN_NUM)16个plmn，如果列表中个数大于16，只取列表中的前16个 */
    ulPlmnNum   = ulHighPlmnNum;

    /* 先加高质量的plmn */
    for (i = 0; i < ulPlmnNum; i++)
    {
        astGeoPlmn[i].ulMcc = pstSearchedExistPlmnInfo->astHighPlmnList[i].ulMcc;
        astGeoPlmn[i].ulMnc = pstSearchedExistPlmnInfo->astHighPlmnList[i].ulMnc;
    }

    ulTotalNum  = ulHighPlmnNum + ulLowPlmnNum;

    /* 再加低质量的plmn */
    for (i = ulPlmnNum; i < NAS_MML_MIN(CSS_MAX_PLMN_ID_NUM, ulTotalNum); i++)
    {
        astGeoPlmn[i].ulMcc = pstSearchedExistPlmnInfo->astLowPlmnList[i - ulPlmnNum].stPlmnId.ulMcc;
        astGeoPlmn[i].ulMnc = pstSearchedExistPlmnInfo->astLowPlmnList[i - ulPlmnNum].stPlmnId.ulMnc;
    }

    /* 最后总的plmn个数 */
    ulPlmnNum = i;

    NAS_MMC_SndCssCurrGeoInd(ucIsPowerOn, ulPlmnNum, astGeoPlmn);

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedSndEplmn_PlmnSelection
 功能描述  : 当前是否需要发送等效Plmn
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年1月9日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2015年1月15日
    作    者   : z00161729
    修改内容   : AT&T 支持DAM特性修改
 3.日    期   : 2015年4月23日
   作    者   : z00161729
   修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedSndEplmn_PlmnSelection( VOS_VOID )
{
    NAS_MML_EQUPLMN_INFO_STRU                              *pstEplmnInfo  = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                                   *pstCurPlmnId = VOS_NULL_PTR;
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU                       *pstForbidPlmnInfo = VOS_NULL_PTR;
    NAS_MMC_FSM_ID_ENUM_UINT32                              enCurrentFsmId;
    NAS_MML_PLMN_WITH_RAT_STRU                              stPlmnWithRat;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enCurRat;
    VOS_UINT32                                              ulCurrentEventType;
    VOS_UINT32                                              ulIsPlmnForbid;
    VOS_UINT32                                              ulIsUserSpecSrch;

    ulIsPlmnForbid  = VOS_FALSE;

    /* 无卡时，无须发送等效 Plmn */
    if (VOS_FALSE == NAS_MML_GetSimPresentStatus())
    {
        return VOS_FALSE;
    }

    /*  当前驻留网络，非Rplmn时，不发送 Eplmn给接入层，避免接入层丢网 */
    pstEplmnInfo = NAS_MML_GetEquPlmnList();

    /* 当前无EPlmn，通知接入层,联合RAU或者联合ATTACH,LAU时，需要删除Eplmn，24008:4.7.3.2.5
    if the attach attempt counter is smaller than 5 and, additionally,
    the update status is different from U1 UPDATED or the stored LAI is different
    from the one of the current serving cell, then the mobile station shall delete
    any LAI, TMSI, ciphering key sequence number stored in the SIM/USIM
    and list of equivalent PLMNs */
    if ( 0 == pstEplmnInfo->ucEquPlmnNum)
    {
        /* 没有EPlmn时，会通知接入层当前驻留的网络 */
        return VOS_TRUE;
    }

    if (VOS_FALSE == NAS_MML_CompareBcchPlmnwithSimPlmn(NAS_MML_GetCurrCampPlmnId(), &(pstEplmnInfo->astEquPlmnAddr[0])))
    {
        return VOS_FALSE;
    }

    pstCurPlmnId        = NAS_MML_GetCurrCampPlmnId();
    enCurRat            = NAS_MML_GetCurrNetRatType();

#if   (FEATURE_ON == FEATURE_LTE)
    /* 当不允许LTE国际漫游时 */
    if ((VOS_TRUE == NAS_MMC_IsNeedDisableLteRoam(pstCurPlmnId->ulMcc))
     && (NAS_MML_NET_RAT_TYPE_LTE == enCurRat))
    {
        ulIsPlmnForbid = VOS_TRUE;
    }
#endif

    /* 构造带接入技术的PLMN ID */
    stPlmnWithRat.enRat          = NAS_MML_GetCurrNetRatType();
    stPlmnWithRat.stPlmnId.ulMcc = pstCurPlmnId->ulMcc;
    stPlmnWithRat.stPlmnId.ulMnc = pstCurPlmnId->ulMnc;

    /* 判断等效PLMN是否在禁止接入技术的PLMN列表中,如果在则不将该PLMN ID发给RRC */
    if (VOS_TRUE == NAS_MML_IsPlmnIdWithRatInDestDisabledPlmnWithForbiddenPeriodList(&stPlmnWithRat))
    {
        ulIsPlmnForbid = VOS_TRUE;
    }

    if (VOS_TRUE == NAS_MML_IsPlmnIdInForbidPlmnList(pstCurPlmnId))
    {
        ulIsPlmnForbid = VOS_TRUE;
    }

    pstForbidPlmnInfo = NAS_MML_GetForbidPlmnInfo();

    /* 对于LTE，只要在forbidden plmn for gprs则认为禁止 */
    if ((VOS_TRUE == NAS_MML_IsSimPlmnIdInDestBcchPlmnList(pstCurPlmnId, pstForbidPlmnInfo->ucForbGprsPlmnNum, pstForbidPlmnInfo->astForbGprsPlmnList))
     && (NAS_MML_NET_RAT_TYPE_LTE == enCurRat))
    {
        ulIsPlmnForbid = VOS_TRUE;
    }

    enCurrentFsmId     = NAS_MMC_GetCurrFsmId();
    ulCurrentEventType = NAS_MMC_GetCurrFsmEventType();

    ulIsUserSpecSrch    = NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enCurrentFsmId, ulCurrentEventType);

    /* 用户指定搜网的情况,EPLMN无效时,当前驻留PLMN在禁止列表里不应该通知RRC，
       否则RRC不能驻留 */
    if ((VOS_TRUE == ulIsUserSpecSrch)
     && (VOS_TRUE == ulIsPlmnForbid))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/* Added by s00246516 for L-C互操作项目, 2014-01-28, Begin */
#if   (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_MMC_DisableLteForSimReason_PlmnSelection
 功能描述  : 开机搜索时,如果SIM卡需要Disable LTE
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年1月28日
   作    者   : s00246516
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_DisableLteForSimReason_PlmnSelection(VOS_VOID)
{
    NAS_MML_SIM_TYPE_ENUM_UINT8                             enSimType;
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;
    VOS_UINT32                                              ulLteOnly;

    ulLteOnly = NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList());

    enSimType           = NAS_MML_GetSimType();
    enLCapabilityStatus = NAS_MML_GetLteCapabilityStatus();

    if ((VOS_TRUE == NAS_MML_IsPlatformSupportLte())
     && (NAS_MML_SIM_TYPE_SIM == enSimType)
     && (VOS_FALSE            == ulLteOnly)
      )
    {
        if ((VOS_FALSE == NAS_MML_GetDisableLteRoamFlg())
         && (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS != enLCapabilityStatus))
        {
            if (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE != NAS_MML_GetLteForbiddenStatusFlg())
            {
                NAS_MMC_SndDisableLteNotify(MMC_LMM_DISABLE_LTE_REASON_SIM_CARD_SWITCH_ON);
            }
        }

        /* 更新disable LTE能力标记 */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS);
    }

    return;
}
#endif

/*****************************************************************************
 函 数 名  : NAS_MMC_RefreshPlmnSelectionListRcvMsccRegReq_PlmnSelection
 功能描述  : 根据注册请求的搜网场景重新刷新搜网列表
 输入参数  : enPlmnSearchScene
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年1月28日
   作    者   : s00246516
   修改内容   : 新生成函数
 2.日    期   : 2014年6月13日
   作    者   : b00269685
   修改内容   : Pref网络不包含UPLMN
*****************************************************************************/
VOS_VOID NAS_MMC_RefreshPlmnSelectionListRcvMsccRegReq_PlmnSelection(
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene
)
{
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionList = VOS_NULL_PTR;

    pstPlmnSelectionList = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();

    switch (enPlmnSearchScene)
    {
        case NAS_MMC_PLMN_SEARCH_SCENE_REG_NCELL:

            /* 重新按NCELL初始化选网列表 */
            PS_MEM_SET(pstPlmnSelectionList, 0x0, sizeof(NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU));
            NAS_MMC_InitPlmnSelectionList_RegNCell(pstPlmnSelectionList, VOS_NULL_PTR);
            break;

        case NAS_MMC_PLMN_SEARCH_SCENE_REG_HPLMN:

            /* 删除非HPLMN */
            NAS_MMC_DeleteSpecTypePlmnInPlmnSelectionList(NAS_MMC_PLMN_TYPE_RPLMN, pstPlmnSelectionList);
            NAS_MMC_DeleteSpecTypePlmnInPlmnSelectionList(NAS_MMC_PLMN_TYPE_UPLMN, pstPlmnSelectionList);
            NAS_MMC_DeleteSpecTypePlmnInPlmnSelectionList(NAS_MMC_PLMN_TYPE_OPLMN, pstPlmnSelectionList);
            NAS_MMC_DeleteSpecTypePlmnInPlmnSelectionList(NAS_MMC_PLMN_TYPE_EPLMN, pstPlmnSelectionList);
            NAS_MMC_DeleteSpecTypePlmnInPlmnSelectionList(NAS_MMC_PLMN_TYPE_AVAIL_PLMN, pstPlmnSelectionList);
            break;

        case NAS_MMC_PLMN_SEARCH_SCENE_REG_PREF_PLMN:

            /* 删除非HPLMN+UOPLMN */
            NAS_MMC_DeleteSpecTypePlmnInPlmnSelectionList(NAS_MMC_PLMN_TYPE_RPLMN, pstPlmnSelectionList);
            NAS_MMC_DeleteSpecTypePlmnInPlmnSelectionList(NAS_MMC_PLMN_TYPE_EPLMN, pstPlmnSelectionList);

            if (VOS_TRUE == NAS_MML_Get3GPP2UplmnNotPrefFlg())
            {
                NAS_MMC_DeleteSpecTypePlmnInPlmnSelectionList(NAS_MMC_PLMN_TYPE_UPLMN, pstPlmnSelectionList);
            }

            NAS_MMC_DeleteSpecTypePlmnInPlmnSelectionList(NAS_MMC_PLMN_TYPE_AVAIL_PLMN, pstPlmnSelectionList);
            break;

        default:

            /* 其他场景不需要刷新选网列表 */
            break;
    }

    /* 可维可测，输出选网列表信息 */
    NAS_MMC_LogPlmnSelectionList(pstPlmnSelectionList);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsAllowedRegAfterAcqSucc_PlmnSelection
 功能描述  : 搜索到网络后是否允许立即发起注册
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年1月28日
   作    者   : s00246516
   修改内容   : 新生成函数
 2.日    期   : 2015年4月24日
   作    者   : w00176964
   修改内容   : CDMA 1x Iteration 10 Modified
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsAllowedRegAfterAcqSucc_PlmnSelection(VOS_VOID)
{
    MSCC_MMC_ACQ_REQ_STRU              *pstMsccMmcAcqReq      = VOS_NULL_PTR;
    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg           = VOS_NULL_PTR;

    /* 获取状态机的入口消息信息 */
    pstEntryMsg  = NAS_MMC_GetCurrEntryMsg();

    /* 如果当前注册是由3GPP MMC控制返回VOS_TRUE */
    if (NAS_MMC_REG_CONTROL_BY_3GPP_MMC == NAS_MMC_GetRegCtrl())
    {
        /* 根据入口消息判定是否需要立即注册 */
         if (ID_MSCC_MMC_ACQ_REQ == NAS_ExtractMsgNameFromEvtType(pstEntryMsg->ulEventType))
         {
             pstMsccMmcAcqReq = (MSCC_MMC_ACQ_REQ_STRU*)(pstEntryMsg->aucEntryMsgBuffer);

             if (VOS_TRUE == pstMsccMmcAcqReq->ucNotRegAfterAcqSucc)
             {
                 return VOS_FALSE;
             }
         }

        return VOS_TRUE;
    }

    /* 如果当前注册是由3GPP2 CBP控制而且是MMA触发的注册返回VOS_TRUE */
    if (VOS_TRUE == NAS_MMC_IsMsccRegReq_PlmnSelection())
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsMsccRegReq_PlmnSelection
 功能描述  : 当前是否是MSCC的注册请求触发搜网注册
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年1月28日
   作    者   : s00246516
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsMsccRegReq_PlmnSelection(VOS_VOID)
{
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene;

    enPlmnSearchScene = NAS_MMC_GetPlmnSearchScene_PlmnSelection();

    if ((NAS_MMC_PLMN_SEARCH_SCENE_REG_NCELL == enPlmnSearchScene)
     || (NAS_MMC_PLMN_SEARCH_SCENE_REG_HPLMN == enPlmnSearchScene)
     || (NAS_MMC_PLMN_SEARCH_SCENE_REG_PREF_PLMN == enPlmnSearchScene)
     || (NAS_MMC_PLMN_SEARCH_SCENE_REG_ANY_PLMN == enPlmnSearchScene))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedSearchAvailPlmn_PlmnSelection
 功能描述  : 是否需要搜索选网列表初始化之外的可用网络
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年1月28日
   作    者   : s00246516
   修改内容   : 新生成函数
 2.日    期   : 2014年5月26日
   作    者   : s00246516
   修改内容   : eHRPD向LTE重选，发起NCELL搜索时，PLMN可能是无效的，因此需要能搜索无效的网络
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedSearchAvailPlmn_PlmnSelection(VOS_VOID)
{
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene;

    enPlmnSearchScene = NAS_MMC_GetPlmnSearchScene_PlmnSelection();

    if ((NAS_MMC_PLMN_SELECTION_MODE_AUTO         == NAS_MMC_GetPlmnSelectionMode())
     && (NAS_MMC_PLMN_SEARCH_SCENE_REG_HPLMN      != enPlmnSearchScene)
     && (NAS_MMC_PLMN_SEARCH_SCENE_REG_PREF_PLMN  != enPlmnSearchScene)
     && (NAS_MMC_PLMN_SEARCH_SCENE_HIGH_PRIO_LTE_PLMN_SEARCH != enPlmnSearchScene))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/* Added by s00246516 for L-C互操作项目, 2014-01-28, End */

/*****************************************************************************
 函 数 名  : NAS_MMC_UpdateRfAvailFlgPlmnSrchFail_PlmnSelection
 功能描述  : 搜网失败后更新MSCC的RF可用标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年6月25日
   作    者   : w00176964
   修改内容   : DSDS III新生成函数
 2.日    期   : 2015年5月21日
   作    者   : w00167002
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0项目修改
 3.日    期   : 2016年1月4日
   作    者   : n00355355
   修改内容   : DTS2016010300936修改
*****************************************************************************/
VOS_VOID NAS_MMC_UpdateRfAvailFlgPlmnSrchFail_PlmnSelection(VOS_VOID)
{
    NAS_MML_PLMN_WITH_RAT_STRU          stDestPlmn;
    NAS_MMC_PLMN_TYPE_ENUM_UINT8        enPlmnType;

    PS_MEM_SET(&stDestPlmn, 0x0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    /* RF资源可用,不需要通知MMA当前RF资源是否可用 */
    if (VOS_TRUE == NAS_MML_GetRfAvailFlg())
    {
        return;
    }

    /* 当还存在下一个需要搜索的网络时，继续进行搜网，否则，进入限制驻留 */

    if (VOS_FALSE == NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        /* 如果先前NO RF,则搜网失败后需要通知MMA当前RF资源可用 */
        NAS_MML_SetCurrRatRfAvailFlg(NAS_MML_NET_RAT_TYPE_BUTT, VOS_TRUE);

        /* 向MMA通知当前NO RF信息 */
        NAS_MMC_SndMsccRfAvailInd(VOS_TRUE);

        /* 上报MMA之前因为no rf而没有上报的状态 */
        NAS_MMC_SndMsccCurrServiceRelatedInfo();

        return;
    }

    enPlmnType = NAS_MMC_GetPlmnTypeInPlmnSelectionList(&stDestPlmn, NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection());

    /* 判断下个搜索的PLMN是否为R+E,如果是则暂不通知MMA当前RF可用,等待R+E是搜网结果后决定是否需要通知MMA;
       否则立即通知MMA */
    if ((NAS_MMC_PLMN_TYPE_RPLMN == enPlmnType)
     || (NAS_MMC_PLMN_TYPE_EPLMN == enPlmnType))
    {
        return;
    }

    NAS_MML_SetCurrRatRfAvailFlg(NAS_MML_NET_RAT_TYPE_BUTT, VOS_TRUE);

    /* 向MMA通知当前NO RF信息 */
    NAS_MMC_SndMsccRfAvailInd(VOS_TRUE);

    /* 上报MMA之前因为no rf而没有上报的状态 */
    NAS_MMC_SndMsccCurrServiceRelatedInfo();

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_UpdateRfAvailFlgPlmnSrchAborted_PlmnSelection
 功能描述  : 搜网被打断后更新MMA的RF可用标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年6月25日
   作    者   : w00176964
   修改内容   : DSDS III新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_UpdateRfAvailFlgPlmnSrchAborted_PlmnSelection(VOS_VOID)
{
    /* RF资源可用,不需要通知MMA当前RF资源是否可用 */
    if (VOS_TRUE == NAS_MML_GetRfAvailFlg())
    {
        return;
    }

    NAS_MML_SetCurrRatRfAvailFlg(NAS_MML_NET_RAT_TYPE_BUTT, VOS_TRUE);

    /* 向MMA通知当前NO RF信息 */
    NAS_MMC_SndMsccRfAvailInd(VOS_TRUE);

    /* 上报MMA之前因为no rf而没有上报的状态 */
    NAS_MMC_SndMsccCurrServiceRelatedInfo();

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_UpdateRfAvailFlgPlmnSrchSucc_PlmnSelection
 功能描述  : 搜网成功后更新MMA的RF可用标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年6月25日
   作    者   : w00176964
   修改内容   : DSDS III新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_UpdateRfAvailFlgPlmnSrchSucc_PlmnSelection(VOS_VOID)
{
    /* RF资源可用,不需要通知MMA当前RF资源是否可用 */
    if (VOS_TRUE == NAS_MML_GetRfAvailFlg())
    {
        return;
    }

    NAS_MML_SetCurrRatRfAvailFlg(NAS_MML_NET_RAT_TYPE_BUTT, VOS_TRUE);

    /* 向MMA通知当前NO RF信息 */
    NAS_MMC_SndMsccRfAvailInd(VOS_TRUE);

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMsccPlmnSrchReq_PlmnSelection_WaitMsccRegReq
 功能描述  : 等待MSCC的reg request过程中收到MSCC的搜网请求消息的处理
 输入参数  : pMsg        - RRMM_REL_IND消息首地址
             ulEventType - 事件类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年4月14日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMsccPlmnSrchReq_PlmnSelection_WaitMsccRegReq(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enNetRatType;
    NAS_MML_PLMN_WITH_RAT_STRU                              stDestPlmn;
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene;
    NAS_MMC_INTER_PLMN_SEARCH_REQ_STRU                     *pstInterPlmnSrchMsg = VOS_NULL_PTR;
    MSCC_MMC_PLMN_SEARCH_REQ_STRU                          *pstPlmnSrchReq      = VOS_NULL_PTR;

    /* 停止保护定时器TI_NAS_MMC_WAIT_MSCC_REG_REQ */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_MSCC_REG_REQ);

    /* 如果有ABORT标志，直接退出 */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    pstPlmnSrchReq = (MSCC_MMC_PLMN_SEARCH_REQ_STRU*)pstMsg;

    enPlmnSearchScene = NAS_MMC_GetPlmnSearchSceneMsccPlmnSrchReq(pstPlmnSrchReq);

    /* 将状态机入口消息替换为构造的内部搜网消息，后续搜到网络后可以直接发起注册 */
    pstInterPlmnSrchMsg = (NAS_MMC_INTER_PLMN_SEARCH_REQ_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC, sizeof(NAS_MMC_INTER_PLMN_SEARCH_REQ_STRU));
    if (VOS_NULL_PTR == pstInterPlmnSrchMsg)
    {
        /* 异常打印 */
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMsccPlmnSrchReq_PlmnSelection_WaitMsccRegReq Alloc mem fail");

        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);

        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    NAS_MMC_BulidInterPlmnSearchReqMsg(enPlmnSearchScene, VOS_NULL_PTR, 0, pstInterPlmnSrchMsg);
    NAS_MMC_SaveCurEntryMsg(NAS_BuildEventType(WUEPS_PID_MMC, MMCMMC_INTER_PLMN_SEARCH_REQ),
                            (struct MsgCB*)pstInterPlmnSrchMsg);
    PS_MEM_FREE(WUEPS_PID_MMC, pstInterPlmnSrchMsg);

    /* 根据enPlmnSearchScene重新刷新选网列表，删除不满足优先级要求的网络 */
    NAS_MMC_RefreshPlmnSelectionListRcvMsccRegReq_PlmnSelection(enPlmnSearchScene);

    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    /* 获取当前接入技术 */
    enNetRatType = NAS_MML_GetCurrNetRatType();

    if (VOS_TRUE != NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();

        return VOS_TRUE;
    }

    if (enNetRatType == stDestPlmn.enRat)
    {
        /* 向接入层或LMM发送搜网请求，根据不同的搜网模式，迁移到不同的L2状态，并启动保护定时器 */
        NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
    }
    /*需要挂起当前模式，切换到等待挂起状态，启动保护定时器*/
    else
    {
        /* 向接入层或LMM发送挂起请求，根据当前不同的接入技术，迁移到不同的L2状态，并启动保护定时器 */
        NAS_MMC_SndSuspendReq_PlmnSelection(enNetRatType);
    }

    return VOS_TRUE;

}




/*****************************************************************************
 函 数 名  : NAS_MMC_SaveGeoPlmn_PlmnSelection
 功能描述  : 保存MSCC在开机搜网时带下来的PLMN
 输入参数  : MSCC_MMC_PLMN_SEARCH_REQ_STRU      *pstPlmnSearchReq
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月22日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SaveGeoPlmn_PlmnSelection(
    MSCC_MMC_PLMN_SEARCH_REQ_STRU      *pstPlmnSearchReq
)
{
    NAS_MML_PLMN_WITH_RAT_STRU          stGeoPlmn;

    /* 不是开机搜网或PLMN无效 */
    if ((VOS_FALSE == NAS_MML_IsPlmnIdValid(&(pstPlmnSearchReq->stInitAcqPlmnInfo.stInitAcqPlmnId)))
     || (NAS_MSCC_PIF_ACQ_REASON_POWER_UP != pstPlmnSearchReq->enAcqReason))
    {
        return;
    }

    PS_MEM_SET(&stGeoPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    /* 保存MSCC带下来的PLMN */
    stGeoPlmn.enRat             = pstPlmnSearchReq->stInitAcqPlmnInfo.enRat;
    stGeoPlmn.stPlmnId.ulMcc    = pstPlmnSearchReq->stInitAcqPlmnInfo.stInitAcqPlmnId.ulMcc;
    stGeoPlmn.stPlmnId.ulMnc    = pstPlmnSearchReq->stInitAcqPlmnInfo.stInitAcqPlmnId.ulMnc;

    NAS_MMC_SetGeoPlmn(&stGeoPlmn);

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_SndMsccSrchedGuPlmnInfo
 功能描述  : 向MSCC发送Searched GU PLMN INFO
 输入参数  : pstInterPlmnSearchInfo - 搜网失败带上来存在的网络信息
             enRat                  - 接入技术
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年1月15日
   作    者   : h00285180
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccSrchedGuPlmnInfo(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    RRMM_SEARCHED_PLMN_INFO_IND_STRU   *pstSearchedPlmnInfoMsg
)
{
    MMC_MSCC_SRCHED_PLMN_INFO_IND_STRU stMmcSrchedPlmnINfo;
    VOS_UINT32                         i;

    PS_MEM_SET(&stMmcSrchedPlmnINfo, 0, sizeof(stMmcSrchedPlmnINfo));

    if (NAS_RRC_MAX_AVAILPLMN_NUM < pstSearchedPlmnInfoMsg->ulAvailPlmnNum)
    {
        pstSearchedPlmnInfoMsg->ulAvailPlmnNum = NAS_RRC_MAX_AVAILPLMN_NUM;
    }
    stMmcSrchedPlmnINfo.ulLaiNum = pstSearchedPlmnInfoMsg->ulAvailPlmnNum;
    if (NAS_MSCC_PIF_MAX_SRCHED_LAI_NUM < stMmcSrchedPlmnINfo.ulLaiNum)
    {
        stMmcSrchedPlmnINfo.ulLaiNum = NAS_MSCC_PIF_MAX_SRCHED_LAI_NUM;
    }

    stMmcSrchedPlmnINfo.enRat = enRat;

    for (i = 0; i < stMmcSrchedPlmnINfo.ulLaiNum; i++)
    {
        stMmcSrchedPlmnINfo.astLai[i].stPlmnId.ulMcc = pstSearchedPlmnInfoMsg->astPlmnWithLacList[i].stPlmnId.ulMcc;
        stMmcSrchedPlmnINfo.astLai[i].stPlmnId.ulMnc = pstSearchedPlmnInfoMsg->astPlmnWithLacList[i].stPlmnId.ulMnc;
        stMmcSrchedPlmnINfo.astLai[i].usLac          = pstSearchedPlmnInfoMsg->astPlmnWithLacList[i].usLac;
    }

    NAS_MMC_SndMsccSrchedPlmnInfo(&stMmcSrchedPlmnINfo);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndMsccSrchedLtePlmnInfo
 功能描述  : 向MSCC发送Searched LTE PLMN INFO
 输入参数  : pstSearchedPlmnInfoInd - 搜网失败带上来存在的网络信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年1月15日
   作    者   : h00285180
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccSrchedLtePlmnInfo(
    LMM_MMC_SEARCHED_PLMN_INFO_IND_STRU                    *pstSearchedPlmnInfoInd
)
{
    MMC_MSCC_SRCHED_PLMN_INFO_IND_STRU stMmcSrchedPlmnINfo;
    VOS_UINT32                         i;
    MSCC_MMC_PLMN_ID_STRU              stGuNasPlmn;

    PS_MEM_SET(&stMmcSrchedPlmnINfo, 0, sizeof(stMmcSrchedPlmnINfo));

    if (LMM_MMC_MAX_SEARCHED_TAI_NUM < pstSearchedPlmnInfoInd->ulTaiNum)
    {
        pstSearchedPlmnInfoInd->ulTaiNum = LMM_MMC_MAX_SEARCHED_TAI_NUM;
    }
    stMmcSrchedPlmnINfo.ulLaiNum = pstSearchedPlmnInfoInd->ulTaiNum;
    if (NAS_MSCC_PIF_MAX_SRCHED_LAI_NUM < pstSearchedPlmnInfoInd->ulTaiNum)
    {
        stMmcSrchedPlmnINfo.ulLaiNum = NAS_MSCC_PIF_MAX_SRCHED_LAI_NUM;
    }

    stMmcSrchedPlmnINfo.enRat = NAS_MSCC_PIF_NET_RAT_TYPE_LTE;

    for (i = 0; i < stMmcSrchedPlmnINfo.ulLaiNum; i++)
    {

        NAS_MMC_ConvertLmmPlmnToGUNasFormat(&pstSearchedPlmnInfoInd->stTaiList[i].stPlmnId,
                                            &stGuNasPlmn);

        stMmcSrchedPlmnINfo.astLai[i].stPlmnId = stGuNasPlmn;
        stMmcSrchedPlmnINfo.astLai[i].usLac    = (pstSearchedPlmnInfoInd->stTaiList[i].stTac.ucTac << 8) | (pstSearchedPlmnInfoInd->stTaiList[i].stTac.ucTacCnt);
    }

    NAS_MMC_SndMsccSrchedPlmnInfo(&stMmcSrchedPlmnINfo);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedUpdateSpecRatPlmnSearchInfo_PlmnSelection
 功能描述  : 收到内部搜网消息时是否需要更新指定rat的搜网相关信息
 输入参数  : NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstPlmnListInfo
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月4日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MMC_IsNeedUpdateSpecRatPlmnSearchInfo_PlmnSelection(
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstPlmnListInfo
)
{
    NAS_MMC_NON_OOS_PLMN_SEARCH_FEATURE_SUPPORT_CFG_STRU   *pstOosCfg   = VOS_NULL_PTR;
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene;

    pstOosCfg           = NAS_MMC_GetNonOosPlmnSearchFeatureSupportCfg();
    enPlmnSearchScene   = NAS_MMC_GetPlmnSearchScene_PlmnSelection();

    /* 和t00173447确认，对于软银定制需求，国外丢网先搜RPLMN，并且RPLMN只搜当前模，
       连接态时，如果W的RPLMN已经全频段搜索过，此时不会更新为不存在，再多搜一次W的RPLMN也没有问题 */
    if (NAS_MMC_PLMN_SEARCH_SCENE_AREA_LOST_ROAMING_CFG == enPlmnSearchScene)
    {
        return VOS_FALSE;
    }

    /* 漫游搜网优化3.0只针对area lost场景作了修改，其他场景保持原来的处理 */
    if (NAS_MMC_PLMN_SEARCH_SCENE_AREA_LOST != enPlmnSearchScene)
    {
        return VOS_TRUE;
    }

    /* 没有进行过pref band搜索或spec搜索，不更新 */
    if ((VOS_FALSE == pstPlmnListInfo->stSearchedType.ucPrefBandSearchedFlg)
     || (VOS_FALSE == pstPlmnListInfo->stSearchedType.ucSpecSearchedFlg))
    {
        return VOS_FALSE;
    }

    /* NV配置area lost场景history之后需要进行spec搜或pref band搜，不更新  */
    if (NAS_MMC_PLMN_SEARCH_TYPE_AFTER_HISTORY_NONE != pstOosCfg->enSearchTypeAfterHistoryInAreaLostScene)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsSpecRatSearched_PlmnSelection
 功能描述  : 指定接入技术是否已经被搜索过
 输入参数  : enSpecRat
 输出参数  : 无
 返 回 值  : VOS_TRUE:已搜索过; VOS_FALSE:未搜索过
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月13日
    作    者   : l00289540
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MMC_IsSpecRatSearched_PlmnSelection(NAS_MML_NET_RAT_TYPE_ENUM_UINT8 enSpecRat)
{
    VOS_UINT8                            ucSearchAllBand;
    NAS_MMC_COVERAGE_TYPE_ENUM_UINT8     enCoverageType;

    ucSearchAllBand           = NAS_MMC_GetAllBandSearch_PlmnSelection(enSpecRat);
    enCoverageType            = NAS_MMC_GetRatCoverage_PlmnSelection(enSpecRat);

    if ( (NAS_MMC_COVERAGE_TYPE_LOW     == enCoverageType)
       ||(NAS_MMC_COVERAGE_TYPE_HIGH    == enCoverageType)
       ||(VOS_TRUE                      == ucSearchAllBand))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedSetLmmAttachClReqStatus_PlmnSelection
 功能描述  : 判断是否需要设置cl attach注册状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月22日
    作    者   : wx270776
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedUpdateLmmAttachClRegStatus_PlmnSelection(
    MMC_LMM_ATTACH_CL_REG_STATUS_ENUM8  enLmmAttachClRegStatusFromLmm
)
{
    VOS_UINT32                          ulOldAttachRegStatusPriority;
    VOS_UINT32                          ulNewAttachRegStatusPriority;
    MMC_LMM_ATTACH_CL_REG_STATUS_ENUM8  enOldLmmAttachRegStatus;

    enOldLmmAttachRegStatus = NAS_MMC_GetLmmAttachClRegStatus_PlmnSelection();

    /* 获取新旧注册状态优先级 */
    ulOldAttachRegStatusPriority = NAS_MMC_GetLmmAttaClRegStatPrioValue(enOldLmmAttachRegStatus);
    ulNewAttachRegStatusPriority = NAS_MMC_GetLmmAttaClRegStatPrioValue(enLmmAttachClRegStatusFromLmm);

    /* 权值越大，优先级越高 */
    if (ulNewAttachRegStatusPriority > ulOldAttachRegStatusPriority)
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}
/*lint -restore */

#ifdef  __cplusplus
#if  __cplusplus
  }
#endif
#endif
