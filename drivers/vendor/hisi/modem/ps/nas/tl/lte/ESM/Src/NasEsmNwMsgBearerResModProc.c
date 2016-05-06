/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasEsmNwMsgBearerResModProc.c
    Description : 处理EMM发给SM的网侧消息
    History     :
     1.丁丽 00128736        2008-09-01  Draft Enact
     2.祝义强 00138739      2008-12-03  Modify BA8D00656
     3.孙兵 49683           2009-01-06  Modify BA8D00870
     4.杨茜惠 00135146      2009-03-06  Modify BA8D01127
     5.李洪00150010         2009-08-03  Modify  BJ9D01608
     6.李洪00150010         2009-08-05  Modify  BJ9D01627
******************************************************************************/


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasEsmInclude.h"
/*#include    "IpDhcpv4Server.h"*/
#include    "NasEsmSmMsgProc.h"
#include    "NasEsmNwMsgProc.h"


/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASESMNWMSGBEARERRESMODPROC_C
#define    THIS_NAS_FILE_ID        PS_FILE_ID_NASESMNWMSGBEARERRESMODPROC_C
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
 Function Name   : NAS_ESM_ProcNwMsgResModRej
 Description     : 处理资源修改拒绝这条空口消息
 Input           : ulStateTblIndex -- 动态表索引
                   pRcvMsg         -- 收到的空口消息
 Output          : None
 Return          : None

 History         :
    1.丁丽 00128736      2008-9-10  Draft Enact
    2.sunbing 49683         2009-02-05 Modify
    3.lihong00150010        2010-2-02  Modify
    4.liuwenyu00143951      2010-11-11 Modify
*****************************************************************************/
VOS_VOID  NAS_ESM_ProcValidNwMsgResModRej
(
    VOS_UINT32                          ulStateTblIndex,
    const EMM_ESM_INTRA_DATA_IND_STRU  *pRcvMsg
)
{
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr    = VOS_NULL_PTR;
    VOS_UINT32                          ulTmpStateTblIndex =  NAS_ESM_NULL;

    /*打印进入该函数*/
    NAS_ESM_NORM_LOG("NAS_ESM_ProcValidNwMsgResModRej is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcValidNwMsgResModRej_ENUM, LNAS_ENTRY);

    /*停止定时器*/
    NAS_ESM_TimerStop(ulStateTblIndex, TI_NAS_ESM_T3481);

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    if(ID_APP_ESM_PDP_SETUP_REQ == pstStateAddr->stAppMsgRecord.enAppMsgType )
    {
        if( NAS_ESM_CAUSE_INVALID_EPS_BEARER_IDENTITY == pRcvMsg->stEsmNwMsgIE.enEsmCau )
        {
            /* 本地释放此承载的关联缺省承载和相关承载 */
            NAS_ESM_DeactBearerAndInformApp(pstStateAddr->ulLinkedEpsbId);

            /*通知EMM当前承载状态信息，发送ID_EMM_ESM_BEARER_STATUS_REQ*/
            NAS_ESM_SndEsmEmmBearerStatusReqMsg(EMM_ESM_BEARER_CNTXT_MOD_MUTUAL);

            /*清除和中止与ulEpsbId关联的流程信息*/
            if(NAS_ESM_SUCCESS == NAS_ESM_QueryStateTblIndexByEpsbId(pstStateAddr->ulLinkedEpsbId, &ulTmpStateTblIndex))
            {
                NAS_ESM_RelStateTblResource(ulTmpStateTblIndex);
            }
        }
        /*向APP发送ID_APP_ESM_PDP_SETUP_CNF(失败)消息*/
        NAS_ESM_SndEsmAppSdfSetupCnfFailMsg(ulStateTblIndex, \
                   NAS_ESM_GetAppErrorByEsmCause(pRcvMsg->stEsmNwMsgIE.enEsmCau));
    }
    else if(ID_APP_ESM_PDP_RELEASE_REQ == pstStateAddr->stAppMsgRecord.enAppMsgType)
    {
        if( NAS_ESM_CAUSE_INVALID_EPS_BEARER_IDENTITY == pRcvMsg->stEsmNwMsgIE.enEsmCau )
        {
            /* 本地释放此承载 */
            NAS_ESM_DeactBearerAndInformApp(pstStateAddr->ulEpsbId);

            /*通知EMM当前承载状态信息，发送ID_EMM_ESM_BEARER_STATUS_REQ*/
            NAS_ESM_SndEsmEmmBearerStatusReqMsg(EMM_ESM_BEARER_CNTXT_MOD_MUTUAL);
        }
        else
        {
            NAS_ESM_SndEsmAppSdfRelCnfFailMsg(ulStateTblIndex,
                  NAS_ESM_GetAppErrorByEsmCause(pRcvMsg->stEsmNwMsgIE.enEsmCau));
        }
    }
    else
    {
        if( NAS_ESM_CAUSE_INVALID_EPS_BEARER_IDENTITY == pRcvMsg->stEsmNwMsgIE.enEsmCau )
        {
            /* 本地释放此承载 */
            NAS_ESM_DeactBearerAndInformApp(pstStateAddr->ulEpsbId);

            /*通知EMM当前承载状态信息，发送ID_EMM_ESM_BEARER_STATUS_REQ*/
            NAS_ESM_SndEsmEmmBearerStatusReqMsg(EMM_ESM_BEARER_CNTXT_MOD_MUTUAL);
        }
        else
        {
            /*向APP返回承载修改失败消息*/
            NAS_ESM_SndEsmAppSdfModCnfFailMsg(ulStateTblIndex, \
                  NAS_ESM_GetAppErrorByEsmCause(pRcvMsg->stEsmNwMsgIE.enEsmCau));
        }
    }

    /*释放状态表资源*/
    NAS_ESM_RelStateTblResource(ulStateTblIndex);
}


/*****************************************************************************
 Function Name   : NAS_ESM_ProcValidNwMsgActDedictdEpsbReq
 Description     : 处理专有承载激活这条空口消息
 Input           : ulStateTblIndex -- 动态表索引
                   pRcvMsg         -- 收到的空口消息
 Output          : None
 Return          : None

 History         :
    1.丁丽 00128736      2008-9-10  Draft Enact
    2.sunbing 49683         2009-02-05  Modify
    3.liuwenyu00143951      2010-11-11  Modify
*****************************************************************************/
/*lint -e960*/
/*lint -e961*/
VOS_VOID  NAS_ESM_ProcValidNwMsgActDedictdEpsbReq
(
    VOS_UINT32                                      ulStateTblIndex,
    const EMM_ESM_INTRA_DATA_IND_STRU              *pRcvMsg
)
{
    VOS_UINT32                          ulEpsbId         = NAS_ESM_NULL;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo    = VOS_NULL_PTR;
    EMM_ESM_INTRA_DATA_IND_STRU        *pMsg                = VOS_NULL_PTR;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;
    NAS_ESM_PDP_MANAGE_INFO_STRU       *pstEsmBearerManageInfo = VOS_NULL_PTR;
    NAS_ESM_ENCODE_INFO_STRU            stEncodeInfo;

    pMsg = (EMM_ESM_INTRA_DATA_IND_STRU *) pRcvMsg;

    /*打印进入该函数*/
    NAS_ESM_NORM_LOG("NAS_ESM_ProcValidNwMsgActDedictdEpsbReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcValidNwMsgActDedictdEpsbReq_ENUM, LNAS_ENTRY);

    /*取出承载信息*/
    ulEpsbId = (VOS_UINT32)(pMsg->stEsmNwMsgIE.ucEpsbId);
    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    /*保存网侧消息携带的PTI*/
    pstStateAddr->bitOpNwMsgRecord    = NAS_ESM_OP_TRUE;
    pstStateAddr->stNwMsgRecord.ucPti = pMsg->stEsmNwMsgIE.ucPti;

    /*设置承载类型*/
    pstEpsbCntxtInfo->enBearerCntxtType = NAS_ESM_BEARER_TYPE_DEDICATED;

    /*初始化，并填充NAS_ESM_ENCODE_INFO_STRU*/
    NAS_ESM_MEM_SET_S(  (VOS_VOID*)&stEncodeInfo,
                        sizeof(NAS_ESM_ENCODE_INFO_STRU),
                        0,
                        sizeof(NAS_ESM_ENCODE_INFO_STRU));

    stEncodeInfo.bitOpESMCau = NAS_ESM_OP_FALSE;
    stEncodeInfo.ucPti       = pstStateAddr->stNwMsgRecord.ucPti;
    stEncodeInfo.ulEpsbId    = ulEpsbId;

    /*停止定时器*/
    NAS_ESM_TimerStop(ulStateTblIndex, pstStateAddr->stTimerInfo.enPara);

    /* 如果是APP主动发起的流程，则自动接受 */
    if (NAS_ESM_PTI_UNASSIGNED_VALUE != pstStateAddr->stNwMsgRecord.ucPti)
    {
        /* 自动接受专有承载激活的处理 */
        NAS_ESM_DediBearActMsgAutoAccept(ulStateTblIndex,
                                         stEncodeInfo,
                                         &(pMsg->stEsmNwMsgIE));

        return ;
    }

    /*取得承载管理信息*/
    pstEsmBearerManageInfo = NAS_ESM_GetBearerManageInfoAddr();

    /*APP设置对承载激活自动应答*/
    if( NAS_ESM_BEARER_MANAGE_MODE_AUTO == pstEsmBearerManageInfo->enMode )
    {
        /*APP设置为接受*/
        if( NAS_ESM_BEARER_MANAGE_TYPE_ACCEPT == pstEsmBearerManageInfo->enType )
        {
            /* 自动接受专有承载激活的处理 */
            NAS_ESM_DediBearActMsgAutoAccept(ulStateTblIndex,
                                             stEncodeInfo,
                                             &(pMsg->stEsmNwMsgIE));
        }
        else
        {
            NAS_ESM_NORM_LOG("NAS_ESM_ProcValidNwMsgActDedictdEpsbReq:NORM: Auto reject manage type!");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcValidNwMsgActDedictdEpsbReq_ENUM, 2);

            /*向网侧回复Activate default bearer context reject*/
            stEncodeInfo.bitOpESMCau = NAS_ESM_OP_TRUE;
            stEncodeInfo.ucESMCau = NAS_ESM_CAUSE_INSUFFICIENT_RESOURCES;

            NAS_ESM_ActDediBearFailProc(&stEncodeInfo,ulStateTblIndex);
        }
    }
    else
    {
        /* 专有承载激活手动处理 */
        NAS_ESM_DediBearActMsgManualProc(ulStateTblIndex,
                                          &(pMsg->stEsmNwMsgIE));
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_InformAppEpsBearerModFail
 Description     : 通知APP承载修改信息失败
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong 00150010       2009-4-21  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_InformAppEpsBearerModFail
(
    VOS_UINT32                          ulStateTblIndex,
    NAS_ESM_CAUSE_ENUM_UINT8            enEsmCause
)
{
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    if(NAS_ESM_OP_TRUE == pstStateAddr->bitOpAppMsgRecord)
    {
        switch(pstStateAddr->stAppMsgRecord.enAppMsgType)
        {
            case ID_APP_ESM_PDP_SETUP_REQ:
                NAS_ESM_SndEsmAppSdfSetupCnfFailMsg(ulStateTblIndex,\
                                         NAS_ESM_GetAppErrorByEsmCause(enEsmCause));
                break;

            case ID_APP_ESM_PDP_RELEASE_REQ:
                NAS_ESM_SndEsmAppSdfRelCnfFailMsg(ulStateTblIndex,\
                                         NAS_ESM_GetAppErrorByEsmCause(enEsmCause));

                break;
            case ID_APP_ESM_PDP_MODIFY_REQ:
                NAS_ESM_SndEsmAppSdfModCnfFailMsg(ulStateTblIndex,\
                                         NAS_ESM_GetAppErrorByEsmCause(enEsmCause));

                break;
            default:
                NAS_ESM_WARN_LOG("NAS_ESM_InformAppEpsBearerModFail:WARNING:No Support App Msg!");
                TLPS_PRINT2LAYER_WARNING(NAS_ESM_InformAppEpsBearerModFail_ENUM, LNAS_MSG_INVALID);
                break;
        }
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_InformAppModEspBearerSucc
 Description     : 通知APP专有承载信息修改成功
 Input           : pstMsgIE--------------------译码后的空口消息
                   ulStateTblIndex-------------状态表记录索引号
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2010-5-25  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_InformAppDediBearModSucc
(
    const  NAS_ESM_NW_MSG_STRU         *pstMsgIE,
    VOS_UINT32                          ulStateTblIndex
)
{
    NAS_ESM_STATE_INFO_STRU           *pstStateAddr = VOS_NULL_PTR;
    APP_ESM_BEARER_MODIFY_ENUM_UINT32  enModfyType  = APP_ESM_BEARER_MODIFY_BUTT;

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    /* APP主动发起的流程 */
    if(NAS_ESM_OP_TRUE == pstStateAddr->bitOpAppMsgRecord)
    {
        NAS_ESM_SndEsmAppSdfProcCnfSucc(ulStateTblIndex, NAS_ESM_GetBearModifyType(pstMsgIE));
        return ;
    }

    if (NAS_ESM_APP_IND_TYPE_SETUP == pstStateAddr->enAppIndType)
    {
        NAS_ESM_SndEsmAppSdfSetupIndMsg(ulStateTblIndex, APP_SUCCESS);
        return ;
    }

    if (NAS_ESM_APP_IND_TYPE_RELEASE == pstStateAddr->enAppIndType)
    {
        NAS_ESM_SndEsmAppSdfRelIndMsg(pstStateAddr->ulCid, pstMsgIE->ucEpsbId);
        return ;
    }

    enModfyType = NAS_ESM_GetBearModifyType(pstMsgIE);
    NAS_ESM_SndEsmAppSdfModIndMsg(ulStateTblIndex, enModfyType);

}

/*****************************************************************************
 Function Name   : NAS_ESM_InformAppEpsBearerModSucc
 Description     : 通知APP承载修改信息成功
 Input           : pstMsgIE--------------------译码后的空口消息
                   ulStateTblIndex-------------状态表记录索引号
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong 00150010       2009-4-21  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_InformAppEpsBearerModSucc
(
    const  NAS_ESM_NW_MSG_STRU         *pstMsgIE,
    VOS_UINT32                          ulStateTblIndex
)
{
    APP_ESM_BEARER_MODIFY_ENUM_UINT32  enModfyType  = APP_ESM_BEARER_MODIFY_BUTT;

    /* 若是缺省承载，且带QOS，则修改类型为即修改TFT又修改QOS；若是缺省承载，
       且不带QOS，则修改类型为修改TFT */
    if (PS_TRUE == NAS_ESM_IsDefaultEpsBearerType(NAS_ESM_GetBearCntxtType(pstMsgIE->ucEpsbId)))
    {
        enModfyType = NAS_ESM_GetBearModifyType(pstMsgIE);
        NAS_ESM_SndEsmAppSdfModIndMsg(ulStateTblIndex, enModfyType);
        return ;
    }

    /* 通知APP专有承载信息修改成功 */
    NAS_ESM_InformAppDediBearModSucc(pstMsgIE, ulStateTblIndex);
}


/*****************************************************************************
 Function Name   : NAS_ESM_ProcValidNwMsgModEpsbReq
 Description     : 处理承载修改这条空口消息
 Input           : ulStateTblIndex -- 动态表索引
                   pRcvMsg         -- 收到的空口消息
 Output          : None
 Return          : None

 History         :
    1.丁丽 00128736    2008-9-10   Draft Enact
    2.sunbing 49683       2009-02-05  Modify
    3.lihong00150010      2010-2-02   Modify
    4.liuwenyu00143951    2010-11-11  Modify
*****************************************************************************/
VOS_VOID  NAS_ESM_ProcValidNwMsgModEpsbReq
(
    VOS_UINT32                          ulStateTblIndex,
    const EMM_ESM_INTRA_DATA_IND_STRU  *pRcvMsg
)
{
    VOS_UINT32                          ulEpsbId            = NAS_ESM_NULL;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;
    NAS_ESM_PDP_MANAGE_INFO_STRU       *pstEsmBearerManageInfo = VOS_NULL_PTR;
    NAS_ESM_ENCODE_INFO_STRU            stEncodeInfo;

    /*打印进入该函数*/
    NAS_ESM_NORM_LOG("NAS_ESM_ProcValidNwMsgModEpsbReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcValidNwMsgModEpsbReq_ENUM, LNAS_ENTRY);

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    /*取出承载信息*/
    ulEpsbId = (VOS_UINT32)(pRcvMsg->stEsmNwMsgIE.ucEpsbId);

    if(NAS_ESM_BEARER_PROC_TRANS_STATE_INACTIVE == pstStateAddr->enProcTransTState)
    {
        /*保存网侧消息携带的PTI*/
        pstStateAddr->stNwMsgRecord.ucPti = pRcvMsg->stEsmNwMsgIE.ucPti;
    }

    /*初始化，并填充NAS_ESM_ENCODE_INFO_STRU*/
    NAS_ESM_MEM_SET_S(  (VOS_VOID*)&stEncodeInfo,
                        sizeof(NAS_ESM_ENCODE_INFO_STRU),
                        0,
                        sizeof(NAS_ESM_ENCODE_INFO_STRU));

    stEncodeInfo.bitOpESMCau = NAS_ESM_OP_FALSE;
    stEncodeInfo.ucPti       = pstStateAddr->stNwMsgRecord.ucPti;
    stEncodeInfo.ulEpsbId    = ulEpsbId;

    /*停止定时器*/
    NAS_ESM_TimerStop(ulStateTblIndex, pstStateAddr->stTimerInfo.enPara);

    /* 如果是APP主动发起的流程，则自动接受 */
    if (NAS_ESM_PTI_UNASSIGNED_VALUE != pstStateAddr->stNwMsgRecord.ucPti)
    {
        /* 自动接受承载修改的处理 */
        NAS_ESM_BearModMsgAutoAccept(ulStateTblIndex,
                                     stEncodeInfo,
                                    &(pRcvMsg->stEsmNwMsgIE));

        return ;
    }

    /*取得承载管理信息*/
    pstEsmBearerManageInfo = NAS_ESM_GetBearerManageInfoAddr();

    /*APP设置对承载激活自动应答*/
    if( NAS_ESM_BEARER_MANAGE_MODE_AUTO == pstEsmBearerManageInfo->enMode )
    {
        /*APP设置为接受*/
        if( NAS_ESM_BEARER_MANAGE_TYPE_ACCEPT == pstEsmBearerManageInfo->enType )
        {
            /* 自动接受承载修改的处理 */
            NAS_ESM_BearModMsgAutoAccept(ulStateTblIndex,
                                         stEncodeInfo,
                                        &(pRcvMsg->stEsmNwMsgIE));
        }
        else
        {
            NAS_ESM_NORM_LOG("NAS_ESM_ProcValidNwMsgModEpsbReq:NORM: Auto reject manage type!");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcValidNwMsgModEpsbReq_ENUM, 2);

            stEncodeInfo.bitOpESMCau = NAS_ESM_OP_TRUE;
            stEncodeInfo.ucESMCau    = NAS_ESM_CAUSE_INSUFFICIENT_RESOURCES;
            NAS_ESM_BearModFailProc(&stEncodeInfo,ulStateTblIndex);
        }
    }
    else
    {
        /* 承载修改手动处理 */
        NAS_ESM_BearModMsgManualProc(ulStateTblIndex,
                                    &(pRcvMsg->stEsmNwMsgIE));
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_IsExistSameEpsbIdInList
 Description     : 判断承载号数组中是否已经有指定的承载号了
 Input           : ucEpsbId-------------------------承载号
                   ucEpsBearNum---------------------承载数
                   pucEpsbIdArray-------------------承载号数组首地址
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.liuwenyu 00143951      2010-5-26  Draft Enact

*****************************************************************************/

VOS_UINT32 NAS_ESM_IsExistSameEpsbIdInList
(
    VOS_UINT8                           ucEpsbId,
    VOS_UINT8                           ucEpsBearNum,
    const VOS_UINT8                    *pucEpsbIdArray
)
{
    VOS_UINT32                          ulCnt = NAS_ESM_NULL;

    for (ulCnt = NAS_ESM_NULL; ulCnt < ucEpsBearNum; ulCnt++)
    {
        if (ucEpsbId == pucEpsbIdArray[ulCnt])
        {
            return NAS_ESM_SUCCESS;
        }
    }

    return NAS_ESM_FAILURE;
}

/*****************************************************************************
 Function Name   : NAS_ESM_IsNeedPreferrenceCollision
 Description     : 判读是否需要进行优先级冲突处理
 Input           : pstNwMsg -- 译码后的空口消息指针
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2011-04-08  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_ESM_IsNeedPreferrenceCollision
(
    const NAS_ESM_NW_MSG_STRU          *pstNwMsg
)
{

    if (NAS_ESM_OP_FALSE == pstNwMsg->bitOpTadInfo)
    {
        return PS_FALSE;
    }

    if ((NAS_ESM_TFT_OP_TYPE_CREATE_TFT == pstNwMsg->stTadInfo.enTftOpType)
        || (NAS_ESM_TFT_OP_TYPE_ADD_FILTER == pstNwMsg->stTadInfo.enTftOpType)
        || (NAS_ESM_TFT_OP_TYPE_REPLACE_FILTER == pstNwMsg->stTadInfo.enTftOpType))
    {
        return PS_TRUE;
    }

    return PS_FALSE;
}

/*****************************************************************************
 Function Name   : NAS_ESM_ValidateLinkedEpsbId
 Description     : 获取空口消息中携带的承载关联的缺省承载
 Input           : pstNwMsg---------------------译码后的空口消息指针
                   pucLinkedEpsbId--------------缺省承载号指针
 Output          : None
 Return          : NAS_ESM_CAUSE_ENUM_UINT8

 History         :
    1.lihong00150010      2010-5-14  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_GetDefltBearLinkToBearInAirMsg
(
    const NAS_ESM_NW_MSG_STRU          *pstNwMsg,
    VOS_UINT8                          *pucLinkedEpsbId
)
{
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEspCntxtInfo = VOS_NULL_PTR;

    if (NAS_ESMCN_MSG_TYPE_ACT_DEDICTD_EPS_BEARER_CNTXT_REQ == pstNwMsg->enEsmCnMsgType)
    {
        *pucLinkedEpsbId = pstNwMsg->ucLinkedEpsbId;
    }
    else
    {
        pstEspCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(pstNwMsg->ucEpsbId);
        if (NAS_ESM_BEARER_TYPE_DEDICATED == pstEspCntxtInfo->enBearerCntxtType)
        {
            *pucLinkedEpsbId = (VOS_UINT8)pstEspCntxtInfo->ulLinkedEpsbId;
        }
        else
        {
            *pucLinkedEpsbId = pstNwMsg->ucEpsbId;
        }
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_ValidatePfPrecedence
 Description     : 验证空口消息中携带的PF优先级与当前此PDN下所有承载的PF的优先级是否冲突
 Input           : pstNwMsg---------------------译码后的空口消息
                   pucPfNum---------------------packet filter数
                   pstPfPVList------------------优先级验证列表首地址
 Output          : pucEpsBearNum----------------承载数
                   pucEpsbIdArray---------------承载号数组首地址
 Return          : VOS_VOID

 History         :
    1.lihong 00150010      2010-5-27  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_ValidatePfPrecedence
(
    const NAS_ESM_NW_MSG_STRU          *pstNwMsg,
    VOS_UINT8                          *pucEpsBearNum,
    VOS_UINT8                          *pucEpsbIdArray
)
{
    VOS_UINT8                           ucCnt1      = NAS_ESM_NULL;
    VOS_UINT8                           ucCnt2      = NAS_ESM_NULL;
    VOS_UINT8                           ucEpsbIdTmp = NAS_ESM_NULL;
    VOS_UINT8                           ucPfNum     = NAS_ESM_NULL;
    VOS_UINT32                          ulRslt      = NAS_ESM_FAILURE;
    NAS_ESM_PF_PRCDNC_VLDT_STRU        *pstPfPVList = VOS_NULL_PTR;

    *pucEpsBearNum = NAS_ESM_NULL;

    /* 申请优先级验证列表存储空间 */
    pstPfPVList = NAS_ESM_MEM_ALLOC(NAS_ESM_MAX_EPSB_NUM * NAS_ESM_MAX_SDF_PF_NUM
                                    * sizeof(NAS_ESM_PF_PRCDNC_VLDT_STRU));

    if (VOS_NULL_PTR == pstPfPVList)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_ValidatePfPrecedence:NAS_ESM_MEM_ALLOC failed!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ValidatePfPrecedence_ENUM, LNAS_NULL_PTR);

        return ;
    }

    /* 获取空口消息中携带的承载关联的缺省承载 */
    NAS_ESM_GetDefltBearLinkToBearInAirMsg(pstNwMsg, &ucEpsbIdTmp);

    /* 形成优先级验证列表 */
    ulRslt = NAS_ESM_CreatePfPrecedenceValidateListInPdn(ucEpsbIdTmp,
                                                         &ucPfNum,
                                                         pstPfPVList);

    if (ulRslt != NAS_ESM_SUCCESS)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_ValidatePfPrecedence:NAS_ESM_CreatePfPrecedenceValidateListInPdn failed!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ValidatePfPrecedence_ENUM, LNAS_FAIL);

        /* 释放优先级验证列表存储空间 */
        NAS_ESM_MEM_FREE(pstPfPVList);

        return ;
    }

    for (ucCnt1 = NAS_ESM_NULL; ucCnt1 < pstNwMsg->stTadInfo.ucSdfPfNum; ucCnt1++)
    {
        for (ucCnt2 = NAS_ESM_NULL; ucCnt2 < ucPfNum; ucCnt2++)
        {
            if (pstPfPVList[ucCnt2].ucPrecedence != pstNwMsg->stTadInfo.astSdfPfInfo[ucCnt1].ucPrecedence)
            {
                continue;
            }
            /* 如果是同一个承载的相同的Packetfilter,不是优先级冲突 */
            if((pstPfPVList[ucCnt2].ucEpsbId == pstNwMsg->ucEpsbId)
            && (pstPfPVList[ucCnt2].ucPfId == pstNwMsg->stTadInfo.astSdfPfInfo[ucCnt1].ucNwPacketFilterId))
            {
                continue;
            }

            ucEpsbIdTmp = pstPfPVList[ucCnt2].ucEpsbId;

            /* 将承载号数组中不存在的承载号添加到数组中 */
            ulRslt = NAS_ESM_IsExistSameEpsbIdInList(ucEpsbIdTmp,
                                                    *pucEpsBearNum,
                                                     pucEpsbIdArray);

            if (NAS_ESM_FAILURE == ulRslt)
            {
                NAS_ESM_INFO_LOG1("NAS_ESM_ValidatePfPrecedence:collision Epsbid =",ucEpsbIdTmp);
                TLPS_PRINT2LAYER_INFO1(NAS_ESM_ValidatePfPrecedence_ENUM, LNAS_FAIL, ucEpsbIdTmp);

                pucEpsbIdArray[*pucEpsBearNum] = ucEpsbIdTmp;
                (*pucEpsBearNum)++;
            }
        }
    }

    /* 释放优先级验证列表存储空间 */
    NAS_ESM_MEM_FREE(pstPfPVList);
}


VOS_VOID NAS_ESM_LocalDeactAlreadyActiveEpsBearer
(
    VOS_UINT32                          ulEpsbId
)
{
    VOS_UINT32                          ulStateTblId    = NAS_ESM_NULL;

    /* 承载已经激活，去激活承载 */
    if(NAS_ESM_BEARER_STATE_ACTIVE == NAS_ESM_GetBearCntxtState(ulEpsbId))
    {
        NAS_ESM_NORM_LOG("NAS_ESM_LocalDeactAlreadyActiveEpsBearer: local deactive active bearer.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_LocalDeactAlreadyActiveEpsBearer_ENUM, 1);

        /*应先去激活此承载及与其关联的承载*/
        NAS_ESM_DeactBearerAndInformApp(ulEpsbId);

        /*清除和中止与ulEpsbId关联的流程信息*/
        if(NAS_ESM_SUCCESS == NAS_ESM_QueryStateTblIndexByEpsbId(ulEpsbId,
                                                                &ulStateTblId))
        {
            NAS_ESM_RelStateTblResource(ulStateTblId);
        }
    }
}

VOS_UINT32  NAS_ESM_SndMsgToRelEpsBearer
(
    VOS_UINT32                          ulEpsbId
)
{
    VOS_UINT32                          ulStateTblIndex     = NAS_ESM_NULL;
    VOS_UINT32                          ulCid               = NAS_ESM_NULL;
    VOS_UINT32                          ulPti               = NAS_ESM_NULL;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;
    NAS_ESM_RES_MOD_ENCODE_INFO_STRU    stResModEncodeInfo;

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_SndMsgToRelEpsBearer is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_SndMsgToRelEpsBearer_ENUM, LNAS_ENTRY);

    (VOS_VOID)NAS_ESM_QueryFirstSdfIdByEpsbId(ulEpsbId, &ulCid);

    /*根据CID号码找到状态表的ulStateTblIndex*/
    if( NAS_ESM_FAILURE == NAS_ESM_GetStateTblIndexByCid(ulCid,&ulStateTblIndex))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_SndMsgToRelEpsBearer:WARNING: Tbl index Query Fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_SndMsgToRelEpsBearer_ENUM, ESM_Tbl_index_Query_Fail);
        return NAS_ESM_FAILURE;
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
    stResModEncodeInfo.ulEpsbId           = ulEpsbId;
    stResModEncodeInfo.ulLinkedEpsbId     = ulEpsbId;
    stResModEncodeInfo.enSdfOpType        = NAS_ESM_SDF_OP_TYPE_DELETE_SDF;

    /*组装Bearer_Res_Mod_Req消息*/
    if( NAS_ESM_FAILURE == NAS_ESM_EncodeBearerResModReqMsgRelBearer(stResModEncodeInfo, \
                                                      pstStateAddr->stNwMsgRecord.aucMsgBuff,\
                                                      &pstStateAddr->stNwMsgRecord.ulMsgLength))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_SndMsgToRelEpsBearer:EncodeBearerResModReqMsg fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_SndMsgToRelEpsBearer_ENUM, EncodeBearerResModReqMsg_fail);

        NAS_ESM_RelStateTblResource(ulStateTblIndex);

        return NAS_ESM_FAILURE;
    }

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

    NAS_ESM_SndAirMsgReportInd(pstStateAddr->stNwMsgRecord.aucMsgBuff,
                           pstStateAddr->stNwMsgRecord.ulMsgLength,
                           NAS_ESM_AIR_MSG_DIR_ENUM_UP,
                           ESM_BEARER_RESOUCE_MOD_REQ);

    /* 释放动态表 */
    NAS_ESM_RelStateTblResource(ulStateTblIndex);

    return NAS_ESM_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_ProcPfPrecedenceCollision
 Description     : PF优先级冲突处理
 Input           : enEsmCnMsgType-----------------------空口消息类型
                   pstEncodeInfo------------------------编码所需信息
                   ulStateTblIndex----------------------动态表索引
                   ucEpsBearNum-------------------------承载数
                   pucEpsbIdArray-----------------------承载数组首地址
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2010-5-26  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_ProcPfPrecedenceCollision
(
    const NAS_ESM_NW_MSG_STRU                *pstNwMsg
)
{
    VOS_UINT8                           ucCnt               = NAS_ESM_NULL;
    VOS_UINT8                           ulEpsBearNum        = NAS_ESM_NULL;
    VOS_UINT8                           aulEpsbIdArray[NAS_ESM_MAX_EPSB_NUM] = {NAS_ESM_NULL};

    /*  验证空口消息中携带的PF优先级与当前此PDN下*/
    /*  所有承载的PF的优先级是否冲突 */
    NAS_ESM_ValidatePfPrecedence(pstNwMsg, &ulEpsBearNum, aulEpsbIdArray);

    if (NAS_ESM_NULL == ulEpsBearNum)
    {
        return;
    }

    /* 判断是否存在与原有的缺省承载优先级冲突的情况 */
    for (ucCnt = NAS_ESM_NULL; ucCnt < ulEpsBearNum; ucCnt++)
    {
        if (PS_TRUE == NAS_ESM_IsDefaultEpsBearerType(NAS_ESM_GetBearCntxtType(aulEpsbIdArray[ucCnt])))
        {
            break;
        }
    }

    /* 存在缺省承载就释放缺省承载，否则释放冲突的专有承载*/
    if (ucCnt >= ulEpsBearNum)
    {
        for (ucCnt = NAS_ESM_NULL; ucCnt < ulEpsBearNum; ucCnt++)
        {
            NAS_ESM_LOG1("NAS_ESM_ProcPfPrecedenceCollision:release dedicate bearer ",aulEpsbIdArray[ucCnt]);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_ProcPfPrecedenceCollision_ENUM, 1, aulEpsbIdArray[ucCnt]);

            /* 发送空口消息,释放承载的所有Packetfilter */
            if (NAS_ESM_FAILURE == NAS_ESM_SndMsgToRelEpsBearer(aulEpsbIdArray[ucCnt]))
            {
                NAS_ESM_WARN_LOG("NAS_ESM_ProcPfPrecedenceCollision:Snd Rel Beare All Pf Error!");
                TLPS_PRINT2LAYER_WARNING(NAS_ESM_ProcPfPrecedenceCollision_ENUM, 2);
            }

            NAS_ESM_LocalDeactAlreadyActiveEpsBearer(aulEpsbIdArray[ucCnt]);
        }
    }
    else
    {
        NAS_ESM_WARN_LOG("NAS_ESM_ProcPfPrecedenceCollision:release default bearer!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ProcPfPrecedenceCollision_ENUM, 3);

        NAS_ESM_LocalDeactAlreadyActiveEpsBearer(aulEpsbIdArray[ucCnt]);
    }


    /*通知EMM当前承载状态信息，发送ID_EMM_ESM_BEARER_STATUS_REQ*/
    NAS_ESM_SndEsmEmmBearerStatusReqMsg(EMM_ESM_BEARER_CNTXT_MOD_MUTUAL);

}


/*****************************************************************************
 Function Name   : NAS_ESM_GetPacketFilter
 Description     : 根据PF号获取SDF下的某个filter
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong 00150010      2009-7-15  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_ESM_GetPacketFilter
(
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo,
    NAS_ESM_CONTEXT_TFT_STRU          **pstPacketFilter,
    VOS_UINT8                           ucNwPacketFilterId
)
{
    VOS_UINT32                          ulCnt = NAS_ESM_NULL;

    /* 输入参数合法性检测 */
    if(VOS_NULL_PTR == pstSdfCntxtInfo)
    {
        return NAS_ESM_FAILURE;
    }

    for(ulCnt = 0; ulCnt < pstSdfCntxtInfo->ulSdfPfNum; ulCnt++)
    {
        if(ucNwPacketFilterId == pstSdfCntxtInfo->astSdfPfInfo[ulCnt].ucNwPacketFilterId)
        {
            *pstPacketFilter = &pstSdfCntxtInfo->astSdfPfInfo[ulCnt];
            return NAS_ESM_SUCCESS;
        }
    }
    return NAS_ESM_FAILURE;
}
/*****************************************************************************
 Function Name   : NAS_ESM_DeleteOnePacketFilter
 Description     : 根据PF号删除SDF下的某个filter
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.liuwenyu 00143951      2010-5-20  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_DeleteOnePacketFilter
(
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo,
    VOS_UINT8                           ucNwPacketFilterId
)
{
    VOS_UINT32                          ulCnt    = NAS_ESM_NULL;

    for(ulCnt = 0; ulCnt < pstSdfCntxtInfo->ulSdfPfNum; ulCnt++)
    {
        if(ucNwPacketFilterId == pstSdfCntxtInfo->astSdfPfInfo[ulCnt].ucNwPacketFilterId)
        {
            break;
        }
    }

    if (ulCnt < pstSdfCntxtInfo->ulSdfPfNum)
    {
        /* 拷贝最后一个到要删除的PF的位置 */
        NAS_ESM_MEM_CPY_S(  &pstSdfCntxtInfo->astSdfPfInfo[ulCnt],
                            sizeof(NAS_ESM_CONTEXT_TFT_STRU),
                            &pstSdfCntxtInfo->astSdfPfInfo[pstSdfCntxtInfo->ulSdfPfNum - 1],
                            sizeof(NAS_ESM_CONTEXT_TFT_STRU));

        NAS_ESM_MEM_SET_S(  &pstSdfCntxtInfo->astSdfPfInfo[pstSdfCntxtInfo->ulSdfPfNum - 1],
                            sizeof(NAS_ESM_CONTEXT_TFT_STRU),
                            NAS_ESM_NULL,
                            sizeof(NAS_ESM_CONTEXT_TFT_STRU));

        pstSdfCntxtInfo->ulSdfPfNum--;
    }

}

/*****************************************************************************
 Function Name   : NAS_ESM_DeletePacketFilterProc
 Description     : 删除SDF处理
 Input           : pstEpsbCntxtInfo---------------承载信息
                   pstSdfCntxtInfo----------------SDF信息
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2010-2-3  Draft Enact
    2.lihong00150010      2010-5-31 Modify

*****************************************************************************/
VOS_VOID  NAS_ESM_DeletePacketFilterProc
(
    const  NAS_ESM_NW_MSG_STRU         *pstMsgIE,
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo,
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo,
    VOS_UINT32                          ulStateTblIndex
)
{
    VOS_UINT32                          ulCnt           = NAS_ESM_NULL;
    APP_ESM_EPS_QOS_INFO_STRU          *pstEpsQosInfo   = VOS_NULL_PTR;
    APP_ESM_EPS_QOS_INFO_STRU          *pstSdfQosInfo   = VOS_NULL_PTR;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr    = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG("NAS_ESM_DeletePacketFilterProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_DeletePacketFilterProc_ENUM, LNAS_ENTRY);

    pstEpsQosInfo = &pstEpsbCntxtInfo->stEpsQoSInfo.stQosInfo;
    pstSdfQosInfo = &pstSdfCntxtInfo->stSdfQosInfo.stQosInfo;
    pstStateAddr    = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    /* 删除SDF上下文中指定的Pakketfilter */
    for (ulCnt = 0; ulCnt < pstMsgIE->stTadInfo.ucSdfPfNum; ulCnt++)
    {
        NAS_ESM_DeleteOnePacketFilter(pstSdfCntxtInfo,
                                      pstMsgIE->stTadInfo.astSdfPfInfo[ulCnt].ucNwPacketFilterId);
    }

    /* 若是专有承载，且此SDF的packet filter被全部删除，则删除此SDF */
    if ((NAS_ESM_NULL == pstSdfCntxtInfo->ulSdfPfNum)
        && (NAS_ESM_BEARER_TYPE_DEDICATED == pstEpsbCntxtInfo->enBearerCntxtType))
    {
        if (PS_TRUE == NAS_ESM_IsGbrBearer(pstEpsbCntxtInfo->stEpsQoSInfo.stQosInfo.ucQCI))
        {
            pstEpsQosInfo->ulULMaxRate -= pstSdfQosInfo->ulULMaxRate;
            pstEpsQosInfo->ulDLMaxRate -= pstSdfQosInfo->ulDLMaxRate;
            pstEpsQosInfo->ulULGMaxRate -= pstSdfQosInfo->ulULGMaxRate;
            pstEpsQosInfo->ulDLGMaxRate -= pstSdfQosInfo->ulDLGMaxRate;
        }

        /* 修改上报类型为NAS_ESM_APP_IND_TYPE_RELEASE */
        pstStateAddr->enAppIndType = NAS_ESM_APP_IND_TYPE_RELEASE;

        /* 删除SDF上下文 */
        NAS_ESM_MEM_SET_S(  pstSdfCntxtInfo,
                            sizeof(NAS_ESM_SDF_CNTXT_INFO_STRU),
                            0,
                            sizeof(NAS_ESM_SDF_CNTXT_INFO_STRU));
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_ReplacePacketFilterProc
 Description     : 修改SDF处理
 Input           : pstMsgIE-----------------------译码后的消息
                   pstSdfCntxtInfo----------------SDF信息
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2010-2-3  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_ReplacePacketFilterProc
(
    const  NAS_ESM_NW_MSG_STRU         *pstMsgIE,
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo
)
{
    VOS_UINT32                          ulCnt            = NAS_ESM_NULL;
    VOS_UINT32                          ulRslt           = NAS_ESM_NULL;
    VOS_UINT8                           ucPacketFilterID = NAS_ESM_NULL;
    NAS_ESM_CONTEXT_TFT_STRU           *pstPacketFilter  = VOS_NULL_PTR;
    NAS_ESM_TAD_INFO_STRU              *pstTadInfoTmp    = {NAS_ESM_NULL};

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_ReplacePacketFilterProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_ReplacePacketFilterProc_ENUM, LNAS_ENTRY);

    pstTadInfoTmp = NAS_ESM_MEM_ALLOC(sizeof(NAS_ESM_TAD_INFO_STRU));
    if(VOS_NULL_PTR == pstTadInfoTmp)
    {
        NAS_ESM_ERR_LOG("NAS_ESM_ReplacePacketFilterProc:Alloc Mem fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_ReplacePacketFilterProc_ENUM, LNAS_NULL_PTR);
        return;
    }

    NAS_ESM_MEM_SET_S(pstTadInfoTmp, sizeof(NAS_ESM_TAD_INFO_STRU), 0, sizeof(NAS_ESM_TAD_INFO_STRU));

    /* 修改PF*/
    for(ulCnt = 0; ulCnt < pstMsgIE->stTadInfo.ucSdfPfNum; ulCnt++)
    {
        ulRslt = NAS_ESM_GetPacketFilter(   pstSdfCntxtInfo,
                                            &pstPacketFilter,
                                            pstMsgIE->stTadInfo.astSdfPfInfo[ulCnt].ucNwPacketFilterId);

        /* 存在就替换，不存在就添加 */
        if(NAS_ESM_SUCCESS == ulRslt)
        {
            NAS_ESM_INFO_LOG("NAS_ESM_ReplacePacketFilterProc:PF Exist!");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_ReplacePacketFilterProc_ENUM, 1);
            /* buffered static packetfilter id */
            ucPacketFilterID = pstPacketFilter->ucPacketFilterId;

            NAS_ESM_MEM_CPY_S(  pstPacketFilter,
                                sizeof(NAS_ESM_CONTEXT_TFT_STRU),
                                &(pstMsgIE->stTadInfo.astSdfPfInfo[ulCnt]),
                                sizeof(NAS_ESM_CONTEXT_TFT_STRU));

            pstPacketFilter->ucPacketFilterId = ucPacketFilterID;
        }
        else
        {
            NAS_ESM_INFO_LOG("NAS_ESM_ReplacePacketFilterProc:PF Not Exist!");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_ReplacePacketFilterProc_ENUM, 2);

            NAS_ESM_MEM_CPY_S(  &pstTadInfoTmp->astSdfPfInfo[pstTadInfoTmp->ucSdfPfNum],
                                sizeof(NAS_ESM_CONTEXT_TFT_STRU),
                                &pstMsgIE->stTadInfo.astSdfPfInfo[ulCnt],
                                sizeof(NAS_ESM_CONTEXT_TFT_STRU));

            pstTadInfoTmp->ucSdfPfNum++;
        }
    }

    /* 添加没有找到的filter 到Sdf中*/
    if ((NAS_ESM_NULL != pstTadInfoTmp->ucSdfPfNum)
      &&((pstSdfCntxtInfo->ulSdfPfNum + pstTadInfoTmp->ucSdfPfNum) <= NAS_ESM_MAX_SDF_PF_NUM))
    {

        NAS_ESM_MEM_CPY_S(  &pstSdfCntxtInfo->astSdfPfInfo[pstSdfCntxtInfo->ulSdfPfNum],
                            sizeof(NAS_ESM_CONTEXT_TFT_STRU) * pstTadInfoTmp->ucSdfPfNum,
                            pstTadInfoTmp->astSdfPfInfo,
                            sizeof(NAS_ESM_CONTEXT_TFT_STRU) * pstTadInfoTmp->ucSdfPfNum);

        pstSdfCntxtInfo->ulSdfPfNum += pstTadInfoTmp->ucSdfPfNum;

        /* 赋值SDF关联的承载信息 */
        pstSdfCntxtInfo->ulEpsbId = pstMsgIE->ucEpsbId;
    }

    NAS_ESM_MEM_FREE(pstTadInfoTmp);
}

/*****************************************************************************
 Function Name   : NAS_ESM_CreateTftProc
 Description     : 修改承载过程中TAD码是Create TFT 的处理函数
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.liuwenyu 00143951      2010-5-12  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_CreateTftProc
(
    const  NAS_ESM_NW_MSG_STRU                  *pstMsgIE,
    NAS_ESM_SDF_CNTXT_INFO_STRU                 *pstSdfCntxtInfo
)
{
    /*打印进入该函数*/
    NAS_ESM_NORM_LOG("NAS_ESM_CreateTftProc: create to default bearer.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_CreateTftProc_ENUM, LNAS_ENTRY);

    NAS_ESM_MEM_CPY_S(  pstSdfCntxtInfo->astSdfPfInfo,
                        sizeof(NAS_ESM_CONTEXT_TFT_STRU) * NAS_ESM_MAX_SDF_PF_NUM,
                        pstMsgIE->stTadInfo.astSdfPfInfo,
                        sizeof(NAS_ESM_CONTEXT_TFT_STRU) * pstMsgIE->stTadInfo.ucSdfPfNum);

    pstSdfCntxtInfo->ulSdfPfNum = pstMsgIE->stTadInfo.ucSdfPfNum;
    pstSdfCntxtInfo->ulEpsbId   = pstMsgIE->ucEpsbId;
}


VOS_VOID NAS_ESM_DeleteTftProc
(
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo
)
{
    /*打印进入该函数*/
    NAS_ESM_NORM_LOG("NAS_ESM_DeleteTftProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_DeleteTftProc_ENUM, LNAS_ENTRY);

    NAS_ESM_MEM_SET_S(  pstSdfCntxtInfo->astSdfPfInfo,
                        sizeof(NAS_ESM_CONTEXT_TFT_STRU) * NAS_ESM_MAX_SDF_PF_NUM,
                        NAS_ESM_NULL,
                        sizeof(NAS_ESM_CONTEXT_TFT_STRU) * NAS_ESM_MAX_SDF_PF_NUM);

    pstSdfCntxtInfo->ulSdfPfNum = NAS_ESM_NULL;
}

/*****************************************************************************
 Function Name   : NAS_ESM_AddPacketFilterProc
 Description     : 添加SDF处理
 Input           : pstMsgIE-----------------------译码后的消息
                   pstEpsbCntxtInfo---------------承载信息
                   pstSdfCntxtInfo----------------SDF信息
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2010-2-3  Draft Enact
    2.lihong00150010      2010-5-31 Modify

*****************************************************************************/
VOS_VOID  NAS_ESM_AddPacketFilterProc
(
    const  NAS_ESM_NW_MSG_STRU         *pstMsgIE,
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo,
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo,
    VOS_UINT32                          ulStateTblIndex
)
{
    VOS_UINT32                          ulRslt              = NAS_ESM_NULL;
    VOS_UINT32                          ulCidTmp            = NAS_ESM_NULL;
    VOS_UINT32                          ulCnt               = NAS_ESM_NULL;
    VOS_UINT32                          ulLoopTimes         = NAS_ESM_NULL;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara          = VOS_NULL_PTR;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfoTmp  = VOS_NULL_PTR;
    APP_ESM_EPS_QOS_INFO_STRU          *pstEpsQosInfo       = VOS_NULL_PTR;
    APP_ESM_EPS_QOS_INFO_STRU          *pstSdfQosInfo       = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG("NAS_ESM_AddPacketFilterProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AddPacketFilterProc_ENUM, LNAS_ENTRY);

    pstStateAddr    = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    /* 若空口消息中携带的预添加的packet filter在承载下已全部存在或部分存在,
       且已存在的packet filter所属的sdf与动态表中存储的用户预操作的sdf不一致，
       则删除已存在的packet filter所属的sdf并更新承载QOS信息 */
    ulRslt = NAS_ESM_QuerySdfId(pstMsgIE, &ulCidTmp);
    if((NAS_ESM_QUERY_CID_RSLT_ALL_UNFOUND != ulRslt)
        && (ulCidTmp != pstStateAddr->ulCid))
    {
        NAS_ESM_INFO_LOG("NAS_ESM_AddPacketFilterProc:packet filter already exist in other sdf!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_AddPacketFilterProc_ENUM, ESM_packet_filter_already_exist_in_other_sdf);

        pstSdfCntxtInfoTmp = NAS_ESM_GetSdfCntxtInfo(ulCidTmp);

        pstEpsQosInfo = &pstEpsbCntxtInfo->stEpsQoSInfo.stQosInfo;
        pstSdfQosInfo = &pstSdfCntxtInfoTmp->stSdfQosInfo.stQosInfo;

        if (PS_TRUE == NAS_ESM_IsGbrBearer(pstEpsQosInfo->ucQCI))
        {
            pstEpsQosInfo->ulULMaxRate -= pstSdfQosInfo->ulULMaxRate;
            pstEpsQosInfo->ulDLMaxRate -= pstSdfQosInfo->ulDLMaxRate;
            pstEpsQosInfo->ulULGMaxRate -= pstSdfQosInfo->ulULGMaxRate;
            pstEpsQosInfo->ulDLGMaxRate -= pstSdfQosInfo->ulDLGMaxRate;
        }

        /* 删除旧SDF上下文 */
        NAS_ESM_MEM_SET_S(  pstSdfCntxtInfoTmp,
                            sizeof(NAS_ESM_SDF_CNTXT_INFO_STRU),
                            0,
                            sizeof(NAS_ESM_SDF_CNTXT_INFO_STRU));

        /* 上报APP SDF释放 */
        NAS_ESM_SndEsmAppSdfRelIndMsg(ulCidTmp, pstMsgIE->ucEpsbId);

        /* 清除承载关联的此CID */
        NAS_ESM_ClearBearCntxtLinkCid(pstMsgIE->ucEpsbId, ulCidTmp);
    }

    /* 赋值SDF关联的承载信息 */
    pstSdfCntxtInfo->ulEpsbId = pstMsgIE->ucEpsbId;

    /* 如果是专有承载，且当前SDF的PF数为0,则说明此次操作为添加SDF，因此将上报
       类型修改为NAS_ESM_APP_IND_TYPE_SETUP */
    if ((NAS_ESM_NULL == pstSdfCntxtInfo->ulSdfPfNum)
        && (NAS_ESM_BEARER_TYPE_DEDICATED == pstEpsbCntxtInfo->enBearerCntxtType))
    {
        pstStateAddr->enAppIndType = NAS_ESM_APP_IND_TYPE_SETUP;
    }

    /* 若没有找到相同的则添加，若找到相同的则替换 */
    NAS_ESM_ReplacePacketFilterProc(pstMsgIE, pstSdfCntxtInfo);

    if (NAS_ESM_PTI_UNASSIGNED_VALUE != pstStateAddr->stNwMsgRecord.ucPti)
    {
        pstSdfPara      = NAS_ESM_GetSdfParaAddr(pstStateAddr->ulCid);

        /* 如果是用户发起的,那么静态参数的数目一定大*/
        /* 于等于动态参数; 如果是网络主动发起的, 动态*/
        /* 参数要大于等于静态参数*/
        ulLoopTimes     = NAS_ESM_MIN(pstSdfCntxtInfo->ulSdfPfNum, pstSdfPara->ulPfNum);

        for (ulCnt = NAS_ESM_NULL; ulCnt < ulLoopTimes; ulCnt++)
        {
            pstSdfCntxtInfo->astSdfPfInfo[ulCnt].ucPacketFilterId =
                            pstSdfPara->astCntxtTftInfo[ulCnt].ucPacketFilterId;

        }
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_UpdatePacketFilterToSdfCntxt
 Description     : 保存承载修改消息中的TFT信息
 Input           : pstMsgIE-----------------------译码后的消息
                   pstEpsbCntxtInfo---------------承载信息
                   pstSdfCntxtInfo----------------SDF信息
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong 00150010      2009-6-18  Draft Enact
    2.lihong 00150010      2009-12-02 Modify
    3.lihong00150010       2010-02-03 Modify

*****************************************************************************/
VOS_VOID  NAS_ESM_UpdatePacketFilterToSdfCntxt
(
    const  NAS_ESM_NW_MSG_STRU         *pstMsgIE,
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo,
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo,
    VOS_UINT32                          ulStateTblIndex
)
{
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    /* 初始化上报类型为NAS_ESM_APP_IND_TYPE_MODIFY */
    pstStateAddr->enAppIndType = NAS_ESM_APP_IND_TYPE_MODIFY;

    /* 判断是否存在TFT操作 */
    if(NAS_ESM_OP_TRUE != pstMsgIE->bitOpTadInfo)
    {
        return ;
    }

    switch (pstMsgIE->stTadInfo.enTftOpType)
    {
        case NAS_ESM_TFT_OP_TYPE_ADD_FILTER :

            /* 添加packet filter */
            NAS_ESM_AddPacketFilterProc(    pstMsgIE,
                                            pstEpsbCntxtInfo,
                                            pstSdfCntxtInfo,
                                            ulStateTblIndex);
            break;

        case NAS_ESM_TFT_OP_TYPE_REPLACE_FILTER:

            /* 修改packet filter */
            NAS_ESM_ReplacePacketFilterProc(pstMsgIE, pstSdfCntxtInfo);
            break;

        case NAS_ESM_TFT_OP_TYPE_DELETE_FILTER:

            /* 删除SDF上下文并修改承载QOS信息 */
            NAS_ESM_DeletePacketFilterProc( pstMsgIE,
                                            pstEpsbCntxtInfo,
                                            pstSdfCntxtInfo,
                                            ulStateTblIndex);
            break;

        case NAS_ESM_TFT_OP_TYPE_CREATE_TFT:

            /* 创建TFT */
            NAS_ESM_CreateTftProc(pstMsgIE, pstSdfCntxtInfo);
            break;

        case NAS_ESM_TFT_OP_TYPE_DELETE_TFT:

            /* 删除TFT */
            NAS_ESM_DeleteTftProc(pstSdfCntxtInfo);
            break;

       default:
            break;
    }

    return;

}

/*****************************************************************************
 Function Name   : NAS_ESM_UpdateEpsQosInfo
 Description     : 保存承载修改消息中的QOS信息
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong 00150010      2009-6-18  Draft Enact
    2.lihong 00150010      2009-12-02 Modify
    3.lihong 00150010      2009-03-18 Modify

*****************************************************************************/
VOS_VOID  NAS_ESM_UpdateEpsQosInfo
(
    const  NAS_ESM_NW_MSG_STRU         *pstMsgIE,
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo,
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo
)
{
    /* 如果不带QOS */
    if( NAS_ESM_OP_TRUE != pstMsgIE->bitOpEpsQos)
    {
        /* 对于NON-GBR承载，当收到网侧的承载修改请求，TAD码为ADD SDF，且不带QOS信息时,
           将承载QOS信息中的QCI赋值给新增SDF的QCI*/
        if ((PS_FALSE == NAS_ESM_IsGbrBearer(pstEpsbCntxtInfo->stEpsQoSInfo.stQosInfo.ucQCI))
          && (NAS_ESM_OP_TRUE == pstMsgIE->bitOpTadInfo)
          && (NAS_ESM_TFT_OP_TYPE_ADD_FILTER == pstMsgIE->stTadInfo.enTftOpType))
        {
            NAS_ESM_MEM_SET_S(  &pstSdfCntxtInfo->stSdfQosInfo,
                                sizeof (NAS_ESM_CONTEXT_LTE_QOS_STRU),
                                NAS_ESM_NULL,
                                sizeof (NAS_ESM_CONTEXT_LTE_QOS_STRU));

            /* 更新SDF的QCI信息 */
            pstSdfCntxtInfo->stSdfQosInfo.stQosInfo.ucQCI =
                        pstEpsbCntxtInfo->stEpsQoSInfo.stQosInfo.ucQCI;

            pstSdfCntxtInfo->stSdfQosInfo.ucNwQCI =
                        pstEpsbCntxtInfo->stEpsQoSInfo.ucNwQCI;

        }

        return ;
    }

    /* 若此SDF的packet filter被全部删除，则返回，因为此情况下承载QOS的更新
       已经在函数NAS_ESM_DeletePacketFilterProc完成了 */
    if ((NAS_ESM_OP_TRUE == pstMsgIE->bitOpTadInfo)
     && (NAS_ESM_TFT_OP_TYPE_DELETE_FILTER == pstMsgIE->stTadInfo.enTftOpType)
     && (NAS_ESM_NULL == pstSdfCntxtInfo->ulSdfPfNum))
    {
        return ;
    }

    /* 更新SDF的QCI信息 */
    pstSdfCntxtInfo->stSdfQosInfo.stQosInfo.ucQCI =
                      pstMsgIE->stSdfQosInfo.stQosInfo.ucQCI;

    pstSdfCntxtInfo->stSdfQosInfo.ucNwQCI =
                      pstMsgIE->stSdfQosInfo.ucNwQCI;

    /* 如果是GBR承载，则需更新速率信息 */
    if (PS_TRUE == NAS_ESM_IsGbrBearer(pstEpsbCntxtInfo->stEpsQoSInfo.stQosInfo.ucQCI))
    {
        /* 修改SDF的QOS */
        NAS_ESM_ModEpsQos(&(pstEpsbCntxtInfo->stEpsQoSInfo.stQosInfo), \
                          &pstMsgIE->stSdfQosInfo.stQosInfo, \
                          &(pstSdfCntxtInfo->stSdfQosInfo.stQosInfo));

        /*设置EPS QOS标识位和EPS QOS内容*/
        pstEpsbCntxtInfo->bitOpEpsQos = NAS_ESM_OP_TRUE;

        NAS_ESM_MEM_CPY_S(  &(pstEpsbCntxtInfo->stEpsQoSInfo),
                            sizeof(NAS_ESM_CONTEXT_LTE_QOS_STRU),
                            &pstMsgIE->stSdfQosInfo,
                            sizeof(NAS_ESM_CONTEXT_LTE_QOS_STRU));
    }
}
/*****************************************************************************
 Function Name   : NAS_ESM_SndEsmAppSdfRelCnfFailMsg
 Description     :
 Input           : VOS_UINT32 ulEpsbId
                   VOS_UINT32 ulErrorCode
                   NAS_ESM_CAUSE_ENUM_UINT8 enEsmCause
 Output          : None
 Return          : VOS_VOID

 History         :
    1.丁丽 00128736      2008-9-25  Draft Enact
    2.祝义强 00138739    2009-2-13  Modify

*****************************************************************************/
VOS_VOID NAS_ESM_SndEsmAppSdfRelCnfFailMsg
(
    VOS_UINT32                          ulStateTblIndex,
    VOS_UINT32                          ulErrorCode
)
{
    NAS_ESM_APP_CNF_MSG_STRU            stEsmAppCnfMsg;
    NAS_ESM_STATE_INFO_STRU            *pStateTblAddr      =VOS_NULL_PTR;

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_SndEsmAppSdfRelCnfFailMsg is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_SndEsmAppSdfRelCnfFailMsg_ENUM, LNAS_ENTRY);

    /*清空*/
    NAS_ESM_MEM_SET_S(  (VOS_VOID*)&stEsmAppCnfMsg,
                        sizeof(NAS_ESM_APP_CNF_MSG_STRU),
                        0,
                        sizeof(NAS_ESM_APP_CNF_MSG_STRU));

    /*向APP发送ID_APP_ESM_PDP_RELEASE_CNF(失败)消息*/
    /*获得本地StateTbl指针,此时动态表还没有释放*/
    pStateTblAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    /*取出本地动态表参数*/
    stEsmAppCnfMsg.bitOpEpsbId = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.ulEpsbId = pStateTblAddr->ulEpsbId;

    /*取出CID*/
    stEsmAppCnfMsg.bitOpCId = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.ulCId = pStateTblAddr->ulCid;

    /*取出opid*/
    stEsmAppCnfMsg.bitOpOpId = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.ulOpId = pStateTblAddr->stAppMsgRecord.ulAppMsgOpId;

    /*取出MID*/
    stEsmAppCnfMsg.bitOpMid = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.usOriginalId = pStateTblAddr->stAppMsgRecord.usOriginalId;
    stEsmAppCnfMsg.usTerminalId = pStateTblAddr->stAppMsgRecord.usTerminalId;

    /*承载释放结果*/
    stEsmAppCnfMsg.ulRst = NAS_ESM_FAILURE;

    stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.ulErrorCode = ulErrorCode;

    NAS_ESM_SndEsmAppSdfRelCnfMsg(&stEsmAppCnfMsg);
}

/*****************************************************************************
 Function Name   : NAS_ESM_SndEsmAppSdfRelCnfSuccMsg
 Description     :
 Input           : VOS_UINT32 ulEpsbId
 Output          : None
 Return          : VOS_VOID

 History         :
    1.丁丽 00128736      2008-9-25  Draft Enact
    2.祝义强 00138739    2009-2-13  Modify
*****************************************************************************/
VOS_VOID NAS_ESM_SndEsmAppSdfRelCnfSuccMsg(   VOS_UINT32 ulStateTblIndex)
{
    NAS_ESM_APP_CNF_MSG_STRU            stEsmAppCnfMsg;
    NAS_ESM_STATE_INFO_STRU            *pStateTblAddr      =VOS_NULL_PTR;

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_SndEsmAppSdfRelCnfSuccMsg is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_SndEsmAppSdfRelCnfSuccMsg_ENUM, LNAS_ENTRY);

    /*清空*/
    NAS_ESM_MEM_SET_S(  (VOS_VOID*)&stEsmAppCnfMsg,
                        sizeof(NAS_ESM_APP_CNF_MSG_STRU),
                        0,
                        sizeof(NAS_ESM_APP_CNF_MSG_STRU));

    /*向APP发送ID_APP_ESM_PDP_RELEASE_CNF(成功)消息*/
    /*获得本地StateTbl指针,此时动态表还没有释放*/
    pStateTblAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    /*取得当前承载号*/
    stEsmAppCnfMsg.bitOpEpsbId = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.ulEpsbId = pStateTblAddr->ulEpsbId;

    /*取出CID*/
    stEsmAppCnfMsg.bitOpCId = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.ulCId = pStateTblAddr->ulCid;

    /*取出opid*/
    stEsmAppCnfMsg.bitOpOpId = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.ulOpId = pStateTblAddr->stAppMsgRecord.ulAppMsgOpId;

    /*取出MID*/
    stEsmAppCnfMsg.bitOpMid = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.usOriginalId = pStateTblAddr->stAppMsgRecord.usOriginalId;
    stEsmAppCnfMsg.usTerminalId = pStateTblAddr->stAppMsgRecord.usTerminalId;

    /*承载释放结果*/
    stEsmAppCnfMsg.ulRst = NAS_ESM_SUCCESS;

    /*错误码*/
    stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_FALSE;


    NAS_ESM_SndEsmAppSdfRelCnfMsg(&stEsmAppCnfMsg);
}

/*****************************************************************************
 Function Name   : NAS_ESM_SndEsmAppSdfSetupCnfSuccMsg
 Description     :
 Input           : VOS_UINT32 ulEpsbId
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.丁丽 00128736      2008-9-25  Draft Enact
    2.祝义强 00138739    2009-2-13  Modify
*****************************************************************************/
VOS_VOID NAS_ESM_SndEsmAppSdfSetupCnfSuccMsg(   VOS_UINT32 ulStateTblIndex)
{
    NAS_ESM_APP_CNF_MSG_STRU            stEsmAppCnfMsg;
    NAS_ESM_STATE_INFO_STRU            *pStateTblAddr       = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo    = VOS_NULL_PTR;

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_SndEsmAppSdfSetupCnfSuccMsg is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_SndEsmAppSdfSetupCnfSuccMsg_ENUM, LNAS_ENTRY);

    /*清空*/
    NAS_ESM_MEM_SET_S(  (VOS_VOID*)&stEsmAppCnfMsg,
                        sizeof(NAS_ESM_APP_CNF_MSG_STRU),
                        0,
                        sizeof(NAS_ESM_APP_CNF_MSG_STRU));

    /*向APP发送ID_APP_ESM_PDP_SETUP_CNF(成功)消息*/
    /*获得本地StateTbl指针,此时动态表还没有释放*/
    pStateTblAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    /*取出本地动态表参数*/
    stEsmAppCnfMsg.bitOpEpsbId = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.ulEpsbId = pStateTblAddr->ulEpsbId;

    /*取出CID*/
    stEsmAppCnfMsg.bitOpCId = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.ulCId = pStateTblAddr->ulCid;

    /*取出opid*/
    stEsmAppCnfMsg.bitOpOpId = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.ulOpId = pStateTblAddr->stAppMsgRecord.ulAppMsgOpId;

    /*取出MID*/
    stEsmAppCnfMsg.bitOpMid = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.usOriginalId = pStateTblAddr->stAppMsgRecord.usOriginalId;
    stEsmAppCnfMsg.usTerminalId = pStateTblAddr->stAppMsgRecord.usTerminalId;

    /*承载建立结果*/
    stEsmAppCnfMsg.ulRst = NAS_ESM_SUCCESS;

    /*原因码*/
    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(pStateTblAddr->ulEpsbId);

    if( NAS_ESM_OP_TRUE == pstEpsbCntxtInfo->bitOpEsmCause)
    {
        /*如果承载信息中有原因码，则通知APP*/
        stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
        stEsmAppCnfMsg.ulErrorCode    = NAS_ESM_GetAppErrorByEsmCause(pstEpsbCntxtInfo->enEsmCau);
    }
    else
    {
        stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_FALSE;
    }

    NAS_ESM_SndEsmAppSdfSetupCnfMsg(&stEsmAppCnfMsg);

    NAS_ESM_SndEsmAppBearerQosIndMsg(pStateTblAddr->ulEpsbId);

}

/*****************************************************************************
 Function Name   : NAS_ESM_SndEsmAppSdfSetupCnfFailMsg
 Description     :
 Input           : VOS_UINT32 ulStateTblIndex
                   VOS_UINT32 ulErrorCode
 Output          : None
 Return          : VOS_VOID

 History         :
    1.丁丽 00128736      2008-9-25  Draft Enact
    2.祝义强 00138739    2009-2-13  Modify
*****************************************************************************/
VOS_VOID NAS_ESM_SndEsmAppSdfSetupCnfFailMsg
(
    VOS_UINT32                          ulStateTblIndex,
    VOS_UINT32                          ulErrorCode
)
{
    NAS_ESM_APP_CNF_MSG_STRU            stEsmAppCnfMsg;
    NAS_ESM_STATE_INFO_STRU             *pStateTblAddr      =VOS_NULL_PTR;

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_SndEsmAppSdfSetupCnfFailMsg is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_SndEsmAppSdfSetupCnfFailMsg_ENUM, LNAS_ENTRY);

    /*清空*/
    NAS_ESM_MEM_SET_S(  (VOS_VOID*)&stEsmAppCnfMsg,
                        sizeof(NAS_ESM_APP_CNF_MSG_STRU),
                        0,
                        sizeof(NAS_ESM_APP_CNF_MSG_STRU));

    /*向APP发送ID_APP_ESM_PDP_SETUP_CNF(失败)消息*/
    /*获得本地StateTbl指针,此时动态表还没有释放*/
    pStateTblAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    /*取出CID*/
    stEsmAppCnfMsg.bitOpCId = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.ulCId = pStateTblAddr->ulCid;

    /*取出opid*/
    stEsmAppCnfMsg.bitOpOpId = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.ulOpId = pStateTblAddr->stAppMsgRecord.ulAppMsgOpId;

    /*取出MID*/
    stEsmAppCnfMsg.bitOpMid = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.usOriginalId = pStateTblAddr->stAppMsgRecord.usOriginalId;
    stEsmAppCnfMsg.usTerminalId = pStateTblAddr->stAppMsgRecord.usTerminalId;

    /*承载建立结果*/
    stEsmAppCnfMsg.ulRst = NAS_ESM_FAILURE;

    /*错误码*/
    stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.ulErrorCode = ulErrorCode;

    NAS_ESM_SndEsmAppSdfSetupCnfMsg(&stEsmAppCnfMsg);

}


VOS_VOID NAS_ESM_SndEsmAppNdisConnCnfSuccMsg(   VOS_UINT32 ulStateTblIndex)
{
    NAS_ESM_APP_CNF_MSG_STRU            stEsmAppCnfMsg;
    NAS_ESM_STATE_INFO_STRU            *pStateTblAddr       = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo    = VOS_NULL_PTR;

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_SndEsmAppNdisConnCnfSuccMsg is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_SndEsmAppNdisConnCnfSuccMsg_ENUM, LNAS_ENTRY);

    /*清空*/
    NAS_ESM_MEM_SET_S(  (VOS_VOID*)&stEsmAppCnfMsg,
                        sizeof(NAS_ESM_APP_CNF_MSG_STRU),
                        0,
                        sizeof(NAS_ESM_APP_CNF_MSG_STRU));

    /*向APP发送ID_APP_ESM_PDP_SETUP_CNF(成功)消息*/
    /*获得本地StateTbl指针,此时动态表还没有释放*/
    pStateTblAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    /*取出本地动态表参数*/
    stEsmAppCnfMsg.bitOpEpsbId = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.ulEpsbId = pStateTblAddr->ulEpsbId;

    /*取出CID*/
    stEsmAppCnfMsg.bitOpCId = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.ulCId = pStateTblAddr->ulCid;

    /*取出opid*/
    stEsmAppCnfMsg.bitOpOpId = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.ulOpId = pStateTblAddr->stAppMsgRecord.ulAppMsgOpId;

    /*取出MID*/
    stEsmAppCnfMsg.bitOpMid = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.usOriginalId = pStateTblAddr->stAppMsgRecord.usOriginalId;
    stEsmAppCnfMsg.usTerminalId = pStateTblAddr->stAppMsgRecord.usTerminalId;

    /*承载建立结果*/
    stEsmAppCnfMsg.ulRst = NAS_ESM_SUCCESS;

    /*原因码*/
    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(pStateTblAddr->ulEpsbId);

    if( NAS_ESM_OP_TRUE == pstEpsbCntxtInfo->bitOpEsmCause)
    {
        /*如果承载信息中有原因码，则通知APP*/
        stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
        stEsmAppCnfMsg.ulErrorCode    = NAS_ESM_GetAppErrorByEsmCause(pstEpsbCntxtInfo->enEsmCau);
    }
    else
    {
        stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_FALSE;
    }

    NAS_ESM_SndEsmAppNdisConnCnfMsg(&stEsmAppCnfMsg);

    NAS_ESM_SndEsmAppBearerQosIndMsg(pStateTblAddr->ulEpsbId);

}


VOS_VOID NAS_ESM_SndEsmAppNdisConnCnfFailMsg
(
    VOS_UINT32                          ulStateTblIndex,
    VOS_UINT32                          ulErrorCode
)
{
    NAS_ESM_APP_CNF_MSG_STRU            stEsmAppCnfMsg;
    NAS_ESM_STATE_INFO_STRU             *pStateTblAddr      =VOS_NULL_PTR;

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_SndEsmAppNdisConnCnfFailMsg is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_SndEsmAppNdisConnCnfFailMsg_ENUM, LNAS_ENTRY);

    /*清空*/
    NAS_ESM_MEM_SET_S(  (VOS_VOID*)&stEsmAppCnfMsg,
                        sizeof(NAS_ESM_APP_CNF_MSG_STRU),
                        0,
                        sizeof(NAS_ESM_APP_CNF_MSG_STRU));

    /*向APP发送ID_APP_ESM_PDP_SETUP_CNF(失败)消息*/
    /*获得本地StateTbl指针,此时动态表还没有释放*/
    pStateTblAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    /*取出CID*/
    stEsmAppCnfMsg.bitOpCId = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.ulCId = pStateTblAddr->ulCid;

    /*取出opid*/
    stEsmAppCnfMsg.bitOpOpId = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.ulOpId = pStateTblAddr->stAppMsgRecord.ulAppMsgOpId;

    /*取出MID*/
    stEsmAppCnfMsg.bitOpMid = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.usOriginalId = pStateTblAddr->stAppMsgRecord.usOriginalId;
    stEsmAppCnfMsg.usTerminalId = pStateTblAddr->stAppMsgRecord.usTerminalId;

    /*承载建立结果*/
    stEsmAppCnfMsg.ulRst = NAS_ESM_FAILURE;

    /*错误码*/
    stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.ulErrorCode = ulErrorCode;

    NAS_ESM_SndEsmAppNdisConnCnfMsg(&stEsmAppCnfMsg);

}


/*****************************************************************************
 Function Name   : NAS_ESM_SndEsmAppSdfModCnfSuccMsg
 Description     :
 Input           : VOS_UINT32 ulEpsbId
                   NAS_ESM_CAUSE_ENUM_UINT8    enEsmCause
 Output          : None
 Return          : VOS_VOID

 History         :
    1.丁丽 00128736      2008-9-25  Draft Enact
    2.祝义强 00138739    2009-2-13  Modify
*****************************************************************************/
VOS_VOID NAS_ESM_SndEsmAppSdfModCnfSuccMsg
(
    VOS_UINT32                          ulStateTblIndex,
    APP_ESM_BEARER_MODIFY_ENUM_UINT32   enModfyType
)
{
    NAS_ESM_APP_CNF_MSG_STRU            stEsmAppCnfMsg;
    NAS_ESM_STATE_INFO_STRU            *pStateTblAddr       = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo    = VOS_NULL_PTR;

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_SndEsmAppSdfModCnfSuccMsg is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_SndEsmAppSdfModCnfSuccMsg_ENUM, LNAS_ENTRY);

    /*清空*/
    NAS_ESM_MEM_SET_S(  (VOS_VOID*)&stEsmAppCnfMsg,
                        sizeof(NAS_ESM_APP_CNF_MSG_STRU),
                        0,
                        sizeof(NAS_ESM_APP_CNF_MSG_STRU));

    /*获得本地StateTbl指针,此时动态表还没有释放*/
    pStateTblAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    /*取出本地动态表参数*/
    stEsmAppCnfMsg.bitOpEpsbId = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.ulEpsbId = pStateTblAddr->ulEpsbId;

    /*取出CID*/
    stEsmAppCnfMsg.bitOpCId = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.ulCId = pStateTblAddr->ulCid;

    /*取出opid*/
    stEsmAppCnfMsg.bitOpOpId = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.ulOpId = pStateTblAddr->stAppMsgRecord.ulAppMsgOpId;

    /*取出MID*/
    stEsmAppCnfMsg.bitOpMid = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.usOriginalId = pStateTblAddr->stAppMsgRecord.usOriginalId;
    stEsmAppCnfMsg.usTerminalId = pStateTblAddr->stAppMsgRecord.usTerminalId;

    /* 取出修改类型 */
    stEsmAppCnfMsg.bitOpModifyType = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.enModfyType = enModfyType;

    /*承载建立结果*/
    stEsmAppCnfMsg.ulRst = NAS_ESM_SUCCESS;

    /*原因码*/
    /* hongli 修改消息中不可能带Esm Cause,可以删除下面代码*/
    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(pStateTblAddr->ulEpsbId);
    if( NAS_ESM_OP_TRUE == pstEpsbCntxtInfo->bitOpEsmCause)
    {
        /*如果承载信息中有原因码，则通知APP*/
        stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
        stEsmAppCnfMsg.ulErrorCode    = NAS_ESM_GetAppErrorByEsmCause(pstEpsbCntxtInfo->enEsmCau);
    }
    else
    {
        stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_FALSE;
    }

    NAS_ESM_SndEsmAppSdfModCnfMsg(&stEsmAppCnfMsg);

}

/*****************************************************************************
 Function Name   : NAS_ESM_SndEsmAppSdfModCnfFailMsg
 Description     :
 Input           : VOS_UINT32                          ulStateTblIndex
                   VOS_UINT32                          ulErrorCode
 Output          : None
 Return          : VOS_VOID

 History         :
    1.丁丽 00128736      2008-9-25  Draft Enact
    2.祝义强 00138739    2009-2-13  Modify
*****************************************************************************/
VOS_VOID NAS_ESM_SndEsmAppSdfModCnfFailMsg
(
    VOS_UINT32                          ulStateTblIndex,
    VOS_UINT32                          ulErrorCode
)
{
    NAS_ESM_APP_CNF_MSG_STRU            stEsmAppCnfMsg;
    NAS_ESM_STATE_INFO_STRU             *pStateTblAddr      =VOS_NULL_PTR;

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_SndEsmAppSdfModCnfFailMsg is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_SndEsmAppSdfModCnfFailMsg_ENUM, LNAS_ENTRY);

    /*清空*/
    NAS_ESM_MEM_SET_S(  (VOS_VOID*)&stEsmAppCnfMsg,
                        sizeof(NAS_ESM_APP_CNF_MSG_STRU),
                        0,
                        sizeof(NAS_ESM_APP_CNF_MSG_STRU));

    /*获得本地StateTbl指针,此时动态表还没有释放*/
    pStateTblAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    /*取出CID*/
    stEsmAppCnfMsg.bitOpCId = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.ulCId = pStateTblAddr->ulCid;

    /*取出opid*/
    stEsmAppCnfMsg.bitOpOpId = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.ulOpId = pStateTblAddr->stAppMsgRecord.ulAppMsgOpId;

    /*取出MID*/
    stEsmAppCnfMsg.bitOpMid = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.usOriginalId = pStateTblAddr->stAppMsgRecord.usOriginalId;
    stEsmAppCnfMsg.usTerminalId = pStateTblAddr->stAppMsgRecord.usTerminalId;

    /*承载建立结果*/
    stEsmAppCnfMsg.ulRst = NAS_ESM_FAILURE;

    /*错误码*/
    stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.ulErrorCode = ulErrorCode;

    NAS_ESM_SndEsmAppSdfModCnfMsg(&stEsmAppCnfMsg);

}

/*****************************************************************************
 Function Name   : NAS_ESM_SndSmEspBearerMdfIndMsg
 Description     : 向SM发送承载修改消息
 Input           : ucEpsbId-----------------承载号
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2011-04-30  Draft Enact

*****************************************************************************/
/*lint -specific(-e433)*/
VOS_VOID NAS_ESM_SndSmEspBearerMdfIndMsg
(
    VOS_UINT32                          ulEpsbId
)
{
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo   = VOS_NULL_PTR;
    SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearInfoInd  = VOS_NULL_PTR;

    /*分配空间并检验分配是否成功*/
    /*lint -e433 -e826*/
    pstEpsBearInfoInd = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(SM_ESM_EPS_BEARER_INFO_IND_STRU));
    /*lint +e433 +e826*/
    if ( VOS_NULL_PTR == pstEpsBearInfoInd )
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndSmEspBearerMdfIndMsg:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndSmEspBearerMdfIndMsg_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*清空*/
    NAS_ESM_MEM_SET_S(  NAS_ESM_GET_MSG_ENTITY(pstEpsBearInfoInd),
                        NAS_ESM_GET_MSG_LENGTH(pstEpsBearInfoInd),
                        0,
                        NAS_ESM_GET_MSG_LENGTH(pstEpsBearInfoInd));

    /*获取对应EpsbCntxtTbl表地址*/
    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);

    pstEpsBearInfoInd->enPdpOption  = SM_ESM_PDP_OPT_MODIFY;
    pstEpsBearInfoInd->ulEpsbId     = ulEpsbId;

    /* 赋值承载信息 */
    NAS_ESM_SetEpsBearInfo(pstEpsbCntxtInfo, pstEpsBearInfoInd);

    /*填写消息头*/
    NAS_ESM_WRITE_SM_MSG_HEAD(pstEpsBearInfoInd, ID_ESM_SM_EPS_BEARER_INFO_IND);

    /* 调用消息发送函数 */
    NAS_ESM_SND_MSG(pstEpsBearInfoInd);
}

/*****************************************************************************
 Function Name   : NAS_ESM_SndSmEspBearerDeactIndMsg
 Description     : 向SM发送承载去激活消息
 Input           : ucEpsbId-----------------承载号
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2011-04-30  Draft Enact

*****************************************************************************/

VOS_VOID NAS_ESM_SndSmEspBearerDeactIndMsg
(
    VOS_UINT32                          ulEpsbId
)
{
    SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearInfoInd  = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo   = VOS_NULL_PTR;

    /*分配空间并检验分配是否成功*/
    /*lint -e433 -e826*/
    pstEpsBearInfoInd = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(SM_ESM_EPS_BEARER_INFO_IND_STRU));
    /*lint +e433 +e826*/
    if ( VOS_NULL_PTR == pstEpsBearInfoInd )
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndSmEspBearerDeactIndMsg:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndSmEspBearerDeactIndMsg_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*获取对应EpsbCntxtTbl表地址*/
    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);

    /*清空*/
    NAS_ESM_MEM_SET_S(  NAS_ESM_GET_MSG_ENTITY(pstEpsBearInfoInd),
                        NAS_ESM_GET_MSG_LENGTH(pstEpsBearInfoInd),
                        0,
                        NAS_ESM_GET_MSG_LENGTH(pstEpsBearInfoInd));

    pstEpsBearInfoInd->enPdpOption  = SM_ESM_PDP_OPT_DEACTIVATE;
    pstEpsBearInfoInd->ulEpsbId     = ulEpsbId;

    pstEpsBearInfoInd->ulBitCid     = pstEpsbCntxtInfo->ulBitCId;

    /* 赋值transaction id */
    pstEpsBearInfoInd->bitOpTransId = pstEpsbCntxtInfo->bitOpTransId;

    NAS_ESM_MEM_CPY_S(  &pstEpsBearInfoInd->stTransId,
                        sizeof(NAS_ESM_CONTEXT_TRANS_ID_STRU),
                        &pstEpsbCntxtInfo->stTransId,
                        sizeof(NAS_ESM_CONTEXT_TRANS_ID_STRU));

    /*填写消息头*/
    NAS_ESM_WRITE_SM_MSG_HEAD(pstEpsBearInfoInd, ID_ESM_SM_EPS_BEARER_INFO_IND);

    /* 调用消息发送函数 */
    NAS_ESM_SND_MSG(pstEpsBearInfoInd);
}
/*lint -specific(+e433)*/

/*****************************************************************************
 Function Name   : NAS_ESM_DeactBearerAndInformApp
 Description     : 本地去激活某一缺省承载以及与其关联的专有承载，并通知相关模块
 Input           : VOS_UINT32 ulEpsbId
 Output          : None
 Return          : None

 History         :
    1.丁丽 00128736      2008-9-25  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_DeactBearerAndInformApp(   VOS_UINT32 ulEpsbId )
{
    VOS_UINT8                           ucCnt            =  NAS_ESM_NULL;
    VOS_UINT32                          ulCurPdnNum      =  NAS_ESM_NULL;
    VOS_UINT32                          ulEpsbIdNum      =  NAS_ESM_NULL;
    VOS_UINT32                          ulStateTblIndex  =  NAS_ESM_NULL;
    VOS_UINT32                          aulEpsbId[NAS_ESM_MAX_EPSB_NUM]  = {NAS_ESM_NULL};
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo = VOS_NULL_PTR;

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG1("NAS_ESM_DeactBearerAndInformApp is entered.", ulEpsbId);
    TLPS_PRINT2LAYER_INFO1(NAS_ESM_DeactBearerAndInformApp_ENUM, LNAS_ENTRY, ulEpsbId);

    /* L4A重构, GU要求BEARER_INFO_IND在Rel Cnf之前 */

    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);

    /*如果当前承载为缺省承载*/
    if(PS_TRUE == NAS_ESM_IsDefaultEpsBearerType(pstEpsbCntxtInfo->enBearerCntxtType))
    {
        /*查找当前PDN连接数*/
        ulCurPdnNum = NAS_ESM_GetCurPdnNum();

        /*PDN连接数减少1条*/
        if(ulCurPdnNum > 0)
        {
            ulCurPdnNum -= 1;
        }

        /*保存当前PDN连接数*/
        NAS_ESM_SetCurPdnNum(ulCurPdnNum);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

        /* 支持EHRPD接入技术，通知EHSM承载释放，给EHSM只支持同步缺省承载，因此专有承载不必处理 */
        if (NAS_ESM_SUCCESS == NAS_EMM_IsEhrpdOr1XRatExist())
        {
            NAS_ESM_SndEhsmSyncPdnInfoDisconnIndMsg(ulEpsbId);
        }
#endif
    }

    /*更新ulEpsbIdNum、aulEpsbId，以便通知RABM*/
    aulEpsbId[ulEpsbIdNum++] = ulEpsbId;

    /*循环承载信息，查找与此承载关联的专有承载*/
    for( ucCnt = NAS_ESM_MIN_EPSB_ID; ucCnt <= NAS_ESM_MAX_EPSB_ID; ucCnt++ )
    {
        pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ucCnt);

        /*某一承载的Linked EPSB ID为当前承载ID*/
        if( (NAS_ESM_BEARER_TYPE_DEDICATED == pstEpsbCntxtInfo->enBearerCntxtType)
            && (NAS_ESM_BEARER_STATE_ACTIVE == pstEpsbCntxtInfo->enBearerCntxtState)\
            && (pstEpsbCntxtInfo->ulLinkedEpsbId == ulEpsbId) )
        {
            /* L4A重构, GU要求BEARER_INFO_IND在Rel Cnf之前 */

            /*更新ulEpsbIdNum、aulEpsbId，以便通知RABM*/
            aulEpsbId[ulEpsbIdNum++] = ucCnt;
        }
    }

    /*通知RABM，向RABM发送ID_ESM_ERABM_DEACT_IND*/
    NAS_ESM_SndEsmRabmDeactIndMsg(ulEpsbIdNum, aulEpsbId, ESM_ERABM_BEARER_RAT_LTE);

    /*根据已记录的承载ID，循环释放承载资源*/
    for( ucCnt = 0; ucCnt < ulEpsbIdNum; ucCnt++ )
    {
        /*关键事件上报*/
        NAS_ESM_SndKeyEventReportInd(NAS_ESM_EVENT_BEARER_RELEASE(aulEpsbId[ucCnt]));

        NAS_ESM_SndSmEspBearerDeactIndMsg(aulEpsbId[ucCnt]);

        /* L4A重构, GU要求BEARER_INFO_IND在Rel Cnf之前 */
        /*通知APP承载释放*/
        NAS_ESM_InformAppBearerRel(aulEpsbId[ucCnt]);

        /* 清除和中止与ulEpsbId关联的流程信息, 原有逻辑相关专有承载调用状态表资源释放 */
        if((ulEpsbId != aulEpsbId[ucCnt] ) && (NAS_ESM_SUCCESS == NAS_ESM_QueryStateTblIndexByEpsbId(aulEpsbId[ucCnt], &ulStateTblIndex)))
        {
            NAS_ESM_RelStateTblResource(ulStateTblIndex);
        }

        /*释放承载资源*/
        NAS_ESM_ClearEsmBearerResource(aulEpsbId[ucCnt]);
    }

}

/*****************************************************************************
 Function Name   : NAS_ESM_GetBearModifyType
 Description     : 获取专有承载修改类型
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2010-5-25  Draft Enact

*****************************************************************************/
APP_ESM_BEARER_MODIFY_ENUM_UINT32  NAS_ESM_GetBearModifyType
(
    const  NAS_ESM_NW_MSG_STRU *pstMsgIE
)
{

    if(NAS_ESM_OP_TRUE != pstMsgIE->bitOpTadInfo)
    {
        return APP_ESM_BEARER_MODIFY_QOS;
    }

    if (NAS_ESM_TFT_OP_TYPE_NO_OP == pstMsgIE->stTadInfo.enTftOpType)
    {
        return APP_ESM_BEARER_MODIFY_QOS;
    }

    if(NAS_ESM_OP_TRUE == pstMsgIE->bitOpEpsQos)
    {
        return APP_ESM_BEARER_MODIFY_TFT_QOS;
    }
    else
    {
        return APP_ESM_BEARER_MODIFY_TFT;
    }
}

/*****************************************************************************
 Function Name   : IsLocalPortRangSameToSinglePort
 Description     : 判断是否存在将只包含一个端口号的端口范围归并为
                   单一端口的情况
 Input           : pstTFT1
                   pstTFT2
 Output          : None
 Return          :
                   NAS_ESM_SUCCESS -- 是端口范围归并为单一端口的情况
                   NAS_ESM_FAILURE -- 不是端口范围归并为单一端口的情况

 History         :
    1.liuwenyu 143951      2010-1-21  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_ESM_IsLocalPortRangeSameToSinglePort
(
    const NAS_ESM_CONTEXT_TFT_STRU              *pstTFT1,
    const NAS_ESM_CONTEXT_TFT_STRU              *pstTFT2
)
{
    if ((NAS_ESM_OP_TRUE == pstTFT1->bitOpSingleLocalPort)
     && (NAS_ESM_OP_TRUE == pstTFT2->bitOpLocalPortRange)
     && (pstTFT2->usLcPortHighLimit == pstTFT2->usLcPortLowLimit)
     && (pstTFT1->usSingleLcPort == pstTFT2->usLcPortHighLimit))
    {
        /* CN 会将只包含一个端口号的端口范围归并为单一端口 */
        return NAS_ESM_SUCCESS;
    }
    else
    {
        return NAS_ESM_FAILURE;
    }

}

/*****************************************************************************
 Function Name   : IsLocalPortRangSameToSinglePort
 Description     : 判断是否存在将只包含一个端口号的端口范围归并为
                   单一端口的情况
 Input           : pstTFT1
                   pstTFT2
 Output          : None
 Return          :
                   NAS_ESM_SUCCESS -- 是端口范围归并为单一端口的情况
                   NAS_ESM_FAILURE -- 不是端口范围归并为单一端口的情况

 History         :
    1.liuwenyu 143951      2010-1-21  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_ESM_IsRemotePortRangeSameToSinglePort
(
    const NAS_ESM_CONTEXT_TFT_STRU              *pstTFT1,
    const NAS_ESM_CONTEXT_TFT_STRU              *pstTFT2
)
{
    if ((NAS_ESM_OP_TRUE == pstTFT1->bitOpSingleRemotePort)
      &&(NAS_ESM_OP_TRUE == pstTFT2->bitOpRemotePortRange)
      &&(pstTFT2->usRmtPortHighLimit == pstTFT2->usRmtPortLowLimit)
      &&(pstTFT1->usSingleRmtPort == pstTFT2->usRmtPortHighLimit))
    {
        /* CN 会将只包含一个端口号的端口范围归并为单一端口 */
        return NAS_ESM_SUCCESS;
    }
    else
    {
        return NAS_ESM_FAILURE;
    }

}
/*****************************************************************************
 Function Name   : NAS_ESM_MatchIpAddrandMask
 Description     : 匹配TFT数据项Ip地址和子网掩码
 Input           : pstNwTFT -- 网侧的TFT信息
                   pstUeTFT -- Ue的TFT信息
 Output          : None
 Return          :
                   NAS_ESM_SUCCESS -- Ip地址和子网掩码相同
                   NAS_ESM_FAILURE -- Ip地址或子网掩码不相同
  History         :
    1.liuwenyu00143951      2009-12-15  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_ESM_MatchIpAddrandMask
(
    const NAS_ESM_CONTEXT_TFT_STRU              *pstPf1,
    const NAS_ESM_CONTEXT_TFT_STRU              *pstPf2
)
{
    VOS_INT32                           lMatchRslt = NAS_ESM_FAILURE;

    if ((pstPf1->bitOpRmtIpv4AddrAndMask != pstPf2->bitOpRmtIpv4AddrAndMask)
     || (pstPf1->bitOpRmtIpv6AddrAndMask != pstPf2->bitOpRmtIpv6AddrAndMask))
    {
        return NAS_ESM_FAILURE;
    }

    if (NAS_ESM_OP_TRUE == pstPf1->bitOpRmtIpv4AddrAndMask)
    {
        lMatchRslt = NAS_ESM_MEM_CMP(pstPf1->aucRmtIpv4Address,
                                     pstPf2->aucRmtIpv4Address,
                                     APP_MAX_IPV4_ADDR_LEN);
        if (lMatchRslt != NAS_ESM_SUCCESS)
        {
            NAS_ESM_NORM_LOG("NAS_ESM_MatchIpAddrandMask:Ipv4 Address not match!");
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_MatchIpAddrandMask_ENUM, LNAS_FAIL, 1);
            return NAS_ESM_FAILURE;
        }

        lMatchRslt = NAS_ESM_MEM_CMP(pstPf1->aucRmtIpv4Mask,
                                     pstPf2->aucRmtIpv4Mask,
                                     APP_MAX_IPV4_ADDR_LEN);
        if (lMatchRslt != NAS_ESM_SUCCESS)
        {
            NAS_ESM_NORM_LOG("NAS_ESM_MatchIpAddrandMask:Ipv4 Mask not match!");
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_MatchIpAddrandMask_ENUM, LNAS_FAIL, 2);
            return NAS_ESM_FAILURE;
        }
    }

    if (NAS_ESM_OP_TRUE == pstPf1->bitOpRmtIpv6AddrAndMask)
    {
        lMatchRslt = NAS_ESM_MEM_CMP(pstPf1->aucRmtIpv6Address,
                                     pstPf2->aucRmtIpv6Address,
                                     APP_MAX_IPV6_ADDR_LEN);
        if (lMatchRslt != NAS_ESM_SUCCESS)
        {
            NAS_ESM_NORM_LOG("NAS_ESM_MatchIpAddrandMask:Ipv6 Address not match!");
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_MatchIpAddrandMask_ENUM, LNAS_FAIL, 3);
            return NAS_ESM_FAILURE;
        }

        lMatchRslt = NAS_ESM_MEM_CMP(pstPf1->aucRmtIpv6Mask,
                                     pstPf2->aucRmtIpv6Mask,
                                     APP_MAX_IPV6_ADDR_LEN);
        if (lMatchRslt != NAS_ESM_SUCCESS)
        {
            NAS_ESM_NORM_LOG("NAS_ESM_MatchIpAddrandMask:Ipv6 Mask not match!");
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_MatchIpAddrandMask_ENUM, LNAS_FAIL, 4);
            return NAS_ESM_FAILURE;
        }
    }

    return NAS_ESM_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_MatchLocalPort
 Description     : 匹配TFT数据项Local Port
 Input           : pstNwTFT -- 网侧的TFT信息
                   pstUeTFT -- Ue的TFT信息
 Output          : None
 Return          :
                   NAS_ESM_SUCCESS -- Local Port相同
                   NAS_ESM_FAILURE -- Local Port不相同
  History         :
    1.liuwenyu00143951      2009-12-15  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_ESM_MatchLocalPort
(
    const NAS_ESM_CONTEXT_TFT_STRU              *pstPf1,
    const NAS_ESM_CONTEXT_TFT_STRU              *pstPf2
)
{
    if ((NAS_ESM_SUCCESS == NAS_ESM_IsLocalPortRangeSameToSinglePort(pstPf1,pstPf2))
     || (NAS_ESM_SUCCESS == NAS_ESM_IsLocalPortRangeSameToSinglePort(pstPf2,pstPf1)))
    {
        /* CN 会将只包含一个端口号的端口范围归并为单一端口 */
        return NAS_ESM_SUCCESS;
    }

    if ((pstPf1->bitOpLocalPortRange != pstPf2->bitOpLocalPortRange)
     || (pstPf1->bitOpSingleLocalPort != pstPf2->bitOpSingleLocalPort))
    {
        return NAS_ESM_FAILURE;
    }

    if ((NAS_ESM_OP_TRUE == pstPf1->bitOpSingleLocalPort)
     && (pstPf1->usSingleLcPort != pstPf2->usSingleLcPort))
    {
        return NAS_ESM_FAILURE;
    }

    if ((NAS_ESM_OP_TRUE == pstPf1->bitOpLocalPortRange)
     && ((pstPf1->usLcPortLowLimit != pstPf2->usLcPortLowLimit)
         || (pstPf1->usLcPortHighLimit != pstPf2->usLcPortHighLimit)))
    {
        return NAS_ESM_FAILURE;
    }

    return NAS_ESM_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_MatchRemotePort
 Description     : 匹配TFT数据项Remote Port
 Input           : pstNwTFT -- 网侧的TFT信息
                   pstUeTFT -- Ue的TFT信息
 Output          : None
 Return          :
                   NAS_ESM_SUCCESS -- Remote Port相同
                   NAS_ESM_FAILURE -- Remote Port不相同
  History         :
    1.liuwenyu00143951      2009-12-15  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_ESM_MatchRemotePort
(
    const NAS_ESM_CONTEXT_TFT_STRU              *pstPf1,
    const NAS_ESM_CONTEXT_TFT_STRU              *pstPf2
)
{
    if ((NAS_ESM_SUCCESS == NAS_ESM_IsRemotePortRangeSameToSinglePort(pstPf1,pstPf2))
     || (NAS_ESM_SUCCESS == NAS_ESM_IsRemotePortRangeSameToSinglePort(pstPf2,pstPf1)))
    {
        /* CN 会将只包含一个端口号的端口范围归并为单一端口 */
        return NAS_ESM_SUCCESS;
    }

    if ((pstPf1->bitOpRemotePortRange != pstPf2->bitOpRemotePortRange)
     || (pstPf1->bitOpSingleRemotePort != pstPf2->bitOpSingleRemotePort))
    {
        return NAS_ESM_FAILURE;
    }

    if ((NAS_ESM_OP_TRUE == pstPf1->bitOpSingleRemotePort)
     && (pstPf1->usSingleRmtPort != pstPf2->usSingleRmtPort))
    {
        return NAS_ESM_FAILURE;
    }

    if ((NAS_ESM_OP_TRUE == pstPf1->bitOpRemotePortRange)
     && ((pstPf1->usRmtPortLowLimit != pstPf2->usRmtPortLowLimit)
         || (pstPf1->usRmtPortHighLimit != pstPf2->usRmtPortHighLimit)))
    {
       return NAS_ESM_FAILURE;
    }

    return NAS_ESM_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_MatchTftOtherItem
 Description     : 匹配TFT数据项ProtocolId,security parameter index,
                   TypeOfService,Flow Label Type
 Input           : pstNwTFT -- 网侧的TFT信息
                   pstUeTFT -- Ue的TFT信息
 Output          : None
 Return          :
                   NAS_ESM_SUCCESS -- 相同
                   NAS_ESM_FAILURE -- 不相同
  History         :
    1.liuwenyu00143951      2009-12-15  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_ESM_MatchTftOtherItem
(
    const NAS_ESM_CONTEXT_TFT_STRU              *pstPf1,
    const NAS_ESM_CONTEXT_TFT_STRU              *pstPf2
)
{
    if ((pstPf1->bitOpProtocolId != pstPf2->bitOpProtocolId)
      ||(pstPf1->bitOpSecuParaIndex != pstPf2->bitOpSecuParaIndex)
      ||(pstPf1->bitOpTypeOfService != pstPf2->bitOpTypeOfService)
      ||(pstPf1->bitOpFlowLabelType != pstPf2->bitOpFlowLabelType))
    {
        return NAS_ESM_FAILURE;
    }

    if ((NAS_ESM_OP_TRUE == pstPf1->bitOpProtocolId)
     && (pstPf1->ucProtocolId != pstPf2->ucProtocolId))
    {
        return NAS_ESM_FAILURE;
    }

    if ((NAS_ESM_OP_TRUE == pstPf1->bitOpSecuParaIndex)
     && (pstPf1->ulSecuParaIndex != pstPf2->ulSecuParaIndex))
    {
        return NAS_ESM_FAILURE;
    }

    if ((NAS_ESM_OP_TRUE == pstPf1->bitOpTypeOfService)
     && ((pstPf1->ucTypeOfService != pstPf2->ucTypeOfService)
         || (pstPf1->ucTypeOfServiceMask != pstPf2->ucTypeOfServiceMask)))

    {
        return NAS_ESM_FAILURE;
    }

    if ((NAS_ESM_OP_TRUE == pstPf1->bitOpFlowLabelType)
     && (pstPf1->ulFlowLabelType != pstPf2->ulFlowLabelType))
    {
        return NAS_ESM_FAILURE;
    }

    return NAS_ESM_SUCCESS;

}


/*****************************************************************************
 Function Name   : NAS_ESM_PfMatch
 Description     : 匹配两个packet filter的内容(第二个PF与第一个PF相比)
 Input           : pstPf1 -- 第一个PF信息
                   pstPf2 -- 第二个PF信息
 Output          : None
 Return          :
                   NAS_ESM_SUCCESS -- 两个packet filter匹配
                   NAS_ESM_FAILURE -- 两个packet filter不匹配
  History         :
    1.liuwenyu00143951      2009-10-23  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_ESM_PfMatch
(
    const NAS_ESM_CONTEXT_TFT_STRU              *pstPf1,
    const NAS_ESM_CONTEXT_TFT_STRU              *pstPf2
)
{
    if (pstPf1->ucPrecedence != pstPf2->ucPrecedence)
    {
        NAS_ESM_NORM_LOG("NAS_ESM_PfMatch:NORM:Precedence not match!");
        TLPS_PRINT2LAYER_INFO1(NAS_ESM_PfMatch_ENUM, LNAS_FAIL, 1);
        return NAS_ESM_FAILURE;
    }

    if (pstPf1->enDirection != pstPf2->enDirection)
    {
        NAS_ESM_NORM_LOG("NAS_ESM_PfMatch:NORM:Direction not match!");
        TLPS_PRINT2LAYER_INFO1(NAS_ESM_PfMatch_ENUM, LNAS_FAIL, 2);
        return NAS_ESM_FAILURE;
    }

    if (NAS_ESM_FAILURE == NAS_ESM_MatchIpAddrandMask(pstPf1,pstPf2))
    {
        NAS_ESM_NORM_LOG("NAS_ESM_PfMatch:NORM:IP address or mask not match!");
        TLPS_PRINT2LAYER_INFO1(NAS_ESM_PfMatch_ENUM, LNAS_FAIL, 3);
        return NAS_ESM_FAILURE;
    }

    if (NAS_ESM_FAILURE == NAS_ESM_MatchLocalPort(pstPf1,pstPf2))
    {
        NAS_ESM_NORM_LOG("NAS_ESM_PfMatch:NORM:Local port not match!");
        TLPS_PRINT2LAYER_INFO1(NAS_ESM_PfMatch_ENUM, LNAS_FAIL, 4);
        return NAS_ESM_FAILURE;
    }

    if (NAS_ESM_FAILURE == NAS_ESM_MatchRemotePort(pstPf1,pstPf2))
    {
        NAS_ESM_NORM_LOG("NAS_ESM_PfMatch:NORM:Remote port not match!");
        TLPS_PRINT2LAYER_INFO1(NAS_ESM_PfMatch_ENUM, LNAS_FAIL, 5);
        return NAS_ESM_FAILURE;
    }

    if (NAS_ESM_FAILURE == NAS_ESM_MatchTftOtherItem(pstPf1,pstPf2))
    {
        NAS_ESM_NORM_LOG("NAS_ESM_PfMatch:NORM:TypeOfService or ProtocolId not match!");
        TLPS_PRINT2LAYER_INFO1(NAS_ESM_PfMatch_ENUM, LNAS_FAIL, 6);
        return NAS_ESM_FAILURE;
    }

    return NAS_ESM_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_TftMatch
 Description     : 匹配两个TFT的内容(第一个TFT与第二个TFT相比)
 Input           : pstTft1PfInfo    -- TFT1中PF数组首地址
                   ulTft1PfNum      -- TFT1中PF个数
                   pstTft2PfInfo    -- TFT2中PF数组首地址
                   ulTft2PfNum      -- TFT2中PF个数
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.liuwenyu00143951      2009-10-23  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_ESM_TftMatch
(
    const NAS_ESM_CONTEXT_TFT_STRU           *pstTft1PfInfo,
    VOS_UINT32                                ulTft1PfNum,
    NAS_ESM_CONTEXT_TFT_STRU                 *pstTft2PfInfo,
    VOS_UINT32                                ulTft2PfNum
)
{
    VOS_UINT32                           ulCnt1        = NAS_ESM_NULL;
    VOS_UINT32                           ulCnt2        = NAS_ESM_NULL;
    /* for decrease number of loop */
    VOS_UINT16                           usMatchedSdf  = NAS_ESM_NULL;
    VOS_UINT32                           ulTFTMatchRlt = NAS_ESM_FAILURE;

    (VOS_VOID)pstTft2PfInfo;

    if (ulTft2PfNum != ulTft1PfNum)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_TftMatch:WARNING: static and dynamic number not equal!");
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_TftMatch_ENUM, LNAS_FAIL, 1);
        return NAS_ESM_FAILURE;
    }

    /* check every dynamic SDF context information */
    for (ulCnt1 = NAS_ESM_NULL; ulCnt1 < ulTft2PfNum; ulCnt1++)
    {
        for (ulCnt2 = NAS_ESM_NULL; ulCnt2 < ulTft1PfNum; ulCnt2++)
        {
            /* do not search sdf which has found the mapped network packetfilterid */
            if (NAS_ESM_OP_TRUE == ((usMatchedSdf >> ulCnt2) & NAS_ESM_OP_TRUE))
            {
                continue;
            }

            ulTFTMatchRlt = NAS_ESM_PfMatch(    &pstTft2PfInfo[ulCnt1],
                                                &pstTft1PfInfo[ulCnt2]);

            /*lint -e701*/
            if (NAS_ESM_SUCCESS == ulTFTMatchRlt)
            {
                /* set sdf network packetfilterid for check whether the sdf */
                /* has found mapped network packetfilterid  */
                usMatchedSdf |= (VOS_UINT16)(NAS_ESM_BIT_0 << ulCnt2);
                break;
            }
            /*lint +e701*/

         }

        if (NAS_ESM_FAILURE == ulTFTMatchRlt)
        {
            NAS_ESM_WARN_LOG("NAS_ESM_TftMatch:WARNING: static and dynamic Tft not matched !");
            TLPS_PRINT2LAYER_WARNING1(NAS_ESM_TftMatch_ENUM, LNAS_FAIL, 2);
            return NAS_ESM_FAILURE;
        }
    }

    return NAS_ESM_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_SaveNwActDedictdEpsbReqInfo
 Description     : 保存专有承载激活的上下文信息
 Input           : pstMsgIE         -- 译码后的网络消息
                   ulStateTblIndex  -- 动态表索引
 Output          : None
 Return          : VOS_VOID

 History         :
    1.liuwenyu00143951      2009-12-02  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_SaveNwActDedictdEpsbReqInfo
(
    const  NAS_ESM_NW_MSG_STRU          *pstMsgIE,
    VOS_UINT32                           ulStateTblIndex
)
{
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr     = VOS_NULL_PTR;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo  = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG("NAS_ESM_SaveNwActDedictdEpsbReqInfo is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_SaveNwActDedictdEpsbReqInfo_ENUM, LNAS_ENTRY);

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    pstSdfCntxtInfo = NAS_ESM_GetSdfCntxtInfo(pstStateAddr->ulCid);

    /* 设置SDF的QOS内容 */
    NAS_ESM_MEM_CPY_S(  &pstSdfCntxtInfo->stSdfQosInfo,
                        sizeof(NAS_ESM_CONTEXT_LTE_QOS_STRU),
                        &pstMsgIE->stSdfQosInfo,
                        sizeof(NAS_ESM_CONTEXT_LTE_QOS_STRU));

    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(pstMsgIE->ucEpsbId);

    /*保存Linked EPS Bearer参数*/
    pstEpsbCntxtInfo->ulLinkedEpsbId =(VOS_UINT32)pstMsgIE->ucLinkedEpsbId;

    /*设置EPS QOS标识位和EPS QOS内容*/
    pstEpsbCntxtInfo->bitOpEpsQos = NAS_ESM_OP_TRUE;

    NAS_ESM_MEM_CPY_S(  &(pstEpsbCntxtInfo->stEpsQoSInfo),
                        sizeof(NAS_ESM_CONTEXT_LTE_QOS_STRU),
                        &(pstSdfCntxtInfo->stSdfQosInfo),
                        sizeof(NAS_ESM_CONTEXT_LTE_QOS_STRU));

    /*根据Cid添加PF*/
    NAS_ESM_MEM_CPY_S(  pstSdfCntxtInfo->astSdfPfInfo,
                        sizeof(NAS_ESM_CONTEXT_TFT_STRU) * NAS_ESM_MAX_SDF_PF_NUM,
                        pstMsgIE->stTadInfo.astSdfPfInfo,
                        sizeof(NAS_ESM_CONTEXT_TFT_STRU) * pstMsgIE->stTadInfo.ucSdfPfNum);

    pstSdfCntxtInfo->ulSdfPfNum = pstMsgIE->stTadInfo.ucSdfPfNum;
    pstSdfCntxtInfo->ulEpsbId   = pstMsgIE->ucEpsbId;

    /* 如果静态和动态信息不一致，则进行调整 */
    NAS_ESM_ModulateSdfTft(ulStateTblIndex);

    NAS_ESM_ModulateSdfQos(ulStateTblIndex);

    /*检查TI(如果存在)，直接存储*/
    pstEpsbCntxtInfo->bitOpTransId = pstMsgIE->bitOpTransId;

    NAS_ESM_MEM_CPY_S(  &pstEpsbCntxtInfo->stTransId,
                        sizeof(NAS_ESM_CONTEXT_TRANS_ID_STRU),
                        &pstMsgIE->stTransId,
                        sizeof(NAS_ESM_CONTEXT_TRANS_ID_STRU));

    /*检查PDP QOS(如果存在)，直接存储*/
    pstEpsbCntxtInfo->bitOpNegQos = pstMsgIE->bitOpNegQos;
    NAS_ESM_MEM_CPY_S(  &pstEpsbCntxtInfo->stCntxtQosInfo,
                        sizeof(NAS_ESM_CONTEXT_QOS_STRU),
                        &pstMsgIE->stCntxtQosInfo,
                        sizeof(NAS_ESM_CONTEXT_QOS_STRU));

    /*检查LLC SAPI(如果存在)，直接存储*/
    pstEpsbCntxtInfo->bitOpLlcSapi = pstMsgIE->bitOpLlcSapi;
    pstEpsbCntxtInfo->ucLlcSapi = pstMsgIE->ucLlcSapi;

    /*检查Radio Priority(如果存在)，直接存储*/
    pstEpsbCntxtInfo->bitOpRadioPriority = pstMsgIE->bitOpRadioPriority;
    pstEpsbCntxtInfo->ucRadioPriority = pstMsgIE->ucRadioPriority;

    /*检查Packet Flow Identifer(如果存在)，直接存储*/
    pstEpsbCntxtInfo->bitOpPacketFlowId = pstMsgIE->bitOpPacketFlowId;
    pstEpsbCntxtInfo->ucPacketFlowId = pstMsgIE->ucPacketFlowId;

}

/*****************************************************************************
 Function Name   : NAS_ESM_SaveNwModEpsbReqInfo
 Description     : 保存承载修改激活的上下文信息
 Input           : pstMsgIE         -- 译码后的网络消息
                   ulStateTblIndex  -- 动态表索引
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2009-12-2  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_SaveNwModEpsbReqInfo
(
    const  NAS_ESM_NW_MSG_STRU          *pstMsgIE,
    VOS_UINT32                           ulStateTblIndex
)
{
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG("NAS_ESM_SaveNwModEpsbReqInfo is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_SaveNwModEpsbReqInfo_ENUM, LNAS_ENTRY);

    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(pstMsgIE->ucEpsbId);

    if (PS_TRUE == NAS_ESM_IsDefaultEpsBearerType(pstEpsbCntxtInfo->enBearerCntxtType))
    {
        NAS_ESM_SaveNwModDeftEpsbReqInfo(pstMsgIE,ulStateTblIndex);
    }
    else
    {
        NAS_ESM_SaveNwModDediEpsbReqInfo(pstMsgIE,ulStateTblIndex);
    }

    /*检查PDP QOS(如果存在)，直接存储*/
    if(NAS_ESM_OP_TRUE == pstMsgIE->bitOpNegQos)
    {
        pstEpsbCntxtInfo->bitOpNegQos = NAS_ESM_OP_TRUE;

        NAS_ESM_MEM_CPY_S(  &pstEpsbCntxtInfo->stCntxtQosInfo,
                            sizeof(NAS_ESM_CONTEXT_QOS_STRU),
                            &pstMsgIE->stCntxtQosInfo,
                            sizeof(NAS_ESM_CONTEXT_QOS_STRU));
    }

    /*检查LLC SAPI(如果存在)，直接存储*/
    if(NAS_ESM_OP_TRUE == pstMsgIE->bitOpLlcSapi)
    {
        pstEpsbCntxtInfo->bitOpLlcSapi = NAS_ESM_OP_TRUE;
        pstEpsbCntxtInfo->ucLlcSapi = pstMsgIE->ucLlcSapi;
    }

    /*检查Radio Priority(如果存在)，直接存储*/
    if(NAS_ESM_OP_TRUE == pstMsgIE->bitOpRadioPriority)
    {
        pstEpsbCntxtInfo->bitOpRadioPriority = NAS_ESM_OP_TRUE;
        pstEpsbCntxtInfo->ucRadioPriority = pstMsgIE->ucRadioPriority;
    }

    /*检查Packet Flow ID(如果存在)，直接存储*/
    if(NAS_ESM_OP_TRUE == pstMsgIE->bitOpPacketFlowId)
    {
        pstEpsbCntxtInfo->bitOpPacketFlowId = NAS_ESM_OP_TRUE;
        pstEpsbCntxtInfo->ucPacketFlowId = pstMsgIE->ucPacketFlowId;
    }

    /*检查APN-AMBR(如果存在)，直接存储*/
    if( NAS_ESM_OP_TRUE == pstMsgIE->bitOpApnAmbr )
    {
        if (PS_FALSE == NAS_ESM_IsDefaultEpsBearerType(pstEpsbCntxtInfo->enBearerCntxtType))
        {
            pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(pstEpsbCntxtInfo->ulLinkedEpsbId);
        }

        pstEpsbCntxtInfo->bitOpApnAmbr = NAS_ESM_OP_TRUE;

        NAS_ESM_MEM_CPY_S(  &pstEpsbCntxtInfo->stApnAmbrInfo,
                            sizeof(NAS_ESM_CONTEXT_APN_AMBR_STRU),
                            &pstMsgIE->stApnAmbrInfo,
                            sizeof(NAS_ESM_CONTEXT_APN_AMBR_STRU));
    }

    /* 检查如果携带P-CSCF地址，则覆盖式保存 */
    if( NAS_ESM_OP_TRUE == pstMsgIE->bitOpPco )
    {
        if (0 != pstMsgIE->stPcoInfo.ucIpv4PcscfNum)
        {
            pstEpsbCntxtInfo->bitOpPco = NAS_ESM_OP_TRUE;
            /* 记录修改后的IPV4 P-CSCF地址个数 */
            pstEpsbCntxtInfo->stPcoInfo.ucIpv4PcscfNum = pstMsgIE->stPcoInfo.ucIpv4PcscfNum;

            NAS_ESM_MEM_CPY_S(  &pstEpsbCntxtInfo->stPcoInfo.astIpv4Pcscf[0],
                                sizeof(NAS_ESM_IPV4_ADDR_STRU) * NAS_ESM_MAX_PCSCF_NUM,
                                &pstMsgIE->stPcoInfo.astIpv4Pcscf[0],
                                sizeof(NAS_ESM_IPV4_ADDR_STRU) * NAS_ESM_MAX_PCSCF_NUM);
        }

        if (0 != pstMsgIE->stPcoInfo.ucIpv6PcscfNum)
        {
            pstEpsbCntxtInfo->bitOpPco = NAS_ESM_OP_TRUE;
            /* 记录修改后的IPV6 P-CSCF地址个数 */
            pstEpsbCntxtInfo->stPcoInfo.ucIpv6PcscfNum = pstMsgIE->stPcoInfo.ucIpv6PcscfNum;

            NAS_ESM_MEM_CPY_S(  &pstEpsbCntxtInfo->stPcoInfo.astIpv6Pcscf[0],
                                sizeof(NAS_ESM_IPV6_ADDR_STRU) * NAS_ESM_MAX_PCSCF_NUM,
                                &pstMsgIE->stPcoInfo.astIpv6Pcscf[0],
                                sizeof(NAS_ESM_IPV6_ADDR_STRU) * NAS_ESM_MAX_PCSCF_NUM);
        }
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_DediBearActMsgManualProc
 Description     : 专有承载激活手动处理
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-12-3  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_DediBearActMsgManualProc
(
    VOS_UINT32                          ulStateTblIndex,
    const NAS_ESM_NW_MSG_STRU          *pstDecodedNwMsg
)
{
    APP_ESM_PDP_MANAGER_IND_STRU        stPdpManInd;
    VOS_UINT32                          ulRslt          = NAS_ESM_FAILURE;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr    = VOS_NULL_PTR;

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_DediBearActMsgManualProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_DediBearActMsgManualProc_ENUM, LNAS_ENTRY);

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    /* 开辟空间，用于缓存译码后的网络信息 */
    pstStateAddr->pstDecodedNwMsg = (VOS_VOID *)NAS_ESM_MEM_ALLOC(sizeof(NAS_ESM_NW_MSG_STRU));

    if (VOS_NULL_PTR == pstStateAddr->pstDecodedNwMsg)
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_DediBearActMsgManualProc:ERROR:SM->APP,Memory Alloc FAIL!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_DediBearActMsgManualProc_ENUM, LNAS_NULL_PTR);

        /*释放状态表资源*/
        NAS_ESM_RelStateTblResource(ulStateTblIndex);

        return ;
    }

    /* 将译码后的网络信息拷贝至缓存区 */
    NAS_ESM_MEM_CPY_S(  pstStateAddr->pstDecodedNwMsg,
                        sizeof(NAS_ESM_NW_MSG_STRU),
                        pstDecodedNwMsg,
                        sizeof(NAS_ESM_NW_MSG_STRU));

    /* 清空临时变量stPdpManInd */
    NAS_ESM_MEM_SET_S(  &stPdpManInd,
                        sizeof(APP_ESM_PDP_MANAGER_IND_STRU),
                        NAS_ESM_NULL,
                        sizeof(APP_ESM_PDP_MANAGER_IND_STRU));

    /* 填写专有承载的linkCid */
    stPdpManInd.bitOpLinkCid = NAS_ESM_OP_TRUE;
    ulRslt = NAS_ESM_QueryFirstSdfIdByEpsbId(pstDecodedNwMsg->ucLinkedEpsbId, &stPdpManInd.ulLinkCid);
    if(NAS_ESM_FAILURE == ulRslt)
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_DediBearActMsgManualProc:ERROR:Can not find linkCid by linkEpsbId!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_DediBearActMsgManualProc_ENUM, LNAS_FAIL);

        /*释放状态表资源*/
        NAS_ESM_RelStateTblResource(ulStateTblIndex);

        return ;
    }

    stPdpManInd.bitOpModifyTpye = NAS_ESM_OP_FALSE;

    /* 填写CID */
    stPdpManInd.ulCid = pstStateAddr->ulCid;

    /* 填写Opid, OriginalId和TerminalId*/
    if (NAS_ESM_PTI_UNASSIGNED_VALUE != pstStateAddr->stNwMsgRecord.ucPti)
    {
        stPdpManInd.ulOpId = pstStateAddr->stAppMsgRecord.ulAppMsgOpId;
        stPdpManInd.usTerminalId = pstStateAddr->stAppMsgRecord.usOriginalId;
        stPdpManInd.usOriginalId = pstStateAddr->stAppMsgRecord.usTerminalId;
    }
    else
    {
        stPdpManInd.ulOpId = NAS_ESM_OPID_TYPE_MANAGER_IND;

        /* 分配本次过程APP_MSG_HEADER*/
        NAS_ESM_AssignMidHeader(&stPdpManInd.usOriginalId,&stPdpManInd.usTerminalId);
    }

    /* 填写操作类型 */
    stPdpManInd.enOperateType = APP_ESM_BEARER_OPERATE_TYPE_DEDI_ACT;

     /* 向APP发送ID_APP_ESM_PDP_MANAGER_IND消息 */
    NAS_ESM_SndEsmAppPdpManageIndMsg(&stPdpManInd);

    /* 启动定时器等待APP回复消息 */
    NAS_ESM_TimerStart(ulStateTblIndex, TI_NAS_ESM_WAIT_APP_CNF);

    /* 设置等待App回复标志位 */
    pstStateAddr->ucIsWaitForUserAnswer = PS_TRUE;
}





/*****************************************************************************
 Function Name   : NAS_ESM_DediBearActMsgAutoAccept
 Description     : 自动接受专有承载激活的处理
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-12-3  Draft Enact
    2.lihong00150010      2010-02-10 Modify

*****************************************************************************/
VOS_VOID NAS_ESM_DediBearActMsgAutoAccept
(
    VOS_UINT32                          ulStateTblIndex,
    NAS_ESM_ENCODE_INFO_STRU            stEncodeInfo,
    const NAS_ESM_NW_MSG_STRU          *pstDecodedNwMsg
)
{
    VOS_UINT32                          ulSndNwMsgLen    = NAS_ESM_NULL;
    VOS_UINT32                          ulRslt           = NAS_ESM_NULL;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr     = VOS_NULL_PTR;

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_DediBearActMsgAutoAccept is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_DediBearActMsgAutoAccept_ENUM, LNAS_ENTRY);

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    /* 保存专有承载激活的上下文信息 */
    NAS_ESM_SaveNwActDedictdEpsbReqInfo(pstDecodedNwMsg, ulStateTblIndex);

    /*向网侧回复Activate dedicated bearer context accept*/
    NAS_ESM_EncodeActDedictdEpsbCntxtAccMsg(stEncodeInfo, \
                                    NAS_ESM_GetCurEsmSndNwMsgAddr(),\
                                   &ulSndNwMsgLen);
    NAS_ESM_SndAirMsgReportInd(NAS_ESM_GetCurEsmSndNwMsgAddr(),ulSndNwMsgLen,
                               NAS_ESM_AIR_MSG_DIR_ENUM_UP,
                               ESM_ACT_DEDICT_EPS_BEARER_CNTXT_ACP);
    NAS_ESM_SndEsmEmmDataReqMsg(NAS_ESM_ILLEGAL_OPID, PS_FALSE, ulSndNwMsgLen, NAS_ESM_GetCurEsmSndNwMsgAddr());
    NAS_ESM_UpdateEsmSndNwMsgLen(ulSndNwMsgLen);

    /*转换状态和设置承载属性*/
    NAS_ESM_SetBearCntxtState(stEncodeInfo.ulEpsbId, NAS_ESM_BEARER_STATE_ACTIVE);
    NAS_ESM_SetBearCntxtType(stEncodeInfo.ulEpsbId, NAS_ESM_BEARER_TYPE_DEDICATED);
    NAS_ESM_SetBearCntxtLinkCid(stEncodeInfo.ulEpsbId,pstStateAddr->ulCid);

    /*关键事件上报*/
    NAS_ESM_SndKeyEventReportInd((OM_PS_KEY_EVENT_ENUM_UINT8)NAS_ESM_EVENT_BEARER_SETUP(stEncodeInfo.ulEpsbId));

    if (NAS_ESM_OP_TRUE == pstStateAddr->bitOpAppMsgRecord)
    {
        /* L4A重构, BEARER_INFO_IND和APP CNF消息顺序调换 */

        /* 缓存PTI和回复消息 */
        ulRslt = NAS_ESM_SavePtiBuffItem(stEncodeInfo.ucPti,
                                         (VOS_UINT8)stEncodeInfo.ulEpsbId,
                                         ulSndNwMsgLen,
                                         NAS_ESM_GetCurEsmSndNwMsgAddr());
        if (ulRslt != NAS_ESM_SUCCESS)
        {
            NAS_ESM_WARN_LOG("NAS_ESM_DediBearActMsgAutoAccept:WARN:Save pti buffer item failed!");
            TLPS_PRINT2LAYER_WARNING1(NAS_ESM_DediBearActMsgAutoAccept_ENUM, LNAS_FAIL, 1);
        }
    }
    /* L4A重构, BEARER_INFO_IND和APP CNF消息顺序调换 */

    if (NAS_ESM_PTI_UNASSIGNED_VALUE != stEncodeInfo.ucPti)
    {
         /* 缓存PTI和回复消息 */
        ulRslt = NAS_ESM_SavePtiBuffItem(stEncodeInfo.ucPti,
                                         (VOS_UINT8)stEncodeInfo.ulEpsbId,
                                         ulSndNwMsgLen,
                                         NAS_ESM_GetCurEsmSndNwMsgAddr());
        if (ulRslt != NAS_ESM_SUCCESS)
        {
            NAS_ESM_WARN_LOG("NAS_ESM_DediBearActMsgAutoAccept:WARN:Save pti buffer item failed!");
            TLPS_PRINT2LAYER_WARNING1(NAS_ESM_DediBearActMsgAutoAccept_ENUM, LNAS_FAIL, 2);
        }
    }

    /*向EMM发送ID_EMM_ESM_BEARER_STATUS_REQ*/
    NAS_ESM_SndEsmEmmBearerStatusReqMsg(EMM_ESM_BEARER_CNTXT_MOD_MUTUAL);

    /*向RABM发送ID_ESM_ERABM_ACT_IND*/
    NAS_ESM_SndEsmRabmActIndMsg(stEncodeInfo.ulEpsbId, ESM_ERABM_BEARER_RAT_LTE, PS_FALSE, ESM_ERABM_INVALID_BEARER_ID);

    NAS_ESM_PrintEpsbInfo(stEncodeInfo.ulEpsbId);

    /* L4A重构, BEARER_INFO_IND和APP CNF消息顺序调换, 释放资源在回复APP之后清 */

    /* 通知SM承载激活 */
    NAS_ESM_SndSmEspBearerActIndMsg(stEncodeInfo.ulEpsbId);

    /* L4A重构, BEARER_INFO_IND和APP CNF消息顺序调换 */
    if (NAS_ESM_OP_TRUE == pstStateAddr->bitOpAppMsgRecord)
    {
        if(ID_APP_ESM_PDP_SETUP_REQ == pstStateAddr->stAppMsgRecord.enAppMsgType )
        {
            /*向APP发送ID_APP_ESM_PDP_SETUP_CNF(成功)消息*/
            NAS_ESM_SndEsmAppSdfSetupCnfSuccMsg(ulStateTblIndex);

        }
        else
        {
            NAS_ESM_SndEsmAppSdfModCnfSuccMsg(ulStateTblIndex,
                                              APP_ESM_BEARER_MODIFY_TFT_QOS);

            NAS_ESM_SndEsmAppBearerQosIndMsg(stEncodeInfo.ulEpsbId);
        }
    }
    else
    {
        /*向APP发送APP_ESM_BEARER_SETUP_IND*/
        NAS_ESM_SndEsmAppSdfSetupIndMsg(ulStateTblIndex, APP_SUCCESS);
    }

    /*释放状态表资源*/
    NAS_ESM_RelStateTblResource(ulStateTblIndex);

    /* PF优先级冲突处理 */
    NAS_ESM_ProcPfPrecedenceCollision(pstDecodedNwMsg);
}


/*****************************************************************************
 Function Name   : NAS_ESM_BearModMsgManualProc
 Description     : 承载修改手动处理
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.liuwenyu00143951      2009-12-3  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_BearModMsgManualProc
(
    VOS_UINT32                          ulStateTblIndex,
    const NAS_ESM_NW_MSG_STRU          *pstDecodedNwMsg
)
{
    APP_ESM_PDP_MANAGER_IND_STRU        stPdpManInd;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr    = VOS_NULL_PTR;

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_BearModMsgManualProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_BearModMsgManualProc_ENUM, LNAS_ENTRY);

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    /* 开辟空间，用于缓存译码后的网络信息 */
    pstStateAddr->pstDecodedNwMsg = (VOS_VOID *)NAS_ESM_MEM_ALLOC(sizeof(NAS_ESM_NW_MSG_STRU));

    if (VOS_NULL_PTR == pstStateAddr->pstDecodedNwMsg)
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_BearModMsgManualProc:ERROR:SM->APP,Memory Alloc FAIL!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_BearModMsgManualProc_ENUM, LNAS_NULL_PTR);

        /*释放状态表资源*/
        NAS_ESM_RelStateTblResource(ulStateTblIndex);

        return ;
    }

    /* 将译码后的网络信息拷贝至缓存区 */
    NAS_ESM_MEM_CPY_S(  pstStateAddr->pstDecodedNwMsg,
                        sizeof(NAS_ESM_NW_MSG_STRU),
                        pstDecodedNwMsg,
                        sizeof(NAS_ESM_NW_MSG_STRU));

    /* 清空临时变量stPdpManInd */
    NAS_ESM_MEM_SET_S(  &stPdpManInd,
                        sizeof(APP_ESM_PDP_MANAGER_IND_STRU),
                        NAS_ESM_NULL,
                        sizeof(APP_ESM_PDP_MANAGER_IND_STRU));

    stPdpManInd.bitOpLinkCid = NAS_ESM_OP_FALSE;

    /* 填写承载修改类型 */
    stPdpManInd.bitOpModifyTpye = NAS_ESM_OP_TRUE;
    stPdpManInd.enBearerModifyType = NAS_ESM_GetBearModifyType(pstDecodedNwMsg);

    /* 填写CID */
    stPdpManInd.ulCid = pstStateAddr->ulCid;

    /* 填写Opid, OriginalId和TerminalId*/
    if (NAS_ESM_PTI_UNASSIGNED_VALUE != pstStateAddr->stNwMsgRecord.ucPti)
    {
        stPdpManInd.ulOpId = pstStateAddr->stAppMsgRecord.ulAppMsgOpId;
        stPdpManInd.usTerminalId = pstStateAddr->stAppMsgRecord.usOriginalId;
        stPdpManInd.usOriginalId = pstStateAddr->stAppMsgRecord.usTerminalId;
    }
    else
    {
        stPdpManInd.ulOpId = NAS_ESM_OPID_TYPE_MANAGER_IND;

        /* 分配本次过程APP_MSG_HEADER*/
        NAS_ESM_AssignMidHeader(&stPdpManInd.usOriginalId,&stPdpManInd.usTerminalId);
    }

    /* 填写操作类型 */
    stPdpManInd.enOperateType = APP_ESM_BEARER_OPERATE_TYPE_MODIFY;

     /* 向APP发送ID_APP_ESM_PDP_MANAGER_IND消息 */
    NAS_ESM_SndEsmAppPdpManageIndMsg(&stPdpManInd);

    /* 启动定时器等待APP回复消息 */
    NAS_ESM_TimerStart(ulStateTblIndex, TI_NAS_ESM_WAIT_APP_CNF);

    /* 设置等待App回复标志位 */
    pstStateAddr->ucIsWaitForUserAnswer = PS_TRUE;
}

/*****************************************************************************
 Function Name   : NAS_ESM_BearModMsgAutoAccept
 Description     : 自动接受承载修改的处理
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.liuwenyu00143951      2009-12-3  Draft Enact
    2.lihong00150010        2010-02-10 Modify

*****************************************************************************/
VOS_VOID NAS_ESM_BearModMsgAutoAccept
(
    VOS_UINT32                          ulStateTblIndex,
    NAS_ESM_ENCODE_INFO_STRU            stEncodeInfo,
    const NAS_ESM_NW_MSG_STRU          *pstDecodedNwMsg
)
{
    VOS_UINT32                          ulSndNwMsgLen    = NAS_ESM_NULL;
    VOS_UINT32                          ulRslt           = NAS_ESM_NULL;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr     = VOS_NULL_PTR;


    #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo = VOS_NULL_PTR;
    #endif

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_BearModMsgAutoAccept is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_BearModMsgAutoAccept_ENUM, LNAS_ENTRY);

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    /* 保存承载修改信息 */
    NAS_ESM_SaveNwModEpsbReqInfo(pstDecodedNwMsg, ulStateTblIndex);

    /*向网侧回复Modify EPS bearer context accept*/
    NAS_ESM_EncodeModEpsbCntxtAccMsg(&stEncodeInfo, \
                                     NAS_ESM_GetCurEsmSndNwMsgAddr(),\
                                    &ulSndNwMsgLen);

    NAS_ESM_SndAirMsgReportInd(NAS_ESM_GetCurEsmSndNwMsgAddr(),\
                               ulSndNwMsgLen, NAS_ESM_AIR_MSG_DIR_ENUM_UP,\
                               ESM_MOD_EPS_BEARER_CNTXT_ACP);
    NAS_ESM_SndEsmEmmDataReqMsg(NAS_ESM_ILLEGAL_OPID, PS_FALSE, ulSndNwMsgLen, NAS_ESM_GetCurEsmSndNwMsgAddr());
    NAS_ESM_UpdateEsmSndNwMsgLen(ulSndNwMsgLen);

    /* L4A重构, BEARER_INFO_IND与APP CNF顺序调换 */
    NAS_ESM_SndSmEspBearerMdfIndMsg(stEncodeInfo.ulEpsbId);

    /* 当TAD码为NAS_ESM_TFT_OP_TYPE_ADD_FILTER，则需要先形成承载与SDF的关联关系，
       后上报APP,这样在上报APP时才能正确填写linkcid；当TAD码为NAS_ESM_TFT_OP_TYPE_DELETE_FILTER
       时，则需先上报APP，后删除承载与SDF的关联关系，,这样在上报APP时才能正确填写linkcid */
    if (NAS_ESM_TFT_OP_TYPE_DELETE_FILTER != pstDecodedNwMsg->stTadInfo.enTftOpType)
    {
        NAS_ESM_UpdateBearCntextLinkCid(pstDecodedNwMsg,
                                        stEncodeInfo.ulEpsbId,
                                        pstStateAddr->ulCid);
        NAS_ESM_InformAppEpsBearerModSucc(pstDecodedNwMsg, \
                                          ulStateTblIndex);
    }
    else
    {
        NAS_ESM_InformAppEpsBearerModSucc(pstDecodedNwMsg, \
                                          ulStateTblIndex);
        NAS_ESM_UpdateBearCntextLinkCid(pstDecodedNwMsg,
                                        stEncodeInfo.ulEpsbId,
                                        pstStateAddr->ulCid);
    }

    /*关键事件上报*/
    NAS_ESM_SndKeyEventReportInd(NAS_ESM_EVENT_BEARER_MODIFY(stEncodeInfo.ulEpsbId));

    if (NAS_ESM_PTI_UNASSIGNED_VALUE != stEncodeInfo.ucPti)
    {
        /* 缓存PTI和回复消息 */
        ulRslt= NAS_ESM_SavePtiBuffItem(stEncodeInfo.ucPti,
                                        (VOS_UINT8)stEncodeInfo.ulEpsbId,
                                        ulSndNwMsgLen,
                                        NAS_ESM_GetCurEsmSndNwMsgAddr());
        if (ulRslt != NAS_ESM_SUCCESS)
        {
            NAS_ESM_WARN_LOG("NAS_ESM_BearModMsgAutoAccept:WARN:Save pti buffer item failed!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_BearModMsgAutoAccept_ENUM, LNAS_FAIL);
        }
    }
    NAS_ESM_SndEsmEmmBearerModifyReq(stEncodeInfo.ulEpsbId);

    /*向RABM发送ID_ESM_ERABM_MDF_IND*/
    if((NAS_ESM_OP_TRUE == pstDecodedNwMsg->bitOpTadInfo)
        && (NAS_ESM_TFT_OP_TYPE_NO_OP != pstDecodedNwMsg->stTadInfo.enTftOpType))
    {
        /* 发送ID_ESM_ERABM_MDF_IND消息 */
        NAS_ESM_SndEsmRabmMdfIndMsg(stEncodeInfo.ulEpsbId, ESM_ERABM_BEARER_RAT_LTE);
    }

    NAS_ESM_PrintEpsbInfo(stEncodeInfo.ulEpsbId);

    /*释放状态表资源*/
    NAS_ESM_RelStateTblResource(ulStateTblIndex);

    /* L4A重构, BEARER_INFO_IND与APP CNF顺序调换 */

    #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

    /*获取对应EpsbCntxtTbl表地址*/
    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(stEncodeInfo.ulEpsbId);

    /* 如果是缺省承载，通知EHSM承载修改 */
    if (PS_TRUE == NAS_ESM_IsDefaultEpsBearerType(pstEpsbCntxtInfo->enBearerCntxtType))
    {
        /* 支持EHRPD接入技术才通知EHSM */
        if (NAS_ESM_SUCCESS == NAS_EMM_IsEhrpdOr1XRatExist())
        {
            NAS_ESM_SndEhsmSyncPdnInfoModIndMsg(stEncodeInfo.ulEpsbId);
        }
    }
    #endif

    /* PF优先级冲突处理 */
    if (PS_TRUE == NAS_ESM_IsNeedPreferrenceCollision(pstDecodedNwMsg))
    {
        NAS_ESM_ProcPfPrecedenceCollision(pstDecodedNwMsg);
    }

}

/*****************************************************************************
 Function Name   : NAS_ESM_ActDediBearFailProc
 Description     : 专有承载激活失败处理
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-12-4  Draft Enact
    2.lihong00150010      2010-02-10 Modify

*****************************************************************************/
VOS_VOID  NAS_ESM_ActDediBearFailProc
(
    const NAS_ESM_ENCODE_INFO_STRU     *pstEncodeInfo,
    VOS_UINT32                          ulStateTblIndex
)
{
    VOS_UINT32                          ulSndNwMsgLen    = NAS_ESM_NULL;
    VOS_UINT32                          ulRslt           = NAS_ESM_NULL;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr     = VOS_NULL_PTR;

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_ActDediBearFailProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_ActDediBearFailProc_ENUM, LNAS_ENTRY);

    if( NAS_ESM_CAUSE_ERROR != pstEncodeInfo->ucESMCau )
    {
        /*向网侧回复Activate dedicated bearer context reject*/
        NAS_ESM_EncodeActDedictdEpsbCntxtRejMsg(*pstEncodeInfo, \
                                                NAS_ESM_GetCurEsmSndNwMsgAddr(),\
                                                &ulSndNwMsgLen);
        NAS_ESM_SndAirMsgReportInd(NAS_ESM_GetCurEsmSndNwMsgAddr(),ulSndNwMsgLen,\
                                   NAS_ESM_AIR_MSG_DIR_ENUM_UP,\
                                   ESM_ACT_DEDICT_EPS_BEARER_CNTXT_REJ);
        NAS_ESM_SndEsmEmmDataReqMsg(NAS_ESM_ILLEGAL_OPID, PS_FALSE, ulSndNwMsgLen, NAS_ESM_GetCurEsmSndNwMsgAddr());
        NAS_ESM_UpdateEsmSndNwMsgLen(ulSndNwMsgLen);
    }

    if (ulStateTblIndex == NAS_ESM_ILL_STATETAL_INDEX)
    {
        return ;
    }

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    /*向APP发送SmAppCnf消息,*/
    if(ID_APP_ESM_PDP_SETUP_REQ == pstStateAddr->stAppMsgRecord.enAppMsgType )
    {
        /*向APP发送ID_APP_ESM_PDP_SETUP_CNF(失败)消息*/
        NAS_ESM_SndEsmAppSdfSetupCnfFailMsg(ulStateTblIndex, \
                                 NAS_ESM_GetAppErrorByEsmCause(pstEncodeInfo->ucESMCau));

        if (NAS_ESM_PTI_UNASSIGNED_VALUE != pstEncodeInfo->ucPti)
        {
            /* 缓存PTI和回复消息，包含了CAUSE原因值为NAS_ESM_CAUSE_ERROR的情况 */
            ulRslt= NAS_ESM_SavePtiBuffItem(pstEncodeInfo->ucPti,
                                            (VOS_UINT8)pstEncodeInfo->ulEpsbId,
                                            ulSndNwMsgLen,
                                            NAS_ESM_GetCurEsmSndNwMsgAddr());
            if (ulRslt != NAS_ESM_SUCCESS)
            {
                NAS_ESM_WARN_LOG("NAS_ESM_ActDediBearFailProc:WARN:Save pti buffer item failed!");
                TLPS_PRINT2LAYER_WARNING(NAS_ESM_ActDediBearFailProc_ENUM, LNAS_FAIL);
            }
        }
    }

    /*释放状态表资源*/
    NAS_ESM_RelStateTblResource(ulStateTblIndex);
}

/*****************************************************************************
 Function Name   : NAS_ESM_BearModFailProc
 Description     : 承载修改失败处理
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-12-4  Draft Enact
    2.lihong00150010      2010-02-10 Modify
*****************************************************************************/
VOS_VOID  NAS_ESM_BearModFailProc
(
    const NAS_ESM_ENCODE_INFO_STRU     *pstEncodeInfo,
    VOS_UINT32                          ulStateTblIndex
)
{
    VOS_UINT32                          ulSndNwMsgLen    = NAS_ESM_NULL;
    VOS_UINT32                          ulRslt           = NAS_ESM_NULL;

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_BearModFailProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_BearModFailProc_ENUM, LNAS_ENTRY);

    if( NAS_ESM_CAUSE_ERROR != pstEncodeInfo->ucESMCau )
    {
        /*向网侧回复Modify EPS bearer context reject*/
        NAS_ESM_EncodeModEpsbCntxtRejMsg(   *pstEncodeInfo, \
                                            NAS_ESM_GetCurEsmSndNwMsgAddr(),\
                                            &ulSndNwMsgLen);
        NAS_ESM_SndAirMsgReportInd(     NAS_ESM_GetCurEsmSndNwMsgAddr(),\
                                        ulSndNwMsgLen, NAS_ESM_AIR_MSG_DIR_ENUM_UP,\
                                        ESM_MOD_EPS_BEARER_CNTXT_REJ);
        NAS_ESM_SndEsmEmmDataReqMsg(NAS_ESM_ILLEGAL_OPID, PS_FALSE, ulSndNwMsgLen, NAS_ESM_GetCurEsmSndNwMsgAddr());
        NAS_ESM_UpdateEsmSndNwMsgLen(ulSndNwMsgLen);
    }

    if (ulStateTblIndex == NAS_ESM_ILL_STATETAL_INDEX)
    {
        return ;
    }

    /* 若是APP主动发起则回复失败消息 */
    NAS_ESM_InformAppEpsBearerModFail(ulStateTblIndex, pstEncodeInfo->ucESMCau);

    if (NAS_ESM_PTI_UNASSIGNED_VALUE != pstEncodeInfo->ucPti)
    {
        /* 缓存PTI和回复消息，包含了CAUSE原因值为NAS_ESM_CAUSE_ERROR的情况 */
        ulRslt = NAS_ESM_SavePtiBuffItem(pstEncodeInfo->ucPti,
                                         (VOS_UINT8)pstEncodeInfo->ulEpsbId,
                                         ulSndNwMsgLen,
                                         NAS_ESM_GetCurEsmSndNwMsgAddr());
        if (ulRslt != NAS_ESM_SUCCESS)
        {
            NAS_ESM_WARN_LOG("NAS_ESM_BearModFailProc:WARN:Save pti buffer item failed!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_BearModFailProc_ENUM, LNAS_FAIL);
        }
    }

    /*释放状态表资源*/
    NAS_ESM_RelStateTblResource(ulStateTblIndex);
}

/*****************************************************************************
 Function Name   : NAS_ESM_SaveNwModEpsbNoTft
 Description     : 保存承载修改激活的上下文信息(NO TFT)
 Input           : pstMsgIE         -- 译码后的网络消息
                   ulStateTblIndex  -- 动态表索引
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2011-06-20  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_SaveNwModEpsbNoTft
(
    const  NAS_ESM_NW_MSG_STRU          *pstMsgIE,
    VOS_UINT32                           ulStateTblIndex
)
{
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr     = VOS_NULL_PTR;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo  = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo = VOS_NULL_PTR;

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    pstSdfCntxtInfo = NAS_ESM_GetSdfCntxtInfo(pstStateAddr->ulCid);

    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(pstMsgIE->ucEpsbId);

    /* 如果不带QOS */
    if( NAS_ESM_OP_TRUE != pstMsgIE->bitOpEpsQos)
    {
        NAS_ESM_NORM_LOG("NAS_ESM_SaveNwModEpsbNoTft:No Qos Info!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_BearModFailProc_ENUM, ESM_NO_QOS_INFO);
        return ;
    }

    NAS_ESM_UpdateEpsQosInfo(pstMsgIE, pstEpsbCntxtInfo, pstSdfCntxtInfo);
}

/*****************************************************************************
 Function Name   : NAS_ESM_SaveNwModDeftEpsbAddPf
 Description     : 保存缺省承载修改激活的上下文信息(ADD PF)
 Input           : pstMsgIE         -- 译码后的网络消息
                   ulStateTblIndex  -- 动态表索引
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2011-06-20  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_SaveNwModDeftEpsbAddPf
(
    const  NAS_ESM_NW_MSG_STRU          *pstMsgIE,
    VOS_UINT32                           ulStateTblIndex
)
{
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr     = VOS_NULL_PTR;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo  = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo = VOS_NULL_PTR;

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    pstSdfCntxtInfo = NAS_ESM_GetSdfCntxtInfo(pstStateAddr->ulCid);

    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(pstMsgIE->ucEpsbId);

    /* 赋值SDF关联的承载信息 */
    pstSdfCntxtInfo->ulEpsbId = pstMsgIE->ucEpsbId;

    /* 若没有找到相同的则添加，若找到相同的则替换 */
    NAS_ESM_ReplacePacketFilterProc(pstMsgIE, pstSdfCntxtInfo);

    /* 如果不带QOS */
    if( NAS_ESM_OP_TRUE != pstMsgIE->bitOpEpsQos)
    {
        NAS_ESM_NORM_LOG("NAS_ESM_SaveNwModDeftEpsbAddPf:No Qos Info!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_SaveNwModDeftEpsbAddPf_ENUM, ESM_NO_QOS_INFO);
        return ;
    }

    NAS_ESM_UpdateEpsQosInfo(pstMsgIE, pstEpsbCntxtInfo, pstSdfCntxtInfo);
}

/*****************************************************************************
 Function Name   : NAS_ESM_SaveNwModDeftEpsbReplacePf
 Description     : 保存缺省承载修改激活的上下文信息(REPLACE PF)
 Input           : pstMsgIE         -- 译码后的网络消息
                   ulStateTblIndex  -- 动态表索引
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2011-06-20  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_SaveNwModDeftEpsbReplacePf
(
    const  NAS_ESM_NW_MSG_STRU          *pstMsgIE,
    VOS_UINT32                           ulStateTblIndex
)
{
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr     = VOS_NULL_PTR;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo  = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo = VOS_NULL_PTR;

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    pstSdfCntxtInfo = NAS_ESM_GetSdfCntxtInfo(pstStateAddr->ulCid);

    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(pstMsgIE->ucEpsbId);

    /* 赋值SDF关联的承载信息 */
    pstSdfCntxtInfo->ulEpsbId = pstMsgIE->ucEpsbId;

    /* 若没有找到相同的则添加，若找到相同的则替换 */
    NAS_ESM_ReplacePacketFilterProc(pstMsgIE, pstSdfCntxtInfo);

    /* 如果不带QOS */
    if( NAS_ESM_OP_TRUE != pstMsgIE->bitOpEpsQos)
    {
        NAS_ESM_NORM_LOG("NAS_ESM_SaveNwModDeftEpsbReplacePf:No Qos Info!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_SaveNwModDeftEpsbReplacePf_ENUM, ESM_NO_QOS_INFO);
        return ;
    }

    NAS_ESM_UpdateEpsQosInfo(pstMsgIE, pstEpsbCntxtInfo, pstSdfCntxtInfo);
}

/*****************************************************************************
 Function Name   : NAS_ESM_SaveNwModDeftEpsbDeletePf
 Description     : 保存缺省承载修改激活的上下文信息(DELETE PF)
 Input           : pstMsgIE         -- 译码后的网络消息
                   ulStateTblIndex  -- 动态表索引
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2011-06-20  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_SaveNwModDeftEpsbDeletePf
(
    const  NAS_ESM_NW_MSG_STRU          *pstMsgIE,
    VOS_UINT32                           ulStateTblIndex
)
{
    VOS_UINT32                          ulCnt           = NAS_ESM_NULL;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr     = VOS_NULL_PTR;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo  = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo = VOS_NULL_PTR;

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    pstSdfCntxtInfo = NAS_ESM_GetSdfCntxtInfo(pstStateAddr->ulCid);

    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(pstMsgIE->ucEpsbId);

    /* 删除SDF上下文中指定的Pakketfilter */
    for (ulCnt = 0; ulCnt < pstMsgIE->stTadInfo.ucSdfPfNum; ulCnt++)
    {
        NAS_ESM_DeleteOnePacketFilter(pstSdfCntxtInfo,
                                      pstMsgIE->stTadInfo.astSdfPfInfo[ulCnt].ucNwPacketFilterId);
    }

    /* 如果不带QOS */
    if( NAS_ESM_OP_TRUE != pstMsgIE->bitOpEpsQos)
    {
        NAS_ESM_NORM_LOG("NAS_ESM_SaveNwModDeftEpsbDeletePf:No Qos Info!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_SaveNwModDeftEpsbDeletePf_ENUM, ESM_NO_QOS_INFO);
        return ;
    }

    NAS_ESM_UpdateEpsQosInfo(pstMsgIE, pstEpsbCntxtInfo, pstSdfCntxtInfo);
}

/*****************************************************************************
 Function Name   : NAS_ESM_SaveNwModDeftEpsbNoOperation
 Description     : 保存缺省承载修改激活的上下文信息(NO OPERATION)
 Input           : pstMsgIE         -- 译码后的网络消息
                   ulStateTblIndex  -- 动态表索引
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2011-06-20  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_SaveNwModDeftEpsbNoOperation
(
    const  NAS_ESM_NW_MSG_STRU          *pstMsgIE,
    VOS_UINT32                           ulStateTblIndex
)
{
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr     = VOS_NULL_PTR;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo  = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo = VOS_NULL_PTR;

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    pstSdfCntxtInfo = NAS_ESM_GetSdfCntxtInfo(pstStateAddr->ulCid);

    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(pstMsgIE->ucEpsbId);

    /* 如果不带QOS */
    if( NAS_ESM_OP_TRUE != pstMsgIE->bitOpEpsQos)
    {
        NAS_ESM_NORM_LOG("NAS_ESM_SaveNwModDeftEpsbNoOperation:No Qos Info!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_SaveNwModDeftEpsbNoOperation_ENUM, ESM_NO_QOS_INFO);
        return ;
    }

    NAS_ESM_UpdateEpsQosInfo(pstMsgIE, pstEpsbCntxtInfo, pstSdfCntxtInfo);
}

/*****************************************************************************
 Function Name   : NAS_ESM_SaveNwModDeftEpsbCreateTft
 Description     : 保存缺省承载修改激活的上下文信息(CREATE TFT)
 Input           : pstMsgIE         -- 译码后的网络消息
                   ulStateTblIndex  -- 动态表索引
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2011-06-20  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_SaveNwModDeftEpsbCreateTft
(
    const  NAS_ESM_NW_MSG_STRU          *pstMsgIE,
    VOS_UINT32                           ulStateTblIndex
)
{
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr     = VOS_NULL_PTR;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo  = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo = VOS_NULL_PTR;

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    pstSdfCntxtInfo = NAS_ESM_GetSdfCntxtInfo(pstStateAddr->ulCid);
    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(pstMsgIE->ucEpsbId);

    /* 创建TFT */
    NAS_ESM_CreateTftProc(pstMsgIE, pstSdfCntxtInfo);

    NAS_ESM_UpdateEpsQosInfo(pstMsgIE, pstEpsbCntxtInfo, pstSdfCntxtInfo);
}

/*****************************************************************************
 Function Name   : NAS_ESM_SaveNwModDeftEpsbDeleteTft
 Description     : 保存缺省承载修改激活的上下文信息(DELETE TFT)
 Input           : pstMsgIE         -- 译码后的网络消息
                   ulStateTblIndex  -- 动态表索引
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2011-06-20  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_SaveNwModDeftEpsbDeleteTft
(
    const  NAS_ESM_NW_MSG_STRU          *pstMsgIE,
    VOS_UINT32                           ulStateTblIndex
)
{
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr     = VOS_NULL_PTR;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo  = VOS_NULL_PTR;

    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo = VOS_NULL_PTR;

    (VOS_VOID)(pstMsgIE);

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    pstSdfCntxtInfo = NAS_ESM_GetSdfCntxtInfo(pstStateAddr->ulCid);
    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(pstMsgIE->ucEpsbId);

    /* 删除TFT */
    NAS_ESM_DeleteTftProc(pstSdfCntxtInfo);

    NAS_ESM_UpdateEpsQosInfo(pstMsgIE, pstEpsbCntxtInfo, pstSdfCntxtInfo);
}

/*****************************************************************************
 Function Name   : NAS_ESM_SetAppPfId
 Description     : 根据网侧的PfId设置App PF ID
 Input           :

 Output          : None
 Return          : VOS_VOID

 History         :
    1.y00159566        2011-7-1       Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_SetAppPfId
(
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara
)
{
    VOS_UINT32                          ulCnt = NAS_ESM_NULL;

    /* 判断长度 */
    if (pstSdfPara->ulPfNum > NAS_ESM_MAX_SDF_PF_NUM)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_SetAppPfId:Pf Num is overflow!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_SetAppPfId_ENUM, 1);

        return;
    }

    /* 循环赋值 */
    for (ulCnt = 0; ulCnt < pstSdfPara->ulPfNum; ulCnt++)
    {
        pstSdfPara->astCntxtTftInfo[ulCnt].ucPacketFilterId
                   = pstSdfPara->astCntxtTftInfo[ulCnt].ucNwPacketFilterId;
    }

    return;
}


/*****************************************************************************
 Function Name   : NAS_ESM_IsExistlinkedPfInSdfCntxt
 Description     : 在动态信息的Pf是否存在对应的静态Pf
 Input           :
 Output          : None
 Return          : VOS_VOID

 History         :
    1.y00159566      2011-7-3  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_ESM_IsExistlinkedPfInSdfCntxt( VOS_UINT32 ulCid,VOS_UINT32 ulSdfParaPfId )
{
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo     = VOS_NULL_PTR;
    VOS_UINT32                          ulCnt;

    pstSdfCntxtInfo    = NAS_ESM_GetSdfCntxtInfo(ulCid);

    for(ulCnt = 0; ulCnt < pstSdfCntxtInfo->ulSdfPfNum; ulCnt++)
    {
        if (pstSdfCntxtInfo->astSdfPfInfo[ulCnt].ucPacketFilterId == ulSdfParaPfId)
        {
            return PS_TRUE;
        }
    }

    return PS_FALSE;
}

/*****************************************************************************
 Function Name   : NAS_ESM_GetAppPfId
 Description     : 获得AppPfId
 Input           :
 Output          : None
 Return          : VOS_VOID

 History         :
    1.y00159566      2011-7-3  Draft Enact

*****************************************************************************/
VOS_UINT8 NAS_ESM_GetAppPfId( VOS_UINT32 ulCid )
{
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo     = VOS_NULL_PTR;
    VOS_UINT8                           ucCnt;
    VOS_UINT32                          ulDynCnt;

    pstSdfCntxtInfo    = NAS_ESM_GetSdfCntxtInfo(ulCid);

    for (ucCnt = 1; ucCnt <= NAS_ESM_MAX_SDF_PF_NUM; ucCnt++)
    {
        for (ulDynCnt = 0; ulDynCnt < pstSdfCntxtInfo->ulSdfPfNum; ulDynCnt++)
        {
            if (pstSdfCntxtInfo->astSdfPfInfo[ulDynCnt].ucPacketFilterId == ucCnt)
            {
                break;
            }
        }

        if (ulDynCnt >= pstSdfCntxtInfo->ulSdfPfNum)
        {
            return ucCnt;
        }
    }

    return NAS_ESM_NULL;
}



VOS_VOID NAS_ESM_ModulateSdfTft
(
    VOS_UINT32                          ulStateTblIndex
)
{
    VOS_UINT32                          ulCnt               = NAS_ESM_NULL;
    VOS_UINT8                           ucAppPfId           = NAS_ESM_NULL;
    VOS_UINT32                          ulDynNum            = NAS_ESM_NULL;
    VOS_UINT32                          ulStaNum            = NAS_ESM_NULL;
    VOS_UINT32                          aulDynPfId[NAS_ESM_MAX_SDF_PF_NUM] = {NAS_ESM_NULL};
    VOS_UINT32                          aulStaPfId[NAS_ESM_MAX_SDF_PF_NUM] = {NAS_ESM_NULL};
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo     = VOS_NULL_PTR;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara          = VOS_NULL_PTR;
    VOS_UINT32                          ulLoopTimes         = NAS_ESM_NULL;
    VOS_UINT32                          ulRslt              = PS_FALSE;

    pstStateAddr     = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    pstSdfCntxtInfo  = NAS_ESM_GetSdfCntxtInfo(pstStateAddr->ulCid);

    pstSdfPara       = NAS_ESM_GetSdfParaAddr(pstStateAddr->ulCid);

    /* 查找动态信息，如果AppPfId为0则认为是未绑定的SDF,放入动态队列中 */
    for (ulCnt = 0; ulCnt < pstSdfCntxtInfo->ulSdfPfNum; ulCnt++)
    {
        if (NAS_ESM_NULL == pstSdfCntxtInfo->astSdfPfInfo[ulCnt].ucPacketFilterId)
        {
            aulDynPfId[ulDynNum++] = ulCnt;
        }
    }

    /* 遍历所有静态信息，如果AppPfId无法在动态信息中找到则表示此静态信息没有动态
    信息关联 */
    for (ulCnt = 0; ulCnt < pstSdfPara->ulPfNum; ulCnt++)
    {
        ulRslt =  NAS_ESM_IsExistlinkedPfInSdfCntxt(pstStateAddr->ulCid,
                                                    pstSdfPara->astCntxtTftInfo[ulCnt].ucPacketFilterId);
        if (ulRslt == PS_FALSE)
        {
            aulStaPfId[ulStaNum++] = ulCnt;
        }
    }

    /* 如果静态PfId比动态的多，则只需要保证每个动态信息都有静态的PfId关联即可 */
    ulLoopTimes     = NAS_ESM_MIN(ulDynNum, ulStaNum);

    for (ulCnt = NAS_ESM_NULL; ulCnt < ulLoopTimes; ulCnt++)
    {
        pstSdfCntxtInfo->astSdfPfInfo[aulDynPfId[ulCnt]].ucPacketFilterId =
                        pstSdfPara->astCntxtTftInfo[aulStaPfId[ulCnt]].ucPacketFilterId;
    }

    /* 如果动态信息比静态信息多，遍历所有没有关联的动态PfId,与未使用的静态PfId关联起来，
    并将动态信息拷贝到静态信息中 */
    for (ulCnt = 0; ulCnt < pstSdfCntxtInfo->ulSdfPfNum; ulCnt++)
    {
        if (NAS_ESM_NULL == pstSdfCntxtInfo->astSdfPfInfo[ulCnt].ucPacketFilterId)
        {
            /* 获取一个没有使用的静态PfId */
            ucAppPfId = NAS_ESM_GetAppPfId(pstStateAddr->ulCid);
            if (NAS_ESM_NULL == ucAppPfId)
            {
                NAS_ESM_ERR_LOG("NAS_ESM_ModulateSdfTft: Get App PfId Failed.");
                TLPS_PRINT2LAYER_ERROR(NAS_ESM_ModulateSdfTft_ENUM, LNAS_FAIL);

                return;
            }

            /* 设置当前PF的APP PF ID为ulAppPfId */
            pstSdfCntxtInfo->astSdfPfInfo[ulCnt].ucPacketFilterId = ucAppPfId;

            /* 拷贝当前PF至SDF的静态信息中，静态信息的PF数加1 */
            NAS_ESM_MEM_CPY_S(  &(pstSdfPara->astCntxtTftInfo[pstSdfPara->ulPfNum]),
                                sizeof(NAS_ESM_CONTEXT_TFT_STRU),
                                &(pstSdfCntxtInfo->astSdfPfInfo[ulCnt]),
                                sizeof(NAS_ESM_CONTEXT_TFT_STRU));

            pstSdfPara->ulPfNum++;
        }
    }

}

VOS_VOID NAS_ESM_ModulateSdfQos
(
    VOS_UINT32                          ulStateTblIndex
)
{
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo     = VOS_NULL_PTR;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara          = VOS_NULL_PTR;

    pstStateAddr     = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    pstSdfCntxtInfo  = NAS_ESM_GetSdfCntxtInfo(pstStateAddr->ulCid);

    pstSdfPara       = NAS_ESM_GetSdfParaAddr(pstStateAddr->ulCid);

    /* 如果静态信息中没有Qci信息，则将动态信息拷贝到静态信息中 */
    if (NAS_ESM_OP_FALSE == pstSdfPara->bitOpSdfQos)
    {
        pstSdfPara->bitOpSdfQos = NAS_ESM_OP_TRUE;

        NAS_ESM_MEM_CPY_S(  &(pstSdfPara->stSdfQosInfo),
                             sizeof(APP_ESM_EPS_QOS_INFO_STRU),
                             &(pstSdfCntxtInfo->stSdfQosInfo.stQosInfo),
                             sizeof(APP_ESM_EPS_QOS_INFO_STRU));
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_ESM_SaveNwModDediEpsbAddPf
 Description     : 保存专有承载修改激活的上下文信息(ADD PF)
 Input           : pstMsgIE         -- 译码后的网络消息
                   ulStateTblIndex  -- 动态表索引
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2011-06-20  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_SaveNwModDediEpsbAddPf
(
    const  NAS_ESM_NW_MSG_STRU          *pstMsgIE,
    VOS_UINT32                           ulStateTblIndex
)
{
    VOS_UINT32                          ulRslt              = NAS_ESM_NULL;
    VOS_UINT32                          ulCidTmp            = NAS_ESM_NULL;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfoTmp  = VOS_NULL_PTR;
    APP_ESM_EPS_QOS_INFO_STRU          *pstEpsQosInfo       = VOS_NULL_PTR;
    APP_ESM_EPS_QOS_INFO_STRU          *pstSdfQosInfo       = VOS_NULL_PTR;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo     = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo    = VOS_NULL_PTR;

    pstStateAddr     = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    pstSdfCntxtInfo  = NAS_ESM_GetSdfCntxtInfo(pstStateAddr->ulCid);

    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(pstMsgIE->ucEpsbId);

    /* 若空口消息中携带的预添加的packet filter在承载下已全部存在或部分存在,
       且已存在的packet filter所属的sdf与动态表中存储的用户预操作的sdf不一致，
       则删除已存在的packet filter所属的sdf并更新承载QOS信息 */
    ulRslt = NAS_ESM_QuerySdfId(pstMsgIE, &ulCidTmp);
    if((NAS_ESM_QUERY_CID_RSLT_ALL_UNFOUND != ulRslt)
        && (ulCidTmp != pstStateAddr->ulCid))
    {
        NAS_ESM_INFO_LOG("NAS_ESM_SaveNwModDediEpsbAddPf:packet filter already exist in other sdf!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_SaveNwModDediEpsbAddPf_ENUM, ESM_packet_filter_already_exist_in_other_sdf);

        pstSdfCntxtInfoTmp = NAS_ESM_GetSdfCntxtInfo(ulCidTmp);

        pstEpsQosInfo = &pstEpsbCntxtInfo->stEpsQoSInfo.stQosInfo;
        pstSdfQosInfo = &pstSdfCntxtInfoTmp->stSdfQosInfo.stQosInfo;

        if (PS_TRUE == NAS_ESM_IsGbrBearer(pstEpsQosInfo->ucQCI))
        {
            pstEpsQosInfo->ulULMaxRate -= pstSdfQosInfo->ulULMaxRate;
            pstEpsQosInfo->ulDLMaxRate -= pstSdfQosInfo->ulDLMaxRate;
            pstEpsQosInfo->ulULGMaxRate -= pstSdfQosInfo->ulULGMaxRate;
            pstEpsQosInfo->ulDLGMaxRate -= pstSdfQosInfo->ulDLGMaxRate;
        }

        /* 删除旧SDF上下文 */
        NAS_ESM_MEM_SET_S(  pstSdfCntxtInfoTmp,
                            sizeof(NAS_ESM_SDF_CNTXT_INFO_STRU),
                            0,
                            sizeof(NAS_ESM_SDF_CNTXT_INFO_STRU));

        /* 上报APP SDF释放 */
        NAS_ESM_SndEsmAppSdfRelIndMsg(ulCidTmp, pstMsgIE->ucEpsbId);

        /* 清除承载关联的此CID */
        NAS_ESM_ClearBearCntxtLinkCid(pstMsgIE->ucEpsbId, ulCidTmp);
    }

    /* 赋值SDF关联的承载信息 */
    pstSdfCntxtInfo->ulEpsbId = pstMsgIE->ucEpsbId;

    /* 如果是专有承载，且当前SDF的PF数为0,则说明此次操作为添加SDF，因此将上报
       类型修改为NAS_ESM_APP_IND_TYPE_SETUP */
    if ((NAS_ESM_NULL == pstSdfCntxtInfo->ulSdfPfNum)
        && (NAS_ESM_BEARER_TYPE_DEDICATED == pstEpsbCntxtInfo->enBearerCntxtType))
    {
        pstStateAddr->enAppIndType = NAS_ESM_APP_IND_TYPE_SETUP;
    }

    /* 若没有找到相同的则添加，若找到相同的则替换 */
    NAS_ESM_ReplacePacketFilterProc(pstMsgIE, pstSdfCntxtInfo);

    /* 如果静态和动态信息不一致，则进行调整 */
    NAS_ESM_ModulateSdfTft(ulStateTblIndex);

    /* 如果不带QOS */
    if( NAS_ESM_OP_TRUE != pstMsgIE->bitOpEpsQos)
    {
        /* 对于NON-GBR承载，当收到网侧的承载修改请求，TAD码为ADD SDF，且不带QOS信息时,
           将承载QOS信息中的QCI赋值给新增SDF的QCI*/
        if (PS_FALSE == NAS_ESM_IsGbrBearer(pstEpsbCntxtInfo->stEpsQoSInfo.stQosInfo.ucQCI))
        {
            NAS_ESM_MEM_SET_S(  &pstSdfCntxtInfo->stSdfQosInfo,
                                sizeof (NAS_ESM_CONTEXT_LTE_QOS_STRU),
                                NAS_ESM_NULL,
                                sizeof (NAS_ESM_CONTEXT_LTE_QOS_STRU));

            /* 更新SDF的QCI信息 */
            pstSdfCntxtInfo->stSdfQosInfo.stQosInfo.ucQCI =
                        pstEpsbCntxtInfo->stEpsQoSInfo.stQosInfo.ucQCI;

            pstSdfCntxtInfo->stSdfQosInfo.ucNwQCI =
                        pstEpsbCntxtInfo->stEpsQoSInfo.ucNwQCI;

        }

        return ;
    }

    NAS_ESM_UpdateEpsQosInfo(pstMsgIE, pstEpsbCntxtInfo, pstSdfCntxtInfo);

    NAS_ESM_ModulateSdfQos(ulStateTblIndex);
}

/*****************************************************************************
 Function Name   : NAS_ESM_SaveNwModDediEpsbReplacePf
 Description     : 保存专有承载修改激活的上下文信息(Replace PF)
 Input           : pstMsgIE         -- 译码后的网络消息
                   ulStateTblIndex  -- 动态表索引
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2011-06-20  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_SaveNwModDediEpsbReplacePf
(
    const  NAS_ESM_NW_MSG_STRU          *pstMsgIE,
    VOS_UINT32                           ulStateTblIndex
)
{
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr     = VOS_NULL_PTR;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo  = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo = VOS_NULL_PTR;

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    pstSdfCntxtInfo = NAS_ESM_GetSdfCntxtInfo(pstStateAddr->ulCid);

    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(pstMsgIE->ucEpsbId);

    /* 赋值SDF关联的承载信息 */
    pstSdfCntxtInfo->ulEpsbId = pstMsgIE->ucEpsbId;

    /* 若没有找到相同的则添加，若找到相同的则替换 */
    NAS_ESM_ReplacePacketFilterProc(pstMsgIE, pstSdfCntxtInfo);

    /* 如果静态和动态信息不一致，则进行调整 */
    NAS_ESM_ModulateSdfTft(ulStateTblIndex);

    /* 如果不带QOS */
    if( NAS_ESM_OP_TRUE != pstMsgIE->bitOpEpsQos)
    {
        NAS_ESM_NORM_LOG("NAS_ESM_SaveNwModDediEpsbReplacePf:No Qos Info!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_SaveNwModDediEpsbReplacePf_ENUM, ESM_NO_QOS_INFO);
        return ;
    }

    NAS_ESM_UpdateEpsQosInfo(pstMsgIE, pstEpsbCntxtInfo, pstSdfCntxtInfo);

    NAS_ESM_ModulateSdfQos(ulStateTblIndex);
}

/*****************************************************************************
 Function Name   : NAS_ESM_SaveNwModDediEpsbCreatPf
 Description     : 保存专有承载修改激活的上下文信息(Creat PF)
 Input           : pstMsgIE         -- 译码后的网络消息
                   ulStateTblIndex  -- 动态表索引
 Return          : VOS_UINT32

 History         :
    1.w00209181     2014-11-04  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_SaveNwModDediEpsbCreatPf
(
    const  NAS_ESM_NW_MSG_STRU          *pstMsgIE,
    VOS_UINT32                           ulStateTblIndex
)
{   VOS_UINT32                          ulRslt              = NAS_ESM_NULL;
    VOS_UINT32                          ulCidTmp            = NAS_ESM_NULL;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfoTmp  = VOS_NULL_PTR;
    APP_ESM_EPS_QOS_INFO_STRU          *pstEpsQosInfo       = VOS_NULL_PTR;
    APP_ESM_EPS_QOS_INFO_STRU          *pstSdfQosInfo       = VOS_NULL_PTR;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr     = VOS_NULL_PTR;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo  = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo = VOS_NULL_PTR;

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    pstSdfCntxtInfo = NAS_ESM_GetSdfCntxtInfo(pstStateAddr->ulCid);

    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(pstMsgIE->ucEpsbId);

    /* 若空口消息中携带的预添加的packet filter在承载下已全部存在或部分存在,
       且已存在的packet filter所属的sdf与动态表中存储的用户预操作的sdf不一致，
       则删除已存在的packet filter所属的sdf并更新承载QOS信息 */
    ulRslt = NAS_ESM_QuerySdfId(pstMsgIE, &ulCidTmp);
    if((NAS_ESM_QUERY_CID_RSLT_ALL_UNFOUND != ulRslt)
        && (ulCidTmp != pstStateAddr->ulCid))
    {
        NAS_ESM_INFO_LOG("NAS_ESM_SaveNwModDediEpsbCreatPf:packet filter already exist in other sdf!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_SaveNwModDediEpsbCreatPf_ENUM, ESM_packet_filter_already_exist_in_other_sdf);

        pstSdfCntxtInfoTmp = NAS_ESM_GetSdfCntxtInfo(ulCidTmp);

        pstEpsQosInfo = &pstEpsbCntxtInfo->stEpsQoSInfo.stQosInfo;
        pstSdfQosInfo = &pstSdfCntxtInfoTmp->stSdfQosInfo.stQosInfo;

        if (PS_TRUE == NAS_ESM_IsGbrBearer(pstEpsQosInfo->ucQCI))
        {
            pstEpsQosInfo->ulULMaxRate -= pstSdfQosInfo->ulULMaxRate;
            pstEpsQosInfo->ulDLMaxRate -= pstSdfQosInfo->ulDLMaxRate;
            pstEpsQosInfo->ulULGMaxRate -= pstSdfQosInfo->ulULGMaxRate;
            pstEpsQosInfo->ulDLGMaxRate -= pstSdfQosInfo->ulDLGMaxRate;
        }

        /* 删除旧SDF上下文 */
        NAS_ESM_MEM_SET_S(  pstSdfCntxtInfoTmp,
                            sizeof(NAS_ESM_SDF_CNTXT_INFO_STRU),
                            0,
                            sizeof(NAS_ESM_SDF_CNTXT_INFO_STRU));

        /* 上报APP SDF释放 */
        NAS_ESM_SndEsmAppSdfRelIndMsg(ulCidTmp, pstMsgIE->ucEpsbId);

        /* 清除承载关联的此CID */
        NAS_ESM_ClearBearCntxtLinkCid(pstMsgIE->ucEpsbId, ulCidTmp);
    }


    /* 赋值SDF关联的承载信息 */
    pstSdfCntxtInfo->ulEpsbId = pstMsgIE->ucEpsbId;

    /* 删除旧的TFT信息 */
    NAS_ESM_MEM_SET_S(  pstSdfCntxtInfo->astSdfPfInfo,
                        sizeof(NAS_ESM_CONTEXT_TFT_STRU) * NAS_ESM_MAX_SDF_PF_NUM,
                        NAS_ESM_NULL,
                        sizeof(NAS_ESM_CONTEXT_TFT_STRU) * NAS_ESM_MAX_SDF_PF_NUM);

    pstSdfCntxtInfo->ulSdfPfNum = NAS_ESM_NULL;

    /* 添加新的TFT信息 */
    NAS_ESM_MEM_CPY_S(  pstSdfCntxtInfo->astSdfPfInfo,
                        sizeof(NAS_ESM_CONTEXT_TFT_STRU) * NAS_ESM_MAX_SDF_PF_NUM,
                        pstMsgIE->stTadInfo.astSdfPfInfo,
                        sizeof(NAS_ESM_CONTEXT_TFT_STRU) * pstMsgIE->stTadInfo.ucSdfPfNum);

    pstSdfCntxtInfo->ulSdfPfNum = pstMsgIE->stTadInfo.ucSdfPfNum;

    /* 如果静态和动态信息不一致，则进行调整 */
    NAS_ESM_ModulateSdfTft(ulStateTblIndex);


    /* 如果不带QOS */
    if( NAS_ESM_OP_TRUE != pstMsgIE->bitOpEpsQos)
    {
        /* 对于NON-GBR承载，当收到网侧的承载修改请求，TAD码为CREAT SDF，且不带QOS信息时,
           将承载QOS信息中的QCI赋值给新增SDF的QCI*/
        if (PS_FALSE == NAS_ESM_IsGbrBearer(pstEpsbCntxtInfo->stEpsQoSInfo.stQosInfo.ucQCI))
        {
            NAS_ESM_MEM_SET_S(  &pstSdfCntxtInfo->stSdfQosInfo,
                                sizeof (NAS_ESM_CONTEXT_LTE_QOS_STRU),
                                NAS_ESM_NULL,
                                sizeof (NAS_ESM_CONTEXT_LTE_QOS_STRU));

            /* 更新SDF的QCI信息 */
            pstSdfCntxtInfo->stSdfQosInfo.stQosInfo.ucQCI =
                        pstEpsbCntxtInfo->stEpsQoSInfo.stQosInfo.ucQCI;

            pstSdfCntxtInfo->stSdfQosInfo.ucNwQCI =
                        pstEpsbCntxtInfo->stEpsQoSInfo.ucNwQCI;

        }

        return ;
    }


    NAS_ESM_UpdateEpsQosInfo(pstMsgIE, pstEpsbCntxtInfo, pstSdfCntxtInfo);

    NAS_ESM_ModulateSdfQos(ulStateTblIndex);
}


/*****************************************************************************
 Function Name   : NAS_ESM_SaveNwModDediEpsbDeletePf
 Description     : 保存专有承载修改激活的上下文信息(DELETE PF)
 Input           : pstMsgIE         -- 译码后的网络消息
                   ulStateTblIndex  -- 动态表索引
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2011-06-20  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_SaveNwModDediEpsbDeletePf
(
    const  NAS_ESM_NW_MSG_STRU          *pstMsgIE,
    VOS_UINT32                           ulStateTblIndex
)
{
    VOS_UINT32                          ulCnt           = NAS_ESM_NULL;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr     = VOS_NULL_PTR;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo  = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo = VOS_NULL_PTR;
    APP_ESM_EPS_QOS_INFO_STRU          *pstEpsQosInfo   = VOS_NULL_PTR;
    APP_ESM_EPS_QOS_INFO_STRU          *pstSdfQosInfo   = VOS_NULL_PTR;

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    pstSdfCntxtInfo = NAS_ESM_GetSdfCntxtInfo(pstStateAddr->ulCid);

    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(pstMsgIE->ucEpsbId);

    pstEpsQosInfo = &(pstEpsbCntxtInfo->stEpsQoSInfo.stQosInfo);

    pstSdfQosInfo = &(pstSdfCntxtInfo->stSdfQosInfo.stQosInfo);

    /* 删除SDF上下文中指定的Pakketfilter */
    for (ulCnt = 0; ulCnt < pstMsgIE->stTadInfo.ucSdfPfNum; ulCnt++)
    {
        NAS_ESM_DeleteOnePacketFilter(pstSdfCntxtInfo,
                                      pstMsgIE->stTadInfo.astSdfPfInfo[ulCnt].ucNwPacketFilterId);
    }

    /* 若是专有承载，且此SDF的packet filter被全部删除，则删除此SDF */
    if (NAS_ESM_NULL == pstSdfCntxtInfo->ulSdfPfNum)
    {
        if (PS_TRUE == NAS_ESM_IsGbrBearer(pstEpsbCntxtInfo->stEpsQoSInfo.stQosInfo.ucQCI))
        {
            pstEpsQosInfo->ulULMaxRate -= pstSdfQosInfo->ulULMaxRate;
            pstEpsQosInfo->ulDLMaxRate -= pstSdfQosInfo->ulDLMaxRate;
            pstEpsQosInfo->ulULGMaxRate -= pstSdfQosInfo->ulULGMaxRate;
            pstEpsQosInfo->ulDLGMaxRate -= pstSdfQosInfo->ulDLGMaxRate;
        }

        /* 修改上报类型为NAS_ESM_APP_IND_TYPE_RELEASE */
        pstStateAddr->enAppIndType = NAS_ESM_APP_IND_TYPE_RELEASE;

        /* 删除SDF上下文 */
        NAS_ESM_MEM_SET_S(  pstSdfCntxtInfo,
                            sizeof(NAS_ESM_SDF_CNTXT_INFO_STRU),
                            0,
                            sizeof(NAS_ESM_SDF_CNTXT_INFO_STRU));

        return ;
    }

    /* 如果静态和动态信息不一致，则进行调整 */
    NAS_ESM_ModulateSdfTft(ulStateTblIndex);

    /* 如果不带QOS */
    if( NAS_ESM_OP_TRUE != pstMsgIE->bitOpEpsQos)
    {
        NAS_ESM_NORM_LOG("NAS_ESM_SaveNwModDediEpsbDeletePf:No Qos Info!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_SaveNwModDediEpsbDeletePf_ENUM, ESM_NO_QOS_INFO);
        return ;
    }

    NAS_ESM_UpdateEpsQosInfo(pstMsgIE, pstEpsbCntxtInfo, pstSdfCntxtInfo);

    NAS_ESM_ModulateSdfQos(ulStateTblIndex);
}
/*lint +e961*/
/*lint +e960*/
/*****************************************************************************
 Function Name   : NAS_ESM_SaveNwModDediEpsbNoOperation
 Description     : 保存专有承载修改激活的上下文信息(NO OPERATION)
 Input           : pstMsgIE         -- 译码后的网络消息
                   ulStateTblIndex  -- 动态表索引
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2011-06-20  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_SaveNwModDediEpsbNoOperation
(
    const  NAS_ESM_NW_MSG_STRU          *pstMsgIE,
    VOS_UINT32                           ulStateTblIndex
)
{
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr     = VOS_NULL_PTR;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo  = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo = VOS_NULL_PTR;

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    pstSdfCntxtInfo = NAS_ESM_GetSdfCntxtInfo(pstStateAddr->ulCid);

    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(pstMsgIE->ucEpsbId);

    /* 如果不带QOS */
    if( NAS_ESM_OP_TRUE != pstMsgIE->bitOpEpsQos)
    {
        NAS_ESM_NORM_LOG("NAS_ESM_SaveNwModDediEpsbNoOperation:No Qos Info!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_SaveNwModDediEpsbNoOperation_ENUM, ESM_NO_QOS_INFO);
        return ;
    }

    NAS_ESM_UpdateEpsQosInfo(pstMsgIE, pstEpsbCntxtInfo, pstSdfCntxtInfo);

    NAS_ESM_ModulateSdfQos(ulStateTblIndex);
}


/*****************************************************************************
 Function Name   : NAS_ESM_SaveNwModDeftEpsbReqInfo
 Description     : 保存缺省承载修改激活的上下文信息
 Input           : pstMsgIE         -- 译码后的网络消息
                   ulStateTblIndex  -- 动态表索引
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2011-06-20  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_SaveNwModDeftEpsbReqInfo
(
    const  NAS_ESM_NW_MSG_STRU          *pstMsgIE,
    VOS_UINT32                           ulStateTblIndex
)
{
    /* 如果没有TFT信息， 则调用NAS_ESM_SaveNwModDeftEpsbNoTft */
    if(NAS_ESM_OP_TRUE != pstMsgIE->bitOpTadInfo)
    {
        NAS_ESM_NORM_LOG("NAS_ESM_SaveNwModDeftEpsbReqInfo:No TFT Info!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_SaveNwModDeftEpsbReqInfo_ENUM, ESM_NO_TFT_INFO);
        NAS_ESM_SaveNwModEpsbNoTft(pstMsgIE, ulStateTblIndex);

        return ;
    }

    switch (pstMsgIE->stTadInfo.enTftOpType)
    {
        case NAS_ESM_TFT_OP_TYPE_ADD_FILTER :
            NAS_ESM_NORM_LOG("NAS_ESM_SaveNwModDeftEpsbReqInfo:ADD PF!");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_SaveNwModDeftEpsbReqInfo_ENUM, ESM_ADD_PF);
            NAS_ESM_SaveNwModDeftEpsbAddPf(pstMsgIE, ulStateTblIndex);
            break;

        case NAS_ESM_TFT_OP_TYPE_REPLACE_FILTER:
            NAS_ESM_NORM_LOG("NAS_ESM_SaveNwModDeftEpsbReqInfo:REPLACE PF!");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_SaveNwModDeftEpsbReqInfo_ENUM, ESM_REPLACE_PF);
            NAS_ESM_SaveNwModDeftEpsbReplacePf(pstMsgIE, ulStateTblIndex);
            break;

        case NAS_ESM_TFT_OP_TYPE_DELETE_FILTER:
            NAS_ESM_NORM_LOG("NAS_ESM_SaveNwModDeftEpsbReqInfo:DELETE PF!");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_SaveNwModDeftEpsbReqInfo_ENUM, ESM_DELETE_PF);
            NAS_ESM_SaveNwModDeftEpsbDeletePf(pstMsgIE, ulStateTblIndex);
            break;

        case NAS_ESM_TFT_OP_TYPE_NO_OP:
            NAS_ESM_NORM_LOG("NAS_ESM_SaveNwModDeftEpsbReqInfo:NO OPERATION!");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_SaveNwModDeftEpsbReqInfo_ENUM, ESM_NO_OPERATION);
            NAS_ESM_SaveNwModDeftEpsbNoOperation(pstMsgIE, ulStateTblIndex);
            break;

        case NAS_ESM_TFT_OP_TYPE_CREATE_TFT:
            NAS_ESM_NORM_LOG("NAS_ESM_SaveNwModDeftEpsbReqInfo:CRREATE TFT!");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_SaveNwModDeftEpsbReqInfo_ENUM, ESM_CREATE_TFT);
            NAS_ESM_SaveNwModDeftEpsbCreateTft(pstMsgIE, ulStateTblIndex);
            break;

        case NAS_ESM_TFT_OP_TYPE_DELETE_TFT:
            NAS_ESM_NORM_LOG("NAS_ESM_SaveNwModDeftEpsbReqInfo:DELETE TFT!");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_SaveNwModDeftEpsbReqInfo_ENUM, ESM_DELETE_TFT);
            NAS_ESM_SaveNwModDeftEpsbDeleteTft(pstMsgIE, ulStateTblIndex);
            break;

       default:
            NAS_ESM_WARN_LOG("NAS_ESM_SaveNwModDeftEpsbReqInfo:illegal tad!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_SaveNwModDeftEpsbReqInfo_ENUM, LNAS_PARAM_INVALID);
            break;
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_SaveNwModDediEpsbReqInfo
 Description     : 保存专有承载修改激活的上下文信息
 Input           : pstMsgIE         -- 译码后的网络消息
                   ulStateTblIndex  -- 动态表索引
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2011-06-20  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_SaveNwModDediEpsbReqInfo
(
    const  NAS_ESM_NW_MSG_STRU          *pstMsgIE,
    VOS_UINT32                           ulStateTblIndex
)
{
    /* 如果没有TFT信息， 则调用NAS_ESM_SaveNwModEpsbNoTft */
    if(NAS_ESM_OP_TRUE != pstMsgIE->bitOpTadInfo)
    {
        NAS_ESM_NORM_LOG("NAS_ESM_SaveNwModDediEpsbReqInfo:No TFT Info!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_SaveNwModDediEpsbReqInfo_ENUM, ESM_NO_TFT_INFO);
        NAS_ESM_SaveNwModEpsbNoTft(pstMsgIE, ulStateTblIndex);

        return ;
    }

    switch (pstMsgIE->stTadInfo.enTftOpType)
    {
        case NAS_ESM_TFT_OP_TYPE_ADD_FILTER :
            NAS_ESM_NORM_LOG("NAS_ESM_SaveNwModDediEpsbReqInfo:ADD PF!");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_SaveNwModDediEpsbReqInfo_ENUM, ESM_ADD_PF);
            NAS_ESM_SaveNwModDediEpsbAddPf(pstMsgIE, ulStateTblIndex);
            break;
        case NAS_ESM_TFT_OP_TYPE_CREATE_TFT:
            NAS_ESM_NORM_LOG("NAS_ESM_SaveNwModDediEpsbReqInfo:CREAT PF!");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_SaveNwModDediEpsbReqInfo_ENUM, ESM_CREATE_TFT);
            NAS_ESM_SaveNwModDediEpsbCreatPf(pstMsgIE, ulStateTblIndex);
            break;
        case NAS_ESM_TFT_OP_TYPE_REPLACE_FILTER:
            NAS_ESM_NORM_LOG("NAS_ESM_SaveNwModDediEpsbReqInfo:REPLACE PF!");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_SaveNwModDediEpsbReqInfo_ENUM, ESM_REPLACE_PF);
            NAS_ESM_SaveNwModDediEpsbReplacePf(pstMsgIE, ulStateTblIndex);
            break;

        case NAS_ESM_TFT_OP_TYPE_DELETE_FILTER:
            NAS_ESM_NORM_LOG("NAS_ESM_SaveNwModDediEpsbReqInfo:DELETE PF!");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_SaveNwModDediEpsbReqInfo_ENUM, ESM_DELETE_PF);
            NAS_ESM_SaveNwModDediEpsbDeletePf(pstMsgIE, ulStateTblIndex);
            break;

        case NAS_ESM_TFT_OP_TYPE_NO_OP:
            NAS_ESM_NORM_LOG("NAS_ESM_SaveNwModDediEpsbReqInfo:NO OPERATION!");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_SaveNwModDediEpsbReqInfo_ENUM, ESM_NO_OPERATION);
            NAS_ESM_SaveNwModDediEpsbNoOperation(pstMsgIE, ulStateTblIndex);
            break;

       default:
            NAS_ESM_WARN_LOG("NAS_ESM_SaveNwModDediEpsbReqInfo:illegal tad!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_SaveNwModDediEpsbReqInfo_ENUM, LNAS_PARAM_INVALID);
            break;
    }
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of NasEsmNwMsgBearerResAllocProc.c */
