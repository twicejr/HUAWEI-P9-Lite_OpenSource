/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafCbaCtx.c
  版 本 号   : 初稿
  作    者   : l00171473
  生成日期   : 2012年3月19日
  最近修改   :
  功能描述   : CBA模块的上下文相关的处理
  函数列表   :
  修改历史   :
  1.日    期   : 2012年3月19日
    作    者   : l00171473
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "TafCbaCtx.h"
#include  "TafCbaProcNvim.h"
#include  "MnMsgTimerProc.h"
#include  "MnErrorCode.h"
#include  "MnComm.h"
#include  "TafLog.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_CBA_CTX_C

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

TAF_CBA_CTX_STRU                        g_stCbaCtx;                             /* CBA的上下文信息 */

/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : TAF_CBA_InitSimInfo
 功能描述  : 初始化CBA模块的SIM卡状态的全局变量信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月26日
    作    者   : l00171473
    修改内容   : 新生成函数
  2.日    期   : 2012年3月29日
    作    者   : w00176964
    修改内容   : USIM文件读取标记增加初始化
  3.日    期   : 2013年6月26日
    作    者   : f62575
    修改内容   : V9R1 STK升级
*****************************************************************************/
VOS_VOID TAF_CBA_InitSimInfo(VOS_VOID)
{
    TAF_CBA_SIM_INFO_STRU               *pstSimInfo;

    pstSimInfo = TAF_CBA_GetSimInfo();

    /* Deleted by f62575 for V9R1 STK升级, 2013-6-26, begin */
    /* TAF_CBA_ClearAllReadUsimFilesFlg */
    /* Deleted by f62575 for V9R1 STK升级, 2013-6-26, end */

    /* 初始化 EFCBMI 文件状态信息 */
    pstSimInfo->stEfCbmiFileInfo.ucEfCbmiExistFlg = VOS_FALSE;                  /* Efcbmi 文件不存在 */
    pstSimInfo->stEfCbmiFileInfo.ucRsv            = 0;
    pstSimInfo->stEfCbmiFileInfo.usEfCbmiFileLen  = 0;

    /* 初始化 EFCBMIR 文件状态信息 */
    pstSimInfo->stEfCbmirFileInfo.ucEfCbmirExistFlg = VOS_FALSE;                /* Efcbmir 文件不存在 */
    pstSimInfo->stEfCbmirFileInfo.ucRsv             = 0;
    pstSimInfo->stEfCbmirFileInfo.usEfCbmirFileLen  = 0;

    /* 初始化 EFCBMID 文件状态信息 */
    pstSimInfo->stEfCbmidFileInfo.ucEfCbmidExistFlg = VOS_FALSE;                /* Efcbmid 文件不存在 */
    pstSimInfo->stEfCbmidFileInfo.ucRsv             = 0;
    pstSimInfo->stEfCbmidFileInfo.usEfCbmidFileLen  = 0;
}

/*****************************************************************************
 函 数 名  : TAF_CBA_InitCbmiRangeList
 功能描述  : 初始化CBMI RANGE List 全局变量
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月26日
    作    者   : l00171473
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_CBA_InitCbmiRangeList(VOS_VOID)
{
    TAF_CBA_CBMI_RANGE_LIST_STRU       *pstCbmiRangInfo;
    VOS_UINT32                          ulInx;

    pstCbmiRangInfo = TAF_CBA_GetCbMiRangeList();

    pstCbmiRangInfo->usCbmirNum    = 0;                                         /* 设定的CBS ID总数为0 */

    pstCbmiRangInfo->aucReserve[0] = 0;
    pstCbmiRangInfo->aucReserve[1] = 0;

    for (ulInx = 0; ulInx < TAF_CBA_MAX_CBMID_RANGE_NUM; ulInx++)
    {
        pstCbmiRangInfo->astCbmiRangeInfo[ulInx].ucLabel[0]  = '\0';            /* 空字符串*/
        pstCbmiRangInfo->astCbmiRangeInfo[ulInx].usMsgIdFrom = 0;
        pstCbmiRangInfo->astCbmiRangeInfo[ulInx].usMsgIdTo   = 0;               /* 起始都为0 */
        pstCbmiRangInfo->astCbmiRangeInfo[ulInx].enRcvMode   =
                                       TAF_CBA_CBMI_RANGE_RCV_MODE_BUTT;        /* 默认为BUTT接受 */
    }
}

/*****************************************************************************
 函 数 名  : TAF_CBA_InitCbsMsCfgInfo
 功能描述  : 初始化用户配置CBS信息的全局变量
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月26日
    作    者   : l00171473
    修改内容   : 新生成函数
  2.日    期   : 2012年12月04日
    作    者   : l00171473
    修改内容   : for DTS2012120600056,新增全局变量初始化
*****************************************************************************/
VOS_VOID  TAF_CBA_InitCbsMsCfgInfo(VOS_VOID)
{
    TAF_CBA_MS_CFG_CBS_INFO_STRU       *pstCfgCbsInfo;
    VOS_UINT32                          ulCbmidNumCount;


    pstCfgCbsInfo = TAF_CBA_GetMsCfgCbsInfo();

    /* 初始化CBS config状态 */
    pstCfgCbsInfo->enCbStatus             = TAF_CBA_CBSTATUS_BUTT;              /* 默认为无效状态 */

    pstCfgCbsInfo->enDupDetectCfg         = TAF_CBA_DUP_DETECT_CFG_BUTT;

    pstCfgCbsInfo->ucRptAppFullPageFlg    = VOS_FALSE;
    pstCfgCbsInfo->ucRsv                  = 0;

    /* 初始化CBS config--stCbMirList状态 */
    TAF_CBA_InitCbmiRangeList();

    /* 初始化CBS config--stCbMidList状态 */
    pstCfgCbsInfo->stCbMiDownloadList.usCbmidNum = 0;                                /* 总的CBS ID总数为0 */

    pstCfgCbsInfo->stCbMiDownloadList.aucRsv[0]  = 0;
    pstCfgCbsInfo->stCbMiDownloadList.aucRsv[1]  = 0;

    for (ulCbmidNumCount = 0; ulCbmidNumCount < TAF_CBA_MAX_CBMID_NUM; ulCbmidNumCount++)
    {
        pstCfgCbsInfo->stCbMiDownloadList.ausMsgId[ulCbmidNumCount] = 0;             /* 列表项中的 CBS ID值为0 */
    }
}

/*****************************************************************************
 函 数 名  : TAF_CBA_InitNetworkInfo
 功能描述  : 初始化CBA模块相关的网络信息全局变量
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月26日
    作    者   : l00171473
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_CBA_InitNetworkInfo(VOS_VOID)
{
    TAF_CBA_NETWORK_INFO_STRU          *pstNetworkInfo;

    pstNetworkInfo = TAF_CBA_GetNetworkInfo();

    pstNetworkInfo->enCurrNetRatType = TAF_CBA_NET_RAT_TYPE_BUTT;               /* 默认为无效 */

    pstNetworkInfo->aucRsv3[0]       = 0;                                       /* 填充字符用 */
    pstNetworkInfo->aucRsv3[1]       = 0;                                       /* 填充字符用 */
    pstNetworkInfo->aucRsv3[2]       = 0;                                       /* 填充字符用 */

    pstNetworkInfo->stCurPlmn.ulMcc  = TAF_CBA_INVALID_MCC;                     /* 默认为无效 */
    pstNetworkInfo->stCurPlmn.ulMnc  = TAF_CBA_INVALID_MNC;                     /* 默认为无效 */

    pstNetworkInfo->usSa             = 0;                                       /* 默认为0 */

    pstNetworkInfo->aucRsv2[0]       = 0;                                       /* 填充字符用 */
    pstNetworkInfo->aucRsv2[1]       = 0;                                       /* 填充字符用 */

    pstNetworkInfo->ulCellId         = 0;                                       /* 默认为0 */
}

/*****************************************************************************
 函 数 名  : TAF_CBA_InitOldNetworkInfo
 功能描述  : 初始化上次的网络信息全局变量(上次 GS_STATUS_CHANGE_IND 中网络信息)
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月26日
    作    者   : l00171473
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_CBA_InitOldNetworkInfo(VOS_VOID)
{
    TAF_CBA_NETWORK_INFO_STRU          *pstOldNetworkInfo;

    pstOldNetworkInfo = TAF_CBA_GetOldNetworkInfo();

    pstOldNetworkInfo->enCurrNetRatType = TAF_CBA_NET_RAT_TYPE_BUTT;            /* 默认为无效 */

    pstOldNetworkInfo->aucRsv3[0]       = 0;                                    /* 填充字符用 */
    pstOldNetworkInfo->aucRsv3[1]       = 0;                                    /* 填充字符用 */
    pstOldNetworkInfo->aucRsv3[2]       = 0;                                    /* 填充字符用 */

    pstOldNetworkInfo->stCurPlmn.ulMcc  = TAF_CBA_INVALID_MCC;                  /* 默认为无效 */
    pstOldNetworkInfo->stCurPlmn.ulMnc  = TAF_CBA_INVALID_MNC;                  /* 默认为无效 */

    pstOldNetworkInfo->usSa             = 0;                                    /* 默认为0 */

    pstOldNetworkInfo->aucRsv2[0]       = 0;                                    /* 填充字符用 */
    pstOldNetworkInfo->aucRsv2[1]       = 0;                                    /* 填充字符用 */

    pstOldNetworkInfo->ulCellId         = 0;                                    /* 默认为0 */
}

#if (FEATURE_ETWS == FEATURE_ON)
/*****************************************************************************
 函 数 名  : TAF_CBA_InitEtwsRecordList
 功能描述  : 初始化ETWS历史记录表全局变量信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月26日
    作    者   : l00171473
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_CBA_InitEtwsRecordList(VOS_VOID)
{
    TAF_CBA_RECORD_LIST_STRU           *pstRcvRecList;
    VOS_UINT32                          ulRecInx;

    pstRcvRecList = TAF_CBA_GetRcvRecordListInfo();

    /* 初始化主通知历史记录表信息 */
    pstRcvRecList->usRcvEtwsPrimNtfNum = 0;                                     /* ETWS主通知历史记录个数 */
    pstRcvRecList->aucRsv[0]           = 0;                                     /* 填充位数用*/
    pstRcvRecList->aucRsv[1]           = 0;                                     /* 填充位数用*/

    for (ulRecInx = 0; ulRecInx < TAF_CBA_MAX_ETWS_PRIM_NTF_RECORD_NUM; ulRecInx++)
    {
        pstRcvRecList->astRcvEtwsPrimNtfList[ulRecInx].enNetMode        = TAF_CBA_NET_RAT_TYPE_BUTT;      /* 无效的接入技术*/
        pstRcvRecList->astRcvEtwsPrimNtfList[ulRecInx].ucTotalPage      = 0;                              /* 总页数（G的CBS消息包含此信息） */
        pstRcvRecList->astRcvEtwsPrimNtfList[ulRecInx].usPageBitmap     = 0;                              /* 已接收页的BitMap(G的CBS消息包含此信息) */
        pstRcvRecList->astRcvEtwsPrimNtfList[ulRecInx].usMsgID          = 0;                              /* 主从通知/CBS消息ID */
        pstRcvRecList->astRcvEtwsPrimNtfList[ulRecInx].usSN             = 0;                              /* 主从通知/CBS序列号 */
        pstRcvRecList->astRcvEtwsPrimNtfList[ulRecInx].stPlmn.ulMcc     = TAF_CBA_INVALID_MCC;            /* 默认为无效 */
        pstRcvRecList->astRcvEtwsPrimNtfList[ulRecInx].stPlmn.ulMnc     = TAF_CBA_INVALID_MNC;            /* 默认为无效 */
        pstRcvRecList->astRcvEtwsPrimNtfList[ulRecInx].ulDupDetcTimeLen = 0;                              /* 有效时长N,单位: 秒, 为0表示一直有效 */
        pstRcvRecList->astRcvEtwsPrimNtfList[ulRecInx].ulRcvTimeTick    = 0;                              /* 收到消息时的时间戳, 取自 VOS_GetTick, 单位: 10 ms */
    }
}
#endif

/*****************************************************************************
 函 数 名  : TAF_CBA_InitCbsRecordList
 功能描述  : 初始化CBS历史记录表全局变量信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月26日
    作    者   : l00171473
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_CBA_InitCbsRecordList(VOS_VOID)
{
    TAF_CBA_RECORD_LIST_STRU           *pstRcvRecList;
    VOS_UINT32                          ulRecInx;

    pstRcvRecList = TAF_CBA_GetRcvRecordListInfo();

    /* 初始化CBS历史记录表信息 */
    pstRcvRecList->usRcvCbsNum = 0;                                             /* CBS(包括ETWS从通知)历史记录个数 */
    pstRcvRecList->aucRsv1[0]  = 0;                                             /* 填充位数用*/
    pstRcvRecList->aucRsv1[1]  = 0;                                             /* 填充位数用*/

    for (ulRecInx = 0; ulRecInx < TAF_CBA_MAX_CBS_RECORD_NUM; ulRecInx++)
    {
        /* ETWS从通知/CBS历史记录表 */
        pstRcvRecList->astRcvCbsList[ulRecInx].enNetMode        = TAF_CBA_NET_RAT_TYPE_BUTT;    /* 无效的接入技术 */
        pstRcvRecList->astRcvCbsList[ulRecInx].ucTotalPage      = 0;                            /* 总页数（G的CBS消息包含此信息） */
        pstRcvRecList->astRcvCbsList[ulRecInx].usPageBitmap     = 0;                            /* 已接收页的BitMap(G的CBS消息包含此信息) */
        pstRcvRecList->astRcvCbsList[ulRecInx].usMsgID          = 0;                            /* 主从通知/CBS消息ID */
        pstRcvRecList->astRcvCbsList[ulRecInx].usSN             = 0;                            /* 主从通知/CBS序列号 */
        pstRcvRecList->astRcvCbsList[ulRecInx].stPlmn.ulMcc     = TAF_CBA_INVALID_MCC;          /* 默认为无效 */
        pstRcvRecList->astRcvCbsList[ulRecInx].stPlmn.ulMnc     = TAF_CBA_INVALID_MNC;          /* 默认为无效 */
        pstRcvRecList->astRcvCbsList[ulRecInx].ulDupDetcTimeLen = 0;                            /* 有效时长为0表示一直有效 */
        pstRcvRecList->astRcvCbsList[ulRecInx].ulRcvTimeTick    = 0;                            /* 时间戳,*/
    }
}


/*****************************************************************************
 函 数 名  : TAF_CBA_InitRecordList
 功能描述  : 初始化历史记录表全局变量信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月26日
    作    者   : l00171473
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_CBA_InitRecordList(VOS_VOID)
{
#if (FEATURE_ETWS == FEATURE_ON)
    /* ETWS历史记录初始化 */
    TAF_CBA_InitEtwsRecordList();
#endif

    /* CBS历史记录初始化 */
    TAF_CBA_InitCbsRecordList();
}

/*****************************************************************************
 函 数 名  : TAF_CBA_InitCtx
 功能描述  : 初始化CBA模块的CTX
 输入参数  : 无
 输出参数  : 无
 返 回 值  : CBA CTX的指针
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月24日
    作    者   : t00212959
    修改内容   : 新生成函数, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
VOS_VOID  TAF_CBA_InitCtx(VOS_VOID)
{
    /* 初始化SIM卡状态的全局变量信息 */
    TAF_CBA_InitSimInfo();

    /* 初始化CBS config状态 */
    TAF_CBA_InitCbsMsCfgInfo();

#if (FEATURE_ETWS == FEATURE_ON)
    /* 初始化ETWS 配置信息 */
    TAF_CBA_InitEtwsMsCfgInfo();
#endif

    /* 初始化网络信息 */
    TAF_CBA_InitNetworkInfo();

    /* 初始化上次的网络信息全局变量(上次 GS_STATUS_CHANGE_IND 中网络信息) */
    TAF_CBA_InitOldNetworkInfo();

    /* 初始化历史记录表信息 */
    TAF_CBA_InitRecordList();
}

/*****************************************************************************
 函 数 名  : TAF_CBA_GetCbsCtx
 功能描述  : 获取CBS的上下文
 输入参数  : 无
 输出参数  : 无
 返 回 值  : CBS CTX的指针
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月19日
    作    者   : l00171473
    修改内容   : 新生成函数, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
TAF_CBA_CTX_STRU* TAF_CBA_GetCbaCtx(VOS_VOID)
{
    return (&g_stCbaCtx);
}

/*****************************************************************************
 函 数 名  : TAF_CBA_GetSimInfo
 功能描述  : 获取CBA模块中SIM卡相关信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : CBS CTX的指针
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月19日
    作    者   : l00171473
    修改内容   : 新生成函数, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
TAF_CBA_SIM_INFO_STRU* TAF_CBA_GetSimInfo(VOS_VOID)
{
    return &(TAF_CBA_GetCbaCtx()->stCbsSimInfo);
}

/*****************************************************************************
 函 数 名  : TAF_CBA_GetEfCbmiInfo
 功能描述  : 获取CBA模块中EFCBMI的信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : CBA模块中EFCBMI的信息
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月19日
    作    者   : l00171473
    修改内容   : 新生成函数, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
TAF_CBA_USIM_EFCBMI_FILE_INFO_STRU* TAF_CBA_GetEfCbmiInfo(VOS_VOID)
{
    return &(TAF_CBA_GetSimInfo()->stEfCbmiFileInfo);
}

/*****************************************************************************
 函 数 名  : TAF_CBA_GetEfCbmiRangeInfo
 功能描述  : 获取CBA模块中EFCBMIR 的信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : CBA模块中EFCBMIR的信息
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月19日
    作    者   : l00171473
    修改内容   : 新生成函数, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
TAF_CBA_USIM_EFCBMIR_FILE_INFO_STRU* TAF_CBA_GetEfCbmiRangeInfo(VOS_VOID)
{
    return &(TAF_CBA_GetSimInfo()->stEfCbmirFileInfo);
}

/*****************************************************************************
 函 数 名  : TAF_CBA_GetEfCbmidInfo
 功能描述  : 获取CBA模块中EFCBMID的信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : CBA模块中EFCBMID的信息
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月19日
    作    者   : l00171473
    修改内容   : 新生成函数, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
TAF_CBA_USIM_EFCBMID_FILE_INFO_STRU* TAF_CBA_GetEfCbmidInfo(VOS_VOID)
{
    return &(TAF_CBA_GetSimInfo()->stEfCbmidFileInfo);
}

/* Deleted by f62575 for V9R1 STK升级, 2013-6-26, begin */
/* Deleted TAF_CBA_SetReadUsimFileFlg TAF_CBA_GetReadUsimFileFlg TAF_CBA_ClearReadUsimFileFlg TAF_CBA_ClearAllReadUsimFilesFlg */
/* Deleted by f62575 for V9R1 STK升级, 2013-6-26, end */

/*****************************************************************************
 函 数 名  : TAF_CBA_GetCbsMsCfgInfo
 功能描述  : 获取用户配置的CBS信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回用户配置的CBS信息
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月19日
    作    者   : l00171473
    修改内容   : 新生成函数, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
TAF_CBA_MS_CFG_CBS_INFO_STRU* TAF_CBA_GetMsCfgCbsInfo(VOS_VOID)
{
    return &(TAF_CBA_GetCbaCtx()->stCbsMsCfg);
}

/*****************************************************************************
 函 数 名  : MN_MSG_GetCbsStatus
 功能描述  : 获取当前CBS功能激活标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回当前CBS功能激活标志
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月19日
    作    者   : l00171473
    修改内容   : 新生成函数, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
TAF_CBA_CBSTATUS_ENUM_UINT8 TAF_CBA_GetCbsStatus(VOS_VOID)
{
    return TAF_CBA_GetMsCfgCbsInfo()->enCbStatus;
}

/*****************************************************************************
 函 数 名  : MN_MSG_SetCbsStatus
 功能描述  : 更新当前CBS功能激活标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回当前CBS功能激活标志
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月19日
    作    者   : l00171473
    修改内容   : 新生成函数, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
VOS_VOID TAF_CBA_SetCbsStatus(
    TAF_CBA_CBSTATUS_ENUM_UINT8         enCbsStatus
)
{
    (TAF_CBA_GetMsCfgCbsInfo()->enCbStatus) = enCbsStatus;
}

/*****************************************************************************
 函 数 名  : TAF_CBA_SetDupDetectCfg
 功能描述  : 更新CBS重复检测的配置开关
 输入参数  : CBS重复过滤的配置开关
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月04日
    作    者   : l00171473
    修改内容   : 新生成函数, for DTS2012120600056

*****************************************************************************/
VOS_VOID TAF_CBA_SetDupDetectCfg(
    TAF_CBA_DUP_DETECT_CFG_ENUM_UINT8   enTmpDupDetectCfg
)
{
    (TAF_CBA_GetMsCfgCbsInfo()->enDupDetectCfg) = enTmpDupDetectCfg;
}

/*****************************************************************************
 函 数 名  : TAF_CBA_GetDupDetectCfg
 功能描述  : 获取CBS重复检测的配置开关
 输入参数  : 无
 输出参数  : 无
 返 回 值  : CBS重复过滤的配置开关
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月04日
    作    者   : l00171473
    修改内容   : 新生成函数, for DTS2012120600056

*****************************************************************************/
TAF_CBA_DUP_DETECT_CFG_ENUM_UINT8 TAF_CBA_GetDupDetectCfg(VOS_VOID)
{
    return (TAF_CBA_GetMsCfgCbsInfo()->enDupDetectCfg);
}


/*****************************************************************************
 函 数 名  : TAF_CBA_SetRptAppFullPageFlg
 功能描述  : 设置向APP上报整页的配置开关
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 向APP上报整页的配置开关
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月04日
    作    者   : l00171473
    修改内容   : 新生成函数, for DTS2012120609682,终端要求CBS统一上报88个字节

*****************************************************************************/
VOS_VOID TAF_CBA_SetRptAppFullPageFlg(
    VOS_UINT8                           ucTmpRptAppFullPageFlg
)
{
    (TAF_CBA_GetMsCfgCbsInfo()->ucRptAppFullPageFlg) = ucTmpRptAppFullPageFlg;
}
/*****************************************************************************
 函 数 名  : TAF_CBA_GetRptAppFullPageFlg
 功能描述  : 获取是否向APP上报整页的配置开关
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 是否向APP上报整页的配置开关
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月04日
    作    者   : l00171473
    修改内容   : 新生成函数, for DTS2012120609682,终端要求CBS统一上报88个字节

*****************************************************************************/
VOS_UINT8 TAF_CBA_GetRptAppFullPageFlg(VOS_VOID)
{
    return (TAF_CBA_GetMsCfgCbsInfo()->ucRptAppFullPageFlg);
}


/*****************************************************************************
 函 数 名  : TAF_CBA_GetCbmiDownloadList
 功能描述  : 获取当前CBS CBMID List的信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回当前CBS CBMID List的信息
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月19日
    作    者   : l00171473
    修改内容   : 新生成函数, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
TAF_CBA_CBMI_DOWNLOAD_LIST_STRU* TAF_CBA_GetCbmiDownloadList(VOS_VOID)
{
    return &(TAF_CBA_GetMsCfgCbsInfo()->stCbMiDownloadList);
}

/*****************************************************************************
 函 数 名  : TAF_CBA_GetCbmiDownloadNum
 功能描述  : 获取当前CBS CBMID List中CBMID 的个数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回当前CBS CBMID List中CBMID 的个数
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月19日
    作    者   : l00171473
    修改内容   : 新生成函数, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
VOS_UINT16 TAF_CBA_GetCbmiDownloadNum(VOS_VOID)
{
    return (TAF_CBA_GetCbmiDownloadList()->usCbmidNum);
}

/*****************************************************************************
 函 数 名  : TAF_CBA_GetCbMiRangeList
 功能描述  : 获取当前CBS CBMIR List的信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回当前CBS CBMIR List的信息
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月19日
    作    者   : l00171473
    修改内容   : 新生成函数, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
TAF_CBA_CBMI_RANGE_LIST_STRU* TAF_CBA_GetCbMiRangeList(VOS_VOID)
{
    return &(TAF_CBA_GetMsCfgCbsInfo()->stCbMiRangeList);
}

/*****************************************************************************
 函 数 名  : TAF_CBA_GetCbmiRangeListHead
 功能描述  : 获取当前CBS CBMIR List的头指针
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前CBS CBMIR List的头指针
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月19日
    作    者   : l00171473
    修改内容   : 新生成函数, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
TAF_CBA_CBMI_RANGE_STRU* TAF_CBA_GetCbmiRangeListHead(VOS_VOID)
{
    return &(TAF_CBA_GetMsCfgCbsInfo()->stCbMiRangeList.astCbmiRangeInfo[0]);
}

/*****************************************************************************
 函 数 名  : TAF_CBA_GetCbmiRangNum
 功能描述  : 获取当前CBS CBMIR List中的CBMIR的个数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回当前CBS CBMIR List中的CBMIR的个数
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月19日
    作    者   : l00171473
    修改内容   : 新生成函数, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
VOS_UINT16 TAF_CBA_GetCbmiRangNum(VOS_VOID)
{
    return (TAF_CBA_GetCbMiRangeList()->usCbmirNum);
}

/*****************************************************************************
 函 数 名  : TAF_CBA_SetCbmiRangeNum
 功能描述  : 设置当前 CBMIR List中的CBMIR的个数
 输入参数  : CBMIR的个数
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月19日
    作    者   : l00171473
    修改内容   : 新生成函数, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
VOS_VOID TAF_CBA_SetCbmiRangeNum(
    VOS_UINT16                          usCbmiRangNum
)
{
    if (usCbmiRangNum >= TAF_CBA_MAX_CBMID_RANGE_NUM)
    {
        usCbmiRangNum = TAF_CBA_MAX_CBMID_RANGE_NUM;
    }

    (TAF_CBA_GetCbMiRangeList()->usCbmirNum) = usCbmiRangNum;
}

#if (FEATURE_ETWS == FEATURE_ON)

/*****************************************************************************
 函 数 名  : TAF_CBA_InitEtwsMsCfgInfo
 功能描述  : 初始化ETWS的用户配置全局变量
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月26日
    作    者   : l00171473
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_CBA_InitEtwsMsCfgInfo(VOS_VOID)
{
    TAF_CBA_MS_CFG_ETWS_INFO_STRU      *pstEtwsCfg;
    VOS_UINT32                          ulInx;

    pstEtwsCfg = TAF_CBA_GetMsCfgEtwsInfo();

    /* 初始化ETWS状态 */
    TAF_CBA_SetEtwsEnableFlg(VOS_FALSE);

    pstEtwsCfg->aucRsv[0]       = 0;                                            /* 填充字符用*/
    pstEtwsCfg->aucRsv[1]       = 0;                                            /* 填充字符用*/
    pstEtwsCfg->aucRsv[2]       = 0;                                            /* 填充字符用*/

    /* 初始化重复检测配置信息 */
    pstEtwsCfg->stDupDetectCfg.ucEnhDupDetectFlg = 0;                           /* 长度为0*/

    pstEtwsCfg->stDupDetectCfg.aucRsv[0]         = 0;
    pstEtwsCfg->stDupDetectCfg.aucRsv[1]         = 0;
    pstEtwsCfg->stDupDetectCfg.aucRsv[2]         = 0;

    pstEtwsCfg->stDupDetectCfg.ulNormalTimeLen                          = 0;    /* 长度为0*/
    pstEtwsCfg->stDupDetectCfg.stDupDetectTimeLen.ulSpecMccTimeLen      = 0;    /* 时长为0*/
    pstEtwsCfg->stDupDetectCfg.stDupDetectTimeLen.ulOtherMccTimeLen     = 0;    /* 时长为0*/

    for ( ulInx = 0; ulInx < TAF_CBA_MAX_ETWS_DUP_DETECT_SPEC_MCC_NUM; ulInx++ )
    {
        pstEtwsCfg->stDupDetectCfg.stDupDetectTimeLen.aulSpecMcc[ulInx] = 0;    /* 时长为0*/
    }

    /* 初始化临时使能CBS时长 */
    pstEtwsCfg->ulTempEnableCbsTimeLen = 0;                                     /* 时长为0*/

    /* 初始化用户定制的ETWS消息的 MSG ID范围 */
    for ( ulInx = 0; ulInx < TAF_CBA_NVIM_MAX_USER_SPEC_ETWS_MSGID_RANGE_NUM; ulInx++ )
    {
        pstEtwsCfg->astSpecEtwsMsgIdList[ulInx].usMsgIdFrom = 0;
        pstEtwsCfg->astSpecEtwsMsgIdList[ulInx].usMsgIdTo   = 0;                /* 起始都为0*/
    }
}

/*****************************************************************************
 函 数 名  : TAF_CBA_GetMsCfgEtwsInfo
 功能描述  : 获取用户配置的ETWS信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回用户配置的ETWS信息
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月19日
    作    者   : l00171473
    修改内容   : 新生成函数, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
TAF_CBA_MS_CFG_ETWS_INFO_STRU* TAF_CBA_GetMsCfgEtwsInfo(VOS_VOID)
{
    return &(TAF_CBA_GetCbaCtx()->stEtwsMsCfg);
}

/*****************************************************************************
 函 数 名  : TAF_CBA_SetEtwsEnableFlg
 功能描述  : 更新用户配置的ETWS信息
 输入参数  : ucEtwsEnableFlg - 从NV读出的ETWS是否有效
 输出参数  : 无
 返 回 值  : 返回用户配置的ETWS信息
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月23日
    作    者   : t00212959
    修改内容   : 新生成函数, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
VOS_VOID TAF_CBA_SetMsCfgEtwsInfo(
    TAF_CBA_MS_CFG_ETWS_INFO_STRU      *pstMsCfgEtwsInfo
)
{
    (TAF_CBA_GetCbaCtx()->stEtwsMsCfg) = (*pstMsCfgEtwsInfo);
}

/*****************************************************************************
 函 数 名  : TAF_CBA_SetEtwsEnableFlg
 功能描述  : 设置当前ETWS是否激活标记
 输入参数  : ETWS是否激活
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月31日
    作    者   : w00176964
    修改内容   : 新生成函数, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
VOS_VOID TAF_CBA_SetEtwsEnableFlg(
    VOS_UINT8                           ucEtwsEnableFlg
)
{
    g_stCbaCtx.stEtwsMsCfg.ucEtwsEnableFlg = ucEtwsEnableFlg;
}

/*****************************************************************************
 函 数 名  : TAF_CBA_GetEtwsEnableFlg
 功能描述  : 获取当前ETWS是否激活标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回当前ETWS是否激活标记
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月19日
    作    者   : l00171473
    修改内容   : 新生成函数, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
VOS_UINT32 TAF_CBA_GetEtwsEnableFlg(VOS_VOID)
{
    return (VOS_UINT32)(TAF_CBA_GetMsCfgEtwsInfo()->ucEtwsEnableFlg);
}

/*****************************************************************************
 函 数 名  : TAF_CBA_SetEnhDupDetcFlg
 功能描述  : 设置DOCOMO增强的重复检测定制特性开关
 输入参数  : 增强的重复检测特性开关
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月19日
    作    者   : l00171473
    修改内容   : 新生成函数, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
VOS_VOID  TAF_CBA_SetEnhDupDetcFlg(
    VOS_UINT8       ucDetcFlg
)
{
    g_stCbaCtx.stEtwsMsCfg.stDupDetectCfg.ucEnhDupDetectFlg = ucDetcFlg;
}

/*****************************************************************************
 函 数 名  : TAF_CBA_GetEnhDupDetcFlg
 功能描述  : 获取DOCOMO增强的重复检测定制特性开关
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 增强的重复检测特性开关
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月19日
    作    者   : l00171473
    修改内容   : 新生成函数, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
VOS_UINT8  TAF_CBA_GetEnhDupDetcFlg(VOS_VOID)
{
    return (TAF_CBA_GetMsCfgEtwsInfo()->stDupDetectCfg.ucEnhDupDetectFlg);
}


/*****************************************************************************
 函 数 名  : TAF_CBA_GetNormalDupDetcTimeLen
 功能描述  : 获取普通的重复检测时长
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 普通的重复检测时长
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月19日
    作    者   : l00171473
    修改内容   : 新生成函数, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
VOS_UINT32  TAF_CBA_GetNormalDupDetcTimeLen(VOS_VOID)
{
    return (TAF_CBA_GetMsCfgEtwsInfo()->stDupDetectCfg.ulNormalTimeLen);
}

/*****************************************************************************
 函 数 名  : TAF_CBA_GetEnhDupDetcTimeLenCfg
 功能描述  : 获取增强重复检测时长配置信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 增强重复检测时长配置信息
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月19日
    作    者   : l00171473
    修改内容   : 新生成函数, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
TAF_CBA_ENH_DUP_DETECT_TIME_LEN_CFG_STRU* TAF_CBA_GetEnhDupDetcTimeLenCfg(VOS_VOID)
{
    return &(TAF_CBA_GetMsCfgEtwsInfo()->stDupDetectCfg.stDupDetectTimeLen);
}

/*****************************************************************************
 函 数 名  : TAF_CBA_GetUserSpecEtwsMsgIdList
 功能描述  : 获取用户定制的ETWS消息ID信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 用户定制的ETWS消息ID信息
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月19日
    作    者   : l00171473
    修改内容   : 新生成函数, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
TAF_CBA_ETWS_MSGID_RANGE_STRU* TAF_CBA_GetUserSpecEtwsMsgIdList(VOS_VOID)
{
    return &(TAF_CBA_GetMsCfgEtwsInfo()->astSpecEtwsMsgIdList[0]);
}

/*****************************************************************************
 函 数 名  : TAF_CBA_GetRcvEtwsPrimNtfNum
 功能描述  : 获取ETWS主通知历史记录个数
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : ETWS主通知历史记录个数
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月9日
    作    者   : l00171473
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT16 TAF_CBA_GetRcvEtwsPrimNtfNum(VOS_VOID)
{
    return (TAF_CBA_GetRcvRecordListInfo()->usRcvEtwsPrimNtfNum);
}

/*****************************************************************************
 函 数 名  : TAF_CBA_SetRcvEtwsPrimNtfNum
 功能描述  : 保存ETWS主通知历史记录个数
 输入参数  : usEtwsPrimNtfNum: ETWS主通知历史记录个数
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月9日
    作    者   : l00171473
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_CBA_SetRcvEtwsPrimNtfNum(
    VOS_UINT16                          usEtwsPrimNtfNum
)
{
    (TAF_CBA_GetRcvRecordListInfo()->usRcvEtwsPrimNtfNum) = usEtwsPrimNtfNum;
}

/*****************************************************************************
 函 数 名  : TAF_CBA_GetRcvEtwsPrimNtfList
 功能描述  : 获取ETWS主通知历史记录表的地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : ETWS主通知历史记录表的地址
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月9日
    作    者   : l00171473
    修改内容   : 新生成函数

*****************************************************************************/
TAF_CBA_RECORD_STRU* TAF_CBA_GetRcvEtwsPrimNtfList(VOS_VOID)
{
    return &(TAF_CBA_GetRcvRecordListInfo()->astRcvEtwsPrimNtfList[0]);
}

/*****************************************************************************
 函 数 名  : TAF_CBA_UpdateTempEnableCbsTimerLen
 功能描述  : 根据NV中的临时使能CBS的时长初始化定时器的时长
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月20日
    作    者   : l00171473
    修改内容   : 新生成函数, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
VOS_VOID TAF_CBA_UpdateTempEnableCbsTimerLen(VOS_VOID)
{
    /* 根据NV中的临时使能CBS的时长更新定时器信息 */

    MN_MSG_UpdateRetryPeriod( TI_TAF_CBA_RCV_ETWS_TEMP_ENABLE_CBS,
                              ((TAF_CBA_GetMsCfgEtwsInfo()->ulTempEnableCbsTimeLen) * TAF_CBA_SECOND_TO_MILLISECOND) );
}

#endif

/*****************************************************************************
 函 数 名  : TAF_CBA_GetNetworkInfo
 功能描述  : 获取当前CBS功能模块的网络信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回当前CBS功能模块的网络信息
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月120日
    作    者   : l00171473
    修改内容   : 新生成函数, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
TAF_CBA_NETWORK_INFO_STRU* TAF_CBA_GetNetworkInfo(VOS_VOID)
{
    return &(TAF_CBA_GetCbaCtx()->stCbsNetworkInfo);
}

/*****************************************************************************
 函 数 名  : TAF_CBA_GetOldNetworkInfo
 功能描述  : 获取上次的网络信息(上次 GS_STATUS_CHANGE_IND 中网络信息)
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回当前CBS功能模块的网络信息
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月120日
    作    者   : l00171473
    修改内容   : 新生成函数, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
TAF_CBA_NETWORK_INFO_STRU* TAF_CBA_GetOldNetworkInfo(VOS_VOID)
{
    return &(TAF_CBA_GetCbaCtx()->stOldNetworkInfo);
}

/*****************************************************************************
 函 数 名  : TAF_CBA_SetOldNetworkInfo
 功能描述  : 设置上次的网络信息(上次 GS_STATUS_CHANGE_IND 中网络信息)
 输入参数  : pstNetworkinfo: 网络信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月120日
    作    者   : l00171473
    修改内容   : 新生成函数, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
VOS_VOID TAF_CBA_SetOldNetworkInfo(
    TAF_CBA_NETWORK_INFO_STRU          *pstNetworkinfo
)
{
    (TAF_CBA_GetCbaCtx()->stOldNetworkInfo) = (*pstNetworkinfo);
}

/*****************************************************************************
 函 数 名  : TAF_CBA_GetNetRatType
 功能描述  : 获取当前CBS功能模块的网络模式
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回当前CBS功能模块的网络模式
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月20日
    作    者   : l00171473
    修改内容   : 新生成函数, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
TAF_CBA_NET_RAT_TYPE_ENUM_UINT8 TAF_CBA_GetNetRatType(VOS_VOID)
{
    return TAF_CBA_GetNetworkInfo()->enCurrNetRatType;
}

/*****************************************************************************
 函 数 名  : TAF_CBA_SetNetRatType
 功能描述  : 设置当前CBS功能模块的网络模式
 输入参数  : enCurrNetMode - 网络模式
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月24日
    作    者   : t00212959
    修改内容   : 新生成函数, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
VOS_VOID TAF_CBA_SetNetRatType(
    TAF_CBA_NET_RAT_TYPE_ENUM_UINT8     enCurrNetMode
)
{
    (TAF_CBA_GetNetworkInfo()->enCurrNetRatType) = enCurrNetMode;
}

/*****************************************************************************
 函 数 名  : TAF_CBA_GetCurrPlmn
 功能描述  : 获取当前CBS功能模块的Plmn
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回当前CBS功能模块的Plmn
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月20日
    作    者   : l00171473
    修改内容   : 新生成函数, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
TAF_CBA_PLMN_ID_STRU* TAF_CBA_GetCurrPlmn(VOS_VOID)
{
    return &(TAF_CBA_GetNetworkInfo()->stCurPlmn);
}

/*****************************************************************************
 函 数 名  : TAF_CBA_GetRcvRecordListInfo
 功能描述  : CBS及ETWS记录信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回CBS及ETWS记录信息
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月120日
    作    者   : l00171473
    修改内容   : 新生成函数, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
TAF_CBA_RECORD_LIST_STRU* TAF_CBA_GetRcvRecordListInfo(VOS_VOID)
{
    return &(TAF_CBA_GetCbaCtx()->stRcvRecordList);
}

/*****************************************************************************
 函 数 名  : TAF_CBA_GetRcvCbsNum
 功能描述  : 获取普通CBS和ETWS从通知记录个数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : CBS记录个数
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月9日
    作    者   : l00171473
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT16 TAF_CBA_GetRcvCbsNum(VOS_VOID)
{
    return (TAF_CBA_GetRcvRecordListInfo()->usRcvCbsNum);
}

/*****************************************************************************
 函 数 名  : TAF_CBA_GetRcvCbsNum
 功能描述  : 设置普通CBS和ETWS从通知记录个数
 输入参数  : usNewRcvCbsNum: 新的CBS记录个数
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月9日
    作    者   : l00171473
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_CBA_SetRcvCbsNum(
    VOS_UINT16                          usNewRcvCbsNum
)
{
    (TAF_CBA_GetRcvRecordListInfo()->usRcvCbsNum) = usNewRcvCbsNum;
}

/*****************************************************************************
 函 数 名  : TAF_CBA_GetRcvCbsList
 功能描述  : 获取普通CBS和ETWS从通知历史记录表的地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : CBS历史记录表的地址
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月9日
    作    者   : l00171473
    修改内容   : 新生成函数

*****************************************************************************/
TAF_CBA_RECORD_STRU* TAF_CBA_GetRcvCbsList(VOS_VOID)
{
    return &(TAF_CBA_GetRcvRecordListInfo()->astRcvCbsList[0]);
}


/*****************************************************************************
 函 数 名  : TAF_CBA_Init
 功能描述  : CBA模块的初始化处理, 该接口目前仅在PID的初始化时调用(上电开机时).
             即是说: 目前CBS相关的NV项在上电的时候才会读取, 修改了相关的NV项后需要
             重新上电开机才能生效
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月20日
    作    者   : l00171473
    修改内容   : 新生成函数, for V7R1C50 CSFB&PPAC&ETWS&ISR
  2.日    期   : 2013年8月12日
    作    者   : f62575
    修改内容   : DTS2013081900835，支持先更新USIM配置，后更新NV配置

*****************************************************************************/
VOS_VOID TAF_CBA_Init(VOS_VOID)
{
    /* 初始化CBA的CTX */
    TAF_CBA_InitCtx();

    /* 读取CBS功能使能NV项 */
    TAF_CBA_ReadCbsServiceParamNvim();

    /* TAF_CBA_ReadCbmiRangeListNvim */    

#if (FEATURE_ETWS == FEATURE_ON)
    /* 读取ETWS的配置NV项 */
    TAF_CBA_ReadEtwsServieCfgNvim();

    /* 根据全局变量中的临时使能CBS的时长更新定时器信息 */
    TAF_CBA_UpdateTempEnableCbsTimerLen();
#endif
}


#endif  /* ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS)) */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
