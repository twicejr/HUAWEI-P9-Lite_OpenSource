

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "MnMsgInclude.h"
#include  "TafCbaCtx.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
  2 变量定义
*****************************************************************************/
/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_MNMSG_REPORT_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/

MN_MSG_EVENT_INFO_STRU           f_stMsgEventInfo;


extern VOS_UINT8                        g_ucMnOmConnectFlg;
extern VOS_UINT8                        g_ucMnOmPcRecurEnableFlg;

/*lint -save -e958 */

/*****************************************************************************
  3 函数实现
*****************************************************************************/

VOS_VOID MN_MSG_ReportRcvMsgEvent(
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_DELIVER_EVT_INFO_STRU  *pstDeliverEvt
)
{
    PS_MEM_SET(&f_stMsgEventInfo,0X00,sizeof(f_stMsgEventInfo));

    /*广播上报来一条短信*/
    PS_MEM_CPY(&f_stMsgEventInfo.u.stDeliverInfo,pstDeliverEvt,sizeof(f_stMsgEventInfo.u.stDeliverInfo));
    f_stMsgEventInfo.opId = opId;
    f_stMsgEventInfo.clientId = MN_CLIENT_ALL;
    MN_SendClientEvent(MN_CLIENT_ALL,MN_CALLBACK_MSG,MN_MSG_EVT_DELIVER,(VOS_VOID *)&f_stMsgEventInfo);
}



VOS_VOID MN_MSG_ReportSmChanged(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    VOS_BOOL                            bBroadCast,
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore
)
{
    MN_OPERATION_ID_T                   bcOpId;
    NAS_OM_SMS_STATICS_STRU             stSmsOmEventPara;
    VOS_UINT32                          ulTempRec;

    PS_MEM_SET(&f_stMsgEventInfo,0X00,sizeof(f_stMsgEventInfo));
    MN_MSG_GetSmStorageList(enMemStore,
                            &f_stMsgEventInfo.u.stStorageListInfo.ulTotalRec,
                            &f_stMsgEventInfo.u.stStorageListInfo.ulUsedRec,
                            f_stMsgEventInfo.u.stStorageListInfo.aulEachStatusRec);
    f_stMsgEventInfo.clientId = clientId;
    f_stMsgEventInfo.opId = opId;
    f_stMsgEventInfo.u.stStorageListInfo.enMemStroe = enMemStore;
    if (VOS_TRUE == bBroadCast)
    {
        MN_SendClientEvent(MN_CLIENT_ALL,
                           MN_CALLBACK_MSG,
                           MN_MSG_EVT_SM_STORAGE_LIST,
                           (VOS_VOID *)&f_stMsgEventInfo);
    }
    else
    {
        MN_SendClientEvent(clientId,
                           MN_CALLBACK_MSG,
                           MN_MSG_EVT_SM_STORAGE_LIST,
                          (VOS_VOID *)&f_stMsgEventInfo);
    }
    stSmsOmEventPara.ucMemType = NAS_SMS_SAVE_AREA_SM;
    stSmsOmEventPara.ucMemCap  = (VOS_UINT8)f_stMsgEventInfo.u.stStorageListInfo.ulTotalRec;
    stSmsOmEventPara.ucMemUsed = (VOS_UINT8)f_stMsgEventInfo.u.stStorageListInfo.ulUsedRec;
    NAS_EventReport(WUEPS_PID_SMS, NAS_OM_EVENT_SMS_STATICS,
                    &stSmsOmEventPara, sizeof(stSmsOmEventPara));

    if (f_stMsgEventInfo.u.stStorageListInfo.ulTotalRec == f_stMsgEventInfo.u.stStorageListInfo.ulUsedRec)
    {
        bcOpId = MN_MSG_GetBCopId();
        f_stMsgEventInfo.opId = bcOpId;
        f_stMsgEventInfo.u.stStorageStateInfo.enMemStroe = enMemStore;

        ulTempRec = f_stMsgEventInfo.u.stStorageListInfo.ulTotalRec;
        f_stMsgEventInfo.u.stStorageStateInfo.ulTotalRec = ulTempRec;
        ulTempRec = f_stMsgEventInfo.u.stStorageListInfo.ulUsedRec;
        f_stMsgEventInfo.u.stStorageStateInfo.ulUsedRec = ulTempRec;

        if (VOS_TRUE == bBroadCast)
        {
            MN_SendClientEvent(MN_CLIENT_ALL,
                               MN_CALLBACK_MSG,
                               MN_MSG_EVT_STORAGE_FULL,
                               (VOS_VOID *)&f_stMsgEventInfo);
        }
        else
        {
            MN_SendClientEvent(clientId,
                               MN_CALLBACK_MSG,
                               MN_MSG_EVT_STORAGE_FULL,
                               (VOS_VOID *)&f_stMsgEventInfo);
        }
    }


}


VOS_VOID MN_MSG_ReportMemExceed(
    MN_OPERATION_ID_T                   opId,
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore
)
{
    MN_INFO_LOG("MN_MSG_ReportMemExceed: step into function.");
    PS_MEM_SET(&f_stMsgEventInfo,0X00,sizeof(f_stMsgEventInfo));
    f_stMsgEventInfo.clientId = MN_CLIENT_ALL;
    f_stMsgEventInfo.opId = opId;
    f_stMsgEventInfo.u.stStorageStateInfo.enMemStroe = enMemStore;
    f_stMsgEventInfo.u.stStorageStateInfo.ulTotalRec = MN_MSG_GetSmCapacity(enMemStore);
    f_stMsgEventInfo.u.stStorageStateInfo.ulUsedRec = f_stMsgEventInfo.u.stStorageStateInfo.ulTotalRec;

    MN_SendClientEvent(MN_CLIENT_ALL,
                       MN_CALLBACK_MSG,
                       MN_MSG_EVT_STORAGE_EXCEED,
                       (VOS_VOID *)&f_stMsgEventInfo);
}


VOS_VOID MN_MSG_ReportDeleteEvent(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_DELETE_EVT_INFO_STRU   *pstDeleteEvt,
    VOS_UINT32                          ulEventType
)
{
    PS_MEM_SET(&f_stMsgEventInfo,0X00,sizeof(f_stMsgEventInfo));
    f_stMsgEventInfo.clientId = clientId;
    f_stMsgEventInfo.opId = opId;
    PS_MEM_CPY(&f_stMsgEventInfo.u.stDeleteInfo,pstDeleteEvt,sizeof(MN_MSG_DELETE_EVT_INFO_STRU));
    MN_SendClientEvent(clientId,MN_CALLBACK_MSG,ulEventType,(VOS_VOID *)&f_stMsgEventInfo);
}


VOS_VOID MN_MSG_ReportDeleteTestEvent(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_DELETE_TEST_EVT_INFO_STRU *pstDeleteTestEvt,
    VOS_UINT32                          ulEventType
)
{
    PS_MEM_SET(&f_stMsgEventInfo,0X00,sizeof(f_stMsgEventInfo));
    f_stMsgEventInfo.clientId = clientId;
    f_stMsgEventInfo.opId = opId;
    PS_MEM_CPY(&f_stMsgEventInfo.u.stDeleteTestInfo,pstDeleteTestEvt,sizeof(MN_MSG_DELETE_TEST_EVT_INFO_STRU));
    MN_SendClientEvent(clientId,MN_CALLBACK_MSG,ulEventType,(VOS_VOID *)&f_stMsgEventInfo);
}


VOS_VOID MN_MSG_ReportWriteEvent(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_WRITE_EVT_INFO_STRU    *pstWriteEvt,
    VOS_UINT32                          ulEventType
)
{
    PS_MEM_SET(&f_stMsgEventInfo,0X00,sizeof(f_stMsgEventInfo));
    f_stMsgEventInfo.clientId = clientId;
    f_stMsgEventInfo.opId = opId;
    PS_MEM_CPY(&f_stMsgEventInfo.u.stWriteInfo,pstWriteEvt,sizeof(MN_MSG_WRITE_EVT_INFO_STRU));
    MN_SendClientEvent(clientId,MN_CALLBACK_MSG,ulEventType,(VOS_VOID *)&f_stMsgEventInfo);
}


VOS_VOID MN_MSG_ReportReadEvent(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_READ_EVT_INFO_STRU     *pReadEvt,
    VOS_UINT32                          ulEventType
)
{
    PS_MEM_SET(&f_stMsgEventInfo,0X00,sizeof(f_stMsgEventInfo));
    f_stMsgEventInfo.clientId = clientId;
    f_stMsgEventInfo.opId = opId;
    PS_MEM_CPY(&f_stMsgEventInfo.u.stReadInfo,pReadEvt,sizeof(MN_MSG_READ_EVT_INFO_STRU));
    MN_SendClientEvent(clientId,MN_CALLBACK_MSG,ulEventType,(VOS_VOID *)&f_stMsgEventInfo);
}


VOS_VOID MN_MSG_ReportListEvent(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_LIST_EVT_INFO_STRU     *pListEvt,
    VOS_UINT32                          ulEventType
)
{
    PS_MEM_SET(&f_stMsgEventInfo,0X00,sizeof(f_stMsgEventInfo));
    f_stMsgEventInfo.clientId = clientId;
    f_stMsgEventInfo.opId = opId;
    PS_MEM_CPY(&f_stMsgEventInfo.u.stListInfo,pListEvt,sizeof(MN_MSG_LIST_EVT_INFO_STRU));
    MN_SendClientEvent(clientId,MN_CALLBACK_MSG,ulEventType,(VOS_VOID *)&f_stMsgEventInfo);
}


VOS_VOID MN_MSG_ReportModifyEvent(
    MN_CLIENT_ID_T                           clientId,
    MN_OPERATION_ID_T                        opId,
    const MN_MSG_MODIFY_STATUS_EVT_INFO_STRU *pModifyStatusEvt,
    VOS_UINT32                                ulEventType
)
{
    PS_MEM_SET(&f_stMsgEventInfo,0X00,sizeof(f_stMsgEventInfo));
    f_stMsgEventInfo.clientId = clientId;
    f_stMsgEventInfo.opId = opId;
    PS_MEM_CPY(&f_stMsgEventInfo.u.stModifyInfo,pModifyStatusEvt,sizeof(MN_MSG_MODIFY_STATUS_EVT_INFO_STRU));
    MN_SendClientEvent(clientId,MN_CALLBACK_MSG,ulEventType,(VOS_VOID *)&f_stMsgEventInfo);
}


VOS_VOID MN_MSG_ReportSrvParmEvent(
    MN_CLIENT_ID_T                       clientId,
    MN_OPERATION_ID_T                    opId,
    const MN_MSG_SRV_PARM_EVT_INFO_STRU *pstSrvParmEvt,
    VOS_UINT32                           ulEventType
)
{
    PS_MEM_SET(&f_stMsgEventInfo,0X00,sizeof(f_stMsgEventInfo));
    f_stMsgEventInfo.clientId = clientId;
    f_stMsgEventInfo.opId = opId;
    PS_MEM_CPY(&f_stMsgEventInfo.u.stSrvParmInfo,pstSrvParmEvt,sizeof(MN_MSG_SRV_PARM_EVT_INFO_STRU));
    MN_SendClientEvent(clientId,MN_CALLBACK_MSG,ulEventType,(VOS_VOID *)&f_stMsgEventInfo);
}


VOS_VOID MN_MSG_ReportSentEvent(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_MSG_SENDMSG_EVT_INFO_STRU        *pstSendMsgEvt,
    VOS_UINT32                          ulEventType
)
{
    PS_MEM_SET(&f_stMsgEventInfo,0X00,sizeof(f_stMsgEventInfo));
    f_stMsgEventInfo.clientId = clientId;
    f_stMsgEventInfo.opId = opId;
    PS_MEM_CPY(&f_stMsgEventInfo.u.stSendMsgInfo,pstSendMsgEvt,sizeof(MN_MSG_SENDMSG_EVT_INFO_STRU));
    MN_SendClientEvent(clientId,MN_CALLBACK_MSG,ulEventType,(VOS_VOID *)&f_stMsgEventInfo);
}


VOS_VOID MN_MSG_ReportSubmitRptEvent(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_MSG_SUBMIT_RPT_EVT_INFO_STRU     *pstSubmitRptEvt,
    VOS_UINT32                          ulEventType
)
{
    PS_MEM_SET(&f_stMsgEventInfo,0X00,sizeof(f_stMsgEventInfo));
    f_stMsgEventInfo.clientId = clientId;
    f_stMsgEventInfo.opId = opId;
    PS_MEM_CPY(&f_stMsgEventInfo.u.stSubmitRptInfo,
               pstSubmitRptEvt,
               sizeof(f_stMsgEventInfo.u.stSubmitRptInfo));
    MN_SendClientEvent(f_stMsgEventInfo.clientId,MN_CALLBACK_MSG,ulEventType,(VOS_VOID *)&f_stMsgEventInfo);
}

VOS_VOID MN_MSG_ReportRcvPathEvent(
    MN_CLIENT_ID_T                         clientId,
    MN_OPERATION_ID_T                      opId,
    VOS_BOOL                               bBroadCast,
    const MN_MSG_RCVMSG_PATH_EVT_INFO_STRU *pRcvPathEvt,
    VOS_UINT32                             ulEventType
)
{
    PS_MEM_SET(&f_stMsgEventInfo,0X00,sizeof(f_stMsgEventInfo));
    f_stMsgEventInfo.clientId = clientId;
    f_stMsgEventInfo.opId = opId;
    PS_MEM_CPY(&f_stMsgEventInfo.u.stRcvMsgPathInfo,pRcvPathEvt,sizeof(MN_MSG_RCVMSG_PATH_EVT_INFO_STRU));
    if (VOS_TRUE == bBroadCast)
    {
        MN_SendClientEvent(MN_CLIENT_ALL,MN_CALLBACK_MSG,ulEventType,(VOS_VOID *)&f_stMsgEventInfo);
    }
    else
    {
        MN_SendClientEvent(clientId,MN_CALLBACK_MSG,ulEventType,(VOS_VOID *)&f_stMsgEventInfo);
    }
}


VOS_VOID MN_MSG_ReportMemStatustEvent(
    MN_CLIENT_ID_T                       clientId,
    MN_OPERATION_ID_T                    opId,
    VOS_BOOL                             bBroadCast,
    const MN_MSG_MEMSTATUS_EVT_INFO_STRU *pstMemStatusEvt,
    VOS_UINT32                           ulEventType
)
{
    PS_MEM_SET(&f_stMsgEventInfo,0X00,sizeof(f_stMsgEventInfo));
    f_stMsgEventInfo.opId = opId;
    f_stMsgEventInfo.clientId = clientId;
    PS_MEM_CPY(&f_stMsgEventInfo.u.stMemStatusInfo,pstMemStatusEvt,sizeof(MN_MSG_MEMSTATUS_EVT_INFO_STRU));
    if (VOS_TRUE == bBroadCast)
    {
        MN_SendClientEvent(MN_CLIENT_ALL,MN_CALLBACK_MSG,ulEventType,(VOS_VOID *)&f_stMsgEventInfo);
    }
    else
    {
        MN_SendClientEvent(clientId,MN_CALLBACK_MSG,ulEventType,(VOS_VOID *)&f_stMsgEventInfo);
    }
}


VOS_VOID MN_MSG_ReportSrvParmChanged(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore
)
{
    PS_MEM_SET(&f_stMsgEventInfo,0X00,sizeof(f_stMsgEventInfo));

    MN_MSG_GetSmspStorageList(enMemStore,
                               &f_stMsgEventInfo.u.stSrvParmChangeInfo.ulTotalRec,
                               &f_stMsgEventInfo.u.stSrvParmChangeInfo.ulUsedRec,
                               f_stMsgEventInfo.u.stSrvParmChangeInfo.astSrvParm);
    f_stMsgEventInfo.opId = opId;
    f_stMsgEventInfo.clientId = clientId;
    MN_SendClientEvent(MN_CLIENT_ALL,MN_CALLBACK_MSG,MN_MSG_EVT_SRV_PARM_CHANGED,(VOS_VOID *)&f_stMsgEventInfo);
}


VOS_VOID MN_MSG_ReportDeliverErr(TAF_MSG_ERROR_ENUM_UINT32 enErrorCode)
{
    MN_OPERATION_ID_T                   bcOpId;

    PS_MEM_SET(&f_stMsgEventInfo,0X00,sizeof(f_stMsgEventInfo));
    f_stMsgEventInfo.u.stDeliverErrInfo.enErrorCode = enErrorCode;
    bcOpId = MN_MSG_GetBCopId();
    f_stMsgEventInfo.clientId = MN_CLIENT_ALL;
    f_stMsgEventInfo.opId = bcOpId;
    MN_SendClientEvent(MN_CLIENT_ALL,MN_CALLBACK_MSG,MN_MSG_EVT_DELIVER_ERR,(VOS_VOID *)&f_stMsgEventInfo);
}


VOS_VOID MN_MSG_ReportLinkCtrl(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    VOS_UINT32                          ulEventType,
    VOS_UINT32                          ulErrorCode,
    MN_MSG_LINK_CTRL_U8                 enLinkCtrl
)
{

    PS_MEM_SET(&f_stMsgEventInfo,0X00,sizeof(f_stMsgEventInfo));
    f_stMsgEventInfo.clientId = clientId;
    f_stMsgEventInfo.opId = opId;
    f_stMsgEventInfo.u.stLinkCtrlInfo.ulErrorCode = ulErrorCode;
    f_stMsgEventInfo.u.stLinkCtrlInfo.enLinkCtrl = enLinkCtrl;
    MN_SendClientEvent(clientId,MN_CALLBACK_MSG,ulEventType,(VOS_VOID *)&f_stMsgEventInfo);
    return;
}


VOS_VOID MN_MSG_ReportResult(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    VOS_UINT32                          ulEventType,
    VOS_UINT32                          ulErrorCode
)
{
    PS_MEM_SET(&f_stMsgEventInfo,0X00,sizeof(f_stMsgEventInfo));
    f_stMsgEventInfo.clientId                     = clientId;
    f_stMsgEventInfo.opId                         = opId;
    f_stMsgEventInfo.u.stLinkCtrlInfo.ulErrorCode = ulErrorCode;
    MN_SendClientEvent(clientId, MN_CALLBACK_MSG, ulEventType, (VOS_VOID *)&f_stMsgEventInfo);
    return;
}



VOS_VOID MN_MSG_SmspInitFinish(
    MN_CLIENT_ID_T                      clientId
)
{
    MN_MSG_USIM_POWER_STATE_ENUM_U8     enPowerState;

    MN_MSG_GetUsimPowerState(&enPowerState);

    if(enPowerState < MN_MSG_USIM_POWER_WAIT_EFSMSP)
    {
        return;
    }
    PS_MEM_SET(&f_stMsgEventInfo,0,sizeof(MN_MSG_EVENT_INFO_STRU));

    MN_MSG_GetSmspStorageList(MN_MSG_MEM_STORE_SIM,
                              &f_stMsgEventInfo.u.stInitSmspResultInfo.ulTotalSrvParm,
                              &f_stMsgEventInfo.u.stInitSmspResultInfo.ulUsedSrvParm,
                              f_stMsgEventInfo.u.stInitSmspResultInfo.astSrvParm);

    MN_MSG_GetCurRcvMsgPath(&f_stMsgEventInfo.u.stInitSmspResultInfo.stRcvMsgPath);

    f_stMsgEventInfo.u.stInitSmspResultInfo.enClass0Tailor = MN_MSG_GetClass0Tailor();;

    MN_SendClientEvent(clientId,
                       MN_CALLBACK_MSG,
                       MN_MSG_EVT_INIT_SMSP_RESULT,
                       (VOS_VOID *)&f_stMsgEventInfo);

}


VOS_VOID MN_MSG_SmInitFinish(
    MN_CLIENT_ID_T                      clientId
)
{
    MN_MSG_USIM_POWER_STATE_ENUM_U8     enPowerState;

#ifndef __PS_WIN32_RECUR__
    if ( (VOS_TRUE == g_ucMnOmConnectFlg)
      && (VOS_TRUE == g_ucMnOmPcRecurEnableFlg) )
    {
        NAS_MSG_SndOutsideContextData_Part1();
        NAS_MSG_SndOutsideContextData_Part2();
        NAS_MSG_SndOutsideContextData_Part3();
    }
#endif

    MN_MSG_GetUsimPowerState(&enPowerState);

    if(MN_MSG_USIM_POWER_ON != enPowerState)
    {
        return;
    }

    /* 清除短信文件要求更新的标志，保证重复接收到REFRESH消息时不会有文件不更新 */
    MN_MSG_SetSmsFileRefreshFlag(USIMM_USIM_EFSMSS_ID, VOS_TRUE);
    MN_MSG_SetSmsFileRefreshFlag(USIMM_USIM_EFSMS_ID, VOS_TRUE);
    MN_MSG_SetSmsFileRefreshFlag(USIMM_USIM_EFSMSP_ID, VOS_TRUE);
    MN_MSG_SetSmsFileRefreshFlag(USIMM_USIM_EFSMSR_ID, VOS_TRUE);

    PS_MEM_SET(&f_stMsgEventInfo,0,sizeof(MN_MSG_EVENT_INFO_STRU));

    MN_MSG_GetSmStorageList(MN_MSG_MEM_STORE_SIM,
                            &f_stMsgEventInfo.u.stInitResultInfo.ulTotalSmRec,
                            &f_stMsgEventInfo.u.stInitResultInfo.ulUsedSmRec,
                            f_stMsgEventInfo.u.stInitResultInfo.aulEachStatusRec);


    MN_MSG_GetSmsrStorageList(MN_MSG_MEM_STORE_SIM,
                              &f_stMsgEventInfo.u.stInitResultInfo.ulTotalSmsrRec,
                              &f_stMsgEventInfo.u.stInitResultInfo.ulUsedSmsrRec);

    MN_SendClientEvent(clientId,
                       MN_CALLBACK_MSG,
                       MN_MSG_EVT_INIT_RESULT,
                       (VOS_VOID *)&f_stMsgEventInfo);

    MN_MSG_StartMemNotification();
}


VOS_VOID MN_MSG_FinishMoProc(
    VOS_VOID
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulStoreIndex;
    MN_MSG_STORE_MSG_STRU               stStoreMsg;
    MN_MSG_SUBMIT_RPT_EVT_INFO_STRU     stSubmitRptEvt;
    MN_MSG_MO_ENTITY_STRU               stMoEntity;
    VOS_UINT32                          ulTotal;

    PS_MEM_SET(&stSubmitRptEvt,0X00,sizeof(stSubmitRptEvt));

    PS_MEM_SET(&stMoEntity,0x00,sizeof(stMoEntity));

    ulTotal = MN_MSG_GetMoBufferCap();
    for (i = 0; i < ulTotal; i++)
    {
        ulStoreIndex = MN_MSG_GetStoreMsg(&stStoreMsg);
        if (MN_MSG_NO_AVAILABLE_SMS_REC == ulStoreIndex)
        {
            continue;
        }
        else
        {
            if ((MN_MSG_MO_TYPE_MO == stStoreMsg.stMoInfo.enSmsMoType)
             || (MN_MSG_MO_TYPE_BUFFER_STK == stStoreMsg.stMoInfo.enSmsMoType)
             || ((MN_MSG_MO_TYPE_SMMA == stStoreMsg.stMoInfo.enSmsMoType)
              && (VOS_TRUE == stStoreMsg.stMoInfo.bReportFlag)))
            {
                MN_INFO_LOG("MN_MSG_FinishMoProc: Abnormal abort.");
                stSubmitRptEvt.ucMr                 = stStoreMsg.stMoInfo.ucMr;/*TP-MR*/
                stSubmitRptEvt.enErrorCode          = TAF_MSG_ERROR_NO_SERVICE;
                stSubmitRptEvt.enSaveArea           = stStoreMsg.stMoInfo.enSaveArea;
                stSubmitRptEvt.ulSaveIndex          = stStoreMsg.stMoInfo.ulSaveIndex;
                MN_MSG_ReportSubmitRptEvent(stStoreMsg.stMoInfo.clientId,
                                            stStoreMsg.stMoInfo.opId,
                                            (MN_MSG_SUBMIT_RPT_EVT_INFO_STRU *)&stSubmitRptEvt,
                                            MN_MSG_EVT_SUBMIT_RPT);
            }
            MN_MSG_FreeStoreMsg(ulStoreIndex);
        }

    }

    PS_MEM_SET(&stMoEntity, 0, sizeof(stMoEntity));

    MN_MSG_GetMoEntity(&stMoEntity);
    if ((stMoEntity.enSmaMoState > MN_MSG_MO_STATE_NULL)
     && (stMoEntity.enSmaMoState < MN_MSG_MO_STATE_MAX))
    {
        if (MN_MSG_MO_STATE_WAIT_FDN_CHECK_RSP == stMoEntity.enSmaMoState)
        {
            MN_MSG_StopTimer(MN_MGS_ID_WAIT_FDN_CHECK);
        }

        if (MN_MSG_MO_STATE_WAIT_SMS_CTRL_RSP == stMoEntity.enSmaMoState)
        {
            MN_MSG_StopTimer(MN_MGS_ID_WAIT_MO_SMS_CTRL_CHECK);
        }

        MN_INFO_LOG("MN_MSG_FinishMoProc: fail to mo.");
        stSubmitRptEvt.ucMr = stMoEntity.ucMr;/*TP-MR*/
        stSubmitRptEvt.enErrorCode          = TAF_MSG_ERROR_NO_SERVICE;
        stSubmitRptEvt.enSaveArea           = stMoEntity.enSaveArea;
        stSubmitRptEvt.ulSaveIndex          = stMoEntity.ulSaveIndex;
        MN_MSG_ReportSubmitRptEvent(stMoEntity.clientId,
                                    stMoEntity.opId,
                                    (MN_MSG_SUBMIT_RPT_EVT_INFO_STRU *)&stSubmitRptEvt,
                                    MN_MSG_EVT_SUBMIT_RPT);
        MN_MSG_DestroyMoInfo();
    }

    return;

}

/*lint -restore */


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

