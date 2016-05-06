/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafMmaInterface.h
  版 本 号   : 初稿
  作    者   : l60609
  生成日期   : 2014年9月9日
  最近修改   :
  功能描述   : Taf pid和Mma pid之间的接口
  函数列表   :
  修改历史   :
  1.日    期   : 2014年9月9日
    作    者   : l60609
    修改内容   : 创建文件

******************************************************************************/

#ifndef __TAF_MMA_INTERFACE_H__
#define __TAF_MMA_INTERFACE_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "PsTypeDef.h"
#include "NasStkInterface.h"

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
/*****************************************************************************
 枚举名    : TAF_MMA_PID_MSG_TYPE_ENUM
 结构说明  : TAF PID和MMA PID之间的消息接口枚举
*****************************************************************************/
enum TAF_MMA_PID_MSG_TYPE_ENUM
{
    MMCM_OM_MAINTAIN_INFO_IND                               = 0x00000000,       /* _H2ASN_MsgChoice MMCM_OM_MAINTAIN_INFO_IND_STRU */

    MN_USIM_STATUS_IND                                      = 0x00000001,       /* _H2ASN_MsgChoice MNPH_USIM_STATUS_IND_STRU */
    MMA_TAF_POWER_OFF_IND                                   = 0x00000002,       /* _H2ASN_MsgChoice TAF_MMA_POWER_OFF_IND_STRU */
    ID_MMA_MSG_CS_SERVICE_CHANGE_NOTIFY                     = 0x00000003,       /* _H2ASN_MsgChoice MMA_MSG_CS_SERVICE_IND */
    /* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-18, begin */
    ID_MMA_TAF_SERVICE_STATUS_CHANGE_NOTIFY                 = 0x00000004,       /* _H2ASN_MsgChoice MMA_TAF_SERVICE_STATUS_CHANGE_NOTIFY_STRU */
    ID_MMA_TAF_NETWORK_CAPABILITY_CHANGE_NOTIFY             = 0x00000005,       /* _H2ASN_MsgChoice MMA_TAF_NETWORK_CAPABILITY_CHANGE_NOTIFY_STRU */
    ID_MMA_TAF_RAT_CHANGE_NOTIFY                            = 0x00000006,       /* _H2ASN_MsgChoice MMA_TAF_RAT_CHANGE_NOTIFY_STRU */
    /* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-18, end */

    /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-31, begin */
    ID_MMA_TAF_IMS_VOICE_CAP_IND                            = 0x00000007,       /* _H2ASN_MsgChoice MMA_TAF_IMS_VOICE_CAP_IND_STRU */
    /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-31, end */

    /* 移动到tafappmma.h 中 */


    ID_MMA_TAF_1X_SERVICE_STATUS_IND,                                           /* _H2ASN_MsgChoice MMA_TAF_1X_SERVICE_STATUS_IND_STRU */

    ID_MMA_TAF_POWER_ON_IND,                                                    /* _H2ASN_MsgChoice TAF_MMA_POWER_ON_IND_STRU */
    ID_MMA_APS_EPDSZID_INFO_IND,                                                /* _H2ASN_MsgChoice MMA_APS_EPDSZID_INFO_IND_STRU */



    ID_MMA_APS_CL_SERVICE_STATUS_IND,                                           /* _H2ASN_MsgChoice MMA_APS_CL_SERVICE_STATUS_IND_STRU */


    ID_MMA_APS_HRPD_DATA_CALL_SYS_ACQ_IND,                                      /* _H2ASN_MsgChoice MMA_APS_HRPD_DATA_CALL_SYS_ACQ_IND_STRU */

    ID_MMA_TAF_SYS_CFG_INFO_IND,                                                /* _H2ASN_MsgChoice MMA_TAF_SYS_CFG_INFO_IND_STRU */

    ID_TAF_MMA_PID_MSG_TYPE_BUTT
};
typedef VOS_UINT32 TAF_MMA_PID_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : MNPH_USIM_STATUS_ENUM
 结构说明  : MNPH_USIM_STATUS_ENUM消息中的 enUsimStatus
*****************************************************************************/
enum MNPH_USIM_STATUS_ENUM
{
    MNPH_USIM_STATUS_AVILABLE         = 0, /* 卡有效 */
    MNPH_USIM_STATUS_NOT_AVAILABLE    = 1, /* 卡无效 */
    MNPH_USIM_STATUS_BUTT
};
typedef VOS_UINT32 MNPH_USIM_STATUS_ENUM_U32;


/* 转移到tafappmma.h 中 */

/*****************************************************************************
 枚举名    : MMA_APS_RAT_TYPE_ENUM_UINT32
 结构说明  : 当前的接入技术
 1.日    期   : 2014年10月19日
   作    者   : Y00213812
   修改内容   : 新建
*****************************************************************************/
enum MMA_TAF_RAT_TYPE_ENUM
{
    MMA_TAF_RAT_TYPE_NULL,          /* 当前未在任何网络上驻留 */
    MMA_TAF_RAT_TYPE_GSM,           /* GSM接入技术 */
    MMA_TAF_RAT_TYPE_WCDMA,         /* WCDMA接入技术 */
    MMA_TAF_RAT_TYPE_LTE,           /* LTE接入技术 */
    MMA_TAF_RAT_TYPE_1X,            /* CDMA-1X接入技术 */
    MMA_TAF_RAT_TYPE_HRPD,          /* CDMA-HRPD接入技术 */
    MMA_TAF_RAT_TYPE_EHRPD,         /* CDMA-EHRPD接入技术 */
    MMA_TAF_RAT_TYPE_BUTT           /* 无效的接入技术 */
};
typedef VOS_UINT32 MMA_TAF_RAT_TYPE_ENUM_UINT32;


enum MMA_APS_SYS_ACQUIRE_ENUM
{
    MMA_APS_SYS_ACQUIRE_NULL,          /* 当前未在任何网络上驻留 */
    MMA_APS_SYS_ACQUIRE_LTE,           /* LTE接入技术 */
    MMA_APS_SYS_ACQUIRE_1X,            /* CDMA-1X接入技术 */
    MMA_APS_SYS_ACQUIRE_EVDO,          /* CDMA-EVDO接入技术 */
    MMA_APS_SYS_ACQUIRE_1X_EVDO,       /* CDMA-1X&EVDO接入技术 */
    MMA_APS_SYS_ACQUIRE_BUTT           /* 无效的接入技术 */
};
typedef VOS_UINT32 MMA_APS_SYS_ACQUIRE_ENUM_UINT32;


/*****************************************************************************
 枚举名    : MMA_TAF_CL_STATUS_ENUM_UINT32
 结构说明  : 当前的接入技术
 1.日    期   : 2015年06月09日
   作    者   : Y00213812
   修改内容   : 新建
*****************************************************************************/
enum MMA_TAF_CL_STATUS_ENUM
{
    MMA_TAF_CL_STATUS_DO_NO_SERVICE,                  /* DO由有服务变为无服务 */
    MMA_TAF_CL_STATUS_LTE_NO_SERVICE,                 /* LTE由有服务变为无服务 */
    MMA_TAF_CL_STATUS_DO_LTE_NO_SERVICE,              /* 当前DO和LTE经过搜网后，未在任何网络上驻留 */
    MMA_TAF_CL_STATUS_LTE_NORMAL_SERVICE,             /* LTE正常服务 */
    MMA_TAF_CL_STATUS_HRPD_NORMAL_SERVICE,            /* HRPD正常服务 */
    MMA_TAF_CL_STATUS_EHRPD_NORMAL_SERVICE,           /* EHRPD正常服务 */
    MMA_TAF_CL_STATUS_BUTT                            /* 无效的值 */
};
typedef VOS_UINT32 MMA_TAF_CL_STATUS_ENUM_UINT32;


/*****************************************************************************
 枚举名    : MMA_TAF_HRPD_DATA_CALL_SYS_ACQ_RST_ENUM_UINT32
 结构说明  : 当前的接入技术
 1.日    期   : 2015年12月16日
   作    者   : y00314741
   修改内容   : 新建
*****************************************************************************/
enum MMA_TAF_HRPD_DATA_CALL_SYS_ACQ_RST_ENUM
{
    MMA_TAF_HRPD_ACQUIRED_RESULT_SUCC,                  /* DO有服务 */
    MMA_TAF_HRPD_ACQUIRED_RESULT_FAIL,                  /* DO无服务 */
    MMA_TAF_HRPD_ACQUIRED_RESULT_ABORT,                 /* DO搜网被打断 */
    MMA_TAF_HRPD_ACQUIRED_RESULT_NO_RF,                 /* DO搜网资源 */
    MMA_TAF_HRPD_ACQUIRED_RESULT_BUTT                   /* 无效的值 */
};
typedef VOS_UINT32 MMA_TAF_HRPD_DATA_CALL_SYS_ACQ_RST_ENUM_UINT32;
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
    VOS_MSG_HEADER
    unsigned long                       ulMsgName;

    VOS_UINT8                           ucOmConnectFlg;                         /* UE与PC工具的连接标志, VOS_TRUE: 已连接; VOS_FALSE: 未连接 */
    VOS_UINT8                           ucOmPcRecurEnableFlg;                   /* OM配置的发送NAS PC回放消息的使能标志 */

    VOS_UINT8                           aucRsv2[2];                             /* 保留   */
}MMCM_OM_MAINTAIN_INFO_IND_STRU;

typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAF_MMA_PID_MSG_TYPE_ENUM_UINT32    enMsgId;                                /* _H2ASN_Skip */
    MNPH_USIM_STATUS_ENUM_U32           enUsimStatus;
}MNPH_USIM_STATUS_IND_STRU;

typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAF_MMA_PID_MSG_TYPE_ENUM_UINT32    enMsgId;                                /* _H2ASN_Skip */
    VOS_UINT8                           aucReserve[4];
}TAF_MMA_POWER_OFF_IND_STRU;

/*****************************************************************************
 结构名    : MMA_MSG_CS_SERVICE_IND
 结构说明  : MMA给MSG发送CS域变更结构体
1.日    期   : 2013年06月03日
  作    者   : s00217060
  修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAF_MMA_PID_MSG_TYPE_ENUM_UINT32    enMsgId;                                /* _H2ASN_Skip */
    TAF_CS_SERVICE_ENUM_UINT32          enCSState;
}MMA_MSG_CS_SERVICE_IND;

/*****************************************************************************
 结构名    : MMA_TAF_SERVICE_STATUS_CHANGE_NOTIFY_STRU
 结构说明  : MMA给SPM发送服务状态变更结构体
1.日    期   : 2013年09月18日
  作    者   : s00217060
  修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAF_MMA_PID_MSG_TYPE_ENUM_UINT32    enMsgId;                                /* _H2ASN_Skip */
}MMA_TAF_SERVICE_STATUS_CHANGE_NOTIFY_STRU;

/*****************************************************************************
 结构名    : MMA_TAF_NETWORK_CAPABILITY_CHANGE_NOTIFY_STRU
 结构说明  : MMA给SPM发送网络能力变更结构体
1.日    期   : 2013年09月18日
  作    者   : s00217060
  修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAF_MMA_PID_MSG_TYPE_ENUM_UINT32    enMsgId;                                /* _H2ASN_Skip */
}MMA_TAF_NETWORK_CAPABILITY_CHANGE_NOTIFY_STRU;

/*****************************************************************************
 结构名    : MMA_TAF_MODE_CHANGE_NOTIFY_STRU
 结构说明  : MMA给SPM发送模式变更结构体
1.日    期   : 2013年09月18日
  作    者   : s00217060
  修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAF_MMA_PID_MSG_TYPE_ENUM_UINT32    enMsgId;                                /* _H2ASN_Skip */
}MMA_TAF_RAT_CHANGE_NOTIFY_STRU;

/* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-31, begin */
/*****************************************************************************
 结构名    : MMA_TAF_IMS_VOICE_CAP_IND_STRU
 结构说明  : MMA给SPM发送ims voice cap结构体
1.日    期   : 2013年12月31日
  作    者   : W00176964
  修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAF_MMA_PID_MSG_TYPE_ENUM_UINT32    enMsgId;                                /* _H2ASN_Skip */
    VOS_UINT8                           ucImsVoiceAvail;                        /* IMS VOICE是否可用:VOS_TRUE:IMS voice可用; VOS_FALSE: IMS VOICE不可用 */
    VOS_UINT8                           aucReserve[3];                         /* 保留 */
}MMA_TAF_IMS_VOICE_CAP_IND_STRU;

/* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-31, end */

/* 移动到tafappmma.h中 */


/*****************************************************************************
 结构名    : MMA_TAF_1X_SERVICE_STATUS_IND_STRU
 结构说明  : MMA通知TAF 服务状态相关参数
 1.日    期   : 2014年10月19日
   作    者   : Y00213812
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAF_MMA_PID_MSG_TYPE_ENUM_UINT32    enMsgId;                                /* _H2ASN_Skip */
    VOS_UINT32                          ulExist1XService;
}MMA_TAF_1X_SERVICE_STATUS_IND_STRU;


/*****************************************************************************
 结构名    : MMA_APS_CL_SERVICE_STATUS_IND_STRU
 结构说明  : MMA通知APS PS域服务状态相关参数
 1.日    期   : 2015年05月24日
   作    者   : Y00213812
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAF_MMA_PID_MSG_TYPE_ENUM_UINT32    enMsgId;                                /* _H2ASN_Skip */
    MMA_TAF_CL_STATUS_ENUM_UINT32       enClStatus;
    VOS_UINT8                           ucIsNewSession;
    VOS_UINT8                           aucReserved[3];
}MMA_APS_CL_SERVICE_STATUS_IND_STRU;


/*****************************************************************************
 结构名    : MMA_APS_CL_SERVICE_STATUS_IND_STRU
 结构说明  : MMA通知APS PS域服务状态相关参数
 1.日    期   : 2015年05月24日
   作    者   : Y00213812
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                                              ulMsgName;          /* _H2ASN_Skip */
    MMA_TAF_HRPD_DATA_CALL_SYS_ACQ_RST_ENUM_UINT32          enHrpdSysAcqRst;
    MMA_TAF_RAT_TYPE_ENUM_UINT32                            enRatType;

}MMA_APS_HRPD_DATA_CALL_SYS_ACQ_IND_STRU;

/*****************************************************************************
 结构名    : MMA_TAF_SYS_CFG_INFO_IND_STRU
 结构说明  : MMA通知APS SYSCFG结果
 1.日    期   : 2015年12月29日
   作    者   : y00314741
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgName;          /* _H2ASN_Skip */
    TAF_MMA_RAT_ORDER_STRU              stOldRatOrder;
    TAF_MMA_RAT_ORDER_STRU              stNewRatOrder;
}MMA_TAF_SYS_CFG_INFO_IND_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAF_MMA_PID_MSG_TYPE_ENUM_UINT32    enMsgId;                                /* _H2ASN_Skip */
}TAF_MMA_POWER_ON_IND_STRU;



/*****************************************************************************
 结构名    : MMA_APS_EPDSZID_INFO_IND_STRU
 结构说明  : MMA通知TAF EPDSZID相关参数
 1.日    期   : 2014年12月24日
   作    者   : g00261581
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAF_MMA_PID_MSG_TYPE_ENUM_UINT32    enMsgId;                                /* _H2ASN_Skip */
    VOS_UINT16                          usSid;
    VOS_UINT16                          usNid;
    VOS_UINT8                           ucPzid;
    VOS_UINT8                           ucReserved[3];
}MMA_APS_EPDSZID_INFO_IND_STRU;



/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

/* ASN解析结构 */
typedef struct
{
    VOS_UINT32                          ulMsgId;                                /*_H2ASN_MsgChoice_Export TAF_MMA_PID_MSG_TYPE_ENUM_UINT32 */
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          TAF_MMA_PID_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}TAF_MMA_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    TAF_MMA_MSG_DATA                    stMsgData;
}TafMmaInterface_MSG;

/*****************************************************************************
  10 函数声明
*****************************************************************************/





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

#endif /* end of TafMmaInterface.h */


