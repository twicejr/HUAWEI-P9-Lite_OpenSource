

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "v_typdef.h"
#include "IpsMntn.h"
#include "TTFComm.h"
#include "v_id.h"
#include "vos.h"
#include "NetfilterEx.h"
#include "TtfOamInterface.h"
#include "TtfIpComm.h"

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 */
#define    THIS_FILE_ID        PS_FILE_ID_ACPU_IPS_MNTN_C
/*lint -e767 */

/*****************************************************************************
  2 宏定义
*****************************************************************************/

/*******************************************************************************
  3 枚举定义
*******************************************************************************/

/*****************************************************************************
  2 结构定义
*****************************************************************************/

/*****************************************************************************
  3 全局变量声明
*****************************************************************************/
IPS_MNTN_TRACE_CONFIG_REQ_STRU          g_stIpsTraceMsgCfg;     /*TCP/IP协议栈可维可测配置信息*/

/*****************************************************************************
  4 消息头定义
*****************************************************************************/

/*****************************************************************************
  5 消息定义
*****************************************************************************/


/*****************************************************************************
  6 UNION定义
*****************************************************************************/

/*****************************************************************************
  7 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  8 函数声明
*****************************************************************************/

/*****************************************************************************
 函 数 名  : IPS_MNTN_SndCfgCnf2Om
 功能描述  : 向OM发送配置确认消息
 输入参数  : usPrimId               消息ID
             usTransMsgContentLen   透传消息长度
             pTransMsgContent       透传消息内容指针
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年8月3日
    作    者   : f00166181
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID IPS_MNTN_SndCfgCnf2Om
(
    VOS_UINT32      ulPrimId,
    VOS_UINT32      ulTransMsgContentLen,
    VOS_VOID       *pTransMsgContent
)
{
    MsgBlock                *pSendMsg;

    /*分配并填写消息*/
    pSendMsg = VOS_AllocMsg(ACPU_PID_NFEXT, ulTransMsgContentLen - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pSendMsg)
    {
        TTF_LOG(ACPU_PID_NFEXT, DIAG_MODE_COMM, PS_PRINT_ERROR,
                                "Error: IPS_MNTN_SndCfgCnf2Om, ERROR, Call VOS_AllocMsg fail!");
        return;
    }

    mdrv_memcpy(pSendMsg, pTransMsgContent, ulTransMsgContentLen);

    if ( VOS_OK != VOS_SendMsg(ACPU_PID_NFEXT, pSendMsg) )
    {
        TTF_LOG(ACPU_PID_NFEXT, DIAG_MODE_COMM, PS_PRINT_ERROR,
                                "Error: IPS_MNTN_SndCfgCnf2Om, ERROR, Call VOS_SendMsg fail!");
    }

    return;
}

#if (FEATURE_ON == FEATURE_NFEXT)
/*****************************************************************************
 函 数 名  : IPS_MNTN_GetPktLenByTraceCfg
 功能描述  : 根据消息配置信息，获取捕获报文长度
 输入参数  : pstTraceCfg        消息配置信息
             usDataLen          报文长度

 输出参数  : pulTraceCfgLen     捕获报文长度
 返 回 值  : PS_TRUE        -   捕获报文
             PS_FALSE       -   不捕获报文
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年8月3日
    作    者   : f00166181
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 IPS_MNTN_GetPktLenByTraceCfg
(
    IPS_MNTN_TRACE_CONFIG_STRU     *pstTraceCfg,
    const VOS_UINT8                *pucPktData,
    VOS_UINT16                      usPktLen,
    VOS_UINT32                     *pulDataLen
)
{
    VOS_UINT32                      ulTraceDataLen;

    *pulDataLen    =   0;

    /*判断定时器是否启动*/
    switch ( pstTraceCfg->ulChoice )
    {
        case IPS_MNTN_TRACE_NULL_CHOSEN:
            return PS_FALSE;

        case IPS_MNTN_TRACE_MSG_HEADER_CHOSEN:
            ulTraceDataLen  = TTF_GetIpDataTraceLen(ACPU_PID_NFEXT, (VOS_UINT8 *)(pucPktData + MAC_HEADER_LENGTH), (usPktLen - MAC_HEADER_LENGTH));
            *pulDataLen     = TTF_MIN((ulTraceDataLen + MAC_HEADER_LENGTH), usPktLen);
            break;

        case IPS_MNTN_TRACE_CONFIGURABLE_LEN_CHOSEN:
            *pulDataLen     = TTF_MIN(pstTraceCfg->ulTraceDataLen, usPktLen);
            break;

        case IPS_MNTN_TRACE_WHOLE_DATA_LEN_CHOSEN:
            *pulDataLen     = usPktLen;
            break;

        default:
            return PS_FALSE;
    }

    return PS_TRUE;
}


/*****************************************************************************
 函 数 名  : IPS_MNTN_PktInfoCB
 功能描述  : 捕获TCP/IP协议栈接收和发送报文回调函数
 输入参数  : aucNetIfName   虚拟网卡信息
             aucPktData     线性数据指针,内容为报文信息
             usLen          报文数据长度
             usType         可维可测消息类型

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年8月3日
    作    者   : f00166181
    修改内容   : 新生成函数

*****************************************************************************/
/*lint -esym( 593, pucTraceData ) */
VOS_VOID IPS_MNTN_PktInfoCB
(
    const VOS_UINT8                        *pucNetIfName,
    const VOS_UINT8                        *pucPktData,
    VOS_UINT16                              usPktLen,
    TTF_MNTN_MSG_TYPE_ENUM_UINT16           enType
)
{
    VOS_UINT8                          *pucTraceData;
    IPS_MNTN_TRACE_CONFIG_STRU         *pstTraceCfg;
    IPS_MNTN_PKT_INFO_STRU             *pstTraceMsg;
    VOS_UINT32                          ulTransDataLen;
    VOS_UINT32                          ulDataLen;
    VOS_UINT32                          ulRst;
    VOS_UINT32                          ulNeedMemLen;

    ulTransDataLen  =   0;
    ulDataLen       =   0;
    ulNeedMemLen    =   0;

    if ( VOS_NULL_PTR == pucPktData )
    {
        TTF_LOG(ACPU_PID_NFEXT, DIAG_MODE_COMM, PS_PRINT_ERROR,
            "IPS, IPS_MNTN_PktInfoCB, ERROR, paucPktData is NULL ");
        return;
    }

    /* HIDS未连接 */
    if (VOS_NO == DIAG_GetConnState())
    {
        return;
    }

    /*根据消息类型选择对应配置信息*/
    if(ID_IPS_TRACE_INPUT_DATA_INFO == enType)
    {
        pstTraceCfg = &(g_stIpsTraceMsgCfg.stPreRoutingTraceCfg);
    }
    else if(ID_IPS_TRACE_OUTPUT_DATA_INFO == enType)
    {
        pstTraceCfg = &(g_stIpsTraceMsgCfg.stPostRoutingTraceCfg);
    }
    else if((enType >= ID_IPS_TRACE_BRIDGE_DATA_INFO) && (enType <= ID_IPS_TRACE_BR_FORWARD_FLOW_CTRL_STOP))
    {
        pstTraceCfg = &(g_stIpsTraceMsgCfg.stLocalTraceCfg);
    }
    else
    {
        /*打印警告信息,消息类型不匹配*/
        TTF_LOG( ACPU_PID_NFEXT, DIAG_MODE_COMM, PS_PRINT_ERROR,
                "IPS, IPS_MNTN_PktInfoCB : ERROR : usType is not Expectes!" );
        return;
    }

    /*根据消息配置信息，获取输出报文长度*/
    ulRst = IPS_MNTN_GetPktLenByTraceCfg(pstTraceCfg, pucPktData, usPktLen, &ulDataLen);
    if(PS_FALSE == ulRst)
    {
        /*不捕获该报文*/
        return;
    }

    ulDataLen           = PS_MIN(IPS_MNTN_TRACE_MAX_BYTE_LEN, ulDataLen);
    TTF_GET_OFFSET(ulTransDataLen, IPS_MNTN_PKT_INFO_STRU, aucData);
    ulTransDataLen      += ulDataLen;
    ulNeedMemLen = ulTransDataLen + sizeof(DIAG_TRANS_IND_STRU);

    /* 从Linux内核申请内存 */
    pucTraceData = NF_EXT_MEM_ALLOC(ACPU_PID_NFEXT, ulNeedMemLen);
    if (VOS_NULL_PTR == pucTraceData)
    {
        NF_EXT_STATS_INC(1, NF_EXT_STATS_ALLOC_MEM_FAIL);

        return;
    }

    /*构建透明消息*/
    pstTraceMsg             = (IPS_MNTN_PKT_INFO_STRU *)(pucTraceData + sizeof(DIAG_TRANS_IND_STRU));
    pstTraceMsg->usLen      = usPktLen;
    pstTraceMsg->usPrimId   = enType;
    mdrv_memcpy(pstTraceMsg->aucNetIfName, pucNetIfName, IPS_IFNAMSIZ);

    /*lint -e669 */
    mdrv_memcpy(pstTraceMsg->aucData, pucPktData, ulDataLen);
    /*lint +e669 */

    if (VOS_OK != IPS_MNTN_TransMsg(pucTraceData, ulTransDataLen, enType))
    {
        NF_EXT_MEM_FREE(ACPU_PID_NFEXT, pucTraceData);
    }

    return;
}
/*lint +esym( 593, pucTraceData ) */

/*****************************************************************************
 函 数 名  : IPS_MNTN_BridgePktInfoCB
 功能描述  : 捕获网桥中转报文回调函数
 输入参数  : aucSrcPort     发送虚拟网卡信息
             aucDestPort    接受虚拟网卡信息
             aucPktData     线性数据指针,内容为报文信息,指向14字节MAC头部
             usPktLen       报文数据长度,包含14字节MAC头
             usType         可维可测消息类型

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年8月3日
    作    者   : f00166181
    修改内容   : 新生成函数

*****************************************************************************/
/*lint -esym( 593, pucTraceData ) */
VOS_VOID IPS_MNTN_BridgePktInfoCB
(
    const VOS_UINT8                        *pucSrcPort,
    const VOS_UINT8                        *pucDestPort,
    VOS_UINT8                              *pucPktData,
    VOS_UINT16                              usPktLen,
    TTF_MNTN_MSG_TYPE_ENUM_UINT16           enType
)
{
    VOS_UINT8                          *pucTraceData;
    IPS_MNTN_TRACE_CONFIG_STRU         *pstTraceCfg;
    IPS_MNTN_BRIDGE_PKT_INFO_STRU      *pstTraceMsg;
    VOS_UINT32                          ulTransDataLen;
    VOS_UINT32                          ulDataLen;
    VOS_UINT32                          ulRst;
    VOS_UINT32                          ulNeedMemLen;

    ulTransDataLen  =   0;
    ulDataLen       =   0;
    ulNeedMemLen    =   0;



    if ( VOS_NULL_PTR == pucPktData )
    {
        TTF_LOG(ACPU_PID_NFEXT, DIAG_MODE_COMM, PS_PRINT_ERROR,
            "IPS, IPS_MNTN_BridgePktInfoCB, ERROR, paucPktData is NULL ");
        return;
    }

    /* HIDS未连接 */
    if (VOS_NO == DIAG_GetConnState())
    {
        return;
    }

    /*根据消息类型选择对应配置信息*/
    if((enType >= ID_IPS_TRACE_BRIDGE_DATA_INFO) && (enType <= ID_IPS_TRACE_BR_FORWARD_FLOW_CTRL_STOP))
    {
        pstTraceCfg = &(g_stIpsTraceMsgCfg.stBridgeArpTraceCfg);
    }
    else
    {
        /*打印警告信息,消息类型不匹配*/
        TTF_LOG( ACPU_PID_NFEXT, DIAG_MODE_COMM, PS_PRINT_ERROR,
                "IPS, IPS_MNTN_BridgePktInfoCB : ERROR : usType is not Expectes!" );
        return;
    }

    /*根据消息配置信息，获取输出报文长度*/
    ulRst = IPS_MNTN_GetPktLenByTraceCfg(pstTraceCfg, pucPktData, usPktLen, &ulDataLen);
    if(PS_FALSE == ulRst)
    {
        /*不捕获该报文*/
        return;
    }

    ulDataLen           = PS_MIN(IPS_MNTN_TRACE_MAX_BYTE_LEN, ulDataLen);
    TTF_GET_OFFSET(ulTransDataLen, IPS_MNTN_BRIDGE_PKT_INFO_STRU, aucData);
    ulTransDataLen      += ulDataLen;
    ulNeedMemLen = ulTransDataLen + sizeof(DIAG_TRANS_IND_STRU);

    /* 从Linux内核申请内存 */
    pucTraceData = NF_EXT_MEM_ALLOC(ACPU_PID_NFEXT, ulNeedMemLen);

    if (VOS_NULL_PTR == pucTraceData)
    {
        NF_EXT_STATS_INC(1, NF_EXT_STATS_ALLOC_MEM_FAIL);

        return;
    }

    /*构建透明消息*/
    pstTraceMsg             = (IPS_MNTN_BRIDGE_PKT_INFO_STRU *)(pucTraceData + sizeof(DIAG_TRANS_IND_STRU));
    pstTraceMsg->usLen      = usPktLen;
    pstTraceMsg->usPrimId   = enType;

    if (VOS_NULL_PTR != pucSrcPort)
    {
        mdrv_memcpy(pstTraceMsg->aucSrcPort, pucSrcPort, IPS_END_NAME);
    }
    if (VOS_NULL_PTR != pucDestPort)
    {
        mdrv_memcpy(pstTraceMsg->aucDestPort, pucDestPort, IPS_END_NAME);
    }

    /*lint -e669 */
    mdrv_memcpy(pstTraceMsg->aucData, pucPktData, ulDataLen);
    /*lint +e669 */

    if (VOS_OK != IPS_MNTN_TransMsg(pucTraceData, ulTransDataLen, enType))
    {
        NF_EXT_MEM_FREE(ACPU_PID_NFEXT, pucTraceData);
    }

    return;

}
/*lint +esym( 593, pucTraceData ) */

/*****************************************************************************
 函 数 名  : IPS_MNTN_CtrlPktInfoCB
 功能描述  : 捕获TCP/IP协议栈控制报文回调函数
 输入参数  : aucNetIfName   虚拟网卡信息
             aucPktData     线性数据指针,内容为报文信息
             usLen          报文数据长度
             usType         可维可测消息类型

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年8月3日
    作    者   : f00166181
    修改内容   : 新生成函数

*****************************************************************************/
/*lint -esym( 593, pucTraceData ) */
VOS_VOID IPS_MNTN_CtrlPktInfoCB
(
    const VOS_UINT8                        *pucNetIfName,
    const VOS_UINT8                        *pucPktData,
    VOS_UINT16                              usPktLen,
    TTF_MNTN_MSG_TYPE_ENUM_UINT16           enType
)
{

    VOS_UINT8                          *pucTraceData;
    IPS_MNTN_PKT_INFO_STRU             *pstTraceMsg;
    VOS_UINT32                          ulTransDataLen;
    VOS_UINT32                          ulDataLen;
    VOS_UINT32                          ulNeedMemLen;

    ulTransDataLen  =   0;
    ulDataLen       =   0;
    ulNeedMemLen    =   0;

    if ( VOS_NULL_PTR == pucPktData )
    {
        TTF_LOG(ACPU_PID_NFEXT, DIAG_MODE_COMM, PS_PRINT_ERROR,
            "IPS, IPS_MNTN_CtrlPktInfoCB, ERROR, pucPktData is NULL ");
        return;
    }

    /* HIDS未连接 */
    if (VOS_NO == DIAG_GetConnState())
    {
        return;
    }

    ulDataLen           = PS_MIN(IPS_MNTN_TRACE_MAX_BYTE_LEN, usPktLen);
    TTF_GET_OFFSET(ulTransDataLen, IPS_MNTN_PKT_INFO_STRU, aucData);
    ulTransDataLen      += ulDataLen;
    ulNeedMemLen = ulTransDataLen + sizeof(DIAG_TRANS_IND_STRU);

    /* 从Linux内核申请内存 */
    pucTraceData = NF_EXT_MEM_ALLOC(ACPU_PID_NFEXT, ulNeedMemLen);

    if (VOS_NULL_PTR == pucTraceData)
    {
        NF_EXT_STATS_INC(1, NF_EXT_STATS_ALLOC_MEM_FAIL);

        return;
    }

    /*构建透明消息*/
    pstTraceMsg             = (IPS_MNTN_PKT_INFO_STRU *)(pucTraceData + sizeof(DIAG_TRANS_IND_STRU));
    pstTraceMsg->usLen      = usPktLen;
    pstTraceMsg->usPrimId   = enType;
    mdrv_memcpy(pstTraceMsg->aucNetIfName, pucNetIfName, IPS_IFNAMSIZ);
    /*lint -e669 */
    mdrv_memcpy(pstTraceMsg->aucData, pucPktData, ulDataLen);
    /*lint +e669 */

    if (VOS_OK != IPS_MNTN_TransMsg(pucTraceData, ulTransDataLen, enType))
    {
        NF_EXT_MEM_FREE(ACPU_PID_NFEXT, pucTraceData);

    }

    return;
}
/*lint +esym( 593, pucTraceData ) */

/*****************************************************************************
 函 数 名  : IPS_MNTN_FlowCtrl
 功能描述  : 协议栈流控可维可测上报
 输入参数  : ulFcType 流控类型，当前只有网桥forward流控
             usType   启流控或者解流控
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年01月12日
    作    者   : t00148005
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID IPS_MNTN_FlowCtrl(VOS_UINT32 ulFcType, TTF_MNTN_MSG_TYPE_ENUM_UINT16  enType)
{
    DIAG_TRANS_IND_STRU                 stTransData;
    IPS_MNTN_FLOW_CTRL_STRU             stFlowCtrlMsg;

    PS_MEM_SET(&stFlowCtrlMsg, 0x0, sizeof(IPS_MNTN_FLOW_CTRL_STRU));

    /* 填充信息 */
    stTransData.ulPid       = ACPU_PID_NFEXT;
    stTransData.ulMsgId     = enType;
    stTransData.ulModule    = DIAG_GEN_MODULE(MODEM_ID_0, DIAG_MODE_COMM);
    stTransData.ulLength    = MNTN_FLOW_CTRL_INFO_LEN;
    stTransData.pData       = &stFlowCtrlMsg;

    stFlowCtrlMsg.ulFcType  = ulFcType;
    stFlowCtrlMsg.usPrimId  = enType;

    if ( VOS_OK != DIAG_TransReport(&stTransData) )
    {
        TTF_LOG(ACPU_PID_NFEXT, DIAG_MODE_COMM, PS_PRINT_ERROR,
            "IPS, DIAG_TransReport, ERROR, Call DIAG_TransReport fail!");
    }

    return;
}

#endif      /* #if (FEATURE_ON == FEATURE_NFEXT) */

/*****************************************************************************
 函 数 名  : IPS_MNTN_SndTransInd2Om
 功能描述  : 向OM发送透传消息
 输入参数  : pTransMsgContent       透传消息内容指针
 输出参数  : 无
 返 回 值  : VOS_UINT32 成功或者失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月30日
    作    者   : f00166181
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 IPS_MNTN_TransMsg
(
    VOS_UINT8                              *pucTransMsg,
    VOS_UINT32                              ulTransMsgContentLen,
    TTF_MNTN_MSG_TYPE_ENUM_UINT16           enMsgName
)
{
    NF_EXT_DATA_RING_BUF_STRU               stBufData;
    DIAG_TRANS_IND_STRU                     *pstDiagTransData;

    /*申请消息*/
    pstDiagTransData            = (DIAG_TRANS_IND_STRU *)pucTransMsg;

    /* 填充信息 */
    pstDiagTransData->ulPid     = ACPU_PID_NFEXT;
    pstDiagTransData->ulMsgId   = enMsgName;
    pstDiagTransData->ulModule  = DIAG_GEN_MODULE(MODEM_ID_0, DIAG_MODE_COMM);
    pstDiagTransData->ulLength  = ulTransMsgContentLen;
    pstDiagTransData->pData     = pucTransMsg + sizeof(DIAG_TRANS_IND_STRU);

    /* 中断上下文在自处理任务中勾包, 非中断上下文直接勾包 */
    if (VOS_FALSE != VOS_CheckInterrupt())
    {
        stBufData.pData         = (VOS_UINT8 *)pucTransMsg;
        stBufData.usDataLen     = (VOS_UINT16)(ulTransMsgContentLen + sizeof(DIAG_TRANS_IND_STRU));

        if (VOS_OK != NFExt_AddDataToRingBuf(&stBufData))
        {
            return VOS_ERR;
        }
    }
    else
    {
        (VOS_VOID)DIAG_TransReport(pstDiagTransData);
        NF_EXT_MEM_FREE(ACPU_PID_NFEXT, pucTransMsg);
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : IPS_MNTN_BridgeTraceCfgChkParam
 功能描述  : 网桥中转钩包配置参数检查
 输入参数  : pRcvMsg
 输出参数  : 无
 返 回 值  : VOS_TRUE/VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月30日
    作    者   : f00166181
    修改内容   : 新生成函数

*****************************************************************************/
PS_BOOL_ENUM_UINT8  IPS_MNTN_BridgeTraceCfgChkParam(IPS_MNTN_TRACE_CONFIG_REQ_STRU *pRcvMsg)
{
    if ( (IPS_MNTN_TRACE_NULL_CHOSEN != pRcvMsg->stBridgeArpTraceCfg.ulChoice)
        && (IPS_MNTN_TRACE_MSG_HEADER_CHOSEN != pRcvMsg->stBridgeArpTraceCfg.ulChoice)
        && (IPS_MNTN_TRACE_CONFIGURABLE_LEN_CHOSEN != pRcvMsg->stBridgeArpTraceCfg.ulChoice)
        && (IPS_MNTN_TRACE_WHOLE_DATA_LEN_CHOSEN != pRcvMsg->stBridgeArpTraceCfg.ulChoice) )
    {
        return PS_FALSE;
    }

    return PS_TRUE;
}

/*****************************************************************************
 函 数 名  : IPS_MNTN_WanTraceCfgChkParam
 功能描述  : TCP/IP协议栈报文钩包配置参数检查
 输入参数  : pRcvMsg
 输出参数  : 无
 返 回 值  : VOS_TRUE/VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月30日
    作    者   : f00166181
    修改内容   : 新生成函数

*****************************************************************************/
PS_BOOL_ENUM_UINT8  IPS_MNTN_TraceCfgChkParam(IPS_MNTN_TRACE_CONFIG_REQ_STRU *pRcvMsg)
{
    if (IPS_MNTN_TRACE_WHOLE_DATA_LEN_CHOSEN < pRcvMsg->stPreRoutingTraceCfg.ulChoice)
    {
        return PS_FALSE;
    }

    if (IPS_MNTN_TRACE_WHOLE_DATA_LEN_CHOSEN < pRcvMsg->stPostRoutingTraceCfg.ulChoice)
    {
        return PS_FALSE;
    }

    if (IPS_MNTN_TRACE_WHOLE_DATA_LEN_CHOSEN < pRcvMsg->stLocalTraceCfg.ulChoice)
    {
        return PS_FALSE;
    }

    if (IPS_MNTN_TRACE_WHOLE_DATA_LEN_CHOSEN < pRcvMsg->stBridgeArpTraceCfg.ulChoice)
    {
        return PS_FALSE;
    }

    if (WTTF_TRACE_MSG_YES < pRcvMsg->enAdsIPConfig)
    {
        return PS_FALSE;
    }

    return PS_TRUE;
}

/*****************************************************************************
 函 数 名  : IPS_MNTN_TraceAdvancedCfgChkParam
 功能描述  : 钩包配置参数检查
 输入参数  : pRcvMsg
 输出参数  : 无
 返 回 值  : VOS_TRUE/VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月30日
    作    者   : f00166181
    修改内容   : 新生成函数

*****************************************************************************/
PS_BOOL_ENUM_UINT8  IPS_MNTN_TraceAdvancedCfgChkParam(IPS_MNTN_TRACE_CONFIG_REQ_STRU *pRcvMsg)
{
    /*TCP/IP协议栈报文钩包配置参数检查*/
    if (PS_FALSE == IPS_MNTN_TraceCfgChkParam(pRcvMsg))
    {
        return PS_FALSE;
    }

    /*网桥中转报文钩包配置参数检查*/
    if (PS_FALSE == IPS_MNTN_BridgeTraceCfgChkParam(pRcvMsg))
    {
        return  PS_FALSE;
    }

    if ((WTTF_TRACE_MSG_YES != pRcvMsg->enAdsIPConfig) && (WTTF_TRACE_MSG_NO != pRcvMsg->enAdsIPConfig))
    {
        return PS_FALSE;
    }

    return PS_TRUE;
}

/*****************************************************************************
 函 数 名  : IPS_MNTN_TraceAdvancedCfgReq
 功能描述  : 保存钩包配置
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月30日
    作    者   : f00166181
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID IPS_MNTN_TraceAdvancedCfgReq(VOS_VOID *pMsg)
{
    PS_BOOL_ENUM_UINT8                       enResult;

    OM_IPS_ADVANCED_TRACE_CONFIG_REQ_STRU    *pRcvMsg;
    IPS_OM_ADVANCED_TRACE_CONFIG_CNF_STRU    stIpsTraceCfgCnf;

    pRcvMsg = (OM_IPS_ADVANCED_TRACE_CONFIG_REQ_STRU *)pMsg;

    /*检测配置参数是否合法*/
    enResult = IPS_MNTN_TraceAdvancedCfgChkParam(&(pRcvMsg->stIpsAdvanceCfgReq));

    /* Fill DIAG trans msg header */
    stIpsTraceCfgCnf.stDiagHdr.ulSenderCpuId        = VOS_LOCAL_CPUID;
    stIpsTraceCfgCnf.stDiagHdr.ulSenderPid          = ACPU_PID_NFEXT;
    stIpsTraceCfgCnf.stDiagHdr.ulReceiverCpuId      = VOS_LOCAL_CPUID;
    stIpsTraceCfgCnf.stDiagHdr.ulReceiverPid        = MSP_PID_DIAG_APP_AGENT;   /* 把应答消息发送给DIAG，由DIAG把透传命令的处理结果发送给HIDS工具*/
    stIpsTraceCfgCnf.stDiagHdr.ulLength             = sizeof(IPS_OM_ADVANCED_TRACE_CONFIG_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    stIpsTraceCfgCnf.stDiagHdr.ulMsgId              = ID_IPS_OM_ADVANCED_TRACE_CONFIG_CNF;

    /* DIAG透传命令中的特定信息*/
    stIpsTraceCfgCnf.stDiagHdr.usOriginalId         = pRcvMsg->stDiagHdr.usOriginalId;
    stIpsTraceCfgCnf.stDiagHdr.usTerminalId         = pRcvMsg->stDiagHdr.usTerminalId;
    stIpsTraceCfgCnf.stDiagHdr.ulTimeStamp          = pRcvMsg->stDiagHdr.ulTimeStamp;
    stIpsTraceCfgCnf.stDiagHdr.ulSN                 = pRcvMsg->stDiagHdr.ulSN;

    if ( PS_FALSE == enResult )
    {
        /*如果参数检测不合法，向OM回复配置失败*/
        stIpsTraceCfgCnf.stIpsAdvanceCfgCnf.enRslt  =   PS_FAIL;

        IPS_MNTN_SndCfgCnf2Om(ID_IPS_OM_ADVANCED_TRACE_CONFIG_CNF,
            sizeof(IPS_OM_ADVANCED_TRACE_CONFIG_CNF_STRU), &stIpsTraceCfgCnf );

        TTF_LOG(ACPU_PID_NFEXT, DIAG_MODE_COMM, PS_PRINT_ERROR,
            "Warning: IPS_MNTN_TraceAdvancedCfgReq check fail");

        return;
    }

#if (FEATURE_ON == FEATURE_NFEXT)
    enResult = NFExt_ConfigEffective(&(pRcvMsg->stIpsAdvanceCfgReq));
    if( PS_FALSE == enResult )
    {
        /*如果注册钩子函数失败，向OM回复配置失败*/
        stIpsTraceCfgCnf.stIpsAdvanceCfgCnf.enRslt =   PS_FAIL;

        IPS_MNTN_SndCfgCnf2Om(ID_IPS_OM_ADVANCED_TRACE_CONFIG_CNF,
            sizeof(IPS_OM_ADVANCED_TRACE_CONFIG_CNF_STRU), &stIpsTraceCfgCnf );

        TTF_LOG(ACPU_PID_NFEXT, DIAG_MODE_COMM, PS_PRINT_ERROR,
            "Warning: IPS_MNTN_SetCallbackFunc fail");

        return;
    }
#endif

    /*保存配置参数*/
    PS_MEM_CPY(&g_stIpsTraceMsgCfg, &(pRcvMsg->stIpsAdvanceCfgReq), sizeof(IPS_MNTN_TRACE_CONFIG_REQ_STRU));

    /*向OM回复配置成功*/
    stIpsTraceCfgCnf.stIpsAdvanceCfgCnf.enRslt = PS_SUCC;

    IPS_MNTN_SndCfgCnf2Om(ID_IPS_OM_ADVANCED_TRACE_CONFIG_CNF,
            sizeof(IPS_OM_ADVANCED_TRACE_CONFIG_CNF_STRU), &stIpsTraceCfgCnf );

    return;

}

/*****************************************************************************
 函 数 名  :IPS_MNTN_Ipv4DataParse
 功能描述  :解析IP包信息
 输入参数  :IPS_MNTN_IP_INFO_STRU *pstTraceMsg
            VOS_UINT8 *pData
 输出参数  :
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   :  2012年10月29日
    作    者   :  00199705
    修改内容   :  创建函数
*****************************************************************************/
VOS_VOID IPS_MNTN_Ipv4DataParse(IPS_MNTN_IP_INFO_STRU *pstIpInfo,VOS_UINT8 *pData)
{
    switch (pstIpInfo->ucL4Proto)
    {
        case IP_IPV4_PROTO_TCP:
            pstIpInfo->usSrcPort      = IP_GET_VAL_NTOH_U16(pData, IP_IPV4_HEAD_LEN);
            pstIpInfo->usDstPort      = IP_GET_VAL_NTOH_U16(pData, (IP_IPV4_HEAD_LEN + IP_IPV4_DST_PORT_POS));
            pstIpInfo->ulL4Id         = IP_GET_VAL_NTOH_U32(pData, (IP_IPV4_HEAD_LEN + IP_IPV4_TCP_SEQ_POS));
            pstIpInfo->ulTcpAckSeq    = IP_GET_VAL_NTOH_U32(pData, (IP_IPV4_HEAD_LEN + IP_IPV4_TCP_ACK_POS));
            break;

        case IP_IPV4_PROTO_UDP:
            pstIpInfo->usSrcPort      = IP_GET_VAL_NTOH_U16(pData, IP_IPV4_HEAD_LEN);
            pstIpInfo->usDstPort      = IP_GET_VAL_NTOH_U16(pData, (IP_IPV4_HEAD_LEN + IP_IPV4_DST_PORT_POS));
            break;

        case IP_IPV4_PROTO_ICMP:
            pstIpInfo->ucIcmpType     = IP_GET_VAL_NTOH_U8(pData, IP_IPV4_HEAD_LEN);
            if ((IP_IPV4_ICMP_ECHO_REQUEST == pstIpInfo->ucIcmpType)
                ||(IP_IPV4_ICMP_ECHO_REPLY == pstIpInfo->ucIcmpType))
            {
                pstIpInfo->ulL4Id     = IP_GET_VAL_NTOH_U32(pData, (IP_IPV4_HEAD_LEN + IP_IPV4_ICMP_IDENTIFY_POS));
            }
            break;

        default:
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  :IPS_MNTN_Ipv6DataParse
 功能描述  :解析IP包信息
 输入参数  :IPS_MNTN_IP_INFO_STRU *pstTraceMsg
            VOS_UINT8 *pData
 输出参数  :
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   :  2012年10月29日
    作    者   :  00199705
    修改内容   :  创建函数
*****************************************************************************/
VOS_VOID IPS_MNTN_Ipv6DataParse(IPS_MNTN_IP_INFO_STRU *pstIpInfo,VOS_UINT8 *pData)
{
    switch (pstIpInfo->ucL4Proto)
    {
        case IP_IPV6_PROTO_TCP:
            pstIpInfo->usSrcPort      = IP_GET_VAL_NTOH_U16(pData, IP_IPV6_HEAD_LEN);
            pstIpInfo->usDstPort      = IP_GET_VAL_NTOH_U16(pData, (IP_IPV6_HEAD_LEN + IP_IPV6_DST_PORT_POS));
            pstIpInfo->ulL4Id         = IP_GET_VAL_NTOH_U32(pData, (IP_IPV6_HEAD_LEN + IP_IPV6_TCP_SEQ_POS));
            pstIpInfo->ulTcpAckSeq    = IP_GET_VAL_NTOH_U32(pData, (IP_IPV6_HEAD_LEN + IP_IPV6_TCP_ACK_POS));
            break;

        case IP_IPV6_PROTO_UDP:
            pstIpInfo->usSrcPort      = IP_GET_VAL_NTOH_U16(pData, IP_IPV6_HEAD_LEN);
            pstIpInfo->usDstPort      = IP_GET_VAL_NTOH_U16(pData, (IP_IPV6_HEAD_LEN + IP_IPV6_DST_PORT_POS));
            break;

        case IP_IPV6_PROTO_ICMP:
            pstIpInfo->ucIcmpType     = IP_GET_VAL_NTOH_U8(pData, IP_IPV6_HEAD_LEN);
            if ((IP_IPV6_ICMP_ECHO_REQUEST == pstIpInfo->ucIcmpType)
                ||(IP_IPV6_ICMP_ECHO_REPLY == pstIpInfo->ucIcmpType))
            {
                pstIpInfo->ulL4Id     = IP_GET_VAL_NTOH_U32(pData, (IP_IPV6_HEAD_LEN + IP_IPV4_ICMP_IDENTIFY_POS));
            }
            break;

        default:
            break;
    }

    return;
}


/*****************************************************************************
 函 数 名  :IPS_MNTN_GetIPInfoCfg
 功能描述  :IP包抓包配置信息
 输入参数  :VOS_UINT16 usType
 输出参数  :
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   :  2012年10月29日
    作    者   :  00199705
    修改内容   :  创建函数
*****************************************************************************/
VOS_UINT32 IPS_MNTN_GetIPInfoCfg(TTF_MNTN_MSG_TYPE_ENUM_UINT16 enType)
{
    if ((ID_IPS_TRACE_ADS_UL == enType)||(ID_IPS_TRACE_ADS_DL == enType))
    {
        if (WTTF_TRACE_MSG_YES == g_stIpsTraceMsgCfg.enAdsIPConfig)
        {
            return PS_TRUE;
        }
    }

    return PS_FALSE;
}

/*****************************************************************************
 函 数 名  : IPS_MNTN_TraceIpInfo
 功能描述  : 向OM发送透传消息
 输入参数  : skb_buff  IP数据包
             usType    消息ID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月15日
    作    者   : 00199705
    修改内容   : 新生成函数

*****************************************************************************/
/*lint -esym( 593, pucTraceData ) */
VOS_VOID IPS_MNTN_TraceIpInfo(
    struct sk_buff *skb,
    TTF_MNTN_MSG_TYPE_ENUM_UINT16 enType,
    VOS_UINT32 ulParam1,
    VOS_UINT32 ulParam2,
    VOS_UINT32 ulParam3,
    VOS_UINT32 ulParam4)
{
    VOS_UINT32                      ulRst;
    VOS_UINT8                      *pIpData;
    VOS_UINT16                      usIpDataLen;
    IPS_MNTN_IP_INFO_STRU          *pstIpInfo;
    VOS_UINT8                      *pucTraceData;

    /* HIDS未连接 */
    if (VOS_NO == DIAG_GetConnState())
    {
        return;
    }

    ulRst = IPS_MNTN_GetIPInfoCfg(enType);
    if(PS_FALSE == ulRst)
    {
        /*不捕获该报文*/
        return;
    }

    if ((VOS_NULL_PTR == skb)||(VOS_NULL_PTR == skb->data))
    {
        TTF_LOG(ACPU_PID_NFEXT, DIAG_MODE_COMM, PS_PRINT_ERROR,
            "IPS, IPS_MNTN_TraceIpInfo, ERROR, skb or skb->data is NULL ");
        return;
    }

    /* USB抓取的skb data可能是IP数据包或者是带MAC头的IP数据包*/
    pIpData         = skb->data;

    if (IP_IPV4_VER_AND_HEAD == *pIpData)
    {
        usIpDataLen = IP_GET_VAL_NTOH_U16(pIpData, IP_IPV4_DATA_LEN_POS);
    }
    else if (IP_IPV6_VER_AND_HEAD == *pIpData)
    {
        usIpDataLen = IP_GET_VAL_NTOH_U16(pIpData, IP_IPV6_DATA_LEN_POS);
    }
    else
    {
        usIpDataLen = 0;
    }

    if (usIpDataLen != skb->len)
    {
        pIpData     += MAC_HEAD_LEN;
    }

    /* 从Linux内核申请内存 */
    pucTraceData = NF_EXT_MEM_ALLOC(ACPU_PID_NFEXT, MNTN_IP_INFO_LEN + sizeof(DIAG_TRANS_IND_STRU));
    if (VOS_NULL_PTR == pucTraceData)
    {
        NF_EXT_STATS_INC(1, NF_EXT_STATS_ALLOC_MEM_FAIL);
        return;
    }

    pstIpInfo               = (IPS_MNTN_IP_INFO_STRU *)(pucTraceData + sizeof(DIAG_TRANS_IND_STRU));
    pstIpInfo->ucIpVer      = *pIpData>>IP_PROTO_VERSION_POS;

    pstIpInfo->usPrimId     = enType;

    pstIpInfo->ulParam1     = ulParam1;
    pstIpInfo->ulParam2     = ulParam2;
    pstIpInfo->ulParam3     = ulParam3;
    pstIpInfo->ulParam4     = ulParam4;

    /* IP报文解析TCP,UDP,ICMP，不解析IP的扩展头*/
    if (IP_IPV4_PROTO_VERSION == pstIpInfo->ucIpVer)
    {
        pstIpInfo->usDataLen  = IP_GET_VAL_NTOH_U16(pIpData, IP_IPV4_DATA_LEN_POS);
        if ((pstIpInfo->usDataLen == skb->len)||(pstIpInfo->usDataLen == (skb->len - MAC_HEAD_LEN)))
        {
            pstIpInfo->usIp4Id    = IP_GET_VAL_NTOH_U16(pIpData, IP_IPV4_IDENTIFY_POS);
            pstIpInfo->ucL4Proto  = IP_GET_VAL_NTOH_U8(pIpData, IP_IPV4_PROTO_POS);

            IPS_MNTN_Ipv4DataParse(pstIpInfo, pIpData);
        }
    }

    if (IP_IPV6_PROTO_VERSION == pstIpInfo->ucIpVer)
    {
        pstIpInfo->usDataLen  = IP_GET_VAL_NTOH_U16(pIpData, IP_IPV6_DATA_LEN_POS);
        if ((pstIpInfo->usDataLen == skb->len)||(pstIpInfo->usDataLen == (skb->len - MAC_HEAD_LEN)))
        {
            pstIpInfo->ucL4Proto  = IP_GET_VAL_NTOH_U8(pIpData, IP_IPV6_PROTO_POS);
            pstIpInfo->usIp4Id    = 0;

            IPS_MNTN_Ipv6DataParse(pstIpInfo, pIpData);
        }
    }

    if (VOS_OK != IPS_MNTN_TransMsg(pucTraceData, MNTN_IP_INFO_LEN, enType))
    {
        NF_EXT_MEM_FREE(ACPU_PID_NFEXT, pucTraceData);
    }

    return;
}
/*lint +esym( 593, pucTraceData ) */
