

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include "NasEmmPubUSuspend.h"
#include "NasLmmPublic.h"
#include "NasLmmPubMOsa.h"
#include "NasEmmPubUGlobal.h"
#include "NasEmmAttDetInterface.h"
#include "NasEmmTauInterface.h"
#include "NasEmmMrrcPubInterface.h"
#include "NasEmmSecuInterface.h"
#include "NasEmmSerInterface.h"
#include "NasLmmPubMTimer.h"
#include "NasEmmPlmnInterface.h"
#include "NasEmmPlmn.h"
#include "NasLmmPubMEntry.h"
#include "NasEmmPubUEntry.h"
#include "NasEmmAttDetInclude.h"
#include "NasEmmPubUResume.h"
#include "NasMmlCtx.h"
#include "NasEmmcPublic.h"
#if (FEATURE_LPP == FEATURE_ON)
#include    "NasEmmLppMsgProc.h"
#include    "EmmLppInterface.h"
#include    "NasEmmSsMsgProc.h"
#include    "NasEmmSerProc.h"
#endif



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

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASEMMPUBSUSPEND_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASEMMPUBSUSPEND_C
/*lint +e767*/

/*****************************************************************************
  3 Function
*****************************************************************************/
/*****************************************************************************
 Function Name   : NAS_EMM_ProcInterSystemTransferBearerInfo
 Description     : 异系统变换时存在ISR激活后承载，去激活ISR
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.leili 00132387      2011-11-30  Draft Enact

*****************************************************************************/
/*lint -e960*/
/*lint -e961*/
VOS_VOID  NAS_EMM_ProcInterSystemTransferBearerInfo(VOS_VOID)
{
    NAS_MML_PS_BEARER_CONTEXT_STRU      *pstPsBearerCtx = NAS_EMM_NULL_PTR;

    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_ProcInterSystemTransferBearerInfo is entry");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcInterSystemTransferBearerInfo_ENUM,LNAS_ENTRY);

    pstPsBearerCtx = NAS_EMM_GetPsBearerCtx();

    /*存在ISR激活后承载,去激活ISR,更新所有承载的ISR标识为激活前*/
    if ((MMC_LMM_TIN_RAT_RELATED_TMSI == NAS_EMM_GetTinType()) &&
        (NAS_EMM_SUCC == NAS_EMM_IsBearIsrActAfter()))
    {
         /*更新TIN值为P-TMSI*/
        NAS_EMM_SetTinType(MMC_LMM_TIN_P_TMSI);
        /*更新所有承载的ISR标识为ISR激活前*/
        NAS_EMM_UpdateBearISRFlag(pstPsBearerCtx);
        NAS_EMM_PUBU_LOG_INFO("NAS_EMM_ProcInterSystemTransferBearerInfo: UPDATE MML PS BEARER INFO:");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcInterSystemTransferBearerInfo_ENUM,LNAS_FUNCTION_LABEL2);

        NAS_LMM_LogPsBearerCtxInfo(pstPsBearerCtx);
    }

    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_PreProcMsgMmcSuspendReq
 Description     : 收到MMC的挂起请求消息。各状态下的处理同收到RRC的挂起消息。

 MMC搜索其他模式的小区，通过该原语挂起L模；
 LMM收到此消息后，通知ESM和ERABM挂起，再给LRRC发送SUSPEND_REQ消息，通知LRRC处于挂起状态；
 LMM收到此消息后的状态等同于LMM收到LRRC上报的挂起消息后的状态；
 约束：
 1）LMM处于空闲态，则MMC可直接下发MMC_LMM_SUSPEND_REQ命令挂起LMM;
 2）LMM处于信令连接态，则MMC需要先下发MMC_LMM_REL_REQ命令释放LMM的信令连接，使LMM进入空闲态，然后再下发MMC_LMM_SUSPEND_REQ命令挂起LMM；
 3）LMM处于数据连接态，则MMC不能将LMM挂起；；
 4）LMM如果在信令连接态或者数据连接态下收到MMC_LMM_SUSPEND_REQ命令，则LMM直接丢弃;
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.HanLufeng 41410      2011-4-26  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_PreProcMsgMmcSuspendReq( MsgBlock * pMsg )
{
    (VOS_VOID)pMsg;

    NAS_EMM_PUBU_LOG2_INFO("NAS_EMM_PreProcMsgMmcSuspendReq: enter.  NAS_EMM_CUR_MAIN_STAT = ,CONN_STATE = ",
                            NAS_EMM_CUR_MAIN_STAT,
                            NAS_EMM_GetConnState());
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_PreProcMsgMmcSuspendReq_ENUM,LNAS_EMM_MAIN_STATE,
                            NAS_EMM_CUR_MAIN_STAT);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_PreProcMsgMmcSuspendReq_ENUM,LNAS_EMM_CONN_STATE,
                            NAS_EMM_GetConnState());
    /* 出现这种场景，一般是L上报进入链接态和MMC的挂起消息对冲，但是RRC支持在链接态下处理NAS的挂起请求，
    在SYSCFGEX命令实现时已支持。因此取消对MMC不能在链接态挂起L模的限制，而是按正常MMC挂起流程处理*/

    NAS_LMM_EstingOrReleasingProcessTimerHandle();

    switch(NAS_EMM_CUR_MAIN_STAT)
    {
        case    EMM_MS_AUTH_INIT:

            NAS_LMM_IfEmmHasBeenPushedThenPop();
            NAS_EMM_PUBU_LOG_INFO(" NAS_EMM_PreProcMsgMmcSuspendReq enter");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgMmcSuspendReq_ENUM,LNAS_ENTRY);
            break;

        default:
            NAS_EMM_PUBU_LOG_INFO(" NAS_EMM_PreProcMsgMmcSuspendReq enter");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgMmcSuspendReq_ENUM,LNAS_ENTRY);
            break;
    }
    switch(NAS_EMM_CUR_MAIN_STAT)
    {
        case    EMM_MS_NULL:
                 /* 开机过程、关机过程中收到，给MMC回复挂起失败 */
                NAS_EMM_PUBU_LOG_INFO(" NAS_EMM_SendMmcSuspendCnf( MMC_LMM_FAIL )");
                TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgMmcSuspendReq_ENUM,LNAS_FAIL);
                NAS_EMM_SendMmcSuspendCnf( MMC_LMM_FAIL );
                break;

        case    EMM_MS_SUSPEND:
                /* MMC重复发送挂起消息，做丢弃处理，因为LNAS后面必然会给MMC回复 */
                if ( EMM_SS_SUSPEND_MMCORI_WAIT_OTHER_SUSPEND == NAS_LMM_GetEmmCurFsmSS())
                {
                    return NAS_LMM_MSG_HANDLED;
                }
                else if (EMM_SS_SUSPEND_RRCORI_WAIT_MMC_SUSPEND == NAS_LMM_GetEmmCurFsmSS())
                {
                    NAS_EMM_ValidStateMsgMmcSuspendReq(NAS_EMM_GetStateBeforeSuspendAddr());
                }
                else
                {
                    /* RRC挂起NAS,已经收到MMC的挂起响应或者SYSCFGEX命令导致挂起，已经给ESM和ERABM
                    发送过挂起消息，所以不需要重复发送 */
                    /* 清空各流程全局变量。同时，除了T3412和T3423，停止其他协议状态定时器, */
                    NAS_EMM_SuspendInitRelResource();

                    /* 不停止3412定时器 */

                    NAS_LMM_SetEmmInfoTriggerTauSysChange(NAS_EMM_NO);
                    /* del by y00307272 for DTS2015122301277 ,2015-12-26，Begin */
                    /* DEL CAUSE:csfb到G下，挂起ps并通知LNAS，随后电话挂断后FR失败，回退到G下丢网，搜L
                     失败，搜W失败(搜时MMC会给LNAS发挂起，我们这是会设置ps not suspension)，在搜到L判断
                     PS没有挂起，不发TAU，被叫失败 */
                    /*NAS_LMM_SetEmmInfoPsState(GMM_LMM_GPRS_NOT_SUSPENSION);*/
                    /* del by y00307272 for DTS2015122301277 ,2015-12-26，End */
                    NAS_EMM_ProcInterSystemTransferBearerInfo();

                    /* 记录挂起的参数: 挂起源 */
                    NAS_EMM_SetSuspendOri(NAS_LMM_SYS_CHNG_ORI_MMC);

                    /* EMM状态迁移, 并启动定时器*/
                    NAS_EMM_PUBU_FSMTranState(  EMM_MS_SUSPEND,
                                                EMM_SS_SUSPEND_MMCORI_WAIT_OTHER_SUSPEND,
                                                TI_NAS_EMM_MMCORI_WAIT_OTHER_SUSPEND_RSP_TIMER);
                }
                break;

        case    EMM_MS_RESUME:
                /*RESUME过程中收到MMC挂起消息的处理*/
                NAS_EMM_ProcMsResumeMsgMmcSuspendReq();
                break;

        default  :
                /* 其他状态，进入各状态处理:
                保存当前状态，清空部分变量, 给ESM/ERABM/LRRC发送挂起请求消息， */
                NAS_EMM_PUBU_LOG_INFO(" NAS_EMM_ValidStateMsgMmcSuspendReq");
                TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgMmcSuspendReq_ENUM,LNAS_FUNCTION_LABEL1);
                NAS_EMM_ValidStateMsgMmcSuspendReq(NAS_LMM_GetCurFsmAddr(NAS_LMM_PARALLEL_FSM_EMM));
                break;
    }


    return NAS_LMM_MSG_HANDLED;
}


/*****************************************************************************
 Function Name   : NAS_EMM_ValidStateMsgMmcSuspendReq
 Description     : 有效状态下处理MMC的挂起消息

 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.HanLufeng 41410      2011-4-28  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_ValidStateMsgMmcSuspendReq
(
    NAS_LMM_FSM_STATE_STRU *pstState
)
{
    (void) pstState;
    NAS_EMM_PUBU_LOG2_INFO(" NAS_EMM_ValidStateMsgMmcSuspendReq:pstState->enMainState,pstState->enSubState",
                            pstState->enMainState,
                            pstState->enSubState);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_ValidStateMsgMmcSuspendReq_ENUM,LNAS_EMM_MAIN_STATE,
                            pstState->enMainState);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_ValidStateMsgMmcSuspendReq_ENUM,LNAS_EMM_SUB_STATE,
                            pstState->enSubState);

    /* 清空各流程全局变量。同时，除了T3412和T3423，停止其他协议状态定时器, */
    NAS_EMM_SuspendInitRelResource();

    /* 不停止3412定时器 */

    NAS_LMM_SetEmmInfoTriggerTauSysChange(NAS_EMM_NO);

    /* del by y00307272 for DTS2015122301277 ,2015-12-26，Begin */
    /* DEL CAUSE:csfb到G下，挂起ps并通知LNAS，随后电话挂断后FR失败，回退到G下丢网，搜L
     失败，搜W失败(搜时MMC会给LNAS发挂起，我们这是会设置ps not suspension)，在搜到L判断
     PS没有挂起，不发TAU，被叫失败 */
    /*NAS_LMM_SetEmmInfoPsState(GMM_LMM_GPRS_NOT_SUSPENSION);*/
    /* del by y00307272 for DTS2015122301277 ,2015-12-26，End */
    NAS_EMM_ProcInterSystemTransferBearerInfo();
    /* 记录挂起前的状态*/
    NAS_LMM_MEM_CPY_S(  NAS_EMM_GetStateBeforeSuspendAddr(),
                        sizeof(NAS_LMM_FSM_STATE_STRU),
                        pstState,
                        sizeof(NAS_LMM_FSM_STATE_STRU));

    /* 记录挂起的参数: 挂起源 */
    NAS_EMM_SetSuspendOri(NAS_LMM_SYS_CHNG_ORI_MMC);
    /* 清除挂起类型，解决问题:发生L2GU HO时,挂起类型置为HO,当HO失败回退到L时,由于挂起类型未被清除,
        当L下发生丢网, MMC挂起LMM,LMM给ERABM发送ID_EMM_ERABM_SUSPEND_IND消息中携带的挂起类型为HO,
        而ERABM在处理HO类型的挂起时会把所有承载的DRB状态状态置为挂起态,导致后续L上数传不通*/
    NAS_EMM_SetSuspendType(LRRC_LMM_SYS_CHNG_TYPE_BUTT);
    /* 进入IDLE态*/
    /*NAS_EMM_MrrcChangeRrcStatusToIdle();*/

    /* 发送 ESM 挂起消息*/
    NAS_EMM_SendEsmSuspendInd();

    /* 发送 ERABM 挂起消息*/
    NAS_EMM_SendErabmSuspendInd();

    /* EMM状态迁移, 并启动定时器*/
    NAS_EMM_PUBU_FSMTranState(  EMM_MS_SUSPEND,
                                EMM_SS_SUSPEND_MMCORI_WAIT_OTHER_SUSPEND,
                                TI_NAS_EMM_MMCORI_WAIT_OTHER_SUSPEND_RSP_TIMER);

    /* 当前的 LTE为挂起态 */
    NAS_EMM_GetCurLteState() = NAS_LMM_CUR_LTE_SUSPEND;

    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_ProcMsResumeMsgMmcSuspendReq
 Description     : RESUME状态下收到MMC的挂起消息处理
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.leili 00132387      2011-11-30  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_ProcMsResumeMsgMmcSuspendReq(VOS_VOID)
{
    /*RESUME状态下收到MMC的挂起消息处理*/
    NAS_EMM_PUBU_LOG1_INFO("NAS_EMM_ProcMsResumeMsgMmcSuspendReq:NAS_EMM_CUR_SUB_STAT",
            NAS_EMM_CUR_SUB_STAT);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_ProcMsResumeMsgMmcSuspendReq_ENUM,LNAS_EMM_SUB_STATE,
            NAS_EMM_CUR_SUB_STAT);

    if (EMM_SS_RESUME_MMCORI_WAIT_SYS_INFO_IND == NAS_LMM_GetEmmCurFsmSS())
    {
       NAS_EMM_ValidStateMsgMmcSuspendReq(NAS_EMM_GetStateBeforeResumeAddr());
    }
    else
    {
        /*RESUME+RRCORI_WAIT_SYS_INFO和RESUME+RRCRSM_WAIT_OTHER_RESUME的处理*/
        NAS_EMM_ProcRrcOriResumeMsgMmcSuspendReq();
    }

    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_ProcRrcOriResumeMsgMmcSuspendReq
 Description     : RESUME+RRCORI_WAIT_SYS_INFO状态收到MMC挂起消息的处理
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.leili 00132387     2011-11-29  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_ProcRrcOriResumeMsgMmcSuspendReq(VOS_VOID)
{
    NAS_EMM_PUBU_LOG1_INFO(" NAS_EMM_ProcRrcOriResumeMsgMmcSuspendReq:NAS_EMM_GetResumeType()",
                            NAS_EMM_GetResumeType());
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_ProcRrcOriResumeMsgMmcSuspendReq_ENUM,LNAS_EMM_RESUME_TYPE,
                            NAS_EMM_GetResumeType());

    /*RESUME+RRCORI_WAIT_SYS_INFO和RESUME+RRCRSM_WAIT_OTHER_RESUME状态下收到MMC挂起消息的处理*/
    switch (NAS_EMM_GetResumeType())
    {
        case NAS_LMM_SYS_CHNG_TYPE_REVERSE_RSL:
        case NAS_LMM_SYS_CHNG_TYPE_REVERSE_HO:
        case NAS_LMM_SYS_CHNG_TYPE_REVERSE_CCO:
        case NAS_LMM_SYS_CHNG_TYPE_REVERSE_REDIR:
            /* MMC在L2GU回退后等待系统消息定时器超时会下发挂起请求消息*/
            NAS_EMM_ValidStateMsgMmcSuspendReq(NAS_EMM_GetStateBeforeSuspendAddr());
            break;

        default:
            /* GU2L后不应该收到MMC的挂起消息，为了容错也进行了处理*/
            NAS_EMM_ValidStateMsgMmcSuspendReq(NAS_EMM_GetStateBeforeResumeAddr());
            break;
    }
    return;
}
/*****************************************************************************
 Function Name   : NAS_EMM_PreProcMsgRrcSuspendRelCnf
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.HanLufeng 41410      2011-4-26  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_PreProcMsgRrcSuspendRelCnf( MsgBlock * pMsg )
{
    (VOS_VOID)pMsg;

    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_PreProcMsgRrcSuspendRelCnf entred");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgRrcSuspendRelCnf_ENUM,LNAS_ENTRY);

    if(NAS_EMM_SUSPEND_REL_CAUSE_ABORT_CSFB
        == NAS_EMM_GetSuspendRelCause())
    {
        NAS_EMM_PUBU_LOG_INFO("NAS_EMM_PreProcMsgRrcSuspendRelCnf:NO SEND TO MMC");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgRrcSuspendRelCnf_ENUM,LNAS_FUNCTION_LABEL1);
        return  NAS_LMM_MSG_HANDLED;
    }

    /* 通知MMCSuspendRelCnf*/
    NAS_EMM_SendMmcSuspendRelCnf();

    return NAS_LMM_MSG_HANDLED;
}
/*****************************************************************************
 Function Name   : NAS_EMM_PreProcMsgRrcSuspendRelCnf
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.HanLufeng 41410      2011-4-26  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMM_MsRrcConnEstInitRcvLrrcSuspendIndProc(MsgBlock * pMsg)
{
    VOS_UINT32                          ulMsgId = ID_LRRC_LMM_SUSPEND_IND;
    LRRC_LMM_SUSPEND_IND_STRU          *pLrrcLmmSuspendInd;

    pLrrcLmmSuspendInd = (LRRC_LMM_SUSPEND_IND_STRU *)pMsg;

    if(   (LRRC_LMM_SYS_CHNG_TYPE_REDIR       == pLrrcLmmSuspendInd->enSysChngType)
        || (LRRC_LMM_SYS_CHNG_TYPE_CCO_REVERSE == pLrrcLmmSuspendInd->enSysChngType) )
    {   /* 建链过程，如果REDIRECT，或CCO_REVERSE, 则需要处理 */

        NAS_LMM_StopStateTimer(TI_NAS_EMM_MRRC_WAIT_RRC_CONN_CNF);
        NAS_EMM_SecuCurrentContextUpNasCountBack();
        NAS_EMM_CommProcConn2Ilde();
        /* RABM:RRC_CONN_REL_IND*/
        NAS_LMM_SendRabmRrcConRelInd(EMM_ERABM_REL_CAUSE_NULL);

        NAS_LMM_EstingOrReleasingProcessTimerHandle();
        NAS_LMM_IfEmmHasBeenPushedThenPop();
        (VOS_VOID)NAS_EMM_RcvLrrcSuspendInd(ulMsgId, pMsg);
    }
    else
    {   /* 如果是RESEL,则丢弃;
           建链过程中，不会发生CCO, HO,*/
        NAS_EMM_PUBU_LOG_NORM("NAS_EMM_MsRrcConnEstInitRcvLrrcSuspendIndProc: RESEL ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRrcConnEstInitRcvLrrcSuspendIndProc_ENUM,LNAS_FUNCTION_LABEL1);
        NAS_EMM_SendLrrcSuspendRsp(LRRC_LNAS_FAIL);
    }

}



/*****************************************************************************
 Function Name   : NAS_EMM_PreProcMsgRrcSuspendInd
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.HanLufeng 41410      2011-4-26  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_PreProcMsgRrcSuspendInd( MsgBlock * pMsg )
{
    VOS_UINT32                          ulMsgId = ID_LRRC_LMM_SUSPEND_IND;
    VOS_UINT32                          ulRslt;
    LRRC_LMM_SUSPEND_IND_STRU          *pLrrcLmmSuspendInd;

    pLrrcLmmSuspendInd = (LRRC_LMM_SUSPEND_IND_STRU *)pMsg;


    NAS_EMM_PUBU_LOG1_INFO("NAS_EMM_PreProcMsgRrcSuspendInd: discard. enSysChngType = ",
                        pLrrcLmmSuspendInd->enSysChngType);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_PreProcMsgRrcSuspendInd_ENUM,LNAS_FUNCTION_LABEL1,
                        pLrrcLmmSuspendInd->enSysChngType);
    if(NAS_LMM_SYSCFG_FLAG_VALID == NAS_LMM_GetEmmInfoSyscfgCtrl())
    {
        NAS_EMM_PUBU_LOG_NORM("NAS_EMM_PreProcMsgRrcSuspendInd: NAS_LMM_SYSCFG_YES");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgRrcSuspendInd_ENUM,LNAS_FUNCTION_LABEL2);
        /* 给RRC回挂起失败*/
        NAS_EMM_SendLrrcSuspendRsp(LRRC_LNAS_FAIL);
        return NAS_LMM_MSG_HANDLED;
    }
    if(NAS_EMM_PLMN_SRCH_FLAG_VALID == NAS_EMMC_GetPlmnSrchFlag())
    {
        NAS_EMM_PUBU_LOG_NORM("NAS_EMM_PreProcMsgRrcSuspendInd: NAS_EMM_PLMN_SRCH_YES");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgRrcSuspendInd_ENUM,LNAS_FUNCTION_LABEL3);
        /* 给RRC回挂起失败*/
        NAS_EMM_SendLrrcSuspendRsp(LRRC_LNAS_FAIL);
        return NAS_LMM_MSG_HANDLED;
    }
    if(NAS_EMM_CONN_ESTING == NAS_EMM_GetConnState())
    {
        NAS_EMM_MsRrcConnEstInitRcvLrrcSuspendIndProc(pMsg);
        return NAS_LMM_MSG_HANDLED;
    }

    if( (NAS_EMM_CONN_RELEASING == NAS_EMM_GetConnState())
        || (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsStaTimerRunning(TI_NAS_EMM_STATE_T3440))
        || (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_REATTACH_DELAY)))
    {
        NAS_EMM_MsRrcConnRelInitRcvLrrcSuspendIndProc();
        return NAS_LMM_MSG_HANDLED;
    }

    switch(NAS_EMM_CUR_MAIN_STAT)
    {
        case    EMM_MS_NULL:
                /* 给RRC回挂起失败*/
                NAS_EMM_SendLrrcSuspendRsp(LRRC_LNAS_FAIL);
                break;

        case    EMM_MS_SUSPEND:
        case    EMM_MS_RESUME :
                /* 只有在CL多模操作的时候，开机过程、关机过程，挂起、恢复过程中才能收到*/
                /* 给RRC回挂起失败*/
                NAS_EMM_SendLrrcSuspendRsp(LRRC_LNAS_FAIL);
                break;

        case    EMM_MS_AUTH_INIT:
                NAS_EMM_MsAuthInitRcvLrrcSuspendIndProc(pMsg);
                break;

        case    EMM_MS_REG_INIT:
                NAS_EMM_MsRegInitRcvLrrcSuspendIndProc(pMsg);
                break;

        case    EMM_MS_DEREG_INIT:
                NAS_EMM_MsDeregInitRcvLrrcSuspendIndProc(pMsg);
                break;

        case    EMM_MS_REG:

                if ( EMM_SS_REG_IMSI_DETACH_WATI_CN_DETACH_CNF == NAS_LMM_GetEmmCurFsmSS())
                {
                    NAS_LMM_StopStateTimer(          TI_NAS_EMM_T3421);

                    #if (FEATURE_ON == FEATURE_DSDS)
                    /*发送end notify消息给RRC，通知RRC释放资源*/
                    NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_PS_DETACH);
                    #endif

                    NAS_EMM_AdStateConvert( EMM_MS_REG,
                                    EMM_SS_REG_NORMAL_SERVICE,
                                    TI_NAS_EMM_STATE_NO_TIMER);

                    NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
                    NAS_EMM_SendDetRslt(MMC_LMM_DETACH_RSLT_SUCCESS);

                    NAS_LMM_ImsiDetachReleaseResource();
                }

                ulRslt = NAS_EMM_RcvLrrcSuspendInd(ulMsgId, pMsg);
                (VOS_VOID)ulRslt;
                break;
        case    EMM_MS_SER_INIT:
                NAS_EMM_MsSerInitRcvLrrcSuspendIndProc(pMsg);
                break;

        case    EMM_MS_TAU_INIT:
                NAS_EMM_MsTauInitRcvLrrcSuspendIndProc(pMsg);
                break;
        default  :
                /* 其他状态: 保存当前状态，清空部分变量, 给LRRC发送挂起请求消息， */
                ulRslt = NAS_EMM_RcvLrrcSuspendInd(ulMsgId, pMsg);
                (VOS_VOID)ulRslt;
                break;
    }

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_RcvLrrcSuspendInd
 Description     : 已开机完成，并且当前没有压栈的状态下，收到LRRC挂起指示
                   该动作函数暂时不包含有压栈的状态处理

                    MMC    ERABM/ESM        LMM         LRRC
                    |           |           |           |
                    |        SUS_IND        | <-------- |
                    | <---------------------|           |
                    |    SUS_RSP|           |           |
                    |  -------------------> |           |
                    |           |           |-------->  |
                    |           |<--------  |           |
                    |           |<--------  |           |
                    |           | --------> |           |
                    |           | --------> |           |
                    |           |           |           |
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-4-25  Draft Enact
    2.lihong00150010            2011-7-4   Modify
    3.sunli 00180715            2011-7-29  DTS2011080401328
*****************************************************************************/
VOS_UINT32  NAS_EMM_RcvLrrcSuspendInd( VOS_UINT32  ulMsgId,
                                  const VOS_VOID   *pMsgStru  )
{
    LRRC_LMM_SUSPEND_IND_STRU          *pLrrcLmmSuspendInd;

    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_RcvLrrcSuspendInd: enter.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_RcvLrrcSuspendInd_ENUM,LNAS_ENTRY);

    (VOS_VOID)ulMsgId;

    pLrrcLmmSuspendInd = (LRRC_LMM_SUSPEND_IND_STRU *)pMsgStru;

    /* 记录挂起参数 */
    NAS_EMM_SaveLrrcSuspendPara(pLrrcLmmSuspendInd);

    /* 如果SUSPEND类型是HO,更新DL_NASCOUNT*/
    if(   (LRRC_LMM_SYS_CHNG_TYPE_HO == pLrrcLmmSuspendInd->enSysChngType)
       && (NAS_EMM_BIT_SLCT == pLrrcLmmSuspendInd->bitOpHoSecuPara))
    {
        NAS_EMM_PUBU_LOG_INFO("NAS_EMM_RcvLrrcSuspendInd: HO.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RcvLrrcSuspendInd_ENUM,LNAS_FUNCTION_LABEL1);
        NAS_EMM_SecuUpdateDlNasCountHo(
            pLrrcLmmSuspendInd->stHoSecuPara.ucHoSecuPara);
    }

    if (LRRC_LMM_SYS_CHNG_TYPE_CCO_REVERSE == pLrrcLmmSuspendInd->enSysChngType)
    {
        NAS_EMM_CcoInterSystemFailProc();
    }

    /* 通知MMC挂起 */
    NAS_EMM_SendMmcSuspendInd();


    /* EMM状态迁移, 并启动定时器*/
    NAS_EMM_PUBU_FSMTranState(  EMM_MS_SUSPEND,
                                EMM_SS_SUSPEND_RRCORI_WAIT_MMC_SUSPEND,
                                TI_NAS_EMM_RRCORI_WAIT_OTHER_SUSPEND_RSP_TIMER);
    /* 当前的 LTE为挂起态 */
    NAS_EMM_GetCurLteState() = NAS_LMM_CUR_LTE_SUSPEND;

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsSuspendSsRrcOriWaitMmcSuspendMmcSusRsp
 Description     :
                   对LRRC触发的挂起:
                   收到 MMC的挂起响应，再给ESM,ERABM发送挂起消息

 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-4-23  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsSuspendSsRrcOriWaitMmcSuspendMmcSusRsp(VOS_UINT32        ulMsgId,
                                                             VOS_VOID   *pMsgStru   )
{
    MMC_LMM_SUSPEND_RSP_STRU           *pMmcEmmRusRsp   = VOS_NULL_PTR;
    LRRC_LNAS_RESULT_ENUM_UINT32        ulRslt          = LRRC_LNAS_SUCC;

    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;

    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_MsSuspendSsRrcOriWaitMmcSuspendMmcSusRsp: enter. ");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsSuspendSsRrcOriWaitMmcSuspendMmcSusRsp_ENUM,LNAS_ENTRY);

    pMmcEmmRusRsp           = (MMC_LMM_SUSPEND_RSP_STRU*)pMsgStru;

    NAS_LMM_StopStateTimer(TI_NAS_EMM_RRCORI_WAIT_OTHER_SUSPEND_RSP_TIMER);
    /*若MMC响应失败*/
    if ( MMC_LMM_FAIL == pMmcEmmRusRsp->ulRst)
    {
        NAS_EMM_PUBU_LOG1_INFO("NAS_EMM_MsSuspendSsRrcOriWaitMmcSuspendMmcSusRsp fail enter: MMC enRslt = ",
                               pMmcEmmRusRsp->ulRst);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsSuspendSsRrcOriWaitMmcSuspendMmcSusRsp_ENUM,LNAS_FAIL,
                               pMmcEmmRusRsp->ulRst);

        /*恢复状态*/
        NAS_LMM_MEM_CPY_S(  NAS_LMM_GetCurFsmAddr(NAS_LMM_PARALLEL_FSM_EMM),
                            sizeof(NAS_LMM_FSM_STATE_STRU),
                            NAS_EMM_GetStateBeforeSuspendAddr(),
                            sizeof(NAS_LMM_FSM_STATE_STRU));

        /* 当前的 LTE为挂起态 */
        NAS_EMM_GetCurLteState() = NAS_LMM_CUR_LTE_ACTIVE;

        /* 停止挂起ESM,ERABM,将MMC的挂起失败消息转发给LRRC */
        /* 发送 LRRC_LMM_SUSPEND_RSP*/

        ulRslt          = LRRC_LNAS_FAIL;
        NAS_EMM_SendLrrcSuspendRsp(ulRslt);
        NAS_EMM_MsSuspendSsRrcOriWaitMmcSuspendFailProc();
    }
    else if(MMC_LMM_SUCC == pMmcEmmRusRsp->ulRst)
    {
        /* 挂起资源 */
        NAS_EMM_PUBU_LOG_INFO("NAS_EMM_MsSuspendSsRrcOriWaitMmcSuspendMmcSusRsp: succ enter.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsSuspendSsRrcOriWaitMmcSuspendMmcSusRsp_ENUM,LNAS_SUCC);

        /*收到MMC的MMC_LMM_SUSPEND_NOTIFY消息后再清除各模块全局变量*/
        /* 发送 ESM 挂起消息*/
        NAS_EMM_SendEsmSuspendInd();

        /* 发送 ERABM 挂起消息*/
        NAS_EMM_SendErabmSuspendInd();
        /* 停止定时器 */
        NAS_LMM_SuspendInitStopLmmTimer();

        /* EMM状态迁移, 并启动定时器*/
        NAS_EMM_PUBU_FSMTranState(  EMM_MS_SUSPEND,
                                    EMM_SS_SUSPEND_RRCORI_WAIT_OTHER_SUSPEND,
                                    TI_NAS_EMM_RRCORI_WAIT_OTHER_SUSPEND_RSP_TIMER);
    }
    else
    {

    }

    return  NAS_LMM_MSG_HANDLED;
}


/*****************************************************************************
 Function Name   : NAS_EMM_SsRrcOriWaitMmcSuspenTimerExp
 Description     : 等待 MMC的挂起响应超时
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhangcaixia 179470      2011-9-10  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_SsRrcOriWaitMmcSuspenTimerExp(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru  )
{
    LRRC_LNAS_RESULT_ENUM_UINT32    ulRslt = LRRC_LNAS_FAIL;
    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;

    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_SsRrcOriWaitMmcSuspenTimerExp: ");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SsRrcOriWaitMmcSuspenTimerExp_ENUM,LNAS_TIMER_EXPIRED);

    /*恢复状态*/
    NAS_LMM_MEM_CPY_S(  NAS_LMM_GetCurFsmAddr(NAS_LMM_PARALLEL_FSM_EMM),
                        sizeof(NAS_LMM_FSM_STATE_STRU),
                        NAS_EMM_GetStateBeforeSuspendAddr(),
                        sizeof(NAS_LMM_FSM_STATE_STRU));

    /* 当前的 LTE为挂起态, 恢复挂起前的激活态 */
    NAS_EMM_GetCurLteState() = NAS_LMM_CUR_LTE_ACTIVE;


    /* 由于等MMC响应超时，不再挂起ESM和ERABM，将MMC的挂起失败消息转发给LRRC */
    /* 发送 LRRC_LMM_SUSPEND_RSP*/
    NAS_EMM_SendLrrcSuspendRsp(ulRslt);
    NAS_EMM_MsSuspendSsRrcOriWaitMmcSuspendFailProc();

    return  NAS_LMM_MSG_HANDLED;
}
/*****************************************************************************
 Function Name   : NAS_EMM_MsSuspendSsRrcOriWaitOtherMsgSusRsp
 Description     :
                   对LRRC触发的挂起:
                   收到 ESM,ERABM 的挂起响应，再给MMC发送挂起指示；
                   收到 MMC的挂起响应，再给LRRC发送响应

                   对MMC触发的挂起:
                   收到 ESM,ERABM 的挂起响应，再给RRCC发送挂起指示；
                   收到 RRC的挂起响应，再给MMC发送响应

 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-4-23  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsSuspendSsRrcOriWaitOtherMsgSusRsp(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru  )
{
    LRRC_LNAS_RESULT_ENUM_UINT32        ulRslt          = LRRC_LNAS_SUCC;

    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;

    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_MsSuspendSsRrcOriWaitOtherMsgSusRsp: enter. ");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsSuspendSsRrcOriWaitOtherMsgSusRsp_ENUM,LNAS_ENTRY);

    NAS_EMM_GetUplayerCount()++;

    /* RRC的响应，意味着挂起通知完成  */
    if(NAS_EMM_SUSPEND_UPLAYER_NUM_CM <= NAS_EMM_GetUplayerCount())
    {
        /* 停止定时器 */
        NAS_LMM_StopStateTimer(TI_NAS_EMM_RRCORI_WAIT_OTHER_SUSPEND_RSP_TIMER);

        /* 清除此次挂起的上层响应记录，恢复过程将使用 */
        NAS_EMM_GetUplayerCount() = NAS_EMM_SUSPEND_UPLAYER_NUM_INITVALUE;

        /* RRC发起的挂起，为收到MMC的响应，给RRC发送响应，然后等待挂起结束 */

        /* 发送 LRRC_LMM_SUSPEND_RSP*/
        NAS_EMM_SendLrrcSuspendRsp(ulRslt);

        /* 状态迁移*/
        NAS_EMM_PUBU_FSMTranState(      EMM_MS_SUSPEND,
                                        EMM_SS_SUSPEND_WAIT_END,
                                        TI_NAS_EMM_WAIT_SUSPEND_END_TIMER);

    }

    return  NAS_LMM_MSG_HANDLED;
}



VOS_UINT32  NAS_EMM_MsSuspendSsRrcOriWaitOtherMsgMmcSuspendRelReq
(
    VOS_UINT32  ulMsgId,
    VOS_VOID   *pMsgStru
)
{
    NAS_LMM_EMMC_LOG_NORM("NAS_EMM_MsSuspendSsRrcOriWaitOtherMsgMmcSuspendRelReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsSuspendSsRrcOriWaitOtherMsgMmcSuspendRelReq_ENUM,LNAS_ENTRY);

    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;

    NAS_EMM_SetSuspendRelCause(NAS_EMM_SUSPEND_REL_CAUSE_MMC_ORI);
    NAS_LMM_EMMC_LOG1_NORM("NAS_EMM_MsSuspendSsRrcOriWaitOtherMsgMmcSuspendRelReq.uspendRelCause =",
                            NAS_EMM_SUSPEND_REL_CAUSE_MMC_ORI);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsSuspendSsRrcOriWaitOtherMsgMmcSuspendRelReq_ENUM,LNAS_FUNCTION_LABEL1,
                            NAS_EMM_SUSPEND_REL_CAUSE_MMC_ORI);

    /* 停止定时器 */
    NAS_LMM_StopStateTimer(TI_NAS_EMM_RRCORI_WAIT_OTHER_SUSPEND_RSP_TIMER);

    /* 清除此次挂起的上层响应记录，恢复过程将使用 */
    NAS_EMM_GetUplayerCount() = NAS_EMM_SUSPEND_UPLAYER_NUM_INITVALUE;

    /* 发送 LRRC_LMM_SUSPEND_RSP*/
    NAS_EMM_SendLrrcSuspendRsp(LRRC_LNAS_SUCC);

    /*发送LRRC_LMM_SUSPEND_REL_REQ消息*/
    NAS_EMM_SndLrrcSuspendRelReq();

    /* 直接转到EMM_SS_SUSPEND_WAIT_END态等待RESUME IND消息 */
    NAS_EMM_PUBU_FSMTranState(      EMM_MS_SUSPEND,
                                    EMM_SS_SUSPEND_WAIT_END,
                                    TI_NAS_EMM_WAIT_SUSPEND_END_TIMER);
    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsSuspendSsRrcOriWaitOtherMsgMmcDetachReq
 Description     : RRC触发挂起等ESM和ERABM回复过程中收到MMC下发的DETACH请求处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunjitan 00193151      2013-12-30  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_EMM_MsSuspendSsRrcOriWaitOtherMsgMmcDetachReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                            *pMsgStru
)
{
    MMC_LMM_DETACH_REQ_STRU            *pstAppDetReq;

    NAS_LMM_EMMC_LOG_NORM("NAS_EMM_MsSuspendSsRrcOriWaitOtherMsgMmcDetachReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsSuspendSsRrcOriWaitOtherMsgMmcDetachReq_ENUM,LNAS_ENTRY);

    (VOS_VOID)ulMsgId;
    pstAppDetReq = (MMC_LMM_DETACH_REQ_STRU*)pMsgStru;

    /* 停止定时器 */
    NAS_LMM_StopStateTimer(TI_NAS_EMM_RRCORI_WAIT_OTHER_SUSPEND_RSP_TIMER);

    /* 清除此次挂起的上层相应记录 */
    NAS_EMM_GetUplayerCount() = NAS_EMM_SUSPEND_UPLAYER_NUM_INITVALUE;

    /* 放弃挂起流程，退回L主模 */
    NAS_EMM_GetCurLteState() = NAS_LMM_CUR_LTE_ACTIVE;

    /* 激活ESM, ERABM */
    NAS_EMM_SendEsmResumeInd();
    NAS_EMM_SendErabmResumeInd();

    /* 给MMC回DETACH成功 */
    NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);

    /* 给MMC发送恢复 */
    NAS_EMM_SendMmcResumeInd();

    /* 给RRC回挂起失败，退回L主模等系统消息*/
    NAS_EMM_SendLrrcSuspendRsp(LRRC_LNAS_FAIL);

    /* 如果是CSFB导致的挂起，中止CSFB和挂起回退到L主模 */
    if(LRRC_LMM_SUS_CAUSE_CSFB == NAS_EMM_GetSuspendCause())
    {
        NAS_EMM_SetCsfbProcedureFlag(PS_FALSE);

        /* 通知MM中止CSFB */
        NAS_EMM_MmSendCsfbSerEndInd(MM_LMM_CSFB_SERVICE_RSLT_MMC_DETACH_FAIL, NAS_LMM_CAUSE_NULL);

        /* 只有CSFB的场景在这里可能收到CS DETACH，其它场景的CS DETACH预处理中已经处理 */
        if(MMC_LMM_MO_DET_CS_ONLY == pstAppDetReq->ulDetachType)
        {
            NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);

            /* 挂起之前注册域为CS_PS，无论是否紧急注册都肯定是注册态 */
            NAS_EMM_AdStateConvert(EMM_MS_REG,
                                   EMM_SS_REG_NO_CELL_AVAILABLE,
                                   TI_NAS_EMM_STATE_NO_TIMER);

            /* IMSI DETACH后释放资源 */
            NAS_LMM_ImsiDetachReleaseResource();

            /* 给RRC发释放，设置连接状态为释放过程中 */
            NAS_EMM_SndRrcRelReq(NAS_LMM_NOT_BARRED);
            NAS_EMM_SetConnState(NAS_EMM_CONN_RELEASING);

            return NAS_LMM_MSG_HANDLED;
        }
    }

    /* 收到的是PS或CS_PS类型，全部执行本地DETACH，包括CSFB场景 */

    /* 通知ESM执行了本地DETACH */
    NAS_EMM_EsmSendStatResult(EMM_ESM_ATTACH_STATUS_DETACHED);

    /* 自研CL版本，PS DETACH通知ESM删除所有EHRPD相关承载记录 */
    NAS_EMM_SndEsmClearAllClBearerNotify();

    /* 有可能是处于紧急注册的无卡状态 */
    if (NAS_LMM_SIM_STATUS_UNAVAILABLE == NAS_LMM_GetSimState())
    {
        /* 无卡 */
        NAS_EMM_AdStateConvert(EMM_MS_DEREG,
                               EMM_SS_DEREG_NO_IMSI,
                               TI_NAS_EMM_STATE_NO_TIMER);
    }
    else
    {
        /* 有卡 */
        NAS_EMM_AdStateConvert(EMM_MS_DEREG,
                               EMM_SS_DEREG_NO_CELL_AVAILABLE,
                               TI_NAS_EMM_STATE_NO_TIMER);
    }

    /* 本地DETACH释放资源:动态内存、赋初值 */
    NAS_LMM_DeregReleaseResource();

    /* 切换和CCO的场景，给RRC发释放 ；重选、重定向和CSFB不发，RRC自然会释放*/
    if((NAS_LMM_SYS_CHNG_TYPE_CCO == NAS_EMM_GetSuspendType())
        ||(NAS_LMM_SYS_CHNG_TYPE_HO == NAS_EMM_GetSuspendType()))
    {
        NAS_EMM_SndRrcRelReq(NAS_LMM_NOT_BARRED);
        NAS_EMM_SetConnState(NAS_EMM_CONN_RELEASING);
    }

    return NAS_LMM_MSG_HANDLED;

}

/*****************************************************************************
 Function Name   : NAS_EMM_MsSuspendSsWaitDownlayerMsgUplayerRsp
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.Hanlufeng 41410      2011-5-4  Draft Enact
    2.sunjitan 00193151   2012-05-24 增加清除Resume触发和类型记录信息

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsSuspendSsMmcOriWaitOtherMsgSusRsp(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru  )
{
    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;

    NAS_EMM_GetUplayerCount()++;

    /* 若等于 2，意味着 ESM和ERABM挂起结束 */
    if(NAS_EMM_SUSPEND_UPLAYER_NUM_CM == NAS_EMM_GetUplayerCount())
    {
        /* 通知RRC挂起 */
        NAS_EMM_SendLrrcSuspendReq();
    }

    /* 若等于 3，意味着 RRC的响应，意味着挂起通知完成  */
    if(NAS_EMM_SUSPEND_UPLAYER_NUM_ALL <= NAS_EMM_GetUplayerCount())
    {
        /* 停止定时器 */
        NAS_LMM_StopStateTimer(TI_NAS_EMM_MMCORI_WAIT_OTHER_SUSPEND_RSP_TIMER);

        /* 清除此次挂起的上层响应记录，恢复过程将使用 */
        NAS_EMM_GetUplayerCount() = NAS_EMM_SUSPEND_UPLAYER_NUM_INITVALUE;

        /* 挂起成功，之前的GU到L的异系统变换触发和类型记录信息可以清除 */
        NAS_EMM_ClearResumeInfo();

        /* MMC发起的挂起，则为收到RRC挂起完成，给MMC响应，完成挂起 */
        /* 给MMC发送挂起响应 */
        NAS_EMM_SendMmcSuspendCnf(MMC_LMM_SUCC);

        /* 挂起结束，改状态 */
        NAS_EMM_SuspendEndStateChng();
    }

    return  NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsSuspendSsMmcOriWaitOtherMsgMmcDetachReq
 Description     : MMC或者SYSCFG触发的挂起在等ESM和ERABM挂起过程中收到MMC的DETACH
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunjitan 00193151      2013-12-30  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsSuspendSsMmcOrSyscfgOriWaitOtherMsgMmcDetachReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                            *pMsgStru
)
{
    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;

    /* 给MMC回DETACH成功 */
    NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);

    /* 通知ESM执行了本地DETACH */
    NAS_EMM_EsmSendStatResult(EMM_ESM_ATTACH_STATUS_DETACHED);

    /* 自研CL版本，PS DETACH通知ESM删除所有EHRPD相关承载记录 */
    NAS_EMM_SndEsmClearAllClBearerNotify();

    /* 修改挂起前状态，继续挂起流程 */
    NAS_EMM_SetMsBefSuspend(EMM_MS_DEREG);

    /* 有可能是处于紧急注册的无卡状态 */
    if (NAS_LMM_SIM_STATUS_UNAVAILABLE == NAS_LMM_GetSimState())
    {
        NAS_EMM_SetSsBefSuspend(EMM_SS_DEREG_NO_IMSI);

    }
    else
    {
        NAS_EMM_SetSsBefSuspend(EMM_SS_DEREG_NO_CELL_AVAILABLE);
    }

    /* 停止所有EMM协议定时器 ，不调用NAS_LMM_DeregReleaseResource为防止误停当前状态定时器 */
    NAS_LMM_StopAllEmmPtlTimer();

    /* 本地DETACH释放资源:动态内存、赋初值 */
    NAS_LMM_PUBM_ClearResource();
    NAS_EMM_PUBU_ClearResource();
    NAS_EMM_SECU_ClearResource();
    NAS_EMM_Attach_ClearResourse();
    NAS_EMM_Detach_ClearResourse();
    NAS_EMM_TAU_ClearResouce();
    NAS_EMM_SER_ClearResource();

    return  NAS_LMM_MSG_HANDLED;
}



/*****************************************************************************
 Function Name   : NAS_EMM_MsSuspendSsWaitOtherMsgTimerExp
 Description     : 等待 ESM,ERABM 的挂起响应超时
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-4-25  Draft Enact
    2.sunbing 49683             2012-5-29  增加复位原因，便于问题定位
*****************************************************************************/
VOS_UINT32  NAS_EMM_MsSuspendSsWaitOtherMsgTimerExp(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru  )
{
    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;

    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_MsSuspendSsWaitOtherMsgTimerExp: enter. ");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsSuspendSsWaitOtherMsgTimerExp_ENUM,LNAS_ENTRY);

    /*MMC挂起ESM/RAMB超时*/
    if( EMM_SS_SUSPEND_MMCORI_WAIT_OTHER_SUSPEND == NAS_LMM_GetEmmCurFsmSS())
    {
        if(NAS_EMM_SUSPEND_UPLAYER_NUM_CM > NAS_EMM_GetUplayerCount())
        {
            NAS_EMM_SendMmcErrInd(NAS_EMM_REBOOT_TYPE_MMC_SUSPEND_ECM_FAIL);
        }
        else
        {
            NAS_EMM_SendMmcErrInd(NAS_EMM_REBOOT_TYPE_MMC_SUSPEND_RRC_FAIL);
        }
    }
    else/*RRC挂起ESM/RAMB超时*/
    {
        NAS_EMM_SendMmcErrInd(NAS_EMM_REBOOT_TYPE_RRC_SUSPEND_ECM_FAIL);

    }

    return  NAS_LMM_MSG_HANDLED;
}


/*****************************************************************************
 Function Name   : NAS_EMM_MsSuspendSsWaitEndMsgMmcResumeNotify
 Description     : 收到 G/U 模的解挂消息，意味着GU已经完成系统变换；
                   L2GU的CCO过程，收到此消息也认为系统变换完成，只是
                   随后收到的LRRC的RESUME可能是CCO REVERSE；
                   系统变换完成，不影响连接状态，HO和CCO都等着LRRC的REL消息
                   才影响连接状态；
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-4-25  Draft Enact
    2.sunli 00180715            2011-7-29  DTS2011080401328
    3.sunjitan 00193151   2012-05-24 增加清除Resume触发和类型记录信息

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsSuspendSsWaitEndMsgMmcResumeNotify(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru  )
{
    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;

    /* 清除TAU Start Cause */
    /*NAS_EMM_TAU_GetEmmTAUStartCause() = NAS_EMM_TAU_START_CAUSE_DEFAULT;*/

    /* 停止定时器 */
    NAS_LMM_StopStateTimer(TI_NAS_EMM_WAIT_SUSPEND_END_TIMER);

    /* 除了T3412和T3423，停止状态定时器, 清空各流程全局变量*/
    NAS_EMM_SuspendInitRelResource();

    /* 挂起成功，之前的GU到L的异系统变换触发和类型记录信息可以清除 */
    NAS_EMM_ClearResumeInfo();

    NAS_LMM_SetEmmInfoTriggerTauSysChange(NAS_EMM_NO);
    /* del by y00307272 for DTS2015122301277 ,2015-12-26，Begin */
    /* DEL CAUSE:csfb到G下，挂起ps并通知LNAS，随后电话挂断后FR失败，回退到G下丢网，搜L
     失败，搜W失败(搜时MMC会给LNAS发挂起，我们这是会设置ps not suspension)，在搜到L判断
     PS没有挂起，不发TAU，被叫失败 */
    /*NAS_LMM_SetEmmInfoPsState(GMM_LMM_GPRS_NOT_SUSPENSION);*/
    /* del by y00307272 for DTS2015122301277 ,2015-12-26，End */


    /* 如果是不是自研CL版本，才执行此分支的处理 */
    #if (FEATURE_ON != FEATURE_UE_MODE_CDMA)
    if (NAS_LMM_SUS_SYS_CHNG_DIR_L2C == NAS_EMM_GetSuspendDir())
    {
        NAS_EMM_SendDetRslt(MMC_LMM_DETACH_RSLT_SUCCESS);
        NAS_EMM_EsmSendStatResult(EMM_ESM_ATTACH_STATUS_DETACHED);
        NAS_EMM_AdStateConvert(EMM_MS_DEREG,
                               EMM_SS_DEREG_NO_CELL_AVAILABLE,
                               TI_NAS_EMM_STATE_NO_TIMER);

        /* 本地DETACH释放资源:动态内存、赋初值,释放链路 */
        NAS_LMM_DeregReleaseResource();
        return NAS_LMM_MSG_HANDLED;
    }
    #endif

    /* 挂起结束，改状态 */
    NAS_EMM_SuspendEndStateChng();

    return NAS_LMM_MSG_HANDLED;
}


VOS_UINT32  NAS_EMM_MsSuspendSsWaitEndMsgMmcSuspendRelReq
(
    VOS_UINT32  ulMsgId,
    VOS_VOID   *pMsgStru
)
{
    NAS_LMM_EMMC_LOG_NORM("NAS_EMM_MsSuspendSsWaitEndMsgMmcSuspendRelReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsSuspendSsWaitEndMsgMmcSuspendRelReq_ENUM,LNAS_ENTRY);

    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;

    NAS_EMM_SetSuspendRelCause(NAS_EMM_SUSPEND_REL_CAUSE_MMC_ORI);
    NAS_LMM_EMMC_LOG1_NORM("NAS_EMM_MsSuspendSsWaitEndMsgMmcSuspendRelReq",
                            NAS_EMM_SUSPEND_REL_CAUSE_MMC_ORI);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsSuspendSsWaitEndMsgMmcSuspendRelReq_ENUM,LNAS_FUNCTION_LABEL1,
                            NAS_EMM_SUSPEND_REL_CAUSE_MMC_ORI);


    /*发送LRRC_LMM_SUSPEND_REL_REQ消息*/
    NAS_EMM_SndLrrcSuspendRelReq();

    return NAS_LMM_MSG_HANDLED;
}


/*****************************************************************************
 Function Name   : NAS_EMM_SuspendEndStateChng
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.Hanlufeng 41410      2011-5-4  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_EMM_SuspendEndStateChng( VOS_VOID)
{
    switch(NAS_EMM_GetMsBefSuspend())
    {
        case    EMM_MS_REG:
        case    EMM_MS_TAU_INIT:
        case    EMM_MS_SER_INIT:
                /* 已注册成功，转为REG 的NO CELL状态 */
                NAS_EMM_PUBU_FSMTranState(  EMM_MS_REG,
                                            EMM_SS_REG_NO_CELL_AVAILABLE,
                                            TI_NAS_EMM_STATE_NO_TIMER);
                break;

        default  :
                if(EMM_SS_DEREG_NO_IMSI == NAS_EMM_GetSsBefSuspend())
                {
                    NAS_EMM_PUBU_FSMTranState(  EMM_MS_DEREG,
                                                EMM_SS_DEREG_NO_IMSI,
                                                TI_NAS_EMM_STATE_NO_TIMER);
                }
                else
                {
                    NAS_EMM_PUBU_FSMTranState(  EMM_MS_DEREG,
                                                EMM_SS_DEREG_NO_CELL_AVAILABLE,
                                                TI_NAS_EMM_STATE_NO_TIMER);
                }
               break;
    }

   return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_MsSuspendSsWaitEndMsgWtEndTimerExp
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-4-25  Draft Enact
    2.sunbing 49683             2012-5-29  增加复位原因，便于问题定位
*****************************************************************************/
VOS_UINT32  NAS_EMM_MsSuspendSsWaitEndMsgWtEndTimerExp(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru  )
{
    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;

    /* 复位 */
    NAS_EMM_SendMmcErrInd(NAS_EMM_REBOOT_TYPE_RRC_SUSPEND_WAIT_MMC_END_FAIL);

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsSuspendSsRrcOriMsgRrcAccessGrantInd
 Description     :  Suspend.RrcOriWtMmcSuspend
                    Suspend.RrcOriWtOtherSuspend
                    Suspend.WtEnd
                   三个状态下收到LRRC_LMM_ACCESS_GRANT_IND消息的处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-11-29  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsSuspendSsRrcOriMsgRrcAccessGrantInd(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru  )
{
    LRRC_LMM_ACCESS_GRANT_IND_STRU     *pstRrcMmGrantInd = NAS_EMM_NULL_PTR;
    VOS_UINT32                          ulEmmStaBeforeSuspend = 0;

    (VOS_VOID)ulMsgId;
    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_MsSuspendSsRrcOriMsgRrcAccessGrantInd enter.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsSuspendSsRrcOriMsgRrcAccessGrantInd_ENUM,LNAS_ENTRY);

    /* 入参空指针检查*/
    if (NAS_EMM_NULL_PTR == pMsgStru)
    {
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_MsSuspendSsRrcOriMsgRrcAccessGrantInd: NULL PTR!!!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsSuspendSsRrcOriMsgRrcAccessGrantInd_ENUM,LNAS_NULL_PTR);
        return NAS_LMM_ERR_CODE_PARA_INVALID;
    }

    /* 获取LRRC_LMM_ACCESS_GRANT_IND消息**/
    pstRrcMmGrantInd = (LRRC_LMM_ACCESS_GRANT_IND_STRU *)pMsgStru;

    /* 获取挂起前的状态*/
    ulEmmStaBeforeSuspend = NAS_LMM_PUB_COMP_EMMSTATE(NAS_EMM_GetMsBefSuspend(),
                                                      NAS_EMM_GetSsBefSuspend());
    /* 根据挂起前的状态做不同处理*/
    switch(ulEmmStaBeforeSuspend)
    {
        /* 挂起前的状态为Dereg.Attach_Needed，
           如果解除了MO_Signal Bar，则将挂起前状态修改为Dereg.Normal_Service;
           否则，打印出错信息，处理结束
         */
        case NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_DEREG,
                                       EMM_SS_DEREG_ATTACH_NEEDED):
            NAS_EMM_PUBU_LOG_INFO("NAS_EMM_MsSuspendSsRrcOriMsgRrcAccessGrantInd:Dereg.Attach_Needed.");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_MsSuspendSsRrcOriMsgRrcAccessGrantInd_ENUM,LNAS_EMM_ATTACH_NEEDED);
            if ((LRRC_LNAS_ACCESS_GRANT_MO_SIGNAL       == pstRrcMmGrantInd->enAccessGrantType)
              ||(LRRC_LNAS_ACCESS_GRANT_MO_SIGNAL_AND_MT== pstRrcMmGrantInd->enAccessGrantType)
              ||(LRRC_LNAS_ACCESS_GRANT_MO_CALL_AND_MO_SIGNAL == pstRrcMmGrantInd->enAccessGrantType)
              ||(LRRC_LNAS_ACCESS_GRANT_MO_CALL_AND_MO_SIGNAL_AND_MT == pstRrcMmGrantInd->enAccessGrantType)
              ||(LRRC_LNAS_ACCESS_GRANT_MO_CALL_AND_MO_SIGNAL_AND_MO_CSFB == pstRrcMmGrantInd->enAccessGrantType)
              ||(LRRC_LNAS_ACCESS_GRANT_MO_SIGNAL_AND_MO_CSFB == pstRrcMmGrantInd->enAccessGrantType)
              ||(LRRC_LNAS_ACCESS_GRANT_MO_SIGNAL_AND_MO_CSFB_AND_MT == pstRrcMmGrantInd->enAccessGrantType)
              ||(LRRC_LNAS_ACCESS_GRANT_ALL             == pstRrcMmGrantInd->enAccessGrantType))
            {
                NAS_EMM_SetMsBefSuspend(EMM_MS_DEREG);
                NAS_EMM_SetSsBefSuspend(EMM_SS_DEREG_NORMAL_SERVICE);
            }
            else
            {
                NAS_EMM_PUBU_LOG_WARN("NAS_EMM_MsSuspendSsRrcOriMsgRrcAccessGrantInd:GrantType Err. ");
                TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsSuspendSsRrcOriMsgRrcAccessGrantInd_ENUM,LNAS_ERROR);
            }
            break;

        /* 挂起前的状态为Reg.WtAccessGrantInd，根据GrantType，修改BarType*/
        case NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG,
                                       EMM_SS_REG_WAIT_ACCESS_GRANT_IND):
            NAS_EMM_PUBU_LOG_INFO("NAS_EMM_MsSuspendSsRrcOriMsgRrcAccessGrantInd:Reg.WtAccessGrantInd.");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_MsSuspendSsRrcOriMsgRrcAccessGrantInd_ENUM,LNAS_FUNCTION_LABEL1);
            NAS_EMM_ClearBarType(pstRrcMmGrantInd->enAccessGrantType);
            break;

        /* 其他状态，打印出错信息*/
        default:
            NAS_EMM_PUBU_LOG_WARN("NAS_EMM_MsSuspendSsRrcOriMsgRrcAccessGrantInd:Sta Err or LRRC Err.");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_MsSuspendSsRrcOriMsgRrcAccessGrantInd_ENUM,LNAS_FUNCTION_LABEL2);
            break;
    }

    return NAS_LMM_MSG_HANDLED;
}


/*****************************************************************************
 Function Name   : NAS_EMM_SaveLrrcSuspendPara
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.HanLufeng 41410      2011-4-28  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_SaveLrrcSuspendPara( const LRRC_LMM_SUSPEND_IND_STRU  *pLrrcLmmSuspendInd )
{
    NAS_EMM_SetSuspendOri(NAS_LMM_SYS_CHNG_ORI_LRRC);
    NAS_EMM_SetSuspendDir(pLrrcLmmSuspendInd->enSysChngDir);
    NAS_EMM_SetSuspendType(pLrrcLmmSuspendInd->enSysChngType);
    NAS_EMM_SetSuspendCause(pLrrcLmmSuspendInd->enSusCause);
    NAS_EMM_SetSuspendSecuPara((pLrrcLmmSuspendInd->stHoSecuPara).ucHoSecuPara);

    NAS_LMM_MEM_CPY_S(  NAS_EMM_GetStateBeforeSuspendAddr(),
                        sizeof(NAS_LMM_FSM_STATE_STRU),
                        NAS_LMM_GetCurFsmAddr(NAS_LMM_PARALLEL_FSM_EMM),
                        sizeof(NAS_LMM_FSM_STATE_STRU));

    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_SuspendInitRelResource
 Description     : 收到挂起消息，要清部分资源。此资源不同于LOCAL DETACH的清，
                   需要各模块提供专用于挂起时清理的函数；
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.HanLufeng 41410      2011-4-26  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_SuspendInitRelResource( VOS_VOID)
{

    /* 停止除了T3402,T3412和T3423的所有EMM协议定时器*/
    NAS_LMM_SuspendInitStopLmmTimer();

    /* 释放可能存在的动态内存 */
    NAS_LMM_FreeDynMem();

    /*PUBM清理*/
    NAS_LMM_PUBM_ClearResource();

    /*===============  EMM各子模块清理  ===============*/

    /* EMM挂起清理，保留承载状态信息 */
    NAS_EMM_PUBU_SuspendClearResource();

    NAS_EMM_SECU_ClearResource();
    NAS_EMM_Attach_SuspendInitClearResourse();
    NAS_EMM_Detach_ClearResourse();

    /* TAU清理，不停止T3402和T3411定时器*/
    NAS_EMM_TAU_SuspendInitClearResouce();
    NAS_EMM_SER_ClearResource();

    /*清除bar流程和类型*/
    NAS_EMM_ClearBarResouce();

    NAS_EMM_ClrAllUlDataReqBufferMsg();

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SuspendEndRelResource
 Description     : 挂起结束，停止T3412, 清空T3412的超时标志
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.HanLufeng 41410      2011-4-26  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_SuspendEndRelResource( VOS_VOID)
{

    NAS_LMM_StopPtlTimer(TI_NAS_EMM_PTL_T3412);

    NAS_LMM_SetEmmInfoT3412ExpCtrl(NAS_EMM_T3412_EXP_NO);

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SendMmcSuspendCnf
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.HanLufeng 41410      2011-4-26  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_SendMmcSuspendCnf( MMC_LMM_RESULT_ID_ENUM_UINT32 ulSuspendRst )
{
    LMM_MMC_SUSPEND_CNF_STRU           *pstMmcSuspendCnfMsg;

    /* 申请MMC内部消息 */
    pstMmcSuspendCnfMsg = (VOS_VOID *) NAS_LMM_GetLmmMmcMsgBuf(sizeof(LMM_MMC_SUSPEND_CNF_STRU));
    if (NAS_LMM_NULL_PTR == pstMmcSuspendCnfMsg)
    {
        /* 打印异常，ERROR_LEVEL */
        NAS_EMM_PUBU_LOG_NORM("NAS_EMM_SendMmcSuspendCnf: MSG ALLOC ERROR!!!");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SendMmcSuspendCnf_ENUM,LNAS_NULL_PTR);
        return ;
    }

    /* 清空 */
    NAS_LMM_MEM_SET_S(  pstMmcSuspendCnfMsg,
                        sizeof(LMM_MMC_SUSPEND_CNF_STRU),
                        0,
                        sizeof(LMM_MMC_SUSPEND_CNF_STRU));

    /* 打包VOS消息头 */
    EMM_PUBU_COMP_MMC_MSG_HEADER((pstMmcSuspendCnfMsg),
                             NAS_EMM_GET_MSG_LENGTH_NO_HEADER(LMM_MMC_SUSPEND_CNF_STRU));

    /* 填充消息ID */
    pstMmcSuspendCnfMsg->ulMsgId        = ID_LMM_MMC_SUSPEND_CNF;

    /* 填充消息体 */
    pstMmcSuspendCnfMsg->ulOpId         = NAS_EMM_OPID_MMC;
    pstMmcSuspendCnfMsg->ulRst          = ulSuspendRst;

    /* 发送MMC内部消息 */
    NAS_LMM_SendLmmMmcMsg(pstMmcSuspendCnfMsg);

    return;
}

VOS_VOID  NAS_EMM_SendMmcSuspendRelCnf(VOS_VOID )
{
    LMM_MMC_SUSPEND_REL_CNF_STRU           *pstMmcSuspendRelCnfMsg;

    /* 申请DOPRA消息 */
    pstMmcSuspendRelCnfMsg = (VOS_VOID *) NAS_LMM_GetLmmMmcMsgBuf(sizeof(LMM_MMC_SUSPEND_REL_CNF_STRU));
    if (NAS_LMM_NULL_PTR == pstMmcSuspendRelCnfMsg)
    {
        /* 打印异常，ERROR_LEVEL */
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_SendMmcSuspendRelCnf: MSG ALLOC ERROR!!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SendMmcSuspendRelCnf_ENUM,LNAS_NULL_PTR);
        return ;
    }

    /* 清空 */
    NAS_LMM_MEM_SET_S(  pstMmcSuspendRelCnfMsg,
                        sizeof(LMM_MMC_SUSPEND_REL_CNF_STRU),
                        0,
                        sizeof(LMM_MMC_SUSPEND_REL_CNF_STRU));

    /* 打包VOS消息头 */
    EMM_PUBU_COMP_MMC_MSG_HEADER((pstMmcSuspendRelCnfMsg),
                             NAS_EMM_GET_MSG_LENGTH_NO_HEADER(LMM_MMC_SUSPEND_REL_CNF_STRU));

    /* 填充消息ID */
    pstMmcSuspendRelCnfMsg->ulMsgId        = ID_LMM_MMC_SUSPEND_REL_CNF;


    /* 发送DOPRA消息 */
    NAS_LMM_SendLmmMmcMsg(pstMmcSuspendRelCnfMsg);

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SendMmcSuspendInd
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.HanLufeng 41410      2011-4-26  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_SendMmcSuspendInd(VOS_VOID )
{
    LMM_MMC_SUSPEND_IND_STRU           *pstMmcSuspendIndMsg;

    /* 申请DOPRA消息 */
    pstMmcSuspendIndMsg = (VOS_VOID *) NAS_LMM_GetLmmMmcMsgBuf(sizeof(LMM_MMC_SUSPEND_IND_STRU));
    if (NAS_LMM_NULL_PTR == pstMmcSuspendIndMsg)
    {
        /* 打印异常，ERROR_LEVEL */
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_SendMmcSuspendInd: MSG ALLOC ERROR!!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SendMmcSuspendInd_ENUM,LNAS_NULL_PTR);
        return ;
    }

    /* 清空 */
    NAS_LMM_MEM_SET_S(  pstMmcSuspendIndMsg,
                        sizeof(LMM_MMC_SUSPEND_IND_STRU),
                        0,
                        sizeof(LMM_MMC_SUSPEND_IND_STRU));

    /* 打包VOS消息头 */
    EMM_PUBU_COMP_MMC_MSG_HEADER((pstMmcSuspendIndMsg),
                             NAS_EMM_GET_MSG_LENGTH_NO_HEADER(LMM_MMC_SUSPEND_IND_STRU));

    /* 填充消息ID */
    pstMmcSuspendIndMsg->ulMsgId        = ID_LMM_MMC_SUSPEND_IND;

    /* 填充消息体 */
    if(NAS_LMM_SUS_SYS_CHNG_DIR_L2W == NAS_EMM_GetSuspendDir())
    {
        pstMmcSuspendIndMsg->ulSysChngDir = MMC_LMM_SYS_CHNG_DIR_L2W;
    }
    else if(NAS_LMM_SUS_SYS_CHNG_DIR_L2C == NAS_EMM_GetSuspendDir())
    {
        pstMmcSuspendIndMsg->ulSysChngDir = MMC_LMM_SYS_CHNG_DIR_L2C;
    }
    else
    {
        pstMmcSuspendIndMsg->ulSysChngDir = MMC_LMM_SYS_CHNG_DIR_L2G;
    }


    switch(NAS_EMM_GetSuspendType())
    {
        case    NAS_LMM_SYS_CHNG_TYPE_RSL:
                pstMmcSuspendIndMsg->ulSysChngType = MMC_LMM_SUS_TYPE_RSL;
                break;

        case    NAS_LMM_SYS_CHNG_TYPE_HO:
                pstMmcSuspendIndMsg->ulSysChngType = MMC_LMM_SUS_TYPE_HO;
                break;

        case    NAS_LMM_SYS_CHNG_TYPE_CCO:
                pstMmcSuspendIndMsg->ulSysChngType = MMC_LMM_SUS_TYPE_CCO;
                break;

        case    NAS_LMM_SYS_CHNG_TYPE_REDIR:
                pstMmcSuspendIndMsg->ulSysChngType = MMC_LMM_SUS_TYPE_REDIR;
                break;

        case    NAS_LMM_SYS_CHNG_TYPE_REVERSE_CCO:
                pstMmcSuspendIndMsg->ulSysChngType = MMC_LMM_SUS_TYPE_CCO_REVERSE;
                break;

        default    :
                NAS_EMM_PUBU_LOG1_ERR("NAS_EMM_SendMmcSuspendInd: ERROR, enSysChngType =",
                                    NAS_EMM_GetSuspendType());
                TLPS_PRINT2LAYER_ERROR1(NAS_EMM_SendMmcSuspendInd_ENUM,LNAS_ERROR,
                                    NAS_EMM_GetSuspendType());
                break;
    }


    /* 发送DOPRA消息 */
    NAS_LMM_SendLmmMmcMsg(pstMmcSuspendIndMsg);

    return;
}




/*****************************************************************************
 Function Name   : NAS_EMM_SendEsmSuspendInd
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.HanLufeng 41410      2011-4-26  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_SendEsmSuspendInd( VOS_VOID )
{
    EMM_ESM_SUSPEND_IND_STRU           *pstEsmSuspendIndMsg;

    /* 申请DOPRA消息 */
    pstEsmSuspendIndMsg = (VOS_VOID *) NAS_LMM_ALLOC_MSG(sizeof(EMM_ESM_SUSPEND_IND_STRU));
    if (NAS_LMM_NULL_PTR == pstEsmSuspendIndMsg)
    {
        return ;
    }

    /* 清空 */
    NAS_LMM_MEM_SET_S(  pstEsmSuspendIndMsg,
                        sizeof(EMM_ESM_SUSPEND_IND_STRU),
                        0,
                        sizeof(EMM_ESM_SUSPEND_IND_STRU));

    /* 打包VOS消息头 */
    EMM_PUBU_COMP_ESM_MSG_HEADER((pstEsmSuspendIndMsg),
                             NAS_EMM_GET_MSG_LENGTH_NO_HEADER(EMM_ESM_SUSPEND_IND_STRU));

    /* 填充消息ID */
    pstEsmSuspendIndMsg->ulMsgId        = ID_EMM_ESM_SUSPEND_IND;


    /* 发送DOPRA消息 */
    NAS_LMM_SEND_MSG(pstEsmSuspendIndMsg);

    return;
}



/*****************************************************************************
 Function Name   : NAS_EMM_SendErabmSuspendInd
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.HanLufeng 41410      2011-4-26  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_SendErabmSuspendInd( VOS_VOID )
{
    EMM_ERABM_SUSPEND_IND_STRU           *pstLrabmSuspendIndMsg;

    /* 申请DOPRA消息 */
    pstLrabmSuspendIndMsg = (VOS_VOID *) NAS_LMM_ALLOC_MSG(sizeof(EMM_ERABM_SUSPEND_IND_STRU));
    if (NAS_LMM_NULL_PTR == pstLrabmSuspendIndMsg)
    {
        return ;
    }

    /* 清空 */
    NAS_LMM_MEM_SET_S(  pstLrabmSuspendIndMsg,
                        sizeof(EMM_ERABM_SUSPEND_IND_STRU),
                        0,
                        sizeof(EMM_ERABM_SUSPEND_IND_STRU));

    /* 打包VOS消息头 */
    EMM_PUBU_COMP_ERABM_MSG_HEADER((pstLrabmSuspendIndMsg),
                             NAS_EMM_GET_MSG_LENGTH_NO_HEADER(EMM_ERABM_SUSPEND_IND_STRU));

    /* 填充消息ID */
    pstLrabmSuspendIndMsg->ulMsgId        = ID_EMM_ERABM_SUSPEND_IND;
    pstLrabmSuspendIndMsg->enSysChngType  = NAS_EMM_GetSuspendType();


    /* 发送DOPRA消息 */
    NAS_LMM_SEND_MSG(pstLrabmSuspendIndMsg);

    return;
}



/*****************************************************************************
 Function Name   : NAS_EMM_SendLrrcSuspendReq
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.HanLufeng 41410      2011-4-28  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_SendLrrcSuspendReq( VOS_VOID )
{
    LRRC_LMM_SUSPEND_REQ_STRU           *pstLrrcSuspendReqMsg;

    /* 申请DOPRA消息 */
    pstLrrcSuspendReqMsg = (VOS_VOID *) NAS_LMM_ALLOC_MSG(sizeof(LRRC_LMM_SUSPEND_REQ_STRU));
    if (NAS_LMM_NULL_PTR == pstLrrcSuspendReqMsg)
    {
        return ;
    }

    /* 清空 */
    NAS_LMM_MEM_SET_S(  pstLrrcSuspendReqMsg,
                        sizeof(LRRC_LMM_SUSPEND_REQ_STRU),
                        0,
                        sizeof(LRRC_LMM_SUSPEND_REQ_STRU));

    /* 打包VOS消息头 */
    NAS_EMM_SET_RRC_MSG_HEADER((pstLrrcSuspendReqMsg),
            NAS_EMM_GET_MSG_LENGTH_NO_HEADER(LRRC_LMM_SUSPEND_REQ_STRU));

    /* 填充消息ID */
    pstLrrcSuspendReqMsg->enMsgId       = ID_LRRC_LMM_SUSPEND_REQ;

    /* 发送DOPRA消息 */
    NAS_LMM_SEND_MSG(pstLrrcSuspendReqMsg);

    return;
}


VOS_VOID  NAS_EMM_SndLrrcSuspendRelReq( VOS_VOID )
{
    LRRC_LMM_SUSPEND_REL_REQ_STRU           *pstLrrcSuspendRelReqMsg;

    NAS_EMM_PUBU_LOG_NORM("NAS_EMM_SndLrrcSuspendRelReq: enter.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SndLrrcSuspendRelReq_ENUM,LNAS_ENTRY);

    /* 申请DOPRA消息 */
    pstLrrcSuspendRelReqMsg = (VOS_VOID *) NAS_LMM_ALLOC_MSG(sizeof(LRRC_LMM_SUSPEND_REL_REQ_STRU));
    if (NAS_LMM_NULL_PTR == pstLrrcSuspendRelReqMsg)
    {
        return ;
    }

    /* 清空 */
    NAS_LMM_MEM_SET_S(  pstLrrcSuspendRelReqMsg,
                        sizeof(LRRC_LMM_SUSPEND_REL_REQ_STRU),
                        0,
                        sizeof(LRRC_LMM_SUSPEND_REL_REQ_STRU));

    /* 打包VOS消息头 */
    NAS_EMM_SET_RRC_MSG_HEADER((pstLrrcSuspendRelReqMsg),
            NAS_EMM_GET_MSG_LENGTH_NO_HEADER(LRRC_LMM_SUSPEND_REL_REQ_STRU));

    /* 填充消息ID */
    pstLrrcSuspendRelReqMsg->enMsgId       = ID_LRRC_LMM_SUSPEND_REL_REQ;

    /* 发送DOPRA消息 */
    NAS_LMM_SEND_MSG(pstLrrcSuspendRelReqMsg);

    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_SendLrrcSuspendRsp
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.HanLufeng 41410      2011-4-28  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_SendLrrcSuspendRsp( LRRC_LNAS_RESULT_ENUM_UINT32 ulRst )
{
    LRRC_LMM_SUSPEND_RSP_STRU           *pstLrrcSuspendRspMsg;

    /* 申请DOPRA消息 */
    pstLrrcSuspendRspMsg = (VOS_VOID *) NAS_LMM_ALLOC_MSG(sizeof(LRRC_LMM_SUSPEND_RSP_STRU));
    if (NAS_LMM_NULL_PTR == pstLrrcSuspendRspMsg)
    {
        return ;
    }

    /* 清空 */
    NAS_LMM_MEM_SET_S(  pstLrrcSuspendRspMsg,
                        sizeof(LRRC_LMM_SUSPEND_RSP_STRU),
                        0,
                        sizeof(LRRC_LMM_SUSPEND_RSP_STRU));

    /* 打包VOS消息头 */
    NAS_EMM_SET_RRC_MSG_HEADER((pstLrrcSuspendRspMsg),
            NAS_EMM_GET_MSG_LENGTH_NO_HEADER(LRRC_LMM_SUSPEND_RSP_STRU));

    /* 填充消息ID */
    pstLrrcSuspendRspMsg->enMsgId       = ID_LRRC_LMM_SUSPEND_RSP;
    pstLrrcSuspendRspMsg->enRslt        = ulRst;

    /* 发送DOPRA消息 */
    NAS_LMM_SEND_MSG(pstLrrcSuspendRspMsg);

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_PreProcMsgMmcActionRstReq
 Description     : 挂起状态下，接收处理GUNAS发来的业务结果消息
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.Hanlufeng 41410      2011-5-12  Draft Enact
    2.sunjitan 00193151   2012-05-31  Modify      原只处理PS下的鉴权拒绝，改为所有鉴权拒绝均处理
*****************************************************************************/
VOS_UINT32  NAS_EMM_PreProcMsgMmcActionRstReq( MsgBlock * pMsg )
{
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pMmcActResult = VOS_NULL_PTR;
    NAS_LMM_MAIN_STATE_ENUM_UINT16      enPreMainState;
    /* 保存当前状态用于判断gu action是否引起emm状态改变 */
    enPreMainState = NAS_LMM_GetEmmCurFsmMS();

    pMmcActResult = (MMC_LMM_ACTION_RESULT_REQ_STRU *)pMsg;

    NAS_EMM_PUBU_LOG2_NORM("NAS_EMM_PreProcMsgMmcActionRstReq: enActionType = , ulActRst = ",
                            pMmcActResult->enActionType,
                            pMmcActResult->ulActRst);
    TLPS_PRINT2LAYER_INFO2(NAS_EMM_PreProcMsgMmcActionRstReq_ENUM,LNAS_FUNCTION_LABEL1,
                            pMmcActResult->enActionType,
                            pMmcActResult->ulActRst);

    /* 若非挂起态，丢弃不处理 */
    if(NAS_LMM_CUR_LTE_ACTIVE == NAS_EMM_GetCurLteState())
    {
        NAS_EMM_PUBU_LOG1_NORM("NAS_EMM_PreProcMsgMmcActionRstReq: NAS_EMM_GetCurLteState = , ",
                            NAS_EMM_GetCurLteState());
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_PreProcMsgMmcActionRstReq_ENUM,LNAS_FUNCTION_LABEL2,
                            NAS_EMM_GetCurLteState());

        return NAS_LMM_MSG_HANDLED;
    }

    /* 若非DEREG.NOCELLAVAILABLE,DEREG.NOIMSI,REG.NOCELLAVAILABLE三个状态，丢弃该消息*/
    if(NAS_EMM_STATE_INVALID == NAS_EMM_CheckMmcActionRstReqStateValid())
    {
        NAS_EMM_PUBU_LOG2_NORM("NAS_EMM_PreProcMsgMmcActionRstReq: NAS_EMM_CUR_MAIN_STAT  = , NAS_EMM_CUR_SUB_STAT = ",
                            NAS_EMM_CUR_MAIN_STAT,
                            NAS_EMM_CUR_SUB_STAT);

        TLPS_PRINT2LAYER_INFO1(NAS_EMM_PreProcMsgMmcActionRstReq_ENUM,LNAS_EMM_MAIN_STATE,
                            NAS_EMM_CUR_MAIN_STAT);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_PreProcMsgMmcActionRstReq_ENUM,LNAS_EMM_SUB_STATE,
                            NAS_EMM_CUR_SUB_STAT);


        return NAS_LMM_MSG_HANDLED;
    }

    /*保存消息到本地*/
    NAS_EMM_SaveGuActRstPara(pMsg);

    /*鉴权拒绝GU模CS、PS、CS_PS的处理相同，L模也均按照卡无效处理 */
    if (MMC_LMM_RSLT_TYPE_AUTH_REJ == pMmcActResult->ulActRst)
    {
        /*处理同拒绝原因3*/
        NAS_EMM_ProcGuDettRejCause3();
        /*因GU的action可能引起EMM状态改变，若EMM状态发生改变向ESM发送StatusInd消息*/
        NAS_EMM_GuActionSendStatusInd(enPreMainState);

        return NAS_LMM_MSG_HANDLED;
    }

    /* 根据业务类型，调用不同模块提供的处理函数 */
    NAS_EMM_GuActionMsgDistr(pMsg);

    /*因GU的action可能引起EMM状态改变，若EMM状态发生改变向ESM发送StatusInd消息*/
    NAS_EMM_GuActionSendStatusInd(enPreMainState);

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SaveGuActRstPara
 Description     : 将GU动作结果消息保存至本地
 Input           : MsgBlock * pMsg
 Output          : None
 Return          : VOS_VOID

 History         :
    1.Zhangcaixia 00179470      2011-5-30  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_SaveGuActRstPara( MsgBlock * pMsg  )
{
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pMmcActResult = VOS_NULL_PTR;

    pMmcActResult = (MMC_LMM_ACTION_RESULT_REQ_STRU *)pMsg;

    NAS_EMM_GetGuActType() = pMmcActResult->enActionType;
    NAS_EMM_GetGuActRst()  = pMmcActResult->ulActRst;
    NAS_EMM_GetGuActRstOpReqDomain() = pMmcActResult->bitOpReqDomain;
    NAS_EMM_GetGuActReqDomain() = pMmcActResult->ulReqDomain;
    NAS_EMM_GetGuActRstOpRstDomain()= pMmcActResult->bitOpRstDomain;
    NAS_EMM_GetGuActRstDomain() = pMmcActResult->ulRstDomain;
    NAS_EMM_GetGuActRstOpMtDetachType()= pMmcActResult->bitOpMtDetachType;
    NAS_EMM_GetGuActMtDetachType() = pMmcActResult->ulMtDetachType;
    NAS_EMM_GetGuActRstOpCnCause() = pMmcActResult->bitOpCnCause;
    NAS_EMM_GetGuActCnCause() = pMmcActResult->ucCnCause;
    NAS_EMM_GetGuActRstOpAtmpCnt() = pMmcActResult->bitOpAtmpCnt;
    NAS_EMM_GetGuActAttemptCount() = pMmcActResult->ulAttemptCount;

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_CheckMmcActionRstReqStateValid
 Description     : 判断接收MMC的ActionResultReq消息的状态是否正确
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.Zhangcaixai 00179470      2011-5-28  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_CheckMmcActionRstReqStateValid( VOS_VOID )
{
    VOS_UINT32                          ulRet = NAS_EMM_STATE_INVALID;
    VOS_UINT32                          ulCurEmmStat;

    ulCurEmmStat = NAS_LMM_PUB_COMP_EMMSTATE(NAS_EMM_CUR_MAIN_STAT,
                                            NAS_EMM_CUR_SUB_STAT);

    switch(ulCurEmmStat)
    {
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_DEREG, EMM_SS_DEREG_NO_CELL_AVAILABLE):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_DEREG, EMM_SS_DEREG_NO_IMSI):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_NO_CELL_AVAILABLE):

                ulRet = NAS_EMM_STATE_VALID;
                break;
        default    :
                break;
    }
    return ulRet;
}
/*****************************************************************************
 Function Name   : NAS_EMM_GuActionMsgDistr
 Description     : GU Action分发处理
 Input           : MsgBlock * pMsg
 Output          : None
 Return          : VOS_VOID

 History         :
    1.Zhangcaixia 00179470      2011-5-30  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_GuActionMsgDistr( MsgBlock * pMsg  )
{
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pMmcActResult = VOS_NULL_PTR;

    pMmcActResult = (MMC_LMM_ACTION_RESULT_REQ_STRU *)pMsg;

    switch(pMmcActResult->enActionType)
    {
        case    MMC_LMM_ACTION_ATTACH:
                NAS_EMM_ProGuAttachRst(pMsg);
                break;

        case    MMC_LMM_ACTION_RAU:

        case    MMC_LMM_ACTION_PERIODC_RAU:
                NAS_EMM_ProGuRauRst(pMsg);
                break;
        case    MMC_LMM_ACTION_MT_DETACH:
                NAS_EMM_ProGuMtDetachRst(pMsg);
                break;

        case    MMC_LMM_ACTION_LOCAL_DETACH:
                NAS_EMM_ProGuLocalDetachRst(pMsg);
                break;

        case    MMC_LMM_ACTION_MO_DETACH:
                NAS_EMM_ProGuMoDetachRst(pMsg);
                break;
        case    MMC_LMM_ACTION_LAU:
                NAS_EMM_ProGuLauRst(pMsg);
                break;

        case    MMC_LMM_ACTION_PS_SERVICE_REQ:
                NAS_EMM_ProGuServiceRst(pMsg);
                break;

        case    MMC_LMM_ACTION_CM_REQ:
                NAS_EMM_ProGuCmRst(pMsg);
                break;
        case    MMC_LMM_ACTION_MM_ABORT:
                NAS_EMM_ProGuAbortRst(pMsg);
                break;

        default    :
                NAS_EMM_PUBU_LOG_NORM("NAS_EMM_PreProcMsgMmcActionRstReq: default RST.");
                TLPS_PRINT2LAYER_INFO(NAS_EMM_GuActionMsgDistr_ENUM,LNAS_FUNCTION_LABEL1);
                break;
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_GuActionSendStatusInd
 Description     : 因GU的action导致EMM状态有可能改变，向ESM发送StatusInd消息
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.Zhangcaixia 00179470      2011-5-30  Draft Enact
    2.leixiantiao 00258641      2014-6-9 判断当前状态是否改变,若没有改变则不给esm发送相应状态信息
*****************************************************************************/
VOS_VOID  NAS_EMM_GuActionSendStatusInd( NAS_LMM_MAIN_STATE_ENUM_UINT16 enPreMainState)
{
    /* 判断当前状态是否改变,若没有改变则不给esm发送相应状态信息 */
    if(NAS_EMM_CUR_MAIN_STAT == enPreMainState)
    {
        return;
    }
    /*根据当前状态，向ESM发相应的状态信息*/
    if(EMM_MS_REG == NAS_EMM_CUR_MAIN_STAT )
    {
        /* 通知ESM状态改变 */
        NAS_EMM_PUB_SendEsmStatusInd(EMM_ESM_ATTACH_STATUS_ATTACHED);
    }
    else if(EMM_MS_DEREG == NAS_EMM_CUR_MAIN_STAT)
    {
        /* 通知ESM状态改变 */
        NAS_EMM_PUB_SendEsmStatusInd(EMM_ESM_ATTACH_STATUS_DETACHED);
    }
    else
    {
        NAS_EMM_PUBU_LOG1_NORM("NAS_EMM_PreProcMsgMmcActionRstReq: NAS_EMM_GetCurLteState = . ",
                            NAS_EMM_GetCurLteState());
        TLPS_PRINT2LAYER_INFO(NAS_EMM_GuActionSendStatusInd_ENUM,LNAS_FUNCTION_LABEL1);
    }
    return;
}
/*****************************************************************************
 Function Name   : NAS_EMM_GuAttachActionRej
 Description     : GU attach 结果域为CN REJ时处理
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.Zhangcaixia 00179470      2011-5-30  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_GuAttachActionRej( MsgBlock * pMsg  )
{
    /*不再判断请求域和结果域，只根据原因值进行处理*/
    NAS_EMM_GuCombinedAndPsOnlyAttachRej(pMsg);


}
/*****************************************************************************
 Function Name   : NAS_EMM_CheckGuActReqDomainCmbRstDomainCmb
 Description     : 判断GU的Combined Action Domain为req为Combined， rst为Combined
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.Zhangcaixai 00179470      2011-5-28  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_CheckGuActReqDomainCmbRstDomainCmb( MsgBlock * pMsg  )
{

    MMC_LMM_ACTION_RESULT_REQ_STRU     *pMmcActResult = VOS_NULL_PTR;

    pMmcActResult = (MMC_LMM_ACTION_RESULT_REQ_STRU *)pMsg;

    if(((NAS_EMM_PUBU_BIT_SLCT == pMmcActResult->bitOpReqDomain)
     &&(MMC_LMM_COMBINED_PS_IMSI == pMmcActResult->ulReqDomain))
     &&((NAS_EMM_PUBU_BIT_SLCT == pMmcActResult->bitOpRstDomain)
     &&(MMC_LMM_COMBINED_PS_IMSI == pMmcActResult->ulRstDomain)))
    {
        return NAS_EMM_SUSPEND_GU_ACT_DOMAIN_YES;
    }

    return NAS_EMM_SUSPEND_GU_ACT_DOMAIN_NO;
}
/*****************************************************************************
 Function Name   : NAS_EMM_CheckGuActReqDomainPsRstDomainPs
 Description     : 判断GU的ACTION是否PS_only ActionDomain结果域也为PS_only
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.Zhangcaixai 00179470      2011-5-30  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_CheckGuActReqDomainPsRstDomainPs( MsgBlock * pMsg  )
{
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pMmcActResult = VOS_NULL_PTR;

    pMmcActResult = (MMC_LMM_ACTION_RESULT_REQ_STRU *)pMsg;

    if(((NAS_EMM_PUBU_BIT_SLCT == pMmcActResult->bitOpReqDomain)
     &&(MMC_LMM_PS_ONLY == pMmcActResult->ulReqDomain))
     &&((NAS_EMM_PUBU_BIT_SLCT == pMmcActResult->bitOpRstDomain)
     &&(MMC_LMM_PS_ONLY == pMmcActResult->ulRstDomain)))
    {
        return NAS_EMM_SUSPEND_GU_ACT_DOMAIN_YES;
    }

    return NAS_EMM_SUSPEND_GU_ACT_DOMAIN_NO;
}
/*****************************************************************************
 Function Name   : NAS_EMM_CheckGuActReqDomainCombiRstDomainPs
 Description     : 判断GU的REQ_Domain为PS/IMSI结果域为PS_only
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.Zhangcaixai 00179470      2011-5-30  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_CheckGuActReqDomainCombiRstDomainPs( MsgBlock * pMsg  )
{
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pMmcActResult = VOS_NULL_PTR;

    pMmcActResult = (MMC_LMM_ACTION_RESULT_REQ_STRU *)pMsg;

    if(((NAS_EMM_PUBU_BIT_SLCT == pMmcActResult->bitOpReqDomain)
       &&(MMC_LMM_COMBINED_PS_IMSI == pMmcActResult->ulReqDomain))
       &&((NAS_EMM_PUBU_BIT_SLCT == pMmcActResult->bitOpRstDomain)
       &&(MMC_LMM_PS_ONLY == pMmcActResult->ulRstDomain)))
    {
        return NAS_EMM_SUSPEND_GU_ACT_DOMAIN_YES;
    }

    return NAS_EMM_SUSPEND_GU_ACT_DOMAIN_NO;
}

/*****************************************************************************
 Function Name   : NAS_EMM_CheckMmUpStateAndLaiChange
 Description     : 判断MM的UPDATE STATE是否为U1且LAI没有变更
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2012-6-5  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_CheckMmUpStateAndLaiChange( MsgBlock * pMsg  )
{
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pMmcActResult = VOS_NULL_PTR;

    pMmcActResult = (MMC_LMM_ACTION_RESULT_REQ_STRU *)pMsg;

    if(((NAS_EMM_PUBU_BIT_SLCT == pMmcActResult->bitOpCsUpdateStatus)
            && (MMC_LMM_CS_UPDATE_STATUS_UPDATED != pMmcActResult->ucCsUpdateStatus))
        || ((NAS_EMM_PUBU_BIT_SLCT == pMmcActResult->bitOpLaiChangFlg)
            && (VOS_TRUE == pMmcActResult->ucLaiChangFlg)))
    {
        return NAS_EMM_SUCC;
    }

    return NAS_EMM_FAIL;
}
/*****************************************************************************
 Function Name   : NAS_EMM_CheckMmUpStateAndLaiChange
 Description     : 判断GPRS的UPDATE STATE是否为GU1且RAI没有变更
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2012-6-5  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_CheckGprsUpStateAndRaiChange( MsgBlock * pMsg  )
{
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pMmcActResult = VOS_NULL_PTR;

    pMmcActResult = (MMC_LMM_ACTION_RESULT_REQ_STRU *)pMsg;

    if(((NAS_EMM_PUBU_BIT_SLCT == pMmcActResult->bitOpGprsUpdateStatus)
            && (MMC_LMM_GPRS_UPDATE_STATUS_UPDATED != pMmcActResult->ucGprsUpdateStatus))
        || ((NAS_EMM_PUBU_BIT_SLCT == pMmcActResult->bitOpRaiChangFlg)
            && (VOS_TRUE == pMmcActResult->ucRaiChangFlg)))
    {
        return NAS_EMM_SUCC;
    }

    return NAS_EMM_FAIL;
}

/*****************************************************************************
 Function Name   : NAS_EMM_RetainCsRegDomainUnchangeProcess
 Description     : CS注册域不变,PS去注册
                    状态转换到DEREG态时,注册域更新为NULL,为了保持CS注册域不变
                    进行以下步骤:
                    1.保存当前注册域
                    2.状态转换
                    3.更新保存的注册域进行注册域更新
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.leili 00132387      2012-6-11  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_ProcCsDomainRetainPsDomainNull
(
    NAS_EMM_SUB_STATE_ENUM_UINT16   usSs
)
{
    NAS_LMM_REG_DOMAIN_ENUM_UINT32      enRegDoamin;

    /*保存当前注册域*/
    enRegDoamin = NAS_LMM_GetEmmInfoRegDomain();

    /*进入DEREG的状态*/
    NAS_EMM_PUBU_FSMTranState(          EMM_MS_DEREG,
                                        usSs,
                                        TI_NAS_EMM_STATE_NO_TIMER);

    /*更新注册域状态*/
    if(NAS_LMM_REG_DOMAIN_CS_PS == enRegDoamin)
    {
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_CS);
    }
    else if(NAS_LMM_REG_DOMAIN_CS == enRegDoamin)
    {
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_CS);
    }
    else
    {
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_NULL);
    }
    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_ProcPsDomainRetainCsDomainNull
 Description     : PS注册域不变,CS去注册

 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.leili 00132387      2012-6-11  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_ProcPsDomainRetainCsDomainNull( VOS_VOID)
{
    /*更新注册域状态*/
    if (NAS_LMM_REG_DOMAIN_CS_PS == NAS_LMM_GetEmmInfoRegDomain())
    {
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
    }
    else if (NAS_LMM_REG_DOMAIN_PS == NAS_LMM_GetEmmInfoRegDomain())
    {
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
    }
    else
    {
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_NULL);
    }
    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_GuCombinedAndPsOnlyAttachRej
 Description     : GU attach REJ时，Combined与PS only处理一样
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.Zhangcaixia 00179470      2011-5-30  Draft Enact
    2.sunjitan 00193151        2012-05-31  Modify     #25原因值也按照other处理
*****************************************************************************/
VOS_VOID  NAS_EMM_GuCombinedAndPsOnlyAttachRej( MsgBlock * pMsg  )
{
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pMmcActResult = VOS_NULL_PTR;

    pMmcActResult = (MMC_LMM_ACTION_RESULT_REQ_STRU *)pMsg;

    /*GU在CN REJ时一定会将bitOpCnCause置为TURE,此处不在容错*/

    switch(pMmcActResult->ucCnCause)
    {
        /* #3,6,7,8走#3原因值处理 */
        case NAS_LMM_CAUSE_ILLEGAL_UE:
        case NAS_LMM_CAUSE_ILLEGAL_ME:
        case NAS_LMM_CAUSE_EPS_SERV_AND_NON_EPS_SERV_NOT_ALLOW:

            NAS_EMM_ProcGuAttRejCause3();

            break;

        case NAS_LMM_CAUSE_EPS_SERV_NOT_ALLOW:
            NAS_EMM_ProcGuAttRejCause7();
            break;

        /* attach #11,12,13,15走#11原因值处理 */
        case NAS_LMM_CAUSE_PLMN_NOT_ALLOW:
        case NAS_LMM_CAUSE_TA_NOT_ALLOW:
        case NAS_LMM_CAUSE_ROAM_NOT_ALLOW:
        case NAS_LMM_CAUSE_NO_SUITABL_CELL:

            NAS_EMM_ProcGuAttachRejCause11();

            break;

        case NAS_LMM_CAUSE_EPS_SERV_NOT_ALLOW_IN_PLMN:
            NAS_EMM_ProcGuAttachRejCause14();
            break;

        /*#95,96,97,99,101,GU下处理将AttachAttempCounter置为5*/
        case NAS_LMM_CAUSE_SEMANTICALLY_INCORRECT_MSG:
        case NAS_LMM_CAUSE_INVALID_MANDATORY_INF:
        case NAS_LMM_CAUSE_MSG_NONEXIST_NOTIMPLEMENTE:
        case NAS_LMM_CAUSE_IE_NONEXIST_NOTIMPLEMENTED:
        case NAS_LMM_CAUSE_MSG_NOT_COMPATIBLE:

            /*进入attach=5的处理*/
            NAS_EMM_ProcGuAttachAttemptCounterEq5(pMsg);

            break;

        /*其余原因值处理，将AttachAttempCounter加1，直至AttachAttempCounter为5时L才处理*/
        default:

            NAS_EMM_ProcGuAttachAttemptCounterEq5(pMsg);

            break;
    }
}

/*****************************************************************************
 Function Name   : NAS_EMM_GuRauActionRej
 Description     : GU Rau 结果域为CN REJ时处理
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.Zhangcaixia 00179470      2011-5-30  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_GuRauActionRej( MsgBlock * pMsg  )
{
    /*不再判断请求域和注册域，只根据原因值进行处理*/
    NAS_EMM_GuCmbAndPsOnlyRauRej(pMsg);

}
/*****************************************************************************
 Function Name   : NAS_EMM_GuCombinedAndPsOnlyRauRej
 Description     : GU Rau REJ时，Combined与PS only处理一样
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.Zhangcaixia 00179470      2011-5-30  Draft Enact
    2.sunjitan 00193151        2012-05-31  Modify     #25原因值也按照other处理
*****************************************************************************/
VOS_VOID  NAS_EMM_GuCmbAndPsOnlyRauRej( MsgBlock * pMsg  )
{
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pMmcActResult = VOS_NULL_PTR;

    pMmcActResult = (MMC_LMM_ACTION_RESULT_REQ_STRU *)pMsg;

    /*结果为CN_REJ时，GU一定携带CN CAUSE,不再对bitOpCnCause容错*/
    switch(pMmcActResult->ucCnCause)
    {
        /* #3,6走#3原因值处理*/
        case    NAS_LMM_CAUSE_ILLEGAL_UE:
        case    NAS_LMM_CAUSE_ILLEGAL_ME:
            NAS_EMM_ProcGuDettRejCause3();
            break;

        case    NAS_LMM_CAUSE_EPS_SERV_NOT_ALLOW:
            NAS_EMM_ProcGuDettRejCause7();
            break;

        case    NAS_LMM_CAUSE_EPS_SERV_AND_NON_EPS_SERV_NOT_ALLOW:
            if (NAS_RELEASE_R11)
            {
                NAS_EMM_PUBU_LOG_NORM("NAS_EMM_GuCmbAndPsOnlyRauRej : CS_PS!!!");
                TLPS_PRINT2LAYER_INFO(NAS_EMM_GuCmbAndPsOnlyRauRej_ENUM,LNAS_FUNCTION_LABEL1);
                NAS_EMM_ProcGuDettRejCause3();
            }
            else
            {
                /*如果是在PS Only的情况下，原因值8按照other case处理*/
                if(NAS_EMM_SUSPEND_GU_ACT_DOMAIN_YES == NAS_EMM_CheckGuActReqDomainPsRstDomainPs(pMsg))
                {
                    NAS_EMM_PUBU_LOG_NORM("NAS_EMM_GuCmbAndPsOnlyRauRej : PS_only!!!");
                    TLPS_PRINT2LAYER_INFO(NAS_EMM_GuCmbAndPsOnlyRauRej_ENUM,LNAS_FUNCTION_LABEL2);
                    NAS_EMM_ProcGuRauAttemptCounter(pMsg);
                }
                /*如果是在CS/PS的情况下，原因值8按照原因值3的处理*/
                else
                {
                    NAS_EMM_PUBU_LOG_NORM("NAS_EMM_GuCmbAndPsOnlyRauRej : CS_PS!!!");
                    TLPS_PRINT2LAYER_INFO(NAS_EMM_GuCmbAndPsOnlyRauRej_ENUM,LNAS_FUNCTION_LABEL3);
                    NAS_EMM_ProcGuDettRejCause3();
                }
            }
            break;

        /*#9原因值处理*/
        case    NAS_LMM_CAUSE_UE_ID_NOT_DERIVED:

            NAS_EMM_ProcGuRauSerRejCause9();
            break;

        /*#10原因值处理*/
        case    NAS_LMM_CAUSE_IMPLICIT_DETACHED:

            if (NAS_EMM_SUSPEND_GU_ACT_DOMAIN_YES == NAS_EMM_CheckGuActReqDomainCmbRstDomainCmb(pMsg))
            {
                NAS_EMM_PUBU_FSMTranState(  EMM_MS_DEREG,
                                            EMM_SS_DEREG_NO_CELL_AVAILABLE,
                                            TI_NAS_EMM_STATE_NO_TIMER);

            }
            else
            {
                /*保持CS域保持不变,PS域去注册*/
                NAS_EMM_ProcCsDomainRetainPsDomainNull(EMM_SS_DEREG_NO_CELL_AVAILABLE);
            }

            break;

        /*#11,12*/
        case    NAS_LMM_CAUSE_PLMN_NOT_ALLOW:
        case    NAS_LMM_CAUSE_TA_NOT_ALLOW:

            NAS_EMM_ProcGuRauSerRejCause11();

            /*清除TAU Attempt Counter*/
            NAS_EMM_TAU_SaveEmmTAUAttemptCnt(NAS_EMM_TAU_ATTEMPT_CNT_ZERO);
            break;

        case    NAS_LMM_CAUSE_EPS_SERV_NOT_ALLOW_IN_PLMN:
            NAS_EMM_ProcGuRauSerRejCause14();

            /*清除TAU Attempt Counter*/
            NAS_EMM_TAU_SaveEmmTAUAttemptCnt(NAS_EMM_TAU_ATTEMPT_CNT_ZERO);
            break;

        /* #25原因值按照other处理 */
        /*#13,15*/
        case    NAS_LMM_CAUSE_ROAM_NOT_ALLOW:
        case    NAS_LMM_CAUSE_NO_SUITABL_CELL:
            NAS_EMM_ProcGuRauSerRejCause13();

            /*清除TAU Attempt Counter*/
            NAS_EMM_TAU_SaveEmmTAUAttemptCnt(NAS_EMM_TAU_ATTEMPT_CNT_ZERO);
            break;

        /*#95,96,97,99,101,GU下处理将AttachAttempCounter置为5*/
        case    NAS_LMM_CAUSE_SEMANTICALLY_INCORRECT_MSG:
        case    NAS_LMM_CAUSE_INVALID_MANDATORY_INF:
        case    NAS_LMM_CAUSE_MSG_NONEXIST_NOTIMPLEMENTE:
        case    NAS_LMM_CAUSE_IE_NONEXIST_NOTIMPLEMENTED:
        case    NAS_LMM_CAUSE_MSG_NOT_COMPATIBLE:

            /* 走RauAttmeptCounter的处理，RauAttemptCounter为5，设置为EU2*/
            NAS_EMM_ProcGuRauAttemptCounter(pMsg);
            break;

        /*其余原因值处理，将RAUAttempCounter加1，走RAUAttempCounter的处理*/
        default    :
            NAS_EMM_ProcGuRauAttemptCounter(pMsg);
            break;
    }
    return;
}

/*****************************************************************************
Function Name   : NAS_EMM_GuLauActionRej
Description     : GU LAU REJ处理
Input           : None
Output          : None
Return          : VOS_VOID

History         :
 1.leili 00132387      2012-6-6  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_EMM_GuLauActionRej( MsgBlock * pMsg  )
{
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pMmcActResult = VOS_NULL_PTR;

    pMmcActResult = (MMC_LMM_ACTION_RESULT_REQ_STRU *)pMsg;

    /*结果为CN_REJ时，GU一定携带CN CAUSE,不再对bitOpCnCause容错*/
    switch(pMmcActResult->ucCnCause)
    {
        case    NAS_LMM_CAUSE_IMSI_UNKNOWN_IN_HSS:
        case    NAS_LMM_CAUSE_ILLEGAL_UE:
        case    NAS_LMM_CAUSE_ILLEGAL_ME:
                NAS_EMM_PUBU_LOG_NORM("NAS_EMM_ProGuLauRst: LAU REJ,CAUSE2");
                TLPS_PRINT2LAYER_INFO(NAS_EMM_GuLauActionRej_ENUM,LNAS_CAUSE_NUMBER);

                /* 如果LAU被拒，原因值为2，则L模后续不能发起联合ATTACH和联合TAU */
                NAS_LMM_SetEmmInfoRejCause2Flag(NAS_EMM_REJ_YES);

                /*CS注册域更新为去注册,PS注册域不变*/
                NAS_EMM_ProcPsDomainRetainCsDomainNull();
                break;

        /*#11,#12,#13,#15走#3原因值处理*/
        case    NAS_LMM_CAUSE_PLMN_NOT_ALLOW:
        case    NAS_LMM_CAUSE_TA_NOT_ALLOW:
        case    NAS_LMM_CAUSE_ROAM_NOT_ALLOW:
        case    NAS_LMM_CAUSE_NO_SUITABL_CELL:

                /*CS注册域更新为去注册,PS注册域不变*/
                NAS_EMM_ProcPsDomainRetainCsDomainNull();
                break;
        default:
                NAS_EMM_ProcGuLauAttemptCounter(pMsg);
                break;

    }
}


/*****************************************************************************
 Function Name   : NAS_EMM_ProcGuRauAttemptCounter
 Description     : GU RauAttemptCounter为5的处理过程
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.Zhangcaixia 00179470      2011-5-27  Draft Enact
    2.lihong 00150010           2012-12-18 Modify:Emergency

*****************************************************************************/
VOS_VOID  NAS_EMM_ProcGuRauAttemptCounter (MsgBlock * pMsg )
{
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pMmcActResult = VOS_NULL_PTR;

    pMmcActResult = (MMC_LMM_ACTION_RESULT_REQ_STRU *)pMsg;

    if((NAS_EMM_PUBU_BIT_SLCT == pMmcActResult->bitOpAtmpCnt)
     &&(5 <= pMmcActResult->ulAttemptCount))
    {
        /* RauAttemptCounter为5，设置为EU2*/
        NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_NOT_UPDATED_EU2);

        if (NAS_LMM_REG_STATUS_EMC_REGED != NAS_LMM_GetEmmInfoRegStatus())
        {
            /*保存PS LOC信息*/
            NAS_LMM_WritePsLoc(NAS_NV_ITEM_UPDATE);
        }

        /*请求域和结果域都为PS_ONLY时,CS和PS域不变,请求域和结果域为CS+PS时,CS域去
        注册,PS域保持不变*/
        if (NAS_EMM_SUSPEND_GU_ACT_DOMAIN_YES == NAS_EMM_CheckGuActReqDomainCmbRstDomainCmb(pMsg))
        {
            /*CS域去注册,PS域保持不变*/
            NAS_EMM_ProcPsDomainRetainCsDomainNull();
        }
    }

    if((NAS_EMM_PUBU_BIT_SLCT == pMmcActResult->bitOpAtmpCnt)
     &&(5 > pMmcActResult->ulAttemptCount))
    {
        /* 如果GPRS update status不为GU1，或者RAI发生变更，则将EPS update status
           改为EU2 */
        if (NAS_EMM_SUCC == NAS_EMM_CheckGprsUpStateAndRaiChange(pMsg))
        {
            NAS_EMM_PUBU_LOG_NORM("NAS_EMM_ProcGuRauAttemptCounter:set eu2!");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcGuRauAttemptCounter_ENUM,LNAS_FUNCTION_LABEL1);
            NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_NOT_UPDATED_EU2);

            if (NAS_LMM_REG_STATUS_EMC_REGED != NAS_LMM_GetEmmInfoRegStatus())
            {
                /*保存PS LOC信息*/
                NAS_LMM_WritePsLoc(NAS_NV_ITEM_UPDATE);
            }
        }

        /*请求域和结果域都为PS_ONLY时,CS和PS域不变;请求域和结果域为CS+PS时,MM Update
        state不为U1或LAI改变,CS域去注册,PS域保持不变,否则,CS和PS域不变*/
        if ((NAS_EMM_SUSPEND_GU_ACT_DOMAIN_YES == NAS_EMM_CheckGuActReqDomainCmbRstDomainCmb(pMsg))
            && (NAS_EMM_SUCC == NAS_EMM_CheckMmUpStateAndLaiChange(pMsg)))
        {

            NAS_EMM_PUBU_LOG_NORM("NAS_EMM_ProcGuRauAttemptCounter:set eu2!");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcGuRauAttemptCounter_ENUM,LNAS_FUNCTION_LABEL2);

            /*CS域去注册,PS域保持不变*/
            NAS_EMM_ProcPsDomainRetainCsDomainNull();
        }
    }
    else
    {
        NAS_EMM_PUBU_LOG2_NORM("NAS_EMM_ProcGuRauAttemptCounter: ucCnCause = , ulAttemptCount = ",
                            pMmcActResult->ucCnCause,
                            pMmcActResult->ulAttemptCount);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_ProcGuRauAttemptCounter_ENUM,LNAS_CAUSE_NUMBER,
                            pMmcActResult->ucCnCause);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_ProcGuRauAttemptCounter_ENUM,LNAS_EMM_ATTEMPT_COUNTER,
                            pMmcActResult->ulAttemptCount);
    }
    return;
}
/*****************************************************************************
 Function Name   : NAS_EMM_GuAttachSuccCommonProcess
 Description     : GU ATTACH成功公共处理
 Input           : VOS_VOID
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2011-09-27  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMM_GuAttachSuccCommonProc( MsgBlock * pMsg )
{
    NAS_EMM_PUBU_FSMTranState(      EMM_MS_REG,
                                    EMM_SS_REG_NO_CELL_AVAILABLE,
                                    TI_NAS_EMM_STATE_NO_TIMER);

    if (NAS_EMM_SUSPEND_GU_ACT_DOMAIN_YES == NAS_EMM_CheckGuActReqDomainCmbRstDomainCmb(pMsg))
    {
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_CS_PS);
    }
    else
    {
        /*更新前注册域为CS或NULL:如果为CS,更新为CS+PS;如果为NULL,更新为PS*/
        if (NAS_LMM_REG_DOMAIN_CS == NAS_LMM_GetEmmInfoRegDomain())
        {
            NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_CS_PS);
        }
        else
        {
            NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
        }
    }

    /* If the UE initiates the first tracking area updating procedure following
       an attach in A/Gb mode or Iu mode, the UE shall include a UE radio
       capability information update needed IE in the TRACKING AREA UPDATE
       REQUEST message. 因此在GU模注册成功后，需要置上第一次TAU标识 */
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_GuAttachSuccCommonProc:set first tau");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_GuAttachSuccCommonProc_ENUM,LNAS_FUNCTION_LABEL1);
    NAS_LMM_SetEmmInfoFirstTauFlag(NAS_EMM_FIRST_TAU);
}

/*****************************************************************************
 Function Name   : NAS_EMM_ProGuAttachSucc
 Description     : 挂起状态下，处理GU发来的ATTACH成功结果
 Input           : VOS_VOID
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2011-09-26  Draft Enact
    2.sunjitan 00193151   2014-08-21  Mod: DTS2014082008149
*****************************************************************************/
VOS_VOID NAS_EMM_ProGuAttachSucc
(
    MsgBlock                           *pMsg
)
{
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pMmcActResult = VOS_NULL_PTR;

    pMmcActResult = (MMC_LMM_ACTION_RESULT_REQ_STRU *)pMsg;

    /* s00193151 DTS2014082008149:  GU下PS注册成功，需要将注册状态设置
       为正常注册，避免在后续收到ANY CELL系统消息时，被误认为是EMC注册 */
    NAS_LMM_SetEmmInfoRegStatus(NAS_LMM_REG_STATUS_NORM_REGED);
    if (NAS_RELEASE_R11)
    {
        /* 将ATTACH的尝试次数清零 */
        NAS_EMM_GLO_AD_GetAttAtmpCnt()      = 0;
    }

    if ((NAS_EMM_SUSPEND_GU_ACT_DOMAIN_YES == NAS_EMM_CheckGuActReqDomainPsRstDomainPs(pMsg))
        || (NAS_EMM_SUSPEND_GU_ACT_DOMAIN_YES == NAS_EMM_CheckGuActReqDomainCmbRstDomainCmb(pMsg)))
    {
        /* GU ATTACH成功公共处理 */
        NAS_EMM_GuAttachSuccCommonProc(pMsg);
        return ;
    }

    if (NAS_EMM_SUSPEND_GU_ACT_DOMAIN_YES == NAS_EMM_CheckGuActReqDomainCombiRstDomainPs(pMsg))
    {
        /* GU ATTACH成功公共处理 */
        /*NAS_EMM_GuAttachSuccCommonProc(pMsg);*/
        NAS_EMM_PUBU_FSMTranState(      EMM_MS_REG,
                                        EMM_SS_REG_NO_CELL_AVAILABLE,
                                        TI_NAS_EMM_STATE_NO_TIMER);

        /*更新CS域去注册，PS域注册*/
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);

        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_ProGuAttachSucc:set first tau");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProGuAttachSucc_ENUM,LNAS_FUNCTION_LABEL1);
        NAS_LMM_SetEmmInfoFirstTauFlag(NAS_EMM_FIRST_TAU);

        /* 如果联合ATTACH,GPRS成功ONLY，原因值为2，则L模后续不能发起联合ATTACH和联合TAU */
        if ((NAS_EMM_PUBU_BIT_SLCT == pMmcActResult->bitOpCnCause)
            && (NAS_EMM_CAUSE_IMSI_UNKNOWN_IN_HSS == pMmcActResult->ucCnCause))
        {
            NAS_LMM_SetEmmInfoRejCause2Flag(NAS_EMM_REJ_YES);
        }

        return ;
    }
}

/*****************************************************************************
 Function Name   : NAS_EMM_ProGuAttachRst
 Description     : 挂起状态下，处理GU发来的ATTACH结果
 Input           : VOS_VOID
 Output          : None
 Return          : VOS_VOID

 History         :
    1.Hanlufeng 41410      2011-5-12  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMM_ProGuAttachRst( MsgBlock * pMsg )
{
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pMmcActResult = VOS_NULL_PTR;

    pMmcActResult = (MMC_LMM_ACTION_RESULT_REQ_STRU *)pMsg;


    NAS_EMM_ATTACH_LOG1_NORM("NAS_EMM_ProGuAttachRst: ulActRst = .",
                            pMmcActResult->ulActRst);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_ProGuAttachRst_ENUM,LNAS_ACT_RESULT,
                            pMmcActResult->ulActRst);

    /*只有请求域与结果域同时为PS ONLY或者PS/IMSI时，
      或者联合注册只有PS成功且网侧携带原因值为#2,16,17,22
      结果才为SUCC*/
    if(MMC_LMM_RSLT_TYPE_SUCCESS == pMmcActResult->ulActRst)
    {
        NAS_EMM_ProGuAttachSucc(pMsg);
    }

    /*GU因网络无响应(超时和底层失败)导致的失败
      和网络没有携带原因值时的处理,此时的请求域和结果域都为PS ONLY或PS/IMSI，
      请求域为PS/IMSI结果域为PS ONLY，应以MMC_LMM_RSLT_TYPE_CN_REJ 或 FAILURE形式下发
      请求域为CS ONLY结果域为CS ONLY不处理*/
    else if ( (MMC_LMM_RSLT_TYPE_FAILURE == pMmcActResult->ulActRst)
            &&((NAS_EMM_SUSPEND_GU_ACT_DOMAIN_YES == NAS_EMM_CheckGuActReqDomainPsRstDomainPs(pMsg))
             ||(NAS_EMM_SUSPEND_GU_ACT_DOMAIN_YES == NAS_EMM_CheckGuActReqDomainCmbRstDomainCmb(pMsg))))
    {

        /*只有AttachAttempCounter=5时才处理*/
        NAS_EMM_ProcGuAttachAttemptCounterEq5(pMsg);

    }

    /*GU在PS only和PS/IMSI的网络拒绝，
      及请求域为PS/IMSI，结果域为PS时都以CN_Rej通知给L
      请求域和结果域的判断在处理函数内部*/
    else if(MMC_LMM_RSLT_TYPE_CN_REJ == pMmcActResult->ulActRst)
    {

        NAS_EMM_GuAttachActionRej(pMsg);
    }
    else
    {
        NAS_EMM_ATTACH_LOG1_NORM("NAS_EMM_ProGuAttachRst: ulActRst = .",
                            pMmcActResult->ulActRst);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_ProGuAttachRst_ENUM,LNAS_ACT_RESULT,
                            pMmcActResult->ulActRst);

    }
    return;
}
/*****************************************************************************
 Function Name   : NAS_EMM_ProGuRauRstSucc
 Description     : 挂起状态下，处理GU发来的RAU成功结果
 Input           : VOS_VOID
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2011-09-23  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMM_ProGuRauRstSucc
(
    MsgBlock                           *pMsg
)
{
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pMmcActResult = VOS_NULL_PTR;

    pMmcActResult = (MMC_LMM_ACTION_RESULT_REQ_STRU *)pMsg;

    if (NAS_EMM_TRIGGER_TAU_RRC_REL_CONN_FAILURE == NAS_LMM_GetEmmInfoTriggerTauRrcRel())
    {
        NAS_LMM_SetEmmInfoTriggerTauRrcRel(NAS_EMM_TRIGGER_TAU_RRC_REL_NO);
    }

    if (NAS_EMM_SUSPEND_GU_ACT_DOMAIN_YES == NAS_EMM_CheckGuActReqDomainPsRstDomainPs(pMsg))
    {
        NAS_EMM_PUBU_FSMTranState(  EMM_MS_REG,
                                    EMM_SS_REG_NO_CELL_AVAILABLE,
                                    TI_NAS_EMM_STATE_NO_TIMER);

        /*更新前注册域只能为:CS+PS或PS:无论哪种都保持不变*/

        return ;
    }

    if (NAS_EMM_SUSPEND_GU_ACT_DOMAIN_YES == NAS_EMM_CheckGuActReqDomainCombiRstDomainPs(pMsg))
    {
        NAS_EMM_PUBU_FSMTranState(  EMM_MS_REG,
                                    EMM_SS_REG_NO_CELL_AVAILABLE,
                                    TI_NAS_EMM_STATE_NO_TIMER);

        /* 如果联合RAU,GPRS成功ONLY，原因值为2，则L模后续不能发起联合ATTACH和联合TAU */
        if ((NAS_EMM_PUBU_BIT_SLCT == pMmcActResult->bitOpCnCause)
            && (NAS_EMM_CAUSE_IMSI_UNKNOWN_IN_HSS == pMmcActResult->ucCnCause))
        {
            NAS_EMM_PUBU_LOG_NORM("NAS_EMM_ProGuRauRstSucc: RAU,GPRS ONLY,CAUSE2");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_ProGuRauRstSucc_ENUM,LNAS_FUNCTION_LABEL1);
            NAS_LMM_SetEmmInfoRejCause2Flag(NAS_EMM_REJ_YES);
        }

        /*更新前注册域只能为:CS+PS或PS:如果为CS+PS,更新为PS;如果为PS,就保持不变*/
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);


        return ;
    }

    /* 从GU到L的异系统变换，如果在GU曾经发起过LAU或者联合RAU成功，则需要发起TAU，
       TAU类型为combined TA/LA with IMSI attach */
    if (NAS_EMM_SUSPEND_GU_ACT_DOMAIN_YES == NAS_EMM_CheckGuActReqDomainCmbRstDomainCmb(pMsg))
    {
        NAS_EMM_PUBU_FSMTranState(  EMM_MS_REG,
                                    EMM_SS_REG_NO_CELL_AVAILABLE,
                                    TI_NAS_EMM_STATE_NO_TIMER);

        /*更新前注册域只能为:CS+PS或PS:无论哪种都更新为CS+PS*/
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_CS_PS);

        if (MMC_LMM_ACTION_PERIODC_RAU != pMmcActResult->enActionType)
        {
            /* 记录GU模曾经发起过联合RAU成功 */
            NAS_LMM_SetEmmInfoLauOrComRauFlag(NAS_EMM_LAU_OR_COMBINED_RAU_HAPPENED);
        }


        return ;
    }
}

/*****************************************************************************
 Function Name   : NAS_EMM_ProGuRauRst
 Description     : 挂起状态下，处理GU发来的RAU结果
 Input           : VOS_VOID
 Output          : None
 Return          : VOS_VOID

 History         :
    1.Zhangcaixia 00179470      2011-5-27  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMM_ProGuRauRst( MsgBlock * pMsg )
{
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pMmcActResult = VOS_NULL_PTR;

    pMmcActResult = (MMC_LMM_ACTION_RESULT_REQ_STRU *)pMsg;


    NAS_EMM_ATTACH_LOG1_NORM("NAS_EMM_ProGuRauRst: ulActRst = .",
                            pMmcActResult->ulActRst);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_ProGuRauRst_ENUM,LNAS_ACT_RESULT,
                            pMmcActResult->ulActRst);

    /*如果不是被bar，并且是非周期性的联合rau，都统一将标志置为happend*/
    if ((MMC_LMM_RSLT_TYPE_ACCESS_BARRED != pMmcActResult->ulActRst))
    {
        if ((NAS_EMM_SUSPEND_GU_ACT_DOMAIN_YES == NAS_EMM_CheckGuActReqDomainCmbRstDomainCmb(pMsg))
            && (MMC_LMM_ACTION_PERIODC_RAU != pMmcActResult->enActionType))
        {
            /* 记录GU模曾经发起过RAU */
            NAS_LMM_SetEmmInfoLauOrComRauFlag(NAS_EMM_LAU_OR_COMBINED_RAU_HAPPENED);
        }
    }

    /*只有请求域与结果域同时为PS ONLY或者PS/IMSI时，
      或者联合注册只有PS成功且网侧携带原因值为#2,16,17,22
      结果才为SUCC*/
    if( MMC_LMM_RSLT_TYPE_SUCCESS == pMmcActResult->ulActRst)
    {
        NAS_EMM_ProGuRauRstSucc(pMsg);
    }

     /*GU因网络无响应(超时和底层失败)导致的失败
      和网络没有携带原因值时的处理,此时的请求域和结果域都为PS ONLY或PS/IMSI，
      请求域为PS/IMSI结果域为PS ONLY，应以MMC_LMM_RSLT_TYPE_CN_REJ 或 FAILURE形式下发
      请求域为CS ONLY结果域为CS ONLY不处理*/
    else if ( (MMC_LMM_RSLT_TYPE_FAILURE == pMmcActResult->ulActRst)
             &&( (NAS_EMM_SUSPEND_GU_ACT_DOMAIN_YES == NAS_EMM_CheckGuActReqDomainPsRstDomainPs(pMsg))
               ||(NAS_EMM_SUSPEND_GU_ACT_DOMAIN_YES == NAS_EMM_CheckGuActReqDomainCmbRstDomainCmb(pMsg))))
    {
        /*按RauAttemptCounter来处理*/
        NAS_EMM_ProcGuRauAttemptCounter(pMsg);
    }
    else if(MMC_LMM_RSLT_TYPE_CN_REJ == pMmcActResult->ulActRst)
    {

        /*根据REJ消息的作用域与CN REJ的cause值来处理*/
        NAS_EMM_GuRauActionRej(pMsg);
    }
    else
    {
        NAS_EMM_ATTACH_LOG1_NORM("NAS_EMM_ProGuRauRst: ulActRst = .",
                            pMmcActResult->ulActRst);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_ProGuRauRst_ENUM,LNAS_ACT_RESULT,
                            pMmcActResult->ulActRst);
    }

    return;
}
/*****************************************************************************
 Function Name   : NAS_EMM_CheckGuMtDetachTypeImsi
 Description     : 判断GU的detach是IMSI detach
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.Zhangcaixai 00179470      2011-5-30  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_CheckGuMtDetachTypeImsi( MsgBlock * pMsg  )
{
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pMmcActResult = VOS_NULL_PTR;

    pMmcActResult = (MMC_LMM_ACTION_RESULT_REQ_STRU *)pMsg;


    if((NAS_EMM_PUBU_BIT_SLCT == pMmcActResult->bitOpReqDomain)
     &&(MMC_LMM_IMSI_ONLY == pMmcActResult->ulReqDomain)
     &&(NAS_EMM_PUBU_BIT_SLCT == pMmcActResult->bitOpRstDomain)
     &&(MMC_LMM_IMSI_ONLY == pMmcActResult->ulRstDomain)
     &&(NAS_EMM_PUBU_BIT_SLCT == pMmcActResult->bitOpMtDetachType)
     &&(MMC_LMM_MT_DET_IMSI == pMmcActResult->ulMtDetachType))
    {
        return NAS_EMM_SUSPEND_GU_ACT_DOMAIN_YES;
    }

    return NAS_EMM_SUSPEND_GU_ACT_DOMAIN_NO;
}

/*****************************************************************************
 Function Name   : NAS_EMM_CheckGuMtDetachTypePsReAttNotRequ
 Description     : 判断GU的detach是非IMSI detach,且re_attach_not_req
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.Zhangcaixai 00179470      2011-5-30  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_CheckGuMtDetachTypePsReAttNotRequ( MsgBlock * pMsg  )
{
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pMmcActResult = VOS_NULL_PTR;

    pMmcActResult = (MMC_LMM_ACTION_RESULT_REQ_STRU *)pMsg;


    if((NAS_EMM_PUBU_BIT_SLCT == pMmcActResult->bitOpReqDomain)
     &&(MMC_LMM_PS_ONLY == pMmcActResult->ulReqDomain)
     &&(NAS_EMM_PUBU_BIT_SLCT == pMmcActResult->bitOpRstDomain)
     &&(MMC_LMM_PS_ONLY == pMmcActResult->ulRstDomain)
     &&(NAS_EMM_PUBU_BIT_SLCT == pMmcActResult->bitOpMtDetachType)
     &&(MMC_LMM_MT_DET_REATTACH_NOT_REQUIRED == pMmcActResult->ulMtDetachType))
    {
        return NAS_EMM_SUSPEND_GU_ACT_DOMAIN_YES;
    }

    return NAS_EMM_SUSPEND_GU_ACT_DOMAIN_NO;
}

/*****************************************************************************
 Function Name   : NAS_EMM_CheckGuMtDetachTypePsReAttRequ
 Description     : 判断GU的detach是非IMSI detach,且re_attach_req
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.Zhangcaixai 00179470      2011-5-30  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_CheckGuMtDetachTypePsReAttRequ( MsgBlock * pMsg  )
{
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pMmcActResult = VOS_NULL_PTR;

    pMmcActResult = (MMC_LMM_ACTION_RESULT_REQ_STRU *)pMsg;


    if((NAS_EMM_PUBU_BIT_SLCT == pMmcActResult->bitOpReqDomain)
     &&(MMC_LMM_PS_ONLY == pMmcActResult->ulReqDomain)
     &&(NAS_EMM_PUBU_BIT_SLCT == pMmcActResult->bitOpRstDomain)
     &&(MMC_LMM_PS_ONLY == pMmcActResult->ulRstDomain)
     &&(NAS_EMM_PUBU_BIT_SLCT == pMmcActResult->bitOpMtDetachType)
     &&(MMC_LMM_MT_DET_REATTACH_REQUIRED == pMmcActResult->ulMtDetachType))
    {
        return NAS_EMM_SUSPEND_GU_ACT_DOMAIN_YES;
    }

    return NAS_EMM_SUSPEND_GU_ACT_DOMAIN_NO;
}

/*****************************************************************************
 Function Name   : NAS_EMM_ProGuMtDetachRstCauseValue
 Description     : reattach_not_requeired时处理GU发来的DETACH 的cause value
 Input           : VOS_VOID
 Output          : None
 Return          : VOS_VOID

 History         :
    1.Zhangcaixia 00179470      2011-5-30  Draft Enact
    2.sunjitan 00193151        2012-05-31  Modify     #25原因值也按照other处理
*****************************************************************************/
VOS_VOID NAS_EMM_ProGuMtDetachRstCauseValue( MsgBlock * pMsg )
{
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pMmcActResult = VOS_NULL_PTR;

    pMmcActResult = (MMC_LMM_ACTION_RESULT_REQ_STRU *)pMsg;

    if(NAS_EMM_PUBU_BIT_SLCT == pMmcActResult->bitOpCnCause)
    {
        switch(pMmcActResult->ucCnCause)
        {
            case NAS_LMM_CAUSE_IMSI_UNKNOWN_IN_HSS:
                /* 如果CN DETACH，reattach not required类型，原因值为2，
                   则L模后续不能发起联合ATTACH和联合TAU */
                NAS_LMM_SetEmmInfoRejCause2Flag(NAS_EMM_REJ_YES);


                /*CS域去注册,PS域保持不变*/
                NAS_EMM_ProcPsDomainRetainCsDomainNull();


                break;

            /* #3,6,8走#3原因值处理 */
            case NAS_LMM_CAUSE_ILLEGAL_UE:
            case NAS_LMM_CAUSE_ILLEGAL_ME:
            case NAS_LMM_CAUSE_EPS_SERV_AND_NON_EPS_SERV_NOT_ALLOW:

                NAS_EMM_ProcGuDettRejCause3();
                break;

            case NAS_LMM_CAUSE_EPS_SERV_NOT_ALLOW:
                NAS_EMM_ProcGuDettRejCause7();
                break;


            /* dettach #11,12,13,15走同 dettach #11原因值处理 */
            case NAS_LMM_CAUSE_PLMN_NOT_ALLOW:
            case NAS_LMM_CAUSE_TA_NOT_ALLOW:
            case NAS_LMM_CAUSE_ROAM_NOT_ALLOW:
            case NAS_LMM_CAUSE_NO_SUITABL_CELL:
                NAS_EMM_ProcGuDettachRejCause11();
                break;

            case NAS_LMM_CAUSE_EPS_SERV_NOT_ALLOW_IN_PLMN:
                NAS_EMM_ProcGuDettachRejCause14();
                break;


            /*其它原因值，及不带原因值时24008协议待补充,GU未处理
              24301Dereg，删除GUTI,LVR TAI,TAI LIST,KSI*/
            default:
                NAS_EMM_PUBU_LOG2_NORM("NAS_EMM_ProGuMtDetachRstCauseValue: ucCnCause = , ulAttemptCount = ",
                        pMmcActResult->ucCnCause,
                        pMmcActResult->ulAttemptCount);
                TLPS_PRINT2LAYER_INFO1(NAS_EMM_ProGuMtDetachRstCauseValue_ENUM,LNAS_CAUSE_NUMBER,
                        pMmcActResult->ucCnCause);
                TLPS_PRINT2LAYER_INFO1(NAS_EMM_ProGuMtDetachRstCauseValue_ENUM,LNAS_EMM_ATTEMPT_COUNTER,
                        pMmcActResult->ulAttemptCount);

                /*保持CS域保持不变,PS域去注册*/
                NAS_EMM_ProcCsDomainRetainPsDomainNull(EMM_SS_DEREG_NO_CELL_AVAILABLE);


                break;
        }

    }
    else
    {
        /*其它原因值，及不带原因值时24008协议待补充,GU进入Dereg.NormalService,
          且此时GU不给L携带原因值IE，见接口描述
          24301Dereg，删除GUTI,LVR TAI,TAI LIST,KSI*/
        NAS_EMM_PUBU_LOG2_NORM("NAS_EMM_ProGuMtDetachRstCauseValue: ucCnCause = , ulAttemptCount = ",
                        pMmcActResult->ucCnCause,
                        pMmcActResult->ulAttemptCount);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_ProGuMtDetachRstCauseValue_ENUM,LNAS_CAUSE_NUMBER,
                        pMmcActResult->ucCnCause);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_ProGuMtDetachRstCauseValue_ENUM,LNAS_EMM_ATTEMPT_COUNTER,
                        pMmcActResult->ulAttemptCount);

        /*保持CS域保持不变,PS域去注册*/
        NAS_EMM_ProcCsDomainRetainPsDomainNull(EMM_SS_DEREG_NO_CELL_AVAILABLE);

    }
}

/*****************************************************************************
 Function Name   : NAS_EMM_ProGuMoDetachRst
 Description     : 挂起状态下，处理GU发来的MO DETACH结果
 Input           : VOS_VOID
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010            2011-11-18   Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMM_ProGuMoDetachRst( MsgBlock * pMsg )
{
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pMmcActResult = VOS_NULL_PTR;

    pMmcActResult = (MMC_LMM_ACTION_RESULT_REQ_STRU *)pMsg;


    NAS_EMM_PUBU_LOG1_NORM("NAS_EMM_ProGuMoDetachRst: ulMoDetachType = ",
                            pMmcActResult->ulMoDetachType);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_ProGuMoDetachRst_ENUM,LNAS_FUNCTION_LABEL1,
                            pMmcActResult->ulMoDetachType);

    if(NAS_EMM_PUBU_BIT_SLCT == pMmcActResult->bitOpMoDetachType)
    {
        /* 处理IMSI DETACH类型 */
        if(MMC_LMM_MO_DET_CS_ONLY == pMmcActResult->ulMoDetachType)
        {
            NAS_EMM_PUBU_LOG_NORM("NAS_EMM_ProGuMoDetachRst:Cs Detach");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_ProGuMoDetachRst_ENUM,LNAS_FUNCTION_LABEL2);

            /*更新前注册域为:CS+PS,CS或PS:如果为CS+PS,更新为PS;如果为PS,保持不变,
            如果为CS,更新为NULL*/
            NAS_EMM_ProcPsDomainRetainCsDomainNull();

        }

        /* 处理EPS DETACH类型*/
        else if(MMC_LMM_MO_DET_PS_ONLY == pMmcActResult->ulMoDetachType)
        {
            NAS_EMM_PUBU_LOG_NORM("NAS_EMM_ProGuMoDetachRst:Ps Detach");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_ProGuMoDetachRst_ENUM,LNAS_FUNCTION_LABEL3);

            /*更新前注册域只能为:CS+PS或PS:如果为CS+PS,更新为CS;如果为PS,更新为NULL*/
            NAS_EMM_ProcCsDomainRetainPsDomainNull(EMM_SS_DEREG_NO_CELL_AVAILABLE);
        }
        /*IMSI/EPS DETACH类型 */
        else if(MMC_LMM_MO_DET_CS_PS == pMmcActResult->ulMoDetachType)
        {
            NAS_EMM_PUBU_LOG_NORM("NAS_EMM_ProGuMoDetachRst:CS+PS Detach");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_ProGuMoDetachRst_ENUM,LNAS_FUNCTION_LABEL4);

            /*进入EMM_SS_DEREG_NO_CELL_AVAILABLE的状态*/
            NAS_EMM_AdStateConvert(             EMM_MS_DEREG,
                                                EMM_SS_DEREG_NO_CELL_AVAILABLE,
                                                TI_NAS_EMM_STATE_NO_TIMER);
           /*更新前注册域只能为:CS+PS或PS:更新为NULL*/
        }
        /*其余情况打印*/
        else
        {
            /* 非法的MO DETACH类型，不处理 */
            NAS_EMM_PUBU_LOG_WARN("NAS_EMM_ProGuMoDetachRst:Illegal Mo Detach Type");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_ProGuMoDetachRst_ENUM,LNAS_FUNCTION_LABEL5);
        }
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_ProGuLocalDetachRst
 Description     : 挂起状态下，处理GU发来的LOCAL DETACH结果
 Input           : VOS_VOID
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010            2011-11-18   Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMM_ProGuLocalDetachRst( MsgBlock * pMsg )
{
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pMmcActResult = VOS_NULL_PTR;

    pMmcActResult = (MMC_LMM_ACTION_RESULT_REQ_STRU *)pMsg;


    NAS_EMM_PUBU_LOG1_NORM("NAS_EMM_ProGuLocalDetachRst: ulLocalDetachType = ",
                            pMmcActResult->ulLocalDetachType);
    TLPS_PRINT2LAYER_INFO(NAS_EMM_ProGuLocalDetachRst_ENUM,LNAS_FUNCTION_LABEL1);

    if(NAS_EMM_PUBU_BIT_SLCT == pMmcActResult->bitOpLocalDetachType)
    {
        /* 处理IMSI PGAING类型的本地DETACH */
        if(MMC_LMM_GU_LOCAL_DET_IMSI_PAGING == pMmcActResult->ulLocalDetachType)
        {
            NAS_EMM_PUBU_LOG_NORM("NAS_EMM_ProGuLocalDetachRst:Imsi Pgaing");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_ProGuLocalDetachRst_ENUM,LNAS_FUNCTION_LABEL2);

            /* 删除GUTI后会自动保存EPS_LOC,所以需要先设置STATUS */
            /*设置EU status为EU2*/
            NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_NOT_UPDATED_EU2);

            /*24.008删除GUTI, LVR TAI, TAI list and KSI,*/
            NAS_EMM_ClearRegInfo(NAS_EMM_NOT_DELETE_RPLMN);
             /*CS域保持不变,PS域去注册*/
            NAS_EMM_ProcCsDomainRetainPsDomainNull(EMM_SS_DEREG_NO_CELL_AVAILABLE);
        }
        /* 处理其他类型的本地DETACH */
        else if(MMC_LMM_GU_LOCAL_DET_OTHERS == pMmcActResult->ulLocalDetachType)
        {
            NAS_EMM_PUBU_LOG_NORM("NAS_EMM_ProGuLocalDetachRst:Others");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_ProGuLocalDetachRst_ENUM,LNAS_FUNCTION_LABEL3);

            /*进入DEREG.EMM_SS_DEREG_NO_CELL_AVAILABLE的状态*/
            NAS_EMM_PUBU_FSMTranState(          EMM_MS_DEREG,
                                                EMM_SS_DEREG_NO_CELL_AVAILABLE,
                                                TI_NAS_EMM_STATE_NO_TIMER);

            /*注册域暂不处理*/

        }
        /*其余情况打印*/
        else
        {
            /* 非法的LOCAL DETACH类型，不处理 */
            NAS_EMM_PUBU_LOG_WARN("NAS_EMM_ProGuLocalDetachRst:Illegal Local Detach Type");
            TLPS_PRINT2LAYER_WARNING(NAS_EMM_ProGuLocalDetachRst_ENUM,LNAS_FUNCTION_LABEL4);
        }
    }

    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_ProGuMtDetachRst
 Description     : 挂起状态下，处理GU发来的MT DETACH结果
 Input           : VOS_VOID
 Output          : None
 Return          : VOS_VOID

 History         :
    1.Zhangcaixia 00179470      2011-5-27   Draft Enact
    2.lihong00150010            2011-11-18  Modify

*****************************************************************************/
VOS_VOID NAS_EMM_ProGuMtDetachRst( MsgBlock * pMsg )
{
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pMmcActResult = VOS_NULL_PTR;

    pMmcActResult = (MMC_LMM_ACTION_RESULT_REQ_STRU *)pMsg;


    NAS_EMM_PUBU_LOG2_NORM("NAS_EMM_ProGuMtDetachRst: ulReqDomain = , ulMtDetachType = ",
                            pMmcActResult->ulReqDomain,
                            pMmcActResult->ulMtDetachType);
    TLPS_PRINT2LAYER_INFO2(NAS_EMM_ProGuLocalDetachRst_ENUM,LNAS_FUNCTION_LABEL1,
                            pMmcActResult->ulReqDomain,
                            pMmcActResult->ulMtDetachType);

    if(NAS_EMM_PUBU_BIT_SLCT == pMmcActResult->bitOpMtDetachType)
    {
        /*GU MT GPRS DETACH的类型3种，IMSI,RE_ATT_REQU,RE_ATT_NOT_REQU；结果域，
          请求域根据DETACH TYPE转换填充*/
        /*如果为IMSI detach时，既不处理 cause值，EMM也不需迁状态，EMM不需处理*/

        if(NAS_EMM_SUSPEND_GU_ACT_DOMAIN_YES == NAS_EMM_CheckGuMtDetachTypeImsi(pMsg))
        {
            NAS_EMM_ATTACH_LOG1_NORM("NAS_EMM_ProGuMtDetachRst: ulReqDomain = .",
                            pMmcActResult->ulReqDomain);
            TLPS_PRINT2LAYER_INFO1(NAS_EMM_ProGuLocalDetachRst_ENUM,LNAS_EMM_REG_DOMAIN,
                            pMmcActResult->ulReqDomain);

            /*CS域去注册,PS域保持不变*/
            NAS_EMM_ProcPsDomainRetainCsDomainNull();
        }

        /*如果为PS detach,re_attach_not_required则根据原因值处理*/
        else if(NAS_EMM_SUSPEND_GU_ACT_DOMAIN_YES == NAS_EMM_CheckGuMtDetachTypePsReAttNotRequ(pMsg))
        {
            NAS_EMM_ATTACH_LOG1_NORM("NAS_EMM_ProGuMtDetachRst: ucCnCause = .", pMmcActResult->ucCnCause);
            TLPS_PRINT2LAYER_INFO1(NAS_EMM_ProGuLocalDetachRst_ENUM,LNAS_CAUSE_NUMBER,
                            pMmcActResult->ucCnCause);
            NAS_EMM_ProGuMtDetachRstCauseValue(pMsg);
        }

        /*如果为PS detach,re_attach_required 迁状态*/
        else if(NAS_EMM_SUSPEND_GU_ACT_DOMAIN_YES == NAS_EMM_CheckGuMtDetachTypePsReAttRequ(pMsg))
        {
            NAS_EMM_PUBU_LOG2_NORM("NAS_EMM_ProGuMtDetachRst: ulReqDomain = , ulMtDetachType = ",
                            pMmcActResult->ulReqDomain,
                            pMmcActResult->ulMtDetachType);
            TLPS_PRINT2LAYER_INFO2(NAS_EMM_ProGuLocalDetachRst_ENUM,LNAS_FUNCTION_LABEL2,
                            pMmcActResult->ulReqDomain,
                            pMmcActResult->ulMtDetachType);

           /*CS域保持不变,PS域去注册*/
            NAS_EMM_ProcCsDomainRetainPsDomainNull(EMM_SS_DEREG_NO_CELL_AVAILABLE);
        }

        /*其余情况打印*/
        else
        {
            /*非法MT DETACH类型，丢弃不处理*/
            NAS_EMM_ATTACH_LOG1_NORM("NAS_EMM_ProGuMtDetachRst: ulReqDomain = .",
                            pMmcActResult->ulReqDomain);
            TLPS_PRINT2LAYER_INFO1(NAS_EMM_ProGuLocalDetachRst_ENUM,LNAS_FUNCTION_LABEL3,
                            pMmcActResult->ulReqDomain);
        }

    }

    return;
}
/*****************************************************************************
 Function Name   : NAS_EMM_ProGuLauRst
 Description     : 挂起状态下，处理GU发来的LAU结果
 Input           : pstMsg---------------------MMC_LMM_ACTION_RESULT_REQ消息指针
 Output          : None
 Return          : VOS_VOID

 History         :
    1.Zhangcaixia 00179470      2011-5-27  Draft Enact
    2.lihong 00150010      2011-09-26  Modify

*****************************************************************************/
VOS_VOID NAS_EMM_ProGuLauRst
(
    MsgBlock                           *pstMsg
)
{
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pMmcActResult   = VOS_NULL_PTR;

    pMmcActResult   = (MMC_LMM_ACTION_RESULT_REQ_STRU *)pstMsg;

    NAS_EMM_PUBU_LOG1_NORM("NAS_EMM_ProGuLauRst: ulActRst = ",
                            pMmcActResult->ulActRst);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_ProGuLauRst_ENUM,LNAS_ACT_RESULT,
                            pMmcActResult->ulActRst);

    /*如果不是被bar，都统一将标志置为happend*/
    if (MMC_LMM_RSLT_TYPE_ACCESS_BARRED != pMmcActResult->ulActRst)
    {
        /* 记录GU模曾经发起过LAU */
        NAS_LMM_SetEmmInfoLauOrComRauFlag(NAS_EMM_LAU_OR_COMBINED_RAU_HAPPENED);
    }


    /* 从GU到L的异系统变换，如果在GU曾经发起过LAU或者联合RAU成功，则需要发起TAU，
       TAU类型为combined TA/LA with IMSI attach */
    if (MMC_LMM_RSLT_TYPE_SUCCESS == pMmcActResult->ulActRst)
    {
        /*如果为NULL,更新为CS;如果为PS,更新为CS+PS,其他注册域保持不变*/
        if (NAS_LMM_REG_DOMAIN_NULL == NAS_LMM_GetEmmInfoRegDomain())
        {
            NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_CS);
        }
        else if (NAS_LMM_REG_DOMAIN_PS == NAS_LMM_GetEmmInfoRegDomain())
        {
            NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_CS_PS);
        }
        else
        {
            NAS_EMM_PUBU_LOG_NORM("NAS_EMM_ProGuLauRst:Reg domain is not change");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_ProGuLauRst_ENUM,LNAS_FUNCTION_LABEL1);
        }

        /* 记录GU模曾经发起过LAU成功 */
        NAS_LMM_SetEmmInfoLauOrComRauFlag(NAS_EMM_LAU_OR_COMBINED_RAU_HAPPENED);

        return ;
    }

    /* LAU被拒绝*/
    if ((MMC_LMM_RSLT_TYPE_CN_REJ == pMmcActResult->ulActRst)
        && (NAS_EMM_PUBU_BIT_SLCT == pMmcActResult->bitOpCnCause))
    {
        NAS_EMM_GuLauActionRej(pstMsg);
        return ;
    }

    /* LAU失败*/
    if (MMC_LMM_RSLT_TYPE_FAILURE == pMmcActResult->ulActRst)
    {
        NAS_EMM_ProcGuLauAttemptCounter(pstMsg);
        return;
    }
    /*LAU接入被bar*/
    if (MMC_LMM_RSLT_TYPE_ACCESS_BARRED == pMmcActResult->ulActRst)
    {
        /*不处理*/

    }
    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_ProGuCmRst
 Description     : 挂起状态下，处理GU发来的CM结果
 Input           : pstMsg---------------------MMC_LMM_ACTION_RESULT_REQ消息指针
 Output          : None
 Return          : VOS_VOID

 History         :
    1.leili 00132387      2012-6-6  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_ProGuCmRst
(
    MsgBlock                           *pstMsg
)
{
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pMmcActResult   = VOS_NULL_PTR;

    pMmcActResult   = (MMC_LMM_ACTION_RESULT_REQ_STRU *)pstMsg;

    NAS_EMM_PUBU_LOG1_NORM("NAS_EMM_ProGuLauRst: ulActRst = ",
                            pMmcActResult->ulActRst);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_ProGuCmRst_ENUM,LNAS_ACT_RESULT,
                            pMmcActResult->ulActRst);

    /*CN REJ*/
    if ((MMC_LMM_RSLT_TYPE_CN_REJ == pMmcActResult->ulActRst)
        && (NAS_EMM_BIT_SLCT == pMmcActResult->bitOpCnCause))
    {
        if (NAS_EMM_CAUSE_IMSI_UNKNOWN_IN_VLR == pMmcActResult->ucCnCause)
        {
            /*CS注册域更新为去注册,PS注册域不变*/
            NAS_EMM_ProcPsDomainRetainCsDomainNull();
            return;
        }

        if (NAS_EMM_CAUSE_ILLEGAL_ME == pMmcActResult->ucCnCause)
        {
            /* 如果CM被拒，原因值为6，则L模后续不能发起联合ATTACH和联合TAU */
            NAS_LMM_SetEmmInfoRejCause2Flag(NAS_EMM_REJ_YES);

            /*CS注册域更新为去注册,PS注册域不变*/
            NAS_EMM_ProcPsDomainRetainCsDomainNull();
            return;
        }
    }

    /*其他结果值不处理*/

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_ProGuAbortRst
 Description     : 挂起状态下，处理GU发来的Abort结果
 Input           : pstMsg---------------------MMC_LMM_ACTION_RESULT_REQ消息指针
 Output          : None
 Return          : VOS_VOID

 History         :
    1.leili 00132387      2012-6-6  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_ProGuAbortRst
(
    MsgBlock                           *pstMsg
)
{
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pMmcActResult   = VOS_NULL_PTR;

    pMmcActResult   = (MMC_LMM_ACTION_RESULT_REQ_STRU *)pstMsg;

    NAS_EMM_PUBU_LOG1_NORM("NAS_EMM_ProGuLauRst: ulActRst = ",
                            pMmcActResult->ulActRst);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_ProGuAbortRst_ENUM,LNAS_ACT_RESULT,
                            pMmcActResult->ulActRst);

    /*CN REJ*/
    if ((MMC_LMM_RSLT_TYPE_CN_REJ == pMmcActResult->ulActRst)
        && (NAS_EMM_BIT_SLCT == pMmcActResult->bitOpCnCause))
    {
        if (NAS_EMM_CAUSE_ILLEGAL_ME == pMmcActResult->ucCnCause)
        {
            /* 如果CM被拒，原因值为6，则L模后续不能发起联合ATTACH和联合TAU */
            NAS_LMM_SetEmmInfoRejCause2Flag(NAS_EMM_REJ_YES);

            /*CS注册域更新为去注册,PS注册域不变*/
            NAS_EMM_ProcPsDomainRetainCsDomainNull();
            return;
        }
    }

    /*其他结果值不处理*/

    return;
}



/*****************************************************************************
 Function Name   : NAS_EMM_ProGuServiceRst
 Description     : 挂起状态下，处理GU发来的SERVICE结果
 Input           : VOS_VOID
 Output          : None
 Return          : VOS_VOID

 History         :
    1.Zhangcaixia 00179470      2011-5-27  Draft Enact
    2.sunjitan 00193151        2012-05-31  Modify     #25原因值也按照other处理
*****************************************************************************/
VOS_VOID NAS_EMM_ProGuServiceRst( MsgBlock * pMsg )
{
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pMmcActResult = VOS_NULL_PTR;

    pMmcActResult = (MMC_LMM_ACTION_RESULT_REQ_STRU *)pMsg;


    NAS_EMM_ATTACH_LOG1_NORM("NAS_EMM_ProGuServiceRst: ulActRst = ",
                            pMmcActResult->ulActRst);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_ProGuServiceRst_ENUM,LNAS_ACT_RESULT,
                            pMmcActResult->ulActRst);

    /*Service只需处理CN REJ的情况*/
    /* GU的Service REQ有PS ONLY和CS only两种情况，只处理PS only */
    /*结果为CN_REJ时，GU一定携带CN CAUSE,不再对bitOpCnCause容错*/
    if((MMC_LMM_RSLT_TYPE_CN_REJ == pMmcActResult->ulActRst)
     &&(NAS_EMM_PUBU_BIT_SLCT == pMmcActResult->bitOpCnCause)
     &&(NAS_EMM_SUSPEND_GU_ACT_DOMAIN_YES == NAS_EMM_CheckGuActReqDomainPsRstDomainPs(pMsg)))
    {

        switch(pMmcActResult->ucCnCause)
        {
            /*#3,6走#3原因值处理*/
            case NAS_LMM_CAUSE_ILLEGAL_UE:
            case NAS_LMM_CAUSE_ILLEGAL_ME:

                NAS_EMM_ProcGuDettRejCause3();
                break;
            case NAS_LMM_CAUSE_EPS_SERV_NOT_ALLOW:
                NAS_EMM_ProcGuDettRejCause7();
                break;
            case NAS_LMM_CAUSE_EPS_SERV_AND_NON_EPS_SERV_NOT_ALLOW:
                if (NAS_RELEASE_R11)
                {
                    NAS_EMM_ProcGuDettRejCause3();
                }
                else
                {
                    NAS_EMM_PUBU_LOG2_NORM("NAS_EMM_ProGuDetachRst: ucCnCause = , ulAttemptCount = ",
                            pMmcActResult->ucCnCause,
                            pMmcActResult->ulAttemptCount);
                    TLPS_PRINT2LAYER_INFO1(NAS_EMM_ProGuServiceRst_ENUM,LNAS_CAUSE_NUMBER,
                            pMmcActResult->ucCnCause);
                    TLPS_PRINT2LAYER_INFO1(NAS_EMM_ProGuServiceRst_ENUM,LNAS_EMM_ATTEMPT_COUNTER,
                                pMmcActResult->ulAttemptCount);
                }
                break;
            /*#9的处理*/
            case NAS_LMM_CAUSE_UE_ID_NOT_DERIVED:
                NAS_EMM_ProcGuRauSerRejCause9();
                break;

            /*#10的处理*/
            case NAS_LMM_CAUSE_IMPLICIT_DETACHED:

                 /*保持CS域保持不变,PS域去注册*/
                NAS_EMM_ProcCsDomainRetainPsDomainNull(EMM_SS_DEREG_NO_CELL_AVAILABLE);
                break;

            /*#11,12的处理*/
            case NAS_LMM_CAUSE_PLMN_NOT_ALLOW:
            case NAS_LMM_CAUSE_TA_NOT_ALLOW:
                NAS_EMM_ProcGuRauSerRejCause11();
                break;

            /* #25原因值按照other处理 */
            /*#13,15,25*/
            case NAS_LMM_CAUSE_ROAM_NOT_ALLOW:
            case NAS_LMM_CAUSE_NO_SUITABL_CELL:
                NAS_EMM_ProcGuRauSerRejCause13();
                break;

            /*other cause，GU abort service*/
            default    :
                NAS_EMM_PUBU_LOG2_NORM("NAS_EMM_ProGuDetachRst: ucCnCause = , ulAttemptCount = ",
                            pMmcActResult->ucCnCause,
                            pMmcActResult->ulAttemptCount);
                TLPS_PRINT2LAYER_INFO1(NAS_EMM_ProGuServiceRst_ENUM,LNAS_CAUSE_NUMBER,
                            pMmcActResult->ucCnCause);
                TLPS_PRINT2LAYER_INFO1(NAS_EMM_ProGuServiceRst_ENUM,LNAS_EMM_ATTEMPT_COUNTER,
                            pMmcActResult->ulAttemptCount);
                break;
        }
    }

    return;
}
/*****************************************************************************
 Function Name   : NAS_EMM_GuActionClearRegInfo
 Description     : GU ACTION导致的删L的GUTI,LVR TAI,KSI
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.Zhangcaixia 00179470      2011-5-27  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_GuActionClearRegInfo( VOS_UINT32 ulDeleteRplmn )
{
    /*删除GUTI*/
    NAS_EMM_ClearGuti();

    /*删除LVR TAI*/

    if (NAS_EMM_DELETE_RPLMN == ulDeleteRplmn)
    {
        NAS_EMM_ClearLVRTai();
    }
    else
    {
        NAS_EMM_SetLVRTacInvalid();
    }

    /*删除KSI*/
    /*NAS_EMM_ClearCurSecuCntxt();*/
    NAS_EMM_ClearAllSecuCntxt();

    /*保存PS LOC信息*/
    NAS_LMM_WritePsLoc(NAS_NV_ITEM_UPDATE);
}

/*****************************************************************************
 Function Name   : NAS_EMM_ProcGuRejCause3
 Description     : GU拒绝原因为3的处理过程
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.Zhangcaixia 00179470      2011-5-27  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_ProcGuAttRejCause3( VOS_VOID )
{
    NAS_LMM_SetPsSimValidity(NAS_LMM_SIM_INVALID);

    /*进入DEREG.EMM_SS_DEREG_NO_IMSI的状态*/
    NAS_EMM_PUBU_FSMTranState(          EMM_MS_DEREG,
                                        EMM_SS_DEREG_NO_IMSI,
                                        TI_NAS_EMM_STATE_NO_TIMER);

    /*设置EU status为EU3*/
    NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_ROAMING_NOT_ALLOWED_EU3);

    /*24.008删除GUTI, LVR TAI, TAI list and KSI,
      24301删除GUTI, LVR TAI and KSI*/
    NAS_EMM_GuActionClearRegInfo(NAS_EMM_DELETE_RPLMN);

    NAS_LMM_SetPsSimValidity(NAS_LMM_SIM_INVALID);

    /*向LRRC发送LRRC_LMM_NAS_INFO_CHANGE_REQ携带USIM卡状态*/
    NAS_EMM_SendUsimStatusToRrc(LRRC_LNAS_USIM_PRESENT_INVALID);

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_ProcGuRejCause7
 Description     : GU拒绝原因为7的处理过程
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.leili 00132387      2011-6-5  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_ProcGuAttRejCause7( VOS_VOID )
{
    NAS_LMM_SetPsSimValidity(NAS_LMM_SIM_INVALID);

    /*设置EU status为EU3*/
    NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_ROAMING_NOT_ALLOWED_EU3);

    /*24.008删除GUTI, LVR TAI, TAI list and KSI,
      24301删除GUTI, LVR TAI and KSI*/
    NAS_EMM_GuActionClearRegInfo(NAS_EMM_DELETE_RPLMN);

    NAS_LMM_SetPsSimValidity(NAS_LMM_SIM_INVALID);

    /*向LRRC发送LRRC_LMM_NAS_INFO_CHANGE_REQ携带USIM卡状态*/
    NAS_EMM_SendUsimStatusToRrc(LRRC_LNAS_USIM_PRESENT_INVALID);

    /*更新前注册域状态为CS或NULL:注册域保持不变*/
    NAS_EMM_ProcCsDomainRetainPsDomainNull(EMM_SS_DEREG_NO_IMSI);

    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_ProcGuRejCause3
 Description     : GU DETACH 拒绝原因为3的处理过程
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.Zhangcaixia 00179470      2011-5-27  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_ProcGuDettRejCause3( VOS_VOID )
{
    NAS_LMM_SetPsSimValidity(NAS_LMM_SIM_INVALID);

    /*进入DEREG.EMM_SS_DEREG_NO_IMSI的状态*/
    NAS_EMM_PUBU_FSMTranState(          EMM_MS_DEREG,
                                        EMM_SS_DEREG_NO_IMSI,
                                        TI_NAS_EMM_STATE_NO_TIMER);

    /* 删除GUTI后会自动保存EPS_LOC,所以需要先设置STATUS */
    /*设置EU status为EU3*/
    NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_ROAMING_NOT_ALLOWED_EU3);

    /*24.008删除GUTI, LVR TAI, TAI list and KSI,*/
    NAS_EMM_ClearRegInfo(NAS_EMM_DELETE_RPLMN);

    NAS_LMM_SetPsSimValidity(NAS_LMM_SIM_INVALID);

    /*向LRRC发送LRRC_LMM_NAS_INFO_CHANGE_REQ携带USIM卡状态*/
    NAS_EMM_SendUsimStatusToRrc(LRRC_LNAS_USIM_PRESENT_INVALID);

    /*更新前注册域只能为:CS+PS或PS:根据协议更新注册域为NULL*/

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_ProcGuRejCause7
 Description     : GU DETACH 拒绝原因为7的处理过程
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.leili 00132387      2012-6-6  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_ProcGuDettRejCause7( VOS_VOID )
{
    NAS_LMM_SetPsSimValidity(NAS_LMM_SIM_INVALID);

    /* 删除GUTI后会自动保存EPS_LOC,所以需要先设置STATUS */
    /*设置EU status为EU3*/
    NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_ROAMING_NOT_ALLOWED_EU3);

    /*24.008删除GUTI, LVR TAI, TAI list and KSI,*/
    NAS_EMM_ClearRegInfo(NAS_EMM_DELETE_RPLMN);

    NAS_LMM_SetPsSimValidity(NAS_LMM_SIM_INVALID);

    /*向LRRC发送LRRC_LMM_NAS_INFO_CHANGE_REQ携带USIM卡状态*/
    NAS_EMM_SendUsimStatusToRrc(LRRC_LNAS_USIM_PRESENT_INVALID);

    /*保持CS域保持不变,PS域去注册*/
    NAS_EMM_ProcCsDomainRetainPsDomainNull(EMM_SS_DEREG_NO_IMSI);

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_ProcGuDettachRejCause11
 Description     : GU Attach拒绝原因为11的处理过程
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.Zhangcaixia 00179470      2011-5-27  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_ProcGuDettachRejCause11( VOS_VOID )
{
    /*进入EMM_SS_DEREG_NO_CELL_AVAILABLE的状态*/
    NAS_EMM_AdStateConvert(             EMM_MS_DEREG,
                                        EMM_SS_DEREG_NO_CELL_AVAILABLE,
                                        TI_NAS_EMM_STATE_NO_TIMER);

    /* 删除GUTI后会自动保存EPS_LOC,所以需要先设置STATUS */
    /*设置EU status为EU3*/
    NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_ROAMING_NOT_ALLOWED_EU3);

    /*24.008删除GUTI, LVR TAI, TAI list and KSI,
      24301删除GUTI, LVR TAI TAI list and KSI*/
    NAS_EMM_ClearRegInfo(NAS_EMM_NOT_DELETE_RPLMN);

    /*清除Attach Attempt Counter*/
    NAS_EMM_AttResetAttAttempCounter();

    /*更新前注册域只能为:CS+PS或PS:根据协议更新注册域为NULL*/

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_ProcGuDettachRejCause14
 Description     : GU Attach拒绝原因为14的处理过程
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.leili 00132387      2012-6-6  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_ProcGuDettachRejCause14( VOS_VOID )
{
    /* 删除GUTI后会自动保存EPS_LOC,所以需要先设置STATUS */
    /*设置EU status为EU3*/
    NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_ROAMING_NOT_ALLOWED_EU3);

    /*24.008删除GUTI, LVR TAI, TAI list and KSI,
      24301删除GUTI, LVR TAI TAI list and KSI*/
    NAS_EMM_ClearRegInfo(NAS_EMM_DELETE_RPLMN);

    /*清除Attach Attempt Counter*/
    NAS_EMM_AttResetAttAttempCounter();

    /*保持CS域保持不变,PS域去注册*/
    NAS_EMM_ProcCsDomainRetainPsDomainNull(EMM_SS_DEREG_NO_CELL_AVAILABLE);

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_ProcGuAttachRejCause11
 Description     : GU Attach拒绝原因为11的处理过程
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.Zhangcaixia 00179470      2011-5-27  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_ProcGuAttachRejCause11( VOS_VOID )
{
    /*进入EMM_SS_DEREG_NO_CELL_AVAILABLE的状态*/
    NAS_EMM_AdStateConvert(             EMM_MS_DEREG,
                                        EMM_SS_DEREG_NO_CELL_AVAILABLE,
                                        TI_NAS_EMM_STATE_NO_TIMER);

    /* 删除GUTI后会自动保存EPS_LOC,所以需要先设置STATUS */
    /*设置EU status为EU3*/
    NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_ROAMING_NOT_ALLOWED_EU3);

    /*24.008删除GUTI, LVR TAI, TAI list and KSI,
      24301删除GUTI, LVR TAI and KSI*/
    NAS_EMM_GuActionClearRegInfo(NAS_EMM_NOT_DELETE_RPLMN);

    /*清除Attach Attempt Counter*/
    NAS_EMM_AttResetAttAttempCounter();

    /*不管更新前注册域状态,根据协议注册域需要更新为NULL*/
    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_ProcGuAttachRejCause14
 Description     : GU Attach拒绝原因为14的处理过程
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.leili 00132387      2012-6-5  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_ProcGuAttachRejCause14( VOS_VOID )
{
    /* 删除GUTI后会自动保存EPS_LOC,所以需要先设置STATUS */
    /*设置EU status为EU3*/
    NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_ROAMING_NOT_ALLOWED_EU3);

    /*24.008删除GUTI, LVR TAI, TAI list and KSI,
      24301删除GUTI, LVR TAI and KSI*/
    NAS_EMM_GuActionClearRegInfo(NAS_EMM_NOT_DELETE_RPLMN);

    /*清除Attach Attempt Counter*/
    NAS_EMM_AttResetAttAttempCounter();

    /*更新前注册域状态为CS或NULL:注册域保持不变*/
    NAS_EMM_ProcCsDomainRetainPsDomainNull(EMM_SS_DEREG_NO_CELL_AVAILABLE);

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_ProcGuAttachAttemptCounterEq5
 Description     : GU AttachAttachAttemptCounter为5的处理过程
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.Zhangcaixia 00179470      2011-5-27  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_ProcGuAttachAttemptCounterEq5( MsgBlock * pMsg )
{
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pMmcActResult = VOS_NULL_PTR;

    pMmcActResult = (MMC_LMM_ACTION_RESULT_REQ_STRU *)pMsg;

    if((NAS_EMM_BIT_SLCT == pMmcActResult->bitOpAtmpCnt)
     &&(5 <= pMmcActResult->ulAttemptCount))
    {
        if (NAS_EMM_SUSPEND_GU_ACT_DOMAIN_YES == NAS_EMM_CheckGuActReqDomainPsRstDomainPs(pMsg))
        {
            /*保持CS注册域不变,PS去注册*/
            NAS_EMM_ProcCsDomainRetainPsDomainNull(EMM_SS_DEREG_NO_CELL_AVAILABLE);
        }
        else
        {
            /*进入EMM_SS_DEREG_NO_CELL_AVAILABLE的状态,注册域为NULL*/
            NAS_EMM_PUBU_FSMTranState(          EMM_MS_DEREG,
                                                EMM_SS_DEREG_NO_CELL_AVAILABLE,
                                                TI_NAS_EMM_STATE_NO_TIMER);

            /*更新前注册域状态为CS或NULL:根据协议更新注册域为NULL*/
        }
        /* 删除GUTI后会自动保存EPS_LOC,所以需要先设置STATUS */
        /*设置EU status为EU2*/
        NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_NOT_UPDATED_EU2);

        /*24.008GUTI, LVR TAI, TAI list and KSI*/
        NAS_EMM_ClearRegInfo(NAS_EMM_NOT_DELETE_RPLMN);
    }

    /*AttachAttempCounter<5时，不处理，只打印*/
    else
    {
        NAS_EMM_PUBU_LOG2_NORM("NAS_EMM_ProcGuAttachAttemptCounterEq5: ucCnCause = , ulAttemptCount = ",
                            pMmcActResult->ucCnCause,
                            pMmcActResult->ulAttemptCount);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_ProcGuAttachAttemptCounterEq5_ENUM,LNAS_CAUSE_NUMBER,
                            pMmcActResult->ucCnCause);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_ProcGuAttachAttemptCounterEq5_ENUM,LNAS_EMM_ATTEMPT_COUNTER,
                            pMmcActResult->ulAttemptCount);

        /*更新前注册域状态为CS或NULL:根据协议,请求域和结果域都为PS_IMSI时,
        LAI变更或MM状态不为U1,更新注册域为NULL;其他场景,CS domain保持不变,PS域去注册;*/
        if((NAS_EMM_SUSPEND_GU_ACT_DOMAIN_YES == NAS_EMM_CheckGuActReqDomainCmbRstDomainCmb(pMsg))
            && (NAS_EMM_SUCC == NAS_EMM_CheckMmUpStateAndLaiChange(pMsg)))
        {
            NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_NULL);
        }
    }
    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_ProcGuRauRejCause9
 Description     : GU RAU rej cause为9的处理过程
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.Zhangcaixia 00179470      2011-5-27  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_ProcGuRauSerRejCause9( VOS_VOID )
{
    /* 删除GUTI后会自动保存EPS_LOC,所以需要先设置STATUS */
    /*设置EU status为EU2*/
    NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_NOT_UPDATED_EU2);

    /*删除GUTI, LVR TAI, TAI list and KSI*/
    NAS_EMM_ClearRegInfo(NAS_EMM_NOT_DELETE_RPLMN);
     /*保持CS域保持不变,PS域去注册*/
    NAS_EMM_ProcCsDomainRetainPsDomainNull(EMM_SS_DEREG_NO_CELL_AVAILABLE);

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_ProcGuRauRejCause11
 Description     : GU RAU rej cause为11的处理过程
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.Zhangcaixia 00179470      2011-5-27  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_ProcGuRauSerRejCause11( VOS_VOID )
{
    /*进入EMM_SS_DEREG_NO_CELL_AVAILABLE的状态*/
    NAS_EMM_PUBU_FSMTranState(          EMM_MS_DEREG,
                                        EMM_SS_DEREG_NO_CELL_AVAILABLE,
                                        TI_NAS_EMM_STATE_NO_TIMER);

    /* 删除GUTI后会自动保存EPS_LOC,所以需要先设置STATUS */
    /*设置EU status为EU3*/
    NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_ROAMING_NOT_ALLOWED_EU3);

    /*删除GUTI, LVR TAI, TAI list and KSI*/
    NAS_EMM_ClearRegInfo(NAS_EMM_NOT_DELETE_RPLMN);

    /*更新前注册域只能为:CS+PS或PS:根据协议更新注册域为NULL*/

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_ProcGuRauRejCause14
 Description     : GU RAU rej cause为14的处理过程
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.leili 00132387      2012-6-6  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_ProcGuRauSerRejCause14( VOS_VOID )
{
    /* 删除GUTI后会自动保存EPS_LOC,所以需要先设置STATUS */
    /*设置EU status为EU3*/
    NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_ROAMING_NOT_ALLOWED_EU3);

    /*删除GUTI, LVR TAI, TAI list and KSI*/
    NAS_EMM_ClearRegInfo(NAS_EMM_NOT_DELETE_RPLMN);

    /*保持CS域保持不变,PS域去注册*/
    NAS_EMM_ProcCsDomainRetainPsDomainNull(EMM_SS_DEREG_NO_CELL_AVAILABLE);

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_ProcGuRauRejCause13
 Description     : GU RAU rej cause为11的处理过程
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.Zhangcaixia 00179470      2011-5-27  Draft Enact
    2.lihong 00150010           2012-12-18 Modify:Emergency

*****************************************************************************/
VOS_VOID  NAS_EMM_ProcGuRauSerRejCause13( VOS_VOID )
{
    /*进入EMM_SS_DEREG_NO_CELL_AVAILABLE的状态*/
    NAS_EMM_PUBU_FSMTranState(          EMM_MS_REG,
                                        EMM_SS_REG_NO_CELL_AVAILABLE,
                                        TI_NAS_EMM_STATE_NO_TIMER);

    /*设置EU status为EU3*/
    NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_ROAMING_NOT_ALLOWED_EU3);

    if (NAS_LMM_REG_STATUS_EMC_REGED != NAS_LMM_GetEmmInfoRegStatus())
    {
        /*保存PS LOC信息*/
        NAS_LMM_WritePsLoc(NAS_NV_ITEM_UPDATE);
    }

    /*更新前注册域只能为:CS+PS或PS:如果注册域为CS+PS,更新为PS;如果注册域为PS,保持不变*/
    NAS_EMM_ProcPsDomainRetainCsDomainNull();

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_ProcGuLauRejOther
 Description     : GU LAU rej cause为其他的处理过程
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.leili 00132387      2012-6-6  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_ProcGuLauAttemptCounter(MsgBlock * pMsg  )
{
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pMmcActResult = VOS_NULL_PTR;

    pMmcActResult = (MMC_LMM_ACTION_RESULT_REQ_STRU *)pMsg;

    if(((NAS_EMM_BIT_SLCT == pMmcActResult->bitOpAtmpCnt)
        &&(4 <= pMmcActResult->ulAttemptCount))
       || ((NAS_EMM_BIT_SLCT == pMmcActResult->bitOpLaiChangFlg)
        &&(VOS_TRUE == pMmcActResult->ucLaiChangFlg))
       || ((NAS_EMM_BIT_SLCT == pMmcActResult->bitOpCsUpdateStatus)
        &&(MMC_LMM_CS_UPDATE_STATUS_UPDATED != pMmcActResult->ucCsUpdateStatus)))
    {
        /*CS注册域更新为去注册,PS注册域不变*/
        NAS_EMM_ProcPsDomainRetainCsDomainNull();
    }
    return;
}



/*****************************************************************************
 Function Name   : NAS_LMM_ProcRrcSysCfgCnfBandNotSupport
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.    zhangcaixia  00179470      2011-09-10  Draft Enact
    2.    lifuxin      00253982      2014-10-31  建链流程重构
*****************************************************************************/
VOS_VOID  NAS_LMM_ProcRrcSysCfgCnfBandNotSupport( VOS_VOID )
{
    NAS_LMM_EstingOrReleasingProcessTimerHandle();

    switch(NAS_EMM_CUR_MAIN_STAT)
    {
        case    EMM_MS_AUTH_INIT:

            NAS_LMM_IfEmmHasBeenPushedThenPop();
            break;

        default:
            NAS_EMM_PUBU_LOG_INFO(" NAS_LMM_ProcRrcSysCfgCnfBandNotSupport");
            TLPS_PRINT2LAYER_INFO(NAS_LMM_ProcRrcSysCfgCnfBandNotSupport_ENUM,LNAS_FUNCTION_LABEL1);
            break;
    }

    /* 记录挂起前的状态*/
    NAS_LMM_MEM_CPY_S(  NAS_EMM_GetStateBeforeSuspendAddr(),
                        sizeof(NAS_LMM_FSM_STATE_STRU),
                        NAS_LMM_GetCurFsmAddr(NAS_LMM_PARALLEL_FSM_EMM),
                        sizeof(NAS_LMM_FSM_STATE_STRU));

    /*向ESM ERABM发挂起消息 */
    NAS_EMM_SendEsmSuspendInd();

    /* 发送 ERABM 挂起消息 */
    NAS_EMM_SendErabmSuspendInd();

    /* EMM状态迁移, 并启动定时器*/
    NAS_EMM_PUBU_FSMTranState(  EMM_MS_SUSPEND,
                                EMM_SS_SUSPEND_SYSCFGORI_WAIT_OTHER_SUSPEND,
                                TI_NAS_EMM_SYSCFGORI_WAIT_OTHER_SUSPEND_RSP_TIMER);

    /* 当前的 LTE为挂起态 */
    NAS_EMM_GetCurLteState() = NAS_LMM_CUR_LTE_SUSPEND;

    return;
}

/*****************************************************************************
 Function Name   : NAS_LMM_ProcRrcSysCfgCnfLteNotActive
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.    zhangcaixia  00179470      2011-09-10  Draft Enact
    2.    lifuxin      00253982      2014-10-31  建链流程重构
*****************************************************************************/
VOS_VOID  NAS_LMM_ProcRrcSysCfgCnfLteNotActive( VOS_VOID )
{

    NAS_LMM_EstingOrReleasingProcessTimerHandle();

    switch(NAS_EMM_CUR_MAIN_STAT)
    {
        case    EMM_MS_AUTH_INIT:

            NAS_LMM_IfEmmHasBeenPushedThenPop();
            break;

        default:
            break;
    }

    /* 记录挂起前的状态*/
    NAS_LMM_MEM_CPY_S(  NAS_EMM_GetStateBeforeSuspendAddr(),
                        sizeof(NAS_LMM_FSM_STATE_STRU),
                        NAS_LMM_GetCurFsmAddr(NAS_LMM_PARALLEL_FSM_EMM),
                        sizeof(NAS_LMM_FSM_STATE_STRU));

    /*向ESM ERABM发挂起消息 */
    NAS_EMM_SendEsmSuspendInd();

    /* 发送 ERABM 挂起消息 */
    NAS_EMM_SendErabmSuspendInd();

    /* EMM状态迁移, 并启动定时器*/
    NAS_EMM_PUBU_FSMTranState(  EMM_MS_SUSPEND,
                                EMM_SS_SUSPEND_SYSCFGORI_WAIT_OTHER_SUSPEND,
                                TI_NAS_EMM_SYSCFGORI_WAIT_OTHER_SUSPEND_RSP_TIMER);

    /* 当前的 LTE为去SUSPEND态 */
    NAS_EMM_GetCurLteState() = NAS_LMM_CUR_LTE_SUSPEND;

    return;
}


/*****************************************************************************
 Function Name   : NAS_LMM_ProcRrcSysCfgCnfNotSuspend
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.    zhangcaixia  00179470      2011-09-10  Draft Enact
    2.    sunjitan 00193151          2012-01-17  Modify for UE radio capbility
    3.    lifuxin  00253982          2014-10-31  建链流程重构
*****************************************************************************/
VOS_UINT32  NAS_LMM_ProcRrcSysCfgCnfNotSuspend(VOS_VOID)
{
    VOS_UINT32                          ulCurEmmStat;
    VOS_UINT32                          ulRslt = NAS_LMM_MSG_DISCARD;

    /* 打印进入函数 */
    NAS_EMM_PUBU_LOG_INFO("NAS_LMM_ProcRrcSysCfgCnfNotSuspend is entered !");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_ProcRrcSysCfgCnfNotSuspend_ENUM,LNAS_ENTRY);

    /* L处于主模 */
    if (NAS_LMM_CUR_LTE_ACTIVE == NAS_EMM_GetCurLteState())
    {
        NAS_EMM_PUBU_LOG_NORM("NAS_LMM_ProcRrcSysCfgCnfNotSuspend:  CUR_LTE_ACTIVE.");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_ProcRrcSysCfgCnfNotSuspend_ENUM,LNAS_FUNCTION_LABEL1);

        if(NAS_EMM_CONN_ESTING == NAS_EMM_GetConnState())
        {
            /* 停止 定时器*/
            NAS_LMM_StopStateTimer(TI_NAS_EMM_MRRC_WAIT_RRC_CONN_CNF);
        }

        /* 获取EMM当前状态 */
        ulCurEmmStat = NAS_LMM_PUB_COMP_EMMSTATE(NAS_EMM_CUR_MAIN_STAT,
                                          NAS_EMM_CUR_SUB_STAT);


        /* 根据不同的状态进行不同处理，仅需记录UE无线能力变化
               而当前无需特殊处理的状态不在此列 */
        switch(ulCurEmmStat)
        {
            /* EMM_MS_REG_INIT的所有子状态一起处理 */
            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG_INIT, EMM_SS_ATTACH_WAIT_CN_ATTACH_CNF):
            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG_INIT, EMM_SS_ATTACH_WAIT_ESM_BEARER_CNF):
            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG_INIT, EMM_SS_ATTACH_WAIT_RRC_DATA_CNF):

                    /* 给MMC回复结果 */
                    (VOS_VOID)NAS_LMM_SendMmcSysCfgCnf(MMC_LMM_SUCC);

                    /* 终止ATTACH流程，重新ATTACH */
                    ulRslt = NAS_EMM_MsRegInitRcvLrrcSyscfgCnfProc();
                    break;

            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_NORMAL_SERVICE):
            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM):

                    /* 给MMC回复结果 */
                    (VOS_VOID)NAS_LMM_SendMmcSysCfgCnf(MMC_LMM_SUCC);

                    /* 如GU变化直接发起TAU，如L变化本地DETACH后重新ATTACH */
                    ulRslt = NAS_EMM_MsRegSsAnyStateRcvLrrcSyscfgCnfCommProc();
                    break;

            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_WAIT_ACCESS_GRANT_IND):

                    /* 给MMC回复结果 */
                    (VOS_VOID)NAS_LMM_SendMmcSysCfgCnf(MMC_LMM_SUCC);

                    /* 如GU变化且未被BAR，发起TAU；如L变化且未被BAR，本地DETACH后重新ATTACH，
                       如被BAR, 保持状态不变 */
                    ulRslt = NAS_EMM_MsRegSsWaitAccGrantIndRcvLrrcSyscfgCnfProc();
                    break;

            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_IMSI_DETACH_WATI_CN_DETACH_CNF):
            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_AUTH_INIT, EMM_SS_AUTH_WAIT_CN_AUTH):

                    /* 能力发生变化则低优先级缓存，若未变化则无特殊处理直接回复MMC */
                    if(NAS_LMM_UE_RADIO_CAP_NOT_CHG != NAS_LMM_GetEmmInfoUeRadioCapChgFlag())
                    {
                        ulRslt = NAS_LMM_STORE_LOW_PRIO_MSG;
                    }
                    else
                    {
                        ulRslt = NAS_LMM_MSG_HANDLED;
                        (VOS_VOID)NAS_LMM_SendMmcSysCfgCnf(MMC_LMM_SUCC);
                    }
                    break;

            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_TAU_INIT, EMM_SS_TAU_WAIT_CN_TAU_CNF):
            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_SER_INIT, EMM_SS_SER_WAIT_CN_SER_CNF):

                    /* 给MMC回复结果 */
                    (VOS_VOID)NAS_LMM_SendMmcSysCfgCnf(MMC_LMM_SUCC);

                    /* 终止TAU或SER, 直接释放, 转入REG.PLMN_SEARCH等系统消息 */
                    ulRslt = NAS_EMM_MsTauSerRcvLrrcSyscfgCnfProc();
                    break;
            default:

                    /* 其它情况认为已处理*/
                    /* 给MMC回复结果 */
                    (VOS_VOID)NAS_LMM_SendMmcSysCfgCnf(MMC_LMM_SUCC);
                    ulRslt = NAS_LMM_MSG_HANDLED;
                    break;
        }
    }
    else
    {
        /* L处于从模则无特殊处理 */
        /* 给MMC回复结果 */
        (VOS_VOID)NAS_LMM_SendMmcSysCfgCnf(MMC_LMM_SUCC);
        ulRslt = NAS_LMM_MSG_HANDLED;
    }

    return ulRslt;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsSuspendSsSysCfgOriWaitOtherMsgSusRsp
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhangcaixia 179470      2011-9-10  Draft Enact
    2.sunjitan 00193151   2012-05-24 增加清除Resume触发和类型记录信息

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsSuspendSsSysCfgOriWaitOtherMsgSusRsp(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru  )
{
    MMC_LMM_RESULT_ID_ENUM_UINT32       ulSysCfgRst = MMC_LMM_SUCC;
    VOS_UINT32                          ulSendResult;

    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;

    NAS_EMM_GetUplayerCount()++;

    /* 若等于 2，意味着 ESM和ERABM挂起结束 */
    if(NAS_EMM_SUSPEND_UPLAYER_NUM_CM == NAS_EMM_GetUplayerCount())
    {
        /* 通知RRC挂起 */
        NAS_EMM_SendLrrcSuspendReq();
    }

    /* 若等于 3，意味着 RRC的响应，意味着挂起通知完成  */
    if(NAS_EMM_SUSPEND_UPLAYER_NUM_ALL <= NAS_EMM_GetUplayerCount())
    {
        /*syscfg引起的SUSPEND，如果当前存在连接，RRC会先上ID_LRRC_LMM_REL_IND，再上SUSPEND响应 */
        /* 停止定时器 */
        NAS_LMM_StopStateTimer(TI_NAS_EMM_SYSCFGORI_WAIT_OTHER_SUSPEND_RSP_TIMER);

        /* 清除此次挂起的上层响应记录，恢复过程将使用 */
        NAS_EMM_GetUplayerCount() = NAS_EMM_SUSPEND_UPLAYER_NUM_INITVALUE;

        /*加清理资源*/
        /* 清空各流程全局变量。同时，除了T3412和T3423，停止其他协议状态定时器, */
        NAS_EMM_SuspendInitRelResource();

        /* 挂起成功，之前的GU到L的异系统变换触发和类型记录信息可以清除 */
        NAS_EMM_ClearResumeInfo();

        /*不停止T3412*/

        NAS_LMM_SetEmmInfoTriggerTauSysChange(NAS_EMM_NO);

        /* del by y00307272 for DTS2015122301277 ,2015-12-26，Begin */
        /* DEL CAUSE:csfb到G下，挂起ps并通知LNAS，随后电话挂断后FR失败，回退到G下丢网，搜L
         失败，搜W失败(搜时MMC会给LNAS发挂起，我们这是会设置ps not suspension)，在搜到L判断
         PS没有挂起，不发TAU，被叫失败 */
        /*NAS_LMM_SetEmmInfoPsState(GMM_LMM_GPRS_NOT_SUSPENSION);*/
        /* del by y00307272 for DTS2015122301277 ,2015-12-26，End */
        /* 挂起结束，改状态 */
        NAS_EMM_SuspendEndStateChng();

        /* 向MMC回复SYS CFG结果*/
        ulSendResult = NAS_LMM_SendMmcSysCfgCnf(ulSysCfgRst);

        if (NAS_EMM_SEND_RRC_OK != ulSendResult)
        {
            /* 打印函数，ERROR_LEVEL */
            NAS_LMM_PUBM_LOG1_INFO("NAS_LMM_SendMmcSysCfgCnf : Send Msg Failure!!! ulSendResult=",
                                     ulSendResult);
            TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsSuspendSsSysCfgOriWaitOtherMsgSusRsp_ENUM,LNAS_SND_RST,
                                     ulSendResult);
        }
    }

    return  NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsSuspendSsSyscfgWaitOtherMsgTimerExp
 Description     : 等待 ESM,ERABM 的挂起响应超时
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhangcaixia 179470      2011-9-10  Draft Enact
    2.sunbing 49683           2012-5-29  增加复位原因，便于问题定位
*****************************************************************************/
VOS_UINT32  NAS_EMM_MsSuspendSsSyscfgWaitOtherMsgTimerExp(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru  )
{
    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;

    NAS_EMM_PUBU_LOG_INFO(" NAS_EMM_MsSuspendSsSyscfgWaitOtherMsgTimerExp");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsSuspendSsSyscfgWaitOtherMsgTimerExp_ENUM,LNAS_ENTRY);

    /*收到消息个数少于2，说明ESM和RABM的回复消息还没有收全*/
    if(NAS_EMM_SUSPEND_UPLAYER_NUM_CM > NAS_EMM_GetUplayerCount())
    {
        NAS_EMM_SendMmcErrInd(NAS_EMM_REBOOT_TYPE_SYSCFG_SUSPEND_ECM_FAIL);
    }
    else
    {
        NAS_EMM_SendMmcErrInd(NAS_EMM_REBOOT_TYPE_SYSCFG_SUSPEND_RRC_FAIL);
    }

    /* 清除此次挂起的上层响应记录 */
    NAS_EMM_GetUplayerCount() = NAS_EMM_SUSPEND_UPLAYER_NUM_INITVALUE;

    return  NAS_LMM_MSG_HANDLED;
}
/*****************************************************************************
 Function Name   : NAS_EMM_MsSuspendSsSomeStatusMsgIntraTauReq
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.FTY         2012-02-21  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsSuspendSsSomeStatusMsgIntraTauReq( VOS_UINT32  ulMsgId,
                                                    VOS_VOID   *pMsgStru )
{
    NAS_LMM_INTRA_TAU_REQ_STRU         *pIntraTauReq = NAS_EMM_NULL_PTR;
    (VOS_VOID)ulMsgId;
    pIntraTauReq    = (NAS_LMM_INTRA_TAU_REQ_STRU*)pMsgStru;
    NAS_EMM_TAU_LOG_INFO(               "NAS_EMM_MsSuspendSsSomeStatusMsgIntraTauReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsSuspendSsSomeStatusMsgIntraTauReq_ENUM,LNAS_ENTRY);
    if(NAS_EMM_NULL_PTR                 == pMsgStru)
    {
        NAS_EMM_TAU_LOG_ERR(            "NAS_EMM_MsSuspendSsSomeStatusMsgIntraTauReq PARA NULL!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsSuspendSsSomeStatusMsgIntraTauReq_ENUM,LNAS_NULL_PTR);
        return NAS_LMM_MSG_DISCARD;
    }
    if(NAS_LMM_INTRA_TAU_TYPE_PARA_CHANGE == pIntraTauReq->enIntraTauType)
    {
        NAS_LMM_SetEmmInfoDrxNetCapChange( NAS_EMM_YES);
    }
    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsRegInitRcvLrrcSyscfgCnfProc
 Description     : 主状态EMM_MS_REG_INIT收到LRRC的LRRC_LMM_SYS_CFG_CNF时的处理
                   主要用于UE无线能力上报。
 Input           : None
 Output          : None
 Return          : VOS_UINT32
 History         :
    1.sunjitan 00193151      2012-01-17  Draft Enact
    2.niuxiufan 00181501     2012-05-06  modify

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegInitRcvLrrcSyscfgCnfProc(VOS_VOID)
{

    /* 打印进入函数 */
    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_MsRegInitRcvLrrcSyscfgCnfProc is entered !");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegInitRcvLrrcSyscfgCnfProc_ENUM,LNAS_ENTRY);

    /* 如果UE无线能力发生变化 */
    if(NAS_LMM_UE_RADIO_CAP_NOT_CHG != NAS_LMM_GetEmmInfoUeRadioCapChgFlag())
    {
        NAS_EMM_PUBU_LOG_INFO("NAS_EMM_MsRegInitRcvLrrcSyscfgCnfProc: UE radio capability is changed, re-attach needed!");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegInitRcvLrrcSyscfgCnfProc_ENUM,LNAS_FUNCTION_LABEL1);

        /* 停止ATTACH定时器 */
        NAS_LMM_Stop3402Timer();
        NAS_LMM_StopStateTimer(TI_NAS_EMM_T3410);
        NAS_LMM_StopPtlTimer(TI_NAS_EMM_PTL_T3411);
        NAS_LMM_StopStateTimer(TI_NAS_EMM_WAIT_ESM_BEARER_CNF);
        NAS_LMM_StopStateTimer(TI_NAS_EMM_WAIT_ESM_PDN_RSP);
        NAS_LMM_StopStateTimer(TI_NAS_EMM_WAIT_RRC_DATA_CNF);

        /* 修改状态：进入主状态DEREG子状态DEREG_PLMN_SEARCH,此时服务状态不上报改变*/
        NAS_EMM_AdStateConvert(EMM_MS_DEREG,
                           EMM_SS_DEREG_PLMN_SEARCH ,
                           TI_NAS_EMM_STATE_NO_TIMER);

        /* 通知ESM清除资源 */
        NAS_EMM_PLMN_SendEmmEsmStautsInd(EMM_ESM_ATTACH_STATUS_DETACHED);

        /* 如果处于连接态，直接发送释放消息 */
        if(NAS_EMM_CONN_IDLE != NAS_EMM_GetConnState())
        {
            /*发送RRC_MM_REL_REQ*/
            NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);

        }

        /* 转入DEREG.PLMN-SEARCH态后收到系统消息自然会发起ATTACH */
    }

    return  NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsRegSsAnyStateRcvLrrcSyscfgCnfCommProc
 Description     : 主状态EMM_MS_REG收到LRRC的LRRC_LMM_SYS_CFG_CNF时的处理
                   主要用于UE无线能力上报。
 Input           : None
 Output          : None
 Return          : VOS_UINT32
 History         :
    1.sunjitan 00193151      2012-01-17  Draft Enact
    2.liuhua   00212067      2012-05-29  Correct timer id of T3411
*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegSsAnyStateRcvLrrcSyscfgCnfCommProc(VOS_VOID)
{
    NAS_LMM_PTL_TI_ENUM_UINT16  enPtlTimerId;

    /* 打印进入函数 */
    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_MsRegSsAnyStateRcvLrrcSyscfgCnfCommProc is entered !");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsAnyStateRcvLrrcSyscfgCnfCommProc_ENUM,LNAS_ENTRY);

    /* 如果GU发生变化且T3411和T3402未启动，发起TAU */
    if ((NAS_LMM_UE_RADIO_CAP_GU_CHG == NAS_LMM_GetEmmInfoUeRadioCapChgFlag())
        &&(NAS_EMM_YES != NAS_EMM_IsT3411orT3402Running(&enPtlTimerId)))
    {
        NAS_EMM_PUBU_LOG_NORM("NAS_EMM_MsRegSsAnyStateRcvLrrcSyscfgCnfCommProc: TAU  start !");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsAnyStateRcvLrrcSyscfgCnfCommProc_ENUM,LNAS_FUNCTION_LABEL1);

        /*NAS_EMM_TAU_SaveEmmTAUStartCause( NAS_EMM_TAU_START_CAUSE_INTRA_TAU_REQ);*/
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
        /* 新增入参TAU发起原因 */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_RADIO_CAP_CHANGE);
    }

    /* 如果LTE发生变化，本地DETACH，清除TAU和SER资源, 转入DEREG.NORMAL-SERVICE，重新ATTACH */
    else if (NAS_LMM_UE_RADIO_CAP_LTE_CHG == NAS_LMM_GetEmmInfoUeRadioCapChgFlag())
    {
        NAS_EMM_PUBU_LOG_NORM("NAS_EMM_MsRegSsAnyStateRcvLrrcSyscfgCnfCommProc: LTE change, local detach and re-attach needed.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsAnyStateRcvLrrcSyscfgCnfCommProc_ENUM,LNAS_FUNCTION_LABEL2);
        if (NAS_EMM_CONN_IDLE != NAS_EMM_GetConnState())
        {
            NAS_EMM_PUBU_LOG_NORM("NAS_EMM_MsRegSsAnyStateRcvLrrcSyscfgCnfCommProc:  Connected.");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsAnyStateRcvLrrcSyscfgCnfCommProc_ENUM,LNAS_FUNCTION_LABEL3);

            /*规避SYSCFG导致的本地DETACH后MMC发释放不响应和搜网问题，给RRC发释放
                 压栈处理是为了防止触发SERVICE流程 */
            NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);
            return NAS_LMM_MSG_HANDLED;
        }
        /* 本地DETACH之后重新ATTACH  */
        NAS_EMM_SomeStateRcvMsgSysInfoLteRadioCapChgCommProc();
    }
    else
    {
        /* 无变化不做特殊处理 */
    }

    return  NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsTauSerRcvLrrcSyscfgCnfProc
 Description     : 主状态EMM_MS_TAU_INIT或EMM_MS_SER_INIT, 等待网侧回复时收到
                    LRRC的LRRC_LMM_SYS_CFG_CNF时的处理，主要用于UE无线能力上报。
 Input           : None
 Output          : None
 Return          : VOS_UINT32
 History         :
    1.sunjitan 00193151      2012-01-17  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_EMM_MsTauSerRcvLrrcSyscfgCnfProc(VOS_VOID)
{
    MMC_LMM_TAU_RSLT_ENUM_UINT32        ulTauRslt = MMC_LMM_TAU_RSLT_BUTT;

    /* 打印进入函数 */
    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_MsTauSerRcvLrrcSyscfgCnfProc is entered !");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsTauSerRcvLrrcSyscfgCnfProc_ENUM,LNAS_ENTRY);

    if (NAS_LMM_UE_RADIO_CAP_NOT_CHG== NAS_LMM_GetEmmInfoUeRadioCapChgFlag())
    {
        NAS_EMM_PUBU_LOG_NORM("NAS_EMM_MsTauSerRcvLrrcSyscfgCnfProc: UE Radio capability is not changed. ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsTauSerRcvLrrcSyscfgCnfProc_ENUM,LNAS_FUNCTION_LABEL1);
        return  NAS_LMM_MSG_HANDLED;
    }

    /* 如果是TAU过程中，终止TAU */
    if (EMM_MS_TAU_INIT == NAS_EMM_CUR_MAIN_STAT)
    {
        NAS_EMM_PUBU_LOG_NORM("NAS_EMM_MsTauSerRcvLrrcSyscfgCnfProc: TAU procedure is stopped. ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsTauSerRcvLrrcSyscfgCnfProc_ENUM,LNAS_FUNCTION_LABEL2);

        /* 向MMC发送LMM_MMC_TAU_RESULT_IND消息 */
        ulTauRslt = MMC_LMM_TAU_RSLT_FAILURE;
        NAS_EMM_MmcSendTauActionResultIndOthertype((VOS_VOID*)&ulTauRslt);

        NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_TAU_T3430);

        #if (FEATURE_ON == FEATURE_DSDS)
        /*发送end notify消息给RRC，通知RRC释放资源*/
        NAS_EMM_TAU_SendRrcDsdsEndNotify();
        #endif
    }

    /* 否则必然是SER过程中，终止SER*/
    else
    {
        NAS_EMM_PUBU_LOG_NORM("NAS_EMM_MsTauSerRcvLrrcSyscfgCnfProc: SER procedure is stopped. ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsTauSerRcvLrrcSyscfgCnfProc_ENUM,LNAS_FUNCTION_LABEL3);
        NAS_EMM_SER_AbnormalOver();
    }

    /* 转入REG.PLMN-SEARCH等系统消息 */
    NAS_EMM_AdStateConvert(EMM_MS_REG,
                           EMM_SS_REG_PLMN_SEARCH,
                           TI_NAS_EMM_STATE_NO_TIMER);

    /* 全都发释放，RRC在空闲态和连接态处理基本相同 */
    /* 如果处于连接态，直接发送释放消息 */
    NAS_EMM_PUBU_LOG_NORM("NAS_EMM_MsTauSerRcvLrrcSyscfgCnfProc: Connected! SndRrcRelReq. ");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsTauSerRcvLrrcSyscfgCnfProc_ENUM,LNAS_FUNCTION_LABEL4);

    /*发送RRC_MM_REL_REQ*/
    NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);

    return  NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsRegWaitAccGrantIndRcvLrrcSyscfgCnfProc
 Description     : 主状态EMM_MS_REG子状态WAIT_ACCESS_GRANT_IND收到
                   LRRC的LRRC_LMM_SYS_CFG_CNF时的处理，主要用于UE无线能力上报。
 Input           : None
 Output          : None
 Return          : VOS_UINT32
 History         :
    1.sunjitan 00193151      2012-01-17  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegSsWaitAccGrantIndRcvLrrcSyscfgCnfProc(VOS_VOID)
{

    /* 打印进入函数 */
    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_MsRegSsWaitAccGrantIndRcvLrrcSyscfgCnfProc is entered !");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsWaitAccGrantIndRcvLrrcSyscfgCnfProc_ENUM,LNAS_ENTRY);

    /* GU发生变化 */
    if (NAS_LMM_UE_RADIO_CAP_GU_CHG == NAS_LMM_GetEmmInfoUeRadioCapChgFlag())
    {
        /* 看信令是否被BAR，否: TAU;   是: 不做特殊处理 */
        if (NAS_EMM_SUCC != NAS_EMM_JudgeBarType(NAS_EMM_BAR_TYPE_MO_SIGNAL))
        {
            NAS_LMM_PUBM_LOG_NORM("NAS_EMM_MsRegSsWaitAccGrantIndRcvLrrcSyscfgCnfProc: TAU  start");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsWaitAccGrantIndRcvLrrcSyscfgCnfProc_ENUM,LNAS_FUNCTION_LABEL1);

            /*NAS_EMM_TAU_SaveEmmTAUStartCause( NAS_EMM_TAU_START_CAUSE_INTRA_TAU_REQ);*/
            NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
            /* 新增入参TAU发起原因 */
            NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_RADIO_CAP_CHANGE);
        }
    }

    /* LTE发生变化 */
    else if (NAS_LMM_UE_RADIO_CAP_LTE_CHG == NAS_LMM_GetEmmInfoUeRadioCapChgFlag())
    {
        NAS_EMM_PUBU_LOG_NORM("NAS_EMM_MsRegSsWaitAccGrantIndRcvLrrcSyscfgCnfProc: LTE  radio capability is changed.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsWaitAccGrantIndRcvLrrcSyscfgCnfProc_ENUM,LNAS_FUNCTION_LABEL2);


        /* 看信令是否被BAR，否: 本地DETACH后，转入DEREG.NORMAL态，发内部ATTACH;
                            是: 保持状态不变 */
        if (NAS_EMM_SUCC != NAS_EMM_JudgeBarType(NAS_EMM_BAR_TYPE_MO_SIGNAL))
        {
            NAS_LMM_PUBM_LOG_NORM("NAS_EMM_MsRegSsWaitAccGrantIndRcvLrrcSyscfgCnfProc: MO_SIGNAL  isn't  barred.");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsWaitAccGrantIndRcvLrrcSyscfgCnfProc_ENUM,LNAS_FUNCTION_LABEL3);

            /* 本地DETACH之后重新ATTACH */
            NAS_EMM_SomeStateRcvMsgSysInfoLteRadioCapChgCommProc();
        }
    }
    else
    {
        /* 无变化则无特殊处理*/
    }

    return  NAS_LMM_MSG_HANDLED;
}
/*****************************************************************************
 Function Name   : NAS_EMM_MsRegInitRcvLrrcSuspendIndProc
 Description     : 主状态EMM_MS_REG_INIT收到LRRC的LRRC_LMM_SUSPEND_IND时的处理
 Input           : None
 Output          : None
 Return          : VOS_VOID
 History         :
    1.niuxiufan 00181501      2012-06-12  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_EMM_MsRegInitRcvLrrcSuspendIndProc(const MsgBlock * pMsg )
{
    VOS_UINT32                  ulMsgId = ID_LRRC_LMM_SUSPEND_IND;

    /*根据当前子状态处理 */
    switch (NAS_EMM_CUR_SUB_STAT)
    {

        case EMM_SS_ATTACH_WAIT_ESM_PDN_RSP:
            /* 注册流程终止，停定时器，尝试次数加1，根据尝试次数处理，通知ESM进入DETACHED态，继续挂起流程*/
             NAS_LMM_StopStateTimer(          TI_NAS_EMM_WAIT_ESM_PDN_RSP);
             NAS_EMM_EsmSendStatResult(       EMM_ESM_ATTACH_STATUS_DETACHED);

             NAS_EMM_GLO_AD_GetAttAtmpCnt()++;
             NAS_EMM_AppSendAttFailWithPara();
             NAS_EMM_AttNrmFailProc();

             (VOS_VOID)NAS_EMM_RcvLrrcSuspendInd(ulMsgId, pMsg);

            break;

        default:

            /*停ATTACH相关状态定时器，增加ATTACH尝试次数，根据尝试次数进行处理，
            给MMC上报ATTACH失败，通知ESM进入DETACHED，给RRC发链路释放请求，压栈*/
            NAS_LMM_StopStateTimer(          TI_NAS_EMM_T3410);
            NAS_LMM_StopStateTimer(          TI_NAS_EMM_WAIT_ESM_BEARER_CNF);
            NAS_LMM_StopStateTimer(          TI_NAS_EMM_WAIT_RRC_DATA_CNF);

            NAS_EMM_TAU_SendEsmStatusInd(  EMM_ESM_ATTACH_STATUS_DETACHED);

            NAS_EMM_GLO_AD_GetAttAtmpCnt()++;
            NAS_EMM_AppSendAttFailWithPara();
            NAS_EMM_AttNrmFailProc();

            NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);

            break;
    }

}
/*****************************************************************************
 Function Name   : NAS_EMM_MsDeregInitRcvLrrcSuspendIndProc
 Description     : 主状态EMM_MS_DEREG_INIT收到LRRC的LRRC_LMM_SUSPEND_IND时的处理
 Input           : None
 Output          : None
 Return          : VOS_VOID
 History         :
    1.niuxiufan 00181501      2012-06-12  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_EMM_MsDeregInitRcvLrrcSuspendIndProc(const MsgBlock * pMsg )
{
    (VOS_VOID)pMsg;

    /*根据当前子状态处理 */
    switch (NAS_EMM_CUR_SUB_STAT)
    {

        case EMM_SS_DETACH_WAIT_CN_DETACH_CNF:
            /* 更新DETACH尝试次数为0，停止DETACH相关状态定时器，给MMC发送DETACH成功
               通知ESM进入DETACHED，转到DEREG+NORMAL_SERVICE态，给RRC发链路释放请求，压栈*/
            NAS_LMM_StopStateTimer(          TI_NAS_EMM_T3421);

            #if (FEATURE_ON == FEATURE_DSDS)
            /*发送end notify消息给RRC，通知RRC释放资源*/
            NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_PS_DETACH);
            #endif

            NAS_EMM_GLO_AD_GetDetAtmpCnt()  = 0;

            /*向ESM发送ID_EMM_ESM_STATUS_IND消息*/
            NAS_EMM_EsmSendStatResult(          EMM_ESM_ATTACH_STATUS_DETACHED);

            NAS_EMM_SendDetRslt(MMC_LMM_DETACH_RSLT_SUCCESS);

            NAS_EMM_AdStateConvert( EMM_MS_DEREG,
                                    EMM_SS_DEREG_NORMAL_SERVICE,
                                    TI_NAS_EMM_STATE_NO_TIMER);

            NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);

            break;



        default:
            break;
    }

}
/*****************************************************************************
 Function Name   : NAS_EMM_MsSerInitRcvLrrcSuspendIndProc
 Description     : 主状态EMM_MS_SER_INIT收到LRRC的LRRC_LMM_SUSPEND_IND时的处理
 Input           : None
 Output          : None
 Return          : VOS_VOID
 History         :
    1.niuxiufan 00181501      2012-06-12  Draft Enact
    2.lihong 00150010         2012-12-18  Modify:Emergency
*****************************************************************************/
VOS_VOID  NAS_EMM_MsSerInitRcvLrrcSuspendIndProc(const MsgBlock * pMsg )
{
    VOS_UINT32                  ulMsgId = ID_LRRC_LMM_SUSPEND_IND;

    NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417);

    /*根据当前子状态处理 */
    switch (NAS_EMM_CUR_SUB_STAT)
    {

        case EMM_SS_SER_WAIT_CN_SER_CNF:

            /* 根据SERVICE触发条件分别处理*/
            if(NAS_EMM_SER_START_CAUSE_SMS_EST_REQ == NAS_EMM_SER_GetSerStartCause())
            {
               NAS_LMM_SndLmmSmsErrInd(LMM_SMS_ERR_CAUSE_OTHERS);
               NAS_EMM_SER_ClearResource();
               NAS_EMM_PUBU_FSMTranState( EMM_MS_REG,
                                    EMM_SS_REG_NORMAL_SERVICE,
                                    TI_NAS_EMM_STATE_NO_TIMER);


               /*通知ERABM SERVICE 流程失败*/
               NAS_EMM_SER_SendRabmReestInd(EMM_ERABM_REEST_STATE_FAIL);

               NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);
            }
            #if (FEATURE_LPP == FEATURE_ON)
            else if(NAS_EMM_SER_START_CAUSE_LPP_EST_REQ == NAS_EMM_SER_GetSerStartCause())
            {
                NAS_EMM_SendLppEstCnf(LMM_LPP_EST_RESULT_FAIL_SERVICE_FAIL);
                NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_BUTT);
                NAS_EMM_SER_ClearResource();
                NAS_EMM_PUBU_FSMTranState( EMM_MS_REG,
                                            EMM_SS_REG_NORMAL_SERVICE,
                                            TI_NAS_EMM_STATE_NO_TIMER);

                /*通知ERABM SERVICE 流程失败*/
                NAS_EMM_SER_SendRabmReestInd(EMM_ERABM_REEST_STATE_FAIL);

                NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);
            }

            else if(NAS_EMM_SER_START_CAUSE_SS_EST_REQ == NAS_EMM_SER_GetSerStartCause())
            {
                NAS_LMM_SndLmmLcsEstCnf( LMM_LCS_EST_RSLT_FAIL_SERVICE_FAIL,
                                        NAS_EMM_SER_GetSsOrLppOpid());
                NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_BUTT);
                NAS_EMM_SER_ClearResource();
                NAS_EMM_PUBU_FSMTranState(  EMM_MS_REG,
                                            EMM_SS_REG_NORMAL_SERVICE,
                                            TI_NAS_EMM_STATE_NO_TIMER);

                /*通知ERABM SERVICE 流程失败*/
                NAS_EMM_SER_SendRabmReestInd(EMM_ERABM_REEST_STATE_FAIL);

                NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);
            }
            #endif
            else if(VOS_TRUE == NAS_EMM_SER_IsCsfbProcedure())
            {
                /* 如果已经收到ABORT消息， */
                if (NAS_EMM_CSFB_ABORT_FLAG_VALID == NAS_EMM_SER_GetEmmSerCsfbAbortFlag())
                {
                    NAS_EMM_SER_LOG_NORM("NAS_EMM_MsSerInitRcvLrrcSuspendIndProc:CSFB is already aborted!");
                    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsSerInitRcvLrrcSuspendIndProc_ENUM,LNAS_FUNCTION_LABEL1);

                    /* 给LRRC响应挂起失败 */
                    NAS_EMM_SendLrrcSuspendRsp(LRRC_LNAS_FAIL);

                    NAS_EMM_SER_ClearResource();

                    /* 状态改为 reg.normal service */
                    NAS_EMM_PUBU_FSMTranState( EMM_MS_REG,
                                    EMM_SS_REG_NORMAL_SERVICE,
                                    TI_NAS_EMM_STATE_NO_TIMER);
                }
                else
                {
                    (VOS_VOID)NAS_EMM_RcvLrrcSuspendInd(ulMsgId, pMsg);
                }
            }
            else
            {
                NAS_EMM_TranStatePsNormalServiceOrPsLimitService();
                /*NAS_EMM_PUBU_FSMTranState( EMM_MS_REG,
                                    EMM_SS_REG_NORMAL_SERVICE,
                                    TI_NAS_EMM_STATE_NO_TIMER);*/
                /*通知ERABM SERVICE 流程失败*/
                NAS_EMM_SER_SendRabmReestInd(EMM_ERABM_REEST_STATE_FAIL);

                NAS_EMM_SER_ClearResource();

                NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);
            }

            break;

        default:
            break;
    }

}
/*****************************************************************************
 Function Name   : NAS_EMM_MsTauInitRcvLrrcSuspendIndProc
 Description     : 主状态EMM_MS_TAU_INIT收到LRRC的LRRC_LMM_SUSPEND_IND时的处理
 Input           : None
 Output          : None
 Return          : VOS_VOID
 History         :
    1.niuxiufan 00181501      2012-06-12  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_EMM_MsTauInitRcvLrrcSuspendIndProc(const MsgBlock * pMsg )
{
    MMC_LMM_TAU_RSLT_ENUM_UINT32        ulTauRslt = MMC_LMM_TAU_RSLT_BUTT;
    VOS_UINT32                  ulMsgId = ID_LRRC_LMM_SUSPEND_IND;

    /* 作异常失败处理,给MMC上报失败,继续挂起流程*/
    ulTauRslt = MMC_LMM_TAU_RSLT_FAILURE;
    NAS_EMM_MmcSendTauActionResultIndOthertype((VOS_VOID*)&ulTauRslt);

    (VOS_VOID)NAS_EMM_RcvLrrcSuspendInd(ulMsgId, pMsg);

    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_MsAuthInitRcvLrrcSuspendIndProc
 Description     : 主状态EMM_MS_AUTH_INIT收到LRRC的LRRC_LMM_SUSPEND_IND时的处理
 Input           : None
 Output          : None
 Return          : VOS_VOID
 History         :
    1.niuxiufan 00181501      2012-06-12  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_EMM_MsAuthInitRcvLrrcSuspendIndProc(const MsgBlock * pMsg )
{
    (VOS_VOID)pMsg;

    /* 停T3418和T3420定时器，转到AUTH_INIT+WAIT_REL_IND态，给RRC发链路释放请求，压栈*/
    NAS_LMM_StopStateTimer(TI_NAS_EMM_T3418);
    NAS_LMM_StopStateTimer(TI_NAS_EMM_T3420);



    NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);

}

/*****************************************************************************
 Function Name   : NAS_EMM_MsRrcConnRelInitRcvLrrcSuspendIndProc
 Description     : 在链路释放状态收到LRRC的挂起消息处理
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.leili 00132387      2012-8-20  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_MsRrcConnRelInitRcvLrrcSuspendIndProc( VOS_VOID)
{
    if (NAS_EMM_CONN_RELEASING != NAS_EMM_GetConnState())
    {
        NAS_EMM_PUBU_LOG_NORM("NAS_EMM_MsRrcConnRelInitRcvLrrcSuspendIndProc:T3440 is running");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRrcConnRelInitRcvLrrcSuspendIndProc_ENUM,LNAS_EMM_T3440_RUNNING);

        NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_T3440);

        /*发送RRC_MM_REL_REQ*/
        NAS_EMM_SndRrcRelReq(NAS_LMM_NOT_BARRED);

        NAS_EMM_SetConnState(NAS_EMM_CONN_RELEASING);

        NAS_LMM_StartStateTimer(TI_NAS_EMM_MRRC_WAIT_RRC_REL_CNF);
    }
    else
    {
        /*根据接口描述，丢弃 */
        NAS_EMM_PUBU_LOG1_NORM("NAS_EMM_MsRrcConnRelInitRcvLrrcSuspendIndProc: discard. state = ",
                        NAS_EMM_CUR_MAIN_STAT);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsRrcConnRelInitRcvLrrcSuspendIndProc_ENUM,LNAS_EMM_MAIN_STATE,
                        NAS_EMM_CUR_MAIN_STAT);
        NAS_EMM_SendLrrcSuspendRsp(LRRC_LNAS_FAIL);
    }
    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsSuspendSsRrcOriWaitMmcSuspendFailProc
 Description     : 主状态EMM_MS_SUSPEND 子状态WAIT_MMC_SUSPEND_RSP收到MMC的挂起失败或者超时的处理
 Input           : None
 Output          : None
 Return          : VOS_VOID
 History         :
    1.niuxiufan 00181501      2012-06-12  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_EMM_MsSuspendSsRrcOriWaitMmcSuspendFailProc(VOS_VOID)
{
    NAS_LMM_FSM_STATE_STRU             *pstStatBeforeSuspend  = NAS_EMM_NULL_PTR;
    VOS_UINT32                          ulStatBeforeSuspend;
    NAS_LMM_PTL_TI_ENUM_UINT16          enPtlTimerId;

    pstStatBeforeSuspend   =  NAS_EMM_GetStateBeforeSuspendAddr();

    ulStatBeforeSuspend = NAS_LMM_PUB_COMP_EMMSTATE(pstStatBeforeSuspend->enMainState,
                                        pstStatBeforeSuspend->enSubState);

    switch (ulStatBeforeSuspend)
    {
        case NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_TAU_INIT, EMM_SS_TAU_WAIT_CN_TAU_CNF):
            /* 如果T3430已经超时,则按照T3430超时进行处理*/
            if (NAS_LMM_TIMER_STOPED == NAS_LMM_IsStaTimerRunning(TI_NAS_EMM_STATE_TAU_T3430))
            {
                /*TAU ATTEMPT COUNT ++*/
                NAS_EMM_TAU_GetEmmTAUAttemptCnt()++;

                /*调用消息处理函数*/
                NAS_EMM_TAU_RcvT3430Exp();
            }
            break;

        case NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_SER_INIT, EMM_SS_SER_WAIT_CN_SER_CNF):
            /* 如果T3417EXT超时,则按照该定时器超时处理 ,判断挂起之前进行了CSFB流程,之前在这个状态挂起时,如果CSFB,不清除发起原因*/
            if ((NAS_LMM_TIMER_STOPED == NAS_LMM_IsStaTimerRunning(TI_NAS_EMM_STATE_SERVICE_T3417_EXT))
                 && (VOS_TRUE == NAS_EMM_SER_IsCsfbProcedure()))
            {

                NAS_EMM_SER_AbnormalOver();

                NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_NULL);

                NAS_EMM_MmSendCsfbSerEndInd(MM_LMM_CSFB_SERVICE_RSLT_T3417EXT_TIME_OUT, NAS_LMM_CAUSE_NULL);

                /*转换EMM状态机MS_REG+EMM_SS_REG_NORMAL_SERVICE*/
                NAS_EMM_TAUSER_FSMTranState(EMM_MS_REG, EMM_SS_REG_NORMAL_SERVICE, TI_NAS_EMM_STATE_NO_TIMER);

                if (NAS_EMM_CONN_DATA != NAS_EMM_GetConnState())
                {
                    /* 如果有未完成的TAU，则等收到系统消息后再处理 */


                    /*向MRRC发送NAS_EMM_MRRC_REL_REQ消息*/
                    NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);
                }

            }
            break;

        case NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_DEREG, EMM_SS_DEREG_ATTEMPTING_TO_ATTACH):
            /* 如果3411和3402都已超时,则按照T3411超时处理 */
            if (NAS_EMM_YES != NAS_EMM_IsT3411orT3402Running(&enPtlTimerId))
            {
                /*重新ATTATCH*/
                NAS_EMM_AD_Reattach();
            }
            break;

        case NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM):
        case NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_ATTEMPTING_TO_UPDATE):
            /* 如果3411和3402都已超时,则按照T3411超时处理 */
            if (NAS_EMM_YES != NAS_EMM_IsT3411orT3402Running(&enPtlTimerId))
            {
                NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);

                /*调用消息处理函数*/
                /* 新增入参TAU发起原因 */
                NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_MMC_SUSPEND_FAIL);
            }
            break;

        case NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_NORMAL_SERVICE):
            /* 如果3411已经超时,如要判断TAU触发条件*/
            if (NAS_LMM_TIMER_STOPED == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_T3411))
            {
                /*挂起过程中能够触发TAU的场景*/
                NAS_EMM_RegSomeStateMsgSysInfoCommProc();
            }
            break;
        default:
            /* 其他场景不处理 */
            break;


    }

}

VOS_UINT32  NAS_LMM_ProcRrcUeCapChangeIndComm(VOS_VOID)
{
    VOS_UINT32                          ulCurEmmStat;
    VOS_UINT32                          ulRslt = NAS_LMM_MSG_DISCARD;

    /* 打印进入函数 */
    NAS_EMM_PUBU_LOG_INFO("NAS_LMM_ProcRrcUeCapChangeIndComm is entered !");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_ProcRrcUeCapChangeIndComm_ENUM,LNAS_ENTRY);

    /* L处于主模 */
    if (NAS_LMM_CUR_LTE_ACTIVE == NAS_EMM_GetCurLteState())
    {
        NAS_EMM_PUBU_LOG_NORM("NAS_LMM_ProcRrcUeCapChangeIndComm:  CUR_LTE_ACTIVE.");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_ProcRrcUeCapChangeIndComm_ENUM,LNAS_FUNCTION_LABEL1);

        if(NAS_EMM_CONN_ESTING == NAS_EMM_GetConnState())
        {
            /* 停止 定时器*/
            NAS_LMM_StopStateTimer(TI_NAS_EMM_MRRC_WAIT_RRC_CONN_CNF);
        }

        /* 获取EMM当前状态 */
        ulCurEmmStat = NAS_LMM_PUB_COMP_EMMSTATE(NAS_EMM_CUR_MAIN_STAT,
                                          NAS_EMM_CUR_SUB_STAT);


        /* 根据不同的状态进行不同处理，仅需记录UE无线能力变化
               而当前无需特殊处理的状态不在此列 */
        switch(ulCurEmmStat)
        {
            /* EMM_MS_REG_INIT的所有子状态一起处理 */
            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG_INIT, EMM_SS_ATTACH_WAIT_CN_ATTACH_CNF):
            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG_INIT, EMM_SS_ATTACH_WAIT_ESM_BEARER_CNF):
            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG_INIT, EMM_SS_ATTACH_WAIT_RRC_DATA_CNF):

                    /* 终止ATTACH流程，重新ATTACH */
                    ulRslt = NAS_EMM_MsRegInitRcvLrrcSyscfgCnfProc();
                    break;

            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_NORMAL_SERVICE):
            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM):

                    /* 如L变化本地DETACH后重新ATTACH */
                    ulRslt = NAS_EMM_MsRegSsAnyStateRcvLrrcSyscfgCnfCommProc();
                    break;

            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_WAIT_ACCESS_GRANT_IND):

                    /* 如GU变化且未被BAR，发起TAU；如L变化且未被BAR，本地DETACH后重新ATTACH，
                       如被BAR, 保持状态不变 */
                    ulRslt = NAS_EMM_MsRegSsWaitAccGrantIndRcvLrrcSyscfgCnfProc();
                    break;

            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_IMSI_DETACH_WATI_CN_DETACH_CNF):
            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_AUTH_INIT, EMM_SS_AUTH_WAIT_CN_AUTH):

                    /* 能力发生变化则低优先级缓存 */
                    ulRslt = NAS_LMM_STORE_LOW_PRIO_MSG;
                    break;

            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_TAU_INIT, EMM_SS_TAU_WAIT_CN_TAU_CNF):
            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_SER_INIT, EMM_SS_SER_WAIT_CN_SER_CNF):

                    /* 终止TAU或SER, 直接释放, 转入REG.PLMN_SEARCH等系统消息 */
                    ulRslt = NAS_EMM_MsTauSerRcvLrrcSyscfgCnfProc();
                    break;
            default:

                    /* 其它情况认为已处理*/
                    ulRslt = NAS_LMM_MSG_HANDLED;
                    break;
        }
    }
    else
    {
        /* L处于从模则无特殊处理 */
        ulRslt = NAS_LMM_MSG_HANDLED;
    }

    return ulRslt;
}


/*lint +e961*/
/*lint +e960*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

/* end of 子系统+模块+文件名.c */
