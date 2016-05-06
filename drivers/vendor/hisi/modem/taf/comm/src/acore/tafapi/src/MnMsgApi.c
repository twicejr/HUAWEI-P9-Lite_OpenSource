

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
/*****************************************************************************
 函 数 名  : MSG_SendAppReq
 功能描述  : 申请消息和填写消息头并发送消息的公共函数
 输入参数  : enMsgType       - 申请消息的类型
             clientId        - 发起该请求的Client的ID
             opId            - Operation ID, 标识本次操作
             pSendParm       - 需要发送的参数内容
 输出参数  : 无
 返 回 值  : MN_ERR_NO_ERROR：成功
             其他：失败及其失败的原因
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月14日
    作    者   : z40661
    修改内容   : 新生成函数
  2.日    期   : 2012年4月5日
    作    者   : l00171473
    修改内容   : for V7R1C50 CSFB&PPAC&ETWS&ISR
  3.日    期   : 2012年12月11日
    作    者   : l00167671
    修改内容   : DTS2012121802573,TQE清理
  4.日    期   : 2012年12月24日
    作    者   : l60609
    修改内容   : DSDA Phase II

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

/* Added by f62575 for AT Project，2011-10-03,  Begin*/
/*****************************************************************************
 函 数 名  : MN_MSG_ReqStub
 功能描述  : 请求C核执行短信桩请求
 输入参数  : MN_CLIENT_ID_T                 clientId 发起该请求的Client的ID
             MN_OPERATION_ID_T              opId     Operation ID, 标识本次操作
             const MN_MSG_STUB_MSG_STRU     *pstStubParam 桩操作参数
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月3日
    作    者   : f62575
    修改内容   : 新生成函数

*****************************************************************************/
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
/* Added by f62575 for AT Project，2011-10-03,  End*/

/*****************************************************************************
 函 数 名  : MN_MSG_SetLinkCtrl
 功能描述  : 应用设置中继链路控制接口
 输入参数  : clientId          - 发起该请求的Client的ID
             opId              - Operation ID, 标识本次操作
             pstSetParam    　 - 应用设置的中继链路控制的参数内容
 输出参数  : 无
 返 回 值  : MN_ERR_NO_ERROR：成功
             其他：失败及其失败的原因
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年7月21日
    作    者   : f62575
    修改内容   : 新生成函数
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : MN_MSG_GetLinkCtrl
 功能描述  : 应用获取中继链路控制接口
 输入参数  : clientId          - 发起该请求的Client的ID
             opId              - Operation ID, 标识本次操作
 输出参数  : 无
 返 回 值  : MN_ERR_NO_ERROR：成功
             其他：失败及其失败的原因
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年7月21日
    作    者   : f62575
    修改内容   : 新生成函数
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : MN_MSG_Send
 功能描述  : 应用直接发送短信和短信命令接口
 输入参数  : clientId          - 发起该请求的Client的ID
             opId              - Operation ID, 标识本次操作
             pstSendDirectParm - 应用发送短信的参数内容
 输出参数  : 无
 返 回 值  : MN_ERR_NO_ERROR：成功
             其他：失败及其失败的原因
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月27日
    作    者   : z40661
    修改内容   : 新生成函数
  2.日    期   : 2011年03月01日
    作    者   : A00165503
    修改内容   : 问题单号: DTS2011021202242/DTS2011021400322，添加宏开关判断
                 服务域为PS_ONLY时，CS域短信和呼叫业务是否能够发起
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : MN_MSG_SendFromMem
 功能描述  : 从内存USIM或NVIM中发送短信接口
 输入参数  : clientId           - 发起该请求的Client的ID
             opId               - Operation ID, 标识本次操作
             enDomain           - 短信发送域
             pstSendFromMemParm - 从内存中发送短信的参数内容
 输出参数  : 无
 返 回 值  : MN_ERR_NO_ERROR：成功
             其他：失败及其失败的原因
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月27日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : MN_MSG_SendAck
 功能描述  : 收到短信后,应用可调用该接口发送收到短信的报告,RP-ACK或RP-ERROR
 输入参数  : clientId           - 发起该请求的Client的ID
             opId               - Operation ID, 标识本次操作
             pstAckParm         - 发送短信报告相关信息
 输出参数  : 无
 返 回 值  : MN_ERR_NO_ERROR：成功
             其他：失败及其失败的原因
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月27日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : MN_MSG_Write
 功能描述  : 向USIM或NVIM中写一条短信
 输入参数  : clientId       - 发起该请求的Client的ID
             opId           - Operation ID, 标识本次操作
             pstWriteParm   - 写短信参数
 输出参数  : 无
 返 回 值  : MN_ERR_NO_ERROR：成功
             其他：失败及其失败的原因
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月27日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : MN_MSG_Read
 功能描述  : 从USIM或NVIM中读一条短信
 输入参数  : clientId       - 发起该请求的Client的ID
             opId           - Operation ID, 标识本次操作
             pstReadParm    - 读取参数
 输出参数  : 无
 返 回 值  : MN_ERR_NO_ERROR：成功
             其他：失败及其失败的原因
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月27日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : MN_MSG_List
 功能描述  : 从USIM或NVIM中列表某种状态短信
 输入参数  : clientId       - 发起该请求的Client的ID
             opId           - Operation ID, 标识本次操作
             pstListParm    - 列表参数
 输出参数  : 无
 返 回 值  : MN_ERR_NO_ERROR：成功
             其他：失败及其失败的原因
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月27日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : MN_MSG_Delete
 功能描述  : 从USIM或NVIM中列表删除短信
 输入参数  : clientId       - 发起该请求的Client的ID
             opId           - Operation ID, 标识本次操作
             pstDeleteParm  - 删除参数,如索引和存储位置等等
 输出参数  : 无
 返 回 值  : MN_ERR_NO_ERROR：成功
             其他：失败及其失败的原因
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月27日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : MN_MSG_Delete_Test
 功能描述  : 从USIM或NVIM中列表删除短信命令的测试操作
 输入参数  : clientId       - 发起该请求的Client的ID
             opId           - Operation ID, 标识本次操作
             enMemStore     - 删除短信测试命令操作的存储介质类型
 输出参数  : 无
 返 回 值  : MN_ERR_NO_ERROR：成功
             其他：失败及其失败的原因
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月27日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : MN_MSG_ReadStaRpt
 功能描述  : 从USIM或NVIM中读一条短信状态报告
 输入参数  : clientId            - 发起该请求的Client的ID
             opId                - Operation ID, 标识本次操作
             pstReadParm         - 读取参数,如索引和存储位置等等
 输出参数  : 无
 返 回 值  : MN_ERR_NO_ERROR：成功
             其他：失败及其失败的原因
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月27日
    作    者   : z40661
    修改内容   : 新生成函数
  2.日    期   : 2012年03月03日
    作    者   : s62952
    修改内容   : BalongV300R002 Build优化项目:删除宏控制
  3.日    期   : 2014年5月30日
    作    者   : j00174725
    修改内容   : TQE
*****************************************************************************/
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

    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
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
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_READ_STARPT,
                           clientId,
                           opId,
                           (VOS_VOID *)pstReadParam);

    return ulRet;
}

/*****************************************************************************
 函 数 名  : MN_MSG_DeleteStaRpt
 功能描述  : 从USIM或NVIM中列表删除短信状态报告
 输入参数  : clientId       - 发起该请求的Client的ID
             opId           - Operation ID, 标识本次操作
             pstDelete      - 删除参数,如索引,存储位置
 输出参数  : 无
 返 回 值  : MN_ERR_NO_ERROR：成功
             其他：失败及其失败的原因
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月27日
    作    者   : z40661
    修改内容   : 新生成函数
 2.日    期   : 2012年03月03日
    作    者   : s62952
    修改内容   : BalongV300R002 Build优化项目:API删除宏控制
*****************************************************************************/
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

    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
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
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */

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


/*****************************************************************************
 函 数 名  : MN_MSG_WriteSrvParam
 功能描述  : 设置短信相关参数,如短信中心，有效期等等
 输入参数  : clientId       - 发起该请求的Client的ID
             opId           - Operation ID, 标识本次操作
             pstSrvParam     - 需要设置的参数,如短信中心等等
 输出参数  : 无
 返 回 值  : MN_ERR_NO_ERROR：成功
             其他：失败及其失败的原因
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月27日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : MN_MSG_ReadSrvParam
 功能描述  : 获取短信相关参数,如短信中心，有效期等等
 输入参数  : clientId       - 发起该请求的Client的ID
             opId           - Operation ID, 标识本次操作
             pstReadParm    - 读取参数,如索引和存储位置等等
 输出参数  : 无
 返 回 值  : MN_ERR_NO_ERROR：成功
             其他：失败及其失败的原因
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月27日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : MN_MSG_DeleteSrvParam
 功能描述  : 删除短信相关参数,如短信中心，有效期等等
 输入参数  : clientId        - 发起该请求的Client的ID
             opId            - Operation ID, 标识本次操作
             pstDeleteParm   - 删除参数,如索引,存储位置等等
 输出参数  : 无
 返 回 值  : MN_ERR_NO_ERROR：成功
             其他：失败及其失败的原因
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月27日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : MN_MSG_ModifyStatus
 功能描述  : 修改短信状态，通过该接口可以将接收到的短信修改为已读或未读状态；
                                     可以SUMBIT或COMMAND短消息修改为已发送或未发送状态
 输入参数  : clientId            - 发起该请求的Client的ID
             opId                - Operation ID, 标识本次操作
             pstModifyParm       - 修改短信状态相关参数
 输出参数  : 无
 返 回 值  : MN_ERR_NO_ERROR：成功
             其他：失败及其失败的原因
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月27日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : MN_MSG_SetRcvMsgPath
 功能描述  : 设置接收短信路径,包括存储位置和短信报告的应答
 输入参数  : clientId            - 发起该请求的Client的ID
             opId                - Operation ID, 标识本次操作
             pstRcvPathParm      - 设置路径相关参数
 输出参数  : 无
 返 回 值  : MN_ERR_NO_ERROR：成功
             其他：失败及其失败的原因
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月27日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : MN_MSG_GetRcvMsgPath
 功能描述  : 获取接收短信路径,包括存储位置和短信报告应答
 输入参数  : clientId            - 发起该请求的Client的ID
             opId                - Operation ID, 标识本次操作
             pstGetRcvPathParm   - 获取路径相关参数
 输出参数  : 无
 返 回 值  : MN_ERR_NO_ERROR：成功
             其他：失败及其失败的原因
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月27日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : MN_MSG_GetStorageStatus
 功能描述  : 获取短信当前的存储状况
 输入参数  : clientId            - 发起该请求的Client的ID
             opId                - Operation ID, 标识本次操作
             pstMemParm          - 短信存储位置相关参数
 输出参数  : 无
 返 回 值  : MN_ERR_NO_ERROR：成功
             其他：失败及其失败的原因
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月27日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : MN_MSG_GetStatusRptIndex
 功能描述  : 根据MO短信索引得到其状态报告索引
 输入参数  : clientId       - 发起该请求的Client的ID
             opId           - Operation ID, 标识本次操作
             pstMoMsgParm   - MO短信的参数,所有和位置
 输出参数  : 无
 返 回 值  : MN_ERR_NO_ERROR：成功
             其他：失败及其失败的原因
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月27日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : MN_MSG_GetMoMsgIndex
 功能描述  : 根据短信状态报告索引得到MO短信的索引
 输入参数  : clientId       - 发起该请求的Client的ID
             opId           - Operation ID, 标识本次操作
             pstStaRptParm  - 短信状态报告的参数,索引和位置

 输出参数  : 无
 返 回 值  : MN_ERR_NO_ERROR：成功
             其他：失败及其失败的原因
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月27日
    作    者   : z40661
    修改内容   : 新生成函数
  2.日    期   : 2012年03月03日
    作    者   : s62952
    修改内容   : BalongV300R002 Build优化项目
*****************************************************************************/
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

    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
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
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_GET_MOMSG_FROMSTARPT,
                           clientId,
                           opId,
                           (VOS_VOID *)pstStaRptParm);

    return ulRet;
}

/*****************************************************************************
 函 数 名  : MN_MSG_SetMemStatus
 功能描述  : APP设置当前的接收容量,满或不满
 输入参数  : clientId            - 发起该请求的Client的ID
             opId                - Operation ID, 标识本次操作
             pMemStatusParm      - APP当前接收容量
 输出参数  : 无
 返 回 值  : MN_ERR_NO_ERROR：成功
             其他：失败及其失败的原因
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月27日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : MN_MSG_GetAllCbMids
 功能描述  : 提供给应用层查询CBS列表功能的请求
 输入参数  : clientId           - 发起该请求的Client的ID
             opId               - Operation ID, 标识本次操作
 输出参数  : 无
 返 回 值  : MN_ERR_NO_ERROR：成功
             其他：失败及其失败的原因
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年5月10日
    作    者   : zhoujun \z40661
    修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : MN_MSG_AddCbMids
 功能描述  : 提供给应用层打开或关闭CBS功能的请求
 输入参数  : clientId           - 发起该请求的Client的ID
             opId               - Operation ID, 标识本次操作
             pstCbMids          - 待增加的广播短消息ID集合
 输出参数  : 无
 返 回 值  : MN_ERR_NO_ERROR：成功
             其他：失败及其失败的原因
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年5月8日
    作    者   : zhoujun /z40661
    修改内容   : 新生成函数
  2.日    期   : 2012年4月5日
    作    者   : l00171473
    修改内容   : for V7R1C50 CSFB&PPAC&ETWS&ISR
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : MN_MSG_DeleteCbMids
 功能描述  : 提供给应用层打开或关闭CBS功能的请求
 输入参数  : clientId           - 发起该请求的Client的ID
             opId               - Operation ID, 标识本次操作
             pstCbMids          - 待删除的广播短消息ID集合
 输出参数  : 无
 返 回 值  : MN_ERR_NO_ERROR：成功
             其他：失败及其失败的原因
 调用函数  :
 被调函数  :

 1.日    期   : 2010年5月8日
   作    者   : zhoujun /z40661
   修改内容   : 新生成函数
  2.日    期   : 2012年4月5日
    作    者   : l00171473
    修改内容   : for V7R1C50 CSFB&PPAC&ETWS&ISR
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : MN_MSG_EmptyCbMids
 功能描述  : 删除所有CBS ID
 输入参数  : clientId           - 发起该请求的Client的ID
             opId               - Operation ID, 标识本次操作
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年5月8日
    作    者   : zhoujun /z40661
    修改内容   : 新生成函数

*****************************************************************************/
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

