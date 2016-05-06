/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TtfErrlog.c
  版 本 号   : 初稿
  作    者   : t00148005
  生成日期   : 2013年10月5日
  最近修改   :
  功能描述   : GU TTF Errlog功能模块
  函数列表   :
              GTTF_MNTN_ErrlogMdlErrEvt
              GTTF_MNTN_ErrlogTbfAbnmlEvt
              TTF_MNTN_ErrlogBufGet
              TTF_MNTN_ErrlogBufPut
              TTF_MNTN_ErrlogBufRpt
              TTF_MNTN_ErrlogCbReg
              TTF_MNTN_ErrlogCbRun
              TTF_MNTN_ErrLogGetModuleId
              TTF_MNTN_ErrLogRcvCtrlInd
              TTF_MNTN_ErrLogRcvRptReq
              TTF_MNTN_ErrlogShow
              TTF_MNTN_InitErrlogBuffer
              TTF_MNTN_InitErrLogEnt
              WTTF_MNTN_ErrlogFlushRlcErrEvt
              WTTF_MNTN_ErrlogRlcLiErrEvt
              WTTF_MNTN_ErrlogRlcResetEvt
              WTTF_MNTN_ErrlogTfciFailEvt

  修改历史   :
  1.日    期   : 2013年10月5日
    作    者   : t00148005
    修改内容   : 创建文件

******************************************************************************/


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TtfErrlog.h"
#include "TtfMemoryMap.h"
#include "TTFMemCtrl.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TTF_ERR_LOG_C

#if (FEATURE_PTM == FEATURE_ON)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )

/* three modems */
#if ( 3 == MULTI_MODEM_NUMBER )
TTF_MNTN_ERR_LOG_ENT_STRU               g_stTtfMntnErrlogEnt =
{
    {VOS_NO, VOS_NO, VOS_NO},
    {{0, 0, {0, 0}},{0, 0, {0, 0}},{0, 0, {0, 0}}},
    {{VOS_NULL_PTR, 0, 0},{VOS_NULL_PTR, 0, 0},{VOS_NULL_PTR, 0, 0}},
    {0, 0, 0},
    {0, 0, 0},
    {VOS_NULL_PTR, VOS_NULL_PTR, VOS_NULL_PTR},
    {VOS_NULL_PTR, VOS_NULL_PTR, VOS_NULL_PTR},
    {VOS_NULL_PTR, VOS_NULL_PTR, VOS_NULL_PTR}
};

/* two modems */
#else
TTF_MNTN_ERR_LOG_ENT_STRU               g_stTtfMntnErrlogEnt =
{
    {VOS_NO, VOS_NO},
    {{0, 0, {0, 0}},{0, 0, {0, 0}}},
    {{VOS_NULL_PTR, 0, 0},{VOS_NULL_PTR, 0, 0}},
    {0, 0},
    {0, 0},
    {VOS_NULL_PTR, VOS_NULL_PTR},
    {VOS_NULL_PTR, VOS_NULL_PTR},
    {VOS_NULL_PTR, VOS_NULL_PTR}
};
#endif

/* only one modem */
#else
TTF_MNTN_ERR_LOG_ENT_STRU               g_stTtfMntnErrlogEnt =
{
    {VOS_NO},
    {{0, 0, {0, 0}}},
    {{VOS_NULL_PTR, 0, 0}},
    {0},
    {0},
    {VOS_NULL_PTR},
    {VOS_NULL_PTR},
    {VOS_NULL_PTR}
};
#endif

TTF_MNTN_ERR_LOG_RPT_CB                 apErrLogRptCb[MODEM_ID_BUTT][MODULE_ID_BUTT];

/* ALM ID从1开始的，所以数组0的取值为BUTT */
VOS_UINT8                               g_aucTtfErrlogAlmLevTbl[TTF_ERR_LOG_ALM_ID_BUTT] =
{
    TTF_ERR_LOG_ALM_LEV_BUTT,
    TTF_ERR_LOG_ALM_LEV_MAJOR,
    TTF_ERR_LOG_ALM_LEV_CRITICAL,
    TTF_ERR_LOG_ALM_LEV_CRITICAL,
    TTF_ERR_LOG_ALM_LEV_CRITICAL,
    TTF_ERR_LOG_ALM_LEV_MAJOR,
    TTF_ERR_LOG_ALM_LEV_CRITICAL,
    TTF_ERR_LOG_ALM_LEV_MAJOR,
    TTF_ERR_LOG_ALM_LEV_CRITICAL,
    TTF_ERR_LOG_ALM_LEV_CRITICAL
};

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958 */
/*****************************************************************************
 函 数 名  : TTF_MNTN_InitErrlogBuffer
 功能描述  : 初始化Errlog使用的缓存
 输入参数  : VOS_UINT32 ulPid
 输出参数  : 无
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年09月12日
    作    者   : t00148005
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TTF_MNTN_InitErrlogBuffer(MODEM_ID_ENUM_UINT16  enModemId)
{
    if (VOS_NULL_PTR != TTF_ERR_LOG_ENT_BUF_GET(enModemId))
    {
        return;
    }

    TTF_ERR_LOG_ENT_BUF_SET(enModemId, (VOS_UINT8 *)PS_ALLOC_STATIC_MEM(UEPS_PID_SN, TTF_ERR_LOG_BUF_SIZE));

    TTF_ERR_LOG_ENT_RINGID_SET(enModemId, OM_RingBufferCreateEx((VOS_CHAR *)TTF_ERR_LOG_ENT_BUF_GET(enModemId), TTF_ERR_LOG_BUF_SIZE));

    TTF_ERR_LOG_ENT_BUFFER_OVER_CNT_SET(enModemId, 0);

    return;
}

/*****************************************************************************
 函 数 名  : TTF_MNTN_InitErrLogEnt
 功能描述  : 初始化Errlog实体
 输入参数  : VOS_UINT32 ulPid
 输出参数  : 无
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年09月12日
    作    者   : t00148005
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TTF_MNTN_InitErrLogEnt(VOS_UINT32 ulPid)
{
    VOS_UINT32                  ulRslt;
    VOS_UINT32                  ulTtfCommInfoBufLen;
    MODEM_ID_ENUM_UINT16        enModemId = VOS_GetModemIDFromPid(ulPid);

    if (MODEM_ID_BUTT <= enModemId)
    {
        enModemId = MODEM_ID_0;
    }

    if (VOS_YES == TTF_ERR_LOG_ENT_STATE_GET(enModemId))
    {
        return VOS_OK;
    }

    PS_MEM_SET(apErrLogRptCb, 0, sizeof(apErrLogRptCb));

    if (TTF_MEMCTRL_MODEL_SUPPORT_YES == TTF_MEM_GET_SUPPORT_WCDMA(enModemId))
    {
        /* 初始化WCDMA基本配置信息结构体 */
        ulTtfCommInfoBufLen =   sizeof(TTF_MNTN_WCDMA_COMM_INFO_STRU);

        TTF_ERR_LOG_ENT_WCDMA_COMM_INFO_GET(enModemId) = (TTF_MNTN_WCDMA_COMM_INFO_STRU *)PS_ALLOC_STATIC_MEM(ulPid, ulTtfCommInfoBufLen);
        if (VOS_NULL_PTR == TTF_ERR_LOG_ENT_WCDMA_COMM_INFO_GET(enModemId))
        {
                TTF_LOG1(ulPid, 0, PS_PRINT_ERROR,
                    "TTF_MNTN_InitErrLogEnt: PS_ALLOC_STATIC_MEM fail!", enModemId);

            return VOS_ERR;
        }

        PS_MEM_SET(TTF_ERR_LOG_ENT_WCDMA_COMM_INFO_GET(enModemId), 0, sizeof(TTF_MNTN_WCDMA_COMM_INFO_STRU));

        TTF_ERR_LOG_FILL_HEADER(
            &(TTF_ERR_LOG_ENT_WCDMA_COMM_INFO_GET(enModemId)->stHeader),
            enModemId,
            TTF_ERR_LOG_ALM_ID_WCDMA_COMM_INFO,
            TTF_ERR_LOG_ALM_LEV_CRITICAL,
            (sizeof(TTF_MNTN_WCDMA_COMM_INFO_STRU) - sizeof(OM_ERR_LOG_HEADER_STRU)));
    }

    if (TTF_MEMCTRL_MODEL_SUPPORT_YES == TTF_MEM_GET_SUPPORT_GSM(enModemId))
    {
        /* 初始化GSM基本配置信息结构体 */
        ulTtfCommInfoBufLen =   sizeof(TTF_MNTN_GSM_COMM_INFO_STRU);

        TTF_ERR_LOG_ENT_GSM_COMM_INFO_GET(enModemId) = (TTF_MNTN_GSM_COMM_INFO_STRU *)PS_ALLOC_STATIC_MEM(ulPid, ulTtfCommInfoBufLen);
        if (VOS_NULL_PTR == TTF_ERR_LOG_ENT_GSM_COMM_INFO_GET(enModemId))
        {
                TTF_LOG1(ulPid, 0, PS_PRINT_ERROR,
                    "TTF_MNTN_InitErrLogEnt: PS_ALLOC_STATIC_MEM fail!", enModemId);

            return VOS_ERR;
        }

        PS_MEM_SET(TTF_ERR_LOG_ENT_GSM_COMM_INFO_GET(enModemId), 0, sizeof(TTF_MNTN_GSM_COMM_INFO_STRU));

        TTF_ERR_LOG_FILL_HEADER(
            &(TTF_ERR_LOG_ENT_GSM_COMM_INFO_GET(enModemId)->stHeader),
            enModemId,
            TTF_ERR_LOG_ALM_ID_GSM_COMM_INFO,
            TTF_ERR_LOG_ALM_LEV_CRITICAL,
            (sizeof(TTF_MNTN_GSM_COMM_INFO_STRU) - sizeof(OM_ERR_LOG_HEADER_STRU)));
    }

    /* 创建互斥信号量，每个Modem 1个 */
    ulRslt    = VOS_SmMCreate("TFEL", VOS_SEMA4_FIFO,
                    (VOS_SEM *)(&TTF_ERR_LOG_ENT_SEM_GET(enModemId)));

    if (VOS_OK != ulRslt)
    {
            TTF_LOG2(ulPid, 0, PS_PRINT_ERROR,
            "TTF_MNTN_InitErrLogEnt: Create TTF_ERR_LOG_ENT_SEM<1>, ulRslt<2> fail!", enModemId, (VOS_INT32)ulRslt);

        return ulRslt;
    }

    /* 读NV项获取当前上报状态 */
    ulRslt = NV_ReadEx(enModemId, en_NV_Item_ErrLogCtrlInfo,
               &g_stTtfMntnErrlogEnt.stCtrlInfo[enModemId],
               sizeof(NV_ID_ERR_LOG_CTRL_INFO_STRU));

    if (VOS_OK != ulRslt)
    {
            TTF_LOG1(ulPid, 0, PS_PRINT_ERROR,
            "TTF_MNTN_InitErrLogEnt: NV_ReadEx fail!",  (VOS_INT32)ulRslt);

        TTF_ERR_LOG_ENT_CTRL_STATUS_SET(enModemId, OM_APP_STATUS_CLOSE);
    }

    TTF_MNTN_InitErrlogBuffer(enModemId);

    TTF_ERR_LOG_ENT_STATE_SET(enModemId, VOS_YES);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TTF_MNTN_ErrLogRcvCtrlInd
 功能描述  : 收到OM ID_OM_ERR_LOG_CTRL_IND的处理函数
 输入参数  : MsgBlock *pstMsg
 输出参数  : 无
 返 回 值  : VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年09月12日
    作    者   : t00148005
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TTF_MNTN_ErrLogRcvCtrlInd(MsgBlock *pstMsg, void *p)
{
    OM_ERROR_LOG_CTRL_IND_STRU *pstCtrlInd;
    MODEM_ID_ENUM_UINT16        enModemId;

    pstCtrlInd = (OM_ERROR_LOG_CTRL_IND_STRU *)pstMsg;

    enModemId = (MODEM_ID_ENUM_UINT16)VOS_GetModemIDFromPid(pstCtrlInd->ulReceiverPid);

    if (MODEM_ID_BUTT <= enModemId)
    {
        TTF_LOG1(WUEPS_PID_RLC, 0, PS_PRINT_ERROR,
            "TTF_MNTN_ErrLogRcvCtrlInd: Invalid ModemId ", enModemId);

        return VOS_ERR;
    }

    TTF_ERR_LOG_ENT_CTRL_STATUS_SET(enModemId, pstCtrlInd->ucAlmStatus);
    TTF_ERR_LOG_ENT_CTRL_LEV_SET(enModemId, pstCtrlInd->ucAlmLevel);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TTF_MNTN_ErrlogBufRpt
 功能描述  : 将缓存的数据上报
 输入参数  : MODEM_ID_ENUM_UINT16 enModemId

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年09月12日
    作    者   : t00148005
    修改内容   : 新生成函数

*****************************************************************************/
/*lint -e{416,419,831} */
VOS_VOID TTF_MNTN_ErrlogBufRpt(VOS_UINT32 ulSenderPid, VOS_UINT32 ulReceiverPid, MODEM_ID_ENUM_UINT16 enModemId)
{
    VOS_UINT32                      ulRslt;
    VOS_UINT32                      ulErrLogBufSize;
    VOS_UINT32                      ulTtfCommInfoBufSize;
    VOS_UINT32                      ulMsgLen;
    OM_RING_ID                      pRingId;
    VOS_UINT32                      ulCpuID;
    OM_ERR_LOG_REPORT_CNF_STRU     *pstLogRpt;
    VOS_UINT32                      ulOffSetLen;
    VOS_CHAR                       *pucContent;

    if (enModemId >= MODEM_ID_BUTT)
    {
        TTF_LOG1(ulSenderPid, 0, PS_PRINT_ERROR,
            "TTF_MNTN_ErrlogBufRpt: enModemId Invalid!", enModemId);

        return;
    }

    ulCpuID         = VOS_GET_CPU_ID(ulReceiverPid);
    if ( ulCpuID >= VOS_SUPPORT_CPU_NUM_MAX )
    {
        TTF_LOG1(ulSenderPid, 0, PS_PRINT_ERROR,
            "TTF_MNTN_ErrlogBufRpt: ulReceiverPid Invalid!", (VOS_INT32)ulReceiverPid);

        return;
    }

    /* 初始化没有异常 */
    ulErrLogBufSize = 0;

    pRingId   = TTF_ERR_LOG_ENT_RINGID_GET(enModemId);
    if (VOS_NULL_PTR != pRingId)
    {
        /* 将各模块本地缓存的数据写入Buffer */
        TTF_MNTN_ErrlogCbRun(enModemId);

        /* 保留的长度复位 */
        TTF_ERR_LOG_ENT_RST_BUF_RSV_LEN(enModemId);

        ulRslt = VOS_SmP(TTF_ERR_LOG_ENT_SEM_GET(enModemId), TTF_ERR_SEM_TIMEOUT_LEN);
        if(VOS_OK != ulRslt)
        {
            TTF_LOG2(ulSenderPid, 0, PS_PRINT_WARNING,
                "TTF_MNTN_ErrlogBufRpt: VOS_SmP <1>, ulRslt<2> fail!", enModemId, (VOS_INT32)ulRslt);

            return;
        }

        ulErrLogBufSize = (VOS_UINT32)OM_RingBufferNBytes(pRingId);
        if (ulErrLogBufSize > TTF_ERR_LOG_BUF_SIZE)
        {
            OM_RingBufferFlush(pRingId);

            TTF_LOG1(ulSenderPid, 0, PS_PRINT_WARNING,
                "TTF_MNTN_ErrlogBufRpt: ulErrLogBufSize invalid!", (VOS_INT32)ulErrLogBufSize);

            ulErrLogBufSize = 0;
        }

        VOS_SmV(TTF_ERR_LOG_ENT_SEM_GET(enModemId));
    }

    ulTtfCommInfoBufSize = 0;
    if (VOS_NULL_PTR != TTF_ERR_LOG_ENT_WCDMA_COMM_INFO_GET(enModemId))
    {
        ulTtfCommInfoBufSize += sizeof(TTF_MNTN_WCDMA_COMM_INFO_STRU);
        TTF_ERR_LOG_ENT_WCDMA_COMM_INFO_GET(enModemId)->usRingBufferOverCounter = TTF_ERR_LOG_ENT_BUFFER_OVER_CNT_GET(enModemId);
    }

    if (VOS_NULL_PTR != TTF_ERR_LOG_ENT_GSM_COMM_INFO_GET(enModemId))
    {
        ulTtfCommInfoBufSize += sizeof(TTF_MNTN_GSM_COMM_INFO_STRU);
        TTF_ERR_LOG_ENT_GSM_COMM_INFO_GET(enModemId)->usRingBufferOverCounter   = TTF_ERR_LOG_ENT_BUFFER_OVER_CNT_GET(enModemId);
    }

    /* Reset环形Buffer溢出标识 */
    TTF_ERR_LOG_ENT_BUFFER_OVER_CNT_SET(enModemId, 0);

    /* 计算消息总的长度 */
    TTF_GET_OFFSET(ulOffSetLen, OM_ERR_LOG_REPORT_CNF_STRU, aucContent);
    ulMsgLen  = ulOffSetLen + ulTtfCommInfoBufSize + ulErrLogBufSize;

    pstLogRpt = (OM_ERR_LOG_REPORT_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulSenderPid, ulMsgLen);
    if (VOS_NULL_PTR == pstLogRpt)
    {
        TTF_LOG1(ulSenderPid, 0, PS_PRINT_WARNING,
                "TTF_MNTN_ErrlogBufRpt: PS_ALLOC_MSG_WITH_HEADER_LEN fail!", (VOS_INT32)ulMsgLen);
        return;
    }

    /* 开始拷贝基本信息 */
    pucContent = (VOS_CHAR *)(pstLogRpt->aucContent);

    if (VOS_NULL_PTR != TTF_ERR_LOG_ENT_WCDMA_COMM_INFO_GET(enModemId))
    /*lint -e{662,669} */
    {
        /* 拷贝WCDMA基本配置信息 */
        PS_MEM_CPY((VOS_VOID *)pucContent, (VOS_VOID *)TTF_ERR_LOG_ENT_WCDMA_COMM_INFO_GET(enModemId), (VOS_UINT32)(sizeof(TTF_MNTN_WCDMA_COMM_INFO_STRU)));
        pucContent += (VOS_UINT32)(sizeof(TTF_MNTN_WCDMA_COMM_INFO_STRU));
    }

    if (VOS_NULL_PTR != TTF_ERR_LOG_ENT_GSM_COMM_INFO_GET(enModemId))
    /*lint -e{662,669} */
    {
        /* 拷贝GSM基本配置信息 */
        PS_MEM_CPY((VOS_VOID *)pucContent, (VOS_VOID *)TTF_ERR_LOG_ENT_GSM_COMM_INFO_GET(enModemId), (VOS_UINT32)(sizeof(TTF_MNTN_GSM_COMM_INFO_STRU)));
        pucContent += (VOS_UINT32)(sizeof(TTF_MNTN_GSM_COMM_INFO_STRU));
    }

    /* 拷贝异常事件信息 */
    if (0 != ulErrLogBufSize)
    {
        TTF_MNTN_ErrlogBufGet(  ulSenderPid,
                                enModemId,
                                pucContent,
                                ulErrLogBufSize);
    }

    pstLogRpt->ulReceiverPid    = ulReceiverPid;
    pstLogRpt->ulMsgName        = ID_OM_ERR_LOG_REPORT_CNF;
    pstLogRpt->ulMsgType        = OM_ERR_LOG_MSG_ERR_REPORT;
    pstLogRpt->ulMsgSN          = mdrv_timer_get_normal_timestamp();
    pstLogRpt->ulRptlen         = ulTtfCommInfoBufSize + ulErrLogBufSize;

    PS_SEND_MSG(UEPS_PID_SN, pstLogRpt);

    return;
}

/*****************************************************************************
 函 数 名  : TTF_MNTN_ErrLogRcvRptReq
 功能描述  : 收到OM ID_OM_ERR_LOG_REPORT_REQ的处理函数
 输入参数  : MsgBlock *pstMsg
 输出参数  : 无
 返 回 值  : VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年09月12日
    作    者   : t00148005
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TTF_MNTN_ErrLogRcvRptReq(MsgBlock *pstMsg, void *p)
{
    OM_ERR_LOG_REPORT_REQ_STRU *pstRptReq;

    pstRptReq = (OM_ERR_LOG_REPORT_REQ_STRU *)pstMsg;

    /* 收到OM消息的ReciverPid作为发送PID, 发送PID作为回复消息的接收PID */
    TTF_MNTN_ErrlogBufRpt(pstRptReq->ulReceiverPid, pstRptReq->ulSenderPid, pstRptReq->usModemID);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TTF_MNTN_ErrlogBufGet
 功能描述  : 从Buffer中读取数据
 输入参数  : VOS_UINT32 ulPid
             VOS_CHAR   *pBuffer 拷入数据的缓存
             VOS_UINT32 ulBytes  读取的字节数
 输出参数  : 无
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年09月12日
    作    者   : t00148005
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TTF_MNTN_ErrlogBufGet(VOS_UINT32 ulPid, MODEM_ID_ENUM_UINT16  enModemId, VOS_CHAR *pBuffer, VOS_UINT32 ulBytes)
{
    VOS_UINT32              ulRslt;
    OM_RING_ID              pRingId;


    if (VOS_NULL_PTR == pBuffer)
    {
        TTF_LOG(ulPid, 0, PS_PRINT_ERROR,
            "TTF_MNTN_ErrlogBufGet: pBuffer NULL PTR");

        return;
    }

    if (enModemId >= MODEM_ID_BUTT)
    {
        TTF_LOG1(ulPid, 0, PS_PRINT_ERROR,
            "TTF_MNTN_ErrlogBufGet: Invalid ModemId ", enModemId);

        return;
    }

    pRingId   = TTF_ERR_LOG_ENT_RINGID_GET(enModemId);

    if (VOS_NULL_PTR == pRingId)
    {
        TTF_LOG(ulPid, 0, PS_PRINT_ERROR,
            "TTF_MNTN_ErrlogBufGet: pRingId NULL PTR");

        return;
    }

    ulRslt = VOS_SmP(TTF_ERR_LOG_ENT_SEM_GET(enModemId), TTF_ERR_SEM_TIMEOUT_LEN);

    if(VOS_OK != ulRslt)
    {
        TTF_LOG2(ulPid, 0, PS_PRINT_WARNING,
            "TTF_MNTN_ErrlogBufGet: VOS_SmP <1>, ulRslt<2> fail!", enModemId, (VOS_INT32)ulRslt);

        return;
    }

    ulRslt = (VOS_UINT32)OM_RingBufferGet(pRingId, pBuffer, (VOS_INT)ulBytes);

    if (ulRslt != ulBytes)
    {
        OM_RingBufferFlush(pRingId);

        TTF_LOG2(ulPid, 0, PS_PRINT_ERROR,
            "TTF_MNTN_ErrlogBufGet: ERROR OM_RingBufferGet fail!", (VOS_INT32)ulRslt, (VOS_INT32)ulBytes);
    }

    VOS_SmV(TTF_ERR_LOG_ENT_SEM_GET(enModemId));
}

/*****************************************************************************
 函 数 名  : TTF_MNTN_ErrlogBufPut
 功能描述  : 向Buffer中写入数据
 输入参数  : VOS_UINT32 ulPid
             VOS_CHAR   *pBuffer 源数据缓存
             VOS_UINT32 ulBytes  写入的字节长度
 输出参数  : 无
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年09月12日
    作    者   : t00148005
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TTF_MNTN_ErrlogBufPut(VOS_UINT32 ulPid,  VOS_CHAR *pBuffer, VOS_UINT32 ulBytes)
{
    MODEM_ID_ENUM_UINT16    enModemId;
    VOS_UINT32              ulRslt;
    VOS_UINT32              ulBuffFreeSize;
    OM_RING_ID              pRingId;

    if (VOS_NULL_PTR == pBuffer)
    {
        TTF_LOG(ulPid, 0, PS_PRINT_WARNING,
            "TTF_MNTN_ErrlogBufPut: pBuffer NULL PTR");

        return;
    }

    enModemId = VOS_GetModemIDFromPid(ulPid);

    if (enModemId >= MODEM_ID_BUTT)
    {
        TTF_LOG1(ulPid, 0, PS_PRINT_ERROR,
            "TTF_MNTN_ErrlogBufPut: Invalid ModemId ", enModemId);

        return;
    }

    pRingId   = TTF_ERR_LOG_ENT_RINGID_GET(enModemId);

    if (VOS_NULL_PTR == pRingId)
    {
        TTF_LOG(ulPid, 0, PS_PRINT_WARNING,
            "TTF_MNTN_ErrlogBufPut: pRingId NULL PTR");

        return;
    }

    ulRslt = VOS_SmP(TTF_ERR_LOG_ENT_SEM_GET(enModemId), TTF_ERR_SEM_TIMEOUT_LEN);

    if(VOS_OK != ulRslt)
    {
        TTF_LOG2(ulPid, 0, PS_PRINT_WARNING,
            "TTF_MNTN_ErrlogBufPut: Create TTF_ERR_LOG_ENT_SEM<1>, ulRslt<2> fail!", enModemId, (VOS_INT32)ulRslt);

        return;
    }

    ulBuffFreeSize  =(VOS_UINT32) OM_RingBufferFreeBytes(pRingId);

    /* Buffer不足，溢出处理 */
    if (ulBuffFreeSize < (ulBytes + TTF_ERR_LOG_ENT_GET_BUF_RSV_LEN(enModemId)))
    {
        TTF_ERR_LOG_ENT_UPDT_BUFFER_OVER_CNT(enModemId, 1);
        OM_RingBufferFlush(pRingId);
    }

    ulRslt = (VOS_UINT32)OM_RingBufferPut(pRingId, pBuffer, (VOS_INT)ulBytes);

    if (ulBytes != ulRslt)
    {
        OM_RingBufferFlush(pRingId);
    }

    VOS_SmV(TTF_ERR_LOG_ENT_SEM_GET(enModemId));

    return;
}


/*****************************************************************************
 函 数 名  : TTF_MNTN_ErrLogGetModuleId
 功能描述  : 将PID转为私有MODULE ID
 输入参数  : VOS_UINT32 ulPid

 输出参数  : 无
 返 回 值  : MODULE ID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年09月12日
    作    者   : t00148005
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TTF_MNTN_ErrLogGetModuleId(VOS_UINT32 ulPid)
{
    VOS_UINT32 ulIndx;
    TTF_MNTN_ERR_LOG_PID_MODULE_STRU astPidModuleTb[] =
    {
        {I0_UEPS_PID_SN,       MODULE_ID_SN},
        {I1_UEPS_PID_SN,       MODULE_ID_SN},
        {I2_UEPS_PID_SN,       MODULE_ID_SN},
        {I0_UEPS_PID_GRM,      MODULE_ID_GRM},
        {I1_UEPS_PID_GRM,      MODULE_ID_GRM},
        {I2_UEPS_PID_GRM,      MODULE_ID_GRM},
        {I0_UEPS_PID_LL,       MODULE_ID_LLC},
        {I1_UEPS_PID_LL,       MODULE_ID_LLC},
        {I2_UEPS_PID_LL,       MODULE_ID_LLC},
        {I0_UEPS_PID_DL,       MODULE_ID_DL},
        {I1_UEPS_PID_DL,       MODULE_ID_DL},
        {I2_UEPS_PID_DL,       MODULE_ID_DL},
        {WUEPS_PID_PDCP,       MODULE_ID_PDCP},
        {WUEPS_PID_RLC,        MODULE_ID_WRM},
        {WUEPS_PID_MAC,        MODULE_ID_WRM}
    };

    for (ulIndx = 0; ulIndx < TTF_ARRAY_SIZE(astPidModuleTb); ulIndx++)
    {
        if (astPidModuleTb[ulIndx].ulPid == ulPid)
        {
            return (VOS_UINT8)astPidModuleTb[ulIndx].ulModuleId;
        }
    }

    return MODULE_ID_BUTT;
}

/*****************************************************************************
 函 数 名  : TTF_MNTN_ErrlogCbReg
 功能描述  : 注册回调函数
 输入参数  : VOS_UINT32 ulPid
             TTF_MNTN_ERR_LOG_RPT_CB pErrlogCb

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年09月12日
    作    者   : t00148005
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TTF_MNTN_ErrlogCbReg(VOS_UINT32 ulPid, TTF_MNTN_ERR_LOG_RPT_CB pErrlogCb)
{
    TTF_MODULE_ID_ENUM_UINT8 enModuleId;
    MODEM_ID_ENUM_UINT16     enModemId;


    enModuleId = TTF_MNTN_ErrLogGetModuleId(ulPid);

    if (MODULE_ID_BUTT <= enModuleId)
    {
        return;
    }

    enModemId = VOS_GetModemIDFromPid(ulPid);

    if (enModemId >= MODEM_ID_BUTT)
    {
        TTF_LOG1(ulPid, 0, PS_PRINT_ERROR,
            "TTF_MNTN_ErrlogCbReg: Invalid ModemId ", enModemId);

        return;
    }

    TTF_ERR_LOG_RPT_CB_SET(enModemId, enModuleId, pErrlogCb);
}

/*****************************************************************************
 函 数 名  : TTF_MNTN_ErrlogCbRun
 功能描述  : 运行所有回调函数
 输入参数  : MODEM_ID_ENUM_UINT16 enModemId

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年09月12日
    作    者   : t00148005
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TTF_MNTN_ErrlogCbRun(MODEM_ID_ENUM_UINT16 enModemId)
{
    VOS_UINT32                  ulIndx;
    TTF_MNTN_ERR_LOG_RPT_CB     pErrlogRptCb;

    if (enModemId >= MODEM_ID_BUTT)
    {
        return;
    }

    for(ulIndx = 0; ulIndx < MODULE_ID_BUTT; ulIndx++)
    {
        pErrlogRptCb = TTF_ERR_LOG_RPT_CB_GET(enModemId, ulIndx);
        if (VOS_NULL_PTR != pErrlogRptCb)
        {
            pErrlogRptCb();
        }
    }
}

/*****************************************************************************
 函 数 名  : GTTF_MNTN_ErrlogTbfAbnmlEvt
 功能描述  : 生成GRPS TBF异常事件并保存到缓存中
 输入参数  : VOS_UINT32 ulPid   PID
             VOS_UINT16 usType  异常类型

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年09月20日
    作    者   : t00148005
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID GTTF_MNTN_ErrlogTbfAbnmlEvt(VOS_UINT32 ulPid, VOS_UINT16 usType)
{
    TTF_MNTN_ERR_LOG_GRLC_TBF_ABNML_STRU stTbfAbnml;
    VOS_UINT8                            ucAlmLev;
    MODEM_ID_ENUM_UINT16                 enModemId;

    ucAlmLev    = TTF_ERR_LOG_GET_ALM_LEV(TTF_ERR_LOG_ALM_ID_GPRS_TBF_ABNML);
    enModemId   = VOS_GetModemIDFromPid(ulPid);
    if (MODEM_ID_BUTT <= enModemId)
    {
        TTF_LOG1(ulPid, 0, PS_PRINT_ERROR,
            "GTTF_MNTN_ErrlogTbfAbnmlEvt: Invalid ModemId ", enModemId);

        return;
    }

    if (!TTF_ERR_LOG_NEED_RPT_LEV(enModemId, ucAlmLev))
    {
        return;
    }

    TTF_ERR_LOG_FILL_HEADER(
        &stTbfAbnml.stHeader,
        enModemId,
        TTF_ERR_LOG_ALM_ID_GPRS_TBF_ABNML,
        ucAlmLev,
        (sizeof(TTF_MNTN_ERR_LOG_GRLC_TBF_ABNML_STRU) - sizeof(OM_ERR_LOG_HEADER_STRU)));

    stTbfAbnml.usAbnmlType = (VOS_UINT16)usType;

    TTF_MNTN_ErrlogBufPut(ulPid, (VOS_CHAR *)&stTbfAbnml, sizeof(TTF_MNTN_ERR_LOG_GRLC_TBF_ABNML_STRU));
}

/*****************************************************************************
 函 数 名  : GTTF_MNTN_ErrlogMdlErrEvt
 功能描述  : 生成GSM MDL Err事件
 输入参数  : VOS_UINT32 ulPid
             VOS_VOID *pMdlErr
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月23日
    作    者   : t00148005
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID GTTF_MNTN_ErrlogMdlErrEvt(VOS_UINT32 ulPid, VOS_VOID *pMdlErr)
{
    TTF_MNTN_ERR_LOG_GDL_MDL_ERR_STRU       stMdlErrEvt;
    VOS_UINT8                               ucAlmLev;
    MODEM_ID_ENUM_UINT16                    enModemId;

    if (VOS_NULL_PTR == pMdlErr)
    {
        return;
    }

    ucAlmLev    = TTF_ERR_LOG_GET_ALM_LEV(TTF_ERR_LOG_ALM_ID_GSM_MDL_ERR);
    enModemId   = VOS_GetModemIDFromPid(ulPid);
    if (MODEM_ID_BUTT <= enModemId)
    {
        TTF_LOG1(ulPid, 0, PS_PRINT_ERROR,
            "GTTF_MNTN_ErrlogMdlErrEvt: Invalid ModemId ", enModemId);

        return;
    }

    if (!TTF_ERR_LOG_NEED_RPT_LEV(enModemId, ucAlmLev))
    {
        return;
    }

    TTF_ERR_LOG_FILL_HEADER(
        &stMdlErrEvt.stHeader,
        enModemId,
        TTF_ERR_LOG_ALM_ID_GSM_MDL_ERR,
        ucAlmLev,
        (sizeof(TTF_MNTN_ERR_LOG_GDL_MDL_ERR_STRU) - sizeof(OM_ERR_LOG_HEADER_STRU)));

    PS_MEM_CPY(&stMdlErrEvt.stDlMdlErrInfo, pMdlErr, sizeof(TTF_MNTN_GDL_MDL_ERR_INFO_STRU));

    TTF_MNTN_ErrlogBufPut(ulPid, (VOS_CHAR *)&stMdlErrEvt, sizeof(TTF_MNTN_ERR_LOG_GDL_MDL_ERR_STRU));
}

/*****************************************************************************
 函 数 名  : WTTF_MNTN_ErrlogRlcResetEvt
 功能描述  : RLC Reset event record
 输入参数  : VOS_UINT8 ucRbId                                           - Rb Id
             TTF_MNTN_ERR_LOG_WRLC_RESET_TYPE_ENUM_UINT8 enResetType    - Rlc reset type

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013.09.20
    作    者   : x59651
    修改内容   : create new function

*****************************************************************************/
VOS_VOID WTTF_MNTN_ErrlogRlcResetEvt(VOS_UINT32 ulPid, VOS_UINT8 ucRbId,
    TTF_MNTN_ERR_LOG_WRLC_RESET_TYPE_ENUM_UINT8 enResetType)
{
    TTF_MNTN_ERR_LOG_WRLC_RESET_STRU    stTtfMntnWrlcReset;
    VOS_UINT8                           ucAlmLev;
    MODEM_ID_ENUM_UINT16                enModemId;

    ucAlmLev    = TTF_ERR_LOG_GET_ALM_LEV(TTF_ERR_LOG_ALM_ID_WRLC_RESET);
    enModemId   = VOS_GetModemIDFromPid(ulPid);
    if (MODEM_ID_BUTT <= enModemId)
    {
        TTF_LOG1(ulPid, 0, PS_PRINT_ERROR,
            "WTTF_MNTN_ErrlogRlcResetEvt: Invalid ModemId ", enModemId);

        return;
    }

    if (!TTF_ERR_LOG_NEED_RPT_LEV(enModemId, ucAlmLev))
    {
        return;
    }

    TTF_ERR_LOG_FILL_HEADER(
        &stTtfMntnWrlcReset.stHeader,
        enModemId,
        TTF_ERR_LOG_ALM_ID_WRLC_RESET,
        ucAlmLev,
        (sizeof(TTF_MNTN_ERR_LOG_WRLC_RESET_STRU) - sizeof(OM_ERR_LOG_HEADER_STRU)));

    stTtfMntnWrlcReset.ucRbId       = ucRbId;
    stTtfMntnWrlcReset.enResetType  = enResetType;
    stTtfMntnWrlcReset.usResetCnt   = 1;

    /* 生成Reset事件 */
    TTF_MNTN_ErrlogBufPut(ulPid, (VOS_CHAR *)&stTtfMntnWrlcReset, sizeof(TTF_MNTN_ERR_LOG_WRLC_RESET_STRU));
}

/*****************************************************************************
 函 数 名  : WTTF_MNTN_ErrlogTfciFailEvt
 功能描述  : report TFC select fail event
 输入参数  : VOS_UINT8 ucMacState                               - MAC UL state
             TTF_MNTN_ERR_LOG_TFC_ERR_NO_CHOICE_ENUM8 enType    - TFC select fail type
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013.09.21
    作    者   : x59651
    修改内容   : create new function

*****************************************************************************/
VOS_VOID  WTTF_MNTN_ErrlogTfciFailEvt(VOS_UINT32 ulPid, VOS_UINT8 ucMacState,
    TTF_MNTN_ERR_LOG_TFC_ERR_NO_CHOICE_ENUM8 enType)
{
    VOS_UINT8                      ucAlmLev;
    WTTF_MNTN_TFCI_FAIL_STRU       stTtfMNtnTfciFail;
    MODEM_ID_ENUM_UINT16           enModemId;

    ucAlmLev       = TTF_ERR_LOG_GET_ALM_LEV(TTF_ERR_LOG_ALM_ID_WRLC_TFCI_FAIL);
    enModemId      = VOS_GetModemIDFromPid(ulPid);
    if (MODEM_ID_BUTT <= enModemId)
    {
        TTF_LOG1(ulPid, 0, PS_PRINT_ERROR,
            "WTTF_MNTN_ErrlogTfciFailEvt: Invalid ModemId ", enModemId);

        return;
    }

    if (!TTF_ERR_LOG_NEED_RPT_LEV(enModemId, ucAlmLev))
    {
        return;
    }

    TTF_ERR_LOG_FILL_HEADER(
             &stTtfMNtnTfciFail.stHeader,
             enModemId,
             TTF_ERR_LOG_ALM_ID_WRLC_TFCI_FAIL,
             ucAlmLev,
             (sizeof(WTTF_MNTN_TFCI_FAIL_STRU) - sizeof(OM_ERR_LOG_HEADER_STRU)));

    stTtfMNtnTfciFail.ucMacState    = ucMacState;
    stTtfMNtnTfciFail.enType        = enType;

    /* 异常事件写入缓存中 */
    TTF_MNTN_ErrlogBufPut(ulPid, (VOS_CHAR *)&stTtfMNtnTfciFail,
        sizeof(WTTF_MNTN_TFCI_FAIL_STRU));

    return;
}

/*****************************************************************************
 函 数 名  : TTF_MNTN_ErrlogGetCommInfoBuffAddrForGUL
 功能描述  : 获取记录G上行信息结构体指针
 输入参数  : ulPid
 输出参数  : 无
 返 回 值  : GTTF_UL_INFO_STRU *
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月5日
    作    者   : g00178567
    修改内容   : 新生成函数

*****************************************************************************/
GTTF_UL_INFO_STRU * TTF_MNTN_ErrlogGetCommInfoBuffAddrForGUL(VOS_UINT32 ulPid)
{
    MODEM_ID_ENUM_UINT16        enModemId       = VOS_GetModemIDFromPid(ulPid);
    GTTF_UL_INFO_STRU          *pstGttfULInfo;

    if (enModemId >= MODEM_ID_BUTT)
    {
        TTF_LOG1(ulPid, 0, PS_PRINT_WARNING,
                "TTF_MNTN_ErrlogGetCommInfoBuffAddrForGUL: Invalid ModemId ", enModemId);
        enModemId = MODEM_ID_0;
    }

    if (VOS_NULL_PTR == TTF_ERR_LOG_ENT_GSM_COMM_INFO_GET(enModemId))
    {
        TTF_LOG1(ulPid, 0, PS_PRINT_WARNING,
                "TTF_MNTN_ErrlogGetCommInfoBuffAddrForGUL: No Mem ", enModemId);

        return VOS_NULL_PTR;
    }

    pstGttfULInfo = &(TTF_ERR_LOG_ENT_GSM_COMM_INFO_GET(enModemId)->astGttfUlInfo[TTF_ERR_LOG_ENT_GSM_COMM_INFO_GET(enModemId)->ucGUlIndex]);
    pstGttfULInfo->ulSlice = mdrv_timer_get_normal_timestamp();

    TTF_ERR_LOG_COMM_COUNTER_INCR(TTF_ERR_LOG_ENT_GSM_COMM_INFO_GET(enModemId)->ucGUlIndex, TTF_ERR_LOG_COMM_INFO_CNT);

    return pstGttfULInfo;
}

/*****************************************************************************
 函 数 名  : TTF_MNTN_ErrlogGetCommInfoBuffAddrForGDL
 功能描述  : 获取记录G下行信息结构体指针
 输入参数  : ulPid
 输出参数  : 无
 返 回 值  : GTTF_DL_INFO_STRU *
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月5日
    作    者   : g00178567
    修改内容   : 新生成函数

*****************************************************************************/
GTTF_DL_INFO_STRU * TTF_MNTN_ErrlogGetCommInfoBuffAddrForGDL(VOS_UINT32 ulPid)
{
    MODEM_ID_ENUM_UINT16        enModemId       = VOS_GetModemIDFromPid(ulPid);
    GTTF_DL_INFO_STRU          *pstGttfDLInfo;

    if (enModemId >= MODEM_ID_BUTT)
    {
        TTF_LOG1(ulPid, 0, PS_PRINT_WARNING,
                "TTF_MNTN_ErrlogGetCommInfoBuffAddrForGDL: Invalid ModemId ", enModemId);
        enModemId = MODEM_ID_0;
    }

    if (VOS_NULL_PTR == TTF_ERR_LOG_ENT_GSM_COMM_INFO_GET(enModemId))
    {
        TTF_LOG1(ulPid, 0, PS_PRINT_WARNING,
                "TTF_MNTN_ErrlogGetCommInfoBuffAddrForGDL: No Mem ", enModemId);

        return VOS_NULL_PTR;
    }

    pstGttfDLInfo = &(TTF_ERR_LOG_ENT_GSM_COMM_INFO_GET(enModemId)->astGttfDlInfo[TTF_ERR_LOG_ENT_GSM_COMM_INFO_GET(enModemId)->ucGDlIndex]);
    pstGttfDLInfo->ulSlice = mdrv_timer_get_normal_timestamp();

    TTF_ERR_LOG_COMM_COUNTER_INCR(TTF_ERR_LOG_ENT_GSM_COMM_INFO_GET(enModemId)->ucGDlIndex, TTF_ERR_LOG_COMM_INFO_CNT);

    return pstGttfDLInfo;
}

/*****************************************************************************
 函 数 名  : TTF_MNTN_ErrlogGetCommInfoBuffAddrForWUL
 功能描述  : 获取记录W上行信息结构体指针
 输入参数  : 无
 输出参数  : 无
 返 回 值  : WTTF_MAC_UL_INFO_STRU *
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月5日
    作    者   : g00178567
    修改内容   : 新生成函数

*****************************************************************************/
WTTF_MAC_UL_INFO_STRU * TTF_MNTN_ErrlogGetCommInfoBuffAddrForWUL(VOS_UINT32 ulPid)
{
    MODEM_ID_ENUM_UINT16            enModemId       = VOS_GetModemIDFromPid(ulPid);
    WTTF_MAC_UL_INFO_STRU          *pstWttfULInfo;

    if (enModemId >= MODEM_ID_BUTT)
    {
        TTF_LOG1(ulPid, 0, PS_PRINT_WARNING,
                "TTF_MNTN_ErrlogGetCommInfoBuffAddrForGUL: Invalid ModemId ", enModemId);
        enModemId = MODEM_ID_0;
    }

    if (VOS_NULL_PTR == TTF_ERR_LOG_ENT_WCDMA_COMM_INFO_GET(enModemId))
    {
        TTF_LOG1(ulPid, 0, PS_PRINT_WARNING,
                "TTF_MNTN_ErrlogGetCommInfoBuffAddrForWUL: No Mem ", enModemId);

        return VOS_NULL_PTR;
    }

    pstWttfULInfo = &(TTF_ERR_LOG_ENT_WCDMA_COMM_INFO_GET(enModemId)->astWttfMacUlInfo[TTF_ERR_LOG_ENT_WCDMA_COMM_INFO_GET(enModemId)->ucWMacUlIndex]);
    pstWttfULInfo->ulSlice = mdrv_timer_get_normal_timestamp();

    TTF_ERR_LOG_COMM_COUNTER_INCR(TTF_ERR_LOG_ENT_WCDMA_COMM_INFO_GET(enModemId)->ucWMacUlIndex, TTF_ERR_LOG_COMM_INFO_CNT);

    return pstWttfULInfo;
}

/*****************************************************************************
 函 数 名  : TTF_MNTN_ErrlogGetCommInfoBuffAddrForWUlSched
 功能描述  : 获取记录WUPA信息结构体指针
 输入参数  : 无
 输出参数  : 无
 返 回 值  : WTTF_UL_SCHED_INFO_STRU *
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月5日
    作    者   : g00178567
    修改内容   : 新生成函数

*****************************************************************************/
WTTF_UL_SCHED_INFO_STRU * TTF_MNTN_ErrlogGetCommInfoBuffAddrForWUlSched(VOS_UINT32 ulPid)
{
    MODEM_ID_ENUM_UINT16                enModemId       = VOS_GetModemIDFromPid(ulPid);
    WTTF_UL_SCHED_INFO_STRU            *pstWttfUlSchedInfo;

    if (enModemId >= MODEM_ID_BUTT)
    {
        TTF_LOG1(ulPid, 0, PS_PRINT_WARNING,
                "TTF_MNTN_ErrlogGetCommInfoBuffAddrForGUL: Invalid ModemId ", enModemId);
        enModemId = MODEM_ID_0;
    }

    if (VOS_NULL_PTR == TTF_ERR_LOG_ENT_WCDMA_COMM_INFO_GET(enModemId))
    {
        TTF_LOG1(ulPid, 0, PS_PRINT_WARNING,
                "TTF_MNTN_ErrlogGetCommInfoBuffAddrForWUlSched: No Mem ", enModemId);

        return VOS_NULL_PTR;
    }

    pstWttfUlSchedInfo = &(TTF_ERR_LOG_ENT_WCDMA_COMM_INFO_GET(enModemId)->astWttfUlSchedInfo[TTF_ERR_LOG_ENT_WCDMA_COMM_INFO_GET(enModemId)->ucWUlSchedIndex]);
    pstWttfUlSchedInfo->ulSlice = mdrv_timer_get_normal_timestamp();

    return pstWttfUlSchedInfo;
}

/*****************************************************************************
 函 数 名  : TTF_MNTN_ErrlogGetCommInfoBuffAddrForWDL
 功能描述  : 获取记录W下行信息结构体指针
 输入参数  : 无
 输出参数  : 无
 返 回 值  : WTTF_MAC_DL_INFO_STRU *
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月5日
    作    者   : g00178567
    修改内容   : 新生成函数

*****************************************************************************/
WTTF_MAC_DL_INFO_STRU * TTF_MNTN_ErrlogGetCommInfoBuffAddrForWDL(VOS_UINT32 ulPid)
{
    MODEM_ID_ENUM_UINT16            enModemId       = VOS_GetModemIDFromPid(ulPid);
    WTTF_MAC_DL_INFO_STRU          *pstWttfDLInfo;

    if (enModemId >= MODEM_ID_BUTT)
    {
        TTF_LOG1(ulPid, 0, PS_PRINT_WARNING,
                "TTF_MNTN_ErrlogGetCommInfoBuffAddrForGUL: Invalid ModemId ", enModemId);
        enModemId = MODEM_ID_0;
    }

    if (VOS_NULL_PTR == TTF_ERR_LOG_ENT_WCDMA_COMM_INFO_GET(enModemId))
    {
        TTF_LOG1(ulPid, 0, PS_PRINT_WARNING,
                "TTF_MNTN_ErrlogGetCommInfoBuffAddrForWDL: No Mem ", enModemId);

        return VOS_NULL_PTR;
    }

    pstWttfDLInfo = &(TTF_ERR_LOG_ENT_WCDMA_COMM_INFO_GET(enModemId)->astWttfMacDlInfo[TTF_ERR_LOG_ENT_WCDMA_COMM_INFO_GET(enModemId)->ucWMacDlIndex]);
    pstWttfDLInfo->ulSlice = mdrv_timer_get_normal_timestamp();

    TTF_ERR_LOG_COMM_COUNTER_INCR(TTF_ERR_LOG_ENT_WCDMA_COMM_INFO_GET(enModemId)->ucWMacDlIndex, TTF_ERR_LOG_COMM_INFO_CNT);

    return pstWttfDLInfo;
}

/*****************************************************************************
 函 数 名  : TTF_MNTN_ErrlogGetWcdmaCommInfo
 功能描述  : 获取记录W Comm信息结构体指针
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TTF_MNTN_WCDMA_COMM_INFO_STRU *
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月5日
    作    者   : g00178567
    修改内容   : 新生成函数

*****************************************************************************/
TTF_MNTN_WCDMA_COMM_INFO_STRU * TTF_MNTN_ErrlogGetWcdmaCommInfo(VOS_UINT32 ulPid)
{
    MODEM_ID_ENUM_UINT16            enModemId       = VOS_GetModemIDFromPid(ulPid);

    if (enModemId >= MODEM_ID_BUTT)
    {
        TTF_LOG1(ulPid, 0, PS_PRINT_WARNING,
                "TTF_MNTN_ErrlogGetWcdmaCommInfo: Invalid ModemId ", enModemId);
        enModemId = MODEM_ID_0;
    }

    return TTF_ERR_LOG_ENT_WCDMA_COMM_INFO_GET(enModemId);
}

/*****************************************************************************
 函 数 名  : TTF_MNTN_ErrlogGetGsmCommInfo
 功能描述  : 获取记录W Comm信息结构体指针
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TTF_MNTN_GSM_COMM_INFO_STRU *
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月5日
    作    者   : g00178567
    修改内容   : 新生成函数

*****************************************************************************/
TTF_MNTN_GSM_COMM_INFO_STRU * TTF_MNTN_ErrlogGetGsmCommInfo(VOS_UINT32 ulPid)
{
    MODEM_ID_ENUM_UINT16            enModemId       = VOS_GetModemIDFromPid(ulPid);

    if (enModemId >= MODEM_ID_BUTT)
    {
        TTF_LOG1(ulPid, 0, PS_PRINT_WARNING,
                "TTF_MNTN_ErrlogGetGsmCommInfo: Invalid ModemId ", enModemId);
        enModemId = MODEM_ID_0;
    }

    return TTF_ERR_LOG_ENT_GSM_COMM_INFO_GET(enModemId);
}


/*****************************************************************************
 函 数 名  : TTF_MNTN_ErrlogShow
 功能描述  : Errlog Debug 打印
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月5日
    作    者   : t00148005
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TTF_MNTN_ErrlogShow(VOS_VOID)
{
    VOS_UINT32                      ulIndx;

    for(ulIndx = 0; ulIndx < MODEM_ID_BUTT; ulIndx++)
    {
        (VOS_VOID)vos_printf("\r\n******************MODEM ID %u*************************\r\n", ulIndx);

        if (VOS_NO == TTF_ERR_LOG_ENT_STATE_GET(ulIndx))
        {
            (VOS_VOID)vos_printf("Errlog 实体不存在!                %u \r\n");
            continue;
        }

        (VOS_VOID)vos_printf("Errlog Modem %d 开关状态:             %u \r\n", ulIndx, TTF_ERR_LOG_ENT_CTRL_STATUS_GET(ulIndx));
        (VOS_VOID)vos_printf("Errlog Modem %d 当前上报级别:         %u \r\n", ulIndx, TTF_ERR_LOG_ENT_CTRL_LEV_GET(ulIndx));
        (VOS_VOID)vos_printf("Errlog Modem %d RingBuff Mem Addr:    0x%x \r\n", ulIndx, TTF_ERR_LOG_ENT_BUF_GET(ulIndx));
        (VOS_VOID)vos_printf("Errlog Modem %d RingBuff ID:          0x%x \r\n", ulIndx, TTF_ERR_LOG_ENT_RINGID_GET(ulIndx));
        (VOS_VOID)vos_printf("Errlog Modem %d SemId:                0x%x \r\n", ulIndx, TTF_ERR_LOG_ENT_SEM_GET(ulIndx));
        (VOS_VOID)vos_printf("Errlog Modem %d Buffer保留长度:       %u \r\n", ulIndx, TTF_ERR_LOG_ENT_GET_BUF_RSV_LEN(ulIndx));
        (VOS_VOID)vos_printf("Errlog Modem %d Buffer中的数据长度:   %u \r\n", ulIndx, OM_RingBufferNBytes(TTF_ERR_LOG_ENT_RINGID_GET(ulIndx)));
        (VOS_VOID)vos_printf("Errlog Modem %d W Comm Addr:          0x%x \r\n", ulIndx, TTF_ERR_LOG_ENT_WCDMA_COMM_INFO_GET(ulIndx));
        (VOS_VOID)vos_printf("Errlog Modem %d G Comm Addr:          0x%x \r\n", ulIndx, TTF_ERR_LOG_ENT_GSM_COMM_INFO_GET(ulIndx));

        TTF_ERR_LOG_CB_SHOW(ulIndx, MODULE_ID_PDCP);
        TTF_ERR_LOG_CB_SHOW(ulIndx, MODULE_ID_WRM);
        TTF_ERR_LOG_CB_SHOW(ulIndx, MODULE_ID_GRM);
        TTF_ERR_LOG_CB_SHOW(ulIndx, MODULE_ID_LLC);
        TTF_ERR_LOG_CB_SHOW(ulIndx, MODULE_ID_SN);
        TTF_ERR_LOG_CB_SHOW(ulIndx, MODULE_ID_DL);
    }

    return;
}
/*lint -restore */

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

