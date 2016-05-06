/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafCbaProcAs.c
  版 本 号   : 初稿
  作    者   : l00171473
  生成日期   : 2012年3月19日
  最近修改   :
  功能描述   : CBA模块对接入层的消息处理
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
#include  "TafCbaProcAs.h"
#include  "TafCbaComFunc.h"
#include  "TafCbaProcEtwsPrimNtf.h"
#include  "TafCbaProcNvim.h"
#include  "TafCbaMntn.h"
#include  "TafCbaProcUsim.h"
#include  "TafCbaProcAt.h"

#include  "MnComm.h"
#include  "mnmsgcbencdec.h"
#include  "MnMsgReport.h"
#include  "MnMsgTimerProc.h"
#include  "TafLog.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_CBA_PROC_AS_C


#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
  3 函数实现
*****************************************************************************/


/*****************************************************************************
 函 数 名  : TAF_CBA_ProcGasMsg
 功能描述  : 处理来自GAS模块的消息
 输入参数  : pstMsg: 来自GAS模块的VOS 消息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月19日
    作    者   : l00171473
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_CBA_ProcGasMsg(
    struct MsgCB                       *pstMsg
)
{
    TAF_CBS_MSG_DATA                   *pstMsgData;

    pstMsgData = (TAF_CBS_MSG_DATA *)pstMsg;
    switch (pstMsgData->enMsgID)
    {
        case ID_GAS_CBS_CFG_CNF:
            TAF_CBA_RcvAsCbsCfgCnf((BMC_CBS_CFG_CNF_STRU *)pstMsg);
            break;

        case ID_GAS_CBS_DATA_IND :
            TAF_CBA_RcvGasCbsDataInd((GAS_CBS_DATA_IND_STRU *)pstMsg);
            break;

        case ID_RR_CBS_GS_STATUS_CHANGE_IND:
            TAF_CBA_RcvAsGsStatusChangeInd((RR_CBS_GS_STATUS_CHANGE_IND_STRU *)pstMsg);
            break;

        default:
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CBA_ProcGasMsg:Invalid Msg");
            break;
    }
}


/*****************************************************************************
 函 数 名  : TAF_CBA_ProcWrrMsg
 功能描述  : 处理来自WRR的消息
 输入参数  : pstMsg: 来自WRR模块的VOS消息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月19日
    作    者   : l00171473
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_CBA_ProcWrrMsg(
    struct MsgCB                       *pstMsg
)
{
    TAF_CBS_MSG_DATA                   *pstMsgData;

    pstMsgData = (TAF_CBS_MSG_DATA *)pstMsg;
    switch (pstMsgData->enMsgID)
    {
#if (FEATURE_ETWS == FEATURE_ON)
        case ID_RR_CBS_ETWS_PRIMARY_NOTIFY_IND:
            TAF_CBA_RcvAsEtwsPrimNotifyInd((RR_CBS_ETWS_PRIMARY_NOTIFY_IND_STRU *)pstMsg);
            break;
#endif
        case ID_RR_CBS_GS_STATUS_CHANGE_IND:
            TAF_CBA_RcvAsGsStatusChangeInd((RR_CBS_GS_STATUS_CHANGE_IND_STRU *)pstMsg);
            break;

        default:
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CBA_ProcWrrMsg:Invalid Msg");
            break;
    }
}

/*****************************************************************************
 函 数 名  : TAF_CBA_ProcBmcMsg
 功能描述  : 处理来自BMC的消息
 输入参数  : pstMsg: 来自BMC模块的VOS消息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月19日
    作    者   : l00171473
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_CBA_ProcBmcMsg(
    struct MsgCB                       *pstMsg
)
{
    TAF_CBS_MSG_DATA                   *pstMsgData;

    pstMsgData = (TAF_CBS_MSG_DATA *)pstMsg;
    switch (pstMsgData->enMsgID)
    {
        case ID_BMC_CBS_CFG_CNF:
            TAF_CBA_RcvAsCbsCfgCnf((BMC_CBS_CFG_CNF_STRU *)pstMsg);
            break;

        case ID_BMC_CBS_DATA_IND :
            TAF_CBA_RcvBmcCbsDataInd((BMC_CBS_DATA_IND_STRU *)pstMsg);
            break;

        default:
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CBA_ProcBmcMsg:Invalid Msg");
            break;
    }
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : TAF_CBA_ProcLrrcMsg
 功能描述  : 处理来自LRRC的消息
 输入参数  : pstMsg: 来自LRRC模块的VOS消息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月19日
    作    者   : l00171473
    修改内容   : 新生成函数
  2.日    期   : 2014年8月27日
    作    者   : w00242748
    修改内容   : DTS2014082004813:L下ERRC给TAF报CBS消息，优先于MMC给TAF报系统消息，
                 当先收到CBS消息时，由于会判断当前是否驻留在LTE下，如果不在，则会直接丢弃。

*****************************************************************************/
VOS_VOID TAF_CBA_ProcLrrcMsg(
    struct MsgCB                       *pstMsg
)
{
    TAF_CBS_MSG_DATA                   *pstMsgData;

    pstMsgData = (TAF_CBS_MSG_DATA *)pstMsg;
    switch (pstMsgData->enMsgID)
    {
#if (FEATURE_ETWS == FEATURE_ON)
        case ID_RR_CBS_ETWS_PRIMARY_NOTIFY_IND:
            TAF_CBA_RcvAsEtwsPrimNotifyInd((RR_CBS_ETWS_PRIMARY_NOTIFY_IND_STRU *)pstMsg);
            break;
#endif

        case ID_LRRC_CBS_DATA_IND:
            TAF_CBA_SetNetRatType(TAF_CBA_NET_RAT_TYPE_LTE);
            TAF_CBA_RcvLrrcCbsDataInd((LRRC_CBS_DATA_IND_STRU *)pstMsg);
            break;

        case ID_RR_CBS_GS_STATUS_CHANGE_IND:
            TAF_CBA_RcvAsGsStatusChangeInd((RR_CBS_GS_STATUS_CHANGE_IND_STRU *)pstMsg);
            break;

        default:
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CBA_ProcLrrcMsg:Invalid Msg");
            break;
    }

}

#endif  /* (FEATURE_ON == FEATURE_LTE) */

/*****************************************************************************
 函 数 名  : TAF_CBA_RcvAsCbsCfgCnf
 功能描述  : 处理接入层发送过来的激活CBS的CNF消息
 输入参数  : pstActiveCnf: As发送的激活CBS的CNF消息
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月19日
    作    者   : l00171473
    修改内容   : 新生成函数, for V7R1C50 CSFB&PPAC&ETWS&ISR
  2.日    期   : 2012年12月11日
    作    者   : l00167671
    修改内容   : DTS2012121802573, TQE清理

*****************************************************************************/
VOS_VOID TAF_CBA_RcvAsCbsCfgCnf(
    BMC_CBS_CFG_CNF_STRU             *pstCfgCnf
)
{

    if ( TAF_CBS_CFG_RSLT_FAIL == pstCfgCnf->enRslt )
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_CBA_RcvAsCbsCfgCnf: Active cnf fail");
    }

}

/*****************************************************************************
 函 数 名  : TAF_CBA_RcvGasCbsDataInd
 功能描述  : 处理G模下收到的CBS消息
 输入参数  : pstGasDataInd  - GAS发送过来的CBS消息
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月19日
    作    者   : l00171473
    修改内容   : 新生成函数, for V7R1C50 CSFB&PPAC&ETWS&ISR
  2.日    期   : 2012年12月10日
    作    者   : l00171473
    修改内容   : for DTS2012120609682,终端要求CBS统一上报88个字节
  3.日    期   : 2013年8月13日
    作    者   : w00242748
    修改内容   : for DTS2013080904352,错误页筛选过滤
*****************************************************************************/
VOS_VOID TAF_CBA_RcvGasCbsDataInd(
    GAS_CBS_DATA_IND_STRU              *pstGasDataInd
)
{
    VOS_UINT8                           ucPageLen;
    MN_MSG_CBRAW_TS_DATA_STRU          *pstCbRawData;
    VOS_UINT8                           ucPageNum;
    MN_MSG_CBGSMPAGE_STRU              *pstGsmPage;
    TAF_CBA_RECORD_STRU                 stNewRecord;
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucTotalPage;
    VOS_UINT8                           ucPageIndex;

    pstCbRawData = (MN_MSG_CBRAW_TS_DATA_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(MN_MSG_CBRAW_TS_DATA_STRU) * (pstGasDataInd->ucPageNum));
    if ( VOS_NULL_PTR == pstCbRawData )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CBA_RcvGasCbsDataInd:Alloc Mem Failed");
        return;
    }


    PS_MEM_SET(pstCbRawData, 0x00, sizeof(MN_MSG_CBRAW_TS_DATA_STRU) * (pstGasDataInd->ucPageNum));

    ucPageNum = 0;
    for ( ucIndex = 0 ; ucIndex < pstGasDataInd->ucPageNum; ucIndex++ )
    {
        /* 将每段CBS的长度去除填充值,更新为实际的长度 */

        if ( VOS_TRUE == TAF_CBA_GetRptAppFullPageFlg() )
        {
            ucPageLen = (VOS_UINT8)(pstGasDataInd->astPageData[ucIndex].ulLength);
        }
        else
        {
            ucPageLen = TAF_CBA_GetGsmCbsPageLen(&(pstGasDataInd->astPageData[ucIndex]));
        }

        /* 如果长度小于头的长度,则不上报 */
        if ( ucPageLen < TAF_CBA_MAX_CB_HEADER_LEN )
        {
            /* 可维可测 */
            TAF_CBA_SndOmLogInfo(TAF_CBA_OM_LOG_PAGELEN_INVALID);
            continue;
        }

        pstGsmPage = (MN_MSG_CBGSMPAGE_STRU*)pstGasDataInd->astPageData[ucIndex].aucData;

        /* 判断该页的索引值是否大于总页数 */
        ucTotalPage = pstGsmPage->Pagesbit4;
        ucPageIndex = pstGsmPage->Pagebit4;

        /* 如果 ucTotalPage或ucPageNumber中一个为0,则当作 0001 0001 ,参见协议23041 9.4.1.2.4 */
        if ( ( 0x00 == ucTotalPage )
          || ( 0x00 == ucPageIndex ) )
        {
            ucTotalPage = 0x01;
            ucPageIndex = 0x01;
        }

        if (ucPageIndex > ucTotalPage)
        {
            /* 可维可测 */
            TAF_CBA_SndOmLogInfo(TAF_CBA_OM_LOG_PAGEINDEX_INVALID);
            continue;
        }

        /* 判断CBS消息的MSG ID是否在激活列表中，不在则继续比较下页 */
        if ( VOS_TRUE != TAF_CBA_IsCbsMsgIdValid( TAF_CBA_BuildCbsMsgId(pstGsmPage->ucMIdHigh, pstGsmPage->ucMIdLow)) )
        {
            /* 可维可测 */
            TAF_CBA_SndOmLogInfo(TAF_CBA_OM_LOG_CBS_MSGID_INVALID);
            continue;
        }

        /* 删除重复检测时长超时的CBS记录 */
        TAF_CBA_DelCbsExpiredRecord();

        /* 构造数据记录 */
        TAF_CBA_BuildGsmCbsRecord(pstGsmPage, &pstGasDataInd->stCurrNetworkInfo, &stNewRecord);

        /* 检查是否是重复的消息页, 重复的消息页不用保存和上报到AT */
        if (VOS_TRUE == TAF_CBA_IsDupGsmCbsRecord(&stNewRecord))
        {
            continue;
        }

        /* 保存该记录项 */
        TAF_CBA_SaveGsmCbsRecord(&stNewRecord);

        pstCbRawData[ucIndex].ulLen = ucPageLen;
        PS_MEM_CPY(pstCbRawData[ucIndex].aucData,
                   pstGasDataInd->astPageData[ucIndex].aucData,
                   ucPageLen);

        ucPageNum++;
    }

    /* 无有效页则不用上报 */
    if (ucPageNum > 0)
    {
        /* 调用统一的处理函数上报CBS或Envelope到USIM */
        TAF_CBA_ReportRcvCbsData(ucPageNum, pstCbRawData);
    }

    PS_MEM_FREE(WUEPS_PID_TAF, pstCbRawData);
}

/*****************************************************************************
 函 数 名  : TAF_CBA_ConverBmcCbsToGsmCbsFormat
 功能描述  : BMC发送过来的消息模拟为从GAS发送的CBS消息
 输入参数  : pstDataPdu:BMC发送过来的CBS消息内容
 输出参数  : pucPageNum:CBS消息页数
             pstPageDataInd:CBS消息内容
 返 回 值  : VOS_UINT32:VOS_OK,处理成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年5月10日
    作    者   : zhoujun /z40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_CBA_ConvertBmcCbsToGsmCbsFormat(
    BMC_CBS_DATA_IND_STRU              *pstDataPdu,
    VOS_UINT8                          *pucPageNum,
    MN_MSG_CBRAW_TS_DATA_STRU          *pstPageDataInd
)
{

    VOS_UINT8                           ucPageIdx;
    VOS_UINT32                          ulIndex;
    MN_MSG_CBGSMPAGE_STRU              *pstGsmPage;
    VOS_UINT8                           ucPageSegment;
    VOS_UINT8                           ucPageSegmentOffset;
    VOS_UINT8                           ucPageNumInMsg;
    VOS_UINT16                          usLeftLength;
    TAF_CBA_CB_W_AIR_DATA_STRU         *pstCbWData;

    *pucPageNum     = 0;
    ucPageIdx       = 1;

    

    /*
    23041 9.4.2.2.5 CBDATA
    -    Number-of-Pages;
    - CBS-Message-Information-Page;
    - CBS-Message-Information-Length.
    Octet Number(s) Parameter
    1 Number-of-Pages
    2 – 83 CBS-Message-Information-Page 1
    84 CBS-Message-Information-Length 1
     … …
    CBS-Message-Information-Page n
    CBS-Message-Information-Length n

    */

    /*  由于消息中携带了Page个数,填充到消息内容中以消息中携带的Page个数为准,
        但获取页数需要综合考虑消息长度和消息中携带的页数 */
    if ( pstDataPdu->usCBDataLen <= TAF_CBA_CB_W_NUM_OF_PAGES_POS )
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_CBA_ConvertBmcCbsToGsmCbsFormat: CbDataLen too small");
        return VOS_ERR;
    }

    /* 第0个字节表示页数 */
    ucPageNumInMsg = pstDataPdu->aucCBData[0];

    /* 计算当前CBS消息的长度的分段 */
    ucPageSegmentOffset = (pstDataPdu->usCBDataLen
                - TAF_CBA_CB_W_NUM_OF_PAGES_POS)%TAF_CBA_MAX_CB_PAGE_LEN;

    ucPageSegment = (VOS_UINT8)((pstDataPdu->usCBDataLen
                - TAF_CBA_CB_W_NUM_OF_PAGES_POS)/TAF_CBA_MAX_CB_PAGE_LEN);

    if ( 0 != ucPageSegmentOffset )
    {
        ucPageSegment++;
    }

    /* 页数不正确,则直接返回 */
    if ( ( 0 == ucPageNumInMsg ) || ( 0 == ucPageSegment ) )
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_CBA_ConvertBmcCbsToGsmCbsFormat:Empty CbDataLen");
        return VOS_ERR;
    }

    *pucPageNum = ucPageSegment;

    if ( *pucPageNum > TAF_CBA_MAX_CBMPAGE_NUM )
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_CBA_ConvertBmcCbsToGsmCbsFormat:Too Long CbDataLen");
        *pucPageNum = TAF_CBA_MAX_CBMPAGE_NUM;
    }

    pstCbWData = (TAF_CBA_CB_W_AIR_DATA_STRU *)(&(pstDataPdu->aucCBData[TAF_CBA_CB_W_NUM_OF_PAGES_POS]));

    /* 将整个CBS消息模拟为G模下CBS消息的格式 */
    usLeftLength = pstDataPdu->usCBDataLen - TAF_CBA_CB_W_NUM_OF_PAGES_POS;

    for ( ulIndex = 0 ; ulIndex < *pucPageNum ; ulIndex++ )
    {
        pstGsmPage = (MN_MSG_CBGSMPAGE_STRU *)(pstPageDataInd->aucData);

        pstGsmPage->ucDCS     = pstDataPdu->ucDataCodeScheme;
        pstGsmPage->ucSnHigh  = (VOS_UINT8)((pstDataPdu->usSerialNum & 0xFF00) >> 8);
        pstGsmPage->ucSnLow   = (VOS_UINT8)(pstDataPdu->usSerialNum & 0x00FF);
        pstGsmPage->ucMIdHigh = (VOS_UINT8)((pstDataPdu->usCBMID & 0xFF00) >> 8);
        pstGsmPage->ucMIdLow  = (VOS_UINT8)((pstDataPdu->usCBMID & 0x00FF));
        pstGsmPage->Pagebit4  = ucPageIdx;
        pstGsmPage->Pagesbit4 = ucPageNumInMsg;

        /* 获取当前CBS消息的有效长度 */
        if (usLeftLength >= TAF_CBA_MAX_CB_PAGE_LEN)
        {
            if ( VOS_TRUE == TAF_CBA_GetRptAppFullPageFlg() )
            {
                pstPageDataInd->ulLen = TAF_CBA_MAX_CBDATA_LEN   + TAF_CBA_MAX_CB_HEADER_LEN;
            }
            else
            {
                pstPageDataInd->ulLen = pstCbWData->ucCbsDataLen + TAF_CBA_MAX_CB_HEADER_LEN;
            }

            /*此处需要进行保护以免网络数据出错*/
            if ( pstPageDataInd->ulLen > TAF_CBA_MAX_CBPAGE_LEN )
            {
                pstPageDataInd->ulLen = TAF_CBA_MAX_CBPAGE_LEN;
            }
            PS_MEM_CPY(pstGsmPage->aucContent,
                   pstCbWData->aucCbsData,
                   TAF_CBA_MAX_CBDATA_LEN);

            usLeftLength -= TAF_CBA_MAX_CB_PAGE_LEN;
        }
        else
        {
            pstPageDataInd->ulLen = usLeftLength + TAF_CBA_MAX_CB_HEADER_LEN;

            PS_MEM_CPY(pstGsmPage->aucContent,
                       pstCbWData->aucCbsData,
                       usLeftLength);
            break;
        }
        ucPageIdx++;
        pstCbWData++;
        pstPageDataInd++;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_CBA_RcvBmcCbsDataInd
 功能描述  : 处理BMC发送过来的DATA_IND 消息
             LRRC发送CBS消息时采用的与BMC相同的数据结构, 故LRRC的CBS消息处理也调用此处理
 输入参数  : pstBmcDataInd  - BMC发送过来的CBS消息
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月19日
    作    者   : l00171473
    修改内容   : 新生成函数, for V7R1C50 CSFB&PPAC&ETWS&ISR
  2.日    期   : 2012年12月10日
    作    者   : l00171473
    修改内容   : for DTS2012120609682,终端要求CBS统一上报88个字节
*****************************************************************************/
VOS_VOID TAF_CBA_RcvBmcCbsDataInd(
    BMC_CBS_DATA_IND_STRU              *pstBmcDataInd
)
{
    MN_MSG_CBRAW_TS_DATA_STRU          *pstCbRawData;
    VOS_UINT8                           ucPageNum;
    VOS_UINT32                          ulRet;
    TAF_CBA_RECORD_STRU                 stNewRecord;

    /* 判断消息ID是否有效 */
    if (VOS_TRUE != TAF_CBA_IsCbsMsgIdValid(pstBmcDataInd->usCBMID))
    {
        /* 可维可测 */
        TAF_CBA_SndOmLogInfo(TAF_CBA_OM_LOG_CBS_MSGID_INVALID);
        return;
    }

    /* 检查和删除重复检测时长超时的CBS记录 */
    TAF_CBA_DelCbsExpiredRecord();

    /* 构造CBS消息数据记录 */
    TAF_CBA_BuildBmcCbsRecord(pstBmcDataInd, &stNewRecord);

    /* 检查是否是重复的消息, 重复的消息, 不用保存和上报到AT */
    if (VOS_TRUE == TAF_CBA_IsDupBmcCbsRecord(&stNewRecord))
    {
        return;
    }

    /* 保存记录 */
    TAF_CBA_SaveBmcCbsRecord(&stNewRecord);

    pstCbRawData = (MN_MSG_CBRAW_TS_DATA_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(MN_MSG_CBRAW_TS_DATA_STRU) * TAF_CBA_MAX_CBMPAGE_NUM);
    if (VOS_NULL_PTR == pstCbRawData)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CBA_RcvBmcCbsDataInd:Alloc Mem Failed");
        return;
    }


    PS_MEM_SET(pstCbRawData, 0x00, sizeof(MN_MSG_CBRAW_TS_DATA_STRU) * TAF_CBA_MAX_CBMPAGE_NUM);


    /* 由于上报的CBS内容是GSM模式的,所以需要将W格式的CBS消息转换为G模式的CBS消息内容 */
    ulRet = TAF_CBA_ConvertBmcCbsToGsmCbsFormat(pstBmcDataInd, &ucPageNum, pstCbRawData);
    if ( VOS_OK != ulRet )
    {
        PS_MEM_FREE(WUEPS_PID_TAF, pstCbRawData);
        return;
    }

    /* 调用统一的处理函数上报CBS或Envelope到USIM */
    TAF_CBA_ReportRcvCbsData(ucPageNum, pstCbRawData);

    PS_MEM_FREE(WUEPS_PID_TAF, pstCbRawData);
}

/*****************************************************************************
 函 数 名  : TAF_CBA_RcvLrrcCbsDataInd
 功能描述  : 处理LRRC发送过来的DATA_IND消息
 输入参数  : pstBmcDataInd  - LRRC发送过来的CBS消息
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月19日
    作    者   : l00171473
    修改内容   : 新生成函数, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
VOS_VOID TAF_CBA_RcvLrrcCbsDataInd(
    LRRC_CBS_DATA_IND_STRU             *pstBmcDataInd
)
{
    /* LRRC发送CBS消息时采用与BMC相同的数据结构, 故直接调用BMC的处理函数处理 */
    TAF_CBA_RcvBmcCbsDataInd((BMC_CBS_DATA_IND_STRU*)pstBmcDataInd);
}

/*****************************************************************************
 函 数 名  : TAF_CBA_RcvAsGsStatusChangeInd
 功能描述  : 处理接入层发送的GS变化消息
 输入参数  : pstGsChangeInd  - AS发送过来的GS CHANGE消息
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月19日
    作    者   : l00171473
    修改内容   : 新生成函数, for V7R1C50 CSFB&PPAC&ETWS&ISR
  2.日    期   : 2013年8月15日
    作    者   : w00242748
    修改内容   : DTS2013080608981 删除NAS修正CHG IND类型的代码

*****************************************************************************/
VOS_VOID TAF_CBA_RcvAsGsStatusChangeInd(
    RR_CBS_GS_STATUS_CHANGE_IND_STRU   *pstGsChangeInd
)
{
    TAF_CBS_GS_CHG_TYPE_ENUM_UINT8      enTmpGsChgType;
    TAF_CBA_NET_RAT_TYPE_ENUM_UINT8     enNetRatType;
    TAF_CBA_NETWORK_INFO_STRU           stCurrNetworkInfo;

    /* 通过SenderPid获取接入模式 */
    enNetRatType = TAF_CBA_GetRatTypeBySenderPid(pstGsChangeInd->ulSenderPid);

    if ( TAF_CBA_NET_RAT_TYPE_BUTT == enNetRatType )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CBA_RcvAsGsStatusChangeInd: ERR enNetRatType.");
        return;
    }

    /* 获取GS CHG 消息中的 CHG TYPE, 并做错误检查 */
    enTmpGsChgType = pstGsChangeInd->enGsChgType;

    if (enTmpGsChgType >= TAF_CBS_GS_CHG_TYPE_CHG_BUTT)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CBA_RcvAsGsStatusChangeInd: ERR GS CHG TYPE.");
        return;
    }

    /* 检查GS CHG 消息中的 网络信息 */
    if ( (VOS_TRUE != pstGsChangeInd->stCurrNetworkInfo.bitOpPlmnId)
      || (VOS_TRUE != pstGsChangeInd->stCurrNetworkInfo.bitOpSa)
      || (VOS_TRUE != pstGsChangeInd->stCurrNetworkInfo.bitOpCellId) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CBA_RcvAsGsStatusChangeInd: ERR NetworkInfo.");
        return;
    }

    /* 获取当前的网络信息 */
    PS_MEM_SET( &stCurrNetworkInfo, 0x00, sizeof(stCurrNetworkInfo) );

    stCurrNetworkInfo.enCurrNetRatType = enNetRatType;
    stCurrNetworkInfo.stCurPlmn.ulMcc  = pstGsChangeInd->stCurrNetworkInfo.stCurPlmn.ulMcc;
    stCurrNetworkInfo.stCurPlmn.ulMnc  = pstGsChangeInd->stCurrNetworkInfo.stCurPlmn.ulMnc;
    stCurrNetworkInfo.usSa             = pstGsChangeInd->stCurrNetworkInfo.usSa;
    stCurrNetworkInfo.ulCellId         = pstGsChangeInd->stCurrNetworkInfo.ulCellId;

    /* 获取上次 GS_STATUS_CHANGE_IND 中的网络信息 */

    /* 如果是异系统的场景, 需要重新判断GS CHG的类型.
       因为目前:
       W模, 网络信息全为有效值(只在IDLE和P态上报GS CHG IND).
            异系统过程中, 每次重新进入W驻留成功, W会向NAS上报GS_CHG_IND(变化类型依赖和W模全局变量中的网络信息的比较);
       G模, 网络信息都为有效值.
            异系统过程中, 每次重新进入G驻留成功, G会向NAS上报GS_CHG_IND(G模会清网络信息的全局变量, 所以都是PLMN变化);
       L模, 网络信息都为有效值.
            异系统过程中, 每次重新进入L驻留成功, L会向NAS上报GS_CHG_IND(变化类型和W类似)
    */

    /* 保存本次GS_STATUS_CHANGE_IND 中的网络信息 */
    TAF_CBA_SetOldNetworkInfo(&stCurrNetworkInfo);

    /* 未变化则不处理 */
    if ( (TAF_CBS_GS_CHG_TYPE_NO_CHG   == enTmpGsChgType)
      || (TAF_CBS_GS_CHG_TYPE_CHG_RAT  == enTmpGsChgType) )
    {
        return;
    }

#if (FEATURE_ETWS == FEATURE_ON)

    /* 删除主通知记录中的无效项 */
    TAF_CBA_DelInvalidEtwsPrimNtfRecordByGsChgType(enTmpGsChgType, enNetRatType);
#endif

    /* 删除CBS记录中的无效项 */
    TAF_CBA_DelInvalidCbsRecordByGsChgType(enTmpGsChgType, enNetRatType);

}

/*****************************************************************************
 函 数 名  : TAF_CBA_GetRatTypeBySenderPid
 功能描述  : 根据AS的SenderPid 获取接入模式类型
 输入参数  : ulSenderPid:  AS的SenderPid
 输出参数  : 无
 返 回 值  : TAF_CBA_NET_RAT_TYPE_ENUM_UINT8: 接入模式
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月19日
    作    者   : l00171473
    修改内容   : 新生成函数, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
TAF_CBA_NET_RAT_TYPE_ENUM_UINT8 TAF_CBA_GetRatTypeBySenderPid(
    VOS_UINT32                          ulSenderPid
)
{
    TAF_CBA_NET_RAT_TYPE_ENUM_UINT8     enNetRatType;

    switch (ulSenderPid)
    {
        case WUEPS_PID_WRR:
        case WUEPS_PID_BMC:

            enNetRatType = TAF_CBA_NET_RAT_TYPE_WCDMA;
            break;

        case UEPS_PID_GAS:

            enNetRatType = TAF_CBA_NET_RAT_TYPE_GSM;
            break;

#if (FEATURE_ON == FEATURE_LTE)
        case PS_PID_ERRC:

            enNetRatType = TAF_CBA_NET_RAT_TYPE_LTE;
            break;
#endif

        default:

            enNetRatType = TAF_CBA_NET_RAT_TYPE_BUTT;
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CBA_GetRatTypeBySenderPid: ERR ulSenderPid.");
            break;
    }

    return enNetRatType;
}


/*****************************************************************************
 函 数 名  : TAF_CBA_IsCbsEnable
 功能描述  : 根据NV项中的设置判断CBS功能是否使能
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE: CBS功能使能
             VOS_FALSE: 未使能
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月2日
    作    者   : l00171473
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_CBA_IsCbsEnable(VOS_VOID)
{
    TAF_CBA_CBSTATUS_ENUM_UINT8         enCbsStatus;
    TAF_CBA_NET_RAT_TYPE_ENUM_UINT8     enNetMode;

    /* 获取当前CBS消息是否激活标志 */
    enCbsStatus     = TAF_CBA_GetCbsStatus();

    enNetMode       = TAF_CBA_GetNetRatType();

    /* 必须满足NV中该模式CBS激活同时该模式宏开关已打开才默认CBS激活 */
#if (FEATURE_ON == FEATURE_WCBS)
    if ( ((TAF_CBA_CBSTATUS_W_ENABLE == enCbsStatus) || (TAF_CBA_CBSTATUS_WG_ENABLE == enCbsStatus))
      && (TAF_CBA_NET_RAT_TYPE_WCDMA == enNetMode) )
    {
        return  VOS_TRUE;
    }
#endif

#if (FEATURE_ON == FEATURE_GCBS)
    if ( ((TAF_CBA_CBSTATUS_G_ENABLE == enCbsStatus) || (TAF_CBA_CBSTATUS_WG_ENABLE == enCbsStatus))
      && (TAF_CBA_NET_RAT_TYPE_GSM == enNetMode) )
    {
        return VOS_TRUE;
    }
#endif

#if (FEATURE_ON == FEATURE_LTE)
    if (TAF_CBA_NET_RAT_TYPE_LTE == enNetMode)
    {
        return VOS_TRUE;
    }
#endif

    return VOS_FALSE;
}

#if (FEATURE_ETWS == FEATURE_ON)
/*****************************************************************************
 函 数 名  : TAF_CBA_IsCbsMsgIdValid_ETWS
 功能描述  : ETWS FEATURE ON的情况下判断CBS或从通知是否是有效的MSG ID
 输入参数  : usMsgId: 从通知/CBS消息的MSG ID
 输出参数  : 无
 返 回 值  : VOS_TRUE : 是有效的
             VOS_FALSE: 不是有效的
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月28日
    作    者   : l00171473
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_CBA_IsCbsMsgIdValid_ETWS(
    VOS_UINT16                          usMsgId
)
{
    VOS_UINT32                          ulIsInCbsActiveList;
    VOS_UINT32                          ulIsInEtwsList;

    ulIsInCbsActiveList = TAF_CBA_IsMsgIdInCbsActiveList(usMsgId);

    /* CBS开启，ETWS开启的情况, 按用户设置的激活列表判断;
       CBS开启，ETWS关闭, 按用户设置的激活列表判断, ETWS也当作普通CBS上报 */
    if (VOS_TRUE == TAF_CBA_IsCbsEnable())
    {
        if (VOS_TRUE == ulIsInCbsActiveList)
        {
            return VOS_TRUE;
        }
        return VOS_FALSE;
    }

    ulIsInEtwsList  = TAF_CBA_IsMsgIdInEtwsMsgIdList(usMsgId);

    /* CBS关闭，ETWS开启的情况，需仅包含激活列表中 ETWS相关的MSG ID */
    if (VOS_TRUE  == TAF_CBA_GetEtwsEnableFlg())
    {
        if ( (VOS_TRUE == ulIsInCbsActiveList)
          && (VOS_TRUE == ulIsInEtwsList) )
        {
            return VOS_TRUE;
        }
        return VOS_FALSE;
    }

    /* ETWS关闭，CBS关闭 */
    return VOS_FALSE;
}

#endif

/*****************************************************************************
 函 数 名  : TAF_CBA_IsCbsMsgIdValid
 功能描述  : 判断CBS或从通知是否是有效的MSG ID
 输入参数  : usMsgId: 主从通知/CBS消息的MSG ID
 输出参数  : 无
 返 回 值  : VOS_TRUE : 是有效的
             VOS_FALSE: 不是有效的
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月28日
    作    者   : l00171473
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_CBA_IsCbsMsgIdValid(
    VOS_UINT16                          usMsgId
)
{
#if (FEATURE_ETWS == FEATURE_ON)

    return TAF_CBA_IsCbsMsgIdValid_ETWS(usMsgId);

#else

    /* 判断CBS消息ID是否在激活列表中 */
    return TAF_CBA_IsMsgIdInCbsActiveList(usMsgId);
#endif
}

/*****************************************************************************
 函 数 名  : TAF_CBA_GetGsmCbsPageLen
 功能描述  : 获取GAS下广播短消息一页的实际长度
 输入参数  : pstCbTpduData - 按GSM格式存放的广播短消息页
 输出参数  : 无
 返 回 值  : 广播短消息一页的实际长度
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2006年12月20日
    作    者   : 傅映君 62575
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_CBA_GetGsmCbsPageLen(
    GAS_CBS_PAGE_DATA_STRU             *pstCbPageData
)
{
    VOS_UINT32                          ulPos;
    VOS_UINT8                           ucPageLen;
    VOS_UINT32                          ulCbpageIdx;

    /* 3GPP 23.041 9.4.1.2节:
      Octet Number(s)   Field
      1-2               Serial Number
      3-4               Message Identifier
      5                 Data Coding Scheme
      6                 Page Parameter
      7-88              Content of Message
    */

    ucPageLen = TAF_CBA_MAX_CBPAGE_LEN;

    for (ulCbpageIdx = 0; ulCbpageIdx < TAF_CBA_MAX_CBPAGE_LEN; ulCbpageIdx++)
    {
        ulPos   = (TAF_CBA_MAX_CBPAGE_LEN - ulCbpageIdx) - 1;

        if (TAF_CBA_PADDING_OCTET != pstCbPageData->aucData[ulPos])
        {
            break;
        }
        ucPageLen--;
    }

    return ucPageLen;
}

/*****************************************************************************
 函 数 名  : TAF_CBA_BuildGsmCbsRecord
 功能描述  : 从G的CBS消息中构造新的记录项
 输入参数  : pstGsmPage:   指向G的CBS消息页数据
 输出参数  : pstNewRecord: 指向新消息记录项
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月9日
    作    者   : l00171473
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_CBA_BuildGsmCbsRecord(
    MN_MSG_CBGSMPAGE_STRU              *pstGsmPage,
    TAF_CBS_NETWORK_INFO_STRU          *pstCampPlmnInfo,
    TAF_CBA_RECORD_STRU                *pstNewRecord
)
{
    VOS_UINT8                           ucTotalPage;
    VOS_UINT8                           ucPageIndex;

    ucTotalPage = pstGsmPage->Pagesbit4;
    ucPageIndex = pstGsmPage->Pagebit4;

    /* 如果 ucTotalPage或ucPageNumber中一个为0,则当作 0001 0001 ,参见协议23041 9.4.1.2.4 */
    if ( ( 0x00 == ucTotalPage )
      || ( 0x00 == ucPageIndex ) )
    {
        ucTotalPage = 0x01;
        ucPageIndex = 0x01;
    }

    PS_MEM_SET(pstNewRecord, 0x00, sizeof(TAF_CBA_RECORD_STRU));

    pstNewRecord->enNetMode        = TAF_CBA_NET_RAT_TYPE_GSM;
    pstNewRecord->ucTotalPage      = ucTotalPage;
    pstNewRecord->usMsgID          = TAF_CBA_BuildCbsMsgId(pstGsmPage->ucMIdHigh, pstGsmPage->ucMIdLow);
    pstNewRecord->usSN             = TAF_CBA_BuildCbsSN(pstGsmPage->ucSnHigh, pstGsmPage->ucSnLow);
    pstNewRecord->stPlmn.ulMcc     = pstCampPlmnInfo->stCurPlmn.ulMcc;
    pstNewRecord->stPlmn.ulMnc     = pstCampPlmnInfo->stCurPlmn.ulMnc;
    pstNewRecord->ulRcvTimeTick    = VOS_GetTick();

    /*lint -e701*/
    /* 计算bitmap ,此处ucPageIndex最小为1,所以需要左移(ucPageIndex - 1) */
    pstNewRecord->usPageBitmap     = TAF_CBA_BuildGsmCbsPageBitmap(ucPageIndex);
    /*lint +e701*/

    /* 普通CBS没有重复检测时效要求，程序实现中设为0 表示永久有效 */
    pstNewRecord->ulDupDetcTimeLen = 0;

}

/*****************************************************************************
 函 数 名  : TAF_CBA_IsDupGsmCbsRecord
 功能描述  : 判断CBS历史记录表中是否存在重复的记录项
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
  3.日    期   : 2013年8月13日
    作    者   : w00242748
    修改内容   : for DTS2013081300926, 参照0341 9.3.2.1 Update Number那一节，
                 除了UPDATE NUMBER外，其他都相同的话，需对UPDATE NUMBER做特殊处理
  4.日    期   : 2013年8月22日
    作    者   : w00242748
    修改内容   : for DTS2013082106860, 根据update number判断原则，先收到update number
    		1,再收到update number 0但页数不同时，处理存在错误
*****************************************************************************/
VOS_UINT32 TAF_CBA_IsDupGsmCbsRecord(
    TAF_CBA_RECORD_STRU                *pstNewRecord
)
{
    TAF_CBA_RECORD_STRU                *pstRcvCbsList;
    VOS_UINT16                          usRcvCbsNum;
    VOS_UINT16                          ulIndex;
    VOS_UINT32                          ulSameGsCode;
    VOS_UINT32                          ulSameMsgCode;
    VOS_UINT32                          ulSameUpdateNumber;


    if ( VOS_TRUE != TAF_CBA_IsNeedDupDetectCbs((pstNewRecord->usMsgID)) )
    {
        /* 不需要做重复过滤则认为 不是重复的记录项 */
        return VOS_FALSE;
    }


    pstRcvCbsList   = TAF_CBA_GetRcvCbsList();
    usRcvCbsNum     = TAF_CBA_GetRcvCbsNum();

    for ( ulIndex = 0; ulIndex < usRcvCbsNum; ulIndex++ )
    {
        /* 判断接入模式 */
        if (pstNewRecord->enNetMode != pstRcvCbsList[ulIndex].enNetMode)
        {
            continue;
        }

        /* 判断 MSG ID */
        if (pstNewRecord->usMsgID != pstRcvCbsList[ulIndex].usMsgID)
        {
            continue;
        }

        ulSameGsCode       = TAF_CBA_IsSameGsCode(pstNewRecord->usSN, pstRcvCbsList[ulIndex].usSN);
        ulSameMsgCode      = TAF_CBA_IsSameMsgCode(pstNewRecord->usSN, pstRcvCbsList[ulIndex].usSN);
        ulSameUpdateNumber = TAF_CBA_IsSameUpdateNum(pstNewRecord->usSN, pstRcvCbsList[ulIndex].usSN);

        if ( !((VOS_TRUE == ulSameGsCode)
         && (VOS_TRUE == ulSameMsgCode)
         && (VOS_TRUE == ulSameUpdateNumber)))
        {
            continue;
        }
        /* 个人感觉标杆出现出现以下情况不符合协议: GS,MSG ID,MSG CODE相同时，先收到update number为1，
           总页数为2，index为1的CBS消息，再收到update number为0，总页数为2，index为2的CBS消息时，
           竟然上报。个人认为不符合协议，故此处没按标杆修改。
        */
        if ( pstNewRecord->usSN == pstRcvCbsList[ulIndex].usSN)
        {
            /* 比较 Total Page */
            if (pstNewRecord->ucTotalPage != pstRcvCbsList[ulIndex].ucTotalPage)
            {
                /* 可维可测 */
                TAF_CBA_SndOmDupRecordInfo(TAF_CBA_OM_MSG_DUP_CBS_RECORD,
                                           &(pstRcvCbsList[ulIndex]));

                /* 已接收过则是重复消息页 */
                return VOS_TRUE;
            }

        /* 判断该页是否已接收过 */
        if (0 != (pstNewRecord->usPageBitmap & pstRcvCbsList[ulIndex].usPageBitmap))
        {
            /* 可维可测 */
            TAF_CBA_SndOmDupRecordInfo(TAF_CBA_OM_MSG_DUP_CBS_RECORD,
                                       &(pstRcvCbsList[ulIndex]));

                /* 已接收过则是重复消息页 */
                return VOS_TRUE;
            }
        }
        else
        {
            /* 可维可测 */
            TAF_CBA_SndOmDupRecordInfo(TAF_CBA_OM_MSG_DUP_CBS_RECORD,
                                           &(pstRcvCbsList[ulIndex]));

            /* 已接收过则是重复消息页 */
            return VOS_TRUE;
        }
    }
    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_CBA_AppendCbsRecord
 功能描述  : 在CBS历史记录表中追加一个记录项
 输入参数  : pstNewRecord: 新的记录项
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月28日
    作    者   : l00171473
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_CBA_AppendCbsRecord(
    TAF_CBA_RECORD_STRU                *pstAppendRecord
)
{
    TAF_CBA_RECORD_STRU                *pstRcvCbsList;
    VOS_UINT16                          usRcvCbsNum;
    VOS_UINT16                          usAppendInx;
    TAF_CBA_OM_SAVE_TYPE_ENUM_UINT8     enSaveType;

    pstRcvCbsList   = TAF_CBA_GetRcvCbsList();
    usRcvCbsNum     = TAF_CBA_GetRcvCbsNum();
    usAppendInx     = 0;

    /* 记录表中不存在和新记录的MSG ID和MSG CODE相同的记录项, 则新增记录项 */
    if ( TAF_CBA_MAX_CBS_RECORD_NUM == usRcvCbsNum )
    {
        /* 列表已满则获取最早的记录项的index, 覆盖之 */
        usAppendInx = TAF_CBA_GetEarliestCbsRecordInx();

        /* 最早记录的可维可测信息 */
        TAF_CBA_SndOmDeledRecordInfo(TAF_CBA_OM_MSG_DEL_DEL_CBS_RECORD,
                                     TAF_CBA_OM_DEL_REASON_LIST_FULL,
                                     &pstRcvCbsList[usAppendInx]);

        /* 保存记录 */
        pstRcvCbsList[usAppendInx] = (*pstAppendRecord);

        enSaveType  = TAF_CBA_OM_SAVE_TYPE_RECORD_FULL;

    }
    else
    {
        /* 列表未满，则在最后增加一个记录 */
        usAppendInx = usRcvCbsNum;

        /* 保存记录 */
        pstRcvCbsList[usAppendInx] = (*pstAppendRecord);

        /* 更新记录个数 */
        usRcvCbsNum++;
        TAF_CBA_SetRcvCbsNum(usRcvCbsNum);

        enSaveType = TAF_CBA_OM_SAVE_TYPE_APPEND_RECORD;
    }

    /* 可维可测 */
    TAF_CBS_SndOmSavedRecordInfo(TAF_CBA_OM_MSG_SAVE_CBS_RECORD,
                                 enSaveType,
                                 pstAppendRecord,
                                 usRcvCbsNum);
}

/*****************************************************************************
 函 数 名  : TAF_CBA_SaveGsmCbsRecord
 功能描述  : 保存新的GAS的CBS消息记录到CBS历史记录表
 输入参数  : pstNewRecord: 新的记录项
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月28日
    作    者   : l00171473
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_CBA_SaveGsmCbsRecord(
    TAF_CBA_RECORD_STRU                *pstNewRecord
)
{
    VOS_UINT32                          ulSameRecordInx;
    TAF_CBA_RECORD_STRU                *pstRcvCbsList;
    VOS_UINT32                          ulSameGsCode;
    VOS_UINT32                          ulSameUpdateNum;
    TAF_CBA_OM_SAVE_TYPE_ENUM_UINT8     enSaveType;

    pstRcvCbsList   = TAF_CBA_GetRcvCbsList();
    ulSameRecordInx = 0;

    /* 记录表中不存在和新记录的MSG ID和MSG CODE相同的记录项, 则新增记录项 */
    if ( VOS_TRUE != TAF_CBA_GetCbsRecordInxByMsgIdCode(pstNewRecord, &ulSameRecordInx) )
    {
        TAF_CBA_AppendCbsRecord(pstNewRecord);
        return;
    }

    /* 记录表中存在和新记录的MSG ID和MSG CODE相同的记录项, 则更新其 PageBitmap 或 覆盖原记录 */

    ulSameGsCode    = TAF_CBA_IsSameGsCode(pstNewRecord->usSN, pstRcvCbsList[ulSameRecordInx].usSN);
    ulSameUpdateNum = TAF_CBA_IsSameUpdateNum(pstNewRecord->usSN, pstRcvCbsList[ulSameRecordInx].usSN);

    /* 判断GS，UpdaeNumber和总页数这三个字段是否全相同, 全相同则更新其 PageBitMap, 否则覆盖原记录项 */
    if ( (VOS_TRUE == ulSameGsCode)
      && (VOS_TRUE == ulSameUpdateNum)
      && (pstNewRecord->ucTotalPage == pstRcvCbsList[ulSameRecordInx].ucTotalPage) )
    {
        /* 仅更新 PageBitMap */
        pstRcvCbsList[ulSameRecordInx].usPageBitmap |= (pstNewRecord->usPageBitmap);

        enSaveType = TAF_CBA_OM_SAVE_TYPE_UPDATE_RECORD_BITMAP;
    }
    else
    {
        /* 保存 覆盖 */
        pstRcvCbsList[ulSameRecordInx] = (*pstNewRecord);

        enSaveType = TAF_CBA_OM_SAVE_TYPE_REPLACE_RECORD;
    }

    /* 可维可测 */
    TAF_CBS_SndOmSavedRecordInfo(TAF_CBA_OM_MSG_SAVE_CBS_RECORD,
                                 enSaveType,
                                 pstNewRecord,
                                 TAF_CBA_GetRcvCbsNum());
}

/*****************************************************************************
 函 数 名  : TAF_CBA_GetCbsRecordInxByMsgIdCode
 功能描述  : 从CBS的历史记录表中获取与指定记录的MSG ID和MSG CODE相同项的Index
 输入参数  : pstRecord: 指向新消息记录
 输出参数  : pstIndex:  相同项的index
 返 回 值  : VOS_TRUE : 获取成功
             VOS_FALSE: 获取失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月9日
    作    者   : l00171473
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_CBA_GetCbsRecordInxByMsgIdCode(
    TAF_CBA_RECORD_STRU                *pstRecord,
    VOS_UINT32                         *pulIndex
)
{
    TAF_CBA_RECORD_STRU                *pstListAddr;
    VOS_UINT32                          usCbsRecordNum;
    VOS_UINT32                          ulInx;

    pstListAddr    = TAF_CBA_GetRcvCbsList();
    usCbsRecordNum = TAF_CBA_GetRcvCbsNum();

    for ( ulInx = 0; ulInx < usCbsRecordNum; ulInx++ )
    {
        /* 判断接入模式 */
        if (pstRecord->enNetMode != pstListAddr[ulInx].enNetMode)
        {
            continue;
        }

        /* 判断PLMN */
        if ( (pstRecord->stPlmn.ulMcc != pstListAddr[ulInx].stPlmn.ulMcc)
          || (pstRecord->stPlmn.ulMnc != pstListAddr[ulInx].stPlmn.ulMnc) )
        {
            continue;
        }

        /* 判断 MSG ID 和 MSG CODE */
        if ( (VOS_TRUE == TAF_CBA_IsSameMsgCode(pstRecord->usSN, pstListAddr[ulInx].usSN))
          && (pstRecord->usMsgID == pstListAddr[ulInx].usMsgID) )
        {
            *pulIndex = ulInx;
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_CBA_GetEarliestCbsRecordInx
 功能描述  : 从CBS历史记录表中获取最早的CBS记录的index
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 最早的CBS记录的index
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月10日
    作    者   : l00171473
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT16  TAF_CBA_GetEarliestCbsRecordInx(VOS_VOID)
{
    TAF_CBA_RECORD_STRU                *pstRecordList;
    VOS_UINT16                          usEarliestInx;
    VOS_UINT16                          usIndex;
    VOS_UINT32                          ulEarliestTick;

    pstRecordList  = TAF_CBA_GetRcvCbsList();

    usEarliestInx  = 0;
    ulEarliestTick = pstRecordList[0].ulRcvTimeTick;

    for ( usIndex = 1; usIndex < TAF_CBA_GetRcvCbsNum(); usIndex++ )
    {
        if ( pstRecordList[usIndex].ulRcvTimeTick < ulEarliestTick )
        {
            usEarliestInx   = usIndex;
            ulEarliestTick  = pstRecordList[usIndex].ulRcvTimeTick;
        }
    }

    return usEarliestInx;

}

/*****************************************************************************
 函 数 名  : TAF_CBA_BuildBmcCbsRecord
 功能描述  : 从BMC的CBS消息中构造新的CBS记录项
 输入参数  : pstBmcDataInd: 指向BMC的CBS消息
 输出参数  : pstNewRecord:  指向新CBS记录
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月9日
    作    者   : l00171473
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_CBA_BuildBmcCbsRecord(
    BMC_CBS_DATA_IND_STRU              *pstBmcDataInd,
    TAF_CBA_RECORD_STRU                *pstNewRecord
)
{
    TAF_CBA_NET_RAT_TYPE_ENUM_UINT8     enRatType;

    enRatType = TAF_CBA_GetRatTypeBySenderPid(pstBmcDataInd->ulSenderPid);

    PS_MEM_SET(pstNewRecord, 0x00, sizeof(TAF_CBA_RECORD_STRU));

    pstNewRecord->enNetMode     = enRatType;
    pstNewRecord->usMsgID       = pstBmcDataInd->usCBMID;
    pstNewRecord->usSN          = pstBmcDataInd->usSerialNum;
    pstNewRecord->stPlmn.ulMcc  = pstBmcDataInd->stCurrNetworkInfo.stCurPlmn.ulMcc;
    pstNewRecord->stPlmn.ulMnc  = pstBmcDataInd->stCurrNetworkInfo.stCurPlmn.ulMnc;
    pstNewRecord->ulRcvTimeTick = VOS_GetTick();

#if (FEATURE_ETWS == FEATURE_ON)
    pstNewRecord->ulDupDetcTimeLen = TAF_CBA_GetCbsDupDetcTimeLen(&(pstNewRecord->stPlmn),
                                                                     pstNewRecord->usMsgID);
#else
    /* 普通CBS没有重复检测时效要求，程序实现中设为0 表示永久有效 */
    pstNewRecord->ulDupDetcTimeLen = 0;
#endif

}

#if (FEATURE_ON == FEATURE_ETWS)
/*****************************************************************************
 函 数 名  : TAF_CBA_IsCbsRecordSamePlmn
 功能描述  : 判断两个CBS记录项的PLMN是否相同
 输入参数  : pstSrcRecord: 指向一个CBS记录
             pstDstRecord: 指向另一个CBS记录
 输出参数  :
 返 回 值  : VOS_TRUE : PLMN相同
             VOS_FALSE: PLMN不同
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月9日
    作    者   : l00171473
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_CBA_IsCbsRecordSamePlmn(
    TAF_CBA_RECORD_STRU                *pstSrcRecord,
    TAF_CBA_RECORD_STRU                *pstDstRecord
)
{
    /* 判断PLMN */
    if ( (pstSrcRecord->stPlmn.ulMcc != pstDstRecord->stPlmn.ulMcc)
      || (pstSrcRecord->stPlmn.ulMnc != pstDstRecord->stPlmn.ulMnc) )
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}
#endif

/*****************************************************************************
 函 数 名  : TAF_CBA_IsDupBmcCbsRecord
 功能描述  : 判断CBS历史记录表中是否存在重复的CBS记录项
 输入参数  : pstRecord: 指向新CBS记录
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
  3.日    期   : 2013年8月13日
    作    者   : w00242748
    修改内容   : for DTS2013081300926, 根据协议规则对update number进行判断
*****************************************************************************/
VOS_UINT32 TAF_CBA_IsDupBmcCbsRecord(
    TAF_CBA_RECORD_STRU                *pstRecord
)
{
    TAF_CBA_RECORD_STRU                *pstCbsListAddr;
    VOS_UINT16                          usCbsRecordNum;
    VOS_UINT16                          usInx;
    VOS_UINT32                          ulSameGsCode;
    VOS_UINT32                          ulSameMsgCode;
    VOS_UINT32                          ulSameUpdateNumber;


    if ( VOS_TRUE != TAF_CBA_IsNeedDupDetectCbs(pstRecord->usMsgID) )
    {
        /* 不需要做重复过滤则认为 不是重复的记录项 */
        return VOS_FALSE;
    }


    pstCbsListAddr  = TAF_CBA_GetRcvCbsList();
    usCbsRecordNum  = TAF_CBA_GetRcvCbsNum();

    for ( usInx = 0; usInx < usCbsRecordNum; usInx++ )
    {
        /* 判断接入模式 */
        if (pstRecord->enNetMode != pstCbsListAddr[usInx].enNetMode)
        {
            continue;
        }

#if (FEATURE_ON == FEATURE_ETWS)
        /* DoCoMo对ETWS的增强的重复检测定制特性激活时, 需要判断PLMN */
        if (VOS_TRUE == TAF_CBA_GetEnhDupDetcFlg())
        {
            if ( VOS_TRUE != TAF_CBA_IsCbsRecordSamePlmn(pstRecord, &(pstCbsListAddr[usInx]) ))
            {
                continue;
            }
        }
#endif
        /* 判断 MSG ID */
        if (pstRecord->usMsgID != pstCbsListAddr[usInx].usMsgID)
        {
            continue;
        }

        /* 比较整个SN, 目前无需分别判断 MSG CODE, GS 和 UPDATE NUMBER */
        ulSameGsCode       = TAF_CBA_IsSameGsCode(pstRecord->usSN, pstCbsListAddr[usInx].usSN);
        ulSameMsgCode      = TAF_CBA_IsSameMsgCode(pstRecord->usSN, pstCbsListAddr[usInx].usSN);
        ulSameUpdateNumber = TAF_CBA_IsSameUpdateNum(pstRecord->usSN, pstCbsListAddr[usInx].usSN);

        if ( ((VOS_TRUE == ulSameGsCode)
         && (VOS_TRUE == ulSameMsgCode)
         && (VOS_TRUE == ulSameUpdateNumber)))
        {
            /* 可维可测 */
            TAF_CBA_SndOmDupRecordInfo(TAF_CBA_OM_MSG_DUP_CBS_RECORD,
                                       &(pstCbsListAddr[usInx]));

            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_CBA_SaveBmcCbsRecord
 功能描述  : 保存新的CBS记录到CBS历史记录表
 输入参数  : pstRecord: 新CBS记录
 输出参数  :
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月9日
    作    者   : l00171473
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_CBA_SaveBmcCbsRecord (
    TAF_CBA_RECORD_STRU                *pstNewRecord
)
{
    TAF_CBA_RECORD_STRU                *pstRcvCbsList;
    VOS_UINT16                          usRcvCbsNum;
    VOS_UINT32                          ulSameMsgIdCodeInx;

    pstRcvCbsList      = TAF_CBA_GetRcvCbsList();
    usRcvCbsNum        = TAF_CBA_GetRcvCbsNum();
    ulSameMsgIdCodeInx = 0;
    usRcvCbsNum        = 0;

    /* 记录表中不存在和新记录的MSG ID和MSG CODE相同的记录项, 则新增一个记录项 */
    if ( VOS_TRUE != TAF_CBA_GetCbsRecordInxByMsgIdCode(pstNewRecord, &ulSameMsgIdCodeInx) )
    {
        TAF_CBA_AppendCbsRecord(pstNewRecord);

        return;
    }

    /* 记录表中存在和新记录的MSG ID和MSG CODE相同的记录项, 则覆盖原记录项 */
    pstRcvCbsList[ulSameMsgIdCodeInx] = (*pstNewRecord);

    /* 可维可测 */
    TAF_CBS_SndOmSavedRecordInfo(TAF_CBA_OM_MSG_SAVE_CBS_RECORD,
                                 TAF_CBA_OM_SAVE_TYPE_REPLACE_RECORD,
                                 pstNewRecord,
                                 usRcvCbsNum);
}

/*lint -e429 -e830*/

/*****************************************************************************
 函 数 名  : TAF_CBA_ReportRcvCbsData
 功能描述  : 处理收到的CBS消息
 输入参数  : ucPageNum    :CBS消息个数
             pstPageData  :CBS页数内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年5月10日
    作    者   : zhoujun /z40661
    修改内容   : 新生成函数
  2.日    期  : 2012年12月26日
    作    者  : 张鹏 id:00214637
    修改内容  : USIM对外接口函数变更的处理 ，Client ID 到 PID的转换处理 ，  
*****************************************************************************/
VOS_VOID TAF_CBA_ReportRcvCbsData(
    VOS_UINT8                           ucPageNum,
    MN_MSG_CBRAW_TS_DATA_STRU          *pstPageData
)
{

    VOS_UINT16                          usMsgId;
    VOS_UINT32                          ulPageIdx;
    MN_MSG_CBGSMPAGE_STRU              *pstGsmPage;
    VOS_UINT32                          ulNeedDownLoad;

    for ( ulPageIdx = 0 ; ulPageIdx < ucPageNum ; ulPageIdx++ )
    {
        pstGsmPage = (MN_MSG_CBGSMPAGE_STRU *)(pstPageData[ulPageIdx].aucData);

        usMsgId = TAF_CBA_BuildCbsMsgId(pstGsmPage->ucMIdHigh, pstGsmPage->ucMIdLow);

        ulNeedDownLoad = TAF_CBA_IsNeedDownloadToUsim(usMsgId);

        if ( VOS_TRUE ==  ulNeedDownLoad )
        {
            /* 一页一页envelop download到UISM */
            TAF_CBA_SndUsimCbMsg(WUEPS_PID_TAF, 0, pstPageData+ulPageIdx);
        }
        else
        {
             /* 一页一页上报 */
            TAF_CBA_SndAtRcvCbmMsg(pstPageData+ulPageIdx);
        }

    }

    return;
}
/*lint +e429 +e830*/

/*****************************************************************************
 函 数 名  : TAF_CBA_IsNeedDownloadToUsim
 功能描述  : 该CB是否需要Download给USIM
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年5月11日
    作    者   : zhoujun /z40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_CBA_IsNeedDownloadToUsim(
    VOS_UINT16                                              usMsgId
)
{
    VOS_UINT32                                              ulIsDownLoad;
    TAF_CBA_USIM_EFCBMID_FILE_INFO_STRU                    *pstEfCbmidFileInfo;
    TAF_CBA_CBMI_DOWNLOAD_LIST_STRU                        *pstCbmidList;

    pstEfCbmidFileInfo = TAF_CBA_GetEfCbmidInfo();
    pstCbmidList       = TAF_CBA_GetCbmiDownloadList();

    /* 无CBMID文件时之间返回不需要DownLoad */
    if ( ( VOS_FALSE == pstEfCbmidFileInfo->ucEfCbmidExistFlg)
      || (0 == pstEfCbmidFileInfo->usEfCbmidFileLen)
      || (0 == pstCbmidList->usCbmidNum) )
    {
        return VOS_FALSE;
    }

    ulIsDownLoad = TAF_CBA_IsMsgIdInCbmid(usMsgId, pstCbmidList);

    return ulIsDownLoad;
}

/*****************************************************************************
 函 数 名  : TAF_CBA_IsMsgIdInCbmid
 功能描述  : 检查消息ID是否为DOWNLOAD的消息ID
 输入参数  : usMsgId        - 用户消息ID
             pstCbmidList   - USIM指定的DOWNLOAD的消息ID列表
 输出参数  : 无
 返 回 值  : VOS_TRUE 消息ID在DOWNLOAD的消息ID列表中,否则,不在DOWNLOAD的消息ID列表中
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月17日
    作    者   : 傅映君 62575
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_CBA_IsMsgIdInCbmid(
    VOS_UINT16                          usMsgId,
    TAF_CBA_CBMI_DOWNLOAD_LIST_STRU    *pstCbmidList
)
{
    VOS_UINT32                          ulLoop;

    for ( ulLoop = 0; ulLoop < pstCbmidList->usCbmidNum; ulLoop++ )
    {
        if (usMsgId == pstCbmidList->ausMsgId[ulLoop])
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

#if (FEATURE_ON == FEATURE_ETWS)
/*****************************************************************************
 函 数 名  : TAF_CBA_GetCbsDupDetcTimeLen
 功能描述  : 获取CBS消息的重复检测时长
 输入参数  : pstPlmn: Plmn信息
             usMsgId: CBS消息的MSG ID
 输出参数  : 无
 返 回 值  : CBS消息的重复检测时长 Duplication Detection Time
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月25日
    作    者   : l00171473
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_CBA_GetCbsDupDetcTimeLen(
    TAF_CBA_PLMN_ID_STRU                                   *pstPlmn,
    VOS_UINT16                                              usMsgId
)
{
    TAF_CBA_ENH_DUP_DETECT_TIME_LEN_CFG_STRU               *pstEnhDupDetcTimeLenCfg;
    VOS_UINT8                                               ucEnhDupDetcFlg;
    VOS_UINT32                                              i;

    ucEnhDupDetcFlg         = TAF_CBA_GetEnhDupDetcFlg();

    pstEnhDupDetcTimeLenCfg = TAF_CBA_GetEnhDupDetcTimeLenCfg();

    /* 增强的重复检测定制特性未开启时的取值, ETWS消息有重复检测时效要求, 普通CBS消息没有时效要求 */
    if (VOS_TRUE != ucEnhDupDetcFlg)
    {
        if ( VOS_TRUE == TAF_CBA_IsMsgIdInEtwsMsgIdList(usMsgId))
        {
            return TAF_CBA_GetNormalDupDetcTimeLen();
        }

        /* 普通CBS没有重复检测时效要求，程序实现中设为0 表示永久有效 */
        return 0;
    }

    /* DoCoMo 增强的重复检测定制特性开启时的取值:
       1. ETWS和普通CBS消息的重复检测时效要求相同，
       2. 当前PLMN的MCC在定制MCC范围类和定制MCC外取值不同  */
    for ( i = 0; i < TAF_CBA_MAX_ETWS_DUP_DETECT_SPEC_MCC_NUM; i++ )
    {
        if (pstPlmn->ulMcc == pstEnhDupDetcTimeLenCfg->aulSpecMcc[i])
        {
            return pstEnhDupDetcTimeLenCfg->ulSpecMccTimeLen;
        }
    }

    return pstEnhDupDetcTimeLenCfg->ulOtherMccTimeLen;
}
#endif


/*****************************************************************************
 函 数 名  : TAF_CBA_IsNeedDupDetectCbs
 功能描述  : 判断CBS消息是否需要做重复过滤
 输入参数  : usMsgID: CBS 消息ID
 输出参数  : 无
 返 回 值  : VOS_TRUE : 需要做重复检测
             VOS_FALSE: 不需要做重复检测
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月04日
    作    者   : l00171473
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_CBA_IsNeedDupDetectCbs(
    VOS_UINT16                          usMsgID
)
{
    TAF_CBA_DUP_DETECT_CFG_ENUM_UINT8   enDupDetectCfg;

    enDupDetectCfg = TAF_CBA_GetDupDetectCfg();

    if (TAF_CBA_DUP_DETECT_CFG_ALL_ENABLE == enDupDetectCfg)
    {
        return VOS_TRUE;
    }

    /* 判断下载到USIM的CBS是否需要过滤 */
    if ( (VOS_TRUE == TAF_CBA_IsNeedDownloadToUsim(usMsgID))
      && (TAF_CBA_DUP_DETECT_CFG_ONLY_DOWNLOAD_TYPE_ENABLE == enDupDetectCfg) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
/*lint -restore */

#endif /* ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS)) */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
