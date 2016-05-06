/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CmmcaMeasResel.c
  版 本 号   : 初稿
  作    者   : l60609
  生成日期   : 2014年01月08日
  最近修改   :
  功能描述   : CMMCA模块测量重选相关的处理
  函数列表   :
  修改历史   :
  1.日    期   : 2014年01月08日
    作    者   : l60609
    修改内容   : 新生成

******************************************************************************/
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "CmmcaCtx.h"
#include "CmmcaMeasReselMgmt.h"

#include "CbpaPsInterface.h"

#include "CmmcaRcmInterface.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e767 修改人: l60609; */
#define    THIS_FILE_ID        PS_FILE_ID_CMMCA_MEAS_RESEL_MGMT_C
/*lint +e767 修改人: l60609; */

#if (FEATURE_ON == FEATURE_CL_INTERWORK)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/* 维护CMDID与MSGID(ERRC->CMMCA)之间的映射表 */
const CMMCA_CMDID_ERRC_MSGID_MAP_STRU   g_astCmmcaCmdIdToErrcMsgIdMapTbl[] =
{
    {ID_CMMCA_MMC_RAT_IRAT_MEAS_IND,                 CMMCA_LRRC_CDMA_MSG_IRAT_MEAS_IND},
    {ID_CMMCA_MMC_RAT_IRAT_SYSTEM_CHG_RSP,           CMMCA_LRRC_CDMA_MSG_IRAT_SYSTEM_CHG_RSP},
    {ID_CMMCA_MMC_RAT_IRAT_SIB8_MEAS_IND,            CMMCA_LRRC_CDMA_MSG_IRAT_SIB8_MEAS_IND},
    {ID_CMMCA_MMC_RAT_RAT_MEAS_CMD,                  CMMCA_LRRC_CDMA_MSG_IRAT_SET_PRIINFO_REQ},
    {ID_CMMCA_MMC_RAT_RAT_RESELMEAS_CMD,             CMMCA_LRRC_CDMA_MSG_IRAT_LTEMEAS_REQ},
    {ID_CMMCA_MMC_RAT_STOP_IRAT_RATMEAS_CMD,         CMMCA_LRRC_CDMA_MSG_STOP_IRAT_RATMEAS_REQ},

    {ID_CMMCA_RAT_MMC_IRAT_MEAS_CMD,                 LRRC_CMMCA_CDMA_MSG_IRAT_MEAS_REQ},
    {ID_CMMCA_RAT_MMC_IRAT_SYSTEM_CHG_REQ,           LRRC_CMMCA_CDMA_MSG_IRAT_SYSTEM_CHG_REQ},
    {ID_CMMCA_RAT_MMC_IRAT_SIB8_MEAS_CMD,            LRRC_CMMCA_CDMA_MSG_IRAT_SIB8_MEAS_IND},
    {ID_CMMCA_RAT_MMC_RAT_MEAS_IND,                  LRRC_CMMCA_CDMA_MSG_IRAT_SET_PRIINFO_REQ},
    {ID_CMMCA_RAT_MMC_RAT_RESELMEAS_IND,             LRRC_CMMCA_CDMA_MSG_IRAT_RATMEAS_IND},
    {ID_CMMCA_RAT_MMC_STOP_IRAT_MEAS_CMD,            LRRC_CMMCA_CDMA_MSG_STOP_IRAT_MEAS_REQ},
    {ID_CMMCA_RAT_MMC_SYSTEM_CHG_ABORT_REQ,          LRRC_CMMCA_CDMA_MSG_IRAT_SYSTEM_CHG_ABORT_CMD}

};

/* g_astCmmcaCmdIdToErrcMsgIdMapTbl的Item个数 */
const VOS_UINT32 g_ulCmmcaCmdIdToErrcMsgIdMapTblSize  = sizeof(g_astCmmcaCmdIdToErrcMsgIdMapTbl) / sizeof(g_astCmmcaCmdIdToErrcMsgIdMapTbl[0]);

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*****************************************************************************
 函 数 名  : CMMCA_SndMmcResumeInd
 功能描述  : 处理CMMC发过来的System change rsp消息，发给Mmc
 输入参数  : CBPCA_DATA_IND_MSG_STRU            *pstDataInd
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年02月08日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CMMCA_SndMmcResumeInd(
    CBPCA_DATA_IND_MSG_STRU            *pstDataInd
)
{
    CMMCA_MMC_RESUME_IND_STRU              *pstResumeInd = VOS_NULL_PTR;
    VOS_UINT32                              ulMsgLen;

    ulMsgLen = sizeof(CMMCA_MMC_RESUME_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstResumeInd = (CMMCA_MMC_RESUME_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_CMMCA, ulMsgLen);
    if (VOS_NULL_PTR == pstResumeInd)
    {
        CMMCA_ERROR_LOG("CMMCA_SndMmcResumeInd: Alloc msg fail!");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstResumeInd + VOS_MSG_HEAD_LENGTH,0,
                             sizeof(CMMCA_MMC_RESUME_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 发送消息给Mmc */
    pstResumeInd->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstResumeInd->ulReceiverPid   = WUEPS_PID_MMC;
    pstResumeInd->enMsgId         = ID_CMMCA_MMC_RESUME_IND;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_CMMCA, pstResumeInd))
    {
        CMMCA_ERROR_LOG("CMMCA_SndMmcResumeInd: Send msg to mmc fail!");
    }

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_RcvCmmcMeasReselReq
 功能描述  : 处理CMMC发过来的meas和resel相关的消息，内容不做解析，直接发给LRRC
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月9日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CMMCA_RcvCmmcMeasReselReq(VOS_VOID *pMsg)
{
    CBPCA_DATA_IND_MSG_STRU                *pstDataInd = VOS_NULL_PTR;
    CMMCA_MMC_RAT_CMD_DATA_STRU            *pstCmdData = VOS_NULL_PTR;
    CMMCA_LRRC_CDMA_MSG_IRAT_MEAS_IND_STRU *pstLrrcMsgInd = VOS_NULL_PTR;
    CMMCA_MMC_RAT_CMD_ID_ENUM_UINT16        enCmdId;
    LRRC_CMMCA_MSG_TYPE_ENUM_UINT32         enMsgId;
    VOS_UINT32                              ulMsgLen;
    VOS_UINT8                               ucIndex;

    pstDataInd = (CBPCA_DATA_IND_MSG_STRU *)pMsg;

    /* 解析出码流中的CmdId */
    pstCmdData = (CMMCA_MMC_RAT_CMD_DATA_STRU *)(pstDataInd->aucData);
    enCmdId    = *((CMMCA_MMC_RAT_CMD_ID_ENUM_UINT16 *)pstCmdData);

    enMsgId = LRRC_CMMCA_MSG_TYPE_BUTT;
    /* 根据解析出的中的CmdId，查表g_astCmmcaCmdIdToErrcMsgIdMapTbl，匹配相应的MsgId */
    for (ucIndex = 0; ucIndex < g_ulCmmcaCmdIdToErrcMsgIdMapTblSize; ucIndex++)
    {
        if (g_astCmmcaCmdIdToErrcMsgIdMapTbl[ucIndex].enCmdId == enCmdId)
        {
            enMsgId = g_astCmmcaCmdIdToErrcMsgIdMapTbl[ucIndex].enMsgId;
            break;
        }
    }

    if (ucIndex >= g_ulCmmcaCmdIdToErrcMsgIdMapTblSize)
    {
        CMMCA_ERROR_LOG("CMMCA_RcvCmmcMeasReselReq: Find CmdId fail!");
        return;
    }

    /* 构造发送给Errc的消息结构 */
    ulMsgLen = sizeof(CMMCA_LRRC_CDMA_MSG_IRAT_MEAS_IND_STRU) - CMMCA_MSG_DATA_RSV_LEN + pstDataInd->ulDataLen - VOS_MSG_HEAD_LENGTH;

    pstLrrcMsgInd = (CMMCA_LRRC_CDMA_MSG_IRAT_MEAS_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_CMMCA, ulMsgLen);

    if (VOS_NULL_PTR == pstLrrcMsgInd)
    {
        CMMCA_ERROR_LOG("CMMCA_RcvCmmcMeasReselReq: Alloc msg fail!");
        return;
    }

    /* 发送消息给LRRC */
    pstLrrcMsgInd->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstLrrcMsgInd->ulReceiverPid   = PS_PID_ERRC;
    pstLrrcMsgInd->enMsgId         = enMsgId;
    pstLrrcMsgInd->ulLen           = pstDataInd->ulDataLen;
    VOS_MemCpy(pstLrrcMsgInd->aucMsgData, pstDataInd->aucData, pstLrrcMsgInd->ulLen);

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_CMMCA, pstLrrcMsgInd))
    {
        CMMCA_ERROR_LOG("CMMCA_RcvCmmcMeasReselReq: Send msg to Lrrc fail!");
        return;
    }

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_RcvCmmcSystemChgRsp
 功能描述  : 处理CMMC发过来的system chg rsp消息，透传给LRRC，如果system change回复成功消息，则发送至MMC
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年03月11日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CMMCA_RcvCmmcSystemChgRsp(VOS_VOID *pMsg)
{
    CBPCA_DATA_IND_MSG_STRU                *pstDataInd = VOS_NULL_PTR;
    CMMCA_LRRC_CDMA_MSG_IRAT_MEAS_IND_STRU *pstLrrcMsgInd = VOS_NULL_PTR;
    VOS_UINT32                              ulMsgLen;
    VOS_UINT32                              ulRslt;
    CMMCA_MMC_RAT_IRAT_SYSTEM_CHG_RSP_STRU  stSystemChgInd;


    VOS_MemSet(&stSystemChgInd, 0, sizeof(CMMCA_MMC_RAT_IRAT_SYSTEM_CHG_RSP_STRU));
    pstDataInd = (CBPCA_DATA_IND_MSG_STRU *)pMsg;

    /* 构造发送给Errc的消息结构 */
    ulMsgLen = sizeof(CMMCA_LRRC_CDMA_MSG_IRAT_MEAS_IND_STRU) - CMMCA_MSG_DATA_RSV_LEN + pstDataInd->ulDataLen - VOS_MSG_HEAD_LENGTH;

    pstLrrcMsgInd = (CMMCA_LRRC_CDMA_MSG_IRAT_MEAS_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_CMMCA, ulMsgLen);

    if (VOS_NULL_PTR == pstLrrcMsgInd)
    {
        CMMCA_ERROR_LOG("CMMCA_RcvCmmcSystemChgRsp: Alloc msg fail!");
        return;
    }

    /* 发送消息给LRRC */
    pstLrrcMsgInd->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstLrrcMsgInd->ulReceiverPid   = PS_PID_ERRC;
    pstLrrcMsgInd->enMsgId         = CMMCA_LRRC_CDMA_MSG_IRAT_SYSTEM_CHG_RSP;
    pstLrrcMsgInd->ulLen           = pstDataInd->ulDataLen;
    VOS_MemCpy(pstLrrcMsgInd->aucMsgData, pstDataInd->aucData, pstLrrcMsgInd->ulLen);

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_CMMCA, pstLrrcMsgInd))
    {
        CMMCA_ERROR_LOG("CMMCA_RcvCmmcSystemChgRsp: Send msg to Lrrc fail!");
        return;
    }

    /* 调用解析函数将CMD码流解析成对应的数据结构 */
    ulRslt = CMMCA_ParseSystemChangeRsp((VOS_UINT16)(pstDataInd->ulDataLen),
                                        pstDataInd->aucData,
                                        &stSystemChgInd);

    if (VOS_OK != ulRslt)
    {
        CMMCA_ERROR_LOG("CMMCA_RcvCmmcSystemChgRsp: Parse System change rsp fail!");
        return;
    }

    /* 如果system change回复成功消息，则发送至Mmc */
    if  ((CMMCA_IRAT_SYSTEM_CHG_SUCCESS      == stSystemChgInd.enResult)
       ||(CMMCA_IRAT_SYSTEM_CHG_HRPD_SUCCESS == stSystemChgInd.enResult))
    {
        /* 设置Modem的状态为INACTIVE */
        CMMCA_SetModemStatus(CMMCA_MODEM_STATUS_INACTIVE);

        CMMCA_SndMmcResumeInd(pstDataInd);
    }

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_GetCmdIdFromErrcMsgId
 功能描述  : 根据ERRC的MSG ID获取对应的CMD ID
 输入参数  : LRRC_CMMCA_MSG_TYPE_ENUM_UINT32     enMsgId
             CMMCA_MMC_RAT_CMD_ID_ENUM_UINT16   *penCmdId
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月10日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CMMCA_GetCmdIdFromErrcMsgId(
    LRRC_CMMCA_MSG_TYPE_ENUM_UINT32     enMsgId,
    CMMCA_MMC_RAT_CMD_ID_ENUM_UINT16   *penCmdId
)
{
    VOS_UINT8                           ucIndex;

    for (ucIndex = 0; ucIndex < g_ulCmmcaCmdIdToErrcMsgIdMapTblSize; ucIndex++)
    {
        if (g_astCmmcaCmdIdToErrcMsgIdMapTbl[ucIndex].enMsgId == enMsgId)
        {
            *penCmdId = g_astCmmcaCmdIdToErrcMsgIdMapTbl[ucIndex].enCmdId;
            return VOS_OK;
        }
    }

    return VOS_ERR;
}

/*****************************************************************************
 函 数 名  : CMMCA_RcvCmmcOtherRatInfoInd
 功能描述  : 处理CMMC发过来的另外一个RAT的信息，对消息进行解析，发送至MTC
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月24日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CMMCA_RcvCmmcOtherRatInfoInd(VOS_VOID *pMsg)
{
    CBPCA_DATA_IND_MSG_STRU            *pstDataInd = VOS_NULL_PTR;
    CMMCA_MTC_OTHER_RAT_INFO_IND_STRU  *pstOtherRatInfoInd = VOS_NULL_PTR;
    CMMCA_OTHER_RAT_INFO_IND_STRU       stOtherRatInfoInd;
    VOS_UINT32                          ulRslt;
    VOS_UINT32                          ulMsgLen;

    pstDataInd = (CBPCA_DATA_IND_MSG_STRU *)pMsg;

    PS_MEM_SET(&stOtherRatInfoInd, 0, sizeof(CMMCA_OTHER_RAT_INFO_IND_STRU));

    /* 调用CMMCA_ParseOtherRatInfoInd函数对参数进行解析 */
    ulRslt = CMMCA_ParseOtherRatInfoInd((VOS_UINT16)(pstDataInd->ulDataLen),
                                    pstDataInd->aucData,
                                    &stOtherRatInfoInd);

    if (VOS_OK != ulRslt)
    {
        CMMCA_ERROR_LOG("CMMCA_RcvCmmcOtherRatInfoReq: Parse Other Rat Info fail!");
        return;
    }

    /* 构造发送给MTC的消息结构 */
    ulMsgLen = sizeof(CMMCA_MTC_OTHER_RAT_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstOtherRatInfoInd = (CMMCA_MTC_OTHER_RAT_INFO_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_CMMCA, ulMsgLen);

    if (VOS_NULL_PTR == pstOtherRatInfoInd)
    {
        CMMCA_ERROR_LOG("CMMCA_RcvCmmcOtherRatInfoReq: Alloc msg fail!");
        return;
    }

    /* 发送消息给MTC */
    pstOtherRatInfoInd->ulReceiverPid = UEPS_PID_MTC;
    pstOtherRatInfoInd->enMsgId = ID_CMMCA_MTC_OTHER_RAT_INFO_IND;
    PS_MEM_CPY(&(pstOtherRatInfoInd->stOtherRatInfo), &stOtherRatInfoInd, sizeof(CMMCA_OTHER_RAT_INFO_IND_STRU));

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_CMMCA, pstOtherRatInfoInd))
    {
        CMMCA_ERROR_LOG("CMMCA_RcvCmmcOtherRatInfoReq: Send msg to mtc fail!");
    }

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_RcvCdmaConnStateInfoInd
 功能描述  : 处理外挂CDMA发过来的状态信息，对消息进行解析，转发送至MTC
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年09月29日
    作    者   : j00174725
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CMMCA_RcvCdmaConnStateInfoInd(VOS_VOID *pMsg)
{
    CBPCA_DATA_IND_MSG_STRU            *pstDataInd          = VOS_NULL_PTR;
    TAF_CTRL_STRU                       stCtrl;
    TAF_MTC_CDMA_STATE_INFO_STRU        stTafCdmaState;
    VOS_UINT32                          ulRst;
    VOS_UINT8                           ucOpid;

    /* 初始化 */
    PS_MEM_SET(&stTafCdmaState, 0x0, sizeof(stTafCdmaState));
    PS_MEM_SET(&stCtrl, 0x0, sizeof(stCtrl));

    /* 参考VIA接口文档，解析消息 */
    pstDataInd      = (CBPCA_DATA_IND_MSG_STRU *)pMsg;

    /* 做参数检查和转换 */
    ulRst = CMMCA_ParseStateInfo((VOS_UINT16)(pstDataInd->ulDataLen),
                                 pstDataInd->aucData,
                                 &stTafCdmaState);
    if (VOS_OK != ulRst)
    {
        CMMCA_ERROR_LOG("CMMCA_RcvCdmaConnStateInfoInd: Parse Fail!");
        return;
    }

    /* 申请OPID */
    ucOpid = 0x0;
    CMMCA_AssignOpid(&ucOpid);

    /* 填写消息控制部分 */
    TAF_API_CTRL_HEADER(&stCtrl, WUEPS_PID_CMMCA, CMMCA_CLIENT_ID, ucOpid);

    /* 调用MTC消息发送接口 */
    ulRst = MTC_SetCdmaServiceConnStateInfo(&stCtrl, &stTafCdmaState);
    if (VOS_OK != ulRst)
    {
        CMMCA_ERROR_LOG("CMMCA_RcvCdmaConnStateInfoInd: Send msg to mtc fail!");
    }

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_RcvCdmaMeasurementInfoInd
 功能描述  : 处理外挂CDMA发过来的测量消息，转发到rcm模块
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年09月29日
    作    者   : j00174725
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CMMCA_RcvCdmaMeasurementInfoInd(VOS_VOID *pMsg)
{
    CBPCA_DATA_IND_MSG_STRU                *pstDataInd              = VOS_NULL_PTR;
    CMMCA_RCM_MEASUREMENT_INFO_IND_STRU    *pstMeasurementInfoInd   = VOS_NULL_PTR;
    VOS_UINT8                              *pucTmpPtr               = VOS_NULL_PTR;
    CMMCA_RCM_MEASUREMENT_INFO_STRU         stMeasureMentInfo;
    VOS_UINT32                              ulRslt;

    /* 初始化 */
    PS_MEM_SET(&stMeasureMentInfo, 0x0, sizeof(stMeasureMentInfo));
    pstDataInd = (CBPCA_DATA_IND_MSG_STRU *)pMsg;

    /* 码流解析 */
    ulRslt = CMMCA_ParseMeasurementInfo((VOS_UINT16)(pstDataInd->ulDataLen),
                                        pstDataInd->aucData,
                                        &stMeasureMentInfo);
    if (VOS_OK != ulRslt)
    {
        CMMCA_ERROR_LOG("CMMCA_RcvCdmaMeasurementInfoInd: Parse Fail!");
        return;
    }

    /* 构造发送给RCM的消息结构 */
    pstMeasurementInfoInd = (CMMCA_RCM_MEASUREMENT_INFO_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_CMMCA, sizeof(CMMCA_RCM_MEASUREMENT_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstMeasurementInfoInd)
    {
        CMMCA_ERROR_LOG("CMMCA_RcvCdmaMeasurementInfoInd: Alloc msg fail!");
        return;
    }

    /* 发送消息给RCM */
    pstMeasurementInfoInd->ulReceiverPid = DSP_PID_RCM;
    pstMeasurementInfoInd->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMeasurementInfoInd->enMsgId = ID_CMMCA_RCM_TAS_MEASUREMENT_IND;
    pucTmpPtr = (VOS_UINT8 *)((VOS_UINT32)(&pstMeasurementInfoInd->stMeasurementInfo));
    PS_MEM_CPY(pucTmpPtr, &stMeasureMentInfo, sizeof(CMMCA_RCM_MEASUREMENT_INFO_STRU));

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_CMMCA, pstMeasurementInfoInd))
    {
        CMMCA_ERROR_LOG("CMMCA_RcvCdmaMeasurementInfoInd: Send msg to mtc fail!");
    }

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_RcvCdmaEventInfoInd
 功能描述  : 处理外挂CDMA发过来的事件消息，转发到rcm模块
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年09月29日
    作    者   : j00174725
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CMMCA_RcvCdmaEventInfoInd(VOS_VOID *pMsg)
{
    CBPCA_DATA_IND_MSG_STRU                *pstDataInd        = VOS_NULL_PTR;
    CDMA_TAS_EVENT_DATA_INFO_IND_STRU      *pstEventInfoInd   = VOS_NULL_PTR;
    VOS_UINT8                              *pucTmpPtr         = VOS_NULL_PTR;
    CDMA_TAS_EVENT_INFO_STRU                stEventInfo;
    VOS_UINT32                              ulRslt;

    /* 初始化 */
    PS_MEM_SET(&stEventInfo, 0x0, sizeof(stEventInfo));
    pstDataInd = (CBPCA_DATA_IND_MSG_STRU *)pMsg;

    /* 码流解析 */
    ulRslt = CMMCA_ParseEventInfo((VOS_UINT16)(pstDataInd->ulDataLen),
                                  pstDataInd->aucData,
                                  &stEventInfo);
    if (VOS_OK != ulRslt)
    {
        CMMCA_ERROR_LOG("CMMCA_RcvCdmaEventInfoInd: Parse Fail!");
        return;
    }

    /* 构造发送给RCM的消息结构 */
    pstEventInfoInd = (CDMA_TAS_EVENT_DATA_INFO_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_CMMCA, sizeof(CDMA_TAS_EVENT_DATA_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstEventInfoInd)
    {
        CMMCA_ERROR_LOG("CMMCA_RcvCdmaEventInfoInd: Alloc msg fail!");
        return;
    }

    /* 发送消息给RCM */
    pstEventInfoInd->ulReceiverPid = DSP_PID_RCM;
    pstEventInfoInd->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstEventInfoInd->enMsgId = ID_CMMCA_RCM_TAS_EVENT_IND;
    pucTmpPtr = (VOS_UINT8 *)((VOS_UINT32)(&pstEventInfoInd->stCdmaEventData));
    PS_MEM_CPY(pucTmpPtr, &stEventInfo, sizeof(stEventInfo));

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_CMMCA, pstEventInfoInd))
    {
        CMMCA_ERROR_LOG("CMMCA_RcvCdmaEventInfoInd: Send msg to mtc fail!");
    }

    return;
}


#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif





