

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


VOS_VOID TAF_CBA_InitSimInfo(VOS_VOID)
{
    TAF_CBA_SIM_INFO_STRU               *pstSimInfo;

    pstSimInfo = TAF_CBA_GetSimInfo();

    /* TAF_CBA_ClearAllReadUsimFilesFlg */

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



VOS_VOID TAF_CBA_InitRecordList(VOS_VOID)
{
#if (FEATURE_ETWS == FEATURE_ON)
    /* ETWS历史记录初始化 */
    TAF_CBA_InitEtwsRecordList();
#endif

    /* CBS历史记录初始化 */
    TAF_CBA_InitCbsRecordList();
}


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


TAF_CBA_CTX_STRU* TAF_CBA_GetCbaCtx(VOS_VOID)
{
    return (&g_stCbaCtx);
}


TAF_CBA_SIM_INFO_STRU* TAF_CBA_GetSimInfo(VOS_VOID)
{
    return &(TAF_CBA_GetCbaCtx()->stCbsSimInfo);
}


TAF_CBA_USIM_EFCBMI_FILE_INFO_STRU* TAF_CBA_GetEfCbmiInfo(VOS_VOID)
{
    return &(TAF_CBA_GetSimInfo()->stEfCbmiFileInfo);
}


TAF_CBA_USIM_EFCBMIR_FILE_INFO_STRU* TAF_CBA_GetEfCbmiRangeInfo(VOS_VOID)
{
    return &(TAF_CBA_GetSimInfo()->stEfCbmirFileInfo);
}


TAF_CBA_USIM_EFCBMID_FILE_INFO_STRU* TAF_CBA_GetEfCbmidInfo(VOS_VOID)
{
    return &(TAF_CBA_GetSimInfo()->stEfCbmidFileInfo);
}

/* Deleted TAF_CBA_SetReadUsimFileFlg TAF_CBA_GetReadUsimFileFlg TAF_CBA_ClearReadUsimFileFlg TAF_CBA_ClearAllReadUsimFilesFlg */


TAF_CBA_MS_CFG_CBS_INFO_STRU* TAF_CBA_GetMsCfgCbsInfo(VOS_VOID)
{
    return &(TAF_CBA_GetCbaCtx()->stCbsMsCfg);
}


TAF_CBA_CBSTATUS_ENUM_UINT8 TAF_CBA_GetCbsStatus(VOS_VOID)
{
    return TAF_CBA_GetMsCfgCbsInfo()->enCbStatus;
}


VOS_VOID TAF_CBA_SetCbsStatus(
    TAF_CBA_CBSTATUS_ENUM_UINT8         enCbsStatus
)
{
    (TAF_CBA_GetMsCfgCbsInfo()->enCbStatus) = enCbsStatus;
}


VOS_VOID TAF_CBA_SetDupDetectCfg(
    TAF_CBA_DUP_DETECT_CFG_ENUM_UINT8   enTmpDupDetectCfg
)
{
    (TAF_CBA_GetMsCfgCbsInfo()->enDupDetectCfg) = enTmpDupDetectCfg;
}


TAF_CBA_DUP_DETECT_CFG_ENUM_UINT8 TAF_CBA_GetDupDetectCfg(VOS_VOID)
{
    return (TAF_CBA_GetMsCfgCbsInfo()->enDupDetectCfg);
}



VOS_VOID TAF_CBA_SetRptAppFullPageFlg(
    VOS_UINT8                           ucTmpRptAppFullPageFlg
)
{
    (TAF_CBA_GetMsCfgCbsInfo()->ucRptAppFullPageFlg) = ucTmpRptAppFullPageFlg;
}

VOS_UINT8 TAF_CBA_GetRptAppFullPageFlg(VOS_VOID)
{
    return (TAF_CBA_GetMsCfgCbsInfo()->ucRptAppFullPageFlg);
}



TAF_CBA_CBMI_DOWNLOAD_LIST_STRU* TAF_CBA_GetCbmiDownloadList(VOS_VOID)
{
    return &(TAF_CBA_GetMsCfgCbsInfo()->stCbMiDownloadList);
}


VOS_UINT16 TAF_CBA_GetCbmiDownloadNum(VOS_VOID)
{
    return (TAF_CBA_GetCbmiDownloadList()->usCbmidNum);
}


TAF_CBA_CBMI_RANGE_LIST_STRU* TAF_CBA_GetCbMiRangeList(VOS_VOID)
{
    return &(TAF_CBA_GetMsCfgCbsInfo()->stCbMiRangeList);
}


TAF_CBA_CBMI_RANGE_STRU* TAF_CBA_GetCbmiRangeListHead(VOS_VOID)
{
    return &(TAF_CBA_GetMsCfgCbsInfo()->stCbMiRangeList.astCbmiRangeInfo[0]);
}


VOS_UINT16 TAF_CBA_GetCbmiRangNum(VOS_VOID)
{
    return (TAF_CBA_GetCbMiRangeList()->usCbmirNum);
}


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


TAF_CBA_MS_CFG_ETWS_INFO_STRU* TAF_CBA_GetMsCfgEtwsInfo(VOS_VOID)
{
    return &(TAF_CBA_GetCbaCtx()->stEtwsMsCfg);
}


VOS_VOID TAF_CBA_SetMsCfgEtwsInfo(
    TAF_CBA_MS_CFG_ETWS_INFO_STRU      *pstMsCfgEtwsInfo
)
{
    (TAF_CBA_GetCbaCtx()->stEtwsMsCfg) = (*pstMsCfgEtwsInfo);
}


VOS_VOID TAF_CBA_SetEtwsEnableFlg(
    VOS_UINT8                           ucEtwsEnableFlg
)
{
    g_stCbaCtx.stEtwsMsCfg.ucEtwsEnableFlg = ucEtwsEnableFlg;
}


VOS_UINT32 TAF_CBA_GetEtwsEnableFlg(VOS_VOID)
{
    return (VOS_UINT32)(TAF_CBA_GetMsCfgEtwsInfo()->ucEtwsEnableFlg);
}


VOS_VOID  TAF_CBA_SetEnhDupDetcFlg(
    VOS_UINT8       ucDetcFlg
)
{
    g_stCbaCtx.stEtwsMsCfg.stDupDetectCfg.ucEnhDupDetectFlg = ucDetcFlg;
}


VOS_UINT8  TAF_CBA_GetEnhDupDetcFlg(VOS_VOID)
{
    return (TAF_CBA_GetMsCfgEtwsInfo()->stDupDetectCfg.ucEnhDupDetectFlg);
}



VOS_UINT32  TAF_CBA_GetNormalDupDetcTimeLen(VOS_VOID)
{
    return (TAF_CBA_GetMsCfgEtwsInfo()->stDupDetectCfg.ulNormalTimeLen);
}


TAF_CBA_ENH_DUP_DETECT_TIME_LEN_CFG_STRU* TAF_CBA_GetEnhDupDetcTimeLenCfg(VOS_VOID)
{
    return &(TAF_CBA_GetMsCfgEtwsInfo()->stDupDetectCfg.stDupDetectTimeLen);
}


TAF_CBA_ETWS_MSGID_RANGE_STRU* TAF_CBA_GetUserSpecEtwsMsgIdList(VOS_VOID)
{
    return &(TAF_CBA_GetMsCfgEtwsInfo()->astSpecEtwsMsgIdList[0]);
}


VOS_UINT16 TAF_CBA_GetRcvEtwsPrimNtfNum(VOS_VOID)
{
    return (TAF_CBA_GetRcvRecordListInfo()->usRcvEtwsPrimNtfNum);
}


VOS_VOID TAF_CBA_SetRcvEtwsPrimNtfNum(
    VOS_UINT16                          usEtwsPrimNtfNum
)
{
    (TAF_CBA_GetRcvRecordListInfo()->usRcvEtwsPrimNtfNum) = usEtwsPrimNtfNum;
}


TAF_CBA_RECORD_STRU* TAF_CBA_GetRcvEtwsPrimNtfList(VOS_VOID)
{
    return &(TAF_CBA_GetRcvRecordListInfo()->astRcvEtwsPrimNtfList[0]);
}


VOS_VOID TAF_CBA_UpdateTempEnableCbsTimerLen(VOS_VOID)
{
    /* 根据NV中的临时使能CBS的时长更新定时器信息 */

    MN_MSG_UpdateRetryPeriod( TI_TAF_CBA_RCV_ETWS_TEMP_ENABLE_CBS,
                              ((TAF_CBA_GetMsCfgEtwsInfo()->ulTempEnableCbsTimeLen) * TAF_CBA_SECOND_TO_MILLISECOND) );
}

#endif


TAF_CBA_NETWORK_INFO_STRU* TAF_CBA_GetNetworkInfo(VOS_VOID)
{
    return &(TAF_CBA_GetCbaCtx()->stCbsNetworkInfo);
}


TAF_CBA_NETWORK_INFO_STRU* TAF_CBA_GetOldNetworkInfo(VOS_VOID)
{
    return &(TAF_CBA_GetCbaCtx()->stOldNetworkInfo);
}


VOS_VOID TAF_CBA_SetOldNetworkInfo(
    TAF_CBA_NETWORK_INFO_STRU          *pstNetworkinfo
)
{
    (TAF_CBA_GetCbaCtx()->stOldNetworkInfo) = (*pstNetworkinfo);
}


TAF_CBA_NET_RAT_TYPE_ENUM_UINT8 TAF_CBA_GetNetRatType(VOS_VOID)
{
    return TAF_CBA_GetNetworkInfo()->enCurrNetRatType;
}


VOS_VOID TAF_CBA_SetNetRatType(
    TAF_CBA_NET_RAT_TYPE_ENUM_UINT8     enCurrNetMode
)
{
    (TAF_CBA_GetNetworkInfo()->enCurrNetRatType) = enCurrNetMode;
}


TAF_CBA_PLMN_ID_STRU* TAF_CBA_GetCurrPlmn(VOS_VOID)
{
    return &(TAF_CBA_GetNetworkInfo()->stCurPlmn);
}


TAF_CBA_RECORD_LIST_STRU* TAF_CBA_GetRcvRecordListInfo(VOS_VOID)
{
    return &(TAF_CBA_GetCbaCtx()->stRcvRecordList);
}


VOS_UINT16 TAF_CBA_GetRcvCbsNum(VOS_VOID)
{
    return (TAF_CBA_GetRcvRecordListInfo()->usRcvCbsNum);
}


VOS_VOID TAF_CBA_SetRcvCbsNum(
    VOS_UINT16                          usNewRcvCbsNum
)
{
    (TAF_CBA_GetRcvRecordListInfo()->usRcvCbsNum) = usNewRcvCbsNum;
}


TAF_CBA_RECORD_STRU* TAF_CBA_GetRcvCbsList(VOS_VOID)
{
    return &(TAF_CBA_GetRcvRecordListInfo()->astRcvCbsList[0]);
}



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
