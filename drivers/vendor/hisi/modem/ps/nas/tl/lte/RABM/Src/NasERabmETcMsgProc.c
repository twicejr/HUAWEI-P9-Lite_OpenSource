


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include  "NasERabmETcMsgProc.h"
#include  "NasERabmIpFilter.h"
#include  "NasERabmCdsMsgProc.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASRABMTCMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASRABMTCMSGPROC_C
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


/*****************************************************************************
  3 Function
*****************************************************************************/

/*****************************************************************************
 Function Name   : NAS_ERABM_TcMsgDistr()
 Description     : RABM模块TC消息分发处理
 Input           : VOS_VOID *pRcvMsg-----------消息指针
 Output          : VOS_VOID
 Return          : VOS_VOID
 History         :
     1.lihong 00150010       2009-10-16   Draft Enact

*****************************************************************************/
/*lint -e960*/
/*lint -e961*/
VOS_VOID NAS_ERABM_TcMsgDistr( VOS_VOID *pRcvMsg )
{
    PS_MSG_HEADER_STRU         *pEmmMsg = VOS_NULL_PTR;

    pEmmMsg = (PS_MSG_HEADER_STRU*)pRcvMsg;

    /*打印进入该函数*/
    NAS_ERABM_INFO_LOG("NAS_ERABM_TcMsgDistr is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ERABM_TcMsgDistr_ENUM, LNAS_ENTRY);

    /*根据消息名，调用相应的消息处理函数*/
    switch (pEmmMsg->ulMsgName)
    {
        /*如果收到的是ID_ETC_ERABM_ACTIVATE_TEST_MODE消息*/
        case ID_ETC_ERABM_ACTIVATE_TEST_MODE:
            NAS_ERABM_RcvRabmTcActTestMode();
            break;

        /*如果收到的是ID_ETC_ERABM_DEACTIVATE_TEST_MODE消息*/
        case ID_ETC_ERABM_DEACTIVATE_TEST_MODE:
            NAS_ERABM_RcvRabmTcDeactTestMode();
            break;

        /*如果收到的是ID_ETC_ERABM_REL_REQ消息*/
        case ID_ETC_ERABM_REL_REQ:
            NAS_ERABM_RcvRabmTcRelReq();
            break;

        /*如果收到的是ID_ETC_ERABM_SUSPEND_RSP消息*/
        case ID_ETC_ERABM_SUSPEND_RSP:
            NAS_ERABM_NORM_LOG("NAS_ERABM_TcMsgDistr:receive ID_ETC_ERABM_SUSPEND_RSP!");
            TLPS_PRINT2LAYER_INFO(NAS_ERABM_TcMsgDistr_ENUM, LNAS_FUNCTION_LABEL1);
            break;

        /*如果收到的是ID_ETC_ERABM_RESUME_RSP消息*/
        case ID_ETC_ERABM_RESUME_RSP:
            NAS_ERABM_NORM_LOG("NAS_ERABM_TcMsgDistr:receive ID_ETC_ERABM_RESUME_RSP!");
            TLPS_PRINT2LAYER_INFO(NAS_ERABM_TcMsgDistr_ENUM, LNAS_FUNCTION_LABEL2);
            break;

        default:
            NAS_ERABM_WARN_LOG("NAS_ERABM_TcMsgDistr:WARNING:TC->RABM Message name non-existent!");
            TLPS_PRINT2LAYER_WARNING(NAS_ERABM_TcMsgDistr_ENUM, LNAS_MSG_INVALID);
            break;
    }
}

/*****************************************************************************
 Function Name   : NAS_ERABM_RcvRabmTcActTestMode
 Description     : 收到TC模块ACTIVATE TEST MODE消息处理函数
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-10-16  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ERABM_RcvRabmTcActTestMode( VOS_VOID )
{
    if (NAS_ERABM_L_MODE_STATUS_NORMAL != NAS_ERABM_GetLModeStatus())
    {
        NAS_ERABM_WARN_LOG("NAS_ERABM_RcvRabmTcActTestMode:Rabm is already suspended!");
        TLPS_PRINT2LAYER_WARNING(NAS_ERABM_RcvRabmTcActTestMode_ENUM, LNAS_ERABM_RabmSuspended);
        return ;
    }

    /* 将模式设为环回模式 */
    NAS_ERABM_SetMode(NAS_ERABM_MODE_TYPE_LB);

    NAS_ERABM_SetUlNdisFilterValidFlag(NAS_ERABM_UL_NDIS_FILTER_INVALID);

    if(PS_FAIL == NAS_ERABM_IpfConfigUlFilter())
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_RcvRabmTcActTestMode: Update IP Filter Failed.");
        TLPS_PRINT2LAYER_ERROR(NAS_ERABM_RcvRabmTcActTestMode_ENUM, LNAS_ERABM_UpdateIPFilterFailed);
    }
}

/*****************************************************************************
 Function Name   : NAS_ERABM_RcvRabmTcDeactTestMode
 Description     : 收到TC模块DEACTIVATE TEST MODE消息处理函数
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-10-16  Draft Enact
    2.yangfan 00159566    2011-03-28  Modify
*****************************************************************************/
VOS_VOID  NAS_ERABM_RcvRabmTcDeactTestMode( VOS_VOID )
{
    if (NAS_ERABM_L_MODE_STATUS_NORMAL != NAS_ERABM_GetLModeStatus())
    {
        NAS_ERABM_WARN_LOG("NAS_ERABM_RcvRabmTcDeactTestMode:Rabm is already suspended!");
        TLPS_PRINT2LAYER_WARNING(NAS_ERABM_RcvRabmTcDeactTestMode_ENUM, LNAS_ERABM_RabmSuspended);
        return ;
    }

    /* 环回模式B下停止环回缓存定时器 */
    if (NAS_ERABM_MODE_TYPE_LB == NAS_ERABM_GetMode())
    {
        NAS_ERABM_TimerStop(NAS_ERABM_WAIT_TC_FREE_BUFFER_TIMER);
    }

    /* 将模式设为正常模式 */
    NAS_ERABM_SetMode(NAS_ERABM_MODE_TYPE_NORMAL);

    if (0 != NAS_ERABM_GetActiveEpsBearerNum())
    {
        NAS_ERABM_SetUlNdisFilterValidFlag(NAS_ERABM_UL_NDIS_FILTER_VALID);
    }
    else
    {
        NAS_ERABM_SetUlNdisFilterValidFlag(NAS_ERABM_UL_NDIS_FILTER_INVALID);
    }

    if(PS_FAIL == NAS_ERABM_IpfConfigUlFilter())
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_RcvRabmTcActTestMode: Update IP Filter Failed.");
        TLPS_PRINT2LAYER_ERROR(NAS_ERABM_RcvRabmTcDeactTestMode_ENUM, LNAS_ERABM_UpdateIPFilterFailed);
    }
}

/*****************************************************************************
 Function Name   : NAS_ERABM_RcvRabmTcRelReq
 Description     : 收到TC模块REL REQ消息处理函数
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-10-16  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ERABM_RcvRabmTcRelReq( VOS_VOID )
{
    VOS_UINT32 ulLoop = NAS_ERABM_NULL;

    /*打印进入该函数*/
    NAS_ERABM_INFO_LOG("NAS_ERABM_RcvRabmTcRelReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ERABM_RcvRabmTcRelReq_ENUM, LNAS_ENTRY);

    /* 通知CDS RAB RELEASE */
    for (ulLoop = NAS_ERABM_MIN_EPSB_ID; ulLoop <= NAS_ERABM_MAX_EPSB_ID; ulLoop++)
    {
        if (NAS_ERABM_EPSB_ACTIVE == NAS_ERABM_GetEpsbStateInfo(ulLoop))
        {
            /* 给CDS发送CDS_ERABM_RAB_RELEASE_IND */
            NAS_ERABM_SndErabmCdsRabReleaseInd(ulLoop);
        }
    }

    /*释放所有资源，回到开机初始化后的状态*/
    NAS_ERABM_ClearRabmResource();

    if(NAS_ERABM_L_MODE_STATUS_NORMAL != NAS_ERABM_GetLModeStatus())
    {
        return;
    }

    /*根据TFT和承载信息更新IP Filter到硬件加速器*/
    if(PS_FAIL == NAS_ERABM_IpfConfigUlFilter())
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_EsmMsgDistr: IPF Update IP Filter Failed.");
        TLPS_PRINT2LAYER_ERROR(NAS_ERABM_RcvRabmTcRelReq_ENUM, LNAS_ERABM_IPFUpdateIPFilterFailed);
    }

    /*根据TFT和承载信息更新IP Filter到CDS*/
    if(PS_FAIL == NAS_ERABM_CdsConfigUlFilter())
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_EsmMsgDistr: CDS Update IP Filter Failed.");
        TLPS_PRINT2LAYER_ERROR(NAS_ERABM_RcvRabmTcRelReq_ENUM, LNAS_ERABM_CDSUpdateIPFilterFailed);
    }
    return;
}

/*****************************************************************************
 Function Name   : NAS_ERABM_SndRabmTcSuspendInd
 Description     : ERABM模块向ETC发送ID_ETC_ERABM_SUSPEND_IND消息
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2011-05-03  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ERABM_SndRabmTcSuspendInd( VOS_VOID )
{
    ETC_ERABM_SUSPEND_IND_STRU           *pstRabmTcSuspendInd  = VOS_NULL_PTR;

    /*分配空间并检验分配是否成功*/
    pstRabmTcSuspendInd = (VOS_VOID*)NAS_ERABM_ALLOC_MSG(sizeof(ETC_ERABM_SUSPEND_IND_STRU));

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pstRabmTcSuspendInd)
    {
        /*打印异常信息*/
        NAS_ERABM_ERR_LOG("NAS_ERABM_SndRabmTcSuspendInd:ERROR:Alloc Msg fail!");
        return ;
    }

    /*清空*/
    NAS_ERABM_MEM_SET_S( NAS_ERABM_GET_MSG_ENTITY(pstRabmTcSuspendInd),
                         NAS_ERABM_GET_MSG_LENGTH(pstRabmTcSuspendInd),
                         0, 
                         NAS_ERABM_GET_MSG_LENGTH(pstRabmTcSuspendInd));

    /*填写消息头*/
    NAS_ERABM_WRITE_TC_MSG_HEAD(pstRabmTcSuspendInd, ID_ETC_ERABM_SUSPEND_IND);

    /*调用消息发送函数 */
    NAS_ERABM_SND_MSG(pstRabmTcSuspendInd);
}

/*****************************************************************************
 Function Name   : NAS_ERABM_SndRabmTcResumeInd
 Description     : ERABM模块向ETC发送ID_ETC_ERABM_RESUME_IND消息
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2011-05-03  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ERABM_SndRabmTcResumeInd( VOS_VOID )
{
    ETC_ERABM_RESUME_IND_STRU            *pstRabmTcResumeInd  = VOS_NULL_PTR;

    /*分配空间并检验分配是否成功*/
    pstRabmTcResumeInd = (VOS_VOID*)NAS_ERABM_ALLOC_MSG(sizeof(ETC_ERABM_RESUME_IND_STRU));

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pstRabmTcResumeInd)
    {
        /*打印异常信息*/
        NAS_ERABM_ERR_LOG("NAS_ERABM_SndRabmTcResumeInd:ERROR:Alloc Msg fail!");
        return ;
    }

    /*清空*/
    NAS_ERABM_MEM_SET_S( NAS_ERABM_GET_MSG_ENTITY(pstRabmTcResumeInd),
                         NAS_ERABM_GET_MSG_LENGTH(pstRabmTcResumeInd), 
                         0, 
                         NAS_ERABM_GET_MSG_LENGTH(pstRabmTcResumeInd));

    /*填写消息头*/
    NAS_ERABM_WRITE_TC_MSG_HEAD(pstRabmTcResumeInd, ID_ETC_ERABM_RESUME_IND);

    /*调用消息发送函数 */
    NAS_ERABM_SND_MSG(pstRabmTcResumeInd);
}
/*lint +e961*/
/*lint +e960*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

