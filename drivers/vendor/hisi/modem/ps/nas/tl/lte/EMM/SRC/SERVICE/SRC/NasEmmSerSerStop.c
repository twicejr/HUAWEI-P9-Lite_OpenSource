/*******************************************************************************
  Copyright     : 2005-2007, Huawei Tech. Co., Ltd.
  File name     : EmmService.c
  Description   : EMM SERVICE REQUEST功能相关处理用源文件
  Function List :

  History       :
    1.  Zhouyan 00125190  2008.09.10  新规作成
    2.  leili       00132387    2009.06.25   BJ9001269 收到系统消息后处理优化
*******************************************************************************/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include "NasEmmTauSerInclude.h"
#include "NasLmmPubMStack.h"

#include "NasEmmPubUSuspend.h"
#if (FEATURE_LPP == FEATURE_ON)
#include "NasEmmLppMsgProc.h"
#include "EmmLppInterface.h"
#include    "NasEmmSsMsgProc.h"
#include    "NasEmmSerProc.h"
#endif

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASEMMSERVICESERSTOP_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASEMMSERVICESERSTOP_C
/*lint +e767*/


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/



/*******************************************************************************
  Module   :
  Function :NAS_EMM_MsSerInitMsgRabmDrbSetupInds
  Input    :
  Output   :
  NOTE     :
  Return   :
  History  :
    1.  Zhouyan 00125190  2008.09.10  新规作成
*******************************************************************************/
VOS_UINT32 NAS_EMM_MsSerInitMsgRabmDrbSetupInd(VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru)
{
    VOS_UINT32                      ulRslt                  = NAS_EMM_FAIL;

    (VOS_VOID)ulMsgId;

    /* 打印进入该函数， INFO_LEVEL */
    NAS_EMM_SER_LOG_INFO( "NAS_EMM_MsSerInitMsgRabmDrbSetupInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsSerInitMsgRabmDrbSetupInd_ENUM,LNAS_ENTRY);

    /* 函数输入指针参数检查, 状态匹配检查,若不匹配,退出*/
    ulRslt = NAS_EMM_SER_CHKFSMStateMsgp(EMM_MS_SER_INIT,EMM_SS_SER_WAIT_CN_SER_CNF,pMsgStru);
    if ( NAS_EMM_SUCC != ulRslt )
    {
        /* 打印异常 */
        NAS_EMM_SER_LOG_WARN("NAS_EMM_TAUSER_CHKFSMStateMsgp ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsSerInitMsgRabmDrbSetupInd_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    /*调用消息处理函数*/
    NAS_EMM_SER_RcvRabmDrbSetupInd(pMsgStru);

    return NAS_LMM_MSG_HANDLED;
}


VOS_VOID NAS_EMM_SER_SndEsmBufMsg( VOS_VOID )
{
    EMM_ESM_DATA_REQ_STRU                *pstMsg = NAS_LMM_NULL_PTR;
    VOS_UINT32                            i      = 0;
    VOS_UINT32                            ulRslt = 0;
    VOS_UINT32                            ulCurEmmStat;

    ulCurEmmStat = NAS_LMM_PUB_COMP_EMMSTATE(NAS_EMM_CUR_MAIN_STAT, NAS_EMM_CUR_SUB_STAT);
    if ((ulCurEmmStat != NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_NORMAL_SERVICE))
        && (ulCurEmmStat != NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM)))
    {
        NAS_EMM_SER_LOG_INFO( "NAS_EMM_SER_SndEsmBufMsg:state is not allowed to send msg.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_SndEsmBufMsg_ENUM,LNAS_FUNCTION_LABEL1);

        NAS_EMM_SerClearEsmDataBuf();
        return ;
    }

    for (i = 0; i < g_stEmmEsmMsgBuf.ulEsmMsgCnt; i++)
    {
       pstMsg = (EMM_ESM_DATA_REQ_STRU *)g_stEmmEsmMsgBuf.apucEsmMsgBuf[i];

       /*发ESM消息*/
       NAS_EMM_SER_SendMrrcDataReq_ESMdata(&pstMsg->stEsmMsg, pstMsg->ulOpId);
       ulRslt = NAS_COMM_FreeBuffItem(NAS_COMM_BUFF_TYPE_EMM, pstMsg);

       if (NAS_COMM_BUFF_SUCCESS != ulRslt)
       {
           NAS_EMM_SER_LOG_WARN("NAS_EMM_SER_RcvRabmDrbSetupInd, Memory Free is not succ");
           TLPS_PRINT2LAYER_WARNING(NAS_EMM_SER_SndEsmBufMsg_ENUM,LNAS_FUNCTION_LABEL2);

       }

       g_stEmmEsmMsgBuf.apucEsmMsgBuf[i] = NAS_LMM_NULL_PTR;
    }

    g_stEmmEsmMsgBuf.ulEsmMsgCnt = 0;
}


/*******************************************************************************
  Module   : NAS_EMM_SER_RcvRabmDrbSetupInd
  Function : 收到EMM_ERABM_DRB_SETUP_IND原语后的处理
  Input    : VOS_VOID *pMsg     原语首地址
  Output   : 无
  NOTE     : 无
  Return   : VOS_UINT32
  History  :
    1.  Zhouyan 00125190     2008.09.09  新规作成
    2.  lihong 00150010      2009-06-23  Modify
    3.  lihong 00150010      2012-12-18  Modify:Emergency
    4.  leixinatiao 00258641 2015-07-23 关键信息上报
*******************************************************************************/
VOS_VOID    NAS_EMM_SER_RcvRabmDrbSetupInd(const VOS_VOID   *pMsgStru)
{
    NAS_LMM_OM_TAU_START_TYPE_ENUM_UINT32 enTauStartType = NAS_LMM_OM_TAU_START_TYPE_OTHERS;
    (VOS_VOID)pMsgStru;

    /* 协议规定EXTENDED SERVICE流程成功终止的标识是异系统变换，而不是DRB建立 */
    if (VOS_TRUE == NAS_EMM_SER_IsCsfbProcedure())
    {
        /*转换安全上下文状态*/
        NAS_EMM_SecuStateConvert(   EMM_CUR_SECU_EXIST_ACTIVE,
                                    NAS_LMM_GetSecuCurFsmNS());

        return ;
    }
    /* 大数据: 更新SER成功次数 */
    NAS_LMM_AddSerCounter(NAS_LMM_OM_PCE_TIMES_TYPE_SUCC);
    /* 大数据: 记录Ser流程结束时间 */
    NAS_EMM_SaveSerEndTimeStamp();
    /*停止定时器3417*/
    NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417);

    /*转换安全上下文状态*/
    NAS_EMM_SecuStateConvert(   EMM_CUR_SECU_EXIST_ACTIVE,
                                NAS_LMM_GetSecuCurFsmNS());

    /*设置SER的结果为NAS_EMM_SER_RESULT_SUCC*/
    /*NAS_EMM_SER_SaveSERresult(NAS_EMM_SER_RESULT_SUCC);*/
    /*SR流程成功后，如果SR流程是由于SMS触发，需要回复SMS建链成功*/
    if(NAS_EMM_SER_START_CAUSE_SMS_EST_REQ == NAS_EMM_SER_GetSerStartCause())
    {
        NAS_LMM_SndLmmSmsEstCnf();
        NAS_LMM_SetConnectionClientId(NAS_LMM_CONNECTION_CLIENT_ID_SMS);
    }

    #if (FEATURE_LPP == FEATURE_ON)
    if(NAS_EMM_SER_START_CAUSE_LPP_EST_REQ == NAS_EMM_SER_GetSerStartCause())
    {
        NAS_EMM_SendLppEstCnf(LMM_LPP_EST_RESULT_SUCC);
        NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_BUTT);
    }

    if(NAS_EMM_SER_START_CAUSE_SS_EST_REQ == NAS_EMM_SER_GetSerStartCause())
    {
        NAS_LMM_SndLmmLcsEstCnf( LMM_LCS_EST_RSLT_SUCC,
                                NAS_EMM_SER_GetSsOrLppOpid());
        NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_BUTT);
    }
    #endif

    NAS_EMM_TranStatePsNormalServiceOrPsLimitService();

    /* 发送缓存的ESM消息*/
    NAS_EMM_SER_SndEsmBufMsg();

    NAS_EMM_SER_ClearResource();

    /* 清除RRC链路释放触发TAU的原因 */
    /*NAS_LMM_SetEmmInfoTriggerTauRrcRel(NAS_EMM_TRIGGER_TAU_RRC_REL_NO);*/

    NAS_LMM_SetEmmInfoT3412ExpCtrl(NAS_EMM_T3412_EXP_NO);

    /* 美国AT&T定制需求: SER成功清除CService计数 */
    NAS_EMM_GetEmmInfoDamParaCserviceCnt() = 0;

    NAS_LMM_StopPtlTimer( TI_NAS_EMM_PTL_SER_BACKOFF_TIMER);

    /*转换EMM状态机MS_REG+SS_REG_NORMAL_SERVIC*/
    /*NAS_EMM_TAUSER_FSMTranState(EMM_MS_REG, EMM_SS_REG_NORMAL_SERVICE, TI_NAS_EMM_STATE_NO_TIMER);*/

    /*如果有参数变更引起或者承载个数变化的TAU未完成，则触发带TAU
      注:该场景一定是连接态下触发TAU，不需要判断上行阻塞*/
    if (NAS_EMM_YES == NAS_EMM_SER_SuccNeedtoContinueTau(&enTauStartType))
    {
        NAS_EMM_SER_LOG_INFO( "NAS_EMM_SER_RcvRabmDrbSetupInd: Need to Continue Tau");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_RcvRabmDrbSetupInd_ENUM,LNAS_FUNCTION_LABEL1);

        if(NAS_LMM_TIMER_STOPED == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_T3411))
        {
            /* 新增入参TAU发起原因 */
            NAS_EMM_TAU_StartTAUREQ(enTauStartType);
        }
    }
    else
    {
        if (NAS_EMM_YES != NAS_EMM_TAU_CanTriggerComTauWithIMSI())
        {
            /* 当RRC建链失败触发的TAU失败，T3411正在运行的时候，service成功，此时就不用再发起TAU，
            另外的，LMM需要给MMC发一个假TAU成功的消息，通知MMC当前TAU已经成功，以便MMC更新状态*/
            if(NAS_EMM_TRIGGER_TAU_RRC_REL_NO != NAS_LMM_GetEmmInfoTriggerTauRrcRel())
            {
                NAS_EMM_SER_LOG_INFO( "NAS_EMM_SER_RcvRabmDrbSetupInd: send tau result");
                NAS_EMM_MmcSendTauActionResultIndSuccWithoutPara();
            }
            NAS_LMM_SetEmmInfoTriggerTauRrcRel(NAS_EMM_TRIGGER_TAU_RRC_REL_NO);

            /*清除TAU资源，注意:与NAS_EMM_SER_SndEsmBufMsg的执行顺序不能颠倒*/
            NAS_EMM_TAU_ClearResouce();

        }

    }


    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_PreProcMsgMmCsfbSerAbortNotify
 Description     : 预处理MM的CSFB ABORT请求消息
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong        00150010      2012-02-27  Draft Enact
    2.leixiantiao   00258641      2015-07-09  fix DTS2015062509266

*****************************************************************************/
/*lint -e960*/
/*lint -e961*/
VOS_UINT32  NAS_EMM_PreProcMsgMmCsfbSerAbortNotify( MsgBlock * pMsg )
{
    VOS_UINT32                          ulCurEmmStat    = NAS_EMM_NULL;
    /*VOS_UINT32                          ulStaAtStackBase= NAS_EMM_NULL;*/

    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_PreProcMsgMmCsfbSerAbortNotify is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgMmCsfbSerAbortNotify_ENUM,LNAS_ENTRY);

    (VOS_VOID)pMsg;

    /* 记录CSFB ABORT标识 */
    NAS_EMM_SER_SaveEmmSerCsfbAbortFlag(NAS_EMM_CSFB_ABORT_FLAG_VALID);

    /* 如果CSFB时延定时器在运行，中止CSFB流程，如果已经发起TAU或SER，到流程完成时用ABORT标识进行处理 */
    NAS_LMM_StopPtlTimer(TI_NAS_EMM_PTL_CSFB_DELAY);

    /*问题背景:主叫走CSFB流程被用户快速挂断电话，此时走CSFB回退流程，
    回退到L的时候，由于TA在TALIST里面，所以不会发起TAU跟网侧交互，但是
    此时核心网PS域已经开始往2/3G迁移，这样会导致被叫不通，或者收不到短信
    改动:增加标识维护识别上面的这种场景，在回到L的时候保证发起TAU*/
    /*设置当前是EU值在csfb流程标识为真的情况下才置*/
    if(PS_TRUE == NAS_EMM_GetCsfbProcedureFlag())
    {
        NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_NOT_UPDATED_EU2);
        NAS_EMM_SetCsfbProcedureFlag(PS_FALSE);
    }

    ulCurEmmStat = NAS_LMM_PUB_COMP_EMMSTATE(   NAS_EMM_CUR_MAIN_STAT,
                                                NAS_EMM_CUR_SUB_STAT);

    /* MM终止CSFB流程,通知LRRC CSFB流程终止,LRRC收到该消息后,若等待网侧释放定时器启动时,停止定时器 */
    NAS_EMM_SndLrrcLmmCsfbNotify(LRRC_LNAS_CSFB_STATUS_END);

    /* 如果LMM当前状态为建链过程中时，状态为是SERVICE_INIT+WAIT_SER_CN_CNF，
       且是CSFB流程时，终止CSFB流程，给RRC发链路释放请求；其他情况则记录
       ABORT标识 */
    if(NAS_EMM_CONN_ESTING == NAS_EMM_GetConnState())
    {
        NAS_LMM_PUBM_LOG_INFO("NAS_EMM_PreProcMsgMmCsfbSerAbortNotify: esting.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgMmCsfbSerAbortNotify_ENUM,LNAS_FUNCTION_LABEL1);

        if ((ulCurEmmStat == NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_SER_INIT,EMM_SS_SER_WAIT_CN_SER_CNF))
            && (VOS_TRUE == NAS_EMM_SER_IsCsfbProcedure()))
        {
            NAS_LMM_PUBM_LOG1_INFO("NAS_EMM_PreProcMsgMmCsfbSerAbortNotify: SubState =",
                                EMM_SS_SER_WAIT_CN_SER_CNF);
            TLPS_PRINT2LAYER_INFO1(NAS_EMM_PreProcMsgMmCsfbSerAbortNotify_ENUM,LNAS_EMM_SUB_STATE,
                                EMM_SS_SER_WAIT_CN_SER_CNF);

            NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417_EXT);

            NAS_EMM_TAUSER_FSMTranState(EMM_MS_REG,
                                        EMM_SS_REG_NORMAL_SERVICE,
                                        TI_NAS_EMM_STATE_NO_TIMER);

            /* 请求RRC链路释放 */
            NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);
        }
    }
    /* 若状态是 EMM_MS_SUSPEND + EMM_SS_SUSPEND_RRCORI_WAIT_OTHER_SUSPEND */
    else if (ulCurEmmStat ==
                NAS_LMM_PUB_COMP_EMMSTATE(  EMM_MS_SUSPEND,
                                            EMM_SS_SUSPEND_RRCORI_WAIT_OTHER_SUSPEND))
    {
        NAS_LMM_PUBM_LOG_INFO("NAS_EMM_PreProcMsgMmCsfbSerAbortNotify: WAIT_OTHER_SUSPEND.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgMmCsfbSerAbortNotify_ENUM,LNAS_FUNCTION_LABEL1);

        /* 停止定时器 */
        NAS_LMM_StopStateTimer(TI_NAS_EMM_RRCORI_WAIT_OTHER_SUSPEND_RSP_TIMER);

        /* 清除此次挂起的上层响应记录，恢复过程将使用 */
        NAS_EMM_GetUplayerCount() = NAS_EMM_SUSPEND_UPLAYER_NUM_INITVALUE;
        /* 给LRRC回复SUSPEND RSP(SUCC)，解决LRRC收到SUSPEND REL REQ停止挂起流程，重新搜网驻留后不上报RESUME IND问题 */
        /* 发送 LRRC_LMM_SUSPEND_RSP*/
        NAS_EMM_SendLrrcSuspendRsp(LRRC_LNAS_SUCC);

        /*发送LRRC_LMM_SUSPEND_REL_REQ消息*/
        NAS_EMM_SndLrrcSuspendRelReq();


        NAS_EMM_SetSuspendRelCause(NAS_EMM_SUSPEND_REL_CAUSE_ABORT_CSFB);
        NAS_LMM_PUBM_LOG1_INFO("NAS_EMM_PreProcMsgMmCsfbSerAbortNotify: SuspendRelCause =",
                                NAS_EMM_SUSPEND_REL_CAUSE_ABORT_CSFB);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_PreProcMsgMmCsfbSerAbortNotify_ENUM,LNAS_CAUSE_NUMBER,
                                NAS_EMM_SUSPEND_REL_CAUSE_ABORT_CSFB);

        /* 状态迁移*/
        NAS_EMM_PUBU_FSMTranState(      EMM_MS_SUSPEND,
                                        EMM_SS_SUSPEND_WAIT_END,
                                        TI_NAS_EMM_WAIT_SUSPEND_END_TIMER);

    }

    /* 若状态是 EMM_MS_SUSPEND + EMM_SS_SUSPEND_WAIT_END */
    else if (ulCurEmmStat == NAS_LMM_PUB_COMP_EMMSTATE(  EMM_MS_SUSPEND,
                                                    EMM_SS_SUSPEND_WAIT_END))
    {
        NAS_LMM_PUBM_LOG_INFO("NAS_EMM_PreProcMsgMmCsfbSerAbortNotify: SUSPEND_WAIT_END.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgMmCsfbSerAbortNotify_ENUM,LNAS_FUNCTION_LABEL2);

        /*发送LRRC_LMM_SUSPEND_REL_REQ消息*/
        NAS_EMM_SndLrrcSuspendRelReq();

        NAS_EMM_SetSuspendRelCause(NAS_EMM_SUSPEND_REL_CAUSE_ABORT_CSFB);
        NAS_LMM_PUBM_LOG1_INFO("NAS_EMM_PreProcMsgMmCsfbSerAbortNotify: SuspendRelCause =",
                                NAS_EMM_SUSPEND_REL_CAUSE_ABORT_CSFB);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_PreProcMsgMmCsfbSerAbortNotify_ENUM,LNAS_CAUSE_NUMBER,
                                NAS_EMM_SUSPEND_REL_CAUSE_ABORT_CSFB);


    }
    else
    {
        NAS_LMM_PUBM_LOG_INFO("NAS_EMM_PreProcMsgMmCsfbSerAbortNotify: no other action.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgMmCsfbSerAbortNotify_ENUM,LNAS_FUNCTION_LABEL3);
    }

    return NAS_LMM_MSG_HANDLED;
}
/*lint +e961*/
/*lint +e960*/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif




