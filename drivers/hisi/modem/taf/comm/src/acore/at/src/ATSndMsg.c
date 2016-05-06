

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "AtSndMsg.h"
#include "AtCsimagent.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e960*/
#define    THIS_FILE_ID        PS_FILE_ID_AT_SND_MSG_C
/*lint +e960*/

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : AT_FillAppReqMsgHeader
 功能描述  : 填充AT消息头
 输入参数  : MN_APP_REQ_MSG_STRU                 *pMsg
             MN_CLIENT_ID_T                      usClientId
             MN_OPERATION_ID_T                   ucOpId
             VOS_UINT16                          usMsgType
             VOS_UINT32                          ulRcvPid
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月15日
    作    者   : 鲁琳/l60609
    修改内容   : 新生成函数
  2.日    期   : 2012年12月17日
    作    者   : l60609
    修改内容   : DSDA Phase II
*****************************************************************************/
VOS_UINT32  AT_FillAppReqMsgHeader(
    MN_APP_REQ_MSG_STRU                *pMsg,
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId,
    VOS_UINT16                          usMsgType,
    VOS_UINT32                          ulRcvPid
 )
{
    MN_APP_REQ_MSG_STRU                *pAppMsgHeader;

    pAppMsgHeader                       = pMsg;
    pAppMsgHeader->clientId             = usClientId;
    pAppMsgHeader->opId                 = ucOpId;
    pAppMsgHeader->usMsgName            = usMsgType;
    pAppMsgHeader->ulSenderPid          = WUEPS_PID_AT;
    pAppMsgHeader->ulReceiverPid        = AT_GetDestPid(usClientId, ulRcvPid);
    pAppMsgHeader->ulSenderCpuId        = VOS_LOCAL_CPUID;
    pAppMsgHeader->ulReceiverCpuId      = VOS_LOCAL_CPUID;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_FillAppReqMsgPara
 功能描述  : 填充AT消息包内容
 输入参数  : VOS_VOID                           *pSndMsgPara
             VOS_VOID                           *pPara
             VOS_UINT32                          ulLen
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月15日
    作    者   : 鲁琳/l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  AT_FillAppReqMsgPara(
    VOS_VOID                           *pSndMsgPara,
    VOS_VOID                           *pPara,
    VOS_UINT32                          ulLen
)
{
    if (VOS_NULL_PTR == pSndMsgPara)
    {
        return VOS_ERR;
    }

    if (ulLen > 0)
    {
        PS_MEM_CPY(pSndMsgPara, pPara, ulLen);
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_GetAppReqMsgLen
 功能描述  : 获取AT消息包长度
 输入参数  : VOS_UINT32                          ulParaLen
             VOS_UINT32                         *pulMsgLen
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月15日
    作    者   : 鲁琳/l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  AT_GetAppReqMsgLen(
    VOS_UINT32                          ulParaLen,
    VOS_UINT32                         *pulMsgLen
)
{
    VOS_UINT32                          ulMsgLen;

    if (VOS_NULL_PTR == pulMsgLen)
    {
        return VOS_ERR;
    }

    if (ulParaLen <= 4)
    {
        ulMsgLen = sizeof(MN_APP_REQ_MSG_STRU);
    }
    else
    {
        ulMsgLen = (sizeof(MN_APP_REQ_MSG_STRU) + ulParaLen) - 4;
    }

    *pulMsgLen = ulMsgLen;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_FillAndSndAppReqMsg
 功能描述  : 填充并发送AT消息包
 输入参数  : MN_CLIENT_ID_T                      usClientId
             MN_OPERATION_ID_T                   ucOpId
             VOS_UINT16                          usMsgType
             VOS_VOID                            *pPara
             VOS_UINT32                          ulParaLen
             VOS_UINT32                          ulRcvPid
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月15日
    作    者   : 鲁琳/l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  AT_FillAndSndAppReqMsg(
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId,
    VOS_UINT16                          usMsgType,
    VOS_VOID                            *pPara,
    VOS_UINT32                          ulParaLen,
    VOS_UINT32                          ulRcvPid
)
{
    VOS_UINT8                          *pMsg;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulMsgLen;
    VOS_UINT8                          *pMsgPara;

    if ((VOS_NULL_PTR == pPara) && (0 < ulParaLen))
    {
        return TAF_FAILURE;
    }

    pMsgPara = (VOS_UINT8 *)pPara;

    /* 获取消息长度 */
    AT_GetAppReqMsgLen( ulParaLen, &ulMsgLen);

    /* 申请消息 */
    pMsg = (VOS_UINT8 *)PS_ALLOC_MSG(WUEPS_PID_AT, ulMsgLen - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pMsg)
    {
        return TAF_FAILURE;
    }

    PS_MEM_SET((pMsg + VOS_MSG_HEAD_LENGTH), 0, (ulMsgLen - VOS_MSG_HEAD_LENGTH));

    /* 填充消息头 */
    AT_FillAppReqMsgHeader((MN_APP_REQ_MSG_STRU *)pMsg, usClientId, ucOpId, usMsgType, ulRcvPid);

    /* 填充消息参数 */
    AT_FillAppReqMsgPara(&pMsg[sizeof(MN_APP_REQ_MSG_STRU) - 4], pMsgPara, ulParaLen);

    ulRet = PS_SEND_MSG(WUEPS_PID_AT, pMsg);

    if (VOS_OK != ulRet)
    {
        return TAF_FAILURE;
    }

    return TAF_SUCCESS;
}

/*****************************************************************************
 函 数 名  : AT_SndSetFastDorm()
 功能描述  : 设置当前FAST DORMANCY
 输入参数  : usClientId      - 用户client id
             ucOpId          - 操作ID
             pstFastDormPara - AT命令操作的参数
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月24日
    作    者   : h44270
    修改内容   : 新生成函数
  2.日    期   : 2012年12月21日
    作    者   : l00227485
    修改内容   : DSDA PhaseII
*****************************************************************************/
VOS_UINT32 AT_SndSetFastDorm (
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    AT_RABM_FASTDORM_PARA_STRU          *pstFastDormPara
)
{
    AT_RABM_SET_FASTDORM_PARA_REQ_STRU  *pstSndMsg;
    VOS_UINT32                           ulRslt;

    /* 申请内存  */
    pstSndMsg = (AT_RABM_SET_FASTDORM_PARA_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_AT,
                                               sizeof(AT_RABM_SET_FASTDORM_PARA_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if ( VOS_NULL_PTR == pstSndMsg )
    {
        /* 内存申请失败 */
        AT_ERR_LOG("AT_SndSetFastDorm:ERROR: Memory Alloc Error for pstMsg");
        return VOS_ERR;
    }

    /* 填写相关参数 */
    pstSndMsg->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSndMsg->stMsgHeader.ulReceiverPid     = AT_GetDestPid(usClientId, I0_WUEPS_PID_RABM);
    pstSndMsg->stMsgHeader.ulLength          = sizeof(AT_RABM_SET_FASTDORM_PARA_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstSndMsg->stMsgHeader.ulMsgName         = ID_AT_RABM_SET_FASTDORM_PARA_REQ;
    pstSndMsg->stFastDormPara                = *pstFastDormPara;
    pstSndMsg->usClientId                    = usClientId;
    pstSndMsg->ucOpId                        = ucOpId;

    /* 调用VOS发送原语 */
    ulRslt = PS_SEND_MSG(WUEPS_PID_AT, pstSndMsg);
    if ( VOS_OK != ulRslt )
    {
        AT_ERR_LOG("AT_SndSetFastDorm:ERROR:PS_SEND_MSG ");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_SndQryFastDorm()
 功能描述  : 查询当前FAST DORMANCY的设置
 输入参数  : usClientId      - 用户client id
             ucOpId          - 操作ID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月24日
    作    者   : h44270
    修改内容   : 新生成函数
  2.日    期   : 2012年12月21日
    作    者   : l00227485
    修改内容   : DSDA PhaseII
*****************************************************************************/
VOS_UINT32 AT_SndQryFastDorm (
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    AT_RABM_QRY_FASTDORM_PARA_REQ_STRU  *pstSndMsg;
    VOS_UINT32                           ulRslt;

    /* 申请内存  */
    pstSndMsg = (AT_RABM_QRY_FASTDORM_PARA_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_AT,
                                               sizeof(AT_RABM_QRY_FASTDORM_PARA_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if ( VOS_NULL_PTR == pstSndMsg )
    {
        /* 内存申请失败 */
        AT_ERR_LOG("AT_SndSetFastDorm:ERROR: Memory Alloc Error for pstMsg");
        return VOS_ERR;
    }

    /* 填写相关参数 */
    pstSndMsg->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSndMsg->stMsgHeader.ulReceiverPid     = AT_GetDestPid(usClientId, I0_WUEPS_PID_RABM);
    pstSndMsg->stMsgHeader.ulLength          = sizeof(AT_RABM_QRY_FASTDORM_PARA_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstSndMsg->stMsgHeader.ulMsgName         = ID_AT_RABM_QRY_FASTDORM_PARA_REQ;
    pstSndMsg->usClientId                    = usClientId;
    pstSndMsg->ucOpId                        = ucOpId;

    /* 调用VOS发送原语 */
    ulRslt = PS_SEND_MSG(WUEPS_PID_AT, pstSndMsg);
    if ( VOS_OK != ulRslt )
    {
        AT_ERR_LOG("AT_SndSetFastDorm:ERROR:PS_SEND_MSG ");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : At_SndReleaseRrcReq
 功能描述  : 快速拆除rrc连接
 输入参数  : usClientId      - 用户client id
             ucOpId          - 操作ID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月11日
    作    者   : M00217266
    修改内容  : Optimize RIL:

*****************************************************************************/
VOS_UINT32 At_SndReleaseRrcReq (
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    AT_RABM_RELEASE_RRC_REQ_STRU        *pstSndMsg;
    VOS_UINT32                           ulRslt;

    /* 申请内存  */
    pstSndMsg = (AT_RABM_RELEASE_RRC_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_AT,
                                               sizeof(AT_RABM_RELEASE_RRC_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if ( VOS_NULL_PTR == pstSndMsg )
    {
        /* 内存申请失败 */
        AT_ERR_LOG("At_SndReleaseRrcReq:ERROR: Memory Alloc Error for pstMsg");
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_CHAR*)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0x00, (sizeof(AT_RABM_RELEASE_RRC_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

    /* 填写相关参数 */
    pstSndMsg->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSndMsg->stMsgHeader.ulReceiverPid     = AT_GetDestPid(usClientId, I0_WUEPS_PID_RABM);
    pstSndMsg->stMsgHeader.ulLength          = sizeof(AT_RABM_RELEASE_RRC_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstSndMsg->stMsgHeader.ulMsgName         = ID_AT_RABM_SET_RELEASE_RRC_REQ;
    pstSndMsg->usClientId                    = usClientId;
    pstSndMsg->ucOpId                        = ucOpId;

    /* 调用VOS发送原语 */
    ulRslt = PS_SEND_MSG(WUEPS_PID_AT, pstSndMsg);
    if ( VOS_OK != ulRslt )
    {
        AT_ERR_LOG("At_SndReleaseRrcReq:ERROR:PS_SEND_MSG ");
        return VOS_ERR;
    }

    return VOS_OK;
}

#if (FEATURE_ON == FEATURE_HUAWEI_VP)
/*****************************************************************************
 函 数 名  : AT_SndSetVoicePrefer
 功能描述  : 发送AP status mask
 输入参数  : usClientId      - 用户client id
             ucOpId          - 操作ID
             pstVpEnablePara - AT命令操作的参数
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月26日
    作    者   : s00273135
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_SndSetVoicePrefer (
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT32                          ulVoicePreferApStatus
)
{
    AT_RABM_SET_VOICEPREFER_PARA_REQ_STRU                  *pstSndMsg = VOS_NULL_PTR;
    VOS_UINT32                                              ulRslt;

    /* 申请内存  */
    pstSndMsg = (AT_RABM_SET_VOICEPREFER_PARA_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_AT,
                                               sizeof(AT_RABM_SET_VOICEPREFER_PARA_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if ( VOS_NULL_PTR == pstSndMsg )
    {
        /* 内存申请失败 */
        AT_ERR_LOG("AT_SndSetVoicePrefer:ERROR: Memory Alloc Error for pstMsg");
        return VOS_ERR;
    }

    /* 填写相关参数 */
    pstSndMsg->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSndMsg->stMsgHeader.ulReceiverPid     = AT_GetDestPid(usClientId, I0_WUEPS_PID_RABM);
    pstSndMsg->stMsgHeader.ulLength          = sizeof(AT_RABM_SET_VOICEPREFER_PARA_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstSndMsg->stMsgHeader.ulMsgName         = ID_AT_RABM_SET_VOICEPREFER_PARA_REQ;
    pstSndMsg->usClientId                    = usClientId;
    pstSndMsg->ucOpId                        = ucOpId;

    pstSndMsg->ulVoicePreferApStatus         = ulVoicePreferApStatus;

    /* 调用VOS发送原语 */
    ulRslt = PS_SEND_MSG(WUEPS_PID_AT, pstSndMsg);
    if ( VOS_OK != ulRslt )
    {
        AT_ERR_LOG("AT_SndSetVoicePrefer:ERROR:PS_SEND_MSG ");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_SndQryVoicePrefer
 功能描述  : 查询当前VoicePrefer的设置
 输入参数  : usClientId      - 用户client id
             ucOpId          - 操作ID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月26日
    作    者   : s00273135
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_SndQryVoicePrefer (
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    AT_RABM_QRY_VOICEPREFER_PARA_REQ_STRU                  *pstSndMsg = VOS_NULL_PTR;
    VOS_UINT32                                              ulRslt;

    /* 申请内存  */
    pstSndMsg = (AT_RABM_QRY_VOICEPREFER_PARA_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_AT,
                                               sizeof(AT_RABM_QRY_VOICEPREFER_PARA_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if ( VOS_NULL_PTR == pstSndMsg )
    {
        /* 内存申请失败 */
        AT_ERR_LOG("AT_SndQryVoicePrefer:ERROR: Memory Alloc Error for pstMsg");
        return VOS_ERR;
    }

    /* 填写相关参数 */
    pstSndMsg->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSndMsg->stMsgHeader.ulReceiverPid     = AT_GetDestPid(usClientId, I0_WUEPS_PID_RABM);
    pstSndMsg->stMsgHeader.ulLength          = sizeof(AT_RABM_QRY_VOICEPREFER_PARA_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstSndMsg->stMsgHeader.ulMsgName         = ID_AT_RABM_QRY_VOICEPREFER_PARA_REQ;
    pstSndMsg->usClientId                    = usClientId;
    pstSndMsg->ucOpId                        = ucOpId;

    /* 调用VOS发送原语 */
    ulRslt = PS_SEND_MSG(WUEPS_PID_AT, pstSndMsg);
    if ( VOS_OK != ulRslt )
    {
        AT_ERR_LOG("AT_SndQryVoicePrefer:ERROR:PS_SEND_MSG ");
        return VOS_ERR;
    }

    return VOS_OK;
}
#endif

/*****************************************************************************
 函 数 名  : AT_FillAndSndCSIMAMsg
 功能描述  : AT到CCIMA模块消息
 输入参数  : VIA Modem 复位状态

 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月20日
    作    者   : d00212987
    修改内容   : V9R1 L_plus_C项目新增

*****************************************************************************/
VOS_UINT32 AT_FillAndSndCSIMAMsg(VOS_UINT16 usClinetID, VOS_UINT32 ulModemStatus)
{
    AT_CSIMA_RESET_STATUS_IND_MSG_STRU  *pstATCSIMAIndMsg;
    MODEM_ID_ENUM_UINT16                enModemID;

    /* 调用接口获取Modem ID */
    if(VOS_OK != AT_GetModemIdFromClient(usClinetID,&enModemID))
    {
        AT_ERR_LOG("AT_FillAndSndCSIMAMsg:ERROR: AT_GetModemIdFromClient Error");
        return VOS_ERR;
    }

    /* 申请内存  */
    pstATCSIMAIndMsg = (AT_CSIMA_RESET_STATUS_IND_MSG_STRU *)PS_ALLOC_MSG(WUEPS_PID_AT,
                                               sizeof(AT_CSIMA_RESET_STATUS_IND_MSG_STRU) - VOS_MSG_HEAD_LENGTH);
    if ( VOS_NULL_PTR == pstATCSIMAIndMsg )
    {
        /* 内存申请失败 */
        AT_ERR_LOG("AT_FillAndSndCSIMAMsg:ERROR: Memory Alloc Error for pstMsg");
        return VOS_ERR;
    }

    /* 填写相关参数 */
    if (MODEM_ID_1 == enModemID)
    {
        pstATCSIMAIndMsg->ulReceiverPid     = I1_WUEPS_PID_CSIMA;
    }
    else
    {
        pstATCSIMAIndMsg->ulReceiverPid     = I0_WUEPS_PID_CSIMA;
    }

    pstATCSIMAIndMsg->ulMsgId           = AT_CSIMA_RESET_IND_MSG;
    pstATCSIMAIndMsg->enVIAModemStatus  = (CBP_MODEM_RESET_STATUS_ENUM_UINT32)ulModemStatus;

    /* 调用VOS发送原语 */
    return PS_SEND_MSG(WUEPS_PID_AT, pstATCSIMAIndMsg);
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif