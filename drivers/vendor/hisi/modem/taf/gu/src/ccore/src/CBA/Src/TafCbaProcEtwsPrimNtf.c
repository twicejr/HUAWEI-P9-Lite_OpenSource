/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafCbaProcEtwsPrimNtf.c
  版 本 号   : 初稿
  作    者   : l00171473
  生成日期   : 2012年3月19日
  最近修改   :
  功能描述   : ETWS主通知相关的消息
  函数列表   :
  修改历史   :
  1.日    期   : 2012年3月19日
    作    者   : l00171473
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "TafCbsInterface.h"
#include  "TafCbaMntn.h"
#include  "TafCbaProcEtwsPrimNtf.h"
#include  "TafCbaComFunc.h"
#include  "TafCbaProcAs.h"
#include  "TafCbaProcAt.h"

#include  "TafLog.h"
#include  "MnComm.h"
#include  "MnMsgTimerProc.h"
#include  "MnMsgReport.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_CBA_PROC_ETWS_PRIM_NTF_C

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))

#if (FEATURE_ON == FEATURE_ETWS)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
  3 函数实现
*****************************************************************************/




/*****************************************************************************
 函 数 名  : TAF_CBA_RcvAsEtwsPrimNotifyInd
 功能描述  : 处理接入层发送的ETWS主通知消息
 输入参数  : pstMsg  - AS发送过来的主通知消息
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月19日
    作    者   : l00171473
    修改内容   : 新生成函数, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
VOS_VOID TAF_CBA_RcvAsEtwsPrimNotifyInd(
    RR_CBS_ETWS_PRIMARY_NOTIFY_IND_STRU                    *pstMsg
)
{
    TAF_CBA_RECORD_STRU                                     stNewRecord;

    /* ETWS特性关闭则不处理ETWS主通知消息 */
    if (VOS_TRUE != TAF_CBA_GetEtwsEnableFlg())
    {
        /* 可维可测 */
        TAF_CBA_SndOmLogInfo(TAF_CBA_OM_LOG_RCV_PRIM_NTF_WHEN_ETWS_DISABLE);
        return;
    }

    /* 判断MSG ID是否有效 */
    if (VOS_TRUE != TAF_CBA_IsEtwsPrimNtfMsgIdValid(pstMsg->usMessageId))
    {
        /* 可维可测 */
        TAF_CBA_SndOmLogInfo(TAF_CBA_OM_LOG_ETWS_PRIM_NTF_MSGID_INVALID);
        return;
    }

    /* 检查和删除重复检测时长超时的ETWS主通知记录 */
    TAF_CBA_DelEtwsPrimNtfExpiredRecord();

    /* 构造主通知数据记录 */
    TAF_CBA_BuildEtwsPrimNtfRecord(pstMsg, &stNewRecord);

    /* 重复检查, 如是重复的消息, 不用保存和上报到AT */
    if ( VOS_TRUE == TAF_CBA_IsDupEtwsPrimNtf(&stNewRecord) )
    {
        return;
    }

    /* 保存主通知记录 */
    TAF_CBA_SaveEtwsPrimNtfRecord(&stNewRecord);

    /* 上报主通知到 AT */
    TAF_CBA_SndAtEtwsPrimNtfMsg(pstMsg);

    /* 后续处理: 当 W模CBS未使能时，需要临时使能CBS功能, 以便于收到ETWS从通知 */
    TAF_CBA_TemporaryEnableCbs();

}

/*****************************************************************************
 函 数 名  : TAF_CBA_IsMsgIdInEtwsMsgIdList
 功能描述  : 判断指定MSG ID是否在ETWS的ID范围
 输入参数  : usMsgId: 主从通知/CBS消息的MSG ID
 输出参数  : 无
 返 回 值  : VOS_TRUE :在ETWS的ID范围内
             VOS_FALSE:不在ETWS的ID范围内
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月25日
    作    者   : l00171473
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_CBA_IsMsgIdInEtwsMsgIdList(
    VOS_UINT16                          usMsgId
)
{
    VOS_UINT32                          ulUserEtwsIdx;
    TAF_CBA_ETWS_MSGID_RANGE_STRU      *pstUserSpecEtwsMsgIdList;
    VOS_UINT16                          usTmpMsgIdFrom;
    VOS_UINT16                          usTmpMsgIdTo;

    /* 首先判断是否在协议规定的ETWS CBS消息ID范围内 */
    if ( (usMsgId >= TAF_CBA_PROTOCOL_ETWS_CBS_MSGID_FROM)
      && (usMsgId <= TAF_CBA_PROTOCOL_ETWS_CBS_MSGID_TO) )
    {
        return VOS_TRUE;
    }

    /* 再判断是否在用户定制的ETWS 消息ID范围内 */
    pstUserSpecEtwsMsgIdList = TAF_CBA_GetUserSpecEtwsMsgIdList();

    for ( ulUserEtwsIdx = 0; ulUserEtwsIdx < TAF_CBA_NVIM_MAX_USER_SPEC_ETWS_MSGID_RANGE_NUM; ulUserEtwsIdx++ )
    {
        /* 由于初始化时没有做大小的判断处理，这里需要处理下 */
        if ( pstUserSpecEtwsMsgIdList[ulUserEtwsIdx].usMsgIdFrom <=  pstUserSpecEtwsMsgIdList[ulUserEtwsIdx].usMsgIdTo)
        {
            usTmpMsgIdFrom =  pstUserSpecEtwsMsgIdList[ulUserEtwsIdx].usMsgIdFrom;
            usTmpMsgIdTo   =  pstUserSpecEtwsMsgIdList[ulUserEtwsIdx].usMsgIdTo;
        }
        else
        {
            usTmpMsgIdFrom =  pstUserSpecEtwsMsgIdList[ulUserEtwsIdx].usMsgIdTo;
            usTmpMsgIdTo   =  pstUserSpecEtwsMsgIdList[ulUserEtwsIdx].usMsgIdFrom;
        }

        if ((usMsgId >= usTmpMsgIdFrom)
         && (usMsgId <= usTmpMsgIdTo))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_CBA_IsEtwsPrimNtfMsgIdValid
 功能描述  : 判断主通知消息ID是否有效
 输入参数  : usMsgId: 待判断的MSG ID
 输出参数  : 无
 返 回 值  : VOS_TRUE : MSG ID有效
             VOS_FALSE: MSG ID无效
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月25日
    作    者   : l00171473
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_CBA_IsEtwsPrimNtfMsgIdValid(
    VOS_UINT16                          usMsgId
)
{
    VOS_UINT32                          ulIsInCbsActiveList;
    VOS_UINT32                          ulIsInEtwsList;

    /* 判断MSG ID 是否在CBS激活列表中 */
    ulIsInCbsActiveList = TAF_CBA_IsMsgIdInCbsActiveList(usMsgId);

    /* 判断MSG ID 是否在ETWS MSG ID 范围内 */
    ulIsInEtwsList      = TAF_CBA_IsMsgIdInEtwsMsgIdList(usMsgId);

    if ( (VOS_TRUE == ulIsInCbsActiveList)
      && (VOS_TRUE == ulIsInEtwsList) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_CBA_GetEtwsDupDetcTimeLen
 功能描述  : 获取ETWS的主通知消息的重复检测时长
 输入参数  : pstPlmn: Plmn信息
 输出参数  : 无
 返 回 值  : 主通知消息的重复检测时长 Duplication Detection Time
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月25日
    作    者   : l00171473
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_CBA_GetEtwsDupDetcTimeLen(
    TAF_CBA_PLMN_ID_STRU                                   *pstPlmn
)
{
    TAF_CBA_ENH_DUP_DETECT_TIME_LEN_CFG_STRU               *pstEnhDupDetcTimeLenCfg;
    VOS_UINT8                                               ucEnhDupDetcFlg;
    VOS_UINT32                                              ulIndex;

    ucEnhDupDetcFlg         = TAF_CBA_GetEnhDupDetcFlg();

    pstEnhDupDetcTimeLenCfg = TAF_CBA_GetEnhDupDetcTimeLenCfg();

    /*  CHANGE REQUEST 23.041   CR  0083
        8.2 Duplication Detection Function
        Upon reception of a new message, the MS/UE shall perform duplication detection on the messages.
        Those messages that are received from the same PLMN in the certain time period specified
        by the Duplication Detection Time are subject to duplication detection.
        The value of Duplication Detection Time to be used by the MS/UE shall be derived from the
        MCC of the current PLMN as follows:
        -   If MCC = 440 or MCC = 441 (Japan), Duplication Detection Time shall be 1 hour;
        -   For all other MCCs, Duplication Detection Time shall be 24 hours.
    */

    /* 增强的重复检测定制特性未开启时的有效时长取值 */
    if (VOS_TRUE != ucEnhDupDetcFlg)
    {
        return TAF_CBA_GetNormalDupDetcTimeLen();
    }

    /* 增强的重复检测定制特性开启时的取值, 当前PLMN的MCC在定制MCC范围类和定制MCC外取值不同 */
    for ( ulIndex = 0; ulIndex < TAF_CBA_MAX_ETWS_DUP_DETECT_SPEC_MCC_NUM; ulIndex++ )
    {
        if (pstPlmn->ulMcc == pstEnhDupDetcTimeLenCfg->aulSpecMcc[ulIndex])
        {
            return pstEnhDupDetcTimeLenCfg->ulSpecMccTimeLen;
        }
    }

    return pstEnhDupDetcTimeLenCfg->ulOtherMccTimeLen;
}


/*****************************************************************************
 函 数 名  : TAF_CBA_BuildEtwsPrimNtfRecord
 功能描述  : 从AS的主通知消息中构造新的ETWS主通知记录
 输入参数  : pstMsg:       指向AS的主通知消息
 输出参数  : pstNewRecord: 新的ETWS主通知记录
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月9日
    作    者   : l00171473
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_CBA_BuildEtwsPrimNtfRecord(
    RR_CBS_ETWS_PRIMARY_NOTIFY_IND_STRU                    *pstMsg,
    TAF_CBA_RECORD_STRU                                    *pstNewRecord
)
{
    TAF_CBA_NET_RAT_TYPE_ENUM_UINT8     enRatType;

    
    if ( (VOS_NULL == pstMsg)
      || (VOS_NULL == pstNewRecord) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CBA_BuildEtwsPrimNtfRecord: ERR:pstMsg NULL Ptr!");
        return;
    }

    enRatType = TAF_CBA_GetRatTypeBySenderPid(pstMsg->ulSenderPid);

    PS_MEM_SET(pstNewRecord, 0x00, sizeof(TAF_CBA_RECORD_STRU));

    pstNewRecord->enNetMode        = enRatType;
    pstNewRecord->ucTotalPage      = 0;
    pstNewRecord->usPageBitmap     = 0;
    pstNewRecord->usMsgID          = pstMsg->usMessageId;
    pstNewRecord->usSN             = pstMsg->usSerialNumber;
    pstNewRecord->stPlmn.ulMcc     = pstMsg->stCurrNetworkInfo.stCurPlmn.ulMcc;
    pstNewRecord->stPlmn.ulMnc     = pstMsg->stCurrNetworkInfo.stCurPlmn.ulMnc;
    pstNewRecord->ulDupDetcTimeLen = TAF_CBA_GetEtwsDupDetcTimeLen(&(pstNewRecord->stPlmn));
    pstNewRecord->ulRcvTimeTick    = VOS_GetTick();
}

/*****************************************************************************
 函 数 名  : TAF_CBA_SaveEtwsPrimNtfRecord
 功能描述  : 保存ETWS主通知记录
 输入参数  : pstNewRecord: 待保存的新的主通知记录
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月27日
    作    者   : l00171473
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_CBA_SaveEtwsPrimNtfRecord (
    TAF_CBA_RECORD_STRU                *pstNewRecord
)
{
    TAF_CBA_RECORD_STRU                *pstPrimNtfList;
    VOS_UINT16                          usPrimNtfNum;
    VOS_UINT32                          ulSameMsgIdCodeInx;
    VOS_UINT32                          ulAppendInx;
    TAF_CBA_OM_SAVE_TYPE_ENUM_UINT8     enSaveType;

    ulSameMsgIdCodeInx   = 0;
    ulAppendInx          = 0;
    pstPrimNtfList       = TAF_CBA_GetRcvEtwsPrimNtfList();
    usPrimNtfNum         = TAF_CBA_GetRcvEtwsPrimNtfNum();

    /* 记录表中存在和收到消息的MSG ID和MSG CODE相同的记录项, 则覆盖原记录项 */
    if (VOS_TRUE == TAF_CBA_GetEtwsPrimNtfRecordInxByMsgIdCode(pstNewRecord, &ulSameMsgIdCodeInx))
    {
        /* 可维可测 */
        TAF_CBS_SndOmSavedRecordInfo(TAF_CBA_OM_MSG_SAVE_ETWS_PRIM_NTF_RECORD,
                                     TAF_CBA_OM_SAVE_TYPE_REPLACE_RECORD,
                                     pstNewRecord,
                                     usPrimNtfNum);

        /* 保存记录项 */
        pstPrimNtfList[ulSameMsgIdCodeInx] = (*pstNewRecord);

        return;
    }

    /*  不存在则新增一个记录项 */
    if ( TAF_CBA_MAX_ETWS_PRIM_NTF_RECORD_NUM == usPrimNtfNum )
    {
        /* 列表已满则获取最早的记录项的index, 覆盖之 */
        ulAppendInx = TAF_CBA_GetEarliestEtwsPrimNtfRecordInx();

        /* 最早记录的可维可测信息 */
        TAF_CBA_SndOmDeledRecordInfo(TAF_CBA_OM_MSG_DEL_ETWS_PRIM_RECORD,
                                     TAF_CBA_OM_DEL_REASON_LIST_FULL,
                                     &pstPrimNtfList[ulAppendInx]);

        /* 保存记录项 */
        pstPrimNtfList[ulAppendInx] = (*pstNewRecord);

        /* 记录保存的类型, 用于可维可测 */
        enSaveType = TAF_CBA_OM_SAVE_TYPE_RECORD_FULL;
    }
    else
    {
        /* 列表未满，则在最后增加一个记录 */
        ulAppendInx = usPrimNtfNum;

        /* 保存主通知记录项 */
        pstPrimNtfList[ulAppendInx] = (*pstNewRecord);

        /* 更新主通知记录个数 */
        usPrimNtfNum++;
        TAF_CBA_SetRcvEtwsPrimNtfNum(usPrimNtfNum);

        /* 记录保存的类型, 用于可维可测 */
        enSaveType = TAF_CBA_OM_SAVE_TYPE_APPEND_RECORD;
    }

    /* 可维可测 */
    TAF_CBS_SndOmSavedRecordInfo(TAF_CBA_OM_MSG_SAVE_ETWS_PRIM_NTF_RECORD,
                                 enSaveType,
                                 pstNewRecord,
                                 usPrimNtfNum);
}

/*****************************************************************************
 函 数 名  : TAF_CBA_GetEarliestEtwsPrimNtfRecordInx
 功能描述  : 获取最早的ETWS主通知记录的index
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 最早的ETWS主通知记录的index
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月10日
    作    者   : l00171473
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_CBA_GetEarliestEtwsPrimNtfRecordInx(VOS_VOID)
{
    TAF_CBA_RECORD_STRU                *pstRecordList;
    VOS_UINT32                          ulRcvPrimNtfNum;
    VOS_UINT32                          ulEarliestInx;
    VOS_UINT32                          ulEarliestTick;
    VOS_UINT32                          ulInx;

    pstRecordList   = TAF_CBA_GetRcvEtwsPrimNtfList();
    ulRcvPrimNtfNum = TAF_CBA_GetRcvEtwsPrimNtfNum();

    ulEarliestInx   = 0;
    ulEarliestTick  = pstRecordList[0].ulRcvTimeTick;

    for ( ulInx = 1; ulInx < ulRcvPrimNtfNum; ulInx++ )
    {
        if ( pstRecordList[ulInx].ulRcvTimeTick < ulEarliestTick )
        {
            ulEarliestInx  = ulInx;
            ulEarliestTick = pstRecordList[ulInx].ulRcvTimeTick;
        }
    }

    return ulEarliestInx;

}

/*****************************************************************************
 函 数 名  : TAF_CBA_IsNeedDupDetectEtwsPrimNtf
 功能描述  : 判断是否需要做重复过滤
 输入参数  : VOS_VOID
 输出参数  :
 返 回 值  : VOS_TRUE : 需要做重复过滤
             VOS_FALSE: 不需要做重复过滤
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月04日
    作    者   : l00171473
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_CBA_IsNeedDupDetectEtwsPrimNtf(VOS_VOID)
{
    TAF_CBA_DUP_DETECT_CFG_ENUM_UINT8   enDupDetectCfg;

    enDupDetectCfg = TAF_CBA_GetDupDetectCfg();
    
    if ( TAF_CBA_DUP_DETECT_CFG_ALL_ENABLE == enDupDetectCfg )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : TAF_CBA_IsDupEtwsPrimNtf
 功能描述  : 判断主通知记录表中是否存在重复的记录项
 输入参数  : pstRecord: 指向新消息记录
 输出参数  :
 返 回 值  : VOS_TRUE : 历史记录表中存在相同的记录项
             VOS_FALSE: 不存在相同的记录项
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月9日
    作    者   : l00171473
    修改内容   : 新生成函数
  2.日    期   : 2012年12月04日
    作    者   : l00171473
    修改内容   : for DTS2012120600056, 增加判断是否需要做重复过滤
*****************************************************************************/
VOS_UINT32 TAF_CBA_IsDupEtwsPrimNtf(
    TAF_CBA_RECORD_STRU                *pstRecord
)
{
    TAF_CBA_RECORD_STRU                *pstPrimNtfList;
    VOS_UINT8                           ucEnhDupDetcFlg;
    VOS_UINT16                          ulPrimNotifyNum;
    VOS_UINT32                          ulInx;


    if ( VOS_TRUE != TAF_CBA_IsNeedDupDetectEtwsPrimNtf() )
    {
        /* 不需要做重复过滤则认为 不是重复的记录项 */        
        return VOS_FALSE;
    }

    ucEnhDupDetcFlg = TAF_CBA_GetEnhDupDetcFlg();

    pstPrimNtfList  = TAF_CBA_GetRcvEtwsPrimNtfList();
    ulPrimNotifyNum = TAF_CBA_GetRcvEtwsPrimNtfNum();

    for ( ulInx = 0; ulInx < ulPrimNotifyNum; ulInx++ )
    {
        /* 判断接入模式 */
        if (pstRecord->enNetMode != pstPrimNtfList[ulInx].enNetMode)
        {
            continue;
        }

        /* DoCoMo对ETWS的增强的重复检测定制特性激活时, 需要判断PLMN */
        if (VOS_TRUE == ucEnhDupDetcFlg)
        {
            /* 判断PLMN */
            if ( (pstRecord->stPlmn.ulMcc != pstPrimNtfList[ulInx].stPlmn.ulMcc)
              || (pstRecord->stPlmn.ulMnc != pstPrimNtfList[ulInx].stPlmn.ulMnc) )
            {
                continue;
            }
        }

        /* 判断 MSG ID */
        if (pstRecord->usMsgID != pstPrimNtfList[ulInx].usMsgID)
        {
            continue;
        }

        /* 比较整个SN, 目前无需分别判断 MSG CODE, GS 和 UPDATE NUMBER */
        if (pstRecord->usSN == pstPrimNtfList[ulInx].usSN)
        {
            /* 可维可测 */
            TAF_CBA_SndOmDupRecordInfo(TAF_CBA_OM_MSG_DUP_ETWS_PRIM_NTF_RECORD,
                                       &(pstPrimNtfList[ulInx]));

            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_CBA_GetEtwsPrimNtfRecordInxByMsgIdCode
 功能描述  : 从主通知历史记录表中获取MSG ID和MSG CODE相同项的Index
 输入参数  : pstRecord: 指向新消息记录
 输出参数  : pstIndex : 相同项的index值
 返 回 值  : VOS_TRUE : 获取成功
             VOS_FALSE: 获取失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月9日
    作    者   : l00171473
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_CBA_GetEtwsPrimNtfRecordInxByMsgIdCode(
    TAF_CBA_RECORD_STRU                *pstRecord,
    VOS_UINT32                         *pstIndex
)
{
    TAF_CBA_RECORD_STRU                *pstPrimNtfList;
    VOS_UINT16                          ulPrimNtfNum;
    VOS_UINT32                          ulInx;

    pstPrimNtfList = TAF_CBA_GetRcvEtwsPrimNtfList();
    ulPrimNtfNum   = TAF_CBA_GetRcvEtwsPrimNtfNum();

    for ( ulInx = 0; ulInx < ulPrimNtfNum; ulInx++ )
    {
        /* 判断接入模式 */
        if (pstRecord->enNetMode != pstPrimNtfList[ulInx].enNetMode)
        {
            continue;
        }

        /* 判断PLMN */
        if ( (pstRecord->stPlmn.ulMcc != pstPrimNtfList[ulInx].stPlmn.ulMcc)
          || (pstRecord->stPlmn.ulMnc != pstPrimNtfList[ulInx].stPlmn.ulMnc) )
        {
            continue;
        }

        /* 判断 MSG ID 和 MSG CODE */
        if ( (VOS_TRUE == TAF_CBA_IsSameMsgCode(pstRecord->usSN, pstPrimNtfList[ulInx].usSN))
          && (pstRecord->usMsgID == pstPrimNtfList[ulInx].usMsgID) )
        {
            *pstIndex = ulInx;
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_CBA_TemporaryEnableCbs
 功能描述  : 检查是否需要临时使能CBS以便于接收ETWS的从通知, 如果需要则向AS发送
             使能CBS消息, 并启动定时器. 定时器超时后需要需向AS发送去使能CBS消息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月15日
    作    者   : l00171473
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_CBA_TemporaryEnableCbs(VOS_VOID)
{
    TAF_CBA_CBSTATUS_ENUM_UINT8         enCbsStatus;
    TAF_CBA_NET_RAT_TYPE_ENUM_UINT8     enNetMode;

    /* 检查CBS功能是否处于开启状态, 已处于开启状态则不需要再临时使能CBS功能 */
    enCbsStatus = TAF_CBA_GetCbsStatus();
    if ( (TAF_CBA_CBSTATUS_W_ENABLE  == enCbsStatus)
      || (TAF_CBA_CBSTATUS_WG_ENABLE == enCbsStatus) )
    {
        /* 当前W模的CBS处于开启，则不用启动T定时器 */
        /* todo:如果G支持ETWS了这里需要修改 */
        return;
    }

    if (VOS_TRUE == MN_MSG_IsTimerStarting(TI_TAF_CBA_RCV_ETWS_TEMP_ENABLE_CBS))
    {
        /* T定时器已启动，则重启之 */
        MN_MSG_StopTimer(TI_TAF_CBA_RCV_ETWS_TEMP_ENABLE_CBS);
        MN_MSG_StartTimer(TI_TAF_CBA_RCV_ETWS_TEMP_ENABLE_CBS, 0);
    }
    else
    {
        /* T定时器未启动则启动之，并通知BMC使能CBS, 以使之能收到ETWS从通知 */
        MN_MSG_StartTimer(TI_TAF_CBA_RCV_ETWS_TEMP_ENABLE_CBS, 0);

        /* W模才需做后续的处理,
           L模也启动定时器，是为了当L模切换到W模后可以通过该定时器的状态决定是否激活W的CBS功能 */
        enNetMode = TAF_CBA_GetNetRatType();
        if ((VOS_FALSE == TAF_CBA_IsCbsActiveListEmpty())
         && (TAF_CBA_NET_RAT_TYPE_WCDMA == enNetMode))      
        {
            TAF_CBA_SndAsActiveCbsReq(TAF_CBS_CFG_ACTIVE);
        }
    }
}
/*lint -restore */

#endif  /* (FEATURE_ON == FEATURE_ETWS) */

#endif /* ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS)) */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
