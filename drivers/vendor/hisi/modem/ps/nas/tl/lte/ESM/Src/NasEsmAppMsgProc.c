/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasEsmAppMsgProc.c
    Description : 处理APP发给SM的承载处理类消息
    History     :
     1.丁丽 00128736        2008-09-01  Draft Enact
     2.祝义强 00138739      2008-09-10
     3.丁丽 00128736        2008-10-14  Modify
     4.刘文宇 00143951      2008-11-27  Modify BA8D00624
     5.刘文宇 00143951      2008-12-01  Modify BA8D00627
     6.刘文宇 00143951      2008-12-02  Modify BA8D00627
     7.杨茜惠 00135146      2008-12-18  Modify BA8D00749
     8.杨茜惠 00135146      2008-12-18  Modify BA8D00752
     9.孙兵 49683           2009-01-06  Modify BA8D00870
     10.杨茜惠 00135146     2009-03-06  Modify BA8D01127
******************************************************************************/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasEsmInclude.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASESMAPPMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASESMAPPMSGPROC_C
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
extern APP_ESM_DT_STRU          g_stEsmDtInfo;



/*****************************************************************************
  3 Function
*****************************************************************************/



/*****************************************************************************
 Function Name  : Sm_AppMsgProc()
 Description    : SM模块APP消息处理函数
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.丁丽 00128736       2008-09-01  Draft Enact
      2.祝义强 00138739     2008-09-10

*****************************************************************************/
VOS_VOID NAS_ESM_AppMsgDistr( VOS_VOID *pRcvMsg )
{
    APP_PS_MSG_HEADER_STRU                *pAppMsg;

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_AppMsgDistr is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppMsgDistr_ENUM, LNAS_ENTRY);

    pAppMsg = (APP_PS_MSG_HEADER_STRU*)pRcvMsg;

    /*根据消息名，调用相应的消息处理函数*/
    switch(pAppMsg->ulMsgId)
    {
        /*如果收到APP参数设置消息*/
        case ID_APP_ESM_SET_TFT_REQ:
        case ID_APP_ESM_SET_QOS_REQ:
        case ID_APP_ESM_SET_EPS_QOS_REQ:
        case ID_APP_ESM_SET_APN_REQ:
        case ID_APP_ESM_SET_PCO_REQ:
        case ID_APP_ESM_SET_PDN_TYPE_REQ:
        case ID_APP_ESM_SET_BEARER_TYPE_REQ:
        case ID_APP_ESM_SET_PDP_MANAGER_TYPE_REQ:
        case ID_APP_ESM_SET_GW_AUTH_REQ:
        case ID_APP_ESM_SET_CGDCONT_REQ:

            /*调用参数设置预处理函数*/
            NAS_ESM_AppParaSetMsgProc(pRcvMsg);
            break;

        /*如果收到APP参数查询消息*/
        case ID_APP_ESM_INQ_TFT_REQ:
        case ID_APP_ESM_INQ_QOS_REQ:
        case ID_APP_ESM_INQ_EPS_QOS_REQ:
        case ID_APP_ESM_INQ_APN_REQ:
        case ID_APP_ESM_INQ_PCO_REQ:
        case ID_APP_ESM_INQ_PDN_TYPE_REQ:
        case ID_APP_ESM_INQ_BEARER_TYPE_REQ:
        case ID_APP_ESM_INQ_PDP_MANAGER_TYPE_REQ:
        case ID_APP_ESM_INQ_DYNAMIC_PDP_CONT_REQ:
        case ID_APP_ESM_INQ_DYNAMIC_EPS_QOS_REQ:
        case ID_APP_ESM_INQ_DYNAMIC_TFT_REQ:
        case ID_APP_ESM_INQ_GW_AUTH_REQ:
            /*调用参数查询预处理函数*/
            NAS_ESM_AppParaQueryMsgProc(pRcvMsg);
            break;

        /*如果收到透明传输命令*/
        case OM_PS_TRANSPARENT_CMD_REQ:
            NAS_ESM_TransparentMsgProc(pRcvMsg);
            break;

        case ID_APP_ESM_IPV6_INFO_NOTIFY:

            /*调用参数设置函数*/
            NAS_ESM_AppIpv6InfoNotifyMsgProc(pRcvMsg);
            break;
        case ID_APP_ESM_PROCEDURE_ABORT_NOTIFY:
            /* 调用流程终止处理函数 */
            NAS_ESM_AppProcAbortNotifyProc(pRcvMsg);
            break;
        default:

            /*打印异常信息*/
            NAS_ESM_WARN_LOG("NAS_ESM_AppMsgDistr:Warning:APP->SM,Receive Abnormal Message!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppMsgDistr_ENUM, LNAS_MSG_INVALID);
            break;
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_SendPdnConReq
 Description     : 根据承载类型和当前Emm注册状态决定如何发送PDN连接请求或回复失败
 Input           : enBearerType    承载类型
                   pRcvMsg         接收到APP消息
 Output          : None
 Return          : None
 History         :
    1.liuhua    00212067       2012-10-25  Draft Enact

*****************************************************************************/
/*lint -e960*/
/*lint -e961*/
VOS_VOID NAS_ESM_SendPdnConReq(NAS_ESM_BEARER_TYPE_ENUM_UINT8 enBearerType, VOS_VOID *pRcvMsg)
{
    NAS_ESM_INFO_LOG2("NAS_ESM_SendPdnConReq entered:", enBearerType, NAS_ESM_GetEmmStatus());
    TLPS_PRINT2LAYER_INFO2(NAS_ESM_SendPdnConReq_ENUM, LNAS_ENTRY, enBearerType, NAS_ESM_GetEmmStatus());

    switch(NAS_ESM_GetEmmStatus())
    {
        case NAS_ESM_PS_REGISTER_STATUS_ATTACHED:
            if (PS_TRUE == NAS_ESM_IsDefaultEpsBearerType(enBearerType))
            {
                NAS_ESM_DefltAttMsgAppSdfSetupReq(pRcvMsg);
            }
            else
            {
                NAS_ESM_DedictdAttMsgAppSdfSetupReq(pRcvMsg);
            }
            break;
        case NAS_ESM_PS_REGISTER_STATUS_ATTACHING:
            if (NAS_ESM_BEARER_TYPE_EMERGENCY == enBearerType)
            {
                NAS_ESM_DefltDetMsgAppSdfSetupReq(pRcvMsg);
            }
            else
            {
                NAS_ESM_AppSdfSetupReqRefusedProc(pRcvMsg);
            }
            break;
        case NAS_ESM_PS_REGISTER_STATUS_DETACHED:
            if (PS_TRUE == NAS_ESM_IsDefaultEpsBearerType(enBearerType))
            {
                NAS_ESM_DefltDetMsgAppSdfSetupReq(pRcvMsg);
            }
            else
            {
                NAS_ESM_AppSdfSetupReqRefusedProc(pRcvMsg);
            }
            break;
        default:
            NAS_ESM_INFO_LOG("NAS_ESM_SendPdnConReq: invalid status");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_SendPdnConReq_ENUM, ESM_STATUS_ERROR);
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_SendNdisConnReq
 Description     : 根据Emm注册状态决定如何发送拨号连接请求或回复失败
 Input           : pRcvMsg         接收到APP消息
 Output          : None
 Return          : None
 History         :
    1.wangchen 00209181     2013-05-30  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_SendNdisConnReq(NAS_ESM_BEARER_TYPE_ENUM_UINT8 enBearerType,VOS_VOID *pRcvMsg)
{
    NAS_ESM_INFO_LOG1("NAS_ESM_SendNdisConnReq entered:",NAS_ESM_GetEmmStatus());
    TLPS_PRINT2LAYER_INFO1(NAS_ESM_SendNdisConnReq_ENUM, LNAS_ENTRY, NAS_ESM_GetEmmStatus());

    switch(NAS_ESM_GetEmmStatus())
    {
        case NAS_ESM_PS_REGISTER_STATUS_ATTACHED:
            NAS_ESM_DefltAttMsgAppNdisConnReq(pRcvMsg);

            break;
        case NAS_ESM_PS_REGISTER_STATUS_ATTACHING:
            if (NAS_ESM_BEARER_TYPE_EMERGENCY == enBearerType)
            {
                NAS_ESM_DefltDetMsgAppNidsConnReq(pRcvMsg);
            }
            else
            {
                NAS_ESM_AppNdisConnReqRefusedProc(pRcvMsg);
            }
            break;
        case NAS_ESM_PS_REGISTER_STATUS_DETACHED:
            NAS_ESM_DefltDetMsgAppNidsConnReq(pRcvMsg);

            break;
        default:
            NAS_ESM_INFO_LOG("NAS_ESM_SendNdisConnReq: invalid status");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_SendNdisConnReq_ENUM, ESM_STATUS_ERROR);
    }
}


/*****************************************************************************
 Function Name   : NAS_ESM_AppSdfSetupMsgProc
 Description     : 处理APP发起的承载建立请求消息
 Input           : VOS_VOID *pRcvMsg
 Output          : None
 Return          : VOS_VOID

 History         :
    1.zhuyiqiang 00138739      2008-9-11  Draft Enact
    2.dingli 00138739          2008-10-14 Modify
    3.sunbing 49683            2009-02-05 Modify
    4.lihong 00150010          2009-09-25 Modify
*****************************************************************************/
VOS_VOID NAS_ESM_AppSdfSetupMsgProc( VOS_VOID *pRcvMsg )
{
    VOS_UINT32                          ulEpsbId            = NAS_ESM_NULL;
    VOS_UINT32                          ulCidRecv           = NAS_ESM_NULL;
    VOS_UINT32                          ulOpId              = NAS_ESM_NULL;
    VOS_UINT32                          ulStateTblIndex     = NAS_ESM_NULL;
    VOS_UINT16                          usOriginalId        = NAS_ESM_NULL;
    VOS_UINT16                          usTerminalId        = NAS_ESM_NULL;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara          = VOS_NULL_PTR;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;
    APP_ESM_PDP_SETUP_REQ_STRU         *pAppMsg;
    NAS_ESM_APP_CNF_MSG_STRU            stEsmAppCnfMsg;
    VOS_UINT32                          ulVerifyRslt        = APP_SUCCESS;
    VOS_UINT32                          ulRslt              = NAS_ESM_FAILURE;
    NAS_BACKOFF_JUDGMENT_PARA_STRU      stJudgmentPara;

    pAppMsg = (APP_ESM_PDP_SETUP_REQ_STRU*)pRcvMsg;

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG2("NAS_ESM_AppSdfSetupMsgProc is entered.", pAppMsg->ulCid, pAppMsg->enSetupType);
    TLPS_PRINT2LAYER_INFO2(NAS_ESM_AppSdfSetupMsgProc_ENUM, LNAS_ENTRY, pAppMsg->ulCid, pAppMsg->enSetupType);

    /*取出消息中包含CID参数*/
    ulCidRecv=pAppMsg->ulCid;

    /*从消息中取出本次过程的ulOPID参数*/
    ulOpId=pAppMsg->ulOpId;

    /*从消息中取出MID参数*/
    usOriginalId = pAppMsg->usOriginalId;
    usTerminalId = pAppMsg->usTerminalId;

    /*封装结构体pstEsmAppCnfMsg*/
    NAS_ESM_MEM_SET_S(  (VOS_VOID*)&stEsmAppCnfMsg,
                        sizeof(NAS_ESM_APP_CNF_MSG_STRU),
                        0,
                        sizeof(NAS_ESM_APP_CNF_MSG_STRU));

    stEsmAppCnfMsg.bitOpEpsbId = NAS_ESM_OP_FALSE;
    stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_FALSE;
    stEsmAppCnfMsg.bitOpCId = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.bitOpOpId = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.bitOpMid = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.ulRst = NAS_ESM_FAILURE;
    stEsmAppCnfMsg.ulCId = ulCidRecv;
    stEsmAppCnfMsg.ulOpId= ulOpId;
    stEsmAppCnfMsg.usOriginalId = usOriginalId;
    stEsmAppCnfMsg.usTerminalId = usTerminalId;

    if (NAS_ESM_L_MODE_STATUS_NORMAL != NAS_ESM_GetLModeStatus())
    {
        NAS_ESM_WARN_LOG("NAS_ESM_AppSdfSetupMsgProc: L mode is already suspended!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppSdfSetupMsgProc_ENUM, LNAS_EMM_LTE_SUSPEND);

        /*封装结构体pstEsmAppCnfMsg*/
        stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
        stEsmAppCnfMsg.ulErrorCode = APP_ERR_SM_SUSPENDED;

        /*ESM 向APP返回ID_APP_ESM_PDP_SETUP_CNF消息，通告建立失败*/
        /*lint -e433*/
        NAS_ESM_SndEsmAppSdfSetupCnfMsg(&stEsmAppCnfMsg);
        /*lint +e433*/
        return ;
    }
    /*判断PPP拨号场景及参数合法性 */
    ulVerifyRslt = NAS_ESM_VerifyAppPppDialSceneAndParam(pRcvMsg);
    if(ulVerifyRslt != APP_SUCCESS)
    {
        /*封装结构体pstEsmAppCnfMsg*/
        stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
        stEsmAppCnfMsg.ulErrorCode = ulVerifyRslt;

        /*ESM 向APP返回ID_APP_ESM_PDP_SETUP_CNF消息，通告建立失败*/
        NAS_ESM_SndEsmAppSdfSetupCnfMsg(&stEsmAppCnfMsg);
        return;
    }

    /*如果ulCidRecv参数非法*/
    if (ulCidRecv >= NAS_ESM_MAX_UE_CONTRUL_CID_NUM)
    {
        /*打印异常消息*/
        NAS_ESM_WARN_LOG("NAS_ESM_AppSdfSetupMsgProc:Warning: Cid is illegal!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppSdfSetupMsgProc_ENUM, ESM_CID_ERROR);

        /*封装结构体pstEsmAppCnfMsg*/
        stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
        stEsmAppCnfMsg.ulErrorCode = APP_ERR_SM_CALL_CID_INVALID;

        /*ESM 向APP返回ID_APP_ESM_PDP_SETUP_CNF消息，通告建立失败*/
        /*调用函数发送APP消息*/
        NAS_ESM_SndEsmAppSdfSetupCnfMsg(&stEsmAppCnfMsg);
        return;
    }

    /*查询静态表，是否有关联的EpsbId，如果有，则回复建立成功*/
    if(NAS_ESM_SUCCESS == NAS_ESM_QueryEpsbCntxtTblByCid(ulCidRecv,&ulEpsbId))
    {
        NAS_ESM_INFO_LOG("NAS_ESM_AppSdfSetupMsgProc is entered.111");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_AppSdfSetupMsgProc_ENUM, 3);

        /*返回承载建立成功消息*/
        stEsmAppCnfMsg.bitOpEpsbId = NAS_ESM_OP_TRUE;
        stEsmAppCnfMsg.ulEpsbId =ulEpsbId;
        stEsmAppCnfMsg.ulRst = NAS_ESM_SUCCESS;

        /*ESM 向APP返回ID_APP_ESM_PDP_SETUP_CNF消息，通告建立成功*/
        NAS_ESM_SndEsmAppSdfSetupCnfMsg(&stEsmAppCnfMsg);
        return;
    }

    /* 如果存在已经建立或正在建立的紧急PDN连接，则不能再发起紧急PDN连接请求*/
    pstSdfPara = NAS_ESM_GetSdfParaAddr(ulCidRecv);
    if ((APP_ESM_BEARER_TYPE_EMERGENCY == pstSdfPara->enBearerCntxtType) &&
        (PS_TRUE == NAS_ESM_HasEmergencyPdn()))
    {
        /*打印异常消息*/
        NAS_ESM_INFO_LOG("NAS_ESM_AppSdfSetupMsgProc: only one emergency PDN allowed");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_AppSdfSetupMsgProc_ENUM, 4);

        /*封装结构体pstEsmAppCnfMsg*/
        stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
        stEsmAppCnfMsg.ulErrorCode = APP_ERR_SM_MULTI_EMERGENCY_NOT_ALLOWED;

        /*ESM 向APP返回ID_APP_ESM_PDP_SETUP_CNF消息，通告建立失败*/
        NAS_ESM_SndEsmAppSdfSetupCnfMsg(&stEsmAppCnfMsg);

        return;
    }

    /* 如果EMM正处于紧急注册状态或正在进行紧急注册，则不能再发起任何其他PDN连接请求*/
    if (PS_TRUE == NAS_ESM_IsEmmEmcAttachedOrAttaching())
    {
        /*打印异常消息*/
        NAS_ESM_INFO_LOG("NAS_ESM_AppSdfSetupMsgProc: any PDN not allowed when emergency attach");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_AppSdfSetupMsgProc_ENUM, 5);

        /*封装结构体pstEsmAppCnfMsg*/
        stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
        stEsmAppCnfMsg.ulErrorCode = APP_ERR_SM_NON_EMERGENCY_NOT_ALLOWED;

        /*ESM 向APP返回ID_APP_ESM_PDP_SETUP_CNF消息，通告建立失败*/
        NAS_ESM_SndEsmAppSdfSetupCnfMsg(&stEsmAppCnfMsg);

        return;
    }

    /* 缺省承载且有APN，Back-off算法判定，如果不允许发起，直接给APP回失败 */
    if((APP_ESM_BEARER_TYPE_DEFAULT == pstSdfPara->enBearerCntxtType)
        &&(NAS_ESM_OP_TRUE == pstSdfPara->bitOpApn))
    {
        NAS_ESM_MEM_SET_S(  &stJudgmentPara,
                            sizeof(NAS_BACKOFF_JUDGMENT_PARA_STRU),
                            0,
                            sizeof(NAS_BACKOFF_JUDGMENT_PARA_STRU));
        NAS_ESM_MEM_CPY_S(  &stJudgmentPara,
                            sizeof(APP_ESM_APN_INFO_STRU),
                            &pstSdfPara->stApnInfo,
                            sizeof(APP_ESM_APN_INFO_STRU));

        if(NAS_BACKOFF_SUCC != NAS_BACKOFF_OperateJudgment(NAS_BACKOFF_NETRAT_LTE, &stJudgmentPara))
        {
            /* 封装结构体pstEsmAppCnfMsg，给APP回失败 */
            stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
            stEsmAppCnfMsg.ulErrorCode    = APP_ERR_SM_BACKOFF_ALG_NOT_ALLOWED;
            NAS_ESM_SndEsmAppSdfSetupCnfMsg(&stEsmAppCnfMsg);
            return;
        }
    }

    /*在动态表中，获取过程标识*/
    if(NAS_ESM_FAILURE==NAS_ESM_GetStateTblIndexByCid(ulCidRecv,&ulStateTblIndex))
    {
        /*打印异常消息，状态表满或者该CID已经在表中*/
        NAS_ESM_WARN_LOG("NAS_ESM_AppSdfSetupMsgProc:Warning: Cid is dealing or resource is insufficient!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppSdfSetupMsgProc_ENUM, ESM_Cid_is_dealing_or_resource_is_insufficient);

        /*封装结构体pstEsmAppCnfMsg*/
        stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
        stEsmAppCnfMsg.ulErrorCode = APP_ERR_INSUFFICIENT_RESOURCES;

        /*ESM 向APP返回ID_APP_ESM_PDP_SETUP_CNF消息，通告建立失败*/
        NAS_ESM_SndEsmAppSdfSetupCnfMsg(&stEsmAppCnfMsg);

        return;
    }

    /*根据CID号码查找对应承载类型*/
    pstSdfPara = NAS_ESM_GetSdfParaAddr(ulCidRecv);

    ulRslt = NAS_ESM_AppNdisconnMsgCheckApnValid(pstSdfPara->bitOpPdnType,
                                                pstSdfPara->enPdnType,
                                                pstSdfPara->bitOpApn,
                                                &(pstSdfPara->stApnInfo),
                                                &stEsmAppCnfMsg);
    if(NAS_ESM_FAILURE == ulRslt)
    {
        /*当前使用的APN在50或者51或者66的拒绝列表中*/
        NAS_ESM_WARN_LOG("NAS_ESM_AppSdfSetupMsgProc:Warning: Rej Cause is 50/51/66!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppSdfSetupMsgProc_ENUM, 7);

        NAS_ESM_SndEsmAppSdfSetupCnfMsg(&stEsmAppCnfMsg);
        return;
    }

    /*设置APP消息记录的标识位*/
    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);
    pstStateAddr->bitOpAppMsgRecord = NAS_ESM_OP_TRUE;

    /*保存本次过程的ulOpId参数*/
    NAS_ESM_SaveAppOpId(ulStateTblIndex,ulOpId);

    /*保存本次过程的MID参数*/
    NAS_ESM_SaveAppMidHeader(ulStateTblIndex,usOriginalId,usTerminalId);

    /*保存收到的APP消息*/
    NAS_ESM_SaveAppMsgType(ulStateTblIndex,ID_APP_ESM_PDP_SETUP_REQ);

    /*设置承载状态和类别*/
    pstStateAddr->enBearerCntxtState = NAS_ESM_BEARER_STATE_INACTIVE;
    pstStateAddr->enBearerCntxtType = (VOS_UINT8)pstSdfPara->enBearerCntxtType;

    /*根据SDF属性和当前注册状态调用相应的处理函数*/
    NAS_ESM_SendPdnConReq(pstStateAddr->enBearerCntxtType, pRcvMsg);
}


/*****************************************************************************
 Function Name   : NAS_ESM_AppSdfReleaseMsgProc
 Description     : 处理APP请求承载释放消息
 Input           :VOS_VOID *pRcvMsg
 Output          : None
 Return          : VOS_VOID

 History         :
    1.zhuyiqiang 00138739      2008-9-11  Draft Enact
    2.dingli 00138739          2008-10-14 Modify
    3.sunbing 49683            2009-02-05 Modify
*****************************************************************************/
VOS_VOID NAS_ESM_AppSdfReleaseMsgProc( VOS_VOID *pRcvMsg )
{
    VOS_UINT32                          ulEpsbId            = NAS_ESM_NULL;
    VOS_UINT32                          ulCidRecv           = NAS_ESM_NULL;
    VOS_UINT32                          ulOpId              = NAS_ESM_NULL;
    VOS_UINT16                          usOriginalId        = NAS_ESM_NULL;
    VOS_UINT16                          usTerminalId        = NAS_ESM_NULL;
    VOS_UINT32                          ulStateTblIndex     = NAS_ESM_NULL;
    APP_ESM_PDP_RELEASE_REQ_STRU       *pAppMsg             = VOS_NULL_PTR;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstBearerCntxtInfo  = VOS_NULL_PTR;
    NAS_ESM_APP_CNF_MSG_STRU            stEsmAppCnfMsg;

    VOS_UINT32                          ulStateTblPdnDiscNum = 0;

    #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    VOS_UINT32                          ulIndex             = 0;
    #endif

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_AppSdfReleaseMsgProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppSdfReleaseMsgProc_ENUM, LNAS_ENTRY);

    pAppMsg=(APP_ESM_PDP_RELEASE_REQ_STRU*)pRcvMsg;

    /*取出消息中包含CID参数*/
    ulCidRecv = pAppMsg->ulCid;

    /*从消息中取出本次过程的ulOPID参数*/
    ulOpId=pAppMsg->ulOpId;

    /*从消息中取出MID参数*/
    usOriginalId = pAppMsg->usOriginalId;
    usTerminalId = pAppMsg->usTerminalId;

    /*封装结构体pstEsmAppCnfMsg*/
    NAS_ESM_MEM_SET_S(  (VOS_VOID*)&stEsmAppCnfMsg,
                        sizeof(NAS_ESM_APP_CNF_MSG_STRU),
                        0,
                        sizeof(NAS_ESM_APP_CNF_MSG_STRU));

    stEsmAppCnfMsg.bitOpEpsbId = NAS_ESM_OP_FALSE;
    stEsmAppCnfMsg.bitOpCId = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.bitOpOpId = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.bitOpMid = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.ulCId = ulCidRecv;
    stEsmAppCnfMsg.ulOpId = ulOpId;
    stEsmAppCnfMsg.usOriginalId = usOriginalId;
    stEsmAppCnfMsg.usTerminalId = usTerminalId;
    stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_FALSE;
    stEsmAppCnfMsg.ulRst = NAS_ESM_FAILURE;

    if (NAS_ESM_L_MODE_STATUS_NORMAL != NAS_ESM_GetLModeStatus())
    {
        NAS_ESM_WARN_LOG("NAS_ESM_AppSdfReleaseMsgProc: L mode is already suspended!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppSdfReleaseMsgProc_ENUM, LNAS_EMM_LTE_SUSPEND);

        /*封装结构体pstEsmAppCnfMsg*/
        stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
        stEsmAppCnfMsg.ulErrorCode = APP_ERR_SM_SUSPENDED;

        /*ESM 向APP返回APP_ESM_BEARER_RELEASE_CNF消息，通告删除失败*/
        NAS_ESM_SndEsmAppSdfRelCnfMsg(&stEsmAppCnfMsg);
        return ;
    }

    /*检查是否ulCidRecv合法*/
    if(ulCidRecv < NAS_ESM_MAX_CID_NUM)
    {
        /*检查CID号码是否与本地对应的EPS承载ulEpsbID关联，如果没有则回复释放成功*/
        if(NAS_ESM_FAILURE == NAS_ESM_QueryEpsbCntxtTblByCid(ulCidRecv,&ulEpsbId))
        {
            #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

            /* 本地无法找到LTE的承载，可能是EHRPD未恢复的承载，根据CID查找EHRPD的PDN实体中看是否存在 */
            if (NAS_ESM_SUCCESS == NAS_ESM_GetEhrpdPdnEntityIndexBasedCid(ulCidRecv, &ulIndex))
            {
                NAS_ESM_WaitHandoverEhrpdPdnRcvApsPdpReleaseProc(pAppMsg, ulIndex);
                return;
            }

            #endif

            /* 用此CID查找动态表，如果查找成功，则释放此动态表记录 */
            if(NAS_ESM_SUCCESS == NAS_ESM_QueryStateTblIndexByCid(ulCidRecv,&ulStateTblIndex))
            {
                /* 若是APP主动发起则回复失败消息 */
                NAS_ESM_SndEsmAppSdfSetupCnfFailMsg(ulStateTblIndex,\
                                         NAS_ESM_GetAppErrorByEsmCause(NAS_ESM_CAUSE_ERROR));

                /*释放状态表资源*/
                NAS_ESM_RelStateTblResource(ulStateTblIndex);
            }

            /*ESM 向APP返回APP_ESM_BEARER_RELEASE_CNF消息，告诉APP承载释放完成*/
            stEsmAppCnfMsg.ulRst = NAS_ESM_SUCCESS;
            NAS_ESM_SndEsmAppSdfRelCnfMsg(&stEsmAppCnfMsg);
            return;
        }

        #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

        /* 本地能找到LTE的承载，可能是EHRPD恢复过程中未收到EMM确认激活ACP发送成功的承载，
        根据CID查找EHRPD的PDN实体中看是否存在 */
        if (NAS_ESM_SUCCESS == NAS_ESM_GetEhrpdPdnEntityIndexBasedCid(ulCidRecv, &ulIndex))
        {
            NAS_ESM_EhrpdPdnHandoverSuccRcvApsPdpReleaseProc(pAppMsg, ulIndex);
        }
        #endif

        /*获取承载信息地址*/
        pstBearerCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);

        /* 查询动态表中正在执行的PDN去连接数 */
        ulStateTblPdnDiscNum = NAS_ESM_QueryPdnDisconnNumInStateTbl();

        /*如果去掉动态表中正在执行的PDN去连接数后，是最后一条PDN连接，UE拒绝发起PDN 去连接请求*/
        if((NAS_ESM_MIN_PDN_NUM >= (NAS_ESM_GetCurPdnNum()- ulStateTblPdnDiscNum))
            && (PS_TRUE == NAS_ESM_IsDefaultEpsBearerType(pstBearerCntxtInfo->enBearerCntxtType))
           )
        {
            /*打印异常消息*/
            NAS_ESM_WARN_LOG("NAS_ESM_AppSdfReleaseMsgProc:WARNING:The Last PDN CONNECT can not be disconnect!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppSdfReleaseMsgProc_ENUM, 1);

            /*ESM 向APP返回APP_ESM_BEARER_RELEASE_CNF消息，告诉APP承载释放失败
                    原因值为:NAS_ESM_CAUSE_LAST_PDN_DISCONN_NOT_ALLOWED*/
            stEsmAppCnfMsg.ulRst = NAS_ESM_FAILURE;
            stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
            stEsmAppCnfMsg.ulErrorCode = NAS_ESM_GetAppErrorByEsmCause(NAS_ESM_CAUSE_LAST_PDN_DISCONN_NOT_ALLOWED);
            stEsmAppCnfMsg.bitOpEpsbId = NAS_ESM_OP_TRUE;
            stEsmAppCnfMsg.ulEpsbId = ulEpsbId ;

            NAS_ESM_SndEsmAppSdfRelCnfMsg(&stEsmAppCnfMsg);

            return ;
        }

        /*检查动态表中是否存在有流程与新激活的专有承载的ID相同*/
        if(NAS_ESM_SUCCESS == NAS_ESM_QueryStateTblIndexByEpsbId(ulEpsbId,
                                                                &ulStateTblIndex))
        {
            NAS_ESM_INFO_LOG("NAS_ESM_AppSdfReleaseMsgProc:Bearer is dealing!");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_AppSdfReleaseMsgProc_ENUM, 2);
            stEsmAppCnfMsg.ulRst = NAS_ESM_FAILURE;
            stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
            stEsmAppCnfMsg.ulErrorCode = APP_ERR_INSUFFICIENT_RESOURCES;

            NAS_ESM_SndEsmAppSdfRelCnfMsg(&stEsmAppCnfMsg);
            return;
        }

        /*在动态表中，获取过程标识Index*/
        if(NAS_ESM_FAILURE == NAS_ESM_GetStateTblIndexByCid(ulCidRecv,&ulStateTblIndex))
        {
            /*打印异常消息, 状态表满或者该CID已经在表中*/
            NAS_ESM_WARN_LOG("NAS_ESM_AppSdfReleaseMsgProc:Warning: Cid is dealing or resource is insufficient!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppSdfReleaseMsgProc_ENUM, ESM_Cid_is_dealing_or_resource_is_insufficient);

            /*ESM 向APP返回APP_ESM_BEARER_RELEASE_CNF消息，告诉APP承载释放失败
                    原因值为:APP_ERR_PS_INSUFFICIENT_RESOURCES*/
            stEsmAppCnfMsg.ulRst = NAS_ESM_FAILURE;
            stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
            stEsmAppCnfMsg.ulErrorCode = APP_ERR_INSUFFICIENT_RESOURCES;

            NAS_ESM_SndEsmAppSdfRelCnfMsg(&stEsmAppCnfMsg);

            return;
        }


        /*设置APP消息记录的标识位*/
        pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);
        pstStateAddr->bitOpAppMsgRecord = NAS_ESM_OP_TRUE;

        /*保存本次过程的ulOpId参数*/
        NAS_ESM_SaveAppOpId(ulStateTblIndex,ulOpId);

        /*保存本次过程的MID参数*/
        NAS_ESM_SaveAppMidHeader(ulStateTblIndex,usOriginalId,usTerminalId);

        /*保存收到的APP消息*/
        NAS_ESM_SaveAppMsgType(ulStateTblIndex,ID_APP_ESM_PDP_RELEASE_REQ);

        /*设置承载状态和类别、关联承载信息*/
        pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);
        pstStateAddr->ulEpsbId           = ulEpsbId;
        pstStateAddr->enBearerCntxtState = NAS_ESM_GetBearCntxtState(ulEpsbId);
        pstStateAddr->enBearerCntxtType  = NAS_ESM_GetBearCntxtType(ulEpsbId);
        pstStateAddr->ulLinkedEpsbId     = pstBearerCntxtInfo->ulLinkedEpsbId;

        if (PS_TRUE == NAS_ESM_IsDefaultEpsBearerType(pstStateAddr->enBearerCntxtType))
        {
            NAS_ESM_DefltAttMsgAppSdfRelReq(pRcvMsg);
        }
        else
        {
            NAS_ESM_DedictdAttMsgAppSdfRelReq(pRcvMsg);
        }

    }
    else
    {
        NAS_ESM_WARN_LOG("NAS_ESM_AppSdfReleaseMsgProc:Warning: Cid is illegal!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppSdfReleaseMsgProc_ENUM, ESM_CID_ERROR);

        /*ESM 向APP返回APP_ESM_BEARER_RELEASE_CNF消息，告诉APP承载释放失败
                            原因值为:APP_ERR_PS_CALL_CID_INVALID*/
        stEsmAppCnfMsg.ulRst = NAS_ESM_FAILURE;
        stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
        stEsmAppCnfMsg.ulErrorCode = APP_ERR_SM_CALL_CID_INVALID;

        NAS_ESM_SndEsmAppSdfRelCnfMsg(&stEsmAppCnfMsg);
    }
}


/*****************************************************************************
 Function Name   : NAS_ESM_AppSdfReleaseMsgProc
 Description     : 处理APP请求承载修改消息
 Input           : VOS_VOID *pRcvMsg
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunbing49683      2008-9-11  Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_AppSdfModifyMsgProc( VOS_VOID *pRcvMsg )
{
    VOS_UINT32                          ulEpsbId            = NAS_ESM_NULL;
    VOS_UINT32                          ulCidRecv           = NAS_ESM_NULL;
    VOS_UINT32                          ulOpId              = NAS_ESM_NULL;
    VOS_UINT16                          usOriginalId        = NAS_ESM_NULL;
    VOS_UINT16                          usTerminalId        = NAS_ESM_NULL;
    VOS_UINT32                          ulStateTblIndex     = NAS_ESM_NULL;
    APP_ESM_PDP_MODIFY_REQ_STRU        *pAppMsg             = VOS_NULL_PTR;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstBearerCntxtInfo  = VOS_NULL_PTR;
    NAS_ESM_APP_CNF_MSG_STRU            stEsmAppCnfMsg;

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_AppSdfModifyMsgProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppSdfModifyMsgProc_ENUM, LNAS_ENTRY);

    pAppMsg=(APP_ESM_PDP_MODIFY_REQ_STRU*)pRcvMsg;

    /*取出消息中包含CID参数*/
    ulCidRecv = pAppMsg->ulCid;

    /*从消息中取出本次过程的ulOPID参数*/
    ulOpId=pAppMsg->ulOpId;

    /*从消息中取出MID参数*/
    usOriginalId = pAppMsg->usOriginalId;
    usTerminalId = pAppMsg->usTerminalId;

    /*封装结构体pstEsmAppCnfMsg*/
    NAS_ESM_MEM_SET_S(  (VOS_VOID*)&stEsmAppCnfMsg,
                        sizeof(NAS_ESM_APP_CNF_MSG_STRU),
                        0,
                        sizeof(NAS_ESM_APP_CNF_MSG_STRU));

    stEsmAppCnfMsg.bitOpEpsbId = NAS_ESM_OP_FALSE;
    stEsmAppCnfMsg.bitOpCId = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.bitOpOpId = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.bitOpMid = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.ulCId = ulCidRecv;
    stEsmAppCnfMsg.ulOpId = ulOpId;
    stEsmAppCnfMsg.usOriginalId = usOriginalId;
    stEsmAppCnfMsg.usTerminalId = usTerminalId;

    stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_FALSE;
    stEsmAppCnfMsg.ulRst = NAS_ESM_FAILURE;

    if (NAS_ESM_L_MODE_STATUS_NORMAL != NAS_ESM_GetLModeStatus())
    {
        NAS_ESM_WARN_LOG("NAS_ESM_SndEsmAppSdfModCnfMsg: L mode is already suspended!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppSdfModifyMsgProc_ENUM, LNAS_EMM_LTE_SUSPEND);

        /*封装结构体pstEsmAppCnfMsg*/
        stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
        stEsmAppCnfMsg.ulErrorCode = APP_ERR_SM_SUSPENDED;

        /*ESM 向APP返回ID_APP_ESM_PDP_MODIFY_CNF消息，通告修改失败*/
        NAS_ESM_SndEsmAppSdfModCnfMsg(&stEsmAppCnfMsg);
        return ;
    }

    /*检查是否ulCidRecv合法*/
    if(ulCidRecv < NAS_ESM_MAX_CID_NUM)
    {
        /*检查CID号码是否与本地对应的EPS承载ulEpsbID关联，如果没有则回复修改失败*/
        if(NAS_ESM_FAILURE == NAS_ESM_QueryEpsbCntxtTblByCid(ulCidRecv,&ulEpsbId))
        {

            stEsmAppCnfMsg.ulRst = NAS_ESM_FAILURE;
            stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
            stEsmAppCnfMsg.ulErrorCode = APP_ERR_SM_CALL_CID_NOT_MATCH_BEARER;

            NAS_ESM_SndEsmAppSdfModCnfMsg(&stEsmAppCnfMsg);

            return;
        }

        /*如果是紧急承载，则不支持修改操作*/
        if (APP_ESM_BEARER_TYPE_EMERGENCY == NAS_ESM_GetBearCntxtType(ulEpsbId))
        {
            NAS_ESM_INFO_LOG("NAS_ESM_AppSdfModifyMsgProc: modification for emergency not allowed");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_AppSdfModifyMsgProc_ENUM, 1);

            stEsmAppCnfMsg.ulRst = NAS_ESM_FAILURE;
            stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
            stEsmAppCnfMsg.ulErrorCode = APP_ERR_SM_MODIFY_EMERGENCY_NOT_ALLOWED;

            NAS_ESM_SndEsmAppSdfModCnfMsg(&stEsmAppCnfMsg);

            return;
        }

        /*判断承载类型，如果是缺省承载则回复错误*/
        if (PS_TRUE == NAS_ESM_IsDefaultEpsBearerType(NAS_ESM_GetBearCntxtType(ulEpsbId)))
        {
            stEsmAppCnfMsg.ulRst = NAS_ESM_FAILURE;
            stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
            stEsmAppCnfMsg.ulErrorCode = APP_ERR_SM_BEARER_TYPE_NOT_DEDICATED;

            NAS_ESM_SndEsmAppSdfModCnfMsg(&stEsmAppCnfMsg);

            return;
        }

        /*检查动态表中是否存在有流程与新激活的专有承载的ID相同*/
        if(NAS_ESM_SUCCESS == NAS_ESM_QueryStateTblIndexByEpsbId(ulEpsbId,
                                                                &ulStateTblIndex))
        {
            NAS_ESM_INFO_LOG("NAS_ESM_AppSdfModifyMsgProc:Bearer is dealing!");
            stEsmAppCnfMsg.ulRst = NAS_ESM_FAILURE;
            stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
            stEsmAppCnfMsg.ulErrorCode = APP_ERR_INSUFFICIENT_RESOURCES;

            NAS_ESM_SndEsmAppSdfModCnfMsg(&stEsmAppCnfMsg);
            return;
        }

        /*在动态表中，获取过程标识Index*/
        if(NAS_ESM_FAILURE == NAS_ESM_GetStateTblIndexByCid(ulCidRecv,&ulStateTblIndex))
        {/*获取失败，状态表满或者该CID已经在表中*/
            /*打印异常消息*/
            NAS_ESM_WARN_LOG("NAS_ESM_AppSdfReleaseMsgProc:Warning: Cid is dealing or resource is insufficient!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppSdfModifyMsgProc_ENUM, ESM_Cid_is_dealing_or_resource_is_insufficient);

            /*ESM 向APP返回APP_ESM_BEARER_RELEASE_CNF消息，告诉APP承载释放失败
                    原因值为:APP_ERR_PS_CALL_CID_INVALID*/
            stEsmAppCnfMsg.ulRst = NAS_ESM_FAILURE;
            stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
            stEsmAppCnfMsg.ulErrorCode = APP_ERR_INSUFFICIENT_RESOURCES;

            NAS_ESM_SndEsmAppSdfModCnfMsg(&stEsmAppCnfMsg);

            return;
        }

        /*获取承载信息地址*/
        pstBearerCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);

        /*设置APP消息记录的标识位*/
        pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);
        pstStateAddr->bitOpAppMsgRecord = NAS_ESM_OP_TRUE;

        /*保存本次过程的ulOpId参数*/
        NAS_ESM_SaveAppOpId(ulStateTblIndex,ulOpId);

        /*保存本次过程的MID参数*/
        NAS_ESM_SaveAppMidHeader(ulStateTblIndex,usOriginalId,usTerminalId);

        /*保存收到的APP消息*/
        NAS_ESM_SaveAppMsgType(ulStateTblIndex,ID_APP_ESM_PDP_MODIFY_REQ);

        /*设置承载状态和类别、关联承载信息*/
        pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);
        pstStateAddr->ulEpsbId           = ulEpsbId;
        pstStateAddr->enBearerCntxtState = NAS_ESM_GetBearCntxtState(ulEpsbId);
        pstStateAddr->enBearerCntxtType  = NAS_ESM_GetBearCntxtType(ulEpsbId);
        pstStateAddr->ulLinkedEpsbId     = pstBearerCntxtInfo->ulLinkedEpsbId;

        NAS_ESM_DedictdAttMsgAppSdfModifyReq(pRcvMsg);

    }
    else
    {
        NAS_ESM_WARN_LOG("NAS_ESM_AppSdfModifyMsgProc:Warning: Cid is illegal!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppSdfModifyMsgProc_ENUM, ESM_CID_ERROR);

        /*ESM 向APP返回APP_ESM_BEARER_MODIFY_CNF消息，告诉APP承载释放失败
                            原因值为:APP_ERR_PS_CALL_CID_INVALID*/
        stEsmAppCnfMsg.ulRst = NAS_ESM_FAILURE;
        stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
        stEsmAppCnfMsg.ulErrorCode = APP_ERR_SM_CALL_CID_INVALID;

        NAS_ESM_SndEsmAppSdfModCnfMsg(&stEsmAppCnfMsg);
    }
    return;
}

/*****************************************************************************
 Function Name   : NAS_ESM_AppPdpManageRspMsgProc
 Description     : 处理App回复的承载激活或承载修改的响应
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.liuwenyu00143951      2009-12-4  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_AppPdpManageRspMsgProc( VOS_VOID *pRcvMsg )
{
    APP_ESM_PDP_MANAGER_RSP_STRU     *pAppMsg             = VOS_NULL_PTR;
    VOS_UINT32                        ulStateTblIndex     = NAS_ESM_NULL;

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_AppPdpManageRspMsgProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppPdpManageRspMsgProc_ENUM, LNAS_ENTRY);

    if (NAS_ESM_L_MODE_STATUS_NORMAL != NAS_ESM_GetLModeStatus())
    {
        NAS_ESM_WARN_LOG("NAS_ESM_AppPdpManageRspMsgProc: L mode is already suspended!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppPdpManageRspMsgProc_ENUM, LNAS_EMM_LTE_SUSPEND);
        return ;
    }

    pAppMsg=(APP_ESM_PDP_MANAGER_RSP_STRU*)pRcvMsg;

    /*根据CID号码找到状态表的ulStateTblIndex*/
    if( NAS_ESM_FAILURE == NAS_ESM_QueryStateTblIndexByCid(pAppMsg->ulCid,
                                                           &ulStateTblIndex))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_AppPdpManageRspMsgProc:WARNING: Tbl index Query Fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppPdpManageRspMsgProc_ENUM, ESM_Tbl_index_Query_Fail);
        return;
    }

    NAS_ESM_TimerStop(ulStateTblIndex, TI_NAS_ESM_WAIT_APP_CNF);

    /* 根据用户的响应类型，采取相应的操作 */
    if (APP_ESM_BEARER_ACT_ACCEPT == pAppMsg->ulSetupRslt)
    {
        NAS_ESM_AppPdpManageRspMsgAcceptProc(ulStateTblIndex);
    }
    else
    {
        /* App拒绝承载激活或承载修改的处理 */
        NAS_ESM_AppPdpManageRspMsgRefuseProc(ulStateTblIndex);
    }

}

/*****************************************************************************
 Function Name   : NAS_ESM_GetAppNdisconnInfo
 Description     : 获取Ndisconninfo
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.x00253310      2014-05-09  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_GetAppNdisconnInfo(VOS_VOID *pRcvMsg)
{
    APP_ESM_NDISCONN_REQ_STRU          *pAppMsg     = VOS_NULL_PTR;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara  = VOS_NULL_PTR;

    pAppMsg = (APP_ESM_NDISCONN_REQ_STRU*)pRcvMsg;

    pstSdfPara = NAS_ESM_GetSdfParaAddr(pAppMsg->ulCid);

    if (APP_ESM_PDP_FOR_EMC == pAppMsg->enEmergencyInd)
    {
        pstSdfPara->enBearerCntxtType = APP_ESM_BEARER_TYPE_EMERGENCY;
    }
    else
    {
        pstSdfPara->enBearerCntxtType = APP_ESM_BEARER_TYPE_DEFAULT;
    }


    if (NAS_ESM_OP_TRUE == pAppMsg->bitOpPcscfDiscovery)
    {
        pstSdfPara->bitOpPcscfDiscovery = NAS_ESM_OP_TRUE;
        pstSdfPara->enPcscfDiscovery = pAppMsg->enPcscfDiscovery;
    }
    else
    {
        pstSdfPara->bitOpPcscfDiscovery = NAS_ESM_OP_FALSE;
    }

    if (NAS_ESM_OP_TRUE == pAppMsg->bitOpImCnSignalFlg)
    {
        pstSdfPara->bitOpImsCnSignalFlag = NAS_ESM_OP_TRUE;
        pstSdfPara->enImsCnSignalFlag = pAppMsg->enImCnSignalFlg;
    }
    else
    {
        pstSdfPara->bitOpImsCnSignalFlag = NAS_ESM_OP_FALSE;
    }
}


#if 0
/*****************************************************************************
 Function Name   : NAS_ESM_AppNdisconnMsgProc
 Description     : 处理App发送的拨号消息
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.wangchen 00209181     2013-05-29  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_ESM_SaveAppNdisconnInfo
(
    APP_ESM_NDISCONN_REQ_STRU           *pAppMsg ,
    NAS_ESM_APP_CNF_MSG_STRU            *pstEsmAppCnfMsg
)
{
    VOS_UINT32                          ulRslt              = NAS_ESM_NULL;

    if (NAS_ESM_OP_TRUE == pAppMsg->bitOpApn)
    {
        ulRslt = NAS_ESM_AppCgdcontOrNdisConnSetApn(pAppMsg->ulCid,
                                                    APP_ESM_PARA_SETTING,
                                                    pAppMsg->stApnInfo);
        if (APP_SUCCESS != ulRslt)
        {
            NAS_ESM_LOG1("NAS_ESM_AppNdisconnMsgProc: APN ERROR, ", ulRslt);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_AppNdisconnMsgProc_ENUM, ESM_APN_ERROR, ulRslt);

            /*封装结构体pstEsmAppCnfMsg*/
            pstEsmAppCnfMsg->bitOpErrorCode = NAS_ESM_OP_TRUE;
            pstEsmAppCnfMsg->ulErrorCode = ulRslt;

            /*ESM 向APP返回ID_APP_ESM_NDISCONN_CNF消息，通告建立失败*/
            /*lint -e433*/
            NAS_ESM_SndEsmAppNdisConnCnfMsg(pstEsmAppCnfMsg);
            /*lint +e433*/
            return NAS_ESM_FAILURE;
        }
    }

    if (NAS_ESM_OP_TRUE == pAppMsg->bitOpGwAuth)
    {
        ulRslt = NAS_ESM_AppNdisConnSetGwAuthInfo(pAppMsg);
        if (APP_SUCCESS != ulRslt)
        {
            NAS_ESM_LOG1("NAS_ESM_AppNdisconnMsgProc: GwAuth ERROR, ", ulRslt);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_AppNdisconnMsgProc_ENUM, LNAS_ERROR, ulRslt);

            /*封装结构体pstEsmAppCnfMsg*/
            pstEsmAppCnfMsg->bitOpErrorCode = NAS_ESM_OP_TRUE;
            pstEsmAppCnfMsg->ulErrorCode = ulRslt;

            /*ESM 向APP返回ID_APP_ESM_NDISCONN_CNF消息，通告建立失败*/
            /*lint -e433*/
            NAS_ESM_SndEsmAppNdisConnCnfMsg(pstEsmAppCnfMsg);
            /*lint +e433*/
            return NAS_ESM_FAILURE;
        }
    }

    if (NAS_ESM_OP_TRUE == pAppMsg->bitOpPdnType)
    {
        ulRslt = NAS_ESM_AppCgdconntOrNDISconnSetPdnType(pAppMsg->ulCid,
                                                        APP_ESM_PARA_SETTING,
                                                        pAppMsg->enPdnType,
                                                        pAppMsg->bitOpIpv4AddrAlloc,
                                                        pAppMsg->enIpv4AddrAlloc);

        if (APP_SUCCESS != ulRslt)
        {
            NAS_ESM_LOG1("NAS_ESM_AppNdisconnMsgProc: Pdn ERROR, ", ulRslt);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_AppNdisconnMsgProc_ENUM, ESM_PDN_TYPE_ERROR, ulRslt);
            /*封装结构体pstEsmAppCnfMsg*/
            pstEsmAppCnfMsg->bitOpErrorCode = NAS_ESM_OP_TRUE;
            pstEsmAppCnfMsg->ulErrorCode = ulRslt;

            /*ESM 向APP返回ID_APP_ESM_NDISCONN_CNF消息，通告建立失败*/
            /*lint -e433*/
            NAS_ESM_SndEsmAppNdisConnCnfMsg(pstEsmAppCnfMsg);
            /*lint +e433*/
            return NAS_ESM_FAILURE;
        }
    }
    return NAS_ESM_SUCCESS;
}
#endif

/*****************************************************************************
 Function Name   : NAS_ESM_AppNdisconnMsgProc
 Description     : 处理App发送的拨号消息
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.wangchen 00209181     2013-05-29  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_ESM_AppNdisconnMsgCheckApnValid
(
    VOS_UINT32                           ulBitOpPdnType,
    APP_ESM_PDN_TYPE_ENUM_UINT32        enPdnType,
    VOS_UINT32                           ulBitOpApnInfo,
    const APP_ESM_APN_INFO_STRU         *pstApnInfo,
    NAS_ESM_APP_CNF_MSG_STRU            *pstEsmAppCnfMsg
)
{
    if (ESM_EMM_RELEASE_R11 <= NAS_EMM_GetNasRelease())
    {
        if (NAS_ESM_OP_FALSE == ulBitOpPdnType)
        {
             /*打印异常消息 */
            NAS_ESM_WARN_LOG("NAS_ESM_AppNdisconnMsgCheckApnValid:Warning: PND INFO is not exist!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppNdisconnMsgCheckApnValid_ENUM, ESM_PDN_TYPE_ERROR);
            return NAS_ESM_SUCCESS;
        }

        /* 如果当前使用的APN在#50拒绝列表中，直接回复失败 */
        if (VOS_TRUE == NAS_ESM_IsCurrentApnHas50Rej(enPdnType,ulBitOpApnInfo,pstApnInfo))
        {
            /*打印异常消息，该APN被#50拒绝过，不允许再发起 */
            NAS_ESM_WARN_LOG("NAS_ESM_AppNdisconnMsgProc:Warning: Cid is Rej #50!");
            TLPS_PRINT2LAYER_WARNING1(NAS_ESM_AppNdisconnMsgCheckApnValid_ENUM, ESM_CID_IS_REJ, 50);

            /*封装结构体pstEsmAppCnfMsg*/
            pstEsmAppCnfMsg->bitOpErrorCode = NAS_ESM_OP_TRUE;
            pstEsmAppCnfMsg->ulErrorCode = NAS_ESM_GetAppErrorByEsmCause(NAS_ESM_CAUSE_PDNTYPE_IPV4_ONLY_ALLOWED);

            /*ESM 向APP返回ID_APP_ESM_NDISCONN_CNF消息，通告建立失败*/
            /*lint -e433*/
            //NAS_ESM_SndEsmAppNdisConnCnfMsg(pstEsmAppCnfMsg);
            /*lint +e433*/

            return NAS_ESM_FAILURE;
        }

        /* 如果当前使用的APN在#51拒绝列表中，直接回复失败 */
        if (VOS_TRUE == NAS_ESM_IsCurrentApnHas51Rej(enPdnType,ulBitOpApnInfo,pstApnInfo))
        {
            /*打印异常消息，该APN被#50拒绝过，不允许再发起 */
            NAS_ESM_WARN_LOG("NAS_ESM_AppNdisconnMsgProc:Warning: Cid is Rej #51!");
            TLPS_PRINT2LAYER_WARNING1(NAS_ESM_AppNdisconnMsgCheckApnValid_ENUM, ESM_CID_IS_REJ, 51);

            /*封装结构体pstEsmAppCnfMsg*/
            pstEsmAppCnfMsg->bitOpErrorCode = NAS_ESM_OP_TRUE;
            pstEsmAppCnfMsg->ulErrorCode = NAS_ESM_GetAppErrorByEsmCause(NAS_ESM_CAUSE_PDNTYPE_IPV6_ONLY_ALLOWED);

            /*ESM 向APP返回ID_APP_ESM_NDISCONN_CNF消息，通告建立失败*/
            /*lint -e433*/
            //NAS_ESM_SndEsmAppNdisConnCnfMsg(pstEsmAppCnfMsg);
            /*lint +e433*/

            return NAS_ESM_FAILURE;
        }

        if (VOS_TRUE == NAS_ESM_IsCurrentApnHas66Rej(ulBitOpApnInfo,pstApnInfo))
        {
            /*打印异常消息，该APN被#50拒绝过，不允许再发起 */
            NAS_ESM_WARN_LOG("NAS_ESM_AppNdisconnMsgProc:Warning: Cid is Rej #66!");
            TLPS_PRINT2LAYER_WARNING1(NAS_ESM_AppNdisconnMsgCheckApnValid_ENUM, ESM_CID_IS_REJ, 66);

            /*封装结构体pstEsmAppCnfMsg*/
            pstEsmAppCnfMsg->bitOpErrorCode = NAS_ESM_OP_TRUE;
            pstEsmAppCnfMsg->ulErrorCode = NAS_ESM_GetAppErrorByEsmCause(NAS_ESM_CAUSE_APN_NOT_SUPPORT_IN_CURRENT_RAT_AND_PLMN);

            /*ESM 向APP返回ID_APP_ESM_NDISCONN_CNF消息，通告建立失败*/
            /*lint -e433*/
            //NAS_ESM_SndEsmAppNdisConnCnfMsg(pstEsmAppCnfMsg);
            /*lint +e433*/

            return NAS_ESM_FAILURE;
        }
    }
    return NAS_ESM_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_AppNdisconnMsgProc
 Description     : 处理App发送的拨号消息
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.wangchen 00209181     2013-05-29  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_AppNdisconnMsgProc( VOS_VOID *pRcvMsg )
{
    VOS_UINT32                          ulEpsbId            = NAS_ESM_NULL;
    VOS_UINT32                          ulCidRecv           = NAS_ESM_NULL;
    VOS_UINT32                          ulOpId              = NAS_ESM_NULL;
    VOS_UINT32                          ulStateTblIndex     = NAS_ESM_NULL;
    VOS_UINT16                          usOriginalId        = NAS_ESM_NULL;
    VOS_UINT16                          usTerminalId        = NAS_ESM_NULL;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara          = VOS_NULL_PTR;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;
    APP_ESM_NDISCONN_REQ_STRU          *pAppMsg;
    NAS_ESM_APP_CNF_MSG_STRU            stEsmAppCnfMsg;
    NAS_BACKOFF_JUDGMENT_PARA_STRU      stJudgmentPara;

    pAppMsg = (APP_ESM_NDISCONN_REQ_STRU*)pRcvMsg;

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG1("NAS_ESM_AppNdisconnMsgProc is entered.", pAppMsg->ulCid);
    TLPS_PRINT2LAYER_INFO1(NAS_ESM_AppNdisconnMsgProc_ENUM, 1, pAppMsg->ulCid);

    /*取出消息中包含CID参数*/
    ulCidRecv=pAppMsg->ulCid;
    pstSdfPara = NAS_ESM_GetSdfParaAddr(ulCidRecv);

    /*从消息中取出本次过程的ulOPID参数*/
    ulOpId=pAppMsg->ulOpId;

    /*从消息中取出MID参数*/
    usOriginalId = pAppMsg->usOriginalId;
    usTerminalId = pAppMsg->usTerminalId;

    /*封装结构体pstEsmAppCnfMsg*/
    NAS_ESM_MEM_SET_S(  (VOS_VOID*)&stEsmAppCnfMsg,
                        sizeof(NAS_ESM_APP_CNF_MSG_STRU),
                        0,
                        sizeof(NAS_ESM_APP_CNF_MSG_STRU));

    stEsmAppCnfMsg.bitOpEpsbId = NAS_ESM_OP_FALSE;
    stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_FALSE;
    stEsmAppCnfMsg.bitOpCId = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.bitOpOpId = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.bitOpMid = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.ulRst = NAS_ESM_FAILURE;
    stEsmAppCnfMsg.ulCId = ulCidRecv;
    stEsmAppCnfMsg.ulOpId= ulOpId;
    stEsmAppCnfMsg.usOriginalId = usOriginalId;
    stEsmAppCnfMsg.usTerminalId = usTerminalId;

    /* 设置承载类型 */
    /*
    if ((APP_ESM_BEARER_TYPE_EMERGENCY != pstSdfPara->enBearerCntxtType)
        && (APP_ESM_BEARER_TYPE_DEFAULT != pstSdfPara->enBearerCntxtType))
    {
        pstSdfPara->enBearerCntxtType = APP_ESM_BEARER_TYPE_DEFAULT;
    }
    */
    NAS_ESM_GetAppNdisconnInfo(pRcvMsg);

    /* leixiantiao 00258641 降低圈复杂度 2014-7-30 */
    if(NAS_ESM_SUCCESS != NAS_ESM_SaveAppNdisConnInfo(pRcvMsg))
    {
        return;
    }

    if (NAS_ESM_L_MODE_STATUS_NORMAL != NAS_ESM_GetLModeStatus())
    {
        NAS_ESM_WARN_LOG("NAS_ESM_AppNdisconnMsgProc: L mode is already suspended!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppNdisconnMsgProc_ENUM, LNAS_EMM_LTE_SUSPEND);

        /*封装结构体pstEsmAppCnfMsg*/
        stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
        stEsmAppCnfMsg.ulErrorCode = APP_ERR_SM_SUSPENDED;

        /*ESM 向APP返回ID_APP_ESM_NDISCONN_CNF消息，通告建立失败*/
        /*lint -e433*/
        NAS_ESM_SndEsmAppNdisConnCnfMsg(&stEsmAppCnfMsg);
        /*lint +e433*/
        return ;
    }

    /*查询静态表，是否有关联的EpsbId，如果有，则回复建立成功*/
    if(NAS_ESM_SUCCESS == NAS_ESM_QueryEpsbCntxtTblByCid(ulCidRecv,&ulEpsbId))
    {
        NAS_ESM_INFO_LOG("NAS_ESM_AppNdisconnMsgProc is entered.111");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_AppNdisconnMsgProc_ENUM, 1);

        /*返回承载建立成功消息*/
        stEsmAppCnfMsg.bitOpEpsbId = NAS_ESM_OP_TRUE;
        stEsmAppCnfMsg.ulEpsbId =ulEpsbId;
        stEsmAppCnfMsg.ulRst = NAS_ESM_SUCCESS;

        /*ESM 向APP返回ID_APP_ESM_NDISCONN_CNF消息，通告建立成功 */
        /*lint -e433*/
        NAS_ESM_SndEsmAppNdisConnCnfMsg(&stEsmAppCnfMsg);
        /*lint +e433*/
        return;
    }

    /* 如果存在已经建立或正在建立的紧急PDN连接，则不能再发起紧急PDN连接请求*/
    if ((APP_ESM_BEARER_TYPE_EMERGENCY == pstSdfPara->enBearerCntxtType) &&
        (PS_TRUE == NAS_ESM_HasEmergencyPdn()))
    {
        /*打印异常消息*/
        NAS_ESM_INFO_LOG("NAS_ESM_AppSdfSetupMsgProc: only one emergency PDN allowed");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_AppNdisconnMsgProc_ENUM, 2);

        /*封装结构体pstEsmAppCnfMsg*/
        stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
        stEsmAppCnfMsg.ulErrorCode = APP_ERR_SM_MULTI_EMERGENCY_NOT_ALLOWED;

        /*ESM 向APP返回ID_APP_ESM_PDP_SETUP_CNF消息，通告建立失败*/
        NAS_ESM_SndEsmAppNdisConnCnfMsg(&stEsmAppCnfMsg);

        return;
    }

    /* 如果EMM正处于紧急注册状态或正在进行紧急注册，则不能再发起任何其他PDN连接请求*/
    if (PS_TRUE == NAS_ESM_IsEmmEmcAttachedOrAttaching())
    {
        /*打印异常消息*/
        NAS_ESM_INFO_LOG("NAS_ESM_AppSdfSetupMsgProc: any PDN not allowed when emergency attach");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_AppNdisconnMsgProc_ENUM, 3);

        /*封装结构体pstEsmAppCnfMsg*/
        stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
        stEsmAppCnfMsg.ulErrorCode = APP_ERR_SM_NON_EMERGENCY_NOT_ALLOWED;

        /*ESM 向APP返回ID_APP_ESM_PDP_SETUP_CNF消息，通告建立失败*/
        NAS_ESM_SndEsmAppNdisConnCnfMsg(&stEsmAppCnfMsg);

        return;
    }

    /* 缺省承载且有APN，Back-off算法判定是否允许发起PDN连接请求 */
    if((APP_ESM_BEARER_TYPE_DEFAULT == pstSdfPara->enBearerCntxtType)
        &&(NAS_ESM_OP_TRUE == pstSdfPara->bitOpApn))
    {
        NAS_ESM_MEM_SET_S(  &stJudgmentPara,
                            sizeof(NAS_BACKOFF_JUDGMENT_PARA_STRU),
                            0,
                            sizeof(NAS_BACKOFF_JUDGMENT_PARA_STRU));
        NAS_ESM_MEM_CPY_S(  &stJudgmentPara,
                            sizeof(APP_ESM_APN_INFO_STRU),
                            &pstSdfPara->stApnInfo,
                            sizeof(APP_ESM_APN_INFO_STRU));

        if(NAS_BACKOFF_SUCC != NAS_BACKOFF_OperateJudgment(NAS_BACKOFF_NETRAT_LTE, &stJudgmentPara))
        {
            /*封装结构体pstEsmAppCnfMsg，给APP回失败*/
            stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
            stEsmAppCnfMsg.ulErrorCode    = APP_ERR_SM_BACKOFF_ALG_NOT_ALLOWED;
            NAS_ESM_SndEsmAppNdisConnCnfMsg(&stEsmAppCnfMsg);
            return;
        }
    }

    /*在动态表中，获取过程标识*/
    if(NAS_ESM_FAILURE==NAS_ESM_GetStateTblIndexByCid(ulCidRecv,&ulStateTblIndex))
    {
        /*打印异常消息，状态表满或者该CID已经在表中*/
        NAS_ESM_WARN_LOG("NAS_ESM_AppNdisconnMsgProc:Warning: Cid is dealing or resource is insufficient!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppNdisconnMsgProc_ENUM, ESM_Cid_is_dealing_or_resource_is_insufficient);

        /*封装结构体pstEsmAppCnfMsg*/
        stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
        stEsmAppCnfMsg.ulErrorCode = APP_ERR_INSUFFICIENT_RESOURCES;

        /*ESM 向APP返回ID_APP_ESM_NDISCONN_CNF消息，通告建立失败*/
        /*lint -e433*/
        NAS_ESM_SndEsmAppNdisConnCnfMsg(&stEsmAppCnfMsg);
        /*lint +e433*/

        return;
    }

    if (NAS_ESM_FAILURE == NAS_ESM_AppNdisconnMsgCheckApnValid(pAppMsg->bitOpPdnType,
                                                                pAppMsg->enPdnType,
                                                                pAppMsg->bitOpApn,
                                                                &(pAppMsg->stApnInfo),
                                                                &stEsmAppCnfMsg))
    {
        NAS_ESM_SndEsmAppNdisConnCnfMsg(&stEsmAppCnfMsg);
        return;
    }

    /*设置APP消息记录的标识位*/
    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);
    pstStateAddr->bitOpAppMsgRecord = NAS_ESM_OP_TRUE;

    /*保存本次过程的ulOpId参数*/
    NAS_ESM_SaveAppOpId(ulStateTblIndex,ulOpId);

    /*保存本次过程的MID参数*/
    NAS_ESM_SaveAppMidHeader(ulStateTblIndex,usOriginalId,usTerminalId);

    /*保存收到的APP消息*/
    NAS_ESM_SaveAppMsgType(ulStateTblIndex,ID_APP_ESM_NDISCONN_REQ);

    /*设置承载状态和类别*/
    pstStateAddr->enBearerCntxtState = NAS_ESM_BEARER_STATE_INACTIVE;
    pstStateAddr->enBearerCntxtType = (VOS_UINT8)pstSdfPara->enBearerCntxtType;

    /*记录pdn请求类型*/
    if(APP_ESM_PDN_REQUEST_TYPE_HANDOVER == pAppMsg->enPdnReqestType)
    {
        pstStateAddr->enPdnReqType = NAS_ESM_PDN_REQ_TYPE_HANDOVER;
    }
    else
    {
        pstStateAddr->enPdnReqType = NAS_ESM_PDN_REQ_TYPE_INITIAL;
    }

    /*根据SDF属性和当前注册状态调用相应的处理函数*/
    NAS_ESM_SendNdisConnReq(pstStateAddr->enBearerCntxtType,pRcvMsg);
}

/*****************************************************************************
 Function Name  : NAS_ESM_DefltDetMsgAppNidsConnReq()
 Description    : 承载状态INACTIVE，PROCEDURE状态INACTIVE，APP->SM发送消息:
                    APP_ESM_BEARER_SETUP_REQ，SM->EMM发送:ID_EMM_ESM_EST_REQ;
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2013-06-03  Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_DefltDetMsgAppNidsConnReq(const VOS_VOID *pRcvMsg )
{
    VOS_UINT32                          ulPti               = NAS_ESM_NULL;
    VOS_UINT32                          ulCidRecv           = NAS_ESM_NULL;
    VOS_UINT32                          ulStateTblIndex     = NAS_ESM_NULL;
    APP_ESM_NDISCONN_REQ_STRU          *pstAppEsmSetupReqMsg= VOS_NULL_PTR;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;
    NAS_ESM_ENCODE_INFO_STRU            stEncodeInfo;


    pstAppEsmSetupReqMsg = (APP_ESM_NDISCONN_REQ_STRU *)pRcvMsg;


    /*打印进入该函数*/
    NAS_ESM_NORM_LOG("NAS_ESM_DefltDetMsgAppNidsConnReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_DefltDetMsgAppNidsConnReq_ENUM, LNAS_ENTRY);

    /*取出消息中包含CID参数*/
    ulCidRecv= pstAppEsmSetupReqMsg->ulCid;

    /*根据CID号码找到状态表的ulStateTblIndex*/
    if( NAS_ESM_FAILURE == NAS_ESM_QueryStateTblIndexByCid(ulCidRecv,&ulStateTblIndex))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_DefltDetMsgAppNidsConnReq:WARNING: Tbl index Query Fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_DefltDetMsgAppNidsConnReq_ENUM, ESM_Tbl_index_Query_Fail);
        return;
    }

    /*分配PTI，并存入承载信息中*/
    NAS_ESM_AssignPTI(&ulPti);
    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);
    pstStateAddr->stNwMsgRecord.ucPti = (VOS_UINT8)ulPti;

    /*填充NAS_ESM_ENCODE_INFO_STRU*/
    NAS_ESM_MEM_SET_S(  (VOS_VOID*)&stEncodeInfo,
                        sizeof(NAS_ESM_ENCODE_INFO_STRU),
                        0,
                        sizeof(NAS_ESM_ENCODE_INFO_STRU));

    stEncodeInfo.bitOpESMCau        = NAS_ESM_OP_FALSE;
    stEncodeInfo.ulCid              = pstStateAddr->ulCid;
    stEncodeInfo.ucPti              = (VOS_UINT8)ulPti;
    stEncodeInfo.ulEpsbId           = pstStateAddr->ulEpsbId;
    stEncodeInfo.enPdnReqType       = pstStateAddr->enPdnReqType;

    /*组装PDN_Connect_Req消息*/
    if( NAS_ESM_FAILURE == NAS_ESM_EncodePdnConReqMsg(stEncodeInfo, \
                                                      pstStateAddr->stNwMsgRecord.aucMsgBuff,\
                                                      &pstStateAddr->stNwMsgRecord.ulMsgLength))
    {
        NAS_ESM_LOG1("NAS_ESM_DefltDetMsgAppNidsConnReq:WARNING:EncodePdnConReqMsg fail!,ERROR =", APP_ERR_UNSPECIFIED_ERROR);
        TLPS_PRINT2LAYER_INFO1(NAS_ESM_DefltDetMsgAppNidsConnReq_ENUM, ESM_EncodePdnConReqMsg_fail, APP_ERR_UNSPECIFIED_ERROR);

        /*向APP回复APP_ESM_BEARER_SETUP_CNF(失败)消息*/
        NAS_ESM_SndEsmAppNdisConnCnfFailMsg(ulStateTblIndex, APP_ERR_UNSPECIFIED_ERROR);


        NAS_ESM_RelStateTblResource(ulStateTblIndex);

        return ;
    }

    /*记录空口消息类型*/
    pstStateAddr->bitOpNwMsgRecord = NAS_ESM_OP_TRUE;
    pstStateAddr->stNwMsgRecord.enEsmCnMsgType \
            = NAS_ESMCN_MSG_TYPE_PDN_CONNECT_REQ;

    /*设置是否为紧急PDN连接请求*/
    if (NAS_ESM_BEARER_TYPE_EMERGENCY == pstStateAddr->enBearerCntxtType)
    {
        pstStateAddr->stNwMsgRecord.ucIsEmcPdnReq = PS_TRUE;
    }
    else
    {
        pstStateAddr->stNwMsgRecord.ucIsEmcPdnReq = PS_FALSE;
    }

    pstStateAddr->stNwMsgRecord.ulOpId = NAS_ESM_AllocEmmEsmOpId();

    /*调用函数，SM向MM发送消息ID_EMM_ESM_EST_REQ*/
    NAS_ESM_SndEsmEmmEstReqMsg(pstStateAddr->stNwMsgRecord.ulOpId,
                               pstStateAddr->stNwMsgRecord.ucIsEmcPdnReq,
                               pstStateAddr->stNwMsgRecord.ulMsgLength,
                               pstStateAddr->stNwMsgRecord.aucMsgBuff);

    /* 记录空口消息 */
    NAS_ESM_SndAirMsgReportInd(pstStateAddr->stNwMsgRecord.aucMsgBuff,
                               pstStateAddr->stNwMsgRecord.ulMsgLength,
                               NAS_ESM_AIR_MSG_DIR_ENUM_UP,
                               ESM_PDN_CONNECT_REQ);

    /*状态转换*/
    NAS_ESM_SetEmmStatus(NAS_ESM_PS_REGISTER_STATUS_ATTACHING);
    NAS_ESM_SetProcTransState(ulStateTblIndex,NAS_ESM_BEARER_PROC_TRANS_STATE_PENDING);

}


/*****************************************************************************
 Function Name  : NAS_ESM_DefltDetMsgAppSdfSetupReq()
 Description    : 承载状态INACTIVE，PROCEDURE状态INACTIVE，APP->SM发送消息:
                    APP_ESM_BEARER_SETUP_REQ，SM->EMM发送:ID_EMM_ESM_EST_REQ;
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.祝义强 00138739       2008-09-10  Draft Enact
      2.sunbing 49683         2009-02-05   Modify
      3.liuwenyu 00143951     2009-09-08   Modify
*****************************************************************************/
VOS_VOID NAS_ESM_DefltDetMsgAppSdfSetupReq(const VOS_VOID *pRcvMsg )
{
    VOS_UINT32                          ulPti               = NAS_ESM_NULL;
    VOS_UINT32                          ulCidRecv           = NAS_ESM_NULL;
    VOS_UINT32                          ulStateTblIndex     = NAS_ESM_NULL;
    APP_ESM_PDP_SETUP_REQ_STRU         *pstAppEsmSetupReqMsg= VOS_NULL_PTR;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;
    NAS_ESM_ENCODE_INFO_STRU            stEncodeInfo;


    pstAppEsmSetupReqMsg = (APP_ESM_PDP_SETUP_REQ_STRU *)pRcvMsg;


    /*打印进入该函数*/
    NAS_ESM_NORM_LOG("NAS_ESM_DefltDetMsgAppSdfSetupReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_DefltDetMsgAppSdfSetupReq_ENUM, LNAS_ENTRY);

    /*取出消息中包含CID参数*/
    ulCidRecv= pstAppEsmSetupReqMsg->ulCid;

    /*根据CID号码找到状态表的ulStateTblIndex*/
    if( NAS_ESM_FAILURE == NAS_ESM_QueryStateTblIndexByCid(ulCidRecv,&ulStateTblIndex))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_DefltDetMsgAppSdfSetupReq:WARNING: Tbl index Query Fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_DefltDetMsgAppSdfSetupReq_ENUM, ESM_Tbl_index_Query_Fail);
        return;
    }

    /*分配PTI，并存入承载信息中*/
    NAS_ESM_AssignPTI(&ulPti);
    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);
    pstStateAddr->stNwMsgRecord.ucPti = (VOS_UINT8)ulPti;

    /*填充NAS_ESM_ENCODE_INFO_STRU*/
    NAS_ESM_MEM_SET_S(  (VOS_VOID*)&stEncodeInfo,
                        sizeof(NAS_ESM_ENCODE_INFO_STRU),
                        0,
                        sizeof(NAS_ESM_ENCODE_INFO_STRU));

    stEncodeInfo.bitOpESMCau        = NAS_ESM_OP_FALSE;
    stEncodeInfo.ulCid              = pstStateAddr->ulCid;
    stEncodeInfo.ucPti              = (VOS_UINT8)ulPti;
    stEncodeInfo.ulEpsbId           = pstStateAddr->ulEpsbId;
    stEncodeInfo.enPdnReqType       = pstStateAddr->enPdnReqType;

    /*组装PDN_Connect_Req消息*/
    if( NAS_ESM_FAILURE == NAS_ESM_EncodePdnConReqMsg(stEncodeInfo, \
                                                      pstStateAddr->stNwMsgRecord.aucMsgBuff,\
                                                      &pstStateAddr->stNwMsgRecord.ulMsgLength))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_DefltDetBInactPInactMsgAppBearSetupReq:WARNING:EncodePdnConReqMsg fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_DefltDetMsgAppSdfSetupReq_ENUM, ESM_EncodePdnConReqMsg_fail);

        /*向APP回复APP_ESM_BEARER_SETUP_CNF(失败)消息*/
        NAS_ESM_SndEsmAppSdfSetupCnfFailMsg(ulStateTblIndex, APP_ERR_UNSPECIFIED_ERROR);


        NAS_ESM_RelStateTblResource(ulStateTblIndex);

        return ;
    }

    /*记录空口消息类型*/
    pstStateAddr->bitOpNwMsgRecord = NAS_ESM_OP_TRUE;
    pstStateAddr->stNwMsgRecord.enEsmCnMsgType \
            = NAS_ESMCN_MSG_TYPE_PDN_CONNECT_REQ;

    /*设置是否为紧急PDN连接请求*/
    if (NAS_ESM_BEARER_TYPE_EMERGENCY == pstStateAddr->enBearerCntxtType)
    {
        pstStateAddr->stNwMsgRecord.ucIsEmcPdnReq = PS_TRUE;
    }
    else
    {
        pstStateAddr->stNwMsgRecord.ucIsEmcPdnReq = PS_FALSE;
    }

    pstStateAddr->stNwMsgRecord.ulOpId = NAS_ESM_AllocEmmEsmOpId();

    /*调用函数，SM向MM发送消息ID_EMM_ESM_EST_REQ*/
    NAS_ESM_SndEsmEmmEstReqMsg(pstStateAddr->stNwMsgRecord.ulOpId,
                               pstStateAddr->stNwMsgRecord.ucIsEmcPdnReq,
                               pstStateAddr->stNwMsgRecord.ulMsgLength,
                               pstStateAddr->stNwMsgRecord.aucMsgBuff);

    /* 记录空口消息 */
    NAS_ESM_SndAirMsgReportInd(pstStateAddr->stNwMsgRecord.aucMsgBuff,
                               pstStateAddr->stNwMsgRecord.ulMsgLength,
                               NAS_ESM_AIR_MSG_DIR_ENUM_UP,
                               ESM_PDN_CONNECT_REQ);

    /*状态转换*/
    NAS_ESM_SetEmmStatus(NAS_ESM_PS_REGISTER_STATUS_ATTACHING);
    NAS_ESM_SetProcTransState(ulStateTblIndex,NAS_ESM_BEARER_PROC_TRANS_STATE_PENDING);

}

/*****************************************************************************
 Function Name  : NAS_ESM_DefltAttMsgAppSdfSetupReq()
 Description    :
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.祝义强 00138739       2008-09-10  Draft Enact
      2.dingli 00138739       2008-10-14  Modify
      3.sunbing 49683         2009-02-05  Modify
*****************************************************************************/
VOS_VOID  NAS_ESM_DefltAttMsgAppSdfSetupReq(const VOS_VOID *pRcvMsg )
{
    VOS_UINT32                          ulCidRecv           = NAS_ESM_NULL;
    VOS_UINT32                          ulStateTblIndex     = NAS_ESM_NULL;
    VOS_UINT32                          ulPti               = NAS_ESM_NULL;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;
    NAS_ESM_ENCODE_INFO_STRU            stEncodeInfo;
    APP_ESM_PDP_SETUP_REQ_STRU         *pstAppEsmSetupReqMsg = VOS_NULL_PTR;

    /*打印进入该函数*/
    NAS_ESM_NORM_LOG("NAS_ESM_DefltAttMsgAppSdfSetupReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_DefltAttMsgAppSdfSetupReq_ENUM, LNAS_ENTRY);

    /*取出消息中包含CID参数*/

    ulCidRecv=((APP_ESM_PDP_SETUP_REQ_STRU*)pRcvMsg)->ulCid;
    pstAppEsmSetupReqMsg = (APP_ESM_PDP_SETUP_REQ_STRU*)pRcvMsg;


    /*根据CID号码找到状态表的ulStateTblIndex*/
    if( NAS_ESM_FAILURE == NAS_ESM_QueryStateTblIndexByCid(ulCidRecv,&ulStateTblIndex))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_DefltAttMsgAppSdfSetupReq:WARNING: Tbl index Query Fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_DefltAttMsgAppSdfSetupReq_ENUM, ESM_Tbl_index_Query_Fail);
        return;
    }

    /*分配PTI，并存入承载信息中*/
    NAS_ESM_AssignPTI(&ulPti);
    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);
    pstStateAddr->stNwMsgRecord.ucPti = (VOS_UINT8)ulPti;

    /*填充NAS_ESM_ENCODE_INFO_STRU*/
    NAS_ESM_MEM_SET_S(  (VOS_VOID*)&stEncodeInfo,
                        sizeof(NAS_ESM_ENCODE_INFO_STRU),
                        0,
                        sizeof(NAS_ESM_ENCODE_INFO_STRU));

    stEncodeInfo.bitOpESMCau        = NAS_ESM_OP_FALSE;
    stEncodeInfo.ulCid              = pstStateAddr->ulCid;
    stEncodeInfo.ucPti              = (VOS_UINT8)ulPti;
    stEncodeInfo.ulEpsbId           = pstStateAddr->ulEpsbId;
    stEncodeInfo.enPdnReqType       = pstStateAddr->enPdnReqType;

    if (APP_ESM_PDP_SETUP_TYPE_PPP == pstAppEsmSetupReqMsg->enSetupType)
    {

        /*组装PDN_Connect_Req消息*/
        if( NAS_ESM_FAILURE == NAS_ESM_EncodePdnConReqMsg_PPP(pstAppEsmSetupReqMsg,\
                                                          stEncodeInfo, \
                                                          pstStateAddr->stNwMsgRecord.aucMsgBuff,\
                                                          &pstStateAddr->stNwMsgRecord.ulMsgLength))
        {
            NAS_ESM_WARN_LOG("NAS_ESM_DefltDetBInactPInactMsgAppBearSetupReq:WARNING:NAS_ESM_EncodePdnConReqMsg_PPP fail!");
            TLPS_PRINT2LAYER_WARNING1(NAS_ESM_DefltAttMsgAppSdfSetupReq_ENUM, LNAS_FAIL, 2);

            /*向APP回复APP_ESM_BEARER_SETUP_CNF(失败)消息*/
            NAS_ESM_SndEsmAppSdfSetupCnfFailMsg(ulStateTblIndex, APP_ERR_UNSPECIFIED_ERROR);


            NAS_ESM_RelStateTblResource(ulStateTblIndex);

            return ;
        }
    }
    else
    {
        /*组装PDN_Connect_Req消息*/
        if( NAS_ESM_FAILURE == NAS_ESM_EncodePdnConReqMsg(stEncodeInfo, \
                                                          pstStateAddr->stNwMsgRecord.aucMsgBuff,\
                                                          &pstStateAddr->stNwMsgRecord.ulMsgLength))
        {
            NAS_ESM_WARN_LOG("NAS_ESM_DefltAttBInactPInactMsgAppBearSetupReq:WARNING:EncodePdnConReqMsg fail!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_DefltAttMsgAppSdfSetupReq_ENUM, ESM_EncodePdnConReqMsg_fail);

            /*向APP回复APP_ESM_BEARER_SETUP_CNF(失败)消息*/
            NAS_ESM_SndEsmAppSdfSetupCnfFailMsg(ulStateTblIndex, APP_ERR_UNSPECIFIED_ERROR);


            NAS_ESM_RelStateTblResource(ulStateTblIndex);

            return ;
        }
    }
    /*记录空口消息类型*/
    pstStateAddr->bitOpNwMsgRecord = NAS_ESM_OP_TRUE;
    pstStateAddr->stNwMsgRecord.enEsmCnMsgType \
            = NAS_ESMCN_MSG_TYPE_PDN_CONNECT_REQ;

    /*设置是否为紧急PDN连接请求*/
    if (NAS_ESM_BEARER_TYPE_EMERGENCY == pstStateAddr->enBearerCntxtType)
    {
        pstStateAddr->stNwMsgRecord.ucIsEmcPdnReq = PS_TRUE;
    }
    else
    {
        pstStateAddr->stNwMsgRecord.ucIsEmcPdnReq = PS_FALSE;
    }
    pstStateAddr->stNwMsgRecord.ulOpId = NAS_ESM_AllocEmmEsmOpId();
    #if (FEATURE_ON == FEATURE_DSDS)
    pstStateAddr->enEsmBearerDataCnf = NAS_ESM_BEARER_DATA_CNF_SENDING;
    NAS_ESM_SendBeginSessionNotify();
    #endif

    /*调用函数，SM->EMM发送消息:ID_EMM_ESM_DATA_REQ(NAS_ESMCN_MSG_TYPE_PDN_CONNECT_REQ)*/
    NAS_ESM_SndEsmEmmDataReqMsg(pstStateAddr->stNwMsgRecord.ulOpId,
                                pstStateAddr->stNwMsgRecord.ucIsEmcPdnReq,
                                pstStateAddr->stNwMsgRecord.ulMsgLength,
                                pstStateAddr->stNwMsgRecord.aucMsgBuff);

    /* 记录空口消息 */
    NAS_ESM_SndAirMsgReportInd(pstStateAddr->stNwMsgRecord.aucMsgBuff,
                               pstStateAddr->stNwMsgRecord.ulMsgLength,
                               NAS_ESM_AIR_MSG_DIR_ENUM_UP,
                               ESM_PDN_CONNECT_REQ);

    /*启动T3482定时器*/
    NAS_ESM_TimerStart(ulStateTblIndex,TI_NAS_ESM_T3482);

    /*状态转换*/
    NAS_ESM_SetProcTransState(ulStateTblIndex,NAS_ESM_BEARER_PROC_TRANS_STATE_PENDING);
}


VOS_VOID  NAS_ESM_DefltAttMsgAppNdisConnReq(const VOS_VOID *pRcvMsg )
{
    VOS_UINT32                          ulCidRecv           = NAS_ESM_NULL;
    VOS_UINT32                          ulStateTblIndex     = NAS_ESM_NULL;
    VOS_UINT32                          ulPti               = NAS_ESM_NULL;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;
    NAS_ESM_ENCODE_INFO_STRU            stEncodeInfo;

    /*打印进入该函数*/
    NAS_ESM_NORM_LOG("NAS_ESM_DefltAttMsgAppNdisConnReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_DefltAttMsgAppNdisConnReq_ENUM, LNAS_ENTRY);

    /*取出消息中包含CID参数*/

    ulCidRecv=((APP_ESM_NDISCONN_REQ_STRU*)pRcvMsg)->ulCid;


    /*根据CID号码找到状态表的ulStateTblIndex*/
    if( NAS_ESM_FAILURE == NAS_ESM_QueryStateTblIndexByCid(ulCidRecv,&ulStateTblIndex))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_DefltAttMsgAppNdisConnReq:WARNING: Tbl index Query Fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_DefltAttMsgAppNdisConnReq_ENUM, ESM_Tbl_index_Query_Fail);
        return;
    }

    /*分配PTI，并存入承载信息中*/
    NAS_ESM_AssignPTI(&ulPti);
    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);
    pstStateAddr->stNwMsgRecord.ucPti = (VOS_UINT8)ulPti;

    /*填充NAS_ESM_ENCODE_INFO_STRU*/
    NAS_ESM_MEM_SET_S(  (VOS_VOID*)&stEncodeInfo,
                        sizeof(NAS_ESM_ENCODE_INFO_STRU),
                        0,
                        sizeof(NAS_ESM_ENCODE_INFO_STRU));

    stEncodeInfo.bitOpESMCau        = NAS_ESM_OP_FALSE;
    stEncodeInfo.ulCid              = pstStateAddr->ulCid;
    stEncodeInfo.ucPti              = (VOS_UINT8)ulPti;
    stEncodeInfo.ulEpsbId           = pstStateAddr->ulEpsbId;
    stEncodeInfo.enPdnReqType       = pstStateAddr->enPdnReqType;

    /*组装PDN_Connect_Req消息*/
    if( NAS_ESM_FAILURE == NAS_ESM_EncodePdnConReqMsg(stEncodeInfo, \
                                                      pstStateAddr->stNwMsgRecord.aucMsgBuff,\
                                                      &pstStateAddr->stNwMsgRecord.ulMsgLength))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_DefltAttMsgAppNdisConnReq:WARNING:EncodePdnConReqMsg fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_DefltAttMsgAppNdisConnReq_ENUM, ESM_Tbl_index_Query_Fail);

        /*向APP回复APP_ESM_BEARER_SETUP_CNF(失败)消息*/
        NAS_ESM_SndEsmAppNdisConnCnfFailMsg(ulStateTblIndex, APP_ERR_UNSPECIFIED_ERROR);


        NAS_ESM_RelStateTblResource(ulStateTblIndex);

        return ;
    }

    /*记录空口消息类型*/
    pstStateAddr->bitOpNwMsgRecord = NAS_ESM_OP_TRUE;
    pstStateAddr->stNwMsgRecord.enEsmCnMsgType \
            = NAS_ESMCN_MSG_TYPE_PDN_CONNECT_REQ;


    /*设置是否为紧急PDN连接请求*/
    if (NAS_ESM_BEARER_TYPE_EMERGENCY == pstStateAddr->enBearerCntxtType)
    {
        pstStateAddr->stNwMsgRecord.ucIsEmcPdnReq = PS_TRUE;
    }
    else
    {
        pstStateAddr->stNwMsgRecord.ucIsEmcPdnReq = PS_FALSE;
    }

    pstStateAddr->stNwMsgRecord.ulOpId = NAS_ESM_AllocEmmEsmOpId();
    #if (FEATURE_ON == FEATURE_DSDS)
    pstStateAddr->enEsmBearerDataCnf = NAS_ESM_BEARER_DATA_CNF_SENDING;
    NAS_ESM_SendBeginSessionNotify();
    #endif

    /*调用函数，SM->EMM发送消息:ID_EMM_ESM_DATA_REQ(NAS_ESMCN_MSG_TYPE_PDN_CONNECT_REQ)*/
    NAS_ESM_SndEsmEmmDataReqMsg(pstStateAddr->stNwMsgRecord.ulOpId,
                                pstStateAddr->stNwMsgRecord.ucIsEmcPdnReq,
                                pstStateAddr->stNwMsgRecord.ulMsgLength,
                                pstStateAddr->stNwMsgRecord.aucMsgBuff);

    /* 记录空口消息 */
    NAS_ESM_SndAirMsgReportInd(pstStateAddr->stNwMsgRecord.aucMsgBuff,
                               pstStateAddr->stNwMsgRecord.ulMsgLength,
                               NAS_ESM_AIR_MSG_DIR_ENUM_UP,
                               ESM_PDN_CONNECT_REQ);

    /*启动T3482定时器*/
    NAS_ESM_TimerStart(ulStateTblIndex,TI_NAS_ESM_T3482);

    /*状态转换*/
    NAS_ESM_SetProcTransState(ulStateTblIndex,NAS_ESM_BEARER_PROC_TRANS_STATE_PENDING);
}


/*****************************************************************************
 Function Name  : NAS_ESM_DefltAttMsgAppSdfRelReq()
 Description    : 承载状态ACTIVE，PROCEDURE状态INACTIVE，APP->SM发送消息:
                    APP_ESM_BEARER_RELEASE_REQ，SM调用状态机；
                    SM->EMM发送:PDN DISCONNECT REQ;
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.祝义强 00138739       2008-09-10  Draft Enact
      2.sunbing 49683         2009-02-05   Modify
*****************************************************************************/
VOS_VOID  NAS_ESM_DefltAttMsgAppSdfRelReq(const VOS_VOID *pRcvMsg )
{
    VOS_UINT32                          ulStateTblIndex     = NAS_ESM_NULL;
    VOS_UINT32                          ulCidRecv           = NAS_ESM_NULL;
    VOS_UINT32                          ulPti               = NAS_ESM_NULL;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;
    NAS_ESM_ENCODE_INFO_STRU            stEncodeInfo;

    /*打印进入该函数*/
    NAS_ESM_NORM_LOG("NAS_ESM_DefltAttMsgAppSdfRelReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_DefltAttMsgAppSdfRelReq_ENUM, LNAS_ENTRY);

    /*取出消息中包含CID参数*/
    ulCidRecv=((APP_ESM_PDP_RELEASE_REQ_STRU*)pRcvMsg)->ulCid;

    /*根据CID号码找到状态表的ulStateTblIndex*/
    if( NAS_ESM_FAILURE == NAS_ESM_QueryStateTblIndexByCid(ulCidRecv,&ulStateTblIndex))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_DefltAttMsgAppSdfRelReq:WARNING: Tbl index Query Fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_DefltAttMsgAppSdfRelReq_ENUM, ESM_Tbl_index_Query_Fail);
        return;
    }

    /*分配PTI，并存入承载信息中*/
    NAS_ESM_AssignPTI(&ulPti);
    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);
    pstStateAddr->stNwMsgRecord.ucPti = (VOS_UINT8)ulPti;

    /*填充NAS_ESM_ENCODE_INFO_STRU*/
    NAS_ESM_MEM_SET_S(  (VOS_VOID*)&stEncodeInfo,
                        sizeof(NAS_ESM_ENCODE_INFO_STRU),
                        0,
                        sizeof(NAS_ESM_ENCODE_INFO_STRU));

    stEncodeInfo.bitOpESMCau        = NAS_ESM_OP_FALSE;
    stEncodeInfo.ulCid              = pstStateAddr->ulCid;
    stEncodeInfo.ucPti              = (VOS_UINT8)ulPti;
    stEncodeInfo.ulEpsbId           = pstStateAddr->ulEpsbId;

    /*组装PDN_Disconnect_Req消息*/
    if( NAS_ESM_FAILURE == NAS_ESM_EncodePdnDisconReqMsg(stEncodeInfo, \
                                                      pstStateAddr->stNwMsgRecord.aucMsgBuff,\
                                                      &pstStateAddr->stNwMsgRecord.ulMsgLength))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_DefltAttMsgAppSdfRelReq:WARNING:EncodePdnDisconReqMsg fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_DefltAttMsgAppSdfRelReq_ENUM, ESM_EncodePdnConReqMsg_fail);

        /*向APP回复APP_ESM_BEARER_RELEASE_CNF(失败)消息*/
        NAS_ESM_SndEsmAppSdfRelCnfFailMsg(ulStateTblIndex, APP_ERR_UNSPECIFIED_ERROR);

        NAS_ESM_RelStateTblResource(ulStateTblIndex);

        return ;
    }

    /*记录空口消息类型*/
    pstStateAddr->bitOpNwMsgRecord = NAS_ESM_OP_TRUE;
    pstStateAddr->stNwMsgRecord.enEsmCnMsgType \
            = NAS_ESMCN_MSG_TYPE_PDN_DISCONNECT_REQ;
    pstStateAddr->stNwMsgRecord.ucIsEmcPdnReq = PS_FALSE;

    pstStateAddr->stNwMsgRecord.ulOpId = NAS_ESM_AllocEmmEsmOpId();
    #if (FEATURE_ON == FEATURE_DSDS)
    pstStateAddr->enEsmBearerDataCnf = NAS_ESM_BEARER_DATA_CNF_SENDING;
    NAS_ESM_SendBeginSessionNotify();
    #endif

    /*调用函数，SM向MM发送消息ID_EMM_ESM_DATA_REQ（PDN DISCONNECT REQ）*/
    NAS_ESM_SndEsmEmmDataReqMsg(pstStateAddr->stNwMsgRecord.ulOpId,
                                pstStateAddr->stNwMsgRecord.ucIsEmcPdnReq,
                                pstStateAddr->stNwMsgRecord.ulMsgLength,
                                pstStateAddr->stNwMsgRecord.aucMsgBuff);

    /* 记录空口消息 */
    NAS_ESM_SndAirMsgReportInd(pstStateAddr->stNwMsgRecord.aucMsgBuff,
                               pstStateAddr->stNwMsgRecord.ulMsgLength,
                               NAS_ESM_AIR_MSG_DIR_ENUM_UP,
                               ESM_PDN_DISCONNECT_REQ);

    /*启动T3492定时器*/
    NAS_ESM_TimerStart(ulStateTblIndex,TI_NAS_ESM_T3492);

    /*状态转换*/
    NAS_ESM_SetProcTransState(ulStateTblIndex,NAS_ESM_BEARER_PROC_TRANS_STATE_PENDING);
}

/*****************************************************************************
 Function Name  : NAS_ESM_AppNdisConnReqRefusedProc()
 Description    : 向APP回复APP_ESM_BEARER_SETUP_CNF(失败)消息
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2013-06-03  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_AppNdisConnReqRefusedProc(VOS_VOID *pRcvMsg )
{
    VOS_UINT32                          ulStateTblIndex     = NAS_ESM_NULL;
    VOS_UINT32                          ulCidRecv           = NAS_ESM_NULL;
    APP_ESM_NDISCONN_REQ_STRU           *pRcvMsgTemp         = VOS_NULL_PTR;

    /*打印进入该函数*/
    NAS_ESM_NORM_LOG("NAS_ESM_AppNdisConnReqRefusedProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppNdisConnReqRefusedProc_ENUM, LNAS_ENTRY);

    /*指向接收消息*/
    pRcvMsgTemp = (APP_ESM_NDISCONN_REQ_STRU*)pRcvMsg;

    /*取出消息中包含CID参数*/
    ulCidRecv = pRcvMsgTemp->ulCid;

    /*根据CID号码找到状态表的ulStateTblIndex*/
    if( NAS_ESM_FAILURE == NAS_ESM_QueryStateTblIndexByCid(ulCidRecv,&ulStateTblIndex))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_AppNdisConnReqRefusedProc:WARNING: Tbl index Query Fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppNdisConnReqRefusedProc_ENUM, ESM_Tbl_index_Query_Fail);
        return;
    }

    NAS_ESM_LOG1("NAS_ESM_AppNdisConnReqRefusedProc:ERROR =", APP_ERR_SM_DETACHED);
    TLPS_PRINT2LAYER_INFO1(NAS_ESM_AppNdisConnReqRefusedProc_ENUM, 1, APP_ERR_SM_DETACHED);

    /*向APP回复APP_ESM_BEARER_SETUP_CNF(失败)消息*/
    NAS_ESM_SndEsmAppNdisConnCnfFailMsg(ulStateTblIndex, APP_ERR_SM_DETACHED);

    /*释放状态表资源*/
    NAS_ESM_RelStateTblResource(ulStateTblIndex);

}


/*****************************************************************************
 Function Name  : NAS_ESM_AppSdfSetupReqRefusedProc()
 Description    : 承载状态INACTIVE，PROCEDURE状态INACTIVE，APP->SM发送消息:
                    APP_ESM_BEARER_SETUP_REQ，SM调用状态机；
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.祝义强 00138739       2008-09-10  Draft Enact
      2.dingli 00138739       2008-10-14  Modify
      3.sunbing 49683         2009-02-05  Modify
      4.lihong 00150010       2009-09-25  Modify
*****************************************************************************/
VOS_VOID  NAS_ESM_AppSdfSetupReqRefusedProc(VOS_VOID *pRcvMsg )
{
    VOS_UINT32                          ulStateTblIndex     = NAS_ESM_NULL;
    VOS_UINT32                          ulCidRecv           = NAS_ESM_NULL;
    APP_ESM_PDP_SETUP_REQ_STRU      *pRcvMsgTemp         = VOS_NULL_PTR;

    /*打印进入该函数*/
    NAS_ESM_NORM_LOG("NAS_ESM_AppSdfSetupReqRefusedProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppSdfSetupReqRefusedProc_ENUM, LNAS_ENTRY);

    /*指向接收消息*/
    pRcvMsgTemp = (APP_ESM_PDP_SETUP_REQ_STRU*)pRcvMsg;

    /*取出消息中包含CID参数*/
    ulCidRecv = pRcvMsgTemp->ulCid;

    /*根据CID号码找到状态表的ulStateTblIndex*/
    if( NAS_ESM_FAILURE == NAS_ESM_QueryStateTblIndexByCid(ulCidRecv,&ulStateTblIndex))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_AppSdfSetupReqRefusedProc:WARNING: Tbl index Query Fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppSdfSetupReqRefusedProc_ENUM, ESM_Tbl_index_Query_Fail);
        return;
    }

    /*向APP回复APP_ESM_BEARER_SETUP_CNF(失败)消息*/
    NAS_ESM_SndEsmAppSdfSetupCnfFailMsg(ulStateTblIndex, APP_ERR_SM_DETACHED);

    /*释放状态表资源*/
    NAS_ESM_RelStateTblResource(ulStateTblIndex);

}

/*****************************************************************************
 Function Name  : NAS_ESM_DedictdAttMsgAppSdfSetupReq()
 Description    : 承载状态INACTIVE，PROCEDURE状态INACTIVE，APP->SM发送消息:
                    APP_ESM_BEARER_SETUP_REQ，SM调用状态机；SM->EMM发送承载资源
                    分配请求:ID_EMM_ESM_DATA_REQ(BEARER RESOURCE ALLOCATION REQ);
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.祝义强 00138739       2008-09-10  Draft Enact
      2.dingli 00138739       2008-10-14  Modify
      3.sunbing 49683         2009-02-05   Modify
*****************************************************************************/
VOS_VOID  NAS_ESM_DedictdAttMsgAppSdfSetupReq(VOS_VOID *pRcvMsg )
{
    VOS_UINT32                          ulStateTblIndex     = NAS_ESM_NULL;
    VOS_UINT32                          ulCidRecv           = NAS_ESM_NULL;
    VOS_UINT32                          ulLinkdCid          = NAS_ESM_NULL;
    VOS_UINT32                          ulLinkeEpsBid       = NAS_ESM_NULL;
    VOS_UINT32                          ulPti               = NAS_ESM_NULL;
    APP_ESM_PDP_SETUP_REQ_STRU         *pRcvMsgTemp         = VOS_NULL_PTR;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara          = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstBearerCntxtInfo  = VOS_NULL_PTR;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;
    NAS_ESM_ENCODE_INFO_STRU            stEncodeInfo;

    /*打印进入该函数*/
    NAS_ESM_NORM_LOG("NAS_ESM_DedictdAttMsgAppSdfSetupReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_DedictdAttMsgAppSdfSetupReq_ENUM, LNAS_ENTRY);

    /*指向接收消息*/
    pRcvMsgTemp = (APP_ESM_PDP_SETUP_REQ_STRU*)pRcvMsg;

    /*取出消息中包含CID参数*/
    ulCidRecv = pRcvMsgTemp->ulCid;

    /*根据CID号码找到状态表的ulStateTblIndex*/
    if( NAS_ESM_FAILURE == NAS_ESM_QueryStateTblIndexByCid(ulCidRecv,&ulStateTblIndex))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_DedictdAttMsgAppSdfSetupReq:WARNING: Tbl index Query Fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_DedictdAttMsgAppSdfSetupReq_ENUM, ESM_Tbl_index_Query_Fail);
        return;
    }

    /*根据CID找到其关联CID,检查LinkdCid合法性*/
    pstSdfPara = NAS_ESM_GetSdfParaAddr(ulCidRecv);
    if( (NAS_ESM_OP_FALSE == pstSdfPara->bitOpLinkdCId)
        ||(pstSdfPara->ulLinkdCId >= NAS_ESM_MAX_UE_CONTRUL_CID_NUM))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_DedictdAttMsgAppSdfSetupReq:WARNING:LinkdCid Error!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_DedictdAttMsgAppSdfSetupReq_ENUM, ESM_CID_ERROR);

        /*向APP回复APP_ESM_BEARER_SETUP_CNF(失败)消息*/
        NAS_ESM_SndEsmAppSdfSetupCnfFailMsg(ulStateTblIndex, APP_ERR_SM_LINK_CID_INVALID);


        /*释放状态表资源*/
        NAS_ESM_RelStateTblResource(ulStateTblIndex);
        return;
    }

    /*根据LinkdCid找到本地对应的EPS承载*/
    ulLinkdCid = pstSdfPara->ulLinkdCId;
    if(NAS_ESM_FAILURE == NAS_ESM_QueryEpsbCntxtTblByCid(ulLinkdCid,&ulLinkeEpsBid))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_DedictdAttMsgAppSdfSetupReq:WARNING:EpsbId Query Fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_DedictdAttMsgAppSdfSetupReq_ENUM, LNAS_FAIL);

        /*向APP回复APP_ESM_BEARER_SETUP_CNF(失败)消息*/
        NAS_ESM_SndEsmAppSdfSetupCnfFailMsg(ulStateTblIndex, APP_ERR_SM_LINK_BEARER_INACTIVE);

        /*释放状态表资源*/
        NAS_ESM_RelStateTblResource(ulStateTblIndex);
        return;

    }

    /*检查关联承载ulLinkeEpsBid的状态:是否被激活*/
    pstBearerCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulLinkeEpsBid);

    /*如果关联承载是紧急承载，则返回APP失败*/
    if (NAS_ESM_BEARER_TYPE_EMERGENCY == pstBearerCntxtInfo->enBearerCntxtType)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_DedictdAttMsgAppSdfSetupReq:WARNING:Linked EPS is emergency!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_DedictdAttMsgAppSdfSetupReq_ENUM, 1);

        /*向APP回复APP_ESM_BEARER_SETUP_CNF(失败)消息*/
        NAS_ESM_SndEsmAppSdfSetupCnfFailMsg(ulStateTblIndex, APP_ERR_SM_MODIFY_EMERGENCY_NOT_ALLOWED);

        /*释放状态表资源*/
        NAS_ESM_RelStateTblResource(ulStateTblIndex);
        return;
    }
    /*如果关联承载处于激活态*/
    if((NAS_ESM_BEARER_STATE_ACTIVE==pstBearerCntxtInfo->enBearerCntxtState)
        &&(PS_TRUE == NAS_ESM_IsDefaultEpsBearerType(pstBearerCntxtInfo->enBearerCntxtType)))
    {
        /*保存LinkeEpsBid*/
        NAS_ESM_SaveLinkedEpbsId(ulStateTblIndex, ulLinkeEpsBid);

        /*分配PTI，并存入承载信息中*/
        NAS_ESM_AssignPTI(&ulPti);
        pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);
        pstStateAddr->stNwMsgRecord.ucPti = (VOS_UINT8)ulPti;


        /*填充NAS_ESM_ENCODE_INFO_STRU*/
        NAS_ESM_MEM_SET_S(  (VOS_VOID*)&stEncodeInfo,
                            sizeof(NAS_ESM_ENCODE_INFO_STRU),
                            0,
                            sizeof(NAS_ESM_ENCODE_INFO_STRU));

        stEncodeInfo.bitOpESMCau        = NAS_ESM_OP_FALSE;
        stEncodeInfo.ulCid              = pstStateAddr->ulCid;
        stEncodeInfo.ucPti              = (VOS_UINT8)ulPti;
        stEncodeInfo.ulEpsbId           = pstStateAddr->ulEpsbId;
        stEncodeInfo.ulLinkedEpsbId     = pstStateAddr->ulLinkedEpsbId;

        /*组装Bearer_Res_Alloc_Req消息*/
        if( NAS_ESM_FAILURE == NAS_ESM_EncodeBearerResAllocReqMsg(stEncodeInfo, \
                                                          pstStateAddr->stNwMsgRecord.aucMsgBuff,\
                                                          &pstStateAddr->stNwMsgRecord.ulMsgLength))
        {
            NAS_ESM_WARN_LOG("NAS_ESM_DedictdAttMsgAppSdfSetupReq:WARNING:EncodeBearerResAllocReqMsg fail!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_DedictdAttMsgAppSdfSetupReq_ENUM, 2);

            /*向APP回复APP_ESM_BEARER_SETUP_CNF(失败)消息*/
            NAS_ESM_SndEsmAppSdfSetupCnfFailMsg(ulStateTblIndex, APP_ERR_UNSPECIFIED_ERROR);

            NAS_ESM_RelStateTblResource(ulStateTblIndex);

            return ;
        }

        /*记录空口消息类型*/
        pstStateAddr->bitOpNwMsgRecord = NAS_ESM_OP_TRUE;
        pstStateAddr->stNwMsgRecord.enEsmCnMsgType \
                = NAS_ESMCN_MSG_TYPE_BEARER_RES_ALLOC_REQ;
        pstStateAddr->stNwMsgRecord.ucIsEmcPdnReq = PS_FALSE;
        pstStateAddr->stNwMsgRecord.ulOpId = NAS_ESM_AllocEmmEsmOpId();
        #if (FEATURE_ON == FEATURE_DSDS)
        pstStateAddr->enEsmBearerDataCnf = NAS_ESM_BEARER_DATA_CNF_SENDING;
        NAS_ESM_SendBeginSessionNotify();
        #endif

        /*调用函数，ESM向EMM发送消息:ID_EMM_ESM_DATA_REQ(BEARER RESOURCE MODIFICATION REQ)*/
        NAS_ESM_SndEsmEmmDataReqMsg(pstStateAddr->stNwMsgRecord.ulOpId,
                                    pstStateAddr->stNwMsgRecord.ucIsEmcPdnReq,
                                    pstStateAddr->stNwMsgRecord.ulMsgLength,
                                    pstStateAddr->stNwMsgRecord.aucMsgBuff);

        /* 记录空口消息 */
        NAS_ESM_SndAirMsgReportInd(pstStateAddr->stNwMsgRecord.aucMsgBuff,
                               pstStateAddr->stNwMsgRecord.ulMsgLength,
                               NAS_ESM_AIR_MSG_DIR_ENUM_UP,
                               ESM_BEARER_RESOUCE_ALLOC_REQ);

        /*启动T3480定时器*/
        NAS_ESM_TimerStart(ulStateTblIndex,TI_NAS_ESM_T3480);

        /*转换状态*/
        NAS_ESM_SetProcTransState(ulStateTblIndex,NAS_ESM_BEARER_PROC_TRANS_STATE_PENDING);


    }
    else
    {
        NAS_ESM_WARN_LOG("NAS_ESM_DedictdAttMsgAppSdfSetupReq: link Eps beare inactive or dedicated bearer!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_DedictdAttMsgAppSdfSetupReq_ENUM, 3);

        /*向APP回复APP_ESM_BEARER_SETUP_CNF(失败)消息*/
        NAS_ESM_SndEsmAppSdfSetupCnfFailMsg(ulStateTblIndex, APP_ERR_SM_LINK_BEARER_INACTIVE);

        /*释放状态表资源*/
        NAS_ESM_RelStateTblResource(ulStateTblIndex);
        return;
    }


}

/*****************************************************************************
 Function Name   : NAS_ESM_IsQosChanged
 Description     : 判断承载QOS是否发生改变
 Input           : pstResModEncodeInfo
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2010-9-14  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_ESM_IsEpsQosChanged
(
    const NAS_ESM_RES_MOD_ENCODE_INFO_STRU   *pstResModEncodeInfo
)
{
    NAS_ESM_CONTEXT_LTE_QOS_STRU        stEpsQoSInfo;
    VOS_UINT8                           aucQos1[NAS_ESM_MAX_EPS_QOS_BYTE] = { NAS_ESM_NULL };
    VOS_UINT8                           aucQos2[NAS_ESM_MAX_EPS_QOS_BYTE] = { NAS_ESM_NULL };
    VOS_UINT32                          ulQosLen1           = NAS_ESM_NULL;
    VOS_UINT32                          ulQosLen2           = NAS_ESM_NULL;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo    = VOS_NULL_PTR;

    NAS_ESM_MEM_SET_S(  &stEpsQoSInfo,
                        sizeof(NAS_ESM_CONTEXT_LTE_QOS_STRU),
                        0,
                        sizeof(NAS_ESM_CONTEXT_LTE_QOS_STRU));

    /* 获取修改后的承载QOS */
    if (NAS_ESM_SUCCESS != NAS_ESM_GetEpsQosAfterMod(*pstResModEncodeInfo,&stEpsQoSInfo))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_IsQosChanged:NAS_ESM_GetEpsQosAfterMod failed!");
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_DedictdAttMsgAppSdfSetupReq_ENUM, LNAS_FAIL, 1);

        return NAS_ESM_EPS_QOS_CHANGE_TYPE_CHANGED;
    }

    /* 对修改后的承载QOS进行编码 */
    if (NAS_ESM_SUCCESS != NAS_ESM_EncodeEpsQos(&stEpsQoSInfo, aucQos1, &ulQosLen1, NAS_MSG_FORMAT_TLV))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_IsQosChanged:Encode modified bearer qos failed!");
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_DedictdAttMsgAppSdfSetupReq_ENUM, LNAS_FAIL, 2);

        return NAS_ESM_EPS_QOS_CHANGE_TYPE_CHANGED;
    }

    /*根据EpsId取出承载信息*/
    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(pstResModEncodeInfo->ulEpsbId);

    /* 对当前承载的QOS进行编码 */
    if (NAS_ESM_SUCCESS != NAS_ESM_EncodeEpsQos(&pstEpsbCntxtInfo->stEpsQoSInfo, aucQos2, &ulQosLen2, NAS_MSG_FORMAT_TLV))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_IsQosChanged:Encode current bearer qos failed!");
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_DedictdAttMsgAppSdfSetupReq_ENUM, LNAS_FAIL, 3);

        return NAS_ESM_EPS_QOS_CHANGE_TYPE_CHANGED;
    }

    /* 比较修改后的承载QOS编码结果与当前承载QOS的编码结果 */
    if (NAS_ESM_SUCCESS != NAS_ESM_MEM_CMP(aucQos1, aucQos2, NAS_ESM_MAX_EPS_QOS_BYTE))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_IsQosChanged:NAS_ESM_MEM_CMP failed!");
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_DedictdAttMsgAppSdfSetupReq_ENUM, LNAS_FAIL, 4);

        return NAS_ESM_EPS_QOS_CHANGE_TYPE_CHANGED;
    }

    return NAS_ESM_EPS_QOS_CHANGE_TYPE_NO_CHANGE;
}

/*****************************************************************************
 Function Name   : NAS_ESM_GetUeSetupPacketfilters
 Description     : 从SDF动态信息中获得用户建立的packetfilter
 Input           : ulCid         -- 操作的Cid
 Output          : ulPfNum       -- 找到的Pf数目
                   pstSdfPfArray -- 找到的Pf数组
 Return          : VOS_VOID

 History         :
    1.liuwenyu 00143951      2010-10-14  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_ESM_GetUeSetupPacketfilters
(
    VOS_UINT32                          ulCid,
    VOS_UINT32                         *pulPfNum,
    NAS_ESM_CONTEXT_TFT_STRU           *pstSdfPfArray
)
{
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntInfo       = VOS_NULL_PTR;
    NAS_ESM_CONTEXT_TFT_STRU           *pstTmpTftInfo       = VOS_NULL_PTR;
    VOS_UINT32                          ulCnt               = NAS_ESM_NULL;

    pstSdfCntInfo = NAS_ESM_GetSdfCntxtInfo(ulCid);

    *pulPfNum = NAS_ESM_NULL;

    for (ulCnt = NAS_ESM_NULL; ulCnt < pstSdfCntInfo->ulSdfPfNum; ulCnt++)
    {
        pstTmpTftInfo = &pstSdfCntInfo->astSdfPfInfo[ulCnt];

        if (NAS_ESM_NULL != pstTmpTftInfo->ucPacketFilterId)
        {
            NAS_ESM_MEM_CPY_S(  &pstSdfPfArray[*pulPfNum],
                                sizeof(NAS_ESM_CONTEXT_TFT_STRU),
                                pstTmpTftInfo,
                                sizeof(NAS_ESM_CONTEXT_TFT_STRU));

            (*pulPfNum)++;
        }
    }
}


/*****************************************************************************
 Function Name   : NAS_ESM_GetBearerResourceModifyType
 Description     : 获取承载资源修改类型
 Input           : ulCid
 Output          : None
 Return          : NAS_ESM_SDF_OP_TYPE_ENUM_UINT8

 History         :
    1.lihong00150010      2010-8-28  Draft Enact

*****************************************************************************/
NAS_ESM_SDF_OP_TYPE_ENUM_UINT8  NAS_ESM_GetBearerResourceModifyType
(
    const NAS_ESM_RES_MOD_ENCODE_INFO_STRU   *pstResModEncodeInfo
)
{
    VOS_UINT32                          ulRslt              = NAS_ESM_SUCCESS;
    VOS_UINT32                          ulPfNum             = NAS_ESM_NULL;
    NAS_ESM_SDF_OP_TYPE_ENUM_UINT8      enSdfOpType         = NAS_ESM_SDF_OP_TYPE_BUTT;
    VOS_UINT32                          ulPfArrayLen        = NAS_ESM_NULL;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara          = VOS_NULL_PTR;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntInfo       = VOS_NULL_PTR;
    NAS_ESM_CONTEXT_TFT_STRU           *pstSdfPfArray       = VOS_NULL_PTR;

    if (NAS_ESM_FAILURE == NAS_ESM_IsSdfQueryNwPfIdSucc(pstResModEncodeInfo))
    {
        return NAS_ESM_SDF_OP_TYPE_ADD_PF;
    }

    ulPfArrayLen = sizeof(NAS_ESM_CONTEXT_TFT_STRU) * NAS_ESM_MAX_SDF_PF_NUM;

    /*分配空间并检验分配是否成功*/
    pstSdfPfArray = (VOS_VOID*)NAS_ESM_MEM_ALLOC(ulPfArrayLen);

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pstSdfPfArray)
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_GetBearerResourceModifyType:Memory Alloc FAIL!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_GetBearerResourceModifyType_ENUM, LNAS_NULL_PTR);
        return NAS_ESM_SDF_OP_TYPE_BUTT;
    }

    NAS_ESM_GetUeSetupPacketfilters(pstResModEncodeInfo->ulCid,
                                   &ulPfNum,
                                    pstSdfPfArray);

    /* 获取SDF的静态信息 */
    pstSdfPara = NAS_ESM_GetSdfParaAddr(pstResModEncodeInfo->ulCid);

    /* 判断PF信息是否发生改变 */
    ulRslt = NAS_ESM_TftMatch(pstSdfPara->astCntxtTftInfo,
                              pstSdfPara->ulPfNum,
                              pstSdfPfArray,
                              ulPfNum);

    /* 获取SDF的动态信息 */
    pstSdfCntInfo = NAS_ESM_GetSdfCntxtInfo(pstResModEncodeInfo->ulCid);

    /* PF未发生改变 */
    if (NAS_ESM_SUCCESS == ulRslt)
    {
        /* 若是GBR，则返回修改类型为只修改QOS，否者返回修改类型为无修改 */
        if ((PS_TRUE == NAS_ESM_IsGbrBearer(pstSdfCntInfo->stSdfQosInfo.stQosInfo.ucQCI))
            && (NAS_ESM_EPS_QOS_CHANGE_TYPE_CHANGED == NAS_ESM_IsEpsQosChanged(pstResModEncodeInfo)))
        {
            enSdfOpType = NAS_ESM_SDF_OP_TYPE_MOD_QOS;
        }
        else
        {
            enSdfOpType = NAS_ESM_SDF_OP_TYPE_NO_CHANGE;
        }
    }
    /* PF发生改变 */
    else
    {
        /* 若是GBR，则返回修改类型为即修改QOS又修改TFT，否者返回修改类型为
           只修改TFT */
        if (PS_TRUE == NAS_ESM_IsGbrBearer(pstSdfCntInfo->stSdfQosInfo.stQosInfo.ucQCI))
        {
            enSdfOpType = NAS_ESM_SDF_OP_TYPE_MOD_QOS_AND_PF;
        }
        else
        {
            enSdfOpType = NAS_ESM_SDF_OP_TYPE_MOD_PF;
        }
    }

    /* 释放内存空间 */
    NAS_ESM_MEM_FREE(pstSdfPfArray);

    return enSdfOpType;
}

/*****************************************************************************
 Function Name  : NAS_ESM_DedictdAttMsgAppSdfModifyReq()
 Description    : 承载状态ACTIVE，PROCEDURE状态INACTIVE，APP->SM发送消息:
                    APP_ESM_BEARER_MODIFY_REQ，SM调用状态机；SM->EMM发送承载资源
                    分配请求:ID_EMM_ESM_DATA_REQ(BEARER RESOURCE ALLOCATION REQ);
                    网络收到后，发起承载资源修改过程;
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.祝义强 00138739       2008-09-10  Draft Enact
      2.dingli 00138739       2008-10-14  Modify
      3.sunbing 49683         2009-02-05  Modify
*****************************************************************************/
VOS_VOID  NAS_ESM_DedictdAttMsgAppSdfModifyReq
(
    const APP_ESM_PDP_MODIFY_REQ_STRU *pRcvMsg
)
{
    VOS_UINT32                          ulStateTblIndex     = NAS_ESM_NULL;
    VOS_UINT32                          ulCidRecv           = NAS_ESM_NULL;
    VOS_UINT32                          ulPti               = NAS_ESM_NULL;
    NAS_ESM_SDF_OP_TYPE_ENUM_UINT8      enSdfOpType         = NAS_ESM_SDF_OP_TYPE_BUTT;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara          = VOS_NULL_PTR;
    NAS_ESM_RES_MOD_ENCODE_INFO_STRU    stResModEncodeInfo;

    /*打印进入该函数*/
    NAS_ESM_NORM_LOG("NAS_ESM_DedictdAttMsgAppSdfModifyReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_DedictdAttMsgAppSdfModifyReq_ENUM, LNAS_ENTRY);

    /*取出消息中包含CID参数*/
    ulCidRecv = pRcvMsg->ulCid;

    /*根据CID号码找到状态表的ulStateTblIndex*/
    if( NAS_ESM_FAILURE == NAS_ESM_QueryStateTblIndexByCid(ulCidRecv,&ulStateTblIndex))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_DedictdAttMsgAppSdfModifyReq:WARNING: Tbl index Query Fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_DedictdAttMsgAppSdfModifyReq_ENUM, ESM_Tbl_index_Query_Fail);
        return;
    }

    /*分配PTI，并存入承载信息中*/
    NAS_ESM_AssignPTI(&ulPti);
    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);
    pstStateAddr->stNwMsgRecord.ucPti = (VOS_UINT8)ulPti;

    /*填充NAS_ESM_ENCODE_INFO_STRU*/
    NAS_ESM_MEM_SET_S(  (VOS_VOID*)&stResModEncodeInfo,
                        sizeof(NAS_ESM_RES_MOD_ENCODE_INFO_STRU),
                        0,
                        sizeof(NAS_ESM_RES_MOD_ENCODE_INFO_STRU));

    stResModEncodeInfo.bitOpESMCau        = NAS_ESM_OP_FALSE;
    stResModEncodeInfo.ulCid              = pstStateAddr->ulCid;
    stResModEncodeInfo.ucPti              = (VOS_UINT8)ulPti;
    stResModEncodeInfo.ulEpsbId           = pstStateAddr->ulEpsbId;

    stResModEncodeInfo.ulLinkedEpsbId     = pstStateAddr->ulEpsbId;

    /* 获取SDF的静态信息 */
    pstSdfPara = NAS_ESM_GetSdfParaAddr(stResModEncodeInfo.ulCid);

    if ((NAS_ESM_NULL == pstSdfPara->ulPfNum) || (NAS_ESM_OP_FALSE == pstSdfPara->bitOpSdfQos))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_DedictdAttMsgAppSdfModifyReq:WARNING:No tft information or no qos information!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_DedictdAttMsgAppSdfModifyReq_ENUM, 1);

        NAS_ESM_SndEsmAppSdfModCnfFailMsg(ulStateTblIndex, APP_ERR_UNSPECIFIED_ERROR);

        NAS_ESM_RelStateTblResource(ulStateTblIndex);

        return ;
    }

    /* 获取承载资源修改类型 */
    enSdfOpType = NAS_ESM_GetBearerResourceModifyType(&stResModEncodeInfo);

    NAS_ESM_LOG1("NAS_ESM_DedictdAttMsgAppSdfModifyReq modify type:", enSdfOpType);
    TLPS_PRINT2LAYER_INFO1(NAS_ESM_DedictdAttMsgAppSdfModifyReq_ENUM, 2, enSdfOpType);

    /* 如果返回类型为修改异常，则直接给APP回复修改失败 */
    if ((NAS_ESM_SDF_OP_TYPE_BUTT == enSdfOpType)
     || (NAS_ESM_SDF_OP_TYPE_ADD_PF == enSdfOpType))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_DedictdAttMsgAppSdfModifyReq:Add packetfilter is not support!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_DedictdAttMsgAppSdfModifyReq_ENUM, 3);

        NAS_ESM_SndEsmAppSdfModCnfFailMsg(ulStateTblIndex, APP_ERR_INSUFFICIENT_RESOURCES);

        NAS_ESM_RelStateTblResource(ulStateTblIndex);

        return ;
    }

    /* 如果返回类型为不修改，则直接给APP回复修改成功 */
    if (NAS_ESM_SDF_OP_TYPE_NO_CHANGE == enSdfOpType)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_DedictdAttMsgAppSdfModifyReq:no information changes!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_DedictdAttMsgAppSdfModifyReq_ENUM, 4);

        NAS_ESM_SndEsmAppSdfModCnfSuccMsg(ulStateTblIndex, APP_ESM_BEARER_MODIFY_TFT);

        NAS_ESM_RelStateTblResource(ulStateTblIndex);

        return ;
    }

    stResModEncodeInfo.enSdfOpType = enSdfOpType;

    /*组装Bearer_Res_Mod_Req消息*/
    if( NAS_ESM_FAILURE == NAS_ESM_EncodeBearerResModReqMsg(stResModEncodeInfo, \
                                                      pstStateAddr->stNwMsgRecord.aucMsgBuff,\
                                                      &pstStateAddr->stNwMsgRecord.ulMsgLength))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_DedictdAttMsgAppSdfModifyReq:WARNING:EncodeBearerResModReqMsg fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_DedictdAttMsgAppSdfModifyReq_ENUM, EncodeBearerResModReqMsg_fail);

        NAS_ESM_SndEsmAppSdfModCnfFailMsg(ulStateTblIndex, APP_ERR_UNSPECIFIED_ERROR);

        NAS_ESM_RelStateTblResource(ulStateTblIndex);

        return ;
    }

    /*记录空口消息类型*/
    pstStateAddr->bitOpNwMsgRecord = NAS_ESM_OP_TRUE;

    pstStateAddr->stNwMsgRecord.enEsmCnMsgType = NAS_ESMCN_MSG_TYPE_BEARER_RES_MOD_REQ;
    pstStateAddr->stNwMsgRecord.ucIsEmcPdnReq = PS_FALSE;
    pstStateAddr->stNwMsgRecord.ulOpId = NAS_ESM_AllocEmmEsmOpId();
    #if (FEATURE_ON == FEATURE_DSDS)
    pstStateAddr->enEsmBearerDataCnf = NAS_ESM_BEARER_DATA_CNF_SENDING;
    NAS_ESM_SendBeginSessionNotify();
    #endif

    /*调用函数，ESM向EMM发送消息:ID_EMM_ESM_DATA_REQ(BEARER RESOURCE MODIFICATION REQ)*/
    NAS_ESM_SndEsmEmmDataReqMsg(pstStateAddr->stNwMsgRecord.ulOpId,
                                pstStateAddr->stNwMsgRecord.ucIsEmcPdnReq,
                                pstStateAddr->stNwMsgRecord.ulMsgLength,
                                pstStateAddr->stNwMsgRecord.aucMsgBuff);

    /* 记录空口消息 */
    NAS_ESM_SndAirMsgReportInd(pstStateAddr->stNwMsgRecord.aucMsgBuff,\
                           pstStateAddr->stNwMsgRecord.ulMsgLength,
                           NAS_ESM_AIR_MSG_DIR_ENUM_UP,
                           ESM_BEARER_RESOUCE_MOD_REQ);

    /*启动T3481定时器*/
    NAS_ESM_TimerStart(ulStateTblIndex,TI_NAS_ESM_T3481);

    /*状态转换*/
    NAS_ESM_SetProcTransState(ulStateTblIndex,NAS_ESM_BEARER_PROC_TRANS_STATE_PENDING);
}

/*****************************************************************************
 Function Name  : NAS_ESM_DedictdAttMsgAppSdfRelReq()
 Description    : 承载状态ACTIVE，PROCEDURE状态INACTIVE，APP->SM发送消息:
                    APP_ESM_BEARER_RELEASE_REQ，SM调用状态机；
                    SM->EMM发送:ID_EMM_ESM_DATA_REQ(BEARER RESOURCE RELEASE REQ);
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.祝义强 00138739       2008-09-10  Draft Enact
      2.sunbing 49683         2009-02-05   Modify
*****************************************************************************/
VOS_VOID  NAS_ESM_DedictdAttMsgAppSdfRelReq(const VOS_VOID *pRcvMsg )
{
    VOS_UINT32                          ulStateTblIndex     = NAS_ESM_NULL;
    VOS_UINT32                          ulCidRecv           = NAS_ESM_NULL;
    VOS_UINT32                          ulPti               = NAS_ESM_NULL;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;
    NAS_ESM_RES_MOD_ENCODE_INFO_STRU    stResModEncodeInfo;

    /*打印进入该函数*/
    NAS_ESM_NORM_LOG("NAS_ESM_DedictdAttMsgAppSdfRelReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_DedictdAttMsgAppSdfRelReq_ENUM, LNAS_ENTRY);

    /*取出消息中包含CID参数*/
    ulCidRecv=((APP_ESM_PDP_RELEASE_REQ_STRU*)pRcvMsg)->ulCid;

    /*根据CID号码找到状态表的ulStateTblIndex*/
    if( NAS_ESM_FAILURE == NAS_ESM_QueryStateTblIndexByCid(ulCidRecv,&ulStateTblIndex))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_DedictdAttMsgAppSdfRelReq:WARNING: Tbl index Query Fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_DedictdAttMsgAppSdfRelReq_ENUM, ESM_Tbl_index_Query_Fail);
        return;
    }

    /*分配PTI，并存入承载信息中*/
    NAS_ESM_AssignPTI(&ulPti);
    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);
    pstStateAddr->stNwMsgRecord.ucPti = (VOS_UINT8)ulPti;

    /*填充NAS_ESM_ENCODE_INFO_STRU*/
    NAS_ESM_MEM_SET_S(  (VOS_VOID*)&stResModEncodeInfo,
                        sizeof(NAS_ESM_RES_MOD_ENCODE_INFO_STRU),
                        0,
                        sizeof(NAS_ESM_RES_MOD_ENCODE_INFO_STRU));

    stResModEncodeInfo.bitOpESMCau        = NAS_ESM_OP_TRUE;
    stResModEncodeInfo.ucESMCau           = NAS_ESM_CAUSE_REGULAR_DEACTIVATION;
    stResModEncodeInfo.ulCid              = pstStateAddr->ulCid;
    stResModEncodeInfo.ucPti              = (VOS_UINT8)ulPti;
    stResModEncodeInfo.ulEpsbId           = pstStateAddr->ulEpsbId;
    stResModEncodeInfo.ulLinkedEpsbId     = pstStateAddr->ulEpsbId;
    stResModEncodeInfo.enSdfOpType        = NAS_ESM_SDF_OP_TYPE_DELETE_SDF;

    /*组装Bearer_Res_Mod_Req消息*/
    if( NAS_ESM_FAILURE == NAS_ESM_EncodeBearerResModReqMsg(stResModEncodeInfo, \
                                                      pstStateAddr->stNwMsgRecord.aucMsgBuff,\
                                                      &pstStateAddr->stNwMsgRecord.ulMsgLength))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_DedictdAttMsgAppSdfRelReq:WARNING:EncodeBearerResModReqMsg fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_DedictdAttMsgAppSdfRelReq_ENUM, EncodeBearerResModReqMsg_fail);

        /*向APP回复APP_ESM_BEARER_RELEASE_CNF(失败)消息*/
        NAS_ESM_SndEsmAppSdfRelCnfFailMsg(ulStateTblIndex, APP_ERR_UNSPECIFIED_ERROR);

        NAS_ESM_RelStateTblResource(ulStateTblIndex);

        return ;
    }

    /*记录空口消息类型*/
    pstStateAddr->bitOpNwMsgRecord = NAS_ESM_OP_TRUE;


    pstStateAddr->stNwMsgRecord.enEsmCnMsgType = NAS_ESMCN_MSG_TYPE_BEARER_RES_MOD_REQ;
    pstStateAddr->stNwMsgRecord.ucIsEmcPdnReq = PS_FALSE;
    pstStateAddr->stNwMsgRecord.ulOpId = NAS_ESM_AllocEmmEsmOpId();
    #if (FEATURE_ON == FEATURE_DSDS)
    pstStateAddr->enEsmBearerDataCnf = NAS_ESM_BEARER_DATA_CNF_SENDING;
    NAS_ESM_SendBeginSessionNotify();
    #endif

    /*调用函数，ESM向EMM发送消息:ID_EMM_ESM_DATA_REQ(BEARER RESOURCE MODIFICATION REQ)*/
    NAS_ESM_SndEsmEmmDataReqMsg(pstStateAddr->stNwMsgRecord.ulOpId,
                                pstStateAddr->stNwMsgRecord.ucIsEmcPdnReq,
                                pstStateAddr->stNwMsgRecord.ulMsgLength,
                                pstStateAddr->stNwMsgRecord.aucMsgBuff);

    /* 记录空口消息 */
    NAS_ESM_SndAirMsgReportInd(pstStateAddr->stNwMsgRecord.aucMsgBuff,
                           pstStateAddr->stNwMsgRecord.ulMsgLength,
                           NAS_ESM_AIR_MSG_DIR_ENUM_UP,
                           ESM_BEARER_RESOUCE_MOD_REQ);

    /*启动T3481定时器*/
    NAS_ESM_TimerStart(ulStateTblIndex,TI_NAS_ESM_T3481);

    /*状态转换*/
    NAS_ESM_SetProcTransState(ulStateTblIndex,NAS_ESM_BEARER_PROC_TRANS_STATE_PENDING);
}


/*lint -specific(-e433)*/
VOS_VOID NAS_ESM_SndEsmAppSdfSetupCnfMsg(const NAS_ESM_APP_CNF_MSG_STRU *pstEsmAppCnfMsg)
{
    VOS_UINT16                          usOriginalId        = NAS_ESM_NULL;
    VOS_UINT16                          usTerminalId        = NAS_ESM_NULL;
    APP_ESM_PDP_SETUP_CNF_STRU         *pSmAppSetupCnf      = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pEpsCntxtInfo       = VOS_NULL_PTR;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo     = VOS_NULL_PTR;


    if(VOS_NULL_PTR == pstEsmAppCnfMsg)
    {
        NAS_ESM_ERR_LOG("NAS_ESM_SndEsmAppSdfSetupCnfMsg:ERROR:APP->SM,Memory Alloc FAIL!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEsmAppSdfSetupCnfMsg_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*分配空间并检验分配是否成功*/
    /*lint -e433 -e826*/
    pSmAppSetupCnf = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(APP_ESM_PDP_SETUP_CNF_STRU));
    /*lint +e433 +e826*/

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pSmAppSetupCnf)
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEsmAppSdfSetupCnfMsg:ERROR:APP->SM,Memory Alloc FAIL!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEsmAppSdfSetupCnfMsg_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*清空*/
    NAS_ESM_MEM_SET_S(  NAS_ESM_GET_MSG_ENTITY(pSmAppSetupCnf),
                        NAS_ESM_GET_MSG_LENGTH(pSmAppSetupCnf),
                        0,
                        NAS_ESM_GET_MSG_LENGTH(pSmAppSetupCnf));

    if( NAS_ESM_OP_TRUE == pstEsmAppCnfMsg->bitOpEpsbId )
    {
        /*填充ulRabId参数*/
        pSmAppSetupCnf->bitOpRabId = NAS_ESM_OP_TRUE;
        pSmAppSetupCnf->ulRabId = pstEsmAppCnfMsg->ulEpsbId;
    }
    else
    {
        pSmAppSetupCnf->bitOpRabId = NAS_ESM_OP_FALSE;
    }

    /*填充ulCid参数*/
    pSmAppSetupCnf->ulCid = pstEsmAppCnfMsg->ulCId;

    /*填充ulOpId参数*/
    pSmAppSetupCnf->ulOpId = pstEsmAppCnfMsg->ulOpId;

    /*填充MID参数*/
    usTerminalId = pstEsmAppCnfMsg->usOriginalId;
    usOriginalId = pstEsmAppCnfMsg->usTerminalId;

    /*填充ulErrorCode参数*/
    if(NAS_ESM_OP_TRUE == pstEsmAppCnfMsg->bitOpErrorCode)
    {
        pSmAppSetupCnf->ulRslt = pstEsmAppCnfMsg->ulErrorCode;
    }
    else
    {
        /*如果bitOpErrorCode为false,当前错误码为空，表示没错误*/
        pSmAppSetupCnf->ulRslt = APP_SUCCESS;
    }


    /*若承载建立成功*/
    if((NAS_ESM_SUCCESS == pstEsmAppCnfMsg->ulRst)
                            &&(NAS_ESM_OP_TRUE == pstEsmAppCnfMsg->bitOpEpsbId))
    {
        pEpsCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(pstEsmAppCnfMsg->ulEpsbId);

        /*承载状态赋值*/
        pSmAppSetupCnf->bitOpBearerState = NAS_ESM_OP_TRUE;
        pSmAppSetupCnf->enBearerState = pEpsCntxtInfo->enBearerCntxtState;

        /*承载类型赋值*/
        pSmAppSetupCnf->bitOpBearerType = NAS_ESM_OP_TRUE;
        pSmAppSetupCnf->enBearerType = pEpsCntxtInfo->enBearerCntxtType;

        /* 若是专有承载，则赋值LinkCid */
        pSmAppSetupCnf->ulLinkCid = NAS_ESM_GetLinkCidByActiveCid(pSmAppSetupCnf->ulCid);
        if (NAS_ESM_ILL_CID != pSmAppSetupCnf->ulLinkCid)
        {
            pSmAppSetupCnf->bitOpLinkCid = NAS_ESM_OP_TRUE;
        }
        else
        {
            pSmAppSetupCnf->bitOpLinkCid = NAS_ESM_OP_FALSE;
        }

        /*承载地址赋值*/
        if(NAS_ESM_OP_TRUE == pEpsCntxtInfo->bitOpPdnAddr)
        {
            pSmAppSetupCnf->bitOpPdnAddr = NAS_ESM_OP_TRUE;

            NAS_ESM_MEM_CPY_S(  (VOS_VOID*)&(pSmAppSetupCnf->stPDNAddrInfo),
                                sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU),
                                (VOS_VOID*)&(pEpsCntxtInfo->stPdnAddrInfo),
                                sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU));

            NAS_ESM_MEM_CPY_S(  (VOS_VOID*)&(pSmAppSetupCnf->stSubnetMask),
                                sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU),
                                (VOS_VOID*)&(pEpsCntxtInfo->stSubnetMask),
                                sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU));
        }

        if (NAS_ESM_OP_TRUE == pEpsCntxtInfo->bitOpGateWayAddrInfo)
        {
            pSmAppSetupCnf->bitOpGateWayAddrInfo = NAS_ESM_OP_TRUE;
            NAS_ESM_MEM_CPY_S(  (VOS_VOID*)&(pSmAppSetupCnf->stGateWayAddrInfo),
                                sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU),
                                (VOS_VOID*)&(pEpsCntxtInfo->stGateWayAddrInfo),
                                sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU));
        }

        /*设置APN参数*/
        if( NAS_ESM_OP_TRUE == pEpsCntxtInfo->bitOpApn )
        {
            pSmAppSetupCnf->bitOpApn = NAS_ESM_OP_TRUE;
            NAS_ESM_MEM_CPY_S(  (VOS_VOID*)&(pSmAppSetupCnf->stApnInfo),
                                sizeof(APP_ESM_APN_INFO_STRU),
                                (VOS_VOID*)&(pEpsCntxtInfo->stApnInfo),
                                sizeof(APP_ESM_APN_INFO_STRU));
        }

        /*设置SDF QOS参数*/
        pstSdfCntxtInfo = NAS_ESM_GetSdfCntxtInfo(pSmAppSetupCnf->ulCid);
        if( NAS_ESM_OP_TRUE == pEpsCntxtInfo->bitOpEpsQos )
        {
            pSmAppSetupCnf->bitOpSdfQos= NAS_ESM_OP_TRUE;
            NAS_ESM_MEM_CPY_S(  (VOS_VOID*)&(pSmAppSetupCnf->stSdfQosInfo),
                                sizeof(APP_ESM_EPS_QOS_INFO_STRU),
                                (VOS_VOID*)(&pstSdfCntxtInfo->stSdfQosInfo.stQosInfo),
                                sizeof(APP_ESM_EPS_QOS_INFO_STRU));
        }

        /*设置PCO信息*/
        if(NAS_ESM_OP_TRUE == pEpsCntxtInfo->bitOpPco)
        {
            NAS_ESM_ProcSetUpMsgPcoInfo(pSmAppSetupCnf,pEpsCntxtInfo);
        }

    }
    else
    {
        pSmAppSetupCnf->bitOpBearerState    = NAS_ESM_OP_FALSE;
        pSmAppSetupCnf->bitOpBearerType     = NAS_ESM_OP_FALSE;
        pSmAppSetupCnf->bitOpPdnAddr        = NAS_ESM_OP_FALSE;
        pSmAppSetupCnf->bitOpApn            = NAS_ESM_OP_FALSE;
        pSmAppSetupCnf->bitOpSdfQos         = NAS_ESM_OP_FALSE;
        pSmAppSetupCnf->bitOpLinkCid        = NAS_ESM_OP_FALSE;
        pSmAppSetupCnf->bitOpDnsPrim        = NAS_ESM_OP_FALSE;
        pSmAppSetupCnf->bitOpDnsSec         = NAS_ESM_OP_FALSE;
        pSmAppSetupCnf->bitOpPCscfPrim      = NAS_ESM_OP_FALSE;
        pSmAppSetupCnf->bitOpPCscfSec       = NAS_ESM_OP_FALSE;
        pSmAppSetupCnf->bitOpGateWayAddrInfo= NAS_ESM_OP_FALSE;
    }

    /*填写消息头*/
    NAS_ESM_WRITE_TAF_MSG_HEAD(pSmAppSetupCnf,ID_APP_ESM_PDP_SETUP_CNF,\
                              usOriginalId,usTerminalId,\
                              pstEsmAppCnfMsg->ulSn);

    /*调用消息发送函数 */
    NAS_ESM_SND_MSG(pSmAppSetupCnf);

}
/*lint -specific(+e433)*/

/*****************************************************************************
 Function Name   : NAS_ESM_SetNdisConnCnfMsgPcoInfo
 Description     : 设置NDIS CONN CNF消息中的PCO信息
 Input           : VOS_VOID *pstRsvMsg
                   VOS_VOID *pstCntxtInfo
 Output          : None
 Return          : VOS_VOID

 History         :
    1. lihong  00150010      2013-8-29  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_SetNdisConnCnfMsgPcoInfo
(
    APP_ESM_NDISCONN_CNF_STRU          *pstEsmAppNdisConnCnf,
    const NAS_ESM_EPSB_CNTXT_INFO_STRU *pstEpsCntxtInfo
)
{
    NAS_ESM_PCO_TRANSFORM_STRU          stTransPco = {0};

    NAS_ESM_TransformPcoStru(   pstEpsCntxtInfo->stPdnAddrInfo.ucIpType,
                                &(pstEpsCntxtInfo->stPcoInfo),
                                &stTransPco);

    if (stTransPco.ucDnsSerNum == 0)
    {
        NAS_ESM_INFO_LOG("NAS_ESM_SetNdisConnCnfMsgPcoInfo:Dns is not exist!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_SetNdisConnCnfMsgPcoInfo_ENUM, 1);
        pstEsmAppNdisConnCnf->bitOpDnsPrim    = NAS_ESM_OP_FALSE;
        pstEsmAppNdisConnCnf->bitOpDnsSec     = NAS_ESM_OP_FALSE;
    }
    else if (stTransPco.ucDnsSerNum == 1)
    {
        NAS_ESM_INFO_LOG("NAS_ESM_SetNdisConnCnfMsgPcoInfo:Prim Dns is exist one!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_SetNdisConnCnfMsgPcoInfo_ENUM, 2);
        pstEsmAppNdisConnCnf->bitOpDnsPrim    = NAS_ESM_OP_TRUE;
        NAS_ESM_MEM_CPY_S(  (VOS_VOID*)&(pstEsmAppNdisConnCnf->stDnsPrimAddrInfo),
                            sizeof(APP_ESM_IP_ADDR_STRU),
                            (VOS_VOID*)&(stTransPco.astDnsServer[0]),
                            sizeof(APP_ESM_IP_ADDR_STRU));
        pstEsmAppNdisConnCnf->bitOpDnsSec     = NAS_ESM_OP_FALSE;
    }
    else
    {
        NAS_ESM_INFO_LOG("NAS_ESM_SetNdisConnCnfMsgPcoInfo:Dns is exist two!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_SetNdisConnCnfMsgPcoInfo_ENUM, 3);
        pstEsmAppNdisConnCnf->bitOpDnsPrim    = NAS_ESM_OP_TRUE;
        pstEsmAppNdisConnCnf->bitOpDnsSec     = NAS_ESM_OP_TRUE;
        NAS_ESM_MEM_CPY_S(  (VOS_VOID*)&(pstEsmAppNdisConnCnf->stDnsPrimAddrInfo),
                            sizeof(APP_ESM_IP_ADDR_STRU),
                            (VOS_VOID*)&(stTransPco.astDnsServer[0]),
                            sizeof(APP_ESM_IP_ADDR_STRU));

        NAS_ESM_MEM_CPY_S(  (VOS_VOID*)&(pstEsmAppNdisConnCnf->stDnsSecAddrInfo),
                            sizeof(APP_ESM_IP_ADDR_STRU),
                            (VOS_VOID*)&(stTransPco.astDnsServer[1]),
                            sizeof(APP_ESM_IP_ADDR_STRU));
    }

    if (stTransPco.ucPcscfNum == 0)
    {
        NAS_ESM_INFO_LOG("NAS_ESM_SetNdisConnCnfMsgPcoInfo:P-CSCF is not exist!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_SetNdisConnCnfMsgPcoInfo_ENUM, 4);
        pstEsmAppNdisConnCnf->bitOpPCscfPrim  = NAS_ESM_OP_FALSE;
        pstEsmAppNdisConnCnf->bitOpPCscfSec   = NAS_ESM_OP_FALSE;
    }
    else if (stTransPco.ucPcscfNum == 1)
    {
        NAS_ESM_INFO_LOG("NAS_ESM_SetNdisConnCnfMsgPcoInfo:Prim P-CSCF is exist one!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_SetNdisConnCnfMsgPcoInfo_ENUM, 5);
        pstEsmAppNdisConnCnf->bitOpPCscfPrim  = NAS_ESM_OP_TRUE;
        NAS_ESM_MEM_CPY_S(  (VOS_VOID*)&(pstEsmAppNdisConnCnf->stPCscfPrimAddrInfo),
                            sizeof(APP_ESM_IP_ADDR_STRU),
                            (VOS_VOID*)&(stTransPco.astPcscf[0]),
                            sizeof(APP_ESM_IP_ADDR_STRU));

        pstEsmAppNdisConnCnf->bitOpPCscfSec   = NAS_ESM_OP_FALSE;
    }
    else
    {
        NAS_ESM_INFO_LOG("NAS_ESM_SetNdisConnCnfMsgPcoInfo:P-CSCF is exist two!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_SetNdisConnCnfMsgPcoInfo_ENUM, 6);
        pstEsmAppNdisConnCnf->bitOpPCscfPrim  = NAS_ESM_OP_TRUE;
        pstEsmAppNdisConnCnf->bitOpPCscfSec   = NAS_ESM_OP_TRUE;
        NAS_ESM_MEM_CPY_S(  (VOS_VOID*)(VOS_VOID*)&(pstEsmAppNdisConnCnf->stPCscfPrimAddrInfo),
                            sizeof(APP_ESM_IP_ADDR_STRU),
                            (VOS_VOID*)(VOS_VOID*)&(stTransPco.astPcscf[0]),
                            sizeof(APP_ESM_IP_ADDR_STRU));
        NAS_ESM_MEM_CPY_S(  (VOS_VOID*)&(pstEsmAppNdisConnCnf->stPCscfSecAddrInfo),
                            sizeof(APP_ESM_IP_ADDR_STRU),
                            (VOS_VOID*)&(stTransPco.astPcscf[1]),
                            sizeof(APP_ESM_IP_ADDR_STRU));
    }

    return;
}


/*lint -specific(-e433)*/
VOS_VOID NAS_ESM_SndEsmAppNdisConnCnfMsg(const NAS_ESM_APP_CNF_MSG_STRU *pstEsmAppCnfMsg)
{
    VOS_UINT16                          usOriginalId                = NAS_ESM_NULL;
    VOS_UINT16                          usTerminalId                = NAS_ESM_NULL;
    APP_ESM_NDISCONN_CNF_STRU          *pSmAppNdisConnCnfCnf        = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pEpsCntxtInfo               = VOS_NULL_PTR;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo             = VOS_NULL_PTR;


    if(VOS_NULL_PTR == pstEsmAppCnfMsg)
    {
        NAS_ESM_ERR_LOG("NAS_ESM_SndEsmAppNdisConnCnfMsg:ERROR:APP->SM,Memory Alloc FAIL!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEsmAppNdisConnCnfMsg_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*分配空间并检验分配是否成功*/
    /*lint -e433 -e826*/
    pSmAppNdisConnCnfCnf = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(APP_ESM_NDISCONN_CNF_STRU));
    /*lint +e433 +e826*/

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pSmAppNdisConnCnfCnf)
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEsmAppNdisConnCnfMsg:ERROR:APP->SM,Memory Alloc FAIL!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEsmAppNdisConnCnfMsg_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*清空*/
    NAS_ESM_MEM_SET_S(  NAS_ESM_GET_MSG_ENTITY(pSmAppNdisConnCnfCnf),
                        NAS_ESM_GET_MSG_LENGTH(pSmAppNdisConnCnfCnf),
                        0,
                        NAS_ESM_GET_MSG_LENGTH(pSmAppNdisConnCnfCnf));

    if( NAS_ESM_OP_TRUE == pstEsmAppCnfMsg->bitOpEpsbId )
    {
        /*填充ulRabId参数*/
        pSmAppNdisConnCnfCnf->bitOpRabId = NAS_ESM_OP_TRUE;
        pSmAppNdisConnCnfCnf->ulRabId = pstEsmAppCnfMsg->ulEpsbId;
    }
    else
    {
        pSmAppNdisConnCnfCnf->bitOpRabId = NAS_ESM_OP_FALSE;
    }

    /*填充ulCid参数*/
    pSmAppNdisConnCnfCnf->ulCid = pstEsmAppCnfMsg->ulCId;

    /*填充ulOpId参数*/
    pSmAppNdisConnCnfCnf->ulOpId = pstEsmAppCnfMsg->ulOpId;

    /*填充MID参数*/
    usTerminalId = pstEsmAppCnfMsg->usOriginalId;
    usOriginalId = pstEsmAppCnfMsg->usTerminalId;

    /*填充ulErrorCode参数*/
    if(NAS_ESM_OP_TRUE == pstEsmAppCnfMsg->bitOpErrorCode)
    {
        pSmAppNdisConnCnfCnf->ulRslt = pstEsmAppCnfMsg->ulErrorCode;
    }
    else
    {
        /*如果bitOpErrorCode为false,当前错误码为空，表示没错误*/
        pSmAppNdisConnCnfCnf->ulRslt = APP_SUCCESS;
    }


    /*若承载建立成功*/
    if((NAS_ESM_SUCCESS == pstEsmAppCnfMsg->ulRst)
        &&(NAS_ESM_OP_TRUE == pstEsmAppCnfMsg->bitOpEpsbId))
    {
        pEpsCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(pstEsmAppCnfMsg->ulEpsbId);

        /*承载状态赋值*/
        pSmAppNdisConnCnfCnf->bitOpBearerState = NAS_ESM_OP_TRUE;
        pSmAppNdisConnCnfCnf->enBearerState = pEpsCntxtInfo->enBearerCntxtState;

        /*承载类型赋值*/
        pSmAppNdisConnCnfCnf->bitOpBearerType = NAS_ESM_OP_TRUE;
        pSmAppNdisConnCnfCnf->enBearerType = pEpsCntxtInfo->enBearerCntxtType;


        /*承载地址赋值*/
        if(NAS_ESM_OP_TRUE == pEpsCntxtInfo->bitOpPdnAddr)
        {
            pSmAppNdisConnCnfCnf->bitOpPdnAddr = NAS_ESM_OP_TRUE;
            NAS_ESM_MEM_CPY_S(  (VOS_VOID*)&(pSmAppNdisConnCnfCnf->stPDNAddrInfo),
                                sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU),
                                (VOS_VOID*)&(pEpsCntxtInfo->stPdnAddrInfo),
                                sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU));

            NAS_ESM_MEM_CPY_S(  (VOS_VOID*)&(pSmAppNdisConnCnfCnf->stSubnetMask),
                                sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU),
                                (VOS_VOID*)&(pEpsCntxtInfo->stSubnetMask),
                                sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU));
        }

        if (NAS_ESM_OP_TRUE == pEpsCntxtInfo->bitOpGateWayAddrInfo)
        {
            pSmAppNdisConnCnfCnf->bitOpGateWayAddrInfo = NAS_ESM_OP_TRUE;
            NAS_ESM_MEM_CPY_S(  (VOS_VOID*)&(pSmAppNdisConnCnfCnf->stGateWayAddrInfo),
                                sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU),
                                (VOS_VOID*)&(pEpsCntxtInfo->stGateWayAddrInfo),
                                sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU));
        }

        /*设置APN参数*/
        if( NAS_ESM_OP_TRUE == pEpsCntxtInfo->bitOpApn )
        {
            pSmAppNdisConnCnfCnf->bitOpApn = NAS_ESM_OP_TRUE;
            NAS_ESM_MEM_CPY_S(  (VOS_VOID*)&(pSmAppNdisConnCnfCnf->stApnInfo),
                                sizeof(APP_ESM_APN_INFO_STRU),
                                (VOS_VOID*)&(pEpsCntxtInfo->stApnInfo),
                                sizeof(APP_ESM_APN_INFO_STRU));
        }

        /*设置SDF QOS参数*/
        pstSdfCntxtInfo = NAS_ESM_GetSdfCntxtInfo(pSmAppNdisConnCnfCnf->ulCid);
        if( NAS_ESM_OP_TRUE == pEpsCntxtInfo->bitOpEpsQos )
        {
            pSmAppNdisConnCnfCnf->bitOpSdfQos= NAS_ESM_OP_TRUE;
            NAS_ESM_MEM_CPY_S(  (VOS_VOID*)&(pSmAppNdisConnCnfCnf->stSdfQosInfo),
                                sizeof(APP_ESM_EPS_QOS_INFO_STRU),
                                (VOS_VOID*)(&pstSdfCntxtInfo->stSdfQosInfo.stQosInfo),
                                sizeof(APP_ESM_EPS_QOS_INFO_STRU));
        }

        /*设置PCO信息*/
        if(NAS_ESM_OP_TRUE == pEpsCntxtInfo->bitOpPco)
        {
            NAS_ESM_SetNdisConnCnfMsgPcoInfo(pSmAppNdisConnCnfCnf,pEpsCntxtInfo);
        }

    }
    else
    {
        pSmAppNdisConnCnfCnf->bitOpBearerState    = NAS_ESM_OP_FALSE;
        pSmAppNdisConnCnfCnf->bitOpBearerType     = NAS_ESM_OP_FALSE;
        pSmAppNdisConnCnfCnf->bitOpPdnAddr        = NAS_ESM_OP_FALSE;
        pSmAppNdisConnCnfCnf->bitOpApn            = NAS_ESM_OP_FALSE;
        pSmAppNdisConnCnfCnf->bitOpSdfQos         = NAS_ESM_OP_FALSE;

        pSmAppNdisConnCnfCnf->bitOpDnsPrim        = NAS_ESM_OP_FALSE;
        pSmAppNdisConnCnfCnf->bitOpDnsSec         = NAS_ESM_OP_FALSE;
        pSmAppNdisConnCnfCnf->bitOpPCscfPrim      = NAS_ESM_OP_FALSE;
        pSmAppNdisConnCnfCnf->bitOpPCscfSec       = NAS_ESM_OP_FALSE;
        pSmAppNdisConnCnfCnf->bitOpGateWayAddrInfo= NAS_ESM_OP_FALSE;
    }

    /*填写消息头*/
    NAS_ESM_WRITE_TAF_MSG_HEAD(pSmAppNdisConnCnfCnf,ID_APP_ESM_NDISCONN_CNF,\
                              usOriginalId,usTerminalId,\
                              pstEsmAppCnfMsg->ulSn);

    /*调用消息发送函数 */
    NAS_ESM_SND_MSG(pSmAppNdisConnCnfCnf);

}
/*lint -specific(+e433)*/



/*****************************************************************************
  Function Name   : NAS_ESM_SndEsmAppSdfSetupIndMsg
  Description     : SM向APP返回消息ID_APP_ESM_PDP_SETUP_IND
  Input           : ulEpsbId
                    ulRslt
  Output          : None
  Return          : VOS_VOID

  History         :
     1.zhuyiqiang 00138739      2008-9-11   Draft Enact
     2.zhuyiqiang 00138739      2009-02-16  Modify
     3.lihong00150010           2010-08-12  Modify
 *****************************************************************************/
/*lint -specific(-e433)*/
VOS_VOID NAS_ESM_SndEsmAppSdfSetupIndMsg
(
    VOS_UINT32                          ulStateTblIndex,
    VOS_UINT32                          ulRslt
)
{
    VOS_UINT32                          ulOpId              = NAS_ESM_NULL;
    VOS_UINT32                          ulCid               = NAS_ESM_NULL;
    VOS_UINT16                          usOriginalId        = NAS_ESM_NULL;
    VOS_UINT16                          usTerminalId        = NAS_ESM_NULL;
    APP_ESM_PDP_SETUP_IND_STRU         *pSmAppSetupInd      = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pEpsCntxtInfo       = VOS_NULL_PTR;
    NAS_ESM_STATE_INFO_STRU            *pStateTblAddr       = VOS_NULL_PTR;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo     = VOS_NULL_PTR;


    /*根据ulOpId，分配一个ulOpId参数*/
    ulOpId = NAS_ESM_OPID_TYPE_SETUP_IND;

    /*获得本地StateTbl指针*/
    pStateTblAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    /*获得关联的CID参数*/
    ulCid = pStateTblAddr->ulCid;

    /*分配空间并检验分配是否成功*/
    /*lint -e433 -e826*/
    pSmAppSetupInd = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(APP_ESM_PDP_SETUP_IND_STRU));
    /*lint +e433 +e826*/
    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pSmAppSetupInd)
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEsmAppSdfSetupIndMsg:ERROR:APP->SM,Memory Alloc FAIL!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEsmAppSdfSetupIndMsg_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*清空*/
    NAS_ESM_MEM_SET_S(  NAS_ESM_GET_MSG_ENTITY(pSmAppSetupInd),
                        NAS_ESM_GET_MSG_LENGTH(pSmAppSetupInd),
                        0,
                        NAS_ESM_GET_MSG_LENGTH(pSmAppSetupInd));

    /*分配本次过程APP_MSG_HEADER*/
    NAS_ESM_AssignMidHeader(&usOriginalId,&usTerminalId);

    /*填写消息头*/
    NAS_ESM_WRITE_TAF_MSG_HEAD(pSmAppSetupInd,ID_APP_ESM_PDP_SETUP_IND,\
                              usOriginalId,usTerminalId,0);

    /*封装消息内容*/
    pSmAppSetupInd->ulCid = ulCid;
    pSmAppSetupInd->ulOpId= ulOpId;

    pSmAppSetupInd->ulRslt = ulRslt;

    if (APP_SUCCESS == ulRslt)
    {
        /*获得本地EpsB承载上下文结构指针*/
        pEpsCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(pStateTblAddr->ulEpsbId);

        pSmAppSetupInd->bitOpBearerState = NAS_ESM_OP_TRUE;
        pSmAppSetupInd->enBearerState = pEpsCntxtInfo->enBearerCntxtState;

        pSmAppSetupInd->bitOpBearerType = NAS_ESM_OP_TRUE;
        pSmAppSetupInd->enBearerType = pEpsCntxtInfo->enBearerCntxtType;

        /* 若是专有承载，则赋值LinkCid */
        pSmAppSetupInd->ulLinkCid = NAS_ESM_GetLinkCidByActiveCid(pSmAppSetupInd->ulCid);
        if (NAS_ESM_ILL_CID != pSmAppSetupInd->ulLinkCid)
        {
            pSmAppSetupInd->bitOpLinkCid = NAS_ESM_OP_TRUE;
        }
        else
        {
            pSmAppSetupInd->bitOpLinkCid = NAS_ESM_OP_FALSE;
        }

        if(NAS_ESM_OP_TRUE == pEpsCntxtInfo->bitOpPdnAddr)
        {
            pSmAppSetupInd->bitOpPdnAddr = NAS_ESM_OP_TRUE;
            NAS_ESM_MEM_CPY_S(  (VOS_VOID*)&(pSmAppSetupInd->stPDNAddrInfo),
                                sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU),
                                (VOS_VOID*)&(pEpsCntxtInfo->stPdnAddrInfo),
                                sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU));

            NAS_ESM_MEM_CPY_S(  (VOS_VOID*)&(pSmAppSetupInd->stSubnetMask),
                                sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU),
                                (VOS_VOID*)&(pEpsCntxtInfo->stSubnetMask),
                                sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU));
        }

        if(NAS_ESM_OP_TRUE == pEpsCntxtInfo->bitOpGateWayAddrInfo)
        {
            pSmAppSetupInd->bitOpGateWayAddrInfo = NAS_ESM_OP_TRUE;
            NAS_ESM_MEM_CPY_S(  (VOS_VOID*)&(pSmAppSetupInd->stGateWayAddrInfo),
                                sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU),
                                (VOS_VOID*)&(pEpsCntxtInfo->stGateWayAddrInfo),
                                sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU));
        }

        pSmAppSetupInd->bitOpRabId = NAS_ESM_OP_TRUE;
        pSmAppSetupInd->ulRabId = pEpsCntxtInfo->ulEpsbId;

        /*设置APN参数*/
        if(NAS_ESM_OP_TRUE == pEpsCntxtInfo->bitOpApn)
        {
            pSmAppSetupInd->bitOpApn = NAS_ESM_OP_TRUE;

            NAS_ESM_MEM_CPY_S(  (VOS_VOID*)&(pSmAppSetupInd->stApnInfo),
                                sizeof(APP_ESM_APN_INFO_STRU),
                                (VOS_VOID*)&(pEpsCntxtInfo->stApnInfo),
                                sizeof(APP_ESM_APN_INFO_STRU));
        }

        /*设置SDF QOS参数*/
        pstSdfCntxtInfo = NAS_ESM_GetSdfCntxtInfo(ulCid);
        if( NAS_ESM_OP_TRUE == pEpsCntxtInfo->bitOpEpsQos )
        {
            pSmAppSetupInd->bitOpSdfQos= NAS_ESM_OP_TRUE;
            NAS_ESM_MEM_CPY_S(  (VOS_VOID*)&(pSmAppSetupInd->stSdfQosInfo),
                                sizeof(APP_ESM_EPS_QOS_INFO_STRU),
                                (VOS_VOID*)(&pstSdfCntxtInfo->stSdfQosInfo.stQosInfo),
                                sizeof(APP_ESM_EPS_QOS_INFO_STRU));
        }

        /*设置PCO信息*/
        if(NAS_ESM_OP_TRUE == pEpsCntxtInfo->bitOpPco)
        {
            NAS_ESM_ProcSetUpMsgPcoInfo(pSmAppSetupInd,pEpsCntxtInfo);

        }

        /*调用消息发送函数 */
        NAS_ESM_SND_MSG(pSmAppSetupInd);

        NAS_ESM_SndEsmAppBearerQosIndMsg(pStateTblAddr->ulEpsbId);
    }
    else
    {
        pSmAppSetupInd->bitOpBearerState    = NAS_ESM_OP_FALSE;
        pSmAppSetupInd->bitOpBearerType     = NAS_ESM_OP_FALSE;
        pSmAppSetupInd->bitOpPdnAddr        = NAS_ESM_OP_FALSE;
        pSmAppSetupInd->bitOpApn            = NAS_ESM_OP_FALSE;
        pSmAppSetupInd->bitOpSdfQos         = NAS_ESM_OP_FALSE;
        pSmAppSetupInd->bitOpLinkCid        = NAS_ESM_OP_FALSE;
        pSmAppSetupInd->bitOpDnsPrim        = NAS_ESM_OP_FALSE;
        pSmAppSetupInd->bitOpDnsSec         = NAS_ESM_OP_FALSE;
        pSmAppSetupInd->bitOpPCscfPrim      = NAS_ESM_OP_FALSE;
        pSmAppSetupInd->bitOpPCscfSec       = NAS_ESM_OP_FALSE;
        pSmAppSetupInd->bitOpRabId          = NAS_ESM_OP_FALSE;
        pSmAppSetupInd->bitOpGateWayAddrInfo= NAS_ESM_OP_FALSE;

        /*调用消息发送函数 */
        NAS_ESM_SND_MSG(pSmAppSetupInd);
    }
}
/*lint -specific(+e433)*/

/*****************************************************************************
 Function Name   : NAS_ESM_SndEsmAppSdfModCnfMsg
 Description     : SM向APP返回消息：ID_APP_ESM_PDP_MODIFY_CNF
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong 00150010      2009-4-21  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_SndEsmAppSdfModCnfMsg
(
    const NAS_ESM_APP_CNF_MSG_STRU      *pstEsmAppCnfMsg
)
{
    VOS_UINT16                          usOriginalId        = NAS_ESM_NULL;
    VOS_UINT16                          usTerminalId        = NAS_ESM_NULL;
    APP_ESM_PDP_MODIFY_CNF_STRU        *pSmAppModCnf        = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pEpsCntxtInfo       = VOS_NULL_PTR;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo     = VOS_NULL_PTR;


    /*分配空间并检验分配是否成功*/
    pSmAppModCnf = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(APP_ESM_PDP_MODIFY_CNF_STRU));

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pSmAppModCnf)
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEsmAppSdfModCnfMsg:ERROR:APP->SM,Memory Alloc FAIL!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEsmAppSdfModCnfMsg_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*清空*/
    NAS_ESM_MEM_SET_S(  NAS_ESM_GET_MSG_ENTITY(pSmAppModCnf),
                        NAS_ESM_GET_MSG_LENGTH(pSmAppModCnf),
                        0,
                        NAS_ESM_GET_MSG_LENGTH(pSmAppModCnf));

    /* 获取修改类型 */
    if ( NAS_ESM_OP_TRUE == pstEsmAppCnfMsg->bitOpModifyType )
    {
        pSmAppModCnf->enBearerModifyType = pstEsmAppCnfMsg->enModfyType;
    }
    else
    {
        NAS_ESM_WARN_LOG("NAS_ESM_SndEsmAppSdfModCnfMsg : Warning --> error modify type.");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_SndEsmAppSdfModCnfMsg_ENUM, 1);
        pSmAppModCnf->enBearerModifyType = APP_ESM_BEARER_MODIFY_BUTT;
    }

    if( NAS_ESM_OP_TRUE == pstEsmAppCnfMsg->bitOpEpsbId )
    {
        /*填充ulRabId参数*/
        pSmAppModCnf->bitOpRabId = NAS_ESM_OP_TRUE;
        pSmAppModCnf->ulRabId = pstEsmAppCnfMsg->ulEpsbId;
    }
    else
    {
        pSmAppModCnf->bitOpRabId = NAS_ESM_OP_FALSE;
    }

    /*填充ulCid参数*/
    pSmAppModCnf->ulCid = pstEsmAppCnfMsg->ulCId;

    /*填充ulOpId参数*/
    pSmAppModCnf->ulOpId = pstEsmAppCnfMsg->ulOpId;

    /*填充MID参数*/
    usTerminalId = pstEsmAppCnfMsg->usOriginalId;
    usOriginalId = pstEsmAppCnfMsg->usTerminalId;

    /*填充ulErrorCode参数*/
    if(NAS_ESM_OP_TRUE == pstEsmAppCnfMsg->bitOpErrorCode)
    {
        pSmAppModCnf->ulRslt = pstEsmAppCnfMsg->ulErrorCode;
    }
    else
    {
        /*如果bitOpErrorCode为false,当前错误码为空，表示没错误*/
        pSmAppModCnf->ulRslt = APP_SUCCESS;
    }


    /*若承载建立成功*/
    if((NAS_ESM_SUCCESS == pstEsmAppCnfMsg->ulRst)
       &&(NAS_ESM_OP_TRUE == pstEsmAppCnfMsg->bitOpEpsbId))
    {
        pEpsCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(pstEsmAppCnfMsg->ulEpsbId);

        /*承载状态赋值*/
        pSmAppModCnf->bitOpBearerState = NAS_ESM_OP_TRUE;
        pSmAppModCnf->enBearerState = pEpsCntxtInfo->enBearerCntxtState;

        /*承载类型赋值*/
        pSmAppModCnf->bitOpBearerType = NAS_ESM_OP_TRUE;
        pSmAppModCnf->enBearerType = pEpsCntxtInfo->enBearerCntxtType;

         /*设置SDF QOS参数*/
         pstSdfCntxtInfo = NAS_ESM_GetSdfCntxtInfo(pSmAppModCnf->ulCid);
         if( NAS_ESM_OP_TRUE == pEpsCntxtInfo->bitOpEpsQos )
         {
             pSmAppModCnf->bitOpSdfQos= NAS_ESM_OP_TRUE;
             NAS_ESM_MEM_CPY_S( (VOS_VOID*)&(pSmAppModCnf->stSdfQosInfo),
                                sizeof(APP_ESM_EPS_QOS_INFO_STRU),
                                (VOS_VOID*)(&pstSdfCntxtInfo->stSdfQosInfo.stQosInfo),
                                sizeof(APP_ESM_EPS_QOS_INFO_STRU));
         }
    }
    else
    {
        pSmAppModCnf->bitOpBearerState = NAS_ESM_OP_FALSE;
        pSmAppModCnf->bitOpBearerType = NAS_ESM_OP_FALSE;
        pSmAppModCnf->bitOpSdfQos = NAS_ESM_OP_FALSE;
    }

    /*填写消息头*/
    NAS_ESM_WRITE_TAF_MSG_HEAD(pSmAppModCnf,ID_APP_ESM_PDP_MODIFY_CNF,\
                              usOriginalId,usTerminalId,\
                              pstEsmAppCnfMsg->ulSn);

    /*调用消息发送函数 */
    NAS_ESM_SND_MSG(pSmAppModCnf);

}

/*****************************************************************************
Function Name   : NAS_ESM_SndEsmAppSdfModIndMsg
Description     : SM向APP返回消息:ID_APP_ESM_PDP_MODIFY_IND;
Input           : ulEpsbId
Output          : None
Return          : VOS_VOID

History         :
 1.zhuyiqiang 00138739      2008-9-11  Draft Enact
 2.zhuyiqiang 00138739      2009-02-16  Modify
*****************************************************************************/
VOS_VOID NAS_ESM_SndEsmAppSdfModIndMsg
(
    VOS_UINT32                          ulStateTblIndex,
    APP_ESM_BEARER_MODIFY_ENUM_UINT32   enModfyType
)
{
    VOS_UINT32                          ulOpId              = NAS_ESM_NULL;
    VOS_UINT32                          ulCid               = NAS_ESM_NULL;
    VOS_UINT16                          usOriginalId        = NAS_ESM_NULL;
    VOS_UINT16                          usTerminalId        = NAS_ESM_NULL;
    APP_ESM_PDP_MODIFY_IND_STRU        *pSmAppModifyInd     = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pEpsCntxtInfo       = VOS_NULL_PTR;
    NAS_ESM_STATE_INFO_STRU            *pStateTblAddr       = VOS_NULL_PTR;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo     = VOS_NULL_PTR;

    /*根据ulOpId，分配一个ulOpId参数*/
    ulOpId = NAS_ESM_OPID_TYPE_MODIFY_IND;

    /*获得本地StateTbl指针*/
    pStateTblAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    /*根据ulOpId，查找对应承载类型*/
    pEpsCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(pStateTblAddr->ulEpsbId);

    /*获得关联的CID参数*/
    ulCid = pStateTblAddr->ulCid;

    /*分配空间并检验分配是否成功*/
    pSmAppModifyInd = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(APP_ESM_PDP_MODIFY_IND_STRU));

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pSmAppModifyInd)
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEsmAppSdfModIndMsg:ERROR:APP->SM,Memory Alloc FAIL!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEsmAppSdfModCnfMsg_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*清空*/
    NAS_ESM_MEM_SET_S(  NAS_ESM_GET_MSG_ENTITY(pSmAppModifyInd),
                        NAS_ESM_GET_MSG_LENGTH(pSmAppModifyInd),
                        0,
                        NAS_ESM_GET_MSG_LENGTH(pSmAppModifyInd));

    /*分配本次过程APP_MSG_HEADER*/
    NAS_ESM_AssignMidHeader(&usOriginalId,&usTerminalId);

    /*填写消息头*/
    NAS_ESM_WRITE_TAF_MSG_HEAD(pSmAppModifyInd,ID_APP_ESM_PDP_MODIFY_IND,\
                               usOriginalId,usTerminalId,0);

    /*封装消息内容*/
    pSmAppModifyInd->ulCid = ulCid;
    pSmAppModifyInd->ulOpId= ulOpId;

    pSmAppModifyInd->enBearerModifyType = enModfyType;

    pSmAppModifyInd->ulRslt = APP_SUCCESS;

    pSmAppModifyInd->bitOpBearerState = NAS_ESM_OP_TRUE;
    pSmAppModifyInd->enBearerState = pEpsCntxtInfo->enBearerCntxtState;

    pSmAppModifyInd->bitOpBearerType = NAS_ESM_OP_TRUE;
    pSmAppModifyInd->enBearerType = pEpsCntxtInfo->enBearerCntxtType;


    pSmAppModifyInd->bitOpRabId = NAS_ESM_OP_TRUE;
    pSmAppModifyInd->ulRabId = pEpsCntxtInfo->ulEpsbId;


    /*设置SDF QOS参数*/
    pstSdfCntxtInfo = NAS_ESM_GetSdfCntxtInfo(ulCid);
    if( NAS_ESM_OP_TRUE == pEpsCntxtInfo->bitOpEpsQos )
    {
        pSmAppModifyInd->bitOpSdfQos= NAS_ESM_OP_TRUE;

        NAS_ESM_MEM_CPY_S(  (VOS_VOID*)&(pSmAppModifyInd->stSdfQosInfo),
                            sizeof(APP_ESM_EPS_QOS_INFO_STRU),
                            (VOS_VOID*)(&pstSdfCntxtInfo->stSdfQosInfo.stQosInfo),
                            sizeof(APP_ESM_EPS_QOS_INFO_STRU));
    }


    /*调用消息发送函数 */
    NAS_ESM_SND_MSG(pSmAppModifyInd);
}

/******************************************************************************
  Function Name   : NAS_ESM_SndEsmAppSdfRelIndMsg
  Description     : SM向APP返回消息:ID_APP_ESM_PDP_RELEASE_IND;
  Input           : ulEpsbId
  Output          : None
  Return          : VOS_VOID

  History         :
     1.zhuyiqiang 00138739      2008-9-11  Draft Enact
     2.zhuyiqiang 00138739      2009-02-16  Modify
 *****************************************************************************/
VOS_VOID NAS_ESM_SndEsmAppSdfRelIndMsg
(
    VOS_UINT32                          ulCid,
    VOS_UINT32                          ulEpsbId
)
{
    VOS_UINT32                          ulOpId              = NAS_ESM_NULL;
    VOS_UINT16                          usOriginalId        = NAS_ESM_NULL;
    VOS_UINT16                          usTerminalId        = NAS_ESM_NULL;
    APP_ESM_PDP_RELEASE_IND_STRU       *pSmAppRelInd        = VOS_NULL_PTR;
     NAS_ESM_EPSB_CNTXT_INFO_STRU      *pEpsCntxtInfo       = VOS_NULL_PTR;

     NAS_ESM_LOG2("NAS_ESM_SndEsmAppSdfRelIndMsg", ulCid, ulEpsbId);
     TLPS_PRINT2LAYER_INFO2(NAS_ESM_SndEsmAppSdfRelIndMsg_ENUM, LNAS_ENTRY, ulCid, ulEpsbId);

    /*根据ulOpId，分配一个ulOpId参数*/
    ulOpId = NAS_ESM_OPID_TYPE_RELEASE_IND;

    /*根据ulEpsbId，查找对应承载类型*/
    pEpsCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);

    /*分配空间并检验分配是否成功*/
    pSmAppRelInd = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(APP_ESM_PDP_RELEASE_IND_STRU));

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pSmAppRelInd)
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEsmAppSdfRelIndMsg:ERROR:APP->SM,Memory Alloc FAIL!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEsmAppSdfRelIndMsg_ENUM, LNAS_NULL_PTR);

        return ;
    }

    /*清空*/
    NAS_ESM_MEM_SET_S(  NAS_ESM_GET_MSG_ENTITY(pSmAppRelInd),
                        NAS_ESM_GET_MSG_LENGTH(pSmAppRelInd),
                        0,
                        NAS_ESM_GET_MSG_LENGTH(pSmAppRelInd));

    /*分配本次过程APP_MSG_HEADER*/
    NAS_ESM_AssignMidHeader(&usOriginalId,&usTerminalId);

    /*填写消息头*/
    NAS_ESM_WRITE_TAF_MSG_HEAD(pSmAppRelInd,ID_APP_ESM_PDP_RELEASE_IND,\
                              usOriginalId,usTerminalId,0);

    /*封装消息内容*/
    pSmAppRelInd->ulCid = ulCid;
    pSmAppRelInd->ulOpId= ulOpId;

    pSmAppRelInd->ulRslt = APP_SUCCESS;

    /* 拷贝PDN信息 */
    pSmAppRelInd->bitOpPdnAddr = pEpsCntxtInfo->bitOpPdnAddr;

    NAS_ESM_MEM_CPY_S(  &pSmAppRelInd->stPDNAddrInfo,
                        sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU),
                        &pEpsCntxtInfo->stPdnAddrInfo,
                        sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU));

    /* 若是专有承载，则赋值LinkCid */
    pSmAppRelInd->ulLinkCid = NAS_ESM_GetLinkCidByActiveCid(pSmAppRelInd->ulCid);
    if (NAS_ESM_ILL_CID != pSmAppRelInd->ulLinkCid)
    {
        pSmAppRelInd->bitOpLinkCid = NAS_ESM_OP_TRUE;
    }
    else
    {
        pSmAppRelInd->bitOpLinkCid = NAS_ESM_OP_FALSE;
    }

    pSmAppRelInd->ulEpsbId = ulEpsbId;

    /*调用消息发送函数 */
    NAS_ESM_SND_MSG(pSmAppRelInd);

}



VOS_VOID NAS_ESM_SndEsmAppSdfRelCnfMsg( const NAS_ESM_APP_CNF_MSG_STRU *pstEsmAppCnfMsg )
{
    VOS_UINT16                          usOriginalId        = NAS_ESM_NULL;
    VOS_UINT16                          usTerminalId        = NAS_ESM_NULL;
    APP_ESM_PDP_RELEASE_CNF_STRU       *pSmAppRelCnf       = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU        *pEpsCntxtInfo      = VOS_NULL_PTR;

    /*分配空间并检验分配是否成功*/
    pSmAppRelCnf = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(APP_ESM_PDP_RELEASE_CNF_STRU));

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pSmAppRelCnf)
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEsmAppSdfRelCnfMsg:ERROR:APP->SM,Memory Alloc FAIL!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEsmAppSdfRelCnfMsg_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*清空*/
    NAS_ESM_MEM_SET_S(  NAS_ESM_GET_MSG_ENTITY(pSmAppRelCnf),
                        NAS_ESM_GET_MSG_LENGTH(pSmAppRelCnf),
                        0,
                        NAS_ESM_GET_MSG_LENGTH(pSmAppRelCnf));

    /*填充ulCid参数*/
    pSmAppRelCnf->ulCid = pstEsmAppCnfMsg->ulCId;

    /*填充ulOpId参数*/
    pSmAppRelCnf->ulOpId = pstEsmAppCnfMsg->ulOpId;

    /*填充MID参数*/
    usTerminalId = pstEsmAppCnfMsg->usOriginalId;
    usOriginalId = pstEsmAppCnfMsg->usTerminalId;

    /*填充ulErrorCode参数*/
    if(NAS_ESM_OP_TRUE == pstEsmAppCnfMsg->bitOpErrorCode)
    {
        pSmAppRelCnf->ulRslt = pstEsmAppCnfMsg->ulErrorCode;
    }
    else
    {
        pSmAppRelCnf->ulRslt = APP_SUCCESS;
    }

    /*承载释放CNF消息*/
    if ((NAS_ESM_SUCCESS == pstEsmAppCnfMsg->ulRst)
       &&(NAS_ESM_OP_TRUE == pstEsmAppCnfMsg->bitOpEpsbId))
    {
        pEpsCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(pstEsmAppCnfMsg->ulEpsbId);

        /* 拷贝PDN信息 */
        pSmAppRelCnf->bitOpPdnAddr = pEpsCntxtInfo->bitOpPdnAddr;

        NAS_ESM_MEM_CPY_S(  &pSmAppRelCnf->stPDNAddrInfo,
                            sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU),
                            &pEpsCntxtInfo->stPdnAddrInfo,
                            sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU));

        /* 若是专有承载，则赋值LinkCid */
        pSmAppRelCnf->ulLinkCid = NAS_ESM_GetLinkCidByActiveCid(pSmAppRelCnf->ulCid);
        if (NAS_ESM_ILL_CID != pSmAppRelCnf->ulLinkCid)
        {
            pSmAppRelCnf->bitOpLinkCid = NAS_ESM_OP_TRUE;
        }
        else
        {
            pSmAppRelCnf->bitOpLinkCid = NAS_ESM_OP_FALSE;
        }
    }
    else
    {
        pSmAppRelCnf->bitOpLinkCid = NAS_ESM_OP_FALSE;
        pSmAppRelCnf->bitOpPdnAddr = NAS_ESM_OP_FALSE;
    }

    /*填写消息头*/
    NAS_ESM_WRITE_TAF_MSG_HEAD(pSmAppRelCnf,ID_APP_ESM_PDP_RELEASE_CNF,\
                               usOriginalId,usTerminalId,\
                               pstEsmAppCnfMsg->ulSn);

    /*调用消息发送函数 */
    NAS_ESM_SND_MSG(pSmAppRelCnf);

}

/*****************************************************************************
 Function Name   : NAS_ESM_SaveAppOpId
 Description     : 保存APP消息中的OpId参数
 Input           : VOS_UINT32 ulEpsbId
                   VOS_UINT32 ulOpId
 Output          : None
 Return          : VOS_VOID

 History         :
    1.zhuyiqiang 00138739      2008-9-18  Draft Enact
    2.sunbing 49683            2009-02-05 Modify
*****************************************************************************/
VOS_VOID NAS_ESM_SaveAppOpId( VOS_UINT32 ulStateTblIndex, VOS_UINT32 ulOpId )
{
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr =  VOS_NULL_PTR;

    /*根据参数ulStateTblIndex，查找状态表位置*/
    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    /*保存ulOpId参数*/
    pstStateAddr->stAppMsgRecord.ulAppMsgOpId = ulOpId;
}

/*****************************************************************************
 Function Name   : NAS_ESM_SaveAppMidHeader
 Description     : 保存APP消息头APP_PS_MSG_HEADER中的MID值
 Input           :  VOS_UINT32 ulEpsbId,
                    VOS_UINT32  ulOriMid,
                    VOS_UINT32 ulTerMid
 Output          : None
 Return          : VOS_VOID

 History         :
    1.zhuyiqiang 00138739      2008-9-20  Draft Enact
    2.sunbing 49683            2009-02-05 Modify
*****************************************************************************/
VOS_VOID NAS_ESM_SaveAppMidHeader( VOS_UINT32 ulStateTblIndex,
                                                VOS_UINT16  usOriMid,
                                                VOS_UINT16 usTerMid)

{
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr =  VOS_NULL_PTR;

    /*根据参数ulStateTblIndex，查找状态表位置*/
    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    /*保存APP消息中的MID参数*/
    pstStateAddr->stAppMsgRecord.usOriginalId = usOriMid;
    pstStateAddr->stAppMsgRecord.usTerminalId= usTerMid;
}

/*****************************************************************************
 Function Name   : NAS_ESM_AssignMidHeader
 Description     : 分配APP消息头APP_PS_MSG_HEADER中的MID参数
 Input           : VOS_UINT32  *pulOriMid,
                    VOS_UINT32 *pulTerMid
 Output          : None
 Return          : VOS_VOID

 History         :
    1.zhuyiqiang 00138739      2008-9-24  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_AssignMidHeader( VOS_UINT16  *pusOriMid,VOS_UINT16 *pusTerMid)
{
    /*初始化MID参数值*/
    *pusOriMid = NAS_ESM_APP_ORIGIN_MID;  /*FFS*/
    *pusTerMid = NAS_ESM_APP_TERMIN_MID;
}

/*****************************************************************************
 Function Name   : NAS_ESM_SaveAppMsgType
 Description     : 保存收到的APP消息
 Input           : VOS_UINT32 ulEpsbId,
                    APP_ESM_MSG_TYPE_ENUM_UINT32 enAppMsgType
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhuyiqiang 00138739      2008-10-7  Draft Enact
    2.sunbing 49683            2009-02-05 Modify
*****************************************************************************/
VOS_VOID  NAS_ESM_SaveAppMsgType( VOS_UINT32 ulStateTblIndex, APP_ESM_MSG_TYPE_ENUM_UINT32 enAppMsgType )
{
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr =  VOS_NULL_PTR;

    /*根据参数ulStateTblIndex，查找状态表位置*/
    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    /*保存APP消息类型*/
    pstStateAddr->stAppMsgRecord.enAppMsgType = enAppMsgType;
}
/*****************************************************************************
 Function Name   : NAS_ESM_SaveLinkedEpbsId
 Description     : 保存关联EPSBID
 Input           : VOS_UINT32 ulStateTblIndex,
                   VOS_UINT32 ulLinkedEpsbId
 Output          : None
 Return          : None

 History         :
    1.dingli 00128736      2008-10-29  Draft Enact
    2.sunbing 49683        2009-02-05  Modify
*****************************************************************************/
VOS_VOID  NAS_ESM_SaveLinkedEpbsId( VOS_UINT32 ulStateTblIndex, VOS_UINT32 ulLinkedEpsbId )
{
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr =  VOS_NULL_PTR;

    /*根据参数ulStateTblIndex，查找状态表位置*/
    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    /*保存APP消息类型*/
    pstStateAddr->ulLinkedEpsbId = ulLinkedEpsbId;
}

/*****************************************************************************
 Function Name   : NAS_ESM_ProcSetUpMsgPcoInfo
 Description     : 通过APP_ESM_PDP_SETUP_IND消息上报用户网关鉴权信息
 Input           : VOS_VOID *pstRsvMsg
                   VOS_VOID *pstCntxtInfo
 Output          : None
 Return          : VOS_VOID

 History         :
    1.    leili  00132387      2010-7-16  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_ProcSetUpMsgPcoInfo( VOS_VOID *pstRsvMsg ,VOS_VOID *pstCntxtInfo)
{
    APP_ESM_PDP_SETUP_IND_STRU         *pstSmAppSetup       = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsCntxtInfo     = VOS_NULL_PTR;
    NAS_ESM_PCO_TRANSFORM_STRU          stTransPco          = {NAS_ESM_NULL};

    pstEpsCntxtInfo = pstCntxtInfo;
    pstSmAppSetup = pstRsvMsg;

    NAS_ESM_TransformPcoStru(   pstEpsCntxtInfo->stPdnAddrInfo.ucIpType,
                                &(pstEpsCntxtInfo->stPcoInfo),
                                &stTransPco);

    if (stTransPco.ucDnsSerNum == 0)
    {
        NAS_ESM_INFO_LOG("NAS_ESM_ProcSetUpMsgPcoInfo:Dns is not exist!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcSetUpMsgPcoInfo_ENUM, 1);
        pstSmAppSetup->bitOpDnsPrim    = NAS_ESM_OP_FALSE;
        pstSmAppSetup->bitOpDnsSec     = NAS_ESM_OP_FALSE;
    }
    else if (stTransPco.ucDnsSerNum == 1)
    {
        NAS_ESM_INFO_LOG("NAS_ESM_ProcSetUpMsgPcoInfo:Prim Dns is exist!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcSetUpMsgPcoInfo_ENUM, 2);
        pstSmAppSetup->bitOpDnsPrim    = NAS_ESM_OP_TRUE;

        NAS_ESM_MEM_CPY_S(  (VOS_VOID*)&(pstSmAppSetup->stDnsPrimAddrInfo),
                            sizeof(APP_ESM_IP_ADDR_STRU),
                            (VOS_VOID*)&(stTransPco.astDnsServer[0]),
                            sizeof(APP_ESM_IP_ADDR_STRU));

        pstSmAppSetup->bitOpDnsSec     = NAS_ESM_OP_FALSE;
    }
    else
    {
        NAS_ESM_INFO_LOG("NAS_ESM_ProcSetUpMsgPcoInfo:Dns is exist!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcSetUpMsgPcoInfo_ENUM, 3);
        pstSmAppSetup->bitOpDnsPrim    = NAS_ESM_OP_TRUE;
        pstSmAppSetup->bitOpDnsSec     = NAS_ESM_OP_TRUE;

        NAS_ESM_MEM_CPY_S(  (VOS_VOID*)&(pstSmAppSetup->stDnsPrimAddrInfo),
                            sizeof(APP_ESM_IP_ADDR_STRU),
                            (VOS_VOID*)&(stTransPco.astDnsServer[0]),
                            sizeof(APP_ESM_IP_ADDR_STRU));

        NAS_ESM_MEM_CPY_S(  (VOS_VOID*)&(pstSmAppSetup->stDnsSecAddrInfo),
                            sizeof(APP_ESM_IP_ADDR_STRU),
                            (VOS_VOID*)&(stTransPco.astDnsServer[1]),
                            sizeof(APP_ESM_IP_ADDR_STRU));
    }

    if (stTransPco.ucPcscfNum == 0)
    {
        NAS_ESM_INFO_LOG("NAS_ESM_ProcSetUpMsgPcoInfo:P-CSCF is not exist!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcSetUpMsgPcoInfo_ENUM, 4);
        pstSmAppSetup->bitOpPCscfPrim  = NAS_ESM_OP_FALSE;
        pstSmAppSetup->bitOpPCscfSec   = NAS_ESM_OP_FALSE;
    }
    else if (stTransPco.ucPcscfNum == 1)
    {
        NAS_ESM_INFO_LOG("NAS_ESM_ProcSetUpMsgPcoInfo:Prim P-CSCF is exist!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcSetUpMsgPcoInfo_ENUM, 5);
        pstSmAppSetup->bitOpPCscfPrim  = NAS_ESM_OP_TRUE;

        NAS_ESM_MEM_CPY_S(  (VOS_VOID*)&(pstSmAppSetup->stPCscfPrimAddrInfo),
                            sizeof(APP_ESM_IP_ADDR_STRU),
                            (VOS_VOID*)&(stTransPco.astPcscf[0]),
                            sizeof(APP_ESM_IP_ADDR_STRU));

        pstSmAppSetup->bitOpPCscfSec   = NAS_ESM_OP_FALSE;
    }
    else
    {
        NAS_ESM_INFO_LOG("NAS_ESM_ProcSetUpMsgPcoInfo:P-CSCF is exist!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcSetUpMsgPcoInfo_ENUM, 6);
        pstSmAppSetup->bitOpPCscfPrim  = NAS_ESM_OP_TRUE;
        pstSmAppSetup->bitOpPCscfSec   = NAS_ESM_OP_TRUE;

        NAS_ESM_MEM_CPY_S(  (VOS_VOID*)(VOS_VOID*)&(pstSmAppSetup->stPCscfPrimAddrInfo),
                            sizeof(APP_ESM_IP_ADDR_STRU),
                            (VOS_VOID*)(VOS_VOID*)&(stTransPco.astPcscf[0]),
                            sizeof(APP_ESM_IP_ADDR_STRU));
        NAS_ESM_MEM_CPY_S(  (VOS_VOID*)&(pstSmAppSetup->stPCscfSecAddrInfo),
                            sizeof(APP_ESM_IP_ADDR_STRU),
                            (VOS_VOID*)&(stTransPco.astPcscf[1]),
                            sizeof(APP_ESM_IP_ADDR_STRU));
    }
    return;
}


/*****************************************************************************
 Function Name   : NAS_ESM_AppPdpManageRspMsgRefuseProc
 Description     : App拒绝承载激活或承载修改的处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.liuwenyu      2009-12-4  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_AppPdpManageRspMsgRefuseProc
(
    VOS_UINT32                          ulStateTblIndex
)
{
    NAS_ESM_ENCODE_INFO_STRU            stEncodeInfo;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;
    NAS_ESM_SND_NW_MSG_STRU            *pstEsmSndNwMsg      = VOS_NULL_PTR;

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    /* 判断缓存消息是否存在 */
    if (pstStateAddr->pstDecodedNwMsg == VOS_NULL_PTR)
    {
        NAS_ESM_ERR_LOG("NAS_ESM_AppPdpManageRspMsgRefuseProc:ERROR:Decoded Nw Msg not exist!");
        TLPS_PRINT2LAYER_ERROR1(NAS_ESM_AppPdpManageRspMsgRefuseProc_ENUM, LNAS_NULL_PTR, 1);

        /*释放状态表资源*/
        NAS_ESM_RelStateTblResource(ulStateTblIndex);

        return ;
    }

    /*初始化，并填充NAS_ESM_ENCODE_INFO_STRU*/
    NAS_ESM_MEM_SET_S(  (VOS_VOID*)&stEncodeInfo,
                        sizeof(NAS_ESM_ENCODE_INFO_STRU),
                        0,
                        sizeof(NAS_ESM_ENCODE_INFO_STRU));

    stEncodeInfo.bitOpESMCau = NAS_ESM_OP_TRUE;
    stEncodeInfo.ucESMCau    = NAS_ESM_CAUSE_INSUFFICIENT_RESOURCES;
    stEncodeInfo.ucPti       = pstStateAddr->stNwMsgRecord.ucPti;
    stEncodeInfo.ulEpsbId    = pstStateAddr->pstDecodedNwMsg->ucEpsbId;

    /*分配空间和检测是否分配成功,用于存放SM准备回复给网侧的消息*/
    pstEsmSndNwMsg = NAS_ESM_GetEsmSndNwMsgAddr();
    pstEsmSndNwMsg->pucNwMsg = (VOS_UINT8 *)NAS_ESM_MEM_ALLOC(ESM_MAX_MSG_CONTAINER_CNTNTS_LEN);
    if ( VOS_NULL_PTR == pstEsmSndNwMsg->pucNwMsg )
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_AppPdpManageRspMsgRefuseProc:ERROR:Alloc Snd Nw Msg fail!");
        TLPS_PRINT2LAYER_ERROR1(NAS_ESM_AppPdpManageRspMsgRefuseProc_ENUM, LNAS_NULL_PTR, 2);
        /*释放状态表资源*/
        NAS_ESM_RelStateTblResource(ulStateTblIndex);
        return;
    }

    /* 根据缓存的空口消息类型，给网侧回相应的拒绝消息 */
    switch (pstStateAddr->pstDecodedNwMsg->enEsmCnMsgType)
    {
        case NAS_ESMCN_MSG_TYPE_ACT_DEFLT_EPS_BEARER_CNTXT_REQ:
            NAS_ESM_ActDefltBearFailProc(&stEncodeInfo, ulStateTblIndex);
            break;
        case NAS_ESMCN_MSG_TYPE_ACT_DEDICTD_EPS_BEARER_CNTXT_REQ:
            NAS_ESM_ActDediBearFailProc(&stEncodeInfo, ulStateTblIndex);
            break;
        case NAS_ESMCN_MSG_TYPE_MOD_EPS_BEARER_CNTXT_REQ:
            NAS_ESM_BearModFailProc(&stEncodeInfo, ulStateTblIndex);
            break;
        default:
            NAS_ESM_ERR_LOG("NAS_ESM_AppPdpManageRspMsgRefuseProc:ERROR:Msg type illegal!");
            TLPS_PRINT2LAYER_ERROR(NAS_ESM_AppPdpManageRspMsgRefuseProc_ENUM, LNAS_MSG_INVALID);

            /*释放状态表资源*/
            NAS_ESM_RelStateTblResource(ulStateTblIndex);
            break;
    }

    /*释放空口消息占用的空间*/
    NAS_ESM_MEM_FREE(pstEsmSndNwMsg->pucNwMsg);
    pstEsmSndNwMsg->pucNwMsg    = VOS_NULL_PTR;
    pstEsmSndNwMsg->ulNwMsgSize = NAS_ESM_NULL;
}

/*****************************************************************************
 Function Name   : NAS_ESM_AppPdpManageRspMsgAcceptProc
 Description     : App接受承载激活或承载修改的处理
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-12-4  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_AppPdpManageRspMsgAcceptProc
(
    VOS_UINT32                          ulStateTblIndex
)
{
    NAS_ESM_ENCODE_INFO_STRU            stEncodeInfo;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;
    NAS_ESM_SND_NW_MSG_STRU            *pstEsmSndNwMsg      = VOS_NULL_PTR;

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    /* 判断缓存消息是否存在 */
    if (pstStateAddr->pstDecodedNwMsg == VOS_NULL_PTR)
    {
        NAS_ESM_ERR_LOG("NAS_ESM_AppPdpManageRspMsgAcceptProc:ERROR:Decoded Nw Msg not exist!");
        TLPS_PRINT2LAYER_ERROR1(NAS_ESM_AppPdpManageRspMsgAcceptProc_ENUM, LNAS_NULL_PTR, 1);

        /*释放状态表资源*/
        NAS_ESM_RelStateTblResource(ulStateTblIndex);

        return ;
    }

    /*初始化，并填充NAS_ESM_ENCODE_INFO_STRU*/
    NAS_ESM_MEM_SET_S(  (VOS_VOID*)&stEncodeInfo,
                        sizeof(NAS_ESM_ENCODE_INFO_STRU),
                        0,
                        sizeof(NAS_ESM_ENCODE_INFO_STRU));

    stEncodeInfo.ucPti       = pstStateAddr->stNwMsgRecord.ucPti;
    stEncodeInfo.ulEpsbId    = pstStateAddr->ulEpsbId;

    /*分配空间和检测是否分配成功,用于存放SM准备回复给网侧的消息*/
    pstEsmSndNwMsg = NAS_ESM_GetEsmSndNwMsgAddr();
    pstEsmSndNwMsg->pucNwMsg = (VOS_UINT8 *)NAS_ESM_MEM_ALLOC(ESM_MAX_MSG_CONTAINER_CNTNTS_LEN);
    if ( VOS_NULL_PTR == pstEsmSndNwMsg->pucNwMsg )
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_AppPdpManageRspMsgAcceptProc:ERROR:Alloc Snd Nw Msg fail!");
        TLPS_PRINT2LAYER_ERROR1(NAS_ESM_AppPdpManageRspMsgAcceptProc_ENUM, LNAS_NULL_PTR, 2);
        /*释放状态表资源*/
        NAS_ESM_RelStateTblResource(ulStateTblIndex);
        return;
    }

    /* 根据缓存的空口消息类型，给网侧回相应的拒绝消息 */
    switch (pstStateAddr->pstDecodedNwMsg->enEsmCnMsgType)
    {
        case NAS_ESMCN_MSG_TYPE_ACT_DEFLT_EPS_BEARER_CNTXT_REQ:
            NAS_ESM_DefltBearActMsgAutoAccept(ulStateTblIndex,
                                              stEncodeInfo,
                                              pstStateAddr->pstDecodedNwMsg);
            break;
        case NAS_ESMCN_MSG_TYPE_ACT_DEDICTD_EPS_BEARER_CNTXT_REQ:
            NAS_ESM_DediBearActMsgAutoAccept(ulStateTblIndex,
                                             stEncodeInfo,
                                             pstStateAddr->pstDecodedNwMsg);
            break;
        case NAS_ESMCN_MSG_TYPE_MOD_EPS_BEARER_CNTXT_REQ:
            NAS_ESM_BearModMsgAutoAccept(ulStateTblIndex,
                                         stEncodeInfo,
                                         pstStateAddr->pstDecodedNwMsg);
            break;
        default:
            NAS_ESM_ERR_LOG("NAS_ESM_AppPdpManageRspMsgRefuseProc:ERROR:Msg type illegal!");
            TLPS_PRINT2LAYER_ERROR(NAS_ESM_AppPdpManageRspMsgAcceptProc_ENUM, LNAS_MSG_INVALID);

            /*释放状态表资源*/
            NAS_ESM_RelStateTblResource(ulStateTblIndex);
            break;
    }

    /*释放空口消息占用的空间*/
    NAS_ESM_MEM_FREE(pstEsmSndNwMsg->pucNwMsg);
    pstEsmSndNwMsg->pucNwMsg    = VOS_NULL_PTR;
    pstEsmSndNwMsg->ulNwMsgSize = NAS_ESM_NULL;
}


/*****************************************************************************
 Function Name   : NAS_ESM_AppPdpManageRspMsgAcceptProc
 Description     : App流程终止消息的处理
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.niuxiufan 00181501      2012-01-06  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_AppProcAbortNotifyProc( VOS_VOID *pRcvMsg )
{
    APP_ESM_PROCEDURE_ABORT_NOTIFY_STRU   *pAppMsg = VOS_NULL_PTR;
    NAS_ESM_STATE_INFO_STRU        *pstStateAddr   = VOS_NULL_PTR;
    VOS_UINT32 ulRcvCid  = NAS_ESM_ILL_CID;
    VOS_UINT32 ulStateId = NAS_ESM_ILL_STATETAL_INDEX;

    NAS_ESM_INFO_LOG("NAS_ESM_AppProcAbortNotifyProc enter!");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppProcAbortNotifyProc_ENUM, LNAS_ENTRY);

    pAppMsg = (APP_ESM_PROCEDURE_ABORT_NOTIFY_STRU*)pRcvMsg;

    ulRcvCid = pAppMsg->ulCid;

    if (NAS_ESM_L_MODE_STATUS_NORMAL != NAS_ESM_GetLModeStatus())
    {
        NAS_ESM_WARN_LOG("NAS_ESM_AppProcAbortNotifyProc: L mode is already suspended!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppProcAbortNotifyProc_ENUM, LNAS_EMM_LTE_SUSPEND);
        return;
    }

    if (NAS_ESM_FAILURE == NAS_ESM_QueryStateTblIndexByCid(ulRcvCid, &ulStateId))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_AppProcAbortNotifyProc: CID is not in state table!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppProcAbortNotifyProc_ENUM, ESM_CID_ERROR);
        return;
    }

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateId);

    /* 如果被取消的是紧急承载建立请求，则尝试停止延迟释放非紧急承载定时器 */
    if (NAS_ESM_BEARER_TYPE_EMERGENCY == pstStateAddr->enBearerCntxtType)
    {
        NAS_ESM_TimerStop(0, TI_NAS_ESM_REL_NON_EMC_BEARER);
    }

    if((NAS_ESM_PS_REGISTER_STATUS_ATTACHING == NAS_ESM_GetEmmStatus())
       && (NAS_ESM_OP_TRUE == pstStateAddr->bitOpAppMsgRecord)
       && ((ID_APP_ESM_PDP_SETUP_REQ == pstStateAddr->stAppMsgRecord.enAppMsgType)
            || (ID_APP_ESM_NDISCONN_REQ == pstStateAddr->stAppMsgRecord.enAppMsgType)))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_AppProcAbortNotifyProc: attaching!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppProcAbortNotifyProc_ENUM, 1);

        /* 由于APP建立承载请求导致的ATTACH流程, 则清除动态表中的APP相关标识 */
        /* 则终止ESM流程, 而保证EMM流程继续进行 */
        pstStateAddr->bitOpAppMsgRecord = NAS_ESM_OP_FALSE;
        return;
    }
    else
    {
        /* 如果是非紧急承载，则里通知EMM删除本次ESM流程导致的缓存的消息
           如果是紧急承载，则在释放动态表资源时*/
        if (NAS_ESM_BEARER_TYPE_EMERGENCY != pstStateAddr->enBearerCntxtType)
        {
            NAS_ESM_SndEsmEmmClrEsmProcResNtyMsg(pstStateAddr->ulCid, PS_FALSE);
        }

        /* 其它场景, 直接释放动态表资源 */
        NAS_ESM_RelStateTblResource(ulStateId);
        return;
    }

}
/*****************************************************************************
 Function Name   : NAS_ESM_VerifyAppPppDialSceneAndParam
 Description     : 对PPP拨号的场景及拨号参数进行检查
 Input           : None
 Output          : APP_SUCCESS : 可以发起PPP拨号
                   其它 :原因值
 Return          : VOS_VOID

 History         :
    1.niuxiufan 00181501      2012-01-06  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_ESM_VerifyAppPppDialSceneAndParam( VOS_VOID *pRcvMsg )
{
    APP_ESM_PDP_SETUP_REQ_STRU      *pstAppPdpSetupReq = VOS_NULL_PTR;
    NAS_ESM_SDF_PARA_STRU           *pstSdfPara = VOS_NULL_PTR;

    pstAppPdpSetupReq   = (APP_ESM_PDP_SETUP_REQ_STRU *)pRcvMsg;
    pstSdfPara  = NAS_ESM_GetSdfParaAddr(pstAppPdpSetupReq->ulCid);

    /* 正常PDP激活不做检查 */
    if (APP_ESM_PDP_SETUP_TYPE_PPP != pstAppPdpSetupReq->enSetupType)
    {
        return APP_SUCCESS;
    }

    /* 去注册状态下不允许PPP拨号 */
    if (NAS_ESM_PS_REGISTER_STATUS_ATTACHED != NAS_ESM_GetEmmStatus())
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_VerifyAppPppDialSceneAndParam:ERR: PPP dial up is not allowed when ESM is detached!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_VerifyAppPppDialSceneAndParam_ENUM, 1);
        return APP_ERR_SM_DETACHED;
    }

    /* PPP拨号必须是缺省承载类型 */
    if(pstSdfPara->enBearerCntxtType != APP_ESM_BEARER_TYPE_DEFAULT)
    {
        NAS_ESM_ERR_LOG("NAS_ESM_VerifyAppPppDialSceneAndParam:ERR: Bearer type is not default!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_VerifyAppPppDialSceneAndParam_ENUM, 2);
        return APP_ERR_SM_BEARER_TYPE_NOT_DEFAULT;

    }
    return APP_SUCCESS;

}

/*****************************************************************************
 Function Name  : NAS_ESM_EncodeEpsAmbr
 Description    : SM模块组装AMBR消息函数
 Input          : VOS_UINT8 *pSendMsg,
                  VOS_UINT32 ulLength
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2013-06-28      Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_EncodeEpsUlAmbr
(
    const NAS_ESM_CONTEXT_APN_AMBR_STRU         *pstEpsAmbr,
    VOS_UINT32                            *pSendUlAmbr
)
{
    VOS_UINT32                          ulULApnAmbrExt;
    VOS_UINT32                          ulULApnAmbrExt2;

    VOS_UINT32                          ulULApnAmbr;

    VOS_UINT32                          *pTmpSendAmbr         = pSendUlAmbr;

    NAS_ESM_INFO_LOG("NAS_ESM_EncodeEpsAmbr:INFO:NAS_ESM_EncodeEpsAmbr been entered!");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_EncodeEpsUlAmbr_ENUM, LNAS_ENTRY);

    if((VOS_NULL_PTR == pTmpSendAmbr) || (VOS_NULL_PTR == pstEpsAmbr))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_EncodeEpsAmbr:ERROR: No SmMsg or No Qos Info!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_EncodeEpsUlAmbr_ENUM, LNAS_NULL_PTR);
        return ;
    }

    *pTmpSendAmbr = (VOS_UINT32)pstEpsAmbr->ucULApnAmbr;

    ulULApnAmbr = (VOS_UINT32)pstEpsAmbr->ucULApnAmbr;


    if (NAS_ESM_OP_TRUE == pstEpsAmbr->bitOpULApnAmbrExt)
    {
        ulULApnAmbrExt = (((VOS_UINT32)pstEpsAmbr->ucDLApnAmbrExt)<< NAS_ESM_MOVEMENT_8_BITS);

        *pTmpSendAmbr = (*pTmpSendAmbr) | ulULApnAmbrExt ;

        *pTmpSendAmbr = (ulULApnAmbr | ulULApnAmbrExt) ;

        *pSendUlAmbr = (ulULApnAmbr | ulULApnAmbrExt);

    }

    if (NAS_ESM_OP_TRUE == pstEpsAmbr->bitOpULApnAmbrExt2)
    {
        ulULApnAmbrExt2 = (((VOS_UINT32)pstEpsAmbr->ucDLApnAmbrExt2)<< NAS_ESM_MOVEMENT_16_BITS);

        *pTmpSendAmbr = (*pTmpSendAmbr )| ulULApnAmbrExt2 ;
    }

    return ;
}
/*****************************************************************************
 Function Name  : NAS_ESM_EncodeEpsAmbr
 Description    : SM模块组装AMBR消息函数
 Input          : VOS_UINT8 *pSendMsg,
                  VOS_UINT32 ulLength
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2013-06-28      Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_EncodeEpsDlAmbr
(
    const NAS_ESM_CONTEXT_APN_AMBR_STRU         *pstEpsAmbr,
    VOS_UINT32                          *pSendDlAmbr
)
{
    VOS_UINT32                          ulDLApnAmbrExt;
    VOS_UINT32                          ulDLApnAmbrExt2;

    VOS_UINT32                          *pTmpSendAmbr         = pSendDlAmbr;

    NAS_ESM_INFO_LOG("NAS_ESM_EncodeEpsDlAmbr:INFO:NAS_ESM_EncodeEpsAmbr been entered!");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_EncodeEpsDlAmbr_ENUM, LNAS_ENTRY);

    if((VOS_NULL_PTR == pTmpSendAmbr) || (VOS_NULL_PTR == pstEpsAmbr))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_EncodeEpsAmbr:ERROR: No SmMsg or No Qos Info!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_EncodeEpsDlAmbr_ENUM, LNAS_NULL_PTR);
        return ;
    }

    *pTmpSendAmbr = (VOS_UINT32)pstEpsAmbr->ucDLApnAmbr;


    if (NAS_ESM_OP_TRUE == pstEpsAmbr->bitOpDLApnAmbrExt)
    {
        ulDLApnAmbrExt = ((VOS_UINT32)pstEpsAmbr->ucDLApnAmbrExt)<< NAS_ESM_MOVEMENT_8_BITS;

        *pTmpSendAmbr = (*pTmpSendAmbr) | ulDLApnAmbrExt ;

    }

    if (NAS_ESM_OP_TRUE == pstEpsAmbr->bitOpDLApnAmbrExt2)
    {
        ulDLApnAmbrExt2 = ((VOS_UINT32)pstEpsAmbr->ucDLApnAmbrExt2)<< NAS_ESM_MOVEMENT_16_BITS;

        *pTmpSendAmbr = (*pTmpSendAmbr) | ulDLApnAmbrExt2 ;
    }

    return ;
}


/*****************************************************************************
 Function Name   : NAS_ESM_CompareEsmInfo
 Description     : 判断ESM模块维护且需要上报给HSO的信息是否发生变化
 Input           : None
 Output          : pulEpsbId
 Return          : VOS_UINT32

 History         :
    1.wangchen 00209181     2013-06-21    Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_ESM_CompareEsmInfo( VOS_VOID )
{
    VOS_UINT32                          ulRst = NAS_ESM_SUCCESS;
    VOS_UINT32                          ulEpsbId;
    VOS_UINT32                          ulCnt = NAS_ESM_NULL;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo = VOS_NULL_PTR;

    VOS_UINT32                          ulDLApnAmbr = NAS_ESM_NULL;
    VOS_UINT32                          ulULApnAmbr = NAS_ESM_NULL;

    NAS_ESM_INFO_LOG("NAS_ESM_CompareEsmInfo:entered!");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_CompareEsmInfo_ENUM, LNAS_ENTRY);

    for( ulEpsbId = NAS_ESM_MIN_EPSB_ID; ulEpsbId <= NAS_ESM_MAX_EPSB_ID; ulEpsbId++ )
    {
        pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);

        NAS_ESM_EncodeEpsUlAmbr(&(pstEpsbCntxtInfo->stApnAmbrInfo),&ulULApnAmbr);
        NAS_ESM_EncodeEpsDlAmbr(&(pstEpsbCntxtInfo->stApnAmbrInfo),&ulDLApnAmbr);

        ulCnt = ulEpsbId - NAS_ESM_MIN_EPSB_ID;

        NAS_ESM_INFO_LOG1("NAS_ESM_CompareEsmInfo:entered,ulCnt = !",ulCnt);
        TLPS_PRINT2LAYER_INFO1(NAS_ESM_CompareEsmInfo_ENUM, 1, ulCnt);

        g_stEsmOmInfo[ulCnt].ulEpsbId = ulEpsbId;

        NAS_ESM_INFO_LOG1("NAS_ESM_CompareEsmInfo:entered,g_stEsmOmInfo[ulCnt].ulEpsbId = !",g_stEsmOmInfo[ulCnt].ulEpsbId);
        TLPS_PRINT2LAYER_INFO1(NAS_ESM_CompareEsmInfo_ENUM, 2, g_stEsmOmInfo[ulCnt].ulEpsbId);

        /* 比较承载状态是否相同 */
        if (g_stEsmOmInfo[ulCnt].enBearerCntxtState != pstEpsbCntxtInfo->enBearerCntxtState)
        {
            g_stEsmOmInfo[ulCnt].enBearerCntxtState = pstEpsbCntxtInfo->enBearerCntxtState;
            ulRst = NAS_ESM_FAILURE;
        }

        /* 比较承载类型是否相同 */
        if (g_stEsmOmInfo[ulCnt].enBearerCntxtType != pstEpsbCntxtInfo->enBearerCntxtType)
        {
            g_stEsmOmInfo[ulCnt].enBearerCntxtType = pstEpsbCntxtInfo->enBearerCntxtType;
            ulRst = NAS_ESM_FAILURE;
        }

        /* 比较LINKCID是否相同 */
        if (g_stEsmOmInfo[ulCnt].ulLinkBearId != pstEpsbCntxtInfo->ulLinkedEpsbId)
        {
            g_stEsmOmInfo[ulCnt].ulLinkBearId = pstEpsbCntxtInfo->ulLinkedEpsbId;
            ulRst = NAS_ESM_FAILURE;
        }

        /* 比较CID是否相同 */
        if (g_stEsmOmInfo[ulCnt].ulCid != pstEpsbCntxtInfo->ulBitCId)
        {
            g_stEsmOmInfo[ulCnt].ulCid = pstEpsbCntxtInfo->ulBitCId;
            ulRst = NAS_ESM_FAILURE;
        }

        /* 比较QOS参数是否相同 */
        if (NAS_ESM_SUCCESS != NAS_ESM_MEM_CMP(&(g_stEsmOmInfo[ulCnt].stSdfQosInfo),
                                                &(pstEpsbCntxtInfo->stEpsQoSInfo.stQosInfo),
                                                sizeof(APP_ESM_EPS_QOS_INFO_STRU)))
        {
            NAS_ESM_MEM_CPY_S(  &(g_stEsmOmInfo[ulCnt].stSdfQosInfo),
                                sizeof(APP_ESM_EPS_QOS_INFO_STRU),
                                &(pstEpsbCntxtInfo->stEpsQoSInfo.stQosInfo),
                                sizeof(APP_ESM_EPS_QOS_INFO_STRU));

            NAS_ESM_INFO_LOG1("NAS_ESM_CompareEsmInfo:entered!,g_stEsmOmInfo[ulCnt].stSdfQosInfo.ucQCI = ",g_stEsmOmInfo[ulCnt].stSdfQosInfo.ucQCI);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_CompareEsmInfo_ENUM, 3, g_stEsmOmInfo[ulCnt].stSdfQosInfo.ucQCI);

            ulRst = NAS_ESM_FAILURE;
        }

        /* 比较APN是否相同 */
        if (NAS_ESM_SUCCESS != NAS_ESM_MEM_CMP(&(g_stEsmOmInfo[ulCnt].stApn),
                                                &(pstEpsbCntxtInfo->stApnInfo),
                                                sizeof(APP_ESM_APN_INFO_STRU)))
        {
            NAS_ESM_MEM_CPY_S(  &(g_stEsmOmInfo[ulCnt].stApn),
                                sizeof(OM_ESM_APN_INFO_STRU),
                                &(pstEpsbCntxtInfo->stApnInfo),
                                sizeof(APP_ESM_APN_INFO_STRU));

            ulRst = NAS_ESM_FAILURE;
        }

        /* 比较IP ADDR是否相同 */
        if (NAS_ESM_SUCCESS != NAS_ESM_MEM_CMP(&(g_stEsmOmInfo[ulCnt].stIpAddr),
                                                 &(pstEpsbCntxtInfo->stPdnAddrInfo),
                                                 sizeof(APP_ESM_IP_ADDR_STRU)))
        {
            NAS_ESM_MEM_CPY_S(  &(g_stEsmOmInfo[ulCnt].stIpAddr),
                                sizeof(APP_ESM_IP_ADDR_STRU),
                                &(pstEpsbCntxtInfo->stPdnAddrInfo),
                                sizeof(APP_ESM_IP_ADDR_STRU));

            ulRst = NAS_ESM_FAILURE;
        }

        /* 比较AMBR */
        if ((ulULApnAmbr!= g_stEsmOmInfo[ulCnt].stApnAmbrInfo.ulULApnAmbr)
            ||(ulDLApnAmbr!= g_stEsmOmInfo[ulCnt].stApnAmbrInfo.ulDLApnAmbr))
        {


            g_stEsmOmInfo[ulCnt].stApnAmbrInfo.ulULApnAmbr = ulULApnAmbr;
            g_stEsmOmInfo[ulCnt].stApnAmbrInfo.ulDLApnAmbr = ulDLApnAmbr;

            ulRst = NAS_ESM_FAILURE;
        }

    }

    return ulRst;
}
/*lint +e961*/
/*lint +e960*/


/*****************************************************************************
 Function Name   : NAS_ESM_CompareEsmDtPDPInfo
 Description     : 判断ESM模块维护且需要上报给路测的信息是否发生变化
 Input           : None
 Output          : pulEpsbId
 Return          : VOS_UINT32

 History         :
    1.l00195322     2014-05-07   Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_ESM_DtComparePdpInfo( VOS_VOID )
{
    VOS_UINT32                          ulRst = NAS_ESM_SUCCESS;

    NAS_OM_ACT_PDP_INFO_STRU   *pstActPdpInfo = (VOS_VOID *) NAS_ESM_MEM_ALLOC(sizeof(NAS_OM_ACT_PDP_INFO_STRU));

    if (VOS_NULL_PTR == pstActPdpInfo)
    {
        NAS_ESM_ERR_LOG("NAS_ESM_DtComparePdpInfo: mem alloc fail!.");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_DtComparePdpInfo_ENUM, LNAS_NULL_PTR);
        return NAS_ESM_FAILURE;
    }

    NAS_ESM_MEM_SET_S(  pstActPdpInfo,
                        sizeof(NAS_OM_ACT_PDP_INFO_STRU),
                        0,
                        sizeof(NAS_OM_ACT_PDP_INFO_STRU));

    /*获取激活承载的信息*/
    NAS_ESM_GetActPdpInfo(pstActPdpInfo);

    /*比较激活承载信息是否变化*/
    if( 0 != NAS_ESM_MEM_CMP(&g_stEsmDtInfo.stActPdpInfo,pstActPdpInfo,sizeof(NAS_OM_ACT_PDP_INFO_STRU)))
    {
        ulRst = NAS_ESM_FAILURE;
    }

    NAS_ESM_MEM_FREE(pstActPdpInfo);

    return ulRst;

}

/*****************************************************************************
 Function Name   : NAS_ESM_CompareEsmDtPDPInfo
 Description     : 判断ESM模块维护且需要上报给路测的信息是否有变化，有变化则上报
 Input           : None
 Output          : pulEpsbId
 Return          : VOS_UINT32

 History         :
    1.l00195322     2014-05-07   Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_DtJudgeifNeedRpt(VOS_VOID)
{

    /*判断是否需要上报pdp*/
    if(APP_ESM_DT_REPORT_STATUS_OPEN== g_ulRptPdpStatus)
    {
        if(NAS_ESM_FAILURE == NAS_ESM_DtComparePdpInfo())
        {
            /* chengmin 00285307  缩进 begin*/
            #if (VOS_WIN32 != VOS_OS_VER)
            NAS_ESM_ReportActPdpInfo();
            #endif
            /* chengmin 00285307  缩进 end*/
        }
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_ESM_CheckSdfHaveUplinkPacketFilter
 Description     : 检查SDF中是否存在上行PF
 Input           : NAS_ESM_SDF_PARA_STRU     *pstSdfPara
 Output          : VOS_VOID
 Return          : VOS_UINT32

 History         :
    1.sunjitan 00193151     2015-04-25   Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_ESM_CheckSdfHaveUplinkPacketFilter
(
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara
)
{
    VOS_UINT32                             ulIndex     = 0;
    APP_ESM_TRANSFER_DIRECTION_ENUM_UINT8  enDirection = APP_ESM_TRANSFER_DIRECTION_BUTT;

    for(ulIndex = 0; ulIndex < pstSdfPara->ulPfNum; ulIndex++)
    {
        enDirection = pstSdfPara->astCntxtTftInfo[ulIndex].enDirection;
        if((APP_ESM_TRANSFER_DIRECTION_UPLINK == enDirection)
            ||(APP_ESM_TRANSFER_DIRECTION_UPLINK_DOWNLINK == enDirection))
        {
            NAS_ESM_INFO_LOG("NAS_ESM_CheckSdfHaveUplinkPacketFilter: Info, there is uplink PF.");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_CheckSdfHaveUplinkPacketFilter_ENUM, LNAS_SUCC);
            return NAS_ESM_SUCCESS;
        }
    }

    NAS_ESM_WARN_LOG("NAS_ESM_CheckSdfHaveUplinkPacketFilter: WARN, no uplink PF.");
    TLPS_PRINT2LAYER_WARNING(NAS_ESM_CheckSdfHaveUplinkPacketFilter_ENUM, LNAS_FAIL);
    return NAS_ESM_FAILURE;
}




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

