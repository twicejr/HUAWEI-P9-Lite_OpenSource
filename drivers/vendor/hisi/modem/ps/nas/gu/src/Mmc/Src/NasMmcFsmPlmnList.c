/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcFsmPlmnList.c
  版 本 号   : 初稿
  作    者   : W00176964
  生成日期   : 2011年07月02日
  最近修改   :
  功能描述   : plmn list时状态机状态处理
  函数列表   :
  修改历史   :
  1.日    期   : 2011年07月02日
    作    者   : W00176964
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "PsTypeDef.h"
#include "NasMmcCtx.h"
#include "NasMmlLib.h"
#include "Nasrrcinterface.h"
#include "MmcGmmInterface.h"
#include "MmcMmInterface.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#endif
#include "NasMmcProcRegRslt.h"
#include "NasMmcProcNvim.h"
#include "NasMmcComFunc.h"
#include "NasMmcTimerMgmt.h"
#include "NasMmlMsgProc.h"
#include "NasMmcSndLmm.h"
#include "NasMmcSndGuAs.h"
#include "NasMmcFsmPlmnList.h"
#include "NasMmcFsmPLmnListTbl.h"
#include "NasMmcSndMscc.h"
#include "NasMmcSndGmm.h"
#include "NasMmcSndMm.h"
#include "NasMmcSndOm.h"
#include "NasMmcSndInternalMsg.h"
#include "NasMmcPlmnSelectionStrategy.h"
#include "NasMmcProcSuspend.h"
#include "NasMmlMsgProc.h"
#include "NasUtranCtrlInterface.h"

/* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
#include "MsccMmcInterface.h"
/* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */
#include "NasMmcSndCss.h"

#include "NasUsimmApi.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_FSM_PLMN_LIST_C
/*****************************************************************************
  2 全局变量
*****************************************************************************/

/*****************************************************************************
  3 宏定义
*****************************************************************************/


/*lint -save -e958 */

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTafPlmnListReq_PlmnList_Init
 功能描述  : 在list搜网的INIT状态,收到TAF的LIST搜网消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:ID_MSCC_MMC_PLMN_LIST_REQ消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2011年09月21日
    作    者   : W00166186
    修改内容   : V7R1 PHASE II开发
  3.日    期   : 2012年5月9日
    作    者   : t00212959
    修改内容   : GUL BG项目调整
  4.日    期   : 2014年1月22日
    作    者   : w00167002
    修改内容   : SVLTE共天线:发起列表搜，则清除NO RF标记，则清除NO RF标记信息。
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTafPlmnListReq_PlmnList_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapStatus;

    /* 获取LTE能力状态 */
    enLteCapStatus = NAS_MML_GetLteCapabilityStatus();
#endif

    /* 保存当前消息为状态机入口消息 */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);


    NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_USER_LIST_SRCH);



#if (FEATURE_ON == FEATURE_LTE)
    /* 设置disable L的标记 */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS == enLteCapStatus)
     || (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == enLteCapStatus))
    {
        NAS_MMC_SetPreLteDisableFlg_PlmnList(VOS_TRUE);
    }
    else
    {
        NAS_MMC_SetPreLteDisableFlg_PlmnList(VOS_FALSE);
    }
#endif

    /* 判断是否需要anycell搜网,需要则设置anycell 搜网标记 */
    if (VOS_TRUE == NAS_MMC_IsNeedAnyCellSrch_PlmnList())
    {
        NAS_MMC_SetAnyCellSrchFlg_PlmnList(VOS_TRUE);
    }

    /* 处理用户LIST搜网请求 */
    NAS_MMC_ProcUserPlmnListReq_PlmnList();

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvInterPlmnListReq_PlmnList_Init
 功能描述  : 在list搜网的INIT状态,收到MMC的内部LIST搜网消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:MMCMMC_INTER_PLMN_LIST_REQ消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月6日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2011年09月24日
    作    者   : W00166186
    修改内容   : V7R1 PHASE II
  3.日    期   : 2012年5月9日
    作    者   : t00212959
    修改内容   : GUL BG项目调整
  4.日    期   : 2012年9月11日
    作    者   : w00176964
    修改内容   : V7R1_GUTL项目调整:TD主模下驻留态下需要通知MM/GMM进入搜网状态
  5.日    期   : 2014年1月22日
    作    者   : w00167002
    修改内容   : SVLTE共天线:发起列表搜，则清除NO RF标记，则清除NO RF标记信息。
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvInterPlmnListReq_PlmnList_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapStatus;

    enLteCapStatus      = NAS_MML_GetLteCapabilityStatus();
#endif

    /* 保存当前消息为状态机入口消息 */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);




#if (FEATURE_ON == FEATURE_LTE)
    /* 设置disable L标记 */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS == enLteCapStatus)
     || (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == enLteCapStatus))
    {
        NAS_MMC_SetPreLteDisableFlg_PlmnList(VOS_TRUE);
    }
    else
    {
        NAS_MMC_SetPreLteDisableFlg_PlmnList(VOS_FALSE);
    }
#endif

    /* 驻留态在GTL模式TD为主模时需要通知MM/GMM进入搜网状态 */
    if (VOS_TRUE == NAS_MMC_IsCurrentTdscdmaMode())
    {
        /* 向GMM发送搜网指示 */
        NAS_MMC_SndGmmPlmnSchInit();

        /* 向MM发送搜网指示 */
        NAS_MMC_SndMmPlmnSchInit();
    }

    /* 根据不同接入模式,发送LIST搜网请求，迁到等待搜网结果状态并启动保护定时器*/
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_GetCurrNetRatType());

    return VOS_TRUE;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiPeriodTryingUserPlmnListExpired_PlmnList_Init
 功能描述  : 在list搜网的INIT状态,收到TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST超时消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月6日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2011年09月21日
    作    者   : W00166186
    修改内容   : V7R1 PHASE II
  3.日    期   : 2012年5月9日
    作    者   : t00212959
    修改内容   : GUL BG项目调整
  4.日    期   : 2014年1月22日
    作    者   : w00167002
    修改内容   : SVLTE共天线:发起列表搜，则清除NO RF标记，则清除NO RF标记信息。
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiPeriodTryingUserPlmnListExpired_PlmnList_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapStatus;

    enLteCapStatus = NAS_MML_GetLteCapabilityStatus();
#endif

    /* 保存当前消息为状态机入口消息 */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);




#if (FEATURE_ON == FEATURE_LTE)
    /* 设置disable L标记 */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS == enLteCapStatus)
     || (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == enLteCapStatus))
    {
        NAS_MMC_SetPreLteDisableFlg_PlmnList(VOS_TRUE);
    }
    else
    {
        NAS_MMC_SetPreLteDisableFlg_PlmnList(VOS_FALSE);
    }
#endif

    /* 判断是否需要anycell搜网,需要则设置anycell 搜网标记 */
    if (VOS_TRUE == NAS_MMC_IsNeedAnyCellSrch_PlmnList())
    {
        NAS_MMC_SetAnyCellSrchFlg_PlmnList(VOS_TRUE);
    }

    /* 处理用户LIST搜网请求 */
    NAS_MMC_ProcUserPlmnListReq_PlmnList();

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiPeriodTryingInterPlmnListExpired_PlmnList_Init
 功能描述  : 在list搜网的INIT状态,收到TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST超时消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月6日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2011年09月21日
    作    者   : W00166186
    修改内容   : V7R1 PHASE II
  3.日    期   : 2012年5月9日
    作    者   : t00212959
    修改内容   : GUL BG项目调整
  4.日    期   : 2012年9月11日
    作    者   : w00176964
    修改内容   : V7R1_GUTL项目调整:TD主模下驻留态下需要通知MM/GMM进入搜网状态
  5.日    期   : 2014年1月22日
    作    者   : w00167002
    修改内容   : SVLTE共天线:发起列表搜，则清除NO RF标记，则清除NO RF标记信息。
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiPeriodTryingInterPlmnListExpired_PlmnList_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapStatus;

    enLteCapStatus = NAS_MML_GetLteCapabilityStatus();
#endif

    /* 保存当前消息为状态机入口消息 */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);




#if (FEATURE_ON == FEATURE_LTE)

    /* 设置disable L标记 */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS == enLteCapStatus)
     || (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == enLteCapStatus))
    {
        NAS_MMC_SetPreLteDisableFlg_PlmnList(VOS_TRUE);
    }
    else
    {
        NAS_MMC_SetPreLteDisableFlg_PlmnList(VOS_FALSE);
    }
#endif

    /* 驻留态在GTL模式TD为主模时需要通知MM/GMM进入搜网状态 */
    if (VOS_TRUE == NAS_MMC_IsCurrentTdscdmaMode())
    {
        /* 向GMM发送搜网指示 */
        NAS_MMC_SndGmmPlmnSchInit();

        /* 向MM发送搜网指示 */
        NAS_MMC_SndMmPlmnSchInit();
    }

    /* 根据不同接入模式,发送LIST搜网请求，迁到等待搜网结果状态并启动保护定时器*/
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_GetCurrNetRatType());

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTafPlmnListReq_PlmnList_NonInit
 功能描述  : 在list搜网的各个状态,收到ID_MSCC_MMC_PLMN_LIST_REQ消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:ID_MSCC_MMC_PLMN_LIST_REQ消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTafPlmnListReq_PlmnList_NonInit(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 用当前消息更新当前状态机入口消息 */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndRslt_PlmnList
 功能描述  : 发送PLMN LIST状态机完成结果消息
 输入参数  : enRslt:状态机退出结果
             ulNeedPlmnSearch:是否需要搜网
             pstListInfo:搜索到的网络列表信息
             pstRegRsltInfo:注册结果信息
 输出参数  : 无
 返 回 值  : VOS_OK: 函数处理消息成功
             VOS_ERR: 函数申请消息失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月5日
    作    者   : t00212959
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SndRslt_PlmnList(
    NAS_MMC_PLMN_LIST_RESULT_ENUM_UINT32                    enRslt,
    VOS_UINT8                                               ucNeedPlmnSearch,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstListInfo,
    NAS_MMC_PLMN_LIST_REG_RSLT_INFO_STRU                   *pstRegRsltInfo
)
{

    NAS_MMC_PLMN_LIST_SEARCH_SCENE_ENUM_UINT8               enPlmnListSearchScene;
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapStatus;

    enLteCapStatus        = NAS_MML_GetLteCapabilityStatus();
#endif

    enPlmnListSearchScene = NAS_MMC_PLMN_LIST_SEARCH_SCENE_BUTT;

    /* 如果需要搜网，则需要构造搜网场景，目前只有USERLIST和disable lte两种搜网场景 */
    if (VOS_TRUE == ucNeedPlmnSearch)
    {
        /* List搜之前Lte 没有disable，在List搜状态机里发生disable lte，搜网场景需为disable lte */
#if (FEATURE_ON == FEATURE_LTE)
        if ((VOS_FALSE == NAS_MMC_GetPreLteDisableFlg_PlmnList())
         && ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS == enLteCapStatus)
          || (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == enLteCapStatus)))
        {
            enPlmnListSearchScene = NAS_MMC_PLMN_LIST_SEARCH_SCENE_DISABLE_LTE;
        }
        else
#endif
        {
            enPlmnListSearchScene = NAS_MMC_PLMN_LIST_SEARCH_SCENE_USER_LIST;
        }
    }

    NAS_MMC_SndPlmnListRslt(enRslt,ucNeedPlmnSearch,enPlmnListSearchScene,
                                pstListInfo,pstRegRsltInfo);
    return;
}
/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitRrcConnRelInd
 功能描述  : 在list搜网的等待RRC链路释放状态,收到MMCMMC_ABORT_FSM_REQ消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:MMCMMC_ABORT_FSM_REQ消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月30日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2015年9月26日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);

    NAS_MMC_SndMsccListSearchCnfMsg_PlmnList();

    /* 未开始搜网，此时搜索列表为空,记录当前注册导致的后续addition值，L1 MAIN上
       收到链路释放后根据addition值决定是否触发搜网 */
    NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                            VOS_FALSE,
                            NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                            NAS_MMC_GetRegRsltInfo_PlmnList());

    /*退出状态机*/
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTafPlmnListAbortReq_PlmnList_WaitRrcConnRelInd
 功能描述  : 在list搜网的等待RRC链路释放状态,收到ID_MSCC_MMC_PLMN_LIST_ABORT_REQ消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:ID_MSCC_MMC_PLMN_LIST_ABORT_REQ消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTafPlmnListAbortReq_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);

    /* 发送ID_MMC_MSCC_PLMN_LIST_ABORT_CNF */
    NAS_MMC_SndMsccPlmnListAbortCnf_PlmnList();

    /* 未开始搜网，用户的LIST搜网定时器超时，此时搜索列表为空
       记录当前注册导致的后续addition值，L1 MAIN上收到链路释放后
       根据addition值决定是否触发搜网 */
    NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                            VOS_FALSE,
                            NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                            NAS_MMC_GetRegRsltInfo_PlmnList());

    /* 退出状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGmmSignalingStatusInd_PlmnList_WaitRrcConnRelInd
 功能描述  : 在list搜网的等待RRC链路释放状态,收到MMCGMM_SIGNALING_STATUS_IND消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:MMCGMM_SIGNALING_STATUS_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvGmmSignalingStatusInd_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 处理GMM上报的信令链接指示 */
    NAS_MMC_ProcRrcConnRelInd_PlmnList();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmRrConnInfoInd_PlmnList_WaitRrcConnRelInd
 功能描述  : 在list搜网的等待RRC链路释放状态,收到MMCMM_RR_CONN_INFO_IND消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:MMCMM_RR_CONN_INFO_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmRrConnInfoInd_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 处理MM上报的RR链接释放指示 */
    NAS_MMC_ProcRrcConnRelInd_PlmnList();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmRrRelInd_PlmnList_WaitRrcConnRelInd
 功能描述  : 在list搜网的等待RRC链路释放状态,收到MMCMM_RR_REL_IND消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:MMCMM_RR_REL_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmRrRelInd_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 处理MM上报的MM链接释放指示 */
    NAS_MMC_ProcRrcConnRelInd_PlmnList();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmRelInd_PlmnList_WaitRrcConnRelInd
 功能描述  : 在list搜网的等待RRC链路释放状态,收到RRMM_REL_IND消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:RRMM_REL_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmRelInd_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 处理RRC链路释放请求 */
    NAS_MMC_ProcRrcConnRelInd_PlmnList();

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGmmTbfRelInd_PlmnList_WaitRrcConnRelInd
 功能描述  : 在list搜网的等待RRC链路释放状态,收到MMCGMM_TBF_REL_IND消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:MMCGMM_TBF_REL_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2011年09月21日
    作    者   : W00166186
    修改内容   : V7R1 PHASE II
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvGmmTbfRelInd_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 判断RRC链接是否存在 */
    if ( VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        /* 返回继续等待 */
        return VOS_TRUE;
    }

    /* 停止等待RRC链路释放定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);

    /* 向GAS发起LIST搜网请求,迁移状态,启动保护定时器 */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_NET_RAT_TYPE_GSM);

    /* 非驻留态通知MM/GMM搜网开始 */
    if (NAS_MMC_AS_CELL_NOT_CAMP_ON == NAS_MMC_GetAsCellCampOn())
    {
        /* 向GMM发送搜网指示 */
        NAS_MMC_SndGmmPlmnSchInit();

        /* 向MM发送搜网指示 */
        NAS_MMC_SndMmPlmnSchInit();

        /* 设置进入搜网状态 */
        NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGmmNetworkDetachInd_PlmnList_WaitRrcConnRelInd
 功能描述  : 在list搜网的等待RRC链路释放状态,收到MMCGMM_NETWORK_DETACH_IND消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:MMCGMM_NETWORK_DETACH_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2011年12月5日
    作    者   : z00161729
    修改内容   : V7R1 Phase IV调整,当前SYSCFG中L不在时，也需要向LMM通知ID_MMC_LMM_ACTION_RESULT_REQ
  3.日    期   : 2012年2月13日
    作    者   : w00167002
    修改内容   : DTS2011122704039:additional action值若为无效值NAS_MMC_ADDITIONAL_ACTION_BUTT
                  则不更新当前的additional action
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvGmmNetworkDetachInd_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMCGMM_NETWORK_DETACH_IND_STRU                         *pstDetachMsg = VOS_NULL_PTR;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;

    pstDetachMsg        = (MMCGMM_NETWORK_DETACH_IND_STRU *)pstMsg;

    /* 处理Detach结果 */
    enAdditionalAction = NAS_MMC_ProcGmmNetworkDetachInd(pstDetachMsg);

    /* AdditionalAction有效，更新PS的下一步的动作类型 */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enAdditionalAction )
    {
        NAS_MMC_SetPsRegAdditionalAction_PlmnList(enAdditionalAction);
    }

#if   (FEATURE_ON == FEATURE_LTE)
        /* 给LMM发送detach结果消息 */
    NAS_MMC_SndLmmMtDetachIndActionResultReq(pstDetachMsg->ulDetachType,
                                             (NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16)pstDetachMsg->ulDetachCause);
#endif

    /* 不迁移状态 */
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmCsRegResultInd_PlmnList_WaitRrcConnRelInd
 功能描述  : 在list搜网的等待RRC链路释放状态,收到MMMMC_CS_REG_RESULT_IND消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:MMMMC_CS_REG_RESULT_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月01日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmCsRegResultInd_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMMMC_CS_REG_RESULT_IND_STRU       *pstCsRegRslt = VOS_NULL_PTR;

    pstCsRegRslt = (MMMMC_CS_REG_RESULT_IND_STRU*)pstMsg;

    /* 等待RRC链路释放时如果发生重选，切换以及CCO，可能网络会发生改变，
       状态机退出后收到缓存的注册结果消息，需要判断当前网络是
       否发生改变，发生改变则丢弃当前注册结果 */
    if ( pstCsRegRslt->enNetType != NAS_MML_GetCurrNetRatType())
    {
        return VOS_TRUE;
    }

    /* 处理CS的注册结果 */
    NAS_MMC_ProcCsRegRslt_PlmnList(pstCsRegRslt);

    /* 不迁移状态 */
    return VOS_TRUE;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGmmPsRegResultInd_PlmnList_WaitRrcConnRelInd
 功能描述  : 在list搜网的等待RRC链路释放状态,收到GMMMMC_PS_REG_RESULT_IND消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:GMMMMC_PS_REG_RESULT_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月01日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvGmmPsRegResultInd_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    GMMMMC_PS_REG_RESULT_IND_STRU      *pstPsRegRslt = VOS_NULL_PTR;

    pstPsRegRslt = (GMMMMC_PS_REG_RESULT_IND_STRU*)pstMsg;

    /* 等待RRC链路释放时如果发生重选，切换以及CCO，可能网络会发生改变，
       状态机退出后收到缓存的注册结果消息，需要判断当前网络是
       否发生改变，发生改变则丢弃当前注册结果 */
    if ( pstPsRegRslt->enNetType != NAS_MML_GetCurrNetRatType())
    {
        return VOS_TRUE;
    }

    /* 处理PS的注册结果*/
    NAS_MMC_ProcPsRegRslt_PlmnList(pstPsRegRslt);

    /* 不迁移状态 */
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmAbortInd_PlmnList_WaitRrcConnRelInd
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
VOS_UINT32 NAS_MMC_RcvMmAbortInd_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMMMC_ABORT_IND_STRU               *pstMmAbortInd   = VOS_NULL_PTR;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_GU_ACTION_RSLT_INFO_STRU    stActionRslt;
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
        NAS_MMC_SetCsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL);
    }

#if (FEATURE_ON == FEATURE_LTE)

    /* 给LMM发送ID_MMC_LMM_ACTION_RESULT_REQ */
    /* 构造ActionRslt消息，结果为CN_Rej,类型填为新增NAS_MML_PROC_MM_ABORT类型
       请求和结果域都是CS，原因值为Abort带的原因值 */
    stActionRslt.enProcType     = NAS_MML_PROC_MM_ABORT;
    stActionRslt.enRegRst       = NAS_MML_REG_RESULT_CN_REJ;
    stActionRslt.enReqDomain    = NAS_MMC_REG_DOMAIN_CS;
    stActionRslt.enRstDomain    = NAS_MMC_REG_DOMAIN_CS;
    stActionRslt.enCnCause      = pstMmAbortInd->enAbortCause;
    stActionRslt.ulAttemptCount = 0x0;

    NAS_MMC_SndLmmRegActionResultReq(&stActionRslt);
#endif

    return VOS_TRUE;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmSysInfoInd_PlmnList_WaitRrcConnRelInd
 功能描述  : 在list搜网的等待RRC链路释放状态,收到RRMM_SYS_INFO_IND消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:RRMM_SYS_INFO_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月01日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmSysInfoInd_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 处理WAS系统消息 */
    NAS_MMC_ProcWasSysInfo_PlmnList(pstMsg);

    /* 不迁移状态 */
    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGrrMmSysInfoInd_PlmnList_WaitRrcConnRelInd
 功能描述  : 在list搜网的等待RRC链路释放状态,收到GRRMM_SYS_INFO_IND消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:GRRMM_SYS_INFO_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月01日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2013年11月01日
    作    者   : l00208543
    修改内容   : 根据卡类型禁止网络制式
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvGrrMmSysInfoInd_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 如果收到GAS的系统消息，且目前Utran被Enable，则重新Disable Utran */
    NAS_MMC_RcvGasSysInfoSetUtranCapabilityStatus();

    /* 处理GAS系统消息 */
    NAS_MMC_ProcGasSysInfo_PlmnList(pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmSuspendInd_PlmnList_WaitRrcConnRelInd
 功能描述  : 在list搜网的等待RRC链路释放状态,收到RRMM_SUSPEND_IND消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:RRMM_SUSPEND_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2011年12月20日
    作    者   : h44270
    修改内容   : 启动异系统状态机时，认为当前无网络，此时APS挂起
  3.日    期   : 2014年04月18日
    作    者   : s00261364
    修改内容   : V3R360_eCall项目

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmSuspendInd_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_IND_ST             *pstSuspendMsg = VOS_NULL_PTR;

    pstSuspendMsg = (RRMM_SUSPEND_IND_ST*)pstMsg;

    /* 根据不同的挂起原因值，启动不同的状态机 */
    switch (pstSuspendMsg->ucSuspendCause)
    {
        case MMC_SUSPEND_CAUSE_CELLRESELECT:
        case MMC_SUSPEND_CAUSE_REDIRECTION:
            NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_INTER_SYS_CELLRESEL);
            NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,
                                     NAS_MML_GetSimPsRegStatus());
            break;

        case MMC_SUSPEND_CAUSE_PLMNSEARCH:
            /* 向WAS发送挂起失败 */
            NAS_MMC_SndAsSuspendRsp(RRC_NAS_SUSPEND_FAILURE, pstSuspendMsg->MsgHeader.ulSenderPid);

            /* 更新服务状态 */
            /* Deleted by s00261364 for V3R360_eCall项目, 2014-4-18, begin */

            /* Deleted by s00261364 for V3R360_eCall项目, 2014-4-18, end */

            /* Added by s00261364 for V3R360_eCall项目, 2014-4-18, begin */
            NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NO_SERVICE);
            /* Added by s00261364 for V3R360_eCall项目, 2014-4-18, end */

            /* 需要主动释放链路 */
            NAS_MMC_SndMmRelReq();

            NAS_MMC_SndGmmRelReq();

            NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

            break;
        case MMC_SUSPEND_CAUSE_HANDOVER:
            NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_INTER_SYS_HO);
            NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,
                                     NAS_MML_GetSimPsRegStatus());
            break;

        case MMC_SUSPEND_CAUSE_CELLCHANGE:
            NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_INTER_SYS_CCO);
            NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,
                                     NAS_MML_GetSimPsRegStatus());
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvRrMmSuspendInd_PlmnList_WaitRrcConnRelInd:Unexpected suspend type!");
            break;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcMmcSuspendRslt_PlmnList_WaitRrcConnRelInd
 功能描述  : 在list搜网的等待RRC链路释放状态,收到MMCMMC_CELLRESELECT_RSLT_CNF消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:MMCMMC_CELLRESELECT_RSLT_CNF消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2011年09月21日
    作    者   : W00166186
    修改内容   : V7R1 PHASE II
  3.日    期   : 2011年12月30日
    作    者   : l65478
    修改内容   : 在迁到L模时,不立刻把CS设置成可选搜网,而是等待PS注册结果时
                 根据具体的原因值再设置
  4.日    期   : 2011年12月20日
    作    者   : h44270
    修改内容   : 退出异系统状态机时，通知APS当前所在网络

  5.日    期   : 2012年4月25日
    作    者   : w00176964
    修改内容   : GUL BG项目调整
  6.日    期   : 2012年9月11日
    作    者   : w00176964
    修改内容   : V7R1_GUTL项目调整:TD主模下驻留态下需要通知MM/GMM进入搜网状态
  7.日    期   : 2013年2月7日
    作    者   : W00176964
    修改内容   : Volte_phase3项目调整:增加IMS不可用时disable L模的逻辑修改
  8.日    期   : 2013年4月9日
    作    者   : y00176023
    修改内容   : DSDS GUNAS II项目:收到NO RF 退状态机,发送失败消息迁移到OOC
  9.日    期   : 2015年9月25日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcMmcSuspendRslt_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMCMMC_SUSPEND_RSLT_STRU       *pstSuspendRslt = VOS_NULL_PTR;

    NAS_MMC_NotifyModeChange(NAS_MML_GetCurrNetRatType(),
                             NAS_MML_GetSimPsRegStatus());

    pstSuspendRslt  = (NAS_MMCMMC_SUSPEND_RSLT_STRU*)pstMsg;

    /* suspend 异系统重选完成 */
    NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMmcMmcSuspendRslt_PlmnList_WaitRrcConnRelInd:SUSPEND COMPLETE!");

    /* 根据状态机退出结果 进行相应的处理 */
    if ( (NAS_MMC_SUSPEND_FAIL == pstSuspendRslt->enRslt)
      && (NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST != pstSuspendRslt->enFailCause))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMmcMmcSuspendRslt_PlmnList_WaitRrcConnRelInd:SUSPEND FAIL!");

        return VOS_TRUE;
    }

    /* 重选后当前接入技术已经改变，需要重选初始化搜网的接入技术优先级 */
 #if (FEATURE_ON == FEATURE_CSG)
    if (VOS_TRUE == NAS_MMC_IsCsgList_PlmnList())
    {
        NAS_MMC_InitCsgListSearchRatInfo_PlmnList();
    }
    else
 #endif
    {
        NAS_MMC_InitSearchRatInfo_PlmnList();
    }

    if (VOS_FALSE == NAS_MML_GetRfAvailFlg())
    {
        /* 停止保护定时器 */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);

        NAS_MMC_SndMsccPlmnListRejMsg_PlmnList();

        /* 由于未进行LIST搜网，搜索到的网络列表为空 */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                VOS_FALSE,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());


        /* 退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

#if (FEATURE_ON == FEATURE_LTE)

    /* 判断当前接入模式 */
    if ( NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        /* 当前存在RRC连接,从GU异系统到LTE后,LTE此时存在信令连接,
           MMC此时需要等待L下的注册结果 */

        /* 停止保护定时器 */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);

        /* 更新CSPS的AdditionalAction */
        NAS_MMC_SetCsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_BUTT);
        NAS_MMC_SetPsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_BUTT);

        NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList();

        NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_PS);

        /* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-8, begin */
#if (FEATURE_ON == FEATURE_IMS)
        NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_IMS);
#endif
        /* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-8, end */

        /* 迁移状态到等待EPS注册结果 */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_EPS_REG_IND);

        /* 启动保护定时器 */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_REG_IND, TI_NAS_MMC_WAIT_EPS_REG_IND_LEN);

        return VOS_TRUE;
    }
#endif

    /*  如果存在信令连接，则继续等待  */
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        return VOS_TRUE;
    }

    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);

    /* 向当前接入技术发送LIST搜网请求,迁移状态，启动保护定时器 */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_GetCurrNetRatType());

    /* 非驻留态通知MM/GMM搜网开始 */
    if (NAS_MMC_AS_CELL_NOT_CAMP_ON == NAS_MMC_GetAsCellCampOn())
    {
        /* 向GMM发送搜网指示 */
        NAS_MMC_SndGmmPlmnSchInit();

        /* 向MM发送搜网指示 */
        NAS_MMC_SndMmPlmnSchInit();

        /* 设置进入搜网状态 */
        NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

        return VOS_TRUE;
    }

    /* 驻留态在GTL模式TD为主模时需要通知MM/GMM进入搜网状态 */
    if (VOS_TRUE == NAS_MMC_IsCurrentTdscdmaMode())
    {
        /* 向GMM发送搜网指示 */
        NAS_MMC_SndGmmPlmnSchInit();

        /* 向MM发送搜网指示 */
        NAS_MMC_SndMmPlmnSchInit();
    }

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitRrcConnRelIndExpired_PlmnList_WaitRrcConnRelInd
 功能描述  : 在list搜网的等待RRC链路释放状态,收到TI_NAS_MMC_WAIT_RRC_CONN_REL_IND消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:TI_NAS_MMC_WAIT_RRC_CONN_REL_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2011年10月25日
    作    者   : w00166186
    修改内容   : V7R1 PHASE II
  3.日    期   : 2012年6月5日
    作    者   : w00176964
    修改内容   : V7R1 C50 GUL BG项目调整:PS业务启动5S定时器保证LIST搜网有机会发起
  4.日    期   : 2015年9月26日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiWaitRrcConnRelIndExpired_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitRrcConnRelIndExpired_PlmnList_WaitRrcConnRelInd Enter!");

    /* 存在业务，回复列表搜失败 */
    if (VOS_TRUE == NAS_MML_GetCsServiceExistFlg())
    {
        NAS_MMC_SndMsccPlmnListRejMsg_PlmnList();
    }
    else
    {
        NAS_MMC_StartPeriodTryingUserListSrchTimer_PlmnList();
    }


    /* 由于未开始搜网，搜索到的网络列表为空，需要周期性尝试，退出状态机后不需要触发搜网 */
    NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                            VOS_FALSE,
                            NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                            NAS_MMC_GetRegRsltInfo_PlmnList());


    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitWasSysInfoInd
 功能描述  : 在list搜网的等待WAS系统消息时,收到MMCMMC_ABORT_FSM_REQ消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:MMCMMC_ABORT_FSM_REQ消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月30日
    作    者   : w00176964
    修改内容   : 新生成函数

  2.日    期   : 2014年8月1日
    作    者   : w00167002
    修改内容   : 在等系统消息时候收到异系统信息，则打断当前状态机进行异系统操作。
  3.日    期   : 2015年9月25日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitWasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ABORT_FSM_STRU                *pstAbortMsg = VOS_NULL_PTR;

    pstAbortMsg = (NAS_MMC_ABORT_FSM_STRU*)pstMsg;

    /* 记录状态机退出标记 */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);


    /* 如果在等系统消息时候,收到SUSPEND IND消息，则打断当前状态机，进行异系统流程 */
    if ( NAS_BuildEventType(WUEPS_PID_WRR, RRMM_SUSPEND_IND) == pstAbortMsg->ulEventType )
    {
        /* 停止等待WAS系统消息的保护定时器 */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO);

        /* 启动5S周期性尝试定时器 */
        if ( VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
        {
             /* CS业务比如电话或短信引起的接入层list rej需要终止list搜，
                响应业务否则AT口被list请求占用，用户无法发起接听电话或收短信 */
            if (VOS_TRUE == NAS_MML_GetCsServiceExistFlg())
            {
                /* 发送LIST REJ给MSCC */
                NAS_Mmc_SndMsccPlmnListRej();
            }
            else
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST, TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST_LEN);
            }
        }
#if (FEATURE_ON == FEATURE_CSG)
        else if (VOS_TRUE == NAS_MMC_IsCsgList_PlmnList())
        {
            /* CS业务比如电话或短信引起的接入层list rej需要终止list搜，
                响应业务否则AT口被list请求占用，用户无法发起接听电话或收短信 */
            if (VOS_TRUE == NAS_MML_GetCsServiceExistFlg())
            {
                /* 发送LIST REJ给MSCC */
                NAS_MMC_SndMsccCsgListSearchRej();
            }
            else
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH, TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH_LEN);
            }
        }
#endif
        else
        {
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST, TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST_LEN);
        }

        /* 发送状态机失败的退出结果 */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                VOS_FALSE,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTafPlmnListAbortReq_PlmnList_WaitWasSysInfoInd
 功能描述  : 在list搜网的等待WAS系统消息时,收到ID_MSCC_MMC_PLMN_LIST_ABORT_REQ消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:ID_MSCC_MMC_PLMN_LIST_ABORT_REQ消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月02日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTafPlmnListAbortReq_PlmnList_WaitWasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 记录状态机退出标记 */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* 记录通知MSCC结果标记 */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitGasSysInfoInd
 功能描述  : 在list搜网的等待WAS系统消息时,收到MMCMMC_ABORT_FSM_REQ消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:MMCMMC_ABORT_FSM_REQ消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月02日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2014年8月1日
    作    者   : w00167002
    修改内容   : 在等系统消息时候收到异系统信息，则打断当前状态机进行异系统操作。
  3.日    期   : 2015年9月25日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitGasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ABORT_FSM_STRU                *pstAbortMsg = VOS_NULL_PTR;

    pstAbortMsg = (NAS_MMC_ABORT_FSM_STRU*)pstMsg;

    /* 记录状态机退出标记 */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);


    /* 如果在等系统消息时候,收到SUSPEND IND消息，则打断当前状态机，进行异系统流程 */
    if ( NAS_BuildEventType(UEPS_PID_GAS, RRMM_SUSPEND_IND) == pstAbortMsg->ulEventType )
    {
        /* 停止等待WAS系统消息的保护定时器 */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_SYS_INFO);

        /* 启动5S周期性尝试定时器 */
        if ( VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
        {
             /* CS业务比如电话或短信引起的接入层list rej需要终止list搜，
                响应业务否则AT口被list请求占用，用户无法发起接听电话或收短信 */
            if (VOS_TRUE == NAS_MML_GetCsServiceExistFlg())
            {
                /* 发送LIST REJ给MSCC */
                NAS_Mmc_SndMsccPlmnListRej();
            }
            else
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST, TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST_LEN);
            }
        }
#if (FEATURE_ON == FEATURE_CSG)
        else if (VOS_TRUE == NAS_MMC_IsCsgList_PlmnList())
        {
            /* CS业务比如电话或短信引起的接入层list rej需要终止list搜，
                响应业务否则AT口被list请求占用，用户无法发起接听电话或收短信 */
            if (VOS_TRUE == NAS_MML_GetCsServiceExistFlg())
            {
                /* 发送LIST REJ给MSCC */
                NAS_MMC_SndMsccCsgListSearchRej();
            }
            else
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH, TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH_LEN);
            }
        }
#endif
        else
        {
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST, TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST_LEN);
        }

        /* 发送状态机失败的退出结果 */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                VOS_FALSE,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTafPlmnListAbortReq_PlmnList_WaitGasSysInfoInd
 功能描述  : 在list搜网的等待WAS系统消息时,收到ID_MSCC_MMC_PLMN_LIST_ABORT_REQ消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:ID_MSCC_MMC_PLMN_LIST_ABORT_REQ消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月02日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTafPlmnListAbortReq_PlmnList_WaitGasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 记录状态机退出标记 */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* 记录通知MSCC结果标记 */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmSysInfoInd_PlmnList_WaitWasSysInfoInd
 功能描述  : 在list搜网的等待WAS sys info,收到RRMM_SYS_INFO_IND消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:RRMM_SYS_INFO_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2015年9月26日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmSysInfoInd_PlmnList_WaitWasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止等待WAS系统消息的保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO);

    /* 处理WAS系统消息 */
    NAS_MMC_ProcWasSysInfo_PlmnList(pstMsg);

    /* 状态机退出标记为真 */
    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnList())
    {
        NAS_MMC_ProcFsmAbort_PlmnList();

        /* 由于未进行LIST搜网，搜索到的网络列表为空 */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                                VOS_FALSE,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* 退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 更新当前等待CSPS的注册结果 */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList();
    NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_CS);
    NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_PS);

    /* 迁移到等待注册结果状态 */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_CSPS_REG_IND);

    /* 启动保护定时器 */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND, TI_NAS_MMC_WAIT_CSPS_REG_IND_LEN);

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGrrMmSysInfoInd_PlmnList_WaitGasSysInfoInd
 功能描述  : 在list搜网的等待GAS SYS INFO,收到GRRMM_SYS_INFO_IND消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:GRRMM_SYS_INFO_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月02日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2013年11月01日
    作    者   : l00208543
    修改内容   : 根据卡类型禁止网络制式
  3.日    期   : 2015年9月26日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvGrrMmSysInfoInd_PlmnList_WaitGasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 如果收到GAS的系统消息，且目前Utran被Enable，则重新Disable Utran */
    NAS_MMC_RcvGasSysInfoSetUtranCapabilityStatus();

    /* 停止等待GAS系统消息的保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_SYS_INFO);

    /* 处理GAS系统消息 */
    NAS_MMC_ProcGasSysInfo_PlmnList(pstMsg);

    /* 状态机退出标记为真 */
    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnList())
    {
        NAS_MMC_ProcFsmAbort_PlmnList();

        /* 由于未进行LIST搜网，搜索到的网络列表为空 */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                                VOS_FALSE,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* 退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 更新当前等待CSPS的注册结果 */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList();
    NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_CS);
    NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_PS);

    /* 迁移到等待注册结果状态 */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_CSPS_REG_IND);

    /* 启动保护定时器 */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND, TI_NAS_MMC_WAIT_CSPS_REG_IND_LEN);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmAreaLostInd_PlmnList_WaitWasSysInfoInd
 功能描述  : 在list搜网的等待WAS系统消息时,收到RRMM_AREA_LOST_IND消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:RRMM_AREA_LOST_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月01日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2011年09月21日
    作    者   : W00166186
    修改内容   : V7R1 PHASE II LIST开发
  3.日    期   : 2013年4月4日
    作    者   : y00176023
    修改内容   : DSDS GUNAS II项目:收到NO RF 退状态机,发送失败消息，迁移到OOC
  4.日    期   : 2014年5月4日
    作    者   : t00173447
    修改内容   : DTS2014042105390,软银定制需求
  4.日    期   : 2014年04月9日
    作    者   : s00261364
    修改内容   : V3R360_eCall项目:增加服务状态上报处理
  5.日    期   : 2015年9月25日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmAreaLostInd_PlmnList_WaitWasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO);

    /* Modified by c00318887 for 预置频点搜网优化, 2015-9-9, begin */
    NAS_MMC_SaveLastCampedPlmnWithRat(NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMcc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMnc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.enCampPlmnNetRat);
    /* Modified by c00318887 for 预置频点搜网优化, 2015-9-9, end */


    /* 清除驻留PLMN RAI LAC信息*/
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* 当前信号更新 */
    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());

    /* Deleted by s00261364 for V3R360_eCall项目, 2014-4-18, begin */

    /* Deleted by s00261364 for V3R360_eCall项目, 2014-4-18, end */
    /* 上报对应的CS/PS服务状态MSCC_MMC_SERVICE_STATUS_NO_SERVICE */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NO_SERVICE);
    NAS_MMC_UpdateRegStateSpecPlmnSearch();
    /* Added by s00261364 for V3R360_eCall项目, 2014-4-8, end */

    /* 状态机退出标记为真 */
    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnList())
    {
        NAS_MMC_ProcFsmAbort_PlmnList();

        /* 由于未进行LIST搜网，搜索到的网络列表为空 */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                                VOS_FALSE,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* 退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    if (VOS_FALSE == NAS_MML_GetRfAvailFlg())
    {
        NAS_MMC_SndMsccPlmnListRejMsg_PlmnList();

        /* 由于未进行LIST搜网，搜索到的网络列表为空 */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                VOS_FALSE,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* 退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 向WAS发送LIST搜网请求，迁移状态到等待WAS LIST搜网回复状态 ，启动保护定时器 */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);

    /* 向GMM发送搜网指示 */
    NAS_MMC_SndGmmPlmnSchInit();

    /* 向MM发送搜网指示 */
    NAS_MMC_SndMmPlmnSchInit();

    /* 设置进入搜网状态 */
    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmAreaLostInd_PlmnList_WaitGasSysInfoInd
 功能描述  : 在list搜网的等待GAS系统消息时,收到RRMM_AREA_LOST_IND消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:RRMM_AREA_LOST_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月01日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2011年09月21日
    作    者   : W00166186
    修改内容   : V7R1 PHASE II LIST开发
  3.日    期   : 2013年4月9日
    作    者   : y00176023
    修改内容   : DSDS GUNAS II项目:收到NO RF 退状态机，发送失败迁移到ooc
  4.日    期   : 2014年04月9日
    作    者   : s00261364
    修改内容   : V3R360_eCall项目:增加服务状态上报处理
  5.日    期   : 2015年9月26日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmAreaLostInd_PlmnList_WaitGasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_SYS_INFO);

    /* Modified by c00318887 for 预置频点搜网优化, 2015-9-9, begin */
    NAS_MMC_SaveLastCampedPlmnWithRat(NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMcc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMnc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.enCampPlmnNetRat);
    /* Modified by c00318887 for 预置频点搜网优化, 2015-9-9, end */


    /* 清除驻留状态 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* 当前信号更新 */
    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());

    /* Deleted by s00261364 for V3R360_eCall项目, 2014-4-18, begin */

    /* Deleted by s00261364 for V3R360_eCall项目, 2014-4-18, end */
    /* Added by s00261364 for V3R360_eCall项目, 2014-4-8, begin */
    /* 上报对应的CS/PS服务状态MSCC_MMC_SERVICE_STATUS_NO_SERVICE */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NO_SERVICE);
    NAS_MMC_UpdateRegStateSpecPlmnSearch();
    /* Added by s00261364 for V3R360_eCall项目, 2014-4-8, end */

    if (VOS_FALSE == NAS_MML_GetRfAvailFlg())
    {
        NAS_MMC_SndMsccPlmnListRejMsg_PlmnList();

        /* 由于未进行LIST搜网，搜索到的网络列表为空 */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                VOS_FALSE,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());


        /* 退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 状态机退出标记为真 */
    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnList())
    {
        NAS_MMC_ProcFsmAbort_PlmnList();

        /* 由于未进行LIST搜网，搜索到的网络列表为空 */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                                VOS_FALSE,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* 退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 向GAS发送LIST搜网请求,迁移状态到等待GAS LIST搜网回复状态,启动保护定时器 */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_NET_RAT_TYPE_GSM);

    /* 向GMM发送搜网指示 */
    NAS_MMC_SndGmmPlmnSchInit();

    /* 向MM发送搜网指示 */
    NAS_MMC_SndMmPlmnSchInit();

    /* 设置进入搜网状态 */
    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitWasSysInfoIndExpired_PlmnList_WaitWasSysInfoInd
 功能描述  : 在list搜网的等待WAS 系统消息时,收到TI_NAS_MMC_WAIT_WAS_SYS_INFO消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:TI_NAS_MMC_WAIT_WAS_SYS_INFO消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月02日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2011年09月21日
    作    者   : W00166186
    修改内容   : V7R1 PHASE II
  3.日    期   : 2014年04月18日
    作    者   : s00261364
    修改内容   : V3R360_eCall项目
  4.日    期   : 2015年9月26日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiWaitWasSysInfoIndExpired_PlmnList_WaitWasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitWasSysInfoIndExpired_PlmnList_WaitWasSysInfoInd Enter!");

    /* 清除驻留PLMN RAI LAC信息*/
    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* 更新驻留状态 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);

    /* 更新服务状态 */
    /* Added by s00261364 for V3R360_eCall项目, 2014-4-18, begin */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NO_SERVICE);
    NAS_MMC_UpdateRegStateSpecPlmnSearch();
    /* Added by s00261364 for V3R360_eCall项目, 2014-4-18, end */

    /* 状态机退出标记为真 */
    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnList())
    {
        NAS_MMC_ProcFsmAbort_PlmnList();

        /* 由于未进行LIST搜网，搜索到的网络列表为空 */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                                VOS_FALSE,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* 退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 向WAS发送LIST搜网请求,迁移状态到等待WAS LIST搜网回复状态,启动保护定时器 */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);

    /* 向GMM发送搜网指示 */
    NAS_MMC_SndGmmPlmnSchInit();

    /* 向MM发送搜网指示 */
    NAS_MMC_SndMmPlmnSchInit();

    /* 设置进入搜网状态 */
    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitGasSysInfoIndExpired_PlmnList_WaitGasSysInfoInd
 功能描述  : 在list搜网的等待GAS 系统消息时,收到TI_NAS_MMC_WAIT_GAS_SYS_INFO消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:TI_NAS_MMC_WAIT_GAS_SYS_INFO消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月02日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2011年09月21日
    作    者   : W00166186
    修改内容   : V7R1 PHASE II
  3.日    期   : 2014年04月18日
    作    者   : s00261364
    修改内容   : V3R360_eCall项目
  4.日    期   : 2015年9月26日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiWaitGasSysInfoIndExpired_PlmnList_WaitGasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitGasSysInfoIndExpired_PlmnList_WaitGasSysInfoInd Enter!");

    /* 清除驻留PLMN RAI LAC信息*/
    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* 更新驻留状态 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);

    /* 更新服务状态 */
    /* Added by s00261364 for V3R360_eCall项目, 2014-4-18, begin */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NO_SERVICE);
    NAS_MMC_UpdateRegStateSpecPlmnSearch();
    /* Added by s00261364 for V3R360_eCall项目, 2014-4-18, end */

    /* 状态机退出标记为真 */
    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnList())
    {
        NAS_MMC_ProcFsmAbort_PlmnList();

        /* 由于未进行LIST搜网，搜索到的网络列表为空 */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                                VOS_FALSE,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* 退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 向GAS发送LIST搜网请求,迁移状态到等待GAS LIST搜网回复状态,启动保护定时器 */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_NET_RAT_TYPE_GSM);

    /* 向GMM发送搜网指示 */
    NAS_MMC_SndGmmPlmnSchInit();

    /* 向MM发送搜网指示 */
    NAS_MMC_SndMmPlmnSchInit();

    /* 设置进入搜网状态 */
    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitCsPsRegRsltInd
 功能描述  : 在list搜网的等待CS/PS的注册结果时,收到MMCMMC_ABORT_FSM_REQ消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:MMCMMC_ABORT_FSM_REQ消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月30日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2015年9月26日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);

    NAS_MMC_SndMsccListSearchCnfMsg_PlmnList();

    /* 未开始搜网，此时搜索列表为空,记录当前注册导致的后续addition值，L1 MAIN上
       收到链路释放后根据addition值决定是否触发搜网 */
    NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                            VOS_FALSE,
                            NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                            NAS_MMC_GetRegRsltInfo_PlmnList());

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTafPlmnListAbortReq_PlmnList_WaitCsPsRegRsltInd
 功能描述  : 在list搜网的等待CS/PS的注册结果时,收到ID_MSCC_MMC_PLMN_LIST_ABORT_REQ消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:ID_MSCC_MMC_PLMN_LIST_ABORT_REQ消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月02日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTafPlmnListAbortReq_PlmnList_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);

    /* 发送ID_MMC_MSCC_PLMN_LIST_ABORT_CNF */
    NAS_MMC_SndMsccPlmnListAbortCnf_PlmnList();

    /* 未开始搜网，此时搜索列表为空,记录当前注册导致的后续addition值，L1 MAIN上
       收到链路释放后根据addition值决定是否触发搜网 */
    NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                            VOS_FALSE,
                            NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                            NAS_MMC_GetRegRsltInfo_PlmnList());

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGmmPsRegResultInd_PlmnList_WaitCsPsRegRsltInd
 功能描述  : 在list搜网的等待CS/PS的注册结果时,收到GMMMMC_PS_REG_RESULT_IND消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:GMMMMC_PS_REG_RESULT_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月02日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2011年09月21日
    作    者   : W00166186
    修改内容   : V7R1 PHASE II
  3.日    期   : 2012年9月11日
    作    者   : w00176964
    修改内容   : V7R1_GUTL项目调整:TD主模下驻留态下需要通知MM/GMM进入搜网状态
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvGmmPsRegResultInd_PlmnList_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsAdditionalAction;
    GMMMMC_PS_REG_RESULT_IND_STRU                          *pstPsRegRslt = VOS_NULL_PTR;

    pstPsRegRslt = (GMMMMC_PS_REG_RESULT_IND_STRU*)pstMsg;

    /* 等待RRC链路释放时如果发生重选，切换以及CCO，可能网络会发生改变，
       状态机退出后收到缓存的注册结果消息，需要判断当前网络是
       否发生改变，发生改变则丢弃当前注册结果 */
    if ( pstPsRegRslt->enNetType != NAS_MML_GetCurrNetRatType())
    {
        return VOS_TRUE;
    }

    /* 处理PS的注册结果*/
    NAS_MMC_ProcPsRegRslt_PlmnList(pstPsRegRslt);

    /* 清除当前等待PS的注册结果 */
    NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_PS);

    /* 是否已经收齐CS/PS的注册结果 */
    if ( NAS_MMC_WAIT_REG_RESULT_IND_NULL != NAS_MMC_GetWaitRegRsltFlag_PlmnList())
    {
        return VOS_TRUE;
    }

    /* 调用优先级比较表格得出CS/PS的处理优先级，并转换为状态机下一步行为 */
    enCsAdditionalAction = NAS_MMC_GetCsRegAdditionalAction_PlmnList();
    enPsAdditionalAction = NAS_MMC_GetPsRegAdditionalAction_PlmnList();
    enAdditionalAction   = NAS_MMC_GetPrioAddtionalAction(enCsAdditionalAction, enPsAdditionalAction);

    /* 如果CS/PS还要继续尝试注册，需要在此状态继续等待注册结果 */
    if (NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT == enAdditionalAction)
    {
        return VOS_TRUE;
    }

    /* 停止等待注册结果的保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);

    if ( VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        /* 迁移状态到等待GU的RRC链路释放 */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_RRC_CONN_REL_IND);

        /* 启动保护定时器 */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL, TI_NAS_MMC_WAIT_RRC_CONN_REL_LEN);

        return VOS_TRUE;
    }

    /* 驻留态在GTL模式TD为主模时需要通知MM/GMM进入搜网状态 */
    if (VOS_TRUE == NAS_MMC_IsCurrentTdscdmaMode())
    {
        /* 向GMM发送搜网指示 */
        NAS_MMC_SndGmmPlmnSchInit();

        /* 向MM发送搜网指示 */
        NAS_MMC_SndMmPlmnSchInit();
    }

    /* 根据当前的接入模式，发起LIST搜网请求,迁移状态，启动保护定时器 */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_GetCurrNetRatType());

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmCsRegResultInd_PlmnList_WaitCsPsRegRsltInd
 功能描述  : 在list搜网的等待CS/PS的注册结果时,收到MMMMC_CS_REG_RESULT_IND消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:MMMMC_CS_REG_RESULT_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月02日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2012年9月11日
    作    者   : w00176964
    修改内容   : V7R1_GUTL项目调整:TD主模下驻留态下需要通知MM/GMM进入搜网状态
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmCsRegResultInd_PlmnList_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsAdditionalAction;
    MMMMC_CS_REG_RESULT_IND_STRU                           *pstCsRegRslt = VOS_NULL_PTR;

    pstCsRegRslt = (MMMMC_CS_REG_RESULT_IND_STRU*)pstMsg;

    /* 等待RRC链路释放时如果发生重选，切换以及CCO，可能网络会发生改变，
       状态机退出后收到缓存的注册结果消息，需要判断当前网络是
       否发生改变，发生改变则丢弃当前注册结果 */
    if ( pstCsRegRslt->enNetType != NAS_MML_GetCurrNetRatType())
    {
        return VOS_TRUE;
    }

    /* 处理CS的注册结果 */
    NAS_MMC_ProcCsRegRslt_PlmnList(pstCsRegRslt);

    /* 清除当前等待CS的注册结果 */
    NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_CS);

    /* 是否已经收齐CS/PS的注册结果 */
    if ( NAS_MMC_WAIT_REG_RESULT_IND_NULL != NAS_MMC_GetWaitRegRsltFlag_PlmnList() )
    {
        return VOS_TRUE;
    }

    /* 调用优先级比较表格得出CS/PS的处理优先级，并转换为状态机下一步行为 */
    enCsAdditionalAction = NAS_MMC_GetCsRegAdditionalAction_PlmnList();
    enPsAdditionalAction = NAS_MMC_GetPsRegAdditionalAction_PlmnList();
    enAdditionalAction   = NAS_MMC_GetPrioAddtionalAction(enCsAdditionalAction, enPsAdditionalAction);

    /* 如果CS/PS还要继续尝试注册，需要在此状态继续等待注册结果 */
    if (NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT == enAdditionalAction)
    {
        return VOS_TRUE;
    }

    /* 停止等待注册结果的保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);

    if ( VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        /* 迁移状态到等待GU的RRC链路释放 */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_RRC_CONN_REL_IND);

        /* 启动保护定时器 */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL, TI_NAS_MMC_WAIT_RRC_CONN_REL_LEN);

        return VOS_TRUE;
    }

    /* 驻留态在GTL模式TD为主模时需要通知MM/GMM进入搜网状态 */
    if (VOS_TRUE == NAS_MMC_IsCurrentTdscdmaMode())
    {
        /* 向GMM发送搜网指示 */
        NAS_MMC_SndGmmPlmnSchInit();

        /* 向MM发送搜网指示 */
        NAS_MMC_SndMmPlmnSchInit();
    }

    /* 根据当前的接入模式，发起LIST搜网请求,迁移状态，启动保护定时器 */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_GetCurrNetRatType());

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmAbortInd_PlmnList_WaitCsPsRegRsltInd
 功能描述  : 等待CS PS注册过程中收到 MM Abort消息的处理
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
VOS_UINT32 NAS_MMC_RcvMmAbortInd_PlmnList_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMMMC_ABORT_IND_STRU               *pstMmAbortInd   = VOS_NULL_PTR;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_GU_ACTION_RSLT_INFO_STRU    stActionRslt;
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
        NAS_MMC_SetCsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL);
    }

#if (FEATURE_ON == FEATURE_LTE)

    /* 给LMM发送ID_MMC_LMM_ACTION_RESULT_REQ */
    /* 构造ActionRslt消息，结果为CN_Rej,类型填为新增NAS_MML_PROC_MM_ABORT类型
       请求和结果域都是CS，原因值为Abort带的原因值 */
    stActionRslt.enProcType     = NAS_MML_PROC_MM_ABORT;
    stActionRslt.enRegRst       = NAS_MML_REG_RESULT_CN_REJ;
    stActionRslt.enReqDomain    = NAS_MMC_REG_DOMAIN_CS;
    stActionRslt.enRstDomain    = NAS_MMC_REG_DOMAIN_CS;
    stActionRslt.enCnCause      = pstMmAbortInd->enAbortCause;
    stActionRslt.ulAttemptCount = 0x0;

    NAS_MMC_SndLmmRegActionResultReq(&stActionRslt);
#endif

    return VOS_TRUE;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGmmNetworkDetachInd_PlmnList_WaitCsPsRegRsltInd
 功能描述  : 在list搜网的等待CS/PS的注册结果时,收到MMCGMM_NETWORK_DETACH_IND消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:MMCGMM_NETWORK_DETACH_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月30日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2011年12月5日
    作    者   : z00161729
    修改内容   : V7R1 Phase IV调整,当前SYSCFG中L不在时，也需要向LMM通知ID_MMC_LMM_ACTION_RESULT_REQ
  3.日    期   : 2012年2月13日
    作    者   : w00167002
    修改内容   : DTS2011122704039:additional action值若为无效值NAS_MMC_ADDITIONAL_ACTION_BUTT
                 则不更新当前的additional action
  4.日    期   : 2012年9月11日
    作    者   : w00176964
    修改内容   : V7R1_GUTL项目调整:TD主模下驻留态下需要通知MM/GMM进入搜网状态
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvGmmNetworkDetachInd_PlmnList_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMCGMM_NETWORK_DETACH_IND_STRU                         *pstDetachMsg = VOS_NULL_PTR;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsAdditionalAction;

    pstDetachMsg        = (MMCGMM_NETWORK_DETACH_IND_STRU *)pstMsg;

    /* 处理Detach结果 */
    enAdditionalAction = NAS_MMC_ProcGmmNetworkDetachInd(pstDetachMsg);

    /* AdditionalAction有效，更新PS的下一步的动作类型 */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enAdditionalAction )
    {
        NAS_MMC_SetPsRegAdditionalAction_PlmnList(enAdditionalAction);
    }

    /* 清除PS域的等待标志 */
    NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_PS);

#if   (FEATURE_ON == FEATURE_LTE)
    /* 给LMM发送detach结果消息 */
    NAS_MMC_SndLmmMtDetachIndActionResultReq(pstDetachMsg->ulDetachType,
                                           (NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16)pstDetachMsg->ulDetachCause);
#endif

    /* 需要继续注册时，不需要执行后续的动作 */
    if (NAS_MMC_GMM_NT_DETACH_REATTACH == pstDetachMsg->ulDetachType)
    {
        return VOS_TRUE;
    }

    /* 未收齐CS/PS的结果，继续等待注册结果 */
    if (NAS_MMC_WAIT_REG_RESULT_IND_NULL != NAS_MMC_GetWaitRegRsltFlag_PlmnList())
    {
        return VOS_TRUE;
    }

    /* 调用优先级比较表格得出CS/PS的处理优先级，并转换为状态机下一步行为 */
    enCsAdditionalAction = NAS_MMC_GetCsRegAdditionalAction_PlmnList();
    enPsAdditionalAction = NAS_MMC_GetPsRegAdditionalAction_PlmnList();
    enAdditionalAction   = NAS_MMC_GetPrioAddtionalAction(enCsAdditionalAction, enPsAdditionalAction);

    /* 如果CS/PS还要继续尝试注册，需要在此状态继续等待注册结果 */
    if (NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT == enAdditionalAction)
    {
        return VOS_TRUE;
    }

    /* 停止等待注册结果的保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);

    if ( VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        /* 迁移状态到等待GU的RRC链路释放 */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_RRC_CONN_REL_IND);

        /* 启动保护定时器 */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL, TI_NAS_MMC_WAIT_RRC_CONN_REL_LEN);

        return VOS_TRUE;
    }

    /* 驻留态在GTL模式TD为主模时需要通知MM/GMM进入搜网状态 */
    if (VOS_TRUE == NAS_MMC_IsCurrentTdscdmaMode())
    {
        /* 向GMM发送搜网指示 */
        NAS_MMC_SndGmmPlmnSchInit();

        /* 向MM发送搜网指示 */
        NAS_MMC_SndMmPlmnSchInit();
    }

    /* 根据当前的接入模式，发起LIST搜网请求,迁移状态，启动保护定时器 */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_GetCurrNetRatType());

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGmmServiceRequestResultInd_PlmnList_WaitCsPsRegRsltInd
 功能描述  : 在list搜网的等待CS/PS的注册结果时,收到GMMMMC_SERVICE_REQUEST_RESULT_IND消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:GMMMMC_SERVICE_REQUEST_RESULT_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月30日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2012年2月13日
    作    者   : w00167002
    修改内容   : DTS2011122704039:additional action值若为无效值NAS_MMC_ADDITIONAL_ACTION_BUTT
                 则不更新当前的additional action
  3.日    期   : 2012年9月11日
    作    者   : w00176964
    修改内容   : V7R1_GUTL项目调整:TD主模下驻留态下需要通知MM/GMM进入搜网状态
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvGmmServiceRequestResultInd_PlmnList_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    GMMMMC_SERVICE_REQUEST_RESULT_IND_STRU                 *pstServiceRsltInd = VOS_NULL_PTR;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsAdditionalAction;

    pstServiceRsltInd = (GMMMMC_SERVICE_REQUEST_RESULT_IND_STRU*)pstMsg;

    if (GMM_MMC_ACTION_RESULT_SUCCESS == pstServiceRsltInd->ulServiceSts)
    {
        /* 更新PS的AdditionalAction */
        NAS_MMC_SetPsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON);
    }
    else
    {
        /* 如果服务失败，处理不同拒绝原因值，返回PS additional Action */
        enAdditionalAction = NAS_MMC_ProcPsServiceRegFail(pstServiceRsltInd);

        /* AdditionalAction有效，更新PS的下一步的动作类型 */
        if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enAdditionalAction )
        {
            NAS_MMC_SetPsRegAdditionalAction_PlmnList(enAdditionalAction);
        }
    }

    /* 清除PS域的等待标志 */
    NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_PS);

    /* 如果注册结果还未收齐，退出函数, 继续等待 */
    if (NAS_MMC_WAIT_REG_RESULT_IND_NULL != NAS_MMC_GetWaitRegRsltFlag_PlmnList())
    {
        return VOS_TRUE;
    }

    /* 调用优先级比较表格得出CS/PS的处理优先级，并转换为状态机下一步行为 */
    enCsAdditionalAction = NAS_MMC_GetCsRegAdditionalAction_PlmnList();
    enPsAdditionalAction = NAS_MMC_GetPsRegAdditionalAction_PlmnList();
    enAdditionalAction   = NAS_MMC_GetPrioAddtionalAction(enCsAdditionalAction, enPsAdditionalAction);

    /* 如果CS/PS还要继续尝试注册，需要在此状态继续等待注册结果 */
    if (NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT == enAdditionalAction)
    {
        return VOS_TRUE;
    }

    /* 停止等待注册结果的保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);

    if ( VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        /* 迁移状态到等待GU的RRC链路释放 */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_RRC_CONN_REL_IND);

        /* 启动保护定时器 */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL, TI_NAS_MMC_WAIT_RRC_CONN_REL_LEN);

        return VOS_TRUE;
    }

    /* 驻留态在GTL模式TD为主模时需要通知MM/GMM进入搜网状态 */
    if (VOS_TRUE == NAS_MMC_IsCurrentTdscdmaMode())
    {
        /* 向GMM发送搜网指示 */
        NAS_MMC_SndGmmPlmnSchInit();

        /* 向MM发送搜网指示 */
        NAS_MMC_SndMmPlmnSchInit();
    }

    /* 根据当前的接入模式，发起LIST搜网请求,迁移状态，启动保护定时器 */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_GetCurrNetRatType());

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvAreaLostInd_PlmnList_WaitCsPsRegRsltInd
 功能描述  : 等待两个域注册结果时丢网
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月4日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2013年4月4日
    作    者   : y00176023
    修改内容   : DSDS GUNAS II项目:收到NO RF 退状态机，发送list搜网失败消息
  3.日    期   : 2014年5月4日
    作    者   : t00173447
    修改内容   : DTS2014042105390,软银定制需求
  4.日    期   : 2014年04月9日
    作    者   : s00261364
    修改内容   : V3R360_eCall项目:增加服务状态上报处理
  5.日    期   : 2014年10月13日
    作    者   : w00167002
    修改内容   : DTS2014102005694:G下，CS注册成功后，PS还未注册成功时候，则
               发起电话业务，在电话业务建联时候丢网，MM没有释放信令，MMC没有发起ANY
               CELL搜网。
  6.日    期   : 2015年9月25日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvAreaLostInd_PlmnList_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止等待注册结果消息的定时器  */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);

    /* Modified by c00318887 for 预置频点搜网优化, 2015-9-9, begin */
    NAS_MMC_SaveLastCampedPlmnWithRat(NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMcc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMnc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.enCampPlmnNetRat);
    /* Modified by c00318887 for 预置频点搜网优化, 2015-9-9, end */


    /* Added by s00261364 for V3R360_eCall项目, 2014-4-8, begin */
    /* 上报对应的CS/PS服务状态MSCC_MMC_SERVICE_STATUS_NO_SERVICE */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NO_SERVICE);
    NAS_MMC_UpdateRegStateSpecPlmnSearch();
    /* Added by s00261364 for V3R360_eCall项目, 2014-4-8, end */

    /* 清除驻留状态 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* 当前信号更新 */
    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());


    /* 通知MM/GMM进入丢网,MM会释放CS业务 */
    NAS_MMC_SndMmCoverageLostInd();
    NAS_MMC_SndGmmCoverageLostInd();

    if (VOS_FALSE == NAS_MML_GetRfAvailFlg())
    {
        NAS_MMC_SndMsccPlmnListRejMsg_PlmnList();

        /* 发送list搜网失败消息 */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                VOS_FALSE,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());
        /* 退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 向WAS/GAS发送LIST搜网请求,迁移状态到等待WAS/GAS LIST搜网回复状态,启动保护定时器 */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_GetCurrNetRatType());

    /* 向GMM发送搜网指示 */
    NAS_MMC_SndGmmPlmnSchInit();

    /* 向MM发送搜网指示 */
    NAS_MMC_SndMmPlmnSchInit();

    /* 设置进入搜网状态 */
    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmSysInfoInd_PlmnList_WaitCsPsRegRsltInd
 功能描述  : 在等待CS+PS注册过程中收到W模式系统消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月4日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmSysInfoInd_PlmnList_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
   /* 处理WAS系统消息 */
    NAS_MMC_ProcWasSysInfo_PlmnList(pstMsg);

    /* 更新当前等待CSPS的注册结果 */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList();
    NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_CS);
    NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_PS);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGrrMmSysInfoInd_PlmnList_WaitCsPsRegRsltInd
 功能描述  : 在等待CS+PS注册过程中收到G模式系统消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月4日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2013年11月01日
    作    者   : l00208543
    修改内容   : 根据卡类型禁止网络制式
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvGrrMmSysInfoInd_PlmnList_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 如果收到GAS的系统消息，且目前Utran被Enable，则重新Disable Utran */
    NAS_MMC_RcvGasSysInfoSetUtranCapabilityStatus();

    /* 处理GAS系统消息 */
    NAS_MMC_ProcGasSysInfo_PlmnList(pstMsg);

    /* 更新当前等待CSPS的注册结果 */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList();
    NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_CS);
    NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_PS);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmSuspendInd_PlmnList_WaitCsPsRegRsltInd
 功能描述  : 在list搜网的等待CS/PS的注册结果时,收到RRMM_SUSPEND_IND消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:RRMM_SUSPEND_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月02日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2011年12月20日
    作    者   : h44270
    修改内容   : 启动异系统状态机时，认为当前无网络，此时APS挂起
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmSuspendInd_PlmnList_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_IND_ST             *pstSuspendMsg = VOS_NULL_PTR;

    pstSuspendMsg = (RRMM_SUSPEND_IND_ST*)pstMsg;

    /* 根据不同的挂起原因值，启动不同的状态机 */
    switch (pstSuspendMsg->ucSuspendCause)
    {
        case MMC_SUSPEND_CAUSE_CELLRESELECT:
        case MMC_SUSPEND_CAUSE_REDIRECTION:
            NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_INTER_SYS_CELLRESEL);
            NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,
                                     NAS_MML_GetSimPsRegStatus());
            break;

        case MMC_SUSPEND_CAUSE_PLMNSEARCH:

            /* 向接入层发送挂起失败 */
            NAS_MMC_SndAsSuspendRsp(RRC_NAS_SUSPEND_FAILURE, pstSuspendMsg->MsgHeader.ulSenderPid);

            /* 更新服务状态 */
            NAS_MMC_SetCsServiceStatus(NAS_MMC_NO_SERVICE);

            NAS_MMC_SetPsServiceStatus(NAS_MMC_NO_SERVICE);

            /* 需要主动释放链路 */
            NAS_MMC_SndMmRelReq();

            NAS_MMC_SndGmmRelReq();

            NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

            /* 迁移状态到等待RRC链路释放 */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_RRC_CONN_REL_IND);

            /* 启动保护定时器 */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL, TI_NAS_MMC_WAIT_RRC_CONN_REL_LEN);

            break;
        case MMC_SUSPEND_CAUSE_HANDOVER:
            NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_INTER_SYS_HO);
            NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,
                                     NAS_MML_GetSimPsRegStatus());
            break;

        case MMC_SUSPEND_CAUSE_CELLCHANGE:
            NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_INTER_SYS_CCO);
            NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,
                                     NAS_MML_GetSimPsRegStatus());
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvRrMmSuspendInd_PlmnList_WaitCsPsRegRsltInd:Unexpected suspend type!");
            break;
    }

    return VOS_TRUE;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcMmcSuspendRslt_PlmnList_WaitCsPsRegRsltInd
 功能描述  : 在list搜网的等待CS/PS的注册结果时,收到MMCMMC_SUSPEND_RSLT_CNF消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:MMCMMC_SUSPEND_RSLT_CNF消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月02日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2011年09月21日
    作    者   : W00166186
    修改内容   : V7R1 PHASE II
  3.日    期   : 2011年12月20日
    作    者   : h44270
    修改内容   : 退出异系统状态机时，通知APS当前所在网络
  4.日    期   : 2012年04月26日
    作    者   : w00176964
    修改内容   : GUL BG项目调整
  5.日    期   : 2013年2月7日
    作    者   : W00176964
    修改内容   : Volte_phase3项目调整:增加IMS不可用时disable L模的逻辑修改
  6.日    期   : 2013年4月4日
    作    者   : y00176023
    修改内容   : DSDS GUNAS II项目:收到NO RF 退状态机，发送失败消息，迁移到OOC
  7.日    期   : 2015年9月25日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcMmcSuspendRslt_PlmnList_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 重选后当前接入技术已经改变，需要重新初始化搜网的接入技术优先级 */
#if (FEATURE_ON == FEATURE_CSG)
    if (VOS_TRUE == NAS_MMC_IsCsgList_PlmnList())
    {
        NAS_MMC_InitCsgListSearchRatInfo_PlmnList();
    }
    else
#endif
    {
        NAS_MMC_InitSearchRatInfo_PlmnList();
    }


    NAS_MMC_NotifyModeChange(NAS_MML_GetCurrNetRatType(),
                             NAS_MML_GetSimPsRegStatus());

    if (VOS_FALSE == NAS_MML_GetRfAvailFlg())
    {
        /* 停止保护定时器 */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);

        NAS_MMC_SndMsccPlmnListRejMsg_PlmnList();

        /* 由于未进行LIST搜网，搜索到的网络列表为空 */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                VOS_FALSE,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());


        /* 退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

#if (FEATURE_ON == FEATURE_LTE)
    /* 判断当前接入模式 */
    if ( NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        /* 停止保护定时器 */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);

        /* IDLE态下从GU异系统到LTE后,LTE下可能发起注册或不发起注册
           都会给MMC上报注册结果 */
        /* 更新CSPS的AdditionalAction */
        NAS_MMC_SetCsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_BUTT);
        NAS_MMC_SetPsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_BUTT);

        /* 更新当前等待EPS的注册结果 */
        NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList();

        NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_PS);

        /* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-8, begin */
#if (FEATURE_ON == FEATURE_IMS)
        NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_IMS);
#endif
        /* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-8, end */

        /* 迁移状态到等待L下的EPS注册结果 */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_EPS_REG_IND);

        /* 启动保护定时器 */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_REG_IND, TI_NAS_MMC_WAIT_EPS_REG_IND_LEN);

        return VOS_TRUE;
    }
#endif

    /* 继续等待注册结果 */
    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitCsPsRegRsltIndExpired_PlmnList_WaitCsPsRegRsltInd
 功能描述  : 在list搜网的等待CS/PS的注册结果时,收到TI_NAS_MMC_WAIT_CSPS_REG_IND消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:TI_NAS_MMC_WAIT_CSPS_REG_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月02日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2012年9月11日
    作    者   : w00176964
    修改内容   : V7R1_GUTL项目调整:TD主模下驻留态下需要通知MM/GMM进入搜网状态
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiWaitCsPsRegRsltIndExpired_PlmnList_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitCsPsRegRsltIndExpired_PlmnList_WaitCsPsRegRsltInd Enter");

    /* 清除等待注册结果标记 */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList();

    /* 存在信令链接 继续等待RRC链接释放 */
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        /* 迁移状态到等待GU的RRC链路释放 */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_RRC_CONN_REL_IND);

        /* 启动保护定时器 */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL, TI_NAS_MMC_WAIT_RRC_CONN_REL_LEN);

        return VOS_TRUE;
    }

    /* 驻留态在GTL模式TD为主模时需要通知MM/GMM进入搜网状态 */
    if (VOS_TRUE == NAS_MMC_IsCurrentTdscdmaMode())
    {
        /* 向GMM发送搜网指示 */
        NAS_MMC_SndGmmPlmnSchInit();

        /* 向MM发送搜网指示 */
        NAS_MMC_SndMmPlmnSchInit();
    }

    /* 根据当前的接入模式，发起LIST搜网请求,迁移状态，启动保护定时器 */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_GetCurrNetRatType());

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrmmLimitServiceCampInd_PlmnList_WaitRrcConnRelInd
 功能描述  : 列表搜网等连接释放状态，对OOS消息RRMM_LIMIT_SERVICE_CAMP_IND的处理
 输入参数  : pstMsg        - RRMM_LIMIT_SERVICE_CAMP_IND消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月15日
    作    者   : z00161729
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrmmLimitServiceCampInd_PlmnList_WaitRrcConnRelInd(
        VOS_UINT32                          ulEventType,
        struct MsgCB                       *pstMsg
)
{
    return NAS_MMC_RcvRrmmLimitServiceCampInd_PlmnList(ulEventType, pstMsg);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrmmLimitServiceCampInd_PlmnList_WaitCsPsRegRsltInd
 功能描述  : 列表搜网等注册结果状态，对OOS消息RRMM_LIMIT_SERVICE_CAMP_IND的处理
 输入参数  : pstMsg        - RRMM_LIMIT_SERVICE_CAMP_IND消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月15日
    作    者   : z00161729
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrmmLimitServiceCampInd_PlmnList_WaitCsPsRegRsltInd(
        VOS_UINT32                          ulEventType,
        struct MsgCB                       *pstMsg
)
{
    return NAS_MMC_RcvRrmmLimitServiceCampInd_PlmnList(ulEventType, pstMsg);
}

/* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-8, begin */
/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMsccImsVoiceCapInd_PlmnList_WaitCsPsRegRsltInd
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
VOS_UINT32 NAS_MMC_RcvMsccImsVoiceCapInd_PlmnList_WaitCsPsRegRsltInd(
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
 函 数 名  : NAS_MMC_RcvRrmmLimitServiceCampInd_PlmnList
 功能描述  : 列表搜网时，对OOS消息的处理
 输入参数  : pstMsg        - RRMM_LIMIT_SERVICE_CAMP_IND消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年06月27日
    作    者   : l65478
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrmmLimitServiceCampInd_PlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_LIMIT_SERVICE_CAMP_IND_STRU        *pstRrmmLimitCampOnMsg = VOS_NULL_PTR;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU    *pastIntraPlmnSrchInfo = VOS_NULL_PTR;
    NAS_MMC_PLMN_LIST_SEARCH_CTRL_STRU      *pstSearchRatInfo   = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU              *pstRatPrioList     = VOS_NULL_PTR;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU    *pstListInfo        = VOS_NULL_PTR;
    VOS_UINT8                                ucRatCnt;

    pstRrmmLimitCampOnMsg = (RRMM_LIMIT_SERVICE_CAMP_IND_STRU *)pstMsg;

    pstSearchRatInfo = NAS_MMC_GetSearchCtrlInfo_PlmnList();
    pstRatPrioList   = NAS_MML_GetMsPrioRatList();
    pstListInfo      = NAS_MMC_GetSearchedPlmnListInfo_PlmnList();

    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);

    pastIntraPlmnSrchInfo = (NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                                             sizeof(NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU) * NAS_MML_MAX_RAT_NUM);
    /* memory alloc fail */
    if (VOS_NULL_PTR == pastIntraPlmnSrchInfo)
    {
        return VOS_TRUE;
    }

    /* 把所有的RAT都设置为已经搜索 */
    for (ucRatCnt = 0; ucRatCnt < pstRatPrioList->ucRatNum; ucRatCnt++)
    {
        pstListInfo[ucRatCnt].enRatType = pstSearchRatInfo[ucRatCnt].enRat;

        pstSearchRatInfo[ucRatCnt].ucSearchedFlag = VOS_TRUE;
    }

    /* 保存搜网列表 */
    NAS_MMC_UpdateSearchedPlmnListInfo_PlmnList(&(pstRrmmLimitCampOnMsg->stPlmnIdList));

    /* 把转换后的PLMN信息保存到本地变量中 */
    PS_MEM_CPY(pastIntraPlmnSrchInfo, pstListInfo, sizeof(NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU) * NAS_MML_MAX_RAT_NUM);


    /* 删除列表中禁止的PLMN */
    NAS_MMC_DelForbPlmnFromAsSrchedPlmnList(pastIntraPlmnSrchInfo);

    /* 手动搜网模式下删除非用户指定的PLMN */
    NAS_MMC_DelNotUserSpecPlmnFromSrchedPlmnList(pastIntraPlmnSrchInfo);

    /* 可维可测信息勾出 */
    NAS_MMC_LogAsPlmnList(pastIntraPlmnSrchInfo);

    /* 用户LIST搜网 */
    if ( VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
    {
        /* 将搜索到的网络进行排序后上报给MSCC */
        NAS_MMC_SndMsccPlmnListCnf_PlmnList();


        /* 退出状态机 */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_SUCC,
                                VOS_TRUE,
                                pastIntraPlmnSrchInfo,
                                NAS_MMC_GetRegRsltInfo_PlmnList());
        NAS_MMC_FSM_QuitFsmL2();

        PS_MEM_FREE(WUEPS_PID_MMC, pastIntraPlmnSrchInfo);
        return VOS_TRUE;
    }

#if (FEATURE_ON == FEATURE_CSG)
    if (VOS_TRUE == NAS_MMC_IsCsgList_PlmnList())
    {
        /* 将搜索到的网络进行排序后上报给MSCC */
        NAS_MMC_SndMsccCsgListSearchCnf_PlmnList();

        /* 退出状态机 */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_SUCC,
                                VOS_TRUE,
                                pastIntraPlmnSrchInfo,
                                NAS_MMC_GetRegRsltInfo_PlmnList());
        NAS_MMC_FSM_QuitFsmL2();

        PS_MEM_FREE(WUEPS_PID_MMC, pastIntraPlmnSrchInfo);
        return VOS_TRUE;
    }
#endif


    /* 需要发起搜网 */
    if (VOS_TRUE == NAS_MMC_IsExistAvailPlmnInSearchedPlmnList(pastIntraPlmnSrchInfo))
    {
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_SUCC,
                                VOS_TRUE,
                                pastIntraPlmnSrchInfo,
                                NAS_MMC_GetRegRsltInfo_PlmnList());


        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
    }

    PS_MEM_FREE(WUEPS_PID_MMC, pastIntraPlmnSrchInfo);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitWasPlmnSearchCnf
 功能描述  : 在等待WAS的LIST搜网回复状态,收到退出消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:MMCMMC_ABORT_FSM_REQ消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止等待WAS搜网结果的保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_LIST_CNF);

    /* 记录状态机退出标记 */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* 向WAS发送停止搜网请求,迁移状态,启动保护定时器 */
    NAS_MMC_SndSpecRatPlmnSearchStopReq_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTafPlmnListAbortReq_PlmnList_WaitWasPlmnSearchCnf
 功能描述  : 在等待WAS的LIST搜网回复状态,收到ID_MSCC_MMC_PLMN_LIST_ABORT_REQ消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:ID_MSCC_MMC_PLMN_LIST_ABORT_REQ消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTafPlmnListAbortReq_PlmnList_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止等待WAS搜网结果的保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_LIST_CNF);

    /* 记录状态机退出标记 */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* 设置通知MSCC回复标记 */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_TRUE);

    /* 向WAS发送停止搜网请求,迁移状态,启动保护定时器 */
    NAS_MMC_SndSpecRatPlmnSearchStopReq_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmPlmnSrchCnf_PlmnList_WaitWasPlmnSearchCnf
 功能描述  : 在等待WAS的LIST搜网回复状态,收到RRMM_PLMN_SEARCH_CNF消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:RRMM_PLMN_SEARCH_CNF消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmPlmnSrchCnf_PlmnList_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU          *pstPlmnSearchcnf = VOS_NULL_PTR;

    pstPlmnSearchcnf = (RRMM_PLMN_SEARCH_CNF_STRU*)pstMsg;

    /* 停止等待WAS搜网回复的保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_LIST_CNF);

    /* 处理PLMN LIST的结果 */
    NAS_MMC_ProcRrmmSearchCnf_PlmnList(pstPlmnSearchcnf);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmRelInd_PlmnList_WaitWasPlmnSearchCnf
 功能描述  : 在等待WAS的LIST搜网回复状态,收到RRMM_REL_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:RRMM_REL_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2012年6月18日
    作    者   : l00171473
    修改内容   : DTS2012051104124, 无需判断REL IND原因值.
                 WAS:接收到RRMM_PLMN_SEARCH_REQ时，不会上报正常原因的rel ind，
                 只有异常原因的rel ind

  3.日    期   : 2014年6月30日
    作    者   : w00176964
    修改内容   : DSDS III:  WAS异常NO RF释放，则进入OOC进行处理
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmRelInd_PlmnList_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_REL_IND_STRU                  *pstRrmmRelIndMsg    = VOS_NULL_PTR;

    pstRrmmRelIndMsg = (RRMM_REL_IND_STRU *)pstMsg;

    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvRrMmRelInd_PlmnList_WaitWasPlmnSearchCnf Enter!");

    /* 无需判断原因值 */

    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_LIST_CNF);

    if (RRC_REL_CAUSE_NO_RF == pstRrmmRelIndMsg->ulRelCause)
    {
        NAS_MMC_ProcNoRf_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);

        return VOS_TRUE;
    }

    /* 发送状态机退出结果 */
    NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                            VOS_FALSE,
                            NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                            NAS_MMC_GetRegRsltInfo_PlmnList());

        /* 启动5S周期性尝试LIST搜网定时器 */
        if ( VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
        {
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST, TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST_LEN);
        }
        else
        {
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST, TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST_LEN);
        }

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();


    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmSysInfoInd_PlmnList_WaitWasPlmnSearchCnf
 功能描述  : 在等待WAS的LIST搜网回复状态,收到RRMM_SYS_INFO_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:RRMM_SYS_INFO_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月01日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmSysInfoInd_PlmnList_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 更新驻留信息，并转发系统消息 */
    NAS_MMC_ProcWasSysInfo_PlmnList(pstMsg);

    /* 不迁移状态 */
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmAreaLostInd_PlmnList_WaitWasPlmnSearchCnf
 功能描述  : 在list搜网的等待搜网回复消息时,收到RRMM_AREA_LOST_IND消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:RRMM_AREA_LOST_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月4日
    作    者   : w00176964
    修改内容   : 新生成函数

  2.日    期   : 2014年5月4日
    作    者   : t00173447
    修改内容   : DTS2014042105390,软银定制需求
  3.日    期   : 2014年04月9日
    作    者   : s00261364
    修改内容   : V3R360_eCall项目:增加服务状态上报处理
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmAreaLostInd_PlmnList_WaitAsPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Modified by c00318887 for 预置频点搜网优化, 2015-9-9, begin */
    NAS_MMC_SaveLastCampedPlmnWithRat(NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMcc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMnc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.enCampPlmnNetRat);
    /* Modified by c00318887 for 预置频点搜网优化, 2015-9-9, end */


     /* 清除驻留状态 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);

    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* 当前信号更新 */
    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());

    /* 向MM/GMM/TAF报出服务区流程 */
    NAS_MMC_SndMmCoverageLostInd();

    NAS_MMC_SndGmmCoverageLostInd();

    /* Added by s00261364 for V3R360_eCall项目, 2014-4-30, begin */
    /* 上报对应的CS/PS服务状态MSCC_MMC_SERVICE_STATUS_NO_SERVICE */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NO_SERVICE);
    NAS_MMC_UpdateRegStateSpecPlmnSearch();
    /* Added by s00261364 for V3R360_eCall项目, 2014-4-30, end */

    /* 更新服务状态 */
    NAS_MMC_SndMsccCoverageInd( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );

    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmCsRegResultInd_PlmnList_WaitWasPlmnSearchCnf
 功能描述  : 在list搜网的等待搜网回复消息时,收到MMMMC_CS_REG_RESULT_IND消息后的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月22日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmCsRegResultInd_PlmnList_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMMMC_CS_REG_RESULT_IND_STRU       *pstCsRegRslt = VOS_NULL_PTR;

    pstCsRegRslt = (MMMMC_CS_REG_RESULT_IND_STRU*)pstMsg;

    /* 等待RRC链路释放时如果发生重选，切换以及CCO，可能网络会发生改变，
       状态机退出后收到缓存的注册结果消息，需要判断当前网络是
       否发生改变，发生改变则丢弃当前注册结果 */
    if ( pstCsRegRslt->enNetType != NAS_MML_GetCurrNetRatType())
    {
        return VOS_TRUE;
    }

    /* 处理CS的注册结果 */
    NAS_MMC_ProcCsRegRslt_PlmnList(pstCsRegRslt);

    /* 不迁移状态 */
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGmmPsRegResultInd_PlmnList_WaitWasPlmnSearchCnf
 功能描述  : 在list搜网的等待搜网回复消息时,收到GMMMMC_PS_REG_RESULT_IND消息后的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月22日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvGmmPsRegResultInd_PlmnList_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    GMMMMC_PS_REG_RESULT_IND_STRU      *pstPsRegRslt = VOS_NULL_PTR;

    pstPsRegRslt = (GMMMMC_PS_REG_RESULT_IND_STRU*)pstMsg;

    /* 等待RRC链路释放时如果发生重选，切换以及CCO，可能网络会发生改变，
       状态机退出后收到缓存的注册结果消息，需要判断当前网络是
       否发生改变，发生改变则丢弃当前注册结果 */
    if ( pstPsRegRslt->enNetType != NAS_MML_GetCurrNetRatType())
    {
        return VOS_TRUE;
    }

    /* 处理PS的注册结果*/
    NAS_MMC_ProcPsRegRslt_PlmnList(pstPsRegRslt);

    /* 不迁移状态 */
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitWasPlmnListCnfExpired_PlmnList_WaitWasPlmnSearchCnf
 功能描述  : 在等待WAS的LIST搜网回复状态,收到TI_NAS_MMC_WAIT_WAS_PLMN_LIST_CNF消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:TI_NAS_MMC_WAIT_WAS_PLMN_LIST_CNF消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2012年4月27日
    作    者   : t00212959
    修改内容   : GUL BG项目调整
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiWaitWasPlmnListCnfExpired_PlmnList_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{


    /* LIST搜网过程中，接入层可能上报RRMM_NOT_CAMP_ON，此时需要根据当前驻留状态更新RAT的搜索标记 */
    if (NAS_MMC_AS_CELL_CAMP_ON == NAS_MMC_GetAsCellCampOn())
    {
        /* 更新三模RAT的搜索标记 */

#if (FEATURE_ON == FEATURE_LTE)

        NAS_MMC_SetSearchedFlag_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

#endif

        NAS_MMC_SetSearchedFlag_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);

        NAS_MMC_SetSearchedFlag_PlmnList(NAS_MML_NET_RAT_TYPE_GSM);
    }
    else
    {
        /* 更新当前RAT的搜索标记 */
        NAS_MMC_SetSearchedFlag_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);
    }

    /* 向WAS发送停止搜网请求,迁移状态,启动保护定时器 */
    NAS_MMC_SndSpecRatPlmnSearchStopReq_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitGasPlmnSearchCnf
 功能描述  : 在等待GAS的LIST搜网回复状态,收到退出消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:MMCMMC_ABORT_FSM_REQ消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitGasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止等待GAS搜网结果的保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_LIST_CNF);

    /* 记录状态机退出标记 */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* 向GAS发送停止搜网请求,迁移状态,启动保护定时器 */
    NAS_MMC_SndSpecRatPlmnSearchStopReq_PlmnList(NAS_MML_NET_RAT_TYPE_GSM);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTafPlmnListAbortReq_PlmnList_WaitGasPlmnSearchCnf
 功能描述  : 在等待GAS的LIST搜网回复状态,收到ID_MSCC_MMC_PLMN_LIST_ABORT_REQ消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:ID_MSCC_MMC_PLMN_LIST_ABORT_REQ消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTafPlmnListAbortReq_PlmnList_WaitGasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止等待GAS搜网结果的保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_LIST_CNF);

    /* 记录状态机退出标记 */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* 设置通知MSCC回复标记 */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_TRUE);

    /* 向GAS发送停止搜网请求,迁移状态,启动保护定时器 */
    NAS_MMC_SndSpecRatPlmnSearchStopReq_PlmnList(NAS_MML_NET_RAT_TYPE_GSM);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmPlmnSrchCnf_PlmnList_WaitGasPlmnSearchCnf
 功能描述  : 在等待GAS的LIST搜网回复状态,收到RRMM_PLMN_SEARCH_CNF消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:RRMM_PLMN_SEARCH_CNF消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmPlmnSrchCnf_PlmnList_WaitGasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU          *pstPlmnSrchcnf = VOS_NULL_PTR;

    pstPlmnSrchcnf = (RRMM_PLMN_SEARCH_CNF_STRU*)pstMsg;

    /* 停止等待GAS搜网回复的保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_LIST_CNF);

    /* 处理PLMN LIST的结果 */
    NAS_MMC_ProcRrmmSearchCnf_PlmnList(pstPlmnSrchcnf);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGrrMmSysInfoInd_PlmnList_WaitGasPlmnSearchCnf
 功能描述  : 在等待GAS的LIST搜网回复状态,收到GRRMM_SYS_INFO_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:GRRMM_SYS_INFO_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月01日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2013年11月01日
    作    者   : l00208543
    修改内容   : 根据卡类型禁止网络制式
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvGrrMmSysInfoInd_PlmnList_WaitGasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 如果收到GAS的系统消息，且目前Utran被Enable，则重新Disable Utran */
    NAS_MMC_RcvGasSysInfoSetUtranCapabilityStatus();

    /* 更新驻留信息，并转发系统消息 */
    NAS_MMC_ProcGasSysInfo_PlmnList(pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmCsRegResultInd_PlmnList_WaitGasPlmnSearchCnf
 功能描述  : 在list搜网的等待搜网回复消息时,收到MMMMC_CS_REG_RESULT_IND消息后的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月22日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmCsRegResultInd_PlmnList_WaitGasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMMMC_CS_REG_RESULT_IND_STRU       *pstCsRegRslt = VOS_NULL_PTR;

    pstCsRegRslt = (MMMMC_CS_REG_RESULT_IND_STRU*)pstMsg;

    /* 等待RRC链路释放时如果发生重选，切换以及CCO，可能网络会发生改变，
       状态机退出后收到缓存的注册结果消息，需要判断当前网络是
       否发生改变，发生改变则丢弃当前注册结果 */
    if ( pstCsRegRslt->enNetType != NAS_MML_GetCurrNetRatType())
    {
        return VOS_TRUE;
    }

    /* 处理CS的注册结果 */
    NAS_MMC_ProcCsRegRslt_PlmnList(pstCsRegRslt);

    /* 不迁移状态 */
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGmmPsRegResultInd_PlmnList_WaitGasPlmnSearchCnf
 功能描述  : 在list搜网的等待搜网回复消息时,收到GMMMMC_PS_REG_RESULT_IND消息后的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月22日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvGmmPsRegResultInd_PlmnList_WaitGasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    GMMMMC_PS_REG_RESULT_IND_STRU      *pstPsRegRslt = VOS_NULL_PTR;

    pstPsRegRslt = (GMMMMC_PS_REG_RESULT_IND_STRU*)pstMsg;

    /* 等待RRC链路释放时如果发生重选，切换以及CCO，可能网络会发生改变，
       状态机退出后收到缓存的注册结果消息，需要判断当前网络是
       否发生改变，发生改变则丢弃当前注册结果 */
    if ( pstPsRegRslt->enNetType != NAS_MML_GetCurrNetRatType())
    {
        return VOS_TRUE;
    }

    /* 处理PS的注册结果*/
    NAS_MMC_ProcPsRegRslt_PlmnList(pstPsRegRslt);

    /* 不迁移状态 */
    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitGasPlmnListCnfExpired_PlmnList_WaitGasPlmnSearchCnf
 功能描述  : 在等待GAS的LIST搜网回复状态,收到TI_NAS_MMC_WAIT_GAS_PLMN_LIST_CNF消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:TI_NAS_MMC_WAIT_GAS_PLMN_LIST_CNF消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2012年4月27日
    作    者   : t00212959
    修改内容   : GUL BG项目调整

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiWaitGasPlmnListCnfExpired_PlmnList_WaitGasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* LIST搜网过程中，接入层可能上报RRMM_NOT_CAMP_ON，此时需要根据当前驻留状态更新RAT的搜索标记 */
    if (NAS_MMC_AS_CELL_CAMP_ON == NAS_MMC_GetAsCellCampOn())
    {
        /* 更新三模RAT的搜索标记 */

#if (FEATURE_ON == FEATURE_LTE)

        NAS_MMC_SetSearchedFlag_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

#endif

        NAS_MMC_SetSearchedFlag_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);

        NAS_MMC_SetSearchedFlag_PlmnList(NAS_MML_NET_RAT_TYPE_GSM);
    }
    else
    {
        /* 更新当前RAT的搜索标记 */
        NAS_MMC_SetSearchedFlag_PlmnList(NAS_MML_NET_RAT_TYPE_GSM);
    }

    /* 向GAS发送停止搜网请求,迁移状态,启动保护定时器 */
    NAS_MMC_SndSpecRatPlmnSearchStopReq_PlmnList(NAS_MML_NET_RAT_TYPE_GSM);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitWasSuspendCnf
 功能描述  : 在等待WAS的suspend回复状态,收到MMCMMC_ABORT_FSM_REQ消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:MMCMMC_ABORT_FSM_REQ消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 记录需要终止当前状态机标志 */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTafPlmnListAbortReq_PlmnList_WaitWasSuspendCnf
 功能描述  : 在等待WAS的suspend回复状态,收到ID_MSCC_MMC_PLMN_LIST_ABORT_REQ消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:ID_MSCC_MMC_PLMN_LIST_ABORT_REQ消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTafPlmnListAbortReq_PlmnList_WaitWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 记录需要终止当前状态机标志 */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* 设置通知MSCC回复标记 */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmSuspendCnf_PlmnList_WaitWasSuspendCnf
 功能描述  : 在等待WAS的suspend回复状态,收到RRMM_SUSPEND_CNF消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:RRMM_SUSPEND_CNF消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2011年09月21日
    作    者   : W00166186
    修改内容   : V7R1 PHASE II
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmSuspendCnf_PlmnList_WaitWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_CNF_ST                *pstRrmmSuspendCnf = VOS_NULL_PTR;

    pstRrmmSuspendCnf  = (RRMM_SUSPEND_CNF_ST*)pstMsg;

    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF);

    /* 处理挂起回复结果 */
    NAS_MMC_ProcRrmmSuspendCnf_PlmnList(pstRrmmSuspendCnf);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitWasSuspendCnfExpired_PlmnList_WaitWasSuspendCnf
 功能描述  : 在等待WAS的suspend回复状态,收到TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
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
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiWaitWasSuspendCnfExpired_PlmnList_WaitWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    enCurRat      = NAS_MML_GetCurrNetRatType();

    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitWasSuspendCnfExpired_PlmnList_WaitWasSuspendCnf: Timer Expired");

    /* 不可恢复故障，复位 */

    if ( (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
      && (NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat) )
    {
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_WAS_SUSPEND_CNF_EXPIRED);
    }
    else
    {
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_TD_SUSPEND_CNF_EXPIRED);
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitGasSuspendCnf
 功能描述  : 在等待GAS的suspend回复状态,收到MMCMMC_ABORT_FSM_REQ消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:MMCMMC_ABORT_FSM_REQ消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitGasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 记录需要终止当前状态机标志 */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTafPlmnListAbortReq_PlmnList_WaitGasSuspendCnf
 功能描述  : 在等待GAS的suspend回复状态,收到ID_MSCC_MMC_PLMN_LIST_ABORT_REQ消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:ID_MSCC_MMC_PLMN_LIST_ABORT_REQ消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTafPlmnListAbortReq_PlmnList_WaitGasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 记录需要终止当前状态机标志 */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* 设置通知MSCC回复标记 */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmSuspendCnf_PlmnList_WaitGasSuspendCnf
 功能描述  : 在等待GAS的suspend回复状态,收到RRMM_SUSPEND_CNF消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:RRMM_SUSPEND_CNF消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2011年09月21日
    作    者   : W00166186
    修改内容   : V7R1 PHASE II
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmSuspendCnf_PlmnList_WaitGasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_CNF_ST                *pstRrmmSuspendCnf = VOS_NULL_PTR;

    pstRrmmSuspendCnf  = (RRMM_SUSPEND_CNF_ST*)pstMsg;

    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF);

    /* 处理挂起回复结果 */
    NAS_MMC_ProcRrmmSuspendCnf_PlmnList(pstRrmmSuspendCnf);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitGasSuspendCnfExpired_PlmnList_WaitGasSuspendCnf
 功能描述  : 在等待GAS的suspend回复状态,收到TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : w00176964
    修改内容   : 新生成函数

  2.日    期   : 2011年12月15日
    作    者   : w00167002
    修改内容   : DTS2011120702166:MMC复位后无复位信息,在MML模块封装复位信息，
                  以供MM层调用，进行软复位。

  3.日    期   : 2015年3月11日
    作    者   : wx270776
    修改内容   : DTS2015011212939:增加复位场景
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiWaitGasSuspendCnfExpired_PlmnList_WaitGasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitGasSuspendCnfExpired_PlmnList_WaitGasSuspendCnf: Timer Expired");

    /* 不可恢复故障，复位 */

    NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_GAS_SUSPEND_CNF_EXPIRED);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmPlmnSrchStopCnf_PlmnList_WaitWasPlmnSearchStopCnf
 功能描述  : 在等待WAS的停止搜网回复状态,收到RRMM_PLMN_SEARCH_STOP_CNF消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:RRMM_PLMN_SEARCH_STOP_CNF消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2011年09月21日
    作    者   : W00166186
    修改内容   : V7R1 PHASE II
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmPlmnSrchStopCnf_PlmnList_WaitWasPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF);

    /* 处理搜网停止回复结果 */
    NAS_MMC_ProcRrmmPlmnSearchStopCnf_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);

    /* 不迁移状态 */
    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmSysInfoInd_PlmnList_WaitWasPlmnSearchStopCnf
 功能描述  : 在等待WAS的停止搜网回复状态,收到RRMM_SYS_INFO_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:RRMM_SYS_INFO_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月8日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmSysInfoInd_PlmnList_WaitWasPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 更新驻留信息，并转发系统消息 */
    NAS_MMC_ProcWasSysInfo_PlmnList(pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitWasPlmnSearchStopCnf
 功能描述  : 在等待WAS的停止搜网回复状态,收到MMCMMC_ABORT_FSM_REQ消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:MMCMMC_ABORT_FSM_REQ消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月28日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitWasPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 记录需要终止当前状态机标志 */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTafPlmnListAbortFsmMsg_PlmnList_WaitWasPlmnSearchStopCnf
 功能描述  : 在等待WAS的停止搜网回复状态,收到ID_MSCC_MMC_PLMN_LIST_ABORT_REQ消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:ID_MSCC_MMC_PLMN_LIST_ABORT_REQ消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTafPlmnListAbortFsmMsg_PlmnList_WaitWasPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 记录需要终止当前状态机标志 */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* 设置通知MSCC回复标记 */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmPlmnSrchCnf_PlmnList_WaitWasPlmnSearchStopCnf
 功能描述  : 在list搜网的等待Was的停止搜网回复时,收到RRMM_PLMN_SEARCH_CNF消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:RRMM_PLMN_SEARCH_CNF消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月28日
    作    者   : t00212959
    修改内容   : 新生成函数
  2.日    期   : 2012年5月28日
    作    者   : z00161729
    修改内容   : V7R1C50 GUL背景搜修改
  3.日    期   : 2012年6月25日
    作    者   : z00161729
    修改内容   : V7R1C50 DTS2012062105468:MMC的stop plmn cnf和L的search cnf对冲，MMC增加保护认为收到WAS
                 的stop plmn cnf，退出状态机
  4.日    期   : 2014年7月9日
    作    者   : w00176964
    修改内容   : DSDS III项目:处理LIST NO RF对冲
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmPlmnSrchCnf_PlmnList_WaitWasPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU          *pstPlmnSrchCnf = VOS_NULL_PTR;

    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat;
    VOS_UINT32                          ulIndex;

    pstPlmnSrchCnf = (RRMM_PLMN_SEARCH_CNF_STRU*)pstMsg;

    /* LIST搜网回复与停止搜网对冲,NO RF时直接退出LIST搜网流程 */
    if (RRC_PLMN_SEARCH_RLT_LIST_NO_RF == pstPlmnSrchCnf->ulSearchRlt)
    {
        /* 停止保护定时器 */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF);

        NAS_MMC_ProcNoRf_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);

        return VOS_TRUE;
    }

     /*只有在搜索成功时才进行处理 */
    if (RRC_PLMN_SEARCH_RLT_LIST != pstPlmnSrchCnf->ulSearchRlt)
    {
        return VOS_TRUE;
    }

    /* LIST搜网过程中,需要根据当前接入层携带的已经搜索过的接入技术信息更新RAT的搜索标记 */
    for ( ulIndex = 0; ulIndex < NAS_RRC_MAX_RAT_NUM; ulIndex++)
    {
        if ( RRC_NAS_RAT_LIST_SEARCH_CMPL == pstPlmnSrchCnf->astSearchRatInfo[ulIndex].enListSearchRlt)
        {
            /*将RRC的接入技术转换成MML定义的格式，然后更新 */
            NAS_MMC_ConvertRrcRatToNasFormat(pstPlmnSrchCnf->astSearchRatInfo[ulIndex].enRat, &enRat);
            NAS_MMC_SetSearchedFlag_PlmnList(enRat);
        }
    }

    /* 保存搜网列表 */
    NAS_MMC_UpdateSearchedPlmnListInfo_PlmnList(&(pstPlmnSrchCnf->PlmnIdList));

    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF);

    /* 处理搜网停止回复结果 */
    NAS_MMC_ProcRrmmPlmnSearchStopCnf_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmRelInd_PlmnList_WaitWasPlmnSearchStopCnf
 功能描述  : 在等待WAS的停止搜网回复状态,收到RRMM_REL_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:RRMM_REL_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月12日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2012年6月18日
    作    者   : l00171473
    修改内容   : DTS2012051104124, WAS:接收到RRMM_PLMN_SEARCH_STOP_REQ时，
                 可能发送有异常原因的rel ind或者RRMM_PLMN_SEARCH_STOP_CNF,
                 收到rel ind时认为停止列表搜网结束.
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmRelInd_PlmnList_WaitWasPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvRrMmRelInd_PlmnList_WaitWasPlmnSearchStopCnf: ENTERED");

    /* 无需判断原因值 */

    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF);

    /* 状态机退出结果为真 */
    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnList())
    {
        /* 当前用户列表搜网 */
        if (VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
        {
            if ( VOS_TRUE == NAS_MMC_GetNotifyMsccFlag_PlmnList())
            {
                /* 向MSCC回复ID_MMC_MSCC_PLMN_LIST_ABORT_CNF */
                NAS_MMC_SndMsccPlmnListAbortCnf_PlmnList();
            }
            else
            {
                /* 向MSCC回复LIST搜网结果 */
                NAS_MMC_SndMsccPlmnListCnf_PlmnList();
            }
        }

        /* 发送状态机ABORT退出结果 */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                                VOS_FALSE,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 发送状态机退出结果 */
    NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                            VOS_FALSE,
                            NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                            NAS_MMC_GetRegRsltInfo_PlmnList());

    /* 启动5S周期性尝试LIST搜网定时器 */
    if ( VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
    {
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST, TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST_LEN);
    }
    else
    {
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST, TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST_LEN);
    }

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitWasStopCnfExpired_PlmnList_WaitWasPlmnSearchStopCnf
 功能描述  : 在等待WAS的停止搜网回复状态,收到TI_NAS_MMC_WAIT_WAS_STOP_CNF消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:TI_NAS_MMC_WAIT_WAS_STOP_CNF消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiWaitWasStopCnfExpired_PlmnList_WaitWasPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitWasStopCnfExpired_PlmnList_WaitWasPlmnSearchStopCnf: Timer Expired");

    /* 处理搜网停止回复结果 */
    NAS_MMC_ProcRrmmPlmnSearchStopCnf_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitGasPlmnSearchStopCnf
 功能描述  : 在等待WAS的停止搜网回复状态,收到MMCMMC_ABORT_FSM_REQ消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:MMCMMC_ABORT_FSM_REQ消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月28日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitGasPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 记录需要终止当前状态机标志 */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmPlmnSrchStopCnf_PlmnList_WaitGasPlmnSearchStopCnf
 功能描述  : 在等待GAS的停止搜网回复状态,收到RRMM_PLMN_SEARCH_STOP_CNF消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:RRMM_PLMN_SEARCH_STOP_CNF消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2011年09月21日
    作    者   : W00166186
    修改内容   : V7R1 PHASE II
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmPlmnSrchStopCnf_PlmnList_WaitGasPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF);

    /* 处理搜网停止回复结果 */
    NAS_MMC_ProcRrmmPlmnSearchStopCnf_PlmnList(NAS_MML_NET_RAT_TYPE_GSM);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGrrMmSysInfoInd_PlmnList_WaitGasPlmnSearchStopCnf
 功能描述  : 在等待GAS的停止搜网回复状态,收到GRRMM_SYS_INFO_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:GRRMM_SYS_INFO_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月8日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2013年11月01日
    作    者   : l00208543
    修改内容   : 根据卡类型禁止网络制式
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvGrrMmSysInfoInd_PlmnList_WaitGasPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 如果收到GAS的系统消息，且目前Utran被Enable，则重新Disable Utran */
    NAS_MMC_RcvGasSysInfoSetUtranCapabilityStatus();

    /* 更新驻留信息，并转发系统消息 */
    NAS_MMC_ProcGasSysInfo_PlmnList(pstMsg);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTafPlmnListAbortFsmMsg_PlmnList_WaitGasPlmnSearchStopCnf
 功能描述  : 在等待GAS的停止搜网回复状态,收到ID_MSCC_MMC_PLMN_LIST_ABORT_REQ消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:ID_MSCC_MMC_PLMN_LIST_ABORT_REQ消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTafPlmnListAbortFsmMsg_PlmnList_WaitGasPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 记录需要终止当前状态机标志 */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* 设置通知MSCC回复标记 */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmPlmnSrchCnf_PlmnList_WaitGasPlmnSearchStopCnf
 功能描述  : 在list搜网的等待Gas的停止搜网回复时,收到RRMM_PLMN_SEARCH_CNF消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:RRMM_PLMN_SEARCH_CNF消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月28日
    作    者   : t00212959
    修改内容   : 新生成函数
  2.日    期   : 2012年5月28日
    作    者   : z00161729
    修改内容   : V7R1C50 GUL背景搜网修改
  3.日    期   : 2012年6月25日
    作    者   : z00161729
    修改内容   : V7R1C50 DTS2012062105468:MMC的stop plmn cnf和L的search cnf对冲，MMC增加保护认为收到L
                 的stop plmn cnf，退出状态机
  4.日    期   : 2014年7月9日
    作    者   : w00176964
    修改内容   : DSDS III项目:处理LIST NO RF对冲
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmPlmnSrchCnf_PlmnList_WaitGasPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU          *pstPlmnSrchCnf = VOS_NULL_PTR;

    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat;
    VOS_UINT32                          ulIndex;

    pstPlmnSrchCnf = (RRMM_PLMN_SEARCH_CNF_STRU*)pstMsg;

     /* LIST搜网回复与停止搜网对冲,NO RF时直接退出LIST搜网流程 */
     if (RRC_PLMN_SEARCH_RLT_LIST_NO_RF == pstPlmnSrchCnf->ulSearchRlt)
     {
         /* 停止保护定时器 */
         NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF);

         NAS_MMC_ProcNoRf_PlmnList(NAS_MML_NET_RAT_TYPE_GSM);

         return VOS_TRUE;
     }

     /*只有在搜索成功时才进行处理 */
    if (RRC_PLMN_SEARCH_RLT_LIST != pstPlmnSrchCnf->ulSearchRlt)
    {
        return VOS_TRUE;
    }

    /* LIST搜网过程中,需要根据当前接入层携带的已经搜索过的接入技术信息更新RAT的搜索标记 */
    for ( ulIndex = 0; ulIndex < NAS_RRC_MAX_RAT_NUM; ulIndex++)
    {
        if ( RRC_NAS_RAT_LIST_SEARCH_CMPL == pstPlmnSrchCnf->astSearchRatInfo[ulIndex].enListSearchRlt)
        {
            /*将RRC的接入技术转换成MML定义的格式，然后更新 */
            NAS_MMC_ConvertRrcRatToNasFormat(pstPlmnSrchCnf->astSearchRatInfo[ulIndex].enRat, &enRat);
            NAS_MMC_SetSearchedFlag_PlmnList(enRat);
        }
    }

    /* 保存搜网列表 */
    NAS_MMC_UpdateSearchedPlmnListInfo_PlmnList(&(pstPlmnSrchCnf->PlmnIdList));

    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF);

    /* 处理搜网停止回复结果 */
    NAS_MMC_ProcRrmmPlmnSearchStopCnf_PlmnList(NAS_MML_NET_RAT_TYPE_GSM);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitGasStopCnfExpired_PlmnList_WaitGasPlmnSearchStopCnf
 功能描述  : 在等待GAS的停止搜网回复状态,收到TI_NAS_MMC_WAIT_GAS_STOP_CNF消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:TI_NAS_MMC_WAIT_GAS_STOP_CNF消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2011年09月21日
    作    者   : W00166186
    修改内容   : V7R1 PHASE II
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiWaitGasStopCnfExpired_PlmnList_WaitGasPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitGasStopCnfExpired_PlmnList_WaitGasPlmnSearchStopCnf: Timer Expired");

    /* 处理搜网停止回复结果 */
    NAS_MMC_ProcRrmmPlmnSearchStopCnf_PlmnList(NAS_MML_NET_RAT_TYPE_GSM);

    return VOS_TRUE;
}


#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitEpsConnRelInd
 功能描述  : 在list搜网的等待EPS链路释放状态,收到MMCMMC_ABORT_FSM_REQ消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:MMCMMC_ABORT_FSM_REQ消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月30日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2015年9月26日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND);

    NAS_MMC_SndMsccListSearchCnfMsg_PlmnList();

    /* 未开始搜网，此时搜索列表为空,记录当前注册导致的后续addition值，L1 MAIN上
       收到链路释放后根据addition值决定是否触发搜网 */
    NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                            VOS_FALSE,
                            NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                            NAS_MMC_GetRegRsltInfo_PlmnList());

    /*退出状态机*/
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTafPlmnListAbortReq_PlmnList_WaitEpsConnRelInd
 功能描述  : 在list搜网的等待EPS链路释放状态,收到ID_MSCC_MMC_PLMN_LIST_ABORT_REQ消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:ID_MSCC_MMC_PLMN_LIST_ABORT_REQ消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月01日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTafPlmnListAbortReq_PlmnList_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND);

    /* 发送ID_MMC_MSCC_PLMN_LIST_ABORT_CNF */
    NAS_MMC_SndMsccPlmnListAbortCnf_PlmnList();

    /* 未开始搜网，此时搜索列表为空,记录当前注册导致的后续addition值，L1 MAIN上
       收到链路释放后根据addition值决定是否触发搜网 */
    NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                            VOS_FALSE,
                            NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                            NAS_MMC_GetRegRsltInfo_PlmnList());

    /*退出状态机*/
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmSuspendInd_PlmnList_WaitEpsConnRelInd
 功能描述  : 在list搜网的等待EPS链路释放状态,收到ID_LMM_MMC_SUSPEND_IND消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:ID_LMM_MMC_SUSPEND_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月01日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmSuspendInd_PlmnList_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 根据不同的挂起原因值,启动不同的状态机 */
    LMM_MMC_SUSPEND_IND_STRU           *pstLSuspendMsg  = VOS_NULL_PTR;

    pstLSuspendMsg = (LMM_MMC_SUSPEND_IND_STRU*)pstMsg;

    /* 根据不同的挂起原因值，启动不同的状态机 */
    switch (pstLSuspendMsg->ulSysChngType)
    {
        case MMC_LMM_SUS_TYPE_RSL:
        case MMC_LMM_SUS_TYPE_REDIR:
            NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_INTER_SYS_CELLRESEL);
            break;

        case MMC_LMM_SUS_TYPE_HO:
            NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_INTER_SYS_HO);
            break;

        case MMC_LMM_SUS_TYPE_CCO:
            NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_INTER_SYS_CCO);
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmSuspendInd_PlmnList_WaitEpsConnRelInd:Unexpected Suspend Type!");
            break;
    }

    if ( (MMC_LMM_SUS_TYPE_BUTT != pstLSuspendMsg->ulSysChngType)
      && (MMC_LMM_SUS_TYPE_CCO_REVERSE != pstLSuspendMsg->ulSysChngType))
    {
        NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,
                                 NAS_MML_GetSimPsRegStatus());
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmMmcStatusInd_PlmnList_WaitEpsConnRelInd
 功能描述  : 在list搜网的等待EPS链路释放状态,收到ID_LMM_MMC_STATUS_IND消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:ID_LMM_MMC_STATUS_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月01日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2011年09月21日
    作    者   : W00166186
    修改内容   : V7R1 PHASE II
  3.日    期   : 2012年04月26日
    作    者   : W00176964
    修改内容   : GUL BG项目调整
  4.日    期   : 2014年02月8日
    作    者   : W00176964
    修改内容   : VOLTE_Phase3项目调整:等待EPS连接释放时收到L的注册结果后需要进一步等待IMS注册结果
  5.日    期   : 2015年9月26日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmMmcStatusInd_PlmnList_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_STATUS_IND_STRU            *pstLmmStatusIndMsg = VOS_NULL_PTR;

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

            /* 停止等待EPS链路释放定时器 */
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND);

            NAS_MMC_StartPeriodTryingUserListSrchTimer_PlmnList();

            /* 有业务时，未进行LIST搜网，搜到的网络列表为空,发送状态机失败的退出结果 */
            NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                     VOS_FALSE,
                                     NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                     NAS_MMC_GetRegRsltInfo_PlmnList());

            /* 退出状态机 */
            NAS_MMC_FSM_QuitFsmL2();

            return VOS_TRUE;

        case MMC_LMM_CONN_IDLE:

            NAS_MML_SetEpsSigConnStatusFlg(VOS_FALSE);
            NAS_MML_SetEpsServiceConnStatusFlg(VOS_FALSE);
            break;

        default:

            break;
    }

    /* 判断RRC链接是否存在 */
    if ( VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        /* 返回继续等待 */
        return VOS_TRUE;
    }

    /* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-8, begin */
    /* 等待IMS的注册结果 */
    if (NAS_MMC_WAIT_REG_RESULT_IND_NULL != NAS_MMC_GetWaitRegRsltFlag_PlmnList())
    {
        return VOS_TRUE;
    }
    /* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-8, end */

    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND);

    /* 向LMM发送LIST搜网请求,更新驻留状态为非驻留,迁移状态,启动保护定时器 */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

    /* 非驻留态通知MM/GMM搜网开始 */
    if (NAS_MMC_AS_CELL_NOT_CAMP_ON == NAS_MMC_GetAsCellCampOn())
    {
        /* 向GMM发送搜网指示 */
        NAS_MMC_SndGmmPlmnSchInit();

        /* 向MM发送搜网指示 */
        NAS_MMC_SndMmPlmnSchInit();

        NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);
    }

    return VOS_TRUE;

}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmSysInfoInd_PlmnList_WaitEpscConnRelInd
 功能描述  : 在list搜网的等待EPS链路释放状态,收到ID_LMM_MMC_SYS_INFO_IND消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:ID_LMM_MMC_SYS_INFO_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月01日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2011年12月30日
    作    者   : l65478
    修改内容   : 在迁到L模时,不立刻把CS设置成可选搜网,而是等待PS注册结果时
                 根据具体的原因值再设置
  3.日    期   : 2012年4月18日
    作    者   : l00130025
    修改内容   : DTS2012040200480,单独维护EPS注册状态,供L模下CEREG/CGREG查询和上报使用
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
  1.日    期   : 2015年02月11日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseII 项目修改
                 方案优化后，LTE下的小区发生变化，LMM会通过系统消息通知MMC
  9.日    期   : 2015年10月24日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmSysInfoInd_PlmnList_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ProcLteSysInfo_PlmnList(pstMsg);

    NAS_MMC_SetCsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_BUTT);
    NAS_MMC_SetPsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_BUTT);


    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmAttachInd_PlmnList_WaitEpscConnRelInd
 功能描述  : 在list搜网的等待EPS链路释放状态,收到ID_LMM_MMC_ATTACH_IND消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:ID_LMM_MMC_ATTACH_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月01日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2011年10月25日
    作    者   : z00161729
    修改内容   : V7R1 phase III联合注册修改
  3.日    期   : 2014年2月8日
    作    者   : w00176964
    修改内容   : VOLTE_Phase3项目修改:增加IMS支持时disable L模的逻辑

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmAttachInd_PlmnList_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_ATTACH_IND_STRU                                *pstLmmAttachIndMsg = VOS_NULL_PTR;

    pstLmmAttachIndMsg  = (LMM_MMC_ATTACH_IND_STRU*)pstMsg;

    /* 向GMM和MM转发注册结果消息 */
    NAS_MMC_SndMmLmmAttachInd(pstLmmAttachIndMsg);
    NAS_MMC_SndGmmLmmAttachInd(pstLmmAttachIndMsg);

    /* 处理attach结果 */
    NAS_MMC_ProcLmmAttachInd_PlmnList(pstLmmAttachIndMsg);

    /* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-8, begin */
    /* L下注册完成后，IMS时支持时会发起IMS注册,需要根据IMS注册的情况决定是否需要
       disable L模,此时需要进一步等待IMS的注册结果 */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList();

#if (FEATURE_ON == FEATURE_IMS)
    NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_IMS);
#endif
    /* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-8, end */

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmTauResultInd_PlmnList_WaitEpscConnRelInd
 功能描述  : 在list搜网的等待EPS链路释放状态,收到ID_LMM_MMC_TAU_RESULT_IND消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:ID_LMM_MMC_TAU_RESULT_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月01日
    作    者   : w00176964
    修改内容   : 新生成函数

  2.日    期   : 2011年10月26日
    作    者   : w00176964
    修改内容   : V7R1 Phase III调整:联合注册修改
  3.日    期   : 2014年2月8日
    作    者   : w00176964
    修改内容   : VOLTE_Phase3项目修改:增加IMS支持时disable L模的逻辑

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmTauResultInd_PlmnList_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_TAU_RESULT_IND_STRU        *pstLmmTauIndMsg;

    pstLmmTauIndMsg  = (LMM_MMC_TAU_RESULT_IND_STRU*)pstMsg;

    /* 向GMM和MM转发注册结果消息 */
    NAS_MMC_SndMmLmmTauResultInd(pstLmmTauIndMsg);
    NAS_MMC_SndGmmLmmTauResultInd(pstLmmTauIndMsg);

    /* 处理tau结果 */
    NAS_MMC_ProcLmmTauResultInd_PlmnList(pstLmmTauIndMsg);

    /* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-8, begin */
    /* L下注册完成后，IMS时支持时会发起IMS注册,需要根据IMS注册的情况决定是否需要
       disable L模,此时需要进一步等待IMS的注册结果 */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList();

#if (FEATURE_ON == FEATURE_IMS)
    NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_IMS);
#endif
    /* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-8, end */

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmDetachInd_PlmnList_WaitEpscConnRelInd
 功能描述  : 在list搜网的等待EPS链路释放状态,收到ID_LMM_MMC_DETACH_IND消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:ID_LMM_MMC_DETACH_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月01日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2011年10月26日
    作    者   : w00176964
    修改内容   : V7R1 Phase III调整:联合注册修改

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmDetachInd_PlmnList_WaitEpsConnRelInd(
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
        NAS_MMC_SetPsRegAdditionalAction_PlmnList(enPsAdditionalAction);
    }

    /*更新CS的下一步的动作类型*/
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enCsAdditionalAction)
    {
        NAS_MMC_SetCsRegAdditionalAction_PlmnList(enCsAdditionalAction);
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

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcMmcSuspendRslt_PlmnList_WaitEpscConnRelInd
 功能描述  : 在list搜网的等待EPS链路释放状态,收到MMCMMC_SUSPEND_RSLT_CNF消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:MMCMMC_SUSPEND_RSLT_CNF消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月01日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2011年09月21日
    作    者   : W00166186
    修改内容   : V7R1 PHASE II
  3.日    期   : 2011年12月20日
    作    者   : h44270
    修改内容   : 退出异系统状态机时，通知APS当前所在网络
  4.日    期   : 2012年5月3日
    作    者   : w00176964
    修改内容   : GUL BG项目调整
  7.日    期   : 2013年4月4日
    作    者   : y00176023
    修改内容   : DSDS GUNAS II项目:收到NO RF 退状态机，迁移到OOC
  8.日    期   : 2015年9月25日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcMmcSuspendRslt_PlmnList_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_NotifyModeChange(NAS_MML_GetCurrNetRatType(),
                             NAS_MML_GetSimPsRegStatus());

    /* 重选后当前接入技术已经改变，需要重新初始化搜网的接入技术优先级 */
 #if (FEATURE_ON == FEATURE_CSG)
    if (VOS_TRUE == NAS_MMC_IsCsgList_PlmnList())
    {
        NAS_MMC_InitCsgListSearchRatInfo_PlmnList();
    }
    else
 #endif
    {
        NAS_MMC_InitSearchRatInfo_PlmnList();
    }

    if (VOS_FALSE == NAS_MML_GetRfAvailFlg())
    {
        /* 停止保护定时器 */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND);

        NAS_MMC_SndMsccPlmnListRejMsg_PlmnList();

        /* 由于未进行LIST搜网，搜索到的网络列表为空 */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                VOS_FALSE,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());


        /* 退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 判断当前接入模式 */
    if ( NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        /* 判断当前信令链接是否存在 */
        if ( VOS_TRUE == NAS_MML_IsRrcConnExist())
        {
            /* 返回继续等待 */
            return VOS_TRUE;
        }

        /* 停止保护定时器 */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND);

        /* 向L发送LIST搜网请求,状态迁移到,启动保护定时器 */
        NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

        /* 非驻留态通知MM/GMM搜网开始 */
        if (NAS_MMC_AS_CELL_NOT_CAMP_ON == NAS_MMC_GetAsCellCampOn())
        {
            /* 向GMM发送搜网指示 */
            NAS_MMC_SndGmmPlmnSchInit();

            /* 向MM发送搜网指示 */
            NAS_MMC_SndMmPlmnSchInit();

            NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);
        }

        return VOS_TRUE;
    }

    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND);

    /* 更新CSPS的AdditionalAction */
    NAS_MMC_SetCsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_BUTT);
    NAS_MMC_SetPsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_BUTT);

    /* 迁移状态到等到CS/PS注册结果 */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList();
    NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_CS);
    NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_PS);

    /* 迁移到等待注册结果状态 */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_CSPS_REG_IND);

    /* 启动保护定时器 */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND, TI_NAS_MMC_WAIT_CSPS_REG_IND_LEN);

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitEpsConnRelIndExpired_PlmnList_WaitEpsConnRelInd
 功能描述  : 在list搜网的等待EPS链路释放状态,收到TI_NAS_MMC_WAIT_EPS_CONN_REL_IND消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:TI_NAS_MMC_WAIT_EPS_CONN_REL_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月01日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2011年10月25日
    作    者   : w00166186
    修改内容   : 新生成函数
  3.日    期   : 2012年6月5日
    作    者   : w00176964
    修改内容   : V7R1 C50 GUL BG项目调整:PS业务启动5S定时器保证LIST搜网有机会发起
  4.日    期   : 2015年9月26日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiWaitEpsConnRelIndExpired_PlmnList_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitRrcConnRelIndExpired_PlmnList_WaitRrcConnRelInd Enter!");

    /* 存在业务，回复列表搜失败 */
    if (VOS_TRUE == NAS_MML_GetCsServiceExistFlg())
    {
        NAS_MMC_SndMsccPlmnListRejMsg_PlmnList();
    }
    else
    {
        NAS_MMC_StartPeriodTryingUserListSrchTimer_PlmnList();
    }

    /* 由于未开始搜网，搜索到的网络列表为空，需要周期性尝试，退出状态机后不需要触发搜网 */
    NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                            VOS_FALSE,
                            NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                            NAS_MMC_GetRegRsltInfo_PlmnList());


    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


/* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-7, begin */
/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMsccImsVoiceCapInd_PlmnList_WaitEpsConnRelInd
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
VOS_UINT32 NAS_MMC_RcvMsccImsVoiceCapInd_PlmnList_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMC_IMS_VOICE_CAP_NOTIFY_STRU     *pstImsVoiceInd = VOS_NULL_PTR;
    VOS_UINT8                           ucWaitRegRsltFlag;

    ucWaitRegRsltFlag   = NAS_MMC_GetWaitRegRsltFlag_PlmnList();
    pstImsVoiceInd      = (MSCC_MMC_IMS_VOICE_CAP_NOTIFY_STRU *)pstMsg;

    /* 如果在等待IMS的注册结果才处理 */
    if (NAS_MMC_WAIT_REG_RESULT_IND_IMS != (ucWaitRegRsltFlag & NAS_MMC_WAIT_REG_RESULT_IND_IMS))
    {
        return VOS_TRUE;
    }

    NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_IMS);

    /* IMS不可用时判断是否需要disable LTE */
    if (VOS_FALSE  == pstImsVoiceInd->ucAvail)
    {
        if (VOS_TRUE == NAS_MMC_IsNeedDisableLte_ImsVoiceNotAvail())
        {
            NAS_MMC_SetCsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION);

            NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS);

            NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE);
        }
    }

    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND);

    /* 向LMM发送LIST搜网请求,更新驻留状态为非驻留,迁移状态,启动保护定时器 */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

    /* 非驻留态通知MM/GMM搜网开始 */
    if (NAS_MMC_AS_CELL_NOT_CAMP_ON == NAS_MMC_GetAsCellCampOn())
    {
        /* 向GMM发送搜网指示 */
        NAS_MMC_SndGmmPlmnSchInit();

        /* 向MM发送搜网指示 */
        NAS_MMC_SndMmPlmnSchInit();

        NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);
    }

    return VOS_TRUE;
}

/* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-7, end */


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitEpsRegInd
 功能描述  : 在list搜网的等待EPS注册结果状态,收到MMCMMC_ABORT_FSM_REQ消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:MMCMMC_ABORT_FSM_REQ消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月25日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2012年5月8日
    作    者   : t00212959
    修改内容   : GUL BG项目调整
  3.日    期   : 2015年9月26日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitEpsRegInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

    NAS_MMC_SndMsccListSearchCnfMsg_PlmnList();

    /* 未开始搜网，此时搜索列表为空,记录当前注册导致的后续addition值，L1 MAIN上
       收到链路释放后根据addition值决定是否触发搜网 */
    NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                            VOS_FALSE,
                            NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                            NAS_MMC_GetRegRsltInfo_PlmnList());

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTafPlmnListAbortReq_PlmnList_WaitEpsRegInd
 功能描述  : 在list搜网的等待EPS注册结果状态,收到ID_MSCC_MMC_PLMN_LIST_ABORT_REQ消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:ID_MSCC_MMC_PLMN_LIST_ABORT_REQ消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月25日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2012年5月8日
    作    者   : t00212959
    修改内容   : GUL BG项目调整
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTafPlmnListAbortReq_PlmnList_WaitEpsRegInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

    /* 发送ID_MMC_MSCC_PLMN_LIST_ABORT_CNF */
    NAS_MMC_SndMsccPlmnListAbortCnf_PlmnList();

    /* 未开始搜网，此时搜索列表为空,记录当前注册导致的后续addition值，L1 MAIN上
       收到链路释放后根据addition值决定是否触发搜网 */
    NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                            VOS_FALSE,
                            NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                            NAS_MMC_GetRegRsltInfo_PlmnList());

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmSuspendInd_PlmnList_WaitEpsRegInd
 功能描述  : 在list搜网的等待EPS注册结果状态,收到ID_LMM_MMC_SUSPEND_IND消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:ID_LMM_MMC_SUSPEND_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月25日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2012年5月8日
    作    者   : t00212959
    修改内容   : GUL BG项目调整
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmSuspendInd_PlmnList_WaitEpsRegInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_SUSPEND_IND_STRU           *pstLSuspendMsg = VOS_NULL_PTR;
    MMC_SUSPEND_CAUSE_ENUM_UINT8        enSuspendCause;
    pstLSuspendMsg = (LMM_MMC_SUSPEND_IND_STRU*)pstMsg;

    /* L模下，挂起原因定义与GU下不同，转换一下挂起原因定义 */
    NAS_MMC_ConvertLmmSysChngTypeToMmcType(pstLSuspendMsg->ulSysChngType, &enSuspendCause);

    /* 如果为参数不正确, 则不允许进行异系统重选 */
    if (MMC_SUSPEND_CAUSE_BUTT <= enSuspendCause)
    {
        NAS_MMC_SndLmmSuspendRsp(MMC_LMM_FAIL);
        return VOS_TRUE;
    }

    /* 根据不同的挂起原因值，启动不同的状态机 */
    switch (enSuspendCause)
    {
        /* 启动 小区重选 状态机 */
        case MMC_SUSPEND_CAUSE_CELLRESELECT:
        case MMC_SUSPEND_CAUSE_REDIRECTION:
            NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_INTER_SYS_CELLRESEL);
            NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,
                                     NAS_MML_GetSimPsRegStatus());
            break;

        /* 启动HANDOVER状态机 */
        case MMC_SUSPEND_CAUSE_HANDOVER:
            NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_INTER_SYS_HO);
            NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,
                                     NAS_MML_GetSimPsRegStatus());

            break;

        /* 启动 CCO状态机 */
        case MMC_SUSPEND_CAUSE_CELLCHANGE:
            NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_INTER_SYS_CCO);
            NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,
                                     NAS_MML_GetSimPsRegStatus());
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmSuspendInd_PlmnList_WaitEpsRegInd:Unexpected suspend type!");
            break;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmSysInfoInd_PlmnList_WaitEpsRegInd
 功能描述  : 在list搜网的等待EPS注册结果状态,收到ID_LMM_MMC_SYS_INFO_IND消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:ID_LMM_MMC_SYS_INFO_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月25日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2012年4月18日
    作    者   : l00130025
    修改内容   : DTS2012040200480,单独维护EPS注册状态,供查询和上报使用
  3.日    期   : 2012年4月28日
    作    者   : W00166186
    修改内容   : DTS2012042602593,MM没有保存当前驻留的PLMN，导致后续判断出错
  4.日    期   : 2012年5月8日
    作    者   : t00212959
    修改内容   : GUL BG项目调整
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
  9.日    期   : 2015年10月24日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmSysInfoInd_PlmnList_WaitEpsRegInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ProcLteSysInfo_PlmnList(pstMsg);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmAttachInd_PlmnList_WaitEpsRegInd
 功能描述  : 在list搜网的等待EPS注册结果状态,收到ID_LMM_MMC_ATTACH_IND消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:ID_LMM_MMC_ATTACH_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月3日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2012年5月14日
    作    者   : z00161729
    修改内容   : GUL背景搜修改
  3.日    期   : 2012年11月22日
    作    者   : t00212959
    修改内容   : DTS2012112006974
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmAttachInd_PlmnList_WaitEpsRegInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_ATTACH_IND_STRU                                *pstLmmAttachIndMsg = VOS_NULL_PTR;
    NAS_MML_LTE_UE_OPERATION_MODE_ENUM_UINT8                enUeOperationMode;

    enUeOperationMode   =  NAS_MML_GetLteUeOperationMode();
    pstLmmAttachIndMsg  = (LMM_MMC_ATTACH_IND_STRU*)pstMsg;

    NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_PS);

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
    NAS_MMC_ProcLmmAttachInd_PlmnList(pstLmmAttachIndMsg);

    if (NAS_MMC_WAIT_REG_RESULT_IND_NULL != NAS_MMC_GetWaitRegRsltFlag_PlmnList())
    {
        return VOS_TRUE;
    }

    /* 停止等待注册结果的保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

    if ( VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        if (VOS_TRUE == NAS_MMC_IsDisableLteNeedLocalReleaseEpsConn())
        {
            NAS_MMC_SndLmmRelReq();
        }

        /* 迁移状态到等待EPS的链路释放 */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_EPS_CONN_REL_IND);

        /* 启动保护定时器 */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND, TI_NAS_MMC_WAIT_EPS_CONN_REL_IND_LEN);

        return VOS_TRUE;
    }

    /* 根据当前的接入模式，发起LIST搜网请求,迁移状态，启动保护定时器 */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmTauResultInd_PlmnList_WaitEpsRegInd
 功能描述  : 在list搜网的等待EPS注册结果状态,收到ID_LMM_MMC_TAU_RESULT_IND消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:ID_LMM_MMC_TAU_RESULT_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月3日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2012年5月14日
    作    者   : z00161729
    修改内容   : GUL背景搜修改
  3.日    期   : 2012年11月22日
    作    者   : t00212959
    修改内容   : DTS2012112006974
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmTauResultInd_PlmnList_WaitEpsRegInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_TAU_RESULT_IND_STRU        *pstLmmTauIndMsg = VOS_NULL_PTR;

    pstLmmTauIndMsg = (LMM_MMC_TAU_RESULT_IND_STRU*)pstMsg;

    NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_PS);

    /* 向GMM和MM转发注册结果消息 */
    NAS_MMC_SndMmLmmTauResultInd(pstLmmTauIndMsg);
    NAS_MMC_SndGmmLmmTauResultInd(pstLmmTauIndMsg);

    /* 处理tau结果 */
    NAS_MMC_ProcLmmTauResultInd_PlmnList(pstLmmTauIndMsg);

    if (NAS_MMC_WAIT_REG_RESULT_IND_NULL != NAS_MMC_GetWaitRegRsltFlag_PlmnList())
    {
        return VOS_TRUE;
    }

    /* 停止等待注册结果的保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

    if ( VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        /*是SMS ONLY,disable LTE,在#18列表中，注册成功，向L发送释放请求*/
        if (VOS_TRUE == NAS_MMC_IsDisableLteNeedLocalReleaseEpsConn())
        {
            NAS_MMC_SndLmmRelReq();
        }

        /* 迁移状态到等待EPS的链路释放 */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_EPS_CONN_REL_IND);

        /* 启动保护定时器 */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND, TI_NAS_MMC_WAIT_EPS_CONN_REL_IND_LEN);

        return VOS_TRUE;
    }

    /* 根据当前的接入模式，发起LIST搜网请求,迁移状态，启动保护定时器 */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmMmcStatusInd_PlmnList_WaitEpsRegInd
 功能描述  : 在list搜网的等待EPS注册结果状态,收到ID_LMM_MMC_STATUS_IND消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:ID_LMM_MMC_STATUS_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月25日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2012年5月8日
    作    者   : t00212959
    修改内容   : GUL BG项目调整
  3.日    期   : 2015年9月26日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmMmcStatusInd_PlmnList_WaitEpsRegInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_STATUS_IND_STRU            *pstLmmStatusIndMsg = VOS_NULL_PTR;

    pstLmmStatusIndMsg = (LMM_MMC_STATUS_IND_STRU*)pstMsg;

    if ( VOS_FALSE == pstLmmStatusIndMsg->bitOpConnState)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmMmcStatusInd_PlmnList_WaitEpsRegInd:bitOpConnState IS VOS_FALSE");
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

            /* 停止保护定时器 */
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

            NAS_MMC_StartPeriodTryingUserListSrchTimer_PlmnList();

            /* 发送状态机失败退出的结果 */
            NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                VOS_FALSE,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

            /* 退出状态机 */
            NAS_MMC_FSM_QuitFsmL2();

            return VOS_TRUE;

        case MMC_LMM_CONN_IDLE:
            NAS_MML_SetEpsSigConnStatusFlg(VOS_FALSE);
            NAS_MML_SetEpsServiceConnStatusFlg(VOS_FALSE);
            break;

        default:

            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmMmcStatusInd_PlmnList_WaitEpsRegInd:Unexpected connection status!");

            break;
    }

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmAreaLostInd_PlmnList_WaitEpsRegInd
 功能描述  : 在list搜网的等待EPS注册结果状态,收到ID_LMM_MMC_AREA_LOST_IND消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:ID_LMM_MMC_AREA_LOST_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月25日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2012年5月8日
    作    者   : t00212959
    修改内容   : GUL BG项目调整
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmAreaLostInd_PlmnList_WaitEpsRegInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止等待注册结果消息的定时器  */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

    /* 清除驻留状态 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* 当前信号更新 */
    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());

    /* 更新服务状态 上报无服务*/
    NAS_MMC_SetCsServiceStatus(NAS_MMC_NO_SERVICE);
    NAS_MMC_SetPsServiceStatus(NAS_MMC_NO_SERVICE);

    /* 向接入层发送LIST搜网请求,迁移状态到等待 LIST搜网回复状态,启动保护定时器 */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

    /* 向GMM发送搜网指示 */
    NAS_MMC_SndGmmPlmnSchInit();

    /* 向MM发送搜网指示 */
    NAS_MMC_SndMmPlmnSchInit();

    /* 设置进入搜网状态 */
    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmAreaLostInd_PlmnList_WaitLmmPlmnSearchCnf
 功能描述  : 在list搜网的等待LMM的搜网回复结果状态,收到ID_LMM_MMC_AREA_LOST_IND消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:ID_LMM_MMC_AREA_LOST_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月4日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmAreaLostInd_PlmnList_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 清除驻留状态 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* 当前信号更新 */
    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());

    /* 更新服务状态 上报无服务*/
    NAS_MMC_SetCsServiceStatus(NAS_MMC_NO_SERVICE);
    NAS_MMC_SetPsServiceStatus(NAS_MMC_NO_SERVICE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmSysInfoInd_PlmnList_WaitLmmPlmnSearchCnf
 功能描述  : 在list搜网的等待LMM搜网结果状态,收到ID_LMM_MMC_SYS_INFO_IND消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:ID_LMM_MMC_SYS_INFO_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月6日
    作    者   : z00161729
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
  5.日    期   : 2015年02月11日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseII 项目修改
                 方案优化后，LTE下的小区发生变化，LMM会通过系统消息通知MMC
  6.日    期   : 2015年10月24日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmSysInfoInd_PlmnList_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ProcLteSysInfo_PlmnList(pstMsg);

    return VOS_TRUE;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmAttachInd_PlmnList_WaitLmmPlmnSearchCnf
 功能描述  : 在list搜网的等待EPS链路释放状态,收到ID_LMM_MMC_ATTACH_IND消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:ID_LMM_MMC_ATTACH_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月22日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmAttachInd_PlmnList_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_ATTACH_IND_STRU                                *pstLmmAttachIndMsg = VOS_NULL_PTR;

    pstLmmAttachIndMsg  = (LMM_MMC_ATTACH_IND_STRU*)pstMsg;

    /* 向GMM和MM转发注册结果消息 */
    NAS_MMC_SndMmLmmAttachInd(pstLmmAttachIndMsg);
    NAS_MMC_SndGmmLmmAttachInd(pstLmmAttachIndMsg);

    /* 处理attach结果 */
    NAS_MMC_ProcLmmAttachInd_PlmnList(pstLmmAttachIndMsg);

    /* L下注册完成后，IMS时支持时会发起IMS注册,需要根据IMS注册的情况决定是否需要
       disable L模,此时需要进一步等待IMS的注册结果 */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList();

#if (FEATURE_ON == FEATURE_IMS)
    NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_IMS);
#endif

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmTauResultInd_PlmnList_WaitLmmPlmnSearchCnf
 功能描述  : 在list搜网的等待EPS链路释放状态,收到ID_LMM_MMC_TAU_RESULT_IND消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:ID_LMM_MMC_TAU_RESULT_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月22日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmTauResultInd_PlmnList_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_TAU_RESULT_IND_STRU        *pstLmmTauIndMsg;

    pstLmmTauIndMsg  = (LMM_MMC_TAU_RESULT_IND_STRU*)pstMsg;

    /* 向GMM和MM转发注册结果消息 */
    NAS_MMC_SndMmLmmTauResultInd(pstLmmTauIndMsg);
    NAS_MMC_SndGmmLmmTauResultInd(pstLmmTauIndMsg);

    /* 处理tau结果 */
    NAS_MMC_ProcLmmTauResultInd_PlmnList(pstLmmTauIndMsg);

    /* L下注册完成后，IMS时支持时会发起IMS注册,需要根据IMS注册的情况决定是否需要
       disable L模,此时需要进一步等待IMS的注册结果 */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList();

#if (FEATURE_ON == FEATURE_IMS)
    NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_IMS);
#endif

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMsccImsVoiceCapInd_PlmnList_WaitLmmPlmnSearchCnf
 功能描述  : 处理MSCC的IMS VOICE是否可用消息
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
             VOS_FALSE:处理未完成
 调用函数  :
 被调函数  :

 修改历史      :
1.日    期   : 2015年7月22日
  作    者   : s00217060
  修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMsccImsVoiceCapInd_PlmnList_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMC_IMS_VOICE_CAP_NOTIFY_STRU *pstImsVoiceInd = VOS_NULL_PTR;
    VOS_UINT8                           ucWaitRegRsltFlag;

    ucWaitRegRsltFlag   = NAS_MMC_GetWaitRegRsltFlag_PlmnList();
    pstImsVoiceInd      = (MSCC_MMC_IMS_VOICE_CAP_NOTIFY_STRU *)pstMsg;

    /* 如果在等待IMS的注册结果才处理 */
    if (NAS_MMC_WAIT_REG_RESULT_IND_IMS != (ucWaitRegRsltFlag & NAS_MMC_WAIT_REG_RESULT_IND_IMS))
    {
        return VOS_TRUE;
    }

    NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_IMS);

    /* IMS不可用时判断是否需要disable LTE */
    if (VOS_FALSE  == pstImsVoiceInd->ucAvail)
    {
        if (VOS_TRUE == NAS_MMC_IsNeedDisableLte_ImsVoiceNotAvail())
        {
            NAS_MMC_SetCsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION);

            NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS);

            NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE);
        }
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcMmcSuspendRslt_PlmnList_WaitEpsRegInd
 功能描述  : 在list搜网的等待EPS注册结果状态,收到MMCMMC_SUSPEND_RSLT_CNF消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:MMCMMC_SUSPEND_RSLT_CNF消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月25日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2012年5月8日
    作    者   : t00212959
    修改内容   : GUL BG项目调整
  3.日    期   : 2013年4月4日
    作    者   : y00176023
    修改内容   : DSDS GUNAS II项目:收到NO RF 退状态机，迁移到OOC状态
  4.日    期   : 2015年9月25日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcMmcSuspendRslt_PlmnList_WaitEpsRegInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 重选后当前接入技术已经改变，需要重新初始化搜网的接入技术优先级 */
 #if (FEATURE_ON == FEATURE_CSG)
    if (VOS_TRUE == NAS_MMC_IsCsgList_PlmnList())
    {
        NAS_MMC_InitCsgListSearchRatInfo_PlmnList();
    }
    else
 #endif
    {
        NAS_MMC_InitSearchRatInfo_PlmnList();
    }

    NAS_MMC_NotifyModeChange(NAS_MML_GetCurrNetRatType(),
                             NAS_MML_GetSimPsRegStatus());

    if (VOS_FALSE == NAS_MML_GetRfAvailFlg())
    {
        /* 停止保护定时器 */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

        NAS_MMC_SndMsccPlmnListRejMsg_PlmnList();

        /* 由于未进行LIST搜网，搜索到的网络列表为空 */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                VOS_FALSE,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* 退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 判断当前接入模式 */
    if ( NAS_MML_NET_RAT_TYPE_LTE != NAS_MML_GetCurrNetRatType())
    {
        /* 停止保护定时器 */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

        /* 更新CSPS的AdditionalAction */
        NAS_MMC_SetCsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_BUTT);
        NAS_MMC_SetPsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_BUTT);

        NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList();
        NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_CS);
        NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_PS);

        /* 迁移到等待注册结果状态 */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_CSPS_REG_IND);

        /* 启动保护定时器 */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND, TI_NAS_MMC_WAIT_CSPS_REG_IND_LEN);

        return VOS_TRUE;
    }

    /* 继续等待注册结果 */
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitEpsRegIndExpired_PlmnList_WaitEpsRegInd
 功能描述  : 在list搜网的等待EPS注册结果状态,收到TI_NAS_MMC_WAIT_EPS_REG_IND消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:TI_NAS_MMC_WAIT_EPS_REG_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月25日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2012年5月8日
    作    者   : t00212959
    修改内容   : GUL BG项目调整
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiWaitEpsRegIndExpired_PlmnList_WaitEpsRegInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitEpsRegIndExpired_PlmnList_WaitEpsRegInd Enter");

    /* 清除等待注册结果标记 */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList();

    /* 存在信令链接 继续等待EPS链接释放 */
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        /* 迁移状态到等待EPS链路释放 */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_EPS_CONN_REL_IND);

        /* 启动保护定时器 */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND, TI_NAS_MMC_WAIT_EPS_CONN_REL_IND_LEN);

        return VOS_TRUE;
    }

    /* 根据当前的接入模式，发起LIST搜网请求,迁移状态，启动保护定时器 */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

    return VOS_TRUE;

}


/* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-7, begin */
/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMsccImsVoiceCapInd_PlmnList_WaitEpsRegInd
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
VOS_UINT32 NAS_MMC_RcvMsccImsVoiceCapInd_PlmnList_WaitEpsRegInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMC_IMS_VOICE_CAP_NOTIFY_STRU     *pstImsVoiceInd = VOS_NULL_PTR;
    VOS_UINT8                           ucWaitRegRsltFlag;

    ucWaitRegRsltFlag   = NAS_MMC_GetWaitRegRsltFlag_PlmnList();
    pstImsVoiceInd      = (MSCC_MMC_IMS_VOICE_CAP_NOTIFY_STRU *)pstMsg;

    /* 如果在等待PS的注册结果则继续等待PS注册结果 */
    if (NAS_MMC_WAIT_REG_RESULT_IND_PS == (ucWaitRegRsltFlag & NAS_MMC_WAIT_REG_RESULT_IND_PS))
    {
        return VOS_TRUE;
    }

    /* 清除等待注册结果标记 */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList();

    /* IMS不可用时判断是否需要disable LTE */
    if (VOS_FALSE  == pstImsVoiceInd->ucAvail)
    {
        if (VOS_TRUE == NAS_MMC_IsNeedDisableLte_ImsVoiceNotAvail())
        {
            NAS_MMC_SetCsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION);

            NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS);

            NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE);
        }
    }

    /* 停止等待注册结果的保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        if (VOS_TRUE == NAS_MMC_IsDisableLteNeedLocalReleaseEpsConn())
        {
            NAS_MMC_SndLmmRelReq();
        }

        /* 迁移状态到等待EPS的链路释放 */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_EPS_CONN_REL_IND);

        /* 启动保护定时器 */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND, TI_NAS_MMC_WAIT_EPS_CONN_REL_IND_LEN);

        return VOS_TRUE;
    }

    /* 根据当前的接入模式，发起LIST搜网请求,迁移状态，启动保护定时器 */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

    return VOS_TRUE;
}

/* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-7, end */


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitLmmPlmnSearchCnf
 功能描述  : 在list搜网的等待LMM的搜网回复时,收到MMCMMC_ABORT_FSM_REQ消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:MMCMMC_ABORT_FSM_REQ消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月30日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止等待LMM搜网结果的保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_LIST_CNF);

    /* 记录状态机退出标记 */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* 向LMM发送停止搜网请求,迁移状态,启动保护定时器 */
    NAS_MMC_SndSpecRatPlmnSearchStopReq_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcTafPlmnListAbortReq_PlmnList_WaitLmmPlmnSearchCnf
 功能描述  : 在list搜网的等待LMM的搜网回复时,收到ID_MSCC_MMC_PLMN_LIST_ABORT_REQ消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:ID_MSCC_MMC_PLMN_LIST_ABORT_REQ消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月01日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcTafPlmnListAbortReq_PlmnList_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止等待LMM搜网结果的保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_LIST_CNF);

    /* 记录状态机退出标记 */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* 设置通知MSCC回复标记 */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_TRUE);

    /* 向LMM发送停止搜网请求,迁移状态,启动保护定时器 */
    NAS_MMC_SndSpecRatPlmnSearchStopReq_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmPlmnSrchCnf_PlmnList_WaitLmmPlmnSearchCnf
 功能描述  : 栽趌ist搜网的等待LMM的搜网回复时,收到ID_LMM_MMC_PLMN_SRCH_CNF消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:ID_LMM_MMC_PLMN_SRCH_CNF消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月01日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmPlmnSrchCnf_PlmnList_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_PLMN_SRCH_CNF_STRU         *pstLmmPlmnSrchcnf = VOS_NULL_PTR;

    pstLmmPlmnSrchcnf = (LMM_MMC_PLMN_SRCH_CNF_STRU*)pstMsg;

    /* 判断LIST搜网结果 */
    NAS_MMC_ProcLmmSearchCnf_PlmnList(pstLmmPlmnSrchcnf);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitLmmPlmnListCnfExpired_PlmnList_WaitLmmPlmnSearchCnf
 功能描述  : 在list搜网的等待LMM的搜网回复时,收到TI_NAS_MMC_WAIT_LMM_PLMN_LIST_CNF消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:TI_NAS_MMC_WAIT_LMM_PLMN_LIST_CNF消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月01日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2011年09月21日
    作    者   : W00166186
    修改内容   : V7R1 PHASE II
   3.日    期   : 2012年4月27日
    作    者   : t00212959
    修改内容   : GUL BG项目调整
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiWaitLmmPlmnListCnfExpired_PlmnList_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* LIST搜网过程中，接入层可能上报RRMM_NOT_CAMP_ON，此时需要根据当前驻留状态更新RAT的搜索标记 */
    if (NAS_MMC_AS_CELL_CAMP_ON == NAS_MMC_GetAsCellCampOn())
    {
        /* 更新三模RAT的搜索标记 */
        NAS_MMC_SetSearchedFlag_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

        NAS_MMC_SetSearchedFlag_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);

        NAS_MMC_SetSearchedFlag_PlmnList(NAS_MML_NET_RAT_TYPE_GSM);
    }
    else
    {
        /* 更新当前RAT的搜索标记 */
        NAS_MMC_SetSearchedFlag_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);
    }

    /* 向LMM发送停止搜网请求,迁移状态,启动保护定时器 */
    NAS_MMC_SndSpecRatPlmnSearchStopReq_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitLmmSuspendCnf
 功能描述  : 在list搜网的等待LMM的挂起回复时,收到MMCMMC_ABORT_FSM_REQ消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:MMCMMC_ABORT_FSM_REQ消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月30日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitLmmSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 记录需要终止当前状态机标志 */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTafPlmnListAbortFsmMsg_PlmnList_WaitLmmSuspendCnf
 功能描述  : 在list搜网的等待LMM的挂起回复时,收到ID_MSCC_MMC_PLMN_LIST_ABORT_REQ消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:ID_MSCC_MMC_PLMN_LIST_ABORT_REQ消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月01日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTafPlmnListAbortFsmMsg_PlmnList_WaitLmmSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 记录需要终止当前状态机标志 */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* 设置通知MSCC回复标记 */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmSuspendCnf_PlmnList_WaitLmmSuspendCnf
 功能描述  : 在list搜网的等待LMM的挂起回复时,收到ID_LMM_MMC_SUSPEND_CNF消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:ID_LMM_MMC_SUSPEND_CNF消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月01日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2011年09月21日
    作    者   : W00166186
    修改内容   : V7R1 PHASE II

  3.日    期   : 2011年12月15日
    作    者   : w00167002
    修改内容   : DTS2011120702166:MMC复位后无复位信息,在MML模块封装复位信息，
                  以供MM层调用，进行软复位。
  4.日    期   : 2012年10月7日
    作    者   : s46746
    修改内容   : for V7R1C50_At_Abort，非驻留列表搜索过程中，发起用户列表搜索，之后打断用户列表搜索，
                 后续没有再次出发搜索

  5.日    期   : 2015年3月11日
    作    者   : wx270776
    修改内容   : DTS2015011212939:增加复位场景
  6.日    期   : 2015年11月04日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmSuspendCnf_PlmnList_WaitLmmSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_SUSPEND_CNF_STRU           *pstLmmSuspendCnf = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat;

    VOS_UINT32                          ulNeedPlmnSearch;

    pstLmmSuspendCnf  = (LMM_MMC_SUSPEND_CNF_STRU*)pstMsg;

    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_SUSPEND_CNF);

    if ( MMC_LMM_FAIL  == pstLmmSuspendCnf->ulRst )
    {
        /* 单板复位 */
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_LMM_SUSPEND_FAILURE);

        return VOS_TRUE;
    }

    /* 判断状态机退出标记是否为真，如果为真*/
    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnList())
    {
        /* 接入技术设置为BUTT，后续可以直接向任意模发送搜网请求 */
        NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

        ulNeedPlmnSearch = VOS_FALSE;

        /*通知MSCC回复标记为真*/
        if ( VOS_TRUE == NAS_MMC_GetNotifyMsccFlag_PlmnList())
        {
            if (VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
            {
                /* 向MSCC回复ID_MMC_MSCC_PLMN_LIST_ABORT_CNF */
                NAS_MMC_SndMsccPlmnListAbortCnf_PlmnList();
            }

            ulNeedPlmnSearch = VOS_TRUE;
        }
        else
        {
            if (VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
            {
                /* 向MSCC回复LIST搜网结果 */
                NAS_MMC_SndMsccPlmnListCnf_PlmnList();
            }
        }

        /* 发送状态机ABORT的退出结果 */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                                (VOS_UINT8)ulNeedPlmnSearch,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 获取不到下一个接入技术 */
    if ( VOS_FALSE == NAS_MMC_GetNextSearchingRat_PlmnList(&enRat))
    {
        /* 异常打印 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcRrmmSuspendCnf_PlmnList: Get next search rat fail.");

        /* 接入技术设置为BUTT，后续可以直接向任意模发送搜网请求 */
        NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

        /* 上报LIST搜网结果 */
        NAS_MMC_SndMsccListSearchCnfMsg_PlmnList();

        /* 发送状态机退出结果 */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                          (VOS_UINT8)NAS_MMC_IsNeedPlmnSearch_PlmnList(),
                          NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                          NAS_MMC_GetRegRsltInfo_PlmnList());

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 根据获取的接入技术设置当前接入技术 */
    NAS_MML_SetCurrNetRatType(enRat);

    /* 向下个接入模式发送LIST搜网请求,迁移状态,启动保护定时器 */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(enRat);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitLmmSuspendCnfExpired_PlmnList_WaitLmmSuspendCnf
 功能描述  : 在list搜网的等待LMM的挂起回复时,收到TI_NAS_MMC_WAIT_LMM_SUSPEND_CNF消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:TI_NAS_MMC_WAIT_LMM_SUSPEND_CNF消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月01日
    作    者   : w00176964
    修改内容   : 新生成函数

  2.日    期   : 2011年12月15日
    作    者   : w00167002
    修改内容   : DTS2011120702166:MMC复位后无复位信息,在MML模块封装复位信息，
                  以供MM层调用，进行软复位。

  3.日    期   : 2015年3月11日
    作    者   : wx270776
    修改内容   : DTS2015011212939:增加复位场景
* ****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiWaitLmmSuspendCnfExpired_PlmnList_WaitLmmSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitLmmSuspendCnfExpired_PlmnList_WaitLmmSuspendCnf: Timer Expired");

    /* 不可恢复故障，复位 */
    NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_LMM_SUSPEND_CNF_EXPIRED);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmPlmnSrchStopCnf_PlmnList_WaitLmmPlmnSearchStopCnf
 功能描述  : 在list搜网的等待LMM的停止搜网回复时,收到ID_LMM_MMC_STOP_PLMN_SRCH_CNF消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:ID_LMM_MMC_STOP_PLMN_SRCH_CNF消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月01日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2011年09月21日
    作    者   : W00166186
    修改内容   : V7R1 PHASE II

  3.日    期   : 2012年9月27日
    作    者   : z40661
    修改内容   : DTS2012083102377,定时器ID填写出错
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmPlmnSrchStopCnf_PlmnList_WaitLmmPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF);


    /* 处理搜网停止回复结果 */
    NAS_MMC_ProcLmmPlmnSearchStopCnf_PlmnList();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitLmmPlmnSearchStopCnf
 功能描述  : 在list搜网的等待LMM的停止搜网回复时,收到MMCMMC_ABORT_FSM_REQ消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:MMCMMC_ABORT_FSM_REQ消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月30日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitLmmPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 置ABORT标志位 */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTafPlmnListAbortFsmMsg_PlmnList_WaitLmmPlmnSearchStopCnf
 功能描述  : 在list搜网的等待LMM的停止搜网回复时,收到ID_MSCC_MMC_PLMN_LIST_ABORT_REQ消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:ID_MSCC_MMC_PLMN_LIST_ABORT_REQ消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月01日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2011年09月21日
    作    者   : W00166186
    修改内容   : V7R1 PHASE II
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTafPlmnListAbortFsmMsg_PlmnList_WaitLmmPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 置ABORT标志位 */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* 设置通知MSCC结果的标记 */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmPlmnSrchCnf_PlmnList_WaitLmmPlmnSearchStopCnf
 功能描述  : 在list搜网的等待LMM的停止搜网回复时,收到ID_MSCC_MMC_PLMN_LIST_ABORT_REQ消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:ID_LMM_MMC_PLMN_SRCH_CNF消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月28日
    作    者   : t00212959
    修改内容   : 新生成函数
  2.日    期   : 2012年5月28日
    作    者   : z00161729
    修改内容   : V7R1C50 GUL背景搜修改
  3.日    期   : 2012年6月25日
    作    者   : z00161729
    修改内容   : V7R1C50 DTS2012062105468:MMC的stop plmn cnf和L的search cnf对冲，MMC增加保护认为收到L
                 的stop plmn cnf，退出状态机
  4.日    期   : 2012年9月27日
    作    者   : z40661
    修改内容   : DTS2012083102377,定时器ID填写出错
  5.日    期   : 2014年7月9日
    作    者   : w00176964
    修改内容   : DSDS III项目:LIST搜网对冲收到NO RF的处理
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmPlmnSrchCnf_PlmnList_WaitLmmPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_PLMN_SRCH_CNF_STRU         *pstLmmPlmnSrchCnf = VOS_NULL_PTR;
    RRC_PLMN_ID_LIST_STRU              *pstGuPlmnIdList;
    VOS_UINT32                          ulIndex;


    pstLmmPlmnSrchCnf = (LMM_MMC_PLMN_SRCH_CNF_STRU*)pstMsg;
    pstGuPlmnIdList   = (RRC_PLMN_ID_LIST_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                   sizeof(RRC_PLMN_ID_LIST_STRU));

    if (VOS_NULL_PTR == pstGuPlmnIdList)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmPlmnSrchCnf_PlmnList_WaitLmmPlmnSearchStopCnf:ERROR: Memory Alloc Error");
        return VOS_TRUE;
    }

    /* LIST搜网回复与停止搜网对冲,NO RF时直接退出LIST搜网流程 */
    if (MMC_LMM_PLMN_SRCH_RLT_LIST_NO_RF == pstLmmPlmnSrchCnf->enRlst)
    {
        /* 停止保护定时器 */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF);

        PS_MEM_FREE(WUEPS_PID_MMC, pstGuPlmnIdList);
        NAS_MMC_ProcNoRf_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

        return VOS_TRUE;
    }

    /*只有在搜索成功时才进行处理 */
    if (MMC_LMM_PLMN_SRCH_RLT_LIST_SUCC != pstLmmPlmnSrchCnf->enRlst)
    {
        PS_MEM_FREE(WUEPS_PID_MMC, pstGuPlmnIdList);
        return VOS_TRUE;
    }

    /* 更新的RAT搜索标记 */
    for ( ulIndex = 0; ulIndex < MMC_LMM_MAX_RAT_NUM; ulIndex++)
    {
        if ( MMC_LMM_RAT_LIST_SEARCH_CMPL == pstLmmPlmnSrchCnf->astSearchRatInfo[ulIndex].enListSearchRlt)
        {
            NAS_MMC_SetSearchedFlag_PlmnList((MMC_LMM_RAT_TYPE_ENUM_UINT8)(pstLmmPlmnSrchCnf->astSearchRatInfo[ulIndex].enRat));
        }
    }

    /*转换L格式的搜索列表成为GU格式的*/
    NAS_MMC_ConvertLmmPlmnIdListToGUFormat(&(pstLmmPlmnSrchCnf->stPlmnIdList), pstGuPlmnIdList);

    /*保存搜索列表*/
    NAS_MMC_UpdateSearchedPlmnListInfo_PlmnList(pstGuPlmnIdList);

    PS_MEM_FREE(WUEPS_PID_MMC, pstGuPlmnIdList);


    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF);


    /* 处理搜网停止回复结果 */
    NAS_MMC_ProcLmmPlmnSearchStopCnf_PlmnList();

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitLmmStopCnfExpired_PlmnList_WaitLmmPlmnSearchStopCnf
 功能描述  : 在list搜网的等待LMM的停止搜网回复时,收到TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月01日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2011年09月21日
    作    者   : W00166186
    修改内容   : V7R1 PHASE II
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiWaitLmmStopCnfExpired_PlmnList_WaitLmmPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitLmmStopCnfExpired_PlmnList_WaitLmmPlmnSearchStopCnf: Timer Expired");

    /* 处理搜网停止回复结果 */
    NAS_MMC_ProcLmmPlmnSearchStopCnf_PlmnList();

    return VOS_TRUE;
}


#endif

/*********************************************************************************/
/*************************PLMN LIST公共函数***************************************/
/*********************************************************************************/
/*****************************************************************************
 函 数 名  : NAS_MMC_IsUserPlmnList_PlmnList
 功能描述  : 判断当前是否是用户LIST搜网
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  用户LIST搜网
             VOS_FALSE 内部LIST搜网
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月01日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_IsUserPlmnList_PlmnList(VOS_VOID)
{
    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg    = VOS_NULL_PTR;

   /* 根据FSM ID获取该FSM 入口消息 */
    pstEntryMsg     = NAS_MMC_GetCurrFsmMsgAddr();

    if ( (ID_MSCC_MMC_PLMN_LIST_REQ == NAS_ExtractMsgNameFromEvtType(pstEntryMsg->ulEventType))
      || (TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST == NAS_ExtractMsgNameFromEvtType(pstEntryMsg->ulEventType)))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcFsmAbort_PlmnList
 功能描述  : list搜网中内部abort的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月26日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_VOID NAS_MMC_ProcFsmAbort_PlmnList(VOS_VOID)
{
    /* 需要向MSCC回复结果 */
    if ( VOS_TRUE == NAS_MMC_GetNotifyMsccFlag_PlmnList())
    {
        if (VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
        {
            NAS_MMC_SndMsccPlmnListAbortCnf_PlmnList();
            return;
        }

#if (FEATURE_ON == FEATURE_CSG)
        if (VOS_TRUE == NAS_MMC_IsCsgList_PlmnList())
        {
            NAS_MMC_SndMsccCsgListAbortCnf_PlmnList();
        }
#endif
    }
    else
    {
        NAS_MMC_SndMsccListSearchCnfMsg_PlmnList();
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndMsccListSearchCnfMsg_PlmnList
 功能描述  : 向MSCC发送LIST搜网结果消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月26日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccListSearchCnfMsg_PlmnList(VOS_VOID)
{
    if (VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
    {
        /* 发送普通LIST搜网结果 */
        NAS_MMC_SndMsccPlmnListCnf_PlmnList();
        return;
    }

#if (FEATURE_ON == FEATURE_CSG)
    if (VOS_TRUE == NAS_MMC_IsCsgList_PlmnList())
    {
        /* 发送CSG LIST搜网结果 */
        NAS_MMC_SndMsccCsgListSearchCnf_PlmnList();
    }
#endif

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_StartPeriodTryingUserListSrchTimer_PlmnList
 功能描述  : 启动周期性尝试list搜网定时器
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月26日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_VOID NAS_MMC_StartPeriodTryingUserListSrchTimer_PlmnList(VOS_VOID)
{

    if (VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
    {
        /* 启动5S周期性尝试LIST搜网定时器 */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST, TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST_LEN);
        return;
    }


#if (FEATURE_ON == FEATURE_CSG)
    if (VOS_TRUE == NAS_MMC_IsCsgList_PlmnList())
    {
        /* 启动5S周期性尝试CSG LIST搜网定时器 */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH, TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH_LEN);
    }
#endif

    return;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_SndMsccPlmnListRejMsg_PlmnList
 功能描述  : 向MSCC发送LIST rej消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月26日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccPlmnListRejMsg_PlmnList(VOS_VOID)
{
    if (VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
    {
        /* 发送LIST REJ给MSCC */
        NAS_Mmc_SndMsccPlmnListRej();
        return;
    }

#if (FEATURE_ON == FEATURE_CSG)
    if (VOS_TRUE == NAS_MMC_IsCsgList_PlmnList())
    {
        /* 发送CSG LIST REJ给MSCC */
        NAS_MMC_SndMsccCsgListSearchRej();
    }
#endif
    return;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedAnyCellSrch_PlmnList
 功能描述  : 判断当前是否需要anycell搜网
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  需要anycell搜网
             VOS_FALSE 不需要anycel搜网
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月31日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_IsNeedAnyCellSrch_PlmnList(VOS_VOID)
{
    /* 卡无效的情况需要判断在L1是否已经进行过anycell搜网
       如果已经进行过anycell搜网则LIST搜网退出不需要重复
       进行anycell搜网;否则LIST搜退出后需要进行一轮anycell
       搜网 */
    if (VOS_FALSE == NAS_MML_IsUsimStausValid())
    {
        /* RRC连接存在说明未进行搜网在LIST搜网状态机里等待RRC连接释放
           RRC连接不存在且进入搜网状态说明已经进行过搜网但未完成 */
        if (VOS_TRUE == NAS_MML_IsRrcConnExist())
        {
            return VOS_TRUE;
        }

        if(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == NAS_MMC_GetSpecPlmnSearchState())
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcCsRegRslt_PlmnList
 功能描述  : 处理CS的注册结果
 输入参数  : pstCsRegRsltInd  CS注册结果消息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月20日
    作    者   : w00176964
    修改内容   : 新生成函数

  2.日    期   : 2011年11月28日
    作    者   : w00167002
    修改内容   : DTS2011112406707:若当前为假流程且当前的AdditionalAction不为
                初始无效值，则不更新当前的AdditionalAction的值，否则若当前为
                真流程或当前为假流程且AdditionalAction为初始无效值，则更新
                当前的AdditionalAction的值.
                修改原因:在ROAMING BROKER时候，设置1次失败,注册失败1次后，
                MMC需要搜网，但是MMC可能要等两个域的结果(如在选网状态机)，
                当收到系统消息的时候，假流程会更改MMC的AdditionalAction的值,
                导致ROMING BROKER特性失效。
   3.日    期   : 2011年12月5日
     作    者   : z00161729
     修改内容   : V7R1 Phase IV调整,当前SYSCFG中L不在时，也需要向LMM通知ID_MMC_LMM_ACTION_RESULT_REQ
   4.日    期   : 2011年12月20日
     作    者   : w00176964
     修改内容   : V7R1 PhaseIV 调整:UT修改NAS_MMC_SetUserSpecPlmnRegisterStatus
                 只在搜网状态机和ON PLMN下进行设置
  5.日    期   : 2012年1月3日
    作    者   : w00167002
    修改内容   : DTS2011122006209:g下PS ONLY注册成功_更改为CS后注册失败4次后未发起搜网
                  统一调整注册ADDITIONAL ACTION的值，若是用户自定义的原因值(>=256)，则
                  不保存注册结果。若当前支持L模，则注册原因值小于260时通知LMM.
                  调整假流程，MMC不需要知道MM/GMM上报的是否是真假流程。
  6.日    期   : 2012年1月20日
    作    者   : w00167002
    修改内容   : DTS2011122006209:将注册失败的消息通知给处理注册结果函数，
                  能进行更好的扩展.
  7.日    期   : 2012年3月1日
    作    者   : w00176964
    修改内容   : DTS2012022407450:联合ATTACH时,MM不能通知LMM此时CS的注册结果，否则导致TAU的类型不正确
  8.日    期   : 2012年6月4日
    作    者   : l00171473
    修改内容   : DTS2012053003921, 用户手动指定网络的注册状态标志清理
  9.日    期   : 2012年08月20日
    作    者   : l65478
    修改内容   : DTS2012081703289，手动搜网失败后关机，重新开机注册成功
                   后出服务区后不驻留EPLMN上
 10.日    期   : 2012年12月6日
    作    者   : s00217060
    修改内容   : DTS2012120410842:注册成功时，需要删除ForbPlmn,ForbLa,ForbGprs等信息
 11.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
 12.日    期   : 2013年12月24日
    作    者   : z00161729
    修改内容   : SVLTE支持NCELL搜网
 13.日    期   : 2014年01月10日
    作    者   : w00176964
    修改内容   : VoLTE_PhaseIII项目
 14.日    期   : 2014年05月4日
    作    者   : w00176964
    修改内容   : V3R3C60_eCall项目调整
 15.日    期   : 2014年11月3日
    作    者   : z00161729
    修改内容   : 开机漫游搜网项目修改
*****************************************************************************/
VOS_VOID NAS_MMC_ProcCsRegRslt_PlmnList(
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
            NAS_MMC_UpdateDPlmnNPlmnList(NAS_MML_GetCurrCampLai(), NAS_MMC_REG_DOMAIN_CS, NAS_MMC_MAX_CFG_DPLMN_NUM, &pstDPlmnNPlmnCfgInfo->usDplmnListNum, pstDPlmnNPlmnCfgInfo->astDPlmnList);
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

        /* Added by w00176964 for V3R3C60_eCall项目, 2014-5-4, begin */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_NORMAL_SERVICE);
        /* Added by w00176964 for V3R3C60_eCall项目, 2014-5-4, end */

#if   (FEATURE_ON == FEATURE_LTE)

        /* 当前SYSCFG中L不在时，需要向LMM通知 */
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
        enAdditionalAction = NAS_MMC_ProcCsRegFail(MM_MMC_CS_REG_RESULT_IND,
                                                   pstCsRegRsltInd);

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
        NAS_MMC_SetCsRegAdditionalAction_PlmnList(enAdditionalAction);
    }

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
 函 数 名  : NAS_MMC_ProcPsRegRslt_PlmnList
 功能描述  : 对Ps注册结果的处理
 输入参数  : pstPsRegRsltInd PS注册结果消息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月20日
    作    者   : w00176964
    修改内容   : 新生成函数

  2.日    期   : 2011年11月28日
    作    者   : w00167002
    修改内容   : DTS2011112406707:若当前为假流程且当前的AdditionalAction不为
                初始无效值，则不更新当前的AdditionalAction的值，否则若当前为
                真流程或当前为假流程且AdditionalAction为初始无效值，则更新
                当前的AdditionalAction的值.
                修改原因:在ROAMING BROKER时候，设置1次失败,注册失败1次后，
                MMC需要搜网，但是MMC可能要等两个域的结果(如在选网状态机)，
                当收到系统消息的时候，假流程会更改MMC的AdditionalAction的值,
                导致ROMING BROKER特性失效。
  3.日    期   : 2011年12月5日
    作    者   : z00161729
    修改内容   : V7R1 Phase IV调整,当前SYSCFG中L不在时，也需要向LMM通知ID_MMC_LMM_ACTION_RESULT_REQ
  4.日    期   : 2011年12月20日
    作    者   : w00176964
    修改内容   : V7R1 PhaseIV 调整:UT修改NAS_MMC_SetUserSpecPlmnRegisterStatus
                 只在搜网状态机和ON PLMN下进行设置
  5.日    期   : 2012年1月3日
    作    者   : w00167002
    修改内容   : DTS2011122006209:g下PS ONLY注册成功_更改为CS后注册失败4次后未发起搜网
                统一调整注册ADDITIONAL ACTION的值，若是用户自定义的原因值(>=256)，则
                不保存注册结果。若当前支持L模，则注册原因值小于260时通知LMM当前的注册结果.
                调整假流程，MMC不需要知道MM/GMM上报的是否是真假流程。
  6.日    期   : 2012年3月1日
    作    者   : w00176964
    修改内容   : DTS2012022407450:增加GMM的联合RAU/ATTACH类型，MMC转发给LMM
  7.日    期   : 2012年03月30日
    作    者   : l00130025
    修改内容   : DTS2012032307791,发给LMM注册结果,CombineReg时需要区分结果域
  8.日    期   : 2012年6月4日
    作    者   : l00171473
    修改内容   : DTS2012053003921, 用户手动指定网络的注册状态标志清理
  9.日    期   : 2012年6月8日
    作    者   : l00130025
    修改内容   : DTS2012060702423:Anycell驻留后，注册成功时，没有通知通知APS/CDS消息，无法数传
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
 15.日    期   : 2014年05月4日
    作    者   : w00176964
    修改内容   : V3R3C60_eCall项目调整
*****************************************************************************/
VOS_VOID NAS_MMC_ProcPsRegRslt_PlmnList(
    GMMMMC_PS_REG_RESULT_IND_STRU      *pstPsRegRsltInd
)
{
    NAS_MML_LAI_STRU                                       *pstLai         = VOS_NULL_PTR;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;

    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_GU_ACTION_RSLT_INFO_STRU                        stActionRslt;
    NAS_MML_PROC_TYPE_ENUM_U32                              enProcType;

    /* 转换发送给L的proctype */
    enProcType = NAS_MML_PROC_BUTT;

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));

    NAS_MMC_ConverGmmActionTypeToMml(pstPsRegRsltInd->enGmmActionType, &enProcType);


    NAS_MMC_ConvertGmmRegDomainToMmcDomain(pstPsRegRsltInd->enReqDomain, &stActionRslt.enReqDomain);

    NAS_MMC_ConvertGmmRegDomainToMmcDomain(pstPsRegRsltInd->enRsltDomain, &stActionRslt.enRstDomain);



#endif
    pstLai              = NAS_MML_GetCurrCampLai();

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-5-4, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-5-4, end */

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

        NAS_MMC_UpdatePsRegStatePsRegSucc();

        /* Added by w00176964 for V3R3C60_eCall项目, 2014-5-4, begin */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_NORMAL_SERVICE);
        /* Added by w00176964 for V3R3C60_eCall项目, 2014-5-4, end */

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
            /* 当前SYSCFG中L不在时，需要向LMM通知 */
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
        NAS_MMC_SetPsRegAdditionalAction_PlmnList(enAdditionalAction);
    }

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
 函 数 名  : NAS_MMC_IsNeedPlmnSearch_PlmnList
 功能描述  : 是否需要搜网
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 需要搜网 VOS_TRUE
             不需要搜网 VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月20日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2012年5月8日
    作    者   : t00212959
    修改内容   : GUL BG项目调整
  3.日    期   : 2012年6月8日
    作    者   : s46746
    修改内容   : for CS/PS mode 1，列表搜网完成后如果需要周期性搜索GU，返回需要搜网
  4.日    期   : 2013年10月17日
    作    者   : l65478
    修改内容   : DTS2013102103487:DT需求:在单域失败时也需要发起搜网
  5.日    期   : 2014年01月10日
    作    者   : w00176964
    修改内容   : VoLTE_PhaseIII项目
  6.日    期   : 2015年1月14日
    作    者   : z00161729
    修改内容   : AT&T 支持DAM特性修改
  7.日    期   : 2015年4月20日
    作    者   : z00161729
    修改内容   : 24301 R11 CR升级项目修改
  8.日    期   : 2015年6月19日
    作    者   : z00161729
    修改内容   : 24008 23122 R11 CR升级项目修改
*****************************************************************************/
VOS_UINT32  NAS_MMC_IsNeedPlmnSearch_PlmnList(VOS_VOID)
{
    VOS_UINT32                                              ulIsNormalService;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_UE_OPERATION_MODE_ENUM_UINT8                enLUeMode;
    NAS_MML_ADDITION_UPDATE_RSLT_INFO_ENUM_UINT8            enAdditionUpdateRslt;

    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enPsRegCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsRegCause;

    enPsRegCause            = NAS_MML_REG_FAIL_CAUSE_NULL;
    enCsRegCause            = NAS_MML_REG_FAIL_CAUSE_NULL;
#endif

    ulIsNormalService = NAS_MMC_IsNormalServiceStatus();

    /* 当前卡有效且为限制服务 */
    if ((VOS_TRUE == NAS_MML_IsUsimStausValid())
     && (VOS_FALSE == ulIsNormalService))
    {
        return VOS_TRUE;
    }

    /* 当前NAS处于搜网未驻留过程 */
    if (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == NAS_MMC_GetSpecPlmnSearchState())
    {
        return VOS_TRUE;
    }

    /* 如果需要anycell搜网,则返回true */
    if (VOS_TRUE == NAS_MMC_GetAnyCellSrchFlg_PlmnList())
    {
        return VOS_TRUE;
    }

    /* 单域注册特性打开时,在PS或者CS注册失败#17,需要发起搜网 */
    if (VOS_TRUE == NAS_MMC_IsSingleDomainRegFailNeedPlmnSrch(NAS_MSCC_PIF_SRVDOMAIN_CS))
    {
        return VOS_TRUE;
    }
    if (VOS_TRUE == NAS_MMC_IsSingleDomainRegFailNeedPlmnSrch(NAS_MSCC_PIF_SRVDOMAIN_PS))
    {
        return VOS_TRUE;
    }

#if (FEATURE_ON == FEATURE_LTE)

    enLUeMode            = NAS_MML_GetLteUeOperationMode();
    enAdditionUpdateRslt = NAS_MML_GetAdditionUpdateRslt();

    /* 当前单模L */
    if (VOS_TRUE == NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
    {
        return VOS_FALSE;
    }

    /* 当前接入技术不为LTE */
    if (NAS_MML_NET_RAT_TYPE_LTE != NAS_MML_GetCurrNetRatType())
    {
        return VOS_FALSE;
    }

    /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, begin */
    /* 不是CS/PS mode 1或IMS VOICE可用 */
    if ((VOS_TRUE                              == NAS_MML_GetImsVoiceAvailFlg())
     || (NAS_MML_LTE_UE_OPERATION_MODE_CS_PS_1 != enLUeMode))

    /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, end */
    {
        return VOS_FALSE;
    }

    /* addition update ie为"SMS ONLY"或"CSFB not preferred" */
    if (VOS_TRUE == NAS_MMC_IsNeedDisableL_CombinedRegSuccAdditionUpdateRslt(enAdditionUpdateRslt))
    {
        return VOS_TRUE;
    }

    /* 当前驻留网络在原因值#18列表中 */
    if (VOS_TRUE == NAS_MML_IsPlmnIdInCsDomainUnAvailPlmnList(NAS_MML_GetCurrCampPlmnId()))
    {
        return VOS_TRUE;
    }

    /* NAS_MMC_GetRegRsltAttemptCounter为5 */
    if (NAS_MML_MAX_PS_REG_FAIL_CNT == NAS_MMC_GetRegRsltAttemptCounter(NAS_MMC_GetRegRsltType()))
    {
        /* 获取之前注册失败的原因值 */
       NAS_MMC_GetDomainRegStatusInRegInfoList(NAS_MML_GetCurrCampPlmnId(),
                                               NAS_MML_NET_RAT_TYPE_LTE,
                                               &enCsRegCause,
                                               &enPsRegCause);

        if (NAS_MML_REG_FAIL_CAUSE_PROCEDURE_CONGESTION == enCsRegCause)
        {
            return NAS_MMC_IsNeedDisableL_RegFailCause22AttmptCntMaxTimes();
        }

        /* 24301_CR1884R4_(Rel-11)_C1-140658-C1-140643-C1-140393-C1-140368-C1-140004-24301-b90-TA-IMSVoPS-EPS-only
          TAU ACCEPT，EPS ONLY成功，被拒原因值为16,17，CS/PS1，DIABLE LTE的条件增加
          persistent EPS bearer是否存在，对应24301 5.5.3.3.4.3章节:
              #16 and #17:a UE operating in CS/PS mode 1 of operation with "IMS voice not available"
          and with a persistent EPS bearer context shall wait until the radio bearer
          associated with the persistent EPS bearer context has been released. When
          the radio bearer associated with the persistent EPS bearer context has been
          released and the UE is registered for EPS services only, operating in CS/PS
          mode 1 of operation with "IMS voice not available", then the UE shall attempt
          to select GERAN or UTRAN radio access technology and proceed with appropriate
          MM or GMM specific procedures and disable the E-UTRA capability (see subclause 4.5).
          该CR受协议版本控制 */
        if (NAS_MML_REG_FAIL_CAUSE_MSC_UNREACHABLE == enCsRegCause)
        {
            return NAS_MMC_IsNeedDisableL_RegFailCause16AttmptCntMaxTimes();
        }

        if (NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE == enCsRegCause)
        {
            return NAS_MMC_IsNeedDisableL_RegFailCause17AttmptCntMaxTimes();
        }

        return VOS_TRUE;
    }

#endif


    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SortSearchedPlmnList_PlmnList
 功能描述  : 将搜索到的列表进行排序
 输入参数  : pstPlmnSearchList 搜到的列表
 输出参数  : pstReportList     排序后的上报列表
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月20日
    作    者   : w00166186
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID    NAS_MMC_SortSearchedPlmnList_PlmnList(
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstPlmnSearchList,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstReportList
)
{
    VOS_UINT32                                              i;
    VOS_UINT32                                              ulRatNum;

    /* 初始化列表 */
    PS_MEM_SET(pstReportList, 0x0, sizeof(NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU));

    /* 向选网列表中增加HPLMN或EHPLMN */
    NAS_MMC_AddEHPlmnInPlmnSelectionList(pstReportList);

    /* 向选网列表中增加UPLMN和OPLMN */
    NAS_MMC_AddUOPlmnInPlmnSelectionList(pstReportList);

    ulRatNum = NAS_MML_GetMsPrioRatList()->ucRatNum;

    /* 更新高优先级候补列表状态并加入剩下的高低质量函数 */
    for(i = 0; i < ulRatNum; i++)
    {
        /* 更新完毕需要将剩余网络补充到列表 */

        NAS_MMC_UpdatePlmnListInPlmnSelectionList((&pstPlmnSearchList[i]),
                                                  pstReportList,
                                                  VOS_TRUE,
                                                  VOS_TRUE);
    }

    /*重新对高低质量网络进行排序*/
    NAS_MMC_SortAvailPlmnInPlmnSelectionList(pstReportList);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetPlmnStatus_PlmnList
 功能描述  : 获取列表中每个PLMN ID的状态
 输入参数  : pstPlmnId                 上报列表中的每个PLMN ID
             usRaMode                  每个PLMN ID对应的接入模式
 输出参数  : pucStatus  PLMN ID的状态
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月20日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2011年09月21日
    作    者   : W00166186
    修改内容   : V7R1 PHASE II
  3.日    期   : 2011年11月24日
    作    者   : w00167002
    修改内容   : DTS2011112405567:原有的函数名NAS_MML_IsPlmnIdInDestPlmnList
                 更改为NAS_MML_IsBcchPlmnIdInDestSimPlmnList,用于明确判断
                 网络的类型，否则网络比较可能会出错
*****************************************************************************/
VOS_VOID NAS_MMC_GetPlmnStatus_PlmnList(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId,
    VOS_UINT8                          *pucStatus,
    VOS_UINT16                          usRaMode
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enOrigNetType;
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU   *pstForbidPlmnInfo;
    NAS_MML_PLMN_ID_STRU               *pstCurPlmnId = VOS_NULL_PTR;

    /* 当前在非驻留状态下，双模时会切换到另一个模式下发起列表搜索，
       而在驻留状态下，在当前模式下就可以把两个模式下的PLMN都搜索并上报上来，
       所以要区分两种情况分别获取RPLMN的RAT */
    if (NAS_MMC_AS_CELL_NOT_CAMP_ON == NAS_MMC_GetAsCellCampOn())
    {
        NAS_MMC_GetOrigenSearchRat_PlmnList(&enOrigNetType);
    }
    else
    {
        enOrigNetType = NAS_MML_GetCurrNetRatType();
    }

    /* 获取禁止网络信息 */
    pstForbidPlmnInfo = NAS_MML_GetForbidPlmnInfo();


    /* 在forbid plmn列表中 */
    if(VOS_TRUE == NAS_MML_IsBcchPlmnIdInDestSimPlmnList(pstPlmnId,
                                                  pstForbidPlmnInfo->ucForbPlmnNum,
                                                  pstForbidPlmnInfo->astForbPlmnIdList))
    {
        *pucStatus              = NAS_MSCC_PIF_PLMN_STATUS_FORBIDDEN;
    }
    else
    {
        *pucStatus              = NAS_MSCC_PIF_PLMN_STATUS_AVAILIBLE;
    }

    /*当PLMN等于当前LAI的PLMN时,则认为其状态为当前*/
    if (VOS_TRUE == NAS_MMC_IsNormalServiceStatus())
    {
        pstCurPlmnId = NAS_MML_GetCurrCampPlmnId();

        if ( (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(pstCurPlmnId, pstPlmnId))
            &&( usRaMode == enOrigNetType))
        {
            if (NAS_MSCC_PIF_PLMN_STATUS_FORBIDDEN != *pucStatus)
            {
                *pucStatus = NAS_MSCC_PIF_PLMN_STATUS_CURRENT;
            }
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_BuidTafMmcPlmnListInd_PlmnList
 功能描述  : 构造消息ID_MMC_MSCC_PLMN_LIST_CNF
 输入参数  : 无
 输出参数  : pstSndTafMsg
 返 回 值  : VOS_TRUE 构造成功
             VOS_FALSE 构造失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月23日
    作    者   : w00166186
    修改内容   : 新生成函数
  2.日    期   : 2012年03月03日
    作    者   : s62952
    修改内容   : BalongV300R002 Build优化项目:删除NAS_FEATURE_BLACK_WHITE_PLMN宏
  3.日    期   : 2012年07月25日
    作    者   : t00212959
    修改内容   : DTS2011110807051:只保留最高优先级的EHPLMN
  4.日    期   : 2012年08月20日
    作    者   : w00176964
    修改内容   : GUTL PhaseII调整:上报列表中删除禁止RAT的PLMN
  5.日    期   : 2013年11月01日
    作    者   : l00208543
    修改内容   : 根据卡类型禁止网络制式
  6.日    期   : 2015年1月15日
    作    者   : z00161729
    修改内容   : AT&T 支持DAM特性修改
*****************************************************************************/
VOS_UINT32    NAS_MMC_BuildTafMmcPlmnListIndMsg_PlmnList(
    MMC_MSCC_PLMN_LIST_CNF_STRU          *pstSndTafMsg
)
{
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU  *pstReportList = VOS_NULL_PTR;
    VOS_UINT32                              i;
    VOS_UINT32                              j;

    NAS_MML_HPLMN_CFG_INFO_STRU            *pstHplmnCfgInfo = VOS_NULL_PTR;

    NAS_MML_DISABLED_RAT_PLMN_CFG_INFO_STRU                *pstDisabledRatPlmnCfg   = VOS_NULL_PTR;

    /* 获取禁止接入技术的PLMN信息 */
    pstDisabledRatPlmnCfg = NAS_MML_GetDisabledRatPlmnInfo();

    pstHplmnCfgInfo = NAS_MML_GetHplmnCfg();

    pstReportList   = (NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                                                           sizeof(NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU));
    if (VOS_NULL_PTR == pstReportList)
    {
        /* 异常打印 */
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccPlmnListCnf_PlmnList: ALLOC MEM FAIL!");
        return VOS_FALSE;
    }

    PS_MEM_SET(pstSndTafMsg, 0, sizeof(MMC_MSCC_PLMN_LIST_CNF_STRU));
    pstSndTafMsg->MsgHeader.ulLength          = sizeof(MMC_MSCC_PLMN_LIST_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstSndTafMsg->MsgHeader.ulMsgName         = ID_MMC_MSCC_PLMN_LIST_CNF;
    pstSndTafMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstSndTafMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSndTafMsg->MsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstSndTafMsg->ulCnt                       = 0;

    /* 将搜索到列表进行排序 */
    NAS_MMC_SortSearchedPlmnList_PlmnList(NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                          pstReportList);

    /* 删除重复的PLMN */
    NAS_MMC_DelDuplicatedPlmnWithRatInPlmnList(pstReportList);

    if (VOS_TRUE == pstHplmnCfgInfo->ucEhplmnSupportFlg)
    {
        if (NAS_MML_EHPLMN_PRESENT_IND_HIGHEST == NAS_MML_GetEHplmnPresentInd())
        {
            /* 仅保留优先级最高的EHPLMN,其他的EHPLMN可删除 */
            NAS_MMC_DelLowPrioEHPlmn(pstReportList);
        }
    }

    /* 将排好序的列表中的网络加入消息结构中 */
    for ( i = 0 ; i < pstReportList->usSearchPlmnNum; i++ )
    {
        /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */
        /* 判断PLMN在黑名单或者不在白名单，则不上报 */
        if (VOS_TRUE == NAS_MML_IsPlmnIdForbiddenByWhiteBlackList(&(pstReportList->astPlmnSelectionList[i].stPlmnId)))
        {
            continue;
        }
        /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */

        /* 删除在禁止接入技术的网络的接入技术 */
        NAS_MMC_DelPlmnSelectionRatInfoInDisabledPlmnWithForbiddenPeriodList(&(pstReportList->astPlmnSelectionList[i]),
                                                  pstDisabledRatPlmnCfg->ulDisabledRatPlmnNum,
                                                  pstDisabledRatPlmnCfg->astDisabledRatPlmnId);

        /* 删除在禁止RAT列表中的接入技术 */
        NAS_MMC_DeleteForbiddenRatInPlmnSeleInfo(&(pstReportList->astPlmnSelectionList[i]));

        /* 若添加网络的接入技术个数为零，则不添加 */
        if ( 0 == pstReportList->astPlmnSelectionList[i].ucRatNum )
        {
            continue;
        }

        /* 将排好序的搜索到的PLMN加入上报消息结构中 */
        for ( j = 0; j < pstReportList->astPlmnSelectionList[i].ucRatNum; j++)
        {
            if (( NAS_MMC_NET_STATUS_SEARCHED_EXIST == pstReportList->astPlmnSelectionList[i].astPlmnRatInfo[j].enNetStatus)
                && (pstSndTafMsg->ulCnt < NAS_MSCC_PIF_MAX_PLMN_CNT))
            {
                /* 把此PLMN加入到上报列表中 */
                pstSndTafMsg->aPlmnList[pstSndTafMsg->ulCnt].ulMcc
                                        = pstReportList->astPlmnSelectionList[i].stPlmnId.ulMcc;

                pstSndTafMsg->aPlmnList[pstSndTafMsg->ulCnt].ulMnc
                                        = pstReportList->astPlmnSelectionList[i].stPlmnId.ulMnc;

                pstSndTafMsg->aucRaMode[pstSndTafMsg->ulCnt]
                                        = pstReportList->astPlmnSelectionList[i].astPlmnRatInfo[j].enRatType;

                /* 获取列表中每个PLMN的状态 */
                NAS_MMC_GetPlmnStatus_PlmnList((NAS_MML_PLMN_ID_STRU *)&(pstSndTafMsg->aPlmnList[pstSndTafMsg->ulCnt]),
                                               &(pstSndTafMsg->aucPlmnStatus[pstSndTafMsg->ulCnt]),
                                               pstSndTafMsg->aucRaMode[pstSndTafMsg->ulCnt]);

                pstSndTafMsg->ulCnt++;
            }
        }
    }

    /* 内存释放 */
    PS_MEM_FREE(WUEPS_PID_MMC, pstReportList);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_BuildTafMmcPlmnListAbortCnfMsg_PlmnList
 功能描述  : 构造消息ID_MMC_MSCC_PLMN_LIST_ABORT_CNF
 输入参数  : 无
 输出参数  : pstSndTafMsg
 返 回 值  : VOS_TRUE 构造成功
             VOS_FALSE 构造失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月6日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2012年03月03日
    作    者   : s62952
    修改内容   : BalongV300R002 Build优化项目:删除NAS_FEATURE_BLACK_WHITE_PLMN宏
  3.日    期   : 2013年4月15日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  4.日    期   : 2013年8月27日
    作    者   : w00242748
    修改内容   : DTS2013071808373编译告警清理
*****************************************************************************/
VOS_UINT32    NAS_MMC_BuildTafMmcPlmnListAbortCnfMsg_PlmnList(
    MMC_MSCC_PLMN_LIST_ABORT_CNF_STRU    *pstSndMsccMsg
)
{
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU  *pstReportList = VOS_NULL_PTR;
    VOS_UINT32                              i;
    VOS_UINT32                              j;

    pstReportList   = (NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                                                           sizeof(NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU));
    if (VOS_NULL_PTR == pstReportList)
    {
        /* 异常打印 */
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_BuildTafMmcPlmnListAbortCnfMsg_PlmnList: ALLOC MEM FAIL!");
        return VOS_FALSE;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstReportList) + VOS_MSG_HEAD_LENGTH, 0, sizeof(NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU) - VOS_MSG_HEAD_LENGTH);
    pstSndMsccMsg->MsgHeader.ulLength          = sizeof(MMC_MSCC_PLMN_LIST_ABORT_CNF_STRU);
    pstSndMsccMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstSndMsccMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSndMsccMsg->MsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstSndMsccMsg->MsgHeader.ulMsgName         = ID_MMC_MSCC_PLMN_LIST_ABORT_CNF;
    pstSndMsccMsg->ulCnt                       = 0;

    /* 将搜索到列表进行排序 */
    NAS_MMC_SortSearchedPlmnList_PlmnList(NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                          pstReportList);

    /* 删除重复的PLMN */
    NAS_MMC_DelDuplicatedPlmnWithRatInPlmnList(pstReportList);

    /* 将排好序的列表中的网络加入消息结构中 */
    for ( i = 0 ; i < pstReportList->usSearchPlmnNum; i++ )
    {
        /* 判断PLMN在黑名单或者不在白名单，则不上报 */
        /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
         if (VOS_TRUE == NAS_MML_IsPlmnIdForbiddenByWhiteBlackList(&(pstReportList->astPlmnSelectionList[i].stPlmnId)))
         {
             continue;
         }
        /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */

        /* 将排好序的搜索到的PLMN加入上报消息结构中 */
        for ( j = 0; j < pstReportList->astPlmnSelectionList[i].ucRatNum; j++)
        {
            if (( NAS_MMC_NET_STATUS_SEARCHED_EXIST == pstReportList->astPlmnSelectionList[i].astPlmnRatInfo[j].enNetStatus)
                && (pstSndMsccMsg->ulCnt < NAS_MSCC_PIF_MAX_PLMN_CNT))
            {
                /* 把此PLMN加入到上报列表中 */
                pstSndMsccMsg->aPlmnList[pstSndMsccMsg->ulCnt].ulMcc
                                        = pstReportList->astPlmnSelectionList[i].stPlmnId.ulMcc;

                pstSndMsccMsg->aPlmnList[pstSndMsccMsg->ulCnt].ulMnc
                                        = pstReportList->astPlmnSelectionList[i].stPlmnId.ulMnc;

                pstSndMsccMsg->aucRaMode[pstSndMsccMsg->ulCnt]
                                        = pstReportList->astPlmnSelectionList[i].astPlmnRatInfo[j].enRatType;

                /* 获取列表中每个PLMN的状态 */
                NAS_MMC_GetPlmnStatus_PlmnList((NAS_MML_PLMN_ID_STRU *)&(pstSndMsccMsg->aPlmnList[pstSndMsccMsg->ulCnt]),
                                               &(pstSndMsccMsg->aucPlmnStatus[pstSndMsccMsg->ulCnt]),
                                               pstSndMsccMsg->aucRaMode[pstSndMsccMsg->ulCnt]);

                pstSndMsccMsg->ulCnt++;
            }
        }
    }

    /* 内存释放 */
    PS_MEM_FREE(WUEPS_PID_MMC, pstReportList);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndMsccPlmnListCnf_PlmnList
 功能描述  : 向MSCC发送LIST搜网结果
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月20日
    作    者   : w00166186
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccPlmnListCnf_PlmnList(VOS_VOID)
{
    MMC_MSCC_PLMN_LIST_CNF_STRU          *pstSndMsccMsg = VOS_NULL_PTR;

    pstSndMsccMsg   = (MMC_MSCC_PLMN_LIST_CNF_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                                              sizeof(MMC_MSCC_PLMN_LIST_CNF_STRU));
    if (VOS_NULL_PTR == pstSndMsccMsg)
    {
        /* 异常打印 */
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccPlmnListCnf_PlmnList: ALLOC MEM FAIL!");
        return;
    }

    /* 构造上报消息 */
    if (VOS_TRUE != NAS_MMC_BuildTafMmcPlmnListIndMsg_PlmnList(pstSndMsccMsg))
    {
        PS_MEM_FREE(WUEPS_PID_MMC, pstSndMsccMsg);
        return;
    }

    /* 向MSCC发送列表搜结果 */
    NAS_MMC_SndMsccPlmnListInd(pstSndMsccMsg);

    /* OM 事件上报 */
    if ( 0 == pstSndMsccMsg->ulCnt)
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
            VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);
    }
    else
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_SUCCESS,
            VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);
    }

    PS_MEM_FREE(WUEPS_PID_MMC, pstSndMsccMsg);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndMsccPlmnListAbortCnf_PlmnList
 功能描述  : 向MSCC发送ID_MMC_MSCC_PLMN_LIST_ABORT_CNF消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月20日
    作    者   : w00166186
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccPlmnListAbortCnf_PlmnList(VOS_VOID)
{
    MMC_MSCC_PLMN_LIST_ABORT_CNF_STRU  *pstSndMsccMsg = VOS_NULL_PTR;

    /* 获取高优先级网络的个数 */
    pstSndMsccMsg   = (MMC_MSCC_PLMN_LIST_ABORT_CNF_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                                              sizeof(MMC_MSCC_PLMN_LIST_ABORT_CNF_STRU));
    if (VOS_NULL_PTR == pstSndMsccMsg)
    {
        /* 异常打印 */
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccPlmnListAbortCnf_PlmnList: ALLOC MEM FAIL!");
        return;
    }

    /* 构造上报消息 */
    if (VOS_TRUE != NAS_MMC_BuildTafMmcPlmnListAbortCnfMsg_PlmnList(pstSndMsccMsg))
    {
        PS_MEM_FREE(WUEPS_PID_MMC, pstSndMsccMsg);
        return;
    }

    /* 向MSCC发送列表搜结果 */
    NAS_MMC_SndMsccPlmnListAbortCnf(pstSndMsccMsg);

    PS_MEM_FREE(WUEPS_PID_MMC, pstSndMsccMsg);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndSpecRatPlmnListReq_PlmnList
 功能描述  : 向指定的接入技术发送LIST搜网请求
 输入参数  : enRat 指定的接入技术
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月20日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2012年4月25日
    作    者   : w00176964
    修改内容   : V7R1C50_GUL_BG 项目开发
  3.日    期   : 2015年10月15日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_VOID NAS_MMC_SndSpecRatPlmnListReq_PlmnList(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
#if (FEATURE_ON == FEATURE_CSG)
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;

    enRatType = NAS_MML_GetCurrNetRatType();

    /* 如果是CSG列表搜网，则进行csg列表搜网，返回 */
    if (VOS_TRUE == NAS_MMC_IsCsgList_PlmnList())
    {
        if ((NAS_MMC_AS_CELL_CAMP_ON == NAS_MMC_GetAsCellCampOn())
         || (NAS_MML_NET_RAT_TYPE_LTE == enRatType))
        {
            NAS_MMC_SndSpecRatCsgListSearchReq_PlmnList(enRatType);
            return;
        }

        /* gu下非驻留态需要挂起gu到lte下搜网 */
        NAS_MMC_SndSpecRatCsgListSuspendReq_PlmnList(enRatType);
        return;
    }
#endif

    switch (enRat)
    {
#if (FEATURE_LTE == FEATURE_ON)
        case NAS_MML_NET_RAT_TYPE_LTE:

            NAS_MMC_SndLmmPlmnListReq();

            /* 目前L支持驻留态LIST搜网,此处不再显示更新当前的驻留状态,由
               新增消息接口ID_LMM_MMC_NOT_CAMP_ON_IND指示 */

            /* 迁移状态到等待LMM的LIST搜网回复 */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_LMM_PLMN_SEARCH_CNF);

            /* 启动保护定时器 */
            if (NAS_MMC_AS_CELL_CAMP_ON == NAS_MMC_GetAsCellCampOn())
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_LIST_CNF, TI_NAS_MMC_CAMP_ON_WAIT_LMM_PLMN_LIST_CNF_LEN);
            }
            else
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_LIST_CNF, TI_NAS_MMC_NOT_CAMP_ON_WAIT_LMM_PLMN_LIST_CNF_LEN);
            }

            break;
#endif

        case NAS_MML_NET_RAT_TYPE_WCDMA:

            NAS_MMC_SndAsPlmnListReq(WUEPS_PID_WRR);

            /* 迁移状态到等待WAS的LIST搜网回复 */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_WAS_PLMN_SEARCH_CNF);

            /* 启动保护定时器 */
            if (NAS_MMC_AS_CELL_CAMP_ON == NAS_MMC_GetAsCellCampOn())
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_PLMN_LIST_CNF, TI_NAS_MMC_CAMP_ON_WAIT_WAS_PLMN_LIST_CNF_LEN);
            }
            else
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_PLMN_LIST_CNF, TI_NAS_MMC_NOT_CAMP_ON_WAIT_WAS_PLMN_LIST_CNF_LEN);
            }

            break;

        case NAS_MML_NET_RAT_TYPE_GSM:

            NAS_MMC_SndAsPlmnListReq(UEPS_PID_GAS);

            /* 迁移状态到等待GAS的LIST搜网回复 */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_GAS_PLMN_SEARCH_CNF);

            /* 启动保护定时器 */
            if (NAS_MMC_AS_CELL_CAMP_ON == NAS_MMC_GetAsCellCampOn())
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_PLMN_LIST_CNF, TI_NAS_MMC_CAMP_ON_WAIT_GAS_PLMN_LIST_CNF_LEN);
            }
            else
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_PLMN_LIST_CNF, TI_NAS_MMC_NOT_CAMP_ON_WAIT_GAS_PLMN_LIST_CNF_LEN);
            }

            break;
        default:

            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndSpecRatPlmnListReq_PlmnList Unexpected Rat type!");

            break;
    }
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndSpecRatPlmnSearchStopReq_PlmnList
 功能描述  : 向指定的接入技术发送停止搜网请求
 输入参数  : enRat 指定的接入技术
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月24日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_SndSpecRatPlmnSearchStopReq_PlmnList(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    switch (enRat)
    {
#if (FEATURE_LTE == FEATURE_ON)
        case NAS_MML_NET_RAT_TYPE_LTE:

            /* 向LMM发送停止搜网请求 */
            NAS_MMC_SndLmmPlmnSrchStopReq();

            /* 迁移状态到等待LMM的停止搜网回复 */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_LMM_PLMN_SEARCH_STOP_CNF);

            /* 启动保护定时器 */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF_LEN);

            break;
#endif

        case NAS_MML_NET_RAT_TYPE_WCDMA:

            /* 向WAS发送停止搜网请求 */
            NAS_MMC_SndAsPlmnSrchStopReq(WUEPS_PID_WRR);

            /* 迁移状态到等待WAS的停止搜网回复 */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_WAS_PLMN_SEARCH_STOP_CNF);

            /* 启动保护定时器 */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF_LEN);

            break;

        case NAS_MML_NET_RAT_TYPE_GSM:

            /* 向GAS发送停止搜网请求 */
            NAS_MMC_SndAsPlmnSrchStopReq(UEPS_PID_GAS);

            /* 迁移状态到等待GAS的停止搜网回复 */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_GAS_PLMN_SEARCH_STOP_CNF);

            /* 启动保护定时器 */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF_LEN);

            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndSpecRatPlmnSearchStopReq_PlmnList Unexpected Rat type!");

            break;
    }
}


/*****************************************************************************
 函 数 名  : NAS_MMC_SndSpecRatSuspendReq_PlmnList
 功能描述  : 向指定的接入技术发送挂起请求
 输入参数  : enRat 指定的接入技术
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月24日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2014年1月28日
    作    者   : s00246516
    修改内容   : L-C互操作项目:增加获取和注册请求的处理
*****************************************************************************/
VOS_VOID NAS_MMC_SndSpecRatSuspendReq_PlmnList(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    switch (enRat)
    {
#if (FEATURE_LTE == FEATURE_ON)
        case NAS_MML_NET_RAT_TYPE_LTE:

            /* 更新驻留状态 */
            NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
            NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

            /* Added by s00246516 for L-C互操作项目, 2014-01-28, Begin */
            NAS_MMC_SetAsAnyCampOn(VOS_FALSE);
            /* Added by s00246516 for L-C互操作项目, 2014-01-28, End */

            /* 向LMM发送挂起请求 */
            NAS_MMC_SndLmmSuspendReq();

            /* 迁移状态到等待LMM的挂起回复 */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_LMM_SUSPEND_CNF);

            /* 启动保护定时器 */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_SUSPEND_CNF, TI_NAS_MMC_WAIT_LMM_SUSPEND_CNF_LEN);

            break;
#endif

        case NAS_MML_NET_RAT_TYPE_WCDMA:

            /* 更新驻留状态 */
            NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
            NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

            /* Added by s00246516 for L-C互操作项目, 2014-01-28, Begin */
            NAS_MMC_SetAsAnyCampOn(VOS_FALSE);
            /* Added by s00246516 for L-C互操作项目, 2014-01-28, End */

            /* 向WAS发送挂起请求 */
            NAS_MMC_SndAsSuspendReq(WUEPS_PID_WRR);

            /* 迁移状态到等待WAS的挂起回复 */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_WAS_SUSPEND_CNF);

            /* 启动保护定时器 */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF, TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF_LEN);

            break;

        case NAS_MML_NET_RAT_TYPE_GSM:

            /* 更新驻留状态 */
            NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
            NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

            /* Added by s00246516 for L-C互操作项目, 2014-01-28, Begin */
            NAS_MMC_SetAsAnyCampOn(VOS_FALSE);
            /* Added by s00246516 for L-C互操作项目, 2014-01-28, End */

            /* 向GAS发送挂起请求 */
            NAS_MMC_SndAsSuspendReq(UEPS_PID_GAS);

            /* 迁移状态到等待GAS的挂起回复 */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_GAS_SUSPEND_CNF);

            /* 启动保护定时器 */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF, TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF_LEN);

            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndSpecRatSuspendReq_PlmnList Unexpected Rat type!");

            break;
    }
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcRrmmSearchCnf_PlmnList
 功能描述  : 处理PLMN LIST的结果
 输入参数  : pstPlmnSrchCnf PLMN LIST的结果
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月24日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2012年6月5日
    作    者   : z00161729
    修改内容   : V7R1C50 GUL背景搜网修改
  3.日    期   : 2012年10月17日
    作    者   : z00161729
    修改内容    : DTS2012052107863:W下有ps业务可以发起list搜，g和l不支持
  4.日    期   : 2014年2月7日
    作    者   : w00167002
    修改内容   : SVLTE共天线项目:驻留成功后的LIST搜网,由于驻留成功后，当前要么是国内，
                 要么是国外。国内是LT模式，TD下不存在NO RF。国外是GUL单待模式，不存在NO RF。
                 当前共天线项目所考虑的场景为:在双待模式，W下和G存在共天线。
  5.日    期   : 2013年3月29日
    作    者   : y00176023
    修改内容   : DSDS GUNAS II项目:NO RF情况下向RRM发起注册，只考虑GU不考虑LTE搜网产生的NO RF
  6.日    期   : 2014年5月15日
    作    者   : w00167002
    修改内容   : DTS2014051501018:DSDS副MODEM发起电话，主MODEM搜网失败启动AVAILABLE
                 定时器，用户发起列表搜，在列表搜过程中，周期搜网定时器超时，列表搜
                 结束后，MMC没有启动周期搜网定时器。
                 修改为:在列表搜NO RF后，都启动AVAILABLE定时器，在AVAILABLE定时器
                 超时后，增加如果当前被拒#12则不搜网，当前ACCESS BAR则不搜网。
*****************************************************************************/
VOS_VOID NAS_MMC_ProcRrmmSearchCnf_PlmnList(
    RRMM_PLMN_SEARCH_CNF_STRU          *pstPlmnSrchCnf
)
{
    /* 判断LIST搜网结果 */
    switch (pstPlmnSrchCnf->ulSearchRlt)
    {
        case RRC_PLMN_SEARCH_RLT_LIST_REJ:

            /* 启动5S周期性尝试定时器 */
            if ( VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
            {
                 /* CS业务比如电话或短信引起的接入层list rej需要终止list搜，
                    响应业务否则AT口被list请求占用，用户无法发起接听电话或收短信 */
                if (VOS_TRUE == NAS_MML_GetCsServiceExistFlg())
                {
                    /* 发送LIST REJ给MSCC */
                    NAS_Mmc_SndMsccPlmnListRej();
                }
                else
                {
                    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST, TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST_LEN);
                }
            }
            else
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST, TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST_LEN);
            }

            /* 发送状态机失败的退出结果 */
            NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                    VOS_FALSE,
                                    NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                    NAS_MMC_GetRegRsltInfo_PlmnList());

            /* 退出状态机 */
            NAS_MMC_FSM_QuitFsmL2();

            break;

       case RRC_PLMN_SEARCH_RLT_LIST:

            /* 处理PLMN LIST搜网成功的结果 */
            NAS_MMC_ProcPlmnListSucc_PlmnList(pstPlmnSrchCnf);

            break;

       case RRC_PLMN_SEARCH_RLT_LIST_FAIL:
            if ( VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
            {
                /* 发送LIST REJ给MSCC */
                NAS_Mmc_SndMsccPlmnListRej();
            }

            /* 发送状态机失败的退出结果 */
            NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                    VOS_FALSE,
                                    NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                    NAS_MMC_GetRegRsltInfo_PlmnList());

            /* 退出状态机 */
            NAS_MMC_FSM_QuitFsmL2();
            break;

       case RRC_PLMN_SEARCH_RLT_LIST_NO_RF:

            NAS_MMC_ProcNoRf_PlmnList(NAS_MML_GetCurrNetRatType());

            break;

       default:

            /*异常打印*/
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcRrmmSearchCnf_PlmnList Unexpected List Result!");

            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcPlmnListSucc_PlmnList
 功能描述  : 处理PLMN LIST的成功的结果
 输入参数  : pstPlmnSrchCnf PLMN LIST的结果
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月24日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2012年4月26日
    作    者   : t00212959
    修改内容   : GUL BG项目调整

*****************************************************************************/
VOS_VOID NAS_MMC_ProcPlmnListSucc_PlmnList(
    RRMM_PLMN_SEARCH_CNF_STRU          *pstPlmnSrchCnf
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat;
    VOS_UINT32                          ulIndex;

    /* LIST搜网过程中,需要根据当前接入层携带的已经搜索
       过的接入技术信息更新RAT的搜索标记 */
    for ( ulIndex = 0; ulIndex < NAS_RRC_MAX_RAT_NUM; ulIndex++)
    {
        if ( RRC_NAS_RAT_LIST_SEARCH_CMPL == pstPlmnSrchCnf->astSearchRatInfo[ulIndex].enListSearchRlt)
        {
            /*将RRC的接入技术转换成MML定义的格式，然后更新 */
            NAS_MMC_ConvertRrcRatToNasFormat(pstPlmnSrchCnf->astSearchRatInfo[ulIndex].enRat, &enRat);
            NAS_MMC_SetSearchedFlag_PlmnList(enRat);
        }
    }

    /* 保存搜网列表 */
    NAS_MMC_UpdateSearchedPlmnListInfo_PlmnList(&(pstPlmnSrchCnf->PlmnIdList));

    /* LIST搜网过程中,RRC可能出服务区,此时需要设置搜网状态,触发退出LIST搜网后的指定
       搜网 */
    if (NAS_MMC_AS_CELL_NOT_CAMP_ON == NAS_MMC_GetAsCellCampOn())
    {
        NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);
    }

    /* 获取不到下一个未搜索的接入模式 */
    if ( VOS_FALSE == NAS_MMC_GetNextSearchingRat_PlmnList(&enRat))
    {
       /* 如果是用户LIST搜网,向MSCC上报结果 */
       if ( VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
       {
           /* 将搜索到的网络进行排序后上报给MSCC */
           NAS_MMC_SndMsccPlmnListCnf_PlmnList();
       }

       /* 发送状态机成功退出的结果 */
       NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_SUCC,
                               (VOS_UINT8)NAS_MMC_IsNeedPlmnSearch_PlmnList(),
                               NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                               NAS_MMC_GetRegRsltInfo_PlmnList());

       /* 退出状态机 */
       NAS_MMC_FSM_QuitFsmL2();

       return;
    }

    /* 当前接入技术发送挂起请求,迁移状态,启动保护定时器 */
    NAS_MMC_SndSpecRatSuspendReq_PlmnList(NAS_MML_GetCurrNetRatType());

    /* 向GMM发送搜网指示 */
    NAS_MMC_SndGmmPlmnSchInit();

    /* 向MM发送搜网指示 */
    NAS_MMC_SndMmPlmnSchInit();

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ProcRrmmSuspendCnf_PlmnList
 功能描述  : 处理接入层的挂起回复的结果
 输入参数  : pstRrmmSuspendCnf 接入层的挂起回复的结果
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月24日
    作    者   : w00176964
    修改内容   : 新生成函数

  2.日    期   : 2011年12月15日
    作    者   : w00167002
    修改内容   : DTS2011120702166:MMC复位后无复位信息,在MML模块封装复位信息，
                  以供MM层调用，进行软复位。
  3.日    期   : 2012年10月7日
    作    者   : s46746
    修改内容   : for V7R1C50_At_Abort，非驻留列表搜索过程中，发起用户列表搜索，之后打断用户列表搜索，
                 后续没有再次出发搜索
  4.日    期   : 2014年2月18日
    作    者  :  w00242748
    修改内容  :  DTS2014021803515:复位时明确是收到哪个接入技术的异常消息导致的。

  5.日    期   : 2015年3月11日
    作    者   : wx270776
    修改内容   : DTS2015011212939:增加复位场景
*****************************************************************************/
VOS_VOID NAS_MMC_ProcRrmmSuspendCnf_PlmnList(
    RRMM_SUSPEND_CNF_ST                *pstRrmmSuspendCnf
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    VOS_UINT32                          ulNeedPlmnSearch;

    enCurRat      = NAS_MML_GetCurrNetRatType();

    if ( MMC_AS_SUSPEND_FAILURE  == pstRrmmSuspendCnf->ucResult )
    {
        /* 单板复位 */

        if ( (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
          && (NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat) )
        {
            NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_WAS_SUSPEND_FAILURE);
        }
        else if ( NAS_MML_NET_RAT_TYPE_GSM == enCurRat )
        {
            NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_GAS_SUSPEND_FAILURE);
        }
        else if ( NAS_MML_NET_RAT_TYPE_LTE == enCurRat)
        {
            NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_LMM_SUSPEND_FAILURE);
        }
        else
        {
            NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_TD_SUSPEND_FAILURE);
        }

        return;
    }

    /* 判断状态机退出标记是否为真，如果为真*/
    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnList())
    {
        /* 接入技术设置为BUTT，后续可以直接向任意模发送搜网请求 */
        NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

        ulNeedPlmnSearch = VOS_FALSE;

        /* 当前用户列表搜网 */
        if (VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
        {
            if ( VOS_TRUE == NAS_MMC_GetNotifyMsccFlag_PlmnList())
            {
                /* 向MSCC回复ID_MMC_MSCC_PLMN_LIST_ABORT_CNF */
                NAS_MMC_SndMsccPlmnListAbortCnf_PlmnList();

                ulNeedPlmnSearch = VOS_TRUE;
            }
            else
            {
                /* 向MSCC回复LIST搜网结果 */
                NAS_MMC_SndMsccPlmnListCnf_PlmnList();
            }
        }

        /* 发送状态机ABORT的退出结果 */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                                (VOS_UINT8)ulNeedPlmnSearch,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* 获取不到下一个接入技术 */
    if ( VOS_FALSE == NAS_MMC_GetNextSearchingRat_PlmnList(&enRat))
    {
        /* 异常打印 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcRrmmSuspendCnf_PlmnList: Get next search rat fail.");

        /* 接入技术设置为BUTT，后续可以直接向任意模发送搜网请求 */
        NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

        /* 当前为用户LIST搜网 */
        if ( VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
        {
            /* 向MSCC回复ID_MMC_MSCC_PLMN_LIST_CNF */
            NAS_MMC_SndMsccPlmnListCnf_PlmnList();
        }

        /* 发送状态机退出结果 */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                (VOS_UINT8)NAS_MMC_IsNeedPlmnSearch_PlmnList(),
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* 根据获取的接入技术设置当前接入技术 */
    NAS_MML_SetCurrNetRatType(enRat);

    /* 向下个接入模式发送LIST搜网请求,迁移状态,启动保护定时器 */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(enRat);

}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcRrcConnRelInd_PlmnList
 功能描述  : 处理RRC链接释放消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月24日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2012年6月5日
    作    者   : w00176964
    修改内容   : GUL BG项目调整:有PS业务存在,继续启动5S定时器尝试
  3.日    期   : 2014年1月28日
    作    者   : w00242748
    修改内容   : DTS2014012605086:MMC在ON PLMN状态机时收到列表搜请求，当前CS信令
                 链接不存在时，会给接入层发送列表搜请求。如果接入层处理不了，
                 则直接由接入层处理回复。
  4.日    期   : 2015年9月26日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_VOID NAS_MMC_ProcRrcConnRelInd_PlmnList(VOS_VOID)
{
    VOS_UINT32                          ulCsServiceStatusFlg;

    ulCsServiceStatusFlg = NAS_MML_GetCsServiceExistFlg();

    /* 一个域链路释放后，等待另外一个域的释放指示时，有可能释放的域上发起业务
       此处需要判断是否有业务存在 */
    if ( VOS_TRUE == ulCsServiceStatusFlg )
    {
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);

        NAS_MMC_SndMsccPlmnListRejMsg_PlmnList();

        /* 有业务时，未进行LIST搜网，搜到的网络列表为空,发送状态机失败的退出结果 */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                            VOS_FALSE,
                            NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                            NAS_MMC_GetRegRsltInfo_PlmnList());

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }
    else if ( VOS_TRUE == NAS_MML_IsRrcConnExist() )
    {
        /* 如果存在信令链接，则继续等待；等待超时之后，再继续尝试发起列表搜 */
    }
    else
    {
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);

        switch (NAS_MML_GetCurrNetRatType())
        {
            case NAS_MML_NET_RAT_TYPE_WCDMA:

                /* 迁移状态到等待was接入层系统消息 */
                NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_WAS_SYS_INFO_IND);

                /* 启动保护定时器 */
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO, TI_NAS_MMC_WAIT_WAS_SYS_INFO_LEN);

                break;
            case NAS_MML_NET_RAT_TYPE_GSM:

                /* 迁移状态到等待Gas接入层系统消息 */
                NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_GAS_SYS_INFO_IND);

                /* 启动保护定时器 */
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_SYS_INFO, TI_NAS_MMC_WAIT_GAS_SYS_INFO_LEN);

                break;

            default:

            /*异常打印*/
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcRrcConnel_PlmnList Unexpected Rat Type!");
            break;
        }
    }

    return;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_ProcRrmmPlmnSearchStopCnf_PlmnList
 功能描述  : 处理接入层的搜网停止回复的结果
 输入参数  : enRatType 当前接入技术
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月24日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2012年5月2日
    作    者   : t00212959
    修改内容   : GUL BG项目调整
  3.日    期   : 2012年10月7日
    作    者   : s46746
    修改内容   : for V7R1C50_At_Abort，非驻留列表搜索过程中，发起用户列表搜索，之后打断用户列表搜索，
                 后续没有再次出发搜索
  4.日    期   : 2015年11月04日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_VOID NAS_MMC_ProcRrmmPlmnSearchStopCnf_PlmnList(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNextRatType;

    VOS_UINT32                          ulNeedPlmnSearch;

    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnList())
    {
        ulNeedPlmnSearch = VOS_FALSE;

        /* 当前用户列表搜网 */
        if (VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
        {
            if ( VOS_TRUE == NAS_MMC_GetNotifyMsccFlag_PlmnList())
            {
                /* 向MSCC回复ID_MMC_MSCC_PLMN_LIST_ABORT_CNF */
                NAS_MMC_SndMsccPlmnListAbortCnf_PlmnList();

                ulNeedPlmnSearch = NAS_MMC_IsNeedPlmnSearch_PlmnList();
            }
            else
            {
                /* 向MSCC回复LIST搜网结果 */
                NAS_MMC_SndMsccPlmnListCnf_PlmnList();
            }
        }

        /* 发送状态机ABORT退出结果 */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                                (VOS_UINT8)ulNeedPlmnSearch,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* 获取不到下一个未搜索的接入模式 */
    if ( VOS_FALSE == NAS_MMC_GetNextSearchingRat_PlmnList(&enNextRatType))
    {
        /* 用户LIST搜网 */
        if ( VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
        {
            /* 将搜索到的网络进行排序后上报给MSCC */
            NAS_MMC_SndMsccPlmnListCnf_PlmnList();
        }

        /* 发送状态机失败退出的结果 */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                (VOS_UINT8)NAS_MMC_IsNeedPlmnSearch_PlmnList(),
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* 向当前接入技术发送挂起请求,迁移状态,启动保护定时器 */
    NAS_MMC_SndSpecRatSuspendReq_PlmnList(enRatType);

    /* 向GMM发送搜网指示 */
    NAS_MMC_SndGmmPlmnSchInit();

    /* 向MM发送搜网指示 */
    NAS_MMC_SndMmPlmnSchInit();

    return;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_MMC_ProcLmmPlmnSearchStopCnf_PlmnList
 功能描述  : 处理LMM的搜网停止回复的结果
 输入参数  : enRatType 当前接入技术
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月06日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2012年5月2日
    作    者   : t00212959
    修改内容   : GUL BG项目调整
  3.日    期   : 2012年10月7日
    作    者   : s46746
    修改内容   : for V7R1C50_At_Abort，非驻留列表搜索过程中，发起用户列表搜索，之后打断用户列表搜索，
                 后续没有再次出发搜索
  4.日    期   : 2015年11月4日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_VOID NAS_MMC_ProcLmmPlmnSearchStopCnf_PlmnList(VOS_VOID)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNextRatType;

    VOS_UINT32                          ulNeedPlmnSearch;

    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnList())
    {
        ulNeedPlmnSearch = VOS_FALSE;

        /* 通知MSCC回复标记为真 */
        if ( VOS_TRUE == NAS_MMC_GetNotifyMsccFlag_PlmnList())
        {
            if (VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
            {
                /* 向MSCC回复ID_MMC_MSCC_PLMN_LIST_ABORT_CNF */
                NAS_MMC_SndMsccPlmnListAbortCnf_PlmnList();
            }

            ulNeedPlmnSearch = NAS_MMC_IsNeedPlmnSearch_PlmnList();
        }
        else
        {
            /* 向MSCC回复LIST搜网结果 */
            NAS_MMC_SndMsccListSearchCnfMsg_PlmnList();
        }

        /* 发送状态机ABORT退出结果 */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                                (VOS_UINT8)ulNeedPlmnSearch,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* 获取不到下一个未搜索的接入模式 */
    if ( VOS_FALSE == NAS_MMC_GetNextSearchingRat_PlmnList(&enNextRatType))
    {
        /* 向MSCC回复LIST搜网结果 */
        NAS_MMC_SndMsccListSearchCnfMsg_PlmnList();

        /* 发送状态机成功退出的结果 */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                 (VOS_UINT8)NAS_MMC_IsNeedPlmnSearch_PlmnList(),
                                 NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                 NAS_MMC_GetRegRsltInfo_PlmnList());

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* 向当前接入技术发送挂起请求,迁移状态,启动保护定时器 */
    NAS_MMC_SndSpecRatSuspendReq_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

    /* 向GMM发送搜网指示 */
    NAS_MMC_SndGmmPlmnSchInit();

    /* 向MM发送搜网指示 */
    NAS_MMC_SndMmPlmnSchInit();

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcLteSysInfo_PlmnList
 功能描述  : 处理LTE的系统消息
 输入参数  : pstLSysInfoInd - LTE的系统消息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年10月24日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增

*****************************************************************************/
VOS_VOID NAS_MMC_ProcLteSysInfo_PlmnList(
    struct MsgCB                       *pstLSysInfoInd
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;
    NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8               enSpecPlmnSearchState;

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

    /* 保留老的驻留网络信息 */
    pstCurCampInfo  = NAS_MML_GetCurrCampPlmnInfo();
    PS_MEM_CPY(&stOldCampInfo, pstCurCampInfo, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

    /* 根据系统消息，更新MML的全部变量 */
    NAS_MMC_UpdateNetworkInfo_LmmSysInfo(pstLSysInfoInd);

    /* 状态更新为当前已经驻留 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

    /* CBS上报*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_LTE);

    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);

    /*方案优化后，LTE下的小区发生变化，LMM会通过系统消息通知MMC*/
    enSpecPlmnSearchState = NAS_MMC_GetSpecPlmnSearchState();

    if ((VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
     || (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == enSpecPlmnSearchState))
    {
        /* 主动上报 */
        NAS_MMC_SndMsccSysInfo();
    }


    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_STOP);

    /* 转发GMM系统消息,供rabm使用 */
    NAS_MMC_SndGmmLteSysinfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstLSysInfoInd);
    NAS_MMC_SndMmLteSysinfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstLSysInfoInd);

    NAS_MMC_SndLmmLteSysInfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstLSysInfoInd);

    return;
}


#endif

/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedWaitRrcRel_PlmnList
 功能描述  : 判断当前是否等待RRC连接释放
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  : 需要等待RRC连接释放
             VOS_FALSE : 不需要等待RRC连接释放
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年6月5日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2013年12月11日
   作    者   : z00161729
   修改内容   : DTS2013121102199:g下lau过程中，sm发送pdp激活请求给gmm，
                gmm缓存设置ps缓存业务存在标识为true，用户发起list搜网未等连接释放直接发起了list搜
 3.日    期   : 2014年1月28日
   作    者   : w00242748
   修改内容   : DTS2014012605086:MMC在ON PLMN状态机时收到列表搜请求，当前CS信令
                链接不存在时，会给接入层发送列表搜请求。如果接入层处理不了，
                则直接由接入层处理回复。
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedWaitRrcRel_PlmnList( VOS_VOID )
{
    VOS_UINT8                           ucCsSigConnStatusFlg;

    ucCsSigConnStatusFlg = NAS_MML_GetCsSigConnStatusFlg();

    /* 当前RRC连接不存在可以直接发起 */
    if (VOS_FALSE == NAS_MML_IsRrcConnExist())
    {
        return VOS_FALSE;
    }

    /* 当前存在PS业务或缓存的ps业务但不存在cs信令连接允许发给RRC */
    if (VOS_FALSE == ucCsSigConnStatusFlg)
    {
        return VOS_FALSE;
    }

    /* 其他情况认为存在信令连接,被动等待RRC释放信令连接 */
    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcUserPlmnListReq_PlmnList
 功能描述  : 处理用户LIST搜网请求
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月24日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2012年4月25日
    作    者   : w00176964
    修改内容   : V7R1_GUL_BG 项目调整
  3.日    期   : 2012年6月5日
    作    者   : w00176964
    修改内容   : V7R1_GUL_BG 项目调整:PS业务存在直接发给RRC进行LIST搜网
  4.日    期   : 2012年9月11日
    作    者   : w00176964
    修改内容   : V7R1_GUTL项目调整:TD主模下驻留态下需要通知MM/GMM进入搜网状态
  5.日    期   : 2012年10月7日
    作    者   : s46746
    修改内容   : for V7R1C50_At_Abort，非驻留列表搜索过程中，发起用户列表搜索，之后打断用户列表搜索，
                 后续没有再次出发搜索
  6.日    期   : 2012年11月10日
    作    者   : t00212959
    修改内容   : DTS2012111002172 P态列表搜
  7.日    期   : 2014年05月6日
    作    者   : w00176964
    修改内容   : V3R3C60_eCall项目调整注册服务状态上报
  8.日    期   : 2014年5月12日
    作    者   : w00242748
    修改内容   : DTS2014050807056:TD下列表搜之后，PDP去激活不了。
*****************************************************************************/
VOS_VOID NAS_MMC_ProcUserPlmnListReq_PlmnList(VOS_VOID)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;

    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus = VOS_NULL_PTR;

    enRatType     = NAS_MML_GetCurrNetRatType();
    pstConnStatus = NAS_MML_GetConnStatus();

    /* 挂起状态下被打断，当前接入技术为BUTT */
    if ( NAS_MML_NET_RAT_TYPE_BUTT == NAS_MML_GetCurrNetRatType())
    {
       NAS_MMC_GetOrigenSearchRat_PlmnList(&enRatType);

       NAS_MML_SetCurrNetRatType(enRatType);
    }

    /* 判断是否需要等待链接释放 */
    if ( VOS_FALSE == NAS_MMC_IsNeedWaitRrcRel_PlmnList() )
    {
       /* 根据不同接入模式,发送LIST搜网请求，迁到等待搜网结果状态并启动保护定时器*/
       NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_GetCurrNetRatType());

       /* 非驻留态通知MM/GMM搜网开始 */
       if (NAS_MMC_AS_CELL_NOT_CAMP_ON == NAS_MMC_GetAsCellCampOn())
       {
            /* Added by w00176964 for V3R3C60_eCall项目, 2014-5-6, begin */
            NAS_MMC_UpdateServiceStateSpecPlmnSearch();
            NAS_MMC_UpdateRegStateSpecPlmnSearch();
            /* Added by w00176964 for V3R3C60_eCall项目, 2014-5-6, end */

            if ((NAS_MML_NET_RAT_TYPE_WCDMA != enRatType)
             || (VOS_FALSE == pstConnStatus->ucRrcStatusFlg))
            {
                /* 向GMM发送搜网指示 */
                NAS_MMC_SndGmmPlmnSchInit();

                /* 向MM发送搜网指示 */
                NAS_MMC_SndMmPlmnSchInit();

                /* 设置进入搜网状态 */
                NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

                return;
            }
       }

       /* 驻留态在GTL模式TD为主模时需要通知MM/GMM进入搜网状态 */
       if ( (VOS_TRUE == NAS_MMC_IsCurrentTdscdmaMode())
         && (VOS_FALSE == pstConnStatus->ucRrcStatusFlg) )
       {
            /* 向GMM发送搜网指示 */
            NAS_MMC_SndGmmPlmnSchInit();

            /* 向MM发送搜网指示 */
            NAS_MMC_SndMmPlmnSchInit();

            /* 多模后续搜网由GUNAS控制 */
            if (VOS_FALSE == NAS_MML_IsWcdmaOnlyMode(NAS_MML_GetMsPrioRatList()))
            {
                /* 设置进入搜网状态 */
                NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);
            }
       }

       return;
    }

    /* 需要等待连接释放 */
    switch (NAS_MML_GetCurrNetRatType())
    {
#if (FEATURE_LTE == FEATURE_ON)
        case NAS_MML_NET_RAT_TYPE_LTE:

        /* L下有EPS信令连接被动等待LMM释放链路,
           保持与GU的实现一致 */

        /* 迁移状态到等待LMM的EPS链路释放 */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_EPS_CONN_REL_IND);

        /* 启动保护定时器 */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND, TI_NAS_MMC_WAIT_EPS_CONN_REL_IND_LEN);

        break;
#endif

    case NAS_MML_NET_RAT_TYPE_WCDMA:
    case NAS_MML_NET_RAT_TYPE_GSM:

        /* 迁移状态到等待GU的RRC链路释放 */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_RRC_CONN_REL_IND);

        /* 启动保护定时器 */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL, TI_NAS_MMC_WAIT_RRC_CONN_REL_LEN);

        break;

    default:
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcUserPlmnListReq_PlmnList Unexpected Rat type!");

        break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcGasSysInfo_PlmnList
 功能描述  : 处理GAS的系统消息
 输入参数  : pstGSysInfoInd GAS的系统消息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月24日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2012年6月16日
    作    者   : l00171473
    修改内容   : DTS2012061409086, 收到W或G的系统消息时通知L模
  3.日    期   : 2012年8月14日
    作    者   : t00212959
    修改内容   : DCM定制需求和遗留问题,禁止LTE漫游
  4.日    期   : 2012年12月11日
    作    者   : w00176964
    修改内容   : 收到系统消息接入禁止信息变化则通知MSCC
  5.日    期   : 2014年1月23日
   作    者   : z00161729
   修改内容   : DTS2014012305088:svlte特性tds或l上系统消息后pstransfer:1，注册随机接入失败，ps迁移
                到modem1后tds或l再次驻留mmc收到系统消息判断驻留信息未改变不会给mma发送系统消息导致
                mtc无法上报pstransfer:1,需要在搜网状态机退出后给mma再发次系统消息

  6.日    期   : 2014年5月4日
    作    者   : t00173447
    修改内容   : DTS2014042105390,软银定制需求

*****************************************************************************/
VOS_VOID NAS_MMC_ProcGasSysInfo_PlmnList(
    struct MsgCB                       *pstGSysInfoInd
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

    NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8                enSpecPlmnSearchState;
    /* Added by t00212959 for DCM定制需求和遗留问题, 2012-8-15, begin */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;


    /* 获取LTE能力状态 */
    enLCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();
#endif
    /* Added by t00212959 for DCM定制需求和遗留问题, 2012-8-15, end */

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    PS_MEM_SET(&stOldCsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_SET(&stOldPsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

    /* 更新驻留状态 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

    /* Added by t00212959 for DCM定制需求和遗留问题, 2012-8-15, begin */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_RcvGuSysInfoIndSetLteAbility(pstGSysInfoInd, enLCapabilityStatus);
#endif
    /* Added by t00212959 for DCM定制需求和遗留问题, 2012-8-15, end */

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
    NAS_MMC_UpdateNetworkInfo_GasSysInfo(pstGSysInfoInd);

    /* 驻留小区变化或重新搜网时，上报系统消息 */
    enSpecPlmnSearchState = NAS_MMC_GetSpecPlmnSearchState();

    if ((VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
     || (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == enSpecPlmnSearchState))
    {
        /* 主动上报 */
        NAS_MMC_SndMsccSysInfo();

    }

    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_STOP);

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
    NAS_MMC_SndMmGsmSysInfoInd (NAS_MMC_GetCurrentLaiForbbidenType(), VOS_FALSE, pstGSysInfoInd);
    NAS_MMC_SndGmmGsmSysInfoInd (NAS_MMC_GetCurrentLaiForbbidenType(), VOS_FALSE, pstGSysInfoInd);

#if (FEATURE_ON == FEATURE_LTE)

    NAS_MMC_SndLmmGsmSysInfoInd(pstGSysInfoInd);
#endif

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ProcWasSysInfo_PlmnList
 功能描述  : 处理WAS的系统消息
 输入参数  : pstWSysInfoInd WAS的系统消息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月24日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2012年6月16日
    作    者   : l00171473
    修改内容   : DTS2012061409086, 收到W或G的系统消息时通知L模
  3.日    期   : 2012年8月14日
    作    者   : t00212959
    修改内容   : DCM定制需求和遗留问题,禁止LTE漫游
  4.日    期   : 2012年12月11日
    作    者   : w00176964
    修改内容   : 收到系统消息接入禁止信息变化则通知MSCC

  5.日    期   : 2014年1月18日
    作    者   : z00234330
    修改内容   : dts2014011801513,接入层上报的系统消息里面有可能没有携带plmnid,
                 此处判断并没有判断plmnid是否有效
  6.日    期   : 2014年1月23日
    作    者   : z00161729
    修改内容    : DTS2014012305088:svlte特性tds或l上系统消息后pstransfer:1，注册随机接入失败，ps迁移
                到modem1后tds或l再次驻留mmc收到系统消息判断驻留信息未改变不会给mma发送系统消息导致
                mtc无法上报pstransfer:1,需要在搜网状态机退出后给mma再发次系统消息

  7.日    期   : 2014年5月4日
    作    者   : t00173447
    修改内容   : DTS2014042105390,软银定制需求
*****************************************************************************/
VOS_VOID NAS_MMC_ProcWasSysInfo_PlmnList(
    struct MsgCB                       *pstWSysInfoInd
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

    NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8                enSpecPlmnSearchState;

    /* Added by t00212959 for DCM定制需求和遗留问题, 2012-8-15, begin */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;

    /* 获取LTE能力状态 */
    enLCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();
#endif
    /* Added by t00212959 for DCM定制需求和遗留问题, 2012-8-15, end */

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    PS_MEM_SET(&stOldCsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_SET(&stOldPsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

    /* 更新驻留状态 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

    /* Added by t00212959 for DCM定制需求和遗留问题, 2012-8-15, begin */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_RcvGuSysInfoIndSetLteAbility(pstWSysInfoInd,enLCapabilityStatus);
#endif
    /* Added by t00212959 for DCM定制需求和遗留问题, 2012-8-15, end */

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
    NAS_MMC_UpdateNetworkInfo_WasSysInfo(pstWSysInfoInd);

    /* 驻留小区变化或重新搜网时，上报系统消息 */
    enSpecPlmnSearchState = NAS_MMC_GetSpecPlmnSearchState();

    if ((VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
     || (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == enSpecPlmnSearchState))
    {
        /* 主动上报 */
        NAS_MMC_SndMsccSysInfo();

    }

    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_STOP);

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
    NAS_MMC_SndMmWasSysInfoInd (NAS_MMC_GetCurrentLaiForbbidenType(), VOS_FALSE, pstWSysInfoInd);
    NAS_MMC_SndGmmWasSysInfoInd (NAS_MMC_GetCurrentLaiForbbidenType(), VOS_FALSE, pstWSysInfoInd);

#if (FEATURE_ON == FEATURE_LTE)

    NAS_MMC_SndLmmWcdmaSysInfoInd(pstWSysInfoInd);
#endif

    return;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_MMC_ProcLmmSearchCnf_PlmnList
 功能描述  : 处理LMM下的PLMN LIST的结果
 输入参数  : pstLmmPlmnSrchCnf PLMN LIST的结果
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月24日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2012年4月27日
    作    者   : t00212959
    修改内容   : GUL BG项目调整
  3.日    期   : 2012年6月10日
    作    者   : z00161729
    修改内容   : GUL BG项目修改
*****************************************************************************/
VOS_VOID NAS_MMC_ProcLmmSearchCnf_PlmnList(
    LMM_MMC_PLMN_SRCH_CNF_STRU         *pstLmmPlmnSrchCnf
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat;
    RRC_PLMN_ID_LIST_STRU              *pstGuPlmnIdList;
    VOS_UINT32                          ulIndex;

    /* 判断LIST搜网结果 */

    if ( (MMC_LMM_PLMN_SRCH_RLT_LIST_SUCC   != pstLmmPlmnSrchCnf->enRlst)
      && (MMC_LMM_PLMN_SRCH_RLT_LIST_REJ    != pstLmmPlmnSrchCnf->enRlst)
      && (MMC_LMM_PLMN_SRCH_RLT_LIST_NO_RF  != pstLmmPlmnSrchCnf->enRlst) )
    {
        /* 异常打印 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcLmmSearchCnf_PlmnList: Unexpected List Search Result!");

        return;
    }

    /* 停止等待LMM搜网回复的保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_LIST_CNF);


    if (MMC_LMM_PLMN_SRCH_RLT_LIST_NO_RF == pstLmmPlmnSrchCnf->enRlst)
    {
        NAS_MMC_ProcNoRf_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

        return;
    }



    if (MMC_LMM_PLMN_SRCH_RLT_LIST_REJ == pstLmmPlmnSrchCnf->enRlst)
    {
        /* 启动5S周期性尝试定时器*/
        if ( VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
        {
            /* CS业务比如电话或短信引起的接入层list rej需要终止list搜，
                响应业务否则AT口被list请求占用，用户无法发起接听电话或收短信
                L下无法知道是cs业务还是短信，只能根据是否ucEpsServiceConnStatusFlg来判断 */

            /* L下数据连接态可以缓存列表搜索，但存在CS业务时需要立即回复列表搜索失败 */
            if (VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist())
            {
                /* 发送LIST REJ给MSCC */
                NAS_Mmc_SndMsccPlmnListRej();
            }
            else
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST, TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST_LEN);
            }

         }
        else
        {
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST, TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST_LEN);
        }

        /* 发送状态机失败退出的结果 */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                VOS_FALSE,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* 更新的RAT搜索标记 */
    for ( ulIndex = 0; ulIndex < MMC_LMM_MAX_RAT_NUM; ulIndex++)
    {
        if ( MMC_LMM_RAT_LIST_SEARCH_CMPL == pstLmmPlmnSrchCnf->astSearchRatInfo[ulIndex].enListSearchRlt)
        {
            NAS_MMC_SetSearchedFlag_PlmnList((MMC_LMM_RAT_TYPE_ENUM_UINT8)(pstLmmPlmnSrchCnf->astSearchRatInfo[ulIndex].enRat));
        }

    }

    pstGuPlmnIdList   = (RRC_PLMN_ID_LIST_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                   sizeof(RRC_PLMN_ID_LIST_STRU));

    if (VOS_NULL_PTR == pstGuPlmnIdList)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcLmmSearchCnf_PlmnList:ERROR: Memory Alloc Error");
        return;
    }

    /*转换L格式的搜索列表成为GU格式的*/
    NAS_MMC_ConvertLmmPlmnIdListToGUFormat(&(pstLmmPlmnSrchCnf->stPlmnIdList), pstGuPlmnIdList);

    /*保存搜索列表*/
    NAS_MMC_UpdateSearchedPlmnListInfo_PlmnList(pstGuPlmnIdList);
    PS_MEM_FREE(WUEPS_PID_MMC, pstGuPlmnIdList);

    if (VOS_FALSE == NAS_MMC_GetNextSearchingRat_PlmnList(&enRat))
    {
        /* 内部列表搜不上报 */
        if ( VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
        {
            /* 将搜索到的网络进行排序后上报给MSCC */
            NAS_MMC_SndMsccPlmnListCnf_PlmnList();
        }

        /* 发送状态机成功退出的结果 */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_SUCC,
                                (VOS_UINT8)NAS_MMC_IsNeedPlmnSearch_PlmnList(),
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* 向LMM发送挂起请求,迁移状态,启动保护定时器 */
    NAS_MMC_SndSpecRatSuspendReq_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

    /* 向GMM发送搜网指示 */
    NAS_MMC_SndGmmPlmnSchInit();

    /* 向MM发送搜网指示 */
    NAS_MMC_SndMmPlmnSchInit();

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ProcLmmEpsOnlyTauResultInd_PlmnList
 功能描述  : Lmm TAU结果的处理函数
 输入参数  : pstLmmTauIndMsg L的TAU消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月26日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2011年12月14日
    作    者   : w00176964
    修改内容   : V7R1 phaseIV调整:EPS单域注册假流程调整
  3.日    期   : 2011年12月15日
    作    者   : w00167002
    修改内容   : DTS2011121307570: MMC没有维护LMM的EPLMN信息，现在统一调整
                  ATTACH/TAU/DETACH/SERVICE中被拒时EPLMN的维护。
                  将函数名由NAS_MMC_ProcEpsRegFail更改为NAS_MMC_ProcEpsTauRegFail
                  调用TAU的注册原因值表进行处理
  4.日    期   : 2011年12月20日
    作    者   : w00176964
    修改内容   : V7R1 PhaseIV 调整:UT修改NAS_MMC_SetUserSpecPlmnRegisterStatus
                 只在搜网状态机和ON PLMN下进行设置
  5.日    期   : 2012年1月8日
    作    者   : z00161729
    修改内容   : V7R1 phaseIV调整:EPS单域注册假流程调整
  6.日    期   : 2012年2月4日
    作    者   : w00167002
    修改内容   : DTS2011122704039:将注册结果类型以及注册消息传递给处理注册结果
                  函数，扩展注册结果函数的处理能力。
                  additional action值若为无效值NAS_MMC_ADDITIONAL_ACTION_BUTT
                 则不更新当前的additional action
  7.日    期   : 2012年06月01日
    作    者   : sunxibo /46746
    修改内容   : Added for V7R1 C50 CS/PS mode 1
  8.日    期   : 2012年6月8日
    作    者   : l00130025
    修改内容   : DTS2012060702423:Anycell驻留后，注册成功时，没有通知通知APS/CDS消息，无法数传
  9.日    期   : 2012年08月20日
    作    者   : l65478
    修改内容   : DTS2012081703289，手动搜网失败后关机，重新开机注册成功
                   后出服务区后不驻留EPLMN上
  10.日    期   : 2012年8月21日
    作    者   : z00161729
    修改内容   : DCM定制需求和遗留问题修改DTS2012090401249
  11.日    期   : 2012年09月12日
     作    者   : z00161729
     修改内容  : DTS2012082904888：cs ps mode1，on plmn、plmn list、bg plmn search状态机在eps only注册成功未调用NAS_MMC_IsNeedDisableL_EpsOnlyRegSucc判断是否需要disable lte
  12.日    期   : 2012年12月6日
     作    者   : s00217060
     修改内容   : DTS2012120410842:注册成功时，需要删除ForbPlmn,ForbGprs等信息
  13.日    期   : 2013年05月08日
     作    者   : s46746
     修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  14.日    期   : 2013年12月10日
      作    者  : w00176964
      修改内容  : VoLTE_PhaseIII 项目:修改Disable L模的逻辑
  15.日    期   : 2014年5月6日
     作    者   : z00161729
     修改内容   : DTS2014050602850:l下联合注册eps成功，cs注册被#18拒绝，disable lte到gu下搜网注册成功，后指定搜l cs注册被#18拒绝的网络，l发起eps单域注册成功，mmc没有disable lte
  16.日    期   : 2014年5月5日
     作    者   : w00242748
     修改内容   : DTS2014043000311:注册状态服务状态不一致，将MMC中报服务状态的场景，都加
                  注册状态的上报。
  17.日    期   : 2014年5月14日
     作    者   : w00242748
     修改内容   : DTS2014051206381:枚举值使用不对
  18.日    期   : 2015年4月18日
     作    者   : z00161729
     修改内容   : 24301 R11 CR升级项目修改
  19.日    期   : 2015年02月11日
     作    者   : l00305157
     修改内容   : Service_State_Optimize_PhaseII 项目修改
                    MMC接收到LMM模块注册结果(EPS ONLY)成功，上报注册状态
  20.日    期   : 2015年06月09日
     作    者   : l00305157
     修改内容   : Service_State_Optimize_PhaseII 项目修改
                    MMC接收到LMM模块注册结果，先更新EPLMN LIST，在处理注册状态的上报
 21.日    期   : 2015年10月14日
    作    者   : c00318887
    修改内容   : DTS2015082002854: 漫游标记不准
*****************************************************************************/
VOS_VOID  NAS_MMC_ProcLmmEpsOnlyTauResultInd_PlmnList(
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
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsRegAdditionalAction;
    
    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));

    NAS_MMC_ConverTauResultToMMLCause(pstLmmTauIndMsg,&enRegRsltCause);

    if (MMC_LMM_TAU_RSLT_SUCCESS == pstLmmTauIndMsg->ulTauRst)
    {
        enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;

        NAS_MMC_SaveRegRsltCtx(LMM_MMC_TAU_RESULT_IND, pstLmmTauIndMsg);


        /*注意: 需要先更新EPLMN LIST，在处理注册状态的上报,因为NAS_MMC_UpdatePsRegStatePsRegSucc()函数中会根据EPLMN LIST上报注册状态 */
        /* 更新EPLMN */
        if (VOS_TRUE == pstLmmTauIndMsg->bitOpEplmn)
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
        /* 此处更新CS addition原因是联合TAU仅EPS成功时,LMM启动T3411再次尝试TAU过程中,
           用户Detach CS,LMM会直接报TAU成功,不再尝试联合TAU */
        NAS_MMC_SetCsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON);

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
        NAS_MMC_SetPsRegAdditionalAction_PlmnList(enAdditionalAction);
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

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcLmmTauResultInd_PlmnList
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
VOS_VOID  NAS_MMC_ProcLmmTauResultInd_PlmnList(
    LMM_MMC_TAU_RESULT_IND_STRU        *pstLmmTauIndMsg
)
{
    switch (pstLmmTauIndMsg->ulReqType)
    {
        case MMC_LMM_COMBINED_TA_LA_UPDATING:
        case MMC_LMM_COMBINED_TA_LA_WITH_IMSI:
        case MMC_LMM_CS_PS_PERIODIC_UPDATING:

            /* 处理lmm的联合tau结果 */
            NAS_MMC_ProcLmmCombinedTauResultInd_PlmnList(pstLmmTauIndMsg);
            break;

        case MMC_LMM_TA_UPDATING:
        case MMC_LMM_PS_PERIODIC_UPDATING:

            /* 处理lmm的非联合tau，EPS only注册的结果 */
            NAS_MMC_ProcLmmEpsOnlyTauResultInd_PlmnList(pstLmmTauIndMsg);
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcLmmTauResultInd_PlmnList:Unexpected tau req type!");
            break;

    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcLmmCombinedAttachInd_PlmnList
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
  3.日    期   : 2011年12月5日
    作    者   : z00161729
    修改内容   : V7R1 phaseIV修改合并原NAS_MMC_HPLMN_REG_REJ_STRU和NAS_MMC_PLMN_REG_INFO_STRU
  4.日    期   : 2011年12月13日
    作    者   : z00161729
    修改内容   : DTS2011121302231:attach被拒#9/#10按协议应该按other cause处理
  5.日    期   : 2011年12月20日
    作    者   : w00176964
    修改内容   : V7R1 PhaseIV 调整:UT修改NAS_MMC_SetUserSpecPlmnRegisterStatus
                 只在搜网状态机和ON PLMN下进行设置
  6.日    期   : 2012年2月4日
    作    者   : w00167002
    修改内容   : DTS2011122704039:将注册结果类型以及注册消息传递给处理注册结果
                  函数，扩展注册结果函数的处理能力。
                  additional action值若为无效值NAS_MMC_ADDITIONAL_ACTION_BUTT
                  则不更新当前的additional action
  7.日    期   : 2012年06月01日
    作    者   : sunxibo /46746
    修改内容   : Added for V7R1 C50 CS/PS mode 1
  8.日    期   : 2012年08月20日
    作    者   : l65478
    修改内容   : DTS2012081703289，手动搜网失败后关机，重新开机注册成功
                   后出服务区后不驻留EPLMN上
  9.日    期   : 2012年8月21日
    作    者   : z00161729
    修改内容   : DCM定制需求和遗留问题修改DTS2012090401249
 10.日    期   : 2014年5月5日
    作    者   : w00242748
    修改内容   : DTS2014043000311:注册状态服务状态不一致，将MMC中报服务状态的场景，都加
                 注册状态的上报。
*****************************************************************************/
VOS_VOID  NAS_MMC_ProcLmmCombinedAttachInd_PlmnList(
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
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcLmmCombinedAttachInd_PlmnList:Unexpected attach result!");
            enPsAdditionalAction = NAS_MMC_GetPsRegAdditionalAction_PlmnList();
            enCsAdditionalAction = NAS_MMC_GetCsRegAdditionalAction_PlmnList();
            break;

    }

    /* AdditionalAction有效，更新EPS的下一步的动作类型 */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enPsAdditionalAction )
    {
        NAS_MMC_SetPsRegAdditionalAction_PlmnList(enPsAdditionalAction);
    }

    /* AdditionalAction有效，更新CS的下一步的动作类型 */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enCsAdditionalAction )
    {
        NAS_MMC_SetCsRegAdditionalAction_PlmnList(enCsAdditionalAction);
    }

    if (VOS_TRUE == NAS_MMC_IsNeedSndEplmn())
    {
        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, begin */
        pstEquPlmnInfo       = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildSndLmmEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndLmmEquPlmnReq(&stSndEquPlmnInfo);
        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, end */

        NAS_MMC_SndOmEquPlmn();

        /* 通知CSS GEO信息 */
        NAS_MMC_SndCssCurrGeoInd(VOS_TRUE, stSndEquPlmnInfo.ucEquPlmnNum, stSndEquPlmnInfo.astEquPlmnAddr);
    }


    NAS_MMC_UpdateUserSpecPlmnRegisterStatus(enPsRegRsltCause);

    return;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcLmmCombinedTauResultInd_PlmnList
 功能描述  : Lmm 的联合TAU结果的处理函数
 输入参数  : pstLmmTauIndMsg L的TAU消息
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
  6.日    期   : 2012年06月01日
    作    者   : sunxibo /46746
    修改内容   : Added for V7R1 C50 CS/PS mode 1
  7.日    期   : 2012年6月4日
    作    者   : z00161729
    修改内容   : V7R1C50 GUL BG搜网将圈复杂度
  8.日    期   : 2012年08月20日
    作    者   : l65478
    修改内容   : DTS2012081703289，手动搜网失败后关机，重新开机注册成功
                   后出服务区后不驻留EPLMN上
  9.日    期   : 2012年8月21日
    作    者   : z00161729
    修改内容   : DCM定制需求和遗留问题修改DTS2012090401249
*****************************************************************************/
VOS_VOID  NAS_MMC_ProcLmmCombinedTauResultInd_PlmnList(
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
        NAS_MMC_SetPsRegAdditionalAction_PlmnList(enPsAdditionalAction);
    }

    /* AdditionalAction有效，更新CS的下一步的动作类型 */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enCsAdditionalAction )
    {
        NAS_MMC_SetCsRegAdditionalAction_PlmnList(enCsAdditionalAction);
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


    NAS_MMC_UpdateUserSpecPlmnRegisterStatus(enPsRegRsltCause);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcLmmEpsOnlyAttachResultInd_PlmnList
 功能描述  : Lmm TAU结果的处理函数
 输入参数  : pstLmmTauIndMsg L的attach消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月26日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2011年12月14日
    作    者   : w00176964
    修改内容   : V7R1 phaseIV调整:EPS单域注册假流程调整
  3.日    期   : 2011年12月15日
    作    者   : w00167002
    修改内容   : DTS2011121307570: MMC没有维护LMM的EPLMN信息，现在统一调整
                  ATTACH/TAU/DETACH/SERVICE中被拒时EPLMN的维护。
                  将函数名由NAS_MMC_ProcEpsRegFail更改为NAS_MMC_ProcEpsAttachRegFail
                  调用ATTACH的注册原因值表进行处理
  4.日    期   : 2011年12月20日
    作    者   : w00176964
    修改内容   : V7R1 PhaseIV 调整:UT修改NAS_MMC_SetUserSpecPlmnRegisterStatus
                 只在搜网状态机和ON PLMN下进行设置
  5.日    期   : 2012年1月8日
    作    者   : z00161729
    修改内容   : V7R1 phaseIV调整:EPS单域注册假流程调整
  6.日    期   : 2012年2月4日
    作    者   : w00167002
    修改内容   : DTS2011122704039:将注册结果类型以及注册消息传递给处理注册结果
                  函数，扩展注册结果函数的处理能力。
                  additional action值若为无效值NAS_MMC_ADDITIONAL_ACTION_BUTT
                 则不更新当前的additional action
  7.日    期   : 2012年06月01日
    作    者   : sunxibo /46746
    修改内容   : Added for V7R1 C50 CS/PS mode 1
  8.日    期   : 2012年6月4日
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
     修改内容   : DTS2012082904888：cs ps mode1，on plmn、plmn list、bg plmn search状态机在eps only注册成功未调用NAS_MMC_IsNeedDisableL_EpsOnlyRegSucc判断是否需要disable lte
  13.日    期   : 2012年12月6日
     作    者   : s00217060
     修改内容   : DTS2012120410842:注册成功时，需要删除ForbPlmn,ForbGprs等信息
  14.日    期   : 2013年05月08日
     作    者   : s46746
     修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  15.日    期   : 2013年12月10日
     作    者   : w00176964
     修改内容   : VoLTE_PhaseIII 项目:修改Disable L模的逻辑
  16.日    期   : 2014年5月6日
     作    者   : z00161729
     修改内容   : DTS2014050602850:l下联合注册eps成功，cs注册被#18拒绝，disable lte到gu下搜网注册成功，后指定搜l cs注册被#18拒绝的网络，l发起eps单域注册成功，mmc没有disable lte
  17.日    期   : 2014年5月5日
     作    者   : w00242748
     修改内容   : DTS2014043000311:注册状态服务状态不一致，将MMC中报服务状态的场景，都加
                  注册状态的上报。
  18.日    期   : 2015年4月18日
     作    者   : z00161729
     修改内容   : 24301 R11 CR升级项目修改
  19.日    期   : 2015年02月11日
     作    者   : l00305157
     修改内容   : Service_State_Optimize_PhaseII 项目修改
                    MMC接收到LMM模块注册结果ATTACH (EPS ONLY)成功，上报注册状态
  20.日    期   : 2015年06月09日
     作    者   : l00305157
     修改内容   : Service_State_Optimize_PhaseII 项目修改
                    MMC接收到LMM模块注册结果，先更新EPLMN LIST，在处理注册状态的上报
 21.日    期   : 2015年10月14日
    作    者   : c00318887
    修改内容   : DTS2015082002854: 漫游标记不准
*****************************************************************************/
VOS_VOID  NAS_MMC_ProcLmmEpsOnlyAttachResultInd_PlmnList(
    LMM_MMC_ATTACH_IND_STRU            *pstLmmAttachIndMsg
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

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));

    NAS_MMC_ConverLmmAttachRsltToMMLCause(pstLmmAttachIndMsg, &enRegRsltCause);

    if (MMC_LMM_ATT_RSLT_SUCCESS == pstLmmAttachIndMsg->ulAttachRslt)
    {
        enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;

        NAS_MMC_SaveRegRsltCtx(LMM_MMC_ATTACH_IND, pstLmmAttachIndMsg);

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
        NAS_MMC_SetPsRegAdditionalAction_PlmnList(enAdditionalAction);
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

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ProcLmmAttachInd_PlmnList
 功能描述  : Lmm TAU结果的处理函数
 输入参数  : pstLmmTauIndMsg L的attach消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月30日
    作    者   : z00161729
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_MMC_ProcLmmAttachInd_PlmnList(
    LMM_MMC_ATTACH_IND_STRU            *pstLmmAttachIndMsg
)
{
    switch (pstLmmAttachIndMsg->ulReqType)
    {
        case MMC_LMM_ATT_TYPE_COMBINED_EPS_IMSI:

            /* 处理lmm的联合attach结果 */
            NAS_MMC_ProcLmmCombinedAttachInd_PlmnList(pstLmmAttachIndMsg);
            break;

        case MMC_LMM_ATT_TYPE_EPS_ONLY:

            /* 处理lmm的非联合attach，EPS only注册的结果 */
            NAS_MMC_ProcLmmEpsOnlyAttachResultInd_PlmnList(pstLmmAttachIndMsg);
            break;

        case MMC_LMM_ATT_TYPE_EPS_EMERGENCY:

            /* 暂不支持未实现 */
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcLmmAttachInd_PlmnList:Unsupported attach req type!");
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcLmmAttachInd_PlmnList:Unexpected attach req type!");
            break;

    }

    return;
}

#endif

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcNoRf_PlmnList
 功能描述  : 处理NO RF的场景
 输入参数  : enCurRat------当前接入技术
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月24日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2015年9月18日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_VOID NAS_MMC_ProcNoRf_PlmnList(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat
)
{
    /* 驻留态时,RRC通知NAS当前LIST 搜网结果为NO RF时,后续RRC会进入非驻留态,
       并发起搜网;非驻留态不会 */
    if (NAS_MMC_AS_CELL_NOT_CAMP_ON == NAS_MMC_GetAsCellCampOn())
    {
        /* 记录NO RF */
        NAS_MML_SetCurrRatRfAvailFlg(enCurRat, VOS_FALSE);

        /* 向MSCC通知当前NO RF信息  */
        NAS_MMC_SndMsccRfAvailInd(VOS_FALSE);

        /* 向RRM发起注册 */
        NAS_MMC_RegisterRrmResourceNtf(enCurRat, RRM_PS_TASK_TYPE_NAS_SEARCH);
    }

    NAS_MMC_SndMsccPlmnListRejMsg_PlmnList();


    /* 发送状态机失败的退出结果 */
    NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_NO_RF_FAIL,
                             VOS_FALSE,
                             NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                             NAS_MMC_GetRegRsltInfo_PlmnList());

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return;
}


#if (FEATURE_ON == FEATURE_CSG)
/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMsccCsgListReq_PlmnList_Init
 功能描述  : 在list搜网的INIT状态,收到MSCC的CSG LIST搜网消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:CSG list搜网消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年10月15日
    作    者   : y00358807
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccCsgListReq_PlmnList_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapStatus;

    /* 获取LTE能力状态 */
    enLteCapStatus = NAS_MML_GetLteCapabilityStatus();
#endif

    /* 保存当前消息为状态机入口消息 */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

#if (FEATURE_ON == FEATURE_LTE)
        /* 设置disable L的标记 */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS == enLteCapStatus)
     || (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == enLteCapStatus))
    {
        NAS_MMC_SetPreLteDisableFlg_PlmnList(VOS_TRUE);
    }
    else
    {
        NAS_MMC_SetPreLteDisableFlg_PlmnList(VOS_FALSE);
    }
#endif

    /* 判断是否需要anycell搜网,需要则设置anycell 搜网标记 */
    if (VOS_TRUE == NAS_MMC_IsNeedAnyCellSrch_PlmnList())
    {
        NAS_MMC_SetAnyCellSrchFlg_PlmnList(VOS_TRUE);
    }

    /* 处理用户LIST搜网请求 */
    NAS_MMC_ProcUserCsgListReq_PlmnList();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiPeriodTryingUserCsgListExpired_PlmnList_Init
 功能描述  : 在list搜网的INIT状态,收到MSCC的周期性尝试CSG LIST搜网定时器超时消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:CSG LIST搜网定时器超时消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年10月15日
    作    者   : y00358807
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiPeriodTryingUserCsgListExpired_PlmnList_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapStatus;

    /* 获取LTE能力状态 */
    enLteCapStatus = NAS_MML_GetLteCapabilityStatus();
#endif

    /* 保存当前消息为状态机入口消息 */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

#if (FEATURE_ON == FEATURE_LTE)
        /* 设置disable L的标记 */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS == enLteCapStatus)
     || (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == enLteCapStatus))
    {
        NAS_MMC_SetPreLteDisableFlg_PlmnList(VOS_TRUE);
    }
    else
    {
        NAS_MMC_SetPreLteDisableFlg_PlmnList(VOS_FALSE);
    }
#endif

    /* 判断是否需要anycell搜网,需要则设置anycell 搜网标记 */
    if (VOS_TRUE == NAS_MMC_IsNeedAnyCellSrch_PlmnList())
    {
        NAS_MMC_SetAnyCellSrchFlg_PlmnList(VOS_TRUE);
    }

    /* 处理用户LIST搜网请求 */
    NAS_MMC_ProcUserCsgListReq_PlmnList();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMsccCsgListAbortReq_PlmnList_WaitCsPsRegRsltInd
 功能描述  : 在CSG list搜网的等待CS/PS的注册结果时,收到LIST ABORT REQ消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:LIST ABORT REQ消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年10月19日
    作    者   : y00358807
    修改内容   : 支持LTE CSG功能新增

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccCsgListAbortReq_PlmnList_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);

    /* 发送csg LIST ABORT CNF */
    NAS_MMC_SndMsccCsgListAbortCnf_PlmnList();

    /* 未开始搜网，此时搜索列表为空,记录当前注册导致的后续addition值，L1 MAIN上
       收到链路释放后根据addition值决定是否触发搜网 */
    NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                            VOS_FALSE,
                            NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                            NAS_MMC_GetRegRsltInfo_PlmnList());

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMsccCsgListAbortReq_PlmnList_WaitGasSysInfoInd
 功能描述  : 在CSG list搜网的等待WAS系统消息时,收到LIST ABORT REQ消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:LIST ABORT REQ消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年10月19日
    作    者   : y00358807
    修改内容   : 支持LTE CSG功能新增

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccCsgListAbortReq_PlmnList_WaitGasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 记录状态机退出标记 */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* 记录通知MSCC结果标记 */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMsccCsgListAbortReq_PlmnList_WaitWasSysInfoInd
 功能描述  : 在CSG list搜网的等待WAS系统消息时,收到LIST ABORT REQ消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:LIST ABORT REQ消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年10月19日
    作    者   : y00358807
    修改内容   : 支持LTE CSG功能新增

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccCsgListAbortReq_PlmnList_WaitWasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 记录状态机退出标记 */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* 记录通知MSCC结果标记 */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvCsgListAbortReq_PlmnList_WaitRrcConnRelInd
 功能描述  : 在CSG list搜网的等待RRC链路释放状态,收到CSG LIST ABORT消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:CSG LIST ABORT消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年10月19日
    作    者   : y00358807
    修改内容   : 支持LTE CSG功能新增

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvCsgListAbortReq_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);

    /* 发送csg list abort cnf */
    NAS_MMC_SndMsccCsgListAbortCnf_PlmnList();

    /* 未开始搜网，用户的LIST搜网定时器超时，此时搜索列表为空
       记录当前注册导致的后续addition值，L1 MAIN上收到链路释放后
       根据addition值决定是否触发搜网 */
    NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                            VOS_FALSE,
                            NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                            NAS_MMC_GetRegRsltInfo_PlmnList());

    /* 退出状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_BuildReportCsgIdList_PlmnList
 功能描述  : 创建上报MSCC的CSG ID列表
 输入参数  : 无
 输出参数  : 最终需要上报列表的排序结果
 返 回 值  : VOS_VOID
 调用函数  : 调用函数保证入参指针不能为空
 被调函数  :
 修改历史      :
  1.日    期   : 2015年10月12日
    作    者   : s00193151
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_VOID NAS_MMC_BuildReportCsgIdList_PlmnList(
    NAS_MSCC_PIF_PLMN_WITH_CSG_ID_INFO_STRU                *pstCsgIdInfoList
)
{
    VOS_UINT32                          ulServiceRslt;

    ulServiceRslt = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_OP_CGS);

    /* 根据LTE-BTR-1-0770，如果是AT&T定制且EF Operator List存在(Service n90可用)，
    只上报Operator List中的CSG ID，如果不存在EF Operator List(卡中项不存在，存在
    但为空不算)，则按照EFAD的值确定是否上报所有的CSG ID */
    if ((VOS_TRUE == NAS_MML_GetOnlyReportOperatorCsgListFlag())
      &&(PS_USIM_SERVICE_AVAILIABLE == ulServiceRslt))
    {
        NAS_MMC_BuildReportCsgIdListInOperatorCsgList_PlmnList(pstCsgIdInfoList);
        return;
    }

    /* 标准协议实现 */
    NAS_MMC_BuildReportCsgIdListAccordingCsgDisplayIndicator_PlmnList(pstCsgIdInfoList);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_BuildReportCsgIdListInOperatorCsgList_PlmnList
 功能描述  : 创建AT&T定制需求需要上报MSCC的CSG ID列表
 输入参数  : 无
 输出参数  : 最终需要上报列表的排序结果
 返 回 值  : VOS_VOID
 调用函数  : 调用函数保证入参指针不能为空
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月12日
    作    者   : s00193151
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_VOID NAS_MMC_BuildReportCsgIdListInOperatorCsgList_PlmnList(
    NAS_MSCC_PIF_PLMN_WITH_CSG_ID_INFO_STRU                *pstCsgIdInfoList
)
{
    VOS_UINT32                                              i;
    NAS_MML_PLMN_ID_STRU                                    stPlmnId;
    NAS_MML_PLMN_WITH_CSG_ID_STRU                           stPlmnCsgId;
    NAS_MMC_CSG_SEARCHED_PLMN_LIST_INFO_STRU               *pstCsgPlmnIdList = VOS_NULL_PTR;
    NAS_MML_CSG_ID_TYPE_ENUM_UINT8                          aenCsgIdType[NAS_MML_MAX_PLMN_CSG_ID_NUM]; /* 用于按序保存相应的CSG类型 */

    /* 局部变量初始化 */
    stPlmnId.ulMcc             = NAS_MML_INVALID_MCC;
    stPlmnId.ulMnc             = NAS_MML_INVALID_MNC;
    stPlmnCsgId.stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
    stPlmnCsgId.stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
    stPlmnCsgId.ulCsgId        = 0;
    PS_MEM_SET(aenCsgIdType,   NAS_MML_CSG_ID_TYPE_BUTT, NAS_MML_MAX_PLMN_CSG_ID_NUM);

    pstCsgPlmnIdList = NAS_MMC_GetCsgSearchedPlmnListInfo_PlmnList();

    /* 创建上报列表的原则为，在Operator list中(非禁止)，且上报顺序为RPLMN->HPLMN->OTHER PLMN，
    此顺序并不考虑当前PLMN是高质量还是低质量，也就是全部都按照此顺序原则进行排，有可能低质量的
    排在高质量的前面，创建列表时不用考虑越界的情况，因为本地状态机上下文保存的最大个数为35，不可能越界 */

    /* 第一次循环先放RPLMN的CSG ID */
    for (i = 0; i < NAS_MML_MIN(pstCsgPlmnIdList->ulTotalPlmnNum, RRC_NAS_MAX_PLMN_CSG_ID_NUM); i++)
    {
        /* 取出i位置的PLMN CSG ID，作为获取CSG ID TYPE的入参 */
        stPlmnCsgId.stPlmnId.ulMcc = pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[i].stPlmnCsgIdWithRat.stPlmnWithRat.stPlmnId.ulMcc;
        stPlmnCsgId.stPlmnId.ulMnc = pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[i].stPlmnCsgIdWithRat.stPlmnWithRat.stPlmnId.ulMnc;
        stPlmnCsgId.ulCsgId        = pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[i].stPlmnCsgIdWithRat.ulCsgId;

        /* 借助本次循环将所有的CSG ID的类型识别出来，下次循环时就可直接使用本次保存的结果 */
        aenCsgIdType[i] = NAS_MMC_GetCsgIdType_PlmnList(&stPlmnCsgId);

        /* 如果在Operator List中的且是RPLMN添加到上报给MSCC的列表中(禁止的先不上报) */
        if ((NAS_MML_CSG_ID_TYPE_IN_OPERATOR_CSG_LIST_NOT_FOBIDDEN == aenCsgIdType[i])
          ||(NAS_MML_CSG_ID_TYPE_IN_ALLOWED_AND_OPERATOR_CSG_LIST == aenCsgIdType[i]))
        {
            stPlmnId.ulMcc = stPlmnCsgId.stPlmnId.ulMcc;
            stPlmnId.ulMnc = stPlmnCsgId.stPlmnId.ulMnc;

            if (VOS_TRUE == NAS_MMC_IsPlmnSameWithRplmn(&stPlmnId))
            {
                /* 加入上报结果CNF列表中 */
                NAS_MMC_AddCsgIdToListCnf_PlmnList(i, aenCsgIdType[i], pstCsgIdInfoList);

                /* 下次循环不再处理此位置的CSG ID */
                aenCsgIdType[i] = NAS_MML_CSG_ID_TYPE_BUTT;
            }
        }
    }

    /* 第二次循环放HPLMN的CSG ID */
    for (i = 0; i < NAS_MML_MIN(pstCsgPlmnIdList->ulTotalPlmnNum, RRC_NAS_MAX_PLMN_CSG_ID_NUM); i++)
    {
        /* 如果在Operator List中且是HPLMN的添加到上报给MSCC的列表中(禁止的先不上报) */
        if ((NAS_MML_CSG_ID_TYPE_IN_OPERATOR_CSG_LIST_NOT_FOBIDDEN == aenCsgIdType[i])
          ||(NAS_MML_CSG_ID_TYPE_IN_ALLOWED_AND_OPERATOR_CSG_LIST == aenCsgIdType[i]))
        {
            stPlmnId.ulMcc = pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[i].stPlmnCsgIdWithRat.stPlmnWithRat.stPlmnId.ulMcc;
            stPlmnId.ulMnc = pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[i].stPlmnCsgIdWithRat.stPlmnWithRat.stPlmnId.ulMnc;

            if (VOS_TRUE == NAS_MML_ComparePlmnIdWithHplmn(&stPlmnId))
            {
                /* 加入上报结果CNF列表中 */
                NAS_MMC_AddCsgIdToListCnf_PlmnList(i, aenCsgIdType[i], pstCsgIdInfoList);

                /* 下次循环不再处理此位置的CSG ID */
                aenCsgIdType[i] = NAS_MML_CSG_ID_TYPE_BUTT;
            }
        }
    }

    /* 第三次循环放其他PLMN的CSG ID */
    for (i = 0; i < NAS_MML_MIN(pstCsgPlmnIdList->ulTotalPlmnNum, RRC_NAS_MAX_PLMN_CSG_ID_NUM); i++)
    {
        /* 如果在Operator List中的添加到上报给MSCC的列表中(禁止的先不上报) */
        if ((NAS_MML_CSG_ID_TYPE_IN_OPERATOR_CSG_LIST_NOT_FOBIDDEN == aenCsgIdType[i])
          ||(NAS_MML_CSG_ID_TYPE_IN_ALLOWED_AND_OPERATOR_CSG_LIST == aenCsgIdType[i]))
        {
            /* 加入上报结果CNF列表中 */
            NAS_MMC_AddCsgIdToListCnf_PlmnList(i, aenCsgIdType[i], pstCsgIdInfoList);

            /* 下次循环不再处理此位置的CSG ID */
            aenCsgIdType[i] = NAS_MML_CSG_ID_TYPE_BUTT;
        }
    }

    /* 其他不在operator list的不上报 */
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_BuildReportCsgIdListAccordingCsgDisplayIndicator_PlmnList
 功能描述  : 创建标准协议要求需要上报MSCC的CSG ID列表
 输入参数  : 无
 输出参数  : 最终需要上报列表的排序结果
 返 回 值  : VOS_VOID
 调用函数  : 调用函数保证入参指针不能为空
 被调函数  :
 修改历史      :
  1.日    期   : 2015年10月12日
    作    者   : s00193151
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_VOID NAS_MMC_BuildReportCsgIdListAccordingCsgDisplayIndicator_PlmnList(
    NAS_MSCC_PIF_PLMN_WITH_CSG_ID_INFO_STRU                *pstCsgIdInfoList
)
{
    VOS_UINT32                                              i;
    NAS_MML_CSG_ID_TYPE_ENUM_UINT8                          enCsgIdType;
    NAS_MML_PLMN_WITH_CSG_ID_STRU                           stPlmnCsgId;
    NAS_MMC_CSG_SEARCHED_PLMN_LIST_INFO_STRU               *pstCsgPlmnIdList = VOS_NULL_PTR;
    NAS_MML_CSG_ID_TYPE_ENUM_UINT8                          aenCsgIdType[NAS_MML_MAX_PLMN_CSG_ID_NUM]; /* 用于按序保存相应的CSG类型 */

    /* 局部变量初始化 */
    enCsgIdType                = NAS_MML_CSG_ID_TYPE_BUTT;
    stPlmnCsgId.stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
    stPlmnCsgId.stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
    stPlmnCsgId.ulCsgId        = 0;
    PS_MEM_SET(aenCsgIdType,   NAS_MML_CSG_ID_TYPE_BUTT, NAS_MML_MAX_PLMN_CSG_ID_NUM);

    pstCsgPlmnIdList = NAS_MMC_GetCsgSearchedPlmnListInfo_PlmnList();

    /* 创建上报列表的原则为，卡中指示可以显示，上报顺序为ALLOWED LIST->OPERATOR LIST->AVAILABLE LIST，
    此顺序并不考虑当前PLMN是高质量还是低质量，也就是全部都按照此顺序原则进行排，有可能低质量的
    排在高质量的前面，创建列表时不用考虑越界的情况，因为本地状态机上下文保存的最大个数为35，不可能越界 */

    /* 遍历PLMN LIST状态机上下文中保存的搜索到的CSG PLMN ID */
    for (i = 0; i < NAS_MML_MIN(pstCsgPlmnIdList->ulTotalPlmnNum, RRC_NAS_MAX_PLMN_CSG_ID_NUM); i++)
    {
        /* 初始化临时变量PLMN+CSG ID的值为当前表中对应项的值 */
        stPlmnCsgId.stPlmnId.ulMcc = pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[i].stPlmnCsgIdWithRat.stPlmnWithRat.stPlmnId.ulMcc;
        stPlmnCsgId.stPlmnId.ulMnc = pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[i].stPlmnCsgIdWithRat.stPlmnWithRat.stPlmnId.ulMnc;
        stPlmnCsgId.ulCsgId        = pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[i].stPlmnCsgIdWithRat.ulCsgId;

        /* 获取CSG ID类型 */
        enCsgIdType  = NAS_MMC_GetCsgIdType_PlmnList(&stPlmnCsgId);

        /* 如果卡中指示不用上报，直接跳过此CSG ID */
        if (VOS_TRUE != NAS_MMC_IsSpecCsgIdDisplayIndicatorNeedReport_PlmnList(&stPlmnCsgId, enCsgIdType))
        {
            /* 对应数组单元aenCsgIdType[i] = NAS_MML_CSG_ID_TYPE_BUTT，也就是没有类型 */
            continue;
        }

        /* 卡中指示可以上报，保存CSG ID类型 */
        if (NAS_MML_MAX_PLMN_CSG_ID_NUM > i)
        {
            aenCsgIdType[i] = enCsgIdType;
        }
    }

    /* 向最终上报MSCC的列表中添加Allowed List */
    for (i = 0; i < NAS_MML_MAX_PLMN_CSG_ID_NUM; i++)
    {
        if ((NAS_MML_CSG_ID_TYPE_IN_ALLOWED_CSG_LIST == aenCsgIdType[i])
          ||(NAS_MML_CSG_ID_TYPE_IN_ALLOWED_AND_OPERATOR_CSG_LIST == aenCsgIdType[i]))
        {
            /* 加入上报结果CNF列表中 */
            NAS_MMC_AddCsgIdToListCnf_PlmnList(i, aenCsgIdType[i], pstCsgIdInfoList);

            /* 下次循环不再处理此位置的CSG ID */
            aenCsgIdType[i] = NAS_MML_CSG_ID_TYPE_BUTT;
        }
    }

    /* 向最终上报MSCC的列表中添加Operator List */
    for (i = 0; i < NAS_MML_MAX_PLMN_CSG_ID_NUM; i++)
    {
        if ((NAS_MML_CSG_ID_TYPE_IN_OPERATOR_CSG_LIST_NOT_FOBIDDEN == aenCsgIdType[i])
          ||(NAS_MML_CSG_ID_TYPE_IN_OPERATOR_CSG_LIST_FOBIDDEN == aenCsgIdType[i]))
        {
            /* 加入上报结果CNF列表中 */
            NAS_MMC_AddCsgIdToListCnf_PlmnList(i, aenCsgIdType[i], pstCsgIdInfoList);

            /* 下次循环不再处理此位置的CSG ID */
            aenCsgIdType[i] = NAS_MML_CSG_ID_TYPE_BUTT;
        }
    }

    /* 向最终上报MSCC的列表中添加Available List */
    for (i = 0; i < NAS_MML_MAX_PLMN_CSG_ID_NUM; i++)
    {
        if (NAS_MML_CSG_ID_TYPE_NOT_IN_ALLOWED_AND_OPERATOR_CSG_LIST == aenCsgIdType[i])
        {
            /* 加入上报结果CNF列表中 */
            NAS_MMC_AddCsgIdToListCnf_PlmnList(i, aenCsgIdType[i], pstCsgIdInfoList);

            /* 下次循环不再处理此位置的CSG ID */
            aenCsgIdType[i] = NAS_MML_CSG_ID_TYPE_BUTT;
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitWasCsgListSearchCnf
 功能描述  : 在CSG List搜网的等待WAS的搜网回复时,收到打断消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年9月7日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitWasCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止等待WAS csg list搜网结果的保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_CSG_LIST_SEARCH_CNF);

    /* 记录状态机退出标记 */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* 发送停止搜网请求,迁移状态,启动保护定时器 */
    NAS_MMC_SndSpecRatCsgListSearchStopReq_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMsccCsgListAbortReq_PlmnList_WaitWasCsgListSearchCnf
 功能描述  : 在CSG List搜网的等待WAS的搜网回复时,收到csg list abort消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年9月7日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccCsgListAbortReq_PlmnList_WaitWasCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止等待WAS csg list搜网结果的保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_CSG_LIST_SEARCH_CNF);

    /* 记录状态机退出标记 */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* 设置通知MSCC回复标记 */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_TRUE);

    /* 向WAS发送停止搜网请求,迁移状态,启动保护定时器 */
    NAS_MMC_SndSpecRatCsgListSearchStopReq_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmCsgListSrchCnf_PlmnList_WaitWasCsgListSearchCnf
 功能描述  : 在CSG List搜网的等待WAS的搜网回复时,收到csg list结果消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年9月7日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmCsgListSrchCnf_PlmnList_WaitWasCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_CSG_LIST_SEARCH_CNF_STRU      *pstPlmnSearchcnf = VOS_NULL_PTR;

    pstPlmnSearchcnf = (RRMM_CSG_LIST_SEARCH_CNF_STRU*)pstMsg;

    /* 停止等待WAS csg list搜网回复的保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_CSG_LIST_SEARCH_CNF);

    /* 处理CSG LIST的结果 */
    NAS_MMC_ProcRrmmCsgListSearchCnf_PlmnList(pstPlmnSearchcnf);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmRelInd_PlmnList_WaitWasCsgListSearchCnf
 功能描述  : 在CSG List搜网的等待WAS的搜网回复时,收到rel ind消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年9月7日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmRelInd_PlmnList_WaitWasCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_REL_IND_STRU                  *pstRrmmRelIndMsg    = VOS_NULL_PTR;

    pstRrmmRelIndMsg = (RRMM_REL_IND_STRU *)pstMsg;

    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvRrMmRelInd_PlmnList_WaitWasCsgListSearchCnf Enter!");

    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_CSG_LIST_SEARCH_CNF);

    if (RRC_REL_CAUSE_NO_RF == pstRrmmRelIndMsg->ulRelCause)
    {
        NAS_MMC_ProcNoRf_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);

        return VOS_TRUE;
    }

    /* 发送状态机退出结果 */
    NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                            VOS_FALSE,
                            NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                            NAS_MMC_GetRegRsltInfo_PlmnList());

    /* 启动5S周期性尝试CSG LIST搜网定时器 */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH, TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH_LEN);

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmSysInfoInd_PlmnList_WaitWasCsgListSearchCnf
 功能描述  : 在CSG List搜网的等待WAS的搜网回复时,收到系统消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年9月7日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmSysInfoInd_PlmnList_WaitWasCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 更新驻留信息，并转发系统消息 */
    NAS_MMC_ProcWasSysInfo_PlmnList(pstMsg);

    /* 不迁移状态 */
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitWasPlmnListCnfExpired_PlmnList_WaitWasCsgListSearchCnf
 功能描述  : 在CSG List搜网的等待WAS的搜网回复时,等搜网回复定时器超时消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年9月7日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiWaitWasCsgListCnfExpired_PlmnList_WaitWasCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_SetSearchedFlag_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);
#endif

    /* 向WAS发送停止搜网请求,迁移状态,启动保护定时器 */
    NAS_MMC_SndSpecRatCsgListSearchStopReq_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmAreaLostInd_PlmnList_WaitAsCsgListSearchCnf
 功能描述  : 在CSG List搜网的等待WAS的搜网回复时,收到丢网消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年9月7日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmAreaLostInd_PlmnList_WaitAsCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_SaveLastCampedPlmnWithRat(NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMcc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMnc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.enCampPlmnNetRat);

    /* 清除驻留状态 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);

    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* 当前信号更新 */
    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());

    /* 向MM/GMM/TAF报出服务区流程 */
    NAS_MMC_SndMmCoverageLostInd();

    NAS_MMC_SndGmmCoverageLostInd();

    /* 上报对应的CS/PS服务状态MSCC_MMC_SERVICE_STATUS_NO_SERVICE */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NO_SERVICE);
    NAS_MMC_UpdateRegStateSpecPlmnSearch();

    /* 更新服务状态 */
    NAS_MMC_SndMsccCoverageInd( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );

    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmCsRegResultInd_PlmnList_WaitWasCsgListSearchCnf
 功能描述  : 在CSG List搜网的等待WAS的搜网回复时,收到cs注册结果消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年9月7日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmCsRegResultInd_PlmnList_WaitWasCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMMMC_CS_REG_RESULT_IND_STRU       *pstCsRegRslt = VOS_NULL_PTR;

    pstCsRegRslt = (MMMMC_CS_REG_RESULT_IND_STRU*)pstMsg;

    /* 等待RRC链路释放时如果发生重选，切换以及CCO，可能网络会发生改变，
       状态机退出后收到缓存的注册结果消息，需要判断当前网络是
       否发生改变，发生改变则丢弃当前注册结果 */
    if ( pstCsRegRslt->enNetType != NAS_MML_GetCurrNetRatType())
    {
        return VOS_TRUE;
    }

    /* 处理CS的注册结果 */
    NAS_MMC_ProcCsRegRslt_PlmnList(pstCsRegRslt);

    /* 不迁移状态 */
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGmmPsRegResultInd_PlmnList_WaitWasCsgListSearchCnf
 功能描述  : 在CSG List搜网的等待WAS的搜网回复时,收到ps注册结果消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年9月7日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvGmmPsRegResultInd_PlmnList_WaitWasCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    GMMMMC_PS_REG_RESULT_IND_STRU      *pstPsRegRslt = VOS_NULL_PTR;

    pstPsRegRslt = (GMMMMC_PS_REG_RESULT_IND_STRU*)pstMsg;

    /* 等待RRC链路释放时如果发生重选，切换以及CCO，可能网络会发生改变，
       状态机退出后收到缓存的注册结果消息，需要判断当前网络是
       否发生改变，发生改变则丢弃当前注册结果 */
    if ( pstPsRegRslt->enNetType != NAS_MML_GetCurrNetRatType())
    {
        return VOS_TRUE;
    }

    /* 处理PS的注册结果*/
    NAS_MMC_ProcPsRegRslt_PlmnList(pstPsRegRslt);

    /* 不迁移状态 */
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitGasCsgListSearchCnf
 功能描述  : 在CSG List搜网的等待GAS的搜网回复时,收到abort消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年9月7日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitGasCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止等待GAS csg list搜网结果的保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_CSG_LIST_SEARCH_CNF);

    /* 记录状态机退出标记 */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* 向GAS发送停止搜网请求,迁移状态,启动保护定时器 */
    NAS_MMC_SndSpecRatCsgListSearchStopReq_PlmnList(NAS_MML_NET_RAT_TYPE_GSM);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMsccCsgListAbortReq_PlmnList_WaitGasCsgListSearchCnf
 功能描述  : 在CSG List搜网的等待GAS的搜网回复时,收到csg list abort消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年9月7日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccCsgListAbortReq_PlmnList_WaitGasCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止等待GAS csg list搜网结果的保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_CSG_LIST_SEARCH_CNF);

    /* 记录状态机退出标记 */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* 设置通知MSCC回复标记 */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_TRUE);

    /* 向GAS发送停止搜网请求,迁移状态,启动保护定时器 */
    NAS_MMC_SndSpecRatCsgListSearchStopReq_PlmnList(NAS_MML_NET_RAT_TYPE_GSM);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmCsgListSrchCnf_PlmnList_WaitGasCsgListSearchCnf
 功能描述  : 在CSG List搜网的等待GAS的搜网回复时,收到搜网结果消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年9月7日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmCsgListSrchCnf_PlmnList_WaitGasCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_CSG_LIST_SEARCH_CNF_STRU      *pstPlmnSrchcnf = VOS_NULL_PTR;

    pstPlmnSrchcnf = (RRMM_CSG_LIST_SEARCH_CNF_STRU*)pstMsg;

    /* 停止等待GAS csg list搜网回复的保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_CSG_LIST_SEARCH_CNF);

    /* 处理CSG LIST的结果 */
    NAS_MMC_ProcRrmmCsgListSearchCnf_PlmnList(pstPlmnSrchcnf);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGrrMmSysInfoInd_PlmnList_WaitGasCsgListSearchCnf
 功能描述  : 在CSG List搜网的等待GAS的搜网回复时,收到系统消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年9月7日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvGrrMmSysInfoInd_PlmnList_WaitGasCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 如果收到GAS的系统消息，且目前Utran被Enable，则重新Disable Utran */
    NAS_MMC_RcvGasSysInfoSetUtranCapabilityStatus();

    /* 更新驻留信息，并转发系统消息 */
    NAS_MMC_ProcGasSysInfo_PlmnList(pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitGasCsgListCnfExpired_PlmnList_WaitGasCsgListSearchCnf
 功能描述  : 在CSG List搜网的等待GAS的搜网回复时,等搜网回复定时器超时消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年9月7日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiWaitGasCsgListCnfExpired_PlmnList_WaitGasCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_SetSearchedFlag_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);
#endif

    /* 向GAS发送停止搜网请求,迁移状态,启动保护定时器 */
    NAS_MMC_SndSpecRatCsgListSearchStopReq_PlmnList(NAS_MML_NET_RAT_TYPE_GSM);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmCsRegResultInd_PlmnList_WaitGasCsgListSearchCnf
 功能描述  : 在CSG List搜网的等待GAS的搜网回复时,收到cs注册结果消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年9月7日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmCsRegResultInd_PlmnList_WaitGasCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMMMC_CS_REG_RESULT_IND_STRU       *pstCsRegRslt = VOS_NULL_PTR;

    pstCsRegRslt = (MMMMC_CS_REG_RESULT_IND_STRU*)pstMsg;

    /* 等待RRC链路释放时如果发生重选，切换以及CCO，可能网络会发生改变，
       状态机退出后收到缓存的注册结果消息，需要判断当前网络是
       否发生改变，发生改变则丢弃当前注册结果 */
    if ( pstCsRegRslt->enNetType != NAS_MML_GetCurrNetRatType())
    {
        return VOS_TRUE;
    }

    /* 处理CS的注册结果 */
    NAS_MMC_ProcCsRegRslt_PlmnList(pstCsRegRslt);

    /* 不迁移状态 */
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGmmPsRegResultInd_PlmnList_WaitGasCsgListSearchCnf
 功能描述  : 在CSG List搜网的等待GAS的搜网回复时,收到ps注册结果消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年9月7日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvGmmPsRegResultInd_PlmnList_WaitGasCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    GMMMMC_PS_REG_RESULT_IND_STRU      *pstPsRegRslt = VOS_NULL_PTR;

    pstPsRegRslt = (GMMMMC_PS_REG_RESULT_IND_STRU*)pstMsg;

    /* 等待RRC链路释放时如果发生重选，切换以及CCO，可能网络会发生改变，
       状态机退出后收到缓存的注册结果消息，需要判断当前网络是
       否发生改变，发生改变则丢弃当前注册结果 */
    if ( pstPsRegRslt->enNetType != NAS_MML_GetCurrNetRatType())
    {
        return VOS_TRUE;
    }

    /* 处理PS的注册结果*/
    NAS_MMC_ProcPsRegRslt_PlmnList(pstPsRegRslt);

    /* 不迁移状态 */
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitCsgListWasSuspendCnf
 功能描述  : 在CSG List搜网的等待WAS挂起回复时，收到abort消息处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年9月7日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitCsgListWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 记录需要终止当前状态机标志 */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMsccCsgListAbortReq_PlmnList_WaitCsgListWasSuspendCnf
 功能描述  : 在CSG List搜网的等待WAS挂起回复时，收到csg list abort消息处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年9月7日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccCsgListAbortReq_PlmnList_WaitCsgListWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 记录需要终止当前状态机标志 */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* 设置通知MSCC回复标记 */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmSuspendCnf_PlmnList_WaitCsgListWasSuspendCnf
 功能描述  : 在CSG List搜网的等待WAS挂起回复时，收到挂起回复消息处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年9月7日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmSuspendCnf_PlmnList_WaitCsgListWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_CNF_ST                *pstRrmmSuspendCnf = VOS_NULL_PTR;

    pstRrmmSuspendCnf  = (RRMM_SUSPEND_CNF_ST*)pstMsg;

    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF);

    /* 处理挂起回复结果 */
    NAS_MMC_ProcRrmmCsgListSuspendCnf_PlmnList(pstRrmmSuspendCnf);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitWasSuspendCnfExpired_PlmnList_WaitCsgListWasSuspendCnf
 功能描述  : 在CSG List搜网的等待WAS挂起回复时，等挂起回复定时器超时消息处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年9月7日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiWaitWasSuspendCnfExpired_PlmnList_WaitCsgListWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    enCurRat      = NAS_MML_GetCurrNetRatType();

    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitWasSuspendCnfExpired_PlmnList_WaitCsgListWasSuspendCnf: Timer Expired");

    /* 不可恢复故障，复位 */

    if ( (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
      && (NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat) )
    {
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_WAS_SUSPEND_CNF_EXPIRED);
    }
    else
    {
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_TD_SUSPEND_CNF_EXPIRED);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitCsgListGasSuspendCnf
 功能描述  : 在CSG List搜网的等待GAS挂起回复时，收到abort消息处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年9月7日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitCsgListGasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 记录需要终止当前状态机标志 */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMsccCsgListAbortReq_PlmnList_WaitCsgListGasSuspendCnf
 功能描述  : 在CSG List搜网的等待GAS挂起回复时，收到csg list abort消息处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年9月7日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccCsgListAbortReq_PlmnList_WaitCsgListGasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 记录需要终止当前状态机标志 */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* 设置通知MSCC回复标记 */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmSuspendCnf_PlmnList_WaitCsgListGasSuspendCnf
 功能描述  : 在CSG List搜网的等待GAS挂起回复时，收到挂起回复消息处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年9月7日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmSuspendCnf_PlmnList_WaitCsgListGasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_CNF_ST                *pstRrmmSuspendCnf = VOS_NULL_PTR;

    pstRrmmSuspendCnf  = (RRMM_SUSPEND_CNF_ST*)pstMsg;

    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF);

    /* 处理挂起回复结果 */
    NAS_MMC_ProcRrmmCsgListSuspendCnf_PlmnList(pstRrmmSuspendCnf);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitGasSuspendCnfExpired_PlmnList_WaitCsgListGasSuspendCnf
 功能描述  : 在CSG List搜网的等待GAS挂起回复时，等挂起回复定时器超时消息处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年9月7日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiWaitGasSuspendCnfExpired_PlmnList_WaitCsgListGasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitGasSuspendCnfExpired_PlmnList_WaitCsgListGasSuspendCnf: Timer Expired");

    /* 不可恢复故障，复位 */
    NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_GAS_SUSPEND_CNF_EXPIRED);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitGasCsgListSearchStopCnf
 功能描述  : 在CSG List搜网的等待GAS停止搜网回复时，收到abort消息处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年9月7日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitGasCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 记录需要终止当前状态机标志 */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmPlmnSrchStopCnf_PlmnList_WaitGasCsgListSearchStopCnf
 功能描述  : 在CSG List搜网的等待GAS停止搜网回复时，收到停止搜网回复消息处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年9月7日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmPlmnSrchStopCnf_PlmnList_WaitGasCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF);

    /* 处理搜网停止回复结果 */
    NAS_MMC_ProcRrmmCsgListSearchStopCnf_PlmnList(NAS_MML_NET_RAT_TYPE_GSM);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGrrMmSysInfoInd_PlmnList_WaitGasCsgListSearchStopCnf
 功能描述  : 在CSG List搜网的等待GAS停止搜网回复时，收到系统消息处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年9月7日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvGrrMmSysInfoInd_PlmnList_WaitGasCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 如果收到GAS的系统消息，且目前Utran被Enable，则重新Disable Utran */
    NAS_MMC_RcvGasSysInfoSetUtranCapabilityStatus();

    /* 更新驻留信息，并转发系统消息 */
    NAS_MMC_ProcGasSysInfo_PlmnList(pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMsccCsgListAbortFsmMsg_PlmnList_WaitGasCsgListSearchStopCnf
 功能描述  : 在CSG List搜网的等待GAS停止搜网回复时，收到csg list abort消息处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年9月7日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccCsgListAbortFsmMsg_PlmnList_WaitGasCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 记录需要终止当前状态机标志 */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* 设置通知MSCC回复标记 */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmCsgListSrchCnf_PlmnList_WaitGasCsgListSearchStopCnf
 功能描述  : 在CSG List搜网的等待GAS停止搜网回复时，收到csg list结果消息处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年9月7日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmCsgListSrchCnf_PlmnList_WaitGasCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_CSG_SEARCHED_PLMN_LIST_INFO_STRU               *pstCsgPlmnIdList  = VOS_NULL_PTR;
    RRMM_CSG_LIST_SEARCH_CNF_STRU                          *pstPlmnSrchCnf = VOS_NULL_PTR;

    pstPlmnSrchCnf = (RRMM_CSG_LIST_SEARCH_CNF_STRU*)pstMsg;

    /* LIST搜网回复与停止搜网对冲,NO RF时直接退出LIST搜网流程 */
    if (RRC_NAS_CSG_SEARCH_RLT_NO_RF == pstPlmnSrchCnf->enSearchRlt)
    {
        /* 停止保护定时器 */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF);

        NAS_MMC_ProcNoRf_PlmnList(NAS_MML_NET_RAT_TYPE_GSM);

        return VOS_TRUE;
    }

     /*只有在搜索成功时才进行处理 */
    if (RRC_NAS_CSG_SEARCH_RLT_SUCC != pstPlmnSrchCnf->enSearchRlt)
    {
        return VOS_TRUE;
    }

    /* 保存GU AS上报的列表搜结果到状态机上下文中 */
    NAS_MMC_SaveRrmmCsgListSearchResult_PlmnList(pstPlmnSrchCnf);

    /* 设置L已被搜索过 */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_SetSearchedFlag_PlmnList(MMC_LMM_RAT_LTE);
#endif

    /* 根据CSG搜索的最终结果刷新状态机上下文中的高低质量搜网列表 */
    pstCsgPlmnIdList = NAS_MMC_GetCsgSearchedPlmnListInfo_PlmnList();
    NAS_MMC_UpdateSearchedPlmnListInfoFromCsgSearchResult_PlmnList(pstCsgPlmnIdList);

    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF);

    /* 处理搜网停止回复结果 */
    NAS_MMC_ProcRrmmCsgListSearchStopCnf_PlmnList(NAS_MML_NET_RAT_TYPE_GSM);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitGasStopCnfExpired_PlmnList_WaitGasCsgListSearchStopCnf
 功能描述  : 在CSG List搜网的等待GAS停止搜网回复时，等停止搜网回复定时器超时消息处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年9月7日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiWaitGasStopCnfExpired_PlmnList_WaitGasCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitGasStopCnfExpired_PlmnList_WaitGasCsgListSearchStopCnf: Timer Expired");

    /* 处理搜网停止回复结果 */
    NAS_MMC_ProcRrmmCsgListSearchStopCnf_PlmnList(NAS_MML_NET_RAT_TYPE_GSM);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitWasCsgListSearchStopCnf
 功能描述  : 在CSG List搜网的等待WAS停止搜网回复时，收到abort消息处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年9月7日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitWasCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 记录需要终止当前状态机标志 */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmPlmnSrchStopCnf_PlmnList_WaitWasCsgListSearchStopCnf
 功能描述  : 在CSG List搜网的等待WAS停止搜网回复时，收到停止搜网回复消息处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年9月7日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmPlmnSrchStopCnf_PlmnList_WaitWasCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF);

    /* 处理搜网停止回复结果 */
    NAS_MMC_ProcRrmmCsgListSearchStopCnf_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);

    /* 不迁移状态 */
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmSysInfoInd_PlmnList_WaitWasCsgListSearchStopCnf
 功能描述  : 在CSG List搜网的等待WAS停止搜网回复时，收到系统消息处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年9月7日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmSysInfoInd_PlmnList_WaitWasCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 更新驻留信息，并转发系统消息 */
    NAS_MMC_ProcWasSysInfo_PlmnList(pstMsg);
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvCsgListAbortFsmMsg_PlmnList_WaitWasCsgListSearchStopCnf
 功能描述  : 在CSG List搜网的等待WAS停止搜网回复时，收到csg list abort消息处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年9月7日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvCsgListAbortFsmMsg_PlmnList_WaitWasCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 记录需要终止当前状态机标志 */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* 设置通知MSCC回复标记 */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmCsgListSrchCnf_PlmnList_WaitWasCsgListSearchStopCnf
 功能描述  : 在CSG List搜网的等待WAS停止搜网回复时，收到csg list搜网结果消息处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年9月7日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmCsgListSrchCnf_PlmnList_WaitWasCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_CSG_SEARCHED_PLMN_LIST_INFO_STRU               *pstCsgPlmnIdList  = VOS_NULL_PTR;
    RRMM_CSG_LIST_SEARCH_CNF_STRU                          *pstPlmnSrchCnf = VOS_NULL_PTR;

    pstPlmnSrchCnf = (RRMM_CSG_LIST_SEARCH_CNF_STRU*)pstMsg;

    /* LIST搜网回复与停止搜网对冲,NO RF时直接退出LIST搜网流程 */
    if (RRC_NAS_CSG_SEARCH_RLT_NO_RF == pstPlmnSrchCnf->enSearchRlt)
    {
        /* 停止保护定时器 */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF);

        NAS_MMC_ProcNoRf_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);

        return VOS_TRUE;
    }

     /*只有在搜索成功时才进行处理 */
    if (RRC_NAS_CSG_SEARCH_RLT_SUCC != pstPlmnSrchCnf->enSearchRlt)
    {
        return VOS_TRUE;
    }

    /* 保存GU AS上报的列表搜结果到状态机上下文中 */
    NAS_MMC_SaveRrmmCsgListSearchResult_PlmnList(pstPlmnSrchCnf);

    /* 设置L已被搜索过 */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_SetSearchedFlag_PlmnList(MMC_LMM_RAT_LTE);
#endif

    /* 根据CSG搜索的最终结果刷新状态机上下文中的高低质量搜网列表 */
    pstCsgPlmnIdList = NAS_MMC_GetCsgSearchedPlmnListInfo_PlmnList();
    NAS_MMC_UpdateSearchedPlmnListInfoFromCsgSearchResult_PlmnList(pstCsgPlmnIdList);

    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF);

    /* 处理搜网停止回复结果 */
    NAS_MMC_ProcRrmmCsgListSearchStopCnf_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmRelInd_PlmnList_WaitWasCsgListSearchStopCnf
 功能描述  : 在CSG List搜网的等待WAS停止搜网回复时，收到rel ind消息处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年9月7日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmRelInd_PlmnList_WaitWasCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvRrMmRelInd_PlmnList_WaitWasCsgListSearchStopCnf: ENTERED");

    /* 无需判断原因值 */

    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF);

    /* 状态机退出结果为真 */
    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnList())
    {
        /* 当前是csg列表搜网 */
        if ( VOS_TRUE == NAS_MMC_GetNotifyMsccFlag_PlmnList())
        {
            /* 向MSCC回复csg LIST ABORT CNF */
            NAS_MMC_SndMsccCsgListAbortCnf_PlmnList();
        }
        else
        {
            /* 向MSCC回复csg LIST搜网结果 */
            NAS_MMC_SndMsccCsgListSearchCnf_PlmnList();
        }

        /* 发送状态机ABORT退出结果 */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                                VOS_FALSE,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 发送状态机退出结果 */
    NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                            VOS_FALSE,
                            NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                            NAS_MMC_GetRegRsltInfo_PlmnList());

    /* 启动5S周期性尝试csg LIST搜网定时器 */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH, TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH_LEN);

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitWasStopCnfExpired_PlmnList_WaitWasCsgListSearchStopCnf
 功能描述  : 在CSG List搜网的等待WAS停止搜网回复时，等was停止搜网定时器超时消息处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年9月7日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiWaitWasStopCnfExpired_PlmnList_WaitWasCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitWasStopCnfExpired_PlmnList_WaitWasCsgListSearchStopCnf: Timer Expired");

    /* 处理搜网停止回复结果 */
    NAS_MMC_ProcRrmmCsgListSearchStopCnf_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsCsgList_PlmnList
 功能描述  : 判断当前是否是用户CSG LIST搜网
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  用户CSG LIST搜网
             VOS_FALSE 非CSG LIST搜网
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年9月7日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增

*****************************************************************************/
VOS_UINT32  NAS_MMC_IsCsgList_PlmnList(VOS_VOID)
{
    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg    = VOS_NULL_PTR;

    /* 根据FSM ID获取该FSM 入口消息 */
    pstEntryMsg     = NAS_MMC_GetCurrFsmMsgAddr();

    if ( (ID_MSCC_MMC_CSG_LIST_SEARCH_REQ == NAS_ExtractMsgNameFromEvtType(pstEntryMsg->ulEventType))
      || (TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH == NAS_ExtractMsgNameFromEvtType(pstEntryMsg->ulEventType)))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndMsccCsgListSearchCnf_PlmnList
 功能描述  : 向MSCC发送CSG LIST搜网结果
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年10月21日
    作    者   : y00358807
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccCsgListSearchCnf_PlmnList(VOS_VOID)
{
    MMC_MSCC_CSG_LIST_SEARCH_CNF_STRU  *pstCsgListSrchCnf = VOS_NULL_PTR;

    /* 申请上报结果的内存空间 */
    pstCsgListSrchCnf = (MMC_MSCC_CSG_LIST_SEARCH_CNF_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                    sizeof(MMC_MSCC_CSG_LIST_SEARCH_CNF_STRU));

    if (VOS_NULL_PTR == pstCsgListSrchCnf)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccCsgListSearchCnf_PlmnList:ERROR,Memory Alloc Error");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstCsgListSrchCnf) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MMC_MSCC_CSG_LIST_SEARCH_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstCsgListSrchCnf->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstCsgListSrchCnf->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstCsgListSrchCnf->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstCsgListSrchCnf->MsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstCsgListSrchCnf->MsgHeader.ulLength          = sizeof(MMC_MSCC_CSG_LIST_SEARCH_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstCsgListSrchCnf->MsgHeader.ulMsgName         = ID_MMC_MSCC_CSG_LIST_SEARCH_CNF;

    /* 挑出满足上报条件的CSG ID，创建上报的CSG ID列表 */
    NAS_MMC_BuildReportCsgIdList_PlmnList(&(pstCsgListSrchCnf->stCsgIdInfo));

    /* 向MSCC发送LIST CNF消息 */
    NAS_MMC_SndMsccUserCsgListSearchCnf(pstCsgListSrchCnf);

    PS_MEM_FREE(WUEPS_PID_MMC, pstCsgListSrchCnf);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndMsccCsgListAbortCnf_PlmnList
 功能描述  : 向MSCC发送CSG LIST abort结果
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年10月21日
    作    者   : y00358807
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccCsgListAbortCnf_PlmnList(VOS_VOID)
{
    MMC_MSCC_CSG_LIST_ABORT_CNF_STRU                      *pstCsgListAbortCnf = VOS_NULL_PTR;

    /* 申请上报结果的内存空间 */
    pstCsgListAbortCnf = (MMC_MSCC_CSG_LIST_ABORT_CNF_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                    sizeof(MMC_MSCC_CSG_LIST_ABORT_CNF_STRU));

    if (VOS_NULL_PTR == pstCsgListAbortCnf)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccCsgListAbortCnf_PlmnList:ERROR,Memory Alloc Error");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstCsgListAbortCnf) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MMC_MSCC_CSG_LIST_ABORT_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstCsgListAbortCnf->MsgHeader.ulLength          = sizeof(MMC_MSCC_CSG_LIST_ABORT_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstCsgListAbortCnf->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstCsgListAbortCnf->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstCsgListAbortCnf->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstCsgListAbortCnf->MsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstCsgListAbortCnf->MsgHeader.ulMsgName         = ID_MMC_MSCC_CSG_LIST_ABORT_CNF;

    /* 挑出满足上报条件的CSG ID，创建上报的CSG ID列表 */
    NAS_MMC_BuildReportCsgIdList_PlmnList(&(pstCsgListAbortCnf->stCsgIdInfo));

    /* 向MSCC发送LIST ABORT CNF消息 */
    NAS_MMC_SndMsccUserCsgListAbortCnf(pstCsgListAbortCnf);

    PS_MEM_FREE(WUEPS_PID_MMC, pstCsgListAbortCnf);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndSpecRatCsgListSearchReq_PlmnList
 功能描述  : 向指定的接入技术发送CSG LIST搜网请求
 输入参数  : enRat 指定的接入技术
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年10月15日
    作    者   : y00358807
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_SndSpecRatCsgListSearchReq_PlmnList(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    switch (enRat)
    {
#if (FEATURE_LTE == FEATURE_ON)
        case NAS_MML_NET_RAT_TYPE_LTE:

            NAS_MMC_SndLmmCsgListSearchReq();

            /* 迁移状态到等待LMM的LIST搜网回复 */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_CSG_LIST_STA_WAIT_LMM_CSG_LIST_SEARCH_CNF);

            /* 启动保护定时器 */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_CSG_LIST_SEARCH_CNF, TI_NAS_MMC_WAIT_LMM_CSG_LIST_SEARCH_CNF_LEN);
            break;
#endif

        case NAS_MML_NET_RAT_TYPE_WCDMA:
            NAS_MMC_SndAsCsgListSearchReq(WUEPS_PID_WRR);

            /* 迁移状态到等待WRR的CSG LIST搜网回复 */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_CSG_LIST_STA_WAIT_WAS_CSG_LIST_SEARCH_CNF);

            /* 启动保护定时器 */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_CSG_LIST_SEARCH_CNF, TI_NAS_MMC_WAIT_WAS_CSG_LIST_SEARCH_CNF_LEN);

            break;

        case NAS_MML_NET_RAT_TYPE_GSM:
            NAS_MMC_SndAsCsgListSearchReq(UEPS_PID_GAS);

            /* 迁移状态到等待GAS的CSG LIST搜网回复 */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_CSG_LIST_STA_WAIT_GAS_CSG_LIST_SEARCH_CNF);

            /* 启动保护定时器 */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_CSG_LIST_SEARCH_CNF, TI_NAS_MMC_WAIT_GAS_CSG_LIST_SEARCH_CNF_LEN);
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndSpecRatCsgListSearchReq_PlmnList Unexpected Rat type!");

            break;
    }

    return;
}
/*****************************************************************************
 函 数 名  : NAS_MMC_ProcUserCsgListReq_PlmnList
 功能描述  : 处理用户CSG LIST搜网请求
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年10月15日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_VOID NAS_MMC_ProcUserCsgListReq_PlmnList(VOS_VOID)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;

    enRatType     = NAS_MML_GetCurrNetRatType();

#if (FEATURE_LTE == FEATURE_ON)
    /* 挂起状态下被打断，当前接入技术为BUTT */
    if( NAS_MML_NET_RAT_TYPE_BUTT == NAS_MML_GetCurrNetRatType())
    {
       enRatType = NAS_MML_NET_RAT_TYPE_LTE;
       NAS_MML_SetCurrNetRatType(enRatType);
    }
#endif

    /* 重新初始化NAS_MMC_GetSearchCtrlInfo_PlmnList，只加LTE接入技术 */
    NAS_MMC_InitCsgListSearchRatInfo_PlmnList();

    /* 判断是否需要等待链接释放 */
    if ( VOS_FALSE == NAS_MMC_IsNeedWaitRrcRel_PlmnList() )
    {
        /* 根据不同接入模式,发送LIST搜网请求，迁到等待搜网结果状态并启动保护定时器*/
        if ((NAS_MMC_AS_CELL_CAMP_ON == NAS_MMC_GetAsCellCampOn())
         || (NAS_MML_NET_RAT_TYPE_LTE == enRatType))
        {
            NAS_MMC_SndSpecRatCsgListSearchReq_PlmnList(enRatType);
            return;
        }

        /* gu下非驻留态需要挂起gu到lte下搜网 */
        NAS_MMC_SndSpecRatCsgListSuspendReq_PlmnList(enRatType);

        return;
    }

    /* 需要等待连接释放 */
    switch (NAS_MML_GetCurrNetRatType())
    {
#if (FEATURE_LTE == FEATURE_ON)
        case NAS_MML_NET_RAT_TYPE_LTE:

        /* L下有EPS信令连接被动等待LMM释放链路,
           保持与GU的实现一致 */

        /* 迁移状态到等待LMM的EPS链路释放 */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_EPS_CONN_REL_IND);

        /* 启动保护定时器 */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND, TI_NAS_MMC_WAIT_EPS_CONN_REL_IND_LEN);

        break;
#endif

    case NAS_MML_NET_RAT_TYPE_WCDMA:
    case NAS_MML_NET_RAT_TYPE_GSM:

        /* 迁移状态到等待GU的RRC链路释放 */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_RRC_CONN_REL_IND);

        /* 启动保护定时器 */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL, TI_NAS_MMC_WAIT_RRC_CONN_REL_LEN);

        break;

    default:
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcUserPlmnListReq_PlmnList Unexpected Rat type!");

        break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndSpecRatCsgListSuspendReq_PlmnList
 功能描述  : 向指定的接入技术发送挂起请求
 输入参数  : enRat - 指定的接入技术
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年10月12日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_VOID NAS_MMC_SndSpecRatCsgListSuspendReq_PlmnList(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    switch (enRat)
    {
#if (FEATURE_LTE == FEATURE_ON)
        case NAS_MML_NET_RAT_TYPE_LTE:

            /* 目前只支持LTE CSG,不存在挂起lte的场景 */
            break;
#endif

        case NAS_MML_NET_RAT_TYPE_WCDMA:

            /* 更新驻留状态 */
            NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
            NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

            NAS_MMC_SetAsAnyCampOn(VOS_FALSE);

            /* 向WAS发送挂起请求 */
            NAS_MMC_SndAsSuspendReq(WUEPS_PID_WRR);

            /* 迁移状态到等待WAS的挂起回复 */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_CSG_LIST_STA_WAIT_WAS_SUSPEND_CNF);

            /* 启动保护定时器 */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF, TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF_LEN);

            break;

        case NAS_MML_NET_RAT_TYPE_GSM:

            /* 更新驻留状态 */
            NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
            NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

            NAS_MMC_SetAsAnyCampOn(VOS_FALSE);

            /* 向GAS发送挂起请求 */
            NAS_MMC_SndAsSuspendReq(UEPS_PID_GAS);

            /* 迁移状态到等待GAS的挂起回复 */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_CSG_LIST_STA_WAIT_GAS_SUSPEND_CNF);

            /* 启动保护定时器 */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF, TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF_LEN);

            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndSpecRatCsgListSuspendReq_PlmnList Unexpected Rat type!");

            break;
    }
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndSpecRatCsgListSearchStopReq_PlmnList
 功能描述  : 向指定的接入技术发送停止CSG List搜网请求
 输入参数  : enRat 指定的接入技术
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年10月10日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_VOID NAS_MMC_SndSpecRatCsgListSearchStopReq_PlmnList(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    switch (enRat)
    {
#if (FEATURE_LTE == FEATURE_ON)
        case NAS_MML_NET_RAT_TYPE_LTE:

            /* 向LMM发送停止搜网请求 */
            NAS_MMC_SndLmmPlmnSrchStopReq();

            /* 迁移状态到等待LMM的停止搜网回复 */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_CSG_LIST_STA_WAIT_LMM_CSG_LIST_SEARCH_STOP_CNF);

            /* 启动保护定时器 */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF_LEN);

            break;
#endif

        case NAS_MML_NET_RAT_TYPE_WCDMA:

            /* 向WAS发送停止搜网请求 */
            NAS_MMC_SndAsPlmnSrchStopReq(WUEPS_PID_WRR);

            /* 迁移状态到等待WAS的停止搜网回复 */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_CSG_LIST_STA_WAIT_WAS_CSG_LIST_SEARCH_STOP_CNF);

            /* 启动保护定时器 */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF_LEN);

            break;

        case NAS_MML_NET_RAT_TYPE_GSM:

            /* 向GAS发送停止搜网请求 */
            NAS_MMC_SndAsPlmnSrchStopReq(UEPS_PID_GAS);

            /* 迁移状态到等待GAS的停止搜网回复 */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_CSG_LIST_STA_WAIT_GAS_CSG_LIST_SEARCH_STOP_CNF);

            /* 启动保护定时器 */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF_LEN);

            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndSpecRatCsgListSearchStopReq_PlmnList Unexpected Rat type!");

            break;
    }
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcRrmmCsgListSearchSucc_PlmnList
 功能描述  : 处理CSG PLMN LIST的成功的结果
 输入参数  : pstPlmnSrchCnf PLMN LIST的结果
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年10月12日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增

*****************************************************************************/
VOS_VOID NAS_MMC_ProcRrmmCsgListSearchSucc_PlmnList(
    RRMM_CSG_LIST_SEARCH_CNF_STRU      *pstPlmnSrchCnf
)
{
    NAS_MMC_CSG_SEARCHED_PLMN_LIST_INFO_STRU               *pstCsgPlmnIdList  = VOS_NULL_PTR;

    /* 保存GU AS上报的列表搜结果到状态机上下文中 */
    NAS_MMC_SaveRrmmCsgListSearchResult_PlmnList(pstPlmnSrchCnf);

    /* 设置L已被搜索过 */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_SetSearchedFlag_PlmnList(MMC_LMM_RAT_LTE);
#endif

    /* 根据CSG搜索的最终结果刷新状态机上下文中的高低质量搜网列表 */
    pstCsgPlmnIdList = NAS_MMC_GetCsgSearchedPlmnListInfo_PlmnList();
    NAS_MMC_UpdateSearchedPlmnListInfoFromCsgSearchResult_PlmnList(pstCsgPlmnIdList);

    NAS_MMC_SndMsccCsgListSearchCnf_PlmnList();

    /* CSG LIST搜网过程中,RRC可能出服务区,此时需要设置搜网状态,触发退出LIST搜网后的指定搜网 */
    if (NAS_MMC_AS_CELL_NOT_CAMP_ON == NAS_MMC_GetAsCellCampOn())
    {
        NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);
    }


    /* 发送状态机退出的结果 */
    NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_SUCC,
                            (VOS_UINT8)NAS_MMC_IsNeedPlmnSearch_PlmnList(),
                             NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                             NAS_MMC_GetRegRsltInfo_PlmnList());

    /* 退出状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcRrmmCsgListSuspendCnf_PlmnList
 功能描述  : 处理接入层的挂起回复的结果
 输入参数  : pstRrmmSuspendCnf - 接入层的挂起回复的结果
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年10月12日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增

*****************************************************************************/
VOS_VOID NAS_MMC_ProcRrmmCsgListSuspendCnf_PlmnList(
    RRMM_SUSPEND_CNF_ST                *pstRrmmSuspendCnf
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;
    VOS_UINT32                          ulNeedPlmnSearch;

    enCurRat      = NAS_MML_GetCurrNetRatType();

    if ( MMC_AS_SUSPEND_FAILURE  == pstRrmmSuspendCnf->ucResult )
    {
        /* 单板复位 */

        if ( (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
          && (NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat) )
        {
            NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_WAS_SUSPEND_FAILURE);
        }
        else if ( NAS_MML_NET_RAT_TYPE_GSM == enCurRat )
        {
            NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_GAS_SUSPEND_FAILURE);
        }
        else if ( NAS_MML_NET_RAT_TYPE_LTE == enCurRat)
        {
            NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_LMM_SUSPEND_FAILURE);
        }
        else
        {
            NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_TD_SUSPEND_FAILURE);
        }

        return;
    }

    /* 判断状态机退出标记是否为真，如果为真*/
    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnList())
    {
        /* 接入技术设置为BUTT，后续可以直接向任意模发送搜网请求 */
        NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

        ulNeedPlmnSearch = VOS_FALSE;

        if ( VOS_TRUE == NAS_MMC_GetNotifyMsccFlag_PlmnList())
        {
            /* 向MSCC回复ABORT_CNF */
            NAS_MMC_SndMsccCsgListAbortCnf_PlmnList();

            ulNeedPlmnSearch = VOS_TRUE;
        }
        else
        {
            /* 向MSCC回复csg LIST搜网结果 */
            NAS_MMC_SndMsccCsgListSearchCnf_PlmnList();
        }

        /* 发送状态机ABORT的退出结果 */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                                (VOS_UINT8)ulNeedPlmnSearch,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* 获取不到下一个接入技术 */
    if ( VOS_FALSE == NAS_MMC_GetNextSearchingRat_PlmnList(&enRat))
    {
        /* 异常打印 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcRrmmCsgListSuspendCnf_PlmnList: Get next search rat fail.");

        /* 接入技术设置为BUTT，后续可以直接向任意模发送搜网请求 */
        NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

        /* 当前为用户LIST搜网 */
        if ( VOS_TRUE == NAS_MMC_IsCsgList_PlmnList())
        {
            /* 向MSCC回复ID_MMC_MSCC_CSG_LIST_SEARCH_CNF */
            NAS_MMC_SndMsccCsgListSearchCnf_PlmnList();
        }

        /* 发送状态机退出结果 */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                (VOS_UINT8)NAS_MMC_IsNeedPlmnSearch_PlmnList(),
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* 根据获取的接入技术设置当前接入技术 */
    NAS_MML_SetCurrNetRatType(enRat);

    /* 向下个接入模式发送LIST搜网请求,迁移状态,启动保护定时器 */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(enRat);

}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcRrmmCsgListSearchCnf_PlmnList
 功能描述  : 处理CSG LIST的结果
 输入参数  : pstPlmnSrchCnf - CSG LIST的结果
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年10月12日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增

*****************************************************************************/
VOS_VOID NAS_MMC_ProcRrmmCsgListSearchCnf_PlmnList(
    RRMM_CSG_LIST_SEARCH_CNF_STRU       *pstPlmnSrchCnf
)
{
    /* 判断CSG LIST搜网结果 */
    switch (pstPlmnSrchCnf->enSearchRlt)
    {
        case RRC_NAS_CSG_SEARCH_RLT_REJ:

            /* 启动5S周期性尝试定时器 */
            /* CS业务比如电话或短信引起的接入层list rej需要终止list搜，
                响应业务否则AT口被list请求占用，用户无法发起接听电话或收短信 */
            if (VOS_TRUE == NAS_MML_GetCsServiceExistFlg())
            {
                /* 发送LIST REJ给MSCC */
                NAS_MMC_SndMsccCsgListSearchRej();
            }
            else
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH, TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH_LEN);
            }

            /* 发送状态机失败的退出结果 */
            NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                    VOS_FALSE,
                                    NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                    NAS_MMC_GetRegRsltInfo_PlmnList());

            /* 退出状态机 */
            NAS_MMC_FSM_QuitFsmL2();

            break;

       case RRC_NAS_CSG_SEARCH_RLT_SUCC:

            /* 处理CSG LIST搜网成功的结果 */
            NAS_MMC_ProcRrmmCsgListSearchSucc_PlmnList(pstPlmnSrchCnf);

            break;

       /* 接入层连接态下回复该结果，mmc不再启动5s周期性尝试csg list搜定时器，直接上报失败 */
       case RRC_NAS_CSG_SEARCH_RLT_FAIL:

            /* 发送LIST REJ给MSCC */
            NAS_MMC_SndMsccCsgListSearchRej();

            /* 发送状态机失败的退出结果 */
            NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                    VOS_FALSE,
                                    NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                    NAS_MMC_GetRegRsltInfo_PlmnList());

            /* 退出状态机 */
            NAS_MMC_FSM_QuitFsmL2();
            break;

       case RRC_NAS_CSG_SEARCH_RLT_NO_RF:
            NAS_MMC_ProcNoRf_PlmnList(NAS_MML_GetCurrNetRatType());
            break;

       default:

            /*异常打印*/
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcRrmmCsgListSearchCnf_PlmnList Unexpected List Result!");

            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcRrmmCsgListSearchStopCnf_PlmnList
 功能描述  : 处理接入层的搜网停止回复的结果
 输入参数  : enRatType - 当前接入技术
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年10月12日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_VOID NAS_MMC_ProcRrmmCsgListSearchStopCnf_PlmnList(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNextRatType;
    VOS_UINT32                          ulNeedPlmnSearch;

    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnList())
    {
        ulNeedPlmnSearch = VOS_FALSE;

        if ( VOS_TRUE == NAS_MMC_GetNotifyMsccFlag_PlmnList())
        {
            /* 向MSCC回复ABORT_CNF */
            NAS_MMC_SndMsccCsgListAbortCnf_PlmnList();

            ulNeedPlmnSearch = NAS_MMC_IsNeedPlmnSearch_PlmnList();
        }
        else
        {
            /* 向MSCC回复csg LIST搜网结果 */
            NAS_MMC_SndMsccCsgListSearchCnf_PlmnList();
        }

        /* 发送状态机ABORT退出结果 */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                                (VOS_UINT8)ulNeedPlmnSearch,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* 获取不到下一个未搜索的接入模式 */
    if ( VOS_FALSE == NAS_MMC_GetNextSearchingRat_PlmnList(&enNextRatType))
    {
        /* 将搜索到的网络进行排序后上报给MSCC */
        NAS_MMC_SndMsccCsgListSearchCnf_PlmnList();

        /* 发送状态机失败退出的结果 */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                (VOS_UINT8)NAS_MMC_IsNeedPlmnSearch_PlmnList(),
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* 向当前接入技术发送挂起请求,迁移状态,启动保护定时器 */
    NAS_MMC_SndSpecRatCsgListSuspendReq_PlmnList(enRatType);

    /* 向GMM发送搜网指示 */
    NAS_MMC_SndGmmPlmnSchInit();

    /* 向MM发送搜网指示 */
    NAS_MMC_SndMmPlmnSchInit();

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SaveRrmmCsgListSearchResult_PlmnList
 功能描述  : 保存RRMM CSG PLMN LIST的成功的结果到PLMN LIST状态机上下文中
 输入参数  : pstPlmnSrchCnf CSG LIST的结果消息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  : 调用函数保证入参指针不能为空
 被调函数  :
 修改历史      :
  1.日    期   : 2015年10月12日
    作    者   : s00193151
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_VOID NAS_MMC_SaveRrmmCsgListSearchResult_PlmnList(
    RRMM_CSG_LIST_SEARCH_CNF_STRU       *pstPlmnSrchCnf
)
{
    NAS_MMC_CSG_SEARCHED_PLMN_LIST_INFO_STRU               *pstCsgPlmnIdList = VOS_NULL_PTR;

    pstCsgPlmnIdList = NAS_MMC_GetCsgSearchedPlmnListInfo_PlmnList();

    /* 参数检查和保护处理 */
    pstCsgPlmnIdList->ulTotalPlmnNum = NAS_MML_MIN(RRC_NAS_MAX_PLMN_CSG_ID_NUM,
                                        pstPlmnSrchCnf->stCsgListSearchedResult.ulTotalPlmnNum);

    pstCsgPlmnIdList->ulHighPlmnNum = NAS_MML_MIN(pstCsgPlmnIdList->ulTotalPlmnNum,
                                        pstPlmnSrchCnf->stCsgListSearchedResult.ulHighPlmnNum);

    /* 拷贝保存列表 */
    PS_MEM_CPY(pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList,
                    pstPlmnSrchCnf->stCsgListSearchedResult.astCsgListSearchedPlmnInfoList,
                    (pstCsgPlmnIdList->ulTotalPlmnNum) * sizeof(RRMM_CSG_LIST_SEARCHED_PLMN_INFO_STRU));

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetCsgIdType_PlmnList
 功能描述  : 获取此PLMN CSG ID的类型，看在哪个表中
 输入参数  : RRMM_PLMN_CSG_ID_WITH_RAT_STRU   CSG ID+PLMN
 输出参数  : 无
 返 回 值  : NAS_MML_CSG_ID_TYPE_ENUM_UINT8   类型
 调用函数  : 调用函数保证入参指针不能为空
 被调函数  :
 修改历史      :
  1.日    期   : 2015年10月12日
    作    者   : s00193151
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
NAS_MML_CSG_ID_TYPE_ENUM_UINT8 NAS_MMC_GetCsgIdType_PlmnList(
    NAS_MML_PLMN_WITH_CSG_ID_STRU      *pstPlmnCsgId
)
{
    NAS_MML_PLMN_WITH_CSG_ID_LIST_STRU *pstAllowedList  = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_CSG_ID_LIST_STRU *pstOperatorList = VOS_NULL_PTR;

    pstOperatorList                     = NAS_MML_GetOperatorCsgList();
    pstAllowedList                      = NAS_MML_GetAllowedCsgList();

    /* 如果是宏小区，则不存在CSG ID类型，返回BUTT */
    if (NAS_MML_INVALID_CSG_ID_VALUE == pstPlmnCsgId->ulCsgId)
    {
        return NAS_MML_CSG_ID_TYPE_BUTT;
    }

    /* 如果在Allowed List中 */
    if (VOS_TRUE == NAS_MMC_IsPlmnWithCsgIdInDestCsgIdWithHomeNodeBNameList(pstPlmnCsgId,
                                        pstAllowedList->ulPlmnWithCsgIdListNum,
                                        pstAllowedList->astPlmnWithCsgIdInfo))
    {
        /* 如果在Operator List中 */
        if (VOS_TRUE == NAS_MMC_IsPlmnWithCsgIdInDestCsgIdWithHomeNodeBNameList(pstPlmnCsgId,
                                        pstOperatorList->ulPlmnWithCsgIdListNum,
                                        pstOperatorList->astPlmnWithCsgIdInfo))
        {
            return NAS_MML_CSG_ID_TYPE_IN_ALLOWED_AND_OPERATOR_CSG_LIST;

        }

        return NAS_MML_CSG_ID_TYPE_IN_ALLOWED_CSG_LIST;
    }

    /* 不在Allowed List中，但是在Operator List中 */
    if (VOS_TRUE == NAS_MMC_IsPlmnWithCsgIdInDestCsgIdWithHomeNodeBNameList(pstPlmnCsgId,
                                        pstOperatorList->ulPlmnWithCsgIdListNum,
                                        pstOperatorList->astPlmnWithCsgIdInfo))
    {
        /* 如果当前处于禁止状态 */
        if (VOS_TRUE == NAS_MMC_IsPlmnCsgIdInForbiddenCsgList(pstPlmnCsgId))
        {
            return NAS_MML_CSG_ID_TYPE_IN_OPERATOR_CSG_LIST_FOBIDDEN;
        }

        return NAS_MML_CSG_ID_TYPE_IN_OPERATOR_CSG_LIST_NOT_FOBIDDEN;
    }

    /* 不在任何一个列表中 */
    return NAS_MML_CSG_ID_TYPE_NOT_IN_ALLOWED_AND_OPERATOR_CSG_LIST;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsSpecCsgIdDisplayIndicatorNeedReport_PlmnList
 功能描述  : 根据卡文件中对此CSG ID的Display Indicator判断指定csg id是否需要上报
 输入参数  : RRMM_PLMN_CSG_ID_WITH_RAT_STRU   CSG ID+PLMN
             NAS_MML_CSG_ID_TYPE_ENUM_UINT8   CSG ID类型
 输出参数  : 无
 返 回 值  : VOS_UINT32: VOS_TRUE 上报； VOS_FAULSE 不上报；
 调用函数  : 调用函数保证入参指针不能为空
 被调函数  :
 修改历史      :
  1.日    期   : 2015年10月12日
    作    者   : s00193151
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsSpecCsgIdDisplayIndicatorNeedReport_PlmnList(
    NAS_MML_PLMN_WITH_CSG_ID_STRU      *pstPlmnCsgId,
    NAS_MML_CSG_ID_TYPE_ENUM_UINT8      enCsgIdType
)
{
    NAS_MML_CSG_ID_DISPLAY_INDICATOR_TYPE_ENUM_UINT8        ucCsgDisplayIndicator;

    ucCsgDisplayIndicator = NAS_MML_CSG_ID_DISPLAY_IND_BUTT;

    /* CSG ID类型异常的，说明是宏小区或者出现了其他异常，默认为不上报 */
    if ((NAS_MML_CSG_ID_TYPE_IN_ALLOWED_CSG_LIST > enCsgIdType)
      ||(NAS_MML_CSG_ID_TYPE_BUTT <= enCsgIdType))
    {
        return VOS_FALSE;
    }

    /* 如果SERVICE n92不可用，则都默认为可以上报 */
    if (PS_USIM_SERVICE_AVAILIABLE != NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_CSG_CTRL))
    {
        return VOS_TRUE;
    }

    /* SERVICE n92可用，根据对应的CSG ID类型，进行不同的处理 */
    switch (enCsgIdType)
    {
        case    NAS_MML_CSG_ID_TYPE_IN_ALLOWED_AND_OPERATOR_CSG_LIST:
        case    NAS_MML_CSG_ID_TYPE_IN_OPERATOR_CSG_LIST_NOT_FOBIDDEN:
        case    NAS_MML_CSG_ID_TYPE_IN_OPERATOR_CSG_LIST_FOBIDDEN:

                /* 如果在Operator List中，则无条件上报 */
                return VOS_TRUE;

        case    NAS_MML_CSG_ID_TYPE_IN_ALLOWED_CSG_LIST:
        case    NAS_MML_CSG_ID_TYPE_NOT_IN_ALLOWED_AND_OPERATOR_CSG_LIST:

                ucCsgDisplayIndicator = NAS_MMC_GetCsgDisplayIndicatorNotInOperatorCsgList_PlmnList(pstPlmnCsgId);

                if ((NAS_MML_CSG_ID_DISPLAY_INDICATOR_TYPE_DISPLAY_ALL_AVAILABLE_CSG_ID == ucCsgDisplayIndicator)
                  ||(NAS_MML_CSG_ID_DISPLAY_INDICATOR_TYPE_NOT_EXIST == ucCsgDisplayIndicator))
                {
                    /* 可以上报或不存在都上报，其他情况走默认不上报 */
                    return VOS_TRUE;
                }

                break;

        default:
                break;

    }

    /* CSG ID类型异常的默认为不上报 */
    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetCsgDisplayIndicatorNotInOperatorCsgList_PlmnList
 功能描述  : 获取不在OperatorList的CSG ID卡文件中对此CSG ID的Display Indicator
 输入参数  : NAS_MML_PLMN_WITH_CSG_ID_STRU*   CSG ID+PLMN
 输出参数  : 无
 返 回 值  : VOS_UINT8: 0 上报； 1 不上报；2 上报；
 调用函数  : 调用函数保证入参指针不能为空
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月12日
    作    者   : s00193151
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT8 NAS_MMC_GetCsgDisplayIndicatorNotInOperatorCsgList_PlmnList(
    NAS_MML_PLMN_WITH_CSG_ID_STRU      *pstPlmnCsgId
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulIndex;
    VOS_UINT8                           ucCsgDisplayIndicator;
    NAS_MML_PLMN_ID_STRU                stPlmnId;
    NAS_MML_PLMN_ID_STRU                stOperatorPlmnId;
    VOS_UINT8                           ucEfadIndicator;
    NAS_MML_PLMN_WITH_CSG_ID_LIST_STRU *pstOperatorCsgIdList = VOS_NULL_PTR;

    /* 局部变量初始化 */
    ulIndex                = 0;
    ucCsgDisplayIndicator  = 0;
    stPlmnId.ulMcc         = pstPlmnCsgId->stPlmnId.ulMcc;
    stPlmnId.ulMnc         = pstPlmnCsgId->stPlmnId.ulMnc;
    stOperatorPlmnId.ulMcc = NAS_MML_INVALID_MCC;
    stOperatorPlmnId.ulMnc = NAS_MML_INVALID_MNC;

    ucEfadIndicator        = NAS_MML_GetCsgDisplayCtrlFlag();

    pstOperatorCsgIdList   = NAS_MML_GetOperatorCsgList();

    /* 保护处理，CSG ID非法，可能是宏小区，直接判断为不上报，
    返回只上报Operator List中的，后续自然不会上报此项 */
    if (NAS_MML_INVALID_CSG_ID_VALUE == pstPlmnCsgId->ulCsgId)
    {
        return NAS_MML_CSG_ID_DISPLAY_INDICATOR_TYPE_DISPLAY_ONLY_OPERATOR_CSG_ID;
    }

    /* 不在Operator list的CSG ID查找显示指示的处理原则:
    先判断此CSG ID的PLMN是否在Operator list，如果在，看此PLMN下是否卡有对应的显示指示，
    有就按卡指示的返回，没有就按EFAD卡文件指示进行返回；如果不在Operator list，直接按
    EFAD卡文件指示进行返回；EFAD卡文件如果不存在，则外部应该将ulEfadIndicator默认初始化为上报 */

    /* 在Operator List中查找当前PLMN */
    for (i = 0; i < pstOperatorCsgIdList->ulPlmnWithCsgIdListNum; i++)
    {
        stOperatorPlmnId.ulMcc = pstOperatorCsgIdList->astPlmnWithCsgIdInfo[i].stPlmnWithCsgId.stPlmnId.ulMcc;
        stOperatorPlmnId.ulMnc = pstOperatorCsgIdList->astPlmnWithCsgIdInfo[i].stPlmnWithCsgId.stPlmnId.ulMnc;

        if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&stPlmnId,&stOperatorPlmnId))
        {
            ulIndex = i;
            break;
        }
    }

    /* PLMN不在Operator List中，直接按EFAD卡文件指示的Display Indicator指示进行返回 */
    if (i >= pstOperatorCsgIdList->ulPlmnWithCsgIdListNum)
    {
        return ucEfadIndicator;
    }

    /* 如果PLMN在Operator List中，则找到对应的PLMN的位置ulIndex，取出对应的indicator */
    ucCsgDisplayIndicator = pstOperatorCsgIdList->astPlmnWithCsgIdInfo[ulIndex].enCsgDisplayIndicator;

    /* 存在Display Indicator */
    if ((NAS_MML_CSG_ID_DISPLAY_INDICATOR_TYPE_DISPLAY_ALL_AVAILABLE_CSG_ID == ucCsgDisplayIndicator)
      ||(NAS_MML_CSG_ID_DISPLAY_INDICATOR_TYPE_DISPLAY_ONLY_OPERATOR_CSG_ID == ucCsgDisplayIndicator))
    {
        /* 根据Display Indicator指示进行返回 */
        return ucCsgDisplayIndicator;
    }

    /* 如果不存在，按EFAD卡文件指示的Display Indicator指示进行返回 */
    return ucEfadIndicator;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_AddCsgIdToListCnf_PlmnList
 功能描述  : 将状态机上下文中保存的指定位置的CSG ID信息添加到给MSCC上报的LIST CNF的列表中
 输入参数  : VOS_UINT32                                待添加的状态机上下文中保存的CSG ID的位置
             NAS_MML_CSG_ID_TYPE_ENUM_UINT8            CSG ID类型
             NAS_MSCC_PIF_PLMN_WITH_CSG_ID_INFO_STRU*  上报给MSCC的消息列表
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  : 调用函数保证入参指针不能为空
 被调函数  :
 修改历史      :
  1.日    期   : 2015年10月16日
    作    者   : s00193151
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_VOID NAS_MMC_AddCsgIdToListCnf_PlmnList(
    VOS_UINT32                                              ulIndex,
    NAS_MML_CSG_ID_TYPE_ENUM_UINT8                          enCsgIdType,
    NAS_MSCC_PIF_PLMN_WITH_CSG_ID_INFO_STRU                *pstCsgIdInfoList
)
{
    VOS_UINT32                                              ulReportListIndex;
    NAS_MML_PLMN_WITH_CSG_ID_STRU                           stPlmnWithCsgId;
    NAS_MMC_CSG_SEARCHED_PLMN_LIST_INFO_STRU               *pstCsgPlmnIdList = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_CSG_ID_LIST_STRU                     *pstOperatorList  = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_CSG_ID_LIST_STRU                     *pstAllowedCsgList  = VOS_NULL_PTR;
    VOS_UINT32                                              ulCsgIdInCsgListIndex;

    /* 找到当前已保存位置的下一个位置 */
    ulReportListIndex              = pstCsgIdInfoList->ulPlmnWithCsgIdNum;

    /* 初始化临时变量PLMN ID，用于后续比较Operator list使用 */
    pstCsgPlmnIdList               = NAS_MMC_GetCsgSearchedPlmnListInfo_PlmnList();
    stPlmnWithCsgId.stPlmnId.ulMcc = pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[ulIndex].stPlmnCsgIdWithRat.stPlmnWithRat.stPlmnId.ulMcc;
    stPlmnWithCsgId.stPlmnId.ulMnc = pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[ulIndex].stPlmnCsgIdWithRat.stPlmnWithRat.stPlmnId.ulMnc;
    stPlmnWithCsgId.ulCsgId        = pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[ulIndex].stPlmnCsgIdWithRat.ulCsgId;

    /* 根据函数入参ulIndex，找到对应状态机上下文中保存的此CSG ID，将其加入到向MSCC上报的
    CSG ID LIST中，加入的位置为，当前向MSCC上报的CSG ID LIST中已存在的最后一个CSG ID的下一个位置 */

    /* 列表已经满了直接返回 */
    if (ulReportListIndex >= NAS_MSCC_PIF_MAX_PLMN_CSG_ID_NUM)
    {
        return;
    }

    /* 保存PLMN */
    pstCsgIdInfoList->astPlmnWithCsgIdList[ulReportListIndex].stPlmnId.ulMcc
                    = pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[ulIndex].stPlmnCsgIdWithRat.stPlmnWithRat.stPlmnId.ulMcc;
    pstCsgIdInfoList->astPlmnWithCsgIdList[ulReportListIndex].stPlmnId.ulMnc
                    = pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[ulIndex].stPlmnCsgIdWithRat.stPlmnWithRat.stPlmnId.ulMnc;

    /* 保存CSG ID */
    pstCsgIdInfoList->astPlmnWithCsgIdList[ulReportListIndex].ulCsgId
                    = pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[ulIndex].stPlmnCsgIdWithRat.ulCsgId;

    /* 保存接入技术 */
    NAS_MMC_ConvertRrcRatToNasFormat(pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[ulIndex].stPlmnCsgIdWithRat.stPlmnWithRat.ulRat,
                    &pstCsgIdInfoList->astPlmnWithCsgIdList[ulReportListIndex].enRatType);

    /* 保存CSG ID TYPE */
    pstCsgIdInfoList->astPlmnWithCsgIdList[ulReportListIndex].enPlmnWithCsgIdType
                    = NAS_MMC_ConvertMmlCsgIdTypeToMsccCsgIdType_PlmnList(enCsgIdType);

    /* 保存HNB Name */
    pstCsgIdInfoList->astPlmnWithCsgIdList[ulReportListIndex].ucHomeNodeBNameLen
                    = NAS_MML_MIN(pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[ulIndex].stHomeNodeBName.ucHomeNodeBNameLen, NAS_MML_MAX_HOME_NODEB_NAME_LEN);
    PS_MEM_CPY(pstCsgIdInfoList->astPlmnWithCsgIdList[ulReportListIndex].aucHomeNodeBName,
                    pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[ulIndex].stHomeNodeBName.aucHomeNodeBName,
                    pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[ulIndex].stHomeNodeBName.ucHomeNodeBNameLen);

    pstOperatorList       = NAS_MML_GetOperatorCsgList();
    ulCsgIdInCsgListIndex = NAS_MMC_GetCsgIdIndexInDestCsgIdList(&stPlmnWithCsgId, pstOperatorList->ulPlmnWithCsgIdListNum, pstOperatorList->astPlmnWithCsgIdInfo);

    /* 不是在Operator list中的情况，直接设置CSG TYPE为0 */
    pstCsgIdInfoList->astPlmnWithCsgIdList[ulReportListIndex].ucCsgTypeLen = 0;
    PS_MEM_SET(pstCsgIdInfoList->astPlmnWithCsgIdList[ulReportListIndex].aucCsgType,
                                    0, NAS_MSCC_PIF_CSG_TYPE_LEN);

    /* Operator list中找到对应项的位置则填写对应的csg type */
    if (pstOperatorList->ulPlmnWithCsgIdListNum > ulCsgIdInCsgListIndex)
    {
        pstCsgIdInfoList->astPlmnWithCsgIdList[ulReportListIndex].ucCsgTypeLen
                      = NAS_MML_MIN(pstOperatorList->astPlmnWithCsgIdInfo[ulCsgIdInCsgListIndex].stCsgType.ucCsgTypeLen, NAS_MML_MAX_CSG_TYPE_LEN);

        PS_MEM_CPY(pstCsgIdInfoList->astPlmnWithCsgIdList[ulReportListIndex].aucCsgType,
                                pstOperatorList->astPlmnWithCsgIdInfo[ulCsgIdInCsgListIndex].stCsgType.aucCsgType,
                                pstOperatorList->astPlmnWithCsgIdInfo[ulCsgIdInCsgListIndex].stCsgType.ucCsgTypeLen);

        pstCsgIdInfoList->ulPlmnWithCsgIdNum++;
        return;
    }

    /* 不在operator csg list中则在allowed csg list中查找对应项的位置填写对应的csg type */
    pstAllowedCsgList     = NAS_MML_GetAllowedCsgList();
    ulCsgIdInCsgListIndex = NAS_MMC_GetCsgIdIndexInDestCsgIdList(&stPlmnWithCsgId, pstAllowedCsgList->ulPlmnWithCsgIdListNum, pstAllowedCsgList->astPlmnWithCsgIdInfo);

    if (pstAllowedCsgList->ulPlmnWithCsgIdListNum > ulCsgIdInCsgListIndex)
    {
        pstCsgIdInfoList->astPlmnWithCsgIdList[ulReportListIndex].ucCsgTypeLen
                      = NAS_MML_MIN(pstAllowedCsgList->astPlmnWithCsgIdInfo[ulCsgIdInCsgListIndex].stCsgType.ucCsgTypeLen, NAS_MML_MAX_CSG_TYPE_LEN);

        PS_MEM_CPY(pstCsgIdInfoList->astPlmnWithCsgIdList[ulReportListIndex].aucCsgType,
                                pstAllowedCsgList->astPlmnWithCsgIdInfo[ulCsgIdInCsgListIndex].stCsgType.aucCsgType,
                                pstAllowedCsgList->astPlmnWithCsgIdInfo[ulCsgIdInCsgListIndex].stCsgType.ucCsgTypeLen);
    }

    pstCsgIdInfoList->ulPlmnWithCsgIdNum++;
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ConvertAsCsgIdTypeToMsccCsgIdType_PlmnList
 功能描述  : 将MML类型的CSG ID TYPE转换为MSCC使用的类型
 输入参数  : NAS_MML_CSG_ID_TYPE_ENUM_UINT8
 输出参数  : 无
 返 回 值  : NAS_MSCC_PIF_PLMN_WITH_CSG_ID_TYPE_ENUM_UINT8
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年10月16日
    作    者   : s00193151
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
NAS_MSCC_PIF_PLMN_WITH_CSG_ID_TYPE_ENUM_UINT8 NAS_MMC_ConvertMmlCsgIdTypeToMsccCsgIdType_PlmnList(
    NAS_MML_CSG_ID_TYPE_ENUM_UINT8      enCsgIdType
)
{
    NAS_MSCC_PIF_PLMN_WITH_CSG_ID_TYPE_ENUM_UINT8    enMsccCsgIdType;

    switch(enCsgIdType)
    {
        case    NAS_MML_CSG_ID_TYPE_IN_ALLOWED_CSG_LIST:
        case    NAS_MML_CSG_ID_TYPE_IN_ALLOWED_AND_OPERATOR_CSG_LIST:

                enMsccCsgIdType = NAS_MSCC_PIF_CSG_ID_TYPE_IN_ALLOWED_CSG_LIST;
                break;

        case    NAS_MML_CSG_ID_TYPE_IN_OPERATOR_CSG_LIST_NOT_FOBIDDEN:

                enMsccCsgIdType = NAS_MSCC_PIF_CSG_ID_TYPE_IN_OPERATOR_CSG_LIST_NOT_FOBIDDEN;
                break;

        case    NAS_MML_CSG_ID_TYPE_IN_OPERATOR_CSG_LIST_FOBIDDEN:

                enMsccCsgIdType = NAS_MSCC_PIF_CSG_ID_TYPE_IN_OPERATOR_CSG_LIST_FOBIDDEN;
                break;

        case    NAS_MML_CSG_ID_TYPE_NOT_IN_ALLOWED_AND_OPERATOR_CSG_LIST:

                enMsccCsgIdType = NAS_MSCC_PIF_CSG_ID_TYPE_NOT_IN_ALLOWED_AND_OPERATOR_CSG_LIST;
                break;
        default:

                enMsccCsgIdType = NAS_MSCC_PIF_CSG_ID_TYPE_BUTT;
                break;

    }

    return enMsccCsgIdType;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_MMC_RcvCsgListAbortReq_PlmnList_WaitEpsRegInd
 功能描述  : 在CSG list搜网的等待EPS注册结果状态,收到LIST ABORT REQ消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:LIST ABORT REQ消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年10月16日
    作    者   : y00358807
    修改内容   : 支持LTE CSG功能新增

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvCsgListAbortReq_PlmnList_WaitEpsRegInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

    /* 发送ID_MMC_MSCC_PLMN_LIST_ABORT_CNF */
    NAS_MMC_SndMsccCsgListAbortCnf_PlmnList();

    /* 未开始搜网，此时搜索列表为空,记录当前注册导致的后续addition值，L1 MAIN上
       收到链路释放后根据addition值决定是否触发搜网 */
    NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                            VOS_FALSE,
                            NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                            NAS_MMC_GetRegRsltInfo_PlmnList());

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}
/*****************************************************************************
 函 数 名  : NAS_MMC_RcvCsgListAbortReq_PlmnList_WaitEpsConnRelInd
 功能描述  : 在CSG list搜网的等待EPS链路释放状态,收到LIST ABORT REQ消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:LIST ABORT REQ消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年10月16日
    作    者   : y00358807
    修改内容   : 支持LTE CSG功能新增

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvCsgListAbortReq_PlmnList_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND);

    /* 发送ID_MMC_MSCC_PLMN_LIST_ABORT_CNF */
    NAS_MMC_SndMsccCsgListAbortCnf_PlmnList();

    /* 未开始搜网，此时搜索列表为空,记录当前注册导致的后续addition值，L1 MAIN上
       收到链路释放后根据addition值决定是否触发搜网 */
    NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                            VOS_FALSE,
                            NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                            NAS_MMC_GetRegRsltInfo_PlmnList());

    /*退出状态机*/
     NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitLmmCsgListSearchCnf
 功能描述  : 在CSG list搜网的等待LMM的搜网回复时,收到MMCMMC_ABORT_FSM_REQ消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:MMCMMC_ABORT_FSM_REQ消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2015年9月7日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitLmmCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止等待LMM搜网结果的保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_CSG_LIST_SEARCH_CNF);

    /* 记录状态机退出标记 */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* 向LMM发送停止搜网请求,迁移NAS_MMC_PLMN_LIST_STA_WAIT_LMM_CSG_LIST_SEARCH_STOP_CNF状态,启动保护定时器 */
    NAS_MMC_SndSpecRatCsgListSearchStopReq_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMsccCsgListAbortReq_PlmnList_WaitLmmCsgListSearchCnf
 功能描述  : 在csg list搜网的等待LMM的搜网回复时,收到csg list abort消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:csg list abort消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2015年10月16日
   作    者   : y00358807
   修改内容   : 支持LTE CSG功能新增

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccCsgListAbortReq_PlmnList_WaitLmmCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止等待LMM搜网结果的保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_CSG_LIST_SEARCH_CNF);

    /* 记录状态机退出标记 */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* 设置通知MSCC回复标记 */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_TRUE);

    /* 向LMM发送停止搜网请求,迁移NAS_MMC_PLMN_LIST_STA_WAIT_LMM_CSG_LIST_SEARCH_STOP_CNF状态,启动保护定时器 */
    NAS_MMC_SndSpecRatCsgListSearchStopReq_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmCsgListSrchCnf_PlmnList_WaitLmmCsgListSearchCnf
 功能描述  : 在CSG List搜网的等待LMM的搜网回复时,收到CSG list 搜网回复消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:CSG list搜网结果消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年9月7日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmCsgListSrchCnf_PlmnList_WaitLmmCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_CSG_LIST_SEARCH_CNF_STRU   *pstLmmCsgListSearchCnf = VOS_NULL_PTR;

    pstLmmCsgListSearchCnf = (LMM_MMC_CSG_LIST_SEARCH_CNF_STRU*)pstMsg;

    /* 处理CSG LIST搜网结果 */
    NAS_MMC_ProcLmmCsgListSearchCnf_PlmnList(pstLmmCsgListSearchCnf);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcLmmCsgListSearchCnf_PlmnList
 功能描述  : 处理LMM下的CSG PLMN LIST的结果
 输入参数  : pstLmmCsgListSrchCnf - CSG list搜网结果
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年9月18日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_VOID NAS_MMC_ProcLmmCsgListSearchCnf_PlmnList(
    LMM_MMC_CSG_LIST_SEARCH_CNF_STRU   *pstLmmCsgListSrchCnf
)
{

    /* 判断CSG LIST搜网结果 */
    switch (pstLmmCsgListSrchCnf->enRlst)
    {
        case MMC_LMM_CSG_LIST_SRCH_RLT_NO_RF:

            /* 停止等待LMM搜网回复的保护定时器 */
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_CSG_LIST_SEARCH_CNF);

            NAS_MMC_ProcNoRf_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);
            return;

        case MMC_LMM_CSG_LIST_SRCH_RLT_REJ:

            /* 停止等待LMM搜网回复的保护定时器 */
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_CSG_LIST_SEARCH_CNF);

            if (VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist())
            {
                /* 发送LIST REJ给MSCC */
                NAS_MMC_SndMsccCsgListSearchRej();
            }
            else
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH, TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST_LEN);
            }

            /* 发送状态机失败退出的结果 */
            NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                     VOS_FALSE,
                                     NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                     NAS_MMC_GetRegRsltInfo_PlmnList());

            /* 退出状态机 */
            NAS_MMC_FSM_QuitFsmL2();
            return;

        case MMC_LMM_CSG_LIST_SRCH_RLT_FAIL:

            /* 停止等待LMM搜网回复的保护定时器 */
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_CSG_LIST_SEARCH_CNF);

            /* 发送LIST REJ给MSCC */
            NAS_MMC_SndMsccCsgListSearchRej();

            /* 发送状态机失败退出的结果 */
            NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                     VOS_FALSE,
                                     NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                     NAS_MMC_GetRegRsltInfo_PlmnList());

            /* 退出状态机 */
            NAS_MMC_FSM_QuitFsmL2();
            return;

        case MMC_LMM_CSG_LIST_SRCH_RLT_SUCC:

            /* 保存列表搜网结果，排序上报 */
            NAS_MMC_ProcLmmCsgListSearchSucc_PlmnList(pstLmmCsgListSrchCnf);
            return;

        default:

            /* 异常打印 */
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcLmmCsgListSearchCnf_PlmnList: Unexpected Csg List Search Result!");
            break;

    }

    /* 一阶段只支持搜LTE，因此不用再判断其他模，直接退出状态机 */
    return;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcLmmCsgListSearchSucc_PlmnList
 功能描述  : 处理LMM CSG PLMN LIST的成功的结果
 输入参数  : pstPlmnSrchCnf CSG LIST的结果
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  : 调用函数保证入参指针不能为空
 被调函数  :
 修改历史      :
  1.日    期   : 2015年10月12日
    作    者   : s00193151
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_VOID NAS_MMC_ProcLmmCsgListSearchSucc_PlmnList(
    LMM_MMC_CSG_LIST_SEARCH_CNF_STRU   *pstLmmCsgListSrchCnf
)
{
    NAS_MMC_CSG_SEARCHED_PLMN_LIST_INFO_STRU               *pstCsgPlmnIdList  = VOS_NULL_PTR;

    /* 保存LMM上报的列表搜结果到状态机上下文中 */
    NAS_MMC_SaveLmmCsgListSearchResult_PlmnList(pstLmmCsgListSrchCnf);

    /* 上报搜索结束时，说明LMM已经上报完所有搜索结果 */
    if (VOS_TRUE == pstLmmCsgListSrchCnf->ucCsgListResultCompleteFlag)
    {
        /* 停止等待LMM搜网回复的保护定时器 */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_CSG_LIST_SEARCH_CNF);

        /* 设置L已被搜索过 */
        NAS_MMC_SetSearchedFlag_PlmnList(MMC_LMM_RAT_LTE);

        /* 根据CSG搜索的最终结果刷新状态机上下文中的高低质量搜网列表 */
        pstCsgPlmnIdList = NAS_MMC_GetCsgSearchedPlmnListInfo_PlmnList();
        NAS_MMC_UpdateSearchedPlmnListInfoFromCsgSearchResult_PlmnList(pstCsgPlmnIdList);

        NAS_MMC_SndMsccCsgListSearchCnf_PlmnList();

        /* CSG LIST搜网过程中,RRC可能出服务区,此时需要设置搜网状态,触发退出LIST搜网后的指定搜网 */
        if (NAS_MMC_AS_CELL_NOT_CAMP_ON == NAS_MMC_GetAsCellCampOn())
        {
            NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);
        }

        /* 发送状态机退出的结果 */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_SUCC,
                                 (VOS_UINT8)NAS_MMC_IsNeedPlmnSearch_PlmnList(),
                                 NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                 NAS_MMC_GetRegRsltInfo_PlmnList());

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SaveLmmCsgListSearchResult_PlmnList
 功能描述  : 保存LMM CSG PLMN LIST的成功的结果到PLMN LIST状态机上下文中
 输入参数  : pstPlmnSrchCnf CSG LIST的结果消息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  : 调用函数保证入参指针不能为空
 被调函数  :
 修改历史      :
  1.日    期   : 2015年10月12日
    作    者   : s00193151
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_VOID NAS_MMC_SaveLmmCsgListSearchResult_PlmnList(
    LMM_MMC_CSG_LIST_SEARCH_CNF_STRU   *pstLmmCsgListSrchCnf
)
{
    VOS_UINT32                                              i;
    VOS_UINT32                                              ulSavePlmnNum;   /* 本次可以保存的PLMN个数 */
    NAS_MMC_CSG_SEARCHED_PLMN_LIST_INFO_STRU               *pstCsgPlmnIdList = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                                    stGUNasPlmn;
    MMC_LMM_PLMN_ID_STRU                                    stLMMPlmn;
    VOS_UINT32                                              ulTotalPlmnNum;

    /* LMM可能会连续上报不止1条消息，因此此处采用累加方式保存 */
    pstCsgPlmnIdList = NAS_MMC_GetCsgSearchedPlmnListInfo_PlmnList();
    ulTotalPlmnNum   = pstCsgPlmnIdList->ulTotalPlmnNum;


    /* 保护处理，如果超大，则只按剩余的位置进行保存(防止循环处理越界)，不超大就按LMM实际上报数量进行保存
    例如: 总数35，已经保存了30个，这次LMM又上报了10个，那就只保存前面5个，剩下的丢弃*/
    if (NAS_MML_MAX_PLMN_CSG_ID_NUM < pstCsgPlmnIdList->ulTotalPlmnNum + pstLmmCsgListSrchCnf->stCsgListSearchedResult.ulTotalPlmnNum)
    {
        ulSavePlmnNum = NAS_MML_MAX_PLMN_CSG_ID_NUM - pstCsgPlmnIdList->ulTotalPlmnNum;
    }
    else
    {
        ulSavePlmnNum = pstLmmCsgListSrchCnf->stCsgListSearchedResult.ulTotalPlmnNum;
    }

    /* 将LMM上报的CSG列表搜结果保存，同时将PLMN转换成GU的格式，注意是累加保存，本次保存要从已有总数的下一个位置开始 */
    for (i = pstCsgPlmnIdList->ulTotalPlmnNum; i < pstCsgPlmnIdList->ulTotalPlmnNum + ulSavePlmnNum; i++)
    {
        /* 保存接入技术 */
        NAS_MMC_ConvertLmmRatToRrcFormat(pstLmmCsgListSrchCnf->stCsgListSearchedResult.astCsgListSearchedPlmnInfoList[i-ulTotalPlmnNum].stPlmnCsgIdWithRat.stPlmnWithRat.enPlmnRat,
              &pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[i].stPlmnCsgIdWithRat.stPlmnWithRat.ulRat);

        /* 保存CSG ID */
        pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[i].stPlmnCsgIdWithRat.ulCsgId
                    = pstLmmCsgListSrchCnf->stCsgListSearchedResult.astCsgListSearchedPlmnInfoList[i-ulTotalPlmnNum].stPlmnCsgIdWithRat.ulCsgId;

        /* 保存HNB Name */
        pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[i].stHomeNodeBName.ucHomeNodeBNameLen
                    = NAS_MML_MIN(pstLmmCsgListSrchCnf->stCsgListSearchedResult.astCsgListSearchedPlmnInfoList[i-ulTotalPlmnNum].stHomeNodeBName.ucHomeNodeBNameLen, NAS_MML_MAX_HOME_NODEB_NAME_LEN);

        PS_MEM_CPY(pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[i].stHomeNodeBName.aucHomeNodeBName,
                    pstLmmCsgListSrchCnf->stCsgListSearchedResult.astCsgListSearchedPlmnInfoList[i-ulTotalPlmnNum].stHomeNodeBName.aucHomeNodeBName,
                    pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[i].stHomeNodeBName.ucHomeNodeBNameLen);

        /* 保存lRscp */
        pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[i].lRscp
                    = pstLmmCsgListSrchCnf->stCsgListSearchedResult.astCsgListSearchedPlmnInfoList[i-ulTotalPlmnNum].lRscp;

        /* 转换并保存PLMN */

        /* 初始化临时变量 */
        PS_MEM_SET(&stGUNasPlmn, 0, sizeof(NAS_MML_PLMN_ID_STRU));
        PS_MEM_SET(&stLMMPlmn,   0, sizeof(MMC_LMM_PLMN_ID_STRU));

        /* 取出LMM的PLMN到临时变量 */
        PS_MEM_CPY(stLMMPlmn.aucPlmnId,
                    pstLmmCsgListSrchCnf->stCsgListSearchedResult.astCsgListSearchedPlmnInfoList[i-ulTotalPlmnNum].stPlmnCsgIdWithRat.stPlmnWithRat.aucPlmnId,
                    MMC_LMM_PLMN_ID_LEN);

        /* 转换L的PLMN到GU的格式 */
        NAS_MMC_ConvertLmmPlmnToGUNasFormat(&stLMMPlmn, &stGUNasPlmn);

        /* 保存PLMN */
        pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[i].stPlmnCsgIdWithRat.stPlmnWithRat.stPlmnId.ulMcc = stGUNasPlmn.ulMcc;
        pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[i].stPlmnCsgIdWithRat.stPlmnWithRat.stPlmnId.ulMnc = stGUNasPlmn.ulMnc;

    }

    /* 保存PLMN总数 */
    pstCsgPlmnIdList->ulTotalPlmnNum += ulSavePlmnNum;

    /* 保存高优先级PLMN个数，注意如果LMM上报的PLMN没能全部保存，则只增加实际保存的个数 */
    pstCsgPlmnIdList->ulHighPlmnNum  += NAS_MML_MIN(pstLmmCsgListSrchCnf->stCsgListSearchedResult.ulHighPlmnNum, ulSavePlmnNum);

    return;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitLmmCsgListSrchCnfExpired_PlmnList_WaitLmmCsgListSearchCnf
 功能描述  : 在CSG List搜网的等待LMM的搜网回复时,收到保护定时器超时消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:等CSG list搜网结果保护定时器超时消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年9月7日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiWaitLmmCsgListSrchCnfExpired_PlmnList_WaitLmmCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 更新当前RAT的搜索标记 */
    NAS_MMC_SetSearchedFlag_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

    /* 向LMM发送停止搜网请求,迁移状态,启动保护定时器 */
    NAS_MMC_SndSpecRatCsgListSearchStopReq_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmAreaLostInd_PlmnList_WaitLmmCsgListSearchCnf
 功能描述  : 在CSG List搜网的等待LMM的搜网回复时,收到丢网消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:丢网消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年9月7日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmAreaLostInd_PlmnList_WaitLmmCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 清除驻留状态 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* 当前信号更新 */
    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());

    /* 更新服务状态 上报无服务*/
    NAS_MMC_SetCsServiceStatus(NAS_MMC_NO_SERVICE);
    NAS_MMC_SetPsServiceStatus(NAS_MMC_NO_SERVICE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmSysInfoInd_PlmnList_WaitLmmCsgListSearchCnf
 功能描述  : 在CSG List搜网的等待LMM的搜网回复时,收到系统消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:系统消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年10月16日
    作    者   : y00358807
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmSysInfoInd_PlmnList_WaitLmmCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ProcLteSysInfo_PlmnList(pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmAttachInd_PlmnList_WaitLmmCsgListSearchCnf
 功能描述  : 在CSG List搜网的等待LMM的搜网回复时,收到attach消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:attach消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年10月16日
    作    者   : y00358807
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmAttachInd_PlmnList_WaitLmmCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_ATTACH_IND_STRU                                *pstLmmAttachIndMsg = VOS_NULL_PTR;

    pstLmmAttachIndMsg  = (LMM_MMC_ATTACH_IND_STRU*)pstMsg;

    /* 向GMM和MM转发注册结果消息 */
    NAS_MMC_SndMmLmmAttachInd(pstLmmAttachIndMsg);
    NAS_MMC_SndGmmLmmAttachInd(pstLmmAttachIndMsg);

    /* 处理attach结果 */
    NAS_MMC_ProcLmmAttachInd_PlmnList(pstLmmAttachIndMsg);

    /* L下注册完成后，IMS时支持时会发起IMS注册,需要根据IMS注册的情况决定是否需要
       disable L模,此时需要进一步等待IMS的注册结果 */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList();

#if (FEATURE_ON == FEATURE_IMS)
    NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_IMS);
#endif

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmTauResultInd_PlmnList_WaitLmmCsgListSearchCnf
 功能描述  : 在CSG List搜网的等待LMM的搜网回复时,收到tau消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:tau消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年10月16日
    作    者   : y00358807
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmTauResultInd_PlmnList_WaitLmmCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_TAU_RESULT_IND_STRU        *pstLmmTauIndMsg;

    pstLmmTauIndMsg  = (LMM_MMC_TAU_RESULT_IND_STRU*)pstMsg;

    /* 向GMM和MM转发注册结果消息 */
    NAS_MMC_SndMmLmmTauResultInd(pstLmmTauIndMsg);
    NAS_MMC_SndGmmLmmTauResultInd(pstLmmTauIndMsg);

    /* 处理tau结果 */
    NAS_MMC_ProcLmmTauResultInd_PlmnList(pstLmmTauIndMsg);

    /* L下注册完成后，IMS时支持时会发起IMS注册,需要根据IMS注册的情况决定是否需要
       disable L模,此时需要进一步等待IMS的注册结果 */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList();

#if (FEATURE_ON == FEATURE_IMS)
    NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_IMS);
#endif

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMsccImsVoiceCapInd_PlmnList_WaitLmmCsgListSearchCnf
 功能描述  : 在CSG List搜网的等待LMM的搜网回复时,收到ims voice cap ind消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:ims voice cap ind消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年10月16日
    作    者   : y00358807
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccImsVoiceCapInd_PlmnList_WaitLmmCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMC_IMS_VOICE_CAP_NOTIFY_STRU *pstImsVoiceInd = VOS_NULL_PTR;
    VOS_UINT8                           ucWaitRegRsltFlag;

    ucWaitRegRsltFlag   = NAS_MMC_GetWaitRegRsltFlag_PlmnList();
    pstImsVoiceInd      = (MSCC_MMC_IMS_VOICE_CAP_NOTIFY_STRU *)pstMsg;

    /* 如果在等待IMS的注册结果才处理 */
    if (NAS_MMC_WAIT_REG_RESULT_IND_IMS != (ucWaitRegRsltFlag & NAS_MMC_WAIT_REG_RESULT_IND_IMS))
    {
        return VOS_TRUE;
    }

    NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_IMS);

    /* IMS不可用时判断是否需要disable LTE */
    if (VOS_FALSE  == pstImsVoiceInd->ucAvail)
    {
        if (VOS_TRUE == NAS_MMC_IsNeedDisableLte_ImsVoiceNotAvail())
        {
            NAS_MMC_SetCsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION);

            NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS);

            NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE);
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitLmmCsgListSearchStopCnf
 功能描述  : 在csg list搜网的等待LMM的停止搜网回复时,收到MMCMMC_ABORT_FSM_REQ消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:MMCMMC_ABORT_FSM_REQ消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2015年9月7日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitLmmCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 置ABORT标志位 */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMsccCsgListAbortFsmMsg_PlmnList_WaitLmmCsgListSearchStopCnf
 功能描述  : 在csg list搜网的等待LMM的停止搜网回复时,收到csg list abort消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:CSG list abort消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2015年9月7日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccCsgListAbortFsmMsg_PlmnList_WaitLmmCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 置ABORT标志位 */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* 设置通知MSCC结果的标记 */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmCsgListSrchCnf_PlmnList_WaitLmmCsgListSearchStopCnf
 功能描述  : 在csg list搜网的等待LMM的停止搜网回复时,收到csg list结果消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:CSG list结果消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2015年10月21日
   作    者   : y00358807
   修改内容   : 支持LTE CSG功能新增

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmCsgListSrchCnf_PlmnList_WaitLmmCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_CSG_LIST_SEARCH_CNF_STRU   *pstLmmCsgListsearchCnf = VOS_NULL_PTR;
    NAS_MMC_CSG_SEARCHED_PLMN_LIST_INFO_STRU               *pstCsgPlmnIdList  = VOS_NULL_PTR;

    pstLmmCsgListsearchCnf = (LMM_MMC_CSG_LIST_SEARCH_CNF_STRU*)pstMsg;

    /* LIST搜网回复与停止搜网对冲,NO RF时直接退出LIST搜网流程 */
    if (MMC_LMM_CSG_LIST_SRCH_RLT_NO_RF == pstLmmCsgListsearchCnf->enRlst)
    {
        /* 停止保护定时器 */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF);

        NAS_MMC_ProcNoRf_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

        return VOS_TRUE;
    }

    /*只有在搜索成功时才进行处理 */
    if (MMC_LMM_CSG_LIST_SRCH_RLT_SUCC != pstLmmCsgListsearchCnf->enRlst)
    {
        return VOS_TRUE;
    }

    /* 保存LMM上报的列表搜结果到状态机上下文中 */
    NAS_MMC_SaveLmmCsgListSearchResult_PlmnList(pstLmmCsgListsearchCnf);

    /* 上报搜索结束时，说明LMM已经上报完所有搜索结果 */
    if (VOS_TRUE == pstLmmCsgListsearchCnf->ucCsgListResultCompleteFlag)
    {
        /* 停止保护定时器 */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF);

        /* 设置L已被搜索过 */
        NAS_MMC_SetSearchedFlag_PlmnList(MMC_LMM_RAT_LTE);

        /* 根据CSG搜索的最终结果刷新状态机上下文中的高低质量搜网列表 */
        pstCsgPlmnIdList = NAS_MMC_GetCsgSearchedPlmnListInfo_PlmnList();
        NAS_MMC_UpdateSearchedPlmnListInfoFromCsgSearchResult_PlmnList(pstCsgPlmnIdList);

        /* 处理搜网停止回复结果 */
        NAS_MMC_ProcLmmCsgListSearchStopCnf_PlmnList();
    }
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmPlmnSrchStopCnf_PlmnList_WaitLmmCsgListSearchStopCnf
 功能描述  : 在csg list搜网的等待LMM的停止搜网回复时,收到停止搜网回复消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:停止搜网回复消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2015年10月16日
   作    者   : y00358807
   修改内容   : 支持LTE CSG功能新增

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmPlmnSrchStopCnf_PlmnList_WaitLmmCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF);

    /* 处理搜网停止回复结果 */
    NAS_MMC_ProcLmmCsgListSearchStopCnf_PlmnList();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitLmmStopCnfExpired_PlmnList_WaitLmmCsgListSearchStopCnf
 功能描述  : 在csg list搜网的等待LMM的停止搜网回复时,收到等停止搜网回复超时消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:等停止搜网回复超时消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2015年10月16日
   作    者   : y00358007
   修改内容   : 支持LTE CSG功能新增

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiWaitLmmStopCnfExpired_PlmnList_WaitLmmCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitLmmStopCnfExpired_PlmnList_WaitLmmCsgListSearchStopCnf: Timer Expired");

    /* 处理搜网停止回复结果 */
    NAS_MMC_ProcLmmCsgListSearchStopCnf_PlmnList();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmAreaLostInd_PlmnList_WaitLmmCsgListSearchStopCnf
 功能描述  : 在停止CSG List搜网的等待LMM的停止搜网回复时,收到丢网消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:丢网消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年10月16日
    作    者   : y00358807
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvLmmAreaLostInd_PlmnList_WaitLmmCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 清除驻留状态 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* 当前信号更新 */
    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());

    /* 更新服务状态 上报无服务*/
    NAS_MMC_SetCsServiceStatus(NAS_MMC_NO_SERVICE);
    NAS_MMC_SetPsServiceStatus(NAS_MMC_NO_SERVICE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmSysInfoInd_PlmnList_WaitLmmCsgListSearchCnf
 功能描述  : 在停止CSG List搜网的等待LMM的停止搜网回复时,收到系统消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:系统消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年10月16日
    作    者   : y00358807
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmSysInfoInd_PlmnList_WaitLmmCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ProcLteSysInfo_PlmnList(pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmAttachInd_PlmnList_WaitLmmCsgListSearchCnf
 功能描述  : 在停止CSG List搜网的等待LMM的停止搜网回复时,收到attach消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:attach消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年10月16日
    作    者   : y00358807
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmAttachInd_PlmnList_WaitLmmCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_ATTACH_IND_STRU                                *pstLmmAttachIndMsg = VOS_NULL_PTR;

    pstLmmAttachIndMsg  = (LMM_MMC_ATTACH_IND_STRU*)pstMsg;

    /* 向GMM和MM转发注册结果消息 */
    NAS_MMC_SndMmLmmAttachInd(pstLmmAttachIndMsg);
    NAS_MMC_SndGmmLmmAttachInd(pstLmmAttachIndMsg);

    /* 处理attach结果 */
    NAS_MMC_ProcLmmAttachInd_PlmnList(pstLmmAttachIndMsg);

    /* L下注册完成后，IMS时支持时会发起IMS注册,需要根据IMS注册的情况决定是否需要
       disable L模,此时需要进一步等待IMS的注册结果 */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList();

#if (FEATURE_ON == FEATURE_IMS)
    NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_IMS);
#endif

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmTauResultInd_PlmnList_WaitLmmCsgListSearchStopCnf
 功能描述  : 在停止CSG List搜网的等待LMM的停止搜网回复时,收到tau消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:tau消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年10月16日
    作    者   : y00358807
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmTauResultInd_PlmnList_WaitLmmCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_TAU_RESULT_IND_STRU        *pstLmmTauIndMsg;

    pstLmmTauIndMsg  = (LMM_MMC_TAU_RESULT_IND_STRU*)pstMsg;

    /* 向GMM和MM转发注册结果消息 */
    NAS_MMC_SndMmLmmTauResultInd(pstLmmTauIndMsg);
    NAS_MMC_SndGmmLmmTauResultInd(pstLmmTauIndMsg);

    /* 处理tau结果 */
    NAS_MMC_ProcLmmTauResultInd_PlmnList(pstLmmTauIndMsg);

    /* L下注册完成后，IMS时支持时会发起IMS注册,需要根据IMS注册的情况决定是否需要
       disable L模,此时需要进一步等待IMS的注册结果 */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList();

#if (FEATURE_ON == FEATURE_IMS)
    NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_IMS);
#endif

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMsccImsVoiceCapInd_PlmnList_WaitLmmCsgListSearchStopCnf
 功能描述  : 在停CSG List搜网的等待LMM的停止搜网回复时,收到ims voice cap ind消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:ims voice cap ind消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年10月16日
    作    者   : y00358807
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccImsVoiceCapInd_PlmnList_WaitLmmCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMC_IMS_VOICE_CAP_NOTIFY_STRU *pstImsVoiceInd = VOS_NULL_PTR;
    VOS_UINT8                           ucWaitRegRsltFlag;

    ucWaitRegRsltFlag   = NAS_MMC_GetWaitRegRsltFlag_PlmnList();
    pstImsVoiceInd      = (MSCC_MMC_IMS_VOICE_CAP_NOTIFY_STRU *)pstMsg;

    /* 如果在等待IMS的注册结果才处理 */
    if (NAS_MMC_WAIT_REG_RESULT_IND_IMS != (ucWaitRegRsltFlag & NAS_MMC_WAIT_REG_RESULT_IND_IMS))
    {
        return VOS_TRUE;
    }

    NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_IMS);

    /* IMS不可用时判断是否需要disable LTE */
    if (VOS_FALSE  == pstImsVoiceInd->ucAvail)
    {
        if (VOS_TRUE == NAS_MMC_IsNeedDisableLte_ImsVoiceNotAvail())
        {
            NAS_MMC_SetCsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION);

            NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS);

            NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE);
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcLmmCsgListSearchStopCnf_PlmnList
 功能描述  : 处理LMM的CSG搜网停止回复的结果
 输入参数  : enRatType 当前接入技术
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年10月06日
    作    者   : y00358807
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_ProcLmmCsgListSearchStopCnf_PlmnList(VOS_VOID)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNextRatType;

    VOS_UINT32                          ulNeedPlmnSearch;

    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnList())
    {
        ulNeedPlmnSearch = VOS_FALSE;

        /* 通知MSCC回复标记为真 */
        if ( VOS_TRUE == NAS_MMC_GetNotifyMsccFlag_PlmnList())
        {
            /* 向MSCC回复ID_MMC_MSCC_PLMN_LIST_ABORT_CNF */
            NAS_MMC_SndMsccCsgListAbortCnf_PlmnList();

            ulNeedPlmnSearch = NAS_MMC_IsNeedPlmnSearch_PlmnList();
        }
        else
        {
            /* 向MSCC回复LIST搜网结果 */
            NAS_MMC_SndMsccCsgListSearchCnf_PlmnList();
        }

        /* 发送状态机ABORT退出结果 */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                                (VOS_UINT8)ulNeedPlmnSearch,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* 获取不到下一个未搜索的接入模式 */
    if ( VOS_FALSE == NAS_MMC_GetNextSearchingRat_PlmnList(&enNextRatType))
    {
        /* 将搜索到的网络进行排序后上报给MSCC */
        NAS_MMC_SndMsccCsgListSearchCnf_PlmnList();

        /* 发送状态机成功退出的结果 */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                 (VOS_UINT8)NAS_MMC_IsNeedPlmnSearch_PlmnList(),
                                 NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                 NAS_MMC_GetRegRsltInfo_PlmnList());

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* 向当前接入技术发送挂起请求,迁移状态,启动保护定时器 */
    NAS_MMC_SndSpecRatSuspendReq_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

    /* 向GMM发送搜网指示 */
    NAS_MMC_SndGmmPlmnSchInit();

    /* 向MM发送搜网指示 */
    NAS_MMC_SndMmPlmnSchInit();

    return;
}
#endif
#endif

/*lint -restore */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif




