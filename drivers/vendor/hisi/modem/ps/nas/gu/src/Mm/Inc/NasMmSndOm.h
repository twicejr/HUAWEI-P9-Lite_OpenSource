
#ifndef _NAS_MM_SND_OM_H
#define _NAS_MM_SND_OM_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "PsTypeDef.h"
#include  "MM_Global.h"

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


enum NAS_MM_OM_MSG_ID_ENUM
{
    /* MM发送给OM的消息 */
    MMOM_LOG_STATE_INFO_IND                       = 0x1000,      /*_H2ASN_MsgChoice  NAS_MM_LOG_STATE_INFO_STRU */
    MMOM_LOG_AUTH_INFO_IND                        = 0x1001,      /*_H2ASN_MsgChoice  NAS_MM_LOG_AUTH_INFO_STRU */

    MMOM_LOG_CTX_INFO_IND                         = 0x1002,      /*_H2ASN_MsgChoice  MMOM_LOG_CTX_INFO_STRU */

    MMOM_LOG_T3212_INFO_IND                       = 0x1003,      /*_H2ASN_MsgChoice  MMOM_LOG_CTX_INFO_STRU */

    MMOM_LOG_BUTT
};
typedef VOS_UINT32 NAS_MM_OM_MSG_ID_ENUM_UINT32;

/* 删除此处枚举定义, 共用NAS_MM_STATE_ENUM_UINT8该枚举定义 */

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
    MSG_HEADER_STRU                     stMsgHeader;/* 消息头 */ /*_H2ASN_Skip*/
    NAS_MM_STATE_ENUM_UINT8             enMmState;
    VOS_UINT8                           aucRsv3[3];
}NAS_MM_LOG_STATE_INFO_STRU;


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;/* 消息头 */ /*_H2ASN_Skip*/
    VOS_UINT8                           ucExpectOpId;
    VOS_UINT8                           ucRcvOpId;
    VOS_UINT8                           aucRsv[2];
}NAS_MM_LOG_AUTH_INFO_STRU;



typedef struct
{
    MSG_HEADER_STRU                                         stMsgHeader;/* 消息头 */ /*_H2ASN_Skip*/

    /* NV中定制的T3212信息 */
    NAS_MML_T3212_TIMER_INFO_CONFIG_STRU                    stMmlT3212NvCfgInfo;

    /* 当前使用NV的T3212时长的计数 */
    VOS_UINT32                                              ulT3212Count;

    /* 网络分配的T3212定时器时长 */
    VOS_UINT32                                              ulNetworkT3212Len;

    /* 网络分配的T3212时长改变后的随机定时器时长 */
    VOS_UINT32                                              ulNetworkRandT3212Len;

    NAS_MML_LAI_STRU                                        stAllocT3212ValueLaiInfo;
    NAS_MM_NETWORK_T3212_VALUE_TYPE_ENUM_UINT8              enT3212ValueType;
    VOS_UINT8                                               aucReserved[3];
}NAS_MM_LOG_T3212_INFO_STRU;


typedef struct
{
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8      enCsUpdateStatus;   /*记录NAS_MML_GetCsUpdateStatus*/
    NAS_MML_CALL_MODE_ENUM_UINT8                   enCallMode;         /*记录NAS_MML_GetCallMode*/
    NAS_MML_CSFB_SERVICE_STATUS_ENUM_UINT8         enCsfbServiceStatus;/*记录NAS_MML_GetCsfbServiceStatus*/
    VOS_UINT8                                      ucImsVoiceAvailFlg; /*记录NAS_MML_GetImsVoiceAvailFlg*/
    VOS_UINT8                                      ucImsVoiceInterSysLauEnableFlg; /*记录NAS_MML_GetImsVoiceInterSysLauEnableFlg*/
    NAS_MML_TIMER_INFO_ENUM_UINT8                  enT3423Status;      /*记录NAS_MML_GetT3423Status*/
    VOS_UINT8                                      ucCsSecurityCksn;   /*记录NAS_MML_GetSimCsSecurityCksn */
    VOS_UINT8                                      ucStaOfRcvXXEstReqCsfb;/*记录NAS_MM_GetStaOfRcvXXEstReq_CSFB*/
    MM_LAI_STRU                                    stAttemptUpdateLaiInfo;/*记录NAS_MM_GetAttemptUpdateLaiInfo*/
    NAS_MML_LAI_STRU                               stCsLastSuccLai;    /*记录NAS_MML_GetCsLastSuccLai*/
    NAS_MML_LAI_STRU                               stCurrCampLai;      /*记录NAS_MML_GetCurrCampLai*/
}MMOM_LOG_MML_CTX_INFO_STRU;


typedef struct
{
    VOS_UINT8                           ucT3213TimerStatus;        /*记录gstMmTimer[MM_TIMER_T3213].ucTimerStatus*/
    VOS_UINT8                           ucT3211TimerStatus;        /*记录gstMmTimer[MM_TIMER_T3211].ucTimerStatus*/
    VOS_UINT8                           ucT3212TimerStatus;        /*记录gstMmTimer[MM_TIMER_T3212].ucTimerStatus*/
    VOS_UINT8                           ucT3242TimerStatus;        /*记录gstMmTimer[MM_TIMER_T3242].ucTimerStatus*/
    VOS_UINT8                           ucT3243TimerStatus;        /*记录gstMmTimer[MM_TIMER_T3243].ucTimerStatus*/
    VOS_UINT8                           aucReserved[3];
}MMOM_LOG_MM_TIMER_INFO_STRU;


typedef struct
{
    VOS_UINT8                           ucMmServiceState;                   /*记录g_MmGlobalInfo.ucMmServiceState*/
    VOS_UINT8                           ConnCtrlInfo_SMS_RcvXXEstReq_ucFlg; /* 记录g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg*/
    VOS_UINT8                           ConnCtrlInfo_SS_RcvXXEstReq_ucFlg;  /* 记录g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg*/
    VOS_UINT8                           ConnCtrlInfo_CC_RcvXXEstReq_ucFlg;  /* 记录g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg*/
    VOS_UINT8                           ucLikeB;                            /*记录g_MmGlobalInfo.ucLikeB*/
    VOS_UINT8                           MsCsInfo_ucOldRac;                  /* 记录g_MmGlobalInfo.MsCsInfo.ucOldRac*/
    VOS_UINT16                          usRac;                              /*记录g_MmGlobalInfo.usRac*/
    VOS_UINT8                           ucNtMod;                            /* 记录g_MmGlobalInfo.ucNtMod*/
    VOS_UINT8                           ucNotCampONPreState;                /* 记录g_MmGlobalInfo.ucNotCampONPreState*/
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enPreRatType;                       /*记录g_MmGlobalInfo.enPreRatType*/
    VOS_UINT8                           ucPreState;                         /*记录g_MmGlobalInfo.ucPreState*/
    NAS_MM_DETACH_TYPE_ENUM_UINT32      stDetachInfo_enDetachType;          /*记录g_MmGlobalInfo.stDetachInfo.enDetachType*/
    VOS_UINT8                           ucAttFlg;                           /*记录g_MmGlobalInfo.ucAttFlg*/
    VOS_UINT8                           ucPowerOnFlg;                       /*记录g_MmGlobalInfo.ucPowerOnFlg*/
    VOS_UINT8                           LuInfo_ucT3212ExpiredFlg;           /*记录g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg*/
    VOS_UINT8                           ucReserved[1];
}MMOM_LOG_MM_GLOBAL_INFO_STRU;



typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;/* 消息头 */ /*_H2ASN_Skip*/
    MMOM_LOG_MML_CTX_INFO_STRU          stMmlCtxInfo;
    MMOM_LOG_MM_GLOBAL_INFO_STRU        stMmGlobalInfo;
    MMOM_LOG_MM_TIMER_INFO_STRU         stMmTimerInfo;
}MMOM_LOG_CTX_INFO_STRU;



/*****************************************************************************
  H2ASN顶级消息结构定义
*****************************************************************************/
typedef struct
{
    NAS_MM_OM_MSG_ID_ENUM_UINT32        enMsgID;    /*_H2ASN_MsgChoice_Export NAS_MM_OM_MSG_ID_ENUM_UINT32*/
                                                    /* 为了兼容NAS的消息头定义，所以转换ASN.1使用NAS_MM_OM_MSG_ID_ENUM_UINT32 */

    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          NAS_MM_OM_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}NAS_MM_SND_OM_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    NAS_MM_SND_OM_MSG_DATA              stMsgData;
}NasMmSndOm_MSG;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern VOS_VOID  NAS_MM_LogMmStateInfo(
    NAS_MM_STATE_ENUM_UINT8             ucMmState
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

#endif

