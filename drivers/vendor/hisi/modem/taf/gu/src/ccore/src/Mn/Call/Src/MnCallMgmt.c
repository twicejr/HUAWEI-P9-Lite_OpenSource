

/*****************************************************************************
   1 头文件包含
*****************************************************************************/
#include "vos.h"
#include "TafTypeDef.h"

#include "MnCallApi.h"

#include "MnComm.h"
#include "MnCallReqProc.h"
#include "MnCallSendCc.h"
#include "UsimPsInterface.h"
#include "MnCallFacilityEncode.h"
#include "NVIM_Interface.h"
#include "NasOmInterface.h"

#include "MnErrorCode.h"
#include "MnCall.h"
#include "AtTafAgentInterface.h"
#include "MnCallProcNvim.h"
#include "MnCallMgmt.h"
#include "MnComm.h"

#include "NasStkInterface.h"

#include "NasIeUtil.h"

#include "MnCallTimer.h"

#include "TafSdcLib.h"

#include "NasUsimmApi.h"

#if (FEATURE_ON == FEATURE_IMS)
#include "SpmImsaInterface.h"
#include "CallImsaInterface.h"
#endif

#include "MnCallSendApp.h"

#include "RabmTafInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_MNCALL_MGMT_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/

/*****************************************************************************
   2 内部数据类型定义
*****************************************************************************/

/*****************************************************************************
   3 全局变量和静态变量定义
*****************************************************************************/
/* 呼叫管理实体 */
LOCAL MN_CALL_MGMT_STRU                     f_astCallMgmtEntities[MN_CALL_MAX_NUM];

/* CALL模块DTMF状态及缓存信息 */
LOCAL TAF_CALL_DTMF_CTX_STRU                f_stCallDtmfCtx;

LOCAL VOS_BOOL                              f_abCallReleaseFlag[MN_CALL_MAX_NUM];

/* 补充业务操作管理 */
LOCAL MN_CALL_SUPS_CMD_ENUM_U8_MGMT_STRU    f_stCallSupsCmdMgmt;

/*CCBS功能打开时,保留的Setup消息 */
LOCAL NAS_CC_MSG_SETUP_MO_STRU              f_stCcbsSetup;

/* 由于CallId分配是从1开始的，故该变量也从1开始 */
/* 呼叫计费相关信息 */
LOCAL MN_CALL_TIMER_CALC_ST            gastCallTimerCalc[CALL_MAX_ENT_NUM + 1];

/*ALS功能打开时,保留的线路号 */
LOCAL MN_CALL_ALS_LINE_NO_ENUM_U8           f_enAlsLineNo = MN_CALL_ALS_LINE_NO_1;

LOCAL MN_CALL_MATCH_MSG_TYPE_STRU           f_stCallMsgType[] =
{
    {MN_CALL_UUS1_MSG_SETUP             ,NAS_CC_MSG_SETUP},
    {MN_CALL_UUS1_MSG_ALERT             ,NAS_CC_MSG_ALERTING},
    {MN_CALL_UUS1_MSG_CONNECT           ,NAS_CC_MSG_CONNECT},
    {MN_CALL_UUS1_MSG_DISCONNECT        ,NAS_CC_MSG_DISCONNECT},
    {MN_CALL_UUS1_MSG_RELEASE           ,NAS_CC_MSG_RELEASE},
    {MN_CALL_UUS1_MSG_RELEASE_COMPLETE  ,NAS_CC_MSG_RELEASE_COMPLETE},
    {MN_CALL_UUS1_MSG_PROGRESS          ,NAS_CC_MSG_PROGRESS}
};


extern    VOS_VOID MN_CALL_SetTchStatus(
    VOS_BOOL                            bAvailable
);


/*lint -save -e958 */


/*****************************************************************************
   3 函数实现
*****************************************************************************/


VOS_VOID  TAF_CALL_DeRegRelCallSsKeyEvent(
    MN_CALL_ID_T                        callId
)
{

    VOS_UINT8                           ucNumOfKeyEvt;
    VOS_UINT16                          ulLoop;

    /* 删除对应关注的事件 */
    ucNumOfKeyEvt = TAF_SDC_MIN(f_stCallSupsCmdMgmt.ucNumOfKeyEvt, (MN_CALL_MAX_SS_CMD_KEY_EVT_NUM-1));

    for (ulLoop = 0; ulLoop < ucNumOfKeyEvt;)
    {
        if (callId == f_stCallSupsCmdMgmt.astKeyEvts[ulLoop].callId)
        {
            PS_MEM_CPY(&f_stCallSupsCmdMgmt.astKeyEvts[ulLoop],
                &f_stCallSupsCmdMgmt.astKeyEvts[ulLoop + 1],
                ((ucNumOfKeyEvt - ulLoop) - 1) * sizeof(MN_CALL_SUPS_CMD_ENUM_U8_KEY_EVT_STRU));

            f_stCallSupsCmdMgmt.ucNumOfKeyEvt--;
            ucNumOfKeyEvt--;
            PS_MEM_SET(&f_stCallSupsCmdMgmt.astKeyEvts[ucNumOfKeyEvt], 0, sizeof(MN_CALL_SUPS_CMD_ENUM_U8_KEY_EVT_STRU));
        }
        else
        {
            ulLoop++;
        }
    }

}


VOS_UINT32 TAF_CALL_CountMptyCallNum(VOS_VOID)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulMptyCallNum;
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;

    ulMptyCallNum = 0;

    enMptyState = MN_CALL_MPYT_STATE_BUTT;

    for (ulLoop = 0; ulLoop < MN_CALL_MAX_NUM; ulLoop++)
    {
        MN_CALL_GetCallState((VOS_UINT8)(ulLoop + 1), &enCallState, &enMptyState);
        if (MN_CALL_IN_MPTY == enMptyState)
        {
            ulMptyCallNum++;
        }
    }

    return ulMptyCallNum;
}


VOS_UINT8 TAF_CALL_GetFirstMptyCallID(MN_CALL_ID_T  callId)
{
    VOS_UINT8                           ucLoop;
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;


    enMptyState = MN_CALL_MPYT_STATE_BUTT;

    for (ucLoop = 0; ucLoop < MN_CALL_MAX_NUM; ucLoop++)
    {
        if ((ucLoop + 1) == callId)
        {
            continue;
        }

        MN_CALL_GetCallState((ucLoop + 1), &enCallState, &enMptyState);
        if (MN_CALL_IN_MPTY == enMptyState)
        {
            return (VOS_UINT8)(ucLoop + 1);
        }
    }

    return MN_CALL_MAX_NUM;
}



VOS_VOID    TAF_CALL_SetCsCallExistFlg(
    VOS_UINT8                           ucCallExitFlg,
    MN_CALL_TYPE_ENUM_U8                enCallType
)
{
    /* 无电话，肯定无紧急呼 */
    if (VOS_FALSE == ucCallExitFlg)
    {
        TAF_SDC_SetCsCallExistFlg(VOS_FALSE);
        TAF_SDC_SetCsEccExistFlg(VOS_FALSE);
        return;
    }

    /* 有电话，根据call type设置紧急呼标记 */
    TAF_SDC_SetCsCallExistFlg(VOS_TRUE);
    
    if (MN_CALL_TYPE_EMERGENCY == enCallType)
    {
        TAF_SDC_SetCsEccExistFlg(VOS_TRUE);
    }
    else
    {
        TAF_SDC_SetCsEccExistFlg(VOS_FALSE);
    }
    
    return;
}



VOS_VOID TAF_CALL_ProcRelCallHoldRetrieveSsKeyEvent(
    MN_CALL_ID_T                        callId,
    MN_CALL_SS_PROGRESS_EVT_ENUM        enEvt
)
{
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;

    VOS_UINT8                           ucFirstMptyCallId;

    /* 获取释放呼叫的多方呼叫属性，非多方通话CALL ID，直接释放呼叫关联的事件 */
    enMptyState = MN_CALL_MPYT_STATE_BUTT;
    MN_CALL_GetCallState(callId, &enCallState, &enMptyState);
    if (MN_CALL_IN_MPTY != enMptyState)
    {
        TAF_CALL_DeRegRelCallSsKeyEvent(callId);
    }
    else
    {
        TAF_CALL_DeRegRelCallSsKeyEvent(callId);

        ucFirstMptyCallId = TAF_CALL_GetFirstMptyCallID(callId);

        if (MN_CALL_MAX_NUM != ucFirstMptyCallId)
        {
            if (MN_CALL_SS_PROG_EVT_HOLD_CNF == enEvt)
            {
                MN_CALL_RegSsKeyEvent(ucFirstMptyCallId,
                                      MN_CALL_SS_PROG_EVT_HOLD_CNF,
                                      MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

                MN_CALL_RegSsKeyEvent(ucFirstMptyCallId,
                                  MN_CALL_SS_PROG_EVT_HOLD_REJ,
                                  MN_CALL_SS_SUBSEQ_OP_RPT_FAIL);

            }
            else
            {
                MN_CALL_RegSsKeyEvent(ucFirstMptyCallId,
                                      MN_CALL_SS_PROG_EVT_RETRIEVE_CNF,
                                      MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

                MN_CALL_RegSsKeyEvent(ucFirstMptyCallId,
                                  MN_CALL_SS_PROG_EVT_RETRIEVE_REJ,
                                  MN_CALL_SS_SUBSEQ_OP_RPT_FAIL);
            }
        }
    }

    if (0 == f_stCallSupsCmdMgmt.ucNumOfKeyEvt)
    {
        f_stCallSupsCmdMgmt.bInProgress = VOS_FALSE;
        f_astCallMgmtEntities[callId - 1].stCallInfo.enSsResult = MN_CALL_SS_RES_SUCCESS;
        MN_CALL_ReportEvent(callId, MN_CALL_EVT_SS_CMD_RSLT);

        MN_CALL_ClearSsKeyEvent();
    }

    return;
}


/* 将下面3个函数从MnCallMnccProc.c中移植到此处 */

VOS_VOID MN_CALL_CleanStartLinkTime( VOS_UINT8 ucCallId)
{
    /*进行清零操作:*/
    gastCallTimerCalc[ucCallId].ulStartCallTime = 0;
}


VOS_VOID  MN_CALL_StartFluxCalculate( VOS_UINT8 ucCallId)
{

    /*获取当前系统时间并将该结构体中的当前连接开始时间置为当前系统时间:*/
    gastCallTimerCalc[ucCallId].ulStartCallTime = VOS_GetTick() / PRE_SECOND_TO_TICK ;

    /*置位该NSAPI所对应的流量结构体的NSAPI激活标志:*/
    gastCallTimerCalc[ucCallId].CallidActiveSwitch = MN_CALL_ACTIVE_SWITCH_ON;
}


VOS_VOID  MN_CALL_StopFluxCalculate( VOS_UINT8 ucCallId)
{
    VOS_UINT32                      	ulCurCallTime = 0;
    VOS_UINT32                          ulCurSysTime;               /*用于保存当前系统时间的变量*/
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;


    ulCurSysTime = 0;

    enCallState = MN_CALL_S_BUTT;
    enMptyState = MN_CALL_MPYT_STATE_BUTT;

    if (gastCallTimerCalc[ucCallId].CallidActiveSwitch == MN_CALL_ACTIVE_SWITCH_OFF )
    {
         return;
    }

    /*复位该CALL ID所对应的流量结构体的CALL ID激活标志:*/
    gastCallTimerCalc[ucCallId].CallidActiveSwitch   = MN_CALL_ACTIVE_SWITCH_OFF;

    /*获取当前系统时间:*/
    ulCurSysTime = VOS_GetTick() / PRE_SECOND_TO_TICK;


    MN_CALL_GetCallState(ucCallId, &enCallState, &enMptyState);
    /*呼叫状态为active或held才需计算连接时间*/
    if ((MN_CALL_S_ACTIVE == enCallState) || (MN_CALL_S_HELD == enCallState))
    {
        /*与结构体中开始连接时间运算，得到本次连接总时间:*/
        if ( VOS_OK != TAF_CalcTime(gastCallTimerCalc[ucCallId].ulStartCallTime,
                                    ulCurSysTime,
                                    &ulCurCallTime ) )
        {
             MN_WARN_LOG( "MN_CALL_StopFluxCalculate:WARNING:Calculate the last  link time FAIL!");
        }
        else
        {
            /*将本次连接总时间赋给"上次连接时间"字段:*/
            gastCallTimerCalc[ucCallId].ulPreCallTime = ulCurCallTime;
            /*将本次连接总时间累加至"累计连接时间"字段:*/
            gastCallTimerCalc[ucCallId].ulTotalCallTime  += ulCurCallTime;
        }
    }
    else
    {
    }

    f_astCallMgmtEntities[ucCallId-1].stCallInfo.ulPreCallTime = gastCallTimerCalc[ucCallId].ulPreCallTime;
    f_astCallMgmtEntities[ucCallId-1].stCallInfo.ulTotalCallTime = gastCallTimerCalc[ucCallId].ulTotalCallTime;

    /*将"开始连接时间"字段清零:*/
    gastCallTimerCalc[ucCallId].ulPreCallTime = 0;
    MN_CALL_CleanStartLinkTime( ucCallId );

}


VOS_VOID   MN_CALL_ResetAllCalls(MN_CALL_POWER_STATE_ENUM_U8 enPowerState)
{
    VOS_UINT32                          i;

    MN_CALL_MSG_BUFF_STRU              *pstMsgBuff = VOS_NULL_PTR;
    TAF_CS_CAUSE_ENUM_UINT32            enCause;

    pstMsgBuff = MN_CALL_GetBufferedMsg();

    if (MN_CALL_POWER_STATE_OFF == enPowerState)
    {
        /*软关机时需要判断当前是否有非IDLE态的呼叫，如果有需要上报MN_CALL_EVT_RELEASED事件*/
        for (i = 0; i < MN_CALL_MAX_NUM; i++)
        {
            if (f_astCallMgmtEntities[i].stCallInfo.enCallState != MN_CALL_S_IDLE)
            {

                /*填cause值127*/
                MN_CALL_UpdateCcCause((VOS_UINT8)(i + 1), MN_CALL_INTERWORKING_UNSPECIFIED);

                MN_INFO_LOG1("MN_CALL_ResetAllCalls: callid.", f_astCallMgmtEntities[i].stCallInfo.callId);

                /* 需要先统计通话时间，再上报RELEASED事件 */
                /* 停止统计通话时间 */
                MN_CALL_StopFluxCalculate(f_astCallMgmtEntities[i].stCallInfo.callId);

                MN_CALL_ReportEvent(f_astCallMgmtEntities[i].stCallInfo.callId,
                                    MN_CALL_EVT_RELEASED);

                TAF_CALL_ProcCallStatusFail(f_astCallMgmtEntities[i].stCallInfo.callId, f_astCallMgmtEntities[i].stCallInfo.enCallState);

                if ((VOS_TRUE == pstMsgBuff->bitOpBufferedSetupMsg)
                 && (pstMsgBuff->stBufferedSetupMsg.ucCallId == f_astCallMgmtEntities[i].stCallInfo.callId))
                {
                    MN_CALL_ClearBufferedMsg();
                    TAF_CALL_StopAllRedialTimers(pstMsgBuff->stBufferedSetupMsg.ucCallId);
                }

#if (FEATURE_ON == FEATURE_PTM)
                /* 记录CS呼叫异常log */
                MN_CALL_CsCallErrRecord(f_astCallMgmtEntities[i].stCallInfo.callId, TAF_CS_CAUSE_POWER_OFF);
#endif

                /* 电话挂断时勾出相应的事件，第三个参数不能是空指针，第四个参数不能是0，否则事件报不上去 */
                enCause = TAF_CS_CAUSE_POWER_OFF;

                if(MN_CALL_DIR_MO == f_astCallMgmtEntities[i].stCallInfo.enCallDir)
                {
                    NAS_EventReport(WUEPS_PID_TAF, NAS_OM_EVENT_CC_MO_DISCONNECT,
                                    &enCause, sizeof(TAF_CS_CAUSE_ENUM_UINT32));
                }
                else
                {
                    NAS_EventReport(WUEPS_PID_TAF, NAS_OM_EVENT_CC_MT_DISCONNECT,
                                    &enCause, sizeof(TAF_CS_CAUSE_ENUM_UINT32));
                }
            }
        }

        /*清f_stWaitSendAlert全局变量*/
        MN_CALL_SetWaitSendAlertStatus(VOS_FALSE, 0);

        /* 所有呼叫都RELEASED后，上报所有呼叫都已RELEASED */
        MN_CALL_ReportEvent(f_astCallMgmtEntities[0].stCallInfo.callId,
                            MN_CALL_EVT_ALL_RELEASED);
        
        TAF_CALL_SetCsCallExistFlg(VOS_FALSE, MN_CALL_TYPE_BUTT);
        

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
        /* 给MTC模块上报当前CS域业务状态 */
        TAF_SendMtcCsSrvInfoInd();
#endif

        TAF_CALL_ResetDtmfCtx(TAF_CS_CAUSE_POWER_OFF);

     }
     else
     {
     }

    /*
    将所有呼叫实体置为未使用的,
    将补充业务操作管理结构设为无操作正在进行
    将补充业务操作管理结构中的关注事件个数置为0
    */
    for (i = 0; i < MN_CALL_MAX_NUM; i++)
    {
        f_astCallMgmtEntities[i].bUsed = VOS_FALSE;
        f_astCallMgmtEntities[i].stCallInfo.enCallState = MN_CALL_S_IDLE;
        f_astCallMgmtEntities[i].stCallInfo.clientId = MN_CLIENT_ALL;
    }

    f_stCallSupsCmdMgmt.bInProgress = VOS_FALSE;
    f_stCallSupsCmdMgmt.ucInvokeId = 0;
    f_stCallSupsCmdMgmt.ucNumOfKeyEvt = 0;

    for ( i = 0 ; i < MN_CALL_MAX_INVOKE_NUM; i++ )
    {
        MN_CALL_InvokeId_Free((VOS_UINT8)i);
    }

#if (FEATURE_ON == FEATURE_HUAWEI_VP)
    MN_CALL_VoicePreferSendRabmVoiceCallIndMsg(VOS_FALSE);
#endif
}



VOS_UINT32 MN_CALL_AllocCallId(
    MN_CALL_ID_T                        *pCallId
)
{
    VOS_UINT16                          i;

    (VOS_VOID)VOS_TaskLock();

    for (i = 0; i < MN_CALL_MAX_NUM; i++)
    {
        /* 如果有未分配的实体，返回的Call id 的值为实体数组下标值加1 */
        if (VOS_FALSE == f_astCallMgmtEntities[i].bUsed)
        {
            *pCallId = (VOS_UINT8)i + 1;
            f_astCallMgmtEntities[i].bUsed = VOS_TRUE;
            f_astCallMgmtEntities[i].stCallInfo.enCallState = MN_CALL_S_IDLE;

            f_astCallMgmtEntities[i].stCallInfo.enCallSubState = TAF_CALL_SUB_STATE_NULL;

            (VOS_VOID)VOS_TaskUnlock();
            return  VOS_OK;
        }

    }

    (VOS_VOID)VOS_TaskUnlock();
    return VOS_ERR;

}


VOS_VOID   MN_CALL_FreeCallId(
    MN_CALL_ID_T                        callId
)
{
    VOS_UINT32                          i;

    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_FreeCallId: callId error!");
        return;
    }

    (VOS_VOID)VOS_TaskLock();

    /* 将对应的呼叫实体的值清0 */
    PS_MEM_SET(&f_astCallMgmtEntities[callId - 1], 0, sizeof(MN_CALL_MGMT_STRU));
    f_astCallMgmtEntities[callId - 1].stCallInfo.enCallState = MN_CALL_S_IDLE;
    f_astCallMgmtEntities[callId - 1].stCallInfo.clientId = MN_CLIENT_ALL;

    f_astCallMgmtEntities[callId - 1].stCallInfo.stDiscDir.ucDiscCallFlag = VOS_FALSE;

    /* 清除呼叫子状态为null */
    TAF_CALL_SetCallSubState(callId, TAF_CALL_SUB_STATE_NULL);

    (VOS_VOID)VOS_TaskUnlock();

    /*遍历所有呼叫控制实体*/
    for (i = 0; i < MN_CALL_MAX_NUM; i++)
    {
        if ((VOS_TRUE == f_astCallMgmtEntities[i].bUsed)
         && (MN_CALL_S_IDLE != f_astCallMgmtEntities[i].stCallInfo.enCallState))

        {
            break;
        }
    }

    if (MN_CALL_MAX_NUM == i)
    {
        TAF_CALL_SetCsCallExistFlg(VOS_FALSE, MN_CALL_TYPE_BUTT);

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
        /* 给MTC模块上报当前CS域业务状态 */
        TAF_SendMtcCsSrvInfoInd();
#endif
    }

#if (FEATURE_ON == FEATURE_HUAWEI_VP)
    MN_CALl_VoicePreferJudgeVoiceCallExist();
#endif
}



VOS_BOOL   MN_CALL_IsAllowToMakeNewCall(
    MN_CALL_ID_T                        callId,
    MN_CALL_DIR_ENUM_U8                 enCallDir
)
{
    VOS_UINT16                          i;


    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_IsAllowToMakeNewCall: callId error!");
        return VOS_FALSE;
    }

    /* CallId对应实体未被使用，则返回 */
    if ( VOS_FALSE == f_astCallMgmtEntities[callId - 1].bUsed )
    {
        return VOS_FALSE;
    }

    if ( MN_CALL_DIR_MO == enCallDir )
    {
        /* 主叫CallId对应实体的呼叫状态不为IDLE */
        if ( MN_CALL_S_IDLE != f_astCallMgmtEntities[callId - 1].stCallInfo.enCallState )
        {
            return VOS_FALSE;
        }
    }
    else
    {
        /* 被叫CallId对应实体的呼叫状态不为INCOMING或WAITING */
        if (( MN_CALL_S_INCOMING != f_astCallMgmtEntities[callId - 1].stCallInfo.enCallState )
          &&( MN_CALL_S_WAITING != f_astCallMgmtEntities[callId - 1].stCallInfo.enCallState ))
        {
            return VOS_FALSE;
        }
    }

    /*其它所有呼叫实体,实体被使用且状态不是HELD或IDLE */
    for (i = 0; i < MN_CALL_MAX_NUM; i++)
    {
        if ( i == (callId - 1) )
        {
            continue;
        }

        if (( VOS_TRUE == f_astCallMgmtEntities[i].bUsed)
          &&( MN_CALL_S_IDLE != f_astCallMgmtEntities[i].stCallInfo.enCallState )
          &&( MN_CALL_S_HELD != f_astCallMgmtEntities[i].stCallInfo.enCallState ))
        {
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}


VOS_VOID  MN_CALL_CreateMoCallEntity(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId,
    MN_CALL_ORIG_PARAM_STRU            *pstOrigParam
)
{
    if (( callId > MN_CALL_MAX_NUM )
     || ( callId == 0 ))
    {
        MN_WARN_LOG("MN_CALL_CreateMoCallEntity: Invalid Msg Type");
        return;
    }

    /* 按照输入参数填写CallId对应呼叫实体中的CallInfo内容 */
    /* 对于主叫而言,由于CC实体还未创建, CC实体中的Ti值被忽略, 等网侧回复上报时再记录 */
    PS_MEM_SET(&f_astCallMgmtEntities[callId - 1],
               0,
               sizeof(f_astCallMgmtEntities[callId - 1]));

    f_astCallMgmtEntities[callId - 1].bUsed                 = VOS_TRUE;
    f_astCallMgmtEntities[callId - 1].stCallInfo.clientId   = clientId;
    f_astCallMgmtEntities[callId - 1].stCallInfo.opId       = opId;
    f_astCallMgmtEntities[callId - 1].stCallInfo.callId     = callId;
    f_astCallMgmtEntities[callId - 1].stCallInfo.enCallType = pstOrigParam->enCallType;
    f_astCallMgmtEntities[callId - 1].stCallInfo.enCallMode = pstOrigParam->enCallMode;
    f_astCallMgmtEntities[callId - 1].stCallInfo.enCallDir  = MN_CALL_DIR_MO;
    f_astCallMgmtEntities[callId - 1].enClirCfg             = pstOrigParam->enClirCfg;

    /* 语音呼叫域信息 */
    f_astCallMgmtEntities[callId - 1].stCallInfo.enVoiceDomain = TAF_CALL_VOICE_DOMAIN_3GPP;                                  /* VOICE DOMAIN */

    PS_MEM_CPY(&f_astCallMgmtEntities[callId - 1].stCugCfg,
               &pstOrigParam->stCugCfg,
               sizeof(f_astCallMgmtEntities[callId - 1].stCugCfg));

    PS_MEM_CPY(&(f_astCallMgmtEntities[callId - 1].stCallInfo.stDataCfgInfo),
               &pstOrigParam->stDataCfg,
               sizeof(MN_CALL_CS_DATA_CFG_STRU));

    PS_MEM_CPY(&f_astCallMgmtEntities[callId - 1].stCallInfo.stCalledNumber,
               &pstOrigParam->stDialNumber,
               sizeof(pstOrigParam->stDialNumber));

    /* 将CallInfo中的转移号码和连接号码中的长度字段都设置为0 */
    f_astCallMgmtEntities[callId - 1].stCallInfo.stRedirectNumber.ucNumLen = 0;
    f_astCallMgmtEntities[callId - 1].stCallInfo.stConnectNumber.ucNumLen = 0;

    PS_MEM_CPY(&f_astCallMgmtEntities[callId - 1].stCallInfo.stCalledSubAddr,
               &pstOrigParam->stSubaddr,
               sizeof(MN_CALL_SUBADDR_STRU));


    TAF_CALL_SetCsCallExistFlg(VOS_TRUE, f_astCallMgmtEntities[callId - 1].stCallInfo.enCallType);

    MN_CALL_UpdateCallReleaseFlag(callId, VOS_FALSE);

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    /* 给MTC模块上报当前CS域业务状态 */
    TAF_SendMtcCsSrvInfoInd();
#endif

    return;
}

#if (FEATURE_ON == FEATURE_ECALL)

VOS_UINT8 TAF_CALL_IsCallTypeEcall(MN_CALL_ID_T ucCallId)
{
    if ( (ucCallId == 0) || ( ucCallId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CALL_IsCallTypeEcall: ucCallId is illegal!");
        return VOS_FALSE;
    }

    if ((MN_CALL_TYPE_MIEC         == (f_astCallMgmtEntities[ucCallId-1].stCallInfo.enCallType))
     || (MN_CALL_TYPE_AIEC         == (f_astCallMgmtEntities[ucCallId-1].stCallInfo.enCallType))
     || (MN_CALL_TYPE_TEST         == (f_astCallMgmtEntities[ucCallId-1].stCallInfo.enCallType))
     || (MN_CALL_TYPE_RECFGURATION == (f_astCallMgmtEntities[ucCallId-1].stCallInfo.enCallType))
     || (MN_CALL_TYPE_PSAP_ECALL   == (f_astCallMgmtEntities[ucCallId-1].stCallInfo.enCallType)))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
#endif


VOS_UINT8 TAF_CALL_IsCallTypeEmgencyCall(MN_CALL_ID_T ucCallId)
{
    if ( (ucCallId == 0) || ( ucCallId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CALL_IsCallTypeEcall: ucCallId is illegal!");
        return VOS_FALSE;
    }

    if ((MN_CALL_TYPE_EMERGENCY == f_astCallMgmtEntities[ucCallId-1].stCallInfo.enCallType)
#if (FEATURE_ON == FEATURE_ECALL)
     || (MN_CALL_TYPE_MIEC      == f_astCallMgmtEntities[ucCallId-1].stCallInfo.enCallType)
     || (MN_CALL_TYPE_AIEC      == f_astCallMgmtEntities[ucCallId-1].stCallInfo.enCallType)
#endif
       )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_VOID TAF_CALL_UpdateCallInfo(
    MN_CALL_ID_T                        ucCallId,
    MN_CALL_INFO_STRU                  *pstCallInfo
)
{
    if ( (ucCallId == 0) || ( ucCallId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CALL_UpdateCallInfo: ucCallId is illegal!");
        return;
    }

        /* 增加主动上报相关全局变量的值 */
    PS_MEM_CPY(&(f_astCallMgmtEntities[ucCallId - 1].stCallInfo),
               pstCallInfo,
               sizeof(MN_CALL_INFO_STRU));

}


VOS_UINT32 MN_CALL_GetSpecificCallInfo(
    MN_CALL_ID_T                        CallId,
    MN_CALL_MGMT_STRU                  *pstCallInfo
)
{
    if ((CallId > MN_CALL_MAX_NUM )
     || (0 == CallId))
    {
        return VOS_ERR;
    }

    PS_MEM_CPY(pstCallInfo, &f_astCallMgmtEntities[CallId - 1], sizeof(MN_CALL_MGMT_STRU));

    return VOS_OK;
}


LOCAL VOS_VOID  MN_CALL_CcIeCallingNumToApiCallingNum(
    NAS_CC_IE_CALLING_NUM_STRU          *pstCcIeNum,
    MN_CALL_BCD_NUM_STRU                *pstNum
)
{
    PS_MEM_SET(pstNum, 0, sizeof(MN_CALL_BCD_NUM_STRU));

    if (VOS_FALSE == NAS_IE_IS_PRESENT(pstCcIeNum))
    {
        return;
    }

    pstNum->ucNumLen = (VOS_UINT8)NAS_IE_GET_BLOCK_SIZE(pstCcIeNum, BCDNum);

    pstNum->enNumType = *((VOS_UINT8*)&pstCcIeNum->Octet3);

    PS_MEM_CPY(pstNum->aucBcdNum, pstCcIeNum->BCDNum, pstNum->ucNumLen);

    return;
}


LOCAL VOS_VOID  MN_CALL_CcIeCalledNumtoApiCalledNum(
    NAS_CC_IE_CALLED_NUM_STRU          *pstCcIeNum,
    MN_CALL_CALLED_NUM_STRU            *pstNum
)
{
    PS_MEM_SET(pstNum, 0, sizeof(MN_CALL_CALLED_NUM_STRU));

    if (VOS_FALSE == NAS_IE_IS_PRESENT(pstCcIeNum))
    {
        return;
    }

    pstNum->ucNumLen = (VOS_UINT8)NAS_IE_GET_BLOCK_SIZE(pstCcIeNum, BCDNum);

    pstNum->enNumType = *((VOS_UINT8*)&pstCcIeNum->Octet3);

    PS_MEM_CPY(pstNum->aucBcdNum, pstCcIeNum->BCDNum, pstNum->ucNumLen);

    return;
}


LOCAL VOS_VOID  MN_CALL_CcIeCalledSubAddrtoApiSubAddr(
    NAS_CC_IE_CALLED_SUBADDR_STRU      *pstCcIeSubAddr,
    MN_CALL_SUBADDR_STRU               *pstSubAddr
)
{
    VOS_UINT8                           ucLen;

    PS_MEM_SET(pstSubAddr, 0, sizeof(MN_CALL_SUBADDR_STRU));

    if (VOS_FALSE == NAS_IE_IS_PRESENT(pstCcIeSubAddr))
    {
        return;
    }

    ucLen = pstCcIeSubAddr->LastOctOffset - sizeof(NAS_CC_IE_CALLED_SUBADDR_OCTET3_STRU);

    if (ucLen <= MN_CALL_MAX_SUBADDR_INFO_LEN)
    {
        pstSubAddr->IsExist         = VOS_TRUE;
        pstSubAddr->LastOctOffset   = pstCcIeSubAddr->LastOctOffset;
        pstSubAddr->Octet3          = *((VOS_UINT8*)&pstCcIeSubAddr->Octet3);

        PS_MEM_CPY(pstSubAddr->SubAddrInfo, pstCcIeSubAddr->SubAddrInfo, ucLen);
    }

    return;
}


LOCAL VOS_VOID  MN_CALL_CcIeCallingSubAddrtoApiSubAddr(
    NAS_CC_IE_CALLING_SUBADDR_STRU     *pstCcIeSubAddr,
    MN_CALL_SUBADDR_STRU               *pstSubAddr
)
{
    VOS_UINT8                           ucLen;

    PS_MEM_SET(pstSubAddr, 0, sizeof(MN_CALL_SUBADDR_STRU));

    if (VOS_FALSE == NAS_IE_IS_PRESENT(pstCcIeSubAddr))
    {
        return;
    }

    ucLen = pstCcIeSubAddr->LastOctOffset - sizeof(NAS_CC_IE_CALLING_SUBADDR_OCTET3_STRU);

    if (ucLen <= MN_CALL_MAX_SUBADDR_INFO_LEN)
    {
        pstSubAddr->IsExist         = VOS_TRUE;
        pstSubAddr->LastOctOffset   = pstCcIeSubAddr->LastOctOffset;
        pstSubAddr->Octet3          = *((VOS_UINT8*)&pstCcIeSubAddr->Octet3);

        PS_MEM_CPY(pstSubAddr->SubAddrInfo, pstCcIeSubAddr->SubAddrInfo, ucLen);
    }

    return;
}


VOS_VOID  MN_CALL_CreateMtCallEntity(
    MN_CALL_ID_T                        callId,
    VOS_UINT8                           ucTi,
    NAS_CC_MSG_SETUP_MT_STRU           *pstSetup
)
{
    MN_CALL_BCD_NUM_STRU                stCallingNum;
    MN_CALL_CALLED_NUM_STRU             stCalledNum;
    MN_CALL_SUBADDR_STRU                stSubAddr;

    /* 初始化 */
    PS_MEM_SET(&stCallingNum, 0, sizeof(stCallingNum));
    PS_MEM_SET(&stCalledNum, 0, sizeof(stCalledNum));
    PS_MEM_SET(&stSubAddr, 0, sizeof(stSubAddr));

    /* 判断callId的合法性 */
    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_CreateMtCallEntity: callId error!");
        return;
    }

    /* 按照输入参数填写CallId对应呼叫实体中的CallInfo内容 */
    f_astCallMgmtEntities[callId - 1].ulTi                  = ucTi;
    f_astCallMgmtEntities[callId - 1].bUsed                 = VOS_TRUE;
    f_astCallMgmtEntities[callId - 1].stCallInfo.clientId   = MN_CLIENT_ALL;
    f_astCallMgmtEntities[callId - 1].stCallInfo.callId     = callId;
    f_astCallMgmtEntities[callId - 1].stCallInfo.enCallType = MN_CALL_TYPE_VOICE;
    f_astCallMgmtEntities[callId - 1].stCallInfo.enCallMode = MN_CALL_MODE_SINGLE;
    f_astCallMgmtEntities[callId - 1].stCallInfo.enCallDir  = MN_CALL_DIR_MT;

    /* 语音呼叫域信息 */
    f_astCallMgmtEntities[callId - 1].stCallInfo.enVoiceDomain = TAF_CALL_VOICE_DOMAIN_3GPP;                                  /* VOICE DOMAIN */

    /* 转换主叫号码 */
    MN_CALL_CcIeCallingNumToApiCallingNum(&pstSetup->stCallingNum, &stCallingNum);
    MN_CALL_UpdateCallNumber(callId, &stCallingNum);

    /* 转换主叫子地址 */
    MN_CALL_CcIeCallingSubAddrtoApiSubAddr(&pstSetup->stCallingSubaddr, &stSubAddr);
    PS_MEM_CPY(&f_astCallMgmtEntities[callId-1].stCallInfo.stSubCallNumber,
               &stSubAddr,
               sizeof(stSubAddr));

    /* 转换被叫号码 */
    MN_CALL_CcIeCalledNumtoApiCalledNum(&pstSetup->stCalledNum, &stCalledNum);
    MN_CALL_UpdateCalledNumber(callId, &stCalledNum);

    /* 转换被叫子地址 */
    MN_CALL_CcIeCalledSubAddrtoApiSubAddr(&pstSetup->stCalledSubaddr, &stSubAddr);
    PS_MEM_CPY(&f_astCallMgmtEntities[callId-1].stCallInfo.stCalledSubAddr,
               &stSubAddr,
               sizeof(stSubAddr));

    /* 记录呼叫源信息 */
    MN_CALL_RecordCallEntityRedirectInfo(callId, pstSetup);

    PS_MEM_SET(&f_astCallMgmtEntities[callId - 1].stCallInfo.stDataCfgInfo,
               0,
               sizeof(MN_CALL_CS_DATA_CFG_INFO_STRU));


    MN_CALL_UpdateCallReleaseFlag(callId, VOS_FALSE);

    TAF_CALL_SetCsCallExistFlg(VOS_TRUE, f_astCallMgmtEntities[callId - 1].stCallInfo.enCallType);

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    /* 给MTC模块上报当前CS域业务状态 */
    TAF_SendMtcCsSrvInfoInd();
#endif

    return;
}


VOS_VOID  MN_CALL_CreateCallEntity(
    MN_CALL_ID_T                        callId,
    VOS_UINT32                          ulTi,
    MN_CLIENT_ID_T                      clientId,
    MN_CALL_TYPE_ENUM_U8                enCallType,
    MN_CALL_MODE_ENUM_U8                enCallMode,
    MN_CALL_DIR_ENUM_U8                 enCallDir,
    const MN_CALL_CS_DATA_CFG_INFO_STRU *pstDataCfgInfo,
    const MN_CALL_BCD_NUM_STRU          *pstNumber
)
{

    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_CreateCallEntity: callId error!");
        return;
    }

    /* 按照输入参数填写CallId对应呼叫实体中的CallInfo内容 */
    f_astCallMgmtEntities[callId - 1].ulTi = ulTi;
    f_astCallMgmtEntities[callId - 1].stCallInfo.clientId = clientId;
    f_astCallMgmtEntities[callId - 1].stCallInfo.callId = callId;
    f_astCallMgmtEntities[callId - 1].stCallInfo.enCallType = enCallType;
    f_astCallMgmtEntities[callId - 1].stCallInfo.enCallMode = enCallMode;
    f_astCallMgmtEntities[callId - 1].stCallInfo.enCallDir = enCallDir;

    /* 语音呼叫域信息 */
    f_astCallMgmtEntities[callId - 1].stCallInfo.enVoiceDomain = TAF_CALL_VOICE_DOMAIN_3GPP;                                  /* VOICE DOMAIN */

    if (VOS_NULL_PTR != pstDataCfgInfo)
    {
        PS_MEM_CPY(&(f_astCallMgmtEntities[callId - 1].stCallInfo.stDataCfgInfo),
                   pstDataCfgInfo,
                   sizeof(MN_CALL_CS_DATA_CFG_INFO_STRU));
    }

    if ( VOS_NULL_PTR == pstNumber )
    {
        f_astCallMgmtEntities[callId - 1].stCallInfo.stCallNumber.ucNumLen = 0;
    }
    else
    {
        f_astCallMgmtEntities[callId - 1].stCallInfo.stCallNumber = *pstNumber;
    }

    PS_MEM_SET(&f_astCallMgmtEntities[callId - 1].stCallInfo.stCalledNumber,
               0,
               sizeof(MN_CALL_CALLED_NUM_STRU));

    /* 将CallInfo中的连接号码中的长度字段设置为0 */
    f_astCallMgmtEntities[callId - 1].stCallInfo.stRedirectNumber.ucNumLen = 0;
    f_astCallMgmtEntities[callId - 1].stCallInfo.stConnectNumber.ucNumLen  = 0;

    /* 将CallInfo中的转移号码和转移号码的子地址的长度置为0 */
    f_astCallMgmtEntities[callId - 1].stCallInfo.stRedirectNumber.ucNumLen       = 0;
    f_astCallMgmtEntities[callId - 1].stCallInfo.stRedirectSubaddr.LastOctOffset = 0;
    f_astCallMgmtEntities[callId - 1].stCallInfo.stRedirectSubaddr.IsExist       = VOS_FALSE;


    MN_CALL_UpdateCallReleaseFlag(callId, VOS_FALSE);

    TAF_CALL_SetCsCallExistFlg(VOS_TRUE, f_astCallMgmtEntities[callId - 1].stCallInfo.enCallType);

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    /* 给MTC模块上报当前CS域业务状态 */
    TAF_SendMtcCsSrvInfoInd();
#endif

    return;

}



VOS_VOID  MN_CALL_DeleteCallEntity(
    MN_CALL_ID_T                        callId
)
{

    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_DeleteCallEntity: callId error!");
        return;
    }

    /* 将CallId对应的呼叫控制实体设置为未使用的 */
    f_astCallMgmtEntities[callId - 1].bUsed = VOS_FALSE;
    f_astCallMgmtEntities[callId - 1].stCallInfo.enCallState = MN_CALL_S_IDLE;
    f_astCallMgmtEntities[callId - 1].stCallInfo.clientId = MN_CLIENT_ALL;
}



VOS_UINT32 MN_CALL_GetCcTi(MN_CALL_ID_T callId)
{

    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_GetCcTi: callId error!");
        return 0;
    }

    return f_astCallMgmtEntities[callId-1].ulTi;
}



VOS_UINT32 MN_CALL_GetCcCallDir(MN_CALL_ID_T callId)
{

    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_GetCcCallDir: callId error!");
        return MN_CALL_DIR_BUTT;
    }

    return f_astCallMgmtEntities[callId-1].stCallInfo.enCallDir;
}


VOS_VOID  MN_CALL_ReportEvent(
    MN_CALL_ID_T                        callId,
    MN_CALL_EVENT_ENUM_U32              enEventType
)
{
    TAF_SDC_CURC_RPT_CTRL_STRU          *pstCurcRptCtrl           = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU   *pstUnsolicitedRptCtrl    = VOS_NULL_PTR;

    pstCurcRptCtrl          = TAF_SDC_GetCurcRptCtrl();
    pstUnsolicitedRptCtrl   = TAF_SDC_GetUnsolicitedRptCtrl();


    if ( (callId == 0)
      || ( callId > MN_CALL_MAX_NUM ))
    {
        TAF_ERROR_LOG1(WUEPS_PID_TAF, "MN_CALL_ReportEvent: callId error!", callId);
        return;
    }

    if ((MN_CALL_EVT_ALL_RELEASED != enEventType)
     && (VOS_FALSE == f_astCallMgmtEntities[callId - 1].bUsed))
    {
        TAF_ERROR_LOG2(WUEPS_PID_TAF, "MN_CALL_ReportEvent: callid or enEventType error!", callId, enEventType);
        return;
    }

    MN_INFO_LOG1("MN_CALL_ReportEvent: event.", (VOS_INT32)enEventType);

    if (VOS_FALSE == TAF_CALL_GetCallStatusControl())
    {
        /*不需要上报语音呼叫的incoming事件*/
        if ((MN_CALL_EVT_INCOMING == enEventType)
          &&(MN_CALL_TYPE_VOICE == f_astCallMgmtEntities[callId - 1].stCallInfo.enCallType))
        {

#if (FEATURE_ON == FEATURE_PTM)
            /* setup消息按协议检查失败的异常记录 */
            MN_CALL_CsMtCallFailRecord(NAS_ERR_LOG_CS_MT_CALL_CAUSE_CALL_STATE_CTRL_NOT_SUPPORT);
#endif

            return;
        }

        /*不需要上报release事件*/
        if (MN_CALL_EVT_RELEASED == enEventType)
        {
            return;
        }
    }

    /* 增加主动上报相关全局变量的值 */
    PS_MEM_CPY(f_astCallMgmtEntities[callId - 1].stCallInfo.aucCurcRptCfg,
                pstCurcRptCtrl->aucRptCfg,
                MN_CALL_RPT_CFG_MAX_SIZE);

    PS_MEM_CPY(f_astCallMgmtEntities[callId - 1].stCallInfo.aucUnsolicitedRptCfg,
                pstUnsolicitedRptCtrl->aucRptCfg,
                MN_CALL_RPT_CFG_MAX_SIZE);


    /* 对所有注册了CS域呼叫事件回调函数的Client调用回调函数 */
    MN_SendClientEvent(MN_CLIENT_ALL,
                       MN_CALLBACK_CS_CALL,
                       enEventType,
                       &f_astCallMgmtEntities[callId - 1].stCallInfo);
}



VOS_VOID  MN_CALL_UpdateClientId(
    MN_CALL_ID_T                        callId,
    MN_CLIENT_ID_T                      clientId
)
{

    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_UpdateClientId: callId error!");
        return;
    }

    f_astCallMgmtEntities[callId - 1].stCallInfo.clientId = clientId;
}



VOS_VOID  MN_CALL_UpdateCallState(
    MN_CALL_ID_T                        callId,
    MN_CALL_STATE_ENUM_U8               enCallState
)
{

    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_UpdateCallState: callId error!");
        return;
    }

    f_astCallMgmtEntities[callId - 1].stCallInfo.enCallState = enCallState;

    MN_INFO_LOG1("MN_CALL_UpdateCallState: CallState,", enCallState);
}


VOS_VOID  MN_CALL_UpdateMptyState(
    MN_CALL_ID_T                        callId,
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState
)
{

    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_UpdateMptyState: callId error!");
        return;
    }

    f_astCallMgmtEntities[callId - 1].stCallInfo.enMptyState = enMptyState;

}



MN_CALL_TYPE_ENUM_U8  MN_CALL_GetCallType(
    MN_CALL_ID_T                        callId
)
{

    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_GetCallType: callId error!");
        return MN_CALL_TYPE_BUTT;
    }

    return f_astCallMgmtEntities[callId - 1].stCallInfo.enCallType;
}



VOS_VOID  MN_CALL_UpdateCallType(
    MN_CALL_ID_T                        callId,
    MN_CALL_TYPE_ENUM_U8                enCallType
)
{

    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_UpdateCallType: callId error!");
        return;
    }

    f_astCallMgmtEntities[callId - 1].stCallInfo.enCallType = enCallType;
}



VOS_VOID  MN_CALL_UpdateCallMode(
    MN_CALL_ID_T                        callId,
    MN_CALL_MODE_ENUM_U8                enCallMode
)
{

    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_UpdateCallMode: callId error!");
        return;
    }

    f_astCallMgmtEntities[callId - 1].stCallInfo.enCallMode = enCallMode;
}



VOS_VOID  MN_CALL_UpdateDataCallCfgInfo(
    MN_CALL_ID_T                        callId,
    const MN_CALL_CS_DATA_CFG_INFO_STRU *pstDataCfgInfo
)
{

    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_UpdateRecallSupsProgress: callId error!");
        return;
    }

    f_astCallMgmtEntities[callId-1].stCallInfo.stDataCfgInfo= *pstDataCfgInfo;
}


VOS_VOID  MN_CALL_GetDataCallCfgInfo(
    MN_CALL_ID_T                        callId,
    MN_CALL_CS_DATA_CFG_INFO_STRU       *pstDataCfgInfo
)
{

    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_GetDataCallCfgInfo: callId error!");
        return;
    }

    *pstDataCfgInfo = f_astCallMgmtEntities[callId-1].stCallInfo.stDataCfgInfo;
}


VOS_VOID  MN_CALL_GetMgmtEntityInfoByCallId(
    MN_CALL_ID_T                        callId,
    MN_CALL_MGMT_STRU                   *pstMgmtEntity
)
{

    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_GetMgmtEntityInfoByCallId: callId error!");
        return;
    }

    *pstMgmtEntity = f_astCallMgmtEntities[callId-1];
}


VOS_VOID  MN_CALL_GetCallInfoByCallId(
    MN_CALL_ID_T                        callId,
    MN_CALL_INFO_STRU                   *pstCallInfo
)
{

    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_GetCallInfoByCallId: callId error!");
        return;
    }

    *pstCallInfo = f_astCallMgmtEntities[callId-1].stCallInfo;
}


VOS_VOID  MN_CALL_UpdateRedirNumber(
    MN_CALL_ID_T                        callId,
    const MN_CALL_BCD_NUM_STRU          *pstRedirNumber
)
{

    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_UpdateRedirNumber: callId error!");
        return;
    }

    f_astCallMgmtEntities[callId-1].stCallInfo.stRedirectNumber = *pstRedirNumber;
}



VOS_VOID  MN_CALL_UpdateConnNumber(
    MN_CALL_ID_T                        callId,
    const MN_CALL_BCD_NUM_STRU          *pstConnNumber
)
{

    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_UpdateConnNumber: callId error!");
        return;
    }

    f_astCallMgmtEntities[callId-1].stCallInfo.stConnectNumber = *pstConnNumber;
}



VOS_VOID  MN_CALL_UpdateCallNumber(
    MN_CALL_ID_T                        callId,
    const MN_CALL_BCD_NUM_STRU          *pstCallNumber
)
{

    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_UpdateCallNumber: callId error!");
        return;
    }


    f_astCallMgmtEntities[callId-1].stCallInfo.stCallNumber = *pstCallNumber;
}


VOS_VOID  MN_CALL_UpdateCalledNumber(
    MN_CALL_ID_T                        callId,
    const MN_CALL_CALLED_NUM_STRU      *pstCalledNumber
)
{
    if ( (0 == callId) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_UpdateCalledNumber: callId error!");
        return;
    }

    PS_MEM_CPY(&f_astCallMgmtEntities[callId-1].stCallInfo.stCalledNumber,
               pstCalledNumber,
               sizeof(MN_CALL_CALLED_NUM_STRU));
    return;
}






#if 0

VOS_VOID  MN_CALL_UpdateSsCmd(
    MN_CALL_ID_T       callId,
    MN_CALL_SUPS_CMD_ENUM_U8     SsCmd,
    MN_CALL_SS_RESULT_ENUM_U8  SsResult
);
#endif


VOS_VOID  MN_CALL_UpdateSsNotify(
    MN_CALL_ID_T                        callId,
    const MN_CALL_SS_NOTIFY_STRU        *pstSsInfo
)
{

    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_UpdateSsNotify: callId error!");
        return;
    }

    f_astCallMgmtEntities[callId-1].stCallInfo.stSsNotify = *pstSsInfo;

    MN_INFO_LOG1("MN_CALL_UpdateSsNotify: enCode.", pstSsInfo->enCode);
}



VOS_VOID  MN_CALL_UpdateCcCause(
    MN_CALL_ID_T                        callId,
    NAS_CC_CAUSE_VALUE_ENUM_U32         enCcCause
)
{

    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_UpdateCcCause: callId error!");
        return;
    }

    f_astCallMgmtEntities[callId-1].stCallInfo.enCause = enCcCause;
}


TAF_CS_CAUSE_ENUM_UINT32  MN_CALL_GetCsCause(
    MN_CALL_ID_T                        callId
)
{
    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_GetCsCause: callId error!");
        return TAF_CS_CAUSE_SUCCESS;
    }

    return f_astCallMgmtEntities[callId-1].stCallInfo.enCause;
}


VOS_VOID  MN_CALL_UpdateNoCliCause(
    MN_CALL_ID_T                        callId,
    MN_CALL_NO_CLI_CAUSE_ENUM_U8        enNoCliCause
)
{

    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_UpdateNoCliCause: callId error!");
        return;
    }

    f_astCallMgmtEntities[callId-1].stCallInfo.enNoCliCause = enNoCliCause;
}



VOS_VOID  MN_CALL_UpdateRabId(
    MN_CALL_ID_T                        callId,
    VOS_UINT8                           ucRabId
)
{

    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_UpdateRabId: callId error!");
        return;
    }

    f_astCallMgmtEntities[callId - 1].stCallInfo.ucRabId = ucRabId;
}



VOS_VOID  MN_CALL_UpdateTi(
    MN_CALL_ID_T                        callId,
    VOS_UINT8                           ucTi
)
{

    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_UpdateTi: callId error!");
        return;
    }

    f_astCallMgmtEntities[callId - 1].ulTi = ucTi;
}


VOS_UINT8 TAF_CALL_GetSrvccLocalAlertedFlagByCallId(
    MN_CALL_ID_T                        callId
)
{
    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_GetCallState: callId error!");
        return VOS_FALSE;
    }

    return f_astCallMgmtEntities[callId - 1].ucSrvccLocalAlertedFlag;
}


VOS_VOID TAF_CALL_SetSrvccLocalAlertedFlagByCallId(
    MN_CALL_ID_T                        callId,
    VOS_UINT8                           ucSrvccLocalAlertedFlag
)
{
    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_GetCallState: callId error!");
        return;
    }

    f_astCallMgmtEntities[callId - 1].ucSrvccLocalAlertedFlag = ucSrvccLocalAlertedFlag;
}


VOS_VOID  MN_CALL_GetCallState(
    MN_CALL_ID_T                        callId,
    MN_CALL_STATE_ENUM_U8               *penCallState,
    MN_CALL_MPTY_STATE_ENUM_U8          *penMptyState
)
{

    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_GetCallState: callId error!");
        return;
    }


    *penCallState = f_astCallMgmtEntities[callId - 1].stCallInfo.enCallState;
    *penMptyState = f_astCallMgmtEntities[callId - 1].stCallInfo.enMptyState;
}


TAF_CALL_SUB_STATE_ENUM_UINT8 TAF_CALL_GetCallSubState(
    MN_CALL_ID_T                        callId
)
{
    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CALL_GetCallSubState: callId error!");
        return TAF_CALL_SUB_STATE_NULL;
    }

    return f_astCallMgmtEntities[callId - 1].stCallInfo.enCallSubState;
}


VOS_VOID TAF_CALL_SetCallSubState(
    MN_CALL_ID_T                        callId,
    TAF_CALL_SUB_STATE_ENUM_UINT8       enCallSubState
)
{
    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CALL_SetCallSubState: callId error!");
        return;
    }

    f_astCallMgmtEntities[callId - 1].stCallInfo.enCallSubState = enCallSubState;
}



VOS_VOID  MN_CALL_GetCallsByState(
    MN_CALL_STATE_ENUM_U8               enCallState,
    VOS_UINT32                          *pulNumOfCalls,
    MN_CALL_ID_T                        *pCallIds
)
{
    VOS_UINT16                          i;

    *pulNumOfCalls = 0;

    for (i = 0; i < MN_CALL_MAX_NUM; i++)
    {
        if (enCallState == f_astCallMgmtEntities[i].stCallInfo.enCallState)
        {
            /*lint -e961*/
            *pCallIds++ = (VOS_UINT8)i + 1;
            /*lint +e961*/
            (*pulNumOfCalls)++;
        }
    }
}




VOS_VOID  MN_CALL_GetNotIdleStateCalls(
    VOS_UINT32                          *pulNumOfCalls,
    MN_CALL_ID_T                        *pCallIds
)
{
    VOS_UINT16                          i;

    *pulNumOfCalls = 0;

    for (i = 0; i < MN_CALL_MAX_NUM; i++)
    {
        if (MN_CALL_S_IDLE != f_astCallMgmtEntities[i].stCallInfo.enCallState)
        {
            /*lint -e961*/
            *pCallIds++ = (VOS_UINT8)i + 1;
            /*lint +e961*/
            (*pulNumOfCalls)++;
        }
    }
}


VOS_VOID  MN_CALL_GetCallsByMptyState(
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState,
    VOS_UINT32                          *pulNumOfCalls,
    MN_CALL_ID_T                        *pCallIds
)
{
    VOS_UINT16                          i;

    *pulNumOfCalls = 0;

    for (i = 0; i < MN_CALL_MAX_NUM; i++)
    {
    if (enMptyState == f_astCallMgmtEntities[i].stCallInfo.enMptyState)
        {
            /*lint -e961*/
            *pCallIds++ = (VOS_UINT8)i + 1;
            /*lint +e961*/
            (*pulNumOfCalls)++;
        }
    }

}



VOS_VOID  MN_CALL_RegSsKeyEvent(
    MN_CALL_ID_T                        callId,
    MN_CALL_SS_PROGRESS_EVT_ENUM        enEvt,
    MN_CALL_SS_SUBSEQ_OP_ENUM           enSubseqOp
)
{
    VOS_UINT8   ucNumOfKeyEvt = f_stCallSupsCmdMgmt.ucNumOfKeyEvt;

    if (ucNumOfKeyEvt >= MN_CALL_MAX_SS_CMD_KEY_EVT_NUM)
    {
        MN_WARN_LOG("MN_CALL_RegSsKeyEvent: NumOfKeyEvt beyond");
        return;
    }

    /* 添加一个关注事件, 根据输入参数填写事件内容 */
    f_stCallSupsCmdMgmt.astKeyEvts[ucNumOfKeyEvt].callId = callId;
    f_stCallSupsCmdMgmt.astKeyEvts[ucNumOfKeyEvt].enEvt = enEvt;
    f_stCallSupsCmdMgmt.astKeyEvts[ucNumOfKeyEvt].enSubseqOp = enSubseqOp;

    f_stCallSupsCmdMgmt.ucNumOfKeyEvt++;


}


VOS_VOID  MN_CALL_DeRegSsKeyEvent(
    MN_CALL_ID_T                        callId,
    MN_CALL_SS_PROGRESS_EVT_ENUM        enEvt
)
{

    VOS_UINT8       ucNumOfKeyEvt = f_stCallSupsCmdMgmt.ucNumOfKeyEvt;
    VOS_UINT16      i;

    MN_CALL_ASSERT ( ucNumOfKeyEvt != 0 );

    /* 删除对应关注的事件 */
    for (i = 0; i < ucNumOfKeyEvt; i++)
    {
        if ((callId == f_stCallSupsCmdMgmt.astKeyEvts[i].callId)
           &&(enEvt == f_stCallSupsCmdMgmt.astKeyEvts[i].enEvt ))
        {
            break;
        }
    }

    if (i != ucNumOfKeyEvt)
    {
        PS_MEM_CPY(&f_stCallSupsCmdMgmt.astKeyEvts[i],
                   &f_stCallSupsCmdMgmt.astKeyEvts[i+1],
                   ((ucNumOfKeyEvt - i) - 1) * sizeof(MN_CALL_SUPS_CMD_ENUM_U8_KEY_EVT_STRU));
        f_stCallSupsCmdMgmt.ucNumOfKeyEvt--;
    }



}



VOS_VOID  MN_CALL_ClearSsKeyEvent(VOS_VOID)
{
    f_stCallSupsCmdMgmt.ucNumOfKeyEvt = 0;
}



VOS_VOID  MN_CALL_BeginCallSupsCmdProgress(
    MN_CLIENT_ID_T                      clientId,
    MN_CALL_SUPS_CMD_ENUM_U8            enCallSupsCmd
)
{
    /* 将补充业务管理结构中的bInProgress标志置为TRUE
       将输入的ClientId和enCallMgmtCmd记录到补充业务管理结构中 */
    f_stCallSupsCmdMgmt.bInProgress = VOS_TRUE;
    f_stCallSupsCmdMgmt.enCallSupsCmd = enCallSupsCmd;
    f_stCallSupsCmdMgmt.clientId = clientId;
}



VOS_BOOL  MN_CALL_IsCallSupsCmdInProgress(VOS_VOID)
{
    return  f_stCallSupsCmdMgmt.bInProgress;
}



VOS_VOID  MN_CALL_UpdateCallSupsProgress(
    MN_CALL_ID_T                        callId,
    MN_CALL_SS_PROGRESS_EVT_ENUM        enEvt,
    VOS_UINT32                          ulErrno
)
{
    VOS_UINT16                          i;
    VOS_BOOL                            bOpCmplt = VOS_FALSE;
    VOS_UINT32                          ulNumOfCalls;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;


    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_UpdateCallSupsProgress: callId error!");
        return;
    }

    PS_MEM_SET(aCallIds, 0x00, sizeof(aCallIds));


    MN_INFO_LOG3("MN_CALL_UpdateCallSupsProgress: callId, event, ulErrno", callId, (VOS_INT32)enEvt, (VOS_INT32)ulErrno);

    /* 判断是否已经存在有呼叫相关补充业务 */
    if (VOS_FALSE == MN_CALL_IsCallSupsCmdInProgress())
    {
        MN_WARN_LOG("MN_CALL_UpdateCallSupsProgress: No Cmd In Progress");
        return;
    }

    /* 在已注册的关注事件中寻找与输入的CallId和enEvt匹配的事件 */
    for (i = 0; i < f_stCallSupsCmdMgmt.ucNumOfKeyEvt; i++)
    {
        if (( callId == f_stCallSupsCmdMgmt.astKeyEvts[i].callId )
          &&( enEvt == f_stCallSupsCmdMgmt.astKeyEvts[i].enEvt ))
        {
            break;
        }
    }

    if ( i == f_stCallSupsCmdMgmt.ucNumOfKeyEvt )
    {
        MN_NORM_LOG("MN_CALL_UpdateCallSupsProgress: No Key Evt");
        return;
    }

    MN_INFO_LOG1("MN_CALL_UpdateCallSupsProgress: SubseqOp, ", f_stCallSupsCmdMgmt.astKeyEvts[i].enSubseqOp);

    switch(f_stCallSupsCmdMgmt.astKeyEvts[i].enSubseqOp)
    {
        case MN_CALL_SS_SUBSEQ_OP_RPT_SUCC:
            f_astCallMgmtEntities[callId - 1].stCallInfo.enSsResult = MN_CALL_SS_RES_SUCCESS;
            bOpCmplt = VOS_TRUE;
            break;

        case MN_CALL_SS_SUBSEQ_OP_RPT_FAIL:
            f_astCallMgmtEntities[callId - 1].stCallInfo.enSsResult = MN_CALL_SS_RES_FAIL;
            f_astCallMgmtEntities[callId - 1].stCallInfo.enSsErrCode = (VOS_UINT8)ulErrno;
            bOpCmplt = VOS_TRUE;
            break;

        case MN_CALL_SS_SUBSEQ_OP_ACCPT_OTH:
            MN_CALL_GetCallsByState(MN_CALL_S_WAITING, &ulNumOfCalls, aCallIds);
            if (0 != ulNumOfCalls)
            {
                /* 处理HOLD_CNF或REL事件后续接听另一路电话，需要去注册另一个事件 */
                if (MN_CALL_SS_PROG_EVT_HOLD_CNF == enEvt)
                {
                    MN_CALL_DeRegSsKeyEvent(callId, MN_CALL_SS_PROG_EVT_REL);
                }

                if (MN_CALL_SS_PROG_EVT_REL == enEvt)
                {
                    MN_CALL_DeRegSsKeyEvent(callId, MN_CALL_SS_PROG_EVT_HOLD_CNF);
                }

                MN_INFO_LOG2("MN_CALL_UpdateCallSupsProgress: accept other: waiting, NumOfCalls, callId",(VOS_INT32)ulNumOfCalls, aCallIds[0]);
                /*有正在等待的呼叫, 接听该呼叫*/
                MN_CALL_CallAnswerReqProc(f_stCallSupsCmdMgmt.clientId,
                                          f_stCallSupsCmdMgmt.opId,
                                          aCallIds[0],
                                          VOS_NULL_PTR);

                /* 停止MN_CALL_TID_RING定时器 */
                MN_CALL_StopTimer(MN_CALL_TID_RING);

                /* 更新该呼叫的Client信息 */
                MN_CALL_UpdateClientId(aCallIds[0], f_stCallSupsCmdMgmt.clientId);

                /* 关注该呼叫的连接建立成功事件, 后续操作为上报操作成功 */
                MN_CALL_RegSsKeyEvent(aCallIds[0],
                                      MN_CALL_SS_PROG_EVT_SETUP_COMPL,
                                      MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);
                /* 关注该呼叫的挂断完成事件, 后续操作为上报操作失败 */
                MN_CALL_RegSsKeyEvent(aCallIds[0],
                                      MN_CALL_SS_PROG_EVT_REL,
                                      MN_CALL_SS_SUBSEQ_OP_RPT_FAIL);
                break;
            }

            MN_CALL_GetCallsByState(MN_CALL_S_HELD, &ulNumOfCalls, aCallIds);
            if ( 0 != ulNumOfCalls )
            {
                enMptyState = MN_CALL_MPYT_STATE_BUTT;
                MN_CALL_GetCallState(aCallIds[0], &enCallState, &enMptyState);
                if ( MN_CALL_IN_MPTY == enMptyState)
                {
                    MN_INFO_LOG2("MN_CALL_UpdateCallSupsProgress: accept other: held in mpty NumOfCalls, callId",(VOS_INT32)ulNumOfCalls, aCallIds[0]);
                    /* 恢复MPTY */
                    MN_CALL_SendCcSimpleFacility(aCallIds[0],
                                                 MN_CALL_SS_RETRIEVEMPTY_OPERATION);
                }
                else
                {
                    MN_INFO_LOG2("MN_CALL_UpdateCallSupsProgress: accept other: held not in mpty NumOfCalls, callId",(VOS_INT32)ulNumOfCalls, aCallIds[0]);
                    /* 恢复该呼叫 */
                    MN_CALL_SendCcRetrieveReq(aCallIds[0]);
                }

                /* 更新该呼叫的Client信息 */
                MN_CALL_UpdateClientId(aCallIds[0], f_stCallSupsCmdMgmt.clientId);

                /* 关注该呼叫的恢复成功事件, 后续操作为上报操作成功 */
                MN_CALL_RegSsKeyEvent(aCallIds[0],
                                  MN_CALL_SS_PROG_EVT_RETRIEVE_CNF,
                                  MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);
                /* 关注该呼叫的恢复被拒绝事件, 后续操作为上报操作失败 */
                MN_CALL_RegSsKeyEvent(aCallIds[0],
                                  MN_CALL_SS_PROG_EVT_RETRIEVE_REJ,
                                  MN_CALL_SS_SUBSEQ_OP_RPT_FAIL);
                break;
            }

            f_astCallMgmtEntities[callId - 1].stCallInfo.enSsResult = MN_CALL_SS_RES_SUCCESS;
            bOpCmplt = VOS_TRUE;
            break;

        default:
            MN_NORM_LOG("MN_CALL_UpdateCallSupsProgress: wrong enSubseqOp");
            return;
    }

    if ( VOS_TRUE == bOpCmplt )
    {
        /* 补充业务操作完成 */
        MN_CALL_ReportEvent(callId, MN_CALL_EVT_SS_CMD_RSLT);
        MN_CALL_ClearSsKeyEvent();
        f_stCallSupsCmdMgmt.bInProgress = VOS_FALSE;
        MN_INFO_LOG("MN_CALL_UpdateCallSupsProgress: clear event & not in progress");
    }
    else
    {
        MN_CALL_DeRegSsKeyEvent(callId, enEvt);
        MN_CALL_ReportEvent(callId, MN_CALL_EVT_SS_CMD_PROGRESS);
        MN_INFO_LOG("MN_CALL_UpdateCallSupsProgress: DeReg event");
    }

}



VOS_VOID  MN_CALL_GetCallInfoList(
    TAF_UINT8                           *pucNumOfCalls,
    MN_CALL_INFO_STRU                   *pstCallInfos
)
{
    VOS_UINT16                          i;

    *pucNumOfCalls = 0;

    /*遍历所有呼叫控制实体*/
    for (i = 0; i < MN_CALL_MAX_NUM; i++)
    {
        if ((VOS_TRUE == f_astCallMgmtEntities[i].bUsed)
          &&(MN_CALL_S_IDLE != f_astCallMgmtEntities[i].stCallInfo.enCallState))

        {

            PS_MEM_CPY(pstCallInfos,
                       &(f_astCallMgmtEntities[i].stCallInfo),
                       sizeof(MN_CALL_INFO_STRU));
            (*pucNumOfCalls)++;
            pstCallInfos++;
        }

        /*
        if 呼叫个数大于输出缓存最多能存储的呼叫信息个数
            退出循环
        */
    }


}


VOS_BOOL  MN_CALL_TiUsedCheck(
    VOS_UINT32                          ulTi
)
{
    VOS_UINT16                          i;

    for (i = 0; i < MN_CALL_MAX_NUM; i++)
    {
        /* 如果当前的Ti隶属与某个已经存在的呼叫，返回 TRUE */
        if ((VOS_TRUE == f_astCallMgmtEntities[i].bUsed)
          &&(f_astCallMgmtEntities[i].ulTi == ulTi))
        {
            return  VOS_TRUE;
        }
    }
    return VOS_FALSE;

}



VOS_BOOL  MN_CALL_CheckNotIdleStateExist( VOS_VOID )
{
    VOS_UINT16                          i;

    for (i = 0; i < MN_CALL_MAX_NUM; i++)
    {
        /* 如果当前当前存在使用的实体 */
        if ((VOS_TRUE == f_astCallMgmtEntities[i].bUsed)
          &&(MN_CALL_S_IDLE != f_astCallMgmtEntities[i].stCallInfo.enCallState))
        {
            return  VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


VOS_BOOL  MN_CALL_CheckCallEntityExist(
    MN_CALL_ID_T                        callId
)
{

    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_CheckCallEntityExist: callId error!");
        return VOS_FALSE;
    }

    if (VOS_TRUE == f_astCallMgmtEntities[callId - 1].bUsed)
    {
        return  VOS_TRUE;
    }

    return VOS_FALSE;
}



/*****************************************************************************
 Prototype      : MN_CALL_InvokeIdAlloc()
 Description    : 分配InvokeId，此函数为原来的代码进行移植
 Input          : ucCallId: 呼叫标识
 Output         : *pInvokeId: 分配的InvokeId
 Return Value   : VOS_OK    分配成功
                : VOS_ERR 分配失败
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-08-19
    Author      : cjh
    Modification: Created function
*****************************************************************************/
VOS_INT32 MN_CALL_InvokeIdAlloc(
    VOS_UINT8                           ucCallId,
    VOS_UINT8                           *pInvokeId,
    VOS_UINT8                           ucOperateCode
)
{
    VOS_UINT8                          i;

    /* 从当前的index开始分配InvokeId */
    for (i=f_stCallSupsCmdMgmt.ucInvokeId; i<MN_CALL_MAX_INVOKE_NUM; i++)
    {
        if (VOS_FALSE == g_stCallInvokeIdTable[i].bUsed)
        {
            *pInvokeId = (VOS_UINT8)i;
            g_stCallInvokeIdTable[i].bUsed = VOS_TRUE;
            g_stCallInvokeIdTable[i].ucCallId = ucCallId;
            g_stCallInvokeIdTable[i].ucInvokeId = (VOS_UINT8)i;
            g_stCallInvokeIdTable[i].ucOperateCode = ucOperateCode;

            f_stCallSupsCmdMgmt.ucInvokeId = i+1;

            return VOS_OK;
        }
    }

    /* 翻转的情况，从0开始 */
    for(i=0; i<f_stCallSupsCmdMgmt.ucInvokeId; i++)
    {
        if( VOS_FALSE == g_stCallInvokeIdTable[i].bUsed )
        {
            *pInvokeId = (VOS_UINT8)i;
            g_stCallInvokeIdTable[i].bUsed = VOS_TRUE;
            g_stCallInvokeIdTable[i].ucCallId = ucCallId;
            g_stCallInvokeIdTable[i].ucInvokeId = (VOS_UINT8)i;
            g_stCallInvokeIdTable[i].ucOperateCode = ucOperateCode;

            f_stCallSupsCmdMgmt.ucInvokeId = i+1;

            return VOS_OK;
        }
    }

    return VOS_ERR;
}

VOS_UINT32 MN_CALL_UpdateAlsLineInfo(
    MN_CALL_ALS_LINE_NO_ENUM_U8         enAlsLine,
    VOS_BOOL                            bUpdateNvim
)
{
    MN_CALL_ALS_LINE_INFO_STRU          stAlsLineInfo;
    VOS_UINT32                          ulLength;
    VOS_UINT32                          ulGetCardImsiRslt;

    ulGetCardImsiRslt   = USIMM_API_RESULT_BUTT;

    ulLength = 0;
    PS_MEM_SET(&stAlsLineInfo,0,sizeof(stAlsLineInfo));

    if ( VOS_FALSE == bUpdateNvim )
    {
        f_enAlsLineNo = enAlsLine;
        return VOS_OK;
    }

    /* 获取IMSI号 */
    ulGetCardImsiRslt   = NAS_USIMMAPI_GetCardIMSI(stAlsLineInfo.aucMmaImsi);
    if ( USIMM_API_SUCCESS !=  ulGetCardImsiRslt)
    {
        if (VOS_TRUE == TAF_SDC_IsImsiAvailableInCurrSimStatus(TAF_SDC_GetSimStatus()))
        {

#if (FEATURE_ON == FEATURE_PTM)
            /* 记录获取卡IMSI异常log */
            TAF_SDC_GetCardImsiFailRecord(ulGetCardImsiRslt, stAlsLineInfo.aucMmaImsi);
#endif
        }

        return VOS_ERR;
    }

    stAlsLineInfo.enAlsLine = enAlsLine;

     /* 写入NVIM中*/
     (VOS_VOID)NV_GetLength(en_NV_Item_ALS_LINE_Config, &ulLength);
    if ( NV_OK != NV_Write(en_NV_Item_ALS_LINE_Config, &stAlsLineInfo, ulLength) )
    {
        return VOS_ERR;
    }

    f_enAlsLineNo = enAlsLine;

    return VOS_OK;
}



MN_CALL_ALS_LINE_NO_ENUM_U8  MN_CALL_GetAlsLineInfo( VOS_VOID )
{
    return f_enAlsLineNo;
}


VOS_VOID  MN_CALL_UpdateAlsLineNbr(
    MN_CALL_ID_T                        callId,
    MN_CALL_ALS_LINE_NO_ENUM_U8         enAlsLineNbr
)
{

    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_UpdateAlsLineNbr: callId error!");
        return;
    }

    f_astCallMgmtEntities[callId - 1].stCallInfo.enAlsLineNo = enAlsLineNbr;

    MN_INFO_LOG1("MN_CALL_UpdateAlsLineNbr: LineNumber,", enAlsLineNbr);

}

/*****************************************************************************
 Prototype      : MN_CALL_CallCtrlProcess
 Description    : 调用USIM模块提供的call control接口，发送Envelop命令给USIM模块
 Input          : pstParam - 主叫的信息，用于填写Envelop命令中的相应参数
 Output         :
 Return Value   : VOS_OK    - 操作成功
                : VOS_ERR - 操作失败
 Calls          :
 Called By      :

 History        :
  1.Date        : 2008-08-19
    Author      : huwen
    Modification: Created function
*****************************************************************************/
VOS_UINT32 MN_CALL_CallCtrlProcess(
    MN_CALL_ORIG_PARAM_STRU             *pstParam
)
{
    /* 该函数需要等待胡骏提供接口 */
    return VOS_OK;
}

/*****************************************************************************
 Prototype      : MN_CALL_SsOpCodeTransToSsEvent
 Description    : 将操作码转换成对应的事件
 Input          : sSOpCode - 操作码
 Output         : penEvent - 对应的事件
 Return Value   : VOS_OK    - 转换成功
                : VOS_ERR   - 转换失败
 Calls          :
 Called By      :

 History        :
  1.Date        : 2007-03-26
    Author      : h44270
    Modification: Created function
*****************************************************************************/
VOS_UINT32  MN_CALL_SsOpCodeTransToSsEvent(
    MN_CALL_SS_OPERATION_CODE_T         sSOpCode,
    MN_CALL_SS_PROGRESS_EVT_ENUM        *penEvent
)
{
    switch (sSOpCode)
    {
    case MN_CALL_SS_SPLITMPTY_OPERATION:
        *penEvent = MN_CALL_SS_PROG_EVT_SPLIT_MPTY_REJ;
        break;

    case MN_CALL_SS_RETRIEVEMPTY_OPERATION:
        *penEvent = MN_CALL_SS_PROG_EVT_RETRIEVE_REJ;
        break;

    case MN_CALL_SS_HOLDMPTY_OPERATION:
        *penEvent = MN_CALL_SS_PROG_EVT_HOLD_REJ;
        break;

    case MN_CALL_SS_BUILDMPTY_OPERATION:
        *penEvent = MN_CALL_SS_PROG_EVT_BUILD_MPTY_REJ;
        break;

    /* 暂不支持AOC
    case MN_CALL_SS_AOC_OPERATION:

        break;
    */

    case MN_CALL_SS_ECT_OPERATION:
        *penEvent = MN_CALL_SS_PROG_EVT_ECT_REJ;
        break;

    default:
        MN_WARN_LOG("MN_CALL_SsOpCodeTransToSsEvent: Op Code Error");
        return VOS_ERR;
    }

    return VOS_OK;
}
/*****************************************************************************
 Prototype      : MN_CALL_InCall
 Description    : 判定当前是否存在呼叫
 Input          : 无
 Output         : 无
 Return Value   : VOS_TRUE    - 存在呼叫
                : VOS_FALSE   - 不存在呼叫
 Calls          :
 Called By      :

 History        :
  1.Date        : 2007-03-26
    Author      : h44270
    Modification: Created function
*****************************************************************************/
VOS_BOOL  MN_CALL_InCall(VOS_VOID)
{
    VOS_UINT8                   i;

    for (i = 0; i < MN_CALL_MAX_NUM; i++)
    {
        if ((VOS_TRUE == f_astCallMgmtEntities[i].bUsed) &&
            (MN_CALL_S_IDLE != f_astCallMgmtEntities[i].stCallInfo.enCallState))

        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}



VOS_VOID  TAF_CALL_ProcRelCallSsKeyEvent(
    MN_CALL_ID_T                        callId
)
{
    VOS_UINT32                          i;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];
    VOS_UINT32                          ulNumOfCalls;


    /*寻找需要处理对应事件的CallID*/
    /* 在已注册的关注事件中寻找与输入的CallId和enEvt匹配的事件 */
    for (i = 0; i < f_stCallSupsCmdMgmt.ucNumOfKeyEvt; i++)
    {
        if ( callId == f_stCallSupsCmdMgmt.astKeyEvts[i].callId )
        {
            switch(f_stCallSupsCmdMgmt.astKeyEvts[i].enEvt)
            {
             case MN_CALL_SS_PROG_EVT_HOLD_CNF:

                TAF_CALL_ProcRelCallHoldRetrieveSsKeyEvent(callId, MN_CALL_SS_PROG_EVT_HOLD_CNF);
                break;

            case MN_CALL_SS_PROG_EVT_RETRIEVE_CNF:
                TAF_CALL_ProcRelCallHoldRetrieveSsKeyEvent(callId, MN_CALL_SS_PROG_EVT_RETRIEVE_CNF);
                break;

            case MN_CALL_SS_PROG_EVT_BUILD_MPTY_CNF:
                MN_CALL_UpdateCallSupsProgress(callId,
                                               MN_CALL_SS_PROG_EVT_BUILD_MPTY_REJ,
                                               MN_CALL_ERR_SS_UNSPECIFIC);
                break;

            case MN_CALL_SS_PROG_EVT_SPLIT_MPTY_CNF:
                MN_CALL_UpdateCallSupsProgress(callId,
                                               MN_CALL_SS_PROG_EVT_SPLIT_MPTY_REJ,
                                               MN_CALL_ERR_SS_UNSPECIFIC);
                break;

            case MN_CALL_SS_PROG_EVT_DEFLECT_CNF:
                MN_CALL_UpdateCallSupsProgress(callId,
                                               MN_CALL_SS_PROG_EVT_DEFLECT_REJ,
                                               MN_CALL_ERR_SS_UNSPECIFIC);
                break;

            case MN_CALL_SS_PROG_EVT_ACT_CCBS_CNF:
                MN_CALL_UpdateCallSupsProgress(callId,
                                               MN_CALL_SS_PROG_EVT_ACT_CCBS_REJ,
                                               MN_CALL_ERR_SS_UNSPECIFIC);
                break;

            case MN_CALL_SS_PROG_EVT_ECT_CNF:
                /*ECT过程有两个callId,对不同的callId注册了不同的关注事件，只需要
                清除对应callId的注册事件 */
                MN_CALL_GetNotIdleStateCalls(&ulNumOfCalls, aCallIds);
                if (2 == ulNumOfCalls)
                {
                    MN_CALL_DeRegSsKeyEvent(callId,MN_CALL_SS_PROG_EVT_ECT_CNF);
                    MN_CALL_DeRegSsKeyEvent(callId,MN_CALL_SS_PROG_EVT_ECT_REJ);
                }
                else
                {
                    MN_CALL_UpdateCallSupsProgress(callId,
                                                   MN_CALL_SS_PROG_EVT_ECT_REJ,
                                                   MN_CALL_ERR_SS_UNSPECIFIC);
                }
                break;

            default:
                break;
            }
        }
    }

}


VOS_VOID  MN_CALL_UpdateCcbsSetup(
    const NAS_CC_MSG_SETUP_MO_STRU   *pstCcbsSetup
)
{
    PS_MEM_CPY(&f_stCcbsSetup, pstCcbsSetup, sizeof(NAS_CC_MSG_SETUP_MO_STRU));
}

VOS_VOID  MN_CALL_GetCcbsSetup(
    NAS_CC_MSG_SETUP_MO_STRU   *pstCcbsSetup
)
{
    PS_MEM_CPY(pstCcbsSetup, &f_stCcbsSetup, sizeof(NAS_CC_MSG_SETUP_MO_STRU));
}


VOS_VOID MN_CALL_UpdateCcCallDir(
    MN_CALL_ID_T                        callId,
    MN_CALL_DIR_ENUM_U8                 enCallDir
)
{

    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_UpdateCcCallDir: callId error!");
        return;
    }

    f_astCallMgmtEntities[callId-1].stCallInfo.enCallDir = enCallDir;
}

VOS_VOID  MN_CALL_UpdateCcbsSupsProgress(
    MN_CALL_ID_T                        callId,
    VOS_UINT32                          ulErrno,
    MN_CALL_SS_RESULT_ENUM_U8           enSsResult
)
{

    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_UpdateCcbsSupsProgress: callId error!");
        return;
    }

    f_astCallMgmtEntities[callId - 1].stCallInfo.enSsResult = enSsResult;
    f_astCallMgmtEntities[callId - 1].stCallInfo.enSsErrCode = (VOS_UINT8)ulErrno;
    f_astCallMgmtEntities[callId - 1].stCallInfo.enCallSupsCmd
                = MN_CALL_SUPS_CMD_ACT_CCBS;
    MN_CALL_ReportEvent(callId, MN_CALL_EVT_TIME_EXPIRED);
    f_stCallSupsCmdMgmt.bInProgress = VOS_FALSE;

}


VOS_VOID  MN_CALL_UpdateRecallSupsProgress(
    MN_CALL_ID_T                        callId,
    VOS_UINT32                          ulErrno,
    MN_CALL_SS_RESULT_ENUM_U8           enSsResult
)
{

    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_UpdateRecallSupsProgress: callId error!");
        return;
    }

    f_astCallMgmtEntities[callId - 1].stCallInfo.enSsResult = enSsResult;
    f_astCallMgmtEntities[callId - 1].stCallInfo.enSsErrCode = (VOS_UINT8)ulErrno;
    f_astCallMgmtEntities[callId - 1].stCallInfo.enCallSupsCmd
            = MN_CALL_SUPS_CMD_ACT_CCBS;
    MN_CALL_ReportEvent(callId, MN_CALL_EVT_SS_CMD_RSLT);
    f_stCallSupsCmdMgmt.bInProgress = VOS_FALSE;

}



VOS_VOID  MN_CALL_UpdateRbId(
    MN_CALL_ID_T                        callId,
    VOS_UINT32                          ulRbId
)
{
    f_astCallMgmtEntities[callId - 1].bRbSet = VOS_TRUE;
    f_astCallMgmtEntities[callId - 1].ulRbId = ulRbId;

}


VOS_UINT32 MN_CALL_GetRbId(MN_CALL_ID_T callId)
{
    return f_astCallMgmtEntities[callId - 1].ulRbId;
}


VOS_VOID MN_CALL_SetVideoCallChannelOpenFlg(
    VOS_BOOL                            bVideoCallChannelOpenFlg,
    MN_CALL_ID_T                        callId
)
{
    f_astCallMgmtEntities[callId - 1].bVpChannelOpenFlg = bVideoCallChannelOpenFlg;
}


VOS_BOOL MN_CALL_GetVideoCallChannelOpenFlg(
    MN_CALL_ID_T                        callId
)
{
    return f_astCallMgmtEntities[callId - 1].bVpChannelOpenFlg;
}



VOS_UINT32 MN_CALL_ConCallMsgTypeToCcMsgType(
    MN_CALL_UUS1_MSG_TYPE_ENUM_U32      enCallMsgType,
    NAS_CC_MSG_TYPE_ENUM_U8             *penCcMsgType
)
{
    VOS_UINT32                          i;

    /* 将MNCALLAPI定义的消息类型转换为CC定义的消息类型 */
    for ( i = 0 ; i < (sizeof(f_stCallMsgType)/sizeof(MN_CALL_MATCH_MSG_TYPE_STRU)) ; i++ )
    {
        if ( enCallMsgType == f_stCallMsgType[i].enCallMsgType)
        {
            *penCcMsgType = f_stCallMsgType[i].enCcMsgType;
            return VOS_OK;
        }
    }

    return VOS_ERR;
}


VOS_UINT32 MN_CALL_ConCcMsgTypeToCallMsgType(
    NAS_CC_MSG_TYPE_ENUM_U8             enCcMsgType,
    MN_CALL_UUS1_MSG_TYPE_ENUM_U32      *penCallMsgType
)
{
    VOS_UINT32                          i;

    /* 将CC定义的消息类型转换为MNCALLAPI定义的消息类型 */
    for ( i = 0 ; i < (sizeof(f_stCallMsgType)/sizeof(MN_CALL_MATCH_MSG_TYPE_STRU)) ; i++ )
    {
        if ( enCcMsgType == f_stCallMsgType[i].enCcMsgType)
        {
            *penCallMsgType = f_stCallMsgType[i].enCallMsgType;
            return VOS_OK;
        }
    }

    return VOS_ERR;
}


VOS_VOID MN_CALL_UpdateRptUus1Info(
    MN_CALL_ID_T                        callId,
    NAS_CC_MSG_TYPE_ENUM_U8             enCcMsgType,
    NAS_CC_IE_USER_USER_STRU            *pstUserUser
)
{
    MN_CALL_ConCcUusInfoToCall(enCcMsgType,
                               pstUserUser,
                               &f_astCallMgmtEntities[callId - 1].stCallInfo.stUusInfo);

    return;
}



VOS_VOID MN_CALL_ConCcUusInfoToCall(
    NAS_CC_MSG_TYPE_ENUM_U8             enCcMsgType,
    NAS_CC_IE_USER_USER_STRU            *pstUserUser,
    MN_CALL_UUS1_INFO_STRU              *pstUus1Info
)
{
    VOS_UINT32                          ulRet;

    /* 先将CC的消息类型转换为CALL的消息类型 */
    ulRet = MN_CALL_ConCcMsgTypeToCallMsgType(enCcMsgType,
            &pstUus1Info->enMsgType);

    if ( VOS_OK != ulRet )
    {
        pstUus1Info->enMsgType = MN_CALL_UUS1_MSG_ANY;
    }

    pstUus1Info->aucUuie[MN_CALL_IEI_POS] = MN_CALL_UUS_IEI;

    pstUus1Info->aucUuie[MN_CALL_LEN_POS] = pstUserUser->LastOctOffset;

    pstUus1Info->aucUuie[MN_CALL_PD_POS]  = pstUserUser->UserUserPD;

    PS_MEM_CPY(&(pstUus1Info->aucUuie[MN_CALL_CONTENT_POS]),
               pstUserUser->UserUserInfo,
               sizeof(pstUserUser->UserUserInfo));

    return;
}



VOS_UINT32  MN_CALL_ConCallUusInfoToCc(
    MN_CALL_UUS1_MSG_TYPE_ENUM_U32      enMsgType,
    MN_CALL_UUS1_INFO_STRU              *pstUus1Info,
    NAS_CC_IE_USER_USER_STRU            *pstUuieInfo
)
{
    pstUuieInfo->IsExist = VOS_TRUE;
    pstUuieInfo->LastOctOffset = pstUus1Info->aucUuie[MN_CALL_LEN_POS];
    if ( ( MN_CALL_UUS1_MSG_SETUP  == enMsgType )
      && ( ( pstUuieInfo->LastOctOffset > MN_CALL_MAX_SETUP_UUIE_CONTEND_LEN )
        || (pstUuieInfo->LastOctOffset < MN_CALL_MIN_UUIE_CONTEND_LEN)))
    {
        return VOS_ERR;
    }
    else if ( ( pstUuieInfo->LastOctOffset > MN_CALL_MAX_OTHER_UUIE_CONTEND_LEN )
           || (pstUuieInfo->LastOctOffset < MN_CALL_MIN_UUIE_CONTEND_LEN))
    {
        return VOS_ERR;
    }
    else
    {
        ;
    }

    pstUuieInfo->UserUserPD = pstUus1Info->aucUuie[MN_CALL_PD_POS];
    if ( pstUuieInfo->LastOctOffset > 0 )
    {
        /* 此处减1的目的是由于前面PID已使用一个字节 */
        PS_MEM_CPY(pstUuieInfo->UserUserInfo,
                  (pstUus1Info->aucUuie + MN_CALL_CONTENT_POS),
                  (pstUuieInfo->LastOctOffset - MN_CALL_MIN_UUIE_CONTEND_LEN));
    }

    return VOS_OK;
}

VOS_VOID NAS_CALL_SndOutsideContextData()
{
    NAS_CALL_SDT_MSG_ST                      *pSndMsgCB     = VOS_NULL_PTR;
    NAS_CALL_OUTSIDE_RUNNING_CONTEXT_ST      *pstOutsideCtx;

    MN_CALL_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;

    /* 获取特性控制NV地址 */
    pstCustomCfgAddr                    = MN_CALL_GetCustomCfgInfo();


    pSndMsgCB = (NAS_CALL_SDT_MSG_ST *)PS_ALLOC_MSG(WUEPS_PID_TAF, sizeof(NAS_CALL_SDT_MSG_ST));

    if ( VOS_NULL_PTR == pSndMsgCB )
    {
        MN_ERR_LOG("NAS_CALL_SndOutsideContextData:ERROR: Alloc Memory Fail.");
        return;
    }

    pstOutsideCtx = &pSndMsgCB->stOutsideCtx;

    PS_MEM_CPY(pstOutsideCtx->pc_g_f_astCallMgmtEntities,f_astCallMgmtEntities,MN_CALL_MAX_NUM * sizeof(MN_CALL_MGMT_STRU));
    PS_MEM_CPY(&pstOutsideCtx->pc_g_f_stCallSupsCmdMgmt, &f_stCallSupsCmdMgmt,sizeof(MN_CALL_SUPS_CMD_ENUM_U8_MGMT_STRU));

    /*CCBS功能打开时,保留的Setup消息 */
    if (MN_CALL_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucCcbsSupportFlg)
    {
        PS_MEM_CPY(&pstOutsideCtx->pc_g_f_stCcbsSetup, &f_stCcbsSetup,sizeof(NAS_CC_MSG_SETUP_MO_STRU));
    }

    if ( MN_CALL_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucAlsSupportFlg )
    {
        pstOutsideCtx->pc_g_f_enAlsLineNo                   = f_enAlsLineNo;
    }
    pstOutsideCtx->pc_g_gucTafCallStatusControl         = TAF_CALL_GetCallStatusControl();
    pstOutsideCtx->pc_g_gucTafMultiSimCallStatusControl = TAF_CALL_GetMultiSimCallStatusControl();
    pstOutsideCtx->pc_g_g_enVpNvCfgState                = TAF_CALL_GetVpCfgState();

    pSndMsgCB->MsgHeader.ulReceiverPid   = WUEPS_PID_TAF;
    pSndMsgCB->MsgHeader.ulSenderPid     = WUEPS_PID_TAF;
    pSndMsgCB->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pSndMsgCB->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;

    pSndMsgCB->MsgHeader.ulLength  = sizeof(NAS_CALL_OUTSIDE_RUNNING_CONTEXT_ST) + 4;
    pSndMsgCB->MsgHeader.ulMsgName = EVT_NAS_CALL_OUTSIDE_RUNNING_CONTEXT_FOR_PC_REPLAY;

    DIAG_TraceReport(pSndMsgCB);
    PS_FREE_MSG(WUEPS_PID_TAF, pSndMsgCB);

    return;
}

#ifdef __PS_WIN32_RECUR__

VOS_UINT32 NAS_CALL_RestoreContextData(struct MsgCB * pMsg)
{
    NAS_CALL_SDT_MSG_ST                      *pRcvMsgCB;
    NAS_CALL_OUTSIDE_RUNNING_CONTEXT_ST      *pstOutsideCtx;
    MN_CALL_CUSTOM_CFG_INFO_STRU             *pstCustomCfgAddr;

    /* 获取特性控制NV地址 */
    pstCustomCfgAddr                    = MN_CALL_GetCustomCfgInfo();


    pRcvMsgCB     = (NAS_CALL_SDT_MSG_ST *)pMsg;

    pstOutsideCtx = &pRcvMsgCB->stOutsideCtx;

    if (EVT_NAS_CALL_OUTSIDE_RUNNING_CONTEXT_FOR_PC_REPLAY == pRcvMsgCB->MsgHeader.ulMsgName)
    {
        PS_MEM_CPY(f_astCallMgmtEntities,pstOutsideCtx->pc_g_f_astCallMgmtEntities,MN_CALL_MAX_NUM * sizeof(MN_CALL_MGMT_STRU));
        PS_MEM_CPY(&f_stCallSupsCmdMgmt,&pstOutsideCtx->pc_g_f_stCallSupsCmdMgmt,sizeof(MN_CALL_SUPS_CMD_ENUM_U8_MGMT_STRU));

        /*CCBS功能打开时,保留的Setup消息 */
        if (MN_CALL_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucCcbsSupportFlg)
        {
            PS_MEM_CPY(&f_stCcbsSetup,&pstOutsideCtx->pc_g_f_stCcbsSetup,sizeof(NAS_CC_MSG_SETUP_MO_STRU));
        }

        if ( MN_CALL_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucAlsSupportFlg)
        {
            f_enAlsLineNo                   = pstOutsideCtx->pc_g_f_enAlsLineNo;
        }
        TAF_CALL_SetCallStatusControl(pstOutsideCtx->pc_g_gucTafCallStatusControl);
        TAF_CALL_SetMultiSimCallStatusControl(pstOutsideCtx->pc_g_gucTafMultiSimCallStatusControl);
        TAF_CALL_SetVpCfgState(pstOutsideCtx->pc_g_g_enVpNvCfgState);

        TAF_LOG(WUEPS_PID_TAF, VOS_NULL, PS_LOG_LEVEL_INFO,"CALL: NAS_CALL_RestoreContextData - data is restored.");
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
#endif


VOS_VOID  MN_CALL_CallInfoReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId
)
{
    MN_CALL_INFO_QRY_CNF_STRU          *pstAppCnfMsg;
    VOS_UINT16                          usLength;
    VOS_UINT16                          i;

    /* 初始化 */
    usLength     = 0;

    pstAppCnfMsg = (MN_CALL_INFO_QRY_CNF_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF,
                                                    sizeof(MN_CALL_INFO_QRY_CNF_STRU));

    if (VOS_NULL_PTR == pstAppCnfMsg)
    {
        return;
    }
    /* 获取当前所有状态不为IDLE的呼叫信息 */
    /*遍历所有呼叫控制实体*/
    (VOS_VOID)VOS_MemSet(pstAppCnfMsg, 0x00, sizeof(MN_CALL_INFO_QRY_CNF_STRU));

    for (i = 0; i < MN_CALL_MAX_NUM; i++)
    {
        if ((VOS_TRUE == f_astCallMgmtEntities[i].bUsed)
         && (MN_CALL_S_IDLE != f_astCallMgmtEntities[i].stCallInfo.enCallState))

        {
            pstAppCnfMsg->astCallInfos[pstAppCnfMsg->ucNumOfCalls].callId      = f_astCallMgmtEntities[i].stCallInfo.callId;
            pstAppCnfMsg->astCallInfos[pstAppCnfMsg->ucNumOfCalls].enCallDir   = f_astCallMgmtEntities[i].stCallInfo.enCallDir;
            pstAppCnfMsg->astCallInfos[pstAppCnfMsg->ucNumOfCalls].enCallState = f_astCallMgmtEntities[i].stCallInfo.enCallState;
            pstAppCnfMsg->astCallInfos[pstAppCnfMsg->ucNumOfCalls].enMptyState = f_astCallMgmtEntities[i].stCallInfo.enMptyState;
            pstAppCnfMsg->astCallInfos[pstAppCnfMsg->ucNumOfCalls].enCallType  = f_astCallMgmtEntities[i].stCallInfo.enCallType;
            pstAppCnfMsg->astCallInfos[pstAppCnfMsg->ucNumOfCalls].enVoiceDomain = f_astCallMgmtEntities[i].stCallInfo.enVoiceDomain;

            PS_MEM_CPY(&(pstAppCnfMsg->astCallInfos[pstAppCnfMsg->ucNumOfCalls].stCallNumber),
                       &(f_astCallMgmtEntities[i].stCallInfo.stCallNumber),
                       sizeof(MN_CALL_BCD_NUM_STRU));

            PS_MEM_CPY(&(pstAppCnfMsg->astCallInfos[pstAppCnfMsg->ucNumOfCalls].stConnectNumber),
                       &(f_astCallMgmtEntities[i].stCallInfo.stConnectNumber),
                       sizeof(MN_CALL_BCD_NUM_STRU));

            PS_MEM_CPY(&(pstAppCnfMsg->astCallInfos[pstAppCnfMsg->ucNumOfCalls].stCalledNumber),
                       &(f_astCallMgmtEntities[i].stCallInfo.stCalledNumber),
                       sizeof(MN_CALL_CALLED_NUM_STRU));

            (pstAppCnfMsg->ucNumOfCalls)++;
        }
    }

    /* 填写事件名称 */
    pstAppCnfMsg->enEvent  = MN_CALL_EVT_CLCC_INFO;
    pstAppCnfMsg->clientId = MN_GetRealClientId(clientId, WUEPS_PID_TAF);

    /* 确定消息长度 */
    usLength = (TAF_UINT16)sizeof(MN_CALL_INFO_QRY_CNF_STRU);

    /* 通过异步消息发送给AT */
    MN_SendReportMsg(MN_CALLBACK_CS_CALL, (TAF_UINT8 *)pstAppCnfMsg, usLength);

    PS_MEM_FREE(WUEPS_PID_TAF, pstAppCnfMsg);
    return;
}



VOS_VOID  MN_CALL_GetCdur(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId
)
{
    VOS_UINT32                          ulCurCallTime = 0;
    VOS_UINT32                          ulCurSysTime;               /*用于保存当前系统时间的变量*/
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;


    enCallState     = MN_CALL_S_BUTT;
    enMptyState     = MN_CALL_MPYT_STATE_BUTT;

    ulCurSysTime    = 0;

    if (MN_CALL_ACTIVE_SWITCH_ON != gastCallTimerCalc[callId].CallidActiveSwitch)
    {
        /* 不在激活态， 输出AT_CME_INCORRECT_PARAMETERS */
        MN_WARN_LOG("MN_CALL_GetCdur: call is inactive!");

        /* 失败时只看原因值，成功时才看ulCurCallTime，所以失败时不用更新ulCurCallTime */
        f_astCallMgmtEntities[callId -1].stCallInfo.enCause      = TAF_CS_CAUSE_STATE_ERROR;

        /* 更新该呼叫的Client信息 */
        MN_SendClientEvent(clientId,
                           MN_CALLBACK_CS_CALL,
                           MN_CALL_EVT_GET_CDUR_CNF,
                           &f_astCallMgmtEntities[callId - 1].stCallInfo);

        return;
    }

    /* 获取当前系统时间: */
    ulCurSysTime = VOS_GetTick() / PRE_SECOND_TO_TICK;

    MN_CALL_GetCallState(callId, &enCallState, &enMptyState);

    if ((MN_CALL_S_ACTIVE == enCallState) || (MN_CALL_S_HELD == enCallState))
    {
        /* 与结构体中开始连接时间运算，得到通话时长: 操作失败输出AT_ERROR */
        if ( VOS_OK != TAF_CalcTime(gastCallTimerCalc[callId].ulStartCallTime,
                                    ulCurSysTime,
                                    &ulCurCallTime ) )
        {
            MN_WARN_LOG("MN_CALL_GetCdur: Calculate the last  link time FAIL!");

            f_astCallMgmtEntities[callId - 1].stCallInfo.enCause      = TAF_CS_CAUSE_UNKNOWN;

            /* 更新该呼叫的Client信息 */
            MN_SendClientEvent(clientId,
                               MN_CALLBACK_CS_CALL,
                               MN_CALL_EVT_GET_CDUR_CNF,
                               &f_astCallMgmtEntities[callId - 1].stCallInfo);

            return;
        }
    }
    else
    {
        /* 不在通话状态或通话保持状态 输出AT_ERROR */
        MN_WARN_LOG("MN_CALL_GetCdur: invalid enCallState!");

        f_astCallMgmtEntities[callId - 1].stCallInfo.enCause      = TAF_CS_CAUSE_STATE_ERROR;

        /* 更新该呼叫的Client信息 */
        MN_SendClientEvent(clientId,
                           MN_CALLBACK_CS_CALL,
                           MN_CALL_EVT_GET_CDUR_CNF,
                           &f_astCallMgmtEntities[callId -1].stCallInfo);

        return;
    }

    /* 上报应用请求确认 */

    f_astCallMgmtEntities[callId - 1].stCallInfo.ulCurCallTime = ulCurCallTime;

    f_astCallMgmtEntities[callId - 1].stCallInfo.callId        = callId;

    f_astCallMgmtEntities[callId - 1].stCallInfo.enCause       = TAF_CS_CAUSE_SUCCESS;

    /* 更新该呼叫的Client信息 */
    MN_SendClientEvent(clientId,
                       MN_CALLBACK_CS_CALL,
                       MN_CALL_EVT_GET_CDUR_CNF,
                       &f_astCallMgmtEntities[callId - 1].stCallInfo);

    MN_NORM_LOG("MN_CALL_GetCdur: get cdur normal.");

    return;
}



VOS_VOID MN_CALL_RcvTafAgentGetCallInfo(VOS_VOID)
{
    TAFAGERNT_MN_GET_CALL_INFO_CNF_STRU                    *pstCnf;
    VOS_UINT32                                              i;

    pstCnf = (TAFAGERNT_MN_GET_CALL_INFO_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF,
                                                              sizeof(TAFAGERNT_MN_GET_CALL_INFO_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstCnf)
    {
        MN_ERR_LOG("MN_CALL_RcvTafAgentGetCallInfo:alloc msg failed.");
        return;
    }

    PS_MEM_SET(pstCnf, 0x00, sizeof(TAFAGERNT_MN_GET_CALL_INFO_CNF_STRU));

    for (i = 0; i < MN_CALL_MAX_NUM; i++)
    {
        if ((VOS_TRUE == f_astCallMgmtEntities[i].bUsed)
         && (MN_CALL_S_IDLE != f_astCallMgmtEntities[i].stCallInfo.enCallState))

        {
            pstCnf->stCallInfo[pstCnf->ucNumOfCalls].callId       = f_astCallMgmtEntities[i].stCallInfo.callId;
            pstCnf->stCallInfo[pstCnf->ucNumOfCalls].enCallType   = f_astCallMgmtEntities[i].stCallInfo.enCallType;
            pstCnf->stCallInfo[pstCnf->ucNumOfCalls].enCallState  = f_astCallMgmtEntities[i].stCallInfo.enCallState;

            (pstCnf->ucNumOfCalls)++;
        }
    }

    pstCnf->ulSenderCpuId                 = VOS_LOCAL_CPUID;
    pstCnf->ulSenderPid                   = WUEPS_PID_TAF;
    pstCnf->ulReceiverCpuId               = VOS_LOCAL_CPUID;
    pstCnf->ulReceiverPid                 = ACPU_PID_TAFAGENT;
    pstCnf->ulLength                      = sizeof(TAFAGERNT_MN_GET_CALL_INFO_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstCnf->enMsgId                       = ID_TAFAGENT_MN_GET_CALL_INFO_CNF;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstCnf))
    {
        MN_ERR_LOG("TAF_APS_RcvFindCidForDialReq_PreProc:send msg failed.");

        return;
    }

    return;

}



VOS_VOID  MN_CALL_CreateStkMoCallEntity(
    MN_CALL_ID_T                        callId,
    MN_CALL_TYPE_ENUM_U8                enCallType,
    MN_APP_CALL_CALLORIG_REQ_STRU      *pstStkCallOrig
)
{
    NAS_CC_IE_BC_STRU                   stBc1CallCnf;
    MN_CALL_CS_DATA_CFG_INFO_STRU       stDataCfgInfo;
    VOS_UINT8                           ucInternalTonNumType;
    VOS_UINT8                           ucUnknownTonNumType;


    PS_MEM_SET(&stDataCfgInfo, 0x00, sizeof(stDataCfgInfo));

    ucUnknownTonNumType  = (MN_CALL_IS_EXIT | (MN_CALL_TON_UNKNOWN << 4) | MN_CALL_NPI_ISDN);
    ucInternalTonNumType = (MN_CALL_IS_EXIT | (MN_CALL_TON_INTERNATIONAL << 4) | MN_CALL_NPI_ISDN);

    /* 根据客户类型的差别分别获取下述信息: */
    /* 被叫号码 */
    /* Call Type */
    /* Call Mode */
    /* 主叫号码限制的配置 */
    /* CUG Configuration */
    /* CS DATA service configration */
    /* Call SubAddress */

    /* 按照输入参数填写CallId对应呼叫实体中的CallInfo内容 */
    /* 对于主叫而言,由于CC实体还未创建, CC实体中的Ti值被忽略, 等网侧回复上报时再记录 */
    PS_MEM_SET(&f_astCallMgmtEntities[callId - 1],
               0,
               sizeof(f_astCallMgmtEntities[callId - 1]));

    f_astCallMgmtEntities[callId - 1].bUsed                 = VOS_TRUE;
    f_astCallMgmtEntities[callId - 1].stCallInfo.clientId   = pstStkCallOrig->usClientId;
    f_astCallMgmtEntities[callId - 1].stCallInfo.opId       = pstStkCallOrig->opID;
    f_astCallMgmtEntities[callId - 1].stCallInfo.callId     = callId;

    f_astCallMgmtEntities[callId - 1].stCallInfo.enCallType = enCallType;
    f_astCallMgmtEntities[callId - 1].stCallInfo.enCallMode = MN_CALL_MODE_SINGLE;
    f_astCallMgmtEntities[callId - 1].stCallInfo.enCallDir  = MN_CALL_DIR_MO;
    f_astCallMgmtEntities[callId - 1].enClirCfg             = MN_CALL_CLIR_AS_SUBS;

    /* 语音呼叫域信息 */
    f_astCallMgmtEntities[callId - 1].stCallInfo.enVoiceDomain = TAF_CALL_VOICE_DOMAIN_3GPP;                                  /* VOICE DOMAIN */

    PS_MEM_CPY(&f_astCallMgmtEntities[callId - 1].stCallInfo.stCalledNumber,
               (MN_CALL_CALLED_NUM_STRU *)&pstStkCallOrig->stCalledAddr,
               sizeof(pstStkCallOrig->stCalledAddr));

    f_astCallMgmtEntities[callId - 1].stCallInfo.stCalledNumber.enNumType |= ucUnknownTonNumType;
    f_astCallMgmtEntities[callId - 1].stCallInfo.stCalledNumber.enNumType &= ucInternalTonNumType;

    /* 支持被叫子地址 */
    if ( ( pstStkCallOrig->stSubAddr.ucLen > 0)
       && (pstStkCallOrig->stSubAddr.ucLen < MN_CALL_MAX_SUBADDR_INFO_LEN))
    {
        f_astCallMgmtEntities[callId - 1].stCallInfo.stCalledSubAddr.IsExist = VOS_TRUE;
        f_astCallMgmtEntities[callId - 1].stCallInfo.stCalledSubAddr.LastOctOffset  = pstStkCallOrig->stSubAddr.ucLen;
        f_astCallMgmtEntities[callId - 1].stCallInfo.stCalledSubAddr.Octet3         = pstStkCallOrig->stSubAddr.aucSubAddr[0];
        PS_MEM_CPY(f_astCallMgmtEntities[callId - 1].stCallInfo.stCalledSubAddr.SubAddrInfo,
                  &(pstStkCallOrig->stSubAddr.aucSubAddr[1]),
                   (pstStkCallOrig->stSubAddr.ucLen - 1));
    }



    /* 将CallInfo中的转移号码和连接号码中的长度字段都设置为0 */
    f_astCallMgmtEntities[callId - 1].stCallInfo.stRedirectNumber.ucNumLen = 0;
    f_astCallMgmtEntities[callId - 1].stCallInfo.stConnectNumber.ucNumLen = 0;

    stBc1CallCnf.IsExist = 1;
    stBc1CallCnf.LastOctOffset = (VOS_UINT8)pstStkCallOrig->stBc.ucLen;
    PS_MEM_CPY(&stBc1CallCnf.Octet3,
               pstStkCallOrig->stBc.aucBc,
               pstStkCallOrig->stBc.ucLen);

    MN_CALL_GetDataCfgInfoFromBc(&stBc1CallCnf, &stDataCfgInfo);

    MN_CALL_UpdateDataCallCfgInfo(callId, &stDataCfgInfo);


    TAF_CALL_SetCsCallExistFlg(VOS_TRUE, f_astCallMgmtEntities[callId - 1].stCallInfo.enCallType);

    MN_CALL_UpdateCallReleaseFlag(callId, VOS_FALSE);

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    /* 给MTC模块上报当前CS域业务状态 */
    TAF_SendMtcCsSrvInfoInd();
#endif

    return;
}


VOS_VOID MN_CALL_GetCallReleaseFlag(
    VOS_UINT8                           ucCallId,
    VOS_BOOL                           *pbReleaseFlag
)
{
    *pbReleaseFlag = f_abCallReleaseFlag[ucCallId - 1];
    return;

}


VOS_VOID MN_CALL_UpdateSubAddress(
    VOS_UINT8                           ucCallId,
    MN_CALL_SUBADDR_STRU               *pstSubCallNumber
)
{
    PS_MEM_CPY(&f_astCallMgmtEntities[ucCallId - 1].stCallInfo.stSubCallNumber,
               pstSubCallNumber,
               sizeof(f_astCallMgmtEntities[ucCallId - 1].stCallInfo.stSubCallNumber));

    return;
}


VOS_VOID MN_CALL_UpdateCallReleaseFlag(
    VOS_UINT8                           ucCallId,
    VOS_BOOL                            bReleaseFlag
)
{
    if ((ucCallId == 0) || (ucCallId > MN_CALL_MAX_NUM))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_UpdateCallReleaseFlag: ucCallId is invalid!");
        return;
    }

    f_abCallReleaseFlag[ucCallId - 1] = bReleaseFlag;
    return;

}


VOS_VOID MN_CALL_UpdateOpId(
    VOS_UINT8                           ucCallId,
    MN_OPERATION_ID_T                   opId
)
{
    f_astCallMgmtEntities[ucCallId - 1].stCallInfo.opId = opId;
    return;

}




VOS_UINT32  MN_CALL_GetSpecificStatusCallInfo(
    MN_CALL_STATE_ENUM_U8                enCallStatus,
    MN_CALL_INFO_STRU                   *pstCallInfo
)
{
    VOS_UINT32                          ulLoop;

    for (ulLoop = 0; ulLoop < MN_CALL_MAX_NUM; ulLoop++)
    {
        if (f_astCallMgmtEntities[ulLoop].stCallInfo.enCallState == enCallStatus)
        {
            *pstCallInfo = f_astCallMgmtEntities[ulLoop].stCallInfo;
            return TAF_CS_CAUSE_SUCCESS;

        }
    }

    return TAF_CS_CAUSE_STATE_ERROR;
}



/* 移这部分函数到文件MnCallSendApp.c文件中 */


VOS_UINT32 MN_CALL_GetUeDiscEventInfo(
    const MNCC_REQ_PRIM_MSG_STRU       *pstMsg,
    NAS_STK_CALL_DISC_CAUSE_STRU       *pstDiscEventCause,
    VOS_UINT8                          *pucTi,
    VOS_UINT8                          *pucCallId
)
{
    const NAS_CC_IE_CAUSE_STRU         *pstCause    = VOS_NULL_PTR;

    VOS_UINT8                           ucPos;

    /*
        事件名称                对应的数据结构                      对应的空口消息
        MNCC_DISC_REQ           NAS_CC_MSG_DISCONNECT_MO_STRU           DISCONNECT
        MNCC_REL_REQ            NAS_CC_MSG_RELEASE_MO_STRU              RELEASE
        MNCC_REJ_REQ            NAS_CC_MSG_RELEASE_COMPLETE_MO_STRU     RELEASE COMPLETE
        MNCC_DISC_IND           NAS_CC_MSG_DISCONNECT_MT_STRU           DISCONNECT
        MNCC_REL_IND            NAS_CC_MSG_RELEASE_MT_STRU              RELEASE
        MNCC_REL_CNF            NAS_CC_MSG_RELEASE_COMPLETE_MT_STRU     RELEASE COMPLETE
        MNCC_REJ_IND            none
        MNCC_RADIO_LINK_FAILURE none                                    呼叫重建
    */


    switch (pstMsg->enPrimName)
    {
        case MNCC_DISC_REQ:
            pstCause    = &pstMsg->unParam.stDisc.stCause;
            break;

        case MNCC_REL_REQ:
            pstCause    = &pstMsg->unParam.stRel.stCause;
            break;

        case MNCC_REJ_REQ:
            pstCause    = &pstMsg->unParam.stRelComp.stCause;
            break;

        default:
            return MN_ERR_INVALIDPARM;

    }

    *pucTi      = pstMsg->ucTi;
    *pucCallId  = pstMsg->ucCallId;

    ucPos       = 0;

    if (0 != pstCause->IsExist)
    {
        pstDiscEventCause->ucExistFlg      = VOS_TRUE;
        PS_MEM_CPY( &(pstDiscEventCause->aucCause[ucPos]),&(pstCause->Octet3),sizeof( pstCause->Octet3 ));
        ucPos++;

        if (0 == pstCause->Octet3.Ext)
        {
            PS_MEM_CPY( &(pstDiscEventCause->aucCause[ucPos]),&(pstCause->Octet3a),sizeof( pstCause->Octet3a ));
            ucPos++;
        }
        PS_MEM_CPY( &(pstDiscEventCause->aucCause[ucPos]),&(pstCause->Octet4),sizeof( pstCause->Octet4 ));
        ucPos++;

        pstDiscEventCause->ucLength = ucPos;
    }

    return MN_ERR_NO_ERROR;
}


VOS_UINT32 MN_CALL_GetNetDiscEventInfo(
    const MNCC_IND_PRIM_MSG_STRU       *pstMsg,
    NAS_STK_CALL_DISC_CAUSE_STRU       *pstDiscEventCause,
    VOS_UINT8                          *pucTi,
    VOS_UINT8                          *pucCallId
)
{
    const NAS_CC_IE_CAUSE_STRU         *pstCause    = VOS_NULL_PTR;
    VOS_UINT8                           ucPos;

    /*
        事件名称                对应的数据结构                          对应的空口消息
        MNCC_DISC_REQ           NAS_CC_MSG_DISCONNECT_MO_STRU           DISCONNECT
        MNCC_REL_REQ            NAS_CC_MSG_RELEASE_MO_STRU              RELEASE
        MNCC_REJ_REQ            NAS_CC_MSG_RELEASE_COMPLETE_MO_STRU     RELEASE COMPLETE
        MNCC_DISC_IND           NAS_CC_MSG_DISCONNECT_MT_STRU           DISCONNECT
        MNCC_REL_IND            NAS_CC_MSG_RELEASE_MT_STRU              RELEASE
        MNCC_REL_CNF            NAS_CC_MSG_RELEASE_COMPLETE_MT_STRU     RELEASE COMPLETE
        MNCC_REJ_IND            none                                    MMCC_REL_IND或MMCC_ERR_IND
    */


    switch (pstMsg->enPrimName)
    {
        case MNCC_DISC_IND:
            pstCause    = &pstMsg->unParam.stDisc.stCause;
            break;

        case MNCC_REL_IND:
            pstCause    = &pstMsg->unParam.stRel.stCause;
            break;

        case MNCC_REL_CNF:
            pstCause    = &pstMsg->unParam.stRelComp.stCause;
            break;

        case MNCC_REJ_IND:
             /*Cause信息来源于DISCONNECT, RELEASE or RELEASE COMPLETE消息，如果消息中没有Cause信息，则不包含这个信息，如果呼叫释放时无线链路超时导致，需要携带Cause信息字段，长度填0。*/
             pstDiscEventCause->ucLength     = 0;
             pstDiscEventCause->ucExistFlg   = VOS_TRUE;

            *pucCallId                      = pstMsg->ucCallId;
            return MN_ERR_NO_ERROR;

        default:
            return MN_ERR_INVALIDPARM;

    }

    *pucTi      = pstMsg->ucTi;
    *pucCallId  = pstMsg->ucCallId;

    ucPos       = 0;

    if (0 != pstCause->IsExist)
    {
        pstDiscEventCause->ucExistFlg      = VOS_TRUE;
        PS_MEM_CPY( &(pstDiscEventCause->aucCause[ucPos]),&(pstCause->Octet3),sizeof( pstCause->Octet3 ));
        ucPos++;

        if (0 == pstCause->Octet3.Ext)
        {
            PS_MEM_CPY( &(pstDiscEventCause->aucCause[ucPos]),&(pstCause->Octet3a),sizeof( pstCause->Octet3a ));
            ucPos++;
        }

        PS_MEM_CPY( &(pstDiscEventCause->aucCause[ucPos]),&(pstCause->Octet4),sizeof( pstCause->Octet4 ));
        ucPos++;

        pstDiscEventCause->ucLength = ucPos;
    }

    return MN_ERR_NO_ERROR;

}

/* 移这部分函数到文件MnCallSendApp.c文件中 */


VOS_VOID  MN_CALL_RecordCallEntityRedirectInfo(
        MN_CALL_ID_T                        callId,
        NAS_CC_MSG_SETUP_MT_STRU            *pstSetup)
{
    VOS_UINT8                           ucLen;

    /* 检查参数的有效性 */
    if (VOS_NULL_PTR == pstSetup)
    {
        return;
    }

    /* 初始化CALLING_PI和NO_CLI_CAUSE参数 */
    f_astCallMgmtEntities[callId - 1].stCallInfo.enCallingPI  = MN_CALL_PRESENTATION_RESERVED;
    f_astCallMgmtEntities[callId - 1].stCallInfo.enNoCliCause = MN_CALL_NO_CLI_BUTT;

    /* 记录CALLING_PI和NO_CLI_CAUSE参数 */
    if (VOS_TRUE == pstSetup->stCallingNum.Octet3a.Ext)
    {
        f_astCallMgmtEntities[callId - 1].stCallInfo.enCallingPI  = pstSetup->stCallingNum.Octet3a.PresentationIndicator;
    }

    if (VOS_TRUE == pstSetup->stNoCLICause.IsExist)
    {
        f_astCallMgmtEntities[callId - 1].stCallInfo.enNoCliCause = pstSetup->stNoCLICause.CauseOfNoCLI;
    }

    /* 记录Redirect_num */
    if (VOS_TRUE == pstSetup->stRedirectingNum.IsExist)
    {
        /*lint -e961*/
        ucLen = pstSetup->stRedirectingNum.LastOctOffset
                          - sizeof(NAS_CC_IE_REDIRECTING_NUM_OCTET3_STRU)
                          - sizeof(NAS_CC_IE_REDIRECTING_NUM_OCTET3A_STRU);
        /*lint +e961*/

        if (ucLen <= NAS_CC_MAX_REDIRECTING_BCD_NUM_LEN)
        {
            f_astCallMgmtEntities[callId - 1].stCallInfo.stRedirectNumber.ucNumLen  = ucLen;

            PS_MEM_CPY(f_astCallMgmtEntities[callId - 1].stCallInfo.stRedirectNumber.aucBcdNum,
                       pstSetup->stRedirectingNum.BCDNum,
                       ucLen);

            f_astCallMgmtEntities[callId - 1].stCallInfo.stRedirectNumber.enNumType
                        = (MN_CALL_NUM_TYPE_ENUM_U8)(MN_CALL_IS_EXIT
                           | (pstSetup->stRedirectingNum.Octet3.TON << 4)
                           | pstSetup->stRedirectingNum.Octet3.NPI);
        }

        /* 记录Redirect_subaddr */
        if (VOS_TRUE == pstSetup->stRedirectingSubaddr.IsExist)
        {
            ucLen = pstSetup->stRedirectingSubaddr.LastOctOffset - sizeof(NAS_CC_IE_REDIRECTING_SUBADDR_OCTET3_STRU);

            if (ucLen <= MN_CALL_MAX_SUBADDR_INFO_LEN)
            {
                f_astCallMgmtEntities[callId - 1].stCallInfo.stRedirectSubaddr.LastOctOffset
                            = pstSetup->stRedirectingSubaddr.LastOctOffset;

                PS_MEM_CPY(f_astCallMgmtEntities[callId - 1].stCallInfo.stRedirectSubaddr.SubAddrInfo,
                           pstSetup->stRedirectingSubaddr.SubAddrInfo,
                           ucLen);

                f_astCallMgmtEntities[callId - 1].stCallInfo.stRedirectSubaddr.IsExist = VOS_TRUE;

                /* 目前只支持NSAP的编码方式的子地址Oct3 = MN_CALL_IS_EXIT */
                f_astCallMgmtEntities[callId - 1].stCallInfo.stRedirectSubaddr.Octet3  = MN_CALL_IS_EXIT;
            }
        }
    }
    return;
}


VOS_VOID  MN_CALL_ReadCallEntityRedirectInfo(
        MN_CALL_ID_T                        callId,
        MN_CALL_CLPR_GET_CNF_STRU          *pstGetClprCnf)
{

    if (MN_CALL_DIR_MT != f_astCallMgmtEntities[callId - 1].stCallInfo.enCallDir)
    {
        pstGetClprCnf->ulRet = TAF_ERR_ERROR;
        return;
    }

    /* 填写<PI>参数 */
    if (MN_CALL_PRESENTATION_RESERVED != f_astCallMgmtEntities[callId - 1].stCallInfo.enCallingPI)
    {
        pstGetClprCnf->stRedirectInfo.bitOpPI = VOS_TRUE;
        pstGetClprCnf->stRedirectInfo.enPI    = f_astCallMgmtEntities[callId - 1].stCallInfo.enCallingPI;
    }
    /* 填写<no_CLI_cause>参数 */
    if (MN_CALL_NO_CLI_BUTT != f_astCallMgmtEntities[callId - 1].stCallInfo.enNoCliCause)
    {
        pstGetClprCnf->stRedirectInfo.bitOpNoCLICause  = VOS_TRUE;
        pstGetClprCnf->stRedirectInfo.enNoCLICause     = (VOS_UINT8)f_astCallMgmtEntities[callId - 1].stCallInfo.enNoCliCause;
    }

    /* 填写<redirect_num>和<num_type>参数 */
    if (0 != f_astCallMgmtEntities[callId - 1].stCallInfo.stRedirectNumber.ucNumLen)
    {
        pstGetClprCnf->stRedirectInfo.bitOpRedirectNum   = VOS_TRUE;
        pstGetClprCnf->stRedirectInfo.stRedirectNum      = f_astCallMgmtEntities[callId - 1].stCallInfo.stRedirectNumber;
    }

    /* 填写<redirect_subaddr>和<subaddr_type>参数 */
    if (VOS_TRUE == f_astCallMgmtEntities[callId - 1].stCallInfo.stRedirectSubaddr.IsExist)
    {
        /* 填写<redirect_num>和<num_type>参数 */
        pstGetClprCnf->stRedirectInfo.bitOpRedirectSubaddr = VOS_TRUE;
        pstGetClprCnf->stRedirectInfo.stRedirectSubaddr    = f_astCallMgmtEntities[callId - 1].stCallInfo.stRedirectSubaddr;
    }

    pstGetClprCnf->ulRet = TAF_ERR_NO_ERROR;
    return;
}



VOS_UINT32 MN_CALL_AllowSupsOperation(VOS_VOID)
{

    if (VOS_TRUE == f_stCallSupsCmdMgmt.bInProgress)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


VOS_UINT32 MN_CALL_IsNeedCallRedial(
    MN_CALL_ID_T                        ucCallId,
    NAS_CC_CAUSE_VALUE_ENUM_U32         enCause
)
{
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;
    VOS_UINT32                          ulCallRedialPeriodRemainLen;
    VOS_UINT32                          ulCallRedialIntervalLen;
    VOS_UINT32                          ulCallRedialSupportFlg;

    enCallState = MN_CALL_S_BUTT;
    enMptyState = MN_CALL_MPYT_STATE_BUTT;

    /* 当前正在进行挂断时,不需要重拨 */
    if ( VOS_TRUE == TAF_CALL_GetDisconnectFlg(ucCallId))
    {
        return VOS_FALSE;
    }

    MN_CALL_GetCallState(ucCallId, &enCallState, &enMptyState);

    ulCallRedialSupportFlg      = TAF_CALL_GetRedialSupportFlg(ucCallId);
    ulCallRedialIntervalLen     = TAF_CALL_GetRedialIntervalTimerLen(ucCallId);
    ulCallRedialPeriodRemainLen = TAF_CALL_GetRemainRedialPeriodTimerLen(ucCallId);

    if ((MN_CALL_DIR_MO == MN_CALL_GetCcCallDir(ucCallId))
     && (MN_CALL_S_DIALING == enCallState)
     && (VOS_TRUE == ulCallRedialSupportFlg))
    {
        if (ulCallRedialPeriodRemainLen > ulCallRedialIntervalLen)
        {
#if (FEATURE_ON == FEATURE_ECALL)
            if (VOS_TRUE == TAF_CALL_IsCallTypeEcall(ucCallId))
            {
                /* 对于eCall呼叫失败，无条件重拨 */
                return VOS_TRUE;
            }
#endif

            if (VOS_TRUE == TAF_CALL_IsCallRedialCause(enCause))
            {
                return VOS_TRUE;
            }
        }

    }

    return VOS_FALSE;
}


VOS_VOID MN_CALL_UpdateDiscCallDir(
    MN_CALL_ID_T                        callId,
    VOS_UINT8                           ucIsUser
)
{
    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_UpdateDiscCallDir: callId error!");
        return;
    }

    if (VOS_TRUE == f_astCallMgmtEntities[callId - 1].stCallInfo.stDiscDir.ucDiscCallFlag)
    {
        return;
    }

    f_astCallMgmtEntities[callId - 1].stCallInfo.stDiscDir.ucIsUser       = ucIsUser;
    f_astCallMgmtEntities[callId - 1].stCallInfo.stDiscDir.ucDiscCallFlag = VOS_TRUE;

    return;
}



VOS_UINT32 TAF_CALL_IsOrigNeedRpt(VOS_VOID)
{
    TAF_SDC_CURC_RPT_CTRL_STRU          *pstCurcRptCtrl          = VOS_NULL_PTR;
    VOS_UINT32                           ulChkCallStaFlg;
    VOS_UINT32                           ulChkOrigFlg;

    pstCurcRptCtrl  = TAF_SDC_GetCurcRptCtrl();

    ulChkCallStaFlg = TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg,
                                                TAF_SDC_CMD_RPT_CTRL_BY_CURC,
                                                TAF_SDC_RPT_CMD_CALLSTATE);

    ulChkOrigFlg    = TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg,
                                                TAF_SDC_CMD_RPT_CTRL_BY_CURC,
                                                TAF_SDC_RPT_CMD_ORIG);

    if ( (VOS_FALSE == ulChkCallStaFlg)
      && (VOS_FALSE == ulChkOrigFlg) )
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_CALL_IsConfNeedRpt(VOS_VOID)
{
    TAF_SDC_CURC_RPT_CTRL_STRU          *pstCurcRptCtrl          = VOS_NULL_PTR;
    VOS_UINT32                           ulChkCallStaFlg;
    VOS_UINT32                           ulChkConfFlg;

    pstCurcRptCtrl  = TAF_SDC_GetCurcRptCtrl();

    ulChkCallStaFlg = TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg,
                                                TAF_SDC_CMD_RPT_CTRL_BY_CURC,
                                                TAF_SDC_RPT_CMD_CALLSTATE);

    ulChkConfFlg    = TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg,
                                                TAF_SDC_CMD_RPT_CTRL_BY_CURC,
                                                TAF_SDC_RPT_CMD_CONF);

    if ( (VOS_FALSE == ulChkCallStaFlg)
      && (VOS_FALSE == ulChkConfFlg) )
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_CALL_IsConnNeedRpt(VOS_VOID)
{
    TAF_SDC_CURC_RPT_CTRL_STRU          *pstCurcRptCtrl          = VOS_NULL_PTR;
    VOS_UINT32                           ulChkCallStaFlg;
    VOS_UINT32                           ulChkConnFlg;

    pstCurcRptCtrl  = TAF_SDC_GetCurcRptCtrl();

    ulChkCallStaFlg = TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg,
                                                TAF_SDC_CMD_RPT_CTRL_BY_CURC,
                                                TAF_SDC_RPT_CMD_CALLSTATE);

    ulChkConnFlg    = TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg,
                                                TAF_SDC_CMD_RPT_CTRL_BY_CURC,
                                                TAF_SDC_RPT_CMD_CONN);

    if ( (VOS_FALSE == ulChkCallStaFlg)
      && (VOS_FALSE == ulChkConnFlg) )
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_CALL_IsCendNeedRpt(VOS_VOID)
{
    TAF_SDC_CURC_RPT_CTRL_STRU          *pstCurcRptCtrl          = VOS_NULL_PTR;
    VOS_UINT32                           ulChkCallStaFlg;
    VOS_UINT32                           ulChkCendFlg;

    pstCurcRptCtrl  = TAF_SDC_GetCurcRptCtrl();

    ulChkCallStaFlg = TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg,
                                                TAF_SDC_CMD_RPT_CTRL_BY_CURC,
                                                TAF_SDC_RPT_CMD_CALLSTATE);

    ulChkCendFlg    = TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg,
                                                TAF_SDC_CMD_RPT_CTRL_BY_CURC,
                                                TAF_SDC_RPT_CMD_CEND);

    if ( (VOS_FALSE == ulChkCallStaFlg)
      && (VOS_FALSE == ulChkCendFlg) )
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}



VOS_UINT8 TAF_CALL_GetDisconnectFlg(
    MN_CALL_ID_T                        callId
)
{
    return f_astCallMgmtEntities[callId - 1].stCallInfo.stDiscDir.ucDiscCallFlag;
}


VOS_VOID TAF_CALL_InitDtmfCtx(VOS_VOID)
{
    PS_MEM_SET(&f_stCallDtmfCtx, 0, sizeof(f_stCallDtmfCtx));

    f_stCallDtmfCtx.enDtmfState = TAF_CALL_DTMF_IDLE;

    /*lint -e717*/
    HI_INIT_LIST_HEAD(&f_stCallDtmfCtx.stList);
    /*lint -e717*/

    return;
}


VOS_VOID TAF_CALL_ResetDtmfCtx(
    TAF_CS_CAUSE_ENUM_UINT32            enCause
)
{
    HI_LIST_S                          *pstMe       = VOS_NULL_PTR;
    HI_LIST_S                          *pstTmp      = VOS_NULL_PTR;
    TAF_CALL_DTMF_NODE_STRU            *pstNode     = VOS_NULL_PTR;
    MN_CALL_EVENT_ENUM_U32              enEventType;

    MN_CALL_StopTimer(TAF_CALL_TID_DTMF_ON_LENGTH);
    MN_CALL_StopTimer(TAF_CALL_TID_DTMF_OFF_LENGTH);

    /* 释放缓存内存 */
    /*lint -e961 -e424*/
    msp_list_for_each_safe(pstMe, pstTmp, &f_stCallDtmfCtx.stList)
    {
        pstNode = msp_list_entry(pstMe, TAF_CALL_DTMF_NODE_STRU, stList);

        if (0 == pstNode->stDtmf.usOnLength)
        {
            enEventType = MN_CALL_EVT_STOP_DTMF_RSLT;
        }
        else
        {
            enEventType = MN_CALL_EVT_START_DTMF_RSLT;
        }

        /* 重置时，需要给缓存中的所有DTMF信息回复正式响应 */
        TAF_CALL_SendDtmfCnf(pstNode->stDtmf.usClientId,
                             pstNode->stDtmf.opId,
                             enEventType,
                             enCause);

        /* 从过滤表中删除节点 */
        msp_list_del(&pstNode->stList);

        /* 释放节点内存 */
        PS_MEM_FREE(WUEPS_PID_TAF, pstNode);/*lint !e424*/
    }
    /*lint +e961 +e424*/

    TAF_CALL_InitDtmfCtx();

    return;
}


TAF_CS_CAUSE_ENUM_UINT32 TAF_CALL_IsAllowDtmf(
    MN_CALL_ID_T                       *pCallIds,
    VOS_UINT32                          ulNumOfCalls,
    MN_CALL_ID_T                        CallId
)
{
    VOS_UINT8                           ucLoop;

    /* 判断CallID的有效性 0默认为当前可用CallID */
    if (0 != CallId)
    {
        for (ucLoop = 0; ucLoop < ulNumOfCalls; ucLoop++)
        {
            if (pCallIds[ucLoop] == CallId)
            {
                break;
            }
        }

        if (ucLoop == ulNumOfCalls)
        {
            return TAF_CS_CAUSE_NO_CALL_ID;
        }
    }

    return TAF_CS_CAUSE_SUCCESS;
}


TAF_CS_CAUSE_ENUM_UINT32  TAF_CALL_GetAllowedDtmfCallId(
    MN_CALL_ID_T                       *pCallId
)
{
    VOS_UINT8                           ucLoop;

    if (VOS_TRUE != MN_CALL_GetTchStatus())
    {
        return TAF_CS_CAUSE_NOT_IN_SPEECH_CALL;
    }

    /* 遍历呼叫实体，找出已Attach的呼叫ID */
    for (ucLoop = 0; ucLoop < MN_CALL_MAX_NUM; ucLoop++)
    {
        if (VOS_TRUE != f_astCallMgmtEntities[ucLoop].bUsed)
        {
            continue;
        }

        if ( (MN_CALL_S_ACTIVE   == f_astCallMgmtEntities[ucLoop].stCallInfo.enCallState)
          || (MN_CALL_S_DIALING  == f_astCallMgmtEntities[ucLoop].stCallInfo.enCallState)
          || (MN_CALL_S_ALERTING == f_astCallMgmtEntities[ucLoop].stCallInfo.enCallState)
          || (MN_CALL_S_INCOMING == f_astCallMgmtEntities[ucLoop].stCallInfo.enCallState) )
        {
            *pCallId = (ucLoop + 1);
            return TAF_CS_CAUSE_SUCCESS;
        }
    }

    return TAF_CS_CAUSE_NOT_IN_SPEECH_CALL;

}


TAF_CS_CAUSE_ENUM_UINT32  TAF_CALL_CheckUserDtmfCallId(
    MN_CALL_ID_T                        CallId
)
{
    VOS_UINT8                           ucLoop;
    VOS_UINT32                          ulNumOfCalls;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];

    ulNumOfCalls    = 0;
    PS_MEM_SET(aCallIds, 0, sizeof(aCallIds));

    /* 遍历呼叫实体，找出已Attach的呼叫ID */
    for (ucLoop = 0; ucLoop < MN_CALL_MAX_NUM; ucLoop++)
    {
        if (VOS_TRUE != f_astCallMgmtEntities[ucLoop].bUsed)
        {
            continue;
        }

        if ( (MN_CALL_S_ACTIVE   == f_astCallMgmtEntities[ucLoop].stCallInfo.enCallState)
          || (MN_CALL_S_DIALING  == f_astCallMgmtEntities[ucLoop].stCallInfo.enCallState)
          || (MN_CALL_S_ALERTING == f_astCallMgmtEntities[ucLoop].stCallInfo.enCallState)
          || (MN_CALL_S_INCOMING == f_astCallMgmtEntities[ucLoop].stCallInfo.enCallState) )
        {
            aCallIds[ulNumOfCalls] = ucLoop + 1;
            ulNumOfCalls++;
        }
    }

    /* 如果没有链路，或Attach的呼叫个数为0则不允许发起DTMF请求 */
    if ( (VOS_TRUE != MN_CALL_GetTchStatus())
      || (0 == ulNumOfCalls) )
    {
        return TAF_CS_CAUSE_NOT_IN_SPEECH_CALL;
    }

    /*
        DTMF发送请求接口约定，
        用户输入的CALL ID是无效值0，指示使用任意CALL ID发送DTMF消息
        用户输入的CALL ID不是无效值0，指示用用户下发的CALL ID发送DTMF消息，所以这个CALL ID
        需要满足发送DTMF消息的条件
    */
    return TAF_CALL_IsAllowDtmf(aCallIds, ulNumOfCalls, CallId);
}


TAF_CALL_DTMF_CTX_STRU* TAF_CALL_GetDtmfCtx(VOS_VOID)
{
    return &f_stCallDtmfCtx;
}


TAF_CALL_DTMF_STATE_ENUM_UINT8 TAF_CALL_GetDtmfState(VOS_VOID)
{
    return f_stCallDtmfCtx.enDtmfState;
}


VOS_VOID TAF_CALL_SetDtmfState(
    TAF_CALL_DTMF_STATE_ENUM_UINT8      enState
)
{
    f_stCallDtmfCtx.enDtmfState = enState;
    return;
}


VOS_UINT8 TAF_CALL_GetDtmfBufCnt(VOS_VOID)
{
    return f_stCallDtmfCtx.ucDtmfCnt;
}


VOS_VOID TAF_CALL_DtmfBufCntIncrement(VOS_VOID)
{
    f_stCallDtmfCtx.ucDtmfCnt++;
    return;
}


VOS_VOID TAF_CALL_DtmfBufCntDecrement(VOS_VOID)
{
    f_stCallDtmfCtx.ucDtmfCnt--;
    return;
}


HI_LIST_S* TAF_CALL_GetDtmfListHead(VOS_VOID)
{
    return &(f_stCallDtmfCtx.stList);
}


TAF_CALL_DTMF_INFO_STRU* TAF_CALL_GetDtmfCurInfo(VOS_VOID)
{
    return &(f_stCallDtmfCtx.stCurrDtmf);
}


VOS_VOID TAF_CALL_FillDtmfCnf(
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   opId,
    TAF_CS_CAUSE_ENUM_UINT32            enCause,
    TAF_CALL_EVT_DTMF_CNF_STRU         *pstDtmfCnf
)
{
    TAF_CALL_DTMF_CTX_STRU             *pstDtmfBuf  = VOS_NULL_PTR;

    pstDtmfBuf = TAF_CALL_GetDtmfCtx();

    pstDtmfCnf->usClientId  = usClientId;
    pstDtmfCnf->opId        = opId;
    pstDtmfCnf->enCause     = enCause;

    pstDtmfCnf->callId      = pstDtmfBuf->stCurrDtmf.CallId;
    pstDtmfCnf->enDtmfState = pstDtmfBuf->enDtmfState;
    pstDtmfCnf->ucDtmfCnt   = pstDtmfBuf->ucDtmfCnt;

    return;
}

/* 移这部分函数到文件MnCallSendApp.c文件中 */


VOS_VOID TAF_CALL_AddDtmfInfo(
    TAF_CALL_DTMF_INFO_STRU            *pstDtmfInfo
)
{
    /*lint -e429 -e830*/
    TAF_CALL_DTMF_NODE_STRU            *pstNode         = VOS_NULL_PTR;

    /* 申请过滤表节点内存 */
    pstNode = (TAF_CALL_DTMF_NODE_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(TAF_CALL_DTMF_NODE_STRU));
    if (VOS_NULL_PTR == pstNode)
    {
        MN_ERR_LOG("TAF_CALL_AddDtmfInfo: Mem Alloc Failed! ");
        return;
    }

    pstNode->stDtmf = *pstDtmfInfo;

    /* 将节点增加到DTMF缓存链表中 */
    msp_list_add_tail(&pstNode->stList, &f_stCallDtmfCtx.stList);

    return;
    /*lint +e429 +e830*/

}


TAF_CS_CAUSE_ENUM_UINT32 TAF_CALL_SaveDtmfInfo(
    TAF_CALL_DTMF_INFO_STRU            *pstDtmfInfo
)
{
    HI_LIST_S                          *pstListHead = VOS_NULL_PTR;
    HI_LIST_S                          *pstListLast = VOS_NULL_PTR;
    TAF_CALL_DTMF_NODE_STRU            *pstNode     = VOS_NULL_PTR;

    /* 判断缓存是否已经满了 */
    if (TAF_CALL_GetDtmfBufCnt() >= TAF_CALL_DTMF_BUF_MAX_CNT)
    {
        return TAF_CS_CAUSE_DTMF_BUF_FULL;
    }

    pstListHead = TAF_CALL_GetDtmfListHead();

    /* 不允许连续缓存两个STOP DTMF请求 */
    if (0 == pstDtmfInfo->usOnLength)
    {
        pstListLast = pstListHead->prev;

        if (pstListLast != pstListHead)
        {
            /*lint -e961*/
            pstNode = msp_list_entry(pstListLast, TAF_CALL_DTMF_NODE_STRU, stList);
            /*lint +e961*/

            if (0 == pstNode->stDtmf.usOnLength)
            {
                return TAF_CS_CAUSE_DTMF_REPEAT_STOP;
            }
        }
    }

    /* 将DTMF信息保存到缓存中 */
    TAF_CALL_AddDtmfInfo(pstDtmfInfo);

    TAF_CALL_DtmfBufCntIncrement();

    return TAF_CS_CAUSE_SUCCESS;
}


VOS_VOID TAF_CALL_DelDtmfNode(
    TAF_CALL_DTMF_NODE_STRU            *pstNode
)
{
    /* 从过滤表中删除节点 */
    msp_list_del(&pstNode->stList);

    /* 释放节点内存 */
    PS_MEM_FREE(WUEPS_PID_TAF, pstNode);

    TAF_CALL_DtmfBufCntDecrement();

    return;
}



VOS_VOID TAF_CALL_PreProcRelAllCall(VOS_VOID)
{
    MN_CALL_ID_T                        callId;

    if (VOS_TRUE != f_stCallSupsCmdMgmt.bInProgress)
    {
        return;
    }

    /* 结束当前的呼叫相关补充业务 */
    callId                                              = f_stCallSupsCmdMgmt.astKeyEvts[0].callId;
    f_astCallMgmtEntities[callId].stCallInfo.enSsResult = MN_CALL_SS_RES_SUCCESS;
    MN_CALL_ReportEvent(callId, MN_CALL_EVT_SS_CMD_RSLT);

    /* 清除呼叫相关补充业务注册信息 */
    MN_CALL_ClearSsKeyEvent();
    f_stCallSupsCmdMgmt.bInProgress = VOS_FALSE;
    MN_INFO_LOG("TAF_CALL_PreProcRelAllCall: clear event & not in progress");

    return;
}

/* 移这部分函数到文件MnCallSendApp.c文件中 */

#if (FEATURE_ON == FEATURE_IMS)

MN_CALL_STATE_ENUM_U8 TAF_CALL_ConvertImsaCallStateToMnCallState(
    CALL_IMSA_SRVCC_CALL_STATE_ENUM_UINT8                   enImsaCallSta
)
{
    MN_CALL_STATE_ENUM_U8               enCallSta;

    switch (enImsaCallSta)
    {
        case CALL_IMSA_SRVCC_CALL_ALERTING:
            enCallSta = MN_CALL_S_ALERTING;
            break;

        case CALL_IMSA_SRVCC_CALL_ACTVING:
            enCallSta = MN_CALL_S_WAITING_ACCEPT;
            break;

        case CALL_IMSA_SRVCC_CALL_ACTIVE:
            enCallSta = MN_CALL_S_ACTIVE;
            break;

        case CALL_IMSA_SRVCC_CALL_HELD:
            enCallSta = MN_CALL_S_HELD;
            break;

        case CALL_IMSA_SRVCC_CALL_INCOMING:
            enCallSta = MN_CALL_S_INCOMING;
            break;

        case CALL_IMSA_SRVCC_CALL_WAITING:
            enCallSta = MN_CALL_S_WAITING;
            break;

        case CALL_IMSA_SRVCC_CALL_DIALING:
        default:
            enCallSta = MN_CALL_S_BUTT;
            break;
    }

    return enCallSta;
}


VOS_UINT8 TAF_CALL_CallStateIsLegal(
    CALL_IMSA_SRVCC_CALL_STATE_ENUM_UINT8                   enCallState
)
{
    VOS_UINT8                           ucRst;
    switch (enCallState)
    {
        case CALL_IMSA_SRVCC_CALL_ACTIVE:
        case CALL_IMSA_SRVCC_CALL_HELD:
        case CALL_IMSA_SRVCC_CALL_INCOMING:
        case CALL_IMSA_SRVCC_CALL_WAITING:
        case CALL_IMSA_SRVCC_CALL_ALERTING:
        case CALL_IMSA_SRVCC_CALL_ACTVING:
            ucRst = VOS_TRUE;
            break;


        case CALL_IMSA_SRVCC_CALL_DIALING:
        default:
            ucRst = VOS_FALSE;
            break;
    }

    return ucRst;
}


VOS_UINT8 TAF_CALL_IsDtmfAllowedInCurrentState(VOS_VOID)
{
    VOS_UINT8                           ucLoop;

    /* 遍历呼叫实体，找出已Attach的呼叫ID */
    for (ucLoop = 0; ucLoop < MN_CALL_MAX_NUM; ucLoop++)
    {
        if (VOS_TRUE != f_astCallMgmtEntities[ucLoop].bUsed)
        {
            continue;
        }

        if ( (MN_CALL_S_ACTIVE   == f_astCallMgmtEntities[ucLoop].stCallInfo.enCallState)
          || (MN_CALL_S_DIALING  == f_astCallMgmtEntities[ucLoop].stCallInfo.enCallState)
          || (MN_CALL_S_ALERTING == f_astCallMgmtEntities[ucLoop].stCallInfo.enCallState)
          || (MN_CALL_S_INCOMING == f_astCallMgmtEntities[ucLoop].stCallInfo.enCallState) )
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


VOS_VOID TAF_CALL_ProcSrvccDtmfBuffInfo(TAF_CALL_DTMF_BUFF_STRU *pstDtmfBuffInfo)
{
    VOS_UINT8                           i;
    TAF_CALL_DTMF_INFO_STRU             stDtmfInfo;

    if ((0                              == pstDtmfBuffInfo->ucNum)
     || (IMSA_CALL_DTMF_REQ_MSG_MAX_NUM < pstDtmfBuffInfo->ucNum))
    {
        return;
    }

    if (VOS_FALSE == TAF_CALL_IsDtmfAllowedInCurrentState())
    {
        /* DTMF不满足在当前呼叫状态下发送DTMF，不处理它 */
        return;
    }

    PS_MEM_SET(&stDtmfInfo, 0, sizeof(TAF_CALL_DTMF_INFO_STRU));

    /* 保存DTMF请求信息 */
    for (i = 0; i < pstDtmfBuffInfo->ucNum; i++)
    {
        stDtmfInfo.CallId      = pstDtmfBuffInfo->astDtmf[i].CallId;
        stDtmfInfo.cKey        = pstDtmfBuffInfo->astDtmf[i].cKey;
        stDtmfInfo.opId        = pstDtmfBuffInfo->astDtmf[i].opId;
        stDtmfInfo.usClientId  = pstDtmfBuffInfo->astDtmf[i].usClientId;
        stDtmfInfo.usOffLength = pstDtmfBuffInfo->astDtmf[i].usOffLength;
        stDtmfInfo.usOnLength  = pstDtmfBuffInfo->astDtmf[i].usOnLength;

        if (TAF_CS_CAUSE_DTMF_BUF_FULL == TAF_CALL_SaveDtmfInfo(&stDtmfInfo))
        {
            MN_ERR_LOG("TAF_CALL_ProcSrvccDtmfBuffInfo: DTMF buffer is full!");
            break;
        }
    }
}


VOS_VOID TAF_CALL_CreateCallEntitiesWithImsCallInfo(
    VOS_UINT8                           ucSrvccCallNum,
    CALL_IMSA_SRVCC_CALL_INFO_STRU     *pstSrvccCallInfo,
    VOS_UINT8                           ucStartedHifiFlag
)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucTi;
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucCallNum;
    VOS_UINT8                           ucCallStateValid;
    VOS_UINT8                           ucCallId;

    ucCallNum      =  ucSrvccCallNum;

    /* 边界检查，避免数组越界 */
    if (ucCallNum > CALL_IMSA_MAX_ENTITY_NUM)
    {
        ucCallNum = CALL_IMSA_MAX_ENTITY_NUM;
    }

    /* 初始化呼叫实体 */
    for(i = 0; i < MN_CALL_MAX_NUM; i++)
    {
        MN_CALL_DeleteCallEntity(i);
    }

    /* SRVCC同步呼叫信息时，会指示hifi是否已经打开，nas不再根据呼叫状态和local alerting标志判断 */
    MN_CALL_SetChannelOpenFlg(ucStartedHifiFlag);

    ucIndex = 0;

    for (i = 0; i < ucCallNum; i++)
    {
        /* 按照24007协议,只需要取imsa通过过来的TI的5到8bit作为CC的TI值,既是TI FLAG+TI VALUE */
        ucTi = pstSrvccCallInfo[i].ucTi >> 4;
        ucTi &= 0x0F;

        /* 有普通呼叫是不可以发起增强型多方通话，不存在CALLID为1的普通呼叫，CALLID为2的增强型多方通话
           增强型多方通话hold后，可以再发起一路普通呼叫，也可以增强型多方通话active普通呼叫hold
           CALLID对应关系如下:
           增强型多方话CALLID值为1，普通呼叫的CALLID为2
           TI对应关系如下:
           active的增强型多方话TI值为0,2,3,4,5 ，hold  的普通呼叫的TI为1
           hold  的增强型多方话TI值为1,2,3,4,5 ，active的普通呼叫的TI为0

           如果是多路普通呼叫，就直接根据使用同步过来的CALLID
         */
        if (VOS_TRUE == pstSrvccCallInfo[i].ucEConferenceFlag)
        {
            /* 为保证CallId不会有重复，TI值是唯一的，CallId通过Ti Value加1来分配即可 */
            /* bit7为Ti Flag, bit0-bit7为Ti Value */
            ucCallId = (ucTi & 0x07) + 1;

            /* 如果CALLID为2，需要将CALLID转为1 */
            if ((CALL_IMSA_SRVCC_CALL_HELD == pstSrvccCallInfo[i].enCallState)
             && (2 == ucCallId))
            {
                ucCallId = 1;
            }
        }
        else
        {
            ucCallId = pstSrvccCallInfo[i].ucCallId;
        }

        /* 非法CALL ID直接丢弃 */
        if ((0               == ucCallId)
         || (MN_CALL_MAX_NUM <  ucCallId))
        {
           continue;
        }

        /* call ID减1为呼叫实体数组下标 */
        ucIndex         = ucCallId - 1;

        /* call id合法时，更新实体信息 */
        if (VOS_TRUE == f_astCallMgmtEntities[ucIndex].bUsed)
        {
            /* call ID重复，跳过 */
            continue;
        }

        f_astCallMgmtEntities[ucIndex].bUsed = VOS_TRUE;

        f_astCallMgmtEntities[ucIndex].ulTi  = ucTi;

        f_astCallMgmtEntities[ucIndex].stCallInfo.clientId    = pstSrvccCallInfo[i].clientId;
        f_astCallMgmtEntities[ucIndex].stCallInfo.opId        = pstSrvccCallInfo[i].opId;
        f_astCallMgmtEntities[ucIndex].stCallInfo.callId      = ucCallId;
        f_astCallMgmtEntities[ucIndex].stCallInfo.enCallType  = pstSrvccCallInfo[i].enCallType;
        f_astCallMgmtEntities[ucIndex].stCallInfo.enCallMode  = pstSrvccCallInfo[i].enCallMode;
        f_astCallMgmtEntities[ucIndex].stCallInfo.enCallDir   = pstSrvccCallInfo[i].enCallDir;

        f_astCallMgmtEntities[ucIndex].stCallInfo.enCallState = TAF_CALL_ConvertImsaCallStateToMnCallState(pstSrvccCallInfo[i].enCallState);
        f_astCallMgmtEntities[ucIndex].stCallInfo.enMptyState = pstSrvccCallInfo[i].enMptyState;

        f_astCallMgmtEntities[ucIndex].stCallInfo.enVoiceDomain = TAF_CALL_VOICE_DOMAIN_3GPP;

        /* 发生SRVCC后，IMSA不会带PI和NoCliCause的值给GU,
           在MT的时候，将这两个值显示的赋值成ALLOWED和BUTT.
         */
        if (MN_CALL_DIR_MT == pstSrvccCallInfo[i].enCallDir)
        {
            f_astCallMgmtEntities[ucIndex].stCallInfo.enCallingPI   = MN_CALL_PRESENTATION_ALLOWED;
            f_astCallMgmtEntities[ucIndex].stCallInfo.enNoCliCause  = MN_CALL_NO_CLI_BUTT;

            if (0 == pstSrvccCallInfo[i].stCallNumber.ucNumLen)
            {
                f_astCallMgmtEntities[ucIndex].stCallInfo.enNoCliCause = MN_CALL_NO_CLI_USR_REJ;
            }
        }

        PS_MEM_CPY(&(f_astCallMgmtEntities[ucIndex].stCallInfo.stCalledNumber),
                   &(pstSrvccCallInfo[i].stCalledNumber),
                   sizeof(MN_CALL_CALLED_NUM_STRU));

        PS_MEM_CPY(&(f_astCallMgmtEntities[ucIndex].stCallInfo.stCallNumber),
                   &(pstSrvccCallInfo[i].stCallNumber),
                   sizeof(MN_CALL_BCD_NUM_STRU));

        PS_MEM_CPY(&(f_astCallMgmtEntities[ucIndex].stCallInfo.stRedirectNumber),
                   &(pstSrvccCallInfo[i].stRedirectNumber),
                   sizeof(MN_CALL_BCD_NUM_STRU));

        PS_MEM_CPY(&(f_astCallMgmtEntities[ucIndex].stCallInfo.stConnectNumber),
                   &(pstSrvccCallInfo[i].stConnectNumber),
                   sizeof(MN_CALL_BCD_NUM_STRU));

        /* 判断通话状态，若是DIALING, 则直接挂断电话 */
        ucCallStateValid    = TAF_CALL_CallStateIsLegal(pstSrvccCallInfo[i].enCallState);
        if (VOS_FALSE == ucCallStateValid)
        {
            if (VOS_TRUE == pstSrvccCallInfo[i].ucEConferenceFlag)
            {
                /* 直接挂断这路电话 */
                MN_CALL_ReportEvent(ucCallId, MN_CALL_EVT_RELEASED);

                TAF_CALL_ProcCallStatusFail(ucCallId, pstSrvccCallInfo[i].enCallState);

                MN_CALL_DeleteCallEntity(ucIndex + 1);
            }
            else
            {
                MN_CALL_DeleteCallEntity(ucIndex + 1);
            }

            continue;
        }

        f_astCallMgmtEntities[ucIndex].ucSrvccLocalAlertedFlag = pstSrvccCallInfo[i].ucLocalAlertedFlag;
    }

}

#endif


MN_CALL_MGMT_STRU *TAF_CALL_GetCallEntityAddr(VOS_VOID)
{
    return &f_astCallMgmtEntities[0];
}

/* 删除获取呼叫实体数目 */




VOS_UINT32 TAF_CALL_IsCallRedialCause_CmSrvRej(
    NAS_CC_CAUSE_VALUE_ENUM_U32         enCause
)
{


    VOS_UINT8                           ucIndex;
    TAF_CALL_REDIAL_CFG_STRU            *pstCallRedialCfg;

    pstCallRedialCfg = MN_CALL_GetCallRedialCfg();

    for (ucIndex = 0; ucIndex < pstCallRedialCfg->ucCallRedialCmSrvRejCauseNum; ucIndex++)
    {
        if (enCause == pstCallRedialCfg->aucCallRedialCmSrvRejCause[ucIndex] + NAS_CC_CAUSE_CM_SRV_REJ_BEGIN)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


VOS_UINT32 TAF_CALL_IsCallRedialCause_CsfbSrvRej(
    NAS_CC_CAUSE_VALUE_ENUM_U32         enCause
)
{
    /* CSFB失败不需要重拨，与NAS_MM_EndCsfbFlow中原来填的是other cause保持一致 */

    return VOS_FALSE;
}


VOS_UINT32 TAF_CALL_IsCallRedialCause_RrConnFail(
    NAS_CC_CAUSE_VALUE_ENUM_U32         enCause
)
{
    if ((NAS_CC_CAUSE_RR_CONN_FAIL_ACCESS_BAR                       == enCause)
     || (NAS_CC_CAUSE_RR_CONN_FAIL_CURRENT_PROTOCOL_NOT_SUPPORT     == enCause)
     || (NAS_CC_CAUSE_RR_CONN_FAIL_INVALID_UE_STATE                 == enCause)
     || (NAS_CC_CAUSE_RR_CONN_FAIL_CELL_BARRED                      == enCause))
    {
        return VOS_FALSE;
    }
    else
    {
        return VOS_TRUE;
    }
}


VOS_UINT32 TAF_CALL_IsCallRedialCause_RrRel(
    NAS_CC_CAUSE_VALUE_ENUM_U32         enCause
)
{
    /* NAS_CC_CAUSE_RR_REL_AUTH_REJ
       NAS_CC_CAUSE_RR_REL_NAS_REL_REQ不需要重拨 */
    if ( (NAS_CC_CAUSE_RR_REL_AUTH_REJ    == enCause)        
      || (NAS_CC_CAUSE_RR_REL_NAS_REL_REQ == enCause) )
    {
        return VOS_FALSE;
    }
    else
    {
        return VOS_TRUE;
    }
}


VOS_UINT32 TAF_CALL_IsCallRedialCause_CsfbLmmFail(
    NAS_CC_CAUSE_VALUE_ENUM_U32         enCause
)
{
    /* CSFB失败不需要重拨，与NAS_MM_EndCsfbFlow中原来填的是other cause保持一致 */

    return VOS_FALSE;
}


VOS_UINT32 TAF_CALL_IsCallRedialCause_MmInterErr(
    NAS_CC_CAUSE_VALUE_ENUM_U32         enCause
)
{
    /* NAS_CC_CAUSE_MM_INTER_ERR_RESUME_TO_GU_FAIL是GU报resume_ind时ucCsResumeResult为fail, GU接入层异常，没必要再重拨
       NAS_CC_CAUSE_MM_INTER_ERR_BACK_TO_LTE是CSFB异系统失败重回LTE, MMC会去GU下搜网，需要重拨
       NAS_CC_CAUSE_MM_INTER_ERR_SND_SAPI3_FAIL NAS_CC_CAUSE_MM_INTER_ERR_EST_SAPI3_FAIL是短信的错误，报到CALL认为异常，不重拨
       NAS_CC_CAUSE_MM_INTER_ERR_ECALL_INACTIVE 不需要重拨
       NAS_CC_CAUSE_MM_INTER_ERR_WAIT_EST_CNF_TIME_OUT 不需要重拨 */

    switch (enCause)
    {
        /* cs LAU rej #12现在有NV定制有业务时会触发搜网，可以允许重拨 */
        case NAS_CC_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR:
        case NAS_CC_CAUSE_MM_INTER_ERR_CS_DETACH:
        case NAS_CC_CAUSE_MM_INTER_ERR_CS_SIM_INVALID:
        case NAS_CC_CAUSE_MM_INTER_ERR_NOT_SUPPORT_CS_CALL_S1_MODE_ONLY:
        case NAS_CC_CAUSE_MM_INTER_ERR_RESUME_TO_GU_FAIL:
        case NAS_CC_CAUSE_MM_INTER_ERR_TI_INVALID:
        case NAS_CC_CAUSE_MM_INTER_ERR_WAIT_EST_CNF_TIME_OUT:
        case NAS_CC_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST:
        case NAS_CC_CAUSE_MM_INTER_ERR_UE_INVALID_STATE:
        case NAS_CC_CAUSE_MM_INTER_ERR_WAIT_CC_REEST_TIME_OUT:
        case NAS_CC_CAUSE_MM_INTER_ERR_SND_SAPI3_FAIL:
        case NAS_CC_CAUSE_MM_INTER_ERR_EST_SAPI3_FAIL:
        case NAS_CC_CAUSE_MM_INTER_ERR_ECALL_INACTIVE:
        case NAS_CC_CAUSE_MM_INTER_ERR_REEST_FAIL:
        case NAS_CC_CAUSE_MM_INTER_ERR_CC_REL_REQ:
        case NAS_CC_CAUSE_MM_INTER_ERR_LTE_LIMITED_SERVICE:

            return VOS_FALSE;

        default:
            return VOS_TRUE;
    }
}


VOS_UINT32 TAF_CALL_IsCallRedialCause_CcInterErr(
    NAS_CC_CAUSE_VALUE_ENUM_U32         enCause
)
{
    if ((NAS_CC_CAUSE_CC_INTER_ERR_T335_TIME_OUT        == enCause)
     || (NAS_CC_CAUSE_CC_INTER_ERR_WAIT_RAB_TIME_OUT    == enCause))
    {
        return VOS_FALSE;
    }
    else
    {
        return VOS_TRUE;
    }
}


VOS_UINT32 TAF_CALL_IsCallRedialCause(
    NAS_CC_CAUSE_VALUE_ENUM_U32         enCause
)
{
    VOS_UINT32                          ulRslt;

    ulRslt  = VOS_TRUE;
    /* cm service reject */
    if ((enCause >= NAS_CC_CAUSE_CM_SRV_REJ_BEGIN)
     && (enCause <= NAS_CC_CAUSE_CM_SRV_REJ_END))
    {
        ulRslt = TAF_CALL_IsCallRedialCause_CmSrvRej(enCause);
    }

    /* CSFB Service reject */
    else if ((enCause >= NAS_CC_CAUSE_CSFB_SRV_REJ_BEGIN)
          && (enCause <= NAS_CC_CAUSE_CSFB_SRV_REJ_END))
    {
        ulRslt = TAF_CALL_IsCallRedialCause_CsfbSrvRej(enCause);
    }

    /* est_cnf失败，与NAS_MM_IsAbleRecover_EstCnfFailResult的处理逻辑保持一致 */
    else if ((enCause >= NAS_CC_CAUSE_RR_CONN_FAIL_BEGIN)
          && (enCause <= NAS_CC_CAUSE_RR_CONN_FAIL_END))
    {
        ulRslt = TAF_CALL_IsCallRedialCause_RrConnFail(enCause);

    }

    /* rel_ind, 除了鉴权被拒，其他原因值与NAS_MM_IsNeedCmServiceRetry_RelIndResult的处理逻辑保持一致 */
    else if ((enCause >= NAS_CC_CAUSE_RR_REL_BEGIN)
          && (enCause <= NAS_CC_CAUSE_RR_REL_END))
    {
        ulRslt = TAF_CALL_IsCallRedialCause_RrRel(enCause);
    }

    /* 除了鉴权被拒，其他原因值暂时定为都需要重拨 */
    else if ((enCause >= NAS_CC_CAUSE_CSFB_LMM_FAIL_BEGIN)
          && (enCause <= NAS_CC_CAUSE_CSFB_LMM_FAIL_END))
    {
        ulRslt = TAF_CALL_IsCallRedialCause_CsfbLmmFail(enCause);
    }

    /* MM INTER ERR */
    else if ((enCause >= NAS_CC_CAUSE_MM_INTER_ERR_BEGIN)
          && (enCause <= NAS_CC_CAUSE_MM_INTER_ERR_END))
    {
        ulRslt = TAF_CALL_IsCallRedialCause_MmInterErr(enCause);
    }

    /* T335超时,等待RAB超时不需要重拨 */
    else if ((enCause >= NAS_CC_CAUSE_CC_INTER_ERR_BEGIN)
          && (enCause <= NAS_CC_CAUSE_CC_INTER_ERR_END))
    {
        ulRslt = TAF_CALL_IsCallRedialCause_CcInterErr(enCause);
    }
    else
    {
        /* 网络挂断，call内部错误，vc错误，不需要重拨 */
        ulRslt  = VOS_FALSE;
    }

    return ulRslt;
}



/*lint -restore */
#if (FEATURE_ON == FEATURE_HUAWEI_VP)

VOS_VOID MN_CALl_VoicePreferJudgeVoiceCallExist(VOS_VOID)
{
    VOS_UINT32      i;

    /* 遍历所有呼叫控制实体*/
    for (i = 0; i < MN_CALL_MAX_NUM; i++)
    {
        /*判断是否处于激活态或者保持态,并且是语音呼叫*/
        if ((VOS_TRUE == f_astCallMgmtEntities[i].bUsed)
         && (MN_CALL_TYPE_VOICE == f_astCallMgmtEntities[i].stCallInfo.enCallType)
         && ((MN_CALL_S_ACTIVE == f_astCallMgmtEntities[i].stCallInfo.enCallState)
          || (MN_CALL_S_HELD == f_astCallMgmtEntities[i].stCallInfo.enCallState)))
        {
            break;
        }
    }

    if (MN_CALL_MAX_NUM == i)
    {
        MN_CALL_VoicePreferSendRabmVoiceCallIndMsg(VOS_FALSE);
    }
    else
    {
        MN_CALL_VoicePreferSendRabmVoiceCallIndMsg(VOS_TRUE);
    }

    return;
}


VOS_VOID MN_CALL_VoicePreferSendRabmVoiceCallIndMsg(VOS_UINT32 ulVoiceFlag)
{
    VOS_UINT32                                              ulRet;              /* 定义调用VOS发送函数的返回值 */
    CALL_RABM_VOICE_PREFER_CS_EXIST_IND_STRU               *pstMsg;             /* 定义原语类型指针 */
    TAF_SDC_PLMN_ID_STRU                                   *pstPlmnId;
    TAF_SDC_PLMN_ID_STRU                                    stPlmnId;

    /* 获取当前注册网络的PLMN,转化为十六进制BCD格式传递给rabm*/
    pstPlmnId = TAF_SDC_GetCurrCampPlmnId();
    stPlmnId.ulMcc = pstPlmnId->ulMcc;
    stPlmnId.ulMnc = pstPlmnId->ulMnc;

    TAF_SDC_PlmnId2Bcd(&stPlmnId);

    /* 申请内存  */
    pstMsg = (CALL_RABM_VOICE_PREFER_CS_EXIST_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_RABM,
                                               sizeof(CALL_RABM_VOICE_PREFER_CS_EXIST_IND_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstMsg)
    {
        /* 内存申请失败 */
        MN_ERR_LOG("MN_CALL_VoicePreferSendRabmVoiceCallIndMsg:ERROR: Memory Alloc Error for pstMsg");
        return ;
    }

    /* 填写相关参数 */
    pstMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid       = WUEPS_PID_TAF;
    pstMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_RABM;
    pstMsg->MsgHeader.ulLength          = sizeof(CALL_RABM_VOICE_PREFER_CS_EXIST_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName         = CALL_RABM_VOICEPREFER_CS_EXIST_IND;

    pstMsg->ulVoiceFlag                 = ulVoiceFlag;
    pstMsg->ulCampMcc                   = stPlmnId.ulMcc;
    pstMsg->ulCampMnc                   = stPlmnId.ulMnc;

    /* 调用VOS发送原语 */
    ulRet = PS_SEND_MSG(WUEPS_PID_TAF, pstMsg);
    if ( VOS_OK != ulRet )
    {
        MN_ERR_LOG("MN_CALL_VoicePreferSendRabmVoiceCallIndMsg:ERROR:PS_SEND_MSG ");
        return ;
    }

    return;
}
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

