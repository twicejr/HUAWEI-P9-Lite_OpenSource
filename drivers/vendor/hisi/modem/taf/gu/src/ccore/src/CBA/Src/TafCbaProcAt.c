

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "TafCbaProcAt.h"
#include  "TafCbsInterface.h"
#include  "TafCbaComFunc.h"
#include  "TafCbaProcUsim.h"

#include  "TafLog.h"
#include  "MnErrorCode.h"
#include  "MnMsgApi.h"
#include  "TafClientApi.h"
#include  "MnComm.h"
#include  "MnMsgSmCommProc.h"
#include  "TafTypeDef.h"
#include  "TafCbaProcNvim.h"
#include  "TafCbaMntn.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_CBA_PROC_AT_C

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

extern MN_MSG_EVENT_INFO_STRU           f_stMsgEventInfo;

/*lint -save -e958 */

/*****************************************************************************
  3 函数实现
*****************************************************************************/


VOS_VOID TAF_CBA_SndAtRcvCbmMsg(
    const MN_MSG_CBRAW_TS_DATA_STRU    *pstTpduData
)
{
    MN_MSG_CB_DELIVER_EVT_INFO_STRU    *pstCbDeliver;
    MN_OPERATION_ID_T                   ucOpId;

    /* 广播上报来一条CBS */
    ucOpId = MN_MSG_GetBCopId();

    PS_MEM_SET(&f_stMsgEventInfo,0x00,sizeof(f_stMsgEventInfo));

    f_stMsgEventInfo.opId           = ucOpId;
    f_stMsgEventInfo.clientId       = MN_CLIENT_ALL;
    pstCbDeliver                    = &(f_stMsgEventInfo.u.stCbsDeliverInfo);
    pstCbDeliver->bSuccess          = VOS_TRUE;
    pstCbDeliver->ulFailCause       = MN_ERR_NO_ERROR;
    PS_MEM_CPY(&pstCbDeliver->stCbRawData,pstTpduData,sizeof(MN_MSG_CBRAW_TS_DATA_STRU));

    MN_SendClientEvent(MN_CLIENT_ALL,
                       MN_CALLBACK_MSG,
                       MN_MSG_EVT_DELIVER_CBM,
                       &f_stMsgEventInfo);

}


VOS_VOID  TAF_CBA_SndAtGetAllCbMidsRslt(
    const MN_MSG_EVENT_PARM_STRU       *pstEventParm
)
{
    MN_MSG_CBMIDS_GET_EVT_INFO_STRU    *pstCbsCbMids;

    PS_MEM_SET(&f_stMsgEventInfo, 0x00, sizeof(f_stMsgEventInfo));

    f_stMsgEventInfo.opId   = pstEventParm->opId;
    pstCbsCbMids            = (MN_MSG_CBMIDS_GET_EVT_INFO_STRU *)&f_stMsgEventInfo.u.stCbsCbMids;

    if (MN_ERR_NO_ERROR != pstEventParm->ulFailCause)
    {
        pstCbsCbMids->bSuccess    = VOS_FALSE;
        pstCbsCbMids->ulFailCause = pstEventParm->ulFailCause;
    }
    else
    {
        pstCbsCbMids->bSuccess    = VOS_TRUE;
    }

    TAF_CBA_GetActiveMids(&(pstCbsCbMids->stCbMidr));

    MN_SendClientEvent(pstEventParm->clientId,
                       MN_CALLBACK_MSG,
                       MN_MSG_EVT_GET_CBTYPE,
                       &f_stMsgEventInfo);
}


VOS_VOID  TAF_CBA_SndAtModifyCbMidsRlst(
    const MN_MSG_EVENT_PARM_STRU       *pstEventParm,
    VOS_UINT32                          ulEventType
)
{
    MN_MSG_CBMIDS_CHANGE_EVT_INFO_STRU *pstCbMidsInfo;

    PS_MEM_SET(&f_stMsgEventInfo, 0X00, sizeof(f_stMsgEventInfo));

    f_stMsgEventInfo.opId   = pstEventParm->opId;
    pstCbMidsInfo           = (MN_MSG_CBMIDS_CHANGE_EVT_INFO_STRU *)&f_stMsgEventInfo.u.stCbsChangeInfo;

    if (MN_ERR_NO_ERROR != pstEventParm->ulFailCause)
    {
        pstCbMidsInfo->bSuccess    = VOS_FALSE;
        pstCbMidsInfo->ulFailCause = pstEventParm->ulFailCause;
    }
    else
    {
        pstCbMidsInfo->bSuccess    = VOS_TRUE;
    }

    MN_SendClientEvent(pstEventParm->clientId,
                       MN_CALLBACK_MSG,
                       ulEventType,
                       &f_stMsgEventInfo);

}


#if (FEATURE_ON == FEATURE_ETWS)


VOS_VOID  TAF_CBA_SndAtEtwsPrimNtfMsg(
    RR_CBS_ETWS_PRIMARY_NOTIFY_IND_STRU                    *pstPrimNtfMsg
)
{
    TAF_CBA_ETWS_PRIM_NTF_EVT_INFO_STRU                    *pstPrimNtfEvt;

    PS_MEM_SET(&f_stMsgEventInfo, 0X00, sizeof(f_stMsgEventInfo));

    /* 广播上报 */
    f_stMsgEventInfo.opId       = MN_MSG_GetBCopId();
    f_stMsgEventInfo.clientId   = MN_CLIENT_ALL;
    pstPrimNtfEvt               = &f_stMsgEventInfo.u.stEtwsPrimNtf;

    pstPrimNtfEvt->stPlmn.ulMcc = pstPrimNtfMsg->stCurrNetworkInfo.stCurPlmn.ulMcc;
    pstPrimNtfEvt->stPlmn.ulMnc = pstPrimNtfMsg->stCurrNetworkInfo.stCurPlmn.ulMnc;
    pstPrimNtfEvt->usWarnType   = pstPrimNtfMsg->usWarnType;
    pstPrimNtfEvt->usMsgId      = pstPrimNtfMsg->usMessageId;
    pstPrimNtfEvt->usSN         = pstPrimNtfMsg->usSerialNumber;

    /* 鉴权结果目前默认为未通过鉴权 */
    pstPrimNtfEvt->enAuthRslt   = TAF_CBA_ETWS_PRIM_NTF_AUTH_FAILED;

    MN_SendClientEvent(MN_CLIENT_ALL,
                       MN_CALLBACK_MSG,
                       MN_MSG_EVT_DELIVER_ETWS_PRIM_NOTIFY,
                       &f_stMsgEventInfo);

}

#endif /* (FEATURE_ON == FEATURE_ETWS) */



VOS_VOID TAF_CBA_InitEventParm(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_MSG_EVENT_PARM_STRU             *pstEventParm
)
{
    pstEventParm->clientId      = clientId;
    pstEventParm->opId          = opId;
    pstEventParm->ulFailCause   = MN_ERR_NO_ERROR;
}


VOS_VOID TAF_CBA_RcvAtGetAllCbMids(
    MN_CLIENT_ID_T                     clientId,
    MN_OPERATION_ID_T                  opId
)
{
    MN_MSG_EVENT_PARM_STRU             stEventParm;

    MN_SendClientResponse(clientId, opId, MN_ERR_NO_ERROR);

    TAF_CBA_InitEventParm(clientId, opId, &stEventParm);

    TAF_CBA_SndAtGetAllCbMidsRslt(&stEventParm);

    return;
}


VOS_VOID  TAF_CBA_RcvAtAddCbMids(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    TAF_CBA_CBMI_RANGE_LIST_STRU       *pstAddCbMidsList
)
{
    VOS_UINT32                          ulRet;
    MN_MSG_EVENT_PARM_STRU              stEventParm;


    /* AT设置过来的MID列表MSG ID需要调整为小的MSG ID
       放到usMsgIdFrom中,大的MSG ID放到usMsgIdTo中 */
    TAF_CBA_SortCbmiRangeList(pstAddCbMidsList);

    MN_SendClientResponse(clientId, opId, MN_ERR_NO_ERROR);

    TAF_CBA_InitEventParm(clientId, opId, &stEventParm);


    /* 有重复的MSG ID也允许设置 */

    /* 将当前的CBMIDR列表更新到内存中 */
    ulRet = TAF_CBA_AddCbMiRangeListToActiveList(pstAddCbMidsList);
    if (VOS_OK != ulRet)
    {
        stEventParm.ulFailCause = MN_ERR_CLASS_CBS_TOO_CBMIDS;
        TAF_CBA_SndAtModifyCbMidsRlst(&stEventParm, MN_MSG_EVT_ADD_CBMIDS);
        return;
    }

    /* 更新NV项和USIM文件以及发送消息 */
    TAF_CBA_RcvAtModifyMsgIds();

    /* 直接在此处上报,不需要等待接入层回复的CNF消息,此处有两种考虑,
           1.接入层回复的CNF失败后,无法恢复内存
           2.发送给USIM修改文件的接口,USIM文件处理失败后也不进行任何处理 */
    stEventParm.ulFailCause = MN_ERR_NO_ERROR;
    TAF_CBA_SndAtModifyCbMidsRlst(&stEventParm, MN_MSG_EVT_ADD_CBMIDS);
}


VOS_VOID TAF_CBA_RcvAtDelCbMids(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    TAF_CBA_CBMI_RANGE_LIST_STRU       *pstDelCbMids
)
{
    VOS_UINT32                          ulRet;
    MN_MSG_EVENT_PARM_STRU              stEventParm;


    MN_SendClientResponse(clientId, opId, MN_ERR_NO_ERROR);

    TAF_CBA_InitEventParm(clientId, opId, &stEventParm);

    /* 先对range list排序 */
    TAF_CBA_SortCbmiRangeList(pstDelCbMids);

    /* 从内存中删除CBMIDS,如果内存中没有则直接返回, 不更新USIM和NIVM以及AS */
    ulRet = TAF_CBA_DelCbMiRangeListFromActiveList(pstDelCbMids);
    if ( VOS_FALSE == ulRet )
    {
        stEventParm.ulFailCause = MN_ERR_NO_ERROR;
        TAF_CBA_SndAtModifyCbMidsRlst(&stEventParm, MN_MSG_EVT_DELETE_CBMIDS);
        return;
    }

    /* 删除不在激活列表中的历史记录项 */
    TAF_CBA_DelRecordByActiveList();

    /* 更新NV项和USIM文件以及发送消息 */
    TAF_CBA_RcvAtModifyMsgIds();

    /* 直接在此处上报,不需要等待接入层回复的CNF消息,此处有两种考虑,
           1.接入曾回复的CNF失败后,无法回复内存
           2.发送给USIM修改文件的接口,USIM文件处理失败后也不进行任何处理 */
    stEventParm.ulFailCause = MN_ERR_NO_ERROR;
    TAF_CBA_SndAtModifyCbMidsRlst(&stEventParm, MN_MSG_EVT_DELETE_CBMIDS);
}



VOS_VOID TAF_CBA_RcvAtEmptyCbMids(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId
)
{
    VOS_UINT32                          ulRet;
    MN_MSG_EVENT_PARM_STRU              stEventParm;


    MN_SendClientResponse(clientId, opId, MN_ERR_NO_ERROR);

    TAF_CBA_InitEventParm(clientId, opId, &stEventParm);

    /* 先判断CBMI RANGE LIST是否已为空 */
    ulRet = TAF_CBA_IsCbmiRangeListEmpty();
    if (VOS_TRUE == ulRet)
    {
       stEventParm.ulFailCause = MN_ERR_NO_ERROR;
       TAF_CBA_SndAtModifyCbMidsRlst(&stEventParm, MN_MSG_EVT_DELETE_ALL_CBMIDS);
       return;
    }

    /* 清空内存中CBMI RANGE LIST */
    TAF_CBA_InitCbmiRangeList();

    /* 清空CBS消息历史记录表 */
    TAF_CBA_InitRecordList();

    /* 更新NV项和USIM文件以及发送消息 */
    TAF_CBA_RcvAtModifyMsgIds();

    /* 直接在此处上报,不需要等待接入层回复的CNF消息,此处有两种考虑,
           1.接入曾回复的CNF失败后,无法回复内存
           2.发送给USIM修改文件的接口,USIM文件处理失败后也不进行任何处理 */
    stEventParm.ulFailCause = MN_ERR_NO_ERROR;
    TAF_CBA_SndAtModifyCbMidsRlst(&stEventParm, MN_MSG_EVT_DELETE_ALL_CBMIDS);

}


VOS_VOID TAF_CBA_ProcAtMsg(
    struct MsgCB                       *pstMsg
)
{
    MN_APP_REQ_MSG_STRU                *pstAppMsg;

    pstAppMsg = (MN_APP_REQ_MSG_STRU*)pstMsg;

    switch(pstAppMsg->usMsgName)
    {
        case MN_MSG_MSGTYPE_GET_ALLCBMIDS:
            TAF_CBA_RcvAtGetAllCbMids(pstAppMsg->clientId,
                                      pstAppMsg->opId);
            break;

        case MN_MSG_MSGTYPE_ADD_CBMIDS:
            TAF_CBA_RcvAtAddCbMids(pstAppMsg->clientId,
                                   pstAppMsg->opId,
                                  (TAF_CBA_CBMI_RANGE_LIST_STRU *)pstAppMsg->aucContent);
            break;
        case MN_MSG_MSGTYPE_DELETE_CBMIDS:
            TAF_CBA_RcvAtDelCbMids(pstAppMsg->clientId,
                                   pstAppMsg->opId,
                                  (TAF_CBA_CBMI_RANGE_LIST_STRU *)pstAppMsg->aucContent);
            break;

        case MN_MSG_MSGTYPE_EMPTY_CBMIDS:
            TAF_CBA_RcvAtEmptyCbMids(pstAppMsg->clientId,pstAppMsg->opId);
            break;

        default:
            break;
    }
}


VOS_VOID TAF_CBA_UpdateAsCbsActiveState(VOS_VOID)
{
    VOS_UINT32                          ulIsActiveListEmpty;

    /* 当前宏开关未打开或CBS未激活,则直接返回  */
    if ( VOS_FALSE == TAF_CBA_IsNeedActAsCbs())
    {
        return;
    }

    /* 根据激活列表是否为空, 决定激活或去激活AS的CBS功能 */
    ulIsActiveListEmpty = TAF_CBA_IsCbsActiveListEmpty();

    if (VOS_TRUE == ulIsActiveListEmpty)
    {
        TAF_CBA_SndAsActiveCbsReq(TAF_CBS_CFG_DEACTIVE);
    }
    else
    {
        TAF_CBA_SndAsActiveCbsReq(TAF_CBS_CFG_ACTIVE);
    }
}


VOS_VOID TAF_CBA_RcvAtModifyMsgIds(VOS_VOID)
{
    /* 更新NV项中的MSGID 列表 */
    TAF_CBA_WriteCbmiRangeListNvim();

    /* 更新USIM中的MSGID 文件 */
    TAF_CBA_UpdateUsimFile();

    /* 根据当前的激活列表情况调整接入层的CBS 功能 */
    TAF_CBA_UpdateAsCbsActiveState();

    /* 可维可测信息 */
    TAF_CBA_SndOmCbmiDownloadListInfo();

    /* 可维可测信息 */
    TAF_CBA_SndOmCbmiRangeList();

    return;
}


VOS_VOID TAF_CBA_GetActiveMids(
    TAF_CBA_CBMI_RANGE_LIST_STRU       *pstActiveCbMids
)
{
    VOS_INT32                           ulCbmidRangeInx;
    TAF_CBA_CBMI_RANGE_LIST_STRU       *pstCbmiRangeList;
    VOS_UINT16                          usCbmiRangNum;

    PS_MEM_SET(pstActiveCbMids, 0, sizeof(TAF_CBA_CBMI_RANGE_LIST_STRU));

    pstCbmiRangeList = TAF_CBA_GetCbMiRangeList();
    usCbmiRangNum    = TAF_CBA_GetCbmiRangNum();

    if (usCbmiRangNum >= TAF_CBA_MAX_CBMID_RANGE_NUM)
    {
        usCbmiRangNum = TAF_CBA_MAX_CBMID_RANGE_NUM;
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CBA_GetActiveMids: usCbmiRangNum ERROR!");
    }

    for ( ulCbmidRangeInx = 0; ulCbmidRangeInx < usCbmiRangNum; ulCbmidRangeInx++ )
    {
        /* 该消息ID的状态不为接收则略过 */
        if ( TAF_CBA_CBMI_RANGE_RCV_MODE_ACCEPT != (pstCbmiRangeList->astCbmiRangeInfo[ulCbmidRangeInx].enRcvMode) )
        {
            continue;
        }

        /* 将激活的CBS消息ID复制到输出参数中 */
        PS_MEM_CPY(&(pstActiveCbMids->astCbmiRangeInfo[pstActiveCbMids->usCbmirNum]),
                   &(pstCbmiRangeList->astCbmiRangeInfo[ulCbmidRangeInx]),
                   sizeof(pstActiveCbMids->astCbmiRangeInfo[pstActiveCbMids->usCbmirNum]));

        pstActiveCbMids->usCbmirNum++;
    }

    return;
}

/*lint -restore */


#endif /* ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS)) */




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
