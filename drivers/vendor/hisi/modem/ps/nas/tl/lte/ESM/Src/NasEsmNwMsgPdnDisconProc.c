/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasEsmNwMsgPdnDisconProc.c
    Description : 处理EMM发给SM的网侧消息
    History     :
     1.丁丽 00128736        2008-09-01  Draft Enact
     2.祝义强 00138739      2008-12-03  Modify BA8D00656
     3.杨茜惠 00135146      2009-03-06  Modify BA8D01127
******************************************************************************/


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasEsmInclude.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASESMNWMSGPDNDISCOCPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASESMNWMSGPDNDISCOCPROC_C
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
 Function Name   : NAS_ESM_ProcNwMsgDeactEpsbReq
 Description     : 处理承载去激活这条空口消息
 Input           : ulStateTblIndex -- 动态表索引
                   pRcvMsg         -- 收到的空口消息
 Output          : None
 Return          : None

 History         :
    1.丁丽 00128736      2008-9-10   Draft Enact
    2.sunbing 49683         2009-02-05  Modify
    3.lihong00150010        2010-02-02  Modify
    4.liuwenyu00143951      2010-11-11  Modify
*****************************************************************************/
/*lint -e960*/
/*lint -e961*/
VOS_VOID  NAS_ESM_ProcValidNwMsgDeactEpsbReq
(
    VOS_UINT32                          ulStateTblIndex,
    const EMM_ESM_INTRA_DATA_IND_STRU  *pRcvMsg
)
{
    VOS_UINT32                          ulEpsbId         = NAS_ESM_NULL;
    VOS_UINT32                          ulSndNwMsgLen    = NAS_ESM_NULL;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr     = VOS_NULL_PTR;
    NAS_ESM_ENCODE_INFO_STRU            stEncodeInfo;

    /*打印进入该函数*/
    NAS_ESM_NORM_LOG("NAS_ESM_ProcNwMsgDeactEpsbReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcValidNwMsgDeactEpsbReq_ENUM, LNAS_ENTRY);

    /*取出承载信息*/
    ulEpsbId = (VOS_UINT32)(pRcvMsg->stEsmNwMsgIE.ucEpsbId);

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    /*停止定时器*/
    NAS_ESM_TimerStop(ulStateTblIndex, pstStateAddr->stTimerInfo.enPara);

    /*保存网侧消息携带的PTI*/
    pstStateAddr->bitOpNwMsgRecord = NAS_ESM_OP_TRUE;
    pstStateAddr->stNwMsgRecord.ucPti = pRcvMsg->stEsmNwMsgIE.ucPti;

    /*通知APP释放缺省承载及其关联承载*/
    NAS_ESM_DeactBearerAndInformApp(ulEpsbId);

    /*初始化，并填充NAS_ESM_ENCODE_INFO_STRU*/
    NAS_ESM_MEM_SET_S(  (VOS_VOID*)&stEncodeInfo,
                        sizeof(NAS_ESM_ENCODE_INFO_STRU),
                        0,
                        sizeof(NAS_ESM_ENCODE_INFO_STRU));
    stEncodeInfo.bitOpESMCau = NAS_ESM_OP_FALSE;
    stEncodeInfo.ucPti       = pstStateAddr->stNwMsgRecord.ucPti;
    stEncodeInfo.ulEpsbId    = ulEpsbId;

    /*向网侧回复Deactivate EPS bearer context accept*/
    NAS_ESM_EncodeDeactEpsbCntxtAccMsg(stEncodeInfo, \
                               NAS_ESM_GetCurEsmSndNwMsgAddr(),\
                              &ulSndNwMsgLen);

    NAS_ESM_SndAirMsgReportInd(NAS_ESM_GetCurEsmSndNwMsgAddr(),\
                                       ulSndNwMsgLen, NAS_ESM_AIR_MSG_DIR_ENUM_UP,\
                                       ESM_DEACT_EPS_BEARER_CNTXT_ACP);
    NAS_ESM_SndEsmEmmDataReqMsg(NAS_ESM_ILLEGAL_OPID, PS_FALSE, ulSndNwMsgLen, NAS_ESM_GetCurEsmSndNwMsgAddr());
    NAS_ESM_UpdateEsmSndNwMsgLen(ulSndNwMsgLen);

    /*通知EMM当前承载状态信息，发送ID_EMM_ESM_BEARER_STATUS_REQ*/
    NAS_ESM_SndEsmEmmBearerStatusReqMsg(EMM_ESM_BEARER_CNTXT_MOD_MUTUAL);

    /*释放状态表资源*/
    NAS_ESM_RelStateTblResource(ulStateTblIndex);
}

/*****************************************************************************
 Function Name   : NAS_ESM_ProcNwMsgPdnDisconRej
 Description     : 处理PDN Disconnect消息
 Input           : ulStateTblIndex -- 动态表索引
                   pRcvMsg         -- 收到的空口消息
 Output          : None
 Return          : None

 History         :
    1.丁丽 00128736      2008-9-10   Draft Enact
    2.sunbing 49683        2009-02-05  Modify
    3.lihong00150010       2010-2-02   Modify
    4.liuwenyu00143951     2010-11-11  Modify
*****************************************************************************/
VOS_VOID  NAS_ESM_ProcValidNwMsgPdnDisconRej
(
    VOS_UINT32                          ulStateTblIndex,
    const EMM_ESM_INTRA_DATA_IND_STRU  *pRcvMsg
)
{
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr     = VOS_NULL_PTR;

    /*打印进入该函数*/
    NAS_ESM_NORM_LOG("NAS_ESM_ProcValidNwMsgPdnDisconRej is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcValidNwMsgPdnDisconRej_ENUM, LNAS_ENTRY);

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    /*停止定时器*/
    NAS_ESM_TimerStop(ulStateTblIndex, TI_NAS_ESM_T3492);

    /*如果REJ携带原因值不为:#49 NAS_ESM_CAUSE_LAST_PDN_DISCONN_NOT_ALLOWED，则本地去激活缺省承载*/
    if(NAS_ESM_CAUSE_LAST_PDN_DISCONN_NOT_ALLOWED != pRcvMsg->stEsmNwMsgIE.enEsmCau)
    {
        /*释放本地承载资源,并向APP回复承载释放成功*/
        NAS_ESM_DeactBearerAndInformApp(pstStateAddr->ulEpsbId);

        /*通知EMM当前承载状态信息，发送ID_EMM_ESM_BEARER_STATUS_REQ*/
        NAS_ESM_SndEsmEmmBearerStatusReqMsg(EMM_ESM_BEARER_CNTXT_MOD_MUTUAL);
    }
    else
    {
        /*向APP发送ID_APP_ESM_BEARER_REL_CNF(失败)消息*/
        NAS_ESM_SndEsmAppSdfRelCnfFailMsg(ulStateTblIndex, \
                 NAS_ESM_GetAppErrorByEsmCause(pRcvMsg->stEsmNwMsgIE.enEsmCau));
    }

    /*终止PDN去连接请求,释放状态表资源*/
    NAS_ESM_RelStateTblResource(ulStateTblIndex);
}

/*****************************************************************************
 Function Name   : NAS_ESM_InformAppBearerRel
 Description     : 通知APP某一承载释放(此承载已激活)
 Input           : VOS_UINT32 ulEpsbId
 Output          : None
 Return          : None

 History         :
    1.丁丽 00128736      2008-10-22  Draft Enact
    2.sunbing 49683      2009-02-05  Modify
*****************************************************************************/
VOS_VOID  NAS_ESM_InformAppBearerRel(VOS_UINT32 ulEpsbId)
{
    VOS_UINT32                          ulStateTblIndex  = NAS_ESM_NULL;
    VOS_UINT32                          ulTmpBitCid      = NAS_ESM_NULL;
    VOS_UINT32                          ulCnt            = NAS_ESM_NULL;
    APP_ESM_MSG_TYPE_ENUM_UINT32        enAppMsgType;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr     = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbInfo      = VOS_NULL_PTR;

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_InformAppBearerRel is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_InformAppBearerRel_ENUM, LNAS_ENTRY);

    /*获取承载信息地址*/
    pstEpsbInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);

    ulTmpBitCid = pstEpsbInfo->ulBitCId;

    /* 若此承载没有对应的CID，则退出 */
    if((NAS_ESM_OP_FALSE == pstEpsbInfo->bitOpCId) || (NAS_ESM_NULL == ulTmpBitCid))
    {
        return;
    }

    for( ulCnt = NAS_ESM_MIN_CID; ulCnt <= NAS_ESM_MAX_CID; ulCnt++ )
    {
        if(NAS_ESM_OP_FALSE == ((ulTmpBitCid >> ulCnt) & NAS_ESM_OP_TRUE))
        {
            continue;
        }

        if(NAS_ESM_SUCCESS != NAS_ESM_QueryStateTblIndexByCid(ulCnt, &ulStateTblIndex))
        {
            /*向APP发送ID_APP_ESM_PDP_RELEASE_IND(成功)消息*/
            NAS_ESM_SndEsmAppSdfRelIndMsg(ulCnt, ulEpsbId);
            continue;
        }

        pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);
        if( NAS_ESM_OP_TRUE != pstStateAddr->bitOpAppMsgRecord )
        {
            /*向APP发送ID_APP_ESM_PDP_RELEASE_IND(成功)消息*/
            NAS_ESM_SndEsmAppSdfRelIndMsg(ulCnt, ulEpsbId);
            continue;
        }

        /*取出此承载中记录的APP消息类型*/
        enAppMsgType = pstStateAddr->stAppMsgRecord.enAppMsgType;

        /*根据所记录的消息类型回复消息*/
        switch( enAppMsgType )
        {
            case ID_APP_ESM_PDP_RELEASE_REQ:
                /*向APP发送ID_APP_ESM_PDP_RELEASE_CNF(成功)消息*/
                NAS_ESM_SndEsmAppSdfRelCnfSuccMsg(ulStateTblIndex);
                break;

            case ID_APP_ESM_PDP_MODIFY_REQ:

                NAS_ESM_SndEsmAppSdfModCnfFailMsg(  ulStateTblIndex, \
                                                    APP_ERR_UNSPECIFIED_ERROR);
                NAS_ESM_SndEsmAppSdfRelIndMsg(ulCnt, ulEpsbId);
                break;

            default:
                /*打印异常信息*/
                NAS_ESM_WARN_LOG("NAS_ESM_InformAppBearerRel:App Msg Record illogic!");
                TLPS_PRINT2LAYER_WARNING(NAS_ESM_InformAppBearerRel_ENUM, 1);
                break;
        }
    }

}
/*lint +e961*/
/*lint +e960*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of NasEsmNwMsgProc.c */
