/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CmmcaMain.c
  版 本 号   : 初稿
  作    者   : l60609
  生成日期   : 2014年01月08日
  最近修改   :
  功能描述   : CMMCA模块消息处理函数对应表及相关公共处理定义
  函数列表   :
  修改历史   :
  1.日    期   : 2014年01月08日
    作    者   : l60609
    修改内容   : 新生成

******************************************************************************/
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "CmmcaMain.h"
#include "CmmcaCtx.h"
#include "CmmcaMeasReselMgmt.h"
#include "CmmcaPktMgmt.h"
#include "CmmcaRegMgmt.h"
#include "CbpaPsInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e767 修改人: l60609; */
#define    THIS_FILE_ID        PS_FILE_ID_CMMCA_MAIN_C
/*lint +e767 修改人: l60609; */

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
#if (FEATURE_ON == FEATURE_CL_INTERWORK)
/* 根据Cmmc码流中Cmd找对应的处理函数 */
const CMMCA_CBPCA_MSG_PROC_STRU         g_astCmmcaMsgProcCbpcaTab[] =
{
    /* Packet Data */
    {ID_CMMCA_MMC_RAT_PDN_TABLE_SETUP_REQ,                  CMMCA_PKT_RcvCmmcSetPdnTabReq},
    {ID_CMMCA_MMC_RAT_DEFAULT_BEARER_REQ,                   CMMCA_PKT_RcvCmmcDefaultBearConnReq},
    {ID_CMMCA_MMC_RAT_BEARER_DISCONNECT_REQ,                CMMCA_PKT_RcvCmmcBearDiscReq},

    /* reg相关消息，发给cmmca */
    {ID_CMMCA_MMC_RAT_RAT_MODE_REQ,                         CMMCA_REG_RcvRatModeReq},
    {ID_CMMCA_MMC_RAT_POWERUP_REQ,                          CMMCA_REG_RcvPowerUpReq},
    {ID_CMMCA_MMC_RAT_POWERDOWN_REQ,                        CMMCA_REG_RcvPowerDownReq},
    {ID_CMMCA_MMC_RAT_MCC_SEARCH_REQ,                       CMMCA_REG_RcvMccSearchReq},
    {ID_CMMCA_MMC_RAT_ACQ_REQ,                              CMMCA_REG_RcvRatAcqReq},
    {ID_CMMCA_MMC_RAT_PS_REG_REQ,                           CMMCA_REG_RcvPsRegReq},
    {ID_CMMCA_MMC_RAT_CELL_INFO_PS_REG_REQ,                 CMMCA_REG_RcvCellInfoPsRegReq},
    {ID_CMMCA_MMC_RAT_NO_SERVICE_REQ,                       CMMCA_REG_RcvNoServiceReq},
    {ID_CMMCA_MMC_RAT_DATACONNECTION_CMD_REQ,               CMMCA_REG_RcvPktDataCmdReq},
    {ID_CMMCA_MMC_RAT_BEARER_DETACH_REQ,                    CMMCA_REG_RcvBearDetachReq},

    /* 鉴权相关消息 */
    {ID_CMMCA_MMC_API_SET_PDN_PCO_AUTH_REQ,                 CMMCA_PKT_RcvCmmcSetPdnPcoAuthReq},

    /* Meas and Resel:直接透传给ERRC或者MMC */
    {ID_CMMCA_MMC_RAT_IRAT_MEAS_IND,                        CMMCA_RcvCmmcMeasReselReq},
    {ID_CMMCA_MMC_RAT_IRAT_SYSTEM_CHG_RSP,                  CMMCA_RcvCmmcSystemChgRsp},
    {ID_CMMCA_MMC_RAT_IRAT_SIB8_MEAS_IND,                   CMMCA_RcvCmmcMeasReselReq},
    {ID_CMMCA_MMC_RAT_RAT_MEAS_CMD,                         CMMCA_RcvCmmcMeasReselReq},
    {ID_CMMCA_MMC_RAT_RAT_RESELMEAS_CMD,                    CMMCA_RcvCmmcMeasReselReq},
    {ID_CMMCA_MMC_RAT_STOP_IRAT_RATMEAS_CMD,                CMMCA_RcvCmmcMeasReselReq},

    {ID_CMMCA_MMC_RAT_IRAT_RESELMEAS_IND,                   CMMCA_RcvCmmcMeasReselReq},
    {ID_CMMCA_MMC_RAT_SET_IDLEMODEMOBILITYINFO,             CMMCA_RcvCmmcMeasReselReq},

    /* 透传给MTC */
    {ID_CMMCA_MMC_RAT_OTHER_RAT_INFO_IND,                   CMMCA_RcvCmmcOtherRatInfoInd},
    {ID_CMMCA_MTC_CONN_STATE_INFO_IND,                      CMMCA_RcvCdmaConnStateInfoInd},     /* 外挂CDMA状态上报 */

    /* 透传给RCM */
    {ID_CMMCA_RCM_TAS_CDMA_MEASUREMENT_IND,                 CMMCA_RcvCdmaMeasurementInfoInd},   /* 外挂CDMA测量上报 */
    {ID_CMMCA_RCM_TAS_CDMA_EVENT_IND,                       CMMCA_RcvCdmaEventInfoInd}         /* 外挂CDMA事件上报 */

};


/* g_astCmmcaMsgProcCbpcaTab的Item个数 */
const VOS_UINT32 g_ulCmmcaMsgProcCbpcaTabSize  = sizeof(g_astCmmcaMsgProcCbpcaTab) / sizeof(g_astCmmcaMsgProcCbpcaTab[0]);


/* 根据TimerId找对应的处理函数 */
const CMMCA_TIMER_MSG_PROC_STRU         g_astCmmcaMsgProcTimerTab[] =
{
    {TI_CMMCA_WAIT_IPV6_RA_INFO,                            CMMCA_PKT_RcvTiWaitIpv6RaExp}
};

/* g_astCmmcaMsgProcTimerTab的Item个数 */
const VOS_UINT32 g_ulCmmcaMsgProcTimerTabSize  = sizeof(g_astCmmcaMsgProcTimerTab) / sizeof(g_astCmmcaMsgProcTimerTab[0]);

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*****************************************************************************
 函 数 名  : CMMCA_RcvCbpcaMsg
 功能描述  : 处理来自WUEPS_PID_CBPCA的消息
 输入参数  : struct MsgCB *pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月9日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CMMCA_RcvCbpcaMsg(struct MsgCB *pstMsg)
{
    /* 定义消息头指针*/
    CBPCA_DATA_IND_MSG_STRU            *pstDataInd = VOS_NULL_PTR;
    CMMCA_MMC_RAT_CMD_DATA_STRU        *pstCmdData = VOS_NULL_PTR;
    CMMCA_CBPCA_MSG_PROC_FUNC           pProcMsgFunc = VOS_NULL_PTR;
    VOS_UINT32                          ulIndex;

    /* 获取消息头指针*/
    pstDataInd = (CBPCA_DATA_IND_MSG_STRU *)pstMsg;

    if (CBPCA_CMMCA_DATA_IND != pstDataInd->enMsgType)
    {
        CMMCA_ERROR_LOG("CMMCA_RcvCbpcaMsg: not data ind");

        return;
    }

    pstCmdData = (CMMCA_MMC_RAT_CMD_DATA_STRU *)(pstDataInd->aucData);

    /* 查表g_astCmmcaMsgProcCbpcaTab找pstCmdData->enCmdId对应的处理函数，参数类型为CMMCA_MMC_RAT_CMD_DATA_STRU */
    for (ulIndex = 0; ulIndex < g_ulCmmcaMsgProcCbpcaTabSize; ulIndex++)
    {
        if (g_astCmmcaMsgProcCbpcaTab[ulIndex].ulCmdId == pstCmdData->enCmdId)
        {
            /* Cmd Id 匹配 */
            pProcMsgFunc = g_astCmmcaMsgProcCbpcaTab[ulIndex].pProcMsgFunc;

            break;
        }
    }

    /* 如果处理函数存在则调用 */
    if ( VOS_NULL_PTR != pProcMsgFunc )
    {
        pProcMsgFunc(pstDataInd);
    }
    else
    {
        CMMCA_ERROR_LOG("CMMCA_RcvCbpcaMsg: proc msg func is null");
    }

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_RcvTafMsg
 功能描述  : 处理来自WUEPS_PID_TAF的消息
 输入参数  : struct MsgCB *pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月9日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CMMCA_RcvTafMsg(struct MsgCB *pstMsg)
{
    /* 定义消息头指针*/
    MSG_HEADER_STRU                     *pstHeader = VOS_NULL_PTR;

    /* 获取消息头指针*/
    pstHeader = (MSG_HEADER_STRU *)pstMsg;

    /* APS消息 */
    if(MN_CALLBACK_PS_CALL == pstHeader->ulMsgName)
    {
        CMMCA_PKT_RcvTafPsEvt((TAF_PS_EVT_STRU*)pstMsg);
    }

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_RcvErrcMsg
 功能描述  : 处理来自PS_PID_ERRC的消息
 输入参数  : struct MsgCB *pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月9日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CMMCA_RcvErrcMsg(struct MsgCB *pstMsg)
{
    LRRC_CMMCA_CDMA_MSG_IRAT_MEAS_REQ_STRU  *pstIratMeasReq = VOS_NULL_PTR;
    CMMCA_MMC_RAT_CMD_ID_ENUM_UINT16         enCmdIdFromMsgId;
    CMMCA_MMC_RAT_CMD_ID_ENUM_UINT16         enCmdIdInData;
    VOS_UINT32                               ulRslt;

    enCmdIdFromMsgId = ID_CMMCA_RAT_MMC_CMD_MAX;

    /* ERRC回复给CMMCA的消息pstMsg,其结构体为LRRC_CMMCA_CDMA_MSG_IRAT_MEAS_REQ_STRU */
    pstIratMeasReq         = (LRRC_CMMCA_CDMA_MSG_IRAT_MEAS_REQ_STRU *)pstMsg;

    ulRslt = CMMCA_GetCmdIdFromErrcMsgId(pstIratMeasReq->enMsgId, &enCmdIdFromMsgId);

    if (VOS_OK != ulRslt)
    {
        CMMCA_ERROR_LOG("CMMCA_RcvErrcMsg: Not find Cmd Id ");
        return;
    }

    enCmdIdInData = *((CMMCA_MMC_RAT_CMD_ID_ENUM_UINT16 *)(pstIratMeasReq->aucMsgData));

    /* 检查根据MsgId计算出来的CmdId跟Errc实际传来的CmdId是否一致 */
    if (enCmdIdFromMsgId != enCmdIdInData)
    {
        CMMCA_ERROR_LOG("CMMCA_RcvErrcMsg: MsgId and CmdId don't match ");
        return;
    }

    /* 调用CBPCA模块接口将数据发送到CBPCA */
    ulRslt = CBPCA_SndDataToCbpca(WUEPS_PID_CMMCA,
                                  CMMCA_CBPCA_DATA_REQ,
                                  (VOS_UINT8 *)(pstIratMeasReq->aucMsgData),
                                  pstIratMeasReq->ulLen);

    if (VOS_OK != ulRslt)
    {
        CMMCA_ERROR_LOG("CMMCA_RcvErrcMsg: send Msg to Cbpca fail");
    }

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_RcvTimerMsg
 功能描述  : 处理来自VOS_PID_TIMER的消息
 输入参数  : struct MsgCB *pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月24日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CMMCA_RcvTimerMsg(struct MsgCB *pstMsg)
{
    /* 定义消息头指针*/
    REL_TIMER_MSG                      *pstTiMsg = VOS_NULL_PTR;
    CMMCA_TIMER_MSG_PROC_FUNC           pProcMsgFunc = VOS_NULL_PTR;
    VOS_UINT32                          ulIndex;

    /* 获取消息头指针*/
    pstTiMsg = (REL_TIMER_MSG *)pstMsg;

    /* 停止定时器 */
    CMMCA_StopTimer(WUEPS_PID_CMMCA, pstTiMsg->ulName);

    /* 查表g_astCmmcaMsgProcTimerTab */
    for (ulIndex = 0; ulIndex < g_ulCmmcaMsgProcTimerTabSize; ulIndex++)
    {
        if (g_astCmmcaMsgProcTimerTab[ulIndex].enTimerId == pstTiMsg->ulName)
        {
            /* Timer Id 匹配 */
            pProcMsgFunc = g_astCmmcaMsgProcTimerTab[ulIndex].pProcMsgFunc;

            break;
        }
    }

    /* 如果处理函数存在则调用 */
    if ( VOS_NULL_PTR != pProcMsgFunc )
    {
        pProcMsgFunc(pstTiMsg);
    }
    else
    {
        CMMCA_ERROR_LOG("CMMCA_RcvTimerMsg: proc msg func is null");
    }


    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_ProcMsg
 功能描述  : CMMCA模块的消息入口函数
 输入参数  : MsgBlock* pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月9日
    作    者   : l60609
    修改内容   : 新生成函数
  2.日    期   : 2014年10月27日
    作    者   : j00174725
    修改内容   : CMMCA可维可测
*****************************************************************************/
VOS_VOID CMMCA_ProcMsg(MsgBlock* pMsg)
{
    MSG_HEADER_STRU                    *pstMsgHeader;

    if (VOS_NULL_PTR == pMsg)
    {
        return;
    }

    pstMsgHeader = (MSG_HEADER_STRU*)pMsg;
    CMMCA_DEBUG_RecordMsgInfo(pMsg->ulSenderPid, pstMsgHeader->ulMsgName);

    switch (pMsg->ulSenderPid)
    {
        case WUEPS_PID_CBPCA:
            CMMCA_RcvCbpcaMsg(pMsg);
            break;

        case WUEPS_PID_TAF:
            CMMCA_RcvTafMsg(pMsg);
            break;

        case PS_PID_ERRC:
            CMMCA_RcvErrcMsg(pMsg);
            break;

        case VOS_PID_TIMER:
            CMMCA_RcvTimerMsg(pMsg);
            break;

        case WUEPS_PID_MMA:
            CMMCA_REG_RcvMmaMsg(pMsg);
            break;
        default:
            CMMCA_WARNING_LOG("CMMCA_PidMsgProc: Abnormal PID.");
            break;

    }

    return;
}

#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif





