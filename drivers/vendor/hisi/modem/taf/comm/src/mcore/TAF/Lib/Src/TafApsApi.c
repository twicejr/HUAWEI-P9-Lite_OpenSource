


/*****************************************************************************
   1 头文件包含
*****************************************************************************/


#include "PsCommonDef.h"
#include "TafApsApi.h"
#if (OSA_CPU_CCPU == VOS_OSA_CPU)
#include "Taf_Aps.h"
#include "TafApsMntn.h"
#endif



#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*lint -e958*/

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_API_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/


/*****************************************************************************
   2 全局变量定义
*****************************************************************************/


/*****************************************************************************
   3 外部函数声明
*****************************************************************************/

#if (OSA_CPU_ACPU == VOS_OSA_CPU)
extern VOS_UINT32 AT_GetDestPid(
    MN_CLIENT_ID_T                      usClientId,
    VOS_UINT32                          ulRcvPid
);
#endif


/*****************************************************************************
   4 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : TAF_PS_SndMsg
 功能描述  : 发送PS域消息
 输入参数  : VOS_UINT32                          ulTaskId
             VOS_UINT32                          ulMsgId
             VOS_VOID                           *pData
             VOS_UINT32                          ulLen
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月8日
    作    者   : A00165503
    修改内容   : 新生成函数
  2.日    期   : 2012年12月21日
    作    者   : l00227485
    修改内容   : DSDA PhaseII
*****************************************************************************/
VOS_UINT32 TAF_PS_SndMsg(
    VOS_UINT32                          ulTaskId,
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pData,
    VOS_UINT32                          ulLength
)
{
    VOS_UINT32                          ulResult = 0;
    TAF_PS_MSG_STRU                    *pstMsg   = VOS_NULL_PTR;
    VOS_UINT32                          ulPid;

#if (OSA_CPU_ACPU == VOS_OSA_CPU)
    TAF_CTRL_STRU                      *pstCtrl  = VOS_NULL_PTR;

    pstCtrl = (TAF_CTRL_STRU *)pData;

    /* 填写消息头 */
    ulPid = AT_GetDestPid(pstCtrl->usClientId, ulTaskId);
#else
    ulPid = WUEPS_PID_TAF;
#endif

    /* 构造消息 */
    pstMsg = (TAF_PS_MSG_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                ulPid,
                                sizeof(MSG_HEADER_STRU) + ulLength);
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_ERR;
    }

    pstMsg->stHeader.ulReceiverPid      = ulPid;
    pstMsg->stHeader.ulMsgName          = ulMsgId;

    /* 填写消息内容 */
    PS_MEM_CPY(pstMsg->aucContent, pData, ulLength);

    /* 发送消息 */
    ulResult = PS_SEND_MSG(ulPid, pstMsg);
    if (VOS_OK != ulResult)
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_PS_SetPrimPdpContextInfo
 功能描述  : 设置Primary PDP上下文信息
 输入参数  : usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
             pstPdpContextInfo          - Primary PDP上下文信息
 输出参数  : 无
 返 回 值  : VOS_OK                     - 发送消息成功
             VOS_ERR                    - 发送消息失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月5日
    作    者   : A00165503
    修改内容   : 新生成函数
  2.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，结构名称修改，增加PID

*****************************************************************************/
VOS_UINT32 TAF_PS_SetPrimPdpContextInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_PDP_PRIM_CONTEXT_EXT_STRU      *pstPdpContextInfo
)
{
    VOS_UINT32                                  ulResult;
    TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_REQ_STRU   stSetPdpCtxInfoReq;

    /* 初始化 */
    ulResult = VOS_OK;
    PS_MEM_SET(&stSetPdpCtxInfoReq, 0x00, sizeof(TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_REQ_STRU));

    /* 构造ID_MSG_TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_REQ消息 */
    stSetPdpCtxInfoReq.stCtrl.ulModuleId = ulModuleId;
    stSetPdpCtxInfoReq.stCtrl.usClientId = usClientId;
    stSetPdpCtxInfoReq.stCtrl.ucOpId     = ucOpId;
    stSetPdpCtxInfoReq.stPdpContextInfo  = *pstPdpContextInfo;

    /* 发送消息 */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_REQ,
                             &stSetPdpCtxInfoReq,
                             sizeof(TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_PS_GetPrimPdpContextInfo
 功能描述  : 获取Primary PDP上下文信息
 输入参数  : usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
 输出参数  : 无
 返 回 值  : VOS_OK                     - 发送消息成功
             VOS_ERR                    - 发送消息失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月5日
    作    者   : A00165503
    修改内容   : 新生成函数
  2.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，结构名称修改，增加PID

*****************************************************************************/
VOS_UINT32 TAF_PS_GetPrimPdpContextInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    VOS_UINT32                                  ulResult;
    TAF_PS_GET_PRIM_PDP_CONTEXT_INFO_REQ_STRU   stGetPdpCtxInfoReq;

    /* 初始化 */
    ulResult = VOS_OK;
    PS_MEM_SET(&stGetPdpCtxInfoReq, 0x00, sizeof(TAF_PS_GET_PRIM_PDP_CONTEXT_INFO_REQ_STRU));

    /* 构造ID_MSG_TAF_PS_GET_PRIM_PDP_CONTEXT_INFO_REQ消息 */
    stGetPdpCtxInfoReq.stCtrl.ulModuleId = ulModuleId;
    stGetPdpCtxInfoReq.stCtrl.usClientId = usClientId;
    stGetPdpCtxInfoReq.stCtrl.ucOpId     = ucOpId;

    /* 发送消息 */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_GET_PRIM_PDP_CONTEXT_INFO_REQ,
                             &stGetPdpCtxInfoReq,
                             sizeof(TAF_PS_GET_PRIM_PDP_CONTEXT_INFO_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_PS_GetPdpContextInfo
 功能描述  : 获取主和从 PDP上下文信息
 输入参数  : usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
 输出参数  : 无
 返 回 值  : VOS_OK                     - 发送消息成功
             VOS_ERR                    - 发送消息失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月5日
    作    者   : c00173809
    修改内容   : DTS2012010604900
*****************************************************************************/
VOS_UINT32 TAF_PS_GetPdpContextInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    VOS_UINT32                                  ulResult;
    TAF_PS_GET_PDP_CONTEXT_INFO_REQ_STRU        stGetPdpCtxInfoReq;

    /* 初始化 */
    ulResult = VOS_OK;
    PS_MEM_SET(&stGetPdpCtxInfoReq, 0x00, sizeof(TAF_PS_GET_PDP_CONTEXT_INFO_REQ_STRU));

    /* 构造ID_MSG_TAF_PS_GET_PRIM_PDP_CONTEXT_INFO_REQ消息 */
    stGetPdpCtxInfoReq.stCtrl.ulModuleId = ulModuleId;
    stGetPdpCtxInfoReq.stCtrl.usClientId = usClientId;
    stGetPdpCtxInfoReq.stCtrl.ucOpId     = ucOpId;

    /* 发送消息 */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_GET_PDPCONT_INFO_REQ,
                             &stGetPdpCtxInfoReq,
                             sizeof(TAF_PS_GET_PDP_CONTEXT_INFO_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_PS_SetSecPdpContextInfo
 功能描述  : 设置Secondary PDP上下文信息
 输入参数  : usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
             pstPdpContextInfo          - Secondary PDP上下文信息
 输出参数  : 无
 返 回 值  : VOS_OK                     - 发送消息成功
             VOS_ERR                    - 发送消息失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月5日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_PS_SetSecPdpContextInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_PDP_SEC_CONTEXT_EXT_STRU       *pstPdpContextInfo
)
{
    VOS_UINT32                                  ulResult;
    TAF_PS_SET_SEC_PDP_CONTEXT_INFO_REQ_STRU    stSetPdpCtxInfoReq;

    /* 初始化 */
    ulResult = VOS_OK;
    PS_MEM_SET(&stSetPdpCtxInfoReq, 0x00, sizeof(TAF_PS_SET_SEC_PDP_CONTEXT_INFO_REQ_STRU));

    /* 构造ID_MSG_TAF_PS_SET_SEC_PDP_CONTEXT_INFO_REQ消息 */
    stSetPdpCtxInfoReq.stCtrl.ulModuleId = ulModuleId;
    stSetPdpCtxInfoReq.stCtrl.usClientId = usClientId;
    stSetPdpCtxInfoReq.stCtrl.ucOpId     = ucOpId;
    stSetPdpCtxInfoReq.stPdpContextInfo  = *pstPdpContextInfo;

    /* 发送消息 */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_SET_SEC_PDP_CONTEXT_INFO_REQ,
                             &stSetPdpCtxInfoReq,
                             sizeof(TAF_PS_SET_SEC_PDP_CONTEXT_INFO_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_PS_GetSecPdpContextInfo
 功能描述  : 获取Secondary PDP上下文信息
 输入参数  : usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月5日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_PS_GetSecPdpContextInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    VOS_UINT32                                  ulResult;
    TAF_PS_GET_SEC_PDP_CONTEXT_INFO_REQ_STRU    stGetPdpCtxInfoReq;

    /* 初始化 */
    ulResult = VOS_OK;
    PS_MEM_SET(&stGetPdpCtxInfoReq, 0x00, sizeof(TAF_PS_GET_SEC_PDP_CONTEXT_INFO_REQ_STRU));

    /* 构造ID_MSG_TAF_PS_GET_SEC_PDP_CONTEXT_INFO_REQ消息 */
    stGetPdpCtxInfoReq.stCtrl.ulModuleId = ulModuleId;
    stGetPdpCtxInfoReq.stCtrl.usClientId = usClientId;
    stGetPdpCtxInfoReq.stCtrl.ucOpId     = ucOpId;

    /* 发送消息 */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_GET_SEC_PDP_CONTEXT_INFO_REQ,
                             &stGetPdpCtxInfoReq,
                             sizeof(TAF_PS_GET_SEC_PDP_CONTEXT_INFO_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_PS_SetTftInfo
 功能描述  : 设置PDP TFT参数
 输入参数  : usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
             pstTftInfo                 - TFT参数
 输出参数  : 无
 返 回 值  : VOS_OK                     - 发送消息成功
             VOS_ERR                    - 发送消息失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月5日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_PS_SetTftInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_TFT_EXT_STRU                   *pstTftInfo
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_SET_TFT_INFO_REQ_STRU        stSetTftInfoReq;

    /* 初始化 */
    ulResult = VOS_OK;
    PS_MEM_SET(&stSetTftInfoReq, 0x00, sizeof(TAF_PS_SET_TFT_INFO_REQ_STRU));

    /* 构造ID_MSG_TAF_PS_SET_TFT_INFO_REQ消息 */
    stSetTftInfoReq.stCtrl.ulModuleId = ulModuleId;
    stSetTftInfoReq.stCtrl.usClientId = usClientId;
    stSetTftInfoReq.stCtrl.ucOpId     = ucOpId;
    stSetTftInfoReq.stTftInfo         = *pstTftInfo;

    /* 发送消息 */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_SET_TFT_INFO_REQ,
                             &stSetTftInfoReq,
                             sizeof(TAF_PS_SET_TFT_INFO_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_PS_GetTftInfo
 功能描述  : 获取PDP TFT参数
 输入参数  : usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
 输出参数  : 无
 返 回 值  : VOS_OK                     - 发送消息成功
             VOS_ERR                    - 发送消息失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月5日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_PS_GetTftInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_GET_TFT_INFO_REQ_STRU        stGetTftInfoReq;

    /* 初始化 */
    ulResult = VOS_OK;
    PS_MEM_SET(&stGetTftInfoReq, 0x00, sizeof(TAF_PS_GET_TFT_INFO_REQ_STRU));

    /* 构造ID_MSG_TAF_PS_GET_SEC_PDP_CONTEXT_INFO_REQ消息 */
    stGetTftInfoReq.stCtrl.ulModuleId = ulModuleId;
    stGetTftInfoReq.stCtrl.usClientId = usClientId;
    stGetTftInfoReq.stCtrl.ucOpId     = ucOpId;

    /* 发送消息 */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_GET_TFT_INFO_REQ,
                             &stGetTftInfoReq,
                             sizeof(TAF_PS_GET_TFT_INFO_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_PS_SetUmtsQosInfo
 功能描述  : 设置UMTS QOS参数信息
 输入参数  : usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
             pstUmtsQosInfo             - UMTS QOS参数
 输出参数  : 无
 返 回 值  : VOS_OK                     - 发送消息成功
             VOS_ERR                    - 发送消息失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月5日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_PS_SetUmtsQosInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_UMTS_QOS_EXT_STRU              *pstUmtsQosInfo
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_SET_UMTS_QOS_INFO_REQ_STRU   stSetUmtsQosInfoReq;

    /* 初始化 */
    ulResult = VOS_OK;
    PS_MEM_SET(&stSetUmtsQosInfoReq, 0x00, sizeof(TAF_PS_SET_UMTS_QOS_INFO_REQ_STRU));

    /* 构造ID_MSG_TAF_PS_SET_UMTS_QOS_INFO_REQ消息 */
    stSetUmtsQosInfoReq.stCtrl.ulModuleId = ulModuleId;
    stSetUmtsQosInfoReq.stCtrl.usClientId = usClientId;
    stSetUmtsQosInfoReq.stCtrl.ucOpId     = ucOpId;
    stSetUmtsQosInfoReq.stUmtsQosInfo     = *pstUmtsQosInfo;

    /* 发送消息 */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_SET_UMTS_QOS_INFO_REQ,
                             &stSetUmtsQosInfoReq,
                             sizeof(TAF_PS_SET_UMTS_QOS_INFO_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_PS_GetUmtsQosInfo
 功能描述  : 获取UMTS QOS参数信息
 输入参数  : usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
 输出参数  : 无
 返 回 值  : VOS_OK                     - 发送消息成功
             VOS_ERR                    - 发送消息失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月5日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_PS_GetUmtsQosInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_GET_UMTS_QOS_INFO_REQ_STRU   stGetUmtsQosInfoReq;

    /* 初始化 */
    ulResult = VOS_OK;
    PS_MEM_SET(&stGetUmtsQosInfoReq, 0x00, sizeof(TAF_PS_GET_UMTS_QOS_INFO_REQ_STRU));

    /* 构造ID_MSG_TAF_PS_GET_UMTS_QOS_INFO_REQ消息 */
    stGetUmtsQosInfoReq.stCtrl.ulModuleId = ulModuleId;
    stGetUmtsQosInfoReq.stCtrl.usClientId = usClientId;
    stGetUmtsQosInfoReq.stCtrl.ucOpId     = ucOpId;

    /* 发送消息 */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_GET_UMTS_QOS_INFO_REQ,
                             &stGetUmtsQosInfoReq,
                             sizeof(TAF_PS_GET_UMTS_QOS_INFO_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_PS_SetUmtsQosMinInfo
 功能描述  : 设置UMTS MIN QOS参数信息
 输入参数  : usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
             pstUmtsQosMinInfo          - UMTS MIN QOS参数
 输出参数  : 无
 返 回 值  : VOS_OK                     - 发送消息成功
             VOS_ERR                    - 发送消息失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月5日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_PS_SetUmtsQosMinInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_UMTS_QOS_EXT_STRU              *pstUmtsQosMinInfo
)
{
    VOS_UINT32                              ulResult;
    TAF_PS_SET_UMTS_QOS_MIN_INFO_REQ_STRU   stSetUmtsQosMinInfoReq;

    /* 初始化 */
    ulResult = VOS_OK;
    PS_MEM_SET(&stSetUmtsQosMinInfoReq, 0x00, sizeof(TAF_PS_SET_UMTS_QOS_MIN_INFO_REQ_STRU));

    /* 构造ID_MSG_TAF_PS_SET_UMTS_QOS_MIN_INFO_REQ消息 */
    stSetUmtsQosMinInfoReq.stCtrl.ulModuleId = ulModuleId;
    stSetUmtsQosMinInfoReq.stCtrl.usClientId = usClientId;
    stSetUmtsQosMinInfoReq.stCtrl.ucOpId     = ucOpId;
    stSetUmtsQosMinInfoReq.stUmtsQosMinInfo  = *pstUmtsQosMinInfo;

    /* 发送消息 */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_SET_UMTS_QOS_MIN_INFO_REQ,
                             &stSetUmtsQosMinInfoReq,
                             sizeof(TAF_PS_SET_UMTS_QOS_MIN_INFO_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_PS_GetUmtsQosMinInfo
 功能描述  : 获取UMTS MIN QOS参数信息
 输入参数  : usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
 输出参数  : 无
 返 回 值  : VOS_OK                     - 发送消息成功
             VOS_ERR                    - 发送消息失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月5日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_PS_GetUmtsQosMinInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    VOS_UINT32                              ulResult;
    TAF_PS_GET_UMTS_QOS_MIN_INFO_REQ_STRU   stGetUmtsQosMinInfoReq;

    /* 初始化 */
    ulResult = VOS_OK;
    PS_MEM_SET(&stGetUmtsQosMinInfoReq, 0x00, sizeof(TAF_PS_GET_UMTS_QOS_MIN_INFO_REQ_STRU));

    /* 构造ID_MSG_TAF_PS_GET_UMTS_QOS_MIN_INFO_REQ消息 */
    stGetUmtsQosMinInfoReq.stCtrl.ulModuleId = ulModuleId;
    stGetUmtsQosMinInfoReq.stCtrl.usClientId = usClientId;
    stGetUmtsQosMinInfoReq.stCtrl.ucOpId     = ucOpId;

    /* 发送消息 */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_GET_UMTS_QOS_MIN_INFO_REQ,
                             &stGetUmtsQosMinInfoReq,
                             sizeof(TAF_PS_GET_UMTS_QOS_MIN_INFO_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_PS_GetDynamicUmtsQosInfo
 功能描述  : 获取动态UMTS QOS参数信息
 输入参数  : usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
             pstCidListInfo             - CID列表
 输出参数  : 无
 返 回 值  : VOS_OK                     - 发送消息成功
             VOS_ERR                    - 发送消息失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月5日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_PS_GetDynamicUmtsQosInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_CID_LIST_STRU                  *pstCidListInfo
)
{
    VOS_UINT32                                  ulResult;
    TAF_PS_GET_DYNAMIC_UMTS_QOS_INFO_REQ_STRU   stGetDynamicUmtsQosInfoReq;

    /* 初始化 */
    ulResult = VOS_OK;
    PS_MEM_SET(&stGetDynamicUmtsQosInfoReq, 0x00, sizeof(TAF_PS_GET_DYNAMIC_UMTS_QOS_INFO_REQ_STRU));

    /* 构造ID_MSG_TAF_PS_GET_DYNAMIC_UMTS_QOS_INFO_REQ消息 */
    stGetDynamicUmtsQosInfoReq.stCtrl.ulModuleId = ulModuleId;
    stGetDynamicUmtsQosInfoReq.stCtrl.usClientId = usClientId;
    stGetDynamicUmtsQosInfoReq.stCtrl.ucOpId     = ucOpId;
    stGetDynamicUmtsQosInfoReq.stCidListInfo     = *pstCidListInfo;

    /* 发送消息 */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_GET_DYNAMIC_UMTS_QOS_INFO_REQ,
                             &stGetDynamicUmtsQosInfoReq,
                             sizeof(TAF_PS_GET_DYNAMIC_UMTS_QOS_INFO_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_PS_SetPdpContextState
 功能描述  : 设置指定CID(表)对应的PDP的状态
 输入参数  : usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
             pstCidListStateInfo        - CID列表状态
 输出参数  : 无
 返 回 值  : VOS_OK                     - 发送消息成功
             VOS_ERR                    - 发送消息失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月5日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_PS_SetPdpContextState(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_CID_LIST_STATE_STRU            *pstCidListStateInfo
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_SET_PDP_STATE_REQ_STRU       stSetPdpStateReq;

    /* 初始化 */
    ulResult = VOS_OK;
    PS_MEM_SET(&stSetPdpStateReq, 0x00, sizeof(TAF_PS_SET_PDP_STATE_REQ_STRU));

    /* 构造ID_MSG_TAF_PS_SET_PDP_STATE_REQ消息 */
    stSetPdpStateReq.stCtrl.ulModuleId = ulModuleId;
    stSetPdpStateReq.stCtrl.usClientId = usClientId;
    stSetPdpStateReq.stCtrl.ucOpId     = ucOpId;
    stSetPdpStateReq.stCidListStateInfo   = *pstCidListStateInfo;

    /* 发送消息 */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ,
                             &stSetPdpStateReq,
                             sizeof(TAF_PS_SET_PDP_STATE_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_PS_GetPdpContextState
 功能描述  : 获取所有已定义CID对应的PDP的状态
 输入参数  : usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
 输出参数  : 无
 返 回 值  : VOS_OK                     - 发送消息成功
             VOS_ERR                    - 发送消息失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月5日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_PS_GetPdpContextState(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_GET_PDP_STATE_REQ_STRU       stGetPdpStateReq;

    /* 初始化 */
    ulResult = VOS_OK;
    PS_MEM_SET(&stGetPdpStateReq, 0x00, sizeof(TAF_PS_GET_PDP_STATE_REQ_STRU));

    /* 构造ID_MSG_TAF_PS_GET_PDP_STATE_REQ消息 */
    stGetPdpStateReq.stCtrl.ulModuleId = ulModuleId;
    stGetPdpStateReq.stCtrl.usClientId = usClientId;
    stGetPdpStateReq.stCtrl.ucOpId     = ucOpId;

    /* 发送消息 */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_GET_PDP_CONTEXT_STATE_REQ,
                             &stGetPdpStateReq,
                             sizeof(TAF_PS_GET_PDP_STATE_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_PS_CallModify
 功能描述  : 修改PS CALL参数
 输入参数  : usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
             TAF_CID_LIST_STRU          - CID列表
 输出参数  : 无
 返 回 值  : VOS_OK                     - 发送消息成功
             VOS_ERR                    - 发送消息失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月5日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_PS_CallModify(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_CID_LIST_STRU                  *pstCidListInfo
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_MODIFY_REQ_STRU         stCallModifyReq;

    /* 初始化 */
    ulResult = VOS_OK;
    PS_MEM_SET(&stCallModifyReq, 0x00, sizeof(TAF_PS_CALL_MODIFY_REQ_STRU));

    /* 构造ID_MSG_TAF_PS_CALL_MODIFY_REQ消息 */
    stCallModifyReq.stCtrl.ulModuleId = ulModuleId;
    stCallModifyReq.stCtrl.usClientId = usClientId;
    stCallModifyReq.stCtrl.ucOpId     = ucOpId;
    stCallModifyReq.stCidListInfo     = *pstCidListInfo;

    /* 发送消息 */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_CALL_MODIFY_REQ,
                             &stCallModifyReq,
                             sizeof(TAF_PS_CALL_MODIFY_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_PS_CallAnswer
 功能描述  : 应答PS CALL
 输入参数  : usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
             pstAnsInfo                 - PS CALL应答信息
 输出参数  : 无
 返 回 值  : VOS_OK                     - 发送消息成功
             VOS_ERR                    - 发送消息失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月5日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_PS_CallAnswer(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_PS_ANSWER_STRU                 *pstAnsInfo
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_ANSWER_REQ_STRU         stCallAnswerReq;

    /* 初始化 */
    ulResult = VOS_OK;
    PS_MEM_SET(&stCallAnswerReq, 0x00, sizeof(TAF_PS_CALL_ANSWER_REQ_STRU));

    /* 构造ID_MSG_TAF_PS_CALL_ANSWER_REQ消息 */
    stCallAnswerReq.stCtrl.ulModuleId = ulModuleId;
    stCallAnswerReq.stCtrl.usClientId = usClientId;
    stCallAnswerReq.stCtrl.ucOpId     = ucOpId;
    stCallAnswerReq.stAnsInfo         = *pstAnsInfo;

    /* 发送消息 */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_CALL_ANSWER_REQ,
                             &stCallAnswerReq,
                             sizeof(TAF_PS_CALL_ANSWER_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_PS_CallHangup
 功能描述  : 挂断PS CALL
 输入参数  : usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
 输出参数  : 无
 返 回 值  : VOS_OK                     - 发送消息成功
             VOS_ERR                    - 发送消息失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月5日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_PS_CallHangup(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_HANGUP_REQ_STRU         stCallHangupReq;

    /* 初始化 */
    ulResult = VOS_OK;
    PS_MEM_SET(&stCallHangupReq, 0x00, sizeof(TAF_PS_CALL_HANGUP_REQ_STRU));

    /* 构造ID_MSG_TAF_PS_CALL_HANGUP_REQ消息 */
    stCallHangupReq.stCtrl.ulModuleId = ulModuleId;
    stCallHangupReq.stCtrl.usClientId = usClientId;
    stCallHangupReq.stCtrl.ucOpId     = ucOpId;

    /* 发送消息 */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_CALL_HANGUP_REQ,
                             &stCallHangupReq,
                             sizeof(TAF_PS_CALL_HANGUP_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_PS_CallOrig
 功能描述  : 发起PS CALL
 输入参数  : usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
             pstDialParaInfo            - PS CALL参数
 输出参数  : 无
 返 回 值  : VOS_OK                     - 发送消息成功
             VOS_ERR                    - 发送消息失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月5日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_PS_CallOrig(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_PS_DIAL_PARA_STRU              *pstDialParaInfo
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_ORIG_REQ_STRU           stCallOrigReq;

    /* 初始化 */
    ulResult = VOS_OK;
    PS_MEM_SET(&stCallOrigReq, 0x00, sizeof(TAF_PS_CALL_ORIG_REQ_STRU));

    /* 构造ID_MSG_TAF_PS_CALL_ORIG_REQ消息 */
    stCallOrigReq.stCtrl.ulModuleId = ulModuleId;
    stCallOrigReq.stCtrl.usClientId = usClientId;
    stCallOrigReq.stCtrl.ucOpId     = ucOpId;
    stCallOrigReq.stDialParaInfo    = *pstDialParaInfo;

    /* 发送消息 */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_CALL_ORIG_REQ,
                             &stCallOrigReq,
                             sizeof(TAF_PS_CALL_ORIG_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_PS_CallEnd
 功能描述  : 结束PS CALL
 输入参数  : usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
             ucCid                      - CID
 输出参数  : 无
 返 回 值  : VOS_OK                     - 发送消息成功
             VOS_ERR                    - 发送消息失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月5日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_PS_CallEnd(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucCid
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_END_REQ_STRU            stCallEndReq;

    /* 初始化 */
    ulResult = VOS_OK;
    PS_MEM_SET(&stCallEndReq, 0x00, sizeof(TAF_PS_CALL_END_REQ_STRU));

    /* 构造ID_MSG_TAF_PS_CALL_END_REQ消息 */
    stCallEndReq.stCtrl.ulModuleId = ulModuleId;
    stCallEndReq.stCtrl.usClientId = usClientId;
    stCallEndReq.stCtrl.ucOpId     = ucOpId;
    stCallEndReq.ucCid             = ucCid;

    /* 发送消息 */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_CALL_END_REQ,
                             &stCallEndReq,
                             sizeof(TAF_PS_CALL_END_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_PS_GetPdpIpAddrInfo
 功能描述  : 获取指定CID(表)的PDP IP地址信息
 输入参数  : usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
             pstCidListInfo             - CID列表
输出参数  : 无
 返 回 值  : VOS_OK                     - 发送消息成功
             VOS_ERR                    - 发送消息失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月5日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_PS_GetPdpIpAddrInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_CID_LIST_STRU                  *pstCidListInfo
)
{
    VOS_UINT32                              ulResult;
    TAF_PS_GET_PDP_IP_ADDR_INFO_REQ_STRU    stGetPdpIpAddrReq;

    /* 初始化 */
    ulResult = VOS_OK;
    PS_MEM_SET(&stGetPdpIpAddrReq, 0x00, sizeof(TAF_PS_GET_PDP_IP_ADDR_INFO_REQ_STRU));

    /* 构造ID_MSG_TAF_PS_GET_PDP_IP_ADDR_INFO_REQ消息 */
    stGetPdpIpAddrReq.stCtrl.ulModuleId = ulModuleId;
    stGetPdpIpAddrReq.stCtrl.usClientId = usClientId;
    stGetPdpIpAddrReq.stCtrl.ucOpId     = ucOpId;
    stGetPdpIpAddrReq.stCidListInfo     = *pstCidListInfo;

    /* 发送消息 */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_GET_PDP_IP_ADDR_INFO_REQ,
                             &stGetPdpIpAddrReq,
                             sizeof(TAF_PS_GET_PDP_IP_ADDR_INFO_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_PS_SetAnsModeInfo
 功能描述  : 设置PS域呼叫应答模式信息
 输入参数  : usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
             ulAnsMode                  - 应答模式信息
 输出参数  : 无
 返 回 值  : VOS_OK                     - 发送消息成功
             VOS_ERR                    - 发送消息失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月5日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_PS_SetAnsModeInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT32                          ulAnsMode
)
{
    VOS_UINT32                              ulResult;
    TAF_PS_SET_ANSWER_MODE_INFO_REQ_STRU    stSetAnsModeReq;

    /* 初始化 */
    ulResult = VOS_OK;
    PS_MEM_SET(&stSetAnsModeReq, 0x00, sizeof(TAF_PS_SET_ANSWER_MODE_INFO_REQ_STRU));

    /* 构造ID_MSG_TAF_PS_SET_ANSWER_MODE_INFO_REQ消息 */
    stSetAnsModeReq.stCtrl.ulModuleId = ulModuleId;
    stSetAnsModeReq.stCtrl.usClientId = usClientId;
    stSetAnsModeReq.stCtrl.ucOpId     = ucOpId;
    stSetAnsModeReq.ulAnsMode         = ulAnsMode;

    /* 发送消息 */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_SET_ANSWER_MODE_INFO_REQ,
                             &stSetAnsModeReq,
                             sizeof(TAF_PS_SET_ANSWER_MODE_INFO_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_PS_GetAnsModeInfo
 功能描述  : 获取PS域呼叫应答模式信息
 输入参数  : usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
 输出参数  : 无
 返 回 值  : VOS_OK                     - 发送消息成功
             VOS_ERR                    - 发送消息失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月5日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_PS_GetAnsModeInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    VOS_UINT32                              ulResult;
    TAF_PS_GET_ANSWER_MODE_INFO_REQ_STRU    stGetAnsModeReq;

    /* 初始化 */
    ulResult = VOS_OK;
    PS_MEM_SET(&stGetAnsModeReq, 0x00, sizeof(TAF_PS_GET_ANSWER_MODE_INFO_REQ_STRU));

    /* 构造ID_MSG_TAF_PS_SET_ANSWER_MODE_INFO_REQ消息 */
    stGetAnsModeReq.stCtrl.ulModuleId   = ulModuleId;
    stGetAnsModeReq.stCtrl.usClientId   = usClientId;
    stGetAnsModeReq.stCtrl.ucOpId       = ucOpId;

    /* 发送消息 */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_GET_ANSWER_MODE_INFO_REQ,
                             &stGetAnsModeReq,
                             sizeof(TAF_PS_GET_ANSWER_MODE_INFO_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_PS_GetDynamicPrimPdpContextInfo
 功能描述  : 获取指定的已定义CID的动态Primary PDP上下文信息
 输入参数  : usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
             ucCid                      - CID
 输出参数  : 无
 返 回 值  : VOS_OK                     - 发送消息成功
             VOS_ERR                    - 发送消息失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月5日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_PS_GetDynamicPrimPdpContextInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucCid
)
{
    VOS_UINT32                                          ulResult;
    TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_REQ_STRU   stGetDynamicPrimPdpCtxInfoReq;

    /* 初始化 */
    ulResult = VOS_OK;
    PS_MEM_SET(&stGetDynamicPrimPdpCtxInfoReq, 0x00, sizeof(TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_REQ_STRU));

    /* 构造ID_MSG_TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_REQ消息 */
    stGetDynamicPrimPdpCtxInfoReq.stCtrl.ulModuleId = ulModuleId;
    stGetDynamicPrimPdpCtxInfoReq.stCtrl.usClientId = usClientId;
    stGetDynamicPrimPdpCtxInfoReq.stCtrl.ucOpId     = ucOpId;
    stGetDynamicPrimPdpCtxInfoReq.ucCid             = ucCid;

    /* 发送消息 */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_REQ,
                             &stGetDynamicPrimPdpCtxInfoReq,
                             sizeof(TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_PS_GetDynamicSecPdpContextInfo
 功能描述  : 获取指定的已定义CID的动态Secondary PDP上下文信息
 输入参数  : usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
             ucCid                      - CID
 输出参数  : 无
 返 回 值  : VOS_OK                     - 发送消息成功
             VOS_ERR                    - 发送消息失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月5日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_PS_GetDynamicSecPdpContextInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucCid
)
{
    VOS_UINT32                                          ulResult;
    TAF_PS_GET_DYNAMIC_SEC_PDP_CONTEXT_INFO_REQ_STRU    stGetDynamicSecPdpCtxInfoReq;

    /* 初始化 */
    ulResult = VOS_OK;
    PS_MEM_SET(&stGetDynamicSecPdpCtxInfoReq, 0x00, sizeof(TAF_PS_GET_DYNAMIC_SEC_PDP_CONTEXT_INFO_REQ_STRU));

    /* 构造ID_MSG_TAF_PS_GET_DYNAMIC_SEC_PDP_CONTEXT_INFO_REQ消息 */
    stGetDynamicSecPdpCtxInfoReq.stCtrl.ulModuleId = ulModuleId;
    stGetDynamicSecPdpCtxInfoReq.stCtrl.usClientId = usClientId;
    stGetDynamicSecPdpCtxInfoReq.stCtrl.ucOpId     = ucOpId;
    stGetDynamicSecPdpCtxInfoReq.ucCid             = ucCid;

    /* 发送消息 */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_GET_DYNAMIC_SEC_PDP_CONTEXT_INFO_REQ,
                             &stGetDynamicSecPdpCtxInfoReq,
                             sizeof(TAF_PS_GET_DYNAMIC_SEC_PDP_CONTEXT_INFO_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_PS_GetDynamicTftInfo
 功能描述  : 获取指定的已定义CID的动态TFT信息
 输入参数  : usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
             ucCid                      - CID
 输出参数  : 无
 返 回 值  : VOS_OK                     - 发送消息成功
             VOS_ERR                    - 发送消息失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月5日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_PS_GetDynamicTftInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucCid
)
{
    VOS_UINT32                              ulResult;
    TAF_PS_GET_DYNAMIC_TFT_INFO_REQ_STRU    stGetDynamicTftInfoReq;

    /* 初始化 */
    ulResult = VOS_OK;
    PS_MEM_SET(&stGetDynamicTftInfoReq, 0x00, sizeof(TAF_PS_GET_DYNAMIC_TFT_INFO_REQ_STRU));

    /* 构造ID_MSG_TAF_PS_GET_DYNAMIC_TFT_INFO_REQ消息 */
    stGetDynamicTftInfoReq.stCtrl.ulModuleId = ulModuleId;
    stGetDynamicTftInfoReq.stCtrl.usClientId = usClientId;
    stGetDynamicTftInfoReq.stCtrl.ucOpId     = ucOpId;
    stGetDynamicTftInfoReq.ucCid             = ucCid;

    /* 发送消息 */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_GET_DYNAMIC_TFT_INFO_REQ,
                             &stGetDynamicTftInfoReq,
                             sizeof(TAF_PS_GET_DYNAMIC_TFT_INFO_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_PS_SetEpsQosInfo
 功能描述  : 设置指定CID的EPS QOS参数信息
 输入参数  : usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
             pstEpsQosInfo              - EPS QOS参数信息
 输出参数  : 无
 返 回 值  : VOS_OK                     - 发送消息成功
             VOS_ERR                    - 发送消息失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月5日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_PS_SetEpsQosInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_EPS_QOS_EXT_STRU               *pstEpsQosInfo
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_SET_EPS_QOS_INFO_REQ_STRU    stSetEpsQosInfoReq;

    /* 初始化 */
    ulResult = VOS_OK;
    PS_MEM_SET(&stSetEpsQosInfoReq, 0x00, sizeof(TAF_PS_SET_EPS_QOS_INFO_REQ_STRU));

    /* 构造ID_MSG_TAF_PS_SET_EPS_QOS_INFO_REQ消息 */
    stSetEpsQosInfoReq.stCtrl.ulModuleId = ulModuleId;
    stSetEpsQosInfoReq.stCtrl.usClientId = usClientId;
    stSetEpsQosInfoReq.stCtrl.ucOpId     = ucOpId;
    stSetEpsQosInfoReq.stEpsQosInfo      = *pstEpsQosInfo;

    /* 发送消息 */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_SET_EPS_QOS_INFO_REQ,
                             &stSetEpsQosInfoReq,
                             sizeof(TAF_PS_SET_EPS_QOS_INFO_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_PS_GetEpsQosInfo
 功能描述  : 获取EPS QOS参数信息
 输入参数  : usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
 输出参数  : 无
 返 回 值  : VOS_OK                     - 发送消息成功
             VOS_ERR                    - 发送消息失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月5日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_PS_GetEpsQosInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_GET_EPS_QOS_INFO_REQ_STRU    stGetEpsQosInfoReq;

    /* 初始化 */
    ulResult = VOS_OK;
    PS_MEM_SET(&stGetEpsQosInfoReq, 0x00, sizeof(TAF_PS_GET_EPS_QOS_INFO_REQ_STRU));

    /* 构造ID_MSG_TAF_PS_GET_EPS_QOS_INFO_REQ消息 */
    stGetEpsQosInfoReq.stCtrl.ulModuleId = ulModuleId;
    stGetEpsQosInfoReq.stCtrl.usClientId = usClientId;
    stGetEpsQosInfoReq.stCtrl.ucOpId     = ucOpId;

    /* 发送消息 */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_GET_EPS_QOS_INFO_REQ,
                             &stGetEpsQosInfoReq,
                             sizeof(TAF_PS_GET_EPS_QOS_INFO_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_PS_GetDynamicEpsQosInfo
 功能描述  : 获取指定的已定义CID的动态EPS QOS参数
 输入参数  : usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
             ucCid                      - CID
 输出参数  : 无
 返 回 值  : VOS_OK                     - 发送消息成功
             VOS_ERR                    - 发送消息失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月5日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_PS_GetDynamicEpsQosInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucCid
)
{
    VOS_UINT32                                  ulResult;
    TAF_PS_GET_DYNAMIC_EPS_QOS_INFO_REQ_STRU    stGetDynamicEpsQosInfoReq;

    /* 初始化 */
    ulResult = VOS_OK;
    PS_MEM_SET(&stGetDynamicEpsQosInfoReq, 0x00, sizeof(TAF_PS_GET_DYNAMIC_EPS_QOS_INFO_REQ_STRU));

    /* 构造ID_MSG_TAF_PS_GET_DYNAMIC_EPS_QOS_INFO_REQ消息 */
    stGetDynamicEpsQosInfoReq.stCtrl.ulModuleId = ulModuleId;
    stGetDynamicEpsQosInfoReq.stCtrl.usClientId = usClientId;
    stGetDynamicEpsQosInfoReq.stCtrl.ucOpId     = ucOpId;
    stGetDynamicEpsQosInfoReq.ucCid             = ucCid;

    /* 发送消息 */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_GET_DYNAMIC_EPS_QOS_INFO_REQ,
                             &stGetDynamicEpsQosInfoReq,
                             sizeof(TAF_PS_GET_DYNAMIC_EPS_QOS_INFO_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_PS_GetDsFlowInfo
 功能描述  : 获取数据流量信息
 输入参数  : usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
             pstQueryConfigInfo         - DSFLOW查询配置参数
 输出参数  : 无
 返 回 值  : VOS_OK                     - 发送消息成功
             VOS_ERR                    - 发送消息失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月5日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_PS_GetDsFlowInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_GET_DSFLOW_INFO_REQ_STRU     stGetDsFlowInfoReq;

    /* 初始化 */
    ulResult = VOS_OK;
    PS_MEM_SET(&stGetDsFlowInfoReq, 0x00, sizeof(TAF_PS_GET_DSFLOW_INFO_REQ_STRU));

    /* 构造ID_MSG_TAF_PS_GET_DSFLOW_INFO_REQ消息 */
    stGetDsFlowInfoReq.stCtrl.ulModuleId = ulModuleId;
    stGetDsFlowInfoReq.stCtrl.usClientId = usClientId;
    stGetDsFlowInfoReq.stCtrl.ucOpId     = ucOpId;

    /* 发送消息 */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_GET_DSFLOW_INFO_REQ,
                             &stGetDsFlowInfoReq,
                             sizeof(TAF_PS_GET_DSFLOW_INFO_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_PS_ClearDsFlowInfo
 功能描述  : 清除数据流量信息
 输入参数  : usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
             pstClearConfigInfo         - 流量清除配置参数信息
 输出参数  : 无
 返 回 值  : VOS_OK                     - 发送消息成功
             VOS_ERR                    - 发送消息失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月5日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_PS_ClearDsFlowInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_DSFLOW_CLEAR_CONFIG_STRU       *pstClearConfigInfo
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_CLEAR_DSFLOW_REQ_STRU        stClearDsFlowReq;

    /* 初始化 */
    ulResult = VOS_OK;
    PS_MEM_SET(&stClearDsFlowReq, 0x00, sizeof(TAF_PS_CLEAR_DSFLOW_REQ_STRU));

    /* 构造ID_MSG_TAF_PS_CLEAR_DSFLOW_REQ消息 */
    stClearDsFlowReq.stCtrl.ulModuleId = ulModuleId;
    stClearDsFlowReq.stCtrl.usClientId = usClientId;
    stClearDsFlowReq.stCtrl.ucOpId     = ucOpId;
    stClearDsFlowReq.stClearConfigInfo = *pstClearConfigInfo;

    /* 发送消息 */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_CLEAR_DSFLOW_REQ,
                             &stClearDsFlowReq,
                             sizeof(TAF_PS_CLEAR_DSFLOW_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_PS_ConfigDsFlowRpt
 功能描述  : 配置流量上报模式
 输入参数  : usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
             pstReportConfigInfo        - 流量上报配置参数信息
 输出参数  : 无
 返 回 值  : VOS_OK                     - 发送消息成功
             VOS_ERR                    - 发送消息失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月5日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_PS_ConfigDsFlowRpt(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_DSFLOW_REPORT_CONFIG_STRU      *pstReportConfigInfo
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_CONFIG_DSFLOW_RPT_REQ_STRU   stConfigDsFlowRptReq;

    /* 初始化 */
    ulResult = VOS_OK;
    PS_MEM_SET(&stConfigDsFlowRptReq, 0x00, sizeof(TAF_PS_CONFIG_DSFLOW_RPT_REQ_STRU));

    /* 构造ID_MSG_TAF_PS_CONFIG_DSFLOW_RPT_REQ消息 */
    stConfigDsFlowRptReq.stCtrl.ulModuleId = ulModuleId;
    stConfigDsFlowRptReq.stCtrl.usClientId = usClientId;
    stConfigDsFlowRptReq.stCtrl.ucOpId     = ucOpId;
    stConfigDsFlowRptReq.stReportConfigInfo   = *pstReportConfigInfo;

    /* 发送消息 */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_CONFIG_DSFLOW_RPT_REQ,
                             &stConfigDsFlowRptReq,
                             sizeof(TAF_PS_CONFIG_DSFLOW_RPT_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_PS_SetPdpDnsInfo
 功能描述  : 设置PDP DNS信息
 输入参数  : usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
             pstPdpDnsInfo              - PDP DNS信息
 输出参数  : 无
 返 回 值  : VOS_OK                     - 发送消息成功
             VOS_ERR                    - 发送消息失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月5日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_PS_SetPdpDnsInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_PDP_DNS_EXT_STRU               *pstPdpDnsInfo
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_SET_PDP_DNS_INFO_REQ_STRU    stSetPdpDnsInfoReq;

    /* 初始化 */
    ulResult = VOS_OK;
    PS_MEM_SET(&stSetPdpDnsInfoReq, 0x00, sizeof(TAF_PS_SET_PDP_DNS_INFO_REQ_STRU));

    /* 构造ID_MSG_TAF_PS_SET_PDP_DNS_INFO_REQ消息 */
    stSetPdpDnsInfoReq.stCtrl.ulModuleId = ulModuleId;
    stSetPdpDnsInfoReq.stCtrl.usClientId = usClientId;
    stSetPdpDnsInfoReq.stCtrl.ucOpId     = ucOpId;
    stSetPdpDnsInfoReq.stPdpDnsInfo      = *pstPdpDnsInfo;

    /* 发送消息 */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_SET_PDP_DNS_INFO_REQ,
                             &stSetPdpDnsInfoReq,
                             sizeof(TAF_PS_SET_PDP_DNS_INFO_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_PS_GetPdpDnsInfo
 功能描述  : 获取PDP DNS信息
 输入参数  : usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
 输出参数  : 无
 返 回 值  : VOS_OK                     - 发送消息成功
             VOS_ERR                    - 发送消息失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月5日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_PS_GetPdpDnsInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_GET_PDP_DNS_INFO_REQ_STRU    stGetPdpDnsInfoReq;

    /* 初始化 */
    ulResult = VOS_OK;
    PS_MEM_SET(&stGetPdpDnsInfoReq, 0x00, sizeof(TAF_PS_GET_PDP_DNS_INFO_REQ_STRU));

    /* 构造ID_MSG_TAF_PS_GET_PDP_DNS_INFO_REQ消息 */
    stGetPdpDnsInfoReq.stCtrl.ulModuleId = ulModuleId;
    stGetPdpDnsInfoReq.stCtrl.usClientId = usClientId;
    stGetPdpDnsInfoReq.stCtrl.ucOpId     = ucOpId;

    /* 发送消息 */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_GET_PDP_DNS_INFO_REQ,
                             &stGetPdpDnsInfoReq,
                             sizeof(TAF_PS_GET_PDP_DNS_INFO_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_PS_TrigGprsData
 功能描述  : 发送上行GPRS数据
 输入参数  : usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
             pstGprsDataInfo            - GPRS数据信息
 输出参数  : 无
 返 回 值  : VOS_OK                     - 发送消息成功
             VOS_ERR                    - 发送消息失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月5日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_PS_TrigGprsData(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_GPRS_DATA_STRU                 *pstGprsDataInfo
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_TRIG_GPRS_DATA_REQ_STRU      stTrigGprsDataReq;

    /* 初始化 */
    ulResult = VOS_OK;
    PS_MEM_SET(&stTrigGprsDataReq, 0x00, sizeof(TAF_PS_TRIG_GPRS_DATA_REQ_STRU));

    /* 构造ID_MSG_TAF_PS_TRIG_GPRS_DATA_REQ消息 */
    stTrigGprsDataReq.stCtrl.ulModuleId = ulModuleId;
    stTrigGprsDataReq.stCtrl.usClientId = usClientId;
    stTrigGprsDataReq.stCtrl.ucOpId     = ucOpId;
    stTrigGprsDataReq.stGprsDataInfo    = *pstGprsDataInfo;

    /* 发送消息 */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_TRIG_GPRS_DATA_REQ,
                             &stTrigGprsDataReq,
                             sizeof(TAF_PS_TRIG_GPRS_DATA_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_PS_ConfigNbnsFunction
 功能描述  : 配置NBNS功能
 输入参数  : usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
             ulEnabled                  - NBNS功能使能标记
 输出参数  : 无
 返 回 值  : VOS_OK                     - 发送消息成功
             VOS_ERR                    - 发送消息失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月5日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_PS_ConfigNbnsFunction(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT32                          ulEnabled
)
{
    VOS_UINT32                              ulResult;
    TAF_PS_CONFIG_NBNS_FUNCTION_REQ_STRU    stConfigNbnsFunReq;

    /* 初始化 */
    ulResult = VOS_OK;
    PS_MEM_SET(&stConfigNbnsFunReq, 0x00, sizeof(TAF_PS_CONFIG_NBNS_FUNCTION_REQ_STRU));

    /* 构造ID_MSG_TAF_PS_CONFIG_NBNS_FUNCTION_REQ消息 */
    stConfigNbnsFunReq.stCtrl.ulModuleId = ulModuleId;
    stConfigNbnsFunReq.stCtrl.usClientId = usClientId;
    stConfigNbnsFunReq.stCtrl.ucOpId     = ucOpId;
    stConfigNbnsFunReq.ulEnabled         = ulEnabled;

    /* 发送消息 */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_CONFIG_NBNS_FUNCTION_REQ,
                             &stConfigNbnsFunReq,
                             sizeof(TAF_PS_CONFIG_NBNS_FUNCTION_REQ_STRU));

    return ulResult;
}

/* Deleted by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
/* Deleted by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

/*****************************************************************************
 函 数 名  : TAF_PS_SetAuthDataInfo
 功能描述  : 设置鉴权参数信息(NDIS)
 输入参数  : usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
             pstAuthDataInfo            - 鉴权参数
 输出参数  : 无
 返 回 值  : VOS_OK                     - 发送消息成功
             VOS_ERR                    - 发送消息失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月5日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_PS_SetAuthDataInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_AUTHDATA_EXT_STRU              *pstAuthDataInfo
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_SET_AUTHDATA_INFO_REQ_STRU   stSetAuthDataInfoReq;

    /* 初始化 */
    ulResult = VOS_OK;
    PS_MEM_SET(&stSetAuthDataInfoReq, 0x00, sizeof(TAF_PS_SET_AUTHDATA_INFO_REQ_STRU));

    /* 构造ID_MSG_TAF_PS_SET_AUTHDATA_INFO_REQ消息 */
    stSetAuthDataInfoReq.stCtrl.ulModuleId = ulModuleId;
    stSetAuthDataInfoReq.stCtrl.usClientId = usClientId;
    stSetAuthDataInfoReq.stCtrl.ucOpId     = ucOpId;
    stSetAuthDataInfoReq.stAuthDataInfo    = *pstAuthDataInfo;

    /* 发送消息 */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_SET_AUTHDATA_INFO_REQ,
                             &stSetAuthDataInfoReq,
                             sizeof(TAF_PS_SET_AUTHDATA_INFO_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_PS_GetAuthDataInfo
 功能描述  : 获取鉴权参数信息(NDIS)
 输入参数  : usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
 输出参数  : 无
 返 回 值  : VOS_OK                     - 发送消息成功
             VOS_ERR                    - 发送消息失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月5日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_PS_GetAuthDataInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_GET_AUTHDATA_INFO_REQ_STRU   stGetAuthDataInfoReq;

    /* 初始化 */
    ulResult = VOS_OK;
    PS_MEM_SET(&stGetAuthDataInfoReq, 0x00, sizeof(TAF_PS_GET_AUTHDATA_INFO_REQ_STRU));

    /* 构造ID_MSG_TAF_PS_GET_AUTHDATA_INFO_REQ消息 */
    stGetAuthDataInfoReq.stCtrl.ulModuleId = ulModuleId;
    stGetAuthDataInfoReq.stCtrl.usClientId = usClientId;
    stGetAuthDataInfoReq.stCtrl.ucOpId     = ucOpId;

    /* 发送消息 */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_GET_AUTHDATA_INFO_REQ,
                             &stGetAuthDataInfoReq,
                             sizeof(TAF_PS_GET_AUTHDATA_INFO_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_PS_GetGprsActiveType
 功能描述  : 获取D命令GPRS类型(PPP拨号)
 输入参数  : usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
             pstAtdPara                 - D命令拨号参数
 输出参数  : 无
 返 回 值  : VOS_OK                     - 发送消息成功
             VOS_ERR                    - 发送消息失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月5日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_PS_GetGprsActiveType(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_ATD_PARA_STRU                  *pstAtdPara
)
{
    VOS_UINT32                              ulResult;
    TAF_PS_GET_D_GPRS_ACTIVE_TYPE_REQ_STRU  stGetGprsActiveTypeReq;

    /* 初始化 */
    ulResult = VOS_OK;
    PS_MEM_SET(&stGetGprsActiveTypeReq, 0x00, sizeof(TAF_PS_GET_D_GPRS_ACTIVE_TYPE_REQ_STRU));

    /* 构造ID_MSG_TAF_PS_GET_AUTHDATA_INFO_REQ消息 */
    stGetGprsActiveTypeReq.stCtrl.ulModuleId = ulModuleId;
    stGetGprsActiveTypeReq.stCtrl.usClientId = usClientId;
    stGetGprsActiveTypeReq.stCtrl.ucOpId     = ucOpId;
    stGetGprsActiveTypeReq.stAtdPara         = *pstAtdPara;

    /* 发送消息 */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_GET_D_GPRS_ACTIVE_TYPE_REQ,
                             &stGetGprsActiveTypeReq,
                             sizeof(TAF_PS_GET_D_GPRS_ACTIVE_TYPE_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_PS_PppDialOrig
 功能描述  : 发起PPP拨号
 输入参数  : usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
             ucCid                      - CID
             pstPppReqConfigInfo        - PPP配置参数
 输出参数  : 无
 返 回 值  : VOS_OK                     - 发送消息成功
             VOS_ERR                    - 发送消息失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月5日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2014年5月16日
    作    者   : A00165503
    修改内容   : DTS2014050703206: PPP拨号接口调整
*****************************************************************************/
VOS_UINT32 TAF_PS_PppDialOrig(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucCid,
    TAF_PPP_REQ_CONFIG_INFO_STRU       *pstPppReqConfigInfo
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU       stPppDialOrigReq;

    /* 初始化 */
    ulResult = VOS_OK;
    PS_MEM_SET(&stPppDialOrigReq, 0x00, sizeof(TAF_PS_PPP_DIAL_ORIG_REQ_STRU));

    /* 构造ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ消息 */
    stPppDialOrigReq.stCtrl.ulModuleId          = ulModuleId;
    stPppDialOrigReq.stCtrl.usClientId          = usClientId;
    stPppDialOrigReq.stCtrl.ucOpId              = ucOpId;

    stPppDialOrigReq.stPppDialParaInfo.ucCid    = ucCid;

    stPppDialOrigReq.stPppDialParaInfo.bitOpPppConfigInfo = VOS_TRUE;
    PS_MEM_CPY(&(stPppDialOrigReq.stPppDialParaInfo.stPppReqConfigInfo),
               pstPppReqConfigInfo,
               sizeof(TAF_PPP_REQ_CONFIG_INFO_STRU));

    /* 发送消息 */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ,
                             &stPppDialOrigReq,
                             sizeof(TAF_PS_PPP_DIAL_ORIG_REQ_STRU));

    return ulResult;
}

#if(FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
函 数 名  : TAF_PS_GetLteCsInfo
功能描述  : 获取LTE CS Info
输入参数  : 无
输出参数  : 无
返 回 值  : VOS_OK                     - 发送消息成功
            VOS_ERR                    - 发送消息失败
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2012年02月23日
   作    者   : h00135900
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_PS_GetLteCsInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId

)
{
    VOS_UINT32                                  ulResult;
    TAF_PS_LTECS_REQ_STRU   stGetLteCsInfoReq;

    /* 初始化 */
    ulResult = VOS_OK;
    PS_MEM_SET(&stGetLteCsInfoReq, 0x00, sizeof(TAF_PS_LTECS_REQ_STRU));

    /* 构造ID_MSG_TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_REQ消息 */
    stGetLteCsInfoReq.stCtrl.ulModuleId = ulModuleId;
    stGetLteCsInfoReq.stCtrl.usClientId = usClientId;
    stGetLteCsInfoReq.stCtrl.ucOpId     = ucOpId;


    /* 发送消息 */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_GET_LTE_CS_REQ,
                             &stGetLteCsInfoReq,
                             sizeof(TAF_PS_LTECS_REQ_STRU));


    return ulResult;
}

/*****************************************************************************
函 数 名  : TAF_PS_GetCemodeInfo
功能描述  : 获取CEMODE Info
输入参数  : 无
输出参数  : 无
返 回 值  : VOS_OK                     - 发送消息成功
            VOS_ERR                    - 发送消息失败
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2012年03月20日
   作    者   : w00182550
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_PS_GetCemodeInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    VOS_UINT32                                  ulResult;
    TAF_PS_CEMODE_REQ_STRU   stGetCemodeInfoReq;



    /* 初始化 */
    ulResult = VOS_OK;
    PS_MEM_SET(&stGetCemodeInfoReq, 0x00, sizeof(TAF_PS_CEMODE_REQ_STRU));

    /* 构造ID_MSG_TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_REQ消息 */
    stGetCemodeInfoReq.stCtrl.ulModuleId = ulModuleId;
    stGetCemodeInfoReq.stCtrl.usClientId = usClientId;
    stGetCemodeInfoReq.stCtrl.ucOpId     = ucOpId;


    /* 发送消息 */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_GET_CEMODE_REQ,
                             &stGetCemodeInfoReq,
                             sizeof(TAF_PS_CEMODE_REQ_STRU));


    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_PS_SetPdpProfInfo
 功能描述  : 设置PDP_Profile 参数
 输入参数  : usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
             stPdpProfInfo            - PDP_Profile 参数
 输出参数  : 无
 返 回 值  : VOS_OK                     - 发送消息成功
             VOS_ERR                    - 发送消息失败
 调用函数  :
 被调函数  :

 修改历史      :
 日    期   : 2012年3月12日
 作    者   : x00126983
 修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_PS_SetPdpProfInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_PDP_PROFILE_EXT_STRU           *stPdpProfInfo
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_SET_PROFILE_INFO_REQ_STRU    stSetPdpProfInfoReq;

    /* 初始化 */
    ulResult = VOS_OK;
    PS_MEM_SET(&stSetPdpProfInfoReq, 0x00, sizeof(TAF_PS_SET_PROFILE_INFO_REQ_STRU));

    /* 构造ID_MSG_TAF_PS_SET_AUTHDATA_INFO_REQ消息 */
    stSetPdpProfInfoReq.stCtrl.ulModuleId = ulModuleId;
    stSetPdpProfInfoReq.stCtrl.usClientId = usClientId;
    stSetPdpProfInfoReq.stCtrl.ucOpId     = ucOpId;
    stSetPdpProfInfoReq.stPdpProfInfo     = *stPdpProfInfo;

    /* 发送消息 */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_SET_PDPROFMOD_INFO_REQ,
                             &stSetPdpProfInfoReq,
                             sizeof(TAF_PS_SET_PROFILE_INFO_REQ_STRU));

    return ulResult;
}
#endif

/*****************************************************************************
 函 数 名  : TAF_PS_GetCidSdfParaInfo
 功能描述  : 获取所有NV项中的SDF配置信息, 支持同步和异步两种方式
             输出参数非空 --- 同步方式(目前仅支持C核)
             输出参数为空 --- 异步方式
 输入参数  : ulModuleId                 - 填写PID
             usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
 输出参数  : pstSdfQueryInfo            - SDF配置信息
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败

修改历史  :

1.日    期   : 2013年07月08日
  作    者   : Y00213812
  修改内容   : VoLTE_PhaseI 项目，新增API

*****************************************************************************/
VOS_UINT32 TAF_PS_GetCidSdfParaInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_SDF_PARA_QUERY_INFO_STRU       *pstSdfQueryInfo
)
{
#if (OSA_CPU_CCPU == VOS_OSA_CPU)
    VOS_UINT8                           ucNum;
#endif
    VOS_UINT32                          ulResult;
    TAF_PS_SDF_INFO_REQ_STRU            stSdfInfoReq;

    ulResult = VOS_ERR;
    PS_MEM_SET(&stSdfInfoReq, 0x00, sizeof(TAF_PS_SDF_INFO_REQ_STRU));

    /* 如果出参为空，则采用异步方式获取SDF信息 */
    if (VOS_NULL_PTR == pstSdfQueryInfo)
    {
        /* 构造ID_MSG_TAF_GET_CID_SDF_REQ消息 */
        stSdfInfoReq.stCtrl.ulModuleId = ulModuleId;
        stSdfInfoReq.stCtrl.usClientId = usClientId;
        stSdfInfoReq.stCtrl.ucOpId     = ucOpId;

        /* 发送消息 */
        ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                                 ID_MSG_TAF_PS_GET_CID_SDF_REQ,
                                 &stSdfInfoReq,
                                 sizeof(TAF_PS_SDF_INFO_REQ_STRU));

        return ulResult;
    }

    PS_MEM_SET(pstSdfQueryInfo, 0, sizeof(TAF_SDF_PARA_QUERY_INFO_STRU));
/* 同步方式目前仅支持C核 */
#if (OSA_CPU_CCPU == VOS_OSA_CPU)
    for (ucNum = 1; ucNum <= TAF_MAX_CID_NV; ucNum++)
    {
        if (VOS_OK == TAF_APS_GetSdfParaInfo(ucNum,
                              &(pstSdfQueryInfo->astSdfPara[pstSdfQueryInfo->ulSdfNum])))
        {
            pstSdfQueryInfo->ulSdfNum ++;
        }
    }
    ulResult = VOS_OK;

    /* 同步消息勾包 */
    TAF_APS_TraceSyncMsg(ID_MSG_TAF_PS_GET_CID_SDF_REQ,
                         (VOS_UINT8 *)pstSdfQueryInfo,
                         sizeof(TAF_SDF_PARA_QUERY_INFO_STRU));
#endif

    return ulResult;
}


/*****************************************************************************
 函 数 名  : TAF_PS_GetUnusedCid
 功能描述  : 获取空闲未激活的CID
             输出参数非空 --- 同步方式(目前仅支持C核)
             输出参数为空 --- 异步方式
 输入参数  : ulModuleId                 - 填写PID
             usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
 输出参数  : puCid                      - 空闲未激活CID
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败

 修改历史  :

 1.日    期   : 2013年07月08日
   作    者   : Y00213812
   修改内容   : VoLTE_PhaseI 项目，新增API
*****************************************************************************/
VOS_UINT32 TAF_PS_GetUnusedCid(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                          *puCid
)
{
    VOS_UINT32                          ulResult;

    ulResult = VOS_OK;

    if (VOS_NULL_PTR == puCid)
    {
        /* 目前暂不支持异步方式 */
        return VOS_ERR;
    }

/* 同步方式目前仅支持C核 */
#if (OSA_CPU_CCPU == VOS_OSA_CPU)
    /* 需找可用于拨号的CID */
    *puCid = TAF_APS_FindCidForDial(ulModuleId);
    if ( TAF_INVALID_CID == *puCid )
    {
        ulResult = VOS_ERR;
    }

    /* 同步消息勾包 */
    TAF_APS_TraceSyncMsg(ID_MSG_TAF_PS_GET_UNUSED_CID_REQ,
                         puCid,
                         sizeof(VOS_UINT8));
#endif

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_PS_GetDynamicDnsInfo
 功能描述  : 获取指定CID的DNS信息
 输入参数  : ulModuleId                 - 填写PID
             usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
             ucCid                      - CID
 输出参数  : 无

 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
 修改历史  :

 1.日    期   : 2013年07月08日
   作    者   : Y00213812
   修改内容   : VoLTE_PhaseI 项目，新增API

*****************************************************************************/
VOS_UINT32 TAF_PS_GetDynamicDnsInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucCid
)
{
    VOS_UINT32                          ulResult;

    TAF_PS_GET_NEGOTIATION_DNS_REQ_STRU stNegoDns;

    /* 初始化 */
    PS_MEM_SET(&stNegoDns, 0x00, sizeof(TAF_PS_GET_NEGOTIATION_DNS_REQ_STRU));

    /* 填充消息结构 */
    stNegoDns.stCtrl.ulModuleId = ulModuleId;
    stNegoDns.stCtrl.usClientId = usClientId;
    stNegoDns.stCtrl.ucOpId     = ucOpId;
    stNegoDns.ucCid             = ucCid;

    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_GET_NEGOTIATION_DNS_REQ,
                             &stNegoDns,
                             sizeof(TAF_PS_GET_NEGOTIATION_DNS_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_PS_SetCqosPriInfo
 功能描述  : 配置CDMA QOS 参数
 输入参数  : VOS_UINT32                                      ulModuleId
             VOS_UINT16                                      usClientId
             TAF_PS_CDATA_1X_QOS_NON_ASSURED_PRI_ENUM_UINT8  enPri
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月16日
    作    者   : y00218312
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_PS_SetCqosPriInfo(
    VOS_UINT32                                      ulModuleId,
    VOS_UINT16                                      usClientId,
    TAF_PS_CDATA_1X_QOS_NON_ASSURED_PRI_ENUM_UINT8  enPri
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_SET_1X_CQOS_PRI_REQ_STRU     stSetCqosPriReq;

    /* 初始化 */
    ulResult = VOS_OK;
    PS_MEM_SET(&stSetCqosPriReq, 0x00, sizeof(TAF_PS_SET_1X_CQOS_PRI_REQ_STRU));

    /* 构造TAF_PS_SET_CQOS_PRI_REQ_STRU消息 */
    stSetCqosPriReq.stCtrl.ulModuleId = ulModuleId;
    stSetCqosPriReq.stCtrl.usClientId = usClientId;
    stSetCqosPriReq.stCtrl.ucOpId     = 0;
    stSetCqosPriReq.enPri             = enPri;

    /* 发送消息 */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_SET_CQOS_PRI_REQ,
                             &stSetCqosPriReq,
                             sizeof(TAF_PS_SET_1X_CQOS_PRI_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_PS_SetApDsFlowRptCfg
 功能描述  : 设置AP流量上报参数
 输入参数  : ulModuleId                 - PID
             usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
             pstRptCfg                  - 配置参数
 输出参数  : 无
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月2日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_PS_SetApDsFlowRptCfg(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_APDSFLOW_RPT_CFG_STRU          *pstRptCfg
)
{
    TAF_PS_SET_APDSFLOW_RPT_CFG_REQ_STRU    stSetRptCfgReq;
    VOS_UINT32                              ulResult;

    PS_MEM_SET(&stSetRptCfgReq, 0x00, sizeof(TAF_PS_SET_APDSFLOW_RPT_CFG_REQ_STRU));

    /* 构造ID_MSG_TAF_PS_SET_APDSFLOW_RPT_CFG_REQ消息 */
    stSetRptCfgReq.stCtrl.ulModuleId = ulModuleId;
    stSetRptCfgReq.stCtrl.usClientId = usClientId;
    stSetRptCfgReq.stCtrl.ucOpId     = ucOpId;

    PS_MEM_CPY(&(stSetRptCfgReq.stRptCfg),
               pstRptCfg,
               sizeof(TAF_APDSFLOW_RPT_CFG_STRU));

    /* 发送消息 */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_SET_APDSFLOW_RPT_CFG_REQ,
                             &stSetRptCfgReq,
                             sizeof(TAF_PS_SET_APDSFLOW_RPT_CFG_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_PS_GetApDsFlowRptCfg
 功能描述  : 获取AP流量上报参数
 输入参数  : ulModuleId                 - PID
             usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
 输出参数  : 无
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月2日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_PS_GetApDsFlowRptCfg(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_PS_GET_APDSFLOW_RPT_CFG_REQ_STRU    stGetRptCfgReq;
    VOS_UINT32                              ulResult;

    PS_MEM_SET(&stGetRptCfgReq, 0x00, sizeof(TAF_PS_GET_APDSFLOW_RPT_CFG_REQ_STRU));

    /* 构造ID_MSG_TAF_PS_GET_APDSFLOW_RPT_CFG_REQ消息 */
    stGetRptCfgReq.stCtrl.ulModuleId = ulModuleId;
    stGetRptCfgReq.stCtrl.usClientId = usClientId;
    stGetRptCfgReq.stCtrl.ucOpId     = ucOpId;

    /* 发送消息 */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_GET_APDSFLOW_RPT_CFG_REQ,
                             &stGetRptCfgReq,
                             sizeof(TAF_PS_GET_APDSFLOW_RPT_CFG_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_PS_SetDsFlowNvWriteCfg
 功能描述  : 设置流量写NV配置
 输入参数  : ulModuleId                 - PID
             usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
             pstNvWriteCfg              - 流量写NV配置
 输出参数  : 无
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月12日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_PS_SetDsFlowNvWriteCfg(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_DSFLOW_NV_WRITE_CFG_STRU       *pstNvWriteCfg
)
{
    TAF_PS_SET_DSFLOW_NV_WRITE_CFG_REQ_STRU stSetWriteNvCfgReq;
    VOS_UINT32                              ulResult;

    PS_MEM_SET(&stSetWriteNvCfgReq, 0x00, sizeof(TAF_PS_SET_DSFLOW_NV_WRITE_CFG_REQ_STRU));

    /* 构造ID_MSG_TAF_PS_SET_DSFLOW_NV_WRITE_CFG_REQ消息 */
    stSetWriteNvCfgReq.stCtrl.ulModuleId = ulModuleId;
    stSetWriteNvCfgReq.stCtrl.usClientId = usClientId;
    stSetWriteNvCfgReq.stCtrl.ucOpId     = ucOpId;

    PS_MEM_CPY(&(stSetWriteNvCfgReq.stNvWriteCfg),
               pstNvWriteCfg,
               sizeof(TAF_DSFLOW_NV_WRITE_CFG_STRU));

    /* 发送消息 */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_SET_DSFLOW_NV_WRITE_CFG_REQ,
                             &stSetWriteNvCfgReq,
                             sizeof(TAF_PS_SET_DSFLOW_NV_WRITE_CFG_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_PS_GetDsFlowNvWriteCfg
 功能描述  : 获取流量写NV配置
 输入参数  : ulModuleId                 - PID
             usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
 输出参数  : 无
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月12日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_PS_GetDsFlowNvWriteCfg(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_PS_GET_DSFLOW_NV_WRITE_CFG_REQ_STRU stGetNvWriteCfgReq;
    VOS_UINT32                              ulResult;

    PS_MEM_SET(&stGetNvWriteCfgReq, 0x00, sizeof(TAF_PS_GET_DSFLOW_NV_WRITE_CFG_REQ_STRU));

    /* 构造ID_MSG_TAF_PS_GET_DSFLOW_WRITE_NV_CFG_REQ消息 */
    stGetNvWriteCfgReq.stCtrl.ulModuleId = ulModuleId;
    stGetNvWriteCfgReq.stCtrl.usClientId = usClientId;
    stGetNvWriteCfgReq.stCtrl.ucOpId     = ucOpId;

    /* 发送消息 */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_GET_DSFLOW_NV_WRITE_CFG_REQ,
                             &stGetNvWriteCfgReq,
                             sizeof(TAF_PS_GET_DSFLOW_NV_WRITE_CFG_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_PS_SetCtaInfo
 功能描述  : 设置aps no data time len
 输入参数  : VOS_UINT32                          ulModuleId,
             VOS_UINT16                          usClientId,
             VOS_UINT8                           ucOpId,
             VOS_UINT8                           ucTimeLen
 输出参数  : 无
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月20日
    作    者   : c00299063
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_PS_SetCtaInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucTimeLen
)
{
    TAF_PS_SET_CTA_INFO_REQ_STRU        stSetPktCdataInactivityTmrlenReq;
    VOS_UINT32                          ulResult;

    PS_MEM_SET(&stSetPktCdataInactivityTmrlenReq, 0x00, sizeof(stSetPktCdataInactivityTmrlenReq));

    /* 构造ID_MSG_TAF_PS_GET_DSFLOW_WRITE_NV_CFG_REQ消息 */
    stSetPktCdataInactivityTmrlenReq.stCtrl.ulModuleId  = ulModuleId;
    stSetPktCdataInactivityTmrlenReq.stCtrl.usClientId  = usClientId;
    stSetPktCdataInactivityTmrlenReq.stCtrl.ucOpId      = ucOpId;


    stSetPktCdataInactivityTmrlenReq.ucPktCdataInactivityTmrLen = ucTimeLen;


    /* 发送消息 */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_SET_CTA_INFO_REQ,
                             &stSetPktCdataInactivityTmrlenReq,
                             sizeof(stSetPktCdataInactivityTmrlenReq));

    return ulResult;
}
/*****************************************************************************
 函 数 名  : TAF_PS_GetCtaInfo
 功能描述  : 获取aps no data time len
 输入参数  : VOS_UINT32                          ulModuleId,
             VOS_UINT16                          usClientId,
             VOS_UINT8                           ucOpId,
 输出参数  : 无
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月20日
    作    者   : c00299063
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_PS_GetCtaInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_PS_GET_CTA_INFO_REQ_STRU        stGetPktCdataInactivityTmrlenReq;
    VOS_UINT32                                              ulResult;

    PS_MEM_SET(&stGetPktCdataInactivityTmrlenReq, 0x00, sizeof(stGetPktCdataInactivityTmrlenReq));

    stGetPktCdataInactivityTmrlenReq.stCtrl.ulModuleId  = ulModuleId;
    stGetPktCdataInactivityTmrlenReq.stCtrl.usClientId  = usClientId;
    stGetPktCdataInactivityTmrlenReq.stCtrl.ucOpId      = ucOpId;

    /* 发送消息 */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_GET_CTA_INFO_REQ,
                             &stGetPktCdataInactivityTmrlenReq,
                             sizeof(stGetPktCdataInactivityTmrlenReq));

    return ulResult;
}


/*****************************************************************************
 函 数 名  : TAF_PS_GetCgmtuInfo
 功能描述  : TAF PS Proc CGMTU AT Qry Command
 输入参数  : VOS_UINT32                          ulModuleId
             VOS_UINT16                          usClientId
             VOS_UINT8                           ucOpId
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月29日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_PS_GetCgmtuInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_PS_GET_CGMTU_VALUE_REQ_STRU     stGetCgmtuValueReq;
    VOS_UINT32                          ulResult;

    PS_MEM_SET(&stGetCgmtuValueReq, 0x00, sizeof(stGetCgmtuValueReq));

    stGetCgmtuValueReq.stCtrl.ulModuleId = ulModuleId;
    stGetCgmtuValueReq.stCtrl.usClientId = usClientId;
    stGetCgmtuValueReq.stCtrl.ucOpId     = ucOpId;

    /* 发送消息 */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_GET_CGMTU_VALUE_REQ,
                             &stGetCgmtuValueReq,
                             sizeof(stGetCgmtuValueReq));

    return ulResult;
}


/*****************************************************************************
 函 数 名  : TAF_PS_SetCdataDialModeInfo
 功能描述  : 配置CDMA  PPP数据传输模式参数
 输入参数  : VOS_UINT32                          ulModuleId
             VOS_UINT16                          usClientId
             TAF_PS_CDATA_DIAL_MODE_ENUM_UINT32 enDialMode
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年04月02日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_PS_SetCdataDialModeInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    TAF_PS_CDATA_DIAL_MODE_ENUM_UINT32  enDialMode
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_CDATA_DIAL_MODE_REQ_STRU     stDialModeReq;

    /* 初始化 */
    ulResult = VOS_OK;
    PS_MEM_SET(&stDialModeReq, 0x00, sizeof(TAF_PS_CDATA_DIAL_MODE_REQ_STRU));

    /* 构造TAF_PS_CDATA_DIAL_MODE_REQ_STRU消息 */
    stDialModeReq.stCtrl.ulModuleId     = ulModuleId;
    stDialModeReq.stCtrl.usClientId     = usClientId;
    stDialModeReq.stCtrl.ucOpId         = 0;
    stDialModeReq.enDialMode            = enDialMode;

    /* 发送消息 */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_SET_CDMA_DIAL_MODE_REQ,
                             &stDialModeReq,
                             sizeof(TAF_PS_CDATA_DIAL_MODE_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_PS_SetImsPdpCfg
 功能描述  : 设置IMS PDP
 输入参数  : usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
             pstImsPdpCfg               - IMS PDP配置
 输出参数  : 无
 返 回 值  : VOS_OK                     - 发送消息成功
             VOS_ERR                    - 发送消息失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月30日
    作    者   : z00301431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_PS_SetImsPdpCfg(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_IMS_PDP_CFG_STRU               *pstImsPdpCfg
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_SET_IMS_PDP_CFG_REQ_STRU     stSetImsPdpCfgReq;

    /* 初始化 */
    ulResult = VOS_OK;
    PS_MEM_SET(&stSetImsPdpCfgReq, 0x00, sizeof(TAF_PS_SET_IMS_PDP_CFG_REQ_STRU));

    /* 构造ID_MSG_TAF_PS_SET_IMS_PDP_CFG_REQ消息 */
    stSetImsPdpCfgReq.stCtrl.ulModuleId = ulModuleId;
    stSetImsPdpCfgReq.stCtrl.usClientId = usClientId;
    stSetImsPdpCfgReq.stCtrl.ucOpId     = ucOpId;
    stSetImsPdpCfgReq.stImsPdpCfg       = *pstImsPdpCfg;

    /* 发送消息 */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_SET_IMS_PDP_CFG_REQ,
                             &stSetImsPdpCfgReq,
                             sizeof(TAF_PS_SET_IMS_PDP_CFG_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_PS_SetCdmaDormantTimer
 功能描述  : 设置DORMANT TIMER
 输入参数  : usClientId                 - 客户端ID
             ucOpId                     - 操作码ID
             ucDormantTimer             - 时长
 输出参数  : 无
 返 回 值  : VOS_OK                     - 发送消息成功
             VOS_ERR                    - 发送消息失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月13日
    作    者   : y00314741
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_PS_SetCdmaDormantTimer(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucDormantTimer
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_SET_1X_DORM_TIMER_REQ_STRU   st1xDormTimerReq;

    /* 初始化 */
    ulResult = VOS_OK;
    PS_MEM_SET(&st1xDormTimerReq, 0x00, sizeof(TAF_PS_SET_1X_DORM_TIMER_REQ_STRU));

    /* 构造ID_MSG_TAF_PS_SET_1X_DORMANT_TIMER_REQ消息 */
    st1xDormTimerReq.stCtrl.ulModuleId = ulModuleId;
    st1xDormTimerReq.stCtrl.usClientId = usClientId;
    st1xDormTimerReq.stCtrl.ucOpId     = ucOpId;
    st1xDormTimerReq.ucDormantTimer    = ucDormantTimer;

    /* 发送消息 */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_SET_1X_DORM_TIMER_REQ,
                             &st1xDormTimerReq,
                             sizeof(TAF_PS_SET_1X_DORM_TIMER_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_PS_ProcCdmaDormTimerQryReq
 功能描述  : TAF PS Proc CDORMTIMER AT Qry Command
 输入参数  : VOS_UINT32                          ulModuleId
             VOS_UINT16                          usClientId
             VOS_UINT8                           ucOpId
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月14日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_PS_ProcCdmaDormTimerQryReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_PS_GET_1X_DORM_TIMER_REQ_STRU   stGet1xDormTimerReq;
    VOS_UINT32                          ulResult;

    PS_MEM_SET(&stGet1xDormTimerReq, 0x00, sizeof(stGet1xDormTimerReq));

    stGet1xDormTimerReq.stCtrl.ulModuleId = ulModuleId;
    stGet1xDormTimerReq.stCtrl.usClientId = usClientId;
    stGet1xDormTimerReq.stCtrl.ucOpId     = ucOpId;

    /* 发送消息 */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_GET_1X_DORM_TIEMR_REQ,
                             &stGet1xDormTimerReq,
                             sizeof(stGet1xDormTimerReq));

    return ulResult;
}




/*****************************************************************************
 函 数 名  : TAF_PS_GetCdataBearStatus
 功能描述  : 获取PPP的状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : APS_CDS_CDATA_BEAR_STATUS_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月20日
    作    者   : y00322978
    修改内容   : 新生成函数
*****************************************************************************/
TAF_PS_CDATA_BEAR_STATUS_ENUM_UINT8 TAF_PS_GetCdataBearStatus(
    VOS_UINT8                                               ucPdpId
)
{
    TAF_PS_CDATA_BEAR_STATUS_ENUM_UINT8 ucCdataBearStatus;

    ucCdataBearStatus = TAF_PS_CDATA_BEAR_STATUS_INACTIVE;

#if (OSA_CPU_CCPU == VOS_OSA_CPU)
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    ucCdataBearStatus = TAF_APS_GetCdataBearStatusCommFun(ucPdpId);
#endif
#endif

    return ucCdataBearStatus;
}

/*****************************************************************************
 函 数 名  : TAF_PS_GetPppStatus
 功能描述  : 可谓可测查询当前PPP状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : APS_CDS_CDATA_BEAR_STATUS_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月20日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
TAF_PS_CDATA_BEAR_STATUS_ENUM_UINT8  TAF_PS_GetPppStatus( VOS_VOID )
{
    VOS_UINT8                           ucPdpId;
    TAF_PS_CDATA_BEAR_STATUS_ENUM_UINT8 enCurrCdataStatus;
    TAF_PS_CDATA_BEAR_STATUS_ENUM_UINT8 enPreCdataStatus;

    enCurrCdataStatus = TAF_PS_CDATA_BEAR_STATUS_INACTIVE;
    enPreCdataStatus = TAF_PS_CDATA_BEAR_STATUS_INACTIVE;

    for (ucPdpId = 0; ucPdpId < TAF_PS_MAX_PDPID; ucPdpId++)
    {
        enCurrCdataStatus = TAF_PS_GetCdataBearStatus(ucPdpId);
        if ((enPreCdataStatus < enCurrCdataStatus)
        && (TAF_PS_CDATA_BEAR_STATUS_BUTT != enCurrCdataStatus))
        {
            enPreCdataStatus = enCurrCdataStatus;
        }

    }
    return enPreCdataStatus;
}



/*lint +e958*/

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
