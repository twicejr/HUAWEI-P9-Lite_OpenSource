/******************************************************************************

                  版权所有 (C), 2001-2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafMmaMain.c
  版 本 号   : 初稿
  作    者   : W00176964
  生成日期   : 2013年7月9日
  最近修改   :
  功能描述   : TafMmaMain.C文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年7月9日
    作    者   : w00176964
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "PsTypeDef.h"
#include "TafLog.h"
#include "TafFsm.h"
#include "TafMmaFsmMainTbl.h"
#include "TafMmaMain.h"
#include "MmaAppLocal.h"
#include "TafMmaProcNvim.h"
#include "TafMmaPreProcTbl.h"
#include "mdrv.h"
#include "NasUtranCtrlInterface.h"
#include "TafMmaProcNvim.h"
#include "NasUsimmApi.h"
#include "TafMmaFsmPhoneModeTbl.h"
#include "TafMmaSndInternalMsg.h"
#include "TafMmaCtx.h"
#include "TafMmaMsgPrioCompare.h"
#include "TafMmaTimerMgmt.h"
#include "TafSdcLib.h"
/* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-25, begin */
#include "Nasrrcinterface.h"
/* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-25, end */

#include "TafMmaFsmImsSwitchTbl.h"

#include "NasComm.h"

#include "TafMmaFsmSysCfgTbl.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 常量定义
*****************************************************************************/

#define    THIS_FILE_ID        PS_FILE_ID_TAF_MMA_MAIN_C

/*****************************************************************************
  3 类型定义
*****************************************************************************/


/*****************************************************************************
  4 函数声明
*****************************************************************************/

/*****************************************************************************
  5 变量定义
*****************************************************************************/
/* 用到的全局变量如下: */
extern VOS_UINT32                                       aStaTimerLen[STA_TIMER_BUTT];
extern TAF_MMA_GLOBAL_VALUE_ST                          gstMmaValue;
extern NAS_MMA_NEW_ADD_GLABAL_VARIABLE_FOR_PC_REPLAY_ST g_MmaNewValue;
extern VOS_INT16                                        g_sLastRscp;
extern VOS_INT16                                        g_sLastEcNo;
extern STATUS_CONTEXT_STRU                              g_StatusContext;
extern VOS_UINT32                                       g_ulUsimHotOutCount;
extern VOS_UINT32                                       g_ulUsimHotInCount;
extern VOS_UINT32                                       g_ucUsimHotOutFlag;
extern VOS_UINT32                                       g_ucUsimHotInFlag;
extern MMA_TIMER_ST                                     g_stPhPinOperTimer;
extern MMA_TIMER_ST                                     g_stPhPhResetTimer;
extern MMA_TIMER_ST                                     g_MmaTimerforPcReplay;
/* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
extern TAF_MMA_LOCATION_STATUS_EVENT_INFO_STRU          g_stMmsStkLocStaSysInfo;
/* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */
extern MMA_TIMER_ST                                     g_MmaSimTimer[TAF_SIM_TIMER_NUM];
extern MMA_TI_TABLE                                     gastMmaTiTab[MMA_MAX_TI];
extern MMA_INTERNAL_TIMER_ST                            gstMmaInternalTimer;
 extern MN_PH_REG_TIME_INFO_STRU                        g_stRegTimeInfo;
extern VOS_UINT8                                        g_ucMnPhRoamStatus;
extern MMA_CIPHER_INFO_STRU                             g_stMmaCipherInfo;
extern ENUM_SYSTEM_APP_CONFIG_TYPE_U16                  g_usMmaAppConfigSupportType;
extern MMA_MODIFY_PLMN_INFO_STRU                        f_stMmaPlmnInfo;
extern VOS_UINT8                                        g_ucMmaOmPcRecurEnableFlg;
extern VOS_UINT8                                        g_ucMmaOmConnectFlg;
extern MMA_ME_PERSONALISATION_STATUS_STRU               g_stMmaMePersonalisationStatus;

extern MMA_UE_FORB_BAND_ST                              gstMmaForbBand;


extern MMA_TIMER_ST                                     g_stPowerDownDelayTimer;

extern MMA_TIMER_ST                                     g_stNetScanProtectTimer;
extern MMA_TIMER_ST                                     g_stAbortNetScanProtectTimer;

/*lint -save -e958 */

/*****************************************************************************
  6 函数定义
*****************************************************************************/
/*****************************************************************************
 函 数 名  : TAF_MMA_BuildEventType
 功能描述  : 构造EventType
 输入参数  : pstMsg      :  消息内容
 输出参数  : 无
 返 回 值  : ulEventType事件类型
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月9日
    作    者   : w00176964
    修改内容   : 新生成函数

  2.日    期   : 2015年6月6日
    作    者   : l00198894
    修改内容   : Modem PID扩展
*****************************************************************************/
VOS_UINT32 TAF_MMA_BuildEventType(
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulEventType;
    MSG_HEADER_STRU                    *pstMsgHeader   = VOS_NULL_PTR;
    REL_TIMER_MSG                      *pstRcvTimerMsg = VOS_NULL_PTR;

    pstMsgHeader = (MSG_HEADER_STRU *)pstMsg;

    /* 动作表里的时间消息不能靠消息头名称进行区分，依靠其结构体的ulName域进行区分
        所以此处进行分别处理 */
    if (VOS_PID_TIMER == pstMsgHeader->ulSenderPid)
    {
        pstRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;
        ulEventType    = TAF_BuildEventType(pstMsgHeader->ulSenderPid, pstRcvTimerMsg->ulName);

        /* 停开关机相关定时器,原来的定时器在后续优化后停止 */
        if (MN_TIMER_CLASS_MMA == (pstRcvTimerMsg->ulName & MN_TIMER_CLASS_MASK))
        {
            TAF_MMA_StopTimer((VOS_UINT16)pstRcvTimerMsg->ulName);
        }
    }
    else
    {
        ulEventType  = TAF_BuildEventType(pstMsgHeader->ulSenderPid, pstMsgHeader->ulMsgName);
    }

    return ulEventType;
}


/*****************************************************************************
 函 数 名    : TAF_MMA_FSM_ProcessEvent
 功能描述    : 状态机的事件处理函数
 输入参数    : ulCurState :当前状态
               ulEventType:处理事件
               pRcvMsg    :消息指针
 输出参数    :
 返回值      : VOS_UINT32:处理是否完成
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月8日
    作    者   : w00176964
    修改内容   : 新生成函数

 *****************************************************************************/
VOS_UINT32 TAF_MMA_FSM_ProcessEvent(
    VOS_UINT32                          ulCurState,
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pRcvMsg
)
{
    TAF_ACTION_FUNC                     pActFun    = VOS_NULL_PTR;
    TAF_FSM_DESC_STRU                  *pstFsmDesc = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    TAF_INFO_LOG2(WUEPS_PID_MMA,"TAF_MMA_FSM_ProcessEvent", ulCurState, ulEventType);

    pstFsmDesc = TAF_MMA_GetCurFsmDesc();

    /* 查找状态转移表中的相应的动作处理函数 */
    pActFun = TAF_FSM_FindAct(pstFsmDesc, ulCurState, ulEventType);

    if (VOS_NULL_PTR != pActFun )
    {
        /* 如果返回的事件处理函数不为空,调用它进行事件处理 */
        ulRet   = (*pActFun) ( ulEventType,(struct MsgCB*)pRcvMsg);
        TAF_INFO_LOG1(WUEPS_PID_MMA,"TAF_MMA_FSM_ProcessEvent", ulRet);
        return ulRet;
    }

    /* 消息未被处理完成需继续处理 */
    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_PreProcessMsg
 功能描述  : MMA消息预处理
 输入参数  : ulEventType  :消息类型
             pstMsg       :消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE:预处理完成
             VOS_FALSE:还需要进行状态机中处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月9日
    作    者   : W00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_MMA_PreProcessMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_FSM_DESC_STRU                  *pstFsmDesc = VOS_NULL_PTR;
    TAF_ACTION_FUNC                     pActFun;
    VOS_UINT32                          ulRet;

    ulRet   = VOS_TRUE;

    /* 消息预处理 */
    TAF_INFO_LOG1(WUEPS_PID_MMA,"TAF_MMA_PreProcessMsg", ulEventType);

    pstFsmDesc = TAF_MMA_GetPreFsmDescAddr();

    /* 查找状态转移表中的相应的动作处理函数 */
    pActFun = TAF_FSM_FindAct(pstFsmDesc, TAF_MMA_MAIN_STA_PREPROC, ulEventType);

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
 函 数 名  : TAF_MMA_ProcessMsgInFsm
 功能描述  : MMA模块消息进状态机查表处理
 输入参数  : ulEventType    :  消息类型+PID
             pstMsg         :  消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE:该消息是否处理完成
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月9日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_MMA_ProcessMsgInFsm(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRet;
    TAF_MMA_FSM_CTX_STRU               *pstCurFsm = VOS_NULL_PTR;
    VOS_UINT16                          usOldStackDepth;
    VOS_UINT16                          usNewStackDepth;

    /* 获取当前MMA的顶层状态 */
    pstCurFsm           = TAF_MMA_GetCurFsmAddr();

    /* 获取当前MMA的栈深度 */
    usOldStackDepth    = TAF_MMA_GetFsmStackDepth();

    /* 消息处理 */
    ulRet     = TAF_MMA_FSM_ProcessEvent( pstCurFsm->ulState,
                                          ulEventType,
                                          (VOS_VOID*)pstMsg );

    /* 获取当前MMA的新栈深度 */
    usNewStackDepth    = TAF_MMA_GetFsmStackDepth();

    /* 栈深度没有增加,表明没有触发新的状态机，可以退出*/
    if ( usNewStackDepth <= usOldStackDepth )
    {
        return ulRet;
    }

    /* 新的栈深度大于老的栈深度 表明进行了压栈,需要将消息放入状态机中继续处理 */
    /* 重新获取当前MMA的顶层状态 */
    pstCurFsm   = TAF_MMA_GetCurFsmAddr();

    /* 将消息放入顶层状态机，继续处理 */
    ulRet       = TAF_MMA_FSM_ProcessEvent( pstCurFsm->ulState,
                                          ulEventType,
                                          (VOS_VOID*)pstMsg );


    return ulRet;

}

/*****************************************************************************
 函 数 名  : TAF_MMA_ProcMsgPrio
 功能描述  : 将当前收到的消息和子状态机的入口消息进行比较,并根据比较结果进行后续的动作
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE: 当前消息处理完成，不需要后续处理
             VOS_FALSE:当前消息处理完成，需要后续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月22日
   作    者   : w00176964
   修改内容   : 新生成函数

 2.日    期   : 2015年4月9日
   作    者   : y00245242
   修改内容   : iteration 13开发
*****************************************************************************/
VOS_UINT32  TAF_MMA_ProcMsgPrio(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_ABORT_FSM_TYPE_UINT8                enAbortType;
    TAF_MMA_MSG_COMPARE_PRIO_RSLT_ENUM_UINT32   enMsgPrio;

    enAbortType = TAF_MMA_ABORT_BUTT;

    enMsgPrio = TAF_MMA_GetMsgComparePrioRslt(ulEventType, pstMsg, &enAbortType);

    switch ( enMsgPrio )
    {
        /* 缓存消息 */
        case TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE :
            if (VOS_FALSE == TAF_MMA_SaveCacheMsgInMsgQueue(ulEventType, (VOS_VOID *) pstMsg))
            {
                /* 消息保存失败 */
                TAF_MMA_RejectAppRequest(ulEventType, pstMsg);
            }
            return VOS_TRUE;

        case TAF_MMA_MSG_COMPARE_PRIO_RSLT_ABORT:
            TAF_MMA_SndInterMmaAbortInd();
            TAF_MMA_ProcessComparePrioRsltAbort(ulEventType, (VOS_VOID *) pstMsg);
            return VOS_TRUE;

        case TAF_MMA_MSG_COMPARE_PRIO_RSLT_REJECT:
            /* 发送拒绝请求 */
            TAF_MMA_ProcessComparePrioRsltReject(ulEventType, (VOS_VOID *) pstMsg);
            return VOS_FALSE;

        case TAF_MMA_MSG_COMPARE_PRIO_RSLT_INITFSM :
        case TAF_MMA_MSG_COMPARE_PRIO_RSLT_DISCARD :
        default:
            NAS_WARNING_LOG1(UEPS_PID_MSCC, "TAF_MMA_ProcMsgPrio:invlid msg priority",ulEventType);
            return VOS_FALSE;
    }

}

/*****************************************************************************
 函 数 名  : TAF_MMA_PostProcessMsg
 功能描述  : MMA状态机后处理函数,将当前收到的消息和sub状态机的入口消息进行比较,
              判断后续的动作
 输入参数  : ulEventType:消息类型
             pstMsg       :消息内容
 输出参数  : 无
 返 回 值  : 返回消息是否已经处理完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月9日
   作    者   : W00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_MMA_PostProcessMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRet;

    ulRet = TAF_MMA_ProcMsgPrio(ulEventType, pstMsg);

    return ulRet;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_ProcessBufferMsg
 功能描述  : 处理缓存
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月12日
   作    者   : W00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_ProcessBufferMsg( VOS_VOID )
{
    TAF_MMA_ENTRY_MSG_STRU             *pstEntryMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          usOldStackDepth;
    VOS_UINT32                          usNewStackDepth;
    VOS_UINT32                          ulOldCacheNum;
    VOS_UINT32                          ulNewCacheNum;

    /* 内存空间分配 */
    pstEntryMsg = (TAF_MMA_ENTRY_MSG_STRU *)PS_MEM_ALLOC( WUEPS_PID_MMA,
                                             sizeof(TAF_MMA_ENTRY_MSG_STRU) );

    if ( VOS_NULL_PTR == pstEntryMsg )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_ProcessBufferMsg:ERROR: MEM ALLOC FAIL");
        return;
    }

    /* 先取高优先级的,再取低优先级的 */
    while (VOS_TRUE == TAF_MMA_GetNextCachedMsg(pstEntryMsg))
    {
        ulOldCacheNum    = TAF_MMA_GetCacheNum();

        if ( VOS_TRUE == TAF_MMA_PreProcessMsg(pstEntryMsg->ulEventType, (struct MsgCB*)pstEntryMsg->aucEntryMsgBuffer) )
        {
            /* 如果缓存的深度增加则表明不能继续继续处理缓存 */
            ulNewCacheNum = TAF_MMA_GetCacheNum();

            if ( ulNewCacheNum > ulOldCacheNum )
            {
                break;
            }
            continue;
        }

        /* 获取当前MMA的栈深度 */
        usOldStackDepth     = TAF_MMA_GetFsmStackDepth();

        /* 进入状态机处理 */
        ulRet  = TAF_MMA_ProcessMsgInFsm(pstEntryMsg->ulEventType, (struct MsgCB*)pstEntryMsg->aucEntryMsgBuffer);

        /* 获取当前MMA的栈深度 */
        usNewStackDepth     = TAF_MMA_GetFsmStackDepth();

        /* 如果栈的深度增加,说明肯定进行了压栈操作,不能继续处理消息 */
        if ( usNewStackDepth > usOldStackDepth )
        {
            break;
        }

        /* 该消息进入了后处理,后处理中是打断或缓存的,则表明不能继续处理缓存 */
        if (VOS_FALSE == ulRet)
        {
            if ( VOS_TRUE == TAF_MMA_PostProcessMsg(pstEntryMsg->ulEventType,
                            (struct MsgCB*)pstEntryMsg->aucEntryMsgBuffer))
            {
                break;
            }
        }
    }

    PS_MEM_FREE(UEPS_PID_MSCC, pstEntryMsg);

    return;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_MsgProc
 功能描述  : MMA的消息处理函数
 输入参数  : pstMsg       :MMA收到的消息
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月9日
   作    者   : w00176964
   修改内容   : Mma_MsgProc函数名修改以及增加预处理和状态机处理分支
*****************************************************************************/
VOS_VOID  TAF_MMA_MsgProc(
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulEventType;
    VOS_UINT16                          usNewStackDepth;
    VOS_UINT16                          usOldStackDepth;

    if ( VOS_NULL_PTR == pstMsg )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_MsgProc:null pointer");

        return;
    }

    /* svlte特性开启时，modem1可能收到usim0的消息，需要将消息中send pid进行转换 */
    if (VOS_TRUE == TAF_SDC_GetSvlteSupportFlag())
    {
        pstMsg->ulSenderPid = TAF_SDC_ConvertOamSendPid(pstMsg->ulSenderPid);
    }

    usOldStackDepth = TAF_MMA_GetFsmStackDepth();
    ulEventType     = TAF_MMA_BuildEventType(pstMsg);

    /* 如果已经预处理完成则直接返回 */
    if (VOS_TRUE == TAF_MMA_PreProcessMsg(ulEventType, pstMsg))
    {
        return;
    }

    /* 进入状态机处理 */
    ulRet  = TAF_MMA_ProcessMsgInFsm(ulEventType, pstMsg);

    /* 状态机中会收到连接释放、状态机退出等消息,所以不能直接返回
    还需要判断能否处理缓存*/
    usNewStackDepth    = TAF_MMA_GetFsmStackDepth();

    /* 如果栈的深度减少,说明肯定进行了退栈操作,需要优先处理该状态机的结果消息,直接返回 */
    if ( usNewStackDepth < usOldStackDepth )
    {
        /* 记录退栈操作,只要发生了退栈后续就可以处理缓存 */
        TAF_MMA_SetFsmStackPopFlg(VOS_TRUE);
        return;
    }

    /* 该消息在状态机中已经处理完成,可尝试处理一下缓存 */
    if ( VOS_TRUE == ulRet)
    {
        /* 当前仅收到状态机的退出消息才能够处理缓存 */
        if (VOS_TRUE == TAF_MMA_GetFsmStackPopFlg())
        {
            TAF_MMA_ProcessBufferMsg();
            TAF_MMA_SetFsmStackPopFlg(VOS_FALSE);
        }
    }
    /* 在当前状态机中未处理完毕，判断消息是否需要打断当前的L2状态机,后处理 */
    else
    {
        (VOS_VOID)TAF_MMA_PostProcessMsg(ulEventType, pstMsg);
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_RegFsm
 功能描述  : 各个状态机注册
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:注册成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年05月8日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2015年02月04日
    作    者   : f00179208
    修改内容   : IMS动态开关配置项目
*****************************************************************************/
VOS_VOID TAF_MMA_RegFsm( VOS_VOID  )
{
    /* 预处理注册 */
    TAF_FSM_RegisterFsm((TAF_MMA_GetPreFsmDescAddr()),
                         "TAF:FSM:MMA:PreProcess",
                         TAF_MMA_GetPreProcessStaTblSize(),
                         TAF_MMA_GetPreProcessStaTbl(),
                         VOS_NULL_PTR,
                         VOS_NULL_PTR);

    /* 注册Main状态机 */
    TAF_FSM_RegisterFsm((TAF_MMA_GetMainFsmDescAddr()),
                         "TAF:FSM:MMA:MAIN",
                         (VOS_UINT32)(TAF_MMA_GetMainStaTblSize()),
                         TAF_MMA_GetMainStaTbl(),
                         VOS_NULL_PTR,
                         VOS_NULL_PTR);

    /* 注册Sub状态机 */
    /* 注册Phone Mode子状态机 */
    TAF_FSM_RegisterFsm((TAF_MMA_GetPhoneModeFsmDescAddr()),
                         "TAF:FSM:MMA:Phone Mode",
                         (VOS_UINT32)TAF_MMA_GetPhoneModeStaTblSize(),
                         TAF_MMA_GetPhoneModeProcessStaTbl(),
                         VOS_NULL_PTR,
                         TAF_MMA_InitFsmCtx_PhoneMode);

#if (FEATURE_IMS == FEATURE_ON)
    /* 注册IMS SWITCH子状态机 */
    TAF_FSM_RegisterFsm((TAF_MMA_GetImsSwitchFsmDescAddr()),
                         "TAF:FSM:MMA:IMS SWITCH",
                         (VOS_UINT32)TAF_MMA_GetImsSwitchStaTblSize(),
                         TAF_MMA_GetImsSwitchProcessStaTbl(),
                         VOS_NULL_PTR,
                         VOS_NULL_PTR);
#endif

    /* 注册SYS CFG SUB状态机 */
    TAF_FSM_RegisterFsm((TAF_MMA_GetSysCfgFsmDescAddr()),
                         "TAF:FSM:MMA:SYS CFG",
                         (VOS_UINT32)TAF_MMA_GetSysCfgStaTblSize(),
                         TAF_MMA_GetSysCfgProcessStaTbl(),
                         VOS_NULL_PTR,
                         TAF_MMA_InitFsmCtx_SysCfg);


}

/*****************************************************************************
 函 数 名  : TAF_MMA_InitTask
 功能描述  : MMA任务初始化函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月9日
   作    者   : W00176964
   修改内容   : 新生成函数

 2.日    期   : 2013年12月03日
   作    者   : z00234330
   修改内容   : dts2012120302954 不需要启动定时器,sdt om端口链接上时和sdt上的log删除时，会导出可维可测
*****************************************************************************/
VOS_VOID  TAF_MMA_InitTask( VOS_VOID )
{
    VOS_UINT32                          ulAutoInitPsFlg;

    NAS_TRACE_HIGH("Mma Init Task Begin!!");

    /* 全局变量初始化 */
    TAF_MMA_InitCtx(TAF_MMA_INIT_CTX_STARTUP, TAF_MMA_GetMmaCtxAddr());

    /* 读取NV */
    TAF_MMA_ReadNvim();

    TAF_MMA_InitTimerLen();

    /* 注册状态机 */
    TAF_MMA_RegFsm();

    ulAutoInitPsFlg = TAF_MMA_GetAutoInitPsFlg();

    NAS_TRACE_HIGH("ulAutoInitPsFlg = %d",ulAutoInitPsFlg);

    /* 上电初始化协议栈NV打开并且不是SFT平台则自动上电 */
    if ((DRV_NOT_START_UMTS != mdrv_sysboot_check_startps())
     && (VOS_TRUE == ulAutoInitPsFlg))
    {
        /* 发送内部上电消息 */
        TAF_MMA_SndInterPowerInitReq();
    }
    else
    {
        NAS_TRACE_HIGH("Not start PS");

        /* FID初始化已投票禁止睡眠,非自动开机的场景允许睡眠 */
        TAF_DRVAPI_PWRCTRL_SLEEPVOTE_UNLOCK(PWRCTRL_SLEEP_NAS);
    }


    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_InitPid
 功能描述  : MMA的PID初始化函数
 输入参数  : enum VOS_INIT_PHASE_DEFINE ip
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月9日
    作    者   : w00176964
    修改内容   : WuepsMmaPidInit修改函数名
  2.日    期   : 2014年8月20日
    作    者   : y00213812
    修改内容   : 增加CMDA模式下CSIM卡的注册回调

*****************************************************************************/
VOS_UINT32 TAF_MMA_InitPid (
    enum VOS_INIT_PHASE_DEFINE          ip
)
{
    switch (ip)
    {
        case VOS_IP_LOAD_CONFIG:
            MMA_WriteVersion();
            break;

        case VOS_IP_INITIAL:

            (VOS_VOID)NAS_PIHAPI_RegUsimCardStatusIndMsg(WUEPS_PID_MMA);
            NAS_PIHAPI_RegCardRefreshIndMsg(WUEPS_PID_MMA);



            break;

        case VOS_IP_STARTUP:

            TAF_MMA_InitTask();

            break;

        case VOS_IP_RIVAL:
        case VOS_IP_KICKOFF:
        case VOS_IP_STANDBY:
        case VOS_IP_BROADCAST_STATE:
        case VOS_IP_RESTART:
        case VOS_IP_FARMALLOC:
        case VOS_IP_ENROLLMENT:
        case VOS_IP_LOAD_DATA:
        case VOS_IP_FETCH_DATA:
            break;

        default:
            break;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_InitCtx
 功能描述  : MMA CTX模块初始化
 输入参数  : enInitType:初始化类型,上电或软关机
 输出参数  : pstMsccCtx:MMA上下文信息
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月9日
   作    者   : W00176964
   修改内容   : 新生成函数
 2.日    期   : 2014年1月28日
   作    者   : s00217060
   修改内容   : DTS2014011709107:修改g_stRegTimeInfo初始值
 3.日    期   : 2013年4月1日
   作    者   : y00176023
   修改内容   : DSDS GUNAS II项目:增加对扩展模块(物理层)的初始化
 4.日    期   : 2015年3月2日
   作    者   : z00161729
   修改内容   : AT&T 支持EONS特性修改
 5.日    期   : 2015年4月10日
   作    者   : h00313353
   修改内容   : SysCfg重构
 6.日    期   : 2015年9月28日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增

*****************************************************************************/
VOS_VOID  TAF_MMA_InitCtx(
    TAF_MMA_INIT_CTX_TYPE_ENUM_UINT8     enInitType,
    TAF_MMA_CONTEXT_STRU                *pstMmaCtx
)
{
    /* 以下全局变量是上电和关机时都需要初始化的 */
    PS_MEM_SET(&g_stMmsStkLocStaSysInfo, 0, sizeof(TAF_MMA_LOCATION_STATUS_EVENT_INFO_STRU));

    PS_MEM_SET(&g_stMmaCipherInfo, 0, sizeof(MMA_CIPHER_INFO_STRU));

    g_ucMnPhRoamStatus              = TAF_PH_INFO_NONE_ROMAING;  /* 记录漫游状态(上报给应用) */

    g_stRegTimeInfo.enRegTimeState  = MN_PH_REG_TIME_STATE_BEGIN;
    g_stRegTimeInfo.ulBeginTick     = 0;
    g_stRegTimeInfo.ulCostTime      = 0;
    g_stRegTimeInfo.ulEndTick       = 0;

    f_stMmaPlmnInfo.stPlmnId.Mcc    = TAF_SDC_INVALID_MCC;
    f_stMmaPlmnInfo.stPlmnId.Mnc    = TAF_SDC_INVALID_MNC;
    f_stMmaPlmnInfo.usIndex         = 0;
    f_stMmaPlmnInfo.PlmnRat         = TAF_MMA_RAT_BUTT;

    TAF_MMA_InitStatusCtx(enInitType);

    TAF_MMA_InitSdcNetworkInfo(enInitType);

    TAF_MMA_InitAllTimers(enInitType, pstMmaCtx->astMmaTimerCtx);

    /* Added by w00167002 for L-C互操作项目, 2014-2-18, begin */
    TAF_MMA_InitOperCtx(pstMmaCtx->astMmaOperCtx);
    /* Added by w00167002 for L-C互操作项目, 2014-2-18, end */

    TAF_MMA_InitMmaGlobalValue(enInitType);

    /* 以下全局变量只有在上电时需要初始化，关机时不需要初始化 */
    if (TAF_MMA_INIT_CTX_STARTUP == enInitType)
    {
        g_ucMmaOmConnectFlg             = VOS_FALSE;
        g_ucMmaOmPcRecurEnableFlg       = VOS_FALSE;


        g_usMmaAppConfigSupportType     = SYSTEM_APP_BUTT;

        TAF_MMA_InitBandInfo();

        TAF_MMA_InitMePersonalisationStatus();

        TAF_MMA_InitTi();

        TAF_MMA_InitTimerLen();

        TAF_MMA_InitTimerId();

        /* USIM热插拔标志 */
        g_ucUsimHotOutFlag  = VOS_FALSE;
        g_ucUsimHotInFlag   = VOS_FALSE;
        g_ulUsimHotOutCount = 0;
        g_ulUsimHotInCount  = 0;

        TAF_MMA_InitPhoneModeCtrlCtx(TAF_MMA_GetPhoneModeCtrl());

        TAF_MMA_InitCurrFsmCtx(&pstMmaCtx->stCurFsm);

        TAF_MMA_InitFsmStackCtx(&pstMmaCtx->stFsmStack);

        TAF_MMA_InitInternalBuffer(&pstMmaCtx->stBufferEntryMsgQueue);

        TAF_MMA_InitInternalMsgQueue(&pstMmaCtx->stInternalMsgQueue);

        TAF_MMA_InitMaintainInfo(&pstMmaCtx->stMaintainInfo);
        TAF_MMA_InitExternalModuleInitStatus(&(pstMmaCtx->stMmaExternalModuleInitStatusCtx));

        TAF_MMA_InitCFreqLockPara();


        TAF_MMA_InitGetGeoCtx();

        TAF_MMA_InitSetDplmnCtx();

#if (FEATURE_ON == FEATURE_CSG)
        TAF_MMA_InitCsgListCtx();
#endif
        /* 初始化IccId */
        TAF_MMA_InitSdcIccId();

        TAF_MMA_InitDelayRptCtrlInfo();

        /* HPLMN可能在开关机过程中查询，不能在关机时清除全局变量 */
        TAF_MMA_InitGetHplmnInfo();
    }


    TAF_MMA_InitAttachInfo();

    TAF_MMA_InitDsdsInfo();

    return;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_ReadNvim
 功能描述  : MMA模块读取NV的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月11日
   作    者   : W00176964
   修改内容   : 新生成函数

 2.日    期   : 2014年2月20日
   作    者   : w00167002
   修改内容   : L-C互操作项目:PID初始化读取NV

 3.日    期   : 2015年4月16日
   作    者   : y00245242
   修改内容   : iteration 13开发
*****************************************************************************/

VOS_VOID TAF_MMA_ReadNvim(VOS_VOID)
{

    /* 更新频段相关NV */
    TAF_MMA_UpdateUeAllowedBandRange();

    /* en_NV_Item_SelPlmn_Mode */
    TAF_MMA_ReadPlmnSelectionModeNvim();

    /* 读platform RAT cap*/
    TAF_MMA_ReadPlatformRatCap();

    /* en_NV_Item_RAT_PRIO_LIST */
    TAF_MMA_ReadRatPrioListNvim();

    /* en_NV_Item_MMA_MsClass */
    TAF_MMA_ReadMsClassNvim();

    /* en_NV_Item_Roam_Capa */
    TAF_MMA_ReadRoamCapaNvim();

    /* en_NV_Item_Roaming_Broker */
    TAF_MMA_ReadRoamingBrokerInfoNvim();

    /* en_NV_Item_REPORT_PLMN_SUPPORT_FLAG */
    TAF_MMA_ReadReportPlmnSupportFlgNvim();

    /* en_NV_Item_MMA_AccessMode */
    TAF_MMA_ReadAccessModeNvim();

    /* en_NV_Item_FollowOn_OpenSpeed_Flag */
    TAF_MMA_ReadFollowonOpenSpeedFlagNvim();

    /* en_NV_Item_RF_Auto_Test_Flag */
    TAF_MMA_ReadRfAutoTestFlagNvim();

    /* en_NV_Item_EFust_Service_Cfg */
    TAF_MMA_ReadEFustServiceCfgNvim();


    /* en_NV_Item_NotDisplayLocalNetworkName */
    TAF_MMA_ReadNotDisplayLocalNetworkNameNvim();

    /* en_NV_Item_System_APP_Config */
    TAF_MMA_ReadSystemAppCofigNvim();

    /* en_NV_Item_IMEI */
    TAF_MMA_ReadImeiNvim();

    /* en_NV_Item_FMRID */
    TAF_MMA_ReadFmridNvim();

    /* en_NV_Item_ProductName */
    TAF_MMA_ReadProductNameNvim();

    /* en_NV_Item_Att_Ens_Ctrl_Para */
    TAF_MMA_ReadAttEnsCustomNvim();


    /* en_NV_Item_DEACT_USIM_WHEN_POWEROFF */
    TAF_MMA_ReadDeactUsimWhenPoweroffNvim();

    /* en_NV_Item_PS_START */
    TAF_MMA_ReadPsStartNvim();

    /* en_NV_Item_CardlockStatus */
    TAF_MMA_ReadCardLockStatusNvim();

    /* en_NV_Item_CustomizeSimLockMaxTimes */
    TAF_MMA_ReadSimLockMaxTimesNvim();

    /* en_NV_Item_CustomizeSimLockPlmnInfo */
    TAF_MMA_ReadSimLockPlmnNvim();

    /* en_NV_Item_Sim_Personalisation_Pwd */
    TAF_MMA_ReadSimPersonalisationPwdNvim();

    /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-25, begin */
    GASGCOM_UpdateCustomizeNv();
    /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-25, end */

    /* Added by w00167002 for L-C互操作项目, 2014-2-20, begin */
    TAF_MMA_ReadLcCtrlNvim();
    /* Added by w00167002 for L-C互操作项目, 2014-2-20, end */

    TAF_MMA_ReadCFreqLockNvim();

    /* en_NV_Item_Ccpu_Reset_Record */
    TAF_MMA_ReadCcpuResetRecordNvim();

    /* en_NV_Item_Get_Geo_Cfg_Info */
    TAF_MMA_ReadGetGeoCfgInfoNvim();

    TAF_MMA_ReadDelayReportServiceStatusCfgNvim();

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    TAF_MMA_ReadCLDelayReportSrvCfgNvim();

    TAF_MMA_ReadMeidFromNvim();

    TAF_MMA_ReadEsnFromNvim();

    TAF_MMA_ReadDelaySndCLServiceStatusTimeLenNvim();
#endif


    TAF_MMA_ReadNonnormalRegStatusMergeCfgNvim();
    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_InitTi
 功能描述  : 增加全局TI初始化
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2006年3月8日
    作    者   : liuyang id:48197
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_InitTi(VOS_VOID)
{
    VOS_UINT32                          ulI;

    for (ulI = 0; ulI < MMA_MAX_TI; ulI++)
    {
        gastMmaTiTab[ulI].ClientId   = MMA_CLIENTID_NONE;
        gastMmaTiTab[ulI].Id         = MMA_OP_ID_INTERNAL;
        gastMmaTiTab[ulI].ucUsed     = MMA_TI_UNUSED;
        gastMmaTiTab[ulI].PhoneEvent = TAF_PH_EVT_ERR;
    }

    return;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_InitTimerId
 功能描述  : 复位内部定时器相关全局变量指针
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月15日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2015年2月26日
    作    者   : b00269685
    修改内容   : at&t修改

*****************************************************************************/
VOS_VOID TAF_MMA_InitTimerId(VOS_VOID)
{
    VOS_UINT32                          i;

    for (i = 0; i< TAF_SIM_TIMER_NUM; i++)
    {
        if ( MMA_TIMER_STOP == g_MmaSimTimer[0].ucTimerStatus )
        {
            g_MmaSimTimer[i].MmaHTimer = VOS_NULL_PTR;
        }
    }

    /*USIM OPIN*/
    g_MmaSimTimer[0].ulTimerId                          = TAF_USIM_OPPIN;


    /* Init MMA Timer for PC Replay */
    g_MmaTimerforPcReplay.ulTimerId                     = MMA_TIMER_FOR_PC_REPLAY;

    g_stPhPhResetTimer.ulTimerId                        = TI_MN_PH_RESET;

    g_stPhPinOperTimer.ulTimerId                        = TI_MN_PH_PIN_OPER;


    g_stPowerDownDelayTimer.ulTimerId                   = TI_TAF_MMA_DELAY_POWER_DOWN;


    g_stNetScanProtectTimer.ulTimerId                   = TI_TAF_MMA_NET_SCAN_TIMER;
    g_stAbortNetScanProtectTimer.ulTimerId              = TI_TAF_MMA_ABORT_NET_SCAN_TIMER;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_InitNetworkSelectionMenuCtx
 功能描述  : 初时化网络选择菜单控制上下文
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月19日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_InitNetworkSelectionMenuCtx(VOS_VOID)
{
    g_StatusContext.stNetSelMenuCtx.ucNetSelMenuFlg   = VOS_FALSE;
    g_StatusContext.stNetSelMenuCtx.enPlmnMode        = TAF_MMA_PLMN_MODE_ENUM_ENABLE;
    g_StatusContext.stNetSelMenuCtx.enAutoPlmnSelUser = TAF_MMA_AUTO_PLMN_SEL_USER_AT;
    g_StatusContext.stNetSelMenuCtx.ucRsv             = 0;
    g_StatusContext.stNetSelMenuCtx.stTiPeriodTryingNetSelMenu.MmaHTimer
                                                      = VOS_NULL_PTR;
    g_StatusContext.stNetSelMenuCtx.stTiPeriodTryingNetSelMenu.ulTimerId
                                                      = TI_TAF_MMA_PERIOD_TRYING_NETWORK_SELECTION_MENU;
    g_StatusContext.stNetSelMenuCtx.stTiPeriodTryingNetSelMenu.ucTimerStatus
                                                      = MMA_TIMER_STOP;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_InitRatBalancingCtx
 功能描述  : 初时化接入技术平衡控制上下文
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月19日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_InitRatBalancingCtx(VOS_VOID)
{
    g_StatusContext.stRatBalancingCtx.ucRatBalancingFlg = VOS_FALSE;
    g_StatusContext.stRatBalancingCtx.enRatMode         = TAF_MMA_RAT_MODE_ENUM_BUTT;
    g_StatusContext.stRatBalancingCtx.aucRsv[0]         = 0;
    g_StatusContext.stRatBalancingCtx.aucRsv[1]         = 0;
    g_StatusContext.stRatBalancingCtx.stTiPeriodTryingRatBalancing.MmaHTimer
                                                        = VOS_NULL_PTR;
    g_StatusContext.stRatBalancingCtx.stTiPeriodTryingRatBalancing.ulTimerId
                                                        = TI_TAF_MMA_PERIOD_TRYING_RAT_BALANCING;
    g_StatusContext.stRatBalancingCtx.stTiPeriodTryingRatBalancing.ucTimerStatus
                                                        = MMA_TIMER_STOP;

    return;
}

/* TAF_MMA_InitUsimInfo */

/*****************************************************************************
 函 数 名  : TAF_MMA_InitStatusCtx
 功能描述  : 初始化和USIM模块相关的信息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月15日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2015年4月10日
    作    者   : h00313353
    修改内容   : SysCfg重构
*****************************************************************************/
VOS_VOID TAF_MMA_InitStatusCtx(
    TAF_MMA_INIT_CTX_TYPE_ENUM_UINT8     enInitType
)
{
    VOS_UINT32                          i;

    /* 只在上电时初始化的变量 */
    if (TAF_MMA_INIT_CTX_STARTUP == enInitType)
    {
        g_StatusContext.ulFsmState      = STA_FSM_NULL;
        g_StatusContext.ulPreFsmState   = STA_FSM_NULL;
        for ( i = 0; i < STA_TIMER_MAX; i++ )
        {
            g_StatusContext.aucFsmSubFlag[i]         = STA_FSMSUB_NULL;
            g_StatusContext.ahStaTimer[i]            = 0;
            g_StatusContext.aFsmSub[i].ulOpId        = 0;
            g_StatusContext.aFsmSub[i].ucFsmStateSub = STA_FSMSUB_NULL;
            g_StatusContext.aFsmSub[i].TimerName     = STA_TIMER_NULL;
        }

        g_StatusContext.ulCurOpId                    = 0;
        g_StatusContext.ulCurClientId                = 0;
        g_StatusContext.ulNewOpId                    = 0;

        g_StatusContext.ulMmProc                     = 0;


        g_StatusContext.stRatPrioList.ucRatOrderNum  = 0;
        g_StatusContext.stRatPrioList.aenRatOrder[0] = TAF_MMA_RAT_BUTT;
        g_StatusContext.stRatPrioList.aenRatOrder[1] = TAF_MMA_RAT_BUTT;
        g_StatusContext.stRatPrioList.aenRatOrder[2] = TAF_MMA_RAT_BUTT;

        g_StatusContext.ucPlmnSelMode                = TAF_PH_PLMN_SEL_MODE_AUTO;
    }

    /* 以下为上电和关机时都需要初始化的变量 */
    g_StatusContext.ucIsReportedLocStatus        = VOS_FALSE;

    g_StatusContext.StaPlmnId.Mcc                = TAF_SDC_INVALID_MCC;
    g_StatusContext.StaPlmnId.Mnc                = TAF_SDC_INVALID_MNC;
    for ( i = 0; i < TAF_MAX_PLMN_NUM; i++ )
    {
        g_StatusContext.PlmnList.Plmn[i].Mcc     = TAF_SDC_INVALID_MCC;
        g_StatusContext.PlmnList.Plmn[i].Mnc     = TAF_SDC_INVALID_MNC;
    }
    g_StatusContext.PlmnList.ucPlmnNum           = 0;

    g_StatusContext.ucPlmnListAbortProc          = TAF_MMA_PLMN_LIST_ABORT_BUTT;

    g_StatusContext.ulCsCause                    = NAS_MSCC_PIF_CAUSE_NULL;
    g_StatusContext.ulPsCause                    = NAS_MSCC_PIF_CAUSE_NULL;
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-3, end */

    g_StatusContext.ulTimMaxFlg                  = VOS_FALSE;

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-3, begin */
    g_StatusContext.ucReselMode                  = 0;
    g_StatusContext.ucDomainFlag                 = NAS_MSCC_PIF_SRVDOMAIN_NO_DOMAIN;
    g_StatusContext.ucModeService                = TAF_PH_MS_CLASS_NULL;
    g_StatusContext.ucOperateType                = STA_OP_NULL;

    g_StatusContext.PhoneError                   = TAF_ERR_NO_ERROR;

    g_StatusContext.ucPreUtranMode               = NAS_UTRANCTRL_UTRAN_MODE_BUTT;

    g_StatusContext.ucDataTranStatus             = STA_DATA_TRANSFER_STATUS_BUTT;
    g_StatusContext.ucDataTranMode               = STA_DATA_TRANSFER_MODE_BUTT;

    for ( i = 0; i < STA_TIMER_MAX; i++ )
    {
        /*初始化电话操作*/
        g_StatusContext.aucStaPhoneOperator[i]   = STA_FSMSUB_NULL;
    }

    /* 初始化网络选择菜单和接入技术平衡 */
    TAF_MMA_InitNetworkSelectionMenuCtx();
    TAF_MMA_InitRatBalancingCtx();

}

/*****************************************************************************
 函 数 名  : TAF_MMA_InitRssiValue
 功能描述  : 初始化MMA中Rssi值
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年2月4日
    作    者   : t00212959
    修改内容   : AT^CERSSI?增加返回参数
  2.日    期   : 2014年11月29日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseI项目修改
*****************************************************************************/
 VOS_VOID TAF_MMA_InitRssiValue(VOS_VOID)
{


    /* 初始化其为最小值 */
    g_sLastRscp = MMA_RSCP_MIN;
    g_sLastEcNo = MMA_ECNO_MIN;

    /*将部分初始化的工作移到TAF_SDC_InitRssiValue()*/


    return;

}


/*****************************************************************************
 函 数 名  : TAF_MMA_InitCellAcInfo
 功能描述  : 清空接入禁止MMA的全局变量
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年2月18日
    作    者   : l00167671
    修改内容   : DTS2013021804440,在L下不使用该全局变量记录接入禁止情况，清空成非接入禁止
                 回到GU下时如果接入禁止发生改变MSCC会重新上报
  2.日    期   : 2013年4月19日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
*****************************************************************************/
VOS_VOID TAF_MMA_InitCellAcInfo(VOS_VOID)
{
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-20, begin */
    TAF_SDC_ACCESS_RESTRICTION_STRU     stCsAcRetriction;
    TAF_SDC_ACCESS_RESTRICTION_STRU     stPsAcRetriction;

    stCsAcRetriction.enCellAcType        = TAF_SDC_CELL_RESTRICTION_TYPE_NONE;
    stCsAcRetriction.ucRestrictPagingRsp = VOS_FALSE;
    stCsAcRetriction.ucRestrictRegister  = VOS_FALSE;
    stCsAcRetriction.ucReserved          = 0;

    stPsAcRetriction.enCellAcType        = TAF_SDC_CELL_RESTRICTION_TYPE_NONE;
    stPsAcRetriction.ucRestrictPagingRsp = VOS_FALSE;
    stPsAcRetriction.ucRestrictRegister  = VOS_FALSE;
    stPsAcRetriction.ucReserved          = 0;

    TAF_SDC_SetCsAcRestriction(&stCsAcRetriction);
    TAF_SDC_SetPsAcRestriction(&stPsAcRetriction);
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-20, end */

    return;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_InitSyscfgInfo
 功能描述  : 初始化和syscfg相关的信息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月15日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2015年4月9日
    作    者   : h00313353
    修改内容   : SysCfg宏定义转为枚举
*****************************************************************************/
VOS_VOID TAF_MMA_InitSyscfgInfo(VOS_VOID)
{

    TAF_MMA_LAST_SETTED_SYSCFG_SET_STRU *pstLastSyscfgSet = VOS_NULL_PTR;

    pstLastSyscfgSet                = TAF_MMA_GetLastSyscfgSetAddr();
    pstLastSyscfgSet->stRatPrioList = gstMmaValue.pg_StatusContext->stRatPrioList;

    /* 初始化LastSyscfg */
    pstLastSyscfgSet->enSrvDomain                       = TAF_MMA_SERVICE_DOMAIN_NULL;
    pstLastSyscfgSet->enRoam                            = NAS_MSCC_PIF_ROAM_BUTT;
    pstLastSyscfgSet->enPrioRat                         = TAF_MMA_USER_SET_PRIO_AUTO;

    /* 初始化接入技术，如果ATT的接入技术平衡定制NV激活，开机读4F36文件，否则从NV中获取接入技术 */
    MN_MMA_SetDefaultRatPrioList(&(pstLastSyscfgSet->stRatPrioList));

    /* 更新gstMmaValue.pg_StatusContext.stRatPrioList全局变量 */
    PS_MEM_CPY(&gstMmaValue.pg_StatusContext->stRatPrioList, &(pstLastSyscfgSet->stRatPrioList), sizeof(TAF_MMA_RAT_ORDER_STRU));

    /* GSM的支持的Band */
    pstLastSyscfgSet->stUserSetBand.uUserSetUeFormatGuBand.unGsmBand.BitBand.BandGsm1800= VOS_TRUE;
    pstLastSyscfgSet->stUserSetBand.uUserSetUeFormatGuBand.unGsmBand.BitBand.BandGsm1900= VOS_TRUE;
    pstLastSyscfgSet->stUserSetBand.uUserSetUeFormatGuBand.unGsmBand.BitBand.BandGsm450 = VOS_TRUE;
    pstLastSyscfgSet->stUserSetBand.uUserSetUeFormatGuBand.unGsmBand.BitBand.BandGsm480 = VOS_TRUE;
    pstLastSyscfgSet->stUserSetBand.uUserSetUeFormatGuBand.unGsmBand.BitBand.BandGsm700 = VOS_TRUE;
    pstLastSyscfgSet->stUserSetBand.uUserSetUeFormatGuBand.unGsmBand.BitBand.BandGsm850 = VOS_TRUE;
    pstLastSyscfgSet->stUserSetBand.uUserSetUeFormatGuBand.unGsmBand.BitBand.BandGsmE900= VOS_TRUE;
    pstLastSyscfgSet->stUserSetBand.uUserSetUeFormatGuBand.unGsmBand.BitBand.BandGsmP900= VOS_TRUE;
    pstLastSyscfgSet->stUserSetBand.uUserSetUeFormatGuBand.unGsmBand.BitBand.BandGsmR900= VOS_FALSE;

    /* WCDMA的支持的Band */
    pstLastSyscfgSet->stUserSetBand.uUserSetUeFormatGuBand.unWcdmaBand.BitBand.BandWCDMA_III_1800 = VOS_TRUE;
    pstLastSyscfgSet->stUserSetBand.uUserSetUeFormatGuBand.unWcdmaBand.BitBand.BandWCDMA_II_1900  = VOS_TRUE;
    pstLastSyscfgSet->stUserSetBand.uUserSetUeFormatGuBand.unWcdmaBand.BitBand.BandWCDMA_IV_1700  = VOS_TRUE;
    pstLastSyscfgSet->stUserSetBand.uUserSetUeFormatGuBand.unWcdmaBand.BitBand.BandWCDMA_IX_J1700 = VOS_TRUE;
    pstLastSyscfgSet->stUserSetBand.uUserSetUeFormatGuBand.unWcdmaBand.BitBand.BandWCDMA_I_2100   = VOS_TRUE;
    pstLastSyscfgSet->stUserSetBand.uUserSetUeFormatGuBand.unWcdmaBand.BitBand.BandWCDMA_VIII_900 = VOS_TRUE;
    pstLastSyscfgSet->stUserSetBand.uUserSetUeFormatGuBand.unWcdmaBand.BitBand.BandWCDMA_VII_2600 = VOS_TRUE;
    pstLastSyscfgSet->stUserSetBand.uUserSetUeFormatGuBand.unWcdmaBand.BitBand.BandWCDMA_VI_800   = VOS_TRUE;
    pstLastSyscfgSet->stUserSetBand.uUserSetUeFormatGuBand.unWcdmaBand.BitBand.BandWCDMA_V_850    = VOS_TRUE;

#if(FEATURE_ON == FEATURE_LTE)
    /* LTE的支持的Band */
    pstLastSyscfgSet->stUserSetBand.stUserSetLteBand.ulBandHigh = MN_MMA_LTE_HIGH_BAND_ANY;
    pstLastSyscfgSet->stUserSetBand.stUserSetLteBand.ulBandLow  = MN_MMA_LTE_LOW_BAND_ANY;
#endif
    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_InitPhoneModeCtrlCtx
 功能描述  : 初始化和开关机相关的控制信息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月15日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_InitPhoneModeCtrlCtx(
    TAF_MMA_PHONE_MODE_CTRL_CTX_STRU   *pstCtrlCtx
)
{
    /* 默认初始化快速开机标志为Disable */
    gstMmaValue.ulQuickStartFlg = MMA_QUICK_START_DISABLE;

    /* Deleted by w00176964 for VoLTE_PhaseIII 项目, 2013-12-25, begin */

    /* Deleted by w00176964 for VoLTE_PhaseIII 项目, 2013-12-25, end */

    /* 默认初始化为上电需要初始化栈 */
    pstCtrlCtx->ulAutoInitPsFlg     = VOS_TRUE;

    /* 默认初始化为上电需要自动开机以及自动下发搜网 */
    pstCtrlCtx->ulAutoSwitchOnFlg   = VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_InitOrigMeInfo
 功能描述  : 初始化stMeInfo
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
 修改历史      :
    1.日    期   : 2009年02月01日
      作    者   : l00130025
      修改内容   : 问题单号：AT2D08501,修改MMA的MeInfo的初始化,软关机时不清除UE信息
    2.日    期   : 2009年07月10日
      作    者   : l00130025
      修改内容   : 问题单号：AT2D12843,输入ATI命令返回厂商名称与其他平台数据卡不一致
    3.日    期   : 2009年07月10日
      作    者   : l00130025
      修改内容   : 问题单号：AT2D12751,Mobile Partner概率性不识别单板驱动名称
    4.日    期   : 2012年11月1日
      作    者   : w00167002
      修改内容   : DTS2012102905571:DCM定制需求，如果当前NV配置不显示本地的全球
                    运行商列表信息,则直接返回.
    5.日    期   : 2015年2月28日
      作    者   : z00161729
      修改内容   : AT&T 支持EONS特性修改
*****************************************************************************/
VOS_VOID TAF_MMA_InitOrigMeInfo( VOS_VOID )
{
    VOS_UINT32                          i;
    VOS_INT32                           lRslt;
    VOS_UINT32                          ulDataLen;
    VOS_CHAR                           *ucSoftDate = "2006/11/15";
    VOS_CHAR                           *ucSoftTime = "00:00:00";

    gstMmaValue.stMeInfo.ImeisV.ImeiMode                                 = TAF_PH_IMEIV_Mode;
    for ( i = 0; i < TAF_PH_IMEI_LEN; i++ )
    {
         gstMmaValue.stMeInfo.ImeisV.aucImei[i]                            = 0;
    }
    gstMmaValue.stMeInfo.ProductName.aucProductName[0]                          = '\0';
    gstMmaValue.stMeInfo.ModelId.aucModelId[0]                                  = '\0';
    gstMmaValue.stMeInfo.ReleaseDate.aucReleaseDate[0]                          = '\0';
    gstMmaValue.stMeInfo.ReleaseTime.aucReleaseTime[0]                          = '\0';
    gstMmaValue.stMeInfo.CompleteCapitiyList.aucCompleteCapilityList[0][0]      = '\0';
    gstMmaValue.stMeInfo.CompleteCapitiyList.aucCompleteCapilityList[1][0]      = '\0';
    gstMmaValue.stMeInfo.CompleteCapitiyList.aucCompleteCapilityList[2][0]      = '\0';
    gstMmaValue.stMeInfo.GsmCompleteCapitiyList.aucCompleteCapilityList[0][0]   = '\0';
    gstMmaValue.stMeInfo.GsmCompleteCapitiyList.aucCompleteCapilityList[1][0]   = '\0';
    gstMmaValue.stMeInfo.GsmCompleteCapitiyList.aucCompleteCapilityList[2][0]   = '\0';
    (VOS_VOID)VOS_StrNCpy((VOS_CHAR *)( gstMmaValue.stMeInfo.SoftVersion.aucRevisionId), 0x00,
                         TAF_MAX_REVISION_ID_LEN+1);
    (VOS_VOID)VOS_sprintf((VOS_CHAR *) gstMmaValue.stMeInfo.FmrId.aucMfrId, "huawei");

    /*获取发行日期*/
    ulDataLen = TAF_PH_RELEASEDATE_LEN + 1;
    (VOS_VOID)VOS_StrNCpy( (VOS_CHAR *)(gstMmaValue.stMeInfo.ReleaseDate.aucReleaseDate),
                 ucSoftDate,
                 ulDataLen);

    /*获取发行时间*/
    ulDataLen = TAF_PH_RELEASETIME_LEN + 1;
    (VOS_VOID)VOS_StrNCpy( (VOS_CHAR *)(gstMmaValue.stMeInfo.ReleaseTime.aucReleaseTime),
                 ucSoftTime,
                 ulDataLen);

    /*获取硬件模块名*/
    lRslt = mdrv_ver_memberctrl((VOS_INT8 *)(gstMmaValue.stMeInfo.ModelId.aucModelId),
                    TAF_MAX_MODEL_ID_LEN,
                    VER_PRODUCT_ID,
                    VERIONREADMODE);
    if(MDRV_OK != lRslt)
    {
        MMA_WARNINGLOG("MMA_InitMeInfo():VER_PRODUCT_ID  Failed!");
    }

    /*获取软件版本号*/
    lRslt = mdrv_ver_memberctrl((VOS_INT8 *)(gstMmaValue.stMeInfo.SoftVersion.aucRevisionId),
                    TAF_MAX_REVISION_ID_LEN + 1,
                    VER_SOFTWARE,
                    VERIONREADMODE);
    if ( MDRV_OK != lRslt )
    {
        MMA_WARNINGLOG("MMA_InitMeInfo():Read Software Version  Failed!");
    }
    /* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-11, begin */

    /* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-11, end */

    /* 默认全球运营商表有效  */
    gstMmaValue.ucNotDisplayLocalNetworkNameFlg = VOS_FALSE;

   /* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-11, begin */

   /* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-11, end */
}



/*****************************************************************************
 函 数 名  : TAF_MMA_InitTimerLen
 功能描述  : 初始化定时器时长
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月28日
    作    者   : s46746
    修改内容   : DSDA GUNAS C CORE项目，定时器时长初始化
  2.日    期   : 2013年7月10日
    作    者   : w00176964
    修改内容   : VoLTE_Phase1项目:开关机定时器重新设计
*****************************************************************************/
VOS_VOID TAF_MMA_InitTimerLen(VOS_VOID)
{
    aStaTimerLen[STA_TIMER_NULL]            = STA_TIMER_NULL_LEN;
    /* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-10, begin */
    /* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-10, end */
    aStaTimerLen[STA_TIMER_PLMN_RESEL]      = STA_TIMER_PLMN_RESEL_LEN;
    aStaTimerLen[STA_TIMER_PLMN_SEL]        = STA_TIMER_PLMN_SEL_LEN;
    aStaTimerLen[STA_TIMER_SERVICE_IND]     = STA_TIMER_SERVICE_IND_LEN;
    aStaTimerLen[STA_TIMER_SPEC_PLMN_ABORT] = STA_TIMER_SPEC_PLMN_ABORT_LEN;


#if(FEATURE_ON == FEATURE_LTE)
    /* 平台支持LTE */
    if (VOS_TRUE == TAF_SDC_IsPlatformSupportLte())
    {
        /* 对全局变量 aStaTimerLen 进行赋值，时长考虑L模场景 */
        aStaTimerLen[STA_TIMER_PLMN_LIST]       = STA_TIMER_GUL_PLMN_LIST_LEN;

        aStaTimerLen[STA_TIMER_PLMN_LIST_ABORT] = STA_TIMER_GUL_PLMN_LIST_ABORT_LEN;
    }
    else
#endif
    {
        /* 对全局变量 aStaTimerLen 进行赋值 */
        aStaTimerLen[STA_TIMER_PLMN_LIST]       = STA_TIMER_GU_PLMN_LIST_LEN;

        aStaTimerLen[STA_TIMER_PLMN_LIST_ABORT] = STA_TIMER_GU_PLMN_LIST_ABORT_LEN;
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_InitInternalTimer
 功能描述  : 复位内部定时器相关全局变量指针
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2006年6月7日
    作    者   : liuyang id:48197
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_InitInternalTimer(VOS_VOID)
{
    gstMmaInternalTimer.ulTimes                  = 0;
    gstMmaInternalTimer.stTimer.ulTimerId        = MMA_INTERNAL_TIMER_ID;
    gstMmaInternalTimer.stTimer.ucTimerStatus    = MMA_TIMER_STOP;
    gstMmaInternalTimer.ulOpType                 = MMA_INTERNAL_OP_NONE;
    gstMmaInternalTimer.ClientId                 = MMA_CLIENTID_NONE;
    gstMmaInternalTimer.OpId                     = MMA_OP_ID_INTERNAL;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_InitAllTimers
 功能描述  : 初始化所有定时器，应在mma初始化时被调用
 输入参数  : pstMmaTimerCtx - 定时器上下文指针
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月23日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  TAF_MMA_InitAllTimers(
    TAF_MMA_INIT_CTX_TYPE_ENUM_UINT8     enInitType,
    TAF_MMA_TIMER_CTX_STRU              *pstMmaTimerCtx
)
{
    VOS_UINT32                          i;

    for (i = 0 ; i < TAF_MMA_MAX_TIMER_NUM ; i++)
    {
        pstMmaTimerCtx[i].hTimer        = VOS_NULL_PTR;
        pstMmaTimerCtx[i].enTimerId     = TI_TAF_MMA_TIMER_BUTT;
        pstMmaTimerCtx[i].enTimerStatus = TAF_MMA_TIMER_STATUS_STOP;
        pstMmaTimerCtx[i].aucReserve[0] = 0;
    }

    for ( i = 0; i < STA_TIMER_MAX; i++ )
    {
        if (STA_TIMER_NULL != g_StatusContext.aFsmSub[i].TimerName )
        {
            (VOS_VOID)VOS_StopRelTimer(&g_StatusContext.ahStaTimer[i]);
            g_StatusContext.aFsmSub[i].TimerName = STA_TIMER_NULL;
        }
    }

    /* 只有在上电才初始化内部定时器 */
    if (TAF_MMA_INIT_CTX_STARTUP == enInitType)
    {
        TAF_MMA_InitInternalTimer();
    }

    return;
}

/* Added by w00167002 for L-C互操作项目, 2014-2-18, begin */
/*****************************************************************************
 函 数 名  : TAF_MMA_InitOperCtx
 功能描述  : 初始化所有OperCtx内容，应在mma初始化时被调用
 输入参数  : pstMmaOperCtx - OperCtx内容指针
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月18日
    作    者   : w00167002
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  TAF_MMA_InitOperCtx(
    TAF_MMA_OPER_CTX_STRU               *pstMmaOperCtx
)
{
    VOS_UINT32                          i;

    for (i = 0; i < TAF_MMA_MAX_OPER_NUM; i++)
    {
        pstMmaOperCtx[i].stCtrl.ulModuleId        = 0;
        pstMmaOperCtx[i].stCtrl.usClientId        = 0;
        pstMmaOperCtx[i].stCtrl.ucOpId            = 0;
        pstMmaOperCtx[i].stCtrl.aucReserved[0]    = 0;
        pstMmaOperCtx[i].ucUsedFlag               = VOS_FALSE;
        pstMmaOperCtx[i].enOperType               = TAF_MMA_OPER_BUTT;
        pstMmaOperCtx[i].aucReserved[0]           = 0;
        pstMmaOperCtx[i].aucReserved[1]           = 0;
        pstMmaOperCtx[i].aucReserved[2]           = 0;
        pstMmaOperCtx[i].pPara                    = VOS_NULL_PTR;
    }

    return;
}

/* Added by w00167002 for L-C互操作项目, 2014-2-18, end */

/*****************************************************************************
 函 数 名  : TAF_MMA_InitSdcNetworkInfo
 功能描述  : 初始化SDC模块中网络相关信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月10日
    作    者   : w00176964
    修改内容   : VoLTE_Phase1项目新增
  2.日    期   : 2014年12月27日
    作    者   : s00217060
    修改内容   : Service_State_Optimize_PhaseI
  3.日    期   : 2015年2月25日
    作    者   : z00161729
    修改内容   : AT&T 支持EONS特性修改
  4.日    期   : 2015年12月29日
    作    者   : z00359541
    修改内容   : DTS2015120305849: 增加初始化原因值为入参
*****************************************************************************/
VOS_VOID TAF_MMA_InitSdcNetworkInfo(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8     enInitType
)
{
    TAF_SDC_CTX_STRU                    *pstSdcCtx = VOS_NULL_PTR;

    pstSdcCtx = TAF_SDC_GetSdcCtx();

    /* 初始化SDC模块中网络相关信息 */
    TAF_SDC_InitNetWorkInfo(&pstSdcCtx->stNetworkInfo);

    TAF_SDC_InitAppNetwork_Info(&pstSdcCtx->stAppNetworkInfo);

    TAF_SDC_InitEnhancedOperatorNameInfo(enInitType, &(pstSdcCtx->stEnhancedOperatorNameInfo));
}

/*****************************************************************************
 函 数 名  : TAF_MMA_InitMePersonalisationStatus
 功能描述  : 初始化定时器时长
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月10日
    作    者   : w00176964
    修改内容   : VoLTE_Phase1项目新增
*****************************************************************************/
VOS_VOID TAF_MMA_InitMePersonalisationStatus(VOS_VOID)
{
    PS_MEM_SET(&g_stMmaMePersonalisationStatus, 0, sizeof(g_stMmaMePersonalisationStatus));

    g_stMmaMePersonalisationStatus.SimLockStatus = MMA_SIM_IS_UNLOCK;
    g_stMmaMePersonalisationStatus.stCardLockInfo.OperatorLockStatus =
                                                   TAF_OPERATOR_LOCK_NONEED_UNLOCK_CODE;

}

/*****************************************************************************
 函 数 名  : TAF_MMA_InitMmaGlobalValue
 功能描述  : 初始化全局变量gstMmaValue
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月10日
    作    者   : w00176964
    修改内容   : VoLTE_Phase1项目新增
  2.日    期   : 2013年10月30日
    作    者   : z00161729
    修改内容   : DTS2013103005073:cardlock解锁卡成功后，mma会触发重新关机清除了
                 g_MmaNewValue.stSimLockMaxTimes.ulLockMaxTimes全局变量，重新开机未重新读取nv项，
                 导致cardlock查询剩余次数为0
  3.日    期   : 2015年2月28日
    作    者   : b00269685
    修改内容   : at&t支持 eons修改
*****************************************************************************/
VOS_VOID TAF_MMA_InitMmaGlobalValue(
    TAF_MMA_INIT_CTX_TYPE_ENUM_UINT8     enInitType
)
{
    /* 以下变量只需要在上电时初始化 */
    if (TAF_MMA_INIT_CTX_STARTUP == enInitType)
    {
        PS_MEM_SET(&gstMmaValue, 0, sizeof(TAF_MMA_GLOBAL_VALUE_ST));
        PS_MEM_SET(&g_MmaNewValue, 0, sizeof(NAS_MMA_NEW_ADD_GLABAL_VARIABLE_FOR_PC_REPLAY_ST));

        /* 所有全局变量复位 */
        gstMmaValue.pg_StatusContext    = &g_StatusContext;

        /* 初始化电池电量信息 */
        gstMmaValue.stBatteryPower.BatteryPowerStatus       = TAF_PH_BATTERYCHARGING;
        gstMmaValue.stBatteryPower.BatteryRemains           = MMA_BATTERY_FULL;

        /* 初始化对PIN码操作相关信息 */
        gstMmaValue.stOpPinData.stMmaPinData.CmdType        = TAF_PIN_CMD_NULL;

        /* 初始化手机类型相关信息 */
        gstMmaValue.stSetMsClass.MsClassType                = gstMmaValue.pg_StatusContext->ucModeService;
        gstMmaValue.stSetMsClass.NewMsClassType             = gstMmaValue.pg_StatusContext->ucModeService;

        /* 初始化漫游特性 */
        gstMmaValue.ucRoamFeatureStatus = NAS_MSCC_PIF_ROAM_FEATURE_OFF;
        gstMmaValue.ucRoamBrokerSwitch  = VOS_FALSE;

        /* 初始化PLMN上报标志 */
        gstMmaValue.ucReportPlmnFlg     = VOS_FALSE;

        TAF_MMA_InitSyscfgInfo();

        TAF_MMA_InitOrigMeInfo();

    }

    /* 以下变量上电和关机都需要初始化 */
    TAF_MMA_InitRssiValue();

    g_MmaNewValue.stSimLockMaxTimes.ulLockMaxTimes  = TAF_PH_CARDLOCK_DEFAULT_MAXTIME;

    return;

}

/*****************************************************************************
 函 数 名  : TAF_MMA_InitBandInfo
 功能描述  : 初始化频段能力信息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月7日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_InitBandInfo(VOS_VOID)
{
    TAF_MMA_UE_BAND_CAPA_ST            *pstUeBandCap = VOS_NULL_PTR;

    pstUeBandCap = TAF_MMA_GetUeSupportBandAddr();

    /* 初始化gstMmaBandCapa */
    pstUeBandCap->ulUeGSptBand         = TAF_PH_BAND_GSM_BAND_ALL;
    pstUeBandCap->ulUeWSptBand         = TAF_PH_BAND_WCDMA_BAND_ALL;
    pstUeBandCap->ulAllUeBand          = (pstUeBandCap->ulUeGSptBand | pstUeBandCap->ulUeWSptBand);
    pstUeBandCap->unWRFSptBand.ulBand  = TAF_PH_BAND_WCDMA_BAND_ALL;
    pstUeBandCap->unGRFSptBand.ulBand  = TAF_PH_BAND_GSM_BAND_ALL;

#if(FEATURE_ON == FEATURE_LTE)
    pstUeBandCap->stUeSupportLteBand.ulBandLow     = MN_MMA_LTE_HIGH_BAND_ANY;
    pstUeBandCap->stUeSupportLteBand.ulBandHigh    = 0;
#endif

    /* 初始化gstMmaForbBand */
    PS_MEM_SET(&gstMmaForbBand, 0, sizeof(gstMmaForbBand));
    gstMmaForbBand.ucActiveFlag = NV_ITEM_DEACTIVE;
    gstMmaForbBand.ucForbStatus = VOS_FALSE;

}

/*****************************************************************************
 函 数 名  : TAF_MMA_InitDsdsInfo
 功能描述  : 初始化DSDS相关的信息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月29日
    作    者   : l00301449
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_InitDsdsInfo(VOS_VOID)
{
    TAF_MMA_SRV_ACQ_RAT_LIST_STRU      *pstSrvAcqRatListAddr = VOS_NULL_PTR;

    pstSrvAcqRatListAddr = TAF_MMA_GetSrvAcqRatListAddr();

    PS_MEM_SET(pstSrvAcqRatListAddr, 0, sizeof(TAF_MMA_SRV_ACQ_RAT_LIST_STRU));
}

/*****************************************************************************
 函 数 名  : TAF_MMA_InitAttachInfo
 功能描述  : 初始化ATTACH相关信息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月29日
    作    者   : l00301449
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_InitAttachInfo(VOS_VOID)
{
    TAF_MMA_CONTEXT_STRU                *pstMmaCtx = VOS_NULL_PTR;

    pstMmaCtx = TAF_MMA_GetMmaCtxAddr();

    pstMmaCtx->stAttachInfo.ucAttachOpId         = 0;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_MsgProcEntry
 功能描述  : MMA的消息处理入口函数
 输入参数  : pstMsg       :MMA收到的消息
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月19日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  TAF_MMA_MsgProcEntry(
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_INTERNAL_MSG_BUF_STRU      *pstNextMsg = VOS_NULL_PTR;

    /* 先处理外部消息 */
    TAF_MMA_MsgProc(pstMsg);

    /* 外部消息处理完成后处理内部消息 */
    pstNextMsg = TAF_MMA_GetNextInternalMsg();

    while (VOS_NULL_PTR != pstNextMsg)
    {
        /* 将该消息钩出来,以便于在PSTAS中显示 */
        DIAG_TraceReport(pstNextMsg);
        TAF_MMA_MsgProc((struct MsgCB *)pstNextMsg);

        /* 寻找下一条内部消息 */
        pstNextMsg = TAF_MMA_GetNextInternalMsg();
    }
}

/*****************************************************************************
 函 数 名  : TAF_MMA_InitDelayRptCtrlInfo
 功能描述  : 延时上报nv项信息初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年10月10日
   作    者   : l00324781
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_InitDelayRptCtrlInfo(VOS_VOID)
{

    /* GUL模试下，服务状态延时上报nv项初始化，初始化为关闭 */
    TAF_MMA_SetDelayReportServiceStatusFlg(VOS_FALSE);
    TAF_MMA_SetDelayReportServiceStatusTimerLen(0);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    /* CL模试下，服务状态延时上报nv项初始化，初始化为关闭 */
    TAF_MMA_SetCLDelayReptSrvStatusFlg(VOS_FALSE);
    TAF_MMA_SetCLDelayReptSrvStatusTimerLen(0);
#endif

    PS_MEM_SET(TAF_MMA_GetCLNoServiceDelayRptInfo(), 0x00, sizeof(TAF_MMA_CL_NO_SERVICE_DELAY_RPT_STRU));

    TAF_MMA_GetCLNoServiceDelayRptInfo()->enDelayType   = TAF_MMA_DELAY_CL_REPORT_TYPE_BUTT;

    TAF_INFO_LOG(WUEPS_PID_MMA, "CLNoServiceDelayRptInfo Init To 0");
}

/*lint -restore */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


