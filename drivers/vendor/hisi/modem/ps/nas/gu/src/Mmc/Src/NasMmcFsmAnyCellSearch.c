/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcFsmAnyCellSearch.c
  版 本 号   : 初稿
  作    者   : w00176964
  生成日期   : 2011年04月25日
  最近修改   :
  功能描述   : ANY CELL搜网处理文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年04月25日
    作    者   : w00176964
    修改内容   : 创建文件
  2.日    期   : 2011年07月20日
    作    者   : l00130025
    修改内容   : PhaseII,Anycell搜网修改
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/

#include "NasMmcSndGmm.h"
#include "NasMmcSndMm.h"
#include "NasMmcSndGuAs.h"
#include "NasMmcSndLmm.h"
#include "NasMmcSndInternalMsg.h"
#include "NasMmcTimerMgmt.h"
#include "NasMmcCtx.h"
#include "NasMmcFsmAnyCellSearch.h"
#include "NasMmcFsmAnyCellSearchTbl.h"
#include "NasComm.h"
#include "NasMmlLib.h"
#include "NasMmlCtx.h"
#include "NasMmcSndMscc.h"
#include "NasMmcComFunc.h"
#include "NasMmcSndOm.h"

#include "NasMmcPlmnSelectionStrategy.h"

#include "NasUtranCtrlInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_FSM_ANYCELL_SEARCH_C


/*lint -save -e958 */

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTafPlmnSrchReq_AnyCellSearch_Init
 功能描述  : 无卡开机搜网处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年4月25日
   作    者   : w00176964
   修改内容   : 新生成函数

 2.日    期   : 2011年11月28日
   作    者   : w00167002
   修改内容   : DTS2011112804693:ANYCELL搜网时，若当前SIM/USIM卡不存在或者
                 CS/PS域都处于卡无效状态，则在ANYCELL搜网前通知GU AS当前卡无效。
 3.日    期   : 2012年11月9日
   作    者  :  z00161729
   修改内容  :  DTS2012110808375:W下注册被拒#3导致cs ps卡无效需通知Gas,否则w acceptable小区重选到g，
                g不知卡无效会发起suitable小区重选到L
 4.日    期   : 2013年05月08日
   作    者   : s46746
   修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
 5.日    期   : 2013年11月01日
   作    者   : l00208543
   修改内容   : 根据卡类型禁止网络制式
 6.日    期   : 2014年1月22日
   作    者   : w00167002
   修改内容   : SVLTE共天线:MMC又触发了新一轮的搜网，则清除NO RF标记信息。
 7.日    期   : 2014年4月14日
   作    者   : s00261364
   修改内容   : V3R360_eCall项目:搜网时更新服务状态
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTafPlmnSrchReq_AnyCellSearch_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat;

    NAS_MML_SIM_STATUS_STRU            *pstSimStatus    = VOS_NULL_PTR;

    enRat = NAS_MML_NET_RAT_TYPE_BUTT;

    /* 保存入口消息 */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

    /* 初始化ANYCELL状态机的要搜索的接入技术 */
    NAS_MMC_SetRatPrioList_AnyCellSearch(NAS_MML_GetMsPrioRatList());

    /* 获取下个要搜索的网络接入技术 */
    enRat = NAS_MMC_GetNextSearchRat_AnyCellSearch();

    if ( NAS_MML_NET_RAT_TYPE_BUTT == enRat )
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        /* 发送搜网失败结果 */
        NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_FAIL);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }


    /* 选网状态机发起选网，则清除NO RF标记 */


    /* 在发起Anycell Search之前如果发现Utran被Disable，就重新Enable Utran */
    NAS_MMC_UpdateUtranCapabilityStatus_AnyCellSearch_Init();

    /* 更新当前的网络接入模式 */
    NAS_MML_SetCurrNetRatType(enRat);

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

    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_START,
                VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    pstSimStatus = NAS_MML_GetSimStatus();

    /* 当前USIM卡不存在或者CS/PS域都卡无效，则需要通知GUAS当前卡无效 */
    if ( (VOS_FALSE   == NAS_MML_GetSimPresentStatus())
      || ( (VOS_FALSE == pstSimStatus->ucSimPsRegStatus)
        && (VOS_FALSE == pstSimStatus->ucSimCsRegStatus) ) )
    {
        NAS_MMC_SndAsNasUsimStatus(RRC_NAS_USIM_INVALID);
    }


    /* 向接入层或LMM发送搜网请求，根据不同的搜网模式，迁移到不同的L2状态，并启动保护定时器 */
    NAS_MMC_SndAnyCellPlmnSearchReq_AnyCellSearch(enRat);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcInterPlmnSearchReq_AnyCellSearch_Init
 功能描述  : 注册被拒导致卡无效后，收到MMC内部搜网请求处理
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
  2.日    期   : 2011年11月28日
    作    者   : w00167002
    修改内容   : DTS2011112804693:ANYCELL搜网时，若当前SIM/USIM卡不存在或者
                  CS/PS域都处于卡无效状态，则在ANYCELL搜网前通知GU AS当前卡无效。
  3.日    期   : 2012年10月8日
    作    者   : t00212959
    修改内容   : DTS2012092905927:处理缓存的anycell搜网消息时，现在支持的接入技术有可能已经发生改变
  4.日    期   : 2012年11月9日
    作    者  :  z00161729
    修改内容  :  DTS2012110808375:W下注册被拒#3导致cs ps卡无效需通知Gas,否则w acceptable小区重选到g，
                 g不知卡无效会发起suitable小区重选到L
  5.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  6.日    期   : 2013年11月01日
    作    者   : l00208543
    修改内容   : 根据卡类型禁止网络制式
  7.日    期   : 2014年1月22日
    作    者   : w00167002
    修改内容   : SVLTE共天线:MMC又触发了新一轮的搜网，则清除NO RF标记信息。
 8. 日    期   : 2014年4月14日
    作    者   : s00261364
    修改内容   : V3R360_eCall项目:搜网时更新服务状态

 9.日    期   : 2014年11月4日
   作    者   : w00167002
   修改内容   : DTS2014103102839:L下拨打电话HO到W失败回退到L，则尝试搜网发起紧急呼
                ，ANYCELL挂起L到GU下搜网，当前L下支持链接态发起挂起操作。
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcInterPlmnSearchReq_AnyCellSearch_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enRat;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enCurrRatType;
    NAS_MMC_INTER_PLMN_SEARCH_REQ_STRU                     *pstInterPlmnSrchMsg = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU                              stRatPrioList;

    NAS_MML_SIM_STATUS_STRU            *pstSimStatus    = VOS_NULL_PTR;

    /* 保存入口消息 */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

    pstInterPlmnSrchMsg = (NAS_MMC_INTER_PLMN_SEARCH_REQ_STRU*)pstMsg;

    /* 初始化ANYCELL状态机的要搜索的接入技术 */
    NAS_MMC_GetCoverageRatPrioList_Anycell(pstInterPlmnSrchMsg, &stRatPrioList);

    /* 删除MS不支持的模式 */
    NAS_MMC_DelMsUnsupportRat(&stRatPrioList);

    NAS_MMC_SetRatPrioList_AnyCellSearch(&stRatPrioList);

    /* 获取下个要搜索的网络接入技术 */
    enRat = NAS_MMC_GetNextSearchRat_AnyCellSearch();

    if ( VOS_TRUE == NAS_MMC_IsNeedRejectAnycellSerach_AnyCellSearch() )
    {
        /* 发送搜网失败结果 */
        NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_REJECT);

        /* 退状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    if ( NAS_MML_NET_RAT_TYPE_BUTT == enRat )
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        /* 发送搜网失败结果 */
        NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_FAIL);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }




    /* 在发起Anycell Search之前如果发现Utran被Disable，就重新Enable Utran */
    NAS_MMC_UpdateUtranCapabilityStatus_AnyCellSearch_Init();

    /* 向GMM发送搜网指示 */
    NAS_MMC_SndGmmPlmnSchInit();

    /* 向MM发送搜网指示 */
    NAS_MMC_SndMmPlmnSchInit();

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, end */

    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_START,
                VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    enCurrRatType = NAS_MML_GetCurrNetRatType();

    /* 与当前接入技术相同则发送搜网，启动保护定时器 或者当前接入技术为Butt,
       对应的场景是选网状态机挂起接入层状态接收到Abort消息,接入层回复SUSPNED CNF
       后会将当前接入模式设置为Butt再退出,表示可以向任何接入技术直接发起搜网 */
    if ((enRat == enCurrRatType)
     || (NAS_MML_NET_RAT_TYPE_BUTT == enCurrRatType))
    {
        NAS_MML_SetCurrNetRatType(enRat);

        pstSimStatus = NAS_MML_GetSimStatus();

        /* 当前USIM卡不存在或者CS/PS域都卡无效，则需要通知GUAS当前卡无效 */
        if ( (VOS_FALSE   == NAS_MML_GetSimPresentStatus())
          || ( (VOS_FALSE == pstSimStatus->ucSimPsRegStatus)
            && (VOS_FALSE == pstSimStatus->ucSimCsRegStatus) ) )
        {
            NAS_MMC_SndAsNasUsimStatus(RRC_NAS_USIM_INVALID);
        }

        /* 向接入层或LMM发送搜网请求，根据不同的搜网模式，迁移到不同的L2状态，并启动保护定时器 */
        NAS_MMC_SndAnyCellPlmnSearchReq_AnyCellSearch(enRat);
    }
    else
    {
        /* 向接入层或LMM发送挂起请求，根据不同的搜网模式，迁移到不同的L2状态，并启动保护定时器 */
        NAS_MMC_SndSuspendReq_AnyCellSearch(enCurrRatType);
    }

    NAS_MMC_UpdateRegStateSpecPlmnSearch();

    /* Added by s00261364 for V3R360_eCall项目, 2014-4-14, begin */
    NAS_MMC_UpdateServiceStateSpecPlmnSearch();
    /* Added by s00261364 for V3R360_eCall项目, 2014-4-14, end */

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcInterAnycellSearchReq_AnyCellSearch_Init
 功能描述  : ANY CELL下MMC内部搜网请求处理
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
  2.日    期   : 2011年11月28日
    作    者   : w00167002
    修改内容   : DTS2011112804693:ANYCELL搜网时，若当前SIM/USIM卡不存在或者
                CS/PS域都处于卡无效状态，则在ANYCELL搜网前通知GU AS当前卡无效。
  3.日    期   : 2012年10月8日
    作    者   : t00212959
    修改内容   : DTS2012092905927:处理缓存的anycell搜网消息时，现在支持的接入技术有可能已经发生改变
  4.日    期   : 2012年11月9日
    作    者  :  z00161729
    修改内容  :  DTS2012110808375:W下注册被拒#3导致cs ps卡无效需通知Gas,否则w acceptable小区重选到g，
                g不知卡无效会发起suitable小区重选到L
  5.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  6.日    期   : 2013年11月01日
    作    者   : l00208543
    修改内容   : 根据卡类型禁止网络制式
  7.日    期   : 2014年1月22日
    作    者   : w00167002
    修改内容   : SVLTE共天线:MMC又触发了新一轮的搜网，则清除NO RF标记信息。
  8.日    期   : 2014年4月24日
    作    者   : w00242748
    修改内容   : DTS2014042405819:无卡状态下，紧急呼被拒#5，后发起ANYCELL搜，导致退状态机
                 后下发RRMM_UE_OOC_STATUS_NOTIFY_IND，导致网络不断下发CM SERVICE REJ
    修改内容   : SVLTE共天线:MMC又触发了新一轮的搜网，则清除NO RF标记信息。
  9.日    期   : 2014年4月14日
    作    者   : s00261364
    修改内容   : V3R360_eCall项目:搜网时更新服务状态
 10.日    期   : 2014年7月1日
    作    者   : z00161729
    修改内容   : DSDS III修改
 11.日    期   : 2014年10月13日
    作    者   : w00167002
    修改内容   : DTS2014102005694:G下，CS注册成功后，PS还未注册成功时候，则
               发起电话业务，在电话业务建联时候丢网，MM没有释放信令，MMC没有发起ANY
               CELL搜网。
               在发起ANYCELL时候，MM的信令链接还存在，直接REJ了，跟闻晓确认此处内部保护先删除，
               没有明确问题场景。
12.日    期   : 2014年11月4日
   作    者   : w00167002
   修改内容   : DTS2014103102839:L下拨打电话HO到W失败回退到L，则尝试搜网发起紧急呼
                ，ANYCELL挂起L到GU下搜网，当前L下支持链接态发起挂起操作。
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcInterAnycellSearchReq_AnyCellSearch_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enRat;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enCurrRatType;
    NAS_MMC_INTER_ANYCELL_SEARCH_REQ_STRU                  *pstAnycellMsg = VOS_NULL_PTR;

    NAS_MML_SIM_STATUS_STRU                                *pstSimStatus    = VOS_NULL_PTR;

    /* 保存入口消息 */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

    pstAnycellMsg = (NAS_MMC_INTER_ANYCELL_SEARCH_REQ_STRU*)pstMsg;

    /* 初始化ANYCELL状态机的要搜索的接入技术 */

    /* 删除MS不支持的模式 */
    NAS_MMC_DelMsUnsupportRat(&(pstAnycellMsg->stAnycellSrchRatList));

    NAS_MMC_SetRatPrioList_AnyCellSearch(&(pstAnycellMsg->stAnycellSrchRatList));

    /* 获取下个要搜索的网络接入技术 */
    enRat         = NAS_MMC_GetNextSearchRat_AnyCellSearch();

    if ( VOS_TRUE == NAS_MMC_IsNeedRejectAnycellSerach_AnyCellSearch() )
    {
        /* 发送搜网失败结果 */
        NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_REJECT);

        /* 退状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    if ( NAS_MML_NET_RAT_TYPE_BUTT == enRat )
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        /* 发送搜网失败结果 */
        NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_FAIL);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }





    /* 在发起Anycell Search之前如果发现Utran被Disable，就重新Enable Utran */
    NAS_MMC_UpdateUtranCapabilityStatus_AnyCellSearch_Init();

    /* 向GMM发送搜网指示 */
    NAS_MMC_SndGmmPlmnSchInit();

    /* 向MM发送搜网指示 */
    NAS_MMC_SndMmPlmnSchInit();

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, end */

    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_START,
                VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    enCurrRatType = NAS_MML_GetCurrNetRatType();

    /* 与当前接入技术相同则发送搜网，启动保护定时器 或者当前接入技术为Butt,
       对应的场景是选网状态机挂起接入层状态接收到Abort消息,接入层回复SUSPNED CNF
       后会将当前接入模式设置为Butt再退出,表示可以向任何接入技术直接发起搜网 */
    if ((enRat == enCurrRatType)
     || (NAS_MML_NET_RAT_TYPE_BUTT == enCurrRatType))
    {
        NAS_MML_SetCurrNetRatType(enRat);

        pstSimStatus = NAS_MML_GetSimStatus();

        /* 当前USIM卡不存在或者CS/PS域都卡无效，则需要通知GUAS当前卡无效 */
        if ( (VOS_FALSE   == NAS_MML_GetSimPresentStatus())
          || ( (VOS_FALSE == pstSimStatus->ucSimPsRegStatus)
            && (VOS_FALSE == pstSimStatus->ucSimCsRegStatus) ) )
        {
            NAS_MMC_SndAsNasUsimStatus(RRC_NAS_USIM_INVALID);
        }

        /* 向接入层或LMM发送搜网请求，根据不同的搜网模式，迁移到不同的L2状态，并启动保护定时器 */
        NAS_MMC_SndAnyCellPlmnSearchReq_AnyCellSearch(enRat);
    }
    else
    {
        /* 向接入层或LMM发送挂起请求，根据不同的搜网模式，迁移到不同的L2状态，并启动保护定时器 */
        NAS_MMC_SndSuspendReq_AnyCellSearch(enCurrRatType);
    }

    NAS_MMC_UpdateRegStateSpecPlmnSearch();
    /* Added by s00261364 for V3R360_eCall项目, 2014-4-14, begin */
    NAS_MMC_UpdateServiceStateSpecPlmnSearch();
    /* Added by s00261364 for V3R360_eCall项目, 2014-4-14, end */


    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndSearchRslt_AnyCellSearch
 功能描述  : 发送anycell搜网的结果
 输入参数  : enResult - anycell搜网结果
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月30日
    作    者   : z00161729
    修改内容   : DSDS III新增

*****************************************************************************/
VOS_VOID NAS_MMC_SndSearchRslt_AnyCellSearch(
    NAS_MMC_ANYCELL_SEARCH_RESULT_ENUM_UINT32               enResult
)
{
#if (FEATURE_ON == FEATURE_DSDS)
    NAS_MMC_ENTRY_MSG_STRU                                 *pstEntryMsg    = VOS_NULL_PTR;
    NAS_MMC_INTER_ANYCELL_SEARCH_REQ_STRU                  *pstInterAnycellSearchReq = VOS_NULL_PTR;


    /* 根据FSM ID获取该FSM 入口消息 */
    pstEntryMsg              = NAS_MMC_GetCurrFsmMsgAddr();
    pstInterAnycellSearchReq = (NAS_MMC_INTER_ANYCELL_SEARCH_REQ_STRU *)pstEntryMsg->aucEntryMsgBuffer;

    if ((MMCMMC_INTER_ANYCELL_SEARCH_REQ == NAS_ExtractMsgNameFromEvtType(pstEntryMsg->ulEventType))
     && (NAS_MMC_ANYCELL_SEARCH_SCENE_SRV_TRIG_PLMN_SEARCH == pstInterAnycellSearchReq->enAnycellSearchScene))
    {
        /* 业务触发搜网，anycell搜网成功，需要回复mscc 搜网结果 */
        if (NAS_MMC_ANYCELL_SEARCH_SUCC == enResult)
        {
            NAS_MMC_SndMsccSrvAcqCnf(NAS_MSCC_PIF_SRV_ACQ_RESULT_SUCCESS);
        }
        else
        {
            NAS_MMC_SndMsccSrvAcqCnf(NAS_MSCC_PIF_SRV_ACQ_RESULT_FAIL);
        }
    }
#endif

    NAS_MMC_SndAnycellSearchRslt(enResult);
    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmPlmnSrchCnf_AnyCellSearch_WaitWasPlmnSrchCnf
 功能描述  : ANYCELL搜网时收到WAS搜网回复结果处理
 输入参数  : struct MsgCB                        *pMsg
             VOS_UINT32                          ulEventType
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月23日
    作    者   : w00176964
    修改内容   : 新生成函数

  2.日    期   : 2011年12月02日
    作    者   : w00167002
    修改内容   : DTS2011112804719:anycel成功后没有发SUITABLECELL给接入层
                 修改方案:在ANYCELL状态机增加等待系统消息的状态，若收到了
                 接入层上报的系统消息，且当前网路为可用网络，则通知接入层
                 重选类型为RESEL_SUITABLE。
  5.日    期   : 2014年1月21日
    作    者   : w00167002
    修改内容   : SVLTE共天线项目:在W下搜网失败为NO RF，表示当前天线资源不可用，
                 则当前搜网结束。
  6.日    期   : 2013年3月28日
    作    者   : y00176023
    修改内容   : DSDS GUNAS II项目:如果返回结果是NO RF则向RRM发起注册
  7.日    期   : 2014年6月27日
    作    者   : b00269685
    修改内容   : DSDS GUNAS III项目修改
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvRrMmPlmnSrchCnf_AnyCellSearch_WaitWasPlmnSrchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU                              *pstSrchCnfMsg = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enRat;

    pstSrchCnfMsg = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;

    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF);

    /* 对于搜索过的网络类型，需要记录下来，避免重复搜索 */
    NAS_MMC_SetSearchedFlag_AnyCellSearch(NAS_MML_NET_RAT_TYPE_WCDMA);


    /* ANYCELL搜网失败原因为NO RF,则退出ANYCELL状态机，等RF资源释放 */
    if ( RRC_PLMN_SEARCH_RLT_SPEC_NO_RF == pstSrchCnfMsg->ulSearchRlt )
    {
        /* 进行NO RF处理 */
        NAS_MMC_ProcNoRf_AnyCellSearch(NAS_MML_NET_RAT_TYPE_WCDMA);

        return VOS_TRUE;
    }

    NAS_MMC_UpdateRfAvailFlg_AnyCellSearch();

    if ( RRC_PLMN_SEARCH_RLT_SPEC_FAIL == pstSrchCnfMsg->ulSearchRlt )
    {
        /* 如果当前为单模或者其他模式都搜索过，则出服务区 */
        enRat = NAS_MMC_GetNextSearchRat_AnyCellSearch();

        if ( NAS_MML_NET_RAT_TYPE_BUTT == enRat )
        {
            NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                            VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

            /* 发送搜网失败结果 */
            NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_FAIL);


            /* 退出状态机 */
            NAS_MMC_FSM_QuitFsmL2();

            return VOS_TRUE;
        }

        /* 向接入层或LMM发送挂起请求，根据不同的搜网模式，迁移到不同的L2状态，并启动保护定时器 */
        NAS_MMC_SndSuspendReq_AnyCellSearch(NAS_MML_NET_RAT_TYPE_WCDMA);
    }
    else
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_SUCCESS,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);


        /* 迁移到等待系统消息上报状态 */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_ANYCELL_SEARCH_STA_WAIT_WAS_SYSINFO_IND);

        /* 并启动保护定时器 */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO, TI_NAS_MMC_WAIT_WAS_SYS_INFO_LEN);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmPlmnSrchCnf_AnyCellSearch_WaitGasPlmnSrchCnf
 功能描述  : ANYCELL搜网时收到GAS搜网回复结果处理
 输入参数  : struct MsgCB                        *pMsg
             VOS_UINT32                          ulEventType
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月23日
    作    者   : w00176964
    修改内容   : 新生成函数

  2.日    期   : 2011年12月02日
    作    者   : w00167002
    修改内容   : DTS2011112804719:anycel成功后没有发SUITABLECELL给接入层
                 修改方案:在ANYCELL状态机增加等待系统消息的状态，若收到了
                 接入层上报的系统消息，且当前网路为可用网络，则通知接入层
                 重选类型为RESEL_SUITABLE。
  5.日    期   : 2014年1月21日
    作    者   : w00167002
    修改内容   : SVLTE共天线项目:在W下搜网失败为NO RF，表示当前天线资源不可用，
                 则当前搜网结束。
  6.日    期   : 2013年3月29日
    作    者   : y00176023
    修改内容   : DSDS GUNAS II项目:如果ulSearchRlt为NO RF，那么就向RRM进行注册
  7.日    期   : 2014年6月27日
    作    者   : b00269685
    修改内容   : DSDS GUNAS III项目修改
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvRrMmPlmnSrchCnf_AnyCellSearch_WaitGasPlmnSrchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU                              *pstSrchCnfMsg = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enRat;

    pstSrchCnfMsg = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;

    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_SEARCH_CNF);

    /* 对于搜索过的网络类型，需要记录下来，避免重复搜索 */
    NAS_MMC_SetSearchedFlag_AnyCellSearch(NAS_MML_NET_RAT_TYPE_GSM);


    /* ANYCELL搜网失败原因为NO RF,则退出ANYCELL状态机，等RF资源释放 */
    if ( RRC_PLMN_SEARCH_RLT_SPEC_NO_RF == pstSrchCnfMsg->ulSearchRlt )
    {
        /* 进行NO RF处理 */
        NAS_MMC_ProcNoRf_AnyCellSearch(NAS_MML_NET_RAT_TYPE_GSM);

        return VOS_TRUE;
    }

    NAS_MMC_UpdateRfAvailFlg_AnyCellSearch();

    if ( RRC_PLMN_SEARCH_RLT_SPEC_FAIL == pstSrchCnfMsg->ulSearchRlt )
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        /* 如果当前为单模或者其他模式都搜索过，则出服务区 */
        enRat = NAS_MMC_GetNextSearchRat_AnyCellSearch();

        if ( NAS_MML_NET_RAT_TYPE_BUTT == enRat )
        {
            /* 发送搜网失败结果 */
            NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_FAIL);

            /* 退出状态机 */
            NAS_MMC_FSM_QuitFsmL2();

            return VOS_TRUE;
        }

        /* 向接入层或LMM发送挂起请求，根据不同的搜网模式，迁移到不同的L2状态，并启动保护定时器 */
        NAS_MMC_SndSuspendReq_AnyCellSearch(NAS_MML_NET_RAT_TYPE_GSM);
    }
    else
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_SUCCESS,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);


        /* 迁移到等待系统消息上报状态 */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_ANYCELL_SEARCH_STA_WAIT_GAS_SYSINFO_IND);

        /* 并启动保护定时器 */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_SYS_INFO, TI_NAS_MMC_WAIT_GAS_SYS_INFO_LEN);
    }

    return VOS_TRUE;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_AnyCellSearch_WaitWasPlmnSrchCnf
 功能描述  : 等待WAS搜网回复过程中收到Abort消息的处理
 输入参数  : pMsg:MMCMMC_ABORT_FSM_REQ
             ulEventType
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月23日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2014年2月18日
    作    者   : s00217060
    修改内容   : DTS2014021203453:设置打断标志，否则会在收到stop_cnf之后发起搜网

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_AnyCellSearch_WaitWasPlmnSrchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF);

    NAS_MMC_SetAbortFlag_AnyCellSearch(VOS_TRUE);

    /* 通知AS停止指定搜网 */
    NAS_MMC_SndAsPlmnSrchStopReq(WUEPS_PID_WRR);

    /* 迁移到等待搜网停止回复状态 */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_ANYCELL_SEARCH_STA_WAIT_WAS_PLMN_STOP_CNF);

    /* 并启动保护定时器 */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcUtranCtrlAbortFinishIndMsg_AnyCellSearch_WaitWasPlmnSrchCnf
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
VOS_UINT32 NAS_MMC_RcvMmcUtranCtrlAbortFinishIndMsg_AnyCellSearch_WaitWasPlmnSrchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMmcUtranCtrlAbortFinishIndMsg_AnyCellSearch_WaitWasPlmnSrchCnf");

    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF);

    NAS_MMC_SetAbortFlag_PlmnSelection(VOS_TRUE);

    NAS_MMC_UpdateRfAvailFlg_AnyCellSearch();

    /* 发送搜网Abort结果 */
    NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_ABORTED);

    /* 退出AnyCell状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_AnyCellSearch_WaitGasPlmnSrchCnf
 功能描述  : 等待GAS搜网回复过程中收到Abort消息的处理
 输入参数  : pMsg:MMCMMC_ABORT_FSM_REQ
             ulEventType
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月23日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2014年2月18日
    作    者   : s00217060
    修改内容   : DTS2014021203453:设置打断标志，否则会在收到stop_cnf之后发起搜网

*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_AnyCellSearch_WaitGasPlmnSrchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 通知AS停止快速指定搜网 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_SEARCH_CNF);

    NAS_MMC_SetAbortFlag_AnyCellSearch(VOS_TRUE);

    NAS_MMC_SndAsPlmnSrchStopReq(UEPS_PID_GAS);

    /* 迁移到等待搜网停止回复状态，并启动保护定时器*/
    NAS_MMC_FSM_SetCurrState(NAS_MMC_ANYCELL_SEARCH_STA_WAIT_GAS_PLMN_STOP_CNF);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmRelInd_AnyCellSearch_WaitWasPlmnSrchCnf
 功能描述  : 等待WAS搜网回复过程中收到RRMM_REL_IND消息的处理
 输入参数  : pMsg        - RRMM_REL_IND消息首地址
             ulEventType - 事件类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年12月05日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   : 2012年6月18日
   作    者   : l00171473
   修改内容   : DTS2012051104124, WAS:接收到RRMM_PLMN_SEARCH_REQ时，
                不会上报正常原因的rel ind，只有异常原因的rel ind
 3.日    期   : 2014年6月17日
   作    者   : w00167002
   修改内容   : DSDS III:WAS异常且当前NO RF,则进入OOC进行处理。
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvRrMmRelInd_AnyCellSearch_WaitWasPlmnSrchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrRatType;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat;

    RRMM_REL_IND_STRU                  *pstRrmmRelIndMsg    = VOS_NULL_PTR;

    pstRrmmRelIndMsg = (RRMM_REL_IND_STRU *)pstMsg;

    /* 无需判断原因值 */

    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvRrMmRelInd_AnyCellSearch_WaitWasPlmnSrchCnf: ENTERED");

    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF);


    /* ANYCELL搜网失败原因为NO RF,则退出ANYCELL状态机，等RF资源释放 */
    if (RRC_REL_CAUSE_NO_RF == pstRrmmRelIndMsg->ulRelCause)
    {
        /* 进行NO RF处理 */
        NAS_MMC_ProcNoRf_AnyCellSearch(NAS_MML_NET_RAT_TYPE_WCDMA);

        return VOS_TRUE;
    }

   /* 获取下个要搜索的网络接入技术 */
   enRat = NAS_MMC_GetNextSearchRat_AnyCellSearch();

   if ( NAS_MML_NET_RAT_TYPE_BUTT == enRat )
   {
       NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                       VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

       /* 发送搜网失败结果 */
       NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_FAIL);

       /* 退出状态机 */
       NAS_MMC_FSM_QuitFsmL2();

       return VOS_TRUE;
   }

   /* 向GMM发送搜网指示 */
   NAS_MMC_SndGmmPlmnSchInit();

   /* 向MM发送搜网指示 */
   NAS_MMC_SndMmPlmnSchInit();

   /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, begin */
   NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
   /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, end */

   NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_START,
                   VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

   enCurrRatType = NAS_MML_GetCurrNetRatType();

   /* 与当前接入技术相同则发送搜网，启动保护定时器 或者当前接入技术为Butt,
      对应的场景是选网状态机挂起接入层状态接收到Abort消息,接入层回复SUSPNED CNF
      后会将当前接入模式设置为Butt再退出,表示可以向任何接入技术直接发起搜网 */
   if ((enRat == enCurrRatType)
    || (NAS_MML_NET_RAT_TYPE_BUTT == enCurrRatType))
   {
       NAS_MML_SetCurrNetRatType(enRat);

       /* 向接入层或LMM发送搜网请求，根据不同的搜网模式，迁移到不同的L2状态，并启动保护定时器 */
       NAS_MMC_SndAnyCellPlmnSearchReq_AnyCellSearch(enRat);
   }
   else
   {
       /* 向接入层或LMM发送挂起请求，根据不同的搜网模式，迁移到不同的L2状态，并启动保护定时器 */
       NAS_MMC_SndSuspendReq_AnyCellSearch(enCurrRatType);
   }

   return VOS_TRUE;
}
/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitWasPlmnSrchCnfExpired_AnyCellSearch_WaitWasPlmnSrchCnf
 功能描述  : 等待WAS搜网回复过程中搜网定时器超时
 输入参数  : VOS_UINT32                          ulEventType,
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月23日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvTiWaitWasPlmnSrchCnfExpired_AnyCellSearch_WaitWasPlmnSrchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitWasPlmnSrchCnfExpired_AnyCellSearch_WaitWasPlmnSrchCnf: Timer Expired");

    /* 对于搜索过的网络类型，需要记录下来，避免重复搜索 */
    NAS_MMC_SetSearchedFlag_AnyCellSearch(NAS_MML_NET_RAT_TYPE_WCDMA);

    /* 通知AS停止指定搜网 */
    NAS_MMC_SndAsPlmnSrchStopReq(WUEPS_PID_WRR);

    /* 迁移到等待搜网停止回复状态 */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_ANYCELL_SEARCH_STA_WAIT_WAS_PLMN_STOP_CNF);

    /* 并启动保护定时器 */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitGasPlmnSrchCnfExpired_AnyCellSearch_WaitGasPlmnSrchCnf
 功能描述  : 等待GAS搜网回复过程中搜网定时器超时
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月23日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2014年6月6日
    作    者   : b00269685
    修改内容   : 定时器超时后先给接入层发送停止搜网消息

*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvTiWaitGasPlmnSrchCnfExpired_AnyCellSearch_WaitGasPlmnSrchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitGasPlmnSrchCnfExpired_AnyCellSearch_WaitGasPlmnSrchCnf: Timer Expired");

    /* 对于搜索过的网络类型，需要记录下来，避免重复搜索 */
    NAS_MMC_SetSearchedFlag_AnyCellSearch(NAS_MML_NET_RAT_TYPE_GSM);

    NAS_MMC_SndAsPlmnSrchStopReq(UEPS_PID_GAS);

    /* 迁移到等待搜网停止回复状态，并启动保护定时器*/
    NAS_MMC_FSM_SetCurrState(NAS_MMC_ANYCELL_SEARCH_STA_WAIT_GAS_PLMN_STOP_CNF);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmSuspendCnf_AnyCellSearch_WaitWasSuspendCnf
 功能描述  : 收到WAS的suspend cnf消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月23日
    作    者   : w00176964
    修改内容   : 新生成函数

  2.日    期   : 2011年11月28日
    作    者   : w00167002
    修改内容   : DTS2011112804693:ANYCELL搜网时，若当前SIM/USIM卡不存在或者
                CS/PS域都处于卡无效状态，则在ANYCELL搜网前通知GU AS当前卡无效。
  3.日    期   : 2011年12月15日
    作    者   : w00167002
    修改内容   : DTS2011120702166:MMC复位后无复位信息,在MML模块封装复位信息，
                  以供MM层调用，进行软复位。
  4.日    期   : 2012年5月15日
    作    者   : w00176964
    修改内容   : GUL BG项目调整:获取下个接入技术为BUTT需要退出状态机
  5.日    期   : 2012年11月9日
    作    者  :  z00161729
    修改内容  :  DTS2012110808375:W下注册被拒#3导致cs ps卡无效需通知Gas,否则w acceptable小区重选到g，
                g不知卡无效会发起suitable小区重选到L
  6.日    期   : 2014年2月18日
    作    者  :  w00242748
    修改内容  :  DTS2014021803515:复位时明确是收到哪个接入技术的异常消息导致的。
  7.日    期   : 2014年6月30日
    作    者   : b00269685
    修改内容   : DSDS GUNAS III项目修改

  8.日    期   : 2015年3月11日
    作    者   : wx270776
    修改内容   : 增加复位场景
*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvRrMmSuspendCnf_AnyCellSearch_WaitWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_CNF_ST                *pstSuspendCnf = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    NAS_MML_SIM_STATUS_STRU            *pstSimStatus    = VOS_NULL_PTR;

    pstSuspendCnf = (RRMM_SUSPEND_CNF_ST*)pstMsg;

    enCurRat      = NAS_MML_GetCurrNetRatType();

    /* 停止定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF);

    if (MMC_AS_SUSPEND_FAILURE == pstSuspendCnf->ucResult)
    {
        /* 不可恢复错误,调用底软接口RESET */
        if ( (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
          && (NAS_MML_NET_RAT_TYPE_WCDMA   == enCurRat) )
        {
            NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_WAS_SUSPEND_FAILURE);
        }
        else
        {
            NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_TD_SUSPEND_FAILURE);
        }

        return VOS_TRUE;
    }

    NAS_MMC_UpdateRfAvailFlg_AnyCellSearch();

    if (VOS_TRUE == NAS_MMC_GetAbortFlag_AnyCellSearch())
    {
        NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

        /* 发送搜网Abort结果 */
        NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_ABORTED);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 获取下个要搜索的网络接入技术 */
    enRat = NAS_MMC_GetNextSearchRat_AnyCellSearch();

    /* 等待GU挂起回复过程中用户detach PS会导致disable LTE,此时获取到的下个接入技术
       可能为BUTT */
    if ( NAS_MML_NET_RAT_TYPE_BUTT == enRat )
    {
        /* 发送搜网失败结果 */
        NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_FAIL);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 更改当前接入模式与网络模式 */
    NAS_MML_SetCurrNetRatType(enRat);

    pstSimStatus = NAS_MML_GetSimStatus();

    /* 当前USIM卡不存在或者CS/PS域都卡无效，则需要通知GUAS当前卡无效 */
    if ( (VOS_FALSE   == NAS_MML_GetSimPresentStatus())
      || ( (VOS_FALSE == pstSimStatus->ucSimPsRegStatus)
        && (VOS_FALSE == pstSimStatus->ucSimCsRegStatus) ) )
    {
        NAS_MMC_SndAsNasUsimStatus(RRC_NAS_USIM_INVALID);
    }


    /* 向接入层或LMM发送搜网请求，根据不同的搜网模式，迁移到不同的L2状态，并启动保护定时器 */
    NAS_MMC_SndAnyCellPlmnSearchReq_AnyCellSearch(enRat);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmSuspendCnf_AnyCellSearch_WaitGasSuspendCnf
 功能描述  : 收到GAS的suspend cnf消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月23日
    作    者   : w00176964
    修改内容   : 新生成函数

  2.日    期   : 2011年11月28日
    作    者   : w00167002
    修改内容   : DTS2011112804693:ANYCELL搜网时，若当前SIM/USIM卡不存在或者
                 CS/PS域都处于卡无效状态，则在ANYCELL搜网前通知GU AS当前卡无效。
  3.日    期   : 2011年12月15日
    作    者   : w00167002
    修改内容   : DTS2011120702166:MMC复位后无复位信息,在MML模块封装复位信息，
                  以供MM层调用，进行软复位。
  4.日    期   : 2012年5月15日
    作    者   : w00176964
    修改内容   : GUL BG项目调整:获取下个接入技术为BUTT需要退出状态机
  5.日    期   : 2012年11月9日
    作    者  :  z00161729
    修改内容  :  DTS2012110808375:W下注册被拒#3导致cs ps卡无效需通知Gas,否则w acceptable小区重选到g，
                 g不知卡无效会发起suitable小区重选到L
  6.日    期   : 2014年6月30日
    作    者   : b00269685
    修改内容   : DSDS GUNAS III项目修改

  7.日    期   : 2015年3月11日
    作    者   : wx270776
    修改内容   : 增加复位场景
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvRrMmSuspendCnf_AnyCellSearch_WaitGasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_CNF_ST                *pstSuspendCnf = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat;

    NAS_MML_SIM_STATUS_STRU            *pstSimStatus    = VOS_NULL_PTR;

    pstSuspendCnf = (RRMM_SUSPEND_CNF_ST*)pstMsg;

    /* 停止定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF);

    if (MMC_AS_SUSPEND_FAILURE == pstSuspendCnf->ucResult)
    {
        /* 不可恢复错误,调用底软接口RESET */
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_GAS_SUSPEND_FAILURE);

        return VOS_TRUE;
    }

    NAS_MMC_UpdateRfAvailFlg_AnyCellSearch();

    if (VOS_TRUE == NAS_MMC_GetAbortFlag_AnyCellSearch())
    {
        NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

        /* 发送搜网Abort结果 */
        NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_ABORTED);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 获取下个要搜索的网络接入技术 */
    enRat = NAS_MMC_GetNextSearchRat_AnyCellSearch();

    /* 等待GU挂起回复过程中用户detach PS会导致disable LTE,此时获取到的下个接入技术
       可能为BUTT */
    if ( NAS_MML_NET_RAT_TYPE_BUTT == enRat )
    {
        /* 发送搜网失败结果 */
        NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_FAIL);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 更改当前接入模式与网络模式*/
    NAS_MML_SetCurrNetRatType(enRat);

    pstSimStatus = NAS_MML_GetSimStatus();

    /* 当前USIM卡不存在或者CS/PS域都卡无效，则需要通知GUAS当前卡无效 */
    if ( (VOS_FALSE   == NAS_MML_GetSimPresentStatus())
      || ( (VOS_FALSE == pstSimStatus->ucSimPsRegStatus)
        && (VOS_FALSE == pstSimStatus->ucSimCsRegStatus) ) )
    {
        NAS_MMC_SndAsNasUsimStatus(RRC_NAS_USIM_INVALID);
    }

    /* 向接入层或LMM发送搜网请求，根据不同的搜网模式，迁移到不同的L2状态，并启动保护定时器 */
    NAS_MMC_SndAnyCellPlmnSearchReq_AnyCellSearch(enRat);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_AnyCellSearch_WaitAsSuspendCnf
 功能描述  : suspend CNF过程中当前状态机退出
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月23日
    作    者   : w00176964
    修改内容   : 新生成函数

****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_AnyCellSearch_WaitAsSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 记录需要退出当前状态机标志 */
    NAS_MMC_SetAbortFlag_AnyCellSearch(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitAsSuspendCnfExpired_AnyCellSearch_WaitAsSuspendCnf
 功能描述  : as的suspend CNF过程中保护定时器超时
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
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
    修改内容   : 增加复位场景

****************************************************************************/

VOS_UINT32 NAS_MMC_RcvTiWaitAsSuspendCnfExpired_AnyCellSearch_WaitAsSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    enCurRat      = NAS_MML_GetCurrNetRatType();

    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitAsSuspendCnfExpired_AnyCellSearch_WaitAsSuspendCnf: Timer Expired");

    /* 不可恢复故障，复位 */

    if ( (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
      && (NAS_MML_NET_RAT_TYPE_WCDMA   == enCurRat) )
    {
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_WAS_SUSPEND_CNF_EXPIRED);
    }
    else if ( NAS_MML_NET_RAT_TYPE_GSM == enCurRat)
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
 函 数 名  : NAS_MMC_RcvRrMmPlmnSearchStopCnf_AnyCellSearch_WaitWasPlmnStopCnf
 功能描述  : 收到WAS的plmn search stop cnf消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月23日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2014年6月6日
    作    者   : b00269685
    修改内容   : 增加非abort状态处理
  3.日    期   : 2014年6月30日
    作    者   : b00269685
    修改内容   : DSDS III项目修改

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvRrMmPlmnSearchStopCnf_AnyCellSearch_WaitWasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8        enRat;

    NAS_MMC_StopTimer( TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF );

    NAS_MMC_UpdateRfAvailFlg_AnyCellSearch();

    if (VOS_TRUE == NAS_MMC_GetAbortFlag_AnyCellSearch())
    {
        /* 发送搜网Abort结果 */
        NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_ABORTED);

        /* 退出AnyCell状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 如果当前为单模或者其他模式都搜索过，则出服务区 */
    enRat = NAS_MMC_GetNextSearchRat_AnyCellSearch();

    if ( NAS_MML_NET_RAT_TYPE_BUTT == enRat )
    {
        /* 发送搜网失败结果 */
        NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_FAIL);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 向接入层或LMM发送挂起请求，根据不同的搜网模式，迁移到不同的L2状态，并启动保护定时器 */
    NAS_MMC_SndSuspendReq_AnyCellSearch(NAS_MML_NET_RAT_TYPE_WCDMA);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmRelInd_AnyCellSearch_WaitWasPlmnStopCnf
 功能描述  : plmn search stop CNF过程中收到收到RRMM_REL_IND消息的处理
 输入参数  : ulEventType - 消息类型
             pstMsg      - 消息内容
 输出参数  : 无
 返 回 值  : VOS_FALSE - 处理消息失败
             VOS_TRUE  - 处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月5日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年6月18日
    作    者   : l00171473
    修改内容   : DTS2012051104124, WAS:接收到RRMM_PLMN_SEARCH_STOP_REQ时，
                 可能发送有异常原因的rel ind或者RRMM_PLMN_SEARCH_STOP_CNF,
                 收到rel ind时认为停止搜网结束
****************************************************************************/
VOS_UINT32 NAS_MMC_RcvRrMmRelInd_AnyCellSearch_WaitWasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 无需判断原因值 */

    NAS_MMC_StopTimer( TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF );

    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvRrMmRelInd_AnyCellSearch_WaitWasPlmnStopCnf: Timer Expired");

    /* 发送搜网Abort结果 */
    NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_ABORTED);

    /* 退出AnyCell状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmPlmnSearchStopCnf_AnyCellSearch_WaitGasPlmnStopCnf
 功能描述  : 收到GAS的plmn search stop cnf消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月23日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2014年6月6日
    作    者   : b00269685
    修改内容   : 增加非abort状态处理
  3.日    期   : 2014年6月30日
    作    者   : b00269685
    修改内容   : DSDS III项目修改

*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvRrMmPlmnSearchStopCnf_AnyCellSearch_WaitGasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat;

    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF);

    NAS_MMC_UpdateRfAvailFlg_AnyCellSearch();

    if (VOS_TRUE == NAS_MMC_GetAbortFlag_AnyCellSearch())
    {
        /* 发送搜网Abort结果 */
        NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_ABORTED);

        /* 退出AnyCell状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 如果当前为单模或者其他模式都搜索过，则出服务区 */
    enRat = NAS_MMC_GetNextSearchRat_AnyCellSearch();

    if ( NAS_MML_NET_RAT_TYPE_BUTT == enRat )
    {
        /* 发送搜网失败结果 */
        NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_FAIL);


        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 向接入层或LMM发送挂起请求，根据不同的搜网模式，迁移到不同的L2状态，并启动保护定时器 */
    NAS_MMC_SndSuspendReq_AnyCellSearch(NAS_MML_NET_RAT_TYPE_GSM);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitWasStopCnfExpired_AnyCellSearch_WaitWasPlmnStopCnf
 功能描述  : plmn search stop CNF过程中保护定时器超时
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月23日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2014年6月6日
    作    者   : b00269685
    修改内容   : 增加因为搜网cnf定时器超时而发送的停止搜网时的处理
  3.日    期   : 2014年6月30日
    作    者   : b00269685
    修改内容   : DSDS III项目修改

****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitWasStopCnfExpired_AnyCellSearch_WaitWasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8        enRat;

    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitWasStopCnfExpired_AnyCellSearch_WaitWasPlmnStopCnf: Timer Expired");

    NAS_MMC_UpdateRfAvailFlg_AnyCellSearch();

    if (VOS_TRUE == NAS_MMC_GetAbortFlag_AnyCellSearch())
    {
        /* 发送搜网Abort结果 */
        NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_ABORTED);

        /* 退出AnyCell状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 如果当前为单模或者其他模式都搜索过，则出服务区 */
    enRat = NAS_MMC_GetNextSearchRat_AnyCellSearch();

    if ( NAS_MML_NET_RAT_TYPE_BUTT == enRat )
    {
        /* 发送搜网失败结果 */
        NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_FAIL);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 向接入层或LMM发送挂起请求，根据不同的搜网模式，迁移到不同的L2状态，并启动保护定时器 */
    NAS_MMC_SndSuspendReq_AnyCellSearch(NAS_MML_NET_RAT_TYPE_WCDMA);


    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitGasStopCnfExpired_AnyCellSearch_WaitGasPlmnStopCnf
 功能描述  : plmn search stop CNF过程中保护定时器超时
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月23日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2014年6月6日
    作    者   : b00269685
    修改内容   : 增加因为搜网cnf定时器超时而发送的停止搜网时的处理
  3.日    期   : 2014年6月30日
    作    者   : b00269685
    修改内容   : DSDS III项目修改

****************************************************************************/

VOS_UINT32 NAS_MMC_RcvTiWaitGasStopCnfExpired_AnyCellSearch_WaitGasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8        enRat;

    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitGasStopCnfExpired_AnyCellSearch_WaitGasPlmnStopCnf: Timer Expired");

    NAS_MMC_UpdateRfAvailFlg_AnyCellSearch();

    if (VOS_TRUE == NAS_MMC_GetAbortFlag_AnyCellSearch())
    {
        /* 发送搜网Abort结果 */
        NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_ABORTED);

        /* 退出AnyCell状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 如果当前为单模或者其他模式都搜索过，则出服务区 */
    enRat = NAS_MMC_GetNextSearchRat_AnyCellSearch();

    if ( NAS_MML_NET_RAT_TYPE_BUTT == enRat )
    {
        /* 发送搜网失败结果 */
        NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_FAIL);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 向接入层或LMM发送挂起请求，根据不同的搜网模式，迁移到不同的L2状态，并启动保护定时器 */
    NAS_MMC_SndSuspendReq_AnyCellSearch(NAS_MML_NET_RAT_TYPE_GSM);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_AnyCellSearch_WaitWasSysInfoInd
 功能描述  : MMC处理QUIT的系统消息
 输入参数  : ulEventType:消息类型
             pstMsg:QUIT消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE 消息处理成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月02日
    作    者   : w00167002
    修改内容   : DTS2011112804719:anycel成功后没有发SUITABLECELL给接入层
                  修改方案:在ANYCELL状态机增加等待系统消息的状态，若收到了
                  接入层上报的系统消息，且当前网路为可用网络，则通知接入层
                  重选类型为RESEL_SUITABLE。
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_AnyCellSearch_WaitWasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    NAS_MMC_SetAbortFlag_AnyCellSearch(VOS_TRUE);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_AnyCellSearch_WaitGasSysInfoInd
 功能描述  : MMC处理QUIT的系统消息
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE 消息处理成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月02日
    作    者   : w00167002
    修改内容   : DTS2011112804719:anycel成功后没有发SUITABLECELL给接入层
                  修改方案:在ANYCELL状态机增加等待系统消息的状态，若收到了
                  接入层上报的系统消息，且当前网路为可用网络，则通知接入层
                  重选类型为RESEL_SUITABLE。

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_AnyCellSearch_WaitGasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    NAS_MMC_SetAbortFlag_AnyCellSearch(VOS_TRUE);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvSysInfoInd_AnyCellSearch_WaitWasSysInfoInd
 功能描述  : 处理WAS系统消息,
             1)记录MML的全部变量 2)向MM/GMM转发系统消息通知 3)更新当前网络的搜索状态
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:状态机处理成功
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年12月02日
   作    者   : w00167002
   修改内容   : DTS2011112804719:anycel成功后没有发SUITABLECELL给接入层
                 修改方案:在ANYCELL状态机增加等待系统消息的状态，若收到了
                 接入层上报的系统消息，且当前网路为可用网络，则通知接入层
                 重选类型为RESEL_SUITABLE。
 2.日    期   : 2012年3月17日
   作    者   : w00176964
   修改内容   : DTS2012031900095 V7R1 C30 SBM&EM定制需求:增加LTE国家漫游功能定制
 3.日    期   : 2012年3月17日
   作    者   : l65478
   修改内容   : DTS2012031907930 用户指定搜网注册失败#11重新开机后没有发起搜网
 4.日    期   : 2012年6月16日
   作    者   : l00171473
   修改内容   : DTS2012061409086, 收到W或G的系统消息时通知L模
 5.日    期   : 2012年7月27日
   作    者   : s00217060
   修改内容   : for CS/PS mode 1,带Disable LTE原因值
 6.日    期   : 2012年8月21日
   作    者   : z00161729
   修改内容   : DCM定制需求和遗留问题修改
 7.日    期   : 2012年12月11日
   作    者   : w00176964
   修改内容   : 收到系统消息接入禁止信息变化则通知MMA
 8.日    期   : 2013年1月17日
   作    者   : w00176964
   修改内容   : DTS2013011607305:GU下紧急呼叫导致的任意驻留，通知RRC进入suitable状态后
                后续可能不通知EPLMN，导致RRC无法驻留
 9.日    期   : 2013年3月30日
   作    者   : l00167671
   修改内容   : 主动上报AT命令控制下移至C核
 10.日    期   : 2013年12月24日
    作    者   : z00161729
    修改内容   : SVLTE支持NCELL搜网
 11.日    期   : 2014年1月18日
    作    者   : z00234330
    修改内容   : dts2014011801513,接入层上报的系统消息里面有可能没有携带plmnid,
                 此处判断并没有判断plmnid是否有效
 12.日    期   : 2014年1月23日
    作    者   : z00161729
    修改内容    : DTS2014012305088:svlte特性tds或l上系统消息后pstransfer:1，注册随机接入失败，ps迁移
                到modem1后tds或l再次驻留mmc收到系统消息判断驻留信息未改变不会给mma发送系统消息导致
                mtc无法上报pstransfer:1,需要在搜网状态机退出后给mma再发次系统消息
 13.日    期   : 2014年1月28日
    作    者   : s00246516
    修改内容   : L-C互操作项目:增加获取和注册请求的处理
 14.日    期   : 2014年5月4日
    作    者   : t00173447
    修改内容   : DTS2014042105390,软银定制需求

*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvSysInfoInd_AnyCellSearch_WaitWasSysInfoInd(
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

    NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8                enSpecPlmnSearchState;

    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, end */

    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;

    /* 获取LTE能力状态 */
    enLCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();

#endif

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    PS_MEM_SET(&stOldCsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_SET(&stOldPsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));

    /* 停止等待系统消息的定时器  */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO);

    /* 状态更新为当前已经驻留 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

    /* Added by s00246516 for L-C互操作项目, 2014-01-28, Begin */
    NAS_MMC_SetAsAnyCampOn(VOS_TRUE);
    /* Added by s00246516 for L-C互操作项目, 2014-01-28, End */

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_RcvGuSysInfoIndSetLteAbility(pstMsg,enLCapabilityStatus);
#endif

    /* 如果当前需要退出状态机 */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_AnyCellSearch())
    {
        /* 发送Abort结果 */
        NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_ABORTED);

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

    /* W下，非NAS_MML_PLMN_FORBID_PLMN，不存在RRC链接，且卡存在
       对于NAS_MML_PLMN_FORBID_PLMN_FOR_GPRS,只有在CS+PS的情况且CS卡有效的情况
       则通知接入层重选类型为RESEL_SUITABLE */
    if (VOS_TRUE == NAS_MMC_IsNeedSndAsSuitableCellSelReq_AnyCellSearch())
    {
        /* Added by s00246516 for L-C互操作项目, 2014-01-28, Begin */
        NAS_MMC_SetAsAnyCampOn(VOS_FALSE);
        /* Added by s00246516 for L-C互操作项目, 2014-01-28, End */

        NAS_MMC_SndRrMmCellSelReq(RRC_NAS_RESEL_SUITABLE);

        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));

        NAS_MMC_BuildEquPlmnInfo(&stSndEquPlmnInfo);

        NAS_MMC_SndGuAsEquPlmnReq(&stSndEquPlmnInfo, NAS_MML_GetCurrNetRatType());
        NAS_MMC_SndOmEquPlmn();

        NAS_MMC_SndMsccEplmnInfoInd(&stSndEquPlmnInfo);
    }
    /* 驻留小区变化或重新搜网时，上报系统消息 */
    enSpecPlmnSearchState = NAS_MMC_GetSpecPlmnSearchState();

    if ((VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
     || (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == enSpecPlmnSearchState))
    {
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
        /* 主动上报 */
        NAS_MMC_SndMsccSysInfo();
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

    }

    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_STOP);

    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
    /* 驻留小区的接入受限信息变化时,通知MMA模块当前接入受限信息 */
	/* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldCsRestrictInfo, pstCurCsRestrictInfo))
    {
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_CS, pstCurCsRestrictInfo);
    }

    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldPsRestrictInfo, pstCurPsRestrictInfo))
    {
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_PS, pstCurPsRestrictInfo);
    }
	/* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */
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

    /* 发送ANYCELL搜网成功结果 */
    NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_SUCC);


    /* 直接退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvSysInfoInd_AnyCellSearch_WaitGasSysInfoInd
 功能描述  : 处理GAS系统消息
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:状态机处理成功
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年12月02日
   作    者   : w00167002
   修改内容   : DTS2011112804719:anycel成功后没有发SUITABLECELL给接入层
                 修改方案:在ANYCELL状态机增加等待系统消息的状态，若收到了
                 接入层上报的系统消息，且当前网路为可用网络，则通知接入层
                 重选类型为RESEL_SUITABLE。
 2.日    期   : 2012年3月17日
   作    者   : l65478
   修改内容   : DTS2012031907930 用户指定搜网注册失败#11重新开机后没有发起搜网
 3.日    期   : 2012年6月16日
   作    者   : l00171473
   修改内容   : DTS2012061409086, 收到W或G的系统消息时通知L模
 4.日    期   : 2012年8月13日
   作    者   : t00212959
   修改内容   : DCM定制需求和遗留问题:增加LTE国家漫游功能定制
 5.日    期   : 2012年11月9日
   作    者   : z00161729
   修改内容   : DTS2012110808375:W下注册被拒#3导致cs ps卡无效需通知Gas,否则w acceptable小区重选到g，
                g不知卡无效会发起suitable小区重选到L
 6.日    期   : 2012年12月11日
   作    者   : w00176964
   修改内容   : 收到系统消息接入禁止信息变化则通知MMA
 7.日    期   : 2013年1月17日
   作    者   : w00176964
   修改内容   : DTS2013011607305:GU下紧急呼叫导致的任意驻留，通知RRC进入suitable状态后
                后续可能不通知EPLMN，导致RRC无法驻留
 8.日    期   : 2013年3月30日
   作    者   : l00167671
   修改内容   : 主动上报AT命令控制下移至C核
 9.日    期   : 2013年11月01日
   作    者   : l00208543
   修改内容   : 根据卡类型禁止网络制式
 10.日    期   : 2013年12月24日
    作    者   : z00161729
    修改内容   : SVLTE支持NCELL搜网
 11.日    期   : 2014年1月23日
    作    者   : z00161729
    修改内容    : DTS2014012305088:svlte特性tds或l上系统消息后pstransfer:1，注册随机接入失败，ps迁移
                到modem1后tds或l再次驻留mmc收到系统消息判断驻留信息未改变不会给mma发送系统消息导致
                mtc无法上报pstransfer:1,需要在搜网状态机退出后给mma再发次系统消息
 12.日    期   : 2014年1月28日
    作    者   : s00246516
    修改内容   : L-C互操作项目:增加获取和注册请求的处理
 13.日    期   : 2014年5月4日
    作    者   : t00173447
    修改内容   : DTS2014042105390,软银定制需求
*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvSysInfoInd_AnyCellSearch_WaitGasSysInfoInd(
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

    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;

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
    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));

    /* 停止等待系统消息的定时器  */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_SYS_INFO);

    /* 更新驻留状态 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

    /* Added by s00246516 for L-C互操作项目, 2014-01-28, Begin */
    NAS_MMC_SetAsAnyCampOn(VOS_TRUE);
    /* Added by s00246516 for L-C互操作项目, 2014-01-28, End */

    /* Added by t00212959 for DCM定制需求和遗留问题, 2012-8-13, begin */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_RcvGuSysInfoIndSetLteAbility(pstMsg, enLCapabilityStatus);
#endif
    /* Added by t00212959 for DCM定制需求和遗留问题, 2012-8-13, end */

    /* 如果Anycell Search状态下收到GAS的系统消息，且目前Utran被Enable，则重新Disable Utran */
    NAS_MMC_RcvGasSysInfoSetUtranCapabilityStatus();

    /* 如果当前需要退出状态机 */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_AnyCellSearch())
    {
        /* 发送Abort结果 */
        NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_ABORTED);


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

    /* G下，非NAS_MML_PLMN_FORBID_PLMN，不存在RRC链接，且卡存在
       则通知接入层重选类型为RESEL_SUITABLE */
    if (VOS_TRUE == NAS_MMC_IsNeedSndAsSuitableCellSelReq_AnyCellSearch())
    {
        /* Added by s00246516 for L-C互操作项目, 2014-01-28, Begin */
        NAS_MMC_SetAsAnyCampOn(VOS_FALSE);
        /* Added by s00246516 for L-C互操作项目, 2014-01-28, End */

        NAS_MMC_SndRrMmCellSelReq(RRC_NAS_RESEL_SUITABLE);

        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndGuAsEquPlmnReq(&stSndEquPlmnInfo, NAS_MML_GetCurrNetRatType());
        NAS_MMC_SndOmEquPlmn();

        NAS_MMC_SndMsccEplmnInfoInd(&stSndEquPlmnInfo);
    }
    /* 驻留小区变化或重新搜网时，上报系统消息 */
    enSpecPlmnSearchState = NAS_MMC_GetSpecPlmnSearchState();
    if ((VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
     || (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == enSpecPlmnSearchState))
    {
        /* 主动上报 */
		/* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
        NAS_MMC_SndMsccSysInfo();
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

    }

    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_STOP);

    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
    /* 驻留小区的接入受限信息变化时,通知MMA模块当前接入受限信息 */
    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldCsRestrictInfo, pstCurCsRestrictInfo))
    {

	    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_CS, pstCurCsRestrictInfo);
		/* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

    }

    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldPsRestrictInfo, pstCurPsRestrictInfo))
    {

	    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_PS, pstCurPsRestrictInfo);
		/* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

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

    /* 发送ANYCELL搜网成功结果 */
    NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_SUCC);


    /* 直接退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitSysInfoExpired_AnyCellSearch_WaitWasSysInfoInd
 功能描述  : 等待W系统消息超时，同丢网的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:状态机处理成功
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年12月02日
   作    者   : w00167002
   修改内容   : DTS2011112804719:anycel成功后没有发SUITABLECELL给接入层
                 修改方案:在ANYCELL状态机增加等待系统消息的状态，若收到了
                 接入层上报的系统消息，且当前网路为可用网络，则通知接入层
                 重选类型为RESEL_SUITABLE。
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiWaitSysInfoExpired_AnyCellSearch_WaitWasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitSysInfoExpired_AnyCellSearch_WaitWasSysInfoInd: Timer Expired");

    /* 如果当前需要退出状态机 */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_AnyCellSearch())
    {
        /* 发送Abort结果 */
        NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_ABORTED);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 发送ANYCELL搜网失败结果 */
    NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_FAIL);

    /* 直接退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitSysInfoExpired_AnyCellSearch_WaitGasSysInfoInd
 功能描述  : 等待g系统消息超时，同丢网的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:状态机处理成功
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年12月02日
   作    者   : w00167002
   修改内容   : DTS2011112804719:anycel成功后没有发SUITABLECELL给接入层
                 修改方案:在ANYCELL状态机增加等待系统消息的状态，若收到了
                 接入层上报的系统消息，且当前网路为可用网络，则通知接入层
                 重选类型为RESEL_SUITABLE。
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiWaitSysInfoExpired_AnyCellSearch_WaitGasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitSysInfoExpired_AnyCellSearch_WaitGasSysInfoInd: Timer Expired");

    /* 如果当前需要退出状态机 */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_AnyCellSearch())
    {
        /* 发送Abort结果 */
        NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_ABORTED);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 发送ANYCELL搜网失败结果 */
    NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_FAIL);

    /* 直接退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmPlmnSrchCnf_AnyCellSearch_WaitLmmPlmnSrchCnf
 功能描述  : ANYCELL搜网时收到LTE搜网回复结果处理
 输入参数  : struct MsgCB                        *pMsg
             VOS_UINT32                          ulEventType
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月23日
    作    者   : w00176964
    修改内容   : 新生成函数

  2.日    期   : 2011年12月02日
    作    者   : w00167002
    修改内容   : DTS2011112804719:anycel成功后没有发SUITABLECELL给接入层
                 修改方案:在ANYCELL状态机增加等待系统消息的状态，若收到了
                 接入层上报的系统消息，且当前网路为可用网络，则通知接入层
                 重选类型为RESEL_SUITABLE。
  3.日    期   : 2014年6月12日
    作    者   : w00167002
    修改内容   : DSDS III:L下NO RF后的处理
  4.日    期   : 2014年8月8日
    作    者   : w00242748
    修改内容   : DTS2014080704343:将ANYCELL标记提前设置，在进行ANYCELL搜，收到L的搜网回复时，
                 将该标志置上。
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmPlmnSrchCnf_AnyCellSearch_WaitLmmPlmnSrchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_PLMN_SRCH_CNF_STRU                             *pstLmmSrchCnfMsg = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enRat;

    pstLmmSrchCnfMsg = (LMM_MMC_PLMN_SRCH_CNF_STRU*)pstMsg;

    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF);

    /* 对于搜索过的网络类型，需要记录下来，避免重复搜索 */
    NAS_MMC_SetSearchedFlag_AnyCellSearch(NAS_MML_NET_RAT_TYPE_LTE);


    /* ANYCELL搜网失败原因为NO RF,则退出ANYCELL状态机，等RF资源释放 */
    if (MMC_LMM_PLMN_SRCH_RLT_SPEC_NO_RF == pstLmmSrchCnfMsg->enRlst)
    {
        /* 进行NO RF处理 */
        NAS_MMC_ProcNoRf_AnyCellSearch(NAS_MML_NET_RAT_TYPE_LTE);

        return VOS_TRUE;
    }

    NAS_MMC_UpdateRfAvailFlg_AnyCellSearch();

    if ( MMC_LMM_PLMN_SRCH_RLT_SPEC_FAIL == pstLmmSrchCnfMsg->enRlst )
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        /* 如果当前为单模或者其他模式都搜索过，则出服务区 */
        enRat = NAS_MMC_GetNextSearchRat_AnyCellSearch();

        if ( NAS_MML_NET_RAT_TYPE_BUTT == enRat )
        {
            /* 发送搜网失败结果 */
            NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_FAIL);

            /* 退出AnyCell状态机 */
            NAS_MMC_FSM_QuitFsmL2();

            return VOS_TRUE;
        }

        /* 向接入层或LMM发送挂起请求，根据不同的搜网模式，迁移到不同的L2状态，并启动保护定时器 */
        NAS_MMC_SndSuspendReq_AnyCellSearch(NAS_MML_NET_RAT_TYPE_LTE);
    }
    else
    {
        NAS_MMC_SetAsAnyCampOn(VOS_TRUE);

        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_SUCCESS,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);


        /* 迁移到等待系统消息上报状态 */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_ANYCELL_SEARCH_STA_WAIT_LMM_SYSINFO_IND);

        /* 并启动保护定时器 */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_SYS_INFO, TI_NAS_MMC_WAIT_LMM_SYS_INFO_LEN);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmAttachCnf_AnyCellSearch_WaitLmmPlmnSrchCnf
 功能描述  : 等待LTE搜网回复过程中收到LMM 的Attach CNF消息的处理
 输入参数  : pMsg:ID_LMM_MMC_ATTACH_CNF消息的首地址
             ulEventType:消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月3日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvLmmAttachCnf_AnyCellSearch_WaitLmmPlmnSrchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 当前LTE的能力状态不为DISABLE 状态，则不处理该消息 */
    if ( NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS != NAS_MML_GetLteCapabilityStatus())
    {
        /* 异常打印 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmDetachCnf_AnyCellSearch_WaitLmmPlmnSrchCnf: unexpect message received");

        return VOS_TRUE;
    }

    /* 通知AS停止快速指定搜网 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF);

    NAS_MMC_SndLmmPlmnSrchStopReq();

    /* 迁移到等待搜网停止回复状态，*/
    NAS_MMC_FSM_SetCurrState(NAS_MMC_ANYCELL_SEARCH_STA_WAIT_LMM_PLMN_STOP_CNF);

    /* 启动保护定时器 */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF_LEN);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmDetachCnf_AnyCellSearch_WaitLmmPlmnSrchCnf
 功能描述  : 等待LTE搜网回复过程中收到LMM 的detach CNF消息的处理
 输入参数  : pMsg:MMCMMC_ABORT_FSM_REQ
             ulEventType
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月14s日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvLmmDetachCnf_AnyCellSearch_WaitLmmPlmnSrchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 当前LTE的能力状态不为DISABLE 状态，则不处理该消息 */
    if ( NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS != NAS_MML_GetLteCapabilityStatus())
    {
        /* 异常打印 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmDetachCnf_AnyCellSearch_WaitLmmPlmnSrchCnf: unexpect message received");

        return VOS_TRUE;
    }

    /* 通知AS停止快速指定搜网 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF);

    NAS_MMC_SndLmmPlmnSrchStopReq();

    /* 迁移到等待搜网停止回复状态，*/
    NAS_MMC_FSM_SetCurrState(NAS_MMC_ANYCELL_SEARCH_STA_WAIT_LMM_PLMN_STOP_CNF);

    /* 启动保护定时器 */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF_LEN);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_AnyCellSearch_WaitLmmPlmnSrchCnf
 功能描述  : 等待LTE搜网回复过程中收到状态机退出消息的处理
 输入参数  : pMsg:MMCMMC_ABORT_FSM_REQ
             ulEventType
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月23日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2014年2月18日
    作    者   : s00217060
    修改内容   : DTS2014021203453:设置打断标志，否则会在收到stop_cnf之后发起搜网
  3.日    期   : 2014年8月8日
    作    者   : w00242748
    修改内容   : DTS2014080704343:将ANYCELL标记提前设置，在进行ANYCELL搜，收到L的搜网回复时，
                 将该标志置上。

*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_AnyCellSearch_WaitLmmPlmnSrchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 通知AS停止快速指定搜网 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF);

    NAS_MMC_SetAbortFlag_AnyCellSearch(VOS_TRUE);

    NAS_MMC_SetAsAnyCampOn(VOS_FALSE);

    NAS_MMC_SndLmmPlmnSrchStopReq();

    /* 迁移到等待搜网停止回复状态，*/
    NAS_MMC_FSM_SetCurrState(NAS_MMC_ANYCELL_SEARCH_STA_WAIT_LMM_PLMN_STOP_CNF);

    /* 启动保护定时器 */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF_LEN);

    return VOS_TRUE;
}
/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitLmmPlmnSrchCnfExpired_AnyCellSearch_WaitLmmPlmnSrchCnf
 功能描述  : 等待LTE搜网回复过程中搜网定时器超时
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月23日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2014年6月6日
    作    者   : b00269685
    修改内容   : 先通知接入层停止搜网

*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvTiWaitLmmPlmnSrchCnfExpired_AnyCellSearch_WaitLmmPlmnSrchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitLmmPlmnSrchCnfExpired_AnyCellSearch_WaitLmmPlmnSrchCnf: Timer Expired");

    /* 对于搜索过的网络类型，需要记录下来，避免重复搜索 */
    NAS_MMC_SetSearchedFlag_AnyCellSearch(NAS_MML_NET_RAT_TYPE_LTE);

    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF);

    /* 通知AS停止快速指定搜网 */
    NAS_MMC_SndLmmPlmnSrchStopReq();

    /* 迁移到等待搜网停止回复状态，*/
    NAS_MMC_FSM_SetCurrState(NAS_MMC_ANYCELL_SEARCH_STA_WAIT_LMM_PLMN_STOP_CNF);

    /* 启动保护定时器 */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmSuspendCnf_AnyCellSearch_WaitLmmSuspendCnf
 功能描述  : 收到LTE的suspend cnf消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月23日
    作    者   : w00176964
    修改内容   : 新生成函数

 2.日    期   : 2011年11月28日
   作    者   : w00167002
   修改内容   : DTS2011112804693:ANYCELL搜网时，若当前SIM/USIM卡不存在或者
                 CS/PS域都处于卡无效状态，则在ANYCELL搜网前通知GU AS当前卡无效。

 3.日    期   : 2011年12月15日
   作    者   : w00167002
   修改内容   : DTS2011120702166:MMC复位后无复位信息,在MML模块封装复位信息，
                 以供MM层调用，进行软复位。
 4.日    期   : 2012年11月9日
   作    者   :  z00161729
   修改内容   :  DTS2012110808375:W下注册被拒#3导致cs ps卡无效需通知Gas,否则w acceptable小区重选到g，
               g不知卡无效会发起suitable小区重选到L
 5.日    期   : 2012年12月11日
   作    者   : l00167671
   修改内容   : DTS2012121802573, TQE清理
 6.日    期   : 2013年6月7日
   作    者   : w00176964
   修改内容   : SS FDN&Call Control项目:更新PS的注册状态
 7.日    期   : 2014年3月10日
   作    者   : f00261443
   修改内容   : 更新PS的注册状态,并不一定是NAS_MML_REG_NOT_REGISTERED_SEARCHING
 8.日    期   : 2014年6月30日
    作    者  : b00269685
    修改内容  : DSDS III项目修改
 9.日    期   : 2015年3月11日
   作    者   : wx270776
   修改内容   : 增加复位场景
*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvLmmSuspendCnf_AnyCellSearch_WaitLmmSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_CNF_ST                 stGuSuspendCnf;
    LMM_MMC_SUSPEND_CNF_STRU           *pstLmmSuspendCnf = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat;
    NAS_MML_SIM_STATUS_STRU            *pstSimStatus    = VOS_NULL_PTR;

    /* L模时，做如下格式转换 */
    pstLmmSuspendCnf = (LMM_MMC_SUSPEND_CNF_STRU*)pstMsg;

    stGuSuspendCnf.ucResult = (VOS_UINT8)pstLmmSuspendCnf->ulRst;

    /* 停止定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_SUSPEND_CNF);

    if (MMC_AS_SUSPEND_FAILURE == stGuSuspendCnf.ucResult)
    {
        /* 不可恢复错误,调用底软接口RESET */

        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_LMM_SUSPEND_FAILURE);

        return VOS_TRUE;
    }

    NAS_MMC_UpdateRfAvailFlg_AnyCellSearch();

    if (VOS_TRUE == NAS_MMC_GetAbortFlag_AnyCellSearch())
    {
        NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

        /* 发送搜网Abort结果 */
        NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_ABORTED);

        /* 退出AnyCell状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 获取下个要搜索的网络接入技术 */
    enRat = NAS_MMC_GetNextSearchRat_AnyCellSearch();
    if (NAS_MML_NET_RAT_TYPE_BUTT == enRat)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }

    /* 更改当前接入模式与网络模式 */
    NAS_MML_SetCurrNetRatType(enRat);

    pstSimStatus = NAS_MML_GetSimStatus();

    /* 当前USIM卡不存在或者CS/PS域都卡无效，则需要通知GUAS当前卡无效 */
    if ( (VOS_FALSE   == NAS_MML_GetSimPresentStatus())
      || ( (VOS_FALSE == pstSimStatus->ucSimPsRegStatus)
        && (VOS_FALSE == pstSimStatus->ucSimCsRegStatus) ) )
    {
        NAS_MMC_SndAsNasUsimStatus(RRC_NAS_USIM_INVALID);
    }

    /* 向接入层或LMM发送搜网请求，根据不同的搜网模式，迁移到不同的L2状态，并启动保护定时器 */
    NAS_MMC_SndAnyCellPlmnSearchReq_AnyCellSearch(enRat);

    /* 保证挂起L回到GU时PS的注册状态始终为2,此处进行一次更新(挂起L时L可能上报的注册状态不为2) */
    NAS_MMC_UpdateRegStateSpecPlmnSearch();

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmPlmnSearchStopCnf_AnyCellSearch_WaitLmmPlmnStopCnf
 功能描述  : 收到LTE的plmn search stop cnf消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月23日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2012年5月14s日
    作    者   : w00176964
    修改内容   : GUL BG项目调整:disable LTE的场景
  3.日    期   : 2014年2月17日
    作    者   : s00217060
    修改内容   : DTS2014021203453:收到LmmStopCnf时如果已经Enable Lte，需要继续去LTE下搜网
  4.日    期   : 2014年6月30日
    作    者   : b00269685
    修改内容   : DSDS III项目修改
*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvLmmPlmnSearchStopCnf_AnyCellSearch_WaitLmmPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat;

    NAS_MMC_StopTimer( TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF );

    NAS_MMC_UpdateRfAvailFlg_AnyCellSearch();

    /* 有打断时，退出状态机 */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_AnyCellSearch())
    {
        /* 发送搜网Abort结果 */
        NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_ABORTED);

        /* 退出AnyCell状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 无打断时:如果当前LTE的能力状态为disable LTE，则搜索下个非LTE的网络
        如果当前LTE的能力状态为Enable LTE,则搜索下个可用的LTE网络
        Enable LTE对应的场景为:等LMM的搜网结果时收到LmmDetachCnf，需要Disable LTE,迁到等LmmStopCnf状态
        在等待LmmStopCnf时，收到LmmAttachCnf，又需要Enable LTE,此时在收到LmmStopCnf需要继续去LTE下搜网 */

    /* 获取下个要搜索的网络接入技术 */
    enRat = NAS_MMC_GetNextSearchRat_AnyCellSearch();

    /* 下个要搜索的网络不存在时，退出状态机 */
    if ( NAS_MML_NET_RAT_TYPE_BUTT == enRat )
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        /* 发送搜网失败结果 */
        NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_FAIL);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 下个要搜索的网络是LTE网络，直接发起搜网，否则先挂起LTE */
    if (NAS_MML_NET_RAT_TYPE_LTE == enRat)
    {
        /* 向LMM发送搜网请求，迁移状态，并启动保护定时器 */
        NAS_MMC_SndAnyCellPlmnSearchReq_AnyCellSearch(NAS_MML_NET_RAT_TYPE_LTE);
    }
    else
    {
        /* 向LMM发送挂起请求，迁移状态，并启动保护定时器 */
        NAS_MMC_SndSuspendReq_AnyCellSearch(NAS_MML_NET_RAT_TYPE_LTE);
    }

    return VOS_TRUE;



}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitLmmStopCnfExpired_AnyCellSearch_WaitLmmPlmnStopCnf
 功能描述  : plmn search stop CNF过程中保护定时器超时
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月23日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2012年5月14日
    作    者   : w00176964
    修改内容   : GUL BG项目调整:disable LTE场景
  3.日    期   : 2014年2月17日
    作    者   : s00217060
    修改内容   : DTS2014021203453:收到LmmStopCnf时如果已经Enable Lte，需要继续去LTE下搜网
  4.日    期   : 2014年6月30日
    作    者   : b00269685
    修改内容   : DSDS III项目修改
****************************************************************************/

VOS_UINT32 NAS_MMC_RcvTiWaitLmmStopCnfExpired_AnyCellSearch_WaitLmmPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat;

    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitLmmStopCnfExpired_AnyCellSearch_WaitLmmPlmnStopCnf: Timer Expired");

    NAS_MMC_UpdateRfAvailFlg_AnyCellSearch();

    /* 有打断时，退出状态机 */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_AnyCellSearch())
    {
        /* 发送搜网Abort结果 */
        NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_ABORTED);

        /* 退出AnyCell状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 无打断时:如果当前LTE的能力状态为disable LTE，则搜索下个非LTE的网络
        如果当前LTE的能力状态为Enable LTE,则搜索下个可用的LTE网络
        Enable LTE对应的场景为:等LMM的搜网结果时收到LmmDetachCnf，需要Disable LTE,迁到等LmmStopCnf状态
        在等待LmmStopCnf时，收到LmmAttachCnf，又需要Enable LTE,此时在收到LmmStopCnf需要继续去LTE下搜网 */

    /* 获取下个要搜索的网络接入技术 */
    enRat = NAS_MMC_GetNextSearchRat_AnyCellSearch();

    /* 下个要搜索的网络不存在时，退出状态机 */
    if ( NAS_MML_NET_RAT_TYPE_BUTT == enRat )
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        /* 发送搜网失败结果 */
        NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_FAIL);


        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 下个要搜索的网络是LTE网络，直接发起搜网，否则先挂起LTE */
    if (NAS_MML_NET_RAT_TYPE_LTE == enRat)
    {
        /* 向LMM发送搜网请求，迁移状态，并启动保护定时器 */
        NAS_MMC_SndAnyCellPlmnSearchReq_AnyCellSearch(NAS_MML_NET_RAT_TYPE_LTE);
    }
    else
    {
        /* 向LMM发送挂起请求，迁移状态，并启动保护定时器 */
        NAS_MMC_SndSuspendReq_AnyCellSearch(NAS_MML_NET_RAT_TYPE_LTE);
    }

    return VOS_TRUE;


}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_AnyCellSearch_WaitLmmSysInfoInd
 功能描述  : MMC处理Aort消息
 输入参数  : ulEventType:消息类型
             pstMsg:Abort消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年12月02日
   作    者   : w00167002
   修改内容   : DTS2011112804719:anycel成功后没有发SUITABLECELL给接入层
                 修改方案:在ANYCELL状态机增加等待系统消息的状态，若收到了
                 接入层上报的系统消息，且当前网路为可用网络，则通知接入层
                 重选类型为RESEL_SUITABLE。
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_AnyCellSearch_WaitLSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_SetAbortFlag_AnyCellSearch(VOS_TRUE);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLSysInfoInd_AnyCellSearch_WaitLSysInfoInd
 功能描述  : MMC处理LMM上报的系统消息
 输入参数  : ulEventType:消息类型
             pstMsg:LMM上报的系统消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年12月02日
   作    者   : w00167002
   修改内容   : DTS2011112804719:anycel成功后没有发SUITABLECELL给接入层
                 修改方案:在ANYCELL状态机增加等待系统消息的状态，若收到了
                 接入层上报的系统消息，且当前网路为可用网络，则通知接入层
                 重选类型为RESEL_SUITABLE。
 2.日    期   : 2012年3月17日
   作    者   : l65478
   修改内容   : DTS2012031907930 用户指定搜网注册失败#11重新开机后没有发起搜网
 3.日    期   : 2012年4月18日
   作    者   : l00130025
   修改内容   : DTS2012040200480,单独维护EPS注册状态,供L模下CEREG/CGREG查询和上报使用
 4.日    期   : 2012年10月12日
   作    者   : t00212959
   修改内容   : DTS2012083107335,向L发送CELL_SELECTION_CTRL_REQ
 5.日    期   : 2012年11月5日
   作    者   : t00212959
   修改内容   : DTS2012110703443,改变向L发送CELL_SELECTION_CTRL_REQ的条件，卡无效，是Forbid GPRS，都不发送
 6.日    期   : 2012年11月10日
   作    者   : s00217060
   修改内容   : DTS2012102902559,SIM卡时，不给接入层发送MMC_LMM_RESEL_SUITABLE
 7.日    期   : 2012年11月29日
   作    者   : w00176964
   修改内容   : DTS2012042804167:通知CBA模块当前接入模式为LTE
 8.日    期   : 2013年1月17日
   作    者   : w00176964
   修改内容   : DTS2013011607305:GU下紧急呼叫导致的任意驻留，通知RRC进入suitable状态后
                后续可能不通知EPLMN，导致RRC无法驻留
 9.日    期   : 2013年3月30日
   作    者   : l00167671
   修改内容   : 主动上报AT命令控制下移至C核
 10.日    期   : 2012年12月20日
   作    者   : w00176964
   修改内容   : DTS2012121906946:收到L的系统消息转发给LMM
 11.日    期   : 2014年1月28日
   作    者   : s00246516
   修改内容   : L-C互操作项目:增加获取和注册请求的处理
 12.日    期   : 2015年02月11日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseII 项目修改
                 方案优化后，LTE下的小区发生变化，LMM会通过系统消息通知MMC
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLSysInfoInd_AnyCellSearch_WaitLSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;

    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;

    NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8                enSpecPlmnSearchState;

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));

    /* 停止等待系统消息的定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_SYS_INFO);

    /* 更新驻留状态 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

    /* 如果当前需要退出状态机 */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_AnyCellSearch())
    {
        /* 发送Abort结果 */
        NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_ABORTED);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /*方案优化后，LTE下的小区发生变化，LMM会通过系统消息通知MMC*/
    /* 保留老的驻留网络信息 */
    pstCurCampInfo  = NAS_MML_GetCurrCampPlmnInfo();
    PS_MEM_CPY(&stOldCampInfo, pstCurCampInfo, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

    /* 根据系统消息，更新MML的全部变量 */
    NAS_MMC_UpdateNetworkInfo_LmmSysInfo(pstMsg);


    enSpecPlmnSearchState = NAS_MMC_GetSpecPlmnSearchState();

    if ((VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
     || (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == enSpecPlmnSearchState))
    {
        /* 主动上报 */
        NAS_MMC_SndMsccSysInfo();
    }

    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_STOP);




    /* Modified by s00246516 for L-C互操作项目, 2014-01-28, Begin */
    NAS_MMC_SetAsAnyCampOn(VOS_TRUE);

    /* L下，非NAS_MML_PLMN_FORBID_PLMN，允许漫游 ,卡有效且不是SIM卡，
       则通知LMM重选类型为RESEL_SUITABLE */
    if (VOS_TRUE == NAS_MMC_IsNeedSndLmmSuitableCellSelReq_AnyCellSearch())
    /* Modified by s00246516 for L-C互操作项目, 2014-01-28, End */
    {
        /* Added by s00246516 for L-C互操作项目, 2014-01-28, Begin */
        NAS_MMC_SetAsAnyCampOn(VOS_FALSE);
        /* Added by s00246516 for L-C互操作项目, 2014-01-28, End */

        NAS_MMC_SndLmmCellSelReq(MMC_LMM_RESEL_SUITABLE);

        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildSndLmmEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndLmmEquPlmnReq(&stSndEquPlmnInfo);
        NAS_MMC_SndOmEquPlmn();
    }

    /* CBS上报*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_LTE);

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, end */

    /* 转发GMM系统消息,供rabm使用 */
    NAS_MMC_SndGmmLteSysinfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);

    NAS_MMC_SndMmLteSysinfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);

    NAS_MMC_SndLmmLteSysInfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);

    /* 发送ANYCELL搜网成功结果 */
    NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_SUCC);

    /* 直接退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitLSysInfoExpired_AnyCellSearch_WaitLSysInfoInd
 功能描述  : 等待系统消息定时器超时超时的处理
 输入参数  : ulEventType:消息类型
             pstMsg:TI_NAS_MMC_WAIT_SYS_INFO超时消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年12月02日
   作    者   : w00167002
   修改内容   : DTS2011112804719:anycel成功后没有发SUITABLECELL给接入层
                 修改方案:在ANYCELL状态机增加等待系统消息的状态，若收到了
                 接入层上报的系统消息，且当前网路为可用网络，则通知接入层
                 重选类型为RESEL_SUITABLE。
 2.日    期   : 2014年8月8日
   作    者   : w00242748
   修改内容   : DTS2014080704343:将ANYCELL标记提前设置，在进行ANYCELL搜，收到L的搜网回复时，
                将该标志置上。
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitLSysInfoExpired_AnyCellSearch_WaitLSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitLSysInfoExpired_AnyCellSearch_WaitLSysInfoInd: Timer Expired");

    NAS_MMC_SetAsAnyCampOn(VOS_FALSE);

    /* 如果当前需要退出状态机 */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_AnyCellSearch())
    {
        /* 发送Abort结果 */
        NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_ABORTED);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 发送ANYCELL搜网失败结果 */
    NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_FAIL);

    /* 直接退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;

}




#endif

/*****************************************************************************
 函 数 名  : NAS_MMC_GetCoverageRatPrioList_Anycell
 功能描述  : 从内部搜网结构中，获取当前存在网络的优先接入技术列表;
             所有接入技术不存在时，使用 SYSCFG设定的接入技术，以当前模为最优先
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年8月12日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2014年6月17日
    作    者   : z00234330
    修改内容   : PCINT清理
*****************************************************************************/
VOS_VOID NAS_MMC_GetCoverageRatPrioList_Anycell(
    NAS_MMC_INTER_PLMN_SEARCH_REQ_STRU     *pstInterPlmnSrchReq,
    NAS_MML_PLMN_RAT_PRIO_STRU             *pstRatPrioList
)
{
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstPlmnRatInfo;
    VOS_UINT32                                              i;
    VOS_UINT32                                              ulIdx;

    ulIdx          =  0;
    pstPlmnRatInfo = pstInterPlmnSrchReq->astInterPlmnSearchInfo;

    /* 从内部搜网结构中，获取当前存在网络的优先接入技术列表 */
    for ( i = 0 ; i < NAS_MML_MAX_RAT_NUM; i++ )

    {   /* Modified by z00234330 for PCLINT清理, 2014-06-16, begin */
        if (NAS_MML_NET_RAT_TYPE_BUTT != pstPlmnRatInfo[i].enRatType)
        {
            pstRatPrioList->aucRatPrio[ulIdx] = pstPlmnRatInfo[i].enRatType;
            ulIdx++;
        }
        /* Modified by z00234330 for PCLINT清理, 2014-06-16, end */
    }

    /* 所有接入技术不存在时，使用 SYSCFG设定的接入技术 */
    if (0 == ulIdx)
    {
        PS_MEM_CPY(pstRatPrioList,
                   NAS_MML_GetMsPrioRatList(), sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));
    }

    else
    {
        pstRatPrioList->ucRatNum = (VOS_UINT8)ulIdx;
    }


    /* 当前接入技术支持时，以当前接入技术最优先 */
    NAS_MML_SortSpecRatPrioHighest(NAS_MML_GetCurrNetRatType(), pstRatPrioList);

}
/*****************************************************************************
 函 数 名  : NAS_MMC_SndAnyCellPlmnSearchReq_AnyCellSearch
 功能描述  : 向接入层或者LMM发送anycell请求消息
 输入参数  : enRat
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1. 日    期  : 2011年7月23日
    作    者  : s46746
    修改内容  : 新生成函数
 2.日    期   : 2012年3月17日
   作    者   : w00176964
   修改内容   : DTS2012031900095 V7R1 C30 SBM&EM定制需求:增加LTE国家漫游功能定制
 3.日    期   : 2013年1月15日
   作    者   : s00217060
   修改内容   : for DSDA GUNAS C CORE:等待WAS的搜网回复定时器长度封装成函数
 4.日    期   : 2013年01月23日
   作    者   : s00217060
   修改内容   : 问题单: DTS2013012106172,Enable Lte时停止定时器TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER
 5.日    期   : 2013年11月01日
   作    者   : l00208543
   修改内容   : 根据卡类型禁止网络制式
 6.日    期   : 2014年1月28日
   作    者   : s00246516
   修改内容   : L-C互操作项目:增加获取和注册请求的处理
 7.日    期   : 2015年02月11日
   作    者   : w00167002
   修改内容   : DTS2015021000324:当前在DSDS双卡中，GSM下搜网可能不回NAS 搜网NO RF,那么
                NAS搜网定时器超时，则上报无服务了.
 8.日    期   : 2015年1月5日
   作    者   : z00161729
   修改内容   : AT&T 支持DAM特性修改
*****************************************************************************/
VOS_VOID NAS_MMC_SndAnyCellPlmnSearchReq_AnyCellSearch(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    VOS_UINT32                                              ulWaitWasPlmnSrchCnfTimerLen;
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;

    /* 获取LTE能力状态 */
    enLCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();
#endif

    ulWaitWasPlmnSrchCnfTimerLen = NAS_MMC_GetWaitWasPlmnSrchCnfTimerLen();

    /* 更新当前为非驻留状态 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

    /* Added by s00246516 for L-C互操作项目, 2014-01-28, Begin */
    NAS_MMC_SetAsAnyCampOn(VOS_FALSE);
    /* Added by s00246516 for L-C互操作项目, 2014-01-28, End */

#if (FEATURE_ON == FEATURE_LTE)
    /* 如果当前已经通知LTE disable,此时存在LTE的国内网络需要enable LTE */
    if ((VOS_TRUE == NAS_MML_GetDisableLteRoamFlg())
     && (NAS_MML_NET_RAT_TYPE_LTE == enRat))
    {
        /* 当前LTE能力恢复可用或者为默认值 */
        if ((NAS_MML_LTE_CAPABILITY_STATUS_BUTT == enLCapabilityStatus)
         || (NAS_MML_LTE_CAPABILITY_STATUS_REENABLE_NOTIFIED_AS == enLCapabilityStatus))
        {
            if (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE != NAS_MML_GetLteForbiddenStatusFlg())
            {
                NAS_MMC_SndEnableLteNotify();
                NAS_MMC_ClearDisabledLtePlmnId();
                NAS_MMC_SetEnableLteTimerExpireFlag(VOS_FALSE);
            }
        }

        if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER))
        {
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER);
        }

        /* 更新disable LTE能力标记 */
        NAS_MML_SetDisableLteRoamFlg(VOS_FALSE);
    }
#endif

    /* 根据不同的接入技术发送AnyCell搜网请求 */
    switch (enRat)
    {
#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:
            NAS_MMC_SndLmmPlmnAnyCellSrchReq();
            NAS_MMC_FSM_SetCurrState(NAS_MMC_ANYCELL_SEARCH_STA_WAIT_LMM_PLMN_SEARCH_CNF);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF, TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF_LEN);
            break;
#endif
        case NAS_MML_NET_RAT_TYPE_WCDMA:
            NAS_MMC_SndAsPlmnAnyCellSrchReq(WUEPS_PID_WRR);
            NAS_MMC_FSM_SetCurrState(NAS_MMC_ANYCELL_SEARCH_STA_WAIT_WAS_PLMN_SEARCH_CNF);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF, ulWaitWasPlmnSrchCnfTimerLen);
            break;

        case NAS_MML_NET_RAT_TYPE_GSM:
            NAS_MMC_SndAsPlmnAnyCellSrchReq(UEPS_PID_GAS);
            NAS_MMC_FSM_SetCurrState(NAS_MMC_ANYCELL_SEARCH_STA_WAIT_GAS_PLMN_SEARCH_CNF);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_PLMN_SEARCH_CNF, NAS_MMC_GetWaitGasPlmnSearchCnfTimerLen(VOS_FALSE));
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndAnyCellPlmnSearchReq_AnyCellSearch: Rat not support.");
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndSuspendReq_AnyCellSearch
 功能描述  : 向接入层或者LMM发送anycell挂起消息
 输入参数  : enRat
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月23日
    作    者  : s46746
    修改内容  : 新生成函数
  2.日    期   : 2014年1月28日
    作    者   : s00246516
    修改内容   : L-C互操作项目:增加获取和注册请求的处理
*****************************************************************************/
VOS_VOID NAS_MMC_SndSuspendReq_AnyCellSearch(
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
        case NAS_MML_NET_RAT_TYPE_WCDMA:
            NAS_MMC_SndAsSuspendReq(WUEPS_PID_WRR);
            NAS_MMC_FSM_SetCurrState(NAS_MMC_ANYCELL_SEARCH_STA_WAIT_WAS_SUSPEND_CNF);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF, TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF_LEN);
            break;

#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:
            NAS_MMC_SndLmmSuspendReq();
            NAS_MMC_FSM_SetCurrState(NAS_MMC_ANYCELL_SEARCH_STA_WAIT_LMM_SUSPEND_CNF);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_SUSPEND_CNF, TI_NAS_MMC_WAIT_LMM_SUSPEND_CNF_LEN);
            break;
#endif

        case NAS_MML_NET_RAT_TYPE_GSM:
            NAS_MMC_SndAsSuspendReq(UEPS_PID_GAS);
            NAS_MMC_FSM_SetCurrState(NAS_MMC_ANYCELL_SEARCH_STA_WAIT_GAS_SUSPEND_CNF);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF, TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF_LEN);
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndSuspendReq_AnyCellSearch: Rat not support.");
            break;
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_AnyCellSearch
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

VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_AnyCellSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
     /* 记录需要退出当前状态机标志 */
    NAS_MMC_SetAbortFlag_AnyCellSearch(VOS_TRUE);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedSndAsSuitableCellSelReq_AnyCellSearch
 功能描述  : 是否需要通知接入层suiteable cell驻留
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:需要通知RRC
             VOS_FALSE:不需要通知
 调用函数  :
 被调函数  :

 1.日    期   : 2012年12月6日
   作    者   : w00176964
   修改内容   : DTS201212905979
 2.日    期   : 2014年2月19日
   作    者   : z00161729
   修改内容   : DTS2014021000537:sim卡anycell驻留l的小区mmc收到系统消息转给mma时应该将禁止网络标识置为TRUE，
                 不上报pstransfer:1,否则导致ps迁移到modem0后l不注册，乒乓ps迁移
*****************************************************************************/

VOS_UINT32 NAS_MMC_IsNeedSndAsSuitableCellSelReq_AnyCellSearch(VOS_VOID)
{
    VOS_UINT32                                              ulIsPlmnForbidGPRSFlg;
    VOS_UINT32                                              ulPlmnLaType;
    NAS_MML_MS_MODE_ENUM_UINT8                              enMsMode;

    ulIsPlmnForbidGPRSFlg   = VOS_FALSE;
    ulPlmnLaType            = NAS_MMC_GetCurrentLaiForbbidenType();
    enMsMode                = NAS_MML_GetMsMode();

    /* 对于14的情况,只有PS ONLY或者CS+PS时CS卡无效的情况才认为禁止网络,否则不为禁止网络 */
    if ((NAS_MML_MS_MODE_PS_ONLY           == enMsMode)
     && (NAS_MML_PLMN_FORBID_PLMN_FOR_GPRS == ulPlmnLaType))
    {
        ulIsPlmnForbidGPRSFlg = VOS_TRUE;
    }

    /* A模式时CS域卡无效时 */
    if ((VOS_FALSE                         == NAS_MML_GetSimCsRegStatus())
     && (NAS_MML_MS_MODE_PS_CS             == enMsMode)
     && (NAS_MML_PLMN_FORBID_PLMN_FOR_GPRS == ulPlmnLaType))
    {
        ulIsPlmnForbidGPRSFlg = VOS_TRUE;
    }

    if (NAS_MML_PLMN_FORBID_ROAM_LA == (ulPlmnLaType & NAS_MML_PLMN_FORBID_ROAM_LA))
    {
        return VOS_FALSE;
    }

    /* W下，非NAS_MML_PLMN_FORBID_PLMN，不存在RRC链接，且卡存在
       对于NAS_MML_PLMN_FORBID_PLMN_FOR_GPRS,只有在CS+PS的情况且CS卡有效的情况
       则通知接入层重选类型为RESEL_SUITABLE */
    if ((VOS_TRUE                 == NAS_MML_IsUsimStausValid())
     && (NAS_MML_PLMN_FORBID_PLMN != ulPlmnLaType)
     && (VOS_FALSE                == ulIsPlmnForbidGPRSFlg))
    {

        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/* Added by s00246516 for L-C互操作项目, 2014-02-14, Begin */
#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedSndLmmSuitableCellSelReq_AnyCellSearch
 功能描述  : 是否需要通知LTE接入层suiteable cell驻留
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:需要通知LMM
             VOS_FALSE:不需要通知
 调用函数  :
 被调函数  :

 1.日    期   : 2014年2月14日
   作    者   : s00246516
   修改内容   : L-C互操作项目:增加获取和注册请求的处理
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedSndLmmSuitableCellSelReq_AnyCellSearch(VOS_VOID)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU                       *pstForbidPlmnInfo = VOS_NULL_PTR;
    NAS_MML_SIM_STATUS_STRU                                *pstSimStatus    = VOS_NULL_PTR;
    VOS_UINT32                                              ulUsimStausFlg;
    VOS_UINT32                                              ulForbidRoamingFlg;
    VOS_UINT32                                              ulIsPlmnForbidGPRSFlg;
    NAS_MML_SIM_TYPE_ENUM_UINT8                             enSimType;
    NAS_MMC_REG_CONTROL_ENUM_UINT8                          enRegCtrl;

    pstCurCampInfo    = NAS_MML_GetCurrCampPlmnInfo();
    pstForbidPlmnInfo = NAS_MML_GetForbidPlmnInfo();

    ulIsPlmnForbidGPRSFlg = NAS_MML_IsBcchPlmnIdInDestSimPlmnList(&(pstCurCampInfo->stLai.stPlmnId),
                                          pstForbidPlmnInfo->ucForbGprsPlmnNum,
                                          pstForbidPlmnInfo->astForbGprsPlmnList);

    /* 禁止LTE漫游 */
    ulForbidRoamingFlg = NAS_MMC_IsNeedDisableLteRoam(pstCurCampInfo->stLai.stPlmnId.ulMcc);

    pstSimStatus = NAS_MML_GetSimStatus();

    ulUsimStausFlg = VOS_TRUE;

    /* 卡不在位，PS无效就认为卡无效 */
    if ( ( VOS_FALSE == NAS_MML_GetSimPresentStatus() )
      || ( VOS_FALSE == pstSimStatus->ucSimPsRegStatus))
    {
        ulUsimStausFlg = VOS_FALSE;
    }

    enSimType = NAS_MML_GetSimType();
    enRegCtrl = NAS_MMC_GetRegCtrl();

    if ( (NAS_MML_PLMN_FORBID_PLMN != NAS_MMC_GetCurrentLaiForbbidenType())
      && (VOS_TRUE  == ulUsimStausFlg)
      && (VOS_FALSE == ulIsPlmnForbidGPRSFlg)
      && (VOS_FALSE == ulForbidRoamingFlg)
      && (NAS_MML_SIM_TYPE_SIM != enSimType)
      && (NAS_MMC_REG_CONTROL_BY_3GPP_MMC == enRegCtrl))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
#endif
/* Added by s00246516 for L-C互操作项目, 2014-02-14, End */


/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedRejectAnycellSerach_AnyCellSearch
 功能描述  : 判断是否需要拒绝当前的ANYCELL搜网
 输入参数  : enRat
 输出参数  : 无
 返 回 值  : VOS_TRUE;
             VOS_FALSE;
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年11月1日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedRejectAnycellSerach_AnyCellSearch(VOS_VOID)
{
    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus = VOS_NULL_PTR;
    VOS_UINT32                          ulRrcConnExistFlag;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrRatType;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enAnycellSearchRat;

    pstConnStatus = NAS_MML_GetConnStatus();
    enCurrRatType = NAS_MML_GetCurrNetRatType();
    ulRrcConnExistFlag   = NAS_MML_IsRrcConnExist();

    /* 当前连接不存在，不需要REJ */
    if ( VOS_FALSE == ulRrcConnExistFlag )
    {
        return VOS_FALSE;
    }

    /* 获取下个要搜索的网络接入技术 */
    enAnycellSearchRat = NAS_MMC_GetNextSearchRat_AnyCellSearch();

    if (NAS_MML_NET_RAT_TYPE_LTE == enCurrRatType)
    {
        /* 当前在L下，下一个要搜索的接入技术为GU，即需要挂起L时候，即便有链路，也是可以发起ANYCELL搜网的 */
        if (NAS_MML_NET_RAT_TYPE_LTE != enAnycellSearchRat)
        {
            return VOS_FALSE;
        }

        /* 在L下有链路时候，又准备在L下进行ANYCELL搜网，则直接拒绝当前的ANYCELL搜网 */
        return VOS_TRUE;
    }

    /* 在GU下，如果当前不存在RRC链路，则可以尝试进行ANYCELL搜网,否则拒绝当前的ANYCELL搜网 */
    if (VOS_TRUE == pstConnStatus->ucRrcStatusFlg)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_ProcNoRf_AnyCellSearch
 功能描述  : anycell状态机中有no rf处理
 输入参数  : 接入技术
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年06月27日
   作    者   : b00269685
   修改内容   : DSDS III新增函数
*****************************************************************************/
VOS_VOID NAS_MMC_ProcNoRf_AnyCellSearch(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNasRat
)
{
    /* 设置NO RF 标记 */
    NAS_MML_SetCurrRatRfAvailFlg(enNasRat, VOS_FALSE);

    /* 向MSCC通知当前NO RF信息  */
    NAS_MMC_SndMsccRfAvailInd(VOS_FALSE);

    /* 发送搜网失败结果 */
    NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_FAIL);

    /* 向RRM发起注册 */
    NAS_MMC_RegisterRrmResourceNtf(enNasRat, RRM_PS_TASK_TYPE_NAS_SEARCH);

    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                    VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    /* 退出状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_UpdateRfAvailFlg_AnyCellSearch
 功能描述  : anycell搜网成功失败或打断后更新RF可用标记的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年07月01日
   作    者   : w00176964
   修改内容   : DSDS III新增函数
*****************************************************************************/
VOS_VOID NAS_MMC_UpdateRfAvailFlg_AnyCellSearch(VOS_VOID)
{
    if (VOS_TRUE == NAS_MML_GetRfAvailFlg())
    {
        return;
    }

    /* 如果存在no rf标记，则清除并通知mma */
    NAS_MML_SetCurrRatRfAvailFlg(NAS_MML_NET_RAT_TYPE_BUTT, VOS_TRUE);

    /* 向MSCC通知当前NO RF信息  */
    NAS_MMC_SndMsccRfAvailInd(VOS_TRUE);

    /* 搜网流程被打断上报MSCC之前因为no rf而没有上报的状态 */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_AnyCellSearch())
    {
        NAS_MMC_SndMsccCurrServiceRelatedInfo();
    }

    return;
}


/*lint -restore */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif




