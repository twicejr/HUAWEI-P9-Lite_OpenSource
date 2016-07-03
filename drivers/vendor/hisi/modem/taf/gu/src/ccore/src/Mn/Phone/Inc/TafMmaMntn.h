

#ifndef __TAF_MMA_MNTN_H__
#define __TAF_MMA_MNTN_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "TafMmaCtx.h"
#include "mdrv.h"
#include "msp_diag_comm.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)



/*****************************************************************************
  2 宏定义
*****************************************************************************/


/*****************************************************************************
  3 枚举定义
*****************************************************************************/

enum TAF_MMA_MNTN_MSG_ID_ENUM
{
    TAF_MMA_LOG_FSM_INFO_IND                                , /*_H2ASN_MsgChoice TAF_MMA_LOG_FSM_INFO_STRU */
    TAF_MMA_LOG_BUFFER_MSG_INFO_IND                         , /*_H2ASN_MsgChoice TAF_MMA_LOG_BUffER_MSG_INFO_STRU */
    TAF_MMA_LOG_INTER_MSG_INFO_IND                          , /*_H2ASN_MsgChoice TAF_MMA_LOG_INTER_MSG_INFO_STRU */
    TAF_MMA_LOG_DRV_API_PWRCTRL_SLEEPVOTE_UNLOCK            , /*_H2ASN_MsgChoice TAF_MMA_LOG_DRV_API_PWRCTRL_SLEEPVOTE_LOCK_STRU */
    TAF_MMA_LOG_DRV_API_PWRCTRL_SLEEPVOTE_LOCK              , /*_H2ASN_MsgChoice TAF_MMA_LOG_DRV_API_PWRCTRL_SLEEPVOTE_LOCK_STRU */

    TAF_MMA_LOG_OPER_CTX_INFO_IND                           , /*_H2ASN_MsgChoice TAF_MMA_LOG_OPER_CTX_INFO_STRU */

    TAF_MMA_LOG_COPS_RLT_INFO_IND                           , /*_H2ASN_MsgChoice TAF_MMA_LOG_COPS_RLT_INFO_STRU */

    TAF_MMA_LOG_NETWORK_APPNETWORK_CTX_INFO_IND             , /*_H2ASN_MsgChoice TAF_SDC_LOG_NETWORK_AND_APPNETWORK_CTX_INFO_STRU */

    TAF_MMA_LOG_READ_NV_INFO_IND                            , /*_H2ASN_MsgChoice TAF_MMA_LOG_READ_NV_INFO_IND_STRU */

    TAF_MMA_LOG_CL_DELAY_REPORT_SERVICE_STATUS_IND         , /*_H2ASN_MsgChoice TAF_MMA_LOG_CL_DELAY_REPORT_SERVICE_STATUS_IND_STRU */

    TAF_MMA_LOG_CL_DELAY_REPORT_SERVICE_STATUS_CTX_ENTER_IND   , /*_H2ASN_MsgChoice TAF_MMA_LOG_CL_DELAY_REPORT_SERVICE_STATUS_CTX_STRU */
    TAF_MMA_LOG_CL_DELAY_REPORT_SERVICE_STATUS_CTX_EXIT_IND    , /*_H2ASN_MsgChoice TAF_MMA_LOG_CL_DELAY_REPORT_SERVICE_STATUS_CTX_STRU */
    TAF_MMA_LOG_BUT
};
typedef VOS_UINT32 TAF_MMA_MNTN_MSG_ID_ENUM_UINT32;


enum TAF_SDC_LOG_OPER_NAME_TYPE_ENUM
{
    TAF_SDC_LOG_OPER_NAME_TYPE_PNN = 1,
    TAF_SDC_LOG_OPER_NAME_TYPE_CPHS,
    TAF_SDC_LOG_OPER_NAME_TYPE_SPN,
    TAF_SDC_LOG_OPER_NAME_TYPE_MMINFO,
    TAF_SDC_LOG_OPER_NAME_TYPE_NV,
    TAF_SDC_LOG_OPER_NAME_TYPE_TABLE,
    TAF_SDC_LOG_OPER_NAME_TYPE_BUTT
};
typedef VOS_UINT8  TAF_SDC_LOG_OPER_NAME_TYPE_ENUM_UINT8;


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
    MSG_HEADER_STRU                     stMsgHeader;/* 消息头                                   */ /*_H2ASN_Skip*/
    TAF_MMA_FSM_ID_ENUM_UINT32          enFsmId;
    VOS_UINT32                          ulState;
}TAF_MMA_LOG_FSM_INFO_STRU;




typedef struct
{
    VOS_MSG_HEADER                                          /* _H2ASN_Skip */
    TAF_MMA_MNTN_MSG_ID_ENUM_UINT32     enMsgId;            /* _H2ASN_Skip*/
    VOS_UINT32                          ulFullFlg;
    TAF_MMA_MSG_QUEUE_STRU              stMsgQueue;
}TAF_MMA_LOG_BUffER_MSG_INFO_STRU;



typedef struct
{
    VOS_MSG_HEADER                                          /* _H2ASN_Skip */
    TAF_MMA_MNTN_MSG_ID_ENUM_UINT32     enMsgId;            /* _H2ASN_Skip*/
    TAF_MMA_OPER_CTX_STRU               astMmaOperCtx[TAF_MMA_MAX_OPER_NUM];
}TAF_MMA_LOG_OPER_CTX_INFO_STRU;



typedef struct
{
    VOS_MSG_HEADER                                          /* _H2ASN_Skip */
    TAF_MMA_MNTN_MSG_ID_ENUM_UINT32     enMsgId;            /* _H2ASN_Skip*/
    VOS_UINT8                           ucFullFlg;
    VOS_UINT8                           ucMsgLenValidFlg;
    VOS_UINT8                           aucReserve[2];
}TAF_MMA_LOG_INTER_MSG_INFO_STRU;


typedef struct
{
    VOS_MSG_HEADER                                          /* _H2ASN_Skip */
    TAF_MMA_MNTN_MSG_ID_ENUM_UINT32     enMsgId;            /* _H2ASN_Skip*/
    PWC_CLIENT_ID_E                     enClientId;
    VOS_UINT32                          ulRslt;
}TAF_MMA_LOG_DRV_API_PWRCTRL_SLEEPVOTE_LOCK_STRU;



typedef struct
{
    TAF_SDC_OPER_NAME_TYPE_PRIO_STRU         stOperNameTypePrio;   /* cops或^eonsucs2查询从PNN或SPN或CPHS或NITZ获取先后顺序优先级*/
    TAF_SDC_SPN_FILE_INFO_STRU               stUsimSpnFileInfo;    /* Usim中的SPN文件0x6f46信息 */
    TAF_SDC_SPN_FILE_INFO_STRU               stSimSpnFileInfo;     /* Sim中的SPN文件0x6f46信息 */
    TAF_SDC_MM_INFO_STRU                     stMmInfo;             /* 记录MM/GMM/EMM info消息中的信息*/
    TAF_SDC_COPS_FORMAT_TYPE_ENUM_UINT8      enCopsFormatType;
    VOS_CHAR                                 cWildCard;             /* 通配符,取值a-f,可代表0-9任意数字 */
    VOS_UINT8                                aucReserved[2];
}TAF_SDC_LOG_EONS_INFO_STRU;




typedef struct
{
    VOS_MSG_HEADER                                          /* _H2ASN_Skip */
    TAF_MMA_MNTN_MSG_ID_ENUM_UINT32         enMsgId;        /* _H2ASN_Skip*/
    TAF_PH_OPERATOR_NAME_STRU               stName;
    TAF_PH_NETWORKNAME_FORMAT               stNameFormat;         /*网络运营商名字格式*/
    TAF_PH_RA_MODE                          ucRaMode;            /*无线接入模式,3G/2G*/
    TAF_PH_PLMN_SEL_MODE                    ucPlmnSelMode;       /*PLMN selection mode*/
    TAF_SDC_LOG_OPER_NAME_TYPE_ENUM_UINT8   enType;
    TAF_SDC_LOG_EONS_INFO_STRU              stEonsInfo;
}TAF_MMA_LOG_COPS_RLT_INFO_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头 */    /* _H2ASN_Skip */
    TAF_MMA_MNTN_MSG_ID_ENUM_UINT32         enMsgId;                            /* 消息ID */    /* _H2ASN_Skip */
    VOS_UINT16                              enNvItem;
    VOS_UINT16                              usNvDataLength;
    VOS_UINT32                              ulPid;
    VOS_UINT8                               aucNvInfo[4];                       /* NV内容 */

}TAF_MMA_LOG_READ_NV_INFO_IND_STRU;


enum TAF_MMA_LOG_DELAY_REPORT_TYPE_ENUM
{
    TAF_MMA_LOG_DELAY_RPT_SRVST = 0,
    TAF_MMA_LOG_DELAY_RPT_CREG,
    TAF_MMA_LOG_DELAY_RPT_CGREG,
    TAF_MMA_LOG_DELAY_RPT_EGREG,
    TAF_MMA_LOG_DELAY_RPT_SID,
    TAF_MMA_LOG_DELAY_RPT_CDMACSQ,
    TAF_MMA_LOG_DELAY_RPT_HDRCSQ,
    TAF_MMA_LOG_DELAY_RPT_BUTT
};
typedef VOS_UINT8  TAF_MMA_LOG_DELAY_REPORT_TYPE_ENUM_UINT8;


typedef struct
{
    VOS_MSG_HEADER
    TAF_MMA_MNTN_MSG_ID_ENUM_UINT32              enMsgId;
    TAF_MMA_LOG_DELAY_REPORT_TYPE_ENUM_UINT8     enDelayRptType;
    VOS_UINT8                                    aucReserved[3];
}TAF_MMA_LOG_CL_DELAY_REPORT_SERVICE_STATUS_IND_STRU;



enum TAF_MMA_LOG_CL_DELAY_REPORT_CTX_TYPE_ENUM
{
    TAF_MMA_LOG_CL_DELAY_REPORT_CTX_TYPE_ENTER = 0,        /* 函数入口勾包消息 */
    TAF_MMA_LOG_CL_DELAY_REPORT_CTX_TYPE_EXIT,             /* 函数出口勾包消息 */
};
typedef VOS_UINT8  TAF_MMA_LOG_CL_DELAY_REPORT_CTX_TYPE_ENUM_UINT8;


typedef struct
{
    VOS_UINT16                          usBandClass;
    VOS_UINT16                          usFreq;
    VOS_INT32                           lSid;             /**<  System identification */
    VOS_INT32                           lNid;             /**<  Network identification */
    VOS_UINT32                          ulMcc;            /**<  Mobile country code */
    VOS_UINT16                          usMnc;            /**<  Mobile network code */
    VOS_UINT16                          usImsi11_12;      /**<  11th and 12th digits of the IMSI */
    VOS_UINT8                           uc1xRfAvailFlg;
    VOS_UINT8                           ucRoamingInd;
    VOS_UINT8                           aucReserved[2];
}TAF_MMA_LOG_CL_DELAY_REPORT_1X_SYS_INFO_STRU;


typedef struct
{
    TAF_MMA_LOG_CL_DELAY_REPORT_1X_SYS_INFO_STRU            st1xSysInfo;         /* 勾包的1x的信息 */
    TAF_SDC_SERVICED_PLMN_INFO_STRU                         st3GppServPlmnInfo;  /* 勾包的lte的信息 */
    TAF_SDC_CS_DOMAIN_INFO_STRU                             stCsDomainInfo;      /*当前CS域信息*/
    TAF_SDC_PS_DOMAIN_INFO_STRU                             stPsDomainInfo;      /*当前PS域信息*/
    TAF_SDC_SYS_MODE_ENUM_UINT8                             enSysMode;
    TAF_SDC_SYS_SUBMODE_ENUM_UINT8                          enSysSubMode;
    TAF_SDC_REPORT_SRVSTA_ENUM_UINT8                        enReportSrvsta;    /* UE的服务状态 ^srvst上报的服务状态*/
    TAF_SDC_SERVICE_DOMAIN_ENUM_UINT8                       enServiceDomain;   /* UE的服务域sysinfo 查询时上报的服务域*/
}TAF_MMA_LOG_CL_DELAY_REPORT_SYS_INFO_STRU;


typedef struct
{
    VOS_MSG_HEADER
    TAF_MMA_MNTN_MSG_ID_ENUM_UINT32                         enMsgId;
    TAF_MMA_LOG_CL_DELAY_REPORT_SYS_INFO_STRU               stNetWorkInfo;              /* 实时系统信息，从g_stTafSdcCtx中的stNetworkInfo中获取 */
    TAF_MMA_LOG_CL_DELAY_REPORT_SYS_INFO_STRU               stAppNetWorkInfo;           /* 延时系统信息，从g_stTafSdcCtx中的stAppNetworkInfo中获取 */
    TAF_MMA_TIMER_STATUS_ENUM_UINT8                         enCsDelayReportTimerStatus; /* CS域延时上报定时器状态 */
    TAF_MMA_TIMER_STATUS_ENUM_UINT8                         enPsDelayReportTimerStatus; /* PS域延时上报定时器状态 */
    TAF_MMA_TIMER_STATUS_ENUM_UINT8                         enDelayRptApsClNoSrvTimerStatue;
    TAF_MMA_TIMER_STATUS_ENUM_UINT8                         enDelayRptApsDoNoSrvTimerStatue;
}TAF_MMA_LOG_CL_DELAY_REPORT_SERVICE_STATUS_CTX_STRU;
/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/
/*****************************************************************************
  H2ASN顶级消息结构定义
*****************************************************************************/
typedef struct
{
    TAF_MMA_MNTN_MSG_ID_ENUM_UINT32     enMsgId;

    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          TAF_MMA_MNTN_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}TAF_MMA_MNTN_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    TAF_MMA_MNTN_MSG_DATA                 stMsgData;
}TafMmaMntn_MSG;


/*****************************************************************************
  10 函数声明
*****************************************************************************/

VOS_VOID  TAF_MMA_LogFsmInfo(VOS_VOID);

VOS_VOID  TAF_MMA_LogBufferQueueMsg(
    VOS_UINT32                          ulFullFlg
);

VOS_VOID TAF_MMA_LogOperCtxInfo(VOS_VOID);

VOS_VOID  TAF_MMA_LogNetworkInfoAndAppNetworkInfo(VOS_VOID);

VOS_VOID  TAF_MMA_SndOmInternalMsgQueueInfo(
    VOS_UINT8                          ucFullFlg,
    VOS_UINT8                          ucMsgLenValidFlg
);

VOS_VOID TAF_MMA_ShowPhoneModeCtrlInfo(VOS_VOID);

VOS_VOID  TAF_MMA_LogDrvApiPwrCtrlSleepVoteUnlock(
    VOS_UINT32                          ulRslt,
    PWC_CLIENT_ID_E                     enClientId
);

VOS_VOID  TAF_MMA_LogDrvApiPwrCtrlSleepVoteLock(
    VOS_UINT32                          ulRslt,
    PWC_CLIENT_ID_E                     enClientId
);

VOS_VOID TAF_MMA_ShowCLConfigInfo(VOS_VOID);

VOS_VOID TAF_MMA_LogCopsRltInfo(
        TAF_PH_NETWORKNAME_STRU                   *pstOperatorName,
        TAF_SDC_LOG_OPER_NAME_TYPE_ENUM_UINT8      enType
);

VOS_VOID TAF_MMA_ModelPihSndUsimStatusInd(
    USIMM_CARD_TYPE_ENUM_UINT32         enCardTypeOne,
    USIMM_CARD_SERVIC_ENUM_UINT32       enCardServiceOne,
    USIMM_CARD_TYPE_ENUM_UINT32         enCardTypeTwo,
    USIMM_CARD_SERVIC_ENUM_UINT32       enCardServiceTwo
);
VOS_VOID TAF_MMA_ModelUphySndInitStatusInd(
    MMA_UPHY_INIT_STATUS_ENUM_UINT16               enInitStatus
);
VOS_VOID TAF_MMA_ModelUsimStatusIndTimeOut(VOS_VOID);
VOS_VOID TAF_MMA_SndTestInterPowerInitReq(VOS_VOID);
VOS_VOID TAF_MMA_TestSetGeoIno(
    VOS_UINT32                          ulMcc,
    VOS_UINT32                          ulMnc
);

VOS_VOID TAF_MMA_LogReadNVInfo(
    VOS_UINT16                              enNvItem,
    VOS_UINT16                              usNvDataLength,
    VOS_UINT32                              ulPid,
    VOS_UINT8                              *pucData
);


#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_VOID TAF_MMA_LogDelayReportInfo(
    TAF_MMA_LOG_DELAY_REPORT_TYPE_ENUM_UINT8    enDelayRptType
);

#endif

VOS_VOID TAF_MMA_LogCLDelayRptSrvStatusCtx(
    TAF_MMA_LOG_CL_DELAY_REPORT_CTX_TYPE_ENUM_UINT8         enMmaLogDelayRptCtxType
);

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

#endif /* end of TafMmaMntn.h */


