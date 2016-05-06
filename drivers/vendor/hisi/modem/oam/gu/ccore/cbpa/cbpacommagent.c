/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : cbpacommagent.c
  版 本 号   : 初稿
  作    者   : L00256032
  生成日期   :
  最近修改   :
  功能描述   : CBPCA模块功能实现
  函数列表   :
  修改历史   :

  1.日    期 : 2013年12月19日
    作    者 : L00256032
    修改内容 : V9R1 L_plus_C项目新增
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "product_config.h"
#include "cbpacommagent.h"
#include "csimagent.h"
#include "mdrv.h"
#include "TafNvInterface.h"
#include "msp_diag_comm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人：h28225；检视人：l46160；原因简述：打点日志文件ID宏定义*/
#define    THIS_FILE_ID        PS_FILE_ID_CBPACOMMAGENT_C
/*lint +e767 修改人：h28225；检视人：l46160；*/

#if (FEATURE_ON == FEATURE_CL_INTERWORK)
/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/* CBPCA 管理上下文 */
CBPCA_CTX_STRU                          g_stCbpcaCtx;

/* CBPCA 可维可测统计 */
CBPCA_STATISTIC_STRU                    g_stCbpcaStatic = {0};

/* CPBCA打印可维可测控制开关 */
VOS_UINT8                               g_ucCbpcaDbgFlag = VOS_FALSE;

/* HDLC帧中的MsgId与CBPCA需要转发到的PID之间的映射关系表 */
CBPCA_PID_MSGID_MAP_TABLE_STRU          g_astCbpcaPidMsgIdMapTbl[] =
{
    /* CBPCA需要转发到的PID */    /* HDLC帧中的MsgId */    /* 保留字节 */    /* CBPCA发送到对应PID所使用的enMsgType */
    { I0_WUEPS_PID_CSIMA,            0x0000,              0x0,               CBPCA_CSIMA_DATA_IND          },/* 这一行的位置不可以变动 */
    { WUEPS_PID_CMMCA,               0x0001,              0x0,               CBPCA_CMMCA_DATA_IND          }

};

VOS_INT  CBPCA_UartRcvCBFunc(UART_CONSUMER_ID uPortNo, VOS_UINT8 *pucData, VOS_UINT32 ulLength);

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
函 数 名  : CBPCA_SetDebugSwitch
功能描述  : CBPCA设置打印上下文开关
输入参数  : ucFlag  --- 打印开关
输出参数  : 无
返 回 值  : VOS_VOID
History     :
1.日    期  : 2013年12月19日
  作    者  : L00256032
  修改内容  : Create
*****************************************************************************/
VOS_VOID CBPCA_SetDebugSwitch(VOS_UINT8 ucFlag)
{
    g_ucCbpcaDbgFlag = ucFlag;

    return;
}

/*****************************************************************************
函 数 名  :CBPCA_ResetStatisticInfo
功能描述  :清除CBPCA可维可测信息
输入参数  :VOS_VOID
输出参数  :无
返 回 值  :VOS_VOID
修订记录  :
1.日    期  : 2013年12月19日
  作    者  : L00256032
  修改内容  : Create
*****************************************************************************/
VOS_VOID CBPCA_ResetStatisticInfo(VOS_VOID)
{
    /*lint -e534*/
    VOS_MemSet(&g_stCbpcaStatic, 0, sizeof(g_stCbpcaStatic));
    /*lint +e534*/
    return;
}

/*****************************************************************************
函 数 名  :CBPCA_ShowCtrlAndStatisticInfo
功能描述  :打印CBPCA控制上下文及可维可测信息
输入参数  :VOS_VOID
输出参数  :无
返 回 值  :VOS_VOID
修订记录  :
1.日    期  : 2013年12月19日
  作    者  : L00256032
  修改内容  : Create
*****************************************************************************/
VOS_VOID CBPCA_ShowCtrlAndStatisticInfo(VOS_VOID)
{
    /*lint -e534*/
    vos_printf("\r\n\r\n********************CBPCA 控制上下文信息************************\r\n");
    vos_printf("g_stCbpcaCtx.usExpectRcvIndex                                  %d\r\n", g_stCbpcaCtx.usExpectRcvIndex);
    vos_printf("g_stCbpcaCtx.usExpectSndIndex                                  %d\r\n", g_stCbpcaCtx.usExpectSndIndex);
    vos_printf("g_stCbpcaCtx.enCBPStatus(0:NOT READY 1:READY)                  %d\r\n", g_stCbpcaCtx.enCBPStatus);
    vos_printf("g_stCbpcaCtx.stDecapCtrlCtx.ulLength(DECAP缓存中的数据长度)    %d\r\n", g_stCbpcaCtx.stDecapCtrlCtx.ulLength);

    vos_printf("\r\n********************CBPCA 可维可测统计信息************************\r\n");
    vos_printf("HDLC解封装:解封装成功次数统计                                 %d\r\n", g_stCbpcaStatic.ulHdlcDecapSucc);
    vos_printf("底软调用回调函数，但uPortNo错误次数统计                       %d\r\n", g_stCbpcaStatic.ulUartCBWrongPortNo);
    vos_printf("底软调用回调函数，但入口指针为空次数统计                      %d\r\n", g_stCbpcaStatic.ulUartCBNullPtr);
    vos_printf("底软调用回调函数，但入口长度为0次数统计                       %d\r\n", g_stCbpcaStatic.ulUartCBLenIsZero);
    vos_printf("底软调用回调函数，但CBP状态为NOT READY次数统计                %d\r\n", g_stCbpcaStatic.ulUartCBCBPNotReady);
    vos_printf("HDLC解封装:FCS错误次数统计                                    %d\r\n", g_stCbpcaStatic.ulHdlcDecapFCSError);
    vos_printf("HDLC解封装:异常帧，丢弃次数统计                               %d\r\n", g_stCbpcaStatic.ulHdlcDecapDiscard);
    vos_printf("HDLC解封装:缓存溢出次数统计                                   %d\r\n", g_stCbpcaStatic.ulHdlcDecapBuffFull);
    vos_printf("HDLC解封装:入参错误次数统计                                   %d\r\n", g_stCbpcaStatic.ulHdlcDecapParaError);
    vos_printf("HDLC解封装:错误的Index次数统计                                %d\r\n", g_stCbpcaStatic.ulHdlcDecapInvalidIndex);
    vos_printf("HDLC解封装:解封装后的数据长度<=6，不存在Data域的异常统计      %d\r\n", g_stCbpcaStatic.ulHdlcDecapNoDataField);
    vos_printf("HDLC解封装:解封装后，LENGTH域<=2的异常统计                    %d\r\n", g_stCbpcaStatic.ulHdlcDecapLengthAbnormal);
    vos_printf("HDLC解封装:Length比实际数据长度要小的异常统计                 %d\r\n", g_stCbpcaStatic.ulHdlcDecapLengthIsLess);
    vos_printf("HDLC解封装:Length比实际数据长度要大的异常统计                 %d\r\n", g_stCbpcaStatic.ulHdlcDecapLengthIsMore);
    vos_printf("HDLC解封装:错误的MsgId次数统计                                %d\r\n", g_stCbpcaStatic.ulHdlcDecapInvalidMsgId);
    vos_printf("HDLC解封装:无效帧次数统计                                     %d\r\n", g_stCbpcaStatic.ulHdlcDecapInvalidFrame);
    vos_printf("调用底软接口mdrv_dualmodem_send发送成功次数统计                     %d\r\n", g_stCbpcaStatic.ulSendToUartSucc);
    vos_printf("CBP未就绪，导致发往CBP的帧被丢弃次数统计                      %d\r\n", g_stCbpcaStatic.ulCBPNotReadyDiscardFrame);
    vos_printf("发往CBP的数据，由于找不到MsgId对应的PID而被丢弃次数统计       %d\r\n", g_stCbpcaStatic.ulHdlcEncapInvalidPID);
    vos_printf("HDLC封装失败次数统计                                          %d\r\n", g_stCbpcaStatic.ulHdlcEncapFail);
    vos_printf("调用底软接口mdrv_dualmodem_send返回失败次数统计                     %d\r\n", g_stCbpcaStatic.ulSendToUartFail);

    vos_printf("\r\n\r\n");
    /*lint +e534*/
    return;

}

/*****************************************************************************
函 数 名  : CBPCA_UartDataHook
功能描述  : CBPCA与UART间数据交互勾包
输入参数  : ulLength  --- 数据长度
            pucData   --- 指针
输出参数  : 无
返 回 值  : 无
调用函数  : 无
被调函数  :
修订记录  :
1.日    期  : 2013年12月19日
  作    者  : L00256032
  修改内容  : Create
*****************************************************************************/
VOS_VOID CBPCA_UartDataHook(VOS_UINT32 ulLength, VOS_UINT8 *pucData)
{
    MsgBlock                           *pstMsg;

    pstMsg = (MsgBlock*)VOS_AllocMsg(WUEPS_PID_CBPCA, ulLength);

    if (VOS_NULL_PTR == pstMsg)
    {
        CBPA_ERROR_LOG("CBPCA_UartDataHook:WARNING:alloc msg failed\n");

        return;
    }

    pstMsg->ulReceiverPid   = WUEPS_PID_CBPCA;

    pstMsg->ulLength        = ulLength;

    /*lint -e534*/
    VOS_MemCpy(pstMsg->aucValue, pucData, ulLength);
    /*lint +e534*/

    DIAG_TraceReport((VOS_VOID *)(pstMsg));

    /*lint -e534*/
    VOS_FreeMsg(WUEPS_PID_CBPCA, pstMsg);
    /*lint +e534*/

    return;
}

/*****************************************************************************
函 数 名  : CBPCA_GetCtxAddr
功能描述  : CBPCA管理上下文的指针获取
输入参数  : 无
输出参数  : 无
返 回 值  : CBPCA_CTX_STRU *
History     :
1.日    期  : 2013年12月19日
  作    者  : L00256032
  修改内容  : Create
*****************************************************************************/
CBPCA_CTX_STRU* CBPCA_GetCtxAddr(VOS_VOID)
{
    return &(g_stCbpcaCtx);
}

/*****************************************************************************
函 数 名  : CBPCA_RestoreIndex
功能描述  : 接收、发送Index的清零操作
输入参数  : pusIndex -- 收发递加操作数
输出参数  : VOS_VOID
返 回 值  : VOS_VOID
History     :
1.日    期  : 2013年12月19日
  作    者  : L00256032
  修改内容  : Create
*****************************************************************************/
VOS_VOID CBPCA_RestoreIndex(VOS_VOID)
{
    CBPCA_CTX_STRU                     *pstCbpcaCtx;
    VOS_INT32                           lLockKey;

    /* 获取CBPCA CTX的指针 */
    pstCbpcaCtx = CBPCA_GetCtxAddr();

    /* 关中断 */
    lLockKey = VOS_SplIMP();

    /* Index清零 */
    pstCbpcaCtx->usExpectRcvIndex = 0;
    pstCbpcaCtx->usExpectSndIndex = 0;

    /* 开中断 */
    VOS_Splx(lLockKey);

    return;
}

/*****************************************************************************
函 数 名  : CBPCA_IncreaseIndex
功能描述  : 接收、发送Index的递加操作
            注: HDLC中Index的值有效范围为:0~0x7fff(0xFFFF固定为错误信息帧的索引),
            累计到0x7fff后从0开始重新计数
输入参数  : pusIndex -- 收发递加操作数
输出参数  : VOS_VOID
返 回 值  : VOS_VOID
History     :
1.日    期  : 2013年12月19日
  作    者  : L00256032
  修改内容  : Create
*****************************************************************************/
VOS_VOID CBPCA_IncreaseIndex(VOS_UINT16 *pusIndex)
{
    VOS_INT32                           lLockKey;

    /* 关中断 */
    lLockKey = VOS_SplIMP();

    /* Index累加 */
    if (*pusIndex < CBPCA_MAX_INDEX)
    {
        (*pusIndex)++;
    }
    else
    {
        *pusIndex = 0;
    }

    /* 开中断 */
    VOS_Splx(lLockKey);

    return;
}

/*****************************************************************************
函 数 名  : CBPCA_FindMatchPidByMsgId
功能描述  : CBPCA 接收到CBP的帧后，需要根据MsgID找到对应的PID，以及与对应PID间的MsgType
输入参数  : usMsgId        -- 消息ID
输出参数  : pulPid         -- 对应PID
            penMsgType     -- 与对应PID间的MsgType
返 回 值  : VOS_OK         -- 找到匹配PID
            VOS_ERR        -- 未找到匹配PID
History     :
1.日    期  : 2013年12月20日
  作    者  : L00256032
  修改内容  : Create
*****************************************************************************/
VOS_UINT32 CBPCA_FindMatchPidByMsgId(
    VOS_UINT16                          usMsgId,
    VOS_UINT32                         *pulPid,
    CBPCA_MSG_TYPE_ENUM_UINT32         *penMsgType)
{
    VOS_UINT8       ucLoop;
    VOS_UINT8       ucTblElementCnt;

    ucTblElementCnt = (VOS_UINT8)(sizeof(g_astCbpcaPidMsgIdMapTbl) / sizeof(CBPCA_PID_MSGID_MAP_TABLE_STRU));

    for (ucLoop = 0; ucLoop < ucTblElementCnt; ucLoop++)
    {
        if (usMsgId == g_astCbpcaPidMsgIdMapTbl[ucLoop].usMsgId)
        {
            *pulPid     = g_astCbpcaPidMsgIdMapTbl[ucLoop].ulPid;
            *penMsgType = g_astCbpcaPidMsgIdMapTbl[ucLoop].enMsgType;
            return VOS_OK;
        }
    }

    return VOS_ERR;
}

/*****************************************************************************
函 数 名  : CBPCA_FindMatchMsgIdByPid
功能描述  : CBPCA 接收到上层应用发送的数据后，需要根据PID找到对应的MsgID
输入参数  : ulPid          -- PID
输出参数  : pusMsgId       -- 对应MsgId
返 回 值  : VOS_OK         -- 找到匹配MsgId
            VOS_ERR        -- 未找到匹配MsgId
History     :
1.日    期  : 2013年12月20日
  作    者  : L00256032
  修改内容  : Create
*****************************************************************************/
VOS_UINT32 CBPCA_FindMatchMsgIdByPid(VOS_UINT32 ulPid, VOS_UINT16 *pusMsgId)
{
    VOS_UINT8       ucLoop;
    VOS_UINT8       ucTblElementCnt;

    ucTblElementCnt = (VOS_UINT8)(sizeof(g_astCbpcaPidMsgIdMapTbl) / sizeof(CBPCA_PID_MSGID_MAP_TABLE_STRU));

    for (ucLoop = 0; ucLoop < ucTblElementCnt; ucLoop++)
    {
        if (ulPid == g_astCbpcaPidMsgIdMapTbl[ucLoop].ulPid)
        {
            *pusMsgId = g_astCbpcaPidMsgIdMapTbl[ucLoop].usMsgId;
            return VOS_OK;
        }
    }

    return VOS_ERR;
}

/*****************************************************************************
函 数 名  : CBPCA_SndDataToCbpca
功能描述  : CBPCA 提供给上层应用的API接口，用于上层应用发送数据至CBPCA
输入参数  : ulSndPid       -- 发送PID
            enMsgType      -- 消息ID
            pucData        -- 数据指针
            ulLength       -- 数据长度
输出参数  : 无
返 回 值  : VOS_OK         -- 发送成功
            VOS_ERR        -- 发送失败
History     :
1.日    期  : 2013年12月20日
  作    者  : L00256032
  修改内容  : Create
*****************************************************************************/
VOS_UINT32 CBPCA_SndDataToCbpca(
    VOS_UINT32                          ulSndPid,
    CBPCA_MSG_TYPE_ENUM_UINT32          enMsgType,
    VOS_UINT8                          *pucData,
    VOS_UINT32                          ulLength)
{
    CBPCA_DATA_REQ_MSG_STRU            *pstMsg;
    VOS_UINT32                          ulMsgLen;
    VOS_UINT8                          *pucTmpptr;

    if ((VOS_NULL == ulLength) || (VOS_NULL_PTR == pucData))
    {
        CBPA_ERROR_LOG("CBPCA_SndDataToCbpca: para error!");
        return VOS_ERR;
    }

    /* 申请消息长度，不包括消息头，并且要预留出前6个字节，用于填写HDLC帧中断Index、Length、MsgId，
        这样可以减少一次内存拷贝，提高数据发送效率 */
    ulMsgLen = ((sizeof(CBPCA_DATA_REQ_MSG_STRU) - CBPCA_MSG_DATA_RSV_LEN)
                + CBPCA_RCV_UPPER_DATA_RSV_LEN + ulLength) - VOS_MSG_HEAD_LENGTH;

    pstMsg = (CBPCA_DATA_REQ_MSG_STRU *)VOS_AllocMsg(ulSndPid, ulMsgLen);
    if (VOS_NULL_PTR == pstMsg)
    {
        CBPA_ERROR1_LOG("CBPCA_SndDataToCbpca: Alloc msg fail!", (VOS_INT32)enMsgType);
        return VOS_ERR;
    }

    /* 填充消息内容 */
    pstMsg->ulReceiverPid      = WUEPS_PID_CBPCA;
    pstMsg->enMsgType          = enMsgType;
    pstMsg->ulDataLen          = ulLength;

    /* 拷贝数据内容，如下pucTmpptr指针转换是为了规避PCLINT检查会有指针溢出告警 */
    pucTmpptr = (VOS_UINT8 *)(((VOS_UINT32)pstMsg->aucData) + CBPCA_RCV_UPPER_DATA_RSV_LEN);
    /*lint -e534*/
    VOS_MemCpy(pucTmpptr, pucData, ulLength);
    /*lint +e534*/

    if (VOS_OK != VOS_SendMsg(ulSndPid, pstMsg))
    {
        CBPA_ERROR1_LOG("CBPCA_SndDataToCbpca: Send msg fail!", (VOS_INT32)enMsgType);
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : CBPCA_DataReqProc
功能描述  : CBPCA 处理CBPCA_DATA_REQ_MSG_STRU消息
输入参数  : pMsg CSIMA或CMMCA等上层适配模块发过来的消息内容

输出参数  : 无
返 回 值  : VOS_VOID
History     :
1.日    期  : 2013年12月19日
  作    者  : L00256032
  修改内容  : Create
*****************************************************************************/
VOS_VOID CBPCA_DataReqProc(CBPCA_DATA_REQ_MSG_STRU *pMsg)
{
    CBPCA_CTX_STRU                     *pCbpcaCtx;
    VOS_UINT8                          *pucData;
    VOS_UINT8                          *pucTmpPtr;
    VOS_UINT16                          usHdlcLength;      /* HDLC帧中Length域的值 */
    VOS_UINT16                          usMsgId;
    VOS_UINT16                          usEncapLen;

    /* HDLC帧的格式如下:
    | 0x7E || Index(Low byte) | Index(High byte) | Length(Low byte) | Length(High byte) | MsgId(Low byte) | MsgId(High byte) |
    |           ... Data(Low byte) | Data(High byte) ...            |   FCS(High byte)  |  FCS(Low byte)  | 0x7E |
    */

    pCbpcaCtx = CBPCA_GetCtxAddr();

    /* 先判断CBP Modem状态是否ready */
    if (CBP_MODEM_STATUS_READY != pCbpcaCtx->enCBPStatus)
    {
        /* 当前CBP未ready，由于VIA驱动限制，当前不能数据发送，数据直接丢弃，记录可维可测 */
        CBPCA_STATISTIC_INC(CBPCA_STATISTIC_CBP_NOT_READY_DISCARD_FRAME);

        return;
    }

    /* pMsg->aucData已经预留了前6个字节，用于填充HDLC帧的Index、Length、MsgId，减少一次内测拷贝，提高传输效率 */
    pucData = pMsg->aucData;

    /* 填充Index */
    *pucData       = (VOS_UINT8)(pCbpcaCtx->usExpectSndIndex & 0xFF);
    *(pucData + 1) = (VOS_UINT8)((pCbpcaCtx->usExpectSndIndex >> 8) & 0xFF);

    /* 填充Length(Length为MsgId和Data域的长度和) */
    pucData += sizeof(VOS_UINT16);
    usHdlcLength = (VOS_UINT16)(pMsg->ulDataLen + sizeof(usMsgId));
    *pucData       = (VOS_UINT8)(usHdlcLength & 0xFF);
    *(pucData + 1) = (VOS_UINT8)((usHdlcLength >> 8) & 0xFF);

    /* 根据ulSenderPid获取对应的MsgId */
    if (VOS_OK != CBPCA_FindMatchMsgIdByPid(pMsg->ulSenderPid, &usMsgId))
    {
        /* 记录可维可测，该数据直接丢弃 */
        CBPCA_STATISTIC_INC(CBPCA_STATISTIC_CANNOT_FIND_MATCH_MSGID);

        CBPA_ERROR_LOG("CBPCA_DataReqProc: Abnormal Msg ID.");

        return;
    }

    /* 填充MsgId，如下pTmpPtr的指针转换，是为了规避PCLINT检查会有指针溢出告警 */
    pucData += sizeof(VOS_UINT16);
    pucTmpPtr        = (VOS_UINT8 *)((VOS_UINT32)pucData);
    *pucTmpPtr       = (VOS_UINT8)(usMsgId & 0xFF);         /* [false alarm]:消息构造，按照实际长度申请空间，此处没有溢出风险 */
    *(pucTmpPtr + 1) = (VOS_UINT8)((usMsgId >> 8) & 0xFF);  /* [false alarm]:消息构造，按照实际长度申请空间，此处没有溢出风险 */

    /* 执行HDLC封装 */
    if (VOS_OK != Om_HdlcEncap(pMsg->aucData,
                               (VOS_UINT16)(CBPCA_RCV_UPPER_DATA_RSV_LEN + pMsg->ulDataLen),
                               pCbpcaCtx->stEncapCtrlCtx.pucEncapBuff,
                               (VOS_UINT16)(pCbpcaCtx->stEncapCtrlCtx.ulEncapBuffSize),
                               &usEncapLen))
    {
        /* HDLC封装失败，记录可维可测 */
        CBPCA_STATISTIC_INC(CBPCA_STATISTIC_HDLC_ENCAP_FAIL);

        CBPA_ERROR_LOG("CBPCA_DataReqProc: Om_HdlcEncap Fail!");

        return;
    }

    /* 调用底软UART发送接口发送数据 */
    if (VOS_OK != mdrv_dualmodem_send(CBP_UART_PORT_ID, pCbpcaCtx->stEncapCtrlCtx.pucEncapBuff, (VOS_UINT32)usEncapLen))
    {
        /* 底软接口发送失败，记录可维可测 */
        CBPCA_STATISTIC_INC(CBPCA_STATISTIC_HDLC_ENCAP_SEND_FAIL);

        CBPA_ERROR_LOG("CBPCA_DataReqProc: mdrv_dualmodem_send Fail!");

        return;
    }

    /* 可维可测打印 */
    /*lint -e40*/
    CBPA_DEBUG_TRACE(pCbpcaCtx->stEncapCtrlCtx.pucEncapBuff, usEncapLen);
    /*lint +e40*/

    /* 记录可维可测 */
    CBPCA_STATISTIC_INC(CBPCA_STATISTIC_HDLC_ENCAP_SEND_SUCC);

    /* 累加发送Index */
    CBPCA_IncreaseIndex(&(pCbpcaCtx->usExpectSndIndex));

    /* 执行勾包操作 */
    CBPCA_UartDataHook((VOS_UINT32)usEncapLen, pCbpcaCtx->stEncapCtrlCtx.pucEncapBuff);

    return;
}

/*****************************************************************************
函 数 名  : CBPCA_CSIMAModemResetIndProc
功能描述  : CBPCA 处理CSIMA_CBPCA_MODEM_RESET_IND_MSG_STRU消息
输入参数  : pMsg CSIMA向CBPCA发送的Modem复位状态指示

输出参数  : 无
返 回 值  : VOS_VOID
History     :
1.日    期  : 2013年12月20日
  作    者  : L00256032
  修改内容  : Create
*****************************************************************************/
VOS_VOID CBPCA_CSIMAModemResetIndProc(CSIMA_CBPCA_MODEM_RESET_IND_MSG_STRU *pMsg)
{
    CBPCA_CTX_STRU                     *pCbpcaCtx;
    VOS_INT32                           iResult;

    pCbpcaCtx = CBPCA_GetCtxAddr();

    if (CSIMA_CBPCA_MODEM_RESET_START == pMsg->enModemReset)
    {
        /* 将CBP Ready标志置为"NOT READY" */
        pCbpcaCtx->enCBPStatus = CBP_MODEM_STATUS_NOT_READY;

    }
    else if (CSIMA_CBPCA_MODEM_RESET_SUCC == pMsg->enModemReset)
    {
        /*通过AT命令判断当前的拼片处理的PID，AP保证只在正确的Modem上面下发该命令*/
        if (g_astCbpcaPidMsgIdMapTbl[0].ulPid != pMsg->ulSenderPid)
        {
            g_astCbpcaPidMsgIdMapTbl[0].ulPid = pMsg->ulSenderPid;
        }

        if (0 != mdrv_dual_modem_init())
        {
            CBPA_WARNING_LOG("CBPCA_CSIMAModemResetIndProc: uart_test_bsp_dual_modem_init fail!");
        }

        CBPA_ERROR_LOG("CBPCA_CSIMAModemResetIndProc after uart_test_bsp_dual_modem_init");

        iResult = mdrv_dualmodem_register_rcvhook(CBP_UART_PORT_ID, (pUARTRecv)CBPCA_UartRcvCBFunc);

        if (VOS_OK != iResult)
        {
            CBPA_ERROR1_LOG("CBPCA_Init: Reg callback function fail!", iResult);
            return;
        }

        CBPA_ERROR_LOG("CBPCA_CSIMAModemResetIndProc after register CBPCA_UartRcvCBFunc");

        /* 清除HDLC封装的缓存数据 */
        /*lint -e534*/
        VOS_MemSet(pCbpcaCtx->stEncapCtrlCtx.pucEncapBuff, 0, pCbpcaCtx->stEncapCtrlCtx.ulEncapBuffSize);

        /* 清除HDLC解封装的缓存数据 */
        VOS_MemSet(pCbpcaCtx->stDecapCtrlCtx.pucDecapBuff, 0, pCbpcaCtx->stDecapCtrlCtx.ulDecapBuffSize);
        /*lint +e534*/
        Om_HdlcInit(&pCbpcaCtx->stDecapCtrlCtx);

        /* 清理HDLC接收、发送Index索引号 */
        CBPCA_RestoreIndex();

        /* 将CBP Ready标志置为"READY" */
        pCbpcaCtx->enCBPStatus = CBP_MODEM_STATUS_READY;

        CBPA_ERROR_LOG("CBPCA_CSIMAModemResetIndProc after enCBPStatus = CBP_MODEM_STATUS_READY");
    }
    else if (CSIMA_CBPCA_MODEM_RESET_FAIL == pMsg->enModemReset)
    {
        /* VIA Modem复位失败，当前不做任何处理 */
        CBPA_WARNING_LOG("CBPCA_CSIMAModemResetIndProc: VIA Reset fail!");
    }
    else
    {
        CBPA_WARNING_LOG("CBPCA_CSIMAModemResetIndProc: Abnormal enModemReset!");
    }

    return;
}

/*****************************************************************************
函 数 名  : CBPCA_CSIMAMsgProc
功能描述  : CBPCA 处理CSIMA消息处理函数
输入参数  : pMsg -- CSIMA 发来消息内容

输出参数  : 无
返 回 值  : VOS_VOID
History     :
1.日    期  : 2013年12月19日
  作    者  : L00256032
  修改内容  : Create
*****************************************************************************/
VOS_VOID CBPCA_CSIMAMsgProc(MsgBlock *pMsg)
{
    CBPCA_MSG_HDR_STRU                 *pstDataReq;

    pstDataReq = (CBPCA_MSG_HDR_STRU *)pMsg;

    switch (pstDataReq->enMsgType)
    {
         case CSIMA_CBPCA_DATA_REQ:
            CBPCA_DataReqProc((CBPCA_DATA_REQ_MSG_STRU *)pMsg);
            break;

         case CSIMA_CBPCA_MODEM_RESET_IND:
            CBPCA_CSIMAModemResetIndProc((CSIMA_CBPCA_MODEM_RESET_IND_MSG_STRU *)pMsg);
            break;

         default:
            CBPA_WARNING_LOG("CBPCA_CSIMAMsgProc: Abnormal Msg ID.");
            break;
    }

    return;
}

/*****************************************************************************
函 数 名  : CBPCA_CMMCAMsgProc
功能描述  : CBPCA 处理CMMCA消息处理函数
输入参数  : pMsg -- CMMCA 发来消息内容

输出参数  : 无
返 回 值  : VOS_VOID
History     :
1.日    期  : 2014年2月18日
  作    者  : L00256032
  修改内容  : Create
*****************************************************************************/
VOS_VOID CBPCA_CMMCAMsgProc(MsgBlock *pMsg)
{
    CBPCA_MSG_HDR_STRU                 *pstDataReq;

    pstDataReq = (CBPCA_MSG_HDR_STRU *)pMsg;

    switch (pstDataReq->enMsgType)
    {
         case CMMCA_CBPCA_DATA_REQ:
            CBPCA_DataReqProc((CBPCA_DATA_REQ_MSG_STRU *)pMsg);
            break;

         default:
            CBPA_WARNING_LOG("CBPCA_CMMCAMsgProc: Abnormal Msg ID.");
            break;
    }

    return;
}


/*****************************************************************************
函 数 名  : CBPCA_PidMsgProc
功能描述  : CBPCA PID消息处理入口
输入参数  : pMsg -- 消息内容

输出参数  : 无
返 回 值  : VOS_VOID
History     :
1.日    期  : 2013年12月19日
  作    者  : L00256032
  修改内容  : Create
*****************************************************************************/
VOS_VOID CBPCA_PidMsgProc(MsgBlock *pMsg)
{
    switch (pMsg->ulSenderPid)
    {
        case I0_WUEPS_PID_CSIMA:
        case I1_WUEPS_PID_CSIMA:
            CBPCA_CSIMAMsgProc(pMsg);
            break;

        case WUEPS_PID_CMMCA:
            CBPCA_CMMCAMsgProc(pMsg);
            break;

        default:
            CBPA_WARNING_LOG("CBPCA_PidMsgProc: Abnormal PID.");
            break;
    }

    return;
}

/*****************************************************************************
函 数 名  : CBPCA_TransferDataToUpperLayer
功能描述  : CBPCA 将HDLC中的源数据转发给上层应用模块
输入参数  : ulRcvPid       -- 对应的接收PID
            enMsgType      -- 消息ID
            pucData        -- 数据指针
            ulLength       -- 数据长度

输出参数  : 无
返 回 值  : VOS_VOID
History     :
1.日    期  : 2013年12月20日
  作    者  : L00256032
  修改内容  : Create
*****************************************************************************/
VOS_VOID CBPCA_TransferDataToUpperLayer(
    VOS_UINT32                          ulRcvPid,
    CBPCA_MSG_TYPE_ENUM_UINT32          enMsgType,
    VOS_UINT8                          *pucData,
    VOS_UINT32                          ulLength)
{
    CBPCA_DATA_IND_MSG_STRU            *pstMsg;
    VOS_UINT32                          ulMsgLen;
    VOS_UINT8                          *pucTmpPtr;

    /* 申请消息长度，不包括消息头 */
    if (ulLength > CBPCA_MSG_DATA_RSV_LEN)
    {
        ulMsgLen = ((sizeof(CBPCA_DATA_IND_MSG_STRU) - CBPCA_MSG_DATA_RSV_LEN) + ulLength) - VOS_MSG_HEAD_LENGTH;
    }
    else
    {
        ulMsgLen = sizeof(CBPCA_DATA_IND_MSG_STRU) - VOS_MSG_HEAD_LENGTH;
    }

    pstMsg = (CBPCA_DATA_IND_MSG_STRU *)VOS_AllocMsg(WUEPS_PID_CBPCA, ulMsgLen);
    if (VOS_NULL_PTR == pstMsg)
    {
        CBPA_ERROR1_LOG("CBPCA_TransferDataToUpperLayer: Alloc msg fail!", (VOS_INT32)enMsgType);
        return;
    }

    /* 填充消息内容 */
    pstMsg->ulReceiverPid      = ulRcvPid;
    pstMsg->enMsgType          = enMsgType;
    pstMsg->ulDataLen          = ulLength;

    if (0 != ulLength)
    {
        /* 拷贝数据内容 */
        pucTmpPtr = (VOS_UINT8 *)((VOS_UINT32)(pstMsg->aucData));
        /*lint -e534*/
        VOS_MemCpy(pucTmpPtr, pucData, ulLength);
        /*lint +e534*/
    }
    if (VOS_OK != VOS_SendMsg(WUEPS_PID_CBPCA, pstMsg))
    {
        CBPA_ERROR1_LOG("CBPCA_TransferDataToUpperLayer: Send msg fail!", (VOS_INT32)enMsgType);
    }

    return;
}

/*****************************************************************************
函 数 名  : CBPCA_DecreaseIndex
功能描述  : CBPCA受到VIA的querymsg时，index为防止加1，先做减1
输入参数  : pusIndex        -- index
输出参数  : 无
返 回 值  : VOS_VOID
History     :
1.日    期  : 2013年12月20日
  作    者  : L00256032
  修改内容  : Create

*****************************************************************************/
VOS_VOID CBPCA_DecreaseIndex(VOS_UINT16 *pusIndex)
{
    VOS_INT32                           lLockKey;

    /* 关中断 */
    lLockKey = VOS_SplIMP();

    /* Index减一 */
    if (*pusIndex > 0)
    {
        (*pusIndex)--;
    }
    else
    {
        *pusIndex = CBPCA_MAX_INDEX;
    }

    /* 开中断 */
    VOS_Splx(lLockKey);

    return;
}

/*****************************************************************************
函 数 名  : CBPCA_DispatchReceivedData
功能描述  : CBPCA 从HDLC中正常解析出DATA并执行转发
输入参数  : pucData        -- 数据指针
            ulInfoLength   -- 数据长度

输出参数  : 无
返 回 值  : VOS_VOID
History     :
1.日    期  : 2013年12月20日
  作    者  : L00256032
  修改内容  : Create
*****************************************************************************/
VOS_VOID CBPCA_DispatchReceivedData(VOS_UINT8 *pucData, VOS_UINT32 ulInfoLength)
{
    VOS_UINT16                          usIndex  = 0;
    VOS_UINT16                          usLength = 0;          /* 记录HDLC帧中length字段的值 */
    VOS_UINT16                          usRawDataLength = 0;   /* 记录HDLC帧中Data域的长度 */
    VOS_UINT16                          usMsgId  = 0;
    VOS_UINT32                          ulRcvPid;
    CBPCA_MSG_TYPE_ENUM_UINT32          enMsgType;
    CBPCA_CTX_STRU                     *pCbpcaCtx;
    VOS_UINT32                          i = 0;

    /* 接收到的数据码流格式如下
    | Index(Low byte) | Index(High byte) | Length(Low byte) | Length(High byte) | MsgId(Low byte) | MsgId(High byte) |
    |           ... Data ...             |
    */

    /* 判断ulLength合法性 */
    if (VOS_NULL == ulInfoLength)
    {
        CBPA_ERROR_LOG("CBPCA_DispatchReceivedData: ulInfoLength is 0!");
        return;
    }

    if (ulInfoLength <= CBPCA_RCV_UPPER_DATA_RSV_LEN)
    {
        /* 记录可维可测信息 */
        CBPCA_STATISTIC_INC(CBPCA_STATISTIC_HDLC_DECAP_NO_DATA_FIELD);

        CBPA_ERROR_LOG("CBPCA_DispatchReceivedData: ulInfoLength <= 6!");
        return;
    }

    /* 获取CBPCA管理上下文指针 */
    pCbpcaCtx = CBPCA_GetCtxAddr();

    /* 判断Index是否与预期的index相等 */
    /*lint -e534*/
    VOS_MemCpy((VOS_VOID *)&usIndex, (VOS_VOID *)pucData, sizeof(VOS_UINT16));
    /*lint +e534*/
    if (pCbpcaCtx->usExpectRcvIndex != usIndex)
    {
        /* 记录可维可测信息，当前先不实现重发，Index错误也继续处理 */
        CBPCA_STATISTIC_INC(CBPCA_STATISTIC_HDLC_DECAP_INVALID_INDEX);
        if (0xffff == usIndex)
        {
            CBPCA_DecreaseIndex(&(CBPCA_GetCtxAddr()->usExpectRcvIndex));
        }
        else if(pCbpcaCtx->usExpectRcvIndex > usIndex)
        {
            /* 打印输出记录错误INDEX信息 */
            /*lint -e534*/
            vos_printf("CBPCA_DispatchReceivedData:ExpectRcvIndex>usIndex,index is 0x%x,pCbpcaCtx->usExpectRcvIndex is 0x%x\n",usIndex,pCbpcaCtx->usExpectRcvIndex);
            /*lint +e534*/
            pCbpcaCtx->usExpectRcvIndex = usIndex;
        }
        else
        {
            /* 打印输出记录错误INDEX信息 */
            /*lint -e534*/
            vos_printf("CBPCA_DispatchReceivedData: index is 0x%x,pCbpcaCtx->usExpectRcvIndex is 0x%x\n",usIndex,pCbpcaCtx->usExpectRcvIndex);
            /*lint +e534*/
            for(i=0;i<ulInfoLength;i++)
            {
                /*lint -e534*/
                vos_printf("pucData[%d]: 0x%x\n",i,pucData[i]);
                /*lint +e534*/
            }
            mdrv_om_system_error(CBPCA_VIAMSG_INDEX_ERROR,THIS_FILE_ID, __LINE__, 0, 0);
            pCbpcaCtx->usExpectRcvIndex = usIndex;
        }
    }

    /* Length为MsgId和Data域长度之和，判断其合法性 */
    pucData += sizeof(VOS_UINT16);
    /*lint -e534*/
    (VOS_VOID)VOS_MemCpy((VOS_VOID *)&usLength, (VOS_VOID *)pucData, sizeof(VOS_UINT16));
    /*lint +e534*/

    if (usLength <= sizeof(usMsgId))
    {
        /* 记录可维可测信息 */
        CBPCA_STATISTIC_INC(CBPCA_STATISTIC_HDLC_DECAP_LENGTH_ABNORMAL);

        CBPA_ERROR_LOG("CBPCA_DispatchReceivedData: usLength <= 2!");
        return;
    }

    if (usLength != (ulInfoLength - sizeof(usIndex) - sizeof(usLength)))
    {
        /* 若usLength小于实际长度，则按照usLength为准，否则按照实际长度为准 */
        if (usLength < (ulInfoLength - sizeof(usIndex) - sizeof(usLength)))
        {
            /* 记录可维可测信息 */
            CBPCA_STATISTIC_INC(CBPCA_STATISTIC_HDLC_DECAP_LENGTH_IS_LESS);

            usRawDataLength = usLength - sizeof(usMsgId);
        }
        else
        {
            /* 记录可维可测信息 */
            CBPCA_STATISTIC_INC(CBPCA_STATISTIC_HDLC_DECAP_LENGTH_IS_MORE);

            usRawDataLength = (VOS_UINT16)(ulInfoLength - sizeof(usIndex) - sizeof(usLength) - sizeof(usMsgId));
        }
    }
    else
    {
        usRawDataLength = usLength - sizeof(usMsgId);
    }

    /* 根据MsgId找到需要转发到的PID */
    pucData += sizeof(VOS_UINT16);
    /*lint -e534*/
    VOS_MemCpy((VOS_VOID *)&usMsgId, (VOS_VOID *)pucData, sizeof(VOS_UINT16));
    /*lint +e534*/
    if (VOS_OK != CBPCA_FindMatchPidByMsgId(usMsgId, &ulRcvPid, &enMsgType))
    {
        /* 记录可维可测信息，并丢弃该帧 */
        CBPCA_STATISTIC_INC(CBPCA_STATISTIC_HDLC_DECAP_INVALID_MSGID);

        return;
    }

    /* 将指针指向Data域 */
    pucData += sizeof(VOS_UINT16);

    /* 将数据转发至目的PID */
    CBPCA_TransferDataToUpperLayer(ulRcvPid, enMsgType, pucData, usRawDataLength);

    /* 可维可测信息统计 */
    CBPCA_STATISTIC_INC(CBPCA_STATISTIC_HDLC_DECAP_SUCC);

    return;
}

/*****************************************************************************
函 数 名  : CBPCA_UartRcvCBFunc
功能描述  : CBPCA向底软UART注册的接收数据回调函数
输入参数  : uPortNo  -- 底软通道编号
            pData    -- 发给CBPA数据
            ulLength -- 数据长度

输出参数  : 无
返 回 值  : VOS_INT
History     :
1.日    期  : 2013年12月19日
  作    者  : L00256032
  修改内容  : Create
*****************************************************************************/
VOS_INT  CBPCA_UartRcvCBFunc(UART_CONSUMER_ID uPortNo, VOS_UINT8 *pucData, VOS_UINT32 ulLength)
{
    VOS_UINT32                          ulLoop;
    OM_HDLC_STRU                       *pstDecapCtrlCtx;
    OM_HDLC_RESULT_ENUM_UINT32          enDecapResult;
    VOS_INT                             iResult = VOS_ERROR;

    /* 判断ucPortNo合法性 */
    if (CBP_UART_PORT_ID != uPortNo)
    {
        /* 可维可测统计 */
        CBPCA_STATISTIC_INC(CBPCA_STATISTIC_UART_CALLBACK_WRONG_PORTNO);

        CBPA_ERROR_LOG("CBPCA_UartRcvCBFunc: ucPortNo != CBP_UART_PORT_ID!");
        return VOS_ERROR;
    }

    /* pData合法性检查 */
    if (VOS_NULL_PTR == pucData)
    {
        /* 可维可测统计 */
        CBPCA_STATISTIC_INC(CBPCA_STATISTIC_UART_CALLBACK_NULL_PTR);

        CBPA_ERROR_LOG("CBPCA_UartRcvCBFunc: pucData is VOS_NULL_PTR!");
        return VOS_ERROR;
    }

    /* uslength合法性检查 */
    if (VOS_NULL == ulLength)
    {
        /* 可维可测统计 */
        CBPCA_STATISTIC_INC(CBPCA_STATISTIC_UART_CALLBACK_LEN_IS_ZERO);

        CBPA_ERROR_LOG("CBPCA_UartRcvCBFunc: ulLength is 0!");
        return VOS_ERROR;
    }

    /* 判断CBP是否ready */
    if (CBP_MODEM_STATUS_READY != CBPCA_GetCtxAddr()->enCBPStatus)
    {
        /* 可维可测统计 */
        CBPCA_STATISTIC_INC(CBPCA_STATISTIC_UART_CALLBACK_CBP_NOT_READY);

        CBPA_ERROR_LOG("CBPCA_UartRcvCBFunc: CBP is not ready!");
        return VOS_ERROR;
    }

    /* 执行勾包操作 */
    CBPCA_UartDataHook(ulLength, pucData);

    pstDecapCtrlCtx = &(CBPCA_GetCtxAddr()->stDecapCtrlCtx);

    /* 执行解封装操作 */
    for (ulLoop = 0; ulLoop < ulLength; ulLoop++)
    {
        enDecapResult = Om_HdlcDecap(pstDecapCtrlCtx, pucData[ulLoop]);

        switch (enDecapResult)
        {
            case HDLC_SUCC:
                /*lint -e40*/
                CBPA_DEBUG_TRACE(pstDecapCtrlCtx->pucDecapBuff, pstDecapCtrlCtx->ulInfoLen);
                /*lint +e40*/

                /* 解析出一个完整HDLC帧，执行转发处理 */
                CBPCA_DispatchReceivedData(pstDecapCtrlCtx->pucDecapBuff, pstDecapCtrlCtx->ulInfoLen);

                /* 将HDLC解析结构还原 */
                Om_HdlcInit(pstDecapCtrlCtx);

                /* 累加接收Index */
                CBPCA_IncreaseIndex(&(CBPCA_GetCtxAddr()->usExpectRcvIndex));

                iResult = VOS_OK;
                break;

            case HDLC_NOT_HDLC_FRAME:
                /*不是完整分帧, 继续HDLC解封装*/
                iResult = VOS_OK;
                break;

            case HDLC_FCS_ERROR:
                /* FCS校验失败，进行可维可测统计 */
                CBPCA_STATISTIC_INC(CBPCA_STATISTIC_HDLC_DECAP_FCS_ERR);

                /* 累加接收Index */
                CBPCA_IncreaseIndex(&(CBPCA_GetCtxAddr()->usExpectRcvIndex));

                iResult = VOS_ERROR;
                break;

            case HDLC_FRAME_DISCARD:
                /* 异常帧，进行可维可测统计 */
                CBPCA_STATISTIC_INC(CBPCA_STATISTIC_HDLC_DECAP_DISCARD);

                /* 累加接收Index */
                CBPCA_IncreaseIndex(&(CBPCA_GetCtxAddr()->usExpectRcvIndex));

                iResult = VOS_ERROR;
                break;

            case HDLC_BUFF_FULL:
                /* 超出缓存，进行可维可测统计 */
                CBPCA_STATISTIC_INC(CBPCA_STATISTIC_HDLC_DECAP_BUFF_FULL);

                /* 累加接收Index */
                CBPCA_IncreaseIndex(&(CBPCA_GetCtxAddr()->usExpectRcvIndex));

                iResult = VOS_ERROR;
                break;
            case HDLC_PARA_ERROR:
                /* 入参错误，进行可维可测统计 */
                CBPCA_STATISTIC_INC(CBPCA_STATISTIC_HDLC_DECAP_PARA_ERROR);

                /* 累加接收Index */
                CBPCA_IncreaseIndex(&(CBPCA_GetCtxAddr()->usExpectRcvIndex));

                iResult = VOS_ERROR;
                break;

            default:
                /* 其他错误，进行可维可测统计 */
                CBPCA_STATISTIC_INC(CBPCA_STATISTIC_HDLC_DECAP_INVALID_FRAME);

                /* 累加接收Index */
                CBPCA_IncreaseIndex(&(CBPCA_GetCtxAddr()->usExpectRcvIndex));

                iResult = VOS_ERROR;
                break;
        }
    }

    return iResult;
}

/*****************************************************************************
函 数 名  : CBPCA_Init
功能描述  : CBPCA模块初始化
输入参数  : 无
输出参数  : 无
返 回 值  : VOS_OK/VOS_ERR
History     :
1.日    期  : 2013年12月19日
  作    者  : L00256032
  修改内容  : Create
*****************************************************************************/
VOS_UINT32 CBPCA_Init(VOS_VOID)
{
    CBPCA_CTX_STRU                     *pstCbpcaCtx;
/*    VOS_INT                             iResult;*/
    TAF_NV_LC_CTRL_PARA_STRU            stModem0LcCtrl = {0};
    TAF_NV_LC_CTRL_PARA_STRU            stModem1LcCtrl = {0};
    VOS_UINT32                          ulResult0;
    VOS_UINT32                          ulResult1;

    /* 获取CBPCA CTX的指针 */
    pstCbpcaCtx = CBPCA_GetCtxAddr();

    /* 将CBPCA CTX上下文清空 */
    /*lint -e534*/
    VOS_MemSet(pstCbpcaCtx, 0, sizeof(CBPCA_CTX_STRU));
    /*lint +e534*/

    /* 判断双卡L+C特性NV是否开启，若未开启，则不需执行初始化操作 */
    ulResult0 = NV_ReadEx(MODEM_ID_0, en_NV_Item_LC_Ctrl_PARA, &stModem0LcCtrl, sizeof(TAF_NV_LC_CTRL_PARA_STRU));

    ulResult1 = NV_ReadEx(MODEM_ID_1, en_NV_Item_LC_Ctrl_PARA, &stModem1LcCtrl, sizeof(TAF_NV_LC_CTRL_PARA_STRU));

    /*如果读取全部失败才退出，否则按照其中某个配置*/
    if ((NV_OK != ulResult0)
     && (NV_OK != ulResult1))
    {
        CBPA_ERROR_LOG("CBPCA_Init: NV en_NV_Item_LC_Ctrl_PARA read fail!");
        return VOS_OK;
    }

    /*全网通产品主副卡都需要打开，电信版本只需要打开主卡*/
    if ((VOS_TRUE != stModem0LcCtrl.ucLCEnableFlg)
     && (VOS_TRUE != stModem1LcCtrl.ucLCEnableFlg))
    {
        CBPA_NORMAL_LOG("CBPCA_Init: NV en_NV_Item_LC_Ctrl_PARA is off!");
        return VOS_OK;
    }

    /* 如果副卡打开CL功能，说明代理在副卡上面，否则默认在主卡 */
    if ((VOS_TRUE                     == stModem0LcCtrl.ucLCEnableFlg)
     && (TAF_NVIM_LC_RAT_COMBINED_GUL == stModem0LcCtrl.enRatCombined)
     && (VOS_TRUE                     == stModem1LcCtrl.ucLCEnableFlg)
     && (TAF_NVIM_LC_RAT_COMBINED_CL  == stModem1LcCtrl.enRatCombined))
    {
        g_astCbpcaPidMsgIdMapTbl[0].ulPid = I1_WUEPS_PID_CSIMA;
    }

    /* 申请用于HDLC封装的缓存 */
    pstCbpcaCtx->stEncapCtrlCtx.pucEncapBuff = (VOS_UINT8 *)VOS_MemAlloc(WUEPS_PID_CBPCA, STATIC_MEM_PT, CBPCA_HDLC_BUFFER_SIZE);

    if (VOS_NULL_PTR == pstCbpcaCtx->stEncapCtrlCtx.pucEncapBuff)
    {
        CBPA_ERROR_LOG("CBPCA_Init: Alloc Encapsulate buffer fail!");
        return VOS_ERR;
    }

    /* HDLC封装缓存长度赋值 */
    pstCbpcaCtx->stEncapCtrlCtx.ulEncapBuffSize = CBPCA_HDLC_BUFFER_SIZE;

    /* 申请用于HDLC解封装的缓存 */
    pstCbpcaCtx->stDecapCtrlCtx.pucDecapBuff = (VOS_UINT8 *)VOS_MemAlloc(WUEPS_PID_CBPCA, STATIC_MEM_PT, CBPCA_HDLC_BUFFER_SIZE);
    if (VOS_NULL_PTR == pstCbpcaCtx->stDecapCtrlCtx.pucDecapBuff)
    {
        CBPA_ERROR_LOG("CBPCA_Init: Alloc Decapsulate buffer fail!");

        /*lint -e534*/
        VOS_MemFree(WUEPS_PID_CBPCA, pstCbpcaCtx->stEncapCtrlCtx.pucEncapBuff);
        /*lint +e534*/
        return VOS_ERR;
    }

    /* HDLC解封装缓存长度赋值 */
    pstCbpcaCtx->stDecapCtrlCtx.ulDecapBuffSize = CBPCA_HDLC_BUFFER_SIZE;

    /* 初始化HDLC解封装控制上下文 */
    Om_HdlcInit(&pstCbpcaCtx->stDecapCtrlCtx);

    /* 初始化收发HDLC帧的Index索引为0 */
    CBPCA_RestoreIndex();

    /* 初始化CBP是否ready的全局标记变量为"NOT READY" */
    pstCbpcaCtx->enCBPStatus = CBP_MODEM_STATUS_NOT_READY;

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : CBPCA_PidInit
功能描述  : CBPCA PID初始化
输入参数  : ip 初始化阶段
输出参数  : 无
返 回 值  : VOS_OK/VOS_ERR
History     :
1.日    期  : 2013年12月19日
  作    者  : L00256032
  修改内容  : Create
*****************************************************************************/
VOS_UINT32 CBPCA_PidInit(enum VOS_INIT_PHASE_DEFINE ip)
{
    switch (ip)
    {
        case VOS_IP_INITIAL:
            return CBPCA_Init();

        default:
            break;
    }

    return VOS_OK;
}
#endif /* FEATURE_ON == FEATURE_CL_INTERWORK */

/*****************************************************************************
函 数 名  : CBPCA_FidInit
功能描述  : CBPA模块FID初始化
输入参数  : ip  ---初始化所处阶段
输出参数  : 无
返 回 值  : VOS_OK/VOS_ERR
History     :
1.日    期  : 2013年12月19日
  作    者  : L00256032
  修改内容  : Create
*****************************************************************************/
VOS_UINT32 CBPCA_FidInit(enum VOS_INIT_PHASE_DEFINE ip)
{
#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    VOS_UINT32      ulRslt;

    switch (ip)
    {
        case VOS_IP_LOAD_CONFIG:
        {
            ulRslt = VOS_RegisterPIDInfo(WUEPS_PID_CBPCA,
                                        (Init_Fun_Type)CBPCA_PidInit,
                                        (Msg_Fun_Type)CBPCA_PidMsgProc);
            if (VOS_OK != ulRslt)
            {
                return VOS_ERR;
            }

            /* 注册任务优先级 */
            ulRslt = VOS_RegisterMsgTaskPrio(WUEPS_FID_CBPCA, VOS_PRIORITY_P1);

            if (VOS_OK != ulRslt)
            {
                return VOS_ERR;
            }

            break;
        }
        default:
            break;
    }
#endif /* FEATURE_ON == FEATURE_CL_INTERWORK */

    return VOS_OK;
}


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

