

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "NasCcInclude.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define THIS_FILE_ID            PS_FILE_ID_NAS_CC_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/

extern VOS_VOID  NAS_CC_ProcRabmPrimitive(const VOS_VOID *pMsg);



VOS_VOID  NAS_CC_ProcGmmccPrimitive(
    const VOS_VOID                      *pMsg
);

/*****************************************************************************
  2 函数实现
*****************************************************************************/

LOCAL VOS_VOID  NAS_CC_Init()
{

    NAS_CC_InitEntities();

    NAS_CC_InitAllTimers();

    NAS_CC_InitUserConn();

    NAS_CC_InitUus1Info();

    NAS_CC_ReadNvimInfo();

    NAS_CC_InitSsSwitchInfo();

    NAS_CC_ClearAllCacheMsg();

    return;
}



VOS_UINT32  NAS_CC_PidInit(
    enum VOS_INIT_PHASE_DEFINE          enInitPhase
)
{
    switch (enInitPhase)
    {
    case VOS_IP_LOAD_CONFIG:
        NAS_CC_Init();

#if (FEATURE_ON == FEATURE_PTM)
        NAS_CC_InitErrLogInfo();
#endif
        break;
    case VOS_IP_FARMALLOC:
    case VOS_IP_INITIAL:
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



VOS_VOID  NAS_CC_MsgRoute(
    struct MsgCB*                       pMsg
)
{
    switch (pMsg->ulSenderPid)
    {
/*回放工程恢复全局变量*/
#ifdef __PS_WIN32_RECUR__
        case WUEPS_PID_CC:
            NAS_CC_RestoreContextData(pMsg);
            break;
#endif
        case WUEPS_PID_MM:
            NAS_CC_ProcMmccPrimitive(pMsg);
            break;

        case WUEPS_PID_TAF:
            NAS_CC_ProcMnccPrimitive(pMsg);
            break;

        case VOS_PID_TIMER:
            NAS_CC_ProcTimeoutMsg(pMsg);
            break;

        case WUEPS_PID_GMM:
            NAS_CC_ProcGmmccPrimitive(pMsg);
            break;

        case WUEPS_PID_AT:
            NAS_CC_ProcAtPrimitive(pMsg);
            break;

#if (FEATURE_ON == FEATURE_PTM)
        case MSP_PID_DIAG_APP_AGENT:
            NAS_CC_RcvAcpuOmMsg(pMsg);
            break;
#endif

        default :
            NAS_CC_WARN_LOG1("NAS_CC_MsgRoute: Unknown messge sender.", (VOS_INT32)(pMsg->ulSenderPid));
            break;
    }
}

/******************************************************************************
 * 函数名称 ： WuepsCmFidInit
 * 功能描述 ： WUEPS CC FID的初始化函数
 * 参数说明 ： 无
 * 备    注 ：
 * 返 回 值 ： VOS_UINT32 初始化结果：
 *             0  : 成功
 *             非0: 失败
 *
 * 变更历史 ：
 *           No.  姓名      变更                                    日   期
 *           1    张志勇    新建                                   2005.02.24
 *           2    张志勇    AS IT时不启动CC/SS                     2005.03.08
 *****************************************************************************/
VOS_UINT32 WuepsCmFidInit ( enum VOS_INIT_PHASE_DEFINE ip )
{
    VOS_UINT32 ulReturnCode;

    switch( ip )
    {
    case   VOS_IP_LOAD_CONFIG:
        ulReturnCode = VOS_RegisterPIDInfo(WUEPS_PID_CC,
                              (Init_Fun_Type) NAS_CC_PidInit,
                                  (Msg_Fun_Type) NAS_CC_MsgRoute  );
        if( VOS_OK != ulReturnCode )
        {
            return VOS_ERR;
        }

        ulReturnCode = VOS_RegisterPIDInfo(WUEPS_PID_SS,
                              (Init_Fun_Type) WuepsSsPidInit,
                                  (Msg_Fun_Type) Ss_TaskEntry_T  );
        if( VOS_OK != ulReturnCode )
        {
            return VOS_ERR;
        }

        ulReturnCode = VOS_RegisterPIDInfo(WUEPS_PID_TC,
                                   (Init_Fun_Type) WuepsTcPidInit,
                                  (Msg_Fun_Type) Tc_TaskEntry  );
        if( VOS_OK != ulReturnCode )
        {
            return VOS_ERR;
        }

        ulReturnCode = VOS_RegisterPIDInfo(WUEPS_PID_SMS,
                              (Init_Fun_Type) WuepsSmsPidInit,
                                  (Msg_Fun_Type) SMS_TaskEntry  );
        if( VOS_OK != ulReturnCode )
        {
            return VOS_ERR;
        }


        ulReturnCode = VOS_RegisterMsgTaskPrio(WUEPS_FID_CM, VOS_PRIORITY_M4 );
        if( VOS_OK != ulReturnCode )
        {
            return VOS_ERR;
        }
        break;

    case   VOS_IP_FARMALLOC:
    case   VOS_IP_INITIAL:
    case   VOS_IP_ENROLLMENT:
    case   VOS_IP_LOAD_DATA:
    case   VOS_IP_FETCH_DATA:
    case   VOS_IP_STARTUP:
    case   VOS_IP_RIVAL:
    case   VOS_IP_KICKOFF:
    case   VOS_IP_STANDBY:
    case   VOS_IP_BROADCAST_STATE:
    case   VOS_IP_RESTART:
    case   VOS_IP_BUTT:
        break;
    }
    return VOS_OK;

}


VOS_VOID  NAS_CC_PowerOff(VOS_VOID)
{
    NAS_CC_StopAllRunningTimer();

    NAS_CC_Init();
}


VOS_VOID NAS_CC_ProcessSpecTypeBufferMsg(VOS_UINT32 ulEventType)
{
    NAS_CC_ENTRY_MSG_STRU              *pstEntryMsg = VOS_NULL_PTR;

    /* 内存空间分配 */
    pstEntryMsg = (NAS_CC_ENTRY_MSG_STRU *)PS_MEM_ALLOC(WUEPS_PID_CC,
                                             sizeof(NAS_CC_ENTRY_MSG_STRU));

    if (VOS_NULL_PTR == pstEntryMsg)
    {
        NAS_CC_ERR_LOG("NAS_CC_ProcessSpecTypeBufferMsg:ERROR: MEM ALLOC FAIL");

        return;
    }

    while (VOS_TRUE == NAS_CC_GetNextSpecEventTypeCachedMsg(ulEventType, pstEntryMsg))
    {
        NAS_CC_MsgRoute((struct MsgCB*)pstEntryMsg->aucEntryMsgBuffer);
    }

    PS_MEM_FREE(WUEPS_PID_CC, pstEntryMsg);

    return;
}


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



