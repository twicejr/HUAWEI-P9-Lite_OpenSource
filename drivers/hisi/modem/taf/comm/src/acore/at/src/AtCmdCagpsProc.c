

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "AtCmdCagpsProc.h"
#include "AtEventReport.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_AGPS))

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 -e960 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_AT_CMDCAGPSPROC_C
/*lint +e767 +e960 修改人:罗建 107747;检视人:sunshaohua*/


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

AT_CAGPS_CMD_NAME_TLB_STRU  g_astAtCagpsCmdNameTlb[] =
{
    {ID_XPDS_AT_GPS_TIME_INFO_IND,         0,             "^CAGPSTIMEINFO"},
    {ID_XPDS_AT_GPS_REFLOC_INFO_CNF,       0,             "^CAGPSREFLOCINFO"},
    {ID_XPDS_AT_GPS_PDE_POSI_INFO_IND,     0,             "^CAGPSPDEPOSINFO"},
    {ID_XPDS_AT_GPS_NI_SESSION_IND,        0,             "^CAGPSNIREQ"},
    {ID_XPDS_AT_GPS_START_REQ,             0,             "^CAGPSSTARTREQ"},
    {ID_XPDS_AT_GPS_CANCEL_IND,            0,             "^CAGPSCANCELIND"},
    {ID_XPDS_AT_GPS_ACQ_ASSIST_DATA_IND,   0,             "^CAGPSACQASSISTINFO"},
    {ID_XPDS_AT_GPS_ABORT_IND,             0,             "^CAGPSABORT"},
    {ID_XPDS_AT_GPS_ION_INFO_IND,          0,             "^CAGPSIONINFO"},
    {ID_XPDS_AT_GPS_EPH_INFO_IND,          0,             "^CAGPSEPHINFO"},
    {ID_XPDS_AT_GPS_DEL_ASSIST_DATA_IND,   0,             "^CAGPSDELASSISTDATAIND"},

    {ID_XPDS_AT_GPS_ALM_INFO_IND,          0,             "^CAGPSALMINFO"},

    {ID_XPDS_AT_GPS_NI_CP_START,           0,             "^CAGPSNICPSTART"},
    {ID_XPDS_AT_GPS_NI_CP_STOP,            0,             "^CAGPSNICPSTOP"},
    {ID_XPDS_AT_GPS_UTS_TEST_START_REQ,    0,             "^CGPSCONTROLSTART"},
    {ID_XPDS_AT_GPS_UTS_TEST_STOP_REQ,     0,             "^CGPSCONTROLSTOP"},

    {ID_XPDS_AT_UTS_GPS_POS_INFO_IND,      0,             "^UTSGPSPOSINFO"},
    {ID_XPDS_AT_GPS_OM_TEST_START_REQ,     0,             "^CGPSTESTSTART"},
    {ID_XPDS_AT_GPS_OM_TEST_STOP_REQ,      0,             "^CGPSTESTSTOP"},
};

AT_CAGPS_CMD_OPT_TLB_STRU  g_astAtCagpsCmdOptTbl[] =
{
    {ID_XPDS_AT_GPS_START_CNF,             AT_CMD_CAGPSSTART_SET},
    {ID_XPDS_AT_GPS_CFG_MPC_ADDR_CNF,      AT_CMD_CAGPSCFGMPCADDR_SET},
    {ID_XPDS_AT_GPS_CFG_PDE_ADDR_CNF,      AT_CMD_CAGPSCFGPDEADDR_SET},
    {ID_XPDS_AT_GPS_CFG_MODE_CNF,          AT_CMD_CAGPSCFGPOSMODE_SET},
    {ID_XPDS_AT_GPS_STOP_CNF,              AT_CMD_CAGPSSTOP_SET},
};

/*****************************************************************************
  3 函数实现
*****************************************************************************/


/*****************************************************************************
 函 数 名  : At_SetAgpsDataCallStatus
 功能描述  : ^CAGPSDATACALLSTATUS
 输入参数  : ucIndex - 端口索引
 输出参数  : 无
 返 回 值  : AT_XXX
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月11日
    作    者   : zhuli
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 At_SetAgpsDataCallStatus(VOS_UINT8 ucIndex)
{
    AT_XPDS_AP_DATA_CALL_STATUS_IND_STRU                   *pstDataCallInd;
    VOS_UINT32                                              ulMsgLength;

    /* 参数检查 */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* 参数过多 */
    if (gucAtParaIndex > 1)
    {
        return AT_TOO_MANY_PARA;
    }

    if (gastAtParaList[0].ulParaValue >= AT_XPDS_DATA_CALL_STATUS_BUTT)
    {
        return AT_CME_OPERATION_NOT_ALLOWED;
    }

    ulMsgLength = sizeof(AT_XPDS_AP_DATA_CALL_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstDataCallInd = (AT_XPDS_AP_DATA_CALL_STATUS_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_AT, ulMsgLength);

    if (VOS_NULL_PTR == pstDataCallInd )
    {
        return AT_ERROR;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstDataCallInd) + VOS_MSG_HEAD_LENGTH, 0, ulMsgLength);

    pstDataCallInd->stAppCtrl.usClientId = gastAtClientTab[ucIndex].usClientId;
    pstDataCallInd->stAppCtrl.ucOpId     = At_GetOpId();

    pstDataCallInd->enChannelState= gastAtParaList[0].ulParaValue;

    pstDataCallInd->ulSenderPid     = WUEPS_PID_AT;
    pstDataCallInd->ulReceiverPid   = AT_GetDestPid(pstDataCallInd->stAppCtrl.usClientId, I0_UEPS_PID_XPDS);
    pstDataCallInd->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstDataCallInd->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstDataCallInd->ulMsgId         = ID_AT_XPDS_AP_DATA_CALL_STATUS_IND;

    if (VOS_OK == PS_SEND_MSG(WUEPS_PID_AT, pstDataCallInd))
    {
        return AT_OK;
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
 函 数 名  : At_SetAgpsUpBindStatus
 功能描述  : ^CUPBINDSTATUS
 输入参数  : ucIndex - 端口索引
 输出参数  : 无
 返 回 值  : AT_XXX
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月11日
    作    者   : zhuli
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 At_SetAgpsUpBindStatus(
    VOS_UINT8                               ucIndex
)
{
    AT_XPDS_AP_SERVER_BIND_STATUS_IND_STRU                 *pstMsgBindInd;
    VOS_UINT32                                              ulMsgLength;

    /* 参数检查 */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* 参数过多 */
    if (gucAtParaIndex > 2)
    {
        return AT_TOO_MANY_PARA;
    }

    if ((gastAtParaList[0].ulParaValue >= AT_XPDS_SERVER_MODE_BUTT)
        ||(gastAtParaList[1].ulParaValue >= AT_XPDS_SERVER_BIND_STATUS_BUTT))
    {
        return AT_CME_OPERATION_NOT_ALLOWED;
    }

    ulMsgLength = sizeof(AT_XPDS_AP_SERVER_BIND_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsgBindInd = (AT_XPDS_AP_SERVER_BIND_STATUS_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_AT, ulMsgLength);

    if (VOS_NULL_PTR == pstMsgBindInd )
    {
        return AT_ERROR;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstMsgBindInd) + VOS_MSG_HEAD_LENGTH, 0, ulMsgLength);

    pstMsgBindInd->stAppCtrl.usClientId = gastAtClientTab[ucIndex].usClientId;
    pstMsgBindInd->stAppCtrl.ucOpId     = At_GetOpId();

    pstMsgBindInd->enServerMode = gastAtParaList[0].ulParaValue;
    pstMsgBindInd->enBindStatus = gastAtParaList[1].ulParaValue;

    pstMsgBindInd->ulSenderPid     = WUEPS_PID_AT;
    pstMsgBindInd->ulReceiverPid   = AT_GetDestPid(pstMsgBindInd->stAppCtrl.usClientId, I0_UEPS_PID_XPDS);
    pstMsgBindInd->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsgBindInd->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsgBindInd->ulMsgId         = ID_AT_XPDS_AP_SERVER_BIND_STATUS_IND;

    if (VOS_OK == PS_SEND_MSG(WUEPS_PID_AT, pstMsgBindInd))
    {
        return AT_OK;
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
 函 数 名  : At_SetAgpsForwardData
 功能描述  : ^CAGPSFORWARDDATA
 输入参数  : ucIndex - 端口索引
 输出参数  : 无
 返 回 值  : AT_XXX
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月11日
    作    者   : zhuli
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 At_SetAgpsForwardData(
    VOS_UINT8                               ucIndex
)
{
    VOS_UINT32                          ulDataLen;
    AT_XPDS_AP_FORWARD_DATA_IND_STRU   *pstMsgFwdDataInd;
    VOS_UINT32                          ulMsgLength;

    /* 参数检查 */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* 参数过多 */
    if (gucAtParaIndex > 5)
    {
        return AT_TOO_MANY_PARA;
    }

    if ((gastAtParaList[0].ulParaValue >= AT_XPDS_SERVER_MODE_BUTT)
        ||(gastAtParaList[2].ulParaValue > gastAtParaList[1].ulParaValue))
    {
        return AT_CME_OPERATION_NOT_ALLOWED;
    }

    if (1 == (gastAtParaList[3].ulParaValue % 2))
    {
        return AT_CME_OPERATION_NOT_ALLOWED;
    }

    ulDataLen = (gastAtParaList[3].ulParaValue / 2);

    if (ulDataLen >= 4)
    {
        ulMsgLength = sizeof(AT_XPDS_AP_FORWARD_DATA_IND_STRU) + ulDataLen - VOS_MSG_HEAD_LENGTH - 4;
    }
    else
    {
        ulMsgLength = sizeof(AT_XPDS_AP_FORWARD_DATA_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    }

    pstMsgFwdDataInd = (AT_XPDS_AP_FORWARD_DATA_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_AT, ulMsgLength);

    if (VOS_NULL_PTR == pstMsgFwdDataInd )
    {
        return AT_ERROR;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstMsgFwdDataInd) + VOS_MSG_HEAD_LENGTH, 0, ulMsgLength);

    pstMsgFwdDataInd->stAppCtrl.usClientId = gastAtClientTab[ucIndex].usClientId;
    pstMsgFwdDataInd->stAppCtrl.ucOpId     = At_GetOpId();

    pstMsgFwdDataInd->enServerMode    = gastAtParaList[0].ulParaValue;
    pstMsgFwdDataInd->ulTotalNum      = gastAtParaList[1].ulParaValue;
    pstMsgFwdDataInd->ulCurNum        = gastAtParaList[2].ulParaValue;
    pstMsgFwdDataInd->ulDataLen       = ulDataLen;

    if (AT_SUCCESS !=  At_AsciiString2HexSimple(pstMsgFwdDataInd->aucData,
                                                gastAtParaList[4].aucPara,
                                                (VOS_UINT16)gastAtParaList[3].ulParaValue))
    {
        VOS_MemFree(WUEPS_PID_AT, pstMsgFwdDataInd);

        return AT_CME_OPERATION_NOT_ALLOWED;
    }

    pstMsgFwdDataInd->ulSenderPid     = WUEPS_PID_AT;
    pstMsgFwdDataInd->ulReceiverPid   = AT_GetDestPid(pstMsgFwdDataInd->stAppCtrl.usClientId, I0_UEPS_PID_XPDS);
    pstMsgFwdDataInd->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsgFwdDataInd->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsgFwdDataInd->ulMsgId         = ID_AT_XPDS_AP_FORWARD_DATA_IND;

    if (VOS_OK == PS_SEND_MSG(WUEPS_PID_AT, pstMsgFwdDataInd))
    {
        return AT_OK;
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
 函 数 名  : AT_RcvXpdsAgpsDataCallReq
 功能描述  : ID_XPDS_AT_AP_DATA_CALL_REQ 消息处理 ^CAGPSDATACALLREQ
 输入参数  : 消息内容
 输出参数  : 无
 返 回 值  : AT_XXX
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月11日
    作    者   : zhuli
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_RcvXpdsAgpsDataCallReq(
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT8                           ucIndex;
    XPDS_AT_AP_DATA_CALL_REQ_STRU      *pstMsgDataCallReq;

    /* 初始化 */
    pstMsgDataCallReq = (XPDS_AT_AP_DATA_CALL_REQ_STRU *)pstMsg;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstMsgDataCallReq->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvXpdsAgpsDataCallReq: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    gstAtSendData.usBufLen  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pgucAtSndCodeAddr,
                                      (TAF_CHAR *)pgucAtSndCodeAddr,
                                      "%s^CAGPSDATACALLREQ: %d,%d%s",
                                      gaucAtCrLf,
                                      pstMsgDataCallReq->enAgpsMode,
                                      pstMsgDataCallReq->enAgpsOper,
                                      gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvXpdsAgpsServerBindReq
 功能描述  : ID_MTA_AT_AGPS_BINDUPREQ_IND 消息处理 ^CBINDUPREQ
 输入参数  : 消息内容
 输出参数  : 无
 返 回 值  : AT_XXX
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月11日
    作    者   : zhuli
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_RcvXpdsAgpsServerBindReq(
    VOS_VOID                            *pstMsg
)
{
    VOS_UINT8                           ucIndex;
    XPDS_AT_AP_SERVER_BIND_REQ_STRU    *pstMsgBindReq;

    /* 初始化 */
    pstMsgBindReq = (XPDS_AT_AP_SERVER_BIND_REQ_STRU *)pstMsg;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstMsgBindReq->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvXpdsAgpsServerBindReq: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    gstAtSendData.usBufLen  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pgucAtSndCodeAddr,
                                      (TAF_CHAR *)pgucAtSndCodeAddr,
                                      "%s^CAGPSBINDCONN: %d,%d,%08x,%d%s",
                                      gaucAtCrLf,
                                      pstMsgBindReq ->enServerMode,
                                      pstMsgBindReq ->enDataCallCtrl,
                                      pstMsgBindReq ->ulIpAddr,
                                      pstMsgBindReq ->ulPortNum,
                                      gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : AT_RcvXpdsAgpsReverseDataInd
 功能描述  : ID_MTA_AT_AGPS_UPDATA_IND 消息处理 ^CAGPSREVERSEDATA
 输入参数  : 消息内容
 输出参数  : 无
 返 回 值  : AT_XXX
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月11日
    作    者   : zhuli
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_RcvXpdsAgpsReverseDataInd(
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT8                           ucIndex;
    XPDS_AT_AP_REVERSE_DATA_IND_STRU   *pstMsgDataInd;
    VOS_UINT32                          ulCurNum;
    VOS_UINT32                          ulTotalNum;
    VOS_UINT32                          ulOffset;
    VOS_UINT8                          *pucSrc;
    VOS_UINT32                          ulOutputLen;
    VOS_UINT32                          ulRemainLen;
    VOS_UINT16                          usLength;

    /* 初始化 */
    pstMsgDataInd = (XPDS_AT_AP_REVERSE_DATA_IND_STRU *)pstMsg;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstMsgDataInd->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvXpdsAgpsReverseDataInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    ulTotalNum = (pstMsgDataInd->ulDataLen / AT_XPDS_AGPS_DATAUPLEN_MAX);

    if (0 != (pstMsgDataInd->ulDataLen % AT_XPDS_AGPS_DATAUPLEN_MAX))
    {
        ulTotalNum++;
    }

    if (VOS_NULL_WORD <= ulTotalNum)
    {
        AT_WARN_LOG("AT_RcvXpdsAgpsReverseDataInd: Data Len Error.");
        return VOS_ERR;
    }

    ulOffset = 0;

    pucSrc = pstMsgDataInd->aucData;

    ulOutputLen = 0;

    ulRemainLen = pstMsgDataInd->ulDataLen;

    for (ulCurNum = 1; ulCurNum <= ulTotalNum; ulCurNum++)
    {
        if (ulRemainLen <= AT_XPDS_AGPS_DATAUPLEN_MAX)
        {
            ulOutputLen = ulRemainLen;
        }
        else
        {
            ulOutputLen = AT_XPDS_AGPS_DATAUPLEN_MAX;

            ulRemainLen -= AT_XPDS_AGPS_DATAUPLEN_MAX;
        }

        usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (TAF_CHAR *)pgucAtSndCodeAddr,
                                          (TAF_CHAR *)pgucAtSndCodeAddr,
                                          "%s^CAGPSREVERSEDATA: %d,%d,%d,%d,",
                                          gaucAtCrLf,
                                          pstMsgDataInd->enServerMode,
                                          ulTotalNum,
                                          ulCurNum,
                                          ulOutputLen*2);

        /* 将16进制数转换为ASCII码后输入主动命令内容 */
        usLength += (TAF_UINT16)At_HexText2AsciiStringSimple(AT_CMD_MAX_LEN,
                                                            (TAF_INT8 *)pgucAtSndCodeAddr,
                                                            (TAF_UINT8 *)pgucAtSndCodeAddr+usLength,
                                                            ulOutputLen,
                                                            (pucSrc+ulOffset));

        usLength  += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (TAF_CHAR *)pgucAtSndCodeAddr,
                                          (TAF_CHAR *)pgucAtSndCodeAddr+usLength,
                                          "%s",
                                          gaucAtCrLf);

        ulOffset += AT_XPDS_AGPS_DATAUPLEN_MAX;

        At_SendResultData(ucIndex, pgucAtSndCodeAddr, usLength);
    }

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : AT_CagpsSndXpdsReq
 功能描述  : AT发送数据给MTA的借口
 输入参数  : ucIndex - 端口索引
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月16日
    作    者   : g00256031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_CagpsSndXpdsReq(
    VOS_UINT8                           ucIndex,
    AT_XPDS_MSG_TYPE_ENUM_UINT32        enMsgType,
    VOS_UINT32                          ulMsgStructSize
)
{
    VOS_UINT32                          ulDataLen;
    VOS_UINT32                          ulMsgLength;
    AT_XPDS_MSG_STRU                   *pstAtXpdsMsg;

    /* 参数检查 */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 参数过多 */
    if (2 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 字符串长度不正确 */
    if (gastAtParaList[0].ulParaValue != gastAtParaList[1].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 将字符串转换为16进制数组 */
    if (AT_FAILURE == At_AsciiNum2HexString(gastAtParaList[1].aucPara, &gastAtParaList[1].usParaLen))
    {
        AT_ERR_LOG1("AT_CagpsSndXpdsReq: At_AsciiNum2HexString fail.", enMsgType);

        return AT_CME_INCORRECT_PARAMETERS;
    }

    ulDataLen = ulMsgStructSize - VOS_MSG_HEAD_LENGTH - sizeof(VOS_UINT32) - sizeof(AT_APPCTRL_STRU);

    /* 消息内容长度是否正确 */
    if (ulDataLen != gastAtParaList[1].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    ulMsgLength = ulMsgStructSize - VOS_MSG_HEAD_LENGTH;

    pstAtXpdsMsg = (AT_XPDS_MSG_STRU *)PS_ALLOC_MSG(WUEPS_PID_AT, ulMsgLength);

    if (VOS_NULL_PTR == pstAtXpdsMsg )
    {
        return AT_ERROR;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstAtXpdsMsg) + VOS_MSG_HEAD_LENGTH, 0, ulMsgLength);

    pstAtXpdsMsg->stAppCtrl.usClientId = gastAtClientTab[ucIndex].usClientId;
    pstAtXpdsMsg->stAppCtrl.ucOpId     = gastAtClientTab[ucIndex].opId;

    PS_MEM_CPY(((VOS_UINT8 *)pstAtXpdsMsg) + VOS_MSG_HEAD_LENGTH + sizeof(VOS_UINT32) + sizeof(AT_APPCTRL_STRU),
                gastAtParaList[1].aucPara,
                gastAtParaList[1].usParaLen);

    pstAtXpdsMsg->ulSenderPid     = WUEPS_PID_AT;
    pstAtXpdsMsg->ulReceiverPid   = AT_GetDestPid(pstAtXpdsMsg->stAppCtrl.usClientId, I0_UEPS_PID_XPDS);
    pstAtXpdsMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstAtXpdsMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstAtXpdsMsg->ulMsgId         = enMsgType;

    if (VOS_OK == PS_SEND_MSG(WUEPS_PID_AT, pstAtXpdsMsg))
    {
        return AT_OK;
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
 函 数 名  : AT_SetCapsCfgPosMode
 功能描述  : ^CAGPSCFGPOSMODE用于GPS Module向Modem请求设置AGPS工作模式
             ^CAGPSCFGPOSMODE=<data_length>,<data>
 输入参数  : ucIndex - 端口索引
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月16日
    作    者   : g00256031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_SetCagpsCfgPosMode(
    VOS_UINT8                           ucIndex
)
{
    VOS_UINT32                          ulResult;

    ulResult = AT_CagpsSndXpdsReq(ucIndex,
                                 ID_AT_XPDS_GPS_CFG_POSITION_MODE_REQ,
                                 sizeof(AT_XPDS_GPS_CFG_POSITION_MODE_REQ_STRU));

    if (AT_OK == ulResult)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CAGPSCFGPOSMODE_SET;

        return AT_WAIT_ASYNC_RETURN;
    }

    return ulResult;
}

/*****************************************************************************
 函 数 名  : AT_SetCagpsStart
 功能描述  : ^CAGPSSTART用于GPS Module 发送给modem，触发AGPS流程
             ^CAGPSSTART
 输入参数  : ucIndex - 端口索引
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月16日
    作    者   : g00256031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_SetCagpsStart(
    VOS_UINT8                           ucIndex
)
{
    VOS_UINT32                          ulResult;

    ulResult = AT_CagpsSndXpdsReq(ucIndex,
                                 ID_AT_XPDS_GPS_START_REQ,
                                 sizeof(AT_XPDS_GPS_START_REQ_STRU));

    if (AT_OK == ulResult)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CAGPSSTART_SET;

        return AT_WAIT_ASYNC_RETURN;
    }

    return ulResult;
}

/*****************************************************************************
 函 数 名  : AT_SetCagpsStop
 功能描述  : ^CAGPSSTOP用于GPS Module通知Modem停止AGPS流程
             ^CAGPSSTOP
 输入参数  : ucIndex - 端口索引
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月16日
    作    者   : g00256031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_SetCagpsStop(
    VOS_UINT8                           ucIndex
)
{
    AT_XPDS_GPS_STOP_REQ_STRU          *pstMsgStopReq;
    VOS_UINT32                          ulMsgLength;

    /* 参数检查 */
    if (AT_CMD_OPT_SET_CMD_NO_PARA != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    ulMsgLength = sizeof(AT_XPDS_GPS_STOP_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsgStopReq = (AT_XPDS_GPS_STOP_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_AT, ulMsgLength);

    if (VOS_NULL_PTR == pstMsgStopReq )
    {
        return AT_ERROR;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstMsgStopReq) + VOS_MSG_HEAD_LENGTH, 0, ulMsgLength);

    pstMsgStopReq->stAppCtrl.usClientId = gastAtClientTab[ucIndex].usClientId;
    pstMsgStopReq->stAppCtrl.ucOpId     = gastAtClientTab[ucIndex].opId;

    pstMsgStopReq->ulSenderPid     = WUEPS_PID_AT;
    pstMsgStopReq->ulReceiverPid   = AT_GetDestPid(pstMsgStopReq->stAppCtrl.usClientId, I0_UEPS_PID_XPDS);
    pstMsgStopReq->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsgStopReq->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsgStopReq->ulMsgId         = ID_AT_XPDS_GPS_STOP_REQ;

    if (VOS_OK == PS_SEND_MSG(WUEPS_PID_AT, pstMsgStopReq))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CAGPSSTOP_SET;

        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
 函 数 名  : AT_SetCagpsCfgMpcAddr
 功能描述  : ^CAGPSCFGMPCADDR用于GPS 请求设置MPC server地址
             ^CAGPSCFGMPCADDR=<data_length>,<data>
 输入参数  : ucIndex - 端口索引
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月16日
    作    者   : g00256031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_SetCagpsCfgMpcAddr(
    VOS_UINT8                           ucIndex
)
{
    VOS_UINT32                          ulResult;

    ulResult = AT_CagpsSndXpdsReq(ucIndex,
                                 ID_AT_XPDS_GPS_CFG_MPC_ADDR_REQ,
                                 sizeof(AT_XPDS_GPS_CFG_MPC_ADDR_REQ_STRU));

    if (AT_OK == ulResult)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CAGPSCFGMPCADDR_SET;

        return AT_WAIT_ASYNC_RETURN;
    }

    return ulResult;
}

/*****************************************************************************
 函 数 名  : AT_SetCagpsCfgPdeAddr
 功能描述  : ^CAGPSCFGPDEADDR用于GPS 请求设置PDE server地址
             ^CAGPSCFGPDEADDR=<data_length>,<data>
 输入参数  : ucIndex - 端口索引
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月16日
    作    者   : g00256031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_SetCagpsCfgPdeAddr(
    VOS_UINT8                           ucIndex
)
{
    VOS_UINT32                          ulResult;

    ulResult = AT_CagpsSndXpdsReq(ucIndex,
                                 ID_AT_XPDS_GPS_CFG_PDE_ADDR_REQ,
                                 sizeof(AT_XPDS_GPS_CFG_PDE_ADDR_REQ_STRU));

    if (AT_OK == ulResult)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CAGPSCFGPDEADDR_SET;

        return AT_WAIT_ASYNC_RETURN;
    }

    return ulResult;
}

/*****************************************************************************
 函 数 名  : AT_SetCagpsQryRefloc
 功能描述  : ^CAGPSQRYREFLOC用于请求基于CDMA网络的位置信息
             ^CAGPSQRYREFLOC
 输入参数  : ucIndex - 端口索引
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月16日
    作    者   : g00256031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_SetCagpsQryRefloc(
    VOS_UINT8                           ucIndex
)
{
    VOS_UINT32                                              ulMsgLength;
    AT_XPDS_GPS_QRY_REFLOC_INFO_REQ_STRU                   *pstMsgQryRefLoc;

    /* 参数检查 */
    if (AT_CMD_OPT_SET_CMD_NO_PARA != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    ulMsgLength = sizeof(AT_XPDS_GPS_QRY_REFLOC_INFO_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsgQryRefLoc = (AT_XPDS_GPS_QRY_REFLOC_INFO_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_AT, ulMsgLength);

    if (VOS_NULL_PTR == pstMsgQryRefLoc )
    {
        return AT_ERROR;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstMsgQryRefLoc) + VOS_MSG_HEAD_LENGTH, 0, ulMsgLength);

    pstMsgQryRefLoc->stAppCtrl.usClientId = gastAtClientTab[ucIndex].usClientId;
    pstMsgQryRefLoc->stAppCtrl.ucOpId     = gastAtClientTab[ucIndex].opId;

    pstMsgQryRefLoc->ulSenderPid     = WUEPS_PID_AT;
    pstMsgQryRefLoc->ulReceiverPid   = AT_GetDestPid(pstMsgQryRefLoc->stAppCtrl.usClientId, I0_UEPS_PID_XPDS);
    pstMsgQryRefLoc->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsgQryRefLoc->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsgQryRefLoc->ulMsgId         = ID_AT_XPDS_GPS_QRY_REFLOC_INFO_REQ;

    if (VOS_OK == PS_SEND_MSG(WUEPS_PID_AT, pstMsgQryRefLoc))
    {
        return AT_OK;
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
 函 数 名  : AT_SetCagpsQryTime
 功能描述  : ^CAGPSQRYTIME用于GPS Module向Modem请求Modem的同步时间
             ^CAGPSQRYTIME=<data_length>,<data>
 输入参数  : ucIndex - 端口索引
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月17日
    作    者   : d00212987
    修改内容   : AGPS项目新增
*****************************************************************************/
VOS_UINT32 AT_SetCagpsQryTime(
    VOS_UINT8                           ucIndex
)
{
    AT_XPDS_GPS_QRY_TIME_INFO_REQ_STRU                     *pstMsgQryTime;
    VOS_UINT32                                              ulMsgLength;

    /* 参数检查 */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 参数过多 */
    if (2 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 将字符串转换为16进制数组 */
    if (AT_FAILURE == At_AsciiNum2HexString(gastAtParaList[1].aucPara, &gastAtParaList[1].usParaLen))
    {
        AT_ERR_LOG("AT_SetCagpsQryTime: At_AsciiNum2HexString fail.");

        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 消息内容长度是否正确 */
    if (sizeof(VOS_UINT32) != gastAtParaList[1].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 按照方案要求，1:reply time sync info；2:reply time sync info and GPS assist data */
    if ((0 == gastAtParaList[1].aucPara[0])
        || (AT_XPDS_REPLY_SYNC_BUTT <= gastAtParaList[1].aucPara[0]))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    ulMsgLength = sizeof(AT_XPDS_GPS_QRY_TIME_INFO_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsgQryTime = (AT_XPDS_GPS_QRY_TIME_INFO_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_AT, ulMsgLength);

    if (VOS_NULL_PTR == pstMsgQryTime )
    {
        return AT_ERROR;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstMsgQryTime) + VOS_MSG_HEAD_LENGTH, 0, ulMsgLength);

    pstMsgQryTime->stAppCtrl.usClientId = gastAtClientTab[ucIndex].usClientId;
    pstMsgQryTime->stAppCtrl.ucOpId     = gastAtClientTab[ucIndex].opId;

    PS_MEM_CPY(&pstMsgQryTime->enActionType, gastAtParaList[1].aucPara, gastAtParaList[1].usParaLen);

    pstMsgQryTime->ulSenderPid     = WUEPS_PID_AT;
    pstMsgQryTime->ulReceiverPid   = AT_GetDestPid(pstMsgQryTime->stAppCtrl.usClientId, I0_UEPS_PID_XPDS);
    pstMsgQryTime->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsgQryTime->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsgQryTime->ulMsgId         = ID_AT_XPDS_GPS_QRY_TIME_INFO_REQ;

    if (VOS_OK == PS_SEND_MSG(WUEPS_PID_AT, pstMsgQryTime))
    {
        return AT_OK;
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
 函 数 名  : AT_SetCagpsPrmInfo
 功能描述  : ^CAGPSPRMINFO用于GPS Module将计算出来的伪距信息发送给Modem
             ^CAGPSPRMINFO=<data_length>,<data>
 输入参数  : ucIndex - 端口索引
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月16日
    作    者   : g00256031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_SetCagpsPrmInfo(
    VOS_UINT8                           ucIndex
)
{
    return AT_CagpsSndXpdsReq(ucIndex,
                             ID_AT_XPDS_GPS_PRM_INFO_RSP,
                             sizeof(AT_XPDS_GPS_PRM_INFO_RSP_STRU));
}

/*****************************************************************************
 函 数 名  : AT_SetCagpsReplyNiReq
 功能描述  : ^CAGPSREPLYNIREQ用于NI定位中，GPS Module答复Modem是否接受定位请求
             ^CAGPSREPLYNIREQ=<data_length>,<data>
 输入参数  : ucIndex - 端口索引
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月16日
    作    者   : g00256031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_SetCagpsReplyNiReq(
    VOS_UINT8                           ucIndex
)
{
    return AT_CagpsSndXpdsReq(ucIndex,
                             ID_AT_XPDS_GPS_REPLY_NI_REQ,
                             sizeof(AT_XPDS_GPS_REPLY_NI_RSP_STRU));
}

/*****************************************************************************
 函 数 名  : AT_SearchCagpsATCmd
 功能描述  : 查找回复AT命令名
 输入参数  : enMsgType
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月16日
    作    者   : g00256031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_CHAR* AT_SearchCagpsATCmd(
    AT_XPDS_MSG_TYPE_ENUM_UINT32        enMsgType
)
{
    VOS_UINT32                          i;

    for (i = 0; i < sizeof(g_astAtCagpsCmdNameTlb)/sizeof(AT_CAGPS_CMD_NAME_TLB_STRU); i++)
    {
        if (enMsgType == g_astAtCagpsCmdNameTlb[i].enMsgType)
        {
            return g_astAtCagpsCmdNameTlb[i].pcATCmd;
        }
    }

    return "UNKOWN-MSG";
}

/*****************************************************************************
 函 数 名  : At_SetCagpsPosInfo
 功能描述  : ^CAGPSPOSINFO 用于GPS 给moderm发送pos info
             ^CAGPSPOSINFO=<data_length>,<data>
 输入参数  : ucIndex - 端口索引
 输出参数  : 无
 返 回 值  : AT_OK 成功；AT_ERROR 失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月16日
    作    者   : x00314862
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 At_SetCagpsPosInfo(
    VOS_UINT8                           ucIndex
)
{
    if (AT_OK == AT_CagpsSndXpdsReq(ucIndex,
                                   ID_AT_XPDS_GPS_POS_INFO_RSP,
                                   sizeof(AT_XPDS_GPS_POS_INFO_RSP_STRU)))
    {
        return AT_OK;
    }

    return AT_ERROR;
}


/*****************************************************************************
 函 数 名  : AT_RcvXpdsCagpsCnf
 功能描述  : 回复消息处理
 输入参数  : ucIndex - 端口索引
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月16日
    作    者   : g00256031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_RcvXpdsCagpsCnf(
    VOS_VOID                           *pMsg
)
{
    AT_XPDS_MSG_STRU                   *pstRcvMsg       = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulContentLen;
    VOS_UINT16                          usLength        = 0;

    /* 初始化 */
    pstRcvMsg           = (AT_XPDS_MSG_STRU *)pMsg;
    ucIndex             = 0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvXpdsCagpsCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN, (TAF_CHAR *)pgucAtSndCodeAddr, (TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%s%s", gaucAtCrLf, AT_SearchCagpsATCmd(pstRcvMsg->ulMsgId));

    /* 获取消息内容长度 */
    ulContentLen = pstRcvMsg->ulLength - (sizeof(pstRcvMsg->ulMsgId) + sizeof(AT_APPCTRL_STRU));

    if (ulContentLen != 0)
    {
         /* <length>, */
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN, (TAF_CHAR *)pgucAtSndCodeAddr, (TAF_CHAR *)pgucAtSndCodeAddr + usLength,": %d,\"", ulContentLen * 2);

        /* <command>, */
        usLength += (TAF_UINT16)At_HexAlpha2AsciiString(AT_CMD_MAX_LEN, (TAF_INT8 *)pgucAtSndCodeAddr, (TAF_UINT8 *)pgucAtSndCodeAddr + usLength, pstRcvMsg->aucContent, (TAF_UINT16)ulContentLen);

        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN, (TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"\"");
    }

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN, (TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength, "%s", gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, usLength);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_SearchCagpsATCmdOpt
 功能描述  : 查找回复AT命令名操作
 输入参数  : enMsgType
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月16日
    作    者   : g00256031
    修改内容   : 新生成函数
*****************************************************************************/
AT_CMD_CURRENT_OPT_ENUM AT_SearchCagpsATCmdOpt(
    AT_XPDS_MSG_TYPE_ENUM_UINT32        enMsgType
)
{
    VOS_UINT32                          i;

    for (i = 0; i < sizeof(g_astAtCagpsCmdOptTbl)/sizeof(AT_CAGPS_CMD_OPT_TLB_STRU); i++)
    {
        if (enMsgType == g_astAtCagpsCmdOptTbl[i].enMsgType)
        {
            return g_astAtCagpsCmdOptTbl[i].enCmdOpt;
        }
    }

    return AT_CMD_CURRENT_OPT_BUTT;
}

/*****************************************************************************
 函 数 名  : AT_RcvXpdsCagpsRlstCnf
 功能描述  : 回复消息处理
 输入参数  : ucIndex - 端口索引
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月16日
    作    者   : g00256031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_RcvXpdsCagpsRlstCnf(
    VOS_VOID                           *pMsg
)
{
    XPDS_AT_RESULT_CNF_STRU            *pstMsgRsltCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    AT_CMD_CURRENT_OPT_ENUM             enCmdOpt;

    /* 初始化 */
    pstMsgRsltCnf = (XPDS_AT_RESULT_CNF_STRU *)pMsg;
    ulResult      = AT_OK;
    ucIndex       = 0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstMsgRsltCnf->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvXpdsCagpsRlstCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    enCmdOpt = AT_SearchCagpsATCmdOpt(pstMsgRsltCnf->ulMsgId);

    /* 当前AT是否在等待该命令返回 */
    if (enCmdOpt != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvXpdsCagpsRlstCnf : Current Option is not correct.");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = 0;

    if (VOS_OK != pstMsgRsltCnf->enResult)
    {
        ulResult = AT_ERROR;
    }

    /* 输出结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}




/*****************************************************************************
 函 数 名  : AT_RcvXpdsEphInfoInd
 功能描述  : ID_XPDS_AT_GPS_EPH_INFO_IND 消息处理 ^CAGPSEPHINFO
             XPDS_AT_GPS_EPH_INFO_IND_STRU结构体大小为1924字节
             AT中的数据字符串总长度为1924 * 2 = 3848
             XPDS_AT_GPS_EPH_INFO_IND_STRU结构体的大小为60字节，字符串的长度为120
             字符串分为5包数据: 8 + 960 * 4 = 3848
             分包规则:
             第1包: ucSvNum + aucReserved[3]，字节长度4，字符串长度8
             第2包: astEphData[0:7]，  字节长度480，字符串长度960
             第3包: astEphData[8:15]， 字节长度480，字符串长度960
             第4包: astEphData[16:23]，字节长度480，字符串长度960
             第5包: astEphData[24:31]，字节长度480，字符串长度960
 输入参数  : 消息内容
 输出参数  : 无
 返 回 值  : AT_XXX
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月22日
    作    者   : y00174758
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_RcvXpdsEphInfoInd(
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT8                           ucIndex;
    XPDS_AT_GPS_EPH_INFO_IND_STRU      *pstMsgEphInfoInd;
    VOS_UINT16                          usAtCmdLength;
    VOS_UINT32                          ulEphDataStrLen;
    VOS_UINT32                          ulEphDataByteOffset;
    VOS_UINT8                          *pucEphData;
    VOS_UINT8                           ucLoop;

    /* 初始化 */
    pstMsgEphInfoInd = (XPDS_AT_GPS_EPH_INFO_IND_STRU *)pstMsg;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstMsgEphInfoInd->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvXpdsEphInfoInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvXpdsEphInfoInd: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    pucEphData = ((VOS_UINT8 *)(pstMsgEphInfoInd)) + VOS_MSG_HEAD_LENGTH
                                                   + sizeof(VOS_UINT32) + sizeof(AT_APPCTRL_STRU);

    ulEphDataStrLen = AT_AGPS_EPH_INFO_FIRST_SEG_STR_LEN;

    /* 第1包数据 */
    usAtCmdLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            "%s^CAGPSEPHINFO: %d,%d,%d,",
                                            gaucAtCrLf,
                                            AT_AGPS_EPH_INFO_MAX_SEG_NUM,
                                            0,
                                            ulEphDataStrLen);

    /* 第1包数据 */
    /* 将16进制数转换为ASCII码后输入主动命令内容 */
    usAtCmdLength += (TAF_UINT16)At_HexText2AsciiStringSimple(AT_CMD_MAX_LEN,
                                            (TAF_INT8 *)pgucAtSndCodeAddr,
                                            ((TAF_UINT8 *)pgucAtSndCodeAddr) + usAtCmdLength,
                                            ulEphDataStrLen / 2,
                                            pucEphData);

    usAtCmdLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR *)pgucAtSndCodeAddr + usAtCmdLength,
                                            "%s", gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, usAtCmdLength);

    ulEphDataByteOffset = ulEphDataStrLen / 2;

    /* 从第2包到第5包的数据 */
    for (ucLoop = 0; ucLoop < AT_AGPS_EPH_INFO_MAX_SEG_NUM - 1; ucLoop++)
    {
        ulEphDataStrLen = AT_AGPS_EPH_INFO_NOT_FIRST_SEG_STR_LEN;

        usAtCmdLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                (TAF_CHAR *)pgucAtSndCodeAddr,
                                                (TAF_CHAR *)pgucAtSndCodeAddr,
                                                "%s^CAGPSEPHINFO: %d,%d,%d,",
                                                gaucAtCrLf,
                                                AT_AGPS_EPH_INFO_MAX_SEG_NUM,
                                                ucLoop + 1,
                                                ulEphDataStrLen);

        /* 将16进制数转换为ASCII码后输入主动命令内容 */
        usAtCmdLength += (TAF_UINT16)At_HexText2AsciiStringSimple(AT_CMD_MAX_LEN,
                                                (TAF_INT8 *)pgucAtSndCodeAddr,
                                                ((TAF_UINT8 *)pgucAtSndCodeAddr) + usAtCmdLength,
                                                ulEphDataStrLen / 2,
                                                pucEphData + ulEphDataByteOffset);

        usAtCmdLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                (TAF_CHAR *)pgucAtSndCodeAddr,
                                                (TAF_CHAR *)pgucAtSndCodeAddr + usAtCmdLength,
                                                "%s", gaucAtCrLf);

        At_SendResultData(ucIndex, pgucAtSndCodeAddr, usAtCmdLength);

        ulEphDataByteOffset += ulEphDataStrLen / 2;
    }

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : AT_RcvXpdsAlmInfoInd
 功能描述  : ID_XPDS_AT_GPS_ALM_INFO_IND 消息处理 ^CAGPSEPHINFO
             XPDS_AT_GPS_ALM_INFO_IND_STRU结构体大小为900字节
             AT命令中的字符串总长度为900 * 2 = 1800
             XPDS_AT_GPS_ALM_INFO_IND_STRU结构体的大小为28字节，字符串的长度为56
             字符串分为3包数据: 8 + 896 * 2 = 1800
             分包规则:
             第1包: ucSvNum + ucWeekNum + ucToa + ucReserved，字节长度4，字符串长度8
             第2包: astAlmData[0:15]，  字节长度448，字符串长度896
             第3包: astEphData[16:31]， 字节长度448，字符串长度896
 输入参数  : 消息内容
 输出参数  : 无
 返 回 值  : AT_XXX
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月22日
    作    者   : y00174758
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_RcvXpdsAlmInfoInd(
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT8                           ucIndex;
    XPDS_AT_GPS_ALM_INFO_IND_STRU      *pstMsgAlmInfoInd;
    VOS_UINT16                          usAtCmdLength;
    VOS_UINT32                          ulAlmDataStrLen;
    VOS_UINT32                          ulAlmDataByteOffset;
    VOS_UINT8                          *pucAlmData;
    VOS_UINT8                           ucLoop;

    /* 初始化 */
    pstMsgAlmInfoInd = (XPDS_AT_GPS_ALM_INFO_IND_STRU *)pstMsg;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstMsgAlmInfoInd->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvXpdsAlmInfoInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvXpdsAlmInfoInd: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    pucAlmData = ((VOS_UINT8 *)(pstMsgAlmInfoInd)) + VOS_MSG_HEAD_LENGTH
                                                   + sizeof(VOS_UINT32) + sizeof(AT_APPCTRL_STRU);

    ulAlmDataStrLen = AT_AGPS_ALM_INFO_FIRST_SEG_STR_LEN;

    /* 第1包数据 */
    usAtCmdLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            "%s^CAGPSALMINFO: %d,%d,%d,",
                                            gaucAtCrLf,
                                            AT_AGPS_ALM_INFO_MAX_SEG_NUM,
                                            0,
                                            ulAlmDataStrLen);

    /* 第1包数据 */
    /* 将16进制数转换为ASCII码后输入主动命令内容 */
    usAtCmdLength += (TAF_UINT16)At_HexText2AsciiStringSimple(AT_CMD_MAX_LEN,
                                            (TAF_INT8 *)pgucAtSndCodeAddr,
                                            ((TAF_UINT8 *)pgucAtSndCodeAddr) + usAtCmdLength,
                                            ulAlmDataStrLen / 2,
                                            pucAlmData);

    usAtCmdLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR *)pgucAtSndCodeAddr + usAtCmdLength,
                                            "%s", gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, usAtCmdLength);

    ulAlmDataByteOffset = ulAlmDataStrLen / 2;

    /* 从第2包到第3包的数据 */
    for (ucLoop = 0; ucLoop < AT_AGPS_ALM_INFO_MAX_SEG_NUM - 1; ucLoop++)
    {
        ulAlmDataStrLen = AT_AGPS_ALM_INFO_NOT_FIRST_SEG_STR_LEN;

        usAtCmdLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                (TAF_CHAR *)pgucAtSndCodeAddr,
                                                (TAF_CHAR *)pgucAtSndCodeAddr,
                                                "%s^CAGPSALMINFO: %d,%d,%d,",
                                                gaucAtCrLf,
                                                AT_AGPS_ALM_INFO_MAX_SEG_NUM,
                                                ucLoop + 1,
                                                ulAlmDataStrLen);

        /* 将16进制数转换为ASCII码后输入主动命令内容 */
        usAtCmdLength += (TAF_UINT16)At_HexText2AsciiStringSimple(AT_CMD_MAX_LEN,
                                                (TAF_INT8 *)pgucAtSndCodeAddr,
                                                ((TAF_UINT8 *)pgucAtSndCodeAddr) + usAtCmdLength,
                                                ulAlmDataStrLen / 2,
                                                pucAlmData + ulAlmDataByteOffset);

        usAtCmdLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                (TAF_CHAR *)pgucAtSndCodeAddr,
                                                (TAF_CHAR *)pgucAtSndCodeAddr + usAtCmdLength,
                                                "%s", gaucAtCrLf);

        At_SendResultData(ucIndex, pgucAtSndCodeAddr, usAtCmdLength);

        ulAlmDataByteOffset += ulAlmDataStrLen / 2;
    }

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : At_SetCgpsControlStart
 功能描述  : ^CGPSControlStart用于CGPS仪器测试通知GPS开始启动定位
             ^CGPSControlStart=<data_length>,<data>
 输入参数  : ucIndex - 端口索引
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月17日
    作    者   : d00212987
    修改内容   : AGPS项目新增
*****************************************************************************/
VOS_UINT32 At_SetCgpsControlStart(
    VOS_UINT8                           ucIndex
)
{
    AT_XPDS_MSG_STRU                   *pstMsgStr;
    VOS_UINT32                          ulMsgLength;

    /* 参数检查 */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 参数过多 */
    if (2 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 字符串长度不正确 */
    if (gastAtParaList[0].ulParaValue != gastAtParaList[1].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 将字符串转换为16进制数组 */
    if (AT_FAILURE == At_AsciiNum2HexString(gastAtParaList[1].aucPara, &gastAtParaList[1].usParaLen))
    {
        AT_ERR_LOG("At_SetgpsControlStart: At_AsciiNum2HexString fail.");

        return AT_CME_INCORRECT_PARAMETERS;
    }

    if (gastAtParaList[1].usParaLen >= 4)
    {
        ulMsgLength = sizeof(AT_XPDS_MSG_STRU) + gastAtParaList[1].usParaLen - VOS_MSG_HEAD_LENGTH - 4;
    }
    else
    {
        ulMsgLength = sizeof(AT_XPDS_MSG_STRU) - VOS_MSG_HEAD_LENGTH;
    }

    pstMsgStr = (AT_XPDS_MSG_STRU *)PS_ALLOC_MSG(UEPS_PID_XPDS, ulMsgLength);

    if (VOS_NULL_PTR == pstMsgStr )
    {
        return AT_ERROR;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstMsgStr) + VOS_MSG_HEAD_LENGTH, 0, ulMsgLength);

    pstMsgStr->stAppCtrl.usClientId = gastAtClientTab[ucIndex].usClientId;
    pstMsgStr->stAppCtrl.ucOpId     = gastAtClientTab[ucIndex].opId;

    PS_MEM_CPY(pstMsgStr->aucContent, gastAtParaList[1].aucPara, gastAtParaList[1].usParaLen);

    pstMsgStr->ulSenderPid     = WUEPS_PID_AT;
    pstMsgStr->ulReceiverPid   = AT_GetDestPid(pstMsgStr->stAppCtrl.usClientId, I0_UEPS_PID_XPDS);
    pstMsgStr->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsgStr->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsgStr->ulMsgId         = ID_AT_XPDS_UTS_TEST_START_REQ;

    if (VOS_OK == PS_SEND_MSG(WUEPS_PID_AT, pstMsgStr))
    {
        return AT_OK;
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
 函 数 名  : At_SetCgpsControlStop
 功能描述  : ^CGPSControlStop用于CGPS仪器测试通知GPS停止定位
             ^CGPSControlStop=<data_length>,<data>
 输入参数  : ucIndex - 端口索引
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月17日
    作    者   : d00212987
    修改内容   : AGPS项目新增
*****************************************************************************/
VOS_UINT32 At_SetCgpsControlStop(
    VOS_UINT8                           ucIndex
)
{
    AT_XPDS_MSG_STRU                   *pstMsgStr;
    VOS_UINT32                          ulMsgLength;

    /* 参数检查 */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 参数过多 */
    if (2 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 字符串长度不正确 */
    if (gastAtParaList[0].ulParaValue != gastAtParaList[1].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 将字符串转换为16进制数组 */
    if (AT_FAILURE == At_AsciiNum2HexString(gastAtParaList[1].aucPara, &gastAtParaList[1].usParaLen))
    {
        AT_ERR_LOG("At_SetCgpsControlStop: At_AsciiNum2HexString fail.");

        return AT_CME_INCORRECT_PARAMETERS;
    }

    if (gastAtParaList[1].usParaLen >= 4)
    {
        ulMsgLength = sizeof(AT_XPDS_MSG_STRU) + gastAtParaList[1].usParaLen - VOS_MSG_HEAD_LENGTH - 4;
    }
    else
    {
        ulMsgLength = sizeof(AT_XPDS_MSG_STRU) - VOS_MSG_HEAD_LENGTH;
    }

    pstMsgStr = (AT_XPDS_MSG_STRU *)PS_ALLOC_MSG(UEPS_PID_XPDS, ulMsgLength);

    if (VOS_NULL_PTR == pstMsgStr )
    {
        return AT_ERROR;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstMsgStr) + VOS_MSG_HEAD_LENGTH, 0, ulMsgLength);

    pstMsgStr->stAppCtrl.usClientId = gastAtClientTab[ucIndex].usClientId;
    pstMsgStr->stAppCtrl.ucOpId     = gastAtClientTab[ucIndex].opId;

    PS_MEM_CPY(pstMsgStr->aucContent, gastAtParaList[1].aucPara, gastAtParaList[1].usParaLen);

    pstMsgStr->ulSenderPid     = WUEPS_PID_AT;
    pstMsgStr->ulReceiverPid   = AT_GetDestPid(pstMsgStr->stAppCtrl.usClientId, I0_UEPS_PID_XPDS);
    pstMsgStr->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsgStr->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsgStr->ulMsgId         = ID_AT_XPDS_UTS_TEST_STOP_REQ;

    if (VOS_OK == PS_SEND_MSG(WUEPS_PID_AT, pstMsgStr))
    {
        return AT_OK;
    }
    else
    {
        return AT_ERROR;
    }
}

#endif

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

