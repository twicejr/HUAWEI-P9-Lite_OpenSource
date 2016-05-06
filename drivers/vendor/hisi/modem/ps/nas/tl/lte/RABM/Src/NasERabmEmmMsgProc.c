

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include  "NasERabmEmmMsgProc.h"
#include  "NasERabmRrcMsgProc.h"
#include  "NasERabmIpFilter.h"
#include  "NasERabmETcMsgProc.h"
#include  "LUPAppItf.h"
/*#include  "R_ITF_FlowCtrl.h"*/
#include  "NasERabmCdsMsgProc.h"
#include  "CdsInterface.h"



/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASRABMEMMMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASRABMEMMMSGPROC_C
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
/* NAS_ERABM_RF_RECOVERY_RB_REEST_TIMER 默认时常 */
VOS_UINT32             g_ulErabmRfRecoveryTimerLength = 60000;


/*****************************************************************************
  3 Function
*****************************************************************************/
/*****************************************************************************
 Function Name   : NAS_ERABM_EmmMsgDistr()
 Description     : RABM模块EMM消息分发处理
 Input           : VOS_VOID *pRcvMsg-----------消息指针
 Output          : VOS_VOID
 Return          : VOS_VOID
 History         :
     1.yangqianhui 00135146       2008-9-8   Draft Enact

*****************************************************************************/

VOS_VOID NAS_ERABM_EmmMsgDistr( VOS_VOID *pRcvMsg )
{
    PS_MSG_HEADER_STRU         *pEmmMsg = VOS_NULL_PTR;

    pEmmMsg = (PS_MSG_HEADER_STRU*)pRcvMsg;

    /*打印进入该函数*/
    NAS_ERABM_INFO_LOG("NAS_ERABM_EmmMsgDistr is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ERABM_EmmMsgDistr_ENUM, LNAS_ENTRY);

    /*根据消息名，调用相应的消息处理函数*/
    switch (pEmmMsg->ulMsgName)
    {
        /*如果收到的是EMM_ERABM_REEST_IND消息，调用NAS_ERABM_RcvRabmEmmReest_Ind函数*/
        case ID_EMM_ERABM_REEST_IND:
            NAS_ERABM_RcvRabmEmmReestInd((EMM_ERABM_REEST_IND_STRU*)pRcvMsg);
            break;

        /*如果收到的是EMM_ERABM_REL_IND消息，调用NAS_ERABM_RcvRabmEmmRelInd函数*/
        case ID_EMM_ERABM_REL_IND:
            NAS_ERABM_RcvRabmEmmRelInd();
            break;

        case ID_EMM_ERABM_RRC_CON_REL_IND:
            NAS_ERABM_RcvRabmEmmRrcConRelInd((EMM_ERABM_RRC_CON_REL_IND_STRU *)pRcvMsg);
            break;

        case ID_EMM_ERABM_SUSPEND_IND:
            NAS_ERABM_RcvRabmEmmSuspendInd( (EMM_ERABM_SUSPEND_IND_STRU *) pRcvMsg );
            break;

        case ID_EMM_ERABM_RESUME_IND:
            NAS_ERABM_RcvRabmEmmResumeInd( (EMM_ERABM_RESUME_IND_STRU *) pRcvMsg );
            break;

        default:
            NAS_ERABM_WARN_LOG("NAS_ERABM_EmmMsgDistr:WARNING:EMM->RABM Message name non-existent!");
            TLPS_PRINT2LAYER_WARNING(NAS_ERABM_EmmMsgDistr_ENUM, LNAS_MSG_INVALID);
            break;
    }
}

/*****************************************************************************
 Function Name   : NAS_ERABM_RcvRabmEmmReestInd()
 Description     : RABM模块EMM_ERABM_REEST_IND_STRU消息分发处理
 Input           : EMM_ERABM_REEST_IND_STRU *pRcvMsg-----------消息指针
 Output          : VOS_VOID
 Return          : VOS_VOID

  History        :
    1.yangqianhui 00135146       2008-9-8   Draft Enact
    2.yangqianhui 00135146       2009-09-19   BN8D01065  Modify
    3.yangfan     00159566       2011-03-28   Modify

*****************************************************************************/
/*lint -e960*/
/*lint -e961*/
VOS_VOID  NAS_ERABM_RcvRabmEmmReestInd(const EMM_ERABM_REEST_IND_STRU *pRcvMsg )
{
    if (NAS_ERABM_L_MODE_STATUS_NORMAL != NAS_ERABM_GetLModeStatus())
    {
        NAS_ERABM_WARN_LOG("NAS_ERABM_RcvRabmEmmReestInd:Rabm is already suspended!");
        TLPS_PRINT2LAYER_WARNING(NAS_ERABM_RcvRabmEmmReestInd_ENUM, LNAS_ERABM_RabmSuspended);
        return ;
    }

    switch(pRcvMsg->enReEstState)
    {
        /*case EMM_ERABM_REEST_STATE_SUCC:*/
        case EMM_ERABM_REEST_STATE_FAIL:

            /*打印进入该函数*/
            NAS_ERABM_LOG1("NAS_ERABM_RcvRabmEmmReestInd: receive Emm Reset result: .",
                          pRcvMsg->enReEstState);
            TLPS_PRINT2LAYER_INFO1(NAS_ERABM_RcvRabmEmmReestInd_ENUM, LNAS_ERABM_EmmResetResult, pRcvMsg->enReEstState);
            if(NAS_ERABM_TIMER_STATE_RUNNING == NAS_ERABM_IsTimerRunning(NAS_ERABM_RF_RECOVERY_RB_REEST_TIMER))
            {
                /* NAS_ERABM_RF_RECOVERY_RB_REEST_TIMER启动时,继续尝试恢复链路,解决连接态RF被抢,
                    UE进入IDLE态，导致UE和网侧状态不一致问题 */
                break;
            }
            /*SERVICE流程结束*,停止定时器*/
            NAS_ERABM_TimerStop(NAS_ERABM_WAIT_RB_REEST_TIMER);
            NAS_ERABM_SetEmmSrState(NAS_ERABM_SERVICE_STATE_TERMIN);
            /* 如果在正常模式下 */
            if (NAS_ERABM_MODE_TYPE_NORMAL == NAS_ERABM_GetMode())
            {
                /* 通知L2释放缓存的数据包 */
                /*APPITF_FreeAllofRabmBuf();*/

                /* 通知CDS释放缓存的数据包 */
                NAS_ERABM_SndErabmCdsFreeBuffDataInd();

                /* 清除上行数据阻塞标志*/
                NAS_ERABM_SetUpDataPending(EMM_ERABM_NO_UP_DATA_PENDING);
            }
            else if (NAS_ERABM_TIMER_STATE_STOPED == NAS_ERABM_IsTimerRunning(NAS_ERABM_WAIT_TC_FREE_BUFFER_TIMER))
            /*环回模式下不清理缓存，保持原上行数据Pending状态*/
            {
                NAS_ERABM_INFO_LOG("NAS_ERABM_RcvRabmEmmReestInd: NAS_ERABM_WAIT_TC_FREE_BUFFER_TIMER start.");
                TLPS_PRINT2LAYER_INFO(NAS_ERABM_RcvRabmEmmReestInd_ENUM, LNAS_FUNCTION_LABEL1);
                NAS_ERABM_TimerStart(   NAS_ERABM_WAIT_TC_FREE_BUFFER_LENGTH,
                                        NAS_ERABM_WAIT_TC_FREE_BUFFER_TIMER,
                                        NAS_ERABM_WAIT_TC_FREE_BUFFER_TIMER);
            }
            else
            {
                NAS_ERABM_INFO_LOG("NAS_ERABM_RcvRabmEmmReestInd: NAS_ERABM_WAIT_TC_FREE_BUFFER_TIMER is running.");
                TLPS_PRINT2LAYER_INFO(NAS_ERABM_RcvRabmEmmReestInd_ENUM, LNAS_FUNCTION_LABEL2);
            }
            break;

        case EMM_ERABM_REEST_STATE_INITIATE:

            /*打印进入该函数*/
            NAS_ERABM_INFO_LOG("NAS_ERABM_RcvRabmEmmReestInd: receive EMM_ERABM_REEST_STATE_INITIATE .");
            TLPS_PRINT2LAYER_INFO(NAS_ERABM_RcvRabmEmmReestInd_ENUM, LNAS_FUNCTION_LABEL3);
            /*SERVICE流程启动,启动定时器*/
            if (NAS_ERABM_SERVICE_STATE_TERMIN == NAS_ERABM_GetEmmSrState())
            {
                NAS_ERABM_TimerStart(   NAS_ERABM_WAIT_RB_REEST_LENGTH,
                                        NAS_ERABM_WAIT_RB_REEST_TIMER,
                                        VOS_FALSE);
                NAS_ERABM_SetEmmSrState(NAS_ERABM_SERVICE_STATE_INIT);
            }
            break;

        default:
            NAS_ERABM_WARN_LOG("NAS_ERABM_RcvRabmEmmReestInd:WARNNING: EstState illegal!");
            TLPS_PRINT2LAYER_WARNING(NAS_ERABM_RcvRabmEmmReestInd_ENUM, LNAS_ERABM_EstStateillegal);
            break;
    }
}

/*****************************************************************************
 Function Name   : NAS_ERABM_RcvRabmEmmRelInd()
 Description     : RABM模块EMM_ERABM_REL_IND_STRU消息分发处理
 Input           : VOS_VOID
 Output          : VOS_VOID
 Return          : VOS_VOID

  History        :
      1.yangqianhui 00135146       2008-9-8   Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ERABM_RcvRabmEmmRelInd( VOS_VOID )
{
    VOS_UINT32 ulLoop = NAS_ERABM_NULL;

    /*打印进入该函数*/
    NAS_ERABM_INFO_LOG("NAS_ERABM_RcvRabmEmmRelInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ERABM_RcvRabmEmmRelInd_ENUM, LNAS_ENTRY);

    /* 通知CDS RAB RELEASE */
    for (ulLoop = NAS_ERABM_MIN_EPSB_ID; ulLoop <= NAS_ERABM_MAX_EPSB_ID; ulLoop++)
    {
        if (NAS_ERABM_EPSB_ACTIVE == NAS_ERABM_GetEpsbStateInfo(ulLoop))
        {
            /* 给CDS发送CDS_ERABM_RAB_RELEASE_IND */
            NAS_ERABM_SndErabmCdsRabReleaseInd(ulLoop);
        }
    }

    /*释放所有资源,回到开机初始化后的状态*/
    NAS_ERABM_ClearRabmResource();

    if(NAS_ERABM_L_MODE_STATUS_NORMAL != NAS_ERABM_GetLModeStatus())
    {
        return;
    }

    /*根据TFT和承载信息更新IP Filter到硬件加速器*/
    if(PS_FAIL == NAS_ERABM_IpfConfigUlFilter())
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_EsmMsgDistr: IPF Update IP Filter Failed.");
        TLPS_PRINT2LAYER_ERROR(NAS_ERABM_RcvRabmEmmRelInd_ENUM, LNAS_ERABM_IPFUpdateIPFilterFailed);
    }

    /*根据TFT和承载信息更新IP Filter到CDS*/
    if(PS_FAIL == NAS_ERABM_CdsConfigUlFilter())
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_EsmMsgDistr: CDS Update IP Filter Failed.");
        TLPS_PRINT2LAYER_ERROR(NAS_ERABM_RcvRabmEmmRelInd_ENUM, LNAS_ERABM_CDSUpdateIPFilterFailed);
    }
    return;

}

/*****************************************************************************
 Function Name   : NAS_ERABM_RcvRabmEmmRrcConRelInd()
 Description     : RABM模块EMM_ERABM_RRC_CON_REL_IND_STRU消息分发处理
 Input           : VOS_VOID
 Output          : VOS_VOID
 Return          : VOS_VOID

  History        :
      1.lihong 00150010       2009-05-25   Draft Enact
      2.yangfan 00159566      2011-03-28   Modify

*****************************************************************************/
VOS_VOID  NAS_ERABM_RcvRabmEmmRrcConRelInd( EMM_ERABM_RRC_CON_REL_IND_STRU *pRcvMsg )
{
    VOS_UINT32                          ulEpsbId = NAS_ERABM_NULL;

    /*打印进入该函数*/
    NAS_ERABM_INFO_LOG("NAS_ERABM_RcvRabmEmmRrcConRelInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ERABM_RcvRabmEmmRrcConRelInd_ENUM, LNAS_ENTRY);

    NAS_ERABM_TimerStop( NAS_ERABM_WAIT_RB_RESUME_TIMER);

    NAS_ERABM_TimerStop( NAS_ERABM_WAIT_RB_REEST_TIMER);

    NAS_ERABM_SetEmmSrState(NAS_ERABM_SERVICE_STATE_TERMIN);

    /*停止建立等待定时器*/
    NAS_ERABM_TimerStop(NAS_ERABM_WAIT_EPSB_ACT_TIMER);

    /*清除等待承载建立标识 */
    NAS_ERABM_SetWaitEpsBActSign(NAS_ERABM_NOT_WAIT_EPSB_ACT_MSG);


    /* 如果在正常模式下 */
    if (NAS_ERABM_MODE_TYPE_NORMAL == NAS_ERABM_GetMode())
    {
        /* 通知L2释放缓存的数据包 */
        /*APPITF_FreeAllofRabmBuf();*/

        /* 异系统切换成功后，RRC会上报链路释放清DRB，但此场景不能通知CDS清缓存 */
        if (NAS_ERABM_L_MODE_STATUS_NORMAL == NAS_ERABM_GetLModeStatus())
        {
            /* (1)如果当前有上行Pending 标识，即有数据缓存,则给CDS发释放缓存 */
            /* (2)存在已激活DRB,则给CDS发释放缓存 */
            if((EMM_ERABM_UP_DATA_PENDING == NAS_ERABM_GetUpDataPending())
               || ((NAS_ERABM_FAILURE == NAS_ERABM_IsAllActtiveBearerWithoutDrb())
                    && (NAS_ERABM_NULL != NAS_ERABM_GetActiveEpsBearerNum())))
            {
                /* 通知CDS释放缓存的数据包 */
                NAS_ERABM_SndErabmCdsFreeBuffDataInd();

                /* 清除上行数据阻塞标志 */
                NAS_ERABM_SetUpDataPending(EMM_ERABM_NO_UP_DATA_PENDING);
            }
        }

    }
    else  /*环回模式下不清理缓存，保持原上行数据Pending状态*/
    {
        NAS_ERABM_INFO_LOG("NAS_ERABM_RcvRabmEmmRrcConRelInd: Do not release buffer .");
        TLPS_PRINT2LAYER_INFO(NAS_ERABM_RcvRabmEmmRrcConRelInd_ENUM, LNAS_ERABM_NotReleaseBuffer);
    }
    /* 释放原因值为NO RF且DRB个数大于0 */
    if((EMM_ERABM_REL_CAUSE_NO_RF == pRcvMsg->enRelCause)&&(NAS_ERABM_FAILURE== NAS_ERABM_IsAllActtiveBearerWithoutDrb()))
    {   /* 释放原因值为NO_RF时，启动定时器NAS_ERABM_RF_RECOVERY_RB_REEST_TIMER，并向RRM注册通知
           在NAS_ERABM_RF_RECOVERY_RB_REEST_TIMER定时器运行期间，收到RRM有RF资源通知时将发起RB重建，
           使UE和网侧状态保持一致 */
        if(NAS_ERABM_TIMER_STATE_STOPED == NAS_ERABM_IsTimerRunning(NAS_ERABM_RF_RECOVERY_RB_REEST_TIMER))
        {
            NAS_ERABM_TimerStart(   NAS_ERABM_RF_RECOVERY_RB_REEST_TIMER_LENGTH,
                                    NAS_ERABM_RF_RECOVERY_RB_REEST_TIMER,
                                    VOS_FALSE);
            NAS_ERABM_SndRrmRegisterInd(RRM_PS_TASK_TYPE_LTE_PS_BACKGROUND_CALL);
        }
        /* 设置上行DATA PENDING标志 */
        NAS_ERABM_SetUpDataPending(EMM_ERABM_UP_DATA_PENDING);
    }

    /* 释放所有RB */
    for (ulEpsbId = NAS_ERABM_MIN_EPSB_ID; ulEpsbId<= NAS_ERABM_MAX_EPSB_ID; ulEpsbId++)
    {
        NAS_ERABM_RcvRbRelease(ulEpsbId);
    }
    return;
}


/*****************************************************************************
 Function Name   : NAS_ERABM_SndRabmEmmReestReq()
 Description     : 构建和发送EMM_ERABM_REEST_REQ消息
 Input           : VOS_VOID
 Output          : None
 Return          : VOS_VOID
 History         :
      1.yangqianhui 00135146       2008-9-8   Draft Enact
      2.lihong 00150010            2012-12-14 Modify:Emergency

*****************************************************************************/
VOS_VOID NAS_ERABM_SndRabmEmmReestReq
(
    VOS_UINT32                          ulIsEmcType
)
{
    EMM_ERABM_REEST_REQ_STRU    *pstReestReq = VOS_NULL_PTR;

    /*分配空间和检测是否分配成功*/
    pstReestReq = (VOS_VOID*)NAS_ERABM_ALLOC_MSG(
                                        sizeof(EMM_ERABM_REEST_REQ_STRU));
    if ( VOS_NULL_PTR == pstReestReq )
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_SndRabmEmmReestReq:ERROR:Alloc msg fail!" );
        return;
    }

    /*清空*/
    NAS_ERABM_MEM_SET_S(NAS_ERABM_GET_MSG_ENTITY(pstReestReq),
                        NAS_ERABM_GET_MSG_LENGTH(pstReestReq), 
                        NAS_ERABM_NULL,
                        NAS_ERABM_GET_MSG_LENGTH(pstReestReq));

    /*填写消息头*/
    NAS_ERABM_WRITE_EMM_MSG_HEAD(pstReestReq, ID_EMM_ERABM_REEST_REQ);
    pstReestReq->ulIsEmcType = ulIsEmcType;
    /* 调用消息发送函数 */
    NAS_ERABM_SND_MSG(pstReestReq);

}

/*****************************************************************************
 Function Name   : NAS_ERABM_SndRabmEmmDrbSetupInd()
 Description     : 构建和发送EMM_ERABM_DRB_SETUP_IND消息
 Input           : None
 Output          : None
 Return          : VOS_VOID
 History         :
      1.yangqianhui 00135146       2008-9-8   Draft Enact
      2.lihong 00150010            2009-06-23   Modify

*****************************************************************************/
VOS_VOID NAS_ERABM_SndRabmEmmDrbSetupInd( VOS_VOID )
{
    EMM_ERABM_DRB_SETUP_IND_STRU    *pstDrbSetInd = VOS_NULL_PTR;

    /*分配空间和检测是否分配成功*/
    pstDrbSetInd = (VOS_VOID*)NAS_ERABM_ALLOC_MSG(
                                        sizeof(EMM_ERABM_DRB_SETUP_IND_STRU));
    if ( VOS_NULL_PTR == pstDrbSetInd )
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_SndRabmEmmDrbSetupInd:ERROR:Alloc msg fail!" );
        return;
    }

    /*清空*/
    NAS_ERABM_MEM_SET_S(NAS_ERABM_GET_MSG_ENTITY(pstDrbSetInd),
                        NAS_ERABM_GET_MSG_LENGTH(pstDrbSetInd), 
                        NAS_ERABM_NULL,
                        NAS_ERABM_GET_MSG_LENGTH(pstDrbSetInd));

    /*填写消息头*/
    NAS_ERABM_WRITE_EMM_MSG_HEAD(pstDrbSetInd, ID_EMM_ERABM_DRB_SETUP_IND);

    /* 调用消息发送函数*/
    NAS_ERABM_SND_MSG(pstDrbSetInd);

}

/*****************************************************************************
 Function Name   : NAS_ERABM_SndRabmEmmRelReq()
 Description     : 构建和发送EMM_ERABM_REL_REQ消息
 Input           : VOS_VOID
 Output          : None
 Return          : VOS_VOID
 History         :
      1.yangqianhui 00135146       2008-9-8   Draft Enact

*****************************************************************************/
VOS_VOID NAS_ERABM_SndRabmEmmRelReq( VOS_VOID)
{
    EMM_ERABM_REL_REQ_STRU    *pstRelReq  = VOS_NULL_PTR;

    /*分配空间和检测是否分配成功*/
    pstRelReq = (VOS_VOID*)NAS_ERABM_ALLOC_MSG(sizeof(EMM_ERABM_REL_REQ_STRU));
    if ( VOS_NULL_PTR == pstRelReq )
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_SndRabmEmmRelReq:ERROR:Alloc msg fail!" );
        return;
    }

    NAS_ERABM_MEM_SET_S(NAS_ERABM_GET_MSG_ENTITY(pstRelReq), NAS_ERABM_GET_MSG_LENGTH(pstRelReq),NAS_ERABM_NULL,\
                     NAS_ERABM_GET_MSG_LENGTH(pstRelReq));

    /*填写消息头*/
    NAS_ERABM_WRITE_EMM_MSG_HEAD(pstRelReq, ID_EMM_ERABM_REL_REQ);

    /* 调用消息发送函数*/
    NAS_ERABM_SND_MSG(pstRelReq);

}

/*****************************************************************************
 Function Name   : NAS_ERABM_SndRabmEmmSuspendRsp
 Description     : ERABM模块回复ID_EMM_ERABM_SUSPEND_RSP消息
 Input           : EMM_ERABM_RSLT_TYPE_ENUM_UINT32       enRslt
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2011-05-03  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ERABM_SndRabmEmmSuspendRsp
(
    EMM_ERABM_RSLT_TYPE_ENUM_UINT32      enRslt
)
{
    EMM_ERABM_SUSPEND_RSP_STRU          *pstRabmEmmSuspendRsp  = VOS_NULL_PTR;

    /*分配空间并检验分配是否成功*/
    pstRabmEmmSuspendRsp = (VOS_VOID*)NAS_ERABM_ALLOC_MSG(sizeof(EMM_ERABM_SUSPEND_RSP_STRU));

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pstRabmEmmSuspendRsp)
    {
        /*打印异常信息*/
        NAS_ERABM_ERR_LOG("NAS_ERABM_SndRabmEmmSuspendRsp:ERROR:Alloc Msg fail!");
        return ;
    }

    /*清空*/
    NAS_ERABM_MEM_SET_S( NAS_ERABM_GET_MSG_ENTITY(pstRabmEmmSuspendRsp),NAS_ERABM_GET_MSG_LENGTH(pstRabmEmmSuspendRsp), 0, NAS_ERABM_GET_MSG_LENGTH(pstRabmEmmSuspendRsp));

    /*填写消息头*/
    NAS_ERABM_WRITE_EMM_MSG_HEAD(pstRabmEmmSuspendRsp, ID_EMM_ERABM_SUSPEND_RSP);

    /*填写响应结果*/
    pstRabmEmmSuspendRsp->enRslt= enRslt;

    /*调用消息发送函数 */
    NAS_ERABM_SND_MSG(pstRabmEmmSuspendRsp);
}

/*****************************************************************************
 Function Name   : NAS_ERABM_SndRabmEmmResumeRsp
 Description     : ESM模块回复ID_EMM_ERABM_RESUME_RSP消息
 Input           : EMM_ERABM_RSLT_TYPE_ENUM_UINT32       enRslt
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2011-05-03  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ERABM_SndRabmEmmResumeRsp
(
    EMM_ERABM_RSLT_TYPE_ENUM_UINT32      enRslt
)
{
    EMM_ERABM_RESUME_RSP_STRU            *pstRabmEmmResumeRsp  = VOS_NULL_PTR;

    /*分配空间并检验分配是否成功*/
    pstRabmEmmResumeRsp = (VOS_VOID*)NAS_ERABM_ALLOC_MSG(sizeof(EMM_ERABM_RESUME_RSP_STRU));

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pstRabmEmmResumeRsp)
    {
        /*打印异常信息*/
        NAS_ERABM_ERR_LOG("NAS_ERABM_SndRabmEmmResumeRsp:ERROR:Alloc Msg fail!");
        return ;
    }

    /*清空*/
    NAS_ERABM_MEM_SET_S( NAS_ERABM_GET_MSG_ENTITY(pstRabmEmmResumeRsp),
                        NAS_ERABM_GET_MSG_LENGTH(pstRabmEmmResumeRsp), 
                        0, 
                        NAS_ERABM_GET_MSG_LENGTH(pstRabmEmmResumeRsp));

    /*填写消息头*/
    NAS_ERABM_WRITE_EMM_MSG_HEAD(pstRabmEmmResumeRsp, ID_EMM_ERABM_RESUME_RSP);

    /*填写响应结果*/
    pstRabmEmmResumeRsp->enRslt= enRslt;

    /*调用消息发送函数 */
    NAS_ERABM_SND_MSG(pstRabmEmmResumeRsp);
}

/*****************************************************************************
 Function Name   : NAS_ERABM_IsDataPending
 Description     : 提供给MM调用，判断ESM是否有上行数据阻塞:直接返回标志g_enERabmUlDataPending
 Input           : VOS_VOID
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421   2011-2-12  Draft Enact

*****************************************************************************/
EMM_ERABM_UP_DATA_PENDING_ENUM_UINT32 NAS_ERABM_IsDataPending( VOS_VOID )
{
    /* 根据CDS记录是否有上行缓存数据，以及RABM记录是否有上行数据PENDING共同决定 */
    return (EMM_ERABM_UP_DATA_PENDING_ENUM_UINT32)(CDS_IsPsDataAvail()||NAS_ERABM_GetUpDataPending());
}

/*****************************************************************************
 Function Name   : NAS_ERABM_RcvRabmEmmSuspendInd
 Description     : ERABM模块收到ID_EMM_ERABM_SUSPEND_IND处理函数
 Input           : EMM_ERABM_SUSPEND_IND_STRU *pRcvMsg
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010            2011-05-03      Draft Enact
*****************************************************************************/
VOS_VOID  NAS_ERABM_RcvRabmEmmSuspendInd(const EMM_ERABM_SUSPEND_IND_STRU *pRcvMsg )
{
    VOS_UINT32                          ulEpsbId        = NAS_ERABM_NULL;
    VOS_UINT8                           ucTimerIndex    = NAS_ERABM_NULL;

    /* 设置状态为挂起态 */
    NAS_ERABM_SetLModeStatus(NAS_ERABM_L_MODE_STATUS_SUSPENDED);
    if(NAS_ERABM_TIMER_STATE_RUNNING == NAS_ERABM_IsTimerRunning(NAS_ERABM_RF_RECOVERY_RB_REEST_TIMER))
    {
        /* 去注册RF资源通知 */
        NAS_ERABM_SndRrmDeRegisterInd(RRM_PS_TASK_TYPE_LTE_PS_BACKGROUND_CALL);
        /* 停止定时器NAS_ERABM_RF_RECOVERY_RB_REEST_TIMER */
        NAS_ERABM_TimerStop(NAS_ERABM_RF_RECOVERY_RB_REEST_TIMER);
    }

    /* 停止定时器 */
    for (ucTimerIndex = 0; ucTimerIndex < NAS_NAS_ERABM_TIMER_NAME_BUTT; ucTimerIndex++)
    {
        NAS_ERABM_TimerStop(ucTimerIndex);
    }
    /* 如果是切换和CCO类型的挂起，则不删除DRB信息，只将DRB的状态设为NAS_ERABM_RB_SUSPENDED，
       因为L-GU切换或者CCO失败回退成功时，RRC并不上报LRRC_LRABM_RAB_IND消息，而
       只上报LRRC_LRABM_STATUS_IND消息恢复数传；其他类型的挂起，则删除DRB信息*/
    if ((EMM_ERABM_SYS_CHNG_TYPE_HO == pRcvMsg->enSysChngType)
         || (EMM_ERABM_SYS_CHNG_TYPE_CCO == pRcvMsg->enSysChngType))
    {
        /* 将DRB状态设为NAS_ERABM_RB_SUSPENDED */
        for (ulEpsbId = NAS_ERABM_MIN_EPSB_ID; ulEpsbId<= NAS_ERABM_MAX_EPSB_ID; ulEpsbId++)
        {
            /* 添加保护,防止出现RbState被误设置为挂起态 */
            if(NAS_ERABM_ILL_RB_ID != NAS_ERABM_GetEpsbRbIdInfo(ulEpsbId))
            {
                NAS_ERABM_SetRbStateInfo(ulEpsbId, NAS_ERABM_RB_SUSPENDED);
            }
        }
    }


    /*清除等待EPS承载激活标识*/
    NAS_ERABM_SetWaitEpsBActSign(NAS_ERABM_NOT_WAIT_EPSB_ACT_MSG);

    /*SERVICE流程停止*/
    NAS_ERABM_SetEmmSrState(NAS_ERABM_SERVICE_STATE_TERMIN);

    /* 通知L2释放缓存的数据包 */
    /*APPITF_FreeAllofRabmBuf();*/

    /* 清除上行数据阻塞标志*/
    NAS_ERABM_SetUpDataPending(EMM_ERABM_NO_UP_DATA_PENDING);

    /* 通知ETC挂起 */
    NAS_ERABM_SndRabmTcSuspendInd();

    /* 回复EMM挂起成功 */
    NAS_ERABM_SndRabmEmmSuspendRsp(EMM_ERABM_RSLT_TYPE_SUCC);
}

/*****************************************************************************
 Function Name   : NAS_ERABM_RcvRabmEmmResumeInd
 Description     : SM模块收到ID_EMM_ERABM_RESUME_IND处理函数
 Input           : EMM_ERABM_RESUME_IND_STRU *pRcvMsg
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010            2011-05-03      Draft Enact
*****************************************************************************/
VOS_VOID  NAS_ERABM_RcvRabmEmmResumeInd(const EMM_ERABM_RESUME_IND_STRU *pRcvMsg )
{
    (VOS_VOID)pRcvMsg;

    /* 设置状态为正常态 */
    NAS_ERABM_SetLModeStatus(NAS_ERABM_L_MODE_STATUS_NORMAL);

    /*根据TFT和承载信息更新IP Filter到硬件加速器*/
    if(PS_FAIL == NAS_ERABM_IpfConfigUlFilter())
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_EsmMsgDistr: IPF Update IP Filter Failed.");
        TLPS_PRINT2LAYER_ERROR(NAS_ERABM_RcvRabmEmmResumeInd_ENUM, LNAS_ERABM_IPFUpdateIPFilterFailed);
    }

    /*根据TFT和承载信息更新IP Filter到CDS*/
    if(PS_FAIL == NAS_ERABM_CdsConfigUlFilter())
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_EsmMsgDistr: CDS Update IP Filter Failed.");
        TLPS_PRINT2LAYER_ERROR(NAS_ERABM_RcvRabmEmmResumeInd_ENUM, LNAS_ERABM_CDSUpdateIPFilterFailed);
    }

    /* 通知ETC解挂 */
    NAS_ERABM_SndRabmTcResumeInd();

    /* 回复EMM解挂成功 */
    NAS_ERABM_SndRabmEmmResumeRsp(EMM_ERABM_RSLT_TYPE_SUCC);
}
/*****************************************************************************
 Function Name   : NAS_ERABM_SndRrmRegisterInd
 Description     : 向RRM注册RF资源通知,TASKType要与去注册时类型一致
 Input           : RRM_PS_TASK_TYPE_ENUM_UINT16       enTaskType
 Output          : None
 Return          : None

 History         :
    1.leixiantiao            2015-01-06      Draft Enact
*****************************************************************************/
VOS_VOID NAS_ERABM_SndRrmRegisterInd(
    RRM_PS_TASK_TYPE_ENUM_UINT16       enTaskType
)
{

    /* 定义原语类型指针 */
    PS_RRM_REGISTER_IND_STRU            *pstMsg    = VOS_NULL_PTR;

    pstMsg = (PS_RRM_REGISTER_IND_STRU *)NAS_ERABM_ALLOC_MSG(sizeof(PS_RRM_REGISTER_IND_STRU));
    /* 内存申请失败 */
    if (VOS_NULL_PTR == pstMsg)
    {
        /* 返回失败 */
        return;
    }

    NAS_ERABM_MEM_SET_S(pstMsg,sizeof(PS_RRM_REGISTER_IND_STRU), NAS_ERABM_NULL,sizeof(PS_RRM_REGISTER_IND_STRU));

    /*填写消息头*/
    pstMsg->stMsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid         = PS_PID_RABM;
    pstMsg->stMsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid       = UEPS_PID_RRM;
    pstMsg->stMsgHeader.ulLength            = sizeof(PS_RRM_REGISTER_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName           = ID_PS_RRM_REGISTER_IND;

    pstMsg->enModemId                       = MODEM_ID_0;
    pstMsg->enTaskType                      = enTaskType;
    pstMsg->enRatType                       = VOS_RATMODE_LTE;

    /*发送消息*/
    NAS_ERABM_SND_MSG(pstMsg);
    return;
}
/*****************************************************************************
 Function Name   : NAS_ERABM_SndRrmDeRegisterInd
 Description     : 给RRM发送去注册RF资源通知,TASKType要与注册时类型一致
 Input           : RRM_PS_TASK_TYPE_ENUM_UINT16       enTaskType
 Output          : None
 Return          : None

 History         :
    1.leixiantiao            2015-01-06      Draft Enact
*****************************************************************************/
VOS_VOID NAS_ERABM_SndRrmDeRegisterInd
(
    RRM_PS_TASK_TYPE_ENUM_UINT16       enTaskType
)
{

    /* 定义原语类型指针 */
    PS_RRM_DEREGISTER_IND_STRU            *pstMsg    = VOS_NULL_PTR;

    pstMsg = (PS_RRM_DEREGISTER_IND_STRU *)NAS_ERABM_ALLOC_MSG(sizeof(PS_RRM_DEREGISTER_IND_STRU));
    /* 内存申请失败 */
    if (VOS_NULL_PTR == pstMsg)
    {
        /* 返回失败 */
        return;
    }

    NAS_ERABM_MEM_SET_S(pstMsg,sizeof(PS_RRM_DEREGISTER_IND_STRU), NAS_ERABM_NULL,sizeof(PS_RRM_DEREGISTER_IND_STRU));

    /*填写消息头*/
    pstMsg->stMsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid         = PS_PID_RABM;
    pstMsg->stMsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid       = UEPS_PID_RRM;
    pstMsg->stMsgHeader.ulLength            = sizeof(PS_RRM_DEREGISTER_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName           = ID_PS_RRM_DEREGISTER_IND;

    pstMsg->enModemId                       = MODEM_ID_0;
    pstMsg->enTaskType                      = enTaskType;
    pstMsg->enRatType                       = VOS_RATMODE_LTE;

    /*发送消息*/
    NAS_ERABM_SND_MSG(pstMsg);
    return;
}

/*lint +e961*/
/*lint +e960*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

