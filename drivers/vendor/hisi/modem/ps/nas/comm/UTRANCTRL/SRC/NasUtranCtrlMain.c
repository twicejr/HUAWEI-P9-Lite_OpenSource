

/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "PsTypeDef.h"
#include "NasComm.h"
#include "NasUtranCtrlMain.h"
#include "NasUtranCtrlCtx.h"
#include "NasUtranCtrlFsmMainTbl.h"
#include "NasUtranCtrlFsmSwitchOnTbl.h"
#include "NasUtranCtrlFsmPoweroffTbl.h"
#include "NasUtranCtrlFsmSyscfgTbl.h"
#include "NasUtranCtrlFsmPlmnSelectionTbl.h"
#include "NasUtranCtrlFsmModeChangeTbl.h"
#include "NasMmlMsgProc.h"
#include "NasUtranCtrlMntn.h"
#include "NasUtranCtrlCommFunc.h"
#include "NasMmlLib.h"

#include "NasMmcSndInternalMsg.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 常量定义
*****************************************************************************/

#define    THIS_FILE_ID        PS_FILE_ID_NAS_UTRANCTRL_MAIN_C

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
  6 函数定义
*****************************************************************************/

VOS_UINT32 NAS_UTRANCTRL_MsgProc(
    struct MsgCB                       *pstSrcMsg,
    struct MsgCB                      **ppstDestMsg
)
{
#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
    VOS_UINT32                          ulRet;

    MSG_HEADER_STRU                    *pstMsgHeader;

#ifndef __PS_WIN32_RECUR__
    VOS_UINT32                          ulIsSndOmPcRecurMsgValid;
#endif

    pstMsgHeader = (MSG_HEADER_STRU *)pstSrcMsg;

    /* 默认为该消息需要进入原有MM层模块处理 */
    ulRet        = VOS_FALSE;

#if (FEATURE_ON == FEATURE_PTM)
    if (VOS_TRUE == NAS_MML_IsNeedNwSearchInfoRecord(pstSrcMsg))
    {
        NAS_MML_RecordNwSearchInfo(pstSrcMsg);
    }
#endif

    /* 平台对W/TD都不支持时，直接返回VOS_FALSE */
    if (VOS_FALSE == NAS_MML_IsPlatformSupportUtran())
    {
        *ppstDestMsg = pstSrcMsg;
        return VOS_FALSE;
    }

    /* 判断接受PID为MMC，进入PID适配处理函数 */
    switch (pstMsgHeader->ulReceiverPid)
    {
        case WUEPS_PID_MMC:

            ulRet = NAS_UTRANCTRL_ProcessMmcMsg(pstSrcMsg);
            break;

        default:

            break;
    }

    /* 消息需要继续处理，需要对消息继续处理，如将TDS的PID适配为WCDMA的PID */
    if (VOS_FALSE == ulRet)
    {
        NAS_UTRANCTRL_PostProcMsg(pstSrcMsg, ppstDestMsg);
    }

#ifndef __PS_WIN32_RECUR__

    /* UTRANCTRL模块的回放消息发送 */
    ulIsSndOmPcRecurMsgValid = NAS_UTRANCTRL_IsSndOmPcRecurMsgValid();

    if ((VOS_TRUE == NAS_UTRANCTRL_GetUePcRecurFlg())
     && (VOS_TRUE == ulIsSndOmPcRecurMsgValid))
    {
        NAS_UTRANCTRL_SetUePcRecurFlg(VOS_FALSE);
        NAS_UTRANCTRL_SndOutsideContextData();
    }
#endif

    return ulRet;
#else

    *ppstDestMsg = pstSrcMsg;

    /* 继续处理处理 */
    return VOS_FALSE;
#endif
}


VOS_VOID NAS_UTRANCTRL_ProcBufferMsg(VOS_VOID)
{
#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
    struct MsgCB                       *pstNextBufferMsg     = VOS_NULL_PTR;
    struct MsgCB                       *pstNextBufferDestMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;

    /* 先判断是否可以处理UTRANCTRL模块的缓存消息 */
    if (NAS_UTRANCTRL_FSM_MAIN == NAS_UTRANCTRL_GetCurrFsmId())
    {
        /* 从UTRANCTRL模块获取缓存的外部消息 */
        pstNextBufferMsg = NAS_UTRANCTRL_GetNextCachBufferMsg();

        while (VOS_NULL_PTR != pstNextBufferMsg)
        {
            /* 将当前消息进入UTRANCTRL模块进行处理 */
            ulRslt = NAS_UTRANCTRL_MsgProc(pstNextBufferMsg, &pstNextBufferDestMsg);

            /* 消息在UTRANCTRL模块未处理完成,继续在MMC继续处理 */
            if (VOS_FALSE == ulRslt)
            {
                /* 处理从UTRANCTRL模块获取的缓存消息 */
                NAS_MML_MsgProc(pstNextBufferDestMsg);
            }

            /* 消息在UTRANCTRL处理后，可能重新进到状态机，需要跳出当前缓冲消息循环处理 */
            if (NAS_UTRANCTRL_FSM_MAIN != NAS_UTRANCTRL_GetCurrFsmId())
            {
                /* 跳出循环 */
                break;
            }

            /* 寻找下一条UTRANCTRL模块缓存的外部消息 */
            pstNextBufferMsg = (struct MsgCB *)NAS_UTRANCTRL_GetNextCachBufferMsg();
        }
    }
#endif
}

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)

VOS_UINT32 NAS_UTRANCTRL_ProcessMmcMsg(
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulEventType;
    VOS_UINT32                          ulRslt;
    MSG_HEADER_STRU                    *pstMsgHeader;
    REL_TIMER_MSG                      *pRcvTimerMsg;
    NAS_UTRANCTRL_FSM_ID_ENUM_UINT32    enPreFsmId;

    pstMsgHeader = (MSG_HEADER_STRU *)pstMsg;

    /* 取得当前消息的事件类型 */
    ulEventType = NAS_UTRANCTRL_GetMsgEventType(pstMsg);

    /* UTRANCTRL 模块的定时器需要在超时时统一停止定时器,方便勾出SDT消息 */
    if (VOS_PID_TIMER == pstMsgHeader->ulSenderPid)
    {
        pRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;

        /* UTRANCTRL的定时器超时则这里进行停止,MMC的定时器在MMC模块停止 */
        if (pRcvTimerMsg->ulName >= NAS_UTRANCTRL_TIMER_ID_START_INDEX)
        {
            NAS_UTRANCTRL_StopTimer((NAS_MMC_TIMER_ID_ENUM_UINT16)(pRcvTimerMsg->ulName));
        }
    }

#if defined(__PC_TRACE_RECUR__)
    /* 无条件处理回放消息 */
    if (NAS_UTRANCTRL_OM_MSG_LOG_RUNNING_CONTEXT_FOR_PC_REPLAY == pstMsgHeader->ulMsgName)
    {
        NAS_UTRANCTRL_RestoreContextData_Main(ulEventType, pstMsg);
        return VOS_TRUE;
    }
#endif


    /* 判断当前是否需要进Utran状态机处理*/
    if ( VOS_FALSE == NAS_UTRANCTRL_IsNeedUtranCtrlFsmProcMsg(pstMsg))
    {
        return VOS_FALSE;

    }

    /* 状态机处理之前,取得当前的状态机名称 */
    enPreFsmId = NAS_UTRANCTRL_GetCurrFsmId();

    /* 在当前状态机中处理当前消息 */
    ulRslt = NAS_UTRANCTRL_ProcessMsgInFsm(ulEventType, pstMsg);

    /* 由空闲态转到其他状态，则需要继续处理当前消息 */
    if ((NAS_UTRANCTRL_FSM_MAIN   != NAS_UTRANCTRL_GetCurrFsmId())
     && (NAS_UTRANCTRL_FSM_MAIN   == enPreFsmId))
    {
        /* 状态机处理之前,取得当前的状态机名称 */
        enPreFsmId = NAS_UTRANCTRL_GetCurrFsmId();

        ulRslt = NAS_UTRANCTRL_ProcessMsgInFsm(ulEventType, pstMsg);
    }

    /* 从其它状态机切换到IDLE状态机,清除缓存的搜网或SYSCFG请求消息 */
    if ((NAS_UTRANCTRL_FSM_MAIN == NAS_UTRANCTRL_GetCurrFsmId())
     && (NAS_UTRANCTRL_FSM_MAIN != enPreFsmId))
    {
        NAS_UTRANCTRL_ClearBufferedSndUtranReqMsg();
    }

    /* 返回消息的处理结果 */
    return ulRslt;
}


VOS_VOID  NAS_UTRANCTRL_PostProcMsg(
    struct MsgCB                       *pstSrcMsg,
    struct MsgCB                      **ppstDestMsg
)
{
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstEntryMsg;

    MSG_HEADER_STRU                    *pstMsgHeader;

    pstEntryMsg                         = NAS_UTRANCTRL_GetBufferUtranSndMmcMsgAddr();

    /* 判断是否需要替换入口消息 */
    if (VOS_TRUE == NAS_UTRANCTRL_GetReplaceMmcMsgFlg())
    {
        *ppstDestMsg = (struct MsgCB *)pstEntryMsg->aucEntryMsgBuffer;

        /* 消息已经使用，回复设置标记位，但不能清除消息。  */
        NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_FALSE);
    }
    else
    {
        *ppstDestMsg = pstSrcMsg;
    }

    pstMsgHeader = (MSG_HEADER_STRU *)(*ppstDestMsg);

    switch (pstMsgHeader->ulSenderPid)
    {
        case TPS_PID_PDC:

            (*ppstDestMsg)->ulSenderPid = WUEPS_PID_PDCP;
            break;

        case TPS_PID_RLC:

            (*ppstDestMsg)->ulSenderPid = WUEPS_PID_RLC;
            break;

        case TPS_PID_RRC:

            (*ppstDestMsg)->ulSenderPid = WUEPS_PID_WRR;
            break;

         default:
            break;
    }

}



VOS_VOID NAS_UTRANCTRL_RegFsm( VOS_VOID  )
{
    /* 主处理注册 */
    NAS_FSM_RegisterFsm(NAS_UTRANCTRL_GetMainFsmDescAddr(),
                         "NAS_UTRANCTRL:FSM:MainProcess",
                         NAS_UTRANCTRL_GetMainProcessStaTblSize(),
                         NAS_UTRANCTRL_GetMainProcessStaTbl(),
                         VOS_NULL_PTR,
                         NAS_UTRANCTRL_InitFsmCtx_Main);


    /* 开机状态机注册 */
    NAS_FSM_RegisterFsm(NAS_UTRANCTRL_GetSwitchOnFsmDescAddr(),
                         "NAS_UTRANCTRL:FSM:SwitchOnProcess",
                         NAS_UTRANCTRL_GetSwitchOnStaTblSize(),
                         NAS_UTRANCTRL_GetSwitchOnStaTbl(),
                         VOS_NULL_PTR,
                         NAS_UTRANCTRL_InitFsmCtx_SwitchOn);

    /* 关机状态机注册 */
    NAS_FSM_RegisterFsm(NAS_UTRANCTRL_GetPowerOffFsmDescAddr(),
                         "NAS_UTRANCTRL:FSM:PowerOffProcess",
                         NAS_UTRANCTRL_GetPowerOffStaTblSize(),
                         NAS_UTRANCTRL_GetPowerOffStaTbl(),
                         VOS_NULL_PTR,
                         NAS_UTRANCTRL_InitFsmCtx_PowerOff);

    /* 搜网状态机注册 */
    NAS_FSM_RegisterFsm(NAS_UTRANCTRL_GetPlmnSelectionFsmDescAddr(),
                         "NAS_UTRANCTRL:FSM:PlmnSelectionProcess",
                         NAS_UTRANCTRL_GetPlmnSelectionStaTblSize(),
                         NAS_UTRANCTRL_GetPlmnSelectionStaTbl(),
                         VOS_NULL_PTR,
                         NAS_UTRANCTRL_InitFsmCtx_PlmnSelection);

    /* SYSCFG状态机注册 */
    NAS_FSM_RegisterFsm(NAS_UTRANCTRL_GetSysCfgFsmDescAddr(),
                         "NAS_UTRANCTRL:FSM:SYSCFG",
                         NAS_UTRANCTRL_GetSysCfgStaTblSize(),
                         NAS_UTRANCTRL_GetSysCfgStaTbl(),
                         VOS_NULL_PTR,
                         NAS_UTRANCTRL_InitFsmCtx_Syscfg);

    /* mode change状态机注册 */
    NAS_FSM_RegisterFsm(NAS_UTRANCTRL_GetModeChangeFsmDescAddr(),
                         "NAS_UTRANCTRL:FSM:ModeChange",
                         NAS_UTRANCTRL_GetModeChangeStaTblSize(),
                         NAS_UTRANCTRL_GetModeChangeStaTbl(),
                         VOS_NULL_PTR,
                         NAS_UTRANCTRL_InitFsmCtx_ModeChange);


    return;
}




VOS_UINT32 NAS_UTRANCTRL_ProcessMsgInFsm(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_ACTION_FUNC                     pActFun;
    NAS_UTRANCTRL_FSM_CTX_STRU         *pstCurFsm;
    VOS_UINT32                          ulRslt;

    NAS_UTRANCTRL_FSM_ID_ENUM_UINT32    enCurrFsmId;

    MSG_HEADER_STRU                    *pstMsgHeader  = VOS_NULL_PTR;

    pstMsgHeader = (MSG_HEADER_STRU *)pstMsg;

    /* 取得当前的状态机名称 */
    enCurrFsmId = NAS_UTRANCTRL_GetCurrFsmId();

    /* 获取当前UTRANCTRL的状态机地址 */
    pstCurFsm           = NAS_UTRANCTRL_GetCurFsmAddr();

    /* 查找状态转移表中的相应的动作处理函数 */
    pActFun = NAS_FSM_FindAct(pstCurFsm->pstFsmDesc, pstCurFsm->ulState, ulEventType);

    if (VOS_NULL_PTR != pActFun)
    {
        /* 在状态表中对消息进行处理 */
        ulRslt = (*pActFun) (ulEventType, (struct MsgCB *)pstMsg);
        return ulRslt;
    }

    /* 通知接入层模式通知或SYSCFG设置的时候，缓存所有找不到的消息 */
    if ((NAS_UTRANCTRL_FSM_MODE_CHANGE == enCurrFsmId)
     || (NAS_UTRANCTRL_FSM_SYSCFG      == enCurrFsmId))
    {
        /* 消息长度超过了缓存的长度，则不保存, 防止数组越界 */
        if ( (pstMsgHeader->ulLength + VOS_MSG_HEAD_LENGTH) > NAS_UTRANCTRL_MAX_MSG_BUFFER_LEN )
        {
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_ProcessMsgInFsm:Msg too big to save ");

            /* 状态表中未找到要处理的消息,则需继续处理 */
            return VOS_FALSE;
        }

        NAS_UTRANCTRL_SaveCacheMsgInMsgQueue(ulEventType, pstMsg);

        /* 缓存消息,当前MMC状态机不处理,后续处理适配层缓存 */
        return VOS_TRUE;
    }

    /* 状态表中未找到要处理的消息,则需继续处理 */
    return VOS_FALSE;
}

#endif








#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
