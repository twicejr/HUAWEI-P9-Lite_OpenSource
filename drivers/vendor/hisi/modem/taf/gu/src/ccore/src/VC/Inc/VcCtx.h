/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : VcCtx.h
  版 本 号   : 初稿
  作    者   : s62952
  生成日期   : 2012年03月03日
  最近修改   :
  功能描述   : VcCtx.c 的头文件
  函数列表   :
  修改历史   :
   1. 日    期   : 2012年03月03日
      作    者   : s62952
      修改内容   : 创建文件

******************************************************************************/
#ifndef _VC_CTX_H_
#define _VC_CTX_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "AppVcApi.h"
#include  "VcMain.h"
#include  "VcCallInterface.h"
#include  "PsTypeDef.h"
#include "hi_list.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  1 全局变量定义
*****************************************************************************/

/*****************************************************************************
  2 宏定义
*****************************************************************************/
/* Added by s00217060 for VoLTE_PhaseI  项目, 2013-08-22, begin */
#define APP_VC_MAX_MSG_BUFF_LEN         (100)
/* Added by s00217060 for VoLTE_PhaseI  项目, 2013-08-22, end */
#define APP_VC_BUFF_MSG_MAX_CNT         32                                      /* VC模块缓存最大消息个数 */

/* Added by j00174725 for V3R3C60_eCall项目, 2014-3-29, begin */
#define APP_VC_MSD_DATA_LEN              (140)
/* Added by j00174725 for V3R3C60_eCall项目, 2014-3-29, end */

#define VC_MAX_AL_ACK_NUM                   (20)

/* 将BIT n置位 */
#define VC_SET_BIT(n)                       (0x01 << n)

#define VC_AL_ACK_CLEAR_DOWN_BIT            VC_SET_BIT(1)                      /* 标识clean Down */



/*****************************************************************************
  3 枚举定义
*****************************************************************************/


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
/* Deleted by s00217060 for VoLTE_PhaseI  项目, 2013-08-16, begin */
/* APP_VC_BUFF_MSG_UNION删除 */
/* Deleted by s00217060 for VoLTE_PhaseI  项目, 2013-08-16, end */

/*****************************************************************************
 结构名    : APP_VC_MS_CFG_INFO_STRU
 结构说明  : NVIM项中的MS定制需求信息
 1.日    期   : 2012年03月03日
   作    者   : s62952
   修改内容   : 新建
 2.日    期   : 2014年3月27日
   作    者   : j00174725
   修改内容   : Ecall项目
*****************************************************************************/
typedef struct
{
    VOS_UINT16                           usVcPcvoiceSupportFlag;                /*Pcvoice业务*/
}APP_VC_MS_CFG_INFO_STRU;

typedef struct
{
    APP_VC_MSG_ORIGIN_ENUM_U16              enMsgOrigin;
    VOS_UINT16                              usReserved;
    /* Modified by s00217060 for VoLTE_PhaseI  项目, 2013-08-16, begin */
    /* IMSA消息分为START_HIFI、STOP_HIFI和HIFI_PARA_CHANGE三个结构体，与原来不一致
       统一改成VOS_UINT8 */
    VOS_UINT8                               aucBufMsg[APP_VC_MAX_MSG_BUFF_LEN];
    /* Modified by s00217060 for VoLTE_PhaseI  项目, 2013-08-16, end */
} APP_VC_BUFFER_MSG_STRU;

/*****************************************************************************
 结构名    : VC_AL_ACK_INFO_STRU
 结构说明  : AL_ACK 上报的信息
 1.日    期   : 2014年06月26日
   作    者   : j00174725
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulTimeStamp;                            /* 上报时间, 单位为tick值 */
    VOS_UINT8                           ucAlAckValue;                           /* AL_ACK值 */
    VOS_UINT8                           aucReserved[3];
}VC_AL_ACK_INFO_STRU;

/*****************************************************************************
 结构名    : VC_AL_ACK_REPORT_INFO_STRU
 结构说明  : AL_ACK 上报的信息
 1.日    期   : 2014年06月26日
   作    者   : j00174725
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulIndex;
    VC_AL_ACK_INFO_STRU                 astAlAckInfo[VC_MAX_AL_ACK_NUM];        /* 上报时间 */
}VC_AL_ACK_REPORT_INFO_STRU;


/*****************************************************************************
 结构名    : VC_ECALL_CTX_STRU
 结构说明  : ecall 上下文定义
 1.日    期   : 2014年3月27日
   作    者   : j00174725
   修改内容   : Ecall项目
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               aucMsdData[APP_VC_MSD_DATA_LEN];     /* 用于保存APP下发的MSD数据 */
    PS_BOOL_ENUM_UINT8                      enMsdFlag;                          /* 用于记录是否下发过MSD数据 */
    PS_BOOL_ENUM_UINT8                      enInECall;                          /* 当前是否在eCall呼叫过程中 */
    PS_BOOL_ENUM_UINT8                      enAllowSetMsdFlag;                  /* 是否允许发送数据 */
    APP_VC_ECALL_TRANS_STATUS_ENUM_UINT8    enEcallState;                       /* MSD传送状态 */
    APP_VC_ECALL_MSD_MODE_ENUM_UINT16       enNewEcallMode;                     /* 用于保存最新APP下发的eCall配置信息(数据传送模式) */
    APP_VC_ECALL_VOC_CONFIG_ENUM_UINT16     enNewEcallVocConfig;                /* 用于保存最新APP下发的eCall配置信息(是否在传送数据时打开声码器) */
    APP_VC_ECALL_MSD_MODE_ENUM_UINT16       enCurrEcallMode;                    /* 用于保存当前MED使用的eCall配置信息(数据传送模式) */
    APP_VC_ECALL_VOC_CONFIG_ENUM_UINT16     enCurrEcallVocConfig;               /* 用于保存当前MED使用的eCall配置信息(是否在传送数据时打开声码器) */
    VOS_UINT32                              ulEcallDescription;                 /* MSD传送状态描述,若表示允许更新MSD的时间窗长度，整数值，单位：毫秒，范围：500~10000 */
    VC_AL_ACK_REPORT_INFO_STRU              stVcAlAckReportInfo;                /* AlAck 消息 */
}VC_ECALL_CTX_STRU;


typedef struct
{

    APP_VC_GLOBAL_STATE_ENUM_U16            enState;                            /* VC的全局状态 */
    MN_CLIENT_ID_T                          clientId;
    MN_OPERATION_ID_T                       opId;
    APP_VC_VOICE_PORT_ENUM_U8               ucVoicePort;
    VOS_UINT8                               ucPcVoiceSupportFlag;
    /* Modified by s00217060 for VoLTE_PhaseI  项目, 2013-07-11, begin */
    APP_VC_START_HIFI_ORIG_ENUM_UINT8       enStartHifiOrig;                    /* 区分是IMSA还是CALL要启动HIFI */
    /* Modified by s00217060 for VoLTE_PhaseI  项目, 2013-07-11, end */
    VOS_BOOL                                bParaUpdate;
    CALL_VC_RADIO_MODE_ENUM_U8              enRadioMode;                        /* 接入模式 */
    CALL_VC_CODEC_TYPE_ENUM_U8              enCodecType;                        /* codec type */
    APP_VC_MUTE_STATUS_ENUM_UINT8           enPreMuteStatus;
    APP_VC_MUTE_STATUS_ENUM_UINT8           enCurrMuteStatus;
    VOS_UINT32                              ulBuffMsgCnt;
    HI_LIST_S                               stBuffMsgListHead;                  /* 缓存消息列表头节点 */
    HTIMER                                  protectTimer;
    VOS_INT32                               iDevHandle;
    VOS_BOOL                                bInCall;                            /* 当前是否在呼叫过程中 */
    APP_VC_MS_CFG_INFO_STRU                 stMsCfgInfo;                        /* MS的配置信息 */
    VOS_UINT32                              ulVoiceTestFlag;

    /* Added by j00174725 for V3R3C60_eCall项目, 2014-3-29, begin */
    VC_ECALL_CTX_STRU                       stEcallCtx;
    /* Added by j00174725 for V3R3C60_eCall项目, 2014-3-29, end */
} APP_VC_STATE_MGMT_STRU;

/* 任意点回放导出全局变量使用*/
typedef struct
{
    APP_VC_STATE_MGMT_STRU                   pc_g_g_stVcStateMgmt;
} NAS_VC_OUTSIDE_RUNNING_CONTEXT_ST;



/*****************************************************************************
 Structure      : NAS_CC_SDT_MSG_ST
 Description    : PC回放工程，CC相关的全局变量通过以下消息结构发送
 Message origin :
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                        MsgHeader;                                          /* 消息头                                   */ /*_H2ASN_Skip*/
    NAS_VC_OUTSIDE_RUNNING_CONTEXT_ST      stOutsideCtx;
}NAS_VC_SDT_MSG_ST;

/*****************************************************************************
 结构名    : APP_VC_BUFF_MSG_NODE_STRU
 结构说明  : VC模块Buffer缓存消息链表节点结构

  1.日    期   : 2015年02月07日
    作    者   : W00316404
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    MsgBlock                           *pBuffMsg;
    HI_LIST_S                           stList;
} APP_VC_BUFF_MSG_NODE_STRU;


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/



/*****************************************************************************
  10 函数声明
*****************************************************************************/
APP_VC_MS_CFG_INFO_STRU* APP_VC_GetCustomCfgInfo( VOS_VOID );
APP_VC_STATE_MGMT_STRU*  APP_VC_GetCtx( VOS_VOID );

/* Added by j00174725 for V3R3C60_eCall项目, 2014-3-29, begin */
APP_VC_STATE_MGMT_STRU*  APP_VC_GetVcStateMgmtAddr( VOS_VOID );

#if (FEATURE_ON == FEATURE_ECALL)
VOS_UINT8* APP_VC_GetEcallMsdAddr( VOS_VOID );
VOS_VOID APP_VC_SetNewEcallCfg( VOS_UINT16 usMode, VOS_UINT16 usVocConfig);
VOS_VOID APP_VC_UpdateCurrEcallCfg(VOS_VOID);
VOS_VOID APP_VC_GetCurrEcallCfg( VOS_UINT16 *pusMode, VOS_UINT16 *pusVocConfig);
VOS_VOID APP_VC_SetInEcallFlag(PS_BOOL_ENUM_UINT8 enFlag);
PS_BOOL_ENUM_UINT8 APP_VC_GetInEcallFlag(VOS_VOID);
VOS_VOID APP_VC_SetMsdFlag(PS_BOOL_ENUM_UINT8 enFlag);
PS_BOOL_ENUM_UINT8 APP_VC_GetMsdFlag(VOS_VOID);
VOS_VOID APP_VC_SetEcallState(APP_VC_ECALL_TRANS_STATUS_ENUM_UINT8 enState);
APP_VC_ECALL_TRANS_STATUS_ENUM_UINT8 APP_VC_GetEcallState(VOS_VOID);
VOS_VOID APP_VC_SetEcallDescription(VOS_UINT32 ulDesc);
VOS_UINT32 APP_VC_GetEcallDescription(VOS_VOID);
VOS_VOID APP_VC_SetAllowSetMsdFlag(PS_BOOL_ENUM_UINT8 enFlag);
PS_BOOL_ENUM_UINT8 APP_VC_GetAllowSetMsdFlag(VOS_VOID);

VC_AL_ACK_REPORT_INFO_STRU* APP_VC_GetAlAckInfoAddr(VOS_VOID);

#endif
/* Added by j00174725 for V3R3C60_eCall项目, 2014-3-29, end */




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

#endif /* end of VcCtx.h */

