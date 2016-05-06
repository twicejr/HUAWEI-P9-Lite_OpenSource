/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafCbaMntn.c
  版 本 号   : 初稿
  作    者   : l00171473
  生成日期   : 2012年3月19日
  最近修改   :
  功能描述   : CBA模块可维可测相关的处理
  函数列表   :
  修改历史   :
  1.日    期   : 2012年3月19日
    作    者   : l00171473
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "TafCbaMntn.h"
#include  "TafLog.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_CBA_MNTN_C

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
  3 函数实现
*****************************************************************************/



/******************************************************************************
函 数 名  : TAF_CBA_SndOmLogInfo
功能描述  : 发送CB模块可维可测事件消息
输入参数  : enEventType: 可维可测事件ID
输出参数  : 无
返 回 值  : VOS_VOID
调用函数  :
被调函数  :

修改历史      :
  1.日    期   : 2012年3月10日
    作    者   : l00171473
    修改内容   : 新生成函数
******************************************************************************/
VOS_VOID TAF_CBA_SndOmLogInfo(
    TAF_CBA_OM_LOG_ID_ENUM_UINT32       enLogId
)
{
    TAF_CBA_MNTN_INFO_STRU              stMsg;

    PS_MEM_SET(&stMsg, 0x00, sizeof(stMsg));

    /* 消息封装 */
    stMsg.ulSenderCpuId       = VOS_LOCAL_CPUID;
    stMsg.ulSenderPid         = WUEPS_PID_TAF;
    stMsg.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    stMsg.ulReceiverPid       = WUEPS_PID_TAF;
    stMsg.ulLength            = sizeof(stMsg) - VOS_MSG_HEAD_LENGTH;

    stMsg.enMsgId             = TAF_CBA_OM_MSG_LOG_INFO;

    stMsg.u.stLogInfo.enLogId = enLogId;

    /* 勾出可维可测信息 */
    DIAG_TraceReport(&stMsg);
}


/******************************************************************************
函 数 名  : TAF_CBA_SndOmDeledRecordInfo
功能描述  : 删除记录的可维可测信息
输入参数  : enType:  可维可测事件ID
            enDelReason: 删除记录的原因
            pstDelRecord: 删除的记录项
输出参数  : 无
返 回 值  : VOS_VOID
调用函数  :
被调函数  :

修改历史      :
  1.日    期   : 2012年3月10日
    作    者   : l00171473
    修改内容   : 新生成函数
******************************************************************************/
VOS_VOID TAF_CBA_SndOmDeledRecordInfo(
    TAF_CBA_OM_MSG_ID_ENUM_UINT32       enType,
    TAF_CBA_OM_DEL_REASON_ENUM_UINT8    enDelReason,
    TAF_CBA_RECORD_STRU                *pstDelRecord
)
{
    TAF_CBA_MNTN_INFO_STRU              stMsg;

    PS_MEM_SET(&stMsg, 0x00, sizeof(stMsg));

    /* 消息封装 */
    stMsg.ulSenderCpuId       = VOS_LOCAL_CPUID;
    stMsg.ulSenderPid         = WUEPS_PID_TAF;
    stMsg.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    stMsg.ulReceiverPid       = WUEPS_PID_TAF;
    stMsg.ulLength            = sizeof(stMsg) - VOS_MSG_HEAD_LENGTH;

    stMsg.enMsgId             = enType;

    /* 构造消息 */
    stMsg.u.stDelRecordInfo.enDelReason      = enDelReason;
    stMsg.u.stDelRecordInfo.usMsgID          = pstDelRecord->usMsgID;
    stMsg.u.stDelRecordInfo.usSN             = pstDelRecord->usSN;
    stMsg.u.stDelRecordInfo.ulDupDetcTimeLen = pstDelRecord->ulDupDetcTimeLen;
    stMsg.u.stDelRecordInfo.ulRcvTimeTick    = pstDelRecord->ulRcvTimeTick;
    stMsg.u.stDelRecordInfo.ulCurrTick       = VOS_GetTick();

    /* 勾出可维可测信息 */
    DIAG_TraceReport(&stMsg);
}

/******************************************************************************
函 数 名  : TAF_CBS_SndOmSavedRecordInfo
功能描述  : 保存记录的可维可测信息
输入参数  : enMsgType: 可维可测事件ID
            enSaveType: 保存类型
            pstNewRecord: 新的记录项
            ulIndex: 新记录项索引
            ulRecordNum:  最新记录个数
输出参数  : 无
返 回 值  : VOS_VOID
调用函数  :
被调函数  :

修改历史      :
  1.日    期   : 2012年3月10日
    作    者   : l00171473
    修改内容   : 新生成函数
******************************************************************************/
VOS_VOID TAF_CBS_SndOmSavedRecordInfo(
    TAF_CBA_OM_MSG_ID_ENUM_UINT32       enMsgType,
    TAF_CBA_OM_SAVE_TYPE_ENUM_UINT8     enSaveType,
    TAF_CBA_RECORD_STRU                *pstNewRecord,
    VOS_UINT16                          usRecordNum
)
{
    TAF_CBA_MNTN_INFO_STRU              stMsg;

    PS_MEM_SET(&stMsg, 0x00, sizeof(stMsg));

    /* 消息封装 */
    stMsg.ulSenderCpuId       = VOS_LOCAL_CPUID;
    stMsg.ulSenderPid         = WUEPS_PID_TAF;
    stMsg.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    stMsg.ulReceiverPid       = WUEPS_PID_TAF;
    stMsg.ulLength            = sizeof(stMsg) - VOS_MSG_HEAD_LENGTH;

    stMsg.enMsgId             = enMsgType;

    stMsg.u.stSaveRecordInfo.enSaveType       = enSaveType;
    stMsg.u.stSaveRecordInfo.usRecordNum      = usRecordNum;
    stMsg.u.stSaveRecordInfo.ulDupDetcTimeLen = pstNewRecord->ulDupDetcTimeLen;

    /* 勾出可维可测信息 */
    DIAG_TraceReport(&stMsg);
}


/******************************************************************************
函 数 名  : TAF_CBA_SndOmDupRecordInfo
功能描述  : 重复记录的可维可测信息
输入参数  : enType: 可维可测事件ID
            pstOldRecord: 原记录项
输出参数  : 无
返 回 值  : VOS_VOID
调用函数  :
被调函数  :

修改历史      :
  1.日    期   : 2012年3月10日
    作    者   : l00171473
    修改内容   : 新生成函数
******************************************************************************/
VOS_VOID TAF_CBA_SndOmDupRecordInfo(
    TAF_CBA_OM_MSG_ID_ENUM_UINT32       enMsgType,
    TAF_CBA_RECORD_STRU                *pstOldRecord
)
{
    TAF_CBA_MNTN_INFO_STRU              stMsg;

    PS_MEM_SET(&stMsg, 0x00, sizeof(stMsg));

    /* 消息封装 */
    stMsg.ulSenderCpuId       = VOS_LOCAL_CPUID;
    stMsg.ulSenderPid         = WUEPS_PID_TAF;
    stMsg.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    stMsg.ulReceiverPid       = WUEPS_PID_TAF;
    stMsg.ulLength            = sizeof(stMsg) - VOS_MSG_HEAD_LENGTH;

    stMsg.enMsgId             = enMsgType;

    stMsg.u.stDupRecordInfo.usPageBitmap = pstOldRecord->usPageBitmap;
    stMsg.u.stDupRecordInfo.usMsgID      = pstOldRecord->usMsgID;
    stMsg.u.stDupRecordInfo.usSN         = pstOldRecord->usSN;

    /* 勾出可维可测信息 */
    DIAG_TraceReport(&stMsg);
}

/******************************************************************************
函 数 名  : TAF_CBA_SndOmCbmiDownloadListInfo
功能描述  : 当前CBS CBMID List的信息的可维可测信息
输入参数  : 无
输出参数  : 无
返 回 值  : VOS_VOID
调用函数  :
被调函数  :

修改历史      :
  1.日    期   : 2012年3月28日
    作    者   : l00171473
    修改内容   : 新生成函数
******************************************************************************/
VOS_VOID TAF_CBA_SndOmCbmiDownloadListInfo(VOS_VOID)
{
    TAF_CBA_MNTN_INFO_STRU             *pstMsg;
    TAF_CBA_CBMI_DOWNLOAD_LIST_STRU    *pstCbmidList;
    VOS_UINT32                          ulCbmidInx;

    pstMsg = (TAF_CBA_MNTN_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(TAF_CBA_MNTN_INFO_STRU));
    if ( VOS_NULL_PTR == pstMsg )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CBA_SndOmCbmiDownloadListInfo: MEM ALLOC ERROR");
        return;
    }

    PS_MEM_SET(pstMsg, 0x00, sizeof(TAF_CBA_MNTN_INFO_STRU));

    /* 消息封装 */
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_TAF;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = WUEPS_PID_TAF;
    pstMsg->ulLength        = sizeof(TAF_CBA_MNTN_INFO_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->enMsgId         = TAF_CBA_OM_MSG_CBMI_DOWNLOAD_LIST;

    /* 构造消息ID列表 */
    pstCbmidList = TAF_CBA_GetCbmiDownloadList();

    pstMsg->u.stCbmiDownloadList.usCbmidNum = pstCbmidList->usCbmidNum;

    for ( ulCbmidInx = 0; ulCbmidInx < pstCbmidList->usCbmidNum; ulCbmidInx++ )
    {
        pstMsg->u.stCbmiDownloadList.ausMsgId[ulCbmidInx] = pstCbmidList->ausMsgId[ulCbmidInx];
    }

    /* 勾出可维可测信息 */
    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_TAF, pstMsg);
}

/******************************************************************************
函 数 名  : TAF_CBA_SndOmCbmiRangeList
功能描述  : 当前CBS CBMIR List的信息的可维可测信息
输入参数  : 无
输出参数  : 无
返 回 值  : VOS_VOID
调用函数  :
被调函数  :

修改历史      :
  1.日    期   : 2012年3月28日
    作    者   : l00171473
    修改内容   : 新生成函数
******************************************************************************/
VOS_VOID TAF_CBA_SndOmCbmiRangeList(VOS_VOID)
{
    TAF_CBA_MNTN_INFO_STRU             *pstMsg;
    TAF_CBA_CBMI_RANGE_LIST_STRU       *pstCbmirList;
    VOS_UINT32                          ulCbmirInx;

    pstMsg = (TAF_CBA_MNTN_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(TAF_CBA_MNTN_INFO_STRU));
    if ( VOS_NULL_PTR == pstMsg )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CBA_SndOmCbmiRangeList: MEM ALLOC ERROR");
        return;
    }

    PS_MEM_SET(pstMsg, 0x00, sizeof(TAF_CBA_MNTN_INFO_STRU));

    /* 消息封装 */
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_TAF;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = WUEPS_PID_TAF;
    pstMsg->ulLength        = sizeof(TAF_CBA_MNTN_INFO_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->enMsgId         = TAF_CBA_OM_MSG_CBMI_RANGE_LIST;

    /* 构造消息ID列表 */
    pstCbmirList = TAF_CBA_GetCbMiRangeList();

    for ( ulCbmirInx = 0; ulCbmirInx < pstCbmirList->usCbmirNum; ulCbmirInx++ )
    {
        if (TAF_CBA_CBMI_RANGE_RCV_MODE_ACCEPT != pstCbmirList->astCbmiRangeInfo[ulCbmirInx].enRcvMode)
        {
            continue;
        }

        pstMsg->u.stCbmiRangeList.astCbmiRange[ulCbmirInx].usMsgIdFrom =
                                    pstCbmirList->astCbmiRangeInfo[ulCbmirInx].usMsgIdFrom;

        pstMsg->u.stCbmiRangeList.astCbmiRange[ulCbmirInx].usMsgIdTo =
                                    pstCbmirList->astCbmiRangeInfo[ulCbmirInx].usMsgIdTo;

        (pstMsg->u.stCbmiRangeList.usCbmirNum)++;
    }

    /* 勾出可维可测信息 */
    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_TAF, pstMsg);
}


/******************************************************************************
函 数 名  : TAF_CBA_SndOmNvimInfo
功能描述  : 发送CBA模块的NV配置的可维可测消息
输入参数  : 无
输出参数  : 无
返 回 值  : VOS_VOID
调用函数  :
被调函数  :

修改历史      :
  1.日    期   : 2012年3月28日
    作    者   : l00171473
    修改内容   : 新生成函数
******************************************************************************/
VOS_VOID TAF_CBA_SndOmNvimInfo(VOS_VOID)
{
    VOS_UINT8                          *pucMsgBuf = VOS_NULL_PTR;
    TAF_CBA_MNTN_INFO_STRU             *pstMsg    = VOS_NULL_PTR;
    VOS_UINT32                          ulBufLen;

    ulBufLen = TAF_CBA_MNTN_INFO_HEADER_LEN + sizeof(TAF_CBA_LOG_NVIM_INFO_STRU);

    pucMsgBuf = PS_MEM_ALLOC(WUEPS_PID_TAF, ulBufLen);
    if ( VOS_NULL_PTR == pucMsgBuf )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CBA_SndOmNvimInfo: MEM ALLOC ERROR");
        return;
    }

    PS_MEM_SET(pucMsgBuf, 0x00, ulBufLen);

    pstMsg = (TAF_CBA_MNTN_INFO_STRU*)pucMsgBuf;

    /* 消息封装 */
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_TAF;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = WUEPS_PID_TAF;
    pstMsg->ulLength        = ulBufLen - VOS_MSG_HEAD_LENGTH;

    pstMsg->enMsgId         = TAF_CBA_OM_MSG_NVIM_INFO;

    /* 填充CBS服务状态相关NV值 */
    pstMsg->u.stCbsNvimInfo.stCbsServiceParam.ucCbStatus     = TAF_CBA_GetCbsStatus();
    pstMsg->u.stCbsNvimInfo.stCbsServiceParam.ucDupDetectCfg = TAF_CBA_GetDupDetectCfg();


    pstMsg->u.stCbsNvimInfo.stCbsServiceParam.ucRptAppFullPageFlg = TAF_CBA_GetRptAppFullPageFlg();

#if (FEATURE_ETWS == FEATURE_ON)
    /* 填充ETWS相关NV值 */
    PS_MEM_CPY(&(pstMsg->u.stCbsNvimInfo.stEtwsMsCfg),
               TAF_CBA_GetMsCfgEtwsInfo(),
               sizeof(TAF_CBA_MS_CFG_ETWS_INFO_STRU));
#endif

    /* 勾出可维可测信息 */
    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_TAF, pucMsgBuf);
}

/*lint -restore */


#endif /* ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS)) */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
