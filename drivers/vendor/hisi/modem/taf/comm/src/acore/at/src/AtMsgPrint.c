

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "ATCmdProc.h"
#include "product_config.h"
#include "AtMsgPrint.h"
#include "AtCheckFunc.h"
#include "AtCmdSmsProc.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*lint -e767 -e960 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define THIS_FILE_ID        PS_FILE_ID_AT_MSG_PRINT_C
/*lint +e767 +e960 修改人:罗建 107747;检视人:sunshaohua*/

/*****************************************************************************
  2 宏定义
*****************************************************************************/


/*****************************************************************************
  3类型定义
*****************************************************************************/


/*****************************************************************************
  5 函数实现
*****************************************************************************/

TAF_UINT32 AT_StubSendAutoReplyMsg(
    VOS_UINT8                           ucIndex,
    MN_MSG_EVENT_INFO_STRU              *pstEvent,
    MN_MSG_TS_DATA_INFO_STRU            *pstTsDataInfo
)
{
    MN_MSG_SEND_PARM_STRU               stSendMsg;
    MN_MSG_TS_DATA_INFO_STRU            *pstTsSubmitInfo;
    MN_MSG_SUBMIT_STRU                  *pstSubmit;
    TAF_UINT32                          ulRet;

    /*1. 为自动回复消息SUBMIT申请内存并情况*/
    pstTsSubmitInfo = (MN_MSG_TS_DATA_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, sizeof(MN_MSG_TS_DATA_INFO_STRU));
    if (VOS_NULL_PTR == pstTsSubmitInfo)
    {
        return AT_ERROR;
    }
    PS_MEM_SET(pstTsSubmitInfo, 0x00, sizeof(MN_MSG_TS_DATA_INFO_STRU));

    /*2. 为自动回复消息SUBMIT填写TPDU数据内容*/
    pstTsSubmitInfo->enTpduType = MN_MSG_TPDU_SUBMIT;
    pstSubmit = (MN_MSG_SUBMIT_STRU *)&pstTsSubmitInfo->u.stSubmit;
    PS_MEM_CPY(&pstSubmit->stDestAddr,
               &pstTsDataInfo->u.stDeliver.stOrigAddr,
               sizeof(pstSubmit->stDestAddr));
    PS_MEM_CPY(&pstSubmit->stDcs,
               &pstTsDataInfo->u.stDeliver.stDcs,
               sizeof(pstSubmit->stDcs));
    pstSubmit->stValidPeriod.enValidPeriod = MN_MSG_VALID_PERIOD_NONE;

    /*3. 为自动回复消息SUBMIT编码*/
    ulRet = MN_MSG_Encode(pstTsSubmitInfo, &stSendMsg.stMsgInfo.stTsRawData);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        PS_MEM_FREE(WUEPS_PID_AT, pstTsSubmitInfo);
        return AT_ERROR;
    }

    /*4. 填写回复消息的短信中心, 存储设备，消息类型和发送域*/
    stSendMsg.enDomain                          = MN_MSG_SEND_DOMAIN_CS_PREFERRED;
    stSendMsg.enMemStore                        = MN_MSG_MEM_STORE_NONE;
    stSendMsg.enClientType                      = MN_MSG_CLIENT_NORMAL;
    stSendMsg.stMsgInfo.stTsRawData.enTpduType  = MN_MSG_TPDU_SUBMIT;
    PS_MEM_CPY(&stSendMsg.stMsgInfo.stScAddr,
               &pstEvent->u.stDeliverInfo.stRcvMsgInfo.stScAddr,
               sizeof(stSendMsg.stMsgInfo.stScAddr));

    /*5. 发送回复消息*/
    ulRet = MN_MSG_Send(ucIndex, 0, &stSendMsg);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        ulRet = AT_ERROR;
    }
    else
    {
        ulRet = AT_OK;
    }
    PS_MEM_FREE(WUEPS_PID_AT, pstTsSubmitInfo);

    return ulRet;
}


TAF_VOID AT_StubClearSpecificAutoRelyMsg(
    VOS_UINT8                           ucClientIndex,
    TAF_UINT32                          ulBufferIndex
)
{
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucClientIndex);

    if (VOS_NULL_PTR != pstSmsCtx->astSmsMtBuffer[ulBufferIndex].pstEvent)
    {
        PS_MEM_FREE(WUEPS_PID_AT, pstSmsCtx->astSmsMtBuffer[ulBufferIndex].pstEvent);
    }

    if (VOS_NULL_PTR != pstSmsCtx->astSmsMtBuffer[ulBufferIndex].pstTsDataInfo)
    {
        PS_MEM_FREE(WUEPS_PID_AT, pstSmsCtx->astSmsMtBuffer[ulBufferIndex].pstTsDataInfo);
    }

    return;
}


TAF_VOID AT_StubTriggerAutoReply(
    VOS_UINT8                           ucIndex,
    TAF_UINT8                           ucCfgValue
)
{
    TAF_UINT8                           ucLoop;
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    pstSmsCtx->ucSmsAutoReply = ucCfgValue;

    /*若关闭自动回复功能，则清空相关动态内存*/
    if (0 == pstSmsCtx->ucSmsAutoReply)
    {
        for (ucLoop = 0; ucLoop < AT_SMSMT_BUFFER_MAX; ucLoop++)
        {
            AT_StubClearSpecificAutoRelyMsg(ucIndex, ucLoop);
            pstSmsCtx->astSmsMtBuffer[ucLoop].bUsed = TAF_FALSE;
        }

        return;
    }

    /*若已启用自动回复功能，按顺序回复接收到的短信*/
    for (ucLoop = 0; ucLoop < AT_SMSMT_BUFFER_MAX; ucLoop++)
    {
        if (TAF_TRUE != pstSmsCtx->astSmsMtBuffer[ucLoop].bUsed)
        {
            AT_StubClearSpecificAutoRelyMsg(ucIndex, ucLoop);
            continue;
        }

        if ((VOS_NULL_PTR == pstSmsCtx->astSmsMtBuffer[ucLoop].pstEvent)
         || (VOS_NULL_PTR == pstSmsCtx->astSmsMtBuffer[ucLoop].pstTsDataInfo))
        {

            AT_StubClearSpecificAutoRelyMsg(ucIndex, ucLoop);
            pstSmsCtx->astSmsMtBuffer[ucLoop].bUsed = TAF_FALSE;
            continue;
        }

        AT_StubSendAutoReplyMsg(ucIndex,
                                pstSmsCtx->astSmsMtBuffer[ucLoop].pstEvent,
                                pstSmsCtx->astSmsMtBuffer[ucLoop].pstTsDataInfo);
        AT_StubClearSpecificAutoRelyMsg(ucIndex, ucLoop);
        pstSmsCtx->astSmsMtBuffer[ucLoop].bUsed = TAF_FALSE;
        break;
    }

    return;

}


TAF_VOID AT_StubSaveAutoReplyData(
    VOS_UINT8                           ucIndex,
    MN_MSG_EVENT_INFO_STRU             *pstEvent,
    MN_MSG_TS_DATA_INFO_STRU           *pstTsDataInfo
)
{
    TAF_UINT8                           ucLoop;
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    /*自动回复功能未开启直接返回;*/
    if (0 == pstSmsCtx->ucSmsAutoReply)
    {
        return;
    }

    /*接收消息不是DELIVER短信或TP-RP没有置位直接返回*/
    if ((MN_MSG_TPDU_DELIVER != pstTsDataInfo->enTpduType)
     || (VOS_TRUE != pstTsDataInfo->u.stDeliver.bReplayPath))
    {
        return;
    }

    /*申请并保存自动回复相关参数到缓存*/
    for (ucLoop = 0; ucLoop < AT_SMSMT_BUFFER_MAX; ucLoop++)
    {
        if (TAF_TRUE == pstSmsCtx->astSmsMtBuffer[ucLoop].bUsed)
        {
            continue;
        }

        AT_StubClearSpecificAutoRelyMsg(ucIndex, ucLoop);

        /*记录接收短信信息记录到内存，用于 GCF测试用例34。2。8*/
        pstSmsCtx->astSmsMtBuffer[ucLoop].pstEvent = (MN_MSG_EVENT_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT,
                                                  sizeof(MN_MSG_EVENT_INFO_STRU));
        if (VOS_NULL_PTR == pstSmsCtx->astSmsMtBuffer[ucLoop].pstEvent)
        {
            AT_WARN_LOG("At_SmsDeliverProc: Fail to alloc memory.");
            return;
        }

        pstSmsCtx->astSmsMtBuffer[ucLoop].pstTsDataInfo = (MN_MSG_TS_DATA_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT,
                                                     sizeof(MN_MSG_TS_DATA_INFO_STRU));
        if (VOS_NULL_PTR == pstSmsCtx->astSmsMtBuffer[ucLoop].pstTsDataInfo)
        {
            PS_MEM_FREE(WUEPS_PID_AT, pstSmsCtx->astSmsMtBuffer[ucLoop].pstEvent);
            AT_WARN_LOG("At_SmsDeliverProc: Fail to alloc memory.");
            return;
        }

        PS_MEM_CPY(pstSmsCtx->astSmsMtBuffer[ucLoop].pstEvent, pstEvent, sizeof(MN_MSG_EVENT_INFO_STRU));
        PS_MEM_CPY(pstSmsCtx->astSmsMtBuffer[ucLoop].pstTsDataInfo,
                   pstTsDataInfo,
                   sizeof(MN_MSG_TS_DATA_INFO_STRU));

        pstSmsCtx->astSmsMtBuffer[ucLoop].bUsed = TAF_TRUE;

        break;
    }

    return;
}


VOS_UINT32 At_SendDomainProtoToNvim(
    AT_CGSMS_SEND_DOMAIN_ENUM_U8        enProtoSendDomain
)
{
    VOS_UINT32                          ulNvimSendDomain;

    if (MN_MSG_SEND_DOMAIN_PS == enProtoSendDomain)
    {
        ulNvimSendDomain = AT_NV_SMS_DOMAIN_PS_ONLY;
    }
    else if (MN_MSG_SEND_DOMAIN_CS == enProtoSendDomain)
    {
        ulNvimSendDomain = AT_NV_SMS_DOMAIN_CS_ONLY;
    }
    else if (MN_MSG_SEND_DOMAIN_PS_PREFERRED == enProtoSendDomain)
    {
        ulNvimSendDomain = AT_NV_SMS_DOMAIN_PS_PREFERRED;
    }
    else
    {
        ulNvimSendDomain = AT_NV_SMS_DOMAIN_CS_PREFERRED;
    }

    return ulNvimSendDomain;
}


VOS_UINT32 At_ParseCsmpFo(
    VOS_UINT8                           *pucFo
)
{
    TAF_UINT32                          ulRet;

    /* 检查<fo>,数字类型 */
    ulRet = At_CheckNumString(gastAtParaList[0].aucPara,gastAtParaList[0].usParaLen);
    if (AT_SUCCESS != ulRet)
    {
        return AT_CMS_OPERATION_NOT_ALLOWED;
    }

    /* 注意: gastAtParaList[0].ulParaValue此时尚未转换，检查其它命令的这种情况 */
    ulRet = At_Auc2ul(gastAtParaList[0].aucPara,gastAtParaList[0].usParaLen,
                      &gastAtParaList[0].ulParaValue);
    if (AT_FAILURE == ulRet)
    {
        return AT_CMS_OPERATION_NOT_ALLOWED;
    }

    /* 检查<fo>,一个字节 */
    if (gastAtParaList[0].ulParaValue > 0xff)
    {
        return AT_CMS_OPERATION_NOT_ALLOWED;
    }

    if ((0x01 != (0x03 & gastAtParaList[0].ulParaValue))
     && (0x02 != (0x03 & gastAtParaList[0].ulParaValue)))
    {
        return AT_CMS_OPERATION_NOT_ALLOWED;
    }

    *pucFo = (TAF_UINT8)gastAtParaList[0].ulParaValue;

    return AT_SUCCESS;
}


TAF_UINT32 At_GetAbsoluteTime(
    TAF_UINT8                           *pucTimeStr,
    TAF_UINT16                          usTimeStrLen,
    MN_MSG_TIMESTAMP_STRU               *pstAbsoluteTime
)
{
    TAF_UINT32                          ulRet;
    TAF_UINT8                           aucBcdNum[2];
    TAF_UINT32                          ulTmp               = 0;


    aucBcdNum[0] = 0;
    aucBcdNum[1] = 0;


    /* 6th of May 1994, 22:10:00 GMT+2 "94/05/06,22:10:00+08"
       注意:还要判断中间字符是否合法
    */
    if ((TAF_NULL_PTR == pucTimeStr)
     || (TAF_NULL_PTR == pstAbsoluteTime))
    {
        AT_WARN_LOG("At_GetAbsoluteTime: parameter is NULL.");
        return AT_ERROR;
    }

    /* 检查<vp>,字符串类型 */
    if ((22 != usTimeStrLen)
     || ('"' != pucTimeStr[0])
     || ('"' != pucTimeStr[usTimeStrLen - 1])/* '"' */
     || ('/' != pucTimeStr[3])/* '/' */
     || ('/' != pucTimeStr[6])/* '/' */
     || (',' != pucTimeStr[9])/* ',' */
     || (':' != pucTimeStr[12])/* ':' */
     || (':' != pucTimeStr[15]))/* ':' */
    {
        return AT_CMS_OPERATION_NOT_ALLOWED;
    }

    /* Year */
    ulRet = At_AsciiNum2BcdNum(aucBcdNum, &pucTimeStr[1], 2);
    if (AT_SUCCESS != ulRet)
    {
        return AT_CMS_OPERATION_NOT_ALLOWED;
    }
    pstAbsoluteTime->ucYear = AT_BCD_REVERSE(aucBcdNum[0]);


    /* Month */
    ulRet = At_AsciiNum2BcdNum(aucBcdNum, &pucTimeStr[4], 2);
    if (AT_SUCCESS != ulRet)
    {
        return AT_CMS_OPERATION_NOT_ALLOWED;
    }
    pstAbsoluteTime->ucMonth = AT_BCD_REVERSE(aucBcdNum[0]);

    /* Day */
    ulRet = At_AsciiNum2BcdNum(aucBcdNum, &pucTimeStr[7], 2);
    if(AT_SUCCESS != ulRet)
    {
        return AT_CMS_OPERATION_NOT_ALLOWED;
    }
    pstAbsoluteTime->ucDay = AT_BCD_REVERSE(aucBcdNum[0]);

    /* Hour */
    ulRet = At_AsciiNum2BcdNum(aucBcdNum, &pucTimeStr[10], 2);
    if(AT_SUCCESS != ulRet)
    {
        return AT_CMS_OPERATION_NOT_ALLOWED;
    }
    pstAbsoluteTime->ucHour = AT_BCD_REVERSE(aucBcdNum[0]);

    /* Minute */
    ulRet = At_AsciiNum2BcdNum(aucBcdNum, &pucTimeStr[13], 2);
    if(AT_SUCCESS != ulRet)
    {
        return AT_CMS_OPERATION_NOT_ALLOWED;
    }
    pstAbsoluteTime->ucMinute = AT_BCD_REVERSE(aucBcdNum[0]);

    /* Second */
    ulRet = At_AsciiNum2BcdNum(aucBcdNum, &pucTimeStr[16], 2);
    if(AT_SUCCESS != ulRet)
    {
        return AT_CMS_OPERATION_NOT_ALLOWED;
    }
    pstAbsoluteTime->ucSecond = AT_BCD_REVERSE(aucBcdNum[0]);

    if(AT_FAILURE == At_Auc2ul(&pucTimeStr[19],2,&ulTmp))
    {
        return AT_CMS_OPERATION_NOT_ALLOWED;
    }

    if ((0 != (ulTmp % 4))
     || (ulTmp > AT_MAX_TIMEZONE_VALUE))
    {
        return AT_CMS_OPERATION_NOT_ALLOWED;
    }

    /* '+' 或者 '-' */
    switch(pucTimeStr[18])
    {
    case '+':
        pstAbsoluteTime->cTimezone = (TAF_INT8)ulTmp;
        break;

    case '-':
        pstAbsoluteTime->cTimezone = (TAF_INT8)((-1) * ulTmp);
        break;

    default:
        return AT_CMS_OPERATION_NOT_ALLOWED;
    }

    return AT_SUCCESS;

}


VOS_UINT32  AT_SetAbsoluteValidPeriod(
    VOS_UINT8                           ucIndex,
    TAF_UINT8                          *pucPara,
    TAF_UINT16                          usParaLen,
    MN_MSG_VALID_PERIOD_STRU           *pstValidPeriod
)
{
    TAF_UINT32                          ulRet;
    TAF_UINT8                           ucDateInvalidType;
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    if (0 == usParaLen)
    {
        if (MN_MSG_VALID_PERIOD_ABSOLUTE == pstSmsCtx->stCscaCsmpInfo.stVp.enValidPeriod)
        {
            PS_MEM_CPY(pstValidPeriod, &(pstSmsCtx->stCscaCsmpInfo.stVp), sizeof(MN_MSG_VALID_PERIOD_STRU));
            return AT_SUCCESS;
        }
        else
        {
            return AT_ERROR;
        }
    }
    else
    {
        ulRet = At_GetAbsoluteTime(pucPara,
                                   usParaLen,
                                   &pstValidPeriod->u.stAbsoluteTime);
        if (AT_SUCCESS != ulRet)
        {
            return ulRet;
        }

        ulRet = MN_MSG_ChkDate(&pstValidPeriod->u.stAbsoluteTime, &ucDateInvalidType);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            return AT_CMS_OPERATION_NOT_ALLOWED;
        }

        return AT_SUCCESS;
    }
}


VOS_UINT32  AT_SetRelativeValidPeriod(
    VOS_UINT8                           ucIndex,
    TAF_UINT8                          *pucPara,
    TAF_UINT16                          usParaLen,
    MN_MSG_VALID_PERIOD_STRU           *pstValidPeriod
)
{
    TAF_UINT32                          ulRet;
    TAF_UINT32                          ulRelativeValidPeriod;
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    if (0 == usParaLen)
    {
        if (MN_MSG_VALID_PERIOD_RELATIVE == pstSmsCtx->stCscaCsmpInfo.stVp.enValidPeriod)
        {
            PS_MEM_CPY(pstValidPeriod, &(pstSmsCtx->stCscaCsmpInfo.stVp), sizeof(MN_MSG_VALID_PERIOD_STRU));
            return AT_SUCCESS;
        }
        else if (MN_MSG_VALID_PERIOD_NONE == pstSmsCtx->stCscaCsmpInfo.stVp.enValidPeriod)
        {
            pstValidPeriod->u.ucOtherTime = 167;
            return AT_SUCCESS;
        }
        else
        {
            return AT_ERROR;
        }
    }
    else
    {
        /* 检查<vp>,数字类型 */
        ulRet = At_CheckNumString(pucPara, usParaLen);
        if (AT_SUCCESS != ulRet)
        {
            return AT_CMS_OPERATION_NOT_ALLOWED;
        }

        /* 注意: gastAtParaList[1].ulParaValue此时尚未转换，检查其它命令的这种情况 */
        ulRet = At_Auc2ul(pucPara, usParaLen, &ulRelativeValidPeriod);
        if (AT_FAILURE == ulRet)
        {
            return AT_CMS_OPERATION_NOT_ALLOWED;
        }

        if (ulRelativeValidPeriod > 255)
        {
            return AT_CMS_OPERATION_NOT_ALLOWED;
        }

        pstValidPeriod->u.ucOtherTime = (TAF_UINT8)ulRelativeValidPeriod;
        return AT_SUCCESS;
    }
}


VOS_UINT32 At_ParseCsmpVp(
    VOS_UINT8                           ucIndex,
    MN_MSG_VALID_PERIOD_STRU           *pstVp
)
{
    TAF_UINT32                          ulRet;
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    /*获取当前配置的TP-VPF值，若用户不配置TP-VPF和TP-VP两项，则复制当前结构到临时结构并推出*/
    if (0 != gastAtParaList[0].usParaLen)
    {
        AT_GET_MSG_TP_VPF(pstVp->enValidPeriod, pstSmsCtx->stCscaCsmpInfo.ucTmpFo);
    }
    else if (0 != gastAtParaList[1].usParaLen)
    {
        pstVp->enValidPeriod = pstSmsCtx->stCscaCsmpInfo.stVp.enValidPeriod;
    }
    else
    {
        PS_MEM_CPY(pstVp, &(pstSmsCtx->stCscaCsmpInfo.stVp), sizeof(MN_MSG_VALID_PERIOD_STRU));
        return AT_SUCCESS;
    }

    /*短信有效期类型设置为无效，<VP>参数项必须为空*/
    if (MN_MSG_VALID_PERIOD_NONE == pstVp->enValidPeriod)
    {
        if (0 != gastAtParaList[1].usParaLen)
        {
            return AT_ERROR;
        }
        PS_MEM_SET(pstVp, 0x00, sizeof(MN_MSG_VALID_PERIOD_STRU));
        return AT_SUCCESS;
    }
    /*短信有效期类型设置为相对有效期，*/
    else if (MN_MSG_VALID_PERIOD_RELATIVE == pstVp->enValidPeriod)
    {
        ulRet = AT_SetRelativeValidPeriod(ucIndex,
                                          gastAtParaList[1].aucPara,
                                          gastAtParaList[1].usParaLen,
                                          pstVp);
        return ulRet;
    }
    else if(MN_MSG_VALID_PERIOD_ABSOLUTE == pstVp->enValidPeriod)
    {
        ulRet = AT_SetAbsoluteValidPeriod(ucIndex,
                                          gastAtParaList[1].aucPara,
                                          gastAtParaList[1].usParaLen,
                                          pstVp);
        return ulRet;
    }
    else
    {
        return AT_CMS_OPERATION_NOT_ALLOWED;
    }

}


TAF_VOID At_MsgResultCodeFormat(
    TAF_UINT8                           ucIndex,
    TAF_UINT16                          usLength
)
{
    if(AT_V_ENTIRE_TYPE == gucAtVType)
    {
        PS_MEM_CPY((TAF_CHAR *)pgucAtSndCrLfAddr,(TAF_CHAR *)gaucAtCrLf,2);/*Code前面加\r\n*/
        At_SendResultData(ucIndex,pgucAtSndCrLfAddr,usLength + 2);
    }
    else
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%s",gaucAtCrLf);
        At_SendResultData(ucIndex,pgucAtSndCodeAddr,usLength);
    }

    return;
}


TAF_VOID At_GetMsgFoValue(
    MN_MSG_TS_DATA_INFO_STRU            *pstTsDataInfo,
    TAF_UINT8                           *pucFo
)
{
    TAF_UINT8                           ucFo                = 0;

    switch (pstTsDataInfo->enTpduType)
    {
        case MN_MSG_TPDU_DELIVER:
            /* TP-MTI, TP-MMS, TP-RP, TP_UDHI, TP-SRI:*/
            AT_SET_MSG_TP_MTI(ucFo, AT_MSG_TP_MTI_DELIVER);
            AT_SET_MSG_TP_MMS(ucFo, pstTsDataInfo->u.stDeliver.bMoreMsg);
            AT_SET_MSG_TP_RP(ucFo, pstTsDataInfo->u.stDeliver.bReplayPath);
            AT_SET_MSG_TP_UDHI(ucFo, pstTsDataInfo->u.stDeliver.bUserDataHeaderInd);
            AT_SET_MSG_TP_SRI(ucFo, pstTsDataInfo->u.stDeliver.bStaRptInd);
            break;
        case MN_MSG_TPDU_DELIVER_RPT_ACK:
            /*TP MTI  TP-UDHI  */
            AT_SET_MSG_TP_MTI(ucFo, AT_MSG_TP_MTI_DELIVER_REPORT);
            AT_SET_MSG_TP_UDHI(ucFo, pstTsDataInfo->u.stDeliverRptAck.bUserDataHeaderInd);
            break;
        case MN_MSG_TPDU_DELIVER_RPT_ERR:
            /*TP MTI  TP-UDHI  */
            AT_SET_MSG_TP_MTI(ucFo, AT_MSG_TP_MTI_DELIVER_REPORT);
            AT_SET_MSG_TP_UDHI(ucFo, pstTsDataInfo->u.stDeliverRptErr.bUserDataHeaderInd);
            break;
        case MN_MSG_TPDU_STARPT:
            /*TP MTI TP UDHI TP MMS TP SRQ*/
            AT_SET_MSG_TP_MTI(ucFo, AT_MSG_TP_MTI_STATUS_REPORT);
            AT_SET_MSG_TP_UDHI(ucFo, pstTsDataInfo->u.stStaRpt.bUserDataHeaderInd);
            AT_SET_MSG_TP_MMS(ucFo, pstTsDataInfo->u.stStaRpt.bMoreMsg);
            AT_SET_MSG_TP_SRQ(ucFo, pstTsDataInfo->u.stStaRpt.bStaRptQualCommand);/*??*/
            break;
        case MN_MSG_TPDU_SUBMIT:
            AT_SET_MSG_TP_MTI(ucFo, AT_MSG_TP_MTI_SUBMIT);
            AT_SET_MSG_TP_RD(ucFo, pstTsDataInfo->u.stSubmit.bRejectDuplicates);
            AT_SET_MSG_TP_VPF(ucFo, pstTsDataInfo->u.stSubmit.stValidPeriod.enValidPeriod);
            AT_SET_MSG_TP_RP(ucFo, pstTsDataInfo->u.stSubmit.bReplayPath);
            AT_SET_MSG_TP_UDHI(ucFo, pstTsDataInfo->u.stSubmit.bUserDataHeaderInd);
            AT_SET_MSG_TP_SRR(ucFo, pstTsDataInfo->u.stSubmit.bStaRptReq);
            break;
        case MN_MSG_TPDU_COMMAND:
            /*TP MTI TP UDHI TP SRR */
            AT_SET_MSG_TP_MTI(ucFo, AT_MSG_TP_MTI_COMMAND);
            AT_SET_MSG_TP_UDHI(ucFo, pstTsDataInfo->u.stCommand.bUserDataHeaderInd);
            AT_SET_MSG_TP_SRR(ucFo, pstTsDataInfo->u.stCommand.bStaRptReq);
            break;
        case MN_MSG_TPDU_SUBMIT_RPT_ACK:
            /*TP MTI  TP-UDHI  */
            AT_SET_MSG_TP_MTI(ucFo, AT_MSG_TP_MTI_SUBMIT_REPORT);
            AT_SET_MSG_TP_UDHI(ucFo, pstTsDataInfo->u.stSubmitRptAck.bUserDataHeaderInd);
            break;
        case MN_MSG_TPDU_SUBMIT_RPT_ERR:
            /*TP MTI  TP-UDHI  */
            AT_SET_MSG_TP_MTI(ucFo, AT_MSG_TP_MTI_SUBMIT_REPORT);
            AT_SET_MSG_TP_UDHI(ucFo, pstTsDataInfo->u.stSubmitRptErr.bUserDataHeaderInd);
            break;
        default:
            AT_NORM_LOG("At_GetMsgFoValue: invalid TPDU type.");
            break;
    }

    *pucFo = ucFo;
    return;
}


VOS_VOID At_SendMsgFoAttr(
    VOS_UINT8                           ucIndex,
    MN_MSG_TS_DATA_INFO_STRU            *pstTsDataInfo
)
{
    TAF_UINT8                           ucFo = 0;
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    if (AT_CMD_CMGC_TEXT_SET == gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        ucFo = gastAtClientTab[ucIndex].AtSmsData.ucFo;
    }
    else
    {
        /*判断FO的有效性*/
        if (TAF_TRUE == pstSmsCtx->stCscaCsmpInfo.bFoUsed)
        {
            ucFo = pstSmsCtx->stCscaCsmpInfo.ucFo;
        }
        else
        {
            if ((MN_MSG_TPDU_DELIVER == pstTsDataInfo->enTpduType)
             || (MN_MSG_TPDU_SUBMIT == pstTsDataInfo->enTpduType))
            {
                ucFo = AT_CSMP_FO_DEFAULT_VALUE1;
            }
            else if ((MN_MSG_TPDU_STARPT == pstTsDataInfo->enTpduType)
                  || (MN_MSG_TPDU_COMMAND == pstTsDataInfo->enTpduType))
            {
                ucFo = AT_CSMP_FO_DEFAULT_VALUE2;
            }
            else
            {
                AT_NORM_LOG("At_SendMsgFoAttr: invalid enTpduType.");
                return;
            }
        }

    }

    switch (pstTsDataInfo->enTpduType)
    {
        case MN_MSG_TPDU_COMMAND:
            /*TP MTI TP UDHI TP SRR */
            AT_GET_MSG_TP_UDHI(pstTsDataInfo->u.stCommand.bUserDataHeaderInd, ucFo);
            AT_GET_MSG_TP_SRR(pstTsDataInfo->u.stCommand.bStaRptReq, ucFo);
            break;

        case MN_MSG_TPDU_DELIVER:
            /* TP-MTI, TP-MMS, TP-RP, TP_UDHI, TP-SRI:*/
            /*decode fo:TP MTI TP MMS TP RP TP UDHI TP SRI*/
            AT_GET_MSG_TP_MMS(pstTsDataInfo->u.stDeliver.bMoreMsg, ucFo);
            AT_GET_MSG_TP_RP(pstTsDataInfo->u.stDeliver.bReplayPath, ucFo);
            AT_GET_MSG_TP_UDHI(pstTsDataInfo->u.stDeliver.bUserDataHeaderInd, ucFo);
            AT_GET_MSG_TP_SRI(pstTsDataInfo->u.stDeliver.bStaRptInd, ucFo);
            break;

        case MN_MSG_TPDU_STARPT:
            /*TP MTI ignore TP UDHI TP MMS TP SRQ*/
            AT_GET_MSG_TP_UDHI(pstTsDataInfo->u.stStaRpt.bUserDataHeaderInd, ucFo);
            AT_GET_MSG_TP_MMS(pstTsDataInfo->u.stStaRpt.bMoreMsg, ucFo);
            AT_GET_MSG_TP_SRQ(pstTsDataInfo->u.stStaRpt.bStaRptQualCommand, ucFo);
            break;

        case MN_MSG_TPDU_SUBMIT:
            AT_GET_MSG_TP_RD(pstTsDataInfo->u.stSubmit.bRejectDuplicates, ucFo);
            /*TP VPF 23040 9.2.3.3*/
            AT_GET_MSG_TP_VPF(pstTsDataInfo->u.stSubmit.stValidPeriod.enValidPeriod, ucFo);
            /*TP RP  23040 9.2.3.17*/
            AT_GET_MSG_TP_RP(pstTsDataInfo->u.stSubmit.bReplayPath, ucFo);
            /*TP UDHI23040 9.2.3.23*/
            AT_GET_MSG_TP_UDHI(pstTsDataInfo->u.stSubmit.bUserDataHeaderInd, ucFo);
            /*TP SRR 23040 9.2.3.5*/
            AT_GET_MSG_TP_SRR(pstTsDataInfo->u.stSubmit.bStaRptReq, ucFo);
            break;

        case MN_MSG_TPDU_DELIVER_RPT_ACK:
            /*TP MTI ignore  TP-UDHI  */
            AT_GET_MSG_TP_UDHI(pstTsDataInfo->u.stDeliverRptAck.bUserDataHeaderInd, ucFo);
            break;

        case MN_MSG_TPDU_DELIVER_RPT_ERR:
            /*TP MTI ignore  TP-UDHI  */
            AT_GET_MSG_TP_UDHI(pstTsDataInfo->u.stDeliverRptErr.bUserDataHeaderInd, ucFo);
            break;

        case MN_MSG_TPDU_SUBMIT_RPT_ACK:
            /*TP MTI ignore TP-UDHI  */
            AT_GET_MSG_TP_UDHI(pstTsDataInfo->u.stSubmitRptAck.bUserDataHeaderInd, ucFo);
            break;

        case MN_MSG_TPDU_SUBMIT_RPT_ERR:
            /*TP MTI ignore TP-UDHI  */
            AT_GET_MSG_TP_UDHI(pstTsDataInfo->u.stSubmitRptErr.bUserDataHeaderInd, ucFo);
            break;

        default:
            AT_NORM_LOG("At_SendMsgFoAttr: invalid pdu type.");
            break;
    }
    return;
}


TAF_VOID  At_PrintCsmsInfo(
    TAF_UINT8                           ucIndex
)
{
    AT_MSG_SERV_STRU                    stMsgServInfo       = {AT_MSG_SERV_STATE_SUPPORT,
                                                               AT_MSG_SERV_STATE_SUPPORT,
                                                               AT_MSG_SERV_STATE_SUPPORT};

    gstAtSendData.usBufLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                     (TAF_CHAR *)pgucAtSndCodeAddr,
                                                     (TAF_CHAR *)(pgucAtSndCodeAddr + gstAtSendData.usBufLen),
                                                     "%d,%d,%d",
                                                     stMsgServInfo.enSmsMT,
                                                     stMsgServInfo.enSmsMO,
                                                     stMsgServInfo.enSmsBM);
    return;
}


TAF_UINT16 At_PrintAsciiAddr(
    MN_MSG_ASCII_ADDR_STRU              *pstAddr,
    TAF_UINT8                           *pDst
)
{
    TAF_UINT16                          usLength            = 0;

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                       (TAF_CHAR *)pDst + usLength,"\"");
    if ((pstAddr->ulLen > 0)
     && (pstAddr->ulLen <= MN_MAX_ASCII_ADDRESS_NUM))
    {
        pstAddr->aucAsciiNum[pstAddr->ulLen] = 0;

        if (MN_MSG_TON_INTERNATIONAL == pstAddr->enNumType)
        {
            usLength += (TAF_UINT16)At_ReadNumTypePara((pDst + usLength), (TAF_UINT8 *)"+");
        }

        usLength += (TAF_UINT16)At_ReadNumTypePara((pDst + usLength), pstAddr->aucAsciiNum);
    }
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                       (TAF_CHAR *)pDst + usLength,"\"");

    return usLength;
}



VOS_UINT32 AT_BcdAddrToAscii(
    MN_MSG_BCD_ADDR_STRU                *pstBcdAddr,
    MN_MSG_ASCII_ADDR_STRU              *pstAsciiAddr
)
{
    VOS_UINT32                          ulRet;

    if ((VOS_NULL_PTR == pstBcdAddr)
     || (VOS_NULL_PTR == pstAsciiAddr))
    {
        AT_WARN_LOG("MN_MSG_BcdAddrToAscii: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    pstAsciiAddr->enNumType = ((pstBcdAddr->addrType >> 4) & 0x07);
    pstAsciiAddr->enNumPlan = (pstBcdAddr->addrType & 0x0f);
    if((pstBcdAddr->aucBcdNum[pstBcdAddr->ucBcdLen - 1] & 0xF0) != 0xF0)
    {
        pstAsciiAddr->ulLen = pstBcdAddr->ucBcdLen * 2;
    }
    else
    {
        pstAsciiAddr->ulLen = (pstBcdAddr->ucBcdLen * 2) - 1;
    }

    if (pstAsciiAddr->ulLen > MN_MAX_ASCII_ADDRESS_NUM)
    {
        AT_WARN_LOG("MN_MSG_BcdAddrToAscii: length of number is invalid.");
        return MN_ERR_INVALIDPARM;
    }

    ulRet = AT_BcdNumberToAscii(pstBcdAddr->aucBcdNum, pstBcdAddr->ucBcdLen, (VOS_CHAR *)pstAsciiAddr->aucAsciiNum);
    if (MN_ERR_NO_ERROR == ulRet)
    {
        return MN_ERR_NO_ERROR;
    }
    else
    {
        return MN_ERR_INVALIDPARM;
    }
}


TAF_UINT16 At_PrintBcdAddr(
    MN_MSG_BCD_ADDR_STRU                *pstBcdAddr,
    TAF_UINT8                           *pDst
)
{
    TAF_UINT16                          usLength            = 0;
    TAF_UINT32                          ulRet;
    MN_MSG_ASCII_ADDR_STRU              stAsciiAddr;


    ulRet = AT_BcdAddrToAscii(pstBcdAddr, &stAsciiAddr);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        AT_WARN_LOG("At_PrintBcdAddr: Fail to convert BCD to ASCII.");
        return 0;
    }

    usLength = At_PrintAsciiAddr(&stAsciiAddr, pDst);
    return usLength;
}


TAF_UINT16  At_PrintAddrType(
    MN_MSG_ASCII_ADDR_STRU              *pstAddr,
    TAF_UINT8                           *pDst
)
{
    TAF_UINT8                           ucAddrType;
    TAF_UINT16                          usLength            = 0;

    ucAddrType  = 0x80;
    ucAddrType |= pstAddr->enNumPlan;
    ucAddrType |= ((pstAddr->enNumType << 4) & 0x70);
    usLength   += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                       (TAF_CHAR *)(pDst + usLength),
                                       "%d",
                                       ucAddrType);

    return usLength;
}


TAF_UINT16  At_PrintMsgFo(
    MN_MSG_TS_DATA_INFO_STRU            *pstTsDataInfo,
    TAF_UINT8                           *pDst
)
{
    TAF_UINT16                          usLength            = 0;
    TAF_UINT8                           ucFo                = 0;

    At_GetMsgFoValue(pstTsDataInfo, &ucFo);
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                       (TAF_CHAR *)pDst + usLength,
                                       "%d",
                                       ucFo);

    return usLength;
}


VOS_UINT32 AT_ChkSmsNumType(
    MN_MSG_TON_ENUM_U8                  enNumType
)
{
    return MN_ERR_NO_ERROR;
}


VOS_UINT32 AT_ChkSmsNumPlan(
    MN_MSG_NPI_ENUM_U8                  enNumPlan
)
{
    return MN_ERR_NO_ERROR;
}


VOS_UINT32  AT_AsciiToBcdCode(
    VOS_CHAR                            cAsciiCode,
    VOS_UINT8                          *pucBcdCode
)
{
    if (VOS_NULL_PTR == pucBcdCode)
    {
        AT_NORM_LOG("AT_AsciiToBcdCode: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    if ((cAsciiCode >= '0')
     && (cAsciiCode <= '9'))
    {
        *pucBcdCode = (VOS_UINT8)(cAsciiCode - '0');
    }
    else if ('*' == cAsciiCode)
    {
        *pucBcdCode = 0x0a;
    }
    else if ('#' == cAsciiCode)
    {
        *pucBcdCode = 0x0b;
    }
    else if (('a' == cAsciiCode)
          || ('b' == cAsciiCode)
          || ('c' == cAsciiCode))
    {
        *pucBcdCode = (VOS_UINT8)((cAsciiCode - 'a') + 0x0c);
    }
    else if (('A' == cAsciiCode)
          || ('B' == cAsciiCode)
          || ('C' == cAsciiCode))
    {
        *pucBcdCode = (VOS_UINT8)((cAsciiCode - 'A') + 0x0c);
    }
    else
    {
        AT_NORM_LOG("AT_AsciiToBcdCode: Parameter of the function is invalid.");
        return MN_ERR_INVALID_ASCII;
    }

    return MN_ERR_NO_ERROR;
}


VOS_UINT32  AT_AsciiNumberToBcd(
    const VOS_CHAR                      *pcAsciiNumber,
    VOS_UINT8                           *pucBcdNumber,
    VOS_UINT8                           *pucBcdLen
)
{
    VOS_UINT8                           ucLoop;
    VOS_UINT8                           ucBcdCode;
    VOS_UINT32                          ulRet;

    if ((TAF_NULL_PTR == pcAsciiNumber)
     || (TAF_NULL_PTR == pucBcdNumber)
     || (TAF_NULL_PTR == pucBcdLen))
    {
        AT_NORM_LOG("AT_AsciiNumberToBcd: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    for (ucLoop = 0; pcAsciiNumber[ucLoop] != '\0'; ucLoop++)
    {
        ulRet = AT_AsciiToBcdCode(pcAsciiNumber[ucLoop], &ucBcdCode);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            return ulRet;
        }

        /*将当前需要填入的空间清0*/
        pucBcdNumber[(ucLoop / 2)] &= ((ucLoop % 2) == 1) ? 0x0F : 0xF0;

        /*将数字填入相应的空间*/
        pucBcdNumber[(ucLoop / 2)] |= (((ucLoop % 2) == 1) ? ((ucBcdCode << 4) & 0xF0) : (ucBcdCode & 0x0F));
    }

    /*如果长度为奇数，则最后一个字符需要填 F */
    if (1 == (ucLoop % 2))
    {
        pucBcdNumber[(ucLoop / 2)] |= 0xF0;
    }

    *pucBcdLen = (ucLoop + 1) / 2;

    return MN_ERR_NO_ERROR;
}


VOS_UINT32  AT_BcdToAsciiCode(
    VOS_UINT8                           ucBcdCode,
    VOS_CHAR                            *pcAsciiCode
)
{
    VOS_CHAR                            cAsciiCode;

    if (TAF_NULL_PTR == pcAsciiCode)
    {
        AT_NORM_LOG("AT_BcdToAsciiCode: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    if (ucBcdCode <= 0x09)
    {
        cAsciiCode = (VOS_CHAR)(ucBcdCode + 0x30);
    }
    else if (0x0A == ucBcdCode)
    {
        cAsciiCode = (VOS_CHAR)(ucBcdCode + 0x20);    /*字符'*'*/
    }
    else if (0x0B == ucBcdCode)
    {
        cAsciiCode = (VOS_CHAR)(ucBcdCode + 0x18);    /*字符'#'*/
    }
    else if ((0x0C == ucBcdCode)
          || (0x0D == ucBcdCode)
          || (0x0E == ucBcdCode))
    {
        cAsciiCode = (VOS_CHAR)(ucBcdCode + 0x55);    /*字符'a', 'b', 'c'*/
    }
    else
    {
        AT_NORM_LOG("AT_BcdToAsciiCode: Parameter of the function is invalid.");
        return MN_ERR_INVALID_BCD;
    }

    *pcAsciiCode = cAsciiCode;

    return MN_ERR_NO_ERROR;
}


VOS_UINT32  AT_BcdNumberToAscii(
    const VOS_UINT8                     *pucBcdNumber,
    VOS_UINT8                           ucBcdLen,
    VOS_CHAR                            *pcAsciiNumber
)
{
    VOS_UINT8                           ucLoop;
    VOS_UINT8                           ucLen;
    VOS_UINT8                           ucBcdCode;
    VOS_UINT32                          ulRet;

    if ((TAF_NULL_PTR == pucBcdNumber)
     || (TAF_NULL_PTR == pcAsciiNumber))
    {
        AT_NORM_LOG("AT_BcdNumberToAscii: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    /*整理号码字符串，去除无效的0XFF数据*/
    while (ucBcdLen > 1)
    {
        if (0xFF == pucBcdNumber[ucBcdLen - 1])
        {
            ucBcdLen--;
        }
        else
        {
            break;
        }
    }

    /*判断pucBcdAddress所指向的字符串的最后一个字节的高位是否为1111，
    如果是，说明号码位数为奇数，否则为偶数*/
    if ((pucBcdNumber[ucBcdLen - 1] & 0xF0) == 0xF0)
    {
        ucLen = (VOS_UINT8)((ucBcdLen * 2) - 1);
    }
    else
    {
        ucLen = (VOS_UINT8)(ucBcdLen * 2);
    }

    /*解析号码*/
    for (ucLoop = 0; ucLoop < ucLen; ucLoop++)
    {
        /*判断当前解码的是奇数位号码还是偶数位号码，从0开始，是偶数*/
        if (1 == (ucLoop % 2))
        {
            /*如果是奇数位号码，则取高4位的值*/
            ucBcdCode = ((pucBcdNumber[(ucLoop / 2)] >> 4) & 0x0F);
        }
        else
        {
            /*如果是偶数位号码，则取低4位的值*/
            ucBcdCode = (pucBcdNumber[(ucLoop / 2)] & 0x0F);
        }

        /*将二进制数字转换成Ascii码形式*/
        ulRet = AT_BcdToAsciiCode(ucBcdCode, &(pcAsciiNumber[ucLoop]));
        if (MN_ERR_NO_ERROR != ulRet)
        {
            return ulRet;
        }
    }

    pcAsciiNumber[ucLoop] = '\0';      /*字符串末尾为0*/

    return MN_ERR_NO_ERROR;
}



TAF_UINT32  At_GetAsciiOrBcdAddr(
    TAF_UINT8                           *pucAddr,
    TAF_UINT16                          usAddrLen,
    TAF_UINT8                           ucAddrType,
    TAF_UINT16                          usNumTypeLen,
    MN_MSG_ASCII_ADDR_STRU              *pstAsciiAddr,
    MN_MSG_BCD_ADDR_STRU                *pstBcdAddr
)
{
    TAF_UINT8                           aucAsciiNum[MN_MAX_ASCII_ADDRESS_NUM+2];   /*array  of ASCII Num*/
    TAF_UINT8                           *pucNum;                                /*指向实际号码（不包括+号）的指针*/
    TAF_UINT32                          ulAsciiAddrLen;
    TAF_UINT32                          ulRet;
    MN_MSG_TON_ENUM_U8                  enNumType;                              /*type of number*/
    MN_MSG_NPI_ENUM_U8                  enNumPlan;                              /*Numbering plan identification*/

    if ((TAF_NULL_PTR == pstAsciiAddr)
     && (TAF_NULL_PTR == pstBcdAddr))
    {
        AT_WARN_LOG("At_GetAsciiOrBcdAddr: output parameter is null. ");
        return AT_ERROR;
    }

    if (TAF_NULL_PTR != pstAsciiAddr)
    {
        PS_MEM_SET(pstAsciiAddr, 0x00, sizeof(MN_MSG_ASCII_ADDR_STRU));
    }

    if (TAF_NULL_PTR != pstBcdAddr)
    {
        PS_MEM_SET(pstBcdAddr, 0x00, sizeof(MN_MSG_BCD_ADDR_STRU));
    }

    if(0 == usAddrLen)
    {
        return AT_OK;
    }

    if(AT_FAILURE == At_CheckNumLen((MN_MAX_ASCII_ADDRESS_NUM + 1), usAddrLen))
    {
        return AT_CMS_OPERATION_NOT_ALLOWED;
    }

    *(pucAddr + usAddrLen) = '\0';

    PS_MEM_SET(aucAsciiNum, 0x00, (MN_MAX_ASCII_ADDRESS_NUM + 2));
    if(AT_SUCCESS != At_SetNumTypePara(aucAsciiNum, (TAF_UINT8 *)pucAddr, usAddrLen))
    {
        return AT_CMS_OPERATION_NOT_ALLOWED;
    }

    /* 设置<toda> */
    if (AT_MSG_INTERNAL_ISDN_ADDR_TYPE == (At_GetCodeType(aucAsciiNum[0])))
    {
        pucNum = (TAF_UINT8 *)(aucAsciiNum + 1);
        if ((0 != usNumTypeLen)
         && (AT_MSG_INTERNAL_ISDN_ADDR_TYPE != ucAddrType))
        {
            return AT_CMS_OPERATION_NOT_ALLOWED;
        }
    }
    else
    {
        pucNum = (TAF_UINT8 *)aucAsciiNum;
    }

    if (0 == usNumTypeLen)
    {
        ucAddrType = (TAF_UINT8)At_GetCodeType(aucAsciiNum[0]);
    }

    ulAsciiAddrLen = VOS_StrLen((TAF_CHAR *)pucNum);
    if (ulAsciiAddrLen > MN_MAX_ASCII_ADDRESS_NUM)
    {
        AT_NORM_LOG("At_GetAsciiOrBcdAddr: invalid address length.");
        return AT_CMS_OPERATION_NOT_ALLOWED;
    }

    At_GetNumTypeFromAddrType(enNumType, ucAddrType);
    At_GetNumPlanFromAddrType(enNumPlan, ucAddrType);
    ulRet = AT_ChkSmsNumPlan(enNumPlan);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        AT_ERR_LOG("At_GetAsciiOrBcdAddr: Numbering plan is invalid");
        return AT_ERROR;
    }
    ulRet = AT_ChkSmsNumType(enNumType);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        AT_ERR_LOG("At_GetAsciiOrBcdAddr: Number type is invalid");
        return AT_ERROR;
    }

    if (TAF_NULL_PTR != pstAsciiAddr)
    {
        pstAsciiAddr->enNumType = enNumType;
        pstAsciiAddr->enNumPlan = enNumPlan;
        pstAsciiAddr->ulLen = ulAsciiAddrLen;
        PS_MEM_CPY(pstAsciiAddr->aucAsciiNum, pucNum, pstAsciiAddr->ulLen);
    }

    if (TAF_NULL_PTR != pstBcdAddr)
    {
        pstBcdAddr->addrType = ucAddrType;
        ulRet = AT_AsciiNumberToBcd((TAF_CHAR *)pucNum,
                                    pstBcdAddr->aucBcdNum,
                                    &pstBcdAddr->ucBcdLen);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            return AT_ERROR;
        }
    }

    return AT_OK;
}


TAF_UINT32  At_PrintListMsg(
    VOS_UINT8                            ucIndex,
    MN_MSG_EVENT_INFO_STRU              *pstEvent,
    MN_MSG_TS_DATA_INFO_STRU            *pstTsDataInfo,
    TAF_UINT8                           *pucDst
)
{
    TAF_UINT16                          usLength = 0;
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    switch (pstTsDataInfo->enTpduType)
    {
        case MN_MSG_TPDU_DELIVER:
            /* +CMGL: <index>,<stat>,<oa/da>,[<alpha>],[<scts>][,<tooa/toda>,<length>]<CR><LF><data>[<CR><LF>*/
            /* <oa> */
            usLength += (TAF_UINT16)At_PrintAsciiAddr(&pstTsDataInfo->u.stDeliver.stOrigAddr,
                                                      (pucDst + usLength));
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pgucAtSndCodeAddr,
                                               (TAF_CHAR *)(pucDst + usLength),
                                               ",");
            /* <alpha> 不报 */
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pgucAtSndCodeAddr,
                                               (TAF_CHAR *)(pucDst + usLength),
                                               ",");

            /* <scts> */
            usLength += (TAF_UINT16)At_SmsPrintScts(&pstTsDataInfo->u.stDeliver.stTimeStamp,
                                                    (pucDst + usLength));
            if (AT_CSDH_SHOW_TYPE == pstSmsCtx->ucCsdhType)
            {
                usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                                   (TAF_CHAR *)(pucDst + usLength),
                                                   ",");

                /* <tooa> */
                usLength += (TAF_UINT16)At_PrintAddrType(&pstTsDataInfo->u.stDeliver.stOrigAddr,
                                                         (pucDst + usLength));


                /* <length> */
                usLength += AT_PrintSmsLength(pstTsDataInfo->u.stDeliver.stDcs.enMsgCoding,
                                              pstTsDataInfo->u.stDeliver.stUserData.ulLen,
                                              (pucDst + usLength));
            }

            /* <data> 有可能得到是UCS2，需仔细处理*/
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pucDst,
                                               (TAF_CHAR *)(pucDst + usLength),
                                               "%s",
                                               gaucAtCrLf);

            usLength += (TAF_UINT16)At_PrintReportData(AT_CMD_MAX_LEN,
                                                       (TAF_INT8 *)pucDst,
                                                       pstTsDataInfo->u.stDeliver.stDcs.enMsgCoding,
                                                       (pucDst + usLength),
                                                       pstTsDataInfo->u.stDeliver.stUserData.aucOrgData,
                                                       (TAF_UINT16)pstTsDataInfo->u.stDeliver.stUserData.ulLen);

            break;
        case MN_MSG_TPDU_SUBMIT:
            /* +CMGL: <index>,<stat>,<oa/da>,[<alpha>],[<scts>][,<tooa/toda>,<length>]<CR><LF><data>[<CR><LF>*/
            /* <da> */
            usLength += At_PrintAsciiAddr(&pstTsDataInfo->u.stSubmit.stDestAddr,
                                          (TAF_UINT8 *)(pucDst + usLength));
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pgucAtSndCodeAddr,
                                               (TAF_CHAR *)(pucDst + usLength),
                                               ",");

            /* <alpha> 不报 */
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pgucAtSndCodeAddr,
                                               (TAF_CHAR *)(pucDst + usLength),
                                               ",");

            if (AT_CSDH_SHOW_TYPE == pstSmsCtx->ucCsdhType)
            {
                usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                                   (TAF_CHAR *)(pucDst + usLength),
                                                   ",");

                /* <toda> */
                usLength += At_PrintAddrType(&pstTsDataInfo->u.stSubmit.stDestAddr,
                                             (pucDst + usLength));

                /* <length> */
                usLength += AT_PrintSmsLength(pstTsDataInfo->u.stDeliver.stDcs.enMsgCoding,
                                              pstTsDataInfo->u.stSubmit.stUserData.ulLen,
                                              (pucDst + usLength));

            }

            /* <data> 有可能得到是UCS2，需仔细处理*/
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pucDst,
                                               (TAF_CHAR *)(pucDst + usLength),
                                               "%s",
                                               gaucAtCrLf);

            usLength += (TAF_UINT16)At_PrintReportData(AT_CMD_MAX_LEN,
                                                       (TAF_INT8 *)pucDst,
                                                       pstTsDataInfo->u.stSubmit.stDcs.enMsgCoding,
                                                       (pucDst + usLength),
                                                       pstTsDataInfo->u.stSubmit.stUserData.aucOrgData,
                                                       (TAF_UINT16)pstTsDataInfo->u.stSubmit.stUserData.ulLen);

            break;
        case MN_MSG_TPDU_COMMAND:
            /*+CMGL: <index>,<stat>,<fo>,<ct>[<CR><LF>*/
            /*<fo>*/
            usLength += At_PrintMsgFo(pstTsDataInfo, (pucDst + usLength));
            /* <ct> */
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pucDst,
                                               (TAF_CHAR *)(pucDst + usLength),
                                               ",%d",
                                               pstTsDataInfo->u.stCommand.enCmdType);
            break;
        case MN_MSG_TPDU_STARPT:
            /*
               +CMGL: <index>,<stat>,<fo>,<mr>,
                      [<ra>],[<tora>],<scts>,<dt>,<st>
                      [<CR><LF>
            */
            /*<fo>*/
            usLength += (TAF_UINT16)At_PrintMsgFo(pstTsDataInfo, (pucDst + usLength));
            /*<mr>*/
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pgucAtSndCodeAddr,
                                               (TAF_CHAR *)(pucDst + usLength),
                                               ",%d,",
                                               pstTsDataInfo->u.stStaRpt.ucMr);

            /*<ra>*/
            usLength += (TAF_UINT16)At_PrintAsciiAddr(&pstTsDataInfo->u.stStaRpt.stRecipientAddr,
                                                      (pucDst + usLength));
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pgucAtSndCodeAddr,
                                               (TAF_CHAR *)(pucDst + usLength),
                                               ",");

            /*<tora>*/
            usLength += (TAF_UINT16)At_PrintAddrType(&pstTsDataInfo->u.stStaRpt.stRecipientAddr,
                                                     (pucDst + usLength));
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pgucAtSndCodeAddr,
                                               (TAF_CHAR *)(pucDst + usLength),
                                               ",");

            /* <scts> */
            usLength += (TAF_UINT16)At_SmsPrintScts(&pstTsDataInfo->u.stStaRpt.stTimeStamp,
                                                    (pucDst + usLength));
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pgucAtSndCodeAddr,
                                               (TAF_CHAR *)(pucDst + usLength),
                                               ",");

             /* <dt> */
             usLength += (TAF_UINT16)At_SmsPrintScts(&pstTsDataInfo->u.stStaRpt.stDischargeTime,
                                                     (pucDst + usLength));

             /*<st>*/
             usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                (TAF_CHAR *)pgucAtSndCodeAddr,
                                                (TAF_CHAR *)(pucDst + usLength),
                                                ",%d",
                                                pstTsDataInfo->u.stStaRpt.enStatus);
            break;
        default:
            break;
    }

    return usLength;
}


TAF_VOID At_GetCpmsMemStatus(
    VOS_UINT8                           ucIndex,
    MN_MSG_MEM_STORE_ENUM_U8            enMemType,
    TAF_UINT32                          *pulTotalRec,
    TAF_UINT32                          *pulUsedRec
)
{
    MN_MSG_STORAGE_LIST_EVT_INFO_STRU   *pstStorageList;
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    if (MN_MSG_MEM_STORE_SIM == enMemType)
    {
        pstStorageList = &(pstSmsCtx->stCpmsInfo.stUsimStorage);
    }
    else if (MN_MSG_MEM_STORE_NV == enMemType)
    {
        pstStorageList = &(pstSmsCtx->stCpmsInfo.stNvimStorage);
    }
    else/*无存储设备*/
    {
        *pulUsedRec = 0;
        *pulTotalRec = 0;
        return;
    }

    *pulTotalRec = pstStorageList->ulTotalRec;
    *pulUsedRec = pstStorageList->ulUsedRec;

    return;
}


TAF_VOID At_PrintSetCpmsRsp(
    TAF_UINT8                           ucIndex
)
{
    TAF_UINT16                          usLength            = 0;
    TAF_UINT32                          ulTotalRec;                             /*sms capacity of NVIM or USIM*/
    TAF_UINT32                          ulUsedRec;                              /*used records including all status*/
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                       (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s: ",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    /*<used1>,<total1>,<used2>,<total2>,<used3>,<total3>*/
    At_GetCpmsMemStatus(ucIndex, pstSmsCtx->stCpmsInfo.enMemReadorDelete, &ulTotalRec, &ulUsedRec);
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                       (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%d,%d,",
                                       ulUsedRec,
                                       ulTotalRec);

    At_GetCpmsMemStatus(ucIndex, pstSmsCtx->stCpmsInfo.enMemSendorWrite, &ulTotalRec, &ulUsedRec);
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                       (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%d,%d,",
                                       ulUsedRec,
                                       ulTotalRec);

    At_GetCpmsMemStatus(ucIndex, pstSmsCtx->stCpmsInfo.stRcvPath.enSmMemStore, &ulTotalRec, &ulUsedRec);
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                       (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%d,%d",
                                       ulUsedRec,
                                       ulTotalRec);

    gstAtSendData.usBufLen = usLength;
    At_FormatResultData(ucIndex, AT_OK);
    return;
}


TAF_UINT8 *At_GetCpmsMemTypeStr(
    MN_MSG_MEM_STORE_ENUM_U8            enMemType
)
{
    TAF_UINT32                          ulMemType;

    if (MN_MSG_MEM_STORE_SIM == enMemType)
    {
        ulMemType = AT_STRING_SM;
    }
    else if (MN_MSG_MEM_STORE_NV == enMemType)
    {
        ulMemType = AT_STRING_ME;
    }
    else
    {
        ulMemType = AT_STRING_BUTT;
    }
    return gastAtStringTab[ulMemType].pucText;
}


VOS_VOID At_PrintGetCpmsRsp(
    VOS_UINT8                           ucIndex
)
{
    VOS_UINT16                          usLength            = 0;
    VOS_UINT32                          ulTotalRec;                             /*sms capacity of NVIM or USIM*/
    VOS_UINT32                          ulUsedRec;                              /*used records including all status*/
    VOS_UINT8                          *pucMemTypeStr       = VOS_NULL_PTR;
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx           = VOS_NULL_PTR;

    ulTotalRec = 0;
    ulUsedRec  = 0;
    pstSmsCtx  = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s: ",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    /*<used1>,<total1>,<used2>,<total2>,<used3>,<total3>*/
    pucMemTypeStr = At_GetCpmsMemTypeStr(pstSmsCtx->stCpmsInfo.enMemReadorDelete);
    At_GetCpmsMemStatus(ucIndex, pstSmsCtx->stCpmsInfo.enMemReadorDelete, &ulTotalRec, &ulUsedRec);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s,%d,%d,",
                                       pucMemTypeStr,
                                       ulUsedRec,
                                       ulTotalRec);

    pucMemTypeStr = At_GetCpmsMemTypeStr(pstSmsCtx->stCpmsInfo.enMemSendorWrite);
    At_GetCpmsMemStatus(ucIndex, pstSmsCtx->stCpmsInfo.enMemSendorWrite, &ulTotalRec, &ulUsedRec);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s,%d,%d,",
                                       pucMemTypeStr,
                                       ulUsedRec,
                                       ulTotalRec);

    pucMemTypeStr = At_GetCpmsMemTypeStr(pstSmsCtx->stCpmsInfo.stRcvPath.enSmMemStore);
    At_GetCpmsMemStatus(ucIndex, pstSmsCtx->stCpmsInfo.stRcvPath.enSmMemStore, &ulTotalRec, &ulUsedRec);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s,%d,%d",
                                       pucMemTypeStr,
                                       ulUsedRec,
                                       ulTotalRec);

    gstAtSendData.usBufLen = usLength;
    At_FormatResultData(ucIndex, AT_OK);

    return;
}


TAF_VOID AT_PrintTimeZone(
    TAF_INT8                            cTimezone,
    TAF_UINT8                           *pucDst,
    TAF_UINT16                          *pusLength
)
{
    TAF_UINT8                           ucTimeZone;
    TAF_UINT16                          usLength;

    if (cTimezone < 0)
    {
        usLength = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pucDst,
                                           "-");
        ucTimeZone  = (TAF_UINT8)(cTimezone * (-1));
    }
    else
    {
        usLength = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pucDst,
                                           "+");
        ucTimeZone  = (TAF_UINT8)cTimezone;
    }

    if (ucTimeZone > MN_MSG_MAX_TIMEZONE_VALUE)
    {
        AT_WARN_LOG("AT_PrintTimeZone: Time zone is invalid.");
        ucTimeZone = 0;
    }

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                       (TAF_CHAR *)(pucDst + usLength),
                                       "%d%d\"",
                                       (0x0f & (ucTimeZone / 10)),
                                       (ucTimeZone % 10));

    *pusLength = usLength;

    return;
}


TAF_UINT32 At_SmsPrintScts(
    const MN_MSG_TIMESTAMP_STRU         *pstTimeStamp,
    TAF_UINT8                           *pDst
)
{
    TAF_UINT16                          usLength;
    TAF_UINT16                          usTimeZoneLength;
    MN_MSG_DATE_INVALID_TYPE_ENUM_UINT8 ucDateInvalidType;
    TAF_UINT32                          ulRet;

    ulRet = MN_MSG_ChkDate(pstTimeStamp, &ucDateInvalidType);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        AT_WARN_LOG("At_SmsPrintScts: Date is invalid.");
    }

    /* "yy/MM/dd,hh:mm:ss±zz" */
    if (0 == (MN_MSG_DATE_INVALID_YEAR & ucDateInvalidType))
    {
        usLength = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pDst,
                                           "\"%d%d/",
                                           ((pstTimeStamp->ucYear >> 4) & 0x0f),
                                           (pstTimeStamp->ucYear & 0x0f));
    }
    else
    {
        usLength = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pDst,
                                           "\"00/");
    }

    /* MM */
    if (0 == (MN_MSG_DATE_INVALID_MONTH & ucDateInvalidType))
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pDst + usLength,
                                           "%d%d/",
                                           ((pstTimeStamp->ucMonth>> 4) & 0x0f),
                                           (pstTimeStamp->ucMonth & 0x0f));
    }
    else
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pDst + usLength,
                                           "01/");
    }

    /* dd */
    if (0 == (MN_MSG_DATE_INVALID_DAY & ucDateInvalidType))
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pDst + usLength,
                                           "%d%d,",
                                           ((pstTimeStamp->ucDay >> 4) & 0x0f),
                                           (pstTimeStamp->ucDay & 0x0f));
    }
    else
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pDst + usLength,
                                           "01,");
    }

    /* hh */
    if (0 == (MN_MSG_DATE_INVALID_HOUR & ucDateInvalidType))
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pDst + usLength,
                                           "%d%d:",
                                           ((pstTimeStamp->ucHour >> 4) & 0x0f),
                                           (pstTimeStamp->ucHour & 0x0f));
    }
    else
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pDst + usLength,
                                           "00:");
    }

    /* mm */
    if (0 == (MN_MSG_DATE_INVALID_MINUTE & ucDateInvalidType))
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pDst + usLength,
                                           "%d%d:",
                                           ((pstTimeStamp->ucMinute >> 4) & 0x0f),
                                           (pstTimeStamp->ucMinute & 0x0f));
    }
    else
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pDst + usLength,
                                           "00:");
    }

    /* ss */
    if (0 == (MN_MSG_DATE_INVALID_SECOND & ucDateInvalidType))
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pDst + usLength,
                                           "%d%d",
                                           ((pstTimeStamp->ucSecond >> 4) & 0x0f),
                                           (pstTimeStamp->ucSecond & 0x0f));
    }
    else
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pDst + usLength,
                                           "00");
    }

    /* ±zz */
    AT_PrintTimeZone(pstTimeStamp->cTimezone,
                     (pDst + usLength),
                     &usTimeZoneLength);
    usLength += usTimeZoneLength;

    return usLength;
}


TAF_UINT16 At_MsgPrintVp(
    MN_MSG_VALID_PERIOD_STRU            *pstValidPeriod,
    TAF_UINT8 *pDst
)
{
    TAF_UINT16 usLength = 0;

    switch (pstValidPeriod->enValidPeriod)
    {
        case MN_MSG_VALID_PERIOD_RELATIVE:
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pgucAtSndCodeAddr,
                                               (TAF_CHAR *)pDst + usLength,
                                               "%d",
                                               pstValidPeriod->u.ucOtherTime);
            break;
        case MN_MSG_VALID_PERIOD_ABSOLUTE:
            usLength += (TAF_UINT16)At_SmsPrintScts(&pstValidPeriod->u.stAbsoluteTime, pDst);
            break;
        default:
            break;
    }
    return usLength;
}


TAF_UINT32 At_SmsPrintState(
    AT_CMGF_MSG_FORMAT_ENUM_U8          enSmsFormat,
    MN_MSG_STATUS_TYPE_ENUM_U8          enStatus,
    TAF_UINT8                           *pDst
)
{
    TAF_UINT16 usLength = 0;

    if(AT_CMGF_MSG_FORMAT_TEXT == enSmsFormat)    /* TEXT */
    {
        switch(enStatus)
        {
        case MN_MSG_STATUS_MT_NOT_READ:
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pDst + usLength,"%s",gastAtStringTab[AT_STRING_REC_UNREAD_TEXT].pucText);
            break;

        case MN_MSG_STATUS_MT_READ:
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pDst + usLength,"%s",gastAtStringTab[AT_STRING_REC_READ_TEXT].pucText);
            break;

        case MN_MSG_STATUS_MO_NOT_SENT:
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pDst + usLength,"%s",gastAtStringTab[AT_STRING_STO_UNSENT_TEXT].pucText);
            break;

        case MN_MSG_STATUS_MO_SENT:
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pDst + usLength,"%s",gastAtStringTab[AT_STRING_STO_SENT_TEXT].pucText);
            break;

        case MN_MSG_STATUS_NONE:
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pDst + usLength,"%s",gastAtStringTab[AT_STRING_ALL_TEXT].pucText);
            break;

        default:
            return 0;
        }
    }
    else        /* PDU */
    {
        switch(enStatus)
        {
        case MN_MSG_STATUS_MT_NOT_READ:
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pDst + usLength,"%s",gastAtStringTab[AT_STRING_REC_UNREAD_PDU].pucText);
            break;

        case MN_MSG_STATUS_MT_READ:
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pDst + usLength,"%s",gastAtStringTab[AT_STRING_REC_READ_PDU].pucText);
            break;

        case MN_MSG_STATUS_MO_NOT_SENT:
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pDst + usLength,"%s",gastAtStringTab[AT_STRING_STO_UNSENT_PDU].pucText);
            break;

        case MN_MSG_STATUS_MO_SENT:
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pDst + usLength,"%s",gastAtStringTab[AT_STRING_STO_SENT_PDU].pucText);
            break;

        case MN_MSG_STATUS_NONE:
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pDst + usLength,"%s",gastAtStringTab[AT_STRING_ALL_PDU].pucText);
            break;

        default:
            return 0;
        }
    }

    return usLength;
}


TAF_UINT32  At_GetScaFromInputStr(
    const TAF_UINT8                     *pucAddr,
    MN_MSG_BCD_ADDR_STRU                *pstBcdAddr,
    TAF_UINT32                          *pulLen
)
{
    TAF_UINT32                          ulRet;
    MN_MSG_ASCII_ADDR_STRU              stAsciiAddr;

    ulRet = MN_MSG_DecodeAddress(pucAddr, TAF_TRUE, &stAsciiAddr, pulLen);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        return ulRet;
    }

    pstBcdAddr->addrType = 0x80;
    pstBcdAddr->addrType |= stAsciiAddr.enNumPlan;
    pstBcdAddr->addrType |= ((stAsciiAddr.enNumType << 4) & 0x70);

    ulRet = AT_AsciiNumberToBcd((TAF_CHAR *)stAsciiAddr.aucAsciiNum, pstBcdAddr->aucBcdNum, &pstBcdAddr->ucBcdLen);

    return ulRet;
}


TAF_UINT32 At_MsgDeleteCmdProc(
    TAF_UINT8                           ucIndex,
    MN_OPERATION_ID_T                   opId,
    MN_MSG_DELETE_PARAM_STRU            stDelete,
    TAF_UINT32                          ulDeleteTypes
)
{
    if (gastAtClientTab[ucIndex].AtSmsData.ucMsgDeleteTypes & AT_MSG_DELETE_SINGLE)
    {
        stDelete.enDeleteType = MN_MSG_DELETE_SINGLE;
        if (MN_ERR_NO_ERROR != MN_MSG_Delete(gastAtClientTab[ucIndex].usClientId, opId, &stDelete))
        {
            return AT_ERROR;
        }
        else
        {
            return AT_OK;
        }
    }

    if (gastAtClientTab[ucIndex].AtSmsData.ucMsgDeleteTypes & AT_MSG_DELETE_READ)
    {
        stDelete.enDeleteType = MN_MSG_DELETE_READ;
        if (MN_ERR_NO_ERROR != MN_MSG_Delete(gastAtClientTab[ucIndex].usClientId, opId, &stDelete))
        {
            return AT_ERROR;
        }
        else
        {
            return AT_OK;
        }
    }

    if (gastAtClientTab[ucIndex].AtSmsData.ucMsgDeleteTypes & AT_MSG_DELETE_SENT)
    {
        stDelete.enDeleteType = MN_MSG_DELETE_SENT;
        if (MN_ERR_NO_ERROR != MN_MSG_Delete(gastAtClientTab[ucIndex].usClientId, opId, &stDelete))
        {
            return AT_ERROR;
        }
        else
        {
            return AT_OK;
        }
    }

    if (gastAtClientTab[ucIndex].AtSmsData.ucMsgDeleteTypes & AT_MSG_DELETE_UNSENT)
    {
        stDelete.enDeleteType = MN_MSG_DELETE_NOT_SENT;
        if (MN_ERR_NO_ERROR != MN_MSG_Delete(gastAtClientTab[ucIndex].usClientId, opId, &stDelete))
        {
            return AT_ERROR;
        }
        else
        {
            return AT_OK;
        }
    }

    if (gastAtClientTab[ucIndex].AtSmsData.ucMsgDeleteTypes & AT_MSG_DELETE_ALL)
    {
        stDelete.enDeleteType = MN_MSG_DELETE_ALL;
        if (MN_ERR_NO_ERROR != MN_MSG_Delete(gastAtClientTab[ucIndex].usClientId, opId, &stDelete))
        {
            return AT_ERROR;
        }
        else
        {
            return AT_OK;
        }
    }

    return AT_ERROR;
}


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

