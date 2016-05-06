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
#include "EmmTcInterface.h"
#include "NasEmmAttDetInclude.h"

#include "ImsaIntraInterface.h"
#if (FEATURE_LPP == FEATURE_ON)
#include "NasEmmLppMsgProc.h"
#include "EmmLppInterface.h"
#endif

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASEMMSERVICESERREQ_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASEMMSERVICESERREQ_C
/*lint +e767*/



/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*******************************************************************************
  Module   :
  Function : NAS_EMM_MsRegSsLimitedSrvMsgRabmReestReq
  Input    : ulMsgId------------------消息ID
             pMsgStru-----------------消息指针
  Output   :
  NOTE     : REG+LIMIT_SERVICE态下收到RABM的建链请求
  Return   : VOS_UINT32
  History  :
    1. lihong 00150010      2012.12.14  新规作成

*******************************************************************************/
VOS_UINT32 NAS_EMM_MsRegSsLimitedSrvMsgRabmReestReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    static VOS_UINT32                   ulMsgCnt    = NAS_EMM_NULL;
    EMM_ERABM_REEST_REQ_STRU           *pstReestReq = NAS_EMM_NULL_PTR;

    (VOS_VOID)ulMsgId;

    NAS_EMM_SER_LOG_INFO( "NAS_EMM_MsRegSsLimitedSrvMsgRabmReestReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsLimitedSrvMsgRabmReestReq_ENUM,LNAS_ENTRY);

    pstReestReq = (EMM_ERABM_REEST_REQ_STRU *)pMsgStru;

    /* 如果不是紧急业务，则丢弃 */
    if (VOS_TRUE != pstReestReq->ulIsEmcType)
    {
        NAS_EMM_SER_LOG_WARN( "NAS_EMM_MsRegSsLimitedSrvMsgRabmReestReq:Not EMC!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsLimitedSrvMsgRabmReestReq_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_LMM_MSG_DISCARD;
    }

    /*如果处于连接态，打印出错信息*/
    if (NAS_EMM_CONN_IDLE != NAS_EMM_GetConnState())
    {
        NAS_EMM_SER_LOG_WARN( "NAS_EMM_MsRegSsLimitedSrvMsgRabmReestReq: CONN.");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsLimitedSrvMsgRabmReestReq_ENUM,LNAS_FUNCTION_LABEL1);
        ulMsgCnt++;

        /* 做保护,防止EMM与RABM维护的RRC链路状态不一致,导致UE长时间无法发起建链*/
        /* 连续2次收到ERABM的建链请求时,将RRC链路状态设置为IDLE态*/
        if (NAS_EMM_DISCARD_ERABM_RESET_REQ_MAX_CNT > ulMsgCnt)
        {
            return NAS_LMM_MSG_HANDLED;
        }

        /*更新连接状态*/
        NAS_EMM_MrrcChangeRrcStatusToIdle();
    }
    ulMsgCnt = NAS_EMM_NULL;

    NAS_EMM_SER_RcvRabmReestReq(pstReestReq->ulIsEmcType);

    return NAS_LMM_MSG_HANDLED;
}
/*******************************************************************************
  Module   :
  Function : NAS_EMM_MsRegSsNormalMsgRabmReestReq
  Input    :
  Output   :
  NOTE     :
  Return   :
  History  :
    1. Zhouyan 00125190      2008.09.10  新规作成
    2. Zhengjunyan 00148421  2010.07.16   MOD:如果有未完成的TAU收到数传请求，不发起SER
                                           触发TAU流程,携带"Active"标志
    3. sunbing      49683    2010.09.07  修改是否发起TAU的判断条件，只有在参数变更的TAU没有成功的场景下，才发起TAU
    4. lihong 00150010       2012.12.14  Modify:Emergency

*******************************************************************************/
VOS_UINT32 NAS_EMM_MsRegSsNormalMsgRabmReestReq(VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru
                               )
{
    VOS_UINT32                          ulRslt      = NAS_EMM_FAIL;
    static VOS_UINT32                   ulMsgCnt    = NAS_EMM_NULL;
    EMM_ERABM_REEST_REQ_STRU           *pstReestReq = NAS_EMM_NULL_PTR;

    (VOS_VOID)ulMsgId;

    NAS_EMM_SER_LOG_INFO( "Nas_Emm_MsRegSsNormalMsgRabmReestReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsNormalMsgRabmReestReq_ENUM,LNAS_ENTRY);

    /*检查当前状态和输入指针*/
    ulRslt = NAS_EMM_SER_CHKFSMStateMsgp(EMM_MS_REG,EMM_SS_REG_NORMAL_SERVICE,pMsgStru);
    if ( NAS_EMM_SUCC != ulRslt )
    {
        NAS_EMM_SER_LOG_WARN( "NAS_EMM_TAUSER_CHKFSMStateMsgp ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsNormalMsgRabmReestReq_ENUM,LNAS_ERROR);
         return NAS_LMM_MSG_HANDLED;
    }

    /*如果处于连接态，打印出错信息*/
    if (NAS_EMM_CONN_IDLE != NAS_EMM_GetConnState())
    {
        NAS_EMM_SER_LOG_WARN( "NAS_EMM_MsRegSsNormalMsgRabmReestReq: CONN.");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsNormalMsgRabmReestReq_ENUM,LNAS_FUNCTION_LABEL1);
        ulMsgCnt++;

        /* 做保护,防止EMM与RABM维护的RRC链路状态不一致,导致UE长时间无法发起建链*/
        /* 连续2次收到ERABM的建链请求时,将RRC链路状态设置为IDLE态*/
        if (NAS_EMM_DISCARD_ERABM_RESET_REQ_MAX_CNT > ulMsgCnt)
        {
            return NAS_LMM_MSG_HANDLED;
        }

        /*更新连接状态*/
        NAS_EMM_MrrcChangeRrcStatusToIdle();
    }
    ulMsgCnt = NAS_EMM_NULL;

    if((NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_CSFB_DELAY))
        &&(VOS_TRUE == NAS_EMM_SER_IsCsfbProcedure()))
    {
        NAS_EMM_SER_LOG_INFO( "NAS_EMM_MsRegSsNormalMsgRabmReestReq: Msg discard, CSFB delay timer is running.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsNormalMsgRabmReestReq_ENUM,LNAS_FUNCTION_LABEL2);
        return NAS_LMM_MSG_HANDLED;
    }

    pstReestReq = (EMM_ERABM_REEST_REQ_STRU *)pMsgStru;
    NAS_EMM_SER_RcvRabmReestReq(pstReestReq->ulIsEmcType);
    return NAS_LMM_MSG_HANDLED;

}

/*****************************************************************************
 Function Name   : NAS_EMM_MsRegSsRegAttemptUpdateMmMsgRabmReestReq
 Description     : REG+REG_ATTEMPTING_TO_UPDATE_MM状态下收到RABM消息处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2011-7-12     Draft Enact
    2.lihong00150010      2011-11-17    Modify
    3. lihong 00150010    2012.12.14    Modify:Emergency

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegSsRegAttemptUpdateMmMsgRabmReestReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    VOS_UINT32                          ulRslt      = NAS_EMM_FAIL;
    static VOS_UINT32                   ulMsgCnt    = NAS_EMM_NULL;
    EMM_ERABM_REEST_REQ_STRU           *pstReestReq = NAS_EMM_NULL_PTR;

    (VOS_VOID)ulMsgId;

    NAS_EMM_SER_LOG_INFO( "NAS_EMM_MsRegSsRegAttemptUpdateMmMsgRabmReestReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgRabmReestReq_ENUM,LNAS_ENTRY);

    /*检查当前状态和输入指针*/
    ulRslt = NAS_EMM_SER_CHKFSMStateMsgp(EMM_MS_REG,
                                        EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM,
                                        pMsgStru);
    if ( NAS_EMM_SUCC != ulRslt )
    {
        NAS_EMM_SER_LOG_WARN( "NAS_EMM_TAUSER_CHKFSMStateMsgp ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgRabmReestReq_ENUM,LNAS_ERROR);
         return NAS_LMM_MSG_HANDLED;
    }

    /*如果处于连接态，打印出错信息*/
    if (NAS_EMM_CONN_IDLE != NAS_EMM_GetConnState())
    {
        NAS_EMM_SER_LOG_WARN( "NAS_EMM_MsRegSsRegAttemptUpdateMmMsgRabmReestReq: CONN.");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgRabmReestReq_ENUM,LNAS_FUNCTION_LABEL1);
        ulMsgCnt++;

        /* 做保护,防止EMM与RABM维护的RRC链路状态不一致,导致UE长时间无法发起建链*/
        /* 连续2次收到ERABM的建链请求时,将RRC链路状态设置为IDLE态*/
        if (NAS_EMM_DISCARD_ERABM_RESET_REQ_MAX_CNT > ulMsgCnt)
        {
            return NAS_LMM_MSG_HANDLED;
        }

        /*更新连接状态*/
        NAS_EMM_MrrcChangeRrcStatusToIdle();
    }
    ulMsgCnt = NAS_EMM_NULL;

    /* 记录UPDATE_MM标识 */
    /*NAS_LMM_SetEmmInfoUpdateMmFlag(NAS_EMM_UPDATE_MM_FLAG_VALID);*/
    pstReestReq = (EMM_ERABM_REEST_REQ_STRU *)pMsgStru;
    NAS_EMM_SER_RcvRabmReestReq(pstReestReq->ulIsEmcType);

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsRegSsLimitedSrvMsgRabmRelReq
 Description     : Reg.Limit_Service状态下收到RABM数传异常，释放连接
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2012-12-29  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegSsLimitedSrvMsgRabmRelReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    NAS_EMM_SER_LOG_INFO("NAS_EMM_MsRegSsLimitedSrvMsgRabmRelReq entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsLimitedSrvMsgRabmRelReq_ENUM,LNAS_ENTRY);
    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;

    /*如果是释放过程中，则直接丢弃*/
    if(NAS_EMM_CONN_RELEASING == NAS_EMM_GetConnState())
    {
        return NAS_LMM_MSG_HANDLED;
    }

    if(NAS_LMM_TIMER_RUNNING == NAS_LMM_IsStaTimerRunning(TI_NAS_EMM_STATE_T3440))
    {
        NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_T3440);

        /*启动定时器TI_NAS_EMM_MRRC_WAIT_RRC_REL*/
        NAS_LMM_StartStateTimer(TI_NAS_EMM_MRRC_WAIT_RRC_REL_CNF);

        /*向MRRC发送NAS_EMM_MRRC_REL_REQ消息*/
        NAS_EMM_SndRrcRelReq(NAS_LMM_NOT_BARRED);

        /* 设置连接状态为释放过程中 */
        NAS_EMM_SetConnState(NAS_EMM_CONN_RELEASING);

        return NAS_LMM_MSG_HANDLED;
    }


    /*向MRRC发送NAS_EMM_MRRC_REL_REQ消息*/
    NAS_EMM_RelReq(                     NAS_LMM_NOT_BARRED);

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsRegSsNormalMsgRabmRelReq
 Description     : Reg.Normal_Service状态下收到RABM数传异常，释放连接
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunbing      2010-12-29  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegSsNormalMsgRabmRelReq( VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru )
{
    NAS_EMM_SER_LOG_INFO("NAS_EMM_MsRegSsNormalMsgRabmRelReq entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsNormalMsgRabmRelReq_ENUM,LNAS_ENTRY);
    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;

    /*如果是释放过程中，则直接丢弃*/
    if(NAS_EMM_CONN_RELEASING == NAS_EMM_GetConnState())
    {
        return NAS_LMM_MSG_HANDLED;
    }

    if(NAS_LMM_TIMER_RUNNING == NAS_LMM_IsStaTimerRunning(TI_NAS_EMM_STATE_T3440))
    {
        NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_T3440);

        /*启动定时器TI_NAS_EMM_MRRC_WAIT_RRC_REL*/
        NAS_LMM_StartStateTimer(TI_NAS_EMM_MRRC_WAIT_RRC_REL_CNF);

        /*向MRRC发送NAS_EMM_MRRC_REL_REQ消息*/
        NAS_EMM_SndRrcRelReq(NAS_LMM_NOT_BARRED);

        /* 设置连接状态为释放过程中 */
        NAS_EMM_SetConnState(NAS_EMM_CONN_RELEASING);

        return NAS_LMM_MSG_HANDLED;
    }

    /*向MRRC发送NAS_EMM_MRRC_REL_REQ消息*/
    NAS_EMM_RelReq(                     NAS_LMM_NOT_BARRED);

    return NAS_LMM_MSG_HANDLED;

}

/*****************************************************************************
 Function Name   : NAS_EMM_MsRegSsRegAttemptUpdateMmMsgRabmRelReq
 Description     : 处理在REG+ATTEMPT_TO_UPDATE_MM状态下收到RABM的释放链路请求
 Input           : ulMsgId-------------------------消息ID
                   pMsgStru------------------------消息指针
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2011-11-17  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegSsRegAttemptUpdateMmMsgRabmRelReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    NAS_EMM_SER_LOG_INFO("NAS_EMM_MsRegSsRegAttemptUpdateMmMsgRabmRelReq entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgRabmRelReq_ENUM,LNAS_ENTRY);

    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;

    /*如果是释放过程中，则直接丢弃*/
    if(NAS_EMM_CONN_RELEASING == NAS_EMM_GetConnState())
    {
        return NAS_LMM_MSG_HANDLED;
    }

    if(NAS_LMM_TIMER_RUNNING == NAS_LMM_IsStaTimerRunning(TI_NAS_EMM_STATE_T3440))
    {
        NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_T3440);

        /*启动定时器TI_NAS_EMM_MRRC_WAIT_RRC_REL*/
        NAS_LMM_StartStateTimer(TI_NAS_EMM_MRRC_WAIT_RRC_REL_CNF);

        /*向MRRC发送NAS_EMM_MRRC_REL_REQ消息*/
        NAS_EMM_SndRrcRelReq(NAS_LMM_NOT_BARRED);

        /* 设置连接状态为释放过程中 */
        NAS_EMM_SetConnState(NAS_EMM_CONN_RELEASING);

        return NAS_LMM_MSG_HANDLED;
    }

    /*向MRRC发送NAS_EMM_MRRC_REL_REQ消息*/
    NAS_EMM_RelReq(                     NAS_LMM_NOT_BARRED);

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsRegInitSsWaitCnAttachCnfMsgTcDataReq
 Description     : 在住状态为EMM_RS_REG_INIT，子状态为EMM_SS_ATTACH_WAIT_CN_ATTACH_CNF
                   下收到ID_EMM_ETC_DATA_REQ消息
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2009-10-16  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegInitSsWaitCnAttachCnfMsgTcDataReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    VOS_UINT32                          ulRslt;

    (VOS_VOID)ulMsgId;

    NAS_EMM_SER_LOG_INFO("NAS_EMM_MsRegInitSsWaitCnAttachCnfMsgTcDataReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegInitSsWaitCnAttachCnfMsgTcDataReq_ENUM,LNAS_ENTRY);

    ulRslt = NAS_EMM_SER_CHKFSMStateMsgp(EMM_MS_REG_INIT,EMM_SS_ATTACH_WAIT_CN_ATTACH_CNF,pMsgStru);
    if ( NAS_EMM_SUCC != ulRslt )
    {
        /* 打印异常 */
        NAS_EMM_SER_LOG_WARN( "NAS_EMM_MsRegInitSsWaitCnAttachCnfMsgTcDataReq ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegInitSsWaitCnAttachCnfMsgTcDataReq_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    NAS_EMM_SER_SendMrrcDataReq_Tcdata((EMM_ETC_DATA_REQ_STRU *)pMsgStru);

    return NAS_LMM_MSG_HANDLED;
}


/*****************************************************************************
 Function Name   : NAS_EMM_MsRegSsNormalMsgTcDataReq
 Description     : 在住状态为EMM_RS_REG，子状态为EMM_SS_NORMAL_SERVICE
                   下收到ID_EMM_ETC_DATA_REQ消息
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2009-10-16  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegSsNormalMsgTcDataReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    VOS_UINT32                      ulRslt              = NAS_EMM_FAIL;

    (VOS_VOID)ulMsgId;

    NAS_EMM_SER_LOG_INFO("NAS_EMM_MsRegSsNormalMsgTcDataReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsNormalMsgTcDataReq_ENUM,LNAS_ENTRY);

    /* 函数输入指针参数检查, 状态匹配检查,若不匹配,退出*/
    ulRslt = NAS_EMM_SER_CHKFSMStateMsgp(EMM_MS_REG,EMM_SS_REG_NORMAL_SERVICE,pMsgStru);
    if ( NAS_EMM_SUCC != ulRslt )
    {
        NAS_EMM_SER_LOG_WARN( "NAS_EMM_TAUSER_CHKFSMStateMsgp ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsNormalMsgTcDataReq_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    /*如果是释放过程中，则直接丢弃*/
    if(NAS_EMM_CONN_RELEASING == NAS_EMM_GetConnState())
    {
        return NAS_LMM_MSG_HANDLED;
    }

    if(NAS_LMM_TIMER_RUNNING == NAS_LMM_IsStaTimerRunning(TI_NAS_EMM_STATE_T3440))
    {
        /* 透传ETC消息 */
         NAS_EMM_SER_SendMrrcDataReq_Tcdata((EMM_ETC_DATA_REQ_STRU *)pMsgStru);
        return NAS_LMM_MSG_HANDLED;
    }


    /*CONN模式下，转发TC消息；IDLE模式下，打印出错信息*/
    if((NAS_EMM_CONN_SIG == NAS_EMM_GetConnState()) ||
        (NAS_EMM_CONN_DATA == NAS_EMM_GetConnState()))
    {
        NAS_EMM_SER_SendMrrcDataReq_Tcdata((EMM_ETC_DATA_REQ_STRU *)pMsgStru);
    }
    else
    {
        NAS_EMM_SER_LOG_WARN( "NAS_EMM_MsRegSsNormalMsgTcDataReq:Warning:RRC connection is not Exist!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsNormalMsgTcDataReq_ENUM,LNAS_FUNCTION_LABEL1);
    }

    return NAS_LMM_MSG_HANDLED;

}

/*****************************************************************************
 Function Name   : NAS_EMM_MsRegSsRegAttemptUpdateMmMsgTcDataReq
 Description     : 在住状态为EMM_RS_REG，子状态为EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM
                   下收到ID_EMM_ETC_DATA_REQ消息
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2011-7-12  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegSsRegAttemptUpdateMmMsgTcDataReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    VOS_UINT32                      ulRslt              = NAS_EMM_FAIL;

    (VOS_VOID)ulMsgId;

    NAS_EMM_SER_LOG_INFO("NAS_EMM_MsRegSsRegAttemptUpdateMmMsgTcDataReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgTcDataReq_ENUM,LNAS_ENTRY);

    /* 函数输入指针参数检查, 状态匹配检查,若不匹配,退出*/
    ulRslt = NAS_EMM_SER_CHKFSMStateMsgp(EMM_MS_REG,
                                        EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM,
                                        pMsgStru);
    if ( NAS_EMM_SUCC != ulRslt )
    {
        NAS_EMM_SER_LOG_WARN( "NAS_EMM_TAUSER_CHKFSMStateMsgp ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgTcDataReq_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    /*如果是释放过程中，则直接丢弃*/
    if(NAS_EMM_CONN_RELEASING == NAS_EMM_GetConnState())
    {
        return NAS_LMM_MSG_HANDLED;
    }

    if(NAS_LMM_TIMER_RUNNING == NAS_LMM_IsStaTimerRunning(TI_NAS_EMM_STATE_T3440))
    {
        /* 透传ETC消息 */
         NAS_EMM_SER_SendMrrcDataReq_Tcdata((EMM_ETC_DATA_REQ_STRU *)pMsgStru);
        return NAS_LMM_MSG_HANDLED;
    }


    /*CONN模式下，转发TC消息；IDLE模式下，打印出错信息*/
    if((NAS_EMM_CONN_SIG == NAS_EMM_GetConnState()) ||
        (NAS_EMM_CONN_DATA == NAS_EMM_GetConnState()))
    {
        NAS_EMM_SER_SendMrrcDataReq_Tcdata((EMM_ETC_DATA_REQ_STRU *)pMsgStru);
    }
    else
    {
        NAS_EMM_SER_LOG_WARN( "NAS_EMM_MsRegSsRegAttemptUpdateMmMsgTcDataReq:Warning:RRC connection is not Exist!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgTcDataReq_ENUM,LNAS_ERROR);
    }

    return NAS_LMM_MSG_HANDLED;
}


/*******************************************************************************
  Module   :
  Function : NAS_EMM_MsRegInitSsWaitCnAttachCnfMsgEsmDataReq
  Input    :
  Output   :
  NOTE     :
  Return   :
  History  :
    1.  lihong00150010  2009-09-25  新规作成
*******************************************************************************/
VOS_UINT32 NAS_EMM_MsRegInitSsWaitCnAttachCnfMsgEsmDataReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    VOS_UINT32                          ulRslt;
    EMM_ESM_DATA_REQ_STRU              *pstEsmDataReq = (EMM_ESM_DATA_REQ_STRU*)pMsgStru;

    (VOS_VOID)ulMsgId;

    NAS_EMM_SER_LOG_INFO("NAS_EMM_MsRegInitSsWaitCnAttachCnfMsgEsmDataReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegInitSsWaitCnAttachCnfMsgEsmDataReq_ENUM,LNAS_ENTRY);

    ulRslt = NAS_EMM_SER_CHKFSMStateMsgp(EMM_MS_REG_INIT,EMM_SS_ATTACH_WAIT_CN_ATTACH_CNF,pMsgStru);
    if ( NAS_EMM_SUCC != ulRslt )
    {
        /* 打印异常 */
        NAS_EMM_SER_LOG_WARN( "NAS_EMM_MsRegInitSsWaitCnAttachCnfMsgEsmDataReq ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegInitSsWaitCnAttachCnfMsgEsmDataReq_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    NAS_EMM_SER_SendMrrcDataReq_ESMdata(&pstEsmDataReq->stEsmMsg, pstEsmDataReq->ulOpId);

    return NAS_LMM_MSG_HANDLED;
}

/*******************************************************************************
  Module   :
  Function : NAS_EMM_MsRegSsNormalMsgMmIntraSERReq
  Input    :
  Output   :
  NOTE     :
  Return   :
  History  :
    1. Zhouyan 00125190      2008.09.10  新规作成
    2. zhengjunyan 00148421  2010.07.30  添加判断是否有未完成的TAU
    3. sunbing      49683    2010.09.07  修改是否发起TAU的判断条件，只有在参数变更的TAU没有成功的场景下，才发起TAU
*******************************************************************************/
VOS_UINT32 NAS_EMM_MsRegSsNormalMsgEsmDataReq(VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru
                               )
{
    VOS_UINT32                          ulRslt          = NAS_EMM_FAIL;
    EMM_ESM_DATA_REQ_STRU              *pstEsmDataReq   = (EMM_ESM_DATA_REQ_STRU*)pMsgStru;

    (VOS_VOID)ulMsgId;

    NAS_EMM_SER_LOG_INFO("NAS_EMM_MsRegSsNormalMsgEsmDataReq entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsNormalMsgEsmDataReq_ENUM,LNAS_ENTRY);

    /* 函数输入指针参数检查, 状态匹配检查,若不匹配,退出*/
    ulRslt = NAS_EMM_SER_CHKFSMStateMsgp(EMM_MS_REG,EMM_SS_REG_NORMAL_SERVICE,pMsgStru);
    if ( NAS_EMM_SUCC != ulRslt )
    {
        NAS_EMM_SER_LOG_WARN( "NAS_EMM_TAUSER_CHKFSMStateMsgp ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsNormalMsgEsmDataReq_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    if (VOS_TRUE == pstEsmDataReq->ulIsEmcType)
    {
        NAS_LMM_SetEmmInfoIsEmerPndEsting(VOS_TRUE);
        /* 解决LRRC REL搜小区驻留上报系统消息前收到ESM紧急承载建立请求，由于空口发送失败，本地detach,发起紧急ATTACH问题
           方案:先高优先级缓存，等到收到LRRC系统消息后处理*/
        if((NAS_EMM_CONN_WAIT_SYS_INFO == NAS_EMM_GetConnState())
            ||(NAS_EMM_CONN_RELEASING == NAS_EMM_GetConnState()))
        {
            return NAS_LMM_STORE_HIGH_PRIO_MSG;
        }
    }

    if((NAS_EMM_CONN_WAIT_SYS_INFO == NAS_EMM_GetConnState())
        ||(NAS_EMM_CONN_RELEASING == NAS_EMM_GetConnState()))
    {
        return NAS_LMM_STORE_HIGH_PRIO_MSG;
    }


    if(NAS_LMM_TIMER_RUNNING == NAS_LMM_IsStaTimerRunning(TI_NAS_EMM_STATE_T3440))
    {
        /* 如果是紧急类型的，则停止T3440定时器，主动发链路释放 */
        if (VOS_TRUE == pstEsmDataReq->ulIsEmcType)
        {
            NAS_LMM_SetEmmInfoIsEmerPndEsting(VOS_TRUE);
            NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_T3440);

            /*启动定时器TI_NAS_EMM_MRRC_WAIT_RRC_REL*/
            NAS_LMM_StartStateTimer(TI_NAS_EMM_MRRC_WAIT_RRC_REL_CNF);

            /*向MRRC发送NAS_EMM_MRRC_REL_REQ消息*/
            NAS_EMM_SndRrcRelReq(NAS_LMM_NOT_BARRED);

            /* 设置连接状态为释放过程中 */
            NAS_EMM_SetConnState(NAS_EMM_CONN_RELEASING);

        }
        return NAS_LMM_STORE_HIGH_PRIO_MSG;

    }


    /*CONN态，转发ESM消息*/
    if((NAS_EMM_CONN_SIG == NAS_EMM_GetConnState()) ||
        (NAS_EMM_CONN_DATA == NAS_EMM_GetConnState()))
    {
        NAS_EMM_SER_SendMrrcDataReq_ESMdata(&pstEsmDataReq->stEsmMsg, pstEsmDataReq->ulOpId);
        return NAS_LMM_MSG_HANDLED;
    }

    if((NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_CSFB_DELAY))
        &&(VOS_TRUE == NAS_EMM_SER_IsCsfbProcedure()))
    {
        NAS_EMM_SER_LOG_INFO( "NAS_EMM_MsRegSsNormalMsgEsmDataReq: Msg discard, CSFB delay timer is running.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsNormalMsgEsmDataReq_ENUM,LNAS_FUNCTION_LABEL1);
        NAS_EMM_SendEsmDataCnf(EMM_ESM_SEND_RSLT_EMM_DISCARD, pstEsmDataReq->ulOpId);
        return NAS_LMM_MSG_HANDLED;
    }

    NAS_EMM_SER_RcvEsmDataReq(pMsgStru);

    return NAS_LMM_MSG_HANDLED;

}

/*****************************************************************************
 Function Name   : NAS_EMM_MsRegSsNormalMsgSmsEstReq
 Description     : 正常服务状态下处理SMS建链请求
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunbing 49683      2011-11-3  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegSsNormalMsgSmsEstReq
(
    VOS_UINT32  ulMsgId,
    VOS_VOID   *pMsgStru
)
{
    VOS_UINT32                          ulRslt          = NAS_EMM_FAIL;

    (VOS_VOID)ulMsgId;

    NAS_EMM_SER_LOG_INFO("NAS_EMM_MsRegSsNormalMsgSmsEstReq entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsNormalMsgSmsEstReq_ENUM,LNAS_ENTRY);

    ulRslt = NAS_EMM_SER_CHKFSMStateMsgp(EMM_MS_REG,EMM_SS_REG_NORMAL_SERVICE,pMsgStru);
    if ( NAS_EMM_SUCC != ulRslt )
    {
        NAS_EMM_SER_LOG_WARN( "NAS_EMM_TAUSER_CHKFSMStateMsgp ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsNormalMsgSmsEstReq_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    /*因为建链函数已经经过预处理，进入这个函数，说明CS域已经注册，
      如果不处于空闲态，可以直接回复建链成功*/
    if (NAS_EMM_NO == NAS_LMM_IsRrcConnectStatusIdle())
    {
        NAS_LMM_SndLmmSmsEstCnf();

        NAS_LMM_SetConnectionClientId(NAS_LMM_CONNECTION_CLIENT_ID_SMS);
        return NAS_LMM_MSG_HANDLED;
    }
    if( NAS_EMM_NO == NAS_EMM_IsSerConditionSatisfied())
    {
        NAS_LMM_SndLmmSmsErrInd(LMM_SMS_ERR_CAUSE_OTHERS);
        return NAS_LMM_MSG_HANDLED;
    }
    /* 大数据: 清Mt Ser Flag标志 */
    NAS_EMM_SetOmMtSerFlag(NAS_EMM_NO);
    /*设置SER触发原因为 NAS_EMM_SER_START_CAUSE_SMS_EST_REQ*/
    NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_SMS_EST_REQ);

    /*Inform RABM that SER init*/
    NAS_EMM_SER_SendRabmReestInd(EMM_ERABM_REEST_STATE_INITIATE);

    /*启动定时器3417*/
    NAS_LMM_StartStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417);

    /*转换EMM状态机MS_SER_INIT+SS_SER_WAIT_CN_CNF*/
    NAS_EMM_TAUSER_FSMTranState(EMM_MS_SER_INIT, EMM_SS_SER_WAIT_CN_SER_CNF, TI_NAS_EMM_STATE_SERVICE_T3417);

    /*组合并发送MRRC_DATA_REQ(SERVICE_REQ)*/
    NAS_EMM_SER_SendMrrcDataReq_ServiceReq();

    return NAS_LMM_MSG_HANDLED;
}

#if (FEATURE_LPP == FEATURE_ON)
/*****************************************************************************
 Function Name   : NAS_EMM_MsRegSsNormalMsgLppEstReq
 Description     : 正常服务状态下收到LPP建链请求的处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lifuxin 00253982     2015-07-16  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegSsNormalMsgLppEstReq
(
    VOS_UINT32  ulMsgId,
    VOS_VOID   *pMsgStru
)
{
    VOS_UINT32                          ulRslt          = NAS_EMM_FAIL;

    (VOS_VOID)ulMsgId;

    NAS_EMM_SER_LOG_INFO("NAS_EMM_MsRegSsNormalMsgLppEstReq entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsNormalMsgLppEstReq_ENUM, LNAS_LPP_Func_Enter);

    ulRslt = NAS_EMM_SER_CHKFSMStateMsgp(EMM_MS_REG,EMM_SS_REG_NORMAL_SERVICE,pMsgStru);
    if ( NAS_EMM_SUCC != ulRslt )
    {
        NAS_EMM_SER_LOG_WARN( "NAS_EMM_TAUSER_CHKFSMStateMsgp ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsNormalMsgLppEstReq_ENUM, LNAS_LPP_CheckStatusError);
        return NAS_LMM_MSG_DISCARD;
    }


    /*如果不处于空闲态，可以直接回复建链成功*/
    if (NAS_EMM_NO == NAS_LMM_IsRrcConnectStatusIdle())
    {
        NAS_EMM_SendLppEstCnf(LMM_LPP_EST_RESULT_SUCC);

        return NAS_LMM_MSG_HANDLED;
    }

    if( NAS_EMM_NO == NAS_EMM_IsSerConditionSatisfied())
    {
        NAS_EMM_SndLppCnf(  ID_LPP_LMM_EST_REQ,
                            LMM_LPP_EST_RESULT_FAIL_OTHERS,
                            LMM_LPP_SEND_RSLT_FAIL_3411_RUNNING,
                            LMM_LPP_SEND_RSLT_OHTERS);

        return NAS_LMM_MSG_HANDLED;
    }

    /*设置SER触发原因为 NAS_EMM_SER_START_CAUSE_LPP_EST_REQ*/
    NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_LPP_EST_REQ);

    /*Inform RABM that SER init*/
    NAS_EMM_SER_SendRabmReestInd(EMM_ERABM_REEST_STATE_INITIATE);

    /*启动定时器3417*/
    NAS_LMM_StartStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417);

    /*转换EMM状态机MS_SER_INIT+SS_SER_WAIT_CN_CNF*/
    NAS_EMM_TAUSER_FSMTranState(EMM_MS_SER_INIT, EMM_SS_SER_WAIT_CN_SER_CNF, TI_NAS_EMM_STATE_SERVICE_T3417);

    /*组合并发送MRRC_DATA_REQ(SERVICE_REQ)*/
    NAS_EMM_SER_SendMrrcDataReq_ServiceReq();

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsRegSsRegAttemptUpdateMmMsgLppEstReq
 Description     : updte mm状态下收到LPP建链请求的处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lifuxin 00253982     2015-07-16  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegSsRegAttemptUpdateMmMsgLppEstReq
(
    VOS_UINT32  ulMsgId,
    VOS_VOID   *pMsgStru
)
{
    VOS_UINT32                          ulRslt          = NAS_EMM_FAIL;

    (VOS_VOID)ulMsgId;

    NAS_EMM_SER_LOG_INFO("NAS_EMM_MsRegSsRegAttemptUpdateMmMsgLppEstReq entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgLppEstReq_ENUM, LNAS_LPP_Func_Enter);

    ulRslt = NAS_EMM_SER_CHKFSMStateMsgp(EMM_MS_REG,EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM,pMsgStru);
    if ( NAS_EMM_SUCC != ulRslt )
    {
        NAS_EMM_SER_LOG_WARN( "NAS_EMM_TAUSER_CHKFSMStateMsgp ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgLppEstReq_ENUM, LNAS_LPP_CheckStatusError);
        return NAS_LMM_MSG_DISCARD;
    }


    /*如果不处于空闲态，可以直接回复建链成功*/
    if (NAS_EMM_NO == NAS_LMM_IsRrcConnectStatusIdle())
    {
        NAS_EMM_SendLppEstCnf(LMM_LPP_EST_RESULT_SUCC);

        return NAS_LMM_MSG_HANDLED;
    }
    if( NAS_EMM_NO == NAS_EMM_IsSerConditionSatisfied())
    {
        NAS_EMM_SndLppCnf(  ID_LPP_LMM_EST_REQ,
                            LMM_LPP_EST_RESULT_FAIL_OTHERS,
                            LMM_LPP_SEND_RSLT_FAIL_3411_RUNNING,
                            LMM_LPP_SEND_RSLT_OHTERS);

        return NAS_LMM_MSG_HANDLED;
    }
    /*设置SER触发原因为 NAS_EMM_SER_START_CAUSE_SMS_EST_REQ*/
    NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_LPP_EST_REQ);

    /*Inform RABM that SER init*/
    NAS_EMM_SER_SendRabmReestInd(EMM_ERABM_REEST_STATE_INITIATE);

    /*启动定时器3417*/
    NAS_LMM_StartStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417);

    /*转换EMM状态机MS_SER_INIT+SS_SER_WAIT_CN_CNF*/
    NAS_EMM_TAUSER_FSMTranState(EMM_MS_SER_INIT, EMM_SS_SER_WAIT_CN_SER_CNF, TI_NAS_EMM_STATE_SERVICE_T3417);

    /*组合并发送MRRC_DATA_REQ(SERVICE_REQ)*/
    NAS_EMM_SER_SendMrrcDataReq_ServiceReq();

    return NAS_LMM_MSG_HANDLED;
}
#endif

/*****************************************************************************
 Function Name   : NAS_EMM_MsRegSsRegAttemptUpdateMmMsgEsmDataReq
 Description     : Reg.Attempting_to_update_mm收到EMM_ESM_DATA_REQ消息
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2011-7-12     Draft Enact
    2.lihong00150010      2011-11-17    Modify

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegSsRegAttemptUpdateMmMsgEsmDataReq
(
    VOS_UINT32  ulMsgId,
    VOS_VOID   *pMsgStru
)
{
    VOS_UINT32                          ulRslt          = NAS_EMM_FAIL;
    EMM_ESM_DATA_REQ_STRU              *pstEsmDataReq   = (EMM_ESM_DATA_REQ_STRU*)pMsgStru;

    (VOS_VOID)ulMsgId;

    NAS_EMM_SER_LOG_INFO("NAS_EMM_MsRegSsRegAttemptUpdateMmMsgEsmDataReq entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgEsmDataReq_ENUM,LNAS_ENTRY);

    /* 函数输入指针参数检查, 状态匹配检查,若不匹配,退出*/
    ulRslt = NAS_EMM_SER_CHKFSMStateMsgp(EMM_MS_REG,
                                        EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM,
                                        pMsgStru);
    if ( NAS_EMM_SUCC != ulRslt )
    {
        NAS_EMM_SER_LOG_WARN( "NAS_EMM_TAUSER_CHKFSMStateMsgp ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsRegAttemptUpdateMmMsgEsmDataReq_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    if (VOS_TRUE == pstEsmDataReq->ulIsEmcType)
    {
        NAS_LMM_SetEmmInfoIsEmerPndEsting(VOS_TRUE);
        /* 解决LRRC REL搜小区驻留上报系统消息前收到ESM紧急承载建立请求，由于空口发送失败，本地detach,发起紧急ATTACH问题
           方案:先高优先级缓存，等到收到LRRC系统消息后处理*/
        if((NAS_EMM_CONN_WAIT_SYS_INFO == NAS_EMM_GetConnState())
            ||(NAS_EMM_CONN_RELEASING == NAS_EMM_GetConnState()))
        {
            return NAS_LMM_STORE_HIGH_PRIO_MSG;
        }
    }

    if((NAS_EMM_CONN_WAIT_SYS_INFO == NAS_EMM_GetConnState())
        ||(NAS_EMM_CONN_RELEASING == NAS_EMM_GetConnState()))
    {
        return NAS_LMM_STORE_HIGH_PRIO_MSG;
    }

    if(NAS_LMM_TIMER_RUNNING == NAS_LMM_IsStaTimerRunning(TI_NAS_EMM_STATE_T3440))
    {
        /* 如果是紧急类型的，则停止T3440定时器，主动发链路释放 */
        if (VOS_TRUE == pstEsmDataReq->ulIsEmcType)
        {
            NAS_LMM_SetEmmInfoIsEmerPndEsting(VOS_TRUE);
            NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_T3440);

            /*启动定时器TI_NAS_EMM_MRRC_WAIT_RRC_REL*/
            NAS_LMM_StartStateTimer(TI_NAS_EMM_MRRC_WAIT_RRC_REL_CNF);

            /*向MRRC发送NAS_EMM_MRRC_REL_REQ消息*/
            NAS_EMM_SndRrcRelReq(NAS_LMM_NOT_BARRED);

            /* 设置连接状态为释放过程中 */
            NAS_EMM_SetConnState(NAS_EMM_CONN_RELEASING);

        }
        return NAS_LMM_STORE_HIGH_PRIO_MSG;
    }

    /*CONN态，转发ESM消息*/
    if((NAS_EMM_CONN_SIG == NAS_EMM_GetConnState()) ||
        (NAS_EMM_CONN_DATA == NAS_EMM_GetConnState()))
    {
        NAS_EMM_SER_SendMrrcDataReq_ESMdata(&pstEsmDataReq->stEsmMsg, pstEsmDataReq->ulOpId);
        return NAS_LMM_MSG_HANDLED;
    }
    /* 记录UPDATE_MM标识 */
    /*NAS_LMM_SetEmmInfoUpdateMmFlag(NAS_EMM_UPDATE_MM_FLAG_VALID);*/
    NAS_EMM_SER_RcvEsmDataReq(pMsgStru);

    return NAS_LMM_MSG_HANDLED;
}


/*******************************************************************************
  Module   :
  Function :NAS_EMM_MsTAUInitMsgRabmReestReq
  Input    :
  Output   :
  NOTE     :
  Return   :
  History  :
    1.  Zhouyan 00125190  2008.09.10  新规作成
*******************************************************************************/
VOS_UINT32 NAS_EMM_MsTauInitMsgRabmReestReq(VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru
                                )
{
    VOS_UINT32                      ulRslt                = NAS_EMM_FAIL;

    (VOS_VOID)ulMsgId;

    /* 打印进入该函数， INFO_LEVEL */
    NAS_EMM_SER_LOG_INFO( "Nas_Emm_MsTauInitMsgRabmReestReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsTauInitMsgRabmReestReq_ENUM,LNAS_ENTRY);

    /* 函数输入指针参数检查, 状态匹配检查,若不匹配,退出*/
    ulRslt = NAS_EMM_SER_CHKFSMStateMsgp(EMM_MS_TAU_INIT,EMM_SS_TAU_WAIT_CN_TAU_CNF,pMsgStru);
    if ( NAS_EMM_SUCC != ulRslt )
    {
        /* 打印异常 */
        NAS_EMM_SER_LOG_WARN( "NAS_EMM_TAUSER_CHKFSMStateMsgp ERROR !!");

        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsTauInitMsgRabmReestReq_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    return NAS_LMM_MSG_DISCARD;
    }

/*******************************************************************************
  Module   :
  Function :NAS_EMM_MsTAUInitMsgRrcPagingInd
  Input    :
  Output   :
  NOTE     :
  Return   :
  History  :
    1.  Zhouyan 00125190  2008.09.10  新规作成
*******************************************************************************/
VOS_UINT32 NAS_EMM_MsTauInitMsgRrcPagingInd(VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru
                                )
{
    VOS_UINT32                      ulRslt              = NAS_EMM_FAIL;

    (VOS_VOID)ulMsgId;

    /* 打印进入该函数， INFO_LEVEL */
    NAS_EMM_SER_LOG_INFO( "Nas_Emm_MsTauInitMsgRrcPagingInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsTauInitMsgRrcPagingInd_ENUM,LNAS_ENTRY);

    /* 函数输入指针参数检查, 状态匹配检查,若不匹配,退出*/
    ulRslt = NAS_EMM_SER_CHKFSMStateMsgp(EMM_MS_TAU_INIT,EMM_SS_TAU_WAIT_CN_TAU_CNF,pMsgStru);
    if ( NAS_EMM_SUCC != ulRslt )
    {
        /* 打印异常 */
        NAS_EMM_SER_LOG_WARN( "NAS_EMM_TAUSER_CHKFSMStateMsgp ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsTauInitMsgRrcPagingInd_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    return NAS_LMM_STORE_HIGH_PRIO_MSG;
}

/*******************************************************************************
  Module   :
  Function :NAS_EMM_MsSerInitMsgEsmdataReq
  Input    :
  Output   :
  NOTE     :
  Return   :
  History  :
    1.  lihong 00150010  2009.12.31  新规作成
*******************************************************************************/
VOS_UINT32 NAS_EMM_MsSerInitMsgEsmdataReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    VOS_UINT32                          ulRslt             = NAS_EMM_FAIL;
    EMM_ESM_DATA_REQ_STRU              *pstsmdatareq       = NAS_EMM_NULL_PTR;

    (VOS_VOID)ulMsgId;

    /* 打印进入该函数， INFO_LEVEL */
    NAS_EMM_SER_LOG_INFO( "NAS_EMM_MsSerInitMsgEsmdataReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsSerInitMsgEsmdataReq_ENUM,LNAS_ENTRY);

    /* 函数输入指针参数检查, 状态匹配检查,若不匹配,退出*/
    ulRslt = NAS_EMM_SER_CHKFSMStateMsgp(EMM_MS_SER_INIT ,EMM_SS_SER_WAIT_CN_SER_CNF,pMsgStru);
    if ( NAS_EMM_SUCC != ulRslt )
    {
        /* 打印异常 */
        NAS_EMM_SER_LOG_WARN( "NAS_EMM_TAUSER_CHKFSMStateMsgp ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsSerInitMsgEsmdataReq_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    /*SER模块自行缓存ESM DATA消息*/
    pstsmdatareq = (EMM_ESM_DATA_REQ_STRU        *)pMsgStru;

    if (VOS_TRUE == pstsmdatareq->ulIsEmcType)
    {
        NAS_LMM_SetEmmInfoIsEmerPndEsting(VOS_TRUE);
        /* 缓存紧急类型的ESM消息 */
        NAS_EMM_SaveEmcEsmMsg(pMsgStru);
    }
    NAS_EMM_SER_SaveEsmMsg(pstsmdatareq);

    return  NAS_LMM_MSG_HANDLED;
}
/*******************************************************************************
  Module   :
  Function :Nas_Emm_MsTauInitMsgEsmdataReq
  Input    :
  Output   :
  NOTE     :
  Return   :
  History  :
    1.  Zhouyan 00125190  2008.09.10  新规作成
*******************************************************************************/
VOS_UINT32 NAS_EMM_MsTauInitMsgEsmdataReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    VOS_UINT32                          ulRslt             = NAS_EMM_FAIL;
    EMM_ESM_DATA_REQ_STRU              *pstsmdatareq       = NAS_EMM_NULL_PTR;

    (VOS_VOID)ulMsgId;

    /* 打印进入该函数， INFO_LEVEL */
    NAS_EMM_SER_LOG_INFO( "Nas_Emm_MsTauInitMsgEsmdataReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsTauInitMsgEsmdataReq_ENUM,LNAS_ENTRY);

    /* 函数输入指针参数检查, 状态匹配检查,若不匹配,退出*/
    ulRslt = NAS_EMM_SER_CHKFSMStateMsgp(EMM_MS_TAU_INIT,EMM_SS_TAU_WAIT_CN_TAU_CNF,pMsgStru);
    if ( NAS_EMM_SUCC != ulRslt )
    {
        /* 打印异常 */
        NAS_EMM_SER_LOG_WARN( "NAS_EMM_TAUSER_CHKFSMStateMsgp ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsTauInitMsgEsmdataReq_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    pstsmdatareq = (EMM_ESM_DATA_REQ_STRU *)pMsgStru;

    if (VOS_TRUE == pstsmdatareq->ulIsEmcType)
    {
        NAS_LMM_SetEmmInfoIsEmerPndEsting(VOS_TRUE);
    }

    /* 若当前TAU是打断了SERVICE的TAU类型,
       则将此收到的ESM消息缓存 */
    if (NAS_EMM_COLLISION_SERVICE == NAS_EMM_TAU_GetEmmCollisionCtrl())
    {
        /*SER模块自行缓存ESM DATA消息*/
        NAS_EMM_SER_SaveEsmMsg(pstsmdatareq);
        if (VOS_TRUE == pstsmdatareq->ulIsEmcType)
        {
            /* 缓存紧急类型的ESM消息 */
            NAS_EMM_SaveEmcEsmMsg(pMsgStru);
        }
        return  NAS_LMM_MSG_HANDLED;
    }

    /*在TAU_INIT+WAIT_CN_CNF状态，且当前的连接状态是NAS_EMM_CONN_ESTING，
      如果当前TAU类型是打断SERVCIE发起TAU， 则需要缓存， 其他类型TAU丢弃。
    */
    if(NAS_EMM_CONN_ESTING == NAS_EMM_GetConnState())
    {
        return  NAS_LMM_MSG_HANDLED;
    }

    /* 透传SM消息 */
    NAS_EMM_SER_SendMrrcDataReq_ESMdata(&pstsmdatareq->stEsmMsg, pstsmdatareq->ulOpId);

    return  NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsTauInitMsgRabmRelReq
 Description     : TauInit.WtTauCnf状态下收到数传异常，终止当前TAU流程，处理同
                   底层异常
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunbing           2010-12-29  Draft Enact
    2.lihong00150010    2012-12-14  Modify:Emergency

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsTauInitMsgRabmRelReq(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    NAS_EMM_SER_LOG_INFO( "NAS_EMM_MsTauInitMsgRabmRelReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsTauInitMsgRabmRelReq_ENUM,LNAS_ENTRY);
    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;

    /*终止当前TAU流程*/
    NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_TAU_T3430);

    #if (FEATURE_ON == FEATURE_DSDS)
    /*发送end notify消息给RRC，通知RRC释放资源*/
    NAS_EMM_TAU_SendRrcDsdsEndNotify();
    #endif

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    NAS_EMM_SendMtcTAUEndType();
#endif

    NAS_EMM_TAU_GetEmmTAUAttemptCnt()++;

    NAS_EMM_TAU_ProcAbnormal();

    if (NAS_EMM_TAU_START_CAUSE_ESM_EMC_PDN_REQ == NAS_EMM_TAU_GetEmmTAUStartCause())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_MsTauInitMsgRabmRelReq:CAUSE_ESM_EMC_PDN_REQ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsTauInitMsgRabmRelReq_ENUM,LNAS_FUNCTION_LABEL1);

        NAS_EMM_EmcPndReqTauAbnormalCommProc(   NAS_EMM_MmcSendTauActionResultIndFailWithPara,
                                                (VOS_VOID*)NAS_EMM_NULL_PTR,
                                                EMM_SS_DEREG_NORMAL_SERVICE);
    }
    else
    {
        NAS_EMM_TAU_RelIndCollisionProc(NAS_EMM_MmcSendTauActionResultIndFailWithPara,
                        (VOS_VOID*)NAS_EMM_NULL_PTR);
    }

    /*向MRRC发送NAS_EMM_MRRC_REL_REQ消息*/
    NAS_EMM_RelReq(                     NAS_LMM_NOT_BARRED);



    return  NAS_LMM_MSG_HANDLED;
}


/*******************************************************************************
  Module   : Nas_Emm_RcvRabmReestReq
  Function : 收到EMM_ERABM_REEST_REQ原语后的处理
  Input    : VOS_VOID *pMsg     原语首地址
  Output   : 无
  NOTE     : 无
  Return   : VOS_UINT32
  History  :
    1.  Zhouyan 00125190  2008.09.09  新规作成
    2.  lihong 00150010   2012.12.14  Modify:Emergency
*******************************************************************************/
VOS_VOID    NAS_EMM_SER_RcvRabmReestReq
(
    VOS_UINT32                          ulIsEmcType
)
{
    NAS_EMM_SER_LOG_INFO( "Nas_Emm_Ser_RcvRabmReestReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_RcvRabmReestReq_ENUM,LNAS_ENTRY);
    if (VOS_TRUE == ulIsEmcType)
    {
        NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_RABM_REEST_EMC);
    }
    else
    {
        if( NAS_EMM_NO == NAS_EMM_IsSerConditionSatisfied())
        {
            NAS_EMM_SER_SendRabmReestInd(EMM_ERABM_REEST_STATE_FAIL);
            return;
        }
        NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_RABM_REEST);
    }
    /* 大数据: 清Mt Ser Flag标志 */
    NAS_EMM_SetOmMtSerFlag(NAS_EMM_NO);
    /*Inform RABM that SER init*/
    NAS_EMM_SER_SendRabmReestInd(EMM_ERABM_REEST_STATE_INITIATE);

    /*启动定时器3417*/
    NAS_LMM_StartStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417);

    /*转换EMM状态机MS_SER_INIT+SS_SER_WAIT_CN_CNF*/
    NAS_EMM_TAUSER_FSMTranState(EMM_MS_SER_INIT, EMM_SS_SER_WAIT_CN_SER_CNF, TI_NAS_EMM_STATE_SERVICE_T3417);

    /*组合并发送MRRC_DATA_REQ(SERVICE_REQ)*/
    NAS_EMM_SER_SendMrrcDataReq_ServiceReq();
    return;
}

/*******************************************************************************
  Module   : NAS_EMM_SER_RcvRrcStmsiPagingInd
  Function : 收到S-TMSI PAGING原语后的处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : VOS_UINT32
  History  :
    1.  Zhouyan 00125190  2008.09.09  新规作成
*******************************************************************************/
VOS_VOID    NAS_EMM_SER_RcvRrcStmsiPagingInd(VOS_VOID)
{

    NAS_EMM_SER_LOG_INFO( "NAS_EMM_SER_RcvRrcStmsiPagingInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_RcvRrcStmsiPagingInd_ENUM,LNAS_ENTRY);

    /* 大数据: 设置SER类型为MT Ser */
    NAS_EMM_SetOmMtSerFlag(NAS_EMM_YES);
    /* 大数据: 记录Mt Ser流程启动时间 */
    NAS_EMM_SaveMtSerStartTimeStamp();
    /*设置SER触发原因为 NAS_EMM_SER_START_CAUSE_RRC_PAGING*/
    NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_RRC_PAGING);

    /*Inform RABM that SER init*/
    NAS_EMM_SER_SendRabmReestInd(EMM_ERABM_REEST_STATE_INITIATE);

    /*启动定时器3417*/
    NAS_LMM_StartStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417);

    /*转换EMM状态机MS_SER_INIT+SS_SER_WAIT_CN_CNF*/
    NAS_EMM_TAUSER_FSMTranState(EMM_MS_SER_INIT, EMM_SS_SER_WAIT_CN_SER_CNF, TI_NAS_EMM_STATE_SERVICE_T3417);

    /*组合并发送MRRC_DATA_REQ(SERVICE_REQ)*/
    NAS_EMM_SER_SendMrrcDataReq_ServiceReq();
    return;

}

/*******************************************************************************
  Module   : NAS_EMM_SER_CsDomainNotRegProcNormalCsfb
  Function : CS域未注册对普通CSFB的处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : VOS_UINT32
  History  :
    1.sunjitan 00193151    2015-07-09   Draft Enact
*******************************************************************************/
VOS_UINT32 NAS_EMM_SER_CsDomainNotRegProcNormalCsfb(VOS_VOID)
{
    NAS_EMM_SER_LOG_WARN("NAS_EMM_SER_CsDomainNotRegProcNormalCsfb is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_CsDomainNotRegProcNormalCsfb_ENUM, LNAS_ENTRY);

    /* 被#2拒绝过，直接终止 */
    if (NAS_EMM_REJ_YES == NAS_LMM_GetEmmInfoRejCause2Flag())
    {
        NAS_EMM_SER_LOG_NORM("NAS_EMM_SER_CsDomainNotRegProcNormalCsfb:REJ#2!");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_CsDomainNotRegProcNormalCsfb_ENUM, LNAS_END);

        NAS_EMM_MmSendCsfbSerEndInd(MM_LMM_CSFB_SERVICE_RSLT_VERIFY_CSFB_FAIL_FOR_OTHERS,
                                        NAS_LMM_CAUSE_NULL);
        return NAS_LMM_MSG_HANDLED;
    }

    /* UPDATE MM态进状态机处理 */
    if ((EMM_MS_REG == NAS_LMM_GetEmmCurFsmMS())
      &&(EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM == NAS_LMM_GetEmmCurFsmSS()))
    {
        return NAS_LMM_MSG_DISCARD;
    }

    /* 其他状态搜网去GU */
    NAS_EMM_MmcSendSerResultIndOtherType(MMC_LMM_SERVICE_RSLT_FAILURE);
    NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);
    return NAS_LMM_MSG_HANDLED;

}

/*******************************************************************************
  Module   : NAS_EMM_SER_CheckCsfbNeedHighPrioStore
  Function : 检测CSFB是否需要缓存
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : VOS_UINT32
  History  :
    1.sunjitan 00193151    2015-07-09   Draft Enact
*******************************************************************************/
VOS_UINT32 NAS_EMM_SER_CheckCsfbNeedHighPrioStore(VOS_VOID)
{
    if (NAS_EMM_CONN_ESTING == NAS_EMM_GetConnState())
    {
        NAS_EMM_SER_LOG_NORM("NAS_EMM_SER_CheckCsfbNeedHighPrioStore:Esting, High priority storage!");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_CheckCsfbNeedHighPrioStore_ENUM, LNAS_FUNCTION_LABEL1);
        return NAS_EMM_SUCC;
    }

    /* T3440定时器启动期间不再高优先级缓存，改为启动delay定时器，防止出现网络一直不发释放导致的发起呼叫慢问题 */
    if ((NAS_EMM_CONN_RELEASING == NAS_EMM_GetConnState())
      ||(NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_REATTACH_DELAY)))
    {
        NAS_EMM_SER_LOG_NORM("NAS_EMM_SER_CheckCsfbNeedHighPrioStore:Releasing, High priority storage!");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_CheckCsfbNeedHighPrioStore_ENUM, LNAS_FUNCTION_LABEL2);
        return NAS_EMM_SUCC;
    }

    NAS_EMM_SER_LOG_NORM("NAS_EMM_SER_CheckCsfbNeedHighPrioStore:Don't need high prio store.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_CheckCsfbNeedHighPrioStore_ENUM, LNAS_FUNCTION_LABEL3);
    return NAS_EMM_FAIL;
}

/*******************************************************************************
  Module   : NAS_EMM_SER_CheckCsfbNeedLowPrioStore
  Function : 检测CSFB是否需要低优先级缓存
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : VOS_UINT32
  History  :
    1.sunjitan 00193151    2015-07-09   Draft Enact
*******************************************************************************/
VOS_UINT32 NAS_EMM_SER_CheckCsfbNeedLowPrioStore
(
    MM_LMM_CSFB_SERVICE_TYPE_ENUM_UINT32  enCsfbSrvTyp
)
{
    switch(NAS_EMM_CUR_MAIN_STAT)
    {
        case    EMM_MS_TAU_INIT:
        case    EMM_MS_AUTH_INIT:
        case    EMM_MS_RESUME:

                NAS_EMM_SER_LOG_NORM("NAS_EMM_SER_CheckCsfbNeedLowPrioStore:TAU, need store!");
                TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_CheckCsfbNeedLowPrioStore_ENUM, LNAS_FUNCTION_LABEL1);
                return NAS_EMM_SUCC;

        case    EMM_MS_SER_INIT:
                if ((NAS_EMM_SER_START_CAUSE_MO_CSFB_REQ == NAS_EMM_SER_GetEmmSERStartCause())
                    &&(MM_LMM_CSFB_SERVICE_MO_NORMAL == enCsfbSrvTyp))
                {
                    return NAS_EMM_FAIL;
                }

                /* 当前与已经存在的MO CSFB冲突，缓存 */
                if (NAS_EMM_SER_START_CAUSE_MT_CSFB_REQ != NAS_EMM_SER_GetEmmSERStartCause())
                {
                    NAS_EMM_SER_LOG_NORM("NAS_EMM_SER_CheckCsfbNeedLowPrioStore:SER, need store!");
                    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_CheckCsfbNeedLowPrioStore_ENUM, LNAS_FUNCTION_LABEL2);
                    return NAS_EMM_SUCC;
                }

                break;

        case    EMM_MS_REG:

                if (EMM_SS_REG_IMSI_DETACH_WATI_CN_DETACH_CNF == NAS_LMM_GetEmmCurFsmSS())
                {
                    NAS_EMM_SER_LOG_NORM("NAS_EMM_SER_CheckCsfbNeedLowPrioStore:Imsi detach, need store!");
                    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_CheckCsfbNeedLowPrioStore_ENUM, LNAS_FUNCTION_LABEL3);
                    return NAS_EMM_SUCC;
                }

                break;

        case    EMM_MS_REG_INIT:

                if ((EMM_SS_ATTACH_WAIT_RRC_DATA_CNF == NAS_LMM_GetEmmCurFsmSS())
                ||(EMM_SS_ATTACH_WAIT_ESM_BEARER_CNF == NAS_LMM_GetEmmCurFsmSS()))
                {
                    NAS_EMM_SER_LOG_NORM("NAS_EMM_SER_CheckCsfbNeedLowPrioStore:Wait rrc data cnf and wait esm bearer cnf,need store!");
                    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_CheckCsfbNeedLowPrioStore_ENUM, LNAS_FUNCTION_LABEL4);
                    return NAS_EMM_SUCC;
                }

                break;

        default:
            break;
    }

    NAS_EMM_SER_LOG_NORM("NAS_EMM_SER_CheckCsfbNeedLowPrioStore:Don't need store.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_CheckCsfbNeedLowPrioStore_ENUM, LNAS_FUNCTION_LABEL4);
    return NAS_EMM_FAIL;
}

/*******************************************************************************
  Module   : NAS_EMM_SER_VerifyNormalCsfb
  Function : 检测普通CSFB能否发起
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : VOS_UINT32
  History  :
    1.sunjitan 00193151    2015-07-09   Draft Enact
*******************************************************************************/
VOS_UINT32 NAS_EMM_SER_VerifyNormalCsfb(VOS_VOID)
{
    NAS_LMM_CS_SERVICE_ENUM_UINT32      ulCsService = NAS_LMM_CS_SERVICE_BUTT;

    /* 不是CS_PS UE mode返回失败 */
    if (NAS_EMM_YES != NAS_EMM_IsCsPsUeMode())
    {
        NAS_EMM_SER_LOG_NORM("NAS_EMM_SER_VerifyNormalCsfb:Not CS_PS UE mode!");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_VerifyNormalCsfb_ENUM, LNAS_FUNCTION_LABEL1);
        return NAS_EMM_FAIL;
    }

    /* 判断UE是否支持CSFB,如果CS SERVICE未使能，则默认支持CSFB */
    ulCsService = NAS_EMM_GetCsService();
    if ((NAS_LMM_CS_SERVICE_CSFB_SMS != ulCsService)
      &&(NAS_LMM_CS_SERVICE_BUTT != ulCsService))
    {
        NAS_EMM_SER_LOG_NORM("NAS_EMM_SER_VerifyNormalCsfb: UE is not support csfb!");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_VerifyNormalCsfb_ENUM, LNAS_FUNCTION_LABEL2);
        return NAS_EMM_FAIL;
    }

    /* 判断是否是L单模 */
    if (NAS_EMM_SUCC != NAS_EMM_CheckMutiModeSupport())
    {
        NAS_EMM_SER_LOG_NORM("NAS_EMM_SER_VerifyNormalCsfb: Lte only");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_VerifyNormalCsfb_ENUM, LNAS_FUNCTION_LABEL3);
        return NAS_EMM_FAIL;
    }

    return NAS_EMM_SUCC;
}

/*******************************************************************************
  Module   : NAS_EMM_SER_VerifyMtCsfb
  Function : 检测MT CSFB能否发起
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : VOS_UINT32
  History  :
    1.  lihong 00150010       2012.02.22  新规作成
    2.  leixiantiao 00258641  2015-06-24 DTS2015061001947
*******************************************************************************/
VOS_UINT32 NAS_EMM_SER_VerifyMtCsfb( VOS_VOID )
{
    NAS_LMM_CS_SERVICE_ENUM_UINT32      ulCsService = NAS_LMM_CS_SERVICE_BUTT;

    /* MT CALL时不判断注册域:解决GU2L,L上TAU由于底层异常,导致TAU失败转到ATTEMP_TO_UPDATE_MM态时收到CS PAGING不处理问题 */

    /* 判断UE是否支持CSFB,如果CS SERVICE未使能，则默认支持CSFB */
    ulCsService = NAS_EMM_GetCsService();
    if ((NAS_LMM_CS_SERVICE_CSFB_SMS != ulCsService)
        && (NAS_LMM_CS_SERVICE_BUTT != ulCsService))
    {
        NAS_EMM_SER_LOG_NORM( "NAS_EMM_SER_VerifyMtCsfb:ue is not support csfb!");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_VerifyMtCsfb_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_FAIL;
    }

    /* 删除原不用的注释代码，和SMS ONLY的相关判断 */
    #if (FEATURE_ON == FEATURE_PTM)
    if (NAS_LMM_ADDITIONAL_UPDATE_SMS_ONLY == NAS_EMM_GetAddUpdateRslt())
    {
        NAS_EMM_ImprovePerformceeErrReport(EMM_OM_ERRLOG_IMPROVEMENT_TYPE_CS_MT_CALL);
    }
    #endif

    /* 判断是否是L单模 */
    if(NAS_EMM_SUCC != NAS_EMM_CheckMutiModeSupport())
    {
        NAS_EMM_SER_LOG_NORM( "NAS_EMM_SER_VerifyMtCsfb:lte only");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_VerifyMtCsfb_ENUM,LNAS_FUNCTION_LABEL3);
        return NAS_EMM_FAIL;
    }

    return NAS_EMM_SUCC;
}

/*******************************************************************************
  Module   : NAS_EMM_SER_VerifyCsfb
  Function : 检测CSFB能否发起
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : VOS_UINT32
  History  :
    1.  lihong 00150010  2012.02.23  新规作成
    2.  wangchen 00209181   2013-02-04 Modify for mo csfb
*******************************************************************************/
VOS_UINT32 NAS_EMM_SER_VerifyCsfb(MM_LMM_CSFB_SERVICE_TYPE_ENUM_UINT32  enCsfbSrvType)
{

    NAS_LMM_CS_SERVICE_ENUM_UINT32      ulCsService = NAS_LMM_CS_SERVICE_BUTT;

    /* 判断注册域是否为CS+PS */
    if (NAS_LMM_REG_DOMAIN_CS_PS != NAS_LMM_GetEmmInfoRegDomain())
    {
       NAS_EMM_SER_LOG_NORM( "NAS_EMM_SER_VerifyCsfb:cs is not registered!");
       TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_VerifyCsfb_ENUM,LNAS_FUNCTION_LABEL1);
       return NAS_EMM_FAIL;
    }

    /* 判断UE是否支持CSFB,如果CS SERVICE未使能，则默认支持CSFB */
    ulCsService = NAS_EMM_GetCsService();
    if ((NAS_LMM_CS_SERVICE_CSFB_SMS != ulCsService)
       && (NAS_LMM_CS_SERVICE_BUTT != ulCsService))
    {
       NAS_EMM_SER_LOG_NORM( "NAS_EMM_SER_VerifyCsfb:ue is not support csfb!");\
       TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_VerifyCsfb_ENUM,LNAS_FUNCTION_LABEL2);
       return NAS_EMM_FAIL;
    }

    /* 对于MO类型的，进入稳态后处理，对于紧急类型的，在预处理里面已经判断，
    应该不会出现，在调用分支中注意 */
    /* 判断网侧是否携带了SMS ONLY */
    if ((NAS_LMM_ADDITIONAL_UPDATE_SMS_ONLY == NAS_EMM_GetAddUpdateRslt())
        && (MM_LMM_CSFB_SERVICE_MT_NORMAL == enCsfbSrvType))
    {
       NAS_EMM_SER_LOG_NORM( "NAS_EMM_SER_VerifyCsfb:additional update result sms only");
       TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_VerifyCsfb_ENUM,LNAS_FUNCTION_LABEL3);
       return NAS_EMM_FAIL;
    }

    /* 判断是否是L单模 */
    if(NAS_EMM_SUCC != NAS_EMM_CheckMutiModeSupport())
    {
       NAS_EMM_SER_LOG_NORM( "NAS_EMM_SER_VerifyCsfb:lte only");
       TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_VerifyCsfb_ENUM,LNAS_FUNCTION_LABEL4);
       return NAS_EMM_FAIL;
    }
    return NAS_EMM_SUCC;
}


/*******************************************************************************
  Module   : NAS_EMM_SER_RcvRrcCsPagingInd
  Function : 收到CS PAGING后的处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : VOS_UINT32
  History  :
    1.  lihong 00150010  2012.02.22  新规作成
*******************************************************************************/
VOS_VOID    NAS_EMM_SER_RcvRrcCsPagingInd
(
    LRRC_LNAS_PAGING_UE_ID_ENUM_UINT32 enPagingUeId
)
{

    NAS_EMM_SER_LOG_INFO( "NAS_EMM_SER_RcvRrcCsPagingInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_RcvRrcCsPagingInd_ENUM,LNAS_ENTRY);

    /* 检测MT CSFB流程是否能够发起 */
    if (NAS_EMM_FAIL == NAS_EMM_SER_VerifyMtCsfb())
    {
        NAS_EMM_SER_LOG_NORM( "NAS_EMM_SER_RcvRrcCsPagingInd:cannot csfb!");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_RcvRrcCsPagingInd_ENUM,LNAS_FUNCTION_LABEL1);
        return ;
    }

    /* 给MM模块发送MM_MM_CSFB_SERVICE_PAGING_IND消息 */
    NAS_EMM_MmSendCsfbSerPaingInd(  NAS_EMM_MT_CSFB_TYPE_CS_PAGING,
                                    VOS_NULL_PTR,
                                    enPagingUeId);
    return;
}

/*******************************************************************************
  Module   : Nas_Emm_Ser_RcvEsmDataReq
  Function : 收到原语后的处理
  Input    : VOS_VOID *pMsg     原语首地址
  Output   : 无
  NOTE     : 无RRC连接时受到ESM DATA
  Return   : VOS_UINT32
  History  :
    1.  Zhouyan 00125190  2008.09.09  新规作成
    2.  lihong 00150010   2012.12.13  Modify
*******************************************************************************/
VOS_VOID    NAS_EMM_SER_RcvEsmDataReq(VOS_VOID   *pMsgStru)
{
    EMM_ESM_DATA_REQ_STRU        *pstsmdatareq = (EMM_ESM_DATA_REQ_STRU*)pMsgStru;

    NAS_EMM_SER_LOG_INFO( "Nas_Emm_Ser_RcvEsmDataReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_RcvEsmDataReq_ENUM,LNAS_ENTRY);
    /* 设置SERVICE触发原因值 */
    if (VOS_TRUE == pstsmdatareq->ulIsEmcType)
    {
        NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_ESM_DATA_REQ_EMC);

        /* 缓存紧急类型的ESM消息 */
        NAS_EMM_SaveEmcEsmMsg(          pMsgStru);
    }
    else
    {
        if( NAS_EMM_NO == NAS_EMM_IsSerConditionSatisfied())
        {
            NAS_EMM_SendEsmDataCnf(EMM_ESM_SEND_RSLT_EMM_DISCARD, pstsmdatareq->ulOpId);
            return;
        }
        NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_ESM_DATA_REQ);
    }
    /* 大数据:　清Mt Ser Flag */
    NAS_EMM_SetOmMtSerFlag(NAS_EMM_NO);
    /*Inform RABM that SER init*/
    NAS_EMM_SER_SendRabmReestInd(EMM_ERABM_REEST_STATE_INITIATE);

    /*SER模块自行缓存ESM DATA消息*/
    pstsmdatareq = (EMM_ESM_DATA_REQ_STRU        *)pMsgStru;
    NAS_EMM_SER_SaveEsmMsg(pstsmdatareq);

    /*启动定时器3417*/
    NAS_LMM_StartStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417);

    /*转换EMM状态机MS_SER_INIT+SS_SER_WAIT_CN_CNF*/
    NAS_EMM_TAUSER_FSMTranState(EMM_MS_SER_INIT, EMM_SS_SER_WAIT_CN_SER_CNF, TI_NAS_EMM_STATE_SERVICE_T3417);

    /*组合并发送MRRC_DATA_REQ(SERVICE_REQ)*/
    NAS_EMM_SER_SendMrrcDataReq_ServiceReq();
    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SER_UplinkPending
 Description     : 判断存在上行信令或者上行数据Pending,需要触发Service流程
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421     2011-2-14  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_SER_UplinkPending( VOS_VOID )
{
    NAS_EMM_SER_LOG_INFO( "NAS_EMM_SER_UplinkPending is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_UplinkPending_ENUM,LNAS_ENTRY);

    if( NAS_EMM_NO == NAS_EMM_IsSerConditionSatisfied())
    {
        return;
    }

    /* 大数据: 清Mt Ser Flag */
    NAS_EMM_SetOmMtSerFlag(NAS_EMM_NO);
    /*设置SER触发原因为 NAS_ESM_SER_START_CAUSE_UPLINK_PENDING*/
    NAS_EMM_SER_SaveEmmSERStartCause(NAS_ESM_SER_START_CAUSE_UPLINK_PENDING);

    /*Inform RABM that SER init*/
    NAS_EMM_SER_SendRabmReestInd(EMM_ERABM_REEST_STATE_INITIATE);

    /*启动定时器3417*/
    NAS_LMM_StartStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417);

    /*转换EMM状态机MS_SER_INIT+SS_SER_WAIT_CN_CNF*/
    NAS_EMM_TAUSER_FSMTranState(EMM_MS_SER_INIT, EMM_SS_SER_WAIT_CN_SER_CNF, TI_NAS_EMM_STATE_SERVICE_T3417);

     /*组合并发送MRRC_DATA_REQ(SERVICE_REQ)*/
    NAS_EMM_SER_SendMrrcDataReq_ServiceReq();
    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_SER_SmsEstReq
 Description     : SMS建链触发Service流程
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunjitan 00193151     2012-08-03  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_EMM_SER_SmsEstReq( VOS_VOID )
{
    NAS_EMM_SER_LOG_INFO( "NAS_EMM_SER_SmsEstReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_SmsEstReq_ENUM,LNAS_ENTRY);

    if( NAS_EMM_NO == NAS_EMM_IsSerConditionSatisfied())
    {
        NAS_LMM_SndLmmSmsErrInd(LMM_SMS_ERR_CAUSE_OTHERS);
        return;
    }

    /*设置SER触发原因为 NAS_EMM_SER_START_CAUSE_SMS_EST_REQ*/
    NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_SMS_EST_REQ);

    /*Inform RABM that SER init*/
    NAS_EMM_SER_SendRabmReestInd(EMM_ERABM_REEST_STATE_INITIATE);

    /*组合并发送MRRC_DATA_REQ(SERVICE_REQ)*/
    NAS_EMM_SER_SendMrrcDataReq_ServiceReq();

    /*启动定时器3417*/
    NAS_LMM_StartStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417);

    /*转换EMM状态机MS_SER_INIT+SS_SER_WAIT_CN_CNF*/
    NAS_EMM_TAUSER_FSMTranState(EMM_MS_SER_INIT, EMM_SS_SER_WAIT_CN_SER_CNF, TI_NAS_EMM_STATE_SERVICE_T3417);

    return;
}




/*lint -e960*/
/*lint -e961*/
VOS_BOOL NAS_EMM_SER_IsSameEsmMsgInBuf
(
    const EMM_ESM_DATA_REQ_STRU               *pMsgStru
)
{
    VOS_UINT32                          i       = 0;
    EMM_ESM_DATA_REQ_STRU              *pEsmMsg = NAS_LMM_NULL_PTR;

    /* 如果消息长度和内容相同，就认为是重复消息 */
    for (i = 0; i < g_stEmmEsmMsgBuf.ulEsmMsgCnt; i++)
    {
        if (NAS_LMM_NULL_PTR != g_stEmmEsmMsgBuf.apucEsmMsgBuf[i])
        {
            pEsmMsg = (EMM_ESM_DATA_REQ_STRU *)g_stEmmEsmMsgBuf.apucEsmMsgBuf[i];

            if ((pMsgStru->stEsmMsg.ulEsmMsgSize == pEsmMsg->stEsmMsg.ulEsmMsgSize)
             && (0 == NAS_LMM_MEM_CMP(pMsgStru->stEsmMsg.aucEsmMsg,
                                     pEsmMsg->stEsmMsg.aucEsmMsg,
                                     pEsmMsg->stEsmMsg.ulEsmMsgSize))
             && (pMsgStru->ulOpId == pEsmMsg->ulOpId)
             && (pMsgStru->ulIsEmcType == pEsmMsg->ulIsEmcType)
               )
            {
                return VOS_TRUE;
            }
        }
        else
        {
            NAS_EMM_SER_LOG_WARN( "NAS_EMM_SER_IsSameEsmMsgInBuf: Null buffer item.");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_IsSameEsmMsgInBuf_ENUM,LNAS_FUNCTION_LABEL1);
        }
    }

    return VOS_FALSE;
}

/*******************************************************************************
  Module   :
  Function : NAS_EMM_SER_FindEsmMsg
  Input    : VOS_UINT32  ulOpid
  Output   :
  NOTE     : 根据OPID查找缓存的ESM消息
  Return   : VOS_UINT32
  History  :
    1.  lihong 00150010  2012.12.14  新规作成
*******************************************************************************/
VOS_UINT32 NAS_EMM_SER_FindEsmMsg
(
    VOS_UINT32                          ulOpid
)
{
    VOS_UINT32                          ulIndex     = NAS_EMM_NULL;
    EMM_ESM_DATA_REQ_STRU              *pstEsmMsg   = NAS_EMM_NULL_PTR;

    /* 打印进入该函数， INFO_LEVEL */
    NAS_EMM_SER_LOG_INFO( "NAS_EMM_SER_FindEsmMsg is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_FindEsmMsg_ENUM,LNAS_ENTRY);

    for (ulIndex = NAS_EMM_NULL; ulIndex < g_stEmmEsmMsgBuf.ulEsmMsgCnt; ulIndex++)
    {
        pstEsmMsg = (EMM_ESM_DATA_REQ_STRU *)g_stEmmEsmMsgBuf.apucEsmMsgBuf[ulIndex];
        if (ulOpid == pstEsmMsg->ulOpId)
        {
            return ulIndex;
        }
    }

    NAS_EMM_SER_LOG_INFO( "NAS_EMM_SER_FindEsmMsg failed!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_FindEsmMsg_ENUM,LNAS_FAIL);

    return NAS_EMM_SER_MAX_ESM_BUFF_MSG_NUM;
}

/*******************************************************************************
  Module   :
  Function : NAS_EMM_SER_DeleteEsmMsg
  Input    : VOS_UINT32  ulOpid
  Output   :
  NOTE     : 根据OPID删除缓存的ESM消息
  Return   : VOS_VOID
  History  :
    1.  lihong 00150010  2012.12.14  新规作成
*******************************************************************************/
VOS_VOID NAS_EMM_SER_DeleteEsmMsg
(
    VOS_UINT32                          ulOpid
)
{
    VOS_UINT32                          ulIndex = NAS_EMM_NULL;
    VOS_UINT32                          ulRslt  = NAS_EMM_NULL;

    /* 打印进入该函数， INFO_LEVEL */
    NAS_EMM_SER_LOG_INFO( "NAS_EMM_SER_DeleteEsmMsg is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_DeleteEsmMsg_ENUM,LNAS_ENTRY);

    ulIndex = NAS_EMM_SER_FindEsmMsg(ulOpid);
    if (ulIndex >= g_stEmmEsmMsgBuf.ulEsmMsgCnt)
    {
        return ;
    }

    ulRslt = NAS_COMM_FreeBuffItem(NAS_COMM_BUFF_TYPE_EMM, g_stEmmEsmMsgBuf.apucEsmMsgBuf[ulIndex]);

    if (NAS_COMM_BUFF_SUCCESS != ulRslt)
    {
       NAS_EMM_SER_LOG_WARN("NAS_EMM_SER_DeleteEsmMsg, Memory Free is not succ");
       TLPS_PRINT2LAYER_WARNING(NAS_EMM_SER_DeleteEsmMsg_ENUM,LNAS_FUNCTION_LABEL1);
    }

    g_stEmmEsmMsgBuf.apucEsmMsgBuf[ulIndex] = NAS_LMM_NULL_PTR;

    for (; ulIndex < (g_stEmmEsmMsgBuf.ulEsmMsgCnt - 1); ulIndex++)
    {
        g_stEmmEsmMsgBuf.apucEsmMsgBuf[ulIndex] = g_stEmmEsmMsgBuf.apucEsmMsgBuf[ulIndex+1];
    }

    g_stEmmEsmMsgBuf.apucEsmMsgBuf[g_stEmmEsmMsgBuf.ulEsmMsgCnt - 1] = NAS_LMM_NULL_PTR;

    g_stEmmEsmMsgBuf.ulEsmMsgCnt--;
}

/*******************************************************************************
  Module   : NAS_EMM_Ser_SaveEsmMsg
  Function :
  Input    : VOS_VOID *pMsg
  Output   :
  NOTE     :
  Return   :
  History  :
    1.  Zhouyan 00125190  2008.09.09  新规作成
*******************************************************************************/
VOS_VOID NAS_EMM_SER_SaveEsmMsg(const EMM_ESM_DATA_REQ_STRU  *pMsgStru)
{
    VOS_VOID                            *pMsgBuf   = NAS_LMM_NULL_PTR;
    VOS_UINT32                           ulBufSize = 0;

    /* 打印进入该函数， INFO_LEVEL */
    NAS_EMM_SER_LOG_INFO( "NAS_EMM_Ser_SaveEsmMsg is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_SaveEsmMsg_ENUM,LNAS_ENTRY);

    /* 不是重复的SM消息，插入队列*/
    if ((VOS_FALSE == NAS_EMM_SER_IsSameEsmMsgInBuf(pMsgStru))
     && (NAS_EMM_SER_MAX_ESM_BUFF_MSG_NUM > g_stEmmEsmMsgBuf.ulEsmMsgCnt))
    {
        ulBufSize = pMsgStru->stEsmMsg.ulEsmMsgSize +
                    sizeof(pMsgStru->stEsmMsg.ulEsmMsgSize) +
                    sizeof(pMsgStru->ulOpId) +
                    sizeof(pMsgStru->ulIsEmcType) +
                    EMM_LEN_VOS_MSG_HEADER +
                    EMM_LEN_MSG_ID;

        /* 分配空间 */
        pMsgBuf = NAS_COMM_AllocBuffItem(NAS_COMM_BUFF_TYPE_EMM, ulBufSize);

        if (NAS_LMM_NULL_PTR != pMsgBuf)
        {
            NAS_LMM_MEM_CPY_S(pMsgBuf, ulBufSize, pMsgStru, ulBufSize);

            g_stEmmEsmMsgBuf.apucEsmMsgBuf[g_stEmmEsmMsgBuf.ulEsmMsgCnt] = pMsgBuf;
            g_stEmmEsmMsgBuf.ulEsmMsgCnt++;

        }
        else
        {
            NAS_EMM_SER_LOG_INFO( "NAS_EMM_Ser_SaveEsmMsg: NAS_AllocBuffItem return null pointer.");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_SaveEsmMsg_ENUM,LNAS_FUNCTION_LABEL1);
        }
    }
    else
    {
        NAS_EMM_SER_LOG1_INFO( "NAS_EMM_Ser_SaveEsmMsg: ESM Msg Not Buffered, Buffered msg number is:",
                               g_stEmmEsmMsgBuf.ulEsmMsgCnt);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_SER_SaveEsmMsg_ENUM,LNAS_FUNCTION_LABEL2,
                               g_stEmmEsmMsgBuf.ulEsmMsgCnt);
    }

    NAS_EMM_SER_LOG1_INFO( "NAS_EMM_Ser_SaveEsmMsg: Buffered msg number is:",
                           g_stEmmEsmMsgBuf.ulEsmMsgCnt);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_SER_SaveEsmMsg_ENUM,LNAS_FUNCTION_LABEL3,
                               g_stEmmEsmMsgBuf.ulEsmMsgCnt);

    return;
}


/*******************************************************************************
  Module   :
  Function : NAS_EMM_MsRegInitSsWaitCnAttachCnfMsgEsmDataReq
  Input    :
  Output   :
  NOTE     :
  Return   :
  History  :
    1.  X00148705  2010-01-26  新规作成
*******************************************************************************/
VOS_UINT32 NAS_EMM_EmmMsRegInitSsWaitRrcDataCnfMsgEsmDataReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    EMM_ESM_DATA_REQ_STRU              *pstEsmDataReq = (EMM_ESM_DATA_REQ_STRU*)pMsgStru;

    (VOS_VOID)(ulMsgId);
    NAS_EMM_SER_LOG_INFO("NAS_EMM_EmmMsRegInitSsWaitRrcDataCnfMsgEsmDataReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_EmmMsRegInitSsWaitRrcDataCnfMsgEsmDataReq_ENUM,LNAS_ENTRY);
    NAS_EMM_SER_SendMrrcDataReq_ESMdata(&pstEsmDataReq->stEsmMsg, pstEsmDataReq->ulOpId);
    return NAS_LMM_MSG_HANDLED;
}



/*****************************************************************************
 Function Name   : NAS_EMM_MsTauSerSsWaitCnCnfEmergencyCsfbProc
 Description     : TAU或SER等待网侧回复过程中收到紧急CSFB的处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunjitan 00193151       2012-08-16   Draft Enact
*****************************************************************************/
VOS_VOID  NAS_EMM_MsTauSerSsWaitCnCnfEmergencyCsfbProc(VOS_VOID)
{
    MMC_LMM_TAU_RSLT_ENUM_UINT32        ulTauRslt = MMC_LMM_TAU_RSLT_BUTT;

    /* TAU过程中, 后面挂起会自动清除资源 */
    if (EMM_MS_TAU_INIT == NAS_LMM_GetEmmCurFsmMS())
    {
        /* 向MMC发送LMM_MMC_TAU_RESULT_IND消息 */
        ulTauRslt = MMC_LMM_TAU_RSLT_FAILURE;
        NAS_EMM_MmcSendTauActionResultIndOthertype((VOS_VOID*)&ulTauRslt);

        NAS_EMM_TAU_AbnormalOver();
    }
    else  /* SER过程中,终止SER */
    {
        NAS_EMM_SER_AbnormalOver();
    }

    /* 转入REG.PLMN-SEARCH等MMC挂起 */
    NAS_EMM_AdStateConvert(EMM_MS_REG,
                           EMM_SS_REG_PLMN_SEARCH,
                           TI_NAS_EMM_STATE_NO_TIMER);

    /*向MMC发送LMM_MMC_SERVICE_RESULT_IND消息*/
    NAS_EMM_MmcSendSerResultIndOtherType(MMC_LMM_SERVICE_RSLT_FAILURE);

    /* 如果处于连接态，压栈释放处理 */
    NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);

    return;

}

/*****************************************************************************
 Function Name   : NAS_EMM_MsAnySsWaitCnDetachCnfEmergencyCsfbProc
 Description     : REG. EMM_SS_REG_IMSI_DETACH_WATI_CN_DETACH_CNF
                   DEREG_INIT. EMM_SS_DETACH_WAIT_CN_DETACH_CNF
                   这两个状态收到紧急CSFB的处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunjitan 00193151       2012-08-16   Draft Enact
*****************************************************************************/
VOS_VOID  NAS_EMM_MsAnySsWaitCnDetachCnfEmergencyCsfbProc(VOS_VOID)
{
    NAS_LMM_StopStateTimer(TI_NAS_EMM_T3421);

    #if (FEATURE_ON == FEATURE_DSDS)
    /*发送end notify消息给RRC，通知RRC释放资源*/
    NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_PS_DETACH);
    #endif

    /* REG. EMM_SS_REG_IMSI_DETACH_WATI_CN_DETACH_CNF 态*/
    if (EMM_MS_REG == NAS_LMM_GetEmmCurFsmMS())
    {
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);

        /* 向MMC发送本地LMM_MMC_DETACH_IND消息 */
        NAS_EMM_SendDetRslt(MMC_LMM_DETACH_RSLT_SUCCESS);
        NAS_EMM_AdStateConvert(EMM_MS_REG,
                               EMM_SS_REG_NORMAL_SERVICE,
                               TI_NAS_EMM_STATE_NO_TIMER);

        NAS_LMM_ImsiDetachReleaseResource();
    }
    else /* DEREG_INIT. EMM_SS_DETACH_WAIT_CN_DETACH_CNF 态*/
    {
        /*向MMC发送本地LMM_MMC_DETACH_IND消息*/
        NAS_EMM_SendDetRslt(MMC_LMM_DETACH_RSLT_SUCCESS);
        NAS_EMM_AdStateConvert(EMM_MS_DEREG,
                               EMM_SS_DEREG_NORMAL_SERVICE,
                               TI_NAS_EMM_STATE_NO_TIMER);

        /* 通知ESM清除资源 */
        NAS_EMM_TAU_SendEsmStatusInd(EMM_ESM_ATTACH_STATUS_DETACHED);
    }

    /*向MMC发送LMM_MMC_SERVICE_RESULT_IND消息*/
    NAS_EMM_MmcSendSerResultIndOtherType(MMC_LMM_SERVICE_RSLT_FAILURE);

    /* 如果处于连接态，压栈释放处理 */
    NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);

    return;

}

/*****************************************************************************
 Function Name   : NAS_EMM_MsRegInitSsAnyStateEmergencyCsfbProc
 Description     : 注册过程中的某些状态收到紧急CSFB的公共处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunjitan 00193151       2012-08-16   Draft Enact
*****************************************************************************/
VOS_VOID  NAS_EMM_MsRegInitSsAnyStateEmergencyCsfbProc(VOS_VOID)
{
    /* 给MMC上报ATTACH结果为失败 */
    NAS_EMM_AppSendAttOtherType(MMC_LMM_ATT_RSLT_FAILURE);

    /* ATTACH停定时器 + 清除资源 */
    NAS_EMM_Attach_SuspendInitClearResourse();

    /* 修改状态：进入主状态DEREG子状态DEREG_PLMN_SEARCH, 此时服务状态不上报改变*/
    NAS_EMM_AdStateConvert(EMM_MS_DEREG,
                           EMM_SS_DEREG_PLMN_SEARCH ,
                           TI_NAS_EMM_STATE_NO_TIMER);

    /* 通知ESM清除资源 */
    NAS_EMM_TAU_SendEsmStatusInd(EMM_ESM_ATTACH_STATUS_DETACHED);

    /*向MMC发送LMM_MMC_SERVICE_RESULT_IND消息*/
    NAS_EMM_MmcSendSerResultIndOtherType(MMC_LMM_SERVICE_RSLT_FAILURE);

    /* 如果处于连接态，压栈释放处理 */
    NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);

    return;

}

/*****************************************************************************
 Function Name   : NAS_EMM_UnableDirectlyStartMoEmergencyCsfbProc
 Description     : 不能在L模下直接发起紧急CSFB的处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunjitan 00193151       2012-08-16   Draft Enact
    2.lifuxin  00253982       2014-10-31   建链流程重构
*****************************************************************************/
VOS_UINT32  NAS_EMM_UnableDirectlyStartMoEmergencyCsfbProc(VOS_VOID)
{

    if(NAS_EMM_CONN_ESTING == NAS_EMM_GetConnState())
    {
        return  NAS_LMM_STORE_HIGH_PRIO_MSG;
    }

    if( (NAS_EMM_CONN_RELEASING == NAS_EMM_GetConnState())
        || (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsStaTimerRunning(TI_NAS_EMM_STATE_T3440))
        || (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_REATTACH_DELAY)))
    {
        NAS_EMM_SER_LOG_NORM( "NAS_EMM_CannotDirectlyStartMoEmergencyCsfbProc:High priority storage!");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_UnableDirectlyStartMoEmergencyCsfbProc_ENUM,LNAS_FUNCTION_LABEL1);
        return  NAS_LMM_STORE_HIGH_PRIO_MSG;
    }

    switch(NAS_EMM_CUR_MAIN_STAT)
    {
        case    EMM_MS_REG_INIT:
            /* 设置SERVICE发起原因为紧急CSFB, 用于给MMC上报SERVICE_RESULT_IND */
            NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_MO_EMERGENCY_CSFB_REQ);
            NAS_EMM_MsRegInitSsAnyStateEmergencyCsfbProc();
            break;

        case    EMM_MS_TAU_INIT:
        case    EMM_MS_SER_INIT:
            /* 设置SERVICE发起原因为紧急CSFB, 用于给MMC上报SERVICE_RESULT_IND */
            NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_MO_EMERGENCY_CSFB_REQ);
            NAS_EMM_MsTauSerSsWaitCnCnfEmergencyCsfbProc();
            break;

        case    EMM_MS_AUTH_INIT:
        case    EMM_MS_RESUME:
            NAS_EMM_SER_LOG_NORM( "NAS_EMM_CannotDirectlyStartMoEmergencyCsfbProc:Low priority storage!");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_UnableDirectlyStartMoEmergencyCsfbProc_ENUM,LNAS_FUNCTION_LABEL2);
            return NAS_LMM_STORE_LOW_PRIO_MSG;

        case    EMM_MS_REG:
        case    EMM_MS_DEREG_INIT:
            /* 设置SERVICE发起原因为紧急CSFB, 用于给MMC上报SERVICE_RESULT_IND */
            NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_MO_EMERGENCY_CSFB_REQ);
            if ((EMM_SS_REG_IMSI_DETACH_WATI_CN_DETACH_CNF == NAS_LMM_GetEmmCurFsmSS())
                || (EMM_SS_DETACH_WAIT_CN_DETACH_CNF == NAS_LMM_GetEmmCurFsmSS()))
            {
                NAS_EMM_MsAnySsWaitCnDetachCnfEmergencyCsfbProc();
            }
            else
            {
                /*向MMC发送LMM_MMC_SERVICE_RESULT_IND消息*/
                NAS_EMM_MmcSendSerResultIndOtherType(MMC_LMM_SERVICE_RSLT_FAILURE);
                NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);
            }
            break;

        default:
            /* 设置SERVICE发起原因为紧急CSFB, 用于给MMC上报SERVICE_RESULT_IND */
            NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_MO_EMERGENCY_CSFB_REQ);
            /*向MMC发送LMM_MMC_SERVICE_RESULT_IND消息*/
            NAS_EMM_MmcSendSerResultIndOtherType(MMC_LMM_SERVICE_RSLT_FAILURE);
            NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);
            break;
    }

    return NAS_LMM_MSG_HANDLED;

}

/*****************************************************************************
 Function Name   : NAS_EMM_MsRegPreProcMmNormalCsfbNotifyMsg
 Description     : 主状态为REG态时，MO CSFB的处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.wangchen 00209181      2013-02-04   Draft Enact
    2.sunjitan 00193151      2015-07-09   Mod for MT_CSFB_IMPROVED_PHASEI
    2.wangchen 00209181      2015-08-05   Modify for CHR
*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegPreProcMmNormalCsfbNotifyMsg
(
    MM_LMM_CSFB_SERVICE_TYPE_ENUM_UINT32  enCsfbSrvTyp
)
{
    NAS_EMM_SER_LOG_NORM( "NAS_EMM_MsRegPreProcMmNormalCsfbNotifyMsg:enter!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegPreProcMmNormalCsfbNotifyMsg_ENUM,LNAS_ENTRY);

    switch (NAS_LMM_GetEmmCurFsmSS())
    {
        /* 这些状态都进状态机处理 */
        case    EMM_SS_REG_NORMAL_SERVICE         :
        case    EMM_SS_REG_WAIT_ACCESS_GRANT_IND  :
        case    EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM:

                return NAS_LMM_MSG_DISCARD;

        /* 受限服务检查IMS电话是否存在，不存在搜网去GU */
        case    EMM_SS_REG_LIMITED_SERVICE        :

                /* 如果有IMS电话，终止CSFB，否则触发搜网去GU */
                #if (FEATURE_ON == FEATURE_IMS)
                if (VOS_TRUE == IMSA_IsCallConnExist())
                {
                    NAS_EMM_SER_LOG_WARN("NAS_EMM_MsRegPreProcMmNormalCsfbNotifyMsg:Limit service,IMS call!");
                    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegPreProcMmNormalCsfbNotifyMsg_ENUM, LNAS_FUNCTION_LABEL1);
                    NAS_EMM_MmSendCsfbSerEndInd(MM_LMM_CSFB_SERVICE_RSLT_VERIFY_CSFB_FAIL_FOR_OTHERS,
                                        NAS_LMM_CAUSE_NULL);
                }
                else
                #endif
                {
                    /* 无论是MO还是MT，都去GU搜网，紧急CSFB目前不会走到这里 */
                    NAS_EMM_MmcSendSerResultIndOtherType(MMC_LMM_SERVICE_RSLT_FAILURE);
                    NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);
                }
                #if (FEATURE_ON == FEATURE_PTM)
                if (MM_LMM_CSFB_SERVICE_MT_NORMAL == enCsfbSrvTyp)
                {
                    NAS_EMM_ImprovePerformceeErrReport(EMM_OM_ERRLOG_IMPROVEMENT_TYPE_CS_MT_CALL);
                }
                #endif
                break;

        /* 这三个状态直接搜网去GU */
        case    EMM_SS_REG_ATTEMPTING_TO_UPDATE   :
        case    EMM_SS_REG_PLMN_SEARCH            :
        case    EMM_SS_REG_NO_CELL_AVAILABLE      :

                NAS_EMM_MmcSendSerResultIndOtherType(MMC_LMM_SERVICE_RSLT_FAILURE);

                #if (FEATURE_ON == FEATURE_PTM)
                if (MM_LMM_CSFB_SERVICE_MO_NORMAL == enCsfbSrvTyp)
                {
                    NAS_EMM_ImprovePerformceeErrReport(EMM_OM_ERRLOG_IMPROVEMENT_TYPE_CS_MO_CALL);
                }
                else
                {
                    NAS_EMM_ImprovePerformceeErrReport(EMM_OM_ERRLOG_IMPROVEMENT_TYPE_CS_MT_CALL);
                }
                #endif
                break;

        /* 只剩余1个子状态IMSI DETACH，前面已经缓存了 */
        default:
                break;
    }

    return NAS_LMM_MSG_HANDLED;

}


/*****************************************************************************
 Function Name   : NAS_EMM_RcvMmNormalCsfbNotifyMsgProc
 Description     : 处理MM的Normal  CSFB开始请求消息
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunjitan 00193151       2012-08-16   Draft Enact
    2.lifuxin  00253982       2014-10-31   建链流程重构
    3.leixiantiao 00258641    2015-06-24   DTS2015061001947不处理CS PAGING问题
    4.sunjitan 00193151       2015-07-09   Mod for MT_CSFB_IMPROVED_PHASEI
*****************************************************************************/
VOS_UINT32  NAS_EMM_RcvMmNormalCsfbNotifyMsgProc
(
    MM_LMM_CSFB_SERVICE_TYPE_ENUM_UINT32          enCsfbSrvTyp
)
{
    NAS_EMM_SER_LOG_NORM("NAS_EMM_RcvMmNormalCsfbNotifyMsgProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_RcvMmNormalCsfbNotifyMsgProc_ENUM, LNAS_ENTRY);

    /* 清除CSFB ABORT标识 */
    NAS_EMM_SER_SaveEmmSerCsfbAbortFlag(NAS_EMM_CSFB_ABORT_FLAG_INVALID);

    /* 检测CSFB流程是否能够发起 */
    if (NAS_EMM_FAIL == NAS_EMM_SER_VerifyNormalCsfb())
    {
        NAS_EMM_MmSendCsfbSerEndInd(MM_LMM_CSFB_SERVICE_RSLT_VERIFY_CSFB_FAIL_FOR_OTHERS,
                                        NAS_LMM_CAUSE_NULL);

        return NAS_LMM_MSG_HANDLED;
    }

    /* 检查是否需要高优先级缓存 */
    if (NAS_EMM_SUCC == NAS_EMM_SER_CheckCsfbNeedHighPrioStore())
    {
        return NAS_LMM_STORE_HIGH_PRIO_MSG;
    }
    /* 判断是否需要低优先级缓存 */
    if (NAS_EMM_SUCC == NAS_EMM_SER_CheckCsfbNeedLowPrioStore(enCsfbSrvTyp))
    {
        return NAS_LMM_STORE_LOW_PRIO_MSG;
    }

    /* 注册域不是CS_PS的处理 */
    if (NAS_LMM_REG_DOMAIN_CS_PS != NAS_LMM_GetEmmInfoRegDomain())
    {
        return NAS_EMM_SER_CsDomainNotRegProcNormalCsfb();
    }

    /* 判断网侧是否携带了SMS ONLY，如果是，去GU搜网，如果是连接态需要释放链路 */
    if ((NAS_LMM_ADDITIONAL_UPDATE_SMS_ONLY == NAS_EMM_GetAddUpdateRslt())
      ||(NAS_LMM_TIMER_RUNNING == NAS_LMM_IsStaTimerRunning(TI_NAS_EMM_STATE_SERVICE_T3442)))
    {
        NAS_EMM_SER_LOG_WARN("NAS_EMM_RcvMmNormalCsfbNotifyMsgProc:Sms only or T3442 is running!");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RcvMmNormalCsfbNotifyMsgProc_ENUM, LNAS_FUNCTION_LABEL1);
        NAS_EMM_MmcSendSerResultIndOtherType(MMC_LMM_SERVICE_RSLT_FAILURE);
        NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);

        #if (FEATURE_ON == FEATURE_PTM)
        if (MM_LMM_CSFB_SERVICE_MT_NORMAL == enCsfbSrvTyp)
        {
            NAS_EMM_ImprovePerformceeErrReport(EMM_OM_ERRLOG_IMPROVEMENT_TYPE_CS_MT_CALL);
        }
        else if (MM_LMM_CSFB_SERVICE_MO_NORMAL == enCsfbSrvTyp)
        {
            NAS_EMM_ImprovePerformceeErrReport(EMM_OM_ERRLOG_IMPROVEMENT_TYPE_CS_MO_CALL);
        }
        else
        {
        }
        #endif
        return NAS_LMM_MSG_HANDLED;
    }

    switch(NAS_EMM_CUR_MAIN_STAT)
    {
        case    EMM_MS_SER_INIT:
                /* 降圈复杂度 */
                return NAS_EMM_MsSerInitPreProcMmNormalCsfbNotifyMsg(enCsfbSrvTyp);

        case    EMM_MS_REG:

                return NAS_EMM_MsRegPreProcMmNormalCsfbNotifyMsg(enCsfbSrvTyp);

        default:/*其他状态为错误的状态，增加告警打印*/
                NAS_EMM_PUBU_LOG1_ERR("NAS_EMM_RcvMmNormalCsfbNotifyMsgProc: Main State is err!",NAS_EMM_CUR_MAIN_STAT);
                TLPS_PRINT2LAYER_ERROR1(NAS_EMM_RcvMmNormalCsfbNotifyMsgProc_ENUM,LNAS_EMM_MAIN_STATE,NAS_EMM_CUR_MAIN_STAT);

                NAS_EMM_SetCsfbProcedureFlag(PS_FALSE);

                /*为容错，增加对MM的回复*/
                NAS_EMM_MmSendCsfbSerEndInd(MM_LMM_CSFB_SERVICE_RSLT_FAILURE, NAS_LMM_CAUSE_NULL);
                break;
    }

    return NAS_LMM_MSG_HANDLED;

}
/*lint +e961*/
/*lint +e960*/
/*****************************************************************************
 Function Name   : NAS_EMM_RcvMmMoEmergencyCsfbNotifyMsgProc
 Description     : 处理MM的Emergency  CSFB开始请求消息
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunjitan 00193151       2012-08-16   Draft Enact
    2.wangchen 00209181       2014-09-04   Modify:R11
    3.lifuxin  00253982       2014-10-31   建链流程重构
*****************************************************************************/
VOS_UINT32  NAS_EMM_RcvMmMoEmergencyCsfbNotifyMsgProc(VOS_VOID)
{
    /* 清除CSFB ABORT标识 */
    NAS_EMM_SER_SaveEmmSerCsfbAbortFlag(NAS_EMM_CSFB_ABORT_FLAG_INVALID);

    /* L单模不能发起紧急CSFB */
    if (NAS_EMM_SUCC != NAS_EMM_CheckMutiModeSupport())
    {
        NAS_EMM_MmSendCsfbSerEndInd(MM_LMM_CSFB_SERVICE_RSLT_VERIFY_CSFB_FAIL_FOR_OTHERS, NAS_LMM_CAUSE_NULL);
        return NAS_LMM_MSG_HANDLED;
    }

    /* 此处置Service启动标志主要是为了当无法发起CSFB时回复MMC Service结果使用，
       若当前主状态为Ser Init，此时置标志会导致Service流程异常 */

    /* 可能可以直接发起紧急CSFB流程, 根据当前所处状态进行不同处理*/
    if (NAS_EMM_SUCC == NAS_EMM_SER_VerifyCsfb(MM_LMM_CSFB_SERVICE_MO_EMERGENCY))
    {
        if((NAS_EMM_CONN_ESTING == NAS_EMM_GetConnState())
            || (NAS_EMM_CONN_RELEASING == NAS_EMM_GetConnState())
            || (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_REATTACH_DELAY)))
        {
            return  NAS_LMM_STORE_HIGH_PRIO_MSG;
        }

        if(NAS_LMM_TIMER_RUNNING == NAS_LMM_IsStaTimerRunning(TI_NAS_EMM_STATE_T3440))
        {
            NAS_EMM_SER_LOG_NORM( "NAS_EMM_RcvMmMoEmergencyCsfbNotifyMsgProc:High priority storage!");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_RcvMmMoEmergencyCsfbNotifyMsgProc_ENUM,LNAS_FUNCTION_LABEL1);
                if (NAS_RELEASE_R11)
                {
                    /* upon receiving a request from upper layers to establish either a CS emergency call or
                    a PDN connection for emergency bearer services, the UE shall stop timer T3340 and
                    shall locally release the NAS signalling connection, before proceeding as specified in subclause 5.6.1*/
                    /* 如果状态不是RELEASING状态，则之前肯定是启动了T3440定时器 */
                    NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_T3440);

                    /*启动定时器TI_NAS_EMM_MRRC_WAIT_RRC_REL*/
                    NAS_LMM_StartStateTimer(TI_NAS_EMM_MRRC_WAIT_RRC_REL_CNF);

                    /*向MRRC发送NAS_EMM_MRRC_REL_REQ消息*/
                    NAS_EMM_SndRrcRelReq(NAS_LMM_NOT_BARRED);

                    /* 设置连接状态为释放过程中 */
                    NAS_EMM_SetConnState(NAS_EMM_CONN_RELEASING);
                }
            return NAS_LMM_STORE_HIGH_PRIO_MSG;
        }

        switch(NAS_EMM_CUR_MAIN_STAT)
        {
            case    EMM_MS_TAU_INIT:
            case    EMM_MS_SER_INIT:
            case    EMM_MS_AUTH_INIT:
            case    EMM_MS_RESUME:
                NAS_EMM_SER_LOG_NORM( "NAS_EMM_RcvMmMoEmergencyCsfbNotifyMsgProc:Low priority storage!");
                TLPS_PRINT2LAYER_INFO(NAS_EMM_RcvMmMoEmergencyCsfbNotifyMsgProc_ENUM,LNAS_FUNCTION_LABEL2);
                return NAS_LMM_STORE_LOW_PRIO_MSG;

            /*只有REG+NORMAL_SERVICE态可能直接发起紧急CSFB*/
            case    EMM_MS_REG:
                if (EMM_SS_REG_NORMAL_SERVICE == NAS_EMM_CUR_SUB_STAT)
                {
                    return NAS_LMM_MSG_DISCARD;
                }
                break;

            default:
                break;

        }
    }

    /* 必然不能直接发起或者状态不是上面所列则认为不能发起 */
    return NAS_EMM_UnableDirectlyStartMoEmergencyCsfbProc();

}

/*****************************************************************************
 Function Name   : NAS_EMM_PreProcMsgMmCsfbSerStartReq
 Description     : 预处理MM的CSFB开始请求消息
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong 00150010      2012-02-23  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_PreProcMsgMmCsfbSerStartNotify( MsgBlock * pMsg )
{
    MM_LMM_CSFB_SERVICE_START_NOTIFY_STRU *pstCsfbSerStartNotify = VOS_NULL_PTR;

    pstCsfbSerStartNotify = (MM_LMM_CSFB_SERVICE_START_NOTIFY_STRU*)pMsg;

    /* 紧急CSFB的处理 */
    if (MM_LMM_CSFB_SERVICE_MO_EMERGENCY == pstCsfbSerStartNotify->enCsfbSrvType)
    {
        return NAS_EMM_RcvMmMoEmergencyCsfbNotifyMsgProc();
    }
    else  /* MO或MT的NORMAL CSFB的处理 */
    {
        return NAS_EMM_RcvMmNormalCsfbNotifyMsgProc(pstCsfbSerStartNotify->enCsfbSrvType);
    }
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsRegSsNormalMsgMmCsfbSerStartNotify
 Description     : 正常服务状态下处理CSFB START请求
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong        00150010      2012-02-23  Draft Enact
    2.leixiantiao   00258641      2015-07-09  fix DTS2015062509266
*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegSsNormalMsgMmCsfbSerStartNotify
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    VOS_UINT32                             ulRslt                   = NAS_EMM_FAIL;
    MM_LMM_CSFB_SERVICE_START_NOTIFY_STRU *pstCsfbSerStartNotify    = VOS_NULL_PTR;

    (VOS_VOID)ulMsgId;

    NAS_EMM_SER_LOG_INFO("NAS_EMM_MsRegSsNormalMsgMmCsfbSerStartNotify entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsNormalMsgMmCsfbSerStartNotify_ENUM,LNAS_ENTRY);

    pstCsfbSerStartNotify = (MM_LMM_CSFB_SERVICE_START_NOTIFY_STRU *)pMsgStru;

    ulRslt = NAS_EMM_SER_CHKFSMStateMsgp(EMM_MS_REG,EMM_SS_REG_NORMAL_SERVICE,pMsgStru);
    if ( NAS_EMM_SUCC != ulRslt )
    {
        NAS_EMM_SER_LOG_WARN( "NAS_EMM_MsRegSsNormalMsgMmCsfbSerStartNotify ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsNormalMsgMmCsfbSerStartNotify_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    /*设置SER触发原因值*/
    if (MM_LMM_CSFB_SERVICE_MO_NORMAL == pstCsfbSerStartNotify->enCsfbSrvType)
    {
        NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_MO_CSFB_REQ);
    }
    else if (MM_LMM_CSFB_SERVICE_MO_EMERGENCY == pstCsfbSerStartNotify->enCsfbSrvType)
    {
        NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_MO_EMERGENCY_CSFB_REQ);
    }
    else
    {
        NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_MT_CSFB_REQ);
    }

    /* 如果处于释放过程中，因底层处于未驻留状态，启动CSFB延时定时器，等收到系统消息时再考虑发起 */
    if((NAS_EMM_CONN_RELEASING == NAS_EMM_GetConnState())
     ||(NAS_EMM_CONN_WAIT_SYS_INFO == NAS_EMM_GetConnState()) \
     /* 为解决T3440定时器启动期间网络一直不释放链路，导致响应被叫太慢的问题，
     此定时器启动期间不再高优先级缓存，改为启动delay定时器 */
     ||(NAS_LMM_TIMER_RUNNING == NAS_LMM_IsStaTimerRunning(TI_NAS_EMM_STATE_T3440)))
    {
       NAS_LMM_StartPtlTimer(TI_NAS_EMM_PTL_CSFB_DELAY);
       return NAS_LMM_MSG_HANDLED;
    }

    /* 设置UE接受CSFB */
    NAS_EMM_SER_SaveEmmSerCsfbRsp(NAS_EMM_CSFB_RSP_ACCEPTED_BY_UE);

    /*启动定时器3417*/
    NAS_LMM_StartStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417_EXT);

    /*转换EMM状态机MS_SER_INIT+SS_SER_WAIT_CN_CNF*/
    NAS_EMM_TAUSER_FSMTranState(EMM_MS_SER_INIT, EMM_SS_SER_WAIT_CN_SER_CNF, TI_NAS_EMM_STATE_SERVICE_T3417_EXT);

    /* ESR空口发送前,通知LRRC CSFB流程INIT,LRRC置一个全局变量,当ESR发送时发生重建,直接回LMM REL,搜网去GU */

    NAS_EMM_SndLrrcLmmCsfbNotify(LRRC_LNAS_CSFB_STATUS_INIT);

    /*组合并发送MRRC_DATA_REQ(SERVICE_REQ)*/
    NAS_EMM_SER_SendMrrcDataReq_ExtendedServiceReq();
    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsRegSsWaitAccessGrantIndMsgMmCsfbSerStartReq
 Description     : 被罢状态下处理CSFB START请求
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong       00150010      2012-02-23  Draft Enact
    2.leixiantiao  00258641      2015-07-09  fix DTS2015062509266
*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegSsWaitAccessGrantIndMsgMmCsfbSerStartNotify
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    VOS_UINT32                             ulRslt                   = NAS_EMM_FAIL;
    MM_LMM_CSFB_SERVICE_START_NOTIFY_STRU *pstCsfbSerStartNotify    = VOS_NULL_PTR;

    (VOS_VOID)ulMsgId;

    NAS_EMM_SER_LOG_INFO("NAS_EMM_MsRegSsWaitAccessGrantIndMsgMmCsfbSerStartNotify entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsWaitAccessGrantIndMsgMmCsfbSerStartNotify_ENUM,LNAS_ENTRY);

    pstCsfbSerStartNotify = (MM_LMM_CSFB_SERVICE_START_NOTIFY_STRU *)pMsgStru;

    ulRslt = NAS_EMM_SER_CHKFSMStateMsgp(EMM_MS_REG,EMM_SS_REG_WAIT_ACCESS_GRANT_IND,pMsgStru);
    if ( NAS_EMM_SUCC != ulRslt )
    {
        NAS_EMM_SER_LOG_WARN( "NAS_EMM_MsRegSsWaitAccessGrantIndMsgMmCsfbSerStartNotify ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsWaitAccessGrantIndMsgMmCsfbSerStartNotify_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    /* MO CSFB不能发起 */
    if (MM_LMM_CSFB_SERVICE_MO_NORMAL == pstCsfbSerStartNotify->enCsfbSrvType)
    {
        NAS_EMM_MmcSendSerResultIndOtherType(MMC_LMM_SERVICE_RSLT_FAILURE);
        return NAS_LMM_MSG_HANDLED;
    }

    /* 此状态不可能收到紧急CSFB,预处理中已规避 */

    /* 如果MT被BAR，且是MT CSFB，则直接搜网去GU */
    if ((NAS_EMM_SUCC == NAS_EMM_JudgeBarType(NAS_EMM_BAR_TYPE_MT))
      &&(MM_LMM_CSFB_SERVICE_MT_NORMAL == pstCsfbSerStartNotify->enCsfbSrvType))
    {
        NAS_EMM_MmcSendSerResultIndOtherType(MMC_LMM_SERVICE_RSLT_FAILURE);
        #if (FEATURE_ON == FEATURE_PTM)
        /* 被罢状态，收到CS PAGING消息时，不主动上报CHR，等收到CSFB START NOTIFY时再上报 */
        NAS_EMM_ImprovePerformceeErrReport(EMM_OM_ERRLOG_IMPROVEMENT_TYPE_CS_MT_CALL);
        #endif
        return NAS_LMM_MSG_HANDLED;
    }

    /* 设置SER启动原因为MT CSFB */
    NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_MT_CSFB_REQ);

    /* 设置UE接受CSFB */
    NAS_EMM_SER_SaveEmmSerCsfbRsp(NAS_EMM_CSFB_RSP_ACCEPTED_BY_UE);

    /* ESR空口发送前,通知LRRC CSFB流程INIT,LRRC置一个全局变量,当ESR发送时发生重建,直接回LMM REL,搜网去GU */
    NAS_EMM_SndLrrcLmmCsfbNotify(LRRC_LNAS_CSFB_STATUS_INIT);

    /*启动定时器3417*/
    NAS_LMM_StartStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417_EXT);

    /*转换EMM状态机MS_SER_INIT+SS_SER_WAIT_CN_CNF*/
    NAS_EMM_TAUSER_FSMTranState(EMM_MS_SER_INIT, EMM_SS_SER_WAIT_CN_SER_CNF, TI_NAS_EMM_STATE_SERVICE_T3417_EXT);

    /*组合并发送MRRC_DATA_REQ(SERVICE_REQ)*/
    NAS_EMM_SER_SendMrrcDataReq_ExtendedServiceReq();
    return NAS_LMM_MSG_HANDLED;
}

/* 删除不使用的UPDATE MM态收到CS PAGING函数的定义 */

/*****************************************************************************
 Function Name   : NAS_EMM_MsSerInitPreProcMmNormalCsfbNotifyMsg
 Description     : SerInit下CSFB NOTIFY MSG处理
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.leixiantiao 00258641      2015-06-24  Draft Enact
    2.leixiantiao 00258641      2015-07-09  fix DTS2015062509266
*****************************************************************************/
VOS_UINT32 NAS_EMM_MsSerInitPreProcMmNormalCsfbNotifyMsg
(
    MM_LMM_CSFB_SERVICE_TYPE_ENUM_UINT32  enCsfbSrvTyp
)
{
    if (NAS_EMM_SER_START_CAUSE_MO_CSFB_REQ == NAS_EMM_SER_GetEmmSERStartCause())
    {
        if (MM_LMM_CSFB_SERVICE_MO_NORMAL == enCsfbSrvTyp)
        {
            /*停止定时器T3417ext*/
            NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417_EXT);

            /*设置SER触发原因值*/
            NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_MO_CSFB_REQ);

            /* 设置UE接受CSFB */
            NAS_EMM_SER_SaveEmmSerCsfbRsp(NAS_EMM_CSFB_RSP_ACCEPTED_BY_UE);

            /* ESR空口发送前,通知LRRC CSFB流程INIT,LRRC置一个全局变量,当ESR发送时发生重建,直接回LMM REL,搜网去GU */

            NAS_EMM_SndLrrcLmmCsfbNotify(LRRC_LNAS_CSFB_STATUS_INIT);

            /*组合并发送MRRC_DATA_REQ(SERVICE_REQ)*/
            NAS_EMM_SER_SendMrrcDataReq_ExtendedServiceReq();

            /*启动定时器T3417ext*/
            NAS_LMM_StartStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417_EXT);

            return NAS_LMM_MSG_HANDLED;
        }
    }

    /* 判断当前是MT CSFB触发的ESR流程中，且网侧再次触发MT CSFB，则重新触发ESR，定时器T3417EXT重新启动
       如果收到了MO类型的CSFB则直接丢弃*/
    if ((NAS_EMM_SER_START_CAUSE_MT_CSFB_REQ == NAS_EMM_SER_GetEmmSERStartCause()))
    {
        if (MM_LMM_CSFB_SERVICE_MT_NORMAL == enCsfbSrvTyp)
        {
            /*停止定时器T3417ext*/
            NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417_EXT);

            /*设置SER触发原因值*/
            NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_MT_CSFB_REQ);

            /* 设置UE接受CSFB */
            NAS_EMM_SER_SaveEmmSerCsfbRsp(NAS_EMM_CSFB_RSP_ACCEPTED_BY_UE);

            /* ESR空口发送前,通知LRRC CSFB流程INIT,LRRC置一个全局变量,当ESR发送时发生重建,直接回LMM REL,搜网去GU */

            NAS_EMM_SndLrrcLmmCsfbNotify(LRRC_LNAS_CSFB_STATUS_INIT);

            /*组合并发送MRRC_DATA_REQ(SERVICE_REQ)*/
            NAS_EMM_SER_SendMrrcDataReq_ExtendedServiceReq();

            /*启动定时器T3417ext*/
            NAS_LMM_StartStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417_EXT);
        }
    }
    /* 与MO CSFB冲突的场景属于缓存场景，在前面已经缓存 */
    return NAS_LMM_MSG_HANDLED;

}
/*****************************************************************************
 Function Name   : NAS_EMM_MsRegSsAttempToUpdateMmMsgMmCsfbSerStartNotify
 Description     : Reg Attemp To Update Mm状态下收到CSFB Start Notify处理
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.leixiantiao 00258641      2015-06-24  Draft Enact
    2.leixiantiao 00258641      2015-07-09  fix DTS2015062509266
*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegSsAttempToUpdateMmMsgMmCsfbSerStartNotify
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    VOS_UINT32                             ulRslt                   = NAS_EMM_FAIL;
    MM_LMM_CSFB_SERVICE_START_NOTIFY_STRU *pstCsfbSerStartNotify    = VOS_NULL_PTR;

    (VOS_VOID)ulMsgId;

    NAS_EMM_SER_LOG_INFO("NAS_EMM_MsRegSsAttempToUpdateMmMsgMmCsfbSerStartNotify entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsAttempToUpdateMmMsgMmCsfbSerStartNotify_ENUM,LNAS_ENTRY);

    pstCsfbSerStartNotify = (MM_LMM_CSFB_SERVICE_START_NOTIFY_STRU *)pMsgStru;

    ulRslt = NAS_EMM_SER_CHKFSMStateMsgp(EMM_MS_REG,EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM,pMsgStru);
    if ( NAS_EMM_SUCC != ulRslt )
    {
        NAS_EMM_SER_LOG_WARN( "NAS_EMM_MsRegSsAttempToUpdateMmMsgMmCsfbSerStartNotify ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsAttempToUpdateMmMsgMmCsfbSerStartNotify_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    /*如果是MO CSFB或者紧急CSFB，则直接回复失败，触发MMC选网到GU，如果当前为
      连接态，还需要主动释放链路 */
    if ((MM_LMM_CSFB_SERVICE_MO_NORMAL == pstCsfbSerStartNotify->enCsfbSrvType)
        || (MM_LMM_CSFB_SERVICE_MO_EMERGENCY == pstCsfbSerStartNotify->enCsfbSrvType))
    {
        NAS_EMM_MmcSendSerResultIndOtherType(MMC_LMM_SERVICE_RSLT_FAILURE);

        NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);

        return NAS_LMM_MSG_HANDLED;
    }

    NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_MT_CSFB_REQ);

    /* 如果处于释放过程中，因底层处于未驻留状态，启动CSFB延时定时器，等收到系统消息时再考虑发起，
    为解决T3440定时器启动期间网络一直不释放链路，导致响应被叫太慢的问题，此定时器启动期间不再高
    优先级缓存，改为启动delay定时器 */
    if((NAS_EMM_CONN_RELEASING == NAS_EMM_GetConnState())
     ||(NAS_EMM_CONN_WAIT_SYS_INFO == NAS_EMM_GetConnState())
     ||(NAS_LMM_TIMER_RUNNING == NAS_LMM_IsStaTimerRunning(TI_NAS_EMM_STATE_T3440)))
    {
       NAS_LMM_StartPtlTimer(TI_NAS_EMM_PTL_CSFB_DELAY);
       return NAS_LMM_MSG_HANDLED;
    }

    /* 设置UE接受CSFB */
    NAS_EMM_SER_SaveEmmSerCsfbRsp(NAS_EMM_CSFB_RSP_ACCEPTED_BY_UE);

    /*启动定时器3417*/
    NAS_LMM_StartStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417_EXT);

    /*转换EMM状态机MS_SER_INIT+SS_SER_WAIT_CN_CNF*/
    NAS_EMM_TAUSER_FSMTranState(EMM_MS_SER_INIT, EMM_SS_SER_WAIT_CN_SER_CNF, TI_NAS_EMM_STATE_SERVICE_T3417_EXT);

    /* ESR空口发送前,通知LRRC CSFB流程INIT,LRRC置一个全局变量,当ESR发送时发生重建,直接回LMM REL,搜网去GU */

    NAS_EMM_SndLrrcLmmCsfbNotify(LRRC_LNAS_CSFB_STATUS_INIT);

    /*组合并发送MRRC_DATA_REQ(SERVICE_REQ)*/
    NAS_EMM_SER_SendMrrcDataReq_ExtendedServiceReq();
    return NAS_LMM_MSG_HANDLED;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



