

#ifndef __TAFCBACTX_H__
#define __TAFCBACTX_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "product_config.h"
#include  "MnMsgApi.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))

/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define TAF_CBA_MAX_CBMID_NUM                               (20)                /* 最多可以记录DOWNLOAD广播短消息类型的个数，具体数据还受文件CBMID限制 */

#define TAF_CBA_MAX_ETWS_DUP_DETECT_SPEC_MCC_NUM            (5)                 /* 有效时长定制特性中最大指定MCC个数 */

#define TAF_CBA_MAX_ETWS_PRIM_NTF_RECORD_NUM                (30)                /* 保存的ETWS Primary Notify(主通知)历史记录最大个数 */

#define TAF_CBA_MAX_CBS_RECORD_NUM                          (150)               /* 保存的CBS(包括ETWS Secondary Notify)历史记录最大个数 */

#define TAF_CBA_NVIM_MAX_USER_SPEC_ETWS_MSGID_RANGE_NUM     (2)                 /* 最大用户可配置的ETWS的MSG ID范围个数 */

#define TAF_CBA_INVALID_MCC                                 (0xffffffff)        /* MCC的无效值 */
#define TAF_CBA_INVALID_MNC                                 (0xffffffff)        /* MNC的无效值 */


/*******************************************************************************
协议定义的ETWS CBS消息ID的范围: 见23041 9.4.1.2.2
4352 0x1100 ETWS CBS Message Identifier for earthquake warning message.
4353 0x1101 ETWS CBS Message Identifier for tsunami warning message.
4354 0x1102 ETWS CBS Message Identifier for earthquake and tsunami combined warning message.
4355 0x1103 ETWS CBS Message Identifier for test message.
          The UE silently discards this message. A UE specially designed
          for testing purposes may display its contents.
4356 0x1104 ETWS CBS Message Identifier for messages related to other emergency types.
4357 - 4359 0x1105 - 0x1107 ETWS CBS Message Identifier for future extension.
*******************************************************************************/
#define TAF_CBA_PROTOCOL_ETWS_CBS_MSGID_FROM                (4352)
#define TAF_CBA_PROTOCOL_ETWS_CBS_MSGID_TO                  (4359)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/


enum TAF_CBA_CBSSTATUS_ENUM
{
    TAF_CBA_CBSTATUS_DISABLE             = 0x00,                                /* CBS功能未使能 */
    TAF_CBA_CBSTATUS_W_ENABLE            = 0x01,                                /* W模的CBS功能使能 */
    TAF_CBA_CBSTATUS_G_ENABLE            = 0x02,                                /* G模的CBS功能使能 */
    TAF_CBA_CBSTATUS_WG_ENABLE           = 0x03,                                /* W和G模的CBS功能均使能 */
    TAF_CBA_CBSTATUS_BUTT                                                       /* 无效值 */
};
typedef VOS_UINT8 TAF_CBA_CBSTATUS_ENUM_UINT8;



enum TAF_CBA_NET_RAT_TYPE_ENUM
{
    TAF_CBA_NET_RAT_TYPE_GSM,                                                   /* GSM接入技术 */
    TAF_CBA_NET_RAT_TYPE_WCDMA,                                                 /* WCDMA接入技术 */
    TAF_CBA_NET_RAT_TYPE_LTE,                                                   /* LTE接入技术 */
    TAF_CBA_NET_RAT_TYPE_BUTT                                                   /* 无效的接入技术 */
};
typedef VOS_UINT8 TAF_CBA_NET_RAT_TYPE_ENUM_UINT8;


enum TAF_CBA_READ_SIM_FILES_FLG_ENUM
{
    TAF_CBA_READ_SIM_FILES_FLG_NULL                                      = 0x00,/* 初始读取标记, 表示不读取任何USIM文件 */
    TAF_CBA_READ_CBMI_FILE_FLG                                           = 0x01,/* 读取CBMI 文件标记 */
    TAF_CBA_READ_CBMIR_FILE_FLG                                          = 0x02,/* 读取CBMIR 文件标记 */
    TAF_CBA_READ_CBMID_FILE_FLG                                          = 0x04,/* 读取CBMID 文件标记 */
    TAF_CBA_READ_SIM_FILES_FLG_BUTT                                      = 0x08 /* 无效标记 */
};
typedef VOS_UINT8 TAF_CBA_READ_SIM_FILES_FLG_ENUM_UINT8;



enum TAF_CBA_DUP_DETECT_CFG_ENUM
{
    TAF_CBA_DUP_DETECT_CFG_ALL_ENABLE                       = 0,    /* 都需要重复检测, 包括上报到应用的CBS(含ETWS), 和下载到USIM的CBS */
    TAF_CBA_DUP_DETECT_CFG_ONLY_DOWNLOAD_TYPE_ENABLE        = 1,    /* 仅对下载到USIM的CBS做重复检测, 上报到应用的CBS(含ETWS)不做重复检测 */
    TAF_CBA_DUP_DETECT_CFG_ALL_DISABLE                      = 2,    /* 都不做重复检测, 包括上报到应用的CBS(含ETWS), 和下载到USIM的CBS */
    TAF_CBA_DUP_DETECT_CFG_BUTT                             = 3
};
typedef VOS_UINT8 TAF_CBA_DUP_DETECT_CFG_ENUM_UINT8;


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/


typedef struct
{
    VOS_UINT8                           ucEfCbmiExistFlg;                       /* USIM中是否存在EFCBMI 文件的标志, VOS_TRUE: 存在, VOS_FALSE: 不存在 */
    VOS_UINT8                           ucRsv;                                  /* 4字节对齐 */
    VOS_UINT16                          usEfCbmiFileLen;                        /* 从EFCBMI 文件中读取的数据的实际长度, EF文件长度(对二进制来说是文件长度，对其它文件来说是记录长度) */
}TAF_CBA_USIM_EFCBMI_FILE_INFO_STRU;


typedef struct
{
    VOS_UINT8                           ucEfCbmirExistFlg;                      /* USIM中是否存在EFCBMIR 文件的标志,  VOS_TRUE: 存在, VOS_FALSE: 不存在  */
    VOS_UINT8                           ucRsv;                                  /* 4字节对齐 */
    VOS_UINT16                          usEfCbmirFileLen;                       /* 从EFCBMIR 文件中读取的数据的实际长度 , EF文件长度(对二进制来说是文件长度，对其它文件来说是记录长度) */
}TAF_CBA_USIM_EFCBMIR_FILE_INFO_STRU;


typedef struct
{
    VOS_UINT8                           ucEfCbmidExistFlg;                      /* USIM中是否存在EFCBMID 文件的标志, VOS_TRUE: 存在, VOS_FASLE: 不存在 */
    VOS_UINT8                           ucRsv;                                  /* 4字节对齐 */
    VOS_UINT16                          usEfCbmidFileLen;                       /* 从EFCBMID 文件中读取的数据的实际长度, EF文件长度(对二进制来说是文件长度，对其它文件来说是记录长度) */
}TAF_CBA_USIM_EFCBMID_FILE_INFO_STRU;



typedef struct
{
    TAF_CBA_USIM_EFCBMI_FILE_INFO_STRU                      stEfCbmiFileInfo;   /* 记录USIM中的Cbmir文件信息 */
    TAF_CBA_USIM_EFCBMIR_FILE_INFO_STRU                     stEfCbmirFileInfo;  /* 记录USIM中的Cbmir文件信息 */
    TAF_CBA_USIM_EFCBMID_FILE_INFO_STRU                     stEfCbmidFileInfo;  /* 记录USIM中的Cbmid文件信息 */
}TAF_CBA_SIM_INFO_STRU;


typedef struct
{
    VOS_UINT16                          usCbmidNum;                             /* 所包含的广播id的总数量 */
    VOS_UINT8                           aucRsv[2];
    VOS_UINT16                          ausMsgId[TAF_CBA_MAX_CBMID_NUM];        /* 具体的广播消息id */
}TAF_CBA_CBMI_DOWNLOAD_LIST_STRU;


typedef struct
{
    TAF_CBA_CBSTATUS_ENUM_UINT8                             enCbStatus;         /* CBS业务是否启用标志 */
    TAF_CBA_DUP_DETECT_CFG_ENUM_UINT8                       enDupDetectCfg;     /* CBS重复过滤开关 */

    VOS_UINT8                                               ucRptAppFullPageFlg; /* VOS_TRUE: 上报整页共88个字节; VOS_FALSE: 上报实际有效字节 */
    VOS_UINT8                                               ucRsv;              /* 4字节对齐，保留 */


    TAF_CBA_CBMI_RANGE_LIST_STRU                            stCbMiRangeList;    /* 用户指定的接收/拒绝消息的ID */

    TAF_CBA_CBMI_DOWNLOAD_LIST_STRU                         stCbMiDownloadList; /* sim卡指定的用于Data Download到卡的消息的ID */
}TAF_CBA_MS_CFG_CBS_INFO_STRU;


typedef struct
{
    VOS_UINT32                          ulSpecMccTimeLen;                       /* 单位:秒, 定制特性激活时主/从通知的MCC在指定Mcc中则使用此重复检测时长 */
    VOS_UINT32                          ulOtherMccTimeLen;                      /* 单位:秒, 定制特性激活时主/从通知的MCC不在指定Mcc中则使用此重复检测时长 */
    VOS_UINT32                          aulSpecMcc[TAF_CBA_MAX_ETWS_DUP_DETECT_SPEC_MCC_NUM];  /* 定制特性相关的MCC */
}TAF_CBA_ENH_DUP_DETECT_TIME_LEN_CFG_STRU;


typedef struct
{
    VOS_UINT8                                               ucEnhDupDetectFlg;  /* DoCoMo增强的重复检测定制特性是否激活, VOS_TRUE:激活,VOS_FALSE:未激活 */
    VOS_UINT8                                               aucRsv[3];
    VOS_UINT32                                              ulNormalTimeLen;    /* 单位:秒, 定制特性未激活时使用此重复检测时长 */
    TAF_CBA_ENH_DUP_DETECT_TIME_LEN_CFG_STRU                stDupDetectTimeLen; /* 定制特性激活时，重复检测时长的配置项 */
}TAF_CBA_DUP_DETECT_CFG_STRU;



typedef struct
{
    VOS_UINT16                          usMsgIdFrom;                            /*Cell broadcast message id value range from  */
    VOS_UINT16                          usMsgIdTo;                              /*Cell broadcast message id value range to    */
}TAF_CBA_ETWS_MSGID_RANGE_STRU;


typedef struct
{
    VOS_UINT8                                               ucEtwsEnableFlg;    /* ETWS特性开关, VOS_TRUE:开启, VOS_FALSE:未开启 */
    VOS_UINT8                                               aucRsv[3];

    TAF_CBA_DUP_DETECT_CFG_STRU                             stDupDetectCfg;     /* 重复检测配置信息 */

    VOS_UINT32                                              ulTempEnableCbsTimeLen;  /* 单位:秒, CBS功能未开启时,收到主通知后临时使能CBS以接收从通知的时长 */

    TAF_CBA_ETWS_MSGID_RANGE_STRU                           astSpecEtwsMsgIdList[TAF_CBA_NVIM_MAX_USER_SPEC_ETWS_MSGID_RANGE_NUM];  /* 用户定制的ETWS的MSG ID的范围 */
}TAF_CBA_MS_CFG_ETWS_INFO_STRU;



typedef struct
{
    TAF_CBA_NET_RAT_TYPE_ENUM_UINT8     enNetMode;                              /* 接收到此条CBS消息的接入技术 */
    VOS_UINT8                           ucTotalPage;                            /* 总页数（G的CBS消息包含此信息） */
    VOS_UINT16                          usPageBitmap;                           /* 已接收页的BitMap(G的CBS消息包含此信息) */

    VOS_UINT16                          usMsgID;                                /* 主从通知/CBS消息ID */
    VOS_UINT16                          usSN;                                   /* 主从通知/CBS序列号 */

    TAF_CBA_PLMN_ID_STRU                stPlmn;
    VOS_UINT32                          ulDupDetcTimeLen;                       /* 有效时长N,单位: 秒, 为0表示一直有效 */
    VOS_UINT32                          ulRcvTimeTick;                          /* 收到消息时的时间戳, 取自 VOS_GetTick, 单位: 10 ms */
}TAF_CBA_RECORD_STRU;


typedef struct
{
    TAF_CBA_NET_RAT_TYPE_ENUM_UINT8     enCurrNetRatType;                       /* 网络模式 */
    VOS_UINT8                           aucRsv3[3];                             /* 4字节对齐  */

    TAF_CBA_PLMN_ID_STRU                stCurPlmn;                              /* PLMN ID  */

    VOS_UINT16                          usSa;                                   /* 服务区信息  */
    VOS_UINT8                           aucRsv2[2];                             /* 4字节对齐  */

    VOS_UINT32                          ulCellId;                               /* 小区ID  */
}TAF_CBA_NETWORK_INFO_STRU;


typedef struct
{
#if (FEATURE_ETWS == FEATURE_ON)

    VOS_UINT16                          usRcvEtwsPrimNtfNum;                    /* ETWS主通知历史记录个数 */
    VOS_UINT8                           aucRsv[2];                              /* 4字节对齐  */
    TAF_CBA_RECORD_STRU                 astRcvEtwsPrimNtfList[TAF_CBA_MAX_ETWS_PRIM_NTF_RECORD_NUM];   /* ETWS主通知历史记录表 */
#endif

    VOS_UINT16                          usRcvCbsNum;                            /* CBS(包括ETWS从通知)历史记录个数 */
    VOS_UINT8                           aucRsv1[2];                             /* 4字节对齐  */
    TAF_CBA_RECORD_STRU                 astRcvCbsList[TAF_CBA_MAX_CBS_RECORD_NUM];  /* CBS(包括ETWS从通知)历史记录表 */
}TAF_CBA_RECORD_LIST_STRU;


typedef struct
{
    TAF_CBA_SIM_INFO_STRU               stCbsSimInfo;                           /* CBS模块SIM卡相关信息 */
    TAF_CBA_MS_CFG_CBS_INFO_STRU        stCbsMsCfg;                             /* 用户配置的CBS信息 */
#if (FEATURE_ETWS == FEATURE_ON)
    TAF_CBA_MS_CFG_ETWS_INFO_STRU       stEtwsMsCfg;                            /* 用户配置的ETWS的信息 */
#endif
    TAF_CBA_NETWORK_INFO_STRU           stCbsNetworkInfo;                       /* 当前网络信息, 其中的 RatType获取自MMC;
                                                                                   PLMN和SA, CELL ID暂未使用 */

    TAF_CBA_NETWORK_INFO_STRU           stOldNetworkInfo;                       /* 保存的上次 GS_STATUS_CHANGE_IND 中网络信息.
                                                                                   目前仅用于判断异系统场景的GS CHG TYPE */

    TAF_CBA_RECORD_LIST_STRU            stRcvRecordList;                        /* CBS及ETWS历史记录信息 */
}TAF_CBA_CTX_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/

VOS_VOID TAF_CBA_InitSimInfo(VOS_VOID);

VOS_VOID TAF_CBA_InitCbmiRangeList(VOS_VOID);

VOS_VOID  TAF_CBA_InitCbsMsCfgInfo(VOS_VOID);

VOS_VOID TAF_CBA_InitNetworkInfo(VOS_VOID);

VOS_VOID TAF_CBA_InitOldNetworkInfo(VOS_VOID);

VOS_VOID TAF_CBA_InitRecordList(VOS_VOID);

VOS_VOID  TAF_CBA_InitCtx(VOS_VOID);

TAF_CBA_CTX_STRU* TAF_CBA_GetCbaCtx(VOS_VOID);

TAF_CBA_SIM_INFO_STRU* TAF_CBA_GetSimInfo(VOS_VOID);

TAF_CBA_USIM_EFCBMI_FILE_INFO_STRU* TAF_CBA_GetEfCbmiInfo(VOS_VOID);

TAF_CBA_USIM_EFCBMIR_FILE_INFO_STRU* TAF_CBA_GetEfCbmiRangeInfo(VOS_VOID);

TAF_CBA_USIM_EFCBMID_FILE_INFO_STRU* TAF_CBA_GetEfCbmidInfo(VOS_VOID);


TAF_CBA_MS_CFG_CBS_INFO_STRU* TAF_CBA_GetMsCfgCbsInfo(VOS_VOID);

TAF_CBA_CBSTATUS_ENUM_UINT8 TAF_CBA_GetCbsStatus(VOS_VOID);
VOS_VOID TAF_CBA_SetCbsStatus(
    TAF_CBA_CBSTATUS_ENUM_UINT8         enCbsStatus
);

VOS_VOID TAF_CBA_SetDupDetectCfg(
    TAF_CBA_DUP_DETECT_CFG_ENUM_UINT8   enTmpDupDetectCfg
);

TAF_CBA_DUP_DETECT_CFG_ENUM_UINT8 TAF_CBA_GetDupDetectCfg(VOS_VOID);


VOS_VOID TAF_CBA_SetRptAppFullPageFlg(
    VOS_UINT8                           ucTmpRptAppFullPageFlg
);

VOS_UINT8 TAF_CBA_GetRptAppFullPageFlg(VOS_VOID);



TAF_CBA_CBMI_DOWNLOAD_LIST_STRU* TAF_CBA_GetCbmiDownloadList(VOS_VOID);

VOS_UINT16 TAF_CBA_GetCbmiDownloadNum(VOS_VOID);

TAF_CBA_CBMI_RANGE_LIST_STRU* TAF_CBA_GetCbMiRangeList(VOS_VOID);

TAF_CBA_CBMI_RANGE_STRU* TAF_CBA_GetCbmiRangeListHead(VOS_VOID);

VOS_UINT16 TAF_CBA_GetCbmiRangNum(VOS_VOID);

VOS_VOID TAF_CBA_SetCbmiRangeNum(
    VOS_UINT16                          usCbmiRangNum
);

#if (FEATURE_ETWS == FEATURE_ON)
VOS_VOID TAF_CBA_InitEtwsMsCfgInfo(VOS_VOID);

TAF_CBA_MS_CFG_ETWS_INFO_STRU* TAF_CBA_GetMsCfgEtwsInfo(VOS_VOID);

VOS_VOID TAF_CBA_SetMsCfgEtwsInfo(
    TAF_CBA_MS_CFG_ETWS_INFO_STRU      *pstMsCfgEtwsInfo
);

VOS_VOID TAF_CBA_SetEtwsEnableFlg(
    VOS_UINT8                           ucEtwsEnableFlg
);

VOS_UINT32 TAF_CBA_GetEtwsEnableFlg(VOS_VOID);

VOS_VOID  TAF_CBA_SetEnhDupDetcFlg(
    VOS_UINT8       ucDetcFlg
);

VOS_UINT8  TAF_CBA_GetEnhDupDetcFlg(VOS_VOID);

VOS_UINT32  TAF_CBA_GetNormalDupDetcTimeLen(VOS_VOID);

TAF_CBA_ENH_DUP_DETECT_TIME_LEN_CFG_STRU* TAF_CBA_GetEnhDupDetcTimeLenCfg(VOS_VOID);

TAF_CBA_ETWS_MSGID_RANGE_STRU* TAF_CBA_GetUserSpecEtwsMsgIdList(VOS_VOID);

VOS_UINT16 TAF_CBA_GetRcvEtwsPrimNtfNum(VOS_VOID);

VOS_VOID TAF_CBA_SetRcvEtwsPrimNtfNum(
    VOS_UINT16                          usEtwsPrimNtfNum
);

TAF_CBA_RECORD_STRU* TAF_CBA_GetRcvEtwsPrimNtfList(VOS_VOID);
#endif


TAF_CBA_NETWORK_INFO_STRU* TAF_CBA_GetNetworkInfo(VOS_VOID);

TAF_CBA_NETWORK_INFO_STRU* TAF_CBA_GetOldNetworkInfo(VOS_VOID);

VOS_VOID TAF_CBA_SetOldNetworkInfo(
    TAF_CBA_NETWORK_INFO_STRU          *pstNetworkinfo
);

TAF_CBA_NET_RAT_TYPE_ENUM_UINT8 TAF_CBA_GetNetRatType(VOS_VOID);

VOS_VOID TAF_CBA_SetNetRatType(
    TAF_CBA_NET_RAT_TYPE_ENUM_UINT8     enCurrNetMode
);

TAF_CBA_PLMN_ID_STRU* TAF_CBA_GetCurrPlmn(VOS_VOID);

TAF_CBA_RECORD_LIST_STRU* TAF_CBA_GetRcvRecordListInfo(VOS_VOID);

VOS_UINT16 TAF_CBA_GetRcvCbsNum(VOS_VOID);

VOS_VOID TAF_CBA_SetRcvCbsNum(
    VOS_UINT16                          usNewRcvCbsNum
);

TAF_CBA_RECORD_STRU* TAF_CBA_GetRcvCbsList(VOS_VOID);

VOS_VOID TAF_CBA_Init(VOS_VOID);

VOS_VOID TAF_CBA_UpdateTempEnableCbsTimerLen(VOS_VOID);


#endif



#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of TafCbaCtx.h */
