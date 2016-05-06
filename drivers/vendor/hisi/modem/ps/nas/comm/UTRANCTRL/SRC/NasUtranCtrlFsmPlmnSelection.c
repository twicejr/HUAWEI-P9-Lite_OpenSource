/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NASUTRANCTRLFSMPLMNSELECTION.c
  版 本 号   : 初稿
  作    者   : w00176964
  生成日期   : 2012年7月12日
  最近修改   :
  功能描述   : 搜网状态机处理文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年8月4日
    作    者   : w00176964
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "NasComm.h"
/* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
#include "MsccMmcInterface.h"
/* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */
#include "NasUtranCtrlCtx.h"
#include "NasUtranCtrlCommFunc.h"
#include "NasUtranCtrlFsmMain.h"
#include "Nasrrcinterface.h"
#include "NasUtranCtrlProcNvim.h"
#include "NasMmcTimerMgmt.h"
#include "NasUtranCtrlFsmPlmnSelectionTbl.h"
#include "NasMmlLib.h"
#include "NasMmcComFunc.h"

#include "NasMmcFsmPlmnSelection.h"

#if (FEATURE_ON == FEATURE_TDS_WCDMA_DYNAMIC_LOAD)
#include "NasDynLoadApi.h"
#include "NasDynLoad.h"
#endif


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 常量定义
*****************************************************************************/

#define    THIS_FILE_ID        PS_FILE_ID_NAS_UTRANCTRL_FSM_PLMN_SELECTION_C

/*****************************************************************************
  3 类型定义
*****************************************************************************/

/*****************************************************************************
  4 函数声明
*****************************************************************************/

/*****************************************************************************
  5 变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数实现
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvWasPlmnSrchCnf_PlmnSelection_Init
 功能描述  : 搜网状态机初始化状态收到WAS搜网回复消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月4日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvWasPlmnSrchCnf_PlmnSelection_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 保存状态机入口消息 */
    NAS_UTRANCTRL_SaveCurEntryMsg(ulEventType, pstMsg);

    /* W下搜网失败需要在TD下继续搜网 挂起WAS */
    NAS_UTRANCTRL_SndGuAsSuspendReq(WUEPS_PID_WRR);

    /* 迁移状态到等到WAS挂起回复 */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF);

    /* 启动定时器 */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF_LEN);

    /* 消息处理完成不需继续进入MMC状态机处理 */
    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvMmcInterSkipSearchWasIndMsg_PlmnSelection_Init
 功能描述  : 搜网状态机初始化状态收到MMC的跳过搜索WAS消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年2月11日
   作    者   : w00167002
   修改内容   : 新生成函数
 2.日    期   : 2015年5月18日
   作    者   : b00269685
   修改内容   : 增加停止W搜网的处理
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvMmcInterSkipSearchWasIndMsg_PlmnSelection_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 保存状态机入口消息 */
    NAS_UTRANCTRL_SaveCurEntryMsg(ulEventType, pstMsg);

    if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_SEARCH_CNF))
    {
        /* 停定时器 */
        NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_SEARCH_CNF);

        /* 向WAS发送停止搜网请求 */
        NAS_UTRANCTRL_SndGuAsPlmnStopReq(WUEPS_PID_WRR);

        /* 迁移状态到等到was停止搜网回复 */
        NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_PLMN_STOP_CNF);

        /* 启动保护定时器 */
        NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_STOP_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_STOP_CNF_LEN);

        return VOS_TRUE;
    }

    /* W下搜网失败需要在TD下继续搜网 挂起WAS */
    NAS_UTRANCTRL_SndGuAsSuspendReq(WUEPS_PID_WRR);

    /* 迁移状态到等到WAS挂起回复 */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF);

    /* 启动定时器 */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF_LEN);

    /* 消息处理完成不需继续进入MMC状态机处理 */
    return VOS_TRUE;
}



/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvMmcInterSkipSearchTdsIndMsg_PlmnSelection_Init
 功能描述  : 搜网状态机初始化状态收到MMC的跳过搜索tds消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年11月3日
   作    者   : z00161729
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvMmcInterSkipSearchTdsIndMsg_PlmnSelection_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 保存状态机入口消息 */
    NAS_UTRANCTRL_SaveCurEntryMsg(ulEventType, pstMsg);

    /* tds下搜网失败需要在w下继续搜网 挂起tds */
    NAS_UTRANCTRL_SndGuAsSuspendReq(TPS_PID_RRC);

    /* 迁移状态到等到TDS挂起回复 */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_SUSPEND_CNF);

    /* 启动定时器 */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF_LEN);

    /* 消息处理完成不需继续进入MMC状态机处理 */
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvTiWaitWasPlmnSearchCnfExpired_PlmnSelection_Init
 功能描述  : 收到WAS的指定搜网回复超时消息
 输入参数  : ulEventType:消息类型
              pstMsg:搜网回复超时消息的首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月22日
    作    者   : w00167002
    修改内容   : V7R1C50_GUTL_PhaseII:新生成函数
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitWasPlmnSearchCnfExpired_PlmnSelection_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 保存状态机入口消息 */
    NAS_UTRANCTRL_SaveCurEntryMsg(ulEventType, pstMsg);

    /* 向WAS发送停止搜网请求 */
    NAS_UTRANCTRL_SndGuAsPlmnStopReq(WUEPS_PID_WRR);

    /* 迁移状态到等到停止W搜网后去TD下搜网状态 */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_PLMN_STOP_CNF_SEARCH_TD);

    /* 启动保护定时器 */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_STOP_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_STOP_CNF_LEN);

    /* 消息处理完成不需继续进入MMC状态机处理 */
    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvWasRrMmRelInd_PlmnSelection_Init
 功能描述  : 搜网时收到WAS的接入层复位消息
 输入参数  : ulEventType:消息类型
              pstMsg:搜网回复超时消息的首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月22日
    作    者   : w00167002
    修改内容   : V7R1C50_GUTL_PhaseII:新生成函数
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvWasRrMmRelInd_PlmnSelection_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 将构造的搜网消息保存到状态机入口消息 */
    NAS_UTRANCTRL_SaveCurEntryMsg(ulEventType, pstMsg);

    /* W下搜网失败需要在TD下继续搜网 挂起WAS */
    NAS_UTRANCTRL_SndGuAsSuspendReq(WUEPS_PID_WRR);

    /* 迁移状态到等到WAS挂起回复 */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF);

    /* 启动定时器 */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF_LEN);

    /* 消息处理完成不需继续进入MMC状态机处理 */
    return VOS_TRUE;

}



/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvTdPlmnSrchCnf_PlmnSelection_Init
 功能描述  : 搜网状态机初始化状态收到TD搜网回复消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月4日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvTdPlmnSrchCnf_PlmnSelection_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 保存状态机入口消息 */
    NAS_UTRANCTRL_SaveCurEntryMsg(ulEventType, pstMsg);

    /* TD下搜网失败根据携带的搜网列表不为空的情况下则退出当前搜网过程,
       否则需要挂起TD到W下搜网 */
    NAS_UTRANCTRL_SndGuAsSuspendReq(TPS_PID_RRC);

    /* 迁移状态到等到TD挂起回复 */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_SUSPEND_CNF);

    /* 启动定时器 */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF_LEN);

    /* 消息处理完成不需继续进入MMC状态机处理 */
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvTiWaitTdPlmnSearchCnfExpired_PlmnSelection_Init
 功能描述  : 收到WAS的指定搜网回复超时消息
 输入参数  : ulEventType:消息类型
              pstMsg:搜网回复超时消息的首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月22日
    作    者   : w00167002
    修改内容   : V7R1C50_GUTL_PhaseII:新生成函数
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitTdPlmnSearchCnfExpired_PlmnSelection_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 保存状态机入口消息 */
    NAS_UTRANCTRL_SaveCurEntryMsg(ulEventType, pstMsg);

    /* 向TD发送停止搜网请求 */
    NAS_UTRANCTRL_SndGuAsPlmnStopReq(TPS_PID_RRC);

    /* 迁移状态到等到停止TD搜网后去W下搜网状态 */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_PLMN_STOP_CNF_SEARCH_W);

    /* 启动保护定时器 */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_PLMN_STOP_CNF, TI_NAS_UTRANCTRL_WAIT_TD_PLMN_STOP_CNF_LEN);

    /* 消息处理完成不需继续进入MMC状态机处理 */
    return VOS_TRUE;

}



/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvRrmmPlmnStopCnf_PlmnSelection_WaitWasPlmnStopCnfSearchTD
 功能描述  : 等待WAS停止搜网去搜TD回复过程中收到停止搜网回复消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年8月28日
   作    者   : w00167002
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvRrmmPlmnStopCnf_PlmnSelection_WaitWasPlmnStopCnfSearchTD(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstBufferEntryMsg = VOS_NULL_PTR;

    /* 获得当前缓存的缓冲区地址 */
    pstBufferEntryMsg = NAS_UTRANCTRL_GetBufferUtranSndMmcMsgAddr();

    /* 停止保护定时器 */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_STOP_CNF);

    /* 收到了MMC打断状态机消息，则回到SUSPEND状态退出UTRANCTRL选网流程 */
    if (VOS_TRUE == NAS_UTRANCTRL_GetRcvMmcAbortFsmReqMsgFlg_PlmnSelection())
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvRrmmPlmnStopCnf_PlmnSelection_WaitWasPlmnStopCnfSearchTD WITH MMC ABORT");

        /* 如果当前有MMC的打断，当前需要继续挂起当前模进行搜网 */
        NAS_UTRANCTRL_SndGuAsSuspendReq(WUEPS_PID_WRR);

        /* 迁移状态到等到WAS挂起回复 */
        NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF);

        /* 启动定时器 */
        NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF_LEN);

        /* 消息处理完成不需继续处理 */
        return VOS_TRUE;
    }

    /* 如果当前存在打断，则直接退出选网状态机 */
    if ( VOS_TRUE == NAS_UTRANCTRL_GetAbortFlg_PlmnSelection())
    {
        /* 构造指定搜网回复失败消息到内存的缓存区域 */
        NAS_UTRANCTRL_BuildRrMmPlmnSearchCnfFailMsg(WUEPS_PID_WRR,
                                                    WUEPS_PID_MMC,
                                                    NAS_UTRANCTRL_GetBufferedPlmnSearchReqType(),
                                                    (RRMM_PLMN_SEARCH_CNF_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

        /* 保存构造指定搜网回复失败消息事件类型 */
        pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );

        /* 设置需要替换入口消息标记 */
        NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

        /* 切换到MAIN状态机 */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* 消息处理完成继续进入MMC状态机处理 */
        return VOS_FALSE;
    }

    /* 如果当前不存在打断，当前需要继续挂起当前模进行搜网 */
    NAS_UTRANCTRL_SndGuAsSuspendReq(WUEPS_PID_WRR);

    /* 迁移状态到等到WAS挂起回复 */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF);

    /* 启动定时器 */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF_LEN);

    /* 消息处理完成不需继续处理 */
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvRrmmPlmnSearchCnf_PlmnSelection_WaitWasPlmnStopCnfSearchTD
 功能描述  : 等待WAS停止搜网去搜TD回复过程中收到搜网回复消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年6月25日
   作    者   : b00269685
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvRrmmPlmnSearchCnf_PlmnSelection_WaitWasPlmnStopCnfSearchTD(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstBufferEntryMsg = VOS_NULL_PTR;
    RRMM_PLMN_SEARCH_CNF_STRU          *pstSrchCnfMsg     = VOS_NULL_PTR;

    pstSrchCnfMsg = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;

    /* 获得当前缓存的缓冲区地址 */
    pstBufferEntryMsg = NAS_UTRANCTRL_GetBufferUtranSndMmcMsgAddr();

    /* 停止保护定时器 */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_STOP_CNF);

    if (VOS_TRUE == NAS_UTRANCTRL_GetRcvMmcAbortFsmReqMsgFlg_PlmnSelection())
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvRrmmPlmnSearchCnf_PlmnSelection_WaitWasPlmnStopCnfSearchTD WITH MMC ABORT");

        /* 如果当前有MMC的打断，当前需要继续挂起当前，在挂起状态MMC回复打断 */
        NAS_UTRANCTRL_SndGuAsSuspendReq(WUEPS_PID_WRR);

        /* 迁移状态到等到WAS挂起回复 */
        NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF);

        /* 启动定时器 */
        NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF_LEN);

        /* 继续等待选网STOP CNF,丢弃当前搜网回复 */
        return VOS_TRUE;
    }

    /* 如果当前存在打断，则直接退出选网状态机 */
    if ( VOS_TRUE == NAS_UTRANCTRL_GetAbortFlg_PlmnSelection())
    {
        /* 构造指定搜网回复失败消息到内存的缓存区域 */
        NAS_UTRANCTRL_BuildRrMmPlmnSearchCnfFailMsg(WUEPS_PID_WRR,
                                                    WUEPS_PID_MMC,
                                                    NAS_UTRANCTRL_GetBufferedPlmnSearchReqType(),
                                                    (RRMM_PLMN_SEARCH_CNF_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

        /* 保存构造指定搜网回复失败消息事件类型 */
        pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );

        /* 设置需要替换入口消息标记 */
        NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

        /* 切换到MAIN状态机 */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* 消息处理完成继续进入MMC状态机处理 */
        return VOS_FALSE;
    }

    /* 如果搜网失败，原因为NO RF，则直接进MMC处理，维持当前为FDD模式 */
    if ((RRC_PLMN_SEARCH_RLT_SPEC_NO_RF     == pstSrchCnfMsg->ulSearchRlt)
     || (RRC_PLMN_SEARCH_RLT_HISTORY_NO_RF  == pstSrchCnfMsg->ulSearchRlt))
    {
        NAS_UTRANCTRL_SetCurrUtranMode(NAS_UTRANCTRL_UTRAN_MODE_FDD);

        /* 状态机切换到MAIN */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* 进MMC状态机处理 */
        return VOS_FALSE;
    }

    /* 如果当前不存在打断，当前需要继续挂起当前模进行搜网 */
    NAS_UTRANCTRL_SndGuAsSuspendReq(WUEPS_PID_WRR);

    /* 迁移状态到等到WAS挂起回复 */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF);

    /* 启动定时器 */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF_LEN);

    /* 消息处理完成不需继续处理 */
    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvRrmmRelInd_PlmnSelection_WaitWasPlmnStopCnfSearchTD
 功能描述  : 等待WAS停止搜网回复过程中收到RRMM_REL_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年8月28日
   作    者   : w00167002
   修改内容   : 新生成函数

 2.日    期   : 2014年6月12日
   作    者   : w00167002
   修改内容   : WAS异常且当前为NO RF,则进入MMC进行处理
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvRrmmRelInd_PlmnSelection_WaitWasPlmnStopCnfSearchTD(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstBufferEntryMsg = VOS_NULL_PTR;

    RRMM_REL_IND_STRU                  *pstRrmmRelIndMsg  = VOS_NULL_PTR;

    pstRrmmRelIndMsg = (RRMM_REL_IND_STRU *)pstMsg;

    /* 获得当前缓存的缓冲区地址 */
    pstBufferEntryMsg = NAS_UTRANCTRL_GetBufferUtranSndMmcMsgAddr();

    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvRrmmRelInd_PlmnSelection_WaitWasPlmnStopCnfSearchTD: ENTERED");

    /* 停止保护定时器 */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_STOP_CNF);

    /* 收到了MMC打断状态机消息，则回到SUSPEND状态退出UTRANCTRL选网流程 */
    if (VOS_TRUE == NAS_UTRANCTRL_GetRcvMmcAbortFsmReqMsgFlg_PlmnSelection())
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvRrmmRelInd_PlmnSelection_WaitWasPlmnStopCnfSearchTD WITH MMC ABORT");

        /* 如果当前有MMC的打断，当前需要继续挂起当前模进行搜网 */
        NAS_UTRANCTRL_SndGuAsSuspendReq(WUEPS_PID_WRR);

        /* 迁移状态到等到WAS挂起回复 */
        NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF);

        /* 启动定时器 */
        NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF_LEN);

        /* 消息处理完成不需继续处理 */
        return VOS_TRUE;
    }


    /* 如果搜网失败，原因为NO RF，则直接进MMC处理，维持当前为FDD模式 */
    if (RRC_REL_CAUSE_NO_RF == pstRrmmRelIndMsg->ulRelCause)
    {
        NAS_UTRANCTRL_SetCurrUtranMode(NAS_UTRANCTRL_UTRAN_MODE_FDD);

        /* 状态机切换到MAIN */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* 进MMC状态机处理 */
        return VOS_FALSE;
    }

    if ( VOS_TRUE == NAS_UTRANCTRL_GetAbortFlg_PlmnSelection())
    {
        /* 构造指定搜网回复失败消息到内存的缓存区域 */
        NAS_UTRANCTRL_BuildRrMmPlmnSearchCnfFailMsg(WUEPS_PID_WRR,
                                                    WUEPS_PID_MMC,
                                                    NAS_UTRANCTRL_GetBufferedPlmnSearchReqType(),
                                                    (RRMM_PLMN_SEARCH_CNF_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

        /* 保存构造指定搜网回复失败消息事件类型 */
        pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );

        /* 设置需要替换入口消息标记 */
        NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

        /* 切换到MAIN状态机 */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* 将搜网失败消息发给MMC处理 */
        return VOS_FALSE;
    }

    /* W下搜网失败需要在TD下继续搜网 挂起WAS */
    NAS_UTRANCTRL_SndGuAsSuspendReq(WUEPS_PID_WRR);

    /* 迁移状态到等到WAS挂起回复 */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF);

    /* 启动定时器 */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF_LEN);

    /* 消息处理完成不需继续进入MMC状态机处理 */
    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasPlmnStopCnfSearchTD
 功能描述  : 等待WAS停止搜网去搜TD回复过程中收到用户请求消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年8月28日
   作    者   : w00167002
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasPlmnStopCnfSearchTD(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 记录状态机打断标记 */
    NAS_UTRANCTRL_SetAbortFlg_PlmnSelection(VOS_TRUE);

    /* 缓存当前用户请求消息 */
    NAS_UTRANCTRL_SaveCacheMsgInMsgQueue(ulEventType, pstMsg);

    /* 消息处理完成不需继续处理 */
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvMmcAbortFsmReqMsg_PlmnSelection_WaitWasPlmnStopCnfSearchTD
 功能描述  : 等待WAS停止搜网搜TD状态收到打断MMC选网状态机消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年12月16日
   作    者   : w00167002
   修改内容   : 新生成函数:在W下搜网失败，进UTRANCTRL选择TD网络时候，收到第一阶段定
                时器超时等消息，触发打断选网状态机。当前MMC给W发STOP REQ请求，而不是
                给TD发STOP搜网请求，这样MMC后续又搜索Lte,出现双主模异常复位. 在消息打断选网状态机时候，
                需要先退出UTRANCTRL选网流程，再打断MMC选网状态机。此时如果MMC收到
                搜网失败消息时候，已经退出选网状态机，可能进入其它状态机，如ANYCELL
                搜网状态机，此时UTRAN保存的ABORT消息可丢弃不用处理。
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvMmcAbortFsmReqMsg_PlmnSelection_WaitWasPlmnStopCnfSearchTD(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 设置状态机打断标记 */
    NAS_UTRANCTRL_SetAbortFlg_PlmnSelection(VOS_TRUE);

    /* 设置MMC打断状态机标记 */
    NAS_UTRANCTRL_SetRcvMmcAbortFsmReqMsgFlg_PlmnSelection(VOS_TRUE);

    /* 消息处理完成不需继续处理 */
    return VOS_TRUE;
}




/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvTiWaitWasPlmnStopCnfExpired_PlmnSelection_WaitWasPlmnStopCnfSearchTD
 功能描述  : 等待WAS停止搜网回复过程中收到停止搜网回复超时消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年8月28日
   作    者   : w00167002
   修改内容   : 新生成函数
*****************************************************************************/

VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitWasPlmnStopCnfExpired_PlmnSelection_WaitWasPlmnStopCnfSearchTD(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstBufferEntryMsg = VOS_NULL_PTR;

    /* 获得当前缓存的缓冲区地址 */
    pstBufferEntryMsg = NAS_UTRANCTRL_GetBufferUtranSndMmcMsgAddr();

    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitWasPlmnStopCnfExpired_PlmnSelection_WaitWasPlmnStopCnfSearchTD: ENTERED");

    /* 收到了MMC打断状态机消息，则回到SUSPEND状态退出UTRANCTRL选网流程 */
    if (VOS_TRUE == NAS_UTRANCTRL_GetRcvMmcAbortFsmReqMsgFlg_PlmnSelection())
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitWasPlmnStopCnfExpired_PlmnSelection_WaitWasPlmnStopCnfSearchTD WITH MMC ABORT");

        /* 如果当前有MMC的打断，当前需要继续挂起当前模进行搜网 */
        NAS_UTRANCTRL_SndGuAsSuspendReq(WUEPS_PID_WRR);

        /* 迁移状态到等到WAS挂起回复 */
        NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF);

        /* 启动定时器 */
        NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF_LEN);

        /* 消息处理完成不需继续处理 */
        return VOS_TRUE;
    }

    /* 如果当前存在打断，则直接退出选网状态机 */
    if ( VOS_TRUE == NAS_UTRANCTRL_GetAbortFlg_PlmnSelection())
    {
        /* 构造指定搜网回复失败消息到内存的缓存区域 */
        NAS_UTRANCTRL_BuildRrMmPlmnSearchCnfFailMsg(WUEPS_PID_WRR,
                                                    WUEPS_PID_MMC,
                                                    NAS_UTRANCTRL_GetBufferedPlmnSearchReqType(),
                                                    (RRMM_PLMN_SEARCH_CNF_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

        /* 保存构造指定搜网回复失败消息事件类型 */
        pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );

        /* 设置需要替换入口消息标记 */
        NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

        /* 切换到MAIN状态机 */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* 将搜网失败消息发给MMC处理 */
        return VOS_FALSE;
    }

    /* 此时需要回到TD下,向WAS发送挂起请求 */
    NAS_UTRANCTRL_SndGuAsSuspendReq(WUEPS_PID_WRR);

    /* 迁移状态到等到was挂起回复 */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF);

    /* 启动保护定时器 */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF_LEN);

    /* 消息处理完成不需继续处理 */
    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvRrmmPlmnStopCnf_PlmnSelection_WaitTdPlmnStopCnfSearchW
 功能描述  : 等待TD停止搜网去搜TD回复过程中收到停止搜网回复消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年8月28日
   作    者   : w00167002
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvRrmmPlmnStopCnf_PlmnSelection_WaitTdPlmnStopCnfSearchW(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstBufferEntryMsg = VOS_NULL_PTR;

    /* 获得当前缓存的缓冲区地址 */
    pstBufferEntryMsg = NAS_UTRANCTRL_GetBufferUtranSndMmcMsgAddr();

    /* 停止保护定时器 */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_TD_PLMN_STOP_CNF);


    /* 收到了MMC打断状态机消息，则退出UTRANCTRL选网流程，通知MMC退出选网流程 */
    if (VOS_TRUE == NAS_UTRANCTRL_GetRcvMmcAbortFsmReqMsgFlg_PlmnSelection())
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvRrmmPlmnStopCnf_PlmnSelection_WaitTdPlmnStopCnfSearchW WITH MMC ABORT");

        /* 如果当前不存在打断，当前需要继续挂起当前模进行搜网 */
        NAS_UTRANCTRL_SndGuAsSuspendReq(TPS_PID_RRC);

        /* 迁移状态到等到TD挂起回复 */
        NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_SUSPEND_CNF);

        /* 启动定时器 */
        NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF_LEN);

        /* 消息处理完成 */
        return VOS_TRUE;
    }

    /* 如果当前存在打断，则直接退出选网状态机 */
    if ( VOS_TRUE == NAS_UTRANCTRL_GetAbortFlg_PlmnSelection())
    {
        /* 构造指定搜网回复失败消息到内存的缓存区域 */
        NAS_UTRANCTRL_BuildRrMmPlmnSearchCnfFailMsg(WUEPS_PID_WRR,
                                                    WUEPS_PID_MMC,
                                                    NAS_UTRANCTRL_GetBufferedPlmnSearchReqType(),
                                                    (RRMM_PLMN_SEARCH_CNF_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

        /* 保存构造指定搜网回复失败消息事件类型 */
        pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );

        /* 设置需要替换入口消息标记 */
        NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

        /* 切换到MAIN状态机 */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* 消息处理完成继续进入MMC状态机处理 */
        return VOS_FALSE;
    }

    /* 如果当前不存在打断，当前需要继续挂起当前模进行搜网 */
    NAS_UTRANCTRL_SndGuAsSuspendReq(TPS_PID_RRC);

    /* 迁移状态到等到TD挂起回复 */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_SUSPEND_CNF);

    /* 启动定时器 */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF_LEN);

    /* 消息处理完成不需继续处理 */
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvRrmmPlmnSearchCnf_PlmnSelection_WaitTdPlmnStopCnfSearchW
 功能描述  : 等待TD停止搜网去搜TD回复过程中收到搜网回复消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年6月25日
   作    者   : b00269685
   修改内容   : DSDS III新生成函数
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvRrmmPlmnSearchCnf_PlmnSelection_WaitTdPlmnStopCnfSearchW(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU          *pstSrchCnfMsg     = VOS_NULL_PTR;
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstBufferEntryMsg = VOS_NULL_PTR;

    pstSrchCnfMsg     = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;

    /* 获得当前缓存的缓冲区地址 */
    pstBufferEntryMsg = NAS_UTRANCTRL_GetBufferUtranSndMmcMsgAddr();

    /* 停止保护定时器 */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_TD_PLMN_STOP_CNF);

    if (VOS_TRUE == NAS_UTRANCTRL_GetRcvMmcAbortFsmReqMsgFlg_PlmnSelection())
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvRrmmPlmnSearchCnf_PlmnSelection_WaitTdPlmnStopCnfSearchW WITH MMC ABORT");

        /* 挂起当前模，通知MMC打断消息 */
        NAS_UTRANCTRL_SndGuAsSuspendReq(TPS_PID_RRC);

        /* 迁移状态到等到TD挂起回复 */
        NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_SUSPEND_CNF);

        /* 启动定时器 */
        NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF_LEN);

        /* 继续等待选网STOP CNF,丢弃当前搜网回复 */
        return VOS_TRUE;
    }

    /* 如果当前存在打断，则直接退出选网状态机 */
    if ( VOS_TRUE == NAS_UTRANCTRL_GetAbortFlg_PlmnSelection())
    {
        /* 构造指定搜网回复失败消息到内存的缓存区域 */
        NAS_UTRANCTRL_BuildRrMmPlmnSearchCnfFailMsg(WUEPS_PID_WRR,
                                                    WUEPS_PID_MMC,
                                                    NAS_UTRANCTRL_GetBufferedPlmnSearchReqType(),
                                                    (RRMM_PLMN_SEARCH_CNF_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

        /* 保存构造指定搜网回复失败消息事件类型 */
        pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );

        /* 设置需要替换入口消息标记 */
        NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

        /* 切换到MAIN状态机 */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* 消息处理完成继续进入MMC状态机处理 */
        return VOS_FALSE;
    }

    /* 如果搜网失败，原因为NO RF，则直接进MMC处理，设置当前为TDD模式 */
    if ((RRC_PLMN_SEARCH_RLT_SPEC_NO_RF     == pstSrchCnfMsg->ulSearchRlt)
     || (RRC_PLMN_SEARCH_RLT_HISTORY_NO_RF  == pstSrchCnfMsg->ulSearchRlt))
    {
        NAS_UTRANCTRL_SetCurrUtranMode(NAS_UTRANCTRL_UTRAN_MODE_TDD);

        /* 状态机切换到MAIN */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* 进MMC状态机处理 */
        return VOS_FALSE;
    }

    /* 如果当前不存在打断，当前需要继续挂起当前模进行搜网 */
    NAS_UTRANCTRL_SndGuAsSuspendReq(TPS_PID_RRC);

    /* 迁移状态到等到TD挂起回复 */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_SUSPEND_CNF);

    /* 启动定时器 */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF_LEN);

    /* 消息处理完成不需继续处理 */
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdPlmnStopCnfSearchW
 功能描述  : 等待TD停止搜网去搜TD回复过程中收到用户请求消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年8月28日
   作    者   : w00167002
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdPlmnStopCnfSearchW(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 记录状态机打断标记 */
    NAS_UTRANCTRL_SetAbortFlg_PlmnSelection(VOS_TRUE);

    /* 缓存当前用户请求消息 */
    NAS_UTRANCTRL_SaveCacheMsgInMsgQueue(ulEventType, pstMsg);

    /* 消息处理完成不需继续处理 */
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvMmcAbortFsmReqMsg_PlmnSelection_WaitTdPlmnStopCnfSearchW
 功能描述  : 等待TD停止搜网搜W状态收到打断MMC选网状态机消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年12月16日
   作    者   : w00167002
   修改内容   : 新生成函数:在W下搜网失败，进UTRANCTRL选择TD网络时候，收到第一阶段定
                时器超时等消息，触发打断选网状态机。当前MMC给W发STOP REQ请求，而不是
                给TD发STOP搜网请求，这样MMC后续又搜索Lte,出现双主模异常复位. 在消息打断选网状态机时候，
                需要先退出UTRANCTRL选网流程，再打断MMC选网状态机。
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvMmcAbortFsmReqMsg_PlmnSelection_WaitTdPlmnStopCnfSearchW(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 设置状态机打断标记 */
    NAS_UTRANCTRL_SetAbortFlg_PlmnSelection(VOS_TRUE);

    /* 设置收到MMC打断选网状态机消息标记 */
    NAS_UTRANCTRL_SetRcvMmcAbortFsmReqMsgFlg_PlmnSelection(VOS_TRUE);

    /* 消息处理完成不需继续处理 */
    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvTiWaitTdPlmnStopCnfExpired_PlmnSelection_WaitTdPlmnStopCnfSearchW
 功能描述  : 等待TD停止搜网回复过程中收到停止搜网回复超时消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年8月28日
   作    者   : w00167002
   修改内容   : 新生成函数
*****************************************************************************/

VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitTdPlmnStopCnfExpired_PlmnSelection_WaitTdPlmnStopCnfSearchW(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstBufferEntryMsg = VOS_NULL_PTR;


    /* 获得当前缓存的缓冲区地址 */
    pstBufferEntryMsg = NAS_UTRANCTRL_GetBufferUtranSndMmcMsgAddr();

    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitTdPlmnStopCnfExpired_PlmnSelection_WaitTdPlmnStopCnfSearchW: ENTERED");


    /* 收到了MMC打断状态机消息，则退出UTRANCTRL选网流程，通知MMC退出选网流程 */
    if (VOS_TRUE == NAS_UTRANCTRL_GetRcvMmcAbortFsmReqMsgFlg_PlmnSelection())
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitTdPlmnStopCnfExpired_PlmnSelection_WaitTdPlmnStopCnfSearchW WITH MMC ABORT");

        /* 如果当前不存在打断，当前需要继续挂起当前模进行搜网 */
        NAS_UTRANCTRL_SndGuAsSuspendReq(TPS_PID_RRC);

        /* 迁移状态到等到TD挂起回复 */
        NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_SUSPEND_CNF);

        /* 启动定时器 */
        NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF_LEN);

        /* 消息处理完成 */
        return VOS_TRUE;
    }

    /* 如果当前存在打断，则直接退出选网状态机 */
    if ( VOS_TRUE == NAS_UTRANCTRL_GetAbortFlg_PlmnSelection())
    {
        /* 构造指定搜网回复失败消息到内存的缓存区域 */
        NAS_UTRANCTRL_BuildRrMmPlmnSearchCnfFailMsg(WUEPS_PID_WRR,
                                                    WUEPS_PID_MMC,
                                                    NAS_UTRANCTRL_GetBufferedPlmnSearchReqType(),
                                                    (RRMM_PLMN_SEARCH_CNF_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

        /* 保存构造指定搜网回复失败消息事件类型 */
        pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );

        /* 设置需要替换入口消息标记 */
        NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

        /* 切换到MAIN状态机 */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* 将搜网失败消息发给MMC处理 */
        return VOS_FALSE;
    }

    /* 此时需要回到w下搜网,向TD发送挂起请求 */
    NAS_UTRANCTRL_SndGuAsSuspendReq(TPS_PID_RRC);

    /* 迁移状态到等到TD挂起回复 */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_SUSPEND_CNF);

    /* 启动保护定时器 */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF_LEN);

    /* 消息处理完成不需继续处理 */
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_IsNeedBuildSearchCnfMsg_WaitSuspendCnf
 功能描述  : 收到suspend cnf的时候是否需要构造搜网回复消息
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_FALSE:不需要
             VOS_TRUE:需要
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年5月23日
   作    者   : b00269685
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_IsNeedBuildSearchCnfMsg_WaitSuspendCnf()
{
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstEntryMsg       = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader      = VOS_NULL_PTR;

    /* 取当前缓存的系统消息 */
    pstEntryMsg = NAS_UTRANCTRL_GetCurrEntryMsgAddr();

    /* 取得当前缓存消息的头 */
    pstMsgHeader = (MSG_HEADER_STRU *)pstEntryMsg->aucEntryMsgBuffer;

    if (VOS_PID_TIMER == pstMsgHeader->ulSenderPid)
    {
        return VOS_TRUE;
    }

    if (pstEntryMsg->ulEventType == NAS_UTRANCTRL_BuildEventType(WUEPS_PID_MMC, MMCMMC_INTER_SKIP_SEARCH_W_IND))
    {
        return VOS_TRUE;
    }

    if (pstEntryMsg->ulEventType == NAS_UTRANCTRL_BuildEventType(WUEPS_PID_MMC, MMCMMC_INTER_SKIP_SEARCH_TDS_IND))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvRrmmSuspendCnf_PlmnSelection_WaitWasSuspendCnf
 功能描述  : 等待WAS挂起回复状态收到WAS挂起回复消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月4日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2014年2月11日
   作    者   : w00167002
   修改内容   : 跳过搜网W结果.
                注:SVLTE共天线，在W下搜网NO RF后，在G下搜网成功国内驻留成功后，
                后续再发起搜网时候不能搜WAS,否则G会丢网。但在UTRANCTRL状态机时候
                ，NO RF时候当前是FDD模式的，因而MMC再发起搜网时候，会先给WAS发送，
                UTRAN构造SKIP W消息，在UTRANCTRL状态机搜索TDD.
 3.日    期   : 2015年8月26日
   作    者   : w00242748
   修改内容   : 动态加载项目

 4.日    期   : 2015年12月17日
   作    者   : w00167002
   修改内容   : 在W下搜网失败，进UTRANCTRL选择TD网络时候，收到第一阶段定
                时器超时等消息，触发打断选网状态机。当前MMC选网状态机给W发STOP REQ请求，而不是
                给TD发STOP搜网请求，这样MMC后续又搜索Lte,出现双主模异常复位. 在消息打断选网状态机时候，
                需要先退出UTRANCTRL选网流程，再打断MMC选网状态机。此时MMC收到选网状态机被MMC发送的
                abort消息打断，则可退出选网状态机。
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvRrmmSuspendCnf_PlmnSelection_WaitWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstEntryMsg       = VOS_NULL_PTR;
    RRMM_SUSPEND_CNF_ST                *pstRrmmSuspendCnf = VOS_NULL_PTR;

    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstBufferEntryMsg = VOS_NULL_PTR;

    /* 获得当前缓存的缓冲区地址 */
    pstBufferEntryMsg = NAS_UTRANCTRL_GetBufferUtranSndMmcMsgAddr();

    pstRrmmSuspendCnf  = (RRMM_SUSPEND_CNF_ST*)pstMsg;

    if (MMC_AS_SUSPEND_FAILURE == pstRrmmSuspendCnf->ucResult)
    {
        /* 单板复位 */
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_WAS_SUSPEND_FAILURE);
        return VOS_TRUE;
    }

    /* 停止保护定时器 */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF);


    /* 收到了MMC打断状态机消息，则退出UTRANCTRL选网流程，通知MMC退出选网流程 */
    if (VOS_TRUE == NAS_UTRANCTRL_GetRcvMmcAbortFsmReqMsgFlg_PlmnSelection())
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvRrmmSuspendCnf_PlmnSelection_WaitWasSuspendCnf WITH MMC ABORT");

        NAS_UTRANCTRL_BuildInterUtranCtrlPlmnSelectionAbortFinishIndMsg((NAS_MMCMMC_INTER_UTRAN_CTRL_PLMN_SELECTION_ABORT_FINISH_IND_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

        /* 保存构造指定搜网回复失败消息事件类型 */
        pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );

        /* 设置需要替换入口消息标记 */
        NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

        /* 切换到MAIN状态机 */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* 消息处理完成继续进入MMC状态机处理 */
        return VOS_FALSE;
    }

    /* 状态机打断标记不存在 */
    if (VOS_FALSE == NAS_UTRANCTRL_GetAbortFlg_PlmnSelection())
    {
#if (FEATURE_ON == FEATURE_TDS_WCDMA_DYNAMIC_LOAD)
        if (VOS_TRUE == NAS_DYNLOAD_GetEnableDynloadTWFlg())
        {
            (VOS_VOID)NAS_DYNLOAD_LoadAS(NAS_DYNLOAD_LOAD_RATCOMB_TYPE_T_W, VOS_RATMODE_TDS);
        }
#endif

        /* 向TDRRC发送指定搜网请求 */
        NAS_UTRANCTRL_SndGuAsSpecPlmnSearchReq(TPS_PID_RRC);

        /* 迁移状态到等到TDRRC搜网回复 */
        NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_PLMN_SEARCH_CNF);

        /* 启动定时器 */
        NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_PLMN_SEARCH_CNF, TI_NAS_UTRANCTRL_WAIT_TD_PLMN_SEARCH_CNF_LEN);

        /* 消息处理完成不需继续进入MMC状态机处理 */
        return VOS_TRUE;
    }

    /* 取当前缓存的系统消息 */
    pstEntryMsg = NAS_UTRANCTRL_GetCurrEntryMsgAddr();



    /* 如果当前的入口消息为定时器超时,或者MMC发送的内部SKIP 搜索W消息，则需要构造搜网回复失败消息 */
    if (VOS_TRUE == NAS_UTRANCTRL_IsNeedBuildSearchCnfMsg_WaitSuspendCnf())
    {

        /* 构造指定搜网回复失败消息到内存的缓存区域 */
        NAS_UTRANCTRL_BuildRrMmPlmnSearchCnfFailMsg(WUEPS_PID_WRR,
                                                    WUEPS_PID_MMC,
                                                    NAS_UTRANCTRL_GetBufferedPlmnSearchReqType(),
                                                   (RRMM_PLMN_SEARCH_CNF_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

        /* 保存构造指定搜网回复失败消息事件类型 */
        pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );
    }
    else
    {
        /* 取缓存的状态机搜网回复失败消息给MMC模块 */
        NAS_UTRANCTRL_SaveBufferUtranSndMmcMsg(pstEntryMsg->ulEventType,
                                (struct MsgCB *)pstEntryMsg->aucEntryMsgBuffer);

    }

    /* 设置需要替换入口消息标记 */
    NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

    /* 切换到MAIN状态机 */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

    /* 消息处理完成继续进入MMC状态机处理 */
    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasSuspendCnf
 功能描述  : 等待WAS挂起回复状态收到用户请求消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月4日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 设置状态机打断标记 */
    NAS_UTRANCTRL_SetAbortFlg_PlmnSelection(VOS_TRUE);

    /* 缓存当前用户请求消息 */
    NAS_UTRANCTRL_SaveCacheMsgInMsgQueue(ulEventType, pstMsg);

    /* 消息处理完成不需继续处理 */
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvMmcAbortFsmReqMsg_PlmnSelection_WaitWasSuspendCnf
 功能描述  : 等待WAS挂起回复状态收到打断MMC选网状态机消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年12月16日
   作    者   : w00167002
   修改内容   : 在W下搜网失败，进UTRANCTRL选择TD网络时候，收到第一阶段定
                时器超时等消息，触发打断选网状态机。当前MMC选网状态机给W发STOP REQ请求，而不是
                给TD发STOP搜网请求，这样MMC后续又搜索Lte,出现双主模异常复位. 在消息打断选网状态机时候，
                需要先退出UTRANCTRL选网流程，再打断MMC选网状态机。此时MMC收到选网状态机被MMC发送的
                abort消息打断，则可退出选网状态机。
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvMmcAbortFsmReqMsg_PlmnSelection_WaitWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 设置状态机打断标记 */
    NAS_UTRANCTRL_SetAbortFlg_PlmnSelection(VOS_TRUE);

    /* 缓存当前打断选网状态机消息 */
    NAS_UTRANCTRL_SetRcvMmcAbortFsmReqMsgFlg_PlmnSelection(VOS_TRUE);

    /* 消息处理完成不需继续处理 */
    return VOS_TRUE;
}



/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvTiWaitWasSuspendCnfExpired_PlmnSelection_WaitWasSuspendCnf
 功能描述  : 等待WAS挂起回复状态suspend CNF过程中保护定时器超时
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月4日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitWasSuspendCnfExpired_PlmnSelection_WaitWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 异常打印 */
    NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitWasSuspendCnfExpired_PlmnSelection_WaitWasSuspendCnf: ENTERED");

    /* 复位 */
    NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_WAS_SUSPEND_CNF_EXPIRED);

    /* 消息处理完成不需继续处理 */
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvRrmmSuspendCnf_PlmnSelection_WaitTdSuspendCnf
 功能描述  : 等待TD挂起回复状态收到TDRRC挂起回复消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月4日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2014年10月31日
   作    者   : z00161729
   修改内容   : 开机漫游搜网项目修改
 3.日    期   : 2015年8月26日
   作    者   : w00242748
   修改内容   : 动态加载项目
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvRrmmSuspendCnf_PlmnSelection_WaitTdSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstEntryMsg       = VOS_NULL_PTR;
    RRMM_SUSPEND_CNF_ST                *pstRrmmSuspendCnf = VOS_NULL_PTR;

    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstBufferEntryMsg = VOS_NULL_PTR;

    pstBufferEntryMsg = NAS_UTRANCTRL_GetBufferUtranSndMmcMsgAddr();
    pstRrmmSuspendCnf = (RRMM_SUSPEND_CNF_ST*)pstMsg;

    if (MMC_AS_SUSPEND_FAILURE == pstRrmmSuspendCnf->ucResult)
    {
        /* 单板复位 */
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_TD_SUSPEND_FAILURE);
        return VOS_TRUE;
    }

    /* 停止保护定时器 */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF);


    /* 收到了MMC打断状态机消息，则退出UTRANCTRL选网流程，通知MMC退出选网流程 */
    if (VOS_TRUE == NAS_UTRANCTRL_GetRcvMmcAbortFsmReqMsgFlg_PlmnSelection())
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvRrmmSuspendCnf_PlmnSelection_WaitTdSuspendCnf WITH MMC ABORT");

        NAS_UTRANCTRL_BuildInterUtranCtrlPlmnSelectionAbortFinishIndMsg((NAS_MMCMMC_INTER_UTRAN_CTRL_PLMN_SELECTION_ABORT_FINISH_IND_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

        /* 保存构造指定搜网回复失败消息事件类型 */
        pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );

        /* 设置需要替换入口消息标记 */
        NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

        /* 切换到MAIN状态机 */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* 消息处理完成继续进入MMC状态机处理 */
        return VOS_FALSE;
    }

    /* 状态机打断标记不存在 */
    if (VOS_FALSE == NAS_UTRANCTRL_GetAbortFlg_PlmnSelection())
    {
#if (FEATURE_ON == FEATURE_TDS_WCDMA_DYNAMIC_LOAD)
        if (VOS_TRUE == NAS_DYNLOAD_GetEnableDynloadTWFlg())
        {
            (VOS_VOID)NAS_DYNLOAD_LoadAS(NAS_DYNLOAD_LOAD_RATCOMB_TYPE_T_W, VOS_RATMODE_WCDMA);
        }
#endif
        /* 向WAS发送指定搜网请求 */
        NAS_UTRANCTRL_SndGuAsSpecPlmnSearchReq(WUEPS_PID_WRR);

        /* 迁移状态到等到WAS搜网回复 */
        NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_PLMN_SEARCH_CNF);

        /* 启动定时器 */
        NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_SEARCH_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_SEARCH_CNF_LEN);

        /* 消息处理完成不需继续处理 */
        return VOS_TRUE;
    }

    /* 取当前缓存的系统消息 */
    pstEntryMsg = NAS_UTRANCTRL_GetCurrEntryMsgAddr();

    /* 如果当前的入口消息为定时器超时，或者MMC发送的内部SKIP 搜索TDS消息,则需要构造搜网回复失败消息 */
    if (VOS_TRUE == NAS_UTRANCTRL_IsNeedBuildSearchCnfMsg_WaitSuspendCnf())
    {
        /* 构造指定搜网回复失败消息到内存的缓存区域 */
        NAS_UTRANCTRL_BuildRrMmPlmnSearchCnfFailMsg(WUEPS_PID_WRR,
                                                    WUEPS_PID_MMC,
                                                    NAS_UTRANCTRL_GetBufferedPlmnSearchReqType(),
                                                   (RRMM_PLMN_SEARCH_CNF_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

        /* 保存构造指定搜网回复失败消息事件类型 */
        pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );
    }
    else
    {
        /* 取缓存的状态机搜网回复失败消息给MMC模块 */
        NAS_UTRANCTRL_SaveBufferUtranSndMmcMsg(pstEntryMsg->ulEventType,
                                (struct MsgCB *)pstEntryMsg->aucEntryMsgBuffer);

    }

    /* 设置需要替换入口消息标记 */
    NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

    /* 切换到MAIN状态机 */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

    /* 消息处理完成继续进入MMC状态机处理 */
    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdSuspendCnf
 功能描述  : 等待TD挂起回复状态收到用户请求消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月4日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 设置状态机打断标记 */
    NAS_UTRANCTRL_SetAbortFlg_PlmnSelection(VOS_TRUE);

    /* 缓存当前用户请求消息 */
    NAS_UTRANCTRL_SaveCacheMsgInMsgQueue(ulEventType, pstMsg);

    /* 消息处理完成不需继续处理 */
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvMmcAbortFsmReqMsg_PlmnSelection_WaitTdSuspendCnf
 功能描述  : 等待TD挂起回复状态收到打断MMC选网状态机消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年12月16日
   作    者   : w00167002
   修改内容   : 新生成函数:在收到SUSPEND CNF后，给MMC发送打断UTRANCTRL结果消息。
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvMmcAbortFsmReqMsg_PlmnSelection_WaitTdSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 设置状态机打断标记 */
    NAS_UTRANCTRL_SetAbortFlg_PlmnSelection(VOS_TRUE);

    /* 设置接收到MMC打断状态机消息标志 */
    NAS_UTRANCTRL_SetRcvMmcAbortFsmReqMsgFlg_PlmnSelection(VOS_TRUE);

    /* 消息处理完成不需继续处理 */
    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvTiWaitTdSuspendCnfExpired_PlmnSelection_WaitTdSuspendCnf
 功能描述  : 等待TD挂起回复状态suspend CNF过程中保护定时器超时
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月4日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitTdSuspendCnfExpired_PlmnSelection_WaitTdSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 异常打印 */
    NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitTdSuspendCnfExpired_PlmnSelection_WaitTdSuspendCnf: ENTERED");

    /* 复位 */
    NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_TD_SUSPEND_CNF_EXPIRED);

    /* 消息处理完成不需继续处理 */
    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvRrmmPlmnSearchCnf_PlmnSelection_WaitWasPlmnSearchCnf
 功能描述  : 等待WAS搜网回复过程中收到WAS搜网回复的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年8月4日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2014年1月20日
   作    者   : w00167002
   修改内容   : SVLTE共天线项目:在W下搜网失败为NO RF，表示当前天线资源不可用，
                则不需要再搜TD，直接进入MMC状态机进行处理，当前处在FDD模式。
 3.日    期   : 2014年11月8日
   作    者   : z00161729
   修改内容   : 开机搜网优化项目修改

*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvRrmmPlmnSearchCnf_PlmnSelection_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU          *pstSrchCnfMsg;

    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstEntryMsg       = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader      = VOS_NULL_PTR;

    /* 取当前缓存的系统消息 */
    pstEntryMsg = NAS_UTRANCTRL_GetCurrEntryMsgAddr();

    /* 取得当前缓存消息的头 */
    pstMsgHeader = (MSG_HEADER_STRU *)pstEntryMsg->aucEntryMsgBuffer;

    pstSrchCnfMsg = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;

    /* 停止保护定时器 */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_SEARCH_CNF);

    /* 如果搜网成功 */
    if ((RRC_PLMN_SEARCH_RLT_SPEC           == pstSrchCnfMsg->ulSearchRlt)
     || (RRC_PLMN_SEARCH_RLT_HISTORY_SUCC   == pstSrchCnfMsg->ulSearchRlt))
    {
        /* 状态机切换到MAIN */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* 进MMC状态机处理 */
        return VOS_FALSE;
    }


    /* 如果搜网失败，原因为NO RF，则直接进MMC处理，设置当前为FDD模式 */
    if ((RRC_PLMN_SEARCH_RLT_SPEC_NO_RF     == pstSrchCnfMsg->ulSearchRlt)
     || (RRC_PLMN_SEARCH_RLT_HISTORY_NO_RF  == pstSrchCnfMsg->ulSearchRlt))
    {
        NAS_UTRANCTRL_SetCurrUtranMode(NAS_UTRANCTRL_UTRAN_MODE_FDD);

        /* 状态机切换到MAIN */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* 进MMC状态机处理 */
        return VOS_FALSE;
    }

    /* 根据搜网列表更新中国网络标记 */
    if (MMCMMC_INTER_SKIP_SEARCH_TDS_IND != pstMsgHeader->ulMsgName)
    {
        NAS_UTRANCTRL_UpdateSearchedSpecTdMccFLg(NAS_UTRANCTRL_GetSpecTdMccListNum(),
                                                 NAS_UTRANCTRL_GetSpecTdMccList(),
                                                 &(pstSrchCnfMsg->PlmnIdList));

        /* 根据中国网络标记设置utran工作模式 */
        if (VOS_TRUE == NAS_UTRANCTRL_GetSearchedSpecTdMccFlg())
        {
            NAS_UTRANCTRL_SetCurrUtranMode(NAS_UTRANCTRL_UTRAN_MODE_TDD);
        }
        else if ((0 != pstSrchCnfMsg->PlmnIdList.ulHighPlmnNum)
              || (0 != pstSrchCnfMsg->PlmnIdList.ulLowPlmnNum))
        {
            /* 未搜到中国网络并且W携带非空列表,更新工作模式为FDD */
            NAS_UTRANCTRL_SetCurrUtranMode(NAS_UTRANCTRL_UTRAN_MODE_FDD);
        }
        else
        {
            /* W携带空列表不修改工作模式 */
        }
    }

    /* 根据当前工作模式为TDD则需要回到TD下 */
    if (NAS_UTRANCTRL_UTRAN_MODE_TDD   == NAS_UTRANCTRL_GetCurrUtranMode())
    {
        NAS_UTRANCTRL_SndGuAsSuspendReq(WUEPS_PID_WRR);

        /* 迁移状态到等待回TD时W的挂起回复状态 */
        NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF_BACK_TD);

        /* 启动保护定时器 */
        NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF_LEN);

        /* 消息处理完成不需继续处理 */
        return VOS_TRUE;
    }

    /* 状态机切换到MAIN */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

    /* 消息处理完成继续进入MMC状态机处理 */
    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvInterAbortUtranCtrlPlmnSearchReq_PlmnSelection_WaitWasPlmnSearchCnf
 功能描述  : 等待WAS搜网回复过程中收到inter abort plmn search req的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年11月13日
   作    者   : z00161729
   修改内容   : 开机搜网优化项目修改
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvInterAbortUtranCtrlPlmnSearchReq_PlmnSelection_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止保护定时器 */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_SEARCH_CNF);

    /* 更新utran mode为fdd，utranctrl 搜网状态机退出，消息进mmc继续处理，通知接入层打断由mmc处理 */
    NAS_UTRANCTRL_SetCurrUtranMode(NAS_UTRANCTRL_UTRAN_MODE_FDD);

    /* 通知mmc MMCMMC_INTER_ABORT_UTRAN_CTRL_PLMN_SEARCH_CNF*/
    NAS_MMC_SndInterAbortUtranCtrlPlmnSearchCnfMsg();

    /* 状态机切换到MAIN */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

    return VOS_TRUE;
}





/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvTdPlmnSearchCnf_PlmnSelection_WaitWasPlmnSearchCnf
 功能描述  : 等W模时候收到TD接入层搜网回复消息的处理
 输入参数  : ulEventType: 消息类型,
              pstMsg: RRMM_PLMN_SEARCH_CNF消息的结构体首址
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月7日
    作    者   : w00167002
    修改内容   : V7R1C50_GUTL_PhaseII:新生成函数
*****************************************************************************/
VOS_UINT32  NAS_UTRANCTRL_RcvTdPlmnSearchCnf_PlmnSelection_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTdPlmnSearchCnf_PlmnSelection_WaitWasPlmnSearchCnf: illegal MESSAGE! ");

    /* 丢弃该非法消息 */
    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvRrmmRelInd_PlmnSelection_WaitWasPlmnSearchCnf
 功能描述  : 等待WAS搜网回复过程中收到RRMM_REL_IND的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年8月4日
   作    者   : w00176964
   修改内容   : 新生成函数

 2.日    期   : 2014年6月12日
   作    者   : w00167002
   修改内容   : WAS异常且NO RF,直接进MMC状态机进行处理
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvRrmmRelInd_PlmnSelection_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_REL_IND_STRU                  *pstRrmmRelIndMsg    = VOS_NULL_PTR;

    pstRrmmRelIndMsg = (RRMM_REL_IND_STRU *)pstMsg;

    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvRrmmRelInd_PlmnSelection_WaitWasPlmnSearchCnf: ENTERED");

    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_SEARCH_CNF);


    /* 如果搜网失败，原因为NO RF，则直接进MMC处理，维持当前为FDD模式 */
    if (RRC_REL_CAUSE_NO_RF == pstRrmmRelIndMsg->ulRelCause)
    {
        NAS_UTRANCTRL_SetCurrUtranMode(NAS_UTRANCTRL_UTRAN_MODE_FDD);

        /* 状态机切换到MAIN */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* 进MMC状态机处理 */
        return VOS_FALSE;
    }

    /* 当前未搜到中国的网络,则认为仍然在TD下,模式保持不变 */
    NAS_UTRANCTRL_SndGuAsSuspendReq(WUEPS_PID_WRR);

    /* 迁移状态到等待回TD时W的挂起回复状态 */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF_BACK_TD);

    /* 启动保护定时器 */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF_LEN);

    /* 消息处理完成不需继续处理 */
    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasPlmnSearchCnf
 功能描述  : 等待WAS搜网回复状态收到用户请求消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月4日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 记录状态机打断标记 */
    NAS_UTRANCTRL_SetAbortFlg_PlmnSelection(VOS_TRUE);

    /* 停止保护定时器 */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_SEARCH_CNF);

    /* 缓存当前用户请求消息 */
    NAS_UTRANCTRL_SaveCacheMsgInMsgQueue(ulEventType, pstMsg);

    /* 向WAS发送停止搜网请求 */
    NAS_UTRANCTRL_SndGuAsPlmnStopReq(WUEPS_PID_WRR);

    /* 迁移状态到等到WAS搜网回复 */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_PLMN_STOP_CNF);

    /* 启动保护定时器 */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_STOP_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_STOP_CNF_LEN);

    /* 消息处理完成不需继续处理 */
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvMmcAbortFsmReqMsg_PlmnSelection_WaitWasPlmnSearchCnf
 功能描述  : 等待WAS挂起回复状态收到打断MMC选网状态机消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年12月16日
   作    者   : w00167002
   修改内容   : 新生成函数:在W下搜网失败，进UTRANCTRL选择TD网络时候，收到第一阶段定
                时器超时等消息，触发打断选网状态机。当前MMC给W发STOP REQ请求，而不是
                给TD发STOP搜网请求，这样MMC后续又搜索Lte,出现双主模异常复位. 在消息打断选网状态机时候，
                需要先退出UTRANCTRL选网流程，再打断MMC选网状态机。
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvMmcAbortFsmReqMsg_PlmnSelection_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvMmcAbortFsmReqMsg_PlmnSelection_WaitWasPlmnSearchCnf WITH MMC ABORT");

    /* 停止保护定时器 */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_SEARCH_CNF);

    /* 设置状态机打断标记 */
    NAS_UTRANCTRL_SetAbortFlg_PlmnSelection(VOS_TRUE);

    /* 设置打断 */
    NAS_UTRANCTRL_SetRcvMmcAbortFsmReqMsgFlg_PlmnSelection(VOS_TRUE);

    /* 向WAS发送停止搜网请求 */
    NAS_UTRANCTRL_SndGuAsPlmnStopReq(WUEPS_PID_WRR);

    /* 迁移状态到等到WAS搜网回复 */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_PLMN_STOP_CNF);

    /* 启动保护定时器 */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_STOP_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_STOP_CNF_LEN);

    /* 消息处理完成不需继续处理 */
    return VOS_TRUE;
}



/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvTiWaitWasPlmnSearchCnfExpired_PlmnSelection_WaitWasPlmnSearchCnf
 功能描述  : 等待WAS搜网回复过程中等待WAS搜网回复超时消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年8月4日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitWasPlmnSearchCnfExpired_PlmnSelection_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitWasPlmnSearchCnfExpired_PlmnSelection_WaitWasPlmnSearchCnf: ENTERED");

    /* 停止WAS搜网 */
    NAS_UTRANCTRL_SndGuAsPlmnStopReq(WUEPS_PID_WRR);

    /* 迁移状态到等到WAS停止搜网回复 */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_PLMN_STOP_CNF);

    /* 启动保护定时器 */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_STOP_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_STOP_CNF_LEN);

    /* 消息处理完成不需继续处理 */
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvMmcInterSkipSearchWasIndMsg_PlmnSelection_WaitWasPlmnSearchCnf
 功能描述  : 等待WAS搜网回复过程中等待WAS搜网回复超时消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年5月18日
   作    者   : b00269685
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvMmcInterSkipSearchWasIndMsg_PlmnSelection_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停定时器 */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_SEARCH_CNF);

    /* 停止WAS搜网 */
    NAS_UTRANCTRL_SndGuAsPlmnStopReq(WUEPS_PID_WRR);

    /* 迁移状态到等到WAS停止搜网回复 */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_PLMN_STOP_CNF);

    /* 启动保护定时器 */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_STOP_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_STOP_CNF_LEN);

    /* 消息处理完成不需继续处理 */
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvRrmmPlmnSearchCnf_PlmnSelection_WaitTdPlmnSearchCnf
 功能描述  : 等待TD搜网回复过程中收到TDRRC搜网回复消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年8月4日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2014年6月12日
   作    者   : w00167002
   修改内容   : DSDS III:在NO RF后进MMC处理
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvRrmmPlmnSearchCnf_PlmnSelection_WaitTdPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU          *pstSrchCnfMsg = VOS_NULL_PTR;

    pstSrchCnfMsg = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;

    /* 停止保护定时器 */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_TD_PLMN_SEARCH_CNF);

    /* 如果指定搜网成功或history搜成功 */
    if ((RRC_PLMN_SEARCH_RLT_SPEC           == pstSrchCnfMsg->ulSearchRlt)
     || (RRC_PLMN_SEARCH_RLT_HISTORY_SUCC   == pstSrchCnfMsg->ulSearchRlt))
    {
        /* 状态机切换到MAIN */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* 进MMC状态机处理 */
        return VOS_FALSE;
    }


    /* 如果搜网失败，原因为NO RF，则直接进MMC处理，维持当前为TDD模式 */
    if ((RRC_PLMN_SEARCH_RLT_SPEC_NO_RF     == pstSrchCnfMsg->ulSearchRlt)
     || (RRC_PLMN_SEARCH_RLT_HISTORY_NO_RF  == pstSrchCnfMsg->ulSearchRlt))
    {
        NAS_UTRANCTRL_SetCurrUtranMode(NAS_UTRANCTRL_UTRAN_MODE_TDD);

        /* 状态机切换到MAIN */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* 进MMC状态机处理 */
        return VOS_FALSE;
    }

    /* 根据搜网列表更新中国网络标记 */
    NAS_UTRANCTRL_UpdateSearchedSpecTdMccFLg(NAS_UTRANCTRL_GetSpecTdMccListNum(),
                                             NAS_UTRANCTRL_GetSpecTdMccList(),
                                             &(pstSrchCnfMsg->PlmnIdList));

    /* 根据中国网络标记设置utran工作模式 */
    if (VOS_TRUE == NAS_UTRANCTRL_GetSearchedSpecTdMccFlg())
    {
        NAS_UTRANCTRL_SetCurrUtranMode(NAS_UTRANCTRL_UTRAN_MODE_TDD);
    }

    /* 根据当前工作模式为FDD则需要回到W下 */
    if (NAS_UTRANCTRL_UTRAN_MODE_FDD   == NAS_UTRANCTRL_GetCurrUtranMode())
    {
        /* 挂起TD */
        NAS_UTRANCTRL_SndGuAsSuspendReq(TPS_PID_RRC);

        /* 迁移状态到等待回W时TD的挂起回复状态 */
        NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_SUSPEND_CNF_BACK_W);

        /* 启动保护定时器 */
        NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF_LEN);

        /* 消息处理完成不需继续处理 */
        return VOS_TRUE;
    }

    /* 状态机切换到MAIN */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

    /* 消息处理完成继续进入MMC状态机处理 */
    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvWasPlmnSearchCnf_PlmnSelection_WaitTdPlmnSearchCnf
 功能描述  : 等TD模时候收到WAS接入层搜网回复消息的处理
 输入参数  : ulEventType: 消息类型,
              pstMsg: RRMM_PLMN_SEARCH_CNF消息的结构体首址
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月7日
    作    者   : w00167002
    修改内容   : V7R1C50_GUTL_PhaseII:新生成函数
*****************************************************************************/
VOS_UINT32  NAS_UTRANCTRL_RcvWasPlmnSearchCnf_PlmnSelection_WaitTdPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvWasPlmnSearchCnf_PlmnSelection_WaitTdPlmnSearchCnf: illegal MESSAGE! ");

    /* 丢弃该非法消息 */
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdPlmnSearchCnf
 功能描述  : 等待td搜网回复状态收到用户请求消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月4日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 记录状态机打断标记 */
    NAS_UTRANCTRL_SetAbortFlg_PlmnSelection(VOS_TRUE);

    /* 停止保护定时器 */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_TD_PLMN_SEARCH_CNF);

    /* 缓存当前用户请求消息 */
    NAS_UTRANCTRL_SaveCacheMsgInMsgQueue(ulEventType, pstMsg);

    /* 向TDRRC发送停止搜网请求 */
    NAS_UTRANCTRL_SndGuAsPlmnStopReq(TPS_PID_RRC);

    /* 迁移状态到等到TDRRC停止搜网回复 */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_PLMN_STOP_CNF);

    /* 启动保护定时器 */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_PLMN_STOP_CNF, TI_NAS_UTRANCTRL_WAIT_TD_PLMN_STOP_CNF_LEN);

    /* 消息处理完成不需继续处理 */
    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvMmcAbortFsmReqMsg_PlmnSelection_WaitTdPlmnSearchCnf
 功能描述  : 等待TDRRC搜网回复状态收到打断MMC选网状态机消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年12月16日
   作    者   : w00167002
   修改内容   : 新生成函数:在W下搜网失败，进UTRANCTRL选择TD网络时候，收到第一阶段定
                时器超时等消息，触发打断选网状态机。当前MMC给W发STOP REQ请求，而不是
                给TD发STOP搜网请求，这样MMC后续又搜索Lte,出现双主模异常复位. 在消息打断选网状态机时候，
                需要先退出UTRANCTRL选网流程，再打断MMC选网状态机。此时如果MMC收到
                搜网失败消息时候，已经退出选网状态机，可能进入其它状态机，如ANYCELL
                搜网状态机，此时UTRAN保存的ABORT消息可丢弃不用处理。
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvMmcAbortFsmReqMsg_PlmnSelection_WaitTdPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvMmcAbortFsmReqMsg_PlmnSelection_WaitTdPlmnSearchCnf WITH MMC ABORT");

    /* 记录状态机打断标记 */
    NAS_UTRANCTRL_SetAbortFlg_PlmnSelection(VOS_TRUE);

    /* 停止保护定时器 */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_TD_PLMN_SEARCH_CNF);

    /* 设置记录打断标志 */
    NAS_UTRANCTRL_SetRcvMmcAbortFsmReqMsgFlg_PlmnSelection(VOS_TRUE);

    /* 向TDRRC发送停止搜网请求 */
    NAS_UTRANCTRL_SndGuAsPlmnStopReq(TPS_PID_RRC);

    /* 迁移状态到等到TDRRC停止搜网回复 */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_PLMN_STOP_CNF);

    /* 启动保护定时器 */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_PLMN_STOP_CNF, TI_NAS_UTRANCTRL_WAIT_TD_PLMN_STOP_CNF_LEN);

    /* 消息处理完成不需继续处理 */
    return VOS_TRUE;
}




/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvTiWaitTdPlmnSearchCnfExpired_PlmnSelection_WaitTdPlmnSearchCnf
 功能描述  : 等待TD搜网回复过程中超时消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年8月4日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitTdPlmnSearchCnfExpired_PlmnSelection_WaitTdPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitTdPlmnSearchCnfExpired_PlmnSelection_WaitTdPlmnSearchCnf: ENTERED");

    /* 停止TDRRC搜网 */
    NAS_UTRANCTRL_SndGuAsPlmnStopReq(TPS_PID_RRC);

    /* 迁移状态到等到TDRRC停止搜网回复 */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_PLMN_STOP_CNF);

    /* 启动保护定时器 */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_PLMN_STOP_CNF, TI_NAS_UTRANCTRL_WAIT_TD_PLMN_STOP_CNF_LEN);

    /* 消息处理完成不需继续处理 */
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvRrmmPlmnStopCnf_PlmnSelection_WaitWasPlmnStopCnf
 功能描述  : 等待WAS停止搜网回复过程中收到停止搜网回复消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年8月4日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2014年11月3日
   作    者   : z00161729
   修改内容   : 开机漫游搜网项目修改
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvRrmmPlmnStopCnf_PlmnSelection_WaitWasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstBufferEntryMsg = VOS_NULL_PTR;

    MSG_HEADER_STRU                    *pstMsgHeader      = VOS_NULL_PTR;
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstEntryMsg       = VOS_NULL_PTR;

    pstEntryMsg = NAS_UTRANCTRL_GetCurrEntryMsgAddr();

    /* 取得当前缓存消息的头 */
    pstMsgHeader = (MSG_HEADER_STRU *)pstEntryMsg->aucEntryMsgBuffer;

    /* 获得当前缓存的缓冲区地址 */
    pstBufferEntryMsg = NAS_UTRANCTRL_GetBufferUtranSndMmcMsgAddr();

    /* 停止保护定时器 */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_STOP_CNF);

    if (VOS_TRUE == NAS_UTRANCTRL_GetRcvMmcAbortFsmReqMsgFlg_PlmnSelection())
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvRrmmPlmnStopCnf_PlmnSelection_WaitWasPlmnStopCnf WITH MMC ABORT");

        /* 此时迁移到挂起状态给MMC回复打断结果 */
        NAS_UTRANCTRL_SndGuAsSuspendReq(WUEPS_PID_WRR);

        /* 迁移状态到等到was挂起回复 */
        NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF_BACK_TD);

        /* 启动保护定时器 */
        NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF_LEN);

        return VOS_TRUE;
    }

    if ((VOS_FALSE == NAS_UTRANCTRL_GetSearchedSpecTdMccFlg())
     && (WUEPS_PID_MMC                  == pstMsgHeader->ulSenderPid)
     && (MMCMMC_INTER_SKIP_SEARCH_TDS_IND == pstMsgHeader->ulMsgName))
    {
        /* 构造指定搜网回复失败消息到内存的缓存区域 */
        NAS_UTRANCTRL_BuildRrMmPlmnSearchCnfFailMsg(WUEPS_PID_WRR,
                                                    WUEPS_PID_MMC,
                                                    NAS_UTRANCTRL_GetBufferedPlmnSearchReqType(),
                                                    (RRMM_PLMN_SEARCH_CNF_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

        /* 保存构造指定搜网回复失败消息事件类型 */
        pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );

        /* 设置需要替换入口消息标记 */
        NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

        /* 状态机切换到MAIN */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* 消息处理完成继续进入MMC状态机处理 */
        return VOS_FALSE;
    }

    if ((WUEPS_PID_MMC == pstMsgHeader->ulSenderPid)
     && (MMCMMC_INTER_SKIP_SEARCH_W_IND == pstMsgHeader->ulMsgName))
    {
        /* 此时需要回到TD下,向WAS发送挂起请求 */
        NAS_UTRANCTRL_SndGuAsSuspendReq(WUEPS_PID_WRR);

        /* 迁移状态到等到was挂起回复 */
        NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF);

        /* 启动保护定时器 */
        NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF_LEN);

        /* 消息处理完成不需继续处理 */
        return VOS_TRUE;
    }


    /* 此时需要回到TD下,向WAS发送挂起请求 */
    NAS_UTRANCTRL_SndGuAsSuspendReq(WUEPS_PID_WRR);

    /* 迁移状态到等到was挂起回复 */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF_BACK_TD);

    /* 启动保护定时器 */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF_LEN);

    /* 消息处理完成不需继续处理 */
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvRrmmPlmnSearchCnf_PlmnSelection_WaitWasPlmnStopCnf
 功能描述  : 等待WAS停止搜网回复过程中收到搜网回复消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年6月25日
   作    者   : b00269685
   修改内容   : DSDS III新生成函数
 2.日    期   : 2014年12月8日
   作    者   : b00269685
   修改内容   : 开机漫游搜网项目修改
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvRrmmPlmnSearchCnf_PlmnSelection_WaitWasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU          *pstSrchCnfMsg;
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstBufferEntryMsg = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader      = VOS_NULL_PTR;
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstEntryMsg       = VOS_NULL_PTR;

    pstSrchCnfMsg = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;

    pstEntryMsg = NAS_UTRANCTRL_GetCurrEntryMsgAddr();

    /* 取得当前缓存消息的头 */
    pstMsgHeader = (MSG_HEADER_STRU *)pstEntryMsg->aucEntryMsgBuffer;

    /* 获得当前缓存的缓冲区地址 */
    pstBufferEntryMsg = NAS_UTRANCTRL_GetBufferUtranSndMmcMsgAddr();

    if (VOS_TRUE == NAS_UTRANCTRL_GetRcvMmcAbortFsmReqMsgFlg_PlmnSelection())
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvRrmmPlmnSearchCnf_PlmnSelection_WaitWasPlmnStopCnf WITH MMC ABORT");

        /* 此时迁移到挂起状态给MMC回复打断结果 */
        NAS_UTRANCTRL_SndGuAsSuspendReq(WUEPS_PID_WRR);

        /* 迁移状态到等到was挂起回复 */
        NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF_BACK_TD);

        /* 启动保护定时器 */
        NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF_LEN);

        return VOS_TRUE;
    }

    /* 停止保护定时器 */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_STOP_CNF);

    /* 如果搜网失败，原因为NO RF，则直接进MMC处理，维持当前为FDD模式 */
    if ((RRC_PLMN_SEARCH_RLT_SPEC_NO_RF     == pstSrchCnfMsg->ulSearchRlt)
     || (RRC_PLMN_SEARCH_RLT_HISTORY_NO_RF  == pstSrchCnfMsg->ulSearchRlt))
    {
        NAS_UTRANCTRL_SetCurrUtranMode(NAS_UTRANCTRL_UTRAN_MODE_FDD);

        /* 状态机切换到MAIN */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* 进MMC状态机处理 */
        return VOS_FALSE;
    }

    if ((VOS_FALSE == NAS_UTRANCTRL_GetSearchedSpecTdMccFlg())
     && (WUEPS_PID_MMC                  == pstMsgHeader->ulSenderPid)
     && (MMCMMC_INTER_SKIP_SEARCH_TDS_IND == pstMsgHeader->ulMsgName))
    {
        /* 构造指定搜网回复失败消息到内存的缓存区域 */
        NAS_UTRANCTRL_BuildRrMmPlmnSearchCnfFailMsg(WUEPS_PID_WRR,
                                                    WUEPS_PID_MMC,
                                                    NAS_UTRANCTRL_GetBufferedPlmnSearchReqType(),
                                                    (RRMM_PLMN_SEARCH_CNF_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

        /* 保存构造指定搜网回复失败消息事件类型 */
        pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );

        /* 设置需要替换入口消息标记 */
        NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

        /* 状态机切换到MAIN */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* 消息处理完成继续进入MMC状态机处理 */
        return VOS_FALSE;
    }

    /* 此时需要回到TD下,向WAS发送挂起请求 */
    NAS_UTRANCTRL_SndGuAsSuspendReq(WUEPS_PID_WRR);

    /* 迁移状态到等到was挂起回复 */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF_BACK_TD);

    /* 启动保护定时器 */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF_LEN);

    /* 消息处理完成不需继续处理 */
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvRrmmPlmnSearchCnf_PlmnSelection_WaitWasPlmnStopCnf
 功能描述  : 等待WAS停止搜网回复过程中收到plmn search info ind的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年5月23日
   作    者   : b00269685
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvRrmmSearchedPlmnInfoInd_PlmnSelection_WaitWasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvTdPlmnSearchCnf_PlmnSelection_WaitWasPlmnStopCnf
 功能描述  : 等W模时候收到TD接入层搜网回复消息的处理
 输入参数  : ulEventType: 消息类型,
              pstMsg: RRMM_PLMN_SEARCH_CNF消息的结构体首址
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月7日
    作    者   : w00167002
    修改内容   : V7R1C50_GUTL_PhaseII:新生成函数
*****************************************************************************/
VOS_UINT32  NAS_UTRANCTRL_RcvTdPlmnSearchCnf_PlmnSelection_WaitWasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTdPlmnSearchCnf_PlmnSelection_WaitWasPlmnStopCnf: illegal MESSAGE! ");

    /* 丢弃该非法消息 */
    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasPlmnStopCnf
 功能描述  : 等待WAS停止搜网回复过程中收到用户请求消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年8月4日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 记录状态机打断标记 */
    NAS_UTRANCTRL_SetAbortFlg_PlmnSelection(VOS_TRUE);

    /* 缓存当前用户请求消息 */
    NAS_UTRANCTRL_SaveCacheMsgInMsgQueue(ulEventType, pstMsg);

    /* 消息处理完成不需继续处理 */
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvMmcAbortFsmReqMsg_PlmnSelection_WaitWasPlmnStopCnf
 功能描述  : 等待WAS停止搜网回复状态收到打断MMC选网状态机消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年12月16日
   作    者   : w00167002
   修改内容   : 新生成函数:在W下搜网失败，进UTRANCTRL选择TD网络时候，收到第一阶段定
                时器超时等消息，触发打断选网状态机。当前MMC给W发STOP REQ请求，而不是
                给TD发STOP搜网请求，这样MMC后续又搜索Lte,出现双主模异常复位. 在消息打断选网状态机时候，
                需要先退出UTRANCTRL选网流程，再打断MMC选网状态机。
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvMmcAbortFsmReqMsg_PlmnSelection_WaitWasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 设置状态机打断标记 */
    NAS_UTRANCTRL_SetAbortFlg_PlmnSelection(VOS_TRUE);

    /* 缓存当前打断选网状态机消息 */
    NAS_UTRANCTRL_SetRcvMmcAbortFsmReqMsgFlg_PlmnSelection(VOS_TRUE);

    /* 消息处理完成不需继续处理 */
    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvTiWaitWasPlmnStopCnfExpired_PlmnSelection_WaitWasPlmnStopCnf
 功能描述  : 等待WAS停止搜网回复过程中收到停止搜网回复超时消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年8月4日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2014年11月3日
   作    者   : z00161729
   修改内容   : 开机漫游搜网项目修改
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitWasPlmnStopCnfExpired_PlmnSelection_WaitWasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstBufferEntryMsg = VOS_NULL_PTR;

    MSG_HEADER_STRU                    *pstMsgHeader      = VOS_NULL_PTR;
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstEntryMsg       = VOS_NULL_PTR;

    pstEntryMsg = NAS_UTRANCTRL_GetCurrEntryMsgAddr();

    /* 取得当前缓存消息的头 */
    pstMsgHeader = (MSG_HEADER_STRU *)pstEntryMsg->aucEntryMsgBuffer;

    /* 获得当前缓存的缓冲区地址 */
    pstBufferEntryMsg = NAS_UTRANCTRL_GetBufferUtranSndMmcMsgAddr();

    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitWasPlmnStopCnfExpired_PlmnSelection_WaitWasPlmnStopCnf: ENTERED");

    if (VOS_TRUE == NAS_UTRANCTRL_GetRcvMmcAbortFsmReqMsgFlg_PlmnSelection())
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitWasPlmnStopCnfExpired_PlmnSelection_WaitWasPlmnStopCnf WITH MMC ABORT");

        /* 此时迁移到挂起状态给MMC回复打断结果 */
        NAS_UTRANCTRL_SndGuAsSuspendReq(WUEPS_PID_WRR);

        /* 迁移状态到等到was挂起回复 */
        NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF_BACK_TD);

        /* 启动保护定时器 */
        NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF_LEN);

        return VOS_TRUE;
    }

    if ((VOS_FALSE == NAS_UTRANCTRL_GetSearchedSpecTdMccFlg())
     && (WUEPS_PID_MMC                  == pstMsgHeader->ulSenderPid)
     && (MMCMMC_INTER_SKIP_SEARCH_TDS_IND == pstMsgHeader->ulMsgName))
    {
        /* 构造指定搜网回复失败消息到内存的缓存区域 */
        NAS_UTRANCTRL_BuildRrMmPlmnSearchCnfFailMsg(WUEPS_PID_WRR,
                                                    WUEPS_PID_MMC,
                                                    NAS_UTRANCTRL_GetBufferedPlmnSearchReqType(),
                                                    (RRMM_PLMN_SEARCH_CNF_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

        /* 保存构造指定搜网回复失败消息事件类型 */
        pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );

        /* 设置需要替换入口消息标记 */
        NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

        /* 状态机切换到MAIN */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* 消息处理完成继续进入MMC状态机处理 */
        return VOS_FALSE;
    }

    /* 此时需要回到TD下,向WAS发送挂起请求 */
    NAS_UTRANCTRL_SndGuAsSuspendReq(WUEPS_PID_WRR);

    /* 迁移状态到等到was挂起回复 */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF_BACK_TD);

    /* 启动保护定时器 */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF_LEN);

    /* 消息处理完成不需继续处理 */
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvRrmmPlmnStopCnf_PlmnSelection_WaitTdPlmnStopCnf
 功能描述  : 等待WAS停止搜网回复过程中收到停止搜网回复消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年8月4日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2014年2月11日
    作    者   : w00167002
    修改内容   : 跳过搜网W结果.
                 注:SVLTE共天线，在W下搜网NO RF后，在G下搜网成功国内驻留成功后，
                 后续再发起搜网时候不能搜WAS,否则G会丢网。但在UTRANCTRL状态机时候
                 ，NO RF时候当前是FDD模式的，因而MMC再发起搜网时候，会先给WAS发送，
                 UTRAN构造SKIP W消息，在UTRANCTRL状态机搜索TDD.
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvRrmmPlmnStopCnf_PlmnSelection_WaitTdPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
     NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstBufferEntryMsg = VOS_NULL_PTR;

    MSG_HEADER_STRU                    *pstMsgHeader      = VOS_NULL_PTR;
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstEntryMsg       = VOS_NULL_PTR;

    /* 取当前缓存的系统消息 */
    pstEntryMsg = NAS_UTRANCTRL_GetCurrEntryMsgAddr();

    /* 取得当前缓存消息的头 */
    pstMsgHeader = (MSG_HEADER_STRU *)pstEntryMsg->aucEntryMsgBuffer;


    /* 获得当前缓存的缓冲区地址 */
    pstBufferEntryMsg = NAS_UTRANCTRL_GetBufferUtranSndMmcMsgAddr();

    /* 停止保护定时器 */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_TD_PLMN_STOP_CNF);


    /* 收到了MMC打断状态机消息，则回到SUSPEND状态退出UTRANCTRL选网流程 */
    if (VOS_TRUE == NAS_UTRANCTRL_GetRcvMmcAbortFsmReqMsgFlg_PlmnSelection())
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvRrmmPlmnStopCnf_PlmnSelection_WaitTdPlmnStopCnf WITH MMC ABORT");

        /* 此时需要回到W下,向TDRRC发送挂起请求 */
        NAS_UTRANCTRL_SndGuAsSuspendReq(TPS_PID_RRC);

        /* 迁移状态到等到TDRRC挂起回复 */
        NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_SUSPEND_CNF_BACK_W);

        /* 启动保护定时器 */
        NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF_LEN);

        /* 消息处理完成不需继续处理 */
        return VOS_TRUE;
    }

    /* 中国网络标记存在则退出当前状态机 */
    if ( (VOS_TRUE == NAS_UTRANCTRL_GetSearchedSpecTdMccFlg())
      || ( (WUEPS_PID_MMC                  == pstMsgHeader->ulSenderPid)
        && (MMCMMC_INTER_SKIP_SEARCH_W_IND == pstMsgHeader->ulMsgName) ) )
    {

        /* 构造指定搜网回复失败消息到内存的缓存区域 */
        NAS_UTRANCTRL_BuildRrMmPlmnSearchCnfFailMsg(WUEPS_PID_WRR,
                                                    WUEPS_PID_MMC,
                                                    NAS_UTRANCTRL_GetBufferedPlmnSearchReqType(),
                                                    (RRMM_PLMN_SEARCH_CNF_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

        /* 保存构造指定搜网回复失败消息事件类型 */
        pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );

        /* 设置需要替换入口消息标记 */
        NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

        /* 状态机切换到MAIN */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* 消息处理完成继续进入MMC状态机处理 */
        return VOS_FALSE;
    }

    /* 此时需要回到W下,向TDRRC发送挂起请求 */
    NAS_UTRANCTRL_SndGuAsSuspendReq(TPS_PID_RRC);

    /* 迁移状态到等到TDRRC挂起回复 */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_SUSPEND_CNF_BACK_W);

    /* 启动保护定时器 */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF_LEN);

    /* 消息处理完成不需继续处理 */
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvRrmmPlmnSearchCnf_PlmnSelection_WaitTdPlmnStopCnf
 功能描述  : 等待WAS停止搜网回复过程中收到搜网回复消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年6月25日
   作    者   : b00269685
   修改内容   : DSDS III新生成函数

*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvRrmmPlmnSearchCnf_PlmnSelection_WaitTdPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU          *pstSrchCnfMsg;
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstBufferEntryMsg = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader      = VOS_NULL_PTR;
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstEntryMsg       = VOS_NULL_PTR;

    pstSrchCnfMsg = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;


    /* 取当前缓存的系统消息 */
    pstEntryMsg = NAS_UTRANCTRL_GetCurrEntryMsgAddr();

    /* 取得当前缓存消息的头 */
    pstMsgHeader = (MSG_HEADER_STRU *)pstEntryMsg->aucEntryMsgBuffer;

    /* 获得当前缓存的缓冲区地址 */
    pstBufferEntryMsg = NAS_UTRANCTRL_GetBufferUtranSndMmcMsgAddr();

    /* 停止保护定时器 */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_TD_PLMN_STOP_CNF);

    if (VOS_TRUE == NAS_UTRANCTRL_GetRcvMmcAbortFsmReqMsgFlg_PlmnSelection())
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvRrmmPlmnSearchCnf_PlmnSelection_WaitTdPlmnStopCnf WITH MMC ABORT");

        /* 此时需要回到W下,向TDRRC发送挂起请求 */
        NAS_UTRANCTRL_SndGuAsSuspendReq(TPS_PID_RRC);

        /* 迁移状态到等到TDRRC挂起回复 */
        NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_SUSPEND_CNF_BACK_W);

        /* 启动保护定时器 */
        NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF_LEN);

        return VOS_TRUE;
    }

    /* 如果搜网失败，原因为NO RF，则直接进MMC处理，维持当前为TDD模式 */
    if ((RRC_PLMN_SEARCH_RLT_SPEC_NO_RF     == pstSrchCnfMsg->ulSearchRlt)
     || (RRC_PLMN_SEARCH_RLT_HISTORY_NO_RF  == pstSrchCnfMsg->ulSearchRlt))
    {
        NAS_UTRANCTRL_SetCurrUtranMode(NAS_UTRANCTRL_UTRAN_MODE_TDD);

        /* 状态机切换到MAIN */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* 进MMC状态机处理 */
        return VOS_FALSE;
    }

    /* 中国网络标记存在则退出当前状态机 */
    if ( (VOS_TRUE == NAS_UTRANCTRL_GetSearchedSpecTdMccFlg())
      || ( (WUEPS_PID_MMC                  == pstMsgHeader->ulSenderPid)
        && (MMCMMC_INTER_SKIP_SEARCH_W_IND == pstMsgHeader->ulMsgName) ) )
    {
        /* 构造指定搜网回复失败消息到内存的缓存区域 */
        NAS_UTRANCTRL_BuildRrMmPlmnSearchCnfFailMsg(WUEPS_PID_WRR,
                                                    WUEPS_PID_MMC,
                                                    NAS_UTRANCTRL_GetBufferedPlmnSearchReqType(),
                                                    (RRMM_PLMN_SEARCH_CNF_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

        /* 保存构造指定搜网回复失败消息事件类型 */
        pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );

        /* 设置需要替换入口消息标记 */
        NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

        /* 状态机切换到MAIN */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* 消息处理完成继续进入MMC状态机处理 */
        return VOS_FALSE;
    }

    /* 此时需要回到W下,向TDRRC发送挂起请求 */
    NAS_UTRANCTRL_SndGuAsSuspendReq(TPS_PID_RRC);

    /* 迁移状态到等到TDRRC挂起回复 */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_SUSPEND_CNF_BACK_W);

    /* 启动保护定时器 */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF_LEN);

    /* 消息处理完成不需继续处理 */
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvWasPlmnStopCnf_PlmnSelection_WaitTdPlmnStopCnf
 功能描述  : 等TD模时候收到WAS接入层搜网回复消息的处理
 输入参数  : ulEventType: 消息类型,
              pstMsg: RRMM_PLMN_SEARCH_CNF消息的结构体首址
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月7日
    作    者   : w00167002
    修改内容   : V7R1C50_GUTL_PhaseII:新生成函数
*****************************************************************************/
VOS_UINT32  NAS_UTRANCTRL_RcvWasPlmnStopCnf_PlmnSelection_WaitTdPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvWasPlmnStopCnf_PlmnSelection_WaitTdPlmnStopCnf: illegal MESSAGE! ");

    /* 丢弃该非法消息 */
    return VOS_TRUE;
}
/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdPlmnStopCnf
 功能描述  : 等待TD停止搜网回复过程中收到用户请求消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年8月4日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 记录状态机打断标记 */
    NAS_UTRANCTRL_SetAbortFlg_PlmnSelection(VOS_TRUE);

    /* 缓存当前用户请求消息 */
    NAS_UTRANCTRL_SaveCacheMsgInMsgQueue(ulEventType, pstMsg);

    /* 消息处理完成不需继续处理 */
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvMmcAbortFsmReqMsg_PlmnSelection_WaitTdPlmnStopCnf
 功能描述  : 等待TD停止搜网回复状态收到打断MMC选网状态机消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年12月16日
   作    者   : w00167002
   修改内容   : 新生成函数:在W下搜网失败，进UTRANCTRL选择TD网络时候，收到第一阶段定
                时器超时等消息，触发打断选网状态机。当前MMC给W发STOP REQ请求，而不是
                给TD发STOP搜网请求，这样MMC后续又搜索Lte,出现双主模异常复位. 在消息打断选网状态机时候，
                需要先退出UTRANCTRL选网流程，再打断MMC选网状态机。
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvMmcAbortFsmReqMsg_PlmnSelection_WaitTdPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 设置状态机打断标记 */
    NAS_UTRANCTRL_SetAbortFlg_PlmnSelection(VOS_TRUE);

    /* 设置收到MMC打断选网状态机消息标记 */
    NAS_UTRANCTRL_SetRcvMmcAbortFsmReqMsgFlg_PlmnSelection(VOS_TRUE);

    /* 消息处理完成不需继续处理 */
    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvTiWaitTdPlmnStopCnfExpired_PlmnSelection_WaitTdPlmnStopCnf
 功能描述  : 等待WAS停止搜网回复过程中收到停止搜网回复超时消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年8月4日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2014年2月11日
   作    者   : w00167002
   修改内容   : 跳过搜网W结果.
                注:SVLTE共天线，在W下搜网NO RF后，在G下搜网成功国内驻留成功后，
                后续再发起搜网时候不能搜WAS,否则G会丢网。但在UTRANCTRL状态机时候
                ，NO RF时候当前是FDD模式的，因而MMC再发起搜网时候，会先给WAS发送，
                UTRAN构造SKIP W消息，在UTRANCTRL状态机搜索TDD.
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitTdPlmnStopCnfExpired_PlmnSelection_WaitTdPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstBufferEntryMsg = VOS_NULL_PTR;

    MSG_HEADER_STRU                    *pstMsgHeader      = VOS_NULL_PTR;
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstEntryMsg       = VOS_NULL_PTR;

    /* 取当前缓存的系统消息 */
    pstEntryMsg = NAS_UTRANCTRL_GetCurrEntryMsgAddr();

    /* 取得当前缓存消息的头 */
    pstMsgHeader = (MSG_HEADER_STRU *)pstEntryMsg->aucEntryMsgBuffer;


    /* 获得当前缓存的缓冲区地址 */
    pstBufferEntryMsg = NAS_UTRANCTRL_GetBufferUtranSndMmcMsgAddr();

    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitTdPlmnStopCnfExpired_PlmnSelection_WaitTdPlmnStopCnf: ENTERED");


    /* 收到了MMC打断状态机消息，则回到SUSPEND状态退出UTRANCTRL选网流程 */
    if (VOS_TRUE == NAS_UTRANCTRL_GetRcvMmcAbortFsmReqMsgFlg_PlmnSelection())
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitTdPlmnStopCnfExpired_PlmnSelection_WaitTdPlmnStopCnf WITH MMC ABORT");

        /* 此时需要回到W下,向TDRRC发送挂起请求 */
        NAS_UTRANCTRL_SndGuAsSuspendReq(TPS_PID_RRC);

        /* 迁移状态到等到TDRRC挂起回复 */
        NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_SUSPEND_CNF_BACK_W);

        /* 启动保护定时器 */
        NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF_LEN);

        /* 消息处理完成不需继续处理 */
        return VOS_TRUE;
    }

    /* 中国网络标记存在则退出当前状态机 */
    if ( (VOS_TRUE == NAS_UTRANCTRL_GetSearchedSpecTdMccFlg())
      || ( (WUEPS_PID_MMC                  == pstMsgHeader->ulSenderPid)
        && (MMCMMC_INTER_SKIP_SEARCH_W_IND == pstMsgHeader->ulMsgName) ) )
    {

        /* 构造指定搜网回复失败消息到内存的缓存区域 */
        NAS_UTRANCTRL_BuildRrMmPlmnSearchCnfFailMsg(WUEPS_PID_WRR,
                                                    WUEPS_PID_MMC,
                                                    NAS_UTRANCTRL_GetBufferedPlmnSearchReqType(),
                                                   (RRMM_PLMN_SEARCH_CNF_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

        /* 保存构造指定搜网回复失败消息事件类型 */
        pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );

        /* 设置需要替换入口消息标记 */
        NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

        /* 状态机切换到MAIN */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* 消息处理完成继续进入MMC状态机处理 */
        return VOS_FALSE;
    }

    /* 此时需要回到W下,向TDRRC发送挂起请求 */
    NAS_UTRANCTRL_SndGuAsSuspendReq(TPS_PID_RRC);

    /* 迁移状态到等到TDRRC挂起回复 */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_SUSPEND_CNF_BACK_W);

    /* 启动保护定时器 */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF_LEN);

    /* 消息处理完成不需继续处理 */
    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvRrmmSuspendCnf_PlmnSelection_WaitWasSuspendCnfBackTD
 功能描述  : 等待回TD挂起W过程中收到WAS挂起回复的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年8月4日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2015年12月17日
   作    者   : w00167002
   修改内容   : 在W下搜网失败，进UTRANCTRL选择TD网络时候，收到第一阶段定
                时器超时等消息，触发打断选网状态机。当前MMC选网状态机给W发STOP REQ请求，而不是
                给TD发STOP搜网请求，这样MMC后续又搜索Lte,出现双主模异常复位. 在消息打断选网状态机时候，
                需要先退出UTRANCTRL选网流程，再打断MMC选网状态机。此时MMC收到选网状态机被MMC发送的
                abort消息打断，则可退出选网状态机。
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvRrmmSuspendCnf_PlmnSelection_WaitWasSuspendCnfBackTD(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstEntryMsg       = VOS_NULL_PTR;
    RRMM_SUSPEND_CNF_ST                *pstRrmmSuspendCnf = VOS_NULL_PTR;

    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstBufferEntryMsg = VOS_NULL_PTR;
#if (FEATURE_ON == FEATURE_TDS_WCDMA_DYNAMIC_LOAD)
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enUtranMode;
    VOS_RATMODE_ENUM_UINT32             enRatMode;
#endif

    /* 获得当前缓存的缓冲区地址 */
    pstBufferEntryMsg = NAS_UTRANCTRL_GetBufferUtranSndMmcMsgAddr();
    pstRrmmSuspendCnf = (RRMM_SUSPEND_CNF_ST*)pstMsg;

    if (MMC_AS_SUSPEND_FAILURE == pstRrmmSuspendCnf->ucResult)
    {
        /* 单板复位 */
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_WAS_SUSPEND_FAILURE);
        return VOS_TRUE;
    }

    /* 停止保护定时器 */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF);

    /* 取当前缓存的系统消息 */
    pstEntryMsg = NAS_UTRANCTRL_GetCurrEntryMsgAddr();


    /* 收到了MMC打断状态机消息，则退出UTRANCTRL选网流程，通知MMC退出选网流程 */
    if (VOS_TRUE == NAS_UTRANCTRL_GetRcvMmcAbortFsmReqMsgFlg_PlmnSelection())
    {
        NAS_UTRANCTRL_BuildInterUtranCtrlPlmnSelectionAbortFinishIndMsg((NAS_MMCMMC_INTER_UTRAN_CTRL_PLMN_SELECTION_ABORT_FINISH_IND_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

        /* 保存构造指定搜网回复失败消息事件类型 */
        pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );
    }

    /* 如果当前的入口消息为定时器超时，则需要构造搜网回复失败消息 */
    else if (VOS_TRUE == NAS_UTRANCTRL_IsNeedBuildSearchCnfMsg_WaitSuspendCnf())
    {
        /* 构造指定搜网回复失败消息到内存的缓存区域 */
        NAS_UTRANCTRL_BuildRrMmPlmnSearchCnfFailMsg(WUEPS_PID_WRR,
                                                    WUEPS_PID_MMC,
                                                    NAS_UTRANCTRL_GetBufferedPlmnSearchReqType(),
                                                    (RRMM_PLMN_SEARCH_CNF_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

        /* 保存构造指定搜网回复失败消息事件类型 */
        pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );
    }
    else
    {
        /* 取缓存的状态机搜网回复失败消息给MMC模块 */
        NAS_UTRANCTRL_SaveBufferUtranSndMmcMsg(pstEntryMsg->ulEventType,
                                (struct MsgCB *)pstEntryMsg->aucEntryMsgBuffer);

    }

    /* 设置需要替换入口消息标记 */
    NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

    /* 切换到MAIN状态机 */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

#if (FEATURE_ON == FEATURE_TDS_WCDMA_DYNAMIC_LOAD)
    /* 如果是TDS/W被挂起的话，可能需要执行次加载操作，以防止如下场景发生:
       开机通知接入层FDD，加载FDD，但搜索失败，加载TDD，需搜索TDD，仍是失败，
       此时需要将FDD重新在加载到内存中，以防止GSM或者LTE驻留后，需与FDD进行互操作
       但FDD不在内存中而复位
    */
    if (VOS_TRUE == NAS_DYNLOAD_GetEnableDynloadTWFlg())
    {
        enUtranMode = NAS_UTRANCTRL_GetPreUtranMode();
        enRatMode   = NAS_UTRANCTRL_GetRatModeBasedOnUtranMode(enUtranMode);

        (VOS_VOID)NAS_DYNLOAD_LoadAS(NAS_DYNLOAD_LOAD_RATCOMB_TYPE_T_W, enRatMode);
    }
#endif

    /* 消息处理完成继续进入MMC状态机处理 */
    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvTiWaitWasSuspendCnfExpired_PlmnSelection_WaitWasSuspendCnfBackTD
 功能描述  : 等待回TD挂起W过程中收到WAS挂起回复超时消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年8月4日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitWasSuspendCnfExpired_PlmnSelection_WaitWasSuspendCnfBackTD(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 异常打印 */
    NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitWasSuspendCnfExpired_PlmnSelection_WaitWasSuspendCnfBackTD: ENTERED");

    /* 复位 */
    NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_WAS_SUSPEND_CNF_EXPIRED);

    /* 消息处理完成不需继续处理 */
    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvRrmmSuspendCnf_PlmnSelection_WaitTdSuspendCnfBackW
 功能描述  : 等待回TD挂起W过程中收到WAS挂起回复超时消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年8月4日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvRrmmSuspendCnf_PlmnSelection_WaitTdSuspendCnfBackW(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstEntryMsg       = VOS_NULL_PTR;
    RRMM_SUSPEND_CNF_ST                *pstRrmmSuspendCnf = VOS_NULL_PTR;

    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstBufferEntryMsg = VOS_NULL_PTR;
#if (FEATURE_ON == FEATURE_TDS_WCDMA_DYNAMIC_LOAD)
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enUtranMode;
    VOS_RATMODE_ENUM_UINT32             enRatMode;
#endif

    /* 获得当前缓存的缓冲区地址 */
    pstBufferEntryMsg = NAS_UTRANCTRL_GetBufferUtranSndMmcMsgAddr();
    pstRrmmSuspendCnf = (RRMM_SUSPEND_CNF_ST*)pstMsg;

    if (MMC_AS_SUSPEND_FAILURE == pstRrmmSuspendCnf->ucResult)
    {
        /* 单板复位 */
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_TD_SUSPEND_FAILURE);
        return VOS_TRUE;
    }

    /* 停止保护定时器 */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF);

    /* 取当前缓存的系统消息 */
    pstEntryMsg = NAS_UTRANCTRL_GetCurrEntryMsgAddr();


    if (VOS_TRUE == NAS_UTRANCTRL_GetRcvMmcAbortFsmReqMsgFlg_PlmnSelection())
    {
        NAS_UTRANCTRL_BuildInterUtranCtrlPlmnSelectionAbortFinishIndMsg((NAS_MMCMMC_INTER_UTRAN_CTRL_PLMN_SELECTION_ABORT_FINISH_IND_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

        /* 保存构造指定搜网回复失败消息事件类型 */
        pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );
    }
    /* 如果当前的入口消息为定时器超时，则需要构造搜网回复失败消息 */
    else if (VOS_TRUE == NAS_UTRANCTRL_IsNeedBuildSearchCnfMsg_WaitSuspendCnf())
    {
        /* 构造指定搜网回复失败消息到内存的缓存区域 */
        NAS_UTRANCTRL_BuildRrMmPlmnSearchCnfFailMsg(WUEPS_PID_WRR,
                                                    WUEPS_PID_MMC,
                                                    NAS_UTRANCTRL_GetBufferedPlmnSearchReqType(),
                                                   (RRMM_PLMN_SEARCH_CNF_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

        /* 保存构造指定搜网回复失败消息事件类型 */
        pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );
    }
    else
    {
        /* 取缓存的状态机搜网回复失败消息给MMC模块 */
        NAS_UTRANCTRL_SaveBufferUtranSndMmcMsg(pstEntryMsg->ulEventType,
                                (struct MsgCB *)pstEntryMsg->aucEntryMsgBuffer);

    }

    /* 设置需要替换入口消息标记 */
    NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

    /* 切换到MAIN状态机 */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

#if (FEATURE_ON == FEATURE_TDS_WCDMA_DYNAMIC_LOAD)
    /* 如果是TDS/W被挂起的话，可能需要执行次加载操作，以防止如下场景发生:
       开机通知接入层FDD，加载FDD，但搜索失败，加载TDD，需搜索TDD，仍是失败，
       此时需要将FDD重新在加载到内存中，以防止GSM或者LTE驻留后，需与FDD进行互操作
       但FDD不在内存中而复位
    */
    if (VOS_TRUE == NAS_DYNLOAD_GetEnableDynloadTWFlg())
    {
        enUtranMode = NAS_UTRANCTRL_GetPreUtranMode();
        enRatMode   = NAS_UTRANCTRL_GetRatModeBasedOnUtranMode(enUtranMode);

        (VOS_VOID)NAS_DYNLOAD_LoadAS(NAS_DYNLOAD_LOAD_RATCOMB_TYPE_T_W, enRatMode);
    }
#endif

    /* 消息处理完成继续进入MMC状态机处理 */
    return VOS_FALSE;
}

#if (FEATURE_ON == FEATURE_CSG)
/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvCsgListAbortReq_PlmnSelection
 功能描述  : 收到csg list abort请求的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年11月3日
   作    者   : z00161729
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvCsgListAbortReq_PlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 如果存在csg list搜网缓存，则清除csg list搜网请求 */
    NAS_UTRANCTRL_ClearCacheMsg(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_CSG_LIST_SEARCH_REQ));

    NAS_UTRANCTRL_SaveCacheMsgInMsgQueue(ulEventType, pstMsg);

    /* 消息处理完成不需继续处理 */
    return VOS_TRUE;
}
#endif

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvTiWaitTdSuspendCnfExpired_PlmnSelection_WaitTdSuspendCnfBackW
 功能描述  : 等待回TD挂起W过程中收到WAS挂起回复超时消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年8月4日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitTdSuspendCnfExpired_PlmnSelection_WaitTdSuspendCnfBackW(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 异常打印 */
    NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitTdSuspendCnfExpired_PlmnSelection_WaitTdSuspendCnfBackW: ENTERED");

    /* 复位 */
    NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_TD_SUSPEND_CNF_EXPIRED);

    /* 消息处理完成不需继续处理 */
    return VOS_TRUE;
}

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
