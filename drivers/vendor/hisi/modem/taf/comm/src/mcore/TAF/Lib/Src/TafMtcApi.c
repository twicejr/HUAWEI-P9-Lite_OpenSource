


/*****************************************************************************
   1 头文件包含
*****************************************************************************/
#include "PsCommonDef.h"

#include "TafMtcApi.h"




#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_MTC_API_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/

#if (FEATURE_MULTI_MODEM == FEATURE_ON)

/*****************************************************************************
   2 全局变量定义
*****************************************************************************/
#if (OSA_CPU_ACPU == VOS_OSA_CPU)
    extern VOS_UINT32 AT_GetDestPid(
        MN_CLIENT_ID_T                      usClientId,
        VOS_UINT32                          ulRcvPid
    );
#endif

/*****************************************************************************
   3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : MTC_SndMsg
 功能描述  : 发送MTC消息
 输入参数  : VOS_UINT32                          ulTaskId
             VOS_UINT32                          ulMsgId
             VOS_VOID                           *pData
             VOS_UINT32                          ulLen
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年06月16日
    作    者   : j00174725
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 MTC_SndMsg(
    VOS_UINT32                          ulTaskId,
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pData,
    VOS_UINT32                          ulLength
)
{
    TAF_PS_MSG_STRU                    *pstMsg   = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;

    ulResult = VOS_OK;

    /* 构造消息 */
    pstMsg = (TAF_PS_MSG_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                UEPS_PID_MTC,
                                sizeof(MSG_HEADER_STRU) + ulLength);
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_ERR;
    }

    pstMsg->stHeader.ulReceiverPid      = UEPS_PID_MTC;
    pstMsg->stHeader.ulMsgName          = ulMsgId;

    /* 填写消息内容 */
    PS_MEM_CPY(pstMsg->aucContent, pData, ulLength);

    /* 发送消息 */
    ulResult = PS_SEND_MSG(UEPS_PID_MTC, pstMsg);
    if (VOS_OK != ulResult)
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : MTC_SetCdmaServiceConnStateInfo
 功能描述  : 设置外部CDMA Modem的连接状态(PS&CS)
 输入参数  : ulModuleId                 - 模块ID(发送Pid)
             usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
             pstCdmsStatus              - 状态信息指针
 输出参数  : 无
 返 回 值  : VOS_OK                     - 发送消息成功
             VOS_ERR                    - 发送消息失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年06月16日
    作    者   : j00174725
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 MTC_SetCdmaServiceConnStateInfo(
    TAF_CTRL_STRU                      *pstCtrl,
    TAF_MTC_CDMA_STATE_INFO_STRU       *pstCdmaState
)
{
    TAF_MTC_CDMA_STATE_IND_STRU         stSetCdmaConnSt;
    VOS_UINT32                          ulResult;

    /* 初始化 */
    ulResult = VOS_OK;
    PS_MEM_SET(&stSetCdmaConnSt, 0x00, sizeof(TAF_MTC_CDMA_STATE_IND_STRU));

    /* 构造ID_MSG_MTC_CDMA_CONN_STATUS消息 */
    TAF_API_CTRL_HEADER(&stSetCdmaConnSt.stCtrl, pstCtrl->ulModuleId,
                        pstCtrl->usClientId, pstCtrl->ucOpId);

    PS_MEM_CPY(&stSetCdmaConnSt.stCdmaState, pstCdmaState, sizeof(TAF_MTC_CDMA_STATE_INFO_STRU));

    /* 发送消息 */
    ulResult = MTC_SndMsg(UEPS_PID_MTC,
                         ID_MSG_MTC_CDMA_CONN_STATE_IND,
                         &stSetCdmaConnSt,
                         sizeof(TAF_MTC_CDMA_STATE_IND_STRU));

    return ulResult;
}

/*****************************************************************************
 函 数 名  : MTC_SetModemServiceConnState
 功能描述  : 设置modem状态信息
 输入参数  : pstCtrl         消息控制头
             pstModemConnSt  状态消息指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年06月16日
    作    者   : j00174725
    修改内容   : K3V3 多模多天线特性
*****************************************************************************/
VOS_UINT32 MTC_SetModemServiceConnState(
    TAF_CTRL_STRU                      *pstCtrl,
    TAF_MTC_SRV_CONN_STATE_INFO_STRU   *pstModemConnSt
)
{
    TAF_MTC_MODEM_CONN_STATUS_IND_STRU  stModemConnSt;
    VOS_UINT32                          ulResult;

    /* 初始化 */
    ulResult = VOS_OK;
    PS_MEM_SET(&stModemConnSt, 0x00, sizeof(TAF_MTC_MODEM_CONN_STATUS_IND_STRU));

    /* 构造ID_MSG_MTC_CDMA_CONN_STATUS消息 */
    TAF_API_CTRL_HEADER(&(stModemConnSt.stCtrl), pstCtrl->ulModuleId, pstCtrl->usClientId, pstCtrl->ucOpId);

    PS_MEM_CPY(&stModemConnSt.stModemConnStateInfo, pstModemConnSt, sizeof(TAF_MTC_SRV_CONN_STATE_INFO_STRU));

    /* 发送消息 */
    ulResult = MTC_SndMsg(UEPS_PID_MTC,
                         ID_MSG_MTC_MODEM_SERVICE_CONN_STATE_IND,
                         &stModemConnSt,
                         sizeof(TAF_MTC_MODEM_CONN_STATUS_IND_STRU));

    return ulResult;
}

/*****************************************************************************
 函 数 名  : MTC_SetModemUsimmState
 功能描述  : 设置卡状态信息
 输入参数  : pstCtrl         消息控制头
             pstModemConnSt  状态消息指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年06月16日
    作    者   : j00174725
    修改内容   : K3V3 多模多天线特性

  2.日    期   : 2015年10月21日
    作    者   : h00313353
    修改内容   : Iteration 19 TAS
*****************************************************************************/
VOS_UINT32 MTC_SetModemUsimmState(
    TAF_CTRL_STRU                           *pstCtrl,
    TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16    enUsimState,
    TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16    enCsimState
)
{
    TAF_MTC_USIMM_STATUS_IND_STRU       stUsimmState;
    VOS_UINT32                          ulResult;

    /* 初始化 */
    ulResult = VOS_OK;
    PS_MEM_SET(&stUsimmState, 0x00, sizeof(TAF_MTC_USIMM_STATUS_IND_STRU));

    /* 构造ID_MSG_MTC_CDMA_CONN_STATUS消息 */
    TAF_API_CTRL_HEADER(&(stUsimmState.stCtrl), pstCtrl->ulModuleId, pstCtrl->usClientId, pstCtrl->ucOpId);

    stUsimmState.enUsimState = enUsimState;
    stUsimmState.enCsimState = enCsimState;

    /* 发送消息 */
    ulResult = MTC_SndMsg(UEPS_PID_MTC,
                          ID_MSG_MTC_USIMM_STATE_IND,
                          &stUsimmState,
                          sizeof(TAF_MTC_USIMM_STATUS_IND_STRU));

    return ulResult;
}

/*****************************************************************************
 函 数 名  : MTC_SetBeginSessionInfo
 功能描述  : 对外提供API，外部模块调用这个函数通知MTC ID_MSG_MTC_BEGIN_SESSION_IND消息
 输入参数  : pstCtrl         消息控制头
             enSessionType   类型消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月04日
    作    者   : j00174725
    修改内容   : DTS2015082406288
*****************************************************************************/
VOS_VOID MTC_SetBeginSessionInfo(
    TAF_CTRL_STRU                      *pstCtrl,
    MTC_SESSION_TYPE_ENUM_UINT8         enSessionType
)
{
    MTC_BEGIN_SESSION_IND_STRU          stSessionInfo;

    /* 初始化 */
    PS_MEM_SET(&stSessionInfo, 0x00, sizeof(MTC_BEGIN_SESSION_IND_STRU));

    /* 构造ID_MSG_MTC_BEGIN_SESSION_IND消息 */
    TAF_API_CTRL_HEADER(&(stSessionInfo.stCtrl), pstCtrl->ulModuleId, pstCtrl->usClientId, pstCtrl->ucOpId);

    stSessionInfo.enSessionType = enSessionType;

    /* 发送消息 */
    MTC_SndMsg(UEPS_PID_MTC,
               ID_MSG_MTC_BEGIN_SESSION_IND,
               &stSessionInfo,
               sizeof(MTC_BEGIN_SESSION_IND_STRU));

    return;
}

/*****************************************************************************
 函 数 名  : MTC_SetEndSessionInfo
 功能描述  : 对外提供API，外部模块调用这个函数通知MTC ID_MSG_MTC_END_SESSION_IND消息
 输入参数  : pstCtrl         消息控制头
             enSessionType   类型消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月04日
    作    者   : j00174725
    修改内容   : DTS2015082406288
*****************************************************************************/
VOS_VOID MTC_SetEndSessionInfo(
    TAF_CTRL_STRU                      *pstCtrl,
    MTC_SESSION_TYPE_ENUM_UINT8         enSessionType
)
{
    MTC_END_SESSION_IND_STRU            stEndSessionInfo;

    /* 初始化 */
    PS_MEM_SET(&stEndSessionInfo, 0x00, sizeof(MTC_END_SESSION_IND_STRU));

    /* 构造ID_MSG_MTC_END_SESSION_IND消息 */
    TAF_API_CTRL_HEADER(&(stEndSessionInfo.stCtrl), pstCtrl->ulModuleId, pstCtrl->usClientId, pstCtrl->ucOpId);

    stEndSessionInfo.enSessionType  = enSessionType;
    stEndSessionInfo.enCsRelAll     = VOS_FALSE;
    stEndSessionInfo.enPsRelAll     = VOS_FALSE;

    /* 发送消息 */
    MTC_SndMsg(UEPS_PID_MTC,
               ID_MSG_MTC_END_SESSION_IND,
               &stEndSessionInfo,
               sizeof(MTC_BEGIN_SESSION_IND_STRU));

    return;
}
#endif


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

