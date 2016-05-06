/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasEsmEmmMsgProc.c
    Description : 处理EMM发给SM的消息
    History     :
     1.丁丽 00128736        2008-09-01  Draft Enact
     2.祝义强 00138739      2008-12-03  Modify BA8D00656
     3.杨茜惠 00135146      2008-12-18  Modify BA8D00753
     4.孙兵 49683           2009-01-06  Modify BA8D00870
     5.杨茜惠 00135146      2009-03-06  Modify BA8D01127
     6.李洪00150010         2009-08-05  Modify  BJ9D01627
******************************************************************************/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasEsmEmmMsgProc.h"
#include    "NasEsmNwMsgProc.h"
#include    "NasEsmInclude.h"
/*#include  "IpDhcpv4Server.h"*/
#include "NasEsmAppMsgParaProc.h"


/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASESMEMMMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASESMEMMMSGPROC_C
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
#if (FEATURE_ON == FEATURE_PTM)
NAS_ESM_CN_CAUSE_TRANS_STRU          g_astEsmErrlogErrNoMap[] =
{
    /*------------casue-----------------------------------error id---------------------------*/
    {NAS_ESM_CAUSE_OPERATOR_DETERMINE_BARRING,      ESM_OM_ERRLOG_CAUSE_OPERATOR_DETERMINE_BARRING},
    {NAS_ESM_CAUSE_INSUFFICIENT_RESOURCES,          ESM_OM_ERRLOG_CAUSE_INSUFFICIENT_RESOURCES},
    {NAS_ESM_CAUSE_UNKNOWN_OR_MISSING_APN,          ESM_OM_ERRLOG_CAUSE_UNKNOWN_OR_MISSING_APN},
    {NAS_ESM_CAUSE_UNKNOWN_PDN_TYPE,                ESM_OM_ERRLOG_CAUSE_UNKNOWN_PDN_TYPE},
    {NAS_ESM_CAUSE_USER_AUTH_FAIL,                  ESM_OM_ERRLOG_CAUSE_USER_AUTH_FAIL},
    {NAS_ESM_CAUSE_REQ_REJ_BY_SGW_OR_PGW,           ESM_OM_ERRLOG_CAUSE_REQ_REJ_BY_SGW_OR_PGW},
    {NAS_ESM_CAUSE_REQ_REJ_UNSPECITY,               ESM_OM_ERRLOG_CAUSE_REQ_REJ_UNSPECITY},
    {NAS_ESM_CAUSE_SERVICE_OPTION_NOT_SUPPORT,      ESM_OM_ERRLOG_CAUSE_SERVICE_OPTION_NOT_SUPPORT},
    {NAS_ESM_CAUSE_REQ_SERVICE_NOT_SUBSCRIBED,      ESM_OM_ERRLOG_CAUSE_REQ_SERVICE_NOT_SUBSCRIBED},
    {NAS_ESM_CAUSE_SERVICE_OPTION_TEMP_OUT_ORDER,   ESM_OM_ERRLOG_CAUSE_SERVICE_OPTION_TEMP_OUT_ORDER},
    {NAS_ESM_CAUSE_PTI_ALREADY_IN_USED,             ESM_OM_ERRLOG_CAUSE_PTI_ALREADY_IN_USED},
    {NAS_ESM_CAUSE_REGULAR_DEACTIVATION,            ESM_OM_ERRLOG_CAUSE_REGULAR_DEACTIVATION},
    {NAS_ESM_CAUSE_EPS_QOS_NOT_ACCEPT,              ESM_OM_ERRLOG_CAUSE_EPS_QOS_NOT_ACCEPT},
    {NAS_ESM_CAUSE_NETWORK_FAILURE,                 ESM_OM_ERRLOG_CAUSE_NETWORK_FAILURE},
    {NAS_ESM_CAUSE_SYNTACTIC_ERR_IN_TFT,            ESM_OM_ERRLOG_CAUSE_SYNTACTIC_ERR_IN_TFT},
    {NAS_ESM_CAUSE_SEMANTIC_ERR_IN_PACKET_FILTER,   ESM_OM_ERRLOG_CAUSE_SEMANTIC_ERR_IN_PACKET_FILTER},
    {NAS_ESM_CAUSE_SYNCTACTIC_ERR_IN_PACKET_FILTER, ESM_OM_ERRLOG_CAUSE_SYNCTACTIC_ERR_IN_PACKET_FILTER},
    {NAS_ESM_CAUSE_BEARER_WITHOUT_TFT_ACT,          ESM_OM_ERRLOG_CAUSE_BEARER_WITHOUT_TFT_ACT},
    {NAS_ESM_CAUSE_PTI_MISMATCH,                    ESM_OM_ERRLOG_CAUSE_PTI_MISMATCH},
    {NAS_ESM_CAUSE_LAST_PDN_DISCONN_NOT_ALLOWED,    ESM_OM_ERRLOG_CAUSE_LAST_PDN_DISCONN_NOT_ALLOWED},
    {NAS_ESM_CAUSE_PDNTYPE_IPV4_ONLY_ALLOWED,       ESM_OM_ERRLOG_CAUSE_PDNTYPE_IPV4_ONLY_ALLOWED},
    {NAS_ESM_CAUSE_PDNTYPE_IPV6_ONLY_ALLOWED,       ESM_OM_ERRLOG_CAUSE_PDNTYPE_IPV6_ONLY_ALLOWED},
    {NAS_ESM_CAUSE_SINGLE_ADDR_BEARER_ONLY_ALLOWED, ESM_OM_ERRLOG_CAUSE_SINGLE_ADDR_BEARER_ONLY_ALLOWED},
    {NAS_ESM_CAUSE_ESM_INFORMATION_NOT_RECEIVED,    ESM_OM_ERRLOG_CAUSE_ESM_INFORMATION_NOT_RECEIVED},
    {NAS_ESM_CAUSE_PDN_CONNECTION_DOES_NOT_EXIST,   ESM_OM_ERRLOG_CAUSE_PDN_CONNECTION_DOES_NOT_EXIST},
    {NAS_ESM_CAUSE_SAME_APN_MULTI_PDN_CONNECTION_NOT_ALLOWED, ESM_OM_ERRLOG_CAUSE_SAME_APN_MULTI_PDN_CONNECTION_NOT_ALLOWED},
    {NAS_ESM_CAUSE_COLLISION_WITH_NETWORK_INITIATED_REQUEST,  ESM_OM_ERRLOG_CAUSE_COLLISION_WITH_NETWORK_INITIATED_REQUEST},
    {NAS_ESM_CAUSE_UNSUPPORTED_QCI_VALUE,           ESM_OM_ERRLOG_CAUSE_UNSUPPORTED_QCI_VALUE},
    {NAS_ESM_CAUSE_INVALID_PTI_VALUE,               ESM_OM_ERRLOG_CAUSE_INVALID_PTI_VALUE},
    {NAS_ESM_CAUSE_SEMANTICALLY_INCORRECT_MESSAGE,  ESM_OM_ERRLOG_CAUSE_SEMANTICALLY_INCORRECT_MESSAGE},
    {NAS_ESM_CAUSE_INVALID_MANDATORY_INFORMATION,   ESM_OM_ERRLOG_CAUSE_INVALID_MANDATORY_INFORMATION},
    {NAS_ESM_CAUSE_MESSAGE_TYPE_NON_EXIST_OR_NOT_IMPLEMENTED, ESM_OM_ERRLOG_CAUSE_MESSAGE_TYPE_NON_EXIST_OR_NOT_IMPLEMENTED},
    {NAS_ESM_CAUSE_MESSAGE_TYPE_NOT_COMPATIBLE_WITH_PROT_STA, ESM_OM_ERRLOG_CAUSE_MESSAGE_TYPE_NOT_COMPATIBLE_WITH_PROT_STA},
    {NAS_ESM_CAUSE_INFO_ELEMENT_NON_EXIST_OR_NOT_IMPLEMENTED, ESM_OM_ERRLOG_CAUSE_INFO_ELEMENT_NON_EXIST_OR_NOT_IMPLEMENTED},
    {NAS_ESM_CAUSE_CONDITIONAL_IE_ERROR,            ESM_OM_ERRLOG_CAUSE_CONDITIONAL_IE_ERROR},
    {NAS_ESM_CAUSE_MESSAGE_NOT_COMPATIBLE_WITH_PROT_STA,     ESM_OM_ERRLOG_CAUSE_MESSAGE_NOT_COMPATIBLE_WITH_PROT_STA},
    {NAS_ESM_CAUSE_PROTOCOL_ERROR,                  ESM_OM_ERRLOG_CAUSE_PROTOCOL_ERROR},
    {NAS_ESM_CAUSE_APN_RESTRICTION_VAL_INCOMPATIBLE_WITH_ACT_BEARER, ESM_OM_ERRLOG_CAUSE_APN_RESTRICTION_VAL_INCOMPATIBLE_WITH_ACT_BEARER},
};

static VOS_UINT32   g_astEsmErrlogErrNum
        = sizeof(g_astEsmErrlogErrNoMap)/sizeof(NAS_ESM_CN_CAUSE_TRANS_STRU);
#endif



/*****************************************************************************
  3 Function
*****************************************************************************/
/*****************************************************************************
 Function Name  : NAS_ESM_EmmMsgDistr()
 Description    : SM模块EMM消息处理函数
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.丁丽 00128736      2008-09-01  Draft Enact
      2.lihong00150010     2009-10-30  Modify

*****************************************************************************/
VOS_VOID NAS_ESM_EmmMsgDistr( VOS_VOID *pRcvMsg )
{
    PS_MSG_HEADER_STRU         *pEmmMsg  = VOS_NULL_PTR;

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_EmmMsgDistr is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_EmmMsgDistr_ENUM, LNAS_ENTRY);

    pEmmMsg = (PS_MSG_HEADER_STRU*)pRcvMsg;

    /*根据消息名，调用相应的消息处理函数*/
    switch(pEmmMsg->ulMsgName)
    {
        case ID_EMM_ESM_SUSPEND_IND:
            NAS_ESM_RcvEsmEmmSuspendInd( (EMM_ESM_SUSPEND_IND_STRU *) pRcvMsg );
            break;

        case ID_EMM_ESM_RESUME_IND:
            NAS_ESM_RcvEsmEmmResumeInd( (EMM_ESM_RESUME_IND_STRU *) pRcvMsg );
            break;
        /*如果收到的是ID_EMM_ESM_PDN_CON_IND消息*/
        case ID_EMM_ESM_PDN_CON_IND:

            /*调用Sm_RcvEsmEmmDataInd函数*/
            NAS_ESM_RcvEsmEmmPdnConInd( (EMM_ESM_PDN_CON_IND_STRU *) pRcvMsg );
            break;

        /*如果收到的是ID_EMM_ESM_DATA_IND消息*/
        case ID_EMM_ESM_DATA_IND:

            /*调用Sm_RcvEsmEmmDataInd函数*/
            NAS_ESM_RcvEsmEmmDataInd( (EMM_ESM_DATA_IND_STRU *) pRcvMsg );
            break;

        /*如果收到的是ID_EMM_ESM_EST_CNF消息*/
        case ID_EMM_ESM_EST_CNF:

            /*调用Sm_RcvEsmEmmDataInd函数*/
            NAS_ESM_RcvEsmEmmEstCnf( (EMM_ESM_EST_CNF_STRU *) pRcvMsg );
            break;

        /*如果收到的是ID_EMM_ESM_STATUS_IND消息*/
        case ID_EMM_ESM_STATUS_IND:

            /*调用Sm_RcvEsmEmmStatusInd函数*/
            NAS_ESM_RcvEsmEmmStatusInd( (EMM_ESM_STATUS_IND_STRU *) pRcvMsg );
            break;

        /*如果收到的是ID_EMM_ESM_BEARER_STATUS_IND消息*/
        case ID_EMM_ESM_BEARER_STATUS_IND:

            /*调用Sm_RcvEsmEmmBearerStatusInd函数*/
            NAS_ESM_RcvEsmEmmBearerStatusInd( (EMM_ESM_BEARER_STATUS_IND_STRU *) pRcvMsg );
            break;

        /*如果收到的是ID_EMM_ESM_REL_IND消息*/
        case ID_EMM_ESM_REL_IND:
            NAS_ESM_RcvEsmEmmRelInd();
            break;
        case ID_EMM_ESM_DEACT_NON_EMC_BEARER_IND:
            NAS_ESM_RcvEsmEmmDeactAllNonEmcBearerInd();
            break;
        case ID_EMM_ESM_START_NOTIFY_IND:
            NAS_ESM_RcvEsmEmmStartNotifyInd();
            break;

        case ID_EMM_ESM_PLMN_CHANGE_IND:
            NAS_ESM_RcvEsmEmmPlmnChangeInd();
            break;

        case ID_EMM_ESM_STOP_NOTIFY_IND:
            NAS_ESM_RcvEsmEmmStopNotifyInd();
            break;
        #if(VOS_WIN32 == VOS_OS_VER)
        case ID_EMM_ESM_REPLAY_EXPORT_CTX_IND:
            NAS_ESM_WARN_LOG("NAS_ESM_EmmMsgDistr:WARNING:EMM->SM Message ID_EMM_ESM_REPLAY_EXPORT_CTX_IND!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_EmmMsgDistr_ENUM, 1);
            (void)NAS_ESM_ExportContextData();
            (void)NAS_ERABM_ExportContextData();

            break;
        #endif

        /*收到ID_ESM_EMM_DATA_CNF的处理*/
        case ID_EMM_ESM_DATA_CNF:
             NAS_ESM_RcvEsmEmmDataCnf((EMM_ESM_DATA_CNF_STRU *)pRcvMsg);
             break;

        #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        case ID_EMM_ESM_CLEAR_CL_BEARER_NOTIFY:
             NAS_ESM_RcvEsmEmmClearClBearerNotify();
             break;
        #endif

        default:
            NAS_ESM_WARN_LOG("NAS_ESM_EmmMsgDistr:WARNING:EMM->SM Message name non-existent!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_EmmMsgDistr_ENUM, LNAS_MSG_INVALID);
            break;
    }
}
/*****************************************************************************
 Function Name   : NAS_ESM_RcvEsmEmmRelInd
 Description     : SM模块收到ID_EMM_ESM_REL_IND处理函数
 Input           : NONE
 Output          : None
 Return          : NONE

 History         :
    1.leixiantiao  00258641        2015-03-03      Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_RcvEsmEmmRelInd(VOS_VOID)
{
    /* 如果ESM处于非注册态，则直接返回 */
    if (NAS_ESM_PS_REGISTER_STATUS_DETACHED == NAS_ESM_GetEmmStatus())
    {
        NAS_ESM_WARN_LOG("NAS_ESM_EmmMsgDistr:WARNING:Msg is discard cause ESM state is detached!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_EmmMsgDistr_ENUM, ESM_STATUS_ERROR);
        return ;
    }

    NAS_ESM_RcvEmmDetachMsg();
}
/*****************************************************************************
 Function Name   : NAS_ESM_RcvEsmEmmSuspendInd
 Description     : SM模块收到ID_EMM_ESM_SUSPEND_IND处理函数
 Input           : EMM_ESM_SUSPEND_IND_STRU *pRcvMsg
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong    00150010        2011-05-02      Draft Enact
    2.liuhua    00212067        2012-09-06      Add support for double APN
*****************************************************************************/
/*lint -e960*/
/*lint -e961*/
VOS_VOID  NAS_ESM_RcvEsmEmmSuspendInd(const EMM_ESM_SUSPEND_IND_STRU *pRcvMsg )
{
    VOS_UINT32                          ulCnt               = NAS_ESM_NULL;
    NAS_ESM_BUFF_MANAGE_INFO_STRU      *pstEsmBuffManInfo   = NAS_ESM_GetEsmBufferManageInfoAddr();

    (VOS_VOID)pRcvMsg;

    /* 设置状态为挂起态 */
    NAS_ESM_SetLModeStatus(NAS_ESM_L_MODE_STATUS_SUSPENDED);

    /*如果延迟释放非紧急承载定时器存在，则停止*/
    NAS_ESM_TimerStop(0, TI_NAS_ESM_REL_NON_EMC_BEARER);

    /* 清空动态表，如果有APP消息，则回复APP相应操作失败，原因值为挂起 */
    NAS_ESM_ClearStateTable(APP_ERR_SM_SUSPENDED, PS_FALSE);

    /* 释放ATTACHING类型缓存记录 */
    for (ulCnt = NAS_ESM_NULL; ulCnt < NAS_ESM_MAX_ATTACHING_BUFF_ITEM_NUM; ulCnt++)
    {
        if (pstEsmBuffManInfo->paAttBuffer[ulCnt] != VOS_NULL_PTR)
        {
            NAS_ESM_ClearEsmBuffItem(NAS_ESM_BUFF_ITEM_TYPE_ATTACHING, ulCnt);
        }
    }

    /* 若ESM当前状态为注册中，则将状态转为去注册态，待GU模注册成功后通知LMM，
       再由LMM通知ESM进入注册态； */
    if (NAS_ESM_PS_REGISTER_STATUS_ATTACHING == NAS_ESM_GetEmmStatus())
    {
        NAS_ESM_SetEmmStatus(NAS_ESM_PS_REGISTER_STATUS_DETACHED);
    }

    /* 如果支持双APN，则停止注册承载重建定时器 */
    if (NAS_ESM_OP_TRUE == NAS_ESM_AttachBearerReestEnable())
    {
        NAS_ESM_TimerStop(0, TI_NAS_ESM_ATTACH_BEARER_REEST);
    }

    /* 回复EMM挂起成功 */
    NAS_ESM_SndEsmEmmSuspendRsp(EMM_ESM_RSLT_TYPE_SUCC);
}

/*****************************************************************************
 Function Name   : NAS_ESM_RcvEsmEmmResumeInd
 Description     : SM模块收到ID_EMM_ESM_RESUME_IND处理函数
 Input           : EMM_ESM_RESUME_IND_STRU *pRcvMsg
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong    00150010        2011-05-02      Draft Enact
    2.liuhua    00212067        2012-09-06      Add support for double APN
*****************************************************************************/
VOS_VOID  NAS_ESM_RcvEsmEmmResumeInd(const EMM_ESM_RESUME_IND_STRU *pRcvMsg )
{
    (VOS_VOID)pRcvMsg;

    /* 设置状态为正常态 */
    NAS_ESM_SetLModeStatus(NAS_ESM_L_MODE_STATUS_NORMAL);

    /* 回复EMM解挂成功 */
    NAS_ESM_SndEsmEmmResumeRsp(EMM_ESM_RSLT_TYPE_SUCC);

    /* 如果支持双APN，则判断是否需要启动注册承载重建定时器 */
    if (NAS_ESM_OP_TRUE == NAS_ESM_AttachBearerReestEnable())
    {
        if ((NAS_ESM_GetCurPdnNum() > 0) &&
            (NAS_ESM_UNASSIGNED_EPSB_ID == NAS_ESM_GetAttachBearerId()))
        {
            /* 如果注册承载重建定时器时长不为0，则启动起重建过程 */
            if (0 != NAS_ESM_GetAttachBearerReestTimerLen())
            {
                NAS_ESM_TimerStart(0, TI_NAS_ESM_ATTACH_BEARER_REEST);
            }
        }
    }
}
/*****************************************************************************
 Function Name   : NAS_ESM_RcvEsmEmmPdnConIndFindSdfPara
 Description     : SM模块收到ID_EMM_ESM_PDN_CONN_IND消息后查找SDF参数
 Input           : NAS_ESM_SDF_PARA_STRU              *pstSdfPara,
                    APP_ESM_SDF_PARA_STRU              *pstAppSdfPara
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.wangchen 00209181         2014-09-28      Draft Enact
*****************************************************************************/
VOS_VOID  NAS_ESM_RcvEsmEmmPdnConIndFindSdfPara
(
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara,
    APP_ESM_SDF_PARA_STRU              *pstAppSdfPara
)
{
    VOS_UINT32                          ulCur               = NAS_ESM_NULL;
    VOS_UINT32                          ulSdfNum            = NAS_ESM_NULL;

    /* 逐一获取12套NV参数 */
    for (ulCur = NAS_ESM_MIN_CID; ulCur < NAS_ESM_CID_NV_NUM; ulCur++)
    {
        pstAppSdfPara->ulCId = ulCur;
        if (APP_FAILURE == NAS_ESM_GetSdfPara(&ulSdfNum, pstAppSdfPara))
        {
            continue;
        }

        if (ESM_EMM_RELEASE_R11 <= NAS_EMM_GetNasRelease())
        {
            /* 如果选取的NV参数，APN被#50拒绝，则选取下一套 */
            if (NAS_ESM_FAILURE == NAS_ESM_IsCurrentApnAvailable(pstAppSdfPara->enPdnType,
                                                                pstAppSdfPara->bitOpApn,
                                                                &(pstAppSdfPara->stApnInfo)))
            {
                continue;
            }
        }

        pstSdfPara = NAS_ESM_GetSdfParaAddr(ulCur);

        NAS_ESM_MEM_CPY_S(  pstSdfPara,
                            sizeof(NAS_ESM_SDF_PARA_STRU),
                            pstAppSdfPara,
                            sizeof(APP_ESM_SDF_PARA_STRU));

    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_RcvEsmEmmPdnConInd
 Description     : SM模块收到ID_EMM_ESM_PDN_CON_IND处理函数
 Input           : EMM_ESM_PDN_CON_IND_STRU *pRcvMsg
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.丁丽      00128736    2008-09-10      Draft Enact
    2.sunbing   49683       2009-02-05      Modify
    3.liuwenyu  00143951    2009-09-08      Modify
    4.lihong    00150010    2010-08-12      Modify
    5.niuxiufan 00181501    2011-12-08      Modify
    6.sunjitan  00193151    2015-06-16      Modify for 1XCL_MULTI_MODE_PHASEI
*****************************************************************************/
VOS_VOID  NAS_ESM_RcvEsmEmmPdnConInd(const EMM_ESM_PDN_CON_IND_STRU *pRcvMsg )
{
    VOS_UINT32                          ulPti               = NAS_ESM_NULL;
    VOS_UINT32                          ulRegCId            = NAS_ESM_NULL;
    VOS_UINT32                          ulStateTblId        = NAS_ESM_NULL;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara          = VOS_NULL_PTR;
    APP_ESM_SDF_PARA_STRU              *pstAppSdfPara       = VOS_NULL_PTR;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;
    NAS_ESM_ENCODE_INFO_STRU            stEncodeInfo;
    NAS_ESM_PDP_MANAGE_INFO_STRU       *pEpsbManageInfo     = VOS_NULL_PTR;


    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_RcvEsmEmmPdnConInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_RcvEsmEmmPdnConInd_ENUM, LNAS_ENTRY);

    (VOS_VOID)pRcvMsg;

    if (NAS_ESM_L_MODE_STATUS_NORMAL != NAS_ESM_GetLModeStatus())
    {
        NAS_ESM_WARN_LOG("NAS_ESM_RcvEsmEmmPdnConInd: L mode is already suspended!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_RcvEsmEmmPdnConInd_ENUM, LNAS_EMM_LTE_SUSPEND);

        NAS_ESM_SetLModeStatus(NAS_ESM_L_MODE_STATUS_NORMAL);
    }

    if (NAS_ESM_PS_REGISTER_STATUS_DETACHED != NAS_ESM_GetEmmStatus())
    {
        NAS_ESM_NORM_LOG("NAS_ESM_RcvEsmEmmPdnConInd:NORM: received abnormal Pdn Con Ind !");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_RcvEsmEmmPdnConInd_ENUM, ESM_STATUS_ERROR);

        if (PS_TRUE == NAS_ESM_HasEmergencyPdn())
        {
            /*如果有紧急承载，则仅本地释放所有非紧急承载*/
            NAS_ESM_ClearEsmResoureWhenEstingEmcPdn();
        }
        else
        {
            /*ESM去注册，释放资源*/
            NAS_ESM_RcvEmmDetachMsg();
        }
    }

    pstAppSdfPara = NAS_ESM_MEM_ALLOC(sizeof(APP_ESM_SDF_PARA_STRU));

    if (VOS_NULL_PTR == pstAppSdfPara)
    {
         /*打印不合法信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_RcvEsmEmmPdnConInd:ERROR: Mem alloc fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_RcvEsmEmmPdnConInd_ENUM, LNAS_NULL_PTR);

        /* 回复EMM ID_EMM_ESM_PDN_CON_RSP（FAIL） */
        NAS_ESM_SndEsmEmmPdnConRspMsg(EMM_ESM_PDN_CON_RSLT_FAIL, 0,0);

        return;
    }

    /* 逐一获取12套NV参数 */
    NAS_ESM_RcvEsmEmmPdnConIndFindSdfPara(pstSdfPara,pstAppSdfPara);

    NAS_ESM_MEM_FREE(pstAppSdfPara);

    /* 从APP获取承载管理模式参数，则采取自动接受模式 */
    pEpsbManageInfo = NAS_ESM_GetBearerManageInfoAddr();
    if (APP_FAILURE == NAS_ESM_GetPdpManageInfo(pEpsbManageInfo))
    {
        /*打印警告信息*/
        NAS_ESM_WARN_LOG("NAS_ESM_RcvEsmEmmPdnConInd:WARN: Fail to get PDP Manage Info from APP!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_RcvEsmEmmPdnConInd_ENUM, LNAS_FAIL);
        pEpsbManageInfo->enMode = APP_ESM_BEARER_MANAGE_MODE_AUTO;
        pEpsbManageInfo->enType = APP_ESM_BEARER_MANAGE_TYPE_ACCEPT;
    }
    /* 获取用于注册的CID，优先级顺序由高到低为CID0 > CID1-CID11 > CID12-CID20 */
    /* 除了个别运营商特殊需求, 需要GU NV项CID0初始化为专有类型，CID11为缺省类型*/
    ulRegCId = NAS_ESM_GetRegistCid();
    NAS_ESM_SndOmRegCidInfo(ulRegCId);
    if (NAS_ESM_ILL_CID == ulRegCId)
    {
        /*打印不合法信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_RcvEsmEmmPdnConInd: There is no default bearer type sdf");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_RcvEsmEmmPdnConInd_ENUM, 1);

        /* 回复EMM ID_EMM_ESM_PDN_CON_RSP（FAIL） */
        NAS_ESM_SndEsmEmmPdnConRspMsg(EMM_ESM_PDN_CON_RSLT_FAIL, 0,0);

        return ;
    }

    NAS_ESM_LOG1("NAS_ESM_RcvEsmEmmPdnConInd:The cid of the found sdf is :", ulRegCId);
    TLPS_PRINT2LAYER_INFO1(NAS_ESM_RcvEsmEmmPdnConInd_ENUM, ESM_CID_IS, ulRegCId);

    /* 将注册用的CID参数信息设置到动态表和SDF表中 */
    if (NAS_ESM_SUCCESS != NAS_ESM_SetAttachCidParaToStateTblAndSdfParaTbl(&ulStateTblId,
                                        ulRegCId, pRcvMsg->enPdnReqType))
    {
        return ;
    }

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblId);

    /*分配PTI,并存存储到承载信息中*/
    NAS_ESM_AssignPTI(&ulPti);
    pstStateAddr->stNwMsgRecord.ucPti   = (VOS_UINT8)ulPti;

    /*填充NAS_ESM_ENCODE_INFO_STRU*/
    NAS_ESM_MEM_SET_S(  (VOS_VOID*)&stEncodeInfo,
                        sizeof(NAS_ESM_ENCODE_INFO_STRU),
                        0,
                        sizeof(NAS_ESM_ENCODE_INFO_STRU));

    stEncodeInfo.bitOpESMCau            = NAS_ESM_OP_FALSE;
    stEncodeInfo.ulCid                  = pstStateAddr->ulCid;
    stEncodeInfo.ucPti                  = (VOS_UINT8)ulPti;
    stEncodeInfo.ulEpsbId               = pstStateAddr->ulEpsbId;

    stEncodeInfo.enPdnReqType           = pstStateAddr->enPdnReqType;

    /*组装PDN_Connect_Req消息*/
    if (NAS_ESM_FAILURE == NAS_ESM_EncodePdnConReqMsg(stEncodeInfo, \
                                                      pstStateAddr->stNwMsgRecord.aucMsgBuff,\
                                                      &pstStateAddr->stNwMsgRecord.ulMsgLength))
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_RcvEsmEmmPdnConInd:ERROR:EncodePdnConReqMsg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_RcvEsmEmmPdnConInd_ENUM, ESM_EncodePdnConReqMsg_fail);

        /* 回复EMM ID_EMM_ESM_PDN_CON_RSP（FAIL）*/
        NAS_ESM_SndEsmEmmPdnConRspMsg(EMM_ESM_PDN_CON_RSLT_FAIL, 0,0);

        NAS_ESM_RelStateTblResource(ulStateTblId);

        return ;
    }

    /*记录空口消息类型*/
    pstStateAddr->bitOpNwMsgRecord                = NAS_ESM_OP_TRUE;
    pstStateAddr->stNwMsgRecord.enEsmCnMsgType    = NAS_ESMCN_MSG_TYPE_PDN_CONNECT_REQ;

    /*给EMM发送ID_EMM_ESM_PDN_CON_RSP*/
    NAS_ESM_SndEsmEmmPdnConRspMsg(EMM_ESM_PDN_CON_RSLT_SUCC, \
                                  pstStateAddr->stNwMsgRecord.ulMsgLength,\
                                  pstStateAddr->stNwMsgRecord.aucMsgBuff);

    /*转换状态*/
    NAS_ESM_SetProcTransState(ulStateTblId, NAS_ESM_BEARER_PROC_TRANS_STATE_PENDING);
    NAS_ESM_SetEmmStatus(NAS_ESM_PS_REGISTER_STATUS_ATTACHING);
}

/*****************************************************************************
 Function Name   : NAS_ESM_BufferDecodedNwMsg
 Description     : 缓存ESM消息
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2009-8-19  Draft Enact
    2.lihong00150010      2010-02-09 Modify
    3.lihong00150010      2010-04-22 Modify

*****************************************************************************/
VOS_VOID  NAS_ESM_BufferDecodedNwMsg
(
    const EMM_ESM_INTRA_DATA_IND_STRU  *pstEmmEsmIntraDataIndMsg,
    NAS_ESM_CAUSE_ENUM_UINT8            enEsmCause
)
{
    NAS_ESM_ATTACHING_BUFF_ITEM_STRU   *pstDecodedNwMsg     = VOS_NULL_PTR;
    NAS_ESM_BUFF_MANAGE_INFO_STRU      *pstEsmBuffManInfo   = NAS_ESM_GetEsmBufferManageInfoAddr();
    VOS_UINT32                          ulBuffItemLen       = NAS_ESM_NULL;
    VOS_UINT32                          ulCnt               = NAS_ESM_NULL;

    /* 判断是否已到达系统能够存储缓存记录的极限 */
    if (pstEsmBuffManInfo->ucAttBuffItemNum >= NAS_ESM_MAX_ATTACHING_BUFF_ITEM_NUM)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_BufferDecodedNwMsg:WARN:Attaching Buffer is full!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_BufferDecodedNwMsg_ENUM, 1);
        return;
    }

    /* 计算缓存记录长度 */
    ulBuffItemLen = sizeof(NAS_ESM_ATTACHING_BUFF_ITEM_STRU);

    /* 获取缓存记录空间 */
    pstDecodedNwMsg = (NAS_ESM_ATTACHING_BUFF_ITEM_STRU *)
                                NAS_COMM_AllocBuffItem( NAS_COMM_BUFF_TYPE_ESM,
                                                        ulBuffItemLen);
    if (VOS_NULL_PTR == pstDecodedNwMsg)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_BufferDecodedNwMsg:WARN:NAS_COMM_AllocBuffItem is failed!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_BufferDecodedNwMsg_ENUM, LNAS_NULL_PTR);
        return;
    }

    /* 缓存译码以后的网络消息 */
    NAS_ESM_MEM_CPY_S(  &pstDecodedNwMsg->stDecodedNwMsg,
                        sizeof(EMM_ESM_INTRA_DATA_IND_STRU),
                        pstEmmEsmIntraDataIndMsg,
                        sizeof(EMM_ESM_INTRA_DATA_IND_STRU));

    /* 缓存译码结果 */
    pstDecodedNwMsg->enDecodeRslt = enEsmCause;

    /* 查找用于存储缓存记录首地址的指针 */
    for (ulCnt = NAS_ESM_NULL; ulCnt < NAS_ESM_MAX_ATTACHING_BUFF_ITEM_NUM; ulCnt++)
    {
        if (pstEsmBuffManInfo->paAttBuffer[ulCnt] == VOS_NULL_PTR)
        {
            break;
        }
    }

    if (ulCnt >= NAS_ESM_MAX_ATTACHING_BUFF_ITEM_NUM)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_BufferDecodedNwMsg:Get the valuable which stores buffer item addr failed!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_BufferDecodedNwMsg_ENUM, LNAS_FAIL);
        return ;
    }

    /* 记录存储缓存记录的首地址 */
    pstEsmBuffManInfo->paAttBuffer[ulCnt] = (VOS_VOID *)pstDecodedNwMsg;

    /* 增加缓存记录个数 */
    pstEsmBuffManInfo->ucAttBuffItemNum++;

    NAS_ESM_INFO_LOG1("NAS_ESM_BufferDecodedNwMsg:INFO:Buffer network msg success!", ulCnt);
    TLPS_PRINT2LAYER_INFO1(NAS_ESM_BufferDecodedNwMsg_ENUM, 2, ulCnt);
}

/*****************************************************************************
 Function Name  : NAS_ESM_RcvEsmEmmDataInd()
 Description    : SM模块收到ID_EMM_ESM_DATA_IND处理函数
 Input          : EMM_ESM_DATA_IND_STRU *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.丁丽 00128736      2008-09-01  Draft Enact
      2.sunbing 49683      2009-02-05  Modify
      3.lihong 00150010    2009-07-25  Modify
      4.lihong 00150010    2009-08-19  Modify
      5.lihong00150010     2009-10-30  Modify
*****************************************************************************/
VOS_VOID NAS_ESM_RcvEsmEmmDataInd( EMM_ESM_DATA_IND_STRU *pRcvMsg )
{
    NAS_ESM_CAUSE_ENUM_UINT8            enEsmCause          = NAS_ESM_CAUSE_SUCCESS;
    VOS_UINT32                          ulRcvNwMsgLen       = NAS_ESM_NULL;
    EMM_ESM_INTRA_DATA_IND_STRU        *pstEmmEsmIntraDataIndMsg = VOS_NULL_PTR;
    VOS_UINT8                          *pucTmpSmMsg         = VOS_NULL_PTR;
    NAS_ESM_SND_NW_MSG_STRU            *pstEsmSndNwMsg      = VOS_NULL_PTR;
    NAS_ESM_NW_MSG_STRU                *pstEsmNwMsgIE       = VOS_NULL_PTR;

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_RcvEsmEmmDataInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_RcvEsmEmmDataInd_ENUM, LNAS_ENTRY);

    if (NAS_ESM_L_MODE_STATUS_NORMAL != NAS_ESM_GetLModeStatus())
    {
        NAS_ESM_WARN_LOG("NAS_ESM_RcvEsmEmmDataInd: L mode is already suspended!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_RcvEsmEmmDataInd_ENUM, LNAS_EMM_LTE_SUSPEND);
        return ;
    }

    /* 如果ESM处于非注册态，则直接返回 */
    if (NAS_ESM_PS_REGISTER_STATUS_DETACHED == NAS_ESM_GetEmmStatus())
    {
        NAS_ESM_WARN_LOG("NAS_ESM_RcvEsmEmmDataInd:WARNING:Msg is discard cause ESM state is detached!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_RcvEsmEmmDataInd_ENUM, ESM_STATUS_ERROR);
        return ;
    }

    pstEmmEsmIntraDataIndMsg = NAS_ESM_MEM_ALLOC(sizeof(EMM_ESM_INTRA_DATA_IND_STRU));
    if(VOS_NULL_PTR == pstEmmEsmIntraDataIndMsg)
    {
        NAS_ESM_ERR_LOG("NAS_ESM_RcvEsmEmmDataInd:Alloc Mem fail!");
        TLPS_PRINT2LAYER_ERROR1(NAS_ESM_RcvEsmEmmDataInd_ENUM, LNAS_NULL_PTR, 1);
        return;
    }

    NAS_ESM_MEM_SET_S(  pstEmmEsmIntraDataIndMsg,
                        sizeof(EMM_ESM_INTRA_DATA_IND_STRU),
                        0,
                        sizeof(EMM_ESM_INTRA_DATA_IND_STRU));

    /*构造内部的ID_EMM_ESM_DATA_IND消息(携带一条已解析的空口消息)*/
    pstEmmEsmIntraDataIndMsg->ulSenderPid = PS_PID_MM;

    pstEsmNwMsgIE = &(pstEmmEsmIntraDataIndMsg->stEsmNwMsgIE);

    /*取出此消息中所包含SM消息的长度*/
    ulRcvNwMsgLen = pRcvMsg->stEsmMsg.ulEsmMsgSize;
    if( ulRcvNwMsgLen > ESM_MAX_MSG_CONTAINER_CNTNTS_LEN )
    {
        NAS_ESM_WARN_LOG("NAS_ESM_RcvEsmEmmDataInd:WARNING:EMM->SM Message NW Msg over-long!");
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_RcvEsmEmmDataInd_ENUM, LNAS_MSG_INVALID, 1);
        ulRcvNwMsgLen = ESM_MAX_MSG_CONTAINER_CNTNTS_LEN;
    }

    /*取得SM消息首地址*/
    pucTmpSmMsg = pRcvMsg->stEsmMsg.aucEsmMsg;

    pstEmmEsmIntraDataIndMsg->ulMsgId = ID_EMM_ESM_DATA_IND;

    /*清空NAS_ESM_NW_MSG_STRU*/
    NAS_ESM_MEM_SET_S(  (VOS_VOID*)pstEsmNwMsgIE,
                        sizeof(NAS_ESM_NW_MSG_STRU),
                        0,
                        sizeof(NAS_ESM_NW_MSG_STRU));

    /*调用空口消息解析函数, 如果解析失败直接返回*/
    enEsmCause = NAS_ESM_DecodeNwMsg( pucTmpSmMsg,
                                   &ulRcvNwMsgLen,
                                    pstEsmNwMsgIE );

    /* 若SM的状态为NAS_ESM_PS_REGISTER_STATUS_ATTACHING，且此消息不为
       ESM INFORMATION REQ消息或者缺省承载激活请求消息，则对消息进行缓存；
       否则直接处理消息 */
    if((NAS_ESM_PS_REGISTER_STATUS_ATTACHING == NAS_ESM_GetEmmStatus())
        && (NAS_ESMCN_MSG_TYPE_ESM_INFORMATION_REQ != pstEsmNwMsgIE->enEsmCnMsgType)
        && (NAS_ESMCN_MSG_TYPE_ACT_DEFLT_EPS_BEARER_CNTXT_REQ != pstEsmNwMsgIE->enEsmCnMsgType)
        && (NAS_ESMCN_MSG_TYPE_PDN_CONNECT_REJ != pstEsmNwMsgIE->enEsmCnMsgType))
    {
        /* 缓存ESM消息 */
        NAS_ESM_BufferDecodedNwMsg(pstEmmEsmIntraDataIndMsg, enEsmCause);

        NAS_ESM_MEM_FREE(pstEmmEsmIntraDataIndMsg);

        return;
    }

    /*分配空间和检测是否分配成功,用于存放SM准备回复给网侧的消息*/
    pstEsmSndNwMsg = NAS_ESM_GetEsmSndNwMsgAddr();
    pstEsmSndNwMsg->pucNwMsg = (VOS_UINT8 *)NAS_ESM_MEM_ALLOC(ESM_MAX_MSG_CONTAINER_CNTNTS_LEN);
    if ( VOS_NULL_PTR == pstEsmSndNwMsg->pucNwMsg )
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_RcvEsmEmmDataInd:ERROR:Alloc Snd Nw Msg fail!");
        TLPS_PRINT2LAYER_ERROR1(NAS_ESM_RcvEsmEmmDataInd_ENUM, LNAS_NULL_PTR, 2);

        NAS_ESM_MEM_FREE(pstEmmEsmIntraDataIndMsg);
        return;
    }

    /*如果解析错误，返回拒绝或丢弃*/
    if( NAS_ESM_CAUSE_SUCCESS != enEsmCause )
    {
        NAS_ESM_ProcNwMsgForDecodeError(pstEsmNwMsgIE,enEsmCause);

        /*打印异常信息*/
        NAS_ESM_WARN_LOG("NAS_ESM_RcvEsmEmmDataInd:WARNING: NW Message Error!");
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_RcvEsmEmmDataInd_ENUM, LNAS_MSG_INVALID, 2);
    }
    else/*如果消息解析成功*/
    {
        /*处理此条空口消息*/
        NAS_ESM_NwMsgProcess(pstEmmEsmIntraDataIndMsg);
    }

    /*释放空口消息占用的空间*/
    NAS_ESM_MEM_FREE(pstEsmSndNwMsg->pucNwMsg);
    pstEsmSndNwMsg->pucNwMsg = VOS_NULL_PTR;
    pstEsmSndNwMsg->ulNwMsgSize = NAS_ESM_NULL;

    NAS_ESM_MEM_FREE(pstEmmEsmIntraDataIndMsg);
}


/*****************************************************************************
 Function Name  : NAS_ESM_RcvEsmEmmBearerStatusInd()
 Description    : SM模块收到ID_EMM_ESM_BEARER_STATUS_IND处理函数
 Input          : EMM_ESM_BEARER_STATUS_IND_STRU *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.丁丽     00128736        2008-09-01      Draft Enact
      2.lihong    00150010        2009-10-30      Modify
      2.liuhua    00212067        2012-09-06      Add support for double APN
*****************************************************************************/
VOS_VOID NAS_ESM_RcvEsmEmmBearerStatusInd(const EMM_ESM_BEARER_STATUS_IND_STRU *pRcvMsg )
{
    VOS_UINT32                  ulCnt                       = NAS_ESM_NULL;
    VOS_UINT32                  ulQueryRslt                 = NAS_ESM_FAILURE;
    VOS_UINT32                  ulEpsbId                    = NAS_ESM_NULL;
    VOS_UINT32                  ulEpsbIdNum                 = NAS_ESM_NULL;
    VOS_UINT32                  aulEpsbId[NAS_ESM_MAX_EPSB_NUM] = {NAS_ESM_NULL};
    VOS_UINT32                  ulStateTblIndex             =  NAS_ESM_NULL;
    NAS_ESM_EPSB_CNTXT_INFO_STRU *pstEpsbCntxtInfo          = VOS_NULL_PTR;

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_RcvEsmEmmBearerStatusInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_RcvEsmEmmBearerStatusInd_ENUM, LNAS_ENTRY);

    if (NAS_ESM_L_MODE_STATUS_NORMAL != NAS_ESM_GetLModeStatus())
    {
        NAS_ESM_WARN_LOG("NAS_ESM_RcvEsmEmmBearerStatusInd: L mode is already suspended!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_RcvEsmEmmBearerStatusInd_ENUM, LNAS_EMM_LTE_SUSPEND);
        return ;
    }

    /* 如果ESM处于非注册态或注册中态，则直接返回 */
    if (NAS_ESM_PS_REGISTER_STATUS_ATTACHED != NAS_ESM_GetEmmStatus())
    {
        NAS_ESM_WARN_LOG("NAS_ESM_RcvEsmEmmBearerStatusInd:WARNING:Msg is discard cause ESM state is not attached!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_RcvEsmEmmBearerStatusInd_ENUM, ESM_STATUS_ERROR);
        return ;
    }

    /*取出ID_EMM_ESM_BEARER_STATUS_IND消息中的EPSID信息*/
    ulEpsbIdNum = pRcvMsg->ulEpsIdNum;

    NAS_ESM_MEM_CPY_S(  aulEpsbId,
                        sizeof(VOS_UINT32) * NAS_ESM_MAX_EPSB_NUM,
                        pRcvMsg->aulEsmEpsId,
                        ulEpsbIdNum*(sizeof(VOS_UINT32)/sizeof(VOS_UINT8)));

    /*轮询每一个承载信息*/
    for( ulEpsbId = NAS_ESM_MIN_EPSB_ID; ulEpsbId <= NAS_ESM_MAX_EPSB_ID; ulEpsbId++ )
    {
        /*取出承载信息*/
        pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);

        /*如果此承载未激活*/
        if( NAS_ESM_BEARER_STATE_INACTIVE == pstEpsbCntxtInfo->enBearerCntxtState )
        {
            continue;
        }

        ulQueryRslt = NAS_ESM_FAILURE;

        /*查询ID_EMM_ESM_BEARER_STATUS_IND消息的EPSID信息中是否包含此承载ID*/
        for( ulCnt = 0; ulCnt < ulEpsbIdNum; ulCnt++ )
        {
            if( ulEpsbId == aulEpsbId[ulCnt] )
            {
                ulQueryRslt = NAS_ESM_SUCCESS;
                break;
            }
        }

        /*如果不包含*/
        if( NAS_ESM_FAILURE == ulQueryRslt )
        {
            /*通知APP释放承载，并释放相关承载和资源*/
            NAS_ESM_DeactBearerAndInformApp(ulEpsbId);

            /*清除和中止与ulEpsbId关联的流程信息*/
            if(NAS_ESM_SUCCESS == NAS_ESM_QueryStateTblIndexByEpsbId(ulEpsbId, &ulStateTblIndex))
            {
                NAS_ESM_RelStateTblResource(ulStateTblIndex);
            }
        }
    }

    /*通知EMM当前承载状态信息，发送ID_EMM_ESM_BEARER_STATUS_REQ*/
    NAS_ESM_SndEsmEmmBearerStatusReqMsg(EMM_ESM_BEARER_CNTXT_MOD_MUTUAL);

    /*如果支持双APN，则检查注册承载，并进行处理*/
    if (NAS_ESM_OP_TRUE == NAS_ESM_AttachBearerReestEnable())
    {
        NAS_ESM_TimerStop(0, TI_NAS_ESM_ATTACH_BEARER_REEST);
        if (NAS_ESM_UNASSIGNED_EPSB_ID == NAS_ESM_GetAttachBearerId())
        {
            NAS_ESM_ReestablishAttachBearer();
        }
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_BufferedNwMsgProc
 Description     : 处理ESM缓存消息
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-8-19  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_BufferedNwMsgProc()
{
    NAS_ESM_ATTACHING_BUFF_ITEM_STRU   *pstDecodedNwMsg     = VOS_NULL_PTR;
    NAS_ESM_SND_NW_MSG_STRU            *pstEsmSndNwMsg      = VOS_NULL_PTR;
    VOS_UINT32                          ulCnt               = NAS_ESM_NULL;

    /*分配空间和检测是否分配成功,用于存放SM准备回复给网侧的消息*/
    pstEsmSndNwMsg = NAS_ESM_GetEsmSndNwMsgAddr();
    pstEsmSndNwMsg->pucNwMsg = (VOS_UINT8 *)NAS_ESM_MEM_ALLOC(ESM_MAX_MSG_CONTAINER_CNTNTS_LEN);

    if ( VOS_NULL_PTR == pstEsmSndNwMsg->pucNwMsg )
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_BufferedNwMsgProc:ERROR:Alloc Snd Nw Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_BufferedNwMsgProc_ENUM, LNAS_NULL_PTR);
        return;
    }

    for (ulCnt = NAS_ESM_NULL; ulCnt < NAS_ESM_MAX_ATTACHING_BUFF_ITEM_NUM; ulCnt++)
    {
        /* 获取缓存记录 */
        pstDecodedNwMsg = (NAS_ESM_ATTACHING_BUFF_ITEM_STRU*)
                                NAS_ESM_GetBuffItemAddr(NAS_ESM_BUFF_ITEM_TYPE_ATTACHING, ulCnt);

        if (pstDecodedNwMsg == VOS_NULL_PTR)
        {
            continue;
        }

        NAS_ESM_INFO_LOG1("NAS_ESM_BufferedNwMsgProc:NORM:Buffer Itmem Index:", ulCnt);
        TLPS_PRINT2LAYER_INFO1(NAS_ESM_BufferedNwMsgProc_ENUM, 1, ulCnt);

        pstEsmSndNwMsg->ulNwMsgSize = NAS_ESM_NULL;

        NAS_ESM_MEM_SET_S(  pstEsmSndNwMsg->pucNwMsg,
                            ESM_MAX_MSG_CONTAINER_CNTNTS_LEN,
                            NAS_ESM_NULL,
                            ESM_MAX_MSG_CONTAINER_CNTNTS_LEN);

        /*如果解析错误，返回拒绝或丢弃*/
        if( NAS_ESM_CAUSE_SUCCESS != pstDecodedNwMsg->enDecodeRslt)
        {
            NAS_ESM_ProcNwMsgForDecodeError(&pstDecodedNwMsg->stDecodedNwMsg.stEsmNwMsgIE,
                                            pstDecodedNwMsg->enDecodeRslt);

            /*打印异常信息*/
            NAS_ESM_WARN_LOG("NAS_ESM_BufferedNwMsgProc:WARNING: NW Message Error!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_BufferedNwMsgProc_ENUM, 2);
        }
        else/*如果消息解析成功*/
        {
            /*处理此条空口消息*/
            NAS_ESM_NwMsgProcess(&pstDecodedNwMsg->stDecodedNwMsg);
        }

        /* 清除缓存记录 */
        NAS_ESM_ClearEsmBuffItem(NAS_ESM_BUFF_ITEM_TYPE_ATTACHING, ulCnt);
    }

    /*释放空口消息占用的空间*/
    NAS_ESM_MEM_FREE(pstEsmSndNwMsg->pucNwMsg);
    pstEsmSndNwMsg->pucNwMsg = VOS_NULL_PTR;
    pstEsmSndNwMsg->ulNwMsgSize = NAS_ESM_NULL;
}

/*****************************************************************************
 Function Name  : NAS_ESM_RcvEsmEmmEstCnf()
 Description    : SM模块收到ID_EMM_ESM_EST_CNF处理函数
 Input          : EMM_ESM_EST_CNF_STRU *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.丁丽 00128736      2008-09-01  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_RcvEsmEmmEstCnf(const EMM_ESM_EST_CNF_STRU *pRcvMsg )
{
    EMM_ESM_ATTACH_RESULT_ENUM_UINT32   ulEstRst         = NAS_ESM_NULL;
    NAS_ESM_STATE_INFO_STRU             *pstStateTblInfo = NAS_ESM_NULL;
    VOS_UINT32                          ulStateTblIndex  = 0;

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG2("NAS_ESM_RcvEsmEmmEstCnf is entered.", NAS_ESM_GetLModeStatus(), pRcvMsg->ulEstRst);
    TLPS_PRINT2LAYER_INFO2(NAS_ESM_RcvEsmEmmEstCnf_ENUM, LNAS_ENTRY, NAS_ESM_GetLModeStatus(), pRcvMsg->ulEstRst);

    if (NAS_ESM_L_MODE_STATUS_NORMAL != NAS_ESM_GetLModeStatus())
    {
        NAS_ESM_WARN_LOG("NAS_ESM_RcvEsmEmmEstCnf: L mode is already suspended!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_RcvEsmEmmEstCnf_ENUM, LNAS_EMM_LTE_SUSPEND);
        return ;
    }

    /*取出消息内容*/
    ulEstRst = ((EMM_ESM_EST_CNF_STRU *)pRcvMsg)->ulEstRst;

    /*判断当前EMM注册状态，如果是Attaching，根据消息内容，保存注册状态；否则丢弃*/
    if( NAS_ESM_PS_REGISTER_STATUS_ATTACHING == NAS_ESM_GetEmmStatus())
    {
        /*注册成功*/
        if( EMM_ESM_ATTACH_RESULT_SUCC == ulEstRst )
        {
            /*保存注册状态*/
            NAS_ESM_SetEmmStatus(NAS_ESM_PS_REGISTER_STATUS_ATTACHED);

            /* 处理ESM缓存消息 */
            NAS_ESM_BufferedNwMsgProc();
        }
        else
        {
            /*EMM注册失败或去注册，释放资源*/
            NAS_ESM_RcvEmmDetachMsg();
        }
    }
    else if (NAS_ESM_PS_REGISTER_STATUS_ATTACHED == NAS_ESM_GetEmmStatus())
    {
        /* 如果紧急PDN连接建立请求和EMM StatusInd对冲时会出现当此分支，
         * 对冲时EMM针对紧急PDN的EstReq将返回失败，ESM后续处理如下:
         *      1. 不改变ESM记录的Emm注册状态
         *      2. 将缓存的紧急PDN连接建立消息使用DataReq进行重发，并启动T3482
         */
        if ((EMM_ESM_ATTACH_RESULT_FAIL == ulEstRst) &&
            (NAS_ESM_SUCCESS == NAS_ESM_QueryStateTblIndexForEmc(&ulStateTblIndex)))
        {
            pstStateTblInfo = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

            NAS_ESM_LOG1("NAS_ESM_RcvEsmEmmEstCnf", pstStateTblInfo->ulCid);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_RcvEsmEmmEstCnf_ENUM, 1, pstStateTblInfo->ulCid);

            NAS_ESM_SndEsmEmmDataReqMsg(pstStateTblInfo->stNwMsgRecord.ulOpId,
                                        pstStateTblInfo->stNwMsgRecord.ucIsEmcPdnReq,
                                        pstStateTblInfo->stNwMsgRecord.ulMsgLength,
                                        pstStateTblInfo->stNwMsgRecord.aucMsgBuff);

            /*启动T3482定时器*/
            NAS_ESM_TimerStart(ulStateTblIndex, TI_NAS_ESM_T3482);

            /*状态转换*/
            /*之前已经更改，这里不再设置状态*/
        }
    }
    else
    {
        /*打印异常信息*/
        NAS_ESM_WARN_LOG("NAS_ESM_RcvEsmEmmEstCnf:Register Status is not attachingl!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_RcvEsmEmmEstCnf_ENUM, ESM_STATUS_ERROR);
    }
}

/*****************************************************************************
 Function Name  : NAS_ESM_RcvEsmEmmStatusInd()
 Description    : SM模块收到ID_EMM_ESM_STATUS_IND处理函数
 Input          : EMM_ESM_STATUS_IND_STRU *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.丁丽 00128736      2008-09-01  Draft Enact
      2.lihong00150010     2009-10-30  Modify

*****************************************************************************/
VOS_VOID NAS_ESM_RcvEsmEmmStatusInd(const EMM_ESM_STATUS_IND_STRU *pRcvMsg )
{
    EMM_ESM_ATTACH_STATUS_ENUM_UINT32   ulEstRst;

	#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    VOS_UINT32                          ulIndex;
    #endif

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_RcvEsmEmmStatusInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_RcvEsmEmmStatusInd_ENUM, LNAS_ENTRY);

    /*取出消息内容*/
    ulEstRst = ((EMM_ESM_STATUS_IND_STRU *)pRcvMsg)->enEMMStatus;

    /*如果消息内容为ATTACHED，记录注册状态*/
    if( EMM_ESM_ATTACH_STATUS_ATTACHED == ulEstRst )
    {
        /*保存注册状态*/
        NAS_ESM_SetEmmStatus(NAS_ESM_PS_REGISTER_STATUS_ATTACHED);

        /* 处理ESM缓存消息 */
        NAS_ESM_BufferedNwMsgProc();

        #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        if (NAS_ESM_SUCCESS == NAS_ESM_GetAttachPdnInEhrpdEntity(&ulIndex))
        {
            /* PDN连接恢复成功的处理 */
            NAS_ESM_EhrpdPdnConnectHandOverSuccProc(ulIndex);
        }
        #endif
    }
    /*消息内容为DETACHED，释放资源*/
    else if(EMM_ESM_ATTACH_STATUS_DETACHED == ulEstRst)
    {
        /*如果延迟释放非紧急承载定时器存在，则停止*/
        NAS_ESM_TimerStop(0, TI_NAS_ESM_REL_NON_EMC_BEARER);

        /*EMM注册失败或去注册，释放资源*/
        NAS_ESM_RcvEmmDetachMsg();
    }
    else if (EMM_ESM_ATTACH_STATUS_EMC_ATTACHING == ulEstRst)
    {
        /* 由紧急PDN连接导致EMM的TAU/Service/Attach失败，且后续将要进行紧急注册，
         * ESM清除紧急注册以外的资源
         */
        NAS_ESM_ClearEsmResoureWhenEstingEmcPdn();
    }
    else
    {
        /*bsun 检查动态表，重启流程*/
        NAS_ESM_NORM_LOG("NAS_ESM_RcvEsmEmmStatusInd:NORM:UE re-entry Sevice NW!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_RcvEsmEmmStatusInd_ENUM, 1);
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_RcvEmmDetachMsg
 Description     : SM收到EMM注册失败或去注册信息，回复APP信息和释放本地资源
 Input           : VOS_VOID
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunbing      2008-10-17  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_RcvEmmDetachMsg( VOS_VOID )
{
    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_RcvEmmDetachMsg is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_RcvEmmDetachMsg_ENUM, LNAS_ENTRY);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

    /* 如果EMM的状态已经为未注册，不用通知ERABM释放，只释放资源 */
    if (NAS_ESM_PS_REGISTER_STATUS_DETACHED == NAS_ESM_GetEmmStatus())
    {
        NAS_ESM_ClearEsmResource();
        return;
    }
#endif

    /* 通知RABM清除资源 */
    NAS_ESM_SndEsmRabmRelIndMsg();


    /*清资源*/
    NAS_ESM_ClearEsmResource();
}
/*****************************************************************************
 Function Name   : NAS_ESM_SndEsmEmmSuspendRsp
 Description     : ESM模块回复ID_EMM_ESM_SUSPEND_RSP消息
 Input           : EMM_ESM_RSLT_TYPE_ENUM_UINT32       enRslt
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2011-05-02  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_SndEsmEmmSuspendRsp
(
    EMM_ESM_RSLT_TYPE_ENUM_UINT32       enRslt
)
{
    EMM_ESM_SUSPEND_RSP_STRU           *pstEsmEmmSuspendRsp  = VOS_NULL_PTR;

    /*分配空间并检验分配是否成功*/
    pstEsmEmmSuspendRsp = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(EMM_ESM_SUSPEND_RSP_STRU));

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pstEsmEmmSuspendRsp)
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEsmEmmSuspendRsp:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEsmEmmSuspendRsp_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*清空*/
    NAS_ESM_MEM_SET_S(  NAS_ESM_GET_MSG_ENTITY(pstEsmEmmSuspendRsp),
                        NAS_ESM_GET_MSG_LENGTH(pstEsmEmmSuspendRsp),
                        0,
                        NAS_ESM_GET_MSG_LENGTH(pstEsmEmmSuspendRsp));

    /*填写消息头*/
    NAS_ESM_WRITE_EMM_MSG_HEAD(pstEsmEmmSuspendRsp, ID_EMM_ESM_SUSPEND_RSP);

    /*填写响应结果*/
    pstEsmEmmSuspendRsp->enRslt= enRslt;

    /*调用消息发送函数 */
    NAS_ESM_SND_MSG(pstEsmEmmSuspendRsp);
}

/*****************************************************************************
 Function Name   : NAS_ESM_SndEsmEmmResumeRsp
 Description     : ESM模块回复ID_EMM_ESM_RESUME_RSP消息
 Input           : EMM_ESM_RSLT_TYPE_ENUM_UINT32       enRslt
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2011-05-02  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_SndEsmEmmResumeRsp
(
    EMM_ESM_RSLT_TYPE_ENUM_UINT32       enRslt
)
{
    EMM_ESM_RESUME_RSP_STRU            *pstEsmEmmResumeRsp  = VOS_NULL_PTR;

    /*分配空间并检验分配是否成功*/
    pstEsmEmmResumeRsp = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(EMM_ESM_SUSPEND_RSP_STRU));

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pstEsmEmmResumeRsp)
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEsmEmmResumeRsp:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEsmEmmResumeRsp_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*清空*/
    NAS_ESM_MEM_SET_S(  NAS_ESM_GET_MSG_ENTITY(pstEsmEmmResumeRsp),
                        NAS_ESM_GET_MSG_LENGTH(pstEsmEmmResumeRsp),
                        0,
                        NAS_ESM_GET_MSG_LENGTH(pstEsmEmmResumeRsp));

    /*填写消息头*/
    NAS_ESM_WRITE_EMM_MSG_HEAD(pstEsmEmmResumeRsp, ID_EMM_ESM_RESUME_RSP);

    /*填写响应结果*/
    pstEsmEmmResumeRsp->enRslt= enRslt;

    /*调用消息发送函数 */
    NAS_ESM_SND_MSG(pstEsmEmmResumeRsp);
}

/*****************************************************************************
 Function Name  : NAS_ESM_SndEsmEmmBearerStatusReqMsg()
 Description    : SM模块发送ID_EMM_ESM_BEARER_STATUS_REQ函数
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.丁丽 00128736      2008-09-01  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_SndEsmEmmBearerStatusReqMsg(
                    EMM_ESM_BEARER_CNTXT_MOD_ENUM_UINT32 enBearerCntxtChangeMod)
{
    VOS_UINT32                  ulCnt                       = NAS_ESM_NULL;
    VOS_UINT32                  ulEpsbIdNum                 = NAS_ESM_NULL;
    VOS_UINT32                  aulEpsbId[NAS_ESM_MAX_EPSB_NUM]  = {NAS_ESM_NULL};
    EMM_ESM_BEARER_STATUS_REQ_STRU *pSmEmmBearStatusReqMsg   = VOS_NULL_PTR;

    /*找出已激活承载，并记录其ID*/
    for( ulCnt = NAS_ESM_MIN_EPSB_ID; ulCnt <= NAS_ESM_MAX_EPSB_ID; ulCnt++ )
    {
        /*此承载已激活*/
        if( NAS_ESM_BEARER_STATE_ACTIVE == NAS_ESM_GetBearCntxtState(ulCnt) )
        {
            /*保存已激活承载ID,准备发送给RABM*/
            aulEpsbId[ulEpsbIdNum++] = ulCnt;
        }
    }

    /*分配空间并检验分配是否成功*/
    pSmEmmBearStatusReqMsg = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(EMM_ESM_BEARER_STATUS_REQ_STRU));

    if ( VOS_NULL_PTR == pSmEmmBearStatusReqMsg )
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEsmEmmBearerStatusReqMsg:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEsmEmmBearerStatusReqMsg_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*清空*/
    NAS_ESM_MEM_SET_S(  NAS_ESM_GET_MSG_ENTITY(pSmEmmBearStatusReqMsg),
                        NAS_ESM_GET_MSG_LENGTH(pSmEmmBearStatusReqMsg),
                        0,
                        NAS_ESM_GET_MSG_LENGTH(pSmEmmBearStatusReqMsg));

    /*此次修改承载上下文的方式*/
    pSmEmmBearStatusReqMsg->enBearerCntxtMod = enBearerCntxtChangeMod;

    /*将ulEpsbIdNum、pulEpsbId填入pSmEmmBearStatusReqMsg*/
    pSmEmmBearStatusReqMsg->ulEpsIdNum = ulEpsbIdNum;

    NAS_ESM_MEM_CPY_S(  (VOS_UINT8*)pSmEmmBearStatusReqMsg->aulEsmEpsId,
                        sizeof(VOS_UINT32) * EMM_ESM_MAX_EPS_BEARER_NUM,
                        (VOS_UINT8*)aulEpsbId,
                        (pSmEmmBearStatusReqMsg->ulEpsIdNum)*(sizeof(VOS_UINT32)/sizeof(VOS_UINT8)));

    /*填写当前是否有紧急PDN连接*/
    pSmEmmBearStatusReqMsg->ulExistEmcPdnFlag = NAS_ESM_HasExistedEmergencyPdn();

    /*填写消息头*/
    NAS_ESM_WRITE_EMM_MSG_HEAD(pSmEmmBearStatusReqMsg,ID_EMM_ESM_BEARER_STATUS_REQ);

    /* 调用消息发送函数 */
    NAS_ESM_SND_MSG(pSmEmmBearStatusReqMsg);

}


/*****************************************************************************
 Function Name  : NAS_ESM_SndEsmEmmPdnConRspMsg()
 Description    : SM模块发送ID_EMM_ESM_PDN_CON_RSP函数
 Input          : EMM_ESM_PDN_CON_RSP_ENUM_UINT8        ulRst
                  VOS_UINT32 ulLength, const VOS_UINT8 *pucSendMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.丁丽 00128736      2008-09-01  Draft Enact
      2.sunbing 49683       2009-02-05  Modify
*****************************************************************************/
VOS_VOID NAS_ESM_SndEsmEmmPdnConRspMsg( EMM_ESM_PDN_CON_RSLT_ENUM_UINT32        ulRst,
                                                          VOS_UINT32 ulLength, const VOS_UINT8 *pucSendMsg)
{
    VOS_UINT32                          ulTmpLength       = NAS_ESM_NULL;
    EMM_ESM_PDN_CON_RSP_STRU           *pSmEmmPdnConRsp   = VOS_NULL_PTR;

    /*根据空口消息的长度分配空间，处于消息头外*/
    /* lint -e831 */
    if(ulLength > ESM_MIN_SND_MSG_LEN)
    {
        ulTmpLength = ulLength - ESM_MIN_SND_MSG_LEN ;
        pSmEmmPdnConRsp = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(EMM_ESM_PDN_CON_RSP_STRU) + ulTmpLength);
    }
    /* lint +e831 */
    else/*如果长度小于ESM_MIN_SND_MSG_LEN，分配的空间等于ESM_MIN_SND_MSG_LEN*/
    {
        pSmEmmPdnConRsp = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(EMM_ESM_PDN_CON_RSP_STRU));
    }


    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pSmEmmPdnConRsp)
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEsmEmmPdnConRspMsg:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEsmEmmPdnConRspMsg_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*清空*/
    NAS_ESM_MEM_SET_S(  NAS_ESM_GET_MSG_ENTITY(pSmEmmPdnConRsp),
                        NAS_ESM_GET_MSG_LENGTH(pSmEmmPdnConRsp),
                        0,
                        NAS_ESM_GET_MSG_LENGTH(pSmEmmPdnConRsp));

    /*填写消息头*/
    NAS_ESM_WRITE_EMM_MSG_HEAD(pSmEmmPdnConRsp,ID_EMM_ESM_PDN_CON_RSP);

    /*填写响应结果*/
    pSmEmmPdnConRsp->ulRst = ulRst;

    /*如果响应结果为成功，填写空口消息*/

    if( EMM_ESM_PDN_CON_RSLT_SUCC == ulRst )
    {
        /*填写空口消息头长度*/
        pSmEmmPdnConRsp->stEsmMsg.ulEsmMsgSize = ulLength;

        /*将空口消息存放到EMM_ESM_PDN_CON_RSP_STRU结构中*/
        /*lint -e669*/
        NAS_ESM_MEM_CPY_S(pSmEmmPdnConRsp->stEsmMsg.aucEsmMsg, ulLength, pucSendMsg, ulLength);/*lint !e669*/
        /*lint +e669*/
    }


    /*调用消息发送函数 */
    NAS_ESM_SND_MSG(pSmEmmPdnConRsp);

}

/*****************************************************************************
 Function Name   : NAS_ESM_SndEsmEmmEstReqMsg
 Description     : 发送上行空口消息，触发MM发起注册
 Input           : VOS_UINT32 ulLength
                   VOS_UINT8 *pucSendMsg
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunbing49683      2009-2-28  Draft Enact

*****************************************************************************/

/*lint -e669*/
/*lint -e831*/
VOS_VOID NAS_ESM_SndEsmEmmEstReqMsg(VOS_UINT32 ulOpId,
                                      VOS_UINT8  ucIsEmcPdnType,
                                      VOS_UINT32 ulLength,
                                      const VOS_UINT8 *pucSendMsg)
{
    VOS_UINT32                          ulTmpLength         = NAS_ESM_NULL;
    EMM_ESM_EST_REQ_STRU               *pSmEmmEstReq        = VOS_NULL_PTR;

    /*根据空口消息的长度分配空间*/
    if( NAS_ESM_NULL == ulLength)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_SndEsmEmmEstReqMsg: WARNING: Msg Length is zero");
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_SndEsmEmmEstReqMsg_ENUM, LNAS_NULL_PTR, 1);
        return ;
    }
    if(ulLength > ESM_MIN_SND_MSG_LEN)
    {
        ulTmpLength = ulLength - ESM_MIN_SND_MSG_LEN ;
        pSmEmmEstReq = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(EMM_ESM_EST_REQ_STRU) + ulTmpLength);
    }
    else/*如果长度小于ESM_MIN_SND_MSG_LEN，分配的空间等于ESM_MIN_SND_MSG_LEN*/
    {
        pSmEmmEstReq = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(EMM_ESM_EST_REQ_STRU));
    }

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pSmEmmEstReq)
    {
         /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEsmEmmEstReqMsg:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR1(NAS_ESM_SndEsmEmmEstReqMsg_ENUM, LNAS_NULL_PTR, 2);
        return ;
    }

    /*清空*/
    NAS_ESM_MEM_SET_S(  NAS_ESM_GET_MSG_ENTITY(pSmEmmEstReq),
                        NAS_ESM_GET_MSG_LENGTH(pSmEmmEstReq),
                        0,
                        NAS_ESM_GET_MSG_LENGTH(pSmEmmEstReq));

    /*填写空口消息头长度*/
    pSmEmmEstReq->stEsmMsg.ulEsmMsgSize    = ulLength;

    /*将空口消息存放到EMM_ESM_EST_REQ_STRU结构中*/
    /*lint -e669*/
    NAS_ESM_MEM_CPY_S(pSmEmmEstReq->stEsmMsg.aucEsmMsg, ulLength, pucSendMsg, ulLength);
    /*lint +e669*/

    /*填写是否是紧急PDN连接请求类型*/
    pSmEmmEstReq->ulIsEmcType = ucIsEmcPdnType;

    /*填写OpId*/
    pSmEmmEstReq->ulOpId = ulOpId;

    /*填写消息头*/
    NAS_ESM_WRITE_EMM_MSG_HEAD(pSmEmmEstReq,ID_EMM_ESM_EST_REQ);

    /*调用消息发送函数 */
    NAS_ESM_SND_MSG(pSmEmmEstReq);

}
/*lint +e831*/
/*lint +e669*/


/*****************************************************************************
 Function Name   : NAS_ESM_SndEsmEmmPdnConSuccReqMsg
 Description     : ATTACH过程中，ESM建立缺省承载成功，
                   向EMM返回EMM_ESM_PDN_CON_SUCC_REQ_STRU消息；
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2009-8-18  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_SndEsmEmmPdnConSuccReqMsg
(
     VOS_UINT32                         ulLength,
     const VOS_UINT8                   *pucSendMsg
)
{
    VOS_UINT32                          ulTmpLength         = NAS_ESM_NULL;
    EMM_ESM_PDN_CON_SUCC_REQ_STRU      *pSmEmmPdnConSucc    = VOS_NULL_PTR;

    /*根据空口消息的长度分配空间*/
    if( NAS_ESM_NULL == ulLength)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_SndEsmEmmPdnConSuccReqMsg: WARNING: Msg Length is zero");
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_SndEsmEmmPdnConSuccReqMsg_ENUM, LNAS_NULL_PTR, 1);
        return ;
    }
    else if(ulLength > ESM_MIN_SND_MSG_LEN)
    {
        ulTmpLength = ulLength - ESM_MIN_SND_MSG_LEN ;
        pSmEmmPdnConSucc = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(EMM_ESM_PDN_CON_SUCC_REQ_STRU) + ulTmpLength);
    }
    else/*如果长度小于ESM_MIN_SND_MSG_LEN，分配的空间等于ESM_MIN_SND_MSG_LEN*/
    {
        pSmEmmPdnConSucc = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(EMM_ESM_PDN_CON_SUCC_REQ_STRU));
    }

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pSmEmmPdnConSucc)
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEsmEmmPdnConSuccReqMsg:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR1(NAS_ESM_SndEsmEmmPdnConSuccReqMsg_ENUM, LNAS_NULL_PTR, 2);
        return ;
    }

    /*清空*/
    NAS_ESM_MEM_SET_S(  NAS_ESM_GET_MSG_ENTITY(pSmEmmPdnConSucc),
                        NAS_ESM_GET_MSG_LENGTH(pSmEmmPdnConSucc),
                        0,
                        NAS_ESM_GET_MSG_LENGTH(pSmEmmPdnConSucc));

    /*填写空口消息头长度*/
    pSmEmmPdnConSucc->stEsmMsg.ulEsmMsgSize = ulLength;

    /*将空口消息存放到EMM_ESM_DATA_REQ_STRU结构中*/
    /*lint -e669 */
    NAS_ESM_MEM_CPY_S(pSmEmmPdnConSucc->stEsmMsg.aucEsmMsg, ulLength, pucSendMsg, ulLength);/*lint !e669 !e670*/
    /*lint +e669*/

    /*填写消息头*/
    NAS_ESM_WRITE_EMM_MSG_HEAD(pSmEmmPdnConSucc,ID_EMM_ESM_PDN_CON_SUCC_REQ);

    /*调用消息发送函数 */
    NAS_ESM_SND_MSG(pSmEmmPdnConSucc);

}


/*****************************************************************************
 Function Name   : NAS_ESM_SndEsmEmmDataReqMsg
 Description     : 向MM发送DATA_REQ消息，携带上行空口消息
 Input           : VOS_UINT32 ulLength
                   VOS_UINT8 *pucSendMsg
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunbing49683      2009-2-28  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_SndEsmEmmDataReqMsg( VOS_UINT32 ulOpId,
                                       VOS_UINT8 ulIsEmcPdnType,
                                       VOS_UINT32 ulLength,
                                       const VOS_UINT8 *pucSendMsg)
{
    VOS_UINT32                          ulTmpLength         = NAS_ESM_NULL;
    EMM_ESM_DATA_REQ_STRU              *pSmEmmDataReq       = VOS_NULL_PTR;

    /*根据空口消息的长度分配空间*/
    if( NAS_ESM_NULL == ulLength)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_SndEsmEmmDataReqMsg: WARNING: Msg Length is zero");
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_SndEsmEmmDataReqMsg_ENUM, LNAS_NULL_PTR, 1);
        return ;
    }
    else if(ulLength > ESM_MIN_SND_MSG_LEN)
    {
        ulTmpLength = ulLength - ESM_MIN_SND_MSG_LEN ;
        pSmEmmDataReq = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(EMM_ESM_DATA_REQ_STRU) + ulTmpLength);
    }
    else/*如果长度小于ESM_MIN_SND_MSG_LEN，分配的空间等于ESM_MIN_SND_MSG_LEN*/
    {
        pSmEmmDataReq = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(EMM_ESM_DATA_REQ_STRU));
    }

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pSmEmmDataReq)
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEsmEmmDataReqMsg:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR1(NAS_ESM_SndEsmEmmDataReqMsg_ENUM, LNAS_NULL_PTR, 2);
        return ;
    }

    /*清空*/
    NAS_ESM_MEM_SET_S(  NAS_ESM_GET_MSG_ENTITY(pSmEmmDataReq),
                        NAS_ESM_GET_MSG_LENGTH(pSmEmmDataReq),
                        0,
                        NAS_ESM_GET_MSG_LENGTH(pSmEmmDataReq));

    /*填写空口消息头长度*/
    pSmEmmDataReq->stEsmMsg.ulEsmMsgSize = ulLength;

    /*将空口消息存放到EMM_ESM_DATA_REQ_STRU结构中*/
    /*lint -e669*/
    NAS_ESM_MEM_CPY_S(pSmEmmDataReq->stEsmMsg.aucEsmMsg, ulLength, pucSendMsg, ulLength);/*lint !e669 !e670*/
    /*lint +e669*/

    /*填写是否是紧急PDN连接请求类型*/
    pSmEmmDataReq->ulIsEmcType = ulIsEmcPdnType;

    /*填写OpId*/
    pSmEmmDataReq->ulOpId = ulOpId;

    /*填写消息头*/
    NAS_ESM_WRITE_EMM_MSG_HEAD(pSmEmmDataReq,ID_EMM_ESM_DATA_REQ);

    /*调用消息发送函数 */
    NAS_ESM_SND_MSG(pSmEmmDataReq);

}



/*****************************************************************************
 Function Name  : NAS_ESM_SndEsmEmmModifyReq()
 Description    : ESM模块发送ID_EMM_ESM_MODIFY_REQ消息
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.leili 00132387      2012-03-01  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_SndEsmEmmBearerModifyReq( VOS_UINT32 ulEpsId)
{
    EMM_ESM_BEARER_MODIFY_REQ_STRU  *pSmEmmBearModReq   = VOS_NULL_PTR;

    /*分配空间并检验分配是否成功*/
    pSmEmmBearModReq = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(EMM_ESM_BEARER_MODIFY_REQ_STRU));

    if ( VOS_NULL_PTR == pSmEmmBearModReq )
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEsmEmmBearerModifyReq:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEsmEmmBearerModifyReq_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*清空*/
    NAS_ESM_MEM_SET_S(  NAS_ESM_GET_MSG_ENTITY(pSmEmmBearModReq),
                        NAS_ESM_GET_MSG_LENGTH(pSmEmmBearModReq),
                        0,
                        NAS_ESM_GET_MSG_LENGTH(pSmEmmBearModReq));

    /*填写消息头*/
    NAS_ESM_WRITE_EMM_MSG_HEAD(pSmEmmBearModReq,ID_EMM_ESM_BEARER_MODIFY_REQ);

    pSmEmmBearModReq->ulEpsId = ulEpsId;

    /*调用消息发送函数 */
    NAS_ESM_SND_MSG(pSmEmmBearModReq);

}

/*****************************************************************************
 Function Name  : NAS_ESM_SndEsmEmmRelReqMsg()
 Description    : SM模块发送ID_EMM_ESM_REL_REQ函数
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.丁丽 00128736      2008-09-01  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_SndEsmEmmRelReqMsg( VOS_VOID )
{
    EMM_ESM_REL_REQ_STRU  *pSmEmmRelReq   = VOS_NULL_PTR;

    /*分配空间并检验分配是否成功*/
    pSmEmmRelReq = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(EMM_ESM_REL_REQ_STRU));

    if ( VOS_NULL_PTR == pSmEmmRelReq )
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEsmEmmRelReqMsg:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEsmEmmRelReqMsg_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*清空*/
    NAS_ESM_MEM_SET_S(  NAS_ESM_GET_MSG_ENTITY(pSmEmmRelReq),
                        NAS_ESM_GET_MSG_LENGTH(pSmEmmRelReq),
                        0,
                        NAS_ESM_GET_MSG_LENGTH(pSmEmmRelReq));

    /*填写消息头*/
    NAS_ESM_WRITE_EMM_MSG_HEAD(pSmEmmRelReq,ID_EMM_ESM_REL_REQ);

    /*调用消息发送函数 */
    NAS_ESM_SND_MSG(pSmEmmRelReq);

}


/*****************************************************************************
 Function Name   : NAS_ESM_ClearStateTable
 Description     : 收到Detach消息后通知APP(回复CNF类或IND类消息)，并清除状态表信息
 Input           : None
 Output          : None
 Return          : None

 History         :
    1.丁丽 00128736      2008-10-22  Draft Enact
    2.sunbing 49683      2009-02-05  Modify
*****************************************************************************/
VOS_VOID  NAS_ESM_ClearStateTable( VOS_UINT32 ulAppErrType, VOS_UINT32 ulKeepEmc )
{
    APP_ESM_MSG_TYPE_ENUM_UINT32        enAppMsgType        = NAS_ESM_NULL;
    VOS_UINT32                          ulStateTblId        = NAS_ESM_NULL;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG2("NAS_ESM_ClearStateTable is entered.", ulAppErrType, ulKeepEmc);
    TLPS_PRINT2LAYER_INFO2(NAS_ESM_ClearStateTable_ENUM, LNAS_ENTRY, ulAppErrType, ulKeepEmc);

    /*遍历状态表，如果有APP消息，则回复APP*/
    for( ulStateTblId = 0; ulStateTblId < NAS_ESM_MAX_STATETBL_NUM; ulStateTblId++ )
    {
        pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblId);

        /*如果允许保留紧急承载对应的动态表项，则跳过该项*/
        if ((NAS_ESM_BEARER_TYPE_EMERGENCY == pstStateAddr->enBearerCntxtType) &&
            (PS_TRUE == ulKeepEmc))
        {
            NAS_ESM_INFO_LOG("NAS_ESM_ClearStateTable:stop 3482");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_ClearStateTable_ENUM, 1);

            /* 如果是紧急PDN引起TAU或者SERVICE，失败后需要发起紧急注册的场景，
               需要停止3482定时器，否则紧急注册过程中3482可能超时 */
            NAS_ESM_TimerStop(ulStateTblId, TI_NAS_ESM_T3482);
            continue;
        }

        /* 如果此状态表存有APP消息记录，根据记录回复消息*/
        if( NAS_ESM_OP_TRUE == pstStateAddr->bitOpAppMsgRecord )
        {
            /*取出此承载中记录的APP消息类型*/
            enAppMsgType = pstStateAddr->stAppMsgRecord.enAppMsgType;

            /*根据所记录的消息类型回复消息*/
            switch( enAppMsgType )
            {
                /*如果是ID_APP_ESM_PDP_SETUP_REQ*/

                case ID_APP_ESM_PDP_SETUP_REQ:
                    /*向APP发送ID_APP_ESM_PDP_SETUP_CNF(失败)消息*/

                    NAS_ESM_SndEsmAppSdfSetupCnfFailMsg(    ulStateTblId, \
                                                            ulAppErrType);
                    break;

                case ID_APP_ESM_PDP_RELEASE_REQ:
                    if (APP_ERR_SM_SUSPENDED == ulAppErrType)
                    {
                        /*向APP发送ID_APP_ESM_PDP_RELEASE_CNF(失败)消息*/
                        NAS_ESM_SndEsmAppSdfRelCnfFailMsg(ulStateTblId, ulAppErrType);
                    }
                    else
                    {
                        /*向APP发送ID_APP_ESM_PDP_RELEASE_CNF(成功)消息*/
                        NAS_ESM_SndEsmAppSdfRelCnfSuccMsg(ulStateTblId);
                    }
                    break;

                case ID_APP_ESM_PDP_MODIFY_REQ:
                    /*向APP发送ID_APP_ESM_PDP_MODIFY_CNF(失败)消息*/
                    NAS_ESM_SndEsmAppSdfModCnfFailMsg(  ulStateTblId, \
                                                        ulAppErrType);
                    break;

                case ID_APP_ESM_NDISCONN_REQ:
                    /*向APP发送ID_APP_ESM_NDISCONN_CNF(失败)消息*/
                    NAS_ESM_LOG1("NAS_ESM_ClearStateTable:ERROR =", ulAppErrType);
                    TLPS_PRINT2LAYER_INFO1(NAS_ESM_ClearStateTable_ENUM, LNAS_ERROR, ulAppErrType);
                    NAS_ESM_SndEsmAppNdisConnCnfFailMsg(    ulStateTblId, \
                                                            ulAppErrType);
                    break;

                default:
                    break;
            }
        }

        NAS_ESM_RelStateTblResource(ulStateTblId);
    }

}

/*****************************************************************************
 Function Name   : NAS_ESM_IsUpSingnalPending
 Description     : 提供给MM调用，判断ESM是否有上行信令阻塞:检查如果存在流程正在等待
                   网侧响应，且该流程对应的定时器正在运行，超时次数小于(最大次数-1)
 Input           : VOS_VOID
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421   2011-2-12  Draft Enact

*****************************************************************************/
EMM_ESM_UP_SINGNAL_PENDING_ENUM_UINT32 NAS_ESM_IsUpSingnalPending( VOS_VOID )
{
    VOS_UINT32                          ulStateTblIndex = NAS_ESM_NULL;
    VOS_UINT32                          ulTimerMaxExpTimer = NAS_ESM_NULL;
    NAS_ESM_TIMER_STRU                 *pstTimerInfo = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG("NAS_ESM_IsUpSingnalPending is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_IsUpSingnalPending_ENUM, LNAS_ENTRY);

    /* 判断是否有流程在等待网侧响应*/
    for (ulStateTblIndex = 0; ulStateTblIndex < NAS_ESM_MAX_STATETBL_NUM; ulStateTblIndex++)
    {
        if (NAS_ESM_BEARER_PROC_TRANS_STATE_PENDING
                == NAS_ESM_GetProcTransState(ulStateTblIndex))
        {
            /* 判断该流程对应定时的超时次数*/
            pstTimerInfo = NAS_ESM_GetStateTblTimer(ulStateTblIndex);

            /* 判断流程对应定时器没有运行，提示警告*/
            if(VOS_NULL_PTR == pstTimerInfo->hTimer)
            {
                NAS_ESM_WARN_LOG("NAS_ESM_IsUpSingnalPending:warn: Timer not running.");
                TLPS_PRINT2LAYER_WARNING(NAS_ESM_IsUpSingnalPending_ENUM, LNAS_TIMER_STOP);
                continue;
            }

            /* 获取流程对应定时器的最大超时次数*/
            ulTimerMaxExpTimer = NAS_ESM_GetTimerMaxExpNum(pstTimerInfo->enPara);

            /* 如果超时次数小于最大次数减1，返回存在上行信令阻塞*/
            if((pstTimerInfo->ucExpireTimes) < (ulTimerMaxExpTimer-1))
            {
                NAS_ESM_INFO_LOG("NAS_ESM_IsUpSingnalPending:Uplink singnal pending.");
                TLPS_PRINT2LAYER_INFO(NAS_ESM_IsUpSingnalPending_ENUM, 1);
                return EMM_ESM_UP_SINGNAL_PENDING;
            }
            else
            {
                /*定时器超时次数已经超过最大次数减1，不认为上行信令阻塞*/
                NAS_ESM_INFO_LOG("NAS_ESM_IsUpSingnalPending:ExpireTimex >= Max-1");
                TLPS_PRINT2LAYER_INFO(NAS_ESM_IsUpSingnalPending_ENUM, 2);
                continue;
            }
        }
    }

    NAS_ESM_INFO_LOG("NAS_ESM_IsUpSingnalPending:no uplink signal pending.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_IsUpSingnalPending_ENUM, 3);
    return EMM_ESM_NO_UP_SINGNAL_PENDING;
}
/*****************************************************************************
 Function Name   : NAS_ESM_GetRegistCid
 Description     : 用于在UE发起注册时，获取适合的CID发起注册
 Input           : VOS_VOID
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.niuxiufan 00181501   2012-03-16   Draft Enact
    2.sunjitan 00193151    2015-06-16   Modify for 1XCL_MULTI_MODE_PHASEI
*****************************************************************************/
VOS_UINT32 NAS_ESM_GetRegistCid(VOS_VOID)
{
    VOS_UINT32                          ulCur;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara = VOS_NULL_PTR;

    #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    VOS_UINT32                          ulEhrpdCid;

    /* 如果存在记录的EHRPD承载信息，需要优先检查是否已经存在用于注册的CID */
    if (0 < NAS_ESM_GET_EHRPD_PDN_ENTITY_TOTAL_NUM())
    {
        if (NAS_ESM_SUCCESS == NAS_ESM_GetAttachCidInEhrpdEntity(&ulEhrpdCid))
        {
            return ulEhrpdCid;
        }
    }
    #endif

    /* 首先判断CID0是否为缺省承载 */
    pstSdfPara = NAS_ESM_GetSdfParaAddr(NAS_ESM_NULL);
    if (NAS_ESM_BEARER_TYPE_DEFAULT == pstSdfPara->enBearerCntxtType)
    {
       return NAS_ESM_NULL;
    }

    /* 从CID11-CID1寻找缺省承载类型的CID */
    for (ulCur = 1; ulCur < NAS_ESM_CID_NV_NUM; ulCur++ )
    {
       pstSdfPara = NAS_ESM_GetSdfParaAddr(ulCur);

       if (NAS_ESM_BEARER_TYPE_DEFAULT == pstSdfPara->enBearerCntxtType)
       {
           return ulCur;
       }
    }

    /* 如果之前的所有CID都不满足条件，则从CID12-CID20寻找缺省承载类型的CID */
    for (ulCur = NAS_ESM_CID_NV_NUM; ulCur < NAS_ESM_MAX_UE_CONTRUL_CID_NUM; ulCur++ )
    {
       pstSdfPara = NAS_ESM_GetSdfParaAddr(ulCur);

       if (NAS_ESM_BEARER_TYPE_DEFAULT == pstSdfPara->enBearerCntxtType)
       {
           return ulCur;
       }
    }

    return NAS_ESM_ILL_CID;
}

/*****************************************************************************
 Function Name   : NAS_ESM_ValidCidAttachBearerReest
 Description     : 用于注册承载重建的CID需要满足如下条件之一:
                     1. 该CID没有对应承载，且没有正在进行的其他动作
                     2. 该CID有对应承载，但承载状状态是未激活，

 Input           : ulCid    待判断的CID
 Output          : None
 Return          : 如果可以作为注册承载重建CID，则返回NAS_ESM_OP_TRUE；否则，
                   返回NAS_ESM_OP_FALSE

 History         :
    1.liuhua   00212067   2012-09-10  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_ESM_ValidCidAttachBearerReest(VOS_UINT32 ulCid)
{
    VOS_UINT32 ulEpsbId = 0;
    VOS_UINT32 ulStateTblId = 0;
    VOS_UINT32 ulResult = PS_FALSE;

    if (NAS_ESM_FAILURE == NAS_ESM_QueryEpsbCntxtTblByCid(ulCid, &ulEpsbId))
    {
        if (NAS_ESM_FAILURE == NAS_ESM_QueryStateTblIndexByCid(ulCid, &ulStateTblId))
        {
            ulResult = PS_TRUE;
        }
    }
    else
    {
        if (NAS_ESM_BEARER_STATE_INACTIVE == NAS_ESM_GetBearCntxtState(ulEpsbId))
        {
            ulResult = PS_TRUE;
        }
    }

    return ulResult;
}

/*****************************************************************************
 Function Name   : NAS_ESM_ReestablishAttachBearer
 Description     : 进行注册承载的重建
 Input           : VOS_VOID
 Output          : None
 Return          : VOS_VOID

 History         :
    1.liuhua   00212067   2012-09-06  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_ReestablishAttachBearer( VOS_VOID )
{
     VOS_UINT32                          ulPti               = NAS_ESM_NULL;
     VOS_UINT32                          ulRegCId            = NAS_ESM_NULL;
     VOS_UINT32                          ulStateTblId        = NAS_ESM_NULL;
     VOS_UINT32                          ulCur               = NAS_ESM_NULL;
     VOS_UINT32                          ulSdfNum            = NAS_ESM_NULL;
     NAS_ESM_SDF_PARA_STRU              *pstSdfPara          = VOS_NULL_PTR;
     APP_ESM_SDF_PARA_STRU              *pstAppSdfPara       = VOS_NULL_PTR;
     NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;
     NAS_ESM_ENCODE_INFO_STRU            stEncodeInfo;
     NAS_ESM_PDP_MANAGE_INFO_STRU       *pEpsbManageInfo     = VOS_NULL_PTR;


    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_ReestablishAttachBearer is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_ReestablishAttachBearer_ENUM, LNAS_ENTRY);

    if (NAS_ESM_L_MODE_STATUS_NORMAL != NAS_ESM_GetLModeStatus())
    {
        NAS_ESM_WARN_LOG("NAS_ESM_ReestablishAttachBearer: L mode is already suspended!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ReestablishAttachBearer_ENUM, LNAS_EMM_LTE_SUSPEND);
        return;
    }

    if (NAS_ESM_PS_REGISTER_STATUS_ATTACHED != NAS_ESM_GetEmmStatus())
    {
        NAS_ESM_NORM_LOG("NAS_ESM_ReestablishAttachBearer: ESM status is not ATTACHED !");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_ReestablishAttachBearer_ENUM, ESM_STATUS_ERROR);
        return;
    }

    pstAppSdfPara = NAS_ESM_MEM_ALLOC(sizeof(APP_ESM_SDF_PARA_STRU));

    if (VOS_NULL_PTR == pstAppSdfPara)
    {
         /*打印不合法信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_ReestablishAttachBearer:ERROR: Mem alloc fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_ReestablishAttachBearer_ENUM, LNAS_NULL_PTR);
        return;
    }

    /* 逐一获取12套NV参数 */
    for (ulCur = NAS_ESM_MIN_CID; ulCur < NAS_ESM_CID_NV_NUM; ulCur++)
    {
        pstAppSdfPara->ulCId = ulCur;
        if (APP_FAILURE == NAS_ESM_GetSdfPara(&ulSdfNum, pstAppSdfPara))
        {
            continue;
        }

        pstSdfPara = NAS_ESM_GetSdfParaAddr(ulCur);

        NAS_ESM_MEM_CPY_S(  pstSdfPara,
                            sizeof(APP_ESM_SDF_PARA_STRU),
                            pstAppSdfPara,
                            sizeof(APP_ESM_SDF_PARA_STRU));
    }

    NAS_ESM_MEM_FREE(pstAppSdfPara);

    /* 从APP获取承载管理模式参数，则采取自动接受模式 */
    pEpsbManageInfo = NAS_ESM_GetBearerManageInfoAddr();
    if (APP_FAILURE == NAS_ESM_GetPdpManageInfo(pEpsbManageInfo))
    {
        /*打印警告信息*/
        NAS_ESM_WARN_LOG("NAS_ESM_ReestablishAttachBearer:WARN: Fail to get PDP Manage Info from APP!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ReestablishAttachBearer_ENUM, 1);
        pEpsbManageInfo->enMode = APP_ESM_BEARER_MANAGE_MODE_AUTO;
        pEpsbManageInfo->enType = APP_ESM_BEARER_MANAGE_TYPE_ACCEPT;
    }
    /* 获取用于注册的CID，优先级顺序由高到低为CID0 > CID1-CID11 > CID12-CID20 */
    /* 除了个别运营商特殊需求, 需要GU NV项CID0初始化为专有类型，CID11为缺省类型*/
    ulRegCId = NAS_ESM_GetRegistCid();
    NAS_ESM_SndOmRegCidInfo(ulRegCId);
    if (NAS_ESM_ILL_CID == ulRegCId)
    {
        /*打印不合法信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_ReestablishAttachBearer: There is no default bearer type sdf");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_ReestablishAttachBearer_ENUM, 2);
        return ;
    }

    NAS_ESM_LOG1("NAS_ESM_ReestablishAttachBearer:The cid of the found sdf is :", ulRegCId);
    TLPS_PRINT2LAYER_INFO1(NAS_ESM_ReestablishAttachBearer_ENUM, ESM_CID_IS, ulRegCId);

    /* 检查CID是否符合注册承载重建的条件 */
    if (PS_FALSE == NAS_ESM_ValidCidAttachBearerReest(ulRegCId))
    {
        NAS_ESM_ERR_LOG("NAS_ESM_ReestablishAttachBearer: Invalid CID");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_ReestablishAttachBearer_ENUM, ESM_CID_ERROR);
        return;
    }

    /*在动态表中，获取过程标识*/
    if(NAS_ESM_SUCCESS != NAS_ESM_GetStateTblIndexByCid(NAS_ESM_ATTACH_CID, &ulStateTblId))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_ReestablishAttachBearer:WARNING:insufficient resource!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ReestablishAttachBearer_ENUM, 4);
        return ;
    }

    /*将查询到的ulRegCId参数拷贝到CID0中，发起注册*/
    pstSdfPara = NAS_ESM_GetSdfParaAddr(NAS_ESM_ATTACH_CID);

    NAS_ESM_MEM_CPY_S(  pstSdfPara,
                        sizeof(NAS_ESM_SDF_PARA_STRU),
                        NAS_ESM_GetSdfParaAddr(ulRegCId),
                        sizeof(NAS_ESM_SDF_PARA_STRU));

    /*设置初始状态*/
    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblId);
    pstStateAddr->enBearerCntxtState = NAS_ESM_BEARER_STATE_INACTIVE;
    pstStateAddr->enBearerCntxtType  = NAS_ESM_BEARER_TYPE_DEFAULT;

    /*分配PTI,并存存储到承载信息中*/
    NAS_ESM_AssignPTI(&ulPti);
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
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_ReestablishAttachBearer:ERROR:EncodePdnConReqMsg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_ReestablishAttachBearer_ENUM, LNAS_FAIL);

        NAS_ESM_RelStateTblResource(ulStateTblId);
        return ;
    }

    /*记录空口消息类型*/
    pstStateAddr->bitOpNwMsgRecord = NAS_ESM_OP_TRUE;
    pstStateAddr->stNwMsgRecord.enEsmCnMsgType = NAS_ESMCN_MSG_TYPE_PDN_CONNECT_REQ;
    pstStateAddr->stNwMsgRecord.ucIsEmcPdnReq = PS_FALSE;
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
    NAS_ESM_TimerStart(ulStateTblId,TI_NAS_ESM_T3482);

    /*转换状态*/
    NAS_ESM_SetProcTransState(ulStateTblId, NAS_ESM_BEARER_PROC_TRANS_STATE_PENDING);
}

/*****************************************************************************
 Function Name   : NAS_ESM_RcvEsmEmmDeactAllNonEmcBearerInd
 Description     : 接收到EMM的释放所有非紧急PDN连接的处理
 Input           : None
 Output          : None
 Return          : None
 History         :
    1.liuhua    00212067       2012-10-25  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_RcvEsmEmmDeactAllNonEmcBearerInd(VOS_VOID)
{
    NAS_ESM_INFO_LOG("NAS_ESM_RcvEsmEmmDeactAllNonEmcBearerInd: enter");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_RcvEsmEmmDeactAllNonEmcBearerInd_ENUM, LNAS_ENTRY);

    if (PS_TRUE == NAS_ESM_HasExistedEmergencyPdn())
    {
        NAS_ESM_INFO_LOG("NAS_ESM_RcvEsmEmmDeactAllNonEmcBearerInd: existed emergency PDN");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_RcvEsmEmmDeactAllNonEmcBearerInd_ENUM, 1);

        /*如果当前有已经建立的紧急PDN连接，则立即释放所有非紧急PDN连接*/
        NAS_ESM_DeactAllNonEmcPdn();
    }
    else if (PS_TRUE == NAS_ESM_HasEstingEmergencyPdn())
    {
        NAS_ESM_INFO_LOG("NAS_ESM_RcvEsmEmmDeactAllNonEmcBearerInd: esting emergency PDN");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_RcvEsmEmmDeactAllNonEmcBearerInd_ENUM, 2);

        /*如果当前有正在建立的紧急PDN连接，则延迟释放所有非紧急PDN连接*/
        NAS_ESM_TimerStart(0, TI_NAS_ESM_REL_NON_EMC_BEARER);
    }
    else
    {   /*如果当前没有紧急PDN，则不做处理*/
        NAS_ESM_INFO_LOG("NAS_ESM_RcvEsmEmmDeactAllNonEmcBearerInd: no emergency PDN");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_RcvEsmEmmDeactAllNonEmcBearerInd_ENUM, 3);
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_ESM_RcvEsmEmmStartNotifyInd
 Description     : 接收到EMM的开机消息的处理
 Input           : None
 Output          : None
 Return          : None
 History         :
    1.sunjitan 00193151    2015-01-15  Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_RcvEsmEmmStartNotifyInd(VOS_VOID)
{
    NAS_BACKOFF_INIT_INFO_STRU          stInitPara;

    NAS_ESM_MEM_SET_S(  &stInitPara,
                        sizeof(NAS_BACKOFF_INIT_INFO_STRU),
                        0,
                        sizeof(NAS_BACKOFF_INIT_INFO_STRU));

    if(NAS_ESM_SUCCESS != NAS_ESM_ReadUsimBackOffRpmPdpPara())
    {
        /* 读卡失败，直接初始化BackOff算法 */
        stInitPara.bitOpSimFxFlag = NAS_ESM_OP_FALSE;
        NAS_BACKOFF_OperateInit(&stInitPara);
    }
    else
    {
        /* 读卡成功，启动定时器等卡回复消息,启动函数第一个入参不使用，填0 */
        NAS_ESM_TimerStart(0, TI_NAS_ESM_BACKOFF_WAIT_USIM_CNF);
    }

    #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    /* 开机，EHRPD实体初始化 */
    NAS_ESM_InitEhrpdEntity();
    #endif

    return;
}

/*****************************************************************************
 Function Name   : NAS_ESM_RcvEsmEmmPlmnChangeInd
 Description     : 接收到EMM的PLMN变更消息的处理
 Input           : None
 Output          : None
 Return          : None
 History         :
    1.sunjitan 00193151    2015-01-15  Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_RcvEsmEmmPlmnChangeInd(VOS_VOID)
{
    NAS_BACKOFF_RESET_CAUSE_ENUM_UINT32 enResetCause;

    NAS_ESM_INFO_LOG("NAS_ESM_RcvEsmEmmPlmnChangeInd: enter");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_RcvEsmEmmPlmnChangeInd_ENUM, LNAS_ENTRY);

    enResetCause = NAS_BACKOFF_RESET_CAUSE_PLMN_CHANGE;

    /* 复位BACKOFF算法 */
    NAS_BACKOFF_OperateReset(NAS_BACKOFF_NETRAT_LTE, &enResetCause);
    return;
}

/*****************************************************************************
 Function Name   : NAS_ESM_RcvEsmEmmStopNotifyInd
 Description     : 接收到EMM的关机消息的处理
 Input           : None
 Output          : None
 Return          : None
 History         :
    1.wangchen 00209181     2014-09-05  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_RcvEsmEmmStopNotifyInd(VOS_VOID)
{
    NAS_BACKOFF_RESET_CAUSE_ENUM_UINT32 enResetCause;

    NAS_ESM_INFO_LOG("NAS_ESM_RcvEsmEmmStopNotifyInd: enter");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_RcvEsmEmmStopNotifyInd_ENUM, LNAS_ENTRY);

    enResetCause = NAS_BACKOFF_RESET_CAUSE_SWITCH_OFF;

    /* 复位BACKOFF算法 */
    NAS_BACKOFF_OperateReset(NAS_BACKOFF_NETRAT_LTE, &enResetCause);

    /* 清空被拒原因值#50和#51的列表 */
    NAS_ESM_PdnRejListDestroy(pg_stNasEsmEntity->pstPdnRej50Info);
    NAS_ESM_PdnRejListDestroy(pg_stNasEsmEntity->pstPdnRej51Info);
    NAS_ESM_PdnRejListDestroy(pg_stNasEsmEntity->pstPdnRej66Info);

    pg_stNasEsmEntity->pstPdnRej50Info =  VOS_NULL_PTR;
    pg_stNasEsmEntity->pstPdnRej51Info =  VOS_NULL_PTR;
    pg_stNasEsmEntity->pstPdnRej66Info =  VOS_NULL_PTR;

    #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    /* 关机，清除所有EHRPD承载记录 */
    NAS_ESM_ClearAllEhrpdPdnInfoProc();

    /* 通知RABM清除所有承载资源，包括EHRPD和LTE的承载 */
    NAS_ESM_SndEsmRabmClearClBearerNotifyMsg();
    #endif

    return;
}

VOS_VOID NAS_ESM_SndEsmEmmClrEsmProcResNtyMsg(VOS_UINT32 ulOpId, VOS_UINT8 ucIsEmcPdnType)
{
    EMM_ESM_CLR_ESM_PROC_RES_NOTIFY_STRU *pSmEmmNotify      = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG2("NAS_ESM_SndEsmEmmClrEsmProcResNtyMsg: enter", ulOpId, ucIsEmcPdnType);
    TLPS_PRINT2LAYER_INFO2(NAS_ESM_SndEsmEmmClrEsmProcResNtyMsg_ENUM, LNAS_ENTRY, ulOpId, ucIsEmcPdnType);

    /*根据空口消息的长度分配空间*/
    pSmEmmNotify= (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(EMM_ESM_CLR_ESM_PROC_RES_NOTIFY_STRU));

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pSmEmmNotify)
    {
         /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEsmEmmClrEsmProcResNtyMsg:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEsmEmmClrEsmProcResNtyMsg_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*清空*/
    NAS_ESM_MEM_SET_S(  NAS_ESM_GET_MSG_ENTITY(pSmEmmNotify),
                        NAS_ESM_GET_MSG_LENGTH(pSmEmmNotify),
                        0,
                        NAS_ESM_GET_MSG_LENGTH(pSmEmmNotify));

    /*填写是否是紧急PDN连接请求类型*/
    pSmEmmNotify->ulIsEmcType = ucIsEmcPdnType;

    /*填写OpId*/
    pSmEmmNotify->ulOpId = ulOpId;

    /*填写消息头*/
    NAS_ESM_WRITE_EMM_MSG_HEAD(pSmEmmNotify, ID_EMM_ESM_CLR_ESM_PROC_RES_NOTIFY);

    /*调用消息发送函数 */
    NAS_ESM_SND_MSG(pSmEmmNotify);
}
/*lint +e961*/
/*lint +e960*/

#if (FEATURE_ON == FEATURE_PTM)
/*****************************************************************************
Function Name   :  NAS_ESM_CnCauseProc
Description     :  将内部网络拒绝原因转换成Lnas error log对应的枚举值
Input           :  ucCauseCode 表示网络拒绝原因

Output          :  输出一个Lnas error log的枚举变量
Return          :

History         :
1.lifuxin 00253982         2013-11-07  新增文件
2.lifuxin 00253982         2014-12-29  errlog重构
*****************************************************************************/
ESM_OM_ERRLOG_ID_ENUM_UINT16  NAS_ESM_CnCauseProc(VOS_UINT8 ucCnCause)
{
    ESM_OM_ERRLOG_ID_ENUM_UINT16   ulErrId = 0;
    VOS_UINT32 i;

    NAS_ESM_INFO_LOG("NAS_ESM_CnCauseProc!");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_CnCauseProc_ENUM, LNAS_ENTRY);

    for(i = 0; i < g_astEsmErrlogErrNum; i++)
    {
        if(ucCnCause == g_astEsmErrlogErrNoMap[i].ulEsmCnCasue)
        {
            ulErrId = g_astEsmErrlogErrNoMap[i].ulEsmErrId;
            break;
        }
    }
    if(g_astEsmErrlogErrNum == i)
    {
            ulErrId = ESM_OM_ERRLOG_CAUSE_OTHERS;
    }

    return ulErrId;
}

/*****************************************************************************
 Function Name   : NAS_ESM_SndEsmEmmSaveErrlogMsg
 Description     : ESM发送给EMM的ERRLOG信息
 Input           :

 Output          : None
 Return          : None
 History         :
    1.lifuxin    00253982       2014-12-30  Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_SndEsmErrlogToEmm(
                 VOS_VOID     *pstEsmErrRslt,  VOS_UINT32   ulEsmErrLength)
{
    EMM_ESM_SAVE_ERRLOG_IND_STRU        *pstSaveEsmErrMsg = NAS_ESM_NULL;
    VOS_UINT32                          ulLength          = 0;

    NAS_ESM_NORM_LOG("NAS_ESM_SndEsmErrlogToEmm!!!");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_SndEsmErrlogToEmm_ENUM, LNAS_ENTRY);

    /*根据消息的长度分配空间*/
    ulLength = sizeof(EMM_ESM_SAVE_ERRLOG_IND_STRU) + ulEsmErrLength - 4;

    pstSaveEsmErrMsg = (VOS_VOID*)NAS_ESM_ALLOC_MSG(ulLength);
    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pstSaveEsmErrMsg)
    {
         /*打印异常信息*/
         NAS_ESM_ERR_LOG("NAS_ESM_SndEsmErrlogToEmm:ERROR:Alloc Msg fail!");
         TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEsmErrlogToEmm_ENUM, LNAS_NULL_PTR);
         return ;
    }

    /*清空*/
    NAS_ESM_MEM_SET_S(pstSaveEsmErrMsg, ulLength, 0, ulLength);

    /*填写实际的esm errlog消息头长度*/
    pstSaveEsmErrMsg->stEmmEsmErrlog.ulEsmMsgSize = ulEsmErrLength;

    /*填写实际要写入缓冲区的esm errlog数据*/
    NAS_ESM_MEM_CPY_S(  pstSaveEsmErrMsg->stEmmEsmErrlog.aucEsmMsg,
                        ulEsmErrLength,
                        pstEsmErrRslt,
                        ulEsmErrLength);

    /*填写消息头*/
    NAS_ESM_WRITE_EMM_MSG_HEAD(pstSaveEsmErrMsg, ID_EMM_ESM_SAVE_ERRLOG_IND);

    /*调用消息发送函数 */
    NAS_ESM_SND_MSG(pstSaveEsmErrMsg);
}

/*****************************************************************************
 Function Name   : NAS_ESM_PdnConRejRecord
 Description     : 记录PdnConRej fail消息
 Input           :

 Output          : None
 Return          : None
 History         :
    1.lifuxin    00253982       2014-12-30  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_ESM_PdnConFailRecord(
        const EMM_ESM_INTRA_DATA_IND_STRU   *pstEmmEsmDataInd,
        ESM_OM_ERRLOG_TIMEOUT_ENUM_UINT16   enErrEsmTimeOut)
{
    ESM_ERR_INFO_PDN_CONN_REJ_RESULT_EVENT_STRU            stEsmPdnConnFailRslt;
    VOS_UINT32                                              ulLength;
    VOS_UINT16                                              usLevel;
    VOS_UINT32                                              ulIsLogRecord;

    NAS_ESM_NORM_LOG("NAS_ESM_PdnConFailRecord!!");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_PdnConRejRecord_ENUM, LNAS_ENTRY);


    /* 查询对应Alarm Id是否需要记录异常信息 */
    usLevel       = NAS_EMM_GetErrLogAlmLevel(LNAS_OM_ERRLOG_ALM_ID_ESM_PDN_CONN_FAIL);
    ulIsLogRecord = NAS_EMM_IsErrLogNeedRecord(usLevel);

    /* 模块异常不需要记录或异常原因值不需要记录时，不保存异常信息 */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(ESM_ERR_INFO_PDN_CONN_REJ_RESULT_EVENT_STRU);

    NAS_ESM_MEM_SET_S(&stEsmPdnConnFailRslt, ulLength, 0x00, ulLength);

    /*填充esm fail异常场景头*/
    NAS_ESM_COMM_BULID_ERRLOG_HEADER_INFO(&stEsmPdnConnFailRslt.stHeader,
                                   VOS_GetModemIDFromPid(PS_PID_ESM),
                                   LNAS_OM_ERRLOG_ALM_ID_ESM_PDN_CONN_FAIL,
                                   usLevel,
                                   VOS_GetSlice(),
                                   (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    if(VOS_NULL_PTR != pstEmmEsmDataInd)
    {
        stEsmPdnConnFailRslt.enFailCause =
                    NAS_ESM_CnCauseProc(pstEmmEsmDataInd->stEsmNwMsgIE.enEsmCau);
    }
    stEsmPdnConnFailRslt.enEsmTimeout = enErrEsmTimeOut;

    (VOS_VOID)NAS_LMM_GetPositionInfo(&(stEsmPdnConnFailRslt.stPositionInfo));

    /*发送ESM errlog信息给EMM，为防止并发导致存储log失败，由EMM保存*/
    NAS_ESM_SndEsmErrlogToEmm(&stEsmPdnConnFailRslt, ulLength);
}

/*****************************************************************************
 Function Name   : NAS_ESM_PdnDisconRejRecord
 Description     : 记录PdnDisConRej fail消息
 Input           :

 Output          : None
 Return          : None
 History         :
    1.lifuxin    00253982       2014-12-30  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_ESM_PdnDisconFailRecord(
        const EMM_ESM_INTRA_DATA_IND_STRU   *pstEmmEsmDataInd,
        ESM_OM_ERRLOG_TIMEOUT_ENUM_UINT16   enErrEsmTimeOut)
{
    ESM_ERR_INFO_PDN_DISCONN_REJ_RESULT_EVENT_STRU         stEsmPdnDisconFailRslt;
    VOS_UINT32                                              ulLength;
    VOS_UINT16                                              usLevel;
    VOS_UINT32                                              ulIsLogRecord;


    NAS_ESM_NORM_LOG("NAS_ESM_PdnDisconFailRecord!!");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_PdnDisconRejRecord_ENUM, LNAS_ENTRY);


    /* 查询对应Alarm Id是否需要记录异常信息 */
    usLevel       = NAS_EMM_GetErrLogAlmLevel(LNAS_OM_ERRLOG_ALM_ID_ESM_PDN_DISCONN_FAIL);
    ulIsLogRecord = NAS_EMM_IsErrLogNeedRecord(usLevel);

    /* 模块异常不需要记录或异常原因值不需要记录时，不保存异常信息 */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(ESM_ERR_INFO_PDN_DISCONN_REJ_RESULT_EVENT_STRU);

    NAS_ESM_MEM_SET_S(&stEsmPdnDisconFailRslt, ulLength, 0x00, ulLength);

    /*填充esm fail异常场景头*/
    NAS_ESM_COMM_BULID_ERRLOG_HEADER_INFO(&stEsmPdnDisconFailRslt.stHeader,
                                   VOS_GetModemIDFromPid(PS_PID_ESM),
                                   LNAS_OM_ERRLOG_ALM_ID_ESM_PDN_DISCONN_FAIL,
                                   usLevel,
                                   VOS_GetSlice(),
                                   (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    if(VOS_NULL_PTR != pstEmmEsmDataInd)
    {
        stEsmPdnDisconFailRslt.enFailCause =
                        NAS_ESM_CnCauseProc(pstEmmEsmDataInd->stEsmNwMsgIE.enEsmCau);
    }
    stEsmPdnDisconFailRslt.enEsmTimeout = enErrEsmTimeOut;

    (VOS_VOID)NAS_LMM_GetPositionInfo(&(stEsmPdnDisconFailRslt.stPositionInfo));

    /*发送ESM errlog信息给EMM，为防止并发导致存储log失败，由EMM保存*/
     NAS_ESM_SndEsmErrlogToEmm(&stEsmPdnDisconFailRslt, ulLength);
}

/*****************************************************************************
 Function Name   : NAS_ESM_ResModRejRecord
 Description     : 记录ResModRej fail消息
 Input           :

 Output          : None
 Return          : None
 History         :
    1.lifuxin    00253982       2014-12-30  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_ESM_ResModFailRecord(
        const EMM_ESM_INTRA_DATA_IND_STRU   *pstEmmEsmDataInd,
        ESM_OM_ERRLOG_TIMEOUT_ENUM_UINT16   enErrEsmTimeOut)
{
    ESM_ERR_INFO_RES_MOD_REJ_RESULT_EVENT_STRU             stEsmResModFailRslt;
    VOS_UINT32                                              ulLength;
    VOS_UINT16                                              usLevel;
    VOS_UINT32                                              ulIsLogRecord;

    NAS_ESM_NORM_LOG("NAS_ESM_ResModFailRecord!!");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_ResModRejRecord_ENUM, LNAS_ENTRY);

    /* 查询对应Alarm Id是否需要记录异常信息 */
    usLevel       = NAS_EMM_GetErrLogAlmLevel(LNAS_OM_ERRLOG_ALM_ID_ESM_RES_MOD_FAIL);
    ulIsLogRecord = NAS_EMM_IsErrLogNeedRecord(usLevel);

    /* 模块异常不需要记录或异常原因值不需要记录时，不保存异常信息 */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(ESM_ERR_INFO_RES_MOD_REJ_RESULT_EVENT_STRU);

    NAS_ESM_MEM_SET_S(&stEsmResModFailRslt, ulLength, 0x00, ulLength);

    /*填充esm fail异常场景头*/
    NAS_ESM_COMM_BULID_ERRLOG_HEADER_INFO(&stEsmResModFailRslt.stHeader,
                                   VOS_GetModemIDFromPid(PS_PID_ESM),
                                   LNAS_OM_ERRLOG_ALM_ID_ESM_RES_MOD_FAIL,
                                   usLevel,
                                   VOS_GetSlice(),
                                   (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    if(VOS_NULL_PTR != pstEmmEsmDataInd)
    {
        stEsmResModFailRslt.enFailCause =
                        NAS_ESM_CnCauseProc(pstEmmEsmDataInd->stEsmNwMsgIE.enEsmCau);
    }
    stEsmResModFailRslt.enEsmTimeout = enErrEsmTimeOut;

    (VOS_VOID)NAS_LMM_GetPositionInfo(&(stEsmResModFailRslt.stPositionInfo));

    /*发送ESM errlog信息给EMM，为防止并发导致存储log失败，由EMM保存*/
    NAS_ESM_SndEsmErrlogToEmm(&stEsmResModFailRslt, ulLength);
}

/*****************************************************************************
 Function Name   : NAS_ESM_ResAllocFailRecord
 Description     : 记录ResAllocRej fail消息
 Input           :

 Output          : None
 Return          : None
 History         :
    1.lifuxin    00253982       2014-12-30  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_ESM_ResAllocFailRecord(
        const EMM_ESM_INTRA_DATA_IND_STRU   *pstEmmEsmDataInd,
        ESM_OM_ERRLOG_TIMEOUT_ENUM_UINT16   enErrEsmTimeOut)
{
    ESM_ERR_INFO_RES_ALLOC_REJ_RESULT_EVENT_STRU           stEsmResAllocFailRslt;
    VOS_UINT32                                              ulLength;
    VOS_UINT16                                              usLevel;
    VOS_UINT32                                              ulIsLogRecord;

    NAS_ESM_NORM_LOG("NAS_ESM_ResAllocFailRecord!!");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_ResAllocRejRecord_ENUM, LNAS_ENTRY);

    /* 查询对应Alarm Id是否需要记录异常信息 */
    usLevel       = NAS_EMM_GetErrLogAlmLevel(LNAS_OM_ERRLOG_ALM_ID_ESM_RES_ALLOC_FAIL);
    ulIsLogRecord = NAS_EMM_IsErrLogNeedRecord(usLevel);

    /* 模块异常不需要记录或异常原因值不需要记录时，不保存异常信息 */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(ESM_ERR_INFO_RES_ALLOC_REJ_RESULT_EVENT_STRU);

    NAS_ESM_MEM_SET_S(&stEsmResAllocFailRslt, ulLength, 0x00, ulLength);

    /*填充esm fail异常场景头*/
    NAS_ESM_COMM_BULID_ERRLOG_HEADER_INFO(&stEsmResAllocFailRslt.stHeader,
                                   VOS_GetModemIDFromPid(PS_PID_ESM),
                                   LNAS_OM_ERRLOG_ALM_ID_ESM_RES_ALLOC_FAIL,
                                   usLevel,
                                   VOS_GetSlice(),
                                   (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    if(VOS_NULL_PTR != pstEmmEsmDataInd)
    {
        stEsmResAllocFailRslt.enFailCause =
                        NAS_ESM_CnCauseProc(pstEmmEsmDataInd->stEsmNwMsgIE.enEsmCau);
    }
    stEsmResAllocFailRslt.enEsmTimeout = enErrEsmTimeOut;

    (VOS_VOID)NAS_LMM_GetPositionInfo(&(stEsmResAllocFailRslt.stPositionInfo));

    /*发送ESM errlog信息给EMM，为防止并发导致存储log失败，由EMM保存*/
    NAS_ESM_SndEsmErrlogToEmm(&stEsmResAllocFailRslt, ulLength);
}
#endif

/*****************************************************************************
 Function Name   : NAS_ESM_FindMsgInDataReqBuffer
 Description     : 根据EMM_ESM_DATA_CNF携带的EmmEsmOpId查找在缓存消息内存中对应的消息
 Input           : None
 Output          : None
 Return          : VOS_UINT32
 History         : lifuxin  00253982   2014-07-02  Draft Enac
*****************************************************************************/
/*lint -e960*/
NAS_ESM_STATE_INFO_STRU* NAS_ESM_FindMsgInStateTable(VOS_UINT32 ulEmmEsmOpId)
{
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          ulRslt = VOS_ERR;
    NAS_ESM_STATE_INFO_STRU             *pstStatTblnfo = VOS_NULL_PTR;

    /*获取动态表的首地址*/
    pstStatTblnfo = NAS_ESM_GetStateTblAddr(0);

    for (ulIndex = 0; ulIndex < NAS_ESM_MAX_STATETBL_NUM; ulIndex++)
    {
        if (ulEmmEsmOpId == pstStatTblnfo->stNwMsgRecord.ulOpId)
        {
            ulRslt = VOS_OK;
            break;
        }
        else
        {
            pstStatTblnfo++;
        }
    }

    if (VOS_ERR == ulRslt)
    {
        return VOS_NULL_PTR;
    }

    return pstStatTblnfo;
}
/*lint +e960*/

/*****************************************************************************
 Function Name   : NAS_ESM_IsExistAllFailStateTable
 Description     : 遍历动态表，判断除了当前承载之外的其他承载的状态
 Input           : ulEmmEsmOpId--当前承载的OpId

 Output          : None
 Return          :
#define ESM_BEARER_STATUS_AT_LEAST_ONE_BEAER_RUNING     (1)
#define ESM_BEARER_STATUS_BESIDE_RUNING                 (2)

 History         :
    1.lifuxin    00253982       2014-07-03  Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_ESM_IsExistAllFailStateTable(VOS_VOID)
{
    NAS_ESM_STATE_INFO_STRU             *pstStateTblInfo = NAS_ESM_NULL;
    VOS_UINT32                          ulStateTblIndex  = 0;
    VOS_UINT32                          ulHaveOneSuccOrSendingFlag = VOS_FALSE;

    for(ulStateTblIndex = 0; ulStateTblIndex < NAS_ESM_MAX_STATETBL_NUM; ulStateTblIndex++)
    {
        pstStateTblInfo = NAS_ESM_GetStateTblAddr(ulStateTblIndex);
        if((NAS_ESM_BEARER_DATA_CNF_SENDING == pstStateTblInfo->enEsmBearerDataCnf)
            || (NAS_ESM_BEARER_DATA_CNF_SUCC == pstStateTblInfo->enEsmBearerDataCnf))
        {
            ulHaveOneSuccOrSendingFlag = VOS_TRUE;
            break;
        }
    }

    if(VOS_TRUE == ulHaveOneSuccOrSendingFlag)
    {
        return ESM_BEARER_STATUS_AT_LEAST_ONE_BEAER_RUNING;
    }
    else
    {
        return ESM_BEARER_STATUS_BESIDE_RUNING;
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_RcvEsmEmmDataCnf
 Description     : 收到EMM_ESM_DATA_CNF的处理
 Input           : pRcvmsg--收到的DATA CNF消息

 Output          : None
 Return          : None
 History         :
    1.lifuxin    00253982       2014-07-03  Draft Enact
*****************************************************************************/
/*lint -e961*/
VOS_VOID NAS_ESM_RcvEsmEmmDataCnf(const EMM_ESM_DATA_CNF_STRU   *pEmmEsmDataCnfMsg)
{
    NAS_ESM_STATE_INFO_STRU             *pstStateTblInfo = NAS_ESM_NULL;

    /*检查入参*/
    if(VOS_NULL == pEmmEsmDataCnfMsg)
    {
        NAS_ESM_ERR_LOG("NAS_ESM_RcvEsmEmmDataCnf(ERR): Input is NULL!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_RcvEsmEmmDataCnf_ENUM, LNAS_NULL_PTR);
        return;
    }

    NAS_ESM_LOG2("NAS_ESM_RcvEsmEmmDataCnf: enBearerDataCnf, EmmEsmOpId:",
                    pEmmEsmDataCnfMsg->enDataCnfRst, pEmmEsmDataCnfMsg->ulEsmEmmOpId);
    TLPS_PRINT2LAYER_INFO2(NAS_ESM_RcvEsmEmmDataCnf_ENUM, 1, pEmmEsmDataCnfMsg->enDataCnfRst, pEmmEsmDataCnfMsg->ulEsmEmmOpId);

    /*根据Emm带过来的OpId去查找对应的动态表项*/
    pstStateTblInfo = NAS_ESM_FindMsgInStateTable(pEmmEsmDataCnfMsg->ulEsmEmmOpId);

    /*更新承载状态*/
    switch(pEmmEsmDataCnfMsg->enDataCnfRst)
    {
        case  EMM_ESM_SEND_RSLT_SUCCESS:

              /* 原DSDS只关注PDN REQ，因此存在动态表才处理，EHRPD承载相反，只关注激活承载ACP，必然找不到动态表 */
              if (NAS_ESM_NULL != pstStateTblInfo)
              {
                  #if (FEATURE_ON == FEATURE_DSDS)
                  pstStateTblInfo->enEsmBearerDataCnf = NAS_ESM_BEARER_DATA_CNF_SUCC;
                  #endif
              }
              else
              {
                  #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
                  /* 发送成功，EHRPD实体针对此OPID可能有特殊处理 */
                  NAS_ESM_EhrpdEntityProcEmmSendDataReqSucc(pEmmEsmDataCnfMsg->ulEsmEmmOpId);
                  #endif
              }

              break;
        case  EMM_ESM_SEND_RSLT_EMM_DISCARD:
        case  EMM_ESM_SEND_RSLT_FAILURE_HO:
        case  EMM_ESM_SEND_RSLT_FAILURE_CONN_REL:
        case  EMM_ESM_SEND_RSLT_FAILURE_CTRL_NOT_CONN:
        case  EMM_ESM_SEND_RSLT_FAILURE_TXN:
        case  EMM_ESM_SEND_RSLT_FAILURE_RLF:
        case  EMM_ESM_SEND_RSLT_NORF:

              /* 原DSDS只关注PDN REQ，因此存在动态表才处理，EHRPD承载相反，只关注激活承载ACP，必然找不到动态表 */
              if (NAS_ESM_NULL != pstStateTblInfo)
              {
                  #if (FEATURE_ON == FEATURE_DSDS)
                  pstStateTblInfo->enEsmBearerDataCnf = NAS_ESM_BEARER_DATA_CNF_FAIL;
                  #endif
              }
              else
              {
                  #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
                  /* EHRPD实体要考虑是否需要对发送失败的场景进行处理 */
                  NAS_ESM_EhrpdEntityProcEmmSendDataReqFail(pEmmEsmDataCnfMsg);
                  #endif
              }

              break;
        default:
              break;
    }

    if (NAS_ESM_NULL != pstStateTblInfo)
    {
        /*通过遍历动态表以及本条承载状态，这里判断如果动态表中至少存在一个是sending和succ状态，
          那么不发送end session， 假设既没有sending状态以及succ状态的承载，不外乎有两种情况，
          1、当前承载都是FAIL的。 2、当前承载FAIL和NULL兼而有之，对于这两种情况，表明当前没有承载
          正在使用射频资源。
        */
        NAS_ESM_LOG1("NAS_ESM_RcvEsmEmmDataCnf: IsRunning:", NAS_ESM_IsExistAllFailStateTable());
        if( ESM_BEARER_STATUS_BESIDE_RUNING == NAS_ESM_IsExistAllFailStateTable())
        {
            #if (FEATURE_ON == FEATURE_DSDS)
            NAS_ESM_SendEndSessionNotify();
            #endif
        }
    }
}
/*lint +e961*/

/*****************************************************************************
 Function Name   : NAS_ESM_SetAttachCidParaToStateTblAndSdfParaTbl
 Description     : 将注册用的CID参数信息设置到动态表和SDF表中
 Input           : VOS_UINT32*                              动态表ID
                   VOS_UINT32                               注册用CID
                   EMM_ESM_PDN_CON_REQ_TYPE_ENUM_UINT32     PDN请求类型
 Output          : None
 Return          : None

 History         :
    1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_ESM_SetAttachCidParaToStateTblAndSdfParaTbl(
    VOS_UINT32                                   *pulStateTblId,
    VOS_UINT32                                    ulRegCid,
    EMM_ESM_PDN_CON_REQ_TYPE_ENUM_UINT32          enPdnReqType
)
{
    NAS_ESM_STATE_INFO_STRU                      *pstStateAddr = VOS_NULL_PTR;
    NAS_ESM_SDF_PARA_STRU                        *pstSdfPara   = VOS_NULL_PTR;

    #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    VOS_UINT32                                    ulIndex;
    NAS_ESM_EHRPD_PDN_ENTITY_STRU                *pstPdnEntity = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG("NAS_ESM_SetAttachCidParaToStateTblAndSdfParaTbl: enter");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_SetAttachCidParaToStateTblAndSdfParaTbl_ENUM, LNAS_ENTRY);

    /* 自研CL多模版本，通过查询EHRPD实体记录来确认，找到也设置为handover类型 */

    /* 可维可测，上报HIDS实体状态 */
    NAS_ESM_SndOmEhrpdUsedPdnEntityStateInfo();

    /* 查找是否存在待恢复的EHRPD承载 */
    if (NAS_ESM_SUCCESS == NAS_ESM_GetAttachPdnInEhrpdEntity(&ulIndex))
    {
        /*在动态表中获取过程标识*/
        if(NAS_ESM_SUCCESS != NAS_ESM_GetStateTblIndexByCid(ulRegCid, pulStateTblId))
        {
            NAS_ESM_WARN_LOG("NAS_ESM_SetAttachCidParaToStateTblAndSdfParaTbl:CMDA insufficient resource!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_SetAttachCidParaToStateTblAndSdfParaTbl_ENUM, ESM_EHSM_STATETABLE_NOT_ENOUGH);

            /* 回复EMM ID_EMM_ESM_PDN_CON_RSP(FAIL) */
            NAS_ESM_SndEsmEmmPdnConRspMsg(EMM_ESM_PDN_CON_RSLT_FAIL, 0,0);
            return NAS_ESM_FAILURE;
        }

        /* 设置动态表初始状态 */
        pstStateAddr                     = NAS_ESM_GetStateTblAddr(*pulStateTblId);

        pstStateAddr->enBearerCntxtState = NAS_ESM_BEARER_STATE_INACTIVE;
        pstStateAddr->enBearerCntxtType  = NAS_ESM_BEARER_TYPE_DEFAULT;
        pstStateAddr->enPdnReqType       = NAS_ESM_PDN_REQ_TYPE_HANDOVER;

        /* 将PDN实体中的信息设置到SDF中，其他参数直接使用此注册CID的SDF表中的参数 */
        pstPdnEntity                     = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(ulIndex);

        /* 当前用于handover ATTACH的PDN实体进入恢复承载过程中 */
        pstPdnEntity->ucIsOnReconnFlag   = PS_TRUE;

        pstSdfPara                       = NAS_ESM_GetSdfParaAddr(ulRegCid);
        NAS_ESM_SetEhrpdPdnInfoToSdf(pstSdfPara, pstPdnEntity);

        /* 设置实体进入PDN请求发送未收到网侧响应态 */
        NAS_ESM_SET_EHRPD_ENTITY_STATE(NAS_ESM_EHRPD_ENTITY_STATE_ATTACH_PDN_REQ_NOT_RCV_CN_RSP);

        return NAS_ESM_SUCCESS;
    }
    #endif
    /* 其他场景 */

    /*在动态表中获取过程标识*/
    if(NAS_ESM_SUCCESS != NAS_ESM_GetStateTblIndexByCid(NAS_ESM_ATTACH_CID, pulStateTblId))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_SetAttachCidParaToStateTblAndSdfParaTbl:insufficient resource!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_SetAttachCidParaToStateTblAndSdfParaTbl_ENUM, ESM_STATETABLE_NOT_ENOUGH);

        /* 回复EMM ID_EMM_ESM_PDN_CON_RSP(FAIL) */
        NAS_ESM_SndEsmEmmPdnConRspMsg(EMM_ESM_PDN_CON_RSLT_FAIL, 0,0);
        return NAS_ESM_FAILURE;
    }

    /* 设置动态表初始状态 */
    pstStateAddr                         = NAS_ESM_GetStateTblAddr(*pulStateTblId);
    pstStateAddr->enBearerCntxtState     = NAS_ESM_BEARER_STATE_INACTIVE;
    pstStateAddr->enBearerCntxtType      = NAS_ESM_BEARER_TYPE_DEFAULT;

    /* VIA拼片版本的handover类型，由EMM发来的消息进行控制 */
    if(EMM_ESM_PDN_CON_REQ_TYPE_HANDOVER == enPdnReqType)
    {
        pstStateAddr->enPdnReqType       = NAS_ESM_PDN_REQ_TYPE_HANDOVER;
    }
    else
    {
        /* 其他场景都是initial类型 */
        pstStateAddr->enPdnReqType       = NAS_ESM_PDN_REQ_TYPE_INITIAL;
    }

    /*将传入的ulRegCid的SDF参数拷贝到CID0中，发起注册*/
    pstSdfPara                           = NAS_ESM_GetSdfParaAddr(NAS_ESM_ATTACH_CID);

    NAS_ESM_MEM_CPY_S(  pstSdfPara,
                        sizeof(NAS_ESM_SDF_PARA_STRU),
                        NAS_ESM_GetSdfParaAddr(ulRegCid),
                        sizeof(NAS_ESM_SDF_PARA_STRU));

    return NAS_ESM_SUCCESS;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 Function Name   : NAS_ESM_RcvEsmEmmClearClBearerNotify
 Description     : 收到EMM发来的ID_EMM_ESM_CLEAR_CL_BEARER_NOTIFY消息的处理
 Input           : VOS_VOID
 Output          : None
 Return          : None

 History         :
    1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_VOID  NAS_ESM_RcvEsmEmmClearClBearerNotify(VOS_VOID)
{
    /* 无论ESM处于主从模 */

    /* EMM通知清除EHRPD承载的原因可能是收到MMC的DETACH，网侧卡无效原因值REJ，
    鉴权REJ，CN MT DETACH(not-reattach)，无论哪种场景，都需要强行向APS上报承载
    恢复失败，对于这种严重异常，属于比较特殊的情况，即使多给APS上报也不会有问题 */

    /* 如果EHRPD实体不是已经收到网侧第一条缺省承载激活请求 */
    if (NAS_ESM_EHRPD_ENTITY_STATE_ALREADY_RCV_FIRST_BEARER_ACT_REQ != NAS_ESM_GET_EHRPD_ENTITY_STATE())
    {
        /* 支持EHRPD接入技术才通知EHSM */
        if (NAS_ESM_SUCCESS == NAS_EMM_IsEhrpdOr1XRatExist())
        {
            /* 通知EHSM清除所有承载 */
            NAS_ESM_SndEhsmClearAllBearerNotifyMsg();
        }

        /* 强行设置EHRPD实体进入已收到网侧第一条缺省承载请求，目的是后续清除的时候给APS上报恢复失败 */
        NAS_ESM_SET_EHRPD_ENTITY_STATE(NAS_ESM_EHRPD_ENTITY_STATE_ALREADY_RCV_FIRST_BEARER_ACT_REQ);
    }

    /* 清除所有EHRPD承载记录并上报恢复失败 */
    NAS_ESM_ClearAllEhrpdPdnInfoProc();

    /* 通知RABM清除所有承载资源 */
    NAS_ESM_SndEsmRabmClearClBearerNotifyMsg();

    return;
}
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of NasEsmEmmMsgProc.c */
