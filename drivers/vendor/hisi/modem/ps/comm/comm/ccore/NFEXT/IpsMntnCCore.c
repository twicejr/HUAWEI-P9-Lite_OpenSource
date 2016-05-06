/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : IpsMntnCCore.c
  版 本 号   : 初稿
  作    者   : caikai
  生成日期   : 2013年7月22日
  最近修改   :
  功能描述   : IPS MNTN模块实现
  函数列表   :
  修改历史   :
  1.日    期   : 2013年7月22日
    作    者   : caikai
    修改内容   : 创建文件

******************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "IpsMntnCCore.h"

#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e534*/
#define    THIS_FILE_ID        PS_FILE_ID_IPS_MNTN_CCORE_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
IPS_MNTN_CCORE_TRACE_CONFIG_REQ_STRU          g_stIpsCcoreTraceMsgCfg;     /*TCP/IP协议栈可维可测配置信息*/
IPS_MNTN_CCORE_INFO_ENTITY                    g_stIpsCcoreMntnInfoEntity;  /*TCP/IP协议栈可维可测实体*/

/* 用于周期性上报的内存 */
VOS_UINT8                                     g_aucIpsCCoreInfo[IPS_CCORE_INFO_LEN] = {0};

TCPIP_LOG_HOOK_FUNC stLogHook           = {IPS_MNTN_CCORE_TCPIP_FixlenLogOutput, IPS_MNTN_CCORE_TCPIP_VarlenLogOutput};
gpfTCPIPInfoOutput  pFnInfoHook         = IPS_MNTN_CCORE_PrintInfoCB;
gpfTCPIPDebugOutput pFnDebugHook        = IPS_MNTN_CCORE_PrintInfoCB;

IPS_MNTN_CCORE_HOOK_MASK_OPS_STRU             g_stIpsCcoreHookMaskOpt[] =
{
    {
        IPS_MNTN_CCORE_IPV4_CAPTRURE_UP_MASK,
        IP_PP4_HOOK_INPUT_ALL_PKT,
        0,
        IPS_MNTN_CCORE_IpLayerUpCapCB,
        (pfRegHook)TCPIP_IP_PP4_Intermediate_Hook_Register,
        (pfUnRegHook)TCPIP_IP_PP4_Intermediate_Hook_UnRegister
    },
    {
        IPS_MNTN_CCORE_IPV4_CAPTRURE_DOWN_MASK,
        IP_PP4_HOOK_OUTPUT_ALL_PKT,
        0,
        IPS_MNTN_CCORE_IpLayerDownCapCB,
        (pfRegHook)TCPIP_IP_PP4_Intermediate_Hook_Register,
        (pfUnRegHook)TCPIP_IP_PP4_Intermediate_Hook_UnRegister
    },
    {
        IPS_MNTN_CCORE_IPV6_CAPTRURE_UP_MASK,
        PP_INPUT_TYPE,
        0,
        IPS_MNTN_CCORE_IpLayerUpCapCB,
        (pfRegHook)TCPIP_IP_PP6_Intermediate_Hook_Register,
        VOS_NULL_PTR
    },
    {
        IPS_MNTN_CCORE_IPV6_CAPTRURE_DOWN_MASK,
        PP_IFOUTPUT_TYPE,
        0,
        IPS_MNTN_CCORE_IpLayerDownCapCB,
        (pfRegHook)TCPIP_IP_PP6_Intermediate_Hook_Register,
        VOS_NULL_PTR
    },
};

VOS_UINT32 g_ulCurrMask = 0; /* 当前Hook掩码 */

extern VOS_UINT32 RTOSCK_AdapterInit(VOS_VOID);
extern VOS_UINT32 VISP_InitTCPIPStack(VOS_VOID);

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958 */
/*****************************************************************************
 函 数 名  : IPS_MNTN_CCORE_SndTransInd2Om
 功能描述  : 向OM发送透传消息
 输入参数  : pTransMsgContent       透传消息内容指针
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月30日
    作    者   : f00166181
    修改内容   : 新生成函数
  2.日    期   : 2013年7月30日
    作    者   : caikai
    修改内容   : VoLTE特性需要将其移植至V9

*****************************************************************************/
VOS_VOID IPS_MNTN_CCORE_TransMsg
(
    VOS_UINT8                                       *pucTransMsg,
    VOS_UINT32                                       ulTransMsgContentLen,
    TTF_MNTN_MSG_TYPE_ENUM_UINT16                    enMsgName
)
{
    DIAG_TRANS_IND_STRU        *pstTransData;
    MODEM_ID_ENUM_UINT16        enModemId;

    pstTransData                = (DIAG_TRANS_IND_STRU *)pucTransMsg;

    enModemId                   = VOS_GetModemIDFromPid(UEPS_PID_IPS_CCORE);

    /* 填充信息 */
    pstTransData->ulPid         = UEPS_PID_IPS_CCORE;
    pstTransData->ulMsgId       = enMsgName;
    pstTransData->ulModule      = DIAG_GEN_MODULE(enModemId, DIAG_MODE_COMM);
    pstTransData->ulLength      = ulTransMsgContentLen;
    pstTransData->pData         = pucTransMsg + IPS_CCORE_OM_TRANS_DATA_OFFSET_LEN;

    if ( VOS_OK != DIAG_TransReport((DIAG_TRANS_IND_STRU *)pucTransMsg) )
    {
        TTF_LOG(UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
            "IPS, IPS_MNTN_CCORE_TransMsg, ERROR, Call DIAG_TransReport fail!");
    }

    return;
}

/*****************************************************************************
 函 数 名  : IPS_MNTN_CCORE_SndCfgCnf2Om
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
  2.日    期   : 2013年7月30日
    作    者   : caikai
    修改内容   : VoLTE特性需要将其移植至V9

*****************************************************************************/
VOS_VOID IPS_MNTN_CCORE_SndCfgCnf2Om
(
    VOS_UINT16      usPrimId,
    VOS_UINT16      usTransMsgContentLen,
    VOS_VOID       *pTransMsgContent
)
{
    MsgBlock                *pSendMsg;

    /*分配并填写消息*/
    pSendMsg = VOS_AllocMsg(UEPS_PID_IPS_CCORE, usTransMsgContentLen - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pSendMsg)
    {
        TTF_LOG(UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
                                "Error: IPS_MNTN_CCORE_SndCfgCnf2Om, ERROR, Call VOS_AllocMsg fail!");
        return;
    }

    mdrv_memcpy(pSendMsg, pTransMsgContent, usTransMsgContentLen);

    if ( VOS_OK != VOS_SendMsg(UEPS_PID_IPS_CCORE, pSendMsg) )
    {
        TTF_LOG(UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
                                "Error: IPS_MNTN_CCORE_SndCfgCnf2Om, ERROR, Call VOS_SendMsg fail!");
    }

    return;
}

/*****************************************************************************
 函 数 名  : IPS_MNTN_CCORE_ChkMntnInfoIsStart
 功能描述  : 检测是否启动捕获TCP/IP协议栈基础信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_YES    -   已启动
             VOS_NO     -   未启动
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年8月3日
    作    者   : f00166181
    修改内容   : 新生成函数
  2.日    期   : 2013年7月30日
    作    者   : caikai
    修改内容   : VoLTE特性需要将其移植至V9

*****************************************************************************/
VOS_UINT32 IPS_MNTN_CCORE_ChkMntnInfoIsStart(VOS_VOID)
{
    /*判断定时器是否启动*/
    if(IPS_MNTN_CCORE_INFO_REPORT_START == g_stIpsCcoreMntnInfoEntity.enIpsMntnFlag)
    {
        return PS_TRUE;
    }
    else if(IPS_MNTN_CCORE_INFO_REPORT_STOP == g_stIpsCcoreMntnInfoEntity.enIpsMntnFlag)
    {
        return PS_FALSE;
    }
    else
    {
        return PS_FALSE;
    }
}

/*****************************************************************************
 函 数 名  : IPS_MNTN_CCORE_StartRelTimer
 功能描述  : 启定时器，如果该定时器已启动，则将其重新启动
 输入参数  : HTIMER     *phTm
             VOS_PID     Pid
             VOS_UINT32  ulLength
             VOS_UINT32  ulName
             VOS_UINT32  ulParam
             VOS_UINT8   ucMode
             VOS_TIMER_PRECISION_ENUM_UINT32 enPrecision  指示26M 还是 32K时钟精度
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年8月3日
    作    者   : f00166181
    修改内容   : 新生成函数
  2.日    期   : 2013年7月30日
    作    者   : caikai
    修改内容   : VoLTE特性需要将其移植至V9

*****************************************************************************/
VOS_UINT32 IPS_MNTN_CCORE_StartRelTimer
(
    HTIMER                         *phTm,
    VOS_PID                         Pid,
    VOS_UINT32                      ulLength,
    VOS_UINT32                      ulName,
    VOS_UINT32                      ulParam,
    VOS_UINT8                       ucMode,
    VOS_TIMER_PRECISION_ENUM_UINT32 enPrecision
)
{
    VOS_UINT32      ulErrCode;

    /*=============*/   /*定时器已经启动，则重新启动*/
    if (VOS_NULL_PTR != *phTm)
    {
        ulErrCode = VOS_RestartRelTimer(phTm);

        if ( VOS_OK != ulErrCode )
        {
            TTF_LOG1(UEPS_PID_IPS_CCORE, PS_SUBMOD_NULL, PS_PRINT_ERROR,
                "IPS, IPS_MNTN_CCORE_StartRelTimer, ERROR, Call VOS_RestartRelTimer fail!\
                ulErrCode:<1>", (VOS_INT32)ulErrCode);
            return PS_FAIL;
        }
    }
    /*=============*/   /*定时器未启动，则启动定时器*/
    else
    {
        ulErrCode = VOS_StartRelTimer(phTm, Pid, ulLength, ulName, ulParam, ucMode, enPrecision);

        if ( VOS_OK != ulErrCode )
        {
            TTF_LOG1(UEPS_PID_IPS_CCORE, PS_SUBMOD_NULL, PS_PRINT_ERROR,
                "IPS, IPS_MNTN_CCORE_StartRelTimer, ERROR, Call VOS_StartRelTimer fail!\
                 ulErrCode:<1>", (VOS_INT32)ulErrCode);
            return PS_FAIL;
        }
    }

    return PS_SUCC;
}

/*****************************************************************************
 函 数 名  : IPS_MNTN_CCORE_StopMntnInfoTimer
 功能描述  : 停止捕获TCP/IP协议栈的定时器
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年8月3日
    作    者   : f00166181
    修改内容   : 新生成函数
  2.日    期   : 2013年7月30日
    作    者   : caikai
    修改内容   : VoLTE特性需要将其移植至V9

*****************************************************************************/
VOS_VOID IPS_MNTN_CCORE_StopMntnInfoTimer(VOS_VOID)
{
    VOS_UINT32  ulErrCode;
    /*判断定时器指针是否为空*/
    if ( VOS_NULL_PTR != g_stIpsCcoreMntnInfoEntity.hIpsMntnTimer )
    {
        /*如果不为空，则停止定时器*/
        ulErrCode = VOS_StopRelTimer(&g_stIpsCcoreMntnInfoEntity.hIpsMntnTimer);

        if ( VOS_OK != ulErrCode )
        {
            g_stIpsCcoreMntnInfoEntity.hIpsMntnTimer = VOS_NULL_PTR;

            TTF_LOG1(UEPS_PID_IPS_CCORE, PS_SUBMOD_NULL, PS_PRINT_ERROR,
                "IPS, IPS_MNTN_CCORE_StopMntnInfoTimer, ERROR, Call VOS_StopRelTimer \
                fail! ulErrCode:<1>", (VOS_INT32)ulErrCode);
        }
    }
}

/*****************************************************************************
 函 数 名  : IPS_MNTN_CCORE_GetPktLenByTraceCfg
 功能描述  : 根据消息配置信息，获取捕获报文长度
 输入参数  : pstTraceCfg        消息配置信息
             usDataLen          报文长度

 输出参数  : pulTraceCfgLen     捕获报文长度
 返 回 值  : PS_TRUE        -   捕获报文
             PS_FALSE       -   不捕获报文
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年8月3日
    作    者   : f00166181
    修改内容   : 新生成函数
  2.日    期   : 2013年7月30日
    作    者   : caikai
    修改内容   : VoLTE特性需要将其移植至V9

*****************************************************************************/
VOS_UINT32 IPS_MNTN_CCORE_GetPktLenByTraceCfg
(
    IPS_MNTN_CCORE_TRACE_CONFIG_STRU     *pstTraceCfg,
    VOS_UINT16                            usPktLen,
    VOS_UINT32                           *pulDataLen
)
{
    *pulDataLen    =   0;

    /*判断定时器是否启动*/
    switch ( pstTraceCfg->ulChoice )
    {
        case IPS_MNTN_CCORE_TRACE_NULL_CHOSEN:
            return PS_FALSE;
        case IPS_MNTN_CCORE_TRACE_MSG_HEADER_CHOSEN:
            break;
        case IPS_MNTN_CCORE_TRACE_CONFIGURABLE_LEN_CHOSEN:
            *pulDataLen = TTF_MIN(pstTraceCfg->ulTraceDataLen, usPktLen);
            break;
        case IPS_MNTN_CCORE_TRACE_WHOLE_DATA_LEN_CHOSEN:
            *pulDataLen = usPktLen;
            break;
        default:
            return PS_FALSE;
    }

    return PS_TRUE;
}

/*****************************************************************************
 函 数 名  : IPS_MNTN_CCORE_CCORE_BridgePktInfo
 功能描述  : 捕获网桥中转报文函数
 输入参数  : aucSrcPort     发送虚拟网卡信息
             aucDestPort    接受虚拟网卡信息
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
  2.日    期   : 2013年7月30日
    作    者   : caikai
    修改内容   : VoLTE特性需要将其移植至V9

*****************************************************************************/
VOS_VOID IPS_MNTN_CCORE_BridgePktInfo
(
    VOS_UINT8                                   *pucSrcPort,
    VOS_UINT8                                   *pucDestPort,
    VOS_UINT8                                   *pucPktData,
    VOS_UINT16                                   usPktLen,
    TTF_MNTN_MSG_TYPE_ENUM_UINT16                usType
)
{
    VOS_UINT8                                *pucTraceData;
    IPS_MNTN_CCORE_TRACE_CONFIG_STRU         *pstTraceCfg;
    IPS_MNTN_CCORE_BRIDGE_PKT_INFO_STRU      *pstTraceMsg;
    VOS_UINT32                                ulTransDataLen;
    VOS_UINT32                                ulDataLen;
    VOS_UINT32                                ulRst;

    ulTransDataLen  =   0;
    ulDataLen       =   0;

    if ( VOS_NULL_PTR == pucPktData )
    {
        TTF_LOG(UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
            "IPS, IPS_MNTN_CCORE_BridgePktInfo, ERROR, paucPktData is NULL ");
        return;
    }

    /*根据消息类型选择对应配置信息*/
    if(ID_IPS_CCORE_TRACE_BRIDGE_DATA_INFO == usType)
    {
        pstTraceCfg = &(g_stIpsCcoreTraceMsgCfg.stBridgeTraceCfg);
    }
    else
    {
        /*打印警告信息,消息类型不匹配*/
        TTF_LOG( UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
                "IPS, IPS_MNTN_CCORE_BridgePktInfo : ERROR : usType is not Expectes!" );
        return;
    }

    /*根据消息配置信息，获取输出报文长度*/
    ulRst = IPS_MNTN_CCORE_GetPktLenByTraceCfg(pstTraceCfg, usPktLen, &ulDataLen);
    if(PS_FALSE == ulRst)
    {
        /*不捕获该报文*/
        return;
    }

    ulDataLen           = PS_MIN(IPS_MNTN_CCORE_TRACE_MAX_BYTE_LEN, ulDataLen);
    ulTransDataLen      = (IPS_CCORE_BRIDGE_PKT_INFO_OFFSET_LEN + ulDataLen);

    pucTraceData        = PS_MEM_ALLOC(UEPS_PID_IPS_CCORE, ulTransDataLen + IPS_CCORE_OM_TRANS_DATA_OFFSET_LEN);
    if (VOS_NULL_PTR == pucTraceData)
    {
        /*打印警告信息,申请内存失败*/
        TTF_LOG( UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
                "IPS, IPS_MNTN_CCORE_BridgePktInfo : ERROR : alloc mem failed!" );

        return;
    }

    /*构建透明消息*/
    pstTraceMsg             = (IPS_MNTN_CCORE_BRIDGE_PKT_INFO_STRU *)(pucTraceData + IPS_CCORE_OM_TRANS_DATA_OFFSET_LEN);
    pstTraceMsg->usLen      = usPktLen;
    pstTraceMsg->usPrimId   = usType;
    PS_MEM_CPY(pstTraceMsg->aucSrcPort, pucSrcPort, IPS_CCORE_END_NAME);
    PS_MEM_CPY(pstTraceMsg->aucDestPort, pucDestPort, IPS_CCORE_END_NAME);

    /*lint -e669 */
    PS_MEM_CPY(pstTraceMsg->aucData, pucPktData, ulDataLen);
    /*lint +e669 */

    IPS_MNTN_CCORE_TransMsg(pucTraceData, ulTransDataLen, usType);

    PS_MEM_FREE(UEPS_PID_IPS_CCORE, pucTraceData);
}

/*****************************************************************************
 函 数 名  : IPS_MNTN_CCORE_BridgePktInfoCB
 功能描述  : 捕获网桥中转报文回调函数
 输入参数  : pstIpsMntnCapturePara  回调函数参数结构
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月1日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID IPS_MNTN_CCORE_BridgePktInfoCB
(
    IPS_MNTN_CCORE_CAPTURE_PARA_STRU *pstIpsMntnCapturePara
)
{
    VOS_UINT8                                   *pucSrcPort;
    VOS_UINT8                                   *pucDestPort;
    VOS_UINT8                                   *pucPktData;
    VOS_UINT16                                   usPktLen;

    if ( VOS_NULL_PTR == pstIpsMntnCapturePara )
    {
        TTF_LOG(UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
            "IPS, IPS_MNTN_CCORE_BridgePktInfoCB, ERROR, pstIpsMntnCapturePara is NULL ");
        return;
    }

    pucSrcPort      = pstIpsMntnCapturePara->paucSrcPort;
    pucDestPort     = pstIpsMntnCapturePara->paucDestPort;
    pucPktData      = pstIpsMntnCapturePara->pucData;
    usPktLen        = pstIpsMntnCapturePara->usLen;

    IPS_MNTN_CCORE_BridgePktInfo(pucSrcPort, pucDestPort, pucPktData, usPktLen, ID_IPS_CCORE_TRACE_BRIDGE_DATA_INFO);

    return;
}

/*****************************************************************************
 函 数 名  : IPS_MNTN_CCORE_CtrlPktInfo
 功能描述  : 捕获TCP/IP协议栈控制报文函数
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
  2.日    期   : 2013年7月30日
    作    者   : caikai
    修改内容   : VoLTE特性需要将其移植至V9

*****************************************************************************/
VOS_VOID IPS_MNTN_CCORE_CtrlPktInfo
(
    VOS_UINT8                                     *pucNetIfName,
    VOS_UINT8                                     *pucPktData,
    VOS_UINT16                                     usPktLen,
    TTF_MNTN_MSG_TYPE_ENUM_UINT16                  usType
)
{
    VOS_UINT8                                *pucTraceData;
    IPS_MNTN_CCORE_PKT_INFO_STRU             *pstTraceMsg;
    VOS_UINT32                                ulTransDataLen;
    VOS_UINT32                                ulDataLen;

    ulTransDataLen  =   0;
    ulDataLen       =   0;

    if ( VOS_NULL_PTR == pucPktData )
    {
        TTF_LOG(UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
            "IPS, IPS_MNTN_CCORE_CtrlPktInfo, ERROR, pucPktData is NULL ");
        return;
    }

    ulDataLen           = PS_MIN(IPS_MNTN_CCORE_TRACE_MAX_BYTE_LEN, usPktLen);
    ulTransDataLen      = (IPS_CCORE_PKT_INFO_OFFSET_LEN + ulDataLen);

    pucTraceData        = PS_MEM_ALLOC(UEPS_PID_IPS_CCORE, ulTransDataLen + IPS_CCORE_OM_TRANS_DATA_OFFSET_LEN);
    if (VOS_NULL_PTR == pucTraceData)
    {
        /*打印警告信息,申请内存失败*/
        TTF_LOG( UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
                "IPS, IPS_MNTN_CCORE_CtrlPktInfo : ERROR : alloc mem failed!" );

        return;
    }

    /*构建透明消息*/
    pstTraceMsg             = (IPS_MNTN_CCORE_PKT_INFO_STRU *)(pucTraceData + IPS_CCORE_OM_TRANS_DATA_OFFSET_LEN);
    pstTraceMsg->usLen      = usPktLen;
    pstTraceMsg->usPrimId   = usType;
    PS_MEM_CPY(pstTraceMsg->aucNetIfName, pucNetIfName, IPS_CCORE_IFNAMSIZ);
    /*lint -e669 */
    PS_MEM_CPY(pstTraceMsg->aucData, pucPktData, ulDataLen);
    /*lint +e669 */

    IPS_MNTN_CCORE_TransMsg(pucTraceData, ulTransDataLen, usType);

    PS_MEM_FREE(UEPS_PID_IPS_CCORE, pucTraceData);
}

/*****************************************************************************
 函 数 名  : IPS_MNTN_CCORE_ArpRecvPktInfoCB
 功能描述  : 捕获TCP/IP协议栈接收的ARP控制报文回调函数
 输入参数  : pstIpsMntnCapturePara  回调函数参数结构
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月1日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID IPS_MNTN_CCORE_ArpRecvPktInfoCB
(
    IPS_MNTN_CCORE_CAPTURE_PARA_STRU *pstIpsMntnCapturePara
)
{
    VOS_UINT8                                    *pucNetIfName;
    VOS_UINT8                                    *pucPktData;
    VOS_UINT16                                    usPktLen;

    if ( VOS_NULL_PTR == pstIpsMntnCapturePara )
    {
        TTF_LOG(UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
            "IPS, IPS_MNTN_CCORE_ArpRecvPktInfoCB, ERROR, pstIpsMntnCapturePara is NULL ");
        return;
    }

    pucNetIfName    = pstIpsMntnCapturePara->paucNetIfName;
    pucPktData      = pstIpsMntnCapturePara->pucData;
    usPktLen        = pstIpsMntnCapturePara->usLen;

    IPS_MNTN_CCORE_CtrlPktInfo(pucNetIfName, pucPktData, usPktLen, ID_IPS_CCORE_TRACE_RECV_ARP_PKT);

    return;
}

/*****************************************************************************
 函 数 名  : IPS_MNTN_CCORE_ArpSendPktInfoCB
 功能描述  : 捕获TCP/IP协议栈发送的ARP控制报文回调函数
 输入参数  : pstIpsMntnCapturePara  回调函数参数结构
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月1日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID IPS_MNTN_CCORE_ArpSendPktInfoCB
(
    IPS_MNTN_CCORE_CAPTURE_PARA_STRU *pstIpsMntnCapturePara
)
{
    VOS_UINT8                                    *pucNetIfName;
    VOS_UINT8                                    *pucPktData;
    VOS_UINT16                                    usPktLen;

    if ( VOS_NULL_PTR == pstIpsMntnCapturePara )
    {
        TTF_LOG(UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
            "IPS, IPS_MNTN_CCORE_ArpSendPktInfoCB, ERROR, pstIpsMntnCapturePara is NULL ");
        return;
    }

    pucNetIfName    = pstIpsMntnCapturePara->paucNetIfName;
    pucPktData      = pstIpsMntnCapturePara->pucData;
    usPktLen        = pstIpsMntnCapturePara->usLen;

    IPS_MNTN_CCORE_CtrlPktInfo(pucNetIfName, pucPktData, usPktLen, ID_IPS_CCORE_TRACE_SEND_ARP_PKT);

    return;
}

/*****************************************************************************
 函 数 名  : IPS_MNTN_CCORE_DhcpcRecvPktInfoCB
 功能描述  : 捕获TCP/IP协议栈接收的DHCP控制报文回调函数
 输入参数  : pstIpsMntnCapturePara  回调函数参数结构
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月1日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID IPS_MNTN_CCORE_DhcpcRecvPktInfoCB
(
    IPS_MNTN_CCORE_CAPTURE_PARA_STRU *pstIpsMntnCapturePara
)
{
    VOS_UINT8                                    *pucNetIfName;
    VOS_UINT8                                    *pucPktData;
    VOS_UINT16                                    usPktLen;

    if ( VOS_NULL_PTR == pstIpsMntnCapturePara )
    {
        TTF_LOG(UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
            "IPS, IPS_MNTN_CCORE_DhcpcRecvPktInfoCB, ERROR, pstIpsMntnCapturePara is NULL ");
        return;
    }

    pucNetIfName    = pstIpsMntnCapturePara->paucNetIfName;
    pucPktData      = pstIpsMntnCapturePara->pucData;
    usPktLen        = pstIpsMntnCapturePara->usLen;

    IPS_MNTN_CCORE_CtrlPktInfo(pucNetIfName, pucPktData, usPktLen, ID_IPS_CCORE_TRACE_RECV_DHCPC_PKT);

    return;
}

/*****************************************************************************
 函 数 名  : IPS_MNTN_CCORE_DhcpcSendPktInfoCB
 功能描述  : 捕获TCP/IP协议栈发送的DHCP控制报文回调函数
 输入参数  : pstIpsMntnCapturePara  回调函数参数结构
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月1日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID IPS_MNTN_CCORE_DhcpcSendPktInfoCB
(
    IPS_MNTN_CCORE_CAPTURE_PARA_STRU *pstIpsMntnCapturePara
)
{
    VOS_UINT8                                    *pucNetIfName;
    VOS_UINT8                                    *pucPktData;
    VOS_UINT16                                    usPktLen;

    if ( VOS_NULL_PTR == pstIpsMntnCapturePara )
    {
        TTF_LOG(UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
            "IPS, IPS_MNTN_CCORE_DhcpcSendPktInfoCB, ERROR, pstIpsMntnCapturePara is NULL ");
        return;
    }

    pucNetIfName    = pstIpsMntnCapturePara->paucNetIfName;
    pucPktData      = pstIpsMntnCapturePara->pucData;
    usPktLen        = pstIpsMntnCapturePara->usLen;

    IPS_MNTN_CCORE_CtrlPktInfo(pucNetIfName, pucPktData, usPktLen, ID_IPS_CCORE_TRACE_SEND_DHCPC_PKT);

    return;
}

/*****************************************************************************
 函 数 名  : IPS_MNTN_CCORE_DhcpsRecvktInfoCB
 功能描述  : 捕获TCP/IP协议栈接收的DHCPS控制报文回调函数
 输入参数  : pstIpsMntnCapturePara  回调函数参数结构
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月1日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID IPS_MNTN_CCORE_DhcpsRecvPktInfoCB
(
    IPS_MNTN_CCORE_CAPTURE_PARA_STRU *pstIpsMntnCapturePara
)
{
    VOS_UINT8                                    *pucNetIfName;
    VOS_UINT8                                    *pucPktData;
    VOS_UINT16                                    usPktLen;

    if ( VOS_NULL_PTR == pstIpsMntnCapturePara )
    {
        TTF_LOG(UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
            "IPS, IPS_MNTN_CCORE_DhcpsRecvktInfoCB, ERROR, pstIpsMntnCapturePara is NULL ");
        return;
    }

    pucNetIfName    = pstIpsMntnCapturePara->paucNetIfName;
    pucPktData      = pstIpsMntnCapturePara->pucData;
    usPktLen        = pstIpsMntnCapturePara->usLen;

    IPS_MNTN_CCORE_CtrlPktInfo(pucNetIfName, pucPktData, usPktLen, ID_IPS_CCORE_TRACE_RECV_DHCPS_PKT);

    return;
}

/*****************************************************************************
 函 数 名  : IPS_MNTN_CCORE_DhcpsSendPktInfoCB
 功能描述  : 捕获TCP/IP协议栈发送的DHCPS控制报文回调函数
 输入参数  : pstIpsMntnCapturePara  回调函数参数结构
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月1日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID IPS_MNTN_CCORE_DhcpsSendPktInfoCB
(
    IPS_MNTN_CCORE_CAPTURE_PARA_STRU *pstIpsMntnCapturePara
)
{
    VOS_UINT8                                    *pucNetIfName;
    VOS_UINT8                                    *pucPktData;
    VOS_UINT16                                    usPktLen;

    if ( VOS_NULL_PTR == pstIpsMntnCapturePara )
    {
        TTF_LOG(UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
            "IPS, IPS_MNTN_CCORE_DhcpsSendPktInfoCB, ERROR, pstIpsMntnCapturePara is NULL ");
        return;
    }

    pucNetIfName    = pstIpsMntnCapturePara->paucNetIfName;
    pucPktData      = pstIpsMntnCapturePara->pucData;
    usPktLen        = pstIpsMntnCapturePara->usLen;

    IPS_MNTN_CCORE_CtrlPktInfo(pucNetIfName, pucPktData, usPktLen, ID_IPS_CCORE_TRACE_SEND_DHCPS_PKT);

    return;
}

/*****************************************************************************
 函 数 名  : IPS_MNTN_CCORE_AppCmdInfoCB
 功能描述  : 捕获APP控制命令函数
 输入参数  : aucData        线性数据指针,内容为APP命令
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
VOS_VOID IPS_MNTN_CCORE_AppCmdInfo
(
    VOS_UINT8                                    *pucData,
    VOS_UINT16                                    usCmdLen,
    TTF_MNTN_MSG_TYPE_ENUM_UINT16                 usType
)
{
    VOS_UINT8                                *pucTraceData;
    IPS_MNTN_CCORE_APP_CMD_INFO_STRU         *pstTraceMsg;
    VOS_UINT32                                ulTransDataLen;
    VOS_UINT32                                ulDataLen;

    ulTransDataLen  =   0;
    ulDataLen       =   0;

    if ( VOS_NULL_PTR == pucData )
    {
        TTF_LOG(UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
            "IPS, IPS_MNTN_CCORE_AppCmdInfo, ERROR, pucData is NULL ");
        return;
    }

    ulDataLen           = PS_MIN(IPS_CCORE_APP_CMD_INFO_LEN, usCmdLen);
    ulTransDataLen      = (IPS_CCORE_APP_CMD_INFO_OFFSET_LEN + ulDataLen);

    pucTraceData        = PS_MEM_ALLOC(UEPS_PID_IPS_CCORE, ulTransDataLen + IPS_CCORE_OM_TRANS_DATA_OFFSET_LEN);
    if (VOS_NULL_PTR == pucTraceData)
    {
        /*打印警告信息,申请内存失败*/
        TTF_LOG( UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
                "IPS, IPS_MNTN_CCORE_AppCmdInfo : ERROR : alloc mem failed!" );

        return;
    }

    /*构建透明消息*/
    pstTraceMsg             = (IPS_MNTN_CCORE_APP_CMD_INFO_STRU *)(pucTraceData + IPS_CCORE_OM_TRANS_DATA_OFFSET_LEN);
    pstTraceMsg->usLen      = usCmdLen;
    pstTraceMsg->usPrimId   = usType;
    /*lint -e669 */
    PS_MEM_CPY(pstTraceMsg->aucData, pucData, ulDataLen);
    /*lint +e669 */

    IPS_MNTN_CCORE_TransMsg(pucTraceData, ulTransDataLen, usType);

    PS_MEM_FREE(UEPS_PID_IPS_CCORE, pucTraceData);
}

/*****************************************************************************
 函 数 名  : IPS_MNTN_CCORE_AppCmdInfoCB
 功能描述  : 捕获APP控制命令回调函数
 输入参数  : pstIpsMntnCapturePara  回调函数参数结构
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月1日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID IPS_MNTN_CCORE_AppCmdInfoCB
(
    IPS_MNTN_CCORE_CAPTURE_PARA_STRU *pstIpsMntnCapturePara
)
{
    VOS_UINT8                              *pucData;
    VOS_UINT16                              usCmdLen;

    if ( VOS_NULL_PTR == pstIpsMntnCapturePara )
    {
        TTF_LOG(UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
            "IPS, IPS_MNTN_CCORE_AppCmdInfoCB, ERROR, pstIpsMntnCapturePara is NULL ");
        return;
    }

    pucData         = pstIpsMntnCapturePara->pucData;
    usCmdLen        = pstIpsMntnCapturePara->usLen;

    IPS_MNTN_CCORE_AppCmdInfo(pucData, usCmdLen, ID_IPS_CCORE_TRACE_APP_CMD);

    return;
}


/*****************************************************************************
 函 数 名  : IPS_MNTN_CCORE_PrintInfoCB
 功能描述  : 提供给VISP输出可维可测信息回调接口
 输入参数  : VOS_UINT8                              *pucData;
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月1日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID IPS_MNTN_CCORE_PrintInfoCB
(
    VOS_CHAR                               *pucData
)
{
    VOS_UINT16                              usCmdLen;

    if ( VOS_NULL_PTR == pucData )
    {
        return;
    }

    usCmdLen        = (VOS_UINT16)VOS_StrLen(pucData);

    IPS_MNTN_CCORE_AppCmdInfo((VOS_UINT8 *)pucData, usCmdLen, ID_IPS_CCORE_TRACE_APP_CMD);

    return;
}

/*****************************************************************************
 函 数 名  : IPS_MNTN_CCORE_TCPIP_FixlenLogOutput
 功能描述  : 提供给VISP输出可维可测信息回调接口
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月16日
    作    者   : g00178567
    修改内容   : 新生成函数

*****************************************************************************/
VOID IPS_MNTN_CCORE_TCPIP_FixlenLogOutput(ULONG ulLogCode, ULONG ulLogLevel, ULONG ulLogType, VOID *ucMessage,
                        ULONG ulPara1, ULONG ulPara2, ULONG ulPara3, ULONG ulPara4)
{
    VOS_CHAR                    aucInfoPrint[IPS_CCORE_APP_CMD_INFO_LEN];
    VOS_UINT32                  ulPos;

    if ( VOS_NULL_PTR == ucMessage )
    {
        return;
    }

    /* ucMessage不能过长 */
    if ((IPS_CCORE_APP_CMD_INFO_LEN >> 1) < VOS_StrLen((VOS_CHAR *)ucMessage))
    {
        return;
    }

    memset(aucInfoPrint, 0, IPS_CCORE_APP_CMD_INFO_LEN);

    switch (ulLogType) {
        case LOG_TYPE_CFG:
        case LOG_TYPE_WARNING:
        case LOG_TYPE_RUN:
            VOS_sprintf((char *)aucInfoPrint, "LogCode:%d,type:%d,level:%d | ",
                                    ulLogCode, ulLogType, ulLogLevel);

            ulPos = VOS_StrLen((VOS_CHAR *)aucInfoPrint);
            VOS_sprintf((char *)&aucInfoPrint[ulPos], (VOS_CHAR *)ucMessage,
                                    ulPara1, ulPara2, ulPara3, ulPara4);
            break;

        default:
            return;
    }

    IPS_MNTN_CCORE_PrintInfoCB(aucInfoPrint);

    return;
}

/*****************************************************************************
 函 数 名  : IPS_MNTN_CCORE_TCPIP_VarlenLogOutput
 功能描述  : 提供给VISP输出可维可测信息回调接口
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月16日
    作    者   : g00178567
    修改内容   : 新生成函数

*****************************************************************************/
VOID IPS_MNTN_CCORE_TCPIP_VarlenLogOutput(ULONG ulLogCode, ULONG ulLogLevel,
                        ULONG ulLogType, VOID* pcFormat, VOID* pData)
{
    VOS_CHAR                    aucInfoPrint[IPS_CCORE_APP_CMD_INFO_LEN];
    VOS_UINT32                  ulPos;

    if (( VOS_NULL_PTR == pcFormat ) || ( VOS_NULL_PTR == pData ))
    {
        return;
    }

    /* ucMessage不能过长 */
    if ((IPS_CCORE_APP_CMD_INFO_LEN >> 1) < (VOS_StrLen((VOS_CHAR *)pcFormat) + VOS_StrLen((VOS_CHAR *)pData)))
    {
        return;
    }

    memset(aucInfoPrint, 0, IPS_CCORE_APP_CMD_INFO_LEN);

    switch (ulLogType) {
        case LOG_TYPE_CFG:
        case LOG_TYPE_WARNING:
        case LOG_TYPE_RUN:
            VOS_sprintf((char *)aucInfoPrint, "LogCode:%d,type:%d,level:%d | ",
                                    ulLogCode, ulLogType, ulLogLevel);
            ulPos = VOS_StrLen((VOS_CHAR *)aucInfoPrint);
            VOS_sprintf((char *)&aucInfoPrint[ulPos], (VOS_CHAR *)pcFormat, (VOS_CHAR *)pData);
            break;

        default:
            return;
    }

    IPS_MNTN_CCORE_PrintInfoCB(aucInfoPrint);

    return;
}

/*****************************************************************************
 函 数 名  : IPS_MNTN_CCORE_BridgeTraceCfgChkParam
 功能描述  : 网桥中转钩包配置参数检查
 输入参数  : pRcvMsg
 输出参数  : 无
 返 回 值  : VOS_TRUE/VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年8月3日
    作    者   : f00166181
    修改内容   : 新生成函数
  2.日    期   : 2013年7月30日
    作    者   : caikai
    修改内容   : VoLTE特性需要将其移植至V9

*****************************************************************************/
PS_BOOL_ENUM_UINT8  IPS_MNTN_CCORE_BridgeTraceCfgChkParam(IPS_MNTN_CCORE_TRACE_CONFIG_REQ_STRU *pRcvMsg)
{
    if ( (IPS_MNTN_CCORE_TRACE_NULL_CHOSEN !=pRcvMsg->stBridgeTraceCfg.ulChoice)
        && (IPS_MNTN_CCORE_TRACE_MSG_HEADER_CHOSEN !=pRcvMsg->stBridgeTraceCfg.ulChoice)
        && (IPS_MNTN_CCORE_TRACE_CONFIGURABLE_LEN_CHOSEN !=pRcvMsg->stBridgeTraceCfg.ulChoice)
        && (IPS_MNTN_CCORE_TRACE_WHOLE_DATA_LEN_CHOSEN !=pRcvMsg->stBridgeTraceCfg.ulChoice) )
    {
        return PS_FALSE;
    }

    return PS_TRUE;
}

/*****************************************************************************
 函 数 名  : IPS_MNTN_CCORE_TraceCfgChkParam
 功能描述  : TCP/IP协议栈报文钩包配置参数检查
 输入参数  : pRcvMsg
 输出参数  : 无
 返 回 值  : VOS_TRUE/VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年8月3日
    作    者   : f00166181
    修改内容   : 新生成函数
  2.日    期   : 2013年7月30日
    作    者   : caikai
    修改内容   : VoLTE特性需要将其移植至V9

*****************************************************************************/
PS_BOOL_ENUM_UINT8  IPS_MNTN_CCORE_TraceCfgChkParam(IPS_MNTN_CCORE_TRACE_CONFIG_REQ_STRU *pRcvMsg)
{
    if ( (IPS_MNTN_CCORE_TRACE_NULL_CHOSEN != pRcvMsg->stInputTraceCfg.ulChoice)
        && (IPS_MNTN_CCORE_TRACE_MSG_HEADER_CHOSEN != pRcvMsg->stInputTraceCfg.ulChoice)
        && (IPS_MNTN_CCORE_TRACE_CONFIGURABLE_LEN_CHOSEN != pRcvMsg->stInputTraceCfg.ulChoice)
        && (IPS_MNTN_CCORE_TRACE_WHOLE_DATA_LEN_CHOSEN != pRcvMsg->stInputTraceCfg.ulChoice) )
    {
        return PS_FALSE;
    }

    if ( (IPS_MNTN_CCORE_TRACE_NULL_CHOSEN != pRcvMsg->stOutputTraceCfg.ulChoice)
        && (IPS_MNTN_CCORE_TRACE_MSG_HEADER_CHOSEN != pRcvMsg->stOutputTraceCfg.ulChoice)
        && (IPS_MNTN_CCORE_TRACE_CONFIGURABLE_LEN_CHOSEN != pRcvMsg->stOutputTraceCfg.ulChoice)
        && (IPS_MNTN_CCORE_TRACE_WHOLE_DATA_LEN_CHOSEN != pRcvMsg->stOutputTraceCfg.ulChoice) )
    {
        return PS_FALSE;
    }

    return PS_TRUE;
}

/*****************************************************************************
 函 数 名  : IPS_MNTN_CCORE_TraceAdvancedCfgChkParam
 功能描述  : 钩包配置参数检查
 输入参数  : pRcvMsg
 输出参数  : 无
 返 回 值  : VOS_TRUE/VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年8月3日
    作    者   : f00166181
    修改内容   : 新生成函数
  2.日    期   : 2013年7月30日
    作    者   : caikai
    修改内容   : VoLTE特性需要将其移植至V9

*****************************************************************************/
PS_BOOL_ENUM_UINT8  IPS_MNTN_CCORE_TraceAdvancedCfgChkParam(IPS_MNTN_CCORE_TRACE_CONFIG_REQ_STRU *pRcvMsg)
{
    /*TCP/IP协议栈报文钩包配置参数检查*/
    if(PS_FALSE == IPS_MNTN_CCORE_TraceCfgChkParam(pRcvMsg))
    {
        return PS_FALSE;
    }

    /*网桥中转报文钩包配置参数检查*/
    if(PS_FALSE == IPS_MNTN_CCORE_BridgeTraceCfgChkParam(pRcvMsg))
    {
        return  PS_FALSE;
    }

    return PS_TRUE;

}

/*****************************************************************************
 函 数 名  : IPS_MNTN_CCORE_OutputRouteIpv4Info
 功能描述  : 输出IPV4路由信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月26日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID IPS_MNTN_CCORE_OutputRouteIpv4Info(VOS_UINT8 *pucData, VOS_UINT16 usType)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulWaitList;
    VOS_UINT32                          ulRtNumReturn;
    VOS_UINT32                          ulLen;
    VOS_UINT8                          *pucTransMsg;
    VOS_UINT16                          usPrimId = ID_IPS_CCORE_TRACE_MNTN_INFO;

    /* 打开获取路由表项的waitlist句柄 */
    ulRet = TCPIP_OpenFibTable((UINTPTR *)&ulWaitList);
    if ( FIB4_OK != ulRet )
    {
        TTF_LOG1(UEPS_PID_IPS_CCORE, 0, PS_PRINT_ERROR,
                "VISP, OpenFibTable Failed!!!", (VOS_INT32)ulRet);
        return;
    }

    ulRtNumReturn   =   0;
    pucTransMsg     =   pucData + IPS_CCORE_OM_TRANS_DATA_OFFSET_LEN;

    ulRet = TCPIP_GetFibEntry(ulWaitList,
        IPS_MNTN_CCORE_MAX_IPV4_ROUTE_ITEM,
        (TCPIP_RT4_ENTRY_S *)(pucTransMsg + IPS_MNTN_CCORE_BASE_INFO_OFFSET_LEN),
        (ULONG *)&ulRtNumReturn);
    if ( FIB4_OK != ulRet )
    {
        TTF_LOG1(UEPS_PID_IPS_CCORE, 0, PS_PRINT_ERROR,
                "VISP, GetFibEntry Failed!!!", (VOS_INT32)ulWaitList);

        TCPIP_CloseFibTable(ulWaitList);

        return;
    }

    if ( ulRtNumReturn > IPS_MNTN_CCORE_MAX_IPV4_ROUTE_ITEM )
    {
        TTF_LOG1(UEPS_PID_IPS_CCORE, 0, PS_PRINT_ERROR,
                "VISP, Get Route Item Too Large!!!", (VOS_INT32)ulRtNumReturn);
        ulRtNumReturn = IPS_MNTN_CCORE_MAX_IPV4_ROUTE_ITEM;
    }

    TCPIP_CloseFibTable(ulWaitList);

    /* 填入类型 */
    PS_MEM_CPY(pucTransMsg, &usPrimId, sizeof(usPrimId));

    /* SDT工具解析时类型采用4字节 */
    pucTransMsg += sizeof(VOS_UINT32);

    /* 填入类型 */
    PS_MEM_CPY(pucTransMsg, &usType, sizeof(usType));

    /* SDT工具解析时类型采用4字节 */
    pucTransMsg += sizeof(VOS_UINT32);

    /* 填入长度 */
    ulLen = sizeof(TCPIP_RT4_ENTRY_S) * ulRtNumReturn;
    PS_MEM_CPY(pucTransMsg, &ulLen, sizeof(ulLen));

    IPS_MNTN_CCORE_TransMsg(pucData,
        ulLen + IPS_MNTN_CCORE_BASE_INFO_OFFSET_LEN, ID_IPS_CCORE_TRACE_MNTN_INFO);

    return;
}

/*****************************************************************************
 函 数 名  : IPS_MNTN_CCORE_OutputUdpInfo
 功能描述  : 输出UDP网络状态信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月26日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID IPS_MNTN_CCORE_OutputUdpInfo(VOS_UINT8 *pucData, VOS_UINT16 usType)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulWaitList;
    VOS_UINT32                          ulLen;
    VOS_UINT8                          *pucTransMsg;
    VOS_UINT16                          usPrimId = ID_IPS_CCORE_TRACE_MNTN_INFO;

    ulRet = TCPIP_OpenUdpNetInfo((UINTPTR *)&ulWaitList);
    if ( VOS_OK != ulRet )
    {
        TTF_LOG1(UEPS_PID_IPS_CCORE, 0, PS_PRINT_ERROR,
                "VISP, OpenUdpNetInfo Failed!!!", (VOS_INT32)ulRet);
        return;
    }

    pucTransMsg     =   pucData + IPS_CCORE_OM_TRANS_DATA_OFFSET_LEN;

    /* 填入类型 */
    PS_MEM_CPY(pucTransMsg, &usPrimId, sizeof(usPrimId));

    /* SDT工具解析时类型采用4字节 */
    pucTransMsg += sizeof(VOS_UINT32);

    /* 填入类型 */
    PS_MEM_CPY(pucTransMsg, &usType, sizeof(usType));

    /* SDT工具解析时类型采用4字节 */
    pucTransMsg += sizeof(VOS_UINT32);

    /* 填入长度 */
    ulLen = sizeof(TCPIP_UDPNETINFO_S);
    PS_MEM_CPY(pucTransMsg, &ulLen, sizeof(ulLen));
    pucTransMsg += sizeof(VOS_UINT32);

    ulRet = TCPIP_GetUdpNetInfo(ulWaitList, (TCPIP_UDPNETINFO_S *)pucTransMsg);
    if ( VOS_OK != ulRet )
    {
        TTF_LOG1(UEPS_PID_IPS_CCORE, 0, PS_PRINT_ERROR,
                "VISP, GetUdpNetInfo Failed!!!", (VOS_INT32)ulRet);

        (VOS_VOID)TCPIP_CloseUdpNetInfo(ulWaitList);
        return;
    }

    (VOS_VOID)TCPIP_CloseUdpNetInfo(ulWaitList);

    IPS_MNTN_CCORE_TransMsg(pucData,
        ulLen + IPS_MNTN_CCORE_BASE_INFO_OFFSET_LEN, ID_IPS_CCORE_TRACE_MNTN_INFO);

    return;
}

/*****************************************************************************
 函 数 名  : IPS_MNTN_CCORE_OutputTcpInfo
 功能描述  : 输出TCP网络状态信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月26日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID IPS_MNTN_CCORE_OutputTcpInfo(VOS_UINT8 *pucData, VOS_UINT16 usType)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulWaitList;
    VOS_UINT32                          ulLen;
    VOS_UINT8                          *pucTransMsg;
    VOS_UINT16                          usPrimId = ID_IPS_CCORE_TRACE_MNTN_INFO;

    ulRet = TCPIP_OpenTcpNetInfo((UINTPTR *)&ulWaitList);
    if ( VOS_OK != ulRet )
    {
        TTF_LOG1(UEPS_PID_IPS_CCORE, 0, PS_PRINT_ERROR,
                "VISP, OpenTcpNetInfo Failed!!!", (VOS_INT32)ulRet);
        return;
    }

    pucTransMsg     =   pucData + IPS_CCORE_OM_TRANS_DATA_OFFSET_LEN;

    /* 填入类型 */
    PS_MEM_CPY(pucTransMsg, &usPrimId, sizeof(usPrimId));

    /* SDT工具解析时类型采用4字节 */
    pucTransMsg += sizeof(VOS_UINT32);

    /* 填入类型 */
    PS_MEM_CPY(pucTransMsg, &usType, sizeof(usType));

    /* SDT工具解析时类型采用4字节 */
    pucTransMsg += sizeof(VOS_UINT32);

    /* 填入长度 */
    ulLen = sizeof(TCPIP_TCPNETINFO_S);
    PS_MEM_CPY(pucTransMsg, &ulLen, sizeof(ulLen));
    pucTransMsg += sizeof(ulLen);

    ulRet = TCPIP_GetTcpNetInfo(ulWaitList, (TCPIP_TCPNETINFO_S *)pucTransMsg);
    if ( TCP_FILTOK != ulRet )
    {
        TTF_LOG1(UEPS_PID_IPS_CCORE, 0, PS_PRINT_ERROR,
                "VISP, GetTcpNetInfo Failed!!!", (VOS_INT32)ulRet);

        TCPIP_CloseTcpNetInfo(ulWaitList);
        return;
    }

    TCPIP_CloseTcpNetInfo(ulWaitList);

    IPS_MNTN_CCORE_TransMsg(pucData,
        ulLen + IPS_MNTN_CCORE_BASE_INFO_OFFSET_LEN, ID_IPS_CCORE_TRACE_MNTN_INFO);

    return;
}

/*****************************************************************************
 函 数 名  : IPS_MNTN_CCORE_OutputNetIfInfo
 功能描述  : 输出接口信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月26日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID IPS_MNTN_CCORE_OutputNetIfInfo(VOS_UINT8 *pucData, VOS_UINT16 usType)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulWaitList;
    VOS_UINT32                          ulLen;
    VOS_UINT8                          *pucTransMsg;
    VOS_UINT16                          usPrimId = ID_IPS_CCORE_TRACE_MNTN_INFO;

    ulRet = TCPIP_OpenIfConfigEntry((UINTPTR *)&ulWaitList);
    if ( VRP_IFNET_NOERR != ulRet )
    {
        TTF_LOG1(UEPS_PID_IPS_CCORE, 0, PS_PRINT_ERROR,
                "VISP, OpenIfConfigEntry Failed!!!", (VOS_INT32)ulRet);
        return;
    }

    pucTransMsg     =   pucData + IPS_CCORE_OM_TRANS_DATA_OFFSET_LEN;

    /* 填入类型 */
    PS_MEM_CPY(pucTransMsg, &usPrimId, sizeof(usPrimId));

    /* SDT工具解析时类型采用4字节 */
    pucTransMsg += sizeof(VOS_UINT32);

    /* 填入类型 */
    PS_MEM_CPY(pucTransMsg, &usPrimId, sizeof(usPrimId));

    /* SDT工具解析时类型采用4字节 */
    pucTransMsg += sizeof(VOS_UINT32);

    /* 填入类型 */
    PS_MEM_CPY(pucTransMsg, &usType, sizeof(usType));

    /* SDT工具解析时类型采用4字节 */
    pucTransMsg += sizeof(VOS_UINT32);

    /* 填入长度 */
    ulLen = sizeof(TCPIP_IFNET_S);
    PS_MEM_CPY(pucTransMsg, &ulLen, sizeof(ulLen));
    pucTransMsg += sizeof(ulLen);

    ulRet = TCPIP_GetIfConfigEntry(ulWaitList, (TCPIP_IFNET_S *)pucTransMsg);
    if ( VRP_IFNET_NOERR != ulRet )
    {
        TTF_LOG1(UEPS_PID_IPS_CCORE, 0, PS_PRINT_ERROR,
                "VISP, GetIfConfigEntry Failed!!!", (VOS_INT32)ulRet);

        TCPIP_CloseIfConfigEntry(ulWaitList);
        return;
    }

    TCPIP_CloseIfConfigEntry(ulWaitList);

    IPS_MNTN_CCORE_TransMsg(pucData,
        ulLen + IPS_MNTN_CCORE_BASE_INFO_OFFSET_LEN, ID_IPS_CCORE_TRACE_MNTN_INFO);

    return;
}

/*****************************************************************************
 函 数 名  : IPS_MNTN_CCORE_OutputIpv4AddrInfo
 功能描述  : 输出IPV4地址信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月26日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID IPS_MNTN_CCORE_OutputIpv4AddrInfo(VOS_UINT8 *pucData, VOS_UINT16 usType)
{
    VOS_UINT32                          ulWaitlist;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulIfIndex;
    VOS_UINT32                          ulLen;
    VOS_UINT32                          ulIndex;
    TCPIP_IPIFADDR_S                    stAddrInfo;
    VOS_UINT8                          *pucTransMsg;
    VOS_UINT8                          *pucDataHead;
    IMS_NIC_ENTITY_STRU                *pstImsNicEntity;
    VOS_UINT16                          usPrimId = ID_IPS_CCORE_TRACE_MNTN_INFO;

    pstImsNicEntity = IMS_NIC_GET_ENTITY_STRU(IMS_NIC_MODEM_ID_0);

    ulIfIndex       = pstImsNicEntity->ulIfIndex;
    PS_MEM_SET(&stAddrInfo, 0, sizeof(stAddrInfo));

    ulRet = TCPIP_OpenAddrTable((UINTPTR *)&ulWaitlist, ulIfIndex);
    if ( ERR_AM4_OK != ulRet )
    {
        TTF_LOG1(UEPS_PID_IPS_CCORE, 0, PS_PRINT_ERROR,
                "VISP, OpenAddrTable Failed!!!", (VOS_INT32)ulRet);
        return;
    }

    pucTransMsg     =   pucData + IPS_CCORE_OM_TRANS_DATA_OFFSET_LEN + IPS_MNTN_CCORE_BASE_INFO_OFFSET_LEN;
    pucDataHead     =   pucData + IPS_CCORE_OM_TRANS_DATA_OFFSET_LEN;

    ulRet = TCPIP_GetAddrTable(ulWaitlist, &stAddrInfo, ulIfIndex);
    if ( ERR_AM4_OK != ulRet )
    {
        TTF_LOG(UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
                "VISP, GetAddrTable Failed!!!");

        TCPIP_CloseAddrTable(ulWaitlist);
        return;
    }

    ulIndex = 0;
    while ( (ERR_AM4_END != ulRet) && (ulIndex < IPS_MNTN_CCORE_MAX_IPV4_ADDR_NUM) )
    {
        PS_MEM_CPY(pucTransMsg, &stAddrInfo, sizeof(stAddrInfo));
        ulRet = TCPIP_GetAddrTable(ulWaitlist, &stAddrInfo, ulIfIndex);
        ulIndex++;
    }

    TCPIP_CloseAddrTable(ulWaitlist);

    /* 填入类型 */
    PS_MEM_CPY(pucDataHead, &usPrimId, sizeof(usPrimId));

    /* SDT工具解析时类型采用4字节 */
    pucDataHead += sizeof(VOS_UINT32);

    /* 填入类型 */
    PS_MEM_CPY(pucDataHead, &usType, sizeof(usType));

    /* SDT工具解析时类型采用4字节 */
    pucDataHead += sizeof(VOS_UINT32);

    /* 填入长度 */
    ulLen = ulIndex * sizeof(stAddrInfo);
    PS_MEM_CPY(pucDataHead, &ulLen, sizeof(ulLen));

    IPS_MNTN_CCORE_TransMsg(pucData,
        ulLen + IPS_MNTN_CCORE_BASE_INFO_OFFSET_LEN, ID_IPS_CCORE_TRACE_MNTN_INFO);

    return;
}

/*****************************************************************************
 函 数 名  : IPS_MNTN_CCORE_IpsMntnInfoTimeoutProc
 功能描述  : 捕获TCP/IP协议栈基本信息定时器超时处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月20日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID IPS_MNTN_CCORE_IpsMntnInfoTimeoutProc(VOS_VOID)
{
    VOS_UINT8                          *pucTraceData;

    g_stIpsCcoreMntnInfoEntity.enIpsMntnFlag = IPS_MNTN_CCORE_INFO_REPORT_STOP;

    /* 为模块实体指定内存 */
    pucTraceData    = g_aucIpsCCoreInfo;

    /* 输出虚拟网卡信息 */
    IPS_MNTN_CCORE_OutputNetIfInfo(pucTraceData, ID_IPS_MNTN_CCORE_NETIF_INFO);

    /* 输出TCP连接状态信息 */
    IPS_MNTN_CCORE_OutputTcpInfo(pucTraceData, ID_IPS_MNTN_CCORE_TCP_INFO);

    /* 输出UDP连接状态信息 */
    IPS_MNTN_CCORE_OutputUdpInfo(pucTraceData, ID_IPS_MNTN_CCORE_UDP_INFO);

    /* 输出IPV4路由表信息 */
    IPS_MNTN_CCORE_OutputRouteIpv4Info(pucTraceData, ID_IPS_MNTN_CCORE_IPV4_ROUTE_INFO);

    /* 输出IPV4地址表信息 */
    IPS_MNTN_CCORE_OutputIpv4AddrInfo(pucTraceData, ID_IPS_MNTN_CCORE_IPV4_ADDR_INFO);

    /* 输出IMS虚拟网卡统计信息 */
    IPS_MNTN_CCORE_OutputImsNicStatsInfo(pucTraceData, ID_IPS_MNTN_CCORE_IMS_NIC_INFO);

    /*重启可维可测定时器*/
    if (PS_SUCC != IPS_MNTN_CCORE_StartRelTimer(&(g_stIpsCcoreMntnInfoEntity.hIpsMntnTimer), UEPS_PID_IPS_CCORE,
                    g_stIpsCcoreMntnInfoEntity.ulIpsMntnTimerLen, IPS_MNTN_CCORE_INFO_TIMER, 0,
                    VOS_RELTIMER_NOLOOP, VOS_TIMER_NO_PRECISION))
    {
        /*启动定时器失败，则停止定时器并注销该模块*/
        IPS_MNTN_CCORE_StopMntnInfoTimer();
        g_stIpsCcoreMntnInfoEntity.enIpsMntnFlag = IPS_MNTN_CCORE_INFO_REPORT_STOP;
    }
    else
    {
        g_stIpsCcoreMntnInfoEntity.enIpsMntnFlag = IPS_MNTN_CCORE_INFO_REPORT_START;
    }

    return;
}

/*****************************************************************************
 函 数 名  : IPS_MNTN_PktInfo
 功能描述  : 捕获TCP/IP协议栈接收和发送报文函数
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
  2.日    期   : 2013年7月30日
    作    者   : caikai
    修改内容   : VoLTE特性需要将其移植至V9
  3.日    期   : 2014年3月20日
    作    者   : c00184031
    修改内容   : 适配IP栈移植到RTOSck

*****************************************************************************/
VOS_VOID IPS_MNTN_CCORE_PktInfo
(
    VOS_UINT8                                    *pucPktData,
    VOS_UINT16                                    usPktLen,
    TTF_MNTN_MSG_TYPE_ENUM_UINT16                 usType
)
{
    VOS_UINT8                          *pucTraceData;
    IPS_MNTN_CCORE_TRACE_CONFIG_STRU   *pstTraceCfg;
    IPS_MNTN_CCORE_PKT_INFO_STRU       *pstTraceMsg;
    VOS_UINT32                          ulTransDataLen;
    VOS_UINT32                          ulDataLen;
    VOS_UINT32                          ulRst;


    /* 空指针在外部已经判断过 */
    ulTransDataLen  =   0;
    ulDataLen       =   0;

    /*根据消息类型选择对应配置信息*/
    if(ID_IPS_CCORE_TRACE_INPUT_DATA_INFO == usType)
    {
        pstTraceCfg = &(g_stIpsCcoreTraceMsgCfg.stInputTraceCfg);
    }
    else if(ID_IPS_CCORE_TRACE_OUTPUT_DATA_INFO == usType)
    {
        pstTraceCfg = &(g_stIpsCcoreTraceMsgCfg.stOutputTraceCfg);
    }
    else
    {
        /*打印警告信息,消息类型不匹配*/
        TTF_LOG( UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
                "IPS, IPS_MNTN_CCORE_PktInfo : ERROR : usType is not Expectes!" );
        return;
    }

    /*根据消息配置信息，获取输出报文长度*/
    ulRst = IPS_MNTN_CCORE_GetPktLenByTraceCfg(pstTraceCfg, usPktLen, &ulDataLen);
    if(PS_FALSE == ulRst)
    {
        /*不捕获该报文*/
        return;
    }

    ulDataLen           = PS_MIN(IPS_MNTN_CCORE_TRACE_MAX_BYTE_LEN, ulDataLen);
    ulTransDataLen      = IPS_CCORE_PKT_INFO_OFFSET_LEN + IMS_NIC_ETH_HDR_SIZE + ulDataLen;

    pucTraceData        = PS_MEM_ALLOC(UEPS_PID_IPS_CCORE, ulTransDataLen + IPS_CCORE_OM_TRANS_DATA_OFFSET_LEN);
    if (VOS_NULL_PTR == pucTraceData)
    {
        /*打印警告信息,申请内存失败*/
        TTF_LOG( UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
                "IPS, IPS_MNTN_CCORE_PktInfo : ERROR : alloc mem failed!" );

        return;
    }

    /*构建透明消息*/
    pstTraceMsg             = (IPS_MNTN_CCORE_PKT_INFO_STRU *)(pucTraceData + IPS_CCORE_OM_TRANS_DATA_OFFSET_LEN);
    pstTraceMsg->usLen      = usPktLen + IMS_NIC_ETH_HDR_SIZE;
    pstTraceMsg->usPrimId   = usType;
    PS_MEM_CPY(pstTraceMsg->aucNetIfName, IMS_NIC_GET_NIC_NAME, IPS_CCORE_IFNAMSIZ);

    /*lint -e416 */
    ulRst = MBUF_CopyDataFromMBufToBuffer((MBUF_S *)pucPktData, 0, ulDataLen,
        (pstTraceMsg->aucData + IMS_NIC_ETH_HDR_SIZE));
    /*lint +e416 */

    if ( VOS_OK != ulRst )
    {
        /*打印警告信息,从MBUF拷贝数据失败*/
        TTF_LOG1(UEPS_PID_IPS_CCORE, 0, PS_PRINT_ERROR,
                "IPS, CopyDataFromMBufToBuffer failed!", (VOS_INT32)ulRst);

        PS_MEM_FREE(UEPS_PID_IPS_CCORE, pucTraceData);

        return;
    }

    IPS_MNTN_CCORE_TransMsg(pucTraceData, ulTransDataLen, usType);

    PS_MEM_FREE(UEPS_PID_IPS_CCORE, pucTraceData);

    return;
}

/*****************************************************************************
 函 数 名  : IPS_MNTN_CCORE_IpLayerUpCapCB
 功能描述  : RTOSck平台IP层上行抓包回调函数
 输入参数  : pMBuf   报文数据
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月29日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 IPS_MNTN_CCORE_IpLayerUpCapCB(MBUF_S *pMBuf)
{
    VOS_UINT16                          usPktLen;

    if ( VOS_NULL_PTR == pMBuf )
    {
        TTF_LOG(UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
            "Link layer capture input data is NULL!!!");
        return PS_FAIL;
    }

    usPktLen        = (VOS_UINT16)pMBuf->ulTotalDataLength;

    IPS_MNTN_CCORE_PktInfo((VOS_UINT8 *)pMBuf, usPktLen, ID_IPS_CCORE_TRACE_INPUT_DATA_INFO);

    return PS_SUCC;
}

/*****************************************************************************
 函 数 名  : IPS_MNTN_CCORE_IpLayerDownCapCB
 功能描述  : RTOSck平台IP层下行抓包回调函数
 输入参数  : pMBuf   报文数据
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月29日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 IPS_MNTN_CCORE_IpLayerDownCapCB(MBUF_S *pMBuf)
{
    VOS_UINT16                          usPktLen;


    if ( VOS_NULL_PTR == pMBuf )
    {
        TTF_LOG(UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
            "Link layer capture output data is NULL!!!");
        return PS_FAIL;
    }

    usPktLen        = (VOS_UINT16)pMBuf->ulTotalDataLength;

    IPS_MNTN_CCORE_PktInfo((VOS_UINT8 *)pMBuf, usPktLen, ID_IPS_CCORE_TRACE_OUTPUT_DATA_INFO);

    return PS_SUCC;
}

/*****************************************************************************
 函 数 名  : IPS_MNTN_CCORE_UnregHooks
 功能描述  : RTOSck平台去注册钩子函数
 输入参数  : ulMask
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月20日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID IPS_MNTN_CCORE_UnregHooks(VOS_UINT32 ulMask)
{
    VOS_UINT32                          ulIndex;


    for ( ulIndex = 0; ulIndex < IPS_ARRAY_SIZE(g_stIpsCcoreHookMaskOpt); ulIndex++ )
    {
        if ( (g_stIpsCcoreHookMaskOpt[ulIndex].ulMask
            == (ulMask & g_stIpsCcoreHookMaskOpt[ulIndex].ulMask))
            && (VOS_NULL_PTR != g_stIpsCcoreHookMaskOpt[ulIndex].pfUnRegHookFunc) )
        {
            /*卸载钩子函数*/
            (VOS_VOID)g_stIpsCcoreHookMaskOpt[ulIndex].pfUnRegHookFunc(g_stIpsCcoreHookMaskOpt[ulIndex].ulType,
                g_stIpsCcoreHookMaskOpt[ulIndex].pfHookCbFunc);

            /* 重置相应的掩码位 */
            g_ulCurrMask &= ~g_stIpsCcoreHookMaskOpt[ulIndex].ulMask;
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : IPS_MNTN_CCORE_RegHooks
 功能描述  : RTOSck平台注册钩子函数
 输入参数  : ulMask
 输出参数  : 无
 返 回 值  : VOS_INT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月20日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 IPS_MNTN_CCORE_RegHooks(VOS_UINT32 ulMask)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulIndex;


    for ( ulIndex = 0; ulIndex < IPS_ARRAY_SIZE(g_stIpsCcoreHookMaskOpt); ulIndex++ )
    {
        if ( (g_stIpsCcoreHookMaskOpt[ulIndex].ulMask
            != (ulMask & g_stIpsCcoreHookMaskOpt[ulIndex].ulMask))
            || (VOS_NULL_PTR == g_stIpsCcoreHookMaskOpt[ulIndex].pfRegHookFunc) )
        {
            continue;
        }

        /* 已经注册过的不再重复注册 */
        if ( 0 == (g_stIpsCcoreHookMaskOpt[ulIndex].ulMask & g_ulCurrMask) )
        {
            /*注册相应的钩子函数*/
            ulRet = g_stIpsCcoreHookMaskOpt[ulIndex].pfRegHookFunc(g_stIpsCcoreHookMaskOpt[ulIndex].ulType,
                g_stIpsCcoreHookMaskOpt[ulIndex].ulPriority, g_stIpsCcoreHookMaskOpt[ulIndex].pfHookCbFunc);
            if ( PS_SUCC != ulRet )
            {
                TTF_LOG1(UEPS_PID_IPS_CCORE, PS_SUBMOD_NULL, PS_PRINT_ERROR,
                    "Reg Fail!!!ulErrCode:<1>", (VOS_INT32)ulRet);

                /*若有一个注册失败则卸载当前所有已经注册上的钩子函数*/
                IPS_MNTN_CCORE_UnregHooks(g_ulCurrMask);
                return ulRet;
            }

            g_ulCurrMask |= g_stIpsCcoreHookMaskOpt[ulIndex].ulMask;
        }
    }

    return PS_SUCC;
}

/*****************************************************************************
 函 数 名  : IPS_MNTN_CCORE_ReRegHooks
 功能描述  : RTOSck平台重新注册钩子函数
 输入参数  : ulMask
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月20日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 IPS_MNTN_CCORE_ReRegHooks(VOS_UINT32 ulMask)
{
    VOS_UINT32                          ulRet;


    /*重新注册前先卸载当前所有的钩子函数*/
    if ( 0 != g_ulCurrMask )
    {
        IPS_MNTN_CCORE_UnregHooks(g_ulCurrMask);
    }

    ulRet = IPS_MNTN_CCORE_RegHooks(ulMask);

    return ulRet;
}


/*****************************************************************************
 函 数 名  : IPS_MNTN_CCORE_SetCallbackFunc
 功能描述  : RTOSck平台注册回调函数
 输入参数  : pRcvMsg
 输出参数  : 无
 返 回 值  : VOS_TRUE/VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月20日
    作    者   : c00184031
    修改内容   : 新生成函数


*****************************************************************************/
PS_BOOL_ENUM_UINT8 IPS_MNTN_CCORE_SetCallbackFunc(IPS_MNTN_CCORE_TRACE_CONFIG_REQ_STRU *pstTraceCfgReq)
{
    VOS_UINT32                          ulMask = 0;
    VOS_UINT32                          ulRet;


    if ( (pstTraceCfgReq->stBridgeTraceCfg.ulChoice > IPS_MNTN_CCORE_TRACE_NULL_CHOSEN)
        && (pstTraceCfgReq->stBridgeTraceCfg.ulChoice <= IPS_MNTN_CCORE_TRACE_WHOLE_DATA_LEN_CHOSEN) )
    {
        ulMask |= IPS_MNTN_CCORE_IPV4_CAPTRURE_UP_MASK;
        ulMask |= IPS_MNTN_CCORE_IPV4_CAPTRURE_DOWN_MASK;
        ulMask |= IPS_MNTN_CCORE_IPV6_CAPTRURE_UP_MASK;
        ulMask |= IPS_MNTN_CCORE_IPV6_CAPTRURE_DOWN_MASK;
    }
    else
    {
        if ( (pstTraceCfgReq->stInputTraceCfg.ulChoice > IPS_MNTN_CCORE_TRACE_NULL_CHOSEN)
            && (pstTraceCfgReq->stInputTraceCfg.ulChoice <= IPS_MNTN_CCORE_TRACE_WHOLE_DATA_LEN_CHOSEN) )
        {
            ulMask |= IPS_MNTN_CCORE_IPV4_CAPTRURE_UP_MASK;
            ulMask |= IPS_MNTN_CCORE_IPV6_CAPTRURE_UP_MASK;
        }

        if ( (pstTraceCfgReq->stOutputTraceCfg.ulChoice > IPS_MNTN_CCORE_TRACE_NULL_CHOSEN)
            && (pstTraceCfgReq->stOutputTraceCfg.ulChoice <= IPS_MNTN_CCORE_TRACE_WHOLE_DATA_LEN_CHOSEN) )
        {
            ulMask |= IPS_MNTN_CCORE_IPV4_CAPTRURE_DOWN_MASK;
            ulMask |= IPS_MNTN_CCORE_IPV6_CAPTRURE_DOWN_MASK;
        }
    }

    ulRet = IPS_MNTN_CCORE_ReRegHooks(ulMask);
    if ( PS_SUCC != ulRet )
    {
        TTF_LOG1(UEPS_PID_IPS_CCORE, PS_SUBMOD_NULL, PS_PRINT_ERROR,
            "RegHooks Fail!!!ulErrCode:<1>", (VOS_INT32)ulRet);
        return PS_FALSE;
    }

    return PS_TRUE;
}


/*****************************************************************************
 函 数 名  : IPS_MNTN_CCORE_TraceAdvancedCfgReq
 功能描述  : 保存钩包配置
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年8月3日
    作    者   : f00166181
    修改内容   : 新生成函数
  2.日    期   : 2013年7月30日
    作    者   : caikai
    修改内容   : VoLTE特性需要将其移植至V9

*****************************************************************************/
VOS_VOID IPS_MNTN_CCORE_TraceAdvancedCfgReq(VOS_VOID *pMsg)
{
    PS_BOOL_ENUM_UINT8                            enResult;

    OM_IPS_CCORE_ADVANCED_TRACE_CONFIG_REQ_STRU   *pRcvMsg;
    IPS_CCORE_OM_ADVANCED_TRACE_CONFIG_CNF_STRU   stIpsCcoreTraceCfgCnf;

    pRcvMsg = (OM_IPS_CCORE_ADVANCED_TRACE_CONFIG_REQ_STRU *)pMsg;

    /* Fill DIAG trans msg header */
    stIpsCcoreTraceCfgCnf.stDiagHdr.ulSenderCpuId   = VOS_LOCAL_CPUID;
    stIpsCcoreTraceCfgCnf.stDiagHdr.ulSenderPid     = UEPS_PID_IPS_CCORE;
    stIpsCcoreTraceCfgCnf.stDiagHdr.ulReceiverCpuId = VOS_LOCAL_CPUID;
    stIpsCcoreTraceCfgCnf.stDiagHdr.ulReceiverPid   = MSP_PID_DIAG_APP_AGENT ;   /* 把应答消息发送给DIAG，由DIAG把透传命令的处理结果发送给HIDS工具*/
    stIpsCcoreTraceCfgCnf.stDiagHdr.ulLength = sizeof(IPS_CCORE_OM_ADVANCED_TRACE_CONFIG_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    stIpsCcoreTraceCfgCnf.stDiagHdr.ulMsgId = ID_IPS_CCORE_OM_ADVANCED_TRACE_CONFIG_CNF;

    /* DIAG透传命令中的特定信息*/
    stIpsCcoreTraceCfgCnf.stDiagHdr.usOriginalId  = pRcvMsg->stDiagHdr.usOriginalId;
    stIpsCcoreTraceCfgCnf.stDiagHdr.usTerminalId  = pRcvMsg->stDiagHdr.usTerminalId;
    stIpsCcoreTraceCfgCnf.stDiagHdr.ulTimeStamp   = pRcvMsg->stDiagHdr.ulTimeStamp;
    stIpsCcoreTraceCfgCnf.stDiagHdr.ulSN          = pRcvMsg->stDiagHdr.ulSN;

    /*检测配置参数是否合法*/
    enResult = IPS_MNTN_CCORE_TraceAdvancedCfgChkParam(&(pRcvMsg->stIpsCcoreCfgReq));

    if ( PS_FALSE == enResult )
    {
        /*如果参数检测不合法，向OM回复配置失败*/
        stIpsCcoreTraceCfgCnf.stIpsCcoreCfgCnf.enRslt = PS_FAIL;

        IPS_MNTN_CCORE_SndCfgCnf2Om(ID_IPS_CCORE_OM_ADVANCED_TRACE_CONFIG_CNF,
            sizeof(stIpsCcoreTraceCfgCnf),&stIpsCcoreTraceCfgCnf);

        TTF_LOG(UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
            "Warning: IPS_MNTN_CCORE_TraceAdvancedCfgReq check fail");

        return;
    }

    enResult = IPS_MNTN_CCORE_SetCallbackFunc(&(pRcvMsg->stIpsCcoreCfgReq));
    if( PS_FALSE == enResult )
    {
        /*如果参数检测不合法，向OM回复配置失败*/
        stIpsCcoreTraceCfgCnf.stIpsCcoreCfgCnf.enRslt = PS_FAIL;

        IPS_MNTN_CCORE_SndCfgCnf2Om(ID_IPS_CCORE_OM_ADVANCED_TRACE_CONFIG_CNF,
            sizeof(stIpsCcoreTraceCfgCnf),&stIpsCcoreTraceCfgCnf);

        TTF_LOG(UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
            "Warning: IPS_MNTN_CCORE_SetCallbackFunc fail");

        return;
    }

    /*保存配置参数*/
    mdrv_memcpy(&g_stIpsCcoreTraceMsgCfg, &(pRcvMsg->stIpsCcoreCfgReq), sizeof(IPS_MNTN_CCORE_TRACE_CONFIG_REQ_STRU));

    if (WTTF_TRACE_MSG_YES == g_stIpsCcoreTraceMsgCfg.stVispLogConfig.enVISPLogOutConfig)
    {
        (VOS_VOID)TCPIP_SetLogType(1,1,1);

        (VOS_VOID)TCPIP_SetLogLevel(g_stIpsCcoreTraceMsgCfg.stVispLogConfig.enVISPRunLogLevelConfig);

        /* SOCKET */
        (VOS_VOID)TCPIP_DebugSockAll();

        /* TCP */
        (VOS_VOID)TCPIP_DebugTCPAll();

        /* UDP */
        (VOS_VOID)TCPIP_DebugUDPAll();

        /* ICMP */
        (VOS_VOID)TCPIP_SetIcmpDebugFlag(1);

        /* PP4 */
        (VOS_VOID)TCPIP_SetPP4DebugFlag(1,0,0,0,1,1);

        /* TCP6 */
        (VOS_VOID)TCP6_DebugSwitch(1);

        /* UDP6 */
        (VOS_VOID)UDP6_DebugSwitch(1);

        /* ICMP6 */
        (VOS_VOID)ICMP6_DebugSwitch(1);

        /* PP6 */
        (VOS_VOID)TCPIP_SetPP6DebugFlag(1,1);

        /* IPSEC */
        (VOS_VOID)TCPIP_IPSEC_SetDebug(1,2);
    }
    else
    {
        /* SOCKET */
        (VOS_VOID)TCPIP_NoDebugSockAll();

        /* TCP */
        (VOS_VOID)TCPIP_NoDebugTCPAll();

        /* UDP */
        (VOS_VOID)TCPIP_NoDebugUDPAll();

        /* ICMP */
        (VOS_VOID)TCPIP_SetIcmpDebugFlag(0);

        /* PP4 */
        (VOS_VOID)TCPIP_SetPP4DebugFlag(0,0,0,0,0,0);

        /* TCP6 */
        (VOS_VOID)TCP6_DebugSwitch(0);

        /* UDP6 */
        (VOS_VOID)UDP6_DebugSwitch(0);

        /* ICMP6 */
        (VOS_VOID)ICMP6_DebugSwitch(0);

        /* PP6 */
        (VOS_VOID)TCPIP_SetPP6DebugFlag(0,0);

        /* IPSEC */
        (VOS_VOID)TCPIP_IPSEC_SetDebug(0,0);

        (VOS_VOID)TCPIP_SetLogType(0,0,0);
    }

    /*向OM回复配置成功*/
    stIpsCcoreTraceCfgCnf.stIpsCcoreCfgCnf.enRslt = PS_SUCC;

    IPS_MNTN_CCORE_SndCfgCnf2Om(ID_IPS_CCORE_OM_ADVANCED_TRACE_CONFIG_CNF,
            sizeof(stIpsCcoreTraceCfgCnf),&stIpsCcoreTraceCfgCnf);

    return;
}

/*****************************************************************************
 函 数 名  : IPS_MNTN_CCORE_RcvIpsMntnInfoCfgReq
 功能描述  : 接收到OM配置的Ips可维可测信息捕获配置请求
 输入参数  : MsgBlock *pMsg,
             VOS_VOID *pPara
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年8月3日
    作    者   : f00166181
    修改内容   : 新生成函数
  2.日    期   : 2013年7月30日
    作    者   : caikai
    修改内容   : VoLTE特性需要将其移植至V9

*****************************************************************************/
VOS_UINT32 IPS_MNTN_CCORE_RcvIpsMntnInfoCfgReq(VOS_VOID *pMsg)
{
    OM_IPS_CCORE_MNTN_INFO_CONFIG_REQ_STRU  *pRcvMsg;
    IPS_CCORE_OM_MNTN_INFO_CONFIG_CNF_STRU  stIpsCcoreMntnCfgCnf;
    IPS_MNTN_CCORE_RESULT_TYPE_ENUM_UINT32  enResult;
    VOS_UINT32                              ulIpsMntnTimerLen;

    pRcvMsg = (OM_IPS_CCORE_MNTN_INFO_CONFIG_REQ_STRU *)pMsg;

    enResult            = IPS_MNTN_CCORE_RESULT_OK;

    /*启动捕获TCP/IP协议栈基础信息*/
    if( IPS_MNTN_CCORE_INFO_REPORT_START == pRcvMsg->stIpsCcoreMntnCfgReq.enCommand )
    {
        /*检测捕获TCP/IP协议栈基础信息功能是否正常启动*/
        if(PS_FALSE == IPS_MNTN_CCORE_ChkMntnInfoIsStart())
        {
            /*设置定时器时长，默认为1000毫秒*/
            ulIpsMntnTimerLen = 1000 * pRcvMsg->stIpsCcoreMntnCfgReq.usTimeLen;

            if (PS_SUCC != IPS_MNTN_CCORE_StartRelTimer(&(g_stIpsCcoreMntnInfoEntity.hIpsMntnTimer), UEPS_PID_IPS_CCORE,
                    ulIpsMntnTimerLen, IPS_MNTN_CCORE_INFO_TIMER, 0,
                    VOS_RELTIMER_NOLOOP, VOS_TIMER_NO_PRECISION))
            {
                /*启动定时器失败，则停止定时器并注销该模块*/
                IPS_MNTN_CCORE_StopMntnInfoTimer();
                enResult = IPS_MNTN_CCORE_RESULT_START_TIMER_FAIL;

                g_stIpsCcoreMntnInfoEntity.enIpsMntnFlag = IPS_MNTN_CCORE_INFO_REPORT_STOP;
            }
            else
            {
                g_stIpsCcoreMntnInfoEntity.ulIpsMntnTimerLen = ulIpsMntnTimerLen;
                g_stIpsCcoreMntnInfoEntity.enIpsMntnFlag     = IPS_MNTN_CCORE_INFO_REPORT_START;
            }
        }
    }
    /*停止捕获TCP/IP协议栈基础信息*/
    else if( IPS_MNTN_CCORE_INFO_REPORT_STOP == pRcvMsg->stIpsCcoreMntnCfgReq.enCommand )
    {
        /*检测捕获TCP/IP协议栈基础信息功能是否正常启动*/
        if(PS_TRUE == IPS_MNTN_CCORE_ChkMntnInfoIsStart())
        {
            /*如果该模块已启动，则停止定时器并注销该模块*/
            IPS_MNTN_CCORE_StopMntnInfoTimer();

            g_stIpsCcoreMntnInfoEntity.enIpsMntnFlag = IPS_MNTN_CCORE_INFO_REPORT_STOP;
        }
    }
    /*================*/    /*OM 请求的参数无效*/
    else
    {
        enResult = IPS_MNTN_CCORE_RESULT_INPUT_PARAM_ERR;
    }

    /* Fill DIAG trans msg header */
    stIpsCcoreMntnCfgCnf.stDiagHdr.ulSenderCpuId    = VOS_LOCAL_CPUID;
    stIpsCcoreMntnCfgCnf.stDiagHdr.ulSenderPid      = UEPS_PID_IPS_CCORE;
    stIpsCcoreMntnCfgCnf.stDiagHdr.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    stIpsCcoreMntnCfgCnf.stDiagHdr.ulReceiverPid    = MSP_PID_DIAG_APP_AGENT ;   /* 把应答消息发送给DIAG，由DIAG把透传命令的处理结果发送给HIDS工具*/
    stIpsCcoreMntnCfgCnf.stDiagHdr.ulLength         = sizeof(IPS_CCORE_OM_MNTN_INFO_CONFIG_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    stIpsCcoreMntnCfgCnf.stDiagHdr.ulMsgId          = ID_IPS_CCORE_OM_MNTN_INFO_CONFIG_CNF;

    /* DIAG透传命令中的特定信息*/
    stIpsCcoreMntnCfgCnf.stDiagHdr.usOriginalId     = pRcvMsg->stDiagHdr.usOriginalId;
    stIpsCcoreMntnCfgCnf.stDiagHdr.usTerminalId     = pRcvMsg->stDiagHdr.usTerminalId;
    stIpsCcoreMntnCfgCnf.stDiagHdr.ulTimeStamp      = pRcvMsg->stDiagHdr.ulTimeStamp;
    stIpsCcoreMntnCfgCnf.stDiagHdr.ulSN             = pRcvMsg->stDiagHdr.ulSN;

    /* 填充确认信息 */
    stIpsCcoreMntnCfgCnf.stIpsCcoreMntnCfgCnf.enCommand = pRcvMsg->stIpsCcoreMntnCfgReq.enCommand;
    stIpsCcoreMntnCfgCnf.stIpsCcoreMntnCfgCnf.enRslt    = enResult;

    /* 发送OM透明消息 */
    IPS_MNTN_CCORE_SndCfgCnf2Om(ID_IPS_CCORE_OM_MNTN_INFO_CONFIG_CNF,
            sizeof(stIpsCcoreMntnCfgCnf),&stIpsCcoreMntnCfgCnf);

    return PS_SUCC;
}

/*****************************************************************************
 函 数 名  : IPS_MNTN_CCORE_OutputImsNicStatsInfo
 功能描述  : 输出虚拟网卡的上下行统计信息
 输入参数  : pucData    -- 数据内存
             usType     -- 可维可测消息类型
 输出参数  : 无
 返 回 值  : 无
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月16日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID IPS_MNTN_CCORE_OutputImsNicStatsInfo
(
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usType
)
{
    VOS_UINT32                          ulDataLen;
    VOS_UINT8                          *pucTransMsg;
    VOS_UINT32                          ulResult;

    ulDataLen       =   0;
    pucTransMsg     =   pucData + sizeof(VOS_UINT32);

    /* 填入类型 */
    PS_MEM_CPY(pucData, &usType, sizeof(usType));

    /* SDT工具解析时类型采用4字节 */
    pucData += sizeof(VOS_UINT32);

    /* 获取IMS虚拟网卡的统计信息 */
    ulResult    = IMS_NIC_GetMntnInfo((pucTransMsg + IPS_CCORE_OM_TRANS_DATA_OFFSET_LEN), &ulDataLen, usType);

    if ((IMS_NIC_SUCC != ulResult) || (0 == ulDataLen) || (ulDataLen > IPS_MNTN_CCORE_INFO_LEN))
    {
        TTF_LOG1(UEPS_PID_IPS_CCORE, 0, PS_PRINT_ERROR,
                "IPS, IPS_MNTN_CCORE_OutputImsNicStatsInfo : ERROR : IMS_NIC_GetMntnInfo  Failed! ulDataLen =%d\n", (long)ulDataLen);
        return;
    }

    IPS_MNTN_CCORE_TransMsg(pucData, ulDataLen + sizeof(VOS_UINT32), usType);

    return;
}

/*****************************************************************************
 函 数 名  : IPS_MNTN_CCORE_RcvOmMsgProc
 功能描述  : IPS MNTN接收到来自OM模块的消息处理
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年8月3日
    作    者   : f00166181
    修改内容   : 新生成函数
  2.日    期   : 2013年7月30日
    作    者   : caikai
    修改内容   : VoLTE特性需要将其移植至V9

*****************************************************************************/
VOS_VOID IPS_MNTN_CCORE_RcvOmMsgProc(VOS_VOID *pMsg)
{
    VOS_UINT32          usMsgId;

    usMsgId = (VOS_UINT16)(*((VOS_UINT32 *)((VOS_UINT8 *)(pMsg) + VOS_MSG_HEAD_LENGTH)));

    switch ( usMsgId )
    {
        case ID_OM_IPS_CCORE_ADVANCED_TRACE_CONFIG_REQ:
            IPS_MNTN_CCORE_TraceAdvancedCfgReq(pMsg);
            break;

        case ID_OM_IPS_CCORE_MNTN_INFO_CONFIG_REQ:
            IPS_MNTN_CCORE_RcvIpsMntnInfoCfgReq(pMsg);
            break;

        default:
            TTF_LOG(UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
                "IPS, IPS_MNTN_CCORE_RcvOmMsgProc : ERROR : Receive Unkown Type Message !" );
            break;
    }
    return;
}

/*****************************************************************************
 函 数 名  : IPS_MNTN_CCORE_RcvTimerExpireMsgProc
 功能描述  : 定时器超时处理
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年8月3日
    作    者   : f00166181
    修改内容   : 新生成函数
  2.日    期   : 2013年7月30日
    作    者   : caikai
    修改内容   : VoLTE特性需要将其移植至V9

*****************************************************************************/
VOS_VOID IPS_MNTN_CCORE_RcvTimerExpireMsgProc(REL_TIMER_MSG *pTimerMsg)
{
    switch ( pTimerMsg->ulName)
    {
        case IPS_MNTN_CCORE_INFO_TIMER:
            IPS_MNTN_CCORE_IpsMntnInfoTimeoutProc();
            break;

        default:
            TTF_LOG(UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
                "IPS, IPS_MNTN_CCORE_RcvTimerExpireMsgProc : ERROR : Receive Unkown Type Message !" );
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : IPS_MNTN_CCORE_MsgProc
 功能描述  : IPS可维可测控制消息处理函数
 输入参数  : pMsg      -- 消息指针
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年8月3日
    作    者   : f00166181
    修改内容   : 新生成函数
  2.日    期   : 2013年7月30日
    作    者   : caikai
    修改内容   : VoLTE特性需要将其移植至V9

*****************************************************************************/
VOS_VOID IPS_MNTN_CCORE_MsgProc( struct MsgCB * pMsg )
{
    if(VOS_NULL_PTR == pMsg)
    {
        TTF_LOG(UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
                "IPS, IPS_MNTN_CCORE_MsgProc : ERROR : Message NULL !" );
        return;
    }

    switch( pMsg->ulSenderPid )
    {
        case MSP_PID_DIAG_APP_AGENT: /* 来自AT的消息处理 */
            IPS_MNTN_CCORE_RcvOmMsgProc( (VOS_VOID *)pMsg );
            break;

        case VOS_PID_TIMER:
            IPS_MNTN_CCORE_RcvTimerExpireMsgProc((REL_TIMER_MSG *)pMsg);
            break;

        default:
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : IPS_MNTN_CCORE_FidInit
 功能描述  : Interpeak可维可测FID任务初始化
 输入参数  : ip   - 初始化阶段
 输出参数  : 无
 返 回 值  : VOS_OK - 成功
             VOS_ERR - 失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年8月1日
    作    者   : f00166181
    修改内容   : 新生成函数
  2.日    期   : 2013年7月30日
    作    者   : caikai
    修改内容   : VoLTE特性需要将其移植至V9

*****************************************************************************/
VOS_UINT32 IPS_MNTN_CCORE_FidInit ( enum VOS_INIT_PHASE_DEFINE ip )
{
    VOS_UINT32  ulReturnCode;


    switch( ip )
    {
    case    VOS_IP_LOAD_CONFIG:
        ulReturnCode = RTOSCK_AdapterInit();
        if ( VOS_OK != ulReturnCode )
        {
            TTF_LOG(UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
                "IPS, IPS_MNTN_CCORE_FidInit RTOSCK_AdapterInit Failed! \n");
            return VOS_ERR;
        }

        ulReturnCode = VISP_InitTCPIPStack();
        if ( VOS_OK != ulReturnCode )
        {
            TTF_LOG(UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
                "IPS, IPS_MNTN_CCORE_FidInit VISP_InitTCPIPStack Failed! \n");
            return VOS_ERR;
        }

        /* 初始化IMS虚拟网卡 */
        ulReturnCode        = IMS_NIC_InitAll();
        if ( IMS_NIC_SUCC != ulReturnCode )
        {
            TTF_LOG(UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
                "IPS, IPS_MNTN_CCORE_FidInit IMS_NIC_Init Failed! \n");
            return VOS_ERR;
        }

        /* PID为WUEPS_PID_IPS_MNTN_CCORE*/
        ulReturnCode = VOS_RegisterPIDInfo(UEPS_PID_IPS_CCORE,
                                    VOS_NULL_PTR,
                                    (Msg_Fun_Type)IPS_MNTN_CCORE_MsgProc);
        if( VOS_OK != ulReturnCode )
        {
            TTF_LOG(UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
                    "IPS, IPS_MNTN_CCORE_FidInit VOS_RegisterPIDInfo Failed" );
            return VOS_ERR;
        }

        /* FID为WUEPS_PID_IPS_MNTN*/
        ulReturnCode = VOS_RegisterMsgTaskPrio(UEPS_FID_IPS_CCORE, VOS_PRIORITY_M4);
        if( VOS_OK != ulReturnCode )
        {
            TTF_LOG(UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
                    "IPS, IPS_MNTN_CCORE_FidInit VOS_RegisterTaskPrio Failed" );
            return VOS_ERR;
        }

        break;

    case   VOS_IP_FARMALLOC:
    case   VOS_IP_INITIAL:
    case   VOS_IP_ENROLLMENT:
    case   VOS_IP_LOAD_DATA:
    case   VOS_IP_FETCH_DATA:
    case   VOS_IP_STARTUP:
    case   VOS_IP_RIVAL:
    case   VOS_IP_KICKOFF:
    case   VOS_IP_STANDBY:
    case   VOS_IP_BROADCAST_STATE:
    case   VOS_IP_RESTART:
        break;

    default:
        break;
    }

    return VOS_OK;
} /* ISP_MNTN_CCORE_FidInit */

#else /*FEATURE_ON == FEATURE_IMS*/
/*****************************************************************************
 函 数 名  : IPS_MNTN_CCORE_FidInit
 功能描述  : FID初始化桩函数
 输入参数  : ip   - 初始化阶段
 输出参数  : 无
 返 回 值  : VOS_OK     - 成功
             VOS_ERR    - 失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年8月1日
    作    者   : f00166181
    修改内容   : 新生成函数
  2.日    期   : 2013年7月30日
    作    者   : caikai
    修改内容   : VoLTE特性需要将其移植至V9

*****************************************************************************/
VOS_UINT32 IPS_MNTN_CCORE_FidInit ( enum VOS_INIT_PHASE_DEFINE ip )
{
    switch( ip )
    {
    case    VOS_IP_LOAD_CONFIG:

        break;

    case   VOS_IP_FARMALLOC:
    case   VOS_IP_INITIAL:
    case   VOS_IP_ENROLLMENT:
    case   VOS_IP_LOAD_DATA:
    case   VOS_IP_FETCH_DATA:
    case   VOS_IP_STARTUP:
    case   VOS_IP_RIVAL:
    case   VOS_IP_KICKOFF:
    case   VOS_IP_STANDBY:
    case   VOS_IP_BROADCAST_STATE:
    case   VOS_IP_RESTART:
        break;

    default:
        break;
    }

    return VOS_OK;
} /* ISP_MNTN_CCORE_FidInit */
/*lint -restore */
/*lint +e534*/

#endif  /*FEATURE_ON == FEATURE_IMS*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif




