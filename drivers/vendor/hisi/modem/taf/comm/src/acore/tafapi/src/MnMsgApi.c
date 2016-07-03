

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "product_config.h"
#include  "vos.h"
#include  "MnErrorCode.h"
#include  "MnMsgApi.h"
#include  "ATCmdProc.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
  2 常量定义
*****************************************************************************/
/*lint -e767 -e960 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define THIS_FILE_ID                PS_FILE_ID_MNMSG_API_C
/*lint +e767 +e960 修改人:罗建 107747;检视人:sunshaohua*/

/*****************************************************************************
  3 类型定义
*****************************************************************************/
/*API发送的消息类型和长度用一个二维数组对应起来*/
typedef struct
{
    MN_MSG_MSGTYPE_ENUM_U16             enMsgType;
    VOS_UINT16                          usLen;
}MSG_MSGTYPE_LEN_STRU;

/*****************************************************************************
  4 变量定义
*****************************************************************************/
LOCAL MSG_MSGTYPE_LEN_STRU             f_astMsgTypeLen[] = {
    {MN_MSG_MSGTYPE_SEND_RPDATA_DIRECT ,sizeof(MN_MSG_SEND_PARM_STRU)},
    {MN_MSG_MSGTYPE_SEND_RPDATA_FROMMEM ,sizeof(MN_MSG_SEND_FROMMEM_PARM_STRU)},
    {MN_MSG_MSGTYPE_SEND_RPRPT ,sizeof(MN_MSG_SEND_ACK_PARM_STRU)},
    {MN_MSG_MSGTYPE_WRITE ,sizeof(MN_MSG_WRITE_PARM_STRU)},
    {MN_MSG_MSGTYPE_READ ,sizeof(MN_MSG_READ_PARM_STRU)},
    {MN_MSG_MSGTYPE_LIST ,sizeof(MN_MSG_LIST_PARM_STRU)},
    {MN_MSG_MSGTYPE_DELETE ,sizeof(MN_MSG_DELETE_PARAM_STRU)},
    {MN_MSG_MSGTYPE_DELETE_TEST, sizeof(MN_MSG_LIST_PARM_STRU)},
    {MN_MSG_MSGTYPE_WRITE_SRV_PARA ,sizeof(MN_MSG_WRITE_SRV_PARAM_STRU)},
    {MN_MSG_MSGTYPE_READ_SRV_PARA ,sizeof(MN_MSG_READ_COMM_PARAM_STRU)},
    {MN_MSG_MSGTYPE_DELETE_SRV_PARA ,sizeof(MN_MSG_DELETE_PARAM_STRU)},
    {MN_MSG_MSGTYPE_MODIFY_STATUS ,sizeof(MN_MSG_MODIFY_STATUS_PARM_STRU)},
    {MN_MSG_MSGTYPE_SET_RCVPATH ,sizeof(MN_MSG_SET_RCVMSG_PATH_PARM_STRU)},
    {MN_MSG_MSGTYPE_GET_RCVPATH ,sizeof(MN_MSG_GET_RCVMSG_PATH_PARM_STRU)},
    {MN_MSG_MSGTYPE_GET_STORAGESTATUS ,sizeof(MN_MSG_GET_STORAGE_STATUS_PARM_STRU)},
    {MN_MSG_MSGTYPE_READ_STARPT ,sizeof(MN_MSG_READ_COMM_PARAM_STRU)},
    {MN_MSG_MSGTYPE_DELETE_STARPT ,sizeof(MN_MSG_DELETE_PARAM_STRU)},
    {MN_MSG_MSGTYPE_GET_STARPT_FROMMOMSG ,sizeof(MN_MSG_STARPT_MOMSG_PARM_STRU)},
    {MN_MSG_MSGTYPE_GET_MOMSG_FROMSTARPT ,sizeof(MN_MSG_STARPT_MOMSG_PARM_STRU)},
    {MN_MSG_MSGTYPE_SET_MEMSTATUS ,sizeof(MN_MSG_SET_MEMSTATUS_PARM_STRU)},
    {MN_MSG_MSGTYPE_SET_RELAY_LINK_CTRL, sizeof(MN_MSG_SET_LINK_CTRL_STRU)},
    {MN_MSG_MSGTYPE_GET_RELAY_LINK_CTRL, 0},
    {MN_MSG_MSGTYPE_STUB, sizeof(MN_MSG_STUB_MSG_STRU)},
#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))
    {MN_MSG_MSGTYPE_GET_ALLCBMIDS ,0},
    {MN_MSG_MSGTYPE_ADD_CBMIDS ,    sizeof(TAF_CBA_CBMI_RANGE_LIST_STRU)},
    {MN_MSG_MSGTYPE_DELETE_CBMIDS , sizeof(TAF_CBA_CBMI_RANGE_LIST_STRU)},
    {MN_MSG_MSGTYPE_EMPTY_CBMIDS,0}
#endif
};

LOCAL MN_MSG_TS_DATA_INFO_STRU         f_stMsgDataInfo;

/*****************************************************************************
  5 函数实现
*****************************************************************************/

VOS_UINT32 MSG_SendAppReq(
    MN_MSG_MSGTYPE_ENUM_U16             enMsgType,
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const VOS_VOID                      *pSendParm
)
{
    MN_APP_REQ_MSG_STRU                *pstAppReq;
    VOS_UINT32                          ulLen;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulSendLen;
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulMaxLoop;

    /* 消息类型有效性判断 */
    if ((enMsgType >= MN_MSG_MSGTYPE_MAX)
     || (enMsgType <= MN_APP_MSG_CLASS_MSG))
    {
        AT_WARN_LOG("MSG_SendAppReq:Invalid enMsgType. ");
        return MN_ERR_INVALIDPARM;
    }

    /* 获取消息信息字段长度 */
    ulMaxLoop    = sizeof(f_astMsgTypeLen)/sizeof(MSG_MSGTYPE_LEN_STRU);
    for (ulLoop = 0; ulLoop < ulMaxLoop; ulLoop++)
    {
        if (enMsgType == f_astMsgTypeLen[ulLoop].enMsgType)
        {
            break;
        }
    }

    if (ulLoop == ulMaxLoop)
    {
        return MN_ERR_CLASS_SMS_INTERNAL;
    }

    ulLen = f_astMsgTypeLen[ulLoop].usLen;

    ulSendLen = (ulLen + sizeof(MN_APP_REQ_MSG_STRU)) - (sizeof(VOS_UINT8)*4);

    /* 填写并发送消息 */
    pstAppReq = (MN_APP_REQ_MSG_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_AT,ulSendLen);

    if (VOS_NULL_PTR == pstAppReq)
    {
        AT_WARN_LOG("MSG_SendAppReq:Alloc Msg Failed");
        return MN_ERR_NOMEM;
    }

    pstAppReq->ulSenderCpuId = VOS_LOCAL_CPUID;
    pstAppReq->ulSenderPid = WUEPS_PID_AT;
    pstAppReq->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstAppReq->ulReceiverPid = AT_GetDestPid(clientId, I0_WUEPS_PID_TAF);
    pstAppReq->usMsgName = enMsgType;
    pstAppReq->aucReserve1[0] = 0;
    pstAppReq->aucReserve1[1] = 0;
    pstAppReq->clientId = clientId;
    pstAppReq->opId = opId;
    pstAppReq->aucReserve2[0] = 0;

    if ((ulLen > 0) && (VOS_NULL_PTR != pSendParm))
    {
        PS_MEM_CPY(pstAppReq->aucContent,(VOS_UINT8*)pSendParm,ulLen);
    }
    ulRet = PS_SEND_MSG(WUEPS_PID_AT, pstAppReq);
    if (VOS_OK != ulRet)
    {
        AT_WARN_LOG("MSG_SendAppReq: PS_SEND_MSG fails");
        return MN_ERR_SEND_MSG_ERROR;
    }

    return MN_ERR_NO_ERROR;
}


VOS_UINT32 MN_MSG_ReqStub(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_STUB_MSG_STRU         *pstStubParam
)
{
    VOS_UINT32                          ulRet;

    /*判断输入参数的合法性*/
    if (VOS_NULL_PTR == pstStubParam)
    {
        AT_WARN_LOG("MN_MSG_ReqStub: pstSetParam is Null ");
        return MN_ERR_NULLPTR;
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_STUB,
                           clientId,
                           opId,
                           (VOS_VOID *)pstStubParam);

    return ulRet;
}


VOS_UINT32   MN_MSG_SetLinkCtrl(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_SET_LINK_CTRL_STRU     *pstSetParam
)
{
    VOS_UINT32                          ulRet;

    /*判断输入参数的合法性*/
    if (VOS_NULL_PTR == pstSetParam)
    {
        AT_WARN_LOG("MN_MSG_SetLinkCtrl:pstSetParam is Null ");
        return MN_ERR_NULLPTR;
    }

    if (pstSetParam->enRelayLinkCtrl >= MN_MSG_LINK_CTRL_BUTT)
    {
        AT_WARN_LOG("MN_MSG_SetLinkCtrl:Invalid value");
        return MN_ERR_INVALIDPARM;
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_SET_RELAY_LINK_CTRL,
                           clientId,
                           opId,
                           (VOS_VOID *)pstSetParam);

    return ulRet;

}


VOS_UINT32   MN_MSG_GetLinkCtrl(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId
)
{
    VOS_UINT32                          ulRet;

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_GET_RELAY_LINK_CTRL,
                           clientId,
                           opId,
                           VOS_NULL_PTR);

    return ulRet;
}


VOS_UINT32   MN_MSG_Send(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_SEND_PARM_STRU         *pstSendParm
)
{
    VOS_UINT32                          ulRet;

    /*判断输入参数的合法性*/
    if (VOS_NULL_PTR == pstSendParm)
    {
        AT_WARN_LOG("MN_MSG_Send:pstSendDirectParm is Null ");
        return MN_ERR_NULLPTR;
    }

    if (MN_MSG_SEND_DOMAIN_CS_PREFERRED < pstSendParm->enDomain)
    {
        AT_WARN_LOG("MN_MSG_Send:Invalid enDomain");
        return MN_ERR_CLASS_SMS_NOAVAILDOMAIN;
    }

#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    if (MN_MSG_MEM_STORE_NV < pstSendParm->enMemStore)
#else
    if (MN_MSG_MEM_STORE_SIM < pstSendParm->enMemStore)
#endif
    {
        AT_WARN_LOG("MN_MSG_Send:Invalid enMemStore");
        return MN_ERR_INVALIDPARM;
    }

    /*如果带有SCADDR,24011协议规定,BCD编码最少长度是2,最大长度是11*/
    if (pstSendParm->stMsgInfo.stScAddr.ucBcdLen > 0)
    {
        if ((pstSendParm->stMsgInfo.stScAddr.ucBcdLen < MN_MSG_MIN_BCD_NUM_LEN)
         || (pstSendParm->stMsgInfo.stScAddr.ucBcdLen > MN_MSG_MAX_BCD_NUM_LEN))
        {
            AT_WARN_LOG("MN_MSG_Send:Invalid SC Address");
            return MN_ERR_CLASS_SMS_INVALID_SCADDR;
        }
    }

    /*判断输入TPDU格式的合法性,即解码是否成功*/
    if ((MN_MSG_TPDU_COMMAND != pstSendParm->stMsgInfo.stTsRawData.enTpduType)
     && (MN_MSG_TPDU_SUBMIT != pstSendParm->stMsgInfo.stTsRawData.enTpduType))
    {
        AT_WARN_LOG("MN_MSG_Send:Invalid Tpdu Type");
        return MN_ERR_CLASS_SMS_INVALID_TPDUTYPE;
    }

    PS_MEM_SET(&f_stMsgDataInfo,0X00,sizeof(f_stMsgDataInfo));
    ulRet = MN_MSG_Decode(&pstSendParm->stMsgInfo.stTsRawData,&f_stMsgDataInfo);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        AT_WARN_LOG("MN_MSG_Send:Invalid Tpdu");
        return MN_ERR_CLASS_SMS_INVALID_TPDU;
    }

    if (MN_MSG_TPDU_SUBMIT == pstSendParm->stMsgInfo.stTsRawData.enTpduType)
    {
        if (MN_MSG_TPDU_SUBMIT != f_stMsgDataInfo.enTpduType)
        {
            AT_WARN_LOG("MN_MSG_Send:Conflict TPDU type");
            return MN_ERR_CLASS_SMS_INVALID_TPDUTYPE;
        }

        if (0 == f_stMsgDataInfo.u.stSubmit.stDestAddr.ulLen)
        {
            AT_WARN_LOG("MN_MSG_Send:No DA");
            return MN_ERR_CLASS_SMS_INVALID_DESTADDR;
        }
    }
    else
    {
        if (MN_MSG_TPDU_COMMAND != f_stMsgDataInfo.enTpduType)
        {
            AT_WARN_LOG("MN_MSG_Send:Conflict TPDU type");
            return MN_ERR_CLASS_SMS_INVALID_TPDUTYPE;
        }
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_SEND_RPDATA_DIRECT,
                           clientId,
                           opId,
                           (VOS_VOID *)pstSendParm);

    return ulRet;
}


VOS_UINT32   MN_MSG_SendFromMem(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_SEND_FROMMEM_PARM_STRU *pstSendFromMemParm
)
{
    VOS_UINT32                          ulRet;

    /*判断输入参数的合法性*/
    if (VOS_NULL_PTR == pstSendFromMemParm)
    {
        AT_WARN_LOG("MN_MSG_SendFromMem:pstSendFromMemParm is Null");
        return MN_ERR_NULLPTR;
    }

    if (MN_MSG_SEND_DOMAIN_CS_PREFERRED < pstSendFromMemParm->enDomain)
    {
        AT_WARN_LOG("MN_MSG_SendFromMem:Invalid enDomain");
        return MN_ERR_INVALIDPARM;
    }

#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    if ((MN_MSG_MEM_STORE_SIM != pstSendFromMemParm->enMemStore)
     && (MN_MSG_MEM_STORE_NV != pstSendFromMemParm->enMemStore))
#else
    if (MN_MSG_MEM_STORE_SIM != pstSendFromMemParm->enMemStore)
#endif
    {
        AT_WARN_LOG("MN_MSG_SendFromMem:Invalid enMemStore");
        return MN_ERR_INVALIDPARM;
    }

    if ((pstSendFromMemParm->stDestAddr.ucBcdLen > 0)
     && ((pstSendFromMemParm->stDestAddr.ucBcdLen < MN_MSG_MIN_BCD_NUM_LEN)
      || (pstSendFromMemParm->stDestAddr.ucBcdLen > MN_MSG_MAX_BCD_NUM_LEN)))
    {
        AT_WARN_LOG("MN_MSG_SendFromMem:Invalid Dest Address");
        return MN_ERR_CLASS_SMS_INVALID_DESTADDR;
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_SEND_RPDATA_FROMMEM,
                           clientId,
                           opId,
                           (VOS_VOID *)pstSendFromMemParm);

    return ulRet;
}


VOS_UINT32   MN_MSG_SendAck(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_SEND_ACK_PARM_STRU     *pstAckParm
)
{
    VOS_UINT32                          ulRet;

    /*判断输入参数的合法性*/
    if (VOS_NULL_PTR == pstAckParm)
    {
        AT_WARN_LOG("MN_MSG_SendAck:pstAckParm is Null");
        return MN_ERR_NULLPTR;
    }
    /*必须是Deliver Ack 或Deliver Err*/
    if ((MN_MSG_TPDU_DELIVER_RPT_ACK != pstAckParm->stTsRawData.enTpduType)
     && (MN_MSG_TPDU_DELIVER_RPT_ERR != pstAckParm->stTsRawData.enTpduType))
    {
        AT_WARN_LOG("MN_MSG_SendAck:Invalid Tpdu Type");
        return MN_ERR_CLASS_SMS_INVALID_TPDUTYPE;
    }
    /*判断输入TPDU格式的合法性,即解码是否成功*/
    PS_MEM_SET(&f_stMsgDataInfo,0X00,sizeof(f_stMsgDataInfo));
    ulRet = MN_MSG_Decode(&pstAckParm->stTsRawData,&f_stMsgDataInfo);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        AT_WARN_LOG("MN_MSG_SendAck:Invalid Tpdu");
        return MN_ERR_CLASS_SMS_INVALID_TPDU;
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_SEND_RPRPT,
                           clientId,
                           opId,
                           (VOS_VOID *)pstAckParm);

    return ulRet;
}


VOS_UINT32   MN_MSG_Write(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_WRITE_PARM_STRU        *pstWriteParm
)
{
    VOS_UINT32                          ulRet;

    /*判断输入参数的合法性*/
    if (VOS_NULL_PTR == pstWriteParm)
    {
        AT_WARN_LOG("MN_MSG_Write:pstWriteParm is Null");
        return MN_ERR_NULLPTR;
    }

    if ((MN_MSG_WRITE_MODE_INSERT != pstWriteParm->enWriteMode)
     && (MN_MSG_WRITE_MODE_REPLACE != pstWriteParm->enWriteMode))
    {
        AT_WARN_LOG("MN_MSG_Write:Invalid enWriteMode");
        return MN_ERR_INVALIDPARM;
    }

#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    if ((MN_MSG_MEM_STORE_SIM != pstWriteParm->enMemStore)
     && (MN_MSG_MEM_STORE_NV != pstWriteParm->enMemStore))
#else
    if (MN_MSG_MEM_STORE_SIM != pstWriteParm->enMemStore)
#endif
    {
        AT_WARN_LOG("MN_MSG_Write:Invalid enMemStore");
        return MN_ERR_INVALIDPARM;
    }

    if (pstWriteParm->enStatus >= MN_MSG_STATUS_NONE)
    {
        AT_WARN_LOG("MN_MSG_Write:Invalid enStatus");
        return MN_ERR_INVALIDPARM;
    }

    /*如果有SC ADDR,判断SC ADDR是否合理*/
    if (pstWriteParm->stMsgInfo.stScAddr.ucBcdLen > 0)
    {
        if ((pstWriteParm->stMsgInfo.stScAddr.ucBcdLen < MN_MSG_MIN_BCD_NUM_LEN)
         || (pstWriteParm->stMsgInfo.stScAddr.ucBcdLen > MN_MSG_MAX_BCD_NUM_LEN))
        {
            AT_WARN_LOG("MN_MSG_Send:Invalid SC Address");
            return MN_ERR_CLASS_SMS_INVALID_SCADDR;
        }
    }

    /*判断输入TPDU格式的合法性,即解码是否成功*/
    PS_MEM_SET(&f_stMsgDataInfo,0X00,sizeof(f_stMsgDataInfo));
    ulRet = MN_MSG_Decode(&pstWriteParm->stMsgInfo.stTsRawData,&f_stMsgDataInfo);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        AT_WARN_LOG("MN_MSG_Write:Invalid Tpdu");
        return MN_ERR_CLASS_SMS_INVALID_TPDU;
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_WRITE,
                           clientId,
                           opId,
                           (VOS_VOID *)pstWriteParm);

    return ulRet;
}


VOS_UINT32   MN_MSG_Read(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_READ_PARM_STRU         *pstReadParm
)
{
    VOS_UINT32                          ulRet;

    if (VOS_NULL_PTR == pstReadParm)
    {
        AT_WARN_LOG("MN_MSG_Read:pstReadParm is Null");
        return MN_ERR_NULLPTR;
    }

#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    if ((MN_MSG_MEM_STORE_SIM != pstReadParm->enMemStore)
     && (MN_MSG_MEM_STORE_NV != pstReadParm->enMemStore))
#else
    if (MN_MSG_MEM_STORE_SIM != pstReadParm->enMemStore)
#endif
    {
        AT_WARN_LOG("MN_MSG_Read:Invalid enMemStore");
        return MN_ERR_INVALIDPARM;
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_READ,
                           clientId,
                           opId,
                           (VOS_VOID *)pstReadParm);

    return ulRet;
}



VOS_UINT32   MN_MSG_List(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_LIST_PARM_STRU         *pstListParm
)
{
    VOS_UINT32                          ulRet;

    if (VOS_NULL_PTR == pstListParm)
    {
        AT_WARN_LOG("MN_MSG_List:pstListParm is Null");
        return MN_ERR_NULLPTR;
    }

#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    if ((MN_MSG_MEM_STORE_SIM != pstListParm->enMemStore)
     && (MN_MSG_MEM_STORE_NV != pstListParm->enMemStore))
#else
    if (MN_MSG_MEM_STORE_SIM != pstListParm->enMemStore)
#endif
    {
        AT_WARN_LOG("MN_MSG_List:Invalid enMemStore");
        return MN_ERR_INVALIDPARM;
    }

    if (MN_MSG_STATUS_NONE < pstListParm->enStatus)
    {
        AT_WARN_LOG("MN_MSG_List:Invalid enStatus");
        return MN_ERR_INVALIDPARM;
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_LIST,
                           clientId,
                           opId,
                           (VOS_VOID *)pstListParm);

    return ulRet;
}


VOS_UINT32   MN_MSG_Delete(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_DELETE_PARAM_STRU      *pstDeleteParam
)
{
    VOS_UINT32                          ulRet;

    if (VOS_NULL_PTR == pstDeleteParam)
    {
        AT_WARN_LOG("MN_MSG_Delete:pstDelete is Null");
        return MN_ERR_NULLPTR;
    }

#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    if ((MN_MSG_MEM_STORE_SIM != pstDeleteParam->enMemStore)
     && (MN_MSG_MEM_STORE_NV != pstDeleteParam->enMemStore))
#else
    if (MN_MSG_MEM_STORE_SIM != pstDeleteParam->enMemStore)
#endif
    {
        AT_WARN_LOG("MN_MSG_Delete:Invalid enMemStore");
        return MN_ERR_INVALIDPARM;
    }

    if (MN_MSG_DELETE_ALL < pstDeleteParam->enDeleteType)
    {
        AT_WARN_LOG("MN_MSG_Delete:Invalid enDeleteType");
        return MN_ERR_INVALIDPARM;
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_DELETE,
                           clientId,
                           opId,
                           (VOS_VOID *)pstDeleteParam);

    return ulRet;
}


VOS_UINT32   MN_MSG_Delete_Test(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_LIST_PARM_STRU         *pstListPara
)
{
    VOS_UINT32                          ulRet;

#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    if ((MN_MSG_MEM_STORE_SIM != pstListPara->enMemStore)
     && (MN_MSG_MEM_STORE_NV != pstListPara->enMemStore))
#else
    if (MN_MSG_MEM_STORE_SIM != pstListPara->enMemStore)
#endif
    {
        AT_WARN_LOG("MN_MSG_Delete:Invalid enMemStore");
        return MN_ERR_INVALIDPARM;
    }

    if (pstListPara->enStatus >= MN_MSG_STATUS_MAX)
    {
        AT_WARN_LOG("MN_MSG_Delete:Invalid enStatus");
        return MN_ERR_INVALIDPARM;
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_DELETE_TEST,
                           clientId,
                           opId,
                           (VOS_VOID *)pstListPara);

    return ulRet;
}


VOS_UINT32   MN_MSG_ReadStaRpt(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_READ_COMM_PARAM_STRU   *pstReadParam
)
{
    VOS_UINT32                          ulRet;

    if (VOS_NULL_PTR == pstReadParam)
    {
        AT_WARN_LOG("MN_MSG_ReadStaRpt:pstReadParam is Null");
        return MN_ERR_NULLPTR;
    }

    if ((MN_MSG_MEM_STORE_SIM != pstReadParam->enMemStore)
     && (MN_MSG_MEM_STORE_NV != pstReadParam->enMemStore))
    {
        AT_WARN_LOG("MN_MSG_ReadStaRpt:Invalid enMemStore1");
        return MN_ERR_INVALIDPARM;
    }

    if (MN_MSG_MEM_STORE_SIM != pstReadParam->enMemStore)
    {
        AT_WARN_LOG("MN_MSG_ReadStaRpt:Invalid enMemStore2");
        return MN_ERR_INVALIDPARM;
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_READ_STARPT,
                           clientId,
                           opId,
                           (VOS_VOID *)pstReadParam);

    return ulRet;
}


VOS_UINT32   MN_MSG_DeleteStaRpt(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_DELETE_PARAM_STRU       *pstDeleteParam
)
{
    VOS_UINT32                          ulRet;

    if (VOS_NULL_PTR == pstDeleteParam)
    {
        AT_WARN_LOG("MN_MSG_DeleteStaRpt:pstDeleteParam is Null");
        return MN_ERR_NULLPTR;
    }

    if ((MN_MSG_MEM_STORE_SIM != pstDeleteParam->enMemStore)
     && (MN_MSG_MEM_STORE_NV != pstDeleteParam->enMemStore))
    {
        AT_WARN_LOG("MN_MSG_DeleteStaRpt:Invalid enMemStore");
        return MN_ERR_INVALIDPARM;
    }

    if (MN_MSG_MEM_STORE_SIM != pstDeleteParam->enMemStore)
    {
        AT_WARN_LOG("MN_MSG_DeleteStaRpt:Invalid enMemStore");
        return MN_ERR_INVALIDPARM;
    }

    if ((MN_MSG_DELETE_SINGLE != pstDeleteParam->enDeleteType)
     && (MN_MSG_DELETE_ALL != pstDeleteParam->enDeleteType))
    {
        AT_WARN_LOG("MN_MSG_DeleteStaRpt:Invalid enDeleteType");
        return MN_ERR_INVALIDPARM;
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_DELETE_STARPT,
                           clientId,
                           opId,
                           (VOS_VOID *)pstDeleteParam);

    return ulRet;
}



VOS_UINT32   MN_MSG_WriteSrvParam(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_WRITE_SRV_PARAM_STRU   *pstSrvParam
)
{
    VOS_UINT32                          ulRet;

    if (VOS_NULL_PTR == pstSrvParam)
    {
        AT_WARN_LOG("MN_MSG_WriteSrvParam:pstSetSrvParm is Null");
        return MN_ERR_NULLPTR;
    }

    if ((MN_MSG_WRITE_MODE_INSERT != pstSrvParam->enWriteMode)
     && (MN_MSG_WRITE_MODE_REPLACE != pstSrvParam->enWriteMode))
    {
        AT_WARN_LOG("MN_MSG_WriteSrvParam:Invalid enWriteMode");
        return MN_ERR_INVALIDPARM;
    }

    if ((MN_MSG_MEM_STORE_SIM != pstSrvParam->enMemStore)
     && (MN_MSG_MEM_STORE_NV != pstSrvParam->enMemStore))
    {
        AT_WARN_LOG("MN_MSG_WriteSrvParam:Invalid enMemStore");
        return MN_ERR_INVALIDPARM;
    }

    if ((MN_MSG_MEM_STORE_NV == pstSrvParam->enMemStore)
     && (0 != pstSrvParam->ulIndex))
    {
        AT_WARN_LOG("MN_MSG_WriteSrvParam:Only one record supported in NV.");
        return MN_ERR_INVALIDPARM;
    }

    /*如果设置的值没有一个有效,则返回*/
    if (MN_MSG_SRV_PARM_TOTALABSENT == (pstSrvParam->stSrvParm.ucParmInd & MN_MSG_SRV_PARM_TOTALABSENT))
    {
        AT_WARN_LOG("MN_MSG_WriteSrvParam:Invalid Parm,No Valid Data");
        return MN_ERR_INVALIDPARM;
    }

    /*判断SC Addr和Dest Addr的有效性*/
    if (MN_MSG_SRV_PARM_PRESENT ==
        ((pstSrvParam->stSrvParm.ucParmInd & MN_MSG_SRV_PARM_MASK_SC_ADDR) >> 1))
    {
       if (pstSrvParam->stSrvParm.stScAddr.ucBcdLen > MN_MSG_MAX_BCD_NUM_LEN)
       {
           AT_WARN_LOG("MN_MSG_WriteSrvParam:Invalid SC Address");
           return MN_ERR_CLASS_SMS_INVALID_SCADDR;
       }
    }

    if (MN_MSG_SRV_PARM_PRESENT ==
        (pstSrvParam->stSrvParm.ucParmInd & MN_MSG_SRV_PARM_MASK_DEST_ADDR))
    {
        if (pstSrvParam->stSrvParm.stDestAddr.ucBcdLen > MN_MSG_MAX_BCD_NUM_LEN)
        {
            AT_WARN_LOG("MN_MSG_WriteSrvParam:Invalid Dest Address");
            return MN_ERR_CLASS_SMS_INVALID_DESTADDR;
        }
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_WRITE_SRV_PARA,
                           clientId,
                           opId,
                           (VOS_VOID *)pstSrvParam);

    return ulRet;
}


VOS_UINT32   MN_MSG_ReadSrvParam(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_READ_COMM_PARAM_STRU  *pstReadParam
)
{
    VOS_UINT32                          ulRet;

    if (VOS_NULL_PTR == pstReadParam)
    {
        AT_WARN_LOG("MN_MSG_ReadSrvParam:pstReadParam is Null");
        return MN_ERR_NULLPTR;
    }

    if ((MN_MSG_MEM_STORE_SIM != pstReadParam->enMemStore)
     && (MN_MSG_MEM_STORE_NV != pstReadParam->enMemStore))
    {
        AT_WARN_LOG("MN_MSG_ReadSrvParam:Invalid enMemStore");
        return MN_ERR_INVALIDPARM;
    }

    if ((MN_MSG_MEM_STORE_NV == pstReadParam->enMemStore)
     && (0 != pstReadParam->ulIndex))
    {
        AT_WARN_LOG("MN_MSG_ReadSrvParam: Only one record supported in NV.");
        return MN_ERR_INVALIDPARM;
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_READ_SRV_PARA,
                           clientId,
                           opId,
                           (VOS_VOID *)pstReadParam);

    return ulRet;
}



VOS_UINT32   MN_MSG_DeleteSrvParam(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_DELETE_PARAM_STRU     *pstDeleteParam
)
{
    VOS_UINT32                          ulRet;

    if (VOS_NULL_PTR == pstDeleteParam)
    {
        AT_WARN_LOG("MN_MSG_DeleteSrvParam:pstDeleteParam is Null");
        return MN_ERR_NULLPTR;
    }

    if ((MN_MSG_MEM_STORE_SIM != pstDeleteParam->enMemStore)
     && (MN_MSG_MEM_STORE_NV != pstDeleteParam->enMemStore))
    {
        AT_WARN_LOG("MN_MSG_DeleteSrvParam:Invalid enMemStore");
        return MN_ERR_INVALIDPARM;
    }

    if ((MN_MSG_DELETE_SINGLE != pstDeleteParam->enDeleteType)
     && (MN_MSG_DELETE_ALL != pstDeleteParam->enDeleteType))
    {
        AT_WARN_LOG("MN_MSG_DeleteSrvParam:Invalid enDeleteType");
        return MN_ERR_INVALIDPARM;
    }

    if (MN_MSG_MEM_STORE_NV == pstDeleteParam->enMemStore)
    {
        if ((MN_MSG_DELETE_SINGLE != pstDeleteParam->enDeleteType)
         && (0 != pstDeleteParam->ulIndex))
        {
            AT_WARN_LOG("MN_MSG_WriteSrvParam:Only one record supported in NV.");
            return MN_ERR_INVALIDPARM;
        }
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_DELETE_SRV_PARA,
                           clientId,
                           opId,
                           (VOS_VOID *)pstDeleteParam);

    return ulRet;
}


VOS_UINT32   MN_MSG_ModifyStatus(
    MN_CLIENT_ID_T                       clientId,
    MN_OPERATION_ID_T                    opId,
    const MN_MSG_MODIFY_STATUS_PARM_STRU *pstModifyParm
)
{
    VOS_UINT32                          ulRet;

    if (VOS_NULL_PTR == pstModifyParm)
    {
        AT_WARN_LOG("MN_MSG_ModifyStatus:pstModifyParm is Null");
        return MN_ERR_NULLPTR;
    }

#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    if ((MN_MSG_MEM_STORE_SIM != pstModifyParm->enMemStore)
     && (MN_MSG_MEM_STORE_NV != pstModifyParm->enMemStore))
#else
    if (MN_MSG_MEM_STORE_SIM != pstModifyParm->enMemStore)
#endif
    {
        AT_WARN_LOG("MN_MSG_ModifyStatus:Invalid enMemStore");
        return MN_ERR_INVALIDPARM;
    }

    if (MN_MSG_STATUS_MO_SENT < pstModifyParm->enStatus)
    {
        AT_WARN_LOG("MN_MSG_ModifyStatus:Invalid enStatus");
        return MN_ERR_INVALIDPARM;
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_MODIFY_STATUS,
                           clientId,
                           opId,
                           (VOS_VOID *)pstModifyParm);

    return ulRet;
}



VOS_UINT32 MN_MSG_SetRcvMsgPath(
    MN_CLIENT_ID_T                         clientId,
    MN_OPERATION_ID_T                      opId,
    const MN_MSG_SET_RCVMSG_PATH_PARM_STRU *pstSetRcvPathParm
)
{
    VOS_UINT32                          ulRet;

    if (VOS_NULL_PTR == pstSetRcvPathParm)
    {
        AT_WARN_LOG("MN_MSG_SetRcvMsgPath:pstSetRcvPathParm is Null");
        return MN_ERR_NULLPTR;
    }

    if  ((MN_MSG_RCVMSG_ACT_TRANSFER_AND_ACK < pstSetRcvPathParm->enRcvSmAct)
      || (MN_MSG_RCVMSG_ACT_TRANSFER_AND_ACK < pstSetRcvPathParm->enRcvStaRptAct))
    {
        AT_WARN_LOG("MN_MSG_SetRcvMsgPath:Invalid enRcvSmAct");
        return MN_ERR_INVALIDPARM;
    }

#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    if ((MN_MSG_MEM_STORE_NV < pstSetRcvPathParm->enSmMemStore)
     || (MN_MSG_MEM_STORE_NV < pstSetRcvPathParm->enStaRptMemStore))
#else
    if ((MN_MSG_MEM_STORE_SIM < pstSetRcvPathParm->enSmMemStore)
     || (MN_MSG_MEM_STORE_SIM < pstSetRcvPathParm->enStaRptMemStore))
#endif
    {
        AT_WARN_LOG("MN_MSG_SetRcvMsgPath:Invalid enSmMemStore");
        return MN_ERR_INVALIDPARM;
    }

    if (MN_MSG_RCVMSG_ACT_STORE == pstSetRcvPathParm->enRcvSmAct)
    {
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
        if ((MN_MSG_MEM_STORE_NV  != pstSetRcvPathParm->enSmMemStore)
         && (MN_MSG_MEM_STORE_SIM != pstSetRcvPathParm->enSmMemStore))
#else
        if (MN_MSG_MEM_STORE_SIM != pstSetRcvPathParm->enSmMemStore)
#endif
        {
            AT_WARN_LOG("MN_MSG_SetRcvMsgPath:Invalid Parm");
            return MN_ERR_INVALIDPARM;
        }
    }

    if (MN_MSG_RCVMSG_ACT_STORE == pstSetRcvPathParm->enRcvStaRptAct)
    {
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
        if ((MN_MSG_MEM_STORE_NV  != pstSetRcvPathParm->enStaRptMemStore)
         && (MN_MSG_MEM_STORE_SIM != pstSetRcvPathParm->enStaRptMemStore))
#else
        if (MN_MSG_MEM_STORE_SIM != pstSetRcvPathParm->enStaRptMemStore)
#endif
        {
            AT_WARN_LOG("MN_MSG_SetRcvMsgPath:Invalid Parm");
            return MN_ERR_INVALIDPARM;
        }
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_SET_RCVPATH,
                           clientId,
                           opId,
                           (VOS_VOID *)pstSetRcvPathParm);

    return ulRet;

}


VOS_UINT32   MN_MSG_GetRcvMsgPath(
    MN_CLIENT_ID_T                         clientId,
    MN_OPERATION_ID_T                      opId,
    const MN_MSG_GET_RCVMSG_PATH_PARM_STRU *pstGetRcvPathParm
)
{
    VOS_UINT32                          ulRet;

    if (VOS_NULL_PTR == pstGetRcvPathParm)
    {
        AT_WARN_LOG("MN_MSG_GetRcvMsgPath:pstGetRcvPathParm is Null");
        return MN_ERR_NULLPTR;
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_GET_RCVPATH,
                           clientId,
                           opId,
                           (VOS_VOID *)pstGetRcvPathParm);

    return ulRet;
}


VOS_UINT32  MN_MSG_GetStorageStatus(
    MN_CLIENT_ID_T                            clientId,
    MN_OPERATION_ID_T                         opId,
    const MN_MSG_GET_STORAGE_STATUS_PARM_STRU *pstStorageParm
)
{
    VOS_UINT32                          ulRet;

    if (VOS_NULL_PTR == pstStorageParm)
    {
        AT_WARN_LOG("MN_MSG_GetStorageStatus:pstMemParm is Null");
        return MN_ERR_NULLPTR;
    }

#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    if ((MN_MSG_MEM_STORE_SIM != pstStorageParm->enMem1Store)
     && (MN_MSG_MEM_STORE_NV != pstStorageParm->enMem1Store)
     && (MN_MSG_MEM_STORE_NONE != pstStorageParm->enMem1Store))
#else
    if (MN_MSG_MEM_STORE_SIM != pstStorageParm->enMem1Store)
#endif
    {
        AT_WARN_LOG("MN_MSG_GetStorageStatus:Invalid enMemStore:mem1");
        return MN_ERR_INVALIDPARM;
    }

    if (pstStorageParm->enMem1Store == pstStorageParm->enMem2Store)
    {
        AT_WARN_LOG("MN_MSG_GetStorageStatus:Invalid enMemStore:mem1 == mem2");
        return MN_ERR_INVALIDPARM;
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_GET_STORAGESTATUS,
                           clientId,
                           opId,
                           (VOS_VOID *)pstStorageParm);

    return ulRet;
}


VOS_UINT32   MN_MSG_GetStaRptIndex(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_STARPT_MOMSG_PARM_STRU *pstMoMsgParm
)
{
    VOS_UINT32                          ulRet;

    if (VOS_NULL_PTR == pstMoMsgParm)
    {
        AT_WARN_LOG("MN_MSG_GetStaRptFromMoMsg:pstMoMsgParm is Null");
        return MN_ERR_NULLPTR;
    }

#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    if ((MN_MSG_MEM_STORE_SIM != pstMoMsgParm->enMemStore)
     && (MN_MSG_MEM_STORE_NV != pstMoMsgParm->enMemStore))
#else
    if (MN_MSG_MEM_STORE_SIM != pstMoMsgParm->enMemStore)
#endif
    {
        AT_WARN_LOG("MN_MSG_GetStaRptFromMoMsg:Invalid enMemStore");
        return MN_ERR_INVALIDPARM;
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_GET_STARPT_FROMMOMSG,
                           clientId,
                           opId,
                           (VOS_VOID *)pstMoMsgParm);

    return ulRet;

}


VOS_UINT32   MN_MSG_GetMoMsgIndex(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_STARPT_MOMSG_PARM_STRU *pstStaRptParm
)
{
    VOS_UINT32                          ulRet;

    if (VOS_NULL_PTR == pstStaRptParm)
    {
        AT_WARN_LOG("MN_MSG_GetMoMsgFromStaRpt:pstMemParm is Null");
        return MN_ERR_NULLPTR;
    }

    if ((MN_MSG_MEM_STORE_SIM != pstStaRptParm->enMemStore)
     && (MN_MSG_MEM_STORE_NV != pstStaRptParm->enMemStore))
    {
        AT_WARN_LOG("MN_MSG_GetMoMsgFromStaRpt:Invalid enMemStore1");
        return MN_ERR_INVALIDPARM;
    }

    if (MN_MSG_MEM_STORE_SIM != pstStaRptParm->enMemStore)
    {
        AT_WARN_LOG("MN_MSG_GetMoMsgFromStaRpt:Invalid enMemStore2");
        return MN_ERR_INVALIDPARM;
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_GET_MOMSG_FROMSTARPT,
                           clientId,
                           opId,
                           (VOS_VOID *)pstStaRptParm);

    return ulRet;
}


VOS_UINT32 MN_MSG_SetMemStatus(
    MN_CLIENT_ID_T                       clientId,
    MN_OPERATION_ID_T                    opId,
    const MN_MSG_SET_MEMSTATUS_PARM_STRU *pMemStatusParm
)
{
    VOS_UINT32                          ulRet;

    if (VOS_NULL_PTR == pMemStatusParm)
    {
        AT_WARN_LOG("MN_MSG_SetMemStatus:pMemStatusParm is Null");
        return MN_ERR_NULLPTR;
    }

    if ((MN_MSG_MEM_FULL_SET != pMemStatusParm->enMemFlag)
     && (MN_MSG_MEM_FULL_UNSET != pMemStatusParm->enMemFlag))
    {
        AT_WARN_LOG("MN_MSG_SetMemStatus:Invalid enMemFlag");
        return MN_ERR_INVALIDPARM;
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_SET_MEMSTATUS,
                           clientId,
                           opId,
                           (VOS_VOID *)pMemStatusParm);

    return ulRet;
}

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))


VOS_UINT32 MN_MSG_GetAllCbMids(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId
)
{
    VOS_UINT32                          ulRet;

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_GET_ALLCBMIDS,
                           clientId,
                           opId,
                           VOS_NULL_PTR);

    return ulRet;
}


VOS_UINT32 MN_MSG_AddCbMids(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const TAF_CBA_CBMI_RANGE_LIST_STRU *pstCbmirList
)
{
    VOS_UINT32                          ulRet;

    if (VOS_NULL_PTR == pstCbmirList)
    {
        AT_WARN_LOG("MN_MSG_DeleteCbMsg: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_ADD_CBMIDS,
                           clientId,
                           opId,
                           (VOS_VOID *)pstCbmirList);

    return ulRet;
}


VOS_UINT32 MN_MSG_DelCbMids(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const TAF_CBA_CBMI_RANGE_LIST_STRU *pstCbmirList
)
{
    VOS_UINT32                          ulRet;

    if (VOS_NULL_PTR == pstCbmirList)
    {
        AT_WARN_LOG("MN_MSG_DeleteCbMsg: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_DELETE_CBMIDS,
                           clientId,
                           opId,
                           (VOS_VOID *)pstCbmirList);

    return ulRet;
}


VOS_UINT32 MN_MSG_EmptyCbMids(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId
)
{
    VOS_UINT32                          ulRet;

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_EMPTY_CBMIDS,
                           clientId,
                           opId,
                           VOS_NULL_PTR);

    return ulRet;
}

#endif
#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

