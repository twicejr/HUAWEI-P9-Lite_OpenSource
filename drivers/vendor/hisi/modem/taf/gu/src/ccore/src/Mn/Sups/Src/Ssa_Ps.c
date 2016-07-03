


#include "Ssa_Define.h"
#include "Taf_Tafm_Remote.h"
#include "Taf_Common.h"
#include "Taf_Ssa_DecodeDef.h"
#include "Taf_Ssa_EncodeDef.h"
#include "MnComm.h"
#include "SsDef.h"
#include "SsInclude.h"
#include "TafClientApi.h"
#include "TafSdcLib.h"
#include "TafStdlib.h"

#include "Ssa_Define.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_SSA_PS_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/

/*lint -save -e958 */


VOS_VOID SSA_DealMsgFromSS(ST_SSP_MSG  *pMsg)
{
    /*输入参数检查,为空的话返回*/
    if (VOS_NULL_PTR == pMsg)
    {
        SSA_LOG(ERROR_PRINT, "SSA_DealMsgFromSS:ERROR: pMsg is NULL");
        return;

    }

    /*处理来自SS的三种消息：ST_BEGIN_IND,ST_SSP_MSGS_FACILITY_IND,ST_END_IND*/
    switch( pMsg->SspmsgCore.ucChoice )
    {
        case D_SMC_BEGIN_IND:
             SSA_RegisterIndProc(pMsg);
             break;

        case D_SMC_FACILITY_IND:
             SSA_FacilityIndProc(pMsg);
             break;

        case D_SMC_END_IND:
             SSA_RelCompleteIndProc(pMsg);
             break;

        case SSA_SS_CS_CONN_IND:
             TAF_SSA_RcvSsCsConnInd(pMsg);

        default:
             SSA_LOG(WARNING_PRINT, "SSA_DealMsgFromSS:WARNING: Receive Msg is Unknow");
             return;
    }

    return;
}


VOS_VOID SSA_RegisterIndProc(ST_SSP_MSG  *pMsg)
{
    /* VOS_UINT8                                 ucComponetTag; */
    VOS_UINT32                                  ulRslt = SSA_SUCCESS;
    ST_BEGIN_IND                                *pBeginInd;
    TAF_SS_CALL_INDEPENDENT_EVENT_STRU          *pstSsEvent;
    VOS_UINT8                                   ucRejectCode;

    pstSsEvent = (TAF_SS_CALL_INDEPENDENT_EVENT_STRU *)PS_MEM_ALLOC(WUEPS_PID_SS, sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
    if (VOS_NULL_PTR == pstSsEvent)
    {
        SSA_LOG( ERROR_PRINT, "SSA_RegisterIndProc:ERROR: Alloc Mem Fail");
        return;
    }


    /*对事件上报的内容赋初值*/
    PS_MEM_SET(pstSsEvent, 0 , sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));

    /*获取消息内容*/
    pBeginInd = &(pMsg->SspmsgCore.u.BeginInd);

    /*获取ti和消息类型,Ti值不用检查,在SS模块已经有了相应的检查*/
    gucCurrentTi = pMsg->ucCr;
    if (gucCurrentTi <= TAF_MIDDLE_SSA_TI)
    {
        SSA_LOG(WARNING_PRINT, "SSA_FacilityIndProc:WARNING: Ti Value beyond range");
        PS_MEM_FREE(WUEPS_PID_SS, pstSsEvent);
        return;
    }

    gastSsaStatetable[gucCurrentTi].ucMsgType = TAF_SS_MSG_TYPE_REGISTER;

    /*componet部分解码*/
    ulRslt = SSA_DecodeComponent(pstSsEvent, pBeginInd->Facility.Facility);

    if (SSA_SUCCESS == ulRslt)
    {
        switch (pstSsEvent->SsEvent)
        {
            /*TAF_SS_FORWARDCHECKSS_INDICATION事件上报给APP/AT后直接释放*/
            #if 0
            case TAF_SS_EVT_FORWARDCHECKSS_INDICATION:
                TAF_SsEventReport(&StEvent);
                SSA_ReleaseComplete(gucCurrentTi + 120, VOS_NULL);
                break;
            #endif
            /*TAF_SS_USS_NOTIFY事件上报给APP/AT后回复网络侧*/
            case TAF_SS_EVT_USS_NOTIFY_IND:
                if (SSA_USED == SSA_TiIdle())
                {
                    gastSsaStatetable[gucCurrentTi].ucState = SSA_USED;

                    /* 此处是异常分支，把ucState置为SSA_USED，后面会紧跟着置为SSA_IDLE，
                        所以不需要再置一下CS域的SS业务是否存在的标志 */

                    SSA_ReturnError(TAF_ERR_SS_USSD_BUSY,
                                    gucCurrentTi,
                                    TAF_SS_MSG_TYPE_RLCOMPLETE,
                                    VOS_NULL);

                    gastSsaStatetable[gucCurrentTi].ucState = SSA_IDLE;

                    PS_MEM_FREE(WUEPS_PID_SS, pstSsEvent);
                    return;
                }
                TAF_SsEventReport(pstSsEvent);

                gastSsaStatetable[gucCurrentTi].ucState = SSA_USED;

                /* 没有调用SSA_TiAlloc函数，需要单独置一下CS域的SS业务是否存在的标志 */
                TAF_SDC_SetCsSsSrvExistFlg(VOS_TRUE);

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
                /* 给MTC模块上报当前CS域业务状态 */
                TAF_SendMtcCsSrvInfoInd();
#endif

                SSA_UssNotifyRsp(gucCurrentTi);

                break;
            case TAF_SS_EVT_USS_REQ_IND:
                /*启动计时器,成功,事件上报给APP/AT,若失败则通知网络侧,返回*/

                if (VOS_TRUE !=  TAF_SSA_StartTimer(TI_TAF_SSA_WAIT_APP_RSP_TIMER,
                                                    NAS_SSA_TIMER_LENGTH_WAIT_APP_RSP,
                                                    gucCurrentTi))

                {
                    gastSsaStatetable[gucCurrentTi].ucState = SSA_USED;

                    /* 此处是异常分支，把ucState置为SSA_USED，后面会紧跟着置为SSA_IDLE，
                        所以不需要再置一下CS域的SS业务是否存在的标志 */

                    SSA_ReturnError(TAF_ERR_SS_SYSTEM_FAILURE,
                                    gucCurrentTi,
                                    TAF_SS_MSG_TYPE_FACILITY,
                                    VOS_NULL);

                    gastSsaStatetable[gucCurrentTi].ucState = SSA_IDLE;

                    SSA_LOG(ERROR_PRINT, "SSA_RegisterIndProc:ERROR: VOS_StartRelTimer runs failed");
                    PS_MEM_FREE(WUEPS_PID_SS, pstSsEvent);
                    return;
                }
                TAF_SsEventReport(pstSsEvent);
                gastSsaStatetable[gucCurrentTi].ucUssdFlag  = TAF_SSA_USSD_MT_CONN_STATE;
                gastSsaStatetable[gucCurrentTi].ucState     = SSA_USED;

                /* 没有调用SSA_TiAlloc函数，需要单独置一下CS域的SS业务是否存在的标志 */
                TAF_SDC_SetCsSsSrvExistFlg(VOS_TRUE);

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
                /* 给MTC模块上报当前CS域业务状态 */
                TAF_SendMtcCsSrvInfoInd();
#endif

                break;

           default:
                SSA_LOG(WARNING_PRINT, "SSA_RegisterIndProc:WARNING: wrong operation type");
                PS_MEM_FREE(WUEPS_PID_SS, pstSsEvent);
                return;
        }
    }
    else
    {
        /*根据返回的错误信息，回复网络侧,ForwardCheckSS-Indication返回消息类型是Release Complete*/
        #if 0
        if (TAF_SS_EVT_FORWARDCHECKSS_INDICATION == StEvent.SsEvent)
        {
            SSA_ReturnReject((VOS_UINT8)ulRslt, gucCurrentTi + 120, TAF_SS_MSG_TYPE_RLCOMPLETE, NULL);
        }
        else
        #endif
        {
            switch(ulRslt)
            {
                case TAF_ERR_SS_USSD_BUSY:

                    gastSsaStatetable[gucCurrentTi].ucState = SSA_USED;

                    /* 此处是把ucState置为SSA_USED，后面会紧跟着置为SSA_IDLE，
                        所以不需要再置一下CS域的SS业务是否存在的标志 */

                    SSA_ReturnError((VOS_UINT16)ulRslt, gucCurrentTi, TAF_SS_MSG_TYPE_RLCOMPLETE, VOS_NULL);

                    gastSsaStatetable[gucCurrentTi].ucState = SSA_IDLE;

                    SSA_LOG(WARNING_PRINT, "SSA_RegisterIndProc:WARNING: send error ussd busy");
                    break;
                case TAF_ERR_SS_UNKNOWN_ALPHABET:
                case TAF_ERR_SS_UNEXPECTED_DATA_VALUE:

                    gastSsaStatetable[gucCurrentTi].ucState = SSA_USED;

                    /* 此处把ucState置为SSA_USED，后面会紧跟着置为SSA_IDLE，
                        所以不需要再置一下CS域的SS业务是否存在的标志 */

                    SSA_ReturnError((VOS_UINT16)ulRslt, gucCurrentTi, TAF_SS_MSG_TYPE_FACILITY, VOS_NULL);

                    gastSsaStatetable[gucCurrentTi].ucState = SSA_IDLE;

                    SSA_LOG(WARNING_PRINT, "SSA_RegisterIndProc:WARNING: send error");
                    break;

                case TAF_SS_REJ_INVALID_MANDATORY_IE:

                    gastSsaStatetable[gucCurrentTi].ucState = SSA_USED;

                    /* 此处把ucState置为SSA_USED，后面会紧跟着置为SSA_IDLE，
                        所以不需要再置一下CS域的SS业务是否存在的标志 */

                    SSA_ReturnError(0, gucCurrentTi, TAF_SS_MSG_TYPE_RLCOMPLETE, SS_CAUSE_INVALID_MANDATORY_IE);

                    gastSsaStatetable[gucCurrentTi].ucState = SSA_IDLE;

                    SSA_LOG(WARNING_PRINT, "SSA_RegisterIndProc:WARNING: No Invoke Id");
                    break;

                default:
                    ucRejectCode = 0x20|(ulRslt & 0x0f);
                    SSA_ReturnReject(ucRejectCode, gucCurrentTi, TAF_SS_MSG_TYPE_FACILITY, VOS_NULL);
                    SSA_LOG(WARNING_PRINT, "SSA_RegisterIndProc:WARNING: send reject");
                    break;
            }
        }
    }

    PS_MEM_FREE(WUEPS_PID_SS, pstSsEvent);
    return;
}


VOS_VOID SSA_FacilityIndProc(ST_SSP_MSG  *pMsg)
{
    /* VOS_UINT8                                    ucComponetTag; */
    VOS_UINT32                                   ulRslt = SSA_SUCCESS;
    ST_SSP_MSGS_FACILITY_IND                     *pFacilityInd;
    TAF_SS_GETPWD_RSP_STRU                       stPara;
    TAF_SS_CALL_INDEPENDENT_EVENT_STRU           *pstSsEvent;
    VOS_UINT8                                    ucRejectCode;

    pstSsEvent = (TAF_SS_CALL_INDEPENDENT_EVENT_STRU *)PS_MEM_ALLOC(WUEPS_PID_SS, sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
    if (VOS_NULL_PTR == pstSsEvent)
    {
        SSA_LOG( ERROR_PRINT, "SSA_FacilityIndProc:ERROR: Alloc Mem Fail");
        return;
    }


    /*对事件上报的内容赋初值*/
    PS_MEM_SET(pstSsEvent, 0 , sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));

    /*获取消息内容*/
    pFacilityInd = &(pMsg->SspmsgCore.u.FacilityInd);

    /*获取ti和消息类型*/
    gucCurrentTi = pMsg->ucCr;
    if ((gucCurrentTi > TAF_MAX_SSA_TI) || (gucCurrentTi == TAF_MIDDLE_SSA_TI))
    {
        SSA_LOG(WARNING_PRINT, "SSA_FacilityIndProc:WARNING: Ti Value beyond range");
        PS_MEM_FREE(WUEPS_PID_SS, pstSsEvent);
        return;
    }

    gastSsaStatetable[gucCurrentTi].ucMsgType = TAF_SS_MSG_TYPE_FACILITY;

    /*检查TI的值是否正确,Ti值不正确的话,抛弃,打印warning信息*/
    ulRslt = SSA_GetIdByTi(&(pstSsEvent->ClientId), &(pstSsEvent->OpId), gucCurrentTi);
    if (SSA_FAILURE == ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_FacilityIndProc:WARNING: Invalid Ti Value");
        PS_MEM_FREE(WUEPS_PID_SS, pstSsEvent);
        return;
    }

    /*componet部分解码*/
    ulRslt = SSA_DecodeComponent(pstSsEvent, pFacilityInd->Facility.Facility);

    if (SSA_SUCCESS == ulRslt)
    {
        /*如果是需要获取密码,看当前状态表中是否已经存有相关操作的密码,已有的话,
        将相关的密码发送给网络侧*/
        if (TAF_SS_EVT_GET_PASSWORD_IND == pstSsEvent->SsEvent)
        {
            if (SSA_PASSWORD_VALID == gastSsaStatetable[gucCurrentTi].ucPwdFlag)
            {
                switch(pstSsEvent->GuidanceInfo)
                {
                    case TAF_SS_ENTER_PASSWORD:
                        PS_MEM_CPY(stPara.aucPwdStr, gastSsaStatetable[gucCurrentTi].aucOldPwdStr, 4);
                        break;
                    case TAF_SS_ENTER_NEW_PASSWORD:
                        PS_MEM_CPY(stPara.aucPwdStr, gastSsaStatetable[gucCurrentTi].aucNewPwdStr, 4);
                        break;
                    case TAF_SS_ENTER_NEW_PASSWORD_AGAIN:
                        PS_MEM_CPY(stPara.aucPwdStr, gastSsaStatetable[gucCurrentTi].aucNewPwdStrCnf, 4);
                        break;
                    default:
                        SSA_LOG(WARNING_PRINT, "SSA_FacilityIndProc: PASSWORD Type Error ");
                        PS_MEM_FREE(WUEPS_PID_SS, pstSsEvent);
                        return;
                }
                SSA_GetPasswordRsp(&stPara, gucCurrentTi);
                PS_MEM_FREE(WUEPS_PID_SS, pstSsEvent);
                return;
            }
            else
            {
                SSA_LOG( ERROR_PRINT, "SSA_FacilityIndProc: NO network required password.");
                PS_MEM_FREE(WUEPS_PID_SS, pstSsEvent);
                return;
            }
        }

        if ((TAF_SS_EVT_USS_REQ_IND != pstSsEvent->SsEvent)
         && (TAF_SS_EVT_USS_NOTIFY_IND != pstSsEvent->SsEvent)
         && (TAF_SS_EVT_PROCESS_USS_REQ_CNF != pstSsEvent->SsEvent))
        {
            SSA_ReturnError(0, gucCurrentTi, TAF_SS_MSG_TYPE_RLCOMPLETE, SS_CAUSE_MSG_NOT_COMPATIBLE_STATUS);
            SSA_LOG( ERROR_PRINT, "SSA_FacilityIndProc rcv wrong message");
            PS_MEM_FREE(WUEPS_PID_SS, pstSsEvent);
            return;
        }

        if (TAF_SS_EVT_USS_NOTIFY_IND == pstSsEvent->SsEvent)
        {
            SSA_UssNotifyRsp(gucCurrentTi);
        }

        /*关闭计时器*/
        TAF_SSA_StopTimer(TI_TAF_SSA_WAIT_NETWORK_RSP_TIMER, gucCurrentTi);

        if (TAF_SS_EVT_USS_REQ_IND == pstSsEvent->SsEvent)
        {
            if (VOS_TRUE !=  TAF_SSA_StartTimer(TI_TAF_SSA_WAIT_APP_RSP_TIMER,
                                                NAS_SSA_TIMER_LENGTH_WAIT_APP_RSP,
                                                gucCurrentTi))
            {
                SSA_LOG(ERROR_PRINT, "SSA_FacilityIndProc:ERROR: VOS_StartRelTimer runs failed");
            }

            gastSsaStatetable[gucCurrentTi].ucUssdFlag  = TAF_SSA_USSD_MT_CONN_STATE;
        }


        /*事件上报给APP/AT*/
        TAF_SsEventReport(pstSsEvent);
    }
    else
    {
        switch(ulRslt)
        {
            case TAF_ERR_SS_UNKNOWN_ALPHABET:
            case TAF_ERR_SS_UNEXPECTED_DATA_VALUE:
                SSA_ReturnError((VOS_UINT8)ulRslt, gucCurrentTi, TAF_SS_MSG_TYPE_FACILITY, VOS_NULL);
                SSA_LOG(WARNING_PRINT, "SSA_FacilityIndProc:WARNING: component error");
                break;
            default:
                if (((ulRslt >> 4) | 0x10) == 0x10)
                {
                    ucRejectCode = (VOS_UINT8)ulRslt;
                }
                else
                {
                    switch (gastSsaStatetable[gucCurrentTi].uComponenttype)
                    {
                        case TAF_SS_COMPONENT_TYPE_INVOKE:
                            ucRejectCode = 0x20|(ulRslt & 0x0f);
                            break;
                        case TAF_SS_COMPONENT_TYPE_RTRNRSLT:
                            ucRejectCode = 0x30|(ulRslt & 0x0f);
                            break;
                        case TAF_SS_COMPONENT_TYPE_RTRNERR:
                            ucRejectCode = 0x40|(ulRslt & 0x0f);
                            break;
                        default:
                            SSA_LOG(WARNING_PRINT, "SSA_FacilityIndProc:WARNING: Component Type Error");
                            PS_MEM_FREE(WUEPS_PID_SS, pstSsEvent);
                            return;
                    }
                }
                SSA_ReturnReject(ucRejectCode, gucCurrentTi, TAF_SS_MSG_TYPE_FACILITY, VOS_NULL);
                SSA_LOG(WARNING_PRINT, "SSA_FacilityIndProc:WARNING: component reject");
                break;
        }
    }

    PS_MEM_FREE(WUEPS_PID_SS, pstSsEvent);
    return;
}


VOS_VOID SSA_RelCompleteIndCauseProc(
    ST_END_IND                                   *pEndInd,
    TAF_SS_CALL_INDEPENDENT_EVENT_STRU           *pstSsEvent
)
{
    if (SSA_FIELD_EXIST == pEndInd->OP_Cause)
    {
        /*作修改,数据结构已经有所变化*/
        /*pstEvent->stCause.ulCnt = pstEndInd->Cause.ulCnt;
        memcpy(pstEvent->stCause.Cause, pstEndInd->Cause.Cause, pstEndInd->Cause.ulCnt);
        */
        /*Cause 值域的第一个字节是编码标准，第二个字节才是Cause的值*/
        pstSsEvent->Cause = *(pEndInd->Cause.Cause + 1) & 0x7f;
        pstSsEvent->OP_Cause = SSA_FIELD_EXIST;
    }
    else
    {
        pstSsEvent->OP_Cause = SSA_FIELD_NOT_EXIST;
    }
}


VOS_UINT32 SSA_RelCompleteIndFacilityProc(
    ST_END_IND                                   *pEndInd,
    TAF_SS_CALL_INDEPENDENT_EVENT_STRU           *pstSsEvent
)
{
    VOS_UINT32            ulRslt;

    VOS_UINT16                      usSysAppConfigType;

    usSysAppConfigType = TAF_SDC_GetAppCfgSupportType();

    ulRslt = SSA_SUCCESS;

    if (SSA_FIELD_EXIST == pEndInd->OP_Facility)
    {
        ulRslt = SSA_DecodeComponent(pstSsEvent, pEndInd->Facility.Facility);
    }
    else
    {
        pstSsEvent->SsEvent = SSA_GetRepEvtFromOpCode(gastSsaStatetable[gucCurrentTi].ucOperationCode);

        if ((TAF_SS_EVT_PROCESS_USS_REQ_CNF == pstSsEvent->SsEvent)
         || (TAF_SS_EVT_USS_REQ_IND == pstSsEvent->SsEvent)
         || ((TAF_SS_EVT_USS_NOTIFY_IND == pstSsEvent->SsEvent)
          && (SYSTEM_APP_ANDROID == usSysAppConfigType)))
        {
            pstSsEvent->SsEvent = TAF_SS_EVT_USS_RELEASE_COMPLETE_IND;
        }
        else if (TAF_SS_EVT_INTERROGATESS_CNF == pstSsEvent->SsEvent)
        {
            pstSsEvent->OP_Error = SSA_FIELD_EXIST;
            pstSsEvent->ErrorCode = TAF_ERR_ERROR;
        }
        else
        {
            ;
        }
        pstSsEvent->OpId = gastSsaStatetable[gucCurrentTi].OpId;
        pstSsEvent->ClientId = gastSsaStatetable[gucCurrentTi].ClientId;
    }

    return ulRslt;
}




VOS_VOID SSA_RelCompleteIndRtrnErrProc(
    TAF_SS_CALL_INDEPENDENT_EVENT_STRU           *pstSsEvent
)
{
    /*根据返回的错误信息，来决定上报信息*/
    pstSsEvent->SsEvent = SSA_GetRepEvtFromOpCode(gastSsaStatetable[gucCurrentTi].ucOperationCode);
    if ((TAF_SS_EVT_PROCESS_USS_REQ_CNF == pstSsEvent->SsEvent)
        ||(TAF_SS_EVT_USS_REQ_IND == pstSsEvent->SsEvent)
        ||(TAF_SS_EVT_USS_NOTIFY_IND == pstSsEvent->SsEvent)
        ||(TAF_SS_EVT_USS_RELEASE_COMPLETE_IND == pstSsEvent->SsEvent))
    {
        pstSsEvent->SsEvent = TAF_SS_EVT_PROCESS_USS_REQ_CNF;
    }
    else
    {
        pstSsEvent->SsEvent = TAF_SS_EVT_ERROR;
    }

    TAF_SsEventReport(pstSsEvent);
    SSA_TiFree(gucCurrentTi);


}


VOS_BOOL SSA_JudgeUssdNotCompatiblity(
    VOS_UINT32                                   ulOpRslt,
    TAF_SS_CALL_INDEPENDENT_EVENT_STRU           *pstSsEvent
)
{
    if (((TAF_SS_REJ_UNRECOGNIZED_OPERATION == ulOpRslt)
           &&(VOS_NULL_PTR != gastSsaStatetable[gucCurrentTi].pstUssdBuf)
           &&(TAF_SS_PROCESS_USS_REQ == gastSsaStatetable[gucCurrentTi].ucOperationCode))
         ||((SSA_FIELD_EXIST == pstSsEvent->OP_Cause)
           &&(0x1d == pstSsEvent->Cause)
           &&(TAF_SS_PROCESS_USS_REQ == gastSsaStatetable[gucCurrentTi].ucOperationCode)
            ))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}



VOS_VOID SSA_RelCompleteIndDefaultProc(
    TAF_SS_CALL_INDEPENDENT_EVENT_STRU           *pstSsEvent
)
{
    /*根据返回的错误信息，来决定上报信息*/
    pstSsEvent->SsEvent = SSA_GetRepEvtFromOpCode(gastSsaStatetable[gucCurrentTi].ucOperationCode);
    if ((TAF_SS_EVT_PROCESS_USS_REQ_CNF == pstSsEvent->SsEvent)
        ||(TAF_SS_EVT_USS_REQ_IND == pstSsEvent->SsEvent)
        ||(TAF_SS_EVT_USS_NOTIFY_IND == pstSsEvent->SsEvent)
        ||(TAF_SS_EVT_USS_RELEASE_COMPLETE_IND == pstSsEvent->SsEvent))
    {
        pstSsEvent->SsEvent = TAF_SS_EVT_PROCESS_USS_REQ_CNF;
    }
    else if ( (TAF_SS_EVT_REGISTERSS_CNF == pstSsEvent->SsEvent)
           || (TAF_SS_EVT_ERASESS_CNF == pstSsEvent->SsEvent)
           || (TAF_SS_EVT_ACTIVATESS_CNF == pstSsEvent->SsEvent)
           || (TAF_SS_EVT_DEACTIVATESS_CNF == pstSsEvent->SsEvent) )
    {
        if ( (VOS_TRUE == pstSsEvent->OP_Cause)
          && (SS_CAUSE_NORMAL_CALL_CLEARING == pstSsEvent->Cause) )
        {
            /* 对于以上携带了错误原因值16的SS事件，无需替换事件类型 */
        }
        else
        {
            pstSsEvent->SsEvent = TAF_SS_EVT_ERROR;
        }
    }
    else
    {
        pstSsEvent->SsEvent = TAF_SS_EVT_ERROR;
    }
    pstSsEvent->OP_ProblemCode = SSA_FIELD_EXIST;
    pstSsEvent->ProblemCode = TAF_ERR_ERROR;
    TAF_SsEventReport(pstSsEvent);
    SSA_TiFree(gucCurrentTi);

}


VOS_VOID SSA_RelCompleteIndProc(ST_SSP_MSG  *pMsg)
{
    VOS_UINT32                          ulRslt = SSA_SUCCESS;
    ST_END_IND                         *pEndInd;
    TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pstSsEvent;
    TAF_SS_PROCESS_USSDATA_REQ_STRU     stProcDataReq;
    ST_SSP_MSG                          stSsStatusNty;

    pstSsEvent = (TAF_SS_CALL_INDEPENDENT_EVENT_STRU *)PS_MEM_ALLOC(WUEPS_PID_SS, sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
    if (VOS_NULL_PTR == pstSsEvent)
    {
        SSA_LOG( ERROR_PRINT, "SSA_RelCompleteIndProc:ERROR: Alloc Mem Fail");
        return;
    }

    /*对事件上报的内容赋初值*/
    PS_MEM_SET(pstSsEvent, 0 , sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));

    /*获取消息内容*/
    pEndInd = &(pMsg->SspmsgCore.u.EndInd);

    /*获取ti和消息类型*/
    gucCurrentTi = pMsg->ucCr;


    /*检查TI的值是否正确,Ti值不正确的话,抛弃,打印warning信息*/
    ulRslt = SSA_GetIdByTi(&(pstSsEvent->ClientId), &(pstSsEvent->OpId), gucCurrentTi);
    if (SSA_FAILURE == ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_RelCompleteIndProc:WARNING: Invalie Ti Value");
        PS_MEM_FREE(WUEPS_PID_SS, pstSsEvent);
        return;
    }


    if (VOS_TRUE == TAF_SSA_IsNeedSsRetry(gucCurrentTi, pEndInd->enSsaSsRelCause))
    {
        /* 启动重发定时器 */
        (VOS_VOID)TAF_SSA_StartTimer(TI_TAF_SSA_RETRY_INTERVAL_TIMER,
                           TAF_SSA_GetSsRetryIntervalTimerLen(), gucCurrentTi);

        PS_MEM_FREE(WUEPS_PID_SS, pstSsEvent);
        return;
    }

    gastSsaStatetable[gucCurrentTi].ucMsgType = TAF_SS_MSG_TYPE_RLCOMPLETE;


    /* 如果保护定时器已启动，停止定时器 */
    TAF_SSA_StopAllTimer(gucCurrentTi);
    TAF_SSA_ClearBufferedMsg(gucCurrentTi);

    PS_MEM_SET(&stSsStatusNty, 0, sizeof(ST_SSP_MSG));
    stSsStatusNty.ucCr                                  = pMsg->ucCr;
    stSsStatusNty.SspmsgCore.ucChoice                   = SSA_SS_STATUS_NTY;
    stSsStatusNty.SspmsgCore.u.stSsStatusNty.enSsStatus = SSA_SS_STATUS_SETUP_FAIL;

    /*向SS发送消息*/
    Taf_SsMsgReq(&stSsStatusNty);

    SSA_RelCompleteIndCauseProc(pEndInd, pstSsEvent);

    ulRslt = SSA_RelCompleteIndFacilityProc(pEndInd, pstSsEvent);

    /* 如果USSD不兼容，则需要发送ProcessUnstructuredData给网络侧 */
    if (VOS_TRUE == SSA_JudgeUssdNotCompatiblity(ulRslt, pstSsEvent))
    {
        if ((0x00 == (gastSsaStatetable[gucCurrentTi].DatacodingScheme>> 4))
           ||(TAF_SS_7BIT_DATA_CODING == gastSsaStatetable[gucCurrentTi].DatacodingScheme))
        {
            if (VOS_TRUE != TAF_STD_AsciiNum2HexString(gastSsaStatetable[gucCurrentTi].pstUssdBuf->aucUssdStr,
                                   &(gastSsaStatetable[gucCurrentTi].pstUssdBuf->usCnt)))
            {
                SSA_LOG(WARNING_PRINT, "SSA_RelCompleteIndProc:WARNING: TAF_STD_AsciiNum2HexString fail");
            }

            SSA_Decode7bit(gastSsaStatetable[gucCurrentTi].pstUssdBuf,
                                   gastSsaStatetable[gucCurrentTi].DatacodingScheme);
        }

        PS_MEM_SET(&stProcDataReq, 0x00, sizeof(stProcDataReq));
        stProcDataReq.ucCnt = (VOS_UINT8)gastSsaStatetable[gucCurrentTi].pstUssdBuf->usCnt;
        PS_MEM_CPY(stProcDataReq.aucUserData,
                   gastSsaStatetable[gucCurrentTi].pstUssdBuf->aucUssdStr,
                   gastSsaStatetable[gucCurrentTi].pstUssdBuf->usCnt);

        /*进行ProcessUnstructuredData操作处理*/
        ulRslt = SSA_ProcessUSSDataReq((TAF_SS_PROCESS_USSDATA_REQ_STRU*)&stProcDataReq,gucCurrentTi);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_RelCompleteIndProc:WARNING: Can not encode UssdData");
            pstSsEvent->SsEvent = TAF_SS_EVT_ERROR;
            pstSsEvent->OP_Error = SSA_FIELD_EXIST;
            pstSsEvent->ErrorCode = TAF_ERR_ERROR;
            TAF_SsEventReport(pstSsEvent);
            SSA_TiFree(gucCurrentTi);
        }
        PS_MEM_FREE(WUEPS_PID_SS, pstSsEvent);
        return;
    }

    /* 如果是没有error的release complete，或者是查询操作的结果，则上报结果 */
    if ( ( (SSA_SUCCESS == ulRslt)
        && (SSA_FIELD_NOT_EXIST == pstSsEvent->OP_Cause)
        && (SSA_FIELD_NOT_EXIST == pstSsEvent->OP_Error) /*<==A32D10439*/
        && (gastSsaStatetable[gucCurrentTi].uComponenttype != TAF_SS_COMPONENT_TYPE_REJECT))
      || (TAF_SS_EVT_INTERROGATESS_CNF == pstSsEvent->SsEvent)) /*<==A32D11329*/
    {
        /*Only in case there is no cause value, could SS send a positive event to TAF to indicate SUCCESS*/
        /*事件上报给APP/AT,关闭计时器*/
        TAF_SsEventReport(pstSsEvent);
        SSA_TiFree(gucCurrentTi);
        PS_MEM_FREE(WUEPS_PID_SS, pstSsEvent);
        return;
    }

    if (((SSA_SUCCESS == ulRslt)
      && (SSA_FIELD_NOT_EXIST == pstSsEvent->OP_Cause)
      && (SSA_FIELD_EXIST == pstSsEvent->OP_Error) ))
    {
        SSA_RelCompleteIndRtrnErrProc(pstSsEvent);
        PS_MEM_FREE(WUEPS_PID_SS, pstSsEvent);
        return;
    }

    SSA_RelCompleteIndDefaultProc(pstSsEvent);
    PS_MEM_FREE(WUEPS_PID_SS, pstSsEvent);
    return;

}


VOS_VOID TAF_SSA_RcvSsCsConnInd(ST_SSP_MSG  *pstMsg)
{
    SSA_SS_CS_CONN_IND_STRU            *pstCsConnIndMsg = VOS_NULL_PTR;
    TAF_SSA_MSG_BUFF_STRU              *pstBuffMsg      = VOS_NULL_PTR;
    ST_SSP_MSG                          stSsStatusNty;

    pstCsConnIndMsg = (SSA_SS_CS_CONN_IND_STRU *)&(pstMsg->SspmsgCore.u.stCsConnInd);

    pstBuffMsg = TAF_SSA_GetBufferedMsg(pstMsg->ucCr);

    gastSsaStatetable[pstMsg->ucCr].enSsaState = pstCsConnIndMsg->enConnState;

    if ((VOS_TRUE == TAF_SSA_GetSsRetrySupportFlg())
     && (SSA_SS_CS_CONN_STATE_PRESENT == pstCsConnIndMsg->enConnState)
     && (VOS_TRUE == pstBuffMsg->bitOpBufferedBeginReqMsg))
    {
        TAF_SSA_StopTimer(TI_TAF_SSA_RETRY_PERIOD_TIMER, pstMsg->ucCr);
        TAF_SSA_StopTimer(TI_TAF_SSA_RETRY_INTERVAL_TIMER, pstMsg->ucCr);
        TAF_SSA_ClearBufferedMsg(pstMsg->ucCr);
    }

    PS_MEM_SET(&stSsStatusNty, 0, sizeof(ST_SSP_MSG));
    stSsStatusNty.ucCr                                  = pstMsg->ucCr;
    stSsStatusNty.SspmsgCore.ucChoice                   = SSA_SS_STATUS_NTY;
    stSsStatusNty.SspmsgCore.u.stSsStatusNty.enSsStatus = SSA_SS_STATUS_SETUP_SUCC;

    /*向SS发送消息*/
    Taf_SsMsgReq(&stSsStatusNty);

    return;
}


VOS_UINT32 SSA_IsSsRetryCause_CmSrvRej(
    SSA_SS_REL_CAUSE_ENUM_UINT32        enCause
)
{


    VOS_UINT8                           ucIndex;
    TAF_SSA_RETRY_CFG_STRU             *pstSsRetryCfg;

    pstSsRetryCfg = TAF_SSA_GetSsaRetryCfgInfo();

    for (ucIndex = 0; ucIndex < pstSsRetryCfg->ucSsRetryCmSrvRejCauseNum; ucIndex++)
    {
        if (enCause == pstSsRetryCfg->aucSsRetryCmSrvRejCause[ucIndex] + SSA_SS_REL_CAUSE_CM_SRV_REJ_BEGIN)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


VOS_UINT32 SSA_IsSsRetryCause_CsfbSrvRej(
    SSA_SS_REL_CAUSE_ENUM_UINT32        enCause
)
{
    /* CSFB失败不需要重拨，与NAS_MM_EndCsfbFlow中原来填的是other cause保持一致 */

    return VOS_FALSE;
}


VOS_UINT32 SSA_IsSsRetryCause_RrConnFail(
    SSA_SS_REL_CAUSE_ENUM_UINT32        enCause
)
{
    if ((SSA_SS_REL_CAUSE_RR_CONN_FAIL_IMMEDIATE_ASSIGN_REJECT          == enCause)
     || (SSA_SS_REL_CAUSE_RR_CONN_FAIL_ACCESS_BAR                       == enCause)
     || (SSA_SS_REL_CAUSE_RR_CONN_FAIL_T3122_RUNING                     == enCause)
     || (SSA_SS_REL_CAUSE_RR_CONN_FAIL_CURRENT_PROTOCOL_NOT_SUPPORT     == enCause)
     || (SSA_SS_REL_CAUSE_RR_CONN_FAIL_INVALID_UE_STATE                 == enCause)
     || (SSA_SS_REL_CAUSE_RR_CONN_FAIL_CELL_BARRED                      == enCause))
    {
        return VOS_FALSE;
    }
    else
    {
        return VOS_TRUE;
    }
}


VOS_UINT32 SSA_IsSsRetryCause_RrRel(
    SSA_SS_REL_CAUSE_ENUM_UINT32        enCause
)
{
    if ( (SSA_SS_REL_CAUSE_RR_REL_AUTH_REJ    == enCause)
      || (SSA_SS_REL_CAUSE_RR_REL_NAS_REL_REQ == enCause) )
    {
        return VOS_FALSE;
    }
    else
    {
        return VOS_TRUE;
    }
}


VOS_UINT32 SSA_IsSsRetryCause_CsfbLmmFail(
    SSA_SS_REL_CAUSE_ENUM_UINT32        enCause
)
{
    /* CSFB失败不需要重拨，与NAS_MM_EndCsfbFlow中原来填的是other cause保持一致 */

    return VOS_FALSE;
}


VOS_UINT32 SSA_IsSsRetryCause_MmInterErr(
    SSA_SS_REL_CAUSE_ENUM_UINT32        enCause
)
{
    /* SSA_SS_REL_CAUSE_MM_INTER_ERR_RESUME_TO_GU_FAIL是GU报resume_ind时ucCsResumeResult为fail, GU接入层异常，没必要再重拨
       SSA_SS_REL_CAUSE_MM_INTER_ERR_BACK_TO_LTE是CSFB异系统失败重回LTE, MMC会去GU下搜网，需要重拨
       SSA_SS_REL_CAUSE_MM_INTER_ERR_SND_SAPI3_FAIL SSA_SS_REL_CAUSE_MM_INTER_ERR_EST_SAPI3_FAIL是短信的失败原因值，
       如果报到SS这儿认为是异常，不需要重拨
       SSA_SS_REL_CAUSE_MM_INTER_ERR_ECALL_INACTIVE 不需要重拨 */

    switch (enCause)
    {
        /* cs LAU rej #12现在有NV定制有业务时会触发搜网，可以允许重拨 */
        case SSA_SS_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR:
        case SSA_SS_REL_CAUSE_MM_INTER_ERR_CS_DETACH:
        case SSA_SS_REL_CAUSE_MM_INTER_ERR_CS_SIM_INVALID:
        case SSA_SS_REL_CAUSE_MM_INTER_ERR_NOT_SUPPORT_CS_CALL_S1_MODE_ONLY:
        case SSA_SS_REL_CAUSE_MM_INTER_ERR_RESUME_TO_GU_FAIL:
        case SSA_SS_REL_CAUSE_MM_INTER_ERR_TI_INVALID:
        case SSA_SS_REL_CAUSE_MM_INTER_ERR_WAIT_EST_CNF_TIME_OUT:
        case SSA_SS_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST:
        case SSA_SS_REL_CAUSE_MM_INTER_ERR_UE_INVALID_STATE:
        case SSA_SS_REL_CAUSE_MM_INTER_ERR_WAIT_CC_REEST_TIME_OUT:
        case SSA_SS_REL_CAUSE_MM_INTER_ERR_SND_SAPI3_FAIL:
        case SSA_SS_REL_CAUSE_MM_INTER_ERR_EST_SAPI3_FAIL:
        case SSA_SS_REL_CAUSE_MM_INTER_ERR_ECALL_INACTIVE:
        case SSA_SS_REL_CAUSE_MM_INTER_ERR_REEST_FAIL:
        case SSA_SS_REL_CAUSE_MM_INTER_ERR_CC_REL_REQ:
        case SSA_SS_REL_CAUSE_MM_INTER_ERR_LTE_LIMITED_SERVICE:

            return VOS_FALSE;

        default:
            return VOS_TRUE;
    }
}


VOS_UINT32 SSA_IsSsRetryCause(
    SSA_SS_REL_CAUSE_ENUM_UINT32        enCause
)
{
    VOS_UINT32                          ulRslt;

    ulRslt  = VOS_TRUE;

    /* cm service reject */
    if ((enCause >= SSA_SS_REL_CAUSE_CM_SRV_REJ_BEGIN)
     && (enCause <= SSA_SS_REL_CAUSE_CM_SRV_REJ_END))
    {
        ulRslt = SSA_IsSsRetryCause_CmSrvRej(enCause);
    }

    /* CSFB Service reject */
    else if ((enCause >= SSA_SS_REL_CAUSE_CSFB_SRV_REJ_BEGIN)
          && (enCause <= SSA_SS_REL_CAUSE_CSFB_SRV_REJ_END))
    {
        ulRslt = SSA_IsSsRetryCause_CsfbSrvRej(enCause);
    }

    /* est_cnf失败，与NAS_MM_IsAbleRecover_EstCnfFailResult的处理逻辑保持一致 */
    else if ((enCause >= SSA_SS_REL_CAUSE_RR_CONN_FAIL_BEGIN)
          && (enCause <= SSA_SS_REL_CAUSE_RR_CONN_FAIL_END))
    {
        ulRslt = SSA_IsSsRetryCause_RrConnFail(enCause);

    }

    /* rel_ind, 除了鉴权被拒，其他原因值与NAS_MM_IsNeedCmServiceRetry_RelIndResult的处理逻辑保持一致 */
    else if ((enCause >= SSA_SS_REL_CAUSE_RR_REL_BEGIN)
          && (enCause <= SSA_SS_REL_CAUSE_RR_REL_END))
    {
        ulRslt = SSA_IsSsRetryCause_RrRel(enCause);
    }

    /* 除了鉴权被拒，其他原因值暂时定为都需要重拨 */
    else if ((enCause >= SSA_SS_REL_CAUSE_CSFB_LMM_FAIL_BEGIN)
          && (enCause <= SSA_SS_REL_CAUSE_CSFB_LMM_FAIL_END))
    {
        ulRslt = SSA_IsSsRetryCause_CsfbLmmFail(enCause);
    }

    /* MM INTER ERR */
    else if ((enCause >= SSA_SS_REL_CAUSE_MM_INTER_ERR_BEGIN)
          && (enCause <= SSA_SS_REL_CAUSE_MM_INTER_ERR_END))
    {
        ulRslt = SSA_IsSsRetryCause_MmInterErr(enCause);
    }

    else
    {
        /* 其他情况不需要重拨 */
        ulRslt  = VOS_FALSE;
    }

    return ulRslt;
}


VOS_UINT32 TAF_SSA_IsNeedSsRetry(
    VOS_UINT8                           ucTi,
    SSA_SS_REL_CAUSE_ENUM_UINT32        enRelCause
)
{
    VOS_UINT32                          ulSsRetryPeriodRemainLen;
    VOS_UINT32                          ulSsRetryIntervalLen;
    VOS_UINT32                          ulSsRetrySupportFlg;
    VOS_UINT32                          ulIsSsRetryCause;

    ulSsRetryPeriodRemainLen = 0;
    ulSsRetrySupportFlg      = TAF_SSA_GetSsRetrySupportFlg();
    ulSsRetryIntervalLen     = TAF_SSA_GetSsRetryIntervalTimerLen();

    if (TAF_SSA_TIMER_STATUS_RUNING == TAF_SSA_GetTimerStatus(TI_TAF_SSA_RETRY_PERIOD_TIMER, ucTi))
    {
        ulSsRetryPeriodRemainLen = TAF_SSA_GetTimerRemainLen(TI_TAF_SSA_RETRY_PERIOD_TIMER, ucTi);
    }

    ulIsSsRetryCause    = SSA_IsSsRetryCause(enRelCause);

    if ((VOS_TRUE == ulSsRetrySupportFlg)
     && (TAF_SSA_STATE_CONN_PENDING == gastSsaStatetable[ucTi].enSsaState)
     && (VOS_TRUE == ulIsSsRetryCause)
     && (ulSsRetryPeriodRemainLen > ulSsRetryIntervalLen))
    {
        /* 满足重发条件:
           1.ss重发nv项开启
           2.状态在等连接建立
           3.连接释放原因值满足重建条件不为SSA_SS_REL_CAUSE_MM_REJ_OTHER_CAUSES和SSA_SS_REL_CAUSE_AS_REJ_OTHER_CAUSES
           4.剩余时间大于重建间隔时长 */
        return VOS_TRUE;
    }

    return VOS_FALSE;
}



/*lint -e429 -e830*/


VOS_VOID TAF_SsEventReport (TAF_SS_CALL_INDEPENDENT_EVENT_STRU  *pEvent)
{
    VOS_UINT32                          ulOamRcvPid;

    if (TAF_SS_MSG_TYPE_REGISTER == gastSsaStatetable[gucCurrentTi].ucMsgType)
    {
        if (1 == pEvent->OP_Error )
        {
            /*在出错情况下，不广播上报,并在状态表中记录ClientId和OpId*/
            pEvent->OpId = gucCurrentTi + 120;
            gastSsaStatetable[gucCurrentTi].ClientId = pEvent->ClientId;
            gastSsaStatetable[gucCurrentTi].OpId = pEvent->OpId;

            MN_SendClientEvent(pEvent->ClientId,
                MN_CALLBACK_SS,
                pEvent->SsEvent,
                pEvent);

        }
        else
        {
            /*在REGISTER消息类型下，向APP发送广播消息,并在状态表中记录ClientId和OpId*/
            pEvent->ClientId = MN_CLIENT_ALL;
            pEvent->OpId = gucCurrentTi + 120;
            gastSsaStatetable[gucCurrentTi].ClientId = pEvent->ClientId;
            gastSsaStatetable[gucCurrentTi].OpId = pEvent->OpId;

            MN_SendClientEvent(pEvent->ClientId,
                MN_CALLBACK_SS,
                pEvent->SsEvent,
                pEvent);
        }

    }
    else
    {
        ulOamRcvPid = MN_GetPidFromClientId(pEvent->ClientId);

        if ( MAPS_STK_PID == ulOamRcvPid )
        {
            pEvent->ClientId = MN_CLIENT_ALL;
            pEvent->OpId = gucCurrentTi + 120;
            gastSsaStatetable[gucCurrentTi].ClientId = pEvent->ClientId;
            gastSsaStatetable[gucCurrentTi].OpId = pEvent->OpId;
        }

        MN_SendClientEvent(pEvent->ClientId,
            MN_CALLBACK_SS,
            pEvent->SsEvent,
            pEvent);
    }
    return;
}
/*lint +e429 +e830*/

/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
