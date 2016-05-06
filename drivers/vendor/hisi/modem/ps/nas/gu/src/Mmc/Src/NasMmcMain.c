/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcMain.c
  版 本 号   : 初稿
  作    者   : zhoujun /40661
  生成日期   : 2010年11月15日
  最近修改   :
  功能描述   : NAS MMC框架处理函数
  函数列表   :
  修改历史   :
  1.日    期   : 2010年11月12日
    作    者   : zhoujun /40661
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/



#include "PsTypeDef.h"
#include "NasFsm.h"
#include "PsCommonDef.h"
#include "NasMmcTimerMgmt.h"
#include "NasComm.h"
#include "NasMmcCtx.h"
#include "NasMmlLib.h"
#include "NasMmcFsmMainTbl.h"
#include "NasMmcMain.h"
#include "NasMmcFsmSyscfg.h"
#include "NasMmcFsmInterSysCellReselTbl.h"
#include "NasMmcFsmAnyCellSearchTbl.h"
#include "NasMmcFsmInterSysHoTbl.h"
#include "NasMmcFsmInterSysCcoTbl.h"
#include "NasMmcFsmInterSysOosTbl.h"
#include "NasMmcFsmPlmnSelectionTbl.h"
#include "NasMmcFsmPLmnListTbl.h"
#include "NasMmcFsmSwitchOnTbl.h"
#include "NasMmcFsmPoweroffTbl.h"
#include "NasMmcFsmSyscfgTbl.h"
#include "NasMmcFsmBgPlmnSearchTbl.h"
#include "NasMmcFsmGetGeoTbl.h"

#include "NasMmcPreProcTbl.h"
#include "NasMmcPreProcAct.h"
#include "NasMmcSndInternalMsg.h"
#include "MM_Share.h"
#include "NasMmcSndOm.h"
/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, begin */
/* 删除ExtAppMmcInterface.h*/
/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, end */
#include "MmcMmInterface.h"
#include "MmcGmmInterface.h"
#include "NasMmcMsgPrioCompare.h"
#include "NasUtranCtrlInterface.h"

#include "NasUsimmApi.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMCMAIN_C


/* PC回放包含其他文件的函数 */
/*extern VOS_UINT32 NAS_MM_SndOutsideContextData(VOS_VOID);
 */
/*extern VOS_UINT32 NAS_GMM_SndOutsideContextData(VOS_VOID);
 */


/*lint -save -e958 */


/*****************************************************************************
 函 数 名  : NAS_MMC_IsExistCachedUserSearchMsg
 功能描述  : 判断是否存在缓存的用户搜网请求，包括指定搜网和列表搜网
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:存在缓存的用户搜网请求
             VOS_FALSE:不存在缓存的用户搜网请求
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月25日
    作    者   : zhoujun 40661
    修改内容   : 新生成函数
  2.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  3.日    期   : 2015年9月6日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_IsExistCachedUserSearchMsg( VOS_VOID )
{
    VOS_UINT32                          ulCacheMsgIdx;
    VOS_UINT32                          ulExistFlg;

    ulExistFlg = NAS_MMC_IsExistCacheMsg(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_LIST_REQ),
                                         &ulCacheMsgIdx);
    if ( VOS_TRUE == ulExistFlg )
    {
        return VOS_TRUE;
    }

    /* 收到内部搜网或列表搜网请求,判断是否有指定搜网或列表搜网,不保存该消息*/
    ulExistFlg = NAS_MMC_IsExistCacheMsg(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_SPECIAL_REQ),
                                         &ulCacheMsgIdx);
    if ( VOS_TRUE == ulExistFlg )
    {
        return VOS_TRUE;
    }

#if (FEATURE_ON == FEATURE_CSG)
    ulExistFlg = NAS_MMC_IsExistCacheMsg(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_CSG_LIST_SEARCH_REQ),
                                         &ulCacheMsgIdx);
    if ( VOS_TRUE == ulExistFlg )
    {
        return VOS_TRUE;
    }
#endif
    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedCacheMsg
 功能描述  : 比较缓存消息与当前消息的优先级
 输入参数  : ulEventType:消息类型
             pstMsg     :消息首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息不需要被缓存
             VOS_TRUE:消息需要被缓存
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月25日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数
 2.日    期   : 2015年9月6日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_IsNeedCacheMsg(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT32                          ulExistFlg;
    VOS_UINT32                          ulCacheEventType;

    switch (ulEventType)
    {
        /* 收到关机请求,清除所有缓存消息,返回消息需要保存*/
        case NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_OFF_REQ):
            NAS_MMC_ClearAllCacheMsg();
            break;

        /* 收到MSCC发生的指定搜网和列表搜网*/
        case NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_SPECIAL_REQ):
        case NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_LIST_REQ):
        case NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST):
#if (FEATURE_ON == FEATURE_CSG)
        case NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_CSG_LIST_SEARCH_REQ):
		case NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH):
#endif

            /* 清除缓存内部指定搜网 */
            ulCacheEventType = NAS_BuildEventType(WUEPS_PID_MMC, MMCMMC_INTER_PLMN_SEARCH_REQ);
            NAS_MMC_ClearCacheMsg(ulCacheEventType);

            break;

        case NAS_BuildEventType(WUEPS_PID_MMC, MMCMMC_INTER_PLMN_SEARCH_REQ):

            /* 收到内部搜网请求,判断是否有指定搜网,不保存该消息*/
            ulExistFlg = NAS_MMC_IsExistCachedUserSearchMsg();
            if ( VOS_TRUE == ulExistFlg)
            {
                return VOS_FALSE;
            }

            /* 收到内部搜网请求,判断是否有内部搜网,清除以前保存的搜网*/

            /* 清除缓存内部指定搜网 */
            ulCacheEventType = NAS_BuildEventType(WUEPS_PID_MMC, MMCMMC_INTER_PLMN_SEARCH_REQ);
            NAS_MMC_ClearCacheMsg(ulCacheEventType);

            break;

        default:
            break;
    }

    /* 默认返回保存该消息 */
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcMsgPrio
 功能描述  : 将当前收到的消息和L2状态机的入口消息进行比较,并根据比较结果进行后续的动作
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE: 当前消息处理完成，不需要后续处理
             VOS_FALSE:当前消息处理完成，需要后续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月02日
   作    者   : zhoujun /40661
   修改内容   : 新生成函数

 2.日    期   : 2011年7月14日
   作    者   : w00167002
   修改内容   : V7R1 PHASEII: NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD 不进行WARNING 打印

 3.日    期   : 2011年9月29日
   作    者   : z40661
   修改内容   : 框架调整

 4.日    期   : 2011年11月29日
   作    者   : w00167002
   修改内容   : DTS2011112301233:增加打断事件ID，状态机可以知道是什么事件
                打断自己的。
                修改原因:用户下发关机命令后，当前可能在等注册结果或者在等连接
                释放，可能需要比较久的时间才能处理关机命令，通过增加打断事件，
                如归当前在等注册结果或者等链接释放状态，若收到关机命令，则直接
                退出当前状态机，处理用户的关机命令。
  5.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
*****************************************************************************/
VOS_UINT32  NAS_MMC_ProcMsgPrio(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ABORT_FSM_TYPE_UINT8                enAbortType;
    NAS_MMC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT32   enMsgPrio;


    enAbortType = NAS_MMC_ABORT_BUTT;

    enMsgPrio = NAS_MMC_GetMsgComparePrioRslt(ulEventType, pstMsg, &enAbortType);

    switch ( enMsgPrio )
    {
        /* 发送Abort消息,则当前已经打断状态机 */
        case NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT :

            NAS_MMC_SndAbortFsmMsg(ulEventType, enAbortType);

            NAS_MMC_SaveCacheMsg(ulEventType,
                                (VOS_VOID *) pstMsg);

            return VOS_TRUE;

        /* 缓存消息 */
        case NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE :
            NAS_MMC_SaveCacheMsg(ulEventType,
                              (VOS_VOID *) pstMsg);

            return VOS_TRUE;

        /* 进状态机中Load 新的状态机 */
        case NAS_MMC_MSG_COMPARE_PRIO_RSLT_INITFSM :
            return VOS_FALSE;

        /* 消息可直接丢弃 */
        case NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD :
            return VOS_FALSE;

        default:
            NAS_WARNING_LOG1(WUEPS_PID_MMC, "NAS_MMC_ProcMsgPrio:invlid msg priority",ulEventType);
            return VOS_FALSE;
    }

}



/*****************************************************************************
 函 数 名  : NAS_MMC_PostProcessMsg
 功能描述  : MMC状态机后处理函数,将当前收到的消息和L2状态机的入口消息进行比较,
              判断后续的动作
 输入参数  : ulEventType:消息类型
             pstMsg       :消息内容
 输出参数  : 无
 返 回 值  : 返回消息是否已经处理完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年3月30日
   作    者   : zhoujun /40661
   修改内容   : 新生成函数

 2.日    期   : 2011年7月11日
   作    者   : zhoujun 40661
   修改内容   : 重新对后处理进行整理

*****************************************************************************/
VOS_UINT32  NAS_MMC_PostProcessMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* 判断是否需要打断当前状态机 */
    if (VOS_TRUE == NAS_MMC_ProcMsgPrio(ulEventType, pstMsg))
    {
        NAS_NORMAL_LOG1(WUEPS_PID_MMC, "NAS_MMC_PostProcessMsg:ulEventType", ulEventType);

        return VOS_TRUE;
    }


    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_MsgPreProcess
 功能描述  : MMC消息预处理
 输入参数  : ulEventType:消息类型
              pMsg       :消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE:预处理完成
              VOS_FALSE:还需要进行状态机中处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年11月13日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_PreProcessMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_ACTION_FUNC                     pActFun;
    NAS_FSM_DESC_STRU                  *pstFsmDesc;
    VOS_UINT32                          ulRet;

    /* 消息预处理 */

    NAS_INFO_LOG1(WUEPS_PID_MMC,"NAS_MMC_PreProcessMsg", ulEventType);

    pstFsmDesc = NAS_MMC_GetPreFsmDescAddr();

    /* 查找状态转移表中的相应的动作处理函数 */
    pActFun = NAS_FSM_FindAct(pstFsmDesc, NAS_MMC_L1_STA_PREPROC, ulEventType);

    if (VOS_NULL_PTR != pActFun )
    {
        /* 预处理消息,分为两类消息,一类为预处理结束就返回,另外一类为预处理
        结束后,仍然需要进行到状态机中继续处理,因此此处直接通过函数返回预处
        理结束后是否需要进行状态机处理*/
        ulRet = (*pActFun) ( ulEventType, (struct MsgCB*)pstMsg);
        return ulRet;
    }

    /* 消息未被处理完成需继续处理 */
    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名    : NAS_MMC_FSM_ProcessEvent
 功能描述    : 状态机的事件处理函数
 输入参数    :
               ulCurState :当前状态
               ulEventType:处理事件
               ulMsgID    :消息ID
               pRcvMsg    :消息指针
 输出参数    :
 返回值      : VOS_UINT32:处理是否完成
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年11月13日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数

  2.日    期   : 2011年4月19日
    作    者   : zhoujun /40661
    修改内容   : 根据最新状态机定义修改
 *****************************************************************************/
VOS_UINT32 NAS_MMC_FSM_ProcessEvent(
    VOS_UINT32                          ulCurState,
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pRcvMsg
)
{
    NAS_ACTION_FUNC                     pActFun;
    NAS_FSM_DESC_STRU                  *pstFsmDesc;
    VOS_UINT32                          ulRet;

    NAS_INFO_LOG2(WUEPS_PID_MMC,"NAS_MMC_FSM_ProcessEvent", ulCurState, ulEventType);

    pstFsmDesc = NAS_MMC_GetCurFsmDesc();

    /* 查找状态转移表中的相应的动作处理函数 */
    pActFun = NAS_FSM_FindAct(pstFsmDesc, ulCurState, ulEventType);

    if (VOS_NULL_PTR != pActFun )
    {
        /* 如果返回的事件处理函数不为空,调用它进行事件处理 */
        ulRet   = (*pActFun) ( ulEventType,(struct MsgCB*)pRcvMsg);
        NAS_INFO_LOG1(WUEPS_PID_MMC,"NAS_MMC_FSM_ProcessEvent", ulRet);
        return VOS_TRUE;
    }

    /* 消息未被处理完成需继续处理 */
    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ProcessMsgInFsm
 功能描述  : 消息状态机处理
 输入参数  : ulEventType :  消息类型+PID
              pMsg        :  消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE:该消息是否处理完成
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年11月15日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_ProcessMsgInFsm(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRet;
    NAS_MMC_FSM_CTX_STRU               *pstCurFsm;
    VOS_UINT16                          usOldStackDepth;
    VOS_UINT16                          usNewStackDepth;

    /* 获取当前MMC的顶层状态 */
    pstCurFsm           = NAS_MMC_GetCurFsmAddr();

    /* 获取当前MMC的栈深度 */
    usOldStackDepth    = NAS_MMC_GetFsmStackDepth();

    /* 消息处理 */
    ulRet     = NAS_MMC_FSM_ProcessEvent( pstCurFsm->ulState,
                                          ulEventType,
                                          (VOS_VOID*)pstMsg );

    /* 获取当前MMC的新栈深度 */
    usNewStackDepth    = NAS_MMC_GetFsmStackDepth();

    /* 栈深度没有增加,表明没有触发新的状态机，可以退出*/
    if ( usNewStackDepth <= usOldStackDepth )
    {
        return ulRet;
    }

    /* 新的栈深度大于老的栈深度 表明进行了压栈,需要将消息放入状态机中继续处理 */
    /* 重新获取当前MMC的顶层状态 */
    pstCurFsm   = NAS_MMC_GetCurFsmAddr();

    /* 将消息放入顶层状态机，继续处理 */
    ulRet       = NAS_MMC_FSM_ProcessEvent( pstCurFsm->ulState,
                                          ulEventType,
                                          (VOS_VOID*)pstMsg );


    return ulRet;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_InitTask
 功能描述  : MMC任务初始化函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月20日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

 2.日    期   : 2012年7月13日
   作    者   : w00167002
   修改内容   : V7R1C50_GUTL_PhaseI:初始化MMAGENT上下文
 3.日    期   : 2012年7月14日
   作    者   : w00176964
   修改内容   : V7R1C50_GUTL_PhaseI:状态机注册
 3.日    期   : 2015年11月28日
   作    者   : z00359541
   修改内容   : DTS2015112803743, 复位时增加可维可测信息输出
*****************************************************************************/
VOS_VOID NAS_MMC_InitTask( VOS_VOID )
{
    NAS_MMC_CONTEXT_STRU                *pstMmcCtx;
    NAS_MML_CTX_STRU                    *pstMmlCtx;

    /* 初始化MML模块CTX */
    pstMmlCtx   = NAS_MML_GetMmlCtx();
    NAS_MML_InitCtx(NAS_MML_INIT_CTX_STARTUP, pstMmlCtx);

    /* 支持TD时，对UTRAN CTRL模块进行初始化 */
    NAS_UTRANCTRL_InitCtx(NAS_MML_INIT_CTX_STARTUP);

    /* 初始化MMC模块CTX */
    pstMmcCtx   = NAS_MMC_GetMmcCtxAddr();
    NAS_MMC_InitCtx(NAS_MMC_INIT_CTX_STARTUP, pstMmcCtx);

    /*注册状态机*/
    NAS_MMC_RegFsm();

    NAS_MML_RegisterDumpCallBack();

    return;
}
/*****************************************************************************
 函 数 名  : NAS_MMC_InitPid
 功能描述  : MMC的PID初始化函数
 输入参数  : enum VOS_INIT_PHASE_DEFINE ip
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月13日
    作    者   : w00167002
    修改内容   : 新生成函数
  2.日    期   : 2013年6月13日
    作    者   : z00161729
    修改内容   : SVLTE 和usim接口调整修改
*****************************************************************************/
VOS_UINT32 NAS_MMC_InitPid(
    enum VOS_INIT_PHASE_DEFINE          ip
)
{
    switch( ip )
    {
        case VOS_IP_LOAD_CONFIG:

            /* 调用MMC模块初始化函数 */
            NAS_MMC_InitTask();
            break;

        case VOS_IP_INITIAL:
            NAS_PIHAPI_RegCardRefreshIndMsg(WUEPS_PID_MMC);
            break;

        case VOS_IP_FARMALLOC:
        case VOS_IP_ENROLLMENT:
        case VOS_IP_LOAD_DATA:
        case VOS_IP_FETCH_DATA:
        case VOS_IP_STARTUP:
        case VOS_IP_RIVAL:
        case VOS_IP_KICKOFF:
        case VOS_IP_STANDBY:
        case VOS_IP_BROADCAST_STATE:
        case VOS_IP_RESTART:
        case VOS_IP_BUTT:
            break;

        default:
            break;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_InitCtx
 功能描述  : MMC CTX模块初始化
 输入参数  : enInitType:初始化类型,上电或软关机
 输出参数  : pstMmcCtx:MMC上下文信息
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年4月19日
   作    者   : zhoujun /40661
   修改内容   : 新生成函数
 2.日    期   : 2011年9月29日
   作    者   : z00161729
   修改内容   : 新生成函数
 3.日    期   : 2015年4月16日
   作    者   : y00245242
   修改内容   : iteration 13开发

*****************************************************************************/
VOS_VOID  NAS_MMC_InitCtx(
    NAS_MMC_INIT_CTX_TYPE_ENUM_UINT8     enInitType,
    NAS_MMC_CONTEXT_STRU                *pstMmcCtx
)
{

    /* 初始化MMC当前状态机上下文 */
    NAS_MMC_InitCurrFsmCtx(&(pstMmcCtx->stCurFsm));

    /* 初始化MMC状态机栈上下文 */
    NAS_MMC_InitFsmStackCtx(&(pstMmcCtx->stFsmStack));

    /* 初始化plmn搜网控制上下文 */
    NAS_MMC_InitPlmnSearchCtrlCtx(enInitType, &(pstMmcCtx->stPlmnSearchCtrl));

    /* 初始化plmn注册被拒结果上下文 */
    NAS_MMC_InitPlmnRegRejCtx(&(pstMmcCtx->stPlmnRegInfo));

    /* 初始化服务信息上下文 */
    NAS_MMC_InitServiceInfo(&(pstMmcCtx->stServiceInfo));

    /* 初始化可维可测信息上下文 */
    NAS_MMC_InitMaintainCtx(&(pstMmcCtx->stMaintainInfo));

    /* 初始化化所有定时器消息 */
    NAS_MMC_InitAllTimers(pstMmcCtx->astMmcTimerCtx);

    /* 初始化内部缓存队列 */
    NAS_MMC_InitInternalBuffer(&(pstMmcCtx->stBufferEntryMsgQueue));


    /* 初始化高优先级搜网控制上下文 */
    NAS_MMC_InitHighPrioPlmnSearchCtx(&(pstMmcCtx->stHighPrioPlmnSearchCtrl));


    NAS_MMC_InitNetScanReqCtx(&(pstMmcCtx->stNetScanReqCtx));

    NAS_MMC_InitPrefPlmnCtx(&(pstMmcCtx->stPreflmnInfo));

    NAS_MMC_InitDetachReqCtx(&(pstMmcCtx->stDetachReqCtx));

    NAS_MMC_InitAttachReqCtx(&(pstMmcCtx->stAttachReqCtx));

    NAS_MMC_InitNoRFBackUpSearchedInfoCtx(&(pstMmcCtx->stBackUpSearchInfo));
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RegFsm
 功能描述  : 注册状态机
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月20日
    作    者   : zhoujun 40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MMC_RegFsm( VOS_VOID )
{
    /* 注册预处理状态机 */
    NAS_MMC_RegPreFsm();

    /* 注册L1状态机 */
    NAS_MMC_RegMainL1Fsm();

    /* 注册L2状态机 */
    NAS_MMC_RegL2Fsm();
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcessBufferMsg
 功能描述  : 处理缓存
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年4月20日
   作    者   : zhoujun /40661
   修改内容   : 新生成函数

 2.日    期   : 2011年8月20日
   作    者   : w00167002
   修改内容   : NAS_MMC_ENTRY_MSG_STRU消息超过1024字节，显示分配

 3.日    期   : 2011年9月29日
   作    者   : zhoujun 40661
   修改内容   : 修改缓存的处理
 4.日    期   : 2011年11月10日
   作    者   : w00166186
   修改内容   : DTS2011110804587 手动模式开机，等注册结果过程改为自动模式，注册成功后再次发起了搜网
*****************************************************************************/
VOS_UINT32 NAS_MMC_ProcessBufferMsg( VOS_VOID )
{
    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          usOldStackDepth;
    VOS_UINT32                          usNewStackDepth;
    VOS_UINT32                          ulOldCacheNum;
    VOS_UINT32                          ulNewCacheNum;

    /* 内存空间分配 */
    pstEntryMsg = (NAS_MMC_ENTRY_MSG_STRU *)PS_MEM_ALLOC( WUEPS_PID_MMC,
                                             sizeof(NAS_MMC_ENTRY_MSG_STRU) );

    if ( VOS_NULL_PTR == pstEntryMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcessBufferMsg:ERROR: MEM ALLOC FAIL");
        return VOS_FALSE;
    }


    ulRet   = VOS_TRUE;

    while( VOS_TRUE == NAS_MMC_GetNextCachedMsg(pstEntryMsg) )
    {
        ulOldCacheNum    = NAS_MMC_GetCacheNum();

        if ( VOS_TRUE == NAS_MMC_PreProcessMsg(pstEntryMsg->ulEventType, (struct MsgCB*)pstEntryMsg->aucEntryMsgBuffer) )
        {
            /* 如果缓存的深度增加则表明不能继续继续处理缓存 */
            ulNewCacheNum = NAS_MMC_GetCacheNum();

            if ( ulNewCacheNum > ulOldCacheNum )
            {
                ulRet   = VOS_FALSE;
                break;
            }
            continue;
        }

        /* 获取当前MMC的栈深度 */
        usOldStackDepth     = NAS_MMC_GetFsmStackDepth();

        /* 进入状态机处理 */
        ulRet  = NAS_MMC_ProcessMsgInFsm(pstEntryMsg->ulEventType, (struct MsgCB*)pstEntryMsg->aucEntryMsgBuffer);

        /* 获取当前MMC的栈深度 */
        usNewStackDepth     = NAS_MMC_GetFsmStackDepth();

        /* 如果栈的深度增加,说明肯定进行了压栈操作,不能继续处理消息 */
        if ( usNewStackDepth > usOldStackDepth )
        {
            ulRet   = VOS_FALSE;
            break;
        }

        /* 该消息进入了后处理,后处理中是打断或缓存的,则表明不能继续处理缓存 */
        if (VOS_FALSE == ulRet)
        {
            if ( VOS_TRUE == NAS_MMC_PostProcessMsg(pstEntryMsg->ulEventType,
                            (struct MsgCB*)pstEntryMsg->aucEntryMsgBuffer))
            {
                ulRet   = VOS_FALSE;
                break;
            }
        }
    }


    PS_MEM_FREE(WUEPS_PID_MMC, pstEntryMsg);

    return ulRet;
}




/*****************************************************************************
 函 数 名  : NAS_MMC_MsgProc
 功能描述  : MMC的消息处理函数
 输入参数  : pstMsg       :MMC收到的消息
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2010年11月15日
   作    者   : zhoujun /40661
   修改内容   : 新生成函数

 2.日    期   : 2011年4月23日
   作    者   : zhoujun /40661
   修改内容   : V7R1 Phase I 修改

 3.日    期   : 2011年7月9日
   作    者   : zhoujun 40661
   修改内容   : V7R1 PhaseII阶段调整,对缓存进行优化

 4.日    期   : 2011年8月15日
   作    者   : W00167002
   修改内容   : 将PC回放消息由最后面调至前面

 5.日    期   : 2011年10月6日
   作    者   : zhoujun 40661
   修改内容   : PhaseII阶段缓存处理调整

 6.日    期   : 2011年10月22日
   作    者   : W00167002
   修改内容   : 将PC回放消息删除，将其增加到NAS_MML_FidMsgProc函数

 7.日    期   : 2015年6月6日
   作    者   : l00198894
   修改内容   : Modem PID 扩展
*****************************************************************************/
VOS_VOID  NAS_MMC_MsgProc(
    struct MsgCB                       *pstMsg
)
{
    MSG_HEADER_STRU                    *pstMsgHeader;
    REL_TIMER_MSG                      *pRcvTimerMsg;
    VOS_UINT32                          ulEventType;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          usOldStackDepth;
    VOS_UINT32                          usNewStackDepth;

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_MsgProc:null pointer");
        return;
    }

    pstMsgHeader = (MSG_HEADER_STRU *)pstMsg;

    /* 动作表里的时间消息不能靠消息头名称进行区分，依靠其结构体的ulName域进行区分
       所以此处进行分别处理
    */
    if ( VOS_PID_TIMER == pstMsgHeader->ulSenderPid )
    {
        pRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;

        ulEventType  = NAS_BuildEventType(pstMsgHeader->ulSenderPid, pRcvTimerMsg->ulName);

        /* 停止对应的定时器，更新定时器的状态 */
        NAS_MMC_StopTimer((NAS_MMC_TIMER_ID_ENUM_UINT16)(pRcvTimerMsg->ulName));
    }
    else
    {
        ulEventType  = NAS_BuildEventType(pstMsgHeader->ulSenderPid, (VOS_UINT16)pstMsgHeader->ulMsgName);
    }

    /* 如果已经处理完成则直接返回 */
    if ( VOS_TRUE == NAS_MMC_PreProcessMsg(ulEventType, pstMsg))
    {
        return;
    }


    /* 获取当前MMC的栈深度 */
    usOldStackDepth    = NAS_MMC_GetFsmStackDepth();

    /* 进入状态机处理 */
    ulRet  = NAS_MMC_ProcessMsgInFsm(ulEventType, pstMsg);

    /* 状态机中会收到连接释放、状态机退出等消息,所以不能直接返回
    还需要判断能否处理缓存*/
    usNewStackDepth    = NAS_MMC_GetFsmStackDepth();

    /* 如果栈的深度减少,说明肯定进行了退栈操作,需要优先处理该状态机的结果消息,直接返回 */
    if ( usNewStackDepth < usOldStackDepth )
    {
        /* 记录退栈操作,只要发生了退栈后续就可以处理缓存 */
        NAS_MMC_SetFsmStackPopFlg(VOS_TRUE);
        return;
    }

    /* 该消息在状态机中已经处理完成,可尝试处理一下缓存 */
    if ( VOS_TRUE == ulRet)
    {
        /* 当前仅收到状态机的退出消息才能够处理缓存 */
        if (VOS_TRUE == NAS_MMC_GetFsmStackPopFlg())
        {
            (VOS_VOID)NAS_MMC_ProcessBufferMsg();
            NAS_MMC_SetFsmStackPopFlg(VOS_FALSE);
        }
    }
    /* 在当前状态机中未处理完毕，判断消息是否需要打断当前的L2状态机,后处理 */
    else
    {
        (VOS_VOID)NAS_MMC_PostProcessMsg(ulEventType, pstMsg);
    }



    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_MainL1FsmReg
 功能描述  : MMC L1状态机处理状态机注册
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年04月19日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_RegMainL1Fsm( VOS_VOID  )
{
    /* 状态机注册 */
    NAS_FSM_RegisterFsm((NAS_MMC_GetMainFsmDescAddr()),
                         "NAS:FSM:MMC:MAIN",
                         (VOS_UINT32)(NAS_MMC_GetL1MainStaTblSize()),
                         NAS_MMC_GetL1MainStaTbl(),
                         VOS_NULL_PTR,
                         NAS_MMC_InitFsmCtx_L1Main);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_L2FsmReg
 功能描述  : MMC L2状态机处理状态机注册
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年04月19日
   作    者   : W00167002
   修改内容   : 新生成函数

 2.日    期   : 2011年07月17日
   作    者   : W00167002
   修改内容   : 增加SYSCFG子状态机的注册

 3.日    期   : 2011年07月19日
   作    者   : w00176964
   修改内容   : 增加cellreselect ho cco子状态机的注册

 4.日    期   : 2011年07月19日
   作    者   : sunxibo 46746
   修改内容   : 增加Plmn selection子状态机的注册

 5.日    期   : 2011年09月24日
   作    者   : w00167002
   修改内容   : 增加HIGH_PRIO_PLMN_SEARCH搜子状态机的注册

*****************************************************************************/
VOS_VOID NAS_MMC_RegL2Fsm( VOS_VOID  )
{

    /* SwitchOn状态机注册 */
    NAS_FSM_RegisterFsm((NAS_MMC_GetSwitchOnFsmDescAddr()),
                         "NAS:FSM:MMC:SwitchOn",
                         (VOS_UINT32)NAS_MMC_GetSwitchOnStaTblSize(),
                         NAS_MMC_GetSwitchOnStaTbl(),
                         VOS_NULL_PTR,
                         NAS_MMC_InitFsmCtx_SwitchOn);

    /* PowerOff状态机注册 */
    NAS_FSM_RegisterFsm((NAS_MMC_GetPowerOffFsmDescAddr()),
                         "NAS:FSM:MMC:PowerOff",
                         (VOS_UINT32)NAS_MMC_GetPowerOffStaTblSize(),
                         NAS_MMC_GetPowerOffStaTbl(),
                         VOS_NULL_PTR,
                         NAS_MMC_InitFsmCtx_PowerOff);

    /* PlmnSelection状态机注册 */
    NAS_FSM_RegisterFsm((NAS_MMC_GetPlmnSelectionFsmDescAddr()),
                         "NAS:FSM:MMC:PlmnSelection",
                         (VOS_UINT32)NAS_MMC_GetPlmnSelectionStaTblSize(),
                         NAS_MMC_GetPlmnSelectionStaTbl(),
                         VOS_NULL_PTR,
                         NAS_MMC_InitFsmCtx_PlmnSelection);

    /* AnyCell搜网状态机注册 */
    NAS_FSM_RegisterFsm((NAS_MMC_GetAnyCellSearchFsmDescAddr()),
                         "NAS:FSM:MMC:AnyCellSearch",
                         (VOS_UINT32)NAS_MMC_GetAnyCellSearchStaTblSize(),
                         NAS_MMC_GetAnyCellSearchStaTbl(),
                         VOS_NULL_PTR,
                         NAS_MMC_InitFsmCtx_AnyCellSearch);

    /* SysCfg状态机注册 */
    NAS_FSM_RegisterFsm((NAS_MMC_GetSysCfgFsmDescAddr()),
                         "NAS:FSM:MMC:SysCfg",
                         (VOS_UINT32)NAS_MMC_GetSysCfgStaTblSize(),
                         NAS_MMC_GetSysCfgStaTbl(),
                         VOS_NULL_PTR,
                         NAS_MMC_InitFsmCtx_SysCfg);

    /* 重选状态机注册 */
    NAS_FSM_RegisterFsm((NAS_MMC_GetInterSysCellReselFsmDescAddr()),
                         "NAS:FSM:MMC:InterSysCellResel",
                         (VOS_UINT32)NAS_MMC_GetInterSysCellReselStaTblSize(),
                         NAS_MMC_GetInterSysCellReselStaTbl(),
                         VOS_NULL_PTR,
                         NAS_MMC_InitFsmCtx_InterSysCellResel);

    /* Handover 状态机注册 */
    NAS_FSM_RegisterFsm((NAS_MMC_GetInterSysHoFsmDescAddr()),
                         "NAS:FSM:MMC:InterSysHo",
                         (VOS_UINT32)NAS_MMC_GetInterSysHoStaTblSize(),
                         NAS_MMC_GetInterSysHoStaTbl(),
                         VOS_NULL_PTR,
                         NAS_MMC_InitFsmCtx_InterSysHo);

    /* CCO状态机注册 */
    NAS_FSM_RegisterFsm((NAS_MMC_GetInterSysCcoFsmDescAddr()),
                         "NAS:FSM:MMC:InterSysCCO",
                         (VOS_UINT32)NAS_MMC_GetInterSysCcoStaTblSize(),
                         NAS_MMC_GetInterSysCcoStaTbl(),
                         VOS_NULL_PTR,
                         NAS_MMC_InitFsmCtx_InterSysCco);

    /* OOS状态机注册 */
    NAS_FSM_RegisterFsm((NAS_MMC_GetInterSysOosFsmDescAddr()),
                         "NAS:FSM:MMC:InterSysOos",
                         (VOS_UINT32)NAS_MMC_GetInterSysOosStaTblSize(),
                         NAS_MMC_GetInterSysOosStaTbl(),
                         VOS_NULL_PTR,
                         NAS_MMC_InitFsmCtx_InterSysOos);

    /* PLMN LIST状态机注册 */
    NAS_FSM_RegisterFsm((NAS_MMC_GetPlmnListFsmDescAddr()),
                         "NAS:FSM:MMC:PlmnList",
                         (VOS_UINT32)NAS_MMC_GetPlmnListStaTblSize(),
                         NAS_MMC_GetPlmnListStaTbl(),
                         VOS_NULL_PTR,
                         NAS_MMC_InitFsmCtx_PlmnList);

    /* BgPlmnSearch状态机注册 */
    NAS_FSM_RegisterFsm((NAS_MMC_GetBgPlmnSearchFsmDescAddr()),
                         "NAS:FSM:MMC:BgPlmnSearch",
                         (VOS_UINT32)NAS_MMC_GetBgPlmnSearchStaTblSize(),
                         NAS_MMC_GetBgPlmnSearchStaTbl(),
                         VOS_NULL_PTR,
                         NAS_MMC_InitFsmCtx_BgPlmnSearch);

    /* GetGeo状态机注册 */
    NAS_FSM_RegisterFsm((NAS_MMC_GetGeoFsmDescAddr()),
                         "NAS:FSM:MMC:GetGeo",
                         (VOS_UINT32)NAS_MMC_GetGeoStaTblSize(),
                         NAS_MMC_GetGetGeoStaTbl(),
                         VOS_NULL_PTR,
                         NAS_MMC_InitFsmCtx_GetGeo);
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RegPreFsm
 功能描述  : MMC预处理状态机注册
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年04月19日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_RegPreFsm( VOS_VOID  )
{
    /* 预处理注册 */
    NAS_FSM_RegisterFsm((NAS_MMC_GetPreFsmDescAddr()),
                         "NAS:FSM:MMC:PreProcess",
                         NAS_MMC_GetPreProcessStaTblSize(),
                         NAS_MMC_GetPreProcessStaTbl(),
                         VOS_NULL_PTR,
                         VOS_NULL_PTR);

    return;
}


/*lint -restore */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

