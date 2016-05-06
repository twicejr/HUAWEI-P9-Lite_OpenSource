


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "AtMntn.h"
#include "AtInputProc.h"
#include "AtCtx.h"
#include "AtDataProc.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 -e960*/
#define    THIS_FILE_ID        PS_FILE_ID_AT_MNTN_C
/*lint -e767 +e960*/

/*****************************************************************************
  2 宏定义
*****************************************************************************/


/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/
AT_DEBUG_INFO_STRU                      g_stAtDebugInfo = {VOS_FALSE};

AT_MNTN_STATS_STRU                      g_stAtStatsInfo;

AT_MNTN_MSG_RECORD_INFO_STRU            g_stAtMsgRecordInfo;

/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  10 函数实现
*****************************************************************************/
/*****************************************************************************
函 数 名  : AT_InitMntnCtx
功能描述  : AT模块可维可测信息初始化
输入参数  : 无
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2014年09月13日
   作    者   : g00261581
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_InitMntnCtx(VOS_VOID)
{
    PS_MEM_SET(&g_stAtMsgRecordInfo, 0, sizeof(g_stAtMsgRecordInfo));
}

/*****************************************************************************
函 数 名  : AT_SetPcuiCtrlConcurrentFlag
功能描述  : 设置PCUI、PCUI2及CTRL口的并发标志位
输入参数  : VOS_UINT8    ucFlag
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2013年4月18日
   作    者   : z00220246
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_SetPcuiCtrlConcurrentFlag(VOS_UINT8 ucFlag)
{
    g_stAtDebugInfo.ucPcuiCtrlConcurrentFlg = ucFlag;
}

/*****************************************************************************
函 数 名  : AT_GetPcuiCtrlConcurrentFlag
功能描述  : 获取PCUI和CTRL口的并发标志位
输入参数  : 无
输出参数  : 无
返 回 值  : VOS_UINT8
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2013年4月18日
   作    者   : z00220246
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 AT_GetPcuiCtrlConcurrentFlag(VOS_VOID)
{
    return g_stAtDebugInfo.ucPcuiCtrlConcurrentFlg;
}

/*****************************************************************************
 函 数 名  : AT_SetPcuiPsCallFlag
 功能描述  : 设置PCUI口模拟nidsdup拨号的标志位
 输入参数  : VOS_UINT8         ucFlag
             VOS_UINT8         ucIndex
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月27日
    作    者   : l60609
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_SetPcuiPsCallFlag(
    VOS_UINT8                           ucFlag,
    VOS_UINT8                           ucIndex
)
{
    g_stAtDebugInfo.ucPcuiPsCallFlg     = ucFlag;
    g_stAtDebugInfo.ucPcuiUserId        = AT_CLIENT_TAB_APP_INDEX;
}

/*****************************************************************************
 函 数 名  : AT_GetPcuiPsCallFlag
 功能描述  : 获取PCUI口模拟nidsdup拨号的标志位
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月27日
    作    者   : l60609
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 AT_GetPcuiPsCallFlag(VOS_VOID)
{
    return g_stAtDebugInfo.ucPcuiPsCallFlg;
}

/*****************************************************************************
 函 数 名  : AT_GetPcuiUsertId
 功能描述  : 获取PCUI口模拟哪个端口NDISDUP拨号
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月7日
    作    者   : l60609
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 AT_GetPcuiUsertId(VOS_VOID)
{
    return g_stAtDebugInfo.ucPcuiUserId;
}

/*****************************************************************************
 函 数 名  : AT_SetCtrlPsCallFlag
 功能描述  : 设置Ctrl口模拟nidsdup拨号的标志位
 输入参数  : VOS_UINT8            ucFlag
             VOS_UINT8            ucIndex
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月8日
    作    者   : l60609
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_SetCtrlPsCallFlag(
    VOS_UINT8                           ucFlag,
    VOS_UINT8                           ucIndex
)
{
    g_stAtDebugInfo.ucCtrlPsCallFlg     = ucFlag;
#if (FEATURE_ON == FEATURE_VCOM_EXT)
    g_stAtDebugInfo.ucCtrlUserId        = AT_CLIENT_TAB_APP5_INDEX;
#else
    g_stAtDebugInfo.ucCtrlUserId        = AT_CLIENT_TAB_APP_INDEX;
#endif
}

/*****************************************************************************
 函 数 名  : AT_GetCtrlPsCallFlag
 功能描述  : 获取CTRL口模拟nidsdup拨号的标志位
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月8日
    作    者   : l60609
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 AT_GetCtrlPsCallFlag(VOS_VOID)
{
    return g_stAtDebugInfo.ucCtrlPsCallFlg;
}

/*****************************************************************************
 函 数 名  : AT_GetCtrlUserId
 功能描述  : 获取CTRL口模拟哪个端口NDISDUP拨号
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月8日
    作    者   : l60609
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 AT_GetCtrlUserId(VOS_VOID)
{
    return g_stAtDebugInfo.ucCtrlUserId;
}

/*****************************************************************************
 函 数 名  : AT_SetPcui2PsCallFlag
 功能描述  : 设置PCUI2口模拟^NDISDUP拨号的标志位
 输入参数  : VOS_UINT8        ucFlag
             VOS_UINT8        ucIndex
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月27日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID AT_SetPcui2PsCallFlag(
    VOS_UINT8                           ucFlag,
    VOS_UINT8                           ucIndex
)
{
    g_stAtDebugInfo.ucPcui2PsCallFlg    = ucFlag;
#if  (FEATURE_ON == FEATURE_VCOM_EXT)
    g_stAtDebugInfo.ucPcui2UserId       = AT_CLIENT_TAB_APP20_INDEX;
#else
    g_stAtDebugInfo.ucPcui2UserId       = AT_CLIENT_TAB_APP_INDEX;
#endif /* #if FEATURE_ON == FEATURE_VCOM_EXT */

}

/*****************************************************************************
 函 数 名  : AT_GetPcui2PsCallFlag
 功能描述  : 获取PCUI2口模拟^NDISDUP拨号的标志位
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月27日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 AT_GetPcui2PsCallFlag(VOS_VOID)
{
    return g_stAtDebugInfo.ucPcui2PsCallFlg;
}

/*****************************************************************************
 函 数 名  : AT_GetPcui2UserId
 功能描述  : 获取PCUI2口模拟哪个端口NDISDUP拨号
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月27日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 AT_GetPcui2UserId(VOS_VOID)
{
    return g_stAtDebugInfo.ucPcui2UserId;
}


/*****************************************************************************
 函 数 名  : AT_SetUnCheckApPortFlg
 功能描述  : 设置 不检查ApPort标志
 输入参数  : VOS_UINT8                            ucFlag
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月1日
    作    者   : n00269697
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_SetUnCheckApPortFlg(
    VOS_UINT8                           ucFlag
)
{
    if ((0 == ucFlag) || (1 == ucFlag))
    {
        g_stAtDebugInfo.ucUnCheckApPortFlg = ucFlag;
    }
}

/*****************************************************************************
 函 数 名  : AT_GetUnCheckApPortFlg
 功能描述  : 获取 不检查ApPort标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : g_stAtDebugInfo.ucUnCheckApPortFlg
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月1日
    作    者   : n00269697
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 AT_GetUnCheckApPortFlg(VOS_VOID)
{
    return g_stAtDebugInfo.ucUnCheckApPortFlg;
}

/*****************************************************************************
 函 数 名  : AT_MNTN_TraceEvent
 功能描述  : 输出可维可测
 输入参数  : pMsg - 可维可测消息(调用者保证非空)
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月11日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_MNTN_TraceEvent(VOS_VOID *pMsg)
{

    DIAG_TraceReport(pMsg);

    return;
}

/*****************************************************************************
 函 数 名  : AT_MNTN_TraceInputMsc
 功能描述  : 管脚信号输入可维可测
 输入参数  : ucIndex   - 端口索引
             pstDceMsc - 管脚信号信息(调用者保证非空)
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月11日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_MNTN_TraceInputMsc(
    VOS_UINT8                           ucIndex,
    AT_DCE_MSC_STRU                    *pstDceMsc
)
{
    AT_MNTN_MSC_STRU                    stMntnMsc;

    /* 填写消息头 */
    AT_MNTN_CFG_MSG_HDR(&stMntnMsc, ID_AT_MNTN_INPUT_MSC, (sizeof(AT_MNTN_MSC_STRU) - VOS_MSG_HEAD_LENGTH));

    /* 填写消息内容 */
    stMntnMsc.ulPortId = ucIndex;
    PS_MEM_CPY(&(stMntnMsc.stDceMscInfo), pstDceMsc, sizeof(AT_DCE_MSC_STRU));

    /* 发送消息 */
    AT_MNTN_TraceEvent(&stMntnMsc);

    return;
}

/*****************************************************************************
 函 数 名  : AT_MNTN_TraceOutputMsc
 功能描述  : 管脚信号输出可维可测
 输入参数  : ucIndex   - 端口索引
             pstDceMsc - 管脚信号信息(调用者保证非空)
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月11日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_MNTN_TraceOutputMsc(
    VOS_UINT8                           ucIndex,
    AT_DCE_MSC_STRU                    *pstDceMsc
)
{
    AT_MNTN_MSC_STRU                    stMntnMsc;

    /* 填写消息头 */
    AT_MNTN_CFG_MSG_HDR(&stMntnMsc, ID_AT_MNTN_OUTPUT_MSC, (sizeof(AT_MNTN_MSC_STRU) - VOS_MSG_HEAD_LENGTH));

    /* 填写消息内容 */
    stMntnMsc.ulPortId = ucIndex;
    PS_MEM_CPY(&(stMntnMsc.stDceMscInfo), pstDceMsc, sizeof(AT_DCE_MSC_STRU));

    /* 发送消息 */
    AT_MNTN_TraceEvent(&stMntnMsc);

    return;
}

/*****************************************************************************
 函 数 名  : AT_MNTN_TraceStartFlowCtrl
 功能描述  : 启动流控可维可测
 输入参数  : ucIndex    - 端口索引
             enFcDevive - 流控设备
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月11日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_MNTN_TraceStartFlowCtrl(
    VOS_UINT8                           ucIndex,
    AT_FC_DEVICE_TYPE_ENUM_UINT32       enFcDevive
)
{
    AT_MNTN_FLOW_CTRL_STRU              stMntnFlowCtrl;

    /* 填写消息头 */
    AT_MNTN_CFG_MSG_HDR(&stMntnFlowCtrl, ID_AT_MNTN_START_FLOW_CTRL, (sizeof(AT_MNTN_FLOW_CTRL_STRU) - VOS_MSG_HEAD_LENGTH));

    /* 填写消息内容 */
    stMntnFlowCtrl.ulPortId = ucIndex;
    stMntnFlowCtrl.enDevice = enFcDevive;

    /* 发送消息 */
    AT_MNTN_TraceEvent(&stMntnFlowCtrl);

    return;
}

/*****************************************************************************
 函 数 名  : AT_MNTN_TraceStopFlowCtrl
 功能描述  : 停止流控可维可测
 输入参数  : ucIndex    - 端口索引
             enFcDevive - 流控设备
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月11日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_MNTN_TraceStopFlowCtrl(
    VOS_UINT8                           ucIndex,
    AT_FC_DEVICE_TYPE_ENUM_UINT32       enFcDevive
)
{
    AT_MNTN_FLOW_CTRL_STRU              stMntnFlowCtrl;

    /* 填写消息头 */
    AT_MNTN_CFG_MSG_HDR(&stMntnFlowCtrl, ID_AT_MNTN_STOP_FLOW_CTRL, (sizeof(AT_MNTN_FLOW_CTRL_STRU) - VOS_MSG_HEAD_LENGTH));

    /* 填写消息内容 */
    stMntnFlowCtrl.ulPortId = ucIndex;
    stMntnFlowCtrl.enDevice = enFcDevive;

    /* 发送消息 */
    AT_MNTN_TraceEvent(&stMntnFlowCtrl);

    return;
}

/*****************************************************************************
 函 数 名  : AT_MNTN_TraceRegFcPoint
 功能描述  : 注册流控点可维可测
 输入参数  : ucIndex   - 端口索引
             enFcPoint - 流控点
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月11日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_MNTN_TraceRegFcPoint(
    VOS_UINT8                           ucIndex,
    AT_FC_POINT_TYPE_ENUM_UINT32        enFcPoint
)
{
    AT_MNTN_FC_POINT_STRU               stMntnFcPoint;

    /* 填写消息头 */
    AT_MNTN_CFG_MSG_HDR(&stMntnFcPoint, ID_AT_MNTN_REG_FC_POINT, (sizeof(AT_MNTN_FC_POINT_STRU) - VOS_MSG_HEAD_LENGTH));

    /* 填写消息内容 */
    stMntnFcPoint.ulPortId = ucIndex;
    stMntnFcPoint.enPoint  = enFcPoint;

    /* 发送消息 */
    AT_MNTN_TraceEvent(&stMntnFcPoint);

    return;
}

/*****************************************************************************
 函 数 名  : AT_MNTN_TraceDeregFcPoint
 功能描述  : 去注册流控点可维可测
 输入参数  : ucIndex   - 端口索引
             enFcPoint - 流控点
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月11日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_MNTN_TraceDeregFcPoint(
    VOS_UINT8                           ucIndex,
    AT_FC_POINT_TYPE_ENUM_UINT32        enFcPoint
)
{
    AT_MNTN_FC_POINT_STRU               stMntnFcPoint;

    /* 填写消息头 */
    AT_MNTN_CFG_MSG_HDR(&stMntnFcPoint, ID_AT_MNTN_DEREG_FC_POINT, (sizeof(AT_MNTN_FC_POINT_STRU) - VOS_MSG_HEAD_LENGTH));

    /* 填写消息内容 */
    stMntnFcPoint.ulPortId = ucIndex;
    stMntnFcPoint.enPoint  = enFcPoint;

    /* 发送消息 */
    AT_MNTN_TraceEvent(&stMntnFcPoint);

    return;
}

/*****************************************************************************
 函 数 名  : AT_MNTN_TraceCmdResult
 功能描述  : AT命令回复可维可测
 输入参数  : ucIndex   - 端口索引
             pucData   - 数据内容
             usDataLen - 数据长度
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月06日
    作    者   : j00174725
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_MNTN_TraceCmdResult(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usDataLen
)
{
    AT_MSG_STRU                        *pstMsg;
    AT_INTER_MSG_ID_ENUM_UINT32         enEventId;
    VOS_UINT32                          ulLength;

    AT_GetAtMsgStruMsgLength(usDataLen, &ulLength);

    /* 申请消息内存 */
    pstMsg = (AT_MSG_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, (ulLength + VOS_MSG_HEAD_LENGTH));
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_ERR_LOG("AT_MNTN_TraceCmdResult:ERROR:Alloc Mem Fail.");
        return;
    }

    /* 填写消息头 */
    enEventId       = AT_GetResultMsgID(ucIndex);
    AT_MNTN_CFG_MSG_HDR(pstMsg, enEventId, ulLength);

    /* 填写消息内容 */
    pstMsg->ucType  = 0x1;
    pstMsg->ucIndex = ucIndex;
    pstMsg->usLen   = usDataLen;

    AT_GetUserTypeFromIndex(ucIndex, &pstMsg->ucUserType);
    PS_MEM_SET(pstMsg->aucReserved, 0x00, sizeof(pstMsg->aucReserved));
    PS_MEM_CPY((TAF_VOID*)pstMsg->aucValue, pucData, usDataLen);

    /* 填写消息内容 */
    AT_MNTN_TraceEvent(pstMsg);

    /* 释放消息内存 */
    PS_MEM_FREE(WUEPS_PID_AT, pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : AT_MNTN_TraceCmdBuffer
 功能描述  : 缓存命令可维可测
 输入参数  : ucIndex   - 端口索引
             pucData   - 数据内容
             usDataLen - 数据长度
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年3月24日
    作    者   : s46746
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_MNTN_TraceCmdBuffer(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usDataLen
)
{
    AT_MSG_STRU                        *pstMsg;
    AT_INTER_MSG_ID_ENUM_UINT32         enEventId;
    VOS_UINT32                          ulLength;

    AT_GetAtMsgStruMsgLength(usDataLen, &ulLength);

    /* 申请消息内存 */
    pstMsg = (AT_MSG_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, (ulLength + VOS_MSG_HEAD_LENGTH));
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_ERR_LOG("AT_MNTN_TraceCmdBuffer:ERROR:Alloc Mem Fail.");
        return;
    }

    /* 填写消息头 */
    enEventId       = AT_GetResultMsgID(ucIndex);
    AT_MNTN_CFG_MSG_HDR(pstMsg, enEventId, ulLength);

    /* 填写消息内容 */
    pstMsg->ucType          = 0x2;
    pstMsg->ucIndex         = ucIndex;
    pstMsg->usLen           = usDataLen;

    AT_GetUserTypeFromIndex(ucIndex, &pstMsg->ucUserType);
    PS_MEM_SET(pstMsg->aucReserved, 0x00, sizeof(pstMsg->aucReserved));
    PS_MEM_CPY((TAF_VOID*)pstMsg->aucValue, pucData, usDataLen);

    /* 填写消息内容 */
    AT_MNTN_TraceEvent(pstMsg);

    /* 释放消息内存 */
    PS_FREE_MSG(WUEPS_PID_AT, pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : AT_MNTN_TraceContextData
 功能描述  : 把AT外部上下文作为SDT消息发送出去，以便在回放时通过桩函数还原
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2010年02月12日
    作    者   : 傅映君 62575
    修改内容   : 新生成函数
  2.日    期   : 2010年7月16日
    作    者   : 傅映君/f62575
    修改内容   : 问题单号：DTS2010071402189，支持AT模块多CLIENT ID的回放
  3.日    期   : 2013年03月07日
    作    者   : f00179208
    修改内容   : DSDA PHASE III
*****************************************************************************/
VOS_VOID AT_MNTN_TraceContextData(VOS_VOID)
{
    NAS_AT_SDT_AT_PART_ST                  *pstSndMsgCB     = VOS_NULL_PTR;
    NAS_AT_OUTSIDE_RUNNING_CONTEXT_PART_ST *pstOutsideCtx   = VOS_NULL_PTR;
    AT_MODEM_SMS_CTX_STRU                  *pstSmsCtx       = VOS_NULL_PTR;
    MODEM_ID_ENUM_UINT16                    enModemId;

    pstSndMsgCB = (NAS_AT_SDT_AT_PART_ST *)PS_ALLOC_MSG(WUEPS_PID_AT,
                                            sizeof(NAS_AT_SDT_AT_PART_ST));

    if (VOS_NULL_PTR == pstSndMsgCB)
    {
        AT_ERR_LOG("AT_MNTN_TraceContextData:ERROR: Alloc Memory Fail.");
        return;
    }

    pstSndMsgCB->ulReceiverPid      = WUEPS_PID_AT;
    pstSndMsgCB->ulSenderPid        = WUEPS_PID_AT;
    pstSndMsgCB->ulSenderCpuId      = VOS_LOCAL_CPUID;
    pstSndMsgCB->ulReceiverCpuId    = VOS_LOCAL_CPUID;
    pstSndMsgCB->ulLength           = sizeof(NAS_AT_OUTSIDE_RUNNING_CONTEXT_PART_ST) + 4;
    pstSndMsgCB->ucType             = AT_PC_REPLAY_MSG;
    pstSndMsgCB->enMsgID            = ID_AT_MNTN_PC_REPLAY_MSG;
    pstSndMsgCB->aucReserved[0]     = 0;
    pstSndMsgCB->aucReserved[1]     = 0;
    pstSndMsgCB->aucReserved[2]     = 0;


    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        pstSmsCtx                           = AT_GetModemSmsCtxAddrFromModemId(enModemId);
        pstOutsideCtx                       = &pstSndMsgCB->astOutsideCtx[enModemId];

        pstOutsideCtx->gucAtCscsType        = gucAtCscsType;
        pstOutsideCtx->gucAtCsdhType        = pstSmsCtx->ucCsdhType;
        pstOutsideCtx->g_OpId               = g_OpId;
        pstOutsideCtx->g_enAtCsmsMsgVersion = pstSmsCtx->enCsmsMsgVersion;
        pstOutsideCtx->g_enAtCmgfMsgFormat  = pstSmsCtx->enCmgfMsgFormat;

        PS_MEM_CPY(&pstOutsideCtx->gstAtCnmiType,
                   &(pstSmsCtx->stCnmiType),
                   sizeof(pstSmsCtx->stCnmiType));

        PS_MEM_CPY(&pstOutsideCtx->g_stAtCgsmsSendDomain,
                   &(pstSmsCtx->stCgsmsSendDomain),
                   sizeof(pstSmsCtx->stCgsmsSendDomain));

        PS_MEM_CPY(&pstOutsideCtx->g_stAtCscaCsmpInfo,
                   &(pstSmsCtx->stCscaCsmpInfo),
                   sizeof(pstSmsCtx->stCscaCsmpInfo));

        PS_MEM_CPY(&pstOutsideCtx->g_stAtCpmsInfo,
                   &(pstSmsCtx->stCpmsInfo),
                   sizeof(pstSmsCtx->stCpmsInfo));

    }

    AT_MNTN_TraceEvent(pstSndMsgCB);

    PS_FREE_MSG(WUEPS_PID_AT, pstSndMsgCB);

    return;
}

/*****************************************************************************
 函 数 名  : AT_MNTN_TraceClientData
 功能描述  : 发送AT模块的客户端口数据
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月17日
    作    者   : 傅映君/f62575
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_MNTN_TraceClientData(VOS_VOID)
{
    NAS_AT_SDT_AT_CLIENT_TABLE_STRU         *pstSndMsgCB;
    TAF_UINT8                               ucLoop;

    pstSndMsgCB = (NAS_AT_SDT_AT_CLIENT_TABLE_STRU *)PS_ALLOC_MSG(WUEPS_PID_AT,
                                            sizeof(NAS_AT_SDT_AT_CLIENT_TABLE_STRU));

    if ( VOS_NULL_PTR == pstSndMsgCB )
    {
        AT_ERR_LOG("AT_MNTN_TraceClientData:ERROR: Alloc Memory Fail.");
        return;
    }

    pstSndMsgCB->ulReceiverPid      = WUEPS_PID_AT;
    pstSndMsgCB->ulSenderPid        = WUEPS_PID_AT;
    pstSndMsgCB->ulSenderCpuId      = VOS_LOCAL_CPUID;
    pstSndMsgCB->ulReceiverCpuId    = VOS_LOCAL_CPUID;
    pstSndMsgCB->ulLength           = sizeof(NAS_AT_SDT_AT_CLIENT_TABLE_STRU) - 20;
    pstSndMsgCB->enMsgID            = ID_AT_MNTN_PC_REPLAY_CLIENT_TAB;
    pstSndMsgCB->ucType             = AT_PC_REPLAY_MSG_CLIENT_TAB;
    pstSndMsgCB->aucReserved[0]     = 0;
    pstSndMsgCB->aucReserved[1]     = 0;
    pstSndMsgCB->aucReserved[2]     = 0;

    for (ucLoop = 0; ucLoop < AT_MAX_CLIENT_NUM; ucLoop++)
    {
        pstSndMsgCB->gastAtClientTab[ucLoop].usClientId   = gastAtClientTab[ucLoop].usClientId;
        pstSndMsgCB->gastAtClientTab[ucLoop].opId         = gastAtClientTab[ucLoop].opId;
        pstSndMsgCB->gastAtClientTab[ucLoop].ucUsed       = gastAtClientTab[ucLoop].ucUsed;
        pstSndMsgCB->gastAtClientTab[ucLoop].UserType     = gastAtClientTab[ucLoop].UserType;
        pstSndMsgCB->gastAtClientTab[ucLoop].Mode         = gastAtClientTab[ucLoop].Mode;
        pstSndMsgCB->gastAtClientTab[ucLoop].IndMode      = gastAtClientTab[ucLoop].IndMode;
    }

    AT_MNTN_TraceEvent(pstSndMsgCB);

    PS_FREE_MSG(WUEPS_PID_AT, pstSndMsgCB);

    return;
}

/*****************************************************************************
 函 数 名  : AT_MNTN_TraceRPTPORT
 功能描述  : 发送AT模块的客户端口数据
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月1日
    作    者   : n00269697
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_MNTN_TraceRPTPORT(VOS_VOID)
{
    AT_MNTN_RPTPORT_STRU                   *pstSndMsgCB;
    VOS_UINT8                               ucLoop;

    pstSndMsgCB = (AT_MNTN_RPTPORT_STRU *)PS_ALLOC_MSG(WUEPS_PID_AT,
                                            sizeof(AT_MNTN_RPTPORT_STRU));

    if ( VOS_NULL_PTR == pstSndMsgCB )
    {
        AT_ERR_LOG("AT_MNTN_TraceRPTPORT:ERROR: Alloc Memory Fail.");
        return;
    }

    pstSndMsgCB->ulReceiverPid      = WUEPS_PID_AT;
    pstSndMsgCB->ulSenderPid        = WUEPS_PID_AT;
    pstSndMsgCB->ulSenderCpuId      = VOS_LOCAL_CPUID;
    pstSndMsgCB->ulReceiverCpuId    = VOS_LOCAL_CPUID;
    pstSndMsgCB->ulLength           = sizeof(AT_MNTN_RPTPORT_STRU) - 20;
    pstSndMsgCB->enMsgId            = ID_AT_MNTN_RPT_PORT;

    for (ucLoop = 0; ucLoop < AT_MAX_CLIENT_NUM; ucLoop++)
    {
        pstSndMsgCB->astAtRptPort[ucLoop].enAtClientTabIndex = (AT_CLIENT_TAB_INDEX_UINT8)ucLoop;
        pstSndMsgCB->astAtRptPort[ucLoop].enModemId          = g_astAtClientCtx[ucLoop].stClientConfiguration.enModemId;
        pstSndMsgCB->astAtRptPort[ucLoop].ucReportFlg        = g_astAtClientCtx[ucLoop].stClientConfiguration.ucReportFlg;
    }

    AT_MNTN_TraceEvent(pstSndMsgCB);

    PS_FREE_MSG(WUEPS_PID_AT, pstSndMsgCB);

    return;
}

/*****************************************************************************
 函 数 名  : AT_InitHsUartStats
 功能描述  : 初始化UART可维可测信息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年09月21日
    作    者   : j00174725
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_InitHsUartStats(VOS_VOID)
{
    PS_MEM_SET(&g_stAtStatsInfo.stHsUartStats, 0x00, sizeof(AT_MNTN_HSUART_STATS_STRU));
    return;
}

/*****************************************************************************
 函 数 名  : AT_MODEM_Help
 功能描述  : 初始化UART可维可测信息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月11日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_InitModemStats(VOS_VOID)
{
    PS_MEM_SET(&g_stAtStatsInfo.stModemStats, 0x00, sizeof(AT_MNTN_MODEM_STATS_STRU));
    return;
}

/*****************************************************************************
 函 数 名  : AT_RecordAtMsgInfo
 功能描述  : 记录进入At_MsgProc函数的消息属性
 输入参数  : VOS_UINT32                          ulSendPid,
             VOS_UINT32                          ulMsgName,
             VOS_UINT32                          ulSliceStart,
             VOS_UINT32                          ulSliceEnd
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年09月04日
    作    者   : g00261581
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_RecordAtMsgInfo(
    VOS_UINT32                          ulSendPid,
    VOS_UINT32                          ulMsgName,
    VOS_UINT32                          ulSliceStart,
    VOS_UINT32                          ulSliceEnd
)
{
    VOS_UINT32                          ulIndex;

    if (g_stAtMsgRecordInfo.ulCurrentIndex >= AT_MNTN_MSG_RECORD_MAX_NUM)
    {
        g_stAtMsgRecordInfo.ulCurrentIndex = 0;
    }

    ulIndex = g_stAtMsgRecordInfo.ulCurrentIndex;

    g_stAtMsgRecordInfo.astAtMntnMsgRecord[ulIndex].ulSendPid    = ulSendPid;
    g_stAtMsgRecordInfo.astAtMntnMsgRecord[ulIndex].ulMsgName    = ulMsgName;
    g_stAtMsgRecordInfo.astAtMntnMsgRecord[ulIndex].ulSliceStart = ulSliceStart;
    g_stAtMsgRecordInfo.astAtMntnMsgRecord[ulIndex].ulSliceEnd   = ulSliceEnd;

    g_stAtMsgRecordInfo.ulCurrentIndex++;

    return;
}

#if (FEATURE_ON == FEATURE_AT_HSUART)
/*****************************************************************************
 函 数 名  : AT_ShowHsUartConfigInfo
 功能描述  : HSUART配置可维可测信息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月11日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_ShowHsUartConfigInfo(VOS_VOID)
{
    AT_UART_LINE_CTRL_STRU             *pstLineCtrl = VOS_NULL_PTR;
    AT_UART_FLOW_CTRL_STRU             *pstFlowCtrl = VOS_NULL_PTR;
    AT_UART_RI_CFG_STRU                *pstUartRiCfgInfo = VOS_NULL_PTR;
    AT_UART_PHY_CFG_STRU               *pstUartPhyCfgInfo = VOS_NULL_PTR;
    AT_UART_FORMAT_PARAM_STRU          *pstFormatParam = VOS_NULL_PTR;
    VOS_CHAR                            acParityStr[][20] = {"ODD", "EVEN", "MARK", "SPACE", "NONE"};
    VOS_CHAR                            acDcdStr[][20] = {"ALWAYS ON", "CONNECT ON"};
    VOS_CHAR                            acDtrStr[][20] = {"IGNORE", "SWITCH CMD MODE", "HANGUP CALL"};
    VOS_CHAR                            acDsrStr[][20] = {"ALWAYS ON", "CONNECT ON"};
    VOS_CHAR                            acDceByDteStr[][20] = {"NONE", "XON OR XOFF REMOVE", "RTS", "XON_OR_XOFF_PASS"};
    VOS_CHAR                            acDteByDceStr[][20] = {"NONE", "XON OR XOFF REMOVE", "CTS"};

    pstLineCtrl       = AT_GetUartLineCtrlInfo();
    pstFlowCtrl       = AT_GetUartFlowCtrlInfo();
    pstUartRiCfgInfo  = AT_GetUartRiCfgInfo();
    pstUartPhyCfgInfo = AT_GetUartPhyCfgInfo();
    pstFormatParam    = AT_HSUART_GetFormatParam(pstUartPhyCfgInfo->stFrame.enFormat);

    (VOS_VOID)vos_printf("====================================\r\n");
    (VOS_VOID)vos_printf("[1] HSUART PHY                      \r\n");
    (VOS_VOID)vos_printf("====================================\r\n");
    (VOS_VOID)vos_printf("BaudRate:                   %d\r\n", pstUartPhyCfgInfo->enBaudRate);
    (VOS_VOID)vos_printf("Format:                     %d\r\n", pstUartPhyCfgInfo->stFrame.enFormat);
    (VOS_VOID)vos_printf("->Data Bit Length:          %d\r\n", pstFormatParam->enDataBitLength);
    (VOS_VOID)vos_printf("->Stop Bit Length:          %d\r\n", pstFormatParam->enStopBitLength);
    (VOS_VOID)vos_printf("->Parity Bit Length:        %d\r\n", pstFormatParam->enParityBitLength);
    (VOS_VOID)vos_printf("Parity Type:                %s\r\n", acParityStr[pstUartPhyCfgInfo->stFrame.enParity]);
    (VOS_VOID)vos_printf("====================================\r\n");
    (VOS_VOID)vos_printf("[2] HSUART LINE                     \r\n");
    (VOS_VOID)vos_printf("====================================\r\n");
    (VOS_VOID)vos_printf("DCD[%d]:                    %s\r\n", pstLineCtrl->enDcdMode, acDcdStr[pstLineCtrl->enDcdMode]);
    (VOS_VOID)vos_printf("DTR[%d]:                    %s\r\n", pstLineCtrl->enDtrMode, acDtrStr[pstLineCtrl->enDtrMode]);
    (VOS_VOID)vos_printf("DSR[%d]:                    %s\r\n", pstLineCtrl->enDsrMode, acDsrStr[pstLineCtrl->enDsrMode]);
    (VOS_VOID)vos_printf("====================================\r\n");
    (VOS_VOID)vos_printf("[3] HSUART FLOW CTRL                \r\n");
    (VOS_VOID)vos_printf("====================================\r\n");
    (VOS_VOID)vos_printf("DCE BY DTE[%d]:             %s\r\n", pstFlowCtrl->enDceByDte, acDceByDteStr[pstFlowCtrl->enDceByDte]);
    (VOS_VOID)vos_printf("DTE BY DCE[%d]:             %s\r\n", pstFlowCtrl->enDteByDce, acDteByDceStr[pstFlowCtrl->enDteByDce]);
    (VOS_VOID)vos_printf("====================================\r\n");
    (VOS_VOID)vos_printf("[4] HSUART RI                       \r\n");
    (VOS_VOID)vos_printf("====================================\r\n");
    (VOS_VOID)vos_printf("SMS RI ON (ms):             %u\r\n", pstUartRiCfgInfo->ulSmsRiOnInterval);
    (VOS_VOID)vos_printf("SMS RI OFF (ms):            %u\r\n", pstUartRiCfgInfo->ulSmsRiOffInterval);
    (VOS_VOID)vos_printf("VOICE RI ON (ms):           %u\r\n", pstUartRiCfgInfo->ulVoiceRiOnInterval);
    (VOS_VOID)vos_printf("VOICE RI OFF (ms):          %u\r\n", pstUartRiCfgInfo->ulVoiceRiOffInterval);
    (VOS_VOID)vos_printf("VOICE RI Cycle Times:       %d\r\n", pstUartRiCfgInfo->ucVoiceRiCycleTimes);

    return;
}

/*****************************************************************************
 函 数 名  : AT_ShowHsUartNvStats
 功能描述  : HSUART NV可维可测信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年09月21日
    作    者   : j00174725
    修改内容   : 新增函数
*****************************************************************************/
VOS_VOID AT_ShowHsUartNvStats(VOS_VOID)
{
    (VOS_VOID)vos_printf("====================================\r\n");
    (VOS_VOID)vos_printf("HSUART NV STATS                     \r\n");
    (VOS_VOID)vos_printf("====================================\r\n");
    (VOS_VOID)vos_printf("Read NV Fail NUM:           %d\r\n", g_stAtStatsInfo.stHsUartStats.ucReadNvFailNum);
    (VOS_VOID)vos_printf("Write NV Fail NUM:          %d\r\n", g_stAtStatsInfo.stHsUartStats.ucWriteNvFailNum);
    (VOS_VOID)vos_printf("BaudRate Invalid NUM:       %d\r\n", g_stAtStatsInfo.stHsUartStats.ucBaudRateERR);
    (VOS_VOID)vos_printf("Format Invalid NUM:         %d\r\n", g_stAtStatsInfo.stHsUartStats.ucFormatERR);

    return;
}

/*****************************************************************************
 函 数 名  : AT_ShowHsUartIoctlStats
 功能描述  : HSUART IOCTL操作结果
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年09月21日
    作    者   : j00174725
    修改内容   : 新生成函数

  2.日    期   : 2015年3月12日
    作    者   : A00165503
    修改内容   : DTS2015032409785: 增加水线检测功能
*****************************************************************************/
VOS_VOID AT_ShowHsUartIoctlStats(VOS_VOID)
{
    (VOS_VOID)vos_printf("====================================\r\n");
    (VOS_VOID)vos_printf("HSUART IOCTL STATS                  \r\n");
    (VOS_VOID)vos_printf("====================================\r\n");
    (VOS_VOID)vos_printf("Set Read CB ERR:            %d\r\n", g_stAtStatsInfo.stHsUartStats.ucSetReadCbERR);
    (VOS_VOID)vos_printf("Relloc Read BUFF ERR:       %d\r\n", g_stAtStatsInfo.stHsUartStats.ucRellocReadBuffERR);
    (VOS_VOID)vos_printf("Set Free CB ERR:            %d\r\n", g_stAtStatsInfo.stHsUartStats.ucSetFreeBuffCbERR);
    (VOS_VOID)vos_printf("Set MSC Read CB ERR:        %d\r\n", g_stAtStatsInfo.stHsUartStats.ucSetMscReadCbERR);
    (VOS_VOID)vos_printf("Set Switch CB ERR:          %d\r\n", g_stAtStatsInfo.stHsUartStats.ucSetSwitchCmdCbERR);
    (VOS_VOID)vos_printf("Set Water Detect CB ERR:    %d\r\n", g_stAtStatsInfo.stHsUartStats.ucSetWaterCbERR);
    (VOS_VOID)vos_printf("Set BaudRate FAIL NUM:      %d\r\n", g_stAtStatsInfo.stHsUartStats.ulSetBaudRateFailNum);
    (VOS_VOID)vos_printf("Set WLEN FAIL NUM:          %d\r\n", g_stAtStatsInfo.stHsUartStats.ulSetWlenFailNum);
    (VOS_VOID)vos_printf("Set STP FAIL NUM:           %d\r\n", g_stAtStatsInfo.stHsUartStats.ulSetStpFailNum);
    (VOS_VOID)vos_printf("Set PARITY FAIL NUM:        %d\r\n", g_stAtStatsInfo.stHsUartStats.ulSetParityFailNum);
    (VOS_VOID)vos_printf("Config FLOW CTL SUCC NUM:   %d\r\n", g_stAtStatsInfo.stHsUartStats.ulCfgFlowCtrlSuccNum);
    (VOS_VOID)vos_printf("Config FLOW CTL FAIL NUM:   %d\r\n", g_stAtStatsInfo.stHsUartStats.ulCfgFlowCtrlFailNum);
    (VOS_VOID)vos_printf("Clear BUFF SUCC NUM:        %d\r\n", g_stAtStatsInfo.stHsUartStats.ulClearBuffSuccNum);
    (VOS_VOID)vos_printf("Clear BUFF FAIL NUM:        %d\r\n", g_stAtStatsInfo.stHsUartStats.ulClearBuffFailNum);
    (VOS_VOID)vos_printf("MSC Read CB NUM:            %d\r\n", g_stAtStatsInfo.stHsUartStats.ulMscReadCBNum);
    (VOS_VOID)vos_printf("MSC Write SUCC NUM:         %d\r\n", g_stAtStatsInfo.stHsUartStats.ulMscWriteSuccNum);
    (VOS_VOID)vos_printf("MSC Write FAIL NUM:         %d\r\n", g_stAtStatsInfo.stHsUartStats.ulMscWriteFailNum);
    (VOS_VOID)vos_printf("MSC Switch CMD CB NUM:      %d\r\n", g_stAtStatsInfo.stHsUartStats.ulSwitchCmdCBNum);

    return;
}

/*****************************************************************************
 函 数 名  : AT_ShowHsUartDataStats
 功能描述  : HSUART数据统计可维可测
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年09月21日
    作    者   : j00174725
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_ShowHsUartDataStats(VOS_VOID)
{
    (VOS_VOID)vos_printf("====================================\r\n");
    (VOS_VOID)vos_printf("HSUART UL DATA STATS                \r\n");
    (VOS_VOID)vos_printf("====================================\r\n");
    (VOS_VOID)vos_printf("UL Read CB NUM:             %d\r\n", g_stAtStatsInfo.stHsUartStats.ulUlDataReadCBNum);
    (VOS_VOID)vos_printf("UL RD SUCC NUM:             %d\r\n", g_stAtStatsInfo.stHsUartStats.ulUlGetRDSuccNum);
    (VOS_VOID)vos_printf("UL RD Fail NUM:             %d\r\n", g_stAtStatsInfo.stHsUartStats.ulUlGetRDFailNum);
    (VOS_VOID)vos_printf("UL Invalid RD NUM:          %d\r\n", g_stAtStatsInfo.stHsUartStats.ulUlInvalidRDNum);
    (VOS_VOID)vos_printf("UL Invalid CMD DATA NUM:    %d\r\n", g_stAtStatsInfo.stHsUartStats.ulUlRcvInvalidCmdNum);
    (VOS_VOID)vos_printf("UL Valid CMD DATA NUM:      %d\r\n", g_stAtStatsInfo.stHsUartStats.ulUlValidCmdNum);
    (VOS_VOID)vos_printf("UL IP Data NUM:             %d\r\n", g_stAtStatsInfo.stHsUartStats.ulUlIpDataNum);
    (VOS_VOID)vos_printf("UL PPP Data NUM:            %d\r\n", g_stAtStatsInfo.stHsUartStats.ulUlPppDataNum);
    (VOS_VOID)vos_printf("UL CSD Data NUM:            %d\r\n", g_stAtStatsInfo.stHsUartStats.ulUlOmDataNum);
    (VOS_VOID)vos_printf("UL OM Data NUM:             %d\r\n", g_stAtStatsInfo.stHsUartStats.ulUlOmDataNum);
    (VOS_VOID)vos_printf("UL DIAG Data NUM:           %d\r\n", g_stAtStatsInfo.stHsUartStats.ulUlDiagDataNum);
    (VOS_VOID)vos_printf("UL Invalid MODE DATA NUM:   %d\r\n", g_stAtStatsInfo.stHsUartStats.ulUlInvalidModeDataNum);
    (VOS_VOID)vos_printf("UL Retrun BUFF SUCC NUM:    %d\r\n", g_stAtStatsInfo.stHsUartStats.ulUlReturnBuffSuccNum);
    (VOS_VOID)vos_printf("UL Retrun BUFF FAIL NUM:    %d\r\n", g_stAtStatsInfo.stHsUartStats.ulUlReturnBuffFailNum);
    (VOS_VOID)vos_printf("====================================\r\n");
    (VOS_VOID)vos_printf("HSUART DL DATA STATS                \r\n");
    (VOS_VOID)vos_printf("====================================\r\n");
    (VOS_VOID)vos_printf("DL Write Async SUCC NUM:    %d\r\n", g_stAtStatsInfo.stHsUartStats.ulDlWriteAsyncSuccNum);
    (VOS_VOID)vos_printf("DL Write Async FAIL NUM:    %d\r\n", g_stAtStatsInfo.stHsUartStats.ulDlWriteAsyncFailNum);
    (VOS_VOID)vos_printf("DL Write Sync SUCC NUM:     %d\r\n", g_stAtStatsInfo.stHsUartStats.ulDlWriteSyncSuccNum);
    (VOS_VOID)vos_printf("DL Write Sync FAIL NUM:     %d\r\n", g_stAtStatsInfo.stHsUartStats.ulDlWriteSyncFailNum);
    (VOS_VOID)vos_printf("DL Write Sync SUCC LEN:     %d\r\n", g_stAtStatsInfo.stHsUartStats.ulDlWriteSyncSuccLen);
    (VOS_VOID)vos_printf("DL Write Sync FAIL LEN:     %d\r\n", g_stAtStatsInfo.stHsUartStats.ulDlWriteSyncFailLen);
    (VOS_VOID)vos_printf("DL Free BUFF NUM:           %d\r\n", g_stAtStatsInfo.stHsUartStats.ulDlFreeBuffNum);

    return;
}

/*****************************************************************************
 函 数 名  : AT_ShowHsUartFcState
 功能描述  : HSUART流控状态可维可测信息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月11日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_ShowHsUartFcState(VOS_VOID)
{
    VOS_CHAR                            acFcStateStr[][20] = {"START", "STOP"};
    AT_IO_LEVEL_ENUM_UINT8              enIoLevel;

    enIoLevel = AT_GetIoLevel(AT_CLIENT_TAB_HSUART_INDEX, IO_CTRL_CTS);

    (VOS_VOID)vos_printf("====================================\r\n");
    (VOS_VOID)vos_printf("HSUART FLOW CTRL STATE              \r\n");
    (VOS_VOID)vos_printf("====================================\r\n");
    (VOS_VOID)vos_printf("FLOW CTRL STATE:            %s\r\n", acFcStateStr[enIoLevel]);

    return;
}
#endif

/*****************************************************************************
 函 数 名  : AT_ShowModemDataStats
 功能描述  : MODEM的数据统计可维可测
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月18日
    作    者   : sunshaohua
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_ShowModemDataStats(VOS_VOID)
{
    (VOS_VOID)vos_printf("====================================\r\n");
    (VOS_VOID)vos_printf("MODEM UL DATA STATS                 \r\n");
    (VOS_VOID)vos_printf("====================================\r\n");
    (VOS_VOID)vos_printf("UL Read CB NUM:             %d\r\n", g_stAtStatsInfo.stModemStats.ulUlDataReadCBNum);
    (VOS_VOID)vos_printf("UL RD SUCC NUM:             %d\r\n", g_stAtStatsInfo.stModemStats.ulUlGetRDSuccNum);
    (VOS_VOID)vos_printf("UL RD Fail NUM:             %d\r\n", g_stAtStatsInfo.stModemStats.ulUlGetRDFailNum);
    (VOS_VOID)vos_printf("UL Invalid RD NUM:          %d\r\n", g_stAtStatsInfo.stModemStats.ulUlInvalidRDNum);
    (VOS_VOID)vos_printf("UL Retrun BUFF SUCC NUM:    %d\r\n", g_stAtStatsInfo.stModemStats.ulUlReturnBuffSuccNum);
    (VOS_VOID)vos_printf("UL Retrun BUFF FAIL NUM:    %d\r\n", g_stAtStatsInfo.stModemStats.ulUlReturnBuffFailNum);
    (VOS_VOID)vos_printf("====================================\r\n");
    (VOS_VOID)vos_printf("MODEM DL DATA STATS                 \r\n");
    (VOS_VOID)vos_printf("====================================\r\n");
    (VOS_VOID)vos_printf("DL Write Async SUCC NUM:    %d\r\n", g_stAtStatsInfo.stModemStats.ulDlWriteAsyncSuccNum);
    (VOS_VOID)vos_printf("DL Write Async FAIL NUM:    %d\r\n", g_stAtStatsInfo.stModemStats.ulDlWriteAsyncFailNum);
    (VOS_VOID)vos_printf("DL Free BUFF NUM:           %d\r\n", g_stAtStatsInfo.stModemStats.ulDlFreeBuffNum);


    return;
}

/*****************************************************************************
 函 数 名  : AT_ShowPsEntityInfo
 功能描述  : PS域实体信息
 输入参数  : ucCallId - 呼叫实体索引
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月31日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_ShowPsEntityInfo(VOS_UINT8 ucCallId)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    MODEM_ID_ENUM_UINT16                enModemId;
#if (FEATURE_ON == FEATURE_IPV6)
    VOS_UINT8                           aucIpv6AddrStr[TAF_MAX_IPV6_ADDR_COLON_STR_LEN];
    VOS_UINT8                           aucIpv6PrimDnsStr[TAF_MAX_IPV6_ADDR_COLON_STR_LEN];
    VOS_UINT8                           aucIpv6SecDnsStr[TAF_MAX_IPV6_ADDR_COLON_STR_LEN];
#endif

    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        (VOS_VOID)vos_printf("################MODEM ID is %d################\n", enModemId);
        pstCallEntity = &(AT_GetModemPsCtxAddrFromModemId(enModemId)->astCallEntity[ucCallId]);

        (VOS_VOID)vos_printf("********************PS拨号实体信息***********************\n");
        (VOS_VOID)vos_printf("Active Flag                             %d\n", pstCallEntity->ulUsedFlg);
        (VOS_VOID)vos_printf("Current Call Type                       %d\n", pstCallEntity->enCurrPdpType);
        (VOS_VOID)vos_printf("********************用户拨号信息*************************\n");
        (VOS_VOID)vos_printf("User Actual Index                       %d\n", pstCallEntity->stUserInfo.enPortIndex);
        (VOS_VOID)vos_printf("User Expect Index                       %d\n", pstCallEntity->stUserInfo.enUserIndex);
        (VOS_VOID)vos_printf("User Type                               %d\n", pstCallEntity->stUserInfo.ucUsrType);
        (VOS_VOID)vos_printf("User CID                                %d\n", pstCallEntity->stUserInfo.ucUsrCid);
        (VOS_VOID)vos_printf("********************IPv4连接信息*************************\n");
        (VOS_VOID)vos_printf("IPv4 Bearer CID                         %d\n", pstCallEntity->ucIpv4Cid);
        (VOS_VOID)vos_printf("IPv4 Bearer State                       %d\n", pstCallEntity->enIpv4State);
        (VOS_VOID)vos_printf("IPv4 Bearer ID (RAB ID)                 %d\n", pstCallEntity->stIpv4DhcpInfo.ucRabId);
        (VOS_VOID)vos_printf("IPv4 Bearer Address                     0x%x\n", pstCallEntity->stIpv4DhcpInfo.ulIpv4Addr);
        (VOS_VOID)vos_printf("IPv4 Bearer Primary DNS                 0x%x\n", pstCallEntity->stIpv4DhcpInfo.ulIpv4PrimDNS);
        (VOS_VOID)vos_printf("IPv4 Bearer Secondary DNS               0x%x\n", pstCallEntity->stIpv4DhcpInfo.ulIpv4SecDNS);
        (VOS_VOID)vos_printf("IPv4 Bearer Gate Way                    0x%x\n", pstCallEntity->stIpv4DhcpInfo.ulIpv4GateWay);
        (VOS_VOID)vos_printf("IPv4 Bearer NET Mask                    0x%x\n", pstCallEntity->stIpv4DhcpInfo.ulIpv4NetMask);
        (VOS_VOID)vos_printf("***********************************************************\n");

#if (FEATURE_ON == FEATURE_IPV6)
        PS_MEM_SET(aucIpv6AddrStr, 0x00, sizeof(aucIpv6AddrStr));
        PS_MEM_SET(aucIpv6PrimDnsStr, 0x00, sizeof(aucIpv6PrimDnsStr));
        PS_MEM_SET(aucIpv6SecDnsStr, 0x00, sizeof(aucIpv6SecDnsStr));

        AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                          pstCallEntity->stIpv6DhcpInfo.aucIpv6Addr,
                                          TAF_IPV6_STR_RFC2373_TOKENS);

        AT_ConvertIpv6AddrToCompressedStr(aucIpv6PrimDnsStr,
                                          pstCallEntity->stIpv6DhcpInfo.aucIpv6PrimDNS,
                                          TAF_IPV6_STR_RFC2373_TOKENS);

        AT_ConvertIpv6AddrToCompressedStr(aucIpv6SecDnsStr,
                                          pstCallEntity->stIpv6DhcpInfo.aucIpv6SecDNS,
                                          TAF_IPV6_STR_RFC2373_TOKENS);

        (VOS_VOID)vos_printf("********************IPv6连接信息*************************\n");
        (VOS_VOID)vos_printf("IPv6 Bearer CID                         %d\n", pstCallEntity->ucIpv6Cid);
        (VOS_VOID)vos_printf("IPv6 Bearer State                       %d\n", pstCallEntity->enIpv6State);
        (VOS_VOID)vos_printf("***********************************************************\n");
        (VOS_VOID)vos_printf("IPv6 Bearer ID (RAB ID)                 %d\n", pstCallEntity->stIpv6DhcpInfo.ucRabId);
        (VOS_VOID)vos_printf("IPv6 Bearer Global Address              %s\n", aucIpv6AddrStr);
        (VOS_VOID)vos_printf("IPv6 Bearer Primary DNS                 %s\n", aucIpv6PrimDnsStr);
        (VOS_VOID)vos_printf("IPv6 Bearer Secondary DNS               %s\n", aucIpv6SecDnsStr);
        (VOS_VOID)vos_printf("***********************************************************\n");
#endif
    }

    return;
}

/*****************************************************************************
 函 数 名  : AT_ShowPsFcIdState
 功能描述  : 显示AT流控点注册信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年04月15日
      作    者   : f00179208
      修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_ShowPsFcIdState(VOS_UINT32 ulFcid)
{
    if (ulFcid >= FC_ID_BUTT)
    {
        (VOS_VOID)vos_printf("AT_ShowFcStatsInfo: Fcid overtop, ulFcid = %d\n", ulFcid);
        return;
    }

    (VOS_VOID)vos_printf("指定FCID对应的结点是否有效                  %d\n", g_stFcIdMaptoFcPri[ulFcid].ulUsed);
    (VOS_VOID)vos_printf("指定FCID对应的结点的优先级                  %d\n", g_stFcIdMaptoFcPri[ulFcid].enFcPri);
    (VOS_VOID)vos_printf("指定FCID对应的结点的RABID掩码               %d\n", g_stFcIdMaptoFcPri[ulFcid].ulRabIdMask);
    (VOS_VOID)vos_printf("指定FCID对应的结点的ModemId                 %d\n", g_stFcIdMaptoFcPri[ulFcid].enModemId);
    (VOS_VOID)vos_printf("\r\n");

    return;
}

/*****************************************************************************
 函 数 名  : AT_ShowResetStats
 功能描述  : 显示AT信号量初始化信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年04月15日
      作    者   : f00179208
      修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_ShowResetStatsInfo(VOS_VOID)
{
    (VOS_VOID)vos_printf("模块初始化标识                              %d\n", g_stAtStatsInfo.stCCpuResetStatsInfo.ulSemInitFlg);
    (VOS_VOID)vos_printf("当前的二进制信号量                          %p\n", AT_GetResetSem());
    (VOS_VOID)vos_printf("创建的二进制信号量                          %p\n", g_stAtStatsInfo.stCCpuResetStatsInfo.hBinarySemId);
    (VOS_VOID)vos_printf("创建二进制信号量失败次数                    %d\n", g_stAtStatsInfo.stCCpuResetStatsInfo.ulCreateBinarySemFailNum);
    (VOS_VOID)vos_printf("锁二进制信号量失败次数                      %d\n", g_stAtStatsInfo.stCCpuResetStatsInfo.ulLockBinarySemFailNum);
    (VOS_VOID)vos_printf("最后一次锁二进制信号量失败原因              %x\n", g_stAtStatsInfo.stCCpuResetStatsInfo.ulLastBinarySemErrRslt);
    (VOS_VOID)vos_printf("C核复位前的次数                             %d\n", g_stAtStatsInfo.stCCpuResetStatsInfo.ulResetBeforeNum);
    (VOS_VOID)vos_printf("C核复位后的次数                             %d\n", g_stAtStatsInfo.stCCpuResetStatsInfo.ulResetAfterNum);
    (VOS_VOID)vos_printf("HIFI复位成功的次数                          %d\n", g_stAtStatsInfo.stCCpuResetStatsInfo.ulHifiResetNum);
    (VOS_VOID)vos_printf("AT复位状态                                  %d\n", AT_GetResetFlag());
    (VOS_VOID)vos_printf("\r\n");

    return;
}

/*****************************************************************************
 函 数 名  : AT_ShowAllClientState
 功能描述  : 端口状态查询
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年01月15日
    作    者   : j00174725
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_ShowAllClientState(VOS_VOID)
{
    VOS_UINT8                           i;
    VOS_CHAR                            acStateStr[][20] = {"READY", "PEND"};
    VOS_CHAR                            acModeStr[][20] = {"CMD", "DATA", "ONLINE_CMD"};

    (VOS_VOID)vos_printf("\r\n The All Client State: \r\n");

    for (i = 0; i < AT_MAX_CLIENT_NUM; i++)
    {
        (VOS_VOID)vos_printf("Client[%d] State: %s    Mode: %s\r\n", i,
            acStateStr[g_stParseContext[i].ucClientStatus], acModeStr[gastAtClientTab[i].Mode]);
    }

    return;
}

/*****************************************************************************
 函 数 名  : AT_SetClientState
 功能描述  : 设置端口状态
 输入参数  : ucIndex -- clientID
             ulState -- 端口状态(Pend/Ready)
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年01月15日
    作    者   : j00174725
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_SetClientState(VOS_UINT8 ucIndex, VOS_UINT8 ucState)
{
    if ((ucIndex >= AT_MAX_CLIENT_NUM)||(ucState > AT_FW_CLIENT_STATUS_PEND))
    {
        return;
    }

    g_stParseContext[ucIndex].ucClientStatus = ucState;

    return;
}

/*****************************************************************************
 函 数 名  : AT_SetClientMode
 功能描述  : 设置端口模式
 输入参数  : ucIndex -- clientID
             ucMode -- 端口模式
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年01月15日
    作    者   : j00174725
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_SetClientMode(VOS_UINT8 ucIndex, VOS_UINT8 ucMode)
{
    if ((ucIndex >= AT_MAX_CLIENT_NUM)||(ucMode > AT_ONLINE_CMD_MODE))
    {
        return;
    }

    gastAtClientTab[ucIndex].Mode = ucMode;

    return;
}

/*****************************************************************************
 函 数 名  : AT_ShowUsedClient
 功能描述  : 打印当前使用端口状态
 输入参数  : ucIndex -- clientID
             ucMode -- 端口模式
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年01月15日
    作    者   : j00174725
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_ShowUsedClient(VOS_VOID)
{
    AT_PORT_BUFF_CFG_STRU              *pstPortCfg;
    VOS_UINT32                          ulIndex;
    VOS_UINT8                           i;
    VOS_CHAR                            acStateStr[][20] = {"READY", "PEND"};
    VOS_CHAR                            acModeStr[][20] = {"CMD", "DATA", "ONLINE_CMD"};

    pstPortCfg = AT_GetPortBuffCfgInfo();

    (VOS_VOID)vos_printf("\r\n The All Used Client State: \r\n");
    for (i = 0; i < pstPortCfg->ucNum; i++)
    {
        ulIndex = pstPortCfg->ulUsedClientID[i];
        (VOS_VOID)vos_printf("Client[%d] State: %s    Mode: %s\r\n", ulIndex,
            acStateStr[g_stParseContext[ulIndex].ucClientStatus], acModeStr[gastAtClientTab[ulIndex].Mode]);
    }

    return;
}


/*****************************************************************************
 函 数 名  : AT_ShowClientCtxInfo
 功能描述  : 打印Client配置的上下文信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年04月25日
    作    者   : f00179208
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_ShowClientCtxInfo(VOS_VOID)
{
    VOS_UINT8                           i;
    AT_CLIENT_CFG_MAP_TAB_STRU         *pstCfgMapTbl;
    AT_CLIENT_CONFIGURATION_STRU       *pstClientCfg;

    (VOS_VOID)vos_printf("\r\n The All Used Client Config: \r\n");
    for (i = 0; i < AT_GET_CLIENT_CFG_TAB_LEN(); i++)
    {
        pstCfgMapTbl = AT_GetClientCfgMapTbl(i);
        pstClientCfg = AT_GetClientConfig(pstCfgMapTbl->enClientId);
        (VOS_VOID)vos_printf("Client[%s] modem:%d, reportFlag:%d\r\n",
                   pstCfgMapTbl->aucPortName,
                   pstClientCfg->enModemId,
                   pstClientCfg->ucReportFlg);
    }
}

/*****************************************************************************
 函 数 名  : AT_Help
 功能描述  : AT可维可测入口
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月12日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_Help(VOS_VOID)
{
    (VOS_VOID)vos_printf("********************************************************\n");
    (VOS_VOID)vos_printf("PS软调信息                                              \n");
    (VOS_VOID)vos_printf("********************************************************\n");
    (VOS_VOID)vos_printf("AT_ShowPsEntityInfo         显示拨号实体信息            \n");
    (VOS_VOID)vos_printf("AT_ShowPsFcIdState(ulFcid)  显示流控点状态信息          \n");
    (VOS_VOID)vos_printf("********************************************************\n");
    (VOS_VOID)vos_printf("UART软调信息                                            \n");
    (VOS_VOID)vos_printf("********************************************************\n");
    (VOS_VOID)vos_printf("AT_ShowHsUartConfigInfo     显示HSUART的配置信息        \n");
    (VOS_VOID)vos_printf("AT_ShowHsUartNvStats        显示HSUART的NV读写统计信息  \n");
    (VOS_VOID)vos_printf("AT_ShowHsUartIoctlStats     显示HSUART的IOCTL统计信息   \n");
    (VOS_VOID)vos_printf("AT_ShowHsUartDataStats      显示HSUART的数据统计信息    \n");
    (VOS_VOID)vos_printf("AT_ShowHsUartFcState        显示HSUART的流控状态信息    \n");
    (VOS_VOID)vos_printf("********************************************************\n");
    (VOS_VOID)vos_printf("MODEM软调信息                                           \n");
    (VOS_VOID)vos_printf("********************************************************\n");
    (VOS_VOID)vos_printf("AT_ShowModemDataStats       显示MODEM的数据统计信息     \n");
    (VOS_VOID)vos_printf("********************************************************\n");
    (VOS_VOID)vos_printf("其他软调信息                                            \n");
    (VOS_VOID)vos_printf("********************************************************\n");
    (VOS_VOID)vos_printf("AT_ShowResetStatsInfo       显示AT复位状态信息          \n");
    (VOS_VOID)vos_printf("AT_ShowAllClientState       查看端口状态信息            \n");
    (VOS_VOID)vos_printf("AT_ShowClientCtxInfo        查看Client配置的上下文信息  \n");

    return;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


