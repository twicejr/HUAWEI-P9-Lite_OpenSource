/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafCbaComFunc.c
  版 本 号   : 初稿
  作    者   : l00171473
  生成日期   : 2012年3月19日
  最近修改   :
  功能描述   : CBS相关的公共处理函数,如Record的共用处理
  函数列表   :
  修改历史   :
  1.日    期   : 2012年3月19日
    作    者   : l00171473
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "TafCbaComFunc.h"
#include  "TafCbaMntn.h"
#include  "TafCbaProcAs.h"
#include  "TafCbaProcUsim.h"
#include  "TafCbaProcNvim.h"
#include  "TafCbaProcEtwsPrimNtf.h"
#include  "MnMsgApi.h"
#include  "MnComm.h"
#include  "TafLog.h"
#include "MnMsgTimerProc.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_CBA_COMM_FUNC_C

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : TAF_CBA_IsMsgIdInCBMIDList
 功能描述  : 判断指定的MSG ID是否在CBMID列表中
 输入参数  : usMsgId: 主从通知/CBS消息的MSG ID
 输出参数  : 无
 返 回 值  : VOS_TRUE :在CBMID列表中
             VOS_FALSE:不在CBMID列表中
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月30日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_CBA_IsMsgIdInCBMIDList(
    VOS_UINT16                          usMsgId
)
{
    VOS_UINT16                          usIndex;
    TAF_CBA_CBMI_DOWNLOAD_LIST_STRU    *pstCbmidList;

    pstCbmidList = TAF_CBA_GetCbmiDownloadList();

    /* 先判断是否在CBMID中 */
    for ( usIndex = 0; usIndex < pstCbmidList->usCbmidNum; usIndex++ )
    {
        if ( usMsgId == pstCbmidList->ausMsgId[usIndex] )
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_CBA_IsMsgIdInCBMIRList
 功能描述  : 判断指定的MSG ID是否在CBMIR列表中
 输入参数  : usMsgId: 主从通知/CBS消息的MSG ID
 输出参数  : 无
 返 回 值  : VOS_TRUE :在CBMIR列表中
             VOS_FALSE:不在CBMIR列表中
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月30日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2013年07月222日
    作    者   : j00177245
    修改内容   : 清理Coverity

*****************************************************************************/
VOS_UINT32 TAF_CBA_IsMsgIdInCBMIRList(
    VOS_UINT16                          usMsgId
)
{
    VOS_UINT16                          usIndex;
    VOS_UINT16                          usTmpMsgIdFrom;
    VOS_UINT16                          usTmpMsgIdTo;
    TAF_CBA_CBMI_RANGE_LIST_STRU       *pstCbmirList;
    VOS_UINT16                          usCbmiRangNum;

    pstCbmirList  = TAF_CBA_GetCbMiRangeList();
    usCbmiRangNum = TAF_CBA_GetCbmiRangNum();

    if (usCbmiRangNum > TAF_CBA_MAX_CBMID_RANGE_NUM)
    {
        usCbmiRangNum = TAF_CBA_MAX_CBMID_RANGE_NUM;
    }

    /* 检查是否在CBMIR中 */
    for ( usIndex = 0 ; usIndex < usCbmiRangNum; usIndex++ )
    {
        if ( TAF_CBA_CBMI_RANGE_RCV_MODE_ACCEPT != pstCbmirList->astCbmiRangeInfo[usIndex].enRcvMode)
        {
            continue;
        }

        usTmpMsgIdFrom = pstCbmirList->astCbmiRangeInfo[usIndex].usMsgIdFrom;
        usTmpMsgIdTo   = pstCbmirList->astCbmiRangeInfo[usIndex].usMsgIdTo;

        if ( (usMsgId >= usTmpMsgIdFrom)
          && (usMsgId <= usTmpMsgIdTo) )
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}



/*****************************************************************************
 函 数 名  : TAF_CBA_IsMsgIdInCbsActiveList
 功能描述  : 判断指定的MSG ID是否在USIM和用户设置的激活列表中
 输入参数  : usMsgId: 主从通知/CBS消息的MSG ID
 输出参数  : 无
 返 回 值  : VOS_TRUE :在激活列表中
             VOS_FALSE:不在激活列表中
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月25日
    作    者   : l00171473
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_CBA_IsMsgIdInCbsActiveList(
    VOS_UINT16                          usMsgId
)
{
    /* 先判断是否在CBMID中 */
    if (VOS_TRUE == TAF_CBA_IsMsgIdInCBMIDList(usMsgId))
    {
        return VOS_TRUE;
    }

    /* 检查是否在CBMIR中 */
    if (VOS_TRUE == TAF_CBA_IsMsgIdInCBMIRList(usMsgId))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : TAF_CBA_IsRecordExpired
 功能描述  : 判断记录项是否超时
 输入参数  : pstRecord: 历史记录项
 输出参数  : 无
 返 回 值  : VOS_TRUE : 指定记录项超时
             VOS_FASLE: 未超时
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月7日
    作    者   : l00171473
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_CBA_IsRecordExpired(
    TAF_CBA_RECORD_STRU                *pstRecord
)
{
    VOS_UINT32                          ulCurrtTick;
    VOS_UINT32                          ulPassSeconds;

    /* VOS TICK 是递增的，10 ms 为单位 */
    ulCurrtTick = VOS_GetTick();

    /* 有效时长为0则表示一直有效 */
    if ( 0 == pstRecord->ulDupDetcTimeLen )
    {
        return VOS_FALSE;
    }

    if ( ulCurrtTick < pstRecord->ulRcvTimeTick )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CBA_IsRecordExpired ,CurrtTick error.\n");
        TAF_CBA_SndOmLogInfo(TAF_CBA_OM_LOG_TICK_ERROR);
        return VOS_FALSE;
    }

    /* 是否超过重复检测时长 */
    ulPassSeconds = (ulCurrtTick - pstRecord->ulRcvTimeTick)/100;
    if ( ulPassSeconds >= pstRecord->ulDupDetcTimeLen )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_CBA_IsSameMsgCode
 功能描述  : 比较当前的两个记录是否具有相同的MSG CODE
 输入参数  : usNewSn
             usOldSn
 输出参数  : 无
 返 回 值  : VOS_UINT32:当前操作成功或失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月27日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_CBA_IsSameMsgCode(
    VOS_UINT16                          usNewSn,
    VOS_UINT16                          usOldSn
)
{
    VOS_UINT16                          usNewMsgCode;
    VOS_UINT16                          usOldMsgCode;

    usNewMsgCode = TAF_CBA_BIT_MASK_MSG_CODE & usNewSn;

    usOldMsgCode = TAF_CBA_BIT_MASK_MSG_CODE & usOldSn;

    if (usNewMsgCode == usOldMsgCode)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_CBA_IsSameGsCode
 功能描述  : 比较当前的两个记录是否具有相同的GS CODE
 输入参数  : usNewSn
             usOldSn
 输出参数  : 无
 返 回 值  : VOS_UINT32:当前操作成功或失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月27日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_CBA_IsSameGsCode(
    VOS_UINT16                          usNewSn,
    VOS_UINT16                          usOldSn
)
{
    VOS_UINT16                          usNewGs;
    VOS_UINT16                          usOldGs;

    usNewGs = TAF_CBA_BIT_MASK_GS & usNewSn;

    usOldGs = TAF_CBA_BIT_MASK_GS & usOldSn;

    if (usNewGs == usOldGs)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_CBA_IsSameUpdateNum
 功能描述  : 比较当前的两个记录是否具有相同的Update Num
 输入参数  : usNewSn
             usOldSn
 输出参数  : 无
 返 回 值  : VOS_UINT32:当前操作成功或失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月27日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2013年8月13日
    作    者   : w00242748
    修改内容   : DTS2013081300926 参照协议0341 9.3.2.1 Update Number一节修改
*****************************************************************************/
VOS_UINT32 TAF_CBA_IsSameUpdateNum(
    VOS_UINT16                          usNewSn,
    VOS_UINT16                          usOldSn
)
{
    VOS_UINT16                          usNewUpdateNum;
    VOS_UINT16                          usOldUpdataNum;
    VOS_UINT8                           usMod;

    usNewUpdateNum = TAF_CBA_BIT_MASK_UPDATE_NUMBER & usNewSn;
    usOldUpdataNum = TAF_CBA_BIT_MASK_UPDATE_NUMBER & usOldSn;

    /* 以下代码我的理解:
       正向取值超过8，则认为该UPDATE NUMBER相同，如oldUpdateNum为6，newUpdateNum为7以后的称为正向;
       反向取值小于8，则认为该UPDATE NUMBER相同，如oldUpdateNum为6，newUpdateNum为5以前的称为反向;
    */
    usMod = (usOldUpdataNum + (VOS_UINT8) (CB_UPDATE_NUMBER_MAX_CHANGE)) % (CB_MAX_UPDATE_NUMBER+1);

    if((usOldUpdataNum <= (VOS_UINT8)(CB_MAX_UPDATE_NUMBER-CB_UPDATE_NUMBER_MAX_CHANGE))
     && ((usNewUpdateNum > usOldUpdataNum)
      && (usNewUpdateNum <= usMod)))
    {
        return VOS_FALSE;
    }
    else if((usOldUpdataNum > (VOS_UINT8)(CB_MAX_UPDATE_NUMBER-CB_UPDATE_NUMBER_MAX_CHANGE))
         && ((usNewUpdateNum > usOldUpdataNum)
          || (usNewUpdateNum <= usMod)))
    {
        return VOS_FALSE;
    }
    else
    {
        return VOS_TRUE;
    }
}

/*****************************************************************************
 函 数 名  : TAF_CBA_DelRecordByActiveList
 功能描述  : 将MN格式的netmode转换为CBA格式的网络类型
 输入参数  : ucMnNtMode:mn格式的网络模式
 输出参数  : penNetType:CBA格式的网络类型
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月30日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_CBA_ConvertMnNetModeToCbaFormat(
    VOS_UINT8                           ucMnNtMode,
    TAF_CBA_NET_RAT_TYPE_ENUM_UINT8    *penNetType
)
{
    switch (ucMnNtMode)
    {
        case MN_NET_MODE_GSM:

            *penNetType = TAF_CBA_NET_RAT_TYPE_GSM;
            break;

        case MN_NET_MODE_WCDMA:

            *penNetType = TAF_CBA_NET_RAT_TYPE_WCDMA;
            break;

#if (FEATURE_ON == FEATURE_LTE)
        case MN_NET_MODE_LTE:

            *penNetType = TAF_CBA_NET_RAT_TYPE_LTE;
            break;
#endif
        default:

            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CBA_ConvertMnNetModeToCbaFormat ,invalid net mode.\n");

            *penNetType = TAF_CBA_NET_RAT_TYPE_BUTT;
            break;
    }
}

/*****************************************************************************
 函 数 名  : TAF_CBA_IsDupMidsInActiveList
 功能描述  : 检查添加消息中是否有与现有的激活列表重复的消息范围，如果存在一个，则立即返回出错

 输入参数  : pstAddbMids:
 输出参数  : 无
 返 回 值  : VOS_UINT32:MN_ERR_NO_ERROR:无重复的MID
                        MN_ERR_CLASS_CBS_CROSS_MID_ERROR:有重复的MID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月26日
    作    者   : t00212959
    修改内容   : 新生成函数 for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
VOS_UINT32 TAF_CBA_IsDupMidsInActiveList(
    TAF_CBA_CBMI_RANGE_LIST_STRU       *pstAddbMids
)
{
    VOS_UINT32                          ulCbmirInx;
    VOS_UINT32                          ulRet;
    TAF_CBA_CBMI_RANGE_LIST_STRU       *pstMemCbmiRangList;
    TAF_CBA_CBMI_RANGE_STRU            *pstAddCbmirInfo;
    VOS_UINT32                          ulCbmidIdx;

    pstMemCbmiRangList = TAF_CBA_GetCbMiRangeList();

    ulRet = VOS_FALSE;

    if ( pstAddbMids->usCbmirNum > TAF_CBA_MAX_CBMID_RANGE_NUM)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CBA_IsDupMidsInActiveList: usCbmirNum Error.");
        pstAddbMids->usCbmirNum  = TAF_CBA_MAX_CBMID_RANGE_NUM;
    }

    pstAddCbmirInfo = pstAddbMids->astCbmiRangeInfo;

    /* 检查是否有存在 */
    for ( ulCbmirInx = 0 ; ulCbmirInx < pstAddbMids->usCbmirNum; ulCbmirInx++ )
    {
        ulRet = TAF_CBA_IsCbmirExist(&pstAddCbmirInfo[ulCbmirInx],
                                     pstMemCbmiRangList,
                                     &ulCbmidIdx);
        if ( VOS_TRUE == ulRet )
        {
            TAF_INFO_LOG(WUEPS_PID_TAF, "TAF_CBA_IsDupMidsInActiveList: Cross Mids.");
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_CBA_AddCbMiRangeListToActiveList
 功能描述  : 添加内存中CBMIR列表,如果CBMID_Range列表中空闲不够时,已经加入的CBMID Range不清除,
             直接返回出错。
 输入参数  : pstOrgCbMirList:需更新的CBMIR列表
             ulCbCount:列表中CBMIR的个数
 输出参数  : 无
 返 回 值  : VOS_UINT32 :VOS_OK  - 加入成功
                         VOS_ERR - 加入失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月26日
    作    者   : t00212959
    修改内容   : 新生成函数 for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
VOS_UINT32 TAF_CBA_AddCbMiRangeListToActiveList(
    TAF_CBA_CBMI_RANGE_LIST_STRU       *pstOrgCbMirList
)
{
    VOS_UINT16                          usIndex;
    VOS_UINT32                          ulRet;
    TAF_CBA_CBMI_RANGE_LIST_STRU       *pstDstCbMirList;
    VOS_UINT32                          ulSaveIdx;
    VOS_UINT32                          ulCbmidIdx;

    pstDstCbMirList = TAF_CBA_GetCbMiRangeList();

    for ( usIndex = 0 ; usIndex < pstOrgCbMirList->usCbmirNum ; usIndex++ )
    {
        ulRet = TAF_CBA_IsCbmirExist(&(pstOrgCbMirList->astCbmiRangeInfo[usIndex]),
                                     pstDstCbMirList,
                                     &ulCbmidIdx);

        /* 原本在列表中存在，不需要加入 */
        if (VOS_TRUE == ulRet)
        {
            continue;
        }

        ulSaveIdx = TAF_CBA_GetCbmiRangNum();

        /* 列表满 */
        if ( ulSaveIdx >= TAF_CBA_MAX_CBMID_RANGE_NUM )
        {
            TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_CBA_AddCbmirListToActiveList:No available Index");
            return VOS_ERR;
        }

        pstDstCbMirList->astCbmiRangeInfo[ulSaveIdx].enRcvMode = TAF_CBA_CBMI_RANGE_RCV_MODE_ACCEPT;

        pstDstCbMirList->astCbmiRangeInfo[ulSaveIdx].usMsgIdFrom
                = pstOrgCbMirList->astCbmiRangeInfo[usIndex].usMsgIdFrom;

        pstDstCbMirList->astCbmiRangeInfo[ulSaveIdx].usMsgIdTo
                = pstOrgCbMirList->astCbmiRangeInfo[usIndex].usMsgIdTo;

        pstDstCbMirList->usCbmirNum++;

    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_CBA_IsCbmirExist
 功能描述  : 检查CBMIR是否存在列表中
 输入参数  : pstMsgRange        - 需检查的MID
             pstCbmirList       - MIDR LIST
 输出参数  : pulCbmirIdx        - 当前找到的CBMID的Index
 返 回 值  : VOS_UINT32  VOS_TRUE  - MIDR在LIST列表中
                         VOS_FALSE - MIDR不在LIST列表中
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月26日
    作    者   : t00212959
    修改内容   : 新生成函数 for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
VOS_UINT32 TAF_CBA_IsCbmirExist(
    TAF_CBA_CBMI_RANGE_STRU            *pstMsgRange,
    TAF_CBA_CBMI_RANGE_LIST_STRU       *pstCbmirList,
    VOS_UINT32                         *pulCbmirIdx
)
{
    VOS_UINT32                          ulCbmidRangeInx;

    for ( ulCbmidRangeInx = 0; ulCbmidRangeInx < pstCbmirList->usCbmirNum; ulCbmidRangeInx++ )
    {
        if (  (TAF_CBA_CBMI_RANGE_RCV_MODE_ACCEPT == pstCbmirList->astCbmiRangeInfo[ulCbmidRangeInx].enRcvMode)
           && ( ( pstMsgRange->usMsgIdFrom == pstCbmirList->astCbmiRangeInfo[ulCbmidRangeInx].usMsgIdFrom)
           && (pstMsgRange->usMsgIdTo == pstCbmirList->astCbmiRangeInfo[ulCbmidRangeInx].usMsgIdTo)))
        {
            *pulCbmirIdx = ulCbmidRangeInx;
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_CBA_IsCbmiRangeListEmpty
 功能描述  : CBMI RANGE 列表是否为空
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 列表已经为空
             VOS_FALSE - 列表不为空
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月26日
    作    者   : t00212959
    修改内容   : 新生成函数 for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
VOS_UINT32 TAF_CBA_IsCbmiRangeListEmpty(VOS_VOID)
{
    /* 如果当前已经清空了 */
    if (0 == TAF_CBA_GetCbmiRangNum())
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_CBA_IsCbsActiveListEmpty
 功能描述  : 判断USIM和用户设置的激活列表是否为空
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE: 激活列表为空
             VOS_FALSE:激活列表不为空
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月26日
    作    者   : t00212959
    修改内容   : 新生成函数 for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
VOS_UINT32 TAF_CBA_IsCbsActiveListEmpty(VOS_VOID)
{
    VOS_INT32                           ulInx;
    TAF_CBA_CBMI_RANGE_STRU            *pstCbmiRangeListHead;
    VOS_UINT16                          usCbmiRangNum;

    /* 如果CBMID中有内容，则需要使能AS的CBS功能  */
    if ( TAF_CBA_GetCbmiDownloadNum() > 0 )
    {
        return VOS_FALSE;
    }

    /* 如果CBMIR中有内容，则需要使能AS的CBS功能 */

    pstCbmiRangeListHead = TAF_CBA_GetCbmiRangeListHead();
    usCbmiRangNum        = TAF_CBA_GetCbmiRangNum();

    for ( ulInx = 0; ulInx < usCbmiRangNum; ulInx++ )
    {
        if ( TAF_CBA_CBMI_RANGE_RCV_MODE_ACCEPT == pstCbmiRangeListHead[ulInx].enRcvMode)
        {
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_CBA_IsNeedActAsCbs
 功能描述  : 判断是否需要激活AS的CBS功能
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月20日
    作    者   : l00171473
    修改内容   : for V7R1C50 CSFB&PPAC&ETWS&ISR
*****************************************************************************/
VOS_UINT32 TAF_CBA_IsNeedActAsCbs(VOS_VOID)
{
    TAF_CBA_CBSTATUS_ENUM_UINT8         enCbsStatus;
    TAF_CBA_NET_RAT_TYPE_ENUM_UINT8     enNetMode;

    /* 获取当前CBS消息是否激活标志 */
    enCbsStatus = TAF_CBA_GetCbsStatus();

    enNetMode   = TAF_CBA_GetNetRatType();

    /* 必须满足NV中该模式CBS激活同时该模式宏开关已打开才默认CBS激活 */
#if (FEATURE_ON == FEATURE_WCBS)
    if (((TAF_CBA_CBSTATUS_W_ENABLE  == enCbsStatus)
      || (TAF_CBA_CBSTATUS_WG_ENABLE == enCbsStatus))
     && (TAF_CBA_NET_RAT_TYPE_WCDMA == enNetMode))
    {
        return VOS_TRUE;
    }
#endif

#if (FEATURE_ON == FEATURE_GCBS)
    if (((TAF_CBA_CBSTATUS_G_ENABLE  == enCbsStatus)
      || (TAF_CBA_CBSTATUS_WG_ENABLE == enCbsStatus))
     && (TAF_CBA_NET_RAT_TYPE_GSM == enNetMode))
    {
        return VOS_TRUE;
    }
#endif

#if  (FEATURE_ON == FEATURE_ETWS)
    /* W模下T定时器使能状态需要向BMC发送Active Req */
    /* todo:如果G支持ETWS了这里需要修改 */
    if ((VOS_TRUE == MN_MSG_IsTimerStarting(TI_TAF_CBA_RCV_ETWS_TEMP_ENABLE_CBS))
     && (TAF_CBA_NET_RAT_TYPE_WCDMA == enNetMode))
    {
        return VOS_TRUE;
    }

#endif

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : TAF_CBA_IsRecordValidByGsChgType
 功能描述  : 判断GS 变化后，记录项是否仍有效
 输入参数  : usSerialNum: 记录项的SN
             enGsChgType: GS变化类型
 输出参数  : 无
 返 回 值  : VOS_TRUE:  记录项仍有效
             VOS_FALSE: 记录项无效
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月29日
    作    者   : l00171473
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_CBA_IsRecordValidByGsChgType(
    VOS_UINT16                          usSerialNum,
    TAF_CBS_GS_CHG_TYPE_ENUM_UINT8      enGsChgType
)
{
    VOS_UINT8                           usGSInSN;
    VOS_UINT32                          ulIsValid;

    /***************************************************************************
                              GS变化后消息有效性判断规则
    GS变化类型\存储SN中的GS 01 PLMN wide  10 Service Area wide  00/11 Cell wide
    RRC_BMC_GS_CHG_PLMN         失效              失效              失效
    RRC_BMC_GS_CHG_SA           有效              失效              失效
    RRC_BMC_GS_CHG_CELL         有效              有效              失效
    ****************************************************************************/

    /* 得到存储SN的有效GS ,移位后只取最后两位 */
    usGSInSN  = TAF_CBA_BuildGsCode(usSerialNum);

    ulIsValid = VOS_TRUE;

    switch ( enGsChgType )
    {
        case TAF_CBS_GS_CHG_TYPE_CHG_PLMN:

            /* 发生PLMN切换，存储的SN失效 */
            ulIsValid = VOS_FALSE;
            break;

        case TAF_CBS_GS_CHG_TYPE_CHG_SA:

            /* 发生SA切换，存储的SN中PLMN范围的记录仍有效 */
            if ( TAF_CBA_GS_CODE_PLMN_WIDE != usGSInSN )
            {
                ulIsValid = VOS_FALSE;
            }
            break;

        case TAF_CBS_GS_CHG_TYPE_CHG_CELL:

            /* 发生SA切换，存储的SN中PLMN和SA范围的记录仍有效 */
            if ( (TAF_CBA_GS_CODE_PLMN_WIDE != usGSInSN)
              && (TAF_CBA_GS_CODE_SERVICE_AREA_WIDE != usGSInSN) )
            {
                ulIsValid = VOS_FALSE;
            }
            break;

        default:

            break;
    }

    return ulIsValid;
}

/*****************************************************************************
 函 数 名  : TAF_CBA_SndAsActiveCbsReq
 功能描述  : 给接入层发送激活请求
 输入参数  : enActiveFlg : 激活或去激活CBS功能
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月20日
    作    者   : l00171473
    修改内容   : for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
VOS_VOID TAF_CBA_SndAsActiveCbsReq(
    TAF_CBS_CFG_ENUM_UINT32             enCfgFlg
)
{
    TAF_CBA_NET_RAT_TYPE_ENUM_UINT8     enNetMode;
    CBS_BMC_CFG_REQ_STRU               *pstMsg;
    TAF_CBS_MSG_TYPE_ENUM_UINT16        enMsgId;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulReceiverPid;

    enNetMode   = TAF_CBA_GetNetRatType();

    if ( TAF_CBA_NET_RAT_TYPE_WCDMA == enNetMode)
    {
        enMsgId = ID_CBS_BMC_CFG_REQ;
        ulReceiverPid = WUEPS_PID_BMC;
    }
    else if (TAF_CBA_NET_RAT_TYPE_GSM == enNetMode)
    {
        enMsgId = ID_CBS_GAS_CFG_REQ;
        ulReceiverPid = UEPS_PID_GAS;
    }
    else
    {
        /* L模不需要激活CBS功能 */
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CBA_SndAsActiveCbsReq: invalid network mode!" );

        return;
    }

    pstMsg = (CBS_BMC_CFG_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF, sizeof(CBS_BMC_CFG_REQ_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        /* ERR LOG */
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CBA_SndAsActiveCbsReq: alloc memory fail!" );

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(CBS_BMC_CFG_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_TAF;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = ulReceiverPid;
    pstMsg->ulLength        = sizeof(CBS_BMC_CFG_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->enMsgId         = enMsgId;

    pstMsg->enCbsActive     = enCfgFlg;


    ulRet = PS_SEND_MSG(WUEPS_PID_TAF, pstMsg);
    if (VOS_OK != ulRet)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CBA_SndAsActiveCbsReq: To send CBS Config message failed!" );
    }
}

#if (FEATURE_ETWS == FEATURE_ON)
/*****************************************************************************
 函 数 名  : TAF_CBA_DelEtwsPrimNtfRecord
 功能描述  : 删除一个主通知历史记录项
 输入参数  : usDelIndex : 需要删除的记录项的index
             enDelReason: 删除的原因, 可维可测
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月9日
    作    者   : l00171473
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_CBA_DelEtwsPrimNtfRecord(
    VOS_UINT32                          ulDelInx,
    TAF_CBA_OM_DEL_REASON_ENUM_UINT8    enDelReason
)
{
    TAF_CBA_RECORD_STRU                *pstPrimNtfList;
    VOS_UINT16                          usPrimNtfNum;
    VOS_UINT32                          ulLastRecordInx;
    VOS_UINT32                          ulCurrInx;

    if ( ulDelInx >= TAF_CBA_MAX_ETWS_PRIM_NTF_RECORD_NUM )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CBA_DelEtwsPrimNtfRecord: ERR,ulDelIndex error !");
        return;
    }

    pstPrimNtfList = TAF_CBA_GetRcvEtwsPrimNtfList();
    usPrimNtfNum   = TAF_CBA_GetRcvEtwsPrimNtfNum();

    if (0 == usPrimNtfNum)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CBA_DelEtwsPrimNtfRecord: ERR,EtwsPrimNotifyNum 0!");
        return;
    }

    ulLastRecordInx = usPrimNtfNum - 1;

    if (ulDelInx > ulLastRecordInx)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CBA_DelEtwsPrimNtfRecord: ERR,ulDelInx > ulLastRecordInx!");
        return;
    }

    /* 可维可测 */
    TAF_CBA_SndOmDeledRecordInfo(TAF_CBA_OM_MSG_DEL_ETWS_PRIM_RECORD,
                                 enDelReason,
                                 &pstPrimNtfList[ulDelInx]);

    /* 依次将后续的记录前移, 覆盖要删除的记录 */
    for ( ulCurrInx = ulDelInx; ulCurrInx < ulLastRecordInx; ulCurrInx++ )
    {
        pstPrimNtfList[ulCurrInx] = pstPrimNtfList[ulCurrInx+1];
    }

    /* 使队尾的记录失效 */
    PS_MEM_SET(&pstPrimNtfList[ulLastRecordInx],
               0x00,
               sizeof(TAF_CBA_RECORD_STRU));

    /* 记录个数减 1 */
    usPrimNtfNum--;
    TAF_CBA_SetRcvEtwsPrimNtfNum(usPrimNtfNum);
}
#endif

/*****************************************************************************
 函 数 名  : TAF_CBA_DelCbsRecord
 功能描述  : 从CBS历史记录表中根据index删除一个CBS历史记录项
 输入参数  : usDelIndex:  需要删除的记录项的index
             enDelReason: 删除的原因, 可维可测
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月9日
    作    者   : l00171473
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_CBA_DelCbsRecord(
    VOS_UINT32                          ulDelInx,
    TAF_CBA_OM_DEL_REASON_ENUM_UINT8    enDelReason
)
{
    TAF_CBA_RECORD_STRU                *pstRcvCbsList;
    VOS_UINT16                          usRcvCbsNum;
    VOS_UINT32                          ulLastRecordInx;
    VOS_UINT32                          ulCurrInx;

    pstRcvCbsList = TAF_CBA_GetRcvCbsList();
    usRcvCbsNum   = TAF_CBA_GetRcvCbsNum();

    if (ulDelInx >= TAF_CBA_MAX_CBS_RECORD_NUM)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CBA_DelCbsRecord: ERR,ulDelIndex error !");
        return;
    }

    if (0 == usRcvCbsNum)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CBA_DelCbsRecord: ERR,RcvCbsNum 0!");
        return;
    }

    ulLastRecordInx = usRcvCbsNum - 1;

    if (ulDelInx > ulLastRecordInx)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CBA_DelCbsRecord: ERR,ulDelIndex > ulLastRecordInx!");
        return;
    }

    /* 可维可测 */
    TAF_CBA_SndOmDeledRecordInfo(TAF_CBA_OM_MSG_DEL_DEL_CBS_RECORD,
                                 enDelReason,
                                 &pstRcvCbsList[ulDelInx]);


    /* 依次将后续的记录前移, 覆盖要删除的记录 */
    for ( ulCurrInx = ulDelInx; ulCurrInx < ulLastRecordInx; ulCurrInx++ )
    {
        pstRcvCbsList[ulCurrInx] = pstRcvCbsList[ulCurrInx+1];
    }

    /* 使队尾的记录失效 */
    PS_MEM_SET(&pstRcvCbsList[ulLastRecordInx],
               0x00,
               sizeof(TAF_CBA_RECORD_STRU));

    /* 记录个数减 1, 并保存记录个数 */
    usRcvCbsNum--;
    TAF_CBA_SetRcvCbsNum(usRcvCbsNum);
}

#if (FEATURE_ETWS == FEATURE_ON)
/*****************************************************************************
 函 数 名  : TAF_CBA_DelEtwsPrimNtfExpiredRecord
 功能描述  : 删除重复检测时长超时的ETWS主通知记录
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月9日
    作    者   : l00171473
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_CBA_DelEtwsPrimNtfExpiredRecord(VOS_VOID)
{
    TAF_CBA_RECORD_STRU                *pstRcvPrimNtfList;
    VOS_UINT16                          usInx;

    usInx             = 0;
    pstRcvPrimNtfList = TAF_CBA_GetRcvEtwsPrimNtfList();

    /* 检查和删除超时的ETWS主通知 */
    while ( usInx < TAF_CBA_GetRcvEtwsPrimNtfNum() )
    {
        if ( VOS_TRUE != TAF_CBA_IsRecordExpired(&pstRcvPrimNtfList[usInx]) )
        {
            usInx++;
            continue;
        }

        TAF_CBA_DelEtwsPrimNtfRecord(usInx, TAF_CBA_OM_DEL_REASON_TIMEOUT);
    }

}
#endif

/*****************************************************************************
 函 数 名  : TAF_CBA_DelCbmiRangeListItemByInx
 功能描述  : 根据Index 删除CBMI RANG LIST中的指定项
 输入参数  : usDelItemInx:需删除的CB MID Range的 index
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月26日
      作    者   : l00171473
      修改内容   : 新生成函数 for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
VOS_VOID TAF_CBA_DelCbmiRangeListItemByInx(
    VOS_UINT16                          usDelItemInx
)
{
    TAF_CBA_CBMI_RANGE_STRU            *pstCbmiRangeListHead;
    VOS_UINT16                          usCbmiRangNum;
    VOS_UINT16                          usLastItemInx;
    VOS_UINT16                          usInx;

    pstCbmiRangeListHead = TAF_CBA_GetCbmiRangeListHead();
    usCbmiRangNum        = TAF_CBA_GetCbmiRangNum();

    /* CBMIR 个数错误检查 */
    if ( (0 == usCbmiRangNum)
      || (usCbmiRangNum > TAF_CBA_MAX_CBMID_RANGE_NUM) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CBA_DelCbmiRangeListItemByInx: usCbmiRangNum ERROR!");
        return;
    }

    /* usDelItemInx 参数检查 */
    if ( (usDelItemInx > (TAF_CBA_MAX_CBMID_RANGE_NUM-1) )
      || (usDelItemInx > (usCbmiRangNum-1) ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CBA_DelCbmiRangeListItemByInx: usCbmiRangNum ERROR!");
        return;
    }

    usLastItemInx = (usCbmiRangNum - 1);

    /* 依次将后续的记录前移, 覆盖要删除的记录 */
    for ( usInx = usDelItemInx; usInx < usLastItemInx; usInx++ )
    {
        pstCbmiRangeListHead[usInx] = pstCbmiRangeListHead[usInx+1];
    }

    /* 使队尾的记录失效 */
    PS_MEM_SET(&pstCbmiRangeListHead[usLastItemInx],
               0x00,
               sizeof(TAF_CBA_CBMI_RANGE_STRU));

    /* 记录个数减 1, 并保存记录个数 */
    usCbmiRangNum--;
    TAF_CBA_SetCbmiRangeNum(usCbmiRangNum);

}

/*****************************************************************************
 函 数 名  : TAF_CBA_DelCbMiRangeListFromActiveList
 功能描述  : 删除内存中的CBMI Range
 输入参数  : pstOrgCbMirList:需删除的CB MID Range列表
 输出参数  : 无
 返 回 值  : VOS_TRUE : 删除成功
             VOS_FALSE: 删除失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月26日
      作    者   : t00212959
      修改内容   : 新生成函数 for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
VOS_UINT32 TAF_CBA_DelCbMiRangeListFromActiveList(
    TAF_CBA_CBMI_RANGE_LIST_STRU       *pstOrgCbMirList
)
{
    VOS_UINT16                          usIndex;
    VOS_UINT32                          ulRet;
    TAF_CBA_CBMI_RANGE_LIST_STRU       *pstDstCbMirList;
    TAF_CBA_CBMI_RANGE_STRU            *pstOrigCbMirInfo;
    VOS_UINT32                          ulCbmidIdx;
    VOS_UINT32                          ulDelCbmirListFlg;

    pstDstCbMirList = TAF_CBA_GetCbMiRangeList();

    /* 此处认为系统出错 */
    if ( pstOrgCbMirList->usCbmirNum >=  TAF_CBA_MAX_CBMID_RANGE_NUM)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CBA_DelCbMiRangeListFromActiveList:usCbmirNum exceeds max ");

        return VOS_FALSE;
    }

    ulDelCbmirListFlg = VOS_FALSE;

    pstOrigCbMirInfo  = pstOrgCbMirList->astCbmiRangeInfo;

    for ( usIndex = 0 ; usIndex < pstOrgCbMirList->usCbmirNum ; usIndex++ )
    {
        ulRet = TAF_CBA_IsCbmirExist(&(pstOrigCbMirInfo[usIndex]),
                                     pstDstCbMirList,
                                     &ulCbmidIdx);

        /* 相同的则需要删除 */
        if ( VOS_TRUE == ulRet )
        {
            TAF_CBA_DelCbmiRangeListItemByInx((VOS_UINT16)ulCbmidIdx);

            ulDelCbmirListFlg = VOS_TRUE;
        }
    }

    return ulDelCbmirListFlg;
}

#if (FEATURE_ETWS == FEATURE_ON)
/*****************************************************************************
 函 数 名  : TAF_CBA_DelInvalidEtwsPrimNtfRecordByGsChgType
 功能描述  : 从ETWS主通知历史记录表中删除GS失效的ETWS主通知记录
 输入参数  : enGsChgType   : GS变化类型
             ucGsChgNetMode: 网络模式
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月12日
    作    者   : l00171473
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_CBA_DelInvalidEtwsPrimNtfRecordByGsChgType(
    TAF_CBS_GS_CHG_TYPE_ENUM_UINT8      enGsChgType,
    TAF_CBA_NET_RAT_TYPE_ENUM_UINT8     enGsChgNetMode
)
{
    TAF_CBA_RECORD_STRU                *pstRcvList;
    VOS_UINT16                          usInx;
    VOS_UINT32                          ulIsValid;

    /* 删除GS失效的主通知记录 */
    usInx       = 0;
    pstRcvList  = TAF_CBA_GetRcvEtwsPrimNtfList();

    while ( usInx < TAF_CBA_GetRcvEtwsPrimNtfNum() )
    {
        /* 检查网络模式 */
        if (pstRcvList[usInx].enNetMode != enGsChgNetMode)
        {
            usInx++;
            continue;
        }

        /* 地理变化类型和GS匹配 */
        ulIsValid = TAF_CBA_IsRecordValidByGsChgType(pstRcvList[usInx].usSN, enGsChgType);

        if (VOS_TRUE == ulIsValid)
        {
            usInx++;
            continue;
        }

        /* 删除无效主通知记录项 */
        TAF_CBA_DelEtwsPrimNtfRecord(usInx, TAF_CBA_OM_DEL_REASON_GS_CHG);
    }
}
#endif

/*****************************************************************************
 函 数 名  : TAF_CBA_DelCbsExpiredRecord
 功能描述  : 删除CBS历史记录表中重复检测时长超时的CBS记录项
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月10日
    作    者   : l00171473
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_CBA_DelCbsExpiredRecord(VOS_VOID)
{
    TAF_CBA_RECORD_STRU                *pstRcvCbsList;
    VOS_UINT16                          ulInx;

    pstRcvCbsList = TAF_CBA_GetRcvCbsList();
    ulInx         = 0;

    /* 检查和删除超时的CBS记录，该记录表中可能有从通知也有CBS消息, CBS消息是一直有效的 */
    while ( ulInx < TAF_CBA_GetRcvCbsNum() )
    {
        if ( VOS_FALSE == TAF_CBA_IsRecordExpired(&pstRcvCbsList[ulInx]) )
        {
            ulInx++;
            continue;
        }

        /* 删除该超时记录 */
        TAF_CBA_DelCbsRecord(ulInx, TAF_CBA_OM_DEL_REASON_TIMEOUT);
    }
}

/*****************************************************************************
 函 数 名  : TAF_CBA_DelInvalidCbsRecordByActiveList
 功能描述  : 删除不在激活列表中的CBS记录
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月12日
    作    者   : l00171473
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_CBA_DelInvalidCbsRecordByActiveList(VOS_VOID)
{
    TAF_CBA_RECORD_STRU                *pstRcvCbsList;
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          ulIsValid;

    ulIndex       = 0;
    pstRcvCbsList = TAF_CBA_GetRcvCbsList();

    while( ulIndex < TAF_CBA_GetRcvCbsNum() )
    {
        ulIsValid = TAF_CBA_IsMsgIdInCbsActiveList(pstRcvCbsList[ulIndex].usMsgID);

        if (VOS_TRUE == ulIsValid)
        {
            ulIndex++;
            continue;
        }

        /* 删除无效CBS记录项 */
        TAF_CBA_DelCbsRecord(ulIndex, TAF_CBA_OM_DEL_REASON_USER);
    }
}


/*****************************************************************************
 函 数 名  : TAF_CBA_DelInvalidCbsRecordByGsChgType
 功能描述  : 删除GS失效的CBS记录
 输入参数  : enGsChgType: GS变化类型
             ucGsChgNetMode: 网络模式
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月12日
    作    者   : l00171473
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_CBA_DelInvalidCbsRecordByGsChgType(
    TAF_CBS_GS_CHG_TYPE_ENUM_UINT8      enGsChgType,
    TAF_CBA_NET_RAT_TYPE_ENUM_UINT8     enGsChgNetMode
)
{
    TAF_CBA_RECORD_STRU                *pstRcvCbsList;
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          ulIsValid;

    ulIndex       = 0;
    pstRcvCbsList = TAF_CBA_GetRcvCbsList();

    while ( ulIndex < TAF_CBA_GetRcvCbsNum() )
    {
        /* 检查网络模式 */
        if (pstRcvCbsList[ulIndex].enNetMode != enGsChgNetMode)
        {
            ulIndex++;
            continue;
        }

        /* 地理变化类型和GS匹配 */
        ulIsValid = TAF_CBA_IsRecordValidByGsChgType(pstRcvCbsList[ulIndex].usSN, enGsChgType);

        if (VOS_TRUE == ulIsValid)
        {
            ulIndex++;
            continue;
        }

        /* 删除无效CBS记录项 */
        TAF_CBA_DelCbsRecord(ulIndex, TAF_CBA_OM_DEL_REASON_GS_CHG);
    }
}

#if (FEATURE_ETWS == FEATURE_ON)
/*****************************************************************************
 函 数 名  : TAF_CBA_DelInvalidEtwsPrimNtfRecordByActiveList
 功能描述  : 删除不在激活列表中的ETWS主通知记录
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月12日
    作    者   : l00171473
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_CBA_DelInvalidEtwsPrimNtfRecordByActiveList(VOS_VOID)
{
    TAF_CBA_RECORD_STRU                *pstRcvList;
    VOS_UINT16                          usInx;
    VOS_UINT32                          ulIsValid;

    usInx       = 0;
    pstRcvList  = TAF_CBA_GetRcvEtwsPrimNtfList();

    while (usInx < TAF_CBA_GetRcvEtwsPrimNtfNum())
    {
        ulIsValid = TAF_CBA_IsMsgIdInCbsActiveList(pstRcvList[usInx].usMsgID);

        if (VOS_TRUE == ulIsValid)
        {
            usInx++;
            continue;
        }

        /* 删除无效主通知记录项 */
        TAF_CBA_DelEtwsPrimNtfRecord(usInx, TAF_CBA_OM_DEL_REASON_USER);
    }
}
#endif

/*****************************************************************************
 函 数 名  : TAF_CBA_DelRecordByActiveList
 功能描述  : 用户设置激活列表后, 删除不在激活列表中的历史记录项
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月27日
    作    者   : l00171473
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_CBA_DelRecordByActiveList(VOS_VOID)
{
#if (FEATURE_ON == FEATURE_ETWS)
    TAF_CBA_DelInvalidEtwsPrimNtfRecordByActiveList();
#endif

    TAF_CBA_DelInvalidCbsRecordByActiveList();
}

/*****************************************************************************
 函 数 名  : TAF_CBA_SortCbmiRangeList
 功能描述  : 将RANGE LIST的MSG ID从小到大排序
 输入参数  : pstRangeList:需要排序的range list
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月1日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_CBA_SortCbmiRangeList(
    TAF_CBA_CBMI_RANGE_LIST_STRU       *pstRangeList
)
{
    VOS_UINT32                          ulIndex;
    VOS_UINT16                          usTmpMsgId;

    /* AT设置过来的MID列表MSG ID需要调整为小的MSG ID
       放到usMsgIdFrom中,大的MSG ID放到usMsgIdTo中 */
    for (ulIndex = 0; ulIndex< pstRangeList->usCbmirNum; ulIndex++)
    {
        if (pstRangeList->astCbmiRangeInfo[ulIndex].usMsgIdFrom >
                        pstRangeList->astCbmiRangeInfo[ulIndex].usMsgIdTo)
        {
            usTmpMsgId = pstRangeList->astCbmiRangeInfo[ulIndex].usMsgIdFrom;
            pstRangeList->astCbmiRangeInfo[ulIndex].usMsgIdFrom = pstRangeList->astCbmiRangeInfo[ulIndex].usMsgIdTo;
            pstRangeList->astCbmiRangeInfo[ulIndex].usMsgIdTo   = usTmpMsgId;
        }
    }
}

/*****************************************************************************
 函 数 名  : TAF_CBA_SortEtwsRangList
 功能描述  : 将ETWS的RANGE LIST的MSG ID从小到大排序
 输入参数  : pstEtwsRangeList:需要排序的range list
             ulMaxNum        :元素的个数
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月4日
    作    者   : l00171473
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_CBA_SortEtwsRangList(
    TAF_CBA_ETWS_MSGID_RANGE_STRU      *pstEtwsRangeList,
    VOS_UINT32                          ulMaxNum
)
{
    VOS_UINT32                          ulInx;
    VOS_UINT16                          usTmpMsgId;

    for ( ulInx = 0; ulInx <ulMaxNum; ulInx++ )
    {
        if (pstEtwsRangeList[ulInx].usMsgIdFrom > pstEtwsRangeList[ulInx].usMsgIdTo)
        {
            usTmpMsgId = pstEtwsRangeList[ulInx].usMsgIdFrom;

            pstEtwsRangeList[ulInx].usMsgIdFrom = pstEtwsRangeList[ulInx].usMsgIdTo;
            pstEtwsRangeList[ulInx].usMsgIdTo   = usTmpMsgId;
        }
    }
}

/*****************************************************************************
 函 数 名  : TAF_CBA_GetGsChgTypeByNetworkInfo
 功能描述  : 通过当前的网络信息和上次的网络信息比较获取GS 变化类型
 输入参数  : pstCurrNetworkInfo    : 当前的网络信息
             pstOldGsChgNetworkInfo: 上次的网络信息
 输出参数  : 无
 返 回 值  : GS 变化类型
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月4日
    作    者   : l00171473
    修改内容   : 新生成函数

*****************************************************************************/
TAF_CBS_GS_CHG_TYPE_ENUM_UINT8 TAF_CBA_GetGsChgTypeByNetworkInfo(
    TAF_CBA_NETWORK_INFO_STRU          *pstCurrNetworkInfo,
    TAF_CBA_NETWORK_INFO_STRU          *pstOldGsChgNetworkInfo
)
{
    if ( (pstCurrNetworkInfo->stCurPlmn.ulMcc != pstOldGsChgNetworkInfo->stCurPlmn.ulMcc)
      || (pstCurrNetworkInfo->stCurPlmn.ulMnc != pstOldGsChgNetworkInfo->stCurPlmn.ulMnc) )
    {
        return TAF_CBS_GS_CHG_TYPE_CHG_PLMN;
    }

    if ( pstCurrNetworkInfo->usSa != pstOldGsChgNetworkInfo->usSa )
    {
        return TAF_CBS_GS_CHG_TYPE_CHG_SA;
    }

    if ( pstCurrNetworkInfo->ulCellId != pstOldGsChgNetworkInfo->ulCellId )
    {
        return TAF_CBS_GS_CHG_TYPE_CHG_CELL;
    }

    return TAF_CBS_GS_CHG_TYPE_NO_CHG;
}

#endif /* ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS)) */
/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
