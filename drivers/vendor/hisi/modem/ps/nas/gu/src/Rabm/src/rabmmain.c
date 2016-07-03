
#include "rabminclude.h"
#include "NasRabmMain.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*lint -e958*/

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印 */
#define    THIS_FILE_ID        PS_FILE_ID_RABM_MAIN_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/

extern VOS_UINT32 WuepsSmPidInit ( enum VOS_INIT_PHASE_DEFINE ip );
extern VOS_VOID Sm_TaskEntry  (struct MsgCB * pRcvMsg);
extern VOS_VOID RABM_TcDataQInit(VOS_VOID);

#ifdef __PS_WIN32_RECUR__

VOS_UINT32 NAS_RABM_RestoreContextData(struct MsgCB * pMsg)
{
    NAS_RABM_SDT_MSG_ST                      *pRcvMsgCB;
    NAS_RABM_OUTSIDE_RUNNING_CONTEXT_ST      *pstOutsideCtx;

    pRcvMsgCB     = (NAS_RABM_SDT_MSG_ST *)pMsg;

    if (EVT_NAS_RABM_OUTSIDE_RUNNING_CONTEXT_FOR_PC_REPLAY == pRcvMsgCB->usMsgID)
    {
        pstOutsideCtx = &pRcvMsgCB->stOutsideCtx;

        gRabm3GTo2GSwitch     = pstOutsideCtx->pc_gRabm3GTo2GSwitch;
        gRabm3GTo2GT1Switch   = pstOutsideCtx->pc_gRabm3GTo2GT1Switch;
        gRabm2GTo3GDataResume = pstOutsideCtx->pc_gRabm2GTo3GDataResume;

        g_ucReestTimerFlg = pstOutsideCtx->pc_g_ucReestTimerFlg;
        PS_MEM_CPY(g_aucSiMapEnt, pstOutsideCtx->pc_g_aucSiMapEnt, 256);
        PS_MEM_CPY(g_aRabmPsEnt, pstOutsideCtx->pc_g_aRabmPsEnt, sizeof(RABM_ENTITY_PS_STRU) * RABM_PS_MAX_ENT_NUM);
        PS_MEM_CPY(g_aRabmCsEnt, pstOutsideCtx->pc_g_aRabmCsEnt, sizeof(RABM_ENTITY_CS_STRU) * RABM_CS_MAX_ENT_NUM);
        PS_MEM_CPY(&g_RabmTcInf, &pstOutsideCtx->pc_g_RabmTcInf, sizeof(RABM_TC_INF_STRU));

        PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_INFO, "RABM: NAS_RABM_RestoreContextData - data is restored.");
    }
    return RABM_TRUE;
}
#endif


VOS_UINT32 NAS_RABM_SndOutsideContextData()
{
    NAS_RABM_SDT_MSG_ST                      *pSndMsgCB     = VOS_NULL_PTR;
    NAS_RABM_OUTSIDE_RUNNING_CONTEXT_ST      *pstOutsideCtx;

    pSndMsgCB = (NAS_RABM_SDT_MSG_ST *)PS_ALLOC_MSG(WUEPS_PID_RABM, sizeof(NAS_RABM_SDT_MSG_ST));

    if ( VOS_NULL_PTR == pSndMsgCB )
    {
        PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_ERROR, "NAS_RABM_SndOutsideContextData:ERROR: Alloc Memory Fail.");
        return RABM_FALSE;
    }

    pstOutsideCtx = &pSndMsgCB->stOutsideCtx;

    pstOutsideCtx->pc_gRabm3GTo2GSwitch     = gRabm3GTo2GSwitch;
    pstOutsideCtx->pc_gRabm3GTo2GT1Switch   = gRabm3GTo2GT1Switch;
    pstOutsideCtx->pc_gRabm2GTo3GDataResume = gRabm2GTo3GDataResume;

    pstOutsideCtx->pc_g_ucReestTimerFlg = g_ucReestTimerFlg;
    PS_MEM_CPY(pstOutsideCtx->pc_g_aucSiMapEnt, g_aucSiMapEnt, 256);
    PS_MEM_CPY(pstOutsideCtx->pc_g_aRabmPsEnt, g_aRabmPsEnt, sizeof(RABM_ENTITY_PS_STRU) * RABM_PS_MAX_ENT_NUM);
    PS_MEM_CPY(pstOutsideCtx->pc_g_aRabmCsEnt, g_aRabmCsEnt, sizeof(RABM_ENTITY_CS_STRU) * RABM_CS_MAX_ENT_NUM);
    PS_MEM_CPY(&pstOutsideCtx->pc_g_RabmTcInf, &g_RabmTcInf, sizeof(RABM_TC_INF_STRU));

    pSndMsgCB->ulReceiverPid = WUEPS_PID_RABM;
    pSndMsgCB->ulSenderPid   = WUEPS_PID_RABM;
    pSndMsgCB->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pSndMsgCB->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pSndMsgCB->ulLength      = sizeof(NAS_RABM_OUTSIDE_RUNNING_CONTEXT_ST) + 4;  /* 4: usMsgID + usReserved */
    pSndMsgCB->usMsgID       = EVT_NAS_RABM_OUTSIDE_RUNNING_CONTEXT_FOR_PC_REPLAY;

    DIAG_TraceReport(pSndMsgCB);
    PS_FREE_MSG(WUEPS_PID_RABM, pSndMsgCB);

    return RABM_TRUE;
}




VOS_VOID Rabm_3GTaskEntry( struct MsgCB* pMsg )
{
    MSG_HEADER_STRU         *pHeader;                                            /* 定义消息头指针*/

    pHeader = (MSG_HEADER_STRU *) pMsg;                                       /* 获取消息头指针*/

    if ( VOS_PID_TIMER == pMsg->ulSenderPid )
    {                                                                       /* 如果是TIMER消息*/
        Rabm_TimerProcess( ( REL_TIMER_MSG *) pMsg );
        return;
    }

    switch( pHeader->ulSenderPid )
    {                                                                    /* 根据Src Tsk Id分发消息*/
    case WUEPS_PID_PDCP:
    case TPS_PID_PDC:
        if( ID_PDCP_RABM_TC_DATA_IND_NOTIFY == *((VOS_UINT16 *)((VOS_UINT8 *)pMsg + VOS_MSG_HEAD_LENGTH)) )
        {
            RABM_RcvPsTcDataInd((VOS_VOID *)pMsg);                            /* 调用下行PS域的数据处理                   */
        }
        else if ( ID_PDCP_RABM_DATA_RESUME_RSP == *((VOS_UINT16 *)((VOS_UINT8 *)pMsg + VOS_MSG_HEAD_LENGTH)) )
        {
            NAS_RabmRcvPdcpDataResumeRsp((VOS_VOID *)pMsg);
        }
        else if ( ID_PDCP_RABM_SAVE_DATA_RSP == *((VOS_UINT16 *)((VOS_UINT8 *)pMsg + VOS_MSG_HEAD_LENGTH)) )
        {
            NAS_RabmRcvPdcpSaveDataRsp((VOS_VOID *)pMsg);
        }
        else
        {
            PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Rabm_3GTaskEntry:WARNING:PDCP->RABM MsgName Error!");
        }
        break;

    case WUEPS_PID_TAF:
        switch( pHeader->ulMsgName )
        {
        case TAFRABM_PS_DATA_REQ:
            RABM_RcvPsDataReq((VOS_VOID *)pMsg);                            /* 调用上行PS域的数据处理*/
            break;
        case TAFRABM_CS_DATA_REQ:
            RABM_RcvCsDataReq((VOS_VOID *)pMsg);                            /* 调用上行CS域的数据处理*/
            break;
#if (FEATURE_ON == FEATURE_HUAWEI_VP)
        case CALL_RABM_VOICEPREFER_CS_EXIST_IND:
            NAS_RABM_RcvVoicePreferCsExistInd((VOS_VOID *)pMsg);
            break;
#endif
        default:
            PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Rabm_3GTaskEntry:WARNING:APP->RABM MsgName Error!");
        }
        break;

    case WUEPS_PID_RLC:
    case TPS_PID_RLC:
        if( ID_RLC_RABM_CS_DATA_IND == *((VOS_UINT16 *)((VOS_UINT8 *)pMsg + VOS_MSG_HEAD_LENGTH)) )
        {                                                               /* 根据消息的类型进行分发                   */
            RABM_RcvRlcDataInd((RLC_RABM_CS_DATA_IND_STRU *)pMsg);       /* 调用下行CS域的数据处理                   */
        }
        else
        {
            PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Rabm_3GTaskEntry:WARNING:RLC->RABM MsgName Error!");
        }
        break;

    case WUEPS_PID_GMM:
        if ( ID_GMM_RABM_ROUTING_AREA_UPDATE_IND == pHeader->ulMsgName )
        {
            NAS_RabmGmmRoutingAreaUpdateIndMsg( (VOS_VOID *)pMsg );  /*收到路由区更新消息*/
        }
        else
        {
            PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Rabm_3GTaskEntry:WARNING:GMM->RABM MsgName Error!");
        }
        break;

    case UEPS_PID_SN:     /*收到2G中的SNDCP消息，直接丢弃*/
        /*打印出错信息---收到不合逻辑的消息*/
        RABM_LOG_WARNING( "Rabm_3GTaskEntry:WARNING:RECEIVE Msg from SNDCP is ILLOGICAL in 3G mode!" );
        break;

    case WUEPS_PID_WRR:
        switch( pHeader->ulMsgName )
        {                                                               /* 根据消息的类型进行分发                   */
        case RRRABM_STATUS_IND:
            RABM_RcvRrcStatusInd((VOS_VOID *)pMsg);                         /* 调用STATUS消息的处理                     */
            break;
        case RRRABM_RAB_IND:
            RABM_RcvRrcRabInd((VOS_VOID *)pMsg);                            /* 调用RAB IND的处理                        */
            break;
        case RRRABM_REL_ALL_REQ:
            RABM_RcvRrcRelAllReq();
            break;

        case RRRABM_FASTDORM_INFO_IND:
            NAS_RABM_RcvWasFastDormInfoInd(pMsg);
            break;

        default:
            PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Rabm_3GTaskEntry:WARNING:RRCF->RABM MsgName Error!");
            break;
        }
        break;

    case WUEPS_PID_TC:
        if( TCRABM_TEST_REQ == pHeader->ulMsgName )
        {
            RABM_RcvTcTestReq((TCRABM_TEST_REQ_STRU *)pMsg);
        }
        else if(TCRABM_TEST_LOOP_REQ == pHeader->ulMsgName)
        {
            RABM_RcvTcTestLoopReq((TCRABM_TEST_LOOP_REQ_STRU *)pMsg);
        }
        else
        {
            PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Rabm_3GTaskEntry:WARNING:TC->RABM MsgName Error!");
        }
        break;
#ifdef __PS_WIN32_RECUR__
    case WUEPS_PID_RABM:
        NAS_RABM_RestoreContextData(pMsg);
        break;
#endif
    default:
        PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Rabm_3GTaskEntry:WARNING:SenderPid Error!");
        break;
    }

}


VOS_VOID Rabm_TimerProcess( REL_TIMER_MSG *pTimer )
{
    /*入口参数合法性检查:指针是否为空，ulPara项是否合法:*/
    if ( VOS_NULL_PTR == pTimer )
    {
        /*打印警告信息---入口指针为空:*/
        RABM_LOG_WARNING( "Rabm_TimerProcess:WARNING:Entry Pointer is NULL!" );
        return;
    }

    if ( pTimer->ulPara >= RABM_TIMER_PARA_BUTT )
    {
        /*打印警告信息---入口消息出错:*/
        RABM_LOG_WARNING( "Rabm_TimerProcess:WARNING:The Parameter of the timer expired Msg is WRONG!" );
        return;
    }

    switch ( pTimer->ulPara )
    {
        case RABM_TIMER_PARA_ROUT_AREA_UPDATE_T1:
        case RABM_TIMER_PARA_3_TO_2_T3:
        case RABM_TIMER_PARA_ACT_REQ_T1:
            /*打印警告信息---收到不合逻辑的信息:*/
            RABM_LOG_NORMAL( "Rabm_TimerProcess:NORMAL:RECEIVE Illogical Timer Expired Msg in 3G mode!" );
            break;

        case RABM_TIMER_PARA_REESTRAB_TIMER:
            NAS_RABM_ProcTiRabReestRequestExpired();
            break;

        case RABM_TIMER_RAB_REESTABLISH_PENDING:
            NAS_RABM_ProcTiRabReestPendingExpired((VOS_UINT8)pTimer->ulName);
            break;

        case RABM_TIMER_FASTDORM_FLUX_DETECT:
            NAS_RABM_FastDormFluxDetectExpired();
            break;

        case RABM_TIMER_FASTDORM_RETRY:
            NAS_RABM_FastDormRetryExpired();
            break;

        case RABM_TIMER_FASTDORM_WAIT_GMM_QRY_RESULT:
            NAS_RABM_FastDormWaitGmmProcQryRsltExpired();
            break;


        case RABM_TIMER_RESEND_EST_REQ:
            RABM_TimerStart(RABM_REESTABLISH_REQ_SENT, RABM_RABM_REEST_PROT_TIMER_LEN);
            RABM_SndRabReestReq();
            break;

#if (FEATURE_ON == FEATURE_HUAWEI_VP)
        case RABM_TIMER_VOICEPREFER_DELAY:
            NAS_RABM_VoicePreferDelayExpired();
            break;

        case RABM_TIMER_VOICEPREFER_REQRY_GMM_DELAY:
            NAS_RABM_VoicePreferReQryGmmDelayExpired();
            break;
 #endif

        default:
            break;
    }
    return;
}


VOS_VOID Rabm_Init()
{
    VOS_UINT8   i;
    for(i = 0; i < RABM_PS_MAX_ENT_NUM; i++)
    {                                                                           /* 初始化PS域的实体                         */
        g_aRabmPsEnt[i].ucState = RABM_NULL;                                    /* 初始化状态                               */
        PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Rabm_Init:NORMAL:RABM state = RABM_NULL ");
        g_aRabmPsEnt[i].ucPppFlg = RABM_SM_IP_PROT;                             /* 初始化PPP标志为不支持PPP                 */
        g_aRabmPsEnt[i].ucReEstFlg = RABM_FALSE;
        g_aRabmPsEnt[i].hRabPendingTmrHdl = VOS_NULL_PTR;
        g_aRabmPsEnt[i].RabInfo.ucRbNum = 0;                                    /* 实体包含的RB的个数为0                    */
        g_aRabmPsEnt[i].QoS.ulQosLength = 0;                                    /* QOS参数置为空                            */
        g_aRabmPsEnt[i].ucStpFlg = RABM_FALSE;
        g_aRabmPsEnt[i].DlDataSave.ucNum = 0;                                   /* 保存的下行数据个数为0                    */
        g_aRabmPsEnt[i].DlDataSave.Data.pData = RABM_POINTER_NULL;
        g_aRabmPsEnt[i].DlDataSave.Data.pNxt = RABM_POINTER_NULL;
    }
    g_ucReestTimerFlg = RABM_FALSE;                                             /* TIMER ID为无效                           */

    for(i = 0; i < RABM_CS_MAX_ENT_NUM; i++)
    {                                                                           /* 初始化CS域的实体                         */
        g_aRabmCsEnt[i].ucState = RABM_NULL;                                    /* 初始化状态为无效                         */
        PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Rabm_Init:NORMAL:RABM state = RABM_NULL ");
        g_aRabmCsEnt[i].RabInfo.ucRbNum = 0;                                    /* 实体包含的RB的个数为0                    */
    }
    RABM_Memset(g_aucSiMapEnt,(VOS_CHAR)0xFF,256);                                        /* 实体ID初始化为无效                       */

    /*初始化g_RabmTcInf*/
    RABM_Memset((VOS_VOID *)&g_RabmTcInf,0,sizeof(RABM_TC_INF_STRU));
    for (i = 0; i < TC_LB_MAX_RBNUM; i++)
    {
        g_RabmTcInf.aRbInf[i].bRlcSduSizeValid = VOS_TRUE;
    }

    g_RabmRrcImportFunc.RrRabmRabInfoRsp = As_RabInfoRsp;
    g_RabmRrcImportFunc.RrRabmRabQosUpdate = As_RabQosUpdate;

    gRabm3GTo2GSwitch   = RABM_3G_TO_2G_SWITCH_OFF;       /*3G到2G切换标识的初始化*/
    gRabm3GTo2GT1Switch = RABM_3G_TO_2G_T1_OFF;           /*Rabm.3To2.T1定时器是否启动标识的初始化*/
    /*初始化3G中记录切换前所处状态的数组*/

    g_ulNasRabmResendEstTimer                      = NAS_RABM_TIMER_STATUS_STOP;

    gRabm2GTo3GDataResume = VOS_FALSE;

    g_ulRabReestTimerId = VOS_NULL_PTR;

    /*TC环回模式所使用的队列初始化*/
    RABM_TcDataQInit();

    /*上下文初始化*/
    NAS_RABM_InitFastDormCtx();

#if (FEATURE_ON == FEATURE_HUAWEI_VP)
    NAS_RABM_InitVoicePreferCtx();
#endif
}


VOS_VOID NAS_RABM_SetRbProtectTmrLen(VOS_UINT32 ulTmrLen)
{
    NAS_RABM_SET_RAB_PENDING_TMR_LEN(ulTmrLen);

    return;
}


VOS_VOID RABM_TimerStart(
    VOS_UINT8                           ucTimerId,
    VOS_UINT32                          ulTimerLen
)
{
    /*启动定时器*/
    if(VOS_OK != NAS_StartRelTimer(&g_ulRabReestTimerId,
                                   WUEPS_PID_RABM,
                                   ulTimerLen,
                                   (VOS_UINT32)ucTimerId,
                                   RABM_TIMER_PARA_REESTRAB_TIMER,
                                   VOS_RELTIMER_NOLOOP))
    {
        PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL,  PS_LOG_LEVEL_ERROR, "RABM_TimerStart:ERROR:Timer Start Failure!");
        return;
    }

    g_ucReestTimerFlg = RABM_TRUE;
    PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_INFO, "RABM_TimerStart:INFO:RABM TimerStart: RabReestTimer");

}

/*******************************************************************************
  Module:   RABM_TimerStop
  Function: 停止Timer
  Input:    VOS_UINT8   ucTimerId
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
      1.   张志勇      2003.12.09   新规作成
*******************************************************************************/
VOS_VOID RABM_TimerStop(
                    VOS_UINT8  ucTimerId
                    )
{
    if( VOS_OK != NAS_StopRelTimer(WUEPS_PID_RABM, RABM_TIMER_PARA_REESTRAB_TIMER, &g_ulRabReestTimerId ) )
    {
        PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_WARNING, "RABM_TimerStop:WARNING:Timer Stop Failure!" );
        return;
    }

    PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_INFO, "RABM_TimerStop:INFO:RABM TimerStop: RabReestTimer");
}

/******************************************************************************
 * 函数名称 ： WuepsRabmPidInit
 * 功能描述 ： WUEPS RABM PID的初始化函数
 * 参数说明 ： 无
 * 备    注 ：
 * 返 回 值 ： VOS_UINT32 初始化结果：
 *             0  : 成功
 *             非0: 失败
 *
 * 变更历史 ：
 *           No.  姓名      变更                                    日   期
 *           1    张志勇    新建                                   2005.02.24
 *****************************************************************************/
VOS_UINT32 WuepsRabmPidInit ( enum VOS_INIT_PHASE_DEFINE ip )
{
    /* VOS_UINT32 ulReturnCode = VOS_OK;  A32D00461,zzy,pclint */
    switch( ip )
    {
    case VOS_IP_LOAD_CONFIG:
        NAS_RABM_CtxInit();
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


VOS_UINT32 WuepsRabmFidInit ( enum VOS_INIT_PHASE_DEFINE ip )
{
    VOS_UINT32 ulReturnCode;
    switch( ip )
    {
    case   VOS_IP_LOAD_CONFIG:
        ulReturnCode = VOS_RegisterPIDInfo(WUEPS_PID_RABM,
                                (Init_Fun_Type) WuepsRabmPidInit,
                                (Msg_Fun_Type) NAS_RABM_MsgProc);
        if( VOS_OK != ulReturnCode )
        {
            PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_WARNING,
                "WuepsRabmFidInit:WARNING:VOS_OK != ulReturnCode ");
            return VOS_ERR;
        }

        ulReturnCode = VOS_RegisterPIDInfo(WUEPS_PID_SM,
                              (Init_Fun_Type) WuepsSmPidInit,
                                  (Msg_Fun_Type) Sm_TaskEntry  );
        if( VOS_OK != ulReturnCode )
        {
            PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING,
                "WuepsRabmFidInit:WARNING:VOS_OK != ulReturnCode ");
            return VOS_ERR;
        }

        ulReturnCode = VOS_RegisterMsgTaskPrio(WUEPS_FID_RABMSM, VOS_PRIORITY_M1);
        if( VOS_OK != ulReturnCode )
        {
            PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_WARNING,
                "WuepsRabmFidInit:WARNING:VOS_OK != ulReturnCode ");
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

/*lint +e958*/

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

