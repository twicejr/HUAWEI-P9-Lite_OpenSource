/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcSndInternalMsg.c
  版 本 号   : 初稿
  作    者   : w00176964
  生成日期   : 2010年5月9日
  最近修改   :
  功能描述   : MMC发给MMC的消息的处理
  函数列表   :
  修改历史   :
  1.日    期   : 2011年05月9日
    作    者   : w00176964
    修改内容   : 创建文件

******************************************************************************/
/*****************************************************************************
  1 头文件包含
*****************************************************************************/

#include "NasMmcSndInternalMsg.h"
#include "NasComm.h"
#include "NasMmlCtx.h"
#include "NasMmlLib.h"
#include "NasMmlMsgProc.h"
#include "NasMmcComFunc.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_SND_INTERNALMSG_C

/*****************************************************************************
  2 全局变量
*****************************************************************************/

/*****************************************************************************
  3 宏定义
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
  4 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : NAS_MMC_SndAbortFsmMsg
 功能描述  : 发送状态机退出消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月11日
   作    者   : zhoujun /40661
   修改内容   : 新生成函数

 2.日    期   : 2011年11月29日
   作    者   : w00167002
   修改内容   : DTS2011112301233:增加打断事件ID，状态机可以知道是什么事件
                打断自己的。
                修改原因:用户下发关机命令后，当前可能在等注册结果或者在等连接
                释放，可能需要比较久的时间才能处理关机命令，通过增加打断事件，
                如归当前在等注册结果或者等链接释放状态，若收到关机命令，则直接
                退出当前状态机，处理用户的关机命令。
*****************************************************************************/
VOS_VOID  NAS_MMC_SndAbortFsmMsg(
    VOS_UINT32                          ulEventType,
    NAS_MMC_ABORT_FSM_TYPE_UINT8        enAbortFsmType
)
{
    NAS_MMC_ABORT_FSM_STRU              *pstMsg         = VOS_NULL_PTR;
    NAS_MML_INTERNAL_MSG_BUF_STRU       *pstInternalMsg = VOS_NULL_PTR;
    VOS_UINT32                           ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(NAS_MMC_ABORT_FSM_STRU);

    pstInternalMsg  = NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    pstMsg                                  = (NAS_MMC_ABORT_FSM_STRU*)pstInternalMsg;
    pstMsg->ulSenderCpuId                   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                     = WUEPS_PID_MMC;
    pstMsg->ulReceiverCpuId                 = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid                   = WUEPS_PID_MMC;
    pstMsg->ulLength                        = ulLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgID                         = MMCMMC_ABORT_FSM_REQ;

    pstMsg->ulEventType                     = ulEventType;

    pstMsg->enAbortFsmType                  = enAbortFsmType;

    NAS_MML_SndInternalMsg((VOS_VOID*)(pstMsg));

}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndInterAnyCellSearchReq
 功能描述  : 构建内部的Anycell搜网请求
 输入参数  : pstAnycellSrchRatList - 接入技术优先级
             enAnycellSearchScene - 搜网场景
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年8月12日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2014年6月30日
    作    者   : z00161729
    修改内容   : DSDS III新增
*****************************************************************************/
VOS_VOID NAS_MMC_SndInterAnyCellSearchReq(
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstAnycellSrchRatList,
    NAS_MMC_ANYCELL_SEARCH_SCENE_ENUM_UINT8                 enAnycellSearchScene
)
{
    /* 构造内部Ancell搜网消息 */
    NAS_MMC_INTER_ANYCELL_SEARCH_REQ_STRU                  *pstInternalMsg = VOS_NULL_PTR;
    VOS_UINT32                                              ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(NAS_MMC_INTER_ANYCELL_SEARCH_REQ_STRU);

    pstInternalMsg  = (NAS_MMC_INTER_ANYCELL_SEARCH_REQ_STRU*)NAS_MML_GetIntMsgSendBuf(ulLen);

    if (VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstInternalMsg + VOS_MSG_HEAD_LENGTH, 0,
          sizeof(NAS_MMC_INTER_ANYCELL_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstInternalMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstInternalMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInternalMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstInternalMsg->stMsgHeader.ulMsgName       = MMCMMC_INTER_ANYCELL_SEARCH_REQ;
    pstInternalMsg->stMsgHeader.ulLength        = sizeof(NAS_MMC_INTER_ANYCELL_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    pstInternalMsg->enAnycellSearchScene        = enAnycellSearchScene;

    if (VOS_NULL_PTR == pstAnycellSrchRatList)
    {
        /*  不指定接入技术时，根据开机和SYSCFG/SYSCFGEX中确定的接入模式和当前模式，
        设定需要进行搜网的接入技术, 优先在当前模式发起搜网 */
        PS_MEM_CPY(&(pstInternalMsg->stAnycellSrchRatList),
                   NAS_MML_GetMsPrioRatList(), sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

        NAS_MML_SortSpecRatPrioHighest(NAS_MML_GetCurrNetRatType(),
                                       &(pstInternalMsg->stAnycellSrchRatList));

    }
    else
    {
        PS_MEM_CPY(&(pstInternalMsg->stAnycellSrchRatList),
                   pstAnycellSrchRatList, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    }

    NAS_MML_SndInternalMsg(pstInternalMsg);

}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndInterPlmnSearchReq
 功能描述  : 构建内部的Plmn搜网请求
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月18日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2011年10月10日
    作    者   : z00161729
    修改内容   : 增加接入技术的个数参数

*****************************************************************************/
VOS_VOID NAS_MMC_SndInterPlmnSearchReq(
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32    enPlmnSearchScene,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU    *pstIntraPlmnSrchInfo,
    VOS_UINT8                                ucRatNum
)
{
    /*根据场景和现在的PlmnId，构造内部搜网消息*/
    NAS_MMC_INTER_PLMN_SEARCH_REQ_STRU  *pstInternalMsg;
    VOS_UINT32                           ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(NAS_MMC_INTER_PLMN_SEARCH_REQ_STRU);

    pstInternalMsg  = (NAS_MMC_INTER_PLMN_SEARCH_REQ_STRU*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    NAS_MMC_BulidInterPlmnSearchReqMsg(enPlmnSearchScene, pstIntraPlmnSrchInfo, ucRatNum, pstInternalMsg);

    NAS_MML_SndInternalMsg(pstInternalMsg);

    NAS_MMC_RecordOosEventForPlmnSearchScene(enPlmnSearchScene);

}


/*****************************************************************************
 函 数 名  : NAS_MMC_SndInterPlmnSearchReq
 功能描述  : 构建内部的Plmn搜网请求
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月20日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SndInterPlmnListReq(VOS_VOID)
{
    NAS_MMC_INTER_PLMN_LIST_REQ_STRU   *pstInternalMsg;
    VOS_UINT32                          ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(NAS_MMC_INTER_PLMN_LIST_REQ_STRU);

    pstInternalMsg  = (NAS_MMC_INTER_PLMN_LIST_REQ_STRU*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }


    PS_MEM_SET((VOS_UINT8*)pstInternalMsg + VOS_MSG_HEAD_LENGTH, 0,
              sizeof(NAS_MMC_INTER_PLMN_LIST_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstInternalMsg->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstInternalMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstInternalMsg->MsgHeader.ulMsgName       = MMCMMC_INTER_PLMN_LIST_REQ;
    pstInternalMsg->MsgHeader.ulLength        = sizeof(NAS_MMC_INTER_PLMN_LIST_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    NAS_MML_SndInternalMsg(pstInternalMsg);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndSwitchOnRlst
 功能描述  : 收到L模开机后的确认后发送消息给MMC指示开机结果
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月22日
    作    者   : luokaihui /l00167671
    修改内容   : 新生成函数
  2.日    期   : 2011年8月04日
    作    者   : w00176964
    修改内容   : V7R1 Phase II 内部消息发送机制修改

  3.日    期   : 2012年8月30日
    作    者   : z40661
    修改内容   : DTS2012081703433，状态机的退出消息需要放在最前面
*****************************************************************************/
VOS_VOID NAS_MMC_SndSwitchOnRlst(VOS_UINT32 ulResult)
{
    NAS_MMC_SWITCHON_RLST_STRU         *pstMsg              = VOS_NULL_PTR;
    NAS_MML_INTERNAL_MSG_BUF_STRU      *pstInternalMsg      = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(NAS_MMC_SWITCHON_RLST_STRU);

    pstInternalMsg  = NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }
    pstMsg                            = (NAS_MMC_SWITCHON_RLST_STRU *)pstInternalMsg;
    pstMsg->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulMsgName       = MMCMMC_SWITCH_ON_RSLT_CNF;
    pstMsg->MsgHeader.ulLength        = sizeof(NAS_MMC_SWITCHON_RLST_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulResult                  = ulResult;


    NAS_MML_InsertInternalMsgHead(pstMsg);

}


/*****************************************************************************
 函 数 名  : NAS_MMC_SndPowerOffRslt
 功能描述  : 发送关机状态机完成结果消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年3月30日
    作    者   : w00167002
    修改内容   : 新生成函数
  2.日    期   : 2011年07月13日
    作    者   : w00176964
    修改内容   : GUNAS V7R1 PhaseII 阶段调整

  3.日    期   : 2012年8月30日
    作    者   : z40661
    修改内容   : DTS2012081703433，状态机的退出消息需要放在最前面
  4.日    期   : 2013年7月4日
    作    者   : z00234330
    修改内容   : 增加开机LOG
  5.日    期   : 2014年1月28日
    作    者   : s00246516
    修改内容   : L-C互操作项目:增加获取和注册请求的处理
*****************************************************************************/
VOS_VOID NAS_MMC_SndPowerOffRslt(
    NAS_MMC_POWEROFF_RSLT_ENUM_UINT32   enRslt
)
{
    NAS_MMCMMC_POWEROFF_RSLT_STRU      *pstMsg;
    NAS_MML_INTERNAL_MSG_BUF_STRU      *pstInternalMsg;
    VOS_UINT32                          ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(NAS_MMCMMC_POWEROFF_RSLT_STRU);

    pstInternalMsg  = NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    pstMsg                              = (NAS_MMCMMC_POWEROFF_RSLT_STRU *)pstInternalMsg;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulMsgName       = MMCMMC_POWER_OFF_RSLT_CNF;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_MMCMMC_POWEROFF_RSLT_STRU) - VOS_MSG_HEAD_LENGTH;

    /* Modified by s00246516 for L-C互操作项目, 2014-01-28, Begin */
    pstMsg->enRslt                      = enRslt;
    /* Modified by s00246516 for L-C互操作项目, 2014-01-28, Begin */


    NAS_MML_InsertInternalMsgHead(pstMsg);


    /* Modified by z00234330 for 开机LOG, 2013-6-24, begin */
    (VOS_VOID)vos_printf("NAS_MMC_SndPowerOffRslt:0x%x",VOS_GetSlice());
    /* Modified by z00234330 for 开机LOG, 2013-6-24, end */

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndPlmnListRslt
 功能描述  : 发送PLMN LIST状态机完成结果消息
 输入参数  : enRslt:状态机退出结果
             ulNeedPlmnSearch:是否需要搜网
             enPlmnListSearchScene:搜网场景
             pstListInfo:搜索到的网络列表信息
             pstRegRsltInfo:注册结果信息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月19日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2012年5月8日
    作    者   : t00212959
    修改内容   : V7R1C50 GUL BG搜网修改,增加搜网场景入参

  3.日    期   : 2012年8月30日
    作    者   : z40661
    修改内容   : DTS2012081703433，状态机的退出消息需要放在最前面
  4.日    期   : 2015年9月26日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_VOID NAS_MMC_SndPlmnListRslt(
    NAS_MMC_PLMN_LIST_RESULT_ENUM_UINT32                    enRslt,
    VOS_UINT8                                               ucNeedPlmnSearch,
    NAS_MMC_PLMN_LIST_SEARCH_SCENE_ENUM_UINT8               enPlmnListSearchScene,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstListInfo,
    NAS_MMC_PLMN_LIST_REG_RSLT_INFO_STRU                   *pstRegRsltInfo
)
{
    NAS_MMCMMC_PLMN_LIST_RSLT_STRU     *pstMsg = VOS_NULL_PTR;
    NAS_MML_INTERNAL_MSG_BUF_STRU      *pstInternalMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;
    VOS_UINT32                          i;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(NAS_MMCMMC_PLMN_LIST_RSLT_STRU);

    pstInternalMsg  = NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    pstMsg                              = (NAS_MMCMMC_PLMN_LIST_RSLT_STRU *)pstInternalMsg;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulMsgName       = MMCMMC_PLMN_LIST_RSLT_CNF;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_MMCMMC_PLMN_LIST_RSLT_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->ucNeedPlmnSearch            = ucNeedPlmnSearch;
    pstMsg->enRslt                      = enRslt;

    pstMsg->enPlmnListSearchScene       = enPlmnListSearchScene;
    /* 注册结果信息为空 */
    if ( VOS_NULL_PTR == pstRegRsltInfo)
    {
        pstMsg->enCsRegAdditionalAction     = NAS_MMC_ADDITIONAL_ACTION_BUTT;
        pstMsg->enPsRegAdditionalAction     = NAS_MMC_ADDITIONAL_ACTION_BUTT;
    }
    else
    {
        pstMsg->enCsRegAdditionalAction         = pstRegRsltInfo->enCsRegAdditionalAction;
        pstMsg->enPsRegAdditionalAction         = pstRegRsltInfo->enPsRegAdditionalAction;
    }

    /* LIST搜网结果 */
    if (VOS_NULL_PTR == pstListInfo)
    {
        /* 设置接入技术为无效 */
        for (i = 0; i < NAS_MML_MAX_RAT_NUM; i++)
        {
            pstMsg->astPlmnSearchInfo[i].enRatType = NAS_MML_NET_RAT_TYPE_BUTT;
        }
    }
    else
    {
        /* 根据消息中携带的搜网信息更新搜网列表 */
        PS_MEM_CPY(pstMsg->astPlmnSearchInfo,
                            pstListInfo, sizeof(pstMsg->astPlmnSearchInfo));
    }


    NAS_MML_InsertInternalMsgHead(pstMsg);


    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndAnycellSearchRlst
 功能描述  : 发送anycell搜网的结果
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月20日
    作    者   : l0013025
    修改内容   : 新生成函数
  2.日    期   : 2012年8月30日
    作    者   : z40661
    修改内容   : DTS2012081703433，状态机的退出消息需要放在最前面
*****************************************************************************/
VOS_VOID NAS_MMC_SndAnycellSearchRslt(
    NAS_MMC_ANYCELL_SEARCH_RESULT_ENUM_UINT32               enResult
)
{
    NAS_MMCMMC_ANYCELL_SEARCH_RSLT_STRU                    *pstInternalMsg = VOS_NULL_PTR;
    VOS_UINT32                                              ulLen;


    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(NAS_MMCMMC_ANYCELL_SEARCH_RSLT_STRU);
    pstInternalMsg  = (NAS_MMCMMC_ANYCELL_SEARCH_RSLT_STRU *)NAS_MML_GetIntMsgSendBuf(ulLen);

    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }
    pstInternalMsg->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstInternalMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstInternalMsg->MsgHeader.ulMsgName       = MMCMMC_ANYCELL_SEARCH_RSLT_CNF;
    pstInternalMsg->MsgHeader.ulLength        = sizeof(NAS_MMCMMC_ANYCELL_SEARCH_RSLT_STRU) - VOS_MSG_HEAD_LENGTH;
    pstInternalMsg->enResult                  = enResult;


    NAS_MML_InsertInternalMsgHead(pstInternalMsg);


    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_SndPlmnSelectionRlst
 功能描述  : 发送PlmnSelection的搜网的结果
 输入参数  :
             NAS_MMC_PLMN_SELECTION_RESULT_ENUM_UINT32               enPlmnSelectionRslt
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月11日
   作    者   : l00130025
   修改内容   : 新生成函数

 2.日    期   : 2012年8月30日
   作    者   : z40661
   修改内容   : DTS2012081703433，状态机的退出消息需要放在最前面

 3.日    期   : 2014年1月21日
   作    者   : w00167002
   修改内容   : SVLTE共天线项目:调整函数参数，扩展可复用性。

*****************************************************************************/

/* Added by c00318887 for 预置频点搜网优化, 2015-9-2, begin */
VOS_VOID  NAS_MMC_SndPlmnSelectionRslt(
    NAS_MMC_PLMN_SELECTION_RESULT_ENUM_UINT32               enPlmnSelectionRslt,
    VOS_UINT32                                              ulCampFlg,
    NAS_MMC_RAT_SEARCH_INFO_STRU                           *pstSearchRatInfo,
    VOS_UINT32                                              ulRatNum,
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   ulPlmnSearchScene
)
/* Added by c00318887 for 预置频点搜网优化, 2015-9-2, end */
{
    NAS_MMCMMC_PLMN_SELECTION_RSLT_STRU                    *pstInternalMsg = VOS_NULL_PTR;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    pstInternalMsg  = (NAS_MMCMMC_PLMN_SELECTION_RSLT_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(NAS_MMCMMC_PLMN_SELECTION_RSLT_STRU));

    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    pstInternalMsg->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstInternalMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstInternalMsg->MsgHeader.ulMsgName       = MMCMMC_PLMN_SELECTION_RSLT_CNF;
    pstInternalMsg->MsgHeader.ulLength        = sizeof(NAS_MMCMMC_PLMN_SELECTION_RSLT_STRU) - VOS_MSG_HEAD_LENGTH;
    pstInternalMsg->enResult                  = enPlmnSelectionRslt;
    pstInternalMsg->ulCampFlg                 = ulCampFlg;
    /* Added by c00318887 for 预置频点搜网优化, 2015-9-2, begin */
    pstInternalMsg->ulPlmnSearchScene         = ulPlmnSearchScene;
    /* Added by c00318887 for 预置频点搜网优化, 2015-9-2, end */

    /* 填充网络覆盖信息 */
    pstInternalMsg->ulRatNum = ulRatNum;

    PS_MEM_CPY(pstInternalMsg->astSearchRatInfo, pstSearchRatInfo,
               (NAS_MML_MAX_RAT_NUM * sizeof(NAS_MMC_RAT_SEARCH_INFO_STRU)));


    NAS_MML_InsertInternalMsgHead(pstInternalMsg);


    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_SndInterSkipSearchWIndMsg
 功能描述  : 发送PlmnSelection的搜网的结果
 输入参数  :
             NAS_MMC_PLMN_SELECTION_RESULT_ENUM_UINT32               enPlmnSelectionRslt
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月11日
    作    者   : w00167002
    修改内容   : 跳过搜网W结果.
                 注:SVLTE共天线，在W下搜网NO RF后，在G下搜网成功国内驻留成功后，
                 后续再发起搜网时候不能搜WAS,否则G会丢网。但在UTRANCTRL状态机时候
                 ，NO RF时候当前是FDD模式的，因而MMC再发起搜网时候，会先给WAS发送，
                 UTRAN构造SKIP W消息，在UTRANCTRL状态机搜索TDD.

*****************************************************************************/
VOS_VOID  NAS_MMC_SndInterSkipSearchWIndMsg(VOS_VOID)
{
    NAS_MMCMMC_INTER_SKIP_SEARCH_W_IND_STRU                *pstInternalMsg      = VOS_NULL_PTR;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    pstInternalMsg  = (NAS_MMCMMC_INTER_SKIP_SEARCH_W_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(NAS_MMCMMC_INTER_SKIP_SEARCH_W_IND_STRU));

    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    pstInternalMsg->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstInternalMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstInternalMsg->MsgHeader.ulMsgName       = MMCMMC_INTER_SKIP_SEARCH_W_IND;
    pstInternalMsg->MsgHeader.ulLength        = sizeof(NAS_MMCMMC_INTER_SKIP_SEARCH_W_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    PS_MEM_SET(pstInternalMsg->aucReserved, 0x00, sizeof(pstInternalMsg->aucReserved));

    NAS_MML_SndInternalMsg(pstInternalMsg);

    return;
}
/*****************************************************************************
 函 数 名  : NAS_MMC_SndInterSkipSearchTdsIndMsg
 功能描述  : 发送MMCMMC_INTER_SKIP_SEARCH_TDS_IND消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月3日
    作    者   : z00161729
    修改内容   : 新增函数

*****************************************************************************/
VOS_VOID  NAS_MMC_SndInterSkipSearchTdsIndMsg(VOS_VOID)
{
    NAS_MMCMMC_INTER_SKIP_SEARCH_TDS_IND_STRU              *pstInternalMsg = VOS_NULL_PTR;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    pstInternalMsg  = (NAS_MMCMMC_INTER_SKIP_SEARCH_TDS_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(NAS_MMCMMC_INTER_SKIP_SEARCH_TDS_IND_STRU));

    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    pstInternalMsg->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstInternalMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstInternalMsg->MsgHeader.ulMsgName       = MMCMMC_INTER_SKIP_SEARCH_TDS_IND;
    pstInternalMsg->MsgHeader.ulLength        = sizeof(NAS_MMCMMC_INTER_SKIP_SEARCH_TDS_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    PS_MEM_SET(pstInternalMsg->aucReserved, 0x00, sizeof(pstInternalMsg->aucReserved));

    NAS_MML_SndInternalMsg(pstInternalMsg);

    return;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_SndInterAbortUtranCtrlPlmnSearchReqMsg
 功能描述  : 发送NAS_MMCMMC_INTER_ABORT_UTRAN_CTRL_PLMN_SEARCH_REQ消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月3日
    作    者   : z00161729
    修改内容   : 新增函数

*****************************************************************************/
VOS_VOID  NAS_MMC_SndInterAbortUtranCtrlPlmnSearchReqMsg(VOS_VOID)
{
    NAS_MMCMMC_INTER_ABORT_UTRAN_CTRL_PLMN_SEARCH_REQ_STRU *pstInternalMsg = VOS_NULL_PTR;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    pstInternalMsg  = (NAS_MMCMMC_INTER_ABORT_UTRAN_CTRL_PLMN_SEARCH_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(NAS_MMCMMC_INTER_ABORT_UTRAN_CTRL_PLMN_SEARCH_REQ_STRU));

    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    pstInternalMsg->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstInternalMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstInternalMsg->MsgHeader.ulMsgName       = MMCMMC_INTER_ABORT_UTRAN_CTRL_PLMN_SEARCH_REQ;
    pstInternalMsg->MsgHeader.ulLength        = sizeof(NAS_MMCMMC_INTER_ABORT_UTRAN_CTRL_PLMN_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    PS_MEM_SET(pstInternalMsg->aucReserved, 0x00, sizeof(pstInternalMsg->aucReserved));

    NAS_MML_SndInternalMsg(pstInternalMsg);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndInterAbortUtranCtrlPlmnSearchCnfMsg
 功能描述  : 发送NAS_MMCMMC_INTER_ABORT_UTRAN_CTRL_PLMN_SEARCH_CNF消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月3日
    作    者   : z00161729
    修改内容   : 新增函数

*****************************************************************************/
VOS_VOID  NAS_MMC_SndInterAbortUtranCtrlPlmnSearchCnfMsg(VOS_VOID)
{
    NAS_MMCMMC_INTER_ABORT_UTRAN_CTRL_PLMN_SEARCH_CNF_STRU *pstInternalMsg = VOS_NULL_PTR;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    pstInternalMsg  = (NAS_MMCMMC_INTER_ABORT_UTRAN_CTRL_PLMN_SEARCH_CNF_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(NAS_MMCMMC_INTER_ABORT_UTRAN_CTRL_PLMN_SEARCH_CNF_STRU));

    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    pstInternalMsg->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstInternalMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstInternalMsg->MsgHeader.ulMsgName       = MMCMMC_INTER_ABORT_UTRAN_CTRL_PLMN_SEARCH_CNF;
    pstInternalMsg->MsgHeader.ulLength        = sizeof(NAS_MMCMMC_INTER_ABORT_UTRAN_CTRL_PLMN_SEARCH_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    PS_MEM_SET(pstInternalMsg->aucReserved, 0x00, sizeof(pstInternalMsg->aucReserved));

    NAS_MML_SndInternalMsg(pstInternalMsg);

    return;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_SndBgPlmnSearchRslt
 功能描述  : 发送BgPlmnSearch的结果
 输入参数  : enPlmnSelectionRslt
             ulNeedPlmnSearch
             ulBgSearchCompleted
             stInterPlmnSearchInfo
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月27日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年4月26日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改,增加搜网场景入参

 3.日    期   : 2012年8月30日
   作    者   : z40661
   修改内容   : DTS2012081703433，状态机的退出消息需要放在最前面

*****************************************************************************/
VOS_VOID  NAS_MMC_SndBgPlmnSearchRslt(
    NAS_MMC_BG_PLMN_SEARCH_RSLT_ENUM_UINT32                 enPlmnSelectionRslt,
    VOS_UINT32                                              ulNeedPlmnSearch,
    NAS_MMC_BG_PLMN_SEARCH_SCENE_ENUM_UINT8                 enBgPlmnSearchScene,
    VOS_UINT32                                              ulBgSearchCompleted,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    NAS_MMCMMC_BG_PLMN_SEARCH_RSLT_STRU                    *pstInternalMsg = VOS_NULL_PTR;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    pstInternalMsg  = (NAS_MMCMMC_BG_PLMN_SEARCH_RSLT_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(NAS_MMCMMC_BG_PLMN_SEARCH_RSLT_STRU));

    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        /* 异常打印 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndBgPlmnSearchRslt:pstInternalMsg IS VOS_NULL_PTR ");

        return;
    }

    pstInternalMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstInternalMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInternalMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstInternalMsg->stMsgHeader.ulMsgName       = MMCMMC_BG_PLMN_SEARCH_RSLT_CNF;
    pstInternalMsg->stMsgHeader.ulLength        = sizeof(NAS_MMCMMC_BG_PLMN_SEARCH_RSLT_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 填充消息内容 */
    pstInternalMsg->enRslt                      = enPlmnSelectionRslt;
    pstInternalMsg->ulNeedPlmnSearch            = ulNeedPlmnSearch;
    pstInternalMsg->ulSearchCompleted           = ulBgSearchCompleted;

    pstInternalMsg->enBgPlmnSearchScene         = enBgPlmnSearchScene;

    /* 填充已搜索到的网络信息 */
    if (VOS_NULL_PTR != pstSearchedPlmnListInfo)
    {
        PS_MEM_CPY(&(pstInternalMsg->stSearchedPlmnListInfo), pstSearchedPlmnListInfo,
                   sizeof(NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU));
    }


    NAS_MML_InsertInternalMsgHead(pstInternalMsg);


    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndSuspendRsltMsg
 功能描述  : 发送重选,HO,CCO状态机退出消息
 输入参数  : enSuspendCause  挂起原因
             enSuspendRslt   挂起结果
             enSuspendFailCause  挂起失败原因
             pstListInfo         接入层上报的列表
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月18日
   作    者   : w00176964
   修改内容   : 新生成函数

 2.日    期   : 2012年8月30日
   作    者   : z40661
   修改内容   : DTS2012081703433，状态机的退出消息需要放在最前面
 3.日    期   : 2012年10月23日
   作    者   : s00217060
   修改内容   : DTS2012102301482，挂起原因为小区重选时，enRatType填的不正确

*****************************************************************************/
VOS_VOID  NAS_MMC_SndSuspendRsltMsg(
    MMC_SUSPEND_CAUSE_ENUM_UINT8                            enSuspendCause,
    NAS_MMC_SUSPEND_RSLT_ENUM_UINT32                        enSuspendRslt,
    NAS_MMC_SUSPEND_FAIL_CAUSE_ENUM_UINT8                   enSuspendFailCause,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstListInfo
)
{
    NAS_MMCMMC_SUSPEND_RSLT_STRU       *pstMsg          = VOS_NULL_PTR;
    NAS_MML_INTERNAL_MSG_BUF_STRU      *pstInternalMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;
    VOS_UINT32                          i;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(NAS_MMCMMC_SUSPEND_RSLT_STRU);

    pstInternalMsg  = NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }
    pstMsg                              = (NAS_MMCMMC_SUSPEND_RSLT_STRU *)pstInternalMsg;

    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_MMCMMC_SUSPEND_RSLT_STRU)
                                       -VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulMsgName       = MMCMMC_SUSPEND_RSLT_CNF;
    pstMsg->enSuspendCause              = enSuspendCause;
    pstMsg->enRslt                      = enSuspendRslt;
    pstMsg->enFailCause                 = enSuspendFailCause;

    /* 设置接入技术为无效 */
    for (i = 0; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        pstMsg->astPlmnSearchInfo[i].enRatType = NAS_MML_NET_RAT_TYPE_BUTT;
    }

    /* F态出服务区搜网时才会上报列表 */
    if ( (MMC_SUSPEND_CAUSE_PLMNSEARCH          == enSuspendCause)
       &&(NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST  == enSuspendFailCause))
    {
        if (VOS_NULL_PTR != pstListInfo)
        {
            /* 根据消息中携带的搜网信息更新搜网列表 */
            PS_MEM_CPY(pstMsg->astPlmnSearchInfo,
                        pstListInfo, sizeof(pstMsg->astPlmnSearchInfo));
        }
    }


    NAS_MML_InsertInternalMsgHead(pstMsg);


}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndSysCfgRslt
 功能描述  : 通知上层状态机SYSCFG运行结果
 输入参数  : VOS_UINT32                          ulSysCfgRslt
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月18日
   作    者   : W00167002
   修改内容   : 新生成函数

 2.日    期   : 2012年8月30日
   作    者   : z40661
   修改内容   : DTS2012081703433，状态机的退出消息需要放在最前面

 3.日    期   : 2015年2月26日
   作    者   : w00167002
   修改内容   : DTS2015021604972:在SYSCFG设置完后，MMA进行ATTACH流程。MMC已经退出
                 SYSCFG状态机，并触发搜网。在搜网时候，如果PS不准许ATTACH，则不搜索LTE.
                 现修改为在SYSCFG后,如果需要搜网，则判别是否ATTACH PS需要先ENABLE LTE。
4.日    期   : 2015年8月6日
  作    者   : c00318887
  修改内容   : DTS2015041401965，syscfg设置只在增加接入技术且新增接入技术优先级高于当前接入技术才触发搜网
*****************************************************************************/
VOS_VOID  NAS_MMC_SndSysCfgRslt(
    VOS_UINT32                          ulSysCfgRslt,
    VOS_UINT32                          ulNeedPlmnSrch,
    VOS_UINT32                          ulIsNeedAttachPs,

    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrePrioRatList
)
{
    NAS_MMCMMC_SysCfg_RSLT_STRU        *pstMsg              = VOS_NULL_PTR;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    pstMsg          = (NAS_MMCMMC_SysCfg_RSLT_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(NAS_MMCMMC_SysCfg_RSLT_STRU));
    if ( VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulMsgName       = MMCMMC_SYSCFG_RSLT_CNF;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_MMCMMC_SysCfg_RSLT_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulRslt                      = ulSysCfgRslt;
    pstMsg->ulNeedPlmnSrch              = ulNeedPlmnSrch;

    pstMsg->ulIsNeedAttachPs            = ulIsNeedAttachPs;

    PS_MEM_CPY((VOS_VOID*)&(pstMsg->stPrePrioRatList), (VOS_VOID*)pstPrePrioRatList, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));


    NAS_MML_InsertInternalMsgHead(pstMsg);


    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_BulidInterPlmnSearchReqMsg
 功能描述  : 构建内部的Plmn搜网请求消息
 输入参数  : enPlmnSearchScene 搜网场景
             pstIntraPlmnSrchInfo 搜网信息
             ucRatNum:接入技术的个数
 输出参数  : pstInterPlmnSrchMsg 内部搜网消息
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年8月06日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2011年10月10日
    作    者   : z00161729
    修改内容   : 增加接入技术的个数参数

*****************************************************************************/
VOS_VOID NAS_MMC_BulidInterPlmnSearchReqMsg(
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstIntraPlmnSrchInfo,
    VOS_UINT8                                               ucRatNum,
    NAS_MMC_INTER_PLMN_SEARCH_REQ_STRU                     *pstMsg
)
{
    VOS_UINT32                          i;

    PS_MEM_SET((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
          sizeof(NAS_MMC_INTER_PLMN_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulMsgName       = MMCMMC_INTER_PLMN_SEARCH_REQ;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_MMC_INTER_PLMN_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->enPlmnSearchScene           = enPlmnSearchScene;


    /* 设置接入技术为无效 */
    for (i = 0; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        pstMsg->astInterPlmnSearchInfo[i].enRatType = NAS_MML_NET_RAT_TYPE_BUTT;
    }

    if (pstIntraPlmnSrchInfo != VOS_NULL_PTR)
    {
        /* 根据消息中携带的搜网信息更新搜网列表 */
        PS_MEM_CPY(pstMsg->astInterPlmnSearchInfo,
                   pstIntraPlmnSrchInfo,
                   sizeof(NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU) * ucRatNum);
    }


}

/*****************************************************************************
 函 数 名  : NAS_MMC_BuildInterDplmnSetReqMsg
 功能描述  : 构造MMCMMC_INTER_DPLMN_SET_REQ消息
 输入参数  : VOS_UINT8                                              *pucVersion
             VOS_UINT8                                               ucEhPlmnNum
             NAS_MSCC_PIF_PLMN_ID_STRU                              *pstEhPlmnInfo
             NAS_MMC_INTER_DPLMN_SET_REQ_STRU                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月9日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_BuildInterDplmnSetReqMsg(
    VOS_UINT8                                              *pucVersion,
    VOS_UINT8                                               ucEhPlmnNum,
    NAS_MSCC_PIF_PLMN_ID_STRU                              *pstEhPlmnInfo,
    NAS_MMC_INTER_DPLMN_SET_REQ_STRU                       *pstMsg
)
{
    /* 清空消息内容 */
    NAS_MMC_CLR_MSG_ENTITY(pstMsg);

    /* 填写消息头 */
    NAS_MMC_CFG_MSG_HDR(pstMsg,
                        WUEPS_PID_MMC,
                        MMCMMC_INTER_DPLMN_SET_REQ,
                        sizeof(NAS_MMC_INTER_DPLMN_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写消息内容 */

    /* EHPLMN个数 */
    pstMsg->ucEhPlmnNum  = ucEhPlmnNum;

    /* EHPLMN列表 */
    PS_MEM_CPY(pstMsg->astEhPlmnInfo,
               pstEhPlmnInfo,
               ucEhPlmnNum * sizeof(NAS_MSCC_PIF_PLMN_ID_STRU));

    /* 版本信息 */
    PS_MEM_CPY(pstMsg->aucVersionId,
               pucVersion,
               NAS_MSCC_PIF_INFO_VERSION_LEN);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndInterNvimOPlmnRefreshInd
 功能描述  : 构建内部的OPlmn刷新请求
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月15日
    作    者   : x65241
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SndInterNvimOPlmnRefreshInd(VOS_VOID)
{
    VOS_UINT32                                   ulLen;
    NAS_MMC_INTER_NVIM_OPLMN_REFRESH_IND_STRU   *pstInternalMsg = VOS_NULL_PTR;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(NAS_MMC_INTER_NVIM_OPLMN_REFRESH_IND_STRU);

    pstInternalMsg  = (NAS_MMC_INTER_NVIM_OPLMN_REFRESH_IND_STRU*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstInternalMsg + VOS_MSG_HEAD_LENGTH, 0,
              sizeof(NAS_MMC_INTER_NVIM_OPLMN_REFRESH_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstInternalMsg->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstInternalMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstInternalMsg->MsgHeader.ulMsgName       = MMCMMC_INTER_NVIM_OPLMN_REFRESH_IND;
    pstInternalMsg->MsgHeader.ulLength        = sizeof(NAS_MMC_INTER_NVIM_OPLMN_REFRESH_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    NAS_MML_SndInternalMsg(pstInternalMsg);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndGetGeoRsltMsg
 功能描述  : 发送GET GEO状态机退出消息
 输入参数  : NAS_MMC_GET_GEO_RSLT_ENUM_UINT32  GetGeo的结果
             NAS_MML_PLMN_ID_STRU*             获取到的PLMN ID
 输出参数  : 无
 返 回 值  :
 调用函数  : 调用者必须保证GetGeo结果为成功时入参不能为NULL指针
 被调函数  :

 修改历史     :
 1.日    期   : 2015年05月08日
   作    者   : sunjitan 00193151
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_MMC_SndGetGeoRsltMsg(
    NAS_MMC_GET_GEO_RSLT_ENUM_UINT32    enGetGeoRslt,
    NAS_MML_PLMN_ID_STRU               *pstGeoPlmn
)
{
    VOS_UINT32                          ulLen;
    NAS_MMCMMC_GET_GEO_RSLT_STRU       *pstMsg         = VOS_NULL_PTR;
    NAS_MML_INTERNAL_MSG_BUF_STRU      *pstInternalMsg = VOS_NULL_PTR;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen                               = sizeof(NAS_MMCMMC_GET_GEO_RSLT_STRU);

    pstInternalMsg                      = NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        NAS_TRACE_HIGH("Alloc msg fail.");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstInternalMsg + VOS_MSG_HEAD_LENGTH, 0,
                                        sizeof(NAS_MMCMMC_GET_GEO_RSLT_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg                              = (NAS_MMCMMC_GET_GEO_RSLT_STRU*)pstInternalMsg;

    /* 清空消息内容 */
    NAS_MMC_CLR_MSG_ENTITY(pstMsg);

    /* 填写消息头 */
    NAS_MMC_CFG_MSG_HDR(pstMsg,
                        WUEPS_PID_MMC,
                        MMCMMC_GET_GEO_RSLT_CNF,
                        sizeof(NAS_MMCMMC_GET_GEO_RSLT_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息内容 */
    pstMsg->enGetGeoRslt                = enGetGeoRslt;

    NAS_TRACE_HIGH("enGetGeoRslt is %u ", enGetGeoRslt);

    /* 扫频成功，填充覆盖信息 */
    if ((NAS_MMC_GET_GEO_SUCCESS == enGetGeoRslt)
     && (VOS_NULL_PTR != pstGeoPlmn))
    {
        pstMsg->stGetGeoPlmn.ulMcc      = pstGeoPlmn->ulMcc;
        pstMsg->stGetGeoPlmn.ulMnc      = pstGeoPlmn->ulMnc;

        NAS_TRACE_HIGH("ulMcc is %x ;ulMnc is %x ", pstMsg->stGetGeoPlmn.ulMcc, pstMsg->stGetGeoPlmn.ulMnc);
    }

    NAS_MML_InsertInternalMsgHead(pstMsg);

    return;
}


/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

